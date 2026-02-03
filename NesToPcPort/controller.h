#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <string>

using namespace std;

class console;

struct inputSetting {
	Uint8 type; //0=none, 1=keyboard, 2=joystick axis, 3=joystick hat, 4=joystick button
	Uint32 v;
};

struct buttons {
	bool up;
	bool down;
	bool left;
	bool right;
	bool a;
	bool b;
	bool select;
	bool start;
};

class controller
{
public:
	console* myConsole;

	buttons controller1;
	buttons controller2;

	Uint8 frameCounter;

	Sint32 windowWidth;
	Sint32 windowHeight;
	bool screenIsWide;
	Sint32 screenXOffset;
	Sint32 screenYOffset;
	float mouseX;
	float mouseY;

	vector<SDL_Joystick*>js;
	inputSetting inputSettings[4][8];

	controller();
	~controller();
	Uint8 getController1State();
	Uint8 getController2State();
	void init();
	void handleEvent(SDL_Event* event);
	void setConfig(string h, string t);
	void setScreenSize(Sint32 w, Sint32 h);
	Uint8 getMouseX();
	Uint8 getMouseY();
};

