#include "PhotoresistorReader.h"

PhotoresistorReader::PhotoresistorReader(uint8_t analogReadPin)
{
    Serial.println("Photoresistor reader starting.");
    photoresistorPin = analogReadPin;
}

float PhotoresistorReader::GetLightLevel()
{
    uint16_t darkness = analogRead(photoresistorPin);
    darkness = darkness / 18; // 1800 is really dark, so set it to be 100% dark.
    return std::max(100 - darkness, 0);
}