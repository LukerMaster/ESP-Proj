#pragma once
#include <inttypes.h>

class CarSimulation
{
    float speed = 0;
    float rpm = 0;
    float odometer = 0;
    float fuel = 30.f;

    float throttleValue = 0;
    float brakeValue = 0;

    int16_t gear = 1;
    int16_t maxGear = 6;

    float rpmRaiseSpeed = 2400;
    float maxRpm = 7200;
    float maxFuel = 30.f;

    float GetGearMult(int16_t gear);

    /// @brief 
    /// Simulating drag coefficient with simple penalty to RPM raise speed at higher gears.
    /// @param gear Current gear
    /// @return 
    float GetRpmRaiseSpeedPenalty(int16_t gear);

    public:
    CarSimulation(float rpmRaiseSpeed = 2400, float maxRpm = 7200, int16_t gearCount = 7, float fuelCapacity = 30.f)
    : rpmRaiseSpeed(rpmRaiseSpeed), 
    maxRpm(maxRpm), 
    maxGear(gearCount), 
    maxFuel(fuelCapacity),  
    fuel(fuelCapacity) {};
    void Tick(float deltaTime);
    void SetThrottle(float throttle);
    void SetBrake(float brake);

    float GetSpeedKmh();
    float GetMaxRpm();
    float GetRpm();
    int16_t GetGear();
    float GetOdometer();
    float GetFuelLeft();
};