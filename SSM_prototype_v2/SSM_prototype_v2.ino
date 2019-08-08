#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

// Wifi 
#define NETWORK_NAME "Arduino_Hotspot"
#define NETWORK_PASSWORD "draadloos"

// gegevens van de arduino onderdelen
int pressurePin = A0;
int force = 0;
int LEDgreen = 10;
int LEDorange = 11;
int LEDred = 12;

// variabelen voor uitlezen/versturen PHP
String response; 
String request;
int result; 
String host = "nadine.mobidapt.com";
bool loginCheck = false;
//-------------------------------------------- Uitlezen van PHP pagina

String getBody(const String & response) {
  int bodyStart = response.indexOf(F("its")); //zoek begin body op (na its)
  int bodyEnd = response.indexOf(F("<br>"), bodyStart + 14); //zoek einde body op, <br>
  String body = response.substring(bodyStart + 14, bodyEnd); //substring deel van string beginnend bij teken (n) eindigend bij teken (x)
  body.trim();
  return body;
}



void setup() {
  Serial.begin(9600);

  setupESP8266();

  pinMode(LEDred, OUTPUT);
  pinMode(LEDorange, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  
  // test bij opstarten of alle lampjes werken
  
   digitalWrite(LEDgreen, HIGH);
   digitalWrite(LEDorange, HIGH);
   digitalWrite(LEDred, HIGH);
    
}

void loop() {
// ---------- INLOG SESSIE -----------

if (loginCheck == false){        // Als er niet niet is ingelogd, doe dit dan eerst
  request = "/login.php?id=1&password=wachtwoord";  
  result = sendRequest(F(host, request, response);

  if (result == 1){ 
    String sessieID = getBody(response);

    if (sessieID == 0) { // als het inloggen niet is gelukt geeft de PHP pagina 0 terug
       loginCheck = false;
    }

    if (sessieID != 0) {  // inloggen gelukt? Dan mag je nu met de database communiceren
      loginCheck = true;
  
  


  
// ---------- DRUK SENSOR UITLEZEN -----------

  force = analogRead(pressurePin);      // lees pin uit
  force = map(force, 0, 1023, 0, 100);  // map resultaat naar 0-100
  
//  Serial.println("huidige druk is: ");
//  Serial.println(force);   

   if (force != 0){     // Is de druksensor gebruikt? Stuur data naar database
       
      Serial.println("Send request...");
      request = "/senddata.php/?thing_id=1&data=";
      request += force;
      result = sendRequest (F(host,request,response);

      // error message check
      if (result < 0) {
        Serial.println(F("Failed to connect to server."));
      } else {
        Serial.println(response);
      }
  
   }else { // Is de sensor niet gebruikt? Laat mij dit weten a.u.b. 
    Serial.println (F(" Er word momenteel niks uitgelezen ");
   }
    
// ---------- PHP uitlezen -----------
request = "" // hier moet ik OF het gemiddelde uitlezen OF de huidige meting OF het verschil tussen deze 2
result = sendRequest (F(host, request, response);
  

  } // einde sessie (nadat sessie inlog is gelukt) 

  } // einde result check (1) 

  } // einde check of er ingelogd is

  delay(1500);
  
}  // einde loop functie
