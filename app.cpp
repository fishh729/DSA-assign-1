#include	<iostream>
#include	<cstdlib>
#include	<cstdio>
#include    <fstream>
#include    <string>

#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;

bool ReadFile(string, List);					// NAT
bool DeleteRecord(List, char);					//SAM
bool Display(List, int, int);					//NAT
bool InsertBook(string, List);					//SAM
bool SearchStudent(List, charid, LibStudent&);	//NAT
bool computeAndDisplayStatistics(List);			//MARCUS
bool printStuWithSameBook(List, char);			//SAM
bool displayWarnedStudent(List, List, List);	//MARCUS
int menu();										//NAT


int main() {
	
	menu();

	cout << "\n\n";
	system("pause");
	return 0;
}

bool ReadFile(string filename, List* list) {

	ifstream studentFile(filename);

	LibStudent student;
	string line;
	int count, pos;
	bool checks[4] = {false, false, false, false};

	while (getline(studentFile, line)) {
		pos = line.find("=");
		if (pos == string::npos) continue;

		switch (line.substr(0, pos-1)) {
		case "Student Id":

			checks[0] = true;
			break;
		case "Name":

			checks[1] = true;
			break;
		case "course":

			checks[2] = true;
			break;
		case "Phone Number":

			checks[2] = true;
			break;
		default:
			cout << "Error parsing " << filename << ": bad attribute identifier";
		}

	}

}

int menu() {

	List* studentList = new List();

	ReadFile("student.txt", studentList);
	// do smth
}