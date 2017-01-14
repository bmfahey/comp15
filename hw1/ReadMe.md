## ReadMe for COMP 15 HW1 
## Dynamic Arrays

Brendan Fahey
Last Edited: 1/25/15

The purpose of this program was to explore the concept of dynamic arrays. It 
uses a list of cards that can change size to do so. This assignment, according 
to the specifications, will follow the same general format of some future ones.
This program helps with practice writing expand functions and dealing with 
pointers to arrays.

main.cpp: This file is the main, executable line of the program. It was used 
for testing and debugging. It calls the other files in the program.

card.h: This is the header file for the "Card" class. It lists the functions
and their return values and arguments that are part of "Card."

card.cpp: This is the implementation file for the "Card" class. It includes the
functions that are part of the "Card" object.

hand.h: This is the header file for the "Hand" class. The "Hand" class has a
dynamic list of "Card" objects.

hand.cpp: This is the implementation file for the "Hand" class. It defines the
functions that a "Hand" can perform.

List_dynamic_array.h: This is the header file for the "List_dynamic_array" 
class. It enumerates the functions that a "List_dynamic_array" can perform.

List_dynamic_array.cpp: This is the file that was not provided to the students.
We filled in the functions to complete the functionality of this class. This 
type of list can expand and cards can be added or removed at different 
locations.

Testing.h: The header file for the "Testing" class.

Testing.cpp: This file was written for the sold purpose of testing the functions
that I wrote in "List_dynamic_array.cpp." Each function is a unit test of a 
function in the list. This all takes place when an instance of Testing is
called from main.

How to Compile: Use the included MakeFile.

Dynamic Arrays were used to make this project. This type of data structure is 
helpful because normal arrays cannot expand to hold any number of objects, while
these can. Dynamic arrays are implemented using pointers to arrays. When the 
array needs to expand it actually creates a new, larger array and copies into 
that one. This makes dynamic arrays somewhat inefficient if large numbers of 
things are constantly being copied and it frequently has to look for new empty
space in memory. However, in terms of memory, it is usually better to have a 
dynamic array than to just make an extremely large array to begin with if you
don't know how many elements it will end up having.

There were no particular algorithms used in this project. All searching was done
linearly with a simple "for" loop.

Extra files were made and used for testing but are not part of "provide." 

Acknowledgements: I consulted Piazza for details about the assignment.

