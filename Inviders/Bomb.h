#pragma once
#include "CEntity.h"
class Bomb : public CEntity
{
public:
	static float	maxSpeedY;
	static int flags;
	
	Bomb();
	void onLoop();
};

