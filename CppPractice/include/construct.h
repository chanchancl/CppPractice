#pragma once


namespace sp
{

    // 使用 replacement new
    // 在memory所指的位置，构造一个 value 的复制品。
    template <class pointer, class T2>
    inline void Construct(pointer iter, T2& value)
    {
        new(static_cast<void*>(iter)) T2(value);
    }

    template <class T>
    inline void Construct(const T* iter)
    {
        new(static_cast<void*>(iter)) T();
    }

    template <class T >
    inline void _Destroy(const T* pointer)
    {
        pointer->~T();
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
            Destroy(&*first);
    }
}


