///
/// Code adapted from geeksforgeeks * @see
/// <a href="https://www.geeksforgeeks.org/avl-tree-set-1-insertion/">geeksforgeeks</a>
/// <a href="https://www.geeksforgeeks.org/avl-tree-set-2-deletion/">geeksforgeeks</a>
/// 
#pragma once
#include "AvlBalanceFactor.h"

template<class T> struct AvlTreeNode
{
public:
	AvlTreeNode();
	AvlTreeNode(int, T);
	AvlTreeNode(T);
#pragma region Methods : get const
#pragma endregion
	int getBalanceFactor() const;
	int getHeight() const;
	AvlTreeNode<T>* getLeftTree() const;
	AvlTreeNode<T>* getRightTree() const;
	T getValue() const;
	bool IsComplete() const;
	bool IsNotComplete() const;
	bool Isleaf() const;
#pragma region Methods : set
#pragma endregion
	void setHeight(int value);
	void setLeftTree(AvlTreeNode<T>*);
	void setRightTree(AvlTreeNode<T>*);
	void setValue(T);
	void updateHeight();
#pragma region Properties
#pragma endregion
	__declspec(property(get = getBalanceFactor))  int BalanceFactor;
	__declspec(property(get = getLeftTree, put = setLeftTree)) AvlTreeNode<T>* LeftTree;
	__declspec(property(get = getRightTree, put = setRightTree)) AvlTreeNode<T>* RightTree;
	__declspec(property(get = getValue, put = setValue)) T Value;
#pragma region Fields
#pragma endregion
private:
	int height;
	AvlTreeNode<T>* leftTree;
	AvlTreeNode<T>* rightTree;
	T value;
};

template<class T> AvlTreeNode<T>::AvlTreeNode()
{
	this->height = 1;
	this->leftTree = this->rightTree = NULL;
}
template<class T> AvlTreeNode<T>::AvlTreeNode(T value)
{
	this->height = 1;
	this->leftTree = this->rightTree = NULL;
	this->value = value;
}
template<class T> AvlTreeNode<T>::AvlTreeNode(int height, T value)
{
	this->height = height;
	this->leftTree = this->rightTree = NULL;
	this->value = value;
}
#pragma region Methods : get const
#pragma endregion
template<class T> int AvlTreeNode<T>::getBalanceFactor() const
{
	int heightDifference = calculateHeight(this->leftTree) - calculateHeight(this->rightTree);
	return heightDifference;
}

template<class T> int AvlTreeNode<T>::getHeight() const
{
	return this->height;
}
template<class T> AvlTreeNode<T>* AvlTreeNode<T>::getLeftTree() const
{
	return this->leftTree;
}
template<class T> AvlTreeNode<T>* AvlTreeNode<T>::getRightTree() const
{
	return this->rightTree;
}
template<class T> T AvlTreeNode<T>::getValue() const
{
	return this->value;
}
template<class T> bool AvlTreeNode<T>::IsComplete() const
{
	return this->leftTree != NULL && this->rightTree != NULL;
}
template<class T> bool AvlTreeNode<T>::IsNotComplete() const
{
	return this->leftTree == NULL || this->rightTree == NULL;
}
template<class T> bool AvlTreeNode<T>::Isleaf() const
{
	return this->leftTree == NULL && this->rightTree == NULL;
}
#pragma region Methods : set
#pragma endregion
template<class T> void AvlTreeNode<T>::setHeight(int value)
{
	this->height = value;
}
template<class T> void AvlTreeNode<T>::setLeftTree(AvlTreeNode<T>* value)
{
	this->leftTree = value;
}
template<class T> void AvlTreeNode<T>::setRightTree(AvlTreeNode<T>* value)
{
	this->rightTree = value;
}
template<class T> void AvlTreeNode<T>::setValue(T value)
{
	this->value = value;
}
int getLargest(int lhs, int rhs)
{
	return (lhs > rhs) ? lhs : rhs;
}
template<class T>int calculateHeight(AvlTreeNode<T>* avlTreeNode)
{
	return avlTreeNode == NULL ? 0 : avlTreeNode->getHeight();
}
template<class T> void AvlTreeNode<T>::updateHeight()
{
	int leftTreeHeight = calculateHeight(this->leftTree);
	int rightTreeHeight = calculateHeight(this->rightTree);
	this->height = 1 + getLargest(leftTreeHeight, rightTreeHeight);
}

