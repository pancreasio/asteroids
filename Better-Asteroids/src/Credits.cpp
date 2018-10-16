#include "Credits.h"
namespace flowspace {
	namespace creditsspace {
		button back;
		void initCredits() {
			back.position.x = screenwidth / 2 - 110;
			back.position.y = screenheight / 2 + 100;
			back.size.x = 220;
			back.size.y = 60.0;
		}
		void updateCredits() {

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (back.position.x <= mousePosition.x && mousePosition.x <= back.position.x + back.size.x) {
					if (back.position.y <= mousePosition.y && mousePosition.y <= back.position.y + back.size.y) {
						goToMenu();
					}
				}
			}

		}
		void drawCredits() {
			DrawText("Game by Julian Serulnikov",screenwidth/2 -300,screenheight/2-200,50,WHITE);
			DrawText("Made with Raylib", screenwidth / 2 - 210, screenheight / 2 - 130, 50, WHITE);
			DrawRectangle(back.position.x, back.position.y, back.size.x, back.size.y, WHITE);
			DrawText("BACK", back.position.x + 32, back.position.y + 10, 45, BLACK);
			DrawText("version 0.9", screenwidth - 150, screenheight - 20, 20, GRAY);
		}
		void goToMenu() {
			menuspace::initMenu();
			currentstate = menustate;
		}
	}
}