#include "mapper001.h"
#include "rom.h"
#include "console.h"
#include "memory.h"

void mapper001::init() {
	writeCnt = 0;
	shiftReg = 0x00;
	setPRGMode(3);
	setCHRMode(0);
	mirroring = rom->nametableArrangementH ? 2 : 3;
}

Uint32 mapper001::readRealAddress(Uint16 address) {
	if (address < 0xC000) {
		return (address - 0x8000 + prgBank0Offset) % rom->prgROMSize;
	}
	else {
		return (address - 0xC000 + prgBank1Offset) % rom->prgROMSize;
	}
}

string mapper001::getMapperMode() {
	return "";
}

void mapper001::setPRGMode(Uint8 mode) {
	prgMode = mode;
	switch (mode) {
	case 0:
	case 1:
		prgBank0Offset = 0;
		prgBank1Offset = 0x4000;
		break;
	case 2:
		prgBank0Offset = 0;
		prgBank1Offset = 0;
		break;
	case 3:
		prgBank0Offset = 0;
		prgBank1Offset = rom->prgROMSize - 0x4000;
		break;
	}
}

void mapper001::setCHRMode(Uint8 mode) {
	chrMode = mode;
	switch (mode) {
	case 0:
		chrBank0Offset = 0;
		chrBank1Offset = 0x1000;
		break;
	case 1:
		chrBank0Offset = 0;
		chrBank1Offset = 0;
		break;
	}
}

Uint8 mapper001::readCPU(Uint16 address) {
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
	else if (address < 0x6000) {
	}
	else if (address < 0x8000) {
		return rom->prgRAM[(address - 0x6000) & 0x7FF];
	}
	else if (address < 0xC000) {
		Uint32 prgAddress = (address - 0x8000 + prgBank0Offset) % rom->prgROMSize;
		return rom->prgData[prgAddress];
	}
	else {
		Uint32 prgAddress = (address - 0xC000 + prgBank1Offset) % rom->prgROMSize;
		return rom->prgData[prgAddress];
	}
}

void mapper001::writeCPU(Uint16 address, Uint8 value) {
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
	else if (address < 0x6000) {
	}
	else if (address < 0x8000) {
		rom->prgRAM[(address - 0x6000) & 0x7FF] = value;
	}
	else {
		if(value & 0x80) {
			shiftReg = 0x00;
			writeCnt = 0;
		}
		else {
			shiftReg >>= 1;
			shiftReg |= (value & 0x01) << 4;
			writeCnt++;
			if (writeCnt == 5) {
				Uint32 targetAddress = (address >> 13) & 0x03;
				switch (targetAddress) {
				case 0:
					controlReg = shiftReg & 0x1F;
					mirroring = controlReg & 0x03;
					setPRGMode((controlReg >> 2) & 0x03);
					setCHRMode((controlReg >> 4) & 0x01);
					break;
				case 1:
					chrBank0 = shiftReg & 0x1F;
					if (chrMode == 0) {
						chrBank0Offset = (chrBank0 & 0x1E) << 12;
						chrBank1Offset = ((chrBank0 & 0x1E) + 1) << 12;
					}
					else {
						chrBank0Offset = chrBank0 << 12;
					}
					break;
				case 2:
					chrBank1 = shiftReg & 0x1F;
					if (chrMode == 1) {
						chrBank1Offset = chrBank1 << 12;
					}
					break;
				case 3:
					prgBank = shiftReg & 0x0F;
					switch (prgMode) {
					case 0:
					case 1:
						prgBank0Offset = (prgBank & 0x0E) << 14;
						prgBank1Offset = ((prgBank & 0x0E) + 1) << 14;
						break;
					case 2:
						prgBank0Offset = 0;
						prgBank1Offset = (prgBank & 0x0F) << 14;
						break;
					case 3:
						prgBank0Offset = (prgBank & 0x0F) << 14;
						prgBank1Offset = rom->prgROMSize - 0x4000;
						break;
					}
					break;
				}
				shiftReg = 0x00;
				writeCnt = 0;
			}
		}
	}
}

Uint8 mapper001::readPPU(Uint16 address) {
	if (address < 0x1000) {
		return rom->chrData[address + chrBank0Offset];
	}
	else if (address < 0x2000) {
		return rom->chrData[address - 0x1000 + chrBank1Offset];
	}
	else if (address < 0x2400) {
		if (mirroring != 1) { // single screen lower
			return rom->myConsole->ppu.nametable[address - 0x2000]; //table 1
		}
		else { // single screen upper
			return rom->myConsole->ppu.nametable[address - 0x1C00]; //table 2
		}
	}
	else if (address < 0x2800) {
		if (mirroring == 0 || mirroring == 3) {
			return rom->myConsole->ppu.nametable[address - 0x2400]; //table 1
		}
		else {
			return rom->myConsole->ppu.nametable[address - 0x2000]; //table 2
		}
	}
	else if (address < 0x2C00) {
		if (mirroring == 0 || mirroring == 2) {
			return rom->myConsole->ppu.nametable[address - 0x2800]; //table 1
		}
		else {
			return rom->myConsole->ppu.nametable[address - 0x2400]; //table 2
		}
	}
	else if (address < 0x3000) {
		if (mirroring == 0) {
			return rom->myConsole->ppu.nametable[address - 0x2C00]; //table 1
		}
		else {
			return rom->myConsole->ppu.nametable[address - 0x2800]; //table 2
		}
	}
	else if (address < 0x3F00) {
		return 0; // Unused area
	}
	else if (address < 0x4000) {
		return rom->myConsole->ppu.paletteRAM[address & 0x1F];
	}
}

void mapper001::writePPU(Uint16 address, Uint8 value) {
	if (address < 0x1000) {
		if (rom->chrROMSize == 0) rom->chrData[address + chrBank0Offset] = value;
	}
	else if (address < 0x2000) {
		if (rom->chrROMSize == 0) rom->chrData[address - 0x1000 + chrBank1Offset] = value;
	}
	else if (address < 0x2400) {
		if (mirroring != 1) { // single screen lower
			rom->myConsole->ppu.nametable[address - 0x2000] = value; //table 1
		}
		else { // single screen upper
			rom->myConsole->ppu.nametable[address - 0x1C00] = value; //table 2
		}
	}
	else if (address < 0x2800) {
		if (mirroring == 0 || mirroring == 3) {
			rom->myConsole->ppu.nametable[address - 0x2400] = value; //table 1
		}
		else {
			rom->myConsole->ppu.nametable[address - 0x2000] = value; //table 2
		}

	}
	else if (address < 0x2C00) {
		if (mirroring == 0 || mirroring == 2) {
			rom->myConsole->ppu.nametable[address - 0x2800] = value; //table 1
		}
		else {
			rom->myConsole->ppu.nametable[address - 0x2400] = value; //table 2
		}
	}
	else if (address < 0x3000) {
		if (mirroring == 0) {
			rom->myConsole->ppu.nametable[address - 0x2C00] = value; //table 1
		}
		else {
			rom->myConsole->ppu.nametable[address - 0x2800] = value; //table 2
		}
	}
	else if (address < 0x3F00) {
	}
	else if (address < 0x4000) {
		rom->myConsole->ppu.paletteRAM[address & 0x1F] = value;
	}
}