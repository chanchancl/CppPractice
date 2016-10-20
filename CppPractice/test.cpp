
#include <iostream>
#include "CVector.h"

using namespace std;

void main()
{
    {
        sp::CVector<int> v(5,14);
        for (auto a = v.begin(); a != v.end(); ++a)
        {
            cout << *a << endl;
        }
        
    }

}