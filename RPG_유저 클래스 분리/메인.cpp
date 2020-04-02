#include "Headers.h"
#include "Menu.h"
#include <crtdbg.h>


void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(154);
	//_CrtSetBreakAlloc(155);
	//_CrtSetBreakAlloc(156);
	//_CrtSetBreakAlloc(157);
	system("mode con lines=31 cols=62");
	srand((unsigned)time(NULL));

	Menu Game;
	Game.PrintMainMenu();
}