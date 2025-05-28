#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

#define MQ2_PIN A0
#define BUZZER_PIN 5  // D1 = GPIO5
#define LED_PIN 4     // D2 = GPIO4

// Wi-Fi credentials
const char* ssid = "Amir Hajipoor";
const char* password = "webdeveloper";

// Backend API
const char* backendEndpoint = "https://fire-detector.liara.run/v1/reports";
const String bearerToken = "2|HFqtO8f9aptOYZUc7h29aT8XIwuj8jZQF0dSlDE1cfd16710";

// Threshold
const int smokeThreshold = 400;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
}

void loop() {
  int mq2Value = analogRead(MQ2_PIN);
  Serial.print("Gas value: ");
  Serial.println(mq2Value);

  if (mq2Value > smokeThreshold) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000); // Alert sound

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client;
      client.setInsecure(); // ⚠️ Disable SSL check (for development only)

      HTTPClient https;

      if (https.begin(client, backendEndpoint)) {
        https.addHeader("Content-Type", "application/json");
        https.addHeader("Accept", "application/json");
        https.addHeader("Authorization", "Bearer " + bearerToken);

        String jsonPayload = "{\"value\":" + String(mq2Value) + "}";
        int httpCode = https.POST(jsonPayload);

        if (httpCode > 0) {
          Serial.print("Response code: ");
          Serial.println(httpCode);
          String response = https.getString();
          Serial.println("Server response: " + response);
        } else {
          Serial.print("POST failed. Error: ");
          Serial.println(https.errorToString(httpCode));
        }

        https.end();
      } else {
        Serial.println("HTTPS connection failed");
      }

      delay(5000); // cooldown to avoid spamming server
    } else {
      Serial.println("Wi-Fi disconnected");
    }

  } else {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(500);
  }

  delay(100);
}