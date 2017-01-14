#include <stdexcept>
#include "NodeVector.h"
#include <vector>
using namespace std;

//constructor - initializes new array
NodeVector::NodeVector() {
	arr = new Pointer_Node[INITIAL_CAP];
	used = 0;
	capacity = INITIAL_CAP;
}

//destructor - calls helper function
NodeVector::~NodeVector() {
	deleteVec();
}

//goes through each slot in the array and deletes the person pointed to by that
//spot, then frees array as a whole
void NodeVector::deleteVec() {
	delete[] arr;
}

//copy constructor - calls helper function
NodeVector::NodeVector(const NodeVector &source) {
	copyVec(source);
}

//assignment operator overload - calls two helper functions
NodeVector& NodeVector::operator=(const NodeVector &rhs) {
	if (this != &rhs) {
		deleteVec();
		copyVec(rhs);
	}
	
	return *this;
}

//copies all aspects of the source NodeVector to a new one
void NodeVector::copyVec(const NodeVector &source) {
	capacity = source.capacity;
	arr = new Pointer_Node[capacity];
	used = source.used;
	for (int i = 0; i < used; i++) {
		arr[i] = source.arr[i];
	}
}

//allows access to the Pointer Node located at index in the array. Prevents 
//segfaults with a runtime error that is thrown if the index is not valid
Pointer_Node &NodeVector::operator[] (int index) {
	if (index >= used) {
		throw runtime_error("Index out of bounds!");
	}
	return arr[index];
}

//exapnds if necessary, then simply adds a Pointer Node onto the back of the 
//array
void NodeVector::add(Pointer_Node value) {
	if (used == capacity) {
		expand();
	}
	arr[used] = value;
	used++;
}

//getter function - returns the current size of the array
int NodeVector::size() {
	return used;
}

//same expand function as always - copies everything to a bigger array 
//different in that it calls delete function
void NodeVector::expand() {
	Pointer_Node* temp = new Pointer_Node[capacity*2];
	for (int i = 0; i < used; i++) {
		temp[i] = arr[i];
	}
	deleteVec();
	arr = temp;
	capacity *= 2;
}

//lists all classes pointed to by TA (NodeVectors exist inside an instance of a
//person). Does not print duplicates
void NodeVector::list_students() {
	vector<string> classes;
	for (int i = 0; i < used; i++) {
		string poss = arr[i].ta_class;
		
		//to prevent duplicate classes from printing:
		for (unsigned long j = 0; j < classes.size(); j++) {
			if (classes[j] == poss) {
				poss = "";
			}
		}
		classes.push_back(poss);
			
	}
	for (unsigned long i = 0; i < classes.size(); i++) {
		if (classes[i] != "") {
			cout << classes[i] << endl;
		}
	}
}
