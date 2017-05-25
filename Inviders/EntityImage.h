#ifndef _EntityImageH_
#define _EntityImageH_

#include <SDL.h>
#include "CSurface.h";
//#include <SDL_image.h>

class EntityImage {
public:
	SDL_Surface*    surf_Entity;
	int				width;
	int				height;
	int				maxFrames;
	bool			hasLeftRight;

public:
	bool onLoad(char* File, int Width, int Height, int MaxFrames);
	void onCleanUp();
};

#endif

