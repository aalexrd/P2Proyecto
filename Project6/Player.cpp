#include "Player.h"

Player::Player(string name, float bet, int hand, Card* cards, bool active) : name(name), bet(bet), hand(hand), active(active)
{
	//if they did'nt send a custom pointer of Card then create it
	if (cards == nullptr)
		this->cards = new Card[12]; //enough space for variants like texas hold'em
	else
		this->cards = cards;
}

Player::~Player()
{
}

void Player::setName(string name)
{
	this->name = name;
}

string Player::getName() const
{
	return name;
}

void Player::setBet(float bet)
{
	this->bet = bet;
}

float Player::getBet() const
{
	return bet;
}

int Player::getHand() const
{
	return hand;
}

void Player::setHand(int hand)
{
	this->hand = hand;
}

Card* Player::getCards() const
{
	return cards;
}

void Player::setCards(Card* cards)
{
	this->cards = cards;
}

bool Player::addCard(Card card) const
{
	for (int i = 0; i < 5; i++)
		if (!cards[i].getGiven())//the given value by default is false so if it is true, there's a valid card there
		{
			cards[i] = card;
			return true;
		}
	return false;
}

bool Player::getActive() const
{
	return active;
}

void Player::setActive(bool active)
{
	this->active = active;
}
