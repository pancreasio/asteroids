#include "FlowManager.h"

namespace flowspace {
	gameState currentstate;
	bool gameSwitch;
	unsigned int screenheight = 600;
	unsigned int screenwidth = 800;
	Vector2 mousePosition;
	void initGame() {
		InitWindow(screenwidth, screenheight, "ASTEROIDS");
		gameSwitch = true;
		menuspace::initMenu();
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

			case creditsstate:
				creditsspace::updateCredits();
				generalDraw();
				break;
			case gameoverstate:
				gameoverspace::updateGameOver();
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
		case creditsstate:
			creditsspace::drawCredits();
			break;
		case gameoverstate:
			gameoverspace::drawGameOver();
			break;

		}
		EndDrawing();
	}
}