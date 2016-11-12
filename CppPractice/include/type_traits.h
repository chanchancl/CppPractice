#pragma once

/*
    2016.11.9
    add type_traits
*/


#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

#include <stddef.h>

namespace sp
{
    /*
        is_char
        is_int
        is_integer
        is_pointer
        is_builtin
        is_builtin_pointer

    */

    template <typename T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef origin<T, v> type;
    };

    // true_type::value == true
    // false_type::type == false_type
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // 
    template <typename B>
    using bool_constant = integral_constant<bool, B>;
    
    // type_select
    // typedef ChosenType = type_select<is_pointer<some_type>::type, iterator, const_iterator>::type;
    template <bool bCondition, class ConditionIsTrueType, class ConditionIsFalseType>
    struct type_select { typedef ConditionIsTrueType type; };
    
    template <class ConditionIsTrueType, class ConditionIsFalseType>
    struct type_select<false, ConditionIsTrueType, ConditionIsFalseType> { typedef ConditionIsFalseType type; };

    // type_or
    // is_pointer_or_integer = type_or<is_pointer<sometype>::value,is_integer<some_type>::value>::value;
    template <bool b1, bool b2, bool b3 = false , bool b4 = false, bool b5 = false>
    struct type_or;

    template <bool b1, bool b2, bool b3, bool b4, bool b5>
    struct type_or { static const bool value = true; };
    
    template <>
    struct type_or<false, false, false, false, false> { static const bool value = false; };

    // type_and
    template <bool b1, bool b2, bool b3 = true, bool b4 = true, bool b5 = true>
    struct type_and;

    template <bool b1, bool b2, bool b3, bool b4, bool b5>
    struct type_and { static const bool value = false; };

    template <>
    struct type_and<true, true, true, true, true> { static const bool value = true; };

    // type_equal
    template <int t1, int t2>
    struct type_equal { static const bool value = (t1 == t2); };

    // type_not_equal
    template <int t1, int t2>
    struct type_not_equal { static const bool value = (t1 != t2); };

    // type_not
    template <int b>
    struct type_not { static const bool value = true; };

    template <>
    struct type_not<true> { static const bool value = false; };

    // is_same
    template <typename A, typename B>
    struct is_same : public false_type {};

    template <typename A >
    struct is_same<A,A> : public true_type {};

    // is_const
    template <typename T> struct is_const_value : public false_type {};
    template <typename T> struct is_const_value<const T*> : public true_type {};
    template <typename T> struct is_const_value<const volatile T*> : public true_type {};
    
    template <typename T> struct is_const : public is_const_value<T*> {};
    template <typename T> struct is_const<T&> : public false_type {};

    // is_volatile
    template <typename T> struct is_volatile_value : public false_type {};
    template <typename T> struct is_volatile_value<volatile T*> : public true_type {};
    template <typename T> struct is_volatile_value<const volatile T*> : public true_type {};

    template <typename T> struct is_volatile : public sp::is_volatile_value<T*> {};
    template <typename T> struct is_volatile : public sp::false_type {};

    // is_reference
    template <typename T> struct is_reference : public false_type {};
    template <typename T> struct is_reference<T&> : public true_type {};

    // is_function
    template <typename>
    struct is_function : public false_type {};

    template <typename ReturnValue, typename... ArgPack>
    struct is_function<ReturnValue (ArgPack...)> : public true_type {};

    template <typename ReturnValue, typename... ArgPack>
    struct is_function<ReturnValue(ArgPack..., ...)> : public true_type {};

    // remove_const
    template <typename T>           struct remove_const { typedef T type; };
    template <typename T>           struct remove_const<const T> { typedef T type; };
    template <typename T>           struct remove_const<const T[]> { typedef T type[]; };
    template <typename T, size_t N> struct remove_const<const T[N]> { typedef T type[N]; };

    // remove_volatile
    template <typename T>           struct remove_volatile { typedef T type; };
    template <typename T>           struct remove_volatile<volatile T> { typedef T type; };
    template <typename T>           struct remove_volatile<volatile T[]> { typedef T type[]; };
    template <typename T, size_t N> struct remove_volatile<volatile T[N]> { typedef T type[N]; };

    // remove_cv
    template <typename T>
    struct remove_cv { typedef typename remove_volatile<typename remove_const<T>::type>::type type; };


    template <typename T> struct add_reference_impl { typedef T&   type; };
    template <typename T> struct add_reference_impl<T&> { typedef T&   type; };
    template <>           struct add_reference_impl<void> { typedef void type; };

    template <typename T> struct add_reference { typedef typename add_reference_impl<T>::type type; };

    // remove_reference
    template <typename T> struct remove_reference { typedef T type; };
    template <typename T> struct remove_reference<T&> { typedef T type; };
    template <typename T> struct remove_reference<T&&> { typedef T type; };

    // static_min   static_max
    template <size_t I0, size_t I1>
    struct static_min
    {
        static const size_t value = ((I0 <= I1) ? I0 : I1);
    };

    template <size_t I0, size_t I1>
    struct static_max
    {
        static const size_t value = ((I0 >= I1) ? I0 : I1);
    };
}

#include <internal\type_fundamental.h>
#include <internal\type_transformation.h>
#include <internal\type_properties.h>
#include <internal\type_compound.h>
#include <internal\type_pod.h>

#endif