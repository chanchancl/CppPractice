
#include "Test.h"

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line)
{
    total++;
    if (bexpression)
    {
        pass++;
    }
    else
    {
        error++;
        std::cerr << expression << " at file : " << file << "  line : " << line << std::endl;
    }
}