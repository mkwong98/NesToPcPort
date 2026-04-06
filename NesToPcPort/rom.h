#pragma once
#include <SDL3/SDL.h>

class mapper;
class console;

struct processedTile {
	Uint32 tileID;
	bool changed;
	Uint64 bitPlane[2];
	Uint16 stripe[8];
	Uint8 hash;
};

class rom
{
public:
	console* myConsole;
	Uint8* chrData;
	processedTile* processedCHRData;
	Uint8* prgData;
	Uint8* prgRAM;
		
	mapper* mapper;

	void loadROM(SDL_IOStream* romFile);
	void reprocessChangedCHRRAMData();
	void writeCHRData(Uint32 address, Uint8 value);
	~rom();

	bool nametableArrangementH; //0 = vertical arrangement / horizontal mirrored
	bool hasPersistentMemory;
	bool hasTrainer;
	bool useAlternativeNametableLayout;
	Uint32 prgROMSize;
	Uint32 chrROMSize;

private:
	processedTile getProcessedCHRData(Uint32 tileID);
};

