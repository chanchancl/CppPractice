#pragma once

namespace sp
{
    template<class _T, size_t _N>
    class array
    {
    public:
        typedef _T                        value_type;
        typedef value_type*               pointer;
        typedef value_type&               reference;
        typedef const value_type          const_iterator;
        typedef value_type                iterator;
        typedef array<value_type,_N>      this_type;


    public:
        

    private:
        value_type _Value[_N];
        size_t _Size;
    };
}