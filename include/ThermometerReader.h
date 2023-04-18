#pragma once
#include <DS18B20.h>
#include <memory>
#include <atomic>

class ThermometerReader
{
    std::shared_ptr<DS18B20> oneWireDriver;
    std::atomic<float> lastTemperature;
public:
    ThermometerReader(uint8_t thermometerPin);
    float MeasureTemperature();
    float GetLastMeasurement();
};