# **Smart Environment Monitoring System using ESP8266 & Blynk**

## **Overview**
This project is a **real-time monitoring system** that tracks **temperature, humidity, and motion** using an **ESP8266**, **DHT11**, and **IR sensor**. It integrates with the **Blynk app** for remote monitoring and uses a **Weather API** to compare indoor and outdoor conditions.

## **Features**
- 📡 **Real-time data collection** using DHT11 & IR sensors  
- 🌐 **Wi-Fi-enabled remote monitoring** via the Blynk app  
- ☁️ **Weather API integration** for environmental comparison  
- 🚨 **LED indicators** for temperature, humidity, and motion alerts  
- 🔔 **Instant notifications** for abnormal readings  
- 🔋 **USB-powered** for reliable performance  
- 📲 **Custom mobile dashboard** for tracking data in real-time  

## **Components Used**
- **ESP8266 (NodeMCU)** – Wi-Fi microcontroller
- **DHT11 Sensor** – Measures temperature & humidity
- **IR Sensor** – Detects motion
- **3 LEDs (Orange, Yellow, Blue)** – Alert indicators
- **USB Power Supply** – Reliable power source
- **Blynk App** – For remote monitoring
- **Weather API** – Fetches outdoor temperature & humidity data

## **Circuit Diagram**
(Insert circuit diagram image here)

## **Setup & Installation**
### **1. Hardware Connections:**
- **DHT11** Data → D4
- **IR Sensor** OUT → D8
- **LED (Orange)** → D3
- **LED (Yellow)** → D1
- **LED (Blue)** → D2
- **Power** via USB

### **2. Software Requirements:**
- Install **Arduino IDE**
- Add **ESP8266 Board Manager**
- Install necessary libraries:
  - `BlynkSimpleEsp8266.h`
  - `ESP8266WiFi.h`
  - `DHT.h`
  - `ArduinoJson.h`
  - `ESP8266HTTPClient.h`

### **3. Uploading Code:**
1. Open the provided **Arduino sketch**.
2. Enter your **Wi-Fi credentials** in the code.
3. Upload the code to **ESP8266**.
4. Open the **Blynk app**, create a dashboard & link it with your device.
5. Run the system and start monitoring!

## **How It Works**
1. The **DHT11 sensor** reads temperature & humidity.
2. The **IR sensor** detects motion.
3. Data is sent to **Blynk** via **Wi-Fi**.
4. The system fetches **outdoor weather data** using an API.
5. Alerts are triggered if:
   - Temperature difference is **>3°C**.
   - Humidity difference is **>10%**.
   - Motion is detected.
6. **LEDs blink** for alerts and notifications are sent to Blynk.

## **Applications**
- 🏠 **Smart Home Automation** – Monitors indoor environment
- 🏭 **Industrial Monitoring** – Detects abnormal temperature/humidity levels
- 🏥 **Medical Facilities** – Ensures stable room conditions for patient care

## **Future Improvements**
- 🔊 Add a **buzzer** for audible alerts
- 📊 Store data in a **cloud database** for historical analysis
- 🔋 Optimize for **battery-powered operation**
- 🏢 Expand to **multi-room monitoring** with more sensors

## **Contributing**
Feel free to fork this repository, improve it, and submit pull requests! 🚀

## **License**
This project is open-source and available under the **MIT License**.

---

💡 **Made with ❤️ and Blynk!** 🚀

