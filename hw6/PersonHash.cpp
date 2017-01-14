#include "hashfunc.h"
#include "PersonHash.h"
#include <vector>
#include <queue>

//default constructor - sets the table to a size of 20
PersonHash::PersonHash() {
	size = INITIAL_SIZE;
	arr = new Person*[INITIAL_SIZE];
	for (int i = 0; i < size; i ++) {
		arr[i] = NULL;
	}
}

//overloaded constructor - sets the table to a size of the parameter s
PersonHash::PersonHash(int s) {
	size = s;
	arr = new Person*[size];
	for (int i = 0; i < size; i++) {
		arr[i] = NULL;
	}
}

//destructor -> goes through and deletes all people in the hash table
PersonHash::~PersonHash() {
	for (int i = 0; i < size; i++) {
		Person* temp = arr[i];
		Person* next;
		while (temp != NULL) {
			next = temp->next;
			delete temp;
			temp = next;
		}
	}
	delete[] arr;
}

//overloaded bracket operator - returns pointer to person at given index
Person* PersonHash::operator[](int index) const {
	return arr[index];
}

//adds the person pointed to by parameter p to the hash table using their name
//as the value to pass to the hash function
void PersonHash::add(Person* p) {
	int key = (hash_string(p->name))%size;
	if (arr[key] == NULL) {
		arr[key] = p;
	}
	else {
		Person* temp = arr[key];
		while (temp->next != NULL) {
			if (temp != p) 
				temp = temp->next;
			else
				return;
		}
		temp->next = p;
	}
}

//returns the pointer to the given student, if they exist. If they don't, the
//NULL pointer is returned
Person* PersonHash::getPointer(string name) {
	int key = (hash_string(name))%size;
	if (arr[key] == NULL) {
		return NULL;
	}
	Person* temp = arr[key];
	while (temp != NULL) {
		if (temp->name == name) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

//lists all students to standard output, as long as they are legitimate (i.e.
//their name is not "NULL")
void PersonHash::list_all() {
	for (int i = 0; i < size; i++) {
		Person* temp = arr[i];
		while (temp != NULL) {
			if (temp->name != "NULL") {
				cout << temp->name << endl;
			}
				temp = temp->next;
		}
	}
}

//lists all the classes taed by calling the "list_students_taed" function on
//the person, once they have been found given their name as a parameter
void PersonHash::list_classes_taed(string name) {
	int key = (hash_string(name))%size;
	Person* temp = arr[key];
	while (temp != NULL) {
		if (temp->name == name) {
			temp->list_students_taed();
			return;
		}
		temp = temp->next;
	}
	cout << "Student not found" << endl;
}

//goes through the entire hash table and sets all the markers of every student
//to false
void PersonHash::unmarkAllStudents() {
	for (int i = 0; i < size; i++) {
		Person* temp = arr[i];
		while (temp != NULL) {
			temp->unmark();
			temp = temp->next;
		}
	}
}
//finds all paths between the given students if they exist, using the helper 
//function "findPaths." This algorithm uses DFS and marks the students to avoid
//infinite loops. 
void PersonHash::findAllPaths(string person1, string person2) {
        unmarkAllStudents();
	int key = (hash_string(person1))%size;
	vector<Pointer_Node> paths;
	vector<Person*> people;
	Person* temp = arr[key];
	if (getPointer(person2) == NULL) {
		cout << "Student not found" << endl;
		return;
	}
	while (temp != NULL) {
		if (temp->name == person1) {
			temp->mark();
			people.push_back(temp);
			for (int i = 0; i < temp->students.size(); i++) {
				Pointer_Node pn = temp->students[i];
				paths.push_back(pn);
				findPaths(pn.pers, person2, paths, people);
				paths.pop_back();
			}
			temp->unmark();
			return;
		}
		temp=temp->next;
	}
	cout << "Student not found" << endl;
}

//returns true if paths have been found. If they have, they have already been
//printed by the time this function recurses all the way back out. Implements
//DFS by checking all the students of a person, and recursively their students,
//etc. 
bool PersonHash::findPaths(Person* pers1, string pers2, vector<Pointer_Node> 
				&paths, vector<Person*> &people){
	if (pers1->name == "NULL") {
		return false;
	}
	if (pers1->name == pers2) {
		people.push_back(pers1);
		printPaths(paths, people);
		people.pop_back();
		return true;
	}
	bool found = false;
	if (pers1->isMarked()) {
		return false;
	}
	people.push_back(pers1);
	pers1->mark();
	for (int i = 0; i < pers1->students.size(); i++) {
		paths.push_back(pers1->students[i]);
		if (findPaths((pers1->students)[i].pers, pers2, paths, people))
			found = true;
		paths.pop_back();
	}
	pers1->unmark();
	people.pop_back();
	return true;
}

//prints the path specified by the vectors paths and peop
void PersonHash::printPaths(vector<Pointer_Node> &paths,vector<Person*> &peop) {
	for (unsigned long i = 0; i < paths.size(); i++) {
		cout << peop[i]->name << " +- " << paths[i].ta_class << " -> ";
	}
	cout << peop[peop.size()-1]->name << endl;
}

//comparable to unmarkAll, this function goes through every person in the hash
//and sets their value to -1, in this case infinity
void PersonHash::setToInf() {
	for (int i = 0; i < size; i++) {
		Person* temp = arr[i];
		while (temp != NULL) {
			temp->distance = -1;
			temp = temp->next;
		}
	}
}

//this function uses BFS to find the shortest path between person1 and person2
//it uses a queue to traverse all people directly related to a given node before
//going any deeper. This way, as soon as it finds a path it can print it because
//it must be the shortest, or one of the shortest
void PersonHash::findShortestPath(string person1, string person2) {
	int key2 = (hash_string(person2))%size;
	setToInf();
	for (Person* temp2 = arr[key2]; temp2 != NULL; temp2=temp2->next) {
		if (temp2->name == person2) {
			int key = (hash_string(person1))%size;
			for (Person* temp=arr[key];temp!=NULL;temp=temp->next){
				if (temp->name == person1) {
					queue<Person*> vertices;					
					temp->distance = 0;
					vertices.push(temp);
					shortPathHelp(vertices,person1,person2);
					return;
				}
			}
			cout << "Student not found" << endl;
			return;
		}
	}
	cout << "Student not found" << endl;
}

//helper function written to make findShortestPath shorter, more readable, and
//under 80 columns.
void PersonHash::shortPathHelp(queue<Person*> &vertices,string p1,string p2){
	while (!(vertices.empty())) {
		Person* p = vertices.front();
		if (p->name == p2) {
			printSinglePath(p, p1);
			return;
		}
		vertices.pop();
		for (int i = 0;i < p->students.size(); i++) {
			if (p->students[i].pers->distance == -1) {
				Person * person = p->students[i].pers;
				person->distance = p->distance +1;
				person->path = p;
				person->pathClass = p->students[i].ta_class;
				vertices.push(p->students[i].pers);
			}
		}
	}
}

//this function takes the pointer to the last person in the path and the string
//name of the first person and uses the path and pathClass variables within
//the Person class to traverse backwards and print the shortest path
void PersonHash::printSinglePath(Person* p, string person1) {
	vector<string> paths;
	vector<string> names;
	names.push_back(p->name);
	while (p->name != person1) {
		paths.push_back(p->pathClass);
		names.push_back(p->path->name);
		p = p->path;
	}
	if (names.size() == 1) {
		return;
	}
	for (int i = names.size()-1; i > 0; i--) {
		cout << names[i] << " +- " << paths[i-1] << " -> ";
	}
	cout << names[0] << endl;
}
