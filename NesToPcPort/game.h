#pragma once
#include <SDL3/SDL.h>
#include <stack>
#include <vector>

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

	std::vector<Uint16> callStack;
	void pushAddress(Uint16 address);
	void popAddress();
	bool handleReturnAddress(Uint16 address, Uint16 expectedAddress);
	void pushStatus();
	void popStatus();
	void opPLA();
	void opPHA();

	void wait();
	void signal();
	void repeat();
	void brk();

	bool needWaitScanline;
	Uint8 waitScanline;
	void atScanline(Uint8 scanline);

	void atSprite0Hit();

	void reset();
	void nmi();
	void SUB_000216();
	void SUB_000228();
	void SUB_000232();
	void SUB_00024B();
	void SUB_00025A();
	void SUB_000268();
	void SUB_000276();
	void SUB_00027D();
	void SUB_000286();
	void SUB_0002A3();
	void SUB_0002B3();
	void SUB_0002CF();
	void SUB_000365();
	void SUB_000370();
	void SUB_0003A7();
	void SUB_000403();
	void SUB_000475();
	void SUB_000487();
	void SUB_000502();
	void SUB_00050F();
	void SUB_000560();
	void SUB_0005A1();
	void SUB_0005C9();
	void SUB_0005D3();
	void SUB_0005D4();
	void SUB_0005F8();
	void SUB_000602();
	void SUB_000603();
	void SUB_0006DD();
	void SUB_0006E9();
	void SUB_0006F5();
	void SUB_000720();
	void SUB_00072F();
	void SUB_00074D();
	void SUB_000757();
	void SUB_000850();
	void SUB_000A9C();
	void SUB_000AF4();
	void SUB_000B32();
	void SUB_000B9F();
	void SUB_000BC3();
	void SUB_000D7C();
	void SUB_000DCF();
	void SUB_000E7D();
	void SUB_000E83();
	void SUB_000EAA();
	void SUB_000EC4();
	void SUB_000EDF();
	void SUB_001097();
	void SUB_0011B2();
	void SUB_0014C5();
	void SUB_001658();
	void SUB_00172B();
	void SUB_001836();
	void SUB_0018A4();
	void SUB_001A0F();
	void SUB_001B01();
	void SUB_001F05();
	void SUB_00204A();
	void SUB_0020A4();
	void SUB_00218E();
	void SUB_00227E();
	void SUB_002316();
	void SUB_0024AC();
	void SUB_0026B3();
	void SUB_002767();
	void SUB_0028BB();
	void SUB_0028F4();
	void SUB_0029DF();
	void SUB_002A72();
	void SUB_002B05();
	void SUB_002D4D();
	void SUB_002D75();
	void SUB_002D9D();
	void SUB_003300();
	void SUB_00331A();
	void SUB_00331B();
	void SUB_003328();
	void SUB_003333();
	void SUB_003341();
	void SUB_003352();
	void SUB_00337F();
	void SUB_00338C();
	void SUB_003399();
	void SUB_0033A6();
	void SUB_0033D4();
	void SUB_0033DB();
	void SUB_0033E3();
	void SUB_0033F1();
	void SUB_0033FE();
	void SUB_003423();
	void SUB_00345E();
	void SUB_003475();
	void SUB_003484();
	void SUB_00349C();
	void SUB_0034AD();
	void SUB_0034D1();
	void SUB_003516();
	void SUB_00351C();
	void SUB_003535();
	void SUB_003537();
	void SUB_00353D();
	void SUB_00355A();
	void SUB_003561();
	void SUB_003572();
	void SUB_0035F1();
	void SUB_00360A();
	void SUB_003627();
	void SUB_003635();
	void SUB_003641();
	void SUB_003653();
	void SUB_003665();
	void SUB_003667();
	void SUB_003669();
	void SUB_00367F();
	void SUB_0036A1();
	void SUB_0036B0();
	void SUB_0036D0();
	void SUB_0036E6();
	void SUB_00370A();
	void SUB_00371D();
	void SUB_00372E();
	void SUB_00376C();
	void SUB_00376E();
	void SUB_00377D();


};

