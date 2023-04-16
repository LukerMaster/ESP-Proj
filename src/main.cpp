#include "Program.h"

Program p;

uint64_t startTickTime;
uint64_t delayTime;
uint64_t endTickTime;
uint64_t tickTime;
void setup() {
  Serial.begin(115200);
  p.SetTickRate(20);
  p.Start();
}

void loop() {
  startTickTime = millis();
  p.Tick(tickTime + delayTime);
  tickTime = millis() - startTickTime;
  delayTime = (1000 / p.GetTickRate() > tickTime) ? 1000 / p.GetTickRate() - tickTime : 0;
  delay(delayTime);
}