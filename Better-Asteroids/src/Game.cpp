#include "Game.h"
namespace flowspace {
	namespace gamespace {
		Texture2D ship;
		player p1;
		int shipswidth = 237;
		int shipsheight = 291;
		float shipscale = 0.15f;
		float u1, u2, v1, v2, auxiliarX, auxiliarY;
		bool isPaused = false;
		Rectangle sourceRec = { 0.0f, 0.0f, (float)shipswidth, (float)shipsheight };
		Rectangle destRec = { (float)screenwidth / 2, (float)screenheight / 2, (float)shipswidth * shipscale , (float)shipsheight * shipscale };
		Vector2 colliderAllignment = { (float)shipswidth /2 * shipscale , (float)shipsheight /2 * shipscale};

		void initGameplay() {
			p1.position.x = screenwidth / 2;
			p1.position.y = screenheight / 2; 
			p1.acceleration = 400.0;
			p1.rotation = 0;
			p1.colliderRadius = 4;
			ship = LoadTexture("res/ship.png");

		}

		void updateGame() {

			if (!isPaused) {
				auxiliarX = 2.0 / cos(DEG2RAD*p1.rotation); 
				auxiliarY = 2.0 / sin(DEG2RAD*p1.rotation);
				u1 = auxiliarX - p1.position.x , u2 = auxiliarY - p1.position.y, v1 = GetMouseX() - p1.position.x, v2 = GetMouseY() - p1.position.y;

				//p1.rotation = acos(((u1 * v1) + (u2 * v1))/sqrt(u1 * u1 + u2 * u2)*2);
				/*system("cls");
				std::cout << "X " << auxiliarX << std::endl;
				std::cout << "Y " << auxiliarY << std::endl;
				std::cout << "ROTACION FORRAAAA    " << p1.rotation;
				*/

				p1.speed.y = cos(DEG2RAD*p1.rotation);
				p1.speed.x = sin(DEG2RAD*p1.rotation);

				if (IsKeyPressed(KEY_Q)) {
					exitGame();
				}
				if (IsKeyDown(KEY_W)) {
					p1.position.y -= p1.speed.y * p1.acceleration * GetFrameTime();
					p1.position.x += p1.speed.x * p1.acceleration * GetFrameTime();
				}
				if (IsKeyDown(KEY_S)) {
					p1.position.y += p1.speed.y * p1.acceleration * GetFrameTime();
					p1.position.x -= p1.speed.x * p1.acceleration * GetFrameTime();
				}
				if (IsKeyDown(KEY_D)) {
					p1.rotation += 100.0f * GetFrameTime();
				}
				if (IsKeyDown(KEY_A)) {
					p1.rotation -= 100.0f * GetFrameTime();
				}

				destRec.x = p1.position.x;
				destRec.y = p1.position.y;
			}

			if (IsKeyPressed(KEY_P)) {
				isPaused = !isPaused;
			}

		}
		void drawGame() {
			DrawTexturePro(ship, sourceRec, destRec, colliderAllignment, p1.rotation, WHITE);
			DrawCircleV(p1.position, p1.colliderRadius, GREEN);
			DrawLine(p1.position.x, p1.position.y, auxiliarX, auxiliarY, BLUE);
			DrawLine(p1.position.x, p1.position.y, GetMouseX(), GetMouseY(), GREEN);
		}
		void exitGame() {
			UnloadTexture(ship);
			currentstate = menustate;
		}
	}
}