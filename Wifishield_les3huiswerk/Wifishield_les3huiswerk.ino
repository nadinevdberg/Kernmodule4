#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

  //#define NETWORK_NAME "PhoneNadine"
  #define NETWORK_NAME "LaptopNadine"
  #define NETWORK_PASSWORD "793b}09F"

const int buttonPin = 2;
  const int ledPin1 = 13;
  boolean lighIsRed = true;
  int buttonState = 0;
void setup() {
  Serial.begin(9600);

  setupESP8266(true);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin1, OUTPUT);
}

void loop() {
 buttonState = digitalRead(buttonPin);
  ESP8266Client client;
 
  
  int result = client.connect("km4.mobidapt.com", 80);
  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else {

String lightRequest = "/lights?userid=nadine&lightid=light1&colour=";

if (buttonState == HIGH){
  lightRequest += "green";
}else {
  lightRequest += "red";
}

   
    Serial.println("Send HTTP request...");
    client.println("GET "+ lightRequest + " HTTP/1.1\n"  //de spaties hier zijn heel belangrijk
                   "Host: km4.mobidapt.com\n"
                   "Connection: close\n");

    Serial.println("Response from server");
    String response;
    while (client.available()) {
      response += (char)client.read();
    }
    Serial.println(response);

    if (response.indexOf("off") >0){ //fucntie in stringclass, zoekt naar positie van dit woord in de hele string.  -1 == not found
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }

  if (client.connected()) {
    client.stop();
  }

  delay(4000);

}
