#include <SoftwareSerial.h>

SoftwareSerial SIM800(10, 11); // RX, TX for SIM800

const int relayPin = 7; // Pin connected to the relay module
String incomingMessage = ""; // To store incoming SMS

void setup() {
  pinMode(relayPin, OUTPUT); // Set relay pin as output
  digitalWrite(relayPin, LOW); // Initially turn off the relay
  Serial.begin(9600); // Begin serial communication at 9600 baud rate
  SIM800.begin(9600); // Begin serial communication with GSM module

  // Initialize the GSM module
  SIM800.print("AT+CMGF=1\r"); // Set SMS mode to text
  delay(1000);
  SIM800.print("AT+CNMI=1,2,0,0,0\r"); // Configure module to send SMS data to serial out
  delay(1000);
}

void loop() {
  if (SIM800.available() > 0) {
    char c = SIM800.read();
    incomingMessage += c;

    // Check if the message is complete (ends with \n)
    if (c == '\n') {
      Serial.print("Message received: ");
      Serial.println(incomingMessage);

      if (incomingMessage.indexOf("WASHA TAA") != -1) {
        digitalWrite(relayPin, HIGH); // Turn on the relay (and bulb)
        Serial.println("Bulb is ON");
      } else if (incomingMessage.indexOf("ZIMA TAA") != -1) {
        digitalWrite(relayPin, LOW); // Turn off the relay (and bulb)
        Serial.println("Bulb is OFF");
      }
      incomingMessage = ""; // Clear the message after processing
    }
  }
}