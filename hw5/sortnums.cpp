/*
 *  Comp 15
 *  Sorting Assignment
 *
 *  sortnums.cpp
 *  Author:  Mark A. Sheldon, Tufts University, Spring 2016
 *
 *  This file is taken from my solution, but with the function
 *  definitions, except for main(), omitted.
 *
 *  You may use this code as-is, you can modify it, or you can throw
 *  it away and do your own thing.  But there are things you should
 *  note:
 * 
 *       - main() is really sweet.  Aspire to this level of directness
 *         and clarity.
 *       - The integer vector is always passed by reference.  This
 *         avoids lots of copying, and allows you to not implement a
 *         copy constructor.
 *       - The input stream (cin) is also passed by reference.  Always
 *         pass input/output streams by reference or pointer. 
 *       - It is common Unix practice to print a "usage" string on the
 *         standard error output (cerr) when a program is not used
 *         correctly.  The usageAbort() function is give to you, and
 *         you can use it to exit the program with an appropriate
 *         message if no algorithm is given on the command line or if
 *         the algorithm given isn't one of "bubble", "sort2",
 *         "sort3".
 *       - Detailed specifications for the functions declared at the
 *         top of the file are given below main(), but the
 *         implementations have been omitted.
 */

//Modified by Brendan Fahey

#include <iostream>
#include <cstdlib>

#include "IntVector.h"
#include "Queue.h"

using namespace std;

string algorithmFromCommandLine(int argc, char *argv[]);
void   usageAbort (string progname, string message);
void   readNumbers(istream &input, IntVector &data);
string checkValidity(string algorithm);
void   sortNumbers(string algorithm, IntVector &data);
void   printNumbers(const IntVector &data);

void swap(IntVector &vector, int i, int j);

void bubbleSort(IntVector &data);
void quickSort(IntVector &data, int pivot);
void quickMerge(IntVector &data, IntVector &l, IntVector &m, IntVector &r);
void radixSort(IntVector &data);
void radixMerge(IntVector &data, Queue* queue_arr[]);


int main(int argc, char *argv[])
{
        IntVector data;
        string    sortAlgorithm;
      
        sortAlgorithm = algorithmFromCommandLine(argc, argv);
        readNumbers(cin, data);
        sortNumbers(sortAlgorithm, data);
	printNumbers(data);

        return 0;
}

/*
 * Abort the program with a message on standard error
 * explaining how to run the program correctly from the 
 * command line.
 */
void usageAbort(string progname, string message)
{
        cerr << message << endl
             << "Usage:  " << progname << " algorithm" << endl
             << "     where algorithm is one of "
             << "bubble, sort2, or sort3"
             << endl;
        exit(1);
}

//returns a string form of the algorithm from the command line if it is valid,
	//otherwise abort
string algorithmFromCommandLine(int argc, char *argv[]) {
	// should onlt be two arguments: program name and algorithm name
	if (argc != 2) {
		usageAbort(argv[0],"Incorrect number of arguments!");
	}
	else {
		string algorithm = argv[1];
		return checkValidity(algorithm);
	}
	return "";
}

//compares the algorithm string to valid ones, aborts if it is not
	//one of them. Because I put it in a new function it will cast to
	//a C++ string
string checkValidity(string s) {
	string algorithm = s;
	if (algorithm == "bubble"||algorithm == "sort2"||algorithm == "sort3") {
		return algorithm;
	}
	else {
		usageAbort("sortnums","Not a valid sorting algorithm!");
	}
	return "";
}

//reads in all the numbers from an inputstream and stores them in an intvector 
	//called data
void readNumbers(istream &input, IntVector &data) {
	bool state = false;
	int number;
	while (!state) {
		input >> number;
		state = input.fail();
		//fail checks the LAST attempt, so we don't want to add a fail
		if (!state) {
			data.add(number);
		}
	}
}

//updates contents of data so items are sorted using the chosen algorithm
void sortNumbers(string algorithm, IntVector &data) {
	if (algorithm == "bubble") {
		bubbleSort(data);
	}
	else if (algorithm == "sort2") {
		quickSort(data, data.size()/2);
	}
	else {
		radixSort(data);
	}
}

//prints contents of data, with one item per line
void printNumbers(const IntVector &data) {
	for (int i = 0; i < data.size(); i++) {
		cout << data.get(i) << endl;
	}
}

//sorts data using bubble sort
void bubbleSort(IntVector &data) {
	bool swapped = true;
	for (int i = 0; i < data.size()-1; i++) {
		swapped = false; //when something hasn't been swapped, in order
		for (int j = 0; j < data.size()-1-i; j++) {
			if (data[j+1] < data[j]) {
				swap(data,j,j+1);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

//sorts data using quicksort, takes data to be sorted and an integer for the 
	//location of the pivot
void quickSort(IntVector &data, int pivot) {
	//lists of 1 or 0 are sorted
	if (data.size() < 2) {
		return;
	}
	IntVector left, right, middle;
	int pivot_val = data.get(pivot);
	for (int i = 0; i < data.size(); i++) {
		if (data.get(i) < pivot_val) {
			left.add(data[i]);
		}
		else if (data.get(i) > pivot_val) {
			right.add(data[i]);
		}
		else {
			middle.add(data[i]);
		}
	}
	//recursively sort sublists
	quickSort(left, left.size()/2);
	quickSort(right, right.size()/2);
	//finally, concatenate
	quickMerge(data, left, middle, right);
}

//concatenates the lists together into the list that was passed to it
void quickMerge(IntVector &data,IntVector &l,IntVector &m, IntVector &r) {
	data.destroy();
	for (int i = 0; i < l.size(); i++) {
		data.add(l[i]);
	}
	for (int i = 0; i < m.size(); i++) {
		data.add(m[i]);
	}
	for (int i = 0; i < r.size(); i++) {
		data.add(r[i]);
	}
}

//sorts using radix sort, only works for base ten and up to the limit of digits
	//given for this assignment
void radixSort(IntVector &data) {
	//initializing an array of queues
	Queue* queue_arr[10];
	for (int i = 0; i < 10; i++) {
		queue_arr[i] = new Queue;
	}
	int key = 1;
	while (key < 1e+9) {
		key *= 10;
		for (int i = 0; i < data.size(); i++) {
			//value is the number in the correct "place" in the int
			int value = ((data[i])%key)/(key/10);
			queue_arr[value]->enqueue(data[i]);
		}
		radixMerge(data, queue_arr);
	}
	for (int i = 0; i < 10; i++) {
		delete queue_arr[i];
	}
}

//concatenates the arrays given in queue_arr into the IntVector Data
void radixMerge(IntVector &data, Queue* queue_arr[]) {
	data.destroy();
	for (int i = 0; i < 10; i++){
		while (!(queue_arr[i]->isEmpty())) {
			data.add(queue_arr[i]->dequeue());
		}
	}
}

//swaps the items at indices i and j in the intvector vector using an in-place 
	//swap
void swap(IntVector &vector, int i, int j) {
	vector[i] = vector[i] ^ vector[j];
	vector[j] = vector[j] ^ vector[i];
	vector[i] = vector[i] ^ vector[j];
}
