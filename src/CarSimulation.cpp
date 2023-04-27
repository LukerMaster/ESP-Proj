#include "CarSimulation.h"

float CarSimulation::GetGearMult(int16_t gear)
{
    float finalDrive = 0.009f;
    switch (gear)
    {
        case 1:
            return 1.0f * finalDrive;
        case 2:
            return 2.2f * finalDrive;
        case 3:
            return 3.0f * finalDrive;
        case 4:
            return 4.2f * finalDrive;
        case 5:
            return 5.0f * finalDrive;
        case 6:
            return 5.8f * finalDrive;
        case 7:
            return 6.4f * finalDrive;
        default:
            return ((gear * 0.4f) + 3.6f) * finalDrive;
    }
}

void CarSimulation::Tick(float deltaTime)
{
    if (throttleValue > 0.02f)
    {
        rpm += throttleValue * deltaTime * rpmRaiseSpeed;
    }
    else
    {
        if (rpm > deltaTime * rpmRaiseSpeed * 0.5f)
            rpm -= deltaTime * rpmRaiseSpeed * 0.5f;
    }

    speed = rpm * GetGearMult(gear);

    if (rpm > maxRpm * 0.87f)
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
    fuel -= rpm * deltaTime * 0.001f;
}

void CarSimulation::SetThrottle(float throttle)
{
    throttleValue = throttle;
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
