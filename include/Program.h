#pragma once
#include <Arduino.h>
#include <memory>
#include <vector>

#include "CarInfo.h"
#include "CarSimulation.h"

#include "ScreenAPI.h"
#include "AnalogReader.h"
#include "PhotoresistorReader.h"
#include "AsyncThermometer.h"
#include "Colorinator.h"
#include "WatchedValue.h"


class Program
{
    uint32_t _TickRate;

    std::shared_ptr<ScreenAPI> screen;
    std::shared_ptr<PhotoresistorReader> photoresistor;
    std::shared_ptr<AsyncThermometer> thermometer;
    std::shared_ptr<AnalogReader> analog;

    std::unique_ptr<Colorinator> colorinator;

    std::vector<std::shared_ptr<INotifiable>> screenWidgets;

    std::shared_ptr<WatchedValue<float>> temperature;
    std::shared_ptr<WatchedValue<uint64_t>> rpm;
    std::shared_ptr<WatchedValue<uint32_t>> kmph;
    std::shared_ptr<WatchedValue<float>> fuelPercentage;
    std::shared_ptr<WatchedValue<int16_t>> gear;
    std::shared_ptr<WatchedValue<uint64_t>> odometer;
    std::shared_ptr<WatchedValue<uint64_t>> tripometer;

    std::shared_ptr<CarSimulation> carInputs;

public:
    Program(std::shared_ptr<ScreenAPI> screen, 
    std::shared_ptr<PhotoresistorReader> photoresistor, 
    std::shared_ptr<AsyncThermometer> thermometer, 
    std::shared_ptr<AnalogReader> analog);

    void SetTickRate(uint32_t tickRate = 20);
    uint32_t GetTickRate();
    void Tick(uint64_t millisDelta);
protected:
    void RefreshWidgets();
    void ReadCarValuesToWidgets();
};