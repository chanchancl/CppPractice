
#include "Test.h"

// global
int total = 0;
int pass = 0;
int error = 0;

int main()
{
    TestType_Traits();
    TestVector();
    TestArray();

    return 0;
}