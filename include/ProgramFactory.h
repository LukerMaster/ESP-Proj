#include <Program.h>

class ProgramFactory
{
public:
    std::shared_ptr<Program> CreateProgram();
};