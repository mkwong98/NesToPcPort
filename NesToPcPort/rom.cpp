#include "rom.h"
#include "mapper000.h"
#include "mapper001.h"
#include "mapper002.h"
#include "mapper003.h"
#include "console.h"

void rom::loadROM(SDL_IOStream* romFile) {
	Uint8 header[16];
	if (!SDL_ReadIO(romFile, header, 16)) {
		SDL_Log("Failed to ROM file");
		return;
	}
	nametableArrangementH = header[6] & 0x01;
	hasPersistentMemory = header[6] & 0x02;
	hasTrainer = header[6] & 0x04;
	useAlternativeNametableLayout = header[6] & 0x08;

	Uint8 mapperID;
	mapperID = (header[7] & 0xF0) | ((header[6] >> 4) & 0x0f);
	switch (mapperID) {
	case 0:
		mapper = new mapper000();
		break;
	case 1:
		mapper = new mapper001();
		break;
	case 2:
		mapper = new mapper002();
		break;
	case 3:
		mapper = new mapper003();
		break;
	}
	mapper->rom = this;
	myConsole->cpu.myMapper = mapper;
	mapper->init();

	if (hasTrainer) SDL_SeekIO(romFile, 512, SDL_IO_SEEK_CUR);
	prgROMSize = header[4] * 16384;
	prgData = (Uint8*)malloc(prgROMSize);
	SDL_ReadIO(romFile, prgData, prgROMSize);

	chrROMSize = header[5] * 8192;
	if (chrROMSize) {
		chrData = (Uint8*)malloc(chrROMSize);
		SDL_ReadIO(romFile, chrData, chrROMSize);
		processedCHRData = (processedTile*)malloc((chrROMSize / 16) * sizeof(processedTile));
		for(Uint32 i = 0; i < chrROMSize / 16; i++) {
			processedCHRData[i] = getProcessedCHRData(i);
		}
	}
	else {
		chrData = (Uint8*)malloc(0x2000);
		processedCHRData = (processedTile*)malloc(0x2000 / 16 * sizeof(processedTile));
	}

	prgRAM = (Uint8*)malloc(0x2000);
	memset(prgRAM, 0, 0x2000);
	if(hasPersistentMemory) {
		SDL_IOStream* savFile = SDL_IOFromFile("battery.dat", "rb");
		if (savFile) {
			SDL_ReadIO(savFile, prgRAM, 0x2000);
			SDL_CloseIO(savFile);
		}
	}

	SDL_CloseIO(romFile);
}

rom::~rom() {
	delete mapper;
	if(hasPersistentMemory) {
		SDL_IOStream* savFile = SDL_IOFromFile("battery.dat", "wb");
		if (savFile) {
			SDL_WriteIO(savFile, prgRAM, 0x2000);
			SDL_CloseIO(savFile);
		}
	}
	free(prgRAM);
	free(prgData);
	free(chrData);
	free(processedCHRData);
}

processedTile rom::getProcessedCHRData(Uint32 tileID) {
	processedTile tile;
	tile.tileID = tileID;
	tile.changed = false;
	tile.bitPlane[0] = 0;
	tile.bitPlane[1] = 0;
	tile.hash = 0;
	for (int i = 0; i < 8; i++) {
		Uint8 plane1 = chrData[tileID * 16 + i];
		Uint8 plane2 = chrData[tileID * 16 + i + 8];
		tile.bitPlane[0] <<= 8;
		tile.bitPlane[0] |= plane1;
		tile.bitPlane[1] <<= 8;
		tile.bitPlane[1] |= plane2;
		tile.stripe[i] = 0;
		for (Uint8 j = 0; j < 8; j++) {
			tile.stripe[i] |= ((plane2 & (0x01 << j)) << (j + 1));
			tile.stripe[i] |= ((plane1 & (0x01 << j)) << j);
		}
		tile.hash ^= plane1;
		tile.hash ^= plane2;
	}
	return tile;
}

void rom::reprocessChangedCHRRAMData() {
	if (chrROMSize) return; // ignore if CHR ROM exists
	for(Uint16 i = 0; i < 0x2000 / 16; i++) {
		if (processedCHRData[i].changed) {
			processedCHRData[i] = getProcessedCHRData(i);
		}
	}
}

void rom::writeCHRData(Uint32 address, Uint8 value) {
	if (chrROMSize) return; // ignore writes if CHR ROM exists
	if (chrData[address] != value) {
		chrData[address] = value;
		processedCHRData[address / 16].changed = true;
	}
}
