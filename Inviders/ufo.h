//=============================================================================
#pragma once

#include "CEntity.h";

class Ufo : public CEntity {
public:
	static int		flags;
	static float	maxSpeedX;
	int level;
	Ufo();

	void onLoop();

	void isHitted();
	
private:
	bool 	posValid(int NewX, int NewY);
	int bombTimer;
	void  tryingDropBomb();

};

