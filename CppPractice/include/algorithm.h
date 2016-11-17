#pragma once

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <iterator.h>
#include <string.h>

namespace sp
{
    template <typename ForwardIter>
    inline ForwardIter max(ForwardIter first, ForwardIter last)
    {
        ForwardIter max = first;
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



