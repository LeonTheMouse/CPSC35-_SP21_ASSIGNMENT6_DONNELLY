/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#include "Student.h"

Student::Student() {//create empty student
	m_level = "-1";
	m_major = "-1";
	m_GPA = 0.0;
	m_advisorID = -1;
}

Student::Student(int ID) {//create student to check if one exists with same ID
	m_ID = ID;
	m_level = "-1";
	m_major = "-1";
	m_GPA = 0.0;
	m_advisorID = -1;
}

Student::Student(string name, string major, string level, int ID, double GPA, int advisorID) {//make a full student
	m_ID = ID;
	m_name = name;
	m_level = level;
	m_major = major;
	m_GPA = GPA;
	m_advisorID = advisorID;
}

Student::~Student() {}