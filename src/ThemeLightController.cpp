#include "ThemeLightController.h"

ThemeLightController::ThemeLightController(uint8_t photoresistor_pin, std::shared_ptr<Themeinator> themeinator)
{
    Serial.println("Photoresistor theme controller starting.");
    SetPhotoResistorPin(photoresistor_pin);
    this->themeinator = themeinator;
}

void ThemeLightController::SetPhotoResistorPin(uint8_t pin)
{
    _PhotoresistorPin = pin;
    pinMode(_PhotoresistorPin, INPUT_PULLUP);
}

void ThemeLightController::UpdateTheme()
{
    uint16_t darkness = analogRead(_PhotoresistorPin);
    if (darkness > 1200 && themeinator->CurrentTheme != Theme::Dark)
    {
        themeinator->CurrentTheme = Theme::Dark;
    }
    if (darkness <= 1200 && themeinator->CurrentTheme != Theme::Standard)
    {
        themeinator->CurrentTheme = Theme::Standard;
    }
}
