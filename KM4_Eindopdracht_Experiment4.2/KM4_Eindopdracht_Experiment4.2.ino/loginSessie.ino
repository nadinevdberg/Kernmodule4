ESP8266Client client;

 int result = client.connect("studenthome.hku.nl", 80);
  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(1000);
  } else {

    String loginRequest = " ";
    
    Serial.println("Send HTTP request...");
    client.println("GET "+ switchRequest + " HTTP/1.1\n"  //de spaties hier zijn heel belangrijk
                   "Host: studenthome.hku.nl\n"
                   "Connection: close\n");
    Serial.println("Response from server");
   
    String response;
    
    while (client.available()) {
      response += (char)client.read();
   
    Serial.println(response);
  }

  if (client.connected()) {
    client.stop();
  }
  }

