#pragma once

#ifndef __UTILITY_H__
#define	__UTILITY_H__

#include <utility>

namespace sp
{
	template <typename T>
	inline void swap(T& a, T& b)
	{
		T tmp = std::move(a);
		a = std::move(b);
		b = std::move(tmp);
	}
}

#endif