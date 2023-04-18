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

    screen->SetTextColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    screen->FillScreen(colorinator->GetBgColor());

    opTimeSeconds = std::make_shared<WatchedValue<uint64_t>>();
    opTimeSeconds->OnValueChanged = [this] (uint64_t value)
    {
        screen->SetTextPosition(10, 10);
        screen->SetTextScale(2);
        screen->DrawText("Op time: " + std::to_string(value) + "s");
    };

    rpm = std::make_shared<WatchedValue<uint64_t>>();
    rpm->OnValueChanged = [this] (uint64_t value)
    {
        screen->SetTextPosition(10, 50);
        screen->SetTextScale(3);
        screen->DrawText(std::to_string(value) + "RPM");
    };

    screenWidgets.push_back(opTimeSeconds);
    screenWidgets.push_back(rpm);
    
    RefreshWidgets();
}

uint32_t Program::GetTickRate()
{
    return _TickRate;
}

void Program::Tick(uint64_t millisDelta)
{
  
  if (photoresistor->GetLightLevel() < 0.7f && colorinator->CurrentTheme != Theme::Dark)
  {
    colorinator->CurrentTheme = Theme::Dark;
    screen->FillScreen(colorinator->GetBgColor());
    screen->SetTextColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    RefreshWidgets();
  }
  else if (photoresistor->GetLightLevel() >= 0.7f && colorinator->CurrentTheme != Theme::Standard)
  {
    colorinator->CurrentTheme = Theme::Standard;
    screen->FillScreen(colorinator->GetBgColor());
    screen->SetTextColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    RefreshWidgets();
  }

  rpm->Set(rpm->Get() + millisDelta);
}

void Program::RefreshWidgets()
{
    std::for_each(screenWidgets.begin(), screenWidgets.end(), [](std::shared_ptr<INotifiable> obj) { obj->Notify(); });
}
