#include <Servo.h>
#include <SoftwareSerial.h>

const int gasSensorPin = A0;  // Analog pin for MQ2 gas sensor
const int ledPin = 8;         // Digital pin for LED
const int relayPin = 7;       // Digital pin for Relay
const int threshold = 300;    // Threshold value for gas detection
Servo myServo;                // Create a servo object

SoftwareSerial mySerial(10, 11);  // RX, TX for GSM module

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  myServo.attach(9);     // Attach the servo on pin 9 to the servo object
  myServo.write(0);      // Initial position of the servo
  Serial.begin(9600);    // Initialize serial communication
  mySerial.begin(9600);  // Initialize GSM module communication
  delay(1000);

  // Initialize GSM module
  mySerial.println("AT");  // Check communication
  delay(1000);
  mySerial.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);  // Read the gas sensor value
  Serial.print("Gas level: ");
  Serial.println(gasLevel);

  if (gasLevel > threshold) {
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    myServo.write(90);           // Rotate the servo to 90 degrees
    sendSMS();                   // Send SMS alert
  } else {
    digitalWrite(ledPin, LOW);  // Turn off the LED
    myServo.write(0);           // Rotate the servo back to 0 degrees
  }

  checkSMS();   // Check for incoming SMS to control the relay
  delay(1000);  // Wait for a second before the next reading
}

void sendSMS() {
  mySerial.println("AT+CMGF=1");  // Set SMS mode to text
  delay(1000);
  mySerial.println("AT+CMGS=\"+1234567890\"");  // Replace with your phone number
  delay(1000);
  mySerial.print("Gas leak detected!");  //
  delay(1000);
  mySerial.write(26);  // ASCII code for CTRL+Z to send the message
  delay(1000);
}

void checkSMS() {
  if (mySerial.available() > 0) {
    String message = mySerial.readString();
    Serial.println("Message received: " + message);
    if (message.indexOf("LIGHT ON") >= 0) {
      digitalWrite(relayPin, HIGH);
      Serial.println("Light turned ON");
    } else if (message.indexOf("LIGHT OFF") >= 0) {
      digitalWrite(relayPin, LOW);
      Serial.println("Light turned OFF");
    }
  }
}