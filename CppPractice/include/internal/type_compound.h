#pragma once

namespace sp
{
    // is_array
    template <typename T>
    struct is_array : public false_type {};

    template <typename T>
    struct is_array<T[]> : public true_type {};

    template <typename T, size_t N>
    struct is_array<T[N]> : public true_type {};

    // is_object
    template <typename T>
    struct is_object : public integral_constant<bool,
        !is_reference<T>::value && !is_void<T>::value && !is_function<T>::value
    > {};

    // is_scalar
    //
    // is_scalar<T>::value == true if and only if:
    //    is_arithmetic<T>::value == true, or
    //    is_enum<T>::value == true, or
    //    is_pointer<T>::value == true, or
    //    is_member_pointer<T>::value == true, or
    //    is_null_pointer<T>::value == true
    //
    template <typename T>
    struct is_scalar : public integral_constant<bool, is_arithmetic<T>::value || is_enum<T>::value || is_member_pointer<T>::value || is_null_pointer<T>::value> {};

    template <typename T> struct is_scalar<T*> : public true_type {};
    template <typename T> struct is_scalar<T* const> : public true_type {};
    template <typename T> struct is_scalar<T* volatile> : public true_type {};
    template <typename T> struct is_scalar<T* const volatile> : public true_type {};

    // is_compound
    template <typename T>
    struct is_compound : public integral_constant<bool, !is_fundamental<T>::value> {};


}