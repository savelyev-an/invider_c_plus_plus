//==============================================================================
#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <list>
#include <vector>

#include "CAnimation.h"
#include "CFPS.h"
#include "CSurface.h"

//==============================================================================

//==============================================================================
class Entity {

public:
	Entity() {};

	//virtual bool onLoad(char* File, int Width, int Height, int MaxFrames)  = 0;

	virtual void onLoop() =0;

	virtual void onRender(SDL_Surface* Surf_Display) =0;

	virtual void onCleanup() =0;

	//static void cleanEntityList() {};

	virtual void onAnimate() =0;

	//virtual void onCollision(Entity* Entity) =0;

	virtual void onMove(float MoveX, float MoveY) =0;

	virtual void stopMove() =0;

	virtual bool collides(int oX, int oY, int oW, int oH) =0;

	virtual bool isDead() =0;

	virtual void isHitted() = 0;

	virtual void checkHiting()=0;

};

#endif

