#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "PC_Nadine"
#define NETWORK_PASSWORD ")6Z3q020"


int sensorPin = A3;
boolean ingelogt = false;

void setup() {
  Serial.begin(9600);
  setupESP8266();

} 

void loop() {
  // Setup sensor and check if it's working
  
  int reading = analogRead(sensorPin);
  Serial.print("Sensor value = ");
  Serial.println(reading);

//setup wifi shield
  ESP8266Client client; 
  int result = client.connect("studenthome.hku.nl",80); // maak verbinding met studenthome

if (result <= 0) { //als connectie mislukt
  Serial.println("Failed to connect to server.");
  delay(1000);
  
}else {
  
  //------------------------ INLOGSESSIE 
  if (ingelogt == false){
   
    String loginRequest = "/~nadine.vandenberg/kernmodule4/login.php?id=1&password=wachtwoord1"; //hier de juiste link invoeren om in te loggen
    Serial.println("Send HTTP request...");
    client.println("GET " + loginRequest + "HTTP/1.1\n"
                    "Host: studenthome.hku.nl\n"
                    "Connection: close\n");
    Serial.println("Response from server");
    String response;
    while (client.available()){
      response += (char)client.read();
    }// sluit whileloop
    Serial.println(response);
    ingelogt = true;
    
  }


  // nadat het inloggen gelukt is, kan ik data naar de database sturen 
  // en data uit de database opvragen in het volgende statement
  if (ingelogt == true){
    //voer hier de request uit die ervoor zorgt dat er data naar je arduino gestuurd wordt
    //of die ervoor zorgt dat er data uit je database gelezen wordt

    //zet de data van mijn sensor (reading) achter de URL zodat ik dit samengevoegd door kan sturen in mijn request
    String insertRequest = "/~nadine.vandenberg/kernmodule4/add_data.php?thing_id=3&temp=";
    insertRequest += reading; 

    Serial.println("Send HTTP request...");
    client.println("GET " + insertRequest + "HTTP/1.1\n"
                    "Host: studenthome.hku.nl\n"
                    "Connection: close\n");
    Serial.println("Response from server");
    String response;
    while (client.available()){
      response += (char)client.read();
    }// sluit whileloop
    Serial.println(response);
  
  }     //einde if ingelogt == true
 }     //afsluiting else result

  if (client.connected()) {
    client.stop();
  }

  delay(6000);
}       //afsluiting void loop

