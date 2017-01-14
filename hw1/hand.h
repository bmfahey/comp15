#ifndef __hand_h__
#define __hand_h__

/*
 * A class for representing a collection of Cards.  
 * We'll call it hand, but a deck or discard pile could also
 * be represented with hand.
 *
 * The current implementation does not restrict a hand from having 
 * more than one of the same card, e.g., there could be 5 jacks of
 * spades.  Some casinos shuffle multiple decks, so this is actually
 * realistic, but if you want to guard against duplicate cards, the
 * application has to do that.
 *
 */

#include "card.h"
#include "List_dynamic_array.h"

class Hand {
public:
	Hand();
	~Hand();

	void order_hand();
	void print_hand();
	void print_hand_int();

        // adds card to the end of the hand
	void add_card(Card c);
	
        // returns true if the card was successfully removed, false otherwise
	bool remove_card(Card c); 

        // randomly shuffles the hand
	void shuffle();

        // deals a card from the top of the hand (the last card)
	Card deal_card_from_top(Hand &h);

        // deals a card from the bottom of the hand (the first card)
	Card deal_card_from_bottom(Hand &h);

        // returns true if the hand contains the card, false otherwise
	bool has_card(Card c);

        // creates a standard 52-card deck
	void create_deck();

        // reads a deck from standard input
	void read_deck();

        // return number of cards currently in the hand
	int cards_in_hand();
	
private:
	List_dynamic_array hand;
};

#endif // __hand_h__
