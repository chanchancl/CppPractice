

#include <algorithm>
#include <vector.h>
#include <array.h>
#include <list.h>
#include <normal_tree.h>

#include <iostream>
#include <vector>
using namespace std;

void main()
{
    sp::vector<int> vec;
	//sp::array<int,5> arr;
	sp::list<int> li;
	
	sp::normaltree<int> tree;
	tree.insert(1);
	tree.insert(100);
	tree.insert(200);
	tree.insert(50);

}