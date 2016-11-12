#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "algorithm.h"
#include "uninitialized.h"


// 越写越乱了。。。尴尬 

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
        typedef pointer       iterator;
        typedef const pointer const_iterator;

    public:
        vector_base()
        {
            _begin = _end = _end_capacity = nullptr;
        }
        vector_base(size_t size, value_type dt) 
        {
            _end = _begin = new value_type[size];
            for (int i = 0; i < size; i++)
            {
                *_end = dt;
                ++_end;
            }
            _end_capacity = _end;
            
        }

        ~vector_base()
        {
            dealloc();
        }

        void dealloc()
        {
            if (_begin)
                delete[] _begin;
            _begin = nullptr;
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
        typedef vector<_T>                  this_type;
        typedef vector_base<_T>             base_type;
        typedef base_type::iterator         iterator;
        typedef base_type::const_iterator   const_iterator;
        typedef base_type::size_type        size_type;
        typedef base_type::difference_type  difference_type;

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
                insert(_end, value);
        }
        inline void push_back() 
        {
            push_back(value_type());
        }

        iterator insert(iterator position, const value_type& value)
        {
            size_type n = position - begin();
            if (_end != _end_capacity && position == _end)
            {
                Construct(_end, value);
                ++_end;
            }

            else
                insert_aux(position, value);
            return begin() + n;
        }
        inline iterator insert(iterator position)
        {
            insert(position, value_type());
        }
        iterator insert(iterator position, size_type n, const value_type& value)
        {
            if (n > 0)
            {
                if (n == 1)
                    return insert(position, value);

                size_type old_n = position - _begin;
                if (position == _end && (_end_capacity - _end) >= n)
                {
                    // 可以插入到尾部
                    iterator end = position + n;
                    for (; _end != end; ++_end)
                        sp::Construct(_end, value);
                }
                else
                    insert_fill(position, n, value);

                return _begin + old_n;
            }
        }
        void insert_aux(iterator position, const value_type& x)
        {
            if (_end != _end_capacity)
            {
                Construct(_end, *(_end - 1));
                value_type x_copy = x;

                /*iterator cur1 = _end-2;
                iterator cur2 = _end-1;*/
                copy_backward(position, _end - 2, _end - 1);
               /* for (; cur2 != position; --cur1, --cur2)
                    *cur2 = *cur1;*/

                *position = x_copy;
                ++_end;
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size != 0 ? VECTOR_INCREASE_FACTOR * old_size : 1;

                iterator new_begin = new value_type[len];
                iterator new_end = new_begin;

                new_end = uninitialized_copy(_begin, position, new_end);

                *new_end = x;
                ++new_end;

                new_end = uninitialized_copy(position, end(), new_end);

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
        void insert_fill(iterator position, size_type n, const value_type& value)
        {
           
            if (_end_capacity - _end >= n)
            {
                // 剩余空间可以放下，不必重新分配空间
                copy_backward(position, _end, position + n);

                fill(position, position + n, value);
            }
            else
            {
                // 需要重新分配空间
                const size_type old_size = size();
                const size_type len = old_size != 0 ? VECTOR_INCREASE_FACTOR * old_size : 1;
                if (len - old_size < n)
                    len = old_size + n;

                iterator new_begin = new value_type[len];
                iterator new_end = new_begin;

                new_end = uninitialized_copy(_begin, position, new_end);

                new_end = fill(_new_end, new_end + n, value);

                new_end = uninitialized_copy(position, end(), new_end);

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
            return *(_begin + index);
        }
        // xxx =  vector[5];
        const value_type operator[](size_t index) const
        {
            // 0 <= index <= _Size-1;
            return return *(_begin + index);
        }
    };

}
#endif
