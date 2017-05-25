//=============================================================================
#include "CEntity.h"

#pragma once
class Bullet : public CEntity {
public:
	static float	maxSpeedY;
	static int flags;

	Bullet();
	void onLoop();
};



