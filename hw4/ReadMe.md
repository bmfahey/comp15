## ReadMe for COMP 15 HW4 
## Binary Search Trees

Brendan Fahey
Last Edited: 3/14/15

This program uses a Binary Search Tree to store and access data. It can
store doubles of numbers and uses a full removal to take out nodes.

Files:

	main.cpp: This file is the main, executable line of the program. It 
was used for testing and debugging. It calls the other files in the program.

	pretty_print.cpp: This file was provided. It prints the tree in a 
graphical format.

	BinarySearchTree.h: This is the header file for the BST class. It 
was provided to us and the public interface was unchanged.
	
	BinarySearchTree.cpp: This is the implementation file for the BST 
class. The functions were filled in by the student. It can add and remove
nodes. The tree created is unbalanced.

How to Compile: Use the included MakeFile.

Binary Search Trees:
	a) invariant: everything to the left of a node is less than that 
		node, everything to the right is greater
	b) most functions have a log(n) efficiency because you are cutting
		the data in half each time (assuming a balanced tree)
	c) this particular implementation is not balanced

Recursion was widely used in this assignment. In fact, almost all the 
functions use it. 

Acknowledgements: I consulted Piazza for details about the assignment.

