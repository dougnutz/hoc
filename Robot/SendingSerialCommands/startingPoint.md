```cpp
#include <Arduino.h>
#include "motors.h"
#include <FastLED.h>

/*
* [0]--|||--[1]       motorpwmPin[4] motordirectionPin[4] (The numbers correspond to the index numbers of motorpwmPin[4] and motordirectionPin[4])
*  |         |          (counterclockwise)
*  |         |        
*  |         |        
*  |         |        
* [3]-------[2]
*/
// Constants
const static uint8_t ledPin = 2;
const static uint8_t pwm_min = 50;
const static uint8_t motorpwmPin[4] =  { 11,9,6,10 };  ///pins for controlling the motor speed
const static uint8_t motordirectionPin[4] = { 13,8,7,12 };  ///pins for controlling the motor direction

// Variables
static CRGB rgbs[1];

// Function prototypes
void Motor_Init(void);
void Motor_Stop(void);
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);
void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift);
void RGB_Show(uint8_t red, uint8_t green, uint8_t blue);

void setup() {
  Serial.begin(9600);  // Open serial port at 9600 bps
  Serial.setTimeout(500);
  Serial.println("Mecanum wheel robot setup begin");

  FastLED.addLeds<WS2812, ledPin, RGB>(rgbs, 1);

  Motor_Init(); ///Initialize the motors
  Motor_Stop();

  // Cycle through LED colors: Red,  Blue, Green
  RGB_Show(255,0,0); // Red
  delay(500);
  RGB_Show(0,0,255); // Blue
  delay(500);
  RGB_Show(0,255,0); // Green
  delay(500);
 
  Serial.println("End Setup");
}

void RGB_Show(uint8_t red, uint8_t green, uint8_t blue) {
  rgbs[0].g = red;
  rgbs[0].r = green;
  rgbs[0].b = blue;
  FastLED.show();
}

void loop() {}
```
