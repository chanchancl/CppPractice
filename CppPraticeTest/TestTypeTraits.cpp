

#include <type_traits.h>
#include "Test.h"

using namespace sp;

bool GetType(true_type)
{
    return true;
}

bool GetType(false_type)
{
    return false;
}

void test_type_traits()
{
    using namespace sp;

    // base type_traits
    {
        // integral_constant 
        // true_type  false_type
        // bool_constant
        EXCEPT(GetType(integral_constant<bool, true>()) == true);
        EXCEPT(true_type::value == true);
        EXCEPT(false_type::value == false);
        EXCEPT(GetType(bool_constant<true>()) == true);

        // type_or
        type_or<true, true, true, true, true>      to1;
        type_or<false, false, false, false, false> to2;
        type_or<true, false, false, false, false>  to3;
        EXCEPT(to1.value == true);
        EXCEPT(to2.value == false);
        EXCEPT(to3.value == true);

        // type_and
        type_and<true, true, true, true, true>      ta1;
        type_and<false, false, false, false, false> ta2;
        type_and<true, false, false, false, false>  ta3;
        EXCEPT(ta1.value == true);
        EXCEPT(ta2.value == false);
        EXCEPT(ta3.value == false);

        // type_equal
        type_equal<true, true>  te1;
        type_equal<true, false> te2;
        EXCEPT(te1.value == true);
        EXCEPT(te2.value == false);

        // type_not_equal
        type_not_equal<true, true>  tne1;
        type_not_equal<true, false> tne2;
        EXCEPT(tne1.value == false);
        EXCEPT(tne2.value == true);

        // type_not
        type_not<true>  tn1;
        type_not<false> tn2;
        EXCEPT(tn1.value == false);
        EXCEPT(tn2.value == true);

        // is_same
        struct _IS {};
        EXCEPT(GetType(is_same<int,int>()) == true);
        EXCEPT(GetType(is_same<int, long>()) == false);
        EXCEPT(GetType(is_same<_IS, _IS>()) == true);
        EXCEPT(GetType(is_same<int, _IS>()) == false);

        // is_const
        EXCEPT(is_const<int>::value == false);
        EXCEPT(is_const<const int>::value == true);
        EXCEPT(is_const<const volatile int>::value == true);
        EXCEPT(is_const<const int&>::value == false);


    }


}




