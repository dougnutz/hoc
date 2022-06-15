#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
const int red =2 ;
const int green =5 ;
char ssid[] = "LHome";     //  your network SSID (name)
char pass[] = "DougAndErikaWireless";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char gateUrl[]="http://hocfun.azurewebsites.net/api/echo?code=isfun&name=doug";

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

//returns true if it is open
bool getGateState(){
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    


    printOut("[HTTP] begin...\n");
    if (http.begin(client, gateUrl)) {  // HTTP

     // http.addHeader  ( "Accept","application/json;odata=nometadata");
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
        Serial.println(httpCode);
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
  //define a variable (bool) to hold the value of the getGateState()
bool boby = getGateState();
  //if it is is open turn on the green  hint define the green
if(boby){
//   analogWrite(green,500);
 //    analogWrite(red,0);
}
 //else turn on red
else{ 
///  analogWrite(red,500);
 // analogWrite(green,0);
}
  //wait 5 sec and check again 
delay(5000);
}


 




