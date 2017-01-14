## ReadMe for COMP 15 HW1 
## Dynamic Arrays

Brendan Fahey
Last Edited: 2/15/15

The purpose of this program was to explore the concept of linked lists. It 
uses a list of cards that can change size to do so. It helps practice
pointers and memory management.

Files:

	main.cpp: This file is the main, executable line of the program. It 
was used for testing and debugging. It calls the other files in the program.

	card.h: This is the header file for the "Card" class. It lists the 
functions and their return values and arguments that are part of "Card."

	card.cpp: This is the implementation file for the "Card" class. It 
includes the functions that are part of the "Card" object.

	hand.h: This is the header file for the "Hand" class. The "Hand" class 
has a dynamic list of "Card" objects.

	hand.cpp: This is the implementation file for the "Hand" class. It 
defines the functions that a "Hand" can perform.

	List_linked_list.h: This is the header file for the "List_linked_list" 
class. It enumerates the functions that a "List_linked_list" can perform.

	List_linked_list.cpp: This is the file that was not provided to the 
students. We filled in the functions to complete the functionality of this class. 
This type of list can expand and cards can be added or removed at different 
locations.

	Testing.h: The header file for the "Testing" class.

	Testing.cpp: This file was written for the sold purpose of testing the 
functions that I wrote in "List_linked_list.cpp." Each function is a unit test
 of a function in the list. This all takes place when an instance of Testing is
called from main.

How to Compile: Use the included MakeFile.

Linked Lists were used in this assignment:
	a. Helpful b/c they don't take up more memory than they need to.
	b. All memory is stored in the heap - must be deleted.
	c. No direct access to elements: list must always be traversed.

There were no particular algorithms used in this project. All searching was done
linearly with a simple "while" loop.

Extra files were made and used for testing and are part of "provide." 

Acknowledgements: I consulted Piazza for details about the assignment.

