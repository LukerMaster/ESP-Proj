#pragma once
#include <Arduino.h>
#include <memory>
#include "ScreenAPI.h"
#include "PhotoresistorReader.h"
#include "Colorinator.h"

class Program
{
    std::shared_ptr<ScreenAPI> screen;
    std::shared_ptr<PhotoresistorReader> photoresistor;

    std::unique_ptr<Colorinator> colorinator;

    uint32_t _TickRate;

    uint64_t time = 0;

public:
    Program(std::shared_ptr<ScreenAPI> screen, std::shared_ptr<PhotoresistorReader> photoresistor);
    void SetTickRate(uint32_t tickRate = 20);
    uint32_t GetTickRate();
    void Start();
    void Tick(uint64_t millisDelta);
};