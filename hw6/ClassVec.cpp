#include "ClassVec.h"
using namespace std;
#include <vector>
#include<iostream>

//no constructor needed
ClassVec::ClassVec() {
}

//destructor
ClassVec::~ClassVec() {
	for (unsigned long i = 0; i < classes.size(); i++) {
		for (unsigned long j = 0; j < classes[i].people.size(); j++) {
			if (classes[i].people[j]->name == "NULL") {
				delete classes[i].people[j];
			}
		}
	}
}

//adds people to a class by their pointer. Makes a new class if it needs to.
void ClassVec::add(Person* p, string class_name) {
	for (unsigned long i = 0; i < classes.size(); i++) {
		if (classes[i].name == class_name) {
			classes[i].people.push_back(p);
			return;
		}
	}
	Class c;
	c.name = class_name;
	classes.push_back(c);
	classes[classes.size()-1].people.push_back(p);
}

//overloaded add function to add a class with no students in it. It adds using
//only the class name
void ClassVec::add(string class_name) {
	for (unsigned long i = 0; i < classes.size(); i++) {
		if (classes[i].name == class_name) {
			return;
		}
	}
	Class c;
	c.name = class_name;
	classes.push_back(c);
}

//goes through a class with the given (string) name and prints out everyone that
//is in the class. Ignores students with name "NULL" because those are place-
//holders for classes with no students.
void ClassVec::list_students(string class_name) {
	for (unsigned long i = 0; i < classes.size(); i++) {
		if (classes[i].name == class_name) {
			unsigned long j;
			for (j = 0; j < classes[i].people.size(); j++) {
				if (classes[i].people[j]->name != "NULL") {
					cout << classes[i].people[j]->name;
					cout << endl;
				}
			}
			return;
		}
	}
	cout << "Course not found" << endl;
}

//returns the entire class given the class name. If no such name exists it 
//creates a class named "NULL" so that it has something to return
Class ClassVec::get_students(string class_name) {
	for (unsigned long i = 0; i < classes.size(); i++) {
		if (classes[i].name == class_name) {
			return classes[i];
		}
	}
	Class c;
	c.name = "NULL";
	return c;
}

//lists all the classes, for lc, unless they are a filler with name "NULL"
void ClassVec::list_classes() {
	for (unsigned long i = 0; i < classes.size(); i++) {
		if (classes[i].name != "NULL") {
			cout << classes[i].name << endl;
		}
	}
}
