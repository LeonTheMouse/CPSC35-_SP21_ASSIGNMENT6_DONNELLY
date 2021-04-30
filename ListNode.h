/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
using namespace std;

template <typename T>
class ListNode{
	public:
		ListNode();
		ListNode(T d);
		~ListNode();
		ListNode *next;
		ListNode *prev;
		T data;
};
#endif
template <typename T>
ListNode<T>::ListNode(){}

template <typename T>
ListNode<T>::ListNode(T d) {
	data = d;
	next = NULL;
	prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode() {
	next = NULL;
	prev = NULL;
	// if not null delete them
}
