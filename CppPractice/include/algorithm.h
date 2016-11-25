#pragma once

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <iterator.h>
#include <string.h>
#include <utility.h>

namespace sp
{
	template <typename T>
	inline T& max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}
	template <typename T>
	inline T& max(const T& a, const T& b, const T& c)
	{
		return max(a, max(b, c));
	}
	template <typename T>
	inline T& min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}
	template <typename T>
	inline T& min(const T& a, const T& b, const T& c)
	{
		return min(a, min(b, c));
	}
	/*template <typename T>
	inline T& mid(const T& a, const T& b, const T& c)
	{
	return a > b ? (b > c ? b : (a > c ? c : a) ) : (b < c ? b : (a < c ? c : a));
	}*/
    template <typename ForwardIter>
    inline ForwardIter max(ForwardIter first, ForwardIter last)
    {
        ForwardIter max = first;
		++first;
        for (; first != last; ++first)
            if (*max < *first)
                max = first;

        return max;
    }
    template <typename ForwardIter>
    inline ForwardIter min(ForwardIter first, ForwardIter last)
    {
        ForwardIter min = first;
        for (; first != last; ++first)
            if (*min > *first)
                max = first;

        return max;
    }

    template <typename InputIterator1, typename InputIterator2>
    inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
                return false;
        }
        return true;
    }
}


#endif



