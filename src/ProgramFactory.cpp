#include "ProgramFactory.h"

std::shared_ptr<Program> ProgramFactory::CreateProgram()
{

    auto cfg = std::make_shared<Configuration>();

    auto bus = std::make_shared<Arduino_HWSPI>(
        cfg->PIN_DC_TFT,
        cfg->PIN_CS_TFT,
        cfg->PIN_SCK_TFT,
        cfg->PIN_MOSI_TFT,
        cfg->PIN_MISO_TFT);

    auto gfx = std::make_shared<Arduino_ILI9341>(bus.get(), cfg->PIN_RST_TFT);
    
    auto screenAPI = std::make_shared<ScreenAPI>(bus, gfx);
    auto photoresistorReader = std::make_shared<PhotoresistorReader>(cfg->PIN_PHOTORESISTOR_INPUT);
    
    
    return std::make_shared<Program>(screenAPI, photoresistorReader);
}