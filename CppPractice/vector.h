#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "algorithm.h"
#include "uninitialized.h"

namespace sp
{
#define VECTOR_INCREASE_FACTOR (2)

    template<class _T>
    class vector_base
    {
    public:
        typedef _T            value_type;
        typedef _T*           pointer;
        typedef const _T*     const_pointer;
        typedef _T&           reference;
        typedef const _T&     const_reference;
        typedef size_t        size_type;
        typedef ptrdiff_t     difference_type;

        class const_iterator
        {
        public:
            const_iterator(pointer vtp) : _Current(vtp) {}
            const_iterator(const const_iterator& oth) : _Current(oth._Current) {}
            inline const_iterator& operator++()
            {
                _Current++;
                return (*this);
            }
            inline const_iterator operator++(int)
            {
                const_iterator tmp = *this;
                ++*this;
                return tmp;
            }
            inline const_iterator& operator--()
            {
                _Current--;
                return (*this);
            }
            inline const_iterator operator--(int)
            {
                const_iterator tmp = *this;
                --*this;
                return tmp;
            }
            inline const_iterator operator+(difference_type diff)
            {
                return _Current + diff;
            }
            inline const_iterator operator-(difference_type diff)
            {
                return _Current - diff;
            }
            inline difference_type operator-(const const_iterator& oth) const
            {
                return _Current - oth._Current;
            }
            inline const reference operator*() const
            {
                return (*_Current);
            }
            inline const pointer operator->() const
            {
                return (&(**this));
            }

            inline bool operator==(const const_iterator& oth) const
            {
                return _Current == oth._Current;
            }
            inline bool operator!=(const const_iterator& oth) const
            {
                return !((*this) == oth);
            }
            inline bool operator<(const const_iterator& oth) const
            {
                return (oth - (*this)) > 0;
            }
            inline bool operator>(const const_iterator& oth) const
            {
                return ((*this) - oth) > 0;
            }
            inline bool operator<=(const const_iterator& oth) const
            {
                return (*this) < oth || *this == oth;
            }
            inline bool operator>=(const const_iterator& oth) const
            {
                return (*this) > oth || *this == oth;
            }

            pointer _Current;
        };
        class iterator : public const_iterator
        {
        public:
            iterator() : const_iterator(nullptr) {}
            iterator(const pointer vtp) : const_iterator(vtp) {}
            iterator(const const_iterator& oth) : const_iterator(oth) { }

            void operator=(const pointer ptr)
            {
                _Current = ptr;
            }

            inline reference operator*() const
            {
                return (*_Current);
            }
            inline pointer operator->() const
            {
                return _Current;
            }
            inline iterator& operator++()
            {
                ++*(const_iterator*)this;
                return (*this);
            }
            inline iterator operator++(int)
            {
                iterator tmp = *this;
                ++*(const_iterator*)this;
                return tmp;
            }
            inline iterator& operator--()
            {
                --*(const_iterator*)this;
                return (*this);
            }
            inline iterator operator--(int)
            {
                iterator tmp = *this;
                --*(const_iterator*)this;
                return tmp;
            }
            inline iterator operator+(difference_type diff) const
            {
                iterator tmp = *(const_iterator*)this + diff;
                return tmp;
            }
            inline iterator operator-(difference_type diff) const
            {
                iterator tmp = *(const_iterator*)this - diff;
                return tmp;
            }
            inline difference_type operator-(const iterator& it) const
            {
                return (*(const_iterator*)this - it);
            }
            inline operator pointer()
            {
                return _Current;
            }
            inline reference operator[](int off) const
            {	
                return (*(*this + off));
            }
        };
        
    public:
        vector_base()
        {
            _begin = _end = _end_capacity;
            count = 0;
        }
        vector_base(size_t size, value_type dt) 
        {
            _begin = new value_type[size];
            _end = _end_capacity = _begin + size;
            
        }

        ~vector_base()
        {
            dealloc();
        }

        void dealloc()
        {
            if (_begin._Current)
                delete[] _begin._Current;
            _begin._Current = nullptr;
        }

        inline size_type capacity()
        {
            return _end_capacity - _begin;
        }

        inline size_type size()
        {
            return _end - _begin;
        }

    protected:
        iterator _begin;
        iterator _end;
        iterator _end_capacity;

    public:
        int count;
    };
    
    template<class _T>
    class vector : public vector_base<_T>
    {
    public:
        typedef vector<_T> this_type;
        typedef vector_base<_T> base_type;
        typedef base_type::iterator iterator;
        typedef base_type::const_iterator const_iterator;
        typedef base_type::size_type size_type;
        typedef base_type::difference_type difference_type;

    public:
        vector(): vector_base() {}
        vector(size_type size , value_type dt) : base_type(size,dt) {}
        // 这里没有拷贝构造函数，这个行为由vector_base<_T>来完成
        // vector<_T>默认的浅拷贝，会调用vector_base<_T>的拷贝构造函数
        
        inline iterator begin()
        {
            return _begin;
        }
        inline iterator end()
        {
            return _end;
        }
        inline const_iterator begin() const
        {
            return _begin;
        }
        inline const_iterator end() const
        {
            return _end;
        }


        void push_back(const value_type& value)
        {
            if (_end != _end_capacity)
            {
                Construct(_end, value);
                _end++;
            }
            else
                insert(end(), value);
        }
        inline void push_back() 
        {
            push_back(value_type());
        }

        iterator insert(const iterator& position, const value_type& value)
        {
            size_type n = position - begin();
            if (_end != _end_capacity && position == end())
            {
                sp::Construct(_end, value);
                _end++;
            }

            else
                insert_aux(position, value);
            return begin() + n;
        }
        inline iterator insert(iterator position)
        {
            insert(position, value_type());
        }
        void insert_aux(iterator position, const value_type& x)
        {
            if (_end != _end_capacity)
            {
                Construct(_end, *(_end - 1));
                value_type x_copy = x;

                iterator cur1 = _end-2;
                iterator cur2 = _end-1;
                for (; cur2 != position; --cur1, --cur2)
                    *cur2 = *cur1;

                *position = x_copy;
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size != 0 ? VECTOR_INCREASE_FACTOR * old_size : 1;


                count++;
                iterator new_begin = new value_type[len];
                iterator new_end = new_begin;

                // uninitizlized_copy(begin(),position,new_end);
                
                new_end = uninitialized_copy(_begin, position, new_end);
                /*
                    // they are equal .
                    iterator cur = begin();
                    while (cur != position)
                        *new_end++ = *cur++;
                */

                *new_end++ = x;

                new_end = uninitialized_copy(position, end(), new_end);
                /*
                    // they are equal
                    while (cur != end())
                        *new_end++ = *cur++;
                */

                // 析构
                Destroy(_begin, _end);

                // 释放内存
                if (pointer(_begin))
                    delete[] pointer(_begin);

                _begin = new_begin;
                _end = new_end;
                _end_capacity = _begin + len;
            }

        }

        void pop_back()
        {
            --_end;
            Destroy(_end);
        }

        iterator erase(iterator position)
        {
            if (last + 1 != end())
                copy(position + 1, end(), position);
            --_end;
            Destroy(_end);
            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            iterator i = copy(last, _end, first);
            Destroy(i, _end);
            _end = _end - (last - first);
            return first;
        }

        void clear()
        {
            erase(_begin, _end);
        }

        // vector[5] = xxx;
        reference operator[](size_t index)
        {
            return *(_begin._Current + index);
        }
        // xxx =  vector[5];
        const value_type operator[](size_t index) const
        {
            // 0 <= index <= _Size-1;
            return return *(_begin._Current + index);
        }
    };

}
#endif
