#include "rom.h"
#include "mapper000.h"
#include "mapper003.h"
#include "console.h"

void rom::loadROM(SDL_IOStream* romFile) {
	Uint8 header[16];
	SDL_ReadIO(romFile, header, 16);

	nametableArrangementH = header[6] & 0x01;
	hasPersistentMemory = header[6] & 0x02;
	hasTrainer = header[6] & 0x04;
	useAlternativeNametableLayout = header[6] & 0x08;

	Uint8 mapperID;
	mapperID = (header[7] & 0xF0) | ((header[6] >> 4) & 0x0f);
	switch (mapperID) {
	case 0:
		mapper = new mapper000();
		mapper->rom = this;
		myConsole->cpu.myMapper = mapper;
		mapper->init();
		break;
	case 3:
		mapper = new mapper003();
		mapper->rom = this;
		myConsole->cpu.myMapper = mapper;
		mapper->init();
		break;
	}

	if (hasTrainer) SDL_SeekIO(romFile, 512, SDL_IO_SEEK_CUR);
	prgROMSize = header[4] * 16384;
	prgData = (Uint8*)malloc(prgROMSize);
	SDL_ReadIO(romFile, prgData, prgROMSize);

	chrROMSize = header[5] * 8192;
	if (chrROMSize) {
		chrData = (Uint8*)malloc(chrROMSize);
		SDL_ReadIO(romFile, chrData, chrROMSize);
	}
	else {
		chrData = (Uint8*)malloc(0x2000);
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
}

