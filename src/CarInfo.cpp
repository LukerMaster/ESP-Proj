#include "CarInfo.h"

void CarInfo::SetSpeed(uint16_t kmph)
{
    this->kmph = kmph;
}

uint16_t CarInfo::GetSpeed()
{
    return kmph;
}

void CarInfo::SetFuelPercentage(float percentage)
{
    this->fuelPercentage = percentage;
}

float CarInfo::GetFuelPercentage()
{
    return fuelPercentage;
}

void CarInfo::SetEngineRpm(uint32_t rpm)
{
    this->rpm = rpm;
}

uint32_t CarInfo::GetEngineRpm()
{
    return rpm;
}

void CarInfo::SetOdometer(uint64_t kms)
{
    this->odometer = kms;
}

uint64_t CarInfo::GetOdometerReading()
{
    return odometer;
}

void CarInfo::SetTripometer(uint64_t kms)
{
    this->tripometer = kms;
}

uint64_t CarInfo::GetTripometerReading()
{
    return tripometer;
}

void CarInfo::SetOilTempC(int16_t tempC)
{
    this->oilTempC = tempC;
}

int16_t CarInfo::GetOilTempC()
{
    return oilTempC;
}

void CarInfo::SetCurrentGear(int16_t gear)
{
    this->gear = gear;
}

int16_t CarInfo::GetCurrentGear()
{
    return gear;
}

void CarInfo::SetNumOfForwardGears(int16_t gears)
{
    this->topGear = gears;
}

int16_t CarInfo::GetNumOfForwardGears()
{
    return topGear;
}

void CarInfo::SetMaxRpm(int32_t maxRpm)
{
    this->maxRpm = maxRpm;
}

int32_t CarInfo::GetMaxRpm()
{
    return maxRpm;
}
