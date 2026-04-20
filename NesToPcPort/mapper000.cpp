#include "mapper000.h"
#include "rom.h"
#include "console.h"
#include "memory.h"

void mapper000::init() {
}

Uint8 mapper000::readCPU(Uint16 address) {
	if (address < 0x2000) {
		return rom->mapper->ram[address & 0x07FF];
	}
	else if (address < 0x4000) {
		return rom->myConsole->ppu.readReg(address & 0x2007);
	}
	else if (address == 0x4015) {
		return rom->myConsole->apu.readReg(address);
	}
	else if (address == 0x4016 || address == 0x4017) {
		return rom->myConsole->iop.readReg(address);
	}
	else if (address < 0x4020) {
	}
	else if (address < 0x8000) {
	}
	else {
		Uint16 prgAddress = (address - 0x8000) % rom->prgROMSize;
		return rom->prgData[prgAddress];
	}
}

void mapper000::writeCPU(Uint16 address, Uint8 value) {
	if (address < 0x2000) {
		rom->mapper->ram[address & 0x07FF] = value;
	}
	else if (address < 0x4000) {
		rom->myConsole->ppu.writeReg(address & 0x2007, value);
	}
	else if (address < 0x4014) {
		rom->myConsole->apu.writeReg(address, value);
	}
	else if (address == 0x4014) {
		rom->myConsole->ppu.writeReg4014(value);
	}
	else if (address == 0x4015) {
		rom->myConsole->apu.writeReg(address, value);
	}
	else if (address == 0x4016) {
		rom->myConsole->iop.writeReg(address, value);
	}
	else if (address == 0x4017) {
		rom->myConsole->apu.writeReg(address, value);
	}
}

Uint8 mapper000::readPPU(Uint16 address) {
	if (address < 0x2000) {
		return rom->chrData[address];
	}
	else if (address < 0x2400) {
		return rom->myConsole->ppu.nametable[address - 0x2000]; //table 1
	}
	else if (address < 0x2800) {
		if (rom->nametableArrangementH) {
			return rom->myConsole->ppu.nametable[address - 0x2000]; //table 2
		}
		else {
			return rom->myConsole->ppu.nametable[address - 0x2400]; //table 1
		}
	}
	else if (address < 0x2C00) {
		if (rom->nametableArrangementH) {
			return rom->myConsole->ppu.nametable[address - 0x2800]; //table 1
		}
		else {
			return rom->myConsole->ppu.nametable[address - 0x2400]; //table 2
		}
	}
	else if (address < 0x3000) {
		return rom->myConsole->ppu.nametable[address - 0x2800]; //table 2
	}
	else if (address < 0x3F00) {
		return 0; // Unused area
	}
	else if (address < 0x4000) {
		return rom->myConsole->ppu.paletteRAM[address & 0x1F];
	}
}

void mapper000::writePPU(Uint16 address, Uint8 value) {
	if (address < 0x2000) {
		rom->writeCHRData(address, value);
	}
	else if (address < 0x2400) {
		rom->myConsole->ppu.nametable[address - 0x2000] = value; //table 1
	}
	else if (address < 0x2800) {
		if (rom->nametableArrangementH) {
			rom->myConsole->ppu.nametable[address - 0x2000] = value; //table 2
		}
		else {
			rom->myConsole->ppu.nametable[address - 0x2400] = value; //table 1
		}
	}
	else if (address < 0x2C00) {
		if (rom->nametableArrangementH) {
			rom->myConsole->ppu.nametable[address - 0x2800] = value; //table 1
		}
		else {
			rom->myConsole->ppu.nametable[address - 0x2400] = value; //table 2
		}
	}
	else if (address < 0x3000) {
		rom->myConsole->ppu.nametable[address - 0x2800] = value; //table 2
	}
	else if (address < 0x3F00) {
	}
	else if (address < 0x4000) {
		rom->myConsole->ppu.paletteRAM[address & 0x1F] = value;
		Uint32 mask = 0x000000FF << ((3 - (address & 0x03)) * 8);
		rom->myConsole->ppu.palettes[(address & 0x0010) >> 4][(address & 0x0F) >> 2] &= ~mask;
		rom->myConsole->ppu.palettes[(address & 0x0010) >> 4][(address & 0x0F) >> 2] |= (value << ((3 - (address & 0x03)) * 8));
	}
}

processedTile* mapper000::getProcessedTile(Uint16 tileID) {
	return &(rom->processedCHRData[tileID]);
}