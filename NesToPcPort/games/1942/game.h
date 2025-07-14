#pragma once
#include <SDL3/SDL.h>
#include <stack>

class console;
class mapper;

struct stackEntry {
	bool isPC;
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
	Uint32 threadSignal;

	game();
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

	void pushAddress(Uint16 address);
	void popAddress();
	void pushStatus();
	void popStatus();
	void opPLA();
	void opPHA();

	void wait();
	void signal();
	void repeat();

	void SUB_00001B();
	void SUB_001FDB();
	void SUB_002050();
	void SUB_0020D0();
	void SUB_0020EA();
	void SUB_00221F();
	void SUB_00225B();
	void SUB_0022CC();
	void SUB_0022E1();
	void SUB_002312();
	void SUB_00231E();
	void SUB_002332();
	void SUB_00234A();
	void SUB_00235A();
	void SUB_00236A();
	void SUB_00238F();
	void SUB_00393D();
	void SUB_00396C();
	void reset();
	void nmi();
	void SUB_0041AD();
	void SUB_0041C7();
	void SUB_0041F5();
	void SUB_0042C0();
	void indirectJump(Uint16 target);

};

