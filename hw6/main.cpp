#include <iostream>
#include <fstream>
#include <stdexcept>

#include "PersonHash.h"

using namespace std;

void check_input(int argc);
void addStudents(string fileName, PersonHash* students, ClassVec* classes);
void addTAs(string fileName, PersonHash* students, ClassVec* classes);
void get_commands(PersonHash* students, ClassVec* classes);

int main (int argc, char* argv[]) {
	PersonHash* students = new PersonHash(1500);
	ClassVec* classes = new ClassVec();
	
	check_input(argc);
	addStudents(argv[1], students, classes);
	addTAs(argv[2], students, classes);
	get_commands(students, classes);

	delete classes;
	delete students;
}

//checks the input to make sure the correct number of arguments is present
//if not, throws error with helpful message
void check_input(int argc) {
	if (argc != 3) {
		cout << "Incorrect numnber of arguments!" << endl;
		cout << "Correct usage: ./hw6degrees <student_file> <ta_file>";
		cout << endl;
		throw runtime_error("Incorrect usage");
	}
}

//parses file and extracts students and the classes they've taken. Removes 
//colons and then adds students and classes to the appropriate structures
void addStudents(string fileName, PersonHash* students, ClassVec* classes) {
	ifstream finput;
        finput.open(fileName.c_str());
	string name = "", class_taken = "", class_taken_fixed = "", str = "";
	unsigned long i;
	while (getline(finput, str)) {
	        for (i = 0; str[i] != ':'; i++) { 
			name += str[i];
		}
		i++;
		for (; i < str.length(); i++) {
			class_taken += str[i];
		}
		for (i = 0; i < class_taken.length();i++) {
			if (class_taken[i] != ':')
				class_taken_fixed += class_taken[i];
		}
		Person* p = students->getPointer(name);
		if (p == NULL) {
			p = new Person(name);
			students->add(p);
		}
		classes->add(p, class_taken_fixed);
		name = "";
		class_taken_fixed = "";
		class_taken = "";
		str = "";
	}
}

//traverses files and extracts names and the classes they have TAed. Removes
//colons and places the names and classes into the TA structures
void addTAs(string fileName, PersonHash* students, ClassVec* classes) {
	ifstream finput;
        finput.open(fileName.c_str());
	string name = "", class_tad = "", class_tad_fixed = "", str = "";
	unsigned long i;
	while (getline(finput, str)) {
	        for (i = 0; str[i] != ':'; i++) { 
			name += str[i];
		}
		i++;
		for (; i < str.length(); i++) {
			class_tad += str[i];
		}
		for (i = 0; i < class_tad.length();i++) {
			if (class_tad[i] != ':')
				class_tad_fixed += class_tad[i];
		}
		Person* p = students->getPointer(name);
		if (p == NULL) {
			p = new Person(name);
			students->add(p);
		} 
		Class cla = classes->get_students(class_tad_fixed);
		//following lines to deal with classes with TAs but no students
		if (cla.name == "NULL") {
			Person* p;
			p = new Person ("NULL");
			classes->add(p, class_tad_fixed);
			cla = classes->get_students(class_tad_fixed);
		}
		for (unsigned long i = 0; i < cla.people.size(); i++) {
			Person* stu = cla.people[i];
			p->addStudent(stu, class_tad_fixed);
		}
		name = "";
		class_tad = "";
		str = "";
		class_tad_fixed = "";
	}
}

//gets commands until end of file is reached. After it receives each command
//(and its appropriate params) it calls the necessary function
void get_commands(PersonHash* students, ClassVec* classes) {
	string command;
	cin >> command;
	while (!(cin.eof())) {
		if (command == "roster") {
			string class_to_roster;
			cin >> class_to_roster;
			classes->list_students(class_to_roster);
		} else if (command == "ls") {
			students->list_all();
		} else if (command == "lc") {
			classes->list_classes();
		} else if (command == "taed") {
			string name;
			cin >> name;
			students->list_classes_taed(name);
		} else if (command == "paths") {
			string person1, person2;
			cin >> person1 >> person2;
			students->findAllPaths(person1, person2);
		} else if (command == "shortestpath") {
			string person1, person2;
			cin >> person1 >> person2;
			students->findShortestPath(person1,person2);
		}
		cin >> command;
	}
}
