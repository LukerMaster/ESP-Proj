#pragma once
#include <inttypes.h>
#include <string>

class Configuration
{
public:
  uint8_t PIN_SCK_TFT = 18; // ADC2X
  uint8_t PIN_MOSI_TFT = 23; // ADC2X
  uint8_t PIN_DC_TFT = 16;
  uint8_t PIN_RST_TFT = 17;
  uint8_t PIN_CS_TFT = 5;

  //uint8_t PIN_MISO_TFT = 19; // ADC2X

  uint8_t PIN_PHOTORESISTOR_INPUT = 32; // ADC2X

  uint8_t PIN_THERMOMETER_ONE_WIRE_INPUT = 33; // ADC2X

  uint8_t PIN_ANALOG_X = 35;
  uint8_t PIN_ANALOG_Y = 34;

  std::string WIFI_SSID = "SSID";
  std::string WIFI_PASSWORD = "PASSWORD";
};