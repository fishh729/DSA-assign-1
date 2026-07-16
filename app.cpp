#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>

#include    <sstream>

#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"


using namespace std;

string[] splitString(string, int)

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

	infile studentFile(filename);

	LibStudent student;
	string 

	while (!studentFile.eof()) {
		studentFile 
	}

}

int menu() {

	List* studentList = new List();

	ReadFile("student.txt", studentList);
	// do smth
}