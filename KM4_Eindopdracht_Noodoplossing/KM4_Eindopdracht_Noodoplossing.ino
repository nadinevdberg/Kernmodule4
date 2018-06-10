int sensorPin = A3;
int ledPin = 13;
int buzzer = 9;
int reading;
int gemiddeldStressNiveau = 500;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {

  reading = analogRead(A3);
  Serial.println(reading);

  if (reading >= gemiddeldStressNiveau) {
    digitalWrite(ledPin, HIGH);
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 900);
    delay(100);
    noTone(buzzer);
    delay(100);
  } if (reading != 0 && reading < gemiddeldStressNiveau) {
    digitalWrite(ledPin, LOW);
    tone(buzzer, 800);
    delay(100);
    tone(buzzer, 1000);
    delay(100);
    noTone(buzzer);
  }  else {
    digitalWrite(ledPin, LOW);

  }
  delay(4000);
}
