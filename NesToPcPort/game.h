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
	void SUB_00000A();
	void SUB_000052();
	void SUB_000187();
	void SUB_00038A();
	void SUB_01A333();
	void SUB_01C0D7();
	void SUB_01C0F7();
	void SUB_01C102();
	void SUB_01C11F();
	void SUB_01C132();
	void SUB_01C13F();
	void SUB_01C14B();
	void SUB_01C16D();
	void SUB_01C18E();
	void SUB_01C19B();
	void SUB_01C1A7();
	void SUB_01C1CF();
	void SUB_01C1D4();
	void SUB_01C1D6();
	void SUB_01C1D8();
	void SUB_01C1E4();
	void SUB_01C365();
	void SUB_01C371();
	void SUB_01C373();
	void SUB_01C37A();
	void SUB_01C474();
	void SUB_01C4A4();
	void SUB_01C4A8();
	void SUB_01C4AA();
	void SUB_01C8C3();
	void SUB_01C8CD();
	void SUB_01C903();
	void SUB_01C90D();
	void SUB_01C917();
	void SUB_01C91C();
	void SUB_01C95D();
	void SUB_01C994();
	void SUB_01CA6D();
	void SUB_01CA8B();
	void SUB_01CAAF();
	void SUB_01CAE3();
	void SUB_01CAE7();
	void SUB_01CB11();
	void SUB_01CC3D();
	void SUB_01CC5F();
	void SUB_01CC68();
	void SUB_01CC75();
	void SUB_01CC95();
	void SUB_01CCEE();
	void SUB_01CCF0();
	void SUB_01CCF2();
	void SUB_01CCF6();
	void SUB_01CFBD();
	void SUB_01CFF9();
	void SUB_01D10E();
	void SUB_01D132();
	void SUB_01D162();
	void SUB_01D195();
	void SUB_01D196();
	void SUB_01D1BE();
	void SUB_01DC50();
	void SUB_01DEDC();
	void SUB_01DF06();
	void SUB_01DF0E();
	void SUB_01DF79();
	void SUB_01E09A();
	void SUB_01E0E2();
	void SUB_01E0E4();
	void SUB_01E0E9();
	void SUB_01E0F4();
	void SUB_01E109();
	void SUB_01E3F4();
	void SUB_01E3FF();
	void SUB_01E4CC();
	void SUB_01E4D9();
	void SUB_01E8F0();
	void SUB_01E924();
	void SUB_01E92B();
	void SUB_01E931();
	void SUB_01EA72();
	void SUB_01EA77();
	void SUB_01EA80();
	void SUB_01EAA9();
	void SUB_01EAB2();
	void SUB_01EAB8();
	void SUB_01EABD();
	void SUB_01EACB();
	void SUB_01EADD();
	void SUB_01EB08();
	void SUB_01EC60();
	void SUB_01EC72();
	void SUB_01EF04();
	void SUB_01EF84();
	void SUB_01F131();
	void SUB_01F1DB();
	void SUB_01F42C();
	void SUB_01F5EA();
	void SUB_01F60F();
	void SUB_01F62D();
	void SUB_01F68C();
	void SUB_01F699();
	void SUB_01F69E();
	void SUB_01F7ED();
	void SUB_01F817();
	void SUB_01F841();
	void SUB_01F868();
	void SUB_01F87C();
	void SUB_01F87D();
	void SUB_01F909();
	void SUB_01F912();
	void SUB_01F94F();
	void SUB_01F9D4();
	void SUB_01FA6A();
	void SUB_01FA8E();
	void SUB_01FB05();
	void SUB_01FB06();
	void SUB_01FC97();
	void SUB_01FCD0();
	void SUB_01FD18();
	void SUB_01FD23();
	void SUB_01FD7E();
	void SUB_01FE96();
	void jump(Uint16 target);


};

