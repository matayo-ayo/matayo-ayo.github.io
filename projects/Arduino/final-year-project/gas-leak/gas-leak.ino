#include <Servo.h>

const int gasSensorPin = A0;
const int gasLedPin = 6;
const int threshold = 300;

Servo windowMotor;

void setupGasCheck() {
  pinMode(gasSensorPin, INPUT);
  pinMode(gasLedPin, OUTPUT);
  windowMotor.attach(7);
  pinMode(LED_BUILTIN, OUTPUT);
}

void gasChecker() {
  int gasLevel = analogRead(gasSensorPin);
  Serial.println("Gas level: " + gasLevel);

  if (gasLevel >= threshold) {
    digitalWrite(gasLedPin, HIGH);
    sendMessage("TAARIFA:\nKiwango cha gesi kinakadiriwa kuzidi. Dirisha linafunguliwa kwa usalama");
    openWindow(windowMotor.read());
  } else {
    digitalWrite(gasLedPin, LOW);
    releaseWindow(windowMotor.read());
  }
}

void openWindow(int rotation) {
  for (int x = rotation; x <= 180; x += 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowMotor.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

void releaseWindow(int rotation) {
  for (int x = rotation; x >= 0; x -= 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowMotor.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}