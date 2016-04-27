#pragma once
#ifndef DECK_H
#define DECK_H
#include "Card.h"
using namespace std;

class Deck
{
private:
	static Card* deck;
public:
	Deck();
	static Card* getDeck();
	void setDeck(Card* deck) const;
};
#endif
