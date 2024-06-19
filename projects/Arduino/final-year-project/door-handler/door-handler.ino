#include <Servo.h>

Servo lockMotor;

void setup() {
  lockMotor.attach(2);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  lockDoor();
  delay(2000);
  unlockDoor();
  delay(2000);
}

void lockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  lockMotor.write(0);
  digitalWrite(LED_BUILTIN, LOW);
}

void unlockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  lockMotor.write(90);
  digitalWrite(LED_BUILTIN, LOW);
}