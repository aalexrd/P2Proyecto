#include "Deck.h"

Deck::Deck()
{
	deck = new Card[52];
	int counter = 0;
	for (int i = 0; i < 2; i++)//there's only 2 colors, red and black
		for (int j = 0; j < 4; j++)//there's 4 suits
			for (int k = 0; k < 13; k++)//there's 13 cards
			{
				deck[counter] = Card(j, k, i);
				counter++;
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
