```cpp
#include <Arduino.h>
#include "Movement.h"  //movement functionality
#include "Ultrasound.h"  //ultrasound functionality
#define FILTER_N 3 // Filter size

// Constants
const static uint8_t pwm_min = 50;
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction



int Filter_Value;
int filter_buf[FILTER_N + 1];
Ultrasound ultrasound; 
uint16_t dis;
// Ultrasound prototypes
int Filter(void);
int ultrasonic_distance(void);



void setup() {

  Movement::Motor_Init();  // Initialize the motors
  Movement::Motor_Stop();  // Stop the motors
}

void loop() {
  dis =  ultrasonic_distance();
  switch (dis) {
    case 700 ... UINT16_MAX: // Using UINT16_MAX as the upper bound for distance
      Movement::Velocity_Controller(0, 0, 0, 0);
      break;
    case 300 ... 699:
      Movement::Velocity_Controller(0, 50, 0, 0);
      break;
    case 200 ... 299:
      Movement::Velocity_Controller(0, 0, 0, 0);
      break;
    default: // dis < 200
      Movement::Velocity_Controller(180, 50, 0, 0);
      break;
  }

  delay(100);
}


int Filter() {
  int filter_sum = 0;

  // Shift all data to the left
  for (int i = 0; i < FILTER_N - 1; i++) {
    filter_buf[i] = filter_buf[i + 1];
    filter_sum += filter_buf[i];
  }

  // Add the new value to the last position
  filter_buf[FILTER_N - 1] = ultrasound.GetDistance();
  filter_sum += filter_buf[FILTER_N - 1];

  return filter_sum / FILTER_N;
}


int ultrasonic_distance(){
  uint8_t s;
  uint16_t distance = Filter();///Get the output value of the filter

  if (distance > 0 && distance <= 80){
    ultrasound.Breathing(1, 0, 0, 1, 0, 0);///Red breathing light mode, in 0.1s
  }
  else if (distance > 80 && distance <= 180){
    s = map(distance,80,180,0,255);
    ultrasound.Color((255-s), 0, 0, (255-s), 0, 0);///Red gradient
  }

  else if (distance > 180 && distance <= 320){
    s = map(distance,180,320,0,255);
    ultrasound.Color(0, 0, s, 0, 0, s);///Blue gradient
  }

  else if (distance > 320 && distance <= 500){
    s = map(distance,320,500,0,255);
    ultrasound.Color(0, s, 255-s, 0, s, 255-s);///Green gradient
  }
  else {
      ultrasound.Color(0, 255, 0, 0, 255, 0);///Green
  }
  return distance;  
}
```