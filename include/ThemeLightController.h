#pragma once
#include <memory>
#include <Themeinator.h>
#include <inttypes.h>
#include <Arduino.h>

/// @brief Controls the theme based on photoresistor input.
class ThemeLightController
{
    uint8_t _PhotoresistorPin;
    std::shared_ptr<Themeinator> themeinator;
public:
    bool ScreenNeedsFullRedraw;
    ThemeLightController(uint8_t photoresistor_pin, std::shared_ptr<Themeinator> themeinator);
    void SetPhotoResistorPin(uint8_t pin);
    void UpdateTheme();
};