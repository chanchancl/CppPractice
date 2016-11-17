
#include "Test.h"
#include <array.h>

void TestArray()
{
    using namespace sp;
    int i;

    Reset("array");

    array<int, 5> a = { 0, 1, 2, 3, 4 };
    array<int, 5> b = { 1, 1, 1, 1, 1 };
    array<int, 5> c;

    for (i = 0; i < 5; ++i)
        EXCEPT(a[i] == i);

    c.fill(1);
    EXCEPT(b == c);

    for (i = 0; i < 5; ++i)
        b[i] = a[i];
    EXCEPT(b == a);
    
    Report();
}
