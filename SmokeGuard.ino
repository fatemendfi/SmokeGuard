define MQ2_PIN A0
#define BUZZER_PIN 5  // GPIO5 = D1
#define LED_PIN 4     // GPIO4 = D2

const int smokeThreshold = 400;
bool smokeDetected = false;
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 2000;
bool ledState = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int mq2Value = analogRead(MQ2_PIN);
  Serial.println(mq2Value);

  if (mq2Value > smokeThreshold) {
    smokeDetected = true;
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 2000);
  } else {
    smokeDetected = false;

    unsigned long currentMillis = millis();
    if (currentMillis - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
/* 
      if (ledState) {
        tone(BUZZER_PIN, 2000); 
      } else {
        noTone(BUZZER_PIN);
      } */
    }
  }

  delay(50);
}
