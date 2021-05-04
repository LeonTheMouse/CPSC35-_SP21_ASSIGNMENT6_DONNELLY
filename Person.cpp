/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#include "Person.h"

Person::Person(){//defualt person
	m_ID = -1;
	m_name = "-1";
}

Person::Person(int ID, string name) {//overloaded person
	m_ID = ID;
	m_name = name;
}

Person::~Person() {}

bool Person::operator==(const Person& right) {
	return (this->m_ID == right.m_ID);//compare ID ==
}

bool Person::operator!=(const Person& right) {
	return (this->m_ID != right.m_ID);//compare ID !=
}
bool Person::operator<(const Person& right) {
	return (this->m_ID < right.m_ID);//compare ID <
}