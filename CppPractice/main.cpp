
#include <iostream>
#include <vector.h>
#include <vector>
using namespace std;

void main()
{
    std::vector<int> vec;

    for (int i = 0; i < 100000; ++i)
    {
        vec.insert(vec.begin(),i);
    }


    double && rref = std::sqrt(36.00);
    double j = 15;
    double && jref = 2.0*j + 18.5;
    std::cout << &rref << '\n';
    std::cout << &jref << '\n';
}