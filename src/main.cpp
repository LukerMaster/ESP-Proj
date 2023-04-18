#include "Program.h"
#include "ProgramFactory.h"

 std::shared_ptr<Program> p;

uint64_t startTickTime;
uint64_t delayTime;
uint64_t endTickTime;
uint64_t tickTime;
void setup() {
  ProgramFactory f;
  Serial.begin(115200);
  p = f.CreateProgram();
  p->SetTickRate(20);
}

void loop() {
  startTickTime = millis();
  p->Tick(tickTime + delayTime);
  tickTime = millis() - startTickTime;
  delayTime = (1000 / p->GetTickRate() > tickTime) ? 1000 / p->GetTickRate() - tickTime : 0;
  delay(delayTime);
}