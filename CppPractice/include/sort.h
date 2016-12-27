#pragma once

#ifndef __SORT_H__
#define __SORT_H__

#include <algorithm.h>
#include <functional.h>

namespace sp
{
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

	// 选择排序
	template <typename ForwardIter, typename Compare>
	void selection_sort(ForwardIter first, ForwardIter last, Compare compare)
	{
		for (; first != last; ++first)
		{
			ForwardIter find = first, current = first;
			++current;
			for (; current != last; ++current)
			{
				if (compare(*current, *find))
					find = current;
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

	// 冒泡排序
	template <typename ForwardIter, typename Compare>
	void bubble_sort(ForwardIter first, ForwardIter last, Compare compare )
	{
		ForwardIter current,next;
		bool sorted = false;
		for (; sorted = !sorted; /*++current*/)
		{
			current = next = first;
			
			for (++next; next != last; ++current,++next)
			{
				// 当前元素，与前一个元素比较，若符合，则交换.
				// less ->  return *next < *current;
				// 则为升序排列
				if (compare(*next, *current))
				{
					swap(*next, *current);
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
