#pragma once

#ifndef __C_VECTOR_H__
#define __C_VECTOR_H__

#include <vector>

namespace sp
{
#define VECTOR_INIT_CAPACITY   10
#define VECTOR_INCREASE_FACTOR 1.5

    template<class _T>
    class vector_base
    {
        

    public:
        typedef _T  ValueType;
        typedef _T* ValueTypePointer;
        typedef _T& ValueTypeReference;
        
        class const_iterator
        {
        public:
            const_iterator(ValueTypePointer vtp) : _Current(vtp) {}

            const_iterator& operator++()
            {
                _Current++;
                return (*this);
            }
            const_iterator& operator++(int)
            {
                const_iterator tmp = *this;
                ++*this;
                return (*this);
            }
            const_iterator& operator--()
            {
                _Current--;
                return (*this)
            }
            const_iterator& operator--(int)
            {
                const_iterator tmp = *this;
                --*this;
                return (*this);
            }
            const ValueTypeReference operator*() const
            {
                return (*_Current);
            }
            const ValueTypePointer operator->() const
            {
                return (&(**this);)
            }

            bool operator==(const const_iterator& oth) const
            {
                return _Current == oth._Current;
            }
            bool operator!=(const const_iterator& oth) const
            {
                return !((*this) == oth);
            }

            ValueTypePointer _Current;
        };
        class iterator : public const_iterator
        {
        public:
            iterator(ValueTypePointer vtp) : const_iterator(vtp) {}
            
            const ValueTypeReference operator*() const
            {
                return (*_Current);
            }
            const ValueTypePointer operator->() const
            {
                return (&(**this);)
            }
        };
        
    public:
        vector_base() : _Size(0), _Capacity(VECTOR_INIT_CAPACITY), _Value(new ValueType[VECTOR_INIT_CAPACITY]) {}
        vector_base(size_t size, ValueType dt) : _Size(size)
        {
            _Capacity = _Size > VECTOR_INIT_CAPACITY ? (size_t)(_Size * VECTOR_INCREASE_FACTOR) : VECTOR_INIT_CAPACITY;
            _Value = new ValueType[_Capacity];
            for (size_t i = 0; i < _Size; i++)
                _Value[i] = dt;
        }
        vector_base(const vector_base& oth)
        {
            _Size = oth._Size;
            _Capacity = oth._Capacity;
            _Value = new ValueType[_Capacity];
            for (size_t i = 0; i < _Size; i++)
                _Value[i] = oth._Value[i];
        }
        ~vector_base()
        {
            if (_Capacity > 0)
                delete[] _Value;
        }

    protected:
        size_t _Capacity;
        size_t _Size;
        ValueTypePointer _Value;
    };

    template<class _T>
    class CVector : vector_base<_T>
    {
    public:
        typedef vector_base<_T> base_type;
        typedef base_type::iterator iterator;
        typedef base_type::const_iterator const_iterator;
    public:
        CVector(): vector_base() {}
        CVector(size_t size , ValueType dt) : base_type(size,dt) {}
        // 这里没有拷贝构造函数，这个行为由vector_base<_T>来完成
        // CVector<_T>默认的浅拷贝，会调用vector_base<_T>的拷贝构造函数
        
        iterator begin()
        {
            return iterator(_Value);
        }
        iterator end()
        {
            return iterator(_Value + _Size);
        }


        ValueTypeReference ElementAt(size_t index)
        {
            return (*this)[index];
        }
        size_t IndexOf(ValueTypeReference value)
        {
            for (size_t i = 0; i < _Size; i++)
                if ((*this)[i] == value)
                    return i;
        }


        ValueTypeReference operator[](size_t index)
        {
            // 0 <= index <= _Size-1;
            return _Value[index];
        }
    };


}
#endif
