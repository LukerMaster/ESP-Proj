#pragma once
#include <Arduino.h>
#include <memory>
#include <vector>

#include "ScreenAPI.h"
#include "PhotoresistorReader.h"
#include "AsyncThermometer.h"
#include "Colorinator.h"
#include "WatchedValue.h"


class Program
{
    std::shared_ptr<ScreenAPI> screen;
    std::shared_ptr<PhotoresistorReader> photoresistor;
    std::shared_ptr<AsyncThermometer> thermometer;

    std::unique_ptr<Colorinator> colorinator;

    uint32_t _TickRate;

    std::vector<std::shared_ptr<INotifiable>> screenWidgets;
    std::shared_ptr<WatchedValue<float>> temperature;
    std::shared_ptr<WatchedValue<uint64_t>> rpm;

public:
    Program(std::shared_ptr<ScreenAPI> screen, std::shared_ptr<PhotoresistorReader> photoresistor, std::shared_ptr<AsyncThermometer> thermometer);
    void SetTickRate(uint32_t tickRate = 20);
    uint32_t GetTickRate();
    void Tick(uint64_t millisDelta);
protected:
    void RefreshWidgets();
};