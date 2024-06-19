#include <Servo.h>

Servo doorMotor;

void setup() {
  doorMotor.attach(3);
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
  doorMotor.write(180);
  digitalWrite(LED_BUILTIN, LOW);
}

void unlockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  doorMotor.write(0);
  digitalWrite(LED_BUILTIN, LOW);
}