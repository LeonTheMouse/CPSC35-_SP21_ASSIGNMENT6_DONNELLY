/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Person {
public:
	int m_ID;//all people have an ID
	string m_name;//all have a name

	Person();//default constructor
	Person(int ID, string name);//overloaded constructor
	~Person();//destructor

	bool operator==(const Person& right);//operand overide to compare persons
	bool operator!=(const Person& right);//check if people aren't the same
	bool operator<(const Person& right);//check if person has lower ID than another
};

#endif
