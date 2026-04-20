#pragma once
#include <SDL3/SDL.h>
#include "mapper.h"

class mapper004: public mapper
{
public:
	Uint8 controlReg;
	Uint8 chrMode;
	Uint8 prgMode;
	Uint8 bankSelect;

	Uint32 chrBankOffset[8];
	Uint32 prgBankOffset[4];

	Uint8 mirroring;

	Uint8 irqLatch;
	Uint8 irqCounter;
	bool irqEnable;

	void init();
	Uint8 readCPU(Uint16 address);
	void writeCPU(Uint16 address, Uint8 value);
	Uint8 readPPU(Uint16 address);
	void writePPU(Uint16 address, Uint8 value);
	Uint32 readRealAddress(Uint16 address);
	string getMapperMode();
	processedTile* getProcessedTile(Uint16 tileID);

private:
	void setPRGMode(Uint8 mode);
	void setCHRMode(Uint8 mode);
};

