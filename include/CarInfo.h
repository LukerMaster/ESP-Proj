#pragma once
#include <inttypes.h>
#include <stdexcept>

class CarInfo
{
protected:
    float kmph = 0;
    float fuel = 0;
    float fuelTankCapacity = 0;
    float rpm = 0;
    float maxRpm = 6000;
    float odometer = 0;
    float tripometer = 0;
    float oilTempC = 0;
    float maxOilTempC = 130;
    int16_t gear = 0;
    int16_t topGear = 6;

    float throttlePressValue = 0;
    float brakePressValue = 0;

    float rpmRaiseSpeed = 0;

    float insideTempReading = 0;
public:

    void SetThrottleInput(float value);
    float GetThrottleInput();
    void SetBrakeInput(float value);
    float GetBrakeInput();

    float GetInsideTemperature();
    void SetInsideTemperature(float tempC);
    void SetSpeed(float kmph);
    float GetSpeed();
    void SetFuel(float liters);
    float GetFuel();
    void SetTankCapacity(float liters);
    float GetTankCapacity();
    void SetEngineRpm(float rpm);
    float GetEngineRpm();
    void SetOdometer(float kms);
    float GetOdometerReading();
    void SetTripometer(float kms);
    float GetTripometerReading();
    void SetOilTempC(float tempC);
    float GetOilTempC();
    void SetCurrentGear(int16_t gear);
    int16_t GetCurrentGear();
    void SetNumOfForwardGears(int16_t gears);
    int16_t GetNumOfForwardGears();
    void SetMaxRpm(float maxRpm);
    float GetMaxRpm();
};