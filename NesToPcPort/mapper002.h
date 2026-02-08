#pragma once
#include "mapper.h"
class mapper002: public mapper
{
public:
	Uint8 prgBank;
	Uint32 prgBank0Offset;
	Uint32 prgBank1Offset;

	void init();
	Uint8 readCPU(Uint16 address);
	void writeCPU(Uint16 address, Uint8 value);
	Uint8 readPPU(Uint16 address);
	void writePPU(Uint16 address, Uint8 value);
	Uint32 readRealAddress(Uint16 address);
};

