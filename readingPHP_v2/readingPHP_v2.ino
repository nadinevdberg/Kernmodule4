#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

// Wifi 
#define NETWORK_NAME "Arduino_Hotspot"
#define NETWORK_PASSWORD "draadloos"


int LEDgreen = 11;
int LEDred = 10;
bool alarm;
String host = "nadine.mobidapt.com";
  
void setup() {
  alarm = false;
  Serial.begin(9600);

  setupESP8266();

  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDred, OUTPUT);
  
// Test om te zien of de LED lampjes het nog doen
  digitalWrite(LEDgreen, HIGH);
  digitalWrite(LEDred, HIGH);
 
    
}

void loop() {

     
// ---------- PHP uitlezen -----------
    

    String requestDifference = "/difference.php"; 

    String response2;

    int result = sendRequest(host, requestDifference, response2);

    if (result < 0) {
    Serial.println(F("Failed to connect to server -- PHP uitlezen."));
  } else {
    Serial.println(response2);

    
        // zoek het woord 'alarm'
 if (response2.indexOf("alarm") >= 0) {
    digitalWrite(LEDgreen, LOW);
    digitalWrite(LEDred, HIGH);
  } else { 
    digitalWrite(LEDgreen, HIGH);
    digitalWrite(LEDred, LOW);
  }
  }



  delay(4000);
}
