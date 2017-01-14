## ReadMe for COMP 15 HW3 
## Sets and Queues

Brendan Fahey
Last Edited: 2/19/15

This program uses the Abstract Data Types of Queues and Sets to implement 
one of the jobs of SIS: a course roster. Students use this to learn how to
implement these ADTs.

Files:

	main.cpp: This file is the main, executable line of the program. It 
was used for testing and debugging. It calls the other files in the program.

	Student.h: This file was provided for us. It has the implementation 
for a struct called "Student" that has a name and boolean for major.

	IsisCourse.cpp: This is the implementation file for a course. It adds
Students to the roster Set or the waitlist Queues. It deals with printing.

	IsisCourse.h: This is the header file for the IsisCourse class. It 
enumerates the functions to be used.

	Queue.cpp: This is the implementation file for a queue. It uses a 
dynamic array with a circular buffer to store the elements of the queue. 

	Queue.h: This is the header file for a queue. It lists the functions 
for a queue, and the public functions were not changed.

	Set.cpp: This is the implementation file for the set class. I used
a dynamic array for my set. It moves backwards to fill empty spaces when
something is removed.
	
	Set.h: This is the header file for the set class. The private part
was written by me and defines the dynamic array used to hold its elements.

How to Compile: Use the included MakeFile.

Queues:
	a. First in, first out system.
	b. Dynamic array with circular buffer was used "under the covers" 
		to implement.
	c. There is no direct way to search or access elements; when they
		come out of the queue they are erased from it.
Sets:
	a. Unordered list - searching has O(n) at best.
	b. Dynamic array was used to implement this.

There were no particular algorithms used in this project. All searching was 
	done linearly with a simple "while" loop.

Acknowledgements: I consulted Piazza for details about the assignment.

