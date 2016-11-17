
#include "Test.h"

// global
int total = 0;
int pass = 0;
int error = 0;

int main()
{
    using namespace std;
    cout << setw(20)<< "" << "pass/error/total" << endl;
    TestType_Traits();
    TestVector();
    TestArray();

    return 0;
}