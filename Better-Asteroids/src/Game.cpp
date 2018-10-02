#include "Game.h"
namespace flowspace {
	namespace gamespace {
		Texture2D ship;
		player p1;
		int shipswidth = 237;
		int shipsheight = 291;
		float shipscale = 0.15f;
		Rectangle sourceRec = { 0.0f, 0.0f, (float)shipswidth, (float)shipsheight};
		Rectangle destRec = { (float)screenwidth / 2, (float)screenheight / 2, (float)shipswidth * shipscale , (float)shipsheight * shipscale};
		Vector2 colliderAllignment = { (float)shipswidth * shipscale - (float)shipswidth/2 * shipscale, (float)shipsheight * shipscale - (float)shipsheight / 2 * shipscale};

		void initGameplay() {
			p1.position.x = screenwidth / 2;
			p1.position.y = screenheight/ 2;
			p1.acceleration = 0.2;
			p1.rotation = 0;
			p1.colliderRadius = 4;
			ship = LoadTexture("../res/ship.png");

		}

		void updateGame() {
			if (IsKeyPressed(KEY_Q)) {
				exitGame();
			}
			if (IsKeyDown(KEY_W)) {
				p1.position.y -= p1.speed.y * p1.acceleration;
				p1.position.x -= p1.speed.x * p1.acceleration;
			}
			if (IsKeyDown(KEY_S)) {
				p1.position.y += p1.speed.y * p1.acceleration;
				p1.position.x += p1.speed.x * p1.acceleration;
			}
			if (IsKeyDown(KEY_D)) {
				p1.rotation += 0.2f;
			}
			if (IsKeyDown(KEY_A)) {
				p1.rotation -= 0.2f;
			}


			p1.speed.y = cos(p1.rotation);
			p1.speed.x = sin(p1.rotation);

			destRec.x = p1.position.x;
			destRec.y = p1.position.y;
			
		}
		void drawGame() {
			DrawTexturePro(ship, sourceRec,destRec ,colliderAllignment, p1.rotation ,WHITE);
			DrawCircleV(p1.position,p1.colliderRadius, GREEN);
		}
		void exitGame() {
			UnloadTexture(ship);
			currentstate = menustate;
		}
	}
}