#include <Servo.h>

Servo windowControl;

void setup() {
  windowControl.attach(4);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  openWindow();
  closeWindow();
}

void openWindow() {
  for (int x = 0; x <= 180; x += 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowControl.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

void closeWindow() {
  for (int x = 180; x >= 0; x -= 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowControl.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}