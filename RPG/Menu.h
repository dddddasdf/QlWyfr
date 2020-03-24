#pragma once
#include "Headers.h"
#include "MapDraw.h"
#include "Game.h"

class Menu
{
private:
	MapDraw MenuMap;
	Game RolePlaying;
public:
	Menu();
	void PrintMainMenu();
	void NewGame();
	void LoadData();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Menu();
};

