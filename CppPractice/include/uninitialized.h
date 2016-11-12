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
        for (; first != last; ++first, ++cur)
            Construct(&*cur, *first);
        return cur;
    }



}

