/*
 * Queue.cpp
 *
 */

#include <assert.h>
#include<iostream>
#include "Queue.h"

using namespace std;

Queue::Queue() {
	queue_array = new Student[QUEUE_INIT_CAPACITY];
	capacity = QUEUE_INIT_CAPACITY;
	size = 0;
	front = 0;
	back = 0;
}

Queue::~Queue() {
	delete[] queue_array;
}

void Queue::enqueue(Student stu) {
	//enough space?	
	if (size == capacity) {
		expand();
	}

	//inserting into queue
	queue_array[back] = stu;
	back = (back+1)%capacity;
	size++;
}

Student Queue::dequeue() {
	//corner case: empty list
	assert(size > 0);

	//removing from queue
	size--;
	Student stu = queue_array[front];
	front = (front+1)%capacity;
	return stu;
}

bool Queue::is_empty() {
	return (size == 0);
}

void Queue::expand() {
	Student* temp = new Student[capacity*2];
	for (int i = 0; i < size; i++) {
		//circular buffer
		temp[i] = queue_array[(front+i)%size];
	}
	front = 0;
	back = size;
	delete[] queue_array;
	queue_array = temp;
	capacity *=2;
}
