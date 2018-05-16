#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "PhoneNadine"
#define NETWORK_PASSWORD "793b}09F"


// we gaan sliders uitlezen. we gaan de waarde zoeken en die gebruiken
// we willen 3 getallen terug krijgen en daarmee een RGB lampje aansturen

void setup() {
  Serial.begin(9600);
  setupESP8266();

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);

// Met 255 zet je m uit
  analogWrite(6, 255);
  analogWrite(5, 255);
  analogWrite(3, 255); 
}

void loop() {
  String response;
  int result;

  result = sendRequest("km4.modidapt.com",
                       "/sliders?userid=nadine&sliderid=slider1", 
                       response);
  int slider1 = getBody(response).toInt(); // alles wegknippen wat voor die blanco regel zit (header)
  Serial.println("slider1= ");
  Serial.println(slider1);
  analogWrite(6, 255 - slider1/8); //omgekeerd met de - want 255 == volledig uit (afhankelijk van welk LEDje je hebt)
  Serial.println(response);
  delay(50);

   result = sendRequest("km4.modidapt.com",
                       "/sliders?userid=nadine&sliderid=slider2", 
                       response);
  int slider2 = getBody(response).toInt(); // alles wegknippen wat voor die blanco regel zit (header)
  Serial.println("slider2= ");
  Serial.println(slider2);
  analogWrite(6, 255 - slider2/8); //omgekeerd met de - want 255 == volledig uit (afhankelijk van welk LEDje je hebt)
  Serial.println(response);
  delay(50);

   result = sendRequest("km4.modidapt.com",
                       "/sliders?userid=nadine&sliderid=slider3", 
                       response);
  int slider3 = getBody(response).toInt(); // alles wegknippen wat voor die blanco regel zit (header)
  Serial.println("slider3= ");
  Serial.println(slider3);
  analogWrite(6, 255 - slider3/8); //omgekeerd met de - want 255 == volledig uit (afhankelijk van welk LEDje je hebt)
  Serial.println(response);
  delay(50);
}

String getBody(const String& response){
//waar begint de body?
int bodyStart = response.indexOf("\r\n\r\n"); // wat is de positie van \r\n\r\n
int bodyEnd = response.indexOf("\n",bodyStart + 4); // kan aangeven waar je wil beginnen met zoeken
return response.substring(bodyStart+4, bodyEnd); // uitknipfunctie

}

