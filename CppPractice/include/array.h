#pragma once
/*
    array.h

    2016.11.6
        尚未完成.
    2016.11.17
        完成
*/

#include <iterator.h>
#include <construct.h>
#include <algorithm.h>

namespace sp
{
    template<class T, size_t N>
    class array
    {
    public:
        typedef array<T, N>                          this_type;
        typedef T                                    value_type;
        typedef T*                                   pointer;
        typedef T&                                   reference;
        typedef const T&                             const_reference;
        typedef T*                                   iterator;
        typedef const T*                             const_iterator;
        typedef sp::reverse_iterator<iterator>       reverse_iterator;
        typedef sp::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef size_t                               size_type;
        

    public:
        value_type _value[N];

        void fill(const value_type& value)
        {
            sp::fill_n(&_value[0], N, value);
        }

        iterator begin()
        {
            return &_value[0];
        }
        const_iterator begin() const
        {
            return &_value[0];
        }
        const_iterator cbegin() const
        {
            return &_value[0];
        }

        iterator end()
        {
            return &_value[N];
        }
        const_iterator end() const
        {
            return &_value[N];
        }
        const_iterator cend() const
        {
            return &_value[N];
        }
        
        reverse_iterator       rbegin()
        {
            return reverse_iterator(&_value[N]);
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(&_value[N]);
        }
        const_reverse_iterator crbegin() const
        {
            return const_reverse_iterator(&_value[N]);
        }
        
        reverse_iterator       rend()
        {
            return reverse_iterator(&_value[0]);
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(&_value[0]);
        }
        const_reverse_iterator crend() const
        {
            return const_reverse_iterator(&_value[0]);
        }

        inline size_type size()
        {
            return (size_type)N;
        }
        inline size_type max_size()
        {
            return (size_type)N;
        }
        inline bool      empty()
        {
            return N == 0;
        }

        inline reference operator[](size_type i)
        {
            return _value[i];
        }
        inline const_reference operator[](size_type i) const
        {
            return _value[i];
        }

    };

    template<typename T,size_t N>
    bool operator==(const array<T, N>& arr1, const array<T, N>& arr2)
    {
        return sp::equal(&arr1._value[0], &arr1._value[N], &arr2._value[0]);
    }

}