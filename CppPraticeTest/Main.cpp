
#include "Test.h"


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