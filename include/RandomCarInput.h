#pragma once
#include <memory>
#include <CarInfo.h>

/// @brief Temporary class to generate random inputs for the car.
class RandomCarInput
{
    std::shared_ptr<CarInfo> carInfo;
    uint32_t millisSinceLastUpdate = 0;
    uint32_t maxMillis = 1000;
public:
    RandomCarInput(std::shared_ptr<CarInfo> car);
    void AddRandomInputsToCar(float deltaTime);
    void AddTime(uint32_t millis);
    void SetTimeBetweenUpdates(uint32_t millis);
};