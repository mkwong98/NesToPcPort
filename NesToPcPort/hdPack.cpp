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
			if (lineHead == "scale") {
				pack.scale = stoi(lineRemain);
				pack.tmpBackSpr = new Uint32[pack.scale * pack.scale];
				pack.tmpFrontSpr = new Uint32[pack.scale * pack.scale];
			}
			else if (lineHead == "img") {
				SDL_Surface* img = SDL_LoadPNG(("pack/" + lineRemain).c_str());
				SDL_PremultiplySurfaceAlpha(img, true);
				SDL_Surface* img2 = SDL_ConvertSurface(img, SDL_PIXELFORMAT_RGBA8888);
				pack.images.push_back(img2);
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
				Uint8 tileHash;
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
					tileHash = r.tileID & 0xFF;
				}
				else {
					tileHash = 0;
					for (int i = 0; i < 16; i++) {
						lineHead = lineRemain.substr(i * 2, 2);
						tileHash ^= stoi(lineHead, nullptr, 16);
					}
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
				pack.replacements[tileHash].push_back(r);
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
				t.addPalette = stoul(lineRemain, nullptr, 16);
			}
		}
	}
	SDL_free(configData);
	return true;
}

void render::cleanHDPack() {
	for (int i = 0; i < pack.images.size(); i++) {
		SDL_DestroySurface(pack.images[i]);
	}
	for (int i = 0; i < pack.backgroundImages.size(); i++) {
		SDL_DestroyTexture(pack.backgroundImages[i]);
	}
	if (pack.backColourLayer) SDL_DestroyTexture(pack.backColourLayer);
	if (pack.backSpriteLayer) SDL_DestroyTexture(pack.backSpriteLayer);
	if (pack.backgroundLayer) SDL_DestroyTexture(pack.backgroundLayer);
	if (pack.frontSpriteLayer) SDL_DestroyTexture(pack.frontSpriteLayer);
	delete[] pack.tmpBackSpr;
	delete[] pack.tmpFrontSpr;
}

void render::renderHDPackFrame() {
	Uint32* tmpPixels = nullptr;
	Uint8* tmpPixelsBackSpr = nullptr;
	Uint32* tmpPixelsBackSprColour = nullptr;
	Uint32* tmpPixelsBackGround = nullptr;
	Uint8* tmpPixelsFrontSpr = nullptr;
	Uint32* tmpPixelsFrontSprColour = nullptr;
	int tmpPitch = 0;
	int tmpPitchBackSpr = 0;
	int tmpPitchBackSprColour = 0;
	int tmpPitchBackGround = 0;
	int tmpPitchFrontSpr = 0;
	int tmpPitchFrontSprColour = 0;
	Uint16 pixelID = 0;
	Uint16 spPixelID = 0;
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
	tmpPixelsBackSprColour = (Uint32*)tmpPixelsBackSpr;
	tmpPixelsFrontSprColour = (Uint32*)tmpPixelsFrontSpr;
	tmpPitchBackGround >>= 2; // convert from byte to pixel
	tmpPitchBackSprColour = tmpPitchBackSpr >> 2;
	tmpPitchFrontSprColour = tmpPitchFrontSpr >> 2;

	//clear all global results for conditions
	for (int i = 0; i < pack.conditions.size(); i++) {
		pack.conditions[i].hasGlobalResult = false;
	}

	Uint32* workPixel;
	for (int j = 0; j < 240; j++) {
		for (int i = 0; i < 256; i++) {
			memset(pack.tmpBackSpr, 0, sizeof(Uint32) * pack.scale * pack.scale);
			memset(pack.tmpFrontSpr, 0, sizeof(Uint32) * pack.scale * pack.scale);

			if (myConsole->ppu.bg0ColourIDs[pixelID] != 0xFF) {
				*tmpPixels = rawColors[myConsole->ppu.bg0ColourIDs[pixelID]];
			}
			else {
				*tmpPixels = 0;
			}
			tmpPixels++;

			bool hasHDTile = false;
			bgPixelDetails* pixel = &(myConsole->ppu.bgScreenPixels[pixelID]);
			if (pixel->tileID != 0xFFFF) {
				bgTileDetails* tile = &(myConsole->ppu.bgScreenTiles[pixel->screenID][pixel->tileID]);
				processedTile* processedTileData = &(myConsole->rom.processedCHRData[tile->patternID]);
				if (!tile->checkedForHDPackTile) {
					tile->hasHDPackTile = false;
					processedTile* condTileData;
					for (Uint8 checkLoop = 0; checkLoop < 2 && !tile->hasHDPackTile; checkLoop++) {
						for (int k = 0; k < pack.replacements[processedTileData->hash].size(); k++) {
							hdPackReplacement* r = &(pack.replacements[processedTileData->hash][k]);
							//check if the tile matches the replacement condition
							//if replacement is not found after the first loop, it will check again and ignore palette condition with the replacements marked as default
							if (r->palette != tile->palette && (checkLoop == 0 || !r->asDefault)) continue;
							if (hasCHRROM) {
								if (r->tileID != processedTileData->tileID) continue;
							}
							else {
								if (r->pattern[0] != processedTileData->bitPlane[0] || r->pattern[1] != processedTileData->bitPlane[1]) continue;
							}
							//check conditions
							bool match = true;
							for (int c = 0; c < r->conditionIDs.size(); c++) {
								bool result = false;
								hdPackCondition* cnd = &(pack.conditions[r->conditionIDs[c]]);
								switch (cnd->type) {
								case CONDITION_TYPE_FRAMERANGE:
								case CONDITION_TYPE_MEMORYCHECK:
								case CONDITION_TYPE_MEMORYCHECKCONSTANT:
								case CONDITION_TYPE_PPUMEMORYCHECK:
								case CONDITION_TYPE_PPUMEMORYCHECKCONSTANT:
								case CONDITION_TYPE_SPRITEATPOSITION:
								case CONDITION_TYPE_TILEATPOSITION:
									result = checkGlobalCondition(cnd);
									break;
								case CONDITION_TYPE_SPRITENEARBY:
									result = checkSpriteNearbyCondition(cnd, tile->x + cnd->x, tile->y + cnd->y);
									break;
								case CONDITION_TYPE_TILENEARBY:
									result = checkTileNearbyCondition(cnd, tile->x + cnd->x, tile->y + cnd->y);
									break;
								}
								if (r->conditionNegations[c]) result = !result;
								if (!result) {
									match = false;
									break;
								}
							}
							if (match) {
								tile->hasHDPackTile = true;
								tile->hdPackReplacementID = k;
								break;
							}
						}
					}
					tile->checkedForHDPackTile = true;
				}
				hasHDTile = tile->hasHDPackTile;
				if (hasHDTile) {
					hdPackReplacement* r = &(pack.replacements[processedTileData->hash][tile->hdPackReplacementID]);
					SDL_Surface* surface = pack.images[r->imageID];
					SDL_LockSurface(surface);
					Uint32* pixel_ptr = (Uint32*)surface->pixels + ((r->y + (pixel->y * pack.scale)) * surface->pitch) + ((r->x + (pixel->x * pack.scale)) * 4);
					for (int subY = 0; subY < pack.scale; subY++) {
						Uint32* row_pixel_ptr = pixel_ptr;
						for (int subX = 0; subX < pack.scale; subX++) {
							if(r->brightness != 1.0) {
								Uint32 colour = adjustColourForBrightness(*row_pixel_ptr, r->brightness);
								*(tmpPixelsBackGround + (subY * tmpPitchBackGround) + subX) = colour;
							}
							else
								*(tmpPixelsBackGround + (subY * tmpPitchBackGround) + subX) = *row_pixel_ptr;
							row_pixel_ptr++;
						}
						pixel_ptr += surface->pitch / 4;
					}
					SDL_UnlockSurface(surface);
				}
			}

			if(!hasHDTile) {
				if (myConsole->ppu.bgScreenPixels[pixelID].colourID != 0xFF) {
					for (int subY = 0; subY < pack.scale; subY++) {
						for (int subX = 0; subX < pack.scale; subX++) {
							*(tmpPixelsBackGround + (subY * tmpPitchBackGround) + subX) = rawColors[myConsole->ppu.bgScreenPixels[pixelID].colourID];
						}
					}
				}
				else {
					for (int subY = 0; subY < pack.scale; subY++) {
						for (int subX = 0; subX < pack.scale; subX++) {
							*(tmpPixelsBackGround + (subY * tmpPitchBackGround) + subX) = 0;
						}
					}
				}
			}
			tmpPixelsBackGround += pack.scale;


			if (spPixelID < myConsole->ppu.spScreenPixelsCnt) {
				if (myConsole->ppu.spPixelLocation[spPixelID].y == j && myConsole->ppu.spPixelLocation[spPixelID].x == i) {
					Sint8 spID = myConsole->ppu.spPixelLocation[spPixelID].cnt - 1;
					while (spID >= 0) {
						hasHDTile = false;
						spPixelDetails* spPixel = &(myConsole->ppu.spScreenPixels[spPixelID][spID]);
						spTileDetails* tile = &(myConsole->ppu.spScreenTiles[spPixel->tileID]);
						processedTile* processedTileData = &(myConsole->rom.processedCHRData[tile->patternID]);
						if (!tile->checkedForHDPackTile) {
							tile->hasHDPackTile = false;
							processedTile* condTileData;
							for (Uint8 checkLoop = 0; checkLoop < 2 && !tile->hasHDPackTile; checkLoop++) {
								for (int k = 0; k < pack.replacements[processedTileData->hash].size(); k++) {
									hdPackReplacement* r = &(pack.replacements[processedTileData->hash][k]);
									//check if the tile matches the replacement condition
									//if replacement is not found after the first loop, it will check again and ignore palette condition with the replacements marked as default
									if (r->palette != tile->palette && (checkLoop == 0 || !r->asDefault)) continue;
									if (hasCHRROM) {
										if (r->tileID != processedTileData->tileID) continue;
									}
									else {
										if (r->pattern[0] != processedTileData->bitPlane[0] || r->pattern[1] != processedTileData->bitPlane[1]) continue;
									}
									//check conditions
									bool match = true;
									for (int c = 0; c < r->conditionIDs.size(); c++) {
										bool result = false;
										hdPackCondition* cnd = &(pack.conditions[r->conditionIDs[c]]);
										switch (cnd->type) {
										case CONDITION_TYPE_FRAMERANGE:
										case CONDITION_TYPE_MEMORYCHECK:
										case CONDITION_TYPE_MEMORYCHECKCONSTANT:
										case CONDITION_TYPE_PPUMEMORYCHECK:
										case CONDITION_TYPE_PPUMEMORYCHECKCONSTANT:
										case CONDITION_TYPE_SPRITEATPOSITION:
										case CONDITION_TYPE_TILEATPOSITION:
											result = checkGlobalCondition(cnd);
											break;
										case CONDITION_TYPE_SPRITENEARBY:
											result = checkSpriteNearbyCondition(cnd, tile->x + (tile->hFlip ? -cnd->x : cnd->x), tile->y + (tile->vFlip ? -cnd->y : cnd->y));
											break;
										case CONDITION_TYPE_TILENEARBY:
											result = checkTileNearbyCondition(cnd, tile->x + (tile->hFlip ? -cnd->x : cnd->x), tile->y + (tile->vFlip ? -cnd->y : cnd->y));
											break;
										case CONDITION_TYPE_HMIRROR:
											result = tile->hFlip;
											break;
										case CONDITION_TYPE_VMIRROR:
											result = tile->vFlip;
											break;
										case CONDITION_TYPE_BGPRIORITY:
											result = !tile->front;
											break;
										}
										if (r->conditionNegations[c]) result = !result;
										if (!result) {
											match = false;
											break;
										}
									}
									if (match) {
										tile->hasHDPackTile = true;
										tile->hdPackReplacementID = k;
										break;
									}
								}
							}
						}
						hasHDTile = tile->hasHDPackTile;
						if (tile->hasHDPackTile) {
							hdPackReplacement* r = &(pack.replacements[processedTileData->hash][tile->hdPackReplacementID]);
							SDL_Surface* surface = pack.images[r->imageID];
							SDL_LockSurface(surface);
							Uint32* pixel_ptr = (Uint32*)surface->pixels + ((r->y + (spPixel->visibleLine * pack.scale) + (tile->vFlip ? pack.scale - 1 : 0)) * surface->pitch) + ((r->x + (spPixel->x * pack.scale) + (tile->hFlip ? pack.scale - 1 : 0)) * 4);
							for (int subY = 0; subY < pack.scale; subY++) {
								Uint32* row_pixel_ptr = pixel_ptr;
								for (int subX = 0; subX < pack.scale; subX++) {
									if (r->brightness != 1.0) {
										Uint32 colour = adjustColourForBrightness(*row_pixel_ptr, r->brightness);
										fillSpritePixel(pack.tmpFrontSpr + (subY * pack.scale) + subX, pack.tmpBackSpr + (subY * pack.scale) + subX, colour);
									}
									else
										fillSpritePixel(pack.tmpFrontSpr + (subY * pack.scale) + subX, pack.tmpBackSpr + (subY * pack.scale) + subX, *row_pixel_ptr);
									if (tile->hFlip) 
										row_pixel_ptr--;
									else
										row_pixel_ptr++;
								}
								if (tile->vFlip)
									pixel_ptr -= surface->pitch / 4;
								else
									pixel_ptr += surface->pitch / 4;
							}
							SDL_UnlockSurface(surface);
						}

						if(!hasHDTile) {
							if (spPixel->colourID != 0xFF) {
								if (tile->front) {
									for (int subY = 0; subY < pack.scale; subY++) {
										for (int subX = 0; subX < pack.scale; subX++) {
											fillSpritePixel(pack.tmpFrontSpr + (subY * pack.scale) + subX, pack.tmpBackSpr + (subY * pack.scale) + subX, rawColors[myConsole->ppu.spScreenPixels[spPixelID][spID].colourID]);
										}
									}
								}
								else {
									for (int subY = 0; subY < pack.scale; subY++) {
										for (int subX = 0; subX < pack.scale; subX++) {
											fillSpritePixel(pack.tmpBackSpr + (subY * pack.scale) + subX, pack.tmpFrontSpr + (subY * pack.scale) + subX, rawColors[myConsole->ppu.spScreenPixels[spPixelID][spID].colourID]);
										}
									}
								}
							}
						}
						spID--;
					}
					spPixelID++;
				}
			}
			//copy sprite pixels to texture
			for(int subY = 0; subY < pack.scale; subY++) {
				for (int subX = 0; subX < pack.scale; subX++) {
					*(tmpPixelsBackSprColour + (subY * tmpPitchBackSprColour) + subX) = *(pack.tmpBackSpr + (subY * pack.scale) + subX);
					*(tmpPixelsFrontSprColour + (subY * tmpPitchFrontSprColour) + subX) = *(pack.tmpFrontSpr + (subY * pack.scale) + subX);
				}
			}
			tmpPixelsBackSprColour += pack.scale;
			tmpPixelsFrontSprColour += pack.scale;

			pixelID++;
		}
		tmpPixelsBackSprColour += tmpPitchBackSprColour * (pack.scale - 1);
		tmpPixelsFrontSprColour += tmpPitchFrontSprColour * (pack.scale - 1);
		tmpPixelsBackGround += tmpPitchBackGround * (pack.scale - 1);
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
}

Uint64 render::convertStringToPattern(string s) {
	Uint64 pattern = 0;
	for (int i = 0; i < s.length(); i+=2) {
		pattern <<= 8;
		string byteString = s.substr(i, 2);
		pattern |= stoi(byteString, nullptr, 16);
	}
	return pattern;
}

void render::fillSpritePixel(Uint32* fillPixel, Uint32* blockPixel, Uint32 colour) {
	Uint16 alpha = colour & 0xFF;
	if (alpha == 0xFF) {
		*fillPixel = colour;
		*blockPixel = 0;
	}
	else if (alpha > 0) {
		Uint16 invAlpha = 0xFF - alpha;

		Uint64 blockRB = ((Uint64)*blockPixel & 0xFF00FF00) * invAlpha;
		Uint64 blockGA = (*blockPixel & 0x00FF00FF) * invAlpha;
		*blockPixel = ((blockRB >> 8) & 0xFF00FF00) | ((blockGA >> 8) & 0x00FF00FF);

		Uint64 rb = ((Uint64)*fillPixel & 0xFF00FF00) * invAlpha;
		Uint64 g = (*fillPixel & 0x00FF00FF) * invAlpha;
		*fillPixel = ((rb >> 8) & 0xFF00FF00) | ((g >> 8) & 0x00FF00FF) + colour;
	}

}

bool render::checkGlobalCondition(hdPackCondition* cnd) {
	bool result = false;
	processedTile* condTileData;

	switch (cnd->type) {
	case CONDITION_TYPE_FRAMERANGE:
		if (cnd->hasGlobalResult) {
			result = cnd->globalResult;
		}
		else {
			result = ((myConsole->ppu.frame % cnd->divisorValue) >= cnd->compareValue);
			cnd->globalResult = result;
			cnd->hasGlobalResult = true;
		}
		break;
	case CONDITION_TYPE_MEMORYCHECK:
	case CONDITION_TYPE_MEMORYCHECKCONSTANT:
		if (cnd->hasGlobalResult) {
			result = cnd->globalResult;
		}
		else {
			result = myConsole->rom.mapper->checkMemory(&(cnd->memCheck));
			cnd->globalResult = result;
			cnd->hasGlobalResult = true;
		}
		break;
	case CONDITION_TYPE_PPUMEMORYCHECK:
	case CONDITION_TYPE_PPUMEMORYCHECKCONSTANT:
		if (cnd->hasGlobalResult) {
			result = cnd->globalResult;
		}
		else {
			result = myConsole->rom.mapper->checkPPUMemory(&(cnd->memCheck));
			cnd->globalResult = result;
			cnd->hasGlobalResult = true;
		}
		break;
	case CONDITION_TYPE_SPRITEATPOSITION:
		if (cnd->hasGlobalResult) {
			result = cnd->globalResult;
		}
		else {
			result = false;
			for (Uint16 idx = 0; idx < myConsole->ppu.spScreenTiles.size(); idx++) {
				spTileDetails* spTile = &(myConsole->ppu.spScreenTiles[idx]);
				if (spTile->x == cnd->x && spTile->y == cnd->y && spTile->palette == cnd->palette) {
					processedTile* condTileData = &(myConsole->rom.processedCHRData[spTile->patternID]);
					if (hasCHRROM) {
						if (condTileData->tileID == cnd->tileID) {
							result = true;
							break;
						}
					}
					else {
						if (condTileData->bitPlane[0] == cnd->pattern[0] && condTileData->bitPlane[1] == cnd->pattern[1]) {
							result = true;
							break;
						}
					}
				}
			}
			cnd->globalResult = result;
			cnd->hasGlobalResult = true;
		}
		break;
	case CONDITION_TYPE_TILEATPOSITION:
		if (cnd->hasGlobalResult) {
			result = cnd->globalResult;
		}
		else {
			result = false;
			for (Uint8 scr = 0; scr < 4; scr++) {
				for (Uint16 i = 0; i < 960; i++) {
					bgTileDetails* bgTile = &(myConsole->ppu.bgScreenTiles[scr][i]);
					if (bgTile->visible && bgTile->x == cnd->x && bgTile->y == cnd->y && bgTile->palette == cnd->palette) {
						processedTile* condTileData = &(myConsole->rom.processedCHRData[bgTile->patternID]);
						if (hasCHRROM) {
							if (condTileData->tileID == cnd->tileID) {
								result = true;
								break;
							}
						}
						else {
							if (condTileData->bitPlane[0] == cnd->pattern[0] && condTileData->bitPlane[1] == cnd->pattern[1]) {
								result = true;
								break;
							}
						}
					}
				}
			}
			cnd->globalResult = result;
			cnd->hasGlobalResult = true;
		}
		break;
	}
	return result;
}

bool render::checkSpriteNearbyCondition(hdPackCondition* cnd, Sint16 x, Sint16 y) {
	bool result = false;
	for (Uint16 idx = 0; idx < myConsole->ppu.spScreenTiles.size(); idx++) {
		spTileDetails* spTile = &(myConsole->ppu.spScreenTiles[idx]);
		if (spTile->x == x && spTile->y == y && spTile->palette == cnd->palette) {
			processedTile* condTileData = &(myConsole->rom.processedCHRData[spTile->patternID]);
			if (hasCHRROM) {
				if (condTileData->tileID == cnd->tileID) {
					result = true;
					break;
				}
			}
			else {
				if (condTileData->bitPlane[0] == cnd->pattern[0] && condTileData->bitPlane[1] == cnd->pattern[1]) {
					result = true;
					break;
				}
			}
		}
	}
	return result;
}

bool render::checkTileNearbyCondition(hdPackCondition* cnd, Sint16 x, Sint16 y) {
	bool result = false;
	for (Uint8 scr = 0; scr < 4; scr++) {
		for (Uint16 i = 0; i < 960; i++) {
			bgTileDetails* bgTile = &(myConsole->ppu.bgScreenTiles[scr][i]);
			if (bgTile->visible && bgTile->x == x && bgTile->y == y && bgTile->palette == cnd->palette) {
				processedTile* condTileData = &(myConsole->rom.processedCHRData[bgTile->patternID]);
				if (hasCHRROM) {
					if (condTileData->tileID == cnd->tileID) {
						result = true;
						break;
					}
				}
				else {
					if (condTileData->bitPlane[0] == cnd->pattern[0] && condTileData->bitPlane[1] == cnd->pattern[1]) {
						result = true;
						break;
					}
				}
			}
		}
	}
	return result;
}

Uint32 render::adjustColourForBrightness(Uint32 colour, double brightness) {
	Uint8 rC = (colour >> 24) & 0xFF;
	Uint8 gC = (colour >> 16) & 0xFF;
	Uint8 bC = (colour >> 8) & 0xFF;
	rC = (Uint8)((float)rC * brightness);
	gC = (Uint8)((float)gC * brightness);
	bC = (Uint8)((float)bC * brightness);
	return (colour & 0x000000FF) | (rC << 24) | (gC << 16) | (bC << 8);
}
