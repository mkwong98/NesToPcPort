#include "mapper004.h"
#include "rom.h"
#include "console.h"
#include "memory.h"

void mapper004::init() {
	setPRGMode(0);
	setCHRMode(0);
	if (rom->useAlternativeNametableLayout)
		mirroring = 2;
	else
		mirroring = rom->nametableArrangementH ? 0 : 1;
	prgBankOffset[3] = rom->prgROMSize - 0x2000;
}

void mapper004::setPRGMode(Uint8 mode) {
	prgMode = mode;
	switch (mode) {
	case 0:
		prgBankOffset[2] = rom->prgROMSize - 0x4000;
		break;
	case 1:
		prgBankOffset[0] = rom->prgROMSize - 0x4000;
		break;
	}
}

void mapper004::setCHRMode(Uint8 mode) {
	chrMode = mode;
}

Uint8 mapper004::readCPU(Uint16 address) {
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
	else {
		Uint32 prgAddress = ((address & 0x1FFF) + prgBankOffset[(address >> 13) & 0x03]) % rom->prgROMSize;
		return rom->prgData[prgAddress];
	}
}

void mapper004::writeCPU(Uint16 address, Uint8 value) {
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
	else if (address < 0xA000) {
		if (address & 0x0001) {
			controlReg = value;
			bankSelect = controlReg & 0x07;
			setPRGMode((controlReg >> 6) & 0x01);
			setCHRMode((controlReg >> 7) & 0x01);
		}
		else {
			switch (bankSelect) {
			case 0:
				if(chrMode == 0) {
					chrBankOffset[0] = (value & 0x7E) << 10;
					chrBankOffset[1] = ((value & 0x7E) + 1) << 10;
				}
				else {
					chrBankOffset[4] = (value & 0x7E) << 10;
					chrBankOffset[5] = ((value & 0x7E) + 1) << 10;
				}
				break;
			case 1:
				if (chrMode == 0) {
					chrBankOffset[2] = (value & 0x7E) << 10;
					chrBankOffset[3] = ((value & 0x7E) + 1) << 10;
				}
				else {
					chrBankOffset[6] = (value & 0x7E) << 10;
					chrBankOffset[7] = ((value & 0x7E) + 1) << 10;
				}
				break;
			case 2:
				if (chrMode == 0) 
					chrBankOffset[4] = (value & 0x7F) << 10;
				else 
					chrBankOffset[0] = (value & 0x7F) << 10;
				break;
			case 3:
				if (chrMode == 0)
					chrBankOffset[5] = (value & 0x7F) << 10;
				else
					chrBankOffset[1] = (value & 0x7F) << 10;
				break;
			case 4:
				if (chrMode == 0)
					chrBankOffset[6] = (value & 0x7F) << 10;
				else
					chrBankOffset[2] = (value & 0x7F) << 10;
				break;
			case 5:
				if (chrMode == 0)
					chrBankOffset[7] = (value & 0x7F) << 10;
				else
					chrBankOffset[3] = (value & 0x7F) << 10;
				break;
			case 6:
				if(prgMode == 0)
					prgBankOffset[0] = (value & 0x3F) << 13;
				else
					prgBankOffset[2] = (value & 0x3F) << 13;
				break;
			case 7:
				prgBankOffset[1] = (value & 0x3F) << 13;
				break;
			}
		}
	}
	else if (address < 0xC000) {
		if (address & 0x0001) {
		}
		else {
			if (!rom->useAlternativeNametableLayout)
				mirroring = value & 0x01;
		}
	}
	else if (address < 0xE000) {
		if (address & 0x0001) {
			irqCounter = 0;
		}
		else {
			irqLatch = value;
		}
	}
	else {
	}
}

Uint8 mapper004::readPPU(Uint16 address) {
	//if (address < 0x2000) {
	//	return rom->chrData[address + chrBankOffset];
	//}
	//else if (address < 0x2400) {
	//	return rom->myConsole->ppu.nametable[address - 0x2000]; //table 1
	//}
	//else if (address < 0x2800) {
	//	if (rom->nametableArrangementH) {
	//		return rom->myConsole->ppu.nametable[address - 0x2000]; //table 2
	//	}
	//	else {
	//		return rom->myConsole->ppu.nametable[address - 0x2400]; //table 1
	//	}
	//}
	//else if (address < 0x2C00) {
	//	if (rom->nametableArrangementH) {
	//		return rom->myConsole->ppu.nametable[address - 0x2800]; //table 1
	//	}
	//	else {
	//		return rom->myConsole->ppu.nametable[address - 0x2400]; //table 2
	//	}
	//}
	//else if (address < 0x3000) {
	//	return rom->myConsole->ppu.nametable[address - 0x2800]; //table 2
	//}
	//else if (address < 0x3F00) {
	//	return 0; // Unused area
	//}
	//else if (address < 0x4000) {
	//	return rom->myConsole->ppu.paletteRAM[address & 0x1F];
	//}
	return 0;
}

void mapper004::writePPU(Uint16 address, Uint8 value) {
	//if (address < 0x2000) {
	//	if (rom->chrROMSize == 0) rom->chrData[address + chrBankOffset] = value;
	//}
	//else if (address < 0x2400) {
	//	rom->myConsole->ppu.nametable[address - 0x2000] = value; //table 1
	//}
	//else if (address < 0x2800) {
	//	if (rom->nametableArrangementH) {
	//		rom->myConsole->ppu.nametable[address - 0x2000] = value; //table 2
	//	}
	//	else {
	//		rom->myConsole->ppu.nametable[address - 0x2400] = value; //table 1
	//	}
	//}
	//else if (address < 0x2C00) {
	//	if (rom->nametableArrangementH) {
	//		rom->myConsole->ppu.nametable[address - 0x2800] = value; //table 1
	//	}
	//	else {
	//		rom->myConsole->ppu.nametable[address - 0x2400] = value; //table 2
	//	}
	//}
	//else if (address < 0x3000) {
	//	rom->myConsole->ppu.nametable[address - 0x2800] = value; //table 2
	//}
	//else if (address < 0x3F00) {
	//}
	//else if (address < 0x4000) {
	//	rom->myConsole->ppu.paletteRAM[address & 0x1F] = value;
	//Uint32 mask = 0x000000FF << ((3 - (address & 0x03)) * 8);
	//rom->myConsole->ppu.palettes[(address & 0x0010) >> 4][(address & 0x0F) >> 2] &= ~mask;
	//rom->myConsole->ppu.palettes[(address & 0x0010) >> 4][(address & 0x0F) >> 2] |= (value << ((3 - (address & 0x03)) * 8));
	//}
}

processedTile* mapper004::getProcessedTile(Uint16 tileID) {
	return &(rom->processedCHRData[tileID]);
}