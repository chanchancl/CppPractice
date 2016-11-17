
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <iomanip>
#include <string>

#pragma warning(disable:4101) // waring : 未引用的变量

extern int total;
extern int pass;
extern int error;

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line);

#define EXCEPT(expression) _EXCEPT((expression), #expression , __FILE__, __LINE__);

void Reset(const char*);

void Report();




// Test Functions
void TestType_Traits();
void TestVector();
void TestArray();

#endif