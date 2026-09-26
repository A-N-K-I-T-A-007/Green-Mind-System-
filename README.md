# 🌱 Green Mind System

### An IoT-Driven Approach for Smart Waste Monitoring and Management

**Green Mind System** is an IoT-enabled smart waste management prototype designed to automate **waste detection, segregation, monitoring, and safety management**.

The system uses an **ESP32 NodeMCU** as the central controller and combines moisture, inductive proximity, IR, gas, and other sensors with servo/stepper-based mechanical actuation. Waste is classified into **Wet, Dry, and Metal** categories and automatically directed to the appropriate compartment.

The system also uses **Blynk IoT** for real-time monitoring, status visualization, and alerts.

---

## 🚀 Features

* ♻️ **Automatic Waste Segregation**

  * Wet Waste
  * Dry Waste
  * Metal Waste

* 📡 **IoT-Based Monitoring**

  * Real-time sensor monitoring
  * Cloud connectivity through Wi-Fi
  * Blynk dashboard integration

* 💧 **Moisture Detection**

  * Identifies wet and dry waste based on moisture level.

* 🔩 **Metal Detection**

  * Inductive proximity sensor detects metallic objects.

* 📊 **Bin Fill-Level Monitoring**

  * IR sensors monitor the fill level of individual compartments.

* 🛡️ **Gas Monitoring**

  * MQ-135 sensor monitors gases associated with waste decomposition.

* ⚙️ **Automated Mechanical Sorting**

  * Servo motor controls the sorting flap.
  * Stepper motor can be used for controlled mechanical movement.

* 🔔 **Alert System**

  * Bin-full notifications
  * Gas-level warnings
  * Sensor malfunction alerts
  * Maintenance notifications

The documented prototype achieved **94% overall segregation accuracy** during testing of 100 waste items.

---

## 🧠 How It Works

The system follows a sensor-based decision-making process:

```text
Waste Item
    ↓
Object Detection
    ↓
Sensor Data Collection
    ↓
Metal Detection
    ↓
Moisture Detection
    ↓
Waste Classification
    ↓
┌───────────────┐
│  Metal        │
│  Wet          │
│  Dry          │
└───────────────┘
    ↓
Servo / Motor Actuation
    ↓
Waste Directed to
Correct Compartment
    ↓
Fill Level + Gas Monitoring
    ↓
Blynk IoT Dashboard
```

The classification logic prioritizes metal detection first. If the object is non-metallic, its moisture level is evaluated; objects above the defined moisture threshold are classified as wet, while the remaining objects are classified as dry.

---

## 🔧 Hardware Components

| Component                      | Purpose                                             |
| ------------------------------ | --------------------------------------------------- |
| **ESP32 NodeMCU**              | Main microcontroller and Wi-Fi communication        |
| **Moisture Sensor**            | Detects wet/dry waste                               |
| **Inductive Proximity Sensor** | Detects metal waste                                 |
| **IR Proximity Sensors**       | Monitors bin fill levels                            |
| **MQ-135 Gas Sensor**          | Detects harmful gases                               |
| **Servo Motor**                | Controls waste-sorting flap                         |
| **Stepper Motor**              | Provides controlled mechanical movement             |
| **Ultrasonic Sensor**          | Object/distance detection                           |
| **Power Supply**               | Provides power to controller, sensors and actuators |

The project architecture is organized into sensing, processing, actuation, communication, and user-interface layers.

---

## 💻 Software & Technologies

* **Embedded C / C++**
* **Arduino IDE**
* **ESP32**
* **Blynk IoT**
* **Wi-Fi**
* **Sensor-based classification**
* **Servo Motor Control**
* **IoT Cloud Monitoring**

### Libraries

```text
WiFi
Blynk
Servo
EEPROM (optional)
Preferences (optional)
Timer (optional)
```

The software is developed using Arduino IDE with the ESP32 board package and Arduino framework.

---

## 🔌 System Architecture

```text
                  ┌─────────────────────┐
                  │      ESP32          │
                  │   Main Controller   │
                  └──────────┬──────────┘
                             │
        ┌────────────────────┼────────────────────┐
        │                    │                    │
        ▼                    ▼                    ▼
 Moisture Sensor      Metal Sensor          IR Sensors
        │                    │                    │
        └────────────────────┼────────────────────┘
                             │
                             ▼
                    Waste Classification
                             │
                             ▼
                    Servo / Stepper Motor
                             │
              ┌──────────────┼──────────────┐
              ▼              ▼              ▼
            WET             DRY           METAL
                             │
                             ▼
                     Blynk IoT Platform
                             │
                  ┌──────────┴──────────┐
                  ▼                     ▼
             Monitoring              Alerts
```

---

## 📱 IoT Monitoring

The ESP32 connects to the internet through its built-in Wi-Fi and communicates with the **Blynk Cloud Platform**.

The Blynk interface can display:

* Sensor readings
* Bin status
* Fill levels
* Gas concentration
* System status
* Alerts and notifications

This enables remote monitoring of the smart dustbin system.

---

## 📈 Results

The prototype was tested using **100 waste items**:

| Waste Category | Test Samples | Correctly Classified | Accuracy |
| -------------- | -----------: | -------------------: | -------: |
| Wet            |           40 |                   38 |      95% |
| Dry            |           40 |                   37 |    92.5% |
| Metal          |           20 |                   19 |      95% |
| **Overall**    |      **100** |               **94** |  **94%** |

The documented system recorded a total segregation cycle of approximately **2–3 seconds**, while Blynk update latency was approximately **1–2 seconds**, depending on Wi-Fi conditions.

---

## ⚠️ Challenges

During development and testing, several challenges were identified:

* Moisture sensor readings can be affected by environmental humidity.
* Metallic objects may require accurate positioning for reliable detection.
* Servo motors can experience mechanical wear with repeated operation.
* Wi-Fi connectivity affects cloud mon
