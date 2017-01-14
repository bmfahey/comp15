//Brendan Fahey
//Implementation of IntVector class
//Comp15
//HW5

#include<stdexcept>
#include "IntVector.h"
using namespace std;

//default constructor
IntVector::IntVector() {
	vector = new int[INITIAL_CAP];
	used = 0;
	vector_capacity = INITIAL_CAP;
}

//overloaded constructor with initial size
IntVector::IntVector(int initialSize) {
	vector = new int[initialSize];
	used = 0;
	vector_capacity = initialSize;
}

//copy constructor
IntVector::IntVector(const IntVector &source) {
	copyVector(source);
}

//assignment operator overload
IntVector& IntVector::operator=(const IntVector &rhs) {
	if (this != &rhs) {
		deleteVector();
		copyVector(rhs);
	}
	
	return *this;
}

//destructor
IntVector::~IntVector() {
	deleteVector();
}

//helper function: deletes a vector
void IntVector::deleteVector() {
	delete[] vector;
	vector = NULL;
	used = 0;
	vector_capacity = 0;
}

//helper function: copies a vector
void IntVector::copyVector(const IntVector &source) {
	vector = new int[source.vector_capacity];
	vector_capacity = source.vector_capacity;
	used = source.used;
	for (int i = 0; i < source.used; i++) {
		vector[i] = source.vector[i];
	}
}

//"resets" a vector back to its initial state
void IntVector::destroy() {
	deleteVector();
	vector = new int[INITIAL_CAP];
	vector_capacity = INITIAL_CAP;
}

//used to return the integer value at the given index, CANNOT be used to set the
//value like the bracket syntax
int IntVector::get(int index) const {
	if (index >= used) {
		throw runtime_error("Index is not valid.");
	}
	else {
		return vector[index];
	}
}

//used to set the value of the vector at a given index
void IntVector::set(int index, int newVal) {
	if (index >= used) {
		throw runtime_error("Index is not valid.");
	}
	else {
		vector[index] = newVal;
	}
}

//overloads the bracket operator, returns a reference to the integer so that it
//can be changed and set equal to things
int& IntVector::operator[](int index) const {
	if (index >= used) {
		throw runtime_error("Index is not valid.");
	}
	else {
		return vector[index];
	}
}

//adds the value to the end of the vector, expands the vector if necessary
void IntVector::add(int newVal) {
	if (used == vector_capacity) {
		expand();
	}
	
	vector[used++] = newVal;
}

//returns the size of the vector
int IntVector::size() const {
	return used;
}

//returns the current capacity of the vector
int IntVector::capacity() const {
	return vector_capacity;
}

//dynamically expands the vector to accomodate more elements
void IntVector::expand() {
	int* temp = new int[vector_capacity*2];
	for (int i = 0; i < used; i++) {
		temp[i] = vector[i];
	}
	delete[] vector;
	vector = temp;
	vector_capacity *= 2;
}
