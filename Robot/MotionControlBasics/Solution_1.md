```cpp
#include <Arduino.h>

/*
* [0]--|||--[1]       motorpwmPin[4] motordirectionPin[4] (The numbers correspond to the index numbers of motorpwmPin[4] and motordirectionPin[4])
*  |         |          (counterclockwise)
*  |         |        
*  |         |        
*  |         |        
* [3]-------[2]
*/
// Constants
const static uint8_t pwm_min = 50; // Minimum PWM value
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction

// Function prototypes
void Motor_Init(void);
void Motor_Stop(void);
void Motor_Move(void);

void setup() {  
  Serial.begin(9600);  // Open serial port at 9600 bps
  Serial.println("Start Setup");
  Motor_Init(); ///Initialize the motors
  Motor_Move(); ///Move forward
  delay(1000);
  Motor_Stop(); ///Stop the motors
}

void Motor_Init(void) {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(motordirectionPin[i], OUTPUT);
    pinMode(motorpwmPin[i], OUTPUT);
  }
}

void Motor_Stop(void) {
  for (uint8_t i = 0; i < 4; i++) {
    analogWrite(motorpwmPin[i], 0); // Set speed to 0
  }
  Serial.println("Stop motors");
}

void Motor_Move(void) {
  for (uint8_t i = 0; i < 4; i++) {
    Serial.println("Motor " + String(i) + " moving");
    digitalWrite(motordirectionPin[i], HIGH); // Set direction to forward
    analogWrite(motorpwmPin[i], 125); // Set speed to 125
    delay(1000);
    analogWrite(motorpwmPin[i], 0); // Set speed to 0
  }
}

void loop() {}
```