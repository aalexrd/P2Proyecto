#include "Interface.h"

Interface::Interface()
{
	srand(time(nullptr)); //Initialize random number generator with a seed of time
	_setmode(_fileno(stdout), 0x20000);
}

void Interface::UI()
{
	system("Color F0");
	setw(L"Bienvenido al...\n");
	setColor(2);
	wcout << "\n"
		<< L"    \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665      \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665      \u2665\u2665     \u2665\u2665\u2665    \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665   \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665   \n"
		<< L"    \u2665\u2665      \u2665\u2665\u2665    \u2665\u2665\u2665    \u2665\u2665\u2665     \u2665\u2665    \u2665\u2665\u2665     \u2665\u2665            \u2665\u2665      \u2665\u2665\u2665  \n"
		<< L"    \u2665\u2665       \u2665\u2665   \u2665\u2665        \u2665\u2665    \u2665\u2665   \u2665\u2665\u2665      \u2665\u2665            \u2665\u2665       \u2665\u2665  \n"
		<< L"    \u2665\u2665       \u2665\u2665  \u2665\u2665\u2665        \u2665\u2665\u2665   \u2665\u2665  \u2665\u2665\u2665       \u2665\u2665            \u2665\u2665       \u2665\u2665  \n"
		<< L"    \u2665\u2665       \u2665\u2665  \u2665\u2665          \u2665\u2665   \u2665\u2665 \u2665\u2665\u2665        \u2665\u2665            \u2665\u2665      \u2665\u2665\u2665  \n"
		<< L"    \u2665\u2665      \u2665\u2665\u2665  \u2665\u2665          \u2665\u2665   \u2665\u2665 \u2665\u2665\u2665        \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665    \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665   \n"
		<< L"    \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665   \u2665\u2665          \u2665\u2665   \u2665\u2665\u2665\u2665\u2665\u2665        \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665    \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665    \n"
		<< L"    \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665    \u2665\u2665          \u2665\u2665   \u2665\u2665\u2665 \u2665\u2665\u2665       \u2665\u2665            \u2665\u2665    \u2665\u2665     \n"
		<< L"    \u2665\u2665           \u2665\u2665          \u2665\u2665   \u2665\u2665   \u2665\u2665\u2665      \u2665\u2665            \u2665\u2665    \u2665\u2665\u2665    \n"
		<< L"    \u2665\u2665           \u2665\u2665\u2665        \u2665\u2665\u2665   \u2665\u2665    \u2665\u2665\u2665     \u2665\u2665            \u2665\u2665     \u2665\u2665    \n"
		<< L"    \u2665\u2665            \u2665\u2665        \u2665\u2665    \u2665\u2665     \u2665\u2665     \u2665\u2665            \u2665\u2665     \u2665\u2665\u2665   \n"
		<< L"    \u2665\u2665             \u2665\u2665\u2665    \u2665\u2665\u2665     \u2665\u2665     \u2665\u2665\u2665    \u2665\u2665            \u2665\u2665      \u2665\u2665\u2665  \n"
		<< L"    \u2665\u2665              \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665      \u2665\u2665      \u2665\u2665\u2665   \u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665\u2665   \u2665\u2665       \u2665\u2665\u2665 \n"
		<< L"\n";
	cin.get();
	system("cls");
	setw(L"Cuantos jugadores desean jugar?\n");
	players = readFloat(); //set players quantity
	while (players > 7 || players < 2) //max of 7 players and a minimum of 2
	{
		wcout << L"No es un número correcto de jugadores";
		cin.get();
		system("cls");
		setw(L"Cuantos jugadores desean jugar?\n");
		players = readFloat();
	}
	player = new Player[players]; //use current pointer of Game class
	system("cls");
	setColor(0);
	//ask players names and bets
	for (int i = 0; i < players; i++)
	{
		setw(L"Ingrese el nombre del jugador " + to_wstring(i + 1) + L"\n");
		player[i].setName(readWstring());
		if (i == 0) //if it is the first player
		{
			setw(L"De cuanto sera la apuesta? ");
			bet = firstBet = readFloat();
			player[i].setBet(bet);
			player[i].setActive(true);
		}
		else
		{
			//print first bet and ask next player if wants to continue
			floorf(firstBet) == firstBet ? setw(L"La apuesta inicial es de " + to_wstring(static_cast<int>(firstBet)) + L"\n") : setw(L"La apuesta inicial es de " + to_wstring(firstBet) + L"\n");
			setw(L"Si desea apostar lo mismo o más, presione enter, si no, digite 1.\n");
			if (readFloat() != 1)
			{
				setw(L"Ingrese su apuesta: ");
				float temp = readFloat();
				if (temp < firstBet)
				{
					setw(L"No te quieras pasar de listo... Esa apuesta es menor que la primera!\n");
					cin.get();
					player[i].setActive(false);
				}
				else
				{
					bet += temp;
					player[i].setBet(temp);
					player[i].setActive(true); //the player didn't fold
				}
			}
			else
				player[i].setActive(false);
		}
		system("cls");
	}
	dealCards(); //Deal cards to players
	//time to show players cards and let 'em decide
	for (int i = 0; i < players && player[i].getActive(); i++)
	{
		setw(L"A continuacion se mostraran las cartas de " + player[i].getName() + L"\n");
		setw(L"Si no eres el/ella no presiones enter\n");
		cin.get();
		setw(L"Ahora mira tus cartas y decide si quieres seguir...\n");
		printCards(i);
		if (i == 0)
		{
			setw(L"Presiona enter para continuar jugando y apostar más...\n");
			setw(L"Si ya no quieres seguir ingresa 1 \n");
			if (readFloat() != 1)
			{
				setw(L"De cuánto sera la apuesta?: ");
				bet = firstBet = readFloat();
			}
			else
			{
				for (int i1 = 0; i1 < players - 1; i1++)
					player[i1] = player[i1 + 1];
				--players;
				i = -1;
			}
		}
		else
		{
			floorf(firstBet) == firstBet ? setw(L"La apuesta inicial es de " + to_wstring(static_cast<int>(firstBet)) + L"\n") : setw(L"La apuesta inicial es de " + to_wstring(firstBet) + L"\n");
			setw(L"Si desea apostar lo mismo o mas, presione enter para continuar.\n");
			setw(L"Si ya no quieres seguir ingresa 1 \n");
			if (readFloat() != 1)
			{
				setw(L"Ingrese su apuesta: ");
				float temp = stof(readWstring().c_str());
				if (temp < firstBet)
				{
					setw(L"No te quieras pasar de listo... Esa apuesta es menor que la primera!\n");
					cin.get();
					player[i].setActive(false);
				}
				else
				{
					bet += temp;
					player[i].setBet(temp);
					player[i].setActive(true); //the player didn't fold
				}
			}
		}
		system("cls");
	}
	int* winners = checkCards();
	if (winners == nullptr)
		exit(0);
	if (winners[0] == 1)
		setw(L"Felicidades " + player[winners[1]].getName() + L" has ganado!\n");
	else
	{
		setw(L"Se ha producido un empate en el lugar más alto, los ganadores:\n");
		for (int i = 1; i <= winners[0]; i++)
			setw(player[winners[i]].getName() + L"\n");
	}
	setw(L"Gracias por jugar");
	cin.get();
	exit(0);
}

void Interface::printCards(int i) const
{
	for (int i1 = 0; i1 < 5; i1++)
	{
		wcout << L"  \u256d\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u256e  ";
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0; i1 < 5; i1++)
	{
		if (player[i].getCards()[i1].getCard() == L"10")
		{
			wcout << L"  \u2502";
			setColor(player[i].getCards()[i1].getColor());
			wcout << player[i].getCards()[i1].getCard();
			setColor(0);
			wcout << L"       \u2502  ";
		}
		else
		{
			wcout << L"  \u2502";
			setColor(player[i].getCards()[i1].getColor());
			wcout << player[i].getCards()[i1].getCard();
			setColor(0);
			wcout << L"        \u2502  ";
		}
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0, lines = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502         \u2502  ";
		if (lines == 0 && i1 == 4)
		{
			wcout << endl;
			i1 = -1;
			lines = 1;
		}
	}
	wcout << endl;
	for (int i1 = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502    ";
		setColor(player[i].getCards()[i1].getColor());
		wcout << player[i].getCards()[i1].getSuit();
		setColor(0);
		wcout << L"    \u2502  ";
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0, lines = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502         \u2502  ";
		if (lines == 0 && i1 == 4)
		{
			wcout << endl;
			i1 = -1;
			lines = 1;
		}
	}
	wcout << endl;
	for (int i1 = 0; i1 < 5; i1++)
	{
		if (player[i].getCards()[i1].getCard() == L"10")
		{
			wcout << L"  \u2502       ";
			setColor(player[i].getCards()[i1].getColor());
			wcout << player[i].getCards()[i1].getCard();
			setColor(0);
			wcout << L"\u2502  ";
		}
		else
		{
			wcout << L"  \u2502        ";
			setColor(player[i].getCards()[i1].getColor());
			wcout << player[i].getCards()[i1].getCard();
			setColor(0);
			wcout << L"\u2502  ";
		}
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2570\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u256f  ";
		if (i1 == 4)
			wcout << endl;
	}
	setw(L"Presiona cualquier tecla para continuar.\n");
	cin.get();
	system("cls");
}

void Interface::setw(const wchar_t* i)
{
	int l = wcslen(i);
	int pos = static_cast<int>((80 - l) / 2);
	for (int k = 0; k < pos; k++)
		wcout << L" ";
	wcout << i;
}

void Interface::setw(wstring i) const
{
	setw(i.c_str());
}

void Interface::setColor(WORD c) /*black=0
								 dark_blue=1
								 dark_green = 2
								 dark_cyan = 3
								 dark_red = 4
								 dark_purple = 5
								 dark_yellow = 6
								 dark_white = 7,
								 gray = 8,
								 blue = 9,
								 green = 10,
								 cyan = 11,
								 red = 12,
								 purple = 13, pink = 13, magenta = 13,
								 yellow = 14,
								 white = 15 */
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

wstring Interface::readWstring() const
{
	string i;
	getline(cin, i);
	while (i == "")
	{
		setw(L"Ingrese lo que se le solicitó\n");
		getline(cin, i);
	}
	return wstring(i.begin(), i.end());
}

float Interface::readFloat() const
{
	string i;
k:
	getline(cin, i);
	for (int k = 0; k < strlen(i.c_str()); k++)
	{
		if (isdigit(i[k]) == false)
		{
			wcout << L"Digite lo que se le solicitó, intente de nuevo\n";
			goto k;
		}
	}
	return i != "" ? stof(i.c_str()) : 0;
}
