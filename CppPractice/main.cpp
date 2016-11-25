


#include <vector.h>
#include <array.h>
#include <list.h>

#include <iostream>
#include <vector>
using namespace std;

void main()
{
    sp::vector<int> vec;
	sp::array<int,5> arr;
	sp::list<int> li;

	auto it = li.begin();
	for (int i = 0; i < 100000; ++i)
    {
        vec.insert(vec.begin(),i);
    }

}