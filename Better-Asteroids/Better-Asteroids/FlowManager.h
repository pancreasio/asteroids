#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H
#include "raylib.h"
#include "Menu.h"
#include "Game.h"
#include <iostream>
namespace flowspace {
	enum gameState{
		menustate, gameplaystate
	};
	extern gameState currentstate;
	extern bool gameSwitch;
	extern unsigned int screenwidth;
	extern unsigned int screenheight;
	void initGame();
	void gameLoop();
	void generalDraw();
}
#endif