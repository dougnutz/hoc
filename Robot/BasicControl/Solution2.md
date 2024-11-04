```cpp
#include <Arduino.h>
const int in1Pin = 8; // IN1 pin of the L298N motor driver uses digital pin 8 on the Arduino
const int in2Pin = 9; // IN2 pin of the L298N motor driver uses digital pin 9 on the Arduino
const int enaPin = 10; // Enable pin for motor A uses PWM to control the speed of the motor
const int buttonPin = 2;    // Pin for the button
int buttonState = 0;        // Variable for reading the button status

void setup() {
  Serial.begin(9600); // Initialize the serial port

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enaPin, OUTPUT); 
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.println("setup complete");
}

void loop() {
    buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 255); // Set motor speed to maximum
        Serial.println("Button pressed");
    } else {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, LOW);
        analogWrite(enaPin, 0); // Stop the motor
    }
    delay(100); // Short delay to prevent reading the button too quickly
}

```