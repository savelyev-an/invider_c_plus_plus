#include "EntityImage.h"


bool EntityImage::onLoad(char* File, int Width, int Height, int MaxFrames) {
	if ((surf_Entity = CSurface::onLoad(File)) == NULL) {
		return false;
	}
	CSurface::transparent(surf_Entity, 255, 255, 255);
	this->width = Width;
	this->height = Height;
	this->maxFrames = MaxFrames;
	return true;
}

void EntityImage::onCleanUp()
{
	if (surf_Entity) {
		SDL_FreeSurface(surf_Entity);
	}
	surf_Entity = NULL;
}
