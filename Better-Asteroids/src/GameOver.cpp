#include "GameOver.h"
namespace flowspace {
	namespace gameoverspace {
		button restartButton;
		button exitButton;
		void updateGameOver() {

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (restartButton.position.x <= mousePosition.x && mousePosition.x <= restartButton.position.x + restartButton.size.x) {
					if (restartButton.position.y <= mousePosition.y && mousePosition.y <= restartButton.position.y + restartButton.size.y) {
						restart();
					}
				}
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (exitButton.position.x <= mousePosition.x && mousePosition.x <= exitButton.position.x + exitButton.size.x) {
					if (exitButton.position.y <= mousePosition.y && mousePosition.y <= exitButton.position.y + exitButton.size.y) {
						goToMenu();
					}
				}
			}
		}
		void initGameOver() {
			restartButton.position.x = screenwidth / 2 - 125;
			restartButton.position.y = screenheight / 2 + 100;
			restartButton.size.x = 250;
			restartButton.size.y = 60.0;
			exitButton.position.x = screenwidth / 2 - 125;
			exitButton.position.y = restartButton.position.y + 80;
			exitButton.size.x = 250;
			exitButton.size.y = 60.0;
		}
		void drawGameOver() {
			if (gamespace::won) {
				DrawText("YOU WON!",screenwidth/2-150,screenheight/2-100,60,WHITE);
			}
			else{
				DrawText("YOU SUCK SO HARD!",screenwidth/2-300 ,screenheight/2-100 ,60 ,WHITE );
			}
			DrawRectangle(exitButton.position.x, exitButton.position.y, exitButton.size.x, exitButton.size.y, WHITE);
			DrawText("MENU", exitButton.position.x + 65, exitButton.position.y + 10, 40, BLACK);
			DrawRectangle(restartButton.position.x, restartButton.position.y, restartButton.size.x, restartButton.size.y, WHITE);
			DrawText("RESTART!", restartButton.position.x + 22, restartButton.position.y + 10, 40, BLACK);
		}
		void restart() {
			gamespace::initGameplay();
			currentstate = gameplaystate;
		}
		void goToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}
	}
}