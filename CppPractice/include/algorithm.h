#pragma once

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <iterator.h>
#include <string.h>

namespace sp
{
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



