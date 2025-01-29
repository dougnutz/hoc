``` cpp
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
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);
void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift);


void setup() {
  Serial.println("Mecanum wheel robot setup begin");
  Serial.begin(9600);  // Open serial port at 9600 bps

  Motor_Init(); ///Initialize the motors

  Motor_Stop();
  Serial.println("End Setup");
}

/**
 * @brief Speed control function
 * @param angle   "angle" controls the robot's motion direction, with the front of the robot as 0 degrees and counterclockwise as the positive direction)
 *                range from 0 to 359)
 * @param velocity   "velocity" controls the robot's speed, with a value range of 0 to 100)
 * @param rot     "rot" controls the robot's self-rotation speed, with a value range of -100 to 100)
 *                If it is greater than 0, the robot has a counterclockwise self-rotation speed. If it is less than 0, the robot has a clockwise self-rotation speed)
 * @param drift   "drift" determines whether the robot enables drift. Value range: 0 or 1. If it is 0, drift is enabled; otherwise, it is disabled)
 * @retval None
 */
void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift) {

  int8_t velocities[4];
  angle += 90;
  float rad = angle * PI / 180;
  velocity /= sqrt(2);

  for (int i = 0; i < 4; i++) {
    float factor = (i % 2 == 0) ? -1 : 1;
    velocities[i] = (velocity * sin(rad) + factor * velocity * cos(rad));
  }

  Motors_Set(velocities[0], velocities[1], velocities[2], velocities[3]);

}

#pragma region Motor_Functions

 /* Motor initialization function */
void Motor_Init(void){
  for(uint8_t i = 0; i < 4; i++){
    pinMode(motordirectionPin[i], OUTPUT);
  }
  Velocity_Controller( 0, 0 , 0, 0);
} 


void Motor_Stop(void) {
  for (uint8_t i = 0; i < 4; i++) {
    digitalWrite(motordirectionPin[i], LOW); // Set direction to stop
    analogWrite(motorpwmPin[i], 0); // Set speed to 0
  }
}

/**
 * @brief PWM and wheel turning setting function
 * @param Motor_x   "Motor_x" is the control value for PWM and motor rotating. Calculated based on the kinematics analysis of mecanum wheels
 * @retval None
 */
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3) {
  int8_t pwm_set[4];
  int8_t motors[4] = { Motor_0, Motor_1, Motor_2, Motor_3};
  bool direction[4] = { 1, 0, 0, 1};///forward, left 1, right 0
  for(uint8_t i=0; i < 4; ++i) {
    direction[i] = motors[i] < 0 ? !direction[i] : direction[i];
      pwm_set[i] = motors[i] == 0 ? 0 : map(abs(motors[i]), 0, 100, pwm_min, 255);
      Serial.println(pwm_set[i]);
      digitalWrite(motordirectionPin[i], direction[i]);
      analogWrite(motorpwmPin[i], pwm_set[i]);
  }
}

#pragma endregion


  void loop() {}
  
  
```