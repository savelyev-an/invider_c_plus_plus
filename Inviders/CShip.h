//=============================================================================
#ifndef _CSHIP_H_
#define _CSHIP_H_
#include "CEntity.h";
#include "CEntity.h";

//=============================================================================
class CShip : public CEntity {
private:
	//static EntityImage* commonEntityImage;
public:
	CShip();
	void onLoop();
	void shoot();
	void isHitted();
};

//=============================================================================

#endif

