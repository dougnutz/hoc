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
const static uint8_t pwm_min = 50;
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction

// Function prototypes
void Motor_Init(void);
void Motor_Stop(void);
 void Velocity_Controller(uint16_t angle, uint8_t velocity);
 void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);

void setup() {
  // Code to setup and to run once:
  Serial.begin(9600); // start serial port
  Serial.println("Start Setup");

  Motor_Init();  // initialize the motors
  Motor_Stop();  // stop the motors
  Serial.println("End Setup");
}

#pragma region MotorControl // pragma is a code organization tool that allows you to group code together

void Motor_Init(void){
  // loop through each motor and set the pins as outputs
  for(uint8_t i = 0; i < 4; i++){
    pinMode(motorpwmPin[i], OUTPUT); // set each motorpwmPin as an OUTPUT
    pinMode(motordirectionPin[i], OUTPUT); // set each motordirectionPin as an OUTPUT
  }
  Serial.println("Motors Initialized");
}

void Motor_Stop(void) {
  for (uint8_t i = 0; i < 4; i++) {
    analogWrite(motorpwmPin[i], 0); // Set speed to 0
  }
  Serial.println("Stop motors");
}

#pragma endregion
 

void Velocity_Controller(uint16_t angle, uint8_t velocity) {


}

void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3) {

}


void loop() {
  // put code here to run repeatedly:
}

