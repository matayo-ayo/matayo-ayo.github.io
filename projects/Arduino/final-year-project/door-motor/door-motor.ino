#include <Servo.h>

Servo doorMotor;

void setup() {
  doorMotor.attach(8);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  lockDoor();
  delay(2000);
  unlockDoor();
}

void lockDoor() {
  doorMotor.write(180);
  digitalWrite(LED_BUILTIN, HIGH);
}

void unlockDoor() {
  doorMotor.write(0);
}