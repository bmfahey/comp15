#include <iostream>
using namespace std;
#include "NodeVector.h"

//each Person has a NodeVector that has the students they have been a TA for for
//any class. They also have markers which make the traversal much more simple.
//The path and pathClass variables are for BFS for shortestpath. Each student
//has a pointer to the next student because they are stored as a linked list
//in the PersonHash

class Person {
	public:
		Person();
		Person(string n);
		~Person();
		void addStudent(Person* p, string ta_class);
		void linkNext(Person p);
		void list_students_taed();
		void mark();
		void unmark();	
		bool isMarked();
		
		string name;
		Person* next;
		NodeVector students;
		int distance;
		Person* path;
		string pathClass;
	private:
		int num_students;
		bool marked;
};
