#include<stdexcept>
#include "Person.h"
using namespace std;

//default constructor - sets name to empty string
Person::Person() {
	name = "";
	next = NULL;
	num_students = 0;
	marked = false;
	distance = -1;
	path = NULL;
	pathClass = "";
}

//overloaded constructor, sets name to given string s
Person::Person(string n) {
	name = n;
	next = NULL;
	num_students = 0;
	marked = false;
	distance = -1;
	path = NULL;
	pathClass = "";
}

//destructor - deletes all students this person has TAed, sets other variables
//to default values
Person::~Person() {
	next = NULL;
	name = "";
	num_students = 0;
	path = NULL;
	pathClass = "";
}

//adds a person p to the NodeVector of the person who's instance this was called
//on. The Pointer Node has a value of ta_class for its string class variable.
void Person::addStudent(Person* p, string ta_class) {
	Pointer_Node node;
	node.pers = p;
	node.ta_class = ta_class;
	students.add(node);
}

//links this person to the next person in the linked list
void Person::linkNext (Person p) {
	next = &p;
}

//lists the students this person has taed by calling a function within the Node-
//Vector
void Person::list_students_taed() {
	students.list_students();
}

//marks a person
void Person::mark() {
	marked = true;
}

//unmarks a person
void Person::unmark() {
	marked = false;
}

//returns true if this person is marked and false if they are not
bool Person::isMarked() {
	return marked;
}

