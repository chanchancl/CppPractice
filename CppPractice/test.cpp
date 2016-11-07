
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
    
    /*for (int i = 0; i < 100000; i++)
    {
        vec.push_back(i);
    }*/

    vec.clear();

    for (int i = 0; i < 100000; i++)
    {
        vec.insert(vec.begin(), i);
    }

    cout << vec.size() << endl;
    cout << vec.count << endl;
}

void test_array()
{
}

void main()
{
    test_vector();
    test_array();

    
}