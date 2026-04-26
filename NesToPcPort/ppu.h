#pragma once
#include <SDL3/SDL.h>
#include <vector>

using namespace std;

const Uint8 MAX_SPRITE_PER_LINE = 8; // maximum number of sprites per scanline

class console;

struct bgTileDetails {
	Uint16 patternID;
	Uint32 palette;
	Sint16 x;
	Sint16 y;
	bool visible;
	bool checkedForHDPackTile;
	bool hasHDPackTile;
	Uint32 hdPackReplacementID;
};

struct spTileDetails {
	Uint16 patternID;
	Uint32 palette;
	Uint8 hash; //use by addition
	Uint16 idx; //use by addition
	Uint8 x;
	Uint8 y;
	bool hFlip;
	bool vFlip;
	bool front;
	Uint8 spriteID;
	bool checkedForHDPackTile;
	bool hasHDPackTile;
	Uint32 hdPackReplacementID;
};

struct bgPixelDetails {
	Uint8 screenID;
	Uint16 tileID;
	Uint8 colourID;
	Uint8 x;
	Uint8 y;
};

struct spPixelDetails {
	Uint16 tileID;
	Uint8 colourID;
	Uint8 x;
	Uint8 visibleLine;
	bool isAddition;
};

class ppu
{
public:
	console* myConsole;
	Uint8 nametable[2048];
	Uint8 paletteRAM[32];
	Uint32 palettes[2][4];
	bool oamVisible[128];
	Uint16 oamIdx[128];
	Uint8 bg0ColourIDs[256 * 240];
	bgTileDetails bgScreenTiles[4][32 * 30];
	vector<spTileDetails> spScreenTiles;
	bgPixelDetails bgScreenPixels[256 * 240];
	vector<spPixelDetails> spPixelLocations[256 * 240];
	Uint64 frame;

	ppu();
	void render();
	void signalNMI();

	Uint8 readReg(Uint16 address);
	void writeReg(Uint16 address, Uint8 v);
	//reg 4014 OAMDMA
	void writeReg4014(Uint8 v);

//private:
	Uint8 ioBus;
	bool wReg;

	//reg 2000 PPUCTRL
	Uint16 baseNametableAddress;
	Uint8 vramAddressIncrement;
	Uint16 spritePatternTable;
	Uint16 bgPatternTable;
	Uint16 spritePatternTableTileOffset;
	Uint16 bgPatternTableTileOffset;

	Uint8 spriteHeight;
	bool vblankNMIEnabled;
	void writeReg2000();

	//reg 2001 PPUMASK
	bool greyscale;
	bool showLeftmostBg;
	bool showLeftmostSprite;
	bool bgRenderingEnable;
	bool spriteRenderingEnable;
	bool emphasizeRed;
	bool emphasizeGreen;
	bool emphasizeBlue;
	void writeReg2001();

	//reg 2002 PPUSTATUS
	bool spriteOverflow;
	bool sprite0Hit;
	bool vblank;
	void readReg2002();

	//reg 2003 OAMADDR
	Uint8 oamAddr;
	void writeReg2003();

	//reg 2004 OAMDATA
	Uint8 oam[256];
	void readReg2004();
	void writeReg2004();

	//reg 2005 PPUSCROLL
	Uint8 scrollX;
	Uint8 scrollY;
	void writeReg2005();

	//reg 2006 PPUADDR
	Uint16 vramAddress;
	void writeReg2006();

	//reg 2007 PPUDATA
	Uint8 readBuffer;
	void readReg2007();
	void writeReg2007();



};

