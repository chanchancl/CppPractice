#pragma once

#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include <iterator.h>
#include <construct.h>
#include <type_traits.h>

namespace sp
{
    
    // uninitialized_copy

    namespace Internal
    {
		// trivial 类型，直接copy
        template <class InputIter, class ForwardIter>
        inline ForwardIter uninitlized_copy_impl(InputIter first, InputIter last, ForwardIter result, true_type)
        {
           return sp::copy(first, last, result);
        }

		// 非 trivail，需要执行 construct copy
        template <class InputIter, class ForwardIter>
        inline ForwardIter uninitlized_copy_impl(InputIter first, InputIter last, ForwardIter result, false_type)
        {
            ForwardIter cur = result;

            for (; first != last; ++first, ++cur)
                sp::construct(cur, *first);

            return cur;
        }
    }

	// 复制 [first,last) 范围内的元素到以result开头的连续空间中
    template <class InputIter,class ForwardIter>
    inline ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
    {
        typedef typename iterator_traits<ForwardIter>::value_type value_type;
        
        return Internal::uninitlized_copy_impl(first, last, result, sp::is_trivial<value_type>());
    }



}

#endif // !_UNINITIALIZED_H_