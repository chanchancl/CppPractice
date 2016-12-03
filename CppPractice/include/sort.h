#pragma once

#ifndef __SORT_H__
#define __SORT_H__

#include <algorithm.h>

namespace sp
{

	// temp functional

	template <typename T>
	struct less
	{
		bool operator()(const T& a, const T& b)
		{
			return a < b;
		}
	};


	template <typename ForwardIter, typename Compare>
	bool is_sorted(ForwardIter first, ForwardIter last, Compare compare)
	{
		if (first != last)
		{
			ForwardIter current = first;
			for (++current; current != last; ++first, ++current)
			{
				if (compare(*current, *first))
				{
					return false;
				}
			}
		}
		return true;
	}

	template <typename ForwardIter>
	bool is_sorted(ForwardIter first, ForwardIter last)
	{
		typedef typename less<typename iterator_traits<ForwardIter>::value_type> Less;

		return is_sorted(first, last, Less());
	}

	// —°‘Ò≈≈–Ú
	template <typename ForwardIter, typename Compare>
	void selection_sort(ForwardIter first, ForwardIter last, Compare compare)
	{
		for (; first != last; ++first)
		{
			ForwardIter find = first, tmp = first;
			++tmp;
			for (; tmp != last; ++tmp)
			{
				if (compare(*tmp, *find))
					find = tmp;
			}

			sp::swap(*find, *first);
		}
	}

	template <typename ForwardIter>
	void selection_sort(ForwardIter first, ForwardIter last)
	{
		typedef typename less<typename iterator_traits<ForwardIter>::value_type> Less;

		selection_sort(first, last, Less());
	}

	// √∞≈›≈≈–Ú
	template <typename ForwardIter, typename Compare>
	void bubble_sort(ForwardIter first, ForwardIter last, Compare compare )
	{
		ForwardIter cur,tmpfirst;
		bool sorted = false;
		for (; sorted = !sorted; ++cur)
		{
			tmpfirst = cur = first;
			
			for (++cur; cur != last; ++cur,++tmpfirst)
			{
				if (compare(*cur, *tmpfirst))
				{
					swap(*cur, *tmpfirst);
					sorted = false;
				}
			}
		}
	}

	template <typename ForwardIter>
	void bubble_sort(ForwardIter first, ForwardIter last)
	{
		typedef typename less<typename iterator_traits<ForwardIter>::value_type> Less;

		bubble_sort(first, last, Less());
	}

}


#endif
