#include "Card.h"

Card::Card(): suit(0), card(0), color(0), given(false)
{
}

Card::Card(int suit, int card, int color) : suit(suits[suit]), card(cards[card]), color(color), given(false)
{
}

const char* Card::getSuits() const
{
	return suits;
}

const char* Card::getCards() const
{
	return cards;
}

char Card::getSuit() const
{
	return suit;
}

void Card::setSuit(int suit)
{
	this->suit = suits[suit];
}

char Card::getCard() const
{
	return card;
}

void Card::setCard(int card)
{
	this->card = cards[card];
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

void Card::operator=(const Card c)
{
	suit = c.getSuit();
	card = c.getCard();
	color = c.getColor();
	given = c.getGiven();
}
