#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

void Motor_Init(void);
void Motor_Stop(void);
void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);
void Velocity_Controller(uint16_t angle, uint8_t velocity, int8_t rot, bool drift);

#endif // MOTORS_H
