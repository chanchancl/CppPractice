#pragma once

#ifndef __FUNCTIONAL_H__
#define __FUNCTIONAL_H__


/*
 * 一元仿函数
 * 二元仿函数
 */

namespace sp
{

	template <typename Argument, typename Result>
	struct unary_function
	{
		typedef Argument argument_type;
		typedef Result	 result_type;
	};

	template <typename Argument1, typename Argument2, typename Result>
	struct binary_function
	{
		typedef Argument1 argument1_type;
		typedef Argument2 argument2_type;
		typedef Result	  result_type;
	};
	
	// less
	template <typename T>
	struct less : public binary_function<T, T, bool>
	{
		bool operator()(const T& a, const T& b) const
		{
			return a < b;
		}
	};

	// greater
	template <typename T>
	struct greater : public binary_function<T, T, bool>
	{
		bool operator()(const T& a, const T& b) const
		{
			return a > b;
		}
	};


}



#endif // !__FUNCTIONAL_H__

