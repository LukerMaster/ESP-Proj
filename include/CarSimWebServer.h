#pragma once
#include <Arduino.h>
#include <string>
#include <WiFi.h>
#include <WebServer.h>
#include <CarSimulation.h>
#include <ESPAsyncWebServer.h>

/// @brief Responsible for monitoring the car simulation and responding for server calls.
class CarSimWebServer
{
    std::shared_ptr<CarSimulation> carData;
    AsyncWebServer server;
    public:
    CarSimWebServer(std::shared_ptr<CarSimulation> programToMonitor, std::string ssid, std::string wifiPass);
    void Tick();
};