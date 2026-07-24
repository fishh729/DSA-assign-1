#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

#include <cstring>
#include <filesystem> //debug purposes

#include "Node.h"
#include "List.h"
#include "LibStudent.h"
#include "LibBook.h"

using namespace std;

void extractSpace(const string &lines, string info[], int maxInfo);

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
bool computeAndDisplayStatistics(List *);
bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();

int main()
{

	menu();

	cout << "\n\n";
	system("pause");
	return 0;
}

void extractSpace(const string &lines, string info[], int maxInfo)
{
	size_s start = 0;
	size_s end;
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

bool ReadFile(string filename, List *list)
{

	// debug purposes
	// cout << "Current directory: " << std::filesystem::current_path() << endl;

	ifstream studentFile(filename);

	if (!studentFile.is_open())
	{
		cout << "Error parsing " << filename << ": file cannot be found" << endl;
		return false;
	}

	LibStudent student, stuCheck;

	string line, attr, value;
	int stuCount = 0, pos;

	while (getline(studentFile, line))
	{

		pos = line.find("=");
		if (pos == string::npos)
			continue; // skip empty lines

		attr = line.substr(0, pos - 1);
		value = line.substr(pos + 2);

		if (attr == "Student Id")
		{
			strcpy(student.id, value.c_str());
		}
		else if (attr == "Name")
		{
			strcpy(student.name, value.c_str());
		}
		else if (attr == "course")
		{
			strcpy(student.course, value.c_str());
		}
		else if (attr == "Phone Number")
		{
			strcpy(student.phone_no, value.c_str());

			bool dupeID = false;
			Node *cur = list->head;

			while (cur != NULL)
			{
				if (cur->item.id == student.id)
				{
					cout << "Warning parsing " << filename << ": duplicate entry id found" << endl;
					dupeID = true;
				}
				cur = cur->next;
			}
			if (!dupeID)
			{
				list->insert(student);
				stuCount++;
			}
		}
		else
		{
			cout << "Error parsing " << filename << ": bad attribute identifier" << endl;
			return false;
		}
	}

	// debug purposes
	int count = 0;
	cout << "Loaded: " << endl;
	Node *cur = list->head;
	while (cur != NULL)
	{
		cout << cur->item.id << endl;
		count++;
		cur = cur->next;
	}
	cout << count << " students!" << endl;

	return true;
}

bool SearchStudent(List *list, char *idPtr, LibStudent &student)
{

	Node *cur = list->head;
	while (cur != NULL)
	{
		cout << cur->item.id << " : " << *idPtr << endl;
		if (cur->item.id == idPtr)
		{
			student = cur->item;
			return true;
		}
		cur = cur->next;
	}
	return false; // not found
}

bool InsertBook(string filename, List *list)
{
	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Error: Cannot open file " << filename << endl;
		return false;
	}

	string lines;
	bool failInserted = false;

	Date currentDate;
	currentDate.day = 29;
	currentDate.month = 3;
	currentDate.year = 2020;

	while (getline(infile, lines))
	{
		if (lines.empty())
		{ // ignored empty lines
			continue;
		}

		string stdID = lines; // get student id

		if (!getline(infile, lines))
		{
			break;
		}

		string authorsLine = lines; // get author name

		if (!getline(infile, lines))
		{
			break;
		}

		string title = lines; // get title

		if (!getline(infile, lines))
		{
			break;
		}

		string Info[6];				  // the array for the storing of the the data
		extractSpace(lines, Info, 6); // use function to seperate the data by using space

		string publisher = Info[0];
		string ISBN = Info[1];
		int yearPublished = stoi(Info[2]);
		string callNum = Info[3];	// insert the data into its own variable
		string borrowStr = Info[4]; // for the parsing date
		string duesStr = Info[5];

		// input to the Libbook
		LibBook book;
		strcpy(book.title, title.c_str());
		strcpy(book.publisher, publisher.c_str());
		strcpy(book.ISBN, ISBN.c_str());
		strcpy(book.callNum, callNum.c_str());
		book.yearPublished = yearPublished;

		Node *cur; // find the student id in the list
		bool found = false;
		while (cur != NULL)
		{
			if (cur->item.id == studentID)
			{
				found = true;
				break;
			}
			cur = cur->next;
		}
		if (!found)
		{
			continue;
		}

		// parse the author name and store it into the book.author array
		int authorCount = 0;
		size_t startPos = 0;
		while (authorCount < 10)
		{
			size_t slash = authorsLine.find('/', startPos);
			string authorName;
			if (slash == string::npos)
			{
				authorName = authorsLine.substr(startPos);
				startPos = string::npos;
			}
			else
			{
				authorName = authorsLine.substr(startPos, slash - startPos);
				startPos = slash + 1;
			}
			if (authorName.empty())
				break;
			book.author[authorCount] = new char[authorName.length() + 1];
			strcpy(book.author[authorCount], authorName.c_str());
			authorCount++;
			if (startPos == string::npos)
				break;
		}

		// parse the borrow and due date and store it into the book.borrow and book.due
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
		int dd = stoi(dueStr.substr(0, d1));
		int dm = stoi(dueStr.substr(d1 + 1, d2 - d1 - 1));
		int dy = stoi(dueStr.substr(d2, d2 + 1));
		book.due.day = dd;
		book.due.month = dm;
		book.due.year = dy;
	}
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
		cout << endl
			 << "Welcome to 89 Student Library Management System!\n\nPlease enter a selection: " << endl;

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
				cout << idQuery << " found!" << endl
					 << endl;
				searchedStu.print(cout);
			}
			else
				cout << idQuery << " not found!" << endl;

			break;
		case 4:
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
			break;
		}
	}

	return 0;
}