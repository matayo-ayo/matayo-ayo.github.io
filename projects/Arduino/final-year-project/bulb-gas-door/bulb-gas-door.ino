#include <SoftwareSerial.h>
#include <Servo.h>

// Objects
SoftwareSerial mySerial(10, 11);  // RX, TX for GSM module
Servo windowControl;              // Mota ya dirisha
Servo doorMotor;                  // Mota ya mlango
Servo lockMotor;                  // Mota ya kitasa

// Variables
const String number = "+255620809207";  // Namba ya simu
const int gasPin = A0;                  // Pin ya mq4
const int gasLed = 6;                   // Digital pin for LED
const int gasLevel = 300;               // Gas detection threshold
const int relayPin = 5;                 // Pin ya relay

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Mota
  doorMotor.attach(8);
  lockMotor.attach(9);
  windowControl.attach(7);

  // Taa
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(gasLed, OUTPUT);

  // Gesi
  pinMode(gasPin, INPUT);

  // Initialize servos to safe positions
  doorMotor.write(90);
  lockMotor.write(90);
  windowControl.write(0);

  // GSM configuration
  mySerial.println("AT");
  delay(1000);
  mySerial.println("AT+CNMI=1,2,0,0,0\r");
  delay(1000);
}

void loop() {
  // Read gas level
  int gasAmount = analogRead(gasPin);
  if (gasAmount > gasLevel) {
    digitalWrite(gasLed, HIGH);  // Turn on the LED
    openWindow();                // Rotate the servo to open the window
    sendSMS();                   // Send SMS alert
  } else {
    digitalWrite(gasLed, LOW);  // Turn off the LED
    releaseWindow();            // Rotate the servo to close the window
  }

  if (mySerial.available()) {
    String sms = readSMS();
    String senderNumber = getSenderNumber(sms);
    String message = getMessage(sms);

    if (senderNumber == number) {
      if (message == "FUNGA MLANGO") {
        lockDoor();
      } else if (message == "FUGUA MLANGO") {
        unlockDoor();
      } else if (message == "WASHA TAA") {
        lightOn();
      } else if (message == "ZIMA TAA") {
        lightOff();
      }
    } else {
      Serial.println("TAARIFA:\n Namba " + senderNumber + " imetuma ujumbe " + message + " katika mfumo wa uangalizi nyumbani");
    }
  }
}

// Functions

// Kusoma message
String readSMS() {
  String sms = "";
  while (mySerial.available()) {
    char c = mySerial.read();
    sms += c;
    delay(10);
  }
  return sms;
}

// Kupata namba ya mtumaji
String getSenderNumber(String sms) {
  int start = sms.indexOf("+");
  int end = sms.indexOf(",", start);
  return sms.substring(start, end);
}

// Kupata message
String getMessage(String sms) {
  int start = sms.indexOf("\n");
  int end = sms.indexOf("\n", start + 1);
  if (end == -1) {
    end = sms.length();
  }
  String message = sms.substring(start + 1, end);
  message.trim();
  return message;
}

// Kuwasha taa
void lightOn() {
  Serial.println("Inawasha taa");
  digitalWrite(relayPin, HIGH);
  delay(500);
  Serial.println("TARIFA:\n Taa zimewashwa kikamilifu");
}

// Kuzima taa
void lightOff() {
  Serial.println("Inazima taa");
  digitalWrite(relayPin, LOW);
  delay(500);
  Serial.println("TARIFA:\n Taa zimezimwa kikamilifu");
}

// Taa ya hatari
void dangerLightOn() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void dangerLightOff() {
  digitalWrite(LED_BUILTIN, LOW);
}

// Kufungua dirisha
void openWindow() {
  for (int rotation = 0; rotation <= 180; rotation += 10) {
    windowControl.write(rotation);
    delay(1000);
  }
}

// Kufunga dirisha
void releaseWindow() {
  for (int rotation = 180; rotation >= 0; rotation -= 10) {
    windowControl.write(rotation);
    delay(1000);
  }
}

// Kufungua mlango
void unlockDoor() {
  Serial.println("TAARIFA:\n Mlango unafunguliwa");
  doorMotor.write(0);
  delay(1000);
  Serial.println("TAARIFA:\n Kitasa kinafunguliwa");
  lockMotor.write(0);
  delay(1000);
  Serial.println("TAARIFA:\n Mlango na kitasa vimefunguliwa");
}

// Kufunga mlango
void lockDoor() {
  Serial.println("TAARIFA:\n Mlango unafungwa");
  doorMotor.write(90);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.println("TAARIFA:\n Kitasa kinafungwa");
  lockMotor.write(90);
  delay(1000);
  Serial.println("TAARIFA:\n Mlango na kitasa vimefungwa");
  digitalWrite(LED_BUILTIN, LOW);
}

// Send SMS
void sendSMS() {
  mySerial.print("AT+CMGF=1\r");
  delay(1000);
  mySerial.print("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  mySerial.print("ALERT: Gas level high! Window opened.\r");
  delay(1000);
  mySerial.write(26);  // ASCII code for CTRL+Z to send the SMS
}