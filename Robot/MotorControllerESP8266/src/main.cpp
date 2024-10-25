#include <Arduino.h>

const int buttonPin = D2; // Pin where the button is connected
const int ledPin = D3;    // Pin where the LED is connected

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    Serial.println("Button pressed");
  } else {
    digitalWrite(ledPin, LOW);  // Turn off the LED
  }
}


 



