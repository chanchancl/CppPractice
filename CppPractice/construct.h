#pragma once


namespace sp
{

    // ʹ�� replacement new
    // ��memory��ָ��λ�ã�����һ�� value �ĸ���Ʒ��
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
            Destroy(first);
    }
}


