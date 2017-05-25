#include "CApp.h"
#include <iostream>;
#include <cstring>;
#include "CEntity.h";
#include "CShip.h";
#include "Ufo.h"
#include "Bomb.h"
//===============================================
EntityImage*  CApp::shipImage;// = new EntityImage();;
EntityImage*  CApp::dyingShipImage;// = new EntityImage();;
EntityImage*  CApp::ufoImage;// = new EntityImage();;
EntityImage*  CApp::bulletImage;// = new EntityImage();;
EntityImage*  CApp::destroyingUfoImage;// = new EntityImage();;
EntityImage*  CApp::bombImage;// = new EntityImage();;

//===============================================

using namespace std;

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

void CApp::setSystemPath(char * systemPath)
{
	this->systemPath = systemPath;
}

void CApp::newUfo()
{
	bool created = false;
	//while (!created) {
		int newY = rand()%370+20;
		bool isPlaceFree = true;
		for (CEntity* cEntity : CEntity::cEntityList) {
			if (cEntity) {
				if (cEntity->type == ENTITY_UFO) {
					if (abs(cEntity->y - newY) < 30) {
						isPlaceFree = false;
						break;
					}
				}
			}
		}
		if (isPlaceFree) {
			Ufo *ufo = new Ufo();
			ufo->x = 1;
			ufo->y = newY;
			ufo->moveRight = true;
			ufo->level = this->level;
			CEntity::cEntityList.push_back(ufo);
		}
	//}
}

CApp::CApp() {
	CApp::shipImage = new EntityImage();;
	CApp::dyingShipImage = new EntityImage();
	CApp::ufoImage = new EntityImage();;
	CApp::bulletImage = new EntityImage();;
	CApp::destroyingUfoImage = new EntityImage();;
	CApp::bombImage = new EntityImage();

	surf_Display = NULL;
	surf_sea = NULL;

	ship= new CShip();
	
	running = true;
}

int CApp::onExecute() {
	if (onInit() == false) {
		return -1;
	}

	SDL_Event event;

	while (running) {
		// рекомендовано использовать SDL_WaitEvent вместо SDL_PollEvent
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}
		onLoop();
		onRender();
	}

	onCleanup();

	return 0;
}



void CApp::onEvent(SDL_Event* Event) {
	C_Event::onEvent(Event);
}

//==============================================================================
void CApp::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_LEFT: {
		ship->moveLeft = true;
		break;
	}

	case SDLK_RIGHT: {
		ship->moveRight = true;
		break;
	}
	
	case SDLK_ESCAPE: {
		onExit();
		break;
	}

		default: {
	}
	}
}

//------------------------------------------------------------------------------
void CApp::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_LEFT: {
		ship->moveLeft = false;
		break;
	}

	case SDLK_RIGHT: {
		ship->moveRight = false;
		break;
	}

	case SDLK_SPACE: {
		ship->shoot();
		break;
	}
	
	default: {
	}
	}
}

//------------------------------------------------------------------------------

void CApp::onLoop()
{
	for (CEntity* cEntity : CEntity::cEntityList) {
		if (cEntity) cEntity->onLoop();
	}

	CFPS::FPSControl.OnLoop();
	int newTimer= SDL_GetTicks();
	if ((newTimer - timer) >= 500+(5000 / level)) {
		newUfo();
		timer = newTimer;
	}

	char Buffer[255];
	sprintf(Buffer, "%d", CFPS::FPSControl.GetFPS());
	SDL_WM_SetCaption(Buffer, Buffer);
	if (ship->dead) onExit();
}

void CApp::onRender()
{
	CSurface::onDraw(surf_Display, surf_sea, 0, 0);
	
	std::list<CEntity*>    entityListToDelete;

	//cout << "Объектов в списке: " << Entity::entityList.size()<<endl;
	for (CEntity* cEntity : CEntity::cEntityList) {
		if (cEntity) cEntity->onRender(surf_Display);
		if (cEntity->isDead()) entityListToDelete.push_back(cEntity); // сохраним в список на удаление
	}

	SDL_Flip(surf_Display);

	//очистка улетевших
	for (CEntity * cEntityToDelete : entityListToDelete) {
		cEntityToDelete->onCleanup();
		CEntity::cEntityList.remove(cEntityToDelete);
	}
}

void CApp::onCleanup()
{
	//чистим поверхности
	SDL_FreeSurface(surf_sea);
	SDL_FreeSurface(surf_Display);
	//чистим все Entity
	CEntity::cleanEntityList();
	
	//чистим все EntityImage 	
	shipImage->onCleanUp();
	bulletImage->onCleanUp();
	ufoImage->onCleanUp();
	destroyingUfoImage->onCleanUp();
	dyingShipImage->onCleanUp();

	delete (surf_sea);
	delete (surf_Display);
	delete (shipImage);
	delete (dyingShipImage);
	delete (bulletImage);
	delete (ufoImage);
	delete (destroyingUfoImage);



	SDL_Quit();
}

void CApp::onExit() {
	running = false;
}

void CApp::reset() {
}




char* CApp::getPath(char* fullFileName)
{
	char * pos = strrchr(fullFileName, '\\');
	//cout << pos<< "   "<<strlen(argv[0]) <<endl;
	int len = pos - fullFileName + 2; // будущая длина пути
	char *result = new char[len];

	//cout << pos - fullFileName + 1 << endl;
	strncpy(result, fullFileName, len - 1);
	result[len - 1] = 0;
	return result;
}

char* CApp::merge(char * str1, char * str2) {
	char * result = new char[strlen(str1) + strlen(str2)];
	strcpy(result, str1);
	strcat(result, str2);
	return result;
}


//#include <Windows.h>
//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
//	CApp theApp;
//	theApp.level = 2;
//	char name[MAX_PATH];
//	GetModuleFileName(GetModuleHandle(0), name, MAX_PATH);
//	char * path = CApp::getPath(name);
//	theApp.setSystemPath(path);
//	return theApp.onExecute();
//}



int main(int argc, char* argv[]) {
	CApp theApp;
	theApp.level = 2;
	theApp.setSystemPath(CApp::getPath(argv[0]));
	return theApp.onExecute();
	//return 0;
}