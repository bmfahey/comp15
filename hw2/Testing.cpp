//Brendan Fahey
//This is how I tested the code. I made an instance of "Testing" in main.cpp
//which runs the constructor here. The constructor calls other functions that
//test individual components of the List_linked_list functions that I coded.

#include <iostream>
#include "List_linked_list.h"
#include "card.h"
#include "Testing.h"
  
using namespace std;

Testing::Testing() {
	List_linked_list list;
	list = test_empty(list);
	list = test_front_insert(list);
	list = test_back_insert(list);
	list = test_index(list);
	list = test_replace(list);
	list = test_card_at(list);
	list = test_has_card(list);
	list = test_removal(list);
	test_expand(list);
}

void Testing::test_expand(List_linked_list list) {
	for (int i = 0; i < 100; i++) {
		Card c;
		list.insert_at_front(c);
	}
	cout << "got to end, no errors" << endl;
}

List_linked_list Testing::test_removal(List_linked_list list) {
	Card c;
	c.set_rank(TWO);
	c.set_suit(SPADE);
	list.insert_at_back(c);
	list.print_list();
	list.remove_from_index(1);
	list.print_list();
	list.remove(c);
	list.print_list();
	list.remove_from_back();
	list.print_list();
	list.remove_from_front();
	list.print_list();
	return list;
}

List_linked_list Testing::test_has_card(List_linked_list list) {
	Card c;
	if (list.has_card(c))
		cout << "working!" << endl;
	return list;
}

List_linked_list Testing::test_card_at(List_linked_list list) {
	list.card_at(1).print_card();
	cout << endl;

	return list;
}

List_linked_list Testing::test_replace(List_linked_list list) {
	Card c;
	list.replace_at_index(c,1);
	list.print_list();

	return list;
}

List_linked_list Testing::test_index(List_linked_list list) {
	Card c;
	c.set_rank(JACK);
	c.set_suit(DIAMOND);
	list.insert_at_index(c,1);
	list.print_list();

	return list;
}

List_linked_list Testing::test_back_insert(List_linked_list list) {
	Card c;
	c.set_rank(FIVE);
	c.set_suit(HEART);
	list.insert_at_back(c);
	list.print_list();

	return list;
}

List_linked_list Testing::test_front_insert (List_linked_list list) {
	Card c;
	list.insert_at_front(c);
	list.print_list();
	return list;
}

List_linked_list Testing::test_empty(List_linked_list list) {
	if (list.is_empty())
		cout << "list is empty" << endl;
	else
		cout << "list is not empty" << endl;
	return list;
}
