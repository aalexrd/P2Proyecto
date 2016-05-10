#include "Card.h"

Card::Card(): suit(0), card(L"0"), color(0), given(false)
{
}

Card::Card(int suit, int card, int color) : suit(suits[suit]), card(cards[card]), color(color), given(false)
{
}

const wchar_t* Card::getSuits() const
{
	return suits;
}

const wstring* Card::getCards() const
{
	return cards;
}

wchar_t Card::getSuit() const
{
	return suit;
}

void Card::setSuit(int suit)
{
	this->suit = suits[suit];
}

wstring Card::getCard() const
{
	return card;
}

void Card::setCard(int card)
{
	this->card = cards[card];
}

int Card::getCardValue() const
{
	for (int i = 0; i < 13; i++)
		if (card == cards[i])
			return i + 2;
	return 0;
}

int Card::getColor() const
{
	return color;
}

void Card::setColor(int color)
{
	this->color = color;
}

bool Card::getGiven() const
{
	return given;
}

void Card::setGiven(bool given)
{
	this->given = given;
}

void Card::operator=(const Card& c)
{
	suit = c.getSuit();
	card = c.getCard();
	color = c.getColor();
	given = c.getGiven();
}
