#pragma once
#include <DS18B20.h>
#include <memory>
#include <atomic>
#include <Task.h>

class AsyncThermometer
{
    std::shared_ptr<DS18B20> oneWireDriver;
    /// @brief Wrapping a float in std::atomic provides thread safety as this value is
    /// accessed by anyone who wants to read the temperature and a seperate thread that
    /// measures the temperature and saves it here.
    std::atomic<float> lastTemperature;

    /// @brief Temperature measurement on DS18B20 takes like 500ms
    /// so it is too slow and lags UI. Therefore we use seperate task to measure
    /// the temperature on a seperate thread (ESP32 has 2 cores).
    /// We also "cheat" by returning last measured temperature
    /// if current measurement is not done yet. So it is not a good way to measure
    /// unless done in a loop, as frequent as possible.
    Task measureTask;
public:
    AsyncThermometer(uint8_t thermometerPin);
    float GetTemperature();
};