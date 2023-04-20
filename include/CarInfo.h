#pragma once
#include <inttypes.h>

class CarInfo
{
protected:
    uint16_t kmph = 0;
    float fuelPercentage = 1.0f;
    uint32_t rpm = 0;
    uint32_t maxRpm = 6000;
    uint64_t odometer = 0;
    uint64_t tripometer = 0;
    int16_t oilTempC = 0;
    int16_t maxOilTempC = 130;
    int16_t gear = 0;
    int16_t topGear = 6;
public:
    void SetSpeed(uint16_t kmph);
    uint16_t GetSpeed();
    void SetFuelPercentage(float percentage);
    float GetFuelPercentage();
    void SetEngineRpm(uint32_t rpm);
    uint32_t GetEngineRpm();
    void SetOdometer(uint64_t kms);
    uint64_t GetOdometerReading();
    void SetTripometer(uint64_t kms);
    uint64_t GetTripometerReading();
    void SetOilTempC(int16_t tempC);
    int16_t GetOilTempC();
    void SetCurrentGear(int16_t gear);
    int16_t GetCurrentGear();
    void SetNumOfForwardGears(int16_t gears);
    int16_t GetNumOfForwardGears();
    void SetMaxRpm(int32_t maxRpm);
    int32_t GetMaxRpm();
};