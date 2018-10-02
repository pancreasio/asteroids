#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "FlowManager.h"
namespace flowspace {
	namespace gamespace {
		struct player{
			Vector2 position;
			Vector2 speed;
			float acceleration;
			float rotation;
			unsigned int shipHeight;
			float colliderRadius;
		};

		struct asteroid {
			Vector2 position;
			Vector2 speed;
			unsigned int colliderRadius;
		};
		void initGameplay();
		void updateGame();
		void drawGame();
		void exitGame();
	}
}
#endif

