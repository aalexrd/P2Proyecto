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
	float earned;
	Card* cards;
	bool active;
public:
	Player();
	Player(string name, float bet, float earned, Card* cards, bool active);
	~Player();
	void setName(string name);
	string getName() const;
	void setBet(float bet);
	float getBet() const;
	void setEarned(float s);
	float getEarned() const;
	Card* getCards() const;
	void setCards(Card* cards);
	bool addCard(Card card) const;
	bool getActive() const;
	void setActive(bool active);
};
#endif
