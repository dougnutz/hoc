#include <Arduino.h>
#include <Arduino.h>
// #include "SSD1306Wire.h"  

char ssid[] = "SSID";     //  your network SSID (name)
char pass[] = "<wifi password>";  // your network password
char gateUrl[]="http://hocfun.azurewebsites.net/api/echo?code=<code>&name=hello";

void setup() {
    Serial.begin(9600);
    Serial.println("Setup begin");
}

void loop() {
     Serial.print("Begin Loop ... ");


    //wait 5 sec and check again 
    delay(5000);
}