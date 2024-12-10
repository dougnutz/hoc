```c++
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



  Motor_Stop();
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
 
 /**
 * @brief Robot motion control function
 * @param angle   "angle" controls the robot's motion direction, with the front of the robot as 0 degrees and counterclockwise as the positive direction  0~359(range from 0 to 359)
 * @param velocity   "velocity" controls the robot's speed, with a value range of 0 to 100
 * @retval None
 */
void Velocity_Controller(uint16_t angle, uint8_t velocity) {

  int8_t velocities[4];
  angle += 90;
  float rad = angle * PI / 180;
  velocity /= sqrt(2);

  for (int i = 0; i < 4; i++) {
    float factor = (i % 2 == 0) ? -1 : 1;
    velocities[i] = velocity * (sin(rad) + factor * cos(rad));
  }

  Motors_Set(velocities[0], velocities[1], velocities[2], velocities[3]);

}


/**
 * @brief PWM and wheel turning setting function
 * @param Motor_x   "Motor_x" is the control value for PWM and motor rotating. Calculated based on the kinematics analysis of mecanum wheels
 * @retval None
 */
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3) {
  
}


void loop() {
  // put code here to run repeatedly:
}


```