```cpp
#include <Arduino.h>
#include "Movement.h"

const static uint8_t keyPin = 3;  // Define the keyPin as 3

bool keyState;  //Detect button status

void setup() {
  Serial.println("Mecanum wheel robot setup begin");
  Serial.begin(9600);  // Open serial port at 9600 bps

  Movement::Motor_Init();  // Initialize the motors


  // move the robot forward
  Movement::Velocity_Controller(0, 100, 0, 0);
  delay(1000);

  Movement::Motor_Stop();

  pinMode(keyPin, INPUT);

  Serial.println("End Setup");
}

void loop() {
  keyState = analogRead(keyPin);  // Read the keyPin and assign the value to keyState
  if (keyState == 0) {  // If the key is pressed, the keyState is 0
    Movement::Velocity_Controller(0, 100, 0, 0);  // Move the robot forward
  } else {  // If the key is not pressed, the keyState is 1
    Movement::Motor_Stop();  // Stop the robot
  }
}
```



