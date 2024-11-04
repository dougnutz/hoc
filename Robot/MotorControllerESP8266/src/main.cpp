#include <Arduino.h>

const int in3Pin = D1;  // Pin for IN3 on L298N for motor B
const int in4Pin = D2; // Pin for IN4 on L298N for motor B
const int buttonPin1 = D3; // Pin where the first button is connected
const int buttonPin2 = D4; // Pin where the second button is connected
const int in1Pin = D6;  // Pin for IN1 on L298N for motor A
const int in2Pin = D7;  // Pin for IN2 on L298N for motor A


void setup() {

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  digitalWrite(in1Pin, LOW);     // Set IN1 low for motor A
  digitalWrite(in2Pin, LOW);     // Set IN2 low for motor A
  digitalWrite(in3Pin, LOW);     // Set IN3 low for motor B
  digitalWrite(in4Pin, LOW);     // Set IN4 low for motor B
  

  pinMode(buttonPin1, INPUT_PULLUP); // Set the first button pin as an input
  pinMode(buttonPin2, INPUT_PULLUP); // Set the second button pin as an input

  Serial.begin(9600);
  Serial.println("Setup complete");
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);

  // if (buttonState1 == LOW) {
  //   digitalWrite(in2Pin, HIGH);   
  //   Serial.println("Button 1 pressed, motor A running");
  // } else {
  //   digitalWrite(in2Pin, LOW);     
  //   Serial.println("Button 1 not pressed, motor A stopped");
  // }

  // if (buttonState2 == LOW) {
  //   digitalWrite(in4Pin, HIGH);    
    
  //   Serial.println("Button 2 pressed, motor B running");
  // } else {
  //   digitalWrite(in4Pin, LOW);    
  //   Serial.println("Button 2 not pressed, motor B stopped");
  // }

  // if button 1 is pressed run both motors forwrard for 2 seconds then run both motors in reverse for 2 seconds
  if (buttonState1 == LOW) {
    digitalWrite(in1Pin, HIGH);   
    digitalWrite(in2Pin, LOW);   
    digitalWrite(in3Pin, HIGH);   
    digitalWrite(in4Pin, LOW);   
    Serial.println("Button 1 pressed, both motors running forward");
    delay(2000);
    digitalWrite(in1Pin, LOW);   
    digitalWrite(in2Pin, HIGH);   
    digitalWrite(in3Pin, LOW);   
    digitalWrite(in4Pin, HIGH);   
    Serial.println("Button 1 pressed, both motors running reverse");
    delay(2000);
  } 
  
// if button 2 run both motors forward for 2 seconds then stop both motors 
// then turn motor1 in reverse for 2 seconds and motor 2 forward for 2 seconds
  if (buttonState2 == LOW) {
    // digitalWrite(in1Pin, HIGH);   
    // digitalWrite(in2Pin, LOW);   
    // digitalWrite(in3Pin, HIGH);   
    // digitalWrite(in4Pin, LOW);   
    // Serial.println("Button 2 pressed, both motors running forward");
    // delay(2000);
    // digitalWrite(in1Pin, LOW);   
    // digitalWrite(in2Pin, LOW);   
    // digitalWrite(in3Pin, LOW);   
    // digitalWrite(in4Pin, LOW);   
    // Serial.println("Button 2 pressed, both motors stopped");
    // delay(1000);
    digitalWrite(in1Pin, HIGH);   
    digitalWrite(in2Pin, LOW);   
    digitalWrite(in3Pin, LOW);   
    digitalWrite(in4Pin, HIGH);   
    Serial.println("Button 2 pressed, both motors running reverse");
    delay(1000);
  }

  digitalWrite(in1Pin, LOW);   
  digitalWrite(in2Pin, LOW);   
  digitalWrite(in3Pin, LOW);   
  digitalWrite(in4Pin, LOW);   
  Serial.println("Button 1 not pressed, both motors stopped");
  


  delay(100);
}
