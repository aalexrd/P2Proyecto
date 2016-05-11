#include "Game.h"

Game::Game(float bet, float firstBet, int players, Player* player) : bet(bet), firstBet(firstBet), players(players), player(player)
{
	if (players != 0)
	{
		this->player = new Player[players];
		this->player = player;
		dealCards(); //time to deal cards to our players
	}
}

void Game::dealCards() const
{
	int v, playerIndex = 0, cardIndex = 0;
	while (cardIndex < 5 && playerIndex < players) //we will be playing five card draw version of poker
	{
		v = rand() % 52; //random number between 0 and 51
		if (!getDeck()[v].getGiven())
		{
			getDeck()[v].setGiven(true);
			player[playerIndex].addCard(getDeck()[v]);
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
		if (player[i].getBet() >= firstBet)
		{//the bet has to be greater or equal to the first
			bet += player[i].getBet();
		}
	}
}

int* Game::checkCards() const
{
	for (int i = 0; i < players; i++)
	{
		if (!player[i].getActive()) //if the player folded skip
		{
			player[i].setHand(-1);
			continue;
		}
		if (checkRoyalFlush(i))
			continue;
		if (checkStraightFlush(i))
			continue;
		if (checkFourOfAKind(i))
			continue;
		if (checkFullHouse(i))
			continue;
		if (checkFlush(i))
			continue;
		if (checkStraight(i))
			continue;
		if (checkThreeOfAKind(i))
			continue;
		if (checkTwoPair(i))
			continue;
		if (checkOnePair(i))
			continue;
		player[i].setHand(HighCard);
		sortCards(i); //for high card
	}
	sameHand();
	int* winners;
	for (int k = 9, count = 0; k >= 0; k--)
		for (int i = 0; i < players; i++)
		{
			if (!player[i].getActive()) //if the player folded skip
				continue;
			if (player[i].getHand() == k) //if enters here it found the highest hand among all players
			{
				for (k = 0; k < players; k++) //then lets find if there's a tie
					if (player[i].getHand() == player[k].getHand() && i != k)
						++count;
				if (count == 0) //if there's only one winner
				{
					winners = new int[2];
					winners[0] = 1; //send how many winners are there
					winners[1] = i;
					return winners;
				}
				winners = new int[count + 2];
				winners[0] = ++count; //send how many winners are there
				winners[1] = i; //save first winner found
				for (k = 0 , count = 1; k < players; k++) //k is the index of player, count is the index of the vec for winners
					if (player[i].getHand() == player[k].getHand() && i != k)
						winners[++count] = k;
				return winners;
			}
		}
	return nullptr;
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
	int counter, c, l;
	for (int fh = 0; fh < 13; fh++) //look for two cards of same rank
	{
		for (c = 0 , counter = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
			{
				++counter;
				if (counter == 2)
				{
					/*for (fh = 3; fh >= 0; fh--) //peek highest suit of the two
						for (int ch = 0; ch < 5; ch++)
							if (player[i].getCards()[ch].getCard() == player[i].getCards()[c].getCard() && player[i].getCards()[ch].getSuit() == getDeck()->getSuits()[fh])
							{*/
					player[i].getCards()[7] = player[i].getCards()[c]; //change c for ch
					/*fh = -1;
					break;
				}*/
					for (l = 12 , counter = 7; l >= 0 && counter < 11; l--)
						for (c = 0; c < 5; c++)
							if (player[i].getCards()[c].getCard() == getDeck()->getCards()[l] && player[i].getCards()[c].getCard() != player[i].getCards()[7].getCard())
							{
								++counter;
								player[i].getCards()[counter] = player[i].getCards()[c];
								break;
							}
					player[i].setHand(OnePair);
					return true;
				}
			}
	}
	return false;
}

bool Game::checkTwoPair(int i) const
{
	int counter, c;
	wstring rank = L"";
	for (int fh = 0; fh < 13; fh++) //look for two cards of same rank
	{
		for (c = 0 , counter = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
			{
				++counter;
				if (counter == 2)
				{
					/*for (fh = 3; fh >= 0; fh--) //peek highest suit of the two
						for (int ch = 0; ch < 5; ch++)
							if (player[i].getCards()[ch].getCard() == player[i].getCards()[c].getCard() && player[i].getCards()[ch].getSuit() == getDeck()->getSuits()[fh])
							{*/
					player[i].getCards()[7] = player[i].getCards()[c]; //change c for ch
					/*fh = -1;
					break;
				}*/
					rank = player[i].getCards()[c].getCard();
					break;
				}
			}
	}
	for (int fh = 0; fh < 13; fh++) //look for another two cards of same rank but different from the past two
	{
		for (c = 0 , counter = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh] && player[i].getCards()[c].getCard() != rank)
			{
				++counter;
				if (counter == 2)
				{
					/*for (fh = 3; fh >= 0; fh--) //peek highest suit of the two
						for (int ch = 0; ch < 5; ch++)
							if (player[i].getCards()[ch].getCard() == player[i].getCards()[c].getCard() && player[i].getCards()[ch].getSuit() == getDeck()->getSuits()[fh])
							{*/
					player[i].getCards()[8] = player[i].getCards()[c]; //change c for ch
					/*fh = -1;
					break;
				}*/
					for (int ch = 0; ch < 5; ch++) //look for fifth different
						if (player[i].getCards()[ch].getCard() != player[i].getCards()[7].getCard() && player[i].getCards()[ch].getCard() != player[i].getCards()[8].getCard())
							player[i].getCards()[9] = player[i].getCards()[ch];
					player[i].setHand(TwoPair);
					return true;
				}
			}
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
			{
				++counter;
				if (counter == 3)
				{
					/*for (fh = 3; fh >= 0; fh--) //peek highest suit of the three
						for (int ch = 0; ch < 5; ch++)
							if (player[i].getCards()[ch].getCard() == player[i].getCards()[c].getCard() && player[i].getCards()[ch].getSuit() == getDeck()->getSuits()[fh])
							{*/
					player[i].getCards()[7] = player[i].getCards()[c]; //change c to ch
					/*fh = -1;
					break;
				}*/
					for (c = 0 , counter = 7; c < 5; c++)
						if (player[i].getCards()[c].getCard() != player[i].getCards()[7].getCard())
						{
							++counter;
							player[i].getCards()[counter] = player[i].getCards()[c];
						}
					player[i].setHand(ThreeOfAKind);
					return true;
				}
			}
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
			{ //for to save cards in order from #7
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
				if (lowest == 4)
				{
					sortCards(i);
					player[i].setHand(Straight);
					return true;
				}
				sf = 0;
			}
	}
	else
	{
		for (int sf = 0; sf < 5 && lowest < 8; sf++)
			if (player[i].getCards()[sf].getCard() == getDeck()->getCards()[lowest])
			{
				++lowest;
				++counter;
				if (counter == 5)
				{
					sortCards(i);
					player[i].setHand(Straight);
					return true;
				}
				sf = 0;
			}
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
		{
			player[i].getCards()[7] = player[i].getCards()[checkHighCard(i)];
			player[i].setHand(Flush);
			return true;
		}
	}
	return false;
}

bool Game::checkFullHouse(int i) const
{
	int counter, fh, c;
	for (fh = 0; fh < 13; fh++) //look for three cards of same rank
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh])
			{
				++counter;
				if (counter == 3)
				{
					/*for (fh = 3; fh >= 0; fh--) //peek highest suit of the three
						for (int ch = 0; ch < 5; ch++)
							if(player[i].getCards()[ch].getCard() == player[i].getCards()[c].getCard() && player[i].getCards()[ch].getSuit() == getDeck()->getSuits()[fh])
							{*/
					player[i].getCards()[7] = player[i].getCards()[c]; //change c for ch
					/*fh = -1;
					break;
				}*/
					break;
				}
			}
	}
	for (fh = 0; fh < 13; fh++) //look for two cards of same rank different from the past three
	{
		counter = 0;
		for (c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[fh] && getDeck()->getCards()[fh] != player[i].getCards()[7].getCard())
			{
				++counter;
				if (counter == 2)
				{
					/*for (fh = 3; fh >= 0; fh--) //peek highest suit of the two
						for (ch = 0; ch < 5; ch++)
							if (player[i].getCards()[ch].getCard() == player[i].getCards()[c].getCard() && player[i].getCards()[ch].getSuit() == getDeck()->getSuits()[fh])
							{*/
					player[i].getCards()[8] = player[i].getCards()[c]; //change c for ch
					/*fh = -1;
					break;
				}*/
					player[i].setHand(FullHouse);
					return true;
				}
			}
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
			{
				++counter;
				if (counter == 4)
				{
					player[i].getCards()[7] = player[i].getCards()[c];
					/*for (fk = 0; fk < 5; fk++)
						if(player[i].getCards()[fk].getCard() != player[i].getCards()[7].getCard())
							player[i].getCards()[8] = player[i].getCards()[fk];*/
					player[i].setHand(FourOfAKind);
					return true;
				}
			}
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
			if (checkStraight(i))
			{
				player[i].setHand(StraightFlush);
				return true;
			}
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
						if (counter == 5)
						{
							player[i].setHand(RoyalFlush);
							return true;
						}
						rf = 0;
					}
		}
	}
	return false;
}

void Game::sameHand() const
//set wich player has the highest hand based on rules
{
	for (int i = 0; i < players; i++)
		for (int j = 0; j < players; j++)
			if (player[i].getHand() == player[j].getHand() && i != j && player[i].getHand() != -1 && player[i].getActive() && player[j].getActive())
				switch (player[i].getHand())
				{
				case RoyalFlush: //if two got Royal Flush then the suit decides
					if (player[i].getCards()[0].getSuit() < player[j].getCards()[0].getSuit())
						player[j].setHand(-1);
					else
						player[i].setHand(-1);
					break;
				case StraightFlush:
					if (player[i].getCards()[7].getCard() == player[j].getCards()[7].getCard()) //if got same straight flush then suit decides
					{
						if (player[i].getCards()[0].getSuit() < player[j].getCards()[0].getSuit())
							player[j].setHand(-1);
						else
							player[i].setHand(-1);
					}
					else //then one is higher than the other
					{
						if (player[i].getCards()[7].getCard() > player[j].getCards()[7].getCard())
							player[j].setHand(-1);
						else
							player[i].setHand(-1);
					}
					break;
				case FourOfAKind:
					/*if (player[i].getCards()[7].getCard() == player[j].getCards()[7].getCard()) //if got same four of a kind then fifth card decides
					{
						if (player[i].getCards()[8].getCard() == player[j].getCards()[8].getCard()) //if for some reason the fifth is the same then suit decides
						{
							if (player[i].getCards()[8].getSuit() < player[j].getCards()[8].getSuit())
								player[j].setHand(-1);
							else
								player[i].setHand(-1);
						}
						else //then one fifth is higher than the other
						{
							if (player[i].getCards()[8].getCard() > player[j].getCards()[8].getCard())
								player[j].setHand(-1);
							else
								player[i].setHand(-1);
						}
					}
					else //then one is higher than the other
					{ */
					if (player[i].getCards()[7].getCard() > player[j].getCards()[7].getCard())
						player[j].setHand(-1);
					else
						player[i].setHand(-1);
					//}
					break;
				case FullHouse:
					/*if (player[i].getCards()[7].getCard() == player[j].getCards()[7].getCard()) //if got same three of same rank 
					{
						if (player[i].getCards()[8].getCard() == player[j].getCards()[8].getCard()) //if for some reason the pair is the same then suit decides
						{
							if (player[i].getCards()[8].getSuit() < player[j].getCards()[8].getSuit())
								player[j].setHand(-1);
							else
								player[i].setHand(-1);
						}
						else //then one pair is higher than the other
						{
							if (player[i].getCards()[8].getCard() > player[j].getCards()[8].getCard())
								player[j].setHand(-1);
							else
								player[i].setHand(-1);
						}
					}
					else //then one trio is higher than the other
					{*/
					if (player[i].getCards()[7].getCard() > player[j].getCards()[7].getCard())
						player[j].setHand(-1);
					else
						player[i].setHand(-1);
					//}
					break;
				case Flush:
					if (player[i].getCards()[7].getCard() == player[j].getCards()[7].getCard()) //if got same flush then sum decides 
					{
						int sum = 0, sum2 = 0;
						for (int k = 0; k < 5; k++)
						{
							sum += player[i].getCards()[k].getCardValue();
							sum2 += player[j].getCards()[k].getCardValue();
						}
						if (sum == sum2) //if fore some reason the sums are the same then suit decides
						{
							if (player[i].getCards()[7].getSuit() < player[j].getCards()[7].getSuit())
								player[j].setHand(-1);
							else
								player[i].setHand(-1);
						}
						else if (sum > sum2)
							player[j].setHand(-1);
						else
							player[i].setHand(-1);
					}
					else if (player[i].getCards()[7].getCard() > player[j].getCards()[7].getCard()) //then one flush is higher than the other
						player[j].setHand(-1);
					else
						player[i].setHand(-1);
					break;
				case Straight:
					if (player[i].getCards()[7].getCard() == player[j].getCards()[7].getCard()) //if got same high card then suit decide
					{
						if (player[i].getCards()[7].getSuit() < player[j].getCards()[7].getSuit())
							player[j].setHand(-1);
						else
							player[i].setHand(-1);
					}
					else if (player[i].getCards()[7].getCard() > player[j].getCards()[7].getCard()) //then one card is higher than the other
						player[j].setHand(-1);
					else
						player[i].setHand(-1);
					break;
				case ThreeOfAKind:
					for (int p = 7; p < 10; p++)
					{
						if (player[i].getCards()[p].getCard() == player[j].getCards()[p].getCard()) //if got same card then others decide
						{
							if (p == 9) //if last one is the same then suit decides
							{
								if (player[i].getCards()[7].getSuit() < player[j].getCards()[7].getSuit())
									player[j].setHand(-1);
								else
									player[i].setHand(-1);
							}
						}
						else if (player[i].getCards()[p].getCard() > player[j].getCards()[p].getCard())
						{
							player[j].setHand(-1);
							break;
						}
						else
						{
							player[i].setHand(-1);
							break;
						}
					}
					break;
				case TwoPair:
					for (int p = 7; p < 10; p++)
					{
						if (player[i].getCards()[p].getCard() == player[j].getCards()[p].getCard()) //if got same card then others decide
						{
							if (p == 9) //if last one is the same then suit decides
							{
								if (player[i].getCards()[7].getSuit() < player[j].getCards()[7].getSuit())
									player[j].setHand(-1);
								else
									player[i].setHand(-1);
							}
						}
						else if (player[i].getCards()[p].getCard() > player[j].getCards()[p].getCard())
						{
							player[j].setHand(-1);
							break;
						}
						else
						{
							player[i].setHand(-1);
							break;
						}
					}
					break;
				case OnePair:
					for (int p = 7; p < 11; p++)
					{
						if (player[i].getCards()[p].getCard() == player[j].getCards()[p].getCard()) //if got same card then others decide
						{
							if (p == 10) //if last one is the same then suit decides
							{
								if (player[i].getCards()[7].getSuit() < player[j].getCards()[7].getSuit())
									player[j].setHand(-1);
								else
									player[i].setHand(-1);
							}
						}
						else if (player[i].getCards()[p].getCard() > player[j].getCards()[p].getCard())
						{
							player[j].setHand(-1);
							break;
						}
						else
						{
							player[i].setHand(-1);
							break;
						}
					}
					break;
				case HighCard:
					for (int p = 7; p < 12; p++)
					{
						if (player[i].getCards()[p].getCard() == player[j].getCards()[p].getCard()) //if got same card then others decide
						{
							if (p == 11) //if last one is the same then suit decides
							{
								if (player[i].getCards()[7].getSuit() < player[j].getCards()[7].getSuit())
									player[j].setHand(-1);
								else
									player[i].setHand(-1);
							}
						}
						else if (player[i].getCards()[p].getCard() > player[j].getCards()[p].getCard())
						{
							player[j].setHand(-1);
							break;
						}
						else
						{
							player[i].setHand(-1);
							break;
						}
					}
					break;
				}
}

void Game::sortCards(int i) const
{
	for (int l = 12, counter = 7; l >= 0 && counter < 12; l--)
		for (int c = 0; c < 5; c++)
			if (player[i].getCards()[c].getCard() == getDeck()->getCards()[l])
			{
				player[i].getCards()[counter] = player[i].getCards()[c];
				++counter;
				break;
			}
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
