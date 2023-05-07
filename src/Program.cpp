#include "Program.h"

void Program::Tick(float deltaTime)
{
    carSimulation->Tick(deltaTime);
    readerLogic->PerformIO();
}