#include <Arduino.h>
const int enAPin = D5;  // Pin for PWM signal to L298N
const int pwmValue = 128; // 50% of 255 for 8-bit PWM
const int buttonPin = D2; // Pin where the button is connected
const int in1Pin = D6;  // Pin for IN1 on L298N
const int in2Pin = D7;  // Pin for IN2 on L298N

void setup() {
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as an input

  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    analogWrite(enAPin, pwmValue); // Set PWM to 50%
    digitalWrite(in1Pin, HIGH);    // Set IN1 high
    digitalWrite(in2Pin, LOW);     // Set IN2 low
    Serial.println("Button pressed, motor running at 50% PWM");
  } else {
    analogWrite(enAPin, 0);        // Stop the motor
    Serial.println("Button not pressed, motor stopped");
  }
}




 



