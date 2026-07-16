#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>

#include	<cstring>

#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

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

bool ReadFile(string filename, List* list) {

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

			for (int i = 0; i < stuCount + 1; i++)
			{
				list->get(i, stuCheck);
				if (stuCheck.id == student.id) //assume all id are unique
				{
					cout << "Warning parsing " << filename << ": duplicate entry id found" << endl;
					continue;
				}
			}
			list->insert(student);
			stuCount++;
		}
		else {
			cout << "Error parsing " << filename << ": bad attribute identifier" << endl;
			return false;
		}
	}

	return true;
}

int menu() {

	List* studentList = new List();

	ReadFile("student.txt", studentList);
	// do smth
}