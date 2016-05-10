#pragma once
#ifndef Interface_H
#define Interface_H
#include <iostream>
#include <io.h>
#include <ctime>
#include "Game.h"
#include <Windows.h>
using namespace std;

class Interface : public Game
{
public:
	Interface();
	void UI();
	void printCards(int i) const;
	static void setw(const wchar_t* i);
	void setw(wstring i) const;
	static void setColor(WORD c);
	wstring readWstring() const;
	float readFloat() const;
};
#endif
