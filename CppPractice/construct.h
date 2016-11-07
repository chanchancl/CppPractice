#pragma once


namespace sp
{

    // 使用 replacement new
    // 在memory所指的位置，构造一个 value 的复制品。
    template <class InputIter, class T2>
    inline void Construct(InputIter iter, T2& value)
    {
        new((void*)&*iter) T2(value);
    }

    template <class InputIter>
    inline void Construct(InputIter iter)
    {
        new((void*)&*iter) T1();
    }

    template <class T1 >
    inline void _Destroy(const T1* pointer)
    {
        pointer->~T1();
    }

    // 析构 pointer 指针所指的对象
    template <class ForwardIter >
    inline void Destroy(const ForwardIter iter)
    {
        _Destroy(&*iter);
    }

    // 析构 first 和 last 之间的所有元素。
    template <class ForwardIter>
    inline void Destroy(ForwardIter first, ForwardIter last)
    {
        for (; first != last; ++first)
            Destroy(first);
    }
}


