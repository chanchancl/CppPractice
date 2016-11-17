
#include <vector>
#include <vector.h>
#include "Test.h"

#define TEST_OBJECT_OUTPUT 1

class TestObject
{
public:
    TestObject() : _count(ConstructCount++)
    {
        #if TEST_OBJECT_OUTPUT
            std::cout << "Test Object :            " << _count << " Construct" << std::endl;
        #endif
    }
    ~TestObject()
    {
        ++DestroyCount;
        #if TEST_OBJECT_OUTPUT
            std::cout << "Test Object : " << _count << " Destroy" << std::endl;
        #endif
    }

    int _count;
    static int ConstructCount;
    static int DestroyCount;
};

// ¶¨Òåstatic class member
int TestObject::ConstructCount = 0;
int TestObject::DestroyCount = 0;


void TestVector()
{
    using namespace sp;
    int i;

    sp::vector<TestObject> vec4;
    for (i = 0; i < 100; ++i)
        vec4.push_back(TestObject());


    vector<int> vec1;
    vector<int> vec2(100, 2);
    vector<int> vec3 = vec2;
    

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

    // 

    int aaa = 5;
}