/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
//this stack is now circular
#ifndef GENSTACK_H
#define GENSTACK_H
#include "TempNode.h"
#include <iostream>
using namespace std;

template <typename T>
class GenStack {
	public:
		GenStack(int size);
		~GenStack();
		void push(T value);
		T pop();
		bool isEmpty();
		T peek();
		int getCount();
		void removeBottom();//needed to get rid of old rollbacks
		int maxSize;//keeps only 5 rollbacks possible
		int count;//size of stack

	private:
		TempNode<T> *top;
};

template <typename T>
GenStack<T>::GenStack(int size) {//sets max size of stack, could be modified to make rollback go further
	maxSize = size;
	top = NULL;
	count = 0;
}


template <typename T>
GenStack<T>::~GenStack() {
	while (count != 0) {
		TempNode<T>* tp = top;//set new pointer to point to top
		top = top->prev;//set top to tops previous
		--count;
		tp->prev = NULL;//null out old tops pointers
		tp->next = NULL;
		delete tp;	
	}
}

template <typename T>
void GenStack<T>::push(T value) {
	TempNode<T> *ptr = new TempNode<T>(value);//make new node with given value and null prev and next pointers
	if (count == maxSize) {
		removeBottom();//makes the queue circular
	}
	if (isEmpty()) {//if its the first node created front and next will be null
		ptr->prev = NULL;
		ptr->next = NULL;
		top = ptr;
		count++;
	}
	else {//other wise
		top->next = ptr;
		ptr->prev = top;
		top = ptr;
		ptr->next = NULL;
		count++;
	}
}

template <typename T>
void GenStack<T>::removeBottom() {
	TempNode<T>* curr = top;
	for (int i = 0; i < count - 1; i++) {
		curr = curr->prev;
	}
	TempNode<T>* next = curr->next;
	next->prev = NULL;
	curr->next = NULL;
	curr->prev = NULL;
	curr = NULL;
	--count;

}

template <typename T>
T GenStack<T>::pop() {
	TempNode<T> *tp = top;

	if (isEmpty()) {
		delete tp;
		throw runtime_error("Stack is Empty, cannot pop. Please check your input notation");//cant pop if empty
	}
	T value = top->data;//get value from top
	top = top->prev;// set new top
	--count;
	delete tp;//delete the old top
	return value;
	
}

template <typename T>
T GenStack<T>::peek() {
	T value = top->data;
	return value;
}

template <typename T>
bool GenStack<T>::isEmpty() {
	if (count == 0) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
int GenStack<T>::getCount() {
	return count;
}

#endif