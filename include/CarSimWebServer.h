#pragma once
#include <Arduino.h>
#include <StrFormat.h>
#include <string>
#include <WiFi.h>
#include <WebServer.h>
#include <CarSimulation.h>
#include <ESPAsyncWebServer.h>
#include <Task.h>

/// @brief Responsible for monitoring the car simulation and responding for server calls.
class CarSimWebServer
{
    std::shared_ptr<CarInfo> carData;
    AsyncWebServer server;
    Task connectionTask;
    public:
    CarSimWebServer(std::shared_ptr<CarInfo> programToMonitor, std::string ssid, std::string wifiPass);
    void Tick();
};