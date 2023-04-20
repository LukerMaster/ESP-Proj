#include "Program.h"

Program::Program(std::shared_ptr<ScreenAPI> screen, std::shared_ptr<PhotoresistorReader> photoresistor,
std::shared_ptr<AsyncThermometer> thermometer)
{
    Serial.println("ESP Program starting.");
    this->screen = screen;
    this->photoresistor = photoresistor;
    this->thermometer = thermometer;

    this->colorinator = std::unique_ptr<Colorinator>(new Colorinator());
    this->carInfo = std::make_shared<CarInfo>();
    this->randomInputs = std::make_shared<RandomCarInput>(carInfo);

    Serial.println("Preparation of the program started.");

    this->screen->SetFgColor(colorinator->GetTextColor());
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
        this->screen->SetTextPosition(10, 30);
        this->screen->SetTextScale(1);
        this->screen->DrawText("RPM:" + std::to_string(value));
        this->screen->DrawProgressBar(10, 
        40, 
        this->screen->GetScreenSizeX()-20, 
        50, 
        (float)value / carInfo->GetMaxRpm());
    };

    this->kmph = std::make_shared<WatchedValue<uint32_t>>();
    this->kmph->OnValueChanged = [this] (uint32_t value)
    {
        this->screen->SetTextPosition(20, 150);
        this->screen->SetTextScale(8);
        this->screen->DrawText(std::to_string(value));
        
        this->screen->SetTextPosition(this->screen->GetScreenSizeX() - 80, 150);
        this->screen->SetTextScale(3);
        this->screen->DrawText("KM/H");
    };

    this->fuelPercentage = std::make_shared<WatchedValue<float>>();
    this->fuelPercentage->OnValueChanged = [this] (float value)
    {
        this->screen->SetTextPosition(10, this->screen->GetScreenSizeY() - 40);
        this->screen->SetTextScale(1);
        this->screen->DrawText("Fuel:");
        this->screen->DrawProgressBar(10, 
        this->screen->GetScreenSizeY() - 30, 
        this->screen->GetScreenSizeX() - 20, 
        20, 
        value);
    };

    this->gear = std::make_shared<WatchedValue<int16_t>>();
    this->gear->OnValueChanged = [this] (int16_t value)
    {
        this->screen->SetTextPosition(this->screen->GetScreenSizeX()-70,
        95);
        this->screen->SetTextScale(1);
        this->screen->DrawText("Gear:");
        this->screen->SetTextPosition(this->screen->GetScreenSizeX()-50,
        110);
        this->screen->SetTextScale(5);
        this->screen->DrawText(std::to_string(value));
    };
    this->odometer = std::make_shared<WatchedValue<uint64_t>>();
    this->odometer->OnValueChanged = [this] (uint64_t value)
    {
        this->screen->SetTextPosition(10, this->screen->GetScreenSizeY() - 80);
        this->screen->SetTextScale(2);
        this->screen->DrawText(std::to_string(value));
    };
    this->tripometer = std::make_shared<WatchedValue<uint64_t>>();
    this->tripometer->OnValueChanged = [this] (uint64_t value)
    {
        this->screen->SetTextPosition(10, this->screen->GetScreenSizeY() - 60);
        this->screen->SetTextScale(2);
        this->screen->DrawText(std::to_string(value));
    };

    this->screenWidgets.push_back(temperature);
    this->screenWidgets.push_back(rpm);
    this->screenWidgets.push_back(kmph);
    this->screenWidgets.push_back(fuelPercentage);
    this->screenWidgets.push_back(gear);
    this->screenWidgets.push_back(odometer);
    this->screenWidgets.push_back(tripometer);
    
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
    screen->SetFgColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    RefreshWidgets();
  }
  else if (photoresistor->GetLightLevel() > 0.30f && colorinator->CurrentTheme != Theme::Standard)
  {
    colorinator->CurrentTheme = Theme::Standard;
    screen->FillScreen(colorinator->GetBgColor());
    screen->SetFgColor(colorinator->GetTextColor());
    screen->SetBgColor(colorinator->GetBgColor());
    RefreshWidgets();
  }

  randomInputs->AddTime(millisDelta);

  ReadCarValuesToWidgets();
}

void Program::RefreshWidgets()
{
    std::for_each(screenWidgets.begin(), screenWidgets.end(), [](std::shared_ptr<INotifiable> obj) { obj->Notify(); });
}


void Program::ReadCarValuesToWidgets()
{
    temperature->Set(thermometer->GetTemperature());
    rpm->Set(carInfo->GetEngineRpm());
    kmph->Set(carInfo->GetSpeed());
    gear->Set(carInfo->GetCurrentGear());
    fuelPercentage->Set(carInfo->GetFuelPercentage());
    odometer->Set(carInfo->GetOdometerReading());
    tripometer->Set(carInfo->GetTripometerReading());
}
