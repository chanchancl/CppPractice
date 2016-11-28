
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <iostream>

#pragma warning(disable:4101) // waring : 未引用的变量

// Test Functions
void TestType_Traits();
void TestVector();
void TestArray();
void TestList();

void   _EXCEPT(bool bexpression, const std::string& expression, const std::string& file, long line);
#define EXCEPT(expression) _EXCEPT((expression), #expression , __FILE__, __LINE__);

#include <vector.h>

// wraper of test function
typedef std::function<void()> TestFunction;

class UnitTest
{
public:
    int mPass;  // count of passed EXCEPT  通过的测试
    int mError; // count of error  EXCEPT  发生错误的测试
    int mTotal; // count of total  EXCEPT  测试的总数

public:
	std::string  mName;
    TestFunction mFunction;
    
	UnitTest();
};

class TestManager
{
private:
	TestManager();
public:
	// single mode
	static TestManager* GetInstance();

	// during a test,you can use this to get the current test
	// for modify the test data.
	UnitTest* GetCurrentTest();

	// when you want to add a test the only thing you should to do 
	// is call AddTest( "Array", Test_Array);
	// "Array" is the name of the test
	// Test_Array is the test function;
	void AddTest(std::string testName, TestFunction fun);
	int  Size();  // count of tests.
	void Run();  // Let's go

private:
	UnitTest*            mCurrentTest; // only availble when a test function is calling.
	// 学以致用 233
	sp::vector<UnitTest> mTests;	   // store the tests
	bool                 mReport;	   // whether report the errors' information of test.
};


#define TEST_OBJECT_OUTPUT 1

class TestObject
{
public:
	TestObject()
	{
		++Alive;
		++ConstructCount;
		_count = ++DefaultConstruct;
#if TEST_OBJECT_OUTPUT
		std::cout << "Test Object :            " << _count << " Construct" << std::endl;
#endif
	}
	TestObject(const TestObject& obj)
	{
		++Alive;
		++ConstructCount;
		++CopyConstruct;
		_count = obj._count;
	}
	TestObject(TestObject&& obj)
	{
		++Alive;
		++ConstructCount;
		++MoveConstruct;
		if (this != &obj)
		{
			_count = obj._count;
			obj._count = 0;
		}
	}
	TestObject& operator=(const TestObject& obj)
	{
		++AssignCopyConstruct;

		if (this != &obj)
			_count = obj._count;

		return *this;
	}

	TestObject& operator=(TestObject&& obj)
	{
		++MoveAssignment;
		if (this != &obj)
		{
			sp::swap(_count, obj._count);
		}
	}

	~TestObject()
	{
		--Alive;
		++DestroyCount;
#if TEST_OBJECT_OUTPUT
		if (_count > 0)
			std::cout << "Test Object : " << _count << " Destroy" << std::endl;
#endif
	}

	static void Reset()
	{
		Alive = 0;
		DefaultConstruct = 0;
		CopyConstruct = 0;
		MoveConstruct = 0;
		AssignCopyConstruct = 0;
		MoveAssignment = 0;
		ConstructCount = 0;
		DestroyCount = 0;
	}

	int _count;
	static int Alive;
	static int DefaultConstruct;
	static int CopyConstruct;
	static int MoveConstruct;
	static int AssignCopyConstruct;
	static int MoveAssignment;
	static int ConstructCount;
	static int DestroyCount;
};



#endif