#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
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

// write definition for bst_insert here
//four cases: BST empty, insInt belongs on left, InsInt belongs on right, or insInt alreadyin set
void bst_insert(btNode*& bst_root, int insInt) {
	
	//check if root empty, if so insert node w/ null pointers
	if (bst_root == 0) {
		btNode* new_root = new btNode;
		new_root->data = insInt;
		new_root->left = 0;
		new_root->right = 0;
		bst_root = new_root;
		return;
	}

	// cursor traverses tree
	btNode* cursor = bst_root;

	//prevent nullptr
	while (cursor != 0) {

		//checks if root data greater
		if (cursor->data > insInt) {
			
			//if so, add node if LST empty or traverse
			if (cursor->left == 0) {
				cursor->left = new btNode;
				cursor->left->data = insInt;
				cursor->left->left = 0;
				cursor->left->right = 0;
				return;
			}
			else {
				cursor = cursor->left;
			}
		}
		//if so, add node if RST empty or traverse
		else if (cursor->data < insInt) {
			if (cursor->right == 0) {
				cursor->right = new btNode;
				cursor->right->data = insInt;
				cursor->right->left = 0;
				cursor->right->right = 0;
				return;
			}
			else {
				cursor = cursor->right;
			}
		}
		else {
			//insInt already present in BST, do nothing
			return;
		}
	}

}

// write definition for bst_remove here
//Cases: tree empty, int not found, return false, else traverse. If found: for two children,
//reorganize w bst_remove_max; for one child, child is now root, int removed, return true
bool bst_remove(btNode*& bst_root, int remInt) {

	/// if tree is empty, nothing to remove. return false
	if (bst_root == 0) { 
		return false; 
	}

	if(remInt < bst_root->data){
		//remInt less than current node, recur to LST
		bst_remove(bst_root->left, remInt);

	}
	else if (remInt > bst_root->data) {
		// remInt greater than current node, recur to RST
		bst_remove(bst_root->right, remInt);

	}
	else {
		//remInt found

		//if current root has two child nodes, use bst_remove_max to adjust subtree
		if (bst_root->left != 0 && bst_root->right != 0) {

			bst_remove_max(bst_root->left, bst_root->data);



		}
		//only one child node present, remove current root and replace with next available
		else {

			//ptr to delete node once removed from tree
			btNode* delRoot = bst_root;

			//node found on right becomes new root
			if (bst_root->left == 0 && bst_root->right != 0) {
				bst_root = bst_root->right;
			}
			//noe found on left becomes new root
			else if (bst_root->left != 0 && bst_root->right == 0) {
				bst_root = bst_root->left;
			}
			else {
				// int removed
				bst_root = 0;
			}

			// clear up node with remInt
			delete delRoot;
		}
		return true;
	}
}


// write definition for bst_remove_max here
//Cases: tree empty, no max; current node is max, set remove and delete; not largest node, traverse
void bst_remove_max(btNode*& bst_root, int& remove) {
	/// Tree is empty, nothing to do
	if (bst_root == 0) {
		return; 
	}
	//if largest number, remove is set to its data
	if (bst_root->right == 0) {

		btNode* delNode = bst_root;
		remove = bst_root->data;

		//if left has node it will be new root, otherwise null
		bst_root = bst_root->left;

		//remove max node
		delete delNode;
	}
	//else if not largest number
	else {
		// continue traverse searching for remove
		bst_remove_max(bst_root->right, remove);
	}
}


