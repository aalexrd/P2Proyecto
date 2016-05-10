#pragma once
#ifndef GAME_H
#define GAME_H
#include "Deck.h"
#include "Player.h"
using namespace std;

class Game : public Deck
{
protected:
	float bet;
	float firstBet;

	enum pokerHands//enum all hands from 0 to 9 in ascending order of value
	{
		HighCard,
		OnePair,
		TwoPair,
		ThreeOfAKind,
		Straight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush,
		RoyalFlush
	};

	int players; //number of players
	Player* player; //original poker game has a maximum of 7 players, maximum is 10 for any version
	int checkHighCard(int i) const;
	bool checkOnePair(int i) const;
	bool checkTwoPair(int i) const;
	bool checkThreeOfAKind(int i) const;
	bool checkStraight(int i) const;
	bool checkFlush(int i) const;
	bool checkFullHouse(int i) const;
	bool checkFourOfAKind(int i) const;
	bool checkStraightFlush(int i) const;
	bool checkRoyalFlush(int i) const;
	void sameHand() const;
	void sortCards(int i) const;
public:
	explicit Game(float bet = 0, float firstBet = 0, int players = 0, Player* player = new Player);
	void dealCards() const;
	void increaseBet();
	int* checkCards() const;
	float getBet() const;
	void setBet(float bet);
	float getFirstBet() const;
	void setFirstBet(float first_bet);
	int getPlayers() const;
	void setPlayers(int players);
	Player* getPlayer() const;
	void setPlayer(Player* player);
};
#endif
