#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"
#include <stdexcept> // Add this include to resolve std::runtime_error

void game::repeat() {
    a = myMapper->readCPU(0x006F);
    opORA(myMapper->readCPU(0x001A));
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0xC03F + y);
    myMapper->writeCPU(0x006F, a);
}

void game::brk() {
}

void game::initGame() {
}

void game::endGame() {

}

void game::atScanline(Uint8 scanline) {

}

void game::atSprite0Hit() {
}

void game::reset() {
    flgD = false;
    flgI = true;
//L_01C00A:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_01C00A;
//    }
//    do {
//        a = myMapper->readCPU(0x2002);
//        setLoadFlag(a);
//    } while (!flgN);
    pushAddress(0xC016);
    jump(0xC132);
    if (handleReturnAddress(poppedEntry.value, 0xC016)) return;
    x = 0xFF;
    s = x;
    pushAddress(0xC01C);
    jump(0xC16D);
    if (handleReturnAddress(poppedEntry.value, 0xC01C)) return;
    pushAddress(0xC01F);
    jump(0xC18E);
    if (handleReturnAddress(poppedEntry.value, 0xC01F)) return;
    pushAddress(0xC022);
    jump(0xC19B);
    if (handleReturnAddress(poppedEntry.value, 0xC022)) return;
    pushAddress(0xC025);
    jump(0xC0F7);
    if (handleReturnAddress(poppedEntry.value, 0xC025)) return;
    pushAddress(0xC028);
    jump(0xC14B);
    if (handleReturnAddress(poppedEntry.value, 0xC028)) return;
    a = 0x06;
    myMapper->writeCPU(0x0024, a);
    pushAddress(0xC02F);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xC02F)) return;
    return;
}

void game::nmi() {
    pushStatus();
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x2002);
    y = myMapper->readCPU(0x001B);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_01C0C0;
    }
    pushAddress(0xC061);
    jump(0xC132);
    if (handleReturnAddress(poppedEntry.value, 0xC061)) return;
    a = 0x00;
    myMapper->writeCPU(0x2003, a);
    myMapper->writeCPU(0x4014, 0x02);
    y = 0x00;
    pushAddress(0xC070);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xC070)) return;
    pushAddress(0xC073);
    jump(0x800A);
    if (handleReturnAddress(poppedEntry.value, 0xC073)) return;
    pushAddress(0xC076);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xC076)) return;
    a = myMapper->readCPU(0x00FE);
    x = myMapper->readCPU(0x001F);
    setLoadFlag(x);
    if (!flgZ) {
        x = myMapper->readCPU(0x001B);
        setLoadFlag(x);
        if (!flgZ) {
            goto L_01C085;
        }
        opDEC(0x001F, 1);
        if (flgZ) {
            goto L_01C087;
        }
    L_01C085:
        a = 0x00;
    }
L_01C087:
    myMapper->writeCPU(0x2001, a);
    pushAddress(0xC08C);
    jump(0xF87D);
    if (handleReturnAddress(poppedEntry.value, 0xC08C)) return;
    pushAddress(0xC08F);
    jump(0xC11F);
    if (handleReturnAddress(poppedEntry.value, 0xC08F)) return;
    opINC(0x001B, 1);
    y = 0x00;
    pushAddress(0xC096);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xC096)) return;
    pushAddress(0xC099);
    jump(0x838A);
    if (handleReturnAddress(poppedEntry.value, 0xC099)) return;
    pushAddress(0xC09C);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xC09C)) return;
    y = 0x06;
    myMapper->writeCPU(0x0027, y);
    pushAddress(0xC0A3);
    jump(0xC8CD);
    if (handleReturnAddress(poppedEntry.value, 0xC0A3)) return;
    pushAddress(0xC0A6);
    jump(0xC1E4);
    if (handleReturnAddress(poppedEntry.value, 0xC0A6)) return;
    y = 0x00;
    pushAddress(0xC0AB);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xC0AB)) return;
    pushAddress(0xC0AE);
    jump(0x8052);
    if (handleReturnAddress(poppedEntry.value, 0xC0AE)) return;
    pushAddress(0xC0B1);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xC0B1)) return;
    pushAddress(0xC0B4);
    jump(0xCCEE);
    if (handleReturnAddress(poppedEntry.value, 0xC0B4)) return;
    a = 0x00;
    myMapper->writeCPU(0x001B, a);
    while (true) {
        opPLA();
        y = a;
        opPLA();
        x = a;
        opPLA();
        popStatus();
        return;
    L_01C0C0:
        a = myMapper->readCPU(0x00FE);
        x = myMapper->readCPU(0x001F);
        setLoadFlag(x);
        if (flgZ) {
            goto L_01C0C8;
        }
        a = 0x00;
    L_01C0C8:
        myMapper->writeCPU(0x2001, a);
        pushAddress(0xC0CD);
        jump(0xF87D);
        if (handleReturnAddress(poppedEntry.value, 0xC0CD)) return;
        pushAddress(0xC0D0);
        jump(0xC11F);
        if (handleReturnAddress(poppedEntry.value, 0xC0D0)) return;
        pushAddress(0xC0D3);
        jump(0xC0D7);
        if (handleReturnAddress(poppedEntry.value, 0xC0D3)) return;
    }
    SUB_01C0D7();
    return;
}

void game::SUB_00000A() {
    y = 0x00;
    do {
        if (myMapper->readCPU(0x0700 + y) == 0) {
            goto L_00002F;
        }
        a = myMapper->readCPU(0x00FF);
        opAND(0x18);
        opORA(myMapper->readCPU(0x8007 + x));
        myMapper->writeCPU(0x2000, a);
        opINY(1);
        a = myMapper->readCPU(0x2002);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0700 + y));
        opINY(1);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0700 + y));
        opINY(1);
        if (!flgZ) {
            goto L_000041;
        }
    L_00002F:
        a = 0x00;
        myMapper->writeCPU(0x0700, a);
        myMapper->writeCPU(0x0020, a);
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x00FF));
        popAddress();
        return;
        do {
            a = 0xFF;
            do {
                myMapper->writeCPU(0x2007, a);
            L_000041:
                a = myMapper->readCPU(0x0700 + y);
                opINY(1);
            } while (a != 0xFF);
            opCMP(myMapper->readCPU(0x0700 + y), 0x03);
        } while (flgC);
    } while (!flgC);
    SUB_000052();
    return;
}

void game::SUB_000052() {
    myMapper->writeCPU(0x0005, 0x00);
    myMapper->writeCPU(0x0007, 0x2E);
    a = myMapper->readCPU(0x0078);
    do {
        flgC = false;
        opADC(0x44);
    } while (a < 0x44);
    myMapper->writeCPU(0x0078, a);
    myMapper->writeCPU(0x0004, a);
    do {
        x = myMapper->readCPU(0x0005);
        if (x >= 0x1C) {
            goto L_0000AC;
        }
        if (myMapper->readCPU(0x0300 + x) == 0) {
            myMapper->writeCPU(0x0000, myMapper->readCPU(0x0338 + x));
            myMapper->writeCPU(0x0001, myMapper->readCPU(0x0354 + x));
            myMapper->writeCPU(0x0002, myMapper->readCPU(0x038C + x));
            myMapper->writeCPU(0x004B, myMapper->readCPU(0x0450 + x));
            a = myMapper->readCPU(0x031C + x);
            opASL_A(1);
            if (flgC) {
                goto L_00009A;
            }
            y = a;
            myMapper->writeCPU(0x0008, myMapper->readCPU(0x8FBE + y));
            a = myMapper->readCPU(0x8FBF + y);
            myMapper->writeCPU(0x0009, a);
            pushAddress(0x8099);

            if (handleReturnAddress(poppedEntry.value, 0x8099)) return;
        L_00009A:
            y = a;
            myMapper->writeCPU(0x0008, myMapper->readCPU(0x90BE + y));
            a = myMapper->readCPU(0x90BF + y);
            myMapper->writeCPU(0x0009, a);
            pushAddress(0x80A7);
            jump(0x80D6);
            if (handleReturnAddress(poppedEntry.value, 0x80A7)) return;
        }
        opINC(0x0005, 1);
    } while (!flgZ);
L_0000AC:
    x = myMapper->readCPU(0x0004);
    y = myMapper->readCPU(0x0007);
    do {
        myMapper->writeCPU(0x0200 + x, 0xF4);
        a = x;
        do {
            flgC = false;
            opADC(0xC4);
        } while (a < 0x44);
        x = a;
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_000187() {
    myMapper->writeCPU(0x00E5, a);
    if (flgZ) {
        myMapper->writeCPU(0x00C2, a);
        myMapper->writeCPU(0x00D2, a);
        popAddress();
        return;
    }
    if (a == 0x1A) {
        myMapper->writeCPU(0x00EE, 0x01);
    }
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x03;
    myMapper->writeCPU(0x00E0, myMapper->readCPU(0x8185));
    myMapper->writeCPU(0x00E1, myMapper->readCPU(0x8186));
    do {
        a = myMapper->readCPU(0x00E5);
        flgC = false;
        opADC(myMapper->readCPU(0x00E0));
        myMapper->writeCPU(0x00E0, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x00E1));
        myMapper->writeCPU(0x00E1, a);
        opDEX(1);
    } while (!flgZ);
    y = 0x00;
    myMapper->writeCPU(0x00E4, y);
    a = myMapper->readCPU(myMapper->readCPU(0x00E0) + (myMapper->readCPU((0x00E0 + 1) & 0x00ff) << 8) + y);
    opROL_A(3);
    opAND(0x03);
    myMapper->writeCPU(0x00E6, a);
    a = myMapper->readCPU(0x00E5);
    if (a != 0x04) {
        if (a == myMapper->readCPU(0x00C2)) {
            goto L_00020D;
        }
        if (a == myMapper->readCPU(0x00D2)) {
            goto L_0001F4;
        }
    }
    y = myMapper->readCPU(0x00E4);
    a = myMapper->readCPU(myMapper->readCPU(0x00E0) + (myMapper->readCPU((0x00E0 + 1) & 0x00ff) << 8) + y);
    opAND(0x3F);
    myMapper->writeCPU(0x00E8, a);
    if (myMapper->readCPU(0x00E5) == 0x04) {
        a = myMapper->readCPU(0x00E8);
        pushAddress(0x81E5);

        if (handleReturnAddress(poppedEntry.value, 0x81E5)) return;
    }
    a = myMapper->readCPU(0x00E8);
    if (a == 0x10) {
        if (myMapper->readCPU(0x00C2) == 0) {
            goto L_00020D;
        }
        a = myMapper->readCPU(0x00D2);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0001FC;
        }
    L_0001F4:
        a = 0x14;
        pushAddress(0x81F8);

        if (handleReturnAddress(poppedEntry.value, 0x81F8)) return;
        do {
            do {
                pushAddress(0x8211);

                if (handleReturnAddress(poppedEntry.value, 0x8211)) return;
            L_0001FC:
                if (a >= myMapper->readCPU(0x00C2)) {
                    goto L_000207;
                }
            } while (a >= myMapper->readCPU(0x00E5));
            pushAddress(0x8206);

            if (handleReturnAddress(poppedEntry.value, 0x8206)) return;
        L_000207:
            a = myMapper->readCPU(0x00C2);
        } while (a >= myMapper->readCPU(0x00E5));
    L_00020D:
        a = 0x10;
    }
    myMapper->writeCPU(0x00E7, a);
    opLSR_A(2);
    y = a;
    x = myMapper->readCPU(0x82AF + y);
    a = myMapper->readCPU(0x00E5);
    setLoadFlag(a);
    if (!flgZ) {
        if (a < myMapper->readCPU((0x0002 + x) & 0x00ff)) {
            goto L_000298;
        }
    }
    myMapper->writeCPU((0x0002 + x) & 0x00ff, 0x00);
    y = myMapper->readCPU(0x00E4);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E0) + (myMapper->readCPU((0x00E0 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    myMapper->writeCPU(0x00BE, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E0) + (myMapper->readCPU((0x00E0 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
    myMapper->writeCPU(0x00BF, a);
    y = 0x01;
    myMapper->writeCPU((0x0000 + x) & 0x00ff, y);
    opDEY(1);
    myMapper->writeCPU((0x0006 + x) & 0x00ff, y);
    if (x == 0x80) {
        myMapper->writeCPU(0x00A1, y);
        myMapper->writeCPU(0x00A7, y);
    }
    if (x == 0x90) {
        myMapper->writeCPU(0x00B5, y);
        myMapper->writeCPU(0x00B8, y);
    }
    if (x != 0xA0) {
        myMapper->writeCPU((0x0001 + x) & 0x00ff, y);
        if (x == 0xB0) {
            goto L_000267;
        }
    }
    a = myMapper->readCPU(myMapper->readCPU(0x00BE) + (myMapper->readCPU((0x00BE + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgZ) {
        myMapper->writeCPU(0x00E5, a);
        if (x == 0xB0) {
            goto L_000267;
        }
    }
    opAND(0xF0);
    if (a != 0x20) {
        opINY(1);
    }
    myMapper->writeCPU((0x0008 + x) & 0x00ff, y);
L_000267:
    y = myMapper->readCPU(0x00E7);
    if (y == 0x00) {
        a = myMapper->readCPU(0x00C2);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_000294;
        }
        pushAddress(0x8273);

        if (handleReturnAddress(poppedEntry.value, 0x8273)) return;
    }
    if (y == 0x04) {
        if (myMapper->readCPU(0x00D2) != 0) {
            goto L_000294;
        }
    }
    a = y;
    opAND(0x0F);
    y = a;
    a = 0x00;
    if (y != 0x08) {
        a = 0x30;
    }
    myMapper->writeCPU(0x4000 + y, a);
    pushAddress(0x828D);
    jump(0x817B);
    if (handleReturnAddress(poppedEntry.value, 0x828D)) return;
    myMapper->writeCPU(0x4001 + y, a);
    pushAddress(0x8293);
    jump(0x817B);
    if (handleReturnAddress(poppedEntry.value, 0x8293)) return;
L_000294:
    a = myMapper->readCPU(0x00E5);
    myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
L_000298:
    opDEC(0x00E6, 1);
    if (flgN) {
        goto L_0002A6;
    }
    y = myMapper->readCPU(0x00E4);
    opINY(3);
    myMapper->writeCPU(0x00E4, y);
    pushAddress(0x82A5);

    if (handleReturnAddress(poppedEntry.value, 0x82A5)) return;
L_0002A6:
    a = 0x00;
    myMapper->writeCPU(0x00E1, a);
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_00038A() {
    if (myMapper->readCPU(0x00E2) == 0) {
        goto L_0003AF;
    }
    opDEC(0x00E3, 1);
    if (flgZ) {
        myMapper->writeCPU(0x00E3, 0x28);
        opDEC(0x0085, 1);
        a = myMapper->readCPU(0x0085);
        opAND(0x0F);
        if (!flgZ) {
            opDEC(0x0095, 1);
            a = myMapper->readCPU(0x0095);
            opAND(0x0F);
            if (!flgZ) {
                goto L_0003AF;
            }
        }
        myMapper->writeCPU(0x00E2, 0x00);
        a = myMapper->readCPU(0x0060);
        pushAddress(0x83AE);
        jump(0x8187);
        if (handleReturnAddress(poppedEntry.value, 0x83AE)) return;
    }
L_0003AF:
    x = 0x80;
    y = 0x00;
    do {
        myMapper->writeCPU(0x00AB, x);
        myMapper->writeCPU(0x00AC, y);
        a = myMapper->readCPU((0x0002 + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
            pushAddress(0x83BD);
            jump(0x83D3);
            if (handleReturnAddress(poppedEntry.value, 0x83BD)) return;
        }
        a = myMapper->readCPU(0x00AB);
        flgC = false;
        opADC(0x10);
        if (a != 0xE0) {
            goto L_0003C8;
        }
        popAddress();
        return;
    L_0003C8:
        x = a;
        a = myMapper->readCPU(0x00AC);
        flgC = false;
        opADC(0x04);
        opAND(0x0F);
        y = a;
    } while (!flgC);
    y = 0x00;
    myMapper->writeCPU(0x00BA, myMapper->readCPU((0x0003 + x) & 0x00ff));
    a = myMapper->readCPU((0x0004 + x) & 0x00ff);
    myMapper->writeCPU(0x00BB, a);
    opDEC((0x0000 + x) & 0x00ff, 1);
    if (flgZ) {
        pushAddress(0x83E3);

        if (handleReturnAddress(poppedEntry.value, 0x83E3)) return;
    }
    a = myMapper->readCPU(0x0022);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x00EF, a);
        a = 0x54;
        if (a != myMapper->readCPU((0x0002 + x) & 0x00ff)) {
            goto L_000415;
        }
        pushAddress(0x83F2);

        if (handleReturnAddress(poppedEntry.value, 0x83F2)) return;
    }
    a = 0x1A;
    if (a != myMapper->readCPU(0x00C2)) {
        if (a == myMapper->readCPU(0x00D2)) {
            goto L_000400;
        }
        pushAddress(0x83FF);

        if (handleReturnAddress(poppedEntry.value, 0x83FF)) return;
    }
L_000400:
    a = myMapper->readCPU(0x00EE);
    setLoadFlag(a);
    if (flgZ) {
        if (x == 0xB0) {
            goto L_000412;
        }
        if (x != 0xC0) {
            if (x == 0xD0) {
                goto L_000412;
            }
            opINC((0x0000 + x) & 0x00ff, 1);
        }
    L_000412:
        pushAddress(0x8414);

        if (handleReturnAddress(poppedEntry.value, 0x8414)) return;
    }
L_000415:
    opINC((0x0000 + x) & 0x00ff, 1);
    myMapper->writeCPU((0x0001 + x) & 0x00ff, y);
    opCMP(0x54, myMapper->readCPU(0x00D2));
    if (!flgZ) {
        a = myMapper->readCPU((0x0001 + x) & 0x00ff);
        pushAddress(0x8424);
        jump(0x876B);
        if (handleReturnAddress(poppedEntry.value, 0x8424)) return;
        if (!flgC) {
            a = 0x30;
            x = myMapper->readCPU(0x00AC);
            myMapper->writeCPU(0x4000 + x, a);
            pushAddress(0x8430);
            jump(0x82B5);
            if (handleReturnAddress(poppedEntry.value, 0x8430)) return;
        }
        a = 0x30;
        myMapper->writeCPU(0x4004, a);
        pushAddress(0x8438);
        jump(0x82B5);
        if (handleReturnAddress(poppedEntry.value, 0x8438)) return;
        pushAddress(0x843B);

        if (handleReturnAddress(poppedEntry.value, 0x843B)) return;
    }
    a = 0x30;
    myMapper->writeCPU(0x4000, a);
    pushAddress(0x8443);
    jump(0x82B5);
    if (handleReturnAddress(poppedEntry.value, 0x8443)) return;
    a = myMapper->readCPU((0x0001 + x) & 0x00ff);
    pushAddress(0x8448);
    jump(0x876B);
    if (handleReturnAddress(poppedEntry.value, 0x8448)) return;
    if (flgC) {
        goto L_000455;
    }
    a = 0x30;
    x = myMapper->readCPU(0x00AC);
    myMapper->writeCPU(0x4000 + x, a);
    pushAddress(0x8454);
    jump(0x82B5);
    if (handleReturnAddress(poppedEntry.value, 0x8454)) return;
L_000455:
    a = 0x00;
    myMapper->writeCPU(0x4008, a);
    pushAddress(0x845C);
    jump(0x82B5);
    if (handleReturnAddress(poppedEntry.value, 0x845C)) return;
    a = 0x30;
    myMapper->writeCPU(0x400C, a);
    pushAddress(0x8464);
    jump(0x82B5);
    if (handleReturnAddress(poppedEntry.value, 0x8464)) return;
    myMapper->writeCPU(0x00EE, 0x00);
    popAddress();
}

void game::SUB_01A333() {
    do {
        myMapper->writeCPU(0x004B, a);
        flgC = true;
        opSBC(0x65);
    } while (flgC);
    x = 0x00;
    a = myMapper->readCPU(0x004B);
    flgC = true;
    opSBC(0x0A);
    if (!flgC) {
        goto L_01A34F;
    }
    opPHA();
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    opPLA();
    myMapper->writeCPU(0x004B, a);
    pushAddress(0xA34E);

    if (handleReturnAddress(poppedEntry.value, 0xA34E)) return;
L_01A34F:
    a = x;
    opORA(myMapper->readCPU(0x004B));
    popAddress();
}


void game::SUB_01C0D7() {
    a = myMapper->readCPU(0x007F);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01C0EE;
    }
    a = 0x01;
    myMapper->writeCPU(0x007F, a);
    y = 0x00;
    pushAddress(0xC0E3);
    jump(0xC1D8);
    if (handleReturnAddress(poppedEntry.value, 0xC0E3)) return;
    pushAddress(0xC0E6);
    jump(0x838A);
    if (handleReturnAddress(poppedEntry.value, 0xC0E6)) return;
    pushAddress(0xC0E9);
    jump(0xC1CF);
    if (handleReturnAddress(poppedEntry.value, 0xC0E9)) return;
    a = 0x00;
    myMapper->writeCPU(0x007F, a);
L_01C0EE:
    popAddress();
}

void game::SUB_01C0F7() {
    myMapper->writeCPU(0x4015, 0x0F);
    a = 0xC0;
    myMapper->writeCPU(0x4017, a);
    popAddress();
}

void game::SUB_01C102() {
    a = 0xB0;
    myMapper->writeCPU(0x00FF, a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x00FE, 0x1E);
    a = 0x05;
    myMapper->writeCPU(0x001F, a);
    popAddress();
}

void game::SUB_01C11F() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x00FD));
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x00FC));
    a = myMapper->readCPU(0x00FF);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_01C132() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    popAddress();
}

void game::SUB_01C13F() {
    x = 0x03;
    do {
        myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0xC13B + x));
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01C14B() {
    if (myMapper->readCPU(0x007F) != 0) {
        goto L_01C16C;
    }
    myMapper->writeCPU(0x07F5, y);
    a = 0x00;
    myMapper->writeCPU(0x00E2, a);
    myMapper->writeCPU(0x00C2, a);
    myMapper->writeCPU(0x00D2, a);
    a = 0x01;
    myMapper->writeCPU(0x00E3, a);
    pushAddress(0xC160);
    jump(0xC132);
    if (handleReturnAddress(poppedEntry.value, 0xC160)) return;
    a = 0x55;
    pushAddress(0xC165);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xC165)) return;
    pushAddress(0xC168);
    jump(0xC102);
    if (handleReturnAddress(poppedEntry.value, 0xC168)) return;
    y = myMapper->readCPU(0x07F5);
L_01C16C:
    popAddress();
}

void game::SUB_01C16D() {
    a = 0x00;
    myMapper->writeCPU(0x0700, a);
    x = 0x02;
    y = 0x06;
    opPHA();
    a = x;
    myMapper->writeCPU(0x0001, y);
    flgC = false;
    opSBC(myMapper->readCPU(0x0001));
    x = a;
    opPLA();
    y = 0x00;
    myMapper->writeCPU(0x0000, y);
    do {
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y, a);
            opDEY(1);
        } while (!flgZ);
        opDEC(0x0001, 1);
        opINX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01C18E() {
    x = 0xB0;
    a = 0x00;
    do {
        myMapper->writeCPU(0x0100 + x, a);
        opDEX(1);
    } while (x >= 0x30);
    popAddress();
}

void game::SUB_01C19B() {
    x = 0x00;
    a = 0x00;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opINX(1);
        opCMP(x, 0xF0);
    } while (!flgC);
    popAddress();
}

void game::SUB_01C1A7() {
    opPHA();
    a = myMapper->readCPU(0x007F);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01C1CD;
    }
    opPLA();
    myMapper->writeCPU(0x07F6, a);
    myMapper->writeCPU(0x07F5, y);
    a = 0x01;
    myMapper->writeCPU(0x007F, a);
    y = 0x00;
    pushAddress(0xC1BB);
    jump(0xC1D8);
    if (handleReturnAddress(poppedEntry.value, 0xC1BB)) return;
    a = myMapper->readCPU(0x07F6);
    pushAddress(0xC1C1);
    jump(0x8187);
    if (handleReturnAddress(poppedEntry.value, 0xC1C1)) return;
    pushAddress(0xC1C4);
    jump(0xC1CF);
    if (handleReturnAddress(poppedEntry.value, 0xC1C4)) return;
    y = myMapper->readCPU(0x07F5);
    myMapper->writeCPU(0x007F, 0x00);
    popAddress();
    return;
L_01C1CD:
    opPLA();
    popAddress();
}

void game::SUB_01C1CF() {
    y = myMapper->readCPU(0x0027);
    jump(0xC1D8);
    return;
}

void game::SUB_01C1D4() {
    y = myMapper->readCPU(0x0024);
    SUB_01C1D6();
    return;
}

void game::SUB_01C1D6() {
    myMapper->writeCPU(0x0027, y);
    SUB_01C1D8();
    return;
}

void game::SUB_01C1D8() {
    opPHA();
    a = myMapper->readCPU(0xC000 + y);
    myMapper->writeCPU(0xC000 + y, a);
    myMapper->writeCPU(0xC000 + y, a);
    opPLA();
    popAddress();
}

void game::SUB_01C1E4() {
    opINC(0x001A, 1);
    a = myMapper->readCPU(0x0018);
    if (a >= 0x03) {
        goto L_01C1EF;
    }
    pushAddress(0xC1EE);
    jump(0xC91C);
    if (handleReturnAddress(poppedEntry.value, 0xC1EE)) return;
L_01C1EF:
    a = myMapper->readCPU(0x0018);
    pushAddress(0xC1F3);
    jump(0xCA6D);
    if (handleReturnAddress(poppedEntry.value, 0xC1F3)) return;
    //NOP
    SUB_01C365();
    return;
}

void game::SUB_01C365() {
    opINC(0x0019, 1);
    popAddress();
}

void game::SUB_01C371() {
    opINC(0x0018, 1);
    SUB_01C373();
    return;
}

void game::SUB_01C373() {
    a = 0x00;
    myMapper->writeCPU(0x001E, a);
    myMapper->writeCPU(0x0019, a);
    popAddress();
}

void game::SUB_01C37A() {
    myMapper->writeCPU(0x0018, a);
    a = 0x50;
    setLoadFlag(a);
    myMapper->writeCPU(0x0025, a);
    if (!flgZ) {
        jump(0xC373);
        return;
    }
    a = myMapper->readCPU(0x0028);
    if (a == 0x12) {
        myMapper->writeCPU(0x0029, a);
        myMapper->writeCPU(0x0018, 0x0C);
        myMapper->writeCPU(0x0019, 0x08);
        popAddress();
        return;
    }
    pushAddress(0xC37C);
    jump(0xFA6A);
    if (handleReturnAddress(poppedEntry.value, 0xC37C)) return;
    a = 0x00;
    pushAddress(0xC39A);
    jump(0x9BBA);
    if (handleReturnAddress(poppedEntry.value, 0xC39A)) return;
    pushAddress(0xC39D);
    jump(0xE8F0);
    if (handleReturnAddress(poppedEntry.value, 0xC39D)) return;
    a = myMapper->readCPU(0x0584);
    opAND(0x03);
    myMapper->writeCPU(0x003C, a);
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_01C3CF;
    }
    a = myMapper->readCPU(0x002E);
    opCMP(a, 0x80);
    if (flgZ) {
        goto L_01C3C6;
    }
    while (true) {
        pushAddress(0xC3B1);
        jump(0x990B);
        if (handleReturnAddress(poppedEntry.value, 0xC3B1)) return;
        y = 0x04;
        pushAddress(0xC3B6);
        jump(0xC1D6);
        if (handleReturnAddress(poppedEntry.value, 0xC3B6)) return;
        pushAddress(0xC3B9);
        jump(0xF5EA);
        if (handleReturnAddress(poppedEntry.value, 0xC3B9)) return;
        pushAddress(0xC3BC);
        jump(0xC1D4);
        if (handleReturnAddress(poppedEntry.value, 0xC3BC)) return;
        a = myMapper->readCPU(0x003C);
        opEOR(0x03);
        myMapper->writeCPU(0x003C, a);
        pushAddress(0xC3C5);

        if (handleReturnAddress(poppedEntry.value, 0xC3C5)) return;
    L_01C3C6:
        pushAddress(0xC3F4);
        jump(0xC474);
        if (handleReturnAddress(poppedEntry.value, 0xC3F4)) return;
        pushAddress(0xC3CB);
        jump(0xC4A4);
        if (handleReturnAddress(poppedEntry.value, 0xC3CB)) return;
        goto L_01C3FB;
    L_01C3CF:
        opDEX(1);
        if (!flgZ) {
            goto L_01C3FE;
        }
        a = myMapper->readCPU(0x001A);
        opAND(0x0F);
        if (flgZ) {
            opINC(0x0025, 1);
            opCMP(myMapper->readCPU(0x0025), 0x02);
            if (flgZ) {
                a = 0x1D;
                pushAddress(0xC3E4);
                jump(0xC1A7);
                if (handleReturnAddress(poppedEntry.value, 0xC3E4)) return;
            }
        }
        a = myMapper->readCPU(0x0025);
        if (a == 0x03) {
            goto L_01C3F2;
        }
        flgC = false;
        opADC(0x1C);
        myMapper->writeCPU(0x031F, a);
        popAddress();
        return;
    L_01C3F2:
        a = 0x01;
        myMapper->writeCPU(0x001A, a);
        opDEC(0x0025, 1);
        goto L_01C3FB;
        while (true) {
            do {
            L_01C3FB:
                jump(0xC365);
                return;
            L_01C3FE:
                opDEX(1);
                if (!flgZ) {
                    goto L_01C418;
                }
                x = 0xB0;
                if (myMapper->readCPU(0x0584) == 0x01) {
                    goto L_01C40C;
                }
                x = 0x50;
            L_01C40C:
                a = x;
            } while (a == myMapper->readCPU(0x038C));
            pushAddress(0xC414);
            jump(0x9458);
            if (handleReturnAddress(poppedEntry.value, 0xC414)) return;
            pushAddress(0xC417);

            if (handleReturnAddress(poppedEntry.value, 0xC417)) return;
        L_01C418:
            opDEX(1);
            if (!flgZ) {
                goto L_01C442;
            }
            a = myMapper->readCPU(0x001A);
            opAND(0x07);
            if (flgZ) {
                opDEC(0x0025, 1);
            }
            a = myMapper->readCPU(0x0025);
            setLoadFlag(a);
            if (flgZ) {
                goto L_01C42E;
            }
            flgC = false;
            opADC(0x1C);
            myMapper->writeCPU(0x031F, a);
            popAddress();
            return;
        L_01C42E:
            a = 0x1D;
            pushAddress(0xC432);
            jump(0xC1A7);
            if (handleReturnAddress(poppedEntry.value, 0xC432)) return;
            a = 0x00;
            myMapper->writeCPU(0x031F, a);
            pushAddress(0xC43A);
            jump(0xC4A8);
            if (handleReturnAddress(poppedEntry.value, 0xC43A)) return;
            a = 0x30;
            myMapper->writeCPU(0x0025, a);
        }
    L_01C442:
        opDEX(1);
        if (!flgZ) {
            goto L_01C44A;
        }
        opDEC(0x0025, 1);
        do {
            if (flgZ) {
                goto L_01C3FB;
            }
            popAddress();
            return;
        L_01C44A:
            opDEX(1);
            if (!flgZ) {
                goto L_01C455;
            }
            a = myMapper->readCPU(0x002E);
            setLoadFlag(a);
        } while (flgZ);
    }
L_01C455:
    a = myMapper->readCPU(0x0450);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01C45C;
    }
    opINC(0x0028, 1);
L_01C45C:
    pushAddress(0xC45E);
    jump(0xA296);
    if (handleReturnAddress(poppedEntry.value, 0xC45E)) return;
    pushAddress(0xC461);
    jump(0xC994);
    if (handleReturnAddress(poppedEntry.value, 0xC461)) return;
    pushAddress(0xC464);
    jump(0xCFBD);
    if (handleReturnAddress(poppedEntry.value, 0xC464)) return;
    pushAddress(0xC467);
    jump(0xD162);
    if (handleReturnAddress(poppedEntry.value, 0xC467)) return;
    pushAddress(0xC46A);
    jump(0xC8C3);
    if (handleReturnAddress(poppedEntry.value, 0xC46A)) return;
    myMapper->writeCPU(0x0018, 0x05);
    myMapper->writeCPU(0x0019, 0x06);
    popAddress();
}

void game::SUB_01C474() {
    myMapper->writeCPU(0x0025, 0x01);
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFB62 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0357, a);
    a = myMapper->readCPU(0xFB62 + x);
    opAND(0x01);
    x = a;
    myMapper->writeCPU(0x038F, myMapper->readCPU(0xC4A2 + x));
    myMapper->writeCPU(0x031F, 0x1D);
    myMapper->writeCPU(0x033B, 0x00);
    a = myMapper->readCPU(0x0584);
    opAND(0x01);
    myMapper->writeCPU(0x0453, a);
    popAddress();
}

void game::SUB_01C4A4() {
    a = 0x07;
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xC4AA);
        return;
    }
    SUB_01C4A8();
    return;
}

void game::SUB_01C4A8() {
    a = 0x00;
    SUB_01C4AA();
    return;
}

void game::SUB_01C4AA() {
    myMapper->writeCPU(0x004B, a);
    x = myMapper->readCPU(0x0020);
    myMapper->writeCPU(0x0700 + x, 0x02);
    opINX(1);
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xFB75 + y));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xFB76 + y));
    y = myMapper->readCPU(0x004B);
    do {
        opINX(1);
        a = myMapper->readCPU(0xC4D9 + y);
        myMapper->writeCPU(0x0700 + x, a);
        if (a == 0xFF) {
            goto L_01C4D5;
        }
        opINY(1);
    } while (!flgZ);
L_01C4D5:
    opINX(1);
    myMapper->writeCPU(0x0020, x);
    popAddress();
}

void game::SUB_01C8C3() {
    a = myMapper->readCPU(0x0028);
    if (a != 0x06) {
        goto L_01C8CC;
    }
    pushAddress(0xC8CB);
    jump(0x837A);
    if (handleReturnAddress(poppedEntry.value, 0xC8CB)) return;
L_01C8CC:
    popAddress();
}

void game::SUB_01C8CD() {
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    y = 0x08;
    do {
        a = myMapper->readCPU(0x4016);
        opAND(0x03);
        myMapper->writeCPU(0x0007, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0007));
        opLSR_A(1);
        opROL_M(0x0004, 1);
        a = myMapper->readCPU(0x4017);
        opAND(0x03);
        myMapper->writeCPU(0x0007, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0007));
        opLSR_A(1);
        opROL_M(0x0005, 1);
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x001C);
    opAND(myMapper->readCPU(0x0010));
    if (!flgZ) {
        jump(0xC90D);
        return;
    }
    a = myMapper->readCPU(0x0004);
    pushAddress(0xC8FF);
    jump(0xC917);
    if (handleReturnAddress(poppedEntry.value, 0xC8FF)) return;
    opINX(1);
    a = myMapper->readCPU((0x0004 + x) & 0x00ff);
    SUB_01C903();
    return;
}

void game::SUB_01C903() {
    y = a;
    opEOR(myMapper->readCPU((0x00F7 + x) & 0x00ff));
    opAND(myMapper->readCPU((0x0004 + x) & 0x00ff));
    myMapper->writeCPU((0x00F5 + x) & 0x00ff, a);
    myMapper->writeCPU((0x00F7 + x) & 0x00ff, y);
    popAddress();
}

void game::SUB_01C90D() {
    a = 0xFF;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01C913;
    }
    a = 0x30;
L_01C913:
    opAND(myMapper->readCPU(0x0004));
    opORA(myMapper->readCPU(0x0005));
    SUB_01C917();
    return;
}

void game::SUB_01C917() {
    myMapper->writeCPU(0x0004, a);
    jump(0xC903);
    return;
}

void game::SUB_01C91C() {
    a = myMapper->readCPU(0x00F5);
    opAND(0x30);
    if (!flgZ) {
        pushAddress(0xC924);
        jump(0xC95D);
        if (handleReturnAddress(poppedEntry.value, 0xC924)) return;
        x = myMapper->readCPU(0x0018);
        if (x != 0x01) {
            goto L_01C935;
        }
        opAND(0x20);
        if (!flgZ) {
            goto L_01C934;
        }
        a = 0x03;
        jump(0xC37A);
        return;
    }
L_01C934:
    popAddress();
    return;
L_01C935:
    x = 0x00;
    myMapper->writeCPU(0x0018, x);
    a = 0x0B;
    opAND(myMapper->readCPU(0x001C));
    myMapper->writeCPU(0x001C, a);
    a = 0x00;
    myMapper->writeCPU(0x00FD, a);
    myMapper->writeCPU(0x00FC, a);
    myMapper->writeCPU(0x00F4, a);
    pushAddress(0xC949);
    jump(0xFD23);
    if (handleReturnAddress(poppedEntry.value, 0xC949)) return;
    pushAddress(0xC94C);
    jump(0xAE8C);
    if (handleReturnAddress(poppedEntry.value, 0xC94C)) return;
    myMapper->writeCPU(0x00FE, 0x1E);
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    myMapper->writeCPU(0x00FF, a);
    pushAddress(0xC959);
    jump(0xB9FC);
    if (handleReturnAddress(poppedEntry.value, 0xC959)) return;
    jump(0xC371);
    return;
}

void game::SUB_01C95D() {
    x = 0x00;
    myMapper->writeCPU(0x0025, x);
    opINX(1);
    myMapper->writeCPU(0x0026, x);
    popAddress();
}

void game::SUB_01C994() {
    myMapper->writeCPU(0x005B, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x007D, a);
    myMapper->writeCPU(0x003B, a);
    myMapper->writeCPU(0x0048, a);
    myMapper->writeCPU(0x002D, a);
    myMapper->writeCPU(0x046C, a);
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x0047, a);
    myMapper->writeCPU(0x003E, a);
    opINC(0x003E, 1);
    myMapper->writeCPU(0x003C, 0x04);
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0xCA0C + x);
    opAND(0xF8);
    myMapper->writeCPU(0x0354, a);
    myMapper->writeCPU(0x003F, a);
    a = myMapper->readCPU(0xCA0C + x);
    opAND(0x07);
    myMapper->writeCPU(0x002F, a);
    opINX(1);
    a = myMapper->readCPU(0xCA0C + x);
    opAND(0xFE);
    myMapper->writeCPU(0x038C, a);
    opROL_A(2);
    opAND(0x01);
    myMapper->writeCPU(0x0450, a);
    a = myMapper->readCPU(0xCA0C + x);
    opAND(0x01);
    myMapper->writeCPU(0x0046, a);
    a = 0x00;
    myMapper->writeCPU(0x0041, a);
    myMapper->writeCPU(0x002E, a);
    x = myMapper->readCPU(0x038C);
    pushAddress(0xC9E9);

    if (handleReturnAddress(poppedEntry.value, 0xC9E9)) return;
    SUB_01CA6D();
    return;
}

void game::SUB_01CA6D() {
    opASL_A(1);
    myMapper->writeCPU(0x0003, x);
    myMapper->writeCPU(0x0002, y);
    y = a;
    opINY(1);
    opPLA();
    myMapper->writeCPU(0x0000, a);
    opPLA();
    myMapper->writeCPU(0x0001, a);
    x = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0001, a);
    myMapper->writeCPU(0x0000, x);
    y = myMapper->readCPU(0x0002);
    x = myMapper->readCPU(0x0003);
    jump(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8));
}

void game::SUB_01CA8B() {
    flgC = false;
    opADC(myMapper->readCPU((0x0000 + x) & 0x00ff));
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (!flgC) {
        goto L_01CA94;
    }
    opINC((0x0001 + x) & 0x00ff, 1);
L_01CA94:
    popAddress();
}

void game::SUB_01CAAF() {
    a = myMapper->readCPU(0x00F4);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    x = 0xFC;
    a = myMapper->readCPU(0x001C);
    opROL_A(2);
    opAND(0x01);
    myMapper->writeCPU(0x0010, a);
    if (a == 0) {
        goto L_01CAC3;
    }
    x = 0xFC;
L_01CAC3:
    myMapper->writeCPU(0x0004, x);
    myMapper->writeCPU(0x0005, 0x07);
    x = 0x01;
    y = 0x00;
    myMapper->writeCPU(0x0000, 0x03);
    flgC = false;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        pushAddress(0xCAD7);
        jump(0xCAE7);
        if (handleReturnAddress(poppedEntry.value, 0xCAD7)) return;
        myMapper->writeCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opINX(1);
        opDEC(0x0000, 1);
    } while (!flgZ);
    if (!flgC) {
        jump(0xCB11);
        return;
    }
    popAddress();
}

void game::SUB_01CAE3() {
    myMapper->writeCPU(0x0000, x);
    x = 0x00;
    SUB_01CAE7();
    return;
}

void game::SUB_01CAE7() {
    myMapper->writeCPU(0x0007, a);
    opAND(0xF0);
    myMapper->writeCPU(0x0006, a);
    opEOR(myMapper->readCPU(0x0007));
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU((0x0000 + x) & 0x00ff);
    opAND(0x0F);
    opADC(myMapper->readCPU(0x0007));
    opCMP(a, 0x0A);
    if (flgC) {
        opADC(0x05);
    }
    opADC(myMapper->readCPU(0x0006));
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU((0x0000 + x) & 0x00ff);
    opAND(0xF0);
    opADC(myMapper->readCPU(0x0006));
    if (flgC) {
        goto L_01CB0D;
    }
    opCMP(a, 0xA0);
    if (!flgC) {
        goto L_01CB10;
    }
L_01CB0D:
    opSBC(0xA0);
    flgC = true;
L_01CB10:
    popAddress();
}

void game::SUB_01CB11() {
    y = 0x02;
    a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
    x = myMapper->readCPU(0x0010);
    opCMP(a, myMapper->readCPU((0x002C + x) & 0x00ff));
    if (flgC) {
        x = 0x05;
        y = myMapper->readCPU(0x0010);
        a = myMapper->readCPU(0x002C + y);
        flgC = false;
        pushAddress(0xCB25);
        jump(0xCAE3);
        if (handleReturnAddress(poppedEntry.value, 0xCB25)) return;
        if (!flgC) {
            goto L_01CB2A;
        }
        a = 0xFF;
    L_01CB2A:
        x = myMapper->readCPU(0x0010);
        myMapper->writeCPU((0x002C + x) & 0x00ff, a);
        opINC((0x002A + x) & 0x00ff, 1);
        pushAddress(0xCB32);
        jump(0xCC3D);
        if (handleReturnAddress(poppedEntry.value, 0xCB32)) return;
        a = 0x25;
        pushAddress(0xCB37);
        jump(0xC1A7);
        if (handleReturnAddress(poppedEntry.value, 0xCB37)) return;
    }
    popAddress();
}

void game::SUB_01CC3D() {
    a = myMapper->readCPU(0x002A);
    setLoadFlag(a);
    myMapper->writeCPU(0x004B, a);
    if (!flgZ) {
        opDEC(0x004B, 1);
    }
    a = 0x63;
    opCMP(a, myMapper->readCPU(0x004B));
    if (!flgC) {
        goto L_01CC4D;
    }
    a = myMapper->readCPU(0x004B);
L_01CC4D:
    pushAddress(0xCC4F);
    jump(0xA333);
    if (handleReturnAddress(poppedEntry.value, 0xCC4F)) return;
    myMapper->writeCPU(0x0008, a);
    a = 0x18;
    pushAddress(0xCC56);
    jump(0xCC95);
    if (handleReturnAddress(poppedEntry.value, 0xCC56)) return;
    a = myMapper->readCPU(0x0008);
    pushAddress(0xCC5B);
    jump(0xCC68);
    if (handleReturnAddress(poppedEntry.value, 0xCC5B)) return;
    jump(0xCC5F);
    return;
}

void game::SUB_01CC5F() {
    a = 0xFF;
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    myMapper->writeCPU(0x0020, x);
    popAddress();
}

void game::SUB_01CC68() {
    myMapper->writeCPU(0x0000, a);
    opLSR_A(4);
    pushAddress(0xCC70);
    jump(0xCC75);
    if (handleReturnAddress(poppedEntry.value, 0xCC70)) return;
    a = myMapper->readCPU(0x0000);
    opAND(0x0F);
    SUB_01CC75();
    return;
}

void game::SUB_01CC75() {
    opORA(0xD0);
    pushAddress(0xCC79);

    if (handleReturnAddress(poppedEntry.value, 0xCC79)) return;
    SUB_01CC95();
    return;
}

void game::SUB_01CC95() {
    opPHA();
    myMapper->writeCPU(0x0003, 0x02);
    a = 0x01;
    pushAddress(0xCC9E);
    jump(0xCCF0);
    if (handleReturnAddress(poppedEntry.value, 0xCC9E)) return;
    opPLA();
    myMapper->writeCPU(0x0002, a);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0000, myMapper->readCPU(0xCCF9 + x));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0xCCFA + x));
    x = myMapper->readCPU(0x0020);
    y = 0x00;
    do {
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opCMP(a, 0xFF);
            if (flgZ) {
                jump(0xCCF6);
                return;
            }
            opCMP(a, 0xFE);
            if (flgZ) {
                goto L_01CCD6;
            }
            opCMP(a, 0xFD);
            if (flgZ) {
                goto L_01CCDA;
            }
            myMapper->writeCPU(0x0700 + x, a);
            if (myMapper->readCPU(0x0002) & 0x80) {
                a = myMapper->readCPU(0x0003);
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_01CCD1;
                }
                myMapper->writeCPU(0x0700 + x, a);
                if (flgZ) {
                    goto L_01CCD3;
                }
            L_01CCD1:
                opDEC(0x0003, 1);
            }
        L_01CCD3:
            opINX(1);
        } while (!flgZ);
    L_01CCD6:
        a = 0xFF;
        setLoadFlag(a);
        if (!flgZ) {
            jump(0xCCF2);
            return;
        }
    L_01CCDA:
        a = 0xFF;
        pushAddress(0xCCDE);
        jump(0xCCF2);
        if (handleReturnAddress(poppedEntry.value, 0xCCDE)) return;
        myMapper->writeCPU(0x0003, 0x02);
        a = 0x01;
        pushAddress(0xCCE7);
        jump(0xCCF2);
        if (handleReturnAddress(poppedEntry.value, 0xCCE7)) return;
    } while (!flgZ);
    a = 0xFF;
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xCCF0);
        return;
    }
    SUB_01CCEE();
    return;
}

void game::SUB_01CCEE() {
    a = 0x00;
    SUB_01CCF0();
    return;
}

void game::SUB_01CCF0() {
    x = myMapper->readCPU(0x0020);
    SUB_01CCF2();
    return;
}

void game::SUB_01CCF2() {
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    SUB_01CCF6();
    return;
}

void game::SUB_01CCF6() {
    myMapper->writeCPU(0x0020, x);
    popAddress();
}

void game::SUB_01CFBD() {
    pushAddress(0xCFBF);
    jump(0xCFF9);
    if (handleReturnAddress(poppedEntry.value, 0xCFBF)) return;
    pushAddress(0xCFC2);
    jump(0xF912);
    if (handleReturnAddress(poppedEntry.value, 0xCFC2)) return;
    opEOR(myMapper->readCPU(0x002F));
    y = 0x24;
    opAND(0x01);
    if (flgZ) {
        goto L_01CFCD;
    }
    y = 0x20;
L_01CFCD:
    myMapper->writeCPU(0x0038, y);
    myMapper->writeCPU(0x003A, y);
    pushAddress(0xCFD3);
    jump(0xF817);
    if (handleReturnAddress(poppedEntry.value, 0xCFD3)) return;
    a = 0x00;
    myMapper->writeCPU(0x0030, a);
    myMapper->writeCPU(0x0031, a);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x002E));
    a = myMapper->readCPU(0x002F);
    opLSR_A(1);
    opROR_M(0x0000, 1);
    opLSR_A(1);
    opROR_M(0x0000, 1);
    opLSR_A(1);
    opROR_M(0x0000, 1);
    opLSR_A(1);
    opROR_M(0x0000, 1);
    opLSR_A(1);
    opROR_M(0x0000, 1);
    a = myMapper->readCPU(0x0000);
    myMapper->writeCPU(0x0036, a);
    flgC = false;
    opADC(0x0F);
    myMapper->writeCPU(0x0035, a);
    popAddress();
}

void game::SUB_01CFF9() {
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0000, myMapper->readCPU(0xFB23 + x));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0xFB24 + x));
    a = myMapper->readCPU(0x0046);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0033, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0034, a);
    popAddress();
}

void game::SUB_01D10E() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFB9B + x);
    pushAddress(0xD115);
    jump(0xCC95);
    if (handleReturnAddress(poppedEntry.value, 0xD115)) return;
    a = 0x05;
    jump(0xCC95);
    return;
}

void game::SUB_01D132() {
    myMapper->writeCPU(0x006D, myMapper->readCPU(0x002F));
    a = myMapper->readCPU(0x002E);
    opASL_A(1);
    opROL_M(0x006D, 1);
    opASL_A(1);
    opROL_M(0x006D, 1);
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x000A, myMapper->readCPU(0xD290 + y));
    myMapper->writeCPU(0x000B, myMapper->readCPU(0xD291 + y));
    x = 0xF0;
    a = myMapper->readCPU(0x0046);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01D154;
    }
    x = 0x0F;
L_01D154:
    myMapper->writeCPU(0x000D, x);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0008, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0009, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
    popAddress();
}

void game::SUB_01D162() {
    pushAddress(0xD164);
    jump(0xD132);
    if (handleReturnAddress(poppedEntry.value, 0xD164)) return;
    myMapper->writeCPU(0x000C, 0x06);
    a = myMapper->readCPU(0x002E);
    opAND(0x3F);
    myMapper->writeCPU(0x004B, a);
    a = 0xC0;
    flgC = true;
    opSBC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x004C, a);
    a = 0x01;
    myMapper->writeCPU(0x004D, a);
    while (true) {
        pushAddress(0xD17C);
        jump(0xD1BE);
        if (handleReturnAddress(poppedEntry.value, 0xD17C)) return;
        opINC(0x006D, 1);
        a = myMapper->readCPU(0x004C);
        flgC = false;
        opADC(0x40);
        myMapper->writeCPU(0x004C, a);
        a = myMapper->readCPU(0x004D);
        opADC(0x00);
        opAND(0x01);
        myMapper->writeCPU(0x004D, a);
        opDEC(0x000C, 1);
        if (flgZ) {
            jump(0xD195);
            return;
        }
    }
    SUB_01D195();
    return;
}

void game::SUB_01D195() {
    popAddress();
}

void game::SUB_01D196() {
    pushAddress(0xD198);
    jump(0xD132);
    if (handleReturnAddress(poppedEntry.value, 0xD198)) return;
    a = myMapper->readCPU(0x006D);
    if (a == myMapper->readCPU(0x0076)) {
        jump(0xD195);
        return;
    }
    myMapper->writeCPU(0x0076, a);
    a = 0x00;
    y = 0xC0;
    if (myMapper->readCPU(0x003C) != 0x01) {
        goto L_01D1AF;
    }
    a = 0x05;
    y = 0x00;
L_01D1AF:
    myMapper->writeCPU(0x004C, y);
    myMapper->writeCPU(0x004B, a);
    a = myMapper->readCPU(0x006D);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x006D, a);
    myMapper->writeCPU(0x004D, 0x01);
    SUB_01D1BE();
    return;
}

void game::SUB_01D1BE() {
    a = myMapper->readCPU(0x006D);
    do {
        opCMP(a, 0x06);
        if (!flgC) {
            goto L_01D1C8;
        }
        opSBC(0x06);
    } while (!flgZ);
L_01D1C8:
    x = a;
    a = myMapper->readCPU(0x006D);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x004F, y);
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x000A, myMapper->readCPU(0xD6C6 + y));
    myMapper->writeCPU(0x000B, myMapper->readCPU(0xD6C7 + y));
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0166 + x, a);
    if (flgZ) {
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0160 + x, a);
        if (!flgZ) {
            goto L_01D20F;
        }
    }
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(myMapper->readCPU(0x004C));
    myMapper->writeCPU(0x0172 + x, a);
    opINY(1);
    myMapper->writeCPU(0x017E + x, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0160 + x, myMapper->readCPU(0x004D));
    a = 0x00;
    myMapper->writeCPU(0x0178 + x, a);
    myMapper->writeCPU(0x016C + x, a);
    myMapper->writeCPU(0x0184 + x, a);
    myMapper->writeCPU(0x018A + x, a);
L_01D20F:
    a = x;
    flgC = false;
    opADC(0x0E);
    x = a;
    y = myMapper->readCPU(0x004F);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    opASL_A(1);
    if (!flgC) {
        y = a;
        myMapper->writeCPU(0x000A, myMapper->readCPU(0xD6C6 + y));
        a = myMapper->readCPU(0xD6C7 + y);
        myMapper->writeCPU(0x000B, a);
    }
    else {
        y = a;
        myMapper->writeCPU(0x000A, myMapper->readCPU(0xD7C6 + y));
        myMapper->writeCPU(0x000B, myMapper->readCPU(0xD7C7 + y));
    }
    myMapper->writeCPU(0x000E, 0x00);
    y = myMapper->readCPU(0x006D);
    a = myMapper->readCPU(0x0190 + y);
    y = 0x00;
    opAND(myMapper->readCPU(0x000D));
    if (flgZ) {
        a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (!flgZ) {
            if (a != 0xFF) {
                goto L_01D254;
            }
            opINY(1);
            myMapper->writeCPU(0x000E, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
        L_01D254:
            if (a != 0xFE) {
                goto L_01D25D;
            }
            opINY(1);
            a = 0x28;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_01D25F;
            }
        L_01D25D:
            a = 0x27;
        L_01D25F:
            pushAddress(0xD261);
            jump(0xEF04);
            if (handleReturnAddress(poppedEntry.value, 0xD261)) return;
            a = 0x28;
            pushAddress(0xD266);
            jump(0xF42C);
            if (handleReturnAddress(poppedEntry.value, 0xD266)) return;
            myMapper->writeCPU(0x0584 + x, myMapper->readCPU(0x000E));
            a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
            flgC = false;
            opADC(myMapper->readCPU(0x004C));
            myMapper->writeCPU(0x038C + x, a);
            opINY(1);
            myMapper->writeCPU(0x0354 + x, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x0300 + x, myMapper->readCPU(0x004D));
            a = myMapper->readCPU(0x006D);
            myMapper->writeCPU(0x04DC + x, a);
            popAddress();
            return;
        }
    }
    myMapper->writeCPU(0x0434 + x, 0x00);
    a = 0x01;
    myMapper->writeCPU(0x0300 + x, a);
    popAddress();
}

void game::SUB_01DC50() {
    y = 0x00;
    a = 0x02;
    pushAddress(0xDC56);
    jump(0xEC72);
    if (handleReturnAddress(poppedEntry.value, 0xDC56)) return;
    a = 0x04;
    jump(0xF131);
    return;
}

void game::SUB_01DEDC() {
    x = 0x04;
    do {
        a = myMapper->readCPU(0x0434 + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == 0x25) {
                goto L_01DEF3;
            }
            if (a < 0x17) {
                goto L_01DEF9;
            }
            if (a < 0x20) {
                goto L_01DEF3;
            }
            if (a < 0x28) {
                goto L_01DEF9;
            }
        }
    L_01DEF3:
        opINX(1);
        opCMP(x, 0x0E);
    } while (!flgC);
    popAddress();
    return;
L_01DEF9:
    a = 0x30;
    myMapper->writeCPU(0x0434 + x, a);
    pushAddress(0xDF00);
    jump(0xE3F4);
    if (handleReturnAddress(poppedEntry.value, 0xDF00)) return;
    goto L_01DEF3;
}

void game::SUB_01DF06() {
    myMapper->writeCPU(0x004E, x);
    y = myMapper->readCPU(0x0434 + x);
    a = myMapper->readCPU(0xDF2A + y);
    SUB_01DF0E();
    return;
}

void game::SUB_01DF0E() {
    myMapper->writeCPU(0x004B, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    y = a;
    myMapper->writeCPU(0x0003, myMapper->readCPU(0xDF52 + y));
    myMapper->writeCPU(0x0002, myMapper->readCPU(0xDF53 + y));
    a = myMapper->readCPU(0xDF54 + y);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0xDF26);
    jump(0xFD18);
    if (handleReturnAddress(poppedEntry.value, 0xDF26)) return;
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01DF79() {
    y = myMapper->readCPU(0x0434 + x);
    a = myMapper->readCPU(0xDFF4 + y);
    myMapper->writeCPU(0x0008, a);
    opAND(0x0F);
    opLSR_A(1);
    y = a;
    a = myMapper->readCPU(0x0354 + x);
    flgC = true;
    do {
        opSBC(0x08);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0009, a);
    a = myMapper->readCPU(0x0008);
    opAND(0xF0);
    opLSR_A(5);
    y = a;
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    do {
        opSBC(0x08);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x000A, a);
    a = myMapper->readCPU(0x0008);
    opAND(0x0F);
    y = a;
    opDEY(1);
    a = myMapper->readCPU(0x0009);
    do {
        flgC = false;
        opADC(0x08);
        if (a >= myMapper->readCPU(0x0069)) {
            goto L_01DFBA;
        }
        myMapper->writeCPU(0x0009, a);
        opDEY(1);
    } while (!flgZ);
L_01DFBA:
    myMapper->writeCPU(0x0357, myMapper->readCPU(0x0009));
    a = myMapper->readCPU(0x0008);
    opAND(0xF0);
    opLSR_A(4);
    y = a;
    opDEY(1);
    a = myMapper->readCPU(0x000A);
    do {
        flgC = false;
        opADC(0x08);
        if (a >= myMapper->readCPU(0x0068)) {
            goto L_01DFD7;
        }
        myMapper->writeCPU(0x000A, a);
        opDEY(1);
    } while (!flgZ);
L_01DFD7:
    myMapper->writeCPU(0x038F, myMapper->readCPU(0x000A));
    myMapper->writeCPU(0x0437, 0x30);
    myMapper->writeCPU(0x056B, 0x10);
    myMapper->writeCPU(0x04C3, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x04A7, a);
    myMapper->writeCPU(0x048B, a);
    popAddress();
}

void game::SUB_01E09A() {
    pushAddress(0xE09C);
    jump(0xE3F4);
    if (handleReturnAddress(poppedEntry.value, 0xE09C)) return;
    pushAddress(0xE09F);
    jump(0xDF06);
    if (handleReturnAddress(poppedEntry.value, 0xE09F)) return;
    y = myMapper->readCPU(0x0434 + x);
    if (y != 0x0B) {
        if (y < 0x20) {
            goto L_01E0AF;
        }
        if (y < 0x28) {
            goto L_01E0B7;
        }
    L_01E0AF:
        a = myMapper->readCPU(0x001A);
        opAND(0x0F);
        if (a == 0x02) {
            jump(0xE109);
            return;
        }
    }
L_01E0B7:
    a = 0x00;
    opCMP(y, 0x03);
    if (!flgZ) {
        opCMP(y, 0x08);
        if (!flgZ) {
            opCMP(y, 0x0A);
            if (flgZ) {
                jump(0xE0E9);
                return;
            }
            opCMP(y, 0x0C);
            if (!flgZ) {
                opCMP(y, 0x0E);
                if (flgZ) {
                    goto L_01E0D5;
                }
                opCMP(y, 0x13);
                if (flgZ) {
                    jump(0xE0E9);
                    return;
                }
                opCMP(y, 0x12);
                if (!flgZ) {
                    goto L_01E0D7;
                }
            }
        }
    }
L_01E0D5:
    a = 0x04;
L_01E0D7:
    myMapper->writeCPU(0x0584 + x, a);
    y = 0x30;
    a = myMapper->readCPU(0x001A);
    opAND(0x07);
    if (!flgZ) {
        jump(0xE0E4);
        return;
    }
    SUB_01E0E2();
    return;
}

void game::SUB_01E0E2() {
    y = 0x31;
    SUB_01E0E4();
    return;
}

void game::SUB_01E0E4() {
    a = y;
    myMapper->writeCPU(0x0434 + x, a);
    popAddress();
}

void game::SUB_01E0E9() {
    myMapper->writeCPU(0x0584 + x, 0x04);
    a = 0x31;
    myMapper->writeCPU(0x0434 + x, a);
    popAddress();
}

void game::SUB_01E0F4() {
    y = 0x00;
    a = myMapper->readCPU(0x0028);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01E107;
    }
    flgC = true;
    opSBC(0x01);
    do {
        if (a < 0x03) {
            goto L_01E107;
        }
        flgC = true;
        opSBC(0x03);
        opINY(1);
    } while (!flgZ);
L_01E107:
    a = y;
    popAddress();
}

void game::SUB_01E109() {
    do {
        opINC(0x007B, 1);
        pushAddress(0xE10D);
        jump(0xE0F4);
        if (handleReturnAddress(poppedEntry.value, 0xE10D)) return;
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x004C, myMapper->readCPU(0xE12C + y));
        myMapper->writeCPU(0x004D, myMapper->readCPU(0xE12D + y));
        a = myMapper->readCPU(0x007B);
        opAND(0x03);
        y = a;
        a = myMapper->readCPU(myMapper->readCPU(0x004C) + (myMapper->readCPU((0x004C + 1) & 0x00ff) << 8) + y);
        opCMP(a, myMapper->readCPU(0x015B));
    } while (flgZ);
    myMapper->writeCPU(0x0584 + x, a);
    jump(0xE0E2);
    return;
}

void game::SUB_01E3F4() {
    myMapper->writeCPU(0x0568 + x, 0x14);
    a = 0x26;
    pushAddress(0xE3FD);
    jump(0xEF04);
    if (handleReturnAddress(poppedEntry.value, 0xE3FD)) return;
    popAddress();
}

void game::SUB_01E3FF() {
    a = myMapper->readCPU(0x0434);
    setLoadFlag(a);
    if (!flgZ) {
        if (flgN) {
            goto L_01E44B;
        }
        if (myMapper->readCPU(0x0568) == 0x11) {
            a = myMapper->readCPU(0x0434);
            opAND(0x7F);
            y = a;
            a = myMapper->readCPU(0xE460 + y);
            flgC = false;
            opADC(myMapper->readCPU(0x0354));
            myMapper->writeCPU(0x0069, a);
            y = myMapper->readCPU(0x0070);
            a = myMapper->readCPU(0x038C);
            x = myMapper->readCPU(0x0450);
            setLoadFlag(x);
            if (!flgZ) {
                flgC = true;
                opSBC(myMapper->readCPU(0xE45D + y));
                if (flgC) {
                    goto L_01E438;
                }
                a = 0x00;
                setLoadFlag(a);
                if (flgZ) {
                    goto L_01E438;
                }
            }
            flgC = false;
            opADC(myMapper->readCPU(0xE45D + y));
            if (flgC) {
                a = 0xFF;
            }
        L_01E438:
            myMapper->writeCPU(0x0068, a);
            a = y;
            opASL_A(1);
            y = a;
            myMapper->writeCPU(0x0073, myMapper->readCPU(0xE464 + y));
            myMapper->writeCPU(0x0074, myMapper->readCPU(0xE465 + y));
            a = 0x00;
            setLoadFlag(a);
            if (flgZ) {
                goto L_01E44D;
            }
        }
    }
L_01E44B:
    a = 0xFF;
L_01E44D:
    myMapper->writeCPU(0x005C, a);
    a = 0x0C;
    y = myMapper->readCPU(0x046C);
    if (y != 0x03) {
        goto L_01E45A;
    }
    a = 0x0A;
L_01E45A:
    myMapper->writeCPU(0x005F, a);
    popAddress();
}

void game::SUB_01E4CC() {
    a = 0x14;
    pushAddress(0xE4D0);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xE4D0)) return;
    y = 0x05;
    pushAddress(0xE4D5);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xE4D5)) return;
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01E4D9() {
    myMapper->writeCPU(0x004E, x);
    a = myMapper->readCPU(0x046C + x);
    setLoadFlag(a);
    if (!flgN) {
        if (myMapper->readCPU(0x0300 + x) == 0) {
            goto L_01E4EF;
        }
        a = myMapper->readCPU(0x0434 + x);
        opCMP(a, 0x04);
        if (!flgZ) {
            goto L_01E502;
        }
    L_01E4EF:
        a = myMapper->readCPU(0x0434 + x);
        opCMP(a, 0x17);
        if (!flgZ) {
            opCMP(a, 0x21);
            if (!flgZ) {
                opCMP(a, 0x25);
                if (!flgZ) {
                    opCMP(a, 0x30);
                    if (!flgC) {
                        goto L_01E503;
                    }
                }
            }
        }
    }
L_01E502:
    popAddress();
    return;
L_01E503:
    if (a == 0x2F) {
    }
    else {
        a = myMapper->readCPU(0x005C);
        setLoadFlag(a);
        if (!flgZ) {
        L_01E50E:
            goto L_01E5EB;
        }
        a = myMapper->readCPU(0x0434 + x);
        if (a == 0x1D) {
            if (myMapper->readCPU(0x007A) == 0) {
                goto L_01E51E;
            }
            a = 0x30;
        }
    L_01E51E:
        opASL_A(1);
        y = a;
        a = myMapper->readCPU(0xE46A + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0073));
        myMapper->writeCPU(0x004C, a);
        a = myMapper->readCPU(0xE46B + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0074));
        myMapper->writeCPU(0x004D, a);
        a = myMapper->readCPU(0x038C + x);
        flgC = true;
        opSBC(myMapper->readCPU(0x0068));
        if (!flgC) {
            opEOR(0xFF);
            opADC(0x01);
        }
        if (a >= myMapper->readCPU(0x004C)) {
            goto L_01E50E;
        }
        a = myMapper->readCPU(0x0354 + x);
        flgC = true;
        opSBC(myMapper->readCPU(0x0069));
        if (!flgC) {
            opEOR(0xFF);
            opADC(0x01);
        }
        if (a >= myMapper->readCPU(0x004D)) {
            goto L_01E50E;
        }
        a = myMapper->readCPU(0x0070);
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x000D, myMapper->readCPU(0xE5D9 + y));
        myMapper->writeCPU(0x000C, myMapper->readCPU(0xE5DA + y));
        myMapper->writeCPU(0x000E, 0xFF);
        while (true) {
            a = myMapper->readCPU(0x0434 + x);
            if (a != 0x1D) {
                opCMP(a, 0x0E);
                if (!flgZ) {
                    pushAddress(0xE56F);
                    jump(0xE4CC);
                    if (handleReturnAddress(poppedEntry.value, 0xE56F)) return;
                }
                pushAddress(0xE572);
                jump(0xDF79);
                if (handleReturnAddress(poppedEntry.value, 0xE572)) return;
            }
        L_01E573:
            a = myMapper->readCPU(0x0434 + x);
            pushAddress(0xE578);
            jump(0xCA6D);
            if (handleReturnAddress(poppedEntry.value, 0xE578)) return;
            //NOP
        L_01E5EB:
            y = 0x14;
            do {
                a = myMapper->readCPU(0x0434 + y);
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_01E5FA;
                }
            L_01E5F2:
                opINY(1);
            } while (y < 0x17);
            goto L_01E6BA;
        L_01E5FA:
            a = myMapper->readCPU(0x0584 + y);
            if (a >= 0x06) {
                goto L_01E5F2;
            }
            a = x;
            if (a == myMapper->readCPU(0x04DC + y)) {
                goto L_01E5F2;
            }
            myMapper->writeCPU(0x000F, y);
            a = myMapper->readCPU(0x0434 + x);
            if (a == 0x1D) {
                if (myMapper->readCPU(0x007A) == 0) {
                    goto L_01E616;
                }
                a = 0x30;
            }
        L_01E616:
            opASL_A(1);
            y = a;
            myMapper->writeCPU(0x004C, myMapper->readCPU(0xE46A + y));
            myMapper->writeCPU(0x004D, myMapper->readCPU(0xE46B + y));
            y = myMapper->readCPU(0x000F);
            a = myMapper->readCPU(0x0584 + y);
            opASL_A(1);
            y = a;
            a = myMapper->readCPU(0xE5DF + y);
            flgC = false;
            opADC(myMapper->readCPU(0x004C));
            myMapper->writeCPU(0x004C, a);
            a = myMapper->readCPU(0xE5E0 + y);
            flgC = false;
            opADC(myMapper->readCPU(0x004D));
            myMapper->writeCPU(0x004D, a);
            y = myMapper->readCPU(0x000F);
            a = myMapper->readCPU(0x038C + y);
            flgC = true;
            opSBC(myMapper->readCPU(0x038C + x));
            if (!flgC) {
                opEOR(0xFF);
                opADC(0x01);
            }
            if (a >= myMapper->readCPU(0x004C)) {
                goto L_01E5F2;
            }
            a = myMapper->readCPU(0x0354 + y);
            flgC = true;
            opSBC(myMapper->readCPU(0x0354 + x));
            if (!flgC) {
                opEOR(0xFF);
                opADC(0x01);
            }
            if (a >= myMapper->readCPU(0x004D)) {
                goto L_01E5F2;
            }
            opINC(0x0079, 1);
            a = myMapper->readCPU(0x0584 + y);
            setLoadFlag(a);
            if (flgZ) {
                myMapper->writeCPU(0x0434 + y, 0x32);
                a = 0x00;
                setLoadFlag(a);
                if (flgZ) {
                    goto L_01E683;
                }
            }
            if (a != 0x01) {
                if (a != 0x05) {
                    goto L_01E683;
                }
            }
            a = myMapper->readCPU(0x0434 + x);
            if (a == 0x1D) {
                goto L_01E683;
            }
            myMapper->writeCPU(0x04DC + y, x);
            a = myMapper->readCPU(0x0584 + y);
        L_01E683:
            myMapper->writeCPU(0x004B, a);
            opASL_A(1);
            flgC = false;
            opADC(myMapper->readCPU(0x004B));
            y = a;
            myMapper->writeCPU(0x000D, myMapper->readCPU(0xE6A8 + y));
            myMapper->writeCPU(0x000C, myMapper->readCPU(0xE6A9 + y));
            myMapper->writeCPU(0x000E, myMapper->readCPU(0xE6AA + y));
            y = myMapper->readCPU(0x000F);
            a = myMapper->readCPU(0x0584 + y);
            if (a == 0x03) {
                goto L_01E6A5;
            }
        }
    L_01E6A5:
        goto L_01E573;
    }
L_01E6BA:
    a = myMapper->readCPU(0x046C);
    opCMP(a, 0x05);
    if (!flgZ) {
        opCMP(a, 0x08);
        if (!flgZ) {
            y = 0x00;
            a = myMapper->readCPU(0x0434 + x);
            opCMP(a, 0x2F);
            if (flgZ) {
                goto L_01E75E;
            }
            a = myMapper->readCPU(0x005B);
            setLoadFlag(a);
            if (flgZ) {
                goto L_01E6D7;
            }
        }
    }
    do {
        popAddress();
        return;
    L_01E6D7:
        a = myMapper->readCPU(0x0434 + x);
        opCMP(a, 0x28);
    } while (flgC);
    while (true) {
        myMapper->writeCPU(0x0008, y);
        if (a == 0x1D) {
            if (myMapper->readCPU(0x007A) == 0) {
                goto L_01E6EA;
            }
            a = 0x30;
        }
    L_01E6EA:
        opASL_A(1);
        y = a;
        a = myMapper->readCPU(0xE46A + y);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x004C, a);
        a = myMapper->readCPU(0xE46B + y);
        flgC = false;
        opADC(myMapper->readCPU(0x005F));
        myMapper->writeCPU(0x004D, a);
        pushAddress(0xE6FE);
        jump(0xEF84);
        if (handleReturnAddress(poppedEntry.value, 0xE6FE)) return;
        opCMP(a, myMapper->readCPU(0x004C));
        if (!flgC) {
            a = myMapper->readCPU(0x0354);
            flgC = true;
            opSBC(myMapper->readCPU(0x0354 + x));
            if (!flgC) {
                opEOR(0xFF);
                opADC(0x01);
            }
            opCMP(a, myMapper->readCPU(0x004D));
            if (!flgC) {
                if (myMapper->readCPU(0x0008) != 0) {
                    goto L_01E762;
                }
                a = myMapper->readCPU(0x0434 + x);
                if (a != 0x02) {
                    if (a == 0x07) {
                        goto L_01E731;
                    }
                    if (a != 0x0F) {
                        opCMP(a, 0x1B);
                        if (!flgZ) {
                            goto L_01E734;
                        }
                        pushAddress(0xE72D);
                        jump(0xEAA9);
                        if (handleReturnAddress(poppedEntry.value, 0xE72D)) return;
                        goto L_01E734;
                    }
                }
            L_01E731:
                pushAddress(0xEC74);
                jump(0xE09A);
                if (handleReturnAddress(poppedEntry.value, 0xEC74)) return;
            L_01E734:
                pushAddress(0xE736);
                jump(0xFE96);
                if (handleReturnAddress(poppedEntry.value, 0xE736)) return;
                x = myMapper->readCPU(0x004E);
                pushAddress(0xE73B);
                jump(0xFC97);
                if (handleReturnAddress(poppedEntry.value, 0xE73B)) return;
                x = myMapper->readCPU(0x004E);
                a = 0x10;
                y = myMapper->readCPU(0x002B);
                setLoadFlag(y);
                if (flgZ) {
                    y = myMapper->readCPU(0x0028);
                    opCMP(y, 0x0C);
                    if (!flgC) {
                        a = 0x0C;
                        opCMP(y, 0x07);
                        if (!flgC) {
                            a = 0x08;
                        }
                    }
                }
                myMapper->writeCPU(0x004B, a);
                a = myMapper->readCPU(0x0045);
                setLoadFlag(a);
                if (flgN) {
                    goto L_01E75D;
                }
                flgC = true;
                opSBC(myMapper->readCPU(0x004B));
                myMapper->writeCPU(0x0045, a);
            }
        }
    L_01E75D:
        popAddress();
        return;
    L_01E75E:
        opINY(1);
    }
L_01E762:
    a = myMapper->readCPU(0x0584 + x);
    opAND(0x0F);
    if (!flgZ) {
        goto L_01E786;
    }
    a = 0x16;
    pushAddress(0xE76D);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xE76D)) return;
    y = 0x05;
    pushAddress(0xE772);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xE772)) return;
    a = myMapper->readCPU(0x0071);
    flgC = false;
    opADC(0x01);
    while (true) {
        opCMP(a, 0x63);
        if (flgC) {
            a = 0x63;
        }
        myMapper->writeCPU(0x0071, a);
        pushAddress(0xE782);
        jump(0xFCD0);
        if (handleReturnAddress(poppedEntry.value, 0xE782)) return;
        goto L_01E7CE;
    L_01E786:
        if (a == 0x0C) {
            goto L_01E801;
        }
        opCMP(a, 0x0A);
        if (flgZ) {
            goto L_01E7EB;
        }
        opCMP(a, 0x0E);
        if (flgZ) {
            goto L_01E7D6;
        }
        y = a;
        opDEY(1);
        if (flgZ) {
            goto L_01E8A5;
        }
        opDEY(2);
        if (flgZ) {
            goto L_01E88E;
        }
        opDEY(1);
        if (flgZ) {
        }
        else {
            opDEY(1);
            if (!flgZ) {
                goto L_01E7AC;
            }
            goto L_01E874;
        L_01E7AC:
            opDEY(1);
            if (flgZ) {
                goto L_01E7D3;
            }
            a = 0x00;
            myMapper->writeCPU(0x0079, a);
            myMapper->writeCPU(0x0064, a);
            myMapper->writeCPU(0x0141, 0x80);
            myMapper->writeCPU(0x015B, myMapper->readCPU(0x0584 + x));
            myMapper->writeCPU(0x0072, 0x00);
            a = 0x18;
            pushAddress(0xE7C8);
            jump(0xC1A7);
            if (handleReturnAddress(poppedEntry.value, 0xE7C8)) return;
            y = 0x05;
            pushAddress(0xE7CD);
            jump(0xC1D6);
            if (handleReturnAddress(poppedEntry.value, 0xE7CD)) return;
            while (true) {
                while (true) {
                    while (true) {
                        while (true) {
                        L_01E7CE:
                            x = myMapper->readCPU(0x004E);
                            jump(0xEC60);
                            return;
                        L_01E7D3:
                            goto L_01E83A;
                        L_01E7D6:
                            myMapper->writeCPU(0x0072, 0x00);
                            a = 0x1B;
                            pushAddress(0xE7DE);
                            jump(0xC1A7);
                            if (handleReturnAddress(poppedEntry.value, 0xE7DE)) return;
                            y = 0x05;
                            pushAddress(0xE7E3);
                            jump(0xC1D6);
                            if (handleReturnAddress(poppedEntry.value, 0xE7E3)) return;
                            a = 0xB4;
                            myMapper->writeCPU(0x005B, a);
                        }
                    L_01E7EB:
                        a = 0x24;
                        pushAddress(0xE7EF);
                        jump(0xC1A7);
                        if (handleReturnAddress(poppedEntry.value, 0xE7EF)) return;
                        y = 0x05;
                        pushAddress(0xE7F4);
                        jump(0xC1D6);
                        if (handleReturnAddress(poppedEntry.value, 0xE7F4)) return;
                        myMapper->writeCPU(0x015D, 0x0F);
                        a = 0x00;
                        myMapper->writeCPU(0x0072, a);
                    }
                L_01E801:
                    a = myMapper->readCPU(0x015B);
                    if (a != 0x08) {
                        if (a == 0x09) {
                            goto L_01E81C;
                        }
                        if (a != 0x0B) {
                            opCMP(a, 0x0D);
                            if (!flgZ) {
                                a = 0x21;
                                myMapper->writeCPU(0x0584 + x, a);
                                goto L_01E8A5;
                            }
                        }
                    }
                L_01E81C:
                    y = 0x01;
                    opCMP(myMapper->readCPU(0x04C0 + x), 0x2F);
                    if (flgZ) {
                        goto L_01E826;
                    }
                    opINY(1);
                L_01E826:
                    myMapper->writeCPU(0x0064, y);
                    myMapper->writeCPU(0x0141, 0x80);
                    a = 0x18;
                    pushAddress(0xE831);
                    jump(0xC1A7);
                    if (handleReturnAddress(poppedEntry.value, 0xE831)) return;
                    y = 0x05;
                    pushAddress(0xE836);
                    jump(0xC1D6);
                    if (handleReturnAddress(poppedEntry.value, 0xE836)) return;
                }
            L_01E83A:
                opCMP(myMapper->readCPU(0x0028), 0x12);
                if (!flgZ) {
                    goto L_01E845;
                }
                a = 0x4B;
                goto L_01E847;
            L_01E845:
                a = 0x48;
            L_01E847:
                pushAddress(0xE849);
                jump(0xC1A7);
                if (handleReturnAddress(poppedEntry.value, 0xE849)) return;
                y = 0x05;
                pushAddress(0xE84E);
                jump(0xC1D6);
                if (handleReturnAddress(poppedEntry.value, 0xE84E)) return;
                myMapper->writeCPU(0x0045, 0x40);
                myMapper->writeCPU(0x0018, 0x0C);
                a = 0x00;
                myMapper->writeCPU(0x0019, a);
            }
        }
        a = 0x16;
        pushAddress(0xE862);
        jump(0xC1A7);
        if (handleReturnAddress(poppedEntry.value, 0xE862)) return;
        y = 0x05;
        pushAddress(0xE867);
        jump(0xC1D6);
        if (handleReturnAddress(poppedEntry.value, 0xE867)) return;
        myMapper->writeCPU(0x0072, 0x00);
        a = myMapper->readCPU(0x0071);
        flgC = false;
        opADC(0x05);
    }
L_01E874:
    a = 0x18;
    pushAddress(0xE878);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xE878)) return;
    y = 0x05;
    pushAddress(0xE87D);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xE87D)) return;
    a = myMapper->readCPU(0x0045);
    flgC = false;
    opADC(0x18);
    if (a < 0x40) {
        goto L_01E889;
    }
    a = 0x40;
L_01E889:
    myMapper->writeCPU(0x0045, a);
    goto L_01E7CE;
L_01E88E:
    a = 0x18;
    pushAddress(0xE892);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xE892)) return;
    y = 0x05;
    pushAddress(0xE897);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xE897)) return;
    myMapper->writeCPU(0x007E, 0x18);
    a = 0x00;
    myMapper->writeCPU(0x0072, a);
    opINC(0x0070, 1);
    goto L_01E7CE;
L_01E8A5:
    a = 0x17;
    pushAddress(0xE8A9);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xE8A9)) return;
    y = 0x05;
    pushAddress(0xE8AE);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xE8AE)) return;
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x0434 + x, 0x33);
    myMapper->writeCPU(0x0568 + x, 0x20);
    a = myMapper->readCPU(0x038C);
    opADC(0x10);
    myMapper->writeCPU(0x038C + x, a);
    myMapper->writeCPU(0x0354 + x, myMapper->readCPU(0x0354));
    a = myMapper->readCPU(0x0584 + x);
    opLSR_A(4);
    y = a;
    myMapper->writeCPU(0x031C + x, myMapper->readCPU(0xE8ED + y));
    a = 0x00;
    myMapper->writeCPU(0x0450 + x, a);
    myMapper->writeCPU(0x0338 + x, a);
    myMapper->writeCPU(0x0488 + x, 0x80);
    a = myMapper->readCPU(0xE8EA + y);
    jump(0xDF0E);
    return;
}

void game::SUB_01E8F0() {
    if (myMapper->readCPU(0x005B) == 0) {
        goto L_01E8FF;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        opDEC(0x005B, 1);
        pushAddress(0xE8FE);
        jump(0xFB06);
        if (handleReturnAddress(poppedEntry.value, 0xE8FE)) return;
    }
L_01E8FF:
    y = 0x00;
    a = myMapper->readCPU(0x002B);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01E907;
    }
    y = 0x20;
L_01E907:
    myMapper->writeCPU(0x007C, y);
    pushAddress(0xE90B);
    jump(0xEB08);
    if (handleReturnAddress(poppedEntry.value, 0xE90B)) return;
    //NOP
    //NOP
    //NOP
    pushAddress(0xE911);
    jump(0xE3FF);
    if (handleReturnAddress(poppedEntry.value, 0xE911)) return;
    goto L_01E922;
L_01E922:
    x = 0x16;
    SUB_01E924();
    return;
}

void game::SUB_01E924() {
    a = myMapper->readCPU(0x0434 + x);
    setLoadFlag(a);
    if (flgN) {
        jump(0xE92B);
        return;
    }
    if (!flgZ) {
        jump(0xE931);
        return;
    }
    SUB_01E92B();
    return;
}

void game::SUB_01E92B() {
    opDEX(1);
    opCMP(x, 0x03);
    if (flgC) {
        jump(0xE924);
        return;
    }
    popAddress();
}

void game::SUB_01E931() {
    myMapper->writeCPU(0x004B, a);
    y = myMapper->readCPU(0x0560);
    setLoadFlag(y);
    if (!flgZ) {
        if (x == 0x03) {
            goto L_01E94F;
        }
        if (a >= 0x13) {
            goto L_01E943;
        }
        do {
            goto L_01E9E6;
        L_01E943:
            if (a < 0x18) {
                goto L_01E94F;
            }
            if (a == 0x25) {
                goto L_01E94F;
            }
        } while (a < 0x28);
    }
L_01E94F:
    a = myMapper->readCPU(0xE9C9);
    opPHA();
    a = myMapper->readCPU(0xE9C8);
    opPHA();
    a = myMapper->readCPU(0x004B);
    pushAddress(0xE95B);
    jump(0xCA6D);
    if (handleReturnAddress(poppedEntry.value, 0xE95B)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x00EA) + (myMapper->readCPU((0x00EA + 1) & 0x00ff) << 8) + y);
    pushStatus();
    //NOP
    do {
        do {
            a = myMapper->readCPU(0x0434 + x);
            goto L_01EA42;
        L_01E9E0:
            a = 0x10;
            y = 0xF1;
            setLoadFlag(y);
            if (!flgZ) {
                goto L_01EA12;
            }
        L_01E9E6:
            a = myMapper->readCPU(0x0434 + x);
            if (a != 0x35) {
                if (a < 0x28) {
                    goto L_01E9F8;
                }
                opCMP(a, 0x2F);
                if (flgC) {
                    goto L_01E9F8;
                }
                jump(0xEA77);
                return;
            }
        L_01E9F8:
            a = myMapper->readCPU(0x0354 + x);
        } while (a < 0x08);
    } while (a >= 0xF8);
    a = myMapper->readCPU(0x0434 + x);
    if (a == 0x12) {
        goto L_01E9E0;
    }
    if (a == 0x1E) {
        goto L_01E9E0;
    }
    a = 0x08;
    y = 0xF9;
L_01EA12:
    myMapper->writeCPU(0x0016, a);
    myMapper->writeCPU(0x0017, y);
    a = myMapper->readCPU(0x0434 + x);
    if (a != 0x08) {
        if (a == 0x0A) {
            goto L_01EA2D;
        }
        if (a != 0x1E) {
            if (a == 0x13) {
                goto L_01EA2D;
            }
            if (a != 0x10) {
                goto L_01EA30;
            }
        }
    }
L_01EA2D:
    jump(0xEADD);
    return;
L_01EA30:
    pushAddress(0xE9EB);
    jump(0xEACB);
    if (handleReturnAddress(poppedEntry.value, 0xE9EB)) return;
    if (a < myMapper->readCPU(0x0017)) {
        opCMP(a, myMapper->readCPU(0x0016));
        if (flgC) {
            jump(0xEA77);
            return;
        }
    }
    a = myMapper->readCPU(0x0434 + x);
    if (a == 0x17) {
        jump(0xEA80);
        return;
    }
L_01EA42:
    if (a < 0x18) {
        goto L_01EA4A;
    }
    opCMP(a, 0x1E);
    if (!flgC) {
        jump(0xEABD);
        return;
    }
L_01EA4A:
    opCMP(a, 0x11);
    if (flgZ) {
        jump(0xEAB8);
        return;
    }
    opCMP(a, 0x07);
    if (flgZ) {
        jump(0xEAB8);
        return;
    }
    opCMP(a, 0x0C);
    if (flgZ) {
        jump(0xEAB8);
        return;
    }
    opCMP(a, 0x0E);
    if (flgZ) {
        jump(0xEABD);
        return;
    }
    opCMP(a, 0x0F);
    if (flgZ) {
        jump(0xEAB8);
        return;
    }
    opCMP(a, 0x13);
    if (flgZ) {
        jump(0xEAB8);
        return;
    }
    opCMP(a, 0x2F);
    if (!flgZ) {
        jump(0xEA72);
        return;
    }
    y = myMapper->readCPU(0x0584 + x);
    setLoadFlag(y);
    if (flgZ) {
        jump(0xEA72);
        return;
    }
    opDEY(1);
    if (flgZ) {
        jump(0xEA72);
        return;
    }
    myMapper->writeCPU(0x0072, 0x00);
    SUB_01EA72();
    return;
}

void game::SUB_01EA72() {
    a = 0x32;
    myMapper->writeCPU(0x0434 + x, a);
    SUB_01EA77();
    return;
}

void game::SUB_01EA77() {
    pushAddress(0xEA79);
    jump(0xE4D9);
    if (handleReturnAddress(poppedEntry.value, 0xEA79)) return;
    pushAddress(0xEA7C);
    jump(0xF1DB);
    if (handleReturnAddress(poppedEntry.value, 0xEA7C)) return;
    jump(0xE92B);
    return;
}

void game::SUB_01EA80() {
    opCMP(myMapper->readCPU(0x0584 + x), 0x01);
    if (!flgZ) {
        jump(0xEA72);
        return;
    }
    opCMP(myMapper->readCPU(0x046C + x), 0x04);
    if (flgZ) {
        jump(0xEA72);
        return;
    }
    opCMP(myMapper->readCPU(0x038C + x), 0xF8);
    if (flgC) {
        goto L_01EA99;
    }
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01EA9B;
    }
L_01EA99:
    a = 0xF8;
L_01EA9B:
    myMapper->writeCPU(0x038C + x, a);
    a = 0x00;
    myMapper->writeCPU(0x04DC + x, a);
    pushAddress(0xEAA5);
    jump(0xEAB2);
    if (handleReturnAddress(poppedEntry.value, 0xEAA5)) return;
    jump(0xEA77);
    return;
}

void game::SUB_01EAA9() {
    a = myMapper->readCPU(0x0450 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x0450 + x, a);
    popAddress();
}

void game::SUB_01EAB2() {
    pushAddress(0xEAB4);
    jump(0xEAA9);
    if (handleReturnAddress(poppedEntry.value, 0xEAB4)) return;
    jump(0xDC50);
    return;
}

void game::SUB_01EAB8() {
    if (myMapper->readCPU(0x046C + x) != 0) {
        jump(0xEA72);
        return;
    }
    SUB_01EABD();
    return;
}

void game::SUB_01EABD() {
    y = myMapper->readCPU(0x0530 + x);
    a = myMapper->readCPU(0x016C + y);
    opAND(0x7F);
    myMapper->writeCPU(0x016C + y, a);
    jump(0xEA72);
    return;
}

void game::SUB_01EACB() {
    a = myMapper->readCPU(0x03A8 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0053));
    myMapper->writeCPU(0x03A8 + x, a);
    a = myMapper->readCPU(0x038C + x);
    opADC(myMapper->readCPU(0x0052));
    myMapper->writeCPU(0x038C + x, a);
    popAddress();
}

void game::SUB_01EADD() {
    pushAddress(0xEADF);
    jump(0xEACB);
    if (handleReturnAddress(poppedEntry.value, 0xEADF)) return;
    y = a;
    a = myMapper->readCPU(0x0300 + x);
    opADC(myMapper->readCPU(0x0051));
    opAND(0x01);
    myMapper->writeCPU(0x0300 + x, a);
    if (!flgZ) {
        goto L_01EAFD;
    }
    opCMP(y, myMapper->readCPU(0x0017));
    if (flgC) {
        goto L_01EAF5;
    }
    opCMP(y, myMapper->readCPU(0x0016));
    if (flgC) {
        goto L_01EAFA;
    }
L_01EAF5:
    a = 0x80;
    myMapper->writeCPU(0x0300 + x, a);
    do {
        do {
        L_01EAFA:
            jump(0xEA77);
            return;
        L_01EAFD:
            opCMP(y, 0x40);
        } while (!flgC);
        opCMP(y, 0xC0);
    } while (flgC);
    jump(0xEA72);
    return;
}

void game::SUB_01EB08() {
    y = 0x00;
    a = myMapper->readCPU(0x0049);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x003C);
        opAND(0x03);
        if (!flgZ) {
            a = myMapper->readCPU(0x003C);
            opAND(0x04);
            if (flgZ) {
                x = myMapper->readCPU(0x003C);
                if (x == 0x03) {
                    goto L_01EB23;
                }
                opDEX(1);
                if (!flgZ) {
                    goto L_01EB24;
                }
            L_01EB23:
                opDEY(1);
            L_01EB24:
                myMapper->writeCPU(0x0051, y);
                myMapper->writeCPU(0x0053, 0x00);
                a = myMapper->readCPU(0x0049);
                myMapper->writeCPU(0x0052, a);
                popAddress();
                return;
            }
        }
    }
    myMapper->writeCPU(0x0051, y);
    myMapper->writeCPU(0x0052, y);
    myMapper->writeCPU(0x0053, y);
    popAddress();
}

void game::SUB_01EC60() {
    a = 0x00;
    myMapper->writeCPU(0x0434 + x, a);
    myMapper->writeCPU(0x031C + x, a);
    a = 0xF4;
    myMapper->writeCPU(0x0354 + x, a);
    opPLA();
    opPLA();
    jump(0xE92B);
    return;
}

void game::SUB_01EC72() {
    myMapper->writeCPU(0x03FC + x, a);
    myMapper->writeCPU(0x0418 + x, y);
    popAddress();
}

void game::SUB_01EF04() {
    myMapper->writeCPU(0x04C0 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x04A4 + x, a);
    myMapper->writeCPU(0x0488 + x, a);
    myMapper->writeCPU(0x0338 + x, a);
    popAddress();
}

void game::SUB_01EF84() {
    y = 0x00;
    a = myMapper->readCPU(0x038C);
    opSBC(myMapper->readCPU(0x038C + x));
    if (flgC) {
        goto L_01EF91;
    }
    opEOR(0xFF);
    opINY(1);
L_01EF91:
    popAddress();
}

void game::SUB_01F131() {
    myMapper->writeCPU(0x046C + x, a);
    popAddress();
}

void game::SUB_01F1DB() {
    a = myMapper->readCPU(0x0488 + x);
    setLoadFlag(a);
    if (!flgN) {
        if (flgZ) {
            goto L_01F1E6;
        }
        opDEC(0x0488 + x, 1);
        popAddress();
        return;
    L_01F1E6:
        myMapper->writeCPU(0x004D, 0x00);
        a = myMapper->readCPU(0x04C0 + x);
        myMapper->writeCPU(0x004C, a);
        opASL_A(1);
        opROL_M(0x004D, 1);
        flgC = false;
        opADC(myMapper->readCPU(0x004C));
        myMapper->writeCPU(0x004C, a);
        a = myMapper->readCPU(0x004D);
        opADC(0x00);
        myMapper->writeCPU(0x004D, a);
        if (!flgZ) {
            myMapper->writeCPU(0x0008, myMapper->readCPU(0xF23A));
            a = myMapper->readCPU(0xF23B);
            myMapper->writeCPU(0x0009, a);
        }
        else {
            myMapper->writeCPU(0x0008, myMapper->readCPU(0xF238));
            myMapper->writeCPU(0x0009, myMapper->readCPU(0xF239));
        }
        y = myMapper->readCPU(0x004C);
        if (myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y) >= myMapper->readCPU(0x04A4 + x)) {
            goto L_01F224;
        }
        myMapper->writeCPU(0x04A4 + x, 0x00);
    L_01F224:
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
        flgC = false;
        opADC(myMapper->readCPU(0x04A4 + x));
        myMapper->writeCPU(0x031C + x, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0488 + x, a);
        opINC(0x04A4 + x, 1);
    }
    popAddress();
}

void game::SUB_01F42C() {
    myMapper->writeCPU(0x0434 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x046C + x, a);
    myMapper->writeCPU(0x0300 + x, a);
    myMapper->writeCPU(0x0370 + x, a);
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0514 + x, a);
    myMapper->writeCPU(0x0568 + x, a);
    myMapper->writeCPU(0x0584 + x, a);
    popAddress();
}

void game::SUB_01F5EA() {
    x = myMapper->readCPU(0x003C);
    opDEX(1);
    if (!flgZ) {
        opDEX(1);
        if (!flgZ) {
            goto L_01F60E;
        }
    }
    a = myMapper->readCPU(0x002E);
    opAND(0x3F);
    if (flgZ) {
        a = myMapper->readCPU(0x0018);
        if (a != 0x08) {
            if (a == 0x0C) {
                goto L_01F605;
            }
            pushAddress(0xF604);
            jump(0xD196);
            if (handleReturnAddress(poppedEntry.value, 0xF604)) return;
        }
    }
L_01F605:
    pushAddress(0xF607);
    jump(0xF60F);
    if (handleReturnAddress(poppedEntry.value, 0xF607)) return;
    pushAddress(0xF60A);
    jump(0xCFF9);
    if (handleReturnAddress(poppedEntry.value, 0xF60A)) return;
    jump(0xF62D);
    return;
L_01F60E:
    popAddress();
}

void game::SUB_01F60F() {
    myMapper->writeCPU(0x00FD, myMapper->readCPU(0x002E));
    a = myMapper->readCPU(0x002F);
    opAND(0x01);
    myMapper->writeCPU(0x0010, a);
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFBD6 + x);
    opEOR(myMapper->readCPU(0x0010));
    opAND(0x01);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    opORA(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x00FF, a);
    popAddress();
}

void game::SUB_01F62D() {
    y = myMapper->readCPU(0x001A);
    opDEY(1);
    a = y;
    opAND(0x01);
    if (flgZ) {
        opINC(0x0030, 1);
        a = myMapper->readCPU(0x0030);
        opAND(0x07);
        myMapper->writeCPU(0x0030, a);
        myMapper->writeCPU(0x0031, a);
    }
    a = myMapper->readCPU(0x002E);
    opAND(0x20);
    opEOR(myMapper->readCPU(0x003B));
    if (!flgZ) {
        y = 0x01;
        a = myMapper->readCPU(0x003C);
        opAND(0x01);
        if (flgZ) {
            y = 0xFF;
        }
        myMapper->writeCPU(0x0010, y);
        x = 0x01;
        do {
            a = y;
            a = myMapper->readCPU((0x0035 + x) & 0x00ff);
            flgC = false;
            opADC(myMapper->readCPU(0x0010));
            myMapper->writeCPU((0x0035 + x) & 0x00ff, a);
            opDEX(1);
        } while (!flgN);
        pushAddress(0xF662);
        jump(0xF817);
        if (handleReturnAddress(poppedEntry.value, 0xF662)) return;
        a = 0x00;
        myMapper->writeCPU(0x0030, a);
        myMapper->writeCPU(0x0031, a);
        a = myMapper->readCPU(0x003B);
        opAND(0x20);
        opEOR(0x20);
        myMapper->writeCPU(0x003B, a);
        jump(0xF68C);
        return;
    }
    x = 0x00;
    a = myMapper->readCPU(0x003C);
    opAND(0x03);
    opCMP(a, 0x01);
    if (flgZ) {
        goto L_01F67F;
    }
    opINX(1);
L_01F67F:
    myMapper->writeCPU(0x004B, x);
    y = myMapper->readCPU(0x001A);
    opDEY(1);
    a = y;
    opAND(0x01);
    if (!flgZ) {
        jump(0xF68C);
        return;
    }
    pushAddress(0xF68B);
    jump(0xF69E);
    if (handleReturnAddress(poppedEntry.value, 0xF68B)) return;
    SUB_01F68C();
    return;
}

void game::SUB_01F68C() {
    popAddress();
}

void game::SUB_01F699() {
    x = myMapper->readCPU(0x004B);
    a = myMapper->readCPU((0x0030 + x) & 0x00ff);
    popAddress();
}

void game::SUB_01F69E() {
    pushAddress(0xF6A0);
    jump(0xF699);
    if (handleReturnAddress(poppedEntry.value, 0xF6A0)) return;
    opCMP(a, 0x00);
    if (flgZ) {
        jump(0xF68C);
        return;
    }
    opCMP(a, 0x07);
    if (flgZ) {
        jump(0xF68C);
        return;
    }
    myMapper->writeCPU(0x000E, 0x00);
    a = myMapper->readCPU((0x0035 + x) & 0x00ff);
    opASL_A(1);
    y = a;
    opASL_A(1);
    myMapper->writeCPU(0x000D, a);
    if (flgC) {
        opINC(0x000E, 1);
    }
    a = y;
    x = 0x0D;
    pushAddress(0xF6BD);
    jump(0xCA8B);
    if (handleReturnAddress(poppedEntry.value, 0xF6BD)) return;
    pushAddress(0xF6C0);
    jump(0xF699);
    if (handleReturnAddress(poppedEntry.value, 0xF6C0)) return;
    y = a;
    opDEY(1);
    a = y;
    x = 0x0D;
    pushAddress(0xF6C8);
    jump(0xCA8B);
    if (handleReturnAddress(poppedEntry.value, 0xF6C8)) return;
    a = myMapper->readCPU(0x000D);
    flgC = false;
    opADC(myMapper->readCPU(0x0033));
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x000E);
    opADC(myMapper->readCPU(0x0034));
    myMapper->writeCPU(0x000E, a);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0032, a);
    opCMP(a, 0xFF);
    if (flgZ) {
        jump(0xF68C);
        return;
    }
    a = myMapper->readCPU(0x004B);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0002, myMapper->readCPU((0x0037 + x) & 0x00ff));
    myMapper->writeCPU(0x0003, myMapper->readCPU((0x0038 + x) & 0x00ff));
    x = myMapper->readCPU(0x004B);
    myMapper->writeCPU(0x004C, myMapper->readCPU((0x0030 + x) & 0x00ff));
    opDEC(0x004C, 1);
    opASL_M(0x004C, 1);
    x = myMapper->readCPU(0x004C);
    a = myMapper->readCPU(0xF68D + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0002, a);
    opINX(1);
    a = myMapper->readCPU(0xF68D + x);
    opADC(myMapper->readCPU(0x0003));
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0006, myMapper->readCPU(0xF9FA + x));
    myMapper->writeCPU(0x0007, myMapper->readCPU(0xF9FB + x));
    myMapper->writeCPU(0x004F, 0x00);
    x = myMapper->readCPU(0x0032);
    myMapper->writeCPU(0x004E, x);
    opASL_M(0x004E, 1);
    opROL_M(0x004F, 1);
    opASL_M(0x004E, 1);
    opROL_M(0x004F, 1);
    opASL_M(0x004E, 1);
    opROL_M(0x004F, 1);
    opASL_M(0x004E, 1);
    opROL_M(0x004F, 1);
    a = x;
    flgC = false;
    opADC(myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x004E, a);
    if (flgC) {
        opINC(0x004F, 1);
    }
    flgC = false;
    a = myMapper->readCPU(0x004E);
    opADC(myMapper->readCPU(0x0006));
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU(0x004F);
    opADC(myMapper->readCPU(0x0007));
    myMapper->writeCPU(0x0007, a);
    pushAddress(0xF747);
    jump(0xF7ED);
    if (handleReturnAddress(poppedEntry.value, 0xF747)) return;
    x = myMapper->readCPU(0x0020);
    y = 0x00;
    myMapper->writeCPU(0x0700 + x, 0x01);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x000B));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x000A));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(myMapper->readCPU(0x0006) + (myMapper->readCPU((0x0006 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x004E, x);
    x = myMapper->readCPU(0x004B);
    a = myMapper->readCPU((0x0030 + x) & 0x00ff);
    x = myMapper->readCPU(0x004E);
    opCMP(a, 0x01);
    if (!flgZ) {
        goto L_01F777;
    }
    a = myMapper->readCPU(0x0700 + x);
    opORA(0x0F);
    myMapper->writeCPU(0x0700 + x, a);
L_01F777:
    opINY(1);
    opINX(1);
    pushAddress(0xF77B);
    jump(0xCC5F);
    if (handleReturnAddress(poppedEntry.value, 0xF77B)) return;
    myMapper->writeCPU(0x000D, 0x04);
    do {
        myMapper->writeCPU(0x004E, x);
        x = myMapper->readCPU(0x004B);
        a = myMapper->readCPU((0x0030 + x) & 0x00ff);
        x = myMapper->readCPU(0x004E);
        if (a == 0x01) {
            a = myMapper->readCPU(0x000D);
            if (a == 0x04) {
                goto L_01F796;
            }
            if (a != 0x03) {
                goto L_01F79D;
            }
        L_01F796:
            opINY(4);
            goto L_01F7E1;
        }
    L_01F79D:
        myMapper->writeCPU(0x0700 + x, 0x01);
        opINX(1);
        a = myMapper->readCPU(0x0003);
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x0009, a);
        opINX(1);
        a = myMapper->readCPU(0x0002);
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x0008, a);
        opINX(1);
        myMapper->writeCPU(0x0020, x);
        myMapper->writeCPU(0x004F, y);
        pushAddress(0xF7B9);
        jump(0xF94F);
        if (handleReturnAddress(poppedEntry.value, 0xF7B9)) return;
        y = myMapper->readCPU(0x004F);
        x = myMapper->readCPU(0x0020);
        myMapper->writeCPU(0x000E, 0x04);
        myMapper->writeCPU(0x0004, 0x00);
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0006) + (myMapper->readCPU((0x0006 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x0700 + x, a);
            pushAddress(0xF7CD);
            jump(0xF9D4);
            if (handleReturnAddress(poppedEntry.value, 0xF7CD)) return;
            opINY(1);
            opINX(1);
            opDEC(0x000E, 1);
        } while (!flgZ);
        myMapper->writeCPU(0x004F, y);
        y = 0x00;
        a = myMapper->readCPU(0x0004);
        myMapper->writeCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y, a);
        y = myMapper->readCPU(0x004F);
        pushAddress(0xF7E0);
        jump(0xCC5F);
        if (handleReturnAddress(poppedEntry.value, 0xF7E0)) return;
    L_01F7E1:
        a = 0x20;
        flgC = false;
        opADC(myMapper->readCPU(0x0002));
        myMapper->writeCPU(0x0002, a);
        opDEC(0x000D, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01F7ED() {
    a = myMapper->readCPU(0x0003);
    x = 0x23;
    if (a < 0x24) {
        goto L_01F7F7;
    }
    x = 0x27;
L_01F7F7:
    myMapper->writeCPU(0x000B, x);
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0x0002);
    opLSR_M(0x0010, 1);
    opROR_A(1);
    opLSR_M(0x0010, 1);
    opROR_A(1);
    opPHA();
    opAND(0x07);
    y = a;
    opPLA();
    opLSR_A(2);
    opAND(0x38);
    flgC = false;
    opADC(0xC0);
    myMapper->writeCPU(0x0010, y);
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x000A, a);
    popAddress();
}

void game::SUB_01F817() {
    myMapper->writeCPU(0x0015, 0x00);
    a = 0x60;
    flgC = false;
    opADC(myMapper->readCPU(0x002E));
    x = a;
    opROL_A(1);
    opAND(0x01);
    opEOR(0x01);
    flgC = false;
    opADC(myMapper->readCPU(0x002F));
    y = a;
    pushAddress(0xF82C);
    jump(0xF841);
    if (handleReturnAddress(poppedEntry.value, 0xF82C)) return;
    opINC(0x0015, 2);
    a = myMapper->readCPU(0x002E);
    flgC = true;
    opSBC(0x80);
    x = a;
    a = myMapper->readCPU(0x002F);
    if (flgC) {
        goto L_01F83E;
    }
    y = a;
    opDEY(1);
    a = y;
L_01F83E:
    opAND(0x01);
    y = a;
    SUB_01F841();
    return;
}

void game::SUB_01F841() {
    a = x;
    opLSR_A(3);
    opAND(0x1C);
    flgC = false;
    opADC(0x80);
    x = myMapper->readCPU(0x0015);
    myMapper->writeCPU((0x0037 + x) & 0x00ff, a);
    a = y;
    opAND(0x01);
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x004E, x);
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFBD6 + x);
    opEOR(myMapper->readCPU(0x0010));
    opAND(0x01);
    opASL_A(2);
    flgC = false;
    opADC(0x20);
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU((0x0038 + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_01F868() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2005, 0x00);
    myMapper->writeCPU(0x2005, 0x00);
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    myMapper->writeCPU(0x2000, a);
    SUB_01F87C();
    return;
}

void game::SUB_01F87C() {
    popAddress();
}

void game::SUB_01F87D() {
    if (myMapper->readCPU(0x0018) != 0x02) {
        goto L_01F889;
    }
    a = myMapper->readCPU(0x0019);
    opCMP(a, 0x01);
    if (flgZ) {
        goto L_01F8B6;
    }
L_01F889:
    a = myMapper->readCPU(0x0018);
    flgC = true;
    opSBC(0x07);
    opCMP(a, 0x05);
    if (flgC) {
        if (myMapper->readCPU(0x0018) != 0x0C) {
            goto L_01F89E;
        }
        a = myMapper->readCPU(0x0019);
        opCMP(a, 0x08);
        if (!flgC) {
            goto L_01F8B6;
        }
    L_01F89E:
        if (myMapper->readCPU(0x0018) == 0x05) {
            a = myMapper->readCPU(0x0019);
            opCMP(a, 0x06);
            if (flgZ) {
                goto L_01F8B6;
            }
        }
        a = myMapper->readCPU(0x0018);
        opCMP(a, 0x04);
        if (!flgZ) {
            jump(0xF87C);
            return;
        }
        a = myMapper->readCPU(0x0019);
        opCMP(a, 0x02);
        if (!flgZ) {
            jump(0xF87C);
            return;
        }
    }
L_01F8B6:
    pushAddress(0xF8B8);
    jump(0xC13F);
    if (handleReturnAddress(poppedEntry.value, 0xF8B8)) return;
    a = myMapper->readCPU(0x001F);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xF87C);
        return;
    }
    pushAddress(0xF8BF);
    jump(0xF868);
    if (handleReturnAddress(poppedEntry.value, 0xF8BF)) return;
    a = myMapper->readCPU(0x001B);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01F8C7;
    }
    pushAddress(0xF8C6);
    jump(0xA08A);
    if (handleReturnAddress(poppedEntry.value, 0xF8C6)) return;
L_01F8C7:
    x = 0x00;
    do {
        opINX(1);
        if (flgZ) {
            goto L_01F8D3;
        }
        a = myMapper->readCPU(0x2002);
        opAND(0x40);
    } while (!flgZ);
L_01F8D3:
    x = 0x00;
    do {
        opINX(1);
        if (flgZ) {
            goto L_01F8E6;
        }
        a = myMapper->readCPU(0x2002);
        opAND(0x40);
        if (!flgZ) {
            goto L_01F8E6;
        }
        a = myMapper->readCPU(0x2002);
        opAND(0x40);
    } while (flgZ);
L_01F8E6:
    y = 0x2C;
    do {
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x2002);
    a = myMapper->readCPU(0x002E);
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU(0x2005, a);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    pushAddress(0xF8FC);
    jump(0xF909);
    if (handleReturnAddress(poppedEntry.value, 0xF8FC)) return;
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    opADC(0x00);
    myMapper->writeCPU(0x00FF, a);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_01F909() {
    pushAddress(0xF90B);
    jump(0xF912);
    if (handleReturnAddress(poppedEntry.value, 0xF90B)) return;
    opEOR(myMapper->readCPU(0x002F));
    opAND(0x01);
    opLSR_A(1);
    popAddress();
}

void game::SUB_01F912() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFBD6 + x);
    popAddress();
}

void game::SUB_01F94F() {
    myMapper->writeCPU(0x0017, 0x00);
    a = myMapper->readCPU(0x0008);
    flgC = true;
    opSBC(0xC0);
    myMapper->writeCPU(0x0008, a);
    if (!flgC) {
        opDEC(0x0009, 1);
    }
    a = myMapper->readCPU(0x0008);
    x = a;
    opAND(0x03);
    opEOR(0x03);
    myMapper->writeCPU(0x0015, a);
    a = x;
    opLSR_M(0x0009, 1);
    opROR_A(1);
    opLSR_M(0x0009, 1);
    opROR_A(1);
    myMapper->writeCPU(0x0016, a);
    a = myMapper->readCPU(0x0009);
    x = 0xB0;
    opAND(0x01);
    if (!flgZ) {
        goto L_01F97A;
    }
    x = 0x00;
L_01F97A:
    a = x;
    x = 0x16;
    pushAddress(0xF97F);
    jump(0xCA8B);
    if (handleReturnAddress(poppedEntry.value, 0xF97F)) return;
    a = 0xA0;
    flgC = false;
    opADC(myMapper->readCPU(0x0016));
    myMapper->writeCPU(0x0016, a);
    a = 0x05;
    opADC(myMapper->readCPU(0x0017));
    myMapper->writeCPU(0x0017, a);
    x = myMapper->readCPU(0x0015);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    while (true) {
        opDEX(1);
        if (flgN) {
            goto L_01F99B;
        }
        opLSR_A(2);
    }
L_01F99B:
    opAND(0x03);
    myMapper->writeCPU(0x0014, a);
    popAddress();
}

void game::SUB_01F9D4() {
    myMapper->writeCPU(0x004C, 0x00);
    a = myMapper->readCPU(0x0700 + x);
    flgC = true;
    opSBC(0x60);
    if (a < 0x0C) {
        myMapper->writeCPU(0x004C, 0x40);
        if (myMapper->readCPU(0x0700 + x) != 0x66) {
            goto L_01F9F1;
        }
        myMapper->writeCPU(0x004C, 0x80);
    }
L_01F9F1:
    opASL_M(0x004C, 1);
    opROL_M(0x0004, 1);
    opASL_M(0x004C, 1);
    opROL_M(0x0004, 1);
    popAddress();
}

void game::SUB_01FA6A() {
    if (myMapper->readCPU(0x015D) == 0) {
        goto L_01FA8D;
    }
    y = myMapper->readCPU(0x001A);
    opDEY(1);
    a = y;
    opAND(0x01);
    if (flgZ) {
        pushAddress(0xFA79);
        jump(0xFA8E);
        if (handleReturnAddress(poppedEntry.value, 0xFA79)) return;
        pushAddress(0xFA7C);
        jump(0xDEDC);
        if (handleReturnAddress(poppedEntry.value, 0xFA7C)) return;
        opDEC(0x015D, 1);
        if (!flgZ) {
            goto L_01FA8D;
        }
        pushAddress(0xFA84);
        jump(0xD10E);
        if (handleReturnAddress(poppedEntry.value, 0xFA84)) return;
        a = 0x00;
        myMapper->writeCPU(0x015C, a);
        myMapper->writeCPU(0x015D, a);
    }
L_01FA8D:
    popAddress();
}

void game::SUB_01FA8E() {
    a = myMapper->readCPU(0x0020);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x0010, a);
    pushAddress(0xFA97);
    jump(0xD10E);
    if (handleReturnAddress(poppedEntry.value, 0xFA97)) return;
    x = 0x0F;
    a = myMapper->readCPU(0x001A);
    opAND(0x02);
    if (!flgZ) {
        goto L_01FAA2;
    }
    x = 0x10;
L_01FAA2:
    myMapper->writeCPU(0x004B, x);
    x = myMapper->readCPU(0x0010);
    y = 0x04;
    do {
        a = myMapper->readCPU(0x004B);
        pushAddress(0xFAAC);
        jump(0xA357);
        if (handleReturnAddress(poppedEntry.value, 0xFAAC)) return;
        opINX(3);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01FB05() {
    popAddress();
}

void game::SUB_01FB06() {
    a = myMapper->readCPU(0x005B);
    x = 0x14;
    opCMP(a, 0x80);
    if (flgZ) {
        goto L_01FB1E;
    }
    opCMP(a, 0x40);
    if (!flgZ) {
        jump(0xFB05);
        return;
    }
    a = 0x1C;
    pushAddress(0xFB16);
    jump(0xC1A7);
    if (handleReturnAddress(poppedEntry.value, 0xFB16)) return;
    y = 0x05;
    pushAddress(0xFB1B);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xFB1B)) return;
    x = 0x15;
L_01FB1E:
    a = x;
    jump(0xCC95);
    return;
}

void game::SUB_01FC97() {
    pushAddress(0xFC99);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xFC99)) return;
    pushAddress(0xFC9C);
    jump(0x96C1);
    if (handleReturnAddress(poppedEntry.value, 0xFC9C)) return;
    y = 0x05;
    jump(0xC1D6);
    return;
}

void game::SUB_01FCD0() {
    y = 0x06;
    pushAddress(0xFCD4);
    jump(0xC1D6);
    if (handleReturnAddress(poppedEntry.value, 0xFCD4)) return;
    a = 0x06;
    a = myMapper->readCPU(0x0071);
    pushAddress(0xFCDB);
    jump(0xA333);
    if (handleReturnAddress(poppedEntry.value, 0xFCDB)) return;
    myMapper->writeCPU(0x0008, a);
    a = 0x1B;
    pushAddress(0xFCE2);
    jump(0xCC95);
    if (handleReturnAddress(poppedEntry.value, 0xFCE2)) return;
    a = myMapper->readCPU(0x0008);
    pushAddress(0xFCE7);
    jump(0xCC68);
    if (handleReturnAddress(poppedEntry.value, 0xFCE7)) return;
    pushAddress(0xFCEA);
    jump(0xCC5F);
    if (handleReturnAddress(poppedEntry.value, 0xFCEA)) return;
    y = 0x05;
    jump(0xC1D6);
    return;
}

void game::SUB_01FD18() {
    pushAddress(0xFD1A);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xFD1A)) return;
    pushAddress(0xFD1D);
    jump(0xCAAF);
    if (handleReturnAddress(poppedEntry.value, 0xFD1D)) return;
    y = 0x05;
    jump(0xC1D6);
    return;
}

void game::SUB_01FD23() {
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0012, myMapper->readCPU(0xFDBB + x));
    a = myMapper->readCPU(0xFDBC + x);
    myMapper->writeCPU(0x0013, a);
    pushAddress(0xFD31);
    jump(0xC132);
    if (handleReturnAddress(poppedEntry.value, 0xFD31)) return;
    y = 0x00;
    opDEY(1);
    while (true) {
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0007, a);
        opCMP(a, 0xFF);
        if (!flgZ) {
            goto L_01FD41;
        }
        goto L_01FD77;
    L_01FD41:
        myMapper->writeCPU(0x0017, y);
        y = myMapper->readCPU(0x0007);
        pushAddress(0xFD47);
        jump(0xC1D6);
        if (handleReturnAddress(poppedEntry.value, 0xFD47)) return;
        y = myMapper->readCPU(0x0017);
        opINY(1);
        x = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x0001, myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0000, x);
        a = myMapper->readCPU(0x0000);
        opINY(1);
        x = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x0003, myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0002, x);
        opINY(1);
        x = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0012) + (myMapper->readCPU((0x0012 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0005, x);
        myMapper->writeCPU(0x0004, a);
        myMapper->writeCPU(0x0014, y);
        pushAddress(0xFD71);
        jump(0xFD7E);
        if (handleReturnAddress(poppedEntry.value, 0xFD71)) return;
        y = myMapper->readCPU(0x0014);
    }
L_01FD77:
    pushAddress(0xFD79);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xFD79)) return;
    pushAddress(0xFD7C);
    jump(0xC102);
    if (handleReturnAddress(poppedEntry.value, 0xFD7C)) return;
    popAddress();
}

void game::SUB_01FD7E() {
    myMapper->writeCPU(0x0008, myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0003));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0002));
    a = 0x00;
    myMapper->writeCPU(0x000C, a);
    myMapper->writeCPU(0x000D, a);
    x = 0x00;
    y = 0x00;
L_01FD9A:
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    opINC(0x0008, 1);
    if (flgZ) {
        opINC(0x0009, 1);
    }
    myMapper->writeCPU(0x2007, a);
    opINC(0x000D, 1);
    if (flgZ) {
        opINC(0x000C, 1);
    }
    a = myMapper->readCPU(0x000D);
    if (a != myMapper->readCPU(0x0005)) {
        goto L_01FDB7;
    }
    a = myMapper->readCPU(0x000C);
    if (a == myMapper->readCPU(0x0004)) {
        goto L_01FDBA;
    }
L_01FDB7:
    goto L_01FD9A;
L_01FDBA:
    popAddress();
}

void game::SUB_01FE96() {
    myMapper->writeCPU(0x4015, 0x0F);
    x = 0x0F;
    y = 0xFD;
    a = 0x0B;
    goto L_01FEA4;
L_01FEA4:
    myMapper->writeCPU(0x4010, x);
    myMapper->writeCPU(0x4012, y);
    myMapper->writeCPU(0x4013, a);
    a = 0x1F;
    myMapper->writeCPU(0x4015, a);
    popAddress();
}

void game::jump(Uint16 target) {
    Uint32 tAddress = myMapper->readRealAddress(target);
    switch (tAddress) {
    case 0x01C132:
        SUB_01C132();
        break;
    case 0x01C16D:
        SUB_01C16D();
        break;
    case 0x01C18E:
        SUB_01C18E();
        break;
    case 0x01C19B:
        SUB_01C19B();
        break;
    case 0x01C0F7:
        SUB_01C0F7();
        break;
    case 0x01C14B:
        SUB_01C14B();
        break;
    case 0x01C1D4:
        SUB_01C1D4();
        break;
    case 0x01C1D6:
        SUB_01C1D6();
        break;
    case 0x01F87D:
        SUB_01F87D();
        break;
    case 0x01C11F:
        SUB_01C11F();
        break;
    case 0x01C8CD:
        SUB_01C8CD();
        break;
    case 0x01C1E4:
        SUB_01C1E4();
        break;
    case 0x01CCEE:
        SUB_01CCEE();
        break;
    case 0x01C0D7:
        SUB_01C0D7();
        break;
    case 0x01C1D8:
        SUB_01C1D8();
        break;
    case 0x01C1CF:
        SUB_01C1CF();
        break;
    case 0x01C1A7:
        SUB_01C1A7();
        break;
    case 0x01C102:
        SUB_01C102();
        break;
    case 0x01C91C:
        SUB_01C91C();
        break;
    case 0x01CA6D:
        SUB_01CA6D();
        break;
    case 0x01C373:
        SUB_01C373();
        break;
    case 0x01FA6A:
        SUB_01FA6A();
        break;
    case 0x01E8F0:
        SUB_01E8F0();
        break;
    case 0x01F5EA:
        SUB_01F5EA();
        break;
    case 0x01C474:
        SUB_01C474();
        break;
    case 0x01C4A4:
        SUB_01C4A4();
        break;
    case 0x01C365:
        SUB_01C365();
        break;
    case 0x01C4A8:
        SUB_01C4A8();
        break;
    case 0x01C994:
        SUB_01C994();
        break;
    case 0x01CFBD:
        SUB_01CFBD();
        break;
    case 0x01D162:
        SUB_01D162();
        break;
    case 0x01C8C3:
        SUB_01C8C3();
        break;
    case 0x01C4AA:
        SUB_01C4AA();
        break;
    case 0x01C90D:
        SUB_01C90D();
        break;
    case 0x01C917:
        SUB_01C917();
        break;
    case 0x01C903:
        SUB_01C903();
        break;
    case 0x01C95D:
        SUB_01C95D();
        break;
    case 0x01C37A:
        SUB_01C37A();
        break;
    case 0x01FD23:
        SUB_01FD23();
        break;
    case 0x01C371:
        SUB_01C371();
        break;
    case 0x01CAE7:
        SUB_01CAE7();
        break;
    case 0x01CB11:
        SUB_01CB11();
        break;
    case 0x01CAE3:
        SUB_01CAE3();
        break;
    case 0x01CC3D:
        SUB_01CC3D();
        break;
    case 0x01CC95:
        SUB_01CC95();
        break;
    case 0x01CC68:
        SUB_01CC68();
        break;
    case 0x01CC5F:
        SUB_01CC5F();
        break;
    case 0x01CC75:
        SUB_01CC75();
        break;
    case 0x01CCF0:
        SUB_01CCF0();
        break;
    case 0x01CCF6:
        SUB_01CCF6();
        break;
    case 0x01CCF2:
        SUB_01CCF2();
        break;
    case 0x01CFF9:
        SUB_01CFF9();
        break;
    case 0x01F912:
        SUB_01F912();
        break;
    case 0x01F817:
        SUB_01F817();
        break;
    case 0x01D132:
        SUB_01D132();
        break;
    case 0x01D1BE:
        SUB_01D1BE();
        break;
    case 0x01D195:
        SUB_01D195();
        break;
    case 0x01EF04:
        SUB_01EF04();
        break;
    case 0x01F42C:
        SUB_01F42C();
        break;
    case 0x01EC72:
        SUB_01EC72();
        break;
    case 0x01F131:
        SUB_01F131();
        break;
    case 0x01E3F4:
        SUB_01E3F4();
        break;
    case 0x01FD18:
        SUB_01FD18();
        break;
    case 0x01DF06:
        SUB_01DF06();
        break;
    case 0x01E109:
        SUB_01E109();
        break;
    case 0x01E0E9:
        SUB_01E0E9();
        break;
    case 0x01E0E4:
        SUB_01E0E4();
        break;
    case 0x01E0F4:
        SUB_01E0F4();
        break;
    case 0x01E0E2:
        SUB_01E0E2();
        break;
    case 0x01E4CC:
        SUB_01E4CC();
        break;
    case 0x01DF79:
        SUB_01DF79();
        break;
    case 0x01EF84:
        SUB_01EF84();
        break;
    case 0x01EAA9:
        SUB_01EAA9();
        break;
    case 0x01E09A:
        SUB_01E09A();
        break;
    case 0x01FE96:
        SUB_01FE96();
        break;
    case 0x01FC97:
        SUB_01FC97();
        break;
    case 0x01FCD0:
        SUB_01FCD0();
        break;
    case 0x01EC60:
        SUB_01EC60();
        break;
    case 0x01DF0E:
        SUB_01DF0E();
        break;
    case 0x01FB06:
        SUB_01FB06();
        break;
    case 0x01EB08:
        SUB_01EB08();
        break;
    case 0x01E3FF:
        SUB_01E3FF();
        break;
    case 0x01E92B:
        SUB_01E92B();
        break;
    case 0x01E931:
        SUB_01E931();
        break;
    case 0x01E924:
        SUB_01E924();
        break;
    case 0x01EA77:
        SUB_01EA77();
        break;
    case 0x01EADD:
        SUB_01EADD();
        break;
    case 0x01EACB:
        SUB_01EACB();
        break;
    case 0x01EA80:
        SUB_01EA80();
        break;
    case 0x01EABD:
        SUB_01EABD();
        break;
    case 0x01EAB8:
        SUB_01EAB8();
        break;
    case 0x01EA72:
        SUB_01EA72();
        break;
    case 0x01E4D9:
        SUB_01E4D9();
        break;
    case 0x01F1DB:
        SUB_01F1DB();
        break;
    case 0x01EAB2:
        SUB_01EAB2();
        break;
    case 0x01DC50:
        SUB_01DC50();
        break;
    case 0x01D196:
        SUB_01D196();
        break;
    case 0x01F60F:
        SUB_01F60F();
        break;
    case 0x01F62D:
        SUB_01F62D();
        break;
    case 0x01F68C:
        SUB_01F68C();
        break;
    case 0x01F69E:
        SUB_01F69E();
        break;
    case 0x01F699:
        SUB_01F699();
        break;
    case 0x01CA8B:
        SUB_01CA8B();
        break;
    case 0x01F7ED:
        SUB_01F7ED();
        break;
    case 0x01F94F:
        SUB_01F94F();
        break;
    case 0x01F9D4:
        SUB_01F9D4();
        break;
    case 0x01F841:
        SUB_01F841();
        break;
    case 0x01F87C:
        SUB_01F87C();
        break;
    case 0x01C13F:
        SUB_01C13F();
        break;
    case 0x01F868:
        SUB_01F868();
        break;
    case 0x01F909:
        SUB_01F909();
        break;
    case 0x01FA8E:
        SUB_01FA8E();
        break;
    case 0x01DEDC:
        SUB_01DEDC();
        break;
    case 0x01D10E:
        SUB_01D10E();
        break;
    case 0x01FB05:
        SUB_01FB05();
        break;
    case 0x01CAAF:
        SUB_01CAAF();
        break;
    case 0x01FD7E:
        SUB_01FD7E();
        break;
    case 0x00000A:
        SUB_00000A();
        break;
    case 0x000052:
        SUB_000052();
        break;
    case 0x000187:
        SUB_000187();
        break;
    case 0x00038A:
        SUB_00038A();
        break;
    case 0x01A333:
        SUB_01A333();
        break;
    default:
		string mapperMode = myMapper->getMapperMode();
        printf("Unhandled jump to address: %04X\n", target);
		exit(1);
    }
}
