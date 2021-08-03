#include "IronGrassEngine.h"

void plog(const char* message)
{
#if _DEBUG
    std::cout << message;
#endif
}

void plogln(const char* message)
{
#if _DEBUG
    plog(message);
    plog("\n");
#endif
}
