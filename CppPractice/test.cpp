
#include <iostream>
#include "vector.h"
#include "array.h"
#include <vector>
using namespace std;


void test_vector()
{
    sp::vector<int> vec;
    vec.push_back(233);
    
    /*for (int i = 0; i < 100000; i++)
    {
        vec.insert(vec.begin(), i);
    }*/
    vec.insert(vec.begin(), 5);
    
    for (int i = 0; i < 100000; i++)
    {
        vec.push_back(i);
    }
}

void test_array()
{
    sp::array<int, 5> a;
}

void main()
{
    test_vector();
    test_array();

    
}