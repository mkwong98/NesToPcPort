#pragma once
#include <SDL3/SDL.h>
#include <vector>

class console;
class mapper;

struct stackEntry {
	bool isPC;
	Uint16 value;
};

struct callStackEntry {
	bool isManual;
	Uint16 value;
};

class game
{
public:
	console* myConsole;
	mapper* myMapper;
	Uint8 a;
	Uint8 x;
	Uint8 y;
	Uint8 s;
	bool flgC;
	bool flgZ;
	bool flgI;
	bool flgD;
	bool flgV;
	bool flgN;
	bool flgB;
	stackEntry poppedEntry;
	callStackEntry poppedStackEntry;
	Uint32 threadSignal;
	Uint32 pushedAddress;
	bool gameEnded;

	game();
	void initGame();
	void endGame();
	Uint8 getStatus();
	void setStatus(Uint8 p);
	void opADC(Uint8 v);
	void opSBC(Uint8 v);
	void opAND(Uint8 v);
	void opORA(Uint8 v);
	void opEOR(Uint8 v);
	void opBIT(Uint8 v);

	void opINC(Uint16 address, Uint8 repeatTimes);
	void opDEC(Uint16 address, Uint8 repeatTimes);
	void opINX(Uint8 repeatTimes);
	void opDEX(Uint8 repeatTimes);
	void opINY(Uint8 repeatTimes);
	void opDEY(Uint8 repeatTimes);

	void opASL_A(Uint8 repeatTimes);
	void opASL_M(Uint16 address, Uint8 repeatTimes);
	void opLSR_A(Uint8 repeatTimes);
	void opLSR_M(Uint16 address, Uint8 repeatTimes);
	void opROL_A(Uint8 repeatTimes);
	void opROL_M(Uint16 address, Uint8 repeatTimes);
	void opROR_A(Uint8 repeatTimes);
	void opROR_M(Uint16 address, Uint8 repeatTimes);
	void opCMP(Uint8 v1, Uint8 v2);

	void setLoadFlag(Uint8 v);

	std::vector<callStackEntry> callStack;
	void pushAddress(Uint16 address);
	void pushManualAddress(Uint16 address);
	void popAddress();
	bool handleReturnAddress(Uint16 address, Uint16 expectedAddress);

	void pushStatus();
	void popStatus();
	void opPLA();
	void opPHA();

	void wait(Uint8 type);
	void signal();

	void repeat();
	void brk();

	bool needWaitScanline;
	Uint8 waitScanline;
	void atScanline(Uint8 scanline);

	void atSprite0Hit();

	void nmi();
	void reset();
	void jump(Uint16 target);

};

