#pragma once
#ifndef Player_H
#define Player_H
#include <string>
#include "Deck.h"
using namespace std;

class Player
{
private:
	string name;
	float bet;
	int hand; //which hand has the player
	Card* cards;
	bool active;
public:
	explicit Player(string name = "Generic", float bet = 0, int hand = 0, Card* cards = nullptr, bool active = false);
	~Player();
	void setName(string name);
	string getName() const;
	void setBet(float bet);
	float getBet() const;
	int getHand() const;
	void setHand(int hand);
	Card* getCards() const;
	void setCards(Card* cards);
	bool addCard(Card card) const;
	bool getActive() const;
	void setActive(bool active);
};
#endif
