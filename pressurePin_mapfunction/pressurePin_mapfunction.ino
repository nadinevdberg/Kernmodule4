
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
  force = map(force, 0, 1000, 0, 100);
  Serial.println("huidige druk is:");  
  Serial.println(force);  

if (force > 0 && force < 33){
 digitalWrite(LEDgreen, HIGH);
 digitalWrite(LEDorange, LOW);
 digitalWrite(LEDred, LOW);
}
else if (force > 33 && force < 66){
  digitalWrite(LEDgreen, LOW);
 digitalWrite(LEDorange, HIGH);
 digitalWrite(LEDred, LOW);
}
else if (force > 66 && force < 100){
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
