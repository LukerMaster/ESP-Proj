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


float CarSimulation::InterpolateOilTemp(float x) 
{
    std::vector<float> x_values = {0, 1000, 3000, 7200, 9000, 11000, 50000};
    std::vector<float> y_values = {30, 80, 100, 120, 180, 300, 800};

    // Finding the two closest data points
    int index = 0;
    while (x > x_values[index]) {
        index++;
    }

    float x1 = x_values[index - 1];
    float x2 = x_values[index];
    float y1 = y_values[index - 1];
    float y2 = y_values[index];

    // Interpolating the value of Y
    float y = y1 + (x - x1) * (y2 - y1) / (x2 - x1);

    return y;
}


void CarSimulation::Tick(float deltaTime)
{
    // Acceleration
    if (carData->GetThrottleInput() > 0.02f && carData->GetFuel() > 0)
    {
        carData->SetSpeed(carData->GetSpeed() + carData->GetThrottleInput() * deltaTime * enginePower);
    }
    // Braking
    if (carData->GetBrakeInput() > 0.02f)
    {
        carData->SetSpeed(carData->GetSpeed() - carData->GetBrakeInput() * deltaTime * enginePower);
    }

    // Wind resistance
    carData->SetSpeed(carData->GetSpeed() - (carData->GetSpeed() * deltaTime * windResistance));

    // Apply to RPM
    carData->SetEngineRpm(carData->GetSpeed() / GetGearMult(carData->GetCurrentGear()));

    // Gear changing
    if (carData->GetEngineRpm() > carData->GetMaxRpm() * 0.94f)
    {
        if (carData->GetCurrentGear() < carData->GetNumOfForwardGears())
        {
            carData->SetCurrentGear(carData->GetCurrentGear() + 1);
            carData->SetEngineRpm( carData->GetSpeed() / GetGearMult(carData->GetCurrentGear()));
        }
    }
    else if (carData->GetEngineRpm() < carData->GetMaxRpm() * 0.4f)
    {
        if (carData->GetCurrentGear() > 1)
        {
            carData->SetCurrentGear(carData->GetCurrentGear() - 1);
            carData->SetEngineRpm(carData->GetSpeed() / GetGearMult(carData->GetCurrentGear()));
        }
    }
    if (carData->GetEngineRpm() > carData->GetMaxRpm())
        carData->SetEngineRpm(carData->GetMaxRpm());

    // Set odometer
    carData->SetOdometer(carData->GetOdometerReading() + carData->GetSpeed() * deltaTime / 3600);
    // Set tripometer
    carData->SetTripometer(carData->GetTripometerReading() + carData->GetSpeed() * deltaTime / 3600);
    // Fuel consumption
    carData->SetFuel(carData->GetFuel() - carData->GetEngineRpm() * deltaTime * 0.00001f);

    // Oil temperature
    float targetOilTemp = InterpolateOilTemp(carData->GetEngineRpm());
    carData->SetOilTempC(carData->GetOilTempC() + ((targetOilTemp - carData->GetOilTempC()) * deltaTime * oilTempConductivity));
}