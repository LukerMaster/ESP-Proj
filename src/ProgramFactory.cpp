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
    std::shared_ptr<Themeinator> themeinator = std::make_shared<Themeinator>();
    
    auto textPrinter = std::make_shared<TextPrinter>(themeinator, gfx);
    auto themeLightController = std::make_shared<ThemeLightController>(cfg->PIN_PHOTORESISTOR_INPUT, themeinator);
    auto screenController = std::make_shared<ScreenController>(bus, gfx, textPrinter, themeinator);
    
    
    return std::make_shared<Program>(screenController, themeLightController);
}