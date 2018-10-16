#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H
#include "raylib.h"
#include "Menu.h"
#include "Game.h"
#include "Credits.h"
#include "GameOver.h"
#include <iostream>
namespace flowspace {
	enum gameState{
		menustate, gameplaystate, creditsstate, gameoverstate
	};

	struct button {
		Vector2 position;
		Vector2 size;
		std::string text;
	};
	extern Vector2 mousePosition;
	extern gameState currentstate;
	extern bool gameSwitch;
	extern unsigned int screenwidth;
	extern unsigned int screenheight;
	void initGame();
	void gameLoop();
	void generalDraw();
}
#endif