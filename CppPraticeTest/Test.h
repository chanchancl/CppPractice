
#ifndef _TEST_H_
#define _TEST_H_

#include <iostream>
#include <string>

#pragma warning(disable:4101) // waring : δ���õı���

extern int total;
extern int pass;
extern int error;

void _EXCEPT(bool bexpression, std::string expression, std::string file, long line);

#define EXCEPT(expression) _EXCEPT((expression), #expression , __FILE__, __LINE__);



void test_type_traits();



#endif