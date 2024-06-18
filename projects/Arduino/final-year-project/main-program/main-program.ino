#include <SoftwareSerial.h>
#include <Servo.h>

// Objects
SoftwareSerial mySerial(10, 11);
Servo windowMotor;
Servo doorMotor;
Servo lockMotor;

// Variables
const String number = "+255620809207";
const int relayPin = 5;
const int gasLedPin = 6;
const int threshold = 300;
const int gasSensorPin = A0;
bool gasFlag = false;
bool gasLeakMsg = false;
bool gasNormalMsg = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(gasLedPin, OUTPUT);
  windowMotor.attach(7);
  pinMode(LED_BUILTIN, OUTPUT);

  mySerial.println("AT");
  mySerial.println("AT+CNMI=1,2,0,0,0\r");

  digitalWrite(gasLedPin, LOW);
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);

  if (gasLevel >= threshold && !gasFlag) {
    gasFlag = true;
    gasLeakMsg = false;
    if (!gasLeakMsg) {
      sendMessage("TAARIFA:\n Kiwango cha gesi kinakadiriwa kufikia " + String(gasLevel) + ". Dirisha linafunguliwa kwa usalama");
      gasLeakMsg = true;
    }
    for (int x = 0; x <= 180; x += 10) {
      windowMotor.write(x);
      delay(500);
    }
    digitalWrite(gasLedPin, HIGH);
    delay(500);
    digitalWrite(gasLedPin, LOW);
    delay(500);
  } else if (gasLevel < threshold && gasFlag) {
    gasFlag = false;
    gasNormalMsg = false;
    if (!gasNormalMsg) {
      sendMessage("TAARIFA:\n Kiwango cha gesi kimerudi kuwa sawa. Dirisha linaweza kufungwa kwa usalama");
      gasNormalMsg = true;
    }
    windowMotor.write(0);
    delay(500);
  }

  if (mySerial.available()) {
    String sms = readSMS();
    String senderNumber = getSenderNumber(sms);
    String message = getMessage(sms);

    if (senderNumber == number) {
      if (message == "FUNGA MLANGO") {
        lockDoor();
      } else if (message == "FUNGUA MLANGO") {
        unlockDoor();
      } else if (message == "WASHA TAA") {
        lightOn();
      } else if (message == "ZIMA TAA") {
        lightOff();
      }
    } else {
      sendMessage("TAARIFA:\n Namba " + String(senderNumber) + " imetuma ujumbe " + String(message) + " katika mfumo wa uangalizi nyumbani");
    }
  }
}

// Lock door
void lockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  doorMotor.write(180);
  delay(1000);
  lockMotor.write(90);
  sendMessage("TAARIFA:\n Mlango umefungwa kikamilifu");
  digitalWrite(LED_BUILTIN, LOW);
}

// Unlock door
void unlockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  doorMotor.write(0);
  delay(1000);
  lockMotor.write(0);
  sendMessage("TAARIFA:\n Mlango umefunguliwa kikamilifu");
  digitalWrite(LED_BUILTIN, LOW);
}

// Light on
void lightOn() {
  Serial.println("Inawasha taa");
  digitalWrite(relayPin, HIGH);
  delay(500);
  Serial.println("TARIFA:\n Taa zimewashwa kikamilifu");
}

// Light off
void lightOff() {
  Serial.println("Inazima taa");
  digitalWrite(relayPin, LOW);
  delay(500);
  Serial.println("TARIFA:\n Taa zimezimwa kikamilifu");
}

// Get full message
String readSMS() {
  String sms = "";
  while (mySerial.available()) {
    char c = mySerial.read();
    sms += c;
    delay(10);
  }
  return sms;
}

// Get sender number
String getSenderNumber(String sms) {
  int start = sms.indexOf("+");
  int end = sms.indexOf(",", start);
  return sms.substring(start, end);
}

// Get message body
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

// Send message
void sendMessage(String messageBody) {
  mySerial.print("AT+CMGF=1\r");
  delay(1000);
  mySerial.print("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  mySerial.print(messageBody);
  delay(1000);
  mySerial.write(26);
}