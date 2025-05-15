#include <Arduino.h>
#include "FastLED.h"    
#include "hw_esp32s3cam_ctl.h"

//constants
const static uint8_t ledPin = 2;
const static uint8_t buzzerPin = 3;

// global variables
static CRGB rgbs[1];
HW_ESP32S3CAM hw_cam;
static uint8_t cam_buffer[COLOR_DETECTION_REG_COUNT];

// function prototypes
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  Serial.println("setup");
  FastLED.addLeds<WS2812, ledPin, RGB>(rgbs, 1);
  Rgb_Show(255,255,255);
  hw_cam.Init();
  pinMode(buzzerPin,OUTPUT);
  tone(buzzerPin, 1200);
  delay(100);
  noTone(buzzerPin);
}

void loop() {
  hw_cam.Colordetection_Data_Receive(ALL_COLOR_INDEX_REG, cam_buffer, sizeof(cam_buffer));
  delay(10);
  if(cam_buffer[0] == 0) Rgb_Show(0,10,0);      // Green for green detection
  else if(cam_buffer[3] == 3) Rgb_Show(0,0,10); // Blue for blue detection
  else if(cam_buffer[2] == 2) Rgb_Show(10,0,0); // Red for red detection
  else Rgb_Show(0,0,0); // Off for no detection
  delay(100);

}

void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue) {
  rgbs[0].r = rValue;
  rgbs[0].g = gValue;
  rgbs[0].b = bValue;
  FastLED.show();
}
