#include "btNode.h"

void bst_insert (btNode*& bst_root, int insInt)
{
   btNode* newNode = new btNode;
   newNode->data = insInt;
   newNode->left = 0;
   newNode->right = 0;
   
   if (bst_root == 0)
   {
   	  //Tree is empty, root becomes insInt
	  bst_root = newNode;
      return;
   }
   //allocate a memory to hold current root
   btNode* cursor = bst_root;
   
   //Check whether to insert LST or RST
   while (cursor != 0)
   {
   	  if (insInt < cursor->data)
   	  {
   	  	 //insert new node LST
   	     if (cursor->left == 0)
		 {
		    cursor->left = newNode;
			return;	
		 }
		 cursor = cursor->left; //keep searching left	
	  }
	  else if (insInt > cursor->data)
	  {
	     if (cursor->right == 0)
		 {
		    //insert new node RST
			cursor->right = newNode;
			return;	
		 }
		 cursor= cursor->right;	//keep searching right
	  }
	  else
	  {
	     //insInt is already in the tree
		 //no need to create a new node
		 delete newNode;
		 return;	
	  }
   }
}

bool bst_remove(btNode*& bst_root, int remInt) 
{
   // Check if tree is empty
   if (bst_root == 0)
      return false;
    
   // If the value to remove is less than the root, recurse left
   if (remInt < bst_root->data)
   {
      return bst_remove(bst_root->left, remInt);
   }
   // If the value to remove is greater than the root, recurse right
   else if (remInt > bst_root->data) 
   {
      return bst_remove(bst_root->right, remInt);
   }
   // If the value to remove is equal to the root
   else 
   {
      // Case 1: Root has no children or only 1 child
      if (!bst_root->left)
	  {
         btNode* temp = bst_root->right;
         delete bst_root;
         bst_root = temp;
         return true;
      }
      else if (!bst_root->right)
	  {
         btNode* temp = bst_root->left;
         delete bst_root;
         bst_root = temp;
         return true;
      }
      // Case 2: Root has two children
      else
	  {
         // Find the maximum value in the left subtree
         // Set the root's value to the max value found
         bst_remove_max(bst_root->left, bst_root->data);
         return true;
      }
    }
}

bool bst_remove_max(btNode*& bst_root, int& data)
{
   //If tree is empty, return
   if (bst_root == 0) return false;
   
   if (bst_root->right == 0)
   {
      // largest item found at root
      data = bst_root->data;
      btNode* temp = bst_root;
      bst_root = bst_root->left;
      delete temp;
      return true;
   }
   else
   {
      // continue search in right subtree
      return bst_remove_max(bst_root->right, data);
   }
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
