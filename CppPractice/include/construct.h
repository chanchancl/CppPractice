#pragma once

#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <iterator.h>
#include <type_traits.h>
#include <stddef.h>

namespace sp
{

    // 使用 replacement new
    // 在memory所指的位置，构造一个 value 的复制品。
    template <class ForwardIter, class T>
    inline void construct(ForwardIter iter, const T& value)
    {
        new(static_cast<void*>(&*iter)) T(value);
    }

    template <class ForwardIter>
    inline void construct(const ForwardIter iter)
    {
        typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;

        new(static_cast<void*>(&*iter)) value_type();
    }

    template <class T >
    inline void _destroy(const T* /*pointer*/, true_type)
    {
        // do nothing
    }

    template <class T >
    inline void _destroy(const T* pointer, false_type)
    {
        pointer->~T();
    }

    // 析构 iter 指向的元素
    template <class ForwardIter >
    inline void destroy(const ForwardIter iter)
    {
        typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;

        _destroy(&*iter,sp::has_trivial_destructor<value_type>());
    }

    // 析构 first 和 last 之间的所有元素。
    template <class ForwardIter>
    inline void destroy(ForwardIter first, ForwardIter last)
    {
        for (; first != last; ++first)
            destroy(first);
    }

    // copy
    // 确定数据区不会重叠，就使用copy
	// 
    template <class InputIter, class OutIter>
    inline OutIter copy_impl(InputIter first, InputIter last, OutIter result, true_type)
    {
        typedef typename iterator_traits<InputIter>::value_type value_type;

        ::memcpy(&*result, &*first, sizeof(value_type)*(last - first));

        return result + (last-first);
    }

	template <class InputIter, class OutIter>
	inline OutIter copy_impl(InputIter first, InputIter last, OutIter result, false_type)
	{
		typedef typename iterator_traits<InputIter>::value_type value_type;

		for (; first != last; ++first, ++result)
			*result = *first;

		return result + (last - first);
	}

	template <class InputIter, class OutIter>
	inline OutIter copy(InputIter first, InputIter last, OutIter result)
	{
		typedef typename iterator_traits<InputIter>::value_type value_type;

		return copy_impl(first, last, result, is_pod<value_type>());
	}

    // copy_backward
    // 如果数据区重叠，可以用 copy_backward
    template <class InputIter, class OutIter>
    inline OutIter copy_backward_impl(InputIter first, InputIter last, OutIter resultEnd, true_type)
    {
        typedef typename iterator_traits<InputIter>::value_type value_type;

        return (OutIter)::memmove(&*(resultEnd - (last - first)), &*first, sizeof(value_type)*(last - first));
    }

	template <class InputIter, class OutIter>
	inline OutIter copy_backward_impl(InputIter first, InputIter last, OutIter resultEnd, false_type)
	{
		for (; last != first; --last, --resultEnd)
			*resultEnd = *last;

		return first;
	}

	template <class InputIter, class OutIter>
	inline OutIter copy_backward(InputIter first, InputIter last, OutIter resultEnd)
	{
		typedef typename iterator_traits<InputIter>::value_type value_type;

		return copy_backward_impl(first, last, resultEnd, is_pod<value_type>());
	}


    template <bool bIsScalar>
    struct fill_imp
    {
        template <typename ForwardIter, typename T>
        static void do_fill(ForwardIter first, ForwardIter last, const T& value)
        {
            for (; first != last; ++first)
                *first = value;
        }
    };

    template <>
    struct fill_imp<true>
    {
        template <typename ForwardIter, typename T>
        static void do_fill(ForwardIter first, ForwardIter last, const T& value)
        {
            typedef typename sp::iterator_traits<ForwardIter>::value_type value_type;
            for (const T temp = value; first != last; ++first)
            {
                (void)temp;
                *first = static_cast<value_type>(temp);
            }
        }
    };

    template <class InputIter, class T>
    inline void fill(InputIter first, InputIter last, const T& value)
    {
        return fill_imp<is_scalar<T>::value>::do_fill(first, last, value);
    }

    inline void fill(char* first, char* last, const char& c) // It's debateable whether we should use 'char& c' or 'char c' here.
    {
        memset(first, (unsigned char)c, (size_t)(last - first));
    }

    inline void fill(char* first, char* last, const int c) // This is used for cases like 'fill(first, last, 0)'.
    {
        memset(first, (unsigned char)c, (size_t)(last - first));
    }

    inline void fill(unsigned char* first, unsigned char* last, const unsigned char& c)
    {
        memset(first, (unsigned char)c, (size_t)(last - first));
    }

    inline void fill(unsigned char* first, unsigned char* last, const int c)
    {
        memset(first, (unsigned char)c, (size_t)(last - first));
    }

    inline void fill(signed char* first, signed char* last, const signed char& c)
    {
        memset(first, (unsigned char)c, (size_t)(last - first));
    }

    inline void fill(signed char* first, signed char* last, const int c)
    {
        memset(first, (unsigned char)c, (size_t)(last - first));
    }

    template <bool bIsScalar>
    struct fill_n_imp
    {
        template <typename OutputIter, typename Size, typename T>
        static OutputIter do_fill(OutputIter first, Size n, const T& value)
        {
            for (; n-- > 0; ++first)
                *first = value;
            return first;
        }
    };
    template <>
    struct fill_n_imp<true>
    {
        template <typename OutputIter, typename Size, typename T>
        static OutputIter do_fill(OutputIter first, Size n, const T& value)
        {
            typedef typename sp::iterator_traits<OutputIter>::value_type value_type;

            for (const T temp = value; n-- > 0; ++first)
                *first = static_cast<value_type>(temp);
            return first;
        }
    };


    template <typename OutputIter, typename Size, typename T>
    OutputIter fill_n(OutputIter first, Size n, const T& value)
    {
        return fill_n_imp< is_scalar<T>::value>::do_fill(first, n, value);
    }

    template <typename Size>
    inline char* fill_n(char* first, Size n, const char& c)
    {
        return (char*)memset(first, (char)c, (size_t)n) + n;
    }

    template <typename Size>
    inline unsigned char* fill_n(unsigned char* first, Size n, const unsigned char& c)
    {
        return (unsigned char*)memset(first, (unsigned char)c, (size_t)n) + n;
    }

    template <typename Size>
    inline signed char* fill_n(signed char* first, Size n, const signed char& c)
    {
        return (signed char*)memset(first, (signed char)c, n) + (size_t)n;
    }

    template <typename Size>
    inline bool* fill_n(bool* first, Size n, const bool& b)
    {
        return (bool*)memset(first, (char)b, n) + (size_t)n;
    }

}


#endif