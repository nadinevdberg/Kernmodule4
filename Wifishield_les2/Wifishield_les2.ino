#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

  #define NETWORK_NAME "PhoneNadine"
  #define NETWORK_PASSWORD "793b}09F"
  
void setup()
{
  setupESP8266();  //Roep de class aan (die je kan hergebruiken)  
  //setupESP8266(true);  //Force reconnect. dus als je wisselt van je telefoon hotspot naar  thuis internet dan moet er TRUE tussen de haakjes staan
}

void loop() {
  ESP8266Client client; // gaat over netwerk communiceren
  
  int result = client.connect("km4.mobidapt.com", 80); //leg verbinding met server
  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  
  } else {
    Serial.println(result);
    Serial.println("Send HTTP request...");
    client.println("GET /lights?userid=nadine&lightid=light3&colour=red HTTP/1.1\n"   //ook al maak je 3 strings, dit wordt automatisch achter elkaar geplakt. 
                   "Host: km4.mobidapt.com\n"
                   "Connection: close\n");

    Serial.println("Response from server");
    while (client.available()) {
      Serial.write(client.read()); //geef mij hetvolgende teken dat beschikbaar is (server heeft antwoord terug gestuurd, dat zijn tekens. dus in dit geval de tijd string)
    }
  
  if (client.connected()) {
    client.stop();
  }
  }
  delay(4000); //zonder deze delay, loopt ie vast 
}
