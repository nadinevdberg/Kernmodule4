// Deze code heb ik op 13-7-2019 voor het laatst getest. Test succesvol. Echter wel alleen wanneer de serial monitor open staat
#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

// instellingen voor internet
#define NETWORK_NAME "Arduino_Hotspot"
#define NETWORK_PASSWORD "draadloos"

// Maak alle variabelen aan
const int buttonPin = 2; 
// boolean lightIsRed = true;
int buttonState = 0;



void setup() {
  
 Serial.begin(9600);

 setupESP8266(true);

 pinMode(buttonPin, INPUT);

}

void loop() {

  String host = "km4.mobidapt.com";

  String request = "/lights.php?userid=edwin&lightid=light1&colour=";
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
      request += "green";
      Serial.println("huidige status button" + buttonState);
    }else {
      request += "red";
      Serial.println("huidige status button" + buttonState);
    }

  String response;
  Serial.println("Send request..."); 
  int result = sendRequest(host, request, response);
  if (result <0){
    Serial.println(F("Failed to connect to server..."));
  } else {
    Serial.println(response);
  }
  
 
  delay(500);
}
