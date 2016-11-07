#pragma once


namespace sp
{

    template <class InputIter, class OutIter>
    inline OutIter copy(InputIter first, InputIter last, OutIter result)
    {
        for (; first != last; ++first, ++result)
            *result = *first;

        return result;
    }
    template <class InputIter, class OutIter>
    inline OutIter copy_backward(InputIter first, InputIter last, OutIter result)
    {
        for()
    }
}






