#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WebRead.h>



WebRead::WebRead(/* args */)
{
}

void WebRead::SetConnectionInfo(String ssid, String passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid.c_str(), passphrase.c_str());
   
}

String WebRead::GetData(String url)
{
   if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    Serial.println("[HTTP] begin...\n");
    if (http.begin(client, url)) {  // HTTP

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
          return payload;
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

    return "";
}


WebRead::~WebRead()
{
}

