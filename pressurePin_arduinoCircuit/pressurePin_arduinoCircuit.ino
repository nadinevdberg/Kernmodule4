
int pressurePin = A0;
int force;
int LEDred = 12;
int LEDorange = 11;
int LEDgreen = 10;

void setup() {
Serial.begin(9600);
pinMode(LEDred, OUTPUT);
pinMode(LEDorange, OUTPUT);
pinMode(LEDgreen, OUTPUT);
}
void loop() {
  force = analogRead(pressurePin);
  Serial.println(force);

if (force > 50 && force < 334){
 digitalWrite(LEDgreen, HIGH);
 digitalWrite(LEDorange, LOW);
 digitalWrite(LEDred, LOW);
}
else if (force > 334 && force < 666){
  digitalWrite(LEDgreen, LOW);
 digitalWrite(LEDorange, HIGH);
 digitalWrite(LEDred, LOW);
}
else if (force > 666 && force < 1000){
  digitalWrite(LEDgreen, LOW);
 digitalWrite(LEDorange, LOW);
 digitalWrite(LEDred, HIGH);
}
else {
 digitalWrite(LEDgreen, LOW);
 digitalWrite(LEDorange, LOW);
 digitalWrite(LEDred, LOW);
  
}


delay(500);
}
