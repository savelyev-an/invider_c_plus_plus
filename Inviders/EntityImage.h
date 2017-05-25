//=============================================================================

#pragma once

#include <SDL.h>
#include "CSurface.h";

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


