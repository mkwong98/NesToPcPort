#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"

void game::initGame() {
}

void game::endGame() {
}

void game::brk() {
    SUB_0004FF();
}

void game::reset() {
    myMapper->writeCPU(0x2000, 0x00);
    flgI = true;
    flgD = false;
    myMapper->writeCPU(0x2000, 0x00);
    x = 0xFF;
    s = x;
    opINX(1);
    myMapper->writeCPU(0x2001, x);
    myMapper->writeCPU(0x00F1, x);
    myMapper->writeCPU(0x4010, x);
    myMapper->writeCPU(0x0032, x);
    myMapper->writeCPU(0x00EB, x);
    myMapper->writeCPU(0x0033, x);
    a = 0x00;
    myMapper->writeCPU(0x002A, a);
    myMapper->writeCPU(0x0029, a);
    myMapper->writeCPU(0x4017, 0x40);
    pushAddress(0x000034);
    SUB_003E8D();
    if (poppedEntry.value != 0x000034) return;
    pushAddress(0x000037);
    SUB_00102F();
    if (poppedEntry.value != 0x000037) return;
    SUB_00003A();
    return;
}

void game::repeat() {
}


void game::SUB_00003A() {
    while (true) {
        pushAddress(0x00003A);
        SUB_0010FD();
        if (poppedEntry.value != 0x00003A) return;
        x = 0xFF;
        myMapper->writeCPU(0x0031, x);
        opINX(1);
        myMapper->writeCPU(0x00EE, x);
        myMapper->writeCPU(0x2000, x);
        myMapper->writeCPU(0x00EF, x);
        myMapper->writeCPU(0x0032, x);
        myMapper->writeCPU(0x0037, x);
        myMapper->writeCPU(0x00F4, x);
        pushAddress(0x00004F);
        SUB_004337();
        if (poppedEntry.value != 0x00004F) return;
        pushAddress(0x000052);
        SUB_0008FB();
        if (poppedEntry.value != 0x000052) return;
        myMapper->writeCPU(0x002E, myMapper->readCPU(0x0033));
        a = 0x00;
        myMapper->writeCPU(0x0033, a);
        myMapper->writeCPU(0x002D, a);
        pushAddress(0x00005F);
        SUB_00007A();
        if (poppedEntry.value != 0x00005F) return;
        myMapper->writeCPU(0x0033, myMapper->readCPU(0x002E));
    }
    SUB_000069();
    return;
}

void game::SUB_000069() {
    pushAddress(0x000069);
    SUB_003E8D();
    if (poppedEntry.value != 0x000069) return;
    myMapper->writeCPU(0x0031, 0x00);
    pushAddress(0x000070);
    SUB_00102F();
    if (poppedEntry.value != 0x000070) return;
    if (myMapper->readCPU(0x0033) & 0x80) {
        SUB_00007A();
        return;
    }
    pushAddress(0x000077);
    SUB_0048EF();
    if (poppedEntry.value != 0x000077) return;
    SUB_00007A();
    return;
}

void game::SUB_00007A() {
    myMapper->writeCPU(0x00EE, 0x10);
    pushAddress(0x00007E);
    SUB_0008C8();
    if (poppedEntry.value != 0x00007E) return;
    myMapper->writeCPU(0x002C, 0x00);
    if (!(myMapper->readCPU(0x0033) & 0x80)) {
        SUB_00008D();
        return;
    }
    myMapper->writeCPU(0x002D, 0x00);
    SUB_00008D();
    return;
}

void game::SUB_00008D() {
    pushAddress(0x00008D);
    SUB_003E8D();
    if (poppedEntry.value != 0x00008D) return;
    pushAddress(0x000090);
    SUB_0003AD();
    if (poppedEntry.value != 0x000090) return;
    pushAddress(0x000093);
    SUB_00198B();
    if (poppedEntry.value != 0x000093) return;
    pushAddress(0x000096);
    SUB_000F00();
    if (poppedEntry.value != 0x000096) return;
    pushAddress(0x000099);
    SUB_0010FD();
    if (poppedEntry.value != 0x000099) return;
    a = myMapper->readCPU(0x002C);
    y = myMapper->readCPU(0x0033);
    setLoadFlag(y);
    if (flgN) {
        goto L_0000A4;
    }
    a = myMapper->readCPU(0x002D);
L_0000A4:
    opROR_A(2);
    opEOR(0x80);
    opAND(0x80);
    myMapper->writeCPU(0x00FC, a);
    SUB_0000AC();
    return;
}

void game::SUB_0000AC() {
L_0000AC:
    a = myMapper->readCPU(0x00FC);
    opEOR(0x80);
    myMapper->writeCPU(0x00FC, a);
    pushAddress(0x0000B2);
    SUB_0010FD();
    if (poppedEntry.value != 0x0000B2) return;
    pushAddress(0x0000B5);
    SUB_000420();
    if (poppedEntry.value != 0x0000B5) return;
    x = 0xFF;
    myMapper->writeCPU(0x0079, x);
    myMapper->writeCPU(0x0067, x);
    myMapper->writeCPU(0x00F7, x);
    myMapper->writeCPU(0x0398, x);
    opINX(1);
    myMapper->writeCPU(0x0068, x);
    myMapper->writeCPU(0x0064, x);
    myMapper->writeCPU(0x0065, x);
    myMapper->writeCPU(0x0069, x);
    myMapper->writeCPU(0x006F, x);
    myMapper->writeCPU(0x0070, x);
    myMapper->writeCPU(0x0082, x);
    myMapper->writeCPU(0x0022, x);
    myMapper->writeCPU(0x0035, x);
    pushAddress(0x0000D6);
    SUB_00108D();
    if (poppedEntry.value != 0x0000D6) return;
    pushAddress(0x0000D9);
    SUB_000EF1();
    if (poppedEntry.value != 0x0000D9) return;
    myMapper->writeCPU(0x004D, 0x6C);
    myMapper->writeCPU(0x004E, 0x04);
    myMapper->writeCPU(0x0010, 0x54);
    myMapper->writeCPU(0x004F, 0x02);
    myMapper->writeCPU(0x0011, 0x01);
    pushAddress(0x0000F0);
    SUB_001DD7();
    if (poppedEntry.value != 0x0000F0) return;
    myMapper->writeCPU(0x0049, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x004A, myMapper->readCPU(0x0013));
    pushAddress(0x0000FB);
    SUB_001633();
    if (poppedEntry.value != 0x0000FB) return;
    myMapper->writeCPU(0x074D, 0x76);
    pushAddress(0x000103);
    SUB_0002DD();
    if (poppedEntry.value != 0x000103) return;
    pushAddress(0x000106);
    SUB_0005D6();
    if (poppedEntry.value != 0x000106) return;
    myMapper->writeCPU(0x0066, 0x00);
    pushAddress(0x00010D);
    SUB_000B14();
    if (poppedEntry.value != 0x00010D) return;
    myMapper->writeCPU(0x00F4, 0x0A);
    pushAddress(0x000114);
    SUB_00409A();
    if (poppedEntry.value != 0x000114) return;
    pushAddress(0x000117);
    SUB_0009AD();
    if (poppedEntry.value != 0x000117) return;
    do {
        wait();
        if (threadSignal == 0x003A) {
            threadSignal = 0;
            SUB_00003A();
            return;
        }
        opCMP(myMapper->readCPU(0x00D3), 0xFF);
    } while (!flgZ);
    pushAddress(0x000120);
    SUB_0009B7();
    if (poppedEntry.value != 0x000120) return;
    x = 0x00;
    myMapper->writeCPU(0x005F, x);
    opINX(1);
    myMapper->writeCPU(0x00F4, x);
    pushAddress(0x00012A);
    SUB_0009AD();
    if (poppedEntry.value != 0x00012A) return;
    do {
		wait();
		if (threadSignal == 0x003A) {
			threadSignal = 0;
			SUB_00003A();
			return;
		}
        pushAddress(0x00012D);
        SUB_000F4A();
        if (poppedEntry.value != 0x00012D) return;
        pushAddress(0x000130);
        SUB_002318();
        if (poppedEntry.value != 0x000130) return;
        pushAddress(0x000133);
        SUB_004558();
        if (poppedEntry.value != 0x000133) return;
    } while (myMapper->readCPU(0x005F) == 0);
    pushAddress(0x00013A);
    SUB_0009B7();
    if (poppedEntry.value != 0x00013A) return;
    pushAddress(0x00013D);
    SUB_000DE2();
    if (poppedEntry.value != 0x00013D) return;
    a = myMapper->readCPU(0x005F);
    opAND(0x20);
    if (!flgZ) {
    }
    else {
        pushAddress(0x000149);
        SUB_001179();
        if (poppedEntry.value != 0x000149) return;
        if (flgC) {
        }
        else {
            pushAddress(0x000151);
            SUB_0002AA();
            if (poppedEntry.value != 0x000151) return;
            pushAddress(0x000154);
            SUB_000B14();
            if (poppedEntry.value != 0x000154) return;
            goto L_00015D;
            while (true) {
                pushAddress(0x00015A);
                SUB_0002AA();
                if (poppedEntry.value != 0x00015A) return;
            L_00015D:
                pushAddress(0x00015D);
                SUB_000EF1();
                if (poppedEntry.value != 0x00015D) return;
                pushAddress(0x000160);
                SUB_000420();
                if (poppedEntry.value != 0x000160) return;
                x = 0xFF;
                myMapper->writeCPU(0x0068, x);
                myMapper->writeCPU(0x006C, x);
                myMapper->writeCPU(0x0021, x);
                myMapper->writeCPU(0x0079, x);
                myMapper->writeCPU(0x00F7, x);
                myMapper->writeCPU(0x0398, x);
                opINX(1);
                myMapper->writeCPU(0x0069, x);
                myMapper->writeCPU(0x0082, x);
                if (myMapper->readCPU(0x0035) & 0x80) {
                    pushAddress(0x00017B);
                    SUB_000BB8();
                    if (poppedEntry.value != 0x00017B) return;
                    pushAddress(0x00017E);
                    SUB_000B14();
                    if (poppedEntry.value != 0x00017E) return;
                }
                myMapper->writeCPU(0x0035, 0x00);
                pushAddress(0x000185);
                SUB_0010FD();
                if (poppedEntry.value != 0x000185) return;
                a = myMapper->readCPU(0x005F);
                opAND(0x08);
                if (flgZ) {
                    goto L_000194;
                }
                pushAddress(0x00018E);
                SUB_000B8E();
                if (poppedEntry.value != 0x00018E) return;
                goto L_0001A2;
            L_000194:
                if (myMapper->readCPU(0x0062) < 0x04) {
                    goto L_0001A5;
                }
                pushAddress(0x00019A);
                SUB_000D28();
                if (poppedEntry.value != 0x00019A) return;
                if (!flgC) {
                    goto L_0001A5;
                }
                pushAddress(0x00019F);
                SUB_000B73();
                if (poppedEntry.value != 0x00019F) return;
            L_0001A2:
                pushAddress(0x0001A2);
                SUB_000B14();
                if (poppedEntry.value != 0x0001A2) return;
            L_0001A5:
                pushAddress(0x0001A5);
                SUB_000B5B();
                if (poppedEntry.value != 0x0001A5) return;
                pushAddress(0x0001A8);
                SUB_00168F();
                if (poppedEntry.value != 0x0001A8) return;
                pushAddress(0x0001AB);
                SUB_000C47();
                if (poppedEntry.value != 0x0001AB) return;
                pushAddress(0x0001AE);
                SUB_0010FD();
                if (poppedEntry.value != 0x0001AE) return;
                myMapper->writeCPU(0x00F4, 0x06);
                a = 0x00;
                myMapper->writeCPU(0x005F, a);
                myMapper->writeCPU(0x0067, a);
                pushAddress(0x0001BB);
                SUB_0009AD();
                if (poppedEntry.value != 0x0001BB) return;
            L_0001BE:
                if (myMapper->readCPU(0x005F) == 0) {
                    wait();
                    if (threadSignal == 0x003A) {
                        threadSignal = 0;
                        SUB_00003A();
                        return;
                    }
                    goto L_0001BE;
                }
                pushAddress(0x0001C2);
                SUB_0009B7();
                if (poppedEntry.value != 0x0001C2) return;
                pushAddress(0x0001C5);
                SUB_000999();
                if (poppedEntry.value != 0x0001C5) return;
                pushAddress(0x0001C8);
                SUB_002038();
                if (poppedEntry.value != 0x0001C8) return;
                pushAddress(0x0001CB);
                SUB_0010FD();
                if (poppedEntry.value != 0x0001CB) return;
                pushAddress(0x0001CE);
                SUB_002FAD();
                if (poppedEntry.value != 0x0001CE) return;
                myMapper->writeCPU(0x0022, 0x80);
                a = 0x00;
                myMapper->writeCPU(0x00F4, a);
                myMapper->writeCPU(0x005F, a);
                pushAddress(0x0001DB);
                SUB_00303F();
                if (poppedEntry.value != 0x0001DB) return;
                pushAddress(0x0001DE);
                SUB_004088();
                if (poppedEntry.value != 0x0001DE) return;
                pushAddress(0x0001E1);
                SUB_0009AD();
                if (poppedEntry.value != 0x0001E1) return;
                do {
                    wait();
                    if (threadSignal == 0x003A) {
                        threadSignal = 0;
                        SUB_00003A();
                        return;
                    }
                    pushAddress(0x0001E4);
                    SUB_002318();
                    if (poppedEntry.value != 0x0001E4) return;
                    pushAddress(0x0001E7);
                    SUB_004558();
                    if (poppedEntry.value != 0x0001E7) return;
                } while (myMapper->readCPU(0x00D3) != 0xFF);
                a = myMapper->readCPU(0x0318);
                opAND(0x0F);
                myMapper->writeCPU(0x0318, a);
                myMapper->writeCPU(0x0022, 0xFF);
                do {
                    wait();
                    if (threadSignal == 0x003A) {
                        threadSignal = 0;
                        SUB_00003A();
                        return;
                    }
                    pushAddress(0x0001FC);
                    SUB_000F4A();
                    if (poppedEntry.value != 0x0001FC) return;
                    pushAddress(0x0001FF);
                    SUB_002318();
                    if (poppedEntry.value != 0x0001FF) return;
                    pushAddress(0x000202);
                    SUB_004558();
                    if (poppedEntry.value != 0x000202) return;
                    a = myMapper->readCPU(0x005F);
                    opAND(0xE8);
                } while (flgZ);
                pushAddress(0x00020B);
                SUB_0009B7();
                if (poppedEntry.value != 0x00020B) return;
                pushAddress(0x00020E);
                SUB_000DE2();
                if (poppedEntry.value != 0x00020E) return;
                a = myMapper->readCPU(0x005F);
                opAND(0x20);
                if (!flgZ) {
                    goto L_000233;
                }
                opINC(0x0062, 1);
            L_000219:
                a = 0x00;
                myMapper->writeCPU(0x00EF, a);
                myMapper->writeCPU(0x2001, a);
                pushAddress(0x000220);
                SUB_001179();
                if (poppedEntry.value != 0x000220) return;
                if (flgC) {
                    goto L_000228;
                }
            }
        }
    L_000228:
        if (myMapper->readCPU(0x0031) & 0x80) {
            popAddress();
            return;
        }
        pushAddress(0x00022D);
        SUB_000399();
        if (poppedEntry.value != 0x00022D) return;
        SUB_00003A();
        return;
    }
L_000233:
    a = 0x80;
    myMapper->writeCPU(0x0070, a);
    myMapper->writeCPU(0x0035, a);
    a = 0x00;
    myMapper->writeCPU(0x0395, a);
    myMapper->writeCPU(0x0396, a);
    myMapper->writeCPU(0x0068, 0xFF);
    pushAddress(0x000245);
    SUB_000EF1();
    if (poppedEntry.value != 0x000245) return;
    pushAddress(0x000248);
    SUB_00168F();
    if (poppedEntry.value != 0x000248) return;
    myMapper->writeCPU(0x0750, 0xF0);
    a = 0x00;
    myMapper->writeCPU(0x005F, a);
    myMapper->writeCPU(0x0067, a);
    myMapper->writeCPU(0x006F, a);
    myMapper->writeCPU(0x00F4, a);
    myMapper->writeCPU(0x0082, a);
    pushAddress(0x00025C);
    SUB_000999();
    if (poppedEntry.value != 0x00025C) return;
    pushAddress(0x00025F);
    SUB_002038();
    if (poppedEntry.value != 0x00025F) return;
    pushAddress(0x000262);
    SUB_002FAD();
    if (poppedEntry.value != 0x000262) return;
    pushAddress(0x000265);
    SUB_0010FD();
    if (poppedEntry.value != 0x000265) return;
    pushAddress(0x000268);
    SUB_00303F();
    if (poppedEntry.value != 0x000268) return;
    pushAddress(0x00026B);
    SUB_004088();
    if (poppedEntry.value != 0x00026B) return;
    myMapper->writeCPU(0x0022, 0xFF);
    pushAddress(0x000272);
    SUB_0009AD();
    if (poppedEntry.value != 0x000272) return;
    do {
        wait();
        pushAddress(0x000275);
        SUB_002318();
        if (poppedEntry.value != 0x000275) return;
        pushAddress(0x000278);
        SUB_004558();
        if (poppedEntry.value != 0x000278) return;
    } while (myMapper->readCPU(0x00D3) != 0xFF);
    a = myMapper->readCPU(0x0318);
    opAND(0x0F);
    myMapper->writeCPU(0x0318, a);
    do {
        wait();
        pushAddress(0x000289);
        SUB_000F4A();
        if (poppedEntry.value != 0x000289) return;
        pushAddress(0x00028C);
        SUB_002318();
        if (poppedEntry.value != 0x00028C) return;
        pushAddress(0x00028F);
        SUB_004558();
        if (poppedEntry.value != 0x00028F) return;
        a = myMapper->readCPU(0x005F);
        opAND(0xE8);
    } while (flgZ);
    pushAddress(0x000298);
    SUB_0009B7();
    if (poppedEntry.value != 0x000298) return;
    pushAddress(0x00029B);
    SUB_000DE2();
    if (poppedEntry.value != 0x00029B) return;
    a = myMapper->readCPU(0x0023);
    opORA(myMapper->readCPU(0x0024));
    if (!flgZ) {
        goto L_0002A7;
    }
    goto L_000219;
L_0002A7:
    goto L_0000AC;
}

void game::SUB_0002AA() {
    a = myMapper->readCPU(0x004E);
    flgC = false;
    opADC(0x18);
    myMapper->writeCPU(0x0060, a);
    a = myMapper->readCPU(0x004F);
    opADC(0x00);
    myMapper->writeCPU(0x0061, a);
    popAddress();
}

void game::SUB_0002B8() {
    myMapper->writeCPU(0x0012, 0x79);
    myMapper->writeCPU(0x0013, 0x83);
    a = myMapper->readCPU(0x002C);
    opLSR_A(1);
    if (!flgC) {
        goto L_0002D2;
    }
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(0x0B);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0013);
    opADC(0x00);
    myMapper->writeCPU(0x0013, a);
L_0002D2:
    myMapper->writeCPU(0x0010, 0x48);
    myMapper->writeCPU(0x0011, 0x2B);
    SUB_001152();
    return;
}

void game::SUB_0002DD() {
    if (myMapper->readCPU(0x0033) & 0x80) {
        SUB_0002B8();
        return;
    }
    a = myMapper->readCPU(0x002D);
    if (a >= 0x08) {
        a = 0x08;
    }
    opAND(0xFE);
    opASL_A(3);
    flgC = false;
    opADC(0x29);
    myMapper->writeCPU(0x0012, a);
    a = 0x00;
    opADC(0x83);
    myMapper->writeCPU(0x0013, a);
    myMapper->writeCPU(0x0010, 0x08);
    myMapper->writeCPU(0x0011, 0x2B);
    pushAddress(0x000301);
    SUB_001152();
    if (poppedEntry.value != 0x000301) return;
    myMapper->writeCPU(0x0012, 0x79);
    myMapper->writeCPU(0x0013, 0x83);
    a = myMapper->readCPU(0x002D);
    opLSR_A(1);
    if (!flgC) {
        goto L_00031E;
    }
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(0x0B);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0013);
    opADC(0x00);
    myMapper->writeCPU(0x0013, a);
L_00031E:
    myMapper->writeCPU(0x0010, 0x48);
    myMapper->writeCPU(0x0011, 0x2B);
    SUB_001152();
    return;
}

void game::SUB_000390() {
    a = 0x00;
    myMapper->writeCPU(0x00EF, a);
    myMapper->writeCPU(0x0049, a);
    myMapper->writeCPU(0x004A, a);
    popAddress();
}

void game::SUB_000399() {
    pushAddress(0x000399);
    SUB_000390();
    if (poppedEntry.value != 0x000399) return;
    pushAddress(0x00039C);
    SUB_0010FD();
    if (poppedEntry.value != 0x00039C) return;
    pushAddress(0x00039F);
    SUB_000EC4();
    if (poppedEntry.value != 0x00039F) return;
    pushAddress(0x0003A2);
    SUB_000EF1();
    if (poppedEntry.value != 0x0003A2) return;
    a = 0x0F;
    pushAddress(0x0003A7);
    SUB_001465();
    if (poppedEntry.value != 0x0003A7) return;
    SUB_001372();
    return;
}

void game::SUB_0003AD() {
    a = myMapper->readCPU(0x002D);
    if (a >= 0x0A) {
        a = 0x09;
    }
    opPHA();
    opASL_A(1);
    y = a;
    opBIT(myMapper->readCPU(0x0031));
    if (flgN) {
        y = 0x14;
        setLoadFlag(y);
        if (!flgZ) {
            goto L_0003C6;
        }
    }
    opBIT(myMapper->readCPU(0x0033));
    if (!flgN) {
        goto L_0003C6;
    }
    y = 0x0C;
L_0003C6:
    myMapper->writeCPU(0x0023, myMapper->readCPU(0x83F6 + y));
    a = myMapper->readCPU(0x83F7 + y);
    myMapper->writeCPU(0x0024, a);
    opPLA();
    opPHA();
    opAND(0x0E);
    y = a;
    myMapper->writeCPU(0x00BD, myMapper->readCPU(0x83EC + y));
    a = myMapper->readCPU(0x83ED + y);
    myMapper->writeCPU(0x00BE, a);
    opPLA();
    y = a;
    myMapper->writeCPU(0x00F5, myMapper->readCPU(0x840C + y));
    myMapper->writeCPU(0x00F6, myMapper->readCPU(0x8414 + y));
    popAddress();
}

void game::SUB_000420() {
    y = 0x00;
    a = 0x00;
    do {
        myMapper->writeCPU(0x0600 + y, a);
        opINY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00042B() {
    a = 0x00;
    myMapper->writeCPU(0x00F3, a);
    myMapper->writeCPU(0x00F2, a);
    a = myMapper->readCPU(0x00EE);
    opAND(0xFD);
    myMapper->writeCPU(0x00EE, a);
    if (myMapper->readCPU(0x00F4) == 0) {
        goto L_000441;
    }
    pushAddress(0x00043B);
    SUB_004B37();
    if (poppedEntry.value != 0x00043B) return;
    goto L_000444;
L_000441:
    pushAddress(0x000441);
    SUB_000953();
    if (poppedEntry.value != 0x000441) return;
L_000444:
    pushAddress(0x000444);
    SUB_0010FD();
    if (poppedEntry.value != 0x000444) return;
    SUB_0004F6();
    return;
}

void game::SUB_00044A() {
    pushAddress(0x00044A);
    SUB_002ECE();
    if (poppedEntry.value != 0x00044A) return;
    SUB_000453();
    return;
}

void game::SUB_000450() {
    pushAddress(0x000450);
    SUB_00147B();
    if (poppedEntry.value != 0x000450) return;
    SUB_000453();
    return;
}

void game::SUB_000453() {
    pushAddress(0x000453);
    SUB_001586();
    if (poppedEntry.value != 0x000453) return;
    SUB_000456();
    return;
}

void game::SUB_000456() {
    a = myMapper->readCPU(0x00F4);
    opCMP(a, 0x05);
    if (!flgZ) {
        opCMP(a, 0x06);
        if (flgZ) {
            goto L_00046E;
        }
        x = 0xF8;
        a = 0x11;
        do {
            opPHA();
            pushAddress(0x000465);
            SUB_0005B0();
            if (poppedEntry.value != 0x000465) return;
            opPLA();
            flgC = true;
            opSBC(0x01);
        } while (!flgN);
    }
L_00046E:
    SUB_0004F3();
    return;
}

void game::nmi() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    myMapper->writeCPU(0x2003, 0x00);
    myMapper->writeCPU(0x4014, 0x07);
    //NOP
    //NOP
    //NOP
    a = myMapper->readCPU(0x0037);
    setLoadFlag(a);
    if (flgN) {
        SUB_0004FA();
        return;
    }
    pushAddress(0x00048A);
    SUB_0014DF();
    if (poppedEntry.value != 0x00048A) return;
    opINC(0x001F, 1);
    if (flgZ) {
        opINC(0x0020, 1);
    }
    pushAddress(0x000493);
    SUB_000E36();
    if (poppedEntry.value != 0x000493) return;
    pushAddress(0x000496);
    SUB_0045F3();
    if (poppedEntry.value != 0x000496) return;
    pushAddress(0x000499);
    SUB_003EA3();
    if (poppedEntry.value != 0x000499) return;
    opDEC(0x0037, 1);
    opBIT(myMapper->readCPU(0x0034));
    if (flgN) {
        SUB_00042B();
        return;
    }
    if (flgV) {
        SUB_000456();
        return;
    }
    opINC(0x0021, 1);
    opINC(0x001D, 1);
    if (!flgZ) {
        goto L_0004B2;
    }
    opINC(0x001E, 1);
L_0004B2:
    a = 0x00;
    myMapper->writeCPU(0x039A, a);
    myMapper->writeCPU(0x039B, a);
    pushAddress(0x0004BA);
    SUB_0010FD();
    if (poppedEntry.value != 0x0004BA) return;
    pushAddress(0x0004BD);
    SUB_00088D();
    if (poppedEntry.value != 0x0004BD) return;
    a = myMapper->readCPU(0x00F4);
    opAND(0x1F);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x8569 + x));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x856A + x));
    indirectJump(myMapper->readCPU(0x0010) + (myMapper->readCPU((0x0010 + 1) & 0x00ff) << 8));
}

void game::SUB_0004D3() {
    pushAddress(0x0004D3);
    SUB_00362C();
    if (poppedEntry.value != 0x0004D3) return;
    SUB_0004D6();
    return;
}

void game::SUB_0004D6() {
    x = 0xF8;
    do {
        pushAddress(0x0004D8);
        SUB_001E77();
        if (poppedEntry.value != 0x0004D8) return;
    } while (x < 0x88);
    SUB_0004DF();
    return;
}

void game::SUB_0004DF() {
    pushAddress(0x0004DF);
    SUB_00147B();
    if (poppedEntry.value != 0x0004DF) return;
    pushAddress(0x0004E2);
    SUB_001586();
    if (poppedEntry.value != 0x0004E2) return;
    pushAddress(0x0004E5);
    SUB_0038A3();
    if (poppedEntry.value != 0x0004E5) return;
    pushAddress(0x0004E8);
    SUB_00057F();
    if (poppedEntry.value != 0x0004E8) return;
    if (myMapper->readCPU(0x0398) & 0x80) {
        SUB_0004F3();
        return;
    }
    opDEC(0x0398, 1);
    SUB_0004F3();
    return;
}

void game::SUB_0004F3() {
    pushAddress(0x0004F3);
    SUB_000500();
    if (poppedEntry.value != 0x0004F3) return;
    SUB_0004F6();
    return;
}

void game::SUB_0004F6() {
    a = 0x00;
    myMapper->writeCPU(0x0037, a);
    SUB_0004FA();
    return;
}

void game::SUB_0004FA() {
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    SUB_0004FF();
    return;
}

void game::SUB_0004FF() {
    return;
}

void game::SUB_000500() {
    a = myMapper->readCPU(0x00EB);
    opAND(0x08);
    if (!flgZ) {
        opEOR(myMapper->readCPU(0x00ED));
        opAND(0x08);
        if (!flgZ) {
            a = myMapper->readCPU(0x0031);
            setLoadFlag(a);
            if (flgN) {
                myMapper->writeCPU(0x00EF, 0x00);
                x = 0xFF;
                s = x;
                myMapper->writeCPU(0x0033, myMapper->readCPU(0x002E));
                threadSignal = 0x003A;
                return;
            }
            opBIT(myMapper->readCPU(0x0036));
            if (flgV) {
                goto L_000531;
            }
            a = 0x40;
            myMapper->writeCPU(0x0036, a);
            myMapper->writeCPU(0x0034, a);
            pushAddress(0x000528);
            SUB_000549();
            if (poppedEntry.value != 0x000528) return;
            pushAddress(0x00052B);
            SUB_003E8D();
            if (poppedEntry.value != 0x00052B) return;
            SUB_004133();
            return;
        L_000531:
            a = 0x00;
            myMapper->writeCPU(0x0036, a);
            myMapper->writeCPU(0x0034, a);
            pushAddress(0x000537);
            SUB_00053B();
            if (poppedEntry.value != 0x000537) return;
        }
    }
    popAddress();
}

void game::SUB_00053B() {
    x = 0x10;
    do {
        myMapper->writeCPU(0x0760 + x, 0xF0);
        opDEX(4);
    } while (!flgN);
    popAddress();
}

void game::SUB_000549() {
    x = 0x13;
    do {
        myMapper->writeCPU(0x0760 + x, myMapper->readCPU(0x8555 + x));
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_00057F() {
    if (myMapper->readCPU(0x0082) == 0) {
        goto L_00058A;
    }
    opDEC(0x0082, 1);
    if (!flgZ) {
        goto L_00058A;
    }
    pushAddress(0x000587);
    SUB_0029C8();
    if (poppedEntry.value != 0x000587) return;
L_00058A:
    a = myMapper->readCPU(0x0024);
    setLoadFlag(a);
    if (!flgN) {
        goto L_000595;
    }
    do {
        a = 0x00;
        myMapper->writeCPU(0x0023, a);
        myMapper->writeCPU(0x0024, a);
        popAddress();
        return;
    L_000595:
        opORA(myMapper->readCPU(0x0023));
        if (flgZ) {
            goto L_0005AF;
        }
        if (!(myMapper->readCPU(0x0022) & 0x80)) {
            goto L_0005AF;
        }
        a = myMapper->readCPU(0x001D);
        opAND(0x0F);
        if (!flgZ) {
            goto L_0005AF;
        }
        opDEC(0x0023, 1);
        if (!flgN) {
            goto L_0005AF;
        }
        myMapper->writeCPU(0x0023, 0x3B);
        opDEC(0x0024, 1);
    } while (flgN);
L_0005AF:
    popAddress();
}

void game::SUB_0005B0() {
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    myMapper->writeCPU(0x0058, x);
    a = 0x01;
    if (x >= 0x48) {
        a = 0x21;
    }
    myMapper->writeCPU(0x0013, a);
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x1F);
    if (a != 0x01) {
        goto L_0005CE;
    }
    myMapper->writeCPU(0x0013, 0x31);
L_0005CE:
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0307 + x));
    SUB_001ECF();
    return;
}

void game::SUB_0005D6() {
    a = 0x00;
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, a);
    if (myMapper->readCPU(0x00FC) & 0x80) {
        a = 0x00;
        setLoadFlag(a);
        if (flgZ) {
            goto L_0005EC;
        }
    }
    a = myMapper->readCPU(0x002D);
    if (a >= 0x05) {
        a = 0x05;
    }
L_0005EC:
    opAND(0x07);
    y = a;
    while (true) {
        opDEY(1);
        if (flgN) {
            goto L_000602;
        }
        a = myMapper->readCPU(0x0010);
        flgC = false;
        opADC(0x28);
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x0011);
        opADC(0x00);
        myMapper->writeCPU(0x0011, a);
    }
L_000602:
    x = 0x00;
    do {
        myMapper->writeCPU(0x0300 + x, 0x00);
        opINX(1);
    } while (x < 0x90);
    x = 0x00;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0300 + x, myMapper->readCPU(0x8691 + y));
        myMapper->writeCPU(0x0301 + x, 0x25);
        myMapper->writeCPU(0x0304 + x, myMapper->readCPU(0x8692 + y));
        myMapper->writeCPU(0x0305 + x, myMapper->readCPU(0x8693 + y));
        myMapper->writeCPU(0x0306 + x, myMapper->readCPU(0x8694 + y));
        if (x >= 0x48) {
            goto L_000644;
        }
        a = myMapper->readCPU(0x0305 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0305 + x, a);
        a = myMapper->readCPU(0x0306 + x);
        opADC(myMapper->readCPU(0x0011));
        myMapper->writeCPU(0x0306 + x, a);
    L_000644:
        opINY(4);
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
    } while (a < 0x90);
    myMapper->writeCPU(0x004D, 0x6C);
    myMapper->writeCPU(0x004E, 0x04);
    myMapper->writeCPU(0x004F, 0x02);
    x = 0x0B;
    do {
        myMapper->writeCPU(0x07C4 + x, myMapper->readCPU(0x86D9 + x));
        opDEX(1);
    } while (x >= 0x08);
    do {
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x86D9 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0050, 0xB0);
    a = myMapper->readCPU(0x0305);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x006A, a);
    a = myMapper->readCPU(0x0306);
    opSBC(0x00);
    myMapper->writeCPU(0x006B, a);
    a = myMapper->readCPU(0x000F);
    opAND(0x40);
    if (!flgZ) {
        goto L_00068E;
    }
    a = 0x80;
L_00068E:
    myMapper->writeCPU(0x00FB, a);
    popAddress();
}

void game::SUB_0006E5() {
    a = myMapper->readCPU(0x001D);
    opAND(0x03);
    if (flgZ) {
        opINC(0x034D, 1);
        if (flgZ) {
            opINC(0x034E, 1);
        }
    }
    a = myMapper->readCPU(0x034D);
    flgC = true;
    opSBC(0xFE);
    a = myMapper->readCPU(0x034E);
    opSBC(0x01);
    if (!flgC) {
        goto L_00070B;
    }
    opINC(0x00F4, 1);
    myMapper->writeCPU(0x034A, 0x18);
    myMapper->writeCPU(0x004C, 0x0C);
L_00070B:
    x = 0xF8;
    do {
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        myMapper->writeCPU(0x0058, x);
        myMapper->writeCPU(0x0012, 0x01);
        myMapper->writeCPU(0x0013, 0x01);
        if (myMapper->readCPU(0x0300 + x) == 0x06) {
            myMapper->writeCPU(0x0012, 0x0C);
            myMapper->writeCPU(0x0013, 0x21);
            if (x != 0x48) {
                goto L_000733;
            }
            myMapper->writeCPU(0x0012, 0x88);
        }
    L_000733:
        pushAddress(0x000733);
        SUB_001ECF();
        if (poppedEntry.value != 0x000733) return;
    } while (x < 0x88);
    SUB_0004DF();
    return;
}

void game::SUB_00073D() {
    x = 0x48;
    myMapper->writeCPU(0x0058, x);
    opDEC(0x0302 + x, 1);
    if (flgN) {
        opINC(0x00F4, 1);
        pushAddress(0x000748);
        SUB_004161();
        if (poppedEntry.value != 0x000748) return;
    }
    a = myMapper->readCPU(0x0302 + x);
    if (a < 0x10) {
        opCMP(a, 0x0F);
        if (flgZ) {
            if (myMapper->readCPU(0x0033) & 0x80) {
                goto L_00075E;
            }
            if (!(myMapper->readCPU(0x00FC) & 0x80)) {
                goto L_000767;
            }
        L_00075E:
            myMapper->writeCPU(0x0348, 0x0D);
            myMapper->writeCPU(0x0079, 0x48);
        L_000767:
            pushAddress(0x000767);
            SUB_004106();
            if (poppedEntry.value != 0x000767) return;
            myMapper->writeCPU(0x0022, 0x80);
        }
        pushAddress(0x00076E);
        SUB_0036D7();
        if (poppedEntry.value != 0x00076E) return;
        opDEC(0x07CC, 1);
        a = 0x69;
        setLoadFlag(a);
        myMapper->writeCPU(0x0012, a);
        if (!flgZ) {
            goto L_00077E;
        }
    }
    myMapper->writeCPU(0x0012, 0x68);
L_00077E:
    myMapper->writeCPU(0x0013, 0x21);
    pushAddress(0x000782);
    SUB_001ECF();
    if (poppedEntry.value != 0x000782) return;
    do {
        a = x;
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0058, a);
        myMapper->writeCPU(0x0012, 0x88);
        myMapper->writeCPU(0x0013, 0x21);
        pushAddress(0x000794);
        SUB_001ECF();
        if (poppedEntry.value != 0x000794) return;
    } while (x < 0x88);
    SUB_0004DF();
    return;
}

void game::SUB_00079E() {
    pushAddress(0x00079E);
    SUB_000839();
    if (poppedEntry.value != 0x00079E) return;
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(myMapper->readCPU(0x006A));
    a = myMapper->readCPU(0x004F);
    opSBC(myMapper->readCPU(0x006B));
    if (flgC) {
        opINC(0x00F4, 1);
        myMapper->writeCPU(0x0700, 0xF0);
    }
    pushAddress(0x0007B3);
    SUB_0036D7();
    if (poppedEntry.value != 0x0007B3) return;
    a = 0x00;
    myMapper->writeCPU(0x039A, a);
    myMapper->writeCPU(0x039B, a);
    a = myMapper->readCPU(0x07CC);
    if (a < 0xF0) {
        goto L_0007C9;
    }
    if (a < 0xF8) {
        goto L_0007CC;
    }
L_0007C9:
    opDEC(0x07CC, 1);
L_0007CC:
    SUB_0004D6();
    return;
}

void game::SUB_0007CF() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(myMapper->readCPU(0x0060));
    a = myMapper->readCPU(0x004F);
    opSBC(myMapper->readCPU(0x0061));
    if (flgC) {
        goto L_0007E0;
    }
    pushAddress(0x0007DA);
    SUB_0036D7();
    if (poppedEntry.value != 0x0007DA) return;
    SUB_0004DF();
    return;
L_0007E0:
    myMapper->writeCPU(0x005F, 0xFF);
    SUB_0004F6();
    return;
}

void game::SUB_0007E7() {
    opDEC(0x0393, 1);
    if (flgN) {
        a = myMapper->readCPU(0x005F);
        opORA(0x10);
        myMapper->writeCPU(0x005F, a);
    }
    x = 0x90;
    myMapper->writeCPU(0x0390, x);
    a = myMapper->readCPU(0x001D);
    opAND(0x01);
    if (flgZ) {
        opINC(0x0391, 1);
        opINC(0x0392, 1);
        if (myMapper->readCPU(0x0394) & 0x80) {
            opDEC(0x0392, 2);
        }
    }
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0391));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0392));
    myMapper->writeCPU(0x0014, 0xC4);
    myMapper->writeCPU(0x0013, 0x91);
    if (!(myMapper->readCPU(0x0394) & 0x80)) {
        goto L_000829;
    }
    a = 0x82;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_00082B;
    }
L_000829:
    a = 0x83;
L_00082B:
    myMapper->writeCPU(0x0012, a);
    pushAddress(0x00082D);
    SUB_001F02();
    if (poppedEntry.value != 0x00082D) return;
    pushAddress(0x000830);
    SUB_001586();
    if (poppedEntry.value != 0x000830) return;
    pushAddress(0x000833);
    SUB_00057F();
    if (poppedEntry.value != 0x000833) return;
    SUB_000456();
    return;
}

void game::SUB_000839() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x02);
    if (!flgZ) {
        goto L_000866;
    }
    a = myMapper->readCPU(0x0010);
    if (a >= 0x30) {
        goto L_000866;
    }
    if (a >= 0x10) {
        goto L_000856;
    }
    do {
        myMapper->writeCPU(0x0701, 0xBE);
        popAddress();
        return;
    L_000856:
        myMapper->writeCPU(0x0700, 0xAC);
        myMapper->writeCPU(0x0701, 0xBF);
        myMapper->writeCPU(0x0704, 0xF0);
        popAddress();
        return;
    L_000866:
        a = myMapper->readCPU(0x006A);
        flgC = true;
        opSBC(myMapper->readCPU(0x004E));
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x006B);
        opSBC(myMapper->readCPU(0x004F));
        if (!flgZ) {
            goto L_00087D;
        }
        a = myMapper->readCPU(0x0010);
    } while (a < 0x10);
    if (a < 0x20) {
        goto L_000856;
    }
L_00087D:
    myMapper->writeCPU(0x0700, 0xA8);
    myMapper->writeCPU(0x0701, 0xC0);
    myMapper->writeCPU(0x0704, 0xB0);
    popAddress();
}

void game::SUB_00088D() {
    if (myMapper->readCPU(0x006C) & 0x80) {
        goto L_0008A0;
    }
    opDEC(0x006C, 1);
    if (!flgN) {
        goto L_0008A0;
    }
    a = 0xF0;
    myMapper->writeCPU(0x07D0, a);
    myMapper->writeCPU(0x07D4, a);
    myMapper->writeCPU(0x07D8, a);
L_0008A0:
    popAddress();
}

void game::SUB_0008A1() {
    y = a;
    if (!(myMapper->readCPU(0x0031) & 0x80)) {
        if (myMapper->readCPU(0x00FC) & 0x80) {
            goto L_0008B5;
        }
        a = myMapper->readCPU(0x88C1 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0025));
        myMapper->writeCPU(0x0025, a);
        SUB_000FFC();
        return;
    L_0008B5:
        a = myMapper->readCPU(0x88C1 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0027));
        myMapper->writeCPU(0x0027, a);
        SUB_000FFC();
        return;
    }
    popAddress();
}

void game::SUB_0008C8() {
    x = 0x1F;
    do {
        myMapper->writeCPU((0x00A3 + x) & 0x00ff, myMapper->readCPU(0x88D3 + x));
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0008F3() {
    pushAddress(0x0008F3);
    SUB_0009B7();
    if (poppedEntry.value != 0x0008F3) return;
    myMapper->writeCPU(0x0034, 0x00);
    popAddress();
}

void game::SUB_0008FB() {
    myMapper->writeCPU(0x0034, 0x80);
    pushAddress(0x0008FF);
    SUB_0009AD();
    if (poppedEntry.value != 0x0008FF) return;
    while (true) {
        do {
            while (true) {
                do {
                    wait();
                    a = myMapper->readCPU(0x00EB);
                    opAND(0x0C);
                } while (!flgZ);
                myMapper->writeCPU(0x0020, 0x00);
                myMapper->writeCPU(0x001F, 0x40);
            L_000910:
                wait();
                opCMP(myMapper->readCPU(0x0020), 0x02);
                if (flgC) {
                    SUB_0008F3();
                    return;
                }
                a = myMapper->readCPU(0x00EB);
                opPHA();
                opAND(0x08);
                if (!flgZ) {
                    goto L_000946;
                }
                opPLA();
                opAND(0x04);
                if (flgZ) {
                    goto L_00092B;
                }
                a = myMapper->readCPU(0x0033);
                opEOR(0x80);
                myMapper->writeCPU(0x0033, a);
            }
        L_00092B:
            a = myMapper->readCPU(0x00EB);
            opAND(0x30);
            if (flgZ) {
                goto L_000910;
            }
            opAND(0x20);
            if (flgZ) {
                goto L_00093D;
            }
            a = myMapper->readCPU(0x0033);
            opORA(0x80);
            myMapper->writeCPU(0x0033, a);
        } while (!flgZ);
    L_00093D:
        a = myMapper->readCPU(0x0033);
        opAND(0x7F);
        myMapper->writeCPU(0x0033, a);
    }
L_000946:
    opPLA();
    pushAddress(0x000947);
    SUB_0009B7();
    if (poppedEntry.value != 0x000947) return;
    a = 0x00;
    myMapper->writeCPU(0x0034, a);
    opPLA();
    opPLA();
    SUB_000069();
    return;
}

void game::SUB_000953() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    if (!(myMapper->readCPU(0x0033) & 0x80)) {
        goto L_000979;
    }
    a = 0x22;
    y = 0x4A;
    pushAddress(0x000963);
    SUB_001474();
    if (poppedEntry.value != 0x000963) return;
    myMapper->writeCPU(0x2007, 0x30);
    a = 0x22;
    y = 0x8A;
    pushAddress(0x00096F);
    SUB_001474();
    if (poppedEntry.value != 0x00096F) return;
    a = 0xBF;
    setLoadFlag(a);
    myMapper->writeCPU(0x2007, a);
    if (!flgZ) {
        goto L_000991;
    }
L_000979:
    a = 0x22;
    y = 0x4A;
    pushAddress(0x00097D);
    SUB_001474();
    if (poppedEntry.value != 0x00097D) return;
    myMapper->writeCPU(0x2007, 0xBF);
    a = 0x22;
    y = 0x8A;
    pushAddress(0x000989);
    SUB_001474();
    if (poppedEntry.value != 0x000989) return;
    myMapper->writeCPU(0x2007, 0x30);
L_000991:
    myMapper->writeCPU(0x2001, 0x1E);
    SUB_000F37();
    return;
}

void game::SUB_000999() {
    a = myMapper->readCPU(0x004D);
    if (a >= 0x44) {
        if (a >= 0x95) {
            goto L_0009A8;
        }
        popAddress();
        return;
    }
    a = 0x45;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0009AA;
    }
L_0009A8:
    a = 0x94;
L_0009AA:
    myMapper->writeCPU(0x004D, a);
    popAddress();
}

void game::SUB_0009AD() {
    a = myMapper->readCPU(0x00EE);
    opORA(0x80);
    myMapper->writeCPU(0x00EE, a);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_0009B7() {
    a = myMapper->readCPU(0x00EE);
    opAND(0x7F);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x00EE, a);
    popAddress();
}

void game::SUB_0009C1() {
    myMapper->writeCPU(0x0392, 0xC0);
    myMapper->writeCPU(0x0391, 0x10);
    myMapper->writeCPU(0x0393, 0x70);
    myMapper->writeCPU(0x0394, 0xFF);
    a = myMapper->readCPU(0x005F);
    opAND(0x40);
    if (!flgZ) {
        pushAddress(0x0009DB);
        SUB_003E8D();
        if (poppedEntry.value != 0x0009DB) return;
        a = 0x08;
        myMapper->writeCPU(0x0392, a);
        myMapper->writeCPU(0x0394, a);
    }
    myMapper->writeCPU(0x00F4, 0x07);
    pushAddress(0x0009EA);
    SUB_0009AD();
    if (poppedEntry.value != 0x0009EA) return;
    do {
        wait();
        if (threadSignal == 0x003A) {
            threadSignal = 0;
            SUB_00003A();
            return;
        }
        a = myMapper->readCPU(0x005F);
        opAND(0x10);
    } while (flgZ);
    pushAddress(0x0009F3);
    SUB_0009B7();
    if (poppedEntry.value != 0x0009F3) return;
    pushAddress(0x0009F6);
    SUB_000D31();
    if (poppedEntry.value != 0x0009F6) return;
    pushAddress(0x0009F9);
    SUB_0040D5();
    if (poppedEntry.value != 0x0009F9) return;
    a = 0x00;
    pushAddress(0x0009FE);
    SUB_000A95();
    if (poppedEntry.value != 0x0009FE) return;
    y = 0x08;
    a = myMapper->readCPU(0x005F);
    opAND(0x20);
    if (!flgZ) {
        pushAddress(0x000A09);
        SUB_0040C3();
        if (poppedEntry.value != 0x000A09) return;
        pushAddress(0x000A0C);
        SUB_004161();
        if (poppedEntry.value != 0x000A0C) return;
        y = 0x09;
    }
    myMapper->writeCPU(0x00F4, y);
    myMapper->writeCPU(0x00F1, 0x06);
    myMapper->writeCPU(0x0021, 0x80);
    pushAddress(0x000A1B);
    SUB_0009AD();
    if (poppedEntry.value != 0x000A1B) return;
L_000A1E:
    if (myMapper->readCPU(0x0021) != 0) {
        wait();
        if (threadSignal == 0x003A) {
            threadSignal = 0;
            SUB_00003A();
            return;
        }
        goto L_000A1E;
    }
    pushAddress(0x000A22);
    SUB_0009B7();
    if (poppedEntry.value != 0x000A22) return;
    pushAddress(0x000A25);
    SUB_000D28();
    if (poppedEntry.value != 0x000A25) return;
    a = myMapper->readCPU(0x0023);
    opORA(myMapper->readCPU(0x0024));
    if (flgZ) {
        opCMP(myMapper->readCPU(0x00F4), 0x09);
        if (!flgZ) {
            if (myMapper->readCPU(0x0070) & 0x80) {
                goto L_000A3E;
            }
            pushAddress(0x000A38);
            SUB_004126();
            if (poppedEntry.value != 0x000A38) return;
            pushAddress(0x000A3B);
            SUB_000D73();
            if (poppedEntry.value != 0x000A3B) return;
        }
    L_000A3E:
        a = 0x18;
        pushAddress(0x000A40);
        SUB_000A95();
        if (poppedEntry.value != 0x000A40) return;
        myMapper->writeCPU(0x00F4, 0x08);
        myMapper->writeCPU(0x0021, 0x80);
        pushAddress(0x000A4B);
        SUB_0009AD();
        if (poppedEntry.value != 0x000A4B) return;
    L_000A4E:
        if (myMapper->readCPU(0x0021) != 0) {
            wait();
            if (threadSignal == 0x003A) {
                threadSignal = 0;
                SUB_00003A();
                return;
            }
            goto L_000A4E;
        }
        SUB_0009B7();
        return;
    }
    pushAddress(0x000A55);
    SUB_000D28();
    if (poppedEntry.value != 0x000A55) return;
    if (!flgC) {
        if (myMapper->readCPU(0x0070) & 0x80) {
            goto L_000A8C;
        }
        if (myMapper->readCPU(0x0035) & 0x80) {
            goto L_000A8C;
        }
        pushAddress(0x000A62);
        SUB_004076();
        if (poppedEntry.value != 0x000A62) return;
        pushAddress(0x000A65);
        SUB_004161();
        if (poppedEntry.value != 0x000A65) return;
        y = 0xDC;
        myMapper->writeCPU(0x002F, 0x50);
        myMapper->writeCPU(0x0010, 0x0E);
        a = 0x48;
        x = 0x07;
        pushAddress(0x000A76);
        SUB_0012D3();
        if (poppedEntry.value != 0x000A76) return;
        a = 0x30;
        pushAddress(0x000A7B);
        SUB_000A95();
        if (poppedEntry.value != 0x000A7B) return;
        myMapper->writeCPU(0x0021, 0x80);
        pushAddress(0x000A82);
        SUB_0009AD();
        if (poppedEntry.value != 0x000A82) return;
    L_000A85:
        if (myMapper->readCPU(0x0021) != 0) {
            wait();
            goto L_000A85;
        }
        pushAddress(0x000A89);
        SUB_0009B7();
        if (poppedEntry.value != 0x000A89) return;
    }
L_000A8C:
    popAddress();
}

void game::SUB_000A95() {
    if (myMapper->readCPU(0x0394) & 0x80) {
        goto L_000A9D;
    }
    flgC = false;
    opADC(0x0C);
L_000A9D:
    x = a;
    y = 0x00;
    do {
        a = myMapper->readCPU(0x8ACC + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0391));
        myMapper->writeCPU(0x07C4 + y, a);
        myMapper->writeCPU(0x07C5 + y, myMapper->readCPU(0x8ACD + x));
        myMapper->writeCPU(0x07C6 + y, myMapper->readCPU(0x8ACE + x));
        a = myMapper->readCPU(0x8ACF + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0392));
        myMapper->writeCPU(0x07C7 + y, a);
        pushAddress(0x000AC0);
        SUB_002AF3();
        if (poppedEntry.value != 0x000AC0) return;
        opINX(4);
        opCMP(y, 0x0C);
    } while (!flgC);
    popAddress();
}

void game::SUB_000B14() {
    myMapper->writeCPU(0x0062, 0x00);
    myMapper->writeCPU(0x0063, 0x10);
    a = myMapper->readCPU(0x0060);
    flgC = true;
    opSBC(0x68);
    myMapper->writeCPU(0x0064, a);
    a = myMapper->readCPU(0x0061);
    opSBC(0x00);
    myMapper->writeCPU(0x0065, a);
    a = 0x98;
    flgC = true;
    opSBC(myMapper->readCPU(0x0064));
    a = 0x03;
    opSBC(myMapper->readCPU(0x0065));
    if (!flgC) {
        myMapper->writeCPU(0x0064, 0x98);
        myMapper->writeCPU(0x0065, 0x03);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0064);
    flgC = true;
    opSBC(0xB8);
    a = myMapper->readCPU(0x0065);
    opSBC(0x00);
    if (flgC) {
        goto L_000B5A;
    }
    myMapper->writeCPU(0x0064, 0xB8);
    myMapper->writeCPU(0x0065, 0x00);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(myMapper->readCPU(0x0064));
    opLSR_A(3);
    myMapper->writeCPU(0x0063, a);
L_000B5A:
    popAddress();
}

void game::SUB_000B5B() {
    if (myMapper->readCPU(0x0062) == 0) {
        goto L_000B6F;
    }
    pushAddress(0x000B5F);
    SUB_000CA4();
    if (poppedEntry.value != 0x000B5F) return;
    if (!flgC) {
        goto L_000B70;
    }
    myMapper->writeCPU(0x0011, 0x00);
    pushAddress(0x000B68);
    SUB_000F62();
    if (poppedEntry.value != 0x000B68) return;
    myMapper->writeCPU(0x0063, myMapper->readCPU(0x0014));
L_000B6F:
    popAddress();
    return;
L_000B70:
    SUB_000B14();
    return;
}

void game::SUB_000B73() {
    opCMP(myMapper->readCPU(0x0050), 0xA0);
    if (!flgC) {
        SUB_000BA6();
        return;
    }
    myMapper->writeCPU(0x0012, 0x60);
    pushAddress(0x000B7D);
    SUB_000CC2();
    if (poppedEntry.value != 0x000B7D) return;
    myMapper->writeCPU(0x0012, 0xED);
    myMapper->writeCPU(0x0013, 0x8C);
    pushAddress(0x000B88);
    SUB_001152();
    if (poppedEntry.value != 0x000B88) return;
    SUB_000BA6();
    return;
}

void game::SUB_000B8E() {
    opCMP(myMapper->readCPU(0x0050), 0xA0);
    if (!flgC) {
        SUB_000BA6();
        return;
    }
    myMapper->writeCPU(0x0012, 0x60);
    pushAddress(0x000B98);
    SUB_000CC2();
    if (poppedEntry.value != 0x000B98) return;
    myMapper->writeCPU(0x0012, 0x0A);
    myMapper->writeCPU(0x0013, 0x8D);
    pushAddress(0x000BA3);
    SUB_001152();
    if (poppedEntry.value != 0x000BA3) return;
    SUB_000BA6();
    return;
}

void game::SUB_000BA6() {
    myMapper->writeCPU(0x00F4, 0x05);
    myMapper->writeCPU(0x0021, 0xC0);
    pushAddress(0x000BAE);
    SUB_0009AD();
    if (poppedEntry.value != 0x000BAE) return;
L_000BB1:
    if (myMapper->readCPU(0x0021) != 0) {
        wait();
        goto L_000BB1;
    }
    pushAddress(0x000BB5);
    SUB_0009B7();
    if (poppedEntry.value != 0x000BB5) return;
    SUB_000BB8();
    return;
}

void game::SUB_000BB8() {
    a = myMapper->readCPU(0x00FC);
    opEOR(0x80);
    myMapper->writeCPU(0x00FC, a);
    a = 0xD8;
    flgC = true;
    opSBC(myMapper->readCPU(0x004D));
    myMapper->writeCPU(0x004D, a);
    a = 0xA8;
    flgC = true;
    opSBC(myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x004E, a);
    myMapper->writeCPU(0x0060, a);
    a = 0x04;
    opSBC(myMapper->readCPU(0x004F));
    myMapper->writeCPU(0x004F, a);
    myMapper->writeCPU(0x0061, a);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0xB8);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    a = myMapper->readCPU(0x0010);
    flgC = true;
    opSBC(0x68);
    a = myMapper->readCPU(0x0011);
    opSBC(0x00);
    if (!flgC) {
        myMapper->writeCPU(0x0010, 0x68);
        myMapper->writeCPU(0x0011, 0x00);
    }
    pushAddress(0x000BF6);
    SUB_001DD7();
    if (poppedEntry.value != 0x000BF6) return;
    myMapper->writeCPU(0x0049, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x004A, myMapper->readCPU(0x0013));
    a = myMapper->readCPU(0x004E);
    opAND(0x07);
    if (a == 0x04) {
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x004E, a);
        a = myMapper->readCPU(0x004F);
        opSBC(0x00);
        myMapper->writeCPU(0x004F, a);
    }
    else {
        if (a != 0x05) {
            goto L_000C2A;
        }
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x004E, a);
        a = myMapper->readCPU(0x004F);
        opSBC(0x00);
        myMapper->writeCPU(0x004F, a);
    }
L_000C2A:
    pushAddress(0x000C2A);
    SUB_001633();
    if (poppedEntry.value != 0x000C2A) return;
    pushAddress(0x000C2D);
    SUB_0002AA();
    if (poppedEntry.value != 0x000C2D) return;
    SUB_000C30();
    return;
}

void game::SUB_000C30() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x18);
    a = myMapper->readCPU(0x004F);
    opSBC(0x01);
    if (flgC) {
        goto L_000C42;
    }
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x68);
    if (!flgZ) {
        goto L_000C44;
    }
L_000C42:
    a = 0xB0;
L_000C44:
    myMapper->writeCPU(0x0050, a);
    popAddress();
}

void game::SUB_000C47() {
    a = myMapper->readCPU(0x0060);
    flgC = true;
    opSBC(0xFC);
    a = myMapper->readCPU(0x0061);
    opSBC(0x03);
    if (!flgC) {
        goto L_000C5A;
    }
    myMapper->writeCPU(0x0061, 0x03);
    myMapper->writeCPU(0x0060, 0xFC);
L_000C5A:
    popAddress();
}

void game::SUB_000CA4() {
    a = myMapper->readCPU(0x006D);
    flgC = true;
    opSBC(myMapper->readCPU(0x0064));
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x006E);
    opSBC(myMapper->readCPU(0x0065));
    if (flgC) {
        opLSR_A(1);
        opROR_M(0x0010, 1);
        opLSR_A(1);
        opROR_M(0x0010, 1);
        opLSR_A(1);
        opROR_M(0x0010, 1);
        opORA(myMapper->readCPU(0x0010));
        if (flgZ) {
            goto L_000CC0;
        }
        flgC = true;
        popAddress();
        return;
    }
L_000CC0:
    flgC = false;
    popAddress();
}

void game::SUB_000CC2() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    pushAddress(0x000CCF);
    SUB_001DD7();
    if (poppedEntry.value != 0x000CCF) return;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0013));
    pushAddress(0x000CDA);
    SUB_0019E0();
    if (poppedEntry.value != 0x000CDA) return;
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0013));
    popAddress();
}

void game::SUB_000D28() {
    if (myMapper->readCPU(0x0068) == 0) {
        goto L_000D2F;
    }
    SUB_000CA4();
    return;
L_000D2F:
    flgC = true;
    popAddress();
}

void game::SUB_000D31() {
    if (!(myMapper->readCPU(0x0035) & 0x80)) {
        goto L_000D43;
    }
    a = myMapper->readCPU(0x0395);
    flgC = true;
    opSBC(0xE8);
    a = myMapper->readCPU(0x0396);
    opSBC(0x03);
    if (flgC) {
        goto L_000D4E;
    }
    popAddress();
    return;
L_000D43:
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0xE8);
    a = myMapper->readCPU(0x004F);
    opSBC(0x03);
    if (flgC) {
    L_000D4E:
        if (myMapper->readCPU(0x0031) & 0x80) {
            goto L_000D72;
        }
        if (!(myMapper->readCPU(0x00FC) & 0x80)) {
            goto L_000D60;
        }
        a = myMapper->readCPU(0x0025);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x0025, a);
        goto L_000D67;
    L_000D60:
        a = myMapper->readCPU(0x0027);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x0027, a);
    L_000D67:
        myMapper->writeCPU(0x0397, 0x80);
        a = myMapper->readCPU(0x005F);
        opORA(0x02);
        myMapper->writeCPU(0x005F, a);
    }
L_000D72:
    popAddress();
}

void game::SUB_000D73() {
    y = 0x00;
    do {
        myMapper->writeCPU(0x0306 + y, 0x00);
        myMapper->writeCPU(0x0305 + y, 0x20);
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    } while (a < 0x90);
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x30);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    pushAddress(0x000D9A);
    SUB_001DD7();
    if (poppedEntry.value != 0x000D9A) return;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0013));
    pushAddress(0x000DA5);
    SUB_0019E0();
    if (poppedEntry.value != 0x000DA5) return;
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(0x06);
    y = a;
    a = myMapper->readCPU(0x0013);
    pushAddress(0x000DB0);
    SUB_001474();
    if (poppedEntry.value != 0x000DB0) return;
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_000DBC;
    }
    a = myMapper->readCPU(0x002D);
    goto L_000DBE;
L_000DBC:
    a = myMapper->readCPU(0x002C);
L_000DBE:
    opAND(0x01);
    y = a;
    opINY(1);
    myMapper->writeCPU(0x2007, y);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x8DD5 + y));
        opINY(1);
        opCMP(y, 0x0D);
    } while (!flgC);
    SUB_000F37();
    return;
}

void game::SUB_000DE2() {
    myMapper->writeCPU(0x0397, 0x00);
    pushAddress(0x000DE7);
    SUB_0009C1();
    if (poppedEntry.value != 0x000DE7) return;
    if (myMapper->readCPU(0x0035) & 0x80) {
        a = myMapper->readCPU(0x0395);
        flgC = true;
        opSBC(0xE8);
        a = myMapper->readCPU(0x0396);
        opSBC(0x03);
        if (flgC) {
            goto L_000E1D;
        }
    }
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0xE8);
    a = myMapper->readCPU(0x004F);
    opSBC(0x03);
    if (!flgC) {
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0x98);
        a = myMapper->readCPU(0x004F);
        opSBC(0x00);
        if (flgC) {
            goto L_000E35;
        }
        myMapper->writeCPU(0x004F, 0x01);
        myMapper->writeCPU(0x004E, 0x64);
        myMapper->writeCPU(0x004D, 0x6C);
    }
L_000E1D:
    a = myMapper->readCPU(0x005F);
    opAND(0x02);
    if (!flgZ) {
        a = myMapper->readCPU(0x0023);
        opORA(myMapper->readCPU(0x0024));
        if (flgZ) {
            goto L_000E35;
        }
        a = myMapper->readCPU(0x00FC);
        opEOR(myMapper->readCPU(0x0397));
        myMapper->writeCPU(0x00FC, a);
        opPLA();
        opPLA();
        SUB_0000AC();
        return;
    }
L_000E35:
    popAddress();
}

void game::SUB_000E36() {
    a = myMapper->readCPU(0x00EB);
    opAND(0x0F);
    myMapper->writeCPU(0x00ED, a);
    a = myMapper->readCPU(0x00EC);
    opAND(0x0F);
    myMapper->writeCPU(0x0059, a);
    myMapper->writeCPU(0x4016, 0x01);
    myMapper->writeCPU(0x4016, 0x00);
    x = 0x08;
    do {
        a = myMapper->readCPU(0x4016);
        opAND(0x03);
        opCMP(a, 0x01);
        opROR_M(0x00EB, 1);
        a = myMapper->readCPU(0x4017);
        opAND(0x03);
        opCMP(a, 0x01);
        opROR_M(0x00EC, 1);
        opDEX(1);
    } while (!flgZ);
    if (!(myMapper->readCPU(0x0031) & 0x80)) {
        a = myMapper->readCPU(0x00ED);
        opEOR(0xFF);
        myMapper->writeCPU(0x00EA, a);
        a = myMapper->readCPU(0x00EB);
        opEOR(myMapper->readCPU(0x00ED));
        opAND(myMapper->readCPU(0x00EA));
        myMapper->writeCPU(0x00E9, a);
        a = myMapper->readCPU(0x0059);
        opEOR(0xFF);
        myMapper->writeCPU(0x00EA, a);
        a = myMapper->readCPU(0x00EC);
        opEOR(myMapper->readCPU(0x0059));
        opAND(myMapper->readCPU(0x00EA));
        myMapper->writeCPU(0x00EA, a);
        if (myMapper->readCPU(0x00FC) & 0x80) {
            myMapper->writeCPU(0x0010, myMapper->readCPU(0x00E9));
            myMapper->writeCPU(0x00E9, myMapper->readCPU(0x00EA));
            myMapper->writeCPU(0x00EA, myMapper->readCPU(0x0010));
        }
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x001D);
    opAND(0x1F);
    if (flgZ) {
        pushAddress(0x000E9A);
        SUB_000F4A();
        if (poppedEntry.value != 0x000E9A) return;
        opAND(0x07);
        y = a;
        a = myMapper->readCPU(0x8EBC + y);
        myMapper->writeCPU(0x00E9, a);
        myMapper->writeCPU(0x0038, a);
        a = myMapper->readCPU(0x001D);
        opAND(0x3F);
        if (!flgZ) {
            goto L_000EB7;
        }
        pushAddress(0x000EAD);
        SUB_000F4A();
        if (poppedEntry.value != 0x000EAD) return;
        opAND(0x03);
        opORA(myMapper->readCPU(0x00E9));
        myMapper->writeCPU(0x00E9, a);
        popAddress();
        return;
    }
L_000EB7:
    myMapper->writeCPU(0x00E9, myMapper->readCPU(0x0038));
    popAddress();
}

void game::SUB_000EC4() {
    y = 0x00;
    myMapper->writeCPU(0x2001, y);
    a = 0x20;
    pushAddress(0x000ECB);
    SUB_001474();
    if (poppedEntry.value != 0x000ECB) return;
    myMapper->writeCPU(0x0010, 0x03);
    a = 0x30;
    do {
        do {
            myMapper->writeCPU(0x2007, a);
            opDEY(1);
        } while (!flgZ);
        opDEC(0x0010, 1);
    } while (!flgZ);
    do {
        myMapper->writeCPU(0x2007, a);
        opINY(1);
        opCMP(y, 0xC0);
    } while (!flgC);
    a = 0x00;
    do {
        myMapper->writeCPU(0x2007, a);
        opINY(1);
    } while (!flgZ);
    SUB_00145F();
    return;
}

void game::SUB_000EF1() {
    y = 0x00;
    a = 0xF0;
    do {
        myMapper->writeCPU(0x0700 + y, a);
        opINY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_000EFC() {
    a = 0x10;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000F02();
        return;
    }
    SUB_000F00();
    return;
}

void game::SUB_000F00() {
    a = 0x20;
    SUB_000F02();
    return;
}

void game::SUB_000F02() {
    myMapper->writeCPU(0x0048, a);
    a = 0x00;
    myMapper->writeCPU(0x2001, a);
    y = a;
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A3 + y));
        opINY(1);
        opCMP(y, myMapper->readCPU(0x0048));
    } while (!flgC);
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x00EF));
    SUB_000F37();
    return;
}

void game::SUB_000F37() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x00EE));
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x00F2));
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x00F3));
    popAddress();
}

void game::SUB_000F4A() {
    a = myMapper->readCPU(0x000F);
    myMapper->writeCPU(0x000E, a);
    opASL_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x000E));
    flgC = false;
    opADC(0x11);
    myMapper->writeCPU(0x000F, a);
    popAddress();
}

void game::SUB_000F59() {
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0013));
    popAddress();
}

void game::SUB_000F62() {
    a = 0x00;
    myMapper->writeCPU(0x0014, a);
    myMapper->writeCPU(0x0015, a);
    myMapper->writeCPU(0x0016, a);
    while (true) {
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0011);
        opSBC(0x27);
        myMapper->writeCPU(0x0013, a);
        if (!flgC) {
            goto L_000F81;
        }
        opINC(0x0016, 1);
        pushAddress(0x000F7B);
        SUB_000F59();
        if (poppedEntry.value != 0x000F7B) return;
    }
    do {
    L_000F81:
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(0xE8);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0011);
        opSBC(0x03);
        myMapper->writeCPU(0x0013, a);
        if (!flgC) {
            goto L_000F9B;
        }
        pushAddress(0x000F90);
        SUB_000F59();
        if (poppedEntry.value != 0x000F90) return;
        a = myMapper->readCPU(0x0015);
        opADC(0x0F);
        myMapper->writeCPU(0x0015, a);
    } while (!flgZ);
    do {
    L_000F9B:
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(0x64);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0011);
        opSBC(0x00);
        myMapper->writeCPU(0x0013, a);
        if (!flgC) {
            SUB_000FB5();
            return;
        }
        pushAddress(0x000FAA);
        SUB_000F59();
        if (poppedEntry.value != 0x000FAA) return;
        a = myMapper->readCPU(0x0015);
        opADC(0x00);
        myMapper->writeCPU(0x0015, a);
    } while (!flgZ);
    SUB_000FB5();
    return;
}

void game::SUB_000FB5() {
    do {
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(0x0A);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0011);
        opSBC(0x00);
        myMapper->writeCPU(0x0013, a);
        if (!flgC) {
            goto L_000FCF;
        }
        pushAddress(0x000FC4);
        SUB_000F59();
        if (poppedEntry.value != 0x000FC4) return;
        a = myMapper->readCPU(0x0014);
        opADC(0x0F);
        myMapper->writeCPU(0x0014, a);
    } while (!flgZ);
L_000FCF:
    a = myMapper->readCPU(0x0010);
    opORA(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0014, a);
    popAddress();
}

void game::SUB_000FFC() {
    a = myMapper->readCPU(0x0025);
    flgC = true;
    opSBC(myMapper->readCPU(0x0027));
    a = myMapper->readCPU(0x0026);
    opSBC(myMapper->readCPU(0x0028));
    if (!flgC) {
        goto L_00101B;
    }
    a = myMapper->readCPU(0x0029);
    flgC = true;
    opSBC(myMapper->readCPU(0x0025));
    a = myMapper->readCPU(0x002A);
    opSBC(myMapper->readCPU(0x0026));
    if (flgC) {
        goto L_00101A;
    }
    myMapper->writeCPU(0x0029, myMapper->readCPU(0x0025));
    myMapper->writeCPU(0x002A, myMapper->readCPU(0x0026));
    do {
    L_00101A:
        popAddress();
        return;
    L_00101B:
        a = myMapper->readCPU(0x0027);
        flgC = true;
        opSBC(myMapper->readCPU(0x0029));
        a = myMapper->readCPU(0x0028);
        opSBC(myMapper->readCPU(0x002A));
    } while (!flgC);
    myMapper->writeCPU(0x0029, myMapper->readCPU(0x0027));
    myMapper->writeCPU(0x002A, myMapper->readCPU(0x0028));
    popAddress();
}

void game::SUB_00102F() {
    a = 0x00;
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x0026, a);
    myMapper->writeCPU(0x0027, a);
    myMapper->writeCPU(0x0028, a);
    myMapper->writeCPU(0x002B, a);
    popAddress();
}

void game::SUB_00103C() {
    pushStatus();
    pushAddress(0x00103D);
    SUB_000F62();
    if (poppedEntry.value != 0x00103D) return;
    a = myMapper->readCPU(0x0016);
    if (a >= 0x0A) {
        a = 0x00;
    }
    myMapper->writeCPU(0x0083, a);
    a = myMapper->readCPU(0x0015);
    opPHA();
    opLSR_A(4);
    myMapper->writeCPU(0x0084, a);
    opPLA();
    opAND(0x0F);
    myMapper->writeCPU(0x0085, a);
    a = myMapper->readCPU(0x0014);
    opPHA();
    opLSR_A(4);
    myMapper->writeCPU(0x0086, a);
    opPLA();
    opAND(0x0F);
    myMapper->writeCPU(0x0087, a);
    myMapper->writeCPU(0x0088, 0x00);
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0083 + y);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_00107B;
        }
        myMapper->writeCPU(0x0083 + y, 0x30);
        opINY(1);
    } while (y < 0x04);
L_00107B:
    popStatus();
    if (flgC) {
        goto L_00107F;
    }
    popAddress();
    return;
L_00107F:
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0083 + y));
        opINY(1);
        opCMP(y, 0x05);
    } while (!flgC);
    popAddress();
}

void game::SUB_00108D() {
    myMapper->writeCPU(0x2001, 0x00);
    a = 0x23;
    y = 0xC0;
    pushAddress(0x001096);
    SUB_001474();
    if (poppedEntry.value != 0x001096) return;
    pushAddress(0x001099);
    SUB_0010D2();
    if (poppedEntry.value != 0x001099) return;
    a = 0x2B;
    y = 0xC0;
    pushAddress(0x0010A0);
    SUB_001474();
    if (poppedEntry.value != 0x0010A0) return;
    pushAddress(0x0010A3);
    SUB_0010D2();
    if (poppedEntry.value != 0x0010A3) return;
    a = 0x23;
    y = 0xD0;
    pushAddress(0x0010AA);
    SUB_001474();
    if (poppedEntry.value != 0x0010AA) return;
    x = 0x02;
    do {
        y = 0x00;
        do {
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x90ED + y));
            opINY(1);
        } while (y < 0x08);
        opDEX(1);
    } while (!flgN);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x90F5 + y));
        opINY(1);
        opCMP(y, 0x08);
    } while (!flgC);
    pushAddress(0x0010CC);
    SUB_00145F();
    if (poppedEntry.value != 0x0010CC) return;
    SUB_000F37();
    return;
}

void game::SUB_0010D2() {
    x = 0x07;
    do {
        y = 0x00;
        do {
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x90E5 + y));
            opINY(1);
            opCMP(y, 0x08);
        } while (!flgC);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0010FD() {
    a = 0xFF;
    myMapper->writeCPU(0x0200, a);
    myMapper->writeCPU(0x025A, a);
    myMapper->writeCPU(0x0222, a);
    popAddress();
}

void game::SUB_001109() {
    a = 0x00;
    myMapper->writeCPU(0x0014, a);
    myMapper->writeCPU(0x0015, a);
    y = 0x0F;
    do {
        opBIT(myMapper->readCPU(0x0011));
        if (flgN) {
            goto L_001121;
        }
        opASL_M(0x0010, 1);
        opROL_M(0x0011, 1);
        opASL_M(0x0012, 1);
        opROL_M(0x0013, 1);
        opDEY(1);
    } while (!flgN);
    popAddress();
    return;
L_001121:
    y = 0x00;
    do {
        opBIT(myMapper->readCPU(0x0013));
        if (flgN) {
            goto L_00112E;
        }
        opASL_M(0x0012, 1);
        opROL_M(0x0013, 1);
        opINY(1);
    } while (!flgN);
    do {
    L_00112E:
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(myMapper->readCPU(0x0012));
        a = myMapper->readCPU(0x0011);
        opSBC(myMapper->readCPU(0x0013));
        if (!flgC) {
            goto L_001146;
        }
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(myMapper->readCPU(0x0012));
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x0011);
        opSBC(myMapper->readCPU(0x0013));
        myMapper->writeCPU(0x0011, a);
    L_001146:
        opROL_M(0x0014, 1);
        opROL_M(0x0015, 1);
        opLSR_M(0x0013, 1);
        opROR_M(0x0012, 1);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_001152() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    a = myMapper->readCPU(0x0011);
    setLoadFlag(a);
    if (flgN) {
        goto L_001171;
    }
    y = myMapper->readCPU(0x0010);
    pushAddress(0x001160);
    SUB_001474();
    if (poppedEntry.value != 0x001160) return;
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_001171;
        }
        myMapper->writeCPU(0x2007, a);
        opINY(1);
    } while (!flgZ);
L_001171:
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x00EF));
    SUB_000F37();
    return;
}

void game::SUB_001179() {
    a = myMapper->readCPU(0x0023);
    opORA(myMapper->readCPU(0x0024));
    if (flgZ) {
        if (myMapper->readCPU(0x0031) & 0x80) {
            goto L_0011B0;
        }
        pushAddress(0x001183);
        SUB_000FFC();
        if (poppedEntry.value != 0x001183) return;
        if (myMapper->readCPU(0x0033) & 0x80) {
            opINC(0x002C, 1);
            a = myMapper->readCPU(0x002C);
            opCMP(a, 0x02);
            if (flgC) {
                goto L_0011B0;
            }
            if (!flgC) {
                goto L_0011A9;
            }
        }
        opINC(0x002D, 1);
        a = myMapper->readCPU(0x002D);
        opLSR_A(1);
        if (flgC) {
            goto L_0011A9;
        }
        opCMP(myMapper->readCPU(0x0025), myMapper->readCPU(0x0027));
        if (flgZ) {
            goto L_0011B0;
        }
        if (!flgC) {
            goto L_0011B0;
        }
        pushAddress(0x0011A3);
        SUB_004BBC();
        if (poppedEntry.value != 0x0011A3) return;
        pushAddress(0x0011A6);
        SUB_00102F();
        if (poppedEntry.value != 0x0011A6) return;
    L_0011A9:
        opPLA();
        opPLA();
        SUB_00008D();
        return;
    }
    flgC = false;
    popAddress();
    return;
L_0011B0:
    flgC = true;
    popAddress();
}

void game::SUB_00127B() {
    a = 0x22;
    y = 0x06;
    pushAddress(0x00127F);
    SUB_001474();
    if (poppedEntry.value != 0x00127F) return;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0025));
    a = myMapper->readCPU(0x0026);
    setLoadFlag(a);
    pushAddress(0x001288);
    SUB_001298();
    if (poppedEntry.value != 0x001288) return;
    a = 0x22;
    y = 0x15;
    pushAddress(0x00128F);
    SUB_001474();
    if (poppedEntry.value != 0x00128F) return;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0027));
    a = myMapper->readCPU(0x0028);
    setLoadFlag(a);
    SUB_001298();
    return;
}

void game::SUB_001298() {
    myMapper->writeCPU(0x0011, a);
    flgC = true;
    SUB_00103C();
    return;
}

void game::SUB_00129E() {
    x = 0x03;
    do {
        myMapper->writeCPU(0x0700 + y, a);
        pushAddress(0x0012A3);
        SUB_002AF3();
        if (poppedEntry.value != 0x0012A3) return;
        flgC = false;
        opADC(0x08);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0012AD() {
    pushAddress(0x0012AD);
    SUB_0012B0();
    if (poppedEntry.value != 0x0012AD) return;
    SUB_0012B0();
    return;
}

void game::SUB_0012B0() {
    x = 0x03;
    do {
        myMapper->writeCPU(0x0700 + y, a);
        pushAddress(0x0012B5);
        SUB_002AF3();
        if (poppedEntry.value != 0x0012B5) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0012D3() {
    do {
        opPHA();
        myMapper->writeCPU(0x0700 + y, myMapper->readCPU(0x002F));
        myMapper->writeCPU(0x0701 + y, myMapper->readCPU(0x9304 + x));
        a = 0x01;
        myMapper->writeCPU(0x0702 + y, a);
        opPLA();
        myMapper->writeCPU(0x0703 + y, a);
        flgC = false;
        opADC(0x08);
        opINX(1);
        pushAddress(0x0012EC);
        SUB_002AF3();
        if (poppedEntry.value != 0x0012EC) return;
    } while (x < myMapper->readCPU(0x0010));
    popAddress();
}

void game::SUB_001372() {
    myMapper->writeCPU(0x0011, 0x20);
    myMapper->writeCPU(0x0010, 0xCB);
    myMapper->writeCPU(0x0012, 0x12);
    myMapper->writeCPU(0x0013, 0x93);
    pushAddress(0x001382);
    SUB_001152();
    if (poppedEntry.value != 0x001382) return;
    pushAddress(0x001385);
    SUB_00127B();
    if (poppedEntry.value != 0x001385) return;
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_0013B5;
    }
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0010, 0xA5);
    myMapper->writeCPU(0x0012, 0xDF);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x00139C);
    SUB_001152();
    if (poppedEntry.value != 0x00139C) return;
    myMapper->writeCPU(0x0010, 0xE5);
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0012, 0xF7);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x0013AF);
    SUB_001152();
    if (poppedEntry.value != 0x0013AF) return;
    goto L_0013DB;
L_0013B5:
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0010, 0xA2);
    myMapper->writeCPU(0x0012, 0x1C);
    myMapper->writeCPU(0x0013, 0x93);
    pushAddress(0x0013C5);
    SUB_001152();
    if (poppedEntry.value != 0x0013C5) return;
    myMapper->writeCPU(0x0011, 0x23);
    myMapper->writeCPU(0x0010, 0x07);
    myMapper->writeCPU(0x0012, 0x39);
    myMapper->writeCPU(0x0013, 0x93);
    pushAddress(0x0013D8);
    SUB_001152();
    if (poppedEntry.value != 0x0013D8) return;
L_0013DB:
    myMapper->writeCPU(0x00F4, 0x05);
    myMapper->writeCPU(0x0017, 0x10);
    a = 0x01;
    pushAddress(0x0013E5);
    SUB_0040B1();
    if (poppedEntry.value != 0x0013E5) return;
    myMapper->writeCPU(0x0021, a);
    SUB_0013EA();
    return;
}

void game::SUB_0013EA() {
    while (true) {
        pushAddress(0x0013EA);
        SUB_0009AD();
        if (poppedEntry.value != 0x0013EA) return;
        do {
            wait();
            a = myMapper->readCPU(0x0021);
            opAND(0x1F);
        } while (!flgZ);
        pushAddress(0x0013F3);
        SUB_0009B7();
        if (poppedEntry.value != 0x0013F3) return;
        opINC(0x0021, 1);
        a = 0x38;
        y = 0x03;
        pushAddress(0x0013FC);
        SUB_00129E();
        if (poppedEntry.value != 0x0013FC) return;
        a = 0xB0;
        y = 0x0F;
        pushAddress(0x001403);
        SUB_00129E();
        if (poppedEntry.value != 0x001403) return;
        a = 0x68;
        y = 0x00;
        pushAddress(0x00140A);
        SUB_0012AD();
        if (poppedEntry.value != 0x00140A) return;
        a = 0x00;
        y = 0x02;
        pushAddress(0x001411);
        SUB_0012AD();
        if (poppedEntry.value != 0x001411) return;
        x = 0x01;
        myMapper->writeCPU(0x0701, x);
        opINX(1);
        myMapper->writeCPU(0x070D, x);
        a = 0x1E;
        myMapper->writeCPU(0x0705, a);
        myMapper->writeCPU(0x0711, a);
        a = 0x19;
        myMapper->writeCPU(0x0709, a);
        myMapper->writeCPU(0x0715, a);
        if (!(myMapper->readCPU(0x0033) & 0x80)) {
            myMapper->writeCPU(0x070D, 0x0C);
            myMapper->writeCPU(0x0711, 0x18);
            myMapper->writeCPU(0x0715, 0x16);
        }
        a = myMapper->readCPU(0x0021);
        opAND(0x20);
        if (!flgZ) {
            y = 0x00;
            opCMP(myMapper->readCPU(0x0025), myMapper->readCPU(0x0027));
            if (flgZ) {
                goto L_001450;
            }
            if (flgC) {
                goto L_001452;
            }
        L_001450:
            y = 0x0C;
        L_001452:
            a = 0xF0;
            pushAddress(0x001454);
            SUB_0012B0();
            if (poppedEntry.value != 0x001454) return;
        }
        opDEC(0x0017, 1);
        if (flgZ) {
            goto L_00145E;
        }
    }
L_00145E:
    popAddress();
}

void game::SUB_00145F() {
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x00EF));
    popAddress();
}

void game::SUB_001465() {
    y = 0x00;
    do {
        myMapper->writeCPU(0x00A3 + y, a);
        pushAddress(0x00146A);
        SUB_002AF3();
        if (poppedEntry.value != 0x00146A) return;
        opCMP(y, 0x20);
    } while (!flgC);
    SUB_000F00();
    return;
}

void game::SUB_001474() {
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, y);
    popAddress();
}

void game::SUB_00147B() {
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    if (flgC) {
    }
    else {
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0xB0);
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x004F);
        opSBC(0x00);
        myMapper->writeCPU(0x0011, a);
        pushAddress(0x001490);
        SUB_001DD7();
        if (poppedEntry.value != 0x001490) return;
        a = 0x68;
        flgC = true;
        opSBC(myMapper->readCPU(0x0012));
        a = 0x00;
        opSBC(myMapper->readCPU(0x0013));
        if (!flgC) {
            a = 0x70;
            flgC = true;
            opSBC(myMapper->readCPU(0x0012));
            a = 0x03;
            opSBC(myMapper->readCPU(0x0013));
            if (flgC) {
                a = myMapper->readCPU(0x0012);
                opAND(0x03);
                if (flgZ) {
                    myMapper->writeCPU(0x0049, myMapper->readCPU(0x0012));
                    a = myMapper->readCPU(0x004A);
                    opAND(0x80);
                    opORA(myMapper->readCPU(0x0013));
                    myMapper->writeCPU(0x004A, a);
                }
            }
        }
    }
    a = myMapper->readCPU(0x004A);
    opAND(0x0F);
    if (a >= 0x01) {
        if (a >= 0x03) {
            goto L_0014CB;
        }
        y = 0x00;
        setLoadFlag(y);
        if (flgZ) {
            goto L_0014CD;
        }
    }
L_0014CB:
    y = 0x02;
L_0014CD:
    myMapper->writeCPU(0x00B0, myMapper->readCPU(0x94D8 + y));
    myMapper->writeCPU(0x00B1, myMapper->readCPU(0x94D9 + y));
    popAddress();
}

void game::SUB_0014DC() {
    SUB_00157C();
    return;
}

void game::SUB_0014DF() {
    a = 0x00;
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x00EF, a);
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    if (!flgC) {
        goto L_00150B;
    }
    pushAddress(0x0014EB);
    SUB_000EFC();
    if (poppedEntry.value != 0x0014EB) return;
    a = myMapper->readCPU(0x0200);
    setLoadFlag(a);
    if (flgN) {
        SUB_0014DC();
        return;
    }
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0201));
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0202 + y));
        opINY(1);
        opCMP(y, 0x20);
    } while (!flgC);
    if (flgC) {
        SUB_00157C();
        return;
    }
L_00150B:
    a = myMapper->readCPU(0x2002);
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0222 + y);
        setLoadFlag(a);
        if (flgN) {
            goto L_001569;
        }
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0223 + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0224 + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0225 + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0226 + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0227 + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0228 + y));
        a = y;
        flgC = false;
        opADC(0x07);
        y = a;
    } while (y < 0x38);
    y = 0x00;
    do {
        a = myMapper->readCPU(0x025A + y);
        setLoadFlag(a);
        if (flgN) {
            goto L_001569;
        }
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x025B + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x025C + y));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x025D + y));
        opINY(4);
    } while (y < 0x30);
L_001569:
    a = myMapper->readCPU(0x004A);
    opASL_A(1);
    opAND(0x02);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x00EE);
    opAND(0xFD);
    opORA(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x00EE, a);
    myMapper->writeCPU(0x00F3, myMapper->readCPU(0x0049));
    SUB_00157C();
    return;
}

void game::SUB_00157C() {
    a = 0x1E;
    myMapper->writeCPU(0x00EF, a);
    myMapper->writeCPU(0x2001, a);
    SUB_000F37();
    return;
}

void game::SUB_001586() {
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    if (!flgC) {
        SUB_0016E8();
        return;
    }
    a = myMapper->readCPU(0x004A);
    setLoadFlag(a);
    if (flgN) {
        opAND(0x0F);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0011, a);
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x0049));
        SUB_0015B7();
        return;
    }
    opAND(0x0F);
    myMapper->writeCPU(0x0011, a);
    a = myMapper->readCPU(0x0049);
    flgC = true;
    opSBC(0x08);
    if (flgC) {
        goto L_0015AF;
    }
    flgC = true;
    opSBC(0x10);
    flgC = false;
L_0015AF:
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0011);
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    SUB_0015B7();
    return;
}

void game::SUB_0015B7() {
    pushAddress(0x0015B7);
    SUB_0019E0();
    if (poppedEntry.value != 0x0015B7) return;
    myMapper->writeCPU(0x0200, a);
    myMapper->writeCPU(0x0201, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0013, 0x00);
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0011));
    do {
        opDEC(0x0012, 1);
        if (flgN) {
            goto L_0015D7;
        }
        a = 0x1E;
        flgC = false;
        opADC(myMapper->readCPU(0x0013));
        myMapper->writeCPU(0x0013, a);
    } while (!flgZ);
L_0015D7:
    a = myMapper->readCPU(0x0010);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0013));
    y = a;
    a = myMapper->readCPU(0x0500 + y);
    myMapper->writeCPU(0x0030, a);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x9A37 + y));
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x9A38 + y));
    y = 0x00;
    x = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_00160F;
        }
        opINY(1);
        myMapper->writeCPU(0x0010, myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0011, myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y));
        do {
            opDEC(0x0011, 1);
            if (flgN) {
                goto L_001613;
            }
            a = myMapper->readCPU(0x0010);
            myMapper->writeCPU(0x0100 + x, a);
            opINX(1);
        } while (!flgZ);
    L_00160F:
        myMapper->writeCPU(0x0100 + x, a);
        opINX(1);
    L_001613:
        opINY(1);
    } while (x < 0x20);
    a = myMapper->readCPU(0x0030);
    opCMP(a, 0x07);
    if (flgC) {
        opCMP(a, 0x10);
        if (flgC) {
            goto L_001627;
        }
        opADC(0xEE);
        myMapper->writeCPU(0x010D, a);
    }
L_001627:
    y = 0x1F;
    do {
        a = myMapper->readCPU(0x0100 + y);
        myMapper->writeCPU(0x0202 + y, a);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_001633() {
    pushAddress(0x001633);
    SUB_001A00();
    if (poppedEntry.value != 0x001633) return;
    myMapper->writeCPU(0x2001, 0x00);
    myMapper->writeCPU(0x0014, 0x1F);
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0049));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x004A));
    do {
        a = myMapper->readCPU(0x0010);
        opPHA();
        a = myMapper->readCPU(0x0011);
        opPHA();
        pushAddress(0x00164D);
        SUB_0015B7();
        if (poppedEntry.value != 0x00164D) return;
        opPLA();
        myMapper->writeCPU(0x0011, a);
        opPLA();
        myMapper->writeCPU(0x0010, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0200));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0201));
        y = 0x00;
        do {
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x0202 + y));
            opINY(1);
        } while (y < 0x20);
        a = myMapper->readCPU(0x0010);
        flgC = false;
        opADC(0x08);
        opCMP(a, 0xF0);
        if (!flgC) {
            goto L_00167B;
        }
        opADC(0x0F);
        flgC = true;
    L_00167B:
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x0011);
        opADC(0x00);
        myMapper->writeCPU(0x0011, a);
        opDEC(0x0014, 1);
    } while (!flgN);
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x00EF));
    pushAddress(0x00168C);
    SUB_000F37();
    if (poppedEntry.value != 0x00168C) return;
    SUB_00168F();
    return;
}

void game::SUB_00168F() {
    y = 0x0B;
    do {
        myMapper->writeCPU(0x0754 + y, myMapper->readCPU(0x997B + y));
        opDEY(1);
    } while (!flgN);
    if (!(myMapper->readCPU(0x0033) & 0x80)) {
        myMapper->writeCPU(0x075D, 0x0C);
    }
    myMapper->writeCPU(0x004C, 0x00);
    myMapper->writeCPU(0x0749, 0xBE);
    myMapper->writeCPU(0x074A, 0x01);
    a = myMapper->readCPU(0x00F4);
    if (a >= 0x01) {
        if (a >= 0x05) {
            goto L_0016BF;
        }
        a = 0xF0;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0016CA;
        }
    }
L_0016BF:
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0064));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0065));
    pushAddress(0x0016C7);
    SUB_003872();
    if (poppedEntry.value != 0x0016C7) return;
L_0016CA:
    myMapper->writeCPU(0x0750, a);
    myMapper->writeCPU(0x0751, 0x2D);
    a = 0x01;
    myMapper->writeCPU(0x0752, a);
    myMapper->writeCPU(0x074E, a);
    a = 0xE0;
    myMapper->writeCPU(0x0753, a);
    myMapper->writeCPU(0x074F, a);
    myMapper->writeCPU(0x074D, 0x2E);
    popAddress();
}

void game::SUB_0016E8() {
    a = myMapper->readCPU(0x0049);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0010, a);
    pushStatus();
    a = myMapper->readCPU(0x004A);
    opADC(0x00);
    myMapper->writeCPU(0x0011, a);
    popStatus();
    if (!flgC) {
        if (myMapper->readCPU(0x0010) < 0xF0) {
            goto L_00170C;
        }
    }
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0011);
    opADC(0x00);
    myMapper->writeCPU(0x0011, a);
L_00170C:
    pushAddress(0x00170C);
    SUB_0019E0();
    if (poppedEntry.value != 0x00170C) return;
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(0x1A);
    myMapper->writeCPU(0x0012, a);
    y = 0x00;
    do {
        myMapper->writeCPU(0x0222 + y, myMapper->readCPU(0x0013));
        myMapper->writeCPU(0x0223 + y, myMapper->readCPU(0x0012));
        a = myMapper->readCPU(0x0012);
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0013);
        opADC(0x00);
        myMapper->writeCPU(0x0013, a);
        opAND(0x03);
        if (a == 0x03) {
            a = myMapper->readCPU(0x0012);
            opCMP(a, 0xC0);
            if (!flgC) {
                goto L_001747;
            }
            opADC(0x3F);
            myMapper->writeCPU(0x0012, a);
            a = myMapper->readCPU(0x0013);
            opAND(0x28);
            opEOR(0x08);
            myMapper->writeCPU(0x0013, a);
        }
    L_001747:
        a = y;
        flgC = false;
        opADC(0x07);
        y = a;
    } while (y < 0x38);
    opINC(0x0012, 2);
    y = 0x00;
    do {
        myMapper->writeCPU(0x025A + y, myMapper->readCPU(0x0013));
        myMapper->writeCPU(0x025B + y, myMapper->readCPU(0x0012));
        a = myMapper->readCPU(0x0012);
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0013);
        opADC(0x00);
        myMapper->writeCPU(0x0013, a);
        opAND(0x03);
        if (a == 0x03) {
            a = myMapper->readCPU(0x0012);
            opCMP(a, 0xC0);
            if (!flgC) {
                goto L_001785;
            }
            opADC(0x3F);
            myMapper->writeCPU(0x0012, a);
            a = myMapper->readCPU(0x0013);
            opAND(0x28);
            opEOR(0x08);
            myMapper->writeCPU(0x0013, a);
        }
    L_001785:
        opINY(4);
    } while (y < 0x30);
    y = 0x00;
    x = 0x00;
    a = 0x32;
    myMapper->writeCPU(0x0255, a);
    myMapper->writeCPU(0x0256, a);
    myMapper->writeCPU(0x0258, a);
    myMapper->writeCPU(0x0259, a);
    if (myMapper->readCPU(0x00FC) & 0x80) {
        a = 0x37;
        x = 0x30;
        setLoadFlag(x);
        if (!flgZ) {
            goto L_0017AB;
        }
    }
    a = 0xC7;
L_0017AB:
    myMapper->writeCPU(0x0257, a);
    a = myMapper->readCPU(0x0010);
    opAND(0x04);
    if (!flgZ) {
        x = 0x18;
        if (myMapper->readCPU(0x00FC) & 0x80) {
            a = 0x3B;
            x = 0x48;
            setLoadFlag(x);
            if (!flgZ) {
                goto L_0017C2;
            }
        }
        a = 0xCA;
    L_0017C2:
        myMapper->writeCPU(0x0257, a);
    }
    do {
        myMapper->writeCPU(0x025C + y, myMapper->readCPU(0x9894 + x));
        myMapper->writeCPU(0x025D + y, myMapper->readCPU(0x9895 + x));
        opINX(2);
        opINY(4);
    } while (y < 0x30);
    a = 0x32;
    myMapper->writeCPU(0x0224, a);
    myMapper->writeCPU(0x0225, a);
    myMapper->writeCPU(0x0226, a);
    myMapper->writeCPU(0x0227, a);
    myMapper->writeCPU(0x0228, a);
    a = myMapper->readCPU(0x0025);
    pushAddress(0x0017EE);
    SUB_001A1F();
    if (poppedEntry.value != 0x0017EE) return;
    myMapper->writeCPU(0x0039, x);
    if (x == 0x00) {
        myMapper->writeCPU(0x0039, 0x10);
    }
    myMapper->writeCPU(0x003A, y);
    a = myMapper->readCPU(0x0027);
    pushAddress(0x0017FF);
    SUB_001A1F();
    if (poppedEntry.value != 0x0017FF) return;
    myMapper->writeCPU(0x003C, x);
    if (x == 0x00) {
        myMapper->writeCPU(0x003C, 0x10);
    }
    myMapper->writeCPU(0x003D, y);
    myMapper->writeCPU(0x003B, 0x10);
    myMapper->writeCPU(0x0011, 0x00);
    pushAddress(0x001816);
    SUB_0018F4();
    if (poppedEntry.value != 0x001816) return;
    myMapper->writeCPU(0x003B, 0x0F);
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0024));
    a = 0x00;
    myMapper->writeCPU(0x0011, a);
    myMapper->writeCPU(0x0014, a);
    pushAddress(0x001827);
    SUB_000FB5();
    if (poppedEntry.value != 0x001827) return;
    opPHA();
    opLSR_A(4);
    myMapper->writeCPU(0x0039, a);
    opPLA();
    opAND(0x0F);
    myMapper->writeCPU(0x003A, a);
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0023));
    a = 0x00;
    myMapper->writeCPU(0x0011, a);
    myMapper->writeCPU(0x0014, a);
    pushAddress(0x001840);
    SUB_000FB5();
    if (poppedEntry.value != 0x001840) return;
    opPHA();
    opLSR_A(4);
    myMapper->writeCPU(0x003C, a);
    opPLA();
    opAND(0x0F);
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x0011, 0x0E);
    pushAddress(0x001853);
    SUB_0018F4();
    if (poppedEntry.value != 0x001853) return;
    a = myMapper->readCPU(0x0062);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0039, a);
    flgC = false;
    opADC(0x09);
    myMapper->writeCPU(0x003A, a);
    myMapper->writeCPU(0x003B, 0x10);
    a = myMapper->readCPU(0x0063);
    opPHA();
    opLSR_A(4);
    if (flgZ) {
        a = 0x10;
    }
    myMapper->writeCPU(0x003C, a);
    opPLA();
    opAND(0x0F);
    myMapper->writeCPU(0x003D, a);
    if (myMapper->readCPU(0x0068) != 0) {
        goto L_00188C;
    }
    myMapper->writeCPU(0x0039, 0x10);
    a = 0x00;
    myMapper->writeCPU(0x003A, a);
    myMapper->writeCPU(0x003C, a);
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x003B, 0x0E);
L_00188C:
    myMapper->writeCPU(0x0011, 0x1C);
    pushAddress(0x001890);
    SUB_0018F4();
    if (poppedEntry.value != 0x001890) return;
    popAddress();
}

void game::SUB_0018F4() {
    y = 0x00;
    myMapper->writeCPU(0x0010, y);
    a = myMapper->readCPU(0x0049);
    opAND(0x04);
    if (flgZ) {
        goto L_001902;
    }
    myMapper->writeCPU(0x0010, 0x22);
    do {
    L_001902:
        a = myMapper->readCPU(0x0039 + y);
        if (a != 0x30) {
            goto L_00190B;
        }
        a = 0x10;
    L_00190B:
        opAND(0x1F);
        opASL_A(1);
        opADC(myMapper->readCPU(0x0010));
        x = a;
        myMapper->writeCPU(0x003E + y, myMapper->readCPU(0x9937 + x));
        myMapper->writeCPU(0x0043 + y, myMapper->readCPU(0x9938 + x));
        opINY(1);
    } while (y < 0x05);
    x = 0x00;
    y = myMapper->readCPU(0x0011);
    do {
        myMapper->writeCPU(0x022B + y, myMapper->readCPU((0x003E + x) & 0x00ff));
        myMapper->writeCPU(0x0232 + y, myMapper->readCPU((0x0043 + x) & 0x00ff));
        opINY(1);
        opINX(1);
        opCMP(x, 0x05);
    } while (!flgC);
    popAddress();
}

void game::SUB_00198B() {
    x = 0x00;
    do {
        myMapper->writeCPU(0x0500 + x, myMapper->readCPU(0x9D4A + x));
        opINX(1);
    } while (x < 0x8E);
    a = myMapper->readCPU(0x002D);
    if (a < 0x08) {
        goto L_0019A0;
    }
    a = 0x08;
L_0019A0:
    opPHA();
    opAND(0x0E);
    opASL_A(1);
    x = a;
    y = 0x00;
    do {
        a = myMapper->readCPU(0x99C2 + x);
        myMapper->writeCPU(0x0514 + y, a);
        opINX(1);
        opINY(1);
    } while (y < 0x03);
    opPLA();
    opAND(0x0E);
    x = a;
    myMapper->writeCPU(0x00A8, myMapper->readCPU(0x99D6 + x));
    myMapper->writeCPU(0x00A9, myMapper->readCPU(0x99D7 + x));
    popAddress();
}

void game::SUB_0019E0() {
    myMapper->writeCPU(0x0013, 0x00);
    a = myMapper->readCPU(0x0010);
    opAND(0xF8);
    myMapper->writeCPU(0x0012, a);
    opASL_M(0x0012, 1);
    opROL_M(0x0013, 1);
    opASL_M(0x0012, 1);
    opROL_M(0x0013, 1);
    a = myMapper->readCPU(0x0011);
    opASL_A(3);
    opAND(0x08);
    opORA(0x20);
    opORA(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0013, a);
    popAddress();
}

void game::SUB_001A00() {
    y = 0x04;
    if (!(myMapper->readCPU(0x00FC) & 0x80)) {
        goto L_001A10;
    }
    do {
        myMapper->writeCPU(0x0548 + y, myMapper->readCPU(0x9A1A + y));
        opDEY(1);
    } while (!flgN);
    popAddress();
    return;
    do {
    L_001A10:
        myMapper->writeCPU(0x0548 + y, myMapper->readCPU(0x9D92 + y));
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_001A1F() {
    myMapper->writeCPU(0x0010, a);
    a = 0x00;
    myMapper->writeCPU(0x0011, a);
    myMapper->writeCPU(0x0014, a);
    pushAddress(0x001A27);
    SUB_000FB5();
    if (poppedEntry.value != 0x001A27) return;
    a = myMapper->readCPU(0x0014);
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0x0014);
    opLSR_A(4);
    x = a;
    popAddress();
}

void game::SUB_001DD7() {
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0011));
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0012);
        flgC = true;
        opSBC(0xF0);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0013);
        opSBC(0x00);
        myMapper->writeCPU(0x0013, a);
        if (!flgC) {
            goto L_001DF3;
        }
        opINY(1);
    } while (!flgZ);
L_001DF3:
    a = y;
    opASL_A(4);
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0012, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0011));
    myMapper->writeCPU(0x0013, a);
    popAddress();
}

void game::SUB_001E04() {
    y = 0x07;
    do {
        myMapper->writeCPU(0x0071 + y, myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgN);
    if (!(myMapper->readCPU(0x00FC) & 0x80)) {
        SUB_001E18();
        return;
    }
    a = myMapper->readCPU(0x0073);
    opEOR(0x02);
    myMapper->writeCPU(0x0073, a);
    SUB_001E18();
    return;
}

void game::SUB_001E18() {
    myMapper->writeCPU(0x0058, x);
    x = myMapper->readCPU(0x0014);
    y = 0x00;
    myMapper->writeCPU(0x0014, 0x01);
    do {
        a = myMapper->readCPU(0x0071 + y);
        if (a != 0x80) {
            goto L_001E2D;
        }
        a = 0xF0;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_001E30;
        }
    L_001E2D:
        flgC = false;
        opADC(myMapper->readCPU(0x0011));
    L_001E30:
        myMapper->writeCPU(0x0700 + x, a);
        opINY(1);
        myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0x0071 + y));
        opINY(1);
        myMapper->writeCPU(0x0702 + x, myMapper->readCPU(0x0071 + y));
        opINY(1);
        a = myMapper->readCPU(0x0071 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0703 + x, a);
        opINY(1);
        opINX(4);
        opDEC(0x0014, 1);
    } while (!flgN);
    x = myMapper->readCPU(0x0058);
    popAddress();
}

void game::SUB_001E77() {
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    myMapper->writeCPU(0x0058, x);
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (flgN) {
        y = 0x00;
        setLoadFlag(y);
        if (flgZ) {
            goto L_001E8B;
        }
    }
    opAND(0x0F);
    opASL_A(1);
    y = a;
L_001E8B:
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x9E57 + y));
    a = myMapper->readCPU(0x9E58 + y);
    myMapper->writeCPU(0x0011, a);
    opBIT(myMapper->readCPU(0x004C));
    if (!flgV) {
        if (x != myMapper->readCPU(0x0079)) {
            goto L_001EC6;
        }
        myMapper->writeCPU(0x00FE, 0x02);
        a = myMapper->readCPU(0x0301 + x);
        opAND(0xC0);
        if (!flgZ) {
            a = myMapper->readCPU(0x0301 + x);
            opAND(0x30);
            if (flgZ) {
                goto L_001EB3;
            }
            myMapper->writeCPU(0x00FE, 0x05);
        L_001EB3:
            a = myMapper->readCPU(0x0305 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x039A));
            myMapper->writeCPU(0x0305 + x, a);
            a = myMapper->readCPU(0x0306 + x);
            opADC(myMapper->readCPU(0x039B));
            myMapper->writeCPU(0x0306 + x, a);
        }
    }
L_001EC6:
    a = 0x9E;
    opPHA();
    a = 0xCF;
    opPHA();
    indirectJump(myMapper->readCPU(0x0010) + (myMapper->readCPU((0x0010 + 1) & 0x00ff) << 8));
    if(poppedEntry.value == 0x9ECF) SUB_001ECF();
}

void game::SUB_001ECF() {
    //NOP
    pushAddress(0x001ED0);
    SUB_00200A();
    if (poppedEntry.value != 0x001ED0) return;
    pushAddress(0x001ED3);
    SUB_001FA9();
    if (poppedEntry.value != 0x001ED3) return;
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x1F);
    if (a != 0x0C) {
        SUB_001F02();
        return;
    }
    a = myMapper->readCPU(0x0010);
    opPHA();
    a = myMapper->readCPU(0x0011);
    opPHA();
    a = myMapper->readCPU(0x0012);
    opPHA();
    a = myMapper->readCPU(0x0013);
    opPHA();
    myMapper->writeCPU(0x0011, 0xF8);
    pushAddress(0x001EEF);
    SUB_001F02();
    if (poppedEntry.value != 0x001EEF) return;
    opPLA();
    myMapper->writeCPU(0x0013, a);
    opPLA();
    myMapper->writeCPU(0x0012, a);
    opPLA();
    myMapper->writeCPU(0x0011, a);
    opPLA();
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0014, 0x00);
    SUB_001F02();
    return;
}

void game::SUB_001F02() {
    if (myMapper->readCPU(0x0067) == 0) {
        goto L_001F21;
    }
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x1F);
    if (a == 0x07) {
        a = 0x00;
        myMapper->writeCPU(0x0011, a);
        pushAddress(0x001F13);
        SUB_002980();
        if (poppedEntry.value != 0x001F13) return;
    }
    opCMP(a, 0x08);
    if (flgZ) {
        a = 0x00;
        myMapper->writeCPU(0x0011, a);
        pushAddress(0x001F1E);
        SUB_0029A4();
        if (poppedEntry.value != 0x001F1E) return;
    }
L_001F21:
    a = myMapper->readCPU(0x0013);
    setLoadFlag(a);
    if (flgN) {
        opAND(0x33);
    }
    else {
        if (myMapper->readCPU(0x0067) == 0) {
            goto L_001F36;
        }
        if (x == myMapper->readCPU(0x0079)) {
            myMapper->writeCPU(0x0013, 0x11);
        }
    L_001F36:
        if (!(myMapper->readCPU(0x00FC) & 0x80)) {
            a = myMapper->readCPU(0x0013);
        }
        else {
            a = myMapper->readCPU(0x0013);
            opLSR_A(4);
            y = a;
            a = myMapper->readCPU(0xA3D4 + y);
        }
    }
    opPHA();
    a = myMapper->readCPU(0x0012);
    setLoadFlag(a);
    if (!flgN) {
        goto L_001F5F;
    }
    opASL_M(0x0012, 2);
    a = myMapper->readCPU(0x001D);
    opLSR_A(3);
    opAND(0x03);
    opORA(myMapper->readCPU(0x0012));
    y = a;
    a = myMapper->readCPU(0xB1A6 + y);
L_001F5F:
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0307 + x, a);
    myMapper->writeCPU(0x0013, 0x00);
    opASL_M(0x0012, 1);
    opROL_M(0x0013, 1);
    opASL_M(0x0012, 1);
    opROL_M(0x0013, 1);
    opASL_M(0x0012, 1);
    opROL_M(0x0013, 1);
    a = 0x06;
    flgC = false;
    opADC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0012, a);
    a = 0xB2;
    opADC(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0013, a);
    y = 0x07;
    do {
        myMapper->writeCPU(0x0071 + y, myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgN);
    a = myMapper->readCPU(0x0014);
    opPHA();
    pushAddress(0x001F8E);
    SUB_001E18();
    if (poppedEntry.value != 0x001F8E) return;
    opPLA();
    y = a;
    opPLA();
    opPHA();
    opLSR_A(4);
    opORA(myMapper->readCPU(0x0702 + y));
    myMapper->writeCPU(0x0702 + y, a);
    opPLA();
    opAND(0x03);
    opORA(myMapper->readCPU(0x0706 + y));
    myMapper->writeCPU(0x0706 + y, a);
    popAddress();
}

void game::SUB_001FA9() {
    a = myMapper->readCPU(0x001F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x0058);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x9FBE + y));
    y = a;
    myMapper->writeCPU(0x0014, myMapper->readCPU(0x9FC2 + y));
    popAddress();
}

void game::SUB_00200A() {
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0305 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0306 + x);
    opSBC(myMapper->readCPU(0x004F));
    myMapper->writeCPU(0x0011, a);
    a = myMapper->readCPU(0x0050);
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0010, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0011));
    if (!flgZ) {
        goto L_00202E;
    }
    a = myMapper->readCPU(0x0010);
    if (a < 0xF8) {
        goto L_002030;
    }
L_00202E:
    a = 0xF8;
L_002030:
    myMapper->writeCPU(0x0011, a);
    a = myMapper->readCPU(0x0304 + x);
    myMapper->writeCPU(0x0010, a);
    popAddress();
}

void game::SUB_002038() {
    pushAddress(0x002038);
    SUB_0029D9();
    if (poppedEntry.value != 0x002038) return;
    x = 0x00;
L_00203D:
    y = 0x00;
    do {
        myMapper->writeCPU(0x0300 + x, myMapper->readCPU(0xA0F3 + y));
        opINY(1);
        opINX(1);
    } while (y < 0x08);
    if (x < 0x50) {
        goto L_002054;
    }
    myMapper->writeCPU(0x02FF + x, 0x65);
L_002054:
    if (x < 0x90) {
        goto L_00203D;
    }
    y = 0x00;
    x = 0x00;
    do {
        a = myMapper->readCPU(0x004D);
        flgC = false;
        opADC(myMapper->readCPU(0x0400 + y));
        myMapper->writeCPU(0x0304 + x, a);
        a = myMapper->readCPU(0x004E);
        flgC = false;
        opADC(myMapper->readCPU(0x0401 + y));
        myMapper->writeCPU(0x0305 + x, a);
        a = myMapper->readCPU(0x004F);
        opADC(myMapper->readCPU(0x0402 + y));
        myMapper->writeCPU(0x0306 + x, a);
        a = myMapper->readCPU(0x0403 + y);
        myMapper->writeCPU(0x0300 + x, a);
        pushAddress(0x00207C);
        SUB_002AF3();
        if (poppedEntry.value != 0x00207C) return;
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
    } while (a < 0x90);
    myMapper->writeCPU(0x0323, 0x48);
    myMapper->writeCPU(0x032B, 0x50);
    myMapper->writeCPU(0x0333, 0x58);
    myMapper->writeCPU(0x033B, 0x60);
    myMapper->writeCPU(0x0343, 0x68);
    myMapper->writeCPU(0x0066, 0x00);
    pushAddress(0x0020A5);
    SUB_00475F();
    if (poppedEntry.value != 0x0020A5) return;
    SUB_002F04();
    return;
}

void game::SUB_0020FB() {
    a = myMapper->readCPU(0x005F);
    opAND(0x08);
    if (!flgZ) {
    }
    else {
        pushAddress(0x002104);
        SUB_0023D8();
        if (poppedEntry.value != 0x002104) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x60);
        if (flgZ) {
            a = myMapper->readCPU(0x0012);
            opAND(0x03);
            if (!flgZ) {
                opAND(0x02);
                if (flgZ) {
                    goto L_00211A;
                }
                do {
                    goto L_002172;
                L_00211A:
                    a = myMapper->readCPU(0x0301 + x);
                    opAND(0x0F);
                    opCMP(a, 0x0F);
                    if (flgZ) {
                        goto L_002140;
                    }
                    pushAddress(0x002123);
                    SUB_00414D();
                    if (poppedEntry.value != 0x002123) return;
                    opINC(0x0066, 1);
                } while (myMapper->readCPU(0x0066) >= 0x03);
                a = myMapper->readCPU(0x0301 + x);
                opORA(0x0F);
                myMapper->writeCPU(0x0301 + x, a);
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x0302 + x, a);
                myMapper->writeCPU(0x0303 + x, a);
                if (flgZ) {
                    goto L_002193;
                }
            L_002140:
                if (!(myMapper->readCPU(0x00FC) & 0x80)) {
                    a = myMapper->readCPU(0x005E);
                    opAND(0xF0);
                    myMapper->writeCPU(0x0010, a);
                    a = myMapper->readCPU(0x00FD);
                    opAND(0xF0);
                    if (a == myMapper->readCPU(0x0010)) {
                        goto L_00215F;
                    }
                    opINC(0x0303 + x, 1);
                    a = myMapper->readCPU(0x0303 + x);
                    opAND(0x00);
                    if (!flgZ) {
                        goto L_00215F;
                    }
                }
                pushAddress(0x00215C);
                SUB_002278();
                if (poppedEntry.value != 0x00215C) return;
            L_00215F:
                a = myMapper->readCPU(0x00FD);
                opAND(0xF0);
                opORA(0x0F);
                myMapper->writeCPU(0x0301 + x, a);
                opINC(0x0302 + x, 1);
                if (myMapper->readCPU(0x0302 + x) < 0x60) {
                    goto L_00219A;
                }
            L_002172:
                pushAddress(0x002172);
                SUB_002E5E();
                if (poppedEntry.value != 0x002172) return;
                goto L_0021B2;
            }
        }
        a = myMapper->readCPU(0x004C);
        opAND(0x60);
        if (!flgZ) {
            SUB_00288E();
            return;
        }
        pushAddress(0x002181);
        SUB_0027B7();
        if (poppedEntry.value != 0x002181) return;
        y = 0x15;
        a = myMapper->readCPU(0x00FD);
        opAND(0xF0);
        if (!flgZ) {
            opORA(0x05);
            y = a;
        }
        myMapper->writeCPU(0x0301 + x, y);
    L_002193:
        if (!(myMapper->readCPU(0x0035) & 0x80)) {
            pushAddress(0x002197);
            SUB_00224F();
            if (poppedEntry.value != 0x002197) return;
        }
    L_00219A:
        if (myMapper->readCPU(0x00F4) == 0x03) {
            goto L_0021B2;
        }
        myMapper->writeCPU(0x0304 + x, myMapper->readCPU(0x004D));
        myMapper->writeCPU(0x0305 + x, myMapper->readCPU(0x004E));
        myMapper->writeCPU(0x0306 + x, myMapper->readCPU(0x004F));
        pushAddress(0x0021AF);
        SUB_0023C5();
        if (poppedEntry.value != 0x0021AF) return;
    }
L_0021B2:
    a = myMapper->readCPU(0x0301 + x);
    myMapper->writeCPU(0x005E, a);
    opLSR_A(4);
    y = a;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0xA1C6 + y));
    myMapper->writeCPU(0x0013, 0x31);
    popAddress();
}

void game::SUB_0021D6() {
    a = myMapper->readCPU(0x00F4);
    if (a != 0x03) {
        a = myMapper->readCPU(0x0301 + x);
        opASL_A(4);
        myMapper->writeCPU(0x0010, a);
        if (a == 0xF0) {
            myMapper->writeCPU(0x0010, 0x00);
            a = myMapper->readCPU(0x001D);
            opAND(0x0F);
            if (!flgZ) {
                goto L_00224E;
            }
        }
        a = myMapper->readCPU(0x001D);
        opAND(0x0F);
        opORA(myMapper->readCPU(0x0010));
        y = a;
        if (myMapper->readCPU(0xA298 + y) != 0) {
            myMapper->writeCPU(0x0010, myMapper->readCPU(0x0301 + x));
            opASL_M(0x0010, 1);
            if (flgC) {
                a = myMapper->readCPU(0x0304 + x);
                opCMP(a, 0xC6);
                if (!flgC) {
                    opADC(0x01);
                    myMapper->writeCPU(0x0304 + x, a);
                }
            }
            opASL_M(0x0010, 1);
            if (flgC) {
                a = myMapper->readCPU(0x0304 + x);
                opCMP(a, 0x13);
                if (flgC) {
                    opSBC(0x01);
                    myMapper->writeCPU(0x0304 + x, a);
                }
            }
            opASL_M(0x0010, 1);
            if (flgC) {
                a = myMapper->readCPU(0x0305 + x);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x0305 + x, a);
                a = myMapper->readCPU(0x0306 + x);
                opADC(0x00);
                myMapper->writeCPU(0x0306 + x, a);
            }
            opASL_M(0x0010, 1);
            if (!flgC) {
                goto L_00224E;
            }
            a = myMapper->readCPU(0x0305 + x);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU(0x0305 + x, a);
            a = myMapper->readCPU(0x0306 + x);
            opSBC(0x00);
            myMapper->writeCPU(0x0306 + x, a);
        }
    }
L_00224E:
    popAddress();
}

void game::SUB_00224F() {
    if (myMapper->readCPU(0x00F4) == 0x03) {
        SUB_002297();
        return;
    }
    a = myMapper->readCPU(0x0301 + x);
    opASL_A(4);
    myMapper->writeCPU(0x0010, a);
    if (a != 0xF0) {
        goto L_00226C;
    }
    myMapper->writeCPU(0x0010, 0x00);
    a = myMapper->readCPU(0x001D);
    opAND(0x0F);
    if (!flgZ) {
        SUB_002297();
        return;
    }
L_00226C:
    a = myMapper->readCPU(0x001D);
    opAND(0x0F);
    opORA(myMapper->readCPU(0x0010));
    y = a;
    if (myMapper->readCPU(0xA298 + y) == 0) {
        SUB_002297();
        return;
    }
    SUB_002278();
    return;
}

void game::SUB_002278() {
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0301 + x));
    opASL_M(0x0010, 1);
    if (flgC) {
        opINC(0x004D, 1);
    }
    opASL_M(0x0010, 1);
    if (flgC) {
        opDEC(0x004D, 1);
    }
    opASL_M(0x0010, 1);
    if (!flgC) {
        goto L_002290;
    }
    pushAddress(0x00228D);
    SUB_0036D7();
    if (poppedEntry.value != 0x00228D) return;
L_002290:
    opASL_M(0x0010, 1);
    if (!flgC) {
        SUB_002297();
        return;
    }
    pushAddress(0x002294);
    SUB_003703();
    if (poppedEntry.value != 0x002294) return;
    SUB_002297();
    return;
}

void game::SUB_002297() {
    popAddress();
}

void game::SUB_002318() {
    y = 0x00;
    do {
        a = y;
        opPHA();
        opLSR_A(1);
        x = a;
        myMapper->writeCPU(0x0017, myMapper->readCPU(0x0305 + x));
        myMapper->writeCPU(0x0018, myMapper->readCPU(0x0306 + x));
        a = myMapper->readCPU(0x0304 + x);
        myMapper->writeCPU(0x0019, a);
        opPLA();
        y = a;
        x = 0x48;
        do {
            pushAddress(0x002331);
            SUB_002348();
            if (poppedEntry.value != 0x002331) return;
            myMapper->writeCPU(0x0400 + y, myMapper->readCPU(0x001C));
            opINY(1);
        } while (x < 0x90);
        a = y;
        flgC = false;
        opADC(0x07);
        y = a;
    } while (a < 0x90);
    popAddress();
}

void game::SUB_002348() {
    myMapper->writeCPU(0x001C, 0x01);
    a = myMapper->readCPU(0x0019);
    flgC = true;
    opSBC(myMapper->readCPU(0x0304 + x));
    if (!flgC) {
        opEOR(0xFF);
    }
    if (a < 0x04) {
        a = myMapper->readCPU(0x0017);
        flgC = true;
        opSBC(myMapper->readCPU(0x0305 + x));
        myMapper->writeCPU(0x001A, a);
        a = myMapper->readCPU(0x0018);
        opSBC(myMapper->readCPU(0x0306 + x));
        myMapper->writeCPU(0x001B, a);
        if (!flgC) {
            opEOR(0xFF);
            myMapper->writeCPU(0x001B, a);
            a = myMapper->readCPU(0x001A);
            opEOR(0xFF);
            myMapper->writeCPU(0x001A, a);
        }
        if (myMapper->readCPU(0x001B) == 0) {
            a = myMapper->readCPU(0x001A);
            if (a < 0x05) {
                if (!(myMapper->readCPU(0x0033) & 0x80)) {
                    goto L_00238A;
                }
                a = myMapper->readCPU(0x0300 + x);
                if (a == 0x0D) {
                    goto L_002398;
                }
            L_00238A:
                a = myMapper->readCPU(0x0300 + x);
                if (a != 0x09) {
                    goto L_0023A2;
                }
                a = myMapper->readCPU(0x0302 + x);
                if (a != 0x01) {
                    goto L_0023A2;
                }
            L_002398:
                a = 0x02;
                setLoadFlag(a);
                myMapper->writeCPU(0x001C, a);
                if (!flgZ) {
                    goto L_0023A2;
                }
            }
        }
    }
    myMapper->writeCPU(0x001C, 0x00);
L_0023A2:
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    popAddress();
}

void game::SUB_0023A8() {
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0307 + x));
    a = 0x01;
    if (x >= 0x48) {
        a = 0x21;
    }
    myMapper->writeCPU(0x0013, a);
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x0F);
    if (a != 0x01) {
        goto L_0023C4;
    }
    myMapper->writeCPU(0x0013, 0x31);
L_0023C4:
    popAddress();
}

void game::SUB_0023C5() {
    a = myMapper->readCPU(0x0069);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0069, a);
    opAND(0x3F);
    if (!flgZ) {
        goto L_0023D3;
    }
    pushAddress(0x0023D0);
    SUB_004113();
    if (poppedEntry.value != 0x0023D0) return;
L_0023D3:
    popAddress();
}

void game::SUB_0023D8() {
    a = myMapper->readCPU(0x0058);
    opASL_A(1);
    y = a;
    x = 0x08;
    a = 0x00;
    do {
        opORA(myMapper->readCPU(0x0400 + y));
        opINY(1);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0012, a);
    x = myMapper->readCPU(0x0058);
    popAddress();
}

void game::SUB_0023EC() {
    pushAddress(0x0023EC);
    SUB_0023D8();
    if (poppedEntry.value != 0x0023EC) return;
    SUB_0023EF();
    return;
}

void game::SUB_0023EF() {
    a = myMapper->readCPU(0x004C);
    opAND(0x0C);
    if (flgZ) {
        a = myMapper->readCPU(0x005E);
        opAND(0x0F);
        if (a == 0x0F) {
            goto L_002404;
        }
        a = myMapper->readCPU(0x005E);
        flgC = false;
        opADC(0x01);
        if (!flgZ) {
            goto L_002406;
        }
    }
L_002404:
    a = myMapper->readCPU(0x005E);
L_002406:
    myMapper->writeCPU(0x0301 + x, a);
    if (myMapper->readCPU(0x0012) == 0) {
        SUB_002415();
        return;
    }
    a = myMapper->readCPU(0x0301 + x);
    opORA(0x0F);
    myMapper->writeCPU(0x0301 + x, a);
    SUB_002415();
    return;
}

void game::SUB_002415() {
    pushAddress(0x002415);
    SUB_0021D6();
    if (poppedEntry.value != 0x002415) return;
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    if (myMapper->readCPU(0x00F4) == 0) {
        if (x == 0x20) {
            goto L_00243F;
        }
        if (x != 0x40) {
            a = myMapper->readCPU(0x004C);
            opAND(0x0C);
            if (!flgZ) {
                opAND(0x08);
                if (flgZ) {
                    if (x != 0x18) {
                        goto L_00243F;
                    }
                }
                a = y;
                flgC = false;
                opADC(0x0A);
                y = a;
            }
        }
    }
L_00243F:
    a = myMapper->readCPU(0xA456 + y);
    myMapper->writeCPU(0x0012, a);
    if (a == 0x91) {
        if (myMapper->readCPU(0x0304 + x) < myMapper->readCPU(0x004D)) {
            goto L_002451;
        }
        opINC(0x0012, 1);
    }
L_002451:
    myMapper->writeCPU(0x0013, 0x01);
    popAddress();
}

void game::SUB_00246B() {
    a = myMapper->readCPU(0x0302 + x);
    opAND(0x03);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0xA47F + y));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0xA480 + y));
    indirectJump(myMapper->readCPU(0x0010) + (myMapper->readCPU((0x0010 + 1) & 0x00ff) << 8));
}

void game::SUB_002487() {
    a = myMapper->readCPU(0x001D);
    opAND(0x0F);
    if (flgZ) {
        pushAddress(0x00248D);
        SUB_0040E7();
        if (poppedEntry.value != 0x00248D) return;
    }
    a = myMapper->readCPU(0x004D);
    flgC = true;
    opSBC(myMapper->readCPU(0x0304 + x));
    if (flgC) {
        if (a >= 0x24) {
            goto L_0024CA;
        }
    }
    pushAddress(0x00249C);
    SUB_0048AE();
    if (poppedEntry.value != 0x00249C) return;
    if (a == 0x21) {
        myMapper->writeCPU(0x0395, myMapper->readCPU(0x004E));
        myMapper->writeCPU(0x0396, myMapper->readCPU(0x004F));
        a = 0x81;
        myMapper->writeCPU(0x0035, a);
    }
    opAND(0x01);
    if (flgZ) {
        y = 0x6F;
        a = myMapper->readCPU(0x001D);
        opAND(0x20);
        if (flgZ) {
            goto L_0024BF;
        }
        y = 0x71;
    L_0024BF:
        myMapper->writeCPU(0x0307, y);
        myMapper->writeCPU(0x0301 + x, 0x47);
        SUB_002415();
        return;
    }
L_0024CA:
    opINC(0x0302 + x, 1);
    myMapper->writeCPU(0x0022, 0x80);
    myMapper->writeCPU(0x0303 + x, 0xF5);
    a = myMapper->readCPU(0x00FD);
    opAND(0xFE);
    myMapper->writeCPU(0x00FD, a);
    a = myMapper->readCPU(0x0050);
    flgC = true;
    opSBC(0x18);
    myMapper->writeCPU(0x07C4, a);
    a = myMapper->readCPU(0x004D);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x07C7, a);
    myMapper->writeCPU(0x07C6, 0x01);
    myMapper->writeCPU(0x07C5, 0xBE);
    myMapper->writeCPU(0x0307, 0x64);
    myMapper->writeCPU(0x0337, 0x6E);
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0307 + x));
    myMapper->writeCPU(0x0013, 0x01);
    myMapper->writeCPU(0x0082, 0xB0);
    SUB_004177();
    return;
}

void game::SUB_002510() {
    opDEC(0x0303 + x, 1);
    if (!flgZ) {
        myMapper->writeCPU(0x0301 + x, 0x15);
        pushAddress(0x00251A);
        SUB_002415();
        if (poppedEntry.value != 0x00251A) return;
        pushAddress(0x00251D);
        SUB_002534();
        if (poppedEntry.value != 0x00251D) return;
        a = 0x04;
        opBIT(myMapper->readCPU(0x0035));
        if (flgN) {
            goto L_002528;
        }
        a = 0x0C;
    L_002528:
        myMapper->writeCPU(0x004C, a);
        popAddress();
        return;
    }
    opINC(0x0302 + x, 1);
    myMapper->writeCPU(0x0303 + x, 0x7F);
    popAddress();
}

void game::SUB_002534() {
    a = myMapper->readCPU(0x07C4);
    flgC = false;
    opADC(0x04);
    opCMP(a, myMapper->readCPU(0x0050));
    if (!flgZ) {
        if (flgC) {
            goto L_002545;
        }
        opSBC(0x02);
        myMapper->writeCPU(0x07C4, a);
    L_002545:
        opPLA();
        opPLA();
        popAddress();
        return;
    }
    myMapper->writeCPU(0x07C4, 0xF0);
    pushAddress(0x00254D);
    SUB_002905();
    if (poppedEntry.value != 0x00254D) return;
    myMapper->writeCPU(0x074D, 0x76);
    pushAddress(0x002555);
    SUB_004140();
    if (poppedEntry.value != 0x002555) return;
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0300 + y);
        opAND(0x0F);
        myMapper->writeCPU(0x0300 + y, a);
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    } while (a < 0x90);
    myMapper->writeCPU(0x0067, a);
    y = 0x20;
    do {
        a = myMapper->readCPU(0x0305 + y);
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(0x0305 + y, a);
        a = myMapper->readCPU(0x0306 + y);
        opSBC(0x00);
        myMapper->writeCPU(0x0306 + y, a);
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    } while (a < 0x48);
    do {
        a = myMapper->readCPU(0x0305 + y);
        flgC = false;
        opADC(0x05);
        myMapper->writeCPU(0x0305 + y, a);
        a = myMapper->readCPU(0x0306 + y);
        opADC(0x00);
        myMapper->writeCPU(0x0306 + y, a);
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    } while (a < 0x70);
    popAddress();
}

void game::SUB_0025A4() {
    pushAddress(0x0025A4);
    SUB_0023D8();
    if (poppedEntry.value != 0x0025A4) return;
    if (myMapper->readCPU(0x0012) != 0) {
        a = myMapper->readCPU(0x004C);
        opAND(0x04);
        if (flgZ) {
            myMapper->writeCPU(0x0300 + x, 0x03);
            SUB_0023EF();
            return;
        }
    }
    opDEC(0x0303 + x, 1);
    if (flgN) {
        myMapper->writeCPU(0x0303 + x, 0x7F);
    }
    y = 0x85;
    a = myMapper->readCPU(0x0303 + x);
    opAND(0x40);
    if (!flgZ) {
        goto L_0025CE;
    }
    y = 0x45;
L_0025CE:
    myMapper->writeCPU(0x0301 + x, y);
    SUB_002415();
    return;
}

void game::SUB_0025D5() {
    a = myMapper->readCPU(0x004C);
    opAND(0xC0);
    if (a == 0xC0) {
        pushAddress(0x0025DD);
        SUB_002C3E();
        if (poppedEntry.value != 0x0025DD) return;
        if (flgC) {
            pushAddress(0x0025E2);
            SUB_00416D();
            if (poppedEntry.value != 0x0025E2) return;
            y = 0x00;
            do {
                a = myMapper->readCPU(0x0300 + y);
                opORA(0x80);
                myMapper->writeCPU(0x0300 + y, a);
                a = y;
                flgC = false;
                opADC(0x08);
                y = a;
            } while (a < 0x90);
            myMapper->writeCPU(0x0300 + x, 0x0C);
            myMapper->writeCPU(0x0302 + x, 0x60);
            y = 0x42;
            a = myMapper->readCPU(0x0301 + x);
            setLoadFlag(a);
            if (flgN) {
                goto L_00260B;
            }
            y = 0x44;
        L_00260B:
            opPLA();
            opPLA();
            a = y;
            SUB_002779();
            return;
        }
    }
    popAddress();
}

void game::SUB_002612() {
    pushAddress(0x002612);
    SUB_0025D5();
    if (poppedEntry.value != 0x002612) return;
    myMapper->writeCPU(0x0013, 0x00);
    a = myMapper->readCPU(0x0304 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x004D));
    myMapper->writeCPU(0x0010, a);
    a = 0x00;
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0x68);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0011);
    opADC(0x00);
    myMapper->writeCPU(0x0011, a);
    if (flgZ) {
        goto L_002648;
    }
    if (flgN) {
        goto L_002642;
    }
    do {
        a = 0x40;
        setLoadFlag(a);
        myMapper->writeCPU(0x0013, a);
        if (!flgZ) {
            goto L_002652;
        }
        do {
        L_002642:
            a = 0x80;
            setLoadFlag(a);
            myMapper->writeCPU(0x0013, a);
            if (!flgZ) {
                goto L_002652;
            }
        L_002648:
            a = myMapper->readCPU(0x0012);
        } while (a < 0x08);
    } while (a >= 0xC8);
L_002652:
    a = myMapper->readCPU(0x0305 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0306 + x);
    opSBC(myMapper->readCPU(0x004F));
    myMapper->writeCPU(0x0011, a);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0xB0);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0011);
    opADC(0x00);
    myMapper->writeCPU(0x0011, a);
    if (flgZ) {
        goto L_002686;
    }
    if (flgN) {
        goto L_00267E;
    }
    do {
        a = myMapper->readCPU(0x0013);
        opORA(0x10);
        myMapper->writeCPU(0x0013, a);
        if (!flgZ) {
            goto L_002690;
        }
        do {
        L_00267E:
            a = myMapper->readCPU(0x0013);
            opORA(0x20);
            myMapper->writeCPU(0x0013, a);
            if (!flgZ) {
                goto L_002690;
            }
        L_002686:
            a = myMapper->readCPU(0x0010);
        } while (a < 0x08);
    } while (a >= 0xE8);
L_002690:
    a = myMapper->readCPU(0x0013);
    opAND(0xF0);
    if (!flgZ) {
        a = myMapper->readCPU(0x0013);
        opORA(0x03);
    }
    else {
        myMapper->writeCPU(0x0011, myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x0012));
        pushAddress(0x0026A5);
        SUB_002780();
        if (poppedEntry.value != 0x0026A5) return;
        a = 0x3D;
        flgC = false;
        opADC(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0012, a);
        a = 0xB9;
        opADC(myMapper->readCPU(0x0011));
        myMapper->writeCPU(0x0013, a);
        y = 0x00;
        y = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        a = myMapper->readCPU(0x0014);
        opAND(0x08);
        if (flgZ) {
            a = y;
            opLSR_A(4);
            y = a;
        }
        a = y;
        opAND(0x0F);
        if (a == 0x0F) {
            a = myMapper->readCPU(0x0301 + x);
            opAND(0x0F);
        }
        myMapper->writeCPU(0x0015, a);
        a = 0xBD;
        flgC = false;
        opADC(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0012, a);
        a = 0xBC;
        opADC(myMapper->readCPU(0x0011));
        myMapper->writeCPU(0x0013, a);
        y = 0x00;
        y = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        a = myMapper->readCPU(0x0014);
        opAND(0x08);
        if (!flgZ) {
            a = y;
            opASL_A(4);
            y = a;
        }
        a = y;
        opAND(0xF0);
        if (flgZ) {
            a = myMapper->readCPU(0x0301 + x);
            opAND(0xF0);
        }
        opORA(myMapper->readCPU(0x0015));
    }
    myMapper->writeCPU(0x0015, a);
    opORA(myMapper->readCPU(0x0301 + x));
    y = a;
    opAND(0x30);
    if (a == 0x30) {
        goto L_002711;
    }
    a = y;
    opAND(0xC0);
    if (a != 0xC0) {
        SUB_002721();
        return;
    }
L_002711:
    myMapper->writeCPU(0x0302 + x, myMapper->readCPU(0x0300 + x));
    myMapper->writeCPU(0x0300 + x, 0x0B);
    myMapper->writeCPU(0x0303 + x, 0x0F);
    SUB_002721();
    return;
}

void game::SUB_002721() {
    myMapper->writeCPU(0x0301 + x, myMapper->readCPU(0x0015));
    pushAddress(0x002726);
    SUB_002DE2();
    if (poppedEntry.value != 0x002726) return;
    pushAddress(0x002729);
    SUB_002798();
    if (poppedEntry.value != 0x002729) return;
    if (myMapper->readCPU(0x0012) != 0) {
        a = myMapper->readCPU(0x0301 + x);
        opORA(0x0F);
        myMapper->writeCPU(0x0301 + x, a);
    }
    if (myMapper->readCPU(0x0600 + x) == 0x0F) {
        a = myMapper->readCPU(0x0301 + x);
        opAND(0x0F);
        if (a != 0x0F) {
            a = myMapper->readCPU(0x0301 + x);
            opAND(0xC0);
            if (!flgZ) {
                goto L_002757;
            }
            a = myMapper->readCPU(0x0301 + x);
            opORA(0x40);
            myMapper->writeCPU(0x0301 + x, a);
        L_002757:
            a = myMapper->readCPU(0x0301 + x);
            opEOR(0xC0);
            opAND(0xF0);
            opORA(0x02);
            myMapper->writeCPU(0x0301 + x, a);
        }
    }
    a = myMapper->readCPU(0x0301 + x);
    opAND(0x0F);
    myMapper->writeCPU(0x0600 + x, a);
    pushAddress(0x00276B);
    SUB_0030AD();
    if (poppedEntry.value != 0x00276B) return;
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    a = myMapper->readCPU(0xA456 + y);
    SUB_002779();
    return;
}

void game::SUB_002779() {
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0013, 0x21);
    popAddress();
}

void game::SUB_002780() {
    myMapper->writeCPU(0x0014, myMapper->readCPU(0x0010));
    a = myMapper->readCPU(0x0011);
    opLSR_A(4);
    opROR_M(0x0010, 1);
    opLSR_A(1);
    opROR_M(0x0010, 1);
    opLSR_A(1);
    opROR_M(0x0010, 1);
    opLSR_A(1);
    opROR_M(0x0010, 1);
    myMapper->writeCPU(0x0011, a);
    popAddress();
}

void game::SUB_002798() {
    a = myMapper->readCPU(0x0058);
    opLSR_A(3);
    flgC = true;
    opSBC(0x09);
    y = a;
    x = 0x08;
    a = 0x00;
    do {
        opORA(myMapper->readCPU(0x0400 + y));
        opPHA();
        a = y;
        flgC = false;
        opADC(0x10);
        y = a;
        opPLA();
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0012, a);
    x = myMapper->readCPU(0x0058);
    popAddress();
}

void game::SUB_0027B7() {
    if (myMapper->readCPU(0x00F4) != 0) {
        goto L_0027CB;
    }
    a = myMapper->readCPU(0x004C);
    opAND(0x0C);
    if (!flgZ) {
        opLSR_A(2);
        opAND(myMapper->readCPU(0x00FD));
        opLSR_A(1);
        if (flgC) {
            goto L_0027CC;
        }
        opLSR_A(1);
        if (flgC) {
            goto L_0027D2;
        }
    }
L_0027CB:
    popAddress();
    return;
L_0027CC:
    a = 0x10;
    setLoadFlag(a);
    myMapper->writeCPU(0x005D, a);
    if (flgZ) {
    L_0027D2:
        a = myMapper->readCPU(0x0301 + x);
        opAND(0xC0);
        if (!flgZ) {
            goto L_0027DB;
        }
        a = 0x80;
    L_0027DB:
        myMapper->writeCPU(0x005D, a);
    }
    a = 0x83;
    myMapper->writeCPU(0x0300, a);
    myMapper->writeCPU(0x0308, a);
    myMapper->writeCPU(0x0310, a);
    myMapper->writeCPU(0x0300 + x, 0x02);
    myMapper->writeCPU(0x0302 + x, 0x0F);
    popAddress();
}

void game::SUB_0027F3() {
    opDEC(0x0302 + x, 1);
    if (flgN) {
        goto L_002824;
    }
    while (true) {
        if (!(myMapper->readCPU(0x0070) & 0x80)) {
            goto L_002800;
        }
        do {
            y = 0x06;
            setLoadFlag(y);
            if (!flgZ) {
                goto L_002814;
            }
        L_002800:
            a = myMapper->readCPU(0x0035);
            setLoadFlag(a);
        } while (flgN);
        opBIT(myMapper->readCPU(0x005D));
        if (!flgN) {
            if (flgV) {
                goto L_002812;
            }
            y = 0x00;
            setLoadFlag(y);
            if (flgZ) {
                goto L_002814;
            }
        }
        y = 0x02;
        setLoadFlag(y);
        if (flgZ) {
        L_002812:
            y = 0x04;
        }
    L_002814:
        if (myMapper->readCPU(0x0302 + x) & 0x80) {
            opINY(1);
        }
        myMapper->writeCPU(0x0012, myMapper->readCPU(0xA886 + y));
        myMapper->writeCPU(0x0013, 0x31);
        popAddress();
        return;
    L_002824:
        opBIT(myMapper->readCPU(0x005D));
        if (!flgN) {
            if (flgV) {
                goto L_002866;
            }
            myMapper->writeCPU(0x005A, myMapper->readCPU(0x031C));
            myMapper->writeCPU(0x005B, myMapper->readCPU(0x031D));
            myMapper->writeCPU(0x005C, myMapper->readCPU(0x031E));
            myMapper->writeCPU(0x004C, 0x20);
            if (myMapper->readCPU(0x0070) & 0x80) {
                goto L_00287E;
            }
            if (myMapper->readCPU(0x0035) & 0x80) {
                goto L_00287E;
            }
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x0318, a);
            if (!flgZ) {
                goto L_00287E;
            }
        }
        myMapper->writeCPU(0x005A, myMapper->readCPU(0x030C));
        myMapper->writeCPU(0x005B, myMapper->readCPU(0x030D));
        myMapper->writeCPU(0x005C, myMapper->readCPU(0x030E));
        myMapper->writeCPU(0x004C, 0x24);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0308, a);
        if (!flgZ) {
            goto L_00287E;
        }
    L_002866:
        myMapper->writeCPU(0x005A, myMapper->readCPU(0x0314));
        myMapper->writeCPU(0x005B, myMapper->readCPU(0x0315));
        myMapper->writeCPU(0x005C, myMapper->readCPU(0x0316));
        myMapper->writeCPU(0x004C, 0x24);
        myMapper->writeCPU(0x0310, 0x01);
    L_00287E:
        myMapper->writeCPU(0x0300 + x, 0x83);
    }
    SUB_00288E();
    return;
}

void game::SUB_00288E() {
    pushAddress(0x00288E);
    SUB_0028AA();
    if (poppedEntry.value != 0x00288E) return;
    a = myMapper->readCPU(0x0307 + x);
    if (x == 0x18) {
        y = 0x91;
        if (myMapper->readCPU(0x0304 + x) < myMapper->readCPU(0x004D)) {
            goto L_0028A2;
        }
        opINY(1);
    L_0028A2:
        a = y;
    }
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0013, 0x31);
    popAddress();
}

void game::SUB_0028AA() {
    a = myMapper->readCPU(0x004D);
    flgC = true;
    opSBC(myMapper->readCPU(0x0304 + x));
    if (!flgC) {
        opEOR(0xFF);
    }
    opCMP(a, 0x08);
    if (!flgC) {
        a = myMapper->readCPU(0x0305 + x);
        opADC(0x03);
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x0306 + x);
        opADC(0x00);
        myMapper->writeCPU(0x0011, a);
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(myMapper->readCPU(0x004E));
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x0011);
        opSBC(myMapper->readCPU(0x004F));
        if (flgC) {
            a = myMapper->readCPU(0x0010);
            if (a < 0x07) {
                a = myMapper->readCPU(0x004C);
                opAND(0x1C);
                myMapper->writeCPU(0x004C, a);
                y = 0x00;
                do {
                    a = myMapper->readCPU(0x0300 + y);
                    opAND(0x0F);
                    myMapper->writeCPU(0x0300 + y, a);
                    a = y;
                    flgC = false;
                    opADC(0x08);
                    y = a;
                    opCMP(a, 0x28);
                } while (!flgC);
                myMapper->writeCPU(0x004D, myMapper->readCPU(0x0304 + x));
                myMapper->writeCPU(0x0069, 0x00);
                a = myMapper->readCPU(0x004C);
                opAND(0x0C);
                if (!flgZ) {
                    goto L_002904;
                }
                pushAddress(0x002901);
                SUB_00416D();
                if (poppedEntry.value != 0x002901) return;
            }
        }
    }
L_002904:
    popAddress();
}

void game::SUB_002905() {
    if (myMapper->readCPU(0x0070) & 0x80) {
        goto L_00290D;
    }
    if (!(myMapper->readCPU(0x0035) & 0x80)) {
        goto L_002933;
    }
L_00290D:
    pushAddress(0x00290D);
    SUB_002F21();
    if (poppedEntry.value != 0x00290D) return;
    myMapper->writeCPU(0x004C, 0x04);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x68);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0013, a);
    if (!flgZ) {
        goto L_002929;
    }
    if (myMapper->readCPU(0x0012) < 0xA8) {
        goto L_002933;
    }
L_002929:
    myMapper->writeCPU(0x031D, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x031E, myMapper->readCPU(0x0013));
L_002933:
    popAddress();
}

void game::SUB_002934() {
    a = myMapper->readCPU(0x0305 + x);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0305 + x, a);
    a = myMapper->readCPU(0x0306 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x0306 + x, a);
    popAddress();
}

void game::SUB_002946() {
    opINC(0x0305 + x, 1);
    if (!flgZ) {
        goto L_00294E;
    }
    opINC(0x0306 + x, 1);
L_00294E:
    popAddress();
}

void game::SUB_00294F() {
    y = myMapper->readCPU(0x0303 + x);
    a = myMapper->readCPU(0x001D);
    opAND(0x1F);
    if (flgZ) {
        pushAddress(0x002959);
        SUB_000F4A();
        if (poppedEntry.value != 0x002959) return;
        opAND(0x02);
        if (!flgZ) {
            goto L_00296D;
        }
        pushAddress(0x002960);
        SUB_002934();
        if (poppedEntry.value != 0x002960) return;
        x = y;
        pushAddress(0x002965);
        SUB_002934();
        if (poppedEntry.value != 0x002965) return;
        x = myMapper->readCPU(0x0058);
        goto L_002977;
    L_00296D:
        pushAddress(0x00296D);
        SUB_002946();
        if (poppedEntry.value != 0x00296D) return;
        x = y;
        pushAddress(0x002972);
        SUB_002946();
        if (poppedEntry.value != 0x002972) return;
        x = myMapper->readCPU(0x0058);
    }
L_002977:
    myMapper->writeCPU(0x0011, 0x00);
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    opAND(0x08);
    SUB_002980();
    return;
}

void game::SUB_002980() {
    myMapper->writeCPU(0x0010, a);
    a = 0xA8;
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0012, a);
    a = 0xA9;
    opADC(myMapper->readCPU(0x0011));
    myMapper->writeCPU(0x0013, a);
    pushAddress(0x00298F);
    SUB_00200A();
    if (poppedEntry.value != 0x00298F) return;
    pushAddress(0x002992);
    SUB_001FA9();
    if (poppedEntry.value != 0x002992) return;
    pushAddress(0x002995);
    SUB_001E04();
    if (poppedEntry.value != 0x002995) return;
    opPLA();
    opPLA();
    popAddress();
}

void game::SUB_00299B() {
    myMapper->writeCPU(0x0011, 0x00);
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    opAND(0x08);
    SUB_0029A4();
    return;
}

void game::SUB_0029A4() {
    opORA(0x10);
    if (!flgZ) {
        SUB_002980();
        return;
    }
    flgD = true;
    s = x;
    pushAddress(0x0029AA);
    flgB = true;
    pushStatus();
    SUB_0004FF();
    popStatus();
    flgB = false;
    popAddress();
}

void game::SUB_0029C8() {
    a = 0x03;
    myMapper->writeCPU(0x0320, a);
    myMapper->writeCPU(0x0340, a);
    a = 0x06;
    myMapper->writeCPU(0x0348, a);
    myMapper->writeCPU(0x0368, a);
    popAddress();
}

void game::SUB_0029D9() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x18);
    myMapper->writeCPU(0x0056, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0057, a);
    y = 0x47;
    do {
        myMapper->writeCPU(0x0400 + y, myMapper->readCPU(0xA0AB + y));
        opDEY(1);
    } while (!flgN);
    if (myMapper->readCPU(0x0070) & 0x80) {
        myMapper->writeCPU(0x004E, 0xFF);
        myMapper->writeCPU(0x0050, 0x97);
        myMapper->writeCPU(0x0011, 0x0F);
        y = 0x00;
        x = 0x18;
        setLoadFlag(x);
        if (!flgZ) {
            goto L_002A7B;
        }
    }
    a = 0x00;
    myMapper->writeCPU(0x0011, a);
    myMapper->writeCPU(0x0013, a);
    do {
        pushAddress(0x002A0D);
        SUB_000F4A();
        if (poppedEntry.value != 0x002A0D) return;
    } while (a >= 0xB6);
    if (a >= 0x50) {
        opCMP(a, 0xAA);
        if (!flgC) {
            goto L_002A36;
        }
        opSBC(0xAA);
        myMapper->writeCPU(0x0010, a);
        y = 0x0A;
        x = 0x23;
        a = 0x03;
        setLoadFlag(a);
        myMapper->writeCPU(0x0012, a);
        if (!flgZ) {
            goto L_002A43;
        }
    }
    myMapper->writeCPU(0x0010, a);
    y = 0x00;
    x = 0x00;
    a = 0x14;
    setLoadFlag(a);
    myMapper->writeCPU(0x0012, a);
    if (flgZ) {
    L_002A36:
        flgC = true;
        opSBC(0x50);
        myMapper->writeCPU(0x0010, a);
        y = 0x04;
        x = 0x14;
        myMapper->writeCPU(0x0012, 0x0F);
    }
L_002A43:
    myMapper->writeCPU(0x0014, 0x00);
    do {
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(myMapper->readCPU(0x0012));
        if (!flgC) {
            goto L_002A54;
        }
        myMapper->writeCPU(0x0010, a);
        opINC(0x0014, 1);
    } while (!flgZ);
L_002A54:
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x0014));
    y = a;
    myMapper->writeCPU(0x0011, myMapper->readCPU(0xAAC1 + y));
    a = x;
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    x = a;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0xB606 + x));
    y = 0x00;
    x = 0x00;
    do {
        opLSR_M(0x0010, 1);
        if (!flgC) {
            goto L_002A73;
        }
        pushAddress(0x002A70);
        SUB_002ACF();
        if (poppedEntry.value != 0x002A70) return;
    L_002A73:
        opINX(4);
    } while (x < 0x18);
    do {
    L_002A7B:
        opLSR_M(0x0011, 1);
        if (!flgC) {
            goto L_002A82;
        }
        pushAddress(0x002A7F);
        SUB_002ACF();
        if (poppedEntry.value != 0x002A7F) return;
    L_002A82:
        opINX(4);
    } while (x < 0x28);
    if (myMapper->readCPU(0x0070) & 0x80) {
        goto L_002A98;
    }
    a = myMapper->readCPU(0x001F);
    opAND(0x0C);
    y = a;
    myMapper->writeCPU(0x043B + y, 0x85);
L_002A98:
    popAddress();
}

void game::SUB_002ACF() {
    pushAddress(0x002ACF);
    SUB_000F4A();
    if (poppedEntry.value != 0x002ACF) return;
    opLSR_A(1);
    if (!flgC) {
        goto L_002ADE;
    }
    a = myMapper->readCPU(0xAA99 + x);
    opSBC(myMapper->readCPU(0xAA9C + x));
    goto L_002AE4;
L_002ADE:
    a = myMapper->readCPU(0xAA99 + x);
    opADC(myMapper->readCPU(0xAA9C + x));
L_002AE4:
    myMapper->writeCPU(0x0438 + y, a);
    myMapper->writeCPU(0x0439 + y, myMapper->readCPU(0xAA9A + x));
    a = myMapper->readCPU(0xAA9B + x);
    myMapper->writeCPU(0x043A + y, a);
    SUB_002AF3();
    return;
}

void game::SUB_002AF3() {
    opINY(4);
    popAddress();
}

void game::SUB_002AF8() {
    opDEC(0x0303 + x, 1);
    if (!flgN) {
        goto L_002B03;
    }
    myMapper->writeCPU(0x0300 + x, myMapper->readCPU(0x0302 + x));
L_002B03:
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0xAB15 + y));
    myMapper->writeCPU(0x0013, 0x21);
    popAddress();
}

void game::SUB_002B20() {
    pushAddress(0x002B20);
    SUB_0025D5();
    if (poppedEntry.value != 0x002B20) return;
    a = myMapper->readCPU(0x004C);
    opAND(0x0C);
    if (flgZ) {
        myMapper->writeCPU(0x0300 + x, 0x06);
    }
    myMapper->writeCPU(0x0013, 0x00);
    y = 0x18;
    a = myMapper->readCPU(0x0304 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0304 + y));
    myMapper->writeCPU(0x0010, a);
    a = 0x00;
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0x68);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0011);
    opADC(0x00);
    myMapper->writeCPU(0x0011, a);
    if (flgZ) {
        goto L_002B64;
    }
    if (flgN) {
        goto L_002B5E;
    }
    do {
        a = 0x40;
        setLoadFlag(a);
        myMapper->writeCPU(0x0013, a);
        if (!flgZ) {
            goto L_002B6E;
        }
        do {
        L_002B5E:
            a = 0x80;
            setLoadFlag(a);
            myMapper->writeCPU(0x0013, a);
            if (!flgZ) {
                goto L_002B6E;
            }
        L_002B64:
            a = myMapper->readCPU(0x0012);
        } while (a < 0x08);
    } while (a >= 0xC8);
L_002B6E:
    a = myMapper->readCPU(0x0305 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0305 + y));
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0306 + x);
    opSBC(myMapper->readCPU(0x0306 + y));
    myMapper->writeCPU(0x0011, a);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0x90);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0011);
    opADC(0x00);
    myMapper->writeCPU(0x0011, a);
    if (flgZ) {
        goto L_002BA4;
    }
    if (flgN) {
        goto L_002B9C;
    }
    do {
        a = myMapper->readCPU(0x0013);
        opORA(0x10);
        myMapper->writeCPU(0x0013, a);
        if (!flgZ) {
            goto L_002BAE;
        }
        do {
        L_002B9C:
            a = myMapper->readCPU(0x0013);
            opORA(0x20);
            myMapper->writeCPU(0x0013, a);
            if (!flgZ) {
                goto L_002BAE;
            }
        L_002BA4:
            a = myMapper->readCPU(0x0010);
        } while (a < 0x08);
    } while (a >= 0xE8);
L_002BAE:
    a = myMapper->readCPU(0x0013);
    opAND(0xF0);
    if (!flgZ) {
        a = myMapper->readCPU(0x0013);
        opORA(0x03);
    }
    else {
        myMapper->writeCPU(0x0011, myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x0012));
        pushAddress(0x002BC3);
        SUB_002780();
        if (poppedEntry.value != 0x002BC3) return;
        a = 0x0D;
        flgC = false;
        opADC(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0012, a);
        a = 0xBB;
        opADC(myMapper->readCPU(0x0011));
        myMapper->writeCPU(0x0013, a);
        y = 0x00;
        y = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        a = myMapper->readCPU(0x0014);
        opAND(0x08);
        if (!flgZ) {
            a = y;
            opASL_A(4);
            y = a;
        }
        a = y;
        opAND(0xF0);
        if (flgZ) {
            a = myMapper->readCPU(0x0301 + x);
            opAND(0xF0);
        }
        opORA(0x03);
    }
    myMapper->writeCPU(0x0015, a);
    opORA(myMapper->readCPU(0x0301 + x));
    myMapper->writeCPU(0x0010, a);
    opAND(0x30);
    if (a != 0x30) {
        a = myMapper->readCPU(0x0010);
        opAND(0xC0);
        if (a != 0xC0) {
            goto L_002C15;
        }
    }
    myMapper->writeCPU(0x0302 + x, myMapper->readCPU(0x0300 + x));
    myMapper->writeCPU(0x0300 + x, 0x0B);
    myMapper->writeCPU(0x0303 + x, 0x0F);
L_002C15:
    myMapper->writeCPU(0x0301 + x, myMapper->readCPU(0x0015));
    pushAddress(0x002C1A);
    SUB_002798();
    if (poppedEntry.value != 0x002C1A) return;
    if (myMapper->readCPU(0x0012) == 0) {
        goto L_002C29;
    }
    a = myMapper->readCPU(0x0301 + x);
    opORA(0x0F);
    myMapper->writeCPU(0x0301 + x, a);
L_002C29:
    pushAddress(0x002C29);
    SUB_0030AD();
    if (poppedEntry.value != 0x002C29) return;
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0xA456 + y));
    myMapper->writeCPU(0x0013, 0x21);
    popAddress();
}

void game::SUB_002C3E() {
    if (myMapper->readCPU(0x0070) & 0x80) {
        goto L_002C79;
    }
    if (!(myMapper->readCPU(0x0035) & 0x80)) {
        a = myMapper->readCPU(0x004D);
        flgC = true;
        opSBC(myMapper->readCPU(0x0304 + x));
        if (!flgC) {
            opEOR(0xFF);
            opADC(0x01);
        }
        if (a < 0x02) {
            a = myMapper->readCPU(0x0305 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0x004E));
            myMapper->writeCPU(0x0010, a);
            a = myMapper->readCPU(0x0306 + x);
            opSBC(myMapper->readCPU(0x004F));
            if (flgZ) {
                if (!flgC) {
                    goto L_002C79;
                }
                a = myMapper->readCPU(0x0010);
                if (a >= 0x00) {
                    if (a >= 0x07) {
                        goto L_002C79;
                    }
                    a = myMapper->readCPU(0x004C);
                    opAND(0x1C);
                    myMapper->writeCPU(0x004C, a);
                    flgC = true;
                    popAddress();
                    return;
                }
            }
        }
    }
L_002C79:
    flgC = false;
    popAddress();
}

void game::SUB_002C7B() {
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    if (flgC) {
        a = myMapper->readCPU(0x0302 + x);
        setLoadFlag(a);
        if (!flgN) {
            goto L_002C8F;
        }
        a = myMapper->readCPU(0x005F);
        opORA(0x08);
        opAND(0xDF);
        myMapper->writeCPU(0x005F, a);
        if (!flgZ) {
            goto L_002CA3;
        }
    L_002C8F:
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0302 + x, a);
        opCMP(a, 0x48);
        if (flgZ) {
            goto L_002CE1;
        }
        if (!flgC) {
            goto L_002CE6;
        }
        if (a == 0x4E) {
            goto L_002CAD;
        }
        if (a == 0x58) {
            goto L_002CD0;
        }
    }
    do {
        do {
            do {
                while (true) {
                L_002CA3:
                    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0307 + x));
                    myMapper->writeCPU(0x0013, 0x21);
                    popAddress();
                    return;
                L_002CAD:
                    a = myMapper->readCPU(0x0305 + x);
                    flgC = false;
                    opADC(0x04);
                    myMapper->writeCPU(0x0305 + x, a);
                    a = myMapper->readCPU(0x0306 + x);
                    opADC(0x00);
                    myMapper->writeCPU(0x0306 + x, a);
                    y = 0x46;
                    if (myMapper->readCPU(0x0307 + x) == 0x43) {
                        goto L_002CC9;
                    }
                    y = 0x49;
                L_002CC9:
                    myMapper->writeCPU(0x0307 + x, y);
                }
            L_002CD0:
                a = myMapper->readCPU(0x0305 + x);
                flgC = true;
                opSBC(0x04);
                myMapper->writeCPU(0x0305 + x, a);
                a = myMapper->readCPU(0x0306 + x);
                opSBC(0x00);
                myMapper->writeCPU(0x0306 + x, a);
            L_002CE1:
                opINC(0x0307 + x, 1);
            } while (!flgZ);
        L_002CE6:
            y = a;
            opAND(0x07);
        } while (!flgZ);
        a = y;
        opAND(0x08);
        if (flgZ) {
            goto L_002D06;
        }
        a = myMapper->readCPU(0x0305 + x);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x0305 + x, a);
        a = myMapper->readCPU(0x0306 + x);
        opADC(0x00);
        myMapper->writeCPU(0x0306 + x, a);
        opDEC(0x0307 + x, 1);
    } while (!flgZ);
L_002D06:
    a = myMapper->readCPU(0x0305 + x);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0305 + x, a);
    a = myMapper->readCPU(0x0306 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x0306 + x, a);
    goto L_002CE1;
}

void game::SUB_002D1A() {
    a = myMapper->readCPU(0x0302 + x);
    opAND(0x03);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0xAD2E + y));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0xAD2F + y));
    indirectJump(myMapper->readCPU(0x0010) + (myMapper->readCPU((0x0010 + 1) & 0x00ff) << 8));
}

void game::SUB_002D36() {
    opDEC(0x0303 + x, 1);
    if (!flgN) {
        goto L_002D46;
    }
    opINC(0x0302 + x, 1);
    pushAddress(0x002D3E);
    SUB_004157();
    if (poppedEntry.value != 0x002D3E) return;
    myMapper->writeCPU(0x0303 + x, 0x38);
L_002D46:
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    a = myMapper->readCPU(0xAD54 + y);
    SUB_002779();
    return;
}

void game::SUB_002D5F() {
    pushAddress(0x002D5F);
    SUB_002798();
    if (poppedEntry.value != 0x002D5F) return;
    if (myMapper->readCPU(0x0012) != 0) {
        a = myMapper->readCPU(0x0301 + x);
        opORA(0x0F);
        if (!flgZ) {
            goto L_002D7F;
        }
    }
    opDEC(0x0303 + x, 1);
    if (!flgN) {
        goto L_002D7A;
    }
    opINC(0x0302 + x, 1);
    myMapper->writeCPU(0x0303 + x, myMapper->readCPU(0x00F5));
L_002D7A:
    a = myMapper->readCPU(0x0301 + x);
    opAND(0xF0);
L_002D7F:
    myMapper->writeCPU(0x0301 + x, a);
    pushAddress(0x002D82);
    SUB_0030AD();
    if (poppedEntry.value != 0x002D82) return;
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    a = myMapper->readCPU(0xAD93 + y);
    SUB_002779();
    return;
}

void game::SUB_002D9E() {
    opDEC(0x0303 + x, 1);
    if (!flgN) {
        goto L_002DAB;
    }
    opINC(0x0302 + x, 1);
    myMapper->writeCPU(0x0303 + x, 0x0F);
L_002DAB:
    a = myMapper->readCPU(0x0307 + x);
    SUB_002779();
    return;
}

void game::SUB_002DB1() {
    opDEC(0x0303 + x, 1);
    if (flgN) {
        a = myMapper->readCPU(0x0079);
        if (a != 0xFF) {
            if (x != myMapper->readCPU(0x0079)) {
                goto L_002DC4;
            }
            a = 0x0D;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_002DC6;
            }
        }
    L_002DC4:
        a = 0x06;
    L_002DC6:
        myMapper->writeCPU(0x0300 + x, a);
    }
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    a = myMapper->readCPU(0xADD7 + y);
    SUB_002779();
    return;
}

void game::SUB_002DE2() {
    a = myMapper->readCPU(0x004C);
    opAND(0x40);
    if (flgZ) {
        a = myMapper->readCPU(0x0300 + x);
        opAND(0x1F);
        if (a == 0x0D) {
            a = myMapper->readCPU(0x00EA);
            opAND(0x03);
            if (flgZ) {
                goto L_002E1B;
            }
            myMapper->writeCPU(0x0398, 0x20);
            a = 0x02;
            goto L_002E49;
        }
        if (myMapper->readCPU(0x0011) != 0x01) {
            goto L_002E1B;
        }
        a = myMapper->readCPU(0x0010);
        opAND(0xF0);
        if (a == 0x20) {
            goto L_002E1C;
        }
        if (a == 0x50) {
            goto L_002E24;
        }
        if (a == 0x60) {
            goto L_002E24;
        }
        if (a == 0x90) {
            goto L_002E1C;
        }
    }
    do {
        do {
            do {
            L_002E1B:
                popAddress();
                return;
            L_002E1C:
                a = myMapper->readCPU(0x0010);
                opAND(0x0F);
                if (a == 0x06) {
                    goto L_002E3D;
                }
            L_002E24:
                a = myMapper->readCPU(0x0010);
                opAND(0x0F);
                if (a == 0x05) {
                    goto L_002E37;
                }
            } while (a != 0x07);
            a = myMapper->readCPU(0x0014);
            opAND(0x08);
            if (!flgZ) {
                goto L_002E3D;
            }
            popAddress();
            return;
        L_002E37:
            a = myMapper->readCPU(0x0014);
            opAND(0x08);
        } while (!flgZ);
    L_002E3D:
        a = myMapper->readCPU(0x0304 + x);
        opEOR(myMapper->readCPU(0x0305 + x));
        opAND(0x01);
    } while (flgZ);
    a = myMapper->readCPU(0x00F6);
L_002E49:
    myMapper->writeCPU(0x0303 + x, a);
    myMapper->writeCPU(0x0300 + x, 0x09);
    a = 0x00;
    myMapper->writeCPU(0x0302 + x, a);
    opPLA();
    opPLA();
    a = myMapper->readCPU(0x0307 + x);
    SUB_002779();
    return;
}

void game::SUB_002E5E() {
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0300 + y);
        opORA(0x80);
        myMapper->writeCPU(0x0300 + y, a);
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
        opCMP(a, 0x90);
    } while (!flgC);
    myMapper->writeCPU(0x0300 + x, 0x0A);
    myMapper->writeCPU(0x0303 + x, 0x0F);
    myMapper->writeCPU(0x006D, myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x006E, myMapper->readCPU(0x004F));
    SUB_00416D();
    return;
}

void game::SUB_002E86() {
    opDEC(0x0303 + x, 1);
    if (!flgN) {
        goto L_002E96;
    }
    myMapper->writeCPU(0x0300 + x, 0x81);
    a = myMapper->readCPU(0x005F);
    opORA(0x80);
    myMapper->writeCPU(0x005F, a);
L_002E96:
    a = myMapper->readCPU(0x0301 + x);
    opLSR_A(4);
    y = a;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0xAD93 + y));
    myMapper->writeCPU(0x0013, 0x31);
    popAddress();
}

void game::SUB_002EA8() {
    if (myMapper->readCPU(0x0305 + x) >= 0xAC) {
        goto L_002EBD;
    }
    a = myMapper->readCPU(0x005F);
    opORA(0x20);
    myMapper->writeCPU(0x005F, a);
    a = myMapper->readCPU(0x0300 + x);
    opORA(0x80);
    myMapper->writeCPU(0x0300 + x, a);
L_002EBD:
    myMapper->writeCPU(0x0301 + x, 0x15);
    pushAddress(0x002EC2);
    SUB_0021D6();
    if (poppedEntry.value != 0x002EC2) return;
    myMapper->writeCPU(0x0012, 0x84);
    myMapper->writeCPU(0x0013, 0x01);
    popAddress();
}

void game::SUB_002ECE() {
    myMapper->writeCPU(0x0021, 0x80);
    a = myMapper->readCPU(0x001D);
    opAND(0x0F);
    if (flgZ) {
        if (!(myMapper->readCPU(0x00F1) & 0x80)) {
            goto L_002EE2;
        }
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0021, a);
        if (flgZ) {
            goto L_002EE4;
        }
    L_002EE2:
        opDEC(0x00F1, 1);
    }
L_002EE4:
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0300 + x);
        if (a == 0x8E) {
            y = 0x6B;
            a = myMapper->readCPU(0x001D);
            opAND(0x10);
            if (!flgZ) {
                goto L_002EF6;
            }
            opINY(1);
        L_002EF6:
            myMapper->writeCPU(0x0307 + x, y);
        }
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
    } while (x < 0x90);
    popAddress();
}

void game::SUB_002F04() {
    if (!(myMapper->readCPU(0x0070) & 0x80)) {
        SUB_002F3D();
        return;
    }
    a = 0x50;
    myMapper->writeCPU(0x030D, a);
    myMapper->writeCPU(0x0315, a);
    a = 0x02;
    myMapper->writeCPU(0x030E, a);
    myMapper->writeCPU(0x0316, a);
    myMapper->writeCPU(0x0056, 0xC0);
    myMapper->writeCPU(0x0057, 0x00);
    popAddress();
}

void game::SUB_002F21() {
    y = 0x07;
    do {
        myMapper->writeCPU(0x0318 + y, myMapper->readCPU(0xAF3E + y));
        opDEY(1);
    } while (!flgN);
    a = myMapper->readCPU(0x004D);
    myMapper->writeCPU(0x031C, a);
    flgC = true;
    opSBC(0x20);
    myMapper->writeCPU(0x031A, a);
    flgC = false;
    opADC(0x40);
    myMapper->writeCPU(0x031B, a);
    SUB_002F3D();
    return;
}

void game::SUB_002F3D() {
    popAddress();
}

void game::SUB_002F46() {
    a = myMapper->readCPU(0x004C);
    opAND(0x60);
    if (flgZ) {
        a = myMapper->readCPU(0x00FD);
        opAND(0xC0);
        if (!flgZ) {
            opASL_A(1);
            if (!flgC) {
                if (myMapper->readCPU(0x0304 + x) < myMapper->readCPU(0x0302 + x)) {
                    goto L_002F6E;
                }
                opDEC(0x0304 + x, 1);
            }
            else {
                if (myMapper->readCPU(0x0304 + x) >= myMapper->readCPU(0x0303 + x)) {
                    goto L_002F6E;
                }
                opINC(0x0304 + x, 1);
            }
        }
    }
L_002F6E:
    myMapper->writeCPU(0x0012, 0x39);
    myMapper->writeCPU(0x0013, 0x01);
    popAddress();
}

void game::SUB_002F77() {
    pushAddress(0x002F77);
    SUB_0025D5();
    if (poppedEntry.value != 0x002F77) return;
    pushAddress(0x002F7A);
    SUB_00200A();
    if (poppedEntry.value != 0x002F7A) return;
    if (myMapper->readCPU(0x0011) >= 0xF0) {
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(myMapper->readCPU(0x0305 + x));
        a = myMapper->readCPU(0x004F);
        opSBC(myMapper->readCPU(0x0306 + x));
        if (flgC) {
            a = 0x20;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_002FA3;
            }
        }
        a = 0x10;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_002FA3;
        }
    }
    a = myMapper->readCPU(0x00EA);
    opAND(0xF0);
    if (!flgZ) {
        goto L_002FA3;
    }
    a = myMapper->readCPU(0x0301 + x);
    opAND(0xF0);
L_002FA3:
    opORA(myMapper->readCPU(0x00FE));
    myMapper->writeCPU(0x0301 + x, a);
    myMapper->writeCPU(0x0015, a);
    SUB_002721();
    return;
}

void game::SUB_002FAD() {
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_002FB6;
    }
    if (myMapper->readCPU(0x00FC) & 0x80) {
        goto L_002FB6;
    }
    popAddress();
    return;
L_002FB6:
    pushAddress(0x002FB6);
    SUB_000C30();
    if (poppedEntry.value != 0x002FB6) return;
    y = 0x00;
    myMapper->writeCPU(0x0010, y);
    opDEY(1);
    myMapper->writeCPU(0x0011, y);
    myMapper->writeCPU(0x007A, y);
    myMapper->writeCPU(0x007E, y);
    y = 0x70;
    do {
        opCMP(myMapper->readCPU(0x0304 + y), myMapper->readCPU(0x0010));
        if (flgC) {
            if (!flgZ) {
                goto L_002FD4;
            }
            pushAddress(0x002FCF);
            SUB_003031();
            if (poppedEntry.value != 0x002FCF) return;
            if (flgC) {
                goto L_002FDB;
            }
        L_002FD4:
            myMapper->writeCPU(0x007A, y);
            myMapper->writeCPU(0x0010, myMapper->readCPU(0x0304 + y));
        }
    L_002FDB:
        opCMP(myMapper->readCPU(0x0304 + y), myMapper->readCPU(0x0011));
        if (!flgZ) {
            if (flgC) {
                goto L_002FF2;
            }
            if (!flgC) {
                goto L_002FEB;
            }
        }
        pushAddress(0x002FE6);
        SUB_003031();
        if (poppedEntry.value != 0x002FE6) return;
        if (flgC) {
            goto L_002FF2;
        }
    L_002FEB:
        myMapper->writeCPU(0x007E, y);
        myMapper->writeCPU(0x0011, myMapper->readCPU(0x0304 + y));
    L_002FF2:
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    } while (a < 0x90);
    y = 0x0A;
    myMapper->writeCPU(0x0701, y);
    opINY(1);
    myMapper->writeCPU(0x0705, y);
    a = 0x01;
    myMapper->writeCPU(0x0702, a);
    myMapper->writeCPU(0x0706, a);
    myMapper->writeCPU(0x0058, myMapper->readCPU(0x007A));
    pushAddress(0x003010);
    SUB_00200A();
    if (poppedEntry.value != 0x003010) return;
    myMapper->writeCPU(0x0703, a);
    a = myMapper->readCPU(0x0011);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0058, myMapper->readCPU(0x007E));
    pushAddress(0x003022);
    SUB_00200A();
    if (poppedEntry.value != 0x003022) return;
    myMapper->writeCPU(0x0707, a);
    a = myMapper->readCPU(0x0011);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x0704, a);
    popAddress();
}

void game::SUB_003031() {
    a = myMapper->readCPU(0x0305 + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x0305 + x));
    a = myMapper->readCPU(0x0306 + y);
    opSBC(myMapper->readCPU(0x0306 + x));
    SUB_00303E();
    return;
}

void game::SUB_00303E() {
    popAddress();
}

void game::SUB_00303F() {
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_003047;
    }
    if (!(myMapper->readCPU(0x00FC) & 0x80)) {
        SUB_00303E();
        return;
    }
L_003047:
    myMapper->writeCPU(0x0021, 0x00);
    pushAddress(0x00304B);
    SUB_0009AD();
    if (poppedEntry.value != 0x00304B) return;
    do {
        do {
            wait();
            pushAddress(0x00304E);
            SUB_000F4A();
            if (poppedEntry.value != 0x00304E) return;
            a = myMapper->readCPU(0x00EA);
            y = a;
            opAND(0x03);
            if (!flgZ) {
                goto L_00307A;
            }
            a = myMapper->readCPU(0x0021);
            opCMP(a, 0xFC);
            if (flgC) {
                goto L_003077;
            }
            opAND(0x20);
            if (flgZ) {
                goto L_00306C;
            }
            a = 0xFF;
            setLoadFlag(a);
            myMapper->writeCPU(0x0701, a);
            myMapper->writeCPU(0x0705, a);
        } while (!flgZ);
    L_00306C:
        y = 0x0A;
        myMapper->writeCPU(0x0701, y);
        opINY(1);
        myMapper->writeCPU(0x0705, y);
    } while (!flgZ);
L_003077:
    y = myMapper->readCPU(0x000F);
L_00307A:
    pushAddress(0x00307A);
    SUB_0009B7();
    if (poppedEntry.value != 0x00307A) return;
    x = 0x00;
    a = y;
    opLSR_A(1);
    if (flgC) {
        goto L_003085;
    }
    x = 0x04;
L_003085:
    y = myMapper->readCPU((0x007A + x) & 0x00ff);
    myMapper->writeCPU(0x0079, y);
    myMapper->writeCPU(0x0300 + y, 0x8D);
    a = 0xF0;
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0704, a);
    popAddress();
}

void game::SUB_003097() {
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_0030A9;
    }
    if (!(myMapper->readCPU(0x00FC) & 0x80)) {
        if (myMapper->readCPU(0x002D) < 0x02) {
            goto L_0030A9;
        }
        a = myMapper->readCPU(0xB126 + y);
        setLoadFlag(a);
        popAddress();
        return;
    }
L_0030A9:
    a = myMapper->readCPU(0xA298 + y);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0030AD() {
    a = myMapper->readCPU(0x00F4);
    if (a != 0x03) {
        a = myMapper->readCPU(0x0301 + x);
        opASL_A(4);
        myMapper->writeCPU(0x0010, a);
        if (a == 0xF0) {
            myMapper->writeCPU(0x0010, 0x00);
            a = myMapper->readCPU(0x001D);
            opAND(0x0F);
            if (!flgZ) {
                goto L_003125;
            }
        }
        a = myMapper->readCPU(0x001D);
        opAND(0x0F);
        opORA(myMapper->readCPU(0x0010));
        y = a;
        pushAddress(0x0030D1);
        SUB_003097();
        if (poppedEntry.value != 0x0030D1) return;
        if (!flgZ) {
            myMapper->writeCPU(0x0010, myMapper->readCPU(0x0301 + x));
            opASL_M(0x0010, 1);
            if (flgC) {
                a = myMapper->readCPU(0x0304 + x);
                opCMP(a, 0xC6);
                if (!flgC) {
                    opADC(0x01);
                    myMapper->writeCPU(0x0304 + x, a);
                }
            }
            opASL_M(0x0010, 1);
            if (flgC) {
                a = myMapper->readCPU(0x0304 + x);
                opCMP(a, 0x13);
                if (flgC) {
                    opSBC(0x01);
                    myMapper->writeCPU(0x0304 + x, a);
                }
            }
            opASL_M(0x0010, 1);
            if (flgC) {
                a = myMapper->readCPU(0x0305 + x);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x0305 + x, a);
                a = myMapper->readCPU(0x0306 + x);
                opADC(0x00);
                myMapper->writeCPU(0x0306 + x, a);
            }
            opASL_M(0x0010, 1);
            if (!flgC) {
                goto L_003125;
            }
            a = myMapper->readCPU(0x0305 + x);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU(0x0305 + x, a);
            a = myMapper->readCPU(0x0306 + x);
            opSBC(0x00);
            myMapper->writeCPU(0x0306 + x, a);
        }
    }
L_003125:
    popAddress();
}

void game::SUB_00362C() {
    a = 0x20;
    opBIT(myMapper->readCPU(0x004C));
    if (!flgV) {
        if (!flgZ) {
            goto L_00363A;
        }
        pushAddress(0x003634);
        SUB_003813();
        if (poppedEntry.value != 0x003634) return;
        SUB_003697();
        return;
    L_00363A:
        SUB_00372D();
        return;
    }
    pushAddress(0x00363D);
    SUB_003813();
    if (poppedEntry.value != 0x00363D) return;
    if (flgC) {
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x0035) & 0x80) {
        if (myMapper->readCPU(0x00F7) != 0) {
            goto L_003656;
        }
        a = myMapper->readCPU(0x005F);
        setLoadFlag(a);
        if (flgN) {
            SUB_003697();
            return;
        }
        opORA(0x80);
        myMapper->writeCPU(0x005F, a);
        SUB_003697();
        return;
    }
L_003656:
    opDEC(0x00F7, 1);
    a = myMapper->readCPU(0x0052);
    flgC = false;
    opADC(myMapper->readCPU(0x0054));
    myMapper->writeCPU(0x0054, a);
    if (flgC) {
        a = myMapper->readCPU(0x004C);
        opLSR_A(1);
        if (!flgC) {
            pushAddress(0x003666);
            SUB_0036D7();
            if (poppedEntry.value != 0x003666) return;
            if (!flgC) {
                goto L_003682;
            }
            a = myMapper->readCPU(0x0054);
            opSBC(myMapper->readCPU(0x0052));
            myMapper->writeCPU(0x0054, a);
            SUB_003697();
            return;
        }
        pushAddress(0x003674);
        SUB_003703();
        if (poppedEntry.value != 0x003674) return;
        if (flgC) {
            a = myMapper->readCPU(0x0054);
            opSBC(myMapper->readCPU(0x0052));
            myMapper->writeCPU(0x0054, a);
            SUB_003697();
            return;
        }
    }
L_003682:
    a = myMapper->readCPU(0x0051);
    flgC = false;
    opADC(myMapper->readCPU(0x0053));
    myMapper->writeCPU(0x0053, a);
    if (!flgC) {
        SUB_003697();
        return;
    }
    a = myMapper->readCPU(0x004C);
    opLSR_A(2);
    if (flgC) {
        goto L_003695;
    }
    opINC(0x004D, 1);
    if (!flgZ) {
        SUB_003697();
        return;
    }
L_003695:
    opDEC(0x004D, 1);
    SUB_003697();
    return;
}

void game::SUB_003697() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x18);
    a = myMapper->readCPU(0x004F);
    opSBC(0x01);
    if (!flgC) {
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0x68);
        if (!flgZ) {
            goto L_0036AB;
        }
    }
    a = 0xB0;
L_0036AB:
    myMapper->writeCPU(0x0050, a);
    if (!(myMapper->readCPU(0x004C) & 0x80)) {
        a = 0xF8;
    }
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0748, a);
    a = myMapper->readCPU(0x004D);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x074B, a);
    if (myMapper->readCPU(0x00F4) == 0) {
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(myMapper->readCPU(0x0056));
        a = myMapper->readCPU(0x004F);
        opSBC(myMapper->readCPU(0x0057));
        if (flgC) {
            goto L_0036D6;
        }
        a = myMapper->readCPU(0x004C);
        opAND(0xF3);
        myMapper->writeCPU(0x004C, a);
    }
L_0036D6:
    popAddress();
}

void game::SUB_0036D7() {
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    if (!flgC) {
        goto L_0036E4;
    }
    a = myMapper->readCPU(0x004E);
    opAND(0x03);
    opCMP(a, 0x03);
    if (flgZ) {
        goto L_003702;
    }
L_0036E4:
    a = myMapper->readCPU(0x004A);
    opORA(0x80);
    myMapper->writeCPU(0x004A, a);
    a = myMapper->readCPU(0x004E);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x004E, a);
    a = myMapper->readCPU(0x004F);
    opADC(0x00);
    myMapper->writeCPU(0x004F, a);
    myMapper->writeCPU(0x039A, 0x01);
    myMapper->writeCPU(0x039B, 0x00);
    flgC = false;
L_003702:
    popAddress();
}

void game::SUB_003703() {
    a = myMapper->readCPU(0x001D);
    opLSR_A(1);
    if (!flgC) {
        goto L_003710;
    }
    a = myMapper->readCPU(0x004E);
    opAND(0x03);
    opCMP(a, 0x01);
    if (flgZ) {
        goto L_00372C;
    }
L_003710:
    a = myMapper->readCPU(0x004A);
    opAND(0x0F);
    myMapper->writeCPU(0x004A, a);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x004E, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x004F, a);
    a = 0xFF;
    myMapper->writeCPU(0x039A, a);
    myMapper->writeCPU(0x039B, a);
    flgC = false;
L_00372C:
    popAddress();
}

void game::SUB_00372D() {
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x005A));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x005B));
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x005C));
    myMapper->writeCPU(0x0053, 0x00);
    a = myMapper->readCPU(0x0011);
    flgC = true;
    opSBC(myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x0011, a);
    myMapper->writeCPU(0x0051, a);
    a = myMapper->readCPU(0x0012);
    opSBC(myMapper->readCPU(0x004F));
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0052, a);
    if (!flgC) {
        opEOR(0xFF);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0011);
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0011, a);
        myMapper->writeCPU(0x0051, a);
        a = myMapper->readCPU(0x0012);
        opADC(0x00);
        myMapper->writeCPU(0x0012, a);
        myMapper->writeCPU(0x0052, a);
        myMapper->writeCPU(0x0053, 0x01);
    }
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0051));
    a = myMapper->readCPU(0x0052);
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0055, a);
    myMapper->writeCPU(0x0052, myMapper->readCPU(0x0011));
    a = myMapper->readCPU(0x0010);
    flgC = true;
    opSBC(myMapper->readCPU(0x004D));
    myMapper->writeCPU(0x0010, a);
    if (!flgC) {
        opEOR(0xFF);
        opADC(0x01);
        myMapper->writeCPU(0x0010, a);
        a = myMapper->readCPU(0x0053);
        opORA(0x02);
        myMapper->writeCPU(0x0053, a);
    }
    myMapper->writeCPU(0x0051, myMapper->readCPU(0x0010));
    a = 0x00;
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0013, a);
    if (myMapper->readCPU(0x0055) == 0) {
        opCMP(myMapper->readCPU(0x0051), myMapper->readCPU(0x0052));
        if (flgZ) {
            goto L_0037BF;
        }
        if (!flgC) {
            goto L_0037C7;
        }
        myMapper->writeCPU(0x0012, myMapper->readCPU(0x0051));
        myMapper->writeCPU(0x0011, myMapper->readCPU(0x0052));
        pushAddress(0x0037AC);
        SUB_001109();
        if (poppedEntry.value != 0x0037AC) return;
        myMapper->writeCPU(0x0052, myMapper->readCPU(0x0014));
        myMapper->writeCPU(0x0051, 0xFF);
        a = 0xC4;
        setLoadFlag(a);
        myMapper->writeCPU(0x0749, a);
        if (!flgZ) {
            goto L_0037E3;
        }
        popAddress();
        return;
    L_0037BF:
        a = 0xFF;
        setLoadFlag(a);
        myMapper->writeCPU(0x0051, a);
        myMapper->writeCPU(0x0052, a);
        if (!flgZ) {
            goto L_0037DE;
        }
    }
L_0037C7:
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0052));
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0055));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0051));
    pushAddress(0x0037D3);
    SUB_001109();
    if (poppedEntry.value != 0x0037D3) return;
    myMapper->writeCPU(0x0051, myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0052, 0xFF);
L_0037DE:
    myMapper->writeCPU(0x0749, 0xBE);
L_0037E3:
    myMapper->writeCPU(0x074A, 0x01);
    a = myMapper->readCPU(0x0053);
    opORA(0xC0);
    myMapper->writeCPU(0x0015, a);
    a = myMapper->readCPU(0x004C);
    opAND(0x0C);
    opORA(myMapper->readCPU(0x0015));
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x0037F6);
    SUB_000F4A();
    if (poppedEntry.value != 0x0037F6) return;
    opLSR_A(2);
    opADC(0xA0);
    myMapper->writeCPU(0x00F7, a);
    a = 0x00;
    myMapper->writeCPU(0x0053, a);
    myMapper->writeCPU(0x0054, a);
    myMapper->writeCPU(0x006D, myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x006E, myMapper->readCPU(0x004F));
    pushAddress(0x00380D);
    SUB_0040F1();
    if (poppedEntry.value != 0x00380D) return;
    SUB_003697();
    return;
}

void game::SUB_003813() {
    a = myMapper->readCPU(0x004D);
    if (a >= 0x14) {
        if (a >= 0xC5) {
            goto L_003856;
        }
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0x70);
        a = myMapper->readCPU(0x004F);
        opSBC(0x00);
        if (!flgC) {
            a = 0x80;
            opORA(myMapper->readCPU(0x005F));
            opAND(0x82);
            myMapper->writeCPU(0x005F, a);
            flgC = true;
            popAddress();
            return;
        }
        if (myMapper->readCPU(0x004F) == 0) {
            opCMP(myMapper->readCPU(0x004E), 0xC0);
            if (flgC) {
                goto L_003843;
            }
            myMapper->writeCPU(0x00F7, 0xFF);
            pushAddress(0x003840);
            SUB_0038FC();
            if (poppedEntry.value != 0x003840) return;
        }
    L_003843:
        a = myMapper->readCPU(0x004E);
        flgC = true;
        opSBC(0x00);
        a = myMapper->readCPU(0x004F);
        opSBC(0x04);
        if (!flgC) {
            goto L_003871;
        }
        myMapper->writeCPU(0x004E, 0xFC);
        myMapper->writeCPU(0x004F, 0x03);
    }
L_003856:
    a = myMapper->readCPU(0x004C);
    opAND(0x03);
    opORA(0x10);
    myMapper->writeCPU(0x004C, a);
    myMapper->writeCPU(0x0022, 0x00);
    a = myMapper->readCPU(0x005F);
    opORA(0x40);
    myMapper->writeCPU(0x005F, a);
    myMapper->writeCPU(0x006D, myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x006E, myMapper->readCPU(0x004F));
    flgC = true;
L_003871:
    popAddress();
}

void game::SUB_003872() {
    a = myMapper->readCPU(0x0010);
    flgC = true;
    opSBC(0xE5);
    a = myMapper->readCPU(0x0011);
    opSBC(0x03);
    if (flgC) {
        goto L_00389D;
    }
    a = myMapper->readCPU(0x0010);
    flgC = true;
    opSBC(0xC0);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0011);
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    if (!flgC) {
        goto L_0038A0;
    }
    myMapper->writeCPU(0x0013, 0x00);
    myMapper->writeCPU(0x0012, 0x0A);
    pushAddress(0x003894);
    SUB_001109();
    if (poppedEntry.value != 0x003894) return;
    a = myMapper->readCPU(0x0014);
    flgC = false;
    opADC(0x5F);
    popAddress();
    return;
L_00389D:
    a = 0xAF;
    popAddress();
    return;
L_0038A0:
    a = 0x5F;
    popAddress();
}

void game::SUB_0038A3() {
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x004F));
    pushAddress(0x0038AB);
    SUB_003872();
    if (poppedEntry.value != 0x0038AB) return;
    flgC = true;
    opSBC(0x02);
    myMapper->writeCPU(0x074C, a);
    SUB_0038B4();
    return;
}

void game::SUB_0038B4() {
    popAddress();
}

void game::SUB_0038B5() {
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x8D);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    if (flgC) {
        SUB_0038B4();
        return;
    }
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x80);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    if (!flgC) {
        SUB_0038B4();
        return;
    }
    a = myMapper->readCPU(0x004D);
    opCMP(a, 0x53);
    if (!flgC) {
        SUB_0038B4();
        return;
    }
    opCMP(a, 0x85);
    if (flgC) {
        SUB_0038B4();
        return;
    }
    y = 0x03;
    myMapper->writeCPU(0x006F, y);
    a = myMapper->readCPU(0x005F);
    opORA(0x02);
    myMapper->writeCPU(0x005F, a);
    if (!(myMapper->readCPU(0x0070) & 0x80)) {
        goto L_0038EB;
    }
    a = myMapper->readCPU(0x005F);
    opAND(0xFD);
    myMapper->writeCPU(0x005F, a);
    y = 0x01;
L_0038EB:
    a = y;
    pushAddress(0x0038EC);
    SUB_0008A1();
    if (poppedEntry.value != 0x0038EC) return;
    myMapper->writeCPU(0x0022, 0x00);
    SUB_004161();
    return;
}

void game::SUB_0038F6() {
    opBIT(myMapper->readCPU(0x004C));
    if (flgV) {
        SUB_0038B5();
        return;
    }
    if (!flgV) {
        SUB_00390C();
        return;
    }
    SUB_0038FC();
    return;
}

void game::SUB_0038FC() {
    if (myMapper->readCPU(0x006F) != 0) {
        SUB_0038B4();
        return;
    }
    a = myMapper->readCPU(0x0070);
    setLoadFlag(a);
    if (flgN) {
        SUB_0038F6();
        return;
    }
    a = myMapper->readCPU(0x0035);
    setLoadFlag(a);
    if (flgN) {
        SUB_0038F6();
        return;
    }
    opBIT(myMapper->readCPU(0x004C));
    if (flgV) {
        SUB_0038B4();
        return;
    }
    SUB_00390C();
    return;
}

void game::SUB_00390C() {
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0300 + x);
        opCMP(a, 0x81);
        if (flgZ) {
            SUB_0038B4();
            return;
        }
        if (a != 0x01) {
            goto L_003929;
        }
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x0304 + x));
        myMapper->writeCPU(0x0011, 0x48);
        a = 0x0E;
        setLoadFlag(a);
        myMapper->writeCPU(0x0300 + x, a);
        if (!flgZ) {
            goto L_00392E;
        }
    L_003929:
        opORA(0x80);
        myMapper->writeCPU(0x0300 + x, a);
    L_00392E:
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        opCMP(x, 0x90);
    } while (!flgC);
    pushAddress(0x003937);
    SUB_004161();
    if (poppedEntry.value != 0x003937) return;
    y = 0x06;
    myMapper->writeCPU(0x006F, y);
    if (!(myMapper->readCPU(0x0070) & 0x80)) {
        goto L_003944;
    }
    y = 0x00;
L_003944:
    a = y;
    pushAddress(0x003945);
    SUB_0008A1();
    if (poppedEntry.value != 0x003945) return;
    myMapper->writeCPU(0x0022, 0x00);
    popAddress();
}

void game::SUB_003E8D() {
    a = 0x00;
    myMapper->writeCPU(0x4015, a);
    myMapper->writeCPU(0x00E8, a);
    a = 0xFF;
    myMapper->writeCPU(0x00D3, a);
    myMapper->writeCPU(0x00D4, a);
    myMapper->writeCPU(0x00D5, a);
    myMapper->writeCPU(0x00D6, a);
    popAddress();
}

void game::SUB_003EA3() {
    x = 0x00;
    pushAddress(0x003EA5);
    SUB_003EB4();
    if (poppedEntry.value != 0x003EA5) return;
    x = 0x01;
    pushAddress(0x003EAA);
    SUB_003EB4();
    if (poppedEntry.value != 0x003EAA) return;
    x = 0x02;
    pushAddress(0x003EAF);
    SUB_003EB4();
    if (poppedEntry.value != 0x003EAF) return;
    x = 0x03;
    SUB_003EB4();
    return;
}

void game::SUB_003EB4() {
    a = x;
    opASL_A(2);
    myMapper->writeCPU(0x00E7, a);
    a = myMapper->readCPU((0x00D3 + x) & 0x00ff);
    setLoadFlag(a);
    if (flgZ) {
        goto L_003EE0;
    }
    opCMP(a, 0xFF);
    if (flgZ) {
        goto L_003ED8;
    }
    opDEC((0x00CB + x) & 0x00ff, 1);
    if (!flgZ) {
        goto L_003ED8;
    }
    while (true) {
        pushAddress(0x003EC5);
        SUB_003F19();
        if (poppedEntry.value != 0x003EC5) return;
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        pushAddress(0x003ECC);
        SUB_004016();
        if (poppedEntry.value != 0x003ECC) return;
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_003ED9;
        }
        pushAddress(0x003ED3);
        SUB_003F47();
        if (poppedEntry.value != 0x003ED3) return;
        opINC((0x00D3 + x) & 0x00ff, 1);
    L_003ED8:
        popAddress();
        return;
    L_003ED9:
        myMapper->writeCPU((0x00D3 + x) & 0x00ff, 0xFF);
        SUB_004006();
        return;
    L_003EE0:
        pushAddress(0x003EE0);
        SUB_003FF7();
        if (poppedEntry.value != 0x003EE0) return;
        myMapper->writeCPU(0x0014, myMapper->readCPU((0x00D7 + x) & 0x00ff));
        myMapper->writeCPU(0x0015, myMapper->readCPU((0x00DB + x) & 0x00ff));
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU((0x00CF + x) & 0x00ff, a);
        opAND(0x30);
        myMapper->writeCPU((0x00C7 + x) & 0x00ff, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        pushAddress(0x003EF8);
        SUB_003F33();
        if (poppedEntry.value != 0x003EF8) return;
        opINY(1);
        myMapper->writeCPU((0x00D3 + x) & 0x00ff, y);
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        opORA(myMapper->readCPU(0x0013));
        y = myMapper->readCPU(0x00E7);
        myMapper->writeCPU(0x4000 + y, a);
        myMapper->writeCPU((0x00E3 + x) & 0x00ff, a);
        y = 0x03;
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        y = myMapper->readCPU(0x00E7);
        myMapper->writeCPU(0x4001 + y, a);
        myMapper->writeCPU((0x00DF + x) & 0x00ff, 0xFF);
    }
    SUB_003F19();
    return;
}

void game::SUB_003F19() {
    myMapper->writeCPU(0x0015, 0x00);
    myMapper->writeCPU(0x0014, myMapper->readCPU((0x00D3 + x) & 0x00ff));
    opASL_M(0x0014, 1);
    opROL_M(0x0015, 1);
    a = myMapper->readCPU((0x00D7 + x) & 0x00ff);
    flgC = false;
    opADC(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0014, a);
    a = myMapper->readCPU((0x00DB + x) & 0x00ff);
    opADC(myMapper->readCPU(0x0015));
    myMapper->writeCPU(0x0015, a);
    popAddress();
}

void game::SUB_003F33() {
    opPHA();
    a = myMapper->readCPU((0x00C7 + x) & 0x00ff);
    opCMP(a, 0x20);
    if (flgZ) {
        goto L_003F43;
    }
    opPLA();
    opROR_A(3);
    opAND(0xC0);
    myMapper->writeCPU(0x0013, a);
    popAddress();
    return;
L_003F43:
    opPLA();
    myMapper->writeCPU(0x0013, a);
    popAddress();
}

void game::SUB_003F47() {
    opPHA();
    a = myMapper->readCPU((0x00C7 + x) & 0x00ff);
    if (a == 0x30) {
        goto L_003F9E;
    }
    opPLA();
    opPHA();
    opAND(0x0F);
    opCMP(a, 0x0C);
    if (flgC) {
        goto L_003F97;
    }
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0xBFAC + y));
    a = myMapper->readCPU(0xBFAB + y);
    myMapper->writeCPU(0x0011, a);
    opPLA();
    opAND(0xF0);
    opCMP(a, 0xA0);
    if (flgC) {
        goto L_003F96;
    }
    opLSR_A(4);
    y = a;
    do {
        opLSR_M(0x0011, 1);
        opROR_M(0x0010, 1);
        opDEY(1);
    } while (!flgN);
    do {
        pushAddress(0x003F75);
        SUB_003FC3();
        if (poppedEntry.value != 0x003F75) return;
        pushAddress(0x003F78);
        SUB_003FF7();
        if (poppedEntry.value != 0x003F78) return;
        a = myMapper->readCPU((0x00E3 + x) & 0x00ff);
        y = myMapper->readCPU(0x00E7);
        myMapper->writeCPU(0x4000 + y, a);
        a = myMapper->readCPU(0x0011);
        opAND(0x07);
        opORA(0x08);
        myMapper->writeCPU(0x0011, a);
        a = myMapper->readCPU(0x0010);
        y = myMapper->readCPU(0x00E7);
        myMapper->writeCPU(0x4002 + y, a);
        a = myMapper->readCPU(0x0011);
        myMapper->writeCPU(0x4003 + y, a);
    L_003F96:
        popAddress();
        return;
    L_003F97:
        opPLA();
        do {
            pushAddress(0x003F98);
            SUB_004006();
            if (poppedEntry.value != 0x003F98) return;
            SUB_003FC3();
            return;
        L_003F9E:
            opPLA();
            opCMP(a, 0x10);
        } while (flgC);
        myMapper->writeCPU(0x0010, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0011, a);
    } while (flgZ);
}

void game::SUB_003FC3() {
    y = 0x01;
    a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
    opCMP(a, 0xF0);
    if (!flgC) {
        goto L_003FE2;
    }
    flgC = true;
    opSBC(0xF0);
    y = a;
    a = myMapper->readCPU(0xBFE7 + y);
    while (true) {
        myMapper->writeCPU((0x00CB + x) & 0x00ff, a);
        a = myMapper->readCPU((0x00CF + x) & 0x00ff);
        opAND(0x01);
        if (flgZ) {
            goto L_003FE1;
        }
        a = myMapper->readCPU((0x00CB + x) & 0x00ff);
        flgC = false;
        opADC(myMapper->readCPU((0x00CB + x) & 0x00ff));
        myMapper->writeCPU((0x00CB + x) & 0x00ff, a);
    L_003FE1:
        popAddress();
        return;
    L_003FE2:
        opAND(0x0F);
    }
    SUB_003FF7();
    return;
}

void game::SUB_003FF7() {
    a = myMapper->readCPU(0x00E8);
    opORA(myMapper->readCPU(0xC00E + x));
    SUB_003FFC();
    return;
}

void game::SUB_003FFC() {
    opBIT(myMapper->readCPU(0x0031));
    if (flgN) {
        goto L_004003;
    }
    myMapper->writeCPU(0x4015, a);
L_004003:
    myMapper->writeCPU(0x00E8, a);
    popAddress();
}

void game::SUB_004006() {
    a = myMapper->readCPU(0x00E8);
    opAND(myMapper->readCPU(0xC012 + x));
    SUB_003FFC();
    return;
}

void game::SUB_004016() {
    if (a >= 0xC0) {
        goto L_004022;
    }
    if (a >= 0xB0) {
        goto L_004048;
    }
    if (a >= 0xA0) {
        goto L_004023;
    }
L_004022:
    popAddress();
    return;
L_004023:
    opINY(1);
    if (myMapper->readCPU((0x00C7 + x) & 0x00ff) == 0x20) {
        goto L_004041;
    }
    a = myMapper->readCPU((0x00E3 + x) & 0x00ff);
    opAND(0xE0);
    while (true) {
        opORA(myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU((0x00E3 + x) & 0x00ff, a);
        y = myMapper->readCPU(0x00E7);
        myMapper->writeCPU(0x4000 + y, a);
    L_004037:
        opINC((0x00D3 + x) & 0x00ff, 1);
    L_004039:
        pushAddress(0x004039);
        SUB_003F19();
        if (poppedEntry.value != 0x004039) return;
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        popAddress();
        return;
    L_004041:
        a = myMapper->readCPU((0x00E3 + x) & 0x00ff);
        opAND(0x80);
    }
L_004048:
    opAND(0x0F);
    if (a == 0x0F) {
        a = 0x02;
        setLoadFlag(a);
        myMapper->writeCPU((0x00D3 + x) & 0x00ff, a);
        if (!flgZ) {
            goto L_004039;
        }
    }
    a = myMapper->readCPU((0x00DF + x) & 0x00ff);
    setLoadFlag(a);
    if (flgZ) {
        goto L_004071;
    }
    if (a >= 0x0F) {
        goto L_004066;
    }
    opDEC((0x00DF + x) & 0x00ff, 1);
    while (true) {
        opINY(1);
        myMapper->writeCPU((0x00D3 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y));
        goto L_004039;
    L_004066:
        a = myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y);
        opAND(0x0F);
        myMapper->writeCPU((0x00DF + x) & 0x00ff, a);
        opDEC((0x00DF + x) & 0x00ff, 1);
    }
L_004071:
    opDEC((0x00DF + x) & 0x00ff, 1);
    goto L_004037;
}

void game::SUB_004076() {
    myMapper->writeCPU(0x00D7, 0x01);
    myMapper->writeCPU(0x00DB, 0xC2);
    myMapper->writeCPU(0x00D9, 0x12);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DD, a);
    if (!flgZ) {
        SUB_0040AA();
        return;
    }
    SUB_004088();
    return;
}

void game::SUB_004088() {
    myMapper->writeCPU(0x00D7, 0x23);
    myMapper->writeCPU(0x00DB, 0xC2);
    myMapper->writeCPU(0x00D9, 0x30);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DD, a);
    if (!flgZ) {
        SUB_0040AA();
        return;
    }
    SUB_00409A();
    return;
}

void game::SUB_00409A() {
    myMapper->writeCPU(0x00D7, 0x81);
    myMapper->writeCPU(0x00DB, 0xC1);
    myMapper->writeCPU(0x00D9, 0x9C);
    myMapper->writeCPU(0x00DD, 0xC1);
    SUB_0040AA();
    return;
}

void game::SUB_0040AA() {
    a = 0x00;
    myMapper->writeCPU(0x00D3, a);
    myMapper->writeCPU(0x00D5, a);
    popAddress();
}

void game::SUB_0040B1() {
    myMapper->writeCPU(0x00D7, 0xB7);
    myMapper->writeCPU(0x00DB, 0xC1);
    myMapper->writeCPU(0x00D9, 0xD0);
    a = 0xC1;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DD, a);
    if (!flgZ) {
        SUB_0040AA();
        return;
    }
    SUB_0040C3();
    return;
}

void game::SUB_0040C3() {
    myMapper->writeCPU(0x00D7, 0xDB);
    myMapper->writeCPU(0x00DB, 0xC1);
    myMapper->writeCPU(0x00D9, 0xEE);
    a = 0xC1;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DD, a);
    if (!flgZ) {
        SUB_0040AA();
        return;
    }
    SUB_0040D5();
    return;
}

void game::SUB_0040D5() {
    myMapper->writeCPU(0x00D7, 0xA7);
    myMapper->writeCPU(0x00DB, 0xC2);
    myMapper->writeCPU(0x00D9, 0xAE);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DD, a);
    if (!flgZ) {
        SUB_0040AA();
        return;
    }
    SUB_0040E7();
    return;
}

void game::SUB_0040E7() {
    myMapper->writeCPU(0x00DA, 0x3D);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DE, a);
    if (!flgZ) {
        SUB_00412E();
        return;
    }
    SUB_0040F1();
    return;
}

void game::SUB_0040F1() {
    if (myMapper->readCPU(0x0070) & 0x80) {
        goto L_004103;
    }
    if (myMapper->readCPU(0x0035) & 0x80) {
        goto L_004103;
    }
    myMapper->writeCPU(0x00DA, 0x28);
    a = 0xC3;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DE, a);
    if (!flgZ) {
        SUB_00412E();
        return;
    }
L_004103:
    pushAddress(0x004103);
    SUB_003E8D();
    if (poppedEntry.value != 0x004103) return;
    SUB_004106();
    return;
}

void game::SUB_004106() {
    myMapper->writeCPU(0x00D7, 0x44);
    myMapper->writeCPU(0x00DB, 0xC2);
    a = 0x00;
    myMapper->writeCPU(0x00D3, a);
    popAddress();
}

void game::SUB_004113() {
    if (myMapper->readCPU(0x00D6) != 0xFF) {
        goto L_004125;
    }
    myMapper->writeCPU(0x00DA, 0x4D);
    myMapper->writeCPU(0x00DE, 0xC2);
    myMapper->writeCPU(0x00D6, 0x00);
L_004125:
    popAddress();
}

void game::SUB_004126() {
    myMapper->writeCPU(0x00DA, 0x88);
    myMapper->writeCPU(0x00DE, 0xC2);
    SUB_00412E();
    return;
}

void game::SUB_00412E() {
    a = 0x00;
    myMapper->writeCPU(0x00D6, a);
    popAddress();
}

void game::SUB_004133() {
    myMapper->writeCPU(0x00D7, 0xB5);
    myMapper->writeCPU(0x00DB, 0xC2);
    myMapper->writeCPU(0x00D3, 0x00);
    popAddress();
}

void game::SUB_004140() {
    myMapper->writeCPU(0x00D8, 0xBE);
    myMapper->writeCPU(0x00DC, 0xC2);
    myMapper->writeCPU(0x00D4, 0x00);
    popAddress();
}

void game::SUB_00414D() {
    myMapper->writeCPU(0x00DA, 0xD9);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DE, a);
    if (!flgZ) {
        SUB_00412E();
        return;
    }
    SUB_004157();
    return;
}

void game::SUB_004157() {
    myMapper->writeCPU(0x00DA, 0xE4);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DE, a);
    if (!flgZ) {
        SUB_00412E();
        return;
    }
    SUB_004161();
    return;
}

void game::SUB_004161() {
    myMapper->writeCPU(0x00D8, 0x0E);
    myMapper->writeCPU(0x00DC, 0xC3);
    myMapper->writeCPU(0x00D4, 0x00);
    SUB_00416D();
    return;
}

void game::SUB_00416D() {
    myMapper->writeCPU(0x00DA, 0xEB);
    a = 0xC2;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DE, a);
    if (!flgZ) {
        SUB_00412E();
        return;
    }
    SUB_004177();
    return;
}

void game::SUB_004177() {
    myMapper->writeCPU(0x00DA, 0x1B);
    a = 0xC3;
    setLoadFlag(a);
    myMapper->writeCPU(0x00DE, a);
    if (!flgZ) {
        SUB_00412E();
        return;
    }
    pushAddress(0x004181);
    flgB = true;
    pushStatus();
    SUB_0004FF();
    popStatus();
    flgB = false;
    popAddress();
}

void game::SUB_004337() {
    pushAddress(0x004337);
    SUB_000EC4();
    if (poppedEntry.value != 0x004337) return;
    pushAddress(0x00433A);
    SUB_000EF1();
    if (poppedEntry.value != 0x00433A) return;
    y = 0x00;
    myMapper->writeCPU(0x0014, 0x08);
    myMapper->writeCPU(0x0010, 0xF0);
    myMapper->writeCPU(0x0011, 0xC3);
    myMapper->writeCPU(0x0013, 0x20);
    a = 0xA5;
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x001D, a);
    do {
        a = myMapper->readCPU(0x2002);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0013));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0012));
        x = 0x00;
        do {
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0010) + (myMapper->readCPU((0x0010 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            if (!flgZ) {
                goto L_00436E;
            }
            opINC(0x0011, 1);
        L_00436E:
            opINX(1);
        } while (x < 0x16);
        a = myMapper->readCPU(0x0012);
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0012, a);
        a = myMapper->readCPU(0x0013);
        opADC(0x00);
        myMapper->writeCPU(0x0013, a);
        opDEC(0x0014, 1);
    } while (!flgN);
    x = 0x00;
    a = 0x23;
    y = 0x05;
    pushAddress(0x00438A);
    SUB_001474();
    if (poppedEntry.value != 0x00438A) return;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xC4B6 + x));
        opINX(1);
        opCMP(x, 0x15);
    } while (!flgC);
    x = 0x00;
    a = 0x23;
    y = 0x45;
    pushAddress(0x00439E);
    SUB_001474();
    if (poppedEntry.value != 0x00439E) return;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xC4CB + x));
        opINX(1);
        opCMP(x, 0x0E);
    } while (!flgC);
    a = 0x23;
    y = 0xC0;
    pushAddress(0x0043B0);
    SUB_001474();
    if (poppedEntry.value != 0x0043B0) return;
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xC523 + y));
        opINY(1);
        opCMP(y, 0x20);
    } while (!flgC);
    x = 0x1F;
    do {
        myMapper->writeCPU((0x00A3 + x) & 0x00ff, myMapper->readCPU(0xC4D9 + x));
        opDEX(1);
    } while (!flgN);
    a = 0x22;
    y = 0x4C;
    pushAddress(0x0043CE);
    SUB_001474();
    if (poppedEntry.value != 0x0043CE) return;
    myMapper->writeCPU(0x2007, 0x01);
    pushAddress(0x0043D6);
    SUB_0044F9();
    if (poppedEntry.value != 0x0043D6) return;
    a = 0x22;
    y = 0x8C;
    pushAddress(0x0043DD);
    SUB_001474();
    if (poppedEntry.value != 0x0043DD) return;
    myMapper->writeCPU(0x2007, 0x02);
    pushAddress(0x0043E5);
    SUB_0044F9();
    if (poppedEntry.value != 0x0043E5) return;
    myMapper->writeCPU(0x2007, 0x1C);
    SUB_000F37();
    return;
}

void game::SUB_0044F9() {
    x = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xC507 + x));
        opINX(1);
        opCMP(x, 0x07);
    } while (!flgC);
    popAddress();
}

void game::SUB_004543() {
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0300 + x);
        opAND(0x1F);
        if (a == 0x01) {
            goto L_004557;
        }
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
    } while (a < 0x20);
L_004557:
    popAddress();
}

void game::SUB_004558() {
    pushAddress(0x004558);
    SUB_004543();
    if (poppedEntry.value != 0x004558) return;
    myMapper->writeCPU(0x00F8, x);
    myMapper->writeCPU(0x00F9, 0x07);
    do {
        pushAddress(0x004561);
        SUB_00456F();
        if (poppedEntry.value != 0x004561) return;
        opDEC(0x00F9, 1);
    } while (!flgN);
    a = myMapper->readCPU(0x001B);
    opEOR(0xFF);
    myMapper->writeCPU(0x00FA, a);
    popAddress();
}

void game::SUB_00456F() {
    y = myMapper->readCPU(0x00F8);
    myMapper->writeCPU(0x0019, myMapper->readCPU(0x0304 + y));
    myMapper->writeCPU(0x0017, myMapper->readCPU(0x0305 + y));
    myMapper->writeCPU(0x0018, myMapper->readCPU(0x0306 + y));
    a = myMapper->readCPU(0x00F9);
    opASL_A(2);
    y = a;
    a = myMapper->readCPU(0x0019);
    flgC = false;
    opADC(myMapper->readCPU(0xC5AF + y));
    myMapper->writeCPU(0x0019, a);
    a = myMapper->readCPU(0x0017);
    flgC = false;
    opADC(myMapper->readCPU(0xC5B0 + y));
    myMapper->writeCPU(0x0017, a);
    a = myMapper->readCPU(0x0018);
    opADC(myMapper->readCPU(0xC5B1 + y));
    myMapper->writeCPU(0x0018, a);
    x = 0x48;
    do {
        pushAddress(0x00459E);
        SUB_0045CF();
        if (poppedEntry.value != 0x00459E) return;
        if (!flgC) {
            goto L_0045AC;
        }
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        opCMP(a, 0x90);
    } while (!flgC);
L_0045AC:
    opROL_M(0x001B, 1);
    popAddress();
}

void game::SUB_0045CF() {
    a = myMapper->readCPU(0x0304 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0019));
    if (flgC) {
        if (a >= 0x19) {
            goto L_0045F1;
        }
        a = myMapper->readCPU(0x0305 + x);
        flgC = true;
        opSBC(myMapper->readCPU(0x0017));
        myMapper->writeCPU(0x001A, a);
        a = myMapper->readCPU(0x0306 + x);
        opSBC(myMapper->readCPU(0x0018));
        if (flgZ) {
            opCMP(myMapper->readCPU(0x001A), 0x19);
            if (flgC) {
                goto L_0045F1;
            }
            popAddress();
            return;
        }
    }
L_0045F1:
    flgC = true;
    popAddress();
}

void game::SUB_0045F3() {
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_0045FB;
    }
    if (myMapper->readCPU(0x00FC) & 0x80) {
        goto L_004600;
    }
L_0045FB:
    a = myMapper->readCPU(0x00E9);
    goto L_00463C;
L_004600:
    pushAddress(0x004600);
    SUB_004543();
    if (poppedEntry.value != 0x004600) return;
    pushAddress(0x004603);
    SUB_00482B();
    if (poppedEntry.value != 0x004603) return;
    a = myMapper->readCPU(0x0301 + x);
    opAND(0x0F);
    if (a == 0x0F) {
        a = myMapper->readCPU(0x001D);
        opAND(0x04);
        if (flgZ) {
            a = 0x00;
            setLoadFlag(a);
            if (flgZ) {
                goto L_00463C;
            }
        }
    }
    a = myMapper->readCPU(0x00FA);
    opORA(myMapper->readCPU(0x0010));
    y = a;
    a = myMapper->readCPU(0xC65F + y);
    myMapper->writeCPU(0x0010, a);
    opAND(0xF0);
    if (a == 0xF0) {
        a = myMapper->readCPU(0x0010);
        opAND(0x0F);
        y = a;
        a = myMapper->readCPU(0x00FB);
        opAND(0xC0);
        opORA(myMapper->readCPU(0xC65B + y));
    }
    myMapper->writeCPU(0x0010, a);
    pushAddress(0x004637);
    SUB_00485A();
    if (poppedEntry.value != 0x004637) return;
    a = myMapper->readCPU(0x0010);
L_00463C:
    myMapper->writeCPU(0x00FD, a);
    y = myMapper->readCPU(0x0398);
    setLoadFlag(y);
    if (!flgN) {
        a = myMapper->readCPU(0x00FD);
        opAND(0x3F);
        myMapper->writeCPU(0x00FD, a);
        if (myMapper->readCPU(0x0304 + x) < 0x6C) {
            goto L_004654;
        }
        a = 0x80;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_004656;
        }
    L_004654:
        a = 0x40;
    L_004656:
        opORA(myMapper->readCPU(0x00FD));
        myMapper->writeCPU(0x00FD, a);
    }
    popAddress();
}

void game::SUB_00475F() {
    myMapper->writeCPU(0x00FB, 0x00);
    a = myMapper->readCPU(0x004D);
    if (a >= 0x48) {
        if (a >= 0x90) {
            goto L_004790;
        }
        y = 0x70;
        do {
            if (myMapper->readCPU(0x0304 + y) >= myMapper->readCPU(0x004D)) {
                goto L_004778;
            }
            opINC(0x00FB, 1);
        L_004778:
            a = y;
            flgC = false;
            opADC(0x08);
            y = a;
        } while (y < 0x90);
        opCMP(myMapper->readCPU(0x00FB), 0x02);
        if (flgZ) {
            pushAddress(0x004787);
            SUB_000F4A();
            if (poppedEntry.value != 0x004787) return;
            opASL_A(2);
            if (!flgC) {
                goto L_004790;
            }
        }
        if (flgC) {
            goto L_004794;
        }
    L_004790:
        a = 0x40;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_004796;
        }
    }
L_004794:
    a = 0x80;
L_004796:
    myMapper->writeCPU(0x00FB, a);
    pushAddress(0x004798);
    SUB_000F4A();
    if (poppedEntry.value != 0x004798) return;
    opAND(0x80);
    myMapper->writeCPU(0x0491, a);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x88);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0011, a);
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(0x68);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    myMapper->writeCPU(0x0013, a);
    a = myMapper->readCPU(0x0012);
    flgC = true;
    opSBC(0xA8);
    a = myMapper->readCPU(0x004F);
    opSBC(0x00);
    if (!flgC) {
        myMapper->writeCPU(0x0013, 0x00);
        myMapper->writeCPU(0x0012, 0xA8);
    }
    a = myMapper->readCPU(0x004E);
    flgC = true;
    opSBC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x004F);
    opSBC(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0013, a);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    pushAddress(0x0047EA);
    SUB_001109();
    if (poppedEntry.value != 0x0047EA) return;
    a = myMapper->readCPU(0x004D);
    flgC = true;
    opSBC(0x6C);
    if (!flgC) {
        opEOR(0xFF);
        opADC(0x01);
    }
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, 0x00);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    opASL_M(0x0010, 1);
    opROL_M(0x0011, 1);
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0015));
    pushAddress(0x004816);
    SUB_001109();
    if (poppedEntry.value != 0x004816) return;
    a = myMapper->readCPU(0x004D);
    opCMP(a, 0x6C);
    if (flgC) {
        goto L_004825;
    }
    opADC(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0490, a);
    popAddress();
    return;
L_004825:
    opSBC(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0490, a);
    popAddress();
}

void game::SUB_00482B() {
    myMapper->writeCPU(0x0010, 0x00);
    a = myMapper->readCPU(0x004D);
    if (a < 0x18) {
        myMapper->writeCPU(0x00FB, 0x80);
        y = 0xE0;
        a = myMapper->readCPU(0x00FA);
        opAND(0x07);
        if (flgZ) {
            goto L_004857;
        }
        y = 0xFF;
        setLoadFlag(y);
        if (!flgZ) {
            goto L_004857;
        }
    }
    if (a >= 0xC0) {
        myMapper->writeCPU(0x00FB, 0x40);
        y = 0x0E;
        a = myMapper->readCPU(0x00FA);
        opAND(0xC1);
        if (flgZ) {
            goto L_004857;
        }
        y = 0xFF;
    L_004857:
        myMapper->writeCPU(0x0010, y);
    }
    popAddress();
}

void game::SUB_00485A() {
    myMapper->writeCPU(0x0010, a);
    if (myMapper->readCPU(0x0070) & 0x80) {
        goto L_00489A;
    }
    if (myMapper->readCPU(0x0035) & 0x80) {
        goto L_00489A;
    }
    a = myMapper->readCPU(0x001D);
    opAND(0x04);
    if (flgZ) {
        goto L_004899;
    }
    a = myMapper->readCPU(0x0069);
    if (a < 0x48) {
        if (a < 0x40) {
            goto L_004899;
        }
        if (a >= 0x46) {
            goto L_004899;
        }
        pushAddress(0x004878);
        SUB_000F4A();
        if (poppedEntry.value != 0x004878) return;
        opAND(0x08);
        if (flgZ) {
            goto L_004899;
        }
        a = 0x02;
        opORA(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0010, a);
        popAddress();
        return;
    }
    pushAddress(0x004886);
    SUB_000F4A();
    if (poppedEntry.value != 0x004886) return;
    opAND(0x80);
    if (!flgZ) {
        goto L_004899;
    }
    a = myMapper->readCPU(0x00FA);
    opAND(0x83);
    if (!flgZ) {
        goto L_004899;
    }
    do {
        a = 0x01;
        opORA(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x0010, a);
    L_004899:
        popAddress();
        return;
    L_00489A:
        opCMP(myMapper->readCPU(0x031C), myMapper->readCPU(0x0490));
    } while (flgZ);
    if (!flgC) {
        goto L_0048A9;
    }
    myMapper->writeCPU(0x0010, 0x40);
    popAddress();
    return;
L_0048A9:
    myMapper->writeCPU(0x0010, 0x80);
    popAddress();
}

void game::SUB_0048AE() {
    if (myMapper->readCPU(0x0033) & 0x80) {
        goto L_0048CD;
    }
    if (!(myMapper->readCPU(0x00FC) & 0x80)) {
        goto L_0048CD;
    }
    opCMP(myMapper->readCPU(0x0062), 0x03);
    if (!flgZ) {
        goto L_0048C5;
    }
    if (myMapper->readCPU(0x0027) >= myMapper->readCPU(0x0025)) {
        goto L_0048D0;
    }
    do {
        a = 0x21;
        popAddress();
        return;
        do {
        L_0048C5:
            a = myMapper->readCPU(0x0491);
            opROL_A(2);
            opAND(0x01);
            popAddress();
            return;
        L_0048CD:
            a = myMapper->readCPU(0x00E9);
            popAddress();
            return;
        L_0048D0:
            a = myMapper->readCPU(0x004E);
            flgC = true;
            opSBC(myMapper->readCPU(0x0064));
            myMapper->writeCPU(0x0010, a);
            a = myMapper->readCPU(0x004F);
            opSBC(myMapper->readCPU(0x0065));
            if (!flgZ) {
                goto L_0048E3;
            }
            opCMP(myMapper->readCPU(0x0010), 0x0C);
        } while (!flgC);
    L_0048E3:
        if (myMapper->readCPU(0x0024) != 0) {
            goto L_0048C5;
        }
        opCMP(myMapper->readCPU(0x0023), 0x05);
    } while (!flgC);
    if (flgC) {
        goto L_0048C5;
    }
    SUB_0048EF();
    return;
}

void game::SUB_0048EF() {
    a = 0x00;
    myMapper->writeCPU(0x00EF, a);
    myMapper->writeCPU(0x0069, a);
    pushAddress(0x0048F5);
    SUB_000EC4();
    if (poppedEntry.value != 0x0048F5) return;
    pushAddress(0x0048F8);
    SUB_000EF1();
    if (poppedEntry.value != 0x0048F8) return;
    myMapper->writeCPU(0x00EE, 0x10);
    x = 0x1F;
    do {
        myMapper->writeCPU((0x00A3 + x) & 0x00ff, myMapper->readCPU(0xCB83 + x));
        opDEX(1);
    } while (!flgN);
    pushAddress(0x004909);
    SUB_000F00();
    if (poppedEntry.value != 0x004909) return;
    myMapper->writeCPU(0x0010, 0x85);
    myMapper->writeCPU(0x0011, 0x20);
    myMapper->writeCPU(0x0012, 0x6B);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x00491C);
    SUB_001152();
    if (poppedEntry.value != 0x00491C) return;
    myMapper->writeCPU(0x0010, 0xC5);
    myMapper->writeCPU(0x0011, 0x20);
    myMapper->writeCPU(0x0012, 0x82);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x00492F);
    SUB_001152();
    if (poppedEntry.value != 0x00492F) return;
    myMapper->writeCPU(0x0010, 0x46);
    myMapper->writeCPU(0x0011, 0x21);
    myMapper->writeCPU(0x0012, 0x8F);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x004942);
    SUB_001152();
    if (poppedEntry.value != 0x004942) return;
    myMapper->writeCPU(0x0010, 0xA6);
    myMapper->writeCPU(0x0011, 0x21);
    myMapper->writeCPU(0x0012, 0xA1);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x004955);
    SUB_001152();
    if (poppedEntry.value != 0x004955) return;
    myMapper->writeCPU(0x0010, 0x06);
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0012, 0xAF);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x004968);
    SUB_001152();
    if (poppedEntry.value != 0x004968) return;
    myMapper->writeCPU(0x0010, 0x66);
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0012, 0xC1);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x00497B);
    SUB_001152();
    if (poppedEntry.value != 0x00497B) return;
    myMapper->writeCPU(0x0010, 0xC6);
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0012, 0xCF);
    myMapper->writeCPU(0x0013, 0xCA);
    pushAddress(0x00498E);
    SUB_001152();
    if (poppedEntry.value != 0x00498E) return;
    a = 0x80;
    myMapper->writeCPU(0x00F4, a);
    myMapper->writeCPU(0x0034, a);
    myMapper->writeCPU(0x002D, 0x00);
    myMapper->writeCPU(0x0700, 0x50);
    myMapper->writeCPU(0x0701, 0xBF);
    myMapper->writeCPU(0x0702, 0x00);
    myMapper->writeCPU(0x0703, 0x20);
    pushAddress(0x0049AF);
    SUB_0009AD();
    if (poppedEntry.value != 0x0049AF) return;
    do {
        wait();
        a = myMapper->readCPU(0x00EB);
        opAND(0x08);
    } while (!flgZ);
    do {
        wait();
        a = myMapper->readCPU(0x00EB);
        opAND(0x08);
    } while (flgZ);
    pushAddress(0x0049BE);
    SUB_0009B7();
    if (poppedEntry.value != 0x0049BE) return;
    opASL_M(0x002D, 1);
    y = 0x00;
    myMapper->writeCPU(0x00EF, y);
    myMapper->writeCPU(0x2001, y);
    myMapper->writeCPU(0x00F2, y);
    myMapper->writeCPU(0x00F3, y);
    pushAddress(0x0049CE);
    SUB_000F37();
    if (poppedEntry.value != 0x0049CE) return;
    a = 0x0A;
    myMapper->writeCPU(0x00EF, a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x001B, 0x06);
    a = myMapper->readCPU(0x002D);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0017, myMapper->readCPU(0xCBA8 + y));
    myMapper->writeCPU(0x0018, myMapper->readCPU(0xCBA9 + y));
    myMapper->writeCPU(0x0019, myMapper->readCPU(0xCBAA + y));
    myMapper->writeCPU(0x001A, myMapper->readCPU(0xCBAB + y));
    do {
    L_0049F4:
        wait();
        if (!(myMapper->readCPU(0x2002) & 0x80)) {
            goto L_0049F4;
        }
        pushAddress(0x0049F9);
        SUB_004A38();
        if (poppedEntry.value != 0x0049F9) return;
        pushAddress(0x0049FC);
        SUB_004A59();
        if (poppedEntry.value != 0x0049FC) return;
    L_0049FF:
        if (!(myMapper->readCPU(0x2002) & 0x80)) {
            wait();
            goto L_0049FF;
        }
        pushAddress(0x004A04);
        SUB_004A15();
        if (poppedEntry.value != 0x004A04) return;
        pushAddress(0x004A07);
        SUB_004A59();
        if (poppedEntry.value != 0x004A07) return;
        opDEC(0x001B, 1);
    } while (!flgN);
    a = 0x00;
    myMapper->writeCPU(0x00F4, a);
    myMapper->writeCPU(0x0034, a);
    popAddress();
}

void game::SUB_004A15() {
    myMapper->writeCPU(0x2001, 0x00);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0018));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0017));
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0019) + (myMapper->readCPU((0x0019 + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_004A32;
        }
        myMapper->writeCPU(0x2007, a);
        opINY(1);
    } while (!flgZ);
L_004A32:
    pushAddress(0x004A32);
    SUB_000F37();
    if (poppedEntry.value != 0x004A32) return;
    SUB_00145F();
    return;
}

void game::SUB_004A38() {
    myMapper->writeCPU(0x2001, 0x00);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0018));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0017));
    y = 0x00;
    a = 0x30;
    do {
        myMapper->writeCPU(0x2007, a);
        opINY(1);
        opCMP(y, 0x14);
    } while (!flgC);
    pushAddress(0x004A53);
    SUB_000F37();
    if (poppedEntry.value != 0x004A53) return;
    SUB_00145F();
    return;
}

void game::SUB_004A59() {
    a = 0x03;
    do {
        x = 0x00;
        do {
            y = 0x80;
            do {
                opDEY(1);
            } while (!flgZ);
            opDEX(1);
        } while (!flgZ);
        flgC = true;
        opSBC(0x01);
    } while (!flgZ);
    popAddress();
}

void game::SUB_004B37() {
    a = myMapper->readCPU(0x00EB);
    opAND(0x04);
    opASL_A(3);
    opORA(myMapper->readCPU(0x00EB));
    opASL_A(3);
    if (flgC) {
        goto L_004B4D;
    }
    opASL_A(1);
    if (flgC) {
        goto L_004B70;
    }
    do {
        do {
            do {
                myMapper->writeCPU(0x0069, myMapper->readCPU(0x00EB));
                popAddress();
                return;
            L_004B4D:
                a = myMapper->readCPU(0x0069);
                opAND(0x04);
                opASL_A(3);
                opORA(myMapper->readCPU(0x0069));
                opAND(0x20);
            } while (!flgZ);
            a = myMapper->readCPU(0x002D);
            if (a < 0x04) {
                goto L_004B62;
            }
            a = 0xFF;
        L_004B62:
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x002D, a);
        L_004B67:
            y = a;
            a = myMapper->readCPU(0xCBA3 + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0700, a);
        } while (!flgZ);
    L_004B70:
        a = myMapper->readCPU(0x0069);
        opAND(0x10);
    } while (!flgZ);
    opDEC(0x002D, 1);
    if (!flgN) {
        goto L_004B7E;
    }
    myMapper->writeCPU(0x002D, 0x04);
L_004B7E:
    a = myMapper->readCPU(0x002D);
    goto L_004B67;
}

void game::SUB_004BBC() {
    pushAddress(0x004BBC);
    SUB_003E8D();
    if (poppedEntry.value != 0x004BBC) return;
    pushAddress(0x004BBF);
    SUB_000390();
    if (poppedEntry.value != 0x004BBF) return;
    pushAddress(0x004BC2);
    SUB_0010FD();
    if (poppedEntry.value != 0x004BC2) return;
    pushAddress(0x004BC5);
    SUB_000EC4();
    if (poppedEntry.value != 0x004BC5) return;
    pushAddress(0x004BC8);
    SUB_000EF1();
    if (poppedEntry.value != 0x004BC8) return;
    a = 0x0F;
    pushAddress(0x004BCD);
    SUB_001465();
    if (poppedEntry.value != 0x004BCD) return;
    pushAddress(0x004BD0);
    SUB_00127B();
    if (poppedEntry.value != 0x004BD0) return;
    myMapper->writeCPU(0x0010, 0xA5);
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0012, 0x0F);
    myMapper->writeCPU(0x0013, 0xCB);
    pushAddress(0x004BE3);
    SUB_001152();
    if (poppedEntry.value != 0x004BE3) return;
    myMapper->writeCPU(0x0010, 0xE5);
    myMapper->writeCPU(0x0011, 0x22);
    myMapper->writeCPU(0x0012, 0x27);
    myMapper->writeCPU(0x0013, 0xCB);
    pushAddress(0x004BF6);
    SUB_001152();
    if (poppedEntry.value != 0x004BF6) return;
    myMapper->writeCPU(0x00F4, 0x05);
    myMapper->writeCPU(0x0017, 0x10);
    myMapper->writeCPU(0x0021, 0x01);
    pushAddress(0x004C05);
    SUB_0013EA();
    if (poppedEntry.value != 0x004C05) return;
    a = 0x1A;
    pushAddress(0x004C0A);
    SUB_001465();
    if (poppedEntry.value != 0x004C0A) return;
    popAddress();
}

void game::indirectJump(Uint16 target) {
    switch (target) {
    case 0x84D3:
        SUB_0004D3();
        break;
    case 0x86E5:
        SUB_0006E5();
        break;
    case 0x873D:
        SUB_00073D();
        break;
    case 0x879E:
        SUB_00079E();
        break;
    case 0x84F6:
        SUB_0004F6();
        break;
    case 0x87CF:
        SUB_0007CF();
        break;
    case 0x87E7:
        SUB_0007E7();
        break;
    case 0x8453:
        SUB_000453();
        break;
    case 0x844A:
        SUB_00044A();
        break;
    case 0x8450:
        SUB_000450();
        break;
    case 0xA3A8:
        SUB_0023A8();
        break;
    case 0xA0FB:
        SUB_0020FB();
        break;
    case 0xA7F3:
        SUB_0027F3();
        break;
    case 0xA3EC:
        SUB_0023EC();
        break;
    case 0xA46B:
        SUB_00246B();
        break;
    case 0xAB20:
        SUB_002B20();
        break;
    case 0xA612:
        SUB_002612();
        break;
    case 0xA94F:
        SUB_00294F();
        break;
    case 0xA99B:
        SUB_00299B();
        break;
    case 0xAD1A:
        SUB_002D1A();
        break;
    case 0xAE86:
        SUB_002E86();
        break;
    case 0xAAF8:
        SUB_002AF8();
        break;
    case 0xAC7B:
        SUB_002C7B();
        break;
    case 0xAF77:
        SUB_002F77();
        break;
    case 0xAEA8:
        SUB_002EA8();
        break;
    case 0xAF46:
        SUB_002F46();
        break;
    case 0xA487:
        SUB_002487();
        break;
    case 0xA510:
        SUB_002510();
        break;
    case 0xA5A4:
        SUB_0025A4();
        break;
    case 0xAD36:
        SUB_002D36();
        break;
    case 0xAD5F:
        SUB_002D5F();
        break;
    case 0xAD9E:
        SUB_002D9E();
        break;
    case 0xADB1:
        SUB_002DB1();
        break;
    }
}
