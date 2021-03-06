//=============================================================================

#pragma once

#include <SDL.h>

class CFPS {
public:
	static CFPS FPSControl;

private:
	int     OldTime;
	int     LastTime;

	float     SpeedFactor;

	int    NumFrames;
	int     Frames;

public:
	CFPS();

	void    OnLoop();

public:
	int     GetFPS();

	float   GetSpeedFactor();
};
