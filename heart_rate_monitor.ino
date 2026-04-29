/*
 * Heart Rate Monitor using Arduino UNO & Pulse Sensor
 * 
 * Course   : Digital Logic Design (DLD)
 * University: Fatima Jinnah Women University (FJWU)
 * Section  : BCS-II(A)
 * 
 * Group Members:
 *   - Naila Shaheen    (FA24B1-CS-015)
 *   - Yasha Akmal      (FA24B1-CS-049)
 *   - Amna Malik       (FA24B1-CS-051)
 *   - Aleeza Shakeel   (FA24B1-CS-027)
 * 
 * Submitted to: Sir Majid Shafique
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---- Pin Definitions ----
#define SENSOR_PIN   A0
#define OLED_RESET   4

// ---- Constants ----
#define THRESHOLD    512       // Adjust based on sensor calibration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ---- Objects ----
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---- Variables ----
int sensorValue = 0;
int BPM = 0;
unsigned long lastBeatTime = 0;
unsigned long beatInterval = 0;

// Moving average for smoothing
int readings[10];
int readIndex = 0;
long total = 0;
int average = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true); // Stop if display fails
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.println("Heart Rate Monitor");
  display.display();
  delay(2000);

  // Initialize readings array
  for (int i = 0; i < 10; i++) readings[i] = 0;
}

void loop() {
  // Read analog sensor value
  sensorValue = analogRead(SENSOR_PIN);

  // Moving average filter (noise reduction)
  total -= readings[readIndex];
  readings[readIndex] = sensorValue;
  total += readings[readIndex];
  readIndex = (readIndex + 1) % 10;
  average = total / 10;

  // Peak detection
  if (average > THRESHOLD) {
    unsigned long currentTime = millis();
    beatInterval = currentTime - lastBeatTime;

    // Valid beat: between 30 BPM (2000ms) and 200 BPM (300ms)
    if (beatInterval > 300 && beatInterval < 2000) {
      BPM = 60000 / beatInterval;
      lastBeatTime = currentTime;

      // Display BPM on OLED
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0, 0);
      display.println("Heart Rate Monitor");
      display.drawLine(0, 10, 128, 10, SSD1306_WHITE);

      display.setTextSize(3);
      display.setCursor(20, 20);
      display.print(BPM);

      display.setTextSize(1);
      display.setCursor(90, 30);
      display.println("BPM");

      display.display();

      // Also print to Serial Monitor
      Serial.print("BPM: ");
      Serial.println(BPM);
    }
  }

  delay(10);
}
