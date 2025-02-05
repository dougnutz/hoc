#include "Helper.h"
#include <Wire.h>
#include "FastLED.h"

#define LINE_FOLLOWER_I2C_ADDR 0x78

const static uint8_t ledPin = 2; // Define the ledPin as 2

static CRGB rgbs[1];

void Helper::Init() {
    FastLED.addLeds<WS2812, ledPin, GRB>(rgbs, 1);
    Wire.begin();
}

bool Helper::WriteBytes(uint8_t data) {
    Wire.beginTransmission(LINE_FOLLOWER_I2C_ADDR); //Select address to start transmission
    Wire.write(data); //Send data
    if (Wire.endTransmission() != 0) {
        // Serial.println("false");  //fail to send
        return false;
    }
    // Serial.println("true");   //send successfully
    return true;
}

bool Helper::ReadBytes(uint8_t data, uint8_t &val) {
    if (!WriteBytes(data)) { //Send read/write signal to line follower
    return false;
    }
    Wire.requestFrom(LINE_FOLLOWER_I2C_ADDR, 1); //the response signal of the line follower is received
    while (Wire.available()) {                   //start to read data
        val = Wire.read();
    }
    return true;
}

/**
 * @brief Set the color of RGB LED
 * @param rValue;gValue;bValue;
 * @arg //Three input parameter value: 0 to 255
 * @retval None
 * @note (255,0,0)red; (0,255,0)green; (0,0,255)blue; (255,255,255)white)
 */
void Helper::Rgb_Show(uint8_t rValue, uint8_t gValue, uint8_t bValue) {
  rgbs[0].r = rValue;
  rgbs[0].g = gValue;
  rgbs[0].b = bValue;
  FastLED.show();
}