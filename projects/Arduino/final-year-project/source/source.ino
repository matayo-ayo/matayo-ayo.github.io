#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial mySerial(2, 3);
Servo doorMotor;
Servo lockMotor;

const String number = "+255620809207";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  doorMotor.attach(8);
  lockMotor.attach(9);
}

void loop() {
  if (mySerial.available()) {
    String sms = readSMS();
    Serial.println(sms);

    // Kupata taarifa za message
    String senderNumber = getSenderNumber(sms);
    String message = getMessage(sms);

    // Kutuma message
    if (senderNumber == number) {
      if (message == "FUNGA MLANGO") {
        lockDoor();
      } else if (message == "FUGUA MLANGO") {
        unlockDoor();
      }
    } else {
      Serial.println("TAARIFA:\n Namba " + senderNumber + " imetua ujumbe " + message + " katika mfumo wa uangalizi nyumbani");
    }
  }
}


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
  int end = sms.indexOf("\n", start);
  if (end == -1) {
    end = sms.length();
  }
  String message = sms.substring(start + 1, end);
  message.trim();
  return message;
}


// Kufunga mlango
void lockDoor() {
  Serial.println("TAARIFA:\n Mlango unafungwa");
  doorMotor.write(90);
  delay(1000);
  Serial.println("TAARIFA:\n Kitasa kinafungwa");
  lockMotor.write(90);
  delay(1000);
  Serial.println("Mlango na kitasa vimefungwa");
}


// Kufungua mlango
void unlockDoor() {
  Serial.println("TAARIFA:\n Mlango unafunguliwa");
  doorMotor.write(0);
  delay(1000);
  Serial.println("TAARIFA:\n Kitasa kinafunguliwa");
  lockMotor.write(0);
  delay(1000);
  Serial.println("Mlango na kitasa vimefunguliwa");
}