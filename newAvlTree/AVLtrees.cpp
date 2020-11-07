#pragma once
#include <iostream>

using namespace std;


typedef enum { LH, EH, RH } balance;
bool Located = false;

template <class ItemType>
struct TreeNode {

	ItemType info;
	ItemType root;
	balance bf;
	TreeNode* left;
	TreeNode* right;
};


template <class ItemType>
class AVLtree
{
public:
	AVLtree();
	~AVLtree();
	void InsertItem(ItemType item);
	void PrintTree();
	void SearchItem(ItemType item);
	void DeleteItem(ItemType item);


	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller);
	void Print(TreeNode<ItemType>*& tree);
	void RightBalance(TreeNode<ItemType>*& tree, bool& taller);
	void LeftBalance(TreeNode<ItemType>*& tree, bool& taller);
	void Search(TreeNode<ItemType>*& tree, ItemType item);
	void Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter);
	void DeleteNode(TreeNode<ItemType>*& tree, bool& shorter);
	//void RotateRight(TreeNode<ItemType>*& tree;
	//void RotateLeft(TreeNode<ItemType>*& tree);
private:

	TreeNode<ItemType>* root;
};

//constructor
template <class ItemType>
AVLtree<ItemType>::AVLtree() {
	root = NULL;
}

//destructor
template <class ItemType>
AVLtree<ItemType>::~AVLtree() {

}

template<class ItemType>
void AVLtree<ItemType>::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller;
	Insert(root, item, taller);
}


template<class ItemType>
void AVLtree<ItemType>::Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller)
// Inserts item into tree.
// Post: item is in tree; search property is maintained
{
	if (tree == NULL)
	{	// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = EH;
		taller = true;
	}
	else if (item == tree->info)
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	else if (item < tree->info)
	{
		Insert(tree->left, item, taller);
		// Insert into left subtree if (taller)	switch (tree->bf)
		{
			switch (tree->bf)
			{
			case LH: LeftBalance(tree, taller);	break;
			case EH: tree->bf = LH;	break;
			case RH: tree->bf = EH;	taller = false; break;
			}

		}
	}

	else {
		Insert(tree->right, item, taller);
		// Insert into right subtree if (taller)
		switch (tree->bf)
		{
		case RH: RightBalance(tree, taller); break;
		case EH: tree->bf = RH; break;
		case LH: tree->bf = EH; taller = false; break;
		}
	}
}

template<class ItemType>
void AVLtree<ItemType>::PrintTree()
{
	Print(root);
}

template<class ItemType>
void AVLtree<ItemType>::SearchItem(ItemType item)
{
	Search(root, item);
}

template<class ItemType>
void AVLtree<ItemType>::Search(TreeNode<ItemType>*& tree, ItemType item)
{

	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Search(tree->left, item);

		}
		else if (item > tree->info)
		{
			Search(tree->right, item);
		}
		else
		{
			Located = true;
			cout << "\n\nName found in tree" << endl;
		}
	}
	else
	{
		cout << "\n\nName not found in Avl Tree" << endl;
	}
}

template<class ItemType>
void AVLtree<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.

{
	bool shorter;
	Delete(root, item, shorter);
	Located = false;

}

template <class ItemType>
void AVLtree<ItemType>::Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->left, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH:
					tree->bf = EH;
					break;
				case EH:
					tree->bf = RH;
					shorter = false;
					break;
				case RH:
					DelRightBalance(tree, shorter);
					break;
				} // END SWITCH
		}
		else if (item > tree->info)
		{
			Delete(tree->right, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH:
					DelLeftBalance(tree, shorter);
					break;
				case EH:
					tree->bf = LH;
					shorter = false;
					break;
				case RH:
					tree->bf = EH;
					break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);

		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.";
	}
	//cout << "Item Deleted" << endl;

}

template <class ItemType>
void AVLtree<ItemType>::DeleteNode(TreeNode <ItemType>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	ItemType data;
	TreeNode <ItemType>* tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->left, data, shorter);
		// Delete the predecessor node
		if (shorter)
		{
			switch (tree->bf)
			{
			case LH:
				tree->bf = EH;
				break;
			case EH:
				tree->bf = RH;
				shorter = false;
				break;
			case RH:
				DelRightBalance(tree, shorter);
				break;
			}
		}
	}
}

template <class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
		tree = tree->right;
	data = tree->info;
}

template <class ItemType>
void DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;
	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		shorter = true; break;
	case EH:	tree->bf = RH;
		rs->bf = LH;
		RotateLeft(tree);
		shorter = false; break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH; break;
		case EH:	tree->bf = rs->bf = EH;
			break;
		case LH:	tree->bf = EH;
			rs->bf = RH; break;
		} // END SWITCH

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class ItemType>
void DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;
	switch (ls->bf)
	{
	case LH:
		tree->bf = ls->bf = EH;
		RotateRight(tree);
		shorter = true; break;
	case EH:
		tree->bf = LH;
		ls->bf = RH;
		RotateRight(tree);
		shorter = false; break;
	case RH:
		rs = ls->right;
		switch (rs->bf)
		{
		case LH:	tree->bf = RH;
			ls->bf = EH; break;
		case EH:	tree->bf = ls->bf = EH;
			break;
		case RH:	tree->bf = EH;
			ls->bf = LH; break;
		} // END SWITCH
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		ls->bf = EH;
		shorter = true;
	}
}

template<class ItemType>
void AVLtree<ItemType>::Print(TreeNode<ItemType>*& tree)
{
	string bf, left, right;
	//If tree is empty print empty tree
	if (tree == NULL)
		//cout << "  AVL tree is empty.\n  Please enter names to fill AVL Tree\n\n" << endl;
		return;
	else
	{

		Print(tree->left);

		if (tree != NULL)
		{
			cout << "\n\t " << tree->info << ":";
		}


		if (tree->left == NULL)
		{
			left = "NULL";
			cout << "\tLeft: " << left << "";
		}
		else
			cout << "\tLeft: " << tree->left->info << " ";

		if (tree->right == NULL)
		{
			right = "NULL";
			cout << "\tRight: " << right << "";
		}
		else
			cout << "\tRight: " << tree->right->info << "  ";

		switch (tree->bf)
		{
		case 0: bf = "Left High "; break;
		case 1: bf = "Equal High "; break;
		case 2: bf = "Right High "; break;
		}
		cout << "\tBalance Factor: " << bf << "" << endl;

		Print(tree->right);
	}

}

template<class ItemType>
void AVLtree<ItemType>::RightBalance(TreeNode<ItemType>*& tree, bool& taller) {
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;

	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;

	case EH:
		cerr << "Tree already balanced " << endl;
		break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH;
			break;
		case EH:	tree->bf = rs->bf = EH;
			break;
		case LH:	tree->bf = EH;
			rs->bf = RH;
			break;
		}

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

template<class ItemType>
void AVLtree<ItemType>::LeftBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;

	switch (ls->bf)
	{
	case LH:
		tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;

	case EH:
		cerr << "Tree already balanced " << endl;
		break;
	case RH:
		rs = ls->right;
		switch (rs->bf)
		{
		case LH:
			tree->bf = RH;
			ls->bf = EH;
			break;
		case EH:
			tree->bf = ls->bf = EH;
			break;
		case RH:
			tree->bf = EH;
			ls->bf = LH;
			break;
		}

		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

template<class ItemType>
void RotateRight(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* ls;
	if (tree == NULL)
		cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
	else if (tree->left == NULL)
		cerr << "It is impossible to make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}

template<class ItemType>
void RotateLeft(TreeNode<ItemType>*& tree)
{
	TreeNode<ItemType>* rs;
	if (tree == NULL)
		cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
	else if (tree->right == NULL)
		cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}
