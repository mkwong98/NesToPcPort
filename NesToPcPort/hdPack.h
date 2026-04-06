#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "string"
#include "mapper.h"

using namespace std;

const Uint8 CONDITION_TYPE_NONE = 0;
const Uint8 CONDITION_TYPE_HMIRROR = 1;
const Uint8 CONDITION_TYPE_VMIRROR = 2;
const Uint8 CONDITION_TYPE_BGPRIORITY = 3;
const Uint8 CONDITION_TYPE_TILENEARBY = 4;
const Uint8 CONDITION_TYPE_SPRITENEARBY = 5;
const Uint8 CONDITION_TYPE_TILEATPOSITION = 6;
const Uint8 CONDITION_TYPE_SPRITEATPOSITION = 7;
const Uint8 CONDITION_TYPE_MEMORYCHECK = 8;
const Uint8 CONDITION_TYPE_PPUMEMORYCHECK = 9;
const Uint8 CONDITION_TYPE_MEMORYCHECKCONSTANT = 10;
const Uint8 CONDITION_TYPE_PPUMEMORYCHECKCONSTANT = 11;
const Uint8 CONDITION_TYPE_FRAMERANGE = 12;

struct hdPackCondition {
	string name;
	Uint8 type;

	Sint16 x;
	Sint16 y;
	Uint32 tileID;
	Uint64 pattern[2];
	Uint32 palette;

	memoryCheck memCheck;

	Uint32 divisorValue;
	Uint32 compareValue;

	bool globalResult;
};

struct hdPackBackground {
	vector<Uint16> conditionIDs;
	vector<bool> conditionNegations;
	Uint16 imageID;
	double brightness;
	double hScrollRatio;
	double vScrollRatio;
	Uint8 priority;
	Uint16 xOffset;
	Uint16 yOffset;
};

struct hdPackReplacement {
	vector<Uint16> conditionIDs;
	vector<bool> conditionNegations;
	Uint16 imageID;
	Uint32 tileID;
	Uint64 pattern[2];
	Uint32 palette;
	Uint16 x;
	Uint16 y;
	double brightness;
	bool asDefault;
};

struct hdPackAdditionalTile {
	Uint32 tileID;
	Uint64 pattern[2];
	Uint32 palette;
	Sint16 x;
	Sint16 y;
	Uint32 addTileID;
	Uint64 addPattern[2];
	Uint32 addPalette;
};

struct hdPackSet {
	Uint8 scale;
	vector<hdPackCondition> conditions;
	vector<SDL_Texture*> images;
	vector<hdPackReplacement> replacements;
	vector<string> backgroundImgNames;
	vector<SDL_Texture*> backgroundImages;
	vector<hdPackBackground> backgrounds;

	SDL_Texture* backColourLayer;
	SDL_Texture* backSpriteLayer;
	SDL_Texture* backgroundLayer;
	SDL_Texture* frontSpriteLayer;

};