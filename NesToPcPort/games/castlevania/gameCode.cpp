#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"
#include <stdexcept> // Add this include to resolve std::runtime_error

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
            goto L_0000A5;
        L_00009A:
            y = a;
            myMapper->writeCPU(0x0008, myMapper->readCPU(0x90BE + y));
            a = myMapper->readCPU(0x90BF + y);
            myMapper->writeCPU(0x0009, a);
        L_0000A5:
            pushAddress(0x80A7);
            SUB_0000D6();
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

void game::SUB_0000C2() {
    flgC = false;
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x004E);
    jump(0x8112);
    return;
}

void game::SUB_0000D2() {
    opINY(1);
    flgC = false;
    if (!flgC) {
        jump(0x80EF);
        return;
    }
    SUB_0000D6();
    return;
}

void game::SUB_0000D6() {
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgZ) {
        jump(0x8134);
        return;
    }
    opINY(1);
    myMapper->writeCPU(0x0003, a);
    x = myMapper->readCPU(0x0004);
    SUB_0000E1();
    return;
}

void game::SUB_0000E1() {
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (!flgN) {
        jump(0x80D2);
        return;
    }
    opINY(1);
    if (a == 0x80) {
        jump(0x8141);
        return;
    }
    if (a == 0x81) {
        jump(0x8135);
        return;
    }
    flgC = true;
    SUB_0000EF();
    return;
}

void game::SUB_0000EF() {
    opROR_A(1);
    if (flgC) {
        jump(0x80C2);
        return;
    }
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    if (myMapper->readCPU(0x004B) != 0) {
        jump(0x815A);
        return;
    }
    if (myMapper->readCPU(0x0000) != 0) {
        goto L_00010A;
    }
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    jump(0x8110);
    return;
L_00010A:
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    opAND(0xDC);
    opORA(myMapper->readCPU(0x0000));
    SUB_000110();
    return;
}

void game::SUB_000110() {
    myMapper->writeCPU(0x004E, a);
    SUB_000112();
    return;
}

void game::SUB_000112() {
    myMapper->writeCPU(0x0202 + x, a);
    opINY(1);
    if (myMapper->readCPU(0x004B) != 0) {
        jump(0x816E);
        return;
    }
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    SUB_00011C();
    return;
}

void game::SUB_00011C() {
    flgC = false;
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0203 + x, a);
    a = x;
    do {
        flgC = false;
        opADC(0xC4);
    } while (a < 0x44);
    x = a;
    opDEC(0x0007, 1);
    opINY(1);
    opDEC(0x0003, 1);
    if (!flgZ) {
        jump(0x80E1);
        return;
    }
    myMapper->writeCPU(0x0004, x);
    SUB_000134();
    return;
}

void game::SUB_000134() {
    popAddress();
}

void game::SUB_000135() {
    myMapper->writeCPU(0x0008, myMapper->readCPU(0x000A));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x000B));
    y = myMapper->readCPU(0x0006);
    setLoadFlag(y);
    if (!flgZ) {
        jump(0x80E1);
        return;
    }
    SUB_000141();
    return;
}

void game::SUB_000141() {
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x0008));
    myMapper->writeCPU(0x000B, myMapper->readCPU(0x0009));
    a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0006, y);
    myMapper->writeCPU(0x0009, a);
    y = 0x00;
    jump(0x80E1);
    return;
}

void game::SUB_00015A() {
    if (myMapper->readCPU(0x0000) != 0) {
        goto L_000163;
    }
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    goto L_000169;
L_000163:
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    opAND(0xDC);
    opORA(myMapper->readCPU(0x0000));
L_000169:
    opEOR(0x40);
    jump(0x8110);
    return;
}

void game::SUB_00016E() {
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x08);
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
    jump(0x811C);
    return;
}

void game::SUB_00017B() {
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
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
    if (a == 0x04) {
        goto L_0001D3;
    }
    if (a == myMapper->readCPU(0x00C2)) {
        goto L_00020D;
    }
    if (a == myMapper->readCPU(0x00D2)) {
        goto L_0001F4;
    }
    while (true) {
    L_0001D3:
        y = myMapper->readCPU(0x00E4);
        a = myMapper->readCPU(myMapper->readCPU(0x00E0) + (myMapper->readCPU((0x00E0 + 1) & 0x00ff) << 8) + y);
        opAND(0x3F);
        myMapper->writeCPU(0x00E8, a);
        if (myMapper->readCPU(0x00E5) == 0x04) {
            a = myMapper->readCPU(0x00E8);
        }
        else {
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
                while (true) {
                L_0001F4:
                    a = 0x14;
                    goto L_00020F;
                    do {
                    L_0001F9:
                        goto L_000298;
                    L_0001FC:
                        if (a >= myMapper->readCPU(0x00C2)) {
                            goto L_000207;
                        }
                    } while (a >= myMapper->readCPU(0x00E5));
                }
            L_000207:
                a = myMapper->readCPU(0x00C2);
                if (a >= myMapper->readCPU(0x00E5)) {
                    goto L_0001F9;
                }
            L_00020D:
                a = 0x10;
            }
        }
    L_00020F:
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
        }
        else {
            if (y != 0x04) {
                goto L_00027C;
            }
            if (myMapper->readCPU(0x00D2) != 0) {
                goto L_000294;
            }
        }
    L_00027C:
        a = y;
        opAND(0x0F);
        y = a;
        a = 0x00;
        if (y == 0x08) {
            goto L_000288;
        }
        a = 0x30;
    L_000288:
        myMapper->writeCPU(0x4000 + y, a);
        pushAddress(0x828D);
        SUB_00017B();
        if (handleReturnAddress(poppedEntry.value, 0x828D)) return;
        myMapper->writeCPU(0x4001 + y, a);
        pushAddress(0x8293);
        SUB_00017B();
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
    }
L_0002A6:
    a = 0x00;
    myMapper->writeCPU(0x00E1, a);
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_0002B5() {
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    //NOP
    popAddress();
}

void game::SUB_0002BF() {
    a = x;
    opPHA();
    a = myMapper->readCPU((0x0002 + x) & 0x00ff);
    myMapper->writeCPU(0x00E8, a);
    myMapper->writeCPU((0x0002 + x) & 0x00ff, y);
    if (x == 0xC0) {
        a = myMapper->readCPU(0x0082);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00032B;
        }
        x = 0x80;
        a = 0x00;
        myMapper->writeCPU(0x4001, a);
        pushAddress(0x82D8);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x82D8)) return;
        a = myMapper->readCPU(0x00A7);
        myMapper->writeCPU(0x4002, a);
        pushAddress(0x82E0);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x82E0)) return;
        a = myMapper->readCPU((0x0001 + x) & 0x00ff);
        myMapper->writeCPU(0x4003, a);
        pushAddress(0x82E8);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x82E8)) return;
        a = myMapper->readCPU(0x00E8);
        if (a == 0x54) {
            goto L_00032B;
        }
        a = myMapper->readCPU((0x0007 + x) & 0x00ff);
        myMapper->writeCPU(0x4000, a);
        pushAddress(0x82F6);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x82F6)) return;
    }
    else {
        if (x != 0xD0) {
            goto L_00032B;
        }
        a = myMapper->readCPU(0x0092);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00032B;
        }
        x = 0x90;
        myMapper->writeCPU(0x4005, y);
        pushAddress(0x8309);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x8309)) return;
        a = myMapper->readCPU(0x00B8);
        myMapper->writeCPU(0x4006, a);
        pushAddress(0x8311);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x8311)) return;
        a = myMapper->readCPU((0x0001 + x) & 0x00ff);
        myMapper->writeCPU(0x4007, a);
        pushAddress(0x8319);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x8319)) return;
        a = myMapper->readCPU(0x00E8);
        if (a == 0x54) {
            goto L_00032B;
        }
        a = myMapper->readCPU((0x0007 + x) & 0x00ff);
        myMapper->writeCPU(0x4004, a);
        pushAddress(0x8327);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x8327)) return;
    }
    opPLA();
    x = a;
    popAddress();
    return;
L_00032B:
    opPLA();
    x = a;
    a = y;
    if (x != 0xA0) {
        myMapper->writeCPU((0x0001 + x) & 0x00ff, y);
        a = 0x30;
        if (x == 0xB0) {
            goto L_00033C;
        }
    }
    myMapper->writeCPU((0x0008 + x) & 0x00ff, y);
L_00033C:
    pushAddress(0x833E);
    SUB_00076B();
    if (handleReturnAddress(poppedEntry.value, 0x833E)) return;
    if (flgC) {
        goto L_000346;
    }
    x = myMapper->readCPU(0x00AC);
    myMapper->writeCPU(0x4000 + x, a);
L_000346:
    popAddress();
}

void game::SUB_000347() {
    opINY(1);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU((0x0004 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y));
    popAddress();
}

void game::SUB_000352() {
    a = myMapper->readCPU((0x0006 + x) & 0x00ff);
    flgC = false;
    opADC(0x01);
    opINY(1);
    opCMP(a, myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y));
    if (!flgZ) {
        if (flgN) {
            goto L_000361;
        }
        flgC = true;
        opSBC(0x01);
    L_000361:
        myMapper->writeCPU((0x0006 + x) & 0x00ff, a);
        opINY(1);
        myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y));
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
        jump(0x8383);
        return;
    }
    myMapper->writeCPU((0x0006 + x) & 0x00ff, 0x00);
    opINY(3);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x00BA));
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x00BB));
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
    SUB_000383();
    return;
}

void game::SUB_000383() {
    a = 0x01;
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    jump(0x83D3);
    return;
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
        if (flgZ) {
            goto L_0003A6;
        }
        opDEC(0x0095, 1);
        a = myMapper->readCPU(0x0095);
        opAND(0x0F);
        if (!flgZ) {
            goto L_0003AF;
        }
    L_0003A6:
        myMapper->writeCPU(0x00E2, 0x00);
        a = myMapper->readCPU(0x0060);
        setLoadFlag(a);
        pushAddress(0x83AE);
        SUB_000187();
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
            SUB_0003D3();
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
    SUB_0003D3();
    return;
}

void game::SUB_0003D3() {
    y = 0x00;
    myMapper->writeCPU(0x00BA, myMapper->readCPU((0x0003 + x) & 0x00ff));
    a = myMapper->readCPU((0x0004 + x) & 0x00ff);
    myMapper->writeCPU(0x00BB, a);
    opDEC((0x0000 + x) & 0x00ff, 1);
    if (!flgZ) {
        jump(0x83E4);
        return;
    }
    jump(0x847D);
    return;
}

void game::SUB_0003E4() {
    a = myMapper->readCPU(0x0022);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x00EF, a);
        a = 0x54;
        if (a != myMapper->readCPU((0x0002 + x) & 0x00ff)) {
            goto L_000415;
        }
        jump(0x8562);
        return;
    }
    a = 0x1A;
    if (a != myMapper->readCPU(0x00C2)) {
        if (a == myMapper->readCPU(0x00D2)) {
            goto L_000400;
        }
        goto L_00046A;
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
        jump(0x8562);
        return;
    }
L_000415:
    opINC((0x0000 + x) & 0x00ff, 1);
    myMapper->writeCPU((0x0001 + x) & 0x00ff, y);
    if (0x54 != myMapper->readCPU(0x00D2)) {
        a = myMapper->readCPU((0x0001 + x) & 0x00ff);
        pushAddress(0x8424);
        SUB_00076B();
        if (handleReturnAddress(poppedEntry.value, 0x8424)) return;
        if (!flgC) {
            a = 0x30;
            x = myMapper->readCPU(0x00AC);
            myMapper->writeCPU(0x4000 + x, a);
            pushAddress(0x8430);
            SUB_0002B5();
            if (handleReturnAddress(poppedEntry.value, 0x8430)) return;
        }
        a = 0x30;
        myMapper->writeCPU(0x4004, a);
        pushAddress(0x8438);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x8438)) return;
    }
    else {
        a = 0x30;
        myMapper->writeCPU(0x4000, a);
        pushAddress(0x8443);
        SUB_0002B5();
        if (handleReturnAddress(poppedEntry.value, 0x8443)) return;
        a = myMapper->readCPU((0x0001 + x) & 0x00ff);
        pushAddress(0x8448);
        SUB_00076B();
        if (handleReturnAddress(poppedEntry.value, 0x8448)) return;
        if (!flgC) {
            a = 0x30;
            x = myMapper->readCPU(0x00AC);
            myMapper->writeCPU(0x4000 + x, a);
            pushAddress(0x8454);
            SUB_0002B5();
            if (handleReturnAddress(poppedEntry.value, 0x8454)) return;
        }
    }
    a = 0x00;
    myMapper->writeCPU(0x4008, a);
    pushAddress(0x845C);
    SUB_0002B5();
    if (handleReturnAddress(poppedEntry.value, 0x845C)) return;
    a = 0x30;
    myMapper->writeCPU(0x400C, a);
    pushAddress(0x8464);
    SUB_0002B5();
    if (handleReturnAddress(poppedEntry.value, 0x8464)) return;
    myMapper->writeCPU(0x00EE, 0x00);
    popAddress();
    return;
L_00046A:
    a = myMapper->readCPU(0x00EF);
    setLoadFlag(a);
    if (flgZ) {
        goto L_000471;
    }
    pushAddress(0x8470);
    SUB_000478();
    if (handleReturnAddress(poppedEntry.value, 0x8470)) return;
L_000471:
    a = 0x00;
    myMapper->writeCPU(0x00EF, a);
    jump(0x8562);
    return;
}

void game::SUB_000478() {
    myMapper->writeCPU(0x0081, 0x00);
    popAddress();
}

void game::SUB_00047D() {
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    opCMP(a, 0xFD);
    if (flgC) {
        if (!flgZ) {
            goto L_0004A0;
        }
        x = myMapper->readCPU(0x00AB);
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opORA(0x08);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
        pushAddress(0x848F);
        SUB_000347();
        if (handleReturnAddress(poppedEntry.value, 0x848F)) return;
        opINY(1);
        a = y;
        flgC = false;
        opADC(myMapper->readCPU(0x00BA));
        myMapper->writeCPU((0x000E + x) & 0x00ff, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x00BB));
        myMapper->writeCPU((0x000F + x) & 0x00ff, a);
        jump(0x8383);
        return;
    L_0004A0:
        if (a == 0xFE) {
            jump(0x8352);
            return;
        }
        if (x != 0xB0) {
            a = myMapper->readCPU((0x0008 + x) & 0x00ff);
            opAND(0x08);
            if (!flgZ) {
                goto L_0004B4;
            }
        }
        jump(0x82BF);
        return;
    L_0004B4:
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opAND(0xF7);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
        myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU((0x000E + x) & 0x00ff));
        a = myMapper->readCPU((0x000F + x) & 0x00ff);
        myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
        jump(0x8383);
        return;
    }
    if (x != 0xB0) {
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opAND(0x01);
        if (!flgZ) {
            jump(0x85C2);
            return;
        }
    }
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        opAND(0xF0);
        if (a == 0x20) {
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            opAND(0x0F);
            myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            pushAddress(0x84E5);
            SUB_00076B();
            if (handleReturnAddress(poppedEntry.value, 0x84E5)) return;
            if (!flgC) {
                x = myMapper->readCPU(0x00AC);
                myMapper->writeCPU(0x4000 + x, a);
            }
            x = myMapper->readCPU(0x00AB);
            if (x == 0xA0) {
                goto L_0004F5;
            }
            myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
        L_0004F5:
            opINY(1);
        }
        myMapper->writeCPU((0x0000 + x) & 0x00ff, myMapper->readCPU((0x0009 + x) & 0x00ff));
        if (x == 0xA0) {
            goto L_00054F;
        }
        a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        if (a != 0x11) {
            goto L_00050E;
        }
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opORA(0x10);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
        opINY(1);
    }
L_00050E:
    if (a == 0x10) {
        pushAddress(0x8514);
        SUB_000755();
        if (handleReturnAddress(poppedEntry.value, 0x8514)) return;
        opINY(1);
        pushAddress(0x8518);
        SUB_00076B();
        if (handleReturnAddress(poppedEntry.value, 0x8518)) return;
        if (!flgC) {
            x = myMapper->readCPU(0x00AC);
            myMapper->writeCPU(0x4001 + x, a);
        }
        x = myMapper->readCPU(0x00AB);
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opORA(0x80);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
    }
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x10);
    if (!flgZ) {
        a = myMapper->readCPU((0x0007 + x) & 0x00ff);
        opAND(0xF0);
        myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
        a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        if (a == 0xF8) {
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        }
        opLSR_A(4);
        opORA(myMapper->readCPU((0x0007 + x) & 0x00ff));
        myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
        pushAddress(0x8547);
        SUB_00076B();
        if (handleReturnAddress(poppedEntry.value, 0x8547)) return;
        if (flgC) {
            goto L_00054F;
        }
        x = myMapper->readCPU(0x00AC);
        myMapper->writeCPU(0x4000 + x, a);
    }
L_00054F:
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    opAND(0x07);
    myMapper->writeCPU(0x00BC, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00BD, a);
    x = myMapper->readCPU(0x00AB);
    pushAddress(0x855E);
    SUB_0006E4();
    if (handleReturnAddress(poppedEntry.value, 0x855E)) return;
    jump(0x8743);
    return;
}

void game::SUB_000562() {
    if (x == 0xB0) {
        goto L_00056C;
    }
    a = myMapper->readCPU((0x0008 + x) & 0x00ff);
    opAND(0x01);
    if (!flgZ) {
        goto L_00056D;
    }
L_00056C:
    popAddress();
    return;
L_00056D:
    if (x == 0xA0) {
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x00BA) == 0) {
        opDEC(0x00BB, 1);
    }
    opDEC(0x00BA, 1);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    if (a == 0xC0) {
        popAddress();
        return;
    }
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x10);
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU((0x000B + x) & 0x00ff);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU((0x000B + x) & 0x00ff, a);
    if (a == myMapper->readCPU((0x0000 + x) & 0x00ff)) {
        flgC = true;
        opSBC(myMapper->readCPU((0x000D + x) & 0x00ff));
        if (!flgC) {
            goto L_0005A4;
        }
        if (flgZ) {
            goto L_0005A4;
        }
        popAddress();
        return;
    }
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU((0x000B + x) & 0x00ff, a);
L_0005A4:
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opAND(0x0F);
    flgC = true;
    opSBC(0x01);
    if (flgN) {
        popAddress();
        return;
    }
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opSBC(0x01);
    myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
    pushAddress(0x85B6);
    SUB_00076B();
    if (handleReturnAddress(poppedEntry.value, 0x85B6)) return;
    if (flgC) {
        goto L_0005BE;
    }
    x = myMapper->readCPU(0x00AC);
    myMapper->writeCPU(0x4000 + x, a);
L_0005BE:
    popAddress();
}

void game::SUB_0005C2() {
    while (true) {
        a = myMapper->readCPU(0x0022);
        setLoadFlag(a);
        if (flgZ) {
            a = 0x1A;
            if (a != myMapper->readCPU(0x00C2)) {
                if (a != myMapper->readCPU(0x00D2)) {
                    goto L_0005D3;
                }
            }
        }
        jump(0x83E4);
        return;
    L_0005D3:
        a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        opAND(0xF0);
        if (a == 0xD0) {
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            opAND(0x0F);
            myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
            opINY(1);
            if (myMapper->readCPU(0x00E2) != 0) {
                a = myMapper->readCPU((0x0005 + x) & 0x00ff);
                opAND(0x0F);
                myMapper->writeCPU(0x00E8, a);
                a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
                opAND(0xF0);
                flgC = false;
                opADC(myMapper->readCPU(0x00E8));
            }
            else {
                a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            }
            myMapper->writeCPU((0x0005 + x) & 0x00ff, a);
            opINY(1);
            if (x == 0xA0) {
                goto L_00062E;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            opLSR_A(4);
            myMapper->writeCPU((0x000C + x) & 0x00ff, a);
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            opAND(0x0F);
            myMapper->writeCPU((0x000D + x) & 0x00ff, a);
            opINY(1);
        }
        if (x != 0xA0) {
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            if (a == 0xF0) {
                pushAddress(0x861A);
                SUB_000755();
                if (handleReturnAddress(poppedEntry.value, 0x861A)) return;
                pushAddress(0x861D);
                SUB_00076B();
                if (handleReturnAddress(poppedEntry.value, 0x861D)) return;
                if (flgC) {
                    goto L_000625;
                }
                x = myMapper->readCPU(0x00AC);
                myMapper->writeCPU(0x4001 + x, a);
            L_000625:
                x = myMapper->readCPU(0x00AB);
                a = myMapper->readCPU((0x0008 + x) & 0x00ff);
                opORA(0x80);
                myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
                opINY(1);
            }
        }
        while (true) {
        L_00062E:
            a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
            if (a == 0xE8) {
                goto L_00065D;
            }
            if (a != 0xE9) {
                if (a == 0xEA) {
                    goto L_00064C;
                }
                opAND(0xF0);
                if (a != 0xE0) {
                    goto L_000667;
                }
                a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
                opAND(0x0F);
                myMapper->writeCPU((0x000A + x) & 0x00ff, a);
                opINY(1);
                jump(0x847D);
                return;
            L_00064C:
                a = 0x01;
                setLoadFlag(a);
            }
            else {
                a = 0x02;
                setLoadFlag(a);
                goto L_000656;
            }
        L_000656:
            pushAddress(0x8658);
            SUB_000187();
            if (handleReturnAddress(poppedEntry.value, 0x8658)) return;
            opINY(1);
        }
    L_00065D:
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opORA(0x10);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
        opINY(1);
    }
L_000667:
    pushAddress(0x8669);
    SUB_000743();
    if (handleReturnAddress(poppedEntry.value, 0x8669)) return;
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    opAND(0x0F);
    myMapper->writeCPU(0x00BC, a);
    if (!flgZ) {
        a = myMapper->readCPU((0x0009 + x) & 0x00ff);
        flgC = false;
        do {
            opADC(myMapper->readCPU((0x0009 + x) & 0x00ff));
            opDEC(0x00BC, 1);
        } while (!flgZ);
        if (flgZ) {
            goto L_000680;
        }
    }
    a = myMapper->readCPU((0x0009 + x) & 0x00ff);
L_000680:
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    if (a != 0xC0) {
        if (x == 0xA0) {
            goto L_000695;
        }
        a = myMapper->readCPU((0x0000 + x) & 0x00ff);
        flgC = false;
        opADC(myMapper->readCPU((0x000C + x) & 0x00ff));
        myMapper->writeCPU((0x000B + x) & 0x00ff, a);
    L_000695:
        a = myMapper->readCPU((0x0005 + x) & 0x00ff);
        if (x != 0xA0) {
            myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
        }
        pushAddress(0x869F);
        SUB_00076B();
        if (handleReturnAddress(poppedEntry.value, 0x869F)) return;
        if (!flgC) {
            x = myMapper->readCPU(0x00AC);
            myMapper->writeCPU(0x4000 + x, a);
        }
        x = myMapper->readCPU(0x00AC);
        a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
        opLSR_A(4);
        if (a != 0x0C) {
            goto L_0006C6;
        }
    }
    a = 0x00;
    if (x != 0x08) {
        a = 0x30;
    }
    pushAddress(0x86BD);
    SUB_00076B();
    if (handleReturnAddress(poppedEntry.value, 0x86BD)) return;
    if (flgC) {
        goto L_0006C5;
    }
    x = myMapper->readCPU(0x00AC);
    myMapper->writeCPU(0x4000 + x, a);
L_0006C5:
    popAddress();
    return;
L_0006C6:
    x = myMapper->readCPU(0x00AB);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00BC, myMapper->readCPU(0x878A + y));
    opINY(1);
    myMapper->writeCPU(0x00BD, myMapper->readCPU(0x878A + y));
    y = myMapper->readCPU((0x000A + x) & 0x00ff);
    while (true) {
        a = y;
        if (a == 0x04) {
            jump(0x86E4);
            return;
        }
        opLSR_M(0x00BC, 1);
        opROR_M(0x00BD, 1);
        opINY(1);
    }
    SUB_0006E4();
    return;
}

void game::SUB_0006E4() {
    if (x >= 0xA0) {
        goto L_0006F4;
    }
    a = myMapper->readCPU((0x0008 + x) & 0x00ff);
    opAND(0x10);
    if (!flgZ) {
        opINC(0x00BD, 1);
        if (flgZ) {
            opINC(0x00BC, 1);
        }
    }
L_0006F4:
    a = myMapper->readCPU(0x00BC);
    opORA(0x08);
    myMapper->writeCPU(0x00BC, a);
    if (x != 0xA0) {
        if (a != myMapper->readCPU((0x0001 + x) & 0x00ff)) {
            goto L_000714;
        }
        if (x == 0xB0) {
            goto L_000724;
        }
        a = myMapper->readCPU((0x0007 + x) & 0x00ff);
        opAND(0x10);
        if (flgZ) {
            goto L_000716;
        }
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opAND(0x80);
        if (!flgZ) {
            goto L_000716;
        }
        if (flgZ) {
            goto L_000724;
        }
    L_000714:
        myMapper->writeCPU((0x0001 + x) & 0x00ff, a);
    }
L_000716:
    a = myMapper->readCPU(0x00BC);
    pushAddress(0x871A);
    SUB_00076B();
    if (handleReturnAddress(poppedEntry.value, 0x871A)) return;
    if (!flgC) {
        x = myMapper->readCPU(0x00AC);
        myMapper->writeCPU(0x4003 + x, a);
        x = myMapper->readCPU(0x00AB);
    }
L_000724:
    a = myMapper->readCPU(0x00BD);
    if (x != 0x80) {
        if (x == 0x90) {
            goto L_000736;
        }
    }
    else {
        myMapper->writeCPU(0x00A7, a);
        goto L_000738;
    L_000736:
        myMapper->writeCPU(0x00B8, a);
    }
L_000738:
    pushAddress(0x873A);
    SUB_00076B();
    if (handleReturnAddress(poppedEntry.value, 0x873A)) return;
    if (flgC) {
        goto L_000742;
    }
    x = myMapper->readCPU(0x00AC);
    myMapper->writeCPU(0x4002 + x, a);
L_000742:
    popAddress();
}

void game::SUB_000743() {
    opINY(1);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x00BA));
    x = myMapper->readCPU(0x00AB);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    if (!flgC) {
        goto L_000754;
    }
    a = myMapper->readCPU(0x00BB);
    opADC(0x00);
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
L_000754:
    popAddress();
}

void game::SUB_000755() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BA) + (myMapper->readCPU((0x00BA + 1) & 0x00ff) << 8) + y);
    if (x == 0x80) {
        goto L_000763;
    }
    if (x == 0x90) {
        goto L_000768;
    }
    goto L_00076A;
L_000763:
    myMapper->writeCPU(0x00A1, a);
    goto L_00076A;
L_000768:
    myMapper->writeCPU(0x00B5, a);
L_00076A:
    popAddress();
}

void game::SUB_00076B() {
    if (myMapper->readCPU(0x00AB) != 0x80) {
        goto L_000778;
    }
    x = myMapper->readCPU(0x00C2);
    setLoadFlag(x);
    if (flgZ) {
        goto L_000786;
    }
    goto L_000782;
L_000778:
    if (myMapper->readCPU(0x00AB) != 0x90) {
        goto L_000786;
    }
    if (myMapper->readCPU(0x00D2) == 0) {
        goto L_000786;
    }
L_000782:
    x = myMapper->readCPU(0x00AB);
    flgC = true;
    popAddress();
    return;
L_000786:
    x = myMapper->readCPU(0x00AB);
    flgC = false;
    popAddress();
}

void game::SUB_01934C() {
    a = myMapper->readCPU(0x0047);
    setLoadFlag(a);
    if (flgZ) {
        goto L_019363;
    }
    opDEC(0x0047, 1);
    pushAddress(0x9354);
    SUB_019A5B();
    if (handleReturnAddress(poppedEntry.value, 0x9354)) return;
    myMapper->writeCPU(0x0049, 0x00);
    x = myMapper->readCPU(0x0159);
    a = myMapper->readCPU(0x9BF1 + x);
    x = a;
    jump(0x9BE3);
    return;
L_019363:
    pushAddress(0x9365);
    SUB_0199F0();
    if (handleReturnAddress(poppedEntry.value, 0x9365)) return;
    a = myMapper->readCPU(0x046C);
    pushAddress(0x936B);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x936B)) return;
    SUB_019380();
    return;
}

void game::SUB_019380() {
    a = myMapper->readCPU(0x0045);
    setLoadFlag(a);
    if (!flgZ) {
        if (!flgN) {
            goto L_019389;
        }
    }
    jump(0xA1E5);
    return;
L_019389:
    pushAddress(0x938B);
    SUB_019A1D();
    if (handleReturnAddress(poppedEntry.value, 0x938B)) return;
    if (flgC) {
        popAddress();
        return;
    }
    pushAddress(0x9391);
    SUB_019A62();
    if (handleReturnAddress(poppedEntry.value, 0x9391)) return;
    pushAddress(0x9394);
    SUB_019F7A();
    if (handleReturnAddress(poppedEntry.value, 0x9394)) return;
    if (flgC) {
        opPLA();
        opPLA();
        a = 0x00;
        myMapper->writeCPU(0x0019, a);
        myMapper->writeCPU(0x0140, a);
        myMapper->writeCPU(0x0018, 0x08);
        if (myMapper->readCPU(0x0028) != 0x0A) {
            goto L_0193BA;
        }
        x = 0x05;
        myMapper->writeCPU(0x0018, x);
        myMapper->writeCPU(0x001F, x);
        a = 0x01;
        myMapper->writeCPU(0x0140, a);
        opINC(0x0028, 1);
        pushAddress(0x93B9);
        SUB_01C998();
        if (handleReturnAddress(poppedEntry.value, 0x93B9)) return;
    L_0193BA:
        popAddress();
        return;
    }
    pushAddress(0x93BD);
    SUB_01AC70();
    if (handleReturnAddress(poppedEntry.value, 0x93BD)) return;
    if (flgC) {
        jump(0x93D9);
        return;
    }
    pushAddress(0x93C2);
    SUB_019E70();
    if (handleReturnAddress(poppedEntry.value, 0x93C2)) return;
    if (flgC) {
        jump(0x93D9);
        return;
    }
    SUB_0193C5();
    return;
}

void game::SUB_0193C5() {
    a = 0x00;
    myMapper->writeCPU(0x0143, a);
    myMapper->writeCPU(0x0049, a);
    x = myMapper->readCPU(0x0450);
    opINX(1);
    myMapper->writeCPU(0x0584, x);
    myMapper->writeCPU(0x046C, 0x07);
    popAddress();
}

void game::SUB_0193D9() {
    a = myMapper->readCPU(0x00F7);
    myMapper->writeCPU(0x0584, a);
    pushAddress(0x93E0);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x93E0)) return;
    pushAddress(0x93E3);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x93E3)) return;
    myMapper->writeCPU(0x0434, 0x00);
    a = myMapper->readCPU(0x00F7);
    opAND(0x0C);
    if (!flgZ) {
        a = 0x00;
        pushAddress(0x93F3);
        SUB_019C10();
        if (handleReturnAddress(poppedEntry.value, 0x93F3)) return;
        if (flgC) {
            myMapper->writeCPU(0x04DC, 0x10);
            myMapper->writeCPU(0x054C, 0x00);
            popAddress();
            return;
        }
    }
    a = myMapper->readCPU(0x00F5);
    opAND(0x80);
    if (!flgZ) {
        pushAddress(0x9409);
        SUB_019998();
        if (handleReturnAddress(poppedEntry.value, 0x9409)) return;
        if (!flgC) {
            jump(0x9458);
            return;
        }
        myMapper->writeCPU(0x04DC, myMapper->readCPU(0x9B8D));
        myMapper->writeCPU(0x04F8, myMapper->readCPU(0x9B8E));
        a = 0x00;
        myMapper->writeCPU(0x0514, a);
        myMapper->writeCPU(0x0143, a);
        opINC(0x046C, 1);
        myMapper->writeCPU(0x0488, a);
        myMapper->writeCPU(0x054C, a);
        a = myMapper->readCPU(0x00F7);
        opAND(0x03);
        y = a;
        setLoadFlag(y);
        if (flgZ) {
            y = 0x00;
        }
        myMapper->writeCPU(0x0000, y);
        pushAddress(0x9436);
        SUB_019A5B();
        if (handleReturnAddress(poppedEntry.value, 0x9436)) return;
        opORA(myMapper->readCPU(0x0000));
        myMapper->writeCPU(0x003C, a);
        popAddress();
        return;
    }
    x = 0x01;
    pushAddress(0x9440);
    SUB_019A2A();
    if (handleReturnAddress(poppedEntry.value, 0x9440)) return;
    if (!flgC) {
        goto L_01944A;
    }
    opINC(0x046C, 2);
    popAddress();
    return;
L_01944A:
    a = myMapper->readCPU(0x00F7);
    opAND(0x04);
    if (flgZ) {
        jump(0x9458);
        return;
    }
    a = 0x03;
    myMapper->writeCPU(0x046C, a);
    jump(0x9A69);
    return;
}

void game::SUB_019458() {
    a = myMapper->readCPU(0x0584);
    opAND(0x03);
    if (!flgZ) {
        opLSR_A(1);
        myMapper->writeCPU(0x0450, a);
        a = myMapper->readCPU(0x0530);
        flgC = false;
        opADC(0x24);
        myMapper->writeCPU(0x0530, a);
        if (!flgC) {
            goto L_019471;
        }
        opINC(0x04A4, 1);
    L_019471:
        a = myMapper->readCPU(0x04A4);
        opAND(0x03);
    }
    jump(0x9BBA);
    return;
}

void game::SUB_019479() {
    a = 0x00;
    y = 0x01;
    SUB_01947D();
    return;
}

void game::SUB_01947D() {
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x003E, y);
    popAddress();
}

void game::SUB_019482() {
    a = myMapper->readCPU(0x003F);
    flgC = true;
    opSBC(0xE0);
    if (a < 0x10) {
        jump(0xA1E5);
        return;
    }
    pushAddress(0x9490);
    SUB_019479();
    if (handleReturnAddress(poppedEntry.value, 0x9490)) return;
    pushAddress(0x9493);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x9493)) return;
    pushAddress(0x9496);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x9496)) return;
    a = myMapper->readCPU(0x054C);
    setLoadFlag(a);
    if (flgZ) {
        x = 0x03;
        pushAddress(0x94A0);
        SUB_019A2A();
        if (handleReturnAddress(poppedEntry.value, 0x94A0)) return;
        if (!flgC) {
            goto L_0194AB;
        }
        a = 0x01;
        opINC(0x054C, 1);
    }
    goto L_019502;
L_0194AB:
    myMapper->writeCPU(0x0434, 0x00);
    x = 0x00;
    opINC(0x0488, 1);
    a = myMapper->readCPU(0x0488);
    flgC = true;
    opSBC(0x04);
    if (a >= 0x1C) {
        goto L_0194C1;
    }
    x = 0x04;
L_0194C1:
    a = x;
    pushAddress(0x94C4);
    SUB_019BBA();
    if (handleReturnAddress(poppedEntry.value, 0x94C4)) return;
    do {
        do {
            a = 0x00;
            pushAddress(0x94C9);
            SUB_019B1E();
            if (handleReturnAddress(poppedEntry.value, 0x94C9)) return;
            a = myMapper->readCPU(0x0514);
            setLoadFlag(a);
            if (!flgZ) {
                pushAddress(0x94D1);
                SUB_019E70();
                if (handleReturnAddress(poppedEntry.value, 0x94D1)) return;
                if (flgC) {
                    goto L_0194DA;
                }
                pushAddress(0x94D6);
                SUB_01AC70();
                if (handleReturnAddress(poppedEntry.value, 0x94D6)) return;
                if (flgC) {
                    goto L_0194DA;
                }
            }
            popAddress();
            return;
        L_0194DA:
            pushAddress(0x94DC);
            SUB_019A62();
            if (handleReturnAddress(poppedEntry.value, 0x94DC)) return;
            if (myMapper->readCPU(0x054C) == 0) {
                goto L_0194F7;
            }
            myMapper->writeCPU(0x046C, 0x02);
            myMapper->writeCPU(0x0530, 0x00);
            a = myMapper->readCPU(0x0434);
            opAND(0x80);
            opORA(0x01);
            myMapper->writeCPU(0x0434, a);
            popAddress();
            return;
        L_0194F7:
            a = 0x00;
            myMapper->writeCPU(0x046C, a);
            pushAddress(0x94FE);
            SUB_019AF8();
            if (handleReturnAddress(poppedEntry.value, 0x94FE)) return;
            jump(0x9782);
            return;
        L_019502:
            pushAddress(0x9504);
            SUB_019A71();
            if (handleReturnAddress(poppedEntry.value, 0x9504)) return;
        } while (!flgC);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x054C, a);
        myMapper->writeCPU(0x0434, a);
    } while (flgZ);
    SUB_019511();
    return;
}

void game::SUB_019511() {
    pushAddress(0x9513);
    SUB_019A1D();
    if (handleReturnAddress(poppedEntry.value, 0x9513)) return;
    if (flgC) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00F7);
    opAND(0xFC);
    myMapper->writeCPU(0x0584, a);
    pushAddress(0x9520);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x9520)) return;
    pushAddress(0x9523);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x9523)) return;
    pushAddress(0x9526);
    SUB_019A71();
    if (handleReturnAddress(poppedEntry.value, 0x9526)) return;
    if (flgC) {
        goto L_01952A;
    }
    popAddress();
    return;
L_01952A:
    pushAddress(0x952C);
    SUB_019AF8();
    if (handleReturnAddress(poppedEntry.value, 0x952C)) return;
    myMapper->writeCPU(0x0434, 0x00);
    myMapper->writeCPU(0x046C, myMapper->readCPU(0x0530));
    popAddress();
}

void game::SUB_019539() {
    pushAddress(0x953B);
    SUB_019A1D();
    if (handleReturnAddress(poppedEntry.value, 0x953B)) return;
    if (flgC) {
        popAddress();
        return;
    }
    pushAddress(0x9541);
    SUB_01AC70();
    if (handleReturnAddress(poppedEntry.value, 0x9541)) return;
    if (!flgC) {
        pushAddress(0x9546);
        SUB_019E70();
        if (handleReturnAddress(poppedEntry.value, 0x9546)) return;
        if (!flgC) {
            jump(0x93C5);
            return;
        }
    }
    a = 0x04;
    myMapper->writeCPU(0x0584, a);
    pushAddress(0x9553);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x9553)) return;
    pushAddress(0x9556);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x9556)) return;
    a = myMapper->readCPU(0x00F7);
    opAND(0x03);
    if (!flgZ) {
        opLSR_A(1);
        myMapper->writeCPU(0x0450, a);
    }
    a = myMapper->readCPU(0x00F7);
    opAND(0x04);
    if (flgZ) {
        jump(0x9578);
        return;
    }
    x = 0x02;
    pushAddress(0x956B);
    SUB_019A2A();
    if (handleReturnAddress(poppedEntry.value, 0x956B)) return;
    if (!flgC) {
        goto L_019574;
    }
    myMapper->writeCPU(0x046C, 0x02);
    popAddress();
    return;
L_019574:
    a = 0x04;
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x9583);
        return;
    }
    SUB_019578();
    return;
}

void game::SUB_019578() {
    a = 0xFC;
    pushAddress(0x957C);
    SUB_019A6B();
    if (handleReturnAddress(poppedEntry.value, 0x957C)) return;
    myMapper->writeCPU(0x046C, 0x00);
    popAddress();
}

void game::SUB_019583() {
    jump(0x9BBA);
    return;
}

void game::SUB_019586() {
    a = myMapper->readCPU(0x0045);
    setLoadFlag(a);
    if (!flgZ) {
        pushAddress(0x958C);
        SUB_019A1D();
        if (handleReturnAddress(poppedEntry.value, 0x958C)) return;
        if (!flgC) {
            goto L_019592;
        }
    }
    jump(0x93C5);
    return;
L_019592:
    a = 0x80;
    y = 0x00;
    pushAddress(0x9598);
    SUB_01947D();
    if (handleReturnAddress(poppedEntry.value, 0x9598)) return;
    a = myMapper->readCPU(0x054C);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x003F);
        opAND(0x07);
        flgC = true;
        opSBC(0x02);
        if (a < 0x04) {
            goto L_0195C2;
        }
        x = 0x01;
        pushAddress(0x95AD);
        SUB_019A2A();
        if (handleReturnAddress(poppedEntry.value, 0x95AD)) return;
        if (!flgC) {
            goto L_0195C2;
        }
        a = 0x01;
        myMapper->writeCPU(0x054C, a);
    }
    pushAddress(0x95B7);
    SUB_019A71();
    if (handleReturnAddress(poppedEntry.value, 0x95B7)) return;
    if (flgC) {
        a = 0x00;
        myMapper->writeCPU(0x054C, a);
        myMapper->writeCPU(0x0434, a);
    }
L_0195C2:
    pushAddress(0x95C4);
    SUB_019A5B();
    if (handleReturnAddress(poppedEntry.value, 0x95C4)) return;
    a = myMapper->readCPU(0x054C);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x003F);
        opAND(0x07);
        if (!flgZ) {
            goto L_0195D8;
        }
        a = myMapper->readCPU(0x00F7);
        myMapper->writeCPU(0x0584, a);
        pushAddress(0x95D7);
        SUB_019C6F();
        if (handleReturnAddress(poppedEntry.value, 0x95D7)) return;
    L_0195D8:
        pushAddress(0x95DA);
        SUB_019C6F();
        if (handleReturnAddress(poppedEntry.value, 0x95DA)) return;
        pushAddress(0x95DD);
        SUB_019809();
        if (handleReturnAddress(poppedEntry.value, 0x95DD)) return;
        pushAddress(0x95E0);
        SUB_019D96();
        if (handleReturnAddress(poppedEntry.value, 0x95E0)) return;
    }
    pushAddress(0x95E3);
    SUB_01962D();
    if (handleReturnAddress(poppedEntry.value, 0x95E3)) return;
    SUB_0195E4();
    return;
}

void game::SUB_0195E4() {
    pushAddress(0x95E6);
    SUB_019FF3();
    if (handleReturnAddress(poppedEntry.value, 0x95E6)) return;
    if (!flgC) {
        goto L_0195F6;
    }
    a = 0x05;
    myMapper->writeCPU(0x0018, a);
    myMapper->writeCPU(0x004A, a);
    myMapper->writeCPU(0x001F, a);
    a = 0x00;
    myMapper->writeCPU(0x0019, a);
    popAddress();
    return;
L_0195F6:
    a = myMapper->readCPU(0x003F);
    if (a == 0xB8) {
        jump(0x962C);
        return;
    }
    opAND(0x0F);
    if (!flgZ) {
        jump(0x962C);
        return;
    }
    pushAddress(0x9602);
    SUB_019E70();
    if (handleReturnAddress(poppedEntry.value, 0x9602)) return;
    if (!flgC) {
        jump(0x962C);
        return;
    }
    SUB_019605();
    return;
}

void game::SUB_019605() {
    a = 0x00;
    myMapper->writeCPU(0x002D, a);
    pushAddress(0x960B);
    SUB_019479();
    if (handleReturnAddress(poppedEntry.value, 0x960B)) return;
    pushAddress(0x960E);
    SUB_019A62();
    if (handleReturnAddress(poppedEntry.value, 0x960E)) return;
    if (myMapper->readCPU(0x054C) == 0) {
        goto L_019624;
    }
    myMapper->writeCPU(0x046C, 0x02);
    myMapper->writeCPU(0x0530, 0x00);
    a = 0x01;
    myMapper->writeCPU(0x0434, a);
    popAddress();
    return;
L_019624:
    a = 0x00;
    myMapper->writeCPU(0x046C, a);
    jump(0x9AF8);
    return;
}

void game::SUB_01962C() {
    popAddress();
}

void game::SUB_01962D() {
    a = myMapper->readCPU(0x003F);
    x = 0x00;
    opAND(0x07);
    flgC = true;
    opSBC(0x02);
    if (a < 0x04) {
        goto L_01963B;
    }
    opINX(1);
L_01963B:
    a = x;
    x = myMapper->readCPU(0x0514);
    flgC = false;
    opADC(myMapper->readCPU(0x9653 + x));
    y = a;
    myMapper->writeCPU(0x0450, myMapper->readCPU(0x9657 + x));
    a = myMapper->readCPU(0x054C);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x95E4);
        return;
    }
    a = y;
    jump(0x9BBA);
    return;
}

void game::SUB_01965B() {
    a = myMapper->readCPU(0x054C);
    setLoadFlag(a);
    if (!flgN) {
        opDEC(0x054C, 1);
        x = 0x00;
        myMapper->writeCPU(0x0049, x);
        pushAddress(0x9669);
        SUB_019A5B();
        if (handleReturnAddress(poppedEntry.value, 0x9669)) return;
        jump(0x962C);
        return;
    }
    a = myMapper->readCPU(0x003F);
    if (a >= 0xE0) {
        jump(0xA1E5);
        return;
    }
    pushAddress(0x9678);
    SUB_01970B();
    if (handleReturnAddress(poppedEntry.value, 0x9678)) return;
    pushAddress(0x967B);
    SUB_019479();
    if (handleReturnAddress(poppedEntry.value, 0x967B)) return;
    pushAddress(0x967E);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x967E)) return;
    pushAddress(0x9681);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x9681)) return;
    myMapper->writeCPU(0x0434, 0x00);
    a = 0x12;
    pushAddress(0x968B);
    SUB_019BBA();
    if (handleReturnAddress(poppedEntry.value, 0x968B)) return;
    a = 0x00;
    pushAddress(0x9690);
    SUB_019B1E();
    if (handleReturnAddress(poppedEntry.value, 0x9690)) return;
    a = myMapper->readCPU(0x0514);
    setLoadFlag(a);
    if (!flgZ) {
        pushAddress(0x9698);
        SUB_019E70();
        if (handleReturnAddress(poppedEntry.value, 0x9698)) return;
        if (flgC) {
            goto L_0196A1;
        }
        pushAddress(0x969D);
        SUB_01AC70();
        if (handleReturnAddress(poppedEntry.value, 0x969D)) return;
        if (flgC) {
            goto L_0196A1;
        }
    }
    popAddress();
    return;
L_0196A1:
    a = 0xF0;
    pushAddress(0x96A5);
    SUB_019A64();
    if (handleReturnAddress(poppedEntry.value, 0x96A5)) return;
    a = myMapper->readCPU(0x0045);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0196AD;
    }
    jump(0xA1E5);
    return;
L_0196AD:
    a = 0x30;
    myMapper->writeCPU(0x005B, a);
    pushAddress(0x96B3);
    SUB_019AF8();
    if (handleReturnAddress(poppedEntry.value, 0x96B3)) return;
    myMapper->writeCPU(0x046C, 0x09);
    a = 0x10;
    myMapper->writeCPU(0x054C, a);
    jump(0x9A69);
    return;
}

void game::SUB_01970B() {
    a = myMapper->readCPU(0x0450);
    flgC = false;
    opADC(0x01);
    opEOR(0x03);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x9717);
    SUB_019A5B();
    if (handleReturnAddress(poppedEntry.value, 0x9717)) return;
    opORA(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x003C, a);
    popAddress();
}

void game::SUB_01971D() {
    jump(0x9605);
    return;
}

void game::SUB_019720() {
    pushAddress(0x9722);
    SUB_019A1D();
    if (handleReturnAddress(poppedEntry.value, 0x9722)) return;
    if (flgC) {
        popAddress();
        return;
    }
    opDEC(0x04DC, 1);
    if (flgN) {
        jump(0x971D);
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x0010, a);
    pushAddress(0x9731);
    SUB_019CBD();
    if (handleReturnAddress(poppedEntry.value, 0x9731)) return;
    if (flgC) {
        a = myMapper->readCPU(0x0008);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_019749;
        }
        pushAddress(0x973A);
        SUB_019C43();
        if (handleReturnAddress(poppedEntry.value, 0x973A)) return;
        pushAddress(0x973D);
        SUB_019A5B();
        if (handleReturnAddress(poppedEntry.value, 0x973D)) return;
        myMapper->writeCPU(0x03A8, 0x00);
        myMapper->writeCPU(0x0370, 0x80);
        popAddress();
        return;
    }
L_019749:
    pushAddress(0x974B);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x974B)) return;
    pushAddress(0x974E);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x974E)) return;
    a = 0x00;
    myMapper->writeCPU(0x0434, a);
    jump(0x9458);
    return;
}

void game::SUB_019757() {
    opINC(0x0143, 1);
    a = 0x00;
    pushAddress(0x975E);
    SUB_019BBA();
    if (handleReturnAddress(poppedEntry.value, 0x975E)) return;
    pushAddress(0x9761);
    SUB_01AC70();
    if (handleReturnAddress(poppedEntry.value, 0x9761)) return;
    if (flgC) {
        jump(0x977B);
        return;
    }
    pushAddress(0x9766);
    SUB_019E70();
    if (handleReturnAddress(poppedEntry.value, 0x9766)) return;
    if (flgC) {
        jump(0x977B);
        return;
    }
    pushAddress(0x976B);
    SUB_019809();
    if (handleReturnAddress(poppedEntry.value, 0x976B)) return;
    pushAddress(0x976E);
    SUB_01989A();
    if (handleReturnAddress(poppedEntry.value, 0x976E)) return;
    a = myMapper->readCPU(0x003F);
    if (a >= 0xE0) {
        jump(0x97A7);
        return;
    }
    a = 0x08;
    pushAddress(0x9779);
    SUB_019A6B();
    if (handleReturnAddress(poppedEntry.value, 0x9779)) return;
    SUB_01977A();
    return;
}

void game::SUB_01977A() {
    popAddress();
}

void game::SUB_01977B() {
    a = 0x00;
    myMapper->writeCPU(0x046C, a);
    myMapper->writeCPU(0x0049, a);
    SUB_019782();
    return;
}

void game::SUB_019782() {
    if (myMapper->readCPU(0x0028) == 0x0A) {
        goto L_01978D;
    }
    a = 0xF0;
    pushAddress(0x978C);
    SUB_019A64();
    if (handleReturnAddress(poppedEntry.value, 0x978C)) return;
L_01978D:
    a = myMapper->readCPU(0x0143);
    if (a < 0x08) {
        jump(0x977A);
        return;
    }
    pushAddress(0x9796);
    SUB_019A69();
    if (handleReturnAddress(poppedEntry.value, 0x9796)) return;
    a = 0x0D;
    pushAddress(0x979B);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0x979B)) return;
    myMapper->writeCPU(0x046C, 0x09);
    myMapper->writeCPU(0x054C, 0x10);
    popAddress();
}

void game::SUB_0197A7() {
    jump(0xA1E5);
    return;
}

void game::SUB_0197AA() {
    pushAddress(0x97AC);
    SUB_019A62();
    if (handleReturnAddress(poppedEntry.value, 0x97AC)) return;
    myMapper->writeCPU(0x0354, a);
    x = 0x00;
    myMapper->writeCPU(0x0049, x);
    myMapper->writeCPU(0x003C, x);
    myMapper->writeCPU(0x0000, 0x02);
    if (myMapper->readCPU(0x003F) < 0xE0) {
        if (myMapper->readCPU(0x001D) == 0) {
            goto L_0197C6;
        }
        opDEC(0x001D, 1);
    L_0197C6:
        a = myMapper->readCPU(0x001D);
        opLSR_A(4);
        opAND(0x01);
        myMapper->writeCPU(0x0000, a);
        flgC = false;
        opADC(0x98);
        x = a;
    }
    myMapper->writeCPU(0x031C, x);
    a = myMapper->readCPU(0x0000);
    flgC = false;
    opADC(0x1C);
    myMapper->writeCPU(0x0159, a);
    a = myMapper->readCPU(0x0082);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x97EA);
        return;
    }
    x = 0x06;
    myMapper->writeCPU(0x0018, x);
    opDEX(1);
    myMapper->writeCPU(0x001F, x);
    SUB_0197EA();
    return;
}

void game::SUB_0197EA() {
    popAddress();
}

void game::SUB_0197EB() {
    a = myMapper->readCPU(0x003C);
    opAND(0xFC);
    myMapper->writeCPU(0x003C, a);
    popAddress();
}

void game::SUB_0197F2() {
    pushAddress(0x97F4);
    SUB_019A1D();
    if (handleReturnAddress(poppedEntry.value, 0x97F4)) return;
    if (flgC) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00F7);
    opORA(0x04);
    myMapper->writeCPU(0x00F7, a);
    opDEC(0x054C, 1);
    if (flgN) {
        goto L_019806;
    }
    jump(0x9539);
    return;
L_019806:
    jump(0x9578);
    return;
}

void game::SUB_019809() {
    a = 0x00;
    myMapper->writeCPU(0x0049, a);
    pushAddress(0x980F);
    SUB_01AC70();
    if (handleReturnAddress(poppedEntry.value, 0x980F)) return;
    x = 0x00;
    if (!flgC) {
        opINX(1);
    }
    a = myMapper->readCPU(0x046C);
    if (a != 0x05) {
        a = myMapper->readCPU(0x0010);
        opDEX(1);
        if (flgZ) {
            a = myMapper->readCPU(0x0584);
        }
        opAND(0x03);
        myMapper->writeCPU(0x0010, a);
        pushAddress(0x982A);
        SUB_019A5B();
        if (handleReturnAddress(poppedEntry.value, 0x982A)) return;
        opORA(myMapper->readCPU(0x0010));
        myMapper->writeCPU(0x003C, a);
    }
    pushAddress(0x9831);
    SUB_019967();
    if (handleReturnAddress(poppedEntry.value, 0x9831)) return;
    a = myMapper->readCPU(0x0048);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x003C);
        opAND(0x03);
        opORA(0x04);
        myMapper->writeCPU(0x003C, a);
    }
    pushAddress(0x9840);
    SUB_019ECE();
    if (handleReturnAddress(poppedEntry.value, 0x9840)) return;
    if (flgC) {
        jump(0x97EB);
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (!flgZ) {
        jump(0x97EA);
        return;
    }
    if (myMapper->readCPU(0x003C) == 0x01) {
        a = myMapper->readCPU(0x003D);
        flgC = false;
        opADC(myMapper->readCPU(0x002D));
        a = myMapper->readCPU(0x003E);
        opADC(myMapper->readCPU(0x002E));
        myMapper->writeCPU(0x004B, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x002F));
        opPHA();
        pushAddress(0x9861);
        SUB_01D015();
        if (handleReturnAddress(poppedEntry.value, 0x9861)) return;
        myMapper->writeCPU(0x0000, a);
        opPLA();
        if (a != myMapper->readCPU(0x0000)) {
            goto L_019899;
        }
        y = myMapper->readCPU(0x004B);
        opDEY(1);
        if (flgZ) {
            goto L_019893;
        }
        if (!flgZ) {
            jump(0x98AA);
            return;
        }
    }
    y = myMapper->readCPU(0x002F);
    myMapper->writeCPU(0x004B, myMapper->readCPU(0x003E));
    a = myMapper->readCPU(0x002D);
    flgC = true;
    opSBC(myMapper->readCPU(0x003D));
    if (!flgC) {
        opINC(0x004B, 1);
    }
    a = myMapper->readCPU(0x002E);
    flgC = true;
    opSBC(myMapper->readCPU(0x004B));
    if (flgC) {
        goto L_019887;
    }
    opDEY(1);
L_019887:
    a = y;
    opPHA();
    pushAddress(0x988B);
    SUB_01D025();
    if (handleReturnAddress(poppedEntry.value, 0x988B)) return;
    myMapper->writeCPU(0x0000, a);
    opPLA();
    if (a != myMapper->readCPU(0x0000)) {
        jump(0x98AA);
        return;
    }
L_019893:
    a = 0x04;
    opORA(myMapper->readCPU(0x003C));
    myMapper->writeCPU(0x003C, a);
L_019899:
    popAddress();
}

void game::SUB_01989A() {
    pushAddress(0x989C);
    SUB_0198AB();
    if (handleReturnAddress(poppedEntry.value, 0x989C)) return;
    a = myMapper->readCPU(0x038C);
    if (a != 0x80) {
        jump(0x98AA);
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0xFB);
    myMapper->writeCPU(0x003C, a);
    SUB_0198AA();
    return;
}

void game::SUB_0198AA() {
    popAddress();
}

void game::SUB_0198AB() {
    a = myMapper->readCPU(0x003C);
    opAND(0x03);
    if (flgZ) {
        jump(0x990A);
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (flgZ) {
        jump(0x990B);
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x03);
    if (a == 0x01) {
        a = myMapper->readCPU(0x03A8);
        flgC = false;
        opADC(myMapper->readCPU(0x003D));
        y = a;
        a = myMapper->readCPU(0x038C);
        opADC(myMapper->readCPU(0x003E));
        if (a == 0xF0) {
            jump(0x990A);
            return;
        }
        myMapper->writeCPU(0x038C, a);
        myMapper->writeCPU(0x03A8, y);
        jump(0x98F3);
        return;
    }
    a = myMapper->readCPU(0x03A8);
    flgC = true;
    opSBC(myMapper->readCPU(0x003D));
    y = a;
    x = myMapper->readCPU(0x038C);
    if (flgC) {
        goto L_0198E5;
    }
    opDEX(1);
L_0198E5:
    a = x;
    flgC = true;
    opSBC(myMapper->readCPU(0x003E));
    if (a == 0x08) {
        jump(0x990A);
        return;
    }
    myMapper->writeCPU(0x038C, a);
    myMapper->writeCPU(0x03A8, y);
    SUB_0198F3();
    return;
}

void game::SUB_0198F3() {
    a = myMapper->readCPU(0x003C);
    x = 0x80;
    opAND(0x04);
    if (flgZ) {
        jump(0x98FE);
        return;
    }
    x = myMapper->readCPU(0x038C);
    SUB_0198FE();
    return;
}

void game::SUB_0198FE() {
    a = x;
    flgC = false;
    opADC(myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x0040, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x002F));
    myMapper->writeCPU(0x0041, a);
    SUB_01990A();
    return;
}

void game::SUB_01990A() {
    popAddress();
}

void game::SUB_01990B() {
    a = myMapper->readCPU(0x003C);
    setLoadFlag(a);
    if (!flgZ) {
        if (a != 0x01) {
            goto L_019919;
        }
        pushAddress(0x9915);
        SUB_01991F();
        if (handleReturnAddress(poppedEntry.value, 0x9915)) return;
        goto L_01991C;
    L_019919:
        pushAddress(0x991B);
        SUB_019944();
        if (handleReturnAddress(poppedEntry.value, 0x991B)) return;
    }
L_01991C:
    jump(0x98F3);
    return;
}

void game::SUB_01991F() {
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x002E));
    a = myMapper->readCPU(0x003D);
    flgC = false;
    opADC(myMapper->readCPU(0x002D));
    myMapper->writeCPU(0x002D, a);
    a = myMapper->readCPU(0x003E);
    opADC(myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x002E, a);
    myMapper->writeCPU(0x0001, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x002F));
    myMapper->writeCPU(0x002F, a);
    SUB_019938();
    return;
}

void game::SUB_019938() {
    a = myMapper->readCPU(0x0001);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    opEOR(0xFF);
    x = a;
    opINX(1);
    myMapper->writeCPU(0x0049, x);
    popAddress();
}

void game::SUB_019944() {
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x004B, myMapper->readCPU(0x003E));
    a = myMapper->readCPU(0x002D);
    flgC = true;
    opSBC(myMapper->readCPU(0x003D));
    myMapper->writeCPU(0x002D, a);
    if (!flgC) {
        opINC(0x004B, 1);
    }
    a = myMapper->readCPU(0x002E);
    flgC = true;
    opSBC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x002E, a);
    myMapper->writeCPU(0x0001, a);
    if (flgC) {
        goto L_019964;
    }
    opDEC(0x002F, 1);
L_019964:
    jump(0x9938);
    return;
}

void game::SUB_019967() {
    if (myMapper->readCPU(0x0048) != 0) {
        goto L_019997;
    }
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFC5E + x);
    opLSR_A(4);
    if (a == myMapper->readCPU(0x0046)) {
        a = myMapper->readCPU(0xFC5E + x);
        opAND(0x0F);
        if (a == myMapper->readCPU(0x002F)) {
            if (myMapper->readCPU(0x002E) != 0) {
                goto L_019997;
            }
            myMapper->writeCPU(0x0060, 0x3F);
            if (myMapper->readCPU(0x0028) == 0x12) {
                goto L_019993;
            }
            myMapper->writeCPU(0x00E2, 0x01);
        L_019993:
            myMapper->writeCPU(0x0048, 0x01);
        }
    }
L_019997:
    popAddress();
}

void game::SUB_019998() {
    a = myMapper->readCPU(0x003F);
    flgC = true;
    opSBC(0x13);
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, 0x00);
    a = myMapper->readCPU(0x0040);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0041);
    myMapper->writeCPU(0x0013, a);
    if (!flgC) {
        opDEC(0x0013, 1);
    }
    pushAddress(0x99B4);
    SUB_01F9A0();
    if (handleReturnAddress(poppedEntry.value, 0x99B4)) return;
    if (flgZ) {
        a = myMapper->readCPU(0x003F);
        flgC = true;
        opSBC(0x13);
        myMapper->writeCPU(0x0010, a);
        myMapper->writeCPU(0x0011, 0x00);
        myMapper->writeCPU(0x0012, myMapper->readCPU(0x0040));
        a = myMapper->readCPU(0x0041);
        myMapper->writeCPU(0x0013, a);
        pushAddress(0x99CC);
        SUB_01F9A0();
        if (handleReturnAddress(poppedEntry.value, 0x99CC)) return;
        if (flgZ) {
            a = myMapper->readCPU(0x003F);
            flgC = true;
            opSBC(0x13);
            myMapper->writeCPU(0x0010, a);
            myMapper->writeCPU(0x0011, 0x00);
            a = myMapper->readCPU(0x0040);
            flgC = false;
            opADC(0x07);
            myMapper->writeCPU(0x0012, a);
            a = 0x00;
            opADC(myMapper->readCPU(0x0041));
            myMapper->writeCPU(0x0013, a);
            pushAddress(0x99E9);
            SUB_01F9A0();
            if (handleReturnAddress(poppedEntry.value, 0x99E9)) return;
            if (!flgZ) {
                goto L_0199EE;
            }
            flgC = true;
            popAddress();
            return;
        }
    }
L_0199EE:
    flgC = false;
    popAddress();
}

void game::SUB_0199F0() {
    a = myMapper->readCPU(0x0028);
    if (a != 0x02) {
        if (a != 0x0A) {
            goto L_019A1C;
        }
    }
    if (myMapper->readCPU(0x0046) == 0) {
        a = myMapper->readCPU(0x0354);
        if (a >= 0xB8) {
            flgC = true;
            opSBC(0xB8);
            opCMP(a, 0x07);
            if (flgC) {
                goto L_019A16;
            }
            x = 0x00;
            pushAddress(0x9A10);
            SUB_01FCB9();
            if (handleReturnAddress(poppedEntry.value, 0x9A10)) return;
            a = 0x0F;
            pushAddress(0x9A15);
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0x9A15)) return;
        L_019A16:
            pushAddress(0x9A18);
            SUB_01C59C();
            if (handleReturnAddress(poppedEntry.value, 0x9A18)) return;
            pushAddress(0x9A1B);
            SUB_01C5CF();
            if (handleReturnAddress(poppedEntry.value, 0x9A1B)) return;
        }
    }
L_019A1C:
    popAddress();
}

void game::SUB_019A1D() {
    a = myMapper->readCPU(0x0042);
    opORA(myMapper->readCPU(0x0043));
    if (!flgZ) {
        jump(0x9A28);
        return;
    }
    pushAddress(0x9A25);
    SUB_01A1E5();
    if (handleReturnAddress(poppedEntry.value, 0x9A25)) return;
    flgC = true;
    popAddress();
}

void game::SUB_019A28() {
    flgC = false;
    popAddress();
}

void game::SUB_019A2A() {
    a = myMapper->readCPU(0x0434);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x9A28);
        return;
    }
    a = myMapper->readCPU(0x00F5);
    opAND(0x40);
    if (flgZ) {
        jump(0x9A28);
        return;
    }
    myMapper->writeCPU(0x0434, x);
    a = myMapper->readCPU(0x00F7);
    opAND(0x08);
    if (!flgZ) {
        pushAddress(0x9A40);
        SUB_01FA26();
        if (handleReturnAddress(poppedEntry.value, 0x9A40)) return;
        if (!flgC) {
            goto L_019A4B;
        }
        a = myMapper->readCPU(0x0434);
        opORA(0x80);
        myMapper->writeCPU(0x0434, a);
    }
L_019A4B:
    a = 0x00;
    myMapper->writeCPU(0x0530, a);
    myMapper->writeCPU(0x0568, a);
    a = myMapper->readCPU(0x046C);
    myMapper->writeCPU(0x0530, a);
    flgC = true;
    popAddress();
}

void game::SUB_019A5B() {
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    myMapper->writeCPU(0x003C, a);
    popAddress();
}

void game::SUB_019A62() {
    a = 0xF8;
    SUB_019A64();
    return;
}

void game::SUB_019A64() {
    opAND(myMapper->readCPU(0x003F));
    myMapper->writeCPU(0x003F, a);
    popAddress();
}

void game::SUB_019A69() {
    a = 0x04;
    SUB_019A6B();
    return;
}

void game::SUB_019A6B() {
    flgC = false;
    opADC(myMapper->readCPU(0x003F));
    myMapper->writeCPU(0x003F, a);
    popAddress();
}

void game::SUB_019A71() {
    opINC(0x0568, 1);
    a = myMapper->readCPU(0x0568);
    opCMP(a, 0x0B);
    if (flgZ) {
        x = 0x09;
        if (myMapper->readCPU(0x0070) == 0) {
            x = 0x0A;
        }
        a = myMapper->readCPU(0x0434);
        opAND(0x80);
        if (!flgZ) {
            a = myMapper->readCPU(0x015B);
            opCMP(a, 0x08);
            if (!flgZ) {
                goto L_019A97;
            }
            x = 0x08;
        }
        a = x;
        pushAddress(0x9A96);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0x9A96)) return;
    }
L_019A97:
    pushAddress(0x9A99);
    SUB_019AE1();
    if (handleReturnAddress(poppedEntry.value, 0x9A99)) return;
    x = myMapper->readCPU(0x0568);
    a = myMapper->readCPU(0x9B07 + x);
    myMapper->writeCPU(0x004B, a);
    if (a == 0xFF) {
        jump(0x9AF8);
        return;
    }
    x = a;
    a = myMapper->readCPU(0x0530);
    if (a != 0x03) {
        if (a != 0x09) {
            goto L_019AB7;
        }
    }
    a = x;
    flgC = false;
    opADC(0x04);
    x = a;
L_019AB7:
    a = x;
    opPHA();
    pushAddress(0x9ABB);
    SUB_01A38D();
    if (handleReturnAddress(poppedEntry.value, 0x9ABB)) return;
    opPLA();
    myMapper->writeCPU(0x004B, a);
    if (myMapper->readCPU(0x046C) == 0x04) {
        x = 0x11;
        a = myMapper->readCPU(0x0514);
        flgC = true;
        opSBC(0x01);
        if (a < 0x02) {
            goto L_019AD4;
        }
        x = 0x0E;
    L_019AD4:
        a = x;
        flgC = false;
        opADC(myMapper->readCPU(0x004B));
        myMapper->writeCPU(0x004B, a);
    }
    a = myMapper->readCPU(0x004B);
    pushAddress(0x9ADE);
    SUB_019BBA();
    if (handleReturnAddress(poppedEntry.value, 0x9ADE)) return;
    flgC = false;
    SUB_019AE0();
    return;
}

void game::SUB_019AE0() {
    popAddress();
}

void game::SUB_019AE1() {
    a = myMapper->readCPU(0x0434);
    opAND(0x80);
    if (flgZ) {
        jump(0x9AE0);
        return;
    }
    if (myMapper->readCPU(0x0568) != 0x11) {
        jump(0x9AE0);
        return;
    }
    a = myMapper->readCPU(0x015B);
    flgC = true;
    opSBC(0x08);
    jump(0xDA5F);
    return;
}

void game::SUB_019AF8() {
    myMapper->writeCPU(0x054C, 0x00);
    a = 0xFC;
    myMapper->writeCPU(0x0355, a);
    myMapper->writeCPU(0x0356, a);
    flgC = true;
    popAddress();
}

void game::SUB_019B1E() {
    x = a;
    while (true) {
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x04DC + x));
        myMapper->writeCPU(0x0011, myMapper->readCPU(0x04F8 + x));
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x0010) + (myMapper->readCPU((0x0010 + 1) & 0x00ff) << 8) + y);
        if (a == 0x80) {
            goto L_019B43;
        }
        if (a != 0x81) {
            goto L_019B48;
        }
        a = myMapper->readCPU(0x0514 + x);
        opEOR(0x01);
        myMapper->writeCPU(0x0514 + x, a);
        pushAddress(0x9B3F);
        SUB_019B7C();
        if (handleReturnAddress(poppedEntry.value, 0x9B3F)) return;
    }
L_019B43:
    a = 0xF8;
    opINC(0x0143, 1);
L_019B48:
    opPHA();
    y = a;
    if (myMapper->readCPU(0x0514 + x) != 0) {
        a = y;
        opEOR(0xFF);
        y = a;
        opINY(1);
    }
    a = x;
    if (a != 0x00) {
        goto L_019B5F;
    }
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x003F));
    myMapper->writeCPU(0x003F, a);
L_019B5F:
    opPLA();
    if (a == 0xF8) {
        jump(0x9B89);
        return;
    }
    if (myMapper->readCPU(0x0514 + x) != 0) {
        jump(0x9B7C);
        return;
    }
    flgC = false;
    a = 0x01;
    opADC(myMapper->readCPU(0x04DC + x));
    myMapper->writeCPU(0x04DC + x, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x04F8 + x));
    myMapper->writeCPU(0x04F8 + x, a);
    flgC = false;
    popAddress();
}

void game::SUB_019B7C() {
    opDEC(0x04DC + x, 1);
    a = myMapper->readCPU(0x04DC + x);
    if (a != 0xFF) {
        jump(0x9B89);
        return;
    }
    opDEC(0x04F8 + x, 1);
    SUB_019B89();
    return;
}

void game::SUB_019B89() {
    flgC = false;
    popAddress();
}

void game::SUB_019BBA() {
    myMapper->writeCPU(0x0159, a);
    x = a;
    x = myMapper->readCPU(0x9BF1 + x);
    if (myMapper->readCPU(0x005B) == 0) {
        if (myMapper->readCPU(0x007D) == 0) {
            jump(0x9BE3);
            return;
        }
        opDEC(0x007D, 1);
        opCMP(myMapper->readCPU(0x007D), 0x80);
        if (!flgZ) {
            goto L_019BDB;
        }
        a = 0x14;
        pushAddress(0x9BD6);
        SUB_01CC95();
        if (handleReturnAddress(poppedEntry.value, 0x9BD6)) return;
        myMapper->writeCPU(0x005B, 0xB4);
    }
L_019BDB:
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        jump(0x9BE3);
        return;
    }
    x = 0x00;
    SUB_019BE3();
    return;
}

void game::SUB_019BE3() {
    myMapper->writeCPU(0x031C, x);
    myMapper->writeCPU(0x0338, 0x00);
    a = myMapper->readCPU(0x003F);
    myMapper->writeCPU(0x0354, a);
    popAddress();
}

void game::SUB_019C10() {
    myMapper->writeCPU(0x0010, a);
    x = a;
    a = myMapper->readCPU(0x0584 + x);
    opAND(0x0C);
    if (flgZ) {
        jump(0x9C6D);
        return;
    }
    if (a == 0x0C) {
        jump(0x9C6D);
        return;
    }
    pushAddress(0x9C20);
    SUB_019CBD();
    if (handleReturnAddress(poppedEntry.value, 0x9C20)) return;
    if (!flgC) {
        jump(0x9C6D);
        return;
    }
    a = myMapper->readCPU(0x0008);
    setLoadFlag(a);
    if (flgZ) {
        jump(0x9C43);
        return;
    }
    myMapper->writeCPU(0x0584, a);
    x = 0x04;
    if (myMapper->readCPU(0x04C0) >= 0x02) {
        goto L_019C35;
    }
    x = 0x08;
L_019C35:
    a = x;
    opORA(myMapper->readCPU(0x0584));
    myMapper->writeCPU(0x0584, a);
    myMapper->writeCPU(0x046C, 0x06);
    flgC = true;
    popAddress();
}

void game::SUB_019C43() {
    pushAddress(0x9C45);
    SUB_019C6F();
    if (handleReturnAddress(poppedEntry.value, 0x9C45)) return;
    a = myMapper->readCPU(0x0009);
    opAND(0x01);
    opEOR(0x01);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x04C0);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0000));
    x = a;
    a = myMapper->readCPU(0x9C65 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x003F));
    myMapper->writeCPU(0x003F, a);
    a = 0x04;
    myMapper->writeCPU(0x046C, a);
    flgC = true;
    popAddress();
}

void game::SUB_019C6D() {
    flgC = false;
    popAddress();
}

void game::SUB_019C6F() {
    a = myMapper->readCPU(0x0584);
    opAND(0x0F);
    if (flgZ) {
        goto L_019CA2;
    }
    x = a;
    a = myMapper->readCPU(0x9CAD + x);
    opLSR_A(1);
    if (a >= 0x03) {
        a = 0x03;
    }
    y = a;
    a = myMapper->readCPU(0x04C0);
    opAND(0x01);
    if (!flgZ) {
        goto L_019CA3;
    }
    a = y;
    flgC = true;
    opSBC(0x01);
    x = 0x00;
    if (a >= 0x02) {
        goto L_019C94;
    }
    opINX(1);
    while (true) {
    L_019C94:
        a = x;
        myMapper->writeCPU(0x0514, a);
        x = 0x01;
        opAND(0x01);
        if (flgZ) {
            goto L_019C9F;
        }
        opINX(1);
    L_019C9F:
        myMapper->writeCPU(0x0584, x);
    L_019CA2:
        popAddress();
        return;
    L_019CA3:
        a = y;
        opAND(0x01);
        flgC = false;
        opADC(0x02);
        x = a;
    }
    SUB_019CBD();
    return;
}

void game::SUB_019CBD() {
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x000E, myMapper->readCPU(0xFBEC + x));
    myMapper->writeCPU(0x000F, myMapper->readCPU(0xFBED + x));
    y = 0x00;
    while (true) {
        while (true) {
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_019D40;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            opLSR_A(2);
            opAND(0x01);
            if (a != myMapper->readCPU(0x0046)) {
                goto L_019D42;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            opAND(0x03);
            myMapper->writeCPU(0x04C0, a);
            x = 0x04;
            opAND(0x02);
            if (flgZ) {
                x = 0x08;
            }
            myMapper->writeCPU(0x0017, x);
            a = myMapper->readCPU(0x0584);
            opAND(myMapper->readCPU(0x0017));
            if (flgZ) {
                goto L_019D42;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            opAND(0xF0);
            myMapper->writeCPU(0x0000, a);
            opINY(1);
            a = y;
            opPHA();
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            opAND(0xF8);
            myMapper->writeCPU(0x0001, a);
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            opAND(0x07);
            myMapper->writeCPU(0x0002, a);
            x = myMapper->readCPU(0x04C0);
            a = myMapper->readCPU(0x9D47 + x);
            setLoadFlag(a);
            if (!flgN) {
                goto L_019D12;
            }
            opDEC(0x0002, 1);
        L_019D12:
            flgC = false;
            opADC(myMapper->readCPU(0x0001));
            myMapper->writeCPU(0x0001, a);
            a = 0x00;
            opADC(myMapper->readCPU(0x0002));
            myMapper->writeCPU(0x0002, a);
            myMapper->writeCPU(0x0010, 0x01);
            myMapper->writeCPU(0x0012, 0x08);
            y = myMapper->readCPU(0x003F);
            x = myMapper->readCPU(0x0040);
            myMapper->writeCPU(0x0003, myMapper->readCPU(0x0041));
            myMapper->writeCPU(0x0011, 0x02);
            a = 0x08;
            myMapper->writeCPU(0x0013, a);
            pushAddress(0x9D37);
            SUB_01A048();
            if (handleReturnAddress(poppedEntry.value, 0x9D37)) return;
            opPLA();
            y = a;
            if (!flgC) {
                goto L_019D4B;
            }
            opINY(1);
        }
    L_019D40:
        flgC = false;
        popAddress();
        return;
    L_019D42:
        opINY(2);
    }
L_019D4B:
    myMapper->writeCPU(0x0008, 0x02);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0x07);
    myMapper->writeCPU(0x000B, a);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0xF8);
    myMapper->writeCPU(0x0009, a);
    x = myMapper->readCPU(0x04C0);
    a = myMapper->readCPU(0x9D47 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEC(0x000B, 1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0009));
    myMapper->writeCPU(0x0009, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x000B, a);
    a = myMapper->readCPU(0x0009);
    flgC = true;
    opSBC(myMapper->readCPU(0x0040));
    y = a;
    a = myMapper->readCPU(0x000B);
    opSBC(myMapper->readCPU(0x0041));
    x = a;
    a = y;
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x0009, a);
    a = x;
    opADC(0x00);
    if (!flgN) {
        myMapper->writeCPU(0x0008, 0x01);
        a = myMapper->readCPU(0x0009);
        if (a >= 0x02) {
            goto L_019D94;
        }
        a = 0x00;
        myMapper->writeCPU(0x0008, a);
    }
L_019D94:
    flgC = true;
    popAddress();
}

void game::SUB_019D96() {
    pushAddress(0x9D98);
    SUB_019DC1();
    if (handleReturnAddress(poppedEntry.value, 0x9D98)) return;
    pushAddress(0x9D9B);
    SUB_0198F3();
    if (handleReturnAddress(poppedEntry.value, 0x9D9B)) return;
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (flgZ) {
        a = myMapper->readCPU(0x003C);
        setLoadFlag(a);
        if (!flgZ) {
            if (a != 0x01) {
                goto L_019DB0;
            }
            pushAddress(0x9DAC);
            SUB_01991F();
            if (handleReturnAddress(poppedEntry.value, 0x9DAC)) return;
            goto L_019DB3;
        L_019DB0:
            pushAddress(0x9DB2);
            SUB_019944();
            if (handleReturnAddress(poppedEntry.value, 0x9DB2)) return;
        }
    }
L_019DB3:
    a = myMapper->readCPU(0x038C);
    if (a != 0x80) {
        jump(0x9DC0);
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0xFB);
    myMapper->writeCPU(0x003C, a);
    SUB_019DC0();
    return;
}

void game::SUB_019DC0() {
    popAddress();
}

void game::SUB_019DC1() {
    a = myMapper->readCPU(0x003C);
    opAND(0x03);
    if (flgZ) {
        jump(0x9DC0);
        return;
    }
    a = myMapper->readCPU(0x04C0);
    opAND(0x01);
    if (flgZ) {
        x = myMapper->readCPU(0x0584);
        a = x;
        opAND(0x08);
        if (flgZ) {
            a = x;
            opAND(0x01);
            if (flgZ) {
                goto L_019DEA;
            }
        }
        a = myMapper->readCPU(0x003C);
        opAND(0x04);
        if (!flgZ) {
            pushAddress(0x9DE3);
            SUB_019E4C();
            if (handleReturnAddress(poppedEntry.value, 0x9DE3)) return;
        }
        pushAddress(0x9DE6);
        SUB_019E3C();
        if (handleReturnAddress(poppedEntry.value, 0x9DE6)) return;
        goto L_019E2B;
    L_019DEA:
        a = myMapper->readCPU(0x003C);
        opAND(0x04);
        if (!flgZ) {
            pushAddress(0x9DF2);
            SUB_019E5E();
            if (handleReturnAddress(poppedEntry.value, 0x9DF2)) return;
        }
        pushAddress(0x9DF5);
        SUB_019E2C();
        if (handleReturnAddress(poppedEntry.value, 0x9DF5)) return;
        goto L_019E2B;
    }
    x = myMapper->readCPU(0x0584);
    a = x;
    opAND(0x08);
    if (flgZ) {
        a = x;
        opAND(0x02);
        if (flgZ) {
            goto L_019E15;
        }
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (!flgZ) {
        pushAddress(0x9E0E);
        SUB_019E5E();
        if (handleReturnAddress(poppedEntry.value, 0x9E0E)) return;
    }
    pushAddress(0x9E11);
    SUB_019E3C();
    if (handleReturnAddress(poppedEntry.value, 0x9E11)) return;
    goto L_019E2B;
L_019E15:
    a = x;
    opAND(0x04);
    if (!flgZ) {
        a = x;
        opAND(0x01);
        if (!flgZ) {
            goto L_019E2B;
        }
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (flgZ) {
        goto L_019E28;
    }
    pushAddress(0x9E27);
    SUB_019E4C();
    if (handleReturnAddress(poppedEntry.value, 0x9E27)) return;
L_019E28:
    pushAddress(0x9E2A);
    SUB_019E2C();
    if (handleReturnAddress(poppedEntry.value, 0x9E2A)) return;
L_019E2B:
    popAddress();
}

void game::SUB_019E2C() {
    a = myMapper->readCPU(0x0370);
    flgC = false;
    opADC(myMapper->readCPU(0x003D));
    myMapper->writeCPU(0x0370, a);
    a = myMapper->readCPU(0x003F);
    opADC(myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x003F, a);
    popAddress();
}

void game::SUB_019E3C() {
    a = myMapper->readCPU(0x0370);
    flgC = true;
    opSBC(myMapper->readCPU(0x003D));
    myMapper->writeCPU(0x0370, a);
    a = myMapper->readCPU(0x003F);
    opSBC(myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x003F, a);
    popAddress();
}

void game::SUB_019E4C() {
    a = myMapper->readCPU(0x03A8);
    flgC = false;
    opADC(myMapper->readCPU(0x003D));
    myMapper->writeCPU(0x03A8, a);
    a = myMapper->readCPU(0x038C);
    opADC(myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x038C, a);
    popAddress();
}

void game::SUB_019E5E() {
    a = myMapper->readCPU(0x03A8);
    flgC = true;
    opSBC(myMapper->readCPU(0x003D));
    myMapper->writeCPU(0x03A8, a);
    a = myMapper->readCPU(0x038C);
    opSBC(myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x038C, a);
    popAddress();
}

void game::SUB_019E70() {
    a = myMapper->readCPU(0x003F);
    flgC = true;
    opSBC(0xD0);
    if (!flgC) {
        myMapper->writeCPU(0x0013, myMapper->readCPU(0x0041));
        a = myMapper->readCPU(0x0040);
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(0x0012, a);
        if (flgC) {
            goto L_019E86;
        }
        opDEC(0x0013, 1);
    L_019E86:
        myMapper->writeCPU(0x0011, 0x00);
        a = myMapper->readCPU(0x003F);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x0010, a);
        pushAddress(0x9E93);
        SUB_01F9A0();
        if (handleReturnAddress(poppedEntry.value, 0x9E93)) return;
        if (myMapper->readCPU(0x0014) == 0) {
            goto L_019EA2;
        }
        do {
            a = myMapper->readCPU(0x0142);
            opORA(0x02);
            myMapper->writeCPU(0x0142, a);
            flgC = true;
            popAddress();
            return;
        L_019EA2:
            a = myMapper->readCPU(0x0040);
            flgC = false;
            opADC(0x04);
            myMapper->writeCPU(0x0012, a);
            a = 0x00;
            opADC(myMapper->readCPU(0x0041));
            myMapper->writeCPU(0x0013, a);
            myMapper->writeCPU(0x0011, 0x00);
            a = myMapper->readCPU(0x003F);
            flgC = false;
            opADC(0x10);
            myMapper->writeCPU(0x0010, a);
            pushAddress(0x9EBC);
            SUB_01F9A0();
            if (handleReturnAddress(poppedEntry.value, 0x9EBC)) return;
        } while (myMapper->readCPU(0x0014) != 0);
    }
    a = myMapper->readCPU(0x0142);
    opAND(0xFD);
    myMapper->writeCPU(0x0142, a);
    flgC = false;
    popAddress();
}

void game::SUB_019ECB() {
    jump(0x9F56);
    return;
}

void game::SUB_019ECE() {
    a = myMapper->readCPU(0x046C);
    if (a == 0x06) {
        jump(0x9ECB);
        return;
    }
    if (a == 0x04) {
        jump(0x9ECB);
        return;
    }
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0040));
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0041));
    a = myMapper->readCPU(0x003C);
    opEOR(0x01);
    opAND(0x01);
    x = a;
    a = myMapper->readCPU(0x0142);
    opAND(0x04);
    if (!flgZ) {
        a = myMapper->readCPU(0x00F7);
        opAND(0x03);
        if (flgZ) {
            a = myMapper->readCPU(0x0142);
            opLSR_A(3);
            opAND(0x01);
            x = a;
        }
    }
    if (x == 0x01) {
        flgC = true;
        a = myMapper->readCPU(0x0012);
        opSBC(0x08);
        myMapper->writeCPU(0x0012, a);
        if (flgC) {
            goto L_019F1C;
        }
        opDEC(0x0013, 1);
    }
    else {
        flgC = false;
        a = myMapper->readCPU(0x0012);
        opADC(0x08);
        myMapper->writeCPU(0x0012, a);
        if (flgC) {
            opINC(0x0013, 1);
        }
    }
L_019F1C:
    y = 0x00;
    if (myMapper->readCPU(0x046C) == 0x01) {
        if (myMapper->readCPU(0x0514) == 0) {
            goto L_019F2C;
        }
        y = 0x02;
    }
L_019F2C:
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x9F6C + y));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x9F6D + y));
    myMapper->writeCPU(0x004F, 0x04);
    do {
        y = myMapper->readCPU(0x004F);
        myMapper->writeCPU(0x004B, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
        flgC = false;
        a = myMapper->readCPU(0x003F);
        opADC(myMapper->readCPU(0x004B));
        myMapper->writeCPU(0x0010, a);
        a = 0x00;
        myMapper->writeCPU(0x0011, a);
        pushAddress(0x9F4D);
        SUB_01F9A0();
        if (handleReturnAddress(poppedEntry.value, 0x9F4D)) return;
        if (myMapper->readCPU(0x0014) != 0) {
            jump(0x9F60);
            return;
        }
        opDEC(0x004F, 1);
    } while (!flgN);
    SUB_019F56();
    return;
}

void game::SUB_019F56() {
    a = myMapper->readCPU(0x0142);
    opAND(0xFE);
    myMapper->writeCPU(0x0142, a);
    flgC = false;
    popAddress();
}

void game::SUB_019F60() {
    a = myMapper->readCPU(0x0142);
    opAND(0xFE);
    opORA(0x01);
    myMapper->writeCPU(0x0142, a);
    flgC = true;
    popAddress();
}

void game::SUB_019F7A() {
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0xFC12 + x);
    opAND(0x01);
    if (a == myMapper->readCPU(0x0046)) {
        a = myMapper->readCPU(0xFC12 + x);
        opAND(0xFE);
        myMapper->writeCPU(0x0000, a);
        opINX(1);
        myMapper->writeCPU(0x0001, myMapper->readCPU(0xFC12 + x));
        a = 0x02;
        myMapper->writeCPU(0x0010, a);
        myMapper->writeCPU(0x0012, a);
        y = myMapper->readCPU(0x003F);
        x = myMapper->readCPU(0x038C);
        a = 0x02;
        myMapper->writeCPU(0x0011, a);
        myMapper->writeCPU(0x0013, a);
        pushAddress(0x9FA7);
        SUB_01A011();
        if (handleReturnAddress(poppedEntry.value, 0x9FA7)) return;
        if (!flgC) {
            goto L_019FAC;
        }
    }
    flgC = false;
    popAddress();
    return;
L_019FAC:
    a = 0x00;
    myMapper->writeCPU(0x0144, a);
    myMapper->writeCPU(0x0146, a);
    x = 0x01;
    if (myMapper->readCPU(0x0001) >= 0x80) {
        goto L_019FBE;
    }
    x = 0x02;
L_019FBE:
    myMapper->writeCPU(0x0584, x);
    a = x;
    opLSR_A(1);
    myMapper->writeCPU(0x0450, a);
    if (flgZ) {
        jump(0x9FE7);
        return;
    }
    opINC(0x0028, 1);
    pushAddress(0x9FCC);
    SUB_01D015();
    if (handleReturnAddress(poppedEntry.value, 0x9FCC)) return;
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x002F, a);
    a = 0x00;
    myMapper->writeCPU(0x002E, a);
    myMapper->writeCPU(0x002D, a);
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    opINX(1);
    a = myMapper->readCPU(0xCA0C + x);
    opAND(0x01);
    myMapper->writeCPU(0x0046, a);
    pushAddress(0x9FE6);
    SUB_01CFBD();
    if (handleReturnAddress(poppedEntry.value, 0x9FE6)) return;
    SUB_019FE7();
    return;
}

void game::SUB_019FE7() {
    pushAddress(0x9FE9);
    SUB_01C5B0();
    if (handleReturnAddress(poppedEntry.value, 0x9FE9)) return;
    a = 0x00;
    myMapper->writeCPU(0x0047, a);
    pushAddress(0x9FF0);
    SUB_019BBA();
    if (handleReturnAddress(poppedEntry.value, 0x9FF0)) return;
    flgC = true;
    popAddress();
}

void game::SUB_019FF3() {
    a = myMapper->readCPU(0x003F);
    if (a == 0xD0) {
        goto L_01A006;
    }
    if (a != 0x30) {
        goto L_01A00F;
    }
    opINC(0x0046, 1);
    a = 0xCF;
    myMapper->writeCPU(0x003F, a);
    jump(0x9FE7);
    return;
L_01A006:
    opDEC(0x0046, 1);
    a = 0x31;
    myMapper->writeCPU(0x003F, a);
    jump(0x9FE7);
    return;
L_01A00F:
    flgC = false;
    popAddress();
}

void game::SUB_01A011() {
    a = myMapper->readCPU(0x0011);
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0014, a);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x0014));
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    opASL_M(0x0014, 1);
    opCMP(a, myMapper->readCPU(0x0014));
    if (flgC) {
        jump(0xA037);
        return;
    }
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0014, a);
    a = x;
    flgC = false;
    opADC(myMapper->readCPU(0x0014));
    flgC = true;
    opSBC(myMapper->readCPU(0x0001));
    opASL_M(0x0014, 1);
    opCMP(a, myMapper->readCPU(0x0014));
    SUB_01A037();
    return;
}

void game::SUB_01A037() {
    popAddress();
}

void game::SUB_01A048() {
    a = myMapper->readCPU(0x0011);
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0014, a);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x0014));
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    opASL_M(0x0014, 1);
    opCMP(a, myMapper->readCPU(0x0014));
    if (flgC) {
        jump(0xA037);
        return;
    }
    a = myMapper->readCPU(0x0012);
    flgC = false;
    opADC(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0014, a);
    a = x;
    flgC = true;
    opSBC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0008, a);
    if (!flgC) {
        opDEC(0x0003, 1);
    }
    a = myMapper->readCPU(0x0003);
    flgC = true;
    opSBC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0009, a);
    a = myMapper->readCPU(0x0008);
    flgC = false;
    opADC(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0008, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0009));
    if (!flgZ) {
        goto L_01A088;
    }
    a = myMapper->readCPU(0x0008);
    opASL_M(0x0014, 1);
    opCMP(a, myMapper->readCPU(0x0014));
    popAddress();
    return;
L_01A088:
    flgC = true;
    popAddress();
}

void game::SUB_01A08A() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        popAddress();
        return;
    }
    pushAddress(0xA093);
    SUB_01CC7A();
    if (handleReturnAddress(poppedEntry.value, 0xA093)) return;
    opCMP(myMapper->readCPU(0x0018), 0x05);
    if (!flgZ) {
        jump(0xA0CD);
        return;
    }
    opCMP(myMapper->readCPU(0x0019), 0x06);
    if (!flgZ) {
        jump(0xA0CD);
        return;
    }
    if (myMapper->readCPU(0x0022) != 0) {
        jump(0xA0CD);
        return;
    }
    if (myMapper->readCPU(0x0560) != 0) {
        goto L_01A0B2;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x3F);
    if (!flgZ) {
        jump(0xA0CD);
        return;
    }
    pushAddress(0xA0B1);
    SUB_01A2AF();
    if (handleReturnAddress(poppedEntry.value, 0xA0B1)) return;
L_01A0B2:
    a = myMapper->readCPU(0x0043);
    opORA(myMapper->readCPU(0x0042));
    if (flgZ) {
        jump(0xA0CD);
        return;
    }
    if (myMapper->readCPU(0x0043) != 0) {
        jump(0xA0CD);
        return;
    }
    opCMP(myMapper->readCPU(0x0042), 0x30);
    if (flgC) {
        jump(0xA0CD);
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x3F);
    if (!flgZ) {
        jump(0xA0CD);
        return;
    }
    a = 0x22;
    pushAddress(0xA0CC);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xA0CC)) return;
    SUB_01A0CD();
    return;
}

void game::SUB_01A0CD() {
    a = 0x1A;
    pushAddress(0xA0D1);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xA0D1)) return;
    y = 0x01;
    do {
        a = myMapper->readCPU(0x0042 + y);
        pushAddress(0xA0D9);
        SUB_01CC68();
        if (handleReturnAddress(poppedEntry.value, 0xA0D9)) return;
        opDEY(1);
    } while (!flgN);
    pushAddress(0xA0DF);
    SUB_01CC5F();
    if (handleReturnAddress(poppedEntry.value, 0xA0DF)) return;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        if (!(myMapper->readCPU(0x0045) & 0x80)) {
            goto L_01A0EE;
        }
        myMapper->writeCPU(0x0045, 0x00);
    L_01A0EE:
        a = myMapper->readCPU(0x0044);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x004B, a);
            opCMP(a, myMapper->readCPU(0x0045));
            if (flgZ) {
            }
            else {
                opDEC(0x004B, 1);
                if (a < myMapper->readCPU(0x0045)) {
                    opINC(0x004B, 2);
                }
                myMapper->writeCPU(0x0044, myMapper->readCPU(0x004B));
                a = 0x67;
                myMapper->writeCPU(0x004F, a);
                pushAddress(0xA10F);
                SUB_01A23B();
                if (handleReturnAddress(poppedEntry.value, 0xA10F)) return;
            }
        }
    }
    pushAddress(0xA112);
    SUB_01A206();
    if (handleReturnAddress(poppedEntry.value, 0xA112)) return;
    x = 0x1A;
    a = myMapper->readCPU(0x015B);
    opAND(0x0F);
    if (!flgZ) {
        goto L_01A11E;
    }
    x = 0xFC;
L_01A11E:
    myMapper->writeCPU(0x023C, x);
    myMapper->writeCPU(0x0240, x);
    myMapper->writeCPU(0x023F, 0x88);
    myMapper->writeCPU(0x0243, 0x90);
    a = myMapper->readCPU(0x015B);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x004B, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    x = a;
    a = myMapper->readCPU(0xA151 + x);
    myMapper->writeCPU(0x023E, a);
    myMapper->writeCPU(0x0242, a);
    myMapper->writeCPU(0x023D, myMapper->readCPU(0xA152 + x));
    myMapper->writeCPU(0x0241, myMapper->readCPU(0xA153 + x));
    popAddress();
}

void game::SUB_01A169() {
    pushAddress(0xA16B);
    SUB_01A1D0();
    if (handleReturnAddress(poppedEntry.value, 0xA16B)) return;
    pushAddress(0xA16E);
    SUB_01A0CD();
    if (handleReturnAddress(poppedEntry.value, 0xA16E)) return;
    pushAddress(0xA171);
    SUB_01A296();
    if (handleReturnAddress(poppedEntry.value, 0xA171)) return;
    myMapper->writeCPU(0x004B, myMapper->readCPU(0x0044));
    myMapper->writeCPU(0x004F, 0x67);
    jump(0xA23B);
    return;
}

void game::SUB_01A17D() {
    pushAddress(0xA17F);
    SUB_01CC7A();
    if (handleReturnAddress(poppedEntry.value, 0xA17F)) return;
    myMapper->writeCPU(0x01AA, myMapper->readCPU(0x01A9));
    myMapper->writeCPU(0x004B, a);
    pushAddress(0xA18A);
    SUB_01A233();
    if (handleReturnAddress(poppedEntry.value, 0xA18A)) return;
    a = 0x07;
    pushAddress(0xA18F);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xA18F)) return;
    pushAddress(0xA192);
    SUB_01CC3D();
    if (handleReturnAddress(poppedEntry.value, 0xA192)) return;
    myMapper->writeCPU(0x0141, 0x01);
    pushAddress(0xA19A);
    SUB_01A2E8();
    if (handleReturnAddress(poppedEntry.value, 0xA19A)) return;
    myMapper->writeCPU(0x004B, 0x20);
    x = 0x00;
    do {
        a = myMapper->readCPU(0xA1B0 + x);
        myMapper->writeCPU(0x021C + x, a);
        opINX(1);
        opDEC(0x004B, 1);
    } while (!flgZ);
    pushAddress(0xA1AE);
    SUB_01D11B();
    if (handleReturnAddress(poppedEntry.value, 0xA1AE)) return;
    popAddress();
}

void game::SUB_01A1D0() {
    a = myMapper->readCPU(0x0071);
    pushAddress(0xA1D4);
    SUB_01A333();
    if (handleReturnAddress(poppedEntry.value, 0xA1D4)) return;
    myMapper->writeCPU(0x0008, a);
    a = 0x1B;
    pushAddress(0xA1DB);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xA1DB)) return;
    a = myMapper->readCPU(0x0008);
    pushAddress(0xA1E0);
    SUB_01CC68();
    if (handleReturnAddress(poppedEntry.value, 0xA1E0)) return;
    jump(0xCC5F);
    return;
}

void game::SUB_01A1E5() {
    a = 0x00;
    myMapper->writeCPU(0x0070, a);
    myMapper->writeCPU(0x00E2, a);
    pushAddress(0xA1ED);
    SUB_019AF8();
    if (handleReturnAddress(poppedEntry.value, 0xA1ED)) return;
    myMapper->writeCPU(0x046C, 0x08);
    a = 0x00;
    pushAddress(0xA1F7);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xA1F7)) return;
    a = 0x59;
    pushAddress(0xA1FC);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xA1FC)) return;
    myMapper->writeCPU(0x001D, 0x20);
    a = 0x4E;
    jump(0xC1A7);
    return;
}

void game::SUB_01A206() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        jump(0xA23A);
        return;
    }
    if (myMapper->readCPU(0x01A9) & 0x80) {
        myMapper->writeCPU(0x01A9, 0x00);
    }
    a = myMapper->readCPU(0x01AA);
    setLoadFlag(a);
    if (flgN) {
        jump(0xA23A);
        return;
    }
    myMapper->writeCPU(0x004B, a);
    if (a == myMapper->readCPU(0x01A9)) {
        popAddress();
        return;
    }
    opDEC(0x004B, 1);
    if (a >= myMapper->readCPU(0x01A9)) {
        goto L_01A22E;
    }
    opINC(0x004B, 2);
L_01A22E:
    a = myMapper->readCPU(0x004B);
    myMapper->writeCPU(0x01AA, a);
    SUB_01A233();
    return;
}

void game::SUB_01A233() {
    y = 0x87;
    myMapper->writeCPU(0x004F, y);
    pushAddress(0xA239);
    SUB_01A23B();
    if (handleReturnAddress(poppedEntry.value, 0xA239)) return;
    SUB_01A23A();
    return;
}

void game::SUB_01A23A() {
    popAddress();
}

void game::SUB_01A23B() {
    myMapper->writeCPU(0x0009, 0xF0);
    x = 0xDA;
    opCMP(myMapper->readCPU(0x004F), 0x87);
    if (flgZ) {
        myMapper->writeCPU(0x0009, 0xDE);
        x = 0xDF;
    }
    myMapper->writeCPU(0x004C, x);
    a = 0x2B;
    pushAddress(0xA253);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xA253)) return;
    a = myMapper->readCPU(0x004F);
    pushAddress(0xA258);
    SUB_01A357();
    if (handleReturnAddress(poppedEntry.value, 0xA258)) return;
    y = 0x08;
    a = myMapper->readCPU(0x004B);
    opLSR_A(3);
    myMapper->writeCPU(0x0008, a);
    if (!flgZ) {
        do {
            a = myMapper->readCPU(0x004C);
            pushAddress(0xA268);
            SUB_01A357();
            if (handleReturnAddress(poppedEntry.value, 0xA268)) return;
            opDEY(1);
            opDEC(0x0008, 1);
        } while (!flgZ);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x07);
    if (!flgZ) {
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x004C));
        a = myMapper->readCPU(0x004B);
        opAND(0x07);
        opCMP(a, 0x05);
        if (flgC) {
            goto L_01A286;
        }
        a = myMapper->readCPU(0x0009);
        myMapper->writeCPU(0x0700 + x, a);
    L_01A286:
        opINX(1);
        opDEY(1);
    }
    while (true) {
        opDEY(1);
        if (flgN) {
            goto L_01A293;
        }
        a = 0xDB;
        pushAddress(0xA28F);
        SUB_01A357();
        if (handleReturnAddress(poppedEntry.value, 0xA28F)) return;
    }
L_01A293:
    jump(0xCC5F);
    return;
}

void game::SUB_01A296() {
    pushAddress(0xA298);
    SUB_01A35C();
    if (handleReturnAddress(poppedEntry.value, 0xA298)) return;
    myMapper->writeCPU(0x004B, a);
    a = 0x1C;
    pushAddress(0xA29F);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xA29F)) return;
    myMapper->writeCPU(0x004E, x);
    a = myMapper->readCPU(0x004B);
    pushAddress(0xA2A6);
    SUB_01A333();
    if (handleReturnAddress(poppedEntry.value, 0xA2A6)) return;
    x = myMapper->readCPU(0x004E);
    pushAddress(0xA2AB);
    SUB_01CC68();
    if (handleReturnAddress(poppedEntry.value, 0xA2AB)) return;
    jump(0xCC5F);
    return;
}

void game::SUB_01A2AF() {
    a = myMapper->readCPU(0x0042);
    opORA(myMapper->readCPU(0x0043));
    if (flgZ) {
        goto L_01A2E1;
    }
    x = 0x42;
    a = 0x01;
    pushAddress(0xA2BB);
    SUB_01CA95();
    if (handleReturnAddress(poppedEntry.value, 0xA2BB)) return;
    y = 0x01;
    do {
        a = myMapper->readCPU(0x0042 + y);
        opAND(0x0F);
        x = a;
        if (a == 0x0F) {
            x = 0x09;
        }
        myMapper->writeCPU(0x0000, x);
        a = myMapper->readCPU(0x0042 + y);
        opAND(0xF0);
        x = a;
        opCMP(a, 0xF0);
        if (!flgZ) {
            goto L_01A2D8;
        }
        x = 0x90;
    L_01A2D8:
        a = x;
        opORA(myMapper->readCPU(0x0000));
        myMapper->writeCPU(0x0042 + y, a);
        opDEY(1);
    } while (!flgN);
L_01A2E1:
    popAddress();
}

void game::SUB_01A2E8() {
    if (myMapper->readCPU(0x0141) == 0) {
        goto L_01A30C;
    }
    y = 0x00;
    opDEC(0x0141, 1);
    a = myMapper->readCPU(0x0141);
    opAND(0x04);
    if (!flgZ) {
        goto L_01A2FE;
    }
    a = myMapper->readCPU(0x0064);
    opASL_A(2);
    y = a;
L_01A2FE:
    x = myMapper->readCPU(0x0020);
    a = 0x7A;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0xA306);
    SUB_01A30D();
    if (handleReturnAddress(poppedEntry.value, 0xA306)) return;
    opINC(0x004C, 1);
    pushAddress(0xA30B);
    SUB_01A30D();
    if (handleReturnAddress(poppedEntry.value, 0xA30B)) return;
L_01A30C:
    popAddress();
}

void game::SUB_01A30D() {
    x = myMapper->readCPU(0x0020);
    a = 0x02;
    pushAddress(0xA313);
    SUB_01A357();
    if (handleReturnAddress(poppedEntry.value, 0xA313)) return;
    a = 0x20;
    pushAddress(0xA318);
    SUB_01A357();
    if (handleReturnAddress(poppedEntry.value, 0xA318)) return;
    a = myMapper->readCPU(0x004C);
    pushAddress(0xA31D);
    SUB_01A357();
    if (handleReturnAddress(poppedEntry.value, 0xA31D)) return;
    pushAddress(0xA320);
    SUB_01A353();
    if (handleReturnAddress(poppedEntry.value, 0xA320)) return;
    pushAddress(0xA323);
    SUB_01A353();
    if (handleReturnAddress(poppedEntry.value, 0xA323)) return;
    jump(0xCC5F);
    return;
}

void game::SUB_01A333() {
    do {
        myMapper->writeCPU(0x004B, a);
        flgC = true;
        opSBC(0x65);
    } while (flgC);
    x = 0x00;
    while (true) {
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
    }
L_01A34F:
    a = x;
    opORA(myMapper->readCPU(0x004B));
    popAddress();
}

void game::SUB_01A353() {
    a = myMapper->readCPU(0xA327 + y);
    opINY(1);
    SUB_01A357();
    return;
}

void game::SUB_01A357() {
    myMapper->writeCPU(0x0700 + x, a);
    opINX(1);
    popAddress();
}

void game::SUB_01A35C() {
    a = myMapper->readCPU(0x002B);
    x = myMapper->readCPU(0x0028);
    if (x == 0x13) {
        x = 0x01;
    }
    myMapper->writeCPU(0x004C, x);
    opCMP(a, 0x06);
    if (!flgC) {
        myMapper->writeCPU(0x004E, a);
        opASL_A(1);
        myMapper->writeCPU(0x004B, a);
        opASL_A(3);
        flgC = false;
        opADC(myMapper->readCPU(0x004B));
        flgC = false;
        opADC(myMapper->readCPU(0x004E));
        flgC = false;
        opADC(myMapper->readCPU(0x004C));
        if (!flgC) {
            opCMP(a, 0x64);
            if (!flgC) {
                opCMP(a, 0x00);
                if (!flgZ) {
                    goto L_01A389;
                }
                a = 0x01;
            L_01A389:
                popAddress();
                return;
            }
        }
    }
    a = 0x63;
    popAddress();
}

void game::SUB_01A38D() {
    x = 0x00;
    if (myMapper->readCPU(0x0070) == 0x02) {
        a = myMapper->readCPU(0x0434);
        opASL_A(1);
        if (!flgC) {
            a = myMapper->readCPU(0x001A);
            opAND(0x03);
            opORA(0x40);
            x = a;
        }
    }
    myMapper->writeCPU(0x0000, x);
    a = myMapper->readCPU(0x0070);
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0x0434);
    opASL_A(1);
    if (flgC) {
        x = 0x06;
    }
    myMapper->writeCPU(0x0001, myMapper->readCPU(0xA46E + x));
    myMapper->writeCPU(0x0002, myMapper->readCPU(0xA46F + x));
    a = myMapper->readCPU(0x004B);
    flgC = true;
    opSBC(0x05);
    opASL_A(1);
    x = 0x01;
    pushAddress(0xA3C4);
    SUB_01CA8B();
    if (handleReturnAddress(poppedEntry.value, 0xA3C4)) return;
    a = myMapper->readCPU(0x0434);
    opAND(0x01);
    opEOR(0x01);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0003, myMapper->readCPU(0xA48E + x));
    myMapper->writeCPU(0x0004, myMapper->readCPU(0xA48F + x));
    a = myMapper->readCPU(0x004B);
    flgC = true;
    opSBC(0x05);
    opASL_A(2);
    x = 0x03;
    pushAddress(0xA3E3);
    SUB_01CA8B();
    if (handleReturnAddress(poppedEntry.value, 0xA3E3)) return;
    myMapper->writeCPU(0x0005, 0x00);
    x = 0x01;
L_01A3EA:
    myMapper->writeCPU(0x0450 + x, myMapper->readCPU(0x0450));
    myMapper->writeCPU(0x0338 + x, myMapper->readCPU(0x0000));
    y = myMapper->readCPU(0x0005);
    myMapper->writeCPU(0x031C + x, myMapper->readCPU(myMapper->readCPU(0x0001) + (myMapper->readCPU((0x0001 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0005);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0003) + (myMapper->readCPU((0x0003 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(myMapper->readCPU(0x003F));
    myMapper->writeCPU(0x0354 + x, a);
    opINY(1);
    myMapper->writeCPU(0x004B, myMapper->readCPU(myMapper->readCPU(0x0003) + (myMapper->readCPU((0x0003 + 1) & 0x00ff) << 8) + y));
    if (myMapper->readCPU(0x0450) != 0) {
        a = myMapper->readCPU(0x004B);
        opEOR(0xFF);
        myMapper->writeCPU(0x004B, a);
        opINC(0x004B, 1);
    }
    a = myMapper->readCPU(0x004B);
    flgC = false;
    opADC(myMapper->readCPU(0x038C));
    myMapper->writeCPU(0x038C + x, a);
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0041));
    a = myMapper->readCPU(0x004B);
    opASL_A(1);
    if (flgC) {
        opDEC(0x0011, 1);
    }
    opROR_A(1);
    y = a;
    flgC = false;
    opADC(myMapper->readCPU(0x0040));
    myMapper->writeCPU(0x0010, a);
    if (flgC) {
        opINC(0x0011, 1);
    }
    a = myMapper->readCPU(0x0010);
    flgC = true;
    opSBC(0x14);
    myMapper->writeCPU(0x0010, a);
    if (!flgC) {
        opDEC(0x0011, 1);
    }
    flgC = true;
    opSBC(myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x0010, a);
    if (!flgC) {
        opDEC(0x0011, 1);
    }
    a = myMapper->readCPU(0x0011);
    flgC = true;
    opSBC(myMapper->readCPU(0x002F));
    if (!flgN) {
        if (!flgZ) {
            goto L_01A45C;
        }
        if (myMapper->readCPU(0x0010) < 0xD8) {
            goto L_01A461;
        }
    }
L_01A45C:
    myMapper->writeCPU(0x0354 + x, 0xFC);
L_01A461:
    opINC(0x0005, 1);
    a = myMapper->readCPU(0x0005);
    opINX(1);
    if (a != 0x02) {
        goto L_01A46B;
    }
    popAddress();
    return;
L_01A46B:
    goto L_01A3EA;
}

void game::SUB_01A824() {
    popAddress();
}

void game::SUB_01A825() {
    pushAddress(0xA827);
    SUB_01A919();
    if (handleReturnAddress(poppedEntry.value, 0xA827)) return;
    a = myMapper->readCPU(0x0434);
    setLoadFlag(a);
    if (flgZ) {
        jump(0xA824);
        return;
    }
    opASL_A(1);
    if (flgC) {
        jump(0xA824);
        return;
    }
    if (myMapper->readCPU(0x0568) != 0x09) {
        jump(0xA824);
        return;
    }
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x000E, myMapper->readCPU(0xFC71 + y));
    myMapper->writeCPU(0x000F, myMapper->readCPU(0xFC72 + y));
    myMapper->writeCPU(0x004F, 0x00);
    while (true) {
        y = myMapper->readCPU(0x004F);
        if (myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y) == 0) {
            jump(0xA824);
            return;
        }
        x = myMapper->readCPU(0x004F);
        a = 0x01;
        while (true) {
            opDEX(2);
            if (flgN) {
                goto L_01A85B;
            }
            opASL_A(1);
        }
    L_01A85B:
        myMapper->writeCPU(0x004C, a);
        opAND(myMapper->readCPU(0x0146));
        if (flgZ) {
            y = myMapper->readCPU(0x004F);
            a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
            opLSR_A(3);
            opAND(0x01);
            if (a == myMapper->readCPU(0x0046)) {
                a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
                opAND(0xF0);
                flgC = false;
                opADC(0x08);
                myMapper->writeCPU(0x0000, a);
                opINY(1);
                if (myMapper->readCPU(0x002B) == 0) {
                    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
                    opAND(0x08);
                    if (!flgZ) {
                        jump(0xA824);
                        return;
                    }
                }
                a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
                opAND(0xF0);
                flgC = false;
                opADC(0x08);
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
                opAND(0x07);
                myMapper->writeCPU(0x0002, a);
                a = 0x08;
                myMapper->writeCPU(0x0010, a);
                myMapper->writeCPU(0x0012, a);
                myMapper->writeCPU(0x0003, myMapper->readCPU(0x0041));
                a = myMapper->readCPU(0x0070);
                opASL_A(1);
                x = a;
                myMapper->writeCPU(0x0013, myMapper->readCPU(0xA8D2 + x));
                x = myMapper->readCPU(0xA8D3 + x);
                if (myMapper->readCPU(0x0450) == 0) {
                    goto L_01A8B5;
                }
                a = x;
                opEOR(0xFF);
                x = a;
                opINX(1);
                opDEC(0x0003, 1);
            L_01A8B5:
                a = x;
                flgC = false;
                opADC(myMapper->readCPU(0x0040));
                x = a;
                a = 0x00;
                opADC(myMapper->readCPU(0x0003));
                myMapper->writeCPU(0x0003, a);
                y = myMapper->readCPU(0x003F);
                a = 0x08;
                myMapper->writeCPU(0x0011, a);
                pushAddress(0xA8C8);
                SUB_01A048();
                if (handleReturnAddress(poppedEntry.value, 0xA8C8)) return;
                if (!flgC) {
                    goto L_01A8D8;
                }
            }
        }
        opINC(0x004F, 2);
    }
L_01A8D8:
    a = myMapper->readCPU(0x0147);
    setLoadFlag(a);
    if (!flgZ) {
        opAND(myMapper->readCPU(0x004C));
        if (!flgZ) {
            goto L_01A8E9;
        }
    }
    myMapper->writeCPU(0x0148, a);
    myMapper->writeCPU(0x0147, myMapper->readCPU(0x004C));
L_01A8E9:
    opINC(0x0148, 1);
    x = 0x01;
    opCMP(x, myMapper->readCPU(0x0148));
    if (flgZ) {
        myMapper->writeCPU(0x0147, 0x00);
        a = 0x15;
        pushAddress(0xA8FC);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0xA8FC)) return;
        pushAddress(0xA8FF);
        SUB_01AA57();
        if (handleReturnAddress(poppedEntry.value, 0xA8FF)) return;
        pushAddress(0xA902);
        SUB_01A989();
        if (handleReturnAddress(poppedEntry.value, 0xA902)) return;
        pushAddress(0xA905);
        SUB_01A9BD();
        if (handleReturnAddress(poppedEntry.value, 0xA905)) return;
        a = myMapper->readCPU(0x004C);
        opAND(myMapper->readCPU(0x0146));
        if (!flgZ) {
            goto L_01A918;
        }
        pushAddress(0xA90F);
        SUB_01AA0B();
        if (handleReturnAddress(poppedEntry.value, 0xA90F)) return;
        a = myMapper->readCPU(0x004C);
        opORA(myMapper->readCPU(0x0146));
        myMapper->writeCPU(0x0146, a);
    }
L_01A918:
    popAddress();
}

void game::SUB_01A919() {
    x = 0x18;
    do {
        if (myMapper->readCPU(0x0434 + x) != 0x03) {
            goto L_01A982;
        }
        if (myMapper->readCPU(0x031C + x) != 0) {
            a = myMapper->readCPU(0x038C + x);
            flgC = true;
            opSBC(0xF8);
            if (a >= 0x08) {
                a = myMapper->readCPU(0x0354 + x);
                flgC = true;
                opSBC(0xD0);
                if (a >= 0x30) {
                    goto L_01A948;
                }
            }
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x046C + x, a);
            myMapper->writeCPU(0x0434 + x, a);
            myMapper->writeCPU(0x031C + x, a);
            if (!flgZ) {
            L_01A948:
                myMapper->writeCPU(0x0338 + x, 0x00);
                myMapper->writeCPU(0x031C + x, 0x95);
                a = myMapper->readCPU(0x03E0 + x);
                flgC = false;
                opADC(0x28);
                myMapper->writeCPU(0x03E0 + x, a);
                a = 0x00;
                opADC(myMapper->readCPU(0x03C4 + x));
                myMapper->writeCPU(0x03C4 + x, a);
                myMapper->writeCPU(0x004E, x);
                pushAddress(0xA967);
                SUB_01AD74();
                if (handleReturnAddress(poppedEntry.value, 0xA967)) return;
                x = myMapper->readCPU(0x004E);
                pushAddress(0xA96C);
                SUB_01AD79();
                if (handleReturnAddress(poppedEntry.value, 0xA96C)) return;
                if (myMapper->readCPU(0x0049) != 0) {
                    opDEC(0x038C + x, 1);
                    a = myMapper->readCPU(0x003C);
                    opAND(0x03);
                    if (a == 0x01) {
                        goto L_01A982;
                    }
                    opINC(0x038C + x, 2);
                }
            }
        }
    L_01A982:
        opINX(1);
    } while (x != 0x1C);
    popAddress();
}

void game::SUB_01A989() {
    pushAddress(0xA98B);
    SUB_01A9F1();
    if (handleReturnAddress(poppedEntry.value, 0xA98B)) return;
    pushAddress(0xA98E);
    SUB_01F918();
    if (handleReturnAddress(poppedEntry.value, 0xA98E)) return;
    y = 0x01;
    x = myMapper->readCPU(0x0020);
    do {
        myMapper->writeCPU(0x0700 + x, 0x02);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0009));
        opINX(1);
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0008));
        opINX(1);
        a = 0x00;
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        a = 0xFF;
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        opINC(0x0008, 1);
        opDEY(1);
    } while (!flgN);
    myMapper->writeCPU(0x0020, x);
    popAddress();
}

void game::SUB_01A9BD() {
    pushAddress(0xA9BF);
    SUB_01A9F1();
    if (handleReturnAddress(poppedEntry.value, 0xA9BF)) return;
    a = myMapper->readCPU(0x000E);
    opPHA();
    a = myMapper->readCPU(0x000F);
    opPHA();
    pushAddress(0xA9C8);
    SUB_01F9A0();
    if (handleReturnAddress(poppedEntry.value, 0xA9C8)) return;
    opPLA();
    myMapper->writeCPU(0x000F, a);
    opPLA();
    myMapper->writeCPU(0x000E, a);
    y = 0x00;
    pushAddress(0xA9D3);
    SUB_01A9E1();
    if (handleReturnAddress(poppedEntry.value, 0xA9D3)) return;
    a = 0x08;
    flgC = false;
    opADC(myMapper->readCPU(0x0016));
    myMapper->writeCPU(0x0016, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0017));
    myMapper->writeCPU(0x0017, a);
    SUB_01A9E1();
    return;
}

void game::SUB_01A9E1() {
    x = 0x0F;
    if (myMapper->readCPU(0x0015) >= 0x02) {
        goto L_01A9EB;
    }
    x = 0xF0;
L_01A9EB:
    a = x;
    opAND(myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_01A9F1() {
    y = myMapper->readCPU(0x004F);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, 0x00);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0x07);
    myMapper->writeCPU(0x0013, a);
    popAddress();
}

void game::SUB_01AA0B() {
    a = 0x0E;
    myMapper->writeCPU(0x004B, a);
    x = 0x04;
    pushAddress(0xAA13);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0xAA13)) return;
    opINX(1);
    if (!flgZ) {
        opDEX(1);
        y = myMapper->readCPU(0x004F);
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        opAND(0x07);
        if (flgZ) {
            goto L_01AA4E;
        }
        myMapper->writeCPU(0x0300 + x, 0x00);
        myMapper->writeCPU(0x0354 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x004E, x);
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        opAND(0x07);
        x = a;
        myMapper->writeCPU(0x004B, myMapper->readCPU(0xAA4F + x));
        x = myMapper->readCPU(0x004E);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        opAND(0xF0);
        flgC = false;
        opADC(0x08);
        flgC = true;
        opSBC(myMapper->readCPU(0x002E));
        myMapper->writeCPU(0x038C + x, a);
        a = myMapper->readCPU(0x004B);
        myMapper->writeCPU(0x0584 + x, a);
        jump(0xEB6A);
        return;
    }
L_01AA4E:
    popAddress();
}

void game::SUB_01AA57() {
    y = myMapper->readCPU(0x004F);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    myMapper->writeCPU(0x0010, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    opAND(0xF8);
    myMapper->writeCPU(0x0012, a);
    x = 0x18;
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0434 + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01AA73;
        }
        if (a != 0x03) {
            goto L_01AAC0;
        }
    L_01AA73:
        myMapper->writeCPU(0x0434 + x, 0x03);
        myMapper->writeCPU(0x031C + x, 0x95);
        myMapper->writeCPU(0x046C + x, 0x01);
        a = myMapper->readCPU(0xAAC9 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0010));
        opAND(0xF0);
        myMapper->writeCPU(0x0354 + x, a);
        opINY(1);
        a = myMapper->readCPU(0xAAC9 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0012));
        flgC = true;
        opSBC(myMapper->readCPU(0x002E));
        opAND(0xF0);
        myMapper->writeCPU(0x038C + x, a);
        opINY(1);
        myMapper->writeCPU(0x03E0 + x, myMapper->readCPU(0xAAC9 + y));
        opINY(1);
        myMapper->writeCPU(0x03C4 + x, myMapper->readCPU(0xAAC9 + y));
        opINY(1);
        myMapper->writeCPU(0x0418 + x, myMapper->readCPU(0xAAC9 + y));
        opINY(1);
        myMapper->writeCPU(0x03FC + x, myMapper->readCPU(0xAAC9 + y));
        opINY(1);
    L_01AAB9:
        opINX(1);
        a = x;
    } while (a != 0x1C);
    popAddress();
    return;
L_01AAC0:
    opINY(6);
    goto L_01AAB9;
}

void game::SUB_01AAE1() {
    popAddress();
}

void game::SUB_01AAE2() {
    a = myMapper->readCPU(0x0028);
    if (a != 0x04) {
        if (a == 0x05) {
            goto L_01AAF0;
        }
        if (a != 0x0A) {
            jump(0xAAE1);
            return;
        }
    }
L_01AAF0:
    myMapper->writeCPU(0x004E, 0x17);
L_01AAF4:
    x = myMapper->readCPU(0x004E);
    if (myMapper->readCPU(0x0434 + x) == 0x01) {
        a = myMapper->readCPU(0x04A4 + x);
        setLoadFlag(a);
        if (flgZ) {
            myMapper->writeCPU(0x031C + x, a);
            if (flgZ) {
                goto L_01AB70;
            }
            myMapper->writeCPU(0x0434 + x, a);
            if (a != 0x01) {
                goto L_01AB70;
            }
        }
        x = myMapper->readCPU(0x004E);
        pushAddress(0xAB12);
        SUB_01ABD6();
        if (handleReturnAddress(poppedEntry.value, 0xAB12)) return;
        x = myMapper->readCPU(0x004E);
        pushAddress(0xAB17);
        SUB_01AC10();
        if (handleReturnAddress(poppedEntry.value, 0xAB17)) return;
        x = myMapper->readCPU(0x004E);
        pushAddress(0xAB1C);
        SUB_01AC4F();
        if (handleReturnAddress(poppedEntry.value, 0xAB1C)) return;
        x = myMapper->readCPU(0x004E);
        a = myMapper->readCPU(0x002E);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x0012, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x002F));
        myMapper->writeCPU(0x004B, a);
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(myMapper->readCPU(0x0012));
        myMapper->writeCPU(0x0010, a);
        if (!flgC) {
            opINC(0x004B, 1);
        }
        a = myMapper->readCPU(0x0011);
        flgC = true;
        opSBC(myMapper->readCPU(0x004B));
        myMapper->writeCPU(0x0011, a);
        pushAddress(0xAB40);
        SUB_01AB83();
        if (handleReturnAddress(poppedEntry.value, 0xAB40)) return;
        a = myMapper->readCPU(0x04A4 + x);
        opAND(0x01);
        if (a != myMapper->readCPU(0x0046)) {
            goto L_01AB7C;
        }
        if (myMapper->readCPU(0x0370 + x) != 0) {
            a = myMapper->readCPU(0x003C);
            opAND(0x04);
            if (!flgZ) {
                goto L_01AB5B;
            }
            a = myMapper->readCPU(0x0142);
            opLSR_A(1);
            if (!flgC) {
                goto L_01AB63;
            }
        }
    L_01AB5B:
        a = myMapper->readCPU(0x0010);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x038C + x, a);
    L_01AB63:
        a = myMapper->readCPU(0x04A4 + x);
        opAND(0xF8);
        myMapper->writeCPU(0x0354 + x, a);
        myMapper->writeCPU(0x0338 + x, 0x00);
    }
    do {
    L_01AB70:
        opINC(0x004E, 1);
        a = myMapper->readCPU(0x004E);
        if (a != 0x1B) {
            goto L_01AB79;
        }
        popAddress();
        return;
    L_01AB79:
        goto L_01AAF4;
    L_01AB7C:
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x031C + x, a);
    } while (flgZ);
    SUB_01AB83();
    return;
}

void game::SUB_01AB83() {
    myMapper->writeCPU(0x0450 + x, 0x00);
    if (myMapper->readCPU(0x0011) == 0) {
        if (myMapper->readCPU(0x0010) >= 0xE0) {
            goto L_01AB98;
        }
        myMapper->writeCPU(0x031C + x, 0xC9);
        popAddress();
        return;
    }
L_01AB98:
    a = myMapper->readCPU(0x0011);
    setLoadFlag(a);
    if (!flgN) {
        goto L_01ABB1;
    }
    if (a != 0xFF) {
        goto L_01ABCE;
    }
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0x20);
    if (a >= 0x20) {
        goto L_01ABCE;
    }
    opLSR_A(3);
    opAND(0x03);
    goto L_01ABC6;
L_01ABB1:
    if (myMapper->readCPU(0x0011) != 0) {
        goto L_01ABCE;
    }
    myMapper->writeCPU(0x0450 + x, 0x01);
    a = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(0x20);
    opLSR_A(3);
    opAND(0x03);
    opEOR(0x03);
L_01ABC6:
    y = a;
    a = myMapper->readCPU(0xABD2 + y);
    do {
        myMapper->writeCPU(0x031C + x, a);
        popAddress();
        return;
    L_01ABCE:
        a = 0x00;
        setLoadFlag(a);
    } while (flgZ);
    brk();
    //NOP
    SUB_01ABD6();
    return;
}

void game::SUB_01ABD6() {
    a = x;
    flgC = false;
    opADC(0x38);
    x = a;
    SUB_01ABDB();
    return;
}

void game::SUB_01ABDB() {
    a = myMapper->readCPU(0x03C4 + x);
    opASL_A(1);
    if (flgC) {
        y = myMapper->readCPU(0x0450 + x);
        do {
            opDEC(0x04DC + x, 1);
            opDEY(1);
        } while (!flgN);
    }
    y = myMapper->readCPU(0x0450 + x);
    opDEY(1);
    if (!flgN) {
        do {
            opASL_A(1);
            if (!flgC) {
                goto L_01ABF6;
            }
            opINC(0x04DC + x, 1);
        L_01ABF6:
            opDEY(1);
        } while (!flgN);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x04C0 + x));
    myMapper->writeCPU(0x04C0 + x, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x04DC + x));
    if (a != 0x80) {
        goto L_01AC0C;
    }
    a = myMapper->readCPU(0x04DC + x);
L_01AC0C:
    myMapper->writeCPU(0x04DC + x, a);
    popAddress();
}

void game::SUB_01AC10() {
    a = x;
    flgC = false;
    opADC(0x38);
    x = a;
    SUB_01AC15();
    return;
}

void game::SUB_01AC15() {
    a = myMapper->readCPU(0x04DC + x);
    opEOR(0xFF);
    y = a;
    opINY(1);
    a = y;
    opASL_A(1);
    if (flgC) {
        y = myMapper->readCPU(0x0450 + x);
        do {
            opDEC(0x03C4 + x, 1);
            opDEY(1);
        } while (!flgN);
    }
    y = myMapper->readCPU(0x0450 + x);
    opDEY(1);
    if (!flgN) {
        do {
            opASL_A(1);
            if (!flgC) {
                goto L_01AC35;
            }
            opINC(0x03C4 + x, 1);
        L_01AC35:
            opDEY(1);
        } while (!flgN);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x03E0 + x, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x03C4 + x));
    if (a != 0x80) {
        goto L_01AC4B;
    }
    a = myMapper->readCPU(0x03C4 + x);
L_01AC4B:
    myMapper->writeCPU(0x03C4 + x, a);
    popAddress();
}

void game::SUB_01AC4F() {
    a = x;
    flgC = false;
    opADC(0x38);
    x = a;
    SUB_01AC54();
    return;
}

void game::SUB_01AC54() {
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x054C + x));
    a = myMapper->readCPU(0x04DC + x);
    opAND(0x80);
    if (!flgZ) {
        opDEC(0x0011, 1);
    }
    a = myMapper->readCPU(0x04DC + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0530 + x));
    myMapper->writeCPU(0x0010, a);
    if (!flgC) {
        goto L_01AC6F;
    }
    opINC(0x0011, 1);
L_01AC6F:
    popAddress();
}

void game::SUB_01AC70() {
    myMapper->writeCPU(0x004E, 0x1A);
    do {
        x = myMapper->readCPU(0x004E);
        myMapper->writeCPU(0x0370 + x, 0x00);
        if (myMapper->readCPU(0x04A4 + x) != 0) {
            if (myMapper->readCPU(0x031C + x) != 0xC9) {
                goto L_01ACBC;
            }
            x = myMapper->readCPU(0x004E);
            y = 0x10;
            if (myMapper->readCPU(0x046C) != 0x03) {
                goto L_01AC94;
            }
            y = 0x0C;
        L_01AC94:
            a = y;
            flgC = false;
            opADC(myMapper->readCPU(0x003F));
            y = a;
            a = myMapper->readCPU(0x0354 + x);
            flgC = false;
            opADC(0x04);
            myMapper->writeCPU(0x0000, a);
            myMapper->writeCPU(0x0001, myMapper->readCPU(0x038C + x));
            myMapper->writeCPU(0x0010, 0x04);
            a = 0x01;
            myMapper->writeCPU(0x0011, a);
            myMapper->writeCPU(0x0013, a);
            a = 0x10;
            myMapper->writeCPU(0x0012, a);
            x = myMapper->readCPU(0x038C);
            pushAddress(0xACB9);
            SUB_01A011();
            if (handleReturnAddress(poppedEntry.value, 0xACB9)) return;
            if (!flgC) {
                goto L_01ACCF;
            }
        }
    L_01ACBC:
        opDEC(0x004E, 1);
    } while (myMapper->readCPU(0x004E) != 0x16);
    a = myMapper->readCPU(0x0142);
    opAND(0xFB);
    myMapper->writeCPU(0x0142, a);
    jump(0xAD4F);
    return;
L_01ACCF:
    x = 0x10;
    a = myMapper->readCPU(0x046C);
    if (a != 0x03) {
        if (a != 0x02) {
            goto L_01ACE5;
        }
        if (myMapper->readCPU(0x0530) != 0x03) {
            goto L_01ACE5;
        }
    }
    x = 0x0C;
L_01ACE5:
    myMapper->writeCPU(0x004C, x);
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x04A4 + x);
    opAND(0xF8);
    flgC = true;
    opSBC(myMapper->readCPU(0x004C));
    myMapper->writeCPU(0x0354, a);
    myMapper->writeCPU(0x003F, a);
    a = myMapper->readCPU(0x0142);
    opAND(0xFB);
    opORA(0x04);
    myMapper->writeCPU(0x0142, a);
    a = myMapper->readCPU(0x0584);
    opAND(0x03);
    if (!flgZ) {
        jump(0xAD68);
        return;
    }
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x0370 + x, 0x01);
    myMapper->writeCPU(0x003E, 0x00);
    myMapper->writeCPU(0x0010, 0x01);
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x03FC + x);
    myMapper->writeCPU(0x003D, a);
    opAND(0x80);
    if (flgZ) {
        goto L_01AD2F;
    }
    a = myMapper->readCPU(0x03FC + x);
    opEOR(0xFF);
    x = a;
    opINX(1);
    myMapper->writeCPU(0x003D, x);
    myMapper->writeCPU(0x0010, 0x02);
L_01AD2F:
    a = myMapper->readCPU(0x0010);
    opASL_A(2);
    opAND(0x08);
    myMapper->writeCPU(0x004C, a);
    a = myMapper->readCPU(0x0142);
    opAND(0xF7);
    opORA(myMapper->readCPU(0x004C));
    myMapper->writeCPU(0x0142, a);
    x = myMapper->readCPU(0x004E);
    y = myMapper->readCPU(0x0488 + x);
    do {
        opASL_M(0x003D, 1);
        opROL_M(0x003E, 1);
        opDEY(1);
    } while (!flgN);
    flgC = true;
    popAddress();
}

void game::SUB_01AD4F() {
    myMapper->writeCPU(0x003D, 0x00);
    myMapper->writeCPU(0x003E, 0x01);
    a = myMapper->readCPU(0x046C);
    if (a != 0x04) {
        goto L_01AD66;
    }
    myMapper->writeCPU(0x003D, 0x80);
    a = 0x00;
    myMapper->writeCPU(0x003E, a);
L_01AD66:
    flgC = false;
    popAddress();
}

void game::SUB_01AD68() {
    pushAddress(0xAD6A);
    SUB_01AD4F();
    if (handleReturnAddress(poppedEntry.value, 0xAD6A)) return;
    a = myMapper->readCPU(0x0584);
    opAND(0x03);
    myMapper->writeCPU(0x0010, a);
    flgC = true;
    popAddress();
}

void game::SUB_01AD74() {
    a = x;
    flgC = false;
    opADC(0x38);
    x = a;
    SUB_01AD79();
    return;
}

void game::SUB_01AD79() {
    a = myMapper->readCPU(0x03E0 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0370 + x));
    myMapper->writeCPU(0x0370 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opADC(myMapper->readCPU(0x0354 + x));
    myMapper->writeCPU(0x0354 + x, a);
    popAddress();
}

void game::SUB_01AD8D() {
    myMapper->writeCPU(0x0450, 0x01);
    myMapper->writeCPU(0x0584, 0x02);
    myMapper->writeCPU(0x003F, 0xC1);
    myMapper->writeCPU(0x038C, 0xFF);
    myMapper->writeCPU(0x0418, 0x80);
    myMapper->writeCPU(0x03FC, 0xFF);
    myMapper->writeCPU(0x0338, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x0451, a);
    myMapper->writeCPU(0x0339, a);
    myMapper->writeCPU(0x0355, 0x48);
    a = 0xE0;
    myMapper->writeCPU(0x038D, a);
    myMapper->writeCPU(0x0419, a);
    myMapper->writeCPU(0x03FD, 0xFF);
    myMapper->writeCPU(0x031D, 0x1A);
    myMapper->writeCPU(0x0452, 0x01);
    myMapper->writeCPU(0x0356, 0x80);
    myMapper->writeCPU(0x038E, 0x10);
    myMapper->writeCPU(0x041A, 0x38);
    myMapper->writeCPU(0x03FE, 0x00);
    myMapper->writeCPU(0x03E2, 0xD8);
    myMapper->writeCPU(0x03C6, 0xFF);
    myMapper->writeCPU(0x033A, 0x00);
    x = 0x03;
    a = 0x00;
    myMapper->writeCPU(0x0418 + x, a);
    myMapper->writeCPU(0x03FC + x, a);
    myMapper->writeCPU(0x04F8 + x, a);
    myMapper->writeCPU(0x0584 + x, a);
    myMapper->writeCPU(0x04C0 + x, a);
    myMapper->writeCPU(0x054C + x, a);
    myMapper->writeCPU(0x0514 + x, 0x10);
    myMapper->writeCPU(0x0568 + x, 0x80);
    myMapper->writeCPU(0x03E0 + x, 0x60);
    myMapper->writeCPU(0x03C4 + x, 0x08);
    myMapper->writeCPU(0x04DC + x, 0x01);
    myMapper->writeCPU(0x0530 + x, 0x3E);
    popAddress();
}

void game::SUB_01AE2B() {
    pushAddress(0xAE2D);
    SUB_01AE87();
    if (handleReturnAddress(poppedEntry.value, 0xAE2D)) return;
    pushAddress(0xAE30);
    SUB_01AE73();
    if (handleReturnAddress(poppedEntry.value, 0xAE30)) return;
    opINC(0x04C2, 1);
    a = myMapper->readCPU(0x04C2);
    opLSR_A(2);
    opAND(0x01);
    flgC = false;
    opADC(0x1B);
    myMapper->writeCPU(0x031E, a);
    myMapper->writeCPU(0x031F, a);
    x = 0x02;
    pushAddress(0xAE48);
    SUB_01AD79();
    if (handleReturnAddress(poppedEntry.value, 0xAE48)) return;
    pushAddress(0xAE4B);
    SUB_01AD74();
    if (handleReturnAddress(poppedEntry.value, 0xAE4B)) return;
    x = 0x03;
    pushAddress(0xAE50);
    SUB_01ABDB();
    if (handleReturnAddress(poppedEntry.value, 0xAE50)) return;
    pushAddress(0xAE53);
    SUB_01AC15();
    if (handleReturnAddress(poppedEntry.value, 0xAE53)) return;
    pushAddress(0xAE56);
    SUB_01AC54();
    if (handleReturnAddress(poppedEntry.value, 0xAE56)) return;
    a = myMapper->readCPU(0x0010);
    myMapper->writeCPU(0x0354 + x, a);
    x = 0x03;
    pushAddress(0xAE60);
    SUB_01ABD6();
    if (handleReturnAddress(poppedEntry.value, 0xAE60)) return;
    x = 0x03;
    pushAddress(0xAE65);
    SUB_01AC10();
    if (handleReturnAddress(poppedEntry.value, 0xAE65)) return;
    x = 0x03;
    pushAddress(0xAE6A);
    SUB_01AC4F();
    if (handleReturnAddress(poppedEntry.value, 0xAE6A)) return;
    x = 0x03;
    myMapper->writeCPU(0x038C + x, myMapper->readCPU(0x0010));
    popAddress();
}

void game::SUB_01AE73() {
    a = myMapper->readCPU(0x038C);
    if (a == 0x80) {
        goto L_01AE82;
    }
    x = 0x00;
    pushAddress(0xAE7E);
    SUB_01AD74();
    if (handleReturnAddress(poppedEntry.value, 0xAE7E)) return;
    jump(0x9458);
    return;
L_01AE82:
    a = 0x11;
    jump(0x9BBA);
    return;
}

void game::SUB_01AE87() {
    x = 0x01;
    jump(0xAD74);
    return;
}

void game::SUB_01AE8C() {
    pushAddress(0xAE8E);
    SUB_01C14B();
    if (handleReturnAddress(poppedEntry.value, 0xAE8E)) return;
    pushAddress(0xAE91);
    SUB_01CAA1();
    if (handleReturnAddress(poppedEntry.value, 0xAE91)) return;
    x = 0x00;
    pushAddress(0xAE96);
    SUB_01CB83();
    if (handleReturnAddress(poppedEntry.value, 0xAE96)) return;
    x = 0x02;
    pushAddress(0xAE9B);
    SUB_01CB83();
    if (handleReturnAddress(poppedEntry.value, 0xAE9B)) return;
    pushAddress(0xAE9E);
    SUB_01D11B();
    if (handleReturnAddress(poppedEntry.value, 0xAE9E)) return;
    a = 0x0A;
    pushAddress(0xAEA3);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xAEA3)) return;
    a = 0x05;
    pushAddress(0xAEA8);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xAEA8)) return;
    a = 0x00;
    myMapper->writeCPU(0x0451, a);
    myMapper->writeCPU(0x0301, a);
    myMapper->writeCPU(0x0339, a);
    myMapper->writeCPU(0x0452, a);
    myMapper->writeCPU(0x0302, a);
    myMapper->writeCPU(0x033A, a);
    myMapper->writeCPU(0x038D, 0x30);
    myMapper->writeCPU(0x0355, 0x18);
    myMapper->writeCPU(0x031D, 0x94);
    myMapper->writeCPU(0x038E, 0x30);
    myMapper->writeCPU(0x0356, 0x58);
    myMapper->writeCPU(0x031E, 0x96);
    popAddress();
}

void game::SUB_01B7DC() {
    a = 0x0B;
    opAND(myMapper->readCPU(0x001C));
    myMapper->writeCPU(0x001C, a);
    a = 0x00;
    myMapper->writeCPU(0x00FD, a);
    myMapper->writeCPU(0x00FC, a);
    myMapper->writeCPU(0x00F4, a);
    pushAddress(0xB7EC);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xB7EC)) return;
    pushAddress(0xB7EF);
    SUB_01AE8C();
    if (handleReturnAddress(poppedEntry.value, 0xB7EF)) return;
    myMapper->writeCPU(0x00FE, 0x1E);
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    myMapper->writeCPU(0x00FF, a);
    pushAddress(0xB7FC);
    SUB_01B9FC();
    if (handleReturnAddress(poppedEntry.value, 0xB7FC)) return;
    jump(0xC371);
    return;
}

void game::SUB_01B823() {
    a = myMapper->readCPU(0x0019);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01B833;
    }
    pushAddress(0xB829);
    SUB_01B99D();
    if (handleReturnAddress(poppedEntry.value, 0xB829)) return;
    if (!flgC) {
        jump(0xB858);
        return;
    }
    opINC(0x0019, 1);
    myMapper->writeCPU(0x001E, 0x00);
    popAddress();
    return;
L_01B833:
    x = 0x03;
    pushAddress(0xB837);
    SUB_01B9D6();
    if (handleReturnAddress(poppedEntry.value, 0xB837)) return;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        jump(0xB858);
        return;
    }
    opDEC(0x001E, 1);
    if (!flgZ) {
        jump(0xB858);
        return;
    }
    pushAddress(0xB844);
    SUB_01C102();
    if (handleReturnAddress(poppedEntry.value, 0xB844)) return;
    myMapper->writeCPU(0x0018, 0x02);
    myMapper->writeCPU(0x0019, 0x00);
    a = 0x03;
    pushAddress(0xB851);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xB851)) return;
    a = myMapper->readCPU(0x00F3);
    opAND(0x03);
    myMapper->writeCPU(0x00F3, a);
    SUB_01B858();
    return;
}

void game::SUB_01B858() {
    popAddress();
}

void game::SUB_01B859() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (flgZ) {
        a = 0x01;
        myMapper->writeCPU(0x00F4, a);
        myMapper->writeCPU(0x07FB, a);
        if (myMapper->readCPU(0x00F3) == 0x03) {
            myMapper->writeCPU(0x00F3, 0x00);
        }
        x = myMapper->readCPU(0x00F3);
        myMapper->writeCPU(0x0028, myMapper->readCPU(0xB8CC + x));
        x = myMapper->readCPU(0x00F3);
        a = myMapper->readCPU(0xB8CF + x);
        pushAddress(0xB87E);
        SUB_01FD23();
        if (handleReturnAddress(poppedEntry.value, 0xB87E)) return;
        pushAddress(0xB881);
        SUB_01D11B();
        if (handleReturnAddress(poppedEntry.value, 0xB881)) return;
        x = 0x00;
        myMapper->writeCPU(0x002B, x);
        myMapper->writeCPU(0x0070, x);
        myMapper->writeCPU(0x015B, x);
        opINX(1);
        myMapper->writeCPU(0x002C, x);
        pushAddress(0xB890);
        SUB_01CB81();
        if (handleReturnAddress(poppedEntry.value, 0xB890)) return;
        pushAddress(0xB893);
        SUB_01C966();
        if (handleReturnAddress(poppedEntry.value, 0xB893)) return;
        myMapper->writeCPU(0x015B, 0x00);
        myMapper->writeCPU(0x0064, a);
        myMapper->writeCPU(0x0018, 0x05);
        myMapper->writeCPU(0x0019, 0x00);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x007E);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0xB8AA);
        SUB_01FEB3();
        if (handleReturnAddress(poppedEntry.value, 0xB8AA)) return;
        a = myMapper->readCPU(0x00F5);
        if (a == 0xFF) {
            a = myMapper->readCPU(0x00F7);
            if (a != 0xFF) {
                goto L_01B8BE;
            }
            a = 0x00;
            myMapper->writeCPU(0x0018, a);
            myMapper->writeCPU(0x0019, a);
            popAddress();
            return;
        }
    }
L_01B8BE:
    pushAddress(0xB8C0);
    SUB_01CED0();
    if (handleReturnAddress(poppedEntry.value, 0xB8C0)) return;
    if (myMapper->readCPU(0x001E) == 0) {
        jump(0xB858);
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x0028, a);
    jump(0xC37A);
    return;
}

void game::SUB_01B8D2() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (flgZ) {
        a = 0x40;
        opORA(myMapper->readCPU(0x001C));
        myMapper->writeCPU(0x001C, a);
        a = 0x50;
        jump(0xC363);
        return;
    }
    opDEC(0x0025, 1);
    if (flgZ) {
        goto L_01B8F8;
    }
    a = 0x08;
    opAND(myMapper->readCPU(0x0025));
    opASL_A(4);
    opORA(0x03);
    jump(0xCC95);
    return;
L_01B8F8:
    pushAddress(0xB8FA);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xB8FA)) return;
    a = 0x06;
    pushAddress(0xB8FF);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xB8FF)) return;
    a = 0x00;
    myMapper->writeCPU(0x001D, a);
    myMapper->writeCPU(0x01B1, a);
    myMapper->writeCPU(0x00F4, a);
    pushAddress(0xB90B);
    SUB_01C102();
    if (handleReturnAddress(poppedEntry.value, 0xB90B)) return;
    a = 0x04;
    jump(0xC37A);
    return;
}

void game::SUB_01B911() {
    a = 0x00;
    myMapper->writeCPU(0x015B, a);
    myMapper->writeCPU(0x0064, a);
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (flgZ) {
        pushAddress(0xB91E);
        SUB_01CB81();
        if (handleReturnAddress(poppedEntry.value, 0xB91E)) return;
        x = 0x00;
        myMapper->writeCPU(0x0028, x);
        pushAddress(0xB925);
        SUB_01C966();
        if (handleReturnAddress(poppedEntry.value, 0xB925)) return;
        a = 0x01;
        pushAddress(0xB92A);
        SUB_01FD23();
        if (handleReturnAddress(poppedEntry.value, 0xB92A)) return;
        a = 0x0D;
        pushAddress(0xB92F);
        SUB_01CC95();
        if (handleReturnAddress(poppedEntry.value, 0xB92F)) return;
        a = 0x27;
        pushAddress(0xB934);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0xB934)) return;
        jump(0xC365);
        return;
    }
    opDEX(1);
    if (!flgZ) {
        goto L_01B946;
    }
    pushAddress(0xB93D);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xB93D)) return;
    x = 0x06;
    pushAddress(0xB942);
    SUB_01CB83();
    if (handleReturnAddress(poppedEntry.value, 0xB942)) return;
    jump(0xC365);
    return;
L_01B946:
    opDEX(1);
    if (!flgZ) {
        goto L_01B969;
    }
    pushAddress(0xB94B);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xB94B)) return;
    myMapper->writeCPU(0x001D, 0x50);
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    myMapper->writeCPU(0x00FF, a);
    a = 0x40;
    myMapper->writeCPU(0x01A9, a);
    pushAddress(0xB95D);
    SUB_01A169();
    if (handleReturnAddress(poppedEntry.value, 0xB95D)) return;
    pushAddress(0xB960);
    SUB_01AD8D();
    if (handleReturnAddress(poppedEntry.value, 0xB960)) return;
    a = 0x70;
    myMapper->writeCPU(0x001D, a);
    jump(0xC365);
    return;
    do {
        do {
            popAddress();
            return;
        L_01B969:
            opDEX(1);
            if (!flgZ) {
                goto L_01B972;
            }
            pushAddress(0xB96E);
            SUB_01A17D();
            if (handleReturnAddress(poppedEntry.value, 0xB96E)) return;
            jump(0xC365);
            return;
        L_01B972:
            a = 0x00;
            myMapper->writeCPU(0x002E, a);
            myMapper->writeCPU(0x00FD, a);
            myMapper->writeCPU(0x002F, a);
            pushAddress(0xB97C);
            SUB_01AE2B();
            if (handleReturnAddress(poppedEntry.value, 0xB97C)) return;
            a = myMapper->readCPU(0x001A);
            opAND(0x03);
        } while (!flgZ);
        opDEC(0x001D, 1);
    } while (!flgZ);
    a = 0x03;
    pushAddress(0xB98B);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xB98B)) return;
    x = 0x00;
    myMapper->writeCPU(0x0028, x);
    myMapper->writeCPU(0x0434, x);
    myMapper->writeCPU(0x0070, x);
    myMapper->writeCPU(0x002B, x);
    opINX(1);
    myMapper->writeCPU(0x002C, x);
    jump(0xC229);
    return;
}

void game::SUB_01B99D() {
    pushAddress(0xB99F);
    SUB_01B9C3();
    if (handleReturnAddress(poppedEntry.value, 0xB99F)) return;
    a = myMapper->readCPU(0x001A);
    opAND(0x07);
    if (!flgZ) {
        goto L_01B9BF;
    }
    opINC(0x001E, 1);
    a = myMapper->readCPU(0x001E);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0xBA17 + y);
    if (a == 0xFF) {
        goto L_01B9C1;
    }
    myMapper->writeCPU(0x038C, a);
    a = myMapper->readCPU(0xBA18 + y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0354, a);
L_01B9BF:
    flgC = false;
    popAddress();
    return;
L_01B9C1:
    flgC = true;
    popAddress();
}

void game::SUB_01B9C3() {
    x = 0x00;
    a = myMapper->readCPU(0x001E);
    if (a < 0x04) {
        jump(0xB9D6);
        return;
    }
    opINX(1);
    if (a < 0x08) {
        jump(0xB9D6);
        return;
    }
    opINX(1);
    if (a < 0x0E) {
        jump(0xB9D6);
        return;
    }
    opINX(1);
    SUB_01B9D6();
    return;
}

void game::SUB_01B9D6() {
    a = x;
    opASL_A(2);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x001A);
    opROR_A(2);
    opAND(0x03);
    flgC = false;
    opADC(myMapper->readCPU(0x0000));
    y = a;
    myMapper->writeCPU(0x031C, myMapper->readCPU(0xB9EC + y));
    popAddress();
}

void game::SUB_01B9FC() {
    a = 0x00;
    myMapper->writeCPU(0x001E, a);
    myMapper->writeCPU(0x0338, a);
    myMapper->writeCPU(0x031C, a);
    myMapper->writeCPU(0x0450, a);
    myMapper->writeCPU(0x0300, a);
    myMapper->writeCPU(0x038C, 0xDC);
    a = 0x77;
    myMapper->writeCPU(0x0354, a);
    popAddress();
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
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xC016)) return;
    x = 0xFF;
    s = x;
    pushAddress(0xC01C);
    SUB_01C16D();
    if (handleReturnAddress(poppedEntry.value, 0xC01C)) return;
    pushAddress(0xC01F);
    SUB_01C18E();
    if (handleReturnAddress(poppedEntry.value, 0xC01F)) return;
    pushAddress(0xC022);
    SUB_01C19B();
    if (handleReturnAddress(poppedEntry.value, 0xC022)) return;
    pushAddress(0xC025);
    SUB_01C0F7();
    if (handleReturnAddress(poppedEntry.value, 0xC025)) return;
    pushAddress(0xC028);
    SUB_01C14B();
    if (handleReturnAddress(poppedEntry.value, 0xC028)) return;
    a = 0x06;
    myMapper->writeCPU(0x0024, a);
    pushAddress(0xC02F);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xC02F)) return;
}

void game::repeat() {
    a = myMapper->readCPU(0x006F);
    opORA(myMapper->readCPU(0x001A));
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0xC03F + y);
    myMapper->writeCPU(0x006F, a);
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
        jump(0xC0C0);
        return;
    }
    pushAddress(0xC061);
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xC061)) return;
    a = 0x00;
    myMapper->writeCPU(0x2003, a);
    myMapper->writeCPU(0x4014, 0x02);
    y = 0x00;
    pushAddress(0xC070);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xC070)) return;
    pushAddress(0xC073);
    jump(0x800A);
    if (handleReturnAddress(poppedEntry.value, 0xC073)) return;
    pushAddress(0xC076);
    SUB_01C1D4();
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
    SUB_01F87D();
    if (handleReturnAddress(poppedEntry.value, 0xC08C)) return;
    pushAddress(0xC08F);
    SUB_01C11F();
    if (handleReturnAddress(poppedEntry.value, 0xC08F)) return;
    opINC(0x001B, 1);
    y = 0x00;
    pushAddress(0xC096);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xC096)) return;
    pushAddress(0xC099);
    jump(0x838A);
    if (handleReturnAddress(poppedEntry.value, 0xC099)) return;
    pushAddress(0xC09C);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xC09C)) return;
    y = 0x06;
    myMapper->writeCPU(0x0027, y);
    pushAddress(0xC0A3);
    SUB_01C8CD();
    if (handleReturnAddress(poppedEntry.value, 0xC0A3)) return;
    pushAddress(0xC0A6);
    SUB_01C1E4();
    if (handleReturnAddress(poppedEntry.value, 0xC0A6)) return;
    y = 0x00;
    pushAddress(0xC0AB);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xC0AB)) return;
    pushAddress(0xC0AE);
    jump(0x8052);
    if (handleReturnAddress(poppedEntry.value, 0xC0AE)) return;
    pushAddress(0xC0B1);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xC0B1)) return;
    pushAddress(0xC0B4);
    SUB_01CCEE();
    if (handleReturnAddress(poppedEntry.value, 0xC0B4)) return;
    SUB_01C0B9();
    return;
}

void game::SUB_01C0B9() {
    a = 0x00;
    myMapper->writeCPU(0x001B, a);
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    popStatus();
	popIRAddress();
    return;
}



void game::SUB_01C0C0() {
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
    SUB_01F87D();
    if (handleReturnAddress(poppedEntry.value, 0xC0CD)) return;
    pushAddress(0xC0D0);
    SUB_01C11F();
    if (handleReturnAddress(poppedEntry.value, 0xC0D0)) return;
    pushAddress(0xC0D3);
    SUB_01C0D7();
    if (handleReturnAddress(poppedEntry.value, 0xC0D3)) return;
    jump(0xC0B9);
    return;
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
    SUB_01C1D8();
    if (handleReturnAddress(poppedEntry.value, 0xC0E3)) return;
    pushAddress(0xC0E6);
    jump(0x838A);
    if (handleReturnAddress(poppedEntry.value, 0xC0E6)) return;
    pushAddress(0xC0E9);
    SUB_01C1CF();
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
    SUB_01C10D();
    return;
}

void game::SUB_01C10D() {
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
    a = myMapper->readCPU(0x007F);
    setLoadFlag(a);
    if (!flgZ) {
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
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xC160)) return;
    a = 0x55;
    pushAddress(0xC165);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xC165)) return;
    pushAddress(0xC168);
    SUB_01C102();
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
    SUB_01C176();
    return;
}

void game::SUB_01C176() {
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
    SUB_01C1D8();
    if (handleReturnAddress(poppedEntry.value, 0xC1BB)) return;
    a = myMapper->readCPU(0x07F6);
    pushAddress(0xC1C1);
    jump(0x8187);
    if (handleReturnAddress(poppedEntry.value, 0xC1C1)) return;
    pushAddress(0xC1C4);
    SUB_01C1CF();
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
    SUB_01C91C();
    if (handleReturnAddress(poppedEntry.value, 0xC1EE)) return;
L_01C1EF:
    a = myMapper->readCPU(0x0018);
    pushAddress(0xC1F3);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xC1F3)) return;
    SUB_01C216();
    return;
}

void game::SUB_01C216() {
    a = 0x08;
    myMapper->writeCPU(0x0025, a);
    do {
        pushAddress(0xC21C);
        SUB_01CB56();
        if (handleReturnAddress(poppedEntry.value, 0xC21C)) return;
        opDEC(0x0025, 1);
    } while (!flgZ);
    pushAddress(0xC223);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC223)) return;
    a = myMapper->readCPU(0x001D);
    opCMP(a, 0x0F);
    popAddress();
}

void game::SUB_01C229() {
    pushAddress(0xC22B);
    SUB_01D11B();
    if (handleReturnAddress(poppedEntry.value, 0xC22B)) return;
    pushAddress(0xC22E);
    SUB_01C966();
    if (handleReturnAddress(poppedEntry.value, 0xC22E)) return;
    jump(0xC371);
    return;
}

void game::SUB_01C232() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_01C255;
    }
    opINC(0x0019, 1);
    pushAddress(0xC23A);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC23A)) return;
    pushAddress(0xC23D);
    SUB_01C5B0();
    if (handleReturnAddress(poppedEntry.value, 0xC23D)) return;
    pushAddress(0xC240);
    SUB_01CFA1();
    if (handleReturnAddress(poppedEntry.value, 0xC240)) return;
    myMapper->writeCPU(0x03FC, myMapper->readCPU(0x002E));
    a = myMapper->readCPU(0x002F);
    myMapper->writeCPU(0x0418, a);
    pushAddress(0xC24D);
    SUB_01CB39();
    if (handleReturnAddress(poppedEntry.value, 0xC24D)) return;
    pushAddress(0xC250);
    SUB_01D10E();
    if (handleReturnAddress(poppedEntry.value, 0xC250)) return;
    pushAddress(0xC253);
    jump(0xA169);
    if (handleReturnAddress(poppedEntry.value, 0xC253)) return;
    do {
        popAddress();
        return;
    L_01C255:
        opDEX(1);
        if (!flgZ) {
            jump(0xC299);
            return;
        }
        pushAddress(0xC25A);
        SUB_01C132();
        if (handleReturnAddress(poppedEntry.value, 0xC25A)) return;
        y = 0x04;
        pushAddress(0xC25F);
        SUB_01C1D6();
        if (handleReturnAddress(poppedEntry.value, 0xC25F)) return;
        pushAddress(0xC262);
        SUB_01C216();
        if (handleReturnAddress(poppedEntry.value, 0xC262)) return;
        pushAddress(0xC265);
        SUB_01C1D4();
        if (handleReturnAddress(poppedEntry.value, 0xC265)) return;
        pushAddress(0xC268);
        SUB_01C102();
        if (handleReturnAddress(poppedEntry.value, 0xC268)) return;
        a = myMapper->readCPU(0x001D);
    } while (a != 0x0F);
    opINC(0x0019, 1);
    pushAddress(0xC273);
    SUB_01C28E();
    if (handleReturnAddress(poppedEntry.value, 0xC273)) return;
    pushAddress(0xC276);
    SUB_01CFA1();
    if (handleReturnAddress(poppedEntry.value, 0xC276)) return;
    pushAddress(0xC279);
    SUB_01C8C3();
    if (handleReturnAddress(poppedEntry.value, 0xC279)) return;
    pushAddress(0xC27C);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC27C)) return;
    myMapper->writeCPU(0x0019, 0x03);
    popAddress();
}

void game::SUB_01C282() {
    a = 0x00;
    myMapper->writeCPU(0x0140, a);
    myMapper->writeCPU(0x0019, a);
    myMapper->writeCPU(0x0018, 0x0B);
    popAddress();
}

void game::SUB_01C28E() {
    myMapper->writeCPU(0x002E, myMapper->readCPU(0x03FC));
    a = myMapper->readCPU(0x0418);
    myMapper->writeCPU(0x002F, a);
    popAddress();
}

void game::SUB_01C299() {
    opDEX(1);
    if (flgZ) {
        pushAddress(0xC29E);
        jump(0xA17D);
        if (handleReturnAddress(poppedEntry.value, 0xC29E)) return;
        a = myMapper->readCPU(0x0019);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x0019, a);
        if (myMapper->readCPU(0x00F4) == 0) {
            popAddress();
            return;
        }
        myMapper->writeCPU(0x0018, 0x02);
        myMapper->writeCPU(0x0019, 0x01);
        popAddress();
        return;
    }
    opDEX(1);
    if (flgZ) {
        myMapper->writeCPU(0x0019, 0x02);
        a = myMapper->readCPU(0x004A);
        setLoadFlag(a);
        if (flgZ) {
            pushAddress(0xC2C1);
            SUB_01C14B();
            if (handleReturnAddress(poppedEntry.value, 0xC2C1)) return;
            if (myMapper->readCPU(0x00F4) != 0) {
                goto L_01C2CE;
            }
            x = myMapper->readCPU(0x0028);
            a = myMapper->readCPU(0xFB4F + x);
            pushAddress(0xC2CD);
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0xC2CD)) return;
        }
    L_01C2CE:
        a = 0x01;
        myMapper->writeCPU(0x001A, a);
        pushAddress(0xC2D4);
        SUB_01C59C();
        if (handleReturnAddress(poppedEntry.value, 0xC2D4)) return;
        if (myMapper->readCPU(0x0140) != 0) {
            jump(0xC282);
            return;
        }
        popAddress();
        return;
    }
    jump(0xCED0);
    return;
}

void game::SUB_01C2DE() {
    pushAddress(0xC2E0);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC2E0)) return;
    a = 0x00;
    myMapper->writeCPU(0x004A, a);
    myMapper->writeCPU(0x00E2, a);
    myMapper->writeCPU(0x0144, a);
    myMapper->writeCPU(0x0146, a);
    pushAddress(0xC2EF);
    SUB_01CAA1();
    if (handleReturnAddress(poppedEntry.value, 0xC2EF)) return;
    pushAddress(0xC2F2);
    SUB_01C5B0();
    if (handleReturnAddress(poppedEntry.value, 0xC2F2)) return;
    opDEC(0x002A, 1);
    if (!flgZ) {
        goto L_01C315;
    }
    pushAddress(0xC2F9);
    SUB_01C14B();
    if (handleReturnAddress(poppedEntry.value, 0xC2F9)) return;
    a = 0x51;
    pushAddress(0xC2FE);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xC2FE)) return;
    myMapper->writeCPU(0x0018, 0x07);
    a = 0x00;
    myMapper->writeCPU(0x002E, a);
    pushAddress(0xC309);
    SUB_01F912();
    if (handleReturnAddress(poppedEntry.value, 0xC309)) return;
    myMapper->writeCPU(0x002F, a);
    pushAddress(0xC30E);
    SUB_01CB81();
    if (handleReturnAddress(poppedEntry.value, 0xC30E)) return;
    pushAddress(0xC311);
    jump(0xA17D);
    if (handleReturnAddress(poppedEntry.value, 0xC311)) return;
    jump(0xA169);
    return;
L_01C315:
    a = 0x00;
    myMapper->writeCPU(0x015B, a);
    myMapper->writeCPU(0x0064, a);
    pushAddress(0xC31E);
    SUB_01C9EA();
    if (handleReturnAddress(poppedEntry.value, 0xC31E)) return;
    myMapper->writeCPU(0x0019, 0x00);
    a = 0x05;
    myMapper->writeCPU(0x0018, a);
    myMapper->writeCPU(0x001F, a);
    jump(0xC98A);
    return;
}

void game::SUB_01C32C() {
    pushAddress(0xC32E);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC32E)) return;
    myMapper->writeCPU(0x020C, 0xF4);
    myMapper->writeCPU(0x020D, 0xFE);
    a = 0x0C;
    pushAddress(0xC33D);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xC33D)) return;
    a = 0x06;
    pushAddress(0xC342);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xC342)) return;
    a = 0x05;
    pushAddress(0xC347);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xC347)) return;
    a = 0x2C;
    pushAddress(0xC34C);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xC34C)) return;
    a = 0x00;
    myMapper->writeCPU(0x00FD, a);
    myMapper->writeCPU(0x0019, a);
    myMapper->writeCPU(0x07F1, a);
    myMapper->writeCPU(0x0018, 0x0D);
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    myMapper->writeCPU(0x00FF, a);
    popAddress();
}

void game::SUB_01C363() {
    myMapper->writeCPU(0x0025, a);
    SUB_01C365();
    return;
}

void game::SUB_01C365() {
    opINC(0x0019, 1);
    popAddress();
}

void game::SUB_01C368() {
    myMapper->writeCPU(0x0018, a);
    jump(0xC373);
    return;
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
    SUB_01C382();
    return;
}

void game::SUB_01C382() {
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x12);
    if (flgZ) {
        myMapper->writeCPU(0x0029, a);
        myMapper->writeCPU(0x0018, 0x0C);
        myMapper->writeCPU(0x0019, 0x08);
        popAddress();
        return;
    }
    pushAddress(0xC395);
    SUB_01FA6A();
    if (handleReturnAddress(poppedEntry.value, 0xC395)) return;
    a = 0x00;
    pushAddress(0xC39A);
    jump(0x9BBA);
    if (handleReturnAddress(poppedEntry.value, 0xC39A)) return;
    pushAddress(0xC39D);
    SUB_01E8F0();
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
        SUB_01C1D6();
        if (handleReturnAddress(poppedEntry.value, 0xC3B6)) return;
        pushAddress(0xC3B9);
        SUB_01F5EA();
        if (handleReturnAddress(poppedEntry.value, 0xC3B9)) return;
        pushAddress(0xC3BC);
        SUB_01C1D4();
        if (handleReturnAddress(poppedEntry.value, 0xC3BC)) return;
        a = myMapper->readCPU(0x003C);
        opEOR(0x03);
        myMapper->writeCPU(0x003C, a);
        jump(0x98B7);
        return;
    L_01C3C6:
        pushAddress(0xC3C8);
        SUB_01C474();
        if (handleReturnAddress(poppedEntry.value, 0xC3C8)) return;
        pushAddress(0xC3CB);
        SUB_01C4A4();
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
                SUB_01C1A7();
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
            jump(0x98B7);
            return;
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
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0xC432)) return;
            a = 0x00;
            myMapper->writeCPU(0x031F, a);
            pushAddress(0xC43A);
            SUB_01C4A8();
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
    SUB_01C994();
    if (handleReturnAddress(poppedEntry.value, 0xC461)) return;
    pushAddress(0xC464);
    SUB_01CFBD();
    if (handleReturnAddress(poppedEntry.value, 0xC464)) return;
    pushAddress(0xC467);
    SUB_01D162();
    if (handleReturnAddress(poppedEntry.value, 0xC467)) return;
    pushAddress(0xC46A);
    SUB_01C8C3();
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

void game::SUB_01C4E7() {
    pushAddress(0xC4E9);
    SUB_01C5B0();
    if (handleReturnAddress(poppedEntry.value, 0xC4E9)) return;
    pushAddress(0xC4EC);
    SUB_01E8F0();
    if (handleReturnAddress(poppedEntry.value, 0xC4EC)) return;
    myMapper->writeCPU(0x003D, 0x50);
    a = 0x00;
    myMapper->writeCPU(0x003E, a);
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (!flgZ) {
        jump(0xC55D);
        return;
    }
    x = 0xB8;
    a = myMapper->readCPU(0x0028);
    setLoadFlag(a);
    if (!flgZ) {
        x = 0x36;
    }
    opCMP(x, myMapper->readCPU(0x038C));
    if (!flgZ) {
        x = 0x01;
        if (!flgC) {
            opINX(1);
        }
        myMapper->writeCPU(0x0584, x);
        myMapper->writeCPU(0x003C, x);
        a = x;
        opLSR_A(1);
        myMapper->writeCPU(0x0450, a);
        jump(0xC575);
        return;
    }
    opINC(0x0019, 1);
    pushAddress(0xC51C);
    SUB_01C59C();
    if (handleReturnAddress(poppedEntry.value, 0xC51C)) return;
    a = 0x19;
    pushAddress(0xC521);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xC521)) return;
    if (myMapper->readCPU(0x0028) != 0) {
        goto L_01C52A;
    }
    x = 0x00;
    setLoadFlag(x);
    if (flgZ) {
        jump(0xC52C);
        return;
    }
L_01C52A:
    x = 0x04;
    SUB_01C52C();
    return;
}

void game::SUB_01C52C() {
    a = myMapper->readCPU(0xC551 + x);
    myMapper->writeCPU(0x0204, a);
    myMapper->writeCPU(0x0208, a);
    a = myMapper->readCPU(0xC552 + x);
    myMapper->writeCPU(0x020C, a);
    myMapper->writeCPU(0x0210, a);
    a = myMapper->readCPU(0xC553 + x);
    myMapper->writeCPU(0x0207, a);
    myMapper->writeCPU(0x020F, a);
    a = myMapper->readCPU(0xC554 + x);
    myMapper->writeCPU(0x020B, a);
    myMapper->writeCPU(0x0213, a);
    popAddress();
}

void game::SUB_01C55D() {
    opDEX(1);
    if (!flgZ) {
        jump(0xC582);
        return;
    }
    x = 0xC8;
    y = 0x01;
    a = myMapper->readCPU(0x0028);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01C56B;
    }
    x = 0x26;
    opINY(1);
L_01C56B:
    if (x == myMapper->readCPU(0x038C)) {
        jump(0xC57B);
        return;
    }
    myMapper->writeCPU(0x0584, y);
    myMapper->writeCPU(0x003C, y);
    SUB_01C575();
    return;
}

void game::SUB_01C575() {
    pushAddress(0xC577);
    jump(0x9458);
    if (handleReturnAddress(poppedEntry.value, 0xC577)) return;
    jump(0x98B7);
    return;
}

void game::SUB_01C57B() {
    opINC(0x0019, 1);
    myMapper->writeCPU(0x001D, 0x40);
    popAddress();
}

void game::SUB_01C582() {
    opDEC(0x001D, 1);
    if (!flgZ) {
        goto L_01C59B;
    }
    pushAddress(0xC588);
    SUB_01CAA1();
    if (handleReturnAddress(poppedEntry.value, 0xC588)) return;
    pushAddress(0xC58B);
    SUB_01C59C();
    if (handleReturnAddress(poppedEntry.value, 0xC58B)) return;
    opINC(0x0028, 1);
    pushAddress(0xC590);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC590)) return;
    myMapper->writeCPU(0x004A, a);
    a = 0x05;
    pushAddress(0xC597);
    SUB_01C368();
    if (handleReturnAddress(poppedEntry.value, 0xC597)) return;
    jump(0xC994);
    return;
L_01C59B:
    popAddress();
}

void game::SUB_01C59C() {
    y = 0x17;
    do {
        a = y;
        opAND(0x03);
        x = a;
        a = myMapper->readCPU(0xC5AC + x);
        myMapper->writeCPU(0x0204 + y, a);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01C5B0() {
    pushAddress(0xC5B2);
    SUB_01D120();
    if (handleReturnAddress(poppedEntry.value, 0xC5B2)) return;
    pushAddress(0xC5B5);
    SUB_01E915();
    if (handleReturnAddress(poppedEntry.value, 0xC5B5)) return;
    a = 0x00;
    myMapper->writeCPU(0x0072, a);
    y = 0x04;
    do {
        myMapper->writeCPU(0x0333 + y, a);
        opDEY(1);
    } while (!flgN);
    x = a;
    do {
        myMapper->writeCPU(0x0190 + x, a);
        opINX(1);
        opCMP(x, 0x18);
    } while (!flgC);
    myMapper->writeCPU(0x0560, a);
    popAddress();
}

void game::SUB_01C5CF() {
    x = 0x08;
    pushAddress(0xC5D3);
    SUB_01C52C();
    if (handleReturnAddress(poppedEntry.value, 0xC5D3)) return;
    a = 0xE0;
    myMapper->writeCPU(0x0214, a);
    myMapper->writeCPU(0x0218, a);
    a = myMapper->readCPU(0x038C);
    myMapper->writeCPU(0x020B, a);
    myMapper->writeCPU(0x0213, a);
    myMapper->writeCPU(0x021B, a);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0207, a);
    myMapper->writeCPU(0x020F, a);
    myMapper->writeCPU(0x0217, a);
    popAddress();
}

void game::SUB_01C8C3() {
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x06);
    if (!flgZ) {
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
    SUB_01C917();
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
        SUB_01C95D();
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
    SUB_01FD23();
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

void game::SUB_01C966() {
    pushAddress(0xC968);
    SUB_01CA38();
    if (handleReturnAddress(poppedEntry.value, 0xC968)) return;
    x = 0x04;
    a = 0x00;
    do {
        myMapper->writeCPU(0x07FC + x, a);
        opDEX(1);
    } while (!flgN);
    a = 0xBF;
    opAND(myMapper->readCPU(0x001C));
    myMapper->writeCPU(0x001C, a);
    myMapper->writeCPU(0x002A, 0x04);
    myMapper->writeCPU(0x002C, 0x03);
    a = 0x00;
    myMapper->writeCPU(0x00FD, a);
    myMapper->writeCPU(0x00FC, a);
    pushAddress(0xC989);
    SUB_01C9EA();
    if (handleReturnAddress(poppedEntry.value, 0xC989)) return;
    SUB_01C98A();
    return;
}

void game::SUB_01C98A() {
    a = 0x40;
    myMapper->writeCPU(0x0044, a);
    myMapper->writeCPU(0x0045, a);
    myMapper->writeCPU(0x0071, 0x05);
    SUB_01C994();
    return;
}

void game::SUB_01C994() {
    myMapper->writeCPU(0x005B, 0x00);
    SUB_01C998();
    return;
}

void game::SUB_01C998() {
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
    jump(0x98FE);
    return;
}

void game::SUB_01C9EA() {
    myMapper->writeCPU(0x0042, 0x00);
    x = myMapper->readCPU(0x0028);
    myMapper->writeCPU(0x0043, myMapper->readCPU(0xC9F6 + x));
    popAddress();
}

void game::SUB_01CA38() {
    pushAddress(0xCA3A);
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xCA3A)) return;
    pushAddress(0xCA3D);
    SUB_01C16D();
    if (handleReturnAddress(poppedEntry.value, 0xCA3D)) return;
    jump(0xC102);
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

void game::SUB_01CA95() {
    opEOR(0xFF);
    flgC = true;
    opADC(myMapper->readCPU((0x0000 + x) & 0x00ff));
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (flgC) {
        goto L_01CAA0;
    }
    opDEC((0x0001 + x) & 0x00ff, 1);
L_01CAA0:
    popAddress();
}

void game::SUB_01CAA1() {
    a = 0x00;
    x = 0x03;
    y = 0x05;
    jump(0xC176);
    return;
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
        SUB_01CAE7();
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
        SUB_01CAE3();
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
        SUB_01CC3D();
        if (handleReturnAddress(poppedEntry.value, 0xCB32)) return;
        a = 0x25;
        pushAddress(0xCB37);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0xCB37)) return;
    }
    popAddress();
}

void game::SUB_01CB39() {
    a = myMapper->readCPU(0x002E);
    flgC = true;
    opSBC(0x80);
    myMapper->writeCPU(0x002E, a);
    if (flgC) {
        goto L_01CB44;
    }
    opDEC(0x002F, 1);
L_01CB44:
    x = myMapper->readCPU(0x002E);
    y = myMapper->readCPU(0x002F);
    a = 0x02;
    myMapper->writeCPU(0x0015, a);
    pushAddress(0xCB4E);
    SUB_01F841();
    if (handleReturnAddress(poppedEntry.value, 0xCB4E)) return;
    a = 0x00;
    myMapper->writeCPU(0x001D, a);
    myMapper->writeCPU(0x0035, a);
    popAddress();
}

void game::SUB_01CB56() {
    opINC(0x0031, 1);
    a = myMapper->readCPU(0x0031);
    opAND(0x07);
    myMapper->writeCPU(0x0031, a);
    if (!flgZ) {
        goto L_01CB77;
    }
    opINC(0x0036, 1);
    a = 0x20;
    x = 0x2E;
    pushAddress(0xCB68);
    SUB_01CA8B();
    if (handleReturnAddress(poppedEntry.value, 0xCB68)) return;
    x = myMapper->readCPU(0x002E);
    y = myMapper->readCPU(0x002F);
    a = 0x02;
    myMapper->writeCPU(0x0015, a);
    pushAddress(0xCB73);
    SUB_01F841();
    if (handleReturnAddress(poppedEntry.value, 0xCB73)) return;
    opINC(0x001D, 1);
    popAddress();
    return;
L_01CB77:
    a = 0x01;
    myMapper->writeCPU(0x004B, a);
    pushAddress(0xCB7D);
    SUB_01CFF9();
    if (handleReturnAddress(poppedEntry.value, 0xCB7D)) return;
    jump(0xF69E);
    return;
}

void game::SUB_01CB81() {
    x = 0x00;
    SUB_01CB83();
    return;
}

void game::SUB_01CB83() {
    y = 0x2C;
    do {
        myMapper->writeCPU(0x0214 + y, 0xF8);
        opDEY(4);
    } while (!flgN);
    myMapper->writeCPU(0x0003, myMapper->readCPU(0xCBF1 + x));
    a = myMapper->readCPU(0xCBF2 + x);
    myMapper->writeCPU(0x0004, a);
    pushAddress(0xCB9C);
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xCB9C)) return;
    myMapper->writeCPU(0x0020, a);
    myMapper->writeCPU(0x00FC, a);
    myMapper->writeCPU(0x00FD, a);
    x = 0x20;
    y = 0x00;
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, x);
    myMapper->writeCPU(0x2006, y);
    a = 0x00;
    myMapper->writeCPU(0x0000, a);
    while (true) {
        y = myMapper->readCPU(0x0000);
        opCMP(y, 0x08);
        if (flgZ) {
            goto L_01CBCC;
        }
        myMapper->writeCPU(0x0001, myMapper->readCPU(myMapper->readCPU(0x0003) + (myMapper->readCPU((0x0003 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0003) + (myMapper->readCPU((0x0003 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0002, a);
        opINY(1);
        myMapper->writeCPU(0x0000, y);
        pushAddress(0xCBC8);
        SUB_01CBCF();
        if (handleReturnAddress(poppedEntry.value, 0xCBC8)) return;
    }
L_01CBCC:
    jump(0xC102);
    return;
}

void game::SUB_01CBCF() {
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0001) + (myMapper->readCPU((0x0001 + 1) & 0x00ff) << 8) + y);
        if (a == 0xD4) {
            goto L_01CBE2;
        }
        if (a == 0xD9) {
            goto L_01CBE1;
        }
        myMapper->writeCPU(0x2007, a);
    L_01CBDE:
        opINY(1);
    } while (!flgZ);
L_01CBE1:
    popAddress();
    return;
L_01CBE2:
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0001) + (myMapper->readCPU((0x0001 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    x = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0001) + (myMapper->readCPU((0x0001 + 1) & 0x00ff) << 8) + y);
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    if (flgZ) {
        goto L_01CBDE;
    }
    //NOP
    SUB_01CC3D();
    return;
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
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xCC56)) return;
    a = myMapper->readCPU(0x0008);
    pushAddress(0xCC5B);
    SUB_01CC68();
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
    SUB_01CC75();
    if (handleReturnAddress(poppedEntry.value, 0xCC70)) return;
    a = myMapper->readCPU(0x0000);
    opAND(0x0F);
    SUB_01CC75();
    return;
}

void game::SUB_01CC75() {
    opORA(0xD0);
    jump(0xA357);
    return;
}

void game::SUB_01CC7A() {
    a = 0x19;
    pushAddress(0xCC7E);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xCC7E)) return;
    y = 0x02;
    do {
        a = myMapper->readCPU(0x07FC + y);
        pushAddress(0xCC86);
        SUB_01CC68();
        if (handleReturnAddress(poppedEntry.value, 0xCC86)) return;
        opDEY(1);
    } while (!flgN);
    if (flgN) {
        jump(0xCC5F);
        return;
    }
    myMapper->writeCPU(0x0004, x);
    pushAddress(0xCC90);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xCC90)) return;
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xCCA0);
        return;
    }
    SUB_01CC95();
    return;
}

void game::SUB_01CC95() {
    opPHA();
    myMapper->writeCPU(0x0003, 0x02);
    a = 0x01;
    pushAddress(0xCC9E);
    SUB_01CCF0();
    if (handleReturnAddress(poppedEntry.value, 0xCC9E)) return;
    opPLA();
    SUB_01CCA0();
    return;
}

void game::SUB_01CCA0() {
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
        SUB_01CCF2();
        if (handleReturnAddress(poppedEntry.value, 0xCCDE)) return;
        myMapper->writeCPU(0x0003, 0x02);
        a = 0x01;
        pushAddress(0xCCE7);
        SUB_01CCF2();
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

void game::SUB_01CED0() {
    a = myMapper->readCPU(0x00F7);
    opAND(0x03);
    opCMP(a, 0x03);
    if (flgZ) {
        a = myMapper->readCPU(0x00F7);
        opAND(0xFC);
        opORA(0x01);
        myMapper->writeCPU(0x00F7, a);
    }
    a = myMapper->readCPU(0x007E);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xFAEF);
        return;
    }
    pushAddress(0xCEE9);
    jump(0xA2E8);
    if (handleReturnAddress(poppedEntry.value, 0xCEE9)) return;
    pushAddress(0xCEEC);
    SUB_01CF53();
    if (handleReturnAddress(poppedEntry.value, 0xCEEC)) return;
    pushAddress(0xCEEF);
    jump(0xA825);
    if (handleReturnAddress(poppedEntry.value, 0xCEEF)) return;
    pushAddress(0xCEF2);
    SUB_01FA6A();
    if (handleReturnAddress(poppedEntry.value, 0xCEF2)) return;
    pushAddress(0xCEF5);
    SUB_01CF28();
    if (handleReturnAddress(poppedEntry.value, 0xCEF5)) return;
    a = myMapper->readCPU(0x0022);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xCF50);
        return;
    }
    pushAddress(0xCEFC);
    jump(0x934C);
    if (handleReturnAddress(poppedEntry.value, 0xCEFC)) return;
    y = 0x04;
    pushAddress(0xCF01);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xCF01)) return;
    pushAddress(0xCF04);
    SUB_01F5EA();
    if (handleReturnAddress(poppedEntry.value, 0xCF04)) return;
    pushAddress(0xCF07);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xCF07)) return;
    pushAddress(0xCF0A);
    jump(0xAAE2);
    if (handleReturnAddress(poppedEntry.value, 0xCF0A)) return;
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x06);
    if (!flgZ) {
        goto L_01CF14;
    }
    pushAddress(0xCF13);
    jump(0x81CA);
    if (handleReturnAddress(poppedEntry.value, 0xCF13)) return;
L_01CF14:
    y = 0x05;
    pushAddress(0xCF18);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xCF18)) return;
    pushAddress(0xCF1B);
    SUB_01E8F0();
    if (handleReturnAddress(poppedEntry.value, 0xCF1B)) return;
    pushAddress(0xCF1E);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xCF1E)) return;
    pushAddress(0xCF21);
    SUB_01F376();
    if (handleReturnAddress(poppedEntry.value, 0xCF21)) return;
    pushAddress(0xCF24);
    jump(0xA4AA);
    if (handleReturnAddress(poppedEntry.value, 0xCF24)) return;
    jump(0xA63A);
    return;
}

void game::SUB_01CF28() {
    a = myMapper->readCPU(0x0023);
    opORA(myMapper->readCPU(0x001F));
    opORA(myMapper->readCPU(0x00F4));
    if (!flgZ) {
        jump(0xCF50);
        return;
    }
    a = myMapper->readCPU(0x00F5);
    y = myMapper->readCPU(0x0022);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_01CF46;
    }
    opAND(0x10);
    if (flgZ) {
        jump(0xCF50);
        return;
    }
    a = 0x01;
    myMapper->writeCPU(0x0022, a);
    pushAddress(0xCF40);
    jump(0x9359);
    if (handleReturnAddress(poppedEntry.value, 0xCF40)) return;
    a = 0x54;
    jump(0xC1A7);
    return;
L_01CF46:
    a = myMapper->readCPU(0x00F5);
    opAND(0x10);
    if (flgZ) {
        jump(0xCF50);
        return;
    }
    myMapper->writeCPU(0x0022, 0x00);
    SUB_01CF50();
    return;
}

void game::SUB_01CF50() {
    popAddress();
}

void game::SUB_01CF52() {
    popAddress();
}

void game::SUB_01CF53() {
    x = 0x00;
    a = myMapper->readCPU(0x0028);
    setLoadFlag(a);
    if (!flgZ) {
        opCMP(a, 0x10);
        if (!flgZ) {
            goto L_01CF9A;
        }
        x = 0x03;
    }
    a = myMapper->readCPU(0x046C);
    setLoadFlag(a);
    if (flgZ) {
        myMapper->writeCPU(0x0000, myMapper->readCPU(0xCF9B + x));
        myMapper->writeCPU(0x0001, myMapper->readCPU(0xCF9C + x));
        myMapper->writeCPU(0x0002, myMapper->readCPU(0xCF9D + x));
        a = 0x02;
        myMapper->writeCPU(0x0010, a);
        myMapper->writeCPU(0x0011, a);
        myMapper->writeCPU(0x0013, a);
        myMapper->writeCPU(0x0012, 0x10);
        y = myMapper->readCPU(0x003F);
        x = myMapper->readCPU(0x0040);
        a = myMapper->readCPU(0x0041);
        myMapper->writeCPU(0x0003, a);
        pushAddress(0xCF89);
        jump(0xA048);
        if (handleReturnAddress(poppedEntry.value, 0xCF89)) return;
        if (flgC) {
            goto L_01CF9A;
        }
        myMapper->writeCPU(0x0018, 0x0A);
        a = 0x00;
        myMapper->writeCPU(0x0019, a);
        myMapper->writeCPU(0x0144, a);
        myMapper->writeCPU(0x0146, a);
    }
L_01CF9A:
    popAddress();
}

void game::SUB_01CFA1() {
    pushAddress(0xCFA3);
    SUB_01CF52();
    if (handleReturnAddress(poppedEntry.value, 0xCFA3)) return;
    myMapper->writeCPU(0x01A8, 0x00);
    a = 0x40;
    myMapper->writeCPU(0x01A9, a);
    pushAddress(0xCFB0);
    SUB_01D162();
    if (handleReturnAddress(poppedEntry.value, 0xCFB0)) return;
    pushAddress(0xCFB3);
    SUB_01D052();
    if (handleReturnAddress(poppedEntry.value, 0xCFB3)) return;
    pushAddress(0xCFB6);
    SUB_01F60F();
    if (handleReturnAddress(poppedEntry.value, 0xCFB6)) return;
    pushAddress(0xCFB9);
    SUB_01C59C();
    if (handleReturnAddress(poppedEntry.value, 0xCFB9)) return;
    myMapper->writeCPU(0x2000, a);
    SUB_01CFBD();
    return;
}

void game::SUB_01CFBD() {
    pushAddress(0xCFBF);
    SUB_01CFF9();
    if (handleReturnAddress(poppedEntry.value, 0xCFBF)) return;
    pushAddress(0xCFC2);
    SUB_01F912();
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
    SUB_01F817();
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

void game::SUB_01D015() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFBB0 + x);
    SUB_01D01A();
    return;
}

void game::SUB_01D01A() {
    y = myMapper->readCPU(0x0046);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_01D022;
    }
    opLSR_A(4);
L_01D022:
    opAND(0x0F);
    popAddress();
}

void game::SUB_01D025() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFBC3 + x);
    pushAddress(0xD02C);
    SUB_01D01A();
    if (handleReturnAddress(poppedEntry.value, 0xD02C)) return;
    if (a == 0x0F) {
        a = 0xFF;
    }
    myMapper->writeCPU(0x004B, a);
    if (myMapper->readCPU(0x0028) == 0x0E) {
        if (myMapper->readCPU(0x0046) == 0) {
            goto L_01D04F;
        }
        if (myMapper->readCPU(0x003F) >= 0x60) {
            if (myMapper->readCPU(0x002F) != 0x04) {
                goto L_01D04F;
            }
            myMapper->writeCPU(0x004B, 0x03);
        }
    }
L_01D04F:
    a = myMapper->readCPU(0x004B);
    popAddress();
}

void game::SUB_01D052() {
    a = 0x00;
    x = 0x17;
    do {
        myMapper->writeCPU(0x04A4 + x, a);
        myMapper->writeCPU(0x0434 + x, a);
        opINX(1);
    } while (x < 0x1C);
    a = myMapper->readCPU(0x0028);
    x = 0x18;
    y = 0x00;
    if (a != 0x04) {
        x = 0x19;
        y = 0x02;
        if (a != 0x05) {
            goto L_01D077;
        }
        if (myMapper->readCPU(0x0046) != 0) {
            goto L_01D081;
        }
    L_01D077:
        a = myMapper->readCPU(0x0028);
        x = 0x1B;
        y = 0x04;
        opCMP(a, 0x0A);
        if (!flgZ) {
            goto L_01D099;
        }
    }
L_01D081:
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0xD0D0 + y));
    a = myMapper->readCPU(0xD0D1 + y);
    myMapper->writeCPU(0x0001, a);
    y = 0x00;
    x = 0x17;
    do {
        pushAddress(0xD093);
        SUB_01D09A();
        if (handleReturnAddress(poppedEntry.value, 0xD093)) return;
        opINX(1);
        opCMP(x, myMapper->readCPU(0x004E));
    } while (!flgZ);
L_01D099:
    popAddress();
}

void game::SUB_01D09A() {
    myMapper->writeCPU(0x0434 + x, 0x01);
    myMapper->writeCPU(0x0418 + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x03FC + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x04F8 + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0514 + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0568 + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0584 + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x04A4 + x, myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0000) + (myMapper->readCPU((0x0000 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0488 + x, a);
    opINY(1);
    popAddress();
}

void game::SUB_01D10E() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFB9B + x);
    pushAddress(0xD115);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xD115)) return;
    a = 0x05;
    jump(0xCC95);
    return;
}

void game::SUB_01D11B() {
    a = 0x06;
    jump(0xCC95);
    return;
}

void game::SUB_01D120() {
    x = 0x00;
    do {
        myMapper->writeCPU(0x0166 + x, 0x00);
        a = 0x01;
        myMapper->writeCPU(0x0160 + x, a);
        opINX(1);
    } while (x < 0x06);
    popAddress();
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
    SUB_01D132();
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
        SUB_01D1BE();
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
    SUB_01D132();
    if (handleReturnAddress(poppedEntry.value, 0xD198)) return;
    a = myMapper->readCPU(0x006D);
    opCMP(a, myMapper->readCPU(0x0076));
    if (flgZ) {
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
            SUB_01EF04();
            if (handleReturnAddress(poppedEntry.value, 0xD261)) return;
            a = 0x28;
            pushAddress(0xD266);
            SUB_01F42C();
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

void game::SUB_01DA44() {
    y = myMapper->readCPU(0x0064);
    x = 0x14;
    do {
        a = myMapper->readCPU(0x0434 + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01DA53;
        }
        opINX(1);
        opDEY(1);
    } while (!flgN);
    do {
        flgC = true;
        popAddress();
        return;
    L_01DA53:
        y = myMapper->readCPU(0x0071);
        setLoadFlag(y);
    } while (flgZ);
    opDEY(1);
    myMapper->writeCPU(0x0071, y);
    pushAddress(0xDA5C);
    jump(0xA1D0);
    if (handleReturnAddress(poppedEntry.value, 0xDA5C)) return;
    flgC = false;
    popAddress();
}

void game::SUB_01DA5F() {
    pushAddress(0xDA61);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xDA61)) return;
    //NOP
    SUB_01DC50();
    return;
}

void game::SUB_01DC50() {
    y = 0x00;
    a = 0x02;
    pushAddress(0xDC56);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0xDC56)) return;
    a = 0x04;
    jump(0xF131);
    return;
}

void game::SUB_01DD14() {
    a = myMapper->readCPU(0x003C);
    opAND(0x03);
    if (!flgZ) {
        a = myMapper->readCPU(0x003C);
        opAND(0x04);
        if (flgZ) {
            y = 0x00;
            a = myMapper->readCPU(0x0049);
            setLoadFlag(a);
            if (!flgN) {
                goto L_01DD27;
            }
            opDEY(1);
        L_01DD27:
            myMapper->writeCPU(0x004F, y);
            flgC = false;
            opADC(myMapper->readCPU(0x038C + x));
            myMapper->writeCPU(0x038C + x, a);
            a = myMapper->readCPU(0x0300 + x);
            opAND(0x01);
            opADC(myMapper->readCPU(0x004F));
            opAND(0x01);
            myMapper->writeCPU(0x0300 + x, a);
        }
    }
    popAddress();
}

void game::SUB_01DD3D() {
    pushAddress(0xDD3F);
    SUB_01DD14();
    if (handleReturnAddress(poppedEntry.value, 0xDD3F)) return;
    if (myMapper->readCPU(0x0300 + x) == 0) {
        a = myMapper->readCPU(0x038C + x);
        if (a >= 0x08) {
            if (a < 0xF9) {
                goto L_01DD5A;
            }
        }
        a = myMapper->readCPU(0x0300 + x);
        opORA(0x80);
        myMapper->writeCPU(0x0300 + x, a);
        if (!flgZ) {
            goto L_01DD5A;
        }
    }
L_01DD5A:
    popAddress();
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
    SUB_01E3F4();
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
    SUB_01FD18();
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
    SUB_01E3F4();
    if (handleReturnAddress(poppedEntry.value, 0xE09C)) return;
    pushAddress(0xE09F);
    SUB_01DF06();
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
        SUB_01E0F4();
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
    SUB_01EF04();
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
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xE4D0)) return;
    y = 0x05;
    pushAddress(0xE4D5);
    SUB_01C1D6();
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
                    SUB_01E4CC();
                    if (handleReturnAddress(poppedEntry.value, 0xE56F)) return;
                }
                pushAddress(0xE572);
                SUB_01DF79();
                if (handleReturnAddress(poppedEntry.value, 0xE572)) return;
            }
        L_01E573:
            a = myMapper->readCPU(0x0434 + x);
            pushAddress(0xE578);
            SUB_01CA6D();
            if (handleReturnAddress(poppedEntry.value, 0xE578)) return;
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
    a = a; //NOP
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
        SUB_01EF84();
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
                        SUB_01EAA9();
                        if (handleReturnAddress(poppedEntry.value, 0xE72D)) return;
                        goto L_01E734;
                    }
                }
            L_01E731:
                pushAddress(0xE733);
                SUB_01E09A();
                if (handleReturnAddress(poppedEntry.value, 0xE733)) return;
            L_01E734:
                pushAddress(0xE736);
                SUB_01FE96();
                if (handleReturnAddress(poppedEntry.value, 0xE736)) return;
                x = myMapper->readCPU(0x004E);
                pushAddress(0xE73B);
                SUB_01FC97();
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
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xE76D)) return;
    y = 0x05;
    pushAddress(0xE772);
    SUB_01C1D6();
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
        SUB_01FCD0();
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
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0xE7C8)) return;
            y = 0x05;
            pushAddress(0xE7CD);
            SUB_01C1D6();
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
                            SUB_01C1A7();
                            if (handleReturnAddress(poppedEntry.value, 0xE7DE)) return;
                            y = 0x05;
                            pushAddress(0xE7E3);
                            SUB_01C1D6();
                            if (handleReturnAddress(poppedEntry.value, 0xE7E3)) return;
                            a = 0xB4;
                            myMapper->writeCPU(0x005B, a);
                        }
                    L_01E7EB:
                        a = 0x24;
                        pushAddress(0xE7EF);
                        SUB_01C1A7();
                        if (handleReturnAddress(poppedEntry.value, 0xE7EF)) return;
                        y = 0x05;
                        pushAddress(0xE7F4);
                        SUB_01C1D6();
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
                    SUB_01C1A7();
                    if (handleReturnAddress(poppedEntry.value, 0xE831)) return;
                    y = 0x05;
                    pushAddress(0xE836);
                    SUB_01C1D6();
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
                SUB_01C1A7();
                if (handleReturnAddress(poppedEntry.value, 0xE849)) return;
                y = 0x05;
                pushAddress(0xE84E);
                SUB_01C1D6();
                if (handleReturnAddress(poppedEntry.value, 0xE84E)) return;
                myMapper->writeCPU(0x0045, 0x40);
                myMapper->writeCPU(0x0018, 0x0C);
                a = 0x00;
                myMapper->writeCPU(0x0019, a);
            }
        }
        a = 0x16;
        pushAddress(0xE862);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0xE862)) return;
        y = 0x05;
        pushAddress(0xE867);
        SUB_01C1D6();
        if (handleReturnAddress(poppedEntry.value, 0xE867)) return;
        myMapper->writeCPU(0x0072, 0x00);
        a = myMapper->readCPU(0x0071);
        flgC = false;
        opADC(0x05);
    }
L_01E874:
    a = 0x18;
    pushAddress(0xE878);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xE878)) return;
    y = 0x05;
    pushAddress(0xE87D);
    SUB_01C1D6();
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
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xE892)) return;
    y = 0x05;
    pushAddress(0xE897);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xE897)) return;
    myMapper->writeCPU(0x007E, 0x18);
    a = 0x00;
    myMapper->writeCPU(0x0072, a);
    opINC(0x0070, 1);
    goto L_01E7CE;
L_01E8A5:
    a = 0x17;
    pushAddress(0xE8A9);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xE8A9)) return;
    y = 0x05;
    pushAddress(0xE8AE);
    SUB_01C1D6();
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
        SUB_01FB06();
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
    SUB_01EB08();
    if (handleReturnAddress(poppedEntry.value, 0xE90B)) return;
    //NOP
    //NOP
    //NOP
    pushAddress(0xE911);
    SUB_01E3FF();
    if (handleReturnAddress(poppedEntry.value, 0xE911)) return;
    jump(0xE922);
    return;
}

void game::SUB_01E915() {
    x = 0x04;
    a = 0x32;
    do {
        myMapper->writeCPU(0x0434 + x, a);
        opINX(1);
    } while (x < 0x17);
    popAddress();
}

void game::SUB_01E922() {
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
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xE95B)) return;
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
    pushAddress(0xEA32);
    SUB_01EACB();
    if (handleReturnAddress(poppedEntry.value, 0xEA32)) return;
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
    SUB_01E4D9();
    if (handleReturnAddress(poppedEntry.value, 0xEA79)) return;
    pushAddress(0xEA7C);
    SUB_01F1DB();
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
    SUB_01EAB2();
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
    SUB_01EAA9();
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
    SUB_01EACB();
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

void game::SUB_01EB6A() {
    myMapper->writeCPU(0x0434 + x, 0x2F);
    myMapper->writeCPU(0x0450 + x, 0x00);
    myMapper->writeCPU(0x046C + x, 0x80);
    myMapper->writeCPU(0x04F8 + x, 0x0C);
    a = myMapper->readCPU(0x0584 + x);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01EBBD;
    }
    opAND(0x0F);
    if (a == 0x01) {
        goto L_01EBAD;
    }
    if (a != 0x06) {
        if (a == 0x05) {
            goto L_01EBA6;
        }
        if (a == 0x07) {
            goto L_01EBA6;
        }
        if (a == 0x0C) {
            goto L_01EBEF;
        }
        y = myMapper->readCPU(0x0072);
        setLoadFlag(y);
        if (!flgZ) {
            goto L_01EBE5;
        }
        if (a == myMapper->readCPU(0x015B)) {
            goto L_01EBE5;
        }
        myMapper->writeCPU(0x0072, 0xFF);
    }
    while (true) {
    L_01EBA6:
        y = a;
        a = myMapper->readCPU(0xEC0A + y);
        jump(0xEF04);
        return;
    L_01EBAD:
        a = 0x0E;
        pushAddress(0xEBB1);
        SUB_01EF04();
        if (handleReturnAddress(poppedEntry.value, 0xEBB1)) return;
        a = myMapper->readCPU(0x0584 + x);
        opLSR_A(4);
        myMapper->writeCPU(0x0338 + x, a);
        popAddress();
        return;
    L_01EBBD:
        if (myMapper->readCPU(0x0079) >= 0x0A) {
            goto L_01EBEF;
        }
    L_01EBC3:
        a = myMapper->readCPU(0x0071);
        y = myMapper->readCPU(0x0072);
        setLoadFlag(y);
        if (flgZ) {
            y = myMapper->readCPU(0x0070);
            if (a < 0x08) {
                if (a < 0x04) {
                    goto L_01EBE5;
                }
                opCMP(y, 0x01);
                if (flgC) {
                    goto L_01EBE5;
                }
                if (!flgC) {
                    goto L_01EBDD;
                }
            }
            if (y >= 0x02) {
                goto L_01EBE5;
            }
        L_01EBDD:
            myMapper->writeCPU(0x0072, 0xFF);
            a = 0x03;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_01EBE9;
            }
        }
    L_01EBE5:
        a = myMapper->readCPU(0x006F);
        opAND(0x01);
    L_01EBE9:
        myMapper->writeCPU(0x0584 + x, a);
    }
L_01EBEF:
    myMapper->writeCPU(0x0079, 0x00);
    y = myMapper->readCPU(0x0064);
    if (y >= 0x02) {
        goto L_01EBC3;
    }
    myMapper->writeCPU(0x004B, y);
    a = 0x0C;
    myMapper->writeCPU(0x0584 + x, a);
    y = a;
    a = myMapper->readCPU(0xEC0A + y);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    jump(0xEF04);
    return;
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

void game::SUB_01F34D() {
    a = myMapper->readCPU(0x003C);
    opAND(0x03);
    if (!flgZ) {
        a = myMapper->readCPU(0x003C);
        opAND(0x04);
        if (flgZ) {
            x = 0x00;
            a = myMapper->readCPU(0x0049);
            setLoadFlag(a);
            if (!flgN) {
                goto L_01F360;
            }
            opDEX(1);
        L_01F360:
            myMapper->writeCPU(0x004F, x);
            flgC = false;
            opADC(myMapper->readCPU(0x0172 + y));
            myMapper->writeCPU(0x0172 + y, a);
            a = myMapper->readCPU(0x0160 + y);
            opAND(0x01);
            opADC(myMapper->readCPU(0x004F));
            opAND(0x01);
            myMapper->writeCPU(0x0160 + y, a);
        }
    }
    popAddress();
}

void game::SUB_01F376() {
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0166 + y);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_01F383;
        }
    L_01F37D:
        opINY(1);
    } while (y < 0x06);
    popAddress();
    return;
L_01F383:
    pushAddress(0xF385);
    SUB_01F34D();
    if (handleReturnAddress(poppedEntry.value, 0xF385)) return;
    if (myMapper->readCPU(0x0160 + y) == 0) {
        goto L_01F396;
    }
    do {
        do {
            a = myMapper->readCPU(0x016C + y);
            opAND(0x80);
            myMapper->writeCPU(0x016C + y, a);
            goto L_01F37D;
        L_01F396:
            a = myMapper->readCPU(0x0172 + y);
        } while (a < 0x08);
    } while (a >= 0xF9);
    a = myMapper->readCPU(0x016C + y);
    opAND(0x7F);
    if (flgZ) {
        a = myMapper->readCPU(0x016C + y);
        opORA(0x01);
        myMapper->writeCPU(0x016C + y, a);
        if (!flgZ) {
            goto L_01F3BC;
        }
    }
    a = myMapper->readCPU(0x016C + y);
    opAND(0x80);
    opORA(0x02);
    myMapper->writeCPU(0x016C + y, a);
L_01F3BC:
    a = myMapper->readCPU(0x0166 + y);
    opAND(0x40);
    if (!flgZ) {
        goto L_01F3C8;
    }
    a = myMapper->readCPU(0x0560);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01F37D;
    }
L_01F3C8:
    pushAddress(0xF3CA);
    SUB_01F4BE();
    if (handleReturnAddress(poppedEntry.value, 0xF3CA)) return;
    a = myMapper->readCPU(0xF41E);
    opPHA();
    a = myMapper->readCPU(0xF41D);
    opPHA();
    myMapper->writeCPU(0x000C, y);
    a = myMapper->readCPU(0x0166 + y);
    opAND(0x3F);
    pushAddress(0xF3DC);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xF3DC)) return;
    SUB_01F41F();
    return;
}

void game::SUB_01F41F() {
    do {
        if (myMapper->readCPU(0x0434 + x) == 0) {
            goto L_01F42B;
        }
        opINX(1);
    } while (x < myMapper->readCPU(0x004B));
    x = 0xFF;
L_01F42B:
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

void game::SUB_01F4BE() {
    if (myMapper->readCPU(0x0184 + y) == 0) {
        goto L_01F4D1;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_01F4D1;
    }
    x = myMapper->readCPU(0x0184 + y);
    opDEX(1);
    myMapper->writeCPU(0x0184 + y, x);
L_01F4D1:
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
        opCMP(a, 0x08);
        if (!flgZ) {
            opCMP(a, 0x0C);
            if (flgZ) {
                goto L_01F605;
            }
            pushAddress(0xF604);
            SUB_01D196();
            if (handleReturnAddress(poppedEntry.value, 0xF604)) return;
        }
    }
L_01F605:
    pushAddress(0xF607);
    SUB_01F60F();
    if (handleReturnAddress(poppedEntry.value, 0xF607)) return;
    pushAddress(0xF60A);
    SUB_01CFF9();
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
        SUB_01F817();
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
    SUB_01F69E();
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
    SUB_01F699();
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
    SUB_01CA8B();
    if (handleReturnAddress(poppedEntry.value, 0xF6BD)) return;
    pushAddress(0xF6C0);
    SUB_01F699();
    if (handleReturnAddress(poppedEntry.value, 0xF6C0)) return;
    y = a;
    opDEY(1);
    a = y;
    x = 0x0D;
    pushAddress(0xF6C8);
    SUB_01CA8B();
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
    SUB_01F7ED();
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
    SUB_01CC5F();
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
        SUB_01F94F();
        if (handleReturnAddress(poppedEntry.value, 0xF7B9)) return;
        y = myMapper->readCPU(0x004F);
        x = myMapper->readCPU(0x0020);
        myMapper->writeCPU(0x000E, 0x04);
        myMapper->writeCPU(0x0004, 0x00);
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0006) + (myMapper->readCPU((0x0006 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x0700 + x, a);
            pushAddress(0xF7CD);
            SUB_01F9D4();
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
        SUB_01CC5F();
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
    SUB_01F841();
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
    SUB_01C13F();
    if (handleReturnAddress(poppedEntry.value, 0xF8B8)) return;
    a = myMapper->readCPU(0x001F);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0xF87C);
        return;
    }
    pushAddress(0xF8BF);
    SUB_01F868();
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
    SUB_01F909();
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
    SUB_01F912();
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

void game::SUB_01F918() {
    myMapper->writeCPU(0x0015, myMapper->readCPU(0x0013));
    x = myMapper->readCPU(0x0028);
    if (myMapper->readCPU(0xFBD6 + x) == 0) {
        goto L_01F925;
    }
    opINC(0x0015, 1);
L_01F925:
    a = myMapper->readCPU(0x0012);
    opLSR_A(3);
    x = a;
    a = myMapper->readCPU(0x0015);
    opAND(0x01);
    opASL_A(2);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0009, a);
    a = myMapper->readCPU(0x0010);
    opAND(0xF8);
    myMapper->writeCPU(0x0014, a);
    a = 0x00;
    opASL_M(0x0014, 1);
    opROL_A(1);
    opASL_M(0x0014, 1);
    opROL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0009));
    myMapper->writeCPU(0x0009, a);
    a = x;
    opORA(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0008, a);
    popAddress();
}

void game::SUB_01F94F() {
    myMapper->writeCPU(0x0017, 0x00);
    a = myMapper->readCPU(0x0008);
    flgC = true;
    opSBC(0xC0);
    myMapper->writeCPU(0x0008, a);
    if (flgC) {
        goto L_01F95E;
    }
    opDEC(0x0009, 1);
L_01F95E:
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
    SUB_01F972();
    return;
}

void game::SUB_01F972() {
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
    SUB_01CA8B();
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
            jump(0xF99B);
            return;
        }
        opLSR_A(2);
    }
    SUB_01F99B();
    return;
}

void game::SUB_01F99B() {
    opAND(0x03);
    myMapper->writeCPU(0x0014, a);
    popAddress();
}

void game::SUB_01F9A0() {
    a = myMapper->readCPU(0x0010);
    opAND(0xF8);
    flgC = true;
    opSBC(0x30);
    myMapper->writeCPU(0x000F, a);
    if (a < 0xB0) {
        goto L_01F9B1;
    }
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        jump(0xF99B);
        return;
    }
L_01F9B1:
    a = myMapper->readCPU(0x0012);
    opLSR_A(3);
    x = a;
    opEOR(0x03);
    opAND(0x03);
    myMapper->writeCPU(0x0015, a);
    a = x;
    opLSR_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x0016, a);
    myMapper->writeCPU(0x0017, 0x00);
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xFBD6 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0013));
    jump(0xF972);
    return;
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

void game::SUB_01FA26() {
    if (myMapper->readCPU(0x0071) == 0) {
        goto L_01FA53;
    }
    x = myMapper->readCPU(0x015B);
    setLoadFlag(x);
    if (!flgZ) {
        if (myMapper->readCPU(0x015C) != 0) {
            goto L_01FA53;
        }
        a = x;
        flgC = true;
        opSBC(0x08);
        opPHA();
        y = a;
        a = myMapper->readCPU(0xFA62 + y);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_01FA46;
        }
        a = x;
        flgC = true;
        opSBC(0x08);
        pushAddress(0xFA45);
        SUB_01DA5F();
        if (handleReturnAddress(poppedEntry.value, 0xFA45)) return;
    L_01FA46:
        opPLA();
        if (a != 0x02) {
            goto L_01FA55;
        }
        myMapper->writeCPU(0x015C, a);
        myMapper->writeCPU(0x015D, 0x0F);
    }
    do {
        do {
        L_01FA53:
            flgC = false;
            popAddress();
            return;
        L_01FA55:
            y = a;
            a = myMapper->readCPU(0xFA62 + y);
            setLoadFlag(a);
        } while (flgZ);
        pushAddress(0xFA5D);
        SUB_01DA44();
        if (handleReturnAddress(poppedEntry.value, 0xFA5D)) return;
    } while (flgC);
    flgC = true;
    popAddress();
}

void game::SUB_01FA6A() {
    a = myMapper->readCPU(0x015D);
    setLoadFlag(a);
    if (!flgZ) {
        y = myMapper->readCPU(0x001A);
        opDEY(1);
        a = y;
        opAND(0x01);
        if (flgZ) {
            pushAddress(0xFA79);
            SUB_01FA8E();
            if (handleReturnAddress(poppedEntry.value, 0xFA79)) return;
            pushAddress(0xFA7C);
            SUB_01DEDC();
            if (handleReturnAddress(poppedEntry.value, 0xFA7C)) return;
            opDEC(0x015D, 1);
            if (!flgZ) {
                goto L_01FA8D;
            }
            pushAddress(0xFA84);
            SUB_01D10E();
            if (handleReturnAddress(poppedEntry.value, 0xFA84)) return;
            a = 0x00;
            myMapper->writeCPU(0x015C, a);
            myMapper->writeCPU(0x015D, a);
        }
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
    SUB_01D10E();
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

void game::SUB_01FAEF() {
    pushAddress(0xFAF1);
    jump(0x9359);
    if (handleReturnAddress(poppedEntry.value, 0xFAF1)) return;
    x = myMapper->readCPU(0x007E);
    setLoadFlag(x);
    if (flgZ) {
        jump(0xFB05);
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        goto L_01FAFE;
    }
    opDEC(0x007E, 1);
L_01FAFE:
    a = myMapper->readCPU(0x007E);
    opAND(0x03);
    myMapper->writeCPU(0x0338, a);
    SUB_01FB05();
    return;
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
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xFB16)) return;
    y = 0x05;
    pushAddress(0xFB1B);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xFB1B)) return;
    x = 0x15;
L_01FB1E:
    a = x;
    jump(0xCC95);
    return;
}

void game::SUB_01FC97() {
    pushAddress(0xFC99);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xFC99)) return;
    pushAddress(0xFC9C);
    jump(0x96C1);
    if (handleReturnAddress(poppedEntry.value, 0xFC9C)) return;
    y = 0x05;
    jump(0xC1D6);
    return;
}

void game::SUB_01FCB9() {
    y = 0x05;
    pushAddress(0xFCBD);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xFCBD)) return;
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x02);
    if (!flgZ) {
        goto L_01FCCA;
    }
    pushAddress(0xFCC6);
    jump(0x8044);
    if (handleReturnAddress(poppedEntry.value, 0xFCC6)) return;
    jump(0xC1D4);
    return;
L_01FCCA:
    pushAddress(0xFCCC);
    jump(0x88B7);
    if (handleReturnAddress(poppedEntry.value, 0xFCCC)) return;
    jump(0xC1D4);
    return;
}

void game::SUB_01FCD0() {
    y = 0x06;
    pushAddress(0xFCD4);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xFCD4)) return;
    a = 0x06;
    a = myMapper->readCPU(0x0071);
    pushAddress(0xFCDB);
    jump(0xA333);
    if (handleReturnAddress(poppedEntry.value, 0xFCDB)) return;
    myMapper->writeCPU(0x0008, a);
    a = 0x1B;
    pushAddress(0xFCE2);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xFCE2)) return;
    a = myMapper->readCPU(0x0008);
    pushAddress(0xFCE7);
    SUB_01CC68();
    if (handleReturnAddress(poppedEntry.value, 0xFCE7)) return;
    pushAddress(0xFCEA);
    SUB_01CC5F();
    if (handleReturnAddress(poppedEntry.value, 0xFCEA)) return;
    y = 0x05;
    jump(0xC1D6);
    return;
}

void game::SUB_01FD18() {
    pushAddress(0xFD1A);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xFD1A)) return;
    pushAddress(0xFD1D);
    SUB_01CAAF();
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
    SUB_01C132();
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
        SUB_01C1D6();
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
        SUB_01FD7E();
        if (handleReturnAddress(poppedEntry.value, 0xFD71)) return;
        y = myMapper->readCPU(0x0014);
    }
L_01FD77:
    pushAddress(0xFD79);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xFD79)) return;
    pushAddress(0xFD7C);
    SUB_01C102();
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

void game::SUB_01FEB3() {
    while (true) {
        if (myMapper->readCPU(0x07FB) != 0) {
            goto L_01FEFD;
        }
        a = myMapper->readCPU(0x07F8);
        setLoadFlag(a);
        if (flgZ) {
            opINC(0x00F1, 1);
            if (flgZ) {
                opINC(0x00F2, 1);
            }
            y = 0x05;
            pushAddress(0xFEC7);
            SUB_01C1D6();
            if (handleReturnAddress(poppedEntry.value, 0xFEC7)) return;
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00F1) + (myMapper->readCPU((0x00F1 + 1) & 0x00ff) << 8) + y);
            opCMP(a, 0xFF);
            if (flgZ) {
                goto L_01FEF9;
            }
            myMapper->writeCPU(0x07F8, a);
            opINC(0x00F1, 1);
            if (flgZ) {
                opINC(0x00F2, 1);
            }
            myMapper->writeCPU(0x07F9, myMapper->readCPU(myMapper->readCPU(0x00F1) + (myMapper->readCPU((0x00F1 + 1) & 0x00ff) << 8) + y));
            opINC(0x00F1, 1);
            if (flgZ) {
                opINC(0x00F2, 1);
            }
            a = myMapper->readCPU(myMapper->readCPU(0x00F1) + (myMapper->readCPU((0x00F1 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x07FA, a);
            pushAddress(0xFEEB);
            SUB_01C1D4();
            if (handleReturnAddress(poppedEntry.value, 0xFEEB)) return;
        }
        opDEC(0x07F8, 1);
        myMapper->writeCPU(0x00F5, myMapper->readCPU(0x07F9));
        a = myMapper->readCPU(0x07FA);
        myMapper->writeCPU(0x00F7, a);
    L_01FEF9:
        pushAddress(0xFEFB);
        SUB_01C1D4();
        if (handleReturnAddress(poppedEntry.value, 0xFEFB)) return;
        popAddress();
        return;
    L_01FEFD:
        a = myMapper->readCPU(0x00F3);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x00F1, myMapper->readCPU(0xFF24 + x));
        myMapper->writeCPU(0x00F2, myMapper->readCPU(0xFF25 + x));
        opINC(0x00F3, 1);
        opDEC(0x00F1, 1);
        if (!flgZ) {
            goto L_01FF13;
        }
        opDEC(0x00F2, 1);
    L_01FF13:
        a = 0x00;
        myMapper->writeCPU(0x07F8, a);
        myMapper->writeCPU(0x07F9, a);
        myMapper->writeCPU(0x07FA, a);
        myMapper->writeCPU(0x07FB, a);
    }
}

void game::jump(Uint16 target) {
    Uint32 tAddress = myMapper->readRealAddress(target);
    switch (tAddress) {
    case 0x000112:
        SUB_000112();
        break;
    case 0x0000EF:
        SUB_0000EF();
        break;
    case 0x000134:
        SUB_000134();
        break;
    case 0x0000D2:
        SUB_0000D2();
        break;
    case 0x000141:
        SUB_000141();
        break;
    case 0x000135:
        SUB_000135();
        break;
    case 0x0000C2:
        SUB_0000C2();
        break;
    case 0x00015A:
        SUB_00015A();
        break;
    case 0x000110:
        SUB_000110();
        break;
    case 0x00016E:
        SUB_00016E();
        break;
    case 0x0000E1:
        SUB_0000E1();
        break;
    case 0x00011C:
        SUB_00011C();
        break;
    case 0x000383:
        SUB_000383();
        break;
    case 0x0003D3:
        SUB_0003D3();
        break;
    case 0x0003E4:
        SUB_0003E4();
        break;
    case 0x00047D:
        SUB_00047D();
        break;
    case 0x000562:
        SUB_000562();
        break;
    case 0x000352:
        SUB_000352();
        break;
    case 0x0002BF:
        SUB_0002BF();
        break;
    case 0x0005C2:
        SUB_0005C2();
        break;
    case 0x000743:
        SUB_000743();
        break;
    case 0x0006E4:
        SUB_0006E4();
        break;
    case 0x019BE3:
        SUB_019BE3();
        break;
    case 0x01A1E5:
        SUB_01A1E5();
        break;
    case 0x0193D9:
        SUB_0193D9();
        break;
    case 0x019458:
        SUB_019458();
        break;
    case 0x019A69:
        SUB_019A69();
        break;
    case 0x019BBA:
        SUB_019BBA();
        break;
    case 0x019782:
        SUB_019782();
        break;
    case 0x0193C5:
        SUB_0193C5();
        break;
    case 0x019578:
        SUB_019578();
        break;
    case 0x019583:
        SUB_019583();
        break;
    case 0x01962C:
        SUB_01962C();
        break;
    case 0x019AF8:
        SUB_019AF8();
        break;
    case 0x0195E4:
        SUB_0195E4();
        break;
    case 0x019605:
        SUB_019605();
        break;
    case 0x01971D:
        SUB_01971D();
        break;
    case 0x01977B:
        SUB_01977B();
        break;
    case 0x0197A7:
        SUB_0197A7();
        break;
    case 0x01977A:
        SUB_01977A();
        break;
    case 0x0197EA:
        SUB_0197EA();
        break;
    case 0x019539:
        SUB_019539();
        break;
    case 0x0197EB:
        SUB_0197EB();
        break;
    case 0x0198AA:
        SUB_0198AA();
        break;
    case 0x01990A:
        SUB_01990A();
        break;
    case 0x01990B:
        SUB_01990B();
        break;
    case 0x0198F3:
        SUB_0198F3();
        break;
    case 0x0198FE:
        SUB_0198FE();
        break;
    case 0x019938:
        SUB_019938();
        break;
    case 0x019A28:
        SUB_019A28();
        break;
    case 0x019AE0:
        SUB_019AE0();
        break;
    case 0x01DA5F:
        SUB_01DA5F();
        break;
    case 0x019B89:
        SUB_019B89();
        break;
    case 0x019B7C:
        SUB_019B7C();
        break;
    case 0x019C6D:
        SUB_019C6D();
        break;
    case 0x019C43:
        SUB_019C43();
        break;
    case 0x019DC0:
        SUB_019DC0();
        break;
    case 0x019F56:
        SUB_019F56();
        break;
    case 0x019ECB:
        SUB_019ECB();
        break;
    case 0x019F60:
        SUB_019F60();
        break;
    case 0x019FE7:
        SUB_019FE7();
        break;
    case 0x01A037:
        SUB_01A037();
        break;
    case 0x01A0CD:
        SUB_01A0CD();
        break;
    case 0x01A23B:
        SUB_01A23B();
        break;
    case 0x01CC5F:
        SUB_01CC5F();
        break;
    case 0x01C1A7:
        SUB_01C1A7();
        break;
    case 0x01A23A:
        SUB_01A23A();
        break;
    case 0x01A824:
        SUB_01A824();
        break;
    case 0x01EB6A:
        SUB_01EB6A();
        break;
    case 0x01AAE1:
        SUB_01AAE1();
        break;
    case 0x01AD4F:
        SUB_01AD4F();
        break;
    case 0x01AD68:
        SUB_01AD68();
        break;
    case 0x01AD74:
        SUB_01AD74();
        break;
    case 0x01C371:
        SUB_01C371();
        break;
    case 0x01B858:
        SUB_01B858();
        break;
    case 0x01C37A:
        SUB_01C37A();
        break;
    case 0x01C363:
        SUB_01C363();
        break;
    case 0x01CC95:
        SUB_01CC95();
        break;
    case 0x01C365:
        SUB_01C365();
        break;
    case 0x01C229:
        SUB_01C229();
        break;
    case 0x01B9D6:
        SUB_01B9D6();
        break;
    case 0x01C0C0:
        SUB_01C0C0();
        break;
    case 0x01C0B9:
        SUB_01C0B9();
        break;
    case 0x01C1D8:
        SUB_01C1D8();
        break;
    case 0x01C299:
        SUB_01C299();
        break;
    case 0x01C282:
        SUB_01C282();
        break;
    case 0x01CED0:
        SUB_01CED0();
        break;
    case 0x01C98A:
        SUB_01C98A();
        break;
    case 0x01C373:
        SUB_01C373();
        break;
    case 0x01C4AA:
        SUB_01C4AA();
        break;
    case 0x01C55D:
        SUB_01C55D();
        break;
    case 0x01C575:
        SUB_01C575();
        break;
    case 0x01C52C:
        SUB_01C52C();
        break;
    case 0x01C582:
        SUB_01C582();
        break;
    case 0x01C57B:
        SUB_01C57B();
        break;
    case 0x01C994:
        SUB_01C994();
        break;
    case 0x01C90D:
        SUB_01C90D();
        break;
    case 0x01C903:
        SUB_01C903();
        break;
    case 0x01C102:
        SUB_01C102();
        break;
    case 0x01C176:
        SUB_01C176();
        break;
    case 0x01CB11:
        SUB_01CB11();
        break;
    case 0x01F69E:
        SUB_01F69E();
        break;
    case 0x01CCA0:
        SUB_01CCA0();
        break;
    case 0x01CCF6:
        SUB_01CCF6();
        break;
    case 0x01CCF2:
        SUB_01CCF2();
        break;
    case 0x01CCF0:
        SUB_01CCF0();
        break;
    case 0x01FAEF:
        SUB_01FAEF();
        break;
    case 0x01CF50:
        SUB_01CF50();
        break;
    case 0x01D195:
        SUB_01D195();
        break;
    case 0x01F131:
        SUB_01F131();
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
    case 0x01E0E2:
        SUB_01E0E2();
        break;
    case 0x01EC60:
        SUB_01EC60();
        break;
    case 0x01DF0E:
        SUB_01DF0E();
        break;
    case 0x01E922:
        SUB_01E922();
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
    case 0x01DC50:
        SUB_01DC50();
        break;
    case 0x01EF04:
        SUB_01EF04();
        break;
    case 0x01F62D:
        SUB_01F62D();
        break;
    case 0x01F68C:
        SUB_01F68C();
        break;
    case 0x01F87C:
        SUB_01F87C();
        break;
    case 0x01F99B:
        SUB_01F99B();
        break;
    case 0x01F972:
        SUB_01F972();
        break;
    case 0x01FB05:
        SUB_01FB05();
        break;
    case 0x01C1D6:
        SUB_01C1D6();
        break;
    case 0x01C1D4:
        SUB_01C1D4();
        break;
    case 0x00000A:
        SUB_00000A();
        break;
    case 0x000052:
        SUB_000052();
        break;
    case 0x0000D6:
        SUB_0000D6();
        break;
    case 0x00017B:
        SUB_00017B();
        break;
    case 0x000187:
        SUB_000187();
        break;
    case 0x00038A:
        SUB_00038A();
        break;
    case 0x01934C:
        SUB_01934C();
        break;
    case 0x019380:
        SUB_019380();
        break;
    case 0x019482:
        SUB_019482();
        break;
    case 0x019511:
        SUB_019511();
        break;
    case 0x019586:
        SUB_019586();
        break;
    case 0x01965B:
        SUB_01965B();
        break;
    case 0x019720:
        SUB_019720();
        break;
    case 0x019757:
        SUB_019757();
        break;
    case 0x0197AA:
        SUB_0197AA();
        break;
    case 0x0197F2:
        SUB_0197F2();
        break;
    case 0x01A048:
        SUB_01A048();
        break;
    case 0x01A08A:
        SUB_01A08A();
        break;
    case 0x01A169:
        SUB_01A169();
        break;
    case 0x01A17D:
        SUB_01A17D();
        break;
    case 0x01A2E8:
        SUB_01A2E8();
        break;
    case 0x01A333:
        SUB_01A333();
        break;
    case 0x01A357:
        SUB_01A357();
        break;
    case 0x01A825:
        SUB_01A825();
        break;
    case 0x01AE8C:
        SUB_01AE8C();
        break;
    case 0x01AAE2:
        SUB_01AAE2();
        break;
    case 0x01B7DC:
        SUB_01B7DC();
        break;
    case 0x01B823:
        SUB_01B823();
        break;
    case 0x01B859:
        SUB_01B859();
        break;
    case 0x01B8D2:
        SUB_01B8D2();
        break;
    case 0x01B911:
        SUB_01B911();
        break;
    case 0x01B99D:
        SUB_01B99D();
        break;
    case 0x01B9C3:
        SUB_01B9C3();
        break;
    case 0x01B9FC:
        SUB_01B9FC();
        break;
    case 0x01C232:
        SUB_01C232();
        break;
    case 0x01C2DE:
        SUB_01C2DE();
        break;
    case 0x01C32C:
        SUB_01C32C();
        break;
    case 0x01C382:
        SUB_01C382();
        break;
    case 0x01C4E7:
        SUB_01C4E7();
        break;
    case 0x01DD3D:
        SUB_01DD3D();
        break;
    default:
		string mapperMode = myMapper->getMapperMode();
        printf("Unhandled jump to address: %04X\n", target);
		exit(1);
    }
}
