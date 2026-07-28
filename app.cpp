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

void extractSpace(const string &lines, string info[], int maxInfo);
int julianDay(int day, int month, int year);

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List, int, int);
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

void extractSpace(const string &lines, string info[], int maxInfo)
{
	size_t start = 0;
	size_t end;
	int count = 0;
	while (count < maxInfo && (end = lines.find(' ', start)) != string::npos)
	{
		info[count++] = lines.substr(start);
		start = end + 1;
	}
	if (count < maxInfo && start < lines.length())
	{
		info[count++] = lines.substr(start);
	}
}

int julianDay(int day, int month, int year) {
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
	int stuCount = 0, pos;

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
		else if (attr == "Phone Number"){
			strcpy(student.phone_no, value.c_str());

			bool dupeID = false;
			Node* cur = list->head;

			while (cur != NULL) {
				if (cur->item.id == student.id) {
					cout << "Warning parsing " << filename << ": duplicate entry id found" << endl;
					dupeID = true;
				}
				cur = cur->next;
			}
			if (!dupeID) {
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
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "Error: Cannot open file " << filename << endl;
		return false;
	}

	string lines;
	bool failInserted = false;

	while (!inFile.eof()) {
		string studentID, authorsLine, borrowStr, dueStr;
		
		//input to the Libbook 
		LibBook book;
		inFile >> studentID >> authorsLine >> book.title >> book.publisher >> book.ISBN >> book.yearPublished >> book.callNum >> borrowStr >> dueStr;

		Node* cur;		//find the student id in the list
		cur = list->head;
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

		//parse the author name and store it into the book.author array
		int authorCount = 0;
		size_t startPos = 0;
		while (authorCount < 10) {
			size_t slash = authorsLine.find('/', startPos);
			string authorName;
			if (slash == string::npos) {
				authorName = authorsLine.substr(startPos);
				startPos = string::npos;
			}
			else {
				authorName = authorsLine.substr(startPos, slash - startPos);
				startPos = slash + 1;
			}
			if (authorName.empty()) break;
			book.author[authorCount] = new char[authorName.length() + 1];
			strcpy(book.author[authorCount], authorName.c_str());
			authorCount++;
			if (startPos == string::npos) break;
		}

		//parse the borrow and due date and store it into the book.borrow and book.due
		size_t d1 = borrowStr.find('/');
		size_t d2 = borrowStr.find('/', d1 + 1);
		int bd = stoi(borrowStr.substr(0, d1));
		int bm = stoi(borrowStr.substr(d1 + 1, d2 - d1 - 1));
		int by = stoi(borrowStr.substr(d2 + 1));
		book.borrow.day = bd;
		book.borrow.month = bm;
		book.borrow.year = by;


		d1 = dueStr.find('/');
		d2 = dueStr.find('/', d1 + 1);
		cout << dueStr.substr(0, d1) << " : " << dueStr.substr(d1 + 1, d2 - d1 - 1) << " : " << dueStr.substr(d2 + 1, d2 + 1) << endl;
		int dd = stoi(dueStr.substr(0, d1));
		int dm = stoi(dueStr.substr(d1 + 1, d2 - d1 - 1));
		int dy = stoi(dueStr.substr(d2 + 1));
		book.due.day = dd;
		book.due.month = dm;
		book.due.year = dy;

		//calculate overdue fine using the julian day
		Date currentDate;
		currentDate.day = 29;
		currentDate.month = 3;
		currentDate.year = 2020;

		int dueJDN = julianDay(book.due.day, book.due.month, book.due.year);
		int currentJDN = julianDay(currentDate.day, currentDate.month, currentDate.year);
		
		int daysOverdue = 0;
		if (currentJDN > dueJDN) {
			daysOverdue = currentJDN - dueJDN;
		}
		book.fine = daysOverdue * 0.5; // RM 0.5 per day


		//insert the book into the student book record
		LibStudent& student = cur->item;	//get the student record
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

int menu()
{

	List *studentList = new List(); // main student list
	int sel;						// menu control

	// 3
	LibStudent searchedStu;
	char idQuery[10];
	// char* idPtr = &idQuery;

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
			break;
		case 8:
			break;
		case 9:
			return 0;
			break;
		}
	}
}