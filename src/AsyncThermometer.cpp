#include "AsyncThermometer.h"

AsyncThermometer::AsyncThermometer(uint8_t thermometerPin)
{
    oneWireDriver = std::make_shared<DS18B20>(thermometerPin);
    lastTemperature = 0.0f;
    measureTask.setPriority(0);
    measureTask.setName("Temperature Measurement");
    measureTask.setStackSize(10000);
    measureTask.setFn([this]()
    {
        lastTemperature = oneWireDriver->getTempC();
    });
}

float AsyncThermometer::GetTemperature()
{
    if (!measureTask.isDone()) 
    {
        return lastTemperature;
    }
    measureTask.stop(); // cleanup after previous measurement.
    measureTask.start(); // start a new one.
    return lastTemperature; // return old value while we wait for new measurement.
}