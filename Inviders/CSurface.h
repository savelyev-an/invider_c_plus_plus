#ifndef _CSurfaceH_
#define _CSurfaceH_

#include <SDL.h>
#include <SDL_image.h>

class CSurface {
public:
	CSurface();

public:
	static SDL_Surface* onLoad(const char* File);
	static bool onDraw(SDL_Surface* surf_Dest, SDL_Surface* surf_Src, int x, int y); // простое рисование
	static bool onDraw(SDL_Surface* surf_Dest, SDL_Surface* surf_Src, int x, int y, int x2, int y2, int w, int h); //рисование куска
	static bool transparent(SDL_Surface* surf_Dest, int R, int G, int B);
};

#endif
