#include <Servo.h>

// Objects
Servo windowMotor;
Servo doorMotor;
Servo lockMotor;

// Variables
const String number = "+255620809207";
const int relayPin = 6;
const int gasLedPin = 5;
const int threshold = 100;
const int gasSensorPin = A0;
// Checkers
bool gasFlag = false;
bool gasLeakMsg = false;
bool gasNormalMsg = false;
bool doorStatus = false;
bool handleStatus = false;
bool lightStatus = false;
bool windowStatus = false;

void setup() {
  Serial.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(gasLedPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  lockMotor.attach(2);
  doorMotor.attach(3);
  windowMotor.attach(4);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CNMI=1,2,0,0,0\r");
}

void loop() {
  int gasLevel = analogRead(gasSensorPin);

  if (gasLevel >= threshold && !windowStatus && !gasFlag) {
    gasFlag = true;

    digitalWrite(gasLedPin, HIGH);

    if (!gasLeakMsg) {
      sendMessage("TAARIFA:\n Kiwango cha gesi kinakadiriwa kufikia " + String(gasLevel) + ". Dirisha linafunguliwa kwa usalama");
      gasLeakMsg = true;
      gasNormalMsg = false;
    }
    openWindow();
    windowStatus = true;
  } else if (gasLevel < threshold && windowStatus && gasFlag) {
    gasFlag = false;
    if (!gasNormalMsg) {
      sendMessage("TAARIFA:\n Kiwango cha gesi kimerudi kuwa sawa. Dirisha linaweza kufungwa kwa usalama");
      gasLeakMsg = false;
      gasNormalMsg = true;
    }
    digitalWrite(gasLedPin, LOW);
    delay(5000);
    closeWindow();
    windowStatus = false;
  }

  if (Serial.available()) {
    String sms = readSMS();
    String senderNumber = getSenderNumber(sms);
    String message = getMessage(sms);

    if (senderNumber == number) {
      if (message == "FUNGA MLANGO" && !doorStatus) {
        lockDoor();
        doorStatus = true;
        handleStatus = true;
      } else if (message == "FUNGUA MLANGO" && doorStatus) {
        unlockDoor();
        doorStatus = false;
        handleStatus = false;
      } else if (message == "WASHA TAA" && !lightStatus) {
        lightOn();
        lightStatus = true;
      } else if (message == "ZIMA TAA" && lightStatus) {
        lightOff();
        lightStatus = false;
      }
    } else {
      sendMessage("TAARIFA:\n Namba " + String(senderNumber) + " imetuma ujumbe " + String(message) + " katika mfumo wa uangalizi nyumbani");
    }
  }
}

// Lock door
void lockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(gasLedPin, HIGH);
  doorMotor.write(180);
  delay(1000);
  lockMotor.write(0);
  sendMessage("TAARIFA:\n Mlango umefungwa kikamilifu");
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(gasLedPin, LOW);
}

// Unlock door
void unlockDoor() {
  digitalWrite(LED_BUILTIN, HIGH);
  doorMotor.write(0);
  delay(1000);
  lockMotor.write(90);
  sendMessage("TAARIFA:\n Mlango umefunguliwa kikamilifu");
  digitalWrite(LED_BUILTIN, LOW);
}

// Open window
void openWindow() {
  for (int x = 0; x <= 180; x += 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowMotor.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

// Close window
void closeWindow() {
  for (int x = 180; x >= 0; x -= 10) {
    digitalWrite(LED_BUILTIN, HIGH);
    windowMotor.write(x);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
}

// Light on
void lightOn() {
  sendMessage("Inawasha taa");
  digitalWrite(relayPin, HIGH);
  delay(500);
  sendMessage("TAARIFA:\n Taa zimewashwa kikamilifu");
}

// Light off
void lightOff() {
  sendMessage("Inazima taa");
  digitalWrite(relayPin, LOW);
  delay(500);
  sendMessage("TAARIFA:\n Taa zimezimwa kikamilifu");
}

// Get full message
String readSMS() {
  String sms = "";
  while (Serial.available()) {
    char c = Serial.read();
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
  Serial.print("AT+CMGF=1\r");
  delay(1000);
  Serial.print("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  Serial.print(messageBody);
  delay(1000);
  Serial.write(26);
}