/* card.h
 *
 * Class for representing cards in a standard 52-card deck.  Each
 * card's state is given by  the card's Rank and Suit, e.g., three of
 * diamonds.
 *
 * We supply enumerations for usual four suits (Clubs, Diamonds,
 * Hearts, and Spades) and for the usual ranks (2 -- 10 and the four
 * face cards). 
 *
 * The default card (the one you get from the default constructor) is
 * the ace of clubs.
 *
 * Cards are mutable:  their suit and rank are separately settable.
 *
 */

#ifndef __card_h__
#define __card_h__

enum Suit {CLUB, DIAMOND, HEART, SPADE};
enum Rank {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
           JACK, QUEEN, KING, ACE};


class Card 
{
public:
	Card();                    // Defaults to ace of clubs
	Card(char r, char s);
	~Card();

	void print_card();         // print card, e.g., "3D"
	void print_card_int();     // print integer value of card
	
	Suit get_suit();           // return suit of card
	void set_suit(Suit s);     // set the suit of card
	
	Rank get_rank();           // return rank of card (e.g., THREE)
	void set_rank(Rank r);     // set rank of card
	
	bool same_card(Card c);    // return true of represent same card
	int card_int();            // return integer value of card
private:
	Suit suit;
	Rank rank;
};

#endif // __card_h__

