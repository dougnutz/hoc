#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

class WebRead
{
private:
    ESP8266WiFiMulti WiFiMulti;
    HTTPClient http;
public:
    WebRead();
    String GetData(String url);
    void SetConnectionInfo(String ssid, String passphrase);
    ~WebRead();
};