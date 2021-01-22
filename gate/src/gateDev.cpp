#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

char ssid[] = "LHome";     //  your network SSID (name)
char pass[] = "DougAndErikaWireless";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char gateUrl[]="http://dtipsstore.table.core.windows.net/gate(PartitionKey='gate',RowKey='state')?sv=2019-12-12&ss=t&srt=sco&sp=rwdlacu&se=2022-01-22T03:04:00Z&st=2021-01-20T19:04:00Z&spr=https,http&sig=CpEls%2FxLL5dYPLnbcnEnXBBMngsDlWcwLcfW6twdmwg%3D";

unsigned int count = 1;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(9600);
  Serial.println("Setup begin");
  WiFi.mode(WIFI_STA);  
  WiFiMulti.addAP(ssid, pass);

}

void printOut(String s){
  Serial.println(s);
}


bool getGateState(){
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    

    printOut("[HTTP] begin...\n");
    if (http.begin(client, gateUrl)) {  // HTTP

      http.addHeader  ( "Accept","application/json;odata=nometadata");
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
          return payload.endsWith("true}");
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  return false;
}

// the loop function runs over and over again forever
void loop() {
   bool shouldOpen = getGateState();
   printOut(String(shouldOpen));

   if(shouldOpen){
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  printOut("gate open");
}
else{ 
  //otherwise turn it off
   delay(1000);                      // Wait for a second
   digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
   printOut("gate closed");
}

  delay(5000);  
  printOut(String("end loop :') " + String(count++)));

}


