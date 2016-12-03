#pragma once

#ifndef __UTILITY_H__
#define	__UTILITY_H__

namespace sp
{
	template <typename T>
	inline void swap(T& a, T& b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}
}

#endif