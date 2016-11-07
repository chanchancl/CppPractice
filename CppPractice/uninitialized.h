#pragma once

#include "construct.h"

namespace sp
{
    
    
    
    //
    // 
    //
    template <class InputIter,class ForwardIter>
    inline ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
    {
        ForwardIter cur = result;

        /*
            // they are equal ?
            for (; first != last; ++first, ++cur)
                *cur = *first;   
        */
        for (; first != last; ++first, ++cur)
            Construct(cur, *first);

        return cur;
    }



}

