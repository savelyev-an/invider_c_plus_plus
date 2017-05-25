
#include <list>
#include <vector>
//=============================================================================

#pragma once

#include "CAnimation.h"
#include "CFPS.h"
#include "CSurface.h"

class Entity {

public:
	Entity() {};

	virtual void onLoop() =0;

	virtual void onRender(SDL_Surface* Surf_Display) =0;

	virtual void onCleanup() =0;

	virtual void onAnimate() =0;

	virtual void onMove(float MoveX, float MoveY) =0;

	virtual void stopMove() =0;

	virtual bool isDead() =0;

	virtual void isHitted() = 0;

	virtual void checkHiting()=0;

};


