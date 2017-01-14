/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;


BinarySearchTree::BinarySearchTree()
{
        root = NULL;
}

BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
}

void BinarySearchTree::post_order_delete(Node *node)
{
	if (node == NULL) return;
	//post order-> left then right then middle
	post_order_delete(node->left);
	post_order_delete(node->right);
	delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
        if (this != &source) { //self-assignment
		post_order_delete(root);
		root = pre_order_copy(source.root);
	}
	
	return *this;
}

Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        if (node == NULL)
                return NULL;
        Node *new_node = new Node();
	//copy all data
	new_node->data = node->data;
	new_node->count = node->count;
	//recursive calls
	new_node->left = pre_order_copy(node->left);
	new_node->right = pre_order_copy(node->right);
	return new_node;
}

int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

//finds pointer of node with minimum value
Node *BinarySearchTree::find_min(Node *node) const
{
	//always leftmost path
       if (node->left == NULL)
	       return node;
       return find_min(node->left);
}

int BinarySearchTree::find_max() const
{
        if (root == NULL)
		return INT_MAX;
	return find_max(root)->data;
}

//finds pointer of node with maximum value
Node *BinarySearchTree::find_max(Node *node) const
{
	//always rightmost path
        if (node->right == NULL)
		return node;
	return find_max(node->right);
}

bool BinarySearchTree::contains(int value) const
{
        return contains(root, value);
}

//sees if a tree contains a node with a certain value
bool BinarySearchTree::contains(Node *node, int value) const
{
	//not here
	if (node == NULL)
		return false;
	//this is it
        if (node->data == value)
		return true;
	//recursive calls
	if (node->data < value)
		return contains(node->right, value);
	return contains(node->left, value);
}

void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

//inserts a new node or updates count
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
	//creating a new node and populating it
	if (node == NULL) {
		return new_node_insert(node,parent,value);
	}
	//already exists
        if (node->data == value) {
		node->count++;
	}
	//recursive calls
	if (node->data < value) {
		return insert(node->right, node, value);
	}
	if (node->data > value) {
		return insert(node->left, node, value);
	}
}

//helper function written to insert a completely new node
void BinarySearchTree::new_node_insert(Node* node, Node* parent, int value) {
	//make a new node & set all its values
	node = new Node();
	node->data = value;
	node->count = 1;
	node->left = NULL;
	node->right = NULL;
	if (parent == NULL) {
		root = node;
	}
	//have to figure out direction we came from
	else if (parent->data < value) {
		parent->right = node;
	}
	else {
		parent->left = node;
	} 
}

bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

//performs non-lazy removal on a node, decrements count if there is 
	//more than one
bool BinarySearchTree::remove(Node *node, Node *parent, int value) {
	//not in tree
	if (!(contains(node, value)) || node == NULL) return false; 
	
	if (node->data == value) { //found it
		//more than one
		if (node->count > 1) { 
			node->count--;
			return true;
		}
		if (node->left == NULL && node->right == NULL) { 
			return delete_leaf(node,parent);
		}
		if (node->left == NULL ^ node->right == NULL) {
			return bypass_node(node,parent);
		}
		//only case left is two children
		return two_child_delete(node);
	}
	else {
		if (node->data < value)
			return remove(node->right, node, value);
		return remove(node->left, node, value);
	}
}

//helper function written to delete a leaf node
bool BinarySearchTree::delete_leaf(Node* node, Node* parent) {
	if (parent == NULL) {
		delete node;
		root = NULL;
		return true;
	}
	if (parent->right == node) {
		delete node;
		parent->right = NULL;
	}
	else {
		delete node;
		parent->left = NULL;
	}
	return true;
}

//helper function written to bypass a node with one child
bool BinarySearchTree::bypass_node(Node *node, Node *parent) {
	//have to figure out what direction it's coming from
	if (node->left == NULL) {
		if (parent->right == node)
			parent->right = node->right;
		else
			parent->left = node->right;
		delete node;
		return true;
	}
	if (node->right == NULL) {
		if (parent->right == node)
			parent->right = node->left;
		else
			parent->left = node->left;
		delete node;
		return true;
	}
	return false;
}

//helper function written to delete a node w/ 2 children
bool BinarySearchTree::two_child_delete(Node* node){
	Node* min_right = find_min(node->right);
	node->data = min_right->data;
	node->count = min_right->count;
	//otherwise it would only lower the count:
	min_right->count = 1;
	return remove (node->right, node, min_right->data);	
}

int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

//finds the height of the tree, the longest path from root to leaf
int BinarySearchTree::tree_height(Node *node) const
{
        if (node == NULL) return -1;
        
        int right_height = tree_height(node->right);
	int left_height = tree_height(node->left);
	
	if (right_height >= left_height)
		return 1 + right_height;
	return 1 + left_height;
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

//counts total number of nodes
int BinarySearchTree::node_count(Node *node) const
{
        if (node == NULL) return 0;
        
        //post-order traversal
        return node_count(node->left) + 1 + node_count(node->right);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

//returns all the nodes' values added together
int BinarySearchTree::count_total(Node *node) const
{
        if (node == NULL) return 0;
        
        return count_total(node->left) + (node->count * node->data) + count_total(node->right);
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left==child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}
