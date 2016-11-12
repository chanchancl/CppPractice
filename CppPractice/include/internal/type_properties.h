#pragma once

namespace sp
{
    // is_signed
    template <typename T> struct is_signed_helper         : public false_type {};

    template <> struct is_signed_helper<signed char>      : public true_type {};
    template <> struct is_signed_helper<signed short>     : public true_type {};
    template <> struct is_signed_helper<signed int>       : public true_type {};
    template <> struct is_signed_helper<signed long>      : public true_type {};
    template <> struct is_signed_helper<signed long long> : public true_type {};
    template <> struct is_signed_helper<float>            : public true_type {};
    template <> struct is_signed_helper<double>           : public true_type {};
    template <> struct is_signed_helper<long double>      : public true_type {};
    template <> struct is_signed_helper<char>             : public true_type {};

    template<typename T>
    struct is_signed : public sp::is_signed_helper<typename sp::remove_cv<T>::type> {};

#define DECLARE_SIGNED(T)                                                       \
	namespace sp{                                                               \
		template <> struct is_signed<T>                : public true_type{};    \
		template <> struct is_signed<const T>          : public true_type{};    \
		template <> struct is_signed<volatile T>       : public true_type{};    \
		template <> struct is_signed<const volatile T> : public true_type{};    \
	}

    //
    template <typename T> struct is_unsigned_helper : public false_type {};

    template <> struct is_unsigned_helper<unsigned char>      : public true_type {};
    template <> struct is_unsigned_helper<unsigned short>     : public true_type {};
    template <> struct is_unsigned_helper<unsigned int>       : public true_type {};
    template <> struct is_unsigned_helper<unsigned long>      : public true_type {};
    template <> struct is_unsigned_helper<unsigned long long> : public true_type {};
    template <> struct is_unsigned_helper<wchar_t>            : public true_type {};

    template <typename T>
    struct is_unsigned : public sp::is_unsigned_helper<typename sp::remove_cv<T>::type> {};

#define DECLARE_UNSIGNED(T)                                                       \
	namespace sp{                                                                 \
		template <> struct is_unsigned<T>                : public true_type{};    \
		template <> struct is_unsigned<const T>          : public true_type{};    \
		template <> struct is_unsigned<volatile T>       : public true_type{};    \
		template <> struct is_unsigned<const volatile T> : public true_type{};    \
	}

    // is_base_of

    template <typename Base, typename Derived>
    struct is_base_of : public sp::integral_constant<bool, __is_base_of(Base, Derived) || sp::is_same<Base, Derived>::value> {};









}