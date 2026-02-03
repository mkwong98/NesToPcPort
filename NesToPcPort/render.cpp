#include "render.h"
#include "console.h"
#include "mapper.h"

void render::renderFrame() {
	Uint16 pixelID = 0;
	Uint16 spPixelID = 0;
	for (int j = 0; j < 240; j++) {
		for (int i = 0; i < 256; i++) {
			Uint8 pixel;

			bool hasSP = false;
			bool spIsFront = false;
			Uint8 spColourID;
			if (spPixelID < myConsole->ppu.spScreenPixelsCnt) {
				if (myConsole->ppu.spPixelLocation[spPixelID].y == j && myConsole->ppu.spPixelLocation[spPixelID].x == i) {
					Uint8 spID = 0;
					while (spID < myConsole->ppu.spPixelLocation[spPixelID].cnt && !hasSP) {
						if (myConsole->ppu.spScreenPixels[spPixelID][spID].colourID != 0xFF) {
							hasSP = true;
							spIsFront = myConsole->ppu.spScreenPixels[spPixelID][spID].front;
							spColourID = myConsole->ppu.spScreenPixels[spPixelID][spID].colourID;
						}
						else {
							spID++;
						}
					}
					spPixelID++;
				}
			}

			if (hasSP && spIsFront) {
				// render sprite pixel
				pixel = spColourID;
			}
			else if (myConsole->ppu.bgScreenPixels[pixelID].colourID != 0xFF) {
				// render background pixel
				pixel = myConsole->ppu.bgScreenPixels[pixelID].colourID;
			}
			else if (hasSP) {
				pixel = spColourID;
			}
			else {
				pixel = myConsole->ppu.bg0ColourIDs[pixelID];
			}
			pixelBuffer[pixelID] = pixel;
			pixelID++;
		}
	}

	Uint8* tmpPixels = nullptr;
	int tmpPitch = 0;
	SDL_LockTexture(internalScreen, NULL, (void**)&tmpPixels, &tmpPitch);

	if (!useFilter) {
		pixelID = 0;
		for (int j = 0; j < 240; j++) {
			for (int i = 0; i < 256; i++) {
				if (pixelBuffer[pixelID] != 0xFF) {
					*tmpPixels = SDL_ALPHA_OPAQUE;
					tmpPixels++;
					*tmpPixels = colors[pixelBuffer[pixelID]].b;
					tmpPixels++;
					*tmpPixels = colors[pixelBuffer[pixelID]].g;
					tmpPixels++;
					*tmpPixels = colors[pixelBuffer[pixelID]].r;
					tmpPixels++;
				}
				else {
					*tmpPixels = SDL_ALPHA_OPAQUE;
					tmpPixels++;
					*tmpPixels = 0;
					tmpPixels++;
					*tmpPixels = 0;
					tmpPixels++;
					*tmpPixels = 0;
					tmpPixels++;
				}
				pixelID++;
			}
		}
	}
	else {
		pixelID = 0;
		for (int j = 0; j < 240; j++) {
			for (int i = 0; i < 256; i++) {
				Uint8 pixel = pixelBuffer[pixelID];
				Uint8 pixelTopLeft = 0xFF;
				Uint8 pixelTop = 0xFF;
				Uint8 pixelTopRight = 0xFF;
				Uint8 pixelLeft = 0xFF;
				Uint8 pixelRight = 0xFF;
				Uint8 pixelBottomLeft = 0xFF;
				Uint8 pixelBottom = 0xFF;
				Uint8 pixelBottomRight = 0xFF;
				if (i > 0 && j > 0) pixelTopLeft = pixelBuffer[pixelID - 256 - 1];
				if (j > 0) pixelTop = pixelBuffer[pixelID - 256];
				if (i < 255 && j > 0) pixelTopRight = pixelBuffer[pixelID - 256 + 1];
				if (i > 0) pixelLeft = pixelBuffer[pixelID - 1];
				if (i < 255) pixelRight = pixelBuffer[pixelID + 1];
				if (i > 0 && j < 239) pixelBottomLeft = pixelBuffer[pixelID + 256 - 1];
				if (j < 239) pixelBottom = pixelBuffer[pixelID + 256];
				if (i < 255 && j < 239) pixelBottomRight = pixelBuffer[pixelID + 256 + 1];

				SDL_Color c = getRenderColor(pixel, pixelTop, pixelLeft, pixelTopLeft);
				*tmpPixels = SDL_ALPHA_OPAQUE;
				*(tmpPixels + 1) = c.b;
				*(tmpPixels + 2) = c.g;
				*(tmpPixels + 3) = c.r;

				c = getRenderColor(pixel, pixelTop, pixelRight, pixelTopRight);
				*(tmpPixels + 4) = SDL_ALPHA_OPAQUE;
				*(tmpPixels + 5) = c.b;
				*(tmpPixels + 6) = c.g;
				*(tmpPixels + 7) = c.r;

				c = getRenderColor(pixel, pixelBottom, pixelLeft, pixelBottomLeft);
				*(tmpPixels + tmpPitch) = SDL_ALPHA_OPAQUE;
				*(tmpPixels + tmpPitch + 1) = c.b;
				*(tmpPixels + tmpPitch + 2) = c.g;
				*(tmpPixels + tmpPitch + 3) = c.r;

				c = getRenderColor(pixel, pixelBottom, pixelRight, pixelBottomRight);
				*(tmpPixels + tmpPitch + 4) = SDL_ALPHA_OPAQUE;
				*(tmpPixels + tmpPitch + 5) = c.b;
				*(tmpPixels + tmpPitch + 6) = c.g;
				*(tmpPixels + tmpPitch + 7) = c.r;
				pixelID++;
				tmpPixels += 8;
			}
			tmpPixels += tmpPitch;
		}
	}


	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0, SDL_ALPHA_OPAQUE);
	//Uint16 addr = 0;
	//for (int tmpY = 0; tmpY < 24; tmpY++) {
	//	SDL_RenderDebugTextFormat(renderer, 0, tmpY * 16 + 243, "%X", tmpY * 2);
	//	for (int tmpX = 0; tmpX < 32; tmpX++) {
	//		SDL_RenderDebugTextFormat(renderer, (tmpX + 1) * 28, tmpY * 16 + 243, "%X", myConsole->cpu.myMapper->readCPU(addr));
	//		addr++;
	//	}
	//}

	SDL_UnlockTexture(internalScreen);
	SDL_RenderTexture(renderer, internalScreen, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void render::loadPalette(SDL_IOStream* palFile) {
	Uint8 pal[192];
	SDL_ReadIO(palFile, pal, 192);
	for (int i = 0; i < 64; i++) {
		colors[i].r = pal[i * 3];
		colors[i].g = pal[i * 3 + 1];
		colors[i].b = pal[i * 3 + 2];
		colors[i].a = SDL_ALPHA_OPAQUE;
		for (int j = 0; j <= 5; j++) {
			workColors[i][j].r = colors[i].r * j;
			workColors[i][j].g = colors[i].g * j;
			workColors[i][j].b = colors[i].b * j;
		}
	}
	SDL_CloseIO(palFile);
}

void render::setConfig(string h, string t) {
	if (h == "PALETTE") {
		loadPalette(SDL_IOFromFile(t.c_str(), "rb"));
	}
	else if (h == "WIDTH") {
		displayWidth = std::stoi(t);
	}
	else if (h == "HEIGHT") {
		displayHeight = std::stoi(t);
	}
	else if (h == "USEFILTER") {
		useFilter = (t == "1");
	}
}

render::render() {
	displayWidth = 256;
	displayHeight = 240;
	useFilter = false;
}


void render::init(SDL_Renderer* r) {
	renderer = r;
	//internalScreen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 960);
	if (!useFilter) {
		internalScreen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);
	}
	else {
		internalScreen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 256 * 2, 240 * 2);
	}
	SDL_SetTextureScaleMode(internalScreen, SDL_SCALEMODE_NEAREST);
	SDL_SetRenderLogicalPresentation(renderer, displayWidth, displayHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	myConsole->controllers.setScreenSize(displayWidth, displayHeight);
}

void render::cleanUp() {
	if (internalScreen) SDL_DestroyTexture(internalScreen);
}

bool render::isClose(Uint8 c1, Uint8 c2) {
	if (c1 == 0xFF || c2 == 0xFF) return false;
	if (c1 == c2) return true;

	Uint8 c1p = c1 & 0x0F;
	Uint8 c2p = c2 & 0x0F;
	Uint8 c1q = c1 >> 4;
	Uint8 c2q = c2 >> 4;
	Uint8 diffP = (c1p > c2p) ? min((c1p - c2p), (c2p + 0xC - c1p)) : min((c2p - c1p), (c1p + 0xC - c2p));
	Uint8 diffQ = (c1q > c2q) ? (c1q - c2q) : (c2q - c1q);

	if (c1p == c2p && diffQ < 3) return true;

	if (c1p >= 0x01 && c1p <= 0x0C && c2p >= 0x01 && c2p <= 0x0C && diffP + diffQ < 3) {
		return true;
	}
	if (isBlack(c1) && isBlack(c2)) return true;
	return false;
}

bool render::isBlack(Uint8 c) {
	if ((c & 0x0F) > 0x0E) return true;
	if (c == 0x0D || c == 0x1D) return true;
	return false;
}

SDL_Color render::getRenderColor(Uint8 o, Uint8 n1, Uint8 n2, Uint8 d) {
	if (o == n1 && o == n2 && o == d) {
		return colors[o];
	}
	bool close1 = isClose(o, n1);
	bool close2 = isClose(o, n2);
	bool close3 = isClose(o, d);

	if (!(close1 || close2 || close3))
		return mixColor(o, 5, 
			(n1 == 0xFF ? 0 : n1), (n1 == 0xFF ? 0 : 2), 
			(n2 == 0xFF ? 0 : n2), (n2 == 0xFF ? 0 : 2),
			(d == 0xFF ? 0 : d), (d == 0xFF ? 0 : 1));
	return mixColor(o, 5, 
		(n1 == 0xFF ? 0 : n1), (close1 ? 2 : 0), 
		(n2 == 0xFF ? 0 : n2), (close2 ? 2 : 0), 
		(d == 0xFF ? 0 : d), (close3 ? 1 : 0));
}

SDL_Color render::mixColor(Uint8 c1, Uint8 w1, Uint8 c2, Uint8 w2, Uint8 c3, Uint8 w3, Uint8 c4, Uint8 w4) {
	SDL_Color result;
	Uint8 totalWeight = w1 + w2 + w3 + w4;	
	result.b = (workColors[c1][w1].b + workColors[c2][w2].b + workColors[c3][w3].b + workColors[c4][w4].b) / totalWeight;
	result.g = (workColors[c1][w1].g + workColors[c2][w2].g + workColors[c3][w3].g + workColors[c4][w4].g) / totalWeight;
	result.r = (workColors[c1][w1].r + workColors[c2][w2].r + workColors[c3][w3].r + workColors[c4][w4].r) / totalWeight;
	result.a = SDL_ALPHA_OPAQUE;
	return result;
}
