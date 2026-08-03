#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

#include <iomanip>
#include <cstring>

#include "Node.h"
#include "List.h"
#include "LibStudent.h"
#include "LibBook.h"

using namespace std;

int splitString(const string &, string[], char, int);
Date extractDate(string);
int julianDay(Date);

bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
bool Display(List*, int, int);
bool InsertBook(string, List*);
bool SearchStudent(List*, char* id, LibStudent&);
bool computeAndDisplayStatistics(List*);
bool printStuWithSameBook(List*, char*);
bool displayWarnedStudent(List*, List*, List*);

int menu();

<<<<<<< Updated upstream
int main()
{
=======
int main() {
>>>>>>> Stashed changes

	menu();

	cout << "\n\n";
	system("pause");
	return 0;
}

<<<<<<< Updated upstream
int splitString(const string &line, string output[], char delim, int maxInfo) // split line into string array using delimiter
=======
int splitString(const string& line, string output[], char delim, int maxInfo)
>>>>>>> Stashed changes
{
	size_t start = 0, end = 0;
	int count = 0;
<<<<<<< Updated upstream
	// split when delimiter exists, store value before the delimiter and move past the delimiter
	while (count < maxInfo && (end = line.find(delim, start)) != std::string::npos)
=======

	while (count < maxInfo && (end = line.find(delim, start)) != string::npos)
>>>>>>> Stashed changes
	{
		output[count++] = line.substr(start, end - start);
		start = end + 1;
	}
<<<<<<< Updated upstream
	if (count < maxInfo && start <= line.size())
	{ // store remaining value
=======

	if (count < maxInfo && start < line.length())
	{
>>>>>>> Stashed changes
		output[count++] = line.substr(start);
	}

	return count;
}

Date extractDate(string line)
{ // assumes '/' delimiter,
	Date date;

	size_t d1 = line.find('/');
	size_t d2 = line.find('/', d1 + 1);
	try
	{ // extract day, month, year integer left, inside, and right of delimiter respectively
		date.day = stoi(line.substr(0, d1));
		date.month = stoi(line.substr(d1 + 1, d2 - d1 - 1));
		date.year = stoi(line.substr(d2 + 1));
	}
	catch (invalid_argument e)
	{ // in case stoi fails due to invalid characters
		cout << "Error: invalid date format for " << line << endl;
	}

	return date;
}

int julianDay(Date date)
{
	int day = date.day, month = date.month, year = date.year;
	// years start on the 2nd month
	if (month <= 2)
	{
		year--;
	}
	// julian day formula
	int a = year / 100;
	int b = 2 - a + (a / 4);
	return static_cast<int>(365.25 * (year + 4716)) + static_cast<int>(30.6001 * (month + 1)) + day + b - 1524.5;
}

bool ReadFile(string filename, List *list)
{

	// open file
	ifstream studentFile(filename);
<<<<<<< Updated upstream
	if (!studentFile.is_open())
	{
		cout << "Warning parsing " << filename << ": file cannot be opened" << endl;
=======

	if (!studentFile.is_open()) {
		cout << "Error parsing " << filename << ": file cannot be found" << endl;
>>>>>>> Stashed changes
		return false;
	}

	LibStudent student;
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
	string line, attr, value;
	int stuCount = 0;
	size_t pos;

	// parse each line of the student file
	while (getline(studentFile, line))
	{

		pos = line.find("=");
		if (pos == string::npos)
			continue; // skip empty lines or bad lines without a '='

<<<<<<< Updated upstream
		// seperate line into before and after '='
=======
>>>>>>> Stashed changes
		attr = line.substr(0, pos - 1);
		value = line.substr(pos + 2);

		if (value.empty())
			cout << "Warning: empty " << endl;

		// copy parsed values into LibStudent instance
		if (attr == "Student Id")
		{
			strcpy(student.id, value.c_str());
		}
<<<<<<< Updated upstream
		else if (attr == "Name")
		{
			strcpy(student.name, value.c_str());
		}
		else if (attr == "course")
		{
			strcpy(student.course, value.c_str());
		}
		else if (attr == "Phone Number")
		{ // assumes order correct: phone number last attr of each student obj
=======
		else if (attr == "Name") {
			strcpy(student.name, value.c_str());
		}
		else if (attr == "course") {
			strcpy(student.course, value.c_str());
		}
		else if (attr == "Phone Number") { //assumes order correct, phone number is the last attribute of each student object
>>>>>>> Stashed changes
			strcpy(student.phone_no, value.c_str());

			bool dupe = false;
			Node *cur = list->head;
			// check for duplicate student by id, assuming all id are unique
			while (cur != NULL)
			{
				if (strcmp(cur->item.id, student.id) == 0)
				{
					cout << "Warning parsing " << filename << ": duplicate entry id found" << endl;
					dupe = true;
				}
				cur = cur->next;
			}
			// insert student if duplicate not found
			if (!dupe)
			{
				list->insert(student);
				stuCount++;
			}
		}
		else
		{
			cout << "Error parsing " << filename << ": bad attribute identifier" << endl;
<<<<<<< Updated upstream
=======
			studentFile.close();
			return false;
>>>>>>> Stashed changes
		}
	}

	// debug purposes ##REMOVE##
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
<<<<<<< Updated upstream
	//
=======

	studentFile.close();
>>>>>>> Stashed changes
	return true;
}

bool DeleteRecord(List *list, char *id)
{
	return true;
}

<<<<<<< Updated upstream
bool SearchStudent(List *list, char *id, LibStudent &student)
{
	Node *cur = list->head;

	while (cur != NULL)
	{
		cout << cur->item.id << " : " << id << endl; // debug, REMOVE
		if (strcmp(cur->item.id, id) == 0)
		{						 // check if given id is
			student = cur->item; // update referenced LibStudent
=======
bool SearchStudent(List* list, char* idPtr, LibStudent& student) {

	Node* cur = list->head;
	while (cur != NULL) {
		cout << cur->item.id << " : " << idPtr << endl;
		if (strcmp(cur->item.id, idPtr) == 0) {
			student = cur->item;
>>>>>>> Stashed changes
			return true;
		}
		cur = cur->next;
	}
	return false; // not found
}

<<<<<<< Updated upstream
bool InsertBook(string filename, List *list)
{
=======
bool InsertBook(string filename, List* list) {
>>>>>>> Stashed changes

	string studentID, authorsLine, borrowStr, dueStr;
	LibBook book;

	Date currentDate;
	currentDate.day = 29;
	currentDate.month = 3;
	currentDate.year = 2020;

	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		cout << "Error: Cannot open file " << filename << endl;
		return false;
	}

<<<<<<< Updated upstream
	while (inFile >> studentID >> authorsLine >> book.title >> book.publisher >> book.ISBN >> book.yearPublished >> book.callNum >> borrowStr >> dueStr)
	{ // input to the Libbook
=======
	while (inFile >> studentID >> authorsLine >> book.title >> book.publisher
		>> book.ISBN >> book.yearPublished >> book.callNum
		>> borrowStr >> dueStr) { //input to the Libbook 
>>>>>>> Stashed changes

		Node *cur = list->head; // find the student id in the list
		bool found = false;
		while (cur != NULL)
		{
			if (strcmp(cur->item.id, studentID.c_str()) == 0)
			{
				found = true;
				break;
			}
			cur = cur->next;
		}
		if (!found)
		{
			cout << "Error: cannot find " << book.title << " book-related " << studentID << " student ID!" << endl;
			continue;
		}
		LibStudent &student = cur->item; // get the student record

		// parse the author names and store it into the book.author array
		string authors[10];
		for (int i = 0; i < splitString(authorsLine, authors, '/', 10); i++)
		{
			book.author[i] = new char[authors[i].length() + 1];
			strcpy(book.author[i], authors[i].c_str());
		}

		// parse the borrow and due date and store it into the book.borrow and book.due
		book.borrow = extractDate(borrowStr);
		book.due = extractDate(dueStr);

		// calculate overdue fine using the julian day
		int dueJDN = julianDay(book.due);
		int currentJDN = julianDay(currentDate);

		int daysOverdue = 0;
		if (currentJDN > dueJDN)
		{
			daysOverdue = currentJDN - dueJDN;
		}
		book.fine = daysOverdue * 0.5; // RM 0.5 per day

		// insert the book into the student book record
		if (student.totalbook < 15)
		{

			student.book[student.totalbook] = book;
			student.totalbook++;
			student.calculateTotalFine(); // undergo the provide function
		}
		cout << "Loaded book " << book.title << endl;
	}

	inFile.close();
	return true;
}

bool Display(List *list, int source, int detail)
{
	if (list == NULL || list->empty())
	{ // check empty list
		cout << "Error: List is empty!" << endl;
		return false;
	}
	ostream *out = &cout; // for screen output if(source ==2)
	ofstream fileOut;	  // for file output (source==1)

	if (source == 1)
	{
		string filename;
		if (detail == 1)
		{
			filename = "student_booklist.txt";
		}
<<<<<<< Updated upstream
		else if (detail == 2)
		{
=======
		else if (detail == 2) {
>>>>>>> Stashed changes
			filename = "student_info.txt";
		}
		else
		{
			cout << "Error: Invalid detail option!" << endl;
			return false;
		}
		fileOut.open(filename);
		if (!fileOut.is_open())
		{
			cout << "Error: Cannot create file!" << endl;
			return false;
		}
		out = &fileOut;
	}
	else if (source != 2)
	{
		cout << "Error: Invalid source option!" << endl;
		return false;
	}

	Node *cur = list->head; // start from first node
	int studentNo = 1;		// student number

	while (cur != NULL)
	{ // loop until end of list
		LibStudent &stu = cur->item;

		*out << "STUDENT " << studentNo << endl;
		*out << "Name:  " << stu.name << endl;
		*out << "Id: " << stu.id << endl;
		*out << "Course: " << stu.course << endl;
		*out << "Phone No: " << stu.phone_no << endl;
		*out << "Total Fine: RM" << fixed << setprecision(2) << stu.total_fine << endl;

		if (detail == 1)
		{
			*out << "\nBOOK LIST:\n\n";
			if (stu.totalbook == 0)
			{
				*out << "No books borrowed.\n";
			}
			else
			{
				for (int i = 0; i < stu.totalbook; i++)
				{
					LibBook &book = stu.book[i];
					*out << "Book " << (i + 1) << endl;
					*out << "Title: " << book.title << endl;
					*out << "Author: ";
					bool first = true;
					for (int a = 0; a < 10; a++)
					{
						if (book.author[a] != NULL && strlen(book.author[a]) > 0)
						{
							if (!first)
							{
								*out << "     ";
							}
							*out << book.author[a];
							first = false;
						}
					}
					*out << endl;

					*out << "Publisher: " << book.publisher << endl;
					*out << "Year Published: " << book.yearPublished << endl;
					*out << "ISBN: " << book.ISBN << endl;
					*out << "Call Number: " << book.callNum << endl;
					*out << "Borrow Date: " << book.borrow.day << "/" << book.borrow.month << "/" << book.borrow.year << endl;
					*out << "Due Date: " << book.due.day << "/" << book.due.month << "/" << book.due.year << endl;
					*out << "Fine: RM" << fixed << setprecision(2) << book.fine << endl;
					*out << endl;
				}
			}
		}

		*out << "*****************************************************************************\n"; // separator
		cur = cur->next;
		studentNo++;
	}

	if (source == 1)
	{
		fileOut.close();
		cout << "Successfully display output to " << ((detail == 1) ? "student_booklist.txt" : "student_info.txt") << endl;
	}
	else
	{
		cout << "Successfully display output" << endl;
	}

	return true;
}

bool computeAndDisplayStatistics(List *list)
{
	if (list == NULL || list->empty())
	{
		cout << "Error: List is empty!" << endl;
		return false;
	}
	const int NUM_COURSES = 5;
	string courses[] = { "CS", "IA", "IB", "CN", "CT" };

	int numStudents[NUM_COURSES] = { 0 };
	int totalBooks[NUM_COURSES] = { 0 };
	int overdueBooks[NUM_COURSES] = { 0 };
	double totalFine[NUM_COURSES] = { 0.0 };

	Node* cur = list->head;
	
	while (cur != NULL) {
		LibStudent& stu = cur->item;
		int courseIndex = -1;
		for (int i = 0; i < NUM_COURSES; i++) {
			if (strcmp(stu.course, courses[i]) == 0) {
				courseIndex = i;
				break;
			}
		}
		if (courseIndex == -1) { // skip courses not in the list
			cur = cur->next;
			continue;
		}
		numStudents[courseIndex]++;
		totalBooks[courseIndex] += stu.totalbook;
		for (int j = 0; j < stu.totalbook; j++) {//count overdue books and fine
			if (stu.book[j].fine > 0) {
				overdueBooks[courseIndex]++;
				totalFine[courseIndex] += stu.total_fine;
				break;
			}
		}
		cur = cur->next;
	}
	cout << "\n";
	cout << "Course\tNumber of Students\tTotal Books Borrowed\tTotal Overdue Books\tTotal Overdue Fine (RM)" << endl;
	for (int i = 0; i < NUM_COURSES; i++) {
		cout << courses[i] << "\t" << numStudents[i] << "\t\t\t" << totalBooks[i] << "\t\t\t" << overdueBooks[i] << "\t\t\t" << fixed << setprecision(2) << totalFine[i] << endl;
	}
	cout << endl;
	return true;
}

bool printStuWithSameBook(List *list, char *callNum)
{

<<<<<<< Updated upstream
	if (list->head == NULL)
	{
=======
	if (list->head == NULL) {
>>>>>>> Stashed changes
		cout << "No Students found!";
		return false;
	}

<<<<<<< Updated upstream
	Node *cur = list->head;
=======
	Node* cur = list->head;
>>>>>>> Stashed changes
	LibBook temp;
	int count = 0;

	strcpy(temp.callNum, callNum);

	while (cur != NULL)
	{
		for (int i = 0; i < cur->item.totalbook; i++)
		{

			if (cur->item.book[i].compareCallNum(temp))
			{
				count++;
				break;
			}
		}
		cur = cur->next;
	}

	if (count == 0)
	{
		cout << "No Books with " << callNum << " found!";
		return false;
	}

	cout << "There are " << count
<<<<<<< Updated upstream
		 << (count == 1 ? " student that borrows" : " students that borrow")
		 << " the book with call number " << callNum
		 << " as shown below: \n\n";
=======
		<< (count == 1 ? " student that borrows" : " students that borrow")
		<< " the book with call number " << callNum
		<< " as shown below: \n\n";
>>>>>>> Stashed changes

	cur = list->head;

	while (cur != NULL)
	{
		for (int j = 0; j < cur->item.totalbook; j++)
		{

			if (cur->item.book[j].compareCallNum(temp))
			{
				cout << "Student ID: " << cur->item.id << endl;
				cout << "Name: " << cur->item.name << endl;
				cout << "Course: " << cur->item.course << endl;
				cout << "Phone No.: " << cur->item.phone_no << endl;
				cout << "Borrow Date: ";
				cur->item.book[j].borrow.print(cout);
				cout << endl;
				cout << "Due Date: ";
				cur->item.book[j].due.print(cout);
				cout << endl
					 << endl;
				break;
			}
		}
		cur = cur->next;
	}
	return true;
}

<<<<<<< Updated upstream
bool displayWarnedStudent(List *list, List *type1, List *type2)
{
=======
bool displayWarnedStudent(List* list, List* type1, List* type2) {

	if (list->head == NULL) {
		cout << "No Students found!";
		return false;
	}

	Node* cur = list->head;
	int count = 0, overdue = 0;

	while (cur != NULL) {
		for (int i = 0; i < cur->item.totalbook; i++) {
			if (cur->item.total_fine / 0.5 >= 10)
				count++;
			else if (cur->item.book->fine > 0)
				overdue++;
			continue;
		}
		if (count >= 2) {
			type1->insert(cur->item);
		}
		if (cur->item.total_fine >= 50 && overdue == cur->item.totalbook) {
			type2->insert(cur->item);
		}
		cur = cur->next;
	}

	cur = type1->head;

	if (type1->size() == 0) {
		cout << "No Students Found in Type 1." << endl;
		return false;
	}
	else {
		cout << "List of Warned Students (>= 2 books overdue for >= 10 days): \n\n";

		while (cur != NULL) {
			cout << "Student Name: " << cur->item.name << endl;
			cout << "Student ID: " << cur->item.id << endl;
			cout << "Course: " << cur->item.course << endl << endl;
			for (int j = 0; j < cur->item.totalbook; j++) {
				cout << "Book " << j + 1 << endl;
				cur->item.book[j].print(cout);
			}
			cur = cur->next;
		}
	}

	cur = type2->head;

	if (type2->size() == 0) {
		cout << "No Students Found in Type 2." << endl;
		return false;
	}
	else {
		cout << "List of Warned Students (Every book is due and totalfine >= 50): \n\n";

		while (cur != NULL) {
			cout << "Student Name: " << cur->item.name << endl;
			cout << "Student ID: " << cur->item.id << endl;
			cout << "Course: " << cur->item.course << endl << endl;
			for (int j = 0; j < cur->item.totalbook; j++) {
				cout << "Book " << j + 1 << endl;
				cur->item.book[j].print(cout);
			}
			cur = cur->next;
		}
	}
>>>>>>> Stashed changes
	return true;
}

int menu()
{
<<<<<<< Updated upstream
	List *studentList = new List(); // main student list
=======

	List* studentList = new List(); // main student list
>>>>>>> Stashed changes
	int sel;						// menu control

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
			LibStudent searchedStu;
			char idQuery[10];
			cout << "Please enter a student ID to search for: ";
			cin >> idQuery;
			if (SearchStudent(studentList, idQuery, searchedStu))
			{
				cout << idQuery << " found!" << endl
					 << endl;
				searchedStu.print(cout);
				cout << "Books: " << endl;
				for (int i = 0; i < searchedStu.totalbook; i++)
				{
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
			int source, detail;
			cout << "DISPLAY OUTPUT\n\n";
			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;
			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;
			Display(studentList, source, detail);
			break;
		case 6:
			computeAndDisplayStatistics(studentList);
			break;
		case 7:
			char callNumQuery[20];
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