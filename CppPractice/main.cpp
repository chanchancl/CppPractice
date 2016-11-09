
#include <iostream>

using namespace std;

void main()
{
    double && rref = std::sqrt(36.00);
    double j = 15;
    double && jref = 2.0*j + 18.5;
    std::cout << rref << '\n';
    std::cout << jref << '\n';
}