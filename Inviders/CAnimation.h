#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include <SDL.h>

class CAnimation {
private:
	int    currentFrame;

	int     frameInc;

	int     frameRate; //Milliseconds

	long    oldTime;

public:
	int    maxFrames;

	bool    oscillate;

	CAnimation();

	void onAnimate();

	void setFrameRate(int rate);

	void setCurrentFrame(int frame);

	int getCurrentFrame();
};

#endif