#pragma once


namespace sp
{
    // type_pod
    template <typename T>
    struct type_pod
    {
        typedef false_type    has_trivial_default_constructor;
        typedef false_type    has_trivial_copy_constructor;
        typedef false_type    has_trivial_assignment_operator;
        typedef false_type    has_trivial_destructor;
        typedef false_type    is_POD_type;
    };

#define DECLARE_POD_TYPE(T)  template<>                             \
        struct type_pod<T>                                          \
        {                                                           \
            typedef true_type    has_trivial_default_constructor;   \
            typedef true_type    has_trivial_copy_constructor;      \
            typedef true_type    has_trivial_assignment_operator;   \
            typedef true_type    has_trivial_destructor;            \
            typedef true_type    is_POD_type;                       \
        };                                                          \

    DECLARE_POD_TYPE(bool)
    DECLARE_POD_TYPE(signed char)
    DECLARE_POD_TYPE(unsigned char)
    DECLARE_POD_TYPE(wchar_t)
    DECLARE_POD_TYPE(short)
    DECLARE_POD_TYPE(unsigned short)
    DECLARE_POD_TYPE(int)
    DECLARE_POD_TYPE(unsigned int)
    DECLARE_POD_TYPE(long)
    DECLARE_POD_TYPE(unsigned long)
    DECLARE_POD_TYPE(long long)
    DECLARE_POD_TYPE(unsigned long long)
    DECLARE_POD_TYPE(float)
    DECLARE_POD_TYPE(double)
    DECLARE_POD_TYPE(long double)

    template <typename T>
    struct type_pod<T*>
    {
        typedef true_type    has_trivial_default_constructor;
        typedef true_type    has_trivial_copy_constructor;
        typedef true_type    has_trivial_assignment_operator;
        typedef true_type    has_trivial_destructor;
        typedef true_type    is_POD_type;
    };

    // has_trivial_default_constructor
    template <typename T>
    struct has_trivial_default_constructor : public bool_constant<type_pod<typename remove_cv<T>::type>::has_trivial_default_constructor::value> {};

    // has_trivial_copy_constructor
    template <typename T>
    struct has_trivial_copy_constructor : public bool_constant<type_pod<typename remove_cv<T>::type>::has_trivial_copy_constructor::value> {};

    // has_trivial_copy_constructor
    template <typename T>
    struct has_trivial_assignment_operator : public bool_constant<type_pod<typename remove_cv<T>::type>::has_trivial_assignment_operator::value> {};

    // has_trivial_copy_constructor
    template <typename T>
    struct has_trivial_destructor : public bool_constant<type_pod<typename remove_cv<T>::type>::has_trivial_destructor::value> {};

    // has_trivial_copy_constructor
    template <typename T>
    struct is_POD_type : public bool_constant<type_pod<typename remove_cv<T>::type>::is_POD_type::value> {};

    // is_trivial
    template <typename T>
    struct is_trivial : public bool_constant< has_trivial_copy_constructor<T>::value > {};

}