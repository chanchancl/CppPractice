
#include <iostream>
#include "vector.h"
#include <vector>
#include <list>
using namespace std;

void main()
{
    sp::vector<int> vec;
    vec.push_back(233);
    
    /*for (int i = 0; i < 100000; i++)
    {
        vec.insert(vec.begin(), i);
    }
    vec.insert(vec.begin(), 5);*/
    
    for (int i = 0; i < 100000; i++)
    {
        vec.push_back(i);
    }

    int a = 55;
    cout << a;

    /*for (auto c : vec)
        cout << c << endl;*/
}