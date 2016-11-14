#pragma once

#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <iterator.h>
#include <type_traits.h>
#include <stddef.h>

namespace sp
{

    // 使用 replacement new
    // 在memory所指的位置，构造一个 value 的复制品。
    template <class ForwardIter, class T>
    inline void construct(ForwardIter iter, const T& value)
    {

        new(static_cast<void*>(&*iter)) T(value);
    }

    template <class ForwardIter>
    inline void construct(const ForwardIter iter)
    {
        typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;

        new(static_cast<void*>(&*iter)) value_type();
    }

    template <class T >
    inline void _destroy(const T* /*pointer*/, true_type)
    {
        // do nothing
    }

    template <class T >
    inline void _destroy(const T* pointer, false_type)
    {
        pointer->~T();
    }

    // 析构 iter 指向的元素
    template <class ForwardIter >
    inline void destroy(const ForwardIter iter)
    {
        typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;

        _destroy(&*iter,sp::has_trivial_destructor<value_type>());
    }

    // 析构 first 和 last 之间的所有元素。
    template <class ForwardIter>
    inline void destroy(ForwardIter first, ForwardIter last)
    {
        
        for (; first != last; ++first)
            destroy(first);
    }

    // copy
    // 确定数据区不会重叠，就使用copy
    template <class InputIter, class OutIter>
    inline OutIter copy(InputIter first, InputIter last, OutIter result)
    {
        typedef typename iterator_traits<InputIter>::value_type valute_type;

        ::memcpy(&*result, &first, sizeof(value_type)*(last - first));

        /*ptrdiff_t n = last - first;
        for (; n > 0; --n, ++first, ++result)
        *result = *first;*/
        return result;
    }

    // copy_backward
    // 如果数据区重叠，可以用 copy_backward
    template <class InputIter, class OutIter>
    inline OutIter copy_backward(InputIter first, InputIter last, OutIter result)
    {
        typedef typename iterator_traits<InputIter>::value_type value_type;

        ::memmove((result - (last - first)), &*first, sizeof(value_type)*(last - first));
        return result;
    }

    template <class InputIter, class T>
    inline InputIter fill(InputIter first, InputIter last, const T& value)
    {

        for (; first != last; ++first)
            construct(first, value);

        return first;
    }



}


#endif