#include "Menu.h"
namespace flowspace {
	namespace menuspace {
		button start;
		button quit;
		button credits;

		void initMenu() {
			start.position.x = screenwidth / 2 - 110;
			start.position.y = screenheight / 2;
			start.size.x = 220;
			start.size.y = 60.0;
			credits.position.x = screenwidth / 2 - 110;
			credits.position.y = screenheight / 2 + 70;
			credits.size.x = 220;
			credits.size.y = 60.0;
			quit.position.x = screenwidth / 2 - 110;
			quit.position.y = screenheight / 2 + 140;
			quit.size.x = 220;
			quit.size.y = 60.0;
		}

		void updateMenu(){

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };


			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (start.position.x <= mousePosition.x && mousePosition.x <= start.position.x + start.size.x) {
					if (start.position.y <= mousePosition.y && mousePosition.y <= start.position.y + start.size.y) {
						startGame();
					}
				}
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (credits.position.x <= mousePosition.x && mousePosition.x <= credits.position.x + credits.size.x) {
					if (credits.position.y <= mousePosition.y && mousePosition.y <= credits.position.y + credits.size.y) {
						viewCredits();
					}
				}
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (quit.position.x <= mousePosition.x && mousePosition.x <= quit.position.x + quit.size.x) {
					if (quit.position.y <= mousePosition.y && mousePosition.y <= quit.position.y + quit.size.y) {
						exitGame();
					}
				}
			}
		}
		void drawMenu() {
			DrawText("ASTEROIDS", screenwidth / 2 - 180, screenheight / 2 - 90, 60, WHITE);
			DrawRectangle(start.position.x, start.position.y, start.size.x, start.size.y, WHITE);
			DrawText("START", start.position.x + 32, start.position.y + 10, 45, BLACK);
			DrawRectangle(credits.position.x, credits.position.y, credits.size.x, credits.size.y, WHITE);
			DrawText("CREDITS", credits.position.x + 10, credits.position.y + 10, 45, BLACK);
			DrawRectangle(quit.position.x, quit.position.y, quit.size.x, quit.size.y, WHITE);
			DrawText("QUIT", quit.position.x + 55, quit.position.y + 10, 45, BLACK);
			DrawText("version 0.9",screenwidth -150,screenheight-20,20,GRAY);
		}
		void startGame() {
			gamespace::initGameplay();
			currentstate = gameplaystate;
		}
		void viewCredits() {
			creditsspace::initCredits();
			currentstate = creditsstate;
		}
		void exitGame() {
			gameSwitch = false;
		}
	}
}