## ReadMe for COMP 15 H6
## 6 Degrees of TAing

## Brendan Fahey
## Last Modified: 4/25/16

	The purpose of this assignment was to apply and learn more about the 
various data structures we learned throughout the year. It was also the first 
time we made our own hash tables and our first extensive use of the C++ STL.

## Files:
	main.cpp: This is the file that includes main. It deals with reading in
the data, parsing it, and calling the appropriate function based on the looping
commands it reads in.

	ClassVec.h: This is the header file for the ClassVec class. A ClassVec
is a dynamic array of classes. This file includes the Class struct.

	ClassVec.cpp: This is the implementation file for the ClassVec class. It
includes functions that allow for adding and accessing of Classes within the
array. It relies on the STL vector.

	NodeVector.h: This is the header file for the NodeVector class. A 
NodeVector is a dynamic array of Pointer_Nodes. This file also contains the 
Pointer_Node struct.

	NodeVector.cpp: This is the implementation file for the NodeVector 
class. It allows for the addition and access of its elements. It expands to 
twice its size when it runs out of space.

	Person.h: This is the header file for the Person class. A Person is an
object that contains a name and an STL vector of pointers to the people it has
taed. It has a next pointer to make it easiser to put into a linked list.
	
	Person.cpp: The implementation file for the Person class. This file 
includes functions that allow students to be added to their TAs and other tools.

	PersonHash.h: This file is the header for the PersonHash class. A 
PersonHash is a static hash table of Person objects. It deals with collisions 
with linked lists.
	
	PersonHash.cpp: This file is the implementation of the PersonHash class.
It allows people to be added to the table. It is where most of the work for 
paths and shortestpath take place.

## How to Compile : Use included Makefile.

## Data Stuctures:
	# Dynamic Array
		a) used in the NodeVector class
		b) useful for random access of information
		c) also useful for tranversals
		d) sometimes memory inefficient->can have up to 2x necessary mem
		e) in this assignment I both made one of my own and used the STL
			vector implementation multiple times
	# Queue
		a) FIFO system
		b) I used the STL implementation for BFS
		c) useful when you only want the first element
	# Hash Table
		a) used for PersonHash
		b) dealt with collisions using Linked Lists
		c) mine is static - downfall: if the load factor gets too large
			it will no longer be O(1). Plus - saving time because
			no rehashing is necessary.
		d) used provided hash function, hash_string
## Algorithms:
	# lc
		Algorithm: To implement lc, I traversed my ClassVector and 
	printed each class as it came up, as long as it wasn't "NULL."
		Efficiency: I traverse the array only once, so this has 
	efficiency O(n).

	#ls
		Algorithm: I go through each element in each linked list of the
	hash table and print out the student's name as long as it is not "NULL."
		Efficiency: I traverse the array once, so as long as the linked 
	lists remain fairly small when compared to the size of the array it 
	has efficiency O(n).

	#roster
		Algorithm: As part of my ClassVec I stored a vector of pointers 
	to people. I traverse the array in ClassVec and follow each of the 
	pointers to get and print the name. 
		Efficiency: Because following the pointers and accessing the 
	name is fairly constant time, the efficiency of this algorithm is O(n) 
	because I traverse the entire vector once.

	#taed
		Algorithm: Taed first finds the person in question in the hash 
	table. It then loops through their Pointer_Nodes and collects the string
	that tells which class was TAed. It goes through each class, sees if it
	is already in the list, and adds an empty string instead of the class 
	name as it is. Then the list is looped through and printed out.
		Efficiency: This is efficiency O(n^2), mainly because of how I 
	prevent it from printing duplicates. Everytime I go to add something I
	loop through the entire existing list to see if it is already there. 
	These nested loops create the n^2.

	#paths
		Algorithm: For each person, I go through every person they have
	TAed, every person each of those people has TAed, and so on. Two vectors
	are passed with each recursive function call. During each function call
	the current node is marked. The person and the path to the next person 
	are pushed onto the back of the vector. Then, each student of the 
	current person is recursively called upon with a for loop. If a path is 
	found then the two vectors are used to print it. As it recurses back 
	out, the most recent things are popped from the vector and the person
	is unmarked.
		Efficiency: Because I have n for loops nested n number of times,
	I believe the efficiency of this algorithm is O(n^n). The efficiency of 
	printing each path is O(length of path). 

	#shortestpath: 
		Algorithm: I used Breadth First Search for this. It was the same
	as the shortest path algorithm discussed in class. Each node is added to
	and while that queue is not empty it adds a length to each person and 
	adds all of their students to a queue. Each time someone is visited, the
	path that it took to get to them has to be stored. This allows for 
	backwards traversal once a path is found.
		Efficiency: The efficiency of BFS depends greatly on how far you
	have to get into the loop. Its best-case efficiency is O(1) if the first
	person you check completes the path already. However, it can get up to 
	O(n^n) for the same reason as finding all the paths if the shortest one
	happens to be the last one checked.
## Citations:
	I talked with Christofer Phipher in a general sense about algorithms but
		we did not discuss specific code.
	I used the shortest path algorithm from class almost exactly.
