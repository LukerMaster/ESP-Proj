#pragma once
#include <Arduino.h>
#include <memory>
#include <vector>

#include "CarSimulation.h"
#include "ScreenAPI.h"
#include "AnalogReader.h"
#include "PhotoresistorReader.h"
#include "AsyncThermometer.h"
#include "Colorinator.h"
#include "WatchedValue.h"

class PhysicalIOLogic
{
    std::shared_ptr<ScreenAPI> screen;
    std::shared_ptr<PhotoresistorReader> photoresistor;
    std::shared_ptr<AsyncThermometer> thermometer;
    std::shared_ptr<AnalogReader> analog;

    std::unique_ptr<Colorinator> colorinator;

    std::vector<std::shared_ptr<INotifiable>> screenWidgets;

    std::shared_ptr<WatchedValue<float>> temperature;
    std::shared_ptr<WatchedValue<float>> oilTemperature;
    std::shared_ptr<WatchedValue<uint64_t>> rpm;
    std::shared_ptr<WatchedValue<uint32_t>> kmph;
    std::shared_ptr<WatchedValue<float>> fuelPercentage;
    std::shared_ptr<WatchedValue<int16_t>> gear;
    std::shared_ptr<WatchedValue<uint64_t>> odometer;
    std::shared_ptr<WatchedValue<uint64_t>> tripometer;

    std::shared_ptr<CarSimulation> simulation;
    std::shared_ptr<CarInfo> carData;

public:
    PhysicalIOLogic(std::shared_ptr<ScreenAPI> screen, 
    std::shared_ptr<PhotoresistorReader> photoresistor, 
    std::shared_ptr<AsyncThermometer> thermometer, 
    std::shared_ptr<AnalogReader> analog,
    std::shared_ptr<CarSimulation> simulation,
    std::shared_ptr<CarInfo> carData);
    void PerformIO();
protected:
    void RefreshWidgets();
    void ReadCarValuesToWidgets();

};