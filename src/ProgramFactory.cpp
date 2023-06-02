#include "ProgramFactory.h"

std::shared_ptr<Program> ProgramFactory::CreateProgram()
{

    auto cfg = std::make_shared<Configuration>();

    auto bus = std::make_shared<Arduino_HWSPI>(
        cfg->PIN_DC_TFT,
        cfg->PIN_CS_TFT,
        cfg->PIN_SCK_TFT,
        cfg->PIN_MOSI_TFT);

    auto gfx = std::make_shared<Arduino_ILI9341>(bus.get(), cfg->PIN_RST_TFT);
    
    auto screenAPI = std::make_shared<ScreenAPI>(bus, gfx);
    auto photoresistorReader = std::make_shared<PhotoresistorReader>(cfg->PIN_PHOTORESISTOR_INPUT);
    auto thermometerReader = std::make_shared<AsyncThermometer>(cfg->PIN_THERMOMETER_ONE_WIRE_INPUT);
    auto analog = std::make_shared<AnalogReader>(cfg->PIN_ANALOG_X, cfg->PIN_ANALOG_Y);
    

    auto carData = std::make_shared<CarInfo>();
    auto carSimulation = std::make_shared<CarSimulation>(carData);
    auto simWebServer = std::make_shared<CarSimWebServer>(carData, cfg->WIFI_SSID, cfg->WIFI_PASSWORD);
    auto carReaderLogic = std::make_shared<PhysicalIOLogic>(screenAPI, photoresistorReader, thermometerReader, analog, carSimulation, carData);

    return std::make_shared<Program>(carReaderLogic, carSimulation, simWebServer);
}