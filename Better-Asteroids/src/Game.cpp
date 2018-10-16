#include "Game.h"
namespace flowspace {
	namespace gamespace {
		Texture2D ship;
		player p1;
		button pauseButton;
		button exitButton;
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
			isPaused = false;
			p1.position.x = screenwidth / 2;
			p1.position.y = screenheight / 2; 
			p1.defaultAcceleration = 400.0;
			p1.acceleration.x = 0.0;
			p1.acceleration.y = 0.0;
			p1.rotation = 0;
			p1.colliderRadius = 4;
			ship = LoadTexture("res/ship.png");
			pauseButton.position.x = screenwidth - 60.0;
			pauseButton.position.y = 0;
			pauseButton.size.x = 60.0;
			pauseButton.size.y = 60.0;
			exitButton.position.x = screenwidth /2 - 120;
			exitButton.position.y = screenheight /2 + 60;
			exitButton.size.x = 240;
			exitButton.size.y = 60.0;

		}

		void updateGame() {

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };

			if (!isPaused) {
				
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

				p1.acceleration.x = normalizedDirection.x * p1.defaultAcceleration;
				p1.acceleration.y = normalizedDirection.y * p1.defaultAcceleration;

				if (IsKeyPressed(KEY_Q)) {
					exitGame();
				}
				if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
					p1.position.y += p1.acceleration.y * GetFrameTime();
					p1.position.x += p1.acceleration.x * GetFrameTime();
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
			else{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					if (exitButton.position.x <= mousePosition.x && mousePosition.x <= exitButton.position.x + exitButton.size.x) {
						if (exitButton.position.y <= mousePosition.y && mousePosition.y <= exitButton.position.y + exitButton.size.y) {
							exitGame();
						}
					}
				}
			}

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (pauseButton.position.x <= mousePosition.x && mousePosition.x <= pauseButton.position.x + pauseButton.size.x) {
					if (pauseButton.position.y <= mousePosition.y && mousePosition.y <=pauseButton.position.y + pauseButton.size.y) {
						isPaused = !isPaused;
					}
				}
			}

		}
		void drawGame() {
			DrawTexturePro(ship, sourceRec, destRec, colliderAllignment, p1.rotation, WHITE);
			DrawCircleV(p1.position, p1.colliderRadius, GREEN);
			DrawLine(p1.position.x, p1.position.y, GetMouseX(), GetMouseY(), GREEN);
			DrawRectangle(pauseButton.position.x + pauseButton.size.x / 6, pauseButton.position.y +10 , pauseButton.size.x / 4, pauseButton.size.y -20, WHITE);
			DrawRectangle(pauseButton.position.x + 4* pauseButton.size.x / 6, pauseButton.position.y + 10, pauseButton.size.x / 4, pauseButton.size.y -20, WHITE);
			if (isPaused) {
				DrawText("PAUSED", screenwidth / 2 - 120, screenheight / 2 - 30, 60, WHITE);
				DrawRectangle(exitButton.position.x,exitButton.position.y,exitButton.size.x,exitButton.size.y,WHITE);
				DrawText("Exit Game", exitButton.position.x +12, exitButton.position.y+10, 45, BLACK);
			}
		}
		void exitGame() {
			UnloadTexture(ship);
			currentstate = menustate;
		}
	}
}