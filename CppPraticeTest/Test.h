
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <iomanip>
#include <string>

#pragma warning(disable:4101) // waring : δ���õı���

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

#endif