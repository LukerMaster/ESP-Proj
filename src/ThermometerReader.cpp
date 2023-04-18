#include "ThermometerReader.h"

ThermometerReader::ThermometerReader(uint8_t thermometerPin)
{
    oneWireDriver = std::make_shared<DS18B20>(thermometerPin);
}

float ThermometerReader::MeasureTemperature()
{
    lastTemperature = oneWireDriver->getTempC();
    return lastTemperature;
}

float ThermometerReader::GetLastMeasurement()
{
    return lastTemperature;
}
