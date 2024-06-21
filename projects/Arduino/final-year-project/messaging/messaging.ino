#include <SoftwareSerial.h>

SoftwareSerial gsm(1, 0);

void setup() {
    Serial.begin(9600);
    gsm.begin(9600);
    delay(3000);
}

void loop() {
    sendMessage("Hello from GSM module!");
    delay(2000);
}

void sendMessage(String message) {
    gsm.println("AT+CMGF=1");
    delay(100);
    gsm.println("AT+CMGS=\"+000123456789\"\r");
    delay(100);
    gsm.println(message);
    delay(100);
    gsm.println((char)26);
    delay(100);
    gsm.println();
    delay(5000);
}