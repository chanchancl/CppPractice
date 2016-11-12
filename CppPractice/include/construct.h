#pragma once


namespace sp
{

    // ʹ�� replacement new
    // ��memory��ָ��λ�ã�����һ�� value �ĸ���Ʒ��
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

    // ���� pointer ָ����ָ�Ķ���
    template <class ForwardIter >
    inline void Destroy(const ForwardIter iter)
    {
        _Destroy(&*iter);
    }

    // ���� first �� last ֮�������Ԫ�ء�
    template <class ForwardIter>
    inline void Destroy(ForwardIter first, ForwardIter last)
    {
        for (; first != last; ++first)
            Destroy(&*first);
    }
}


