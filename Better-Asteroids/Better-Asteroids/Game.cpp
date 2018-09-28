#include "Game.h"
namespace flowspace {
	namespace gamespace {
		Vector2 position = { 0,0 };

		void updateGame() {
			if (IsKeyPressed(KEY_Q)) {
				exitGame();
			}
		}
		void drawGame() {

		}
		void exitGame() {
			currentstate = menustate;
		}
	}
}