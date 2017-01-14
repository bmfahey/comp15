/*
 * IsisCourse.cpp
 *
 */

#include <iostream>
#include <exception>
#include <stdexcept>

using std::runtime_error;

#include "IsisCourse.h"

IsisCourse::IsisCourse()
{
        class_capacity = 0; // no students allowed in yet
}

IsisCourse::IsisCourse(int init_capacity)
{
	class_capacity = init_capacity;
}

IsisCourse::~IsisCourse()
{
        // nothing to do
}

void IsisCourse::set_class_cap(int cap)
{
        if (cap < class_capacity)
                throw runtime_error("IsisCourse:  "
                                    "class capacity cannot be lowered");
        class_capacity = cap;
        if (roster.size() < class_capacity) {
                update_enrollments();
        }
}

int IsisCourse::get_class_cap() {
	return class_capacity;
}

/*
 * See the enrollment logic from the assignment handout or
 * the IsisCourse.h file!
 */
IsisCourse::ENROLLMENT_STATUS IsisCourse::enroll_student(Student s)
{
        if (s.major) {
		if (roster.size() < class_capacity) {
			roster.add(s);
			return ENROLLED;
		}
		else {
			major_waitlist.enqueue(s);
			return MAJOR_WAITLIST;
		}
	}
	else {
		other_waitlist.enqueue(s);
		return OTHER_WAITLIST;
	}
}

bool IsisCourse::drop_student(Student s) {
        bool found_student = false;     // if we find the student to drop
        
	if (roster.drop(s)) return true;
	Queue temp_major, temp_other;

	//these loops avoid changing public functions
	while (!(major_waitlist.is_empty())) 
		temp_major.enqueue(major_waitlist.dequeue());
	while (!(temp_major.is_empty())) {
		Student stu = temp_major.dequeue();
		if (stu.name == s.name) 
			found_student = true;
		else 
			major_waitlist.enqueue(stu);
	}

	while (!(other_waitlist.is_empty())) 
		temp_other.enqueue(other_waitlist.dequeue());
	while (!(temp_other.is_empty())) {
		Student stu = temp_other.dequeue();
		if (stu.name == s.name) 
			found_student = true;
		else 
			other_waitlist.enqueue(stu);
	}

        // if we dropped a student, there should be room
        update_enrollments();
        return found_student;
}

int IsisCourse::get_roster_size() {
	return roster.size();
}

int IsisCourse::waitlist_position(ENROLLMENT_STATUS status, Student s)
{
	int place, count = 0;
	Queue temp;
	//loops avoid changing public interface
        if (status == MAJOR_WAITLIST) {
		while (!(major_waitlist.is_empty())) 
			temp.enqueue(major_waitlist.dequeue());
		while (!(temp.is_empty())) {
			Student stu = temp.dequeue();
			if (stu.name == s.name) 
				place =  count;
			else 
				count++;
		        major_waitlist.enqueue(stu);
		}
	}
	else {
		while (!(other_waitlist.is_empty())) 
			temp.enqueue(other_waitlist.dequeue());
		while (!(temp.is_empty())) {
			Student stu = temp.dequeue();
			if (stu.name == s.name) 
				place =  count;
			else 
				count++;
		        other_waitlist.enqueue(stu);
		}
	}	
	return place;
}

/* 
 * Return an ENROLLMENT_STATUS that says which list
 * (or none) that the student is on.
 */
IsisCourse::ENROLLMENT_STATUS IsisCourse::status(Student s) {
        //checking if student is already enrolled
	if (roster.drop(s)) {
		roster.add(s);
		return ENROLLED;
	}

	Queue temp_major, temp_other;
	ENROLLMENT_STATUS status = NONE;

	//traversing the queues
	while (!(major_waitlist.is_empty())) 
		temp_major.enqueue(major_waitlist.dequeue());
	while (!(temp_major.is_empty())) {
		Student stu = temp_major.dequeue();
		if (stu.name == s.name) status = MAJOR_WAITLIST;
		major_waitlist.enqueue(stu);
	}
	while (!(other_waitlist.is_empty())) 
		temp_other.enqueue(other_waitlist.dequeue());
	while (!(temp_other.is_empty())) {
		Student stu = temp_other.dequeue();
		if (stu.name == s.name) status = OTHER_WAITLIST;
		other_waitlist.enqueue(stu);
	}
	return status;
}

void IsisCourse::print_list(ENROLLMENT_STATUS status)
{
        Queue *waitlist_queue;
        Queue  temp_queue;

        if (status == ENROLLED) {
                roster.print_class();
                return;
        }
        if (status == MAJOR_WAITLIST) {
                waitlist_queue = &major_waitlist;
        } else {
                waitlist_queue = &other_waitlist;
        }
        // now handle printing the queue
	Queue temp;
	int place = 1;
        while (!(waitlist_queue->is_empty())) 
		temp.enqueue(waitlist_queue->dequeue());
	while (!(temp.is_empty())) {
		Student stu = temp.dequeue();
		std::cout << place << ". " << stu.name << std::endl;
		place++;
		waitlist_queue->enqueue(stu);
	}
}

/*
 * Put students from the waitlists into the class
 * in priority (majors first, then others), up to
 * the class capacity.
 */
void IsisCourse::update_enrollments()
{
	//add majors first
	while(roster.size()<class_capacity&&!(major_waitlist.is_empty())) {
		Student s = major_waitlist.dequeue();
		roster.add(s);
	}

	//while there's space, add everyone else
	while(roster.size()<class_capacity&&!(other_waitlist.is_empty())) {
		Student s = other_waitlist.dequeue();
		roster.add(s);
	}
}
