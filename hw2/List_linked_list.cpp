#include "List_linked_list.h"

#include <iostream>
#include <cassert>

using namespace std;

/*
 * The following #define allows us to use Card_Node as a type.
 * Because the node structure is private, we would otherwise
 * have to write List_linked_list::Card_node everywhere.
 *
 * I put a few of those in, so you can see what I mean (see
 * the copy constructor.
 */
#define Card_Node List_linked_list::Card_Node

// hint: in your constructor, you might want to set the front to NULL
List_linked_list::List_linked_list() {
	front = NULL;
}

List_linked_list::~List_linked_list()
{
	//base case - avoid seg fault
	if (front == NULL) {
		return;
	}
	Card_Node* current = front;
	Card_Node* next_node = front->next;
	while (next_node != NULL) {
		//all these point to the heap, need deletion
		delete current;
		current = next_node;
		next_node = current->next;
	}
	delete current;
	//cleaned up last one	
}

List_linked_list::Card_Node 
*List_linked_list::copy_card_list(List_linked_list::Card_Node *lst)
{
        // Easy to copy an empty list
        if (lst == NULL)
                return NULL;

        // Otherwise make a new node
        List_linked_list::Card_Node *new_node_p
                = new List_linked_list::Card_Node;

        // Copy node data
        new_node_p->card = lst->card;

        // and copy the rest of the nodes
        new_node_p->next = copy_card_list(lst->next);

        // Return pointer to first node in copied list
        return new_node_p;
}

/*
 * Explicit copy constructor necessary because of cards list 
 * in the heap.
 */
List_linked_list::List_linked_list(const List_linked_list &source)
{
        front = copy_card_list(source.front);
}

/*
 * Explicit operator= overload necessary because of heap-allocated 
 * card nodes
 */
List_linked_list List_linked_list::operator =(const List_linked_list &source)
{
	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}
	// delete all current cards
	while (front != NULL) {
		Card_Node *next = front->next;
		delete front;
		front = next;
	}
	// copy over all cards from source list
	if (source.front == NULL) return *this; // nothing to do

	front = new Card_Node;
	Card_Node *this_current   = front;
	Card_Node *source_current = source.front;

	while (source_current != NULL) {
		// deep copy each Card_Node
		this_current->card = source_current->card;
		if (source_current->next != NULL) {
			Card_Node *new_node = new Card_Node();
			this_current->next  = new_node;
		} else {
			this_current->next = NULL; // at back
		}
		source_current = source_current->next;
		this_current   = this_current->next;
	}
	return *this;
}

void List_linked_list::print_list()
{
	Card_Node *current = front;
	while (current != NULL) {
		current->card.print_card();
		if (current->next != NULL) {
			cout << ",";
		} else {
			cout << "\n";
		}
		current = current->next;
	}
}

void List_linked_list::print_list_int()
{
	Card_Node *current = front;
	while (current != NULL) {
		current->card.print_card_int();
		if (current->next != NULL) {
			cout << ",";
		} else {
			cout << "\n";
		}
		current = current->next;
	}
}

int List_linked_list::cards_in_hand() {
	int count = 0;
	Card_Node* current = front;
	//traverse list and keep count
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

void List_linked_list::make_empty() {
	//NOTE: copied from destructor 
	
	//base case - avoid seg fault
	if (front == NULL) {
		return;
	}
	Card_Node* current = front;
	Card_Node* next_node = front->next;
	while (next_node != NULL) {
		//all these point to the heap, need deletion
		delete current;
		current = next_node;
		next_node = current->next;
	}
	delete current;
	//cleaned up last one	
	
	front = NULL;
}

void List_linked_list::insert_at_front(Card c) {
	//must make a new node w/ given card
	Card_Node* cn = new Card_Node;
	cn->card = c;
	cn->next = NULL;
	
	//base case
	if (front == NULL) {
		front = cn;
		return;
	}
	
	//other cases
	cn->next = front;
	front = cn;
}

void List_linked_list::insert_at_back(Card c) {
	//making new node w/ given card
	Card_Node* cn = new Card_Node;
	cn->card = c;
	cn->next = NULL;
	
	//base case
	if (front == NULL) {
		front = cn;
		return;
	}
	
	//must traverse list to find the end
	Card_Node* current = front;
	while (current->next != NULL) {
		current=current->next;
	}
	current->next=cn;
}

void List_linked_list::insert_at_index(Card c, int index) {
	//program crashes if this index doesn't exist
	assert(index <= cards_in_hand() && index >= 0);
	
	//making new node w/given card
	Card_Node* cn = new Card_Node;
	cn->card = c;
	cn->next = NULL;
	
	//empty list
	if (front == NULL) {
		front = cn;
		return;
	}

	//first element-corner case
	if (index == 0) {
		cn->next = front;
		front = cn;
		return;
	}

	int place = 0;
	//traverse list
	Card_Node* current = front;
	while (place < index-1) {
		current = current->next;
		place++;
	}
	cn-> next= current->next;
	current->next = cn;
}

void List_linked_list::replace_at_index(Card c, int index) {
	assert(index < cards_in_hand() && index >=0);

	//traverse array
	Card_Node* current = front;
	int count = 0;
	while (count < index) {
		current = current->next;
		count++;
	}
	current->card = c;
}

Card List_linked_list::card_at(int index) {
	//crashes with invalid index
	assert(index < cards_in_hand() && index >= 0);
	
	int place = 0;
	//traverse list
	Card_Node* current = front;
	while (place < index) {
		current = current->next;
		place++;
	}
	return current->card;
}

bool List_linked_list::has_card(Card c) {
	//must traverse list
	Card_Node* current = front;
	while (current != NULL) {
		if (current->card.same_card(c)) {
			return true;
		}
		current=current->next;
	}
	return false;
}

bool List_linked_list::remove(Card c) {
	//card not in list
	if (!(has_card(c))) {
		return false;
	}
	
	//corner case - first element
	if (front->card.same_card(c)) {
		Card_Node* to_delete = front;
		front = front->next;
		delete to_delete;
		return true;
	}

	//must traverse list
	Card_Node* current = front;
	while (current->next != NULL) {
		if (current->next->card.same_card(c)) {
			Card_Node* to_delete = current->next;
			current->next = current->next->next;
			delete to_delete;
			return true;
		}
		current=current->next;
	}	
	return false;
}

Card List_linked_list::remove_from_front() {
	//failing if list is empty
	assert(cards_in_hand() > 0);
	
	return remove_from_index(0);
}

Card List_linked_list::remove_from_back() {
	//failing if list is empty
	assert(cards_in_hand() > 0);
	
	return remove_from_index(cards_in_hand()-1);
}

Card List_linked_list::remove_from_index(int index) {
	//failing if index is invalid
	assert(index < cards_in_hand() && index >= 0);
	
	//special case: first element
	if (index == 0) {
		Card_Node* to_delete = front;
		Card c = front->card;
		front = front->next;
		delete to_delete;
		return c;
	}
	
	int place = 0;
	//traverse list
	Card_Node* current = front;
	while (place < index-1) {
		current=current->next;
		place++;
	}
	Card c = current->next->card;
	Card_Node* to_delete = current->next;
	current->next = current->next->next;
	delete to_delete;
	return c;
}
