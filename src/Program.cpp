#include "Program.h"

Program::Program(std::shared_ptr<ScreenAPI> screen, std::shared_ptr<PhotoresistorReader> photoresistor)
{
    Serial.println("ESP Program starting.");
    this->screen = screen;
    this->photoresistor = photoresistor;

    this->colorinator = std::unique_ptr<Colorinator>(new Colorinator());
}

void Program::SetTickRate(uint32_t tickRate)
{
    _TickRate = tickRate;
}

void Program::Start()
{
    Serial.println("Start called.");
    screen->FillScreen(colorinator->GetBgColor());
}

uint32_t Program::GetTickRate()
{
    return _TickRate;
}

void Program::Tick(uint64_t millisDelta)
{
  time += millisDelta;
  if (photoresistor->GetLightLevel() < 0.4f && colorinator->CurrentTheme != Theme::Dark)
  {
    colorinator->CurrentTheme = Theme::Dark;
    screen->FillScreen(colorinator->GetBgColor());
  }
  else if (photoresistor->GetLightLevel() >= 0.4f && colorinator->CurrentTheme != Theme::Standard)
  {
    colorinator->CurrentTheme = Theme::Standard;
    screen->FillScreen(colorinator->GetBgColor());
  }
  screen->SetTextColor(colorinator->GetTextColor());
  screen->SetBgColor(colorinator->GetBgColor());


  screen->SetTextPosition(10, 10);
  screen->SetTextScale(2);
  screen->DrawText("Op time: " + std::to_string(time/1000) + "s");
}
