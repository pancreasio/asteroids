#include "Game.h"
namespace flowspace {
	namespace gamespace {
		Texture2D ship;
		player p1;
		Vector2 colliderAllignment;
		int shipswidth = 237;
		int shipsheight = 291;
		float shipscale = 0.35f;
		Rectangle sourceRec = { 0.0f, 0.0f, (float)shipswidth, (float)shipsheight};
		Rectangle destRec = { (float)screenwidth / 2, (float)screenheight / 2, (float)shipswidth , (float)shipsheight};

		void initGameplay() {
			p1.position.x = screenwidth / 2;
			p1.position.y = screenheight/ 2;
			p1.acceleration = 4;
			p1.rotation = 0;
			p1.colliderRadius = 4;
			ship = LoadTexture("../res/ship.png");

		}

		void updateGame() {
			if (IsKeyPressed(KEY_Q)) {
				exitGame();
			}
			if (IsKeyDown(KEY_W)) {
				p1.position.y -= 2;
			}
			if (IsKeyDown(KEY_S)) {
				p1.position.y += 2;
			}
			if (IsKeyDown(KEY_D)) {
				p1.rotation -= 0.5f;
			}
			if (IsKeyDown(KEY_A)) {
				p1.rotation += 0.5f;
			}
			colliderAllignment = { p1.position.x + (237 / 2 * shipscale) ,p1.position.y - (291 / 2 * shipscale) };
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