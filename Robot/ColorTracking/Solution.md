# Solution: main.cpp

```cpp
#include <Arduino.h>
#include "FastLED.h"
#include "hw_esp32s3cam_ctl.h"

const static uint8_t ledPin = 2;
const static uint8_t buzzerPin = 3;
static uint16_t g_current_point = 0;
static uint16_t color_info[4] = { 0, 0, 0, 0};
static CRGB rgbs[1];
HW_ESP32S3CAM hw_cam;

static uint8_t cam_buffer[COLOR_DETECTION_REG_COUNT];
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  Serial.write("setup");
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
  Serial.print("cam_buffer[0]: ");
  Serial.println(cam_buffer[0]);
  Serial.print("cam_buffer[1]: ");
  Serial.println(cam_buffer[1]);
  Serial.print("cam_buffer[2]: ");
  Serial.println(cam_buffer[2]);
  Serial.print("cam_buffer[3]: ");
  Serial.println(cam_buffer[3]);
  if(cam_buffer[0] == 0) Rgb_Show(0,10,0);
  else if(cam_buffer[3] == 3) Rgb_Show(0,0,10);
  else if(cam_buffer[2] == 2) Rgb_Show(10,0,0);
  delay(100);
}

/**
 * @brief Set the color of the RGB LED
 * @param rValue Value Range: [0,255]
 * @param gValue Value Range: [0,255]
 * @param bValue Value Range: [0,255]
 * @retval None
 * @note (255,0,0) green; (0,255,0) red; (0,0,255) blue; (255,255,255) white
 */
void Rgb_Show(uint8_t rValue,uint8_t gValue,uint8_t bValue) {
  rgbs[0].r = rValue;
  rgbs[0].g = gValue;
  rgbs[0].b = bValue;
  FastLED.show();
}
```
