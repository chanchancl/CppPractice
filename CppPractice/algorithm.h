#pragma once


namespace sp
{

    template <class InputIter, class OutIter>
    inline OutIter copy(InputIter first, InputIter last, OutIter result)
    {
        ptrdiff_t n = last - first;
        for (; n > 0; --n, ++first, ++result)
            *result = *first;
        return result;
    }
    template <class InputIter, class OutIter>
    inline OutIter copy_backward(InputIter first, InputIter last, OutIter result)
    {
        for (; last != first; --last, --result)
            *result = *last;
        return result;
    }

    template <class InputIter, class T>
    inline InputIter fill(InputIter first, InputIter last, const T& result)
    {
        ptrdiff_t n = last - first;
        for (; n > 0; ++first)
            *first = result;

        return first;
    }
}






