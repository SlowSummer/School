#include "btNode.h"

void bst_insert(btNode*& bst_root, int insInt)
{
	if (bst_root == 0) // check if root is null
	{
		bst_root = new btNode;
		bst_root->data = insInt;
		bst_root->left = 0;
		bst_root->right = 0;

		return;
	}
	
	btNode* temp = bst_root;

	while (temp != 0)
	{
		if (temp->data == insInt) // insInt match
		{
			return;
		}

		if (temp->data < insInt) // insInt goes on right branch
		{
			if (temp->right == 0) // vacant branch on right
			{
				temp->right = new btNode;
				temp->right->data = insInt;
				temp->right->left = 0;
				temp->right->right = 0;
			}
			else
			{
				temp = temp->right;
			}

			continue; 
		}

		// insInt goes on left branch
		if (temp->left == 0) //vacant branch on left
		{
			temp->left = new btNode;
			temp->left->data = insInt;
			temp->left->left = 0;
			temp->left->right = 0;
		}
		else
		{
			temp = temp->left;
		}
	}
}

bool bst_remove(btNode*& bst_root, int delInt)
{
	if (bst_root == 0) // check if tree is empty
	{
		return false;
	}

	if (bst_root->data > delInt) // recur left
	{
		return bst_remove(bst_root->left, delInt);
	}

	if (bst_root->data < delInt) //recur right
	{
		return bst_remove(bst_root->right, delInt);
	}

	if (bst_root->data == delInt)
	{
		btNode* old_bst_root = bst_root;

		if (bst_root->left != 0 && bst_root != 0) // two children
		{
			bst_remove_max(bst_root->left, bst_root->data);
			return true;
		}

		if (bst_root->left == 0 && bst_root->right != 0) // no left child
		{
			bst_root = bst_root->right;
			delete old_bst_root;
		}
		else if (bst_root->left != 0 && bst_root->right == 0) // no right child
		{
			bst_root = bst_root->left;
			delete old_bst_root;
		}
		else // no children
		{
			bst_root = 0;
		}

		return true;
	}
}

void bst_remove_max(btNode*& bst_root, int& data)
{
	if (bst_root == 0) // check if tree is empty
	{
		return;
	}

	if (bst_root->right == 0) // check if root has right child
	{
		data = bst_root->data;

		btNode* temp = bst_root;
		bst_root = bst_root->left;
		delete temp;

		return;
	}

	bst_remove_max(bst_root->right, data);
}


void portToArrayInOrder(btNode* bst_root, int* portArray)
{
   if (bst_root == 0) return;
   int portIndex = 0;
   portToArrayInOrderAux(bst_root, portArray, portIndex);
}

void portToArrayInOrderAux(btNode* bst_root, int* portArray, int& portIndex)
{
   if (bst_root == 0) return;
   portToArrayInOrderAux(bst_root->left, portArray, portIndex);
   portArray[portIndex++] = bst_root->data;
   portToArrayInOrderAux(bst_root->right, portArray, portIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}
