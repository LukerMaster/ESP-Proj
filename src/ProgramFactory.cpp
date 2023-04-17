#include "ProgramFactory.h"

std::shared_ptr<Program> ProgramFactory::CreateProgram()
{

    auto cfg = std::make_shared<Configuration>();

    std::shared_ptr<Themeinator> themeinator = std::make_shared<Themeinator>();
    auto themeLightController = std::make_shared<ThemeLightController>(cfg->PIN_PHOTORESISTOR_INPUT, themeinator);
    auto screenController = std::make_shared<ScreenController>(cfg, themeinator);
    return std::make_shared<Program>(screenController, themeLightController);
}