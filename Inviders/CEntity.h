//=============================================================================

#pragma once


#include <vector>
#include <list> 
#include "CAnimation.h"
#include "CFPS.h"
#include "CSurface.h"
#include "Entity.h"
#include "EntityImage.h"

//==============================================================================
enum {
	ENTITY_FLAG_NONE = 0,
	ENTITY_FLAG_GRAVITY = 0x00000001,
	ENTITY_FLAG_GHOST = 0x00000002,
	ENTITY_FLAG_MAPONLY = 0x00000004,
	ENTITY_FLAG_ROCKET = 0x00000008
};

enum {
	ENTITY_GHOSTS = 0,
	ENTITY_SHIP = 0x00000001,
	ENTITY_UFO = 0x00000002,
	ENTITY_BULLET = 0x00000003,
	ENTITY_BOMB = 0x00000004,

};

//==============================================================================

class CEntity : public Entity{

protected:
	CAnimation      anim_Control;
	EntityImage*	entityImage;
	EntityImage*    dyingEntityImage;

public:
	static std::list<CEntity*>    cEntityList;

	float	x;
	float	y;

	bool	moveLeft;
	bool	moveRight;


public:
	bool	isDying;
	bool	dead;
	int		flags;
	int		type;

protected:
	int		aimType;

	float	speedX;
	float	speedY;

	float	accelX;
	float	accelY;


public:
	float	maxSpeedX;
	float	maxSpeedY;

protected:
	int		currentFrameCol;
	int		currentFrameRow;
	int		col_X;
	int		col_Y;
	int		col_Width;
	int		col_Height;

public:
	CEntity(EntityImage*	entityImage, int type);

	CEntity(EntityImage*	entityImage, int type, EntityImage*	dyingEntityImage);

	CEntity(EntityImage*	entityImage, int type, int aimType);

	virtual ~CEntity();

	virtual  EntityImage* getEntityImage();

	virtual void onLoop();

	virtual void onRender(SDL_Surface* Surf_Display);

	virtual void onCleanup();

	virtual void onAnimate();

	void    onMove(float MoveX, float MoveY);

	void 	stopMove();

	bool isDead() { return dead; };

	static void cleanEntityList();

	virtual void isHitted();

	virtual void checkHiting();

private:
	virtual bool 	posValid(int NewX, int NewY);

};
