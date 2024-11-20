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
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction

// Function prototypes
void Motor_Init(void);
void Motor_Stop(void);
void Motor_Forward(void);

void setup() {  
  // Open serial port at 9600 bps
  Serial.println("Start Setup");

  //Initialize the motors

  Motor_Stop(); ///Stop the motors
}

void Motor_Init(void) {
  for (uint8_t i = 0; i < 4; i++) {
    // Set the motorpwmPin to output
     // Set the motordirectionPin to output
  }
}

void Motor_Stop(void) {
  for (uint8_t i = 0; i < 4; i++) {
     // Set speed to 0
  }
  Serial.println("Stop motors");
}

void Motor_Move(void) {

}

void loop() {}