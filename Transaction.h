/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Student.h"
#include "Faculty.h"
#include <iostream>

using namespace std;

class Transaction {
public:
	//7-12
	int caseNum;//represents command that generated the transaction
	//Faculty/Student objects
	Student oldStudent;
	Student newStudent;
	Faculty oldFaculty;
	Faculty newFaculty;

	Transaction();//defualt transaction
	Transaction(Student student, string addOrDelete);//transaction for undoing student addition/deletion
	Transaction(Faculty faculty, string addOrDelete);//transaction for undoing faculty addition/deletion
	Transaction(Student student, Faculty faculty, int caseNumber);//for any transactions that need to store both faculty and student

};
#endif