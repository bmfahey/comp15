//Implementation of a Queue
//Brendan Fahey
//Comp15
//HW5

#include "Queue.h"
#include<iostream>
#include<assert.h>
using namespace std;

//constructor
Queue::Queue() {
	front = NULL;
	back = NULL;
	count = 0;
}

//destructor
Queue::~Queue() {
	if (front == NULL) {
		return;
	}
	Node* temp = front;
	Node* next_node = front->next;
	while (temp != NULL) {
		next_node = temp->next;
		delete temp;
		temp = next_node;
	}
	front = NULL;
	back = NULL;
	count = 0;
}

//enqueues the given integer into a node at the back of the linked list
void Queue::enqueue(int num) {
	Node* new_node = new Node();
	new_node->value = num;
	new_node->next = NULL;
	if (front == NULL) {
		front = new_node;
	}
	else {
		back->next = new_node;
	}
	back = new_node;
	count++;
}

//dequeues and returns the integer from the node at the beginning of the linked
	//list
int Queue::dequeue() {
	assert(count > 0);
	Node* temp = front;
	front = front->next;
	int num = temp->value;
	delete temp;
	if (count == 1)
		back = NULL;
	count--;
	return num;
}

//returns true if the list is empty
bool Queue::isEmpty() {
	return (count == 0);
}
