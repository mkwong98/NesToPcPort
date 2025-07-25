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

	void pushAddress(Uint16 address);
	void popAddress();
	void pushStatus();
	void popStatus();
	void opPLA();
	void opPHA();

	void wait();
	void signal();
	void repeat();
	void brk();

	struct threadData {
		int threadIdx;
		Uint32 threadId;
		SDL_Thread* thread;
		SDL_Mutex* lock;
		SDL_Condition* cond;
		game* myGame;
		Uint32 continueAddress;
		int xIdx;
		bool waitingNMI;
	};

	void switchThread();
	void createThread(Uint32 address);
	void markThread();
	void holdThread(int threadIdx);

	static int gameThread(void* ptr);
	std::vector<threadData> threadList;
	threadData runningThread;
	int xIdx;

	void SUB_000000();
	void SUB_00001B();
	void SUB_00004C();
	void SUB_0000DA();
	void SUB_0001E6();
	void SUB_0001EE();
	void SUB_000246();
	void SUB_00024F();
	void SUB_00026C();
	void SUB_0002B9();
	void SUB_001FDB();
	void SUB_002050();
	void SUB_00205B();
	void SUB_00206B();
	void SUB_002094();
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
	void SUB_00273E();
	void SUB_00275A();
	void SUB_002816();
	void SUB_002834();
	void SUB_002855();
	void SUB_002893();
	void SUB_0028AE();
	void SUB_0028C6();
	void SUB_0029D3();
	void SUB_0029F4();
	void SUB_002A00();
	void SUB_002A61();
	void SUB_002B2C();
	void SUB_002C14();
	void SUB_002C1A();
	void SUB_002D0E();
	void SUB_002D39();
	void SUB_002DC9();
	void SUB_002E8C();
	void SUB_002EAD();
	void SUB_002EF0();
	void SUB_002F55();
	void SUB_002F7A();
	void SUB_003048();
	void SUB_0030BC();
	void SUB_0030E5();
	void SUB_003102();
	void SUB_00311F();
	void SUB_00312B();
	void SUB_003148();
	void SUB_00316F();
	void SUB_0031D7();
	void SUB_00337B();
	void SUB_0033CF();
	void SUB_0033D5();
	void SUB_0033E3();
	void SUB_0033E8();
	void SUB_0033F3();
	void SUB_0033F3_B();
	void SUB_00340A();
	void SUB_0034E0();
	void SUB_0034F9();
	void SUB_003509();
	void SUB_003533();
	void SUB_003588();
	void SUB_00365F();
	void SUB_0037C3();
	void SUB_003922();
	void SUB_00393D();
	void SUB_00396C();
	void SUB_0039E5();
	void SUB_003A12();
	void SUB_003C86();
	void SUB_003CAF();
	void SUB_003CBA();
	void SUB_003CBF();
	void SUB_003CF1();
	void SUB_003D3A();
	void SUB_003F58();
	void SUB_003F74();
	void SUB_003F7F();
	void reset();
	void nmi();
	void SUB_0041AD();
	void SUB_0041C7();
	void SUB_0041F5();
	void SUB_004230();
	void SUB_004237();
	void SUB_004240();
	void SUB_004251();
	void SUB_004275();
	void SUB_004288();
	void SUB_0042A4();
	void SUB_0042C0();
	void SUB_004306();
	void SUB_00432D();
	void SUB_0043CA();
	void SUB_00445A();
	void SUB_00453F();
	void SUB_004546();
	void SUB_00454D();
	void SUB_00506A();
	void SUB_0050B5();
	void SUB_00515B();
	void SUB_005165();
	void SUB_00519A();
	void SUB_0051AC();
	void SUB_0051AE();
	void SUB_0051B5();
	void SUB_0051B5_B();
	void SUB_0051C0();
	void SUB_0051C0_B();
	void SUB_0051FC();
	void SUB_0051FC_B();
	void SUB_005214();
	void SUB_005214_B();
	void SUB_00525B();
	void SUB_0052AA();
	void SUB_0052DE();
	void SUB_0052F3();
	void SUB_0052FB();
	void SUB_005303();
	void SUB_0053B9();
	void SUB_005472();
	void SUB_005589();
	void SUB_005592();
	void SUB_005593();
	void SUB_0055A5();
	void SUB_0055BC();
	void SUB_005617();
	void SUB_00563E();
	void SUB_005698();
	void SUB_0056B7();
	void SUB_00570E();
	void SUB_00572F();
	void SUB_00574E();
	void SUB_005769();
	void SUB_00579B();
	void SUB_0057A1();
	void SUB_0057F0();
	void SUB_005E5C();
	void SUB_005E82();
	void SUB_005E8E();
	void SUB_005E92();
	void SUB_005E9D();
	void SUB_0061E0();
	void SUB_006229();
	void SUB_006240();
	void SUB_006C0C();
	void SUB_006C45();
	void SUB_006C79();
	void SUB_006CAD();
	void SUB_006CF1();
	void SUB_006D2A();
	void SUB_006D39();
	void SUB_006D48();
	void SUB_006D57();
	void SUB_006D5C();
	void SUB_006D67();
	void SUB_006E36();
	void SUB_006E5F();
	void SUB_006E8C();
	void SUB_006EB4();
	void SUB_006ED7();
	void SUB_006EEA();
	void SUB_006F00();
	void SUB_006F13();
	void SUB_006F2B();
	void SUB_006F49();
	void SUB_006F6B();
	void SUB_006F6E();
	void SUB_006F7B();
	void SUB_006F7D();
	void SUB_006F8E();
	void SUB_006F91();
	void SUB_006F96();
	void SUB_006F98();
	void SUB_006FA0();
	void SUB_006FAD();
	void SUB_006FB5();
	void SUB_006FBD();
	void SUB_006FC5();
	void SUB_006FCD();
	void SUB_006FDA();
	void SUB_007054();
	void SUB_0070CE();
	void SUB_0070FD();
	void SUB_00715A();
	void SUB_007176();
	void SUB_00719C();
	void SUB_0071CB();
	void SUB_00734C();
	void SUB_007386();
	void SUB_00742C();
	void SUB_0074BA();
	void SUB_007507();
	void SUB_007570();
	void SUB_0075BC();
	void SUB_0076D1();
	void SUB_0076E8();
	void SUB_007775();
	void SUB_0077B1();
	void SUB_0077C3();
	void SUB_0077CD();
	void SUB_0077FC();
	void SUB_00783C();
	void SUB_00794A();
	void SUB_007955();
	void SUB_007961();
	void SUB_00797D();
	void SUB_0079AB();
	void SUB_0079E1();
	void SUB_007A32();
	void SUB_007B00();
	void indirectJump(Uint16 target);
};

