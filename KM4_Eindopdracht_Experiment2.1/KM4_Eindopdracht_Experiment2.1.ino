#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

//#define NETWORK_NAME "PhoneNadine"
  #define NETWORK_NAME "LaptopNadine"
  #define NETWORK_PASSWORD "793b}09F"


 int sensorPin = A3;  //analoge pin temperatuurmeter


void setup() {
  Serial.begin(9600);

  setupESP8266(true);

}

void loop() {
int reading = analogRead(sensorPin);
int voltage = reading * 5;
voltage /= 1024.0;
int temp = (voltage - 0.5) * 100;

  ESP8266Client client;
 
  
  int result = client.connect("studenthome.hku.nl", 80);
  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else {

// String lightRequest = "/lights?userid=nadine&lightid=light1&colour=";
String insertRequest = "/~nadine.vandenberg/kernmodule4/insertexperiment.php?thing_id=2&temp=";
insertRequest += temp;  // In een vorig experiment voegde ik de reading toe aan het einde van de hele insertrequest string (...&colour="+ reading), maar dat wilde niet werken en zo wilde het wel werken

   
    Serial.println("Send HTTP request...");
    client.println("GET "+ insertRequest + " HTTP/1.1\n"  //de spaties hier zijn heel belangrijk
                   "Host: studenthome.hku.nl\n"
                   "Connection: close\n");

    Serial.println("Response from server");
    String response;
    while (client.available()) {
      response += (char)client.read();
    }
    Serial.println(response);

  }

  if (client.connected()) {
    client.stop();
  }

  delay(4000);

}
