#pragma once

#ifndef __NORMAL_TREE_H__
#define __NORMAL_TREE_H__

#include <functional.h>

namespace sp
{
	// 先来试试写，非平衡二叉树

	// tree_node_base
	struct BaseNormalTreeNode
	{
		BaseNormalTreeNode *parent, *lchild, *rchild;
		BaseNormalTreeNode() : parent(nullptr), lchild(nullptr), rchild(nullptr) {}

	};

	template <typename T>
	struct NormalTreeNode : public BaseNormalTreeNode
	{
		T value;
	};

	template <typename T>
	class BaseNormalTree
	{
		typedef BaseNormalTree<T>		this_type;
		typedef NormalTreeNode<T>		node_type;
		typedef BaseNormalTreeNode		base_node_type;

		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;



		// _node is the root of the tree
		// and it dont's have value.
		base_node_type _node;
	};


	// 默认升序排列
	template <typename T, typename Compare = less<T>>
	class normaltree : BaseNormalTree<T>
	{
		typedef normaltree<T>			this_type;
		typedef BaseNormalTree<T>		base_type;
	
		typedef T						value_type;
		typedef T*						pointer;
		typedef const T*				const_pointer;
		typedef T&						reference;


	};


}



#endif // !__NORMAL_TREE_H__

