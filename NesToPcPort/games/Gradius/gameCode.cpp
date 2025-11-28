#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"
#include <stdexcept> // Add this include to resolve std::runtime_error

void game::repeat() {
}

void game::brk() {
}

void game::initGame() {
}

void game::endGame() {

}

void game::atScanline(Uint8 scanline) {
    nmi_B();
}

void game::atSprite0Hit() {
}

void game::reset() {
    flgD = false;
    flgI = true;
L_000012:
    if (!(myMapper->readCPU(0x2002) & 0x80)) {
        wait();
        goto L_000012;
    }
L_000017:
    if (!(myMapper->readCPU(0x2002) & 0x80)) {
        wait();
        goto L_000017;
    }
    pushAddress(0x00001E);
    SUB_000336();
    if (handleReturnAddress(poppedEntry.value, 0x00001E)) return;
    x = 0xFF;
    s = x;
    opINX(1);
    myMapper->writeCPU(0x0099, 0x07);
    a = x;
    myMapper->writeCPU(0x0098, x);
    y = 0xCF;
    do {
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y, a);
            opDEY(1);
        } while (!flgZ);
        opDEC(0x0099, 1);
    } while (!flgN);
    x = 0xF0;
    do {
        opCMP(x, myMapper->readCPU(0x0700 + x));
        if (!flgZ) {
            goto L_000042;
        }
        opINX(1);
    } while (!flgZ);
    if (flgZ) {
        goto L_000057;
    }
L_000042:
    a = y;
    do {
        myMapper->writeCPU(0x0700 + y, a);
        opINY(1);
    } while (!flgZ);
    x = 0xF0;
    do {
        myMapper->writeCPU(0x0700 + x, x);
        opINX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x07E1, 0x50);
L_000057:
    a = 0x00;
    myMapper->writeCPU(0x0000, a);
    myMapper->writeCPU(0x0700, a);
    pushAddress(0x000060);
    SUB_0001AB();
    if (handleReturnAddress(poppedEntry.value, 0x000060)) return;
    pushAddress(0x000063);
    SUB_0003AB();
    if (handleReturnAddress(poppedEntry.value, 0x000063)) return;
    pushAddress(0x000066);
    SUB_000510();
    if (handleReturnAddress(poppedEntry.value, 0x000066)) return;
}

void game::nmi() {
	callStack.clear();

    pushStatus();
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x2002);
    if (myMapper->readCPU(0x0004) == 0) {
        pushAddress(0x000079);
        SUB_000336();
        if (handleReturnAddress(poppedEntry.value, 0x000079)) return;
        a = 0x00;
        myMapper->writeCPU(0x2000, a);
        myMapper->writeCPU(0x2001, a);
        myMapper->writeCPU(0x2003, a);
        myMapper->writeCPU(0x4014, 0x02);
        a = myMapper->readCPU(0x0011);
        if (myMapper->readCPU(0x000D) != 0) {
            opDEC(0x000D, 1);
            if (flgZ) {
                goto L_000096;
            }
            a = 0x00;
        }
    L_000096:
        myMapper->writeCPU(0x2001, a);
        pushAddress(0x00009B);
        SUB_000A51();
        if (handleReturnAddress(poppedEntry.value, 0x00009B)) return;
        pushAddress(0x00009E);
        SUB_000281();
        if (handleReturnAddress(poppedEntry.value, 0x00009E)) return;
        opINC(0x0004, 1);
        pushAddress(0x0000A3);
        SUB_006D02();
        if (handleReturnAddress(poppedEntry.value, 0x0000A3)) return;
        pushAddress(0x0000A6);
        SUB_0001BF();
        if (handleReturnAddress(poppedEntry.value, 0x0000A6)) return;
        pushAddress(0x0000A9);
        SUB_000B10();
        if (handleReturnAddress(poppedEntry.value, 0x0000A9)) return;
        needWaitScanline = true;
        waitScanline = 212;
        return;
    }
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    return;
}


void game::nmi_B() {
    pushAddress(0x0000AC);
    SUB_0000BE();
    //if (handleReturnAddress(poppedEntry.value, 0x0000AC)) return;
    pushAddress(0x0000AF);
    SUB_000BAB();
    if (handleReturnAddress(poppedEntry.value, 0x0000AF)) return;
    pushAddress(0x0000B2);
    SUB_000641();
    if (handleReturnAddress(poppedEntry.value, 0x0000B2)) return;
    a = 0x00;
    myMapper->writeCPU(0x0004, a);
    
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    return;
}

void game::SUB_0000BE() {
    opINC(0x0002, 1);
    opCMP(myMapper->readCPU(0x0000), 0x03);
    if (!flgC) {
        a = myMapper->readCPU(0x0003);
        opAND(0x40);
        if (!flgZ) {
            goto L_0000CF;
        }
        pushAddress(0x0000CE);
        SUB_00021A();
        if (handleReturnAddress(poppedEntry.value, 0x0000CE)) return;
    }
L_0000CF:
    a = myMapper->readCPU(0x0000);
    pushAddress(0x0000D3);
    SUB_0003E4();
    if (handleReturnAddress(poppedEntry.value, 0x0000D3)) return;
    SUB_0000E2();
    return;
}

void game::SUB_0000E2() {
    if (myMapper->readCPU(0x0001) != 0) {
        goto L_0000FF;
    }
    pushAddress(0x0000E8);
    SUB_00082C();
    if (handleReturnAddress(poppedEntry.value, 0x0000E8)) return;
    pushAddress(0x0000EB);
    SUB_000256();
    if (handleReturnAddress(poppedEntry.value, 0x0000EB)) return;
    myMapper->writeCPU(0x002D, 0x03);
    a = 0x00;
    myMapper->writeCPU(0x0013, a);
    myMapper->writeCPU(0x0003, a);
    opINC(0x001F, 1);
    myMapper->writeCPU(0x0012, 0xFE);
    opINC(0x0001, 1);
    popAddress();
    return;
L_0000FF:
    a = 0x06;
    pushAddress(0x000103);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x000103)) return;
    myMapper->writeCPU(0x0120, 0x00);
    if (myMapper->readCPU(0x0012) == 0) {
        SUB_000186();
        return;
    }
    opDEC(0x0012, 2);
    SUB_000111();
    return;
}

void game::SUB_000111() {
    myMapper->writeCPU(0x002D, 0x03);
    SUB_000115();
    return;
}

void game::SUB_000115() {
    popAddress();
}

void game::SUB_000116() {
    pushAddress(0x000118);
    SUB_0002A1();
    if (handleReturnAddress(poppedEntry.value, 0x000118)) return;
    pushAddress(0x00011B);
    SUB_00019B();
    if (handleReturnAddress(poppedEntry.value, 0x00011B)) return;
    if (!flgZ) {
        SUB_000111();
        return;
    }
    SUB_000186();
    return;
}

void game::SUB_000121() {
    x = myMapper->readCPU(0x0001);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_00012A;
    }
    opINC(0x0001, 1);
    SUB_0002C7();
    return;
L_00012A:
    pushAddress(0x00012C);
    SUB_00164D();
    if (handleReturnAddress(poppedEntry.value, 0x00012C)) return;
    if (myMapper->readCPU(0x000B) == 0) {
        SUB_000115();
        return;
    }
    SUB_000131();
    return;
}

void game::SUB_000131() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0001, a);
    if (flgZ) {
        SUB_00018F();
        return;
    }
    SUB_000137();
    return;
}

void game::SUB_000137() {
    x = myMapper->readCPU(0x0001);
    setLoadFlag(x);
    if (flgZ) {
        a = 0x90;
        pushAddress(0x00013F);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x00013F)) return;
        a = 0x50;
        setLoadFlag(a);
        if (!flgZ) {
            SUB_00017D();
            return;
        }
    }
    opDEX(1);
    if (!flgZ) {
        goto L_00015F;
    }
    opDEC(0x004C, 1);
    if (flgZ) {
        SUB_00017F();
        return;
    }
    a = 0x01;
    flgC = false;
    opADC(myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x0098, a);
    a = 0x08;
    opAND(myMapper->readCPU(0x004C));
    opASL_A(4);
    opORA(myMapper->readCPU(0x0098));
    SUB_0005E8();
    return;
L_00015F:
    pushAddress(0x000161);
    SUB_0002D5();
    if (handleReturnAddress(poppedEntry.value, 0x000161)) return;
    SUB_000186();
    return;
}

void game::SUB_000165() {
    myMapper->writeCPU(0x001B, 0x00);
    SUB_000186();
    return;
}

void game::SUB_00016C() {
    pushAddress(0x00016E);
    SUB_000418();
    if (handleReturnAddress(poppedEntry.value, 0x00016E)) return;
    pushAddress(0x000171);
    SUB_000424();
    if (handleReturnAddress(poppedEntry.value, 0x000171)) return;
    a = myMapper->readCPU(0x0003);
    opAND(0x0F);
    myMapper->writeCPU(0x0003, a);
    SUB_000131();
    return;
}

void game::SUB_00017D() {
    myMapper->writeCPU(0x004C, a);
    SUB_00017F();
    return;
}

void game::SUB_00017F() {
    opINC(0x0001, 1);
    popAddress();
}

void game::SUB_000186() {
    opINC(0x0000, 1);
    SUB_000188();
    return;
}

void game::SUB_000188() {
    a = 0x00;
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_00018F() {
    myMapper->writeCPU(0x0000, a);
    a = 0x20;
    setLoadFlag(a);
    myMapper->writeCPU(0x004C, a);
    if (!flgZ) {
        SUB_000188();
        return;
    }
    x = 0x4E;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_00019D();
        return;
    }
    SUB_00019B();
    return;
}

void game::SUB_00019B() {
    x = 0x4C;
    SUB_00019D();
    return;
}

void game::SUB_00019D() {
    a = myMapper->readCPU((0x0000 + x) & 0x00ff);
    opORA(myMapper->readCPU((0x0001 + x) & 0x00ff));
    if (flgZ) {
        goto L_0001AA;
    }
    a = 0x01;
    pushAddress(0x0001A7);
    SUB_00040C();
    if (handleReturnAddress(poppedEntry.value, 0x0001A7)) return;
    a = 0x01;
    setLoadFlag(a);
L_0001AA:
    popAddress();
}

void game::SUB_0001AB() {
    myMapper->writeCPU(0x4015, 0x1F);
    myMapper->writeCPU(0x4017, 0xC0);
    SUB_0001B5();
    return;
}

void game::SUB_0001B5() {
    a = 0x88;
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x2000, a);
    SUB_0003B0();
    return;
}

void game::SUB_0001BF() {
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    y = 0x08;
    do {
        a = myMapper->readCPU(0x4016);
        myMapper->writeCPU(0x009F, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x009F));
        opLSR_A(1);
        opROL_M(0x009C, 1);
        a = myMapper->readCPU(0x4017);
        myMapper->writeCPU(0x009F, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x009F));
        opLSR_A(1);
        opROL_M(0x009D, 1);
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0005);
    opAND(0x10);
    opEOR(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0014, a);
    a = myMapper->readCPU(0x0003);
    opAND(0x20);
    if (flgZ) {
        SUB_00020B();
        return;
    }
    a = myMapper->readCPU(0x0003);
    opAND(0xF0);
    if (a == 0xE0) {
        SUB_00020F();
        return;
    }
    a = myMapper->readCPU(0x009C);
    pushAddress(0x0001FD);
    SUB_000215();
    if (handleReturnAddress(poppedEntry.value, 0x0001FD)) return;
    opINX(1);
    a = myMapper->readCPU((0x009C + x) & 0x00ff);
    SUB_000201();
    return;
}

void game::SUB_000201() {
    y = a;
    opEOR(myMapper->readCPU((0x0007 + x) & 0x00ff));
    opAND(myMapper->readCPU((0x009C + x) & 0x00ff));
    myMapper->writeCPU((0x0005 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0007 + x) & 0x00ff, y);
    popAddress();
}

void game::SUB_00020B() {
    a = 0xFF;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000211();
        return;
    }
    SUB_00020F();
    return;
}

void game::SUB_00020F() {
    a = 0x30;
    SUB_000211();
    return;
}

void game::SUB_000211() {
    opAND(myMapper->readCPU(0x009C));
    opORA(myMapper->readCPU(0x009D));
    SUB_000215();
    return;
}

void game::SUB_000215() {
    myMapper->writeCPU(0x009C, a);
    SUB_000201();
    return;
}

void game::SUB_00021A() {
    a = myMapper->readCPU(0x0005);
    opAND(0x30);
    if (!flgZ) {
        pushAddress(0x000222);
        SUB_000279();
        if (handleReturnAddress(poppedEntry.value, 0x000222)) return;
        x = myMapper->readCPU(0x0000);
        opCMP(x, 0x01);
        if (!flgZ) {
            goto L_000248;
        }
        opAND(0x20);
        if (flgZ) {
            x = myMapper->readCPU(0x000F);
            myMapper->writeCPU(0x0003, myMapper->readCPU(0x8254 + x));
            a = 0x03;
            SUB_00018F();
            return;
        }
        opINC(0x000F, 1);
        a = 0x02;
        flgC = true;
        opSBC(myMapper->readCPU(0x000F));
        if (!flgZ) {
            goto L_000244;
        }
        myMapper->writeCPU(0x000F, a);
    L_000244:
        pushAddress(0x000246);
        SUB_0002A1();
        if (handleReturnAddress(poppedEntry.value, 0x000246)) return;
    }
    popAddress();
    return;
L_000248:
    myMapper->writeCPU(0x000E, 0x00);
    pushAddress(0x00024E);
    SUB_000256();
    if (handleReturnAddress(poppedEntry.value, 0x00024E)) return;
    x = 0x01;
    myMapper->writeCPU(0x0000, x);
    popAddress();
}

void game::SUB_000256() {
    pushAddress(0x000258);
    SUB_0003AB();
    if (handleReturnAddress(poppedEntry.value, 0x000258)) return;
    myMapper->writeCPU(0x002D, 0x03);
    pushAddress(0x00025F);
    SUB_000824();
    if (handleReturnAddress(poppedEntry.value, 0x00025F)) return;
    pushAddress(0x000262);
    SUB_000418();
    if (handleReturnAddress(poppedEntry.value, 0x000262)) return;
    pushAddress(0x000265);
    SUB_000424();
    if (handleReturnAddress(poppedEntry.value, 0x000265)) return;
    a = 0x06;
    pushAddress(0x00026A);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x00026A)) return;
    myMapper->writeCPU(0x0011, 0x1E);
    myMapper->writeCPU(0x0010, 0xA8);
    pushAddress(0x000275);
    SUB_0002A1();
    if (handleReturnAddress(poppedEntry.value, 0x000275)) return;
    pushAddress(0x000278);
    SUB_0002B6();
    if (handleReturnAddress(poppedEntry.value, 0x000278)) return;
    SUB_000279();
    return;
}

void game::SUB_000279() {
    x = 0x00;
    myMapper->writeCPU(0x004C, x);
    opINX(1);
    myMapper->writeCPU(0x004D, x);
    popAddress();
}

void game::SUB_000281() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    x = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x0010));
    popAddress();
}

void game::SUB_0002A1() {
    myMapper->writeCPU(0x0360, 0x50);
    myMapper->writeCPU(0x0120, 0x01);
    x = myMapper->readCPU(0x000F);
    myMapper->writeCPU(0x0320, myMapper->readCPU(0x82B4 + x));
    popAddress();
}

void game::SUB_0002B6() {
    myMapper->writeCPU(0x00A0, 0x03);
    do {
        a = myMapper->readCPU(0x00A0);
        flgC = false;
        opADC(0x01);
        pushAddress(0x0002C1);
        SUB_0005E8();
        if (handleReturnAddress(poppedEntry.value, 0x0002C1)) return;
        opDEC(0x00A0, 1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0002C7() {
    a = myMapper->readCPU(0x000A);
    opPHA();
    pushAddress(0x0002CC);
    SUB_000307();
    if (handleReturnAddress(poppedEntry.value, 0x0002CC)) return;
    opPLA();
    myMapper->writeCPU(0x000A, a);
    opINC(0x0020, 1);
    opINC(0x0009, 1);
    popAddress();
}

void game::SUB_0002D5() {
    pushAddress(0x0002D7);
    SUB_000307();
    if (handleReturnAddress(poppedEntry.value, 0x0002D7)) return;
    x = 0x0B;
    do {
        a = 0x00;
        myMapper->writeCPU(0x07E4 + x, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0009, a);
    a = myMapper->readCPU(0x0003);
    opAND(0x02);
    if (!flgZ) {
        myMapper->writeCPU(0x001A, 0x00);
    }
    y = 0x07;
    a = myMapper->readCPU(0x0003);
    opAND(0x20);
    if (!flgZ) {
        goto L_0002F8;
    }
    y = 0x01;
L_0002F8:
    myMapper->writeCPU(0x000A, y);
    a = 0x03;
    myMapper->writeCPU(0x0020, a);
    myMapper->writeCPU(0x0021, a);
    a = 0x01;
    myMapper->writeCPU(0x002A, a);
    myMapper->writeCPU(0x002B, a);
    popAddress();
}

void game::SUB_000307() {
    x = 0x12;
    pushAddress(0x00030B);
    SUB_000336();
    if (handleReturnAddress(poppedEntry.value, 0x00030B)) return;
    a = 0x00;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opINX(1);
    } while (x != 0xF0);
    x = 0x07;
    myMapper->writeCPU(0x0099, 0x03);
    myMapper->writeCPU(0x0098, a);
    y = 0x00;
    do {
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
        } while (!flgZ);
        opINC(0x0099, 1);
        opCMP(x, myMapper->readCPU(0x0099));
    } while (!flgZ);
    pushAddress(0x00032C);
    SUB_0003B0();
    if (handleReturnAddress(poppedEntry.value, 0x00032C)) return;
    a = myMapper->readCPU(0x0010);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_000333() {
    pushAddress(0x000335);
    SUB_0003B0();
    if (handleReturnAddress(poppedEntry.value, 0x000335)) return;
    SUB_000336();
    return;
}

void game::SUB_000336() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    popAddress();
}

void game::SUB_000357() {
    y = myMapper->readCPU(0x0019);
    myMapper->writeCPU(0x002D, myMapper->readCPU(0x8346 + y));
    if (myMapper->readCPU(0x0009) != 0) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x001B);
    opAND(0x70);
    if (flgZ) {
        if (myMapper->readCPU(0x003E) != 0) {
            goto L_00039A;
        }
        a = myMapper->readCPU(0x003F);
        x = myMapper->readCPU(0x833F + y);
        if (a == myMapper->readCPU(0x834F + y)) {
            goto L_00039B;
        }
        flgC = false;
        opADC(0x01);
        opCMP(a, myMapper->readCPU(0x834F + y));
        if (!flgZ) {
            if (flgC) {
                goto L_000383;
            }
            x = 0x93;
        L_000383:
            opCMP(a, myMapper->readCPU(0x9A3D + y));
            if (!flgZ) {
                if (!flgC) {
                    goto L_00039B;
                }
                x = 0xA5;
                setLoadFlag(x);
                if (!flgZ) {
                    goto L_00039B;
                }
            }
        }
        if (myMapper->readCPU(0x001B) < 0x82) {
            if (myMapper->readCPU(0x00F0) != 0) {
                goto L_00039A;
            }
            opINC(0x00F0, 1);
        }
    }
    do {
    L_00039A:
        popAddress();
        return;
    L_00039B:
        opCMP(x, myMapper->readCPU(0x001C));
    } while (flgZ);
    SUB_00039F();
    return;
}

void game::SUB_00039F() {
    myMapper->writeCPU(0x001C, x);
    a = 0x7D;
    pushAddress(0x0003A5);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x0003A5)) return;
    a = myMapper->readCPU(0x001C);
    SUB_006C1E();
    return;
}

void game::SUB_0003AB() {
    a = 0xFC;
    SUB_006C1E();
    return;
}

void game::SUB_0003B0() {
    myMapper->writeCPU(0x000D, 0x10);
    popAddress();
}

void game::SUB_0003B5() {
    opINC(0x005D, 1);
    myMapper->writeCPU(0x0098, x);
    myMapper->writeCPU(0x0099, y);
    myMapper->writeCPU(0x009A, 0x00);
    if (!(myMapper->readCPU(0x009B) & 0x80)) {
        goto L_0003CB;
    }
    opLSR_M(0x0098, 1);
    opROR_M(0x0099, 1);
    opROR_M(0x009A, 1);
    opLSR_M(0x009B, 1);
L_0003CB:
    a = 0x00;
    x = 0x11;
    flgC = false;
    do {
        do {
            opROL_M(0x009A, 1);
            opROL_M(0x0099, 1);
            opROL_M(0x0098, 1);
            opDEX(1);
            if (flgZ) {
                goto L_0003E2;
            }
            opROL_A(1);
            opCMP(a, myMapper->readCPU(0x009B));
        } while (!flgC);
        opSBC(myMapper->readCPU(0x009B));
    } while (flgC);
L_0003E2:
    popAddress();
}

void game::SUB_0003E4() {
    opASL_A(1);
    myMapper->writeCPU(0x009B, x);
    myMapper->writeCPU(0x009A, y);
    y = a;
    opINY(1);
    opPLA();
    myMapper->writeCPU(0x0098, a);
    opPLA();
    myMapper->writeCPU(0x0099, a + 0x80);
    callStack.pop_back(); // remove current function from call stack
    x = myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0099, myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0098, x);
    y = myMapper->readCPU(0x009A);
    x = myMapper->readCPU(0x009B);
    indirectJump(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8));
}

void game::SUB_000402() {
    flgC = false;
    opADC(myMapper->readCPU((0x0000 + x) & 0x00ff));
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (!flgC) {
        goto L_00040B;
    }
    opINC((0x0001 + x) & 0x00ff, 1);
L_00040B:
    popAddress();
}

void game::SUB_00040C() {
    opEOR(0xFF);
    flgC = true;
    opADC(myMapper->readCPU((0x0000 + x) & 0x00ff));
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (flgC) {
        goto L_000417;
    }
    opDEC((0x0001 + x) & 0x00ff, 1);
L_000417:
    popAddress();
}

void game::SUB_000418() {
    a = 0x00;
    x = 0x01;
    y = 0x7F;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_000430();
        return;
    }
    y = 0xFF;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_000430();
        return;
    }
    SUB_000424();
    return;
}

void game::SUB_000424() {
    a = 0x20;
    y = 0x77;
    setLoadFlag(y);
    if (!flgZ) {
        goto L_00042E;
    }
    a = 0x30;
    y = 0x67;
L_00042E:
    x = 0x00;
    SUB_000430();
    return;
}

void game::SUB_000430() {
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(0x0099, x);
    a = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y, a);
        opDEY(1);
        opCMP(y, 0xFF);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00043F() {
    myMapper->writeCPU(0x009B, 0x01);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0099, a);
    myMapper->writeCPU(0x009A, a);
    if (flgZ) {
        SUB_00046F();
        return;
    }
    SUB_00044B();
    return;
}

void game::SUB_00044B() {
    a = 0x05;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000455();
        return;
    }
    SUB_00044F();
    return;
}

void game::SUB_00044F() {
    a = 0x03;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000455();
        return;
    }
    SUB_000453();
    return;
}

void game::SUB_000453() {
    a = 0x01;
    SUB_000455();
    return;
}

void game::SUB_000455() {
    myMapper->writeCPU(0x009A, a);
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_000469();
        return;
    }
    SUB_00045B();
    return;
}

void game::SUB_00045B() {
    myMapper->writeCPU(0x009A, 0x00);
    a = 0x50;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000469();
        return;
    }
    SUB_000463();
    return;
}

void game::SUB_000463() {
    myMapper->writeCPU(0x009A, 0x00);
    a = 0x10;
    SUB_000469();
    return;
}

void game::SUB_000469() {
    myMapper->writeCPU(0x0099, a);
    myMapper->writeCPU(0x009B, 0x00);
    SUB_00046F();
    return;
}

void game::SUB_00046F() {
    if (myMapper->readCPU(0x0009) == 0) {
        goto L_000474;
    }
    popAddress();
    return;
L_000474:
    a = 0xE4;
    if (myMapper->readCPU(0x0018) == 0) {
        goto L_00047C;
    }
    a = 0xE8;
L_00047C:
    myMapper->writeCPU(0x009C, a);
    myMapper->writeCPU(0x009D, 0x07);
    x = 0x01;
    y = 0x00;
    myMapper->writeCPU(0x0098, 0x03);
    flgC = false;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y);
        pushAddress(0x00048F);
        SUB_0004A9();
        if (handleReturnAddress(poppedEntry.value, 0x00048F)) return;
        myMapper->writeCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opINX(1);
        opDEC(0x0098, 1);
    } while (!flgZ);
    if (!flgC) {
        SUB_0004D3();
        return;
    }
    x = 0x02;
    a = 0x99;
    do {
        myMapper->writeCPU(0x07E0 + x, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0004A5() {
    myMapper->writeCPU(0x0098, x);
    x = 0x00;
    SUB_0004A9();
    return;
}

void game::SUB_0004A9() {
    myMapper->writeCPU(0x009F, a);
    opAND(0xF0);
    myMapper->writeCPU(0x009E, a);
    opEOR(myMapper->readCPU(0x009F));
    myMapper->writeCPU(0x009F, a);
    a = myMapper->readCPU((0x0098 + x) & 0x00ff);
    opAND(0x0F);
    opADC(myMapper->readCPU(0x009F));
    opCMP(a, 0x0A);
    if (flgC) {
        opADC(0x05);
    }
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x009E, a);
    a = myMapper->readCPU((0x0098 + x) & 0x00ff);
    opAND(0xF0);
    opADC(myMapper->readCPU(0x009E));
    if (flgC) {
        goto L_0004CF;
    }
    opCMP(a, 0xA0);
    if (!flgC) {
        goto L_0004D2;
    }
L_0004CF:
    opSBC(0xA0);
    flgC = true;
L_0004D2:
    popAddress();
}

void game::SUB_0004D3() {
    y = 0x02;
    a = myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y);
    x = myMapper->readCPU(0x0018);
    if (a >= myMapper->readCPU((0x002A + x) & 0x00ff)) {
        x = 0x01;
        y = myMapper->readCPU(0x0018);
        a = myMapper->readCPU(0x002A + y);
        flgC = false;
        pushAddress(0x0004E7);
        SUB_0004A5();
        if (handleReturnAddress(poppedEntry.value, 0x0004E7)) return;
        if (!flgC) {
            goto L_0004EC;
        }
        a = 0xFF;
    L_0004EC:
        x = myMapper->readCPU(0x0018);
        myMapper->writeCPU((0x002A + x) & 0x00ff, a);
        opINC((0x0020 + x) & 0x00ff, 1);
        a = 0x36;
        pushAddress(0x0004F6);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x0004F6)) return;
    }
    y = 0x02;
    do {
        opCMP(myMapper->readCPU(0x07E0 + y), myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y));
        if (!flgC) {
            goto L_000505;
        }
        if (!flgZ) {
            goto L_00050F;
        }
        opDEY(1);
    } while (!flgN);
L_000505:
    y = 0x02;
    do {
        myMapper->writeCPU(0x07E0 + y, myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgN);
L_00050F:
    popAddress();
}

void game::SUB_000510() {
    pushAddress(0x000512);
    SUB_0001BF();
    if (handleReturnAddress(poppedEntry.value, 0x000512)) return;
    a = myMapper->readCPU(0x0007);
    opAND(0xC0);
    opCMP(a, 0xC0);
    if (flgZ) {
        SUB_000523();
        return;
    }
    popAddress();
}

void game::SUB_00051C() {
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, x);
    popAddress();
}

void game::SUB_000523() {
    pushAddress(0x000525);
    SUB_00082C();
    if (handleReturnAddress(poppedEntry.value, 0x000525)) return;
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0000, a);
    myMapper->writeCPU(0x0001, a);
    myMapper->writeCPU(0x000E, a);
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, a);
    x = 0x0F;
    do {
        myMapper->writeCPU(0x00A0, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x00A1, 0x80);
    do {
        do {
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
            x = 0xA8;
            pushAddress(0x00054B);
            SUB_000402();
            if (handleReturnAddress(poppedEntry.value, 0x00054B)) return;
            opINC(0x00A0, 1);
        } while (!flgZ);
        opINC(0x00A1, 1);
    } while (!flgZ);
    y = 0x03;
    myMapper->writeCPU(0x002D, y);
    do {
        pushAddress(0x00055A);
        SUB_000A9E();
        if (handleReturnAddress(poppedEntry.value, 0x00055A)) return;
        myMapper->writeCPU(0x00A1, 0x20);
        a = 0x00;
        x = a;
        pushAddress(0x000564);
        SUB_00051C();
        if (handleReturnAddress(poppedEntry.value, 0x000564)) return;
        a = myMapper->readCPU(0x2007);
        do {
            do {
                a = myMapper->readCPU(0x2007);
                x = 0xAA;
                pushAddress(0x00056F);
                SUB_000402();
                if (handleReturnAddress(poppedEntry.value, 0x00056F)) return;
                opDEC(0x00A0, 1);
            } while (!flgZ);
            opDEC(0x00A1, 1);
        } while (!flgZ);
        opDEY(1);
    } while (!flgN);
    x = 0x02;
    do {
        opCMP(myMapper->readCPU((0x00A8 + x) & 0x00ff), myMapper->readCPU(0x85D9 + x));
        if (flgZ) {
            opCMP(myMapper->readCPU((0x00A9 + x) & 0x00ff), myMapper->readCPU(0x85DA + x));
            if (!flgZ) {
                goto L_00058F;
            }
            a = 0x00;
            setLoadFlag(a);
            if (flgZ) {
                goto L_000591;
            }
        }
    L_00058F:
        a = 0x01;
    L_000591:
        myMapper->writeCPU((0x00A0 + x) & 0x00ff, a);
        opDEX(2);
    } while (!flgN);
    a = 0x06;
    pushAddress(0x00059B);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x00059B)) return;
    a = 0x23;
    flgC = false;
    opADC(myMapper->readCPU(0x00A0));
    pushAddress(0x0005A3);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0005A3)) return;
    a = 0x25;
    flgC = false;
    opADC(myMapper->readCPU(0x00A2));
    pushAddress(0x0005AB);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0005AB)) return;
    myMapper->writeCPU(0x0700 + x, 0x00);
    pushAddress(0x0005B3);
    SUB_000A51();
    if (handleReturnAddress(poppedEntry.value, 0x0005B3)) return;
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2001, 0x09);
    myMapper->writeCPU(0x0098, 0x0A);
    do {
        x = 0x00;
        do {
            y = 0x00;
            do {
                opDEY(1);
            } while (!flgZ);
            opDEX(1);
        } while (!flgZ);
        opDEC(0x0098, 1);
    } while (!flgZ);
    SUB_0001B5();
    return;
}

void game::SUB_0005E8() {
    opPHA();
    myMapper->writeCPU(0x009B, 0x02);
    a = 0x01;
    pushAddress(0x0005F1);
    SUB_000645();
    if (handleReturnAddress(poppedEntry.value, 0x0005F1)) return;
    opPLA();
    SUB_0005F3();
    return;
}

void game::SUB_0005F3() {
    myMapper->writeCPU(0x009A, a);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x864E + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x864F + x));
    x = myMapper->readCPU(0x000E);
    y = 0x00;
    do {
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opCMP(a, 0xFF);
            if (flgZ) {
                SUB_00064B();
                return;
            }
            opCMP(a, 0xFE);
            if (flgZ) {
                goto L_000629;
            }
            opCMP(a, 0xFD);
            if (flgZ) {
                goto L_00062D;
            }
            myMapper->writeCPU(0x0700 + x, a);
            if (myMapper->readCPU(0x009A) & 0x80) {
                a = myMapper->readCPU(0x009B);
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_000624;
                }
                myMapper->writeCPU(0x0700 + x, a);
                if (flgZ) {
                    goto L_000626;
                }
            L_000624:
                opDEC(0x009B, 1);
            }
        L_000626:
            opINX(1);
        } while (!flgZ);
    L_000629:
        a = 0xFF;
        setLoadFlag(a);
        if (!flgZ) {
            SUB_000647();
            return;
        }
    L_00062D:
        a = 0xFF;
        pushAddress(0x000631);
        SUB_000647();
        if (handleReturnAddress(poppedEntry.value, 0x000631)) return;
        myMapper->writeCPU(0x009B, 0x02);
        a = 0x01;
        pushAddress(0x00063A);
        SUB_000647();
        if (handleReturnAddress(poppedEntry.value, 0x00063A)) return;
    } while (!flgZ);
    SUB_00063D();
    return;
}

void game::SUB_00063D() {
    a = 0xFF;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000645();
        return;
    }
    SUB_000641();
    return;
}

void game::SUB_000641() {
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_000645();
        return;
    }
    SUB_000645();
    return;
}

void game::SUB_000645() {
    x = myMapper->readCPU(0x000E);
    SUB_000647();
    return;
}

void game::SUB_000647() {
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    SUB_00064B();
    return;
}

void game::SUB_00064B() {
    myMapper->writeCPU(0x000E, x);
    popAddress();
}

void game::SUB_000824() {
    myMapper->writeCPU(0x002D, 0x03);
    x = 0x02;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_00082E();
        return;
    }
    SUB_00082C();
    return;
}

void game::SUB_00082C() {
    x = 0x00;
    SUB_00082E();
    return;
}

void game::SUB_00082E() {
    myMapper->writeCPU(0x009B, myMapper->readCPU(0x8893 + x));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x8894 + x));
    pushAddress(0x00083A);
    SUB_000333();
    if (handleReturnAddress(poppedEntry.value, 0x00083A)) return;
    a = 0x00;
    myMapper->writeCPU(0x000E, a);
    myMapper->writeCPU(0x001F, a);
    myMapper->writeCPU(0x0013, a);
    myMapper->writeCPU(0x0012, a);
    x = 0x20;
    y = 0x00;
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, x);
    myMapper->writeCPU(0x2006, y);
    myMapper->writeCPU(0x0098, 0x00);
    while (true) {
        y = myMapper->readCPU(0x0098);
        opCMP(y, 0x0C);
        if (flgZ) {
            goto L_00086E;
        }
        myMapper->writeCPU(0x0099, myMapper->readCPU(myMapper->readCPU(0x009B) + (myMapper->readCPU((0x009B + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x009A, myMapper->readCPU(myMapper->readCPU(0x009B) + (myMapper->readCPU((0x009B + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0098, y);
        pushAddress(0x00086A);
        SUB_000871();
        if (handleReturnAddress(poppedEntry.value, 0x00086A)) return;
    }
L_00086E:
    SUB_0001B5();
    return;
}

void game::SUB_000871() {
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0099) + (myMapper->readCPU((0x0099 + 1) & 0x00ff) << 8) + y);
        if (a == 0x34) {
            goto L_000884;
        }
        if (a == 0x39) {
            goto L_000883;
        }
        myMapper->writeCPU(0x2007, a);
    L_000880:
        opINY(1);
    } while (!flgZ);
L_000883:
    popAddress();
    return;
L_000884:
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0099) + (myMapper->readCPU((0x0099 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    x = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0099) + (myMapper->readCPU((0x0099 + 1) & 0x00ff) << 8) + y);
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    if (flgZ) {
        goto L_000880;
    }
    flgI = true;
    myMapper->writeCPU(0x8C8C, y);
    popAddress();
}

void game::SUB_000898() {
    opCMP(myMapper->readCPU(0x000E), 0x04);
    if (!flgC) {
        goto L_00089F;
    }
    do {
        popAddress();
        return;
    L_00089F:
        a = myMapper->readCPU(0x0002);
        opLSR_A(1);
    } while (!flgC);
    opINC(0x0048, 1);
    a = myMapper->readCPU(0x0048);
    opAND(0x03);
    pushAddress(0x0008AC);
    SUB_0003E4();
    if (handleReturnAddress(poppedEntry.value, 0x0008AC)) return;
    SUB_0008B6();
    return;
}

void game::SUB_0008B6() {
    myMapper->writeCPU(0x009A, 0x1E);
    a = 0x11;
    pushAddress(0x0008BE);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0008BE)) return;
    x = myMapper->readCPU(0x0018);
    a = myMapper->readCPU((0x0020 + x) & 0x00ff);
    setLoadFlag(a);
    if (flgN) {
        a = 0x00;
    }
    x = 0x00;
    do {
        myMapper->writeCPU(0x0098, a);
        opCMP(a, 0x0A);
        if (!flgC) {
            goto L_0008D9;
        }
        opSBC(0x0A);
        opINX(1);
    } while (x < 0x0A);
    x = 0x09;
    a = x;
L_0008D9:
    y = myMapper->readCPU(0x000E);
    opORA(0x30);
    opCMP(x, 0x00);
    if (flgZ) {
        opCMP(a, 0x30);
        if (flgZ) {
            goto L_0008F0;
        }
    }
    myMapper->writeCPU(0x06FE + y, a);
    a = x;
    setLoadFlag(a);
    if (flgZ) {
        goto L_0008F0;
    }
    opORA(0x30);
    myMapper->writeCPU(0x06FD + y, a);
L_0008F0:
    myMapper->writeCPU(0x06FC + y, 0x61);
    popAddress();
}

void game::SUB_0008F6() {
    a = 0x12;
    pushAddress(0x0008FA);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0008FA)) return;
    y = 0x02;
    do {
        a = myMapper->readCPU(0x07E0 + y);
        pushAddress(0x000902);
        SUB_000915();
        if (handleReturnAddress(poppedEntry.value, 0x000902)) return;
        opDEY(1);
    } while (!flgN);
    SUB_000906();
    return;
}

void game::SUB_000906() {
    myMapper->writeCPU(0x0700 + x, 0x30);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x000E, x);
    popAddress();
}

void game::SUB_000915() {
    myMapper->writeCPU(0x0098, a);
    opLSR_A(4);
    opORA(0x30);
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    a = myMapper->readCPU(0x0098);
    opAND(0x0F);
    opORA(0x30);
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    popAddress();
}

void game::SUB_00092C() {
    a = 0x13;
    flgC = false;
    opADC(myMapper->readCPU(0x0018));
    pushAddress(0x000933);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x000933)) return;
    y = 0x02;
    do {
        if (myMapper->readCPU(0x0018) == 0) {
            goto L_000940;
        }
        a = myMapper->readCPU(0x07E8 + y);
        goto L_000943;
    L_000940:
        a = myMapper->readCPU(0x07E4 + y);
    L_000943:
        pushAddress(0x000945);
        SUB_000915();
        if (handleReturnAddress(poppedEntry.value, 0x000945)) return;
        opDEY(1);
    } while (!flgN);
    if (flgN) {
        SUB_000906();
        return;
    }
    SUB_00094B();
    return;
}

void game::SUB_00094B() {
    opINC(0x0042, 1);
    opCMP(myMapper->readCPU(0x0042), 0x07);
    if (flgC) {
        pushAddress(0x000955);
        SUB_004E89();
        if (handleReturnAddress(poppedEntry.value, 0x000955)) return;
        if (flgZ) {
            a = 0x04;
            myMapper->writeCPU(0x0035, a);
        }
        opCMP(a, 0x05);
        if (!flgZ) {
            goto L_000965;
        }
        a = 0x10;
        pushAddress(0x000964);
        SUB_000455();
        if (handleReturnAddress(poppedEntry.value, 0x000964)) return;
    L_000965:
        myMapper->writeCPU(0x0042, 0x01);
    }
    pushAddress(0x00096B);
    SUB_00045B();
    if (handleReturnAddress(poppedEntry.value, 0x00096B)) return;
    a = 0x0D;
    pushAddress(0x000970);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x000970)) return;
    SUB_000A30();
    return;
}

void game::SUB_000974() {
    opCMP(myMapper->readCPU(0x0100), 0x01);
    if (!flgZ) {
        SUB_000983();
        return;
    }
    x = myMapper->readCPU(0x0018);
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x40);
    if (!flgZ) {
        SUB_000984();
        return;
    }
    SUB_000983();
    return;
}

void game::SUB_000983() {
    popAddress();
}

void game::SUB_000984() {
    a = myMapper->readCPU(0x0042);
    pushAddress(0x000988);
    SUB_0003E4();
    if (handleReturnAddress(poppedEntry.value, 0x000988)) return;
    SUB_0009A1();
    return;
}

void game::SUB_0009A1() {
    opINC(0x0040, 1);
    myMapper->writeCPU(0x0042, 0x00);
    a = 0x0E;
    pushAddress(0x0009AB);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x0009AB)) return;
    SUB_000A30();
    return;
}

void game::SUB_0009AF() {
    if (myMapper->readCPU(0x0041) != 0) {
        SUB_000983();
        return;
    }
    opINC(0x0041, 1);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0042, a);
    if (flgZ) {
        SUB_0009DD();
        return;
    }
    SUB_0009BB();
    return;
}

void game::SUB_0009BB() {
    a = 0x02;
    SUB_0009BD();
    return;
}

void game::SUB_0009BD() {
    myMapper->writeCPU(0x0098, a);
    opCMP(myMapper->readCPU(0x0044), myMapper->readCPU(0x0098));
    if (flgZ) {
        SUB_000983();
        return;
    }
    myMapper->writeCPU(0x0044, myMapper->readCPU(0x0098));
    SUB_0009C9();
    return;
}

void game::SUB_0009C9() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0042, a);
    if (flgZ) {
        SUB_0009DD();
        return;
    }
    SUB_0009CF();
    return;
}

void game::SUB_0009CF() {
    a = 0x01;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_0009BD();
        return;
    }
    SUB_0009D3();
    return;
}

void game::SUB_0009D3() {
    opCMP(myMapper->readCPU(0x0045), 0x02);
    if (flgC) {
        SUB_000983();
        return;
    }
    opINC(0x0045, 1);
    if (!flgZ) {
        SUB_0009C9();
        return;
    }
    SUB_0009DD();
    return;
}

void game::SUB_0009DD() {
    a = 0x0E;
    pushAddress(0x0009E1);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x0009E1)) return;
    popAddress();
}

void game::SUB_0009E3() {
    opCMP(myMapper->readCPU(0x0100), 0x02);
    if (flgC) {
        popAddress();
        return;
    }
    a = 0x0F;
    pushAddress(0x0009EF);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0009EF)) return;
    a = 0x15;
    if (myMapper->readCPU(0x0041) != 0) {
        a = 0x19;
    }
    pushAddress(0x0009FA);
    SUB_0005F3();
    if (handleReturnAddress(poppedEntry.value, 0x0009FA)) return;
    a = 0x16;
    if (myMapper->readCPU(0x0044) == 0x02) {
        a = 0x19;
    }
    pushAddress(0x000A07);
    SUB_0005F3();
    if (handleReturnAddress(poppedEntry.value, 0x000A07)) return;
    a = 0x17;
    if (myMapper->readCPU(0x0044) == 0x01) {
        a = 0x19;
    }
    pushAddress(0x000A14);
    SUB_0005F3();
    if (handleReturnAddress(poppedEntry.value, 0x000A14)) return;
    a = 0x18;
    if (myMapper->readCPU(0x0045) >= 0x02) {
        a = 0x19;
    }
    pushAddress(0x000A21);
    SUB_0005F3();
    if (handleReturnAddress(poppedEntry.value, 0x000A21)) return;
    a = 0x1B;
    if (myMapper->readCPU(0x0046) == 0) {
        goto L_000A2A;
    }
    a = 0x19;
L_000A2A:
    pushAddress(0x000A2C);
    SUB_0005F3();
    if (handleReturnAddress(poppedEntry.value, 0x000A2C)) return;
    pushAddress(0x000A2F);
    SUB_00063D();
    if (handleReturnAddress(poppedEntry.value, 0x000A2F)) return;
    SUB_000A30();
    return;
}

void game::SUB_000A30() {
    a = 0x1A;
    pushAddress(0x000A34);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x000A34)) return;
    if (myMapper->readCPU(0x0042) == 0) {
        goto L_000A4B;
    }
    a = 0x08;
    flgC = true;
    opSBC(myMapper->readCPU(0x0042));
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(myMapper->readCPU(0x0098));
    x = a;
    myMapper->writeCPU(0x0700 + x, 0x55);
L_000A4B:
    popAddress();
}

void game::SUB_000A51() {
    y = 0x00;
    do {
        if (myMapper->readCPU(0x0700 + y) == 0) {
            goto L_000A76;
        }
        a = myMapper->readCPU(0x0010);
        opAND(0x18);
        opORA(myMapper->readCPU(0x8A4B + x));
        myMapper->writeCPU(0x2000, a);
        opINY(1);
        a = myMapper->readCPU(0x2002);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0700 + y));
        opINY(1);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0700 + y));
        opINY(1);
        if (!flgZ) {
            goto L_000A8B;
        }
    L_000A76:
        a = 0x00;
        myMapper->writeCPU(0x0700, a);
        myMapper->writeCPU(0x000E, a);
        pushAddress(0x000A7F);
        SUB_000A9C();
        if (handleReturnAddress(poppedEntry.value, 0x000A7F)) return;
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0010));
        popAddress();
        return;
        do {
            a = 0xFF;
            do {
                myMapper->writeCPU(0x2007, a);
            L_000A8B:
                a = myMapper->readCPU(0x0700 + y);
                opINY(1);
            } while (a != 0xFF);
            opCMP(myMapper->readCPU(0x0700 + y), 0x03);
        } while (flgC);
    } while (!flgC);
    SUB_000A9C();
    return;
}

void game::SUB_000A9C() {
    y = myMapper->readCPU(0x002D);
    SUB_000A9E();
    return;
}

void game::SUB_000A9E() {
    a = myMapper->readCPU(0x8AA8 + y);
    myMapper->writeCPU(0x8AA8 + y, a);
    myMapper->writeCPU(0x8AA8 + y, a);
    popAddress();
}

void game::SUB_000AAC() {
    opASL_A(1);
    if (!flgC) {
        y = a;
        x = myMapper->readCPU(0x8D9E + y);
        a = myMapper->readCPU(0x8D9F + y);
    }
    else {
        y = a;
        x = myMapper->readCPU(0x8E9E + y);
        a = myMapper->readCPU(0x8E9F + y);
    }
    myMapper->writeCPU(0x00A0, x);
    myMapper->writeCPU(0x00A1, a);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_000B02;
    }
    opINY(1);
    myMapper->writeCPU(0x009B, a);
    x = myMapper->readCPU(0x009C);
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        flgC = false;
        opADC(myMapper->readCPU(0x0099));
        myMapper->writeCPU(0x0200 + x, a);
        a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x0201 + x, a);
        a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
        opORA(myMapper->readCPU(0x009E));
        opINY(1);
        myMapper->writeCPU(0x0202 + x, a);
        flgC = false;
        a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgN) {
            goto L_000B03;
        }
        opADC(myMapper->readCPU(0x009A));
        if (flgC) {
            goto L_000AFB;
        }
    L_000AEF:
        myMapper->writeCPU(0x0203 + x, a);
        a = x;
        do {
            flgC = false;
            opADC(0xC4);
        } while (flgZ);
        x = a;
        opDEC(0x009F, 1);
    L_000AFB:
        opINY(1);
        opDEC(0x009B, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x009C, x);
L_000B02:
    popAddress();
    return;
L_000B03:
    opADC(myMapper->readCPU(0x009A));
    goto L_000AEF;
}

void game::SUB_000B10() {
    myMapper->writeCPU(0x009F, 0x3E);
    a = 0x00;
    x = 0x03;
    myMapper->writeCPU(0x009D, a);
    y = myMapper->readCPU(0x001F);
    setLoadFlag(y);
    if (!flgZ) {
        x = 0x07;
        opDEY(1);
        if (flgZ) {
            y = 0x02;
            setLoadFlag(y);
            myMapper->writeCPU(0x001F, y);
            if (!flgZ) {
                goto L_000B2B;
            }
        }
        a = 0x01;
    }
L_000B2B:
    myMapper->writeCPU(0x001E, a);
    y = 0x03;
    do {
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x8B08 + x));
        opDEX(1);
        opDEY(1);
    } while (!flgN);
    a = myMapper->readCPU(0x002F);
    flgC = false;
    opADC(0x44);
    if (!flgZ) {
        goto L_000B43;
    }
    flgC = false;
    opADC(0x04);
L_000B43:
    myMapper->writeCPU(0x002F, a);
    myMapper->writeCPU(0x009C, a);
    do {
        x = myMapper->readCPU(0x009D);
        if (x >= 0x20) {
            goto L_000B8D;
        }
        if (myMapper->readCPU(0x0120 + x) != 0) {
            myMapper->writeCPU(0x009E, myMapper->readCPU(0x0180 + x));
            myMapper->writeCPU(0x0099, myMapper->readCPU(0x0320 + x));
            myMapper->writeCPU(0x009A, myMapper->readCPU(0x0360 + x));
            a = myMapper->readCPU(0x0120 + x);
            pushAddress(0x000B66);
            SUB_000AAC();
            if (handleReturnAddress(poppedEntry.value, 0x000B66)) return;
            if (myMapper->readCPU(0x009D) == 0) {
                y = myMapper->readCPU(0x0046);
                setLoadFlag(y);
                if (!flgZ) {
                    a = myMapper->readCPU(0x001B);
                    opAND(0x70);
                    if (flgZ) {
                        if (y != 0x01) {
                            goto L_000B7D;
                        }
                        myMapper->writeCPU(0x009E, 0x03);
                    L_000B7D:
                        a = myMapper->readCPU(0x0002);
                        opLSR_A(2);
                        opAND(0x03);
                        flgC = false;
                        opADC(0x5A);
                        pushAddress(0x000B88);
                        SUB_000AAC();
                        if (handleReturnAddress(poppedEntry.value, 0x000B88)) return;
                    }
                }
            }
        }
        opINC(0x009D, 1);
    } while (!flgZ);
L_000B8D:
    opCMP(myMapper->readCPU(0x0019), 0x04);
    if (flgZ) {
        SUB_000BD9();
        return;
    }
    SUB_000B93();
    return;
}

void game::SUB_000B93() {
    x = myMapper->readCPU(0x009C);
    myMapper->writeCPU(0x0036, x);
    a = myMapper->readCPU(0x009F);
    setLoadFlag(a);
    if (!flgN) {
        opCMP(a, 0x14);
        if (!flgC) {
            goto L_000BA8;
        }
        opSBC(0x14);
        y = a;
        a = 0x13;
        setLoadFlag(a);
        myMapper->writeCPU(0x0037, a);
        if (!flgZ) {
            SUB_000BAF();
            return;
        }
    }
L_000BA8:
    myMapper->writeCPU(0x0037, a);
    popAddress();
}

void game::SUB_000BAB() {
    y = myMapper->readCPU(0x0037);
    setLoadFlag(y);
    if (flgN) {
        SUB_000BC2();
        return;
    }
    SUB_000BAF();
    return;
}

void game::SUB_000BAF() {
    x = myMapper->readCPU(0x0036);
    do {
        myMapper->writeCPU(0x0200 + x, 0xF4);
        a = x;
        do {
            flgC = false;
            opADC(0xC4);
        } while (flgZ);
        x = a;
        opDEY(1);
    } while (!flgN);
    myMapper->writeCPU(0x0036, x);
    SUB_000BC2();
    return;
}

void game::SUB_000BC2() {
    popAddress();
}

void game::SUB_000BC3() {
    a = myMapper->readCPU(0x0037);
    setLoadFlag(a);
    if (flgN) {
        goto L_000BCB;
    }
    opCMP(a, 0x12);
    if (flgC) {
        goto L_000BD1;
    }
L_000BCB:
    x = 0x59;
    do {
        opDEX(1);
    } while (!flgZ);
    popAddress();
    return;
L_000BD1:
    opSBC(0x12);
    myMapper->writeCPU(0x0037, a);
    y = 0x11;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_000BAF();
        return;
    }
    SUB_000BD9();
    return;
}

void game::SUB_000BD9() {
    myMapper->writeCPU(0x00A8, 0x90);
    do {
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0600 + x) == 0) {
            goto L_000BE7;
        }
        pushAddress(0x000BE6);
        SUB_000C06();
        if (handleReturnAddress(poppedEntry.value, 0x000BE6)) return;
    L_000BE7:
        a = myMapper->readCPU(0x00A8);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x00A8, a);
    } while (!flgN);
    if (flgN) {
        SUB_000B93();
        return;
    }
    opSBC(myMapper->readCPU(0xFBFB + x));
    opSBC(myMapper->readCPU(0xFBF9 + y));
    //NOP
    SUB_000C06();
    return;
}

void game::SUB_000C06() {
    myMapper->writeCPU(0x00AA, 0x05);
    y = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x00A9, y);
    a = myMapper->readCPU(0x0615 + y);
    opLSR_A(2);
    opAND(0x0F);
    x = a;
    opLSR_A(2);
    y = a;
    myMapper->writeCPU(0x00AB, myMapper->readCPU(0x8BF2 + x));
    myMapper->writeCPU(0x00AC, myMapper->readCPU(0x8C02 + y));
    do {
        y = myMapper->readCPU(0x00A9);
        x = myMapper->readCPU(0x009C);
        a = myMapper->readCPU(0x0618 + y);
        setLoadFlag(a);
        if (!flgZ) {
            opCMP(a, 0xF4);
            if (!flgC) {
                myMapper->writeCPU(0x0203 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0620 + y));
                a = 0xF7;
                y = myMapper->readCPU(0x00AA);
                setLoadFlag(y);
                if (flgZ) {
                    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(0x00AB));
                    a = myMapper->readCPU(0x00AC);
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0202 + x, a);
                    if (!flgN) {
                        goto L_000C65;
                    }
                    a = myMapper->readCPU(0x0200 + x);
                    flgC = true;
                    opSBC(0x08);
                    myMapper->writeCPU(0x0200 + x, a);
                }
                else {
                    myMapper->writeCPU(0x0201 + x, a);
                    a = 0x01;
                    if (y != 0x03) {
                        goto L_000C62;
                    }
                    a = 0x02;
                L_000C62:
                    myMapper->writeCPU(0x0202 + x, a);
                }
            L_000C65:
                a = x;
                do {
                    flgC = false;
                    opADC(0xC4);
                } while (flgZ);
                myMapper->writeCPU(0x009C, a);
                opDEC(0x009F, 1);
                if (flgN) {
                    goto L_000C77;
                }
            }
        }
        opINC(0x00A9, 1);
        opDEC(0x00AA, 1);
    } while (!flgN);
L_000C77:
    popAddress();
}

void game::SUB_00164D() {
    pushAddress(0x00164F);
    SUB_001C6D();
    if (handleReturnAddress(poppedEntry.value, 0x00164F)) return;
    SUB_001650();
    return;
}

void game::SUB_001650() {
    myMapper->writeCPU(0x0013, 0x0C);
    a = 0x00;
    myMapper->writeCPU(0x005D, a);
    myMapper->writeCPU(0x005B, a);
    myMapper->writeCPU(0x005C, a);
    if (myMapper->readCPU(0x0015) != 0) {
        SUB_001A8C();
        return;
    }
    opCMP(myMapper->readCPU(0x0019), 0x04);
    if (flgZ) {
        x = 0x00;
        if (myMapper->readCPU(0x0600) != 0) {
            opINX(1);
        }
        if (myMapper->readCPU(0x0630) != 0) {
            opINX(1);
        }
        if (myMapper->readCPU(0x0660) != 0) {
            opINX(1);
        }
        if (myMapper->readCPU(0x0690) != 0) {
            opINX(1);
        }
        myMapper->writeCPU(0x005C, x);
        opCMP(x, 0x02);
        if (flgC) {
            a = myMapper->readCPU(0x0002);
            opLSR_A(1);
            if (flgC) {
                pushAddress(0x001690);
                SUB_0022C0();
                if (handleReturnAddress(poppedEntry.value, 0x001690)) return;
                pushAddress(0x001693);
                SUB_004B91();
                if (handleReturnAddress(poppedEntry.value, 0x001693)) return;
                pushAddress(0x001696);
                SUB_002DAB();
                if (handleReturnAddress(poppedEntry.value, 0x001696)) return;
                pushAddress(0x001699);
                SUB_003BB7();
                if (handleReturnAddress(poppedEntry.value, 0x001699)) return;
                pushAddress(0x00169C);
                SUB_001FFC();
                if (handleReturnAddress(poppedEntry.value, 0x00169C)) return;
                pushAddress(0x00169F);
                SUB_0040C7();
                if (handleReturnAddress(poppedEntry.value, 0x00169F)) return;
                opINC(0x005B, 1);
                SUB_001A8C();
                return;
            }
        }
    }
    a = 0x10;
    opAND(myMapper->readCPU(0x001B));
    if (flgZ) {
        a = 0x20;
        opAND(myMapper->readCPU(0x001B));
        if (!flgZ) {
            goto L_0016EF;
        }
        a = 0x40;
        opAND(myMapper->readCPU(0x001B));
        if (!flgZ) {
            goto L_0016FB;
        }
        a = myMapper->readCPU(0x001B);
        setLoadFlag(a);
        if (flgN) {
            SUB_00182A();
            return;
        }
        x = 0x03;
        myMapper->writeCPU(0x000D, x);
        pushAddress(0x0016C4);
        SUB_0003E4();
        if (handleReturnAddress(poppedEntry.value, 0x0016C4)) return;
    }
    x = myMapper->readCPU(0x001B);
    opINC(0x0019, 1);
    a = 0x00;
    myMapper->writeCPU(0x0039, a);
    myMapper->writeCPU(0x003A, a);
    myMapper->writeCPU(0x003F, a);
    x = 0x20;
    do {
        myMapper->writeCPU((0x0050 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0055, 0x01);
    pushAddress(0x0016E8);
    SUB_001BF0();
    if (handleReturnAddress(poppedEntry.value, 0x0016E8)) return;
    pushAddress(0x0016EB);
    SUB_001C3C();
    if (handleReturnAddress(poppedEntry.value, 0x0016EB)) return;
    SUB_001A5E();
    return;
L_0016EF:
    if (myMapper->readCPU(0x004C) == 0) {
        SUB_00179D();
        return;
    }
    opDEC(0x004C, 1);
    SUB_001A5E();
    return;
L_0016FB:
    opINC(0x005B, 1);
    if (myMapper->readCPU(0x00B0) == 0) {
        a = myMapper->readCPU(0x000A);
        opAND(0x03);
        if (flgZ) {
            a = myMapper->readCPU(0x0005);
            opAND(0x10);
            if (!flgZ) {
                pushAddress(0x00170F);
                SUB_0002D5();
                if (handleReturnAddress(poppedEntry.value, 0x00170F)) return;
                myMapper->writeCPU(0x0000, 0x04);
                popAddress();
                return;
            }
        }
        if (myMapper->readCPU(0x004C) == 0) {
            x = myMapper->readCPU(0x0018);
            y = myMapper->readCPU(0x0033);
            opCMP(y, 0x0A);
            if (!flgZ) {
                goto L_00174B;
            }
            myMapper->writeCPU((0x0020 + x) & 0x00ff, 0x03);
            myMapper->writeCPU((0x002A + x) & 0x00ff, 0x01);
            a = myMapper->readCPU(0x9749 + x);
            opORA(myMapper->readCPU(0x000A));
            myMapper->writeCPU(0x000A, a);
            myMapper->writeCPU((0x0024 + x) & 0x00ff, 0x00);
            a = x;
            opASL_A(2);
            x = a;
            a = 0x00;
            myMapper->writeCPU(0x07E4 + x, a);
            myMapper->writeCPU(0x07E5 + x, a);
            myMapper->writeCPU(0x07E6 + x, a);
            myMapper->writeCPU(0x07E7 + x, a);
            SUB_0017DD();
            return;
        L_00174B:
            a = myMapper->readCPU(0x000A);
            opAND(0x03);
            if (!flgZ) {
                SUB_0017C5();
                return;
            }
            pushAddress(0x001753);
            SUB_001B3E();
            if (handleReturnAddress(poppedEntry.value, 0x001753)) return;
            a = 0x00;
            myMapper->writeCPU(0x0000, a);
            myMapper->writeCPU(0x001B, a);
            popAddress();
            return;
        }
        opDEC(0x004C, 1);
    }
    x = 0x00;
    pushAddress(0x001761);
    SUB_001765();
    if (handleReturnAddress(poppedEntry.value, 0x001761)) return;
    SUB_001A5E();
    return;
}

void game::SUB_001765() {
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x9785 + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x9786 + x));
    x = myMapper->readCPU(0x0018);
    y = myMapper->readCPU(0x0033);
    setLoadFlag(y);
    if (!flgN) {
        a = myMapper->readCPU((0x0005 + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y)) {
                goto L_001781;
            }
            y = 0x00;
            setLoadFlag(y);
            if (flgZ) {
                goto L_001782;
            }
        L_001781:
            opINY(1);
        L_001782:
            myMapper->writeCPU(0x0033, y);
        }
    }
    popAddress();
}

void game::SUB_00179D() {
    x = myMapper->readCPU(0x0018);
    opDEC((0x0020 + x) & 0x00ff, 1);
    x = myMapper->readCPU(0x0018);
    a = 0x00;
    y = myMapper->readCPU(0x0042);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0x01;
    }
    myMapper->writeCPU((0x0022 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0026 + x) & 0x00ff, myMapper->readCPU(0x0019));
    a = myMapper->readCPU(0x003F);
    opAND(0x0E);
    if (a < 0x08) {
        goto L_0017BB;
    }
    a = 0x08;
L_0017BB:
    myMapper->writeCPU((0x0024 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0028 + x) & 0x00ff, myMapper->readCPU(0x001A));
    if (myMapper->readCPU((0x0020 + x) & 0x00ff) & 0x80) {
        SUB_0017F1();
        return;
    }
    SUB_0017C5();
    return;
}

void game::SUB_0017C5() {
    x = myMapper->readCPU(0x0018);
    a = myMapper->readCPU(0x000A);
    opCMP(x, 0x01);
    if (flgZ) {
        opAND(0x01);
        if (flgZ) {
            goto L_0017DB;
        }
        x = 0x00;
        setLoadFlag(x);
        if (flgZ) {
            goto L_0017DB;
        }
    }
    opAND(0x02);
    if (flgZ) {
        goto L_0017DB;
    }
    x = 0x01;
L_0017DB:
    myMapper->writeCPU(0x0018, x);
    SUB_0017DD();
    return;
}

void game::SUB_0017DD() {
    a = 0x00;
    myMapper->writeCPU(0x0039, a);
    myMapper->writeCPU(0x003A, a);
    myMapper->writeCPU(0x005D, a);
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x001B, a);
    myMapper->writeCPU(0x001C, a);
    pushAddress(0x0017ED);
    SUB_001C09();
    if (handleReturnAddress(poppedEntry.value, 0x0017ED)) return;
    SUB_001B3E();
    return;
}

void game::SUB_0017F1() {
    a = 0xFE;
    opCMP(x, 0x00);
    if (!flgZ) {
        a = 0xFD;
    }
    opAND(myMapper->readCPU(0x000A));
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x001B, 0xC0);
    if (myMapper->readCPU(0x0009) == 0) {
        goto L_00180E;
    }
    myMapper->writeCPU(0x000D, 0x05);
    opINC(0x000B, 1);
    SUB_001C09();
    return;
L_00180E:
    a = 0x1C;
    pushAddress(0x001812);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x001812)) return;
    a = myMapper->readCPU(0x0018);
    flgC = false;
    opADC(0x31);
    myMapper->writeCPU(0x06EC + x, a);
    pushAddress(0x00181D);
    SUB_0003AB();
    if (handleReturnAddress(poppedEntry.value, 0x00181D)) return;
    a = 0xAF;
    pushAddress(0x001822);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x001822)) return;
    myMapper->writeCPU(0x004C, 0x78);
    SUB_001A5E();
    return;
}

void game::SUB_00182A() {
    a = myMapper->readCPU(0x001B);
    pushAddress(0x00182E);
    SUB_0003E4();
    if (handleReturnAddress(poppedEntry.value, 0x00182E)) return;
    SUB_00184F();
    return;
}

void game::SUB_00184F() {
    myMapper->writeCPU(0x002D, 0x01);
    x = 0x3E;
    a = 0x04;
    pushAddress(0x001859);
    SUB_000402();
    if (handleReturnAddress(poppedEntry.value, 0x001859)) return;
    opCMP(myMapper->readCPU(0x003F), 0x11);
    if (flgC) {
        a = myMapper->readCPU(0x001B);
        opAND(0x70);
        if (!flgZ) {
            goto L_00186F;
        }
        a = 0x50;
        pushAddress(0x00186A);
        SUB_000455();
        if (handleReturnAddress(poppedEntry.value, 0x00186A)) return;
        myMapper->writeCPU(0x001B, 0x90);
    }
L_00186F:
    SUB_001A5E();
    return;
}

void game::SUB_001872() {
    opINC(0x001B, 1);
    x = myMapper->readCPU(0x0018);
    a = 0x00;
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU((0x0026 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0024 + x) & 0x00ff, a);
    y = myMapper->readCPU(0x0042);
    setLoadFlag(y);
    if (flgZ) {
        goto L_001887;
    }
    a = 0x01;
L_001887:
    myMapper->writeCPU((0x0022 + x) & 0x00ff, a);
    opINC((0x0028 + x) & 0x00ff, 1);
    popAddress();
}

void game::SUB_00188C() {
    if (myMapper->readCPU(0x0057) != 0) {
        goto L_001893;
    }
    SUB_001C24();
    return;
L_001893:
    myMapper->writeCPU(0x00A8, 0x09);
    pushAddress(0x001899);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x001899)) return;
    opDEC(0x00A8, 1);
    pushAddress(0x00189E);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x00189E)) return;
    myMapper->writeCPU(0x0315, 0x28);
    myMapper->writeCPU(0x0335, 0x88);
    myMapper->writeCPU(0x0375, 0xA4);
    myMapper->writeCPU(0x0334, 0x80);
    myMapper->writeCPU(0x0374, 0x74);
    myMapper->writeCPU(0x0134, 0x9E);
    a = 0x00;
    myMapper->writeCPU(0x0120, a);
    myMapper->writeCPU(0x0100, a);
    opINC(0x001B, 1);
    myMapper->writeCPU(0x0100, 0x03);
    a = 0xE8;
    pushAddress(0x0018D0);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x0018D0)) return;
    opINC(0x001F, 1);
    a = 0x21;
    pushAddress(0x0018D7);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0018D7)) return;
    a = 0x05;
    SUB_0005E8();
    return;
}

void game::SUB_0018DD() {
    opINC(0x005B, 1);
    pushAddress(0x0018E1);
    SUB_002DAB();
    if (handleReturnAddress(poppedEntry.value, 0x0018E1)) return;
    SUB_001A8C();
    return;
}

void game::SUB_0018E5() {
    opINC(0x005B, 1);
    myMapper->writeCPU(0x001B, 0x00);
    SUB_001B3E();
    return;
}

void game::SUB_0018EE() {
    a = 0x80;
    flgC = false;
    opADC(myMapper->readCPU(0x003D));
    myMapper->writeCPU(0x003D, a);
    a = 0x00;
    opROL_A(1);
    x = 0x3E;
    SUB_000402();
    return;
}

void game::SUB_001904() {
    a = myMapper->readCPU(0x0019);
    opCMP(a, 0x06);
    if (flgZ) {
        SUB_001872();
        return;
    }
    opCMP(a, 0x05);
    if (flgZ) {
        pushAddress(0x001913);
        SUB_004DA5();
        if (handleReturnAddress(poppedEntry.value, 0x001913)) return;
    }
    if (myMapper->readCPU(0x00B2) == 0) {
        x = 0x93;
        pushAddress(0x00191C);
        SUB_00039F();
        if (handleReturnAddress(poppedEntry.value, 0x00191C)) return;
    }
    if (myMapper->readCPU(0x001C) == 0x93) {
        pushAddress(0x001925);
        SUB_00194A();
        if (handleReturnAddress(poppedEntry.value, 0x001925)) return;
    }
    y = myMapper->readCPU(0x0019);
    if (myMapper->readCPU(0x003F) >= myMapper->readCPU(0x98FD + y)) {
        a = myMapper->readCPU(0x001B);
        opAND(0x70);
        if (flgZ) {
            a = 0x90;
            if (myMapper->readCPU(0x0039) == 0) {
                goto L_001945;
            }
            opINC(0x0019, 1);
            opINC(0x003A, 1);
            myMapper->writeCPU(0x003F, 0x00);
            a = 0x8E;
        L_001945:
            myMapper->writeCPU(0x001B, a);
        }
    }
    SUB_001A5E();
    return;
}

void game::SUB_00194A() {
    if (myMapper->readCPU(0x003E) < 0xD0) {
        goto L_00197D;
    }
    x = myMapper->readCPU(0x005E);
    setLoadFlag(x);
    if (!flgN) {
        opDEC(0x005E, 1);
        a = 0x00;
        myMapper->writeCPU(0x0600 + x, a);
        myMapper->writeCPU(0x0640 + x, a);
        myMapper->writeCPU(0x0680 + x, a);
        myMapper->writeCPU(0x06C0 + x, a);
        myMapper->writeCPU(0x0500 + x, a);
        myMapper->writeCPU(0x0540 + x, a);
        myMapper->writeCPU(0x0580 + x, a);
        myMapper->writeCPU(0x05C0 + x, a);
        if (x >= 0x14) {
            goto L_00197D;
        }
        myMapper->writeCPU(0x010C + x, a);
        myMapper->writeCPU(0x012C + x, a);
        myMapper->writeCPU(0x030C + x, a);
    }
L_00197D:
    popAddress();
}

void game::SUB_00197E() {
    opINC(0x005B, 1);
    if (!flgZ) {
        SUB_0019B7();
        return;
    }
    SUB_001982();
    return;
}

void game::SUB_001982() {
    x = myMapper->readCPU(0x0019);
    opCMP(myMapper->readCPU(0x003F), myMapper->readCPU(0x9A3D + x));
    if (flgZ) {
        SUB_0019BA();
        return;
    }
    a = 0x1E;
    pushAddress(0x00198F);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x00198F)) return;
    a = 0x05;
    pushAddress(0x001994);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x001994)) return;
    myMapper->writeCPU(0x002D, 0x01);
    myMapper->writeCPU(0x00A8, 0x09);
    pushAddress(0x00199F);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x00199F)) return;
    myMapper->writeCPU(0x0315, 0x98);
    myMapper->writeCPU(0x0335, 0x80);
    myMapper->writeCPU(0x0375, 0xF0);
    opINC(0x005B, 1);
    opINC(0x001B, 1);
    myMapper->writeCPU(0x005E, 0x3F);
    SUB_0019B7();
    return;
}

void game::SUB_0019B7() {
    SUB_001A5E();
    return;
}

void game::SUB_0019BA() {
    pushAddress(0x0019BC);
    SUB_00194A();
    if (handleReturnAddress(poppedEntry.value, 0x0019BC)) return;
    SUB_001A5E();
    return;
}

void game::SUB_0019C0() {
    opINC(0x001B, 1);
    opCMP(myMapper->readCPU(0x0019), 0x05);
    if (flgC) {
        if (!flgZ) {
            goto L_0019CF;
        }
        a = 0xAC;
        pushAddress(0x0019CE);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x0019CE)) return;
    L_0019CF:
        myMapper->writeCPU(0x001B, 0x86);
    }
    opINC(0x005B, 1);
    myMapper->writeCPU(0x0062, 0x02);
    pushAddress(0x0019DB);
    SUB_0019DF();
    if (handleReturnAddress(poppedEntry.value, 0x0019DB)) return;
    SUB_001A5E();
    return;
}

void game::SUB_0019DF() {
    x = 0x0C;
    a = 0x00;
    do {
        myMapper->writeCPU((0x0063 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0019E9() {
    opINC(0x005B, 1);
    x = 0x4C;
    a = 0x01;
    pushAddress(0x0019F1);
    SUB_00040C();
    if (handleReturnAddress(poppedEntry.value, 0x0019F1)) return;
    a = myMapper->readCPU(0x004C);
    opORA(myMapper->readCPU(0x004D));
    if (!flgZ) {
        SUB_001A5E();
        return;
    }
    myMapper->writeCPU(0x0060, a);
    opINC(0x001B, 1);
    a = myMapper->readCPU(0x0019);
    setLoadFlag(a);
    if (!flgZ) {
        opCMP(a, 0x03);
        if (flgZ) {
            goto L_001A06;
        }
        if (!flgZ) {
            SUB_001A5E();
            return;
        }
    }
L_001A06:
    a = 0x3F;
    pushAddress(0x001A0A);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x001A0A)) return;
    SUB_001A5E();
    return;
}

void game::SUB_001A0E() {
    x = myMapper->readCPU(0x0017);
    if (myMapper->readCPU(0x0019) != 0x06) {
        goto L_001A1E;
    }
    myMapper->writeCPU(0x004D, 0x01);
    a = 0xCA;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_001A25;
    }
L_001A1E:
    myMapper->writeCPU(0x004D, myMapper->readCPU(0x9A35 + x));
    a = 0x00;
L_001A25:
    myMapper->writeCPU(0x004C, a);
    opINC(0x005B, 1);
    opINC(0x001B, 1);
    myMapper->writeCPU(0x0062, 0x01);
    pushAddress(0x001A31);
    SUB_0019DF();
    if (handleReturnAddress(poppedEntry.value, 0x001A31)) return;
    SUB_001A5B();
    return;
}

void game::SUB_001A4D() {
    x = myMapper->readCPU(0x0019);
    if (myMapper->readCPU(0x003F) < myMapper->readCPU(0x9A3D + x)) {
        SUB_001A5B();
        return;
    }
    myMapper->writeCPU(0x001B, myMapper->readCPU(0x9A45 + x));
    SUB_001A5B();
    return;
}

void game::SUB_001A5B() {
    pushAddress(0x001A5D);
    SUB_000357();
    if (handleReturnAddress(poppedEntry.value, 0x001A5D)) return;
    SUB_001A5E();
    return;
}

void game::SUB_001A5E() {
    opCMP(myMapper->readCPU(0x005C), 0x02);
    if (flgC) {
        goto L_001A70;
    }
    pushAddress(0x001A66);
    SUB_0022C0();
    if (handleReturnAddress(poppedEntry.value, 0x001A66)) return;
    pushAddress(0x001A69);
    SUB_003BB7();
    if (handleReturnAddress(poppedEntry.value, 0x001A69)) return;
    pushAddress(0x001A6C);
    SUB_001FFC();
    if (handleReturnAddress(poppedEntry.value, 0x001A6C)) return;
    pushAddress(0x001A6F);
    SUB_002DAB();
    if (handleReturnAddress(poppedEntry.value, 0x001A6F)) return;
L_001A70:
    pushAddress(0x001A72);
    SUB_003FE2();
    if (handleReturnAddress(poppedEntry.value, 0x001A72)) return;
    pushAddress(0x001A75);
    SUB_000974();
    if (handleReturnAddress(poppedEntry.value, 0x001A75)) return;
    pushAddress(0x001A78);
    SUB_004772();
    if (handleReturnAddress(poppedEntry.value, 0x001A78)) return;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x003E));
    a = myMapper->readCPU(0x003F);
    opLSR_A(1);
    a = myMapper->readCPU(0x0010);
    opAND(0xFC);
    opADC(0x00);
    myMapper->writeCPU(0x0010, a);
    if (!(myMapper->readCPU(0x001B) & 0x80)) {
        SUB_001AC4();
        return;
    }
    SUB_001A8C();
    return;
}

void game::SUB_001A8C() {
    if (myMapper->readCPU(0x001E) == 0) {
        SUB_001AC4();
        return;
    }
    if (myMapper->readCPU(0x001F) == 0) {
        SUB_001AC4();
        return;
    }
    if (myMapper->readCPU(0x000D) != 0) {
        SUB_001AC4();
        return;
    }
    if (myMapper->readCPU(0x0015) == 0) {
        if (myMapper->readCPU(0x005B) != 0) {
            goto L_001AA3;
        }
        pushAddress(0x001AA2);
        SUB_0018EE();
        if (handleReturnAddress(poppedEntry.value, 0x001AA2)) return;
    }
    do {
    L_001AA3:
        a = myMapper->readCPU(0x2002);
        opAND(0x40);
    } while (flgZ);
    pushAddress(0x001AAC);
    SUB_000BC3();
    if (handleReturnAddress(poppedEntry.value, 0x001AAC)) return;
    a = myMapper->readCPU(0x2002);
    x = 0x00;
    myMapper->writeCPU(0x2005, x);
    myMapper->writeCPU(0x2005, x);
    a = myMapper->readCPU(0x0010);
    opAND(0xFC);
    myMapper->writeCPU(0x2000, a);
    y = 0x02;
    pushAddress(0x001AC3);
    SUB_000A9E();
    if (handleReturnAddress(poppedEntry.value, 0x001AC3)) return;
    SUB_001AC4();
    return;
}

void game::SUB_001AC4() {
    pushAddress(0x001AC6);
    SUB_001C45();
    if (handleReturnAddress(poppedEntry.value, 0x001AC6)) return;
    pushAddress(0x001AC9);
    SUB_000898();
    if (handleReturnAddress(poppedEntry.value, 0x001AC9)) return;
    if (myMapper->readCPU(0x005B) == 0) {
        pushAddress(0x001AD0);
        SUB_001D83();
        if (handleReturnAddress(poppedEntry.value, 0x001AD0)) return;
    }
    a = myMapper->readCPU(0x001B);
    setLoadFlag(a);
    if (flgN) {
        opAND(0x70);
        if (flgZ) {
            goto L_001ADA;
        }
    }
    popAddress();
    return;
L_001ADA:
    a = myMapper->readCPU(0x0009);
    opORA(myMapper->readCPU(0x0016));
    opORA(myMapper->readCPU(0x000D));
    if (flgZ) {
        a = myMapper->readCPU(0x0005);
        y = myMapper->readCPU(0x0015);
        setLoadFlag(y);
        if (flgZ) {
            opAND(0x10);
            if (flgZ) {
                goto L_001B3D;
            }
            myMapper->writeCPU(0x0015, 0x01);
            x = 0x10;
            do {
                myMapper->writeCPU(0x01A0 + x, myMapper->readCPU((0x00B0 + x) & 0x00ff));
                opDEX(1);
            } while (!flgN);
            a = 0x3B;
            SUB_006C1E();
            return;
        }
        x = myMapper->readCPU(0x0018);
        if (!(myMapper->readCPU((0x003B + x) & 0x00ff) & 0x80)) {
            x = 0x02;
            pushAddress(0x001B09);
            SUB_001765();
            if (handleReturnAddress(poppedEntry.value, 0x001B09)) return;
            opCMP(myMapper->readCPU(0x0033), 0x0A);
            if (flgZ) {
                pushAddress(0x001B12);
                SUB_001C5E();
                if (handleReturnAddress(poppedEntry.value, 0x001B12)) return;
                x = myMapper->readCPU(0x0018);
                opDEC((0x003B + x) & 0x00ff, 1);
                myMapper->writeCPU(0x0033, 0x00);
            }
        }
        a = myMapper->readCPU(0x0005);
        opAND(0x10);
        if (flgZ) {
            goto L_001B3D;
        }
        a = 0x00;
        myMapper->writeCPU(0x0015, a);
        opINC(0x005B, 1);
        myMapper->writeCPU(0x00B2, a);
        myMapper->writeCPU(0x4000, 0x30);
        myMapper->writeCPU(0x4008, myMapper->readCPU(0x00D7));
        x = 0x10;
        do {
            myMapper->writeCPU((0x00B0 + x) & 0x00ff, myMapper->readCPU(0x01A0 + x));
            opDEX(1);
        } while (!flgN);
    }
L_001B3D:
    popAddress();
}

void game::SUB_001B3E() {
    x = 0x5A;
    a = 0x00;
    do {
        myMapper->writeCPU((0x003D + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    x = 0x7F;
    do {
        myMapper->writeCPU(0x0100 + x, a);
        myMapper->writeCPU(0x0300 + x, a);
        myMapper->writeCPU(0x0500 + x, a);
        myMapper->writeCPU(0x0580 + x, a);
        myMapper->writeCPU(0x0600 + x, a);
        myMapper->writeCPU(0x0680 + x, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0035, 0x14);
    x = myMapper->readCPU(0x0018);
    myMapper->writeCPU(0x0042, myMapper->readCPU((0x0022 + x) & 0x00ff));
    a = myMapper->readCPU((0x0024 + x) & 0x00ff);
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x0055, a);
    myMapper->writeCPU(0x0019, myMapper->readCPU((0x0026 + x) & 0x00ff));
    myMapper->writeCPU(0x001A, myMapper->readCPU((0x0028 + x) & 0x00ff));
    opINC(0x001B, 1);
    pushAddress(0x001B7A);
    SUB_00082C();
    if (handleReturnAddress(poppedEntry.value, 0x001B7A)) return;
    myMapper->writeCPU(0x0011, 0x1E);
    myMapper->writeCPU(0x0010, 0xA8);
    myMapper->writeCPU(0x0120, 0x01);
    y = myMapper->readCPU(0x0019);
    a = myMapper->readCPU(0x003F);
    opLSR_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x9BCC + y));
    y = a;
    a = myMapper->readCPU(0x9BD4 + y);
    opAND(0xF0);
    myMapper->writeCPU(0x0320, a);
    myMapper->writeCPU(0x0321, a);
    myMapper->writeCPU(0x0322, a);
    x = 0x1F;
    do {
        myMapper->writeCPU(0x07C0 + x, a);
        opDEX(1);
    } while (!flgN);
    a = myMapper->readCPU(0x9BD4 + y);
    opASL_A(4);
    myMapper->writeCPU(0x0360, a);
    myMapper->writeCPU(0x0361, a);
    myMapper->writeCPU(0x0362, a);
    x = 0x1F;
    do {
        myMapper->writeCPU(0x07A0 + x, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0100, 0x01);
    myMapper->writeCPU(0x000D, 0x06);
    SUB_0003AB();
    return;
}

void game::SUB_001BED() {
    pushAddress(0x001BEF);
    SUB_0003AB();
    if (handleReturnAddress(poppedEntry.value, 0x001BEF)) return;
    SUB_001BF0();
    return;
}

void game::SUB_001BF0() {
    a = 0x10;
    pushAddress(0x001BF4);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x001BF4)) return;
    a = myMapper->readCPU(0x0019);
    flgC = false;
    opADC(0x08);
    pushAddress(0x001BFC);
    SUB_0005F3();
    if (handleReturnAddress(poppedEntry.value, 0x001BFC)) return;
    a = 0x07;
    pushAddress(0x001C01);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x001C01)) return;
    a = 0x05;
    pushAddress(0x001C06);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x001C06)) return;
    opINC(0x001B, 1);
    SUB_001C09();
    return;
}

void game::SUB_001C09() {
    myMapper->writeCPU(0x0057, 0x00);
    myMapper->writeCPU(0x005E, 0x3F);
    popAddress();
}

void game::SUB_001C12() {
    pushAddress(0x001C14);
    SUB_0008B6();
    if (handleReturnAddress(poppedEntry.value, 0x001C14)) return;
    pushAddress(0x001C17);
    SUB_0008F6();
    if (handleReturnAddress(poppedEntry.value, 0x001C17)) return;
    pushAddress(0x001C1A);
    SUB_00092C();
    if (handleReturnAddress(poppedEntry.value, 0x001C1A)) return;
    opINC(0x001B, 1);
    popAddress();
}

void game::SUB_001C1E() {
    pushAddress(0x001C20);
    SUB_0009E3();
    if (handleReturnAddress(poppedEntry.value, 0x001C20)) return;
    opINC(0x001B, 1);
    popAddress();
}

void game::SUB_001C24() {
    myMapper->writeCPU(0x000D, 0x05);
    if (myMapper->readCPU(0x0057) != 0) {
        goto L_001C38;
    }
    pushAddress(0x001C2E);
    SUB_001D8E();
    if (handleReturnAddress(poppedEntry.value, 0x001C2E)) return;
    pushAddress(0x001C31);
    SUB_001D8E();
    if (handleReturnAddress(poppedEntry.value, 0x001C31)) return;
    pushAddress(0x001C34);
    SUB_001D8E();
    if (handleReturnAddress(poppedEntry.value, 0x001C34)) return;
    SUB_001D8E();
    return;
L_001C38:
    myMapper->writeCPU(0x001F, 0x01);
    SUB_001C3C();
    return;
}

void game::SUB_001C3C() {
    myMapper->writeCPU(0x0060, 0x01);
    myMapper->writeCPU(0x001B, 0x80);
    popAddress();
}

void game::SUB_001C45() {
    y = 0x00;
    x = myMapper->readCPU(0x0044);
    setLoadFlag(x);
    if (!flgZ) {
        opINY(1);
    }
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x0045));
    y = a;
    if (myMapper->readCPU(0x0046) != 0) {
        opINY(1);
    }
    if (myMapper->readCPU(0x0019) == 0) {
        goto L_001C5B;
    }
    opINY(1);
L_001C5B:
    myMapper->writeCPU(0x0017, y);
    popAddress();
}

void game::SUB_001C5E() {
    myMapper->writeCPU(0x0046, 0x05);
    a = 0x01;
    myMapper->writeCPU(0x0041, a);
    myMapper->writeCPU(0x0040, a);
    myMapper->writeCPU(0x0045, 0x02);
    popAddress();
}

void game::SUB_001C6D() {
    if (myMapper->readCPU(0x001B) & 0x80) {
        goto L_001C72;
    }
    popAddress();
    return;
L_001C72:
    y = myMapper->readCPU(0x0031);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_001C79;
    }
    pushAddress(0x001C78);
    SUB_001C5E();
    if (handleReturnAddress(poppedEntry.value, 0x001C78)) return;
L_001C79:
    a = myMapper->readCPU(0x0005);
    opAND(0x30);
    if (!flgZ) {
        SUB_001CB1();
        return;
    }
    a = myMapper->readCPU(0x0002);
    opLSR_A(1);
    if (flgC) {
        SUB_001C96();
        return;
    }
    y = myMapper->readCPU(0x0031);
    setLoadFlag(y);
    if (flgZ) {
        SUB_001CB0();
        return;
    }
    SUB_001C88();
    return;
}

void game::SUB_001C88() {
    a = myMapper->readCPU(0x9CB5 + y);
    myMapper->writeCPU(0x0005, a);
    myMapper->writeCPU(0x0007, a);
    a = 0x00;
    myMapper->writeCPU(0x0008, a);
    myMapper->writeCPU(0x0006, a);
    popAddress();
}

void game::SUB_001C96() {
    y = myMapper->readCPU(0x0031);
    setLoadFlag(y);
    if (flgZ) {
        goto L_001C9E;
    }
    if (myMapper->readCPU(0x0030) != 0) {
        goto L_001CAB;
    }
L_001C9E:
    a = myMapper->readCPU(0x9CB8 + y);
    myMapper->writeCPU(0x0030, a);
    opCMP(a, 0xFF);
    if (flgZ) {
        SUB_001CB1();
        return;
    }
    opINY(2);
    myMapper->writeCPU(0x0031, y);
L_001CAB:
    pushAddress(0x001CAD);
    SUB_001C88();
    if (handleReturnAddress(poppedEntry.value, 0x001CAD)) return;
    opDEC(0x0030, 1);
    SUB_001CB0();
    return;
}

void game::SUB_001CB0() {
    popAddress();
}

void game::SUB_001CB1() {
    opINC(0x000B, 1);
    pushAddress(0x001CB5);
    SUB_0003AB();
    if (handleReturnAddress(poppedEntry.value, 0x001CB5)) return;
    popAddress();
}

void game::SUB_001D83() {
    if (myMapper->readCPU(0x003A) != 0) {
        goto L_001D8D;
    }
    opCMP(myMapper->readCPU(0x000E), 0x04);
    if (!flgC) {
        SUB_001D8E();
        return;
    }
L_001D8D:
    popAddress();
}

void game::SUB_001D8E() {
    myMapper->writeCPU(0x0057, 0x00);
    if (myMapper->readCPU(0x0058) == 0) {
        a = myMapper->readCPU(0x0054);
        flgC = true;
        opSBC(myMapper->readCPU(0x003E));
        myMapper->writeCPU(0x0098, a);
        a = myMapper->readCPU(0x0055);
        opSBC(myMapper->readCPU(0x003F));
        if (!flgN) {
            opCMP(a, 0x01);
            if (flgC) {
                if (!flgZ) {
                    goto L_001DAF;
                }
                opCMP(myMapper->readCPU(0x0098), 0x80);
                if (!flgC) {
                    goto L_001DB2;
                }
            L_001DAF:
                opINC(0x0057, 1);
                popAddress();
                return;
            }
        }
    }
L_001DB2:
    a = myMapper->readCPU(0x0055);
    opAND(0x01);
    x = a;
    myMapper->writeCPU(0x00A9, myMapper->readCPU(0x9D6D + x));
    a = myMapper->readCPU(0x9D6F + x);
    myMapper->writeCPU(0x00AB, a);
    opORA(0x03);
    myMapper->writeCPU(0x00AD, a);
    a = myMapper->readCPU(0x0054);
    flgC = false;
    opADC(myMapper->readCPU(0x0058));
    myMapper->writeCPU(0x00A8, a);
    a = 0x00;
    if (myMapper->readCPU(0x0054) & 0x80) {
        a = 0x10;
    }
    myMapper->writeCPU(0x00AA, a);
    opLSR_A(2);
    opORA(0xC0);
    myMapper->writeCPU(0x00AC, a);
    a = myMapper->readCPU(0x0058);
    opAND(0x07);
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(0x0099, a);
    a = 0x00;
    opLSR_M(0x0098, 1);
    opROR_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x00AA));
    myMapper->writeCPU(0x00AA, a);
    a = myMapper->readCPU(0x00AB);
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x00AB, a);
    a = myMapper->readCPU(0x0058);
    opAND(0xF8);
    opLSR_A(3);
    flgC = false;
    myMapper->writeCPU(0x009A, a);
    opADC(myMapper->readCPU(0x00AA));
    myMapper->writeCPU(0x00AA, a);
    a = myMapper->readCPU(0x00AB);
    opADC(0x00);
    myMapper->writeCPU(0x00AB, a);
    a = myMapper->readCPU(0x0099);
    opASL_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x00AC));
    myMapper->writeCPU(0x00AC, a);
    a = myMapper->readCPU(0x009A);
    opLSR_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x00AC));
    myMapper->writeCPU(0x00AC, a);
    a = myMapper->readCPU(0x0058);
    opAND(0xF0);
    opLSR_A(5);
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x0058);
    opAND(0x07);
    opASL_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    if (myMapper->readCPU(0x0054) & 0x80) {
        opADC(0x04);
    }
    myMapper->writeCPU(0x00AE, a);
    a = myMapper->readCPU(0x0019);
    opASL_A(1);
    myMapper->writeCPU(0x0098, a);
    x = a;
    myMapper->writeCPU(0x00A0, myMapper->readCPU(0x9FBC + x));
    myMapper->writeCPU(0x00A1, myMapper->readCPU(0x9FBD + x));
    y = myMapper->readCPU(0x0055);
    a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
    if (x != 0x00) {
        opCMP(a, 0x00);
        if (flgZ) {
            x = 0x00;
            a = 0x01;
        }
        opSBC(0x01);
    }
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0x9D4F + y);
    flgC = false;
    opADC(myMapper->readCPU(0x9FCC + x));
    myMapper->writeCPU(0x00A0, a);
    a = myMapper->readCPU(0x9D50 + y);
    opADC(myMapper->readCPU(0x9FCD + x));
    myMapper->writeCPU(0x00A1, a);
    y = myMapper->readCPU(0x00AE);
    myMapper->writeCPU(0x00AE, myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x9FDC + x));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x9FDD + x));
    a = myMapper->readCPU(0x00AE);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00A4, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x00A5, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x00A6, myMapper->readCPU(0x9FEC + x));
    myMapper->writeCPU(0x00A7, myMapper->readCPU(0x9FED + x));
    a = 0x01;
    x = myMapper->readCPU(0x000E);
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x00AD));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x00AC));
    opINX(1);
    y = myMapper->readCPU(0x00AE);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(myMapper->readCPU(0x00A6) + (myMapper->readCPU((0x00A6 + 1) & 0x00ff) << 8) + y));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x00AF, x);
    myMapper->writeCPU(0x009A, 0xF0);
    y = 0x00;
    myMapper->writeCPU(0x0098, 0x04);
    while (true) {
        myMapper->writeCPU(0x0099, 0x04);
        myMapper->writeCPU(0x0700 + x, 0x01);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x00AB));
        opINX(1);
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x00AA));
        opINX(1);
        a = 0x20;
        flgC = false;
        opADC(myMapper->readCPU(0x00AA));
        myMapper->writeCPU(0x00AA, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x00AB));
        myMapper->writeCPU(0x00AB, a);
        do {
            do {
                a = myMapper->readCPU(myMapper->readCPU(0x00A4) + (myMapper->readCPU((0x00A4 + 1) & 0x00ff) << 8) + y);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_001F37;
                }
                opBIT(myMapper->readCPU(0x009A));
                if (!flgZ) {
                    goto L_001F37;
                }
                opINY(1);
                myMapper->writeCPU(0x009B, y);
                if (a != 0x07) {
                    if (a == 0x08) {
                        goto L_001F16;
                    }
                    if (a != 0x09) {
                        opCMP(a, 0x0A);
                        if (!flgZ) {
                            if (!flgZ) {
                                goto L_001F26;
                            }
                        }
                    }
                    opAND(0x01);
                    opORA(0x40);
                    do {
                        myMapper->writeCPU(0x0700 + x, a);
                        opEOR(0x01);
                        opINX(1);
                        opDEC(0x0099, 1);
                    } while (!flgZ);
                    if (flgZ) {
                        goto L_001F32;
                    }
                }
                a = 0xED;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_001F18;
                }
            L_001F16:
                a = 0x00;
            L_001F18:
                myMapper->writeCPU(0x0700 + x, a);
                opINX(1);
                myMapper->writeCPU(0x0700 + x, a);
                opDEC(0x0099, 2);
                opINX(1);
            } while (!flgZ);
        L_001F26:
            y = a;
            a = myMapper->readCPU(0x9D73 + y);
            do {
                myMapper->writeCPU(0x0700 + x, a);
                opINX(1);
                opDEC(0x0099, 1);
            } while (!flgZ);
        L_001F32:
            y = myMapper->readCPU(0x009B);
            goto L_001F40;
        L_001F37:
            myMapper->writeCPU(0x0700 + x, a);
            opINY(1);
            opINX(1);
            opDEC(0x0099, 1);
        } while (!flgZ);
    L_001F40:
        myMapper->writeCPU(0x0700 + x, 0xFF);
        opINX(1);
        opDEC(0x0098, 1);
        if (flgZ) {
            goto L_001F4D;
        }
    }
L_001F4D:
    myMapper->writeCPU(0x000E, x);
    y = myMapper->readCPU(0x0019);
    if (y != 0x04) {
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x9FB4 + y));
        y = myMapper->readCPU(0x00AF);
        myMapper->writeCPU(0x009A, 0x00);
        do {
            x = 0x04;
            myMapper->writeCPU(0x0099, 0x00);
            do {
                a = myMapper->readCPU(0x0703 + y);
                if (a < myMapper->readCPU(0x0098)) {
                    goto L_001F6F;
                }
                a = 0x80;
            L_001F6F:
                opASL_A(1);
                opROR_M(0x0099, 1);
                opASL_A(1);
                opROR_M(0x0099, 1);
                a = y;
                flgC = false;
                opADC(0x08);
                y = a;
                opDEX(1);
            } while (!flgZ);
            myMapper->writeCPU(myMapper->readCPU((0x00A8 + x) & 0x00ff) + (myMapper->readCPU((0x00A8 + x + 1) & 0x00ff) << 8), myMapper->readCPU(0x0099));
            a = 0x08;
            flgC = false;
            opADC(myMapper->readCPU(0x00A8));
            myMapper->writeCPU(0x00A8, a);
            opINC(0x00AF, 1);
            y = myMapper->readCPU(0x00AF);
            opINC(0x009A, 1);
        } while (myMapper->readCPU(0x009A) < 0x04);
    }
    a = myMapper->readCPU(0x0058);
    opAND(0x07);
    opCMP(a, 0x06);
    if (!flgC) {
        goto L_001FB1;
    }
    a = 0x19;
    opADC(myMapper->readCPU(0x0058));
    myMapper->writeCPU(0x0058, a);
    opCMP(a, 0x80);
    if (!flgC) {
        goto L_001FB3;
    }
    myMapper->writeCPU(0x0058, 0x00);
    x = 0x54;
    a = 0x80;
    SUB_000402();
    return;
L_001FB1:
    opINC(0x0058, 1);
L_001FB3:
    popAddress();
}

void game::SUB_001FFC() {
    if (myMapper->readCPU(0x0100) < 0x02) {
        goto L_002006;
    }
    goto L_00216F;
L_002006:
    a = myMapper->readCPU(0x0040);
    flgC = false;
    opADC(0x02);
    if (a >= 0x10) {
        a = 0x10;
    }
    myMapper->writeCPU(0x0099, a);
    myMapper->writeCPU(0x0098, 0x00);
    opLSR_M(0x0099, 1);
    opROR_M(0x0098, 1);
    y = 0x40;
    x = myMapper->readCPU(0x0018);
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x01);
    if (!flgZ) {
        pushAddress(0x002027);
        SUB_002285();
        if (handleReturnAddress(poppedEntry.value, 0x002027)) return;
        if (a >= 0xF0) {
            a = 0xF0;
        }
        myMapper->writeCPU(0x0360, a);
    }
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x02);
    if (!flgZ) {
        pushAddress(0x002039);
        SUB_002297();
        if (handleReturnAddress(poppedEntry.value, 0x002039)) return;
        if (a < 0x10) {
            a = 0x10;
        }
        myMapper->writeCPU(0x0360, a);
    }
    a = 0x01;
    y = 0x00;
    myMapper->writeCPU(0x009B, a);
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x04);
    if (!flgZ) {
        if (myMapper->readCPU(0x0320) >= 0xC0) {
            goto L_002063;
        }
        pushAddress(0x002058);
        SUB_002285();
        if (handleReturnAddress(poppedEntry.value, 0x002058)) return;
        if (a >= 0xC0) {
            a = 0xC0;
        }
        y = 0x02;
        setLoadFlag(y);
        if (!flgZ) {
            goto L_00207B;
        }
    }
L_002063:
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x08);
    if (!flgZ) {
        if (myMapper->readCPU(0x0320) < 0x10) {
            goto L_002080;
        }
        pushAddress(0x002072);
        SUB_002297();
        if (handleReturnAddress(poppedEntry.value, 0x002072)) return;
        if (a < 0x10) {
            a = 0x10;
        }
        y = 0x03;
    L_00207B:
        myMapper->writeCPU(0x009B, y);
        myMapper->writeCPU(0x0320, a);
    }
L_002080:
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x0F);
    if (!flgZ) {
        a = myMapper->readCPU(0x0160);
        flgC = false;
        opADC(0x01);
        opCMP(a, 0x18);
        if (flgC) {
            opSBC(0x18);
        }
        myMapper->writeCPU(0x0160, a);
        y = a;
        myMapper->writeCPU(0x07A0 + y, myMapper->readCPU(0x0360));
        myMapper->writeCPU(0x07C0 + y, myMapper->readCPU(0x0320));
        y = 0x01;
        a = myMapper->readCPU(0x0160);
        pushAddress(0x0020A9);
        SUB_0022A9();
        if (handleReturnAddress(poppedEntry.value, 0x0020A9)) return;
        pushAddress(0x0020AC);
        SUB_0022A9();
        if (handleReturnAddress(poppedEntry.value, 0x0020AC)) return;
    }
    opINC(0x0140, 1);
    if (flgN) {
        myMapper->writeCPU(0x0140, 0x10);
    }
    opCMP(myMapper->readCPU(0x0140), 0x08);
    if (!flgC) {
        goto L_0020C8;
    }
    myMapper->writeCPU(0x0120, myMapper->readCPU(0x009B));
    myMapper->writeCPU(0x0140, 0x00);
L_0020C8:
    x = myMapper->readCPU(0x0045);
    do {
        opDEX(1);
        if (flgN) {
            goto L_0020E9;
        }
        opINC(0x0141 + x, 1);
        a = myMapper->readCPU(0x0141 + x);
        opLSR_A(3);
        opAND(0x01);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x0121 + x, a);
    } while (!flgZ);
    opASL_M(0x0007, 1);
    opASL_M(0x0006, 1);
    //NOP
L_0020E9:
    x = myMapper->readCPU(0x0044);
    myMapper->writeCPU(0x0098, myMapper->readCPU(0xA0E0 + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0xA0E6 + x));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0xA0E3 + x));
    x = myMapper->readCPU(0x0018);
    a = myMapper->readCPU((0x0005 + x) & 0x00ff);
    opAND(0x80);
    myMapper->writeCPU(0x009A, a);
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x80);
    myMapper->writeCPU(0x009B, a);
    x = myMapper->readCPU(0x0045);
    do {
        if (myMapper->readCPU(0x0123 + x) != 0) {
            goto L_002134;
        }
        if (myMapper->readCPU(0x009A) == 0) {
            if (myMapper->readCPU(0x03A3 + x) != 0) {
                goto L_002131;
            }
            if (myMapper->readCPU(0x009B) == 0) {
                goto L_002134;
            }
        }
        pushAddress(0x00211E);
        SUB_002235();
        if (handleReturnAddress(poppedEntry.value, 0x00211E)) return;
        myMapper->writeCPU(0x03A3 + x, myMapper->readCPU(0x0035));
        opCMP(myMapper->readCPU(0x0044), 0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x0035);
            setLoadFlag(a);
            myMapper->writeCPU(0x03A6 + x, a);
            if (!flgZ) {
                goto L_00215C;
            }
        L_002131:
            opDEC(0x03A3 + x, 1);
        }
    L_002134:
        if (myMapper->readCPU(0x0126 + x) == 0) {
            if (myMapper->readCPU(0x009A) != 0) {
                goto L_002146;
            }
            if (myMapper->readCPU(0x03A6 + x) != 0) {
                goto L_002159;
            }
            if (myMapper->readCPU(0x009B) == 0) {
                goto L_00215C;
            }
        L_002146:
            pushAddress(0x002148);
            SUB_002250();
            if (handleReturnAddress(poppedEntry.value, 0x002148)) return;
            myMapper->writeCPU(0x03A6 + x, myMapper->readCPU(0x0035));
            opCMP(myMapper->readCPU(0x0044), 0x02);
            if (!flgZ) {
                myMapper->writeCPU(0x03A3 + x, myMapper->readCPU(0x0035));
            L_002159:
                opDEC(0x03A6 + x, 1);
            }
        }
    L_00215C:
        if (myMapper->readCPU(0x0041) != 0) {
            if (myMapper->readCPU(0x0129 + x) != 0) {
                goto L_00216C;
            }
            if (myMapper->readCPU(0x009B) == 0) {
                goto L_00216C;
            }
            pushAddress(0x00216B);
            SUB_00226B();
            if (handleReturnAddress(poppedEntry.value, 0x00216B)) return;
        }
    L_00216C:
        opDEX(1);
    } while (!flgN);
L_00216F:
    myMapper->writeCPU(0x00A8, 0x08);
    do {
        y = 0x00;
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0163 + x) != 0) {
            opCMP(myMapper->readCPU(0x0019), 0x04);
            if (!flgZ) {
                pushAddress(0x002184);
                SUB_0043AF();
                if (handleReturnAddress(poppedEntry.value, 0x002184)) return;
                y = 0x00;
                if (a != 0x00) {
                    a = myMapper->readCPU(0x00A5);
                    flgC = true;
                    opSBC(0x08);
                    myMapper->writeCPU(0x00A5, a);
                    a = myMapper->readCPU(0x00A4);
                    flgC = false;
                    opADC(0x08);
                    myMapper->writeCPU(0x00A4, a);
                    pushAddress(0x00219B);
                    SUB_0043D3();
                    if (handleReturnAddress(poppedEntry.value, 0x00219B)) return;
                    if (!flgZ) {
                        goto L_0021D6;
                    }
                    y = 0x01;
                    a = 0x08;
                    setLoadFlag(a);
                    if (!flgZ) {
                        goto L_0021AC;
                    }
                    //NOP
                }
            }
            a = 0x0A;
        L_0021AC:
            myMapper->writeCPU(0x0123 + x, a);
            a = myMapper->readCPU(0xA1A4 + y);
            flgC = false;
            opADC(myMapper->readCPU(0x0323 + x));
            myMapper->writeCPU(0x0323 + x, a);
            if (a < 0xC8) {
                a = myMapper->readCPU(0xA1A8 + y);
                flgC = false;
                opADC(myMapper->readCPU(0x0383 + x));
                myMapper->writeCPU(0x0383 + x, a);
                a = myMapper->readCPU(0x0363 + x);
                opADC(myMapper->readCPU(0xA1A6 + y));
                myMapper->writeCPU(0x0363 + x, a);
                if (flgC) {
                    goto L_0021D6;
                }
                if (a < 0xF8) {
                    goto L_0021DE;
                }
            }
        L_0021D6:
            a = 0x00;
            myMapper->writeCPU(0x0123 + x, a);
            myMapper->writeCPU(0x0163 + x, a);
        }
    L_0021DE:
        opDEC(0x00A8, 1);
    } while (myMapper->readCPU(0x00A8) >= 0x06);
    x = 0x00;
    myMapper->writeCPU(0x0098, x);
    do {
        if (myMapper->readCPU(0x0123 + x) == 0) {
            goto L_00222F;
        }
        a = myMapper->readCPU(0x0163 + x);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_00220B;
        }
        a = 0x07;
        do {
            flgC = false;
            opADC(myMapper->readCPU(0x0363 + x));
            myMapper->writeCPU(0x0363 + x, a);
            if (a < 0xF8) {
                goto L_00222F;
            }
            do {
            L_002201:
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x0163 + x, a);
                myMapper->writeCPU(0x0123 + x, a);
                if (flgZ) {
                    goto L_00222F;
                }
            L_00220B:
                if (a != 0x02) {
                    goto L_002220;
                }
                a = myMapper->readCPU(0x0323 + x);
                flgC = true;
                opSBC(0x04);
                myMapper->writeCPU(0x0323 + x, a);
            } while (a < 0x10);
            a = 0x04;
            setLoadFlag(a);
        } while (!flgZ);
    L_002220:
        a = myMapper->readCPU(0x0363 + x);
        flgC = false;
        opADC(0x0C);
        myMapper->writeCPU(0x0363 + x, a);
        if (flgC) {
            goto L_002201;
        }
        if (a >= 0xF0) {
            goto L_002201;
        }
    L_00222F:
        opINX(1);
        opCMP(x, 0x06);
    } while (!flgC);
    popAddress();
}

void game::SUB_002235() {
    myMapper->writeCPU(0x0363 + x, myMapper->readCPU(0x0360 + x));
    myMapper->writeCPU(0x0323 + x, myMapper->readCPU(0x0320 + x));
    myMapper->writeCPU(0x0123 + x, myMapper->readCPU(0x0098));
    a = myMapper->readCPU(0x0044);
    opAND(0x01);
    myMapper->writeCPU(0x0163 + x, a);
    SUB_002266();
    return;
}

void game::SUB_002250() {
    myMapper->writeCPU(0x0366 + x, myMapper->readCPU(0x0360 + x));
    myMapper->writeCPU(0x0326 + x, myMapper->readCPU(0x0320 + x));
    myMapper->writeCPU(0x0126 + x, myMapper->readCPU(0x009C));
    myMapper->writeCPU(0x0166 + x, myMapper->readCPU(0x0044));
    SUB_002266();
    return;
}

void game::SUB_002266() {
    a = myMapper->readCPU(0x0099);
    SUB_006C1E();
    return;
}

void game::SUB_00226B() {
    myMapper->writeCPU(0x0369 + x, myMapper->readCPU(0x0360 + x));
    a = myMapper->readCPU(0x0320 + x);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x0329 + x, a);
    myMapper->writeCPU(0x0129 + x, 0x0A);
    myMapper->writeCPU(0x0169 + x, 0x03);
    popAddress();
}

void game::SUB_002285() {
    a = myMapper->readCPU(0x0098);
    flgC = false;
    opADC(myMapper->readCPU(0x0340 + y));
    myMapper->writeCPU(0x0340 + y, a);
    a = myMapper->readCPU(0x0099);
    opADC(myMapper->readCPU(0x0320 + y));
    myMapper->writeCPU(0x0320 + y, a);
    popAddress();
}

void game::SUB_002297() {
    a = myMapper->readCPU(0x0340 + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0340 + y, a);
    a = myMapper->readCPU(0x0320 + y);
    opSBC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0320 + y, a);
    popAddress();
}

void game::SUB_0022A9() {
    flgC = true;
    opSBC(0x0B);
    if (flgC) {
        goto L_0022B0;
    }
    opADC(0x18);
L_0022B0:
    x = a;
    myMapper->writeCPU(0x0360 + y, myMapper->readCPU(0x07A0 + x));
    myMapper->writeCPU(0x0320 + y, myMapper->readCPU(0x07C0 + x));
    opINY(1);
    a = x;
    popAddress();
}

void game::SUB_0022C0() {
    if (myMapper->readCPU(0x003A) == 0) {
        goto L_0022C7;
    }
    SUB_004413();
    return;
L_0022C7:
    x = myMapper->readCPU(0x0060);
    setLoadFlag(x);
    if (flgZ) {
        popAddress();
        return;
    }
    opDEX(1);
    if (!flgZ) {
        goto L_0022F0;
    }
    opINC(0x0060, 1);
    do {
        a = myMapper->readCPU(0x0019);
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x0098, myMapper->readCPU(0xA7D0 + y));
        myMapper->writeCPU(0x0099, myMapper->readCPU(0xA7D1 + y));
        a = myMapper->readCPU(0x003F);
        opAND(0x0E);
        myMapper->writeCPU(0x0061, a);
        y = a;
        myMapper->writeCPU(0x006A, myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x006B, myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y));
        popAddress();
        return;
    L_0022F0:
        a = myMapper->readCPU(0x001B);
        if (a == 0x81) {
            popAddress();
            return;
        }
        opCMP(a, 0x82);
        if (!flgZ) {
            goto L_0022FE;
        }
        SUB_004413();
        return;
    L_0022FE:
        if (myMapper->readCPU(0x0069) != 0) {
            goto L_00232B;
        }
        y = myMapper->readCPU(0x0061);
        opINY(2);
    } while (y == myMapper->readCPU(0x003F));
    y = 0x00;
    myMapper->writeCPU(0x0098, myMapper->readCPU(myMapper->readCPU(0x006A) + (myMapper->readCPU((0x006A + 1) & 0x00ff) << 8) + y));
    a = 0x00;
    opASL_M(0x0098, 1);
    opROL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0061));
    myMapper->writeCPU(0x0099, a);
    opCMP(myMapper->readCPU(0x003F), myMapper->readCPU(0x0099));
    if (!flgZ) {
        if (flgC) {
            goto L_002335;
        }
        if (!flgC) {
            goto L_00232A;
        }
    }
    if (myMapper->readCPU(0x003E) < myMapper->readCPU(0x0098)) {
    L_00232A:
        popAddress();
        return;
    L_00232B:
        if (myMapper->readCPU(0x006C) == 0) {
            SUB_002411();
            return;
        }
        opDEC(0x006C, 1);
        popAddress();
        return;
    }
L_002335:
    opINC(0x005D, 1);
    y = 0x00;
    myMapper->writeCPU(0x009A, y);
    myMapper->writeCPU(0x009B, y);
    x = 0x00;
    if (myMapper->readCPU(myMapper->readCPU(0x006A) + (myMapper->readCPU((0x006A + 1) & 0x00ff) << 8) + y) == 0xFF) {
        popAddress();
        return;
    }
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x006A) + (myMapper->readCPU((0x006A + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0098, a);
    if (a < 0xF0) {
        a = 0x02;
        x = 0x6A;
        pushAddress(0x002355);
        SUB_000402();
        if (handleReturnAddress(poppedEntry.value, 0x002355)) return;
        a = myMapper->readCPU(0x0098);
        setLoadFlag(a);
        if (flgN) {
            goto L_00236D;
        }
        opASL_A(1);
        flgC = false;
        opADC(myMapper->readCPU(0x0098));
        myMapper->writeCPU(0x009A, a);
        a = 0x00;
        opADC(0x00);
        myMapper->writeCPU(0x009B, a);
        y = 0x00;
        pushAddress(0x00236A);
        SUB_002397();
        if (handleReturnAddress(poppedEntry.value, 0x00236A)) return;
        if (flgN) {
            SUB_0023B1();
            return;
        }
    L_00236D:
        a = myMapper->readCPU(0x0098);
        opASL_A(2);
        myMapper->writeCPU(0x009A, a);
        y = 0x02;
        pushAddress(0x002377);
        SUB_002397();
        if (handleReturnAddress(poppedEntry.value, 0x002377)) return;
        if (flgN) {
            SUB_0023E4();
            return;
        }
    }
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x006A) + (myMapper->readCPU((0x006A + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU((0x0063 + x) & 0x00ff, a);
        opINX(1);
    } while (y < 0x05);
    a = 0x05;
    x = 0x6A;
    pushAddress(0x00238C);
    SUB_000402();
    if (handleReturnAddress(poppedEntry.value, 0x00238C)) return;
    a = myMapper->readCPU(0x0064);
    flgC = true;
    opSBC(0x70);
    myMapper->writeCPU(0x0064, a);
    SUB_002466();
    return;
}

void game::SUB_002397() {
    a = myMapper->readCPU(0xA5FE + y);
    flgC = false;
    opADC(myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x009A, a);
    a = myMapper->readCPU(0xA5FF + y);
    opADC(myMapper->readCPU(0x009B));
    myMapper->writeCPU(0x009B, a);
    y = 0x03;
    do {
        myMapper->writeCPU(0x0064 + y, myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0023B1() {
    x = 0x09;
    do {
        if (myMapper->readCPU(0x030C + x) == 0) {
            goto L_0023BC;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_0023BC:
    myMapper->writeCPU(0x00A8, x);
    pushAddress(0x0023C0);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x0023C0)) return;
    x = myMapper->readCPU(0x00A8);
    y = 0xF0;
    a = myMapper->readCPU(0x0064);
    flgC = true;
    opSBC(0xA0);
    opCMP(a, 0x30);
    if (!flgC) {
        goto L_0023D2;
    }
    y = 0x10;
    opSBC(0x30);
L_0023D2:
    myMapper->writeCPU(0x030C + x, a);
    myMapper->writeCPU(0x036C + x, y);
    a = myMapper->readCPU(0x0065);
    pushAddress(0x0023DD);
    SUB_002579();
    if (handleReturnAddress(poppedEntry.value, 0x0023DD)) return;
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0x0066));
    popAddress();
}

void game::SUB_0023E4() {
    a = myMapper->readCPU(0x0066);
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0xA592 + x);
    opAND(0x0F);
    myMapper->writeCPU(0x0069, a);
    myMapper->writeCPU(0x006F, a);
    if (a < 0x04) {
        goto L_002405;
    }
    opINC(0x0049, 1);
    a = myMapper->readCPU(0x0049);
    opAND(0x01);
    opORA(0x02);
    myMapper->writeCPU(0x0049, a);
    y = a;
    myMapper->writeCPU(0x0048 + y, myMapper->readCPU(0x0069));
L_002405:
    a = myMapper->readCPU(0xA592 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x006D, a);
    myMapper->writeCPU(0x006E, myMapper->readCPU(0xA593 + x));
    SUB_002411();
    return;
}

void game::SUB_002411() {
    opDEC(0x0069, 1);
    if (!flgN) {
        x = 0x09;
        do {
            if (myMapper->readCPU(0x030C + x) == 0) {
                goto L_002420;
            }
            opDEX(1);
        } while (!flgN);
    }
    popAddress();
    return;
L_002420:
    myMapper->writeCPU(0x00A8, x);
    pushAddress(0x002424);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x002424)) return;
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x0067);
    opASL_A(2);
    flgC = true;
    opSBC(myMapper->readCPU(0x0067));
    y = a;
    myMapper->writeCPU(0x006C, myMapper->readCPU(0xA5BC + y));
    a = myMapper->readCPU(0xA5BD + y);
    flgC = false;
    opADC(myMapper->readCPU(0x006E));
    myMapper->writeCPU(0x006E, a);
    myMapper->writeCPU(0x032C + x, a);
    myMapper->writeCPU(0x036C + x, myMapper->readCPU(0x006D));
    a = myMapper->readCPU(0xA5BE + y);
    pushAddress(0x002449);
    SUB_002579();
    if (handleReturnAddress(poppedEntry.value, 0x002449)) return;
    if (myMapper->readCPU(0x0065) != 0x0B) {
        if (myMapper->readCPU(0x006F) < 0x04) {
            goto L_00245B;
        }
        myMapper->writeCPU(0x03AC + x, myMapper->readCPU(0x0049));
    }
L_00245B:
    myMapper->writeCPU(0x010C + x, myMapper->readCPU(0x0064));
    myMapper->writeCPU(0x030C + x, myMapper->readCPU(0x0065));
    popAddress();
}

void game::SUB_002466() {
    opCMP(myMapper->readCPU(0x0019), 0x02);
    if (flgZ) {
        goto L_00246F;
    }
    SUB_0024A6();
    return;
L_00246F:
    x = 0x09;
    do {
        if (myMapper->readCPU(0x030C + x) == 0) {
            goto L_00247A;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_00247A:
    myMapper->writeCPU(0x005D, 0x01);
    myMapper->writeCPU(0x00A8, x);
    pushAddress(0x002482);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x002482)) return;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x0069, a);
    myMapper->writeCPU(0x010C + x, myMapper->readCPU(0x0064));
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0x0065));
    myMapper->writeCPU(0x03BC + x, myMapper->readCPU(0x0066));
    myMapper->writeCPU(0x03EC + x, myMapper->readCPU(0x0067));
    myMapper->writeCPU(0x030C + x, 0x96);
    myMapper->writeCPU(0x036C + x, 0xF0);
    popAddress();
}

void game::SUB_0024A6() {
    x = 0x09;
    do {
        if (myMapper->readCPU(0x030C + x) == 0) {
            goto L_0024B1;
        }
        opDEX(1);
    } while (!flgZ);
    popAddress();
    return;
L_0024B1:
    myMapper->writeCPU(0x00A8, x);
    myMapper->writeCPU(0x0098, 0x00);
    do {
        myMapper->writeCPU(0x00A9, 0x90);
        do {
            x = myMapper->readCPU(0x00A9);
            a = myMapper->readCPU(0x0600 + x);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0024C4;
            }
            if (flgZ) {
                goto L_002500;
            }
        L_0024C4:
            a = myMapper->readCPU(0x00A9);
            flgC = true;
            opSBC(0x30);
            myMapper->writeCPU(0x00A9, a);
        } while (!flgN);
    L_0024CD:
        opLSR_M(0x0065, 4);
    } while (!flgZ);
    pushAddress(0x0024D9);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x0024D9)) return;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x030C + x, myMapper->readCPU(0x0066));
    myMapper->writeCPU(0x010C + x, 0x80);
    myMapper->writeCPU(0x036C + x, 0xF0);
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0x0067));
    myMapper->writeCPU(0x012C + x, 0x89);
    myMapper->writeCPU(0x016C + x, myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0460 + x, 0x01);
    popAddress();
    return;
L_002500:
    a = myMapper->readCPU(0x0065);
    opAND(0x0F);
    if (flgZ) {
        goto L_0024CD;
    }
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0601 + x, a);
    myMapper->writeCPU(0x0600 + x, myMapper->readCPU(0x00A8));
    a = 0x00;
    opINC(0x0098, 1);
    y = 0x05;
    do {
        myMapper->writeCPU(0x0610 + x, a);
        myMapper->writeCPU(0x0602 + x, a);
        myMapper->writeCPU(0x0618 + x, a);
        opINX(1);
        opDEY(1);
    } while (!flgN);
    goto L_0024CD;
}

void game::SUB_002527() {
    y = myMapper->readCPU(0x00A8);
    a = 0x00;
    myMapper->writeCPU(0x0496 + y, a);
    myMapper->writeCPU(0x0460 + y, a);
    flgC = false;
    a = myMapper->readCPU(0x00A8);
    opADC(0x0C);
    x = a;
    a = 0x00;
    myMapper->writeCPU(0x0100 + x, a);
    myMapper->writeCPU(0x0120 + x, a);
    myMapper->writeCPU(0x0140 + x, a);
    myMapper->writeCPU(0x0160 + x, a);
    myMapper->writeCPU(0x0180 + x, a);
    myMapper->writeCPU(0x0300 + x, a);
    myMapper->writeCPU(0x0320 + x, a);
    myMapper->writeCPU(0x0340 + x, a);
    myMapper->writeCPU(0x0360 + x, a);
    myMapper->writeCPU(0x0380 + x, a);
    myMapper->writeCPU(0x03A0 + x, a);
    myMapper->writeCPU(0x03B0 + x, a);
    myMapper->writeCPU(0x03E0 + x, a);
    myMapper->writeCPU(0x0400 + x, a);
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x0440 + x, a);
    myMapper->writeCPU(0x0460 + x, a);
    myMapper->writeCPU(0x0480 + x, a);
    myMapper->writeCPU(0x04A0 + x, a);
    myMapper->writeCPU(0x04C0 + x, a);
    myMapper->writeCPU(0x04E0 + x, a);
    popAddress();
}

void game::SUB_002579() {
    myMapper->writeCPU(0x0098, a);
    opAND(0xFE);
    myMapper->writeCPU(0x04EC + x, a);
    myMapper->writeCPU(0x040C + x, a);
    a = myMapper->readCPU(0x0098);
    opAND(0x01);
    myMapper->writeCPU(0x03AC + x, a);
    if (flgZ) {
        goto L_002591;
    }
    myMapper->writeCPU(0x018C + x, 0x03);
L_002591:
    popAddress();
}

void game::SUB_002DAB() {
    myMapper->writeCPU(0x00AF, 0x80);
    myMapper->writeCPU(0x00AE, 0x00);
    myMapper->writeCPU(0x00A8, 0x09);
    do {
        x = myMapper->readCPU(0x00A8);
        pushAddress(0x002DBB);
        SUB_002DE5();
        if (handleReturnAddress(poppedEntry.value, 0x002DBB)) return;
        opDEC(0x00A8, 1);
    } while (!flgN);
    popAddress();
}

void game::SUB_002DE5() {
    a = myMapper->readCPU(0x010C + x);
    setLoadFlag(a);
    if (!flgN) {
        if (flgZ) {
            goto L_002E14;
        }
        if (myMapper->readCPU(0x014C + x) != 0) {
            goto L_002E11;
        }
        myMapper->writeCPU(0x014C + x, 0x06);
        a = myMapper->readCPU(0x010C + x);
        opASL_A(2);
        myMapper->writeCPU(0x0098, a);
        do {
            opINC(0x016C + x, 1);
            a = myMapper->readCPU(0x016C + x);
            opAND(0x03);
            flgC = false;
            opADC(myMapper->readCPU(0x0098));
            y = a;
            a = myMapper->readCPU(0xADC1 + y);
            setLoadFlag(a);
        } while (flgZ);
        myMapper->writeCPU(0x012C + x, a);
    L_002E11:
        opDEC(0x014C + x, 1);
    }
L_002E14:
    a = myMapper->readCPU(0x030C + x);
    setLoadFlag(a);
    if (flgZ) {
        SUB_002E70();
        return;
    }
    pushAddress(0x002E1B);
    SUB_0003E4();
    if (handleReturnAddress(poppedEntry.value, 0x002E1B)) return;
    SUB_002E70();
    return;
}

void game::SUB_002E70() {
    popAddress();
}

void game::SUB_002E99() {
    if (myMapper->readCPU(0x014C + x) != 0) {
        goto L_002EDA;
    }
    myMapper->writeCPU(0x014C + x, 0x05);
    a = myMapper->readCPU(0x016C + x);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0098, myMapper->readCPU(0xAE71 + y));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0xAE72 + y));
    y = myMapper->readCPU(0x042C + x);
    opINC(0x042C + x, 1);
    a = myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgZ) {
        y = myMapper->readCPU(0x03AC + x);
        setLoadFlag(y);
        if (flgZ) {
            SUB_002EF8();
            return;
        }
        myMapper->writeCPU(0x030C + x, 0x01);
        y = 0x07;
        opINC(0x0047, 1);
        a = myMapper->readCPU(0x0047);
        opAND(0x0F);
        if (flgZ) {
            goto L_002ED2;
        }
        y = 0x06;
    L_002ED2:
        myMapper->writeCPU(0x010C + x, y);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x012C + x, a);
L_002EDA:
    opDEC(0x014C + x, 1);
    SUB_002EDD();
    return;
}

void game::SUB_002EDD() {
    if (myMapper->readCPU(0x005B) != 0) {
        SUB_002F09();
        return;
    }
    SUB_002EE1();
    return;
}

void game::SUB_002EE1() {
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    opSBC(0x80);
    myMapper->writeCPU(0x038C + x, a);
    if (flgC) {
        SUB_002F09();
        return;
    }
    opDEC(0x036C + x, 1);
    opCMP(myMapper->readCPU(0x036C + x), 0x08);
    if (flgC) {
        SUB_002F09();
        return;
    }
    SUB_002EF8();
    return;
}

void game::SUB_002EF8() {
    a = 0x00;
    myMapper->writeCPU(0x030C + x, a);
    myMapper->writeCPU(0x010C + x, a);
    myMapper->writeCPU(0x012C + x, a);
    myMapper->writeCPU(0x014C + x, a);
    myMapper->writeCPU(0x016C + x, a);
    SUB_002F09();
    return;
}

void game::SUB_002F09() {
    popAddress();
}

void game::SUB_002F10() {
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x0002);
    opAND(0x1F);
    opCMP(a, 0x1A);
    if (flgC) {
        goto L_002F26;
    }
    a = myMapper->readCPU(0x030C + x);
    flgC = true;
    opSBC(0x20);
    y = a;
    a = myMapper->readCPU(0xAF0A + y);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_002F28;
    }
L_002F26:
    a = 0x00;
L_002F28:
    myMapper->writeCPU(0x012C + x, a);
    SUB_002F2B();
    return;
}

void game::SUB_002F2B() {
    SUB_002EDD();
    return;
}

void game::SUB_002F2E() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_002F43();
        return;
    }
    SUB_002F33();
    return;
}

void game::SUB_002F33() {
    a = 0x01;
    myMapper->writeCPU(0x0460 + x, a);
    myMapper->writeCPU(0x048C + x, a);
    myMapper->writeCPU(0x010C + x, 0x80);
    SUB_0030B4();
    return;
}

void game::SUB_002F43() {
    y = 0x08;
    a = 0x09;
    pushAddress(0x002F49);
    SUB_002F98();
    if (handleReturnAddress(poppedEntry.value, 0x002F49)) return;
    a = 0x78;
    if (myMapper->readCPU(0x0019) != 0x05) {
        SUB_002F54();
        return;
    }
    a = 0x63;
    SUB_002F54();
    return;
}

void game::SUB_002F54() {
    myMapper->writeCPU(0x012C + x, a);
    y = myMapper->readCPU(0x046C + x);
    if (y >= 0x03) {
        myMapper->writeCPU(0x018C + x, 0x03);
    }
    opCMP(y, 0x05);
    if (!flgC) {
        SUB_002F2B();
        return;
    }
    if (myMapper->readCPU(0x0019) == 0) {
        a = myMapper->readCPU(0x0018);
        opASL_A(2);
        y = a;
        a = myMapper->readCPU(0x07E5 + y);
        opLSR_A(1);
        if (!flgC) {
            opINC(0x005F, 1);
            opCMP(myMapper->readCPU(0x005F), 0x04);
            if (!flgC) {
                goto L_002F80;
            }
            opINC(0x0039, 1);
        }
    }
L_002F80:
    a = 0x0A;
    pushAddress(0x002F84);
    SUB_004B28();
    if (handleReturnAddress(poppedEntry.value, 0x002F84)) return;
    SUB_000453();
    return;
}

void game::SUB_002F88() {
    if (!(myMapper->readCPU(0x030C + x) & 0x80)) {
        SUB_002F33();
        return;
    }
    y = 0xF6;
    a = 0x0C;
    pushAddress(0x002F93);
    SUB_002F98();
    if (handleReturnAddress(poppedEntry.value, 0x002F93)) return;
    a = 0x79;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002F54();
        return;
    }
    SUB_002F98();
    return;
}

void game::SUB_002F98() {
    myMapper->writeCPU(0x00AC, y);
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x00AB, x);
    myMapper->writeCPU(0x00AA, a);
    y = myMapper->readCPU(0x042C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_002FB1;
    }
    opDEY(1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opCMP(myMapper->readCPU(0x036C + x), 0xA0);
    if (!flgC) {
        do {
            popAddress();
            return;
        L_002FB1:
            opCMP(myMapper->readCPU(0x036C + x), 0xC8);
        } while (!flgC);
    }
    a = myMapper->readCPU(0x0002);
    opAND(0x0F);
    if (flgZ) {
        opINC(0x044C + x, 1);
        opCMP(myMapper->readCPU(0x044C + x), 0x05);
        if (flgC) {
            goto L_003014;
        }
        x = 0x09;
        do {
            if (myMapper->readCPU(0x030C + x) == 0) {
                goto L_002FD7;
            }
            opDEX(1);
        } while (!flgN);
        while (true) {
            x = myMapper->readCPU(0x00AB);
            myMapper->writeCPU(0x00A8, x);
            popAddress();
            return;
        L_002FD7:
            myMapper->writeCPU(0x00A8, x);
            pushAddress(0x002FDB);
            SUB_002527();
            if (handleReturnAddress(poppedEntry.value, 0x002FDB)) return;
            x = myMapper->readCPU(0x00A8);
            myMapper->writeCPU(0x030C + x, myMapper->readCPU(0x00AA));
            myMapper->writeCPU(0x010C + x, 0x00);
            y = myMapper->readCPU(0x00AB);
            a = myMapper->readCPU(0x036C + y);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x036C + x, a);
            a = myMapper->readCPU(0x032C + y);
            flgC = false;
            opADC(myMapper->readCPU(0x00AC));
            myMapper->writeCPU(0x032C + x, a);
            y = myMapper->readCPU(0x0017);
            if (myMapper->readCPU(0x0019) != 0) {
                opINY(1);
            }
            if (myMapper->readCPU(0x001A) == 0) {
                goto L_003008;
            }
            opINY(1);
        L_003008:
            a = myMapper->readCPU(0xB01D + y);
            myMapper->writeCPU(0x04EC + x, a);
            myMapper->writeCPU(0x040C + x, a);
        }
    L_003014:
        myMapper->writeCPU(0x044C + x, 0x00);
        opINC(0x042C + x, 1);
    }
    popAddress();
}

void game::SUB_003026() {
    myMapper->writeCPU(0x030C + x, 0x91);
    if (myMapper->readCPU(0x032C + x) >= myMapper->readCPU(0x0320)) {
        SUB_003038();
        return;
    }
    SUB_003033();
    return;
}

void game::SUB_003033() {
    myMapper->writeCPU(0x040C + x, 0x0A);
    SUB_003038();
    return;
}

void game::SUB_003038() {
    y = 0x00;
    a = myMapper->readCPU(0x036C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0360));
    if (flgC) {
        opCMP(a, 0x30);
        if (!flgC) {
            goto L_00306D;
        }
        opINY(1);
        opCMP(a, 0x60);
        if (!flgC) {
            goto L_00306D;
        }
        if (flgC) {
            goto L_003059;
        }
    }
    y = 0x03;
    opCMP(a, 0xD0);
    if (!flgC) {
        opINY(1);
        opCMP(a, 0xA0);
        if (!flgC) {
        L_003059:
            a = myMapper->readCPU(0x032C + x);
            flgC = true;
            opSBC(myMapper->readCPU(0x0320));
            if (flgC) {
                opCMP(a, 0x30);
                if (!flgC) {
                    goto L_00306C;
                }
                if (flgC) {
                    goto L_00306D;
                }
            }
            opCMP(a, 0xD0);
            if (flgC) {
            L_00306C:
                opINY(1);
            }
        }
    }
L_00306D:
    myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xB086 + y));
    if (!(myMapper->readCPU(0x018C + x) & 0x80)) {
        goto L_00307D;
    }
    a = myMapper->readCPU(0xB092 + y);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_003080;
    }
L_00307D:
    a = myMapper->readCPU(0xB08C + y);
L_003080:
    myMapper->writeCPU(0x0496 + x, a);
    SUB_002EDD();
    return;
}

void game::SUB_003098() {
    myMapper->writeCPU(0x030C + x, 0x92);
    a = myMapper->readCPU(0x018C + x);
    opORA(0x80);
    myMapper->writeCPU(0x018C + x, a);
    opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
    if (flgC) {
        SUB_003033();
        return;
    }
    if (!flgC) {
        SUB_003038();
        return;
    }
    SUB_0030AF();
    return;
}

void game::SUB_0030AF() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_0030BE();
        return;
    }
    SUB_0030B4();
    return;
}

void game::SUB_0030B4() {
    a = 0x80;
    flgC = false;
    opADC(myMapper->readCPU(0x030C + x));
    myMapper->writeCPU(0x030C + x, a);
    popAddress();
}

void game::SUB_0030BE() {
    y = myMapper->readCPU(0x048C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opDEY(1);
        if (flgZ) {
            goto L_0030E9;
        }
        opDEY(1);
        if (flgZ) {
            goto L_0030FA;
        }
        opDEY(1);
        if (flgZ) {
            goto L_003101;
        }
        popAddress();
        return;
    }
    a = 0xFE;
    pushAddress(0x0030D1);
    SUB_003164();
    if (handleReturnAddress(poppedEntry.value, 0x0030D1)) return;
    opCMP(a, 0x60);
    if (!flgC) {
        myMapper->writeCPU(0x046C + x, 0x40);
        opCMP(myMapper->readCPU(0x032C + x), 0x80);
        if (!flgC) {
            goto L_0030E5;
        }
        opINC(0x048C + x, 1);
    L_0030E5:
        opINC(0x048C + x, 1);
    }
    popAddress();
    return;
L_0030E9:
    pushAddress(0x0030EB);
    SUB_003109();
    if (handleReturnAddress(poppedEntry.value, 0x0030EB)) return;
    a = 0x02;
    do {
        pushAddress(0x0030F0);
        SUB_00317C();
        if (handleReturnAddress(poppedEntry.value, 0x0030F0)) return;
        opINC(0x036C + x, 1);
        opDEC(0x046C + x, 1);
        if (flgZ) {
            SUB_003111();
            return;
        }
        popAddress();
        return;
    L_0030FA:
        pushAddress(0x0030FC);
        SUB_003117();
        if (handleReturnAddress(poppedEntry.value, 0x0030FC)) return;
        a = 0xFE;
        setLoadFlag(a);
    } while (!flgZ);
L_003101:
    a = 0x03;
    SUB_003103();
    return;
}

void game::SUB_003103() {
    pushAddress(0x003105);
    SUB_003164();
    if (handleReturnAddress(poppedEntry.value, 0x003105)) return;
    SUB_003251();
    return;
}

void game::SUB_003109() {
    opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
    if (!flgC) {
        SUB_003116();
        return;
    }
    SUB_003111();
    return;
}

void game::SUB_003111() {
    myMapper->writeCPU(0x048C + x, 0x03);
    SUB_003116();
    return;
}

void game::SUB_003116() {
    popAddress();
}

void game::SUB_003117() {
    opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
    if (!flgC) {
        SUB_003111();
        return;
    }
    popAddress();
}

void game::SUB_003120() {
    a = myMapper->readCPU(0x03EC + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x048C + x));
    myMapper->writeCPU(0x03EC + x, a);
    if (flgC) {
        goto L_00312F;
    }
    opDEC(0x03BC + x, 1);
L_00312F:
    popAddress();
}

void game::SUB_003130() {
    a = myMapper->readCPU(0x03EC + x);
    flgC = false;
    opADC(myMapper->readCPU(0x048C + x));
    myMapper->writeCPU(0x03EC + x, a);
    if (!flgC) {
        goto L_00313F;
    }
    opINC(0x03BC + x, 1);
L_00313F:
    popAddress();
}

void game::SUB_003140() {
    a = myMapper->readCPU(0x034C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x03EC + x));
    myMapper->writeCPU(0x034C + x, a);
    a = myMapper->readCPU(0x032C + x);
    opSBC(myMapper->readCPU(0x03BC + x));
    myMapper->writeCPU(0x032C + x, a);
    popAddress();
}

void game::SUB_003154() {
    a = myMapper->readCPU(0x044C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x038C + x));
    myMapper->writeCPU(0x038C + x, a);
    a = myMapper->readCPU(0x042C + x);
    SUB_003165();
    return;
}

void game::SUB_003164() {
    flgC = false;
    SUB_003165();
    return;
}

void game::SUB_003165() {
    opADC(myMapper->readCPU(0x036C + x));
    myMapper->writeCPU(0x036C + x, a);
    popAddress();
}

void game::SUB_00316C() {
    a = myMapper->readCPU(0x03EC + x);
    flgC = false;
    opADC(myMapper->readCPU(0x034C + x));
    myMapper->writeCPU(0x034C + x, a);
    a = myMapper->readCPU(0x03BC + x);
    SUB_00317D();
    return;
}

void game::SUB_00317C() {
    flgC = false;
    SUB_00317D();
    return;
}

void game::SUB_00317D() {
    opADC(myMapper->readCPU(0x032C + x));
    myMapper->writeCPU(0x032C + x, a);
    popAddress();
}

void game::SUB_003184() {
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x044C + x));
    myMapper->writeCPU(0x038C + x, a);
    a = myMapper->readCPU(0x036C + x);
    opSBC(myMapper->readCPU(0x042C + x));
    myMapper->writeCPU(0x036C + x, a);
    popAddress();
}

void game::SUB_003198() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_0031C2();
        return;
    }
    myMapper->writeCPU(0x010C + x, 0x02);
    pushAddress(0x0031A4);
    SUB_0030B4();
    if (handleReturnAddress(poppedEntry.value, 0x0031A4)) return;
    myMapper->writeCPU(0x04AC + x, 0x00);
    SUB_0031AA();
    return;
}

void game::SUB_0031AA() {
    myMapper->writeCPU(0x048C + x, 0x20);
    a = 0x03;
    SUB_0031B1();
    return;
}

void game::SUB_0031B1() {
    myMapper->writeCPU(0x03BC + x, a);
    a = 0x00;
    myMapper->writeCPU(0x03EC + x, a);
    myMapper->writeCPU(0x044C + x, a);
    myMapper->writeCPU(0x042C + x, 0xFE);
    popAddress();
}

void game::SUB_0031C2() {
    y = myMapper->readCPU(0x04AC + x);
    myMapper->writeCPU(0x046C + x, myMapper->readCPU(0xB200 + y));
    a = myMapper->readCPU(0x03BC + x);
    setLoadFlag(a);
    if (!flgN) {
        SUB_0031DA();
        return;
    }
    opCMP(a, 0xFD);
    if (flgC) {
        SUB_0031DA();
        return;
    }
    opINC(0x04AC + x, 1);
    SUB_0031AA();
    return;
}

void game::SUB_0031DA() {
    if (myMapper->readCPU(0x046C + x) != 0) {
        SUB_0031E5();
        return;
    }
    SUB_0031DF();
    return;
}

void game::SUB_0031DF() {
    pushAddress(0x0031E1);
    SUB_003154();
    if (handleReturnAddress(poppedEntry.value, 0x0031E1)) return;
    SUB_0031E8();
    return;
}

void game::SUB_0031E5() {
    pushAddress(0x0031E7);
    SUB_003184();
    if (handleReturnAddress(poppedEntry.value, 0x0031E7)) return;
    SUB_0031E8();
    return;
}

void game::SUB_0031E8() {
    pushAddress(0x0031EA);
    SUB_003140();
    if (handleReturnAddress(poppedEntry.value, 0x0031EA)) return;
    SUB_0031EB();
    return;
}

void game::SUB_0031EB() {
    pushAddress(0x0031ED);
    SUB_003120();
    if (handleReturnAddress(poppedEntry.value, 0x0031ED)) return;
    SUB_003251();
    return;
}

void game::SUB_0031F1() {
    pushAddress(0x0031F3);
    SUB_003154();
    if (handleReturnAddress(poppedEntry.value, 0x0031F3)) return;
    SUB_0031F4();
    return;
}

void game::SUB_0031F4() {
    pushAddress(0x0031F6);
    SUB_00316C();
    if (handleReturnAddress(poppedEntry.value, 0x0031F6)) return;
    SUB_0031EB();
    return;
}

void game::SUB_0031FA() {
    pushAddress(0x0031FC);
    SUB_003184();
    if (handleReturnAddress(poppedEntry.value, 0x0031FC)) return;
    SUB_0031F4();
    return;
}

void game::SUB_003205() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_00321A();
        return;
    }
    SUB_00320A();
    return;
}

void game::SUB_00320A() {
    myMapper->writeCPU(0x046C + x, 0x00);
    pushAddress(0x003211);
    SUB_0030B4();
    if (handleReturnAddress(poppedEntry.value, 0x003211)) return;
    SUB_003212();
    return;
}

void game::SUB_003212() {
    myMapper->writeCPU(0x048C + x, 0x20);
    SUB_00322E();
    return;
}

void game::SUB_00321A() {
    if (myMapper->readCPU(0x046C + x) != 0) {
        SUB_003233();
        return;
    }
    a = myMapper->readCPU(0x03BC + x);
    setLoadFlag(a);
    if (!flgN) {
        goto L_003228;
    }
    opCMP(a, 0xFE);
    if (!flgC) {
        goto L_00322B;
    }
L_003228:
    SUB_0031DF();
    return;
L_00322B:
    opINC(0x046C + x, 1);
    SUB_00322E();
    return;
}

void game::SUB_00322E() {
    a = 0x02;
    SUB_0031B1();
    return;
}

void game::SUB_003233() {
    a = myMapper->readCPU(0x03BC + x);
    setLoadFlag(a);
    if (flgN) {
        opCMP(a, 0xFE);
        if (flgC) {
            goto L_00323E;
        }
        if (!flgC) {
            SUB_00320A();
            return;
        }
    }
L_00323E:
    SUB_0031F1();
    return;
}

void game::SUB_003250() {
    popAddress();
}

void game::SUB_003251() {
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x036C + x);
    opCMP(a, 0x04);
    if (flgC) {
        opCMP(a, 0xF4);
        if (!flgC) {
            a = myMapper->readCPU(0x032C + x);
            opCMP(a, 0x08);
            if (!flgC) {
                goto L_003269;
            }
            opCMP(a, 0xC4);
            if (!flgC) {
                SUB_003250();
                return;
            }
        }
    }
L_003269:
    SUB_002EF8();
    return;
}

void game::SUB_00326C() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        goto L_00327F;
    }
    myMapper->writeCPU(0x048C + x, 0x80);
    myMapper->writeCPU(0x04AC + x, 0x00);
    pushAddress(0x00327D);
    SUB_0030B4();
    if (handleReturnAddress(poppedEntry.value, 0x00327D)) return;
    popAddress();
    return;
L_00327F:
    if (myMapper->readCPU(0x046C + x) != 0) {
        goto L_00329D;
    }
    if (myMapper->readCPU(0x04AC + x) != 0) {
        SUB_0032C0();
        return;
    }
    myMapper->writeCPU(0x012C + x, 0x3A);
    opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
    if (flgZ) {
        SUB_0032DB();
        return;
    }
    if (!flgC) {
        SUB_0032BB();
        return;
    }
    myMapper->writeCPU(0x046C + x, 0x1E);
L_00329D:
    opDEC(0x036C + x, 1);
    myMapper->writeCPU(0x012C + x, 0x38);
    opDEC(0x046C + x, 1);
    if (flgZ) {
        SUB_0032AF();
        return;
    }
    myMapper->writeCPU(0x046C + x, 0x00);
    SUB_0032AF();
    return;
}

void game::SUB_0032AF() {
    pushAddress(0x0032B1);
    SUB_0032EE();
    if (handleReturnAddress(poppedEntry.value, 0x0032B1)) return;
    pushAddress(0x0032B4);
    SUB_003120();
    if (handleReturnAddress(poppedEntry.value, 0x0032B4)) return;
    SUB_0032B5();
    return;
}

void game::SUB_0032B5() {
    pushAddress(0x0032B7);
    SUB_003304();
    if (handleReturnAddress(poppedEntry.value, 0x0032B7)) return;
    SUB_003251();
    return;
}

void game::SUB_0032BB() {
    myMapper->writeCPU(0x04AC + x, 0x1E);
    SUB_0032C0();
    return;
}

void game::SUB_0032C0() {
    opDEC(0x036C + x, 1);
    myMapper->writeCPU(0x012C + x, 0x39);
    opDEC(0x04AC + x, 1);
    if (flgZ) {
        SUB_0032D2();
        return;
    }
    myMapper->writeCPU(0x04AC + x, 0x00);
    SUB_0032D2();
    return;
}

void game::SUB_0032D2() {
    pushAddress(0x0032D4);
    SUB_0032EE();
    if (handleReturnAddress(poppedEntry.value, 0x0032D4)) return;
    pushAddress(0x0032D7);
    SUB_003130();
    if (handleReturnAddress(poppedEntry.value, 0x0032D7)) return;
    SUB_0032B5();
    return;
}

void game::SUB_0032DB() {
    a = 0xFE;
    SUB_003103();
    return;
}

void game::SUB_0032E6() {
    myMapper->writeCPU(0x03BC + x, a);
    myMapper->writeCPU(0x03EC + x, y);
    popAddress();
}

void game::SUB_0032EE() {
    a = myMapper->readCPU(0x032C + x);
    y = myMapper->readCPU(0x034C + x);
    SUB_0032E6();
    return;
}

void game::SUB_003304() {
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0x03BC + x));
    myMapper->writeCPU(0x034C + x, myMapper->readCPU(0x03EC + x));
    popAddress();
}

void game::SUB_003311() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_003343();
        return;
    }
    myMapper->writeCPU(0x04CC + x, 0x0A);
    SUB_0030B4();
    return;
}

void game::SUB_00331E() {
    opINC(0x014C + x, 1);
    a = myMapper->readCPU(0x014C + x);
    opLSR_A(2);
    opAND(0x07);
    y = a;
    a = 0x00;
    if (y < 0x04) {
        goto L_003331;
    }
    a = 0x80;
L_003331:
    myMapper->writeCPU(0x018C + x, a);
    myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xB33B + y));
    popAddress();
}

void game::SUB_003343() {
    pushAddress(0x003345);
    SUB_00331E();
    if (handleReturnAddress(poppedEntry.value, 0x003345)) return;
    if (myMapper->readCPU(0x04AC + x) != 0) {
        goto L_003355;
    }
    opDEC(0x04CC + x, 1);
    if (!flgZ) {
        goto L_003362;
    }
    myMapper->writeCPU(0x04AC + x, 0x01);
L_003355:
    if (myMapper->readCPU(0x048C + x) != 0) {
        SUB_003367();
        return;
    }
    if (myMapper->readCPU(0x0320) >= myMapper->readCPU(0x032C + x)) {
        SUB_003367();
        return;
    }
L_003362:
    a = 0xFE;
    SUB_0033F9();
    return;
}

void game::SUB_003367() {
    myMapper->writeCPU(0x048C + x, 0x01);
    SUB_0032DB();
    return;
}

void game::SUB_00336F() {
    if (!(myMapper->readCPU(0x030C + x) & 0x80)) {
        SUB_0033A7();
        return;
    }
    SUB_0031E5();
    return;
}

void game::SUB_003377() {
    if (!(myMapper->readCPU(0x030C + x) & 0x80)) {
        SUB_0033A7();
        return;
    }
    SUB_0031FA();
    return;
}

void game::SUB_00337F() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_0033AA();
        return;
    }
    if (myMapper->readCPU(0x04CC + x) == 0) {
        opINC(0x04AC + x, 1);
        a = myMapper->readCPU(0x04AC + x);
        opLSR_A(2);
        y = a;
        myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xB3C2 + y));
        opCMP(y, 0x08);
        if (flgZ) {
            goto L_00339D;
        }
        popAddress();
        return;
    }
L_00339D:
    myMapper->writeCPU(0x04CC + x, 0x01);
    SUB_0033A2();
    return;
}

void game::SUB_0033A2() {
    myMapper->writeCPU(0x048C + x, 0x00);
    SUB_0033A7();
    return;
}

void game::SUB_0033A7() {
    SUB_0030B4();
    return;
}

void game::SUB_0033AA() {
    myMapper->writeCPU(0x012C + x, 0x67);
    if (myMapper->readCPU(0x048C + x) != 0) {
        goto L_0033B9;
    }
    a = myMapper->readCPU(0x00A8);
    pushAddress(0x0033B8);
    SUB_003CB5();
    if (handleReturnAddress(poppedEntry.value, 0x0033B8)) return;
L_0033B9:
    pushAddress(0x0033BB);
    SUB_003DFA();
    if (handleReturnAddress(poppedEntry.value, 0x0033BB)) return;
    myMapper->writeCPU(0x048C + x, 0x01);
    popAddress();
}

void game::SUB_0033CB() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        goto L_0033D8;
    }
    myMapper->writeCPU(0x04CC + x, 0x14);
    SUB_0033A2();
    return;
L_0033D8:
    pushAddress(0x0033DA);
    SUB_00331E();
    if (handleReturnAddress(poppedEntry.value, 0x0033DA)) return;
    if (myMapper->readCPU(0x04AC + x) != 0) {
        goto L_0033EA;
    }
    opDEC(0x04CC + x, 1);
    if (!flgZ) {
        goto L_0033F7;
    }
    myMapper->writeCPU(0x04AC + x, 0x01);
L_0033EA:
    if (myMapper->readCPU(0x048C + x) != 0) {
        SUB_0033FF();
        return;
    }
    if (myMapper->readCPU(0x032C + x) >= myMapper->readCPU(0x0320)) {
        SUB_0033FF();
        return;
    }
L_0033F7:
    a = 0x02;
    SUB_0033F9();
    return;
}

void game::SUB_0033F9() {
    pushAddress(0x0033FB);
    SUB_00317C();
    if (handleReturnAddress(poppedEntry.value, 0x0033FB)) return;
    SUB_002EDD();
    return;
}

void game::SUB_0033FF() {
    SUB_003367();
    return;
}

void game::SUB_003402() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_003412();
        return;
    }
    SUB_003407();
    return;
}

void game::SUB_003407() {
    pushAddress(0x003409);
    SUB_0030B4();
    if (handleReturnAddress(poppedEntry.value, 0x003409)) return;
    myMapper->writeCPU(0x04AC + x, 0x00);
    SUB_00340F();
    return;
}

void game::SUB_00340F() {
    SUB_003212();
    return;
}

void game::SUB_003412() {
    y = myMapper->readCPU(0x04AC + x);
    myMapper->writeCPU(0x046C + x, myMapper->readCPU(0xB42F + y));
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x03BC + x);
    setLoadFlag(a);
    if (flgN) {
        opCMP(a, 0xFE);
        if (flgC) {
            goto L_00342C;
        }
        opINC(0x04AC + x, 1);
        SUB_00340F();
        return;
    }
L_00342C:
    SUB_0031DA();
    return;
}

void game::SUB_003434() {
    if (!(myMapper->readCPU(0x030C + x) & 0x80)) {
        SUB_003407();
        return;
    }
    y = myMapper->readCPU(0x04AC + x);
    myMapper->writeCPU(0x046C + x, myMapper->readCPU(0xB45C + y));
    a = myMapper->readCPU(0x03BC + x);
    setLoadFlag(a);
    if (flgN) {
        opCMP(a, 0xFE);
        if (!flgC) {
            opINC(0x04AC + x, 1);
            SUB_003212();
            return;
        }
    }
    if (myMapper->readCPU(0x046C + x) != 0) {
        goto L_003459;
    }
    SUB_0031F1();
    return;
L_003459:
    SUB_0031FA();
    return;
}

void game::SUB_003480() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        goto L_003496;
    }
    pushAddress(0x003487);
    SUB_0030B4();
    if (handleReturnAddress(poppedEntry.value, 0x003487)) return;
    myMapper->writeCPU(0x048C + x, 0x02);
    y = myMapper->readCPU(0x0017);
    myMapper->writeCPU(0x04CC + x, myMapper->readCPU(0xB4E4 + y));
    popAddress();
    return;
L_003496:
    y = 0x06;
    pushAddress(0x00349A);
    SUB_003628();
    if (handleReturnAddress(poppedEntry.value, 0x00349A)) return;
    if (myMapper->readCPU(0x048C + x) == 0) {
        a = myMapper->readCPU(0x00A8);
        pushAddress(0x0034A4);
        SUB_003CB5();
        if (handleReturnAddress(poppedEntry.value, 0x0034A4)) return;
    }
    y = myMapper->readCPU(0x048C + x);
    opDEY(1);
    if (!flgZ) {
        opDEY(1);
        if (flgZ) {
            goto L_0034C8;
        }
    }
    opDEC(0x04CC + x, 1);
    if (flgZ) {
        goto L_0034BC;
    }
    pushAddress(0x0034B5);
    SUB_003DFA();
    if (handleReturnAddress(poppedEntry.value, 0x0034B5)) return;
    a = 0x01;
    do {
        myMapper->writeCPU(0x048C + x, a);
        popAddress();
        return;
    L_0034BC:
        y = myMapper->readCPU(0x0017);
        myMapper->writeCPU(0x04CC + x, myMapper->readCPU(0xB4E4 + y));
        a = 0x02;
        setLoadFlag(a);
    } while (!flgZ);
L_0034C8:
    pushAddress(0x0034CA);
    SUB_002EE1();
    if (handleReturnAddress(poppedEntry.value, 0x0034CA)) return;
    opDEC(0x04CC + x, 1);
    if (flgZ) {
        goto L_0034D4;
    }
    a = 0x02;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0034DE;
    }
L_0034D4:
    y = myMapper->readCPU(0x0017);
    myMapper->writeCPU(0x04CC + x, myMapper->readCPU(0xB4EB + y));
    a = 0x00;
L_0034DE:
    myMapper->writeCPU(0x048C + x, a);
    SUB_003251();
    return;
}

void game::SUB_0034F2() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        goto L_0034FA;
    }
    SUB_0030B4();
    return;
L_0034FA:
    SUB_003DFA();
    return;
}

void game::SUB_0034FD() {
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        SUB_003510();
        return;
    }
    SUB_003502();
    return;
}

void game::SUB_003502() {
    pushAddress(0x003504);
    SUB_0030B4();
    if (handleReturnAddress(poppedEntry.value, 0x003504)) return;
    myMapper->writeCPU(0x048C + x, 0x80);
    myMapper->writeCPU(0x04AC + x, 0x14);
    popAddress();
}

void game::SUB_003510() {
    y = 0x03;
    pushAddress(0x003514);
    SUB_003628();
    if (handleReturnAddress(poppedEntry.value, 0x003514)) return;
    opDEC(0x036C + x, 1);
    pushAddress(0x00351A);
    SUB_003251();
    if (handleReturnAddress(poppedEntry.value, 0x00351A)) return;
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_00352A;
    }
    opDEY(1);
    if (flgZ) {
        goto L_003538;
    }
    opDEY(1);
    if (flgZ) {
        goto L_003546;
    }
    opDEY(1);
    if (flgZ) {
        goto L_003556;
    }
    popAddress();
    return;
L_00352A:
    opDEC(0x04AC + x, 1);
    if (myMapper->readCPU(0x04AC + x) != 0) {
        goto L_003537;
    }
    a = 0x01;
    do {
        do {
            do {
                myMapper->writeCPU(0x046C + x, a);
            L_003537:
                popAddress();
                return;
            L_003538:
                a = 0x02;
                y = myMapper->readCPU(0x032C + x);
                opCMP(y, myMapper->readCPU(0x0320));
            } while (flgC);
            a = 0x03;
            setLoadFlag(a);
        } while (!flgZ);
    L_003546:
        pushAddress(0x003548);
        SUB_0032AF();
        if (handleReturnAddress(poppedEntry.value, 0x003548)) return;
        opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
        if (flgZ) {
            goto L_003552;
        }
        popAddress();
        return;
    L_003552:
        a = 0x04;
        setLoadFlag(a);
    } while (!flgZ);
L_003556:
    SUB_0032D2();
    return;
}

void game::SUB_003559() {
    if (!(myMapper->readCPU(0x030C + x) & 0x80)) {
        SUB_003502();
        return;
    }
    y = 0x09;
    pushAddress(0x003562);
    SUB_003628();
    if (handleReturnAddress(poppedEntry.value, 0x003562)) return;
    opDEC(0x036C + x, 1);
    SUB_003251();
    return;
}

void game::SUB_003569() {
    pushAddress(0x00356B);
    SUB_002EDD();
    if (handleReturnAddress(poppedEntry.value, 0x00356B)) return;
    opCMP(myMapper->readCPU(0x036C + x), 0xB0);
    if (flgC) {
        popAddress();
        return;
    }
    opINC(0x005B, 1);
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        opINC(0x046C + x, 1);
        a = 0x1F;
        SUB_0005E8();
        return;
    }
    opCMP(y, 0x07);
    if (flgC) {
        SUB_002EF8();
        return;
    }
    opINC(0x04AC + x, 1);
    opCMP(myMapper->readCPU(0x04AC + x), 0x14);
    if (!flgC) {
        popAddress();
        return;
    }
    opINC(0x046C + x, 1);
    myMapper->writeCPU(0x04AC + x, 0x00);
    opDEY(1);
    myMapper->writeCPU(0x00A9, y);
    a = y;
    opLSR_A(1);
    if (!flgC) {
        opADC(myMapper->readCPU(0x00A9));
        x = a;
        y = 0x02;
        do {
            a = myMapper->readCPU(0xB612 + x);
            myMapper->writeCPU(0x06C2 + y, a);
            myMapper->writeCPU(0x06CA + y, a);
            myMapper->writeCPU(0x06D2 + y, a);
            myMapper->writeCPU(0x06DA + y, a);
            opINX(1);
            opDEY(1);
        } while (!flgN);
    }
    a = 0x20;
    pushAddress(0x0035C0);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0035C0)) return;
    a = 0x20;
    pushAddress(0x0035C5);
    SUB_0005E8();
    if (handleReturnAddress(poppedEntry.value, 0x0035C5)) return;
    a = myMapper->readCPU(0x00A9);
    y = 0xC2;
    opLSR_A(1);
    if (flgC) {
        goto L_0035CF;
    }
    y = 0xC3;
L_0035CF:
    myMapper->writeCPU(0x0099, y);
    a = myMapper->readCPU(0x00A9);
    opAND(0xFE);
    opASL_A(1);
    myMapper->writeCPU(0x00A9, a);
    x = myMapper->readCPU(0x00A9);
    y = myMapper->readCPU(0x000E);
    myMapper->writeCPU(0x06F1 + y, myMapper->readCPU(0xB606 + x));
    myMapper->writeCPU(0x06F2 + y, myMapper->readCPU(0xB607 + x));
    myMapper->writeCPU(0x06F9 + y, myMapper->readCPU(0xB608 + x));
    myMapper->writeCPU(0x06FA + y, myMapper->readCPU(0xB609 + x));
    x = 0x03;
    do {
        a = myMapper->readCPU(0x0099);
        myMapper->writeCPU(0x06FB + y, a);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x06F3 + y, a);
        opINY(1);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_00361E() {
    y = 0x00;
    pushAddress(0x003622);
    SUB_003628();
    if (handleReturnAddress(poppedEntry.value, 0x003622)) return;
    a = 0xFE;
    SUB_003103();
    return;
}

void game::SUB_003628() {
    opINC(0x014C + x, 1);
    opCMP(myMapper->readCPU(0x014C + x), myMapper->readCPU(0xB650 + y));
    if (!flgC) {
        SUB_00364F();
        return;
    }
    a = myMapper->readCPU(0x016C + x);
    flgC = false;
    opADC(0x01);
    if (a < myMapper->readCPU(0xB652 + y)) {
        goto L_003640;
    }
    a = 0x00;
L_003640:
    myMapper->writeCPU(0x016C + x, a);
    flgC = false;
    opADC(myMapper->readCPU(0xB651 + y));
    SUB_003647();
    return;
}

void game::SUB_003647() {
    myMapper->writeCPU(0x012C + x, a);
    myMapper->writeCPU(0x014C + x, 0x00);
    SUB_00364F();
    return;
}

void game::SUB_00364F() {
    popAddress();
}

void game::SUB_00365C() {
    a = myMapper->readCPU(0x0360);
    flgC = false;
    opADC(0x30);
    if (!flgC) {
        opAND(0xF8);
        if (a < 0xF0) {
            goto L_00366C;
        }
    }
    a = 0xF0;
L_00366C:
    opCMP(a, 0x20);
    if (flgC) {
        goto L_003672;
    }
    a = 0x20;
L_003672:
    myMapper->writeCPU(0x048C + x, a);
    popAddress();
}

void game::SUB_003676() {
    myMapper->writeCPU(0x04EC + x, 0x00);
    a = myMapper->readCPU(0x036C + x);
    opAND(0xF8);
    opCMP(a, myMapper->readCPU(0x048C + x));
    if (flgZ) {
        SUB_0036A2();
        return;
    }
    if (!flgC) {
        SUB_003697();
        return;
    }
    a = 0xFE;
    pushAddress(0x00368B);
    SUB_003164();
    if (handleReturnAddress(poppedEntry.value, 0x00368B)) return;
    opCMP(a, 0x08);
    if (flgC) {
        SUB_003693();
        return;
    }
    SUB_003690();
    return;
}

void game::SUB_003690() {
    SUB_002EF8();
    return;
}

void game::SUB_003693() {
    a = 0x03;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00369E();
        return;
    }
    SUB_003697();
    return;
}

void game::SUB_003697() {
    a = 0x01;
    pushAddress(0x00369B);
    SUB_003164();
    if (handleReturnAddress(poppedEntry.value, 0x00369B)) return;
    a = 0x04;
    SUB_00369E();
    return;
}

void game::SUB_00369E() {
    myMapper->writeCPU(0x010C + x, a);
    popAddress();
}

void game::SUB_0036A2() {
    y = myMapper->readCPU(0x0017);
    a = myMapper->readCPU(0xB6D2 + y);
    myMapper->writeCPU(0x04EC + x, a);
    myMapper->writeCPU(0x040C + x, a);
    opINC(0x046C + x, 1);
    a = 0x00;
    myMapper->writeCPU(0x010C + x, a);
    myMapper->writeCPU(0x04CC + x, a);
    SUB_0036B8();
    return;
}

void game::SUB_0036B8() {
    y = myMapper->readCPU(0x04AC + x);
    opCMP(myMapper->readCPU(0x036C + x), myMapper->readCPU(0x0360));
    if (flgC) {
        goto L_0036C5;
    }
    opINY(2);
L_0036C5:
    myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xB6D9 + y));
    myMapper->writeCPU(0x0496 + x, myMapper->readCPU(0xB6DD + y));
    popAddress();
}

void game::SUB_0036E1() {
    x = myMapper->readCPU(0x00A8);
    if (myMapper->readCPU(0x030C + x) & 0x80) {
        goto L_0036EE;
    }
    pushAddress(0x0036EA);
    SUB_00365C();
    if (handleReturnAddress(poppedEntry.value, 0x0036EA)) return;
    SUB_0030B4();
    return;
L_0036EE:
    a = myMapper->readCPU(0x046C + x);
    opAND(0x01);
    if (!flgZ) {
        SUB_003723();
        return;
    }
    myMapper->writeCPU(0x00A4, myMapper->readCPU(0x036C + x));
    a = myMapper->readCPU(0x032C + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x00A5, a);
    pushAddress(0x003704);
    SUB_0043D3();
    if (handleReturnAddress(poppedEntry.value, 0x003704)) return;
    if (!flgZ) {
        SUB_003710();
        return;
    }
    SUB_003707();
    return;
}

void game::SUB_003707() {
    a = 0x03;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00371D();
        return;
    }
    SUB_00370B();
    return;
}

void game::SUB_00370B() {
    x = myMapper->readCPU(0x00A8);
    SUB_00317C();
    return;
}

void game::SUB_003710() {
    opDEC(0x00A5, 3);
    pushAddress(0x003718);
    SUB_0043D3();
    if (handleReturnAddress(poppedEntry.value, 0x003718)) return;
    if (flgZ) {
        SUB_003720();
        return;
    }
    SUB_00371B();
    return;
}

void game::SUB_00371B() {
    a = 0xFD;
    SUB_00371D();
    return;
}

void game::SUB_00371D() {
    pushAddress(0x00371F);
    SUB_00370B();
    if (handleReturnAddress(poppedEntry.value, 0x00371F)) return;
    SUB_003720();
    return;
}

void game::SUB_003720() {
    SUB_003676();
    return;
}

void game::SUB_003723() {
    pushAddress(0x003725);
    SUB_002EDD();
    if (handleReturnAddress(poppedEntry.value, 0x003725)) return;
    pushAddress(0x003728);
    SUB_0036B8();
    if (handleReturnAddress(poppedEntry.value, 0x003728)) return;
    opINC(0x04CC + x, 1);
    opCMP(myMapper->readCPU(0x04CC + x), 0x3C);
    if (!flgC) {
        popAddress();
        return;
    }
    opINC(0x046C + x, 1);
    opCMP(myMapper->readCPU(0x046C + x), 0x07);
    if (flgC) {
        goto L_003741;
    }
    SUB_00365C();
    return;
L_003741:
    myMapper->writeCPU(0x048C + x, 0x00);
    popAddress();
}

void game::SUB_003747() {
    x = myMapper->readCPU(0x00A8);
    if (!(myMapper->readCPU(0x030C + x) & 0x80)) {
        goto L_003774;
    }
    a = myMapper->readCPU(0x046C + x);
    opAND(0x01);
    if (!flgZ) {
        SUB_003723();
        return;
    }
    myMapper->writeCPU(0x00A4, myMapper->readCPU(0x036C + x));
    a = myMapper->readCPU(0x032C + x);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x00A5, a);
    pushAddress(0x003764);
    SUB_0043D3();
    if (handleReturnAddress(poppedEntry.value, 0x003764)) return;
    if (flgZ) {
        SUB_00371B();
        return;
    }
    opINC(0x00A5, 3);
    pushAddress(0x00376F);
    SUB_0043D3();
    if (handleReturnAddress(poppedEntry.value, 0x00376F)) return;
    if (flgZ) {
        SUB_003720();
        return;
    }
    if (!flgZ) {
        SUB_003707();
        return;
    }
L_003774:
    myMapper->writeCPU(0x04AC + x, 0x01);
    a = myMapper->readCPU(0x018C + x);
    opORA(0x80);
    myMapper->writeCPU(0x018C + x, a);
    pushAddress(0x003783);
    SUB_00365C();
    if (handleReturnAddress(poppedEntry.value, 0x003783)) return;
    SUB_0030B4();
    return;
}

void game::SUB_0037A1() {
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x010C + x, 0x80);
    myMapper->writeCPU(0x0460 + x, 0x01);
    myMapper->writeCPU(0x030C + x, 0x97);
    y = myMapper->readCPU(0x048C + x);
    myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xB797 + y));
    y = myMapper->readCPU(0x0017);
    if (myMapper->readCPU(0x04CC + x) < 0x28) {
        if (myMapper->readCPU(0x0360) < myMapper->readCPU(0x036C + x)) {
            goto L_0037DF;
        }
        opINC(0x04CC + x, 1);
        if (myMapper->readCPU(0x036C + x) >= 0xF0) {
            goto L_0037F6;
        }
        opINC(0x036C + x, 2);
        goto L_0037F6;
    }
L_0037DF:
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0xB78F + y));
    myMapper->writeCPU(0x038C + x, a);
    a = myMapper->readCPU(0x036C + x);
    opSBC(0x01);
    myMapper->writeCPU(0x036C + x, a);
    if (!flgC) {
        SUB_003690();
        return;
    }
L_0037F6:
    opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
    if (flgC) {
        a = myMapper->readCPU(0x034C + x);
        opSBC(myMapper->readCPU(0xB799 + y));
        myMapper->writeCPU(0x034C + x, a);
        a = myMapper->readCPU(0x032C + x);
        opSBC(0x00);
    }
    else {
        a = myMapper->readCPU(0x034C + x);
        opADC(myMapper->readCPU(0xB799 + y));
        myMapper->writeCPU(0x034C + x, a);
        a = myMapper->readCPU(0x032C + x);
        opADC(0x00);
    }
    if (a < 0x14) {
        a = 0x14;
    }
    if (a >= 0xAC) {
        a = 0xAC;
    }
    myMapper->writeCPU(0x032C + x, a);
    y = myMapper->readCPU(0x0017);
    opCMP(myMapper->readCPU(0x03BC + x), myMapper->readCPU(0xB787 + y));
    if (!flgC) {
        opCMP(myMapper->readCPU(0x046C + x), myMapper->readCPU(0xB852 + y));
        if (flgC) {
            pushAddress(0x003840);
            SUB_00044F();
            if (handleReturnAddress(poppedEntry.value, 0x003840)) return;
            a = 0x0C;
            SUB_004B26();
            return;
        }
        opINC(0x03BC + x, 1);
        if (myMapper->readCPU(0x048C + x) != 0) {
            opINC(0x03BC + x, 1);
        }
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x048C + x) != 0) {
        a = 0x00;
        myMapper->writeCPU(0x048C + x, a);
        myMapper->writeCPU(0x03BC + x, a);
        popAddress();
        return;
    }
    a = 0x01;
    myMapper->writeCPU(0x048C + x, a);
    myMapper->writeCPU(0x03BC + x, a);
    a = 0x80;
    myMapper->writeCPU(0x00A0, a);
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x00A2, a);
    y = 0x09;
    x = 0x00;
    do {
        if (myMapper->readCPU(0x0136 + y) != 0) {
            goto L_003889;
        }
        myMapper->writeCPU((0x00A0 + x) & 0x00ff, y);
        opINX(1);
        opCMP(x, 0x03);
        if (flgC) {
            goto L_00388C;
        }
    L_003889:
        opDEY(1);
    } while (!flgN);
L_00388C:
    opDEX(1);
    if (!flgN) {
        goto L_003890;
    }
    popAddress();
    return;
L_003890:
    myMapper->writeCPU(0x00A9, x);
    y = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x036C + y));
    a = myMapper->readCPU(0x032C + y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x00A4, a);
    myMapper->writeCPU(0x0099, 0x00);
    do {
        y = myMapper->readCPU(0x00A9);
        x = myMapper->readCPU((0x00A0 + y) & 0x00ff);
        myMapper->writeCPU(0x0476 + x, myMapper->readCPU(0xB8EC + y));
        myMapper->writeCPU(0x0099, myMapper->readCPU(0xB8E9 + y));
        myMapper->writeCPU(0x009A, myMapper->readCPU(0xB8E6 + y));
        myMapper->writeCPU(0x0376 + x, myMapper->readCPU(0x00A3));
        myMapper->writeCPU(0x0336 + x, myMapper->readCPU(0x00A4));
        myMapper->writeCPU(0x0176 + x, 0x01);
        myMapper->writeCPU(0x0316 + x, 0x02);
        myMapper->writeCPU(0x0136 + x, 0x7A);
        myMapper->writeCPU(0x0116 + x, 0x01);
        a = x;
        flgC = false;
        opADC(0x0A);
        x = a;
        a = 0x40;
        pushAddress(0x0038E0);
        SUB_003D2C();
        if (handleReturnAddress(poppedEntry.value, 0x0038E0)) return;
        opDEC(0x00A9, 1);
    } while (!flgN);
    popAddress();
}

void game::SUB_003913() {
    popAddress();
}

void game::SUB_003914() {
    x = myMapper->readCPU(0x00A8);
    if (myMapper->readCPU(0x03AC + x) & 0x80) {
        myMapper->writeCPU(0x04EC + x, 0x00);
    }
    myMapper->writeCPU(0x010C + x, 0x90);
    myMapper->writeCPU(0x0460 + x, 0x03);
    myMapper->writeCPU(0x030C + x, 0x98);
    y = myMapper->readCPU(0x046C + x);
    if (y < 0x07) {
        a = myMapper->readCPU(0xB8EF + y);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == myMapper->readCPU(0x012C + x)) {
                SUB_0039A8();
                return;
            }
            myMapper->writeCPU(0x012C + x, a);
            opCMP(a, 0x6C);
            if (flgZ) {
                SUB_0039A8();
                return;
            }
            pushAddress(0x003949);
            SUB_00045B();
            if (handleReturnAddress(poppedEntry.value, 0x003949)) return;
            a = 0x08;
            pushAddress(0x00394E);
            SUB_006C1E();
            if (handleReturnAddress(poppedEntry.value, 0x00394E)) return;
            x = myMapper->readCPU(0x00A8);
            if (myMapper->readCPU(0x001A) != 0) {
                myMapper->writeCPU(0x04EC + x, 0xFF);
                myMapper->writeCPU(0x03AC + x, 0x00);
            }
            SUB_0039A8();
            return;
        }
    }
    opCMP(myMapper->readCPU(0x0019), 0x01);
    if (flgZ) {
        x = myMapper->readCPU(0x00A8);
        opCMP(myMapper->readCPU(0x04CC + x), 0x01);
        if (flgZ) {
            opCMP(myMapper->readCPU(0x04AC + x), 0x78);
            if (flgC) {
                goto L_00397A;
            }
            opINC(0x0039, 1);
        }
    }
L_00397A:
    a = 0x10;
    pushAddress(0x00397E);
    SUB_000455();
    if (handleReturnAddress(poppedEntry.value, 0x00397E)) return;
    x = myMapper->readCPU(0x0018);
    opINC((0x003B + x) & 0x00ff, 1);
    SUB_003983();
    return;
}

void game::SUB_003983() {
    a = 0xAC;
    pushAddress(0x003987);
    SUB_004B26();
    if (handleReturnAddress(poppedEntry.value, 0x003987)) return;
    myMapper->writeCPU(0x016C + x, 0x04);
    a = 0x00;
    y = 0x01;
    do {
        myMapper->writeCPU(0x030B + x, a);
        myMapper->writeCPU(0x012B + x, a);
        myMapper->writeCPU(0x010B + x, a);
        opDEX(1);
        opDEY(1);
    } while (!flgN);
    opCMP(myMapper->readCPU(0x0100), 0x02);
    if (flgC) {
        goto L_0039A7;
    }
    opINC(0x001B, 1);
L_0039A7:
    popAddress();
}

void game::SUB_0039A8() {
    if (myMapper->readCPU(0x036C + x) < 0xA4) {
        SUB_003A0A();
        return;
    }
    opDEC(0x036C + x, 1);
    if (myMapper->readCPU(0x048C + x) != 0) {
        SUB_003A0A();
        return;
    }
    SUB_0039B7();
    return;
}

void game::SUB_0039B7() {
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x045F + x, 0x02);
    myMapper->writeCPU(0x045E + x, 0x00);
    myMapper->writeCPU(0x012B + x, 0x85);
    a = 0x03;
    y = myMapper->readCPU(0x048C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_0039D1;
    }
    a = 0x00;
L_0039D1:
    myMapper->writeCPU(0x018A + x, a);
    myMapper->writeCPU(0x012A + x, 0x32);
    a = myMapper->readCPU(0x036C + x);
    myMapper->writeCPU(0x036B + x, a);
    myMapper->writeCPU(0x036A + x, a);
    a = myMapper->readCPU(0x032C + x);
    myMapper->writeCPU(0x032A + x, a);
    flgC = true;
    opSBC(0x14);
    myMapper->writeCPU(0x032B + x, a);
    pushAddress(0x0039F0);
    SUB_0039F2();
    if (handleReturnAddress(poppedEntry.value, 0x0039F0)) return;
    opDEX(1);
    SUB_0039F2();
    return;
}

void game::SUB_0039F2() {
    a = 0x00;
    myMapper->writeCPU(0x018C + x, a);
    myMapper->writeCPU(0x048B + x, a);
    myMapper->writeCPU(0x04EB + x, a);
    myMapper->writeCPU(0x030B + x, 0x99);
    myMapper->writeCPU(0x010B + x, 0x80);
    x = myMapper->readCPU(0x00A8);
    popAddress();
}

void game::SUB_003A0A() {
    if (myMapper->readCPU(0x0360) < myMapper->readCPU(0x036C + x)) {
        goto L_003A18;
    }
    opINC(0x036C + x, 2);
L_003A18:
    y = myMapper->readCPU(0x0017);
    opCMP(myMapper->readCPU(0x042C + x), myMapper->readCPU(0xB90A + y));
    if (flgC) {
        y = 0x00;
        a = myMapper->readCPU(0x032C + x);
        flgC = true;
        opSBC(0x10);
        opCMP(a, myMapper->readCPU(0x0320));
        if (!flgC) {
            opINY(1);
        }
        myMapper->writeCPU(0x03EC + x, y);
    }
    y = myMapper->readCPU(0x0017);
    if (myMapper->readCPU(0x03EC + x) == 0) {
        a = myMapper->readCPU(0x034C + x);
        opSBC(myMapper->readCPU(0xB8F8 + y));
        myMapper->writeCPU(0x034C + x, a);
        a = myMapper->readCPU(0x032C + x);
        opSBC(myMapper->readCPU(0xB901 + y));
    }
    else {
        a = myMapper->readCPU(0x034C + x);
        opADC(myMapper->readCPU(0xB8F8 + y));
        myMapper->writeCPU(0x034C + x, a);
        a = myMapper->readCPU(0x032C + x);
        opADC(myMapper->readCPU(0xB901 + y));
    }
    if (a < 0x18) {
        a = 0x18;
    }
    if (a >= 0xA8) {
        a = 0xA8;
    }
    myMapper->writeCPU(0x032C + x, a);
    pushAddress(0x003A6D);
    SUB_0039B7();
    if (handleReturnAddress(poppedEntry.value, 0x003A6D)) return;
    y = myMapper->readCPU(0x0017);
    opCMP(myMapper->readCPU(0x042C + x), myMapper->readCPU(0xB90A + y));
    if (!flgC) {
        opINC(0x042C + x, 1);
        opINC(0x04AC + x, 1);
        if (flgZ) {
            opINC(0x04CC + x, 1);
            y = myMapper->readCPU(0x04CC + x);
            if (y >= 0x01) {
                myMapper->writeCPU(0x048C + x, 0x01);
            }
            if (y >= 0x05) {
                myMapper->writeCPU(0x048C + x, 0x00);
            }
            opCMP(y, 0x06);
            if (!flgC) {
                goto L_003A9F;
            }
            SUB_003983();
            return;
        }
    L_003A9F:
        popAddress();
        return;
    }
    myMapper->writeCPU(0x042C + x, 0x00);
    myMapper->writeCPU(0x00A9, 0x03);
    do {
        x = myMapper->readCPU(0x00A9);
        a = 0x00;
        myMapper->writeCPU(0x0476 + x, a);
        myMapper->writeCPU(0x0099, a);
        myMapper->writeCPU(0x009A, a);
        y = myMapper->readCPU(0x00A8);
        a = myMapper->readCPU(0x036C + y);
        flgC = false;
        opADC(myMapper->readCPU(0xBAF7 + x));
        myMapper->writeCPU(0x0376 + x, a);
        a = myMapper->readCPU(0x032C + y);
        flgC = false;
        opADC(myMapper->readCPU(0xBAFB + x));
        myMapper->writeCPU(0x0336 + x, a);
        myMapper->writeCPU(0x0176 + x, 0x02);
        a = 0x00;
        myMapper->writeCPU(0x0316 + x, a);
        myMapper->writeCPU(0x0116 + x, a);
        myMapper->writeCPU(0x0136 + x, 0x41);
        a = 0x00;
        myMapper->writeCPU(0x03F6 + x, a);
        myMapper->writeCPU(0x03C6 + x, a);
        y = myMapper->readCPU(0x0017);
        myMapper->writeCPU(0x0436 + x, myMapper->readCPU(0xBAFF + y));
        myMapper->writeCPU(0x0456 + x, myMapper->readCPU(0xBB07 + y));
        opDEC(0x00A9, 1);
    } while (!flgN);
    popAddress();
}

void game::SUB_003B0F() {
    x = 0x09;
    y = myMapper->readCPU(0x048C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opCMP(myMapper->readCPU(0x004F), 0xFF);
        if (!flgZ) {
            SUB_004E94();
            return;
        }
        opDEC(0x004C, 1);
        if (!flgZ) {
            goto L_003B81;
        }
        pushAddress(0x003B25);
        SUB_002EF8();
        if (handleReturnAddress(poppedEntry.value, 0x003B25)) return;
        opINC(0x001B, 1);
        popAddress();
        return;
    }
    opINC(0x014C + x, 1);
    opCMP(myMapper->readCPU(0x014C + x), 0x06);
    if (flgC) {
        a = myMapper->readCPU(0x0475);
        opASL_A(1);
        y = a;
        a = myMapper->readCPU(0xBB82 + y);
        opCMP(a, 0xFF);
        if (!flgZ) {
            opINC(0x0475, 1);
            flgC = false;
            opADC(myMapper->readCPU(0x0375));
            myMapper->writeCPU(0x0375, a);
            a = myMapper->readCPU(0xBB83 + y);
            opLSR_A(4);
            myMapper->writeCPU(0x0098, a);
            a = myMapper->readCPU(0x0335);
            flgC = true;
            opSBC(myMapper->readCPU(0x0098));
            myMapper->writeCPU(0x0335, a);
            a = myMapper->readCPU(0xBB83 + y);
            opAND(0x0F);
            flgC = false;
            opADC(0x96);
            SUB_003647();
            return;
        }
        myMapper->writeCPU(0x0135, 0x00);
        if (myMapper->readCPU(0x00D4) != 0) {
            goto L_003B81;
        }
        a = 0xAC;
        opDEX(1);
        pushAddress(0x003B74);
        SUB_004B28();
        if (handleReturnAddress(poppedEntry.value, 0x003B74)) return;
        myMapper->writeCPU(0x016C + x, 0x05);
        opINC(0x0495, 1);
        myMapper->writeCPU(0x004E, 0xA0);
    }
L_003B81:
    popAddress();
}

void game::SUB_003BB7() {
    if (myMapper->readCPU(0x005D) != 0) {
        goto L_003C19;
    }
    y = 0x01;
    a = myMapper->readCPU(0x0019);
    opORA(myMapper->readCPU(0x001A));
    if (!flgZ) {
        a = myMapper->readCPU(0x0002);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x001A);
            setLoadFlag(a);
            if (!flgZ) {
                opINY(1);
                if (a >= 0x02) {
                    opINY(1);
                }
                if (myMapper->readCPU(0x0046) == 0) {
                    goto L_003BE5;
                }
                opINY(1);
                if (!flgZ) {
                    goto L_003BE5;
                }
            }
            if (myMapper->readCPU(0x0046) != 0) {
                if (myMapper->readCPU(0x0019) < 0x02) {
                    goto L_003BE5;
                }
                opINY(1);
            }
        }
    L_003BE5:
        if (myMapper->readCPU(0x0017) < 0x03) {
            goto L_003BEC;
        }
        opINY(1);
    }
L_003BEC:
    myMapper->writeCPU(0x0098, y);
    myMapper->writeCPU(0x00A8, 0x09);
    do {
        x = myMapper->readCPU(0x00A8);
        a = myMapper->readCPU(0x030C + x);
        opAND(0x7F);
        opCMP(a, 0x03);
        if (flgC) {
            a = myMapper->readCPU(0x040C + x);
            opSBC(myMapper->readCPU(0x0098));
            if (flgC) {
                goto L_003C12;
            }
            a = myMapper->readCPU(0x04EC + x);
            setLoadFlag(a);
            if (flgZ) {
                goto L_003C15;
            }
            myMapper->writeCPU(0x040C + x, a);
            pushAddress(0x003C0E);
            SUB_003C44();
            if (handleReturnAddress(poppedEntry.value, 0x003C0E)) return;
            goto L_003C19;
        L_003C12:
            myMapper->writeCPU(0x040C + x, a);
        }
    L_003C15:
        opDEC(0x00A8, 1);
    } while (!flgN);
L_003C19:
    myMapper->writeCPU(0x00A9, 0x13);
    myMapper->writeCPU(0x00A8, 0x09);
    do {
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0136 + x) == 0) {
            goto L_003C2B;
        }
        pushAddress(0x003C2A);
        SUB_003DD5();
        if (handleReturnAddress(poppedEntry.value, 0x003C2A)) return;
    L_003C2B:
        opDEC(0x00A9, 1);
        opDEC(0x00A8, 1);
    } while (!flgN);
    popAddress();
}

void game::SUB_003C44() {
    if (myMapper->readCPU(0x001A) != 0) {
        goto L_003C59;
    }
    if (myMapper->readCPU(0x0019) < 0x02) {
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0360) >= myMapper->readCPU(0x036C + x)) {
            popAddress();
            return;
        }
    }
L_003C59:
    x = 0x09;
    do {
        if (myMapper->readCPU(0x0136 + x) == 0) {
            goto L_003C68;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_003C68:
    myMapper->writeCPU(0x00A9, x);
    x = myMapper->readCPU(0x00A8);
    y = 0x00;
    a = myMapper->readCPU(0x010C + x);
    setLoadFlag(a);
    if (flgN) {
        if (a >= 0x90) {
            goto L_003C78;
        }
        opINY(1);
    }
L_003C78:
    x = myMapper->readCPU(0x00A9);
    myMapper->writeCPU(0x0136 + x, myMapper->readCPU(0xBC64 + y));
    a = myMapper->readCPU(0xBC66 + y);
    myMapper->writeCPU(0x0316 + x, a);
    myMapper->writeCPU(0x0176 + x, a);
    myMapper->writeCPU(0x0116 + x, 0x00);
    y = myMapper->readCPU(0x00A8);
    x = myMapper->readCPU(0x0496 + y);
    myMapper->writeCPU(0x0098, myMapper->readCPU(0xBC32 + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0xBC3B + x));
    x = myMapper->readCPU(0x00A9);
    a = myMapper->readCPU(0x032C + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0336 + x, a);
    a = myMapper->readCPU(0x036C + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0376 + x, a);
    SUB_003CB1();
    return;
}

void game::SUB_003CB1() {
    a = x;
    flgC = false;
    opADC(0x0A);
    SUB_003CB5();
    return;
}

void game::SUB_003CB5() {
    myMapper->writeCPU(0x00A9, a);
    x = a;
    if (myMapper->readCPU(0x0017) >= 0x03) {
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x0320));
        a = myMapper->readCPU(0x0002);
        opASL_A(1);
        a = myMapper->readCPU(0x0002);
        opLSR_A(2);
        opAND(0x1F);
        opADC(myMapper->readCPU(0x0360));
        if (flgC) {
            a = 0xF8;
        }
        myMapper->writeCPU(0x0099, a);
    }
    else {
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x0320));
        myMapper->writeCPU(0x0099, myMapper->readCPU(0x0360));
    }
    y = 0x00;
    a = myMapper->readCPU(0x032C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0098));
    if (!flgC) {
        opINY(1);
        opEOR(0xFF);
    }
    if (flgZ) {
        a = 0x01;
    }
    myMapper->writeCPU(0x009C, a);
    a = myMapper->readCPU(0x036C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0099));
    if (!flgC) {
        opINY(2);
        opEOR(0xFF);
    }
    if (flgZ) {
        a = 0x01;
    }
    myMapper->writeCPU(0x00A0, y);
    y = 0x00;
    x = myMapper->readCPU(0x009C);
    myMapper->writeCPU(0x009D, a);
    if (a >= myMapper->readCPU(0x009C)) {
        goto L_003D16;
    }
    a = myMapper->readCPU(0x009C);
    x = myMapper->readCPU(0x009D);
    opINY(1);
L_003D16:
    myMapper->writeCPU(0x009B, a);
    myMapper->writeCPU(0x00A1, y);
    y = 0x00;
    pushAddress(0x003D1E);
    SUB_0003B5();
    if (handleReturnAddress(poppedEntry.value, 0x003D1E)) return;
    x = myMapper->readCPU(0x00A9);
    myMapper->writeCPU(0x046C + x, myMapper->readCPU(0x00A0));
    if (myMapper->readCPU(0x00A1) != 0) {
        SUB_003D7E();
        return;
    }
    a = 0x00;
    SUB_003D2C();
    return;
}

void game::SUB_003D2C() {
    myMapper->writeCPU(0x044C + x, a);
    myMapper->writeCPU(0x042C + x, 0x01);
    myMapper->writeCPU(0x03EC + x, myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x03BC + x, myMapper->readCPU(0x0099));
    opLSR_M(0x0099, 1);
    opROR_M(0x009A, 1);
    if (myMapper->readCPU(0x001A) != 0) {
        a = myMapper->readCPU(0x009A);
        opADC(myMapper->readCPU(0x03EC + x));
        myMapper->writeCPU(0x03EC + x, a);
        a = myMapper->readCPU(0x0099);
        opADC(myMapper->readCPU(0x03BC + x));
        myMapper->writeCPU(0x03BC + x, a);
        myMapper->writeCPU(0x044C + x, 0x80);
    }
    opLSR_M(0x0099, 1);
    opROR_M(0x009A, 1);
    opCMP(myMapper->readCPU(0x0017), 0x02);
    if (!flgC) {
        goto L_003D7D;
    }
    a = myMapper->readCPU(0x009A);
    opADC(myMapper->readCPU(0x03EC + x));
    myMapper->writeCPU(0x03EC + x, a);
    a = myMapper->readCPU(0x0099);
    opADC(myMapper->readCPU(0x03BC + x));
    myMapper->writeCPU(0x03BC + x, a);
    a = myMapper->readCPU(0x044C + x);
    opADC(0x40);
    myMapper->writeCPU(0x044C + x, a);
L_003D7D:
    popAddress();
}

void game::SUB_003D7E() {
    myMapper->writeCPU(0x03BC + x, 0x01);
    myMapper->writeCPU(0x03EC + x, 0x00);
    myMapper->writeCPU(0x044C + x, myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x042C + x, myMapper->readCPU(0x0099));
    opLSR_M(0x0099, 1);
    opROR_M(0x009A, 1);
    if (myMapper->readCPU(0x001A) != 0) {
        a = myMapper->readCPU(0x009A);
        opADC(myMapper->readCPU(0x044C + x));
        myMapper->writeCPU(0x044C + x, a);
        a = myMapper->readCPU(0x0099);
        opADC(myMapper->readCPU(0x042C + x));
        myMapper->writeCPU(0x042C + x, a);
        myMapper->writeCPU(0x03EC + x, 0x80);
    }
    opLSR_M(0x0099, 1);
    opROR_M(0x009A, 1);
    opCMP(myMapper->readCPU(0x0017), 0x02);
    if (!flgC) {
        goto L_003DD1;
    }
    a = myMapper->readCPU(0x009A);
    opADC(myMapper->readCPU(0x044C + x));
    myMapper->writeCPU(0x044C + x, a);
    a = myMapper->readCPU(0x0099);
    opADC(myMapper->readCPU(0x042C + x));
    myMapper->writeCPU(0x042C + x, a);
    a = myMapper->readCPU(0x03EC + x);
    opADC(0x40);
    myMapper->writeCPU(0x03EC + x, a);
L_003DD1:
    popAddress();
}

void game::SUB_003DD5() {
    x = myMapper->readCPU(0x00A9);
    y = myMapper->readCPU(0x010C + x);
    setLoadFlag(y);
    if (flgZ) {
        SUB_003DFA();
        return;
    }
    if (myMapper->readCPU(0x014C + x) == 0) {
        myMapper->writeCPU(0x014C + x, 0x10);
        opINY(1);
        if (y < 0x04) {
            goto L_003DED;
        }
        y = 0x01;
    L_003DED:
        myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xBDD1 + y));
        myMapper->writeCPU(0x010C + x, y);
    }
    opDEC(0x014C + x, 1);
    SUB_003DFA();
    return;
}

void game::SUB_003DFA() {
    if (myMapper->readCPU(0x046C + x) < 0x02) {
        goto L_003E17;
    }
    a = myMapper->readCPU(0x044C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x038C + x));
    myMapper->writeCPU(0x038C + x, a);
    a = myMapper->readCPU(0x042C + x);
    opADC(myMapper->readCPU(0x036C + x));
    myMapper->writeCPU(0x036C + x, a);
    goto L_003E2A;
L_003E17:
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x044C + x));
    myMapper->writeCPU(0x038C + x, a);
    a = myMapper->readCPU(0x036C + x);
    opSBC(myMapper->readCPU(0x042C + x));
    myMapper->writeCPU(0x036C + x, a);
L_003E2A:
    opCMP(a, 0x02);
    if (flgC) {
        opCMP(a, 0xFC);
        if (!flgC) {
            a = myMapper->readCPU(0x046C + x);
            opAND(0x01);
            if (!flgZ) {
                a = myMapper->readCPU(0x03EC + x);
                flgC = false;
                opADC(myMapper->readCPU(0x034C + x));
                myMapper->writeCPU(0x034C + x, a);
                a = myMapper->readCPU(0x03BC + x);
                opADC(myMapper->readCPU(0x032C + x));
                myMapper->writeCPU(0x032C + x, a);
            }
            else {
                a = myMapper->readCPU(0x034C + x);
                flgC = true;
                opSBC(myMapper->readCPU(0x03EC + x));
                myMapper->writeCPU(0x034C + x, a);
                a = myMapper->readCPU(0x032C + x);
                opSBC(myMapper->readCPU(0x03BC + x));
                myMapper->writeCPU(0x032C + x, a);
            }
            opCMP(a, 0x08);
            if (flgC) {
                opCMP(a, 0xC4);
                if (flgC) {
                    goto L_003E6B;
                }
                popAddress();
                return;
            }
        }
    }
L_003E6B:
    SUB_002EF8();
    return;
}

void game::SUB_003E93() {
    a = myMapper->readCPU(0x030C + y);
    opAND(0x7F);
    x = a;
    opCMP(x, 0x22);
    if (!flgC) {
        a = myMapper->readCPU(0xBE6E + x);
        setLoadFlag(a);
        if (!flgZ) {
            pushAddress(0x003EA4);
            SUB_006C1E();
            if (handleReturnAddress(poppedEntry.value, 0x003EA4)) return;
        }
    }
    a = myMapper->readCPU(0x03AC + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x01) {
            goto L_003EB5;
        }
        x = a;
        a = 0x00;
        opDEC((0x0048 + x) & 0x00ff, 1);
        if (!flgZ) {
            goto L_003EB7;
        }
    L_003EB5:
        a = 0x01;
    L_003EB7:
        myMapper->writeCPU(0x03AC + y, a);
    }
    x = 0x01;
    a = myMapper->readCPU(0x030C + y);
    opAND(0x1F);
    if (a == 0x1A) {
        x = 0x03;
    }
    if (a != 0x05) {
        goto L_003ECD;
    }
    x = 0x00;
L_003ECD:
    myMapper->writeCPU(0x016C + y, x);
    myMapper->writeCPU(0x030C + y, 0x02);
    myMapper->writeCPU(0x014C + y, 0x03);
    a = 0x00;
    myMapper->writeCPU(0x018C + y, a);
    myMapper->writeCPU(0x010C + y, a);
    myMapper->writeCPU(0x012C + y, a);
    myMapper->writeCPU(0x042C + y, a);
    popAddress();
}

void game::SUB_003EF3() {
    myMapper->writeCPU(0x00A9, 0x90);
    do {
        x = myMapper->readCPU(0x00A9);
        if (myMapper->readCPU(0x0600 + x) == 0) {
            goto L_003F01;
        }
        pushAddress(0x003F00);
        SUB_003F0B();
        if (handleReturnAddress(poppedEntry.value, 0x003F00)) return;
    L_003F01:
        a = myMapper->readCPU(0x00A9);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x00A9, a);
    } while (!flgN);
    popAddress();
}

void game::SUB_003F0B() {
    myMapper->writeCPU(0x00AB, 0x05);
    a = x;
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x00AA, a);
    do {
        x = myMapper->readCPU(0x00AA);
        a = myMapper->readCPU(0x00A0);
        flgC = true;
        opSBC(myMapper->readCPU(0x0618 + x));
        opCMP(a, myMapper->readCPU(0x00A3));
        if (flgC) {
            goto L_003F2A;
        }
        a = myMapper->readCPU(0x00A1);
        opSBC(myMapper->readCPU(0x0620 + x));
        if (a < 0x0A) {
            goto L_003F31;
        }
    L_003F2A:
        opDEC(0x00AA, 1);
        opDEC(0x00AB, 1);
    } while (!flgN);
    popAddress();
    return;
L_003F31:
    opCMP(myMapper->readCPU(0x00AB), 0x02);
    if (flgZ) {
        goto L_003F3A;
    }
    do {
        SUB_0040B7();
        return;
    L_003F3A:
        x = myMapper->readCPU(0x00A9);
        opINC(0x0605 + x, 1);
        a = myMapper->readCPU(0x0605 + x);
        y = myMapper->readCPU(0x0017);
        opCMP(a, myMapper->readCPU(0xBEEA + y));
    } while (!flgC);
    pushAddress(0x003F4B);
    SUB_000453();
    if (handleReturnAddress(poppedEntry.value, 0x003F4B)) return;
    x = 0x00;
    a = 0x00;
    y = myMapper->readCPU(0x00A9);
    x = myMapper->readCPU(0x0600 + y);
    opDEC(0x016C + x, 1);
    myMapper->writeCPU(0x0600 + y, 0x00);
    x = 0x00;
    myMapper->writeCPU(0x036C + x, myMapper->readCPU(0x061A + y));
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0x0622 + y));
    a = 0x0C;
    x = 0x00;
    pushAddress(0x003F71);
    SUB_004B28();
    if (handleReturnAddress(poppedEntry.value, 0x003F71)) return;
    SUB_0040B7();
    return;
}

void game::SUB_003F75() {
    y = myMapper->readCPU(0x00A9);
    if (myMapper->readCPU(0x0316 + y) != 0) {
        goto L_003F7D;
    }
    do {
        do {
            popAddress();
            return;
        L_003F7D:
            a = myMapper->readCPU(0x00A1);
            flgC = true;
            opSBC(myMapper->readCPU(0x0336 + y));
            opCMP(a, 0x10);
        } while (flgC);
        a = myMapper->readCPU(0x00A0);
        opSBC(myMapper->readCPU(0x0376 + y));
    } while (a >= myMapper->readCPU(0x00A3));
    opCMP(myMapper->readCPU(0x0316 + y), 0x02);
    if (flgZ) {
        a = 0x05;
        pushAddress(0x003F9B);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x003F9B)) return;
        SUB_0040B7();
        return;
    }
    opINC(0x005D, 1);
    x = myMapper->readCPU(0x0136 + y);
    myMapper->writeCPU(0x00AA, x);
    a = 0x00;
    myMapper->writeCPU(0x0136 + y, a);
    myMapper->writeCPU(0x0176 + y, a);
    myMapper->writeCPU(0x0316 + y, a);
    pushAddress(0x003FB3);
    SUB_000463();
    if (handleReturnAddress(poppedEntry.value, 0x003FB3)) return;
    a = 0x09;
    pushAddress(0x003FB8);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x003FB8)) return;
    opCMP(myMapper->readCPU(0x00AA), 0x59);
    if (flgZ) {
        goto L_003FC2;
    }
    SUB_0040AE();
    return;
L_003FC2:
    SUB_0040B7();
    return;
}

void game::SUB_003FE2() {
    myMapper->writeCPU(0x00A8, 0x08);
    do {
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0123 + x) != 0) {
            y = myMapper->readCPU(0x0163 + x);
            a = myMapper->readCPU(0x0363 + x);
            flgC = false;
            opADC(myMapper->readCPU(0xBFCE + y));
            if (flgC) {
                a = 0xFF;
            }
            myMapper->writeCPU(0x00A0, a);
            myMapper->writeCPU(0x00A3, myMapper->readCPU(0xBFD2 + y));
            a = myMapper->readCPU(0x0323 + x);
            flgC = false;
            opADC(myMapper->readCPU(0xBFD6 + y));
            myMapper->writeCPU(0x00A1, a);
            x = 0x09;
            myMapper->writeCPU(0x00A9, x);
            do {
                y = myMapper->readCPU(0x00A9);
                if (myMapper->readCPU(0x030C + y) & 0x80) {
                    a = myMapper->readCPU(0x00A0);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x036C + y));
                    opCMP(a, myMapper->readCPU(0x00A3));
                    if (!flgC) {
                        x = myMapper->readCPU(0x0460 + y);
                        a = myMapper->readCPU(0x00A1);
                        opSBC(myMapper->readCPU(0x032C + y));
                        opCMP(a, myMapper->readCPU(0xBFDE + x));
                        if (flgC) {
                            goto L_004030;
                        }
                        pushAddress(0x00402F);
                        SUB_004055();
                        if (handleReturnAddress(poppedEntry.value, 0x00402F)) return;
                    }
                }
            L_004030:
                pushAddress(0x004032);
                SUB_003F75();
                if (handleReturnAddress(poppedEntry.value, 0x004032)) return;
                opDEC(0x00A9, 1);
            } while (!flgN);
            if (myMapper->readCPU(0x0019) == 0x04) {
                x = myMapper->readCPU(0x00A8);
                if (myMapper->readCPU(0x0123 + x) == 0) {
                    goto L_004047;
                }
                pushAddress(0x004046);
                SUB_003EF3();
                if (handleReturnAddress(poppedEntry.value, 0x004046)) return;
            }
        }
    L_004047:
        opDEC(0x00A8, 1);
    } while (!flgN);
    if (myMapper->readCPU(0x005C) < 0x02) {
        goto L_004052;
    }
    popAddress();
    return;
L_004052:
    SUB_0040C7();
    return;
}

void game::SUB_004055() {
    if (!(myMapper->readCPU(0x030C + y) & 0x80)) {
        SUB_0040B7();
        return;
    }
    if (myMapper->readCPU(0x010C + y) & 0x80) {
        if (myMapper->readCPU(0x012C + y) == 0) {
            goto L_004070;
        }
        opCMP(myMapper->readCPU(0x030C + y), 0x94);
        if (!flgZ) {
            a = 0x05;
            pushAddress(0x00406F);
            SUB_006C1E();
            if (handleReturnAddress(poppedEntry.value, 0x00406F)) return;
        }
    L_004070:
        if (myMapper->readCPU(0x048C + y) == 0) {
            SUB_0040B7();
            return;
        }
        x = myMapper->readCPU(0x00A9);
        a = 0x01;
        y = myMapper->readCPU(0x0460 + x);
        setLoadFlag(y);
        if (!flgZ) {
            y = myMapper->readCPU(0x00A8);
            if (y >= 0x06) {
                a = 0x02;
            }
        }
        flgC = false;
        opADC(myMapper->readCPU(0x046C + x));
        myMapper->writeCPU(0x046C + x, a);
        SUB_0040B7();
        return;
    }
    x = myMapper->readCPU(0x00A9);
    opCMP(myMapper->readCPU(0x030C + x), 0x9A);
    if (!flgZ) {
        goto L_0040A6;
    }
    opINC(0x04AC + x, 1);
    a = myMapper->readCPU(0x04AC + x);
    y = myMapper->readCPU(0x0017);
    opCMP(a, myMapper->readCPU(0xBFC5 + y));
    if (!flgC) {
        SUB_0040AE();
        return;
    }
L_0040A6:
    pushAddress(0x0040A8);
    SUB_000463();
    if (handleReturnAddress(poppedEntry.value, 0x0040A8)) return;
    y = myMapper->readCPU(0x00A9);
    pushAddress(0x0040AD);
    SUB_003E93();
    if (handleReturnAddress(poppedEntry.value, 0x0040AD)) return;
    SUB_0040AE();
    return;
}

void game::SUB_0040AE() {
    x = myMapper->readCPU(0x00A8);
    opCMP(myMapper->readCPU(0x0163 + x), 0x01);
    if (flgZ) {
        SUB_0040C6();
        return;
    }
    SUB_0040B7();
    return;
}

void game::SUB_0040B7() {
    a = 0x00;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x00A9, a);
    SUB_0040BD();
    return;
}

void game::SUB_0040BD() {
    myMapper->writeCPU(0x0123 + x, a);
    myMapper->writeCPU(0x0163 + x, a);
    myMapper->writeCPU(0x0103 + x, a);
    SUB_0040C6();
    return;
}

void game::SUB_0040C6() {
    popAddress();
}

void game::SUB_0040C7() {
    if (myMapper->readCPU(0x0100) < 0x02) {
        goto L_004101;
    }
    if (myMapper->readCPU(0x0140) == 0) {
        if (myMapper->readCPU(0x0120) == 0) {
            goto L_0040F4;
        }
        myMapper->writeCPU(0x0140, 0x0A);
        x = myMapper->readCPU(0x0160);
        opINC(0x0160, 1);
        a = myMapper->readCPU(0xC0FA + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0120, a);
        if (flgZ) {
            myMapper->writeCPU(0x0121, a);
            myMapper->writeCPU(0x0122, a);
            myMapper->writeCPU(0x0140, a);
        }
    }
L_0040F4:
    opDEC(0x0140, 1);
    SUB_0042A5();
    return;
L_004101:
    myMapper->writeCPU(0x00A8, 0x09);
    a = myMapper->readCPU(0x0360);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x00A0, a);
    a = myMapper->readCPU(0x0320);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x00A1, a);
    do {
        y = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x030C + y) != 0) {
            x = myMapper->readCPU(0x0460 + y);
            a = myMapper->readCPU(0x00A0);
            flgC = true;
            opSBC(myMapper->readCPU(0x036C + y));
            if (flgC) {
                opCMP(a, myMapper->readCPU(0xBFDA + x));
                if (flgC) {
                    goto L_004136;
                }
                a = myMapper->readCPU(0x00A1);
                opSBC(myMapper->readCPU(0x032C + y));
                if (a < myMapper->readCPU(0xBFDE + x)) {
                    goto L_00416E;
                }
            }
        }
    L_004136:
        opDEC(0x00A8, 1);
    } while (!flgN);
    SUB_00420A();
    return;
    do {
        a = myMapper->readCPU(0x0018);
        opASL_A(2);
        x = a;
        a = myMapper->readCPU(0x07E5 + x);
        opLSR_A(1);
        if (flgC) {
            goto L_004136;
        }
        myMapper->writeCPU(0x030C + y, 0x01);
        myMapper->writeCPU(0x012C + y, 0xA3);
        x = myMapper->readCPU(0x0018);
        opINC((0x0020 + x) & 0x00ff, 1);
        goto L_004166;
    L_004159:
        myMapper->writeCPU(0x030C + y, 0x01);
        myMapper->writeCPU(0x012C + y, 0xA1);
        pushAddress(0x004165);
        SUB_00044B();
        if (handleReturnAddress(poppedEntry.value, 0x004165)) return;
    L_004166:
        a = 0x36;
        pushAddress(0x00416A);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x00416A)) return;
        goto L_004136;
    L_00416E:
        a = myMapper->readCPU(0x030C + y);
        opAND(0x7F);
    } while (a == 0x27);
    if (a == 0x29) {
        goto L_004159;
    }
    if (a < 0x03) {
        if (a != 0x01) {
            goto L_004136;
        }
        a = myMapper->readCPU(0x010C + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_004136;
        }
        opCMP(a, 0x06);
        if (!flgZ) {
            pushAddress(0x00418E);
            SUB_0041FD();
            if (handleReturnAddress(poppedEntry.value, 0x00418E)) return;
            a = 0x0B;
            pushAddress(0x004193);
            SUB_006C1E();
            if (handleReturnAddress(poppedEntry.value, 0x004193)) return;
            y = 0x09;
            do {
                if (myMapper->readCPU(0x010C + y) & 0x80) {
                    goto L_0041A9;
                }
                a = myMapper->readCPU(0x030C + y);
                setLoadFlag(a);
                if (flgN) {
                    opAND(0x7F);
                    if (a < 0x03) {
                        goto L_0041A9;
                    }
                    pushAddress(0x0041A8);
                    SUB_003E93();
                    if (handleReturnAddress(poppedEntry.value, 0x0041A8)) return;
                }
            L_0041A9:
                opDEY(1);
            } while (!flgN);
            SUB_00420A();
            return;
        }
        pushAddress(0x0041B1);
        SUB_0041FD();
        if (handleReturnAddress(poppedEntry.value, 0x0041B1)) return;
        pushAddress(0x0041B4);
        SUB_00094B();
        if (handleReturnAddress(poppedEntry.value, 0x0041B4)) return;
        goto L_004136;
    }
    if (!(myMapper->readCPU(0x030C + y) & 0x80)) {
        goto L_0041CD;
    }
    if (myMapper->readCPU(0x0046) == 0) {
        SUB_0041D6();
        return;
    }
    opDEC(0x0046, 1);
    if (!(myMapper->readCPU(0x010C + y) & 0x80)) {
        goto L_0041D0;
    }
    x = myMapper->readCPU(0x00A8);
    opINC(0x046C + x, 1);
L_0041CD:
    goto L_004136;
L_0041D0:
    pushAddress(0x0041D2);
    SUB_003E93();
    if (handleReturnAddress(poppedEntry.value, 0x0041D2)) return;
    goto L_004136;
}

void game::SUB_0041D6() {
    opCMP(myMapper->readCPU(0x001B), 0x81);
    if (!flgC) {
        goto L_0041E0;
    }
    myMapper->writeCPU(0x0060, 0x00);
L_0041E0:
    myMapper->writeCPU(0x004C, 0x78);
    myMapper->writeCPU(0x0100, 0x02);
    a = 0x00;
    myMapper->writeCPU(0x0160, a);
    myMapper->writeCPU(0x0140, a);
    myMapper->writeCPU(0x001B, 0xA0);
    a = 0xF7;
    pushAddress(0x0041F9);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x0041F9)) return;
    SUB_0042C4();
    return;
}

void game::SUB_0041FD() {
    x = y;
    SUB_002EF8();
    return;
}

void game::SUB_00420A() {
    myMapper->writeCPU(0x00A8, 0x09);
    a = myMapper->readCPU(0x0360);
    myMapper->writeCPU(0x00A0, a);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x00A2, a);
    a = myMapper->readCPU(0x0320);
    myMapper->writeCPU(0x00A4, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x00A5, a);
    opADC(0x04);
    myMapper->writeCPU(0x00A6, a);
    do {
        y = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0136 + y) != 0) {
            x = myMapper->readCPU(0x0176 + y);
            a = myMapper->readCPU((0x00A0 + x) & 0x00ff);
            flgC = true;
            opSBC(myMapper->readCPU(0x0376 + y));
            opCMP(a, myMapper->readCPU(0xC202 + x));
            if (!flgC) {
                a = myMapper->readCPU((0x00A4 + x) & 0x00ff);
                opSBC(myMapper->readCPU(0x0336 + y));
                if (a < myMapper->readCPU(0xC206 + x)) {
                    if (myMapper->readCPU(0x0046) != 0) {
                        goto L_00424E;
                    }
                    SUB_0041D6();
                    return;
                L_00424E:
                    opDEC(0x0046, 1);
                    a = 0x0A;
                    flgC = false;
                    opADC(myMapper->readCPU(0x00A8));
                    x = a;
                    pushAddress(0x004258);
                    SUB_002EF8();
                    if (handleReturnAddress(poppedEntry.value, 0x004258)) return;
                }
            }
        }
        opDEC(0x00A8, 1);
    } while (!flgN);
    if (myMapper->readCPU(0x0019) != 0x04) {
        SUB_0042A5();
        return;
    }
    myMapper->writeCPU(0x00A9, 0x90);
    do {
        x = myMapper->readCPU(0x00A9);
        if (myMapper->readCPU(0x0600 + x) == 0) {
            goto L_00429B;
        }
        myMapper->writeCPU(0x00AB, 0x05);
        a = x;
        flgC = false;
        opADC(0x05);
        myMapper->writeCPU(0x00AA, a);
        do {
            x = myMapper->readCPU(0x00AA);
            a = myMapper->readCPU(0x00A0);
            opSBC(myMapper->readCPU(0x0618 + x));
            opCMP(a, 0x0A);
            if (!flgC) {
                a = myMapper->readCPU(0x00A4);
                opSBC(myMapper->readCPU(0x0620 + x));
                opCMP(a, 0x0A);
                if (!flgC) {
                    if (myMapper->readCPU(0x0046) != 0) {
                        goto L_004293;
                    }
                    SUB_0041D6();
                    return;
                L_004293:
                    opDEC(0x0046, 1);
                }
            }
            opDEC(0x00AA, 1);
            opDEC(0x00AB, 1);
        } while (!flgN);
    L_00429B:
        a = myMapper->readCPU(0x00A9);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x00A9, a);
    } while (!flgN);
    popAddress();
}

void game::SUB_0042A5() {
    a = myMapper->readCPU(0x0019);
    if (a == 0x02) {
        goto L_0042B0;
    }
    opCMP(a, 0x04);
    if (!flgZ) {
        goto L_0042B5;
    }
    popAddress();
    return;
L_0042B0:
    a = myMapper->readCPU(0x0002);
    opLSR_A(1);
    if (!flgC) {
        SUB_0042FF();
        return;
    }
L_0042B5:
    opCMP(myMapper->readCPU(0x0100), 0x02);
    if (flgC) {
        SUB_0042C4();
        return;
    }
    pushAddress(0x0042BE);
    SUB_0043A3();
    if (handleReturnAddress(poppedEntry.value, 0x0042BE)) return;
    if (flgZ) {
        SUB_0042C4();
        return;
    }
    SUB_0041D6();
    return;
}

void game::SUB_0042C4() {
    myMapper->writeCPU(0x00A8, 0x05);
    do {
        x = myMapper->readCPU(0x00A8);
        pushAddress(0x0042CC);
        SUB_0043AF();
        if (handleReturnAddress(poppedEntry.value, 0x0042CC)) return;
        if (!flgZ) {
            y = myMapper->readCPU(0x00A3);
            do {
                opDEY(1);
                if (flgN) {
                    goto L_0042D8;
                }
                opLSR_A(2);
            } while (!flgZ);
        L_0042D8:
            opCMP(a, 0x02);
            if (!flgZ) {
                goto L_0042E8;
            }
            pushAddress(0x0042DE);
            SUB_00432F();
            if (handleReturnAddress(poppedEntry.value, 0x0042DE)) return;
            x = myMapper->readCPU(0x00A8);
            opCMP(myMapper->readCPU(0x0163 + x), 0x01);
            if (flgZ) {
                goto L_0042ED;
            }
        L_0042E8:
            a = 0x00;
            pushAddress(0x0042EC);
            SUB_0040BD();
            if (handleReturnAddress(poppedEntry.value, 0x0042EC)) return;
        }
    L_0042ED:
        opDEC(0x00A8, 1);
    } while (!flgN);
    opCMP(myMapper->readCPU(0x0100), 0x02);
    if (flgC) {
        SUB_0042FF();
        return;
    }
    opCMP(myMapper->readCPU(0x0019), 0x02);
    if (!flgZ) {
        SUB_0042FF();
        return;
    }
    popAddress();
}

void game::SUB_0042FF() {
    myMapper->writeCPU(0x00A8, 0x09);
    do {
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x0136 + x) != 0) {
            a = myMapper->readCPU(0x0336 + x);
            if (myMapper->readCPU(0x0316 + x) == 0) {
                flgC = false;
                opADC(0x08);
            }
            myMapper->writeCPU(0x00A5, a);
            myMapper->writeCPU(0x00A4, myMapper->readCPU(0x0376 + x));
            pushAddress(0x00431E);
            SUB_0043D3();
            if (handleReturnAddress(poppedEntry.value, 0x00431E)) return;
            if (flgZ) {
                goto L_00432A;
            }
            a = 0x0A;
            flgC = false;
            opADC(myMapper->readCPU(0x00A8));
            x = a;
            pushAddress(0x004329);
            SUB_002EF8();
            if (handleReturnAddress(poppedEntry.value, 0x004329)) return;
        }
    L_00432A:
        opDEC(0x00A8, 1);
    } while (!flgN);
    popAddress();
}

void game::SUB_00432F() {
    x = myMapper->readCPU(0x0019);
    if (a == 0x04) {
        a = 0x00;
        popAddress();
        return;
    }
    a = 0x04;
    opCMP(x, 0x05);
    if (!flgZ) {
        a = 0x03;
    }
    pushAddress(0x004342);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x004342)) return;
    myMapper->writeCPU(0x00A6, 0x00);
    a = 0x20;
    y = myMapper->readCPU(0x00A1);
    if (y == 0x05) {
        goto L_004351;
    }
    a = 0x24;
L_004351:
    myMapper->writeCPU(0x00A7, a);
    a = myMapper->readCPU(0x00A0);
    opAND(0x07);
    opLSR_A(1);
    opROR_M(0x00A6, 1);
    flgC = false;
    opADC(myMapper->readCPU(0x00A7));
    myMapper->writeCPU(0x00A7, a);
    a = myMapper->readCPU(0x00A0);
    opLSR_A(3);
    opORA(myMapper->readCPU(0x00A6));
    x = myMapper->readCPU(0x00A3);
    opORA(myMapper->readCPU(0xC39F + x));
    myMapper->writeCPU(0x00A6, a);
    a = 0x01;
    x = myMapper->readCPU(0x000E);
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x00A7));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x00A6));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0x00);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x000E, x);
    x = myMapper->readCPU(0x00A3);
    a = myMapper->readCPU(0x00A2);
    opAND(myMapper->readCPU(0xC39B + x));
    x = 0x00;
    myMapper->writeCPU(myMapper->readCPU((0x00A0 + x) & 0x00ff) + (myMapper->readCPU((0x00A0 + x + 1) & 0x00ff) << 8), a);
    popAddress();
}

void game::SUB_0043A3() {
    myMapper->writeCPU(0x00A5, myMapper->readCPU(0x0320));
    a = myMapper->readCPU(0x0360);
    setLoadFlag(a);
    myMapper->writeCPU(0x00A4, a);
    if (!flgZ) {
        SUB_0043D3();
        return;
    }
    SUB_0043AF();
    return;
}

void game::SUB_0043AF() {
    a = myMapper->readCPU(0x0123 + x);
    setLoadFlag(a);
    if (flgZ) {
        SUB_00440E();
        return;
    }
    a = myMapper->readCPU(0x0323 + x);
    opCMP(x, 0x06);
    if (flgC) {
        opADC(0x03);
    }
    myMapper->writeCPU(0x00A5, a);
    opCMP(myMapper->readCPU(0x0163 + x), 0x01);
    if (!flgZ) {
        goto L_0043CE;
    }
    a = myMapper->readCPU(0x0363 + x);
    opADC(0x0A);
    goto L_0043D1;
L_0043CE:
    a = myMapper->readCPU(0x0363 + x);
L_0043D1:
    myMapper->writeCPU(0x00A4, a);
    SUB_0043D3();
    return;
}

void game::SUB_0043D3() {
    a = myMapper->readCPU(0x00A4);
    flgC = false;
    opADC(0x08);
    opADC(myMapper->readCPU(0x003E));
    opAND(0xF8);
    myMapper->writeCPU(0x00A0, a);
    a = myMapper->readCPU(0x003F);
    opADC(0x00);
    opAND(0x01);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x00A1, a);
    a = myMapper->readCPU(0x00A5);
    flgC = false;
    opADC(0x14);
    opLSR_A(3);
    myMapper->writeCPU(0x00A3, a);
    opLSR_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x00A0, a);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00A0) + (myMapper->readCPU((0x00A0 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x00A2, a);
    if (flgZ) {
        SUB_00440E();
        return;
    }
    a = myMapper->readCPU(0x00A3);
    opAND(0x03);
    myMapper->writeCPU(0x00A3, a);
    y = a;
    a = myMapper->readCPU(0x00A2);
    opAND(myMapper->readCPU(0xC40F + y));
    SUB_00440E();
    return;
}

void game::SUB_00440E() {
    popAddress();
}

void game::SUB_004413() {
    a = myMapper->readCPU(0x0002);
    opAND(0x03);
    if (flgZ) {
        goto L_00441A;
    }
    popAddress();
    return;
L_00441A:
    myMapper->writeCPU(0x00A8, 0x09);
    do {
        x = myMapper->readCPU(0x00A8);
        if (myMapper->readCPU(0x030C + x) == 0) {
            SUB_00442A();
            return;
        }
        opDEC(0x00A8, 1);
    } while (!flgN);
    SUB_004429();
    return;
}

void game::SUB_004429() {
    popAddress();
}

void game::SUB_00442A() {
    pushAddress(0x00442C);
    SUB_002527();
    if (handleReturnAddress(poppedEntry.value, 0x00442C)) return;
    if (myMapper->readCPU(0x003A) == 0) {
        goto L_004434;
    }
    SUB_004686();
    return;
L_004434:
    a = myMapper->readCPU(0x0019);
    pushAddress(0x004438);
    SUB_0003E4();
    if (handleReturnAddress(poppedEntry.value, 0x004438)) return;
    SUB_00444F();
    return;
}

void game::SUB_00444F() {
    myMapper->writeCPU(0x009A, myMapper->readCPU(0xC447 + x));
    myMapper->writeCPU(0x009B, myMapper->readCPU(0xC448 + x));
    a = myMapper->readCPU(0x0069);
    if (a == 0xFF) {
        a = 0x7F;
        myMapper->writeCPU(0x0069, a);
    }
    opINC(0x0069, 1);
    opAND(0x3F);
    opLSR_A(1);
    y = a;
    myMapper->writeCPU(0x00A9, myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0069);
    opAND(0x01);
    myMapper->writeCPU(0x00AA, a);
    if (!flgZ) {
        goto L_00447E;
    }
    a = myMapper->readCPU(0x00A9);
    opLSR_A(4);
    goto L_004480;
L_00447E:
    a = myMapper->readCPU(0x00A9);
L_004480:
    opAND(0x0F);
    opASL_A(1);
    myMapper->writeCPU(0x00A9, a);
    popAddress();
}

void game::SUB_004486() {
    y = myMapper->readCPU(0x0069);
    setLoadFlag(y);
    if (flgZ) {
        a = 0x0F;
        pushAddress(0x00448E);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x00448E)) return;
    }
    x = 0x00;
    pushAddress(0x004493);
    SUB_00444F();
    if (handleReturnAddress(poppedEntry.value, 0x004493)) return;
    a = myMapper->readCPU(0x00A9);
    opLSR_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x00A9));
    y = a;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x042C + x, myMapper->readCPU(0xC4F6 + y));
    myMapper->writeCPU(0x03BC + x, myMapper->readCPU(0xC4F7 + y));
    a = myMapper->readCPU(0x0069);
    if (a < 0x1E) {
        opDEC(0x03BC + x, 2);
        if (a >= 0x0A) {
            goto L_0044BF;
        }
        opDEC(0x03BC + x, 2);
    }
L_0044BF:
    a = myMapper->readCPU(0x0002);
    opASL_A(3);
    opAND(0x07);
    flgC = false;
    opADC(myMapper->readCPU(0xC4F8 + y));
    myMapper->writeCPU(0x048C + x, a);
    myMapper->writeCPU(0x04AC + x, 0x01);
    y = myMapper->readCPU(0x00AA);
    myMapper->writeCPU(0x036C + x, myMapper->readCPU(0xC4F4 + y));
    myMapper->writeCPU(0x030C + x, 0x0A);
    myMapper->writeCPU(0x032C + x, 0x90);
    SUB_0044E4();
    return;
}

void game::SUB_0044E4() {
    a = myMapper->readCPU(0x0002);
    opAND(0x3F);
    myMapper->writeCPU(0x044C + x, a);
    myMapper->writeCPU(0x03EC + x, a);
    myMapper->writeCPU(0x012C + x, 0x58);
    popAddress();
}

void game::SUB_004526() {
    //NOP
    SUB_004546();
    return;
}

void game::SUB_004546() {
    a = myMapper->readCPU(0x0002);
    opAND(0x07);
    if (flgZ) {
        goto L_00454D;
    }
    popAddress();
    return;
L_00454D:
    x = 0x02;
    pushAddress(0x004551);
    SUB_00444F();
    if (handleReturnAddress(poppedEntry.value, 0x004551)) return;
    y = myMapper->readCPU(0x00A9);
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x036C + x, myMapper->readCPU(0xC56D + y));
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0xC56E + y));
    myMapper->writeCPU(0x030C + x, 0x0B);
    myMapper->writeCPU(0x012C + x, 0x67);
    popAddress();
}

void game::SUB_00458D() {
    opORA(myMapper->readCPU(myMapper->readCPU((0x0023 + x) & 0x00ff) + (myMapper->readCPU((0x0023 + x + 1) & 0x00ff) << 8)));
    opEOR(myMapper->readCPU(0x0067));
    //NOP
    SUB_0045AD();
    return;
}

void game::SUB_0045AD() {
    if (myMapper->readCPU(0x0069) != 0) {
        goto L_0045B6;
    }
    a = 0x0F;
    pushAddress(0x0045B5);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x0045B5)) return;
L_0045B6:
    x = 0x04;
    pushAddress(0x0045BA);
    SUB_00444F();
    if (handleReturnAddress(poppedEntry.value, 0x0045BA)) return;
    a = myMapper->readCPU(0x00A9);
    opLSR_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x00A9));
    y = a;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x042C + x, myMapper->readCPU(0xC603 + y));
    myMapper->writeCPU(0x03BC + x, myMapper->readCPU(0xC604 + y));
    if (myMapper->readCPU(0x0069) >= 0x1E) {
        goto L_0045DC;
    }
    opDEC(0x03BC + x, 2);
L_0045DC:
    a = myMapper->readCPU(0x0002);
    opAND(0x0F);
    flgC = false;
    opADC(myMapper->readCPU(0xC605 + y));
    myMapper->writeCPU(0x048C + x, a);
    myMapper->writeCPU(0x04AC + x, 0x01);
    y = myMapper->readCPU(0x00AA);
    myMapper->writeCPU(0x036C + x, myMapper->readCPU(0xC601 + y));
    myMapper->writeCPU(0x030C + x, 0x15);
    myMapper->writeCPU(0x032C + x, 0x2C);
    SUB_0044E4();
    return;
}

void game::SUB_004633() {
    //NOP
    SUB_004653();
    return;
}

void game::SUB_004653() {
    opINC(0x0068, 1);
    opCMP(myMapper->readCPU(0x0068), 0x28);
    if (!flgC) {
        goto L_004679;
    }
    myMapper->writeCPU(0x0068, 0x00);
    a = myMapper->readCPU(0x0069);
    opAND(0x06);
    x = a;
    myMapper->writeCPU(0x0065, myMapper->readCPU(0xC67A + x));
    myMapper->writeCPU(0x0066, 0x14);
    myMapper->writeCPU(0x0067, myMapper->readCPU(0xC67B + x));
    opINX(2);
    myMapper->writeCPU(0x0069, x);
    pushAddress(0x004678);
    SUB_0024A6();
    if (handleReturnAddress(poppedEntry.value, 0x004678)) return;
L_004679:
    popAddress();
}

void game::SUB_004686() {
    opINC(0x0068, 1);
    a = myMapper->readCPU(0x0068);
    y = myMapper->readCPU(0x003A);
    opCMP(a, myMapper->readCPU(0xC684 + y));
    if (!flgC) {
        popAddress();
        return;
    }
    opCMP(myMapper->readCPU(0x003F), 0x0E);
    if (!flgC) {
        goto L_004699;
    }
    popAddress();
    return;
L_004699:
    myMapper->writeCPU(0x0068, 0x00);
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x0069);
    opINC(0x0069, 1);
    opAND(0x0F);
    y = a;
    myMapper->writeCPU(0x032C + x, myMapper->readCPU(0xC6CE + y));
    myMapper->writeCPU(0x0460 + x, 0x01);
    y = myMapper->readCPU(0x003A);
    myMapper->writeCPU(0x012C + x, myMapper->readCPU(0xC6CA + y));
    myMapper->writeCPU(0x030C + x, myMapper->readCPU(0xC6CC + y));
    myMapper->writeCPU(0x010C + x, 0x80);
    myMapper->writeCPU(0x036C + x, 0xF0);
    popAddress();
}

void game::SUB_0046DE() {
    if (myMapper->readCPU(0x0069) != 0) {
        goto L_0046E2;
    }
L_0046E2:
    a = 0x04;
    x = 0x06;
    pushAddress(0x0046E8);
    SUB_00444F();
    if (handleReturnAddress(poppedEntry.value, 0x0046E8)) return;
    x = 0x09;
    do {
        if (myMapper->readCPU(0x0136 + x) == 0) {
            goto L_0046F4;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_0046F4:
    myMapper->writeCPU(0x00A8, x);
    a = myMapper->readCPU(0x00A9);
    opASL_A(4);
    myMapper->writeCPU(0x00A9, a);
    a = 0x00;
    opROL_A(1);
    opASL_M(0x00A9, 1);
    opROL_A(1);
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x0002);
    flgC = false;
    opADC(myMapper->readCPU(0x00A9));
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x03F6 + x, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x03C6 + x, a);
    myMapper->writeCPU(0x0436 + x, 0x04);
    a = 0x00;
    myMapper->writeCPU(0x0456 + x, a);
    myMapper->writeCPU(0x0116 + x, a);
    myMapper->writeCPU(0x0356 + x, a);
    myMapper->writeCPU(0x0396 + x, a);
    y = 0x00;
    a = myMapper->readCPU(0x0002);
    opAND(0x04);
    if (!flgZ) {
        goto L_004733;
    }
    opINY(1);
L_004733:
    myMapper->writeCPU(0x0476 + x, y);
    a = 0x01;
    myMapper->writeCPU(0x0316 + x, a);
    myMapper->writeCPU(0x0176 + x, a);
    myMapper->writeCPU(0x0336 + x, myMapper->readCPU(0xC750 + y));
    myMapper->writeCPU(0x0376 + x, 0x98);
    myMapper->writeCPU(0x0136 + x, 0x8D);
    popAddress();
}

void game::SUB_004752() {
    //NOP
    SUB_004772();
    return;
}

void game::SUB_004772() {
    opCMP(myMapper->readCPU(0x0019), 0x04);
    if (!flgZ) {
        goto L_00477B;
    }
    SUB_004B8A();
    return;
L_00477B:
    popAddress();
}

void game::SUB_00477C() {
    opINC(0x005F, 1);
    opCMP(myMapper->readCPU(0x005F), 0x0A);
    if (!flgC) {
        goto L_004788;
    }
    myMapper->writeCPU(0x0039, 0x01);
L_004788:
    opINC(0x005D, 1);
    pushAddress(0x00478C);
    SUB_00044F();
    if (handleReturnAddress(poppedEntry.value, 0x00478C)) return;
    pushAddress(0x00478F);
    SUB_004822();
    if (handleReturnAddress(poppedEntry.value, 0x00478F)) return;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x03EC + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x03BC + x));
    a = 0x0C;
    pushAddress(0x0047A0);
    SUB_004B26();
    if (handleReturnAddress(poppedEntry.value, 0x0047A0)) return;
    a = myMapper->readCPU(0x00A9);
    opASL_A(1);
    myMapper->writeCPU(0x00A9, a);
    x = myMapper->readCPU(0x00A9);
    myMapper->writeCPU(0x009A, myMapper->readCPU(0xC893 + x));
    myMapper->writeCPU(0x009B, myMapper->readCPU(0xC894 + x));
    a = 0x01;
    y = 0x00;
    x = myMapper->readCPU(0x000E);
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    do {
        a = myMapper->readCPU(0x0098);
        flgC = true;
        opSBC(myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0701 + x, a);
        a = myMapper->readCPU(0x0099);
        opSBC(0x00);
        myMapper->writeCPU(0x0700 + x, a);
        opINY(1);
        opINX(2);
        while (true) {
            a = myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y);
            opINY(1);
            if (a == 0xFF) {
                goto L_0047E0;
            }
            if (a == 0xFE) {
                goto L_0047EE;
            }
            myMapper->writeCPU(0x0700 + x, a);
            opINX(1);
        }
    L_0047E0:
        myMapper->writeCPU(0x0700 + x, 0xFF);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, 0x01);
        opINX(1);
    } while (!flgZ);
L_0047EE:
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0x01);
    opINX(1);
    a = myMapper->readCPU(0x0098);
    flgC = false;
    opADC(myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0701 + x, a);
    a = myMapper->readCPU(0x0099);
    opADC(0x00);
    myMapper->writeCPU(0x0700 + x, a);
    opINY(1);
    opINX(2);
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_004819;
        }
        opINY(1);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
    } while (!flgZ);
L_004819:
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x000E, x);
    popAddress();
}

void game::SUB_004822() {
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x03BC + x);
    myMapper->writeCPU(0x0098, a);
    y = 0x05;
    opAND(0x04);
    if (!flgZ) {
        y = 0x06;
    }
    myMapper->writeCPU(0x009B, y);
    a = myMapper->readCPU(0x03EC + x);
    myMapper->writeCPU(0x0099, a);
    opASL_A(1);
    opROL_M(0x0098, 1);
    opASL_A(2);
    opAND(0xF8);
    myMapper->writeCPU(0x009A, a);
    a = myMapper->readCPU(0x0098);
    opAND(0x07);
    opORA(myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x009A, a);
    y = 0x00;
    a = myMapper->readCPU(0x00A9);
    setLoadFlag(a);
    if (flgZ) {
        goto L_004854;
    }
    opCMP(a, 0x02);
    if (flgZ) {
        goto L_00486F;
    }
    popAddress();
    return;
L_004854:
    x = 0x00;
    while (true) {
        a = 0x0F;
        do {
            y = myMapper->readCPU(0xC87B + x);
            setLoadFlag(y);
            if (flgN) {
                goto L_004862;
            }
            myMapper->writeCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y, a);
            opINX(1);
        } while (!flgZ);
        do {
        L_004862:
            opINX(1);
            a = 0x00;
            y = myMapper->readCPU(0xC87B + x);
            setLoadFlag(y);
            if (flgN) {
                goto L_00486E;
            }
            myMapper->writeCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y, a);
        } while (!flgN);
    L_00486E:
        popAddress();
        return;
    L_00486F:
        x = 0x0C;
        a = myMapper->readCPU(0x009A);
        flgC = true;
        opSBC(0x29);
        myMapper->writeCPU(0x009A, a);
    }
    SUB_004906();
    return;
}

void game::SUB_004906() {
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x010C + x);
    opAND(0x0F);
    myMapper->writeCPU(0x00A9, a);
    opCMP(myMapper->readCPU(0x046C + x), 0x03);
    if (flgC) {
        SUB_00477C();
        return;
    }
    pushAddress(0x00491B);
    SUB_002EDD();
    if (handleReturnAddress(poppedEntry.value, 0x00491B)) return;
    if (myMapper->readCPU(0x005D) == 0) {
        opCMP(myMapper->readCPU(0x000E), 0x04);
        if (!flgC) {
            if (myMapper->readCPU(0x04AC + x) != 0) {
                goto L_004932;
            }
            a = myMapper->readCPU(0x048C + x);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00495A;
            }
            if (!flgZ) {
                goto L_00493D;
            }
        L_004932:
            opDEC(0x04AC + x, 1);
        }
    }
    popAddress();
    return;
L_00493D:
    a = 0x00;
    myMapper->writeCPU(0x048C + x, a);
    myMapper->writeCPU(0x046C + x, a);
    myMapper->writeCPU(0x04EC + x, a);
    y = myMapper->readCPU(0x0017);
    myMapper->writeCPU(0x04AC + x, myMapper->readCPU(0xC936 + y));
    a = myMapper->readCPU(0x00A9);
    opASL_A(2);
    flgC = false;
    opADC(0x10);
    goto L_0049BA;
L_00495A:
    a = myMapper->readCPU(0x0360);
    y = myMapper->readCPU(0x00A9);
    setLoadFlag(y);
    if (!flgZ) {
        opCMP(y, 0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x0320);
            opDEY(1);
            if (!flgZ) {
                opADC(0x0A);
                opCMP(a, myMapper->readCPU(0x032C + x));
                if (!flgC) {
                    goto L_00499F;
                }
                popAddress();
                return;
            }
            opSBC(0x0A);
            opCMP(a, myMapper->readCPU(0x032C + x));
            if (flgC) {
                goto L_00499F;
            }
            popAddress();
            return;
        }
        opSBC(0x0A);
        opCMP(a, myMapper->readCPU(0x036C + x));
        if (!flgC) {
            goto L_00499E;
        }
        a = myMapper->readCPU(0x0320);
        opSBC(0x0A);
        opCMP(a, myMapper->readCPU(0x032C + x));
        if (!flgC) {
            goto L_00499F;
        }
        popAddress();
        return;
    }
    opADC(0x0A);
    opCMP(a, myMapper->readCPU(0x036C + x));
    if (!flgC) {
        a = myMapper->readCPU(0x0320);
        opSBC(0x0A);
        opCMP(a, myMapper->readCPU(0x032C + x));
        if (!flgC) {
            goto L_00499F;
        }
    }
L_00499E:
    popAddress();
    return;
L_00499F:
    opINC(0x005D, 1);
    myMapper->writeCPU(0x040C + x, 0x00);
    y = myMapper->readCPU(0x0017);
    a = 0x14;
    myMapper->writeCPU(0x04EC + x, a);
    myMapper->writeCPU(0x048C + x, a);
    myMapper->writeCPU(0x04AC + x, myMapper->readCPU(0xC936 + y));
    a = myMapper->readCPU(0x00A9);
    opASL_A(2);
L_0049BA:
    myMapper->writeCPU(0x00AA, a);
    a = 0x01;
    y = myMapper->readCPU(0x000E);
    myMapper->writeCPU(0x0700 + y, a);
    opINY(1);
    myMapper->writeCPU(0x0700 + y, myMapper->readCPU(0x03BC + x));
    opINY(1);
    opCMP(myMapper->readCPU(0x00A9), 0x02);
    if (flgZ) {
        a = myMapper->readCPU(0x03EC + x);
        flgC = true;
        opSBC(0x01);
    }
    else {
        a = myMapper->readCPU(0x03EC + x);
    }
    myMapper->writeCPU(0x0700 + y, a);
    opINY(1);
    x = myMapper->readCPU(0x00AA);
    myMapper->writeCPU(0x0700 + y, myMapper->readCPU(0xCA29 + x));
    opINY(1);
    myMapper->writeCPU(0x0700 + y, myMapper->readCPU(0xCA2A + x));
    opINY(1);
    myMapper->writeCPU(0x0700 + y, 0xFF);
    opINY(1);
    if (myMapper->readCPU(0xCA2B + x) != 0) {
        goto L_004A26;
    }
    myMapper->writeCPU(0x0700 + y, 0x01);
    opINY(1);
    x = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x03EC + x);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0701 + y, a);
    a = myMapper->readCPU(0x03BC + x);
    opADC(0x00);
    myMapper->writeCPU(0x0700 + y, a);
    opINY(2);
    x = myMapper->readCPU(0x00AA);
    myMapper->writeCPU(0x0700 + y, myMapper->readCPU(0xCA2C + x));
    opINY(1);
    myMapper->writeCPU(0x0700 + y, 0xFF);
    opINY(1);
L_004A26:
    myMapper->writeCPU(0x000E, y);
    popAddress();
}

void game::SUB_004A5E() {
    y = myMapper->readCPU(0x0017);
    myMapper->writeCPU(0x0098, myMapper->readCPU(0xCA49 + y));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0xCA50 + y));
    a = 0x94;
    x = myMapper->readCPU(0x00A8);
    myMapper->writeCPU(0x030C + x, a);
    opINC(0x042C + x, 1);
    a = myMapper->readCPU(0x042C + x);
    y = 0x81;
    opAND(0x08);
    if (!flgZ) {
        opINY(1);
    }
    if (myMapper->readCPU(0x046C + x) >= myMapper->readCPU(0x0098)) {
        a = 0x00;
        if (a != myMapper->readCPU(0x0460 + x)) {
            myMapper->writeCPU(0x0460 + x, a);
            a = myMapper->readCPU(0x036C + x);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x036C + x, a);
            a = myMapper->readCPU(0x032C + x);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x032C + x, a);
        }
        opINY(2);
    }
    myMapper->writeCPU(0x012C + x, y);
    myMapper->writeCPU(0x048C + x, 0x01);
    opCMP(myMapper->readCPU(0x046C + x), myMapper->readCPU(0x0099));
    if (!flgC) {
        if (myMapper->readCPU(0x016C + x) != 0) {
            goto L_004AC1;
        }
        pushAddress(0x004ABA);
        SUB_002EE1();
        if (handleReturnAddress(poppedEntry.value, 0x004ABA)) return;
        if (myMapper->readCPU(0x012C + x) == 0) {
            popAddress();
            return;
        }
    L_004AC1:
        if (myMapper->readCPU(0x04AC + x) == 0) {
            a = myMapper->readCPU(0x0002);
            opAND(0x3F);
            myMapper->writeCPU(0x04AC + x, a);
            y = 0x00;
            opCMP(myMapper->readCPU(0x032C + x), myMapper->readCPU(0x0320));
            if (!flgC) {
                opINY(1);
            }
            myMapper->writeCPU(0x04CC + x, y);
        }
        opDEC(0x04AC + x, 1);
        y = myMapper->readCPU(0x0017);
        if (myMapper->readCPU(0x04CC + x) == 0) {
            a = myMapper->readCPU(0x034C + x);
            opSBC(myMapper->readCPU(0xCA57 + y));
            myMapper->writeCPU(0x034C + x, a);
            a = myMapper->readCPU(0x032C + x);
            opSBC(0x00);
            if (a < 0x20) {
                a = 0x20;
            }
            myMapper->writeCPU(0x032C + x, a);
        }
        else {
            a = myMapper->readCPU(0x034C + x);
            opADC(myMapper->readCPU(0xCA57 + y));
            myMapper->writeCPU(0x034C + x, a);
            a = myMapper->readCPU(0x032C + x);
            opADC(0x00);
            if (a < 0xA8) {
                goto L_004B14;
            }
            a = 0xA8;
        L_004B14:
            myMapper->writeCPU(0x032C + x, a);
        }
        pushAddress(0x004B19);
        SUB_002EE1();
        if (handleReturnAddress(poppedEntry.value, 0x004B19)) return;
        popAddress();
        return;
    }
    pushAddress(0x004B1D);
    SUB_00044B();
    if (handleReturnAddress(poppedEntry.value, 0x004B1D)) return;
    a = 0x0A;
    pushAddress(0x004B22);
    SUB_004B26();
    if (handleReturnAddress(poppedEntry.value, 0x004B22)) return;
    SUB_004B4E();
    return;
}

void game::SUB_004B26() {
    x = myMapper->readCPU(0x00A8);
    SUB_004B28();
    return;
}

void game::SUB_004B28() {
    pushAddress(0x004B2A);
    SUB_006C1E();
    if (handleReturnAddress(poppedEntry.value, 0x004B2A)) return;
    SUB_004B2B();
    return;
}

void game::SUB_004B2B() {
    a = 0x00;
    myMapper->writeCPU(0x042C + x, a);
    myMapper->writeCPU(0x014C + x, a);
    myMapper->writeCPU(0x018C + x, a);
    myMapper->writeCPU(0x046C + x, a);
    myMapper->writeCPU(0x04AC + x, a);
    myMapper->writeCPU(0x010C + x, a);
    myMapper->writeCPU(0x03AC + x, a);
    myMapper->writeCPU(0x040C + x, a);
    a = 0x02;
    myMapper->writeCPU(0x030C + x, a);
    myMapper->writeCPU(0x016C + x, a);
    popAddress();
}

void game::SUB_004B4E() {
    myMapper->writeCPU(0x00A9, 0x90);
    do {
        x = myMapper->readCPU(0x00A9);
        y = myMapper->readCPU(0x0600 + x);
        setLoadFlag(y);
        if (!flgZ) {
            opCMP(y, myMapper->readCPU(0x00A8));
            if (!flgZ) {
                goto L_004B80;
            }
            myMapper->writeCPU(0x0600 + x, 0x00);
            x = 0x07;
            do {
                if (myMapper->readCPU(0x030C + x) != 0) {
                    goto L_004B7D;
                }
                pushAddress(0x004B6B);
                SUB_004B2B();
                if (handleReturnAddress(poppedEntry.value, 0x004B6B)) return;
                y = myMapper->readCPU(0x00A9);
                myMapper->writeCPU(0x036C + x, myMapper->readCPU(0x061A + y));
                myMapper->writeCPU(0x032C + x, myMapper->readCPU(0x0622 + y));
                goto L_004B80;
            L_004B7D:
                opDEX(1);
            } while (!flgN);
        }
    L_004B80:
        a = myMapper->readCPU(0x00A9);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x00A9, a);
    } while (!flgN);
    popAddress();
}

void game::SUB_004B8A() {
    opCMP(myMapper->readCPU(0x005C), 0x02);
    if (!flgC) {
        SUB_004B91();
        return;
    }
    popAddress();
}

void game::SUB_004B91() {
    myMapper->writeCPU(0x00AE, 0x00);
    myMapper->writeCPU(0x00A8, 0x90);
    do {
        x = myMapper->readCPU(0x00A8);
        y = myMapper->readCPU(0x0600 + x);
        setLoadFlag(y);
        if (!flgZ) {
            pushAddress(0x004BA2);
            SUB_004C33();
            if (handleReturnAddress(poppedEntry.value, 0x004BA2)) return;
            x = myMapper->readCPU(0x00A8);
            opINC(0x0604 + x, 1);
            a = myMapper->readCPU(0x0604 + x);
            y = myMapper->readCPU(0x0017);
            if (a >= myMapper->readCPU(0xCBCA + y)) {
                if (myMapper->readCPU(0x00AE) != 0) {
                    goto L_004BC0;
                }
                opINC(0x00AE, 1);
                myMapper->writeCPU(0x0604 + x, 0x00);
                pushAddress(0x004BBF);
                SUB_004BD1();
                if (handleReturnAddress(poppedEntry.value, 0x004BBF)) return;
            }
        }
    L_004BC0:
        a = myMapper->readCPU(0x00A8);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x00A8, a);
    } while (!flgN);
    popAddress();
}

void game::SUB_004BD1() {
    x = 0x09;
    do {
        if (myMapper->readCPU(0x0136 + x) == 0) {
            goto L_004BDC;
        }
        opDEX(1);
    } while (!flgN);
    do {
        do {
            do {
                popAddress();
                return;
            L_004BDC:
                y = myMapper->readCPU(0x00A8);
                a = myMapper->readCPU(0x061D + y);
            } while (a < 0x10);
        } while (a >= 0xF0);
    } while (myMapper->readCPU(0x0625 + y) >= 0xD0);
    myMapper->writeCPU(0x00A9, x);
    myMapper->writeCPU(0x0136 + x, 0x86);
    a = 0x00;
    myMapper->writeCPU(0x0316 + x, a);
    myMapper->writeCPU(0x0116 + x, a);
    myMapper->writeCPU(0x0176 + x, a);
    y = myMapper->readCPU(0x00A8);
    a = myMapper->readCPU(0x061D + y);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0376 + x, a);
    a = myMapper->readCPU(0x0625 + y);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0336 + x, a);
    SUB_003CB1();
    return;
}

void game::SUB_004C19() {
    myMapper->writeCPU(0x0600 + x, 0x00);
    popAddress();
}

void game::SUB_004C33() {
    if (myMapper->readCPU(0x030C + y) == 0) {
        SUB_004C19();
        return;
    }
    a = myMapper->readCPU(0x0603 + x);
    opDEC(0x0603 + x, 1);
    a = myMapper->readCPU(0x0603 + x);
    opAND(0x01);
    if (flgZ) {
        goto L_004C46;
    }
    popAddress();
    return;
L_004C46:
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x036C + y));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x032C + y));
    a = myMapper->readCPU(0x0460 + y);
    opASL_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x0601 + x));
    myMapper->writeCPU(0x009A, a);
    a = myMapper->readCPU(0x0601 + x);
    y = a;
    opAND(0x01);
    myMapper->writeCPU(0x009F, a);
    myMapper->writeCPU(0x009B, myMapper->readCPU(0xCC1F + y));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0xCC21 + y));
    a = x;
    opASL_A(1);
    opADC(myMapper->readCPU(0x0002));
    opAND(0x7F);
    opADC(myMapper->readCPU(0x0360));
    opAND(0xF0);
    myMapper->writeCPU(0x009E, a);
    y = myMapper->readCPU(0x009A);
    a = myMapper->readCPU(0xCC23 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0618 + x, a);
    a = myMapper->readCPU(0xCC2B + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0620 + x, a);
    myMapper->writeCPU(0x00A9, x);
    myMapper->writeCPU(0x00AA, 0x04);
    myMapper->writeCPU(0x009D, myMapper->readCPU(0x0320));
    while (true) {
        x = myMapper->readCPU(0x00A9);
        if (myMapper->readCPU(0x009F) == 0) {
            goto L_004CB0;
        }
        a = myMapper->readCPU(0x0619 + x);
        opAND(0xF0);
        opCMP(a, myMapper->readCPU(0x009E));
        if (!flgZ) {
            if (!flgC) {
                goto L_004CBB;
            }
            do {
                opINC(0x0611 + x, 1);
                goto L_004CBE;
            L_004CB0:
                a = myMapper->readCPU(0x0619 + x);
                opAND(0xF0);
                opCMP(a, myMapper->readCPU(0x009E));
                if (flgZ) {
                    goto L_004CBE;
                }
            } while (!flgC);
        }
    L_004CBB:
        opDEC(0x0611 + x, 1);
    L_004CBE:
        a = myMapper->readCPU(0x0611 + x);
        if (a < myMapper->readCPU(0x009B)) {
            a = myMapper->readCPU(0x009B);
        }
        if (a >= myMapper->readCPU(0x009C)) {
            a = myMapper->readCPU(0x009C);
        }
        myMapper->writeCPU(0x0611 + x, a);
        if (myMapper->readCPU(0x009F) != 0) {
            if (a < 0x84) {
                goto L_004CF7;
            }
            if (myMapper->readCPU(0x0621 + x) < myMapper->readCPU(0x009D)) {
                goto L_004CF7;
            }
            myMapper->writeCPU(0x0611 + x, 0x7C);
        }
        else {
            if (a >= 0x3C) {
                goto L_004CF7;
            }
            if (myMapper->readCPU(0x0621 + x) < myMapper->readCPU(0x009D)) {
                myMapper->writeCPU(0x0611 + x, 0x44);
            }
        }
    L_004CF7:
        a = myMapper->readCPU(0x0611 + x);
        y = a;
        flgC = false;
        opADC(0x06);
        myMapper->writeCPU(0x009C, a);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x009B, a);
        a = y;
        a = myMapper->readCPU(0x0611 + x);
        opAND(0x3F);
        y = a;
        opCMP(y, 0x20);
        if (flgC) {
            opAND(0x1F);
            y = a;
            a = myMapper->readCPU(0x0618 + x);
            opSBC(myMapper->readCPU(0xCD65 + y));
        }
        else {
            a = myMapper->readCPU(0xCD65 + y);
            opADC(myMapper->readCPU(0x0618 + x));
        }
        myMapper->writeCPU(0x0619 + x, a);
        if (a >= 0x10) {
            goto L_004D36;
        }
        if (myMapper->readCPU(0x0098) >= 0xA0) {
            do {
                a = 0x00;
                setLoadFlag(a);
                myMapper->writeCPU(0x0619 + x, a);
                if (flgZ) {
                    goto L_004D40;
                }
            L_004D36:
                if (a < 0xF0) {
                    goto L_004D40;
                }
            } while (myMapper->readCPU(0x0098) < 0x30);
        }
    L_004D40:
        a = myMapper->readCPU(0x0611 + x);
        opAND(0x20);
        if (flgZ) {
            goto L_004D51;
        }
        a = myMapper->readCPU(0x0620 + x);
        flgC = true;
        opSBC(myMapper->readCPU(0xCD85 + y));
        goto L_004D58;
    L_004D51:
        a = myMapper->readCPU(0x0620 + x);
        flgC = false;
        opADC(myMapper->readCPU(0xCD85 + y));
    L_004D58:
        myMapper->writeCPU(0x0621 + x, a);
        opINC(0x00A9, 1);
        opDEC(0x00AA, 1);
        if (flgN) {
            goto L_004D64;
        }
    }
L_004D64:
    popAddress();
}

void game::SUB_004DA5() {
    opCMP(myMapper->readCPU(0x0066), 0x58);
    if (!flgC) {
        goto L_004DAC;
    }
    popAddress();
    return;
L_004DAC:
    pushAddress(0x004DAE);
    SUB_004DB3();
    if (handleReturnAddress(poppedEntry.value, 0x004DAE)) return;
    pushAddress(0x004DB1);
    SUB_004DB3();
    if (handleReturnAddress(poppedEntry.value, 0x004DB1)) return;
    popAddress();
}

void game::SUB_004DB3() {
    x = myMapper->readCPU(0x0066);
    opCMP(x, 0x58);
    if (!flgC) {
        goto L_004DBA;
    }
    popAddress();
    return;
L_004DBA:
    opINC(0x0066, 1);
    myMapper->writeCPU(0x009B, 0x00);
    a = myMapper->readCPU(0xCE31 + x);
    myMapper->writeCPU(0x0099, a);
    opAND(0xF0);
    opASL_A(1);
    opROL_M(0x009B, 1);
    myMapper->writeCPU(0x009A, a);
    a = myMapper->readCPU(0x0099);
    opORA(0xF0);
    flgC = false;
    opADC(myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x009A, a);
    a = 0x24;
    opADC(myMapper->readCPU(0x009B));
    myMapper->writeCPU(0x009B, a);
    x = myMapper->readCPU(0x000E);
    myMapper->writeCPU(0x0700 + x, 0x01);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x009B));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x009A));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0x00);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x000E, x);
    a = myMapper->readCPU(0x0099);
    opAND(0x0F);
    opASL_A(3);
    myMapper->writeCPU(0x009A, a);
    a = myMapper->readCPU(0x0099);
    opLSR_A(4);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x009B, a);
    opLSR_A(2);
    flgC = false;
    opADC(0x81);
    opADC(myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x009C, a);
    myMapper->writeCPU(0x009D, 0x06);
    a = myMapper->readCPU(0x009B);
    opAND(0x03);
    x = a;
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y);
    opAND(myMapper->readCPU(0xCE2D + x));
    myMapper->writeCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_004E89() {
    a = myMapper->readCPU(0x0018);
    opASL_A(2);
    y = a;
    a = myMapper->readCPU(0x07E5 + y);
    opAND(0x0F);
    popAddress();
}

void game::SUB_004E94() {
    if (myMapper->readCPU(0x00C3) != 0) {
        goto L_004EA1;
    }
    if (myMapper->readCPU(0x004F) == 0) {
        a = 0xB2;
        pushAddress(0x004EA0);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x004EA0)) return;
    }
L_004EA1:
    if (myMapper->readCPU(0x004E) != 0) {
        opDEC(0x004E, 1);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x004E, 0x08);
    a = myMapper->readCPU(0x001A);
    if (a >= 0x06) {
        a = 0x06;
    }
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0098, myMapper->readCPU(0xCF2D + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0xCF2E + x));
    y = 0x00;
    a = myMapper->readCPU(0x004F);
    setLoadFlag(a);
    if (flgN) {
        opCMP(a, 0xFF);
        if (!flgZ) {
            if (myMapper->readCPU(0x00B2) != 0) {
                goto L_004ED5;
            }
            myMapper->writeCPU(0x004F, 0xFF);
            pushAddress(0x004ED4);
            SUB_00043F();
            if (handleReturnAddress(poppedEntry.value, 0x004ED4)) return;
        }
    L_004ED5:
        popAddress();
        return;
    }
    myMapper->writeCPU(0x009A, a);
    x = myMapper->readCPU(0x000E);
    do {
        a = 0x01;
        pushAddress(0x004EDE);
        SUB_004F28();
        if (handleReturnAddress(poppedEntry.value, 0x004EDE)) return;
        pushAddress(0x004EE1);
        SUB_004F25();
        if (handleReturnAddress(poppedEntry.value, 0x004EE1)) return;
        pushAddress(0x004EE4);
        SUB_004F25();
        if (handleReturnAddress(poppedEntry.value, 0x004EE4)) return;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y);
            opCMP(a, 0xFF);
            if (flgZ) {
                goto L_004F12;
            }
            opCMP(a, 0xFE);
            if (flgZ) {
                goto L_004F0C;
            }
            pushAddress(0x004EF1);
            SUB_004F23();
            if (handleReturnAddress(poppedEntry.value, 0x004EF1)) return;
        } while (!(myMapper->readCPU(0x009A) & 0x80));
        a = 0x3F;
        y = myMapper->readCPU(0x06FF + x);
        setLoadFlag(y);
        if (flgZ) {
            goto L_004EFF;
        }
        a = 0x35;
    L_004EFF:
        pushAddress(0x004F01);
        SUB_006C1E();
        if (handleReturnAddress(poppedEntry.value, 0x004F01)) return;
        do {
            a = 0xFF;
            pushAddress(0x004F06);
            SUB_004F28();
            if (handleReturnAddress(poppedEntry.value, 0x004F06)) return;
            myMapper->writeCPU(0x000E, x);
            opINC(0x004F, 1);
            popAddress();
            return;
        L_004F0C:
            a = 0x80;
            setLoadFlag(a);
            myMapper->writeCPU(0x004F, a);
        } while (!flgZ);
    L_004F12:
        pushAddress(0x004F14);
        SUB_004F25();
        if (handleReturnAddress(poppedEntry.value, 0x004F14)) return;
        myMapper->writeCPU(0x0098, myMapper->readCPU(0xCF2D));
        myMapper->writeCPU(0x0099, myMapper->readCPU(0xCF2E));
        y = 0x00;
        setLoadFlag(y);
    } while (flgZ);
    SUB_004F23();
    return;
}

void game::SUB_004F23() {
    opDEC(0x009A, 1);
    SUB_004F25();
    return;
}

void game::SUB_004F25() {
    a = myMapper->readCPU(myMapper->readCPU(0x0098) + (myMapper->readCPU((0x0098 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    SUB_004F28();
    return;
}

void game::SUB_004F28() {
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    popAddress();
}

void game::SUB_006C1E() {
    myMapper->writeCPU(0x00DF, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x00DF);
    opROL_A(3);
    opAND(0x03);
    myMapper->writeCPU(0x00E0, a);
    a = myMapper->readCPU(0x00DF);
    opAND(0x3F);
    myMapper->writeCPU(0x00DF, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x00DF));
    y = a;
    while (true) {
        myMapper->writeCPU(0x00E8, y);
        a = myMapper->readCPU(0xEFCD + y);
        myMapper->writeCPU(0x00E1, a);
        opLSR_A(2);
        y = a;
        x = myMapper->readCPU(0xECB2 + y);
        a = myMapper->readCPU(0x00DF);
        setLoadFlag(a);
        if (!flgZ) {
            if (a < myMapper->readCPU((0x0002 + x) & 0x00ff)) {
                goto L_006C95;
            }
        }
        myMapper->writeCPU((0x0002 + x) & 0x00ff, 0x00);
        y = myMapper->readCPU(0x00E8);
        a = myMapper->readCPU(0xEFCE + y);
        myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
        myMapper->writeCPU(0x00F6, a);
        a = myMapper->readCPU(0xEFCF + y);
        myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
        myMapper->writeCPU(0x00F7, a);
        y = 0x01;
        myMapper->writeCPU((0x0000 + x) & 0x00ff, y);
        opDEY(1);
        myMapper->writeCPU((0x0006 + x) & 0x00ff, y);
        if (x != 0xD2) {
            myMapper->writeCPU((0x0007 + x) & 0x00ff, y);
            myMapper->writeCPU((0x000C + x) & 0x00ff, y);
            myMapper->writeCPU((0x000B + x) & 0x00ff, y);
        }
        a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgZ) {
            myMapper->writeCPU(0x00DF, a);
        }
        opAND(0xF0);
        if (a != 0x20) {
            opINY(1);
        }
        myMapper->writeCPU((0x0009 + x) & 0x00ff, y);
        y = myMapper->readCPU(0x00E1);
        a = 0x00;
        if (y != 0x08) {
            a = 0x30;
        }
        myMapper->writeCPU(0x4000 + y, a);
        myMapper->writeCPU(0x4001 + y, a);
        a = myMapper->readCPU(0x00DF);
        myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
    L_006C95:
        opCMP(x, 0xC1);
        if (!flgZ) {
            goto L_006CA1;
        }
        a = 0x00;
        myMapper->writeCPU(0x00F0, a);
        myMapper->writeCPU(0x00F1, a);
        myMapper->writeCPU(0x00F2, a);
    L_006CA1:
        opDEC(0x00E0, 1);
        if (flgN) {
            goto L_006CAD;
        }
        y = myMapper->readCPU(0x00E8);
        opINY(3);
    }
L_006CAD:
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_006CB6() {
    a = y;
    myMapper->writeCPU((0x0002 + x) & 0x00ff, y);
    if (x == 0xD2) {
        goto L_006CC1;
    }
    myMapper->writeCPU((0x000C + x) & 0x00ff, y);
    a = 0x30;
L_006CC1:
    x = myMapper->readCPU(0x00F9);
    myMapper->writeCPU(0x4000 + x, a);
    popAddress();
}

void game::SUB_006CC7() {
    opINY(1);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU((0x0004 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y));
    popAddress();
}

void game::SUB_006CD2() {
    myMapper->writeCPU((0x0006 + x) & 0x00ff, 0x00);
    opINY(3);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x00FA));
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x00FB));
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
    SUB_006CE5();
    return;
}

void game::SUB_006CE5() {
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (!flgZ) {
        SUB_006D46();
        return;
    }
    SUB_006CEB();
    return;
}

void game::SUB_006CEB() {
    a = myMapper->readCPU((0x0006 + x) & 0x00ff);
    flgC = false;
    opADC(0x01);
    opINY(1);
    opCMP(a, myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y));
    if (flgZ) {
        SUB_006CD2();
        return;
    }
    if (flgN) {
        goto L_006CFA;
    }
    flgC = true;
    opSBC(0x01);
L_006CFA:
    myMapper->writeCPU((0x0006 + x) & 0x00ff, a);
    pushAddress(0x006CFE);
    SUB_006CC7();
    if (handleReturnAddress(poppedEntry.value, 0x006CFE)) return;
    SUB_006CE5();
    return;
}

void game::SUB_006D02() {
    x = 0xB0;
    y = 0x00;
    do {
        myMapper->writeCPU(0x00F8, x);
        myMapper->writeCPU(0x00F9, y);
        if (myMapper->readCPU((0x0002 + x) & 0x00ff) != 0) {
            pushAddress(0x006D10);
            SUB_006D46();
            if (handleReturnAddress(poppedEntry.value, 0x006D10)) return;
        }
        a = myMapper->readCPU(0x00F8);
        flgC = false;
        opADC(0x11);
        if (a == 0xF4) {
            if (myMapper->readCPU(0x00F0) == 0) {
                goto L_006D3C;
            }
            opINC(0x00F1, 1);
            if (myMapper->readCPU(0x00F1) == 0x30) {
                opINC(0x00F2, 1);
                myMapper->writeCPU(0x00F1, 0x00);
                if (myMapper->readCPU(0x00F3) >= 0x07) {
                    goto L_006D3C;
                }
                a = 0x00;
                myMapper->writeCPU(0x00D4, a);
                myMapper->writeCPU(0x4008, a);
                myMapper->writeCPU(0x4009, a);
            }
        L_006D3C:
            popAddress();
            return;
        }
        x = a;
        a = myMapper->readCPU(0x00F9);
        flgC = false;
        opADC(0x04);
        y = a;
    } while (!flgC);
    SUB_006D46();
    return;
}

void game::SUB_006D46() {
    y = 0x00;
    myMapper->writeCPU(0x00FA, myMapper->readCPU((0x0003 + x) & 0x00ff));
    myMapper->writeCPU(0x00FB, myMapper->readCPU((0x0004 + x) & 0x00ff));
    opDEC((0x0000 + x) & 0x00ff, 1);
    if (flgZ) {
        goto L_006D77;
    }
    if (myMapper->readCPU(0x0015) == 0) {
        goto L_006D74;
    }
    if (myMapper->readCPU((0x0002 + x) & 0x00ff) == 0x3B) {
        goto L_006D74;
    }
    while (true) {
        opINC((0x0000 + x) & 0x00ff, 1);
        a = y;
        myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
        x = myMapper->readCPU(0x00F9);
        myMapper->writeCPU(0x4002 + x, a);
        myMapper->writeCPU(0x4003 + x, a);
        myMapper->writeCPU(0x4008, a);
        myMapper->writeCPU(0x400C, 0x30);
        popAddress();
        return;
    L_006D74:
        goto L_006E35;
    L_006D77:
        a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFD);
        if (flgC) {
            if (!flgZ) {
                goto L_006D98;
            }
            a = myMapper->readCPU((0x0009 + x) & 0x00ff);
            opORA(0x80);
            myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
            pushAddress(0x006D87);
            SUB_006CC7();
            if (handleReturnAddress(poppedEntry.value, 0x006D87)) return;
            opINY(1);
            a = y;
            flgC = false;
            opADC(myMapper->readCPU(0x00FA));
            myMapper->writeCPU(0x00DD, a);
            a = 0x00;
            opADC(myMapper->readCPU(0x00FB));
            myMapper->writeCPU(0x00DE, a);
            SUB_006CE5();
            return;
        L_006D98:
            if (a == 0xFE) {
                SUB_006CEB();
                return;
            }
            a = myMapper->readCPU((0x0009 + x) & 0x00ff);
            setLoadFlag(a);
            if (!flgN) {
                SUB_006CB6();
                return;
            }
            opAND(0x7F);
            myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
            myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU(0x00DD));
            myMapper->writeCPU((0x0004 + x) & 0x00ff, myMapper->readCPU(0x00DE));
            SUB_006CE5();
            return;
        }
        a = myMapper->readCPU((0x0009 + x) & 0x00ff);
        opAND(0x7F);
        if (!flgZ) {
        }
        else {
            do {
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                opAND(0xF0);
                if (a != 0x20) {
                    goto L_006DD9;
                }
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                opAND(0x0F);
                myMapper->writeCPU((0x0001 + x) & 0x00ff, a);
                opINY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                x = myMapper->readCPU(0x00F9);
                myMapper->writeCPU(0x4000 + x, a);
                x = myMapper->readCPU(0x00F8);
                myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
                opINY(1);
            L_006DD9:
                myMapper->writeCPU((0x0000 + x) & 0x00ff, myMapper->readCPU((0x0001 + x) & 0x00ff));
                if (x == 0xD2) {
                    goto L_006E22;
                }
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                if (a != 0x11) {
                    goto L_006DEF;
                }
                opINY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                myMapper->writeCPU((0x000C + x) & 0x00ff, a);
                opINY(1);
            } while (!flgZ);
        L_006DEF:
            if (a == 0x10) {
                opINY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                opINY(1);
                x = myMapper->readCPU(0x00F9);
                myMapper->writeCPU(0x4001 + x, a);
                x = myMapper->readCPU(0x00F8);
                myMapper->writeCPU((0x000B + x) & 0x00ff, a);
            }
            a = myMapper->readCPU((0x0008 + x) & 0x00ff);
            opAND(0x10);
            if (!flgZ) {
                a = myMapper->readCPU((0x0008 + x) & 0x00ff);
                opAND(0xF0);
                myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
                a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                if (a == 0xF8) {
                    opINY(1);
                    a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
                }
                opLSR_A(4);
                opORA(myMapper->readCPU((0x0008 + x) & 0x00ff));
                myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
                x = myMapper->readCPU(0x00F9);
                myMapper->writeCPU(0x4000 + x, a);
            }
        L_006E22:
            a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
            opAND(0x07);
            myMapper->writeCPU(0x00F4, a);
            opINY(1);
            myMapper->writeCPU(0x00F5, myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y));
            x = myMapper->readCPU(0x00F8);
            pushAddress(0x006E31);
            SUB_006F62();
            if (handleReturnAddress(poppedEntry.value, 0x006E31)) return;
            SUB_006FA6();
            return;
        L_006E35:
            a = myMapper->readCPU((0x0009 + x) & 0x00ff);
            opAND(0x7F);
            if (flgZ) {
                popAddress();
                return;
            }
            if (x == 0xD2) {
                popAddress();
                return;
            }
            if (myMapper->readCPU(0x00FA) == 0) {
                opDEC(0x00FB, 1);
            }
            opDEC(0x00FA, 1);
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
            opAND(0xF0);
            if (a == 0xC0) {
                popAddress();
                return;
            }
            a = myMapper->readCPU((0x000D + x) & 0x00ff);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU((0x000D + x) & 0x00ff, a);
            if (a == myMapper->readCPU((0x0000 + x) & 0x00ff)) {
                flgC = true;
                opSBC(myMapper->readCPU((0x000F + x) & 0x00ff));
                if (!flgC) {
                    goto L_006E6C;
                }
                if (flgZ) {
                    goto L_006E6C;
                }
                popAddress();
                return;
            }
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU((0x000D + x) & 0x00ff, a);
        L_006E6C:
            a = myMapper->readCPU((0x0008 + x) & 0x00ff);
            opAND(0x0F);
            flgC = true;
            opSBC(0x01);
            if (!flgN) {
                goto L_006E76;
            }
            popAddress();
            return;
        L_006E76:
            a = myMapper->readCPU((0x0008 + x) & 0x00ff);
            opSBC(0x01);
            myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
            x = myMapper->readCPU(0x00F9);
            myMapper->writeCPU(0x4000 + x, a);
            popAddress();
            return;
        }
        if (myMapper->readCPU(0x0015) == 0) {
            goto L_006E89;
        }
    }
L_006E89:
    a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    if (a == 0xD0) {
        a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
        opAND(0x0F);
        myMapper->writeCPU((0x000A + x) & 0x00ff, a);
        opINY(1);
        myMapper->writeCPU((0x0005 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y));
        opINY(1);
        if (x == 0xD2) {
            goto L_006D77;
        }
        a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
        opLSR_A(4);
        myMapper->writeCPU((0x000E + x) & 0x00ff, a);
        a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
        opAND(0x0F);
        myMapper->writeCPU((0x000F + x) & 0x00ff, a);
        opINY(1);
    }
    a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    if (a == 0xE0) {
        a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
        opAND(0x0F);
        myMapper->writeCPU((0x0010 + x) & 0x00ff, a);
        opINY(1);
    }
    pushAddress(0x006EC4);
    SUB_006FA6();
    if (handleReturnAddress(poppedEntry.value, 0x006EC4)) return;
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
    opAND(0x0F);
    myMapper->writeCPU(0x00F4, a);
    if (!flgZ) {
        a = myMapper->readCPU((0x000A + x) & 0x00ff);
        flgC = false;
        do {
            opADC(myMapper->readCPU((0x000A + x) & 0x00ff));
            opDEC(0x00F4, 1);
        } while (!flgZ);
        if (flgZ) {
            goto L_006EDB;
        }
    }
    a = myMapper->readCPU((0x000A + x) & 0x00ff);
L_006EDB:
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (x != 0xD2) {
        flgC = false;
        opADC(myMapper->readCPU((0x000E + x) & 0x00ff));
        myMapper->writeCPU((0x000D + x) & 0x00ff, a);
        if (myMapper->readCPU(0x00F0) != 0) {
            if (x != 0xC1) {
                goto L_006F26;
            }
            if (myMapper->readCPU(0x00F2) >= 0x0B) {
                myMapper->writeCPU(0x00F2, 0x0B);
            }
            myMapper->writeCPU((0x000E + x) & 0x00ff, 0x06);
            if (myMapper->readCPU(0x00C3) == 0x13) {
                a = 0x0D;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_006F08;
                }
            }
            a = 0x05;
        L_006F08:
            myMapper->writeCPU((0x000F + x) & 0x00ff, a);
            a = myMapper->readCPU((0x0000 + x) & 0x00ff);
            flgC = false;
            opADC(myMapper->readCPU((0x000E + x) & 0x00ff));
            myMapper->writeCPU((0x000D + x) & 0x00ff, a);
            a = myMapper->readCPU((0x0005 + x) & 0x00ff);
            opAND(0x0F);
            flgC = true;
            opSBC(myMapper->readCPU(0x00F2));
            if (flgN) {
                a = 0x00;
            }
            myMapper->writeCPU(0x00F3, a);
            a = myMapper->readCPU((0x0005 + x) & 0x00ff);
            opAND(0xF0);
            opORA(myMapper->readCPU(0x00F3));
            if (!flgZ) {
                goto L_006F28;
            }
        }
    }
L_006F26:
    a = myMapper->readCPU((0x0005 + x) & 0x00ff);
L_006F28:
    myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
    x = myMapper->readCPU(0x00F9);
    myMapper->writeCPU(0x4000 + x, a);
    a = myMapper->readCPU(myMapper->readCPU(0x00FA) + (myMapper->readCPU((0x00FA + 1) & 0x00ff) << 8) + y);
    opLSR_A(4);
    if (a == 0x0C) {
        a = 0x00;
        if (x == 0x08) {
            goto L_006F41;
        }
        a = 0x30;
    L_006F41:
        myMapper->writeCPU(0x4000 + x, a);
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x00F8);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00F4, myMapper->readCPU(0xEFB8 + y));
    opINY(1);
    myMapper->writeCPU(0x00F5, myMapper->readCPU(0xEFB8 + y));
    y = myMapper->readCPU((0x0010 + x) & 0x00ff);
    do {
        if (y == 0x04) {
            SUB_006F62();
            return;
        }
        opLSR_M(0x00F4, 1);
        opROR_M(0x00F5, 1);
        opINY(1);
    } while (!flgZ);
    SUB_006F62();
    return;
}

void game::SUB_006F62() {
    if (x >= 0xD2) {
        goto L_006F7B;
    }
    if (myMapper->readCPU(0x00F4) == 0) {
        if (myMapper->readCPU(0x00F5) == 0) {
            goto L_006F7B;
        }
    }
    a = myMapper->readCPU((0x000C + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = false;
        opADC(myMapper->readCPU(0x00F5));
        myMapper->writeCPU(0x00F5, a);
        if (flgC) {
            opINC(0x00F4, 1);
        }
    }
L_006F7B:
    a = myMapper->readCPU(0x00F4);
    opORA(0x08);
    myMapper->writeCPU(0x00F4, a);
    if (x != 0xD2) {
        if (a != myMapper->readCPU((0x0007 + x) & 0x00ff)) {
            goto L_006F95;
        }
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opAND(0x10);
        if (flgZ) {
            goto L_006F97;
        }
        a = myMapper->readCPU((0x000B + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_006F97;
        }
        if (flgZ) {
            goto L_006F9E;
        }
    L_006F95:
        myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
    }
L_006F97:
    a = myMapper->readCPU(0x00F4);
    x = myMapper->readCPU(0x00F9);
    myMapper->writeCPU(0x4003 + x, a);
L_006F9E:
    x = myMapper->readCPU(0x00F9);
    myMapper->writeCPU(0x4002 + x, myMapper->readCPU(0x00F5));
    popAddress();
}

void game::SUB_006FA6() {
    opINY(1);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x00FA));
    x = myMapper->readCPU(0x00F8);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    if (!flgC) {
        goto L_006FB7;
    }
    a = myMapper->readCPU(0x00FB);
    opADC(0x00);
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
L_006FB7:
    popAddress();
}

void game::indirectJump(Uint16 target) {
    switch (target) {
    case 0x80E2:
        SUB_0000E2();
        break;
    case 0x8116:
        SUB_000116();
        break;
    case 0x8121:
        SUB_000121();
        break;
    case 0x8137:
        SUB_000137();
        break;
    case 0x8165:
        SUB_000165();
        break;
    case 0x816C:
        SUB_00016C();
        break;
    case 0x9650:
        SUB_001650();
        break;
    case 0x88B6:
        SUB_0008B6();
        break;
    case 0x88F6:
        SUB_0008F6();
        break;
    case 0x89E3:
        SUB_0009E3();
        break;
    case 0x892C:
        SUB_00092C();
        break;
    case 0x9B3E:
        SUB_001B3E();
        break;
    case 0x9BED:
        SUB_001BED();
        break;
    case 0x9C12:
        SUB_001C12();
        break;
    case 0x9C1E:
        SUB_001C1E();
        break;
    case 0x9C24:
        SUB_001C24();
        break;
    case 0x9A4D:
        SUB_001A4D();
        break;
    case 0x9A0E:
        SUB_001A0E();
        break;
    case 0x99E9:
        SUB_0019E9();
        break;
    case 0x99C0:
        SUB_0019C0();
        break;
    case 0x9982:
        SUB_001982();
        break;
    case 0x997E:
        SUB_00197E();
        break;
    case 0x9904:
        SUB_001904();
        break;
    case 0x988C:
        SUB_00188C();
        break;
    case 0x98DD:
        SUB_0018DD();
        break;
    case 0x98E5:
        SUB_0018E5();
        break;
    case 0x984F:
        SUB_00184F();
        break;
    case 0x8983:
        SUB_000983();
        break;
    case 0x89A1:
        SUB_0009A1();
        break;
    case 0x89AF:
        SUB_0009AF();
        break;
    case 0x89BB:
        SUB_0009BB();
        break;
    case 0x89CF:
        SUB_0009CF();
        break;
    case 0x89D3:
        SUB_0009D3();
        break;
    case 0xAE70:
        SUB_002E70();
        break;
    case 0xAEDD:
        SUB_002EDD();
        break;
    case 0xAE99:
        SUB_002E99();
        break;
    case 0xAEE1:
        SUB_002EE1();
        break;
    case 0xB205:
        SUB_003205();
        break;
    case 0xB0AF:
        SUB_0030AF();
        break;
    case 0xB198:
        SUB_003198();
        break;
    case 0xB6E1:
        SUB_0036E1();
        break;
    case 0xB26C:
        SUB_00326C();
        break;
    case 0xB311:
        SUB_003311();
        break;
    case 0xB36F:
        SUB_00336F();
        break;
    case 0xB37F:
        SUB_00337F();
        break;
    case 0xB3CB:
        SUB_0033CB();
        break;
    case 0xB402:
        SUB_003402();
        break;
    case 0xB434:
        SUB_003434();
        break;
    case 0xAF2E:
        SUB_002F2E();
        break;
    case 0xAF88:
        SUB_002F88();
        break;
    case 0xB026:
        SUB_003026();
        break;
    case 0xB098:
        SUB_003098();
        break;
    case 0xB747:
        SUB_003747();
        break;
    case 0xCA5E:
        SUB_004A5E();
        break;
    case 0xB377:
        SUB_003377();
        break;
    case 0xC906:
        SUB_004906();
        break;
    case 0xB7A1:
        SUB_0037A1();
        break;
    case 0xB914:
        SUB_003914();
        break;
    case 0xB913:
        SUB_003913();
        break;
    case 0xB480:
        SUB_003480();
        break;
    case 0xB4F2:
        SUB_0034F2();
        break;
    case 0xB4FD:
        SUB_0034FD();
        break;
    case 0xB559:
        SUB_003559();
        break;
    case 0xB569:
        SUB_003569();
        break;
    case 0xAF10:
        SUB_002F10();
        break;
    case 0xB61E:
        SUB_00361E();
        break;
    case 0xBB0F:
        SUB_003B0F();
        break;
    case 0xC486:
        SUB_004486();
        break;
    case 0xC546:
        SUB_004546();
        break;
    case 0xC686:
        SUB_004686();
        break;
    case 0xC5AD:
        SUB_0045AD();
        break;
    case 0xC653:
        SUB_004653();
        break;
    case 0xC6DE:
        SUB_0046DE();
        break;
    case 0xC429:
        SUB_004429();
        break;
    case 0xC526:
        SUB_004526();
        break;
    case 0xC58D:
        SUB_00458D();
        break;
    case 0xC633:
        SUB_004633();
        break;
    case 0xC752:
        SUB_004752();
        break;
    default:
        // Unhandled indirect jump
		break;
    }
}
