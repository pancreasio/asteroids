#include "Menu.h"
namespace flowspace {
	namespace menuspace {
		void updateMenu(){
			exitGame();
		}
		void drawMenu() {

		}
		void exitMenu() {
			currentstate = gameplaystate;
		}
		void exitGame() {
			gameSwitch = false;
		}
	}
}