/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef BST_H
#define BST_H

using namespace std;
#include <iostream>
#include "TreeNode.h"
#include "DoublyLinkedList.h"

template <typename T>
class BST {
private:
	TreeNode<T>* root;


public:
	BST();
	~BST();

	void insert(T value);
	void destroyRecursive(TreeNode<T>* node);
	T* find(T value);//this is search
	bool deleteNode(T k);
	bool isEmpty();

	T* getMin();
	T* getMax();//return T* if template class

	TreeNode<T>* getSuccessor(TreeNode<T>* d);//this function plays a large role in deleteNode()

	DoublyLinkedList<T>* toList();
	void preOrderList(TreeNode<T>* node, DoublyLinkedList<T>* list);


	void recPrint(TreeNode<T>* node);
	void print();


};

template <typename T>
BST<T>::BST() {
	root = NULL; //empty tree
}

template <typename T>
BST<T>::~BST() {
	destroyRecursive(root);
}

template <typename T>
void BST<T>::print() {
	if (isEmpty()) {
		throw runtime_error("Can't Print Empty BST");
	}
	else {
		recPrint(root);
	}
	
}

template <typename T>
void BST<T>::recPrint(TreeNode<T>* node) {
	if (node == NULL)
		return;
	recPrint(node->left);
	cout << node->key << endl;
	recPrint(node->right);
}

template <typename T>
void BST<T>::destroyRecursive(TreeNode<T>* node) {
	if (node != NULL) {
		destroyRecursive(node->left);
		destroyRecursive(node->right);
		delete node;
	}
	return;
}

template <typename T>
T* BST<T>::getMin() {
	if (root == NULL)
		return NULL;

	TreeNode<T>* current = root;

	while (current->left != NULL) {
		current = current->left;
	}

	return &current->key;
}

template <typename T>
T* BST<T>::getMax() {
	if (root == NULL)
		return NULL;

	TreeNode<T>* current = root;

	while (current->right != NULL) {
		current = current->right;
	}

	return &current->key;
}

template <typename T>
void BST<T>::insert(T value) {
	TreeNode<T>* node = new TreeNode<T>(value);

	if (isEmpty()) {
		root = node;
	}
	else {
		// the tree is not empty, need to find the insertion point.
		TreeNode<T>* current = root;
		TreeNode<T>* parent = NULL;
		while (true) {
			parent = current;
			// overload <
			if (value < current->key) {
				current = current->left;
				if (current == NULL) {
					// found insertion point
					parent->left = node;
					break;
				}
			}
			else {
				current = current->right;
				if (current == NULL) {
					// found insertion
					parent->right = node;
					break;
				}
			}
		}
	}
}

template <typename T>
T* BST<T>::find(T value) {
	if (isEmpty()) {
		return NULL;
	}
	else {  //not empty
		TreeNode<T>* current = root;

		while (current->key != value) {
			if (value < current->key) {
				current = current->left;
			}
			else {
				current = current->right;
			}
			if (current == NULL) {
				return NULL;
			}
		}
		return &current->key;
	}
}


template <typename T>
bool BST<T>::deleteNode(T key) {
	if (isEmpty())
		return false;

	TreeNode<T>* parent = NULL;
	TreeNode<T>* current = root;
	bool isLeftNode = true;

	while (current->key != key) {
		parent = current;

		if (key < current->key) {
			isLeftNode = true;
			current = current->left;
		}
		else {
			isLeftNode = false;
			current = current->right;
		}

		if (current == NULL) {
			return false;
		}
	}
		//value found, need to delete

		//case: node to be deleted does not have children, AKA leaf Node.
		if (current->left == NULL && current->right == NULL) {
			if (current == root) {
				root = NULL;
			}
			else if (isLeftNode) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		//case: node to be deleted has one child. need to determine whether descendent is left or right
		else if (current->right == NULL) {
			//doesnt have right child, must have left
			if (current == root) {
				root = current->left;
			}
			else if (isLeftNode) {
				parent->left = current->left;
			}
			else {
				//node to be deleted is a right child
				parent->right = current->left;
			}
		}
		//case: node to be deleted has one child
		else if (current->left == NULL) {
			//doesnt have left child, must have right
			if (current == root) {
				root = current->right;
			}
			else if (isLeftNode) {
				parent->left = current->right;
			}
			else {
				//node to be deleted is a right child
				parent->right = current->right;
			}
		}
		else {
			//node to be deleted has 2 children, must find successor
			TreeNode<T>* successor = getSuccessor(current);
			if (current == root) {
				root = successor;
			}
			else if (isLeftNode) {
				parent->left = successor;
			}
			else {
				parent->right = successor;
			}
			successor->left = current->left;
		}
		delete current;
		return true;

}

template <typename T>
DoublyLinkedList<T>* BST<T>::toList() {
	if (isEmpty()) {
		throw runtime_error("Can't operate on empty list.");
	}
	TreeNode<T>* curr = root;
	DoublyLinkedList<T>* list = new DoublyLinkedList<T>();
	preOrderList(root, list);
	return list;

}

template <typename T>
void BST<T>::preOrderList(TreeNode<T>* node, DoublyLinkedList<T>* list) {
	if (node == NULL) {
		return;
	}
	list->insertBack(node->key);
	preOrderList(node->left, list);
	preOrderList(node->right, list);
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d) {

	TreeNode<T>* sp = d;
	TreeNode<T>* successor = d;
	TreeNode<T>* current = d->right;

	while (current != NULL) {
		sp = successor;
		successor = current;
		current = current->left;
	}

	if (successor != d->right) {
		sp->left = successor->right;
		successor->right = d->right;
	}
	return successor;

}

template <typename T>
bool BST<T>::isEmpty() {
	return (root == NULL);
}



#endif