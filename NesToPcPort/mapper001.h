#pragma once
#include "mapper.h"
class mapper001 : public mapper
{
public: 
	Uint8 prgMode;
	Uint8 chrMode;
	Uint8 shiftReg;
	Uint8 writeCnt;
	Uint8 controlReg;
	Uint8 mirroring;
	Uint8 chrBank0;
	Uint32 chrBank0Offset;
	Uint8 chrBank1;
	Uint32 chrBank1Offset;
	Uint8 prgBank;
	Uint32 prgBank0Offset;
	Uint32 prgBank1Offset;

	void init();
	Uint8 readCPU(Uint16 address);
	void writeCPU(Uint16 address, Uint8 value);
	Uint8 readPPU(Uint16 address);
	void writePPU(Uint16 address, Uint8 value);
	Uint32 readRealAddress(Uint16 address);
	string getMapperMode();

private:
	void setPRGMode(Uint8 mode);
	void setCHRMode(Uint8 mode);
};

