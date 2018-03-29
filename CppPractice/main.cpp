

#include <algorithm>
#include <vector.h>
#include <array.h>
#include <list>
#include <list.h>
#include <normal_tree.h>
#include <map>

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void main()
{
    sp::vector<int> vec;
	//sp::array<int,5> arr;
	sp::list<int>  li1;
	std::list<int> li2;
	std::map<int, int> a;
	int c,d;
	std::swap(c, d);
	
	sp::normaltree<int> tree;
	tree.insert(1);
	tree.insert(100);
	tree.insert(200);
	tree.insert(50);

}