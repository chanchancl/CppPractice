


#include <vector.h>
#include <array.h>

#include <iostream>
#include <vector>
using namespace std;

void main()
{
    sp::vector<int> vec;

    for (int i = 0; i < 100000; ++i)
    {
        vec.insert(vec.begin(),i);
    }

}