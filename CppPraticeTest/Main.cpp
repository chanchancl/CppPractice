
#include "Test.h"


int main()
{
    using namespace std;
    
	// Get TestManager
	TestManager *tm = TestManager::GetInstance();

	// Add tests.
	tm->AddTest("Type_Traits", TestType_Traits);
	tm->AddTest("Vector",      TestVector);
	tm->AddTest("Array",       TestArray);
	tm->AddTest("List",        TestList);
	// Run tests.
	tm->Run();

    return 0;
}