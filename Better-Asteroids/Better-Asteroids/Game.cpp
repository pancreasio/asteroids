#include "Game.h"
namespace flowspace {
	namespace gamespace {


		void updateGame() {
			if (IsKeyPressed(KEY_Q)) {
				exitGame();
			}
		}
		void drawGame() {
			DrawTexture(ship, 100, 500, RED);
			DrawText("aca tendria que haber una nave", 300, 300, 20, GRAY);
		}
		void exitGame() {
			currentstate = menustate;
		}
	}
}