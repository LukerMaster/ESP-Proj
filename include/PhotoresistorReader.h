#pragma once
#include <inttypes.h>
#include <Arduino.h>

class PhotoresistorReader
{
    uint8_t photoresistorPin;
public:
    PhotoresistorReader(uint8_t analogReadPin);
    float GetLightLevel();
};