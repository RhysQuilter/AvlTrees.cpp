///
/// Code adapted from geeksforgeeks * @see
/// <a href="https://www.geeksforgeeks.org/avl-tree-set-1-insertion/">geeksforgeeks</a>
/// <a href="https://www.geeksforgeeks.org/avl-tree-set-2-deletion/">geeksforgeeks</a>
/// 
#pragma once
#include <sstream>
#include <string>
#include "AvlTreeNode.h"
using namespace std;

template<class T>AvlTreeNode<T>* BalanceTreeAfterDeletion(AvlTreeNode<T>*&);
template<class T>AvlTreeNode<T>* BalanceTreeAfterInsert(AvlTreeNode<T>*&, T&);
template<class T>bool ContainsValue(AvlTreeNode<T>*, T);
template<class T>AvlTreeNode<T>* DeleteNodeByValue(AvlTreeNode<T>*, T);
template<class T>AvlTreeNode<T>* GetLeftmostNode(AvlTreeNode<T>*);
template<class T>AvlTreeNode<T>* InsertValue(AvlTreeNode<T>*, T);
template<class T>AvlTreeNode<T>* RotateRight(AvlTreeNode<T>*);
template<class T>AvlTreeNode<T>* RotateLeft(AvlTreeNode<T>*);
template<class T>string ToInOrderString(AvlTreeNode<T>* tree);
template<class T>string ToPreOrderString(AvlTreeNode<T>* tree);
template<class T>string ToString(AvlTreeNode<T>* tree);
template<class T>string TtoString(T const& t);

template<class T>AvlTreeNode<T>* BalanceTreeAfterDeletion(AvlTreeNode<T>*& tree)
{
	tree->updateHeight();
	int balanceFactor = tree->getBalanceFactor();

	if (balanceFactor > AvlBalanceFactor::LeftUnbalanced)
	{
		int leftBalanceFactor = tree->LeftTree->BalanceFactor;
		if (leftBalanceFactor >= AvlBalanceFactor::Balanced)
			return RotateRight(tree);
		else if (leftBalanceFactor < AvlBalanceFactor::Balanced)
		{
			tree->LeftTree = RotateLeft(tree->LeftTree);
			return RotateRight(tree);
		}
	}
	else if (balanceFactor < AvlBalanceFactor::RightUnbalanced)
	{
		int rightBalanceFactor = tree->RightTree->BalanceFactor;
		if (rightBalanceFactor <= AvlBalanceFactor::Balanced)
			return RotateLeft(tree);
		else if (rightBalanceFactor > AvlBalanceFactor::Balanced)
		{
			tree->RightTree = RotateRight(tree->RightTree);
			return RotateLeft(tree);
		}
	}
	return tree;
}
template<class T>AvlTreeNode<T>* BalanceTreeAfterInsert(AvlTreeNode<T>*& tree, T& value)
{
	tree->updateHeight();
	int balanceFactor = tree->getBalanceFactor();

	if (balanceFactor > AvlBalanceFactor::LeftUnbalanced)
	{
		if (value < tree->getLeftTree()->getValue())
			return RotateRight(tree);
		else if (value > tree->getLeftTree()->getValue())
		{
			tree->setLeftTree(RotateLeft(tree->getLeftTree()));
			return RotateRight(tree);
		}
		else return tree;
	}
	else if (balanceFactor < AvlBalanceFactor::RightUnbalanced)
	{
		if (value > tree->getRightTree()->getValue())
			return RotateLeft(tree);
		else if (value < tree->getRightTree()->getValue())
		{
			tree->setRightTree(RotateRight(tree->getRightTree()));
			return RotateLeft(tree);
		}
		else
		{
			return tree;
		}
	}
	else
	{
		return tree;
	}
}
template<class T>bool ContainsValue(AvlTreeNode<T>* tree, T value)
{
	if (tree == NULL)
		return false;
	else if (value < tree->Value)
		return ContainsValue(tree->LeftTree, value);
	else if (value > tree->Value)
		return ContainsValue(tree->RightTree, value);
	else
		return value == tree->Value;
}
template<class T>AvlTreeNode<T>* DeleteNodeByValue(AvlTreeNode<T>* tree, T value)
{
	if (tree == NULL)
		return tree;
	else
	{
		if (value < tree->Value)
			tree->LeftTree = DeleteNodeByValue(tree->LeftTree, value);
		else if (value > tree->Value)
			tree->RightTree = DeleteNodeByValue(tree->RightTree, value);
		else //if (value == root->Value)
		{
			if ((tree->IsNotComplete()))
			{
				AvlTreeNode<T>* nodeToDelete = tree->LeftTree ? tree->LeftTree : tree->RightTree;

				if (nodeToDelete == NULL)
				{
					nodeToDelete = tree;
					tree = NULL;
					//return root;
				}
				else
				{
					*tree = *nodeToDelete; // Copy the contents of the non-empty child
				}
				delete nodeToDelete;
			}
			else
			{
				AvlTreeNode<T>* leftmostNode = GetLeftmostNode(tree->RightTree);
				tree->Value = leftmostNode->Value;
				tree->RightTree = DeleteNodeByValue(tree->RightTree, leftmostNode->Value);
			}
		}

		// If the tree had only one node then return
		if (tree == NULL)
			return tree;

		return BalanceTreeAfterDeletion(tree);
	}
}
template<class T>AvlTreeNode<T>* GetLeftmostNode(AvlTreeNode<T>* tree)
{
	AvlTreeNode<T>* iterator = tree;
	for (; iterator->LeftTree != NULL; iterator = iterator->LeftTree)
	{
	}
	return iterator;
}
template<class T>AvlTreeNode<T>* InsertValue(AvlTreeNode<T>* tree, T value)
{
	if (tree == NULL)
		return new AvlTreeNode<T>(value);
	else
	{
		if (value < tree->Value)
			tree->LeftTree = InsertValue(tree->LeftTree, value);
		else if (value > tree->Value)
			tree->RightTree = InsertValue(tree->RightTree, value);
		else // Equal keys are not allowed in BST
			return tree;

		return BalanceTreeAfterInsert(tree, value);
	}
}
template<class T>AvlTreeNode<T>* RotateRight(AvlTreeNode<T>* root)
{
	AvlTreeNode<T>* newRoot = root->getLeftTree();
	AvlTreeNode<T>* rootNewLeft = newRoot->getRightTree();

	newRoot->setRightTree(root);
	root->setLeftTree(rootNewLeft);

	root->updateHeight();
	newRoot->updateHeight();

	return newRoot;
}
template<class T>AvlTreeNode<T>* RotateLeft(AvlTreeNode<T>* root)
{
	AvlTreeNode<T>* newRoot = root->getRightTree();
	AvlTreeNode<T>* rootNewRight = newRoot->getLeftTree();

	newRoot->setLeftTree(root);
	root->setRightTree(rootNewRight);

	root->updateHeight();
	newRoot->updateHeight();

	return newRoot;
}
template<class T>string ToInOrderString(AvlTreeNode<T>* tree)
{
	if (tree == NULL)
		return "";
	else
	{
		string text = ToInOrderString(tree->getLeftTree());
		text += ToString(tree);
		text += ToInOrderString(tree->getRightTree());
		return text;
	}
}
template<class T>string ToPreOrderString(AvlTreeNode<T>* tree)
{
	if (tree != NULL)
	{
		string text = TtoString(tree->Value) + " ";
		text += ToPreOrderString(tree->LeftTree);
		text += ToPreOrderString(tree->RightTree);
		return text;
	}
	else
		return "";
}
template<class T>string ToString(AvlTreeNode<T>* tree)
{
	string lhs = tree->LeftTree == NULL ? "NULL" : TtoString(tree->LeftTree->Value);
	string rhs = tree->RightTree == NULL ? "NULL" : TtoString(tree->RightTree->Value);
	string balanceFactor = AvlBalanceFactor::ToString(tree->getBalanceFactor());

	return "\n\t " + TtoString(tree->Value) + ":\tLeft: " + lhs + " \tRight: " + rhs + " \tBalance Factor: " + balanceFactor;
}
template<class T>string TtoString(T const& t)
{
	ostringstream myObjectStream;
	myObjectStream << t;
	return myObjectStream.str();
}