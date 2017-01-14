#include "List_dynamic_array.h"

#include <iostream>
#include <cassert>

using namespace std;

List_dynamic_array::List_dynamic_array()
{
        cards = new Card[INITIAL_CAPACITY];
	cards_held = 0;
	hand_capacity = INITIAL_CAPACITY;
}

List_dynamic_array::~List_dynamic_array()
{
	  delete[] cards;
}

/*
 * explicit copy constructor necessary because of pointer to cards
 * array 
 */
List_dynamic_array::List_dynamic_array(const List_dynamic_array &source)
{

	cards_held    = source.cards_held;
	hand_capacity = source.hand_capacity;

	cards = new Card[hand_capacity];
	for (int i = 0; i < cards_held; i++) {
		cards[i] = source.cards[i];
	}
}

/*
 * explicit operator= overload necessary because of pointer to cards
 * array 
 */
List_dynamic_array 
List_dynamic_array::operator=(const List_dynamic_array &source)
{
	Card *new_cards;

	// check for self-assignment -- return without doing anything
	if (this == &source) {
		return *this;
	}

	hand_capacity = source.hand_capacity;
	cards_held    = source.cards_held;
	new_cards     = new Card[hand_capacity];

	for (int i = 0; i < hand_capacity; i++) {
		new_cards[i] = source.cards[i];
	}
	delete [ ] cards;
	cards = new_cards;
	return *this;
}

bool List_dynamic_array::is_empty()
{
        return cards_held == 0;
}

void List_dynamic_array::make_empty()
{
        cards_held = 0;
}


int List_dynamic_array::cards_in_hand()
{
        return cards_held;
}

void List_dynamic_array::print_list()
{
	for (int i = 0; i < cards_held; i++) {
		cards[i].print_card();
		if (i != cards_held - 1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::print_list_int()
{
	for (int i = 0; i < cards_held; i++) {
		cards[i].print_card_int();
		if (i != cards_held - 1) {
			cout << ", ";
		} else {
			cout << "\n";
		}
	}
}

void List_dynamic_array::insert_at_front(Card c)
{
	//enough space?
        if (cards_held == hand_capacity) {
        	expand();
        }

        //shifts
        for (int i = cards_held; i > 0; i--) {
        	cards[i] = cards[i-1];
        }

        cards[0] = c;

        cards_held++;
}

void List_dynamic_array::insert_at_back(Card c)
{
	//enough space?
        if (cards_held == hand_capacity) {
        	expand();
        }

        //inserts and updates cards_held
        cards[cards_held] = c;
	cards_held++;
}

void List_dynamic_array::insert_at_index(Card c,int index)
{
	// if index is greater than cards_held, then fail
	assert(index <= cards_held);
	
	//enough space?
	if (cards_held == hand_capacity) {
		expand();
	}
	
	//moving to the right
	for (int i = cards_held; i > index; i--) {
		cards[i] = cards[i-1];
	}
	
	cards[index] = c;
	cards_held++;
}

void List_dynamic_array::replace_at_index(Card c, int index)
{
	// if index is greater than cards_held-1, then fail
	assert(index < cards_held);

	cards[index] = c;
}

Card List_dynamic_array::card_at(int index)
{
	// if index is out of bounds, fail
	assert (index >= 0 && index < cards_held);
	
	return cards[index];
}

bool List_dynamic_array::has_card(Card c)
{
	//checks all cards in deck
        for (int i = 0; i < cards_held; i++) {
        	if (cards[i].same_card(c))
        		return true;
        }

        return false;
}

bool List_dynamic_array::remove(Card c)
{
	//fails immediately if card not in deck
        if (!has_card(c))
        	return false;

        for (int i = 0; i < cards_held; i++) {
        	if (cards[i].same_card(c)) { //when it is found
        		for (int j = i; j < cards_held-1; j++) {
        			cards[j] = cards[j+1];
        		}
        		cards_held--;
        		return true;
        	}
        }
        return false;
}

Card List_dynamic_array::remove_from_front()
{
	// if the list is empty, fail
	assert(cards_held > 0);

	//so that this card isn't lost
	Card c = cards[0];

	//shifting backwards
	for (int i = 0; i < cards_held-1; i++) {
		cards[i] = cards[i+1];
	}
	cards_held--;

	return c;

}

Card List_dynamic_array::remove_from_back()
{
	// if the list is empty, fail
	assert(cards_held > 0);

	cards_held--;
	return cards[cards_held];
}

Card List_dynamic_array::remove_from_index(int index)
{
	// if the list is empty, fail
	assert(cards_held > 0);
	
	// if loc is outside of bounds, fail
	assert(index >= 0 && index < cards_held);

        //so the card isn't lost
	Card c = cards[index];

	//shifting backwards
	for (int i = index; i < cards_held-1; i++) {
		cards[i] = cards[i+1];
	}
	
	cards_held--;
	return c;
}

void List_dynamic_array::expand()
{
        Card * templist = new Card[hand_capacity*2];

        for (int i = 0; i < cards_held; i++) {
        	templist[i] = cards[i];
        }

        delete[] cards;

        cards = templist;

        hand_capacity *= 2;
}
