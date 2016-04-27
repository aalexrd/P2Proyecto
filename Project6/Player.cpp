#include "Player.h"

Player::Player(): name("Generic"), bet(0), earned(0), cards(new Card[5]), active(false)
//five cards maximum
{
}

Player::Player(string name = "Generic", float bet = 0, float earned = 0, Card* cards = nullptr, bool active = false) : name(name), bet(bet), earned(earned), active(active)
{
	//if they did'nt send a custom pointer of Card then create it
	if (cards == nullptr)
		this->cards = new Card[5];
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

void Player::setEarned(float s)
{
	earned = s;
}

float Player::getEarned() const
{
	return earned;
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
