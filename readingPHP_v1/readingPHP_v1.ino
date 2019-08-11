#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

// Wifi 
#define NETWORK_NAME "Arduino_Hotspot"
#define NETWORK_PASSWORD "draadloos"


int LEDgreen = 11;
int LEDred = 10;
bool alarm;

void setup() {
  alarm = false;
  Serial.begin(9600);

  setupESP8266();

  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
 
    
}

void loop() {

     
// ---------- PHP uitlezen -----------
  ESP8266Client client;
  int result = client.connect("nadine.mobidapt.com",80);
   if (result <= 0) {
    Serial.println("Failed to connect to server part 2.");
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
     
if (response2.indexOf("alarm") > 0){ //functie in stringclass, zoekt naar positie van dit woord in de hele string.  -1 == not found
  
      digitalWrite(LEDgreen, LOW);
      digitalWrite(LEDred, HIGH);
      alarm = true;
      Serial.println("Alarm signaal afgegeven");
      
    } else {
      
      digitalWrite(LEDgreen, HIGH);
      digitalWrite(LEDred, LOW);
      alarm = false;
      Serial.println("Het gaat goed");
    }


  }

  if (client.connected()) {
      client.stop();
  }

  delay(4000);
}
