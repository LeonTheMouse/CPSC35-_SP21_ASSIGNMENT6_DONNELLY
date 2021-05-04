/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
using namespace std;

template <typename T>
class TreeNode {

public:
	TreeNode();
	TreeNode(T k);

	~TreeNode();

	T key;
	TreeNode<T>* left;
	TreeNode<T>* right;
};

template <typename T>
TreeNode<T>::TreeNode() {
	left = NULL;
	right = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T k) {
	left = NULL;
	right = NULL;
	key = k;
}

template <typename T>
TreeNode<T>::~TreeNode() {
	left = NULL;
	right = NULL;
}

#endif