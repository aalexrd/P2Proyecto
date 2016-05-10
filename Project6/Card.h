#pragma once
#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

class Card
{
private:
	const wchar_t suits[4] = {'\u2660', '\u2665', '\u2666', '\u2663'}; // 0 \u2660 = spades, 1 \u2665 = heart, 2 \u2666 = diamond, 3 \u2663 = clubs
	const wstring cards[13] = {L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"J", L"Q", L"K", L"A"};
	wchar_t suit;
	wstring card;
	int color;
	bool given;
public:
	Card();
	Card(int suit, int card, int color);
	const wchar_t* getSuits() const;
	const wstring* getCards() const;
	wchar_t getSuit() const;
	void setSuit(int suit);
	wstring getCard() const;
	void setCard(int card);
	int getCardValue() const;
	int getColor() const;
	void setColor(int color);
	bool getGiven() const;
	void setGiven(bool given);
	void operator=(const Card& c);
};
#endif
