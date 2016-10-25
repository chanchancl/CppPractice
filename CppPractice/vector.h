#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace sp
{
#define VECTOR_INCREASE_FACTOR 2

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
            const_iterator(const const_iterator& oth) : _Current(oth._Current) {}
            const_iterator& operator++()
            {
                _Current++;
                return (*this);
            }
            const_iterator operator++(int)
            {
                const_iterator tmp = *this;
                ++*this;
                return tmp;
            }
            const_iterator& operator--()
            {
                _Current--;
                return (*this);
            }
            const_iterator operator--(int)
            {
                const_iterator tmp = *this;
                --*this;
                return tmp;
            }
            const_iterator operator+(int diff)
            {
                const_iterator tmp = _Current + diff;
                return tmp;
            }
            const_iterator operator-(int diff)
            {
                const_iterator tmp = _Current - diff;
                return tmp;
            }
            int operator-(const const_iterator& oth) const
            {
                return _Current - oth._Current;
            }
            const ValueTypeReference operator*() const
            {
                return (*_Current);
            }
            const ValueTypePointer operator->() const
            {
                return (&(**this));
            }

            bool operator==(const const_iterator& oth) const
            {
                return _Current == oth._Current;
            }
            bool operator!=(const const_iterator& oth) const
            {
                return !((*this) == oth);
            }
            bool operator<(const const_iterator& oth) const
            {
                return (oth - (*this)) > 0;
            }
            bool operator>(const const_iterator& oth) const
            {
                return ((*this) - oth) > 0;
            }
            bool operator<=(const const_iterator& oth) const
            {
                return (*this) < oth || *this == oth;
            }
            bool operator>=(const const_iterator& oth) const
            {
                return (*this) > oth || *this == oth;
            }

            ValueTypePointer _Current;
        };
        class iterator : public const_iterator
        {
        public:
            iterator(ValueTypePointer vtp) : const_iterator(vtp) {}
            iterator(const const_iterator& oth) : const_iterator(oth) { }
            ValueTypeReference operator*() const
            {
                return (*_Current);
            }
            ValueTypePointer operator->() const
            {
                return (&(**this);)
            }
            iterator& operator++()
            {
                ++*(const_iterator*)this;
                return (*this);
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                ++*(const_iterator*)this;
                return tmp;
            }
            iterator& operator--()
            {
                --*(const_iterator*)this;
                return (*this);
            }
            iterator operator--(int)
            {
                iterator tmp = *this;
                --*(const_iterator*)this;
                return tmp;
            }
            iterator operator+(int diff)
            {
                iterator tmp = *(const_iterator*)this + diff;
                return tmp;
            }
            iterator operator-(int diff)
            {
                iterator tmp = *(const_iterator*)this - diff;
                return tmp;
            }
            int operator-(iterator it)
            {
                return (*(const_iterator*)this - it);
            }
            operator ValueTypePointer()
            {
                return _Current;
            }
            ValueTypeReference operator[](int off) const
            {	
                return (*(*this + off));
            }
        };
        
    public:
        vector_base() : _Size(0), _Capacity(0), _Value(nullptr)
        {
        }
        vector_base(size_t size, ValueType dt) : _Size(size) ,_Capacity(_Size), _Value( new ValueType[_Capacity])
        {
            for (size_t i = 0; i < _Size; i++)
                _Value[i] = dt;
        }
        vector_base(const vector_base& oth) :_Size(oth._Size),_Capacity(oth._Capacity), _Value( new ValueType[_Capacity])
        {
            for (size_t i = 0; i < _Size; i++)
                _Value[i] = oth._Value[i];
        }
        ~vector_base()
        {
            if (_Capacity > 0)
                delete[] _Value;
        }

        void ReAlloc(size_t new_cap)
        {
            if (new_cap == 0)
                new_cap = 1;
            _Capacity = new_cap;
            auto tmp = _Value;
            _Value = new ValueType[_Capacity];
            for (size_t i = 0; i < _Size; i++)
                _Value[i] = tmp[i];
            if (tmp)
                delete[] tmp;
        }

    protected:
        size_t _Capacity;
        size_t _Size;
        ValueTypePointer _Value;

    };
    
    template<class _T>
    class vector : vector_base<_T>
    {
    public:
        typedef vector<_T> this_type;
        typedef vector_base<_T> base_type;
        typedef base_type::iterator iterator;
        typedef base_type::const_iterator const_iterator;
    public:
        vector(): vector_base() {}
        vector(size_t size , ValueType dt) : base_type(size,dt) {}
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
        const_iterator begin() const
        {
            return const_iterator(begin());
        }
        const_iterator end() const
        {
            return const_iterator(end());
        }

        void assign(iterator itstart, iterator itbegin, iterator itend)
        {
            size_t new_size = itend - itbegin;
            if (new_size > _Capacity)
                ReAlloc(new_size);
            _Size = new_size;
            ValueTypePointer pbegin，pend, pstart;
            pstart = itstart;
            pbegin = itbegin;
            pend = itend;

            for (; pbegin != pend; ++pbegin,++pstart)
                *pstart = *pbegin;
        }
        void assign(iterator itbegin, iterator itend)
        {
            assign(begin(), itbegin, itend);
        }

        ValueTypeReference elementAt(size_t index)
        {
            return (*this)[index];
        }


        void push_back(const ValueType& value)
        {
            if (_Size == _Capacity)
                ReAlloc(size_t(_Capacity * VECTOR_INCREASE_FACTOR));
            _Value[_Size++] = value;
        }
        void insert(const_iterator& index, const ValueType& value)
        {
           
            // 0<= index <= _Size-1
            int diff = -1;
            if (_Size == _Capacity)
            {
                diff = index - begin();
                ReAlloc(size_t(_Capacity * VECTOR_INCREASE_FACTOR));
            }  
            
            if (_Size == 0)
                push_back(value);
            else if ( index == end() )
                push_back(value);
            else
            {
                if( diff >= 0)
                    index = begin() + diff;

                // 使用指针操作。。。这里如果用迭代器的话，效率低的惊人
                ValueTypePointer v1, v2;
                v1 = end()._Current;
                v2 = v1 - 1;
                for (; v2 >= index._Current; v1--,v2--)
                    *v1 = *v2;
                _Size++;
                *index._Current = value;
                
            }
           
        }
        ValueType pop()
        {
            return _Value[--_Size];
        }

        iterator erase(const_iterator it1, const_iterator it2)
        {
            if (it1 == begin() && it2 == end())
                clear();
            else
            {
                ValueTypePointer it11 = iterator(it1);
                ValueTypePointer it22 = iterator(it2);
                auto itend = end();
                for (; it22 != itend._Current; ++it22, ++it11)
                    *it11 = *it22;
                _Size -= it22 - it11;
            }
            return iterator(it1);
        }

        void clear()
        {
            if (_Capacity)
                delete[] _Value;
            _Size = _Capacity = 0;
        }

        // vector[5] = xxx;
        ValueTypeReference operator[](size_t index)
        {
            // 0 <= index <= _Size-1;
            return _Value[index];
        }
        // xxx =  vector[5];
        const ValueTypeReference operator[](size_t index) const
        {
            // 0 <= index <= _Size-1;
            return _Value[index];
        }
        this_type& operator=(const this_type& oth)
        {
            // 只装有用的
            assign(oth.begin(), oth.end());
        }
    };

}
#endif
