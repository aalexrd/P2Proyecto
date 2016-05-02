#include "Deck.h"

Deck::Deck()
{
	deck = new Card[52];
	int counter = 0, i;
	for (int j = 0; j < 4; j++)//there's 4 suits
		for (int k = 0; k < 13; k++)//there's 13 cards
		{
			if (j == 1 || j == 2) //hearts and diamonds red
				i = 1;
			else
				i = 0;
			deck[counter++] = Card(j, k, i);
		}
}

Card* Deck::getDeck()
{
	return deck;
}

void Deck::setDeck(Card* deck) const
{
	this->deck = deck;
}
