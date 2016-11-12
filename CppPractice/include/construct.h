#pragma once

#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <iterator.h>
#include <type_traits.h>

namespace sp
{

    // 使用 replacement new
    // 在memory所指的位置，构造一个 value 的复制品。
    template <class ForwardIter, class T>
    inline void Construct(ForwardIter iter, T& value)
    {

        new(static_cast<void*>(&*iter)) T(value);
    }

    template <class ForwardIter>
    inline void Construct(const ForwardIter iter)
    {
        typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;

        new(static_cast<void*>(&*iter)) value_type();
    }

    template <class T >
    inline void _Destroy(const T* /*pointer*/, true_type)
    {
        // do nothing
    }

    template <class T >
    inline void _Destroy(const T* pointer, false_type)
    {
        pointer->~T();
    }

    // 析构 iter 指向的元素
    template <class ForwardIter >
    inline void Destroy(const ForwardIter iter)
    {
        typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;
        _Destroy(&*iter,sp::has_trivial_destructor<value_type>());
    }

    // 析构 first 和 last 之间的所有元素。
    template <class ForwardIter>
    inline void Destroy(ForwardIter first, ForwardIter last)
    {
        

        for (; first != last; ++first)
            Destroy(first);
    }
}


#endif