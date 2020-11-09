#pragma once
#include <string>
#include "AvlMethods.h"

template <class T>class AvlTree
{
public:
	AvlTree();
	~AvlTree();
public:
	void Clear();
	bool Contains(T candidate);
	void Insert(T value);
	AvlTreeNode<T>* Nodes();
	bool Remove(T value);
	string ToString();
private:
	AvlTreeNode<T>* root;
};

//
//	constructor/desturtor
//
template<class T> AvlTree<T>::AvlTree()
{
	root = NULL;
}
template<class T> AvlTree<T>::~AvlTree() { }
#pragma region Public Methods
#pragma endregion
template<class T> void AvlTree<T>::Clear()
{
	root = NULL;//Lazy way, memoery not recoved
}
template<class T> bool AvlTree<T>::Contains(T candidate)
{
	return ContainsValue<T>(root, candidate);
}
template<class T> void AvlTree<T>::Insert(T value)
{
	root = InsertValue<T>(root, value);
}
template<class T> AvlTreeNode<T>* AvlTree<T>::Nodes()
{
	return root; // should be a deep copy of Nodes
}
template<class T> bool AvlTree<T>::Remove(T value)
{
	bool present = Contains(value);
	if (present)
		root = DeleteNodeByValue<T>(root, value);
	return present;
}
template<class T> string AvlTree<T>::ToString()
{
	return ToInOrderString<T>(root);
}
