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

    // is_member_pointer
    template <typename T> struct is_mem_fun_pointer_value : public false_type {};

    template <typename R, typename T> struct is_mem_fun_pointer_value<R(T::*)()> : public true_type {};
    template <typename R, typename T> struct is_mem_fun_pointer_value<R(T::*)() const> : public true_type {};
    template <typename R, typename T> struct is_mem_fun_pointer_value<R(T::*)() volatile> : public true_type {};
    template <typename R, typename T> struct is_mem_fun_pointer_value<R(T::*)() const volatile> : public true_type {};

    template <typename R, typename T, typename Arg0> struct is_mem_fun_pointer_value<R(T::*)(Arg0)> : public true_type {};
    template <typename R, typename T, typename Arg0> struct is_mem_fun_pointer_value<R(T::*)(Arg0) const> : public true_type {};
    template <typename R, typename T, typename Arg0> struct is_mem_fun_pointer_value<R(T::*)(Arg0) volatile> : public true_type {};
    template <typename R, typename T, typename Arg0> struct is_mem_fun_pointer_value<R(T::*)(Arg0) const volatile> : public true_type {};

    template <typename R, typename T, typename Arg0, typename Arg1> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1)> : public true_type {};
    template <typename R, typename T, typename Arg0, typename Arg1> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1) const> : public true_type {};
    template <typename R, typename T, typename Arg0, typename Arg1> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1) volatile> : public true_type {};
    template <typename R, typename T, typename Arg0, typename Arg1> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1) const volatile> : public true_type {};

    template <typename R, typename T, typename Arg0, typename Arg1, typename Arg2> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1, Arg2)> : public true_type {};
    template <typename R, typename T, typename Arg0, typename Arg1, typename Arg2> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1, Arg2) const> : public true_type {};
    template <typename R, typename T, typename Arg0, typename Arg1, typename Arg2> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1, Arg2) volatile> : public true_type {};
    template <typename R, typename T, typename Arg0, typename Arg1, typename Arg2> struct is_mem_fun_pointer_value<R(T::*)(Arg0, Arg1, Arg2) const volatile> : public true_type {};

    template <typename T>
    struct is_member_function_pointer : public integral_constant<bool, is_mem_fun_pointer_value<T>::value> {};

    template <typename T>
    struct is_member_pointer
        : public integral_constant<bool, is_member_function_pointer<T>::value> {};

    template <typename T, typename U>
    struct is_member_pointer<U T::*>
        : public true_type {};

    // is_member_object_pointer
    template<typename T>
    struct is_member_object_pointer : public integral_constant<bool,
        is_member_pointer<T>::value &&
        !is_member_function_pointer<T>::value
    > {};

    // is_pointer
    template <typename T> struct is_pointer_helper : public false_type {};

    template <typename T> struct is_pointer_helper<T*> : public true_type {};
    template <typename T> struct is_pointer_helper<T* const> : public true_type {};
    template <typename T> struct is_pointer_helper<T* volatile> : public true_type {};
    template <typename T> struct is_pointer_helper<T* const volatile> : public true_type {};

    template <typename T>
    struct is_pointer_value : public type_and<is_pointer_helper<T>::value, type_not<is_member_pointer<T>::value>::value> {};

    template <typename T>
    struct is_pointer : public integral_constant<bool, is_pointer_value<T>::value> {};

    // is_union
    template <typename T>
    struct is_union : public integral_constant<bool, __is_union(T)> {};

    // is_class
    template <typename T>
    struct is_class : public integral_constant<bool, __is_class(T)> {};

    // is_enum
    template <typename T>
    struct is_enum : public integral_constant<bool, __is_enum(T)> {};

    

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