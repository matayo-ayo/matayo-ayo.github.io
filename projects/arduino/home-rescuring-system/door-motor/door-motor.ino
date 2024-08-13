#include <Servo.h>

Servo doorMotor;
Servo lockHandler;

void setup() {
  doorMotor.attach(2);
  lockHandler.attach(3);
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
  delay(1000);
  lockHandler(0);
  digitalWrite(LED_BUILTIN, LOW);
}

void unlockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  doorMotor.write(0);
  delay(1000);
  lockHandler(90);
  digitalWrite(LED_BUILTIN, LOW);
}