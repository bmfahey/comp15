#include <vector>
#include <iostream>
#ifndef CLASSVEC_H
#define CLASSVEC_H
#include "Person.h"
#endif

//The ClassVec class makes a vector of Class structs and performs operations on
//it such as adding a new class, adding a person to a class, and listing all the
//possible classes.

using namespace std;

struct Class {
	string name;
	vector<Person*> people;
};

class ClassVec {
	public:
		ClassVec();
		~ClassVec();
		void add(Person* p, string class_name);
		void add(string class_name);
		void list_students(string class_name);
		Class get_students(string class_name);
		void list_classes();
		
	private:
		vector<Class> classes;
};
