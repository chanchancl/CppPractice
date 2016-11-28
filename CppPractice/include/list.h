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

		ListNodeBase() : _next(nullptr), _prev(nullptr) {}
		ListNodeBase(ListNodeBase* next, ListNodeBase* prev = nullptr) : _next(next), _prev(prev) {}

		void insert(ListNodeBase *next)
		{
			_next = next;
			_prev = next->_prev;
			next->_prev->_next = this;
			next->_prev = this;
		}
		void remove()
		{
			_next->_prev = _prev;
			_prev->_next = _next;
		}
	};

	template <typename T>
	class ListNode : public ListNodeBase
	{
	public:
		T _value;
	};

	// Pointer Reference
	// const pointer
	template <typename T, typename Pointer, typename Reference>
	class ListIterator
	{
	public:
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
		ListIterator& operator++()
		{
			this->_node = static_cast<node_type*>(this->_node->_next);
			return *this;
		}
		ListIterator operator++(int)
		{
			ListIterator tmp(*this);
			this->_node = static_cast<node_type*>(this->_node->_next);
			return tmp;
		}
		ListIterator& operator--()
		{
			this->_node = static_cast<node_type*>(this->_node->_prev);
			return *this;
		}
		ListIterator operator--(int)
		{
			ListIterator tmp(*this);
			this->_node = static_cast<node_type*>(this->_node->_prev);
			return tmp;
		}

		inline bool operator==(const ListIterator& oth)
		{
			return this->_node == oth._node;
		}
		inline bool operator!=(const ListIterator& oth)
		{
			return this->_node != oth._node;
		}

		reference operator*() const
		{
			return _node->_value;
		}
		pointer	  operator->() const
		{
			return &_node->_value;
		}
		

	private:
		node_type *_node;
	};

	template <typename T>
	class ListBase
	{
	public:
		typedef T										value_type;
		typedef value_type&								reference;
		typedef ListNode<T>								node_type;
		typedef node_type*								node_pointer;
		typedef ListNodeBase							node_base_type;
		typedef node_base_type*							node_base_pointer;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;

	public:
		ListBase() : _node(&_node,&_node) {}
		ListBase(size_type size)
		{
			_node->_next = alloc(size);
		}
		~ListBase()
		{
			dealloc();
		}

		node_pointer alloc_node(const value_type& x)
		{
			node_pointer pNode = (node_pointer)malloc(sizeof(node_type));
			new(&pNode->_value) value_type(x);
			return pNode;
		}

		node_pointer alloc(size_type size, node_pointer new_node = nullptr)
		{
			node_pointer ret, cur;
			ret = cur = new node_type;
			if (size != 0)
				size - 1;
			while (size--)
				cur = cur->_next = new node_type;
			if (new_node)
			{
				cur->_next = new_node;
				new_node->_prev = cur;
			}
			else
			{
				cur->_next = &_node;
				_node->_prev = cur;
			}
			return ret;
		}

		void dealloc()
		{
			node_base_pointer cur = _node._next;

			while( cur != &_node  /*&& cur != nullptr*/ )
			{
				cur = cur->_next;  // 先跳到下个元素，然后删除上个元素。
				delete cur->_prev;
			}
			_node._prev = _node._next = &_node;
		}

		void dealloc_node(const node_pointer node)
		{
			if (node)
				free(node);
		}

	protected:
		node_base_type _node;
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

		using base_type::_node;

	public:
		list() : ListBase() {}

		iterator	   begin()
		{
			return iterator((node_type*)_node._next);
		}
		const_iterator begin() const
		{
			return const_iterator((node_type*)_node.next);
		}
		const_iterator cbegin() const
		{
			return const_iterator((node_type*)_node.next);
		}

		iterator	   end()
		{
			return iterator((node_type*)&_node);
		}
		const_iterator end() const
		{
			return iterator((node_type*)&_node);
		}
		const_iterator cend() const
		{
			return const_iterator((node_type*)&_node);
		}
		
		bool	  empty()
		{
			return _node._next == &_node;
		}
		size_type size()
		{
			return sp::distance(begin(), end());
		}

		reference  front()
		{
			// make sure  list is not empty
			return *_node._next->_value;
		}
		value_type front() const
		{
			return *_node._next->_value;
		}
		reference  back()
		{
			return *_node._prev->_value;
		}
		value_type back() const
		{
			return *_node._prev->_value;
		}

		void push_front(const reference x)
		{
			node_type* pNode = alloc_node(x);

			pNode->insert(_node._next);
		}
		void push_back(const reference x)
		{
			node_type* pNode = alloc_node(x);

			pNode->insert(&_node);
		}

		void pop_front()
		{
			node_type* pNode = _node._next;
			pNode->remove();
			node_type*(pNode)->~node_type();
			
		}
		void pop_back()
		{
			node_type* pNode = _node._prev;
			pNode->remove();
			node_type*(pNode)->~node_type();
		}

		iterator erase(const_iterator position)
		{
			++position;

			delete position._node->_prev;
			return iterator(position._node);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			while (first != last)
				erase(first);
			return iterator(last._node);
		}

		void clear()
		{
			dealloc();
		}
	};

}

#endif