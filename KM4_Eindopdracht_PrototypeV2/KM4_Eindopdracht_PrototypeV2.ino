/* Script om data naar de database te sturen en data uit de database uit te lezen */

#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "PhoneNadine"
#define NETWORK_PASSWORD "793b}09F"

int sensorPin = A3;  //analoge pin temperatuurmeter
bool ingelogt = false;

void setup() {
  Serial.begin(9600);
  setupESP8266(true);
}



void loop() {
  String response;
  int reading = analogRead(sensorPin); //lees de sensorpin uit
  Serial.print("Sensorwaarde = ");
  Serial.println(reading);

  ESP8266Client client;

  int result = client.connect("studenthome.hku.nl", 80); //maak verbinding met de studenthome

  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else { //als verbinding lukt:


    /* Stap 1: log in met de arduino om een sessie te starten */

    if (ingelogt == false) { //als er nog niet ingelogd is
      Serial.println("loggin in");
      client.println("GET /~nadine.vandenberg/kernmodule4/login.php?id=1&password=wachtwoord1 HTTP/1.1\n"
                     "Host: studenthome.hku.nl\n"
                     "Connection: close\n");
      Serial.println("Response from server. Trying to login");

      while (client.available()) {
        Serial.write(client.read());
      }
      Serial.println("-----");

      String loginResult = getBody(response);
      if (loginResult != '0') {
        Serial.println("CONGRATS! You've succesfully logged in! ");
        Serial.println(loginResult);
        ingelogt = true;

      } else {
        Serial.println("Login failed");
      }
    }
    if (ingelogt == true) {
      /* verstuur data */
      String insertRequest = "/~nadine.vandenberg/kernmodule4/insertexperiment.php?thing_id=2&temp=";
      insertRequest += reading;  // vul de gemeten temperatuur in en voeg deze toe aan de request

      if (reading != 0) {
        Serial.println("Send HTTP insert request...");
        client.println("GET " + insertRequest + " HTTP/1.1\n" //de spaties hier zijn heel belangrijk
                       "Host: studenthome.hku.nl\n"
                       "Connection: close\n");

        Serial.println("Response from server");
        String insertResponse;
        while (client.available()) {
          insertResponse += (char)client.read();
        }
        Serial.println(insertResponse);
      }
    }
  }

  if (client.connected()) {
    client.stop();
  }

  /* Data uitlezen en vergelijken */


  int currentData;
  currentData = sendRequest("studenthome.hku.nl",
                            "/~nadine.vandenberg/kernmodule4/getrecentdata",
                            response);
  int recentData = getBody(response).toInt(); // alles wegknippen wat voor die blanco regel zit
  Serial.println("recent gemeten data = ");
  Serial.println(recentData);
Serial.println(response);


  int currentAvgData;
  currentAvgData = sendRequest("studenthome.hku.nl",
                               "/~nadine.vandenberg/kernmodule4/getavgdata",
                               response);
  int avgData = getBody(response).toInt(); // alles wegknippen wat voor die blanco regel zit
  Serial.println("gemiddelde van alle data = ");
  Serial.println(avgData);

  int difference = avgData - recentData;
  Serial.println("difference in data = ");
  Serial.println(difference);

  Serial.println(response);
  delay(4000);

}


String getBody(const String& response) {
  int bodyStart = response.indexOf("\r\n\r\n");
  int bodyEnd = response.indexOf('\n', bodyStart + 4);
  String result = response.substring(bodyStart + 4, bodyEnd);
  result.trim();
  
  return result;
}


