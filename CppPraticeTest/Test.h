
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <iostream>

#pragma warning(disable:4101) // waring : 未引用的变量

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line);

#define EXCEPT(expression) _EXCEPT((expression), #expression , __FILE__, __LINE__);

//
// when you add a new Unit Test.
//   call Reset( "TestName");
// and at the end.
//   call Report();
//


// Test Functions
void TestType_Traits();
void TestVector();
void TestArray();


#include <vector.h>

typedef std::function<void()> TestFunction;

class UnitTest
{
public:
    int mPass;  // 通过的测试
    int mError; // 发生错误的测试
    int mTotal; // 测试的总数

public:
	std::string  mName;
    TestFunction mFunction;
    
    // 输出
	UnitTest();

};

class TestManager
{
private:
	TestManager();
public:
	// single mode
	static TestManager* GetInstance();
	UnitTest* GetCurrentTest();

	// when you want to add a test
	// the only thing you should do is
	// AddTest( "Array", Test_Array);
	// "Array" is the name of the test
	// Test_Array is the test function;
	void AddTest(std::string testName, TestFunction fun);
	int Size();
	void Run();

private:
	UnitTest *mCurrentTest;
	sp::vector<UnitTest> mTests;
	bool mReport;
};


#endif