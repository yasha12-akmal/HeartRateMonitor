# 💓 Heart Rate Monitor using Arduino UNO & Pulse Sensor

> A non-invasive heart rate monitoring system that detects pulse from a fingertip and displays BPM on an LCD display in real-time.

---

## 📌 Project Overview

This project was developed as part of the **Digital Logic Design (DLD)** course at **Fatima Jinnah Women University**, Department of Computer Science.

The system uses **PPG (Photoplethysmography)** — an optical technique that measures blood volume changes using light — to calculate and display the user's heart rate in real-time on an LCD screen.

---

## 👩‍💻 Group Members

| Name | Roll No |
|------|---------|
| Naila Shaheen | FA24B1-CS-015 |
| Yasha Akmal | FA24B1-CS-049 |
| Amna Malik | FA24B1-CS-051 |
| Aleeza Shakeel | FA24B1-CS-027 |

**Submitted to:** Sir Majid Shafique  
**Section:** BCS-II(A)

---

## 🎯 Objective

To develop a device that:
- ✅ Accurately detects human heartbeats using a fingertip pulse sensor
- ✅ Calculates the heart rate in **BPM (Beats Per Minute)**
- ✅ Displays the result on an **LCD screen** in real-time

---

## 📸 Project Demo

### Hardware Setup
![Circuit Overview](Circuit_Overview.jpg)

### LCD Displaying BPM Output
![Heart Rate 46 BPM](Heart_Rate_46BPM.jpg)
![Heart Rate 129 BPM](Heart_Rate_129BPM.jpg)

### LCD Scrolling Output
![LCD Output](LCD_Output.jpg)

### Pulse Sensor (Glowing Red on Finger)
![Pulse Sensor](Pulse_Sensor.jpg)

### Arduino Code
![Code Screenshot](Code_Screenshot.jpg)

---

## 🛠️ Components Used

| Component | Description |
|-----------|-------------|
| Arduino UNO | Main microcontroller |
| Pulse Sensor | Detects heartbeat via PPG |
| LCD Display (16x2) | Shows BPM in real-time |
| LED (IR/Green) | Emits light through skin |
| Op-Amp (LM358) | Amplifies small PPG signals |
| Resistors & Capacitors | Signal filtering |
| Jumper Wires | Circuit connections |
| USB Cable | Power from laptop |

---

## ⚙️ Working Principle

```
Finger placed on Pulse Sensor
        ↓
LED emits light into skin
        ↓
Blood absorbs light → Photodiode detects changes
        ↓
Analog signal → Arduino ADC
        ↓
Digital filtering → Peak Detection
        ↓
BPM = 60000 / (time between beats)
        ↓
Display on LCD Screen
```

---

## 💻 Arduino Code

```cpp
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = A0;
int BPM = 0;
unsigned long lastBeatTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Heart Rate Mon.");
  delay(2000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  if (sensorValue > 512) {
    unsigned long currentTime = millis();
    unsigned long interval = currentTime - lastBeatTime;

    if (interval > 300 && interval < 2000) {
      BPM = 60000 / interval;
      lastBeatTime = currentTime;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Heart Rate:");
      lcd.setCursor(0, 1);
      lcd.print(BPM);
      lcd.print(" BPM");
    }
  }
  delay(10);
}
```

---

## 📡 Signal Processing

- **Analog Filtering:** Low-pass filter removes high-frequency noise
- **Digital Filtering:** Moving average smoothing
- **Peak Detection:** Threshold-based beat detection
- **BPM Formula:** `BPM = 60000 / interval_between_beats`

---

## 🔋 Applications

- Personal health and fitness tracking
- Hospital patient monitoring
- Wearable health devices
- Academic biomedical engineering projects

---

## ⚠️ Limitations

- Motion artifacts can affect accuracy
- Requires proper finger placement on sensor
- Ambient light may cause interference

---

## 🔮 Future Scope

- Add SpO2 (blood oxygen) measurement
- Bluetooth wireless data transmission
- Mobile app integration
- Machine learning for heart anomaly detection

---

## 🏫 Academic Info

**Course:** Digital Logic Design (DLD)  
**University:** Fatima Jinnah Women University (FJWU)  
**Semester:** BCS - 2nd Year  
**Year:** 2024-2025

---

*Made with ❤️ by Group BCS-II(A) — FJWU*
