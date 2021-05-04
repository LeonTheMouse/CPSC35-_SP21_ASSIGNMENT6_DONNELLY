/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"

 
class Student : public Person {
public:
	string m_level;//member level
	string m_major;//member major
	double m_GPA;//member gpa
	int m_advisorID;//memboer advisorID

	Student();//default student
	Student(int ID);//student with only ID
	Student(string name, string major, string level, int ID, double GPA, int advisorID);// full student
	~Student();

	friend ostream& operator<<(ostream& out, const Student& student) {// overides cout << student << so it displays the required information
		out << "Student: " << student.m_name << endl;
		out << "ID: " << student.m_ID << endl;
		out << "Level: " << student.m_level << endl;
		out << "Major: " << student.m_major << endl;
		out << "GPA: " << student.m_GPA << endl;
		out << "Advisor's ID: " << student.m_advisorID << endl;
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Student& student) {//interprets a student from a line in a file 
		string currLine;
		string data = "";
		int dataCount = 0;
		getline(in, currLine, '\n');
		
		for (int i = 0; i < currLine.size(); i++) {
			if (currLine.at(i) == ';')
			{
				if (dataCount == 0) {
					student.m_ID = stoi(data);//ID
				}
				else if (dataCount == 1) {
					student.m_name = data;//Name
				}
				else if (dataCount == 2) {
					student.m_major = data;//Major
				}
				else if (dataCount == 3) {
					student.m_level = data;//Level
				}
				else if (dataCount == 4) {
					student.m_GPA = stod(data);//GPA
				}
				else {
					student.m_advisorID = stoi(data);//Advisor's ID
				}
				++dataCount;
				data = "";
			}
			else {
				data += currLine.at(i);
			}
		}
		
		return in;
	}
};

#endif