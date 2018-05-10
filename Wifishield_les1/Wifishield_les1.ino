#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

  #define NETWORK_NAME "LaptopNadine"
  #define NETWORK_PASSWORD "793b}09F"

void setup() {
  setupESP8266();
  
  /*  dit deel was nodig vóór we de class van de ESP826Setup hebben toegevoegd
Serial.begin(9600);

  int succes = esp8266.begin();  //verbinding arduino en ESP chip opzetten
  if (succes){  //lukt dit niet, checken of alles wel goed zit (spanning, solderen, pinnen, alles checken)
    Serial.println("ESP8266 shield found! Hoera!");
  }else{
    Serial.println("Geen contact met ESP8266 shield :(");
    while(1);
  }

  int result = esp8266.connect(NETWORK_NAME, NETWORK_PASSWORD); //netwerkverbinding leggen met lokale wifi netwerk
  if (result < 0){ // check of het gelukt is, zo niet dan: 
    Serial.print("Error connecting: ");
    Serial.println(result);
    while(1);
  }

  IPAddress mijnIP = esp8266.localIP();  // lokale IP adres opvragen
  Serial.print("Mijn IP: ");
  Serial.println(mijnIP);
  */
}

void loop() {
  // put your main code here, to run repeatedly:

}
