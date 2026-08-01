#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>

#include	<cstring>
#include	<filesystem> //debug purposes

#include	"Node.h"
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

int splitString(const string&, string[], char, int);
Date extractDate(string);
int julianDay(Date);

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List *, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);

int menu();

int main() {
	
	menu();

	cout << "\n\n";
	system("pause");
	return 0;
}

int splitString(const string &line, string output[], char delim, int maxInfo)
{
	size_t start = 0, end;
	int count = 0;
	while (count < maxInfo && (end = line.find(delim, start)) != string::npos)
	{
		output[count++] = line.substr(start);
		start = end + 1;
	}
	if (count < maxInfo && start < line.length())
	{
		output[count++] = line.substr(start);
	}
	return count;
}

Date extractDate(string line) { // assumes '/' delimiter
	Date date;

	size_t d1 = line.find('/');
	size_t d2 = line.find('/', d1 + 1);
	date.day = stoi(line.substr(0, d1));
	date.month = stoi(line.substr(d1 + 1, d2 - d1 - 1));
	date.year = stoi(line.substr(d2 + 1));

	return date;
}

int julianDay(Date date) {
	int day = date.day, month = date.month, year = date.year;
	if (month <= 2) {
		year--;
	}
	int a = year / 100;
	int b = 2 - a + (a / 4);
	//julian day formula
	return static_cast<int>(365.25 * (year + 4716)) + static_cast<int>(30.6001 * (month + 1)) + day + b - 1524.5;
}

bool ReadFile(string filename, List* list) {

	//debug purposes
	//cout << "Current directory: " << std::filesystem::current_path() << endl;

	ifstream studentFile(filename);

	if(!studentFile.is_open()){
		cout << "Error parsing " << filename << ": file cannot be found" << endl;
		return false;
	}

	LibStudent student, stuCheck;

	string line, attr, value;
	int stuCount = 0;
	size_t pos;

	while (getline(studentFile, line)) {

		pos = line.find("=");
		if (pos == string::npos) continue; //skip empty lines

		attr = line.substr(0, pos-1);
		value = line.substr(pos + 2);

		if (attr == "Student Id")
		{
			strcpy(student.id, value.c_str());
		}
		else if (attr == "Name"){
			strcpy(student.name, value.c_str());
		}
		else if (attr == "course"){
			strcpy(student.course, value.c_str());
		}
		else if (attr == "Phone Number"){ //assumes order correct, phone number is the last attribute of each student object
			strcpy(student.phone_no, value.c_str());

			bool dupe = false;
			Node* cur = list->head;

			while (cur != NULL) {
				if (strcmp(cur->item.id, student.id) == 0) {
					cout << "Warning parsing " << filename << ": duplicate entry id found" << endl;
					dupe = true;
				}
				cur = cur->next;
			}
			if (!dupe) {
				list->insert(student);
				stuCount++;
			}
		}
		else {
			cout << "Error parsing " << filename << ": bad attribute identifier" << endl;
			return false;
		}
	}

	//debug purposes
	int count = 0;
	cout << "Loaded: " << endl;
	Node* cur = list->head;
	while (cur != NULL) {
		cout << cur->item.id << endl;
		count++;
		cur = cur->next;
	}
	cout << count << " students!" << endl;

	return true;
}

bool DeleteRecord(List* list, char* id) {
	return true;
}

bool SearchStudent(List *list, char *idPtr, LibStudent& student) {
	
	Node* cur = list->head;
	while (cur != NULL) {
		cout << cur->item.id << " : " << idPtr << endl;
		if (strcmp(cur->item.id, idPtr) == 0) {
			student = cur->item;
			return true;
		}
		cur = cur->next;
	}
	return false; //not found
}

bool InsertBook(string filename, List* list) {
	
	string studentID, authorsLine, borrowStr, dueStr;
	LibBook book;

	Date currentDate;
	currentDate.day = 29;
	currentDate.month = 3;
	currentDate.year = 2020;

	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "Error: Cannot open file " << filename << endl;
		return false;
	}

	while (inFile >> studentID >> authorsLine >> book.title >> book.publisher 
				>> book.ISBN >> book.yearPublished >> book.callNum 
				>> borrowStr >> dueStr) { //input to the Libbook 

		Node* cur = list->head;		//find the student id in the list
		bool found = false;
		while (cur != NULL) {
			if (strcmp(cur->item.id, studentID.c_str()) == 0) {
				found = true;
				break;
			}
			cur = cur->next;
		}
		if (!found) {
			cout << "Error: cannot find " << book.title << " book-related " << studentID << " student ID!" << endl;
			continue;
		}
		LibStudent& student = cur->item;	//get the student record

		//parse the author names and store it into the book.author array
		string authors[10];
		for (int i = 0; i < splitString(authorsLine, authors, '/', 10); i++) {
			book.author[i] = new char[authors[i].length() + 1];
			strcpy(book.author[i], authors[i].c_str());
		}

		//parse the borrow and due date and store it into the book.borrow and book.due
		book.borrow = extractDate(borrowStr);
		book.due = extractDate(dueStr);

		//calculate overdue fine using the julian day
		int dueJDN = julianDay(book.due);
		int currentJDN = julianDay(currentDate);
		
		int daysOverdue = 0;
		if (currentJDN > dueJDN) {
			daysOverdue = currentJDN - dueJDN;
		}
		book.fine = daysOverdue * 0.5; // RM 0.5 per day

		//insert the book into the student book record
		if (student.totalbook < 15) {

			student.book[student.totalbook] = book;
			student.totalbook++;
			student.calculateTotalFine();	//undergo the provide function
		}
		cout << "Loaded book " << book.title << endl;
	}

	inFile.close();
	return true;
}

bool Display(List* list, int source, int detail) { //make it look more beautiful

	Node* cur = list->head; //init traversal node to head of linked list

	while (cur != NULL) { //while not at tail of linked list
		cur->item.print(cout); //placeholder print student
		for (int i = 0; i < cur->item.totalbook; i++) {
			cur->item.book[i].print(cout); //placeholder print book
		}
		cur = cur->next; //go to next node
	}

	return true;
}

bool computeAndDisplayStatistics(List* list) {
	return true;
}

bool printStuWithSameBook(List* list, char* callNum) {

	if(list->head == NULL) {
		cout << "No Students found!";
		return false;
	}
	
	Node* cur = list->head;
	LibBook temp;
	int count = 0;

	strcpy(temp.callNum, callNum);

	while (cur != NULL) {
		for (int i = 0; i < cur->item.totalbook; i++) {

			if (cur->item.book[i].compareCallNum(temp)) {
				count++;
				break;
			}
		}
		cur = cur -> next;
	}

	if (count == 0) {
		cout << "No Books with " << callNum << " found!";
		return false;
	}

	cout << "There are " << count
     << (count == 1 ? " student that borrows" : " students that borrow")
     << " the book with call number " << callNum
     << " as shown below: \n\n";

	cur = list->head;

	while (cur != NULL) {
		for (int j = 0; j < cur->item.totalbook; j++) {

			if (cur->item.book[j].compareCallNum(temp)) {
				cout << "Student ID: " << cur->item.id << endl;
				cout << "Name: " << cur->item.name << endl;
				cout << "Course: " << cur->item.course << endl;
				cout << "Phone No.: " << cur->item.phone_no << endl;
				cout << "Borrow Date: ";
				cur->item.book[j].borrow.print(cout);
				cout << endl;
				cout << "Due Date: ";
				cur->item.book[j].due.print(cout);
				cout << endl << endl;
				break;
			}
		}
		cur = cur -> next;
	}
	return true;
}

bool displayWarnedStudent(List* list, List* type1, List* type2) {
	return true;
}

int menu()
{

	List *studentList = new List(); // main student list
	int sel;						// menu control

	// 3
	LibStudent searchedStu;
	char idQuery[10];
	char callNumQuery[20];

	while (true)
	{
		cout << endl << "Welcome to 89 Student Library Management System!\n\nPlease enter a selection: " << endl;

		cout << "(1) Read File" << endl;
		cout << "(2) Delete Record" << endl;
		cout << "(3) Search Student" << endl;
		cout << "(4) Insert Book" << endl;
		cout << "(5) Display Output" << endl;
		cout << "(6) Compute and Display Statistics" << endl;
		cout << "(7) Find Student with Same Book" << endl;
		cout << "(8) Display Warned Students" << endl;
		cout << "(9) Quit" << endl;

		cout << ">> ";
		cin >> sel;
		cout << endl;

		switch (sel)
		{
		case 1:
			ReadFile("student.txt", studentList);
			break;
		case 2:
			break;
		case 3:
			cout << "Please enter a student ID to search for: ";
			cin >> idQuery;
			if (SearchStudent(studentList, idQuery, searchedStu))
			{
				cout << idQuery << " found!" << endl << endl;
				searchedStu.print(cout);
				cout << "Books: " << endl;
				for (int i = 0; i < searchedStu.totalbook; i++) {
					searchedStu.book[i].print(cout);
				}
				cout << endl;
			}
			else
				cout << idQuery << " not found!" << endl;

			break;
		case 4:
			InsertBook("book.txt", studentList);
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			cout << "Enter Book's Call Number to search for: ";
			cin >> callNumQuery;
			printStuWithSameBook(studentList, callNumQuery);
			break;
		case 8:
			break;
		case 9:
			return 0;
			break;
		}
	}
}