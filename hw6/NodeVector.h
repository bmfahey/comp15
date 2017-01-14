#include <iostream>
using namespace std;

//forward declatation of person to let it know that that class exists:
class Person; 

struct Pointer_Node {
	string ta_class;
	Person* pers;
};

//The NodeVector class holds a dynamic array of Pointer_Nodes, each of which 
//points to a person and has a string that constitutes the class said person
//was taed in.

class NodeVector {
	public:
		NodeVector();
		~NodeVector();
		NodeVector(const NodeVector &source);
		NodeVector& operator=(const NodeVector &rhs);
		Pointer_Node& operator[](int index);
		
		void add(Pointer_Node value);
		int size();
		void list_students();
		
	private:
		void deleteVec();
		void copyVec(const NodeVector &source);
		void expand();

		Pointer_Node* arr;
		int used;
		int capacity;
		
		static const int INITIAL_CAP = 20;
};
