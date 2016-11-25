#pragma once

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