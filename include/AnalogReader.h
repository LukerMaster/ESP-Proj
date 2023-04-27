#include <Arduino.h>
#include <inttypes.h>

class AnalogReader
{
    uint8_t xPin;
    uint8_t yPin;
    public:
    AnalogReader(uint8_t Xpin, uint8_t Ypin);
    float GetX();
    float GetY();
};