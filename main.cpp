/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#include <iostream>
#include <fstream>
#include "BST.h"
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "ListADT.h"
#include "Database.h"

using namespace std;

int main(){
	bool isRunning = true;
	int caseNum;
	Database db = Database();
	db.loadSaveData();//load data from text files into BST's
	cout << "Student/Faculty Database Initilized" << endl;
	while (isRunning) {
		caseNum = db.getNextInput();//prompt for user input
		if (caseNum == -1) {
			continue;
		}
		cout << caseNum << endl;
		if (caseNum == 14) {//exit
			isRunning = false;
		}
		db.handleCase(caseNum);//
	}	
	return 0;
}