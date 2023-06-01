#pragma once
#include <inttypes.h>
#include "CarInfo.h"
#include <memory>
#include <Arduino.h>

class CarSimulation
{
    std::shared_ptr<CarInfo> carData;

    float GetGearMult(int16_t gear);

    /// @brief 
    /// Simulating drag coefficient with simple penalty to RPM raise speed at higher gears.
    /// @param gear Current gear
    /// @return 
    float GetRpmRaiseSpeedPenalty(int16_t gear);

    public:
    CarSimulation(std::shared_ptr<CarInfo> carData)
    : carData(carData){};
    void Tick(float deltaTime);
};