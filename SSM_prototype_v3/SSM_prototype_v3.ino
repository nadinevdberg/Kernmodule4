// Code voor een eerste prototype voor een slimme stress meter
// Geschreven door Nadine van den Berg
// ©2019


#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

// Wifi 
#define NETWORK_NAME "Arduino_Hotspot"
#define NETWORK_PASSWORD "draadloos"

// gegevens van de arduino onderdelen
int pressurePin = A1;
int force = 0;
int LEDgreen = 11;
int LEDred = 10;



void setup() {
  Serial.begin(9600);

  setupESP8266();

  pinMode(LEDred, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  
 
}

void loop() {

  
// ---------- DRUK SENSOR UITLEZEN -----------
// Hier kijk ik of de gebruiker zijn/haar stresslevel meet. 
// Meet de force-sensor data? Stuur deze dan naar de database. 
// Gebruikt de gebruiker de druksensor niet? Doe dan niets. 

  force = analogRead(pressurePin);      // lees pin uit
  force = map(force, 0, 1023, 0, 100);  // map resultaat naar 0-100 (dit zodat ik geen uitschieters heb wanneer ik gebruik maak van een andere sensor i.p.v. een druksensor) 
  
  String host = "nadine.mobidapt.com";
  String request = "/senddata.php?thing_id=1&data=";
  
  if (force != 0){     // Is de druksensor gebruikt? Stuur data naar database
       
      request += force;
      
      String response;
      Serial.println("Send request...");
      int result = sendRequest (host, request, response);

      if (result < 0) {
        Serial.println(F("Failed to connect to server."));
      } else {
        Serial.println("Data verstuurd naar de database");
        Serial.println(response);
        
      }
  
   }
   else { // Is de sensor niet gebruikt? Laat mij dit weten a.u.b. 
    Serial.println (" Er word momenteel niks uitgelezen ");
   }
    
// ---------- PHP uitlezen -----------
// De volgende stap is het kijken of de meest recent gemeten data hoger is dan het gemiddelde van de stressmeter. 
// Het gemiddelde kijkt naar alle gebruikers. Dit doe ik voor het geval de gebruiker van het begin af aan al een te hoog stressniveau heeft.
// Het gemiddelde wordt berekend via de PHP pagina(s) m.g.v de database. 

  ESP8266Client client;
  int result = client.connect("nadine.mobidapt.com",80);
   if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else {
  
String requestDifference = "/difference.php"; 


    Serial.println("Send HTTP request...");
    client.println("GET "+ requestDifference + " HTTP/1.1\n"
                  "Host: nadine.mobidapt.com\n"
                   "Connection: close\n");

    Serial.println("Response from server");
    String response2;

      while (client.available()) {
      response2 += (char)client.read();
      }
      
     Serial.println(response2);
     
if (response2.indexOf("alarm") >0){ //functie in stringclass, zoekt naar positie van dit woord in de hele string.  -1 == not found
  
      digitalWrite(LEDgreen, LOW);
      digitalWrite(LEDred, HIGH);
      
    } else {
      
      digitalWrite(LEDgreen, HIGH);
      digitalWrite(LEDred, LOW);
      
    }
  }

  if (client.connected()) {
      client.stop();
  }

  delay(4000);

  
}  // einde loop functie
