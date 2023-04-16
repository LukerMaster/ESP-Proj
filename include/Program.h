#pragma once
#include <Arduino.h>
#include <ScreenController.h>
#include <Configuration.h>
#include <ThemeLightController.h>
#include <memory>

class Program
{
    std::shared_ptr<Configuration> cfg;

    std::shared_ptr<ScreenController> screenController;
    std::shared_ptr<ThemeLightController> themeLightController;
    
    uint32_t _TickRate;
public:
    void SetTickRate(uint32_t tickRate = 20);
    uint32_t GetTickRate();
    void Start();
    void Tick(uint64_t millisDelta);
};