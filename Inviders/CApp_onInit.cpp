#include "CApp.h";

bool CApp::onInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}
	if ((surf_Display = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HIGTH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		return false;
	}

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	reset();

	if ((surf_sea = CSurface::onLoad(merge(systemPath, "sea.bmp"))) == NULL) {
		return false;
	}
		
	if (CApp::shipImage->onLoad(merge(systemPath, "ShipDouble.bmp"), 100, 40, 0) == false) {
		return false;
	} 
	shipImage->hasLeftRight = true;

	ship->x = 400;
	ship->y = 520;
	
	CEntity::cEntityList.push_back(ship);
	// загрузить картинку dyingShipImage
	if (CApp::dyingShipImage->onLoad(merge(systemPath, "DyingShipDouble.bmp"), 100, 60, 14) == false) {
		return false;
	}
	dyingShipImage->hasLeftRight = true;

	// загрузить картинку и настроить bullet
	if (CApp::bulletImage->onLoad(merge(systemPath, "bullet.bmp"), 6, 15, 0) == false) {
		return false;
	}
	// загрузить картинку и настроить bomb
	if (CApp::bombImage->onLoad(merge(systemPath, "bomb.bmp"), 10, 10, 0) == false) {

		return false;
	}
	//загрузить картинку и настроить ufo
	if (CApp::ufoImage->onLoad(merge(systemPath, "ufo.bmp"), 100, 26, 0) == false) {
		return false;
	}
	
	// загрузить картинку destroyingUfoImage
	if (CApp::destroyingUfoImage->onLoad(merge(systemPath, "destroying_ufo.bmp"), 100, 26, 12) == false) {
		return false;
	}

	return true;
}
