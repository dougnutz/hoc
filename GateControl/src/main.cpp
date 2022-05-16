#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>



ESP8266WiFiMulti WiFiMulti;
char ssid[] = "LHome";     //  your network SSID (name)
char pass[] = "DougAndErikaWireless";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char gateUrl[]="http://dtipsstore.table.core.windows.net/gate(PartitionKey='gate',RowKey='state')?sv=";

const int buttonPin = 4; /* GPIO4 (D2) for Push Button */
const int ledPin = 5; /* GPIO5 (D1) for LED */

int ledState = LOW; /* Variable to hold the current state of LED Pin. Initialized to LOW */
int buttonState = LOW; /* Variable to hold current state of Button Pin. Initialized to LOW */
int buttonValue; /* Variable to store state of the Button */
int lastButtonState = LOW; /* Variable to hold the previous state of the Button. Initialized to LOW */

void setup() {
  Serial.begin(9600);
  Serial.println("Setup begin");
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(buttonPin, INPUT); // initialize the button pin as a input
  
  WiFi.mode(WIFI_STA);  
  WiFiMulti.addAP(ssid, pass);
}
void printOut(String s){
  Serial.println(s);
}




void setGateState(bool doOpen){
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    

    printOut("[HTTP] begin...\n");
    if (http.begin(client, gateUrl)) {  // HTTP

      http.addHeader  ( "Accept","application/json;odata=nometadata");
      http.addHeader  ( "Content-Type", "application/json" );
      Serial.print("[HTTP] Put...\n");

      // start connection and send HTTP header
      String newPayload ;
      if(doOpen){
         newPayload= "{\"Open\":true}";
      }
      else{
          newPayload= "{\"Open\":false}";
      }
      
      Serial.print("sending payload \n");
      Serial.print(newPayload);
      int httpCode = http.PUT(newPayload);

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] Put... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String responsePayload = http.getString();
          Serial.println(responsePayload);
          return;
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
}

void updateState(int newButtonValue){
    if(newButtonValue == HIGH) /* If the button state is HIGH, toggle the LED state */
    {
      Serial.print("button high ");
      ledState = !ledState;
    }
    lastButtonState= newButtonValue;
    Serial.printf("Led %d \n",ledState);

    digitalWrite(ledPin, ledState); /* Set the new state of the LED */
    lastButtonState = newButtonValue; /* Store the present button state for next loop */ 

    bool newGateState = ledState == HIGH;
    setGateState(newGateState);
}


void loop() {
   // put your main code here, to run repeatedly:
  buttonValue = digitalRead(buttonPin); /* Read the state of the Button into the variable: buttonValue */
 
  /* Reset the debounce timer after button press */
  if(buttonValue != lastButtonState)
  {
     Serial.printf("Button Value %d ",buttonValue);
     updateState(buttonValue);
  }
  delay(50);
}
