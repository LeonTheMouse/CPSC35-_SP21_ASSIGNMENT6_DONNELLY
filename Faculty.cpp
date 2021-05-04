/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#include "Faculty.h"
#include <iostream>

using namespace std;

Faculty::Faculty() {//defualt faculty
	m_level = "-1";
	m_department = "-1";
	m_advisees = new DoublyLinkedList<int>();
}

Faculty::Faculty(int ID) {//used to see if faculty with same ID exists
	m_ID = ID;
	m_level = "-1";
	m_department = "-1";
	m_advisees = new DoublyLinkedList<int>();
}

Faculty::Faculty(int ID, string name, string level, string department, DoublyLinkedList<int>* advisees) {//full faculty member
	m_ID = ID;
	m_name = name;
	m_level = level;
	m_department = department;
	m_advisees = advisees;
}

Faculty::~Faculty(){
	delete m_advisees;//delete the list of advisees
}

Faculty& Faculty::operator=(const Faculty& faculty) {//set a faculty = to another faculty
	if (this == &faculty) {
		return *this;
	}
	m_name = faculty.m_name;
	m_ID = faculty.m_ID;
	m_level = faculty.m_level;
	m_department = faculty.m_department;
	*m_advisees = *faculty.m_advisees;
	return *this;
}

Faculty::Faculty(const Faculty& faculty) {//create a copy of a faculty member
	m_advisees = new DoublyLinkedList<int>();
	m_name = faculty.m_name;
	m_ID = faculty.m_ID;
	m_level = faculty.m_level;
	m_department = faculty.m_department;
	*m_advisees = *faculty.m_advisees;

}