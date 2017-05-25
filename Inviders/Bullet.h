//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "CEntity.h";
//=============================================================================
class Bullet : public CEntity {
public:
	static float	maxSpeedY;
	static int flags;

	Bullet();
	void onLoop();
};

//=============================================================================

#endif
