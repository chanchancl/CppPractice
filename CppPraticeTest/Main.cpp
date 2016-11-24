
#include "Test.h"

// global
int total = 0;
int pass = 0;
int error = 0;

int main()
{
    using namespace std;
    
	TestManager *tm = TestManager::GetInstance();

	tm->AddTest("Type_Traits", TestType_Traits);
	tm->AddTest("Vector",      TestVector);
	tm->AddTest("Array",       TestArray);
	
	tm->Run();

    return 0;
}