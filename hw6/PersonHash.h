using namespace std;
#include "ClassVec.h"
#include<queue>

//a PersonHash is a Hash Table of pointers to People, that themselves form a 
//linked list. This hash table does not expand but unless an extremely large
//amount of students is added, it will not slow down all that noticably.

class PersonHash {
	public:
		PersonHash();
		PersonHash(int s);
		~PersonHash();
		Person* operator[](int index) const;
		void add(Person* p);
		Person* getPointer(string name);
		void list_all();
		void list_classes_taed(string name);
		void findAllPaths(string person1, string person2);
		void findShortestPath(string person1, string person2);
		
	private:
		static const int INITIAL_SIZE = 20;
		int size;
		Person** arr;
		
		void unmarkAllStudents();
		void setToInf();
		void printPaths(vector<Pointer_Node> &paths, vector<Person*>
								&peop);
		void shortPathHelp(queue<Person*> &vertices,string p1,
								string p2);
		void printSinglePath(Person* p, string person1);
		bool findPaths(Person* person1, string person2, 
			       vector<Pointer_Node> &paths, vector<Person*>
				&people);
};
