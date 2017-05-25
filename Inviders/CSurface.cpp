#include "CSurface.h"

CSurface::CSurface() {
}

SDL_Surface* CSurface::onLoad(const char* file) {
	SDL_Surface* surf_Temp = NULL;
	SDL_Surface*surf_Return = NULL;

	if ((surf_Temp = SDL_LoadBMP(file)) == NULL) {
		return NULL;
	}

	surf_Return = SDL_DisplayFormat(surf_Temp);
	SDL_FreeSurface(surf_Temp);

	return surf_Return;
}

bool CSurface::onDraw(SDL_Surface* surf_Dest, SDL_Surface* surf_Src, int x, int y) {
	if (surf_Dest == NULL || surf_Src == NULL) {
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;

	SDL_BlitSurface(surf_Src, NULL, surf_Dest, &destR);

	return true;
}

bool CSurface::onDraw(SDL_Surface* surf_Dest, SDL_Surface* surf_Src, int x, int y, int x2, int y2, int w, int h) {
	if (surf_Dest == NULL || surf_Src == NULL) {
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;

	SDL_Rect srcR;

	srcR.x = x2;
	srcR.y = y2;
	srcR.w = w;
	srcR.h = h;

	SDL_BlitSurface(surf_Src, &srcR, surf_Dest, &destR);

	return true;
}

bool CSurface::transparent(SDL_Surface* surf_Dest, int R, int G, int B) {
	if (surf_Dest == NULL) {
		return false;
	}

	SDL_SetColorKey(surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surf_Dest->format, R, G, B));

	return true;
}