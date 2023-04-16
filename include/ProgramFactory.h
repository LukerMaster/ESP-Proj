#include <Program.h>

class ProgramFactory
{
    std::shared_ptr<Program> CreateProgram();
};