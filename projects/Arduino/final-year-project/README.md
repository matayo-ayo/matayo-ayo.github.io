# Mfumo wa kiotomatiki wa usalama nyumbani
Hii ni kazi ya mradi (Project work) ya kumaliza elimu ya ngazi ya Stashahada (Diploma) katika chuo cha Fedha (IFM - Main campus)

---

## Kuhusu mfumo
Mradi huu una mlengo wa kuongeza usalama wa majumbani kwa kufanya na kuleta vitu vya kiotomatiki kwa kutumia vifaa mbalimbali vya kiumeme kwa njia za kiumbali

---

## Vifaa na maandalizi vilivyotumika
- Kompyuta
- Programu ya arduino
- Arduino Uno
- GSM SIM800C
- 2 Servo motors
- Jumper wires (Male to male (6) )
- Power supply for the servos

---

## Libraries zinazohitajika
- `SoftwareSerial`
- `Servo`

---

## Mpangiliio

1. ***maandalizi na uunganishaji wa vifaa:***
    - GSM SIM800C:
      - GSM RX kwenda Arduino UNO pin 2
      - GSM TX kwenda Arduino UNO pin 3
      - GND na VIN kwenda katika Arduino UNO DNG na VIN au 5V pins
    - Kuunganisha mota ya mlango:
      - Waya ya data (njano) kwenda Arduino UNO pin 8
      - Waya nyeusi kwenda katika Arduino UNO pin ya GND
      - Waya nyekundu kwenda Arduino UNO pin ya 5V
    - Kuunganisha mota ya kitasa:
      - Waya ya data (njano) kwenda Arduino UNO pin 9
      - Waya nyeusi kwenda katika Arduino UNO pin ya GND
      - Waya nyekundu kwenda Arduino UNO pin ya 5V

2. ***Maandalizi ya programu:***
    - Komputa
    - Programu ya arduino. Unaweza kuipata kupitia [Tovuti ya Arduino](https://www.arduino.cc/en/software)
    - Mfumo huu utahitaji `Libraries` za `SoftwareSerial` na `Servo` (Mara nyingi huwa zinakuja na IDE ya Arduino)

---

## Ufanyaji wa kazi
1. ***Muunganiko***
    - Pakua programu
    - Unganisha vifaa kwa uangalifu

2. ***Sehemu za programu***
   - Inasubiri ujumbe kutoka kwa muhusika
   - Inasoma ujumbe, Inachukua namba ya mtumiaji na kuhakiki namba
   - Inachakata ujumbe kama una maneno yanayotakiwa kufanyiwa kazi
     - "FUNGA MLANGO" Inatoa amri ya kufungwa kwa mlango 
     - "FUGUA MLANGO" Inatoa amri ya kufunguliwa kwa mlango
   - Inatuma ujumbe wa majibu ya hali ya mchakato

3. ***Functions:***
   - `readSMS()`: Inasoma ujumbe ulioingia
   - `getSenderNumber(String sms)`: Unasoma namba ya aliyetuma
   - `getMessage(String sms)`: Ichabue ujumbe husika
   - `lockDoor()`: Amri ya kufunga mlango
   - `unlockDoor()`: Amri ya kufungua mlango

---

## Sehemu za Faili ghafi
1. ***Sehemu kuu ya programu***
```bash
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  doorMotor.attach(8);
  lockMotor.attach(9);
}
```

2. ***Sehemu ya marudio ya program***
```bash
void loop() {
    if (mySerial.available()) {
        String sms = readSMS();
        Serial.println(sms);

        String senderNumber = getSenderNumber(sms); // Namba ya mtumaji
        String message = getMessage(sms); // Meseji ya mtumaji

        ...
    }
}
```

3. ***Usomaji wa Ujumbe kwa ujumla***
```bash
String readSMS() {
  String sms = "";
  while (mySerial.available()) {
    char c = mySerial.read();
    sms += c;
    delay(10);
  }
  return sms;
}
```

4. ***Kuchambua namba ya mtumaji***
```bash
 Kupata namba ya mtumaji
String getSenderNumber(String sms) {
  int start = sms.indexOf("+");
  int end = sms.indexOf(",", start);
  return sms.substring(start, end);
}
```

5. ***Kuchambua ujumbe wa mtumaji***
```bash
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
```

6. ***Amri ya kufunga mlango***
```bash
void lockDoor() {
  Serial.println("Notification:\n Door is locked");
  doorMotor.write(90);
  delay(1000);
  Serial.println("Notification:\n Bolt is engaged");
  lockMotor.write(90);
  delay(1000);
  Serial.println("Door and bolt are locked");
}
```

7. ***Amri ya kufungua mlango***
```bash
void unlockDoor() {
  Serial.println("Notification:\n Door is unlocked");
  doorMotor.write(0);
  delay(1000);
  Serial.println("Notification:\n Bolt is disengaged");
  lockMotor.write(0);
  delay(1000);
  Serial.println("Door and bolt are unlocked");
}
```

---

## Zingatio
- Hakikisha usambaaji wa umeme kwa vifaa kutokana na nguvu inayohitajika
- Rekebisha mikao ya mota kama itavyohitajika kwa mlango wako
- Iweke namba husika kuwa namba ya mawasiliano utakayotumia