//==============================================================================
#include "CEntity.h"
#include <iostream>
#include "EntityImage.h"
#include "CApp.h"

using namespace std;
//==============================================================================

list<CEntity*>   CEntity::cEntityList;

//==============================================================================
CEntity::CEntity(EntityImage*	entityImage, int type) {
	this->entityImage = entityImage;
	this->type = type;

	this->dyingEntityImage = nullptr;
	this->isDying = false;
	this->aimType = 0;

	x = 0;
	y = 0;

	moveLeft = false;
	moveRight = false;

	dead = false;
	//flags = ENTITY_FLAG_GRAVITY;
	flags = 0;
	speedX = 0;
	speedY = 0;

	accelX = 0;
	accelY = 0;

	maxSpeedX = 5;
	maxSpeedY = 5;

	currentFrameCol = 0;
	currentFrameRow = 0;

	col_X = 0;
	col_Y = 0;

	col_Width = 0;
	col_Height = 0;
}

CEntity::CEntity(EntityImage * entityImage, int type, EntityImage * dyingEntityImage):
	CEntity(entityImage, type) 
{
	
	this->dyingEntityImage = dyingEntityImage;
}

CEntity::CEntity(EntityImage * entityImage, int type, int aimType):
	CEntity(entityImage, type)
{
	
	this->aimType = aimType;
}

//CEntity::CEntity(){}

//------------------------------------------------------------------------------
CEntity::~CEntity() {
}

EntityImage* CEntity::getEntityImage(){
	return entityImage;
}

//------------------------------------------------------------------------------
void CEntity::onLoop() {
	//We're not Moving
	
	if (flags & ENTITY_FLAG_GRAVITY) {
		accelY = 0.3f;
	}

	if (flags & ENTITY_FLAG_ROCKET) {
		accelY = -0.9f;
	}

	speedX += accelX * CFPS::FPSControl.GetSpeedFactor();
	speedY += accelY * CFPS::FPSControl.GetSpeedFactor();

	if (speedX > maxSpeedX)  speedX = maxSpeedX;
	if (speedX < -maxSpeedX) speedX = -maxSpeedX;
	if (speedY > maxSpeedY)  speedY = maxSpeedY;
	if (speedY < -maxSpeedY) speedY = -maxSpeedY;
	
	onAnimate();
	if (isDying) { // на последнем фрейме умирающего - дохнет
		if (anim_Control.getCurrentFrame() == (entityImage->maxFrames - 1))
			dead = true;
	}

	onMove(speedX, speedY);
	// проверка на попадания, если объект- пуля
	if (this->aimType != 0) checkHiting();
}

//------------------------------------------------------------------------------
void CEntity::onRender(SDL_Surface* Surf_Display) {
	if (entityImage->surf_Entity == NULL || Surf_Display == NULL) return;

	CSurface::onDraw(Surf_Display, entityImage->surf_Entity, x, y,
		currentFrameCol * entityImage->width, (currentFrameRow + anim_Control.getCurrentFrame()) * entityImage->height,
		entityImage->width, entityImage->height);
}

//------------------------------------------------------------------------------
void CEntity:: onCleanup() {
	entityImage = NULL;
	dyingEntityImage = NULL;
}

//------------------------------------------------------------------------------
void CEntity::onAnimate() {
	if (entityImage->hasLeftRight) {
		if (moveLeft) {
			currentFrameCol = 0;
		}
		else if (moveRight) {
			currentFrameCol = 1;
		}
	}
	anim_Control.onAnimate();
}

//------------------------------------------------------------------------------
void CEntity::onCollision(CEntity* Entity) {
}

//==============================================================================
void CEntity::onMove(float MoveX, float MoveY) {
	if (MoveX == 0 && MoveY == 0) return;

	double NewX = 0;
	double NewY = 0;

	MoveX *= CFPS::FPSControl.GetSpeedFactor();
	MoveY *= CFPS::FPSControl.GetSpeedFactor();

	if (MoveX != 0) {
		if (MoveX >= 0) 	NewX = CFPS::FPSControl.GetSpeedFactor();
		else 			NewX = -CFPS::FPSControl.GetSpeedFactor();
	}

	if (MoveY != 0) {
		if (MoveY >= 0) 	NewY = CFPS::FPSControl.GetSpeedFactor();
		else 			NewY = -CFPS::FPSControl.GetSpeedFactor();
	}

	while (true) {
		if (flags & ENTITY_FLAG_GHOST) {
			posValid((int)(x + NewX), (int)(y + NewY)); //We don't care about collisions, but we need to send events to other entities

			x += NewX;
			y += NewY;
		}
		else {
			if (posValid((int)(x + NewX), (int)(y))) {
				x += NewX;
			}
			else {
				speedX = 0;
			}

			if (posValid((int)(x), (int)(y + NewY))) {
				y += NewY;
			}
			else {
				speedY = 0;
			}
		}

		MoveX += -NewX;
		MoveY += -NewY;

		if (NewX > 0 && MoveX <= 0) NewX = 0;
		if (NewX < 0 && MoveX >= 0) NewX = 0;

		if (NewY > 0 && MoveY <= 0) NewY = 0;
		if (NewY < 0 && MoveY >= 0) NewY = 0;

		if (MoveX == 0) NewX = 0;
		if (MoveY == 0) NewY = 0;

		if (MoveX == 0 && MoveY == 0) 	break;
		if (NewX == 0 && NewY == 0) 	break;
	}
}

//------------------------------------------------------------------------------
void CEntity::stopMove() {
	if (speedX > 0) {
		accelX = -1;
	}

	if (speedX < 0) {
		accelX = 1;
	}

	if (speedX < 2.0f && speedX > -2.0f) {
		accelX = 0;
		speedX = 0;
	}
}

//==============================================================================
bool CEntity::collides(int oX, int oY, int oW, int oH) {
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	int tX = (int)x + col_X;
	int tY = (int)y + col_Y;

	left1 = tX;
	left2 = oX;

	right1 = left1 + entityImage->width - 1 - col_Width;
	right2 = oX + oW - 1;

	top1 = tY;
	top2 = oY;

	bottom1 = top1 + entityImage->height - 1 - col_Height;
	bottom2 = oY + oH - 1;


	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;

	if (right1 < left2) return false;
	if (left1 > right2) return false;

	return true;
}

bool CEntity::posValid(int NewX, int NewY) {
	if (NewX < 0) return false;
	if ((NewX + entityImage->width) > SCREEN_WIDTH) return false;
	return true;
}

void CEntity::cleanEntityList()
{
	for (CEntity* cEntity : CEntity::cEntityList) {
		if (cEntity) {
			cEntity->onCleanup();
			delete (cEntity);
			cEntity = NULL;
		}
	}
	CEntity::cEntityList.clear();
}

void CEntity::isHitted()
{
	cout << this->type<<" подбит !!!!!!!" << endl;
	isDying = true;
	CEntity::entityImage = CEntity::dyingEntityImage;//меняем Image, 
	currentFrameRow = 0; // текущий фрейм
	CEntity::anim_Control.maxFrames = this->entityImage->maxFrames; // количество фреймов 
	CEntity::type = ENTITY_GHOSTS;
	// включаем замедление
	if (speedX > 0) accelX = -0.2;
	else if (speedX < 0) accelX = 0.2;
}

void CEntity::checkHiting()
{
	for (CEntity* cEntity : CEntity::cEntityList) {
		if (cEntity) {
			if (cEntity->type == aimType && cEntity->isDying==false) {
				if (
					((this->x >= cEntity->x && this->x <= cEntity->x + cEntity->getEntityImage()->width) &&
					(this->y >= cEntity->y && this->y <= cEntity->y + cEntity->getEntityImage()->height)) ||
						((cEntity->x >= this->x && cEntity->x <= this->x + this->getEntityImage()->width) &&
					(cEntity->y >= this->y && cEntity->y <= this->y + this->getEntityImage()->height))
					)
				{
					// попали - пока просто отправим сообщение цель
					cEntity->isHitted();
					dead = true;
				}
			}
		};
	}
}
