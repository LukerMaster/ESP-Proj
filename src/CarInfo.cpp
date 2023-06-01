#include "CarInfo.h"

void CarInfo::SetSpeed(float kmph)
{
    this->kmph = kmph;
}

float CarInfo::GetSpeed()
{
    return kmph;
}

void CarInfo::SetFuel(float liters)
{
    this->fuel = liters;
    if (this->fuel < 0)
        this->fuel = 0;
}

float CarInfo::GetFuel()
{
    return fuel;
}

void CarInfo::SetTankCapacity(float liters)
{
    if (liters < 0)
        throw std::runtime_error("Fuel tank cannot have negative capacity.");
    this->fuelTankCapacity = liters;
}
float CarInfo::GetTankCapacity()
{
    return fuelTankCapacity;
}

void CarInfo::SetEngineRpm(float rpm)
{
    this->rpm = rpm;
}

float CarInfo::GetEngineRpm()
{
    return rpm;
}

void CarInfo::SetOdometer(float kms)
{
    this->odometer = kms;
}

float CarInfo::GetOdometerReading()
{
    return odometer;
}

void CarInfo::SetTripometer(float kms)
{
    this->tripometer = kms;
}

float CarInfo::GetTripometerReading()
{
    return tripometer;
}

void CarInfo::SetOilTempC(float tempC)
{
    this->oilTempC = tempC;
}

float CarInfo::GetOilTempC()
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

void CarInfo::SetMaxRpm(float maxRpm)
{
    this->maxRpm = maxRpm;
}

float CarInfo::GetMaxRpm()
{
    return maxRpm;
}

void CarInfo::SetThrottleInput(float value)
{
    this->throttlePressValue = value;
}

float CarInfo::GetThrottleInput()
{
    return this->throttlePressValue;
}

void CarInfo::SetBrakeInput(float value)
{
    this->brakePressValue = value;
}

float CarInfo::GetBrakeInput()
{
    return this->brakePressValue;
}

void CarInfo::SetRpmRaiseSpeed(float rpmPerSec)
{
    this->rpmRaiseSpeed = rpmPerSec;
}

float CarInfo::GetRpmRaiseSpeed()
{
    return this->rpmRaiseSpeed;
}

float CarInfo::GetInsideTemperature()
{
    return this->insideTempReading;
}

void CarInfo::SetInsideTemperature(float tempC)
{
    this->insideTempReading = tempC;
}
