#pragma once


namespace sp
{
	namespace old
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
		struct has_trivial_default_constructor : public type_pod<typename remove_cv<T>::type>::has_trivial_default_constructor {};

		// has_trivial_copy_constructor
		template <typename T>
		struct has_trivial_copy_constructor : public type_pod<typename remove_cv<T>::type>::has_trivial_copy_constructor {};

		// has_trivial_copy_constructor
		template <typename T>
		struct has_trivial_assignment_operator : public type_pod<typename remove_cv<T>::type>::has_trivial_assignment_operator {};

		// has_trivial_copy_constructor
		template <typename T>
		struct has_trivial_destructor : public type_pod<typename remove_cv<T>::type>::has_trivial_destructor {};

		// has_trivial_copy_constructor
		template <typename T>
		struct is_pod : public type_pod<typename remove_cv<T>::type>::is_POD_type {};

		// is_trivial
		template <typename T>
		struct is_trivial : public has_trivial_copy_constructor<T> {};
	}


	template <typename T>
	struct is_pod : public bool_constant<__is_pod(T)> {};

	template <typename T>
	struct is_empty : public bool_constant<__is_empty(T)> {};

	template <typename T>
	struct is_polymorphic : public bool_constant<__is_polymorphic(T)> {};

	template <typename T>
	struct is_abstract : public bool_constant<__is_abstract(T)> {};

	template <typename T>
	struct is_final : public bool_constant<__is_final(T)> {};

	template <typename T>
	struct is_trivial : public bool_constant<__is_trivial(T)> {};

	template <typename T>
	struct is_trivially_copyable : public bool_constant<__is_trivially_copyable(T)> {};

	template <typename T>
	struct has_virtual_destructor : public bool_constant<__has_virtual_destructor(T)> {};

	template <typename T, class ...Args>
	struct is_constructible : public bool_constant<__is_constructible(T,Args)> {};

	template <typename T>
	struct is_copy_constructible : public is_constructible< T, typename add_lvalue_reference< typename add_const<T>::type>::type>::type {};

	template <typename T>
	struct is_default_constructible : public is_constructible<T>::type {};

	template <typename T>
	struct is_move_constructible : public is_constructible<T, typename add_rvalue_reference< typename add_const<T>::type>::type>::type {};

	template <typename T>
	struct is_destructible : public bool_constant<__is_destructible(T)> {};

	template <typename T, class ...Args>
	struct is_trivially_constructible : public bool_constant<__is_trivially_constructible(T, Args...)> {};

	template <typename T>
	struct is_trivially_copy_constructible : public is_trivially_constructible<T, typename add_rvalue_reference< typename add_const<T>::type>::type>::type {};

	template <typename T>
	struct has_trivial_constructor : public bool_constant<__has_trivial_constructor(T)> {};

	template <typename T>
	struct has_trivial_copy : public bool_constant<__has_trivial_copy(T)> {};

	template <typename T>
	struct has_trivial_assign : public bool_constant<__has_trivial_assign(T)> {};

	template <typename T>
	struct has_trivial_destructor : public bool_constant<__has_trivial_destructor(T)> {};




}