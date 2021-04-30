/* Jack Donnelly
2342203
CPSC 350-02
Assignment 6
*/
#include "Database.h"
#include <fstream>

Database::Database() {
	masterStudent = new BST<Student>();
	masterFaculty = new BST<Faculty>();
	rollBackData = new GenStack<Transaction>(5);
	studentFile = "studentTable.txt";
	facultyFile = "facultyTable.txt";
	isRollBack = false;
}

Database::~Database() {
	delete masterStudent;
	delete masterFaculty;
	delete rollBackData;
}

void Database::printMenu() {
	cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
	cout << "<> Database Options:                                                              <>" << endl;
	cout << "<> [1] Print all students by ascending ID                                         <>" << endl;
	cout << "<> [2] Print all faculty by ascending ID                                          <>" << endl;
	cout << "<> [3] Print student info given ID                                                <>" << endl;
	cout << "<> [4] Print faculty info given student ID                                        <>" << endl;
	cout << "<> [5] Print a students advisor info given ID                                     <>" << endl;
	cout << "<> [6] Print all advisee info given advisor ID                                    <>" << endl;
	cout << "<> [7] Add a new student                                                          <>" << endl;
	cout << "<> [8] Delete student given ID                                                    <>" << endl;
	cout << "<> [9] Add a new faculty member                                                   <>" << endl;
	cout << "<> [10] Delete faculty given ID                                                   <>" << endl;
	cout << "<> [11] Change student's advisor given student ID and new faculty ID              <>" << endl;
	cout << "<> [12] Remove advisee from faculty member given student ID and faculty ID        <>" << endl;
	cout << "<> [13] Rollback                                                                  <>" << endl;
	cout << "<> [14] Exit                                                                      <>" << endl;
	cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endl;
}

void Database::handleCase(int caseNum) {
	Transaction transaction;//given transaction to be created by the case
	Student* student = NULL;//student to be manupulated
	Faculty* oldFaculty = NULL;//old faculty to be manipulated
	Faculty* faculty = NULL;//current faculty


	switch (caseNum) {
		case 1://print all students
			printStudents();
			return;
		case 2://print all faculty
			printFaculty();
			return;
		case 3://print specific student with ID
			student = getStudentFromInput();
			displayStudentInfo(student);
			return;
		case 4://print specific faculty with ID
			faculty = getFacultyFromInput();
			displayFacultyInfo(faculty);
			return;
		case 5://print student's advisor info
			student = getStudentFromInput();
			displayStudentAdvisorInfo(student);
			return;
		case 6://print all students that faculty advises
			faculty = getFacultyFromInput();
			displayFacultyAdvisees(faculty);
			return;
		case 7://create a new student from input// if rollback delete that student
			if (!isRollBack) {
			student = createStudentFromInput();
				if (student == NULL) {
					return;
				}
				else {
					transaction = Transaction(*student, "Add");//create an appropriate transaction
					rollBackData->push(transaction);
				}
			}
			else {
				transaction = rollBackData->pop();
				student = &transaction.oldStudent;
			}
			addNewStudent(student);
			return;
		case 8://delete a student given ID, if rollback add that student back in
			if (!isRollBack) {
				student = getStudentFromInput();
				if (student == NULL) {
					return;
				}
				else {
					transaction = Transaction(*student, "Delete");//create a transaction with the given student
					rollBackData->push(transaction);//push the transaction to the stack
				}
			}
			else {
				transaction = rollBackData->pop();//get latest transaction from the stack
				student = &transaction.newStudent;//perform rollback action
			}
			deleteStudent(student);
			return;
		case 9://create a new faculty from imput, if rollback delete that faculty
			if (!isRollBack) {
				faculty = createFacultyFromInput();
				if (faculty == NULL) {
					return;
				}
				else {
					transaction = Transaction(*faculty, "Add");//create an appropriate transaction
					rollBackData->push(transaction);//add transaction to stack
				}
			}
			else {
				transaction = rollBackData->pop();
				faculty = &transaction.oldFaculty;//perform rollback action
			}
			addNewFaculty(faculty);
			return;
		case 10://delete a faculty given the ID, if rollack add them back
			if (!isRollBack) {
				faculty = getFacultyFromInput();
				if (faculty == NULL) {
					return;
				}
				else {
					transaction = Transaction(*faculty, "Delete");//create an appropriate transaction
					rollBackData->push(transaction);//add transaction to stack
				}
			}
			else {
				transaction = rollBackData->pop();
				faculty = &transaction.newFaculty;//perform rollback action
			}
			deleteFaculty(faculty);
			return;
		case 11://change student's advisor, if rollback change it back
			student = getStudentFromInput();
			if (student == NULL) {
				return;
			}
			//new faculty
			faculty = getFacultyFromInput();
			if (faculty == NULL) {
				return;
			}
			oldFaculty = getFacultyWithID(student->m_advisorID);
			if (oldFaculty == NULL) {
				oldFaculty = new Faculty();
			}
			transaction = Transaction(*student, *oldFaculty, 11);//create appropriate transaction
			if (oldFaculty->m_name == "-1") {
				delete oldFaculty;
			}
			rollBackData->push(transaction);//add transaction to stack
			changeAdvisor(student, faculty);
			return;
		case 12://remove a given adviss, if rollback add them back
			if (!isRollBack) {
				faculty = getFacultyFromInput();
				if (faculty == NULL) {
					return;
				}
				student = getStudentFromInput();
				if (student == NULL) {
					return;
				}
				if (faculty->m_advisees->find(student->m_ID) == -1) {
					cout << "ERROR: student is not advisee of faculty member!" << endl;
					return;
				}
				transaction = Transaction(*student, *faculty, 12);
				rollBackData->push(transaction);//add transaction to stack
			}
			else {
				transaction = rollBackData->pop();
				changeAdvisor(&transaction.oldStudent, &transaction.oldFaculty);//perform rollback action
			}
			removeAdvisee(faculty, student);
			return;
		case 13:// trigger a rollback
			if (rollBackData->isEmpty()) {
				cout << "ERROR: No actions to undo!" << endl;
				return;
			}
			rollback();
			return;
		case 14://save the data and quit
			outputData();
			return;
	}
}

void Database::printStudents() {
	if (masterStudent->isEmpty()) {
		cout << "Can't print empty student table." << endl;
		return;
	}
	cout << "All Students: " << endl;
	masterStudent->print();//prints all students in ascending ID order
}

void Database::printFaculty() {
	if (masterFaculty->isEmpty()) {
		cout << "Can't print empty faculty table." << endl;
		return;
	}
	cout << "All Faculty: " << endl;
	masterFaculty->print();//prints all faculty in ascending ID order
}


void Database::displayStudentInfo(Student* student) {
	if (student == NULL) {
		return;//exit
	}
	cout << "\n" << *student;//prints a student
}

void Database::displayFacultyInfo(Faculty* faculty) {
	if (faculty == NULL) {
		return;//exit
	}
	cout << "\n" << *faculty;//prints a faculty member
}



void Database::displayStudentAdvisorInfo(Student* student) {
	if (student == NULL) {
		return;//exit
	}
	if (student->m_advisorID == -1) {//advisor hasn't been set yet
		cout << "ERROR: Student doesn't have advisor!" << endl;
	}
	Faculty* advisor = getFacultyWithID(student->m_advisorID);
	cout << "\n" << *advisor;
}


void Database::displayFacultyAdvisees(Faculty* faculty) {
	if (faculty == NULL) {
		return;//exit
	}
	if (faculty->m_advisees->isEmpty()) {//list of advisees is empty
		cout << "ERROR: Faculty has no advisees!" << endl;
		return;
	}
	Student* student;
	cout << "\n";
	for (unsigned int i = 0; i < faculty->m_advisees->getSize(); i++) {
		student = getStudentWithID(faculty->m_advisees->getValAtIndex(i));
		cout << *student;//print the student at given i in the list of advisees
	}
}

bool Database::isInterger(string input) {//checks if whole string is interger rather than just a character
	if (input.at(0) == '0') {
		return false;
	}
	for (int i = 0; i < input.size(); i++) {
		if (!isdigit(input.at(i))) {
			return false;
		}
	}
	return true;
}

bool Database::isDouble(string input) {//makes sure input is given in a.b notation
	int decimal = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == '.'){
		++decimal;
		}
		if (!isdigit(input.at(i)) && input.at(i) != '.'){
			return false;
		}
	}
	if (decimal > 1) {
		return false;
	}
	if (decimal == 0 && input.at(0) == '0') {
		return false;
	}
	return true;
}

void Database::addNewStudent(Student* student) {
	masterStudent->insert(*student);
	if (student->m_advisorID != 1) {//if they have an advisor update said advisor to have them
		Faculty* advisor = getFacultyWithID(student->m_advisorID);
		advisor->m_advisees->insertBack(student->m_ID);
	}
	if (!isRollBack) {
		delete student;//reverse operation
	}
}

void Database::deleteStudent(Student* student) {
	Faculty* advisor = getFacultyWithID(student->m_advisorID);
	if (advisor != NULL) {//if they have an advisor make sure they get deleted from the advisors list
		advisor->m_advisees->remove(student->m_ID);
	}
	masterStudent->deleteNode(*student);
}

void Database::addNewFaculty(Faculty* faculty) {
	masterFaculty->insert(*faculty);
	Student* advisee;
	for (unsigned int i = 0; i < faculty->m_advisees->getSize(); i++) {
		advisee = getStudentWithID(faculty->m_advisees->getValAtIndex(i));
		advisee->m_advisorID = faculty->m_ID;//change advisee ID
	}
	if (!isRollBack) {
		delete faculty;//reverse operation
	}
}

void Database::deleteFaculty(Faculty* faculty) {
	Student* student;
	for (unsigned int i = 0; i < faculty->m_advisees->getSize(); i++) {
		student = getStudentWithID(faculty->m_advisees->getValAtIndex(i));
		student->m_advisorID = -1;//set all advisees advisor IDs to -1
	}
	masterFaculty->deleteNode(*faculty);
}

void Database::changeAdvisor(Student* student, Faculty* newAdvisor) {
	int oldAdvisorID = student->m_advisorID;
	Faculty* oldAdvisor;
	oldAdvisor = getFacultyWithID(oldAdvisorID);
	if (oldAdvisor != NULL) {
		removeAdvisee(oldAdvisor, student);//remove old advisee
	}
	if (newAdvisor == NULL) {
		student->m_advisorID = -1;
	}
	else {
		student->m_advisorID = newAdvisor->m_ID;
		newAdvisor->m_advisees->insertBack(student->m_ID);
	}
}

void Database::removeAdvisee(Faculty* faculty, Student* student) {
	int studentID = student->m_ID;
	if (faculty->m_advisees->find(studentID) == -1){//check if student exists first
		return;//exit
	}
	else {
		faculty->m_advisees->remove(studentID);
	}
		student->m_advisorID = -1;
}

void Database::revertStudentAndFacultyMember(Student student, Faculty faculty) {
	//removal is ID based so this removes the student and faculty to be reverted not the actual student/ faculty provided in argument
	if (faculty.m_name != "-1") {
		masterFaculty->deleteNode(faculty);
		masterFaculty->insert(faculty);
	}
	masterStudent->deleteNode(student);
	masterStudent->insert(student);
}

void Database::rollback() {
	//works by calling the appropriate functions to undo the actions
	isRollBack = true;//keeps rollback true in handlecase
	Transaction transaction;
	Student* student1;
	Faculty* faculty1;
	int caseNumber = (rollBackData->peek()).caseNum;

	cout << "RollBack Case Number: " << caseNumber << endl;

	switch (caseNumber) {
		case 7:
			handleCase(8);
			break;
		case 8:
			handleCase(7);
			break;
		case 9:
			handleCase(10);
			break;
		case 10:
			handleCase(9);
			break;
		case 11:
			transaction = rollBackData->pop();
			student1 = masterStudent->find(transaction.oldStudent);
			faculty1 = masterFaculty->find(student1->m_advisorID);
			removeAdvisee(faculty1, student1);
			revertStudentAndFacultyMember(transaction.oldStudent, transaction.oldFaculty);//revert BST by replacing new Faculty/student with old ones
			break;
		case 12:
			transaction = rollBackData->pop();
			revertStudentAndFacultyMember(transaction.oldStudent, transaction.oldFaculty);
			break;
	}
	isRollBack = false;//once rollback is complete handlecase is no longer doing rollback
}

void Database::clearFile(string file) {//also creates new files of that name if they don't exist
	ofstream OFS;
	OFS.open(file);
	OFS.close();
}

bool Database::fileExists(string file) {
	ifstream IFS;
	IFS.open(file);
	return IFS.is_open();//returns true if file is open
}

void Database::outputData() {
	if (!fileExists("studentTable.txt") && !fileExists("facultyTable.txt")) {
		return;//don't run if files don't exist yet
	}

	outputStudentData();
	outputFacultyData();
}

void Database::outputStudentData() {
	if (masterStudent->isEmpty()) {
		clearFile("studentTable.txt");//make sure file is empty
		return;
	}
	ofstream OFS1;
	DoublyLinkedList<Student>* studentList = masterStudent->toList();
	Student tempStudent;
	OFS1.open(studentFile);
	if (!OFS1.is_open()) {
		throw runtime_error("Can't open Student File");
	}
	for (unsigned int i = 0; i < studentList->getSize(); i++) {
		tempStudent = studentList->getValAtIndex(i);
		OFS1 << tempStudent.m_ID << ";" << tempStudent.m_name << ";" << tempStudent.m_major << ";" << tempStudent.m_level << ";" << tempStudent.m_GPA << ";" << tempStudent.m_advisorID << ";" << endl;//write this line into the file for each node
	}
	OFS1.close();

}

void Database::outputFacultyData() {
	if (masterFaculty->isEmpty()) {
		clearFile("facultyTable.txt");
		return;
	}
	ofstream OFS2;
	DoublyLinkedList<Faculty>* facultyList = masterFaculty->toList();
	Faculty tempFaculty;
	OFS2.open(facultyFile);
	if (!OFS2.is_open()) {
		throw runtime_error("Can't open Faculty File");
	}
	for (unsigned int i = 0; i < facultyList->getSize(); i++) {
		tempFaculty = facultyList->getValAtIndex(i);
		OFS2 << tempFaculty.m_ID << ";" << tempFaculty.m_name << ";" << tempFaculty.m_level << ";" << tempFaculty.m_department << ";";//write this line into the file for each node
		for (unsigned int i = 0; i < tempFaculty.m_advisees->getSize(); i++) {
			OFS2 << tempFaculty.m_advisees->getValAtIndex(i) << ";";
		}
		OFS2 << endl;
	}
	OFS2.close();
	delete facultyList;

}

void Database::loadSaveData(){
	loadStudentData();
	loadFacultyData();
}

void Database::loadStudentData() {
	Student stud1 = Student();
	ifstream IFS1;
	IFS1.open("studentTable.txt");
	while (IFS1 >> stud1) {
		masterStudent->insert(stud1);//insert student one by one
		stud1 = Student();
	}
	IFS1.close();
	
}

void Database::loadFacultyData() {
	Faculty fac1 = Faculty();
	ifstream IFS2;
	IFS2.open("facultyTable.txt");
	while (IFS2 >> fac1) {
		masterFaculty->insert(fac1);
		fac1 = Faculty();
	}
	IFS2.close();
}

int Database::getNextInput() {//get inputs for menu and make sure they are in the right range
	string input;
	int caseNumber;
	printMenu();
	getline(cin, input);
	if (!isInterger(input)) {
		cout << "Please provide an interger between 1 and 14." << endl;
		return -1;
	}
	caseNumber = stoi(input);
	if (caseNumber < 0 || caseNumber > 14) {
		cout << "Invalid command, please try again." << endl;
		return -1;
	}

	return caseNumber;
}

Student* Database::getStudentFromInput() {//asks for and checks student ID to make sure it exists
	string input;
	Student* student;
	int ID;
	while (true) {
		cout << "Please provide a valid student ID (q to quit): " << endl;
		getline(cin, input);
		if (input == "q")
			break;
		if (!isInterger(input)) {
			cout << "ERROR: Please enter a valid interger!" << endl;
			continue;
		}
		ID = stoi(input);
		student = getStudentWithID(ID);
		if (student == NULL) {
			cout << "ERROR: student not found!" << endl;
		}
		return student;
	}
	return NULL;
}

Faculty* Database::getFacultyFromInput() {//gets faculty ID and checks if they exist
	string input;
	Faculty* faculty;
	int ID;
	while (true) {
		cout << "Please provide a valid faculty ID (q to quit): " << endl;
		getline(cin, input);
		if (input == "q")
			break;
		if (!isInterger(input)) {
			cout << "ERROR: Please enter a valid interger!" << endl;
			continue;
		}
		ID = stoi(input);
		faculty = getFacultyWithID(ID);
		if (faculty == NULL) {
			cout << "ERROR: faculty not found!" << endl;
		}
		return faculty;
	}
	return NULL;
}

Student* Database::createStudentFromInput() {//asks user for all required data from a student
	Student* preStudent;
	Faculty* preFaculty;
	Student* student;
	string input;
	int ID;
	string name;
	string major;
	string level;
	double GPA;
	int advisorID;

	while (true) {
		cout << "Enter student's ID (press q to quit) " << endl;
		getline(cin, input);
		cout << "\n";
		if (input == "q") {
			return NULL;//forces a quit from handleCase()
		}
		if (!isInterger(input)) {
			cout << "Invalid ID, please enter a valid ID." << endl;
			continue;
		}
		ID = stoi(input);
		preStudent = getStudentWithID(ID);
		if (preStudent != NULL) {
			cout << "ERROR: student already exists!" << endl;
			continue;
		}
		break;
	}
	cout << "Enter student's name: " << endl;
	getline(cin, input);
	cout << "\n";
	name = input;

	cout << "Enter student's major: " << endl;
	getline(cin, input);
	cout << "\n";
	major = input;

	cout << "Enter student's level: " << endl;
	getline(cin, input);
	cout << "\n";
	level = input;

	while (true) {
		cout << "Enter student's GPA (press q to quit) " << endl;
		getline(cin, input);
		cout << "\n";
		if (input == "q") {
			return NULL;
		}
		if (!isDouble(input)) {
			cout << "Invalid input, please provide a double." << endl;
			continue;
		}
		GPA = stod(input);
		break;
	}

	while (true) {
		cout << "Enter student's advisor ID (press q to quit) " << endl;
		getline(cin, input);
		cout << "\n";
		if (input == "q") {
			return NULL;
		}
		if (!isInterger(input)) {
			cout << "Invalid input, please provide an int." << endl;
			continue;
		}
		advisorID = stoi(input);
		preFaculty = getFacultyWithID(advisorID);
		if (preFaculty == NULL) {
			cout << "ERROR: faculty doesn't exist!" << endl;
			continue;
		}
		break;
	}

	student = new Student(name, major, level, ID, GPA, advisorID);//creates student with given attributes
	return student;
}

Faculty* Database::createFacultyFromInput() {
	Faculty* faculty;
	Faculty* preFaculty;
	Student* preStudent;
	string input;
	int ID;
	int adviseeID;
	string adAdvisee = "y";
	string name;
	string level;
	string department;
	DoublyLinkedList<int>* adviseeList = new DoublyLinkedList<int>();

	while (true) {
		cout << "Enter faculty member's ID (press q to quit) " << endl;
		getline(cin, input);
		cout << "\n";
		if (input == "q") {
			delete adviseeList;
			return NULL;
		}
		if (!isInterger(input)) {
			cout << "ERROR: please input a valid interger!" << endl;
			continue;
		}
		ID = stoi(input);
		preFaculty = getFacultyWithID(ID);
		if (preFaculty != NULL) {
			cout << "ERROR: Faculty member already exists." << endl;
			continue;
		}
		break;
	}
	cout << "Enter Faculty's name: " << endl;
	getline(cin, input);
	cout << "\n";
	name = input;

	cout << "Enter Faculty's department: " << endl;
	getline(cin, input);
	cout << "\n";
	department = input;

	cout << "Enter Faculty's level: " << endl;
	getline(cin, input);
	cout << "\n";
	level = input;

	while (adAdvisee == "y") {
		while (true) {
			cout << "Enter advisee's ID (press q to quit) " << endl;
			getline(cin, input);
			cout << "\n";
			if (input == "q") {
				break;
			}
			if (!isInterger(input)) {
				cout << "ERROR: Please provide an interger!" << endl;
				continue;
			}
			adviseeID = stoi(input);
			cout << "Advisee ID: " << adviseeID << endl;
			preStudent = getStudentWithID(adviseeID);
			if (preStudent == NULL) {
				cout << "ERROR: Student doesn't exist!" << endl;
				continue;
			}
			if (preStudent->m_advisorID != -1) {
				cout << preStudent->m_advisorID << endl;
				cout << "ERROR: Student already has an advisor!" << endl;
				continue;
			}
			if (preStudent->m_advisorID == -1) {
				adviseeList->insertBack(preStudent->m_ID);
				break;
			}
		}
		cout << "Would you like to add another advisee? (y/n)" << endl;//ability to add more than one advisee at a time
		getline(cin, adAdvisee);
		cout << "\n";
	}
	faculty = new Faculty(ID, name, level, department, adviseeList);//creates faculty with given attributes
	return faculty;
}

Student* Database::getStudentWithID(int ID) {
	Student studentSearch = Student(ID);
	return masterStudent->find(studentSearch);//returns the desired student or null
}

Faculty* Database::getFacultyWithID(int ID) {
	Faculty facultySearch = Faculty(ID);
	return masterFaculty->find(facultySearch);//returns the desired faculty or null
}