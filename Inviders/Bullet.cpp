//=============================================================================
#include "Bullet.h";
#include <iostream>;
#include "CApp.h";

using namespace std;
//=============================================================================
float	Bullet::maxSpeedY = 20;
int     Bullet::flags= ENTITY_FLAG_GRAVITY;
//=============================================================================

Bullet::Bullet(): CEntity(CApp::bulletImage, ENTITY_BULLET, ENTITY_UFO) {
	CEntity::flags = Bullet::flags;
	CEntity::maxSpeedY = Bullet::maxSpeedY;
	CEntity::speedY = -18;
}

void Bullet::onLoop() {
	// при выходе за границы экрана - умираем  
	if (y < -entityImage->height) this->dead = true;
	CEntity::onLoop();
}
//=============================================================================



