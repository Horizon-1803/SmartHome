#define BLYNK_TEMPLATE_ID "TMPL3F8PeB229"
#define BLYNK_TEMPLATE_NAME "Temp Humidity IR"
#define BLYNK_AUTH_TOKEN "XQYjDNMxRESKQHbNPHNBGH7OSvxvaU29"

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

// WiFi & Blynk Credentials
char ssid[] = "Le gareeb";
char pass[] = "legareeb";
char auth[] = "XQYjDNMxRESKQHbNPHNBGH7OSvxvaU29";

#define DHTPIN D4  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define IR_SENSOR D8  
#define LED_ORANGE D3  
#define LED_YELLOW D1  
#define LED_BLUE D2  

const char* apiKey = "8e44c20da5a33fc1cf1db3552db646ba";  
const char* lat = "23.079489415629073";
const char* lon = "76.85159334409776";  

String weatherAPI = "http://api.openweathermap.org/data/2.5/weather?lat=" + 
                 String(lat) + "&lon=" + String(lon) + 
                 "&appid=" + String(apiKey) + "&units=metric";

// Global Variables
float tempSensor, humSensor;
float tempAPI, humAPI;
String weather;

BlynkTimer timer;

String messageV8 = " Monitoring System Active. ";
int scrollPosV8 = 0;

// Function to scroll text on V8 (Alerts)
void scrollTextV8() {
    int textLength = messageV8.length();
    String displayText = messageV8.substring(scrollPosV8, scrollPosV8 + 16);

    if (scrollPosV8 + 16 > textLength) {
        displayText += messageV8.substring(0, (scrollPosV8 + 16) - textLength);
    }

    Blynk.virtualWrite(V8, displayText);

    scrollPosV8++;
    if (scrollPosV8 >= textLength) scrollPosV8 = 0;
}

// Function to fetch weather data
void getWeatherData() {
    HTTPClient http; 
    WiFiClient client;  
    http.begin(client, weatherAPI);
    int httpCode = http.GET();

    if (httpCode > 0) {
        String payload = http.getString();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        
        tempAPI = doc["main"]["temp"];
        humAPI = doc["main"]["humidity"];
        weather = doc["weather"][0]["main"].as<String>();

        Blynk.virtualWrite(V3, tempAPI);
        Blynk.virtualWrite(V2, humAPI);
        Blynk.virtualWrite(V4, "Weather: " + weather); // No scrolling here
        Blynk.virtualWrite(V8, (weather == "Rain" || weather == "Storm") ? "Bad Weather" : "You can go out Today! ");

    } else {
        Blynk.virtualWrite(V4, "Weather Fetch Failed!");
    }
    http.end();
}

// Function to blink LED for alerts
void blinkLED(int pin) {
    for (int i = 0; i < 3; i++) {
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
    }
}

// Function to check alerts and send notifications
void checkAlerts() {
    if (abs(tempSensor - tempAPI) > 3) {
        Serial.println("⚠️ TEMPERATURE ALERT: Significant temperature difference detected.");
        
        Blynk.logEvent("temp_alert", "⚠️ Temperature Difference Detected\n"
                       "🏠 Indoor: " + String(tempSensor) + "°C\n"
                       "🌍 Outdoor: " + String(tempAPI) + "°C\n"
                       "🔎 Please check ventilation or heating/cooling adjustments.");

        blinkLED(LED_ORANGE);
    }

    if (abs(humSensor - humAPI) > 10) {
        Serial.println("⚠️ HUMIDITY ALERT: Significant humidity variation detected.");

        if (humAPI > humSensor) {
            Blynk.logEvent("humidity_alert", "⚠️ Humidity Alert\n"
                           "🏠 Indoor: " + String(humSensor) + "%\n"
                           "🌍 Outdoor: " + String(humAPI) + "%\n"
                           "🔎 Consider increasing indoor ventilation to balance humidity.");
        } else {
            Blynk.logEvent("humidity_alert", "⚠️ Humidity Alert\n"
                           "🏠 Indoor: " + String(humSensor) + "%\n"
                           "🌍 Outdoor: " + String(humAPI) + "%\n"
                           "🔎 Reduce ventilation to maintain indoor humidity levels.");
        }

        blinkLED(LED_YELLOW);
    }
}

// Function to read sensors and update Blynk
void readSensors() {
    tempSensor = dht.readTemperature();
    humSensor = dht.readHumidity();
    int motion = digitalRead(IR_SENSOR);

    Blynk.virtualWrite(V0, tempSensor);
    Blynk.virtualWrite(V1, humSensor);
    Blynk.virtualWrite(V5, motion ? "Motion Detected" : "No Motion");

    messageV8 = (weather == "Rain" || weather == "Storm") ? "Bad Weather" : "You can go out Today! ";

    if (motion) {
        Serial.println("⚠ Motion Detected! Turning ON LED.");
        digitalWrite(LED_BLUE, HIGH);  // Turn ON LED for motion detection
        Blynk.logEvent("motion_detected", "⚠ Motion Detected at Home!");
    } else {
        Serial.println("✅ No Motion. Turning OFF LED.");
        digitalWrite(LED_BLUE, LOW);  // Turn OFF LED when no motion
    }

    if (tempSensor > 30) {
        Blynk.logEvent("high_temperature", "🔥 High Temperature Alert: " + String(tempSensor) + "°C!");
    }

    checkAlerts(); 
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    Blynk.begin(auth, ssid, pass);
    
    pinMode(IR_SENSOR, INPUT);
    pinMode(LED_ORANGE, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    timer.setInterval(500L, scrollTextV8);  // Scroll LCD V8 (Alerts)
    timer.setInterval(10000L, getWeatherData);  // Fetch API data every 10s
    timer.setInterval(2000L, readSensors);  // Read sensors every 2s
}

void loop() {
    Blynk.run();
    timer.run();
}
