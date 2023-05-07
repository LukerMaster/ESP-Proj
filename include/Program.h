#pragma once
#include <Arduino.h>
#include <memory>
#include <vector>

#include "CarSimulation.h"
#include "PhysicalIOLogic.h"
#include "CarSimWebServer.h"


class Program
{
    std::shared_ptr<PhysicalIOLogic> readerLogic;
    std::shared_ptr<CarSimulation> carSimulation;
    std::shared_ptr<CarSimWebServer> simWebServer;
public:
    Program(
    std::shared_ptr<PhysicalIOLogic> readerLogic,
    std::shared_ptr<CarSimulation> carSimulation,
    std::shared_ptr<CarSimWebServer> simWebServer
    ) :
    readerLogic(readerLogic),
    carSimulation(carSimulation),
    simWebServer(simWebServer) 
    {};

    /// @brief Updates the program loop
    /// @param deltaTime Time since last update in seconds.
    void Tick(float deltaTime);
};