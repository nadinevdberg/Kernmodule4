#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

  //#define NETWORK_NAME "PhoneNadine"
  #define NETWORK_NAME "LaptopNadine"
  #define NETWORK_PASSWORD "793b}09F"

  int reading;
 

void setup() {
  Serial.begin(9600);
  setupESP8266(true);
}

void loop() {
  reading = analogRead(A3);
  
  ESP8266Client client;
  
  int result = client.connect("km4.mobidapt.com", 80);
  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else {

String sliderRequest = "/sliders?userid=nadine&sliderid=slider1&value=";
  sliderRequest += reading;
  
    Serial.println("Send HTTP request...");
    client.println("GET " + sliderRequest + " HTTP/1.1\n"  //de spaties hier zijn heel belangrijk
                   "Host: km4.mobidapt.com\n"
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
