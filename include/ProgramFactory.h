#include <Program.h>
#include <Configuration.h>

class ProgramFactory
{
public:
    std::shared_ptr<Program> CreateProgram();
};