#include "Program.h"

Program::Program(std::shared_ptr<ScreenController> screenCtrl, std::shared_ptr<ThemeLightController> themeCtrl)
{
    Serial.println("ESP Program starting.");
    this->screenController = screenCtrl;
    this->themeLightController = themeCtrl;
}

void Program::SetTickRate(uint32_t tickRate)
{
    _TickRate = tickRate;
}

void Program::Start()
{
    Serial.println("Start called.");
}

uint32_t Program::GetTickRate()
{
    return _TickRate;
}

void Program::Tick(uint64_t millisDelta)
{
  themeLightController->UpdateTheme();
  if (themeLightController->ScreenNeedsFullRedraw)
  {
    screenController->RedrawEverything();
    themeLightController->ScreenNeedsFullRedraw = false;
  }
  screenController->Tick(millisDelta);
}
