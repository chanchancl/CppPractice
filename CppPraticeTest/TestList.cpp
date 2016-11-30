
#include "Test.h"
#include <list.h>

void TestList()
{
	using namespace sp;
	list<int> li1;
	list<int> li2(100,2);
	list<int> li3(li2);
	list<TestObject> li4;

	EXCEPT(li1.empty());
	EXCEPT(li2.size() == 100);
	EXCEPT(li3.size() == 100);
	EXCEPT(li4.size() == 0  );

	for (auto it = li2.begin(); it != li2.end(); ++it)
		EXCEPT(*it == 2);

	li2.front() = 5;
	li2.back() = 5;
	EXCEPT(li2.front() == li2.back());

	li1.clear();
	li2.clear();
	for (int i = 1; i <= 100; ++i)
	{
		li1.push_back(i);
		li2.push_front(101 - i);
	}
	EXCEPT(li1 == li2);

	li1.erase(find(li1.begin(), li1.end(), 50), li1.end());
	int i = 50;
	while (i--)
		li2.erase(--li2.end());
	EXCEPT(li1 == li2);

	TestObject::Reset();
	for (int i = 0; i < 100; ++i)
		li4.push_back(TestObject());

	EXCEPT(TestObject::Alive == 100 );

	li4.clear();
	EXCEPT(TestObject::Alive == 0);
}