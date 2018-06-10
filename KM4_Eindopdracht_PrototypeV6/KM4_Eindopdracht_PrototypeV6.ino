/*Prototype V5 -- Inlog sessie verwijderd om ruimte te besparen (het was toch maar voor de show), en om in eerste instantie maar met 1 cliënt te werken
  In plaats van 2 pagina's uitlezen, begin ik met het uitlezen van 1 pagina
  Uiteindelijk werkt ook dit niet want mijn variabele blijft leeg, in plaats van dat hij de data laat zien dei die van de pagina zou moeten halen*/

#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "PhoneNadine"
#define NETWORK_PASSWORD "793b}09F"

#define HOST "studenthome.hku.nl"

int sensorPin = A3;
int ledPin = 13;
int buzzer = 9;

void setup() {

  Serial.begin(9600);
  setupESP8266();

  pinMode(ledPin, OUTPUT);
  pinMode (buzzer, OUTPUT);
}



void loop() {
  String response;

  /* Data uitlezen en vergelijken */
  int result2;
  result2 = sendRequest("studenthome.hku.nl", "/~nadine.vandenberg/kernmodule4/getrecentdata.php", response);
  Serial.println("response is:");
  Serial.println(response);
  


  delay(4000);
}


  /*  uitknipfunctie */

  String getBody(const String& response) {
    int bodyStart = response.indexOf("\r\n\r\n");
    int bodyEnd = response.indexOf('\n', bodyStart );
    String result = response.substring(bodyStart, bodyEnd);
    result.trim();
    return result;
  }


