#include "CarSimulation.h"

float CarSimulation::GetGearMult(int16_t gear)
{
    float finalDrive = 0.013f;
    switch (gear)
    {
        case 1:
            return 1.0f * finalDrive;
        case 2:
            return 2.2f * finalDrive;
        case 3:
            return 3.0f * finalDrive;
        case 4:
            return 3.6f * finalDrive;
        default:
            return (((gear-4) * 0.4f) + 3.6f) * finalDrive;
    }
}

float CarSimulation::GetRpmRaiseSpeedPenalty(int16_t gear)
{
    return 2.f / (gear*gear + 1);
}

void CarSimulation::Tick(float deltaTime)
{
    if (throttleValue > 0.02f && fuel > 0)
    {
        rpm += throttleValue * deltaTime * rpmRaiseSpeed * GetRpmRaiseSpeedPenalty(gear);
    }
    else
    {
        if (rpm > deltaTime * rpmRaiseSpeed * 0.5f)
            rpm -= deltaTime * rpmRaiseSpeed * 0.5f * GetRpmRaiseSpeedPenalty(gear);
    }

    if (brakeValue > 0.02f)
    {
        rpm -= brakeValue * deltaTime * rpmRaiseSpeed;
    }

    if (brakeValue > 0.02f)
    {
        rpm -= brakeValue * deltaTime * rpmRaiseSpeed;
    }

    if (rpm < 0)
    {
        rpm = 0;
    };

    speed = rpm * GetGearMult(gear);

    if (rpm > maxRpm * 0.94f)
    {
        if (gear < maxGear)
        {
            gear += 1;
            rpm = speed / GetGearMult(gear);
        }
            
        else if (rpm > maxRpm)
            rpm = maxRpm;
    }
    else if (rpm < maxRpm * 0.4f)
    {
        if (gear > 1)
        {
            gear -= 1;
            rpm = speed / GetGearMult(gear);
        }
    }

    odometer += speed * deltaTime / 3600;
    fuel -= rpm * deltaTime * 0.00002f;
}

void CarSimulation::SetThrottle(float throttle)
{
    throttleValue = throttle;
}

void CarSimulation::SetBrake(float brake)
{
    brakeValue = brake;
}

float CarSimulation::GetSpeedKmh()
{
    return speed;
}

float CarSimulation::GetMaxRpm()
{
    return maxRpm;
}

float CarSimulation::GetRpm()
{
    return rpm;
}

int16_t CarSimulation::GetGear()
{
    return gear;
}

float CarSimulation::GetOdometer()
{
    return odometer;
}

float CarSimulation::GetFuelLeft()
{
    return fuel / maxFuel;
}
