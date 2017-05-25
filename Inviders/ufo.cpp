//=============================================================================
#include "Ufo.h";
#include <iostream>;
#include "CApp.h";
#include "Bomb.h"

using namespace std;
//=============================================================================
int		Ufo::flags = 0;
float	Ufo::maxSpeedX = 5;

//=============================================================================

Ufo::Ufo():CEntity(CApp::ufoImage, ENTITY_UFO,CApp::destroyingUfoImage) {
//	entityImage = cApp->ufoImage;
	CEntity::flags = Ufo::flags;
	CEntity::maxSpeedX = Ufo::maxSpeedX;
	CEntity::speedX = 2;
	bombTimer = SDL_GetTicks();
}

void Ufo::onLoop() {

	if (moveLeft) {
		accelX = -0.6;
	}
	else if (moveRight) {
		accelX = 0.6;
	}
	speedX += accelX * CFPS::FPSControl.GetSpeedFactor();
	speedY += accelY * CFPS::FPSControl.GetSpeedFactor();

	if (speedX > maxSpeedX)  speedX = maxSpeedX;
	if (speedX < -maxSpeedX) speedX = -maxSpeedX;
	if (speedY > maxSpeedY)  speedY = maxSpeedY;
	if (speedY < -maxSpeedY) speedY = -maxSpeedY;

	if(!isDying) tryingDropBomb();

	CEntity::onLoop();
}
//=============================================================================

void Ufo::isHitted()
{
	CEntity::flags += ENTITY_FLAG_GRAVITY;
	CEntity::isHitted();
}

//=============================================================================


bool Ufo::posValid(int NewX, int NewY) {
	if (NewX < 0) {
		moveLeft = false;
		moveRight = true;
		speedX = 0;
		return false;
	}
	if ((NewX + entityImage->width) > SCREEN_WIDTH) {
		moveLeft = true;
		moveRight = false;
		speedX = 0;
		return false;
	}
	return true;
}

void Ufo::tryingDropBomb()
{
	int newTimer = SDL_GetTicks();
	if ((newTimer - bombTimer) >= 500 + (1000 / level)) {
		Bomb* bomb = new Bomb();
		bomb->x = this->x+ this->entityImage->width;
		bomb->y = this->y+this->entityImage->height;
		CEntity::cEntityList.push_back(bomb);
		bombTimer = newTimer;
	}
}

