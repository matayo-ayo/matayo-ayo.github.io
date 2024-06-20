const int gasSensorPin = A0;
const int ledPin = 5;
const int threshold = 100;

void setup() {
  pinMode(gasSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(gasSensorPin);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  } else {
    digitalWrite(ledPin, LOW);
  }
}