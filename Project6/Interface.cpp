#include "Interface.h"

Interface::Interface()
{
	srand(time(nullptr)); //Initialize random number generator with a seed of time
	_setmode(_fileno(stdout), 0x20000);
}

void Interface::UI()
{
	setw(L"Bienvenido a")
}

void Interface::setw(wchar_t* i)
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
