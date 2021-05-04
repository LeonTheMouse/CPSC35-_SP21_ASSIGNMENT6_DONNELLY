/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef LISTADT_H
#define LISTADT_H

#include <iostream>

using namespace std;

template <typename T>
class ListADT {
public:
	virtual void insertFront(T data)=0;
	virtual void insertBack(T data)=0;
	virtual void printList(bool printLink)=0;
	virtual T remove(T key)=0;
	virtual int find(T key)=0;
	virtual T peekFront()=0;
	virtual T peekBack()=0;
	virtual T removeFront()=0;
	virtual T removeBack()=0;
	virtual size_t getSize()=0;
	virtual bool isEmpty()=0;
};



#endif