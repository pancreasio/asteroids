#include "Game.h"
namespace flowspace {
	namespace gamespace {
#define CLIPSIZE 5
#define ENEMYCOUNT 16
		//------------hardcoded variables and stuff, some are unnecesary but I don't want to break anything------
		Texture2D ship;
		player p1;
		button pauseButton;
		button exitButton;
		bullet bulletArray[CLIPSIZE];
		bullet auxBullet;
		asteroid enemyArray[ENEMYCOUNT];
		bool fireSwitch;
		unsigned const int shipswidth = 237;
		unsigned const int shipsheight = 291;
		unsigned const int bulletRadius = 4;
		unsigned int bulletCounter = 0;
		unsigned const int asteroidRadius = 60;
		unsigned const int timeToKill = 1;
		unsigned int activeEnemies;
		const float shipscale = 0.15f;
		float magicAngle = 0;
		float directionModule = 0;
		const float asteroidAcceleration = 100;
		float auxFloat = 0;
		const const float bulletSpeed = 800;
		bool isPaused = false;
		bool won = false;
		Vector2 directionVector, normalizedDirection, mousePosition;
		Rectangle sourceRec = { 0.0f, 0.0f, (float)shipswidth, (float)shipsheight };
		Rectangle destRec = { (float)screenwidth / 2, (float)screenheight / 2, (float)shipswidth * shipscale , (float)shipsheight * shipscale };
		Vector2 colliderAllignment = { (float)shipswidth / 2 * shipscale , (float)shipsheight / 2 * shipscale };

		void initGameplay() {
			//initialize lots of variables (some are unnecesary, but initGampeplay is not called very often so its not super ineficient)
			isPaused = false;
			won = false;
			p1.position.x = screenwidth / 2;
			p1.position.y = screenheight / 2;
			p1.defaultAcceleration = 400.0;
			p1.acceleration.x = 0.0;
			p1.acceleration.y = 0.0;
			p1.rotation = 0;
			p1.colliderRadius = 4;
			p1.speed.x = 0;
			p1.speed.y = 0;
			ship = LoadTexture("res/ship.png");
			pauseButton.position.x = screenwidth - 60.0;
			pauseButton.position.y = 0;
			pauseButton.size.x = 60.0;
			pauseButton.size.y = 60.0;
			exitButton.position.x = screenwidth / 2 - 120;
			exitButton.position.y = screenheight / 2 + 60;
			exitButton.size.x = 240;
			exitButton.size.y = 60.0;
			for (int i = 0; i < CLIPSIZE; i++) {
				bulletArray[i].active = false;
			}
			for (int i = 0; i < ENEMYCOUNT; i++) {
				enemyArray[i].active = false;
			}
			for (int i = 0; i < 4; i++) {
				enemyArray[i].active = true;
				enemyArray[i].stage = 3;
				enemyArray[i].colliderRadius = asteroidRadius;
				enemyArray[i].acceleration = asteroidAcceleration;
			}
			activeEnemies = 4;

			enemyArray[0].position.x = 30;
			enemyArray[0].position.y = 30;
			enemyArray[0].speed.x = 1;
			enemyArray[0].speed.y = 0;
			enemyArray[1].position.x = screenwidth - 30;
			enemyArray[1].position.y = 30;
			enemyArray[1].speed.x = 0;
			enemyArray[1].speed.y = 1;
			enemyArray[2].position.x = 30;
			enemyArray[2].position.y = screenheight - 30;
			enemyArray[2].speed.x = 0;
			enemyArray[2].speed.y = -1;
			enemyArray[3].position.x = screenwidth - 30;
			enemyArray[3].position.y = screenheight - 30;
			enemyArray[3].speed.x = -1;
			enemyArray[3].speed.y = 0;
		}

		void updateGame() {

			mousePosition = { (float)GetMouseX(),(float)GetMouseY() };
			activeEnemies = ENEMYCOUNT;
			if (!isPaused) {

				//---------------------------------player rotation logic-----------------------------------

				directionVector.x = mousePosition.x - p1.position.x;
				directionVector.y = mousePosition.y - p1.position.y;

				magicAngle = RAD2DEG * atan(directionVector.y / directionVector.x);

				if (directionVector.x < 0 && directionVector.y < 0) { //Quadrant II
					magicAngle += 270.0;
				}
				if (directionVector.y >= 0 && directionVector.x >= 0) { //Quadrant IV
					magicAngle += 90.0;
				}
				if (directionVector.x < 0 && directionVector.y >= 0) { //QuadrantIII
					magicAngle += 270.0;
				}
				if (directionVector.x >= 0 && directionVector.y < 0) { //Quadrant I
					magicAngle += 90;
				}

				p1.rotation = magicAngle;

				//-------------------------------player movement logic-------------------------------

				directionModule = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
				normalizedDirection.x = directionVector.x / directionModule;
				normalizedDirection.y = directionVector.y / directionModule;

				p1.acceleration.x = normalizedDirection.x * p1.defaultAcceleration;
				p1.acceleration.y = normalizedDirection.y * p1.defaultAcceleration;

				p1.position.x += p1.speed.x * GetFrameTime();
				p1.position.y += p1.speed.y * GetFrameTime();

				if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
					p1.speed.x += p1.acceleration.x * 0.0012;
					p1.speed.y += p1.acceleration.y * 0.0012;
				}
				if (p1.position.x < 0) {
					p1.position.x = screenwidth - 1;
				}
				if (p1.position.x > screenwidth) {
					p1.position.x = 1;
				}
				if (p1.position.y < 0) {
					p1.position.y = screenheight - 1;
				}
				if (p1.position.y > screenheight) {
					p1.position.y = 1;
				}

				//-------------------------------player collider logic------------------
				for (int i = 0; i < ENEMYCOUNT; i++){
					if (enemyArray[i].active) {
						if (abs(p1.position.x - enemyArray[i].position.x) < enemyArray[i].colliderRadius&& abs(p1.position.y - enemyArray[i].position.y) < enemyArray[i].colliderRadius) {
							finishGame();
						}
					}
				}
				

				//----------------------------------firing logic---------------------------

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					fireSwitch = false;
					for (bulletCounter = 0; bulletCounter < CLIPSIZE; bulletCounter++) {
						if (!bulletArray[bulletCounter].active) {
							bulletArray[bulletCounter].position = p1.position;
							bulletArray[bulletCounter].active = true;
							bulletArray[bulletCounter].birthDate = GetTime();
							bulletArray[bulletCounter].defaultAcceleration = bulletSpeed;
							bulletArray[bulletCounter].colliderRadius = bulletRadius;
							bulletArray[bulletCounter].acceleration.x = normalizedDirection.x * bulletArray[bulletCounter].defaultAcceleration;
							bulletArray[bulletCounter].acceleration.y = normalizedDirection.y * bulletArray[bulletCounter].defaultAcceleration;
							bulletCounter = CLIPSIZE;
							fireSwitch = true;
						}

						if (!fireSwitch) {
							if (bulletCounter == CLIPSIZE) {
								for (int i = 0; i < CLIPSIZE - 1; i++)
								{
									auxBullet = bulletArray[i + 1];
									bulletArray[i + 1] = bulletArray[i];
								}
								bulletArray[0].position = p1.position;
								bulletArray[0].active = true;
								bulletArray[0].birthDate = GetTime();
								bulletArray[0].defaultAcceleration = bulletSpeed;
								bulletArray[0].colliderRadius = bulletRadius;
								bulletArray[0].acceleration.x = normalizedDirection.x * bulletArray[0].defaultAcceleration;
								bulletArray[0].acceleration.y = normalizedDirection.y * bulletArray[0].defaultAcceleration;
								fireSwitch = true;
							}
						}
					}
				}

				for (int i = 0; i < CLIPSIZE; i++) {
					if (bulletArray[i].active) {
						bulletArray[i].position.x += bulletArray[i].acceleration.x * GetFrameTime();
						bulletArray[i].position.y += bulletArray[i].acceleration.y * GetFrameTime();
						if (bulletArray[i].position.x < 0) {
							bulletArray[i].position.x = screenwidth - 1;
						}
						if (bulletArray[i].position.x > screenwidth) {
							bulletArray[i].position.x = 1;
						}
						if (bulletArray[i].position.y < 0) {
							bulletArray[i].position.y = screenheight - 1;
						}
						if (bulletArray[i].position.y > screenheight) {
							bulletArray[i].position.y = 1;
						}
						if (GetTime() - bulletArray[i].birthDate > timeToKill) {
							bulletArray[i].active = false;
						}
					}
				}
				//-------------------------------asteroid logic-----------------------------
				for (int i = 0; i < ENEMYCOUNT; i++) {
					if (enemyArray[i].active) {
						enemyArray[i].position.x += enemyArray[i].speed.x *enemyArray[i].acceleration * GetFrameTime();
						enemyArray[i].position.y += enemyArray[i].speed.y *enemyArray[i].acceleration * GetFrameTime();
						if (enemyArray[i].position.x < 0) {
							enemyArray[i].position.x = screenwidth - 1;
						}
						if (enemyArray[i].position.x > screenwidth) {
							enemyArray[i].position.x = 1;
						}
						if (enemyArray[i].position.y < 0) {
							enemyArray[i].position.y = screenheight - 1;
						}
						if (enemyArray[i].position.y > screenheight) {
							enemyArray[i].position.y = 1;
						}
					}
					else{
						activeEnemies--;
					}
				}
				//----------------------------- bullet->asteroid collider logic---------------------------
				for (int i = 0; i < CLIPSIZE; i++) {
					if (bulletArray[i].active) {
						for (int i2 = 0; i2 < ENEMYCOUNT; i2++) {
							if(enemyArray[i2].active){
								if (abs(bulletArray[i].position.x - enemyArray[i2].position.x) < enemyArray[i2].colliderRadius && abs(bulletArray[i].position.y - enemyArray[i2].position.y) < enemyArray[i2].colliderRadius) {
									bulletArray[i].active = false;
									if (enemyArray[i2].stage > 1) {
										enemyArray[i2].colliderRadius = enemyArray[i2].colliderRadius / 2;
										enemyArray[i2].acceleration = enemyArray[i2].acceleration * 1.60;
										enemyArray[i2].stage--;
										auxFloat = enemyArray[i2].speed.x;
										enemyArray[i2].speed.x = enemyArray[i2].speed.y;
										enemyArray[i2].speed.y = auxFloat;
										for (int i3 = 0; i3 < ENEMYCOUNT; i3++) {
											if (!enemyArray[i3].active) {
												enemyArray[i3] = enemyArray[i2];
												enemyArray[i3].speed.x = -1 * enemyArray[i3].speed.x;
												enemyArray[i3].speed.y = -1 * enemyArray[i3].speed.y;
											}
										}
									}
									else {
										enemyArray[i2].active = false;
									}
								}
							}
						}
					}
				}
				//-----------------------------------win logic------------------------------
				if (activeEnemies <= 0) {
					won = true;
					finishGame();
				}
				//---------------------------------sprite logic-----------------------------
				destRec.x = p1.position.x;
				destRec.y = p1.position.y;
			}

			//-----------------------------------------pause menu-----------------------------
			else {
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
					if (pauseButton.position.y <= mousePosition.y && mousePosition.y <= pauseButton.position.y + pauseButton.size.y) {
						isPaused = !isPaused;
					}
				}
			}

		}


		void drawGame() {
			DrawTexturePro(ship, sourceRec, destRec, colliderAllignment, p1.rotation, WHITE);
			for (int i = 0; i < CLIPSIZE; i++) {
				if (bulletArray[i].active) {
					DrawCircle(bulletArray[i].position.x, bulletArray[i].position.y, bulletArray[i].colliderRadius, YELLOW);
				}
			}
			for (int i = 0; i < ENEMYCOUNT; i++) {
				if (enemyArray[i].active) {
					DrawCircle(enemyArray[i].position.x, enemyArray[i].position.y, enemyArray[i].colliderRadius, GRAY);
				}
			}
			DrawRectangle(pauseButton.position.x + pauseButton.size.x / 6, pauseButton.position.y + 10, pauseButton.size.x / 4, pauseButton.size.y - 20, WHITE);
			DrawRectangle(pauseButton.position.x + 4 * pauseButton.size.x / 6, pauseButton.position.y + 10, pauseButton.size.x / 4, pauseButton.size.y - 20, WHITE);
			if (isPaused) {
				DrawText("PAUSED", screenwidth / 2 - 120, screenheight / 2 - 30, 60, WHITE);
				DrawRectangle(exitButton.position.x, exitButton.position.y, exitButton.size.x, exitButton.size.y, WHITE);
				DrawText("Exit Game", exitButton.position.x + 12, exitButton.position.y + 10, 45, BLACK);
			}
		}
		void exitGame() {
			UnloadTexture(ship);
			menuspace::initMenu();
			currentstate = menustate;
		}
		void finishGame() {
			UnloadTexture(ship);
			gameoverspace::initGameOver();
			currentstate = gameoverstate;
		}
	}
}