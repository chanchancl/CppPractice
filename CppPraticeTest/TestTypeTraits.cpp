

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

struct Pod1 {};
struct Pod2
{
    int a;
    int b;
};
DECLARE_POD_TYPE(Pod1);
DECLARE_POD_TYPE(Pod2);

void TestType_Traits()
{
    using namespace sp;

    Reset("type_traits");

    // base type_traits
    {
        // integral_constant 
        // true_type  false_type
        // bool_constant
        
        EXCEPT(true_type::value == true);
        EXCEPT(false_type::value == false);
        EXCEPT(GetType(integral_constant<bool, true>()) == true);
        EXCEPT(GetType(bool_constant<true>()) == true);

        // type_or
        static_assert(type_or<true, true, true, true, true>::value == true       , "type_or failure");
        static_assert(type_or<false, false, false, false, false>::value == false , "type_or failure");
        static_assert(type_or<true, false, false, false, false>::value == true   , "type_or failure");

        // type_and
        static_assert(type_and<true, true, true, true, true>::value == true, "type_and failure");
        static_assert(type_and<false, false, false, false, false>::value == false, "type_and failure");
        static_assert(type_and<true, false, false, false, false>::value == false, "type_and failure");

        // type_equal
        static_assert(type_equal<true, true>::value == true, "type_equal failure");
        static_assert(type_equal<true, false>::value == false, "type_equal failure");

        // type_not_equal
        static_assert(type_not_equal<true, true>::value == false, "type_not_equal failure");
        static_assert(type_not_equal<true, false>::value == true, "type_not_equal failure");

        // type_not
        EXCEPT(type_not<true>::value == false);
        EXCEPT(type_not<false>::value == true);

        // is_same
        struct _IS {};
        EXCEPT(GetType(is_same<int,int>()) == true);
        EXCEPT(GetType(is_same<int, long>()) == false);
        EXCEPT(GetType(is_same<_IS, _IS>()) == true);
        EXCEPT(GetType(is_same<int, _IS>()) == false);

        // is_const
        EXCEPT(is_const<const int>::value == true);
        EXCEPT(is_const<int>::value == false);
        EXCEPT(is_const<const volatile int>::value == true);
        EXCEPT(is_const<const int&>::value == false);

        // is_volatile
        EXCEPT(is_volatile<volatile int>::value == true);
        EXCEPT(is_volatile<int>::value == false);
        EXCEPT(is_volatile<volatile long>::value == true);
        EXCEPT(is_volatile<const volatile int>::value == true);
        EXCEPT(is_volatile<const int&>::value == false);

        // is_void
        EXCEPT(is_void<void>::value == true);
        EXCEPT(is_void<const void>::value == true);
        EXCEPT(is_void<int>::value == false);

        // is_null_ptr
        EXCEPT(is_null_pointer<std::nullptr_t>::value == true);
        EXCEPT(is_null_pointer<void*>::value == false);
        EXCEPT(is_null_pointer<int*>::value == false);

        // is_integral
        EXCEPT(is_integral<int>::value == true);
        EXCEPT(is_integral<const int>::value == true);
        EXCEPT(is_integral<float>::value == false);

        // is_floating_point
        EXCEPT(is_floating_point<float>::value == true);
        EXCEPT(is_floating_point<long double>::value == true);
        EXCEPT(is_floating_point<const float>::value == true);
        EXCEPT(is_floating_point<int>::value == false);

        // is_arithmetic
        class is_arithmetic_tmp {};
        EXCEPT(is_arithmetic<int>::value == true);
        EXCEPT(is_arithmetic<float>::value == true);
        EXCEPT(is_fundamental<char>::value == true);
        EXCEPT(is_arithmetic<is_arithmetic_tmp> ::value == false);

        // is_fundamental
        class is_fundamental_tmp {};
        EXCEPT(is_fundamental<int>::value == true);
        EXCEPT(is_fundamental<float>::value == true);
        EXCEPT(is_fundamental<char>::value == true);
        EXCEPT(is_fundamental<is_fundamental_tmp>::value == false);

        // is_array
        typedef char array[8];
        typedef const char array_const[8];
        EXCEPT(is_array<array>::value == true);
        EXCEPT(is_array<array_const>::value == true);
        EXCEPT(is_array<int[]>::value == true);
        EXCEPT(is_array<int>::value == false);
        EXCEPT(is_array<int*>::value == false);

        // is_reference
        EXCEPT(is_reference<int&>::value == true);
        EXCEPT(is_reference<const int&>::value == true);
        EXCEPT(is_reference<array&>::value == true);
        EXCEPT(is_reference<int*>::value == false);

        // is_member_function_pointer
        class Class {};
        EXCEPT(is_member_function_pointer<int>::value == false);
        EXCEPT(is_member_function_pointer<int(Class::*)>::value == false);
        EXCEPT(is_member_function_pointer<int(Class::*)()>::value == true);
        EXCEPT(is_member_function_pointer<int(Class::*)(int)>::value == true);

        // is_member_object_pointer
        EXCEPT(is_member_object_pointer<int>::value == false);
        EXCEPT(is_member_object_pointer<int(Class::*)>::value == true);
        EXCEPT(is_member_object_pointer<int(Class::*)()>::value == false);

        // is_member_pointer
        EXCEPT(is_member_pointer<int>::value == false);
        EXCEPT(is_member_pointer<int(Class::*)>::value == true);
        EXCEPT(is_member_pointer<int(Class::*)()>::value == true);

        // is_pointer
        EXCEPT(is_pointer<int*>::value == true);
        EXCEPT(is_pointer<const int*>::value == true);
        EXCEPT(is_pointer<int>::value == false);
        EXCEPT(is_pointer<Class*>::value == true);
        EXCEPT(is_pointer<int**>::value == true);

        // is_enum
        enum Enum {};
        EXCEPT(is_enum<Enum>::value == true);
        EXCEPT(is_enum<const Enum>::value == true);
        EXCEPT(is_enum<int>::value == false);
        EXCEPT(is_enum<Enum*>::value == false);
        EXCEPT(is_enum<Class>::value == false);
        
        // is_union
        union Union {};
        EXCEPT(is_union<Union>::value == true);
        EXCEPT(is_union<const Union>::value == true);
        EXCEPT(is_union<int>::value == false);
        EXCEPT(is_union<Union*>::value == false);
        EXCEPT(is_union<Class>::value == false);

        // is_class
        EXCEPT(is_class<Class>::value == true);
        EXCEPT(is_class<const Class>::value == true);
        EXCEPT(is_class<int>::value == false);
        EXCEPT(is_class<Class*>::value == false);
        EXCEPT(is_class<volatile Class>::value == true);

        // is_function
        typedef void  Function1();
        typedef int*  Function2(Class, int, long);
        typedef void* Function3();
        EXCEPT(is_function<Function1>::value == true);
        EXCEPT(is_function<Function2>::value == true);
        EXCEPT(is_function<Function3>::value == true);
        EXCEPT(is_function<int>::value == false);
        EXCEPT(is_function<int[]>::value == false);

        // is_object
        EXCEPT(is_object<int>::value == true);
        EXCEPT(is_object<Class>::value == true);
        EXCEPT(is_object<int*>::value == true);
        EXCEPT(is_object<int&>::value == false);

        // is_scalar
        EXCEPT(is_scalar<int>::value == true);
        EXCEPT(is_scalar<float>::value == true);
        EXCEPT(is_scalar<const int>::value == true);
        EXCEPT(is_scalar<Enum>::value == true);
        EXCEPT(is_scalar<int*>::value == true);

        // is_compound
        EXCEPT(is_compound<Class>::value == true);
        EXCEPT(is_compound<Enum>::value == true);
        EXCEPT(is_compound<Union>::value == true);
        EXCEPT(is_compound<int*>::value == true);
        EXCEPT(is_compound<int>::value == false);

        // is_pod
        // 目前的 pod 除了builtin类型，其他自定义类型要 DECLARE_POD_TYPE
        //struct Pod1 {};
        /*struct Pod2
        {
            int a;
            int b;
        };*/
        struct NoPod {};
        //DECLARE_POD_TYPE(Pod1);
        //DECLARE_POD_TYPE(Pod2);
        EXCEPT(is_pod<Pod1>::value == true);
        EXCEPT(is_pod<Pod2>::value == true);
        EXCEPT(is_pod<Class>::value == false);
        EXCEPT(is_pod<int>::value == true);
        EXCEPT(is_pod<int*>::value == true);
        EXCEPT(is_pod<NoPod>::value == false);

        // has_trivial_xxxx
        EXCEPT(has_trivial_default_constructor<int>::value == true);
        EXCEPT(has_trivial_default_constructor<int*>::value == true);

        // is_signed
        EXCEPT(is_signed<int>::value == true);
        EXCEPT(is_signed<const long long>::value == true);
        EXCEPT(is_signed<unsigned int>::value == false);
        EXCEPT(is_signed<Class>::value == false);
        EXCEPT(is_signed<bool>::value == false);

        // is_unsigned
        EXCEPT(is_unsigned<unsigned int>::value == true);
        EXCEPT(is_unsigned<unsigned char>::value == true);
        EXCEPT(is_unsigned<int>::value == false);
        EXCEPT(is_unsigned<Class>::value == false);
        EXCEPT(is_unsigned<bool>::value == false);

        
    }

    Report();
}




