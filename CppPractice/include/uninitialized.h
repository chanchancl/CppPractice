#pragma once

#include <iterator.h>
#include <construct.h>
#include <type_traits.h>

namespace sp
{
    
    // uninitialized_copy

    namespace Internal
    {
        template <class InputIter, class ForwardIter>
        inline ForwardIter uninitlized_copy_impl(InputIter first, InputIter last, ForwardIter result, true_type)
        {
           return sp::copy(first, last, result);
        }

        template <class InputIter, class ForwardIter>
        inline ForwardIter uninitlized_copy_impl(InputIter first, InputIter last, ForwardIter result, false_type)
        {
            ForwardIter cur = result;

            for (; first != last; ++first, ++result)
                sp::construct(cur, first);

            return result;
        }
    }

    template <class InputIter,class ForwardIter>
    inline ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
    {
        typedef typename iterator_traits<ForwardIter>::value_type value_type;
        
        return Internal::uninitlized_copy_impl(first, last, result, sp::is_trivial<value_type>());
    }



}

