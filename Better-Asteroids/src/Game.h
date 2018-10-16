#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include <iostream>
#include "FlowManager.h"
#include "GameOver.h"
namespace flowspace {
	namespace gamespace {

		
		struct player{
			Vector2 position;
			Vector2 acceleration;
			Vector2 speed;
			float defaultAcceleration;
			float rotation;
			unsigned int shipHeight;
			float colliderRadius;
		};

		struct asteroid {
			bool active;
			unsigned float acceleration;
			unsigned int stage;
			Vector2 position;
			Vector2 speed;
			unsigned int colliderRadius;
		};

		struct bullet {
			bool active;
			Vector2 position;
			Vector2 acceleration;
			float defaultAcceleration;
			double birthDate;
			unsigned int colliderRadius;
			
		};
		extern bool won;
		extern bool isPaused;
		void initGameplay();
		void updateGame();
		void drawGame();
		void finishGame();
		void exitGame();
	}
}
#endif

