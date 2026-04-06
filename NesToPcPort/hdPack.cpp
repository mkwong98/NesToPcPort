#include "render.h"
#include "console.h"
#include "mapper.h"

bool render::loadHDPack() {
	char* configData;
	size_t dataSize;
	configData = (char*)SDL_LoadFile("pack/hires.txt", &dataSize);
	if (configData == NULL) {
		return false;
	}

	//init pack
	pack.scale = 1;
	//add built in conditions
	hdPackCondition c;
	c.name = "";
	c.type = CONDITION_TYPE_NONE;
	pack.conditions.push_back(c);
	c.name = "hmirror";
	c.type = CONDITION_TYPE_HMIRROR;;
	pack.conditions.push_back(c);
	c.name = "vmirror";
	c.type = CONDITION_TYPE_VMIRROR;
	pack.conditions.push_back(c);
	c.name = "bgpriority";
	c.type = CONDITION_TYPE_BGPRIORITY;
	pack.conditions.push_back(c);


	string tmpStr = configData;
	tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), '\r'), tmpStr.end());
	stringstream s(tmpStr);
	string configLine;
	while (getline(s, configLine)) {
		string lineRemain = configLine;
		string lineHead = configLine.substr(0, 1);
		vector<Uint16> conditionIDs;
		vector<bool> conditionNegations;
		if (lineHead == "[") {
			size_t findIdx = configLine.find("]");
			string condition = configLine.substr(1, findIdx - 1);

			while (condition.length() > 0) {
				size_t findIdx2 = condition.find("&");
				string conditionName = (findIdx2 == string::npos) ? condition : condition.substr(0, findIdx2);
				bool negation = false;
				if (conditionName.length() > 0 && conditionName[0] == '!') {
					negation = true;
					conditionName = conditionName.substr(1);
				}
				for (Uint16 i = 0; i < pack.conditions.size(); i++) {
					if (pack.conditions[i].name == conditionName) {
						conditionIDs.push_back(i);
						conditionNegations.push_back(negation);
						break;
					}
				}
				if (findIdx2 == string::npos) break;
				else condition = condition.substr(findIdx2 + 1);
			}

			lineRemain = lineRemain.substr(findIdx + 1);
			lineHead = lineRemain.substr(0, 1);
		}
		if (lineHead == "<") {
			size_t findIdx = lineRemain.find(">");
			lineHead = lineRemain.substr(1, findIdx - 1);
			lineRemain = lineRemain.substr(findIdx + 1);
			if (lineHead == "scale")
				pack.scale = stoi(lineRemain);
			else if (lineHead == "img") {
				SDL_Surface* img = SDL_LoadPNG(("pack/" + lineRemain).c_str());
				pack.images.push_back(SDL_CreateTextureFromSurface(renderer, img));
				SDL_DestroySurface(img);
			}
			else if (lineHead == "condition") {
				hdPackCondition c;
				findIdx = lineRemain.find(",");
				c.name = lineRemain.substr(0, findIdx);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				if (lineHead == "tilenearby") c.type = CONDITION_TYPE_TILENEARBY;
				else if (lineHead == "spriteNearby") c.type = CONDITION_TYPE_SPRITENEARBY;
				else if (lineHead == "tileAtPosition") c.type = CONDITION_TYPE_TILEATPOSITION;
				else if (lineHead == "spriteAtPosition") c.type = CONDITION_TYPE_SPRITEATPOSITION;
				else if (lineHead == "memoryCheck") c.type = CONDITION_TYPE_MEMORYCHECK;
				else if (lineHead == "ppuMemoryCheck") c.type = CONDITION_TYPE_PPUMEMORYCHECK;
				else if (lineHead == "memoryCheckConstant") c.type = CONDITION_TYPE_MEMORYCHECKCONSTANT;
				else if (lineHead == "ppuMemoryCheckConstant") c.type = CONDITION_TYPE_PPUMEMORYCHECKCONSTANT;
				else if (lineHead == "frameRange") c.type = CONDITION_TYPE_FRAMERANGE;
				else c.type = CONDITION_TYPE_NONE;
				lineRemain = lineRemain.substr(findIdx + 1);

				switch (c.type) {
				case CONDITION_TYPE_TILENEARBY:
				case CONDITION_TYPE_SPRITENEARBY:
				case CONDITION_TYPE_TILEATPOSITION:
				case CONDITION_TYPE_SPRITEATPOSITION:
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					c.x = stoi(lineHead);
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					c.y = stoi(lineHead);
					lineRemain = lineRemain.substr(findIdx + 1);
					if (hasCHRROM) {
						findIdx = lineRemain.find(",");
						lineHead = lineRemain.substr(0, findIdx);
						c.tileID = stoi(lineHead, nullptr, 16);
						lineRemain = lineRemain.substr(findIdx + 1);
					}
					else {
						for (int i = 0; i < 2; i++) {
							lineHead = lineRemain.substr(0, 16);
							c.pattern[i] = convertStringToPattern(lineHead);
							lineRemain = lineRemain.substr(16);
						}
						lineRemain = lineRemain.substr(1);
					}
					c.palette = stoul(lineRemain, nullptr, 16);
					break;
				case CONDITION_TYPE_MEMORYCHECK:
				case CONDITION_TYPE_PPUMEMORYCHECK:
				case CONDITION_TYPE_MEMORYCHECKCONSTANT:
				case CONDITION_TYPE_PPUMEMORYCHECKCONSTANT:
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					c.memCheck.address = stoi(lineHead, nullptr, 16);
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					if (lineHead == "==") c.memCheck.opType = memoryCheck::EQ;
					else if (lineHead == "!=") c.memCheck.opType = memoryCheck::NE;
					else if (lineHead == ">") c.memCheck.opType = memoryCheck::GT;
					else if (lineHead == "<") c.memCheck.opType = memoryCheck::LS;
					else if (lineHead == ">=") c.memCheck.opType = memoryCheck::GE;
					else if (lineHead == "<=") c.memCheck.opType = memoryCheck::LE;
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos) {
						c.memCheck.value = stoi(lineRemain, nullptr, 16);
						c.memCheck.mask = 0xFF;
					}
					else {
						lineHead = lineRemain.substr(0, findIdx);
						c.memCheck.value = stoi(lineHead, nullptr, 16);
						lineRemain = lineRemain.substr(findIdx + 1);
						c.memCheck.mask = stoi(lineRemain, nullptr, 16);
					}
					if (c.type == CONDITION_TYPE_MEMORYCHECK || c.type == CONDITION_TYPE_PPUMEMORYCHECK)
						c.memCheck.valueAsAddress = false;
					else
						c.memCheck.valueAsAddress = true;
					break;
				case CONDITION_TYPE_FRAMERANGE:
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					c.divisorValue = stoi(lineHead);
					lineRemain = lineRemain.substr(findIdx + 1);
					c.compareValue = stoi(lineRemain);
					break;
				}
				pack.conditions.push_back(c);
			}
			else if (lineHead == "background") {
				hdPackBackground bg;
				bg.brightness = 1.0;
				bg.hScrollRatio = 0;
				bg.vScrollRatio = 0;
				bg.priority = 10;
				findIdx = lineRemain.find(",");
				if (findIdx == string::npos)
					lineHead = lineRemain;
				else
					lineHead = lineRemain.substr(0, findIdx);
				bg.imageID = UINT16_MAX;
				for (Uint16 i = 0; i < pack.backgroundImgNames.size(); i++) {
					if (pack.backgroundImgNames[i] == lineHead) {
						bg.imageID = i;
						break;
					}
				}
				if (bg.imageID == UINT16_MAX) {
					SDL_Surface* img = SDL_LoadPNG(("pack/" + lineHead).c_str());
					pack.backgroundImgNames.push_back(lineHead);
					pack.backgroundImages.push_back(SDL_CreateTextureFromSurface(renderer, img));
					SDL_DestroySurface(img);
					bg.imageID = pack.backgroundImgNames.size() - 1;
				}
				if (findIdx != string::npos) {
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos)
						lineHead = lineRemain;
					else
						lineHead = lineRemain.substr(0, findIdx);
					bg.brightness = stod(lineHead);
				}
				if (findIdx != string::npos) {
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos)
						lineHead = lineRemain;
					else
						lineHead = lineRemain.substr(0, findIdx);
					bg.hScrollRatio = stod(lineHead);
				}
				if (findIdx != string::npos) {
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos)
						lineHead = lineRemain;
					else
						lineHead = lineRemain.substr(0, findIdx);
					bg.vScrollRatio = stod(lineHead);
				}
				if (findIdx != string::npos) {
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos)
						lineHead = lineRemain;
					else
						lineHead = lineRemain.substr(0, findIdx);
					bg.priority = stoi(lineHead);
				}
				if (findIdx != string::npos) {
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos)
						lineHead = lineRemain;
					else
						lineHead = lineRemain.substr(0, findIdx);
					bg.xOffset = stoi(lineHead);
				}
				if (findIdx != string::npos) {
					lineRemain = lineRemain.substr(findIdx + 1);
					findIdx = lineRemain.find(",");
					if (findIdx == string::npos)
						lineHead = lineRemain;
					else
						lineHead = lineRemain.substr(0, findIdx);
					bg.yOffset = stoi(lineHead);
				}
				bg.conditionIDs = conditionIDs;
				bg.conditionNegations = conditionNegations;
				pack.backgrounds.push_back(bg);
			}
			else if (lineHead == "tile") {
				hdPackReplacement r;
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				r.imageID = stoi(lineHead);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);

				if (hasCHRROM) {
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					r.tileID = stoi(lineHead, nullptr, 16);
					lineRemain = lineRemain.substr(findIdx + 1);
				}
				else {
					for (int i = 0; i < 2; i++) {
						lineHead = lineRemain.substr(0, 16);
						r.pattern[i] = convertStringToPattern(lineHead);
						lineRemain = lineRemain.substr(16);
					}
					lineRemain = lineRemain.substr(1);
				}
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				r.palette = stoul(lineHead, nullptr, 16);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				r.x = stoi(lineHead);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				r.y = stoi(lineHead);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				r.brightness = stod(lineHead);
				lineRemain = lineRemain.substr(findIdx + 1);
				r.asDefault = (lineRemain == "Y");

				r.conditionIDs = conditionIDs;
				r.conditionNegations = conditionNegations;
				pack.replacements.push_back(r);
			}
			else if (lineHead == "addition") {
				hdPackAdditionalTile t;
				if (hasCHRROM) {
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					t.tileID = stoi(lineHead, nullptr, 16);
					lineRemain = lineRemain.substr(findIdx + 1);
				}
				else {
					for (int i = 0; i < 2; i++) {
						lineHead = lineRemain.substr(0, 16);
						t.pattern[i] = convertStringToPattern(lineHead);
						lineRemain = lineRemain.substr(16);
					}
					lineRemain = lineRemain.substr(1);
				}
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				t.palette = stoul(lineHead, nullptr, 16);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				t.x = stoi(lineHead);
				lineRemain = lineRemain.substr(findIdx + 1);
				findIdx = lineRemain.find(",");
				lineHead = lineRemain.substr(0, findIdx);
				t.y = stoi(lineHead);
				lineRemain = lineRemain.substr(findIdx + 1);
				if (hasCHRROM) {
					findIdx = lineRemain.find(",");
					lineHead = lineRemain.substr(0, findIdx);
					t.addTileID = stoi(lineHead, nullptr, 16);
					lineRemain = lineRemain.substr(findIdx + 1);
				}
				else {
					for (int i = 0; i < 2; i++) {
						lineHead = lineRemain.substr(0, 16);
						t.addPattern[i] = convertStringToPattern(lineHead);
						lineRemain = lineRemain.substr(16);
					}
					lineRemain = lineRemain.substr(1);
				}
				t.addPalette = stoi(lineRemain, nullptr, 16);
			}
		}
	}
	SDL_free(configData);
	return true;
}

void render::cleanHDPack() {
	for (int i = 0; i < pack.images.size(); i++) {
		SDL_DestroyTexture(pack.images[i]);
	}
	for (int i = 0; i < pack.backgroundImages.size(); i++) {
		SDL_DestroyTexture(pack.backgroundImages[i]);
	}
	if (pack.backColourLayer) SDL_DestroyTexture(pack.backColourLayer);
	if (pack.backSpriteLayer) SDL_DestroyTexture(pack.backSpriteLayer);
	if (pack.backgroundLayer) SDL_DestroyTexture(pack.backgroundLayer);
	if (pack.frontSpriteLayer) SDL_DestroyTexture(pack.frontSpriteLayer);
}

void render::renderHDPackFrame() {
	Uint32* tmpPixels = nullptr;
	Uint8* tmpPixelsBackSpr = nullptr;
	Uint8* tmpPixelsBackGround = nullptr;
	Uint8* tmpPixelsFrontSpr = nullptr;
	int tmpPitch = 0;
	int tmpPitchBackSpr = 0;
	int tmpPitchBackGround = 0;
	int tmpPitchFrontSpr = 0;
	Uint16 pixelID = 0;
	/*clear all layers*/
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_SetRenderTarget(renderer, pack.backColourLayer);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, pack.backSpriteLayer);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, pack.backgroundLayer);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, pack.frontSpriteLayer);
	SDL_RenderClear(renderer);
	/*lock for direct pixel manipulation*/
	SDL_LockTexture(pack.backColourLayer, NULL, (void**)&tmpPixels, &tmpPitch);
	SDL_LockTexture(pack.backSpriteLayer, NULL, (void**)&tmpPixelsBackSpr, &tmpPitchBackSpr);
	SDL_LockTexture(pack.backgroundLayer, NULL, (void**)&tmpPixelsBackGround, &tmpPitchBackGround);
	SDL_LockTexture(pack.frontSpriteLayer, NULL, (void**)&tmpPixelsFrontSpr, &tmpPitchFrontSpr);
	tmpPitch <<= 2; // convert from byte to pixel
	for (int j = 0; j < 240; j++) {
		for (int i = 0; i < 256; i++) {
			if (myConsole->ppu.bg0ColourIDs[pixelID] != 0xFF) {
				*tmpPixels = rawColors[myConsole->ppu.bg0ColourIDs[pixelID]];
				tmpPixels++;
			}
			else {
				*tmpPixels = 0;
			}
			pixelID++;
		}
	}
	SDL_UnlockTexture(pack.backColourLayer);
	SDL_UnlockTexture(pack.backSpriteLayer);
	SDL_UnlockTexture(pack.backgroundLayer);
	SDL_UnlockTexture(pack.frontSpriteLayer);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderTexture(renderer, pack.backColourLayer, NULL, NULL);
	SDL_RenderTexture(renderer, pack.backSpriteLayer, NULL, NULL);
	SDL_RenderTexture(renderer, pack.backgroundLayer, NULL, NULL);
	SDL_RenderTexture(renderer, pack.frontSpriteLayer, NULL, NULL);
	SDL_RenderPresent(renderer);
}

Uint64 render::convertStringToPattern(string s) {
	Uint64 pattern = 0;
	for (int i = 0; i < s.length(); i++) {
		pattern <<= 8;
		string byteString = s.substr(0, 2);
		pattern |= stoi(byteString, nullptr, 16);
	}
	return pattern;
}
