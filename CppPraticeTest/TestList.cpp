
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

	TestObject::Reset();
	for (int i = 0; i < 100; ++i)
		li4.push_back(TestObject());

	EXCEPT(TestObject::Alive == 100 );

	li4.clear();
	EXCEPT(TestObject::Alive == 0);
}