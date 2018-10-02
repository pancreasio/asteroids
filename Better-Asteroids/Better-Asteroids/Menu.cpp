#include "Menu.h"
namespace flowspace {
	namespace menuspace {
		void updateMenu(){
			if (IsKeyPressed(KEY_Q)) {
				exitGame();
			}
			if (IsKeyPressed(KEY_V)) {
				exitMenu();
			}
		}
		void drawMenu() {
			DrawText("AAAAAAAAAAAAA",200,300, 50, RED);
			DrawText("Presiona V para comenzar, Q para salir", 100, 400, 30, GRAY);
		}
		void exitMenu() {
			gamespace::initGameplay();
			currentstate = gameplaystate;
		}
		void exitGame() {
			gameSwitch = false;
		}
	}
}