#include "BinarySearchTree.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

void InOrder(BinarySearchTree::Node* temp);

BinarySearchTree::Node::Node(DataType newval)
{
	val = newval;
	left = NULL;
  	right = NULL;
}

// Implement the functions here.
// Default constructor.
BinarySearchTree::BinarySearchTree()
{
	root_ = NULL;
	size_ = 0;
}

// Destructor.
BinarySearchTree::~BinarySearchTree()
{
	if (root_ == NULL)
		return;
	
	while (root_ != NULL)
		remove(root_->val);
}
  
// Inserts value "val" into the tree. Returns false if failed (i.e., "val"
// already exists in the tree), and true otherwise.
bool BinarySearchTree::insert(DataType val)
{
	if (size_ == 0)
	{
		root_ = new Node(val);
		size_++;
		return true;
	}

  	Node *temp = root_, *parent = NULL;
	
	while (temp != NULL)
	{
		if (temp->val == val)
			return false;
		
		parent = temp;

		if (val > temp->val)
			temp = temp->right;
		
		else if (val < temp->val)
			temp = temp->left;
	}
	
	temp = new Node(val);
	size_++;

	if (val > parent->val)
		parent->right = temp;
	else
		parent->left = temp;

	return true;
}

// Removes the node with value "val" from the tree. Returns true if successful,
// false otherwise.
bool BinarySearchTree::remove(DataType val)
{
	if (!exists(val))
		return false;
	
	if (size_ == 1)
	{
		delete root_;
		root_ = NULL;
		size_--;
		return true;
	}
	
	if (val == root_->val)
	{
		if (root_->left == NULL && root_->right != NULL)
		{
			Node* temp = root_->right;
			
			delete root_;
			root_ = NULL;
			size_--;
			
			root_ = temp;
			return true;
		}
		
		else if (root_->right == NULL && root_->left != NULL)
		{
			Node* temp = root_->left;
			
			delete root_;
			root_ = NULL;
			size_--;
			
			root_ = temp;
			return true;
		}
		
		else
		{
			Node* curr = root_->right, *parent = root_;
			
			while (curr->left != NULL)
			{
				if (curr->left != NULL)
					parent = curr;
				curr = curr->left;
			}

			DataType swap = root_->val;
			root_->val = curr->val;
			curr->val = swap;

			if (curr->right == NULL)
			{
				if (parent->left->val == val)
				{
					delete parent->left;
					parent->left = NULL;
				}
				else
				{
					delete parent->right;
					parent->right = NULL;
				}

				curr = NULL;
				size_--;
		
				return true;
			}
			else if (parent == root_)
			{
				parent->right = curr->right;

				delete curr;
				curr = NULL;
				size_--;

				return true;
			}
			else
			{
				parent->left = curr->right;

				delete curr;
				curr = NULL;
				size_--;
			
				return true;
			}
		}
	}
	
  	Node *temp = root_, *parent = NULL;
  	
  	while (temp != NULL)
  	{		
  		if (val > temp->val)
  		{
  			if (temp->right->val == val)
  				parent = temp;
		  	temp = temp->right;
		}
  		
  		else if (val < temp->val)
  		{
  			if (temp->left->val == val)
  				parent = temp;
  			temp = temp->left;
  		}
  		
  		if (val == temp->val)
  			break;
	}
	
	if (temp->left == NULL && temp->right == NULL)
	{
		if (parent->left->val == val)
		{
			delete parent->left;
			parent->left = NULL;
		}
		else
		{
			delete parent->right;
			parent->right = NULL;
		}

		temp = NULL;
		size_--;
		
		return true;
	}
	
	else if (temp->left != NULL && temp->right != NULL)
	{
		Node *curr = temp->right, *parent = temp;
		
		while (curr->left != NULL)
		{
			if (curr->left != NULL)
				parent = curr;
			curr = curr->left;
		}

		DataType swap = temp->val;
		temp->val = curr->val;
		curr->val = swap;
		
		if (curr->right == NULL)
		{
			if (parent->left->val == val)
			{
				delete parent->left;
				parent->left = NULL;
			}
			else
			{
				delete parent->right;
				parent->right = NULL;
			}

			curr = NULL;
			size_--;
		
			return true;
		}
		else if (parent == temp)
		{
			parent->right = curr->right;

			delete curr;
			curr = NULL;
			size_--;

			return true;
		}
		else
		{
			parent->left = curr->right;

			delete curr;
			curr = NULL;
			size_--;
		
			return true;
		}
	}
	
	else
	{
		Node* child = NULL;
		if (temp->left != NULL)
			child = temp->left;
		else
			child = temp->right;
			
		if (parent->left->val == val)
			parent->left = child;
		else
			parent->right = child;
		
		delete temp;
		temp = NULL;
		size_--;
		
		return true;
	}
}
  
// Returns true if a node with value "val" exists in the tree; false otherwise.
bool BinarySearchTree::exists(DataType val) const
{
  	Node* temp = root_;
  	
  	while (temp != NULL)
  	{
  		if (temp->val == val)
  			return true;
  			
  		if (val > temp->val)
  			temp = temp->right;
  		
  		else if (val < temp->val)
  			temp = temp->left;
	}
	
	return false;
}

// Returns the minimum value of the tree. You can assume that this function
// will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::min() const
{
  	Node* temp = root_;
  	
  	while (temp->left != NULL)
  		temp = temp->left;
  	
  	return temp->val;
}
  
// Returns the maximum value of the tree. You can assume that this function
// will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::max() const
{
  	Node* temp = root_;
  	
  	while (temp->right != NULL)
  		temp = temp->right;
  	
  	return temp->val;
}
  
// Returns the number of nodes in the tree.
unsigned int BinarySearchTree::size() const
{
	return size_;
}
  
// Returns the maximum depth of the tree. A tree with only the root node has a
// depth of 0. You can assume that this function will never be called on an 
// empty tree.
unsigned int BinarySearchTree::depth() const
{
  	if (size_ == 1)
  		return 0;
  		
	return getNodeDepth(root_)-1;
}
  
// You can print the tree in which ever manner you like, however methods such
// as in-order, level-order, etc. might be the most useful for debugging
// purposes.
void BinarySearchTree::print() const
{
	if (root_ == NULL)
		return;

	InOrder(root_);
	return;
}

void InOrder(BinarySearchTree::Node* temp)
{
	if (temp == NULL)
		return;

	InOrder(temp->left);
	cout << temp->val << " ";
	InOrder(temp->right);

	return;
}

// Optional function
// Recursively get the maximum depth from a given node. Call on root_ first.
// This might be of great value to you in depth().
int BinarySearchTree::getNodeDepth(Node* n) const
{
	if (n == NULL)
  		return 0;

	int leftChild = getNodeDepth(n->left);
	int rightChild = getNodeDepth(n->right);

	if (leftChild <= rightChild)
		return rightChild+1;

	else
		return leftChild+1;
}
