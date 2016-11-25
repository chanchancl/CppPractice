#pragma once

#ifndef __LIST_H__
#define __LIST_H__

#include <iterator.h>

namespace sp
{

	class ListNodeBase
	{
	public:
		ListNodeBase *_next;
		ListNodeBase *_prev;

	public:
		ListNodeBase() : _next(nullptr), _prev(nullptr) {}
		ListNodeBase(ListNodeBase* next, ListNodeBase* prev = nullptr) : _next(next), _prev(prev) {}
	};

	template <typename T>
	class ListNode : public ListNodeBase
	{
	public:
		typedef T         value_type;
		typedef T*        pointer;

	public:
		ListNode() : ListNodeBase() {}
		ListNode(pointer next, pointer prev = nullptr) : ListNodeBase(next,prev) {}

	private:
		T _value;
	};

	// Pointer Reference
	// const pointer
	template <typename T, typename Pointer, typename Reference>
	class ListIterator
	{
		typedef ListIterator<T,Pointer,Reference>	this_type;
		typedef T									value_type;
		typedef Pointer								pointer;
		typedef Reference							reference;
		typedef size_t								size_type;
		typedef ptrdiff_t							difference_type;
		typedef ListNode<T>							node_type;
		typedef sp::bidirectional_iterator_tag		iterator_category;
		
	public:
		ListIterator() : _node(nullptr) {}
		ListIterator(const node_type *node) : _node(static_cast<node_type*>(const_cast<ListNode<T>*>(node))) {}
		ListIterator(const this_type &iter) : _node(iter._node) {}

		// operator 
		// + -  ++ --

	private:
		node_type *_node;
	};

	template <typename T>
	class ListBase
	{
	public:
		typedef T										value_type;
		typedef ListNode<T>								node_type;
		typedef node_type*								node_pointer;
		typedef ListNodeBase							node_base_type;
		typedef node_base_type*							node_base_pointer;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;

	public:
		ListBase() : _begin(&_begin,&_begin) {}
		ListBase(size_type size)
		{
			_begin->_next = alloc(size);
		}
		~ListBase()
		{
			dealloc();
		}

		node_pointer* alloc(size_type size)
		{
			node_pointer ret, cur;
			ret = cur = new node_type;
			while (size--)
				cur = cur->_next = new node_type;
			cur->_next = &_begin;
			_begin->_prev = cur;
			return ret;
		}

		void dealloc()
		{
			node_base_pointer cur = _begin._next;

			while( cur != &_begin  /*&& cur != nullptr*/ )
			{
				cur = cur->_next;  // 先跳到下个元素，然后删除上个元素。
				delete cur->_prev;
			}
			_begin._prev = _begin._next = &_begin;
		}

	protected:
		node_base_type _begin;
	};

	template <typename T>
	class list : public ListBase<T>
	{
	public:
		typedef list<T>									this_type;
		typedef ListBase<T>								base_type;
		typedef T                                       value_type;
		typedef T*                                      pointer;
		typedef const T*                                const_pointer;
		typedef T&                                      reference;
		typedef const T&                                const_reference;
		typedef ListIterator<T, T*, T&>                 iterator;
		typedef ListIterator<T, const T*, const T&>     const_iterator;
		typedef sp::reverse_iterator<iterator>			reverse_iterator;
		typedef sp::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename base_type::size_type           size_type;
		typedef typename base_type::difference_type     difference_type;
		typedef typename base_type::node_type           node_type;
		typedef typename base_type::node_base_type      node_base_type;

		using base_type::_begin;

	public:
		list() {}

		iterator	   begin()
		{
			return iterator((node_type*)_begin._next);
		}
		const_iterator begin() const
		{
			return const_iterator((node_type*)_begin.next);
		}
		const_iterator cbegin() const
		{
			return const_iterator((node_type*)_begin.next);
		}

		iterator	   end()
		{
			return iterator((node_type*)_begin._prev);
		}
		const_iterator end() const
		{
			return iterator((node_type*)_begin._prev);
		}
		const_iterator cend() const
		{
			return const_iterator((node_type*)_begin._prev);
		}
		
		bool	  empty()
		{
			return _begin._next == &_begin;
		}
		size_type size()
		{
			return 0;
		}
	};

}

#endif