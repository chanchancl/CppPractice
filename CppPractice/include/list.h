#pragma once

#ifndef __LIST_H__
#define __LIST_H__

#include <iterator.h>

namespace sp
{

	struct ListNodeBase
	{
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

		template <typename Pointer2, typename Reference2>
		inline bool operator==(const ListIterator<T,Pointer2,Reference2>& oth)
		{
			return this->_node == oth._node;
		}
		template <typename Pointer2, typename Reference2>
		inline bool operator!=(const ListIterator<T, Pointer2, Reference2>& oth)
		{
			return this->_node != oth._node;
		}

		template <typename Pointer2, typename Reference2>
		operator ListIterator<T, Pointer2, Reference2>()
		{
			return ListIterator<T, Pointer2, Reference2>(this->_node);
		}

		reference operator*() const
		{
			return _node->_value;
		}
		pointer	  operator->() const
		{
			return &_node->_value;
		}
		

	public:
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
		~ListBase()
		{
			dealloc();
		}

		node_pointer alloc_node()
		{
			return (node_pointer)malloc(sizeof(node_type));
		}
		node_pointer create_node(const value_type& value)
		{
			node_pointer pNode = alloc_node();
			sp::construct(&pNode->_value, value);
			return pNode;
		}

		node_pointer alloc(size_type size, node_pointer new_node = nullptr)
		{
			node_pointer ret, cur;
			ret = cur = alloc_node();
			
			while (size--)
				cur = cur->_next = alloc_node();
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
				dealloc_node(static_cast<node_pointer>(cur->_prev));
			}
			_node._prev = _node._next = &_node;
		}

		void dealloc_node(const node_pointer node)
		{
			if (node)
			{
				sp::destroy(&node->_value);
				free(node);
			}
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
		typedef node_type*								node_pointer;
		typedef typename base_type::node_base_type      node_base_type;
		typedef node_base_type*							node_base_pointer;

		using base_type::_node;
		using base_type::create_node;
		using base_type::alloc_node;
		using base_type::dealloc_node;
		using base_type::alloc;
		using base_type::dealloc;

	public:
		list() : base_type() {}
		list(size_type size, const value_type& value)
		{
			insert(cbegin(), size, value);
		}
		list(const this_type& oth)
		{
			insert(cbegin(), oth.begin(), oth.end());
		}

		this_type& operator=(const this_type& oth)
		{
			if (this != &oth)
			{
				clear();
				insert(begin(),oth.cbegin(), oth.cend());
			}
		}

		iterator	   begin()
		{
			return iterator(node_pointer(_node._next));
		}
		const_iterator begin() const
		{
			return const_iterator(node_pointer(_node._next));
		}
		const_iterator cbegin() const
		{
			return const_iterator(node_pointer(_node._next));
		}

		iterator	   end()
		{
			return iterator(node_pointer(&_node));
		}
		const_iterator end() const
		{
			return const_iterator(node_pointer(&_node));
		}
		const_iterator cend() const
		{
			return const_iterator(node_pointer(&_node));
		}

		reverse_iterator	   rbegin()
		{
			return reverse_iterator(node_pointer(_node._prev));
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(node_pointer(_node._prev));
		}
		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(node_pointer(_node._prev));
		}

		reverse_iterator	   rend()
		{
			return reverse_iterator(node_pointer(&_node));
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(node_pointer(&_node));
		}
		const_reverse_iterator cren() const
		{
			return const_reverse_iterator(node_pointer(&_node));
		}

		
		bool	   empty()
		{
			return _node._next == &_node;
		}
		size_type  size()
		{
			return sp::distance(begin(), end());
		}

		reference  front()
		{
			// make sure  list is not empty
			return node_pointer(_node._next)->_value;
		}
		value_type front() const
		{
			return node_pointer(_node._next)->_value;
		}
		reference  back()
		{
			return node_pointer(_node._prev)->_value;
		}
		value_type back() const
		{
			return node_pointer(_node._prev)->_value;
		}

		void push_front(const value_type& x)
		{
			node_pointer pNode = create_node(x);

			node_base_pointer(pNode)->insert(_node._next);
		}
		void push_back(const value_type& x)
		{
			node_pointer pNode = create_node(x);

			node_base_pointer(pNode)->insert(&_node);
		}

		void pop_front()
		{
			node_pointer pNode = _node._next;
			pNode->remove();
			dealloc_node(pNode);
		}
		void pop_back()
		{
			node_pointer pNode = _node._prev;
			pNode->remove();
			dealloc_node(pNode);
		}

		iterator insert(const_iterator position, const value_type& x)
		{
			node_pointer pNode = create_node(x);
			node_base_pointer(pNode)->insert(position._node);

			return pNode;
		}
		void	 insert(const_iterator position, size_type size, const value_type& x)
		{
			while (size--)
			{
				node_pointer pNode = create_node(x);
				node_base_pointer(pNode)->insert(position._node);
			}
		}
		void	 insert(const_iterator position, const_iterator first, const_iterator last)
		{
			// 将[first,last)中的元素依次插入到position后
			for (; first != last; ++first, ++position)
			{
				node_pointer pNode = create_node(*first);
				node_base_pointer(pNode)->insert(position._node);
			}
		}

		iterator erase(const_iterator position)
		{
			++position;

			node_base_pointer pNode = position._node->_prev;
			pNode->remove();
			dealloc_node(node_pointer(pNode));
			return iterator(position._node);
		}
		iterator erase(const_iterator first, const_iterator last)
		{
			while (first != last)
				first = erase(first);
			return iterator(last._node);
		}

		void clear()
		{
			dealloc();
		}
	};

	template<typename T>
	bool operator==(const list<T>& li1, const list<T>& li2)
	{
		return sp::equal(li1.begin(), li1.end(), li2.begin());
	}

}

#endif