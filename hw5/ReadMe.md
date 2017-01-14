## ReadMe for COMP 15 HW5
## Sorting Assignment

## Brendan Fahey
## Last Modified: 4/4/16

	The purpose of this assignment was to explore and practice the coding of 
different sorting algorithms. We learned how to examine the upsides and 
downsides of each in terms of both time efficiency and memory space.

## Files:
	sortnums.cpp: This is the main file, that reads in the data, checks the 
arguments for validity, sorts the numbers using the appropriate algorithm, and
displays the sorted list.

	IntVector.h: This is the header file for the IntVector class. It uses
a dynamic array to store integers.
	
	IntVector.cpp: This is the implementation file for the IntVector class.

	Queue.h: This is the header file for the Queue class. I wrote a Queue 
class because it seemed to make the most sense to use queues for radix sort.

	Queue.cpp: This file implements a Queue data structure using a linked
list.

## How to Compile : Use included Makefile.

## Data Stuctures:
	# Dynamic Array
		a) used to implement the IntVector class
		b) useful for many sorts because of random access
		c) slightly memory inefficient: at most you have twice what 
			you actually needed
		d) expanding copies entire list - also inefficient
	# Queue
		a) useful for radix sort because no random access was needed
		b) because I used a front and back pointer, all operations on
			the queue were constant time
		c) linked list was used for my implementation because it does 
			not use much more memory than necessary

## Algorithms:
	# Bubble Sort:
	Bubble sort only involves going through each element in the list and 
		comparing it to the next element. If the second is smaller, it 
		is swapped with the first.

	I made my implementation of bubble sort more efficient by allowing the
		loop to stop if nothing was swapped on that run (the list is 
		already sorted) and by only going as far into the array as I 
		needed to (the end of the list is always sorted).

	Efficiency:
		The worst case for bubble sort is O(n^2). This is because it may
		need to go through the entire list n number of times to put the 
		elements one at a time into place. This happens when the list is
		in reverse order.

		The best case for my implementation of bubble sort is O(n). If 
		it goes through the list once and nothing has moved, it stops 
		immediately.

	#QuickSort:
	QuickSort goes through a list and puts all elements less than a "pivot" 
		on its left and all numbers greater than it on its right. It
		does this recursively until the lists are sorted, then it merges
		them together through simple concatenation.

	I tried to avoid the worst case efficiency in my implementation by 
		always choosing the pivot to be halfway through a list.

	Efficiency:
		The worst case for quicksort is O(n^2) This happens when the 
		pivot happens to be in the worst place, because then the 
		algorithm must move everything n times.

		The best case for quicksort is O(nlog(n)). This is the case
		because it must go through every element in the list at least 
		once (to put it on the correct side of the pivot) and it must 
		recurse through the entire list (hence the log).

	#Radix Sort:
	Radix sort starts with the least significant digit of a number, and 
		sorts all the numbers with that digit into buckets. Then it adds
		these buckets together to make a new list, and the digit moves 
		up by one place. It keeps doing this until the list is 
		completely sorted. 

	Efficiency:
		The efficiency of radix sort is unusual because it depends on
		the length of the number you are passing to it. Becasue the
		numbers for this assignment are limited to 12 digits, it will 
		perform the loop at most 12 times, obviously a constant. 
		However, each time this happens the list needs to be
		concatenated from queues back into the IntVector. This has an
		efficiency of n each time because it must visit each element in
		the list. Thus, the efficiency of my algorithm is, I believe, 
		O(n).

## Citations:
	Piazza
	Class Notes
	https://en.wikipedia.org/wiki/Radix_sort
	https://en.wikipedia.org/wiki/Bubble_sort
	https://en.wikipedia.org/wiki/Quicksort