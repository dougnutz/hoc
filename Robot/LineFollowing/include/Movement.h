#include <Arduino.h>


class Movement {
    public:
        static void Motor_Init(void);
        static void Motor_Stop(void);
        static void Motors_Set(int8_t Motor_0, int8_t Motor_1, int8_t Motor_2, int8_t Motor_3);
        static void Velocity_Controller(uint16_t angle, uint8_t velocity,int8_t rot,bool drift);
};
