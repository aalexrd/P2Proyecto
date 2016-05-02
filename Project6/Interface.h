#pragma once
#ifndef Interface_H
#define Interface_H
#include <iostream>
#include <io.h>
#include "Game.h"
using namespace std;

class Interface : public Game
{
public:
	Interface();
	void UI();
	static void setw(wchar_t* i);
	void setw(wstring i) const;
};
#endif
