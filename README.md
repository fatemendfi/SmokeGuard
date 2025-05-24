# SmokeGuard ESP
backend:
https://github.com/amirhajipoor/fire-detector-backend
A simple and effective smoke detection system using an **MQ2 gas sensor** and **ESP8266** (NodeMCU). The system continuously monitors the air for smoke or gas presence. If the smoke level exceeds a defined threshold, it triggers an alarm using a **buzzer** and **LED**. When no smoke is detected, the LED blinks periodically to indicate normal operation.

## 🛠️ Features

- 📟 **MQ2 Sensor**: Reads smoke/gas concentration through analog pin.
- 🔔 **Buzzer Alert**: Activates when smoke exceeds the threshold.
- 💡 **LED Indicator**:
  - Solid ON when smoke is detected.
  - Blinks every 2 seconds when air is clean.
- 📊 Serial output for monitoring sensor values (via Serial Monitor).
- 🚀 Lightweight and easy to deploy on ESP8266 NodeMCU.

## ⚙️ Hardware Requirements

- ESP8266 NodeMCU (e.g., ESP-12E)
- MQ2 Gas Sensor
- Buzzer
- LED
- Resistors (220Ω for LED)
- Breadboard + jumper wires
- USB cable for programming

## 🔌 Circuit Diagram (Pin Mapping)

| Component   | ESP8266 Pin | Description        |
|-------------|-------------|--------------------|
| MQ2 Sensor  | A0          | Analog read pin    |
| Buzzer      | D1 (GPIO5)  | Output for alarm   |
| LED         | D2 (GPIO4)  | Status indicator   |

## 🧠 Code Logic

```cpp
#define MQ2_PIN A0
#define BUZZER_PIN 5  // GPIO5 = D1
#define LED_PIN 4     // GPIO4 = D2

const int smokeThreshold = 400;

void loop() {
  int mq2Value = analogRead(MQ2_PIN);

  if (mq2Value > smokeThreshold) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
  } else {
    // Blink LED every 2 seconds when no smoke
    // Optional: toggle buzzer too
  }
}
