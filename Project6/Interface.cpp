#include "Interface.h"

Interface::Interface()
{
	srand(time(nullptr)); //Initialize random number generator with a seed of time
	_setmode(_fileno(stdout), 0x20000);
}

void Interface::UI()
{
	std::system("Color F0");
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
	std::system("cls");
	setw(L"Cuantos jugadores desean jugar?\n");
	int players = readFloat();
	float bet = 0, firstBet = 0;
	while (players>7 || players<2)
	{
		wcout << L"No es un número correcto de jugadores";
		cin.get();
		std::system("cls");
		setw(L"Cuantos jugadores desean jugar?\n");
		players = readFloat();
	}
	player = new Player[players]; //use current pointer of Game class
	std::system("cls");
	setColor(0);
	for (int i = 0; i < players; i++)
	{
		setw(L"Ingrese el nombre del jugador " + to_wstring(i+1) + L"\n");
		getPlayer()[i].setName(readWstring());
		if (i == 0)
		{
			setw(L"De cuanto sera la apuesta? ");
			bet = firstBet = readFloat();
			getPlayer()[i].setBet(bet);
			getPlayer()[i].setActive(true);
		}
		else
		{
			setw(L"La apuesta inicial es de "+ to_wstring(firstBet)+L"\n");
			setw(L"Si desea apostar lo mismo o mas, presione 1 para continuar.\n");
			if (readFloat() == 1)
			{
				setw(L"Ingrese su apuesta: ");
				float temp = readFloat();
				if (temp < firstBet)
				{
					setw(L"No te quieras pasar de listo... Esa apuesta es menor que la primera!\n");
					cin.get();
				}
				else
				{
					bet += temp;
					getPlayer()[i].setBet(temp);
					getPlayer()[i].setActive(true); //the player didn't fold
				}
			}
		}
		system("cls");
	}
	Game(bet, firstBet, players, player); //Initialize game with valid data
	for (int i = 0; i < players; i++)
	{
		setw(L"A continuacion se mostraran las cartas de "+ getPlayer()[i].getName() + L"\n");
		cin.get();
		setw(L"Ahora mira tus cartas y decide si quieres seguir...\n");
		printCards(i);
		setw(L"Presiona 1 para continuar jugando y apostar mas...");
		setw(L"Si ya no quieres seguir presiona cualquier otra tecla");
		if (i == 0)
		{
			setw(L"De cuanto sera la apuesta?");
			bet = firstBet = readFloat();
		}
		else
		{
			setw(L"La apuesta inicial es de " + to_wstring(firstBet) + L"\n");
			setw(L"Si desea apostar lo mismo o mas, presione 1 para continuar.\n");
			if (readFloat() == 1)
			{
				setw(L"Ingrese su apuesta: ");
				float temp = stof(readWstring().c_str());
				if (temp < firstBet)
				{
					setw(L"No te quieras pasar de listo... Esa apuesta es menor que la primera!\n");
					cin.get();
				}
				else
				{
					bet += temp;
					getPlayer()[i].setBet(temp);
					getPlayer()[i].setActive(true); //the player didn't fold
				}
			}
		}
	}
	setBet(bet);
	setFirstBet(firstBet);
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
		wcout << L"  \u2502" << getPlayer()[i].getCards()[i1].getCard() << L"       \u2502  ";
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0, lines = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502        \u2502  ";
		if (lines == 0 && i1 == 4)
		{
			wcout << endl;
			i1 = 0;
			lines = 1;
		}
	}
	for (int i1 = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502    " << getPlayer()[i].getCards()[i1].getSuit() << L"    \u2502  ";
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0, lines = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502        \u2502  ";
		if (lines == 0 && i1 == 4)
		{
			wcout << endl;
			i1 = 0;
			lines = 1;
		}
	}
	for (int i1 = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2502        " << getPlayer()[i].getCards()[i1].getCard() << L"\u2502  ";
		if (i1 == 4)
			wcout << endl;
	}
	for (int i1 = 0; i1 < 5; i1++)
	{
		wcout << L"  \u2570\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u256f  ";
		if (i1 == 4)
			wcout << endl;
	}
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
			wcout << L"Digite lo que se le solicit\242, intente de nuevo\n";
			goto k;
		}
	}
	return stof(i.c_str());
}
