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

void loop() {
  while (Serial.available()) {
    String cmd = Serial.readStringUntil('$');
    cmd.trim();
    Serial.print("Received command: ");
    Serial.println(cmd);
    /// Parse command: expected format X|Y|$
    int sepIndex = cmd.indexOf('|');
    if(sepIndex <0){
      Serial.print("Invalid command");
      Serial.println(cmd);
      continue;
    }
    char commandType = cmd.charAt(0);
    String arg1 = cmd.substring(sepIndex + 1);
    arg1.trim();
    switch (commandType) {
      case 'A': {
        arg1.trim();
        int color = arg1.toInt();
        if (color == 1) RGB_Show(255, 0, 0); // Red
        else if (color == 2) RGB_Show(0, 0, 255); // Blue
        else if (color == 3) RGB_Show(0, 255, 0); // Green
        else {
          RGB_Show(0, 0, 0); // Turn off LED
          Serial.println("Unknown color code");
        }
        break;
      }
      case 'B': {
        int commaIndex = arg1.indexOf(',');
        if (commaIndex < 0) {
          Serial.println("Invalid B command format. Use B|direction,speed|$");
          break;
        }
        String dirStr = arg1.substring(0, commaIndex);
        String speedStr = arg1.substring(commaIndex + 1);
        dirStr.trim(); 
        speedStr.trim();
        Velocity_Controller(dirStr.toInt(), speedStr.toInt(), 0, false);
        delay(1000);
        Motor_Stop();
        break;
      }
      // Add more cases here for other command types
      default:
        Serial.println("Unknown command type");
        break;
    }
    cmd = "";
  }
}