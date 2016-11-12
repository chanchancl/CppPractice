#pragma once


namespace sp
{

    // add_const
    template <typename T, bool = is_const<T>::value || is_reference<T>::value || is_function<T>::value >
    struct add_const_helper { typedef T type; };

    template <typename T>
    struct add_const_helper<T, false>
    {
        typedef const T type;
    };

    template <typename T>
    struct add_const 
    { 
        typedef typename add_const_helper<T>::type type;
    };

    // add volatile
    template <typename T, bool = is_volatile<T>::value || is_reference<T>::value || is_function<T>::value>
    struct add_volatile_helper 
    { typedef T type; };

    template <typename T>
    struct add_volatile_helper<T, false>
    { 
        typedef volatile T type; 
    };

    template <typename T>
    struct add_volatile 
    { 
        typedef typename add_volatile_helper<T>::type value; 
    };

    // add_cv
    template <typename T>
    struct add_cv
    {
        typedef typename add_const<typename add_volatile<T>::type>::type type;
    };

    // make_signed
    template <typename T> struct make_signed { typedef T type; };

    template <> struct make_signed<unsigned char>        { typedef signed char      type; };
    template <> struct make_signed<const unsigned char>  { typedef signed char      type; };
    template <> struct make_signed<unsigned short>       { typedef signed short     type; };
    template <> struct make_signed<const unsigned short> { typedef signed short     type; };
    template <> struct make_signed<unsigned int>         { typedef signed int       type; };
    template <> struct make_signed<const unsigned int>   { typedef signed int       type; };
    template <> struct make_signed<unsigned long>        { typedef signed long      type; };
    template <> struct make_signed<const unsigned long>  { typedef signed long      type; };
    template <> struct make_signed<unsigned long long>   { typedef signed long long type; };
    template <> struct make_signed<const unsigned long long> { typedef signed long long type; };

    // add_signed
    template <typename T>
    struct add_signed 
    {
        typedef typename make_signed<T>::type type;
    };

    // make_unsigned
    template <typename T> struct make_unsigned { typedef T type; };

    template <> struct make_unsigned<signed char>        { typedef unsigned char            type; };
    template <> struct make_unsigned<const signed char>  { typedef const unsigned char      type; };
    template <> struct make_unsigned<signed short>       { typedef unsigned short           type; };
    template <> struct make_unsigned<const signed short> { typedef const unsigned short     type; };
    template <> struct make_unsigned<signed int>         { typedef unsigned int             type; };
    template <> struct make_unsigned<const signed int>   { typedef const unsigned int       type; };
    template <> struct make_unsigned<signed long>        { typedef unsigned long            type; };
    template <> struct make_unsigned<const signed long>  { typedef const unsigned long      type; };
    template <> struct make_unsigned<signed long long>   { typedef unsigned long long       type; };
    template <> struct make_unsigned<const signed long long> { typedef const unsigned long long type; };

    // add_unsigned
    template<class T>
    struct add_unsigned : public make_unsigned<T>
    {
        typedef typename make_signed<T>::type type;
    };

    // remove_pointer
    template <typename T> struct remove_pointer { typedef T type; };
    template <typename T> struct remove_pointer<T*> { typedef T type; };
    template <typename T> struct remove_pointer<T* const> { typedef T type; };
    template <typename T> struct remove_pointer<T* volatile> { typedef T type; };
    template <typename T> struct remove_pointer<T* const volatile> { typedef T type; };

    // add_pointer
    template <typename T>
    struct add_pointer
    {
        typedef typename remove_reference<T>::type* type;
    };






}