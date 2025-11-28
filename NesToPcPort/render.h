#pragma once
#include <SDL3/SDL.h>
#include "string"

using namespace std;

class console;

class render
{
public:
	console* myConsole;
	SDL_Renderer* renderer;
	SDL_Texture* internalScreen;
	Uint8 pixelBuffer[256 * 240];

	int displayWidth;
	int displayHeight;

	render();
	void init(SDL_Renderer* r);
	void cleanUp();
	void setConfig(string h, string t);
	void renderFrame();

private:
	SDL_Color colors[64];
	void loadPalette(SDL_IOStream* palFile);
	SDL_Color getRenderColor(Uint8 o, Uint8 n1, Uint8 n2, Uint8 d);
	bool isClose(Uint8 c1, Uint8 c2);
	bool isBlack(Uint8 c);
	SDL_Color mixColor(Uint8 c1, Uint8 w1, Uint8 c2, Uint8 w2, Uint8 c3, Uint8 w3, Uint8 c4, Uint8 w4);
};

