#ifndef  GAMEOVER_H
#define GAMEOVER_H
#include "raylib.h"
#include "Game.h"
#include "FlowManager.h"
#include "Menu.h"
namespace flowspace {
	namespace gameoverspace {
		void updateGameOver();
		void initGameOver();
		void drawGameOver();
		void restart();
		void goToMenu();
	}
}
#endif 
