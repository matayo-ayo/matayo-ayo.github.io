// Include necessary libraries
#include <SoftwareSerial.h>

// Define GSM module connections
#define GSM_TX_PIN 7
#define GSM_RX_PIN 8

// Create SoftwareSerial object to communicate with GSM
SoftwareSerial gsm(GSM_TX_PIN, GSM_RX_PIN);

void setup() {
    // Start serial communication with PC
    Serial.begin(9600);

    // Start communication with GSM module
    gsm.begin(9600);
    delay(3000);  // Give time to initialize
}

void loop() {
    sendMessage("Hello from GSM module!");

    // Wait for 2 seconds before sending the next message
    delay(2000);
}

void sendMessage(String message) {
    // AT command to send SMS message
    gsm.println("AT+CMGF=1");    // Set SMS mode to text
    delay(100);
    gsm.println("AT+CMGS=\"+255655606468\"\r");  // Replace with recipient's number
    delay(100);
    gsm.println(message);       // The SMS message
    delay(100);
    gsm.println((char)26);      // End AT command with Ctrl+Z
    delay(100);
    gsm.println();
    delay(5000);  // Give module time to send SMS
}