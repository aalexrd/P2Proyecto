#pragma once
#ifndef DECK_H
#define DECK_H
#include "Card.h"
using namespace std;

class Deck// mazo
{
protected:
	Card* deck;
public:
	Deck();
	Card* getDeck() const;
	void setDeck(Card* deck);
};
#endif
