#include "Game.h"
namespace flowspace {
	namespace gamespace {
		Texture2D ship;
		player p1;
		int shipswidth = 237;
		int shipsheight = 291;
		float shipscale = 0.15f;
		float magicAngle = 0;
		float directionModule = 0;
		bool isPaused = false;
		Vector2 directionVector, normalizedDirection, mousePosition;
		Rectangle sourceRec = { 0.0f, 0.0f, (float)shipswidth, (float)shipsheight };
		Rectangle destRec = { (float)screenwidth / 2, (float)screenheight / 2, (float)shipswidth * shipscale , (float)shipsheight * shipscale };
		Vector2 colliderAllignment = { (float)shipswidth /2 * shipscale , (float)shipsheight /2 * shipscale};

		void initGameplay() {
			p1.position.x = screenwidth / 2;
			p1.position.y = screenheight / 2; 
			p1.defaultAcceleration = 400.0;
			p1.acceleration.x = 0.0;
			p1.acceleration.y = 0.0;
			p1.rotation = 0;
			p1.colliderRadius = 4;
			ship = LoadTexture("res/ship.png");

		}

		void updateGame() {

			if (!isPaused) {
				
				mousePosition = {(float)GetMouseX(),(float)GetMouseY()};
				directionVector.x = mousePosition.x - p1.position.x;
				directionVector.y = mousePosition.y - p1.position.y;

				magicAngle = RAD2DEG * atan(directionVector.y / directionVector.x);

				if (directionVector.x <0 && directionVector.y <0) { //cuadrante II
					magicAngle += 270.0;
				}
				if (directionVector.y >= 0 && directionVector.x >= 0) { //cuadrante IV
					magicAngle += 90.0;
				}
				if (directionVector.x < 0 && directionVector.y >= 0) { //cuadrante III
					magicAngle += 270.0;
				}
				if (directionVector.x >= 0 && directionVector.y < 0) { //cuadrante I
					magicAngle += 90;
				}

				p1.rotation = magicAngle;

				directionModule = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
				normalizedDirection.x = directionVector.x / directionModule;
				normalizedDirection.y = directionVector.y / directionModule;

				p1.acceleration.x = abs(normalizedDirection.x * p1.defaultAcceleration);
				p1.acceleration.y = abs(normalizedDirection.y * p1.defaultAcceleration);

				p1.speed.y = cos(DEG2RAD*p1.rotation);
				p1.speed.x = sin(DEG2RAD*p1.rotation);

				if (IsKeyPressed(KEY_Q)) {
					exitGame();
				}
				if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
					p1.position.y -= p1.speed.y * p1.defaultAcceleration * GetFrameTime();
					p1.position.x += p1.speed.x * p1.defaultAcceleration * GetFrameTime();
				}
				std::system("cls");
				std::cout <<"aceleracion x: " << p1.acceleration.x << std::endl;
				std::cout <<"aceleracion y: " << p1.acceleration.y << std::endl;
				std::cout << "vector x: " << directionVector.x << std::endl;
				std::cout << "vector y: " << directionVector.y << std::endl;
				std::cout << "vector normalizado x: " << normalizedDirection.x << std::endl;
				std::cout << "vector normalizado y: " << normalizedDirection.y << std::endl;

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
			DrawLine(p1.position.x, p1.position.y, GetMouseX(), GetMouseY(), GREEN);
		}
		void exitGame() {
			UnloadTexture(ship);
			currentstate = menustate;
		}
	}
}