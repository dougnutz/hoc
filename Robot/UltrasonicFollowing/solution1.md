```cpp
#include <Arduino.h>
#include "Movement.h"  //movement functionality
#include "Ultrasound.h"  //ultrasound functionality
#define STOP 0  
#define FORWARD 1
#define BACKWARD 2
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
  ultrasonic_distance();
  delay(100);  // Delay for 100ms
}


int Filter() {
  int i;
  int filter_sum = 0;
  filter_buf[FILTER_N] = ultrasound.GetDistance();///Read the ultrasonic ranging value
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = filter_buf[i + 1];///Shift all data to the left, and clear the low bit
    filter_sum += filter_buf[i];
  }
  return (int)(filter_sum / FILTER_N);
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