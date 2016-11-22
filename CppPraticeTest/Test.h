
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <iostream>

#pragma warning(disable:4101) // waring : 未引用的变量

extern int total;
extern int pass;
extern int error;

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line);

#define EXCEPT(expression) _EXCEPT((expression), #expression , __FILE__, __LINE__);

//
// when you add a new Unit Test.
//   call Reset( "TestName");
// and at the end.
//   call Report();
//
void Reset(const char*);

void Report();




// Test Functions
void TestType_Traits();
void TestVector();
void TestArray();


typedef std::function<void()> TestFunction;

class UnitTest
{
public:
    int mPass;  // 通过的测试
    int mError; // 发生错误的测试
    int mTotal; // 测试的总数

public:
    TestFunction mFunction;
    
    // 输出
    // 

};



#endif