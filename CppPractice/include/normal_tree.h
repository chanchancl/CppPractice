#pragma once

#ifndef __NORMAL_TREE_H__
#define __NORMAL_TREE_H__

#include <stdlib.h>
#include <iterator.h>
#include <functional.h>

namespace sp
{
	// 先来试试写，非平衡二叉树


	// tree_node_base
	struct BaseNormalTreeNode
	{
		BaseNormalTreeNode *_parent, *_lchild, *_rchild;
		BaseNormalTreeNode(BaseNormalTreeNode* p = nullptr) : _parent(p), _lchild(nullptr), _rchild(nullptr) {}

	};

	template <typename T>
	struct NormalTreeNode : public BaseNormalTreeNode
	{
		NormalTreeNode(NormalTreeNode* p = nullptr) : BaseNormalTreeNode(p) {}
		T _value;
	};

	template <typename T, typename Pointer, typename Reference>
	class NormalTreeIterator
	{
	public:
		typedef NormalTreeIterator<T, Pointer, Reference>		this_type;
		typedef NormalTreeIterator<T, T*, T&>					iterator;
		typedef NormalTreeIterator<T, const T*, const T&>		const_iterator;
		typedef size_t											size_type;
		typedef ptrdiff_t										different_type;
		typedef T												value_type;
		typedef BaseNormalTreeNode								base_node_type;
		typedef NormalTreeNode<T>								node_type;
		typedef Pointer											pointer;
		typedef Reference										reference;
		typedef sp::bidirectional_iterator_tag					iterator_category;

	public:
		node_type *_node;

	public:
		NormalTreeIterator() : _node(nullptr) {}
		explicit NormalTreeIterator(node_type* node) : _node(node) {}
		NormalTreeIterator(const iterator& iter) : _node(iter._node) {}

		// operators

		reference operator*() const
		{
			return _node->value;
		}
		pointer operator->() const
		{
			return &_node->value;
		}

		this_type& operator++()
		{

		}
		this_type operator++(int)
		{

		}
		this_type& operator--()
		{

		}
		this_type operator--(int)
		{

		}

	};

	template <typename T>
	class BaseNormalTree
	{
	public:
		typedef BaseNormalTree<T>		this_type;
		typedef NormalTreeNode<T>		node_type;
		typedef BaseNormalTreeNode		base_node_type;
		typedef node_type*				node_pointer;

		/*typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;*/
		typedef size_t					size_type;

		node_pointer alloc_node(node_pointer parent = nullptr)
		{
			return new node_type(parent);
		}

		void dealloc_node(node_pointer node)
		{
			if (node)
				delete node;
		}

		void dealloc()
		{
			// 清楚所有节点
			node_pointer pNode = &_node;

		}

		node_pointer root()
		{
			return node_pointer(_node._parent);
		}

	protected:
		size_type	   _size;
		base_node_type _node;
	};


	// 默认升序排列
	template <typename T, typename Compare = less<T>>
	class normaltree : public BaseNormalTree<T>
	{
	public:
		typedef normaltree<T>			this_type;
		typedef BaseNormalTree<T>		base_type;
	
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;
		typedef NormalTreeIterator<T, T*, T&>			  iterator;
		typedef NormalTreeIterator<T, const T*, const T&> const_iterator;

		using base_type::_node;
		using base_type::_size;
		using typename base_type::node_type;
		using typename base_type::node_pointer;
		using typename base_type::base_node_type;

		normaltree()
		{
			reset();
		};

		iterator begin()
		{
			return iterator(node_pointer(_node._lchild));
		}
		iterator end()
		{
			return _node;
		}

		iterator insert(const value_type v)
		{
			return insert(const_iterator(root()), v);
		}

		iterator insert(const const_iterator position, const value_type& v)
		{
			Compare compare;
			bool right = true;
			node_pointer pos = position._node;
			++_size;
			node_pointer pNode = alloc_node(pos);
			pNode->_value = v;

			if (pos == &_node) // 空树
			{
				node._parent = node._lchild = pNode;
				node_pointer(pNode)->_value = v;
				return iterator(node_pointer(pNode));
			}
			while (1) // 寻找插入位置
			{
				if (compare(pos->_value, v))
				{
					// *position < v
					// 插入右节点
					if (pos->_rchild)// 存在右节点
						pos = node_pointer(pos->_rchild);
					else
					{
						right = true;
						break;
					}
				}
				else
				{
					if (pos->_lchild)
						pos = node_pointer(pos->_lchild);
					else
					{
						right = false;
						break;
					}
				}
			}
			
			if (right) // 在当前节点插入右节点
				pos->_rchild = pNode;
			else // 插入左节点
				pos->_lchild = pNode;
			if (pos == _node._lchild && !right)
				_node._lchild = pNode; // 更新 begin()
			return iterator(pos);
		}

		
		void reset()
		{
			_node._parent = &_node;
			_node._lchild = &_node;
			_node._rchild = &_node;
			_size = 0;
		}
	};


}



#endif // !__NORMAL_TREE_H__

