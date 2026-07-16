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

	try {
		ifstream studentFile(filename);
	}
	catch {
		cout << "Input file " + filename + " cannot be found!" << endl;
		return false;
	}

	LibStudent student = new LibStudent();

	string line;
	int stuCount = 0, pos;

	while (getline(studentFile, line)) {

		pos = line.find("=");
		if (pos == string::npos) continue; //skip empty lines

		switch (line.substr(0, pos-1)) { //check for attribute type, update attribute accordingly
		case "Student Id":
			student.id = line.substr(pos + 2);
			break;
		case "Name":
			student.name = line.substr(pos + 2);
			break;
		case "course":
			student.course = line.substr(pos + 2);
			break;
		case "Phone Number":
			student.number = line.substr(pos + 2);
			list.insert(student);
			stuCount++;
			break;
		default:
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