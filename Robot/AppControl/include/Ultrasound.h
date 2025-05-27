#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include <Arduino.h>

#define ULTRASOUND_I2C_ADDR 0x77 

// register
#define DISDENCE_L    0 // low 8 bits of distance, unit: mm
#define DISDENCE_H    1

#define RGB_BRIGHTNESS  50 // 0-255

#define RGB_WORK_MODE 2 // RGB light mode: 0 indicates custom mode; 1 indicates breathing light mode. Default is 0

#define RGB1_R      3 // R value of probe 1, 0~255, default 0
#define RGB1_G      4 // default 0
#define RGB1_B      5 // default 255

#define RGB2_R      6 // R value of probe 2, 0~255, default 0
#define RGB2_G      7 // default 0
#define RGB2_B      8 // default 255

#define RGB1_R_BREATHING_CYCLE      9 // in breathing light mode, breathing cycle for R of probe 1, unit: 100ms, default 0
#define RGB1_G_BREATHING_CYCLE      10
#define RGB1_B_BREATHING_CYCLE      11

#define RGB2_R_BREATHING_CYCLE      12 // probe 2
#define RGB2_G_BREATHING_CYCLE      13
#define RGB2_B_BREATHING_CYCLE      14

#define RGB_WORK_SIMPLE_MODE    0
#define RGB_WORK_BREATHING_MODE   1

class Ultrasound {
  public:
    Ultrasound();
    bool wireWriteByte(uint8_t addr, uint8_t val);
    bool wireWriteDataArray(uint8_t addr, uint8_t reg,uint8_t *val,unsigned int len);
    int wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len);
    
    void Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
    void Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
    int Filter();
    u16 GetDistance();
};
#endif
