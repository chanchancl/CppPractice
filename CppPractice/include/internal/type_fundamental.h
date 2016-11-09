#pragma once


namespace sp
{
    // is_void
    // is_void<T>::value == true ,only if T is type of 
    // [const] [volatile] void
    template <typename T>
    struct is_void : public false_type{};

    template <> struct is_void<void> : public true_type {};
    template <> struct is_void<void const> : public true_type {};
    template <> struct is_void<void volatile> : public true_type {};
    template <> struct is_void<void const volatile> : public true_type {};

    // is_null_pointer
    //
    // C++14 type trait. Refers only to nullptr_t and not NULL (0).
    // is_null_pointer<nullptr>::value == true
    // is_null_pointer<std::nullptr_t>::value == true
    // is_null_pointer<void*>::value == false
    // is_null_pointer<NULL>::value == [cannot compile]
    template <typename T>
    struct is_null_pointer : public is_same<typename remove_cv<T>::type, std::nullptr_t> {};

    // is_integral
    //
    // is_integral<T>::value == true if and only if T  is one of the following types:
    //    [const] [volatile] bool
    //    [const] [volatile] char
    //    [const] [volatile] signed char
    //    [const] [volatile] unsigned char
    //    [const] [volatile] wchar_t
    //    [const] [volatile] short
    //    [const] [volatile] int
    //    [const] [volatile] long
    //    [const] [volatile] long long
    //    [const] [volatile] unsigned short
    //    [const] [volatile] unsigned int
    //    [const] [volatile] unsigned long
    //    [const] [volatile] unsigned long long

    template <typename T> struct is_integral_helper : public false_type {};

    template <> struct is_integral_helper<unsigned char> : public true_type {};
    template <> struct is_integral_helper<unsigned short> : public true_type {};
    template <> struct is_integral_helper<unsigned int> : public true_type {};
    template <> struct is_integral_helper<unsigned long> : public true_type {};
    template <> struct is_integral_helper<unsigned long long> : public true_type {};

    template <> struct is_integral_helper<signed char> : public true_type {};
    template <> struct is_integral_helper<signed short> : public true_type {};
    template <> struct is_integral_helper<signed int> : public true_type {};
    template <> struct is_integral_helper<signed long> : public true_type {};
    template <> struct is_integral_helper<signed long long> : public true_type {};

    template <> struct is_integral_helper<bool> : public true_type {};
    template <> struct is_integral_helper<char> : public true_type {};
    template <> struct is_integral_helper<wchar_t> : public true_type {};

    template <typename T> 
    struct is_integral : public is_integral_helper<typename remove_cv<T>::type> {};
    
    // 这样。。所有的 const volatile 都会被剔除。

    #define SP_DECLARE_INTEGRAL(T)                                                \
	namespace sp{                                                                 \
		template <> struct is_integral<T>                : public true_type{};    \
		template <> struct is_integral<const T>          : public true_type{};    \
		template <> struct is_integral<volatile T>       : public true_type{};    \
		template <> struct is_integral<const volatile T> : public true_type{};    \
	}


    // is_floating_point
    //
    // is_floating_point<T>::value == true if and only if T is one of the following types:
    //    [const] [volatile] float
    //    [const] [volatile] double
    //    [const] [volatile] long double
    //

    template <typename T> struct is_floating_point_helper : public false_type {};
    template <> struct is_floating_point_helper<float> : public true_type {};
    template <> struct is_floating_point_helper<double> : public true_type {};
    template <> struct is_floating_point_helper<long double> : public true_type {};

    template <typename T>
    struct is_floating_point : public is_floating_point_helper<typename sp::remove_cv<T>::type> {};

    #define EASTL_DECLARE_FLOATING_POINT(T)                                             \
	namespace sp{                                                                       \
		template <> struct is_floating_point<T>                : public true_type{};    \
		template <> struct is_floating_point<const T>          : public true_type{};    \
		template <> struct is_floating_point<volatile T>       : public true_type{};    \
		template <> struct is_floating_point<const volatile T> : public true_type{};    \
	}

    // is_arithmetic
    //
    // is_arithmetic<T>::value == true if and only if:
    //    is_floating_point<T>::value == true, or
    //    is_integral<T>::value == true

    template <typename T>
    struct is_arithmetic : public integral_constant<bool,
        is_integral<T>::value || is_floating_point<T>::value > {};

    // is_fundamental
    //
    // is_fundamental<T>::value == true if and only if:
    //    is_floating_point<T>::value == true, or
    //    is_integral<T>::value == true, or
    //    is_void<T>::value == true
    //    is_null_pointer<T>::value == true

    template <typename T>
    struct is_fundamental : public integral_constant<bool,
        is_integral<T>::value || is_float_point<T>::value || is_void<T>::value || is_null_pointer<T>::value> {};


}
