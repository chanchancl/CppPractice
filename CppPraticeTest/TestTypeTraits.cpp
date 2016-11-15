
#include <iostream>
#include <string>
#include "type_traits.h"

static int total = 0;
static int pass = 0;
static int error = 0;

template <class T>
inline void EXCEPT(T b, T value, std::string errormsg = "")
{
    total++;
    if (b == value)
    {
        pass++;
    }
    else
    {
        error++;
        std::cerr << errormsg << std::endl;
    }
}

void test_type_traits()
{
    using namespace sp;

    EXCEPT(true_type::value, true, "true_type::value != true");
    EXCEPT(false_type::value, false, "false_type::value != false");



}




