#include "Program.h"
#include "CarSimWebServer.h"
#include "ProgramFactory.h"

std::shared_ptr<Program> p;
uint64_t desiredTickRate;

uint64_t startTickTime;
uint64_t delayTime;
uint64_t tickTime;
void setup() {
  ProgramFactory f;
  Serial.begin(115200);
  p = f.CreateProgram();
  desiredTickRate = 20;
}

void loop() {
  startTickTime = millis();
  p->Tick((float)(tickTime + delayTime)/1000.f);
  tickTime = millis() - startTickTime;
  delayTime = (1000 / desiredTickRate > tickTime) ? 1000 / desiredTickRate - tickTime : 0;
  delay(delayTime);
}