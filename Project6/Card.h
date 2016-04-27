#pragma once
#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card
{
private:
	const char suits[4] = {'\u2660', '\u2665', '\u2666', '\u2663'}; // 0 \u2660 = spades, 1 \u2665 = heart, 2 \u2666 = diamond, 3 \u2663 = clubs
	const char cards[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'};
	char suit;
	char card;
	int color;
	bool given;
public:
	Card();
	Card(int suit, int card, int color);
	const char* getSuits() const;
	const char* getCards() const;
	char getSuit() const;
	void setSuit(int suit);
	char getCard() const;
	void setCard(int card);
	int getColor() const;
	void setColor(int color);
	bool getGiven() const;
	void setGiven(bool given);
	void operator=(const Card c);
};
#endif
