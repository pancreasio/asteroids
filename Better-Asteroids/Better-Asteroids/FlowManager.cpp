#include "FlowManager.h"

namespace flowspace {
	gameState currentstate;
	bool gameSwitch;

	void initGame() {
		InitWindow(800, 600, "(title here)");
		gameSwitch = true;
		currentstate = menustate;
		gameLoop();
	}
	void gameLoop() {
		while (gameSwitch){
			switch (currentstate) {
			case menustate:
				menuspace::updateMenu();
				generalDraw();
					break;

			case gameplaystate:
				gamespace::updateGame();
				generalDraw();
					break;
			}
		}
	}

	void generalDraw() {
		switch (currentstate) {
		case menustate:
			menuspace::drawMenu();
			break;
		case gameplaystate:
			gamespace::drawGame();
			break;
		}
	}
}