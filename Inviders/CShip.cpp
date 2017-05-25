//=============================================================================
#include "CShip.h";
#include <iostream>;
#include "Bullet.h";
#include "CApp.h"
#include "Entity.h";

using namespace std;

CShip::CShip() : CEntity(CApp::shipImage, ENTITY_SHIP, CApp::dyingShipImage) {
}

void CShip::onLoop()
{
	if (moveLeft == false && moveRight == false) {
		stopMove();
	}

	if (moveLeft) {
		accelX = -0.5;
	}
	else

		if (moveRight) {
			accelX = 0.5;
		}

	CEntity::onLoop();
}



void CShip::shoot()
{
	Bullet* bullet = new Bullet();
	bullet->CEntity::x = this->CEntity::x + this->entityImage->width / 2;
	bullet->CEntity::y = this->CEntity::y + (bullet->CEntity::getEntityImage())->height;
	CEntity::cEntityList.push_back(bullet);
}

void CShip::isHitted()
{
	if (!isDying) {
		CEntity::isHitted();
		y -= 20;
	}
}


