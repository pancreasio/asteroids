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
	extern Texture ship;
	extern gameState currentstate;
	extern bool gameSwitch;
	void initGame();
	void gameLoop();
	void update();
	void generalDraw();
}
#endif