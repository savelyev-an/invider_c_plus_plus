//=============================================================================

#pragma once

#include <SDL.h>

#include "CSurface.h"
#include "EntityImage.h"
#include "CAnimation.h"
#include "C_Event.h";
#include "CEntity.h";
#include "CShip.h";



const int SCREEN_WIDTH=800;
const int SCREEN_HIGTH=600;

enum {
	GRID_TYPE_NONE = 0,
	GRID_TYPE_X,
	GRID_TYPE_O
};

class CApp : public C_Event {
private:
	bool running;

	char* systemPath;

	SDL_Surface*    surf_Display;

	SDL_Surface*	surf_sea;

	CShip*		  ship;

	void newUfo();
public:
	int level=1;
	int timer;

	static EntityImage*  shipImage;
	static EntityImage*  dyingShipImage;
	static EntityImage*  ufoImage;
	static EntityImage*  bulletImage;
	static EntityImage*  destroyingUfoImage;
	static EntityImage*  bombImage;

	CApp();

	void setSystemPath(char* systemPath);

	int onExecute();

	bool onInit();

	void onEvent(SDL_Event* event);

		void onExit();

		void CApp::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

		void CApp::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	void onLoop();

	void onRender();

	void onCleanup();

	void reset();

	static char* CApp::getPath(char* fullFileName);

	static char* CApp::merge(char * str1, char * str2);
};
