#include "Game.h"

Game::Game() : bet(0), players(2), player(new Player[2]) //by default it'll have 2 players
{
}

Game::Game(float bet = 0, int players = 2, Player* player = nullptr) : bet(bet), players(players)
{
	//if they didn't send a custom pointer of Player then create it
	if (player == nullptr)
		this->player = new Player[this->players];
	else
		this->player = player;
	//sum all bets for initial value if this is the first time
	if (bet == 0)
		for (int i = 0; i < players; i++)
			this->bet += player[i].getBet();
	dealCards(); //time to deal cards to our players
	srand(time(nullptr)); //Initialize random number generator with a seed of time
}

void Game::dealCards() const
{
	int v, playerIndex = 0, cardIndex = 0;

	while (cardIndex < 5) //we will be playing five card draw version of poker
	{
		v = rand() % 52; //random number between 0 and 51
		if (!getDeck()[v].getGiven())
		{
			player[playerIndex].addCard(getDeck()[v]);
			getDeck()->setGiven(true);
			++cardIndex;
			if (cardIndex == 5 && playerIndex < players)//if I haven't finished to deal cards to all players
			{
				cardIndex = 0;
				++playerIndex;
			}
		}
	}
}

void Game::increaseBet()
{
	for (int i = 0; i < players; i++)
	{
		if (player[i].getBet() >= firstBet)//either the player hasn't made a bet yet or folded
		{//also the bet has to be greater or equal to the first
			bet += player[i].getBet();
		}
	}
}

int Game::checkCards()
{
	int highest = 0;
	enum pokerHands
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
	int* p = new int[players];
	for (int i = 0; i < players; i++)
	{
		if (!player[i].getActive()) //if the player folded skip
			continue;
		if (checkRoyalFlush(i))
		{
			p[i] = RoyalFlush;
			continue;
		}
		if (checkStraightFlush(i))
		{
			p[i] = StraightFlush;
			continue;
		}
		if(checkFourOfAKind(i))
		{
			p[i] = FourOfAKind;
			continue;
		}
		if(checkFullHouse(i))
		{
			p[i] = FullHouse;
			continue;
		}
		if(checkFlush(i))
		{
			p[i] = Flush;
			continue;
		}
		if(checkStraight(i))
		{
			p[i] = Straight;
			continue;
		}
		if(checkThreeOfAKind(i))
		{
			p[i] = ThreeOfAKind;
			continue;
		}
		if(checkTwoPair(i))
		{
			p[i] = TwoPair;
			continue;
		}
		if(checkOnePair(i))
		{
			p[i] = OnePair;
			continue;
		}
		p[i] = HighCard;
	}
	for (int i = 0; i < players; i++)
	{
		switch(p[i])
		{
			
		}
	}
}

int Game::checkHighCard(int i) const
{
	for (int l = 12; l >= 0; l--) //find highest ranking of card
		for (int c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[l])
				return l;
	return 0;
}

bool Game::checkOnePair(int i) const
{
	int counter, c;
	for (int fh = 0; fh < 13; fh++) //look for two cards of same rank
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
				++counter;
		if (counter == 2)
			return true;
	}
	return false;
}

bool Game::checkTwoPair(int i) const
{
	int counter, c;
	char rank = 0;
	for (int fh = 0; fh < 13; fh++) //look for two cards of same rank
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
				++counter;
		if (counter == 2)
		{
			rank = player[i].getCards()[c].getCard();
			break;
		}
	}
	for (int fh = 0; fh < 13; fh++) //look for another two cards of same rank but different from the past two
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh] && player[i].getCards()[c].getCard() != rank)
				++counter;
		if (counter == 2)
			return true;
	}
	return false;
}

bool Game::checkThreeOfAKind(int i) const
{
	int counter, c;
	for (int fh = 0; fh < 13; fh++) //look for three cards of same rank
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
				++counter;
		if (counter == 3)
			return true;
	}
	return false;
}

bool Game::checkStraight(int i) const
{
	bool aceAsOne = false, passed = true;
	int counter = 0, lowest = 0;
	for (int l = 0; l < 13 && passed; l++) //find lowest ranking of card
		for (int c = 0; c < 5 && passed; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[l])
			{
				lowest = c;
				passed = false; //break both for
			}
	if (lowest == 0) //check if Ace has to be used as 1
		for (int l = 0; l < 5; l++)
			if (player[i].getCards()[l].getCard() == getDeck()->getCards()[12])
				aceAsOne = true;
	if (aceAsOne)
	{
		for (int sf = 0; sf < 5; sf++)
			if (player[i].getCards()[sf].getCard() == getDeck()->getCards()[lowest])
			{
				++lowest;
				sf = 0;
			}
		if (lowest == 3)
			return true;
	}
	else
	{
		for (int sf = 0; sf < 5 && lowest < 8; sf++)
			if (player[i].getCards()[sf].getCard() == getDeck()->getCards()[lowest])
			{
				++lowest;
				++counter;
				sf = 0;
			}
		if (counter == 5)
			return true;
	}
	return false;
}

bool Game::checkFlush(int i) const
{
	int counter;
	for (int fh = 0; fh < 4; fh++) //check if all cards have the same suit
	{
		counter = 0;
		for (int c = 0; c < 5; c++)
			if (player[i].getCards()[c].getSuit() == getDeck()->getSuits()[fh])
				++counter;
		if (counter == 5)
			return true;
	}
	return false;
}

bool Game::checkFullHouse(int i) const
{
	int counter, c;
	char rank = 0;
	for (int fh = 0; fh < 13; fh++) //look for three cards of same rank
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
				++counter;
		if (counter == 3)
		{
			rank = player[i].getCards()[c].getCard();
			break;
		}
	}
	for (int fh = 0; fh < 13; fh++) //look for two cards of same rank different from the past three
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh] && player[i].getCards()[c].getCard() != rank)
				++counter;
		if (counter == 2)
			return true;
	}
	return false;
}

bool Game::checkFourOfAKind(int i) const
{
	int counter;
	for (int fk = 0; fk < 13; fk++)
	{
		counter = 0;
		for (int c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fk])
				++counter;
		if (counter == 4)
			return true;
	}
	return false;
}

bool Game::checkStraightFlush(int i) const
{
	int counter;
	for (int sf = 0; sf < 4; sf++) //check if all cards have the same suit
	{
		counter = 0;
		for (int c = 0; c < 5; c++)
			if (player[i].getCards()[c].getSuit() == getDeck()->getSuits()[sf])
				++counter;
		if (counter == 5) //once we validate that all cards have the same suit check if they're consecutive
			return checkStraight(i);
	}
	return false;
}

bool Game::checkRoyalFlush(int i) const
{
	int counter;
	for (int fh = 0; fh < 4; fh++) //check if all cards have the same suit
	{
		counter = 0;
		for (int c = 0; c < 5; c++)
			if (player[i].getCards()[c].getSuit() == getDeck()->getSuits()[fh])
				++counter;
		if (counter == 5)
		{
			counter = 0;
			for (int rf = 0; rf < 5; rf++)
				for (int c = 9; c < 13; c++)
					if (player[i].getCards()[rf].getCard() == getDeck()->getCards()[c])
					{
						++counter;
						rf = 0;
					}
			if (counter == 5)
				return true;
		}
	}
	return false;
}

void Game::sameHand(int* p)
{

}

float Game::getBet() const
{
	return bet;
}

void Game::setBet(float bet)
{
	this->bet = bet;
}

float Game::getFirstBet() const
{
	return firstBet;
}

void Game::setFirstBet(float first_bet)
{
	firstBet = first_bet;
}

int Game::getPlayers() const
{
	return players;
}

void Game::setPlayers(int players)
{
	this->players = players;
}

Player* Game::getPlayer() const
{
	return player;
}

void Game::setPlayer(Player* player)
{
	this->player = player;
}
