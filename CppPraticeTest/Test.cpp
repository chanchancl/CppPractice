
#include "Test.h"

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line)
{
	UnitTest *Current = TestManager::GetInstance()->GetCurrentTest();
	Current->mTotal++;
	if (bexpression)
	{
		Current->mPass++;
	}
	else
	{
		Current->mError++;
		std::cerr << expression << " at file : " << file << "  line : " << line << std::endl;
	}
}

void Reset(const char* name)
{
	/*using namespace std;
	total = pass = error = 0;
	cout << "Test " << setw(15) << setiosflags(ios::left) << name;*/

}

void Report()
{
	/*using namespace std;
	cout << setw(4) << resetiosflags(ios::left) << pass << '/'
		 << setw(5) << error << '/'
		 << setw(5) << total << " ("
		 << showpoint << setprecision(5) << (pass / float(total) * 100) << '%' << ')' << endl;*/
}


UnitTest::UnitTest() : mPass(0), mError(0), mTotal(0) {}


TestManager::TestManager() : mCurrentTest(nullptr)
{
}

TestManager* TestManager::GetInstance()
{
	static TestManager Instance;
	return &Instance;
}

UnitTest * TestManager::GetCurrentTest()
{
	return mCurrentTest;
}

void TestManager::AddTest(std::string testName, TestFunction fun)
{
	UnitTest test;
	test.mName = testName;
	test.mFunction = fun;

	mTests.push_back(test);
}

int TestManager::Size()
{
	return mTests.size();
}

void TestManager::Run()
{
	using namespace std;
	for (auto& test : mTests)
	{
		// test begin
		cout << "Test " << test.mName << endl;
		mCurrentTest = &test; // for EXCEPT
		test.mFunction();
	}
	mCurrentTest = nullptr;

	// test end and report
	cout << "*******************************************************" << endl;
	cout << setw(20) << setiosflags(ios::left) << "TestName" 
		 << resetiosflags(ios::left) << "Pass/Error/Total" << setw(18) <<"STATUS"<< endl;
	for (const auto test : mTests)
	{
		cout << setw(20)<< setiosflags(ios::left)   << test.mName ;
		cout << setw(4) << resetiosflags(ios::left) << test.mPass << '/'
			 << setw(5) << test.mError << '/'
			 << setw(5) << test.mTotal << " ("
			 << showpoint << setprecision(5) << (test.mPass / float(test.mTotal) * 100) << '%' << ')';
		if (test.mError == 0)
			cout << "\tPASSED";
		else
			cout << "\tFAILED";
		cout << endl;
	}
	cout << "*******************************************************" << endl;
}