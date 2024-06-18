#include <Servo.h>

Servo windowControl;

void setup() {
  windowControl.attach(8);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  openWindow(windowControl.read());
  closeWindow(windowControl.read());
}

void openWindow(int rotation) {
  for (int x = rotation; x <= 180; x += 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowControl.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

void closeWindow(int rotation) {
  for (int x = rotation; x >= 0; x -= 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowControl.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}