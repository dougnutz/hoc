```cpp
#include <Arduino.h>

const int buttonPin = 2;    // Pin for the button
const int ledPin = 13;      // Pin for the LED
int buttonState = 0;        // Variable for reading the button status

void setup() {
  Serial.begin(115200); // Initialize the serial port

  pinMode(13, OUTPUT); // Set pin 13 as an output
  pinMode(ledPin, OUTPUT);  // Set the LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as an input with internal pull-up resistor

  Serial.println("setup complete");
}

void loop() {
    buttonState = digitalRead(buttonPin); // Read the state of the button

    if (buttonState == LOW) { // If the button is pressed
        digitalWrite(ledPin, HIGH); // Turn the LED on
    } else {
        digitalWrite(ledPin, LOW);  // Turn the LED off
    }

    delay(100); // Short delay to prevent reading the button too quickly
}
```
