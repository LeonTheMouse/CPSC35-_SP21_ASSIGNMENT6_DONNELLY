/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#include "Transaction.h"


Transaction::Transaction() {
	caseNum = -1;
	oldStudent = Student();
	newStudent = Student();
	oldFaculty = Faculty();
	newFaculty = Faculty();
}

Transaction::Transaction(Student student, string addOrDelete) {
	if (addOrDelete == "Add") {//transaction for adding student
		caseNum = 7;
		newStudent = student;
		oldStudent = Student();
	}
	else if (addOrDelete == "Delete") {//transaction for deleting student
		caseNum = 8;
		oldStudent = student;
		newStudent = Student();
	}
	oldFaculty = Faculty();
	newFaculty = Faculty();
	
}

Transaction::Transaction(Faculty faculty, string addOrDelete) {
	if (addOrDelete == "Add") {//transaction for adding faculty
		oldFaculty = Faculty();
		newFaculty = faculty;
		caseNum = 9;
	}
	else if (addOrDelete == "Delete") {//transaction for deleting faculty
		newFaculty = Faculty();
		oldFaculty = faculty;
		caseNum = 10;
	}
	oldStudent = Student();
	newStudent = Student();
}

Transaction::Transaction(Student student, Faculty faculty, int caseNumber) {
	caseNum = caseNumber;//either switch advisees back or add advisees back
	oldFaculty = faculty;
	oldStudent = student;
	newFaculty = Faculty();
	newStudent = Student();
}



