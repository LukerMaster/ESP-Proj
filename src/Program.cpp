#include "Program.h"

Program::Program(std::shared_ptr<ScreenAPI> screen, std::shared_ptr<PhotoresistorReader> photoresistor,
std::shared_ptr<AsyncThermometer> thermometer)
{
    Serial.println("ESP Program starting.");
    this->screen = screen;
    this->photoresistor = photoresistor;
    this->thermometer = thermometer;

    this->colorinator = std::unique_ptr<Colorinator>(new Colorinator());

    Serial.println("Preparation of the program started.");

    this->screen->SetTextColor(colorinator->GetTextColor());
    this->screen->SetBgColor(colorinator->GetBgColor());
    this->screen->FillScreen(colorinator->GetBgColor());

    this->temperature = std::make_shared<WatchedValue<float>>();
    this->temperature->OnValueChanged = [this] (float value)
    {
        this->screen->SetTextPosition(5, 5);
        this->screen->SetTextScale(2);
        this->screen->DrawText(std::to_string(value).substr(0, std::to_string(value).find(".") + 2) + "C");
    };

    this->rpm = std::make_shared<WatchedValue<uint64_t>>();
    this->rpm->OnValueChanged = [this] (uint64_t value)
    {
        this->screen->SetTextPosition(10, 50);
        this->screen->SetTextScale(3);
        this->screen->DrawText(std::to_string(value) + "RPM");
    };

    this->screenWidgets.push_back(temperature);
    this->screenWidgets.push_back(rpm);
    
    RefreshWidgets();
}

void Program::SetTickRate(uint32_t tickRate)
{
    _TickRate = tickRate;
}


uint32_t Program::GetTickRate()
{
    return _TickRate;
}

void Program::Tick(uint64_t millisDelta)
{
  if (photoresistor->GetLightLevel() < 0.08f && colorinator->CurrentTheme != Theme::Dark)
  {
    colorinator->CurrentTheme = Theme::Dark;
    screen->FillScreen(colorinator->GetBgColor());
    screen->SetTextColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    RefreshWidgets();
  }
  else if (photoresistor->GetLightLevel() > 0.30f && colorinator->CurrentTheme != Theme::Standard)
  {
    colorinator->CurrentTheme = Theme::Standard;
    screen->FillScreen(colorinator->GetBgColor());
    screen->SetTextColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    RefreshWidgets();
  }

    

  temperature->Set(thermometer->GetTemperature());
  rpm->Set(rpm->Get() + millisDelta);

  
}

void Program::RefreshWidgets()
{
    std::for_each(screenWidgets.begin(), screenWidgets.end(), [](std::shared_ptr<INotifiable> obj) { obj->Notify(); });
}
