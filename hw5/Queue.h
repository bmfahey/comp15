//Brendan Fahey
//Queue.h
//Comp15
//HW5

//implements a Queue using a linked list

using namespace std;

class Queue {
	public:
		Queue();
		~Queue();
		
		void enqueue(int num);
		int dequeue();
		bool isEmpty();
	private:
		struct Node {
			int value;
			Node* next;
		};
		int count;
		Node* front;
		Node* back;
};