//=============================================================================

#include "C_Event.h"
#include <iostream>
using namespace std;

C_Event::C_Event() {
}

C_Event::~C_Event() {
	//Do nothing
}

void C_Event::onEvent(SDL_Event* Event) {
	switch (Event->type) {
	case SDL_ACTIVEEVENT: {
		switch (Event->active.state) {
		case SDL_APPMOUSEFOCUS: {
			if (Event->active.gain)    onMouseFocus();
			else onMouseBlur();

			break;
		}
		case SDL_APPINPUTFOCUS: {
			if (Event->active.gain)    onInputFocus();
			else onInputBlur();

			break;
		}
		case SDL_APPACTIVE: {
			if (Event->active.gain)    onRestore();
			else onMinimize();

			break;
		}
		}
		break;
	}

	case SDL_KEYDOWN: {
		onKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
		break;
	}

	case SDL_KEYUP: {
		onKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
		break;
	}

	case SDL_MOUSEMOTION: {
		onMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		switch (Event->button.button) {
		case SDL_BUTTON_LEFT: {
			onLButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			onRButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			onMButtonDown(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}

	case SDL_MOUSEBUTTONUP: {
		switch (Event->button.button) {
		case SDL_BUTTON_LEFT: {
			onLButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			onRButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			onMButtonUp(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}

	case SDL_JOYAXISMOTION: {
		onJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
		break;
	}

	case SDL_JOYBALLMOTION: {
		onJoyBall(Event->jball.which, Event->jball.ball, Event->jball.xrel, Event->jball.yrel);
		break;
	}

	case SDL_JOYHATMOTION: {
		onJoyHat(Event->jhat.which, Event->jhat.hat, Event->jhat.value);
		break;
	}
	case SDL_JOYBUTTONDOWN: {
		onJoyButtonDown(Event->jbutton.which, Event->jbutton.button);
		break;
	}

	case SDL_JOYBUTTONUP: {
		onJoyButtonUp(Event->jbutton.which, Event->jbutton.button);
		break;
	}

	case SDL_QUIT: {
		onExit();
		break;
	}

	case SDL_SYSWMEVENT: {
		//Ignore
		break;
	}

	case SDL_VIDEORESIZE: {
		onResize(Event->resize.w, Event->resize.h);
		break;
	}

	case SDL_VIDEOEXPOSE: {
		onExpose();
		break;
	}

	default: {
		onUser(Event->user.type, Event->user.code, Event->user.data1, Event->user.data2);
		break;
	}
	}
}

void C_Event::onInputFocus() {
	//Pure virtual, do nothing
}

void C_Event::onInputBlur() {
	//Pure virtual, do nothing
}

void C_Event::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym)
	{
	case SDLK_ESCAPE:
	{
		cout << "Hey, HABR! Escape pressed by m0sk1t\n";
		break;
	}
	case SDLK_UP:
	{
		cout << "Hey, HABR! UP pressed by m0sk1t\n";
		break;
	}
	case SDLK_DOWN:
	{
		cout << "Hey, HABR! DOWN pressed by m0sk1t\n";
		
		break;
	}
	case SDLK_LEFT:
	{
		cout << "Hey, HABR! LEFT pressed by m0sk1t\n";
		break;
	}
	case SDLK_RIGHT:
	{
		cout << "Hey, HABR! RIGHT pressed by m0sk1t\n";
		break;
	}
	default: break;
	}

}

void C_Event::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	//Pure virtual, do nothing
}

void C_Event::onMouseFocus() {
	//Pure virtual, do nothing
}

void C_Event::onMouseBlur() {
	//Pure virtual, do nothing
}

void C_Event::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
	//Pure virtual, do nothing
}

void C_Event::onMouseWheel(bool Up, bool Down) {
	//Pure virtual, do nothing
}

void C_Event::onLButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

void C_Event::onLButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

void C_Event::onRButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

void C_Event::onRButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

void C_Event::onMButtonDown(int mX, int mY) {
	//Pure virtual, do nothing
}

void C_Event::onMButtonUp(int mX, int mY) {
	//Pure virtual, do nothing
}

void C_Event::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
	//Pure virtual, do nothing
}

void C_Event::onJoyButtonDown(Uint8 which, Uint8 button) {
	//Pure virtual, do nothing
}

void C_Event::onJoyButtonUp(Uint8 which, Uint8 button) {
	//Pure virtual, do nothing
}

void C_Event::onJoyHat(Uint8 which, Uint8 hat, Uint8 value) {
	//Pure virtual, do nothing
}

void C_Event::onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {
	//Pure virtual, do nothing
}

void C_Event::onMinimize() {
	//Pure virtual, do nothing
}

void C_Event::onRestore() {
	//Pure virtual, do nothing
}

void C_Event::onResize(int w, int h) {
	//Pure virtual, do nothing
}

void C_Event::onExpose() {
	//Pure virtual, do nothing
}

void C_Event::onExit() {
	//Pure virtual, do nothing
}

void C_Event::onUser(Uint8 type, int code, void* data1, void* data2) {
	//Pure virtual, do nothing
}