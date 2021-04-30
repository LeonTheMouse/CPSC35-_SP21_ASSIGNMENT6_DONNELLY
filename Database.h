/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "BST.h"
#include "DoublyLinkedList.h"
#include "Student.h"
#include "Faculty.h"
#include "Transaction.h"
#include "GenStack.h"

using namespace std;

class Database {//this function basically runs the whole database rather than having a crowded main
public:
	//names of files used for storage
	string facultyFile;
	string studentFile;

	bool isRollBack;//allows us to use the same switch statement for rollback/non rollback situations

	BST<Student>* masterStudent;//BST for students
	BST<Faculty>* masterFaculty;//BST for faculty
	GenStack<Transaction>* rollBackData;//circular stack for keeping track of possibly needed rollbacks

	Database();//constructor
	~Database();//destructor

	void printMenu();//prints the menu of options to choose from

	void handleCase(int caseNum);//handles the appropriate case given user input

	void printStudents();//prints all of the students in the BST in ascending ID order
	void printFaculty();//prints all of the faculty members from the BST in ascending ID order

	void displayStudentInfo(Student* student);//displays a specific student
	void displayFacultyInfo(Faculty* faculty);//displays a specific faculty member

	void displayStudentAdvisorInfo(Student* student);//displays the student's advisor information
	void displayFacultyAdvisees(Faculty* faculty);//displays all of the faculty's advisees information

	bool isInterger(string input);//checks if string represents a valid interger
	bool isDouble(string input);//checks if string represents a valid double for GPA input
	
	void addNewStudent(Student* student);//add a new student to the BST
	void deleteStudent(Student* student);//delete a student from the BST
	
	void addNewFaculty(Faculty* faculty);//add new faculty to BST
	void deleteFaculty(Faculty* faculty);//delete faculty from BST
	
	void changeAdvisor(Student* student, Faculty* newAdvisor);//change a student's advisor
	void removeAdvisee(Faculty* faculty, Student* student);//remove an advisee from a faculty's list
	
	void revertStudentAndFacultyMember(Student student, Faculty faculty);//replace student and faculty members in the BST to complete rollback

	void rollback();//reverses the previous actions that effected the BST's
	
	void clearFile(string file);//empties a file
	bool fileExists(string file);//checks if a file exists
	void outputData();//puts BST data into a text file
	void outputStudentData();//formats student BST for file output
	void outputFacultyData();//formats faculty BST for file output
	void loadSaveData();//generates the BST at beginning
	void loadStudentData();//reads from file to format student data
	void loadFacultyData();//reads from file to format faculty data

	int getNextInput();//prints the menu and prompts for input form user
	Student* getStudentFromInput();//prompt for input of a student ID that exists
	Faculty* getFacultyFromInput();//prompt for input of a faculty ID that exists

	Student* createStudentFromInput();//prompt for appropriate data to create a new student
	Faculty* createFacultyFromInput();//prompt for appropriate data to create a new faculty member

	Student* getStudentWithID(int ID);//get a pointer to a given student with the ID
	Faculty* getFacultyWithID(int ID);//get a pointer to a given faculty with the ID
};
#endif
