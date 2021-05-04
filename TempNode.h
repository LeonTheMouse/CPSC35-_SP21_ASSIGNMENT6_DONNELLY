/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef TEMPNODE_H
#define TEMPNODE_H
#include <iostream>

using namespace std;

template <typename T>
class TempNode {
public:
	TempNode();//constructor
	TempNode(T data);//overloaded constructor
	~TempNode();//destructor
	TempNode *next;
	TempNode *prev;
	T data;
};

template <typename T>
TempNode<T>::TempNode(){}

template <typename T>
TempNode<T>::TempNode(T d) {//create node with given data
	data = d;
	next = NULL;
	prev = NULL;
}

template <typename T>
TempNode<T>::~TempNode() {//delete node
	next = NULL;
	prev = NULL;
}

#endif