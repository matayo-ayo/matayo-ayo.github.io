#include <Servo.h>

Servo handlerMotor;

void setup() {
  handlerMotor.attach(9);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  lockHandler();
  delay(2000);
  unlockHandler();
}

void lockHandler() {
  handlerMotor.write(90);
  digitalWrite(LED_BUILTIN, HIGH);
}

void unlockHandler() {
  handlerMotor.write(0);
  digitalWrite(LED_BUILTIN, LOW);
}