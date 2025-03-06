#include <Arduino.h>
class Helper {
    public:
        static void Init();
        static bool WriteBytes(uint8_t data);
        static bool ReadBytes(uint8_t address, uint8_t &val);
        static void Rgb_Show(uint8_t rValue, uint8_t gValue, uint8_t bValue);
};