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
  int result;

  int reading = analogRead(sensorPin); //lees de sensorpin uit
  Serial.print("Sensorwaarde = ");
  Serial.println(reading);

  ESP8266Client client;


  result = client.connect("studenthome.hku.nl", 80);  //maak verbinding met de studenthome

  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else { //als verbinding lukt:


    /* zorg dat ik alleen data stuur, als er ook echt iets gemeten is */

    if (reading != 0) {
      // maak mijn request string (dus link naar het PHP script + de sensorwaarde die hij moet versturen naar de database
      String insertRequest = "/~nadine.vandenberg/kernmodule4/insertexperiment.php?thing_id=2&temp=";
      insertRequest += reading;  // vul de gemeten temperatuur in en voeg deze toe aan de request


      Serial.println("Send HTTP insert request...");
      client.println("GET " + insertRequest + " HTTP/1.1\n" //de spaties hier zijn heel belangrijk
                     "Host: studenthome.hku.nl\n"
                     "Connection: close\n");
      Serial.println("Response from server. Data has been sent");
      String insertResponse;
      while (client.available()) {
        insertResponse += (char)client.read();
      }
      Serial.println(insertResponse);
    }
  }


  if (client.connected()) {
    client.stop();
  }


  /* Data uitlezen en vergelijken */
  int result2;
  result2 = sendRequest("studenthome.hku.nl", "/~nadine.vandenberg/kernmodule4/getrecentdata", response);
  String data = getBody(response);
  Serial.println(data);
  //int recentData  = data.toInt();
//  Serial.println("recent gemeten data = ");
//  Serial.println(recentData);


  delay(4000);
}


  /*  uitknipfunctie */

  String getBody(const String& response) {
    int bodyStart = response.indexOf("\r\n\r\n");
    int bodyEnd = response.indexOf('\n', bodyStart + 4);
    String result = response.substring(bodyStart + 4, bodyEnd);
    result.trim();
    return result;
  }


