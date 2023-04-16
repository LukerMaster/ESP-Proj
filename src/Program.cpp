#include "Program.h"

void Program::SetTickRate(uint32_t tickRate)
{
    _TickRate = tickRate;
}

void Program::Start()
{
    Serial.println("ESP Program starting.");
    cfg = std::make_shared<Configuration>();

    std::shared_ptr<Themeinator> themeinator = std::make_shared<Themeinator>();
    themeLightController = std::make_shared<ThemeLightController>(cfg->PIN_PHOTORESISTOR_INPUT, themeinator);
    screenController = std::make_shared<ScreenController>(cfg, themeinator);
    
}

uint32_t Program::GetTickRate()
{
    return _TickRate;
}

void Program::Tick(uint64_t millisDelta)
{
  themeLightController->UpdateTheme();
  screenController->Tick(millisDelta);
}
