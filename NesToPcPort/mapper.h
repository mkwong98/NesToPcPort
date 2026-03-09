#pragma once
#include <SDL3/SDL.h>
#include <string>

using namespace std;

struct memoryCheck {
	static const Uint8 EQ = 0;
	static const Uint8 NE = 1;
	static const Uint8 GT = 2;
	static const Uint8 LS = 3;
	static const Uint8 GE = 4;
	static const Uint8 LE = 5;

	bool valueAsAddress;
	Uint16 address;
	Uint16 value;
	Uint8 opType;
	Uint8 mask;
};

class rom;

class mapper
{
public:
	rom* rom;
	Uint8 ram[0x800];

	virtual void init() = 0;
	virtual Uint8 readCPU(Uint16 address) = 0;
	virtual void writeCPU(Uint16 address, Uint8 value) = 0;
	virtual Uint8 readPPU(Uint16 address) = 0;
	virtual void writePPU(Uint16 address, Uint8 value) = 0;

	virtual Uint32 readRealAddress(Uint16 address);
	virtual string getMapperMode();
	bool checkMemory(memoryCheck* check);
};

