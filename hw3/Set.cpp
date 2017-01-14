/*
 * Set.cpp
 *
 * Add your code below.  Do not change the print function.
 *
 */

#include <iostream>
#include "Set.h"

using namespace std;


void Set::print_class()
{
        for (int i = 0; i < back; i++) {
                Student s = set_array[i];
                cout << s.name << ", "
                                << (s.major ? "Major" : "Non-Major")
                                << "\n";
        }
}

Set::Set() {
	set_array = new Student[INITIAL_CAP];
	back = 0;
	capacity = INITIAL_CAP;
}

Set::~Set() {
	delete[] set_array;
}

bool Set::add(Student s) {
	//is student already in set?
	if (is_enrolled(s)) {
		return false;
	} 

	//enough space?
	if (back == capacity) {
		expand();
	}

	//inserting
	set_array[back++] = s;

	return true;
}

bool Set::drop(Student s) {
	//searching for student
	for (int i = 0; i < back; i++) {
		if (set_array[i].name == s.name) {
			move_back(i);
			return true;
		}
	}

	//student not found
	return false;
}

bool Set::is_enrolled(Student s) {
	for (int i = 0; i < back; i++) {
		if (set_array[i].name == s.name) {
			return true;
		}
	}

	//not found
	return false;
}

int Set::size() {
	return back;
}

void Set::move_back(int index) {
	//filling space
	for (int i = index; i < back-1; i++) {
		set_array[i] = set_array[i+1];
	}
	back--;
}

void Set::expand() {
	Student* temp = new Student[capacity*2];
	for (int i = 0; i < capacity; i++) {
		temp[i] = set_array[i];
	}
	delete[] set_array;
	set_array = temp;
	capacity *=2;
}
