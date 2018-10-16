#ifndef MENU_H
#define MENU_H
#include "raylib.h"
#include "FlowManager.h"
#include "Game.h"
namespace flowspace {
	namespace menuspace {
		void updateMenu();
		void drawMenu();
		void initMenu();
		void startGame();
		void viewCredits();
		void exitGame();
	}
}
#endif

