#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <iostream>
#include "FlowManager.h"
namespace flowspace {
	namespace gamespace {

		
		struct player{
			Vector2 position;
			Vector2 speed;
			Vector2 acceleration;
			float defaultAcceleration;
			float rotation;
			unsigned int shipHeight;
			float colliderRadius;
		};

		struct asteroid {
			Vector2 position;
			Vector2 speed;
			unsigned int colliderRadius;
		};

		extern bool isPasued;
		void initGameplay();
		void updateGame();
		void drawGame();
		void exitGame();
	}
}
#endif

