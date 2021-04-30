/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#ifndef FACULTY_H
#define FACULTY_H
#include "Person.h"
#include "ListADT.h"
#include "DoublyLinkedList.h"


class Faculty : public Person {
public:
	string m_level;//member level
	string m_department;//member department

	DoublyLinkedList<int>* m_advisees;//list of advisees

	Faculty();//create empty faculty
	Faculty(int ID);//create faculty with ID
	Faculty(int ID, string name, string level, string department, DoublyLinkedList<int>* advisees);//create full faculty
	Faculty(const Faculty& faculty);//copy constructor
	~Faculty();
	Faculty& operator=(const Faculty& faculty);//faculty = assignment operator

    friend ostream& operator<<(ostream& out, const Faculty& faculty) {//cout for a faculty object
        out << "Faculty: " << faculty.m_name << endl;
        out << "ID: " << faculty.m_ID << endl;
        out << "Level: " << faculty.m_level << endl;
        out << "Department: " << faculty.m_department << endl;
        out << endl;
		out << "Advisees: " << endl;
		if (!faculty.m_advisees->isEmpty()) {
			for (unsigned int i = 0; i < faculty.m_advisees->getSize(); ++i) {
				out << faculty.m_advisees->getValAtIndex(i) << endl;
			}
		}
		else {
			out << "No Advisees to Dislpay" << endl;
		}
        return out;
    }

    friend istream& operator>>(istream& in, Faculty& faculty) {//interpret faculty data from line in file
		string currLine;
		string data = "";
		int dataCount = 0;
		getline(in, currLine, '\n');

		for (int i = 0; i < currLine.size(); i++) {
			if (currLine.at(i) == ';')
			{
				if (dataCount == 0) {
					faculty.m_ID = stoi(data);//ID number
				}
				else if (dataCount == 1) {
					faculty.m_name = data;//name
				}
				else if (dataCount == 2) {
					faculty.m_level = data;//level
				}
				else if (dataCount == 3) {
					faculty.m_department = data;//department
				}
				else {
					faculty.m_advisees->insertBack(stoi(data));//list of adsvisees
				}
				++dataCount;//counts chunks of data seperated in file by ;
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