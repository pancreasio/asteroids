#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "FlowManager.h"
namespace flowspace {
	namespace gamespace {
		struct player{
			Vector2 position;
			Vector2 speed;
			Vector2 acceleration;
			unsigned int shipHeight;
			unsigned int colliderRadius;
		};

		struct asteroid {
			Vector2 position;
			Vector2 speed;
			unsigned int colliderRadius;
		};
		void updateGame();
		void drawGame();
		void exitGame();
	}
}
#endif

