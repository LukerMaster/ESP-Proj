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
    Serial.println(carData->GetThrottleInput());
    if (carData->GetThrottleInput() > 0.02f && carData->GetFuel() > 0)
    {
        carData->SetEngineRpm(carData->GetEngineRpm() + carData->GetThrottleInput() * deltaTime * carData->GetRpmRaiseSpeed() * GetRpmRaiseSpeedPenalty(carData->GetCurrentGear()));
    }
    else
    {
        if (carData->GetEngineRpm() > deltaTime * carData->GetRpmRaiseSpeed() * 0.5f)
            carData->SetEngineRpm(carData->GetEngineRpm() - deltaTime * carData->GetRpmRaiseSpeed() * 0.5f * GetRpmRaiseSpeedPenalty(carData->GetCurrentGear()));
    }

    if (carData->GetBrakeInput() > 0.02f)
    {
        carData->SetEngineRpm(carData->GetEngineRpm() - carData->GetBrakeInput() * deltaTime * carData->GetRpmRaiseSpeed());
    }

    if (carData->GetBrakeInput() > 0.02f)
    {
        carData->SetEngineRpm(carData->GetEngineRpm() - carData->GetBrakeInput() * deltaTime * carData->GetRpmRaiseSpeed());
    }

    if (carData->GetEngineRpm() < 0)
    {
        carData->SetEngineRpm(0);
    };

    carData->SetSpeed(carData->GetEngineRpm() * GetGearMult(carData->GetCurrentGear()));

    if (carData->GetEngineRpm() > carData->GetMaxRpm() * 0.94f)
    {
        if (carData->GetCurrentGear() < carData->GetNumOfForwardGears())
        {
            carData->SetCurrentGear(carData->GetCurrentGear() + 1);
            carData->SetEngineRpm( carData->GetSpeed() / GetGearMult(carData->GetCurrentGear()));
        }
            
        else if (carData->GetEngineRpm() > carData->GetMaxRpm())
            carData->SetEngineRpm(carData->GetMaxRpm());
    }
    else if (carData->GetEngineRpm() < carData->GetMaxRpm() * 0.4f)
    {
        if (carData->GetCurrentGear() > 1)
        {
            carData->SetCurrentGear(carData->GetCurrentGear() - 1);
            carData->SetEngineRpm(carData->GetSpeed() / GetGearMult(carData->GetCurrentGear()));
        }
    }

    carData->SetOdometer(carData->GetOdometerReading() + carData->GetSpeed() * deltaTime / 3600);
    carData->SetFuel(carData->GetFuel() - carData->GetEngineRpm() * deltaTime * 0.00002f);
}

