

#include <algorithm>
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

	for (int i = 1; i <= 100000; ++i)
		li.push_back(i);

	cout << sp::count_if(li.begin(), li.end(), [](int x) {
		return x % 3 == 0;
	}) << endl;

}