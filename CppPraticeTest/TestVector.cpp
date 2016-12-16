
#include <vector>
#include <vector.h>
#include "Test.h"
#include <sort.h>

void TestVector()
{
    using namespace sp;
    int i;

    vector<int> vec1;
    vector<int> vec2(100, 2);
    vector<int> vec3(vec2);
	vector<TestObject> vec4;
    
	EXCEPT(vec1.size() == 0  );
	EXCEPT(vec2.size() == 100);
	EXCEPT(vec3.size() == 100);
	EXCEPT(vec4.size() == 0  );

    vector<int>::iterator it;
    vector<int>::const_iterator cit = vec2.begin();
    vector<int>::reverse_iterator rit;
    vector<int>::const_reverse_iterator crit;

    it = vec1.begin();
    it = vec1.end();
    auto cit1 = vec1.rbegin();
    auto cit2 = vec1.rend();
    rit = vec1.rbegin();
    rit = vec1.rend();

    EXCEPT(vec1.begin() == vec1.end());
    EXCEPT(vec1.size() == 0);
    EXCEPT(vec1.capacity() == 0);


    for (i = 0; i < 100; ++i)
        vec1.push_back(2);

    EXCEPT(vec1 == vec2);

    bool flag = true;
    for (i = 0; i < 100; ++i)
        if (vec1[i] != vec2[i])
            flag = false;

    EXCEPT(flag == true);

    vec1.clear();
    vec2.clear();
    EXCEPT(vec1.size() == 0);
    EXCEPT(vec2.size() == 0);

    vec1 = vec3;
    vec2 = vec3;
    EXCEPT(vec1 == vec2);

    for (auto it = vec3.begin(); it != vec3.end(); ++it)
        *it += 1;
    for (i = 0; i < (int)vec3.size(); ++i)
        EXCEPT(vec3[i] == 3);

    vec1.clear();
    vec2.clear();
    for (i = 0; i < 100; ++i)
    {
        vec1.insert(vec1.begin(), 99 - i);
        vec2.insert(vec2.end(), i);
    }
    EXCEPT(vec1 == vec2);

    for (i = 0; i < 50; ++i)
    {
        vec1.pop_back();
        vec2.pop_back();
    }
    EXCEPT(vec1 == vec2);

	vec1.clear();
	vec2.clear();
	for (i = 0; i < 50; ++i)
	{
		vec1.push_back(i);
		vec2.push_back(50-i-1);
	}
	//bubble_sort(vec2.begin(), vec2.end());
	selection_sort(vec2.begin(), vec2.end());
	EXCEPT(is_sorted(vec1.begin(), vec1.begin()));
	EXCEPT(is_sorted(vec2.begin(), vec2.begin()));
	EXCEPT(vec1 == vec2);
    // 
    //sp::vector<TestObject> vec4;
    for (i = 0; i < 100; ++i)
        vec4.push_back(TestObject());

    // 此时有100个对象存活，
    // 析构函数的调用次数应比 构造函数少100次
    EXCEPT(TestObject::Alive == 100);
    EXCEPT(TestObject::ConstructCount == TestObject::DefaultConstruct 
           + TestObject::AssignCopyConstruct + TestObject::CopyConstruct);
    EXCEPT(TestObject::ConstructCount == TestObject::DestroyCount + 100);

    vec4.clear();

    // 对象全部销毁
    EXCEPT(TestObject::Alive == 0);
    EXCEPT(TestObject::ConstructCount == TestObject::DestroyCount);

}