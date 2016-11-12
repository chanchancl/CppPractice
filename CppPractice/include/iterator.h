#pragma once

#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <type_traits.h>
#include <stddef.h>

namespace sp
{

    // iterator category
    struct input_iterator_tag {};
    struct outpur_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<typename Category, typename T, typename Distance = ptrdiff_t,
             typename Pointer = T*, typename Reference = T&>
    struct iterator
    {
        typedef Category  iterator_category;
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
    };

    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
    };

    // 定义原生指针的 traits
    template <typename T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef T*                         pointer;
        typedef T&                         reference;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef const T*                   pointer;
        typedef const T&                   reference;
    };


    // reverse_iterator
    template <typename Iterator>
    class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
                                             typename iterator_traits<Iterator>::value_type,
                                             typename iterator_traits<Iterator>::difference_type,
                                             typename iterator_traits<Iterator>::pointer,
                                             typename iterator_traits<Iterator>::reference>
    {
    public:
        typedef Iterator                                            iterator_type;
        typedef typename iterator_traits<Iterator>::pointer         pointer;
        typedef typename iterator_traits<Iterator>::reference       reference;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;

    protected:
        Iterator _Iterator;

    public:
        reverse_iterator() 
            : _Iterator() {}

        explicit reverse_iterator(iterator_type i) 
            : _Iterator(i) {}

        reverse_iterator(const reverse_iterator& ri)
            : _Iterator(ri._Iterator) {}

        iterator_type base() const
            { return _Iterator; }

        reference operator*() const
        {
            iterator_type i(_Iterator);
            return *--i;
        }

        reverse_iterator& operator++()
        {
            --_Iterator; return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator ri(*this);
            --_Iterator;
            return ri;
        }

        reverse_iterator& operator--()
        {
            ++_Iterator; return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator ri(*this);
            ++_Iterator;
            return ri;
        }

        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(_Iterator - n);
        }

        reverse_iterator& operator+=(difference_type n)
        {
            _Iterator -= n; return *this;
        }

        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(_Iterator + n);
        }

        reverse_iterator& operator-=(difference_type n)
        {
            _Iterator += n; return *this;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }

    };

    template <typename Iterator1, typename Iterator2>
    inline bool
        operator==(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return a.base() == b.base();
    }


    template <typename Iterator1, typename Iterator2>
    inline bool
        operator<(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return a.base() > b.base();
    }


    template <typename Iterator1, typename Iterator2>
    inline bool
        operator!=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return a.base() != b.base();
    }


    template <typename Iterator1, typename Iterator2>
    inline bool
        operator>(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return a.base() < b.base();
    }


    template <typename Iterator1, typename Iterator2>
    inline bool
        operator<=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return a.base() >= b.base();
    }


    template <typename Iterator1, typename Iterator2>
    inline bool
        operator>=(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return a.base() <= b.base();
    }


    template <typename Iterator1, typename Iterator2>
    inline typename reverse_iterator<Iterator1>::difference_type
        operator-(const reverse_iterator<Iterator1>& a, const reverse_iterator<Iterator2>& b)
    {
        return b.base() - a.base();
    }


    template <typename Iterator>
    inline reverse_iterator<Iterator>
        operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& a)
    {
        return reverse_iterator<Iterator>(a.base() - n);
    }

    // is_reverse_iterator
    template <typename T>
    struct is_reverse_iterator
        : public sp::false_type {};

    template<typename Iterator>
    struct is_reverse_iterator< sp::reverse_iterator<Iterator> >
        : public sp::true_type {};


    // distance
    template <typename InputIterator>
    inline typename sp::iterator_traits<InputIterator>::difference_type
    distance_impl(InputIterator first, InputIterator last, sp::input_iterator_tag)
    {
        typename sp::iterator_traits<InputIterator>::difference_type n = 0;

        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <typename RandomAccessIterator>
    inline typename sp::iterator_traits<RandomAccessIterator>::difference_type
    distance_impl(RandomAccessIterator first, RandomAccessIterator last, sp::random_access_iterator_tag)
    {
        return last - first;
    }

    template <typename InputIterator>
    inline typename sp::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typedef typename sp::iterator_traits<InputIterator>::iterator_category IC;

        return sp::distance_impl(first, last, IC());
    }



}

#endif