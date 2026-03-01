#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"
#include <stdexcept> // Add this include to resolve std::runtime_error

//SUB_00000A fill content starting 0x700 to ppu
//format: head byte: 0 = empty, 1 = horizontal, 2 = vertical
//2 ppu address bytes
//bytes to fill until a 0xFF byte is reached
//if the next byte after the 0xFF byte is larger than 0x03, fill a 0xFF

void game::brk() {
    popStatus();
    popIRAddress();
    return;
}

void game::initGame() {
}

void game::endGame() {

}

void game::atScanline(Uint8 scanline) {
    a = myMapper->readCPU(0x2002);
    a = myMapper->readCPU(0x002E);
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU(0x2005, a);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
}

void game::atSprite0Hit() {
}

void game::SUB_00000A() {
    y = 0x00;
    do {
        x = myMapper->readCPU(0x0700 + y);
        setLoadFlag(x);
        if (flgZ) {
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
    SUB_000112();
    return;
}

void game::SUB_0000D2() {
    opINY(1);
    flgC = false;
    if (!flgC) {
        SUB_0000EF();
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
        SUB_000134();
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
        SUB_0000D2();
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
        SUB_0000C2();
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
    SUB_000110();
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
        SUB_0000E1();
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
        SUB_0000E1();
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
    SUB_0000E1();
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
    SUB_000110();
    return;
}

void game::SUB_00016E() {
    a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x08);
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
    SUB_00011C();
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
        SUB_000383();
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
    SUB_0003D3();
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
        SUB_0003E4();
        return;
    }
    SUB_00047D();
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
        SUB_000562();
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
        SUB_000562();
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
    SUB_000562();
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
        SUB_000383();
        return;
    L_0004A0:
        if (a == 0xFE) {
            SUB_000352();
            return;
        }
        if (x != 0xB0) {
            a = myMapper->readCPU((0x0008 + x) & 0x00ff);
            opAND(0x08);
            if (!flgZ) {
                goto L_0004B4;
            }
        }
        SUB_0002BF();
        return;
    L_0004B4:
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opAND(0xF7);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
        myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU((0x000E + x) & 0x00ff));
        a = myMapper->readCPU((0x000F + x) & 0x00ff);
        myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
        SUB_000383();
        return;
    }
    if (x != 0xB0) {
        a = myMapper->readCPU((0x0008 + x) & 0x00ff);
        opAND(0x01);
        if (!flgZ) {
            SUB_0005C2();
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
    SUB_000743();
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
        SUB_0003E4();
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
                SUB_00047D();
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

void game::SUB_014008() {
    a = myMapper->readCPU(0x046C + x);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x800F);
        SUB_01EE48();
        if (handleReturnAddress(poppedEntry.value, 0x800F)) return;
        myMapper->writeCPU(0x004C, 0x10);
        a = myMapper->readCPU(0x0354 + x);
        myMapper->writeCPU(0x004D, a);
        pushAddress(0x801B);
        SUB_01EC21();
        if (handleReturnAddress(poppedEntry.value, 0x801B)) return;
        a = myMapper->readCPU(0x0014);
        setLoadFlag(a);
        if (flgZ) {
            goto L_014023;
        }
        SUB_01EAA9();
        return;
    L_014023:
        pushAddress(0x8025);
        SUB_01EF9C();
        if (handleReturnAddress(poppedEntry.value, 0x8025)) return;
        if (myMapper->readCPU(0x0014) != 0) {
            jump(0x8056);
            return;
        }
        a = 0x01;
        myMapper->writeCPU(0x046C + x, a);
        SUB_01F1D2();
        return;
    }
    pushAddress(0x8034);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0x8034)) return;
    pushAddress(0x8037);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0x8037)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        jump(0x8056);
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x046C + x, a);
    SUB_01EFAF();
    return;
}

void game::SUB_014044() {
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x0008, 0x03);
    y = 0x04;
    SUB_01404C();
    return;
}

void game::SUB_01404C() {
    if (myMapper->readCPU(0x0434 + y) == 0) {
        jump(0x8057);
        return;
    }
    SUB_014051();
    return;
}

void game::SUB_014051() {
    opINY(1);
    opCMP(y, 0x0C);
    if (!flgC) {
        SUB_01404C();
        return;
    }
    SUB_014056();
    return;
}

void game::SUB_014056() {
    popAddress();
}

void game::SUB_014057() {
    myMapper->writeCPU(0x0016, 0x25);
    a = 0x50;
    pushAddress(0x805F);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x805F)) return;
    myMapper->writeCPU(0x0450 + y, 0x00);
    a = myMapper->readCPU(0x0008);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x03FC + y, myMapper->readCPU(0x8088 + x));
    myMapper->writeCPU(0x0418 + y, myMapper->readCPU(0x8089 + x));
    myMapper->writeCPU(0x03C4 + y, myMapper->readCPU(0x8090 + x));
    myMapper->writeCPU(0x03E0 + y, myMapper->readCPU(0x8091 + x));
    opDEC(0x0008, 1);
    if (!flgZ) {
        SUB_014051();
        return;
    }
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_014098() {
    myMapper->writeCPU(0x004C, 0x08);
    myMapper->writeCPU(0x004E, x);
    y = 0x0C;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_0140AA;
        }
        opINY(1);
        opCMP(y, 0x0E);
    } while (!flgC);
L_0140AA:
    myMapper->writeCPU(0x0016, 0x26);
    a = 0x08;
    pushAddress(0x80B2);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x80B2)) return;
    a = myMapper->readCPU(0x0354 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x004C));
    myMapper->writeCPU(0x0354 + y, a);
    myMapper->writeCPU(0x03FC + y, 0x01);
    myMapper->writeCPU(0x0418 + y, 0xC0);
    popAddress();
}

void game::SUB_0140C7() {
    pushAddress(0x80C9);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x80C9)) return;
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0x80D1);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x80D1)) return;
    SUB_0140E0();
    return;
}

void game::SUB_0140E0() {
    if (myMapper->readCPU(0x0048) != 0) {
        goto L_0140E5;
    }
    popAddress();
    return;
L_0140E5:
    myMapper->writeCPU(0x004E, x);
    y = 0x81;
    a = 0x78;
    SUB_01ED34();
    return;
}

void game::SUB_0140EE() {
    a = myMapper->readCPU(0x004B);
    opEOR(0x01);
    myMapper->writeCPU(0x004B, a);
    SUB_014103();
    return;
}

void game::SUB_0140F7() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0140FD();
        return;
    }
    popAddress();
}

void game::SUB_0140FD() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    myMapper->writeCPU(0x004B, a);
    SUB_014103();
    return;
}

void game::SUB_014103() {
    a = 0x48;
    y = myMapper->readCPU(0x004B);
    setLoadFlag(y);
    if (!flgZ) {
        opEOR(0xFF);
    }
    opADC(myMapper->readCPU(0x038C));
    opCMP(a, 0x10);
    if (!flgC) {
        SUB_0140EE();
        return;
    }
    opCMP(a, 0xF0);
    if (flgC) {
        SUB_0140EE();
        return;
    }
    myMapper->writeCPU(0x0001, a);
    myMapper->writeCPU(0x0059, a);
    a = myMapper->readCPU(0x0354);
    opSBC(0x28);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x8123);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0x8123)) return;
    pushAddress(0x8126);
    SUB_01EDA5();
    if (handleReturnAddress(poppedEntry.value, 0x8126)) return;
    x = myMapper->readCPU(0x004E);
    if (myMapper->readCPU(0x0009) != 0) {
        goto L_01413E;
    }
    a = myMapper->readCPU(0x0001);
    y = myMapper->readCPU(0x0002);
    pushAddress(0x8133);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x8133)) return;
    y = 0xC0;
    a = 0x00;
    pushAddress(0x813A);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x813A)) return;
    goto L_01414C;
L_01413E:
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0001);
    pushAddress(0x8144);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8144)) return;
    a = 0x00;
    y = 0xC0;
    pushAddress(0x814B);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x814B)) return;
L_01414C:
    a = 0x4A;
    pushAddress(0x8150);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8150)) return;
    a = 0x02;
    SUB_01F131();
    return;
}

void game::SUB_014156() {
    pushAddress(0x8158);
    SUB_01EC7D();
    if (handleReturnAddress(poppedEntry.value, 0x8158)) return;
    pushAddress(0x815B);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0x815B)) return;
    a = myMapper->readCPU(0x0059);
    opSBC(myMapper->readCPU(0x038C + x));
    if (flgC) {
        goto L_014165;
    }
    opEOR(0xFF);
L_014165:
    opCMP(a, 0x04);
    if (flgC) {
        SUB_01418B();
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x8176 + y);
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_01417A() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        goto L_014182;
    }
    SUB_0141DE();
    return;
L_014182:
    a = myMapper->readCPU(0x001A);
    opAND(0x0F);
    if (!flgZ) {
        SUB_01418B();
        return;
    }
    pushAddress(0x818A);
    SUB_014224();
    if (handleReturnAddress(poppedEntry.value, 0x818A)) return;
    SUB_01418B();
    return;
}

void game::SUB_01418B() {
    popAddress();
}

void game::SUB_01418C() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0141DE();
        return;
    }
    SUB_01EF56();
    return;
}

void game::SUB_014194() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x06);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    if (!flgN) {
        goto L_0141AD;
    }
    a = myMapper->readCPU(0x0354 + x);
    opCMP(a, 0x70);
    if (!flgC) {
        SUB_0141D1();
        return;
    }
L_0141AD:
    pushAddress(0x81AF);
    SUB_01EF43();
    if (handleReturnAddress(poppedEntry.value, 0x81AF)) return;
    pushAddress(0x81B2);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0x81B2)) return;
    a = myMapper->readCPU(0x038C + x);
    opCMP(a, 0x10);
    if (!flgC) {
        goto L_0141C7;
    }
    opCMP(a, 0xF0);
    if (!flgC) {
        goto L_0141C6;
    }
    a = 0xF0;
    do {
        myMapper->writeCPU(0x038C + x, a);
        pushAddress(0x81C5);
        SUB_01EAA9();
        if (handleReturnAddress(poppedEntry.value, 0x81C5)) return;
    L_0141C6:
        popAddress();
        return;
    L_0141C7:
        a = 0x10;
        setLoadFlag(a);
    } while (!flgZ);
    SUB_0141CB();
    return;
}

void game::SUB_0141CB() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0141D1();
        return;
    }
    popAddress();
}

void game::SUB_0141D1() {
    SUB_0140FD();
    return;
}

void game::SUB_0141D4() {
    pushAddress(0x81D6);
    SUB_01EC88();
    if (handleReturnAddress(poppedEntry.value, 0x81D6)) return;
    y = 0x06;
    a = 0x18;
    SUB_01ED34();
    return;
}

void game::SUB_0141DE() {
    a = myMapper->readCPU(0x0354);
    opSBC(myMapper->readCPU(0x0354 + x));
    if (!flgC) {
        SUB_0141D4();
        return;
    }
    a = myMapper->readCPU(0x0354);
    opADC(0x18);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x038C);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0x81F4);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0x81F4)) return;
    x = myMapper->readCPU(0x004E);
    opASL_M(0x0002, 1);
    opROL_M(0x0001, 1);
    if (myMapper->readCPU(0x0009) != 0) {
        goto L_014210;
    }
    y = 0x00;
    a = 0x02;
    pushAddress(0x8205);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8205)) return;
    a = myMapper->readCPU(0x0001);
    y = myMapper->readCPU(0x0002);
    pushAddress(0x820C);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x820C)) return;
    goto L_01421E;
L_014210:
    a = 0x01;
    y = 0x80;
    pushAddress(0x8216);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x8216)) return;
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0001);
    pushAddress(0x821D);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x821D)) return;
L_01421E:
    myMapper->writeCPU(0x046C + x, 0x05);
    SUB_014223();
    return;
}

void game::SUB_014223() {
    popAddress();
}

void game::SUB_014224() {
    a = myMapper->readCPU(0x0354);
    opSBC(myMapper->readCPU(0x0354 + x));
    if (flgC) {
        goto L_01422E;
    }
    opEOR(0xFF);
L_01422E:
    opCMP(a, 0x14);
    if (flgC) {
        SUB_014223();
        return;
    }
    pushAddress(0x8234);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x8234)) return;
    if (a >= 0x58) {
        jump(0x8223);
        return;
    }
    opCMP(y, myMapper->readCPU(0x0450));
    if (flgZ) {
        SUB_014223();
        return;
    }
    a = 0x02;
    y = 0x80;
    pushAddress(0x8245);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x8245)) return;
    y = 0x04;
    a = 0x08;
    SUB_01ED34();
    return;
}

void game::SUB_01424D() {
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opDEY(1);
        if (flgZ) {
            goto L_014287;
        }
        pushAddress(0x8257);
        SUB_01EE48();
        if (handleReturnAddress(poppedEntry.value, 0x8257)) return;
        pushAddress(0x825A);
        SUB_01EC50();
        if (handleReturnAddress(poppedEntry.value, 0x825A)) return;
        pushAddress(0x825D);
        SUB_01EF98();
        if (handleReturnAddress(poppedEntry.value, 0x825D)) return;
        a = myMapper->readCPU(0x0014);
        setLoadFlag(a);
        if (flgZ) {
            goto L_014286;
        }
        pushAddress(0x8264);
        SUB_01EFAF();
        if (handleReturnAddress(poppedEntry.value, 0x8264)) return;
    }
    else {
        pushAddress(0x826A);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0x826A)) return;
        opCMP(a, 0x40);
        if (!flgC) {
            goto L_014272;
        }
        SUB_01EE94();
        return;
    }
L_014272:
    pushAddress(0x8274);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x8274)) return;
    y = 0x00;
    a = 0x02;
    pushAddress(0x827B);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x827B)) return;
    a = 0x52;
    pushAddress(0x8280);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8280)) return;
    myMapper->writeCPU(0x046C + x, 0x01);
    do {
    L_014286:
        popAddress();
        return;
    L_014287:
        pushAddress(0x8289);
        SUB_01EE48();
        if (handleReturnAddress(poppedEntry.value, 0x8289)) return;
        pushAddress(0x828C);
        SUB_01EF98();
        if (handleReturnAddress(poppedEntry.value, 0x828C)) return;
    } while (myMapper->readCPU(0x0014) != 0);
    a = 0x1E;
    pushAddress(0x8295);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8295)) return;
    a = 0x01;
    y = 0x80;
    pushAddress(0x829C);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x829C)) return;
    a = 0x02;
    SUB_01F131();
    return;
}

void game::SUB_0142C5() {
    pushAddress(0x82C7);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x82C7)) return;
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0x82CF);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x82CF)) return;
    SUB_0142DA();
    return;
}

void game::SUB_0142DA() {
    if (myMapper->readCPU(0x0048) != 0) {
        jump(0x82DF);
        return;
    }
    SUB_0142DE();
    return;
}

void game::SUB_0142DE() {
    popAddress();
}

void game::SUB_0142DF() {
    y = 0x81;
    a = 0xB4;
    SUB_01ED34();
    return;
}

void game::SUB_0142E6() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_0142DE();
        return;
    }
    pushAddress(0x82ED);
    SUB_01FAB4();
    if (handleReturnAddress(poppedEntry.value, 0x82ED)) return;
    a = myMapper->readCPU(0x001A);
    opAND(0x03);
    myMapper->writeCPU(0x0055, a);
    SUB_0142F4();
    return;
}

void game::SUB_0142F4() {
    myMapper->writeCPU(0x03C4 + x, 0x00);
    myMapper->writeCPU(0x03E0 + x, 0x80);
    myMapper->writeCPU(0x046C + x, 0x02);
    popAddress();
}

void game::SUB_014304() {
    pushAddress(0x8306);
    SUB_01EF56();
    if (handleReturnAddress(poppedEntry.value, 0x8306)) return;
    opCMP(a, 0xA8);
    if (!flgC) {
        goto L_01430C;
    }
    popAddress();
    return;
L_01430C:
    pushAddress(0x830E);
    SUB_014371();
    if (handleReturnAddress(poppedEntry.value, 0x830E)) return;
    a = myMapper->readCPU(0x0354 + x);
    opADC(0x04);
    myMapper->writeCPU(0x04DC + x, a);
    a = 0x00;
    myMapper->writeCPU(0x04F8 + x, a);
    pushAddress(0x831E);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x831E)) return;
    y = 0xE0;
    a = 0x00;
    pushAddress(0x8325);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8325)) return;
    a = 0x1F;
    pushAddress(0x832A);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x832A)) return;
    opINC(0x0055, 1);
    a = myMapper->readCPU(0x0055);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x833A + y);
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_01433E() {
    pushAddress(0x8340);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0x8340)) return;
    a = myMapper->readCPU(0x038C + x);
    y = myMapper->readCPU(0x0450 + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01434F;
    }
    opCMP(a, 0x10);
    if (flgC) {
        SUB_014368();
        return;
    }
    if (!flgC) {
        goto L_014353;
    }
L_01434F:
    opCMP(a, 0xF0);
    if (!flgC) {
        SUB_014368();
        return;
    }
L_014353:
    SUB_01EAA9();
    return;
}

void game::SUB_014356() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014361;
    }
    pushAddress(0x835D);
    SUB_01EF13();
    if (handleReturnAddress(poppedEntry.value, 0x835D)) return;
    SUB_01433E();
    return;
L_014361:
    y = 0x04;
    a = 0x3C;
    pushAddress(0x8367);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x8367)) return;
    SUB_014368();
    return;
}

void game::SUB_014368() {
    popAddress();
}

void game::SUB_014369() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_014368();
        return;
    }
    SUB_0142F4();
    return;
}

void game::SUB_014371() {
    myMapper->writeCPU(0x004E, x);
    y = 0x0D;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_014380;
        }
        opDEY(1);
        opCMP(y, 0x08);
    } while (flgC);
    popAddress();
    return;
L_014380:
    myMapper->writeCPU(0x0016, 0x09);
    a = 0x1D;
    SUB_01ED82();
    return;
}

void game::SUB_014389() {
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x838E);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x838E)) return;
    SUB_014397();
    return;
}

void game::SUB_014397() {
    pushAddress(0x8399);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x8399)) return;
    pushAddress(0x839C);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0x839C)) return;
    myMapper->writeCPU(0x046C + x, 0x01);
    SUB_0143A2();
    return;
}

void game::SUB_0143A2() {
    popAddress();
}

void game::SUB_0143A3() {
    pushAddress(0x83A5);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0x83A5)) return;
    a = myMapper->readCPU(0x0354 + x);
    opADC(0x08);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x83B3);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0x83B3)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        SUB_0143A2();
        return;
    }
    pushAddress(0x83BA);
    SUB_01EFAF();
    if (handleReturnAddress(poppedEntry.value, 0x83BA)) return;
    SUB_0143BB();
    return;
}

void game::SUB_0143BB() {
    y = 0x80;
    a = 0x01;
    pushAddress(0x83C1);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x83C1)) return;
    y = 0x02;
    a = 0x18;
    SUB_01ED34();
    return;
}

void game::SUB_0143C9() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0143E6;
    }
    pushAddress(0x83D0);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0x83D0)) return;
    a = myMapper->readCPU(0x0354 + x);
    opADC(0x08);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x83DE);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0x83DE)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_0143A2();
        return;
    }
    SUB_014397();
    return;
L_0143E6:
    y = 0x03;
    a = 0x01;
    SUB_01ED34();
    return;
}

void game::SUB_0143ED() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0143BB();
        return;
    }
    popAddress();
}

void game::SUB_0143F3() {
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x83F8);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x83F8)) return;
    SUB_0143FF();
    return;
}

void game::SUB_0143FF() {
    a = myMapper->readCPU(0x0354);
    opSBC(myMapper->readCPU(0x0354 + x));
    opCMP(a, 0x38);
    if (flgC) {
        SUB_01EE94();
        return;
    }
    pushAddress(0x840E);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x840E)) return;
    opCMP(a, 0x60);
    if (!flgC) {
        goto L_014416;
    }
    SUB_01EE94();
    return;
L_014416:
    myMapper->writeCPU(0x046C + x, 0x01);
    myMapper->writeCPU(0x0450 + x, y);
    a = 0x01;
    myMapper->writeCPU(0x03FC + x, a);
    myMapper->writeCPU(0x03C4 + x, a);
    a = 0x80;
    myMapper->writeCPU(0x0418 + x, a);
    myMapper->writeCPU(0x03E0 + x, a);
    a = 0x3B;
    pushAddress(0x8433);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8433)) return;
    SUB_01EE94();
    return;
}

void game::SUB_014437() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x08);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    if (!flgN) {
        goto L_014450;
    }
    a = 0x02;
    setLoadFlag(a);
    myMapper->writeCPU(0x046C + x, a);
    if (!flgZ) {
        SUB_014453();
        return;
    }
L_014450:
    pushAddress(0x8452);
    SUB_01EF43();
    if (handleReturnAddress(poppedEntry.value, 0x8452)) return;
    SUB_014453();
    return;
}

void game::SUB_014453() {
    SUB_01EE48();
    return;
}

void game::SUB_014456() {
    pushAddress(0x8458);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x8458)) return;
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opDEY(1);
        if (!flgZ) {
            pushAddress(0x8463);
            SUB_01EC50();
            if (handleReturnAddress(poppedEntry.value, 0x8463)) return;
            pushAddress(0x8466);
            SUB_01EF9C();
            if (handleReturnAddress(poppedEntry.value, 0x8466)) return;
            if (myMapper->readCPU(0x0014) == 0) {
                popAddress();
                return;
            }
            myMapper->writeCPU(0x046C + x, 0x00);
            a = myMapper->readCPU(0x0354 + x);
            opAND(0xF0);
            myMapper->writeCPU(0x0354 + x, a);
            popAddress();
            return;
        }
        a = myMapper->readCPU(0x0354);
        opSBC(myMapper->readCPU(0x0354 + x));
        if (!flgC) {
            opEOR(0xFF);
        }
        opCMP(a, 0x04);
        if (flgC) {
            y = 0x00;
            a = 0xC0;
            SUB_01ED34();
            return;
        }
        opDEC(0x054C + x, 1);
        if (flgZ) {
            pushAddress(0x8496);
            SUB_0144F5();
            if (handleReturnAddress(poppedEntry.value, 0x8496)) return;
        }
        goto L_0144B5;
    }
    a = myMapper->readCPU(0x0354);
    opSBC(myMapper->readCPU(0x0354 + x));
    if (!flgC) {
        opEOR(0xFF);
    }
    opCMP(a, 0x04);
    if (!flgC) {
        SUB_0144F5();
        return;
    }
    opDEC(0x054C + x, 1);
    if (flgZ) {
        pushAddress(0x84AF);
        SUB_01EAA9();
        if (handleReturnAddress(poppedEntry.value, 0x84AF)) return;
        a = 0xC0;
        myMapper->writeCPU(0x054C + x, a);
    }
L_0144B5:
    pushAddress(0x84B7);
    SUB_01EE75();
    if (handleReturnAddress(poppedEntry.value, 0x84B7)) return;
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x84BF);
        SUB_01EF9C();
        if (handleReturnAddress(poppedEntry.value, 0x84BF)) return;
        if (myMapper->readCPU(0x0014) != 0) {
            goto L_0144CC;
        }
        a = 0x02;
        myMapper->writeCPU(0x046C + x, a);
        SUB_01F1D2();
        return;
    }
L_0144CC:
    myMapper->writeCPU(0x004C, 0x10);
    a = myMapper->readCPU(0x0354 + x);
    myMapper->writeCPU(0x004D, a);
    pushAddress(0x84D7);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0x84D7)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0144E0;
    }
    pushAddress(0x84DE);
    SUB_01EAA9();
    if (handleReturnAddress(poppedEntry.value, 0x84DE)) return;
    do {
        popAddress();
        return;
    L_0144E0:
        myMapper->writeCPU(0x004C, 0x04);
        a = myMapper->readCPU(0x0354 + x);
        opADC(0x14);
        myMapper->writeCPU(0x004D, a);
        pushAddress(0x84ED);
        SUB_01EC21();
        if (handleReturnAddress(poppedEntry.value, 0x84ED)) return;
        a = myMapper->readCPU(0x0014);
        setLoadFlag(a);
    } while (!flgZ);
    SUB_01EAA9();
    return;
}

void game::SUB_0144F5() {
    pushAddress(0x84F7);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x84F7)) return;
    y = 0x01;
    a = 0xC0;
    SUB_01ED34();
    return;
}

void game::SUB_0144FF() {
    pushAddress(0x8501);
    SUB_01EF69();
    if (handleReturnAddress(poppedEntry.value, 0x8501)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8507);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8507)) return;
    SUB_014516();
    return;
}

void game::SUB_014516() {
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x0450 + x);
    }
    else {
        pushAddress(0x8525);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0x8525)) return;
        y = myMapper->readCPU(0x0450 + x);
        opCMP(a, 0x48);
        if (!flgC) {
            goto L_014531;
        }
        a = y;
        goto L_014534;
    L_014531:
        a = y;
        opEOR(0x01);
    }
L_014534:
    myMapper->writeCPU(0x04F8 + x, a);
    popAddress();
}

void game::SUB_014538() {
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x04DC + x, myMapper->readCPU(0x8551 + y));
    y = 0x80;
    a = 0x01;
    pushAddress(0x8549);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8549)) return;
    y = 0x01;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014555() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opDEC(0x04DC + x, 1);
    if (flgZ) {
        goto L_01456A;
    }
    pushAddress(0x8562);
    SUB_014516();
    if (handleReturnAddress(poppedEntry.value, 0x8562)) return;
    y = 0x02;
    a = 0x10;
    SUB_01ED34();
    return;
L_01456A:
    y = 0x03;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014571() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0145B0;
    }
    pushAddress(0x8578);
    SUB_01EE6F();
    if (handleReturnAddress(poppedEntry.value, 0x8578)) return;
    myMapper->writeCPU(0x004D, myMapper->readCPU(0x0354 + x));
    a = 0x0C;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x8584);
    SUB_01EC1A();
    if (handleReturnAddress(poppedEntry.value, 0x8584)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        goto L_014592;
    }
    a = myMapper->readCPU(0x04F8 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x04F8 + x, a);
    do {
        popAddress();
        return;
    L_014592:
        pushAddress(0x8594);
        SUB_01EF9C();
        if (handleReturnAddress(poppedEntry.value, 0x8594)) return;
    } while (myMapper->readCPU(0x0014) != 0);
    y = 0x40;
    a = 0x01;
    pushAddress(0x859F);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x859F)) return;
    myMapper->writeCPU(0x03C4 + x, 0x02);
    myMapper->writeCPU(0x03E0 + x, 0x80);
    myMapper->writeCPU(0x046C + x, 0x05);
    popAddress();
    return;
L_0145B0:
    y = 0x01;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_0145B7() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0145C5;
    }
    pushAddress(0x85C4);
    SUB_01ED5C();
    if (handleReturnAddress(poppedEntry.value, 0x85C4)) return;
L_0145C5:
    myMapper->writeCPU(0x054C + x, 0x08);
    myMapper->writeCPU(0x046C + x, 0x04);
    popAddress();
}

void game::SUB_0145D0() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0145D6();
        return;
    }
    popAddress();
}

void game::SUB_0145D6() {
    myMapper->writeCPU(0x046C + x, 0x00);
    popAddress();
}

void game::SUB_0145DC() {
    pushAddress(0x85DE);
    SUB_01EE6F();
    if (handleReturnAddress(poppedEntry.value, 0x85DE)) return;
    pushAddress(0x85E1);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0x85E1)) return;
    pushAddress(0x85E4);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0x85E4)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        goto L_0145F6;
    }
    a = myMapper->readCPU(0x0354 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0354 + x, a);
    myMapper->writeCPU(0x046C + x, 0x06);
L_0145F6:
    popAddress();
}

void game::SUB_0145F7() {
    myMapper->writeCPU(0x004E, x);
    y = 0x0D;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_014606;
        }
        opDEY(1);
        opCMP(y, 0x09);
    } while (flgC);
    popAddress();
    return;
L_014606:
    myMapper->writeCPU(0x0016, 0x22);
    a = 0x03;
    pushAddress(0x860E);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x860E)) return;
    x = 0x08;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_014619;
    }
    x = 0xF8;
L_014619:
    a = x;
    opADC(myMapper->readCPU(0x0354 + y));
    myMapper->writeCPU(0x0354 + y, a);
    myMapper->writeCPU(0x04DC + y, a);
    a = 0x01;
    myMapper->writeCPU(0x03FC + y, a);
    myMapper->writeCPU(0x03C4 + y, a);
    a = 0x80;
    myMapper->writeCPU(0x0418 + y, a);
    myMapper->writeCPU(0x03E0 + y, a);
    a = 0x00;
    myMapper->writeCPU(0x04F8 + y, a);
    pushAddress(0x863A);
    SUB_01FD04();
    if (handleReturnAddress(poppedEntry.value, 0x863A)) return;
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01463E() {
    pushAddress(0x8640);
    SUB_01EF13();
    if (handleReturnAddress(poppedEntry.value, 0x8640)) return;
    SUB_01EE48();
    return;
}

void game::SUB_014644() {
    pushAddress(0x8646);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x8646)) return;
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0x864E);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x864E)) return;
    SUB_01465B();
    return;
}

void game::SUB_01465B() {
    a = myMapper->readCPU(0x001A);
    opAND(0x1F);
    if (flgZ) {
        pushAddress(0x8663);
        SUB_01EF7C();
        if (handleReturnAddress(poppedEntry.value, 0x8663)) return;
        y = 0x00;
        a = myMapper->readCPU(0x0450 + x);
        opCMP(a, myMapper->readCPU(0x0450));
        if (!flgZ) {
            pushAddress(0x8670);
            SUB_01EF84();
            if (handleReturnAddress(poppedEntry.value, 0x8670)) return;
            opCMP(a, 0x38);
            if (flgC) {
                goto L_014679;
            }
            opINY(1);
            pushAddress(0x8678);
            SUB_01EAA9();
            if (handleReturnAddress(poppedEntry.value, 0x8678)) return;
        }
    }
L_014679:
    popAddress();
}

void game::SUB_01467A() {
    pushAddress(0x867C);
    SUB_01465B();
    if (handleReturnAddress(poppedEntry.value, 0x867C)) return;
    opCMP(y, 0x00);
    if (!flgZ) {
        goto L_014687;
    }
    myMapper->writeCPU(0x046C + x, 0x02);
    popAddress();
    return;
L_014687:
    SUB_01EF7C();
    return;
}

void game::SUB_01468A() {
    if (myMapper->readCPU(0x0048) != 0) {
        goto L_01468F;
    }
    popAddress();
    return;
L_01468F:
    a = x;
    opADC(myMapper->readCPU(0x001A));
    opAND(0x03);
    myMapper->writeCPU(0x04DC + x, a);
    myMapper->writeCPU(0x0584 + x, 0x20);
    myMapper->writeCPU(0x0530 + x, 0x00);
    y = 0x81;
    a = 0x78;
    SUB_01ED34();
    return;
}

void game::SUB_0146A8() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0146AE;
    }
    popAddress();
    return;
L_0146AE:
    y = 0xC0;
    a = 0x00;
    pushAddress(0x86B4);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x86B4)) return;
    SUB_0146B5();
    return;
}

void game::SUB_0146B5() {
    pushAddress(0x86B7);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x86B7)) return;
    a = 0x1B;
    pushAddress(0x86BC);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x86BC)) return;
    opINC(0x04DC + x, 1);
    a = myMapper->readCPU(0x04DC + x);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x86CE + y);
    y = 0x02;
    SUB_01ED34();
    return;
}

void game::SUB_0146D2() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        pushAddress(0x86D9);
        SUB_01465B();
        if (handleReturnAddress(poppedEntry.value, 0x86D9)) return;
        pushAddress(0x86DC);
        SUB_01EE48();
        if (handleReturnAddress(poppedEntry.value, 0x86DC)) return;
        a = myMapper->readCPU(0x038C + x);
        if (myMapper->readCPU(0x0450 + x) != 0) {
            if (a >= 0x09) {
                goto L_0146F6;
            }
            a = 0x08;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0146F3;
            }
        }
        if (a < 0xF8) {
            goto L_0146F6;
        }
        a = 0xF8;
    L_0146F3:
        myMapper->writeCPU(0x038C + x, a);
    L_0146F6:
        popAddress();
        return;
    }
    pushAddress(0x86F9);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x86F9)) return;
    y = 0x03;
    a = 0x28;
    SUB_01ED34();
    return;
}

void game::SUB_014701() {
    y = 0x00;
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014715;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x02);
    if (flgZ) {
        goto L_014710;
    }
    y = 0x43;
    do {
    L_014710:
        myMapper->writeCPU(0x0338 + x, y);
        popAddress();
        return;
    L_014715:
        pushAddress(0x8717);
        SUB_0145F7();
        if (handleReturnAddress(poppedEntry.value, 0x8717)) return;
        a = 0x08;
        y = 0x04;
        pushAddress(0x871E);
        SUB_01ED34();
        if (handleReturnAddress(poppedEntry.value, 0x871E)) return;
        y = 0x00;
        setLoadFlag(y);
    } while (flgZ);
    SUB_014723();
    return;
}

void game::SUB_014723() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014729;
    }
    popAddress();
    return;
L_014729:
    SUB_0146B5();
    return;
}

void game::SUB_014787() {
    pushAddress(0x8789);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x8789)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x878F);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x878F)) return;
    SUB_01479A();
    return;
}

void game::SUB_01479A() {
    y = 0x00;
    opCMP(myMapper->readCPU(0x0354), myMapper->readCPU(0x0354 + x));
    if (flgC) {
        goto L_0147A5;
    }
    opINY(1);
L_0147A5:
    myMapper->writeCPU(0x04DC + x, y);
    popAddress();
}

void game::SUB_0147AA() {
    a = myMapper->readCPU(0x054C + x);
    setLoadFlag(a);
    if (flgZ) {
        SUB_0147B5();
        return;
    }
    opDEC(0x054C + x, 1);
    SUB_01EE94();
    return;
}

void game::SUB_0147B5() {
    a = 0x13;
    pushAddress(0x87B9);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x87B9)) return;
    pushAddress(0x87BC);
    SUB_01479A();
    if (handleReturnAddress(poppedEntry.value, 0x87BC)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x03C4 + x, myMapper->readCPU(0x87E3 + y));
    a = myMapper->readCPU(0x87E4 + y);
    myMapper->writeCPU(0x03E0 + x, a);
    pushAddress(0x87D1);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x87D1)) return;
    myMapper->writeCPU(0x04F8 + x, y);
    y = 0xC0;
    a = 0x00;
    pushAddress(0x87DC);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x87DC)) return;
    myMapper->writeCPU(0x046C + x, 0x01);
    popAddress();
}

void game::SUB_0147EB() {
    y = myMapper->readCPU(0x04DC + x);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_0147F3;
    }
    SUB_01EF43();
    return;
L_0147F3:
    SUB_01EF56();
    return;
}

void game::SUB_0147F6() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x08);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    if (flgN) {
        goto L_01480E;
    }
    pushAddress(0x880A);
    SUB_0147EB();
    if (handleReturnAddress(poppedEntry.value, 0x880A)) return;
    SUB_01EE1C();
    return;
L_01480E:
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x881B + y);
    y = 0x02;
    SUB_01ED34();
    return;
}

void game::SUB_01481F() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_014825();
        return;
    }
    SUB_014824();
    return;
}

void game::SUB_014824() {
    popAddress();
}

void game::SUB_014825() {
    a = myMapper->readCPU(0x0354);
    opSBC(myMapper->readCPU(0x0354 + x));
    if (!flgC) {
        opEOR(0xFF);
    }
    opCMP(a, 0x20);
    if (!flgC) {
        goto L_014836;
    }
    SUB_0147B5();
    return;
L_014836:
    pushAddress(0x8838);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x8838)) return;
    myMapper->writeCPU(0x04F8 + x, y);
    a = 0x00;
    y = 0x40;
    pushAddress(0x8843);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8843)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x01);
    y = a;
    a = myMapper->readCPU(0x8851 + y);
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_014853() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0147B5();
        return;
    }
    a = myMapper->readCPU(0x0418 + x);
    opADC(0x08);
    myMapper->writeCPU(0x0418 + x, a);
    a = myMapper->readCPU(0x03FC + x);
    opADC(0x00);
    myMapper->writeCPU(0x03FC + x, a);
    pushAddress(0x886D);
    SUB_01EE1C();
    if (handleReturnAddress(poppedEntry.value, 0x886D)) return;
    a = 0x08;
    y = myMapper->readCPU(0x04F8 + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_014880;
    }
    opEOR(0xFF);
    opADC(myMapper->readCPU(0x038C));
    if (a >= myMapper->readCPU(0x038C + x)) {
        goto L_014888;
    }
    popAddress();
    return;
L_014880:
    opADC(myMapper->readCPU(0x038C));
    if (a >= myMapper->readCPU(0x038C + x)) {
        jump(0x8824);
        return;
    }
L_014888:
    pushAddress(0x888A);
    SUB_01479A();
    if (handleReturnAddress(poppedEntry.value, 0x888A)) return;
    a = 0x00;
    y = 0x80;
    pushAddress(0x8891);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8891)) return;
    a = 0x79;
    y = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014899() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        goto L_0148A1;
    }
    SUB_0147B5();
    return;
L_0148A1:
    pushAddress(0x88A3);
    SUB_0147EB();
    if (handleReturnAddress(poppedEntry.value, 0x88A3)) return;
    a = myMapper->readCPU(0x0418 + x);
    opSBC(0x08);
    myMapper->writeCPU(0x0418 + x, a);
    a = myMapper->readCPU(0x03FC + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03FC + x, a);
    SUB_01EE1C();
    return;
}

void game::SUB_0148B7() {
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x0008, 0x03);
    y = 0x04;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_0148CA;
        }
    L_0148C4:
        opINY(1);
        opCMP(y, 0x0C);
    } while (!flgC);
    popAddress();
    return;
L_0148CA:
    myMapper->writeCPU(0x0016, 0x25);
    a = 0x50;
    pushAddress(0x88D2);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x88D2)) return;
    myMapper->writeCPU(0x0450 + y, 0x00);
    a = myMapper->readCPU(0x0008);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x03FC + y, myMapper->readCPU(0x8900 + x));
    myMapper->writeCPU(0x0418 + y, myMapper->readCPU(0x8901 + x));
    myMapper->writeCPU(0x03C4 + y, myMapper->readCPU(0x8908 + x));
    myMapper->writeCPU(0x03E0 + y, myMapper->readCPU(0x8909 + x));
    myMapper->writeCPU(0x054C + x, 0x10);
    opDEC(0x0008, 1);
    if (!flgZ) {
        goto L_0148C4;
    }
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_014910() {
    myMapper->writeCPU(0x004C, 0x08);
    myMapper->writeCPU(0x004E, x);
    y = 0x0C;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_014922;
        }
        opINY(1);
        opCMP(y, 0x0E);
    } while (!flgC);
L_014922:
    myMapper->writeCPU(0x0016, 0x26);
    a = 0x08;
    pushAddress(0x892A);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x892A)) return;
    a = myMapper->readCPU(0x0354 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x004C));
    myMapper->writeCPU(0x0354 + y, a);
    myMapper->writeCPU(0x0418 + y, 0xC0);
    myMapper->writeCPU(0x03FC + y, 0x01);
    popAddress();
}

void game::SUB_01493F() {
    if (myMapper->readCPU(0x0568 + x) == 0) {
        goto L_014956;
    }
    y = 0x00;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_01494E;
    }
    y = 0x82;
L_01494E:
    myMapper->writeCPU(0x031C + x, y);
    opDEC(0x0568 + x, 1);
    popAddress();
    return;
L_014956:
    a = myMapper->readCPU(0x0488 + x);
    opAND(0x7F);
    myMapper->writeCPU(0x0488 + x, a);
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8963);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8963)) return;
    SUB_01496C();
    return;
}

void game::SUB_01496C() {
    pushAddress(0x896E);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x896E)) return;
    pushAddress(0x8971);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0x8971)) return;
    y = 0x80;
    a = 0x01;
    SUB_01EC72();
    return;
}

void game::SUB_014979() {
    pushAddress(0x897B);
    SUB_01F06D();
    if (handleReturnAddress(poppedEntry.value, 0x897B)) return;
    pushAddress(0x897E);
    SUB_014998();
    if (handleReturnAddress(poppedEntry.value, 0x897E)) return;
    if (!(myMapper->readCPU(0x03C4 + x) & 0x80)) {
        goto L_014991;
    }
    a = 0x3E;
    pushAddress(0x8988);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8988)) return;
    pushAddress(0x898B);
    SUB_01EC88();
    if (handleReturnAddress(poppedEntry.value, 0x898B)) return;
    myMapper->writeCPU(0x046C + x, 0x02);
L_014991:
    popAddress();
}

void game::SUB_014992() {
    pushAddress(0x8994);
    SUB_01F06D();
    if (handleReturnAddress(poppedEntry.value, 0x8994)) return;
    SUB_014998();
    return;
}

void game::SUB_014998() {
    a = myMapper->readCPU(0x038C + x);
    opCMP(a, 0x09);
    if (flgC) {
        goto L_0149A3;
    }
    a = 0x09;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0149A9;
    }
L_0149A3:
    opCMP(a, 0xF7);
    if (!flgC) {
        SUB_0149AF();
        return;
    }
    a = 0xF7;
L_0149A9:
    myMapper->writeCPU(0x038C + x, a);
    pushAddress(0x89AE);
    SUB_01EAA9();
    if (handleReturnAddress(poppedEntry.value, 0x89AE)) return;
    SUB_0149AF();
    return;
}

void game::SUB_0149AF() {
    opCMP(myMapper->readCPU(0x0354 + x), 0x30);
    if (flgC) {
        goto L_0149BE;
    }
    a = 0x30;
    myMapper->writeCPU(0x0354 + x, a);
    pushAddress(0x89BD);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0x89BD)) return;
L_0149BE:
    popAddress();
}

void game::SUB_0149BF() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_0149AF();
        return;
    }
    myMapper->writeCPU(0x046C + x, 0x01);
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x03C4 + x, myMapper->readCPU(0x89DE + y));
    myMapper->writeCPU(0x03E0 + x, 0x00);
    a = 0x3D;
    SUB_01EF04();
    return;
}

void game::SUB_0149E2() {
    pushAddress(0x89E4);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x89E4)) return;
    pushAddress(0x89E7);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x89E7)) return;
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0x89EF);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x89EF)) return;
    SUB_0149F8();
    return;
}

void game::SUB_0149F8() {
    if (myMapper->readCPU(0x0048) != 0) {
        goto L_0149FD;
    }
    popAddress();
    return;
L_0149FD:
    y = 0x81;
    a = 0x78;
    SUB_01ED34();
    return;
}

void game::SUB_014A04() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014A0A;
    }
    popAddress();
    return;
L_014A0A:
    y = 0xC0;
    a = 0x00;
    pushAddress(0x8A10);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8A10)) return;
    a = myMapper->readCPU(0x001A);
    opAND(0x03);
    myMapper->writeCPU(0x0055, a);
    y = 0x02;
    a = 0x3C;
    SUB_01ED34();
    return;
}

void game::SUB_014A1E() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014A2C;
    }
    a = myMapper->readCPU(0x038C + x);
    myMapper->writeCPU(0x0394, a);
    SUB_01EE48();
    return;
L_014A2C:
    a = 0x01;
    myMapper->writeCPU(0x0474, a);
    SUB_014A31();
    return;
}

void game::SUB_014A31() {
    y = myMapper->readCPU(0x0450 + x);
    pushAddress(0x8A36);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x8A36)) return;
    opCMP(a, 0x50);
    if (flgC) {
        goto L_014A41;
    }
    a = y;
    opEOR(0x01);
    goto L_014A42;
L_014A41:
    a = y;
L_014A42:
    myMapper->writeCPU(0x04F8 + x, a);
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x8A52 + y);
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_014A56() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_014A31();
        return;
    }
    pushAddress(0x8A5D);
    SUB_01EE1C();
    if (handleReturnAddress(poppedEntry.value, 0x8A5D)) return;
    a = myMapper->readCPU(0x038C + x);
    if (a < 0x10) {
        goto L_014A69;
    }
    if (a < 0xF0) {
        goto L_014A71;
    }
L_014A69:
    a = myMapper->readCPU(0x04F8 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x04F8 + x, a);
L_014A71:
    popAddress();
}

void game::SUB_014A72() {
    a = myMapper->readCPU(0x0514 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x0514 + x, a);
    a = myMapper->readCPU(0x04F8 + x);
    opSBC(myMapper->readCPU(0x03C4 + x));
    SUB_014AA2();
    return;
}

void game::SUB_014A85() {
    y = x;
    opINY(1);
    myMapper->writeCPU(0x004F, y);
    y = myMapper->readCPU(0x04DC + x);
    setLoadFlag(y);
    if (flgZ) {
        SUB_014ACD();
        return;
    }
    opDEY(1);
    if (flgZ) {
        SUB_014A72();
        return;
    }
    a = myMapper->readCPU(0x0514 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x0514 + x, a);
    a = myMapper->readCPU(0x04F8 + x);
    opADC(myMapper->readCPU(0x03C4 + x));
    SUB_014AA2();
    return;
}

void game::SUB_014AA2() {
    if (flgN) {
        goto L_014AAC;
    }
    if (a < 0x08) {
        goto L_014ACA;
    }
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_014AB2;
    }
L_014AAC:
    if (a >= 0xF9) {
        goto L_014ACA;
    }
    a = 0xF8;
L_014AB2:
    myMapper->writeCPU(0x04F8 + x, a);
    a = myMapper->readCPU(0x04DC + x);
    y = myMapper->readCPU(0x004F);
    myMapper->writeCPU(0x04DC + y, a);
    myMapper->writeCPU(0x03C4 + y, 0x01);
    a = 0xC0;
    myMapper->writeCPU(0x03E0 + y, a);
    SUB_014ACD();
    return;
L_014ACA:
    myMapper->writeCPU(0x04F8 + x, a);
    SUB_014ACD();
    return;
}

void game::SUB_014ACD() {
    y = myMapper->readCPU(0x004F);
    a = myMapper->readCPU(0x0354 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x04F8 + x));
    myMapper->writeCPU(0x0354 + x, a);
    popAddress();
}

void game::SUB_014ADA() {
    a = myMapper->readCPU(0x0560);
    setLoadFlag(a);
    if (flgZ) {
        goto L_014AE2;
    }
    SUB_014B08();
    return;
L_014AE2:
    pushAddress(0x8AE4);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x8AE4)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8AEA);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8AEA)) return;
    SUB_014AF7();
    return;
}

void game::SUB_014AF7() {
    a = x;
    flgC = true;
    opSBC(0x04);
    y = a;
    myMapper->writeCPU(0x004B, myMapper->readCPU(0x8B02 + y));
    popAddress();
}

void game::SUB_014B08() {
    a = myMapper->readCPU(0x0396);
    flgC = true;
    opSBC(myMapper->readCPU(0x0530 + x));
    myMapper->writeCPU(0x038C + x, a);
    a = myMapper->readCPU(0x030A);
    opAND(0x7F);
    opSBC(0x00);
    myMapper->writeCPU(0x0300 + x, a);
    pushAddress(0x8B1E);
    SUB_01DD40();
    if (handleReturnAddress(poppedEntry.value, 0x8B1E)) return;
    SUB_014C95();
    return;
}

void game::SUB_014B22() {
    pushAddress(0x8B24);
    SUB_014AF7();
    if (handleReturnAddress(poppedEntry.value, 0x8B24)) return;
    a = myMapper->readCPU(0x0530 + x);
    flgC = false;
    opADC(0x01);
    opCMP(a, myMapper->readCPU(0x004B));
    if (flgC) {
        goto L_014B35;
    }
    while (true) {
        myMapper->writeCPU(0x0530 + x, a);
        SUB_014B08();
        return;
    L_014B35:
        a = 0x08;
        y = 0x02;
        pushAddress(0x8B3B);
        SUB_01ED34();
        if (handleReturnAddress(poppedEntry.value, 0x8B3B)) return;
        a = myMapper->readCPU(0x004B);
    }
    SUB_014B41();
    return;
}

void game::SUB_014B41() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_014B08();
        return;
    }
    myMapper->writeCPU(0x04DC + x, 0x02);
    myMapper->writeCPU(0x03C4 + x, 0x01);
    myMapper->writeCPU(0x03E0 + x, 0xC0);
    a = 0x38;
    y = 0x03;
    pushAddress(0x8B5B);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x8B5B)) return;
    SUB_014B08();
    return;
}

void game::SUB_014B5F() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_014B70();
        return;
    }
    SUB_014B64();
    return;
}

void game::SUB_014B64() {
    a = myMapper->readCPU(0x001A);
    opAND(0x1F);
    if (flgZ) {
        SUB_014B97();
        return;
    }
    opCMP(a, 0x08);
    if (flgZ) {
        SUB_014B82();
        return;
    }
    if (!flgZ) {
        SUB_014B91();
        return;
    }
    SUB_014B70();
    return;
}

void game::SUB_014B70() {
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x054C + x, myMapper->readCPU(0x8BB3 + y));
    a = myMapper->readCPU(0x04DC + x);
    opEOR(0x03);
    if (!flgZ) {
        SUB_014B8E();
        return;
    }
    SUB_014B82();
    return;
}

void game::SUB_014B82() {
    y = 0x02;
    if (myMapper->readCPU(0x0354) >= myMapper->readCPU(0x0354 + x)) {
        goto L_014B8D;
    }
    opDEY(1);
L_014B8D:
    a = y;
    SUB_014B8E();
    return;
}

void game::SUB_014B8E() {
    myMapper->writeCPU(0x04DC + x, a);
    SUB_014B91();
    return;
}

void game::SUB_014B91() {
    pushAddress(0x8B93);
    SUB_014A85();
    if (handleReturnAddress(poppedEntry.value, 0x8B93)) return;
    SUB_014B08();
    return;
}

void game::SUB_014B97() {
    a = myMapper->readCPU(0x046C + x);
    opCMP(a, 0x03);
    if (!flgZ) {
        SUB_014B91();
        return;
    }
    a = myMapper->readCPU(0x006F);
    opAND(0x01);
    if (!flgZ) {
        SUB_014B91();
        return;
    }
    a = 0x2D;
    pushAddress(0x8BA8);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8BA8)) return;
    a = 0x10;
    y = 0x04;
    pushAddress(0x8BAF);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x8BAF)) return;
    SUB_014B91();
    return;
}

void game::SUB_014BB7() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_014B64();
        return;
    }
    if (myMapper->readCPU(0x0300 + x) == 0) {
        opCMP(myMapper->readCPU(0x038C), myMapper->readCPU(0x038C + x));
        if (!flgC) {
            a = myMapper->readCPU(0x0354);
            opSBC(myMapper->readCPU(0x0354 + x));
            if (!flgC) {
                opEOR(0xFF);
            }
            opCMP(a, 0x28);
            if (flgC) {
                goto L_014BDA;
            }
            pushAddress(0x8BD9);
            SUB_01EC88();
            if (handleReturnAddress(poppedEntry.value, 0x8BD9)) return;
        }
    }
L_014BDA:
    y = 0x05;
    a = 0x10;
    pushAddress(0x8BE0);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x8BE0)) return;
    SUB_014B64();
    return;
}

void game::SUB_014BE4() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014BEC;
    }
    SUB_014B64();
    return;
L_014BEC:
    a = 0x5A;
    pushAddress(0x8BF0);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8BF0)) return;
    a = 0x03;
    myMapper->writeCPU(0x046C + x, a);
    SUB_014B70();
    return;
}

void game::SUB_014BF9() {
    a = myMapper->readCPU(0x0560);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_014C03;
    }
    a = myMapper->readCPU(0x056C);
    setLoadFlag(a);
    if (flgZ) {
        goto L_014C06;
    }
L_014C03:
    SUB_014B08();
    return;
L_014C06:
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8C0B);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8C0B)) return;
    SUB_014C12();
    return;
}

void game::SUB_014C12() {
    pushAddress(0x8C14);
    SUB_014AF7();
    if (handleReturnAddress(poppedEntry.value, 0x8C14)) return;
    a = myMapper->readCPU(0x0530 + x);
    flgC = false;
    opADC(0x01);
    if (a >= myMapper->readCPU(0x004B)) {
        goto L_014C25;
    }
    while (true) {
        myMapper->writeCPU(0x0530 + x, a);
        SUB_014B08();
        return;
    L_014C25:
        myMapper->writeCPU(0x046C + x, 0x02);
        a = myMapper->readCPU(0x004B);
    }
    SUB_014C2F();
    return;
}

void game::SUB_014C2F() {
    pushAddress(0x8C31);
    SUB_014C38();
    if (handleReturnAddress(poppedEntry.value, 0x8C31)) return;
    pushAddress(0x8C34);
    SUB_014A85();
    if (handleReturnAddress(poppedEntry.value, 0x8C34)) return;
    SUB_014B08();
    return;
}

void game::SUB_014C38() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x20);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    if (!flgN) {
        goto L_014C50;
    }
    pushAddress(0x8C4C);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0x8C4C)) return;
    myMapper->writeCPU(0x04DC + x, a);
L_014C50:
    popAddress();
}

void game::SUB_014C51() {
    a = myMapper->readCPU(0x0560);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x046C + x);
        setLoadFlag(a);
        if (flgZ) {
            opDEC(0x054C + x, 1);
            if (!flgZ) {
                goto L_014C74;
            }
            y = 0x04;
            a = 0x01;
            do {
                myMapper->writeCPU(0x046C + y, a);
                opINY(1);
            } while (y < 0x0A);
            a = 0x01;
            myMapper->writeCPU(0x046C + x, a);
        }
    }
L_014C74:
    pushAddress(0x8C76);
    SUB_01DD3D();
    if (handleReturnAddress(poppedEntry.value, 0x8C76)) return;
    a = myMapper->readCPU(0x0300 + x);
    if (a != 0x01) {
        jump(0x8C95);
        return;
    }
    a = myMapper->readCPU(0x038C + x);
    if (a < 0x70) {
        jump(0x8C95);
        return;
    }
    if (a >= 0x90) {
        jump(0x8C95);
        return;
    }
    y = 0x04;
    do {
        a = 0x32;
        myMapper->writeCPU(0x0434 + y, a);
        opINY(1);
    } while (y < 0x0B);
    SUB_014C95();
    return;
}

void game::SUB_014C95() {
    opPLA();
    opPLA();
	callStack.pop_back();
    SUB_01EA77();
    return;
}

void game::SUB_014C9A() {
    pushAddress(0x8C9C);
    SUB_01EF69();
    if (handleReturnAddress(poppedEntry.value, 0x8C9C)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8CA2);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8CA2)) return;
    SUB_014CB1();
    return;
}

void game::SUB_014CB1() {
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x0450 + x);
    }
    else {
        pushAddress(0x8CC0);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0x8CC0)) return;
        y = myMapper->readCPU(0x0450 + x);
        opCMP(a, 0x48);
        if (!flgC) {
            goto L_014CCC;
        }
        a = y;
        goto L_014CCF;
    L_014CCC:
        a = y;
        opEOR(0x01);
    }
L_014CCF:
    myMapper->writeCPU(0x04F8 + x, a);
    popAddress();
}

void game::SUB_014CD3() {
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x04DC + x, myMapper->readCPU(0x8CEC + y));
    y = 0x80;
    a = 0x01;
    pushAddress(0x8CE4);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8CE4)) return;
    y = 0x01;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014CF0() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opDEC(0x04DC + x, 1);
    if (flgZ) {
        goto L_014D05;
    }
    pushAddress(0x8CFD);
    SUB_014CB1();
    if (handleReturnAddress(poppedEntry.value, 0x8CFD)) return;
    y = 0x02;
    a = 0x10;
    SUB_01ED34();
    return;
L_014D05:
    y = 0x03;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014D0C() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_014D43;
    }
    pushAddress(0x8D13);
    SUB_01EE6F();
    if (handleReturnAddress(poppedEntry.value, 0x8D13)) return;
    myMapper->writeCPU(0x004D, myMapper->readCPU(0x0354 + x));
    a = 0x0C;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x8D1F);
    SUB_01EC1A();
    if (handleReturnAddress(poppedEntry.value, 0x8D1F)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        goto L_014D28;
    }
    pushAddress(0x8D26);
    SUB_0150EF();
    if (handleReturnAddress(poppedEntry.value, 0x8D26)) return;
    do {
        popAddress();
        return;
    L_014D28:
        pushAddress(0x8D2A);
        SUB_01EF9C();
        if (handleReturnAddress(poppedEntry.value, 0x8D2A)) return;
    } while (myMapper->readCPU(0x0014) != 0);
    y = 0x40;
    a = 0x01;
    pushAddress(0x8D35);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8D35)) return;
    a = 0x02;
    y = 0x80;
    pushAddress(0x8D3C);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x8D3C)) return;
    myMapper->writeCPU(0x046C + x, 0x05);
    popAddress();
    return;
L_014D43:
    y = 0x01;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014D4A() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_014D58;
    }
    pushAddress(0x8D57);
    SUB_01ED5C();
    if (handleReturnAddress(poppedEntry.value, 0x8D57)) return;
L_014D58:
    a = 0x08;
    y = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_014D5F() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_014D65();
        return;
    }
    popAddress();
}

void game::SUB_014D65() {
    myMapper->writeCPU(0x046C + x, 0x00);
    popAddress();
}

void game::SUB_014D6B() {
    pushAddress(0x8D6D);
    SUB_01EE6F();
    if (handleReturnAddress(poppedEntry.value, 0x8D6D)) return;
    pushAddress(0x8D70);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0x8D70)) return;
    pushAddress(0x8D73);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0x8D73)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        goto L_014D85;
    }
    a = myMapper->readCPU(0x0354 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0354 + x, a);
    myMapper->writeCPU(0x046C + x, 0x06);
L_014D85:
    popAddress();
}

void game::SUB_014D86() {
    myMapper->writeCPU(0x004E, x);
    y = 0x0D;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_014D95;
        }
        opDEY(1);
        opCMP(y, 0x07);
    } while (flgC);
    popAddress();
    return;
L_014D95:
    myMapper->writeCPU(0x0016, 0x27);
    a = 0x16;
    pushAddress(0x8D9D);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x8D9D)) return;
    x = 0xF4;
    a = myMapper->readCPU(0x006F);
    opAND(0x01);
    if (flgZ) {
        goto L_014DA8;
    }
    x = 0x08;
L_014DA8:
    a = x;
    x = myMapper->readCPU(0x004E);
    flgC = false;
    opADC(myMapper->readCPU(0x0354 + x));
    myMapper->writeCPU(0x0354 + y, a);
    myMapper->writeCPU(0x04DC + y, x);
    myMapper->writeCPU(0x054C + y, 0x58);
    myMapper->writeCPU(0x03FC + y, 0x01);
    myMapper->writeCPU(0x0418 + y, 0x40);
    popAddress();
}

void game::SUB_014DC6() {
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opDEY(1);
        if (flgZ) {
            goto L_014DE2;
        }
        opDEY(1);
        if (flgZ) {
            goto L_014E08;
        }
    }
    else {
        opDEC(0x054C + x, 1);
        if (!flgZ) {
            SUB_01EE48();
            return;
        }
        myMapper->writeCPU(0x046C + x, 0x01);
        popAddress();
        return;
    L_014DE2:
        a = myMapper->readCPU(0x0418 + x);
        opSBC(0x20);
        myMapper->writeCPU(0x0418 + x, a);
        a = myMapper->readCPU(0x03FC + x);
        opSBC(0x00);
        myMapper->writeCPU(0x03FC + x, a);
        if (!flgN) {
            SUB_01EE48();
            return;
        }
        pushAddress(0x8DF9);
        SUB_01EAA9();
        if (handleReturnAddress(poppedEntry.value, 0x8DF9)) return;
        a = 0x00;
        myMapper->writeCPU(0x0418 + x, a);
        myMapper->writeCPU(0x03FC + x, a);
        myMapper->writeCPU(0x046C + x, 0x02);
        popAddress();
        return;
    L_014E08:
        a = myMapper->readCPU(0x0418 + x);
        opADC(0x20);
        myMapper->writeCPU(0x0418 + x, a);
        a = myMapper->readCPU(0x03FC + x);
        opADC(0x00);
        myMapper->writeCPU(0x03FC + x, a);
        pushAddress(0x8E1A);
        SUB_01EE48();
        if (handleReturnAddress(poppedEntry.value, 0x8E1A)) return;
        if (myMapper->readCPU(0x03FC + x) != 0x01) {
            goto L_014E5C;
        }
        opCMP(myMapper->readCPU(0x0418 + x), 0x40);
        if (!flgC) {
            goto L_014E5C;
        }
        myMapper->writeCPU(0x046C + x, 0x03);
        a = 0x01;
        y = 0x40;
        SUB_01EC72();
        return;
    }
    pushAddress(0x8E37);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0x8E37)) return;
    y = myMapper->readCPU(0x04DC + x);
    a = myMapper->readCPU(0x0354 + x);
    opSBC(myMapper->readCPU(0x0354 + y));
    if (!flgC) {
        opEOR(0xFF);
    }
    opCMP(a, 0x10);
    if (!flgC) {
        a = myMapper->readCPU(0x038C + x);
        opSBC(myMapper->readCPU(0x038C + y));
        if (!flgC) {
            opEOR(0xFF);
        }
        if (a >= 0x10) {
            goto L_014E5C;
        }
        myMapper->writeCPU(0x0434 + x, 0x32);
    }
L_014E5C:
    popAddress();
}

void game::SUB_014EB8() {
    pushAddress(0x8EBA);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x8EBA)) return;
    pushAddress(0x8EBD);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x8EBD)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8EC3);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8EC3)) return;
    SUB_014ECE();
    return;
}

void game::SUB_014ECE() {
    if (myMapper->readCPU(0x0048) != 0) {
        goto L_014ED3;
    }
    popAddress();
    return;
L_014ED3:
    y = 0x81;
    a = 0x78;
    SUB_01ED34();
    return;
}

void game::SUB_014EDA() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_014EF0();
        return;
    }
    a = 0x58;
    pushAddress(0x8EE3);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x8EE3)) return;
    a = 0x02;
    y = 0x80;
    pushAddress(0x8EEA);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x8EEA)) return;
    myMapper->writeCPU(0x046C + x, 0x02);
    SUB_014EF0();
    return;
}

void game::SUB_014EF0() {
    popAddress();
}

void game::SUB_014EF1() {
    a = myMapper->readCPU(0x03E0 + x);
    flgC = true;
    opSBC(0x05);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    pushAddress(0x8F04);
    SUB_01EF43();
    if (handleReturnAddress(poppedEntry.value, 0x8F04)) return;
    pushAddress(0x8F07);
    SUB_014F72();
    if (handleReturnAddress(poppedEntry.value, 0x8F07)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        SUB_014EF0();
        return;
    }
    pushAddress(0x8F0E);
    SUB_01EFAF();
    if (handleReturnAddress(poppedEntry.value, 0x8F0E)) return;
    SUB_014F0F();
    return;
}

void game::SUB_014F0F() {
    pushAddress(0x8F11);
    SUB_01505B();
    if (handleReturnAddress(poppedEntry.value, 0x8F11)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x8F1F + y);
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_014F23() {
    a = myMapper->readCPU(0x001A);
    opAND(0x1F);
    if (flgZ) {
        goto L_014F52;
    }
    do {
        opDEC(0x054C + x, 1);
        if (flgZ) {
            y = 0x01;
            a = myMapper->readCPU(0x006F);
            opAND(0x01);
            if (flgZ) {
                goto L_014F38;
            }
            y = 0x02;
        L_014F38:
            a = y;
            y = 0x00;
            pushAddress(0x8F3D);
            SUB_01ECEA();
            if (handleReturnAddress(poppedEntry.value, 0x8F3D)) return;
            a = myMapper->readCPU(0x001A);
            opAND(0x01);
            myMapper->writeCPU(0x04F8 + x, a);
            a = 0x00;
            y = 0xC0;
            pushAddress(0x8F4B);
            SUB_01EC72();
            if (handleReturnAddress(poppedEntry.value, 0x8F4B)) return;
            myMapper->writeCPU(0x046C + x, 0x04);
        }
        popAddress();
        return;
    L_014F52:
        pushAddress(0x8F54);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0x8F54)) return;
        opCMP(a, 0x48);
    } while (flgC);
    myMapper->writeCPU(0x04F8 + x, myMapper->readCPU(0x0450 + x));
    a = 0x01;
    y = 0x40;
    pushAddress(0x8F65);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8F65)) return;
    myMapper->writeCPU(0x046C + x, 0x04);
    a = 0x02;
    y = 0x00;
    SUB_01ECEA();
    return;
}

void game::SUB_014F72() {
    a = myMapper->readCPU(0x0354 + x);
    opADC(0x18);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    SUB_01EC21();
    return;
}

void game::SUB_014F80() {
    pushAddress(0x8F82);
    SUB_01EE1C();
    if (handleReturnAddress(poppedEntry.value, 0x8F82)) return;
    a = myMapper->readCPU(0x038C + x);
    opCMP(a, 0xF0);
    if (!flgC) {
        opCMP(a, 0x10);
        if (flgC) {
            goto L_014F9A;
        }
        a = 0x10;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_014F94;
        }
    }
    a = 0xF0;
L_014F94:
    myMapper->writeCPU(0x038C + x, a);
    pushAddress(0x8F99);
    SUB_0150EF();
    if (handleReturnAddress(poppedEntry.value, 0x8F99)) return;
L_014F9A:
    pushAddress(0x8F9C);
    SUB_014FBD();
    if (handleReturnAddress(poppedEntry.value, 0x8F9C)) return;
    a = myMapper->readCPU(0x0354 + x);
    opCMP(a, 0x20);
    if (!flgC) {
        a = 0x21;
        myMapper->writeCPU(0x0354 + x, a);
        pushAddress(0x8FAB);
        SUB_01F1D2();
        if (handleReturnAddress(poppedEntry.value, 0x8FAB)) return;
    }
    else {
        pushAddress(0x8FB1);
        SUB_014F72();
        if (handleReturnAddress(poppedEntry.value, 0x8FB1)) return;
        a = myMapper->readCPU(0x0014);
        setLoadFlag(a);
        if (flgZ) {
            goto L_014FBC;
        }
        pushAddress(0x8FB8);
        SUB_01EFAF();
        if (handleReturnAddress(poppedEntry.value, 0x8FB8)) return;
        SUB_014F0F();
        return;
    }
L_014FBC:
    popAddress();
}

void game::SUB_014FBD() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x06);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    SUB_01EF56();
    return;
}

void game::SUB_014FD0() {
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x8FD5);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x8FD5)) return;
    SUB_014FDE();
    return;
}

void game::SUB_014FDE() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        myMapper->writeCPU(0x0300 + x, 0x00);
        myMapper->writeCPU(0x046C + x, 0x01);
        popAddress();
        return;
    }
    y = 0x00;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_014FF8;
    }
    y = 0x80;
L_014FF8:
    myMapper->writeCPU(0x0300 + x, y);
    SUB_014FFC();
    return;
}

void game::SUB_014FFC() {
    popAddress();
}

void game::SUB_014FFD() {
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x038C));
    a = myMapper->readCPU(0x0354);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x9009);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0x9009)) return;
    x = myMapper->readCPU(0x004E);
    if (myMapper->readCPU(0x0009) != 0) {
        goto L_015021;
    }
    a = 0x00;
    y = 0xE0;
    pushAddress(0x9016);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x9016)) return;
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0001);
    pushAddress(0x901D);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x901D)) return;
    goto L_01502F;
L_015021:
    a = 0x00;
    y = 0xE0;
    pushAddress(0x9027);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0x9027)) return;
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0001);
    pushAddress(0x902E);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x902E)) return;
L_01502F:
    a = 0x78;
    y = 0x02;
    SUB_01ED34();
    return;
}

void game::SUB_015036() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        a = myMapper->readCPU(0x04DC + x);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_015046;
        }
        pushAddress(0x9042);
        SUB_01EF43();
        if (handleReturnAddress(poppedEntry.value, 0x9042)) return;
        goto L_015049;
    L_015046:
        pushAddress(0x9048);
        SUB_01EF56();
        if (handleReturnAddress(poppedEntry.value, 0x9048)) return;
    L_015049:
        SUB_01EE48();
        return;
    }
    a = 0x20;
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_015053() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_014FFC();
        return;
    }
    SUB_014FFD();
    return;
}

void game::SUB_01505B() {
    myMapper->writeCPU(0x004E, x);
    a = 0x03;
    if (myMapper->readCPU(0x002B) == 0) {
        goto L_015065;
    }
    a = 0x04;
L_015065:
    myMapper->writeCPU(0x004B, a);
    y = 0x0D;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_015074;
        }
    L_01506E:
        opDEY(1);
        opCMP(y, 0x0A);
    } while (flgC);
    popAddress();
    return;
L_015074:
    myMapper->writeCPU(0x054C + x, 0x28);
    x = myMapper->readCPU(0x004B);
    a = myMapper->readCPU(0x038C);
    opADC(myMapper->readCPU(0x90A0 + x));
    myMapper->writeCPU(0x038C + y, a);
    a = myMapper->readCPU(0x0354);
    opADC(myMapper->readCPU(0x90A5 + x));
    myMapper->writeCPU(0x0354 + y, a);
    x = y;
    a = 0x0B;
    pushAddress(0x9093);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x9093)) return;
    a = 0x59;
    pushAddress(0x9098);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9098)) return;
    opDEC(0x004B, 1);
    if (!flgZ) {
        goto L_01506E;
    }
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_0150AA() {
    pushAddress(0x90AC);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x90AC)) return;
    pushAddress(0x90AF);
    SUB_01EF69();
    if (handleReturnAddress(poppedEntry.value, 0x90AF)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x90B5);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x90B5)) return;
    SUB_0150BE();
    return;
}

void game::SUB_0150BE() {
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x90EB + y);
    myMapper->writeCPU(0x04DC + x, a);
    SUB_0150C9();
    return;
}

void game::SUB_0150C9() {
    y = myMapper->readCPU(0x0450 + x);
    pushAddress(0x90CE);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x90CE)) return;
    opCMP(a, 0x50);
    if (flgC) {
        goto L_0150D9;
    }
    a = y;
    opEOR(0x01);
    goto L_0150DA;
L_0150D9:
    a = y;
L_0150DA:
    myMapper->writeCPU(0x04F8 + x, a);
    a = 0x00;
    y = 0xA0;
    pushAddress(0x90E3);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x90E3)) return;
    a = 0x10;
    y = 0x01;
    SUB_01ED34();
    return;
}

void game::SUB_0150EF() {
    a = myMapper->readCPU(0x04F8 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x04F8 + x, a);
    popAddress();
}

void game::SUB_0150F8() {
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x01);
    if (flgZ) {
        opDEC(0x054C + x, 1);
        if (!flgZ) {
            myMapper->writeCPU(0x004D, myMapper->readCPU(0x0354 + x));
            a = 0x0C;
            myMapper->writeCPU(0x004C, a);
            pushAddress(0x910F);
            SUB_01EC1A();
            if (handleReturnAddress(poppedEntry.value, 0x910F)) return;
            a = myMapper->readCPU(0x0014);
            setLoadFlag(a);
            if (!flgZ) {
                if (!flgZ) {
                    goto L_015129;
                }
            }
            a = myMapper->readCPU(0x0354 + x);
            flgC = false;
            opADC(0x10);
            myMapper->writeCPU(0x004D, a);
            a = 0x04;
            myMapper->writeCPU(0x004C, a);
            pushAddress(0x9124);
            SUB_01EC1A();
            if (handleReturnAddress(poppedEntry.value, 0x9124)) return;
            a = myMapper->readCPU(0x0014);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_01512C;
            }
        L_015129:
            pushAddress(0x912B);
            SUB_0150EF();
            if (handleReturnAddress(poppedEntry.value, 0x912B)) return;
        L_01512C:
            SUB_01EE6F();
            return;
        }
        opDEC(0x04DC + x, 1);
        if (flgZ) {
            goto L_01513B;
        }
    }
    a = 0x04;
    y = 0x02;
    SUB_01ED34();
    return;
L_01513B:
    a = 0x10;
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_015142() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_015157();
        return;
    }
    SUB_0150C9();
    return;
}

void game::SUB_01514A() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_015157();
        return;
    }
    pushAddress(0x9151);
    SUB_014D86();
    if (handleReturnAddress(poppedEntry.value, 0x9151)) return;
    myMapper->writeCPU(0x046C + x, 0x00);
    SUB_015157();
    return;
}

void game::SUB_015157() {
    popAddress();
}

void game::SUB_015158() {
    opDEC(0x0568 + x, 1);
    if (flgZ) {
        goto L_01515E;
    }
    popAddress();
    return;
L_01515E:
    a = 0x57;
    pushAddress(0x9162);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9162)) return;
    a = 0x54;
    y = 0x80;
    SUB_01ED34();
    return;
}

void game::SUB_01516A() {
    pushAddress(0x916C);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0x916C)) return;
    pushAddress(0x916F);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0x916F)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        jump(0x91A2);
        return;
    }
    a = 0x02;
    myMapper->writeCPU(0x046C + x, a);
    SUB_01EFAF();
    return;
}

void game::SUB_01517C() {
    if (myMapper->readCPU(0x0560) == 0) {
        goto L_015189;
    }
    opCMP(myMapper->readCPU(0x046C + x), 0x84);
    if (flgZ) {
        SUB_015158();
        return;
    }
    popAddress();
    return;
L_015189:
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0x9190);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x9190)) return;
    SUB_01519D();
    return;
}

void game::SUB_01519D() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0151A3();
        return;
    }
    SUB_0151A2();
    return;
}

void game::SUB_0151A2() {
    popAddress();
}

void game::SUB_0151A3() {
    myMapper->writeCPU(0x04DC + x, 0x01);
    myMapper->writeCPU(0x046C + x, 0x81);
    a = 0x54;
    SUB_01EF04();
    return;
}

void game::SUB_0151B2() {
    opCMP(myMapper->readCPU(0x04A4 + x), 0x02);
    if (!flgZ) {
        goto L_0151BE;
    }
    a = myMapper->readCPU(0x0488 + x);
    setLoadFlag(a);
    if (flgZ) {
        SUB_0151BF();
        return;
    }
L_0151BE:
    popAddress();
}

void game::SUB_0151BF() {
    opDEC(0x04DC + x, 1);
    if (!flgZ) {
        goto L_0151D2;
    }
    pushAddress(0x91C6);
    SUB_01EF69();
    if (handleReturnAddress(poppedEntry.value, 0x91C6)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x04DC + x, myMapper->readCPU(0x91E5 + y));
L_0151D2:
    a = 0x02;
    pushAddress(0x91D6);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x91D6)) return;
    a = 0x00;
    y = 0xA0;
    pushAddress(0x91DD);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x91DD)) return;
    a = 0x30;
    y = 0x02;
    SUB_01ED34();
    return;
}

void game::SUB_0151E9() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        pushAddress(0x91F0);
        SUB_01EE75();
        if (handleReturnAddress(poppedEntry.value, 0x91F0)) return;
        myMapper->writeCPU(0x004D, myMapper->readCPU(0x0354 + x));
        a = 0x0C;
        myMapper->writeCPU(0x004C, a);
        pushAddress(0x91FC);
        SUB_01EC21();
        if (handleReturnAddress(poppedEntry.value, 0x91FC)) return;
        a = myMapper->readCPU(0x0014);
        setLoadFlag(a);
        if (flgZ) {
            goto L_015204;
        }
        SUB_01EAA9();
        return;
    L_015204:
        a = myMapper->readCPU(0x0300 + x);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_015224;
        }
        pushAddress(0x920B);
        SUB_01EF9C();
        if (handleReturnAddress(poppedEntry.value, 0x920B)) return;
        if (myMapper->readCPU(0x0014) != 0) {
            goto L_015224;
        }
        a = 0x05;
        myMapper->writeCPU(0x046C + x, a);
        SUB_01F1D2();
        return;
    }
    myMapper->writeCPU(0x0488 + x, 0x80);
    a = 0x10;
    y = 0x03;
    pushAddress(0x9223);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9223)) return;
L_015224:
    popAddress();
}

void game::SUB_015225() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01522B;
    }
    popAddress();
    return;
L_01522B:
    SUB_0151BF();
    return;
}

void game::SUB_01522E() {
    pushAddress(0x9230);
    SUB_01EF69();
    if (handleReturnAddress(poppedEntry.value, 0x9230)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x9236);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x9236)) return;
    SUB_015245();
    return;
}

void game::SUB_015245() {
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x0450 + x);
    }
    else {
        pushAddress(0x9254);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0x9254)) return;
        y = myMapper->readCPU(0x0450 + x);
        opCMP(a, 0x48);
        if (!flgC) {
            goto L_015260;
        }
        a = y;
        goto L_015263;
    L_015260:
        a = y;
        opEOR(0x01);
    }
L_015263:
    myMapper->writeCPU(0x04F8 + x, a);
    popAddress();
}

void game::SUB_015267() {
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x04DC + x, myMapper->readCPU(0x9280 + y));
    y = 0x80;
    a = 0x01;
    pushAddress(0x9278);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x9278)) return;
    y = 0x01;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_015284() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opDEC(0x04DC + x, 1);
    if (flgZ) {
        goto L_015299;
    }
    pushAddress(0x9291);
    SUB_015245();
    if (handleReturnAddress(poppedEntry.value, 0x9291)) return;
    y = 0x02;
    a = 0x10;
    SUB_01ED34();
    return;
L_015299:
    y = 0x03;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_0152A0() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0152DF;
    }
    pushAddress(0x92A7);
    SUB_01EE6F();
    if (handleReturnAddress(poppedEntry.value, 0x92A7)) return;
    myMapper->writeCPU(0x004D, myMapper->readCPU(0x0354 + x));
    a = 0x0C;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x92B3);
    SUB_01EC1A();
    if (handleReturnAddress(poppedEntry.value, 0x92B3)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0152C1;
    }
    a = myMapper->readCPU(0x04F8 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x04F8 + x, a);
    do {
        popAddress();
        return;
    L_0152C1:
        pushAddress(0x92C3);
        SUB_01EF9C();
        if (handleReturnAddress(poppedEntry.value, 0x92C3)) return;
    } while (myMapper->readCPU(0x0014) != 0);
    y = 0x40;
    a = 0x01;
    pushAddress(0x92CE);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x92CE)) return;
    myMapper->writeCPU(0x03C4 + x, 0x02);
    myMapper->writeCPU(0x03E0 + x, 0x80);
    myMapper->writeCPU(0x046C + x, 0x05);
    popAddress();
    return;
L_0152DF:
    y = 0x01;
    a = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_0152E6() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0152F4;
    }
    pushAddress(0x92F3);
    SUB_01ED5C();
    if (handleReturnAddress(poppedEntry.value, 0x92F3)) return;
L_0152F4:
    myMapper->writeCPU(0x054C + x, 0x08);
    myMapper->writeCPU(0x046C + x, 0x04);
    popAddress();
}

void game::SUB_0152FF() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_015305();
        return;
    }
    popAddress();
}

void game::SUB_015305() {
    myMapper->writeCPU(0x046C + x, 0x00);
    popAddress();
}

void game::SUB_01530B() {
    pushAddress(0x930D);
    SUB_01EE6F();
    if (handleReturnAddress(poppedEntry.value, 0x930D)) return;
    pushAddress(0x9310);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0x9310)) return;
    pushAddress(0x9313);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0x9313)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        goto L_015325;
    }
    a = myMapper->readCPU(0x0354 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0354 + x, a);
    myMapper->writeCPU(0x046C + x, 0x06);
L_015325:
    popAddress();
}

void game::SUB_01535E() {
    pushAddress(0x9360);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x9360)) return;
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0x9366);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x9366)) return;
    SUB_015371();
    return;
}

void game::SUB_015371() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_015377();
        return;
    }
    popAddress();
}

void game::SUB_015377() {
    a = myMapper->readCPU(0x038C);
    opADC(0x30);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x0354);
    opSBC(0x10);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x9387);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0x9387)) return;
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0002);
    opLSR_M(0x0001, 1);
    opROR_M(0x0002, 1);
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0002, a);
    a = y;
    opADC(myMapper->readCPU(0x0001));
    if (myMapper->readCPU(0x0009) != 0) {
        jump(0x93AF);
        return;
    }
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x03C4 + x, a);
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x03E0 + x, a);
    SUB_0153A5();
    return;
}

void game::SUB_0153A5() {
    a = 0x00;
    y = 0xC0;
    pushAddress(0x93AB);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x93AB)) return;
    SUB_0153C0();
    return;
}

void game::SUB_0153AF() {
    x = myMapper->readCPU(0x004E);
    y = myMapper->readCPU(0x0001);
    pushAddress(0x93B5);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x93B5)) return;
    myMapper->writeCPU(0x03C4 + x, 0x00);
    myMapper->writeCPU(0x03E0 + x, 0xC0);
    SUB_0153C0();
    return;
}

void game::SUB_0153C0() {
    a = 0x4A;
    pushAddress(0x93C4);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x93C4)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x93D2 + y);
    y = 0x01;
    SUB_01ED34();
    return;
}

void game::SUB_0153D6() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0153E1;
    }
    pushAddress(0x93DD);
    SUB_01EE75();
    if (handleReturnAddress(poppedEntry.value, 0x93DD)) return;
    SUB_0154DB();
    return;
L_0153E1:
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x93EE + y);
    y = 0x02;
    SUB_01ED34();
    return;
}

void game::SUB_0153F2() {
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (!flgZ) {
        pushAddress(0x93F9);
        SUB_01F1D2();
        if (handleReturnAddress(poppedEntry.value, 0x93F9)) return;
        SUB_0153A5();
        return;
    }
    a = myMapper->readCPU(0x0354);
    opSBC(myMapper->readCPU(0x0354 + x));
    if (flgC) {
        goto L_01540F;
    }
    do {
        do {
            pushAddress(0x9407);
            SUB_01EC88();
            if (handleReturnAddress(poppedEntry.value, 0x9407)) return;
            a = 0x10;
            y = 0x00;
            SUB_01ED34();
            return;
        L_01540F:
            opCMP(a, 0x38);
        } while (flgC);
        pushAddress(0x9415);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0x9415)) return;
        opCMP(a, 0x48);
    } while (flgC);
    a = myMapper->readCPU(0x0354);
    opADC(0x18);
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x038C);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0x9428);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0x9428)) return;
    x = myMapper->readCPU(0x004E);
    if (myMapper->readCPU(0x0009) != 0) {
        goto L_015447;
    }
    a = 0x01;
    y = 0xC0;
    pushAddress(0x9435);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x9435)) return;
    a = myMapper->readCPU(0x0002);
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x0001);
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x03C4 + x, a);
    goto L_015462;
L_015447:
    myMapper->writeCPU(0x03C4 + x, 0x02);
    myMapper->writeCPU(0x03E0 + x, 0x00);
    a = myMapper->readCPU(0x0002);
    opASL_A(1);
    opROL_M(0x0001, 1);
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0418 + x, a);
    a = myMapper->readCPU(0x0001);
    opADC(0x00);
    myMapper->writeCPU(0x03FC + x, a);
L_015462:
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x946F + y);
    y = 0x04;
    SUB_01ED34();
    return;
}

void game::SUB_015473() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0153F2();
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x07);
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00F7);
    opAND(0x40);
    if (!flgZ) {
        a = myMapper->readCPU(0x0354);
        opSBC(myMapper->readCPU(0x0354 + x));
        if (!flgC) {
            opEOR(0xFF);
        }
        opCMP(a, 0x14);
        if (!flgC) {
            pushAddress(0x9498);
            SUB_01EF84();
            if (handleReturnAddress(poppedEntry.value, 0x9498)) return;
            opCMP(a, 0x58);
            if (flgC) {
                goto L_0154B1;
            }
            myMapper->writeCPU(0x03C4 + x, 0x02);
            a = 0x80;
            myMapper->writeCPU(0x03E0 + x, a);
            pushAddress(0x94A9);
            SUB_01EC72();
            if (handleReturnAddress(poppedEntry.value, 0x94A9)) return;
            a = 0x08;
            y = 0x03;
            pushAddress(0x94B0);
            SUB_01ED34();
            if (handleReturnAddress(poppedEntry.value, 0x94B0)) return;
        }
    }
L_0154B1:
    popAddress();
}

void game::SUB_0154B2() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        goto L_0154BA;
    }
    SUB_0153F2();
    return;
L_0154BA:
    SUB_01EF56();
    return;
}

void game::SUB_0154BD() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        goto L_0154C5;
    }
    SUB_015377();
    return;
L_0154C5:
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x06);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    pushAddress(0x94D7);
    SUB_01EF43();
    if (handleReturnAddress(poppedEntry.value, 0x94D7)) return;
    SUB_01EE75();
    return;
}

void game::SUB_0154DB() {
    y = myMapper->readCPU(0x04DC + x);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_0154E3;
    }
    SUB_01EF43();
    return;
L_0154E3:
    SUB_01EF56();
    return;
}

void game::SUB_0154E6() {
    a = myMapper->readCPU(0x007A);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x046C + x);
        opCMP(a, 0x0E);
        if (flgZ) {
            goto L_0154F4;
        }
        pushAddress(0x94F3);
        SUB_01EF7C();
        if (handleReturnAddress(poppedEntry.value, 0x94F3)) return;
    L_0154F4:
        pushAddress(0x94F6);
        SUB_01EEA7();
        if (handleReturnAddress(poppedEntry.value, 0x94F6)) return;
        a = myMapper->readCPU(0x046C + x);
        opAND(0x7F);
        pushAddress(0x94FE);
        SUB_01CA6D();
        if (handleReturnAddress(poppedEntry.value, 0x94FE)) return;
    }
    pushAddress(0x951F);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0x951F)) return;
    pushAddress(0x9522);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0x9522)) return;
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0x952A);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x952A)) return;
    SUB_015541();
    return;
}

void game::SUB_015541() {
    if (myMapper->readCPU(0x0048) != 0) {
        goto L_015546;
    }
    popAddress();
    return;
L_015546:
    a = 0x78;
    y = 0x81;
    SUB_01ED34();
    return;
}

void game::SUB_01554D() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_015553;
    }
    popAddress();
    return;
L_015553:
    myMapper->writeCPU(0x020D, 0xFC);
    myMapper->writeCPU(0x020E, 0x01);
    x = 0x08;
    a = 0x04;
    pushAddress(0x9563);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x9563)) return;
    a = 0x80;
    myMapper->writeCPU(0x0300 + x, a);
    myMapper->writeCPU(0x038C + x, a);
    myMapper->writeCPU(0x0354 + x, a);
    myMapper->writeCPU(0x046C + x, a);
    x = 0x07;
    a = 0x3C;
    y = 0x82;
    SUB_01ED34();
    return;
}

void game::SUB_01557B() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0155B7();
        return;
    }
    SUB_015580();
    return;
}

void game::SUB_015580() {
    a = myMapper->readCPU(0x0354 + x);
    flgC = false;
    opADC(0xDD);
    myMapper->writeCPU(0x020C, a);
    opADC(0x08);
    myMapper->writeCPU(0x035C, a);
    myMapper->writeCPU(0x0474, myMapper->readCPU(0x046C + x));
    myMapper->writeCPU(0x004B, 0xF6);
    a = 0x01;
    if (myMapper->readCPU(0x0450 + x) != 0) {
        goto L_0155A5;
    }
    myMapper->writeCPU(0x004B, 0x02);
    a = 0x41;
L_0155A5:
    myMapper->writeCPU(0x020E, a);
    a = myMapper->readCPU(0x038C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x020F, a);
    opADC(0x04);
    myMapper->writeCPU(0x0394, a);
    popAddress();
}

void game::SUB_0155B7() {
    myMapper->writeCPU(0x03C4 + x, 0x00);
    myMapper->writeCPU(0x03E0 + x, 0x80);
    a = 0x83;
    myMapper->writeCPU(0x046C + x, a);
    SUB_015580();
    return;
}

void game::SUB_0155C9() {
    pushAddress(0x95CB);
    SUB_01EF56();
    if (handleReturnAddress(poppedEntry.value, 0x95CB)) return;
    opCMP(a, 0xA8);
    if (!flgC) {
        goto L_0155D3;
    }
    SUB_015580();
    return;
L_0155D3:
    myMapper->writeCPU(0x0354 + x, 0xA8);
    a = 0x3C;
    y = 0x84;
    pushAddress(0x95DE);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x95DE)) return;
    SUB_015580();
    return;
}

void game::SUB_0155E2() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0155EA;
    }
    SUB_015580();
    return;
L_0155EA:
    myMapper->writeCPU(0x0488 + x, 0x80);
    a = 0x45;
    y = 0x85;
    pushAddress(0x95F5);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x95F5)) return;
    SUB_015580();
    return;
}

void game::SUB_0155F9() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_01560F();
        return;
    }
    y = 0x00;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_015608;
    }
    y = 0xD0;
L_015608:
    a = y;
    myMapper->writeCPU(0x031C + x, a);
    SUB_015580();
    return;
}

void game::SUB_01560F() {
    a = 0x29;
    pushAddress(0x9613);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9613)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x9624 + y);
    y = 0x06;
    pushAddress(0x9620);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9620)) return;
    SUB_015580();
    return;
}

void game::SUB_015628() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_015630;
    }
    SUB_015580();
    return;
L_015630:
    a = 0x2A;
    pushAddress(0x9634);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9634)) return;
    a = 0x10;
    y = 0x07;
    pushAddress(0x963B);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x963B)) return;
    SUB_015580();
    return;
}

void game::SUB_01563F() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_015647;
    }
    SUB_015580();
    return;
L_015647:
    pushAddress(0x9649);
    SUB_0159C3();
    if (handleReturnAddress(poppedEntry.value, 0x9649)) return;
    x = 0x07;
    a = 0x20;
    y = 0x08;
    pushAddress(0x9652);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9652)) return;
    SUB_015580();
    return;
}

void game::SUB_015656() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01565E;
    }
    SUB_015580();
    return;
L_01565E:
    myMapper->writeCPU(0x0488 + x, 0x80);
    a = 0x20;
    y = 0x89;
    pushAddress(0x9669);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9669)) return;
    SUB_015580();
    return;
}

void game::SUB_01566D() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_01568E();
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        SUB_015686();
        return;
    }
    SUB_015678();
    return;
}

void game::SUB_015678() {
    myMapper->writeCPU(0x031C + x, 0x00);
    a = 0xF4;
    myMapper->writeCPU(0x020C, a);
    myMapper->writeCPU(0x0210, a);
    popAddress();
}

void game::SUB_015686() {
    a = 0xD1;
    myMapper->writeCPU(0x031C + x, a);
    SUB_015580();
    return;
}

void game::SUB_01568E() {
    a = 0x23;
    pushAddress(0x9692);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9692)) return;
    a = 0x4F;
    y = 0x8A;
    pushAddress(0x9699);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9699)) return;
    SUB_015678();
    return;
}

void game::SUB_01569D() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0156A3;
    }
    popAddress();
    return;
L_0156A3:
    myMapper->writeCPU(0x004B, myMapper->readCPU(0x001A));
    while (true) {
        a = myMapper->readCPU(0x004B);
        opAND(0x07);
        y = a;
        a = myMapper->readCPU(0x038C);
        opADC(myMapper->readCPU(0x96C9 + y));
        opCMP(a, 0x14);
        if (!flgC) {
            goto L_0156BA;
        }
        opCMP(a, 0xEC);
        if (!flgC) {
            goto L_0156BF;
        }
    L_0156BA:
        opINC(0x004B, 1);
    }
L_0156BF:
    myMapper->writeCPU(0x038C + x, a);
    a = 0x20;
    y = 0x8B;
    SUB_01ED34();
    return;
}

void game::SUB_0156D1() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        a = myMapper->readCPU(0x001A);
        opAND(0x01);
        if (flgZ) {
            goto L_0156DF;
        }
        SUB_015678();
        return;
    L_0156DF:
        a = 0xD0;
        myMapper->writeCPU(0x031C + x, a);
        SUB_015580();
        return;
    }
    SUB_01560F();
    return;
}

void game::SUB_0156EA() {
    a = 0xF4;
    myMapper->writeCPU(0x020C, a);
    myMapper->writeCPU(0x0210, a);
    x = 0x08;
    a = 0x35;
    pushAddress(0x96F8);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x96F8)) return;
    a = 0x2B;
    pushAddress(0x96FD);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x96FD)) return;
    x = 0x07;
    a = myMapper->readCPU(0x0450 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x0458, a);
    myMapper->writeCPU(0x0404, 0x02);
    myMapper->writeCPU(0x0420, 0x00);
    myMapper->writeCPU(0x03CC, 0x05);
    myMapper->writeCPU(0x03E8, 0x00);
    a = 0x78;
    y = 0x8E;
    SUB_01ED34();
    return;
}

void game::SUB_015723() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_015729;
    }
    popAddress();
    return;
L_015729:
    myMapper->writeCPU(0x007A, 0x01);
    myMapper->writeCPU(0x04DC + x, myMapper->readCPU(0x031C + x));
    myMapper->writeCPU(0x0488 + x, 0x80);
    y = 0x80;
    a = 0x20;
    SUB_01ED34();
    return;
}

void game::SUB_01573F() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        a = myMapper->readCPU(0x001A);
        opAND(0x01);
        if (flgZ) {
            goto L_015750;
        }
        myMapper->writeCPU(0x031C + x, 0x00);
        popAddress();
        return;
    L_015750:
        myMapper->writeCPU(0x031C + x, myMapper->readCPU(0x04DC + x));
        popAddress();
        return;
    }
    myMapper->writeCPU(0x004E, x);
    pushAddress(0x975B);
    SUB_01FCF0();
    if (handleReturnAddress(poppedEntry.value, 0x975B)) return;
    x = myMapper->readCPU(0x004E);
    pushAddress(0x9760);
    SUB_015945();
    if (handleReturnAddress(poppedEntry.value, 0x9760)) return;
    myMapper->writeCPU(0x0300 + x, 0x80);
    a = 0x10;
    y = 0x81;
    SUB_01ED34();
    return;
}

void game::SUB_01576D() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_015773;
    }
    popAddress();
    return;
L_015773:
    myMapper->writeCPU(0x01A9, 0x40);
    myMapper->writeCPU(0x01A8, 0x00);
    SUB_01577D();
    return;
}

void game::SUB_01577D() {
    myMapper->writeCPU(0x0300 + x, 0x00);
    a = 0x36;
    pushAddress(0x9786);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9786)) return;
    x = 0x08;
    a = 0x04;
    pushAddress(0x978D);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x978D)) return;
    myMapper->writeCPU(0x0300 + x, 0x80);
    x = 0x07;
    myMapper->writeCPU(0x0354 + x, 0xA8);
    a = 0x21;
    y = 0x82;
    pushAddress(0x97A0);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x97A0)) return;
    SUB_0157A1();
    return;
}

void game::SUB_0157A1() {
    a = myMapper->readCPU(0x0354 + x);
    flgC = true;
    opSBC(0x20);
    myMapper->writeCPU(0x035C, a);
    a = 0x08;
    if (myMapper->readCPU(0x0450 + x) == 0) {
        goto L_0157B3;
    }
    a = 0xF8;
L_0157B3:
    myMapper->writeCPU(0x004B, a);
    a = myMapper->readCPU(0x038C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x0394, a);
    popAddress();
}

void game::SUB_0157BF() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_0157C7();
        return;
    }
    SUB_0157A1();
    return;
}

void game::SUB_0157C7() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    y = a;
    a = myMapper->readCPU(0x97D7 + y);
    y = 0x03;
    pushAddress(0x97D3);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x97D3)) return;
    SUB_0157A1();
    return;
}

void game::SUB_0157DB() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        a = myMapper->readCPU(0x001A);
        opAND(0x0F);
        if (flgZ) {
            a = myMapper->readCPU(0x0450);
            opCMP(a, myMapper->readCPU(0x0450 + x));
            if (flgZ) {
                goto L_0157F4;
            }
            a = myMapper->readCPU(0x00F7);
            opAND(0x40);
            if (!flgZ) {
                goto L_0157F7;
            }
        }
    L_0157F4:
        SUB_0157A1();
        return;
    }
L_0157F7:
    a = 0x31;
    pushAddress(0x97FB);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x97FB)) return;
    a = 0x10;
    y = 0x04;
    pushAddress(0x9802);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9802)) return;
    SUB_0157A1();
    return;
}

void game::SUB_015806() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01580E;
    }
    SUB_0157A1();
    return;
L_01580E:
    a = 0x32;
    pushAddress(0x9812);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9812)) return;
    myMapper->writeCPU(0x04F8 + x, myMapper->readCPU(0x0450 + x));
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_015838;
    }
    myMapper->writeCPU(0x03C4 + x, 0x06);
    myMapper->writeCPU(0x03E0 + x, 0x00);
    while (true) {
        a = 0x00;
        y = 0xC0;
        pushAddress(0x982F);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0x982F)) return;
        a = 0x05;
        myMapper->writeCPU(0x046C + x, a);
        SUB_0157A1();
        return;
    L_015838:
        myMapper->writeCPU(0x03C4 + x, 0x04);
        a = 0x80;
        myMapper->writeCPU(0x03E0 + x, a);
    }
    SUB_015845();
    return;
}

void game::SUB_015845() {
    pushAddress(0x9847);
    SUB_01591C();
    if (handleReturnAddress(poppedEntry.value, 0x9847)) return;
    pushAddress(0x984A);
    SUB_01EE1C();
    if (handleReturnAddress(poppedEntry.value, 0x984A)) return;
    if (myMapper->readCPU(0x04F8 + x) != 0) {
        opCMP(myMapper->readCPU(0x038C + x), 0x18);
        if (!flgC) {
            goto L_015860;
        }
        if (flgC) {
            goto L_015868;
        }
    }
    opCMP(myMapper->readCPU(0x038C + x), 0xE8);
    if (flgC) {
    L_015860:
        a = myMapper->readCPU(0x04F8 + x);
        opEOR(0x01);
        myMapper->writeCPU(0x04F8 + x, a);
    }
L_015868:
    a = myMapper->readCPU(0x0354 + x);
    opADC(0x08);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0x9875);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0x9875)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        goto L_015890;
    }
    pushAddress(0x987C);
    SUB_01EFAF();
    if (handleReturnAddress(poppedEntry.value, 0x987C)) return;
    a = 0x18;
    y = 0x06;
    pushAddress(0x9883);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x9883)) return;
    a = 0x34;
    pushAddress(0x9888);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x9888)) return;
    myMapper->writeCPU(0x004E, x);
    pushAddress(0x988D);
    SUB_01FD0E();
    if (handleReturnAddress(poppedEntry.value, 0x988D)) return;
    x = myMapper->readCPU(0x004E);
L_015890:
    SUB_0157A1();
    return;
}

void game::SUB_015893() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01589B;
    }
    SUB_0157A1();
    return;
L_01589B:
    a = 0x36;
    pushAddress(0x989F);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x989F)) return;
    a = myMapper->readCPU(0x0354 + x);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x0354 + x, a);
    a = 0x10;
    y = 0x07;
    pushAddress(0x98AF);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x98AF)) return;
    SUB_0157A1();
    return;
}

void game::SUB_0158B3() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_0157A1();
        return;
    }
    pushAddress(0x98BD);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0x98BD)) return;
    opCMP(a, 0x30);
    if (flgC) {
        goto L_0158C5;
    }
    do {
        SUB_0157C7();
        return;
    L_0158C5:
        opAND(0x03);
    } while (flgZ);
    y = 0x10;
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (flgZ) {
        goto L_0158D3;
    }
    y = 0x28;
L_0158D3:
    a = y;
    y = 0x08;
    pushAddress(0x98D8);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x98D8)) return;
    SUB_0157A1();
    return;
}

void game::SUB_0158DC() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0158E4;
    }
    SUB_0157A1();
    return;
L_0158E4:
    a = 0x35;
    pushAddress(0x98E8);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x98E8)) return;
    y = 0x09;
    a = 0x10;
    pushAddress(0x98EF);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x98EF)) return;
    SUB_0157A1();
    return;
}

void game::SUB_0158F3() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_0158FB;
    }
    SUB_0157A1();
    return;
L_0158FB:
    myMapper->writeCPU(0x004E, x);
    pushAddress(0x98FF);
    SUB_01FCFA();
    if (handleReturnAddress(poppedEntry.value, 0x98FF)) return;
    x = myMapper->readCPU(0x004E);
    pushAddress(0x9904);
    SUB_0159BE();
    if (handleReturnAddress(poppedEntry.value, 0x9904)) return;
    x = 0x07;
    a = 0x10;
    y = 0x0A;
    pushAddress(0x990D);
    SUB_01ED34();
    if (handleReturnAddress(poppedEntry.value, 0x990D)) return;
    SUB_0157A1();
    return;
}

void game::SUB_015911() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_015919;
    }
    SUB_0157A1();
    return;
L_015919:
    SUB_01577D();
    return;
}

void game::SUB_01591C() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x30);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    pushAddress(0x992E);
    SUB_01EF56();
    if (handleReturnAddress(poppedEntry.value, 0x992E)) return;
    opCMP(a, 0x20);
    if (!flgC) {
        pushAddress(0x9935);
        SUB_01F1D2();
        if (handleReturnAddress(poppedEntry.value, 0x9935)) return;
        a = myMapper->readCPU(0x0354 + x);
    }
    y = 0x32;
    opCMP(a, 0x60);
    if (flgC) {
        goto L_015941;
    }
    y = 0x33;
L_015941:
    a = y;
    SUB_01EF04();
    return;
}

void game::SUB_015945() {
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x0012, 0x00);
    y = 0x04;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_015958;
        }
    L_015952:
        opINY(1);
        opCMP(y, 0x0E);
    } while (!flgC);
    popAddress();
    return;
L_015958:
    myMapper->writeCPU(0x0016, 0x21);
    a = 0x37;
    pushAddress(0x9960);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x9960)) return;
    a = myMapper->readCPU(0x0012);
    opASL_A(1);
    myMapper->writeCPU(0x004B, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    x = a;
    myMapper->writeCPU(0x0450 + y, myMapper->readCPU(0x999A + x));
    myMapper->writeCPU(0x04DC + y, myMapper->readCPU(0x999B + x));
    myMapper->writeCPU(0x03FC + y, myMapper->readCPU(0x999C + x));
    myMapper->writeCPU(0x0418 + y, myMapper->readCPU(0x999D + x));
    myMapper->writeCPU(0x03C4 + y, myMapper->readCPU(0x999E + x));
    myMapper->writeCPU(0x03E0 + y, myMapper->readCPU(0x999F + x));
    x = myMapper->readCPU(0x004E);
    opINC(0x0012, 1);
    opCMP(myMapper->readCPU(0x0012), 0x06);
    if (!flgC) {
        goto L_015952;
    }
    popAddress();
}

void game::SUB_0159BE() {
    x = 0x08;
    SUB_0159C5();
    return;
}

void game::SUB_0159C3() {
    x = 0x07;
    SUB_0159C5();
    return;
}

void game::SUB_0159C5() {
    myMapper->writeCPU(0x0012, x);
    myMapper->writeCPU(0x0010, 0x02);
    y = 0x0D;
    do {
        a = myMapper->readCPU(0x0434 + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0159DA;
        }
    L_0159D2:
        opDEY(1);
        opCMP(y, 0x04);
    } while (flgC);
    goto L_015A34;
L_0159DA:
    myMapper->writeCPU(0x0011, y);
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x0016, 0x20);
    a = 0x08;
    pushAddress(0x99E6);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0x99E6)) return;
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x038C));
    a = myMapper->readCPU(0x0354);
    y = myMapper->readCPU(0x0010);
    flgC = false;
    opADC(myMapper->readCPU(0x9A35 + y));
    myMapper->writeCPU(0x0000, a);
    x = myMapper->readCPU(0x0011);
    pushAddress(0x99FB);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0x99FB)) return;
    opASL_M(0x0002, 1);
    opROL_M(0x0001, 1);
    if (myMapper->readCPU(0x0009) == 0) {
        myMapper->writeCPU(0x03E0 + x, myMapper->readCPU(0x0002));
        myMapper->writeCPU(0x03C4 + x, myMapper->readCPU(0x0001));
        a = 0x02;
        y = 0x00;
        pushAddress(0x9A14);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0x9A14)) return;
    }
    else {
        y = myMapper->readCPU(0x0002);
        a = myMapper->readCPU(0x0001);
        pushAddress(0x9A1E);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0x9A1E)) return;
        myMapper->writeCPU(0x03C4 + x, 0x02);
        a = 0x00;
        myMapper->writeCPU(0x03E0 + x, a);
    }
    opDEC(0x0010, 1);
    if (flgN) {
        goto L_015A34;
    }
    y = myMapper->readCPU(0x0011);
    x = myMapper->readCPU(0x0012);
    goto L_0159D2;
L_015A34:
    popAddress();
}

void game::SUB_01805D() {
    a = myMapper->readCPU(0x0184 + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_018063;
    }
    do {
        popAddress();
        return;
    L_018063:
        myMapper->writeCPU(0x004B, 0x07);
        x = 0x04;
        pushAddress(0x806B);
        SUB_01F41F();
        if (handleReturnAddress(poppedEntry.value, 0x806B)) return;
        opCMP(x, 0xFF);
    } while (flgZ);
    myMapper->writeCPU(0x000D, x);
    a = myMapper->readCPU(0x006F);
    opAND(0x01);
    while (true) {
        myMapper->writeCPU(0x004B, a);
        a = 0xF8;
        y = myMapper->readCPU(0x004B);
        setLoadFlag(y);
        if (!flgZ) {
            a = 0x08;
        }
        myMapper->writeCPU(0x038C + x, a);
        opSBC(myMapper->readCPU(0x038C));
        if (flgC) {
            goto L_01808A;
        }
        opEOR(0xFF);
    L_01808A:
        opCMP(a, 0x40);
        if (flgC) {
            goto L_018097;
        }
        a = myMapper->readCPU(0x006F);
        opAND(0x01);
        opEOR(0x01);
    }
L_018097:
    a = y;
    opEOR(0x01);
    myMapper->writeCPU(0x0450 + x, a);
    myMapper->writeCPU(0x004C, 0x00);
    y = myMapper->readCPU(0x000C);
    a = myMapper->readCPU(0x017E + y);
    myMapper->writeCPU(0x0354 + x, a);
    flgC = false;
    opADC(0x14);
    myMapper->writeCPU(0x004D, a);
    pushAddress(0x80B0);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0x80B0)) return;
    if (myMapper->readCPU(0x0014) != 0) {
        opCMP(myMapper->readCPU(0x0063), 0x03);
        if (!flgC) {
            goto L_0180C3;
        }
        myMapper->writeCPU(0x0063, 0x00);
        a = 0x90;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0180C5;
        }
    L_0180C3:
        a = 0x10;
    L_0180C5:
        y = myMapper->readCPU(0x000C);
        myMapper->writeCPU(0x0184 + y, a);
        opINC(0x0063, 1);
        a = 0x00;
        y = 0xE0;
        pushAddress(0x80D2);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0x80D2)) return;
        a = 0x01;
        pushAddress(0x80D7);
        SUB_01F42C();
        if (handleReturnAddress(poppedEntry.value, 0x80D7)) return;
        a = 0x00;
        SUB_01EF04();
        return;
    }
    myMapper->writeCPU(0x0434 + x, 0x32);
    popAddress();
}

void game::SUB_0180E3() {
    if (myMapper->readCPU(0x002B) == 0) {
        jump(0x80EC);
        return;
    }
    SUB_0180E7();
    return;
}

void game::SUB_0180E7() {
    a = myMapper->readCPU(0x0184 + y);
    setLoadFlag(a);
    if (flgZ) {
        SUB_0180ED();
        return;
    }
    SUB_0180EC();
    return;
}

void game::SUB_0180EC() {
    popAddress();
}

void game::SUB_0180ED() {
    myMapper->writeCPU(0x004B, 0x0C);
    x = 0x09;
    pushAddress(0x80F5);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x80F5)) return;
    if (x == 0xFF) {
        jump(0x80EC);
        return;
    }
    opCMP(myMapper->readCPU(0x046C), 0x04);
    if (flgZ) {
        SUB_0180EC();
        return;
    }
    myMapper->writeCPU(0x000D, x);
    a = myMapper->readCPU(0x0450);
    while (true) {
        myMapper->writeCPU(0x004B, a);
        a = 0xF8;
        y = myMapper->readCPU(0x004B);
        setLoadFlag(y);
        if (!flgZ) {
            a = 0x08;
        }
        myMapper->writeCPU(0x038C + x, a);
        opSBC(myMapper->readCPU(0x038C));
        if (flgC) {
            goto L_01811A;
        }
        opEOR(0xFF);
    L_01811A:
        opCMP(a, 0x40);
        if (flgC) {
            goto L_018126;
        }
        a = myMapper->readCPU(0x0450);
        opEOR(0x01);
    }
L_018126:
    a = y;
    opEOR(0x01);
    myMapper->writeCPU(0x0450 + x, a);
    a = 0xC0;
    y = myMapper->readCPU(0x000C);
    myMapper->writeCPU(0x0184 + y, a);
    a = 0x01;
    y = 0x20;
    pushAddress(0x8139);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8139)) return;
    pushAddress(0x813C);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0x813C)) return;
    myMapper->writeCPU(0x04F8 + x, a);
    a = myMapper->readCPU(0x001A);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0x815D + y);
    opADC(myMapper->readCPU(0x0354));
    myMapper->writeCPU(0x0354 + x, a);
    opADC(0x08);
    myMapper->writeCPU(0x04DC + x, a);
    a = 0x02;
    pushAddress(0x8157);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x8157)) return;
    a = 0x38;
    SUB_01EF04();
    return;
}

void game::SUB_018161() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_018173;
    }
    myMapper->writeCPU(0x004B, 0x0A);
    x = 0x07;
    pushAddress(0x816E);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x816E)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_018174;
    }
L_018173:
    popAddress();
    return;
L_018174:
    myMapper->writeCPU(0x000D, x);
    pushAddress(0x8178);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x8178)) return;
    myMapper->writeCPU(0x000E, 0x51);
    a = 0x11;
    SUB_01F447();
    return;
}

void game::SUB_018182() {
    if (myMapper->readCPU(0x016C + y) != 0x01) {
        goto L_01818F;
    }
    myMapper->writeCPU(0x0184 + y, 0x54);
    do {
        do {
            do {
                popAddress();
                return;
            L_01818F:
                a = myMapper->readCPU(0x0184 + y);
                setLoadFlag(a);
            } while (!flgZ);
            myMapper->writeCPU(0x004B, 0x09);
            x = 0x07;
            pushAddress(0x819C);
            SUB_01F41F();
            if (handleReturnAddress(poppedEntry.value, 0x819C)) return;
        } while (x == 0xFF);
        myMapper->writeCPU(0x000D, x);
        pushAddress(0x81A5);
        SUB_01F4A9();
        if (handleReturnAddress(poppedEntry.value, 0x81A5)) return;
        if (myMapper->readCPU(0x002B) != 0) {
            goto L_0181B0;
        }
        opCMP(myMapper->readCPU(0x004B), 0x28);
    } while (!flgC);
L_0181B0:
    myMapper->writeCPU(0x0184 + y, 0xFF);
    myMapper->writeCPU(0x000E, 0x04);
    a = 0x03;
    SUB_01F447();
    return;
}

void game::SUB_0181BE() {
    pushAddress(0x81C0);
    SUB_01F48D();
    if (handleReturnAddress(poppedEntry.value, 0x81C0)) return;
    myMapper->writeCPU(0x000E, 0x49);
    a = 0x19;
    SUB_01F484();
    return;
}

void game::SUB_0181DD() {
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x014A + x);
    opAND(0x03);
    pushAddress(0x81E6);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0x81E6)) return;
    SUB_0181EF();
    return;
}

void game::SUB_0181EF() {
    SUB_018282();
    return;
}

void game::SUB_0181F6() {
    a = myMapper->readCPU(0x001A);
    flgC = true;
    opSBC(myMapper->readCPU(0x004E));
    myMapper->writeCPU(0x004F, a);
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x014A + x);
    x = 0x0F;
    opAND(0x04);
    if (!flgZ) {
        x = 0x03;
    }
    a = x;
    opAND(myMapper->readCPU(0x004F));
    if (!flgZ) {
        SUB_018282();
        return;
    }
    pushAddress(0x8211);
    SUB_0183A3();
    if (handleReturnAddress(poppedEntry.value, 0x8211)) return;
    if (flgC) {
        SUB_018282();
        return;
    }
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x0156 + x);
    opAND(0x0F);
    myMapper->writeCPU(0x004B, a);
    y = a;
    setLoadFlag(y);
    if (!flgZ) {
        a = myMapper->readCPU(0x0156 + x);
        opLSR_A(4);
        if (a != myMapper->readCPU(0x004B)) {
            goto L_018233;
        }
    }
    a = myMapper->readCPU(0x014A + x);
    opEOR(0x04);
    myMapper->writeCPU(0x014A + x, a);
L_018233:
    a = myMapper->readCPU(0x014A + x);
    opINC(0x0156 + x, 1);
    opAND(0x04);
    if (flgZ) {
        opDEC(0x0156 + x, 2);
    }
    pushAddress(0x8245);
    SUB_018307();
    if (handleReturnAddress(poppedEntry.value, 0x8245)) return;
    a = 0x20;
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0010, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0011));
    myMapper->writeCPU(0x0011, a);
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x014A + x);
    opAND(0x04);
    if (!flgZ) {
        a = myMapper->readCPU(0x0010);
        flgC = true;
        opSBC(0x40);
        myMapper->writeCPU(0x0010, a);
        if (!flgC) {
            opDEC(0x0011, 1);
        }
    }
    myMapper->writeCPU(0x004B, 0x02);
    a = myMapper->readCPU(0x014A + x);
    opAND(0x04);
    if (!flgZ) {
        opDEC(0x004B, 1);
        a = myMapper->readCPU(0x0156 + x);
        opAND(0x0F);
        if (a != 0x01) {
            goto L_01827F;
        }
        opDEC(0x004B, 1);
    }
L_01827F:
    pushAddress(0x8281);
    SUB_018338();
    if (handleReturnAddress(poppedEntry.value, 0x8281)) return;
    SUB_018282();
    return;
}

void game::SUB_018282() {
    a = myMapper->readCPU(0x046C);
    if (a != 0x05) {
        if (a == 0x08) {
            goto L_0182FB;
        }
        if (myMapper->readCPU(0x005B) == 0) {
            x = myMapper->readCPU(0x004E);
            a = myMapper->readCPU(0x014A + x);
            opAND(0x03);
            if (a == 0x01) {
                a = myMapper->readCPU(0x0156 + x);
                opAND(0x0F);
                opASL_A(3);
                myMapper->writeCPU(0x0000, a);
                a = 0x04;
                myMapper->writeCPU(0x0010, a);
                flgC = false;
                opADC(myMapper->readCPU(0x014D + x));
                flgC = false;
                opADC(myMapper->readCPU(0x0000));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x0150 + x);
                flgC = false;
                opADC(0x0A);
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x0153 + x);
                opADC(0x00);
                myMapper->writeCPU(0x0002, a);
                myMapper->writeCPU(0x0012, 0x10);
                x = myMapper->readCPU(0x0040);
                myMapper->writeCPU(0x0003, myMapper->readCPU(0x0041));
                y = myMapper->readCPU(0x003F);
                myMapper->writeCPU(0x0011, 0x0C);
                a = 0x06;
                myMapper->writeCPU(0x0013, a);
                pushAddress(0x82D8);
                SUB_01A048();
                if (handleReturnAddress(poppedEntry.value, 0x82D8)) return;
                if (!flgC) {
                    x = myMapper->readCPU(0x046C);
                    opDEX(1);
                    if (!flgZ) {
                        goto L_0182E7;
                    }
                    pushAddress(0x82E3);
                    SUB_0196C1();
                    if (handleReturnAddress(poppedEntry.value, 0x82E3)) return;
                    goto L_0182EA;
                L_0182E7:
                    pushAddress(0x82E9);
                    SUB_01A1E5();
                    if (handleReturnAddress(poppedEntry.value, 0x82E9)) return;
                L_0182EA:
                    a = 0x00;
                    myMapper->writeCPU(0x0044, a);
                    myMapper->writeCPU(0x0045, a);
                    a = myMapper->readCPU(0x0044);
                    myMapper->writeCPU(0x004B, a);
                    y = 0x67;
                    myMapper->writeCPU(0x004F, y);
                    pushAddress(0x82FA);
                    SUB_01A23B();
                    if (handleReturnAddress(poppedEntry.value, 0x82FA)) return;
                }
            }
        }
    }
L_0182FB:
    opINC(0x004E, 1);
    a = myMapper->readCPU(0x004E);
    if (a != 0x03) {
        jump(0x8304);
        return;
    }
    SUB_018303();
    return;
}

void game::SUB_018303() {
    popAddress();
}

void game::SUB_018304() {
    SUB_0181DD();
    return;
}

void game::SUB_018307() {
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x004C, myMapper->readCPU(0x014D + x));
    a = myMapper->readCPU(0x0156 + x);
    opAND(0x0F);
    opASL_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x004C));
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0011, 0x00);
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0150 + x));
    a = myMapper->readCPU(0x0153 + x);
    myMapper->writeCPU(0x0013, a);
    pushAddress(0x832B);
    SUB_01F918();
    if (handleReturnAddress(poppedEntry.value, 0x832B)) return;
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0008));
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x0009));
    myMapper->writeCPU(0x004B, 0x03);
    SUB_018338();
    return;
}

void game::SUB_018338() {
    a = myMapper->readCPU(0x004B);
    opASL_A(2);
    y = a;
    x = myMapper->readCPU(0x0020);
    myMapper->writeCPU(0x0700 + x, 0x01);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0011));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0010));
    opINX(1);
    myMapper->writeCPU(0x004B, 0x04);
    do {
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x836A + y));
        opINX(1);
        opINY(1);
        opDEC(0x004B, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0700 + x, 0xFF);
    opINX(1);
    myMapper->writeCPU(0x0020, x);
    popAddress();
}

void game::SUB_0183A3() {
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x0153 + x));
    a = myMapper->readCPU(0x0150 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0040));
    myMapper->writeCPU(0x0000, a);
    if (!flgC) {
        opDEC(0x0001, 1);
    }
    a = myMapper->readCPU(0x0001);
    flgC = true;
    opSBC(myMapper->readCPU(0x0041));
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x0000);
    flgC = false;
    opADC(0xC0);
    myMapper->writeCPU(0x0000, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0001));
    if (flgZ) {
        goto L_0183D4;
    }
    if (a != 0x01) {
        goto L_0183D6;
    }
    if (myMapper->readCPU(0x0000) >= 0x80) {
        goto L_0183D6;
    }
L_0183D4:
    flgC = false;
    popAddress();
    return;
L_0183D6:
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x0156 + x);
    opAND(0xF0);
    opORA(0x01);
    myMapper->writeCPU(0x0156 + x, a);
    flgC = true;
    popAddress();
}

void game::SUB_018425() {
    pushAddress(0x8427);
    SUB_01F48D();
    if (handleReturnAddress(poppedEntry.value, 0x8427)) return;
    myMapper->writeCPU(0x000E, 0x23);
    a = 0x1B;
    SUB_01F484();
    return;
}

void game::SUB_01849A() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_0184AC;
    }
    myMapper->writeCPU(0x004B, 0x0C);
    x = 0x09;
    pushAddress(0x84A7);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x84A7)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_0184AD;
    }
L_0184AC:
    popAddress();
    return;
L_0184AD:
    pushAddress(0x84AF);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x84AF)) return;
    myMapper->writeCPU(0x000E, 0x3A);
    a = 0x07;
    SUB_01F447();
    return;
}

void game::SUB_0184B9() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_0184CB;
    }
    myMapper->writeCPU(0x004B, 0x07);
    x = 0x04;
    pushAddress(0x84C6);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x84C6)) return;
    if (x != 0xFF) {
        goto L_0184CC;
    }
L_0184CB:
    popAddress();
    return;
L_0184CC:
    myMapper->writeCPU(0x000D, x);
    pushAddress(0x84D0);
    SUB_01F4A9();
    if (handleReturnAddress(poppedEntry.value, 0x84D0)) return;
    pushAddress(0x84D3);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x84D3)) return;
    myMapper->writeCPU(0x03FC + x, 0x00);
    myMapper->writeCPU(0x0418 + x, 0x80);
    myMapper->writeCPU(0x000E, 0x47);
    a = 0x08;
    SUB_01F447();
    return;
}

void game::SUB_018567() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_018579;
    }
    myMapper->writeCPU(0x004B, 0x09);
    x = 0x07;
    pushAddress(0x8574);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x8574)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_01857A;
    }
L_018579:
    popAddress();
    return;
L_01857A:
    myMapper->writeCPU(0x000D, x);
    pushAddress(0x857E);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x857E)) return;
    myMapper->writeCPU(0x000E, 0x4E);
    a = 0x10;
    SUB_01F447();
    return;
}

void game::SUB_018588() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_01859A;
    }
    myMapper->writeCPU(0x004B, 0x09);
    x = 0x07;
    pushAddress(0x8595);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x8595)) return;
    if (x != 0xFF) {
        goto L_01859B;
    }
    do {
        do {
            do {
            L_01859A:
                popAddress();
                return;
            L_01859B:
                myMapper->writeCPU(0x000D, x);
                x = myMapper->readCPU(0x0172 + y);
                a = myMapper->readCPU(0x0166 + y);
                opAND(0xF0);
                if (flgZ) {
                    goto L_0185AE;
                }
                opCMP(x, 0xE0);
            } while (!flgC);
            if (flgC) {
                goto L_0185B3;
            }
        L_0185AE:
            opCMP(x, 0x20);
        } while (flgC);
    L_0185B3:
        a = myMapper->readCPU(0x0354);
        opSBC(myMapper->readCPU(0x017E + y));
        if (flgC) {
            goto L_0185BD;
        }
        opEOR(0xFF);
    L_0185BD:
        opCMP(a, 0x30);
    } while (flgC);
    x = myMapper->readCPU(0x000D);
    pushAddress(0x85C5);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x85C5)) return;
    myMapper->writeCPU(0x000E, 0x19);
    a = 0x0D;
    SUB_01F447();
    return;
}

void game::SUB_0185CF() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_0185E9;
    }
    myMapper->writeCPU(0x004B, 0x0C);
    x = 0x09;
    pushAddress(0x85DC);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x85DC)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_0185EA;
    }
    a = myMapper->readCPU(0x016C + y);
    opORA(0x80);
    myMapper->writeCPU(0x016C + y, a);
L_0185E9:
    popAddress();
    return;
L_0185EA:
    pushAddress(0x85EC);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x85EC)) return;
    myMapper->writeCPU(0x054C + x, 0x3C);
    myMapper->writeCPU(0x000E, 0x14);
    a = 0x0F;
    SUB_01F447();
    return;
}

void game::SUB_0185FB() {
    if (myMapper->readCPU(0x002B) == 0) {
        goto L_01860B;
    }
    if (myMapper->readCPU(0x016C + y) != 0x01) {
        goto L_01860C;
    }
    myMapper->writeCPU(0x0184 + y, 0x09);
    do {
        do {
            do {
            L_01860B:
                popAddress();
                return;
            L_01860C:
                a = myMapper->readCPU(0x0184 + y);
                setLoadFlag(a);
            } while (!flgZ);
            myMapper->writeCPU(0x004B, 0x0C);
            x = 0x09;
            pushAddress(0x8619);
            SUB_01F41F();
            if (handleReturnAddress(poppedEntry.value, 0x8619)) return;
        } while (x == 0xFF);
        opCMP(myMapper->readCPU(0x046C), 0x04);
    } while (flgZ);
    myMapper->writeCPU(0x000D, x);
    a = 0xF8;
    y = myMapper->readCPU(0x0450);
    setLoadFlag(y);
    if (flgZ) {
        goto L_018630;
    }
    a = 0x08;
L_018630:
    myMapper->writeCPU(0x038C + x, a);
    a = y;
    opEOR(0x01);
    myMapper->writeCPU(0x0450 + x, a);
    y = myMapper->readCPU(0x000C);
    myMapper->writeCPU(0x0184 + y, 0x40);
    a = 0x01;
    y = 0x40;
    pushAddress(0x8646);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0x8646)) return;
    pushAddress(0x8649);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0x8649)) return;
    myMapper->writeCPU(0x04F8 + x, a);
    a = myMapper->readCPU(0x0354);
    opSBC(0x20);
    myMapper->writeCPU(0x0354 + x, a);
    opADC(0x20);
    myMapper->writeCPU(0x04DC + x, a);
    a = 0x06;
    pushAddress(0x865E);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x865E)) return;
    a = 0x12;
    SUB_01EF04();
    return;
}

void game::SUB_018664() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (!flgN) {
        goto L_01866A;
    }
    popAddress();
    return;
L_01866A:
    opORA(0x80);
    myMapper->writeCPU(0x016C + y, a);
    pushAddress(0x8671);
    SUB_01F470();
    if (handleReturnAddress(poppedEntry.value, 0x8671)) return;
    pushAddress(0x8674);
    SUB_01F4A9();
    if (handleReturnAddress(poppedEntry.value, 0x8674)) return;
    x = 0x07;
    do {
        opCMP(myMapper->readCPU(0x0434 + x), 0x1A);
        if (!flgZ) {
            goto L_018684;
        }
        opINX(1);
    } while (x < 0x09);
    popAddress();
    return;
L_018684:
    myMapper->writeCPU(0x000D, x);
    myMapper->writeCPU(0x0530 + x, y);
    myMapper->writeCPU(0x000E, 0x24);
    a = 0x1A;
    SUB_01F484();
    return;
}

void game::SUB_018693() {
    pushAddress(0x8695);
    SUB_01E8F0();
    if (handleReturnAddress(poppedEntry.value, 0x8695)) return;
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (flgZ) {
        myMapper->writeCPU(0x04C0, 0x04);
        myMapper->writeCPU(0x0514, 0x00);
        a = 0x14;
        myMapper->writeCPU(0x038C, a);
        myMapper->writeCPU(0x0040, a);
        a = 0xE0;
        myMapper->writeCPU(0x003F, a);
        myMapper->writeCPU(0x0354, a);
        pushAddress(0x86B4);
        SUB_01C59C();
        if (handleReturnAddress(poppedEntry.value, 0x86B4)) return;
        opINC(0x0019, 1);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x003D, 0x80);
    myMapper->writeCPU(0x003E, 0x00);
    a = 0x01;
    myMapper->writeCPU(0x0584, a);
    pushAddress(0x86C7);
    SUB_019C6F();
    if (handleReturnAddress(poppedEntry.value, 0x86C7)) return;
    a = 0x05;
    myMapper->writeCPU(0x003C, a);
    pushAddress(0x86CE);
    SUB_019D96();
    if (handleReturnAddress(poppedEntry.value, 0x86CE)) return;
    a = 0x01;
    pushAddress(0x86D3);
    SUB_01962D();
    if (handleReturnAddress(poppedEntry.value, 0x86D3)) return;
    a = myMapper->readCPU(0x0354);
    if (a == 0xB0) {
        goto L_0186DE;
    }
    SUB_01C5CF();
    return;
L_0186DE:
    a = 0xF4;
    y = 0x14;
    do {
        myMapper->writeCPU(0x0204 + y, a);
        opDEY(4);
    } while (!flgN);
    SUB_01C46B();
    return;
}

void game::SUB_0186EE() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (flgZ) {
        pushAddress(0x86F4);
        SUB_01CAA1();
        if (handleReturnAddress(poppedEntry.value, 0x86F4)) return;
        pushAddress(0x86F7);
        SUB_01D10E();
        if (handleReturnAddress(poppedEntry.value, 0x86F7)) return;
        pushAddress(0x86FA);
        SUB_01CB81();
        if (handleReturnAddress(poppedEntry.value, 0x86FA)) return;
        a = 0x00;
        myMapper->writeCPU(0x004A, a);
        myMapper->writeCPU(0x0032, a);
        myMapper->writeCPU(0x0033, a);
        myMapper->writeCPU(0x0034, 0x20);
        myMapper->writeCPU(0x038C, 0x50);
        myMapper->writeCPU(0x031C, 0x01);
        opINC(0x0019, 1);
        popAddress();
        return;
    }
    opDEX(1);
    if (flgZ) {
        pushAddress(0x8719);
        SUB_01C10D();
        if (handleReturnAddress(poppedEntry.value, 0x8719)) return;
        a = myMapper->readCPU(0x0032);
        opCMP(a, 0x08);
        if (!flgZ) {
            pushAddress(0x8722);
            SUB_0188ED();
            if (handleReturnAddress(poppedEntry.value, 0x8722)) return;
            opINC(0x0032, 1);
            popAddress();
            return;
        }
        a = 0x0B;
        pushAddress(0x872A);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0x872A)) return;
        opINC(0x0019, 1);
        a = 0x00;
        myMapper->writeCPU(0x001D, a);
        myMapper->writeCPU(0x0354, a);
        x = myMapper->readCPU(0x0020);
        myMapper->writeCPU(0x0700 + x, 0x01);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, 0x23);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, 0xC0);
        opINX(1);
        y = 0x40;
        do {
            a = 0x55;
            myMapper->writeCPU(0x0700 + x, a);
            opINX(1);
            opDEY(1);
        } while (!flgZ);
        SUB_01CC5F();
        return;
    }
    a = myMapper->readCPU(0x0354);
    flgC = true;
    opSBC(0xE0);
    opCMP(a, 0x10);
    if (!flgC) {
        pushAddress(0x8762);
        SUB_01C10D();
        if (handleReturnAddress(poppedEntry.value, 0x8762)) return;
        pushAddress(0x8765);
        SUB_01C31F();
        if (handleReturnAddress(poppedEntry.value, 0x8765)) return;
        pushAddress(0x8768);
        SUB_01C9EA();
        if (handleReturnAddress(poppedEntry.value, 0x8768)) return;
        a = 0x00;
        myMapper->writeCPU(0x003F, a);
        myMapper->writeCPU(0x0354, a);
        SUB_01CB81();
        return;
    }
    if (myMapper->readCPU(0x001D) == 0) {
        a = myMapper->readCPU(0x0354);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0354, a);
        if (a == 0x80) {
            myMapper->writeCPU(0x001D, 0x70);
        }
        popAddress();
        return;
    }
    opDEC(0x001D, 1);
    a = myMapper->readCPU(0x00FC);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x00FC, a);
    a = myMapper->readCPU(0x00FC);
    flgC = true;
    opSBC(0xF0);
    if (a >= 0x10) {
        goto L_01879F;
    }
    myMapper->writeCPU(0x00FC, 0x00);
L_01879F:
    popAddress();
}

void game::SUB_018867() {
    if (!(myMapper->readCPU(0x016C + y) & 0x80)) {
        goto L_01886D;
    }
    popAddress();
    return;
L_01886D:
    a = myMapper->readCPU(0x016C + y);
    opORA(0x80);
    myMapper->writeCPU(0x016C + y, a);
    x = 0x04;
    y = 0x5A;
    myMapper->writeCPU(0x004B, 0x0C);
    a = 0x14;
    do {
        pushAddress(0x8881);
        SUB_01F42C();
        if (handleReturnAddress(poppedEntry.value, 0x8881)) return;
        a = y;
        pushAddress(0x8885);
        SUB_01EF04();
        if (handleReturnAddress(poppedEntry.value, 0x8885)) return;
        a = 0x00;
        myMapper->writeCPU(0x04F8 + x, a);
        myMapper->writeCPU(0x0514 + x, a);
        myMapper->writeCPU(0x04DC + x, a);
        myMapper->writeCPU(0x0450 + x, 0x01);
        myMapper->writeCPU(0x0530 + x, myMapper->readCPU(0x004B));
        y = myMapper->readCPU(0x000C);
        a = myMapper->readCPU(0x0172 + y);
        flgC = true;
        opSBC(myMapper->readCPU(0x004B));
        myMapper->writeCPU(0x038C + x, a);
        myMapper->writeCPU(0x0354 + x, myMapper->readCPU(0x017E + y));
        y = 0x2E;
        myMapper->writeCPU(0x004B, 0x00);
        a = 0x15;
        opINX(1);
        opCMP(x, 0x0B);
    } while (!flgC);
    opDEX(1);
    myMapper->writeCPU(0x0434 + x, 0x16);
    myMapper->writeCPU(0x054C + x, 0x08);
    popAddress();
}

void game::SUB_0188C5() {
    pushAddress(0x88C7);
    SUB_01F48D();
    if (handleReturnAddress(poppedEntry.value, 0x88C7)) return;
    myMapper->writeCPU(0x000E, 0x25);
    a = 0x1C;
    pushAddress(0x88D0);
    SUB_01F484();
    if (handleReturnAddress(poppedEntry.value, 0x88D0)) return;
    x = 0x08;
    a = 0x1F;
    pushAddress(0x88D7);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0x88D7)) return;
    a = 0x4D;
    pushAddress(0x88DC);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0x88DC)) return;
    myMapper->writeCPU(0x0394, myMapper->readCPU(0x0393));
    a = myMapper->readCPU(0x035B);
    flgC = true;
    opSBC(0x18);
    myMapper->writeCPU(0x035C, a);
    popAddress();
}

void game::SUB_0188ED() {
    myMapper->writeCPU(0x0031, 0x00);
    do {
        a = myMapper->readCPU(0x0031);
        if (a == 0x04) {
            goto L_018915;
        }
        if (a != 0x02) {
            goto L_018901;
        }
        a = myMapper->readCPU(0x0032);
        if (a == 0x07) {
            goto L_018915;
        }
    L_018901:
        pushAddress(0x8903);
        SUB_018916();
        if (handleReturnAddress(poppedEntry.value, 0x8903)) return;
        a = myMapper->readCPU(0x0033);
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0033, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x0034));
        myMapper->writeCPU(0x0034, a);
        opINC(0x0031, 1);
    } while (!flgZ);
L_018915:
    popAddress();
}

void game::SUB_018916() {
    x = myMapper->readCPU(0x0020);
    myMapper->writeCPU(0x0700 + x, 0x01);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0034));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0033));
    opINX(1);
    myMapper->writeCPU(0x004B, 0xF3);
    myMapper->writeCPU(0x004F, 0x00);
    while (true) {
        a = myMapper->readCPU(0x004F);
        opCMP(a, 0x08);
        if (flgZ) {
            goto L_01895D;
        }
        a = myMapper->readCPU(0x0031);
        opASL_A(2);
        y = a;
        a = 0x05;
        myMapper->writeCPU(0x004C, a);
        while (true) {
            opDEC(0x004C, 1);
            if (flgZ) {
                goto L_018956;
            }
            a = myMapper->readCPU(0x004B);
            opAND(0x01);
            if (flgZ) {
                goto L_01894E;
            }
            a = myMapper->readCPU(0x8960 + y);
        L_01894E:
            myMapper->writeCPU(0x0700 + x, a);
            opINX(1);
            opINY(1);
        }
    L_018956:
        opINC(0x004F, 1);
        opLSR_M(0x004B, 1);
    }
L_01895D:
    SUB_01CC5F();
    return;
}

void game::SUB_0189F5() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_018A07;
    }
    myMapper->writeCPU(0x004B, 0x09);
    x = 0x07;
    pushAddress(0x8A02);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x8A02)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_018A08;
    }
L_018A07:
    popAddress();
    return;
L_018A08:
    myMapper->writeCPU(0x000D, x);
    pushAddress(0x8A0C);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x8A0C)) return;
    myMapper->writeCPU(0x000E, 0x15);
    a = 0x0A;
    SUB_01F447();
    return;
}

void game::SUB_018A16() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_018A28;
    }
    myMapper->writeCPU(0x004B, 0x0C);
    x = 0x09;
    pushAddress(0x8A23);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x8A23)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_018A29;
    }
L_018A28:
    popAddress();
    return;
L_018A29:
    pushAddress(0x8A2B);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x8A2B)) return;
    myMapper->writeCPU(0x054C + x, 0x3C);
    myMapper->writeCPU(0x000E, 0x2C);
    a = 0x13;
    pushAddress(0x8A39);
    SUB_01F447();
    if (handleReturnAddress(poppedEntry.value, 0x8A39)) return;
    myMapper->writeCPU(0x046C + x, 0x80);
    popAddress();
}

void game::SUB_018AA9() {
    pushAddress(0x8AAB);
    SUB_01F48D();
    if (handleReturnAddress(poppedEntry.value, 0x8AAB)) return;
    myMapper->writeCPU(0x000E, 0x23);
    a = 0x18;
    SUB_01F484();
    return;
}

void game::SUB_018AED() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_018AFF;
    }
    myMapper->writeCPU(0x004B, 0x07);
    x = 0x04;
    pushAddress(0x8AFA);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0x8AFA)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_018B00;
    }
L_018AFF:
    popAddress();
    return;
L_018B00:
    myMapper->writeCPU(0x000D, x);
    pushAddress(0x8B04);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0x8B04)) return;
    myMapper->writeCPU(0x054C + x, 0x3C);
    myMapper->writeCPU(0x000E, 0x4A);
    a = 0x1E;
    SUB_01F447();
    return;
}

void game::SUB_018B3B() {
    pushAddress(0x8B3D);
    SUB_01F48D();
    if (handleReturnAddress(poppedEntry.value, 0x8B3D)) return;
    myMapper->writeCPU(0x007A, 0x00);
    myMapper->writeCPU(0x000E, 0x23);
    a = 0x1D;
    SUB_01F484();
    return;
}

void game::SUB_018B4B() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_018B78;
    }
    //NOP
    //NOP
    //NOP
    pushAddress(0x8B54);
    SUB_01CAA1();
    if (handleReturnAddress(poppedEntry.value, 0x8B54)) return;
    a = 0x1E;
    myMapper->writeCPU(0x00FE, a);
    x = 0x00;
    pushAddress(0x8B5D);
    SUB_01CB83();
    if (handleReturnAddress(poppedEntry.value, 0x8B5D)) return;
    x = 0x08;
    pushAddress(0x8B62);
    SUB_01CB83();
    if (handleReturnAddress(poppedEntry.value, 0x8B62)) return;
    a = 0x17;
    pushAddress(0x8B67);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0x8B67)) return;
    a = myMapper->readCPU(0x00FF);
    opAND(0xFE);
    myMapper->writeCPU(0x00FF, a);
    opINC(0x0019, 1);
    myMapper->writeCPU(0x001D, 0x80);
    popAddress();
    return;
    do {
        SUB_018C22();
        return;
    L_018B78:
        opDEX(1);
    } while (!flgZ);
    opINC(0x0019, 1);
    pushAddress(0x8B7F);
    SUB_018C15();
    if (handleReturnAddress(poppedEntry.value, 0x8B7F)) return;
    a = 0x00;
    myMapper->writeCPU(0x0033, a);
    x = a;
    y = a;
    do {
        myMapper->writeCPU(0x0354 + y, myMapper->readCPU(0x8BC1 + x));
        opINX(1);
        myMapper->writeCPU(0x031C + y, myMapper->readCPU(0x8BC1 + x));
        opINX(1);
        myMapper->writeCPU(0x0338 + y, myMapper->readCPU(0x8BC1 + x));
        opINX(1);
        myMapper->writeCPU(0x038C + y, myMapper->readCPU(0x8BC1 + x));
        opINX(1);
        myMapper->writeCPU(0x0450 + y, myMapper->readCPU(0x8BC1 + x));
        opINX(1);
        opINY(1);
    } while (x != 0x14);
    x = 0x00;
    do {
        myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x8BD5 + x));
        opINX(1);
    } while (x != 0x40);
    myMapper->writeCPU(0x001A, 0xFF);
    popAddress();
}

void game::SUB_018C15() {
    myMapper->writeCPU(0x0032, 0x00);
    myMapper->writeCPU(0x0036, 0x20);
    myMapper->writeCPU(0x0037, 0xC2);
    popAddress();
}

void game::SUB_018C22() {
    opDEX(1);
    if (flgZ) {
        opDEC(0x001D, 1);
        if (flgZ) {
            opINC(0x0019, 1);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (flgZ) {
        a = myMapper->readCPU(0x001A);
        opAND(0x3F);
        if (flgZ) {
            a = 0x20;
            pushAddress(0x8C39);
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0x8C39)) return;
        }
        a = myMapper->readCPU(0x001A);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x038C);
            opEOR(0x01);
            myMapper->writeCPU(0x038C, a);
            myMapper->writeCPU(0x038D, a);
            myMapper->writeCPU(0x038E, a);
            myMapper->writeCPU(0x038F, a);
        }
        a = myMapper->readCPU(0x001A);
        opAND(0x07);
        if (flgZ) {
            opINC(0x0354, 1);
            opINC(0x0355, 1);
            opINC(0x0356, 1);
            opINC(0x0357, 1);
        }
        a = myMapper->readCPU(0x0354);
        if (a == 0x70) {
            opINC(0x0019, 1);
            myMapper->writeCPU(0x001D, 0x70);
            popAddress();
            return;
        }
        opAND(0x0F);
        if (flgZ) {
            a = myMapper->readCPU(0x0354);
            opLSR_A(4);
            opAND(0x0F);
            x = a;
            x = myMapper->readCPU(0x8C89 + x);
            myMapper->writeCPU(0x031C + x, 0x00);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (!flgZ) {
        goto L_018CB5;
    }
    opDEC(0x001D, 1);
    if (flgZ) {
        opINC(0x0019, 1);
        a = 0x45;
        pushAddress(0x8C9E);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0x8C9E)) return;
    }
    popAddress();
    return;
    do {
        goto L_018D44;
    L_018CB5:
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0033);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0034, myMapper->readCPU(0x8DCB + x));
    myMapper->writeCPU(0x0035, myMapper->readCPU(0x8DCC + x));
    x = myMapper->readCPU(0x0032);
    if (myMapper->readCPU(0x0033) == 0x09) {
        a = x;
        flgC = false;
        opADC(0x09);
        x = a;
    }
    a = myMapper->readCPU(0x8CA0 + x);
    myMapper->writeCPU(0x004F, a);
    opAND(0x03);
    myMapper->writeCPU(0x0000, a);
    opASL_A(4);
    y = a;
    myMapper->writeCPU(0x0000, 0x10);
    x = myMapper->readCPU(0x0020);
    myMapper->writeCPU(0x0700 + x, 0x01);
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0036));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x0037));
    opINX(1);
    do {
        myMapper->writeCPU(0x0001, myMapper->readCPU(myMapper->readCPU(0x0034) + (myMapper->readCPU((0x0034 + 1) & 0x00ff) << 8) + y));
        opCMP(myMapper->readCPU(0x004F), 0x04);
        if (flgZ) {
            goto L_018D40;
        }
        a = myMapper->readCPU(0x004F);
        opASL_A(1);
        if (flgC) {
            opCMP(myMapper->readCPU(0x0001), 0x54);
            if (flgZ) {
                goto L_018D10;
            }
            opINC(0x0001, 1);
        }
    L_018D10:
        a = myMapper->readCPU(0x0001);
    L_018D12:
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        opINY(1);
        opDEC(0x0000, 1);
    } while (!flgZ);
    pushAddress(0x8D1D);
    SUB_01CC5F();
    if (handleReturnAddress(poppedEntry.value, 0x8D1D)) return;
    a = myMapper->readCPU(0x0037);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0037, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x0036));
    myMapper->writeCPU(0x0036, a);
    opINC(0x0032, 1);
    a = myMapper->readCPU(0x0032);
    if (a != 0x09) {
        popAddress();
        return;
    }
    pushAddress(0x8D36);
    SUB_018C15();
    if (handleReturnAddress(poppedEntry.value, 0x8D36)) return;
    opINC(0x0033, 1);
    myMapper->writeCPU(0x0043, 0x00);
    opINC(0x0019, 1);
    popAddress();
    return;
L_018D40:
    a = 0x54;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_018D12;
    }
L_018D44:
    opDEX(1);
    if (flgZ) {
        opINC(0x0043, 1);
        pushAddress(0x8D4B);
        SUB_018D88();
        if (handleReturnAddress(poppedEntry.value, 0x8D4B)) return;
        if (myMapper->readCPU(0x0043) == 0x10) {
            if (myMapper->readCPU(0x0033) == 0x0B) {
                jump(0x8DC2);
                return;
            }
            opINC(0x0019, 1);
            myMapper->writeCPU(0x001D, 0xE2);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (flgZ) {
        opDEC(0x001D, 1);
        if (flgZ) {
            opINC(0x0019, 1);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (flgZ) {
        opDEC(0x0043, 1);
        pushAddress(0x8D70);
        SUB_018D88();
        if (handleReturnAddress(poppedEntry.value, 0x8D70)) return;
        if (myMapper->readCPU(0x0043) == 0) {
            opINC(0x0019, 1);
            myMapper->writeCPU(0x001D, 0x20);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (!flgZ) {
        SUB_018DB2();
        return;
    }
    opDEC(0x001D, 1);
    if (!flgZ) {
        goto L_018D87;
    }
    myMapper->writeCPU(0x0019, 0x05);
L_018D87:
    popAddress();
}

void game::SUB_018D88() {
    a = 0x17;
    pushAddress(0x8D8C);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0x8D8C)) return;
    a = myMapper->readCPU(0x0020);
    flgC = true;
    opSBC(0x14);
    x = a;
    a = myMapper->readCPU(0x0043);
    opLSR_A(1);
    opAND(0x0E);
    y = a;
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x8DA8 + y));
    opINX(1);
    myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0x8DA9 + y));
    popAddress();
}

void game::SUB_018DB2() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        SUB_018DCA();
        return;
    }
    opDEC(0x001D, 1);
    if (!flgZ) {
        SUB_018DCA();
        return;
    }
    pushAddress(0x8DBE);
    SUB_01CB81();
    if (handleReturnAddress(poppedEntry.value, 0x8DBE)) return;
    SUB_01C6C7();
    return;
}

void game::SUB_018DC2() {
    myMapper->writeCPU(0x0019, 0x0A);
    myMapper->writeCPU(0x001D, 0x90);
    SUB_018DCA();
    return;
}

void game::SUB_018DCA() {
    popAddress();
}

void game::SUB_01934C() {
    a = myMapper->readCPU(0x0047);
    setLoadFlag(a);
    if (flgZ) {
        SUB_019363();
        return;
    }
    opDEC(0x0047, 1);
    pushAddress(0x9354);
    SUB_019A5B();
    if (handleReturnAddress(poppedEntry.value, 0x9354)) return;
    myMapper->writeCPU(0x0049, 0x00);
    SUB_019359();
    return;
}

void game::SUB_019359() {
    x = myMapper->readCPU(0x0159);
    a = myMapper->readCPU(0x9BF1 + x);
    x = a;
    SUB_019BE3();
    return;
}

void game::SUB_019363() {
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
    SUB_01A1E5();
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
		callStack.pop_back();
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
        SUB_0193D9();
        return;
    }
    pushAddress(0x93C2);
    SUB_019E70();
    if (handleReturnAddress(poppedEntry.value, 0x93C2)) return;
    if (flgC) {
        SUB_0193D9();
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
            SUB_019458();
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
        SUB_019458();
        return;
    }
    a = 0x03;
    myMapper->writeCPU(0x046C, a);
    SUB_019A69();
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
    SUB_019BBA();
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
        SUB_01A1E5();
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
            SUB_019782();
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
            SUB_0193C5();
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
        SUB_019578();
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
        SUB_019583();
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
    SUB_019BBA();
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
    SUB_0193C5();
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
        SUB_01962C();
        return;
    }
    pushAddress(0x9602);
    SUB_019E70();
    if (handleReturnAddress(poppedEntry.value, 0x9602)) return;
    if (!flgC) {
        SUB_01962C();
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
    SUB_019AF8();
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
        SUB_0195E4();
        return;
    }
    a = y;
    SUB_019BBA();
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
        SUB_01962C();
        return;
    }
    a = myMapper->readCPU(0x003F);
    if (a >= 0xE0) {
        SUB_01A1E5();
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
    if (flgZ) {
        goto L_0196A0;
    }
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
L_0196A0:
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
        SUB_0196AD();
        return;
    }
    SUB_01A1E5();
    return;
}

void game::SUB_0196AD() {
    a = 0x30;
    myMapper->writeCPU(0x005B, a);
    pushAddress(0x96B3);
    SUB_019AF8();
    if (handleReturnAddress(poppedEntry.value, 0x96B3)) return;
    myMapper->writeCPU(0x046C, 0x09);
    a = 0x10;
    myMapper->writeCPU(0x054C, a);
    SUB_019A69();
    return;
}

void game::SUB_0196C1() {
    a = myMapper->readCPU(0x046C);
    if (a == 0x04) {
        myMapper->writeCPU(0x0047, 0x10);
        a = 0x30;
        myMapper->writeCPU(0x005B, a);
        popAddress();
        return;
    }
    pushAddress(0x96D3);
    SUB_019998();
    if (handleReturnAddress(poppedEntry.value, 0x96D3)) return;
    if (!flgC) {
        SUB_0196AD();
        return;
    }
    pushAddress(0x96D8);
    SUB_019A62();
    if (handleReturnAddress(poppedEntry.value, 0x96D8)) return;
    pushAddress(0x96DB);
    SUB_019AF8();
    if (handleReturnAddress(poppedEntry.value, 0x96DB)) return;
    myMapper->writeCPU(0x054C, 0x04);
    myMapper->writeCPU(0x04DC, myMapper->readCPU(0x9BA5));
    myMapper->writeCPU(0x04F8, myMapper->readCPU(0x9BA6));
    a = 0x00;
    myMapper->writeCPU(0x0514, a);
    myMapper->writeCPU(0x0488, a);
    myMapper->writeCPU(0x046C, 0x05);
    y = 0x01;
    x = myMapper->readCPU(0x004E);
    if (myMapper->readCPU(0x038C + x) < myMapper->readCPU(0x038C)) {
        goto L_019708;
    }
    y = 0x00;
L_019708:
    myMapper->writeCPU(0x0450, y);
    SUB_01970B();
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
    SUB_019605();
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
        SUB_01971D();
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
    SUB_019458();
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
        SUB_01977B();
        return;
    }
    pushAddress(0x9766);
    SUB_019E70();
    if (handleReturnAddress(poppedEntry.value, 0x9766)) return;
    if (flgC) {
        SUB_01977B();
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
    SUB_01A1E5();
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
        SUB_0197EA();
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
    SUB_019539();
    return;
L_019806:
    SUB_019578();
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
        SUB_0197EB();
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (!flgZ) {
        SUB_0197EA();
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
            SUB_0198AA();
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
        SUB_01990A();
        return;
    }
    a = myMapper->readCPU(0x003C);
    opAND(0x04);
    if (flgZ) {
        SUB_01990B();
        return;
    }
    SUB_0198B7();
    return;
}

void game::SUB_0198B7() {
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
        SUB_0198F3();
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
        SUB_0198FE();
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
    SUB_0198F3();
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
    SUB_019938();
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
        SUB_019A28();
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
        SUB_019A28();
        return;
    }
    a = myMapper->readCPU(0x00F5);
    opAND(0x40);
    if (flgZ) {
        SUB_019A28();
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
        SUB_019AE0();
        return;
    }
    a = myMapper->readCPU(0x0568);
    opCMP(a, 0x11);
    if (!flgZ) {
        SUB_019AE0();
        return;
    }
    a = myMapper->readCPU(0x015B);
    flgC = true;
    opSBC(0x08);
    SUB_01DA5F();
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
        SUB_019BE3();
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
        SUB_019C6D();
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
        SUB_019C6D();
        return;
    }
    a = myMapper->readCPU(0x0008);
    setLoadFlag(a);
    if (flgZ) {
        SUB_019C43();
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
        SUB_019DC0();
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
    SUB_019F56();
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
        SUB_019FE7();
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
    SUB_019FE7();
    return;
L_01A006:
    opDEC(0x0046, 1);
    a = 0x31;
    myMapper->writeCPU(0x003F, a);
    SUB_019FE7();
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
        SUB_01A037();
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

void game::SUB_01A038() {
    y = myMapper->readCPU(0x003F);
    x = myMapper->readCPU(0x0040);
    myMapper->writeCPU(0x0003, myMapper->readCPU(0x0041));
    myMapper->writeCPU(0x0011, 0x10);
    myMapper->writeCPU(0x0013, 0x08);
    SUB_01A048();
    return;
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
        SUB_01A037();
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
        SUB_01A0CD();
        return;
    }
    opCMP(myMapper->readCPU(0x0019), 0x06);
    if (!flgZ) {
        SUB_01A0CD();
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
        SUB_01A0CD();
        return;
    }
    pushAddress(0xA0B1);
    SUB_01A2AF();
    if (handleReturnAddress(poppedEntry.value, 0xA0B1)) return;
L_01A0B2:
    a = myMapper->readCPU(0x0043);
    opORA(myMapper->readCPU(0x0042));
    if (flgZ) {
        SUB_01A0CD();
        return;
    }
    if (myMapper->readCPU(0x0043) != 0) {
        jump(0xA0CD);
        return;
    }
    opCMP(myMapper->readCPU(0x0042), 0x30);
    if (flgC) {
        SUB_01A0CD();
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x3F);
    if (!flgZ) {
        SUB_01A0CD();
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
    a = myMapper->readCPU(0xA153 + x);
    myMapper->writeCPU(0x0241, a);
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
    a = myMapper->readCPU(0x0044);
    myMapper->writeCPU(0x004B, a);
    y = 0x67;
    myMapper->writeCPU(0x004F, y);
    SUB_01A23B();
    return;
}

void game::SUB_01A17D() {
    pushAddress(0xA17F);
    SUB_01CC7A();
    if (handleReturnAddress(poppedEntry.value, 0xA17F)) return;
    a = myMapper->readCPU(0x01A9);
    myMapper->writeCPU(0x01AA, a);
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
    a = 0x01;
    myMapper->writeCPU(0x0141, a);
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
    SUB_01CC5F();
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
    SUB_01C1A7();
    return;
}

void game::SUB_01A206() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        SUB_01A23A();
        return;
    }
    if (myMapper->readCPU(0x01A9) & 0x80) {
        myMapper->writeCPU(0x01A9, 0x00);
    }
    a = myMapper->readCPU(0x01AA);
    setLoadFlag(a);
    if (flgN) {
        SUB_01A23A();
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
    SUB_01CC5F();
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
    SUB_01CC5F();
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
    SUB_01CC5F();
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

void game::SUB_01A4AA() {
    myMapper->writeCPU(0x004E, 0x17);
    SUB_01A4AE();
    return;
}

void game::SUB_01A4AE() {
    x = myMapper->readCPU(0x004E);
    if (myMapper->readCPU(0x0434 + x) != 0x02) {
        jump(0xA4D7);
        return;
    }
    a = myMapper->readCPU(0x001A);
    opLSR_A(1);
    opAND(0x03);
    myMapper->writeCPU(0x0338 + x, a);
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0xA4C4);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xA4C4)) return;
    SUB_01A4D1();
    return;
}

void game::SUB_01A4D1() {
    pushAddress(0xA4D3);
    SUB_01A60E();
    if (handleReturnAddress(poppedEntry.value, 0xA4D3)) return;
    SUB_01A4D4();
    return;
}

void game::SUB_01A4D4() {
    pushAddress(0xA4D6);
    SUB_01A57D();
    if (handleReturnAddress(poppedEntry.value, 0xA4D6)) return;
    SUB_01A4D7();
    return;
}

void game::SUB_01A4D7() {
    opINC(0x004E, 1);
    if (myMapper->readCPU(0x004E) != 0x1C) {
        jump(0xA4AE);
        return;
    }
    popAddress();
}

void game::SUB_01A4E0() {
    pushAddress(0xA4E2);
    SUB_01A4E5();
    if (handleReturnAddress(poppedEntry.value, 0xA4E2)) return;
    if (flgZ) {
        SUB_01A4D7();
        return;
    }
    SUB_01A4E5();
    return;
}

void game::SUB_01A4E5() {
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x0354 + x, 0xF8);
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x031C + x, a);
    myMapper->writeCPU(0x046C + x, a);
    myMapper->writeCPU(0x0434 + x, a);
    popAddress();
}

void game::SUB_01A4F8() {
    x = myMapper->readCPU(0x004E);
    a = 0x10;
    myMapper->writeCPU(0x0488 + x, a);
    opINC(0x046C + x, 1);
    SUB_01A4D1();
    return;
}

void game::SUB_01A505() {
    pushAddress(0xA507);
    SUB_01A78C();
    if (handleReturnAddress(poppedEntry.value, 0xA507)) return;
    a = myMapper->readCPU(0x001A);
    opAND(0x03);
    if (!flgZ) {
        SUB_01A4D1();
        return;
    }
    x = myMapper->readCPU(0x004E);
    opDEC(0x0488 + x, 1);
    if (flgZ) {
        SUB_01A53F();
        return;
    }
    a = 0xFF;
    opDEC(0x03C4 + x, 1);
    pushAddress(0xA51C);
    SUB_01A52F();
    if (handleReturnAddress(poppedEntry.value, 0xA51C)) return;
    SUB_01A4D1();
    return;
}

void game::SUB_01A520() {
    myMapper->writeCPU(0x004C, x);
    opPHA();
    a = x;
    flgC = false;
    opADC(0x38);
    x = a;
    opPLA();
    pushAddress(0xA52B);
    SUB_01A52F();
    if (handleReturnAddress(poppedEntry.value, 0xA52B)) return;
    x = myMapper->readCPU(0x004C);
    popAddress();
}

void game::SUB_01A52F() {
    flgC = false;
    opADC(myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x03E0 + x, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x03C4 + x));
    myMapper->writeCPU(0x03C4 + x, a);
    popAddress();
}

void game::SUB_01A53F() {
    opINC(0x046C + x, 1);
    myMapper->writeCPU(0x0530 + x, 0x00);
    a = x;
    flgC = true;
    opSBC(0x17);
    opASL_A(3);
    x = a;
    x = a;
    a = 0xF8;
    myMapper->writeCPU(0x0207 + x, a);
    myMapper->writeCPU(0x020B + x, a);
    SUB_01A558();
    return;
}

void game::SUB_01A558() {
    SUB_01A4D1();
    return;
}

void game::SUB_01A55B() {
    pushAddress(0xA55D);
    SUB_01A78C();
    if (handleReturnAddress(poppedEntry.value, 0xA55D)) return;
    x = myMapper->readCPU(0x004E);
    opDEC(0x0530 + x, 1);
    if (!flgZ) {
        SUB_01A558();
        return;
    }
    pushAddress(0xA567);
    SUB_01A4E5();
    if (handleReturnAddress(poppedEntry.value, 0xA567)) return;
    if (flgZ) {
        SUB_01A558();
        return;
    }
    SUB_01A56A();
    return;
}

void game::SUB_01A56A() {
    SUB_01A558();
    return;
}

void game::SUB_01A56D() {
    x = myMapper->readCPU(0x004E);
    opDEC(0x0488 + x, 1);
    if (flgZ) {
        goto L_01A57A;
    }
    pushAddress(0xA576);
    SUB_01A7AD();
    if (handleReturnAddress(poppedEntry.value, 0xA576)) return;
    SUB_01A4D4();
    return;
L_01A57A:
    SUB_01A4E0();
    return;
}

void game::SUB_01A57D() {
    a = myMapper->readCPU(0x002E);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0000, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x002F));
    myMapper->writeCPU(0x0001, a);
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x0418 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0010, a);
    if (!flgC) {
        opINC(0x0001, 1);
    }
    a = myMapper->readCPU(0x03FC + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0001));
    if (flgZ) {
        a = myMapper->readCPU(0x0010);
        if (a >= 0xF0) {
            goto L_01A5D7;
        }
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x038C + x, a);
        myMapper->writeCPU(0x0354 + x, myMapper->readCPU(0x03E0 + x));
        if (myMapper->readCPU(0x046C + x) != 0x02) {
            goto L_01A5DC;
        }
        a = x;
        flgC = true;
        opSBC(0x17);
        opASL_A(3);
        y = a;
        myMapper->writeCPU(0x004F, a);
        pushAddress(0xA5C5);
        SUB_01A5ED();
        if (handleReturnAddress(poppedEntry.value, 0xA5C5)) return;
        a = 0xFE;
        myMapper->writeCPU(0x0205 + y, a);
        myMapper->writeCPU(0x0209 + y, a);
        a = 0x21;
        myMapper->writeCPU(0x0206 + y, a);
        myMapper->writeCPU(0x020A + y, a);
        popAddress();
        return;
    }
L_01A5D7:
    myMapper->writeCPU(0x031C + x, 0x00);
L_01A5DC:
    a = x;
    flgC = true;
    opSBC(0x17);
    opASL_A(3);
    x = a;
    a = 0xF8;
    myMapper->writeCPU(0x0207 + x, a);
    myMapper->writeCPU(0x020B + x, a);
    popAddress();
}

void game::SUB_01A5ED() {
    a = 0x0F;
    flgC = true;
    opSBC(myMapper->readCPU(0x0488 + x));
    flgC = false;
    opADC(myMapper->readCPU(0x0354 + x));
    opAND(0xF8);
    y = myMapper->readCPU(0x004F);
    myMapper->writeCPU(0x0204 + y, a);
    myMapper->writeCPU(0x0208 + y, a);
    a = myMapper->readCPU(0x038C + x);
    myMapper->writeCPU(0x0207 + y, a);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x020B + y, a);
    popAddress();
}

void game::SUB_01A60E() {
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x0418 + x));
    myMapper->writeCPU(0x0002, myMapper->readCPU(0x03FC + x));
    a = 0x06;
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xA627);
    SUB_01A038();
    if (handleReturnAddress(poppedEntry.value, 0xA627)) return;
    if (flgC) {
        goto L_01A639;
    }
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x046C + x, 0x05);
    a = 0x30;
    myMapper->writeCPU(0x0488 + x, a);
    pushAddress(0xA638);
    SUB_01A7BD();
    if (handleReturnAddress(poppedEntry.value, 0xA638)) return;
L_01A639:
    popAddress();
}

void game::SUB_01A63A() {
    a = myMapper->readCPU(0x0028);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0016, myMapper->readCPU(0xFC38 + x));
    myMapper->writeCPU(0x0017, myMapper->readCPU(0xFC39 + x));
    myMapper->writeCPU(0x004F, 0x00);
    SUB_01A64C();
    return;
}

void game::SUB_01A64C() {
    y = myMapper->readCPU(0x004F);
    if (myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y) != 0xFF) {
        myMapper->writeCPU(0x0000, 0x01);
        a = y;
        while (true) {
            flgC = true;
            opSBC(0x04);
            if (!flgC) {
                goto L_01A663;
            }
            opASL_M(0x0000, 1);
        }
    L_01A663:
        a = myMapper->readCPU(0x0144);
        opAND(myMapper->readCPU(0x0000));
        if (!flgZ) {
            SUB_01A685();
            return;
        }
        a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
        opAND(0x08);
        if (flgZ) {
            goto L_01A674;
        }
        a = myMapper->readCPU(0x002B);
        setLoadFlag(a);
        if (flgZ) {
            SUB_01A685();
            return;
        }
    L_01A674:
        a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
        opLSR_A(1);
        opAND(0x03);
        pushAddress(0xA67B);
        SUB_01CA6D();
        if (handleReturnAddress(poppedEntry.value, 0xA67B)) return;
    }
    popAddress();
}

void game::SUB_01A685() {
    SUB_01A708();
    return;
}

void game::SUB_01A688() {
    if (flgC) {
        SUB_01A685();
        return;
    }
    x = 0x17;
    do {
        if (myMapper->readCPU(0x0434 + x) != 0) {
            goto L_01A696;
        }
        if (myMapper->readCPU(0x046C + x) == 0) {
            goto L_01A69E;
        }
    L_01A696:
        opINX(1);
        a = x;
        opCMP(a, 0x1C);
    } while (!flgZ);
    if (flgZ) {
        SUB_01A685();
        return;
    }
L_01A69E:
    myMapper->writeCPU(0x0434 + x, 0x02);
    myMapper->writeCPU(0x046C + x, 0x01);
    y = myMapper->readCPU(0x004F);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    myMapper->writeCPU(0x03E0 + x, a);
    myMapper->writeCPU(0x03C4 + x, 0x00);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0x07);
    myMapper->writeCPU(0x03FC + x, a);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0xF8);
    myMapper->writeCPU(0x0418 + x, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    flgC = false;
    opADC(0x08);
    if (flgN) {
        opDEC(0x03C4 + x, 1);
    }
    pushAddress(0xA6D4);
    SUB_01A52F();
    if (handleReturnAddress(poppedEntry.value, 0xA6D4)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opASL_A(4);
    opROL_A(1);
    if (!flgC) {
        goto L_01A6E1;
    }
    opDEC(0x03FC + x, 1);
L_01A6E1:
    opROR_A(1);
    pushAddress(0xA6E4);
    SUB_01A520();
    if (handleReturnAddress(poppedEntry.value, 0xA6E4)) return;
    opINY(1);
    myMapper->writeCPU(0x0568 + x, myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0000, 0x01);
    a = myMapper->readCPU(0x004F);
    while (true) {
        flgC = true;
        opSBC(0x04);
        if (!flgC) {
            goto L_01A6FB;
        }
        opASL_M(0x0000, 1);
    }
L_01A6FB:
    a = myMapper->readCPU(0x0144);
    opORA(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0144, a);
    a = 0x23;
    SUB_01C1A7();
    return;
}

void game::SUB_01A708() {
    opINC(0x004F, 4);
    SUB_01A64C();
    return;
}

void game::SUB_01A713() {
    pushAddress(0xA715);
    SUB_01A764();
    if (handleReturnAddress(poppedEntry.value, 0xA715)) return;
    if (flgC) {
        SUB_01A723();
        return;
    }
    a = myMapper->readCPU(0x00F7);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01A71E();
        return;
    }
    if (flgZ) {
        SUB_01A746();
        return;
    }
    SUB_01A71E();
    return;
}

void game::SUB_01A71E() {
    a = 0x00;
    myMapper->writeCPU(0x0145, a);
    SUB_01A723();
    return;
}

void game::SUB_01A723() {
    flgC = true;
    SUB_01A724();
    return;
}

void game::SUB_01A724() {
    SUB_01A688();
    return;
}

void game::SUB_01A727() {
    pushAddress(0xA729);
    SUB_01A764();
    if (handleReturnAddress(poppedEntry.value, 0xA729)) return;
    if (flgC) {
        SUB_01A723();
        return;
    }
    a = myMapper->readCPU(0x00F7);
    opAND(0x04);
    if (flgZ) {
        SUB_01A723();
        return;
    }
    flgC = false;
    if (!flgC) {
        SUB_01A724();
        return;
    }
    SUB_01A735();
    return;
}

void game::SUB_01A735() {
    pushAddress(0xA737);
    SUB_01A764();
    if (handleReturnAddress(poppedEntry.value, 0xA737)) return;
    if (flgC) {
        SUB_01A723();
        return;
    }
    a = myMapper->readCPU(0x0142);
    opLSR_A(1);
    if (!flgC) {
        SUB_01A71E();
        return;
    }
    a = myMapper->readCPU(0x00F7);
    opAND(0x03);
    if (flgZ) {
        SUB_01A71E();
        return;
    }
    SUB_01A746();
    return;
}

void game::SUB_01A746() {
    a = myMapper->readCPU(0x001A);
    opAND(0x01);
    if (!flgZ) {
        SUB_01A723();
        return;
    }
    opINC(0x0145, 1);
    a = myMapper->readCPU(0x0145);
    if (a != 0x40) {
        jump(0xA723);
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x0145, a);
    flgC = false;
    if (!flgC) {
        SUB_01A724();
        return;
    }
    SUB_01A75E();
    return;
}

void game::SUB_01A75E() {
    pushAddress(0xA760);
    SUB_01A764();
    if (handleReturnAddress(poppedEntry.value, 0xA760)) return;
    SUB_01A724();
    return;
}

void game::SUB_01A764() {
    y = myMapper->readCPU(0x004F);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0x01);
    if (a != myMapper->readCPU(0x0046)) {
        goto L_01A78A;
    }
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    myMapper->writeCPU(0x0000, a);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0xF8);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y);
    opAND(0x07);
    myMapper->writeCPU(0x0002, a);
    a = 0x06;
    myMapper->writeCPU(0x0010, a);
    myMapper->writeCPU(0x0012, a);
    SUB_01A038();
    return;
L_01A78A:
    flgC = true;
    popAddress();
}

void game::SUB_01A78C() {
    a = myMapper->readCPU(0x0568 + x);
    if (a == 0x04) {
        goto L_01A79B;
    }
    y = a;
    a = myMapper->readCPU(0xA7A9 + y);
    myMapper->writeCPU(0x031C + x, a);
    popAddress();
    return;
L_01A79B:
    a = myMapper->readCPU(0x001A);
    opLSR_A(3);
    opAND(0x03);
    flgC = false;
    opADC(0xE1);
    myMapper->writeCPU(0x031C + x, a);
    popAddress();
}

void game::SUB_01A7AD() {
    y = myMapper->readCPU(0x0568 + x);
    a = myMapper->readCPU(0xA7B8 + y);
    myMapper->writeCPU(0x031C + x, a);
    popAddress();
}

void game::SUB_01A7BD() {
    a = myMapper->readCPU(0x0568 + x);
    if (a != 0x01) {
        goto L_01A7CE;
    }
    opINC(0x002A, 1);
    pushAddress(0xA7C8);
    SUB_01CC3D();
    if (handleReturnAddress(poppedEntry.value, 0xA7C8)) return;
    a = 0x25;
    SUB_01C1A7();
    return;
L_01A7CE:
    a = 0x10;
    pushAddress(0xA7D2);
    SUB_01A520();
    if (handleReturnAddress(poppedEntry.value, 0xA7D2)) return;
    x = myMapper->readCPU(0x0568 + x);
    a = myMapper->readCPU(0xA7F8 + x);
    myMapper->writeCPU(0x004B, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    y = a;
    myMapper->writeCPU(0x0003, myMapper->readCPU(0xA7FD + y));
    myMapper->writeCPU(0x0002, myMapper->readCPU(0xA7FE + y));
    a = myMapper->readCPU(0xA7FF + y);
    myMapper->writeCPU(0x0001, a);
    pushAddress(0xA7F2);
    SUB_01CAAF();
    if (handleReturnAddress(poppedEntry.value, 0xA7F2)) return;
    a = 0x17;
    SUB_01C1A7();
    return;
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
        SUB_01A824();
        return;
    }
    opASL_A(1);
    if (flgC) {
        SUB_01A824();
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
                        SUB_01A824();
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
        SUB_01EB6A();
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
    SUB_01AD4F();
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
        SUB_01AD68();
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
    SUB_019458();
    return;
L_01AE82:
    a = 0x11;
    SUB_019BBA();
    return;
}

void game::SUB_01AE87() {
    x = 0x01;
    SUB_01AD74();
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
    SUB_01C371();
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
        SUB_01B858();
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
        SUB_01B858();
        return;
    }
    opDEC(0x001E, 1);
    if (!flgZ) {
        SUB_01B858();
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
    SUB_01C37A();
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
        SUB_01C363();
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
    SUB_01CC95();
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
    SUB_01C37A();
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
        SUB_01C365();
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
    SUB_01C365();
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
    SUB_01C365();
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
            SUB_01C365();
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
    SUB_01C229();
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

    while (true) {
        repeat();
        wait(1);
        myConsole->ppu.signalNMI();
        myConsole->cpu.signal();
    }

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
        SUB_01C0C0();
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
    a = 0x00;
    myMapper->writeCPU(0x001B, a);
    SUB_01C0B9();
    return;
}

void game::SUB_01C0B9() {
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    brk();
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

    a = 0x00;
    myMapper->writeCPU(0x001B, a);

    SUB_01C0B9();
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
    SUB_01C1D8();
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
    SUB_01C371();
    return;
}

void game::SUB_01C232() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_01C255();
        return;
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
    SUB_01C241();
    return;
}

void game::SUB_01C241() {
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
    SUB_01C254();
    return;
}

void game::SUB_01C254() {
    popAddress();
}

void game::SUB_01C255() {
    opDEX(1);
    if (!flgZ) {
        SUB_01C299();
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
    if (a != 0x0F) {
        jump(0xC254);
        return;
    }
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
    SUB_01CED0();
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
        SUB_01C315();
        return;
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
}

void game::SUB_01C315() {
    a = 0x00;
    myMapper->writeCPU(0x015B, a);
    myMapper->writeCPU(0x0064, a);
    pushAddress(0xC31E);
    SUB_01C9EA();
    if (handleReturnAddress(poppedEntry.value, 0xC31E)) return;
    SUB_01C31F();
    return;
}

void game::SUB_01C31F() {
    myMapper->writeCPU(0x0019, 0x00);
    a = 0x05;
    myMapper->writeCPU(0x0018, a);
    myMapper->writeCPU(0x001F, a);
    SUB_01C98A();
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
    SUB_01C373();
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
        SUB_01C373();
        return;
    }
    SUB_01C382();
    return;
}

void game::SUB_01C382() {
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x12);
    if (!flgZ) {
        SUB_01C393();
        return;
    }
    SUB_01C388();
    return;
}

void game::SUB_01C388() {
    myMapper->writeCPU(0x0029, a);
    myMapper->writeCPU(0x0018, 0x0C);
    myMapper->writeCPU(0x0019, 0x08);
    popAddress();
}

void game::SUB_01C393() {
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
                SUB_01C365();
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
    SUB_01C46B();
    return;
}

void game::SUB_01C46B() {
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
        SUB_01C4AA();
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
        SUB_01C55D();
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
        SUB_01C575();
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
        SUB_01C52C();
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
        SUB_01C582();
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
        SUB_01C59B();
        return;
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
    SUB_01C593();
    return;
}

void game::SUB_01C593() {
    a = 0x05;
    pushAddress(0xC597);
    SUB_01C368();
    if (handleReturnAddress(poppedEntry.value, 0xC597)) return;
    SUB_01C994();
    return;
}

void game::SUB_01C59B() {
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

void game::SUB_01C5F5() {
    x = myMapper->readCPU(0x0019);
    setLoadFlag(x);
    if (flgZ) {
        pushAddress(0xC5FB);
        SUB_01D11B();
        if (handleReturnAddress(poppedEntry.value, 0xC5FB)) return;
        a = 0x00;
        myMapper->writeCPU(0x0047, a);
        myMapper->writeCPU(0x005B, a);
        myMapper->writeCPU(0x00F7, a);
        pushAddress(0xC606);
        jump(0x934C);
        if (handleReturnAddress(poppedEntry.value, 0xC606)) return;
        if (myMapper->readCPU(0x046C) == 0) {
        L_01C60C:
            myMapper->writeCPU(0x001D, 0x70);
            opINC(0x0019, 1);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (flgZ) {
        a = 0x00;
        myMapper->writeCPU(0x00F7, a);
        pushAddress(0xC61C);
        jump(0x934C);
        if (handleReturnAddress(poppedEntry.value, 0xC61C)) return;
        a = myMapper->readCPU(0x001A);
        opAND(0x01);
        if (flgZ) {
            opDEC(0x001D, 1);
            if (!flgZ) {
                goto L_01C656;
            }
            opINC(0x0019, 1);
        }
        popAddress();
        return;
    }
    opDEX(1);
    if (!flgZ) {
        goto L_01C657;
    }
    a = myMapper->readCPU(0x0042);
    opORA(myMapper->readCPU(0x0043));
    if (!flgZ) {
        myMapper->writeCPU(0x0002, 0x00);
        a = 0x10;
        myMapper->writeCPU(0x0001, a);
        pushAddress(0xC63D);
        SUB_01CAAB();
        if (handleReturnAddress(poppedEntry.value, 0xC63D)) return;
        a = myMapper->readCPU(0x001A);
        opAND(0x07);
        if (flgZ) {
            a = 0x03;
            pushAddress(0xC648);
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0xC648)) return;
        }
        jump(0xA2AF);
        return;
    }
    opINC(0x0019, 1);
    myMapper->writeCPU(0x001D, 0x30);
    myMapper->writeCPU(0x001A, 0x00);
    do {
        do {
        L_01C656:
            popAddress();
            return;
        L_01C657:
            opDEX(1);
            if (!flgZ) {
                goto L_01C683;
            }
            if (myMapper->readCPU(0x001D) == 0) {
                goto L_01C661;
            }
            opDEC(0x001D, 1);
            popAddress();
            return;
        L_01C661:
            a = myMapper->readCPU(0x001A);
            opAND(0x07);
        } while (!flgZ);
        a = myMapper->readCPU(0x0071);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01C680;
        }
        opDEC(0x0071, 1);
        pushAddress(0xC66F);
        jump(0xA1D0);
        if (handleReturnAddress(poppedEntry.value, 0xC66F)) return;
        myMapper->writeCPU(0x0002, 0x01);
        a = 0x00;
        myMapper->writeCPU(0x0001, a);
        pushAddress(0xC67A);
        SUB_01CAAB();
        if (handleReturnAddress(poppedEntry.value, 0xC67A)) return;
        a = 0x04;
        SUB_01C1A7();
        return;
    L_01C680:
        goto L_01C60C;
    L_01C683:
        opDEX(1);
        if (!flgZ) {
            SUB_01C6D0();
            return;
        }
        opDEC(0x001D, 1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x12);
    if (!flgZ) {
        goto L_01C698;
    }
    pushAddress(0xC692);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC692)) return;
    myMapper->writeCPU(0x0019, 0x0A);
    popAddress();
    return;
L_01C698:
    opINC(0x0028, 1);
    a = 0x02;
    pushAddress(0xC69E);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xC69E)) return;
    a = myMapper->readCPU(0x0028);
    myMapper->writeCPU(0x0029, a);
    pushAddress(0xC6A5);
    SUB_01CAA1();
    if (handleReturnAddress(poppedEntry.value, 0xC6A5)) return;
    pushAddress(0xC6A8);
    SUB_01C5B0();
    if (handleReturnAddress(poppedEntry.value, 0xC6A8)) return;
    pushAddress(0xC6AB);
    SUB_01CB81();
    if (handleReturnAddress(poppedEntry.value, 0xC6AB)) return;
    a = 0x14;
    myMapper->writeCPU(0x0028, a);
    pushAddress(0xC6B2);
    SUB_01C98A();
    if (handleReturnAddress(poppedEntry.value, 0xC6B2)) return;
    pushAddress(0xC6B5);
    SUB_01CFB1();
    if (handleReturnAddress(poppedEntry.value, 0xC6B5)) return;
    pushAddress(0xC6B8);
    SUB_01C241();
    if (handleReturnAddress(poppedEntry.value, 0xC6B8)) return;
    x = myMapper->readCPU(0x0029);
    myMapper->writeCPU(0x0028, x);
    pushAddress(0xC6BF);
    jump(0xA296);
    if (handleReturnAddress(poppedEntry.value, 0xC6BF)) return;
    myMapper->writeCPU(0x0028, 0x14);
    opINC(0x0019, 1);
    popAddress();
}

void game::SUB_01C6C7() {
    opINC(0x002B, 1);
    a = 0x00;
    myMapper->writeCPU(0x0028, a);
    SUB_01C388();
    return;
}

void game::SUB_01C6D0() {
    opDEX(1);
    if (flgZ) {
        pushAddress(0xC6D5);
        jump(0xA17D);
        if (handleReturnAddress(poppedEntry.value, 0xC6D5)) return;
        SUB_01C365();
        return;
    }
    opDEX(1);
    if (!flgZ) {
        goto L_01C70F;
    }
    pushAddress(0xC6DE);
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xC6DE)) return;
    y = 0x04;
    pushAddress(0xC6E3);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xC6E3)) return;
    pushAddress(0xC6E6);
    SUB_01C216();
    if (handleReturnAddress(poppedEntry.value, 0xC6E6)) return;
    pushAddress(0xC6E9);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xC6E9)) return;
    pushAddress(0xC6EC);
    SUB_01C102();
    if (handleReturnAddress(poppedEntry.value, 0xC6EC)) return;
    a = myMapper->readCPU(0x001D);
    if (a != 0x0F) {
        popAddress();
        return;
    }
    pushAddress(0xC6F6);
    SUB_01C98A();
    if (handleReturnAddress(poppedEntry.value, 0xC6F6)) return;
    pushAddress(0xC6F9);
    SUB_01C28E();
    if (handleReturnAddress(poppedEntry.value, 0xC6F9)) return;
    pushAddress(0xC6FC);
    SUB_01CFB1();
    if (handleReturnAddress(poppedEntry.value, 0xC6FC)) return;
    myMapper->writeCPU(0x038C, 0x10);
    a = 0xB0;
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x0354, a);
    SUB_01C365();
    return;
    do {
        SUB_01C7E2();
        return;
    L_01C70F:
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x003C, 0x01);
    myMapper->writeCPU(0x003D, 0x80);
    myMapper->writeCPU(0x003E, 0x01);
    a = myMapper->readCPU(0x002F);
    setLoadFlag(a);
    if (!flgZ) {
        x = 0x00;
        a = myMapper->readCPU(0x0029);
        if (a >= 0x08) {
            x = 0x80;
        }
        opCMP(x, myMapper->readCPU(0x002E));
        if (flgZ) {
            goto L_01C73F;
        }
    }
    pushAddress(0xC732);
    jump(0x990B);
    if (handleReturnAddress(poppedEntry.value, 0xC732)) return;
    y = 0x04;
    pushAddress(0xC737);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xC737)) return;
    pushAddress(0xC73A);
    SUB_01F5EA();
    if (handleReturnAddress(poppedEntry.value, 0xC73A)) return;
    pushAddress(0xC73D);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xC73D)) return;
    popAddress();
    return;
L_01C73F:
    pushAddress(0xC741);
    SUB_01C766();
    if (handleReturnAddress(poppedEntry.value, 0xC741)) return;
    opCMP(myMapper->readCPU(0x038C), 0xF0);
    if (!flgZ) {
        a = myMapper->readCPU(0x001A);
        opAND(0x0F);
        if (!flgZ) {
            goto L_01C754;
        }
        a = 0x06;
        pushAddress(0xC753);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0xC753)) return;
    L_01C754:
        opINC(0x038C, 1);
        x = 0x00;
        myMapper->writeCPU(0x0450, x);
        opINX(1);
        myMapper->writeCPU(0x0584, x);
        jump(0x9458);
        return;
    }
    opINC(0x0019, 1);
    popAddress();
}

void game::SUB_01C766() {
    x = 0x00;
    myMapper->writeCPU(0x034F, x);
    myMapper->writeCPU(0x0350, x);
    myMapper->writeCPU(0x0317, x);
    myMapper->writeCPU(0x0318, x);
    y = myMapper->readCPU(0x0029);
    a = 0x03;
    myMapper->writeCPU(0x0003, a);
    pushAddress(0xC77C);
    SUB_01CA41();
    if (handleReturnAddress(poppedEntry.value, 0xC77C)) return;
    a = myMapper->readCPU(0x0002);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x036B, myMapper->readCPU(0xC7C7 + x));
    opINX(1);
    myMapper->writeCPU(0x03A3, myMapper->readCPU(0xC7C7 + x));
    a = myMapper->readCPU(0x001A);
    opLSR_A(3);
    opAND(0x01);
    if (!flgZ) {
        a = 0xD6;
    }
    myMapper->writeCPU(0x0333, a);
    a = myMapper->readCPU(0x0002);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x036C, myMapper->readCPU(0xC7D3 + x));
    opINX(1);
    myMapper->writeCPU(0x03A4, myMapper->readCPU(0xC7D3 + x));
    a = myMapper->readCPU(0x001A);
    opLSR_A(3);
    opAND(0x01);
    myMapper->writeCPU(0x004B, a);
    a = 0xD7;
    y = myMapper->readCPU(0x0029);
    if (y != 0x10) {
        goto L_01C7C0;
    }
    a = 0xD9;
L_01C7C0:
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x0334, a);
    popAddress();
}

void game::SUB_01C7DF() {
    SUB_01C829();
    return;
}

void game::SUB_01C7E2() {
    opDEX(1);
    if (!flgZ) {
        SUB_01C7DF();
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x004A, a);
    myMapper->writeCPU(0x0333, a);
    myMapper->writeCPU(0x0334, a);
    myMapper->writeCPU(0x0144, a);
    myMapper->writeCPU(0x0146, a);
    x = myMapper->readCPU(0x0029);
    myMapper->writeCPU(0x0028, x);
    a = myMapper->readCPU(0xC8B0 + x);
    pushAddress(0xC7FE);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xC7FE)) return;
    a = 0x0B;
    x = myMapper->readCPU(0x0028);
    setLoadFlag(x);
    if (!flgZ) {
        opCMP(x, 0x12);
        if (flgZ) {
            a = 0x0C;
        }
    }
    pushAddress(0xC80D);
    SUB_01D11B();
    if (handleReturnAddress(poppedEntry.value, 0xC80D)) return;
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x0A);
    if (flgZ) {
        goto L_01C81E;
    }
    opCMP(a, 0x12);
    if (flgZ) {
        goto L_01C826;
    }
    pushAddress(0xC81A);
    SUB_01C9EA();
    if (handleReturnAddress(poppedEntry.value, 0xC81A)) return;
    SUB_01C31F();
    return;
L_01C81E:
    pushAddress(0xC820);
    SUB_01C9EA();
    if (handleReturnAddress(poppedEntry.value, 0xC820)) return;
    a = 0x0E;
    SUB_01C368();
    return;
L_01C826:
    SUB_01C593();
    return;
}

void game::SUB_01C829() {
    opDEX(1);
    if (!flgZ) {
        goto L_01C836;
    }
    a = 0x01;
    a = 0x03;
    pushAddress(0xC832);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xC832)) return;
    opDEC(0x0019, 1);
    popAddress();
    return;
L_01C836:
    a = 0x08;
    a = 0x0A;
    pushAddress(0xC83C);
    SUB_01FD23();
    if (handleReturnAddress(poppedEntry.value, 0xC83C)) return;
    a = 0x55;
    pushAddress(0xC841);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xC841)) return;
    a = 0x0F;
    SUB_01C368();
    return;
}

void game::SUB_01C847() {
    a = myMapper->readCPU(0x00F5);
    opAND(0x10);
    if (flgZ) {
        a = myMapper->readCPU(0x00F5);
        opAND(0x20);
        if (flgZ) {
            goto L_01C89C;
        }
        a = 0x04;
        pushAddress(0xC857);
        SUB_01C1A7();
        if (handleReturnAddress(poppedEntry.value, 0xC857)) return;
        x = myMapper->readCPU(0x07F1);
        opINX(1);
        a = x;
        opAND(0x01);
        myMapper->writeCPU(0x07F1, a);
        flgC = false;
        opADC(0x2C);
        SUB_01CC95();
        return;
    }
    x = myMapper->readCPU(0x0028);
    myMapper->writeCPU(0x0028, myMapper->readCPU(0xC89D + x));
    if (myMapper->readCPU(0x07F1) != 0) {
        goto L_01C895;
    }
    myMapper->writeCPU(0x002A, 0x04);
    myMapper->writeCPU(0x002C, 0x03);
    a = 0x00;
    myMapper->writeCPU(0x0064, a);
    myMapper->writeCPU(0x01AB, a);
    myMapper->writeCPU(0x07FC, a);
    myMapper->writeCPU(0x07FD, a);
    myMapper->writeCPU(0x07FE, a);
    myMapper->writeCPU(0x07FF, a);
    pushAddress(0xC891);
    SUB_01C10D();
    if (handleReturnAddress(poppedEntry.value, 0xC891)) return;
    SUB_01C315();
    return;
L_01C895:
    a = 0x00;
    myMapper->writeCPU(0x0018, a);
    myMapper->writeCPU(0x0019, a);
    popAddress();
    return;
L_01C89C:
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
        SUB_01C90D();
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
    SUB_01C903();
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
        SUB_01C37A();
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
    SUB_01C371();
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
    a = myMapper->readCPU(0xC9F6 + x);
    myMapper->writeCPU(0x0043, a);
    popAddress();
}

void game::SUB_01CA38() {
    pushAddress(0xCA3A);
    SUB_01C132();
    if (handleReturnAddress(poppedEntry.value, 0xCA3A)) return;
    pushAddress(0xCA3D);
    SUB_01C16D();
    if (handleReturnAddress(poppedEntry.value, 0xCA3D)) return;
    SUB_01C102();
    return;
}

void game::SUB_01CA41() {
    myMapper->writeCPU(0x0000, x);
    myMapper->writeCPU(0x0001, y);
    myMapper->writeCPU(0x0002, 0x00);
    if (!(myMapper->readCPU(0x0003) & 0x80)) {
        goto L_01CA55;
    }
    opLSR_M(0x0000, 1);
    opROR_M(0x0001, 1);
    opROR_M(0x0002, 1);
    opLSR_M(0x0003, 1);
L_01CA55:
    a = 0x00;
    x = 0x11;
    flgC = false;
    do {
        do {
            opROL_M(0x0002, 1);
            opROL_M(0x0001, 1);
            opROL_M(0x0000, 1);
            opDEX(1);
            if (flgZ) {
                goto L_01CA6C;
            }
            opROL_A(1);
            opCMP(a, myMapper->readCPU(0x0003));
        } while (!flgC);
        opSBC(myMapper->readCPU(0x0003));
    } while (flgC);
L_01CA6C:
    popAddress();
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
    callStack.pop_back();
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
    SUB_01C176();
    return;
}

void game::SUB_01CAAB() {
    myMapper->writeCPU(0x0003, 0x00);
    SUB_01CAAF();
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
        SUB_01CB11();
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
    SUB_01F69E();
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
    SUB_01C102();
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
    SUB_01CC5F();
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
        SUB_01CC5F();
        return;
    }
    myMapper->writeCPU(0x0004, x);
    pushAddress(0xCC90);
    SUB_01CC95();
    if (handleReturnAddress(poppedEntry.value, 0xCC90)) return;
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01CCA0();
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
                SUB_01CCF6();
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
            SUB_01CCF2();
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
        SUB_01CCF0();
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
        SUB_01FAEF();
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
        SUB_01CF50();
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
        SUB_01CF50();
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
        SUB_01CF50();
        return;
    }
    a = 0x01;
    myMapper->writeCPU(0x0022, a);
    pushAddress(0xCF40);
    jump(0x9359);
    if (handleReturnAddress(poppedEntry.value, 0xCF40)) return;
    a = 0x54;
    SUB_01C1A7();
    return;
L_01CF46:
    a = myMapper->readCPU(0x00F5);
    opAND(0x10);
    if (flgZ) {
        SUB_01CF50();
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
    SUB_01CFB1();
    return;
}

void game::SUB_01CFB1() {
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
    SUB_01CC95();
    return;
}

void game::SUB_01D11B() {
    a = 0x06;
    SUB_01CC95();
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
            SUB_01D195();
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
        SUB_01D195();
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
            opCMP(a, 0xFE);
            if (!flgZ) {
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
    SUB_01DA72();
    return;
}

void game::SUB_01DA72() {
    pushAddress(0xDA74);
    SUB_01DA90();
    if (handleReturnAddress(poppedEntry.value, 0xDA74)) return;
    y = 0x17;
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_01DABC();
        return;
    }
    SUB_01DA7B();
    return;
}

void game::SUB_01DA7B() {
    a = myMapper->readCPU(0x0071);
    flgC = true;
    opSBC(0x05);
    if (flgN) {
        SUB_01DA9D();
        return;
    }
    y = a;
    goto L_01DA8B;
L_01DA8B:
    myMapper->writeCPU(0x0071, y);
    jump(0xA1D0);
    return;
}

void game::SUB_01DA90() {
    y = myMapper->readCPU(0x0064);
    x = 0x14;
    do {
        a = myMapper->readCPU(0x0434 + x);
        setLoadFlag(a);
        if (flgZ) {
            SUB_01DAA0();
            return;
        }
        opINX(1);
        opDEY(1);
    } while (!flgN);
    SUB_01DA9D();
    return;
}

void game::SUB_01DA9D() {
    opPLA();
    opPLA();
    callStack.pop_back();
    popAddress();
}

void game::SUB_01DAA0() {
    myMapper->writeCPU(0x004E, x);
    popAddress();
}

void game::SUB_01DAA3() {
    pushAddress(0xDAA5);
    SUB_01DA90();
    if (handleReturnAddress(poppedEntry.value, 0xDAA5)) return;
    y = 0x40;
    a = 0x03;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01DABC();
        return;
    }
    SUB_01DAAC();
    return;
}

void game::SUB_01DAAC() {
    pushAddress(0xDAAE);
    SUB_01DA90();
    if (handleReturnAddress(poppedEntry.value, 0xDAAE)) return;
    y = 0x41;
    a = 0x01;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01DABC();
        return;
    }
    SUB_01DAB5();
    return;
}

void game::SUB_01DAB5() {
    pushAddress(0xDAB7);
    SUB_01DA90();
    if (handleReturnAddress(poppedEntry.value, 0xDAB7)) return;
    y = 0x16;
    a = 0x05;
    SUB_01DABC();
    return;
}

void game::SUB_01DABC() {
    x = myMapper->readCPU(0x004E);
    opPHA();
    a = 0x17;
    pushAddress(0xDAC3);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0xDAC3)) return;
    opPLA();
    myMapper->writeCPU(0x0584 + x, a);
    myMapper->writeCPU(0x0450 + x, myMapper->readCPU(0x0450));
    myMapper->writeCPU(0x038C + x, myMapper->readCPU(0x038C));
    a = myMapper->readCPU(0x0354);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0354 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x04DC + x, a);
    myMapper->writeCPU(0x04F8 + x, a);
    a = y;
    SUB_01EF04();
    return;
}

void game::SUB_01DAE9() {
    pushAddress(0xDAEB);
    SUB_01DA90();
    if (handleReturnAddress(poppedEntry.value, 0xDAEB)) return;
    pushAddress(0xDAEE);
    SUB_01DA7B();
    if (handleReturnAddress(poppedEntry.value, 0xDAEE)) return;
    y = 0x23;
    a = 0x07;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01DABC();
        return;
    }
    SUB_01DAF5();
    return;
}

void game::SUB_01DAF5() {
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x038C + x, myMapper->readCPU(0x038C));
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01DB0B;
    }
    a = myMapper->readCPU(0x005B);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01DB20();
        return;
    }
    x = myMapper->readCPU(0x004E);
    SUB_01EC60();
    return;
L_01DB0B:
    a = 0x1B;
    pushAddress(0xDB0F);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xDB0F)) return;
    y = 0x05;
    pushAddress(0xDB14);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xDB14)) return;
    myMapper->writeCPU(0x005B, 0xB4);
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x046C + x, 0x01);
    SUB_01DB20();
    return;
}

void game::SUB_01DB20() {
    popAddress();
}

void game::SUB_01DB21() {
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x038C + x, myMapper->readCPU(0x038C));
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opDEC(0x0568 + x, 1);
        if (!flgZ) {
            SUB_01DB20();
            return;
        }
        y = 0x04;
        do {
            if (myMapper->readCPU(0x0434 + y) == 0) {
                goto L_01DB42;
            }
            a = myMapper->readCPU(0x0488 + y);
            opAND(0x7F);
            myMapper->writeCPU(0x0488 + y, a);
        L_01DB42:
            opINY(1);
        } while (y < 0x0E);
        a = 0x00;
        myMapper->writeCPU(0x054C + x, a);
        SUB_01EC60();
        return;
    }
    a = 0x1A;
    pushAddress(0xDB53);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xDB53)) return;
    y = 0x05;
    pushAddress(0xDB58);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xDB58)) return;
    x = myMapper->readCPU(0x004E);
    y = 0x04;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_01DB6A;
        }
        a = myMapper->readCPU(0x0488 + y);
        opORA(0x80);
        myMapper->writeCPU(0x0488 + y, a);
    L_01DB6A:
        opINY(1);
        opCMP(y, 0x0E);
    } while (!flgC);
    if (myMapper->readCPU(0x0048) != 0) {
        a = myMapper->readCPU(0x0028);
        opCMP(a, 0x03);
        if (!flgZ) {
            opCMP(a, 0x06);
            if (flgZ) {
                goto L_01DB81;
            }
            a = 0x08;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_01DB83;
            }
        }
    }
L_01DB81:
    a = 0xB4;
L_01DB83:
    myMapper->writeCPU(0x0568 + x, a);
    a = 0xFF;
    y = 0x01;
    SUB_01ED34();
    return;
}

void game::SUB_01DB8D() {
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01DB95;
    }
    SUB_01EE48();
    return;
L_01DB95:
    myMapper->writeCPU(0x046C + x, 0x01);
    y = 0x00;
    a = 0x04;
    SUB_01EC72();
    return;
}

void game::SUB_01DBA1() {
    do {
        do {
            y = myMapper->readCPU(0x0584 + x);
            setLoadFlag(y);
            if (flgZ) {
                SUB_01DB8D();
                return;
            }
            opDEY(1);
            if (!flgZ) {
                goto L_01DBAC;
            }
            SUB_01DC5F();
            return;
        L_01DBAC:
            opDEY(1);
        } while (flgZ);
        opDEY(1);
        if (flgZ) {
            goto L_01DBC5;
        }
        opDEY(1);
    } while (flgZ);
    opDEY(1);
    if (flgZ) {
        SUB_01DCCA();
        return;
    }
    opDEY(1);
    if (!flgZ) {
        opDEY(1);
        SUB_01DB21();
        return;
    }
    SUB_01DAF5();
    return;
L_01DBC5:
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01DBD0;
    }
    opDEY(1);
    if (flgZ) {
        SUB_01DBE6();
        return;
    }
    SUB_01EB5A();
    return;
L_01DBD0:
    a = 0x01;
    myMapper->writeCPU(0x03FC + x, a);
    myMapper->writeCPU(0x03C4 + x, a);
    a = 0x80;
    myMapper->writeCPU(0x0418 + x, a);
    myMapper->writeCPU(0x03E0 + x, a);
    myMapper->writeCPU(0x046C + x, 0x01);
    SUB_01DBE5();
    return;
}

void game::SUB_01DBE5() {
    popAddress();
}

void game::SUB_01DBE6() {
    pushAddress(0xDBE8);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0xDBE8)) return;
    pushAddress(0xDBEB);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0xDBEB)) return;
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0xDBF7);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0xDBF7)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        jump(0xDBE5);
        return;
    }
    myMapper->writeCPU(0x004E, x);
    a = 0x1E;
    pushAddress(0xDC02);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xDC02)) return;
    y = 0x05;
    pushAddress(0xDC07);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xDC07)) return;
    x = myMapper->readCPU(0x004E);
    pushAddress(0xDC0C);
    SUB_01EFAF();
    if (handleReturnAddress(poppedEntry.value, 0xDC0C)) return;
    myMapper->writeCPU(0x0568 + x, 0x4C);
    myMapper->writeCPU(0x046C + x, 0x02);
    a = 0x4C;
    SUB_01EF04();
    return;
}

void game::SUB_01DC1C() {
    pushAddress(0xDC1E);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0xDC1E)) return;
    pushAddress(0xDC21);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0xDC21)) return;
    opCMP(a, 0x08);
    if (flgC) {
        SUB_01DBE5();
        return;
    }
    a = myMapper->readCPU(0x0354 + x);
    opSBC(myMapper->readCPU(0x0354));
    if (flgC) {
        goto L_01DC30;
    }
    opEOR(0xFF);
L_01DC30:
    if (a >= 0x10) {
        jump(0xDBE5);
        return;
    }
    SUB_01EC60();
    return;
}

void game::SUB_01DC37() {
    a = myMapper->readCPU(0x0418 + x);
    opADC(0x20);
    myMapper->writeCPU(0x0418 + x, a);
    a = myMapper->readCPU(0x03FC + x);
    opADC(0x00);
    myMapper->writeCPU(0x03FC + x, a);
    opCMP(a, 0x02);
    if (!flgC) {
        SUB_01DC5C();
        return;
    }
    myMapper->writeCPU(0x04DC + x, 0x00);
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
    SUB_01F131();
    return;
}

void game::SUB_01DC5C() {
    SUB_01EE48();
    return;
}

void game::SUB_01DC5F() {
    myMapper->writeCPU(0x004E, x);
    a = myMapper->readCPU(0x046C + x);
    setLoadFlag(a);
    if (!flgZ) {
        y = myMapper->readCPU(0x04A4 + x);
        opDEY(1);
        if (flgZ) {
            a = 0x07;
            pushAddress(0xDC70);
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0xDC70)) return;
            y = 0x05;
            pushAddress(0xDC75);
            SUB_01C1D6();
            if (handleReturnAddress(poppedEntry.value, 0xDC75)) return;
            x = myMapper->readCPU(0x004E);
        }
    }
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (!flgZ) {
        opDEY(1);
        if (flgZ) {
            goto L_01DC9A;
        }
        opDEY(1);
        if (flgZ) {
            goto L_01DCA7;
        }
        opDEY(1);
        if (flgZ) {
            SUB_01DC37();
            return;
        }
        SUB_01DC1C();
        return;
    }
    myMapper->writeCPU(0x0568 + x, 0x40);
    myMapper->writeCPU(0x046C + x, 0x01);
    y = 0x00;
    a = 0x02;
    SUB_01EC72();
    return;
L_01DC9A:
    opDEC(0x0568 + x, 1);
    if (!flgZ) {
        goto L_01DCA4;
    }
    a = 0x02;
    myMapper->writeCPU(0x046C + x, a);
    while (true) {
        do {
        L_01DCA4:
            SUB_01EE48();
            return;
        L_01DCA7:
            a = myMapper->readCPU(0x0418 + x);
            opSBC(0x20);
            myMapper->writeCPU(0x0418 + x, a);
            a = myMapper->readCPU(0x03FC + x);
            opSBC(0x00);
            myMapper->writeCPU(0x03FC + x, a);
        } while (!flgN);
        a = 0x00;
        y = a;
        pushAddress(0xDCBE);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0xDCBE)) return;
        pushAddress(0xDCC1);
        SUB_01EAA9();
        if (handleReturnAddress(poppedEntry.value, 0xDCC1)) return;
        a = 0x03;
        myMapper->writeCPU(0x046C + x, a);
    }
    SUB_01DCCA();
    return;
}

void game::SUB_01DCCA() {
    myMapper->writeCPU(0x004E, x);
    a = myMapper->readCPU(0x046C + x);
    setLoadFlag(a);
    if (!flgZ) {
        y = myMapper->readCPU(0x04A4 + x);
        opDEY(1);
        if (flgZ) {
            a = 0x09;
            pushAddress(0xDCDB);
            SUB_01C1A7();
            if (handleReturnAddress(poppedEntry.value, 0xDCDB)) return;
            y = 0x05;
            pushAddress(0xDCE0);
            SUB_01C1D6();
            if (handleReturnAddress(poppedEntry.value, 0xDCE0)) return;
            x = myMapper->readCPU(0x004E);
        }
    }
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_01DCFB;
    }
    a = 0x05;
    y = 0x80;
    pushAddress(0xDCEE);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0xDCEE)) return;
    myMapper->writeCPU(0x046C + x, 0x01);
    y = 0x00;
    a = 0x02;
    SUB_01EC72();
    return;
L_01DCFB:
    pushAddress(0xDCFD);
    SUB_01DD01();
    if (handleReturnAddress(poppedEntry.value, 0xDCFD)) return;
    SUB_01EE48();
    return;
}

void game::SUB_01DD01() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x40);
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03C4 + x, a);
    SUB_01EF56();
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
    SUB_01DD40();
    return;
}

void game::SUB_01DD40() {
    a = myMapper->readCPU(0x0300 + x);
    setLoadFlag(a);
    if (flgZ) {
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

void game::SUB_01DD5B() {
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0xDD62);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xDD62)) return;
    SUB_01DD6D();
    return;
}

void game::SUB_01DD6D() {
    a = 0x80;
    myMapper->writeCPU(0x038C + x, a);
    myMapper->writeCPU(0x0354 + x, a);
    a = 0x3C;
    y = 0x81;
    SUB_01ED34();
    return;
}

void game::SUB_01DD7C() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01DD82;
    }
    popAddress();
    return;
L_01DD82:
    a = 0x4B;
    pushAddress(0xDD86);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xDD86)) return;
    myMapper->writeCPU(0x0488 + x, 0x80);
    a = 0x20;
    y = 0x82;
    SUB_01ED34();
    return;
}

void game::SUB_01DD93() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        y = 0x00;
        a = myMapper->readCPU(0x001A);
        opAND(0x01);
        if (flgZ) {
            goto L_01DDA2;
        }
        y = 0xA2;
    L_01DDA2:
        myMapper->writeCPU(0x031C + x, y);
        popAddress();
        return;
    }
    pushAddress(0xDDA9);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0xDDA9)) return;
    myMapper->writeCPU(0x0488 + x, a);
    a = 0x03;
    SUB_01F131();
    return;
}

void game::SUB_01DDB2() {
    a = 0x01;
    myMapper->writeCPU(0x046C + x, a);
    SUB_01F1D2();
    return;
}

void game::SUB_01DDBA() {
    pushAddress(0xDDBC);
    SUB_01DD01();
    if (handleReturnAddress(poppedEntry.value, 0xDDBC)) return;
    opADC(0x08);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0xDDC7);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0xDDC7)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        SUB_01DDD7();
        return;
    }
    pushAddress(0xDDCE);
    SUB_01EFAF();
    if (handleReturnAddress(poppedEntry.value, 0xDDCE)) return;
    opINC(0x046C + x, 1);
    myMapper->writeCPU(0x0568 + x, 0xB4);
    SUB_01DDD7();
    return;
}

void game::SUB_01DDD7() {
    popAddress();
}

void game::SUB_01DDD8() {
    a = myMapper->readCPU(0x0584 + x);
    if (a == 0x0A) {
        jump(0xDDD7);
        return;
    }
    opDEC(0x0568 + x, 1);
    if (!flgZ) {
        SUB_01DDD7();
        return;
    }
    opAND(0x0F);
    if (a != 0x01) {
        if (a == 0x05) {
            goto L_01DDFE;
        }
        if (a != 0x06) {
            if (a == 0x07) {
                goto L_01DDFE;
            }
            if (a == 0x0C) {
                goto L_01DDFE;
            }
            myMapper->writeCPU(0x0072, 0x00);
        }
    }
L_01DDFE:
    myMapper->writeCPU(0x0434 + x, 0x32);
    SUB_01DE03();
    return;
}

void game::SUB_01DE03() {
    popAddress();
}

void game::SUB_01DE04() {
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0xDE0B);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xDE0B)) return;
    SUB_01DE12();
    return;
}

void game::SUB_01DE12() {
    if (!(myMapper->readCPU(0x046C + x) & 0x80)) {
        goto L_01DE2B;
    }
    opCMP(myMapper->readCPU(0x0584 + x), 0x06);
    if (!flgZ) {
        opDEC(0x04F8 + x, 1);
        if (flgZ) {
            a = myMapper->readCPU(0x046C + x);
            opAND(0x7F);
            myMapper->writeCPU(0x046C + x, a);
        }
    }
L_01DE2B:
    a = myMapper->readCPU(0x0584 + x);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01DE37;
    }
    opCMP(a, 0x06);
    if (!flgZ) {
        SUB_01DE04();
        return;
    }
    SUB_01DD5B();
    return;
L_01DE37:
    a = myMapper->readCPU(0x046C + x);
    opAND(0x7F);
    pushAddress(0xDE3E);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xDE3E)) return;
    SUB_01DE45();
    return;
}

void game::SUB_01DE45() {
    myMapper->writeCPU(0x0514 + x, myMapper->readCPU(0x038C + x));
    a = 0x00;
    y = 0xE0;
    pushAddress(0xDE51);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0xDE51)) return;
    a = 0x00;
    y = 0x80;
    pushAddress(0xDE58);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0xDE58)) return;
    a = 0x00;
    myMapper->writeCPU(0x0530 + x, a);
    myMapper->writeCPU(0x054C + x, a);
    opINC(0x046C + x, 1);
    popAddress();
}

void game::SUB_01DE65() {
    a = myMapper->readCPU(0x054C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0053));
    myMapper->writeCPU(0x054C + x, a);
    a = myMapper->readCPU(0x0514 + x);
    opADC(myMapper->readCPU(0x0052));
    myMapper->writeCPU(0x0514 + x, a);
    if (a < 0x08) {
        jump(0xDEA3);
        return;
    }
    if (a >= 0xF8) {
        jump(0xDEA3);
        return;
    }
    pushAddress(0xDE80);
    SUB_01DEA9();
    if (handleReturnAddress(poppedEntry.value, 0xDE80)) return;
    pushAddress(0xDE83);
    SUB_01EF43();
    if (handleReturnAddress(poppedEntry.value, 0xDE83)) return;
    opADC(0x08);
    myMapper->writeCPU(0x004D, a);
    a = 0x00;
    myMapper->writeCPU(0x004C, a);
    pushAddress(0xDE8E);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0xDE8E)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        jump(0xDE9D);
        return;
    }
    myMapper->writeCPU(0x046C + x, 0x02);
    myMapper->writeCPU(0x0568 + x, 0xB4);
    SUB_01DE9D();
    return;
}

void game::SUB_01DE9D() {
    popAddress();
}

void game::SUB_01DE9E() {
    opDEC(0x0568 + x, 1);
    if (!flgZ) {
        SUB_01DE9D();
        return;
    }
    SUB_01DEA3();
    return;
}

void game::SUB_01DEA3() {
    myMapper->writeCPU(0x0434 + x, 0x32);
    popAddress();
}

void game::SUB_01DEA9() {
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0514 + x));
    y = 0x00;
    if (!flgC) {
        opDEY(1);
    }
    myMapper->writeCPU(0x0001, y);
    y = myMapper->readCPU(0x0530 + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01DEC6;
    }
    do {
        flgC = false;
        opBIT(myMapper->readCPU(0x0001));
        if (!flgN) {
            goto L_01DEC2;
        }
        flgC = true;
    L_01DEC2:
        opROR_A(1);
        opDEY(1);
    } while (!flgZ);
L_01DEC6:
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0418 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0418 + x, a);
    a = myMapper->readCPU(0x03FC + x);
    opSBC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x03FC + x, a);
    SUB_01EE35();
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
            opCMP(a, 0x17);
            if (!flgC) {
                goto L_01DEF9;
            }
            if (a < 0x20) {
                goto L_01DEF3;
            }
            opCMP(a, 0x28);
            if (!flgC) {
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

void game::SUB_01E024() {
    myMapper->writeCPU(0x004E, x);
    a = myMapper->readCPU(0x000E);
    opCMP(a, 0xFF);
    if (!flgZ) {
        y = myMapper->readCPU(0x000F);
        a = myMapper->readCPU(0x04F8 + y);
        setLoadFlag(a);
        if (!flgZ) {
            myMapper->writeCPU(0x004B, a);
            y = 0x0D;
            do {
                a = myMapper->readCPU(0x0434 + y);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_01E046;
                }
                opDEY(1);
            } while (y >= 0x04);
            x = myMapper->readCPU(0x004B);
            goto L_01E074;
        L_01E046:
            myMapper->writeCPU(0x0434 + y, 0x33);
            myMapper->writeCPU(0x0568 + y, 0x20);
            myMapper->writeCPU(0x038C + y, myMapper->readCPU(0x038C + x));
            a = myMapper->readCPU(0x0354 + x);
            flgC = true;
            opSBC(0x18);
            myMapper->writeCPU(0x0354 + y, a);
            x = myMapper->readCPU(0x004B);
            myMapper->writeCPU(0x031C + y, myMapper->readCPU(0xE092 + x));
            a = 0x00;
            myMapper->writeCPU(0x0450 + y, a);
            myMapper->writeCPU(0x0338 + y, a);
            myMapper->writeCPU(0x0488 + y, 0x80);
        L_01E074:
            a = myMapper->readCPU(0xE08D + x);
            pushAddress(0xE079);
            SUB_01DF0E();
            if (handleReturnAddress(poppedEntry.value, 0xE079)) return;
        }
        y = myMapper->readCPU(0x000F);
        x = myMapper->readCPU(0x04F8 + y);
        opINX(1);
        opCMP(x, 0x05);
        if (!flgC) {
            goto L_01E086;
        }
        x = 0x04;
    L_01E086:
        a = x;
        myMapper->writeCPU(0x04F8 + y, a);
    }
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01E097() {
    pushAddress(0xE099);
    SUB_01E024();
    if (handleReturnAddress(poppedEntry.value, 0xE099)) return;
    SUB_01E09A();
    return;
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
                SUB_01E0E9();
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
                    SUB_01E0E9();
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
        SUB_01E0E4();
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
    SUB_01E0E2();
    return;
}

void game::SUB_01E150() {
    a = myMapper->readCPU(0x000D);
    opASL_M(0x000C, 1);
    opROL_A(1);
    opASL_M(0x000C, 1);
    opROL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0514 + x));
    popAddress();
}

void game::SUB_01E15D() {
    a = myMapper->readCPU(0x000D);
    opASL_M(0x000C, 1);
    opROL_A(1);
    opASL_M(0x000C, 1);
    opROL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0584 + x));
    popAddress();
}

void game::SUB_01E16A() {
    pushAddress(0xE16C);
    SUB_01E15D();
    if (handleReturnAddress(poppedEntry.value, 0xE16C)) return;
    opCMP(a, 0xC0);
    if (!flgC) {
        goto L_01E18A;
    }
    x = 0x05;
    do {
        myMapper->writeCPU(0x0434 + x, 0x31);
        a = 0x00;
        myMapper->writeCPU(0x0584 + x, a);
        pushAddress(0xE17F);
        SUB_01E3F4();
        if (handleReturnAddress(poppedEntry.value, 0xE17F)) return;
        opINX(1);
        opCMP(x, 0x0B);
    } while (!flgC);
    x = 0x04;
    SUB_01E097();
    return;
L_01E18A:
    SUB_01E1BC();
    return;
}

void game::SUB_01E18D() {
    pushAddress(0xE18F);
    SUB_01E15D();
    if (handleReturnAddress(poppedEntry.value, 0xE18F)) return;
    opCMP(a, 0xC0);
    if (!flgC) {
        goto L_01E197;
    }
    SUB_01E1B6();
    return;
L_01E197:
    myMapper->writeCPU(0x0584 + x, a);
    a = myMapper->readCPU(0x000E);
    opCMP(a, 0x03);
    if (flgZ) {
        SUB_01E1CC();
        return;
    }
    SUB_01E332();
    return;
}

void game::SUB_01E1A3() {
    a = 0xC0;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01E1AD();
        return;
    }
    SUB_01E1A7();
    return;
}

void game::SUB_01E1A7() {
    a = 0x40;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01E1AD();
        return;
    }
    SUB_01E1AB();
    return;
}

void game::SUB_01E1AB() {
    a = 0x40;
    SUB_01E1AD();
    return;
}

void game::SUB_01E1AD() {
    myMapper->writeCPU(0x004B, a);
    pushAddress(0xE1B1);
    SUB_01E15D();
    if (handleReturnAddress(poppedEntry.value, 0xE1B1)) return;
    opCMP(a, myMapper->readCPU(0x004B));
    if (!flgC) {
        SUB_01E1BC();
        return;
    }
    SUB_01E1B6();
    return;
}

void game::SUB_01E1B6() {
    pushAddress(0xE1B8);
    SUB_01E4CC();
    if (handleReturnAddress(poppedEntry.value, 0xE1B8)) return;
    SUB_01E097();
    return;
}

void game::SUB_01E1BC() {
    myMapper->writeCPU(0x0584 + x, a);
    myMapper->writeCPU(0x0568 + x, 0x10);
    a = myMapper->readCPU(0x0488 + x);
    opORA(0x80);
    myMapper->writeCPU(0x0488 + x, a);
    SUB_01E1CC();
    return;
}

void game::SUB_01E1CC() {
    popAddress();
}

void game::SUB_01E1CD() {
    a = myMapper->readCPU(0x0450 + x);
    opCMP(a, myMapper->readCPU(0x0450));
    if (!flgZ) {
        SUB_01E1DC();
        return;
    }
    SUB_01E1D5();
    return;
}

void game::SUB_01E1D5() {
    pushAddress(0xE1D7);
    SUB_01E4CC();
    if (handleReturnAddress(poppedEntry.value, 0xE1D7)) return;
    SUB_01E1D8();
    return;
}

void game::SUB_01E1D8() {
    a = myMapper->readCPU(0x0010);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01E1AB();
        return;
    }
    SUB_01E1DC();
    return;
}

void game::SUB_01E1DC() {
    pushAddress(0xE1DE);
    SUB_01E150();
    if (handleReturnAddress(poppedEntry.value, 0xE1DE)) return;
    opCMP(a, 0xE0);
    if (!flgC) {
        goto L_01E1E5;
    }
    a = 0xFF;
L_01E1E5:
    myMapper->writeCPU(0x0514 + x, a);
    SUB_01E332();
    return;
}

void game::SUB_01E1EB() {
    a = myMapper->readCPU(0x000E);
    opCMP(a, 0x03);
    if (flgZ) {
        SUB_01E1D8();
        return;
    }
    if (!flgZ) {
        SUB_01E1D5();
        return;
    }
    SUB_01E1F3();
    return;
}

void game::SUB_01E1F3() {
    pushAddress(0xE1F5);
    SUB_01E024();
    if (handleReturnAddress(poppedEntry.value, 0xE1F5)) return;
    pushAddress(0xE1F8);
    SUB_01DF06();
    if (handleReturnAddress(poppedEntry.value, 0xE1F8)) return;
    myMapper->writeCPU(0x0568 + x, 0x20);
    a = 0x56;
    pushAddress(0xE202);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xE202)) return;
    a = 0x84;
    SUB_01E2A5();
    return;
}

void game::SUB_01E208() {
    y = myMapper->readCPU(0x0514 + x);
    opINY(1);
    if (flgZ) {
        SUB_01E1AB();
        return;
    }
    myMapper->writeCPU(0x0010, 0x01);
    if (myMapper->readCPU(0x000E) == 0xFF) {
        jump(0xE1CD);
        return;
    }
    myMapper->writeCPU(0x0568 + x, 0x08);
    y = myMapper->readCPU(0x000F);
    if (myMapper->readCPU(0x0450 + x) == 0) {
        a = myMapper->readCPU(0x038C + x);
        opCMP(a, myMapper->readCPU(0x038C + y));
        if (flgC) {
            SUB_01E1EB();
            return;
        }
        if (!flgC) {
            goto L_01E236;
        }
    }
    a = myMapper->readCPU(0x038C + x);
    if (a < myMapper->readCPU(0x038C + y)) {
        jump(0xE1EB);
        return;
    }
L_01E236:
    y = myMapper->readCPU(0x000E);
    setLoadFlag(y);
    if (!flgZ) {
        opDEY(1);
        if (flgZ) {
            goto L_01E251;
        }
        opDEY(2);
        if (flgZ) {
            goto L_01E262;
        }
    L_01E241:
        y = myMapper->readCPU(0x000F);
        a = 0x00;
        myMapper->writeCPU(0x03FC + y, a);
        myMapper->writeCPU(0x0418 + y, a);
        SUB_01E1DC();
        return;
    }
    SUB_01E1DC();
    return;
L_01E251:
    x = myMapper->readCPU(0x000F);
    a = myMapper->readCPU(0x046C + x);
    opCMP(a, 0x04);
    if (!flgZ) {
        pushAddress(0xE25C);
        SUB_01EAB2();
        if (handleReturnAddress(poppedEntry.value, 0xE25C)) return;
    }
    x = myMapper->readCPU(0x004E);
    SUB_01E1DC();
    return;
L_01E262:
    y = myMapper->readCPU(0x000F);
    a = myMapper->readCPU(0x046C + y);
    if (a != 0x02) {
        goto L_01E26E;
    }
    SUB_01E1D8();
    return;
L_01E26E:
    goto L_01E241;
}

void game::SUB_01E271() {
    opLSR_M(0x000D, 1);
    opROR_M(0x000C, 1);
    popAddress();
}

void game::SUB_01E276() {
    pushAddress(0xE278);
    SUB_01E271();
    if (handleReturnAddress(poppedEntry.value, 0xE278)) return;
    SUB_01E279();
    return;
}

void game::SUB_01E279() {
    pushAddress(0xE27B);
    SUB_01E3C0();
    if (handleReturnAddress(poppedEntry.value, 0xE27B)) return;
    if (myMapper->readCPU(0x01A9) != 0) {
        jump(0xE2A9);
        return;
    }
    a = myMapper->readCPU(0x0434 + x);
    opCMP(a, 0x1C);
    if (flgZ) {
        SUB_01E2B7();
        return;
    }
    opCMP(a, 0x04);
    if (flgZ) {
        SUB_01E2C6();
        return;
    }
    SUB_01E28C();
    return;
}

void game::SUB_01E28C() {
    myMapper->writeCPU(0x0568 + x, 0x3C);
    a = 0x3F;
    pushAddress(0xE295);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xE295)) return;
    pushAddress(0xE298);
    SUB_01DF06();
    if (handleReturnAddress(poppedEntry.value, 0xE298)) return;
    a = 0x31;
    SUB_01E29B();
    return;
}

void game::SUB_01E29B() {
    myMapper->writeCPU(0x0434 + x, a);
    myMapper->writeCPU(0x0584 + x, 0x06);
    a = 0x80;
    SUB_01E2A5();
    return;
}

void game::SUB_01E2A5() {
    myMapper->writeCPU(0x046C + x, a);
    popAddress();
}

void game::SUB_01E2A9() {
    myMapper->writeCPU(0x0568 + x, 0x08);
    a = myMapper->readCPU(0x0488 + x);
    opORA(0x80);
    myMapper->writeCPU(0x0488 + x, a);
    popAddress();
}

void game::SUB_01E2B7() {
    a = 0x30;
    x = 0x08;
    myMapper->writeCPU(0x0434 + x, a);
    pushAddress(0xE2C0);
    SUB_01E3F4();
    if (handleReturnAddress(poppedEntry.value, 0xE2C0)) return;
    x = 0x07;
    SUB_01E28C();
    return;
}

void game::SUB_01E2C6() {
    myMapper->writeCPU(0x0473, 0x8D);
    popAddress();
}

void game::SUB_01E2CC() {
    a = x;
    opEOR(0x0F);
    myMapper->writeCPU(0x0017, a);
    opLSR_M(0x000D, 1);
    opROR_M(0x000C, 1);
    opLSR_M(0x000D, 1);
    opROR_M(0x000C, 1);
    a = myMapper->readCPU(0x0530 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x000C));
    myMapper->writeCPU(0x0530 + x, a);
    a = myMapper->readCPU(0x0584 + x);
    opSBC(myMapper->readCPU(0x000D));
    if (flgN) {
        a = 0x00;
    }
    myMapper->writeCPU(0x0584 + x, a);
    pushAddress(0xE2F0);
    SUB_01E3A8();
    if (handleReturnAddress(poppedEntry.value, 0xE2F0)) return;
    if (myMapper->readCPU(0x0584 + x) != 0) {
        jump(0xE2A9);
        return;
    }
    myMapper->writeCPU(0x0568 + x, 0x3C);
    a = 0x3F;
    pushAddress(0xE2FF);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xE2FF)) return;
    pushAddress(0xE302);
    SUB_01DF06();
    if (handleReturnAddress(poppedEntry.value, 0xE302)) return;
    y = myMapper->readCPU(0x0017);
    if (myMapper->readCPU(0x0434 + y) == 0x1A) {
        goto L_01E310;
    }
    a = 0x31;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01E29B();
        return;
    }
L_01E310:
    a = 0x30;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01E29B();
        return;
    }
    SUB_01E314();
    return;
}

void game::SUB_01E314() {
    opLSR_M(0x000D, 1);
    opROR_M(0x000C, 1);
    SUB_01E279();
    return;
}

void game::SUB_01E31B() {
    a = myMapper->readCPU(0x007A);
    setLoadFlag(a);
    if (!flgZ) {
        y = myMapper->readCPU(0x000E);
        if (y != 0x03) {
            goto L_01E32C;
        }
        opLSR_M(0x000D, 1);
        opROR_M(0x000C, 1);
        SUB_01E346();
        return;
    }
L_01E32C:
    opCMP(myMapper->readCPU(0x00B2), 0x14);
    if (flgZ) {
        SUB_01E386();
        return;
    }
    SUB_01E332();
    return;
}

void game::SUB_01E332() {
    a = 0x10;
    pushAddress(0xE336);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xE336)) return;
    y = 0x05;
    pushAddress(0xE33B);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xE33B)) return;
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01E33F() {
    a = myMapper->readCPU(0x007A);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01E346();
        return;
    }
    SUB_01E276();
    return;
}

void game::SUB_01E346() {
    opLSR_M(0x000D, 1);
    opROR_M(0x000C, 1);
    opLSR_M(0x000D, 1);
    opROR_M(0x000C, 1);
    myMapper->writeCPU(0x004E, x);
    pushAddress(0xE352);
    SUB_01E3C0();
    if (handleReturnAddress(poppedEntry.value, 0xE352)) return;
    if (myMapper->readCPU(0x01A9) != 0) {
        jump(0xE387);
        return;
    }
    myMapper->writeCPU(0x043C, 0x32);
    x = 0x07;
    myMapper->writeCPU(0x0568 + x, 0x5A);
    a = 0x20;
    pushAddress(0xE368);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xE368)) return;
    pushAddress(0xE36B);
    SUB_01DF06();
    if (handleReturnAddress(poppedEntry.value, 0xE36B)) return;
    myMapper->writeCPU(0x0434 + x, 0x31);
    myMapper->writeCPU(0x046C + x, 0x80);
    myMapper->writeCPU(0x0584 + x, 0x06);
    a = myMapper->readCPU(0x0354 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0354 + x, a);
    x = myMapper->readCPU(0x004E);
    SUB_01E386();
    return;
}

void game::SUB_01E386() {
    popAddress();
}

void game::SUB_01E387() {
    myMapper->writeCPU(0x056F, 0x08);
    a = myMapper->readCPU(0x048F);
    opORA(0x80);
    myMapper->writeCPU(0x048F, a);
    popAddress();
}

void game::SUB_01E395() {
    myMapper->writeCPU(0x0434 + x, 0x34);
    myMapper->writeCPU(0x0568 + x, 0x54);
    a = myMapper->readCPU(0x0488 + x);
    opORA(0x80);
    myMapper->writeCPU(0x0488 + x, a);
    popAddress();
}

void game::SUB_01E3A8() {
    y = myMapper->readCPU(0x0017);
    if (myMapper->readCPU(0x0434 + y) == 0x1A) {
        goto L_01E3B5;
    }
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        goto L_01E3B8;
    }
L_01E3B5:
    a = myMapper->readCPU(0x0584 + y);
L_01E3B8:
    flgC = false;
    opADC(myMapper->readCPU(0x0584 + x));
    myMapper->writeCPU(0x01A9, a);
    popAddress();
}

void game::SUB_01E3C0() {
    a = myMapper->readCPU(0x01A8);
    flgC = true;
    opSBC(myMapper->readCPU(0x000C));
    myMapper->writeCPU(0x01A8, a);
    a = myMapper->readCPU(0x01A9);
    opSBC(myMapper->readCPU(0x000D));
    if (!flgN) {
        goto L_01E3D2;
    }
    a = 0x00;
L_01E3D2:
    myMapper->writeCPU(0x01A9, a);
    popAddress();
}

void game::SUB_01E3D6() {
    popAddress();
}

void game::SUB_01E3D7() {
    y = myMapper->readCPU(0x04DC + x);
    opCMP(y, 0xFF);
    if (!flgZ) {
        a = 0xF0;
        if (myMapper->readCPU(0x0046) == 0) {
            goto L_01E3E6;
        }
        a = 0x0F;
    L_01E3E6:
        y = myMapper->readCPU(0x04DC + x);
        opORA(myMapper->readCPU(0x0190 + y));
        myMapper->writeCPU(0x0190 + y, a);
    }
    myMapper->writeCPU(0x0434 + x, 0x31);
    SUB_01E3F4();
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
        if (a != 0x04) {
            goto L_01E502;
        }
    L_01E4EF:
        a = myMapper->readCPU(0x0434 + x);
        if (a != 0x17) {
            if (a == 0x21) {
                goto L_01E502;
            }
            if (a != 0x25) {
                if (a < 0x30) {
                    goto L_01E503;
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
    if (a != 0x05) {
        if (a == 0x08) {
            goto L_01E6D6;
        }
        y = 0x00;
        a = myMapper->readCPU(0x0434 + x);
        if (a == 0x2F) {
            goto L_01E75E;
        }
        a = myMapper->readCPU(0x005B);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01E6D7;
        }
    }
    do {
    L_01E6D6:
        popAddress();
        return;
    L_01E6D7:
        a = myMapper->readCPU(0x0434 + x);
    } while (a >= 0x28);
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
        if (a < myMapper->readCPU(0x004C)) {
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
                opCMP(a, 0x02);
                if (!flgZ) {
                    opCMP(a, 0x07);
                    if (!flgZ) {
                        opCMP(a, 0x0F);
                        if (!flgZ) {
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
                }
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
                    if (y < 0x0C) {
                        a = 0x0C;
                        if (y < 0x07) {
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
                            SUB_01EC60();
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
    SUB_01DF0E();
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
    SUB_01E922();
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
        SUB_01E92B();
        return;
    }
    if (!flgZ) {
        SUB_01E931();
        return;
    }
    SUB_01E92B();
    return;
}

void game::SUB_01E92B() {
    opDEX(1);
    opCMP(x, 0x03);
    if (flgC) {
        SUB_01E924();
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
            SUB_01E9E6();
            return;
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
    pushManualAddress(0xE9E5);
    a = myMapper->readCPU(0x004B);
    pushAddress(0xE95B);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xE95B)) return;
    SUB_01E9CA();
    return;
}

void game::SUB_01E9CA() {
    a = myMapper->readCPU(0x0434 + x);
    SUB_01EA42();
    return;
}

void game::SUB_01E9E0() {
    a = 0x10;
    y = 0xF1;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_01EA12();
        return;
    }
    SUB_01E9E6();
    return;
}

void game::SUB_01E9E6() {
    a = myMapper->readCPU(0x0434 + x);
    if (a != 0x35) {
        if (a < 0x28) {
            goto L_01E9F8;
        }
        if (a >= 0x2F) {
            goto L_01E9F8;
        }
        SUB_01EA77();
        return;
    }
L_01E9F8:
    a = myMapper->readCPU(0x0354 + x);
    if (a < 0x08) {
        jump(0xE9CA);
        return;
    }
    if (a >= 0xF8) {
        jump(0xE9CA);
        return;
    }
    a = myMapper->readCPU(0x0434 + x);
    if (a == 0x12) {
        jump(0xE9E0);
        return;
    }
    if (a == 0x1E) {
        jump(0xE9E0);
        return;
    }
    a = 0x08;
    y = 0xF9;
    SUB_01EA12();
    return;
}

void game::SUB_01EA12() {
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
    SUB_01EADD();
    return;
L_01EA30:
    pushAddress(0xEA32);
    SUB_01EACB();
    if (handleReturnAddress(poppedEntry.value, 0xEA32)) return;
    SUB_01EA33();
    return;
}

void game::SUB_01EA33() {
    if (a >= myMapper->readCPU(0x0017)) {
        goto L_01EA3B;
    }
    if (a >= myMapper->readCPU(0x0016)) {
        jump(0xEA77);
        return;
    }
L_01EA3B:
    a = myMapper->readCPU(0x0434 + x);
    if (a == 0x17) {
        jump(0xEA80);
        return;
    }
    SUB_01EA42();
    return;
}

void game::SUB_01EA42() {
    if (a < 0x18) {
        goto L_01EA4A;
    }
    if (a < 0x1E) {
        jump(0xEABD);
        return;
    }
L_01EA4A:
    if (a == 0x11) {
        jump(0xEAB8);
        return;
    }
    if (a == 0x07) {
        jump(0xEAB8);
        return;
    }
    if (a == 0x0C) {
        jump(0xEAB8);
        return;
    }
    if (a == 0x0E) {
        jump(0xEABD);
        return;
    }
    if (a == 0x0F) {
        jump(0xEAB8);
        return;
    }
    if (a == 0x13) {
        jump(0xEAB8);
        return;
    }
    if (a != 0x2F) {
        jump(0xEA72);
        return;
    }
    y = myMapper->readCPU(0x0584 + x);
    setLoadFlag(y);
    if (flgZ) {
        SUB_01EA72();
        return;
    }
    opDEY(1);
    if (flgZ) {
        SUB_01EA72();
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
    SUB_01E92B();
    return;
}

void game::SUB_01EA80() {
    if (myMapper->readCPU(0x0584 + x) != 0x01) {
        jump(0xEA72);
        return;
    }
    if (myMapper->readCPU(0x046C + x) == 0x04) {
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
    SUB_01EA77();
    return;
}

void game::SUB_01EAA9() {
    a = myMapper->readCPU(0x0450 + x);
    opEOR(0x01);
    myMapper->writeCPU(0x0450 + x, a);
    SUB_01EAB1();
    return;
}

void game::SUB_01EAB1() {
    popAddress();
}

void game::SUB_01EAB2() {
    pushAddress(0xEAB4);
    SUB_01EAA9();
    if (handleReturnAddress(poppedEntry.value, 0xEAB4)) return;
    SUB_01DC50();
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
    SUB_01EA72();
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
    if (y >= myMapper->readCPU(0x0017)) {
        goto L_01EAF5;
    }
    if (y >= myMapper->readCPU(0x0016)) {
        goto L_01EAFA;
    }
L_01EAF5:
    a = 0x80;
    myMapper->writeCPU(0x0300 + x, a);
    do {
    L_01EAFA:
        SUB_01EA77();
        return;
    L_01EAFD:
        if (y < 0x40) {
            goto L_01EAFA;
        }
    } while (y >= 0xC0);
    SUB_01EA72();
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

void game::SUB_01EB36() {
    opDEC(0x0568 + x, 1);
    if (!flgZ) {
        y = 0x00;
        a = myMapper->readCPU(0x001A);
        opAND(0x01);
        if (flgZ) {
            goto L_01EB44;
        }
        opINY(1);
    L_01EB44:
        myMapper->writeCPU(0x0300 + x, y);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0300 + x, 0x00);
    myMapper->writeCPU(0x0434 + x, 0x1F);
    popAddress();
}

void game::SUB_01EB54() {
    pushAddress(0xEB56);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0xEB56)) return;
    SUB_01EB57();
    return;
}

void game::SUB_01EB57() {
    SUB_01EE48();
    return;
}

void game::SUB_01EB5A() {
    opDEC(0x0568 + x, 1);
    if (!flgZ) {
        SUB_01EB64();
        return;
    }
    myMapper->writeCPU(0x0434 + x, 0x32);
    SUB_01EB64();
    return;
}

void game::SUB_01EB64() {
    popAddress();
}

void game::SUB_01EB65() {
    opDEC(0x0568 + x, 1);
    if (!flgZ) {
        SUB_01EB64();
        return;
    }
    SUB_01EB6A();
    return;
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
    opCMP(a, 0x01);
    if (flgZ) {
        goto L_01EBAD;
    }
    opCMP(a, 0x06);
    if (!flgZ) {
        opCMP(a, 0x05);
        if (!flgZ) {
            opCMP(a, 0x07);
            if (flgZ) {
                goto L_01EBA6;
            }
            opCMP(a, 0x0C);
            if (flgZ) {
                goto L_01EBEF;
            }
            y = myMapper->readCPU(0x0072);
            setLoadFlag(y);
            if (!flgZ) {
                goto L_01EBE5;
            }
            opCMP(a, myMapper->readCPU(0x015B));
            if (flgZ) {
                goto L_01EBE5;
            }
            myMapper->writeCPU(0x0072, 0xFF);
        }
    }
    while (true) {
    L_01EBA6:
        y = a;
        a = myMapper->readCPU(0xEC0A + y);
        SUB_01EF04();
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
        opCMP(myMapper->readCPU(0x0079), 0x0A);
        if (flgC) {
            goto L_01EBEF;
        }
    L_01EBC3:
        a = myMapper->readCPU(0x0071);
        y = myMapper->readCPU(0x0072);
        setLoadFlag(y);
        if (flgZ) {
            y = myMapper->readCPU(0x0070);
            if (a < 0x08) {
                opCMP(a, 0x04);
                if (!flgC) {
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
            opCMP(y, 0x02);
            if (flgC) {
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
    opCMP(y, 0x02);
    if (flgC) {
        goto L_01EBC3;
    }
    myMapper->writeCPU(0x004B, y);
    a = 0x0C;
    myMapper->writeCPU(0x0584 + x, a);
    y = a;
    a = myMapper->readCPU(0xEC0A + y);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    SUB_01EF04();
    return;
}

void game::SUB_01EC1A() {
    y = myMapper->readCPU(0x04F8 + x);
    setLoadFlag(y);
    if (flgZ) {
        SUB_01EC2F();
        return;
    }
    if (!flgZ) {
        SUB_01EC26();
        return;
    }
    SUB_01EC21();
    return;
}

void game::SUB_01EC21() {
    y = myMapper->readCPU(0x0450 + x);
    setLoadFlag(y);
    if (flgZ) {
        SUB_01EC2F();
        return;
    }
    SUB_01EC26();
    return;
}

void game::SUB_01EC26() {
    a = myMapper->readCPU(0x038C + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x004C));
    SUB_01EC35();
    return;
}

void game::SUB_01EC2F() {
    a = myMapper->readCPU(0x038C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x004C));
    SUB_01EC35();
    return;
}

void game::SUB_01EC35() {
    flgC = false;
    opADC(myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x002F);
    opADC(0x00);
    myMapper->writeCPU(0x0013, a);
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x004D));
    a = 0x00;
    myMapper->writeCPU(0x0011, a);
    myMapper->writeCPU(0x004E, x);
    pushAddress(0xEC4C);
    SUB_01F9A0();
    if (handleReturnAddress(poppedEntry.value, 0xEC4C)) return;
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01EC50() {
    a = myMapper->readCPU(0x03E0 + x);
    opSBC(0x20);
    myMapper->writeCPU(0x03E0 + x, a);
    if (flgC) {
        goto L_01EC5D;
    }
    opDEC(0x03C4 + x, 1);
L_01EC5D:
    SUB_01EF56();
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
    callStack.pop_back();
    SUB_01E92B();
    return;
}

void game::SUB_01EC72() {
    myMapper->writeCPU(0x03FC + x, a);
    a = y;
    myMapper->writeCPU(0x0418 + x, a);
    popAddress();
}

void game::SUB_01EC7A() {
    pushAddress(0xEC7C);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0xEC7C)) return;
    SUB_01EC7D();
    return;
}

void game::SUB_01EC7D() {
    y = myMapper->readCPU(0x04DC + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01EC85;
    }
    SUB_01EF56();
    return;
L_01EC85:
    SUB_01EF43();
    return;
}

void game::SUB_01EC88() {
    myMapper->writeCPU(0x004E, x);
    myMapper->writeCPU(0x0012, x);
    y = 0x0D;
    do {
        if (myMapper->readCPU(0x0434 + y) == 0) {
            goto L_01EC99;
        }
        opDEY(1);
        opCMP(y, 0x0C);
    } while (flgC);
    popAddress();
    return;
L_01EC99:
    myMapper->writeCPU(0x0011, y);
    myMapper->writeCPU(0x0016, 0x20);
    a = 0x08;
    pushAddress(0xECA3);
    SUB_01ED82();
    if (handleReturnAddress(poppedEntry.value, 0xECA3)) return;
    x = y;
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x038C));
    a = myMapper->readCPU(0x0354);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0xECB2);
    SUB_01EEBB();
    if (handleReturnAddress(poppedEntry.value, 0xECB2)) return;
    a = myMapper->readCPU(0x0002);
    y = myMapper->readCPU(0x0001);
    opLSR_M(0x0001, 1);
    opROR_M(0x0002, 1);
    opADC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0002, a);
    a = y;
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0001, a);
    if (myMapper->readCPU(0x0009) != 0) {
        goto L_01ECD9;
    }
    y = 0x80;
    a = 0x01;
    pushAddress(0xECCE);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0xECCE)) return;
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0001);
    pushAddress(0xECD5);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0xECD5)) return;
    while (true) {
        x = myMapper->readCPU(0x0012);
        popAddress();
        return;
    L_01ECD9:
        a = 0x01;
        y = 0x80;
        pushAddress(0xECDF);
        SUB_01ECEA();
        if (handleReturnAddress(poppedEntry.value, 0xECDF)) return;
        y = myMapper->readCPU(0x0002);
        a = myMapper->readCPU(0x0001);
        pushAddress(0xECE6);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0xECE6)) return;
    }
    SUB_01ECEA();
    return;
}

void game::SUB_01ECEA() {
    myMapper->writeCPU(0x03C4 + x, a);
    a = y;
    myMapper->writeCPU(0x03E0 + x, a);
    popAddress();
}

void game::SUB_01ECF2() {
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01ED00;
    }
    opDEY(1);
    if (flgZ) {
        SUB_01ED3B();
        return;
    }
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01ED30;
    }
    popAddress();
    return;
L_01ED00:
    myMapper->writeCPU(0x004E, x);
    a = x;
    flgC = true;
    opSBC(0x05);
    x = a;
    a = 0x0C;
    pushAddress(0xED0B);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0xED0B)) return;
    myMapper->writeCPU(0x046C + x, 0x05);
    a = 0x4D;
    pushAddress(0xED15);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xED15)) return;
    y = x;
    x = myMapper->readCPU(0x004E);
    a = myMapper->readCPU(0x0354 + x);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x0354 + y, a);
    myMapper->writeCPU(0x038C + y, myMapper->readCPU(0x038C + x));
    y = 0xC0;
    a = 0x01;
    pushAddress(0xED2F);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0xED2F)) return;
L_01ED30:
    a = 0x30;
    y = 0x01;
    SUB_01ED34();
    return;
}

void game::SUB_01ED34() {
    myMapper->writeCPU(0x054C + x, a);
    a = y;
    SUB_01F131();
    return;
}

void game::SUB_01ED3B() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01ED43;
    }
    SUB_01EE48();
    return;
L_01ED43:
    a = 0x10;
    y = 0x02;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_01ED34();
        return;
    }
    SUB_01ED49();
    return;
}

void game::SUB_01ED49() {
    a = myMapper->readCPU(0x0028);
    if (a == 0x06) {
        jump(0x82A2);
        return;
    }
    if (a != 0x0F) {
        goto L_01ED59;
    }
    jump(0x8E5D);
    return;
L_01ED59:
    jump(0x872C);
    return;
}

void game::SUB_01ED5C() {
    a = myMapper->readCPU(0x0028);
    if (a == 0x0D) {
        jump(0x8E80);
        return;
    }
    if (a != 0x11) {
        goto L_01ED6C;
    }
    jump(0x9326);
    return;
L_01ED6C:
    jump(0x874F);
    return;
}

void game::SUB_01ED6F() {
    a = myMapper->readCPU(0x0028);
    if (a == 0x0D) {
        jump(0x8C9A);
        return;
    }
    if (a != 0x11) {
        goto L_01ED7F;
    }
    jump(0x922E);
    return;
L_01ED7F:
    jump(0x84FF);
    return;
}

void game::SUB_01ED82() {
    myMapper->writeCPU(0x0017, a);
    x = y;
    a = myMapper->readCPU(0x0016);
    pushAddress(0xED8A);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0xED8A)) return;
    a = myMapper->readCPU(0x0017);
    pushAddress(0xED8F);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xED8F)) return;
    x = myMapper->readCPU(0x004E);
    myMapper->writeCPU(0x038C + y, myMapper->readCPU(0x038C + x));
    myMapper->writeCPU(0x0354 + y, myMapper->readCPU(0x0354 + x));
    myMapper->writeCPU(0x0450 + y, myMapper->readCPU(0x0450 + x));
    popAddress();
}


void game::SUB_01EDA5() {
    a = myMapper->readCPU(0x0002);
    y = myMapper->readCPU(0x0001);
    opLSR_M(0x0001, 1);
    opROR_M(0x0002, 1);
    opLSR_M(0x0001, 1);
    opROR_M(0x0002, 1);
    opSBC(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0002, a);
    a = y;
    opSBC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_01EDBB() {
    pushAddress(0xEDBD);
    SUB_01EEA7();
    if (handleReturnAddress(poppedEntry.value, 0xEDBD)) return;
    a = myMapper->readCPU(0x046C + x);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x01;
        myMapper->writeCPU(0x054C + x, a);
        myMapper->writeCPU(0x046C + x, a);
    }
    opDEC(0x054C + x, 1);
    if (!flgZ) {
    }
    else {
        myMapper->writeCPU(0x054C + x, 0x20);
        myMapper->writeCPU(0x0001, myMapper->readCPU(0x038C));
        a = myMapper->readCPU(0x0354);
        myMapper->writeCPU(0x0000, a);
        pushAddress(0xEDE4);
        SUB_01EEBB();
        if (handleReturnAddress(poppedEntry.value, 0xEDE4)) return;
        pushAddress(0xEDE7);
        SUB_01EDA5();
        if (handleReturnAddress(poppedEntry.value, 0xEDE7)) return;
        if (myMapper->readCPU(0x0009) == 0) {
            y = 0xC0;
            a = 0x00;
            pushAddress(0xEDF2);
            SUB_01EC72();
            if (handleReturnAddress(poppedEntry.value, 0xEDF2)) return;
            y = myMapper->readCPU(0x0002);
            a = myMapper->readCPU(0x0001);
            pushAddress(0xEDF9);
            SUB_01ECEA();
            if (handleReturnAddress(poppedEntry.value, 0xEDF9)) return;
        }
        else {
            a = 0x00;
            y = 0xC0;
            pushAddress(0xEE03);
            SUB_01ECEA();
            if (handleReturnAddress(poppedEntry.value, 0xEE03)) return;
            y = myMapper->readCPU(0x0002);
            a = myMapper->readCPU(0x0001);
            pushAddress(0xEE0A);
            SUB_01EC72();
            if (handleReturnAddress(poppedEntry.value, 0xEE0A)) return;
        }
    }
    a = myMapper->readCPU(0x04DC + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01EE16;
    }
    pushAddress(0xEE12);
    SUB_01EF43();
    if (handleReturnAddress(poppedEntry.value, 0xEE12)) return;
    SUB_01EE48();
    return;
L_01EE16:
    pushAddress(0xEE18);
    SUB_01EF56();
    if (handleReturnAddress(poppedEntry.value, 0xEE18)) return;
    SUB_01EE48();
    return;
}

void game::SUB_01EE1C() {
    a = myMapper->readCPU(0x04F8 + x);
    setLoadFlag(a);
    SUB_01EE4B();
    return;
}

void game::SUB_01EE22() {
    a = myMapper->readCPU(0x03A8 + x);
    opSBC(myMapper->readCPU(0x0418 + x));
    myMapper->writeCPU(0x03A8 + x, a);
    a = myMapper->readCPU(0x038C + x);
    opSBC(myMapper->readCPU(0x03FC + x));
    myMapper->writeCPU(0x038C + x, a);
    popAddress();
}

void game::SUB_01EE35() {
    a = myMapper->readCPU(0x03A8 + x);
    opADC(myMapper->readCPU(0x0418 + x));
    myMapper->writeCPU(0x03A8 + x, a);
    a = myMapper->readCPU(0x038C + x);
    opADC(myMapper->readCPU(0x03FC + x));
    myMapper->writeCPU(0x038C + x, a);
    popAddress();
}

void game::SUB_01EE48() {
    a = myMapper->readCPU(0x0450 + x);
    setLoadFlag(a);
    SUB_01EE4B();
    return;
}

void game::SUB_01EE4B() {
    if (flgZ) {
        goto L_01EE5E;
    }
    pushAddress(0xEE4F);
    SUB_01EE22();
    if (handleReturnAddress(poppedEntry.value, 0xEE4F)) return;
    a = myMapper->readCPU(0x03A8 + x);
    opSBC(myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x03A8 + x, a);
    if (!flgC) {
        opDEC(0x038C + x, 1);
    }
    popAddress();
    return;
L_01EE5E:
    pushAddress(0xEE60);
    SUB_01EE35();
    if (handleReturnAddress(poppedEntry.value, 0xEE60)) return;
    a = myMapper->readCPU(0x03A8 + x);
    opADC(myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x03A8 + x, a);
    if (!flgC) {
        goto L_01EE6E;
    }
    opINC(0x038C + x, 1);
L_01EE6E:
    popAddress();
}

void game::SUB_01EE6F() {
    a = myMapper->readCPU(0x04F8 + x);
    setLoadFlag(a);
    SUB_01EE78();
    return;
}


void game::SUB_01EE75() {
    a = myMapper->readCPU(0x0450 + x);
    setLoadFlag(a);
    SUB_01EE78();
    return;
}

void game::SUB_01EE78() {
    if (flgZ) {
        goto L_01EE88;
    }
    pushAddress(0xEE7C);
    SUB_01EE22();
    if (handleReturnAddress(poppedEntry.value, 0xEE7C)) return;
    a = myMapper->readCPU(0x0300 + x);
    opSBC(0x00);
    opAND(0x01);
    myMapper->writeCPU(0x0300 + x, a);
    popAddress();
    return;
L_01EE88:
    pushAddress(0xEE8A);
    SUB_01EE35();
    if (handleReturnAddress(poppedEntry.value, 0xEE8A)) return;
    a = myMapper->readCPU(0x0300 + x);
    opADC(0x00);
    myMapper->writeCPU(0x0300 + x, a);
    popAddress();
}

void game::SUB_01EE94() {
    pushAddress(0xEE96);
    SUB_01DD14();
    if (handleReturnAddress(poppedEntry.value, 0xEE96)) return;
    a = 0x08;
    y = 0xF9;
    myMapper->writeCPU(0x0016, a);
    myMapper->writeCPU(0x0017, y);
    opPLA();
    opPLA();
    callStack.pop_back();
    a = myMapper->readCPU(0x038C + x);
    SUB_01EA33();
    return;
}

void game::SUB_01EEA7() {
    a = myMapper->readCPU(0x0568 + x);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01EEB2;
    }
    opDEC(0x0568 + x, 1);
    opPLA();
    opPLA();
    callStack.pop_back();
    popAddress();
    return;
L_01EEB2:
    a = myMapper->readCPU(0x0488 + x);
    opAND(0x7F);
    myMapper->writeCPU(0x0488 + x, a);
    popAddress();
}

void game::SUB_01EEBB() {
    y = 0x00;
    a = myMapper->readCPU(0x0000);
    opSBC(myMapper->readCPU(0x0354 + x));
    if (!flgC) {
        opINY(1);
        opEOR(0xFF);
    }
    if (flgZ) {
        a = 0x01;
    }
    myMapper->writeCPU(0x0004, a);
    myMapper->writeCPU(0x04DC + x, y);
    y = 0x00;
    a = myMapper->readCPU(0x0001);
    opSBC(myMapper->readCPU(0x038C + x));
    if (!flgC) {
        opINY(1);
        opEOR(0xFF);
    }
    if (flgZ) {
        a = 0x01;
    }
    myMapper->writeCPU(0x0005, a);
    myMapper->writeCPU(0x0450 + x, y);
    myMapper->writeCPU(0x004E, x);
    y = 0x00;
    x = myMapper->readCPU(0x0004);
    a = myMapper->readCPU(0x0005);
    if (a >= myMapper->readCPU(0x0004)) {
        goto L_01EEF8;
    }
    a = myMapper->readCPU(0x0004);
    x = myMapper->readCPU(0x0005);
    opINY(1);
L_01EEF8:
    myMapper->writeCPU(0x0003, a);
    myMapper->writeCPU(0x0009, y);
    y = 0x00;
    pushAddress(0xEF00);
    SUB_01CA41();
    if (handleReturnAddress(poppedEntry.value, 0xEF00)) return;
    x = myMapper->readCPU(0x004E);
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

void game::SUB_01EF13() {
    a = myMapper->readCPU(0x0354 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x04DC + x));
    y = 0x00;
    if (!flgC) {
        opDEY(1);
    }
    myMapper->writeCPU(0x0001, y);
    y = myMapper->readCPU(0x04F8 + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01EF30;
    }
    do {
        flgC = false;
        opBIT(myMapper->readCPU(0x0001));
        if (!flgN) {
            goto L_01EF2C;
        }
        flgC = true;
    L_01EF2C:
        opROR_A(1);
        opDEY(1);
    } while (!flgZ);
L_01EF30:
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x03E0 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x03E0 + x, a);
    a = myMapper->readCPU(0x03C4 + x);
    opSBC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x03C4 + x, a);
    SUB_01EF43();
    return;
}

void game::SUB_01EF43() {
    a = myMapper->readCPU(0x0370 + x);
    opADC(myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x0370 + x, a);
    a = myMapper->readCPU(0x0354 + x);
    opADC(myMapper->readCPU(0x03C4 + x));
    myMapper->writeCPU(0x0354 + x, a);
    popAddress();
}

void game::SUB_01EF56() {
    a = myMapper->readCPU(0x0370 + x);
    opSBC(myMapper->readCPU(0x03E0 + x));
    myMapper->writeCPU(0x0370 + x, a);
    a = myMapper->readCPU(0x0354 + x);
    opSBC(myMapper->readCPU(0x03C4 + x));
    myMapper->writeCPU(0x0354 + x, a);
    popAddress();
}

void game::SUB_01EF69() {
    a = myMapper->readCPU(0x0300 + x);
    opAND(0x01);
    if (flgZ) {
        SUB_01EF7C();
        return;
    }
    y = 0x00;
    a = myMapper->readCPU(0x038C + x);
    opCMP(a, 0x80);
    if (flgC) {
        SUB_01EF7F();
        return;
    }
    opINY(1);
    if (!flgZ) {
        SUB_01EF7F();
        return;
    }
    SUB_01EF7C();
    return;
}

void game::SUB_01EF7C() {
    pushAddress(0xEF7E);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0xEF7E)) return;
    SUB_01EF7F();
    return;
}

void game::SUB_01EF7F() {
    a = y;
    myMapper->writeCPU(0x0450 + x, a);
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

void game::SUB_01EF92() {
    pushAddress(0xEF94);
    SUB_01EF13();
    if (handleReturnAddress(poppedEntry.value, 0xEF94)) return;
    SUB_01EE48();
    return;
}

void game::SUB_01EF98() {
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01EF9E();
        return;
    }
    SUB_01EF9C();
    return;
}

void game::SUB_01EF9C() {
    a = 0x10;
    SUB_01EF9E();
    return;
}

void game::SUB_01EF9E() {
    myMapper->writeCPU(0x004B, a);
    myMapper->writeCPU(0x004C, 0x00);
    a = myMapper->readCPU(0x0354 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x004B));
    myMapper->writeCPU(0x004D, a);
    SUB_01EC21();
    return;
}

void game::SUB_01EFAF() {
    a = myMapper->readCPU(0x0354 + x);
    opAND(0xF8);
    myMapper->writeCPU(0x0354 + x, a);
    popAddress();
}

void game::SUB_01EFB8() {
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0xEFBD);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xEFBD)) return;
    SUB_01EFCA();
    return;
}

void game::SUB_01EFCA() {
    a = x;
    flgC = false;
    opADC(0x05);
    y = a;
    myMapper->writeCPU(0x004F, y);
    a = myMapper->readCPU(0x0434 + y);
    opCMP(a, 0x12);
    if (!flgZ) {
        SUB_01EFF5();
        return;
    }
    a = myMapper->readCPU(0x001A);
    opAND(0x07);
    if (flgZ) {
        pushAddress(0xEFE0);
        SUB_01EF84();
        if (handleReturnAddress(poppedEntry.value, 0xEFE0)) return;
        opCMP(a, 0x40);
        if (flgC) {
            goto L_01EFE7;
        }
        if (!flgC) {
            SUB_01EFF5();
            return;
        }
    }
L_01EFE7:
    y = myMapper->readCPU(0x004F);
    myMapper->writeCPU(0x038C + x, myMapper->readCPU(0x038C + y));
    SUB_01EFEF();
    return;
}

void game::SUB_01EFEF() {
    popAddress();
}

void game::SUB_01EFF0() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_01EFEF();
        return;
    }
    SUB_01EFF5();
    return;
}

void game::SUB_01EFF5() {
    pushAddress(0xEFF7);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0xEFF7)) return;
    a = 0x3D;
    pushAddress(0xEFFC);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xEFFC)) return;
    a = 0x01;
    SUB_01F131();
    return;
}

void game::SUB_01F002() {
    pushAddress(0xF004);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0xF004)) return;
    myMapper->writeCPU(0x004C, 0x00);
    a = myMapper->readCPU(0x0354 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x004D, a);
    pushAddress(0xF013);
    SUB_01EC21();
    if (handleReturnAddress(poppedEntry.value, 0xF013)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (flgZ) {
        SUB_01F028();
        return;
    }
    pushAddress(0xF01A);
    SUB_01EFAF();
    if (handleReturnAddress(poppedEntry.value, 0xF01A)) return;
    a = 0x3C;
    pushAddress(0xF01F);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xF01F)) return;
    myMapper->writeCPU(0x054C + x, 0x08);
    opINC(0x046C + x, 1);
    SUB_01F028();
    return;
}

void game::SUB_01F028() {
    popAddress();
}

void game::SUB_01F029() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_01F028();
        return;
    }
    SUB_01F02E();
    return;
}

void game::SUB_01F02E() {
    a = myMapper->readCPU(0x005B);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0xF034);
        SUB_01EF7C();
        if (handleReturnAddress(poppedEntry.value, 0xF034)) return;
    }
    a = 0x3D;
    pushAddress(0xF039);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xF039)) return;
    pushAddress(0xF03C);
    SUB_01EF84();
    if (handleReturnAddress(poppedEntry.value, 0xF03C)) return;
    opCMP(a, 0x40);
    if (!flgC) {
        opCMP(myMapper->readCPU(0x0450), myMapper->readCPU(0x0450 + x));
        if (flgZ) {
            goto L_01F05A;
        }
        y = 0x80;
        a = 0x03;
        pushAddress(0xF04F);
        SUB_01ECEA();
        if (handleReturnAddress(poppedEntry.value, 0xF04F)) return;
        y = 0x00;
        a = 0x01;
        pushAddress(0xF056);
        SUB_01EC72();
        if (handleReturnAddress(poppedEntry.value, 0xF056)) return;
        goto L_01F068;
    }
L_01F05A:
    a = 0x01;
    y = 0x00;
    pushAddress(0xF060);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0xF060)) return;
    y = 0x40;
    a = 0x02;
    pushAddress(0xF067);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0xF067)) return;
L_01F068:
    a = 0x03;
    SUB_01F131();
    return;
}

void game::SUB_01F06D() {
    pushAddress(0xF06F);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0xF06F)) return;
    SUB_01F002();
    return;
}

void game::SUB_01F073() {
    opDEC(0x054C + x, 1);
    if (!flgZ) {
        SUB_01F028();
        return;
    }
    SUB_01F02E();
    return;
}

void game::SUB_01F07B() {
    pushAddress(0xF07D);
    SUB_01EF13();
    if (handleReturnAddress(poppedEntry.value, 0xF07D)) return;
    SUB_01EE48();
    return;
}

void game::SUB_01F081() {
    a = myMapper->readCPU(0x046C + x);
    pushAddress(0xF086);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xF086)) return;
    SUB_01F095();
    return;
}

void game::SUB_01F095() {
    myMapper->writeCPU(0x004E, x);
    a = 0x0E;
    pushAddress(0xF09B);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xF09B)) return;
    x = myMapper->readCPU(0x004E);
    pushAddress(0xF0A0);
    SUB_01FCB9();
    if (handleReturnAddress(poppedEntry.value, 0xF0A0)) return;
    a = 0x05;
    y = 0x80;
    pushAddress(0xF0A7);
    SUB_01ECEA();
    if (handleReturnAddress(poppedEntry.value, 0xF0A7)) return;
    myMapper->writeCPU(0x04DC + x, 0x00);
    a = 0x01;
    SUB_01F131();
    return;
}

void game::SUB_01F0B2() {
    a = 0x06;
    SUB_01F131();
    return;
}

void game::SUB_01F0B7() {
    a = 0x80;
    myMapper->writeCPU(0x0488 + x, a);
    pushAddress(0xF0BE);
    SUB_01EC50();
    if (handleReturnAddress(poppedEntry.value, 0xF0BE)) return;
    if (!(myMapper->readCPU(0x03C4 + x) & 0x80)) {
        jump(0xF101);
        return;
    }
    a = myMapper->readCPU(0x0354 + x);
    opCMP(a, 0xC0);
    if (flgC) {
        SUB_01F0B2();
        return;
    }
    pushAddress(0xF0CD);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0xF0CD)) return;
    if (myMapper->readCPU(0x0014) == 0) {
        jump(0xF101);
        return;
    }
    if (myMapper->readCPU(0x04DC + x) != 0) {
        goto L_01F0E3;
    }
    myMapper->writeCPU(0x004E, x);
    a = 0x0D;
    pushAddress(0xF0DD);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xF0DD)) return;
    x = myMapper->readCPU(0x004E);
    opINC(0x04DC + x, 1);
L_01F0E3:
    a = myMapper->readCPU(0x0354 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0354 + x, a);
    pushAddress(0xF0ED);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0xF0ED)) return;
    y = 0xC0;
    a = 0x00;
    pushAddress(0xF0F4);
    SUB_01EC72();
    if (handleReturnAddress(poppedEntry.value, 0xF0F4)) return;
    a = 0x08;
    y = 0x02;
    SUB_01ED34();
    return;
}

void game::SUB_01F0FC() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_01F102();
        return;
    }
    SUB_01F101();
    return;
}

void game::SUB_01F101() {
    popAddress();
}

void game::SUB_01F102() {
    a = 0x04;
    pushAddress(0xF106);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xF106)) return;
    myMapper->writeCPU(0x0488 + x, 0x00);
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0xF119 + y);
    y = 0x03;
    SUB_01ED34();
    return;
}

void game::SUB_01F11D() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        SUB_01F135();
        return;
    }
    pushAddress(0xF124);
    SUB_01EE48();
    if (handleReturnAddress(poppedEntry.value, 0xF124)) return;
    pushAddress(0xF127);
    SUB_01EF9C();
    if (handleReturnAddress(poppedEntry.value, 0xF127)) return;
    a = myMapper->readCPU(0x0014);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01F134();
        return;
    }
    pushAddress(0xF12E);
    SUB_01F1D2();
    if (handleReturnAddress(poppedEntry.value, 0xF12E)) return;
    a = 0x01;
    SUB_01F131();
    return;
}

void game::SUB_01F131() {
    myMapper->writeCPU(0x046C + x, a);
    SUB_01F134();
    return;
}

void game::SUB_01F134() {
    popAddress();
}

void game::SUB_01F135() {
    a = 0x06;
    pushAddress(0xF139);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xF139)) return;
    y = 0x04;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_01F149();
        return;
    }
    SUB_01F13E();
    return;
}

void game::SUB_01F13E() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01F144;
    }
    popAddress();
    return;
L_01F144:
    pushAddress(0xF146);
    SUB_01FCA2();
    if (handleReturnAddress(poppedEntry.value, 0xF146)) return;
    y = 0x05;
    SUB_01F149();
    return;
}

void game::SUB_01F149() {
    a = 0x10;
    SUB_01ED34();
    return;
}

void game::SUB_01F14E() {
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01F154;
    }
    popAddress();
    return;
L_01F154:
    pushAddress(0xF156);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0xF156)) return;
    SUB_01F102();
    return;
}

void game::SUB_01F15A() {
    myMapper->writeCPU(0x004E, x);
    a = 0x0F;
    pushAddress(0xF160);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xF160)) return;
    x = myMapper->readCPU(0x004E);
    pushAddress(0xF165);
    SUB_01FCB9();
    if (handleReturnAddress(poppedEntry.value, 0xF165)) return;
    myMapper->writeCPU(0x0434 + x, 0x32);
    popAddress();
}

void game::SUB_01F16C() {
    pushAddress(0xF16E);
    SUB_01EF7C();
    if (handleReturnAddress(poppedEntry.value, 0xF16E)) return;
    y = myMapper->readCPU(0x046C + x);
    setLoadFlag(y);
    if (flgZ) {
        goto L_01F19D;
    }
    opDEY(1);
    if (flgZ) {
        goto L_01F1AB;
    }
    opDEY(1);
    if (flgZ) {
        goto L_01F1C9;
    }
    opDEC(0x054C + x, 1);
    if (flgZ) {
        goto L_01F182;
    }
    SUB_01EE94();
    return;
L_01F182:
    pushAddress(0xF184);
    SUB_01ED49();
    if (handleReturnAddress(poppedEntry.value, 0xF184)) return;
    a = myMapper->readCPU(0x006F);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0xF199 + y);
    y = 0x00;
    do {
        do {
            myMapper->writeCPU(0x054C + x, a);
            a = y;
        L_01F193:
            myMapper->writeCPU(0x046C + x, a);
            SUB_01EE94();
            return;
        L_01F19D:
            opDEC(0x054C + x, 1);
            if (flgZ) {
                goto L_01F1A5;
            }
            SUB_01EE94();
            return;
        L_01F1A5:
            a = 0x18;
            y = 0x01;
            setLoadFlag(y);
        } while (!flgZ);
    L_01F1AB:
        y = 0x00;
        opDEC(0x054C + x, 1);
        if (!flgZ) {
            a = myMapper->readCPU(0x001A);
            opAND(0x01);
            if (flgZ) {
                goto L_01F1BA;
            }
            y = 0x03;
        L_01F1BA:
            a = y;
            myMapper->writeCPU(0x0338 + x, a);
            SUB_01EE94();
            return;
        }
        myMapper->writeCPU(0x0338 + x, y);
        a = 0x02;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_01F193;
        }
    L_01F1C9:
        pushAddress(0xF1CB);
        SUB_01ED49();
        if (handleReturnAddress(poppedEntry.value, 0xF1CB)) return;
        a = 0x28;
        y = 0x03;
        setLoadFlag(y);
    } while (!flgZ);
    SUB_01F1D2();
    return;
}

void game::SUB_01F1D2() {
    a = 0x00;
    myMapper->writeCPU(0x03C4 + x, a);
    myMapper->writeCPU(0x03E0 + x, a);
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
    SUB_01F378();
    return;
}

void game::SUB_01F378() {
    a = myMapper->readCPU(0x0166 + y);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_01F383();
        return;
    }
    SUB_01F37D();
    return;
}

void game::SUB_01F37D() {
    opINY(1);
    if (y < 0x06) {
        jump(0xF378);
        return;
    }
    popAddress();
}

void game::SUB_01F383() {
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
            SUB_01F37D();
            return;
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
        SUB_01F37D();
        return;
    }
L_01F3C8:
    pushAddress(0xF3CA);
    SUB_01F4BE();
    if (handleReturnAddress(poppedEntry.value, 0xF3CA)) return;
    a = myMapper->readCPU(0xF41E);
    opPHA();
    a = myMapper->readCPU(0xF41D);
    opPHA();
    pushManualAddress(0xF37C);
    myMapper->writeCPU(0x000C, y);
    a = myMapper->readCPU(0x0166 + y);
    opAND(0x3F);
    pushAddress(0xF3DC);
    SUB_01CA6D();
    if (handleReturnAddress(poppedEntry.value, 0xF3DC)) return;
    SUB_01F41D();
    return;
}

void game::SUB_01F41D() {
    //NOP
    SUB_01F41F();
    return;
}

void game::SUB_01F41F() {
    do {
        a = myMapper->readCPU(0x0434 + x);
        setLoadFlag(a);
        if (flgZ) {
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

void game::SUB_01F447() {
    pushAddress(0xF449);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0xF449)) return;
    myMapper->writeCPU(0x0450 + x, myMapper->readCPU(0x004F));
    a = myMapper->readCPU(0x000E);
    pushAddress(0xF453);
    SUB_01EF04();
    if (handleReturnAddress(poppedEntry.value, 0xF453)) return;
    y = myMapper->readCPU(0x000C);
    myMapper->writeCPU(0x0354 + x, myMapper->readCPU(0x017E + y));
    myMapper->writeCPU(0x038C + x, myMapper->readCPU(0x0172 + y));
    popAddress();
}

void game::SUB_01F463() {
    a = myMapper->readCPU(0x016C + y);
    opORA(0x80);
    myMapper->writeCPU(0x016C + y, a);
    myMapper->writeCPU(0x0530 + x, y);
    popAddress();
}

void game::SUB_01F470() {
    x = 0x04;
    do {
        a = myMapper->readCPU(0x0434 + x);
        if (a == 0x1A) {
            goto L_01F47E;
        }
        a = 0x32;
        myMapper->writeCPU(0x0434 + x, a);
    L_01F47E:
        opINX(1);
    } while (x < 0x0E);
    popAddress();
}

void game::SUB_01F484() {
    pushAddress(0xF486);
    SUB_01F447();
    if (handleReturnAddress(poppedEntry.value, 0xF486)) return;
    myMapper->writeCPU(0x046C + x, 0x80);
    popAddress();
}

void game::SUB_01F48D() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (!flgN) {
        goto L_01F495;
    }
    opPLA();
    opPLA();
    callStack.pop_back();
    popAddress();
    return;
L_01F495:
    opORA(0x80);
    myMapper->writeCPU(0x016C + y, a);
    pushAddress(0xF49C);
    SUB_01F470();
    if (handleReturnAddress(poppedEntry.value, 0xF49C)) return;
    pushAddress(0xF49F);
    SUB_01F4A9();
    if (handleReturnAddress(poppedEntry.value, 0xF49F)) return;
    x = 0x07;
    myMapper->writeCPU(0x000D, x);
    myMapper->writeCPU(0x0530 + x, y);
    popAddress();
}

void game::SUB_01F4A9() {
    x = 0x00;
    a = myMapper->readCPU(0x038C);
    flgC = true;
    opSBC(myMapper->readCPU(0x0172 + y));
    if (flgC) {
        goto L_01F4B7;
    }
    opEOR(0xFF);
    opINX(1);
L_01F4B7:
    myMapper->writeCPU(0x004B, a);
    myMapper->writeCPU(0x004F, x);
    x = myMapper->readCPU(0x000D);
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

void game::SUB_01F4D2() {
    if (myMapper->readCPU(0x0184 + y) != 0) {
        goto L_01F4E3;
    }
    x = 0x09;
    do {
        if (myMapper->readCPU(0x0434 + x) == 0) {
            goto L_01F4E4;
        }
    L_01F4DE:
        opINX(1);
    } while (x < 0x0C);
L_01F4E3:
    popAddress();
    return;
L_01F4E4:
    myMapper->writeCPU(0x000D, x);
    a = x;
    flgC = true;
    opSBC(0x05);
    y = a;
    if (myMapper->readCPU(0x0434 + y) != 0) {
        goto L_01F4DE;
    }
    a = myMapper->readCPU(0x006F);
    opAND(0x01);
    myMapper->writeCPU(0x004B, a);
    a = 0x12;
    y = myMapper->readCPU(0x004B);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_01F4FE;
    }
    a = 0xEE;
L_01F4FE:
    myMapper->writeCPU(0x038C + x, a);
    a = y;
    opEOR(0x01);
    myMapper->writeCPU(0x0450 + x, a);
    y = myMapper->readCPU(0x000C);
    myMapper->writeCPU(0x0184 + y, 0x38);
    a = myMapper->readCPU(0x018A + y);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x018A + y, a);
    opAND(0x03);
    y = a;
    a = myMapper->readCPU(0xF52F + y);
    y = myMapper->readCPU(0x000C);
    opADC(myMapper->readCPU(0x017E + y));
    myMapper->writeCPU(0x0354 + x, a);
    a = 0x12;
    pushAddress(0xF529);
    SUB_01F42C();
    if (handleReturnAddress(poppedEntry.value, 0xF529)) return;
    a = 0x53;
    SUB_01EF04();
    return;
}

void game::SUB_01F533() {
    a = myMapper->readCPU(0x0028);
    if (a != 0x02) {
        goto L_01F53C;
    }
    jump(0x8182);
    return;
L_01F53C:
    jump(0x87A6);
    return;
}

void game::SUB_01F53F() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xC89D + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01F549;
    }
    jump(0x80E3);
    return;
L_01F549:
    jump(0x87E2);
    return;
}

void game::SUB_01F54C() {
    a = myMapper->readCPU(0x0028);
    if (a != 0x02) {
        goto L_01F555;
    }
    jump(0x80E7);
    return;
L_01F555:
    jump(0x87E6);
    return;
}

void game::SUB_01F558() {
    x = myMapper->readCPU(0x0028);
    a = myMapper->readCPU(0xC89D + x);
    if (a == 0x04) {
        jump(0x8431);
        return;
    }
    if (a != 0x07) {
        goto L_01F56B;
    }
    jump(0x85FB);
    return;
L_01F56B:
    jump(0x8A40);
    return;
}

void game::SUB_01F56E() {
    a = myMapper->readCPU(0x0028);
    if (a == 0x0F) {
        jump(0x8A44);
        return;
    }
    if (a < 0x08) {
        goto L_01F57E;
    }
    jump(0x85FF);
    return;
L_01F57E:
    jump(0x8435);
    return;
}

void game::SUB_01F581() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_01F593;
    }
    myMapper->writeCPU(0x004B, 0x07);
    x = 0x04;
    pushAddress(0xF58E);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0xF58E)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_01F594;
    }
L_01F593:
    popAddress();
    return;
L_01F594:
    myMapper->writeCPU(0x000D, x);
    pushAddress(0xF598);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0xF598)) return;
    myMapper->writeCPU(0x054C + x, 0x3C);
    myMapper->writeCPU(0x000E, 0x4D);
    a = 0x0C;
    SUB_01F447();
    return;
}

void game::SUB_01F5A7() {
    a = myMapper->readCPU(0x0028);
    if (a != 0x06) {
        goto L_01F5B0;
    }
    jump(0x84E7);
    return;
L_01F5B0:
    jump(0x8588);
    return;
}

void game::SUB_01F5B3() {
    a = myMapper->readCPU(0x016C + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_01F5C5;
    }
    myMapper->writeCPU(0x004B, 0x07);
    x = 0x04;
    pushAddress(0xF5C0);
    SUB_01F41F();
    if (handleReturnAddress(poppedEntry.value, 0xF5C0)) return;
    opCMP(x, 0xFF);
    if (!flgZ) {
        goto L_01F5C6;
    }
L_01F5C5:
    popAddress();
    return;
L_01F5C6:
    pushAddress(0xF5C8);
    SUB_01F463();
    if (handleReturnAddress(poppedEntry.value, 0xF5C8)) return;
    myMapper->writeCPU(0x054C + x, 0x18);
    myMapper->writeCPU(0x000E, 0x48);
    a = 0x0E;
    SUB_01F447();
    return;
}

void game::SUB_01F5D7() {
    a = myMapper->readCPU(0x0028);
    if (a == 0x0D) {
        jump(0x89D4);
        return;
    }
    if (a != 0x11) {
        goto L_01F5E7;
    }
    jump(0x8B13);
    return;
L_01F5E7:
    jump(0x8567);
    return;
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
    SUB_01F62D();
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
        SUB_01F68C();
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
        SUB_01F68C();
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
        SUB_01F68C();
        return;
    }
    opCMP(a, 0x07);
    if (flgZ) {
        SUB_01F68C();
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
        SUB_01F68C();
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
            SUB_01F87C();
            return;
        }
        a = myMapper->readCPU(0x0019);
        opCMP(a, 0x02);
        if (!flgZ) {
            SUB_01F87C();
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
        SUB_01F87C();
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
//    x = 0x00;
//    do {
//        opINX(1);
//        if (flgZ) {
//            goto L_01F8D3;
//        }
//        a = myMapper->readCPU(0x2002);
//        opAND(0x40);
//    } while (!flgZ);
//L_01F8D3:
//    x = 0x00;
//    do {
//        opINX(1);
//        if (flgZ) {
//            goto L_01F8E6;
//        }
//        a = myMapper->readCPU(0x2002);
//        opAND(0x40);
//        if (!flgZ) {
//            goto L_01F8E6;
//        }
//        a = myMapper->readCPU(0x2002);
//        opAND(0x40);
//    } while (flgZ);

    wait(2);
    needWaitScanline = true;
    waitScanline = 40;

//L_01F8E6:
//    y = 0x2C;
//    do {
//        opDEY(1);
//    } while (!flgZ);
//    a = myMapper->readCPU(0x2002);
//    a = myMapper->readCPU(0x002E);
//    x = myMapper->readCPU(0x0000);
//    myMapper->writeCPU(0x2005, a);
//    a = 0x00;
//    myMapper->writeCPU(0x2005, a);
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
            SUB_01F99B();
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
    opCMP(a, 0xB0);
    if (!flgC) {
        goto L_01F9B1;
    }
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_01F99B();
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
    SUB_01F972();
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

void game::SUB_01FAB4() {
    myMapper->writeCPU(0x004E, x);
    y = 0x00;
    myMapper->writeCPU(0x004B, 0x20);
    x = myMapper->readCPU(0x0020);
    do {
        a = myMapper->readCPU(0xFACF + y);
        opINY(1);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        opDEC(0x004B, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0020, x);
    x = myMapper->readCPU(0x004E);
    popAddress();
}

void game::SUB_01FAEF() {
    pushAddress(0xFAF1);
    jump(0x9359);
    if (handleReturnAddress(poppedEntry.value, 0xFAF1)) return;
    x = myMapper->readCPU(0x007E);
    setLoadFlag(x);
    if (flgZ) {
        SUB_01FB05();
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
        SUB_01FB05();
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
    SUB_01CC95();
    return;
}

void game::SUB_01FB22() {
    popAddress();
}

void game::SUB_01FC97() {
    pushAddress(0xFC99);
    SUB_01C1D4();
    if (handleReturnAddress(poppedEntry.value, 0xFC99)) return;
    pushAddress(0xFC9C);
    jump(0x96C1);
    if (handleReturnAddress(poppedEntry.value, 0xFC9C)) return;
    y = 0x05;
    SUB_01C1D6();
    return;
}

void game::SUB_01FCA2() {
    y = 0x05;
    pushAddress(0xFCA6);
    SUB_01C1D6();
    if (handleReturnAddress(poppedEntry.value, 0xFCA6)) return;
    a = myMapper->readCPU(0x0028);
    opCMP(a, 0x02);
    if (!flgZ) {
        goto L_01FCB3;
    }
    pushAddress(0xFCAF);
    jump(0x8098);
    if (handleReturnAddress(poppedEntry.value, 0xFCAF)) return;
    SUB_01C1D4();
    return;
L_01FCB3:
    pushAddress(0xFCB5);
    jump(0x8910);
    if (handleReturnAddress(poppedEntry.value, 0xFCB5)) return;
    SUB_01C1D4();
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
    SUB_01C1D4();
    return;
L_01FCCA:
    pushAddress(0xFCCC);
    jump(0x88B7);
    if (handleReturnAddress(poppedEntry.value, 0xFCCC)) return;
    SUB_01C1D4();
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
    SUB_01C1D6();
    return;
}

void game::SUB_01FCF0() {
    a = 0x42;
    pushAddress(0xFCF4);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xFCF4)) return;
    y = 0x05;
    SUB_01C1D6();
    return;
}

void game::SUB_01FCFA() {
    a = 0x12;
    pushAddress(0xFCFE);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xFCFE)) return;
    y = 0x05;
    SUB_01C1D6();
    return;
}

void game::SUB_01FD04() {
    a = 0x13;
    pushAddress(0xFD08);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xFD08)) return;
    y = 0x05;
    SUB_01C1D6();
    return;
}

void game::SUB_01FD0E() {
    a = 0x1D;
    pushAddress(0xFD12);
    SUB_01C1A7();
    if (handleReturnAddress(poppedEntry.value, 0xFD12)) return;
    y = 0x05;
    SUB_01C1D6();
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
    SUB_01C1D6();
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
    case 0x000141:
        SUB_000141();
        break;
    case 0x000135:
        SUB_000135();
        break;
    case 0x00015A:
        SUB_00015A();
        break;
    case 0x00016E:
        SUB_00016E();
        break;
    case 0x0006E4:
        SUB_0006E4();
        break;
    case 0x014056:
        SUB_014056();
        break;
    case 0x014057:
        SUB_014057();
        break;
    case 0x014223:
        SUB_014223();
        break;
    case 0x0142DF:
        SUB_0142DF();
        break;
    case 0x014824:
        SUB_014824();
        break;
    case 0x014C95:
        SUB_014C95();
        break;
    case 0x0151A2:
        SUB_0151A2();
        break;
    case 0x0153AF:
        SUB_0153AF();
        break;
    case 0x0180EC:
        SUB_0180EC();
        break;
    case 0x018304:
        SUB_018304();
        break;
    case 0x018DC2:
        SUB_018DC2();
        break;
    case 0x01962C:
        SUB_01962C();
        break;
    case 0x0197A7:
        SUB_0197A7();
        break;
    case 0x01977A:
        SUB_01977A();
        break;
    case 0x0198AA:
        SUB_0198AA();
        break;
    case 0x01990A:
        SUB_01990A();
        break;
    case 0x019AF8:
        SUB_019AF8();
        break;
    case 0x019B89:
        SUB_019B89();
        break;
    case 0x019B7C:
        SUB_019B7C();
        break;
    case 0x019BE3:
        SUB_019BE3();
        break;
    case 0x019C6D:
        SUB_019C6D();
        break;
    case 0x019DC0:
        SUB_019DC0();
        break;
    case 0x019ECB:
        SUB_019ECB();
        break;
    case 0x019F60:
        SUB_019F60();
        break;
    case 0x01A0CD:
        SUB_01A0CD();
        break;
    case 0x01A4D7:
        SUB_01A4D7();
        break;
    case 0x01A4AE:
        SUB_01A4AE();
        break;
    case 0x01A723:
        SUB_01A723();
        break;
    case 0x01A824:
        SUB_01A824();
        break;
    case 0x01AAE1:
        SUB_01AAE1();
        break;
    case 0x01B858:
        SUB_01B858();
        break;
    case 0x01B9D6:
        SUB_01B9D6();
        break;
    case 0x01C254:
        SUB_01C254();
        break;
    case 0x01C282:
        SUB_01C282();
        break;
    case 0x01C57B:
        SUB_01C57B();
        break;
    case 0x01DBE5:
        SUB_01DBE5();
        break;
    case 0x01DDD7:
        SUB_01DDD7();
        break;
    case 0x01DEA3:
        SUB_01DEA3();
        break;
    case 0x01DE9D:
        SUB_01DE9D();
        break;
    case 0x01E109:
        SUB_01E109();
        break;
    case 0x01E1CD:
        SUB_01E1CD();
        break;
    case 0x01E1EB:
        SUB_01E1EB();
        break;
    case 0x01E2A9:
        SUB_01E2A9();
        break;
    case 0x01E387:
        SUB_01E387();
        break;
    case 0x01E9CA:
        SUB_01E9CA();
        break;
    case 0x01E9E0:
        SUB_01E9E0();
        break;
    case 0x01EA77:
        SUB_01EA77();
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
    case 0x01F101:
        SUB_01F101();
        break;
    case 0x01F378:
        SUB_01F378();
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
    case 0x014008:
        SUB_014008();
        break;
    case 0x014044:
        SUB_014044();
        break;
    case 0x014098:
        SUB_014098();
        break;
    case 0x0140C7:
        SUB_0140C7();
        break;
    case 0x0140E0:
        SUB_0140E0();
        break;
    case 0x0140F7:
        SUB_0140F7();
        break;
    case 0x014156:
        SUB_014156();
        break;
    case 0x01417A:
        SUB_01417A();
        break;
    case 0x01418C:
        SUB_01418C();
        break;
    case 0x014194:
        SUB_014194();
        break;
    case 0x0141CB:
        SUB_0141CB();
        break;
    case 0x01424D:
        SUB_01424D();
        break;
    case 0x0142C5:
        SUB_0142C5();
        break;
    case 0x0142DA:
        SUB_0142DA();
        break;
    case 0x0142E6:
        SUB_0142E6();
        break;
    case 0x014304:
        SUB_014304();
        break;
    case 0x014356:
        SUB_014356();
        break;
    case 0x014369:
        SUB_014369();
        break;
    case 0x014389:
        SUB_014389();
        break;
    case 0x014397:
        SUB_014397();
        break;
    case 0x0143A3:
        SUB_0143A3();
        break;
    case 0x0143C9:
        SUB_0143C9();
        break;
    case 0x0143ED:
        SUB_0143ED();
        break;
    case 0x0143F3:
        SUB_0143F3();
        break;
    case 0x0143FF:
        SUB_0143FF();
        break;
    case 0x014437:
        SUB_014437();
        break;
    case 0x014453:
        SUB_014453();
        break;
    case 0x014456:
        SUB_014456();
        break;
    case 0x0144FF:
        SUB_0144FF();
        break;
    case 0x014538:
        SUB_014538();
        break;
    case 0x014555:
        SUB_014555();
        break;
    case 0x014571:
        SUB_014571();
        break;
    case 0x0145B7:
        SUB_0145B7();
        break;
    case 0x0145D0:
        SUB_0145D0();
        break;
    case 0x0145DC:
        SUB_0145DC();
        break;
    case 0x0145D6:
        SUB_0145D6();
        break;
    case 0x01463E:
        SUB_01463E();
        break;
    case 0x014644:
        SUB_014644();
        break;
    case 0x01467A:
        SUB_01467A();
        break;
    case 0x01468A:
        SUB_01468A();
        break;
    case 0x0146A8:
        SUB_0146A8();
        break;
    case 0x0146D2:
        SUB_0146D2();
        break;
    case 0x014701:
        SUB_014701();
        break;
    case 0x014723:
        SUB_014723();
        break;
    case 0x014787:
        SUB_014787();
        break;
    case 0x0147AA:
        SUB_0147AA();
        break;
    case 0x0147F6:
        SUB_0147F6();
        break;
    case 0x01481F:
        SUB_01481F();
        break;
    case 0x014853:
        SUB_014853();
        break;
    case 0x014899:
        SUB_014899();
        break;
    case 0x0148B7:
        SUB_0148B7();
        break;
    case 0x014910:
        SUB_014910();
        break;
    case 0x01493F:
        SUB_01493F();
        break;
    case 0x01496C:
        SUB_01496C();
        break;
    case 0x014979:
        SUB_014979();
        break;
    case 0x014992:
        SUB_014992();
        break;
    case 0x0149BF:
        SUB_0149BF();
        break;
    case 0x0149E2:
        SUB_0149E2();
        break;
    case 0x0149F8:
        SUB_0149F8();
        break;
    case 0x014A04:
        SUB_014A04();
        break;
    case 0x014A1E:
        SUB_014A1E();
        break;
    case 0x014A56:
        SUB_014A56();
        break;
    case 0x014ADA:
        SUB_014ADA();
        break;
    case 0x014B08:
        SUB_014B08();
        break;
    case 0x014B22:
        SUB_014B22();
        break;
    case 0x014B41:
        SUB_014B41();
        break;
    case 0x014B5F:
        SUB_014B5F();
        break;
    case 0x014BB7:
        SUB_014BB7();
        break;
    case 0x014BE4:
        SUB_014BE4();
        break;
    case 0x014BF9:
        SUB_014BF9();
        break;
    case 0x014C12:
        SUB_014C12();
        break;
    case 0x014C2F:
        SUB_014C2F();
        break;
    case 0x014C51:
        SUB_014C51();
        break;
    case 0x014C9A:
        SUB_014C9A();
        break;
    case 0x014CD3:
        SUB_014CD3();
        break;
    case 0x014CF0:
        SUB_014CF0();
        break;
    case 0x014D0C:
        SUB_014D0C();
        break;
    case 0x014D4A:
        SUB_014D4A();
        break;
    case 0x014D5F:
        SUB_014D5F();
        break;
    case 0x014D65:
        SUB_014D65();
        break;
    case 0x014D6B:
        SUB_014D6B();
        break;
    case 0x014DC6:
        SUB_014DC6();
        break;
    case 0x014EB8:
        SUB_014EB8();
        break;
    case 0x014ECE:
        SUB_014ECE();
        break;
    case 0x014EDA:
        SUB_014EDA();
        break;
    case 0x014EF1:
        SUB_014EF1();
        break;
    case 0x014F23:
        SUB_014F23();
        break;
    case 0x014F80:
        SUB_014F80();
        break;
    case 0x014FD0:
        SUB_014FD0();
        break;
    case 0x014FDE:
        SUB_014FDE();
        break;
    case 0x014FFD:
        SUB_014FFD();
        break;
    case 0x015036:
        SUB_015036();
        break;
    case 0x015053:
        SUB_015053();
        break;
    case 0x0150AA:
        SUB_0150AA();
        break;
    case 0x0150BE:
        SUB_0150BE();
        break;
    case 0x0150F8:
        SUB_0150F8();
        break;
    case 0x015142:
        SUB_015142();
        break;
    case 0x01514A:
        SUB_01514A();
        break;
    case 0x015158:
        SUB_015158();
        break;
    case 0x01516A:
        SUB_01516A();
        break;
    case 0x01517C:
        SUB_01517C();
        break;
    case 0x01519D:
        SUB_01519D();
        break;
    case 0x0151B2:
        SUB_0151B2();
        break;
    case 0x0151E9:
        SUB_0151E9();
        break;
    case 0x015225:
        SUB_015225();
        break;
    case 0x01522E:
        SUB_01522E();
        break;
    case 0x015267:
        SUB_015267();
        break;
    case 0x015284:
        SUB_015284();
        break;
    case 0x0152A0:
        SUB_0152A0();
        break;
    case 0x0152E6:
        SUB_0152E6();
        break;
    case 0x0152FF:
        SUB_0152FF();
        break;
    case 0x015305:
        SUB_015305();
        break;
    case 0x01530B:
        SUB_01530B();
        break;
    case 0x01535E:
        SUB_01535E();
        break;
    case 0x015371:
        SUB_015371();
        break;
    case 0x0153D6:
        SUB_0153D6();
        break;
    case 0x015473:
        SUB_015473();
        break;
    case 0x0154B2:
        SUB_0154B2();
        break;
    case 0x0154BD:
        SUB_0154BD();
        break;
    case 0x0154E6:
        SUB_0154E6();
        break;
    case 0x015541:
        SUB_015541();
        break;
    case 0x01554D:
        SUB_01554D();
        break;
    case 0x01557B:
        SUB_01557B();
        break;
    case 0x0155C9:
        SUB_0155C9();
        break;
    case 0x0155E2:
        SUB_0155E2();
        break;
    case 0x0155F9:
        SUB_0155F9();
        break;
    case 0x015628:
        SUB_015628();
        break;
    case 0x01563F:
        SUB_01563F();
        break;
    case 0x015656:
        SUB_015656();
        break;
    case 0x01566D:
        SUB_01566D();
        break;
    case 0x01569D:
        SUB_01569D();
        break;
    case 0x0156D1:
        SUB_0156D1();
        break;
    case 0x0156EA:
        SUB_0156EA();
        break;
    case 0x015723:
        SUB_015723();
        break;
    case 0x01573F:
        SUB_01573F();
        break;
    case 0x01576D:
        SUB_01576D();
        break;
    case 0x0157BF:
        SUB_0157BF();
        break;
    case 0x0157DB:
        SUB_0157DB();
        break;
    case 0x015806:
        SUB_015806();
        break;
    case 0x015845:
        SUB_015845();
        break;
    case 0x015893:
        SUB_015893();
        break;
    case 0x0158B3:
        SUB_0158B3();
        break;
    case 0x0158DC:
        SUB_0158DC();
        break;
    case 0x0158F3:
        SUB_0158F3();
        break;
    case 0x015911:
        SUB_015911();
        break;
    case 0x01805D:
        SUB_01805D();
        break;
    case 0x0180E3:
        SUB_0180E3();
        break;
    case 0x0180E7:
        SUB_0180E7();
        break;
    case 0x018161:
        SUB_018161();
        break;
    case 0x018182:
        SUB_018182();
        break;
    case 0x0181BE:
        SUB_0181BE();
        break;
    case 0x0181EF:
        SUB_0181EF();
        break;
    case 0x0181F6:
        SUB_0181F6();
        break;
    case 0x018303:
        SUB_018303();
        break;
    case 0x018425:
        SUB_018425();
        break;
    case 0x01849A:
        SUB_01849A();
        break;
    case 0x0184B9:
        SUB_0184B9();
        break;
    case 0x018567:
        SUB_018567();
        break;
    case 0x018588:
        SUB_018588();
        break;
    case 0x0185CF:
        SUB_0185CF();
        break;
    case 0x0185FB:
        SUB_0185FB();
        break;
    case 0x018664:
        SUB_018664();
        break;
    case 0x018693:
        SUB_018693();
        break;
    case 0x0186EE:
        SUB_0186EE();
        break;
    case 0x018867:
        SUB_018867();
        break;
    case 0x0188C5:
        SUB_0188C5();
        break;
    case 0x0189F5:
        SUB_0189F5();
        break;
    case 0x018A16:
        SUB_018A16();
        break;
    case 0x018AA9:
        SUB_018AA9();
        break;
    case 0x018AED:
        SUB_018AED();
        break;
    case 0x018B3B:
        SUB_018B3B();
        break;
    case 0x018B4B:
        SUB_018B4B();
        break;
    case 0x01934C:
        SUB_01934C();
        break;
    case 0x019359:
        SUB_019359();
        break;
    case 0x019380:
        SUB_019380();
        break;
    case 0x019458:
        SUB_019458();
        break;
    case 0x019482:
        SUB_019482();
        break;
    case 0x019511:
        SUB_019511();
        break;
    case 0x019539:
        SUB_019539();
        break;
    case 0x019586:
        SUB_019586();
        break;
    case 0x01965B:
        SUB_01965B();
        break;
    case 0x0196C1:
        SUB_0196C1();
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
    case 0x0198B7:
        SUB_0198B7();
        break;
    case 0x0198FE:
        SUB_0198FE();
        break;
    case 0x01990B:
        SUB_01990B();
        break;
    case 0x019BBA:
        SUB_019BBA();
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
    case 0x01A1D0:
        SUB_01A1D0();
        break;
    case 0x01A296:
        SUB_01A296();
        break;
    case 0x01A2AF:
        SUB_01A2AF();
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
    case 0x01A4AA:
        SUB_01A4AA();
        break;
    case 0x01A4E0:
        SUB_01A4E0();
        break;
    case 0x01A4F8:
        SUB_01A4F8();
        break;
    case 0x01A505:
        SUB_01A505();
        break;
    case 0x01A55B:
        SUB_01A55B();
        break;
    case 0x01A56A:
        SUB_01A56A();
        break;
    case 0x01A56D:
        SUB_01A56D();
        break;
    case 0x01A63A:
        SUB_01A63A();
        break;
    case 0x01A713:
        SUB_01A713();
        break;
    case 0x01A727:
        SUB_01A727();
        break;
    case 0x01A735:
        SUB_01A735();
        break;
    case 0x01A75E:
        SUB_01A75E();
        break;
    case 0x01A825:
        SUB_01A825();
        break;
    case 0x01AAE2:
        SUB_01AAE2();
        break;
    case 0x01AE8C:
        SUB_01AE8C();
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
    case 0x01C5F5:
        SUB_01C5F5();
        break;
    case 0x01C847:
        SUB_01C847();
        break;
    case 0x01DA72:
        SUB_01DA72();
        break;
    case 0x01DA7B:
        SUB_01DA7B();
        break;
    case 0x01DAA3:
        SUB_01DAA3();
        break;
    case 0x01DAAC:
        SUB_01DAAC();
        break;
    case 0x01DAB5:
        SUB_01DAB5();
        break;
    case 0x01DAE9:
        SUB_01DAE9();
        break;
    case 0x01DBA1:
        SUB_01DBA1();
        break;
    case 0x01DD3D:
        SUB_01DD3D();
        break;
    case 0x01DD6D:
        SUB_01DD6D();
        break;
    case 0x01DD7C:
        SUB_01DD7C();
        break;
    case 0x01DD93:
        SUB_01DD93();
        break;
    case 0x01DDB2:
        SUB_01DDB2();
        break;
    case 0x01DDBA:
        SUB_01DDBA();
        break;
    case 0x01DDD8:
        SUB_01DDD8();
        break;
    case 0x01DE03:
        SUB_01DE03();
        break;
    case 0x01DE12:
        SUB_01DE12();
        break;
    case 0x01DE45:
        SUB_01DE45();
        break;
    case 0x01DE65:
        SUB_01DE65();
        break;
    case 0x01DE9E:
        SUB_01DE9E();
        break;
    case 0x01E097:
        SUB_01E097();
        break;
    case 0x01E16A:
        SUB_01E16A();
        break;
    case 0x01E18D:
        SUB_01E18D();
        break;
    case 0x01E1A3:
        SUB_01E1A3();
        break;
    case 0x01E1A7:
        SUB_01E1A7();
        break;
    case 0x01E1AB:
        SUB_01E1AB();
        break;
    case 0x01E1F3:
        SUB_01E1F3();
        break;
    case 0x01E208:
        SUB_01E208();
        break;
    case 0x01E276:
        SUB_01E276();
        break;
    case 0x01E279:
        SUB_01E279();
        break;
    case 0x01E2CC:
        SUB_01E2CC();
        break;
    case 0x01E314:
        SUB_01E314();
        break;
    case 0x01E31B:
        SUB_01E31B();
        break;
    case 0x01E332:
        SUB_01E332();
        break;
    case 0x01E33F:
        SUB_01E33F();
        break;
    case 0x01E395:
        SUB_01E395();
        break;
    case 0x01E3D6:
        SUB_01E3D6();
        break;
    case 0x01E3D7:
        SUB_01E3D7();
        break;
    case 0x01E9E6:
        SUB_01E9E6();
        break;
    case 0x01EAB1:
        SUB_01EAB1();
        break;
    case 0x01EB36:
        SUB_01EB36();
        break;
    case 0x01EB54:
        SUB_01EB54();
        break;
    case 0x01EB57:
        SUB_01EB57();
        break;
    case 0x01EB5A:
        SUB_01EB5A();
        break;
    case 0x01EB65:
        SUB_01EB65();
        break;
    case 0x01EC60:
        SUB_01EC60();
        break;
    case 0x01EC7A:
        SUB_01EC7A();
        break;
    case 0x01ECF2:
        SUB_01ECF2();
        break;
    case 0x01ED6F:
        SUB_01ED6F();
        break;
    case 0x01EDBB:
        SUB_01EDBB();
        break;
    case 0x01EF92:
        SUB_01EF92();
        break;
    case 0x01EFB8:
        SUB_01EFB8();
        break;
    case 0x01EFCA:
        SUB_01EFCA();
        break;
    case 0x01EFF0:
        SUB_01EFF0();
        break;
    case 0x01F002:
        SUB_01F002();
        break;
    case 0x01F029:
        SUB_01F029();
        break;
    case 0x01F06D:
        SUB_01F06D();
        break;
    case 0x01F073:
        SUB_01F073();
        break;
    case 0x01F07B:
        SUB_01F07B();
        break;
    case 0x01F081:
        SUB_01F081();
        break;
    case 0x01F095:
        SUB_01F095();
        break;
    case 0x01F0B7:
        SUB_01F0B7();
        break;
    case 0x01F0FC:
        SUB_01F0FC();
        break;
    case 0x01F11D:
        SUB_01F11D();
        break;
    case 0x01F13E:
        SUB_01F13E();
        break;
    case 0x01F14E:
        SUB_01F14E();
        break;
    case 0x01F15A:
        SUB_01F15A();
        break;
    case 0x01F16C:
        SUB_01F16C();
        break;
    case 0x01F37D:
        SUB_01F37D();
        break;
    case 0x01F41D:
        SUB_01F41D();
        break;
    case 0x01F4D2:
        SUB_01F4D2();
        break;
    case 0x01F533:
        SUB_01F533();
        break;
    case 0x01F53F:
        SUB_01F53F();
        break;
    case 0x01F54C:
        SUB_01F54C();
        break;
    case 0x01F558:
        SUB_01F558();
        break;
    case 0x01F56E:
        SUB_01F56E();
        break;
    case 0x01F581:
        SUB_01F581();
        break;
    case 0x01F5A7:
        SUB_01F5A7();
        break;
    case 0x01F5B3:
        SUB_01F5B3();
        break;
    case 0x01F5D7:
        SUB_01F5D7();
        break;
    case 0x01FB22:
        SUB_01FB22();
        break;
    default:
		string mapperMode = myMapper->getMapperMode();
        printf("Unhandled jump to address: %04X\n", target);
		exit(1);
    }
}
