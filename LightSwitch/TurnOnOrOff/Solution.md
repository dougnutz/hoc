#Solution
This represents one possible solution
```
#include <Arduino.h>
#include <WebRead.h>


char ssid[] = "<network name>";     //  your network SSID (name)
char pass[] = "<network password>";  // your network password
char gateUrl[]="http://hocfun.azurewebsites.net/api/echo?code=<code>&name=hello";
int ledPin = 13; // D7 on NodeMCU
WebRead webRead;


void setup() {
   // setup serial communication
    Serial.begin(9600);
    Serial.println("Setup begin");
    // set pin mode for the led pin
    pinMode(ledPin, OUTPUT); 
    webRead.SetConnectionInfo(ssid, pass);
}

void loop() {
     Serial.print("Begin Loop ... ");
     
     // make a web request and get pin state
     String response = webRead.GetData(gateUrl);
     Serial.println(response);

     if(response == "on")
     {
        digitalWrite(ledPin, HIGH);
     }
     else if(response == "off")
     {
        digitalWrite(ledPin, LOW);
     }

    //wait 2 sec and check again 
    delay(2000);
}
```