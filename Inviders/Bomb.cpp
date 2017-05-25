//=============================================================================
#include "Bomb.h"
#include "CApp.h";
using namespace std;

//=============================================================================
float	Bomb::maxSpeedY = 10;
int     Bomb::flags = ENTITY_FLAG_GRAVITY;
//=============================================================================

Bomb::Bomb() : CEntity(CApp::bombImage, ENTITY_BOMB, ENTITY_SHIP) {
	CEntity::flags = Bomb::flags;
	CEntity::maxSpeedY = Bomb::maxSpeedY;
	CEntity::speedY = 0;
}

void Bomb::onLoop() {
	// при выходе за границы экрана - умираем  
	if (y > 560) this->dead = true;
	CEntity::onLoop();
}
//=============================================================================

