#include "RandomCarInput.h"

RandomCarInput::RandomCarInput(std::shared_ptr<CarInfo> car)
{
    carInfo = car;
}

void RandomCarInput::AddRandomInputsToCar(float deltaTime)
{
  carInfo->SetFuelPercentage(carInfo->GetFuelPercentage() - deltaTime/300000);
  carInfo->SetSpeed(carInfo->GetSpeed() + (deltaTime/6000 * std::max(0, 380 - carInfo->GetSpeed())));
  carInfo->SetOdometer(carInfo->GetOdometerReading() + (float)carInfo->GetSpeed()/20);
  carInfo->SetTripometer(carInfo->GetTripometerReading() + (float)carInfo->GetSpeed()/20);
  carInfo->SetEngineRpm(carInfo->GetEngineRpm() + deltaTime/3 * ((float)carInfo->GetMaxRpm() / carInfo->GetEngineRpm()));
  if (carInfo->GetEngineRpm() > carInfo->GetMaxRpm())
  {
    carInfo->SetEngineRpm(1000);
    carInfo->SetCurrentGear(carInfo->GetCurrentGear() + 1);
  }
  if (carInfo->GetCurrentGear() > carInfo->GetNumOfForwardGears())
  {
    carInfo->SetCurrentGear(1);
  }
}

void RandomCarInput::AddTime(uint32_t millis)
{
  millisSinceLastUpdate += millis;
  if (millisSinceLastUpdate > maxMillis)
  {
    AddRandomInputsToCar(millisSinceLastUpdate);
    millisSinceLastUpdate = 0;
  }
}

void RandomCarInput::SetTimeBetweenUpdates(uint32_t millis)
{
  maxMillis = millis;
}
