#include "FlowManager.h"

namespace flowspace {
	gameState currentstate;
	bool gameSwitch;
	Texture ship = LoadTexture("res/ship.png");

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
		BeginDrawing();
		ClearBackground(BLACK);
		switch (currentstate) {
		case menustate:
			menuspace::drawMenu();
			break;
		case gameplaystate:
			gamespace::drawGame();
			break;
		}
		EndDrawing();
	}
}