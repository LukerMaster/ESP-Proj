#include "AnalogReader.h"

AnalogReader::AnalogReader(uint8_t Xpin, uint8_t Ypin)
{
    xPin = Xpin;
    yPin = Ypin;

    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
}

float AnalogReader::GetX()
{
    return (float)analogRead(xPin) / 4095;
}

float AnalogReader::GetY()
{
    return (float)analogRead(yPin) / 4095;
}
