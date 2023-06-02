#pragma once
#include <inttypes.h>
#include "CarInfo.h"
#include <memory>
#include <Arduino.h>
#include <vector>

class CarSimulation
{
    std::shared_ptr<CarInfo> carData;

    float GetGearMult(int16_t gear);

    /// @brief 
    /// Simulating drag coefficient with simple penalty to RPM raise speed at higher gears.
    /// @param gear Current gear
    /// @return 
    float GetRpmRaiseSpeedPenalty(int16_t gear);
    float InterpolateOilTemp(float x);

    float windResistance = 0.7f;
    float oilTempConductivity = 0.06f;

    public:
        CarSimulation(std::shared_ptr<CarInfo> carData)
            : carData(carData)
        {
            carData->SetRpmRaiseSpeed(5000);
            carData->SetTankCapacity(30);
            carData->SetFuel(30);
            carData->SetNumOfForwardGears(7);
            carData->SetMaxRpm(7200);
            carData->SetOilTempC(15);
        };
    void Tick(float deltaTime);
};