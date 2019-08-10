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



void setup() {
  Serial.begin(9600);

  setupESP8266();

  pinMode(LEDred, OUTPUT);
  pinMode(LEDorange, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  
  // test bij opstarten of alle lampjes werken
  
//   digitalWrite(LEDgreen, HIGH);
//   digitalWrite(LEDorange, HIGH);
//   digitalWrite(LEDred, HIGH);


    
}

void loop() {

  
// ---------- DRUK SENSOR UITLEZEN -----------

  force = analogRead(pressurePin);      // lees pin uit
  force = map(force, 0, 1023, 0, 100);  // map resultaat naar 0-100
  
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
//String requestDifference = "/difference.php"; 
//result = sendRequest (host, requestDifference, response);
//        if (result == 1){
//          Serial.println("Pagina 'difference.php' bereikt");
//          String difference = getBody(response);
//      
//          if (response == ("! ! ! alarm ! ! !")){  // Is het stresslevel te hoog? Zet het rode lampje aan
//             digitalWrite(LEDgreen, LOW);
//             digitalWrite(LEDorange, LOW);
//             digitalWrite(LEDred, HIGH);
//          } else {                                // Is het stresslevel oke? Zet het groene lichtje aan
//             digitalWrite(LEDgreen, HIGH);
//             digitalWrite(LEDorange, LOW);
//             digitalWrite(LEDred, LOW);
//          }
//          
//        }


  delay(1500);
  
}  // einde loop functie


//-------------------------------------------- Functie voor het uitlezen van PHP pagina

//String getBody(const String & response) {
//  int bodyStart = response.indexOf(F("persoonlijk stressniveau")); //zoek begin body op (na 'persoonlijk stressniveau')
//  int bodyEnd = response.indexOf(F("<br>"), bodyStart + 14); //zoek einde body op, <br>
//  String body = response.substring(bodyStart + 14, bodyEnd); //substring deel van string beginnend bij teken (n) eindigend bij teken (x)
//  body.trim();
//  return body;
//}
