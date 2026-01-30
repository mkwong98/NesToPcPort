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
}

void game::atSprite0Hit() {
}

void game::SUB_000018() {
    opPHA();
    a = myMapper->readCPU((0x0028 + x) & 0x00ff);
    myMapper->writeCPU(0x0057, a);
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU((0x0025 + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (!flgC) {
        goto L_000029;
    }
    flgC = true;
    opSBC(0x0A);
    flgC = true;
L_000029:
    myMapper->writeCPU((0x0025 + x) & 0x00ff, a);
    a = 0x00;
    SUB_000037();
    return;
}


void game::SUB_000030() {
    opPHA();
    a = myMapper->readCPU((0x0028 + x) & 0x00ff);
    myMapper->writeCPU(0x0057, a);
    opPLA();
    flgC = false;
    SUB_000037();
    return;
}

void game::SUB_000037() {
    opADC(myMapper->readCPU((0x0026 + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
        flgC = true;
    }
    myMapper->writeCPU((0x0026 + x) & 0x00ff, a);
    a = 0x00;
    goto L_00004F;
L_00004F:
    opADC(myMapper->readCPU((0x0027 + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
        flgC = true;
    }
    myMapper->writeCPU((0x0027 + x) & 0x00ff, a);
    a = 0x00;
    opADC(myMapper->readCPU((0x0028 + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
        flgC = true;
    }
    myMapper->writeCPU((0x0028 + x) & 0x00ff, a);
    a = 0x00;
    opADC(myMapper->readCPU((0x0029 + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
        flgC = true;
    }
    myMapper->writeCPU((0x0029 + x) & 0x00ff, a);
    a = 0x00;
    opADC(myMapper->readCPU((0x002A + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
        flgC = true;
    }
    myMapper->writeCPU((0x002A + x) & 0x00ff, a);
    a = 0x00;
    opADC(myMapper->readCPU((0x002B + x) & 0x00ff));
    if (a >= 0x0A) {
        flgC = true;
        opSBC(0x0A);
        flgC = true;
    }
    myMapper->writeCPU((0x002B + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0028 + x) & 0x00ff);
    if (a == myMapper->readCPU(0x0057)) {
        popAddress();
        return;
    }
    if (a != 0x04) {
        if (a == 0x08) {
            goto L_0000A3;
        }
        popAddress();
        return;
    }
L_0000A3:
    a = myMapper->readCPU((0x0029 + x) & 0x00ff);
    opORA(myMapper->readCPU((0x002A + x) & 0x00ff));
    opORA(myMapper->readCPU((0x002B + x) & 0x00ff));
    if (flgZ) {
        goto L_0000AC;
    }
    popAddress();
    return;
L_0000AC:
    a = x;
    opLSR_A(1);
    x = a;
    SUB_0000E8();
    return;
}

void game::SUB_0000B2() {
    a = myMapper->readCPU((0x003C + x) & 0x00ff);
    opORA(myMapper->readCPU((0x003D + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003E + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003F + x) & 0x00ff));
    if (flgZ) {
        popAddress();
        return;
    }
    opDEC((0x003C + x) & 0x00ff, 1);
    if (!flgN) {
        popAddress();
        return;
    }
    myMapper->writeCPU((0x003C + x) & 0x00ff, 0x09);
    opDEC((0x003D + x) & 0x00ff, 1);
    if (!flgN) {
        popAddress();
        return;
    }
    myMapper->writeCPU((0x003D + x) & 0x00ff, 0x09);
    opDEC((0x003E + x) & 0x00ff, 1);
    if (!flgN) {
        popAddress();
        return;
    }
    myMapper->writeCPU((0x003E + x) & 0x00ff, 0x09);
    opDEC((0x003F + x) & 0x00ff, 1);
    if (flgN) {
        goto L_0000DD;
    }
    popAddress();
    return;
L_0000DD:
    a = 0x00;
    myMapper->writeCPU((0x003C + x) & 0x00ff, a);
    myMapper->writeCPU((0x003D + x) & 0x00ff, a);
    myMapper->writeCPU((0x003E + x) & 0x00ff, a);
    myMapper->writeCPU((0x003F + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_0000E8() {
    if (myMapper->readCPU(0x005B) == 0) {
        SUB_000103();
        return;
    }
    pushAddress(0x0000EC);
    SUB_000103();
    if (poppedEntry.value != 0x0000EC) return;
    pushAddress(0x0000EF);
    SUB_000103();
    if (poppedEntry.value != 0x0000EF) return;
    a = myMapper->readCPU((0x003D + x) & 0x00ff);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU((0x003D + x) & 0x00ff, a);
    if (a >= 0x0A) {
        goto L_0000FE;
    }
    popAddress();
    return;
L_0000FE:
    flgC = true;
    opSBC(0x0A);
    myMapper->writeCPU((0x003D + x) & 0x00ff, a);
    SUB_000103();
    return;
}

void game::SUB_000103() {
    flgC = false;
    a = 0x01;
    opADC(myMapper->readCPU((0x003E + x) & 0x00ff));
    if (a < 0x0A) {
        myMapper->writeCPU((0x003E + x) & 0x00ff, a);
        popAddress();
        return;
    }
    myMapper->writeCPU((0x003E + x) & 0x00ff, 0x00);
    flgC = false;
    a = 0x01;
    opADC(myMapper->readCPU((0x003F + x) & 0x00ff));
    if (a >= 0x0A) {
        goto L_00011F;
    }
    myMapper->writeCPU((0x003F + x) & 0x00ff, a);
    popAddress();
    return;
L_00011F:
    a = 0x09;
    myMapper->writeCPU((0x003C + x) & 0x00ff, a);
    myMapper->writeCPU((0x003D + x) & 0x00ff, a);
    myMapper->writeCPU((0x003E + x) & 0x00ff, a);
    myMapper->writeCPU((0x003F + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_00012A() {
    a = 0x00;
    myMapper->writeCPU(0x0000, a);
    myMapper->writeCPU(0x0001, a);
    do {
        x = myMapper->readCPU(0x0000);
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00013A;
        }
        pushAddress(0x000137);
        SUB_00017C();
        if (poppedEntry.value != 0x000137) return;
    L_00013A:
        a = myMapper->readCPU(0x0000);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0000, a);
    } while (!flgZ);
    x = 0x00;
    y = 0x00;
L_000147:
    if (myMapper->readCPU(0x0300 + x) == 0) {
        goto L_000174;
    }
    myMapper->writeCPU(0x0005, 0x08);
    do {
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x0300 + x));
        opINX(1);
        opINY(1);
        opDEC(0x0005, 1);
    } while (!flgZ);
    while (true) {
        if (x != 0) {
            goto L_000147;
        }
        if (y == 0) {
            goto L_00016A;
        }
        a = 0x00;
        do {
            myMapper->writeCPU(0x0200 + y, a);
            opINY(1);
        } while (!flgZ);
    L_00016A:
        x = 0x00;
        a = x;
        do {
            myMapper->writeCPU(0x0300 + x, a);
            opINX(1);
        } while (!flgZ);
        popAddress();
        return;
    L_000174:
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
    }
    SUB_00017C();
    return;
}

void game::SUB_00017C() {
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0007, myMapper->readCPU(0x818B + x));
    myMapper->writeCPU(0x0008, myMapper->readCPU(0x818C + x));
    indirectJump(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8));
}

void game::SUB_0003AD() {
    myMapper->writeCPU(0x000B, x);
    myMapper->writeCPU(0x000C, y);
    a = myMapper->readCPU(0x0023);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x81C3 + x));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x81C4 + x));
    while (true) {
        do {
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                goto L_0003E4;
            }
            pushAddress(0x0003CE);
            SUB_0003E7();
            if (poppedEntry.value != 0x0003CE) return;
            if (flgZ) {
                goto L_0003D6;
            }
            a = 0x7F;
            setLoadFlag(a);
            popAddress();
            return;
        L_0003D6:
            a = 0x04;
            flgC = false;
            opADC(myMapper->readCPU(0x0009));
            myMapper->writeCPU(0x0009, a);
        } while (!flgC);
        opINC(0x000A, 1);
    }
L_0003E4:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0003E7() {
    a = myMapper->readCPU(0x000B);
    y = 0x00;
    opCMP(a, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
    if (flgC) {
        opINY(2);
        opCMP(a, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
        if (!flgZ) {
            if (flgC) {
                goto L_000409;
            }
        }
        a = myMapper->readCPU(0x000C);
        opDEY(1);
        opCMP(a, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
        if (flgC) {
            opINY(2);
            opCMP(a, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                goto L_000406;
            }
            if (flgC) {
                goto L_000409;
            }
        L_000406:
            a = 0xFF;
            setLoadFlag(a);
            popAddress();
            return;
        }
    }
L_000409:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00040C() {
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0200 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(2);
    x = a;
    a = myMapper->readCPU((0x003C + x) & 0x00ff);
    opORA(myMapper->readCPU((0x003D + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003E + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003F + x) & 0x00ff));
    if (flgZ) {
        myMapper->writeCPU(0x0020, 0x3C);
        x = myMapper->readCPU(0x0000);
        x = myMapper->readCPU(0x0200 + x);
        if (myMapper->readCPU((0x004F + x) & 0x00ff) != 0) {
            opDEC((0x004F + x) & 0x00ff, 1);
        }
        else {
            opDEC((0x004B + x) & 0x00ff, 1);
            pushStatus();
            a = myMapper->readCPU((0x004B + x) & 0x00ff);
            opAND(0x03);
            x = a;
            a = myMapper->readCPU(0x8473 + x);
            x = myMapper->readCPU(0x0000);
            myMapper->writeCPU(0x0205 + x, a);
            pushAddress(0x000444);
            SUB_0065FB();
            if (poppedEntry.value != 0x000444) return;
            popStatus();
            if (flgZ) {
                x = myMapper->readCPU(0x0000);
                myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
                myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + x));
                pushAddress(0x000456);
                SUB_0038F0();
                if (poppedEntry.value != 0x000456) return;
                if (myMapper->readCPU(0x0023) == 0x10) {
                    x = myMapper->readCPU(0x0000);
                    x = myMapper->readCPU(0x0200 + x);
                    if (myMapper->readCPU((0x004D + x) & 0x00ff) != 0) {
                        pushAddress(0x000469);
                        SUB_00659D();
                        if (poppedEntry.value != 0x000469) return;
                    }
                }
                myMapper->writeCPU(0x005B, 0x00);
                SUB_000A4C();
                return;
            }
        }
    }
    a = myMapper->readCPU(0x0023);
    if (a >= 0x0B) {
        if (a >= 0x0D) {
            goto L_000495;
        }
        x = myMapper->readCPU(0x0000);
        if (myMapper->readCPU(0x0202 + x) < 0x25) {
            a = myMapper->readCPU(0x0200 + x);
            flgC = true;
            opSBC(0x01);
            x = a;
            myMapper->writeCPU((0x004A + x) & 0x00ff, 0x1E);
        }
    }
L_000495:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    y = myMapper->readCPU(0x0200 + x);
    opDEY(1);
    a = myMapper->readCPU(0x0205 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0048 + y, a);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0004);
    opAND(0x03);
    if (flgZ) {
        a = myMapper->readCPU(0x0023);
        if (a < 0x07) {
            a = myMapper->readCPU(0x0205 + x);
            opAND(0x0F);
            if (!flgZ) {
                goto L_00050D;
            }
            myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
            a = myMapper->readCPU(0x0204 + x);
            pushAddress(0x0004C4);
            SUB_000962();
            if (poppedEntry.value != 0x0004C4) return;
            myMapper->writeCPU(0x0304 + y, a);
            goto L_000550;
        }
        if (a < 0x0A) {
            a = myMapper->readCPU(0x0205 + x);
            opAND(0x0F);
            if (!flgZ) {
                goto L_00050D;
            }
            myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
            a = myMapper->readCPU(0x0204 + x);
            pushAddress(0x0004E1);
            SUB_000962();
            if (poppedEntry.value != 0x0004E1) return;
            pushAddress(0x0004E4);
            SUB_000962();
            if (poppedEntry.value != 0x0004E4) return;
            pushAddress(0x0004E7);
            SUB_000962();
            if (poppedEntry.value != 0x0004E7) return;
            pushAddress(0x0004EA);
            SUB_000962();
            if (poppedEntry.value != 0x0004EA) return;
            myMapper->writeCPU(0x0304 + y, a);
            goto L_000550;
        }
        if (a < 0x0D) {
            myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
            a = myMapper->readCPU(0x0204 + x);
            pushAddress(0x000500);
            SUB_00099C();
            if (poppedEntry.value != 0x000500) return;
            myMapper->writeCPU(0x0304 + y, a);
            goto L_000550;
        }
        if (a >= 0x10) {
            goto L_00051C;
        }
    }
L_00050D:
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    goto L_000550;
L_00051C:
    if (!(myMapper->readCPU(0x0201 + x) & 0x80)) {
        a = myMapper->readCPU(0x0203 + x);
        pushAddress(0x000524);
        SUB_000962();
        if (poppedEntry.value != 0x000524) return;
        myMapper->writeCPU(0x0303 + y, a);
    }
    else {
        a = myMapper->readCPU(0x0203 + x);
        pushAddress(0x000530);
        SUB_00099C();
        if (poppedEntry.value != 0x000530) return;
        myMapper->writeCPU(0x0303 + y, a);
    }
    if (!(myMapper->readCPU(0x0202 + x) & 0x80)) {
        a = myMapper->readCPU(0x0204 + x);
        pushAddress(0x00053E);
        SUB_000962();
        if (poppedEntry.value != 0x00053E) return;
        myMapper->writeCPU(0x0304 + y, a);
    }
    else {
        a = myMapper->readCPU(0x0204 + x);
        pushAddress(0x00054A);
        SUB_00099C();
        if (poppedEntry.value != 0x00054A) return;
        myMapper->writeCPU(0x0304 + y, a);
    }
L_000550:
    a = myMapper->readCPU(0x0004);
    opAND(0x07);
    if (flgZ) {
        if (myMapper->readCPU(0x0023) >= 0x0D) {
            goto L_000575;
        }
        a = myMapper->readCPU(0x0303 + y);
        setLoadFlag(a);
        if (!flgZ) {
            if (flgN) {
                goto L_00056C;
            }
            pushAddress(0x000563);
            SUB_00099C();
            if (poppedEntry.value != 0x000563) return;
            myMapper->writeCPU(0x0303 + y, a);
            goto L_000575;
        L_00056C:
            pushAddress(0x00056C);
            SUB_000962();
            if (poppedEntry.value != 0x00056C) return;
            myMapper->writeCPU(0x0303 + y, a);
        }
    }
    else {
    }
L_000575:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0206 + x);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = true;
        opSBC(0x01);
    }
    myMapper->writeCPU(0x0306 + y, a);
    a = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU(0x0300 + y, a);
    flgC = true;
    opSBC(0x01);
    pushAddress(0x00058D);
    SUB_0057C1();
    if (poppedEntry.value != 0x00058D) return;
    myMapper->writeCPU(0x000B, a);
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0200 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(2);
    x = a;
    a = myMapper->readCPU((0x003C + x) & 0x00ff);
    opORA(myMapper->readCPU((0x003D + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003E + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003F + x) & 0x00ff));
    if (flgZ) {
        myMapper->writeCPU(0x000B, 0x00);
    }
    a = myMapper->readCPU(0x000B);
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    opAND(0xF0);
    if (flgZ) {
        a = myMapper->readCPU(0x0205 + x);
    }
    else {
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x0205 + x);
        opAND(0x0F);
        opORA(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x0205 + x, a);
    myMapper->writeCPU(0x0305 + y, a);
    myMapper->writeCPU(0x0017, 0x00);
    myMapper->writeCPU(0x0018, 0x08);
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x000B);
    opAND(0x01);
    if (flgZ) {
    }
    else {
        if (myMapper->readCPU(0x0206 + x) == 0) {
            goto L_0005E7;
        }
        goto L_0006B6;
    L_0005E7:
        a = myMapper->readCPU(0x0200 + x);
        flgC = true;
        opSBC(0x01);
        opASL_A(2);
        x = a;
        pushAddress(0x0005F0);
        SUB_0000B2();
        if (poppedEntry.value != 0x0005F0) return;
        x = myMapper->readCPU(0x0000);
        myMapper->writeCPU(0x0306 + y, 0x05);
        myMapper->writeCPU(0x0018, 0x10);
        myMapper->writeCPU(0x0308 + y, 0x03);
        myMapper->writeCPU(0x030C + y, myMapper->readCPU(0x0200 + x));
        myMapper->writeCPU(0x0309 + y, myMapper->readCPU(0x0201 + x));
        myMapper->writeCPU(0x030A + y, myMapper->readCPU(0x0202 + x));
        myMapper->writeCPU(0x030D + y, 0x0B);
        a = myMapper->readCPU(0x0205 + x);
        opAND(0xF0);
        myMapper->writeCPU(0x030B + y, a);
        if (a != 0x80) {
            goto L_000648;
        }
        a = myMapper->readCPU(0x0303 + y);
        pushAddress(0x000629);
        SUB_00093E();
        if (poppedEntry.value != 0x000629) return;
        myMapper->writeCPU(0x0303 + y, a);
        a = myMapper->readCPU(0x0023);
        opCMP(a, 0x0D);
        if (flgC) {
            opCMP(a, 0x10);
            if (!flgC) {
                a = myMapper->readCPU(0x0303 + y);
                opAND(0x78);
                if (flgZ) {
                    myMapper->writeCPU(0x0303 + y, 0x08);
                }
            }
        }
        do {
            do {
                do {
                    goto L_0006B3;
                L_000648:
                    if (a != 0x40) {
                        goto L_00066E;
                    }
                    a = myMapper->readCPU(0x0303 + y);
                    pushAddress(0x00064F);
                    SUB_00097A();
                    if (poppedEntry.value != 0x00064F) return;
                    myMapper->writeCPU(0x0303 + y, a);
                    a = myMapper->readCPU(0x0023);
                    opCMP(a, 0x0D);
                    if (!flgC) {
                        goto L_00066B;
                    }
                    opCMP(a, 0x10);
                    if (flgC) {
                        goto L_00066B;
                    }
                    a = myMapper->readCPU(0x0303 + y);
                    opAND(0x78);
                } while (!flgZ);
                myMapper->writeCPU(0x0303 + y, 0x88);
            L_00066B:
                goto L_0006B3;
            L_00066E:
                if (a != 0x20) {
                    goto L_000694;
                }
                a = myMapper->readCPU(0x0304 + y);
                pushAddress(0x000675);
                SUB_00097A();
                if (poppedEntry.value != 0x000675) return;
                myMapper->writeCPU(0x0304 + y, a);
                a = myMapper->readCPU(0x0023);
                opCMP(a, 0x0D);
                if (!flgC) {
                    goto L_000691;
                }
                opCMP(a, 0x10);
                if (flgC) {
                    goto L_000691;
                }
                a = myMapper->readCPU(0x0304 + y);
                opAND(0x78);
            } while (!flgZ);
            myMapper->writeCPU(0x0304 + y, 0x88);
        L_000691:
            goto L_0006B3;
        L_000694:
            a = myMapper->readCPU(0x0304 + y);
            pushAddress(0x000697);
            SUB_00093E();
            if (poppedEntry.value != 0x000697) return;
            myMapper->writeCPU(0x0304 + y, a);
            a = myMapper->readCPU(0x0023);
            opCMP(a, 0x0D);
            if (!flgC) {
                goto L_0006B3;
            }
            opCMP(a, 0x10);
            if (flgC) {
                goto L_0006B3;
            }
            a = myMapper->readCPU(0x0304 + y);
            opAND(0x78);
        } while (!flgZ);
        myMapper->writeCPU(0x0304 + y, 0x08);
    L_0006B3:
        pushAddress(0x0006B3);
        SUB_0062A3();
        if (poppedEntry.value != 0x0006B3) return;
    }
L_0006B6:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0205 + x);
    opAND(0x0F);
    if (flgZ) {
    }
    else {
        a = 0x00;
        myMapper->writeCPU(0x0303 + y, a);
        myMapper->writeCPU(0x0203 + x, a);
        if (myMapper->readCPU(0x0204 + x) == 0) {
            myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
            myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
            a = myMapper->readCPU(0x000B);
            opAND(0xC0);
            if (flgZ) {
                goto L_00082E;
            }
            pushStatus();
            y = myMapper->readCPU(0x0200 + x);
            opDEY(1);
            a = myMapper->readCPU(0x0046 + y);
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x0046 + y, a);
            opAND(0x01);
            if (!flgZ) {
                popStatus();
                goto L_00082E;
            }
            y = myMapper->readCPU(0x0001);
            setLoadFlag(y);
            popStatus();
            if (!flgN) {
                y = myMapper->readCPU(0x0202 + x);
                x = myMapper->readCPU(0x0201 + x);
                opINX(2);
                pushAddress(0x00070B);
                SUB_0003AD();
                if (poppedEntry.value != 0x00070B) return;
                if (!flgZ) {
                    goto L_00082E;
                }
                x = myMapper->readCPU(0x0000);
                y = myMapper->readCPU(0x0001);
                a = myMapper->readCPU(0x0201 + x);
                flgC = false;
                opADC(0x02);
                myMapper->writeCPU(0x0301 + y, a);
                goto L_00082E;
            }
            y = myMapper->readCPU(0x0202 + x);
            x = myMapper->readCPU(0x0201 + x);
            opDEX(2);
            pushAddress(0x00072C);
            SUB_0003AD();
            if (poppedEntry.value != 0x00072C) return;
            if (!flgZ) {
                goto L_00082E;
            }
            x = myMapper->readCPU(0x0000);
            y = myMapper->readCPU(0x0001);
            a = myMapper->readCPU(0x0201 + x);
            flgC = true;
            opSBC(0x02);
            myMapper->writeCPU(0x0301 + y, a);
            goto L_00082E;
        }
    }
    a = myMapper->readCPU(0x0303 + y);
    pushAddress(0x000747);
    SUB_000918();
    if (poppedEntry.value != 0x000747) return;
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0303 + y);
    setLoadFlag(a);
    pushStatus();
    opAND(0x78);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    popStatus();
    if (!flgN) {
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x0304 + y);
    pushAddress(0x00076E);
    SUB_000918();
    if (poppedEntry.value != 0x00076E) return;
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0304 + y);
    setLoadFlag(a);
    pushStatus();
    opAND(0x78);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0202 + x);
    setLoadFlag(a);
    popStatus();
    if (!flgN) {
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x000E, a);
    a = myMapper->readCPU(0x0023);
    if (a >= 0x0A) {
        if (a >= 0x0D) {
            goto L_0007A8;
        }
        if (a != 0x0B) {
            a = myMapper->readCPU(0x0004);
            opAND(0x01);
            if (!flgZ) {
                opINC(0x000D, 1);
            }
        }
    }
L_0007A8:
    x = myMapper->readCPU(0x000D);
    y = myMapper->readCPU(0x000E);
    pushAddress(0x0007AC);
    SUB_0003AD();
    if (poppedEntry.value != 0x0007AC) return;
    if (!flgZ) {
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0001);
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
        a = myMapper->readCPU(0x0303 + y);
        setLoadFlag(a);
        if (!flgZ) {
            pushStatus();
            opAND(0x7F);
            opLSR_A(2);
            if (flgZ) {
                popStatus();
                a = 0x00;
                setLoadFlag(a);
                if (flgZ) {
                    goto L_0007D7;
                }
            }
            popStatus();
            if (!flgN) {
                opORA(0x80);
            }
        }
    L_0007D7:
        myMapper->writeCPU(0x0303 + y, a);
        a = myMapper->readCPU(0x0304 + y);
        setLoadFlag(a);
        if (!flgZ) {
            pushStatus();
            opAND(0x7F);
            opLSR_A(2);
            if (flgZ) {
                popStatus();
                a = 0x00;
                setLoadFlag(a);
                if (flgZ) {
                    goto L_0007F0;
                }
            }
            popStatus();
            if (!flgN) {
                opORA(0x80);
            }
        }
    L_0007F0:
        myMapper->writeCPU(0x0304 + y, a);
        a = myMapper->readCPU(0x0023);
        if (a >= 0x0D) {
            if (a >= 0x10) {
                goto L_00081F;
            }
            a = myMapper->readCPU(0x0303 + y);
            opAND(0x78);
            if (flgZ) {
                a = myMapper->readCPU(0x0303 + y);
                opAND(0x80);
                opORA(0x08);
                myMapper->writeCPU(0x0303 + y, a);
            }
            a = myMapper->readCPU(0x0304 + y);
            opAND(0x78);
            if (flgZ) {
                a = myMapper->readCPU(0x0304 + y);
                opAND(0x80);
                opORA(0x08);
                myMapper->writeCPU(0x0304 + y, a);
            }
        }
    L_00081F:
        goto L_00082E;
    }
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x000D));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x000E));
L_00082E:
    if (myMapper->readCPU(0x0023) < 0x0D) {
        y = myMapper->readCPU(0x0001);
        x = myMapper->readCPU(0x0301 + y);
        y = myMapper->readCPU(0x0302 + y);
        opINY(1);
        pushAddress(0x00083F);
        SUB_0003AD();
        if (poppedEntry.value != 0x00083F) return;
        if (!flgZ) {
            goto L_000853;
        }
    }
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0205 + x);
    opAND(0xF0);
    myMapper->writeCPU(0x0305 + y, a);
    goto L_00085F;
L_000853:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0205 + x);
    opORA(0x0F);
    myMapper->writeCPU(0x0305 + y, a);
L_00085F:
    y = myMapper->readCPU(0x0001);
    x = myMapper->readCPU(0x0300 + y);
    opDEX(1);
    if (myMapper->readCPU((0x004A + x) & 0x00ff) != 0) {
        opDEC((0x004A + x) & 0x00ff, 1);
        a = x;
        opASL_A(2);
        x = a;
        myMapper->writeCPU(0x0005, x);
        pushAddress(0x000872);
        SUB_0000B2();
        if (poppedEntry.value != 0x000872) return;
        x = myMapper->readCPU(0x0005);
        a = myMapper->readCPU((0x003C + x) & 0x00ff);
        opORA(myMapper->readCPU((0x003D + x) & 0x00ff));
        opORA(myMapper->readCPU((0x003E + x) & 0x00ff));
        opORA(myMapper->readCPU((0x003F + x) & 0x00ff));
        if (!flgZ) {
            y = myMapper->readCPU(0x0001);
            myMapper->writeCPU(0x000D, myMapper->readCPU(0x0301 + y));
            myMapper->writeCPU(0x000E, myMapper->readCPU(0x0302 + y));
            x = myMapper->readCPU(0x0000);
            myMapper->writeCPU(0x0013, myMapper->readCPU(0x0200 + x));
            opDEC(0x0013, 1);
            pushAddress(0x000896);
            SUB_0038AF();
            if (poppedEntry.value != 0x000896) return;
        }
    }
    y = myMapper->readCPU(0x0001);
    x = myMapper->readCPU(0x0300 + y);
    opDEX(1);
    a = myMapper->readCPU((0x0048 + x) & 0x00ff);
    opLSR_A(5);
    if (!flgZ) {
        opLSR_A(1);
        if (flgZ) {
            goto L_0008CB;
        }
        opLSR_A(1);
        if (flgZ) {
            goto L_0008D9;
        }
        if (myMapper->readCPU((0x0044 + x) & 0x00ff) != 0x00) {
            a = 0x07;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0008E5;
            }
        }
        a = 0x06;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0008E5;
        }
    }
    if (myMapper->readCPU((0x0044 + x) & 0x00ff) != 0x00) {
        a = 0x01;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0008E5;
        }
    }
    a = 0x00;
    setLoadFlag(a);
    if (!flgZ) {
    L_0008CB:
        if (myMapper->readCPU((0x0044 + x) & 0x00ff) != 0x02) {
            goto L_0008D5;
        }
        a = 0x02;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0008E5;
        }
    L_0008D5:
        a = 0x03;
        setLoadFlag(a);
        if (flgZ) {
        L_0008D9:
            if (myMapper->readCPU((0x0044 + x) & 0x00ff) != 0x00) {
                goto L_0008E3;
            }
            a = 0x04;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0008E5;
            }
        L_0008E3:
            a = 0x05;
        }
    }
L_0008E5:
    opASL_A(2);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0305 + y);
    opLSR_A(5);
    if (flgZ) {
        a = 0x00;
        setLoadFlag(a);
        if (flgZ) {
            goto L_000907;
        }
    }
    opLSR_A(1);
    if (flgZ) {
        a = 0x01;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_000907;
        }
    }
    opLSR_A(1);
    if (!flgZ) {
        goto L_000905;
    }
    a = 0x02;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000907;
    }
L_000905:
    a = 0x03;
L_000907:
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    y = a;
    myMapper->writeCPU((0x0044 + x) & 0x00ff, myMapper->readCPU(0x89B2 + y));
    a = myMapper->readCPU(0x0001);
    flgC = false;
    opADC(myMapper->readCPU(0x0018));
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_000918() {
    opAND(0x07);
    opPHA();
    a = myMapper->readCPU(0x0004);
    opAND(0x01);
    if (!flgZ) {
        opPLA();
        opLSR_A(2);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0004);
    opAND(0x02);
    if (!flgZ) {
        opPLA();
        opLSR_A(1);
        opAND(0x01);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0004);
    opAND(0x04);
    if (flgZ) {
        goto L_00093A;
    }
    opPLA();
    opAND(0x01);
    popAddress();
    return;
L_00093A:
    opPLA();
    a = 0x00;
    popAddress();
}

void game::SUB_00093E() {
    x = 0x09;
    do {
        do {
            opORA(0x00);
            if (flgN) {
                goto L_000951;
            }
            if (a >= 0x1F) {
                goto L_00094B;
            }
        L_000948:
            flgC = false;
            opADC(0x01);
        L_00094B:
            opDEX(1);
        } while (!flgZ);
        x = myMapper->readCPU(0x0000);
        popAddress();
        return;
    L_000951:
        opAND(0x7F);
        if (flgZ) {
            goto L_000948;
        }
        flgC = true;
        opSBC(0x01);
        if (flgZ) {
            goto L_00094B;
        }
        opORA(0x80);
        opDEX(1);
    } while (!flgZ);
    x = myMapper->readCPU(0x0000);
    popAddress();
}

void game::SUB_000962() {
    opORA(0x00);
    if (flgN) {
        goto L_00096E;
    }
    if (a >= 0x1F) {
        goto L_00096D;
    }
    do {
        flgC = false;
        opADC(0x01);
    L_00096D:
        popAddress();
        return;
    L_00096E:
        opAND(0x7F);
    } while (flgZ);
    flgC = true;
    opSBC(0x01);
    if (flgZ) {
        goto L_00096D;
    }
    opORA(0x80);
    popAddress();
}

void game::SUB_00097A() {
    x = 0x09;
    do {
        do {
            opORA(0x00);
            if (flgN) {
                goto L_00098B;
            }
            if (flgZ) {
                goto L_00098B;
            }
            flgC = true;
            opSBC(0x01);
            opDEX(1);
        } while (!flgZ);
        x = myMapper->readCPU(0x0000);
        popAddress();
        return;
    L_00098B:
        opAND(0x7F);
        if (a >= 0x1F) {
            goto L_000994;
        }
        flgC = false;
        opADC(0x01);
    L_000994:
        opORA(0x80);
        opDEX(1);
    } while (!flgZ);
    x = myMapper->readCPU(0x0000);
    popAddress();
}

void game::SUB_00099C() {
    opORA(0x00);
    if (!flgN) {
        if (flgZ) {
            goto L_0009A6;
        }
        flgC = true;
        opSBC(0x01);
        popAddress();
        return;
    }
L_0009A6:
    opAND(0x7F);
    if (a >= 0x1F) {
        goto L_0009AF;
    }
    flgC = false;
    opADC(0x01);
L_0009AF:
    opORA(0x80);
    popAddress();
}

void game::SUB_0009D2() {
    x = myMapper->readCPU(0x0000);
    opDEC(0x0205 + x, 1);
    if (flgZ) {
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0202 + x);
    x = myMapper->readCPU(0x0201 + x);
    pushAddress(0x0009E3);
    SUB_0003AD();
    if (poppedEntry.value != 0x0009E3) return;
    if (!flgZ) {
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    a = myMapper->readCPU(0x0203 + x);
    myMapper->writeCPU(0x0303 + y, a);
    opPHA();
    opAND(0xC0);
    if (flgZ) {
        opPLA();
        opAND(0x20);
        if (!flgZ) {
            a = myMapper->readCPU(0x0202 + x);
            flgC = false;
            opADC(0x07);
        }
        else {
            a = myMapper->readCPU(0x0202 + x);
            flgC = true;
            opSBC(0x07);
        }
        myMapper->writeCPU(0x0302 + y, a);
    }
    else {
        opPLA();
        if (!flgN) {
            goto L_000A3E;
        }
        a = myMapper->readCPU(0x0201 + x);
        flgC = true;
        opSBC(0x07);
        if (!flgC) {
            SUB_000A4C();
            return;
        }
        goto L_000A46;
    L_000A3E:
        a = myMapper->readCPU(0x0201 + x);
        flgC = false;
        opADC(0x07);
        if (flgC) {
            SUB_000A4C();
            return;
        }
    L_000A46:
        myMapper->writeCPU(0x0301 + y, a);
    }
    SUB_000A69();
    return;
}

void game::SUB_000A4C() {
    y = myMapper->readCPU(0x0001);
    a = 0x00;
    myMapper->writeCPU(0x0300 + y, a);
    myMapper->writeCPU(0x0301 + y, a);
    myMapper->writeCPU(0x0302 + y, a);
    myMapper->writeCPU(0x0303 + y, a);
    myMapper->writeCPU(0x0304 + y, a);
    myMapper->writeCPU(0x0305 + y, a);
    myMapper->writeCPU(0x0306 + y, a);
    myMapper->writeCPU(0x0307 + y, a);
    popAddress();
}

void game::SUB_000A69() {
    a = myMapper->readCPU(0x0001);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_000A71() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    flgC = false;
    opADC(0x01);
    opCMP(a, 0x51);
    if (flgZ) {
        a = 0x00;
    }
    myMapper->writeCPU(0x0303 + y, a);
    x = a;
    a = myMapper->readCPU(0x0004);
    opAND(0x01);
    pushStatus();
    a = myMapper->readCPU(0x8AB6 + x);
    setLoadFlag(a);
    popStatus();
    if (flgZ) {
        pushAddress(0x000AA0);
        SUB_001A0C();
        if (poppedEntry.value != 0x000AA0) return;
    }
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x000F));
    a = myMapper->readCPU(0x0010);
    if (a < 0xF3) {
        goto L_000AB0;
    }
    a = 0x0C;
L_000AB0:
    myMapper->writeCPU(0x0302 + y, a);
    SUB_000A69();
    return;
}

void game::SUB_000B07() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x02F9 + y));
    a = myMapper->readCPU(0x02FA + y);
    flgC = false;
    opADC(0x0C);
    myMapper->writeCPU(0x0302 + y, a);
    SUB_000A69();
    return;
}

void game::SUB_000B23() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0304 + y, a);
    if (!flgZ) {
        if (flgN) {
            goto L_000B5B;
        }
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x02F9 + y));
        a = myMapper->readCPU(0x02FA + y);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0302 + y, a);
        SUB_000A69();
        return;
    L_000B5B:
        a = myMapper->readCPU(0x0201 + x);
        myMapper->writeCPU(0x0301 + y, a);
        opPHA();
        a = myMapper->readCPU(0x0004);
        opLSR_A(1);
        a = myMapper->readCPU(0x0202 + x);
        opADC(0x01);
        myMapper->writeCPU(0x0302 + y, a);
        y = a;
        opPLA();
        x = a;
        pushAddress(0x000B70);
        SUB_0003AD();
        if (poppedEntry.value != 0x000B70) return;
        if (flgZ) {
            goto L_000B8C;
        }
        y = myMapper->readCPU(0x0001);
        myMapper->writeCPU(0x000D, myMapper->readCPU(0x0301 + y));
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0302 + y));
        pushAddress(0x000B81);
        SUB_0038F0();
        if (poppedEntry.value != 0x000B81) return;
        opDEC(0x001F, 1);
        pushAddress(0x000B86);
        SUB_006996();
        if (poppedEntry.value != 0x000B86) return;
        SUB_000A4C();
        return;
    }
L_000B8C:
    SUB_000A69();
    return;
}

void game::SUB_000B8F() {
    x = myMapper->readCPU(0x0000);
    if (myMapper->readCPU(0x0207 + x) != 0) {
        goto L_000B99;
    }
    pushAddress(0x000B96);
    SUB_0064F5();
    if (poppedEntry.value != 0x000B96) return;
L_000B99:
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0307 + y, 0xFF);
    SUB_000BA0();
    return;
}

void game::SUB_000BA0() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0303 + y, a);
    if (flgN) {
        a = myMapper->readCPU(0x0201 + x);
        flgC = true;
        opSBC(0x02);
        if (!flgC) {
            goto L_000BE6;
        }
        if (flgC) {
            goto L_000BD6;
        }
    }
    a = myMapper->readCPU(0x0201 + x);
    flgC = false;
    opADC(0x02);
    if (!flgC) {
    L_000BD6:
        myMapper->writeCPU(0x0301 + y, a);
        x = a;
        y = myMapper->readCPU(0x0302 + y);
        pushAddress(0x000BDE);
        SUB_0003AD();
        if (poppedEntry.value != 0x000BDE) return;
        if (!flgZ) {
            goto L_000BE6;
        }
        SUB_000A69();
        return;
    }
L_000BE6:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0004);
    opADC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0500 + y, a);
    myMapper->writeCPU(0x0501 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0502 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0503 + y, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    opEOR(0x80);
    myMapper->writeCPU(0x0504 + y, a);
    myMapper->writeCPU(0x0505 + y, 0x05);
    a = y;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    SUB_000A4C();
    return;
}

void game::SUB_000C19() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    if (myMapper->readCPU(0x0204 + x) != 0) {
        if (myMapper->readCPU(0x0004) != 0) {
            goto L_000C30;
        }
        opDEC(0x0204 + x, 1);
        if (flgZ) {
            myMapper->writeCPU(0x0202 + x, 0x67);
        }
    L_000C30:
        myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
        myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
        myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
        SUB_000A69();
        return;
    }
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0303 + y, a);
    pushStatus();
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0301 + y, a);
    popStatus();
    if (!flgN) {
        goto L_000C76;
    }
    opDEC(0x0201 + x, 2);
    goto L_000C7C;
L_000C76:
    opINC(0x0201 + x, 2);
L_000C7C:
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    SUB_000A69();
    return;
}

void game::SUB_000C85() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    SUB_000A69();
    return;
}

void game::SUB_000C9E() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0306 + y, myMapper->readCPU(0x0206 + x));
    myMapper->writeCPU(0x0307 + y, myMapper->readCPU(0x0207 + x));
    SUB_000A69();
    return;
}

void game::SUB_000CD5() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    a = myMapper->readCPU(0x0004);
    opAND(0x07);
    pushStatus();
    a = 0x00;
    setLoadFlag(a);
    popStatus();
    if (flgZ) {
        a = 0x01;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0203 + x));
    if (a != 0x0C) {
        goto L_000CF5;
    }
    a = 0x00;
L_000CF5:
    myMapper->writeCPU(0x0303 + y, a);
    x = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x8D20 + x));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x8D2C + x));
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0204 + x);
    myMapper->writeCPU(0x0304 + y, a);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0301 + y, a);
    a = myMapper->readCPU(0x0205 + x);
    myMapper->writeCPU(0x0305 + y, a);
    flgC = false;
    opADC(myMapper->readCPU(0x0006));
    myMapper->writeCPU(0x0302 + y, a);
    SUB_000A69();
    return;
}

void game::SUB_000D38() {
    pushAddress(0x000D38);
    SUB_00649C();
    if (poppedEntry.value != 0x000D38) return;
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0306 + y, myMapper->readCPU(0x0206 + x));
    a = myMapper->readCPU(0x0004);
    opAND(0x1F);
    if (flgZ) {
        opCMP(myMapper->readCPU(0x0023), 0x06);
        if (flgZ) {
            y = myMapper->readCPU(0x0002);
            myMapper->writeCPU(0x0500 + y, 0x03);
            myMapper->writeCPU(0x0501 + y, 0x0B);
            myMapper->writeCPU(0x0502 + y, myMapper->readCPU(0x0201 + x));
            myMapper->writeCPU(0x0503 + y, myMapper->readCPU(0x0202 + x));
            myMapper->writeCPU(0x0505 + y, myMapper->readCPU(0x0203 + x));
            myMapper->writeCPU(0x0506 + y, 0x0C);
            a = myMapper->readCPU(0x0004);
            opLSR_A(5);
            opAND(0x01);
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x0504 + y, a);
            a = y;
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x0002, a);
            y = myMapper->readCPU(0x0001);
        }
    }
    if (myMapper->readCPU(0x0206 + x) == 0) {
        a = myMapper->readCPU(0x0201 + x);
        opAND(0xE0);
        if (!flgZ) {
            opEOR(0xE0);
            if (!flgZ) {
                a = myMapper->readCPU(0x0205 + x);
                flgC = true;
                opSBC(0x01);
                if (!flgZ) {
                    myMapper->writeCPU(0x0305 + y, a);
                    SUB_000A69();
                    return;
                }
                myMapper->writeCPU(0x0306 + y, 0xFF);
                a = myMapper->readCPU(0x0004);
                opLSR_A(1);
                opORA(0x40);
                myMapper->writeCPU(0x0305 + y, a);
                SUB_000A69();
                return;
            }
        }
    }
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    pushStatus();
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    popStatus();
    if (flgN) {
        flgC = true;
        opSBC(0x02);
    }
    else {
        flgC = false;
        opADC(0x02);
    }
    myMapper->writeCPU(0x0301 + y, a);
    a = myMapper->readCPU(0x0205 + x);
    flgC = true;
    opSBC(0x01);
    if (flgZ) {
        goto L_000DFB;
    }
    myMapper->writeCPU(0x0305 + y, a);
    SUB_000A69();
    return;
L_000DFB:
    a = myMapper->readCPU(0x0004);
    opLSR_A(3);
    opORA(myMapper->readCPU(0x0020));
    myMapper->writeCPU(0x0305 + y, a);
    myMapper->writeCPU(0x0306 + y, 0x00);
    SUB_000A69();
    return;
}

void game::SUB_000E0D() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    if (myMapper->readCPU(0x0202 + x) < 0x30) {
        myMapper->writeCPU(0x0202 + x, 0x30);
    }
    else {
        if (myMapper->readCPU(0x0202 + x) < 0xC0) {
            goto L_000E2C;
        }
        myMapper->writeCPU(0x0202 + x, 0xC0);
    }
L_000E2C:
    if (myMapper->readCPU(0x0207 + x) == 0) {
        myMapper->writeCPU(0x0207 + x, 0xFF);
        pushAddress(0x000E36);
        SUB_006522();
        if (poppedEntry.value != 0x000E36) return;
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0001);
    }
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0307 + y, myMapper->readCPU(0x0207 + x));
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    flgC = false;
    opPHA();
    opADC(0x01);
    if (a != 0x85) {
        goto L_000E60;
    }
    a = 0x00;
L_000E60:
    myMapper->writeCPU(0x0303 + y, a);
    a = 0x01;
    pushAddress(0x000E65);
    SUB_001A47();
    if (poppedEntry.value != 0x000E65) return;
    opPLA();
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
    pushAddress(0x000E6C);
    SUB_001A0C();
    if (poppedEntry.value != 0x000E6C) return;
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0010));
    SUB_000A69();
    return;
}

void game::SUB_000E7E() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    if (myMapper->readCPU(0x0202 + x) < 0x30) {
        myMapper->writeCPU(0x0202 + x, 0x30);
    }
    else {
        if (myMapper->readCPU(0x0202 + x) < 0xC0) {
            goto L_000E9D;
        }
        myMapper->writeCPU(0x0202 + x, 0xC0);
    }
L_000E9D:
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0304 + y, a);
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
        myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
        a = myMapper->readCPU(0x0205 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0305 + y, a);
        if (flgZ) {
            a = myMapper->readCPU(0x0004);
            opLSR_A(1);
            a = myMapper->readCPU(0x0202 + x);
            opSBC(0x01);
            myMapper->writeCPU(0x0302 + y, a);
            SUB_000A69();
            return;
        }
        if (a == 0x01) {
            a = myMapper->readCPU(0x0004);
            opLSR_A(1);
            a = myMapper->readCPU(0x0202 + x);
            opADC(0x01);
            myMapper->writeCPU(0x0302 + y, a);
            SUB_000A69();
            return;
        }
        if (a == 0x02) {
            a = myMapper->readCPU(0x0201 + x);
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x0301 + y, a);
            SUB_000A69();
            return;
        }
        a = myMapper->readCPU(0x0201 + x);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0301 + y, a);
        SUB_000A69();
        return;
    }
    myMapper->writeCPU(0x0304 + y, 0x00);
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    flgC = false;
    opPHA();
    opADC(0x01);
    if (a != 0x09) {
        goto L_000F20;
    }
    a = 0x00;
L_000F20:
    myMapper->writeCPU(0x0303 + y, a);
    a = 0x02;
    pushAddress(0x000F25);
    SUB_001A47();
    if (poppedEntry.value != 0x000F25) return;
    opPLA();
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
    pushAddress(0x000F2C);
    SUB_001A0C();
    if (poppedEntry.value != 0x000F2C) return;
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0010));
    SUB_000A69();
    return;
}

void game::SUB_000F3E() {
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0203 + x);
    y = 0x00;
    do {
        if (a == myMapper->readCPU(0x0200 + y)) {
            goto L_000F58;
        }
        opINY(8);
    } while (!flgZ);
    pushAddress(0x000F54);
    SUB_006956();
    if (poppedEntry.value != 0x000F54) return;
    popAddress();
    return;
L_000F58:
    myMapper->writeCPU(0x000C, myMapper->readCPU(0x0202 + y));
    a = myMapper->readCPU(0x0207 + x);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x000F62);
        SUB_00646B();
        if (poppedEntry.value != 0x000F62) return;
        a = 0xFF;
    }
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0307 + y, a);
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0304 + y, a);
    if (!flgN) {
        a = myMapper->readCPU(0x0201 + x);
        flgC = false;
        opADC(0x02);
        if (flgC) {
            SUB_000A4C();
            return;
        }
        myMapper->writeCPU(0x0301 + y, a);
    }
    else {
        a = myMapper->readCPU(0x0201 + x);
        flgC = true;
        opSBC(0x02);
        if (!flgC) {
            SUB_000A4C();
            return;
        }
        myMapper->writeCPU(0x0301 + y, a);
    }
    a = myMapper->readCPU(0x0205 + x);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0305 + y, a);
        a = myMapper->readCPU(0x0302 + y);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0302 + y, a);
        if (!(myMapper->readCPU(0x0204 + x) & 0x80)) {
            a = myMapper->readCPU(0x0201 + x);
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x0301 + y, a);
            SUB_000A69();
            return;
        }
        a = myMapper->readCPU(0x0201 + x);
        flgC = true;
        opSBC(0x03);
        myMapper->writeCPU(0x0301 + y, a);
        SUB_000A69();
        return;
    }
    myMapper->writeCPU(0x0305 + y, a);
    if (myMapper->readCPU(0x000C) >= myMapper->readCPU(0x0202 + x)) {
        a = myMapper->readCPU(0x0302 + y);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0302 + y, a);
    }
    else {
        a = myMapper->readCPU(0x0302 + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0302 + y, a);
    }
    if (!(myMapper->readCPU(0x0304 + y) & 0x80)) {
        a = myMapper->readCPU(0x0301 + y);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x0301 + y, a);
        if (flgC) {
            goto L_001019;
        }
        if (!flgC) {
            goto L_001016;
        }
    }
    a = myMapper->readCPU(0x0301 + y);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0301 + y, a);
    if (!flgC) {
        goto L_001019;
    }
L_001016:
    SUB_000A69();
    return;
L_001019:
    pushAddress(0x001019);
    SUB_006956();
    if (poppedEntry.value != 0x001019) return;
    SUB_000A4C();
    return;
}

void game::SUB_00101F() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0307 + y, myMapper->readCPU(0x0207 + x));
    a = myMapper->readCPU(0x0206 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0306 + y, a);
    if (!flgZ) {
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0306 + y, a);
        pushAddress(0x00105B);
        SUB_00661F();
        if (poppedEntry.value != 0x00105B) return;
        SUB_000A69();
        return;
    }
    a = myMapper->readCPU(0x0203 + x);
    x = 0x00;
    do {
        if (a == myMapper->readCPU(0x0200 + x)) {
            goto L_00107F;
        }
        opINX(8);
    } while (!flgZ);
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0203 + x);
    opEOR(0x03);
    myMapper->writeCPU(0x0303 + y, a);
L_00107F:
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x0202 + x));
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0204 + x);
    opAND(0x02);
    if (!flgZ) {
        if (myMapper->readCPU(0x0204 + x) & 0x80) {
            goto L_0010EB;
        }
        if (myMapper->readCPU(0x0005) < myMapper->readCPU(0x0201 + x)) {
            goto L_0010B9;
        }
        a = myMapper->readCPU(0x0201 + x);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0301 + y, a);
        while (true) {
            a = myMapper->readCPU(0x0207 + x);
            flgC = false;
            opADC(0x01);
            if (a >= 0x14) {
                a = 0x00;
            }
            myMapper->writeCPU(0x0307 + y, a);
            SUB_000A69();
            return;
        L_0010B9:
            a = myMapper->readCPU(0x0204 + x);
            opAND(0xFD);
            myMapper->writeCPU(0x0304 + y, a);
            if (myMapper->readCPU(0x0203 + x) != 0x02) {
                goto L_0010D0;
            }
            myMapper->writeCPU(0x0303 + y, 0x01);
            SUB_000A69();
            return;
        L_0010D0:
            x = 0x00;
            a = 0x02;
            do {
                if (a == myMapper->readCPU(0x0200 + x)) {
                    goto L_0010E5;
                }
                opINX(8);
            } while (!flgZ);
            a = 0x01;
        L_0010E5:
            myMapper->writeCPU(0x0303 + y, a);
            SUB_000A69();
            return;
        L_0010EB:
            if (myMapper->readCPU(0x0201 + x) < myMapper->readCPU(0x0005)) {
                goto L_0010B9;
            }
            a = myMapper->readCPU(0x0201 + x);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU(0x0301 + y, a);
        }
    }
    myMapper->writeCPU(0x0007, 0x00);
    a = myMapper->readCPU(0x0005);
    flgC = true;
    opSBC(myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0005, a);
    if (!flgC) {
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0005, a);
        myMapper->writeCPU(0x0007, 0x80);
    }
    a = myMapper->readCPU(0x0202 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0006));
    if (!flgC) {
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
    }
    myMapper->writeCPU(0x0006, a);
    opCMP(a, 0x09);
    if (!flgC) {
        opCMP(a, myMapper->readCPU(0x0005));
        if (!flgC) {
            a = myMapper->readCPU(0x0204 + x);
            opORA(0x02);
            opAND(0x7F);
            opORA(myMapper->readCPU(0x0007));
            myMapper->writeCPU(0x0304 + y, a);
            SUB_000A69();
            return;
        }
    }
    a = myMapper->readCPU(0x0204 + x);
    opAND(0x01);
    if (flgZ) {
        a = myMapper->readCPU(0x0205 + x);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0305 + y, a);
        if (!flgZ) {
            SUB_000A69();
            return;
        }
        a = myMapper->readCPU(0x0204 + x);
        opEOR(0x80);
        opORA(0x01);
        myMapper->writeCPU(0x0304 + y, a);
        a = myMapper->readCPU(0x0004);
        opLSR_A(2);
        flgC = false;
        opADC(0x0A);
        myMapper->writeCPU(0x0305 + y, a);
        SUB_000A69();
        return;
    }
    a = myMapper->readCPU(0x0004);
    opAND(0x03);
    pushStatus();
    a = 0x00;
    setLoadFlag(a);
    popStatus();
    if (flgZ) {
        a = 0x01;
    }
    myMapper->writeCPU(0x0008, a);
    if (!(myMapper->readCPU(0x0204 + x) & 0x80)) {
        a = myMapper->readCPU(0x0201 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0008));
        myMapper->writeCPU(0x0301 + y, a);
    }
    else {
        a = myMapper->readCPU(0x0201 + x);
        flgC = true;
        opSBC(myMapper->readCPU(0x0008));
        myMapper->writeCPU(0x0301 + y, a);
    }
    a = myMapper->readCPU(0x0205 + x);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0305 + y, a);
    if (flgZ) {
        goto L_00119F;
    }
    SUB_000A69();
    return;
L_00119F:
    a = myMapper->readCPU(0x0204 + x);
    opAND(0xFE);
    myMapper->writeCPU(0x0304 + y, a);
    a = myMapper->readCPU(0x0004);
    opLSR_A(1);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x0305 + y, a);
    SUB_000A69();
    return;
}

void game::SUB_0011B3() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0307 + y, myMapper->readCPU(0x0207 + x));
    a = myMapper->readCPU(0x0206 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0306 + y, a);
    if (flgZ) {
    }
    else {
        pushAddress(0x0011EC);
        SUB_0063DA();
        if (poppedEntry.value != 0x0011EC) return;
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0001);
        a = myMapper->readCPU(0x0304 + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0304 + y, a);
        if (!flgZ) {
            SUB_000A69();
            return;
        }
        pushAddress(0x001201);
        SUB_00694D();
        if (poppedEntry.value != 0x001201) return;
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0001);
        if (!(myMapper->readCPU(0x0206 + x) & 0x80)) {
            a = 0x00;
            myMapper->writeCPU(0x0304 + y, a);
            myMapper->writeCPU(0x0306 + y, a);
            SUB_000A69();
            return;
        }
        myMapper->writeCPU(0x0308 + y, myMapper->readCPU(0x0205 + x));
        myMapper->writeCPU(0x0309 + y, myMapper->readCPU(0x0201 + x));
        a = myMapper->readCPU(0x0202 + x);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x030A + y, a);
        a = 0x00;
        myMapper->writeCPU(0x030B + y, a);
        myMapper->writeCPU(0x030C + y, a);
        myMapper->writeCPU(0x030D + y, a);
        myMapper->writeCPU(0x030E + y, a);
        myMapper->writeCPU(0x030F + y, a);
        myMapper->writeCPU(0x0304 + y, 0x30);
        a = 0x00;
        myMapper->writeCPU(0x0305 + y, a);
        myMapper->writeCPU(0x0306 + y, a);
        myMapper->writeCPU(0x0307 + y, a);
        pushAddress(0x00124E);
        SUB_000A69();
        if (poppedEntry.value != 0x00124E) return;
        SUB_000A69();
        return;
    }
    a = myMapper->readCPU(0x0301 + y);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0301 + y, a);
    if (myMapper->readCPU(0x0203 + x) != 0) {
        a = myMapper->readCPU(0x0301 + y);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x0301 + y, a);
    }
    pushAddress(0x00126B);
    SUB_00145B();
    if (poppedEntry.value != 0x00126B) return;
    if (!flgZ) {
        a = myMapper->readCPU(0x0203 + x);
        opAND(0x01);
        opEOR(0x01);
        myMapper->writeCPU(0x0303 + y, a);
    }
    else {
        pushAddress(0x00127D);
        SUB_00143C();
        if (poppedEntry.value != 0x00127D) return;
        if (flgZ) {
        }
        else {
            a = myMapper->readCPU(0x003C);
            opEOR(myMapper->readCPU(0x003D));
            opEOR(myMapper->readCPU(0x0040));
            opEOR(myMapper->readCPU(0x0041));
            opEOR(myMapper->readCPU(0x0004));
            opAND(0x07);
            myMapper->writeCPU(0x0005, a);
            a = myMapper->readCPU(0x0023);
            flgC = true;
            opSBC(0x07);
            opASL_A(3);
            flgC = false;
            opADC(myMapper->readCPU(0x0005));
            myMapper->writeCPU(0x0005, a);
            x = a;
            y = myMapper->readCPU(0x0002);
            myMapper->writeCPU(0x0502 + y, myMapper->readCPU(0x950A + x));
            myMapper->writeCPU(0x0503 + y, myMapper->readCPU(0x9522 + x));
            x = myMapper->readCPU(0x0000);
            myMapper->writeCPU(0x0501 + y, myMapper->readCPU(0x0200 + x));
            myMapper->writeCPU(0x0500 + y, 0x1E);
            a = myMapper->readCPU(0x0203 + x);
            opAND(0x01);
            opEOR(0x01);
            myMapper->writeCPU(0x0504 + y, a);
            myMapper->writeCPU(0x0505 + y, myMapper->readCPU(0x0204 + x));
            a = myMapper->readCPU(0x0205 + x);
            if (a != 0x0F) {
                myMapper->writeCPU(0x0506 + y, a);
                myMapper->writeCPU(0x0507 + y, 0x00);
                a = y;
                flgC = false;
                opADC(0x08);
                myMapper->writeCPU(0x0002, a);
            }
            else {
                a = 0x00;
                myMapper->writeCPU(0x0506 + y, a);
                myMapper->writeCPU(0x0507 + y, a);
                a = y;
                flgC = false;
                opADC(0x08);
                y = a;
                a = myMapper->readCPU(0x0004);
                opAND(0x07);
                opEOR(myMapper->readCPU(0x0005));
                x = a;
                myMapper->writeCPU(0x0502 + y, myMapper->readCPU(0x950A + x));
                myMapper->writeCPU(0x0503 + y, myMapper->readCPU(0x9522 + x));
                x = myMapper->readCPU(0x0000);
                myMapper->writeCPU(0x0501 + y, myMapper->readCPU(0x0200 + x));
                myMapper->writeCPU(0x0500 + y, 0x32);
                a = myMapper->readCPU(0x0203 + x);
                opAND(0x01);
                opEOR(0x01);
                myMapper->writeCPU(0x0504 + y, a);
                myMapper->writeCPU(0x0505 + y, myMapper->readCPU(0x0204 + x));
                a = 0x00;
                myMapper->writeCPU(0x0506 + y, a);
                myMapper->writeCPU(0x0507 + y, a);
                a = y;
                flgC = false;
                opADC(0x08);
                myMapper->writeCPU(0x0002, a);
            }
            SUB_000A4C();
            return;
        }
    }
    if (myMapper->readCPU(0x0205 + x) == 0) {
        if (myMapper->readCPU(0x0204 + x) == 0) {
            goto L_001347;
        }
        a = myMapper->readCPU(0x0304 + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0304 + y, a);
        if (!flgZ) {
            goto L_001368;
        }
    }
L_001347:
    a = myMapper->readCPU(0x0205 + x);
    setLoadFlag(a);
    if (!flgZ) {
        if (a != 0x04) {
            goto L_001368;
        }
        if (myMapper->readCPU(0x0004) == 0xB1) {
            a = myMapper->readCPU(0x003C);
            opEOR(myMapper->readCPU(0x0040));
            opAND(0x01);
            if (!flgZ) {
                myMapper->writeCPU(0x0304 + y, 0x0A);
                myMapper->writeCPU(0x0306 + y, 0xFF);
            }
        }
    L_001368:
        SUB_000A69();
        return;
    }
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + x));
    pushAddress(0x001375);
    SUB_00139D();
    if (poppedEntry.value != 0x001375) return;
    if (!flgZ) {
        goto L_00137D;
    }
    SUB_000A69();
    return;
L_00137D:
    myMapper->writeCPU(0x0305 + y, a);
    myMapper->writeCPU(0x0304 + y, 0x0C);
    myMapper->writeCPU(0x0306 + y, 0x7F);
    SUB_000A69();
    return;
}

void game::SUB_00138D() {
    a = myMapper->readCPU(0x000F);
    flgC = true;
    opSBC(myMapper->readCPU(0x0010));
    if (flgC) {
        goto L_001399;
    }
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
L_001399:
    flgC = true;
    opSBC(0x05);
    popAddress();
}

void game::SUB_00139D() {
    x = 0x00;
    while (true) {
        a = myMapper->readCPU(0x0200 + x);
        if (a != 0x04) {
            if (a == 0x0F) {
                goto L_0013AD;
            }
            goto L_001431;
        }
    L_0013AD:
        myMapper->writeCPU(0x000F, myMapper->readCPU(0x0201 + x));
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x000D));
        pushAddress(0x0013B6);
        SUB_00138D();
        if (poppedEntry.value != 0x0013B6) return;
        if (!flgC) {
            myMapper->writeCPU(0x000F, myMapper->readCPU(0x0202 + x));
            myMapper->writeCPU(0x0010, myMapper->readCPU(0x000E));
            pushAddress(0x0013C4);
            SUB_00138D();
            if (poppedEntry.value != 0x0013C4) return;
            if (flgC) {
                goto L_001431;
            }
            a = myMapper->readCPU(0x0200 + x);
            opPHA();
            myMapper->writeCPU(0x0005, myMapper->readCPU(0x0201 + x));
            myMapper->writeCPU(0x0006, myMapper->readCPU(0x0202 + x));
            a = 0x00;
            myMapper->writeCPU(0x0200 + x, a);
            myMapper->writeCPU(0x0201 + x, a);
            myMapper->writeCPU(0x0202 + x, a);
            myMapper->writeCPU(0x0203 + x, a);
            myMapper->writeCPU(0x0204 + x, a);
            myMapper->writeCPU(0x0205 + x, a);
            myMapper->writeCPU(0x0206 + x, a);
            myMapper->writeCPU(0x0207 + x, a);
            x = 0x00;
            do {
                a = myMapper->readCPU(0x0300 + x);
                if (a != 0x04) {
                    if (a != 0x0F) {
                        goto L_001428;
                    }
                }
                if (myMapper->readCPU(0x0301 + x) == myMapper->readCPU(0x0005)) {
                    if (myMapper->readCPU(0x0302 + x) != myMapper->readCPU(0x0006)) {
                        goto L_001428;
                    }
                    a = 0x00;
                    myMapper->writeCPU(0x0300 + x, a);
                    myMapper->writeCPU(0x0301 + x, a);
                    myMapper->writeCPU(0x0302 + x, a);
                    myMapper->writeCPU(0x0303 + x, a);
                    myMapper->writeCPU(0x0304 + x, a);
                    myMapper->writeCPU(0x0305 + x, a);
                    myMapper->writeCPU(0x0306 + x, a);
                    myMapper->writeCPU(0x0307 + x, a);
                    opPLA();
                    popAddress();
                    return;
                }
            L_001428:
                a = x;
                flgC = false;
                opADC(0x08);
                x = a;
                setLoadFlag(x);
            } while (!flgZ);
            opPLA();
            popAddress();
            return;
        }
    L_001431:
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        setLoadFlag(x);
        if (flgZ) {
            goto L_00143B;
        }
    }
L_00143B:
    popAddress();
}

void game::SUB_00143C() {
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x0301 + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x0302 + y));
    a = myMapper->readCPU(0x0023);
    flgC = true;
    opSBC(0x07);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x949E + x));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x949F + x));
    y = 0x00;
    setLoadFlag(y);
    if (flgZ) {
        SUB_001478();
        return;
    }
    SUB_00145B();
    return;
}

void game::SUB_00145B() {
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x0301 + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x0302 + y));
    a = myMapper->readCPU(0x0023);
    flgC = true;
    opSBC(0x07);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x94C6 + x));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x94C7 + x));
    y = 0x00;
    SUB_001478();
    return;
}

void game::SUB_001478() {
    while (true) {
        do {
            opINY(1);
            if (myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y) == 0) {
                goto L_001497;
            }
            opDEY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            if (a != myMapper->readCPU(0x0005)) {
                goto L_001493;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y);
            opINY(1);
        } while (a != myMapper->readCPU(0x0006));
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0001);
        a = 0xFF;
        setLoadFlag(a);
        popAddress();
        return;
    L_001493:
        opINY(1);
    }
L_001497:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00153A() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    a = myMapper->readCPU(0x0023);
    if (a >= 0x0A) {
        if (a >= 0x0D) {
            goto L_001563;
        }
        if (a != 0x0B) {
            a = myMapper->readCPU(0x0004);
            opLSR_A(1);
            a = 0x00;
            opADC(myMapper->readCPU(0x0201 + x));
            myMapper->writeCPU(0x0301 + y, a);
        }
    }
L_001563:
    a = myMapper->readCPU(0x0202 + x);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0302 + y, a);
    opCMP(a, 0x30);
    if (!flgC) {
        goto L_001573;
    }
    SUB_000A69();
    return;
L_001573:
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0x1E);
    myMapper->writeCPU(0x0501 + x, 0x11);
    a = myMapper->readCPU(0x0004);
    opROR_A(4);
    myMapper->writeCPU(0x0502 + x, a);
    opEOR(myMapper->readCPU(0x0004));
    opLSR_A(1);
    opADC(0x40);
    myMapper->writeCPU(0x0503 + x, a);
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, x);
    SUB_000A4C();
    return;
}

void game::SUB_001599() {
    x = myMapper->readCPU(0x0000);
    flgC = false;
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    if (!flgN) {
        opADC(myMapper->readCPU(0x0202 + x));
        if (flgC) {
            goto L_0015ED;
        }
        if (!flgC) {
            goto L_0015AD;
        }
    }
    opADC(myMapper->readCPU(0x0202 + x));
    if (flgC) {
    L_0015AD:
        y = a;
        flgC = false;
        a = myMapper->readCPU(0x0203 + x);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x0201 + x));
            if (flgC) {
                goto L_0015ED;
            }
            if (!flgC) {
                goto L_0015C0;
            }
        }
        opADC(myMapper->readCPU(0x0201 + x));
        if (flgC) {
        L_0015C0:
            x = a;
            myMapper->writeCPU(0x0005, x);
            myMapper->writeCPU(0x0006, y);
            pushAddress(0x0015C5);
            SUB_0003AD();
            if (poppedEntry.value != 0x0015C5) return;
            if (!flgZ) {
                goto L_0015ED;
            }
            x = myMapper->readCPU(0x0000);
            y = myMapper->readCPU(0x0001);
            myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
            myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0005));
            myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0006));
            myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
            myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
            SUB_000A69();
            return;
        }
    }
L_0015ED:
    popAddress();
}

void game::SUB_0015EE() {
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0207 + x);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x0015F5);
        SUB_006553();
        if (poppedEntry.value != 0x0015F5) return;
        x = myMapper->readCPU(0x0000);
        a = myMapper->readCPU(0x0207 + x);
        a = 0xFF;
    }
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0307 + y, a);
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    if (myMapper->readCPU(0x0023) != 0x10) {
        myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
        myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
        a = myMapper->readCPU(0x0203 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0303 + y, a);
        if (flgN) {
            a = myMapper->readCPU(0x0201 + x);
            flgC = true;
            opSBC(0x02);
            if (!flgC) {
                goto L_001650;
            }
            if (flgC) {
                goto L_001640;
            }
        }
        a = myMapper->readCPU(0x0201 + x);
        flgC = false;
        opADC(0x02);
        if (!flgC) {
        L_001640:
            myMapper->writeCPU(0x0301 + y, a);
            x = a;
            y = myMapper->readCPU(0x0302 + y);
            pushAddress(0x001648);
            SUB_0003AD();
            if (poppedEntry.value != 0x001648) return;
            if (flgZ) {
                SUB_000A69();
                return;
            }
        }
    L_001650:
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0002);
        a = myMapper->readCPU(0x0004);
        opADC(myMapper->readCPU(0x0001));
        opAND(0x7F);
        myMapper->writeCPU(0x0500 + y, a);
        myMapper->writeCPU(0x0501 + y, myMapper->readCPU(0x0200 + x));
        myMapper->writeCPU(0x0502 + y, myMapper->readCPU(0x0201 + x));
        a = myMapper->readCPU(0x0004);
        opAND(0x3F);
        opADC(0x60);
        myMapper->writeCPU(0x0503 + y, a);
        a = myMapper->readCPU(0x0203 + x);
        opEOR(0x80);
        myMapper->writeCPU(0x0504 + y, a);
        myMapper->writeCPU(0x0505 + y, 0x0A);
        a = y;
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0002, a);
        pushAddress(0x001685);
        SUB_006975();
        if (poppedEntry.value != 0x001685) return;
        SUB_000A4C();
        return;
    }
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0306 + y, myMapper->readCPU(0x0206 + x));
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    opPHA();
    flgC = false;
    opADC(0x01);
    if (a != 0x8C) {
        x = myMapper->readCPU(0x0000);
        myMapper->writeCPU(0x0303 + y, a);
        a = myMapper->readCPU(0x0204 + x);
        myMapper->writeCPU(0x0304 + y, a);
        pushAddress(0x0016C1);
        SUB_001A47();
        if (poppedEntry.value != 0x0016C1) return;
        opPLA();
        y = a;
        a = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
        x = myMapper->readCPU(0x0000);
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x0204 + x);
        if (a != 0x0B) {
            if (a != 0x0C) {
                goto L_0016E0;
            }
            a = myMapper->readCPU(0x0005);
            opEOR(0x88);
            myMapper->writeCPU(0x0005, a);
            goto L_00170F;
        L_0016E0:
            if (a == 0x0E) {
                a = myMapper->readCPU(0x0005);
                opEOR(0x80);
                opLSR_A(4);
                myMapper->writeCPU(0x0006, a);
                a = myMapper->readCPU(0x0005);
                opASL_A(4);
                opORA(myMapper->readCPU(0x0006));
                myMapper->writeCPU(0x0005, a);
            }
            else {
                a = myMapper->readCPU(0x0005);
                opEOR(0x08);
                opASL_A(4);
                myMapper->writeCPU(0x0006, a);
                a = myMapper->readCPU(0x0005);
                opLSR_A(4);
                opORA(myMapper->readCPU(0x0006));
                myMapper->writeCPU(0x0005, a);
            }
        }
    L_00170F:
        a = myMapper->readCPU(0x0005);
        pushAddress(0x001711);
        SUB_001A0C();
        if (poppedEntry.value != 0x001711) return;
        y = myMapper->readCPU(0x0001);
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x000F));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0010));
        SUB_000A69();
        return;
    }
    opPLA();
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0004);
    opAND(0x7F);
    opORA(0x40);
    myMapper->writeCPU(0x0500 + y, a);
    myMapper->writeCPU(0x0501 + y, myMapper->readCPU(0x0200 + x));
    a = myMapper->readCPU(0x0205 + x);
    myMapper->writeCPU(0x0502 + y, a);
    myMapper->writeCPU(0x0506 + y, a);
    a = myMapper->readCPU(0x0206 + x);
    myMapper->writeCPU(0x0503 + y, a);
    myMapper->writeCPU(0x0507 + y, a);
    a = myMapper->readCPU(0x0204 + x);
    myMapper->writeCPU(0x0505 + y, a);
    opCMP(a, 0x0D);
    pushStatus();
    a = 0x11;
    setLoadFlag(a);
    popStatus();
    if (!flgC) {
        goto L_001759;
    }
    a = 0x00;
L_001759:
    myMapper->writeCPU(0x0504 + y, a);
    a = y;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    pushAddress(0x001762);
    SUB_006975();
    if (poppedEntry.value != 0x001762) return;
    SUB_000A4C();
    return;
}

void game::SUB_001768() {
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    opDEC(0x0204 + x, 1);
    if (flgZ) {
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x0203 + x) & 0x80) {
        goto L_001780;
    }
    a = myMapper->readCPU(0x0201 + x);
    flgC = false;
    opADC(0x03);
    goto L_001786;
L_001780:
    a = myMapper->readCPU(0x0201 + x);
    flgC = true;
    opSBC(0x03);
L_001786:
    myMapper->writeCPU(0x0301 + y, a);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0204 + x));
    SUB_000A69();
    return;
}

void game::SUB_0017A4() {
    while (true) {
        x = myMapper->readCPU(0x0000);
        if (myMapper->readCPU(0x0204 + x) == 0) {
            goto L_0017AE;
        }
        goto L_001886;
    L_0017AE:
        a = myMapper->readCPU(0x0203 + x);
        x = 0x00;
        do {
            opCMP(a, myMapper->readCPU(0x0200 + x));
            if (flgZ) {
                goto L_0017CC;
            }
            opINX(8);
        } while (!flgZ);
        x = myMapper->readCPU(0x0000);
        myMapper->writeCPU(0x0204 + x, 0x01);
    }
L_0017CC:
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x0202 + x));
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0304 + y, 0x00);
    a = myMapper->readCPU(0x0205 + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0305 + y, a);
    pushStatus();
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    popStatus();
    if (!flgN) {
        flgC = false;
        opADC(0x01);
    }
    else {
        flgC = true;
        opSBC(0x01);
    }
    myMapper->writeCPU(0x0301 + y, a);
    a = myMapper->readCPU(0x0202 + x);
    opSBC(myMapper->readCPU(0x0006));
    if (flgZ) {
        a = myMapper->readCPU(0x0202 + x);
    }
    else {
        if (flgC) {
            goto L_00182E;
        }
        x = 0x01;
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
        opLSR_A(2);
        do {
            opORA(0x00);
            if (flgZ) {
                goto L_001824;
            }
            opLSR_A(1);
            opINX(1);
        } while (!flgZ);
    L_001824:
        a = x;
        opLSR_A(1);
        x = myMapper->readCPU(0x0000);
        opADC(myMapper->readCPU(0x0202 + x));
        goto L_001847;
    L_00182E:
        x = 0x01;
        opLSR_A(2);
        do {
            opORA(0x00);
            if (flgZ) {
                goto L_00183A;
            }
            opLSR_A(1);
            opINX(1);
        } while (!flgZ);
    L_00183A:
        a = x;
        opEOR(0x01);
        opLSR_A(1);
        myMapper->writeCPU(0x0007, a);
        x = myMapper->readCPU(0x0000);
        a = myMapper->readCPU(0x0202 + x);
        opSBC(myMapper->readCPU(0x0007));
    }
L_001847:
    myMapper->writeCPU(0x0302 + y, a);
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    a = myMapper->readCPU(0x0302 + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x0006));
    if (!flgC) {
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
    }
    if (a < 0x08) {
        if (myMapper->readCPU(0x0305 + y) & 0x80) {
            goto L_001872;
        }
        a = myMapper->readCPU(0x0005);
        flgC = true;
        opSBC(myMapper->readCPU(0x0301 + y));
        if (!flgC) {
            goto L_001883;
        }
        opCMP(a, 0x50);
        if (flgC) {
            goto L_001883;
        }
        if (!flgC) {
            goto L_00187E;
        }
    L_001872:
        a = myMapper->readCPU(0x0301 + y);
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
        if (flgC) {
            if (a >= 0x50) {
                goto L_001883;
            }
        L_00187E:
            myMapper->writeCPU(0x0304 + y, 0x14);
        }
    }
L_001883:
    SUB_000A69();
    return;
L_001886:
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0202 + x));
    myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0203 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0304 + y, a);
    if (!flgZ) {
        if (a == 0x0A) {
            goto L_0018B8;
        }
        SUB_000A69();
        return;
    L_0018B8:
        pushAddress(0x0018B8);
        SUB_006409();
        if (poppedEntry.value != 0x0018B8) return;
        x = myMapper->readCPU(0x0000);
        y = myMapper->readCPU(0x0002);
        myMapper->writeCPU(0x0500 + y, 0x01);
        myMapper->writeCPU(0x0501 + y, 0x15);
        myMapper->writeCPU(0x0502 + y, myMapper->readCPU(0x0201 + x));
        a = myMapper->readCPU(0x0202 + x);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x0503 + y, a);
        myMapper->writeCPU(0x0504 + y, myMapper->readCPU(0x0205 + x));
        myMapper->writeCPU(0x0505 + y, 0x28);
        a = y;
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0002, a);
        SUB_000A69();
        return;
    }
    a = myMapper->readCPU(0x0205 + x);
    opEOR(0x80);
    myMapper->writeCPU(0x0305 + y, a);
    a = myMapper->readCPU(0x0203 + x);
    opEOR(0x03);
    x = 0x00;
    do {
        if (a == myMapper->readCPU(0x0200 + x)) {
            goto L_00190C;
        }
        opINX(8);
    } while (!flgZ);
    opEOR(0x03);
L_00190C:
    myMapper->writeCPU(0x0303 + y, a);
    SUB_000A69();
    return;
}

void game::SUB_001912() {
    x = myMapper->readCPU(0x0000);
    a = myMapper->readCPU(0x0207 + x);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x001919);
        SUB_006650();
        if (poppedEntry.value != 0x001919) return;
        a = 0xFF;
    }
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0307 + y, a);
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0200 + x));
    myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0306 + y, myMapper->readCPU(0x0206 + x));
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0202 + x));
    a = myMapper->readCPU(0x0203 + x);
    opPHA();
    a = myMapper->readCPU(0x0204 + x);
    x = a;
    opPLA();
    opPHA();
    flgC = false;
    opADC(0x01);
    if (a != myMapper->readCPU(0x9A01 + x)) {
        x = myMapper->readCPU(0x0000);
        myMapper->writeCPU(0x0303 + y, a);
        a = myMapper->readCPU(0x0204 + x);
        myMapper->writeCPU(0x0304 + y, a);
        pushAddress(0x001960);
        SUB_001A47();
        if (poppedEntry.value != 0x001960) return;
        opPLA();
        y = a;
        a = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
        x = myMapper->readCPU(0x0000);
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x0204 + x);
        opCMP(a, 0x08);
        if (flgC) {
            if (!flgZ) {
                goto L_00197D;
            }
            a = myMapper->readCPU(0x0005);
            opEOR(0x88);
            myMapper->writeCPU(0x0005, a);
            goto L_0019AC;
        L_00197D:
            if (a != 0x09) {
                goto L_001998;
            }
            a = myMapper->readCPU(0x0005);
            opEOR(0x80);
            opLSR_A(4);
            myMapper->writeCPU(0x0006, a);
            a = myMapper->readCPU(0x0005);
            opASL_A(4);
            opORA(myMapper->readCPU(0x0006));
            myMapper->writeCPU(0x0005, a);
            goto L_0019AC;
        L_001998:
            a = myMapper->readCPU(0x0005);
            opEOR(0x08);
            opASL_A(4);
            myMapper->writeCPU(0x0006, a);
            a = myMapper->readCPU(0x0005);
            opLSR_A(4);
            opORA(myMapper->readCPU(0x0006));
            myMapper->writeCPU(0x0005, a);
        }
    L_0019AC:
        a = myMapper->readCPU(0x0005);
        opPHA();
        x = myMapper->readCPU(0x0000);
        a = myMapper->readCPU(0x0204 + x);
        x = a;
        opPLA();
        myMapper->writeCPU((0x0084 + x) & 0x00ff, a);
        pushAddress(0x0019B8);
        SUB_001A0C();
        if (poppedEntry.value != 0x0019B8) return;
        y = myMapper->readCPU(0x0001);
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x000F));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0010));
        SUB_000A69();
        return;
    }
    opPLA();
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0004);
    opAND(0x7F);
    opORA(0x40);
    myMapper->writeCPU(0x0500 + y, a);
    myMapper->writeCPU(0x0501 + y, myMapper->readCPU(0x0200 + x));
    a = myMapper->readCPU(0x0205 + x);
    myMapper->writeCPU(0x0502 + y, a);
    myMapper->writeCPU(0x0506 + y, a);
    a = myMapper->readCPU(0x0206 + x);
    myMapper->writeCPU(0x0503 + y, a);
    myMapper->writeCPU(0x0507 + y, a);
    myMapper->writeCPU(0x0505 + y, myMapper->readCPU(0x0204 + x));
    myMapper->writeCPU(0x0504 + y, 0x00);
    a = y;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    SUB_000A4C();
    return;
}

void game::SUB_001A0C() {
    opPHA();
    opLSR_A(4);
    opPHA();
    opAND(0x08);
    if (flgZ) {
        opPLA();
        flgC = false;
        opADC(myMapper->readCPU(0x000F));
        myMapper->writeCPU(0x000F, a);
    }
    else {
        opPLA();
        opAND(0x07);
        myMapper->writeCPU(0x0007, a);
        a = myMapper->readCPU(0x000F);
        flgC = true;
        opSBC(myMapper->readCPU(0x0007));
        myMapper->writeCPU(0x000F, a);
    }
    opPLA();
    opAND(0x0F);
    opPHA();
    opAND(0x08);
    if (!flgZ) {
        goto L_001A3A;
    }
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0010, a);
    popAddress();
    return;
L_001A3A:
    opPLA();
    opAND(0x07);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0010);
    flgC = true;
    opSBC(myMapper->readCPU(0x0007));
    myMapper->writeCPU(0x0010, a);
    popAddress();
}

void game::SUB_001A47() {
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x9A52 + x));
    a = myMapper->readCPU(0x9A53 + x);
    myMapper->writeCPU(0x000E, a);
    popAddress();
}

void game::SUB_001C9E() {
    if (myMapper->readCPU(0x0022) == 0x02) {
        goto L_001CA5;
    }
    popAddress();
    return;
L_001CA5:
    a = myMapper->readCPU(0x003C);
    opORA(myMapper->readCPU(0x003D));
    opORA(myMapper->readCPU(0x003E));
    opORA(myMapper->readCPU(0x003F));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0040);
    opORA(myMapper->readCPU(0x0041));
    opORA(myMapper->readCPU(0x0042));
    opORA(myMapper->readCPU(0x0043));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0085);
    opAND(0x02);
    if (!flgZ) {
        pushAddress(0x001CC1);
        SUB_0057C5();
        if (poppedEntry.value != 0x001CC1) return;
        myMapper->writeCPU(0x0085, a);
    }
    else {
        pushAddress(0x001CC9);
        SUB_0057C5();
        if (poppedEntry.value != 0x001CC9) return;
        myMapper->writeCPU(0x0085, a);
        opAND(0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x003E);
            opORA(myMapper->readCPU(0x003F));
            if (!flgZ) {
                pushAddress(0x001CD8);
                SUB_001CFB();
                if (poppedEntry.value != 0x001CD8) return;
            }
        }
    }
    a = myMapper->readCPU(0x0086);
    opAND(0x02);
    if (!flgZ) {
        pushAddress(0x001CE1);
        SUB_0057DE();
        if (poppedEntry.value != 0x001CE1) return;
        myMapper->writeCPU(0x0086, a);
        popAddress();
        return;
    }
    pushAddress(0x001CE7);
    SUB_0057DE();
    if (poppedEntry.value != 0x001CE7) return;
    myMapper->writeCPU(0x0086, a);
    opAND(0x02);
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0042);
    opORA(myMapper->readCPU(0x0043));
    if (!flgZ) {
        goto L_001CF8;
    }
    popAddress();
    return;
L_001CF8:
    SUB_001D3A();
    return;
}

void game::SUB_001CFB() {
    a = myMapper->readCPU(0x003E);
    opORA(myMapper->readCPU(0x003F));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x003E);
    flgC = true;
    opSBC(0x01);
    if (flgC) {
        myMapper->writeCPU(0x003E, a);
    }
    else {
        myMapper->writeCPU(0x003E, 0x09);
        a = myMapper->readCPU(0x003F);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x003F, a);
    }
    pushAddress(0x001D19);
    SUB_0065CA();
    if (poppedEntry.value != 0x001D19) return;
    a = myMapper->readCPU(0x0042);
    flgC = false;
    opADC(0x01);
    if (a < 0x0A) {
        myMapper->writeCPU(0x0042, a);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0042, 0x00);
    a = myMapper->readCPU(0x0043);
    flgC = false;
    opADC(0x01);
    if (a < 0x0A) {
        goto L_001D37;
    }
    a = 0x09;
L_001D37:
    myMapper->writeCPU(0x0043, a);
    popAddress();
}

void game::SUB_001D3A() {
    a = myMapper->readCPU(0x0042);
    opORA(myMapper->readCPU(0x0043));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0042);
    flgC = true;
    opSBC(0x01);
    if (flgC) {
        myMapper->writeCPU(0x0042, a);
    }
    else {
        myMapper->writeCPU(0x0042, 0x09);
        a = myMapper->readCPU(0x0043);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0043, a);
    }
    pushAddress(0x001D58);
    SUB_0065CA();
    if (poppedEntry.value != 0x001D58) return;
    a = myMapper->readCPU(0x003E);
    flgC = false;
    opADC(0x01);
    if (a < 0x0A) {
        myMapper->writeCPU(0x003E, a);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x003E, 0x00);
    a = myMapper->readCPU(0x003F);
    flgC = false;
    opADC(0x01);
    if (a < 0x0A) {
        goto L_001D76;
    }
    a = 0x09;
L_001D76:
    myMapper->writeCPU(0x003F, a);
    popAddress();
}

void game::SUB_002C7F() {
    a = 0x00;
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x0059, a);
    while (true) {
        while (true) {
            x = myMapper->readCPU(0x0058);
            if (myMapper->readCPU(0x0200 + x) == 0) {
                goto L_002D1F;
            }
            if (x == myMapper->readCPU(0x0059)) {
            }
            else {
                y = myMapper->readCPU(0x0059);
                a = myMapper->readCPU(0x0200 + y);
                setLoadFlag(a);
                if (!flgZ) {
                    if (a < myMapper->readCPU(0x0200 + x)) {
                        goto L_002D13;
                    }
                    a = myMapper->readCPU(0x0201 + x);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0201 + y));
                    if (!flgC) {
                        opEOR(0xFF);
                        flgC = false;
                        opADC(0x01);
                    }
                    opPHA();
                    y = myMapper->readCPU(0x0200 + y);
                    a = myMapper->readCPU(0x0200 + x);
                    x = a;
                    opPLA();
                    flgC = true;
                    opSBC(myMapper->readCPU(0xAD43 + x));
                    if (flgC) {
                        opSBC(myMapper->readCPU(0xAD43 + y));
                        if (flgC) {
                            goto L_002D13;
                        }
                    }
                    x = myMapper->readCPU(0x0058);
                    y = myMapper->readCPU(0x0059);
                    a = myMapper->readCPU(0x0202 + x);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0202 + y));
                    if (!flgC) {
                        opEOR(0xFF);
                        flgC = false;
                        opADC(0x01);
                    }
                    opPHA();
                    y = myMapper->readCPU(0x0200 + y);
                    a = myMapper->readCPU(0x0200 + x);
                    x = a;
                    opPLA();
                    flgC = true;
                    opSBC(myMapper->readCPU(0xAD60 + x));
                    if (!flgC) {
                        goto L_002CEC;
                    }
                    opSBC(myMapper->readCPU(0xAD60 + y));
                    if (flgC) {
                        goto L_002D13;
                    }
                L_002CEC:
                    x = myMapper->readCPU(0x0058);
                    y = myMapper->readCPU(0x0059);
                    x = myMapper->readCPU(0x0200 + x);
                    a = myMapper->readCPU(0xAD7C + x);
                    flgC = false;
                    opADC(myMapper->readCPU(0x0200 + y));
                    opASL_A(1);
                    myMapper->writeCPU(0x0005, a);
                    a = 0x00;
                    opROL_A(1);
                    myMapper->writeCPU(0x0006, a);
                    a = 0x99;
                    flgC = false;
                    opADC(myMapper->readCPU(0x0005));
                    myMapper->writeCPU(0x0005, a);
                    a = 0xAD;
                    opADC(myMapper->readCPU(0x0006));
                    myMapper->writeCPU(0x0006, a);
                    pushAddress(0x002D10);
                    SUB_002D30();
                    if (poppedEntry.value != 0x002D10) return;
                }
            }
        L_002D13:
            a = myMapper->readCPU(0x0059);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x0059, a);
            if (flgZ) {
                goto L_002D1F;
            }
        }
    L_002D1F:
        myMapper->writeCPU(0x0059, 0x00);
        a = myMapper->readCPU(0x0058);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0058, a);
        if (flgZ) {
            goto L_002D2F;
        }
    }
L_002D2F:
    popAddress();
}

void game::SUB_002D30() {
    y = 0x00;
    x = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0005, x);
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    indirectJump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_002F05() {
    popAddress();
}

void game::SUB_002F06() {
    a = 0x1E;
    myMapper->writeCPU(0x004A, a);
    myMapper->writeCPU(0x004B, a);
    a = myMapper->readCPU(0x0203 + x);
    opPHA();
    a = myMapper->readCPU(0x0203 + y);
    myMapper->writeCPU(0x0203 + x, a);
    opPLA();
    myMapper->writeCPU(0x0203 + y, a);
    a = myMapper->readCPU(0x0204 + x);
    opPHA();
    a = myMapper->readCPU(0x0204 + y);
    myMapper->writeCPU(0x0204 + x, a);
    opPLA();
    myMapper->writeCPU(0x0204 + y, a);
    popAddress();
}

void game::SUB_002F29() {
    if (myMapper->readCPU(0x0204 + y) != myMapper->readCPU(0x0200 + x)) {
        goto L_002F32;
    }
    popAddress();
    return;
L_002F32:
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_002F40() {
    y = myMapper->readCPU(0x0200 + x);
    opDEY(1);
    a = y;
    opASL_A(2);
    x = a;
    a = myMapper->readCPU((0x003C + x) & 0x00ff);
    opORA(myMapper->readCPU((0x003D + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003E + x) & 0x00ff));
    opORA(myMapper->readCPU((0x003F + x) & 0x00ff));
    if (flgZ) {
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    if (!(myMapper->readCPU(0x0204 + y) & 0x80)) {
        goto L_002F5F;
    }
    pushAddress(0x002F5C);
    SUB_006996();
    if (poppedEntry.value != 0x002F5C) return;
L_002F5F:
    pushAddress(0x002F5F);
    SUB_0065CA();
    if (poppedEntry.value != 0x002F5F) return;
    opDEC(0x001F, 1);
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0200 + y, 0x00);
    a = myMapper->readCPU(0x0200 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(2);
    opPHA();
    x = a;
    pushAddress(0x002F77);
    SUB_0000E8();
    if (poppedEntry.value != 0x002F77) return;
    opPLA();
    opASL_A(1);
    x = a;
    flgC = false;
    a = 0x03;
    pushAddress(0x002F80);
    SUB_000030();
    if (poppedEntry.value != 0x002F80) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x02;
    SUB_00390D();
    return;
}

void game::SUB_002F94() {
    opDEC(0x001F, 1);
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    if (!(myMapper->readCPU(0x0204 + y) & 0x80)) {
        goto L_002FAA;
    }
    pushAddress(0x002FA3);
    SUB_006996();
    if (poppedEntry.value != 0x002FA3) return;
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
L_002FAA:
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    SUB_0038F0();
    return;
}

void game::SUB_002FB7() {
    if (myMapper->readCPU(0x0208 + y) != 0x06) {
        goto L_002FE2;
    }
    myMapper->writeCPU(0x0208 + y, 0x00);
    if (myMapper->readCPU(0x0210 + y) == 0x04) {
        pushAddress(0x002FCA);
        SUB_0062F1();
        if (poppedEntry.value != 0x002FCA) return;
        x = myMapper->readCPU(0x0058);
        y = myMapper->readCPU(0x0059);
        a = myMapper->readCPU(0x0214 + y);
        setLoadFlag(a);
        if (!flgZ) {
            if (flgN) {
                goto L_002FE2;
            }
            myMapper->writeCPU(0x0214 + y, 0xFF);
            myMapper->writeCPU(0x0213 + y, 0x01);
        }
    }
L_002FE2:
    myMapper->writeCPU(0x0200 + y, 0x00);
    pushAddress(0x002FE7);
    SUB_0062C9();
    if (poppedEntry.value != 0x002FE7) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    SUB_0038D3();
    return;
}

void game::SUB_002FF9() {
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    if (!flgZ) {
        opEOR(0x80);
        myMapper->writeCPU(0x0204 + x, a);
    }
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    if (!flgZ) {
        opEOR(0x80);
        myMapper->writeCPU(0x0204 + x, a);
    }
    if (myMapper->readCPU(0x0201 + x) < myMapper->readCPU(0x0201 + y)) {
        goto L_003019;
    }
    a = 0x80;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_00301B;
    }
L_003019:
    a = 0x00;
L_00301B:
    myMapper->writeCPU(0x0203 + y, a);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003027() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003030() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003039() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003042() {
    pushAddress(0x003042);
    SUB_006956();
    if (poppedEntry.value != 0x003042) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003057() {
    a = myMapper->readCPU(0x0203 + x);
    pushAddress(0x00305A);
    SUB_000918();
    if (poppedEntry.value != 0x00305A) return;
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    pushStatus();
    opAND(0x78);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    popStatus();
    if (flgN) {
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x0201 + x, a);
    a = myMapper->readCPU(0x0204 + x);
    pushAddress(0x003082);
    SUB_000918();
    if (poppedEntry.value != 0x003082) return;
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    pushStatus();
    opAND(0x78);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0202 + x);
    setLoadFlag(a);
    popStatus();
    if (flgN) {
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x0202 + x, a);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    if (!flgZ) {
        opEOR(0x80);
    }
    myMapper->writeCPU(0x0203 + x, a);
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0030B8;
    }
    opEOR(0x80);
L_0030B8:
    myMapper->writeCPU(0x0204 + x, a);
    popAddress();
}

void game::SUB_0030BC() {
    a = myMapper->readCPU(0x0203 + x);
    pushAddress(0x0030BF);
    SUB_000918();
    if (poppedEntry.value != 0x0030BF) return;
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    pushStatus();
    opAND(0x78);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0201 + x);
    setLoadFlag(a);
    popStatus();
    if (flgN) {
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x0201 + x, a);
    a = myMapper->readCPU(0x0204 + x);
    pushAddress(0x0030E7);
    SUB_000918();
    if (poppedEntry.value != 0x0030E7) return;
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    pushStatus();
    opAND(0x78);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0202 + x);
    setLoadFlag(a);
    popStatus();
    if (flgN) {
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x0005));
    }
    myMapper->writeCPU(0x0202 + x, a);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    pushStatus();
    opAND(0x7F);
    opLSR_A(2);
    opCMP(a, 0x08);
    if (!flgC) {
        a = 0x08;
        setLoadFlag(a);
    }
    popStatus();
    if (!flgN) {
        opORA(0x80);
    }
    myMapper->writeCPU(0x0203 + x, a);
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    pushStatus();
    opAND(0x7F);
    opLSR_A(2);
    opCMP(a, 0x08);
    if (!flgC) {
        a = 0x08;
        setLoadFlag(a);
    }
    popStatus();
    if (flgN) {
        goto L_003135;
    }
    opORA(0x80);
L_003135:
    myMapper->writeCPU(0x0204 + x, a);
    popAddress();
}

void game::SUB_003139() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003142() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_00314B() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003154() {
    pushAddress(0x003154);
    SUB_00643A();
    if (poppedEntry.value != 0x003154) return;
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0xB4);
    myMapper->writeCPU(0x0501 + x, myMapper->readCPU(0x0200 + y));
    myMapper->writeCPU(0x0502 + x, 0x00);
    myMapper->writeCPU(0x0503 + x, myMapper->readCPU(0x0202 + y));
    myMapper->writeCPU(0x0504 + x, myMapper->readCPU(0x0203 + y));
    myMapper->writeCPU(0x0505 + x, myMapper->readCPU(0x0204 + y));
    myMapper->writeCPU(0x0506 + x, myMapper->readCPU(0x0205 + y));
    myMapper->writeCPU(0x0507 + x, myMapper->readCPU(0x0206 + y));
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_00319D() {
    pushAddress(0x00319D);
    SUB_00695C();
    if (poppedEntry.value != 0x00319D) return;
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_0031AB() {
    opDEC(0x0056, 1);
    if (!flgZ) {
        goto L_0031CE;
    }
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0x3C);
    myMapper->writeCPU(0x0501 + x, 0x12);
    a = 0x00;
    myMapper->writeCPU(0x0502 + x, a);
    myMapper->writeCPU(0x0504 + x, a);
    myMapper->writeCPU(0x0503 + x, 0x60);
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
L_0031CE:
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_0031E2() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_0031EB() {
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_0031FB() {
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003204() {
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0x0A);
    myMapper->writeCPU(0x0501 + x, myMapper->readCPU(0x0200 + y));
    a = myMapper->readCPU(0x0205 + y);
    myMapper->writeCPU(0x0502 + x, a);
    myMapper->writeCPU(0x0506 + x, a);
    a = myMapper->readCPU(0x0206 + y);
    myMapper->writeCPU(0x0503 + x, a);
    myMapper->writeCPU(0x0507 + x, a);
    myMapper->writeCPU(0x0505 + x, myMapper->readCPU(0x0204 + y));
    myMapper->writeCPU(0x0504 + x, 0x00);
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003248() {
    myMapper->writeCPU(0x0200 + y, 0x00);
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU((0x0049 + x) & 0x00ff, 0x1E);
    popAddress();
}

void game::SUB_003258() {
    a = 0x00;
    myMapper->writeCPU(0x0203 + x, a);
    myMapper->writeCPU(0x0204 + x, a);
    y = myMapper->readCPU(0x0200 + x);
    myMapper->writeCPU(0x004D + y, 0xFF);
    a = myMapper->readCPU(0x0200 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(2);
    x = a;
    a = 0x00;
    myMapper->writeCPU((0x003C + x) & 0x00ff, a);
    myMapper->writeCPU((0x003D + x) & 0x00ff, a);
    myMapper->writeCPU((0x003E + x) & 0x00ff, a);
    myMapper->writeCPU((0x003F + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_00327D() {
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    popAddress();
}

void game::SUB_003286() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    flgC = false;
    a = 0x03;
    pushAddress(0x003298);
    SUB_000030();
    if (poppedEntry.value != 0x003298) return;
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    if (myMapper->readCPU(0x0208 + y) == 0x06) {
        myMapper->writeCPU(0x0208 + y, 0x00);
        if (myMapper->readCPU(0x0210 + y) == 0x04) {
            pushAddress(0x0032B2);
            SUB_0062F1();
            if (poppedEntry.value != 0x0032B2) return;
            x = myMapper->readCPU(0x0058);
            y = myMapper->readCPU(0x0059);
            a = myMapper->readCPU(0x0214 + y);
            setLoadFlag(a);
            if (!flgZ) {
                if (flgN) {
                    goto L_0032CA;
                }
                myMapper->writeCPU(0x0214 + y, 0xFF);
                myMapper->writeCPU(0x0213 + y, 0x01);
            }
        }
    }
L_0032CA:
    myMapper->writeCPU(0x0200 + y, 0x00);
    pushAddress(0x0032CF);
    SUB_0062C9();
    if (poppedEntry.value != 0x0032CF) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    pushAddress(0x0032DE);
    SUB_0038D3();
    if (poppedEntry.value != 0x0032DE) return;
    y = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0202 + y);
    flgC = false;
    opSBC(0x0C);
    myMapper->writeCPU(0x000E, a);
    a = 0x02;
    SUB_00390D();
    return;
}

void game::SUB_0032F0() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    a = myMapper->readCPU(0x0203 + y);
    opEOR(0xFF);
    myMapper->writeCPU(0x0203 + y, a);
    popAddress();
}

void game::SUB_0032FE() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    myMapper->writeCPU(0x0206 + y, 0x28);
    popAddress();
}

void game::SUB_003309() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    pushAddress(0x00330E);
    SUB_006385();
    if (poppedEntry.value != 0x00330E) return;
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x01;
    SUB_000030();
    return;
}

void game::SUB_003322() {
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0x50);
    myMapper->writeCPU(0x0501 + x, myMapper->readCPU(0x0200 + y));
    a = myMapper->readCPU(0x0203 + y);
    opEOR(0x80);
    myMapper->writeCPU(0x0504 + x, a);
    myMapper->writeCPU(0x0502 + x, 0x00);
    a = myMapper->readCPU(0x0004);
    opAND(0x3F);
    opADC(0x30);
    myMapper->writeCPU(0x0503 + x, a);
    myMapper->writeCPU(0x0507 + x, 0xFF);
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    x = myMapper->readCPU(0x0058);
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    pushAddress(0x003364);
    SUB_0038F0();
    if (poppedEntry.value != 0x003364) return;
    pushAddress(0x003367);
    SUB_0069C6();
    if (poppedEntry.value != 0x003367) return;
    pushAddress(0x00336A);
    SUB_0064C4();
    if (poppedEntry.value != 0x00336A) return;
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x01;
    pushAddress(0x00337B);
    SUB_000030();
    if (poppedEntry.value != 0x00337B) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x00;
    SUB_00390D();
    return;
}

void game::SUB_00338F() {
    pushAddress(0x00338F);
    SUB_006956();
    if (poppedEntry.value != 0x00338F) return;
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    flgC = false;
    a = 0x01;
    pushAddress(0x00339F);
    SUB_000030();
    if (poppedEntry.value != 0x00339F) return;
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x00;
    SUB_00390D();
    return;
}

void game::SUB_0033BD() {
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    flgC = false;
    a = 0x01;
    pushAddress(0x0033CA);
    SUB_000018();
    if (poppedEntry.value != 0x0033CA) return;
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0200 + x, 0x00);
    pushAddress(0x0033D6);
    SUB_006364();
    if (poppedEntry.value != 0x0033D6) return;
    a = myMapper->readCPU(0x0204 + y);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0204 + y, a);
    }
    else {
        myMapper->writeCPU(0x0204 + y, 0x03);
        a = myMapper->readCPU(0x0203 + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0203 + y, a);
        if (flgZ) {
            myMapper->writeCPU(0x0204 + y, a);
        }
    }
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + x));
    pushAddress(0x003404);
    SUB_0038F0();
    if (poppedEntry.value != 0x003404) return;
    y = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0200 + y);
    if (a == 0x1B) {
        SUB_004B22();
        return;
    }
    if (a == 0x16) {
        SUB_004AFA();
        return;
    }
    if (a != 0x0C) {
        goto L_003421;
    }
    SUB_004ADB();
    return;
L_003421:
    popAddress();
}

void game::SUB_003422() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    a = myMapper->readCPU(0x0207 + y);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0207 + y, a);
    if (a == 0x01) {
        a = myMapper->readCPU(0x0204 + x);
        flgC = true;
        opSBC(0x01);
        opASL_A(3);
        x = a;
        a = 0x05;
        pushAddress(0x003440);
        SUB_000030();
        if (poppedEntry.value != 0x003440) return;
        y = myMapper->readCPU(0x0059);
        myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
        a = myMapper->readCPU(0x0202 + y);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        a = 0x03;
        pushAddress(0x003454);
        SUB_00390D();
        if (poppedEntry.value != 0x003454) return;
        x = myMapper->readCPU(0x0058);
        y = myMapper->readCPU(0x0059);
        myMapper->writeCPU(0x0200 + y, 0x0F);
        pushAddress(0x003460);
        SUB_0069C3();
        if (poppedEntry.value != 0x003460) return;
        y = myMapper->readCPU(0x0059);
        if (myMapper->readCPU(0x0206 + y) != 0) {
            pushAddress(0x00346A);
            SUB_00694D();
            if (poppedEntry.value != 0x00346A) return;
        }
        y = myMapper->readCPU(0x0059);
        if (myMapper->readCPU(0x0205 + y) != 0x04) {
            goto L_003478;
        }
        opDEC(0x001F, 1);
    }
L_003478:
    popAddress();
}

void game::SUB_003479() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    a = myMapper->readCPU(0x0204 + y);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0204 + y, a);
    if (flgZ) {
        goto L_00348A;
    }
    popAddress();
    return;
L_00348A:
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0x32);
    myMapper->writeCPU(0x0501 + x, myMapper->readCPU(0x0200 + y));
    myMapper->writeCPU(0x0503 + x, myMapper->readCPU(0x0202 + y));
    myMapper->writeCPU(0x0502 + x, 0x00);
    a = myMapper->readCPU(0x0203 + y);
    opEOR(0x80);
    myMapper->writeCPU(0x0504 + x, a);
    myMapper->writeCPU(0x0505 + x, 0x05);
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0200 + y, 0x00);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    pushAddress(0x0034C4);
    SUB_0038F0();
    if (poppedEntry.value != 0x0034C4) return;
    pushAddress(0x0034C7);
    SUB_006959();
    if (poppedEntry.value != 0x0034C7) return;
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x05;
    pushAddress(0x0034D8);
    SUB_000030();
    if (poppedEntry.value != 0x0034D8) return;
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x0C);
    myMapper->writeCPU(0x000E, a);
    a = 0x03;
    pushAddress(0x0034E4);
    SUB_00390D();
    if (poppedEntry.value != 0x0034E4) return;
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x05;
    SUB_000030();
    return;
}

void game::SUB_0034F8() {
    pushAddress(0x0034F8);
    SUB_00643A();
    if (poppedEntry.value != 0x0034F8) return;
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0xB4);
    myMapper->writeCPU(0x0501 + x, myMapper->readCPU(0x0200 + y));
    myMapper->writeCPU(0x0502 + x, 0x00);
    myMapper->writeCPU(0x0503 + x, myMapper->readCPU(0x0202 + y));
    myMapper->writeCPU(0x0504 + x, myMapper->readCPU(0x0203 + y));
    myMapper->writeCPU(0x0505 + x, myMapper->readCPU(0x0204 + y));
    myMapper->writeCPU(0x0506 + x, myMapper->readCPU(0x0205 + y));
    myMapper->writeCPU(0x0507 + x, myMapper->readCPU(0x0206 + y));
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    x = myMapper->readCPU(0x0058);
    a = 0x00;
    myMapper->writeCPU(0x0200 + y, a);
    myMapper->writeCPU(0x0200 + x, a);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x01;
    pushAddress(0x003547);
    SUB_000030();
    if (poppedEntry.value != 0x003547) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x00;
    SUB_00390D();
    return;
}

void game::SUB_00355B() {
    myMapper->writeCPU(0x0056, 0x04);
    pushAddress(0x00355F);
    SUB_00695C();
    if (poppedEntry.value != 0x00355F) return;
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0200 + x, 0x00);
    myMapper->writeCPU(0x0200 + y, a);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x01;
    flgC = false;
    pushAddress(0x00357B);
    SUB_000030();
    if (poppedEntry.value != 0x00357B) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x00;
    pushAddress(0x00358C);
    SUB_00390D();
    if (poppedEntry.value != 0x00358C) return;
    x = myMapper->readCPU(0x0002);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0500 + x, 0x10);
    myMapper->writeCPU(0x0508 + x, a);
    myMapper->writeCPU(0x0510 + x, a);
    myMapper->writeCPU(0x0518 + x, a);
    myMapper->writeCPU(0x0501 + x, 0x13);
    myMapper->writeCPU(0x0509 + x, a);
    myMapper->writeCPU(0x0511 + x, a);
    myMapper->writeCPU(0x0519 + x, a);
    myMapper->writeCPU(0x0504 + x, 0x00);
    myMapper->writeCPU(0x050C + x, a);
    myMapper->writeCPU(0x0514 + x, a);
    myMapper->writeCPU(0x051C + x, a);
    myMapper->writeCPU(0x0505 + x, 0x14);
    myMapper->writeCPU(0x050D + x, a);
    myMapper->writeCPU(0x0515 + x, a);
    myMapper->writeCPU(0x051D + x, a);
    myMapper->writeCPU(0x0506 + x, 0x00);
    myMapper->writeCPU(0x050E + x, 0x01);
    myMapper->writeCPU(0x0516 + x, 0x02);
    myMapper->writeCPU(0x051E + x, 0x03);
    myMapper->writeCPU(0x0502 + x, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x050A + x, a);
    myMapper->writeCPU(0x0512 + x, a);
    myMapper->writeCPU(0x051A + x, a);
    myMapper->writeCPU(0x0503 + x, myMapper->readCPU(0x0202 + y));
    myMapper->writeCPU(0x050B + x, a);
    myMapper->writeCPU(0x0513 + x, a);
    myMapper->writeCPU(0x051B + x, a);
    a = x;
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0002, a);
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x05;
    SUB_000030();
    return;
}

void game::SUB_003614() {
    opDEC(0x0056, 1);
    if (!flgZ) {
        goto L_003637;
    }
    x = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0500 + x, 0x3C);
    myMapper->writeCPU(0x0501 + x, 0x12);
    a = 0x00;
    myMapper->writeCPU(0x0502 + x, a);
    myMapper->writeCPU(0x0504 + x, a);
    myMapper->writeCPU(0x0503 + x, 0x60);
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
L_003637:
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x03;
    SUB_000018();
    return;
}


void game::SUB_003652() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    popAddress();
}

void game::SUB_003658() {
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    flgC = false;
    a = 0x01;
    pushAddress(0x00366D);
    SUB_000030();
    if (poppedEntry.value != 0x00366D) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x00;
    SUB_00390D();
    return;
}

void game::SUB_003681() {
    a = myMapper->readCPU(0x0204 + x);
    flgC = true;
    opSBC(0x01);
    opASL_A(3);
    x = a;
    a = 0x01;
    pushAddress(0x00368D);
    SUB_000030();
    if (poppedEntry.value != 0x00368D) return;
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + y));
    a = 0x00;
    pushAddress(0x00369E);
    SUB_00390D();
    if (poppedEntry.value != 0x00369E) return;
    pushAddress(0x0036A1);
    SUB_006975();
    if (poppedEntry.value != 0x0036A1) return;
    y = myMapper->readCPU(0x0059);
    x = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0004);
    opAND(0x7F);
    opORA(0x0F);
    myMapper->writeCPU(0x0500 + x, a);
    myMapper->writeCPU(0x0501 + x, myMapper->readCPU(0x0200 + y));
    myMapper->writeCPU(0x0502 + x, 0x00);
    myMapper->writeCPU(0x0503 + x, myMapper->readCPU(0x0202 + y));
    myMapper->writeCPU(0x0504 + x, myMapper->readCPU(0x0203 + y));
    myMapper->writeCPU(0x0505 + x, myMapper->readCPU(0x0204 + y));
    myMapper->writeCPU(0x0506 + x, myMapper->readCPU(0x0205 + y));
    myMapper->writeCPU(0x0507 + x, myMapper->readCPU(0x0206 + y));
    if (myMapper->readCPU(0x0023) == 0x10) {
        myMapper->writeCPU(0x0502 + x, myMapper->readCPU(0x0205 + y));
        myMapper->writeCPU(0x0503 + x, myMapper->readCPU(0x0206 + y));
        opCMP(myMapper->readCPU(0x0204 + y), 0x0D);
        pushStatus();
        a = 0x11;
        setLoadFlag(a);
        popStatus();
        if (flgC) {
            a = 0x00;
        }
        myMapper->writeCPU(0x0504 + x, a);
    }
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0002, a);
    a = 0x00;
    x = myMapper->readCPU(0x0058);
    myMapper->writeCPU(0x0200 + y, a);
    myMapper->writeCPU(0x0200 + x, a);
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    x = 0x00;
    do {
        if (a == myMapper->readCPU(0x0200 + x)) {
            goto L_003723;
        }
        opINX(8);
    } while (!flgZ);
    popAddress();
    return;
L_003723:
    y = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0201 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0201 + y));
    myMapper->writeCPU(0x0005, a);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0202 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0202 + y));
    myMapper->writeCPU(0x0006, a);
    myMapper->writeCPU(0x0008, a);
    if (flgN) {
        opEOR(0xFF);
        myMapper->writeCPU(0x0008, a);
        opINC(0x0008, 1);
    }
    a = myMapper->readCPU(0x0007);
    setLoadFlag(a);
    if (flgN) {
        opEOR(0xFF);
        myMapper->writeCPU(0x0007, a);
        opINC(0x0007, 1);
    }
    while (true) {
        a = myMapper->readCPU(0x0007);
        opORA(myMapper->readCPU(0x0008));
        opAND(0xFC);
        if (flgZ) {
            goto L_00375C;
        }
        opLSR_M(0x0007, 1);
        opLSR_M(0x0008, 1);
    }
L_00375C:
    if (myMapper->readCPU(0x0005) & 0x80) {
        a = myMapper->readCPU(0x0007);
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0007, a);
    }
    if (!(myMapper->readCPU(0x0006) & 0x80)) {
        goto L_003776;
    }
    a = myMapper->readCPU(0x0008);
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0008, a);
L_003776:
    x = myMapper->readCPU(0x0002);
    a = 0x04;
    myMapper->writeCPU(0x0500 + x, a);
    myMapper->writeCPU(0x0508 + x, a);
    myMapper->writeCPU(0x0510 + x, a);
    myMapper->writeCPU(0x0518 + x, a);
    a = 0x1A;
    myMapper->writeCPU(0x0501 + x, a);
    myMapper->writeCPU(0x0509 + x, a);
    myMapper->writeCPU(0x0511 + x, a);
    myMapper->writeCPU(0x0519 + x, a);
    a = myMapper->readCPU(0x0007);
    myMapper->writeCPU(0x0504 + x, a);
    myMapper->writeCPU(0x050C + x, a);
    myMapper->writeCPU(0x0514 + x, a);
    myMapper->writeCPU(0x051C + x, a);
    a = myMapper->readCPU(0x0008);
    myMapper->writeCPU(0x0505 + x, a);
    myMapper->writeCPU(0x050D + x, a);
    myMapper->writeCPU(0x0515 + x, a);
    myMapper->writeCPU(0x051D + x, a);
    a = myMapper->readCPU(0x0201 + y);
    opSBC(0x08);
    myMapper->writeCPU(0x0502 + x, a);
    myMapper->writeCPU(0x050A + x, a);
    opADC(0x10);
    myMapper->writeCPU(0x0512 + x, a);
    myMapper->writeCPU(0x051A + x, a);
    a = myMapper->readCPU(0x0202 + y);
    opSBC(0x08);
    myMapper->writeCPU(0x0503 + x, a);
    myMapper->writeCPU(0x0513 + x, a);
    opADC(0x10);
    myMapper->writeCPU(0x050B + x, a);
    myMapper->writeCPU(0x051B + x, a);
    a = x;
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0002, a);
    popAddress();
}

void game::SUB_0037DD() {
    popAddress();
}

void game::SUB_0037DE() {
    a = 0x00;
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0200 + y, a);
    popAddress();
}

void game::SUB_0037E7() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    popAddress();
}

void game::SUB_0037ED() {
    if (myMapper->readCPU(0x0201 + x) < myMapper->readCPU(0x0201 + y)) {
        goto L_0037F9;
    }
    a = 0x80;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0037FB;
    }
L_0037F9:
    a = 0x00;
L_0037FB:
    myMapper->writeCPU(0x0203 + y, a);
    popAddress();
}

void game::SUB_0037FF() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    opDEC(0x001F, 1);
    if (!(myMapper->readCPU(0x0204 + x) & 0x80)) {
        goto L_003812;
    }
    pushAddress(0x00380B);
    SUB_006996();
    if (poppedEntry.value != 0x00380B) return;
    x = myMapper->readCPU(0x0058);
    y = myMapper->readCPU(0x0059);
L_003812:
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + x));
    SUB_0038F0();
    return;
}

void game::SUB_00381F() {
    if (myMapper->readCPU(0x0208 + x) != 0x06) {
        goto L_003843;
    }
    myMapper->writeCPU(0x0208 + x, 0x00);
    if (myMapper->readCPU(0x0210 + x) == 0x04) {
        a = myMapper->readCPU(0x0214 + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (flgN) {
                goto L_003843;
            }
            myMapper->writeCPU(0x0214 + x, 0xFF);
            myMapper->writeCPU(0x0213 + x, 0x01);
        }
    }
L_003843:
    myMapper->writeCPU(0x0200 + x, 0x00);
    pushAddress(0x003848);
    SUB_0062C9();
    if (poppedEntry.value != 0x003848) return;
    x = myMapper->readCPU(0x0058);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + x));
    SUB_0038D3();
    return;
}

void game::SUB_00385A() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    pushAddress(0x00385F);
    SUB_006337();
    if (poppedEntry.value != 0x00385F) return;
    if (myMapper->readCPU(0x0208 + x) == 0x04) {
        a = myMapper->readCPU(0x020C + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (flgN) {
                goto L_003875;
            }
            myMapper->writeCPU(0x020C + x, 0xFF);
        }
    }
L_003875:
    popAddress();
}

void game::SUB_003876() {
    a = myMapper->readCPU(0x0203 + x);
    myMapper->writeCPU(0x0203 + y, a);
    opEOR(0xFF);
    myMapper->writeCPU(0x0203 + x, a);
    popAddress();
}

void game::SUB_0038A6() {
    popAddress();
}

void game::SUB_0038A7() {
    myMapper->writeCPU(0x0200 + x, 0x00);
    SUB_00659D();
    return;
}

void game::SUB_0038AF() {
    x = myMapper->readCPU(0x0003);
    myMapper->writeCPU(0x0400 + x, 0x02);
    myMapper->writeCPU(0x0403 + x, 0x01);
    myMapper->writeCPU(0x0401 + x, myMapper->readCPU(0x000D));
    myMapper->writeCPU(0x0402 + x, myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x0404 + x, myMapper->readCPU(0x0013));
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0003, a);
    SUB_0065FB();
    return;
}

void game::SUB_0038D3() {
    x = myMapper->readCPU(0x0003);
    myMapper->writeCPU(0x0400 + x, 0x18);
    myMapper->writeCPU(0x0403 + x, 0x02);
    myMapper->writeCPU(0x0401 + x, myMapper->readCPU(0x000D));
    myMapper->writeCPU(0x0402 + x, myMapper->readCPU(0x000E));
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0003, a);
    popAddress();
}

void game::SUB_0038F0() {
    x = myMapper->readCPU(0x0003);
    myMapper->writeCPU(0x0400 + x, 0x03);
    myMapper->writeCPU(0x0403 + x, 0x03);
    myMapper->writeCPU(0x0401 + x, myMapper->readCPU(0x000D));
    myMapper->writeCPU(0x0402 + x, myMapper->readCPU(0x000E));
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0003, a);
    popAddress();
}

void game::SUB_00390D() {
    x = myMapper->readCPU(0x0003);
    myMapper->writeCPU(0x0404 + x, a);
    myMapper->writeCPU(0x0400 + x, 0x1E);
    myMapper->writeCPU(0x0403 + x, 0x04);
    myMapper->writeCPU(0x0401 + x, myMapper->readCPU(0x000D));
    myMapper->writeCPU(0x0402 + x, myMapper->readCPU(0x000E));
    a = x;
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0003, a);
    popAddress();
}

void game::SUB_00392D() {
    if (myMapper->readCPU(0x0023) != 0x10) {
        goto L_00393A;
    }
    a = myMapper->readCPU(0x0004);
    opAND(0x01);
    if (flgZ) {
        goto L_00393A;
    }
    popAddress();
    return;
L_00393A:
    x = 0x00;
    do {
        if (myMapper->readCPU(0x0200 + x) == 0) {
            goto L_003949;
        }
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        setLoadFlag(x);
    } while (!flgZ);
    popAddress();
    return;
L_003949:
    y = 0x00;
    do {
        if (myMapper->readCPU(0x0500 + y) == 0) {
            goto L_00398C;
        }
        a = myMapper->readCPU(0x0500 + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0500 + y, a);
        if (!flgZ) {
            goto L_00398C;
        }
        myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0501 + y));
        myMapper->writeCPU(0x0201 + x, myMapper->readCPU(0x0502 + y));
        myMapper->writeCPU(0x0202 + x, myMapper->readCPU(0x0503 + y));
        myMapper->writeCPU(0x0203 + x, myMapper->readCPU(0x0504 + y));
        myMapper->writeCPU(0x0204 + x, myMapper->readCPU(0x0505 + y));
        myMapper->writeCPU(0x0205 + x, myMapper->readCPU(0x0506 + y));
        myMapper->writeCPU(0x0206 + x, myMapper->readCPU(0x0507 + y));
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        setLoadFlag(x);
        if (flgZ) {
            goto L_003993;
        }
    L_00398C:
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
        setLoadFlag(y);
    } while (!flgZ);
L_003993:
    x = 0x00;
    y = 0x00;
    do {
        if (myMapper->readCPU(0x0500 + x) == 0) {
            goto L_0039D1;
        }
        myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0500 + x));
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0501 + x));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0502 + x));
        myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0503 + x));
        myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0504 + x));
        myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0505 + x));
        myMapper->writeCPU(0x0306 + y, myMapper->readCPU(0x0506 + x));
        myMapper->writeCPU(0x0307 + y, myMapper->readCPU(0x0507 + x));
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    L_0039D1:
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        setLoadFlag(x);
    } while (!flgZ);
    myMapper->writeCPU(0x0002, y);
    a = 0x00;
    do {
        myMapper->writeCPU(0x0300 + y, a);
        opINY(1);
    } while (!flgZ);
    do {
        myMapper->writeCPU(0x0500 + y, myMapper->readCPU(0x0300 + y));
        opINY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0039EC() {
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x070B + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0707 + x, a);
    myMapper->writeCPU(0x070F + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0704 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0708 + x, a);
    myMapper->writeCPU(0x070C + x, a);
    popAddress();
}

void game::SUB_003A15() {
    a = myMapper->readCPU(0xBA43 + y);
    opORA(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBA5B + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBA5C + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBA5D + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBA5E + y));
    popAddress();
}

void game::SUB_003ABB() {
    pushAddress(0x003ABB);
    SUB_003A15();
    if (poppedEntry.value != 0x003ABB) return;
    pushAddress(0x003ABE);
    SUB_0039EC();
    if (poppedEntry.value != 0x003ABE) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003AC7() {
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x0B);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x070F + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0707 + x, a);
    myMapper->writeCPU(0x0713 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070B + x, a);
    myMapper->writeCPU(0x0717 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0704 + x, a);
    myMapper->writeCPU(0x0708 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070C + x, a);
    myMapper->writeCPU(0x0710 + x, a);
    myMapper->writeCPU(0x0714 + x, a);
    popAddress();
}

void game::SUB_003AFF() {
    a = myMapper->readCPU(0xBB42 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    myMapper->writeCPU(0x0712 + x, a);
    myMapper->writeCPU(0x0716 + x, a);
    a = y;
    opASL_A(1);
    myMapper->writeCPU(0x0005, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBB4E + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBB4F + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBB50 + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBB51 + y));
    myMapper->writeCPU(0x0711 + x, myMapper->readCPU(0xBB52 + y));
    myMapper->writeCPU(0x0715 + x, myMapper->readCPU(0xBB53 + y));
    popAddress();
}

void game::SUB_003B96() {
    pushAddress(0x003B96);
    SUB_003AFF();
    if (poppedEntry.value != 0x003B96) return;
    pushAddress(0x003B99);
    SUB_003AC7();
    if (poppedEntry.value != 0x003B99) return;
    a = x;
    flgC = false;
    opADC(0x18);
    x = a;
    popAddress();
}

void game::SUB_003BA2() {
    a = myMapper->readCPU(0xBBCE + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBBDE + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBBDF + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBBE0 + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBBE1 + y));
    popAddress();
}

void game::SUB_003C1E() {
    pushAddress(0x003C1E);
    SUB_003BA2();
    if (poppedEntry.value != 0x003C1E) return;
    pushAddress(0x003C21);
    SUB_0039EC();
    if (poppedEntry.value != 0x003C21) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003C2A() {
    a = myMapper->readCPU(0xBC6D + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    myMapper->writeCPU(0x0712 + x, a);
    myMapper->writeCPU(0x0716 + x, a);
    a = y;
    opASL_A(1);
    myMapper->writeCPU(0x0005, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBC71 + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBC72 + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBC73 + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBC74 + y));
    myMapper->writeCPU(0x0711 + x, myMapper->readCPU(0xBC75 + y));
    myMapper->writeCPU(0x0715 + x, myMapper->readCPU(0xBC76 + y));
    popAddress();
}

void game::SUB_003C89() {
    pushAddress(0x003C89);
    SUB_003C2A();
    if (poppedEntry.value != 0x003C89) return;
    pushAddress(0x003C8C);
    SUB_003AC7();
    if (poppedEntry.value != 0x003C8C) return;
    a = x;
    flgC = false;
    opADC(0x18);
    x = a;
    popAddress();
}

void game::SUB_003C95() {
    a = myMapper->readCPU(0xBCC1 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBCD3 + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBCD4 + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBCD5 + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBCD6 + y));
    popAddress();
}

void game::SUB_003D1B() {
    pushAddress(0x003D1B);
    SUB_003C95();
    if (poppedEntry.value != 0x003D1B) return;
    pushAddress(0x003D1E);
    SUB_0039EC();
    if (poppedEntry.value != 0x003D1E) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003D27() {
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0702 + x, myMapper->readCPU(0xBD5C + y));
    myMapper->writeCPU(0x0706 + x, myMapper->readCPU(0xBD5D + y));
    myMapper->writeCPU(0x070A + x, myMapper->readCPU(0xBD5E + y));
    myMapper->writeCPU(0x070E + x, myMapper->readCPU(0xBD5F + y));
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBD7C + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBD7D + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBD7E + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBD7F + y));
    popAddress();
}

void game::SUB_003D9C() {
    pushAddress(0x003D9C);
    SUB_003D27();
    if (poppedEntry.value != 0x003D9C) return;
    pushAddress(0x003D9F);
    SUB_0039EC();
    if (poppedEntry.value != 0x003D9F) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003DA8() {
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0702 + x, myMapper->readCPU(0xBDDD + y));
    myMapper->writeCPU(0x0706 + x, myMapper->readCPU(0xBDDE + y));
    myMapper->writeCPU(0x070A + x, myMapper->readCPU(0xBDDF + y));
    myMapper->writeCPU(0x070E + x, myMapper->readCPU(0xBDE0 + y));
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBDED + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBDEE + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBDEF + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBDF0 + y));
    popAddress();
}

void game::SUB_003DFD() {
    pushAddress(0x003DFD);
    SUB_003DA8();
    if (poppedEntry.value != 0x003DFD) return;
    pushAddress(0x003E00);
    SUB_0039EC();
    if (poppedEntry.value != 0x003E00) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003E09() {
    a = myMapper->readCPU(0xBE35 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBE3D + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBE3E + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBE3F + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBE40 + y));
    popAddress();
}

void game::SUB_003E5D() {
    pushAddress(0x003E5D);
    SUB_003E09();
    if (poppedEntry.value != 0x003E5D) return;
    pushAddress(0x003E60);
    SUB_0039EC();
    if (poppedEntry.value != 0x003E60) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003E69() {
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0703 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0700 + x, a);
    popAddress();
}

void game::SUB_003E7A() {
    myMapper->writeCPU(0x0702 + x, myMapper->readCPU(0xBE87 + y));
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBE91 + y));
    popAddress();
}

void game::SUB_003E9B() {
    pushAddress(0x003E9B);
    SUB_003E7A();
    if (poppedEntry.value != 0x003E9B) return;
    pushAddress(0x003E9E);
    SUB_003E69();
    if (poppedEntry.value != 0x003E9E) return;
    opINX(4);
    popAddress();
}

void game::SUB_003EA6() {
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x0707 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0700 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0704 + x, a);
    popAddress();
}

void game::SUB_003EC0() {
    a = myMapper->readCPU(0xBED9 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    a = y;
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBEDB + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBEDC + y));
    popAddress();
}

void game::SUB_003EDF() {
    pushAddress(0x003EDF);
    SUB_003EC0();
    if (poppedEntry.value != 0x003EDF) return;
    pushAddress(0x003EE2);
    SUB_003EA6();
    if (poppedEntry.value != 0x003EE2) return;
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    popAddress();
}

void game::SUB_003EEB() {
    a = myMapper->readCPU(0xBF17 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBF1B + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBF1C + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBF1D + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBF1E + y));
    popAddress();
}

void game::SUB_003F2B() {
    pushAddress(0x003F2B);
    SUB_003EEB();
    if (poppedEntry.value != 0x003F2B) return;
    pushAddress(0x003F2E);
    SUB_0039EC();
    if (poppedEntry.value != 0x003F2E) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003F37() {
    a = myMapper->readCPU(0xBF63 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xBF67 + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xBF68 + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xBF69 + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xBF6A + y));
    popAddress();
}

void game::SUB_003F77() {
    pushAddress(0x003F77);
    SUB_003F37();
    if (poppedEntry.value != 0x003F77) return;
    pushAddress(0x003F7A);
    SUB_0039EC();
    if (poppedEntry.value != 0x003F7A) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_003F83() {
    a = y;
    opAND(0x01);
    if (!flgZ) {
        goto L_003FB1;
    }
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x0B);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x070B + x, a);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x0707 + x, a);
    myMapper->writeCPU(0x070F + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x0B);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0704 + x, a);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x0708 + x, a);
    myMapper->writeCPU(0x070C + x, a);
    popAddress();
    return;
L_003FB1:
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x0B);
    myMapper->writeCPU(0x0707 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x070F + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070B + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x0B);
    myMapper->writeCPU(0x0700 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0704 + x, a);
    myMapper->writeCPU(0x0708 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070C + x, a);
    popAddress();
}

void game::SUB_003FE0() {
    a = y;
    opASL_A(2);
    y = a;
    a = myMapper->readCPU(0xC01D + y);
    opORA(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0702 + x, a);
    a = myMapper->readCPU(0xC01E + y);
    opORA(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x0706 + x, a);
    a = myMapper->readCPU(0xC01F + y);
    opORA(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x070A + x, a);
    a = myMapper->readCPU(0xC020 + y);
    opORA(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x070E + x, a);
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC02D + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xC02E + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xC02F + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xC030 + y));
    popAddress();
}

void game::SUB_00403D() {
    pushAddress(0x00403D);
    SUB_003F83();
    if (poppedEntry.value != 0x00403D) return;
    pushAddress(0x004040);
    SUB_003FE0();
    if (poppedEntry.value != 0x004040) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_004049() {
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x07);
    myMapper->writeCPU(0x0703 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0707 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0704 + x, a);
    popAddress();
}

void game::SUB_004063() {
    a = 0x00;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    a = y;
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC07B + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xC07C + y));
    popAddress();
}

void game::SUB_00408F() {
    pushAddress(0x00408F);
    SUB_004063();
    if (poppedEntry.value != 0x00408F) return;
    pushAddress(0x004092);
    SUB_004049();
    if (poppedEntry.value != 0x004092) return;
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    popAddress();
}

void game::SUB_00409B() {
    a = myMapper->readCPU(0xC0AE + y);
    if (y != 0x00) {
        goto L_0040A4;
    }
    opORA(myMapper->readCPU(0x0013));
L_0040A4:
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC0B0 + y));
    popAddress();
}

void game::SUB_0040B2() {
    pushAddress(0x0040B2);
    SUB_00409B();
    if (poppedEntry.value != 0x0040B2) return;
    pushAddress(0x0040B5);
    SUB_003E69();
    if (poppedEntry.value != 0x0040B5) return;
    opINX(4);
    popAddress();
}

void game::SUB_0040BD() {
    a = myMapper->readCPU(0xC0E9 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC0ED + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xC0EE + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xC0EF + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xC0F0 + y));
    popAddress();
}

void game::SUB_0040FD() {
    pushAddress(0x0040FD);
    SUB_0040BD();
    if (poppedEntry.value != 0x0040FD) return;
    pushAddress(0x004100);
    SUB_0039EC();
    if (poppedEntry.value != 0x004100) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_004109() {
    a = myMapper->readCPU(0xC135 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    a = y;
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC139 + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xC13A + y));
    myMapper->writeCPU(0x0709 + x, myMapper->readCPU(0xC13B + y));
    myMapper->writeCPU(0x070D + x, myMapper->readCPU(0xC13C + y));
    popAddress();
}

void game::SUB_004149() {
    pushAddress(0x004149);
    SUB_004109();
    if (poppedEntry.value != 0x004149) return;
    pushAddress(0x00414C);
    SUB_0039EC();
    if (poppedEntry.value != 0x00414C) return;
    a = x;
    flgC = false;
    opADC(0x10);
    x = a;
    popAddress();
}

void game::SUB_004155() {
    a = 0x00;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x0701 + x, 0xF1);
    myMapper->writeCPU(0x0705 + x, 0xF2);
    popAddress();
}

void game::SUB_004168() {
    if (myMapper->readCPU(0x0023) >= 0x0D) {
        goto L_00417A;
    }
    pushAddress(0x00416E);
    SUB_004049();
    if (poppedEntry.value != 0x00416E) return;
    pushAddress(0x004171);
    SUB_004155();
    if (poppedEntry.value != 0x004171) return;
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    popAddress();
    return;
L_00417A:
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0703 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x05);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0701 + x, 0xFA);
    myMapper->writeCPU(0x0702 + x, 0x20);
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    popAddress();
}

void game::SUB_00419A() {
    a = myMapper->readCPU(0xC1B3 + y);
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    a = y;
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC1B6 + y));
    myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0xC1B7 + y));
    popAddress();
}

void game::SUB_0041BC() {
    pushAddress(0x0041BC);
    SUB_004049();
    if (poppedEntry.value != 0x0041BC) return;
    pushAddress(0x0041BF);
    SUB_00419A();
    if (poppedEntry.value != 0x0041BF) return;
    a = x;
    flgC = false;
    opADC(0x08);
    x = a;
    popAddress();
}

void game::SUB_0041C8() {
    if (y != 0x00) {
        goto L_00420E;
    }
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x0707 + x, a);
    myMapper->writeCPU(0x070B + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x18);
    myMapper->writeCPU(0x0700 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0704 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0708 + x, a);
    myMapper->writeCPU(0x0701 + x, 0xA8);
    myMapper->writeCPU(0x0705 + x, 0xA9);
    myMapper->writeCPU(0x0709 + x, 0xAA);
    a = 0x03;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    a = x;
    flgC = false;
    opADC(0x0C);
    x = a;
    popAddress();
    return;
L_00420E:
    if (y == 0x01) {
        a = myMapper->readCPU(0x000D);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x0703 + x, a);
        myMapper->writeCPU(0x0707 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x070B + x, a);
        myMapper->writeCPU(0x070F + x, a);
        myMapper->writeCPU(0x0713 + x, a);
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x18);
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x0708 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0704 + x, a);
        myMapper->writeCPU(0x070C + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0710 + x, a);
        myMapper->writeCPU(0x0701 + x, 0xAB);
        myMapper->writeCPU(0x0705 + x, 0xAC);
        myMapper->writeCPU(0x0709 + x, 0xAD);
        myMapper->writeCPU(0x070D + x, 0xAE);
        myMapper->writeCPU(0x0711 + x, 0xAA);
        a = 0x03;
        myMapper->writeCPU(0x0702 + x, a);
        myMapper->writeCPU(0x0706 + x, a);
        myMapper->writeCPU(0x070A + x, a);
        myMapper->writeCPU(0x070E + x, a);
        myMapper->writeCPU(0x0712 + x, a);
        a = x;
        flgC = false;
        opADC(0x14);
        x = a;
        popAddress();
        return;
    }
    if (y == 0x02) {
        a = myMapper->readCPU(0x000D);
        flgC = true;
        opSBC(0x14);
        myMapper->writeCPU(0x0703 + x, a);
        myMapper->writeCPU(0x0707 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x070B + x, a);
        myMapper->writeCPU(0x070F + x, a);
        myMapper->writeCPU(0x0713 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0717 + x, a);
        myMapper->writeCPU(0x071B + x, a);
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x18);
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x0708 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0704 + x, a);
        myMapper->writeCPU(0x070C + x, a);
        myMapper->writeCPU(0x0714 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0710 + x, a);
        myMapper->writeCPU(0x0718 + x, a);
        myMapper->writeCPU(0x0701 + x, 0xAF);
        a = 0xB0;
        myMapper->writeCPU(0x0705 + x, a);
        myMapper->writeCPU(0x0711 + x, a);
        myMapper->writeCPU(0x0709 + x, 0xB1);
        myMapper->writeCPU(0x070D + x, 0xB2);
        myMapper->writeCPU(0x0715 + x, 0xB3);
        myMapper->writeCPU(0x0719 + x, 0xB4);
        a = 0x03;
        myMapper->writeCPU(0x0702 + x, a);
        myMapper->writeCPU(0x0706 + x, a);
        myMapper->writeCPU(0x070A + x, a);
        myMapper->writeCPU(0x070E + x, a);
        myMapper->writeCPU(0x0712 + x, a);
        myMapper->writeCPU(0x0716 + x, a);
        myMapper->writeCPU(0x071A + x, a);
        a = x;
        flgC = false;
        opADC(0x1C);
        x = a;
        popAddress();
        return;
    }
    if (y == 0x03) {
        a = myMapper->readCPU(0x000D);
        flgC = true;
        opSBC(0x14);
        myMapper->writeCPU(0x0703 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0707 + x, a);
        myMapper->writeCPU(0x070B + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x070F + x, a);
        myMapper->writeCPU(0x0713 + x, a);
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x0704 + x, a);
        myMapper->writeCPU(0x070C + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0708 + x, a);
        myMapper->writeCPU(0x0710 + x, a);
        myMapper->writeCPU(0x0701 + x, 0xB5);
        myMapper->writeCPU(0x0705 + x, 0xB6);
        myMapper->writeCPU(0x0709 + x, 0xB7);
        myMapper->writeCPU(0x070D + x, 0xB8);
        myMapper->writeCPU(0x0711 + x, 0xB9);
        a = 0x03;
        myMapper->writeCPU(0x0702 + x, a);
        myMapper->writeCPU(0x0706 + x, a);
        myMapper->writeCPU(0x070A + x, a);
        myMapper->writeCPU(0x070E + x, a);
        myMapper->writeCPU(0x0712 + x, a);
        a = x;
        flgC = false;
        opADC(0x14);
        x = a;
        popAddress();
        return;
    }
    if (y == 0x04) {
        a = myMapper->readCPU(0x000D);
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(0x0703 + x, a);
        myMapper->writeCPU(0x0707 + x, a);
        myMapper->writeCPU(0x070B + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x070F + x, a);
        myMapper->writeCPU(0x0713 + x, a);
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x18);
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x070C + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0704 + x, a);
        myMapper->writeCPU(0x0710 + x, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0708 + x, a);
        myMapper->writeCPU(0x0701 + x, 0xAD);
        myMapper->writeCPU(0x0705 + x, 0xAE);
        myMapper->writeCPU(0x0709 + x, 0xAA);
        myMapper->writeCPU(0x070D + x, 0xAB);
        myMapper->writeCPU(0x0711 + x, 0xAC);
        a = 0x43;
        myMapper->writeCPU(0x0702 + x, a);
        myMapper->writeCPU(0x0706 + x, a);
        myMapper->writeCPU(0x070E + x, a);
        myMapper->writeCPU(0x0712 + x, a);
        myMapper->writeCPU(0x070A + x, 0x03);
        a = x;
        flgC = false;
        opADC(0x14);
        x = a;
        popAddress();
        return;
    }
    if (y != 0x05) {
        goto L_004443;
    }
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x0707 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070B + x, a);
    myMapper->writeCPU(0x070F + x, a);
    myMapper->writeCPU(0x0713 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0717 + x, a);
    myMapper->writeCPU(0x071B + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x18);
    myMapper->writeCPU(0x0708 + x, a);
    myMapper->writeCPU(0x0714 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x070C + x, a);
    myMapper->writeCPU(0x0718 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0704 + x, a);
    myMapper->writeCPU(0x0710 + x, a);
    myMapper->writeCPU(0x0701 + x, 0xB3);
    myMapper->writeCPU(0x0705 + x, 0xB4);
    myMapper->writeCPU(0x0709 + x, 0xB1);
    myMapper->writeCPU(0x070D + x, 0xB2);
    a = 0xB0;
    myMapper->writeCPU(0x0711 + x, a);
    myMapper->writeCPU(0x0719 + x, a);
    myMapper->writeCPU(0x0715 + x, 0xAF);
    a = 0x43;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    myMapper->writeCPU(0x0712 + x, a);
    myMapper->writeCPU(0x0716 + x, a);
    myMapper->writeCPU(0x071A + x, a);
    a = x;
    flgC = false;
    opADC(0x1C);
    x = a;
    popAddress();
    return;
L_004443:
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0703 + x, a);
    myMapper->writeCPU(0x0707 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070B + x, a);
    myMapper->writeCPU(0x070F + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0713 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0708 + x, a);
    myMapper->writeCPU(0x0710 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0704 + x, a);
    myMapper->writeCPU(0x070C + x, a);
    myMapper->writeCPU(0x0701 + x, 0xB8);
    myMapper->writeCPU(0x0705 + x, 0xB9);
    myMapper->writeCPU(0x0709 + x, 0xB6);
    myMapper->writeCPU(0x070D + x, 0xB7);
    myMapper->writeCPU(0x0711 + x, 0xB5);
    a = 0x43;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    myMapper->writeCPU(0x070A + x, a);
    myMapper->writeCPU(0x070E + x, a);
    myMapper->writeCPU(0x0712 + x, a);
    a = x;
    flgC = false;
    opADC(0x14);
    x = a;
    popAddress();
}

void game::SUB_0044A4() {
    a = myMapper->readCPU(0x000D);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0703 + x, a);
    a = myMapper->readCPU(0x000E);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0702 + x, 0x00);
    myMapper->writeCPU(0x0701 + x, myMapper->readCPU(0xC4C4 + y));
    opINX(4);
    popAddress();
}

void game::SUB_0044C7() {
    myMapper->writeCPU(0x0059, 0x00);
    a = myMapper->readCPU(0x0004);
    opASL_A(5);
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x005A, a);
    do {
        x = myMapper->readCPU(0x0058);
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0044EC;
        }
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x0005, myMapper->readCPU(0xC5AA + x));
        myMapper->writeCPU(0x0006, myMapper->readCPU(0xC5AB + x));
        pushAddress(0x0044E9);
        SUB_004591();
        if (poppedEntry.value != 0x0044E9) return;
    L_0044EC:
        a = myMapper->readCPU(0x0058);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0058, a);
    } while (a != myMapper->readCPU(0x005A));
    myMapper->writeCPU(0x0058, 0x00);
    do {
        x = myMapper->readCPU(0x0058);
        if (myMapper->readCPU(0x0400 + x) != 0) {
            opDEC(0x0400 + x, 1);
            if (flgZ) {
                goto L_00450A;
            }
            pushAddress(0x004507);
            SUB_004573();
            if (poppedEntry.value != 0x004507) return;
        }
    L_00450A:
        a = myMapper->readCPU(0x0058);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0058, a);
    } while (!flgZ);
    x = 0x00;
    y = 0x00;
    do {
        if (myMapper->readCPU(0x0400 + x) == 0) {
            goto L_004551;
        }
        myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0x0400 + x));
        myMapper->writeCPU(0x0301 + y, myMapper->readCPU(0x0401 + x));
        myMapper->writeCPU(0x0302 + y, myMapper->readCPU(0x0402 + x));
        myMapper->writeCPU(0x0303 + y, myMapper->readCPU(0x0403 + x));
        myMapper->writeCPU(0x0304 + y, myMapper->readCPU(0x0404 + x));
        myMapper->writeCPU(0x0305 + y, myMapper->readCPU(0x0405 + x));
        myMapper->writeCPU(0x0306 + y, myMapper->readCPU(0x0406 + x));
        myMapper->writeCPU(0x0307 + y, myMapper->readCPU(0x0407 + x));
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
    L_004551:
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        setLoadFlag(x);
    } while (!flgZ);
    myMapper->writeCPU(0x0003, y);
    a = 0x00;
    do {
        myMapper->writeCPU(0x0300 + y, a);
        opINY(1);
    } while (!flgZ);
    x = 0x00;
    do {
        myMapper->writeCPU(0x0400 + x, myMapper->readCPU(0x0300 + x));
        myMapper->writeCPU(0x0300 + x, 0x00);
        opINX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_004573() {
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0401 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0402 + x));
    a = myMapper->readCPU(0x0403 + x);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xC5A0 + x));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0xC5A1 + x));
    x = myMapper->readCPU(0x0058);
    indirectJump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_004591() {
    x = myMapper->readCPU(0x0058);
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0202 + x));
    indirectJump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_0045E4() {
    y = 0x01;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0045E8);
    SUB_0040B2();
    if (poppedEntry.value != 0x0045E8) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0045EE() {
    x = myMapper->readCPU(0x0058);
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0204 + x));
    opDEC(0x0013, 1);
    y = 0x00;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0045FB);
    SUB_0040B2();
    if (poppedEntry.value != 0x0045FB) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004601() {
    a = myMapper->readCPU(0x0004);
    opLSR_A(3);
    opAND(0x01);
    myMapper->writeCPU(0x0005, a);
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0203 + x);
    opLSR_A(6);
    opAND(0x02);
    opORA(myMapper->readCPU(0x0005));
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x00461C);
    SUB_0040FD();
    if (poppedEntry.value != 0x00461C) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004622() {
    y = 0x00;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004626);
    SUB_004149();
    if (poppedEntry.value != 0x004626) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_00462C() {
    x = myMapper->readCPU(0x0058);
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0200 + x));
    opDEC(0x0013, 1);
    y = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0205 + x);
    opAND(0x0F);
    if (!flgZ) {
        a = myMapper->readCPU(0x0205 + x);
        opAND(0x30);
        if (flgZ) {
            if (!(myMapper->readCPU(0x0205 + x) & 0x80)) {
                goto L_004674;
            }
            a = myMapper->readCPU(0x0207 + x);
            opAND(0x3F);
            if (!flgZ) {
                a = 0x04;
                goto L_0046D7;
            }
            y = myMapper->readCPU(0x0200 + x);
            opDEY(1);
            a = myMapper->readCPU(0x0046 + y);
            opLSR_A(1);
            opAND(0x02);
            if (!flgZ) {
                a = 0x01;
                goto L_0046D7;
            }
            a = myMapper->readCPU(0x0046 + y);
            opLSR_A(2);
            a = 0x02;
            opADC(0x00);
            goto L_0046D7;
        L_004674:
            a = myMapper->readCPU(0x0207 + x);
            opAND(0x3F);
            if (!flgZ) {
                a = 0x08;
                goto L_0046D7;
            }
            y = myMapper->readCPU(0x0200 + x);
            opDEY(1);
            a = myMapper->readCPU(0x0046 + y);
            opLSR_A(1);
            opAND(0x02);
            if (!flgZ) {
                a = 0x05;
                goto L_0046D7;
            }
            a = myMapper->readCPU(0x0046 + y);
            opLSR_A(2);
            a = 0x06;
            opADC(0x00);
            goto L_0046D7;
        }
    }
    a = myMapper->readCPU(0x0206 + x);
    setLoadFlag(a);
    if (!flgZ) {
        a = 0x10;
    }
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0205 + x);
    opAND(0xF0);
    if (flgN) {
        a = 0x0C;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0046C3;
        }
    }
    opASL_A(2);
    if (flgC) {
        a = 0x08;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0046C3;
        }
    }
    opASL_A(1);
    if (flgC) {
        goto L_0046C1;
    }
    a = 0x04;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0046C3;
    }
L_0046C1:
    a = 0x00;
L_0046C3:
    flgC = false;
    opADC(myMapper->readCPU(0x0007));
    myMapper->writeCPU(0x0007, a);
    y = myMapper->readCPU(0x0200 + x);
    opDEY(1);
    a = myMapper->readCPU(0x0044 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0007));
    y = a;
    a = myMapper->readCPU(0xC6E1 + y);
L_0046D7:
    y = a;
    opDEY(1);
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0046DB);
    SUB_003ABB();
    if (poppedEntry.value != 0x0046DB) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004701() {
    y = 0x00;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004705);
    SUB_004168();
    if (poppedEntry.value != 0x004705) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_00470B() {
    x = myMapper->readCPU(0x0058);
    if (myMapper->readCPU(0x0208 + x) == 0x04) {
        a = myMapper->readCPU(0x020C + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (flgN) {
                goto L_00471F;
            }
            y = 0x00;
            setLoadFlag(y);
            if (flgZ) {
                goto L_00472B;
            }
        }
    }
L_00471F:
    a = myMapper->readCPU(0x0004);
    opLSR_A(6);
    opAND(0x01);
    y = a;
    opINY(1);
L_00472B:
    x = myMapper->readCPU(0x0059);
    pushAddress(0x00472D);
    SUB_0041BC();
    if (poppedEntry.value != 0x00472D) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004733() {
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    opROL_A(2);
    opAND(0x01);
    opEOR(0x01);
    opASL_A(1);
    myMapper->writeCPU(0x0005, a);
    opASL_A(1);
    opORA(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0206 + x);
    setLoadFlag(a);
    if (!flgZ) {
        opLSR_A(1);
        opAND(0x01);
        opORA(0x04);
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
        y = a;
    }
    else {
        a = myMapper->readCPU(0x0204 + x);
        opAND(0x03);
        if (flgZ) {
            y = myMapper->readCPU(0x0005);
        }
        else {
            a = myMapper->readCPU(0x0204 + x);
            opAND(0x02);
            if (flgZ) {
                a = myMapper->readCPU(0x0004);
                opLSR_A(1);
            }
            else {
                a = myMapper->readCPU(0x0207 + x);
                opLSR_A(2);
                x = a;
                a = myMapper->readCPU(0xC7A8 + x);
                flgC = false;
                opADC(myMapper->readCPU(0x0005));
                y = a;
                goto L_0047A0;
            }
            opLSR_A(2);
            opAND(0x03);
            if (!flgZ) {
                if (a == 0x02) {
                    goto L_00479D;
                }
                if (a != 0x01) {
                    goto L_004795;
                }
                y = myMapper->readCPU(0x0005);
                opINY(2);
                goto L_0047A0;
            L_004795:
                y = myMapper->readCPU(0x0005);
                opINY(3);
                goto L_0047A0;
            }
        L_00479D:
            y = myMapper->readCPU(0x0005);
            opINY(1);
        }
    }
L_0047A0:
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0047A2);
    SUB_003B96();
    if (poppedEntry.value != 0x0047A2) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0047AD() {
    x = myMapper->readCPU(0x0058);
    if (!(myMapper->readCPU(0x0203 + x) & 0x80)) {
        goto L_0047BD;
    }
    a = myMapper->readCPU(0x0004);
    opLSR_A(2);
    opAND(0x03);
    goto L_0047CA;
L_0047BD:
    a = myMapper->readCPU(0x0004);
    opLSR_A(2);
    opAND(0x03);
    myMapper->writeCPU(0x0005, a);
    a = 0x03;
    flgC = true;
    opSBC(myMapper->readCPU(0x0005));
L_0047CA:
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0047CD);
    SUB_003DFD();
    if (poppedEntry.value != 0x0047CD) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0047D3() {
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0203 + x);
    opROL_A(3);
    opAND(0x02);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0004);
    opLSR_A(2);
    opAND(0x01);
    opORA(myMapper->readCPU(0x0005));
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0047EA);
    SUB_003C89();
    if (poppedEntry.value != 0x0047EA) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0047F0() {
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0203 + x);
    opAND(0x01);
    opEOR(0x01);
    opASL_A(1);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0205 + x);
    setLoadFlag(a);
    if (!flgZ) {
        a = 0x01;
    }
    opORA(myMapper->readCPU(0x0005));
    opASL_A(2);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0004);
    opAND(0x03);
    opORA(myMapper->readCPU(0x0005));
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004812);
    SUB_003D1B();
    if (poppedEntry.value != 0x004812) return;
    myMapper->writeCPU(0x0059, x);
    x = myMapper->readCPU(0x0058);
    if (myMapper->readCPU(0x0205 + x) != 0) {
        myMapper->writeCPU(0x000D, myMapper->readCPU(0x0201 + x));
        a = myMapper->readCPU(0x0206 + x);
        setLoadFlag(a);
        if (flgZ) {
            if (myMapper->readCPU(0x0205 + x) != 0x04) {
                goto L_00483A;
            }
            a = myMapper->readCPU(0x0202 + x);
            flgC = true;
            opSBC(0x0C);
            myMapper->writeCPU(0x000E, a);
            goto L_00485F;
        L_00483A:
            a = myMapper->readCPU(0x0202 + x);
            flgC = true;
            opSBC(0x10);
            myMapper->writeCPU(0x000E, a);
            goto L_00485F;
        }
        if (flgN) {
            a = myMapper->readCPU(0x0202 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0x0204 + x));
            myMapper->writeCPU(0x000E, a);
        }
        else {
            a = myMapper->readCPU(0x0202 + x);
            flgC = true;
            opSBC(0x0C);
            flgC = false;
            opADC(myMapper->readCPU(0x0204 + x));
            myMapper->writeCPU(0x000E, a);
        }
    L_00485F:
        if (myMapper->readCPU(0x0205 + x) != 0x04) {
            goto L_004870;
        }
        y = 0x00;
        x = myMapper->readCPU(0x0059);
        pushAddress(0x00486A);
        SUB_004168();
        if (poppedEntry.value != 0x00486A) return;
        myMapper->writeCPU(0x0059, x);
        popAddress();
        return;
    L_004870:
        a = myMapper->readCPU(0x0203 + x);
        flgC = false;
        opADC(0x10);
        y = a;
        x = myMapper->readCPU(0x0059);
        pushAddress(0x004879);
        SUB_003D1B();
        if (poppedEntry.value != 0x004879) return;
        myMapper->writeCPU(0x0059, x);
    }
    popAddress();
}

void game::SUB_00487F() {
    x = myMapper->readCPU(0x0058);
    if (!(myMapper->readCPU(0x0203 + x) & 0x80)) {
        goto L_00488E;
    }
    a = myMapper->readCPU(0x0004);
    opLSR_A(1);
    opAND(0x07);
    goto L_00489A;
L_00488E:
    a = myMapper->readCPU(0x0004);
    opLSR_A(1);
    opAND(0x07);
    myMapper->writeCPU(0x0005, a);
    a = 0x07;
    flgC = true;
    opSBC(myMapper->readCPU(0x0005));
L_00489A:
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x00489D);
    SUB_003D9C();
    if (poppedEntry.value != 0x00489D) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0048A3() {
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0048AC;
    }
    a = 0x01;
L_0048AC:
    flgC = false;
    opADC(0x10);
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0048B2);
    SUB_003D1B();
    if (poppedEntry.value != 0x0048B2) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0048B8() {
    x = myMapper->readCPU(0x0058);
    a = myMapper->readCPU(0x0204 + x);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0004);
        opLSR_A(2);
        opAND(0x01);
    }
    else {
        if (a < 0x0A) {
            goto L_0048D0;
        }
        a = 0x02;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0048D2;
        }
    L_0048D0:
        a = 0x03;
    }
L_0048D2:
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0205 + x);
    opLSR_A(5);
    opAND(0x04);
    opORA(myMapper->readCPU(0x0005));
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0048E3);
    SUB_003E5D();
    if (poppedEntry.value != 0x0048E3) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0048E9() {
    a = myMapper->readCPU(0x0004);
    opLSR_A(3);
    opAND(0x01);
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x0048F3);
    SUB_003EDF();
    if (poppedEntry.value != 0x0048F3) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_0048F9() {
    a = myMapper->readCPU(0x0004);
    opLSR_A(2);
    opAND(0x03);
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004902);
    SUB_003E9B();
    if (poppedEntry.value != 0x004902) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004908() {
    a = myMapper->readCPU(0x0004);
    opLSR_A(2);
    opAND(0x03);
    opORA(0x04);
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004913);
    SUB_003E9B();
    if (poppedEntry.value != 0x004913) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004919() {
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x0204 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x0205 + x));
    y = myMapper->readCPU(0x0203 + x);
    y = myMapper->readCPU(0xC932 + y);
    x = myMapper->readCPU(0x0059);
    pushAddress(0x00492C);
    SUB_0041C8();
    if (poppedEntry.value != 0x00492C) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_00493E() {
    x = myMapper->readCPU(0x0058);
    if (!(myMapper->readCPU(0x0203 + x) & 0x80)) {
        goto L_00494F;
    }
    a = myMapper->readCPU(0x0004);
    opLSR_A(3);
    opAND(0x03);
    goto L_00495D;
L_00494F:
    a = myMapper->readCPU(0x0004);
    opLSR_A(3);
    opAND(0x03);
    myMapper->writeCPU(0x0005, a);
    a = 0x03;
    flgC = true;
    opSBC(myMapper->readCPU(0x0005));
L_00495D:
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004960);
    SUB_003F2B();
    if (poppedEntry.value != 0x004960) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004966() {
    x = myMapper->readCPU(0x0058);
    x = myMapper->readCPU(0x0204 + x);
    a = myMapper->readCPU((0x0084 + x) & 0x00ff);
    opLSR_A(4);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU((0x0084 + x) & 0x00ff);
    opASL_A(4);
    opORA(myMapper->readCPU(0x0005));
    x = a;
    y = myMapper->readCPU(0xC989 + x);
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004983);
    SUB_003C1E();
    if (poppedEntry.value != 0x004983) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004A89() {
    a = myMapper->readCPU(0x0004);
    opAND(0x03);
    if (a != 0x03) {
        goto L_004A93;
    }
    a = 0x02;
L_004A93:
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004A96);
    SUB_0044A4();
    if (poppedEntry.value != 0x004A96) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004A9C() {
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x0404 + x));
    a = myMapper->readCPU(0x0004);
    opAND(0x03);
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004AA8);
    SUB_00403D();
    if (poppedEntry.value != 0x004AA8) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004AAE() {
    a = 0x17;
    flgC = true;
    opSBC(myMapper->readCPU(0x0400 + x));
    opLSR_A(3);
    y = a;
    opINY(1);
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004ABB);
    SUB_004149();
    if (poppedEntry.value != 0x004ABB) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004AC1() {
    a = 0x03;
    flgC = true;
    opSBC(myMapper->readCPU(0x0400 + x));
    y = a;
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004ACA);
    SUB_003F77();
    if (poppedEntry.value != 0x004ACA) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004AD0() {
    y = myMapper->readCPU(0x0404 + x);
    x = myMapper->readCPU(0x0059);
    pushAddress(0x004AD5);
    SUB_00408F();
    if (poppedEntry.value != 0x004AD5) return;
    myMapper->writeCPU(0x0059, x);
    popAddress();
}

void game::SUB_004ADB() {
    x = myMapper->readCPU(0x0059);
    x = myMapper->readCPU(0x0203 + x);
    myMapper->writeCPU(0x0078, myMapper->readCPU(0xCAF4 + x));
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0203 + x);
    opORA(myMapper->readCPU(0x0204 + x));
    if (!flgZ) {
        goto L_004AF3;
    }
    myMapper->writeCPU(0x0200 + x, a);
L_004AF3:
    popAddress();
}

void game::SUB_004AFA() {
    x = myMapper->readCPU(0x0059);
    x = myMapper->readCPU(0x0203 + x);
    a = myMapper->readCPU(0xCB18 + x);
    opPHA();
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0205 + x);
    x = a;
    opPLA();
    myMapper->writeCPU((0x0078 + x) & 0x00ff, a);
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_004B17;
    }
    myMapper->writeCPU(0x0200 + x, a);
L_004B17:
    popAddress();
}

void game::SUB_004B22() {
    if (myMapper->readCPU(0x0023) == 0x10) {
        goto L_004B5C;
    }
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0205 + x);
    opASL_A(1);
    opADC(myMapper->readCPU(0x0205 + x));
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU(0x0205 + x);
    opASL_A(3);
    myMapper->writeCPU(0x0005, a);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0005));
    flgC = false;
    opADC(myMapper->readCPU(0x0203 + x));
    x = a;
    a = myMapper->readCPU(0xCB81 + x);
    opPHA();
    a = myMapper->readCPU(0xCB89 + x);
    opPHA();
    a = myMapper->readCPU(0xCB91 + x);
    x = myMapper->readCPU(0x0006);
    myMapper->writeCPU((0x007A + x) & 0x00ff, a);
    opPLA();
    myMapper->writeCPU((0x0079 + x) & 0x00ff, a);
    opPLA();
    myMapper->writeCPU((0x0078 + x) & 0x00ff, a);
    goto L_004B76;
L_004B5C:
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0205 + x);
    opASL_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0203 + x));
    x = a;
    a = myMapper->readCPU(0xCBE1 + x);
    opPHA();
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0205 + x);
    x = a;
    opPLA();
    myMapper->writeCPU((0x0078 + x) & 0x00ff, a);
L_004B76:
    x = myMapper->readCPU(0x0059);
    a = myMapper->readCPU(0x0203 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_004B80;
    }
    myMapper->writeCPU(0x0200 + x, a);
L_004B80:
    popAddress();
}

void game::SUB_004C21() {
    myMapper->writeCPU(0x0023, 0x00);
    pushAddress(0x004C25);
    SUB_006A1B();
    if (poppedEntry.value != 0x004C25) return;
    myMapper->writeCPU(0x0009, 0x60);
    myMapper->writeCPU(0x000A, 0x02);
    SUB_004C40();
    return;
}

void game::SUB_004C33() {
    myMapper->writeCPU(0x0023, 0x00);
    pushAddress(0x004C37);
    SUB_006A1B();
    if (poppedEntry.value != 0x004C37) return;
    a = 0x00;
    myMapper->writeCPU(0x0009, a);
    myMapper->writeCPU(0x000A, a);
    SUB_004C40();
    return;
}

void game::SUB_004C40() {
    pushAddress(0x004C40);
    SUB_007A7B();
    if (poppedEntry.value != 0x004C40) return;
    myMapper->writeCPU(0x0055, 0x00);
    a = 0x04;
    myMapper->writeCPU(0x0007, a);
    myMapper->writeCPU(0x0008, a);
    myMapper->writeCPU(0x005D, 0x00);
    myMapper->writeCPU(0x4015, 0x0F);
    pushAddress(0x004C56);
    SUB_00610C();
    if (poppedEntry.value != 0x004C56) return;
    pushAddress(0x004C59);
    SUB_006D27();
    if (poppedEntry.value != 0x004C59) return;
    if (myMapper->readCPU(0x0022) != 0) {
    }
    else {
        myMapper->writeCPU(0x0055, 0xFF);
        myMapper->writeCPU(0x0023, 0x01);
        myMapper->writeCPU(0x2001, 0x00);
        pushAddress(0x004C70);
        SUB_0077B1();
        if (poppedEntry.value != 0x004C70) return;
        myMapper->writeCPU(0x2001, 0x1E);
        pushAddress(0x004C78);
        SUB_007A7B();
        if (poppedEntry.value != 0x004C78) return;
        a = 0x04;
        myMapper->writeCPU(0x0015, a);
        myMapper->writeCPU(0x0016, a);
        x = 0x00;
        do {
            a = 0x00;
            myMapper->writeCPU(0x0300 + x, a);
            myMapper->writeCPU(0x0400 + x, a);
            myMapper->writeCPU(0x0200 + x, a);
            myMapper->writeCPU(0x0500 + x, a);
            opDEX(1);
        } while (!flgZ);
        x = 0x47;
        do {
            myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0xD761 + x));
            opDEX(1);
        } while (!flgN);
        x = 0x17;
        do {
            myMapper->writeCPU(0x0500 + x, myMapper->readCPU(0xD7A9 + x));
            opDEX(1);
        } while (!flgN);
        a = 0xE6;
        x = 0x1F;
        do {
            myMapper->writeCPU((0x008F + x) & 0x00ff, a);
            opDEX(1);
        } while (!flgN);
        myMapper->writeCPU(0x0021, 0x01);
        do {
        L_004CB7:
            if (myMapper->readCPU(0x0021) != 0) {
                wait(1);
                goto L_004CB7;
            }
            myMapper->writeCPU(0x0021, 0x02);
            pushAddress(0x004CBF);
            SUB_00012A();
            if (poppedEntry.value != 0x004CBF) return;
            pushAddress(0x004CC2);
            SUB_00392D();
            if (poppedEntry.value != 0x004CC2) return;
            pushAddress(0x004CC5);
            SUB_006681();
            if (poppedEntry.value != 0x004CC5) return;
            pushAddress(0x004CC8);
            SUB_006681();
            if (poppedEntry.value != 0x004CC8) return;
            pushAddress(0x004CCB);
            SUB_002C7F();
            if (poppedEntry.value != 0x004CCB) return;
            pushAddress(0x004CCE);
            SUB_007A7B();
            if (poppedEntry.value != 0x004CCE) return;
            pushAddress(0x004CD1);
            SUB_0044C7();
            if (poppedEntry.value != 0x004CD1) return;
            if (myMapper->readCPU(0x0015) == 0) {
                opDEC(0x0016, 1);
            }
            opDEC(0x0015, 1);
            pushAddress(0x004CDC);
            SUB_0057C5();
            if (poppedEntry.value != 0x004CDC) return;
            opAND(0x0C);
            if (flgZ) {
                goto L_004CE6;
            }
            SUB_004C33();
            return;
        L_004CE6:
            a = myMapper->readCPU(0x0015);
            opORA(myMapper->readCPU(0x0016));
        } while (!flgZ);
        pushAddress(0x004CEC);
        SUB_007A7B();
        if (poppedEntry.value != 0x004CEC) return;
        SUB_004C21();
        return;
    }
    a = 0xE6;
    x = 0x1F;
    do {
        myMapper->writeCPU((0x008F + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    pushAddress(0x004CFB);
    SUB_007A7B();
    if (poppedEntry.value != 0x004CFB) return;
    myMapper->writeCPU(0x4015, 0x0F);
    a = 0x3C;
    myMapper->writeCPU(0x004C, a);
    myMapper->writeCPU(0x004D, a);
    a = 0x14;
    myMapper->writeCPU(0x0050, a);
    myMapper->writeCPU(0x0051, a);
    a = 0x00;
    myMapper->writeCPU(0x004E, a);
    myMapper->writeCPU(0x004F, a);
    myMapper->writeCPU(0x005B, a);
    myMapper->writeCPU(0x004A, a);
    myMapper->writeCPU(0x004B, a);
    myMapper->writeCPU(0x0054, a);
    myMapper->writeCPU(0x0053, a);
    myMapper->writeCPU(0x003C, a);
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x003E, a);
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x0040, a);
    myMapper->writeCPU(0x0041, a);
    myMapper->writeCPU(0x0042, a);
    myMapper->writeCPU(0x0043, a);
    myMapper->writeCPU(0x003D, 0x05);
    if (myMapper->readCPU(0x0022) != 0x02) {
        goto L_004D3F;
    }
    a = 0x05;
    myMapper->writeCPU(0x0041, a);
    myMapper->writeCPU(0x005B, a);
L_004D3F:
    x = 0x10;
    a = 0x00;
    do {
        myMapper->writeCPU((0x0024 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0023, 0x01);
    SUB_004D4C();
    return;
}

void game::SUB_004D4C() {
    while (true) {
        pushAddress(0x004D4C);
        SUB_006EA2();
        if (poppedEntry.value != 0x004D4C) return;
        pushAddress(0x004D4F);
        SUB_007A7B();
        if (poppedEntry.value != 0x004D4F) return;
        x = myMapper->readCPU(0x0023);
        myMapper->writeCPU(0x001F, myMapper->readCPU(0xCF9A + x));
        a = 0x00;
        x = a;
        do {
            myMapper->writeCPU(0x0200 + x, a);
            myMapper->writeCPU(0x0300 + x, a);
            myMapper->writeCPU(0x0500 + x, a);
            myMapper->writeCPU(0x0400 + x, a);
            opINX(1);
        } while (!flgZ);
        a = myMapper->readCPU(0x0023);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x0005, myMapper->readCPU(0xCFB9 + x));
        myMapper->writeCPU(0x0006, myMapper->readCPU(0xCFBA + x));
        y = 0x00;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_004DAF;
            }
            myMapper->writeCPU(0x0200 + y, a);
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
        } while (!flgZ);
    L_004DAF:
        a = myMapper->readCPU(0x0023);
        opASL_A(1);
        myMapper->writeCPU(0x0005, myMapper->readCPU(0xCFD9 + x));
        myMapper->writeCPU(0x0006, myMapper->readCPU(0xCFDA + x));
        y = 0x00;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_004DF2;
            }
            myMapper->writeCPU(0x0500 + y, a);
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0500 + y, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
        } while (!flgZ);
    L_004DF2:
        a = myMapper->readCPU(0x003C);
        opORA(myMapper->readCPU(0x003D));
        opORA(myMapper->readCPU(0x003E));
        opORA(myMapper->readCPU(0x003F));
        if (flgZ) {
            myMapper->writeCPU(0x0200, a);
        }
        a = myMapper->readCPU(0x0040);
        opORA(myMapper->readCPU(0x0041));
        opORA(myMapper->readCPU(0x0042));
        opORA(myMapper->readCPU(0x0043));
        if (!flgZ) {
            goto L_004E0C;
        }
        myMapper->writeCPU(0x0208, a);
    L_004E0C:
        a = 0x00;
        myMapper->writeCPU(0x004A, a);
        myMapper->writeCPU(0x004B, a);
        myMapper->writeCPU(0x0076, 0x30);
        myMapper->writeCPU(0x0077, 0xFF);
        x = myMapper->readCPU(0x0023);
        myMapper->writeCPU(0x005D, myMapper->readCPU(0xCFAA + x));
        pushAddress(0x004E21);
        SUB_00610C();
        if (poppedEntry.value != 0x004E21) return;
        a = myMapper->readCPU(0x0023);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x0076, myMapper->readCPU(0xD67F + x));
        myMapper->writeCPU(0x0077, myMapper->readCPU(0xD680 + x));
        a = myMapper->readCPU(0x0023);
        flgC = true;
        opSBC(0x01);
        opASL_A(2);
        myMapper->writeCPU(0x0005, a);
        opASL_A(1);
        flgC = false;
        opADC(myMapper->readCPU(0x0005));
        x = a;
        y = 0x00;
        do {
            myMapper->writeCPU(0x0078 + y, myMapper->readCPU(0xD6A1 + x));
            opINX(1);
            opINY(1);
        } while (y != 0x0C);
        myMapper->writeCPU(0x2001, 0x00);
        pushAddress(0x004E53);
        SUB_0077B1();
        if (poppedEntry.value != 0x004E53) return;
        myMapper->writeCPU(0x2001, 0x1E);
        pushAddress(0x004E5B);
        SUB_007A7B();
        if (poppedEntry.value != 0x004E5B) return;
        myMapper->writeCPU(0x0021, 0x01);
    L_004E62:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_004E62;
        }
        myMapper->writeCPU(0x0020, 0x3C);
        myMapper->writeCPU(0x0021, 0x1E);
        do {
        L_004E6E:
            if (myMapper->readCPU(0x0021) != 0) {
                wait(1);
                goto L_004E6E;
            }
            myMapper->writeCPU(0x0021, 0x02);
            pushAddress(0x004E76);
            SUB_00012A();
            if (poppedEntry.value != 0x004E76) return;
            pushAddress(0x004E79);
            SUB_001C9E();
            if (poppedEntry.value != 0x004E79) return;
            pushAddress(0x004E7C);
            SUB_00392D();
            if (poppedEntry.value != 0x004E7C) return;
            pushAddress(0x004E7F);
            SUB_007A94();
            if (poppedEntry.value != 0x004E7F) return;
            pushAddress(0x004E82);
            SUB_00611E();
            if (poppedEntry.value != 0x004E82) return;
            pushAddress(0x004E85);
            SUB_006681();
            if (poppedEntry.value != 0x004E85) return;
            pushAddress(0x004E88);
            SUB_007A7B();
            if (poppedEntry.value != 0x004E88) return;
            pushAddress(0x004E8B);
            SUB_0044C7();
            if (poppedEntry.value != 0x004E8B) return;
            pushAddress(0x004E8E);
            SUB_002C7F();
            if (poppedEntry.value != 0x004E8E) return;
            pushAddress(0x004E91);
            SUB_00611E();
            if (poppedEntry.value != 0x004E91) return;
            pushAddress(0x004E94);
            SUB_006681();
            if (poppedEntry.value != 0x004E94) return;
            a = myMapper->readCPU(0x003C);
            opORA(myMapper->readCPU(0x003D));
            opORA(myMapper->readCPU(0x003E));
            opORA(myMapper->readCPU(0x003F));
            opORA(myMapper->readCPU(0x0040));
            opORA(myMapper->readCPU(0x0041));
            opORA(myMapper->readCPU(0x0042));
            opORA(myMapper->readCPU(0x0043));
            if (flgZ) {
                myMapper->writeCPU(0x001F, a);
                myMapper->writeCPU(0x0054, 0xFF);
            }
            pushAddress(0x004EAF);
            SUB_0057C5();
            if (poppedEntry.value != 0x004EAF) return;
            opAND(0x08);
            if (flgZ) {
                goto L_004EB9;
            }
            pushAddress(0x004EB6);
            SUB_004F4C();
            if (poppedEntry.value != 0x004EB6) return;
        L_004EB9:
            if (myMapper->readCPU(0x001F) != 0) {
                goto L_004E6E;
            }
            opDEC(0x0020, 1);
        } while (!flgZ);
        myMapper->writeCPU(0x0021, 0x78);
    L_004EC5:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_004EC5;
        }
        a = 0x00;
        myMapper->writeCPU(0x006A, a);
        myMapper->writeCPU(0x006B, a);
        myMapper->writeCPU(0x006C, a);
        myMapper->writeCPU(0x006D, a);
        if (myMapper->readCPU(0x0054) != 0) {
            goto L_004F0C;
        }
        myMapper->writeCPU(0x0076, 0x30);
        myMapper->writeCPU(0x0077, 0xFF);
        a = 0x00;
        myMapper->writeCPU(0x4000, a);
        myMapper->writeCPU(0x4004, a);
        myMapper->writeCPU(0x4008, a);
        myMapper->writeCPU(0x400C, 0x40);
        pushAddress(0x004EEF);
        SUB_007A7B();
        if (poppedEntry.value != 0x004EEF) return;
        a = 0x00;
        x = a;
        do {
            myMapper->writeCPU(0x0500 + x, a);
            myMapper->writeCPU(0x0400 + x, a);
            opINX(1);
        } while (!flgZ);
        opINC(0x0023, 1);
        if (myMapper->readCPU(0x0023) >= 0x11) {
            goto L_004F09;
        }
    }
L_004F09:
    SUB_004F88();
    return;
L_004F0C:
    myMapper->writeCPU(0x0053, 0xFF);
    pushAddress(0x004F10);
    SUB_007A7B();
    if (poppedEntry.value != 0x004F10) return;
    pushAddress(0x004F13);
    SUB_00775A();
    if (poppedEntry.value != 0x004F13) return;
    myMapper->writeCPU(0x005D, 0x00);
    pushAddress(0x004F1A);
    SUB_00610C();
    if (poppedEntry.value != 0x004F1A) return;
    myMapper->writeCPU(0x0007, 0xE0);
    myMapper->writeCPU(0x0008, 0x05);
    do {
    L_004F25:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_004F25;
        }
        opINC(0x0021, 1);
        pushAddress(0x004F2B);
        SUB_00611E();
        if (poppedEntry.value != 0x004F2B) return;
        if (myMapper->readCPU(0x0007) != 0) {
            goto L_004F34;
        }
        opDEC(0x0008, 1);
    L_004F34:
        opDEC(0x0007, 1);
        pushAddress(0x004F36);
        SUB_0057C5();
        if (poppedEntry.value != 0x004F36) return;
        opAND(0x0C);
        if (!flgZ) {
            goto L_004F43;
        }
        a = myMapper->readCPU(0x0007);
        opORA(myMapper->readCPU(0x0008));
    } while (!flgZ);
L_004F43:
    a = 0x00;
    myMapper->writeCPU(0x0053, a);
    myMapper->writeCPU(0x0054, a);
    SUB_004C33();
    return;
}

void game::SUB_004F4C() {
    do {
        myMapper->writeCPU(0x2001, 0x1E);
        pushAddress(0x004F51);
        SUB_0057C5();
        if (poppedEntry.value != 0x004F51) return;
        opAND(0x08);
    } while (!flgZ);
    myMapper->writeCPU(0x005D, 0x07);
    pushAddress(0x004F5C);
    SUB_00610C();
    if (poppedEntry.value != 0x004F5C) return;
    do {
    L_004F5F:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_004F5F;
        }
        opINC(0x0021, 1);
        pushAddress(0x004F65);
        SUB_00611E();
        if (poppedEntry.value != 0x004F65) return;
        a = 0x00;
        pushAddress(0x004F6A);
        SUB_0057C5();
        if (poppedEntry.value != 0x004F6A) return;
        opAND(0x08);
    } while (flgZ);
    do {
        pushAddress(0x004F71);
        SUB_0057C5();
        if (poppedEntry.value != 0x004F71) return;
        opAND(0x08);
    } while (!flgZ);
    x = myMapper->readCPU(0x0023);
    myMapper->writeCPU(0x005D, myMapper->readCPU(0xCFAA + x));
    pushAddress(0x004F7F);
    SUB_00610C();
    if (poppedEntry.value != 0x004F7F) return;
    myMapper->writeCPU(0x2001, 0x1E);
    popAddress();
}

void game::SUB_004F88() {
    pushAddress(0x004F88);
    SUB_007187();
    if (poppedEntry.value != 0x004F88) return;
    myMapper->writeCPU(0x0023, 0x01);
    SUB_004D4C();
    return;
}

void game::SUB_0057C1() {
    opORA(0x00);
    if (!flgZ) {
        SUB_0057DE();
        return;
    }
    SUB_0057C5();
    return;
}

void game::SUB_0057C5() {
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    x = 0x08;
    do {
        a = myMapper->readCPU(0x4016);
        opLSR_A(1);
        if (flgC) {
            goto L_0057D7;
        }
        opLSR_A(1);
    L_0057D7:
        opROR_M(0x0005, 1);
        opDEX(1);
    } while (!flgZ);
    if (flgZ) {
        SUB_0057F5();
        return;
    }
    SUB_0057DE();
    return;
}

void game::SUB_0057DE() {
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    x = 0x08;
    do {
        a = myMapper->readCPU(0x4017);
        opLSR_A(1);
        if (flgC) {
            goto L_0057F0;
        }
        opLSR_A(1);
    L_0057F0:
        opROR_M(0x0005, 1);
        opDEX(1);
    } while (!flgZ);
    SUB_0057F5();
    return;
}

void game::SUB_0057F5() {
    a = myMapper->readCPU(0x0005);
    opAND(0x3F);
    myMapper->writeCPU(0x0014, a);
    a = myMapper->readCPU(0x0005);
    opAND(0x80);
    opLSR_A(1);
    myMapper->writeCPU(0x0013, a);
    a = myMapper->readCPU(0x0005);
    opAND(0x40);
    opASL_A(1);
    opORA(myMapper->readCPU(0x0013));
    opORA(myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x0005, a);
    opAND(0xC0);
    if (!flgZ) {
        goto L_005814;
    }
    a = myMapper->readCPU(0x0005);
    popAddress();
    return;
L_005814:
    a = 0xCF;
    opAND(myMapper->readCPU(0x0005));
    popAddress();
}

void game::SUB_005819() {
    x = myMapper->readCPU(0x005D);
    myMapper->writeCPU(0x4000, myMapper->readCPU(0xD849 + x));
    myMapper->writeCPU(0x4001, myMapper->readCPU(0xD851 + x));
    popAddress();
}

void game::SUB_005828() {
    x = myMapper->readCPU(0x005D);
    myMapper->writeCPU(0x4004, myMapper->readCPU(0xD859 + x));
    myMapper->writeCPU(0x4005, myMapper->readCPU(0xD861 + x));
    popAddress();
}

void game::SUB_005837() {
    x = myMapper->readCPU(0x005D);
    myMapper->writeCPU(0x4008, myMapper->readCPU(0xD869 + x));
    popAddress();
}

void game::SUB_005840() {
    x = myMapper->readCPU(0x005D);
    myMapper->writeCPU(0x400C, myMapper->readCPU(0xD871 + x));
    popAddress();
}

void game::SUB_005879() {
    a = myMapper->readCPU(0x005D);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x005E, myMapper->readCPU(0xD8A6 + x));
    myMapper->writeCPU(0x005F, myMapper->readCPU(0xD8A7 + x));
    myMapper->writeCPU(0x0060, myMapper->readCPU(0xD8B6 + x));
    myMapper->writeCPU(0x0061, myMapper->readCPU(0xD8B7 + x));
    myMapper->writeCPU(0x0062, myMapper->readCPU(0xD8C6 + x));
    myMapper->writeCPU(0x0063, myMapper->readCPU(0xD8C7 + x));
    myMapper->writeCPU(0x0064, myMapper->readCPU(0xD8D6 + x));
    myMapper->writeCPU(0x0065, myMapper->readCPU(0xD8D7 + x));
    popAddress();
}

void game::SUB_00610C() {
    a = 0x01;
    myMapper->writeCPU(0x0066, a);
    myMapper->writeCPU(0x0067, a);
    myMapper->writeCPU(0x0068, a);
    myMapper->writeCPU(0x0069, a);
    myMapper->writeCPU(0x005C, a);
    pushAddress(0x006118);
    SUB_005879();
    if (poppedEntry.value != 0x006118) return;
    SUB_006219();
    return;
}

void game::SUB_00611E() {
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (!flgZ) {
        opDEC(0x0066, 1);
        if (flgZ) {
            a = myMapper->readCPU(0x005E);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x005E, a);
            a = myMapper->readCPU(0x005F);
            opADC(0x00);
            myMapper->writeCPU(0x005F, a);
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                SUB_00610C();
                return;
            }
            y = 0x01;
            a = myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y);
            pushAddress(0x006145);
            SUB_00627B();
            if (poppedEntry.value != 0x006145) return;
            myMapper->writeCPU(0x0066, a);
            if (myMapper->readCPU(0x005C) == 0) {
                opDEY(1);
                myMapper->writeCPU(0x4002, myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y));
                opINY(1);
                myMapper->writeCPU(0x4003, myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y));
            }
        }
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (!flgZ) {
        opDEC(0x0067, 1);
        if (flgZ) {
            a = myMapper->readCPU(0x0060);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x0060, a);
            a = myMapper->readCPU(0x0061);
            opADC(0x00);
            myMapper->writeCPU(0x0061, a);
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                SUB_00610C();
                return;
            }
            y = 0x01;
            a = myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y);
            pushAddress(0x006181);
            SUB_00627B();
            if (poppedEntry.value != 0x006181) return;
            myMapper->writeCPU(0x0067, a);
            if (myMapper->readCPU(0x005C) == 0) {
                opDEY(1);
                myMapper->writeCPU(0x4006, myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y));
                opINY(1);
                myMapper->writeCPU(0x4007, myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y));
            }
        }
    }
    a = myMapper->readCPU(0x0062);
    opORA(myMapper->readCPU(0x0063));
    if (!flgZ) {
        opDEC(0x0068, 1);
        if (flgZ) {
            a = myMapper->readCPU(0x0062);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x0062, a);
            a = myMapper->readCPU(0x0063);
            opADC(0x00);
            myMapper->writeCPU(0x0063, a);
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                SUB_00610C();
                return;
            }
            y = 0x01;
            a = myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y);
            pushAddress(0x0061BD);
            SUB_00627B();
            if (poppedEntry.value != 0x0061BD) return;
            myMapper->writeCPU(0x0068, a);
            if (myMapper->readCPU(0x005C) == 0) {
                opDEY(1);
                myMapper->writeCPU(0x400A, myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y));
                opINY(1);
                myMapper->writeCPU(0x400B, myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y));
            }
        }
    }
    a = myMapper->readCPU(0x0064);
    opORA(myMapper->readCPU(0x0065));
    if (!flgZ) {
        opDEC(0x0069, 1);
        if (flgZ) {
            a = myMapper->readCPU(0x0064);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x0064, a);
            a = myMapper->readCPU(0x0065);
            opADC(0x00);
            myMapper->writeCPU(0x0065, a);
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opORA(myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                pushAddress(0x0061F2);
                SUB_00610C();
                if (poppedEntry.value != 0x0061F2) return;
            }
            y = 0x01;
            a = myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y);
            pushAddress(0x0061F9);
            SUB_00627B();
            if (poppedEntry.value != 0x0061F9) return;
            myMapper->writeCPU(0x0069, a);
            if (myMapper->readCPU(0x005C) != 0) {
                goto L_00620E;
            }
            opDEY(1);
            myMapper->writeCPU(0x400E, myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x400F, myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y));
        }
    }
L_00620E:
    popAddress();
}

void game::SUB_00620F() {
    if (myMapper->readCPU(0x005C) == 0) {
        goto L_006214;
    }
    popAddress();
    return;
L_006214:
    myMapper->writeCPU(0x005C, 0xFF);
    popAddress();
}

void game::SUB_006219() {
    if (myMapper->readCPU(0x005C) != 0) {
        goto L_00621E;
    }
    popAddress();
    return;
L_00621E:
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (!flgZ) {
        pushAddress(0x006224);
        SUB_005819();
        if (poppedEntry.value != 0x006224) return;
        y = 0x01;
        myMapper->writeCPU(0x4002, myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x4003, myMapper->readCPU(myMapper->readCPU(0x005E) + (myMapper->readCPU((0x005E + 1) & 0x00ff) << 8) + y));
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (!flgZ) {
        pushAddress(0x00623A);
        SUB_005828();
        if (poppedEntry.value != 0x00623A) return;
        y = 0x01;
        myMapper->writeCPU(0x4006, myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x4007, myMapper->readCPU(myMapper->readCPU(0x0060) + (myMapper->readCPU((0x0060 + 1) & 0x00ff) << 8) + y));
    }
    a = myMapper->readCPU(0x0062);
    opORA(myMapper->readCPU(0x0063));
    if (!flgZ) {
        pushAddress(0x006250);
        SUB_005837();
        if (poppedEntry.value != 0x006250) return;
        y = 0x01;
        myMapper->writeCPU(0x400A, myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x400B, myMapper->readCPU(myMapper->readCPU(0x0062) + (myMapper->readCPU((0x0062 + 1) & 0x00ff) << 8) + y));
    }
    a = myMapper->readCPU(0x0064);
    opORA(myMapper->readCPU(0x0065));
    if (flgZ) {
        goto L_006276;
    }
    pushAddress(0x006266);
    SUB_005840();
    if (poppedEntry.value != 0x006266) return;
    y = 0x01;
    myMapper->writeCPU(0x400E, myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x400F, myMapper->readCPU(myMapper->readCPU(0x0064) + (myMapper->readCPU((0x0064 + 1) & 0x00ff) << 8) + y));
L_006276:
    myMapper->writeCPU(0x005C, 0x00);
    popAddress();
}

void game::SUB_00627B() {
    opLSR_A(3);
    x = a;
    a = myMapper->readCPU(0xE283 + x);
    popAddress();
}

void game::SUB_0062A3() {
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (flgZ) {
        goto L_0062AC;
    }
    pushAddress(0x0062A9);
    SUB_00620F();
    if (poppedEntry.value != 0x0062A9) return;
L_0062AC:
    myMapper->writeCPU(0x006A, 0x01);
    myMapper->writeCPU(0x4000, 0x85);
    myMapper->writeCPU(0x4001, 0x83);
    myMapper->writeCPU(0x4002, 0x28);
    myMapper->writeCPU(0x4003, 0xA0);
    myMapper->writeCPU(0x006E, 0x18);
    popAddress();
}

void game::SUB_0062C9() {
    opCMP(0x02, myMapper->readCPU(0x006D));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0064);
    opORA(myMapper->readCPU(0x0065));
    if (flgZ) {
        goto L_0062D9;
    }
    pushAddress(0x0062D6);
    SUB_00620F();
    if (poppedEntry.value != 0x0062D6) return;
L_0062D9:
    myMapper->writeCPU(0x006D, 0x02);
    myMapper->writeCPU(0x400C, 0x07);
    myMapper->writeCPU(0x400E, 0x08);
    myMapper->writeCPU(0x400F, 0xD0);
    myMapper->writeCPU(0x0071, 0x24);
    popAddress();
}

void game::SUB_0062F1() {
    opCMP(0x03, myMapper->readCPU(0x006A));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    opORA(myMapper->readCPU(0x0060));
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_006305;
    }
    pushAddress(0x006302);
    SUB_00620F();
    if (poppedEntry.value != 0x006302) return;
L_006305:
    a = 0x03;
    myMapper->writeCPU(0x006A, a);
    myMapper->writeCPU(0x006B, a);
    myMapper->writeCPU(0x4000, 0xBF);
    myMapper->writeCPU(0x4001, 0x87);
    a = 0x00;
    myMapper->writeCPU(0x4002, a);
    myMapper->writeCPU(0x4006, a);
    myMapper->writeCPU(0x4004, 0x8C);
    a = 0x87;
    myMapper->writeCPU(0x4003, 0x01);
    myMapper->writeCPU(0x4007, 0xB1);
    myMapper->writeCPU(0x006F, 0x30);
    myMapper->writeCPU(0x006E, 0xFF);
    popAddress();
}

void game::SUB_006337() {
    opCMP(0x04, myMapper->readCPU(0x006A));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (flgZ) {
        goto L_006347;
    }
    pushAddress(0x006344);
    SUB_00620F();
    if (poppedEntry.value != 0x006344) return;
L_006347:
    myMapper->writeCPU(0x006A, 0x04);
    myMapper->writeCPU(0x4000, 0x82);
    myMapper->writeCPU(0x4001, 0x00);
    myMapper->writeCPU(0x4002, 0x23);
    myMapper->writeCPU(0x4003, 0xC8);
    myMapper->writeCPU(0x006E, 0x0C);
    popAddress();
}

void game::SUB_006364() {
    a = myMapper->readCPU(0x0064);
    opORA(myMapper->readCPU(0x0065));
    if (flgZ) {
        goto L_00636D;
    }
    pushAddress(0x00636A);
    SUB_00620F();
    if (poppedEntry.value != 0x00636A) return;
L_00636D:
    myMapper->writeCPU(0x006D, 0x05);
    myMapper->writeCPU(0x400C, 0x04);
    myMapper->writeCPU(0x400E, 0x07);
    myMapper->writeCPU(0x400F, 0x20);
    myMapper->writeCPU(0x0071, 0x14);
    popAddress();
}

void game::SUB_006385() {
    opCMP(0x06, myMapper->readCPU(0x006A));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (flgZ) {
        goto L_006395;
    }
    pushAddress(0x006392);
    SUB_00620F();
    if (poppedEntry.value != 0x006392) return;
L_006395:
    myMapper->writeCPU(0x006A, 0x06);
    myMapper->writeCPU(0x4000, 0xCF);
    myMapper->writeCPU(0x4001, 0x08);
    myMapper->writeCPU(0x4002, 0xFF);
    myMapper->writeCPU(0x4003, 0x47);
    myMapper->writeCPU(0x006E, 0x50);
    popAddress();
}

void game::SUB_0063DA() {
    opCMP(0x0A, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_0063EA;
    }
    pushAddress(0x0063E7);
    SUB_00620F();
    if (poppedEntry.value != 0x0063E7) return;
L_0063EA:
    myMapper->writeCPU(0x006B, 0x0A);
    myMapper->writeCPU(0x4004, 0x9F);
    a = 0xFF;
    myMapper->writeCPU(0x4005, a);
    myMapper->writeCPU(0x4006, a);
    myMapper->writeCPU(0x4007, 0xD7);
    myMapper->writeCPU(0x006F, 0x0C);
    myMapper->writeCPU(0x0073, 0x01);
    popAddress();
}

void game::SUB_006409() {
    opCMP(0x0B, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_006419;
    }
    pushAddress(0x006416);
    SUB_00620F();
    if (poppedEntry.value != 0x006416) return;
L_006419:
    myMapper->writeCPU(0x006B, 0x0B);
    myMapper->writeCPU(0x4004, 0x9D);
    myMapper->writeCPU(0x4005, 0x00);
    myMapper->writeCPU(0x4006, 0x75);
    myMapper->writeCPU(0x4007, 0x8D);
    myMapper->writeCPU(0x006F, 0x08);
    myMapper->writeCPU(0x0073, 0x01);
    popAddress();
}

void game::SUB_00643A() {
    opCMP(0x0C, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_00644A;
    }
    pushAddress(0x006447);
    SUB_00620F();
    if (poppedEntry.value != 0x006447) return;
L_00644A:
    myMapper->writeCPU(0x006B, 0x0C);
    myMapper->writeCPU(0x4004, 0x9F);
    myMapper->writeCPU(0x4005, 0x00);
    myMapper->writeCPU(0x4006, 0x64);
    myMapper->writeCPU(0x4007, 0x38);
    myMapper->writeCPU(0x006F, 0x08);
    myMapper->writeCPU(0x0073, 0x01);
    popAddress();
}


void game::SUB_00646B() {
    opCMP(0x0D, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_00647B;
    }
    pushAddress(0x006478);
    SUB_00620F();
    if (poppedEntry.value != 0x006478) return;
L_00647B:
    myMapper->writeCPU(0x006B, 0x0D);
    myMapper->writeCPU(0x4004, 0x9F);
    myMapper->writeCPU(0x4005, 0x00);
    myMapper->writeCPU(0x4006, 0x35);
    myMapper->writeCPU(0x4007, 0x38);
    myMapper->writeCPU(0x006F, 0x03);
    myMapper->writeCPU(0x0073, 0x01);
    popAddress();
}

void game::SUB_00649C() {
    opCMP(0x0E, myMapper->readCPU(0x006D));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0064);
    opORA(myMapper->readCPU(0x0065));
    if (flgZ) {
        goto L_0064AC;
    }
    pushAddress(0x0064A9);
    SUB_00620F();
    if (poppedEntry.value != 0x0064A9) return;
L_0064AC:
    myMapper->writeCPU(0x006D, 0x0E);
    myMapper->writeCPU(0x400C, 0x1F);
    myMapper->writeCPU(0x400E, 0x07);
    myMapper->writeCPU(0x400F, 0x18);
    myMapper->writeCPU(0x0071, 0x02);
    popAddress();
}

void game::SUB_0064C4() {
    opCMP(0x0F, myMapper->readCPU(0x006A));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (flgZ) {
        goto L_0064D4;
    }
    pushAddress(0x0064D1);
    SUB_00620F();
    if (poppedEntry.value != 0x0064D1) return;
L_0064D4:
    myMapper->writeCPU(0x006A, 0x0F);
    myMapper->writeCPU(0x4000, 0x9F);
    myMapper->writeCPU(0x4001, 0x00);
    myMapper->writeCPU(0x4002, 0x28);
    myMapper->writeCPU(0x4003, 0x38);
    myMapper->writeCPU(0x006E, 0x03);
    myMapper->writeCPU(0x0072, 0x01);
    popAddress();
}

void game::SUB_0064F5() {
    opCMP(0x10, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_006505;
    }
    pushAddress(0x006502);
    SUB_00620F();
    if (poppedEntry.value != 0x006502) return;
L_006505:
    myMapper->writeCPU(0x006B, 0x10);
    myMapper->writeCPU(0x4004, 0x8F);
    myMapper->writeCPU(0x4005, 0x53);
    myMapper->writeCPU(0x4006, 0x14);
    myMapper->writeCPU(0x4007, 0x40);
    myMapper->writeCPU(0x006F, 0x50);
    popAddress();
}

void game::SUB_006522() {
    opCMP(0x11, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_006532;
    }
    pushAddress(0x00652F);
    SUB_00620F();
    if (poppedEntry.value != 0x00652F) return;
L_006532:
    myMapper->writeCPU(0x006B, 0x11);
    myMapper->writeCPU(0x4004, 0x9F);
    myMapper->writeCPU(0x4005, 0x00);
    myMapper->writeCPU(0x4006, 0x28);
    myMapper->writeCPU(0x4007, 0x28);
    myMapper->writeCPU(0x006F, 0x02);
    myMapper->writeCPU(0x0073, 0x01);
    popAddress();
}

void game::SUB_006553() {
    opCMP(0x12, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    opORA(myMapper->readCPU(0x0064));
    opORA(myMapper->readCPU(0x0065));
    if (flgZ) {
        goto L_006567;
    }
    pushAddress(0x006564);
    SUB_00620F();
    if (poppedEntry.value != 0x006564) return;
L_006567:
    a = 0x12;
    myMapper->writeCPU(0x006B, a);
    myMapper->writeCPU(0x006D, a);
    myMapper->writeCPU(0x4004, 0x9F);
    myMapper->writeCPU(0x4005, 0x8F);
    myMapper->writeCPU(0x4006, 0x5C);
    myMapper->writeCPU(0x400C, 0x1A);
    myMapper->writeCPU(0x400E, 0x09);
    myMapper->writeCPU(0x4007, 0xCA);
    myMapper->writeCPU(0x400F, 0xC8);
    a = 0x0C;
    myMapper->writeCPU(0x006F, a);
    myMapper->writeCPU(0x0071, a);
    a = 0x00;
    myMapper->writeCPU(0x0073, a);
    myMapper->writeCPU(0x0075, a);
    popAddress();
}

void game::SUB_00659D() {
    opCMP(0x13, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_0065AD;
    }
    pushAddress(0x0065AA);
    SUB_00620F();
    if (poppedEntry.value != 0x0065AA) return;
L_0065AD:
    myMapper->writeCPU(0x006B, 0x13);
    myMapper->writeCPU(0x4004, 0x9F);
    myMapper->writeCPU(0x4005, 0x83);
    myMapper->writeCPU(0x4006, 0x14);
    myMapper->writeCPU(0x4007, 0x30);
    myMapper->writeCPU(0x006F, 0x28);
    popAddress();
}

void game::SUB_0065CA() {
    opCMP(0x14, myMapper->readCPU(0x006A));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (flgZ) {
        goto L_0065DA;
    }
    pushAddress(0x0065D7);
    SUB_00620F();
    if (poppedEntry.value != 0x0065D7) return;
L_0065DA:
    myMapper->writeCPU(0x006A, 0x14);
    myMapper->writeCPU(0x4000, 0x9F);
    myMapper->writeCPU(0x4001, 0x8A);
    myMapper->writeCPU(0x4002, 0x47);
    myMapper->writeCPU(0x4003, 0x68);
    myMapper->writeCPU(0x006E, 0x06);
    myMapper->writeCPU(0x0072, 0x01);
    popAddress();
}

void game::SUB_0065FB() {
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_006604;
    }
    pushAddress(0x006601);
    SUB_00620F();
    if (poppedEntry.value != 0x006601) return;
L_006604:
    myMapper->writeCPU(0x006B, 0x15);
    myMapper->writeCPU(0x006F, 0x04);
    myMapper->writeCPU(0x4004, 0x80);
    a = 0x00;
    myMapper->writeCPU(0x4005, a);
    myMapper->writeCPU(0x4006, a);
    a = 0x49;
    setLoadFlag(a);
    myMapper->writeCPU(0x4007, a);
    popAddress();
}

void game::SUB_00661F() {
    opCMP(0x16, myMapper->readCPU(0x006A));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (flgZ) {
        goto L_00662F;
    }
    pushAddress(0x00662C);
    SUB_00620F();
    if (poppedEntry.value != 0x00662C) return;
L_00662F:
    myMapper->writeCPU(0x006C, 0x16);
    myMapper->writeCPU(0x4000, 0x9F);
    myMapper->writeCPU(0x4001, 0x08);
    myMapper->writeCPU(0x4002, 0xAE);
    myMapper->writeCPU(0x4003, 0x8E);
    myMapper->writeCPU(0x006E, 0x08);
    myMapper->writeCPU(0x0072, 0x00);
    popAddress();
}

void game::SUB_006650() {
    opCMP(0x17, myMapper->readCPU(0x006B));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0060);
    opORA(myMapper->readCPU(0x0061));
    if (flgZ) {
        goto L_006660;
    }
    pushAddress(0x00665D);
    SUB_00620F();
    if (poppedEntry.value != 0x00665D) return;
L_006660:
    myMapper->writeCPU(0x006B, 0x17);
    myMapper->writeCPU(0x4004, 0x83);
    myMapper->writeCPU(0x4005, 0x08);
    myMapper->writeCPU(0x4006, 0x2C);
    myMapper->writeCPU(0x4007, 0x48);
    myMapper->writeCPU(0x0073, 0x00);
    myMapper->writeCPU(0x006F, 0x04);
    popAddress();
}

void game::SUB_006681() {
    a = 0x03;
    if (a == myMapper->readCPU(0x006A)) {
        if (a == myMapper->readCPU(0x006B)) {
            goto L_00668F;
        }
        myMapper->writeCPU(0x006A, 0x00);
    }
L_00668F:
    a = 0x03;
    if (a == myMapper->readCPU(0x006B)) {
        if (a == myMapper->readCPU(0x006A)) {
            goto L_00669D;
        }
        myMapper->writeCPU(0x006B, 0x00);
    }
L_00669D:
    a = 0x12;
    if (a == myMapper->readCPU(0x006B)) {
        if (a == myMapper->readCPU(0x006D)) {
            goto L_0066AB;
        }
        myMapper->writeCPU(0x006B, 0x00);
    }
L_0066AB:
    a = 0x12;
    if (a == myMapper->readCPU(0x006D)) {
        if (a == myMapper->readCPU(0x006B)) {
            goto L_0066B9;
        }
        myMapper->writeCPU(0x006D, 0x00);
    }
L_0066B9:
    a = myMapper->readCPU(0x006A);
    setLoadFlag(a);
    pushAddress(0x0066BB);
    SUB_0066D6();
    if (poppedEntry.value != 0x0066BB) return;
    a = myMapper->readCPU(0x006B);
    opCMP(a, 0x03);
    if (!flgZ) {
        pushAddress(0x0066C4);
        SUB_0066D6();
        if (poppedEntry.value != 0x0066C4) return;
    }
    a = myMapper->readCPU(0x006C);
    setLoadFlag(a);
    pushAddress(0x0066C9);
    SUB_0066D6();
    if (poppedEntry.value != 0x0066C9) return;
    a = myMapper->readCPU(0x006D);
    opCMP(a, 0x12);
    if (flgZ) {
        goto L_0066D5;
    }
    pushAddress(0x0066D2);
    SUB_0066D6();
    if (poppedEntry.value != 0x0066D2) return;
L_0066D5:
    popAddress();
}

void game::SUB_0066D6() {
    if (!flgZ) {
        goto L_0066D9;
    }
    popAddress();
    return;
L_0066D9:
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xE6E8 + x));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0xE6E9 + x));
    indirectJump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_006705() {
    //NOP
    SUB_006718();
    return;
}

void game::SUB_006718() {
    opDEC(0x006E, 1);
    if (flgZ) {
        goto L_00671D;
    }
    popAddress();
    return;
L_00671D:
    myMapper->writeCPU(0x006A, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_006724() {
    opDEC(0x0071, 1);
    if (flgZ) {
        goto L_006729;
    }
    popAddress();
    return;
L_006729:
    myMapper->writeCPU(0x006D, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_006730() {
    opDEC(0x006F, 1);
    if (flgZ) {
        goto L_006735;
    }
    popAddress();
    return;
L_006735:
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_00673C() {
    opDEC(0x0071, 1);
    if (flgZ) {
        goto L_006741;
    }
    popAddress();
    return;
L_006741:
    myMapper->writeCPU(0x006D, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_006748() {
    opDEC(0x006B, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opCMP(myMapper->readCPU(0x0073), 0x02);
    if (flgZ) {
        goto L_00676B;
    }
    myMapper->writeCPU(0x4005, 0x00);
    myMapper->writeCPU(0x4006, 0x60);
    myMapper->writeCPU(0x4007, 0xB7);
    myMapper->writeCPU(0x0073, 0x02);
    myMapper->writeCPU(0x006F, 0x24);
    popAddress();
    return;
L_00676B:
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_006772() {
    opDEC(0x006B, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opCMP(myMapper->readCPU(0x0073), 0x02);
    if (flgZ) {
        goto L_00679A;
    }
    myMapper->writeCPU(0x4004, 0x8A);
    myMapper->writeCPU(0x4005, 0x00);
    myMapper->writeCPU(0x4006, 0x89);
    myMapper->writeCPU(0x4007, 0x34);
    myMapper->writeCPU(0x0073, 0x02);
    myMapper->writeCPU(0x006F, 0x28);
    popAddress();
    return;
L_00679A:
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_0067A1() {
    opDEC(0x006B, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opCMP(myMapper->readCPU(0x0073), 0x02);
    if (flgZ) {
        goto L_0067C9;
    }
    myMapper->writeCPU(0x4004, 0x9F);
    myMapper->writeCPU(0x4005, 0x85);
    myMapper->writeCPU(0x4006, 0x64);
    myMapper->writeCPU(0x4007, 0xD8);
    myMapper->writeCPU(0x0073, 0x02);
    myMapper->writeCPU(0x006F, 0x0D);
    popAddress();
    return;
L_0067C9:
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_0067D0() {
    opDEC(0x006F, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opINC(0x0073, 1);
    a = myMapper->readCPU(0x0073);
    opCMP(a, 0x07);
    if (flgZ) {
        goto L_0067E9;
    }
    x = a;
    myMapper->writeCPU(0x4006, myMapper->readCPU(0xE7F0 + x));
    myMapper->writeCPU(0x006F, 0x03);
    popAddress();
    return;
L_0067E9:
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_0067F7() {
    opDEC(0x0071, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opINC(0x0075, 1);
    a = myMapper->readCPU(0x0075);
    if (a != 0x07) {
        goto L_006808;
    }
    a = 0x01;
    myMapper->writeCPU(0x0075, a);
L_006808:
    x = a;
    myMapper->writeCPU(0x400E, myMapper->readCPU(0xE819 + x));
    myMapper->writeCPU(0x400F, 0x18);
    myMapper->writeCPU(0x0071, 0x01);
    popAddress();
}

void game::SUB_006820() {
    opDEC(0x006E, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x006E, 0x03);
    opINC(0x0072, 1);
    a = myMapper->readCPU(0x0072);
    opCMP(a, 0x08);
    if (!flgZ) {
        goto L_006838;
    }
    myMapper->writeCPU(0x006A, 0x00);
    SUB_0069EC();
    return;
L_006838:
    x = a;
    myMapper->writeCPU(0x4002, myMapper->readCPU(0xE849 + x));
    myMapper->writeCPU(0x4003, 0x38);
    myMapper->writeCPU(0x006E, 0x03);
    popAddress();
}

void game::SUB_006851() {
    opDEC(0x006F, 1);
    if (flgZ) {
        goto L_006856;
    }
    popAddress();
    return;
L_006856:
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_00685D() {
    opDEC(0x006F, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opINC(0x0073, 1);
    a = myMapper->readCPU(0x0073);
    opCMP(a, 0x0A);
    if (!flgZ) {
        goto L_006871;
    }
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
L_006871:
    x = a;
    myMapper->writeCPU(0x4006, myMapper->readCPU(0xE87D + x));
    myMapper->writeCPU(0x006F, 0x02);
    popAddress();
}

void game::SUB_006887() {
    opDEC(0x006F, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x0073);
    opINX(1);
    opCMP(x, 0x05);
    if (flgC) {
        goto L_0068A2;
    }
    myMapper->writeCPU(0x0073, x);
    a = 0xCA;
    myMapper->writeCPU(0x4007, a);
    myMapper->writeCPU(0x400F, a);
    myMapper->writeCPU(0x006F, 0x0C);
    popAddress();
    return;
L_0068A2:
    a = 0x00;
    myMapper->writeCPU(0x006B, a);
    myMapper->writeCPU(0x006D, a);
    SUB_0069EC();
    return;
}

void game::SUB_0068AB() {
    opDEC(0x006E, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    opINC(0x0072, 1);
    a = myMapper->readCPU(0x0072);
    if (a == 0x05) {
        SUB_00693A();
        return;
    }
    x = a;
    myMapper->writeCPU(0x4003, myMapper->readCPU(0xE8CF + x));
    opCMP(myMapper->readCPU(0x0072), 0x04);
    pushStatus();
    a = 0x06;
    setLoadFlag(a);
    popStatus();
    if (!flgZ) {
        goto L_0068CE;
    }
    a = 0x12;
L_0068CE:
    myMapper->writeCPU(0x006E, a);
    popAddress();
}

void game::SUB_0068D4() {
    opDEC(0x006E, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x0072) != 0) {
        goto L_0068F0;
    }
    myMapper->writeCPU(0x400A, 0x89);
    myMapper->writeCPU(0x400B, 0x8B);
    myMapper->writeCPU(0x0072, 0x01);
    myMapper->writeCPU(0x006E, 0x08);
    popAddress();
    return;
L_0068F0:
    myMapper->writeCPU(0x006A, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_0068F7() {
    opDEC(0x006F, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x0073);
    opINX(1);
    opCMP(x, 0x06);
    if (flgZ) {
        goto L_006918;
    }
    myMapper->writeCPU(0x0073, x);
    myMapper->writeCPU(0x4006, myMapper->readCPU(0xE923 + x));
    a = myMapper->readCPU(0xE928 + x);
    myMapper->writeCPU(0x4007, a);
    opLSR_A(4);
    myMapper->writeCPU(0x006F, a);
    popAddress();
    return;
L_006918:
    myMapper->writeCPU(0x4004, 0x10);
    myMapper->writeCPU(0x006B, 0x00);
    SUB_0069EC();
    return;
}

void game::SUB_00693A() {
    opCMP(0x14, myMapper->readCPU(0x006A));
    if (flgZ) {
        goto L_006941;
    }
    popAddress();
    return;
L_006941:
    myMapper->writeCPU(0x006A, 0x00);
    myMapper->writeCPU(0x4000, 0x10);
    SUB_0069EC();
    return;
}

void game::SUB_00694D() {
    a = 0x0A;
    opBIT(myMapper->readCPU(0x0BA9));
    opBIT(myMapper->readCPU(0x0CA9));
    opBIT(myMapper->readCPU(0x0DA9));
    SUB_006956();
    return;
}

void game::SUB_006956() {
    a = 0x0D;
    SUB_00695B();
    return;
}

void game::SUB_006959() {
    a = 0x10;
    SUB_00695B();
    return;
}

void game::SUB_00695B() {
    SUB_00695E();
    return;
}

void game::SUB_00695C() {
    a = 0x11;
    SUB_00695E();
    return;
}

void game::SUB_00695E() {
    goto L_006961;
    a = 0x13;
L_006961:
    goto L_006964;
    a = 0x17;
L_006964:
    opCMP(a, myMapper->readCPU(0x006B));
    if (flgZ) {
        goto L_006969;
    }
    popAddress();
    return;
L_006969:
    myMapper->writeCPU(0x006B, 0x00);
    myMapper->writeCPU(0x4004, 0x10);
    SUB_0069EC();
    return;
}

void game::SUB_006975() {
    if (0x12 != myMapper->readCPU(0x006B)) {
        goto L_006984;
    }
    myMapper->writeCPU(0x006B, 0x00);
    myMapper->writeCPU(0x4004, 0x10);
L_006984:
    opCMP(0x12, myMapper->readCPU(0x006D));
    if (!flgZ) {
        goto L_006993;
    }
    myMapper->writeCPU(0x006D, 0x00);
    myMapper->writeCPU(0x400C, 0x10);
L_006993:
    SUB_0069EC();
    return;
}

void game::SUB_006996() {
    if (0x03 != myMapper->readCPU(0x006B)) {
        goto L_0069A5;
    }
    myMapper->writeCPU(0x006B, 0x00);
    myMapper->writeCPU(0x4004, 0x10);
L_0069A5:
    opCMP(0x03, myMapper->readCPU(0x006A));
    if (!flgZ) {
        goto L_0069B4;
    }
    myMapper->writeCPU(0x006A, 0x00);
    myMapper->writeCPU(0x400C, 0x10);
L_0069B4:
    SUB_0069EC();
    return;
}

void game::SUB_0069C3() {
    a = 0x09;
    opBIT(myMapper->readCPU(0x0EA9));
    SUB_0069C6();
    return;
}

void game::SUB_0069C6() {
    opCMP(0x0E, myMapper->readCPU(0x006D));
    if (flgZ) {
        goto L_0069CD;
    }
    popAddress();
    return;
L_0069CD:
    myMapper->writeCPU(0x006D, 0x00);
    myMapper->writeCPU(0x400C, 0x10);
    SUB_0069EC();
    return;
}

void game::SUB_0069EC() {
    if (myMapper->readCPU(0x006A) == 0) {
        goto L_0069F7;
    }
    a = myMapper->readCPU(0x005E);
    opORA(myMapper->readCPU(0x005F));
    if (!flgZ) {
        popAddress();
        return;
    }
L_0069F7:
    if (myMapper->readCPU(0x006B) != 0) {
        a = myMapper->readCPU(0x0060);
        opORA(myMapper->readCPU(0x0061));
        if (!flgZ) {
            popAddress();
            return;
        }
    }
    if (myMapper->readCPU(0x006C) != 0) {
        a = myMapper->readCPU(0x0062);
        opORA(myMapper->readCPU(0x0063));
        if (!flgZ) {
            popAddress();
            return;
        }
    }
    if (myMapper->readCPU(0x006D) != 0) {
        a = myMapper->readCPU(0x0064);
        opORA(myMapper->readCPU(0x0065));
        if (flgZ) {
            goto L_006A18;
        }
        popAddress();
        return;
    }
L_006A18:
    SUB_006219();
    return;
}

void game::SUB_006A1B() {
    myMapper->writeCPU(0x2001, 0x01);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    a = 0xE6;
    x = 0x00;
    do {
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        opINX(1);
    } while (!flgZ);
    x = 0x40;
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0xC0);
    a = 0x00;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xCB);
    x = 0x09;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEBFA + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0x44);
    x = 0x07;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC04 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0x55);
    x = 0x08;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC0C + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xAA);
    x = 0x06;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC15 + x));
        opDEX(1);
    } while (!flgN);
    x = 0x05;
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xB2);
    do {
        a = myMapper->readCPU((0x0034 + x) & 0x00ff);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xE5);
    x = 0x0A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC1C + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xF1);
    x = 0x08;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC27 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x03);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC30 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x23);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC4B + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x43);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC66 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x63);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC81 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x83);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xEC9C + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0xA3);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xECB7 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0xC3);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xECD2 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0xE3);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xECED + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0x03);
    x = 0x1A;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xED08 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2000, 0x10);
//L_006BA8:
    //if (!(myMapper->readCPU(0x2002) & 0x80)) {
    //    goto L_006BA8;
    //}
    x = 0x00;
    do {
        myMapper->writeCPU(0x2006, 0x3F);
        myMapper->writeCPU(0x2006, x);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xED23 + x));
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        opINX(1);
    } while (x != 0x04);
    myMapper->writeCPU(0x2000, 0x90);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0xC0);
    x = 0x00;
    a = x;
    do {
        myMapper->writeCPU(0x2007, a);
        opINX(1);
    } while (x != 0x40);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2001, 0x1E);
    popAddress();
}

void game::SUB_006D27() {
    myMapper->writeCPU(0x2001, 0x01);
    myMapper->writeCPU(0x2000, 0x10);
//L_006D31:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_006D31;
//    }
    x = 0x10;
    do {
        myMapper->writeCPU(0x2006, 0x3F);
        myMapper->writeCPU(0x2006, x);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xA80F + x));
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        opINX(1);
        opCMP(x, 0x20);
    } while (!flgZ);
    myMapper->writeCPU(0x2000, 0x90);
    myMapper->writeCPU(0x2001, 0x1E);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0022, 0x00);
    myMapper->writeCPU(0x0085, 0xFF);
    while (true) {
    L_006D75:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_006D75;
        }
        opINC(0x0021, 1);
        a = myMapper->readCPU(0x0009);
        opORA(myMapper->readCPU(0x000A));
        if (!flgZ) {
            if (myMapper->readCPU(0x0009) != 0) {
                goto L_006D87;
            }
            opDEC(0x000A, 1);
        L_006D87:
            opDEC(0x0009, 1);
            pushAddress(0x006D89);
            SUB_00611E();
            if (poppedEntry.value != 0x006D89) return;
            a = myMapper->readCPU(0x0009);
            opORA(myMapper->readCPU(0x000A));
            if (flgZ) {
                pushAddress(0x006D92);
                SUB_00620F();
                if (poppedEntry.value != 0x006D92) return;
            }
        }
        pushAddress(0x006D95);
        SUB_007A7B();
        if (poppedEntry.value != 0x006D95) return;
        a = myMapper->readCPU(0x0022);
        opASL_A(2);
        myMapper->writeCPU(0x0058, a);
        opASL_A(3);
        flgC = false;
        opADC(myMapper->readCPU(0x0058));
        x = a;
        y = 0x00;
        do {
            myMapper->writeCPU(0x0700 + y, myMapper->readCPU(0xEDF1 + x));
            opINX(1);
            opINY(1);
        } while (y != 0x24);
        pushAddress(0x006DB3);
        SUB_0057C5();
        if (poppedEntry.value != 0x006DB3) return;
        myMapper->writeCPU(0x000B, a);
        opAND(0x08);
        if (!flgZ) {
            if (myMapper->readCPU(0x0085) != 0) {
                goto L_006DC5;
            }
            opINC(0x0022, 1);
            goto L_006E39;
        }
    L_006DC5:
        a = myMapper->readCPU(0x000B);
        opAND(0x04);
        if (!flgZ) {
            if (myMapper->readCPU(0x0085) != 0) {
                goto L_006DD7;
            }
            a = myMapper->readCPU(0x0022);
            opEOR(0x01);
            myMapper->writeCPU(0x0022, a);
            a = 0xFF;
        }
    L_006DD7:
        myMapper->writeCPU(0x0085, myMapper->readCPU(0x000B));
        if (myMapper->readCPU(0x0007) != 0) {
            goto L_006DE1;
        }
        opDEC(0x0008, 1);
    L_006DE1:
        opDEC(0x0007, 1);
        a = myMapper->readCPU(0x0007);
        opORA(myMapper->readCPU(0x0008));
        if (flgZ) {
            goto L_006DEC;
        }
    }
L_006DEC:
    myMapper->writeCPU(0x0022, 0x00);
    popAddress();
    return;
L_006E39:
    myMapper->writeCPU(0x0058, 0x03);
    do {
        pushAddress(0x006E3D);
        SUB_0062A3();
        if (poppedEntry.value != 0x006E3D) return;
        myMapper->writeCPU(0x0059, 0x00);
        do {
            a = myMapper->readCPU(0x0022);
            flgC = true;
            opSBC(0x01);
            opASL_A(3);
            flgC = false;
            opADC(myMapper->readCPU(0x0059));
            y = a;
            myMapper->writeCPU(0x0727, myMapper->readCPU(0xEE92 + y));
            myMapper->writeCPU(0x0724, 0x94);
            myMapper->writeCPU(0x0725, 0x00);
            a = myMapper->readCPU(0x0022);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU(0x0726, a);
            myMapper->writeCPU(0x0021, 0x02);
        L_006E6C:
            if (myMapper->readCPU(0x0021) != 0) {
                wait(1);
                goto L_006E6C;
            }
            opINC(0x0059, 1);
            opCMP(myMapper->readCPU(0x0059), 0x08);
        } while (!flgC);
        opDEC(0x0058, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0724, 0xF8);
    myMapper->writeCPU(0x0021, 0x01);
L_006E85:
    if (myMapper->readCPU(0x0021) != 0) {
        wait(1);
        goto L_006E85;
    }
    myMapper->writeCPU(0x0021, 0x14);
L_006E8D:
    if (myMapper->readCPU(0x0021) != 0) {
        wait(1);
        goto L_006E8D;
    }
    popAddress();
}

void game::SUB_006EA2() {
    a = myMapper->readCPU(0x0052);
    opPHA();
    myMapper->writeCPU(0x0052, 0xFF);
    myMapper->writeCPU(0x0076, 0x30);
    myMapper->writeCPU(0x0077, 0xFF);
    myMapper->writeCPU(0x2001, 0x00);
    myMapper->writeCPU(0x2000, 0x10);
//L_006EBB:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_006EBB;
//    }
    x = 0x00;
    do {
        myMapper->writeCPU(0x2006, 0x3F);
        myMapper->writeCPU(0x2006, x);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xED23 + x));
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        opINX(1);
    } while (x < 0x04);
    myMapper->writeCPU(0x2000, 0x90);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    a = 0xE6;
    x = 0xF0;
    do {
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    x = 0x40;
    a = 0x00;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x6C);
    myMapper->writeCPU(0x2007, 0xF2);
    myMapper->writeCPU(0x2007, 0xE4);
    myMapper->writeCPU(0x2007, 0xE7);
    myMapper->writeCPU(0x2007, 0xEA);
    myMapper->writeCPU(0x2007, 0xE9);
    myMapper->writeCPU(0x2007, 0xE6);
    if (myMapper->readCPU(0x0023) < 0x0A) {
        goto L_006F52;
    }
    myMapper->writeCPU(0x2007, 0xF7);
    a = myMapper->readCPU(0x0023);
    flgC = false;
    opADC(0xEC);
    myMapper->writeCPU(0x2007, a);
    goto L_006F5F;
L_006F52:
    myMapper->writeCPU(0x2007, 0xE6);
    a = myMapper->readCPU(0x0023);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x2007, a);
L_006F5F:
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2001, 0x16);
    myMapper->writeCPU(0x0052, 0x00);
    pushAddress(0x006F70);
    SUB_007A7B();
    if (poppedEntry.value != 0x006F70) return;
    myMapper->writeCPU(0x0058, 0x00);
    do {
        a = myMapper->readCPU(0x0058);
        opAND(0xFE);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x000D, a);
        myMapper->writeCPU(0x000E, 0xB0);
        myMapper->writeCPU(0x0013, 0x00);
        a = myMapper->readCPU(0x0058);
        opLSR_A(1);
        opAND(0x03);
        x = a;
        y = myMapper->readCPU(0xF0D5 + x);
        x = 0x00;
        pushAddress(0x006F94);
        SUB_003ABB();
        if (poppedEntry.value != 0x006F94) return;
        myMapper->writeCPU(0x0021, 0x02);
    L_006F9B:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_006F9B;
        }
        opINC(0x0058, 1);
    } while (myMapper->readCPU(0x0058) < 0x3A);
    myMapper->writeCPU(0x0058, 0x00);
    do {
        x = myMapper->readCPU(0x0058);
        myMapper->writeCPU(0x000E, myMapper->readCPU(0xF0D9 + x));
        myMapper->writeCPU(0x000D, 0x40);
        myMapper->writeCPU(0x0013, 0x00);
        a = myMapper->readCPU(0x0058);
        opLSR_A(3);
        opAND(0x01);
        x = a;
        y = myMapper->readCPU(0xF0FB + x);
        x = 0x00;
        pushAddress(0x006FC8);
        SUB_003ABB();
        if (poppedEntry.value != 0x006FC8) return;
        x = myMapper->readCPU(0x0058);
        myMapper->writeCPU(0x0710, myMapper->readCPU(0xF0FD + x));
        a = 0x00;
        myMapper->writeCPU(0x0711, a);
        myMapper->writeCPU(0x0712, a);
        myMapper->writeCPU(0x0713, 0x3C);
        myMapper->writeCPU(0x0021, 0x02);
    L_006FE4:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_006FE4;
        }
        a = myMapper->readCPU(0x0058);
        opAND(0x07);
        if (!flgZ) {
            goto L_006FF1;
        }
        pushAddress(0x006FEE);
        SUB_0062A3();
        if (poppedEntry.value != 0x006FEE) return;
    L_006FF1:
        opINC(0x0058, 1);
    } while (myMapper->readCPU(0x0058) < 0x22);
    myMapper->writeCPU(0x0058, 0x00);
    do {
        x = myMapper->readCPU(0x0058);
        myMapper->writeCPU(0x000D, myMapper->readCPU(0xF11F + x));
        myMapper->writeCPU(0x000E, 0x5C);
        myMapper->writeCPU(0x0013, 0x00);
        a = myMapper->readCPU(0x0058);
        opLSR_A(2);
        opAND(0x01);
        x = a;
        y = myMapper->readCPU(0xF152 + x);
        x = 0x00;
        pushAddress(0x007019);
        SUB_003ABB();
        if (poppedEntry.value != 0x007019) return;
        x = myMapper->readCPU(0x0058);
        myMapper->writeCPU(0x0713, myMapper->readCPU(0xF154 + x));
        a = 0x00;
        myMapper->writeCPU(0x0711, a);
        myMapper->writeCPU(0x0712, a);
        myMapper->writeCPU(0x0710, 0x5C);
        myMapper->writeCPU(0x0021, 0x02);
    L_007035:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_007035;
        }
        a = myMapper->readCPU(0x0058);
        opAND(0x07);
        if (flgZ) {
            pushAddress(0x00703F);
            SUB_0062A3();
            if (poppedEntry.value != 0x00703F) return;
        }
        if (myMapper->readCPU(0x0058) != 0x1E) {
            goto L_00704D;
        }
        myMapper->writeCPU(0x2001, 0x1C);
    L_00704D:
        opINC(0x0058, 1);
    } while (myMapper->readCPU(0x0058) < 0x33);
    myMapper->writeCPU(0x0710, 0xF8);
    myMapper->writeCPU(0x0058, 0x00);
    do {
        a = myMapper->readCPU(0x0058);
        opASL_A(1);
        flgC = false;
        opADC(0x5C);
        myMapper->writeCPU(0x000E, a);
        myMapper->writeCPU(0x000D, 0xC0);
        myMapper->writeCPU(0x0013, 0x00);
        y = 0x15;
        x = 0x00;
        pushAddress(0x007072);
        SUB_003ABB();
        if (poppedEntry.value != 0x007072) return;
        myMapper->writeCPU(0x0021, 0x02);
    L_007079:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_007079;
        }
        opINC(0x0058, 1);
    } while (myMapper->readCPU(0x0058) < 0x2A);
    myMapper->writeCPU(0x0058, 0x00);
    do {
        a = myMapper->readCPU(0x0058);
        opAND(0xFE);
        flgC = false;
        opADC(0xC0);
        myMapper->writeCPU(0x000D, a);
        myMapper->writeCPU(0x000E, 0xB0);
        myMapper->writeCPU(0x0013, 0x00);
        a = myMapper->readCPU(0x0058);
        opLSR_A(1);
        opAND(0x03);
        x = a;
        y = myMapper->readCPU(0xF0D5 + x);
        x = 0x00;
        pushAddress(0x0070A6);
        SUB_003ABB();
        if (poppedEntry.value != 0x0070A6) return;
        myMapper->writeCPU(0x0021, 0x02);
    L_0070AD:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_0070AD;
        }
        opINC(0x0058, 1);
    } while (myMapper->readCPU(0x0058) < 0x3C);
    pushAddress(0x0070B9);
    SUB_007A7B();
    if (poppedEntry.value != 0x0070B9) return;
    myMapper->writeCPU(0x0021, 0x01);
L_0070C0:
    if (myMapper->readCPU(0x0021) != 0) {
        wait(1);
        goto L_0070C0;
    }
    myMapper->writeCPU(0x0021, 0x1E);
L_0070C8:
    if (myMapper->readCPU(0x0021) != 0) {
        wait(1);
        goto L_0070C8;
    }
    a = 0x1E;
    myMapper->writeCPU(0x2001, a);
    opPLA();
    myMapper->writeCPU(0x0052, a);
    popAddress();
}

void game::SUB_007187() {
    myMapper->writeCPU(0x0052, 0xFF);
    myMapper->writeCPU(0x0076, 0x30);
    myMapper->writeCPU(0x0077, 0xFF);
    pushAddress(0x007193);
    SUB_00775A();
    if (poppedEntry.value != 0x007193) return;
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    x = 0xF0;
    a = 0xE6;
    do {
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    a = 0x00;
    x = 0x40;
    do {
        myMapper->writeCPU(0x2006, a);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x2000, 0x10);
//L_0071CA:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_0071CA;
//    }
    x = 0x10;
    do {
        myMapper->writeCPU(0x2006, 0x3F);
        myMapper->writeCPU(0x2006, x);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xA80F + x));
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        opINX(1);
    } while (x < 0x20);
    myMapper->writeCPU(0x2000, 0x90);
    x = 0x1F;
    a = 0xE6;
    do {
        myMapper->writeCPU((0x008F + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0x0E);
    a = myMapper->readCPU(0x0026);
    flgC = false;
    opADC(myMapper->readCPU(0x002E));
    if (a >= 0x0A) {
        flgC = true;
        opSBC(0x0A);
    }
    opASL_A(2);
    x = a;
    myMapper->writeCPU(0x2007, myMapper->readCPU(0xF732 + x));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0xF733 + x));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0xF734 + x));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0xF735 + x));
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0xA9);
    x = 0x04;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xF5AF + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2007, 0xF7);
    myMapper->writeCPU(0x2007, 0xE6);
    myMapper->writeCPU(0x0058, 0x00);
    x = 0x05;
    do {
        a = myMapper->readCPU((0x0024 + x) & 0x00ff);
        pushAddress(0x00725A);
        SUB_007590();
        if (poppedEntry.value != 0x00725A) return;
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x2007, a);
    if (myMapper->readCPU(0x0022) != 0x02) {
        goto L_0072A9;
    }
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0xC9);
    x = 0x04;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xF5AF + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2007, 0xF8);
    myMapper->writeCPU(0x2007, 0xE6);
    myMapper->writeCPU(0x0058, 0x00);
    x = 0x05;
    do {
        a = myMapper->readCPU((0x002C + x) & 0x00ff);
        pushAddress(0x007298);
        SUB_007590();
        if (poppedEntry.value != 0x007298) return;
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x002C);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x2007, a);
L_0072A9:
    myMapper->writeCPU(0x2001, 0x16);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0052, a);
    myMapper->writeCPU(0x4015, 0x00);
    myMapper->writeCPU(0x4015, 0x0F);
    myMapper->writeCPU(0x005D, 0x00);
    pushAddress(0x0072C6);
    SUB_00610C();
    if (poppedEntry.value != 0x0072C6) return;
    myMapper->writeCPU(0x0058, 0x09);
    while (true) {
        pushAddress(0x0072CD);
        SUB_007A7B();
        if (poppedEntry.value != 0x0072CD) return;
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000D, 0x74);
        myMapper->writeCPU(0x0013, 0x00);
        y = 0x04;
        x = 0x00;
        pushAddress(0x0072E0);
        SUB_003ABB();
        if (poppedEntry.value != 0x0072E0) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x0072EC);
        SUB_0041BC();
        if (poppedEntry.value != 0x0072EC) return;
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000D, 0x8C);
        myMapper->writeCPU(0x0013, 0x01);
        y = 0x00;
        pushAddress(0x0072FD);
        SUB_003ABB();
        if (poppedEntry.value != 0x0072FD) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x007309);
        SUB_0041BC();
        if (poppedEntry.value != 0x007309) return;
        pushAddress(0x00730C);
        SUB_0075A3();
        if (poppedEntry.value != 0x00730C) return;
        pushAddress(0x00730F);
        SUB_0075A3();
        if (poppedEntry.value != 0x00730F) return;
        pushAddress(0x007312);
        SUB_0075A3();
        if (poppedEntry.value != 0x007312) return;
        opINC(0x0058, 1);
        if (myMapper->readCPU(0x0058) >= 0x10) {
            goto L_007320;
        }
    }
    while (true) {
    L_007320:
        pushAddress(0x007320);
        SUB_007A7B();
        if (poppedEntry.value != 0x007320) return;
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000D, 0x74);
        myMapper->writeCPU(0x0013, 0x00);
        y = 0x04;
        x = 0x00;
        pushAddress(0x007333);
        SUB_003ABB();
        if (poppedEntry.value != 0x007333) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x00733F);
        SUB_0041BC();
        if (poppedEntry.value != 0x00733F) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x00734B);
        SUB_004149();
        if (poppedEntry.value != 0x00734B) return;
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000D, 0x8C);
        myMapper->writeCPU(0x0013, 0x01);
        y = 0x00;
        pushAddress(0x00735C);
        SUB_003ABB();
        if (poppedEntry.value != 0x00735C) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x007368);
        SUB_0041BC();
        if (poppedEntry.value != 0x007368) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x007374);
        SUB_004149();
        if (poppedEntry.value != 0x007374) return;
        pushAddress(0x007377);
        SUB_0075A3();
        if (poppedEntry.value != 0x007377) return;
        pushAddress(0x00737A);
        SUB_0075A3();
        if (poppedEntry.value != 0x00737A) return;
        pushAddress(0x00737D);
        SUB_0075A3();
        if (poppedEntry.value != 0x00737D) return;
        opINC(0x0058, 1);
        if (myMapper->readCPU(0x0058) >= 0x3C) {
            goto L_00738B;
        }
    }
L_00738B:
    myMapper->writeCPU(0x0058, 0x00);
    while (true) {
        pushAddress(0x00738F);
        SUB_007A7B();
        if (poppedEntry.value != 0x00738F) return;
        a = myMapper->readCPU(0x0058);
        opASL_A(1);
        myMapper->writeCPU(0x0005, a);
        a = 0x00;
        opADC(0x00);
        myMapper->writeCPU(0x0006, a);
        a = myMapper->readCPU(0x0005);
        flgC = false;
        opADC(0xB4);
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x0006);
        opADC(0xF5);
        myMapper->writeCPU(0x0006, a);
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x000D, a);
        opINY(1);
        myMapper->writeCPU(0x000E, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0013, 0x00);
        y = 0x04;
        x = 0x00;
        pushAddress(0x0073C2);
        SUB_003ABB();
        if (poppedEntry.value != 0x0073C2) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x0073CE);
        SUB_0041BC();
        if (poppedEntry.value != 0x0073CE) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x0073DA);
        SUB_004149();
        if (poppedEntry.value != 0x0073DA) return;
        y = 0x00;
        myMapper->writeCPU(0x000D, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x000E, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0013, 0x01);
        y = 0x00;
        pushAddress(0x0073EE);
        SUB_003ABB();
        if (poppedEntry.value != 0x0073EE) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x0073FA);
        SUB_0041BC();
        if (poppedEntry.value != 0x0073FA) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x007406);
        SUB_004149();
        if (poppedEntry.value != 0x007406) return;
        myMapper->writeCPU(0x0006, x);
        myMapper->writeCPU(0x0005, 0x00);
        a = myMapper->readCPU(0x0058);
        flgC = true;
        while (true) {
            opSBC(0x06);
            if (!flgC) {
                goto L_00741B;
            }
            opINC(0x0005, 1);
        }
    L_00741B:
        a = myMapper->readCPU(0x0005);
        opASL_A(3);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x0005, a);
        x = myMapper->readCPU(0x0006);
        y = 0x00;
        do {
            myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xF68A + y));
            opINX(1);
            opINY(1);
            opCMP(y, myMapper->readCPU(0x0005));
        } while (!flgC);
        pushAddress(0x007435);
        SUB_0075A3();
        if (poppedEntry.value != 0x007435) return;
        pushAddress(0x007438);
        SUB_0075A3();
        if (poppedEntry.value != 0x007438) return;
        pushAddress(0x00743B);
        SUB_0075A3();
        if (poppedEntry.value != 0x00743B) return;
        pushAddress(0x00743E);
        SUB_0075A3();
        if (poppedEntry.value != 0x00743E) return;
        opINC(0x0058, 1);
        if (myMapper->readCPU(0x0058) >= 0x6B) {
            goto L_00744C;
        }
    }
L_00744C:
    myMapper->writeCPU(0x2001, 0x1A);
    myMapper->writeCPU(0x0058, 0xC1);
    while (true) {
        pushAddress(0x007455);
        SUB_007A7B();
        if (poppedEntry.value != 0x007455) return;
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000D, 0x74);
        myMapper->writeCPU(0x0013, 0x00);
        y = 0x04;
        x = 0x00;
        pushAddress(0x007468);
        SUB_003ABB();
        if (poppedEntry.value != 0x007468) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x007474);
        SUB_0041BC();
        if (poppedEntry.value != 0x007474) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x007480);
        SUB_004149();
        if (poppedEntry.value != 0x007480) return;
        myMapper->writeCPU(0x000E, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000D, 0x8C);
        myMapper->writeCPU(0x0013, 0x01);
        y = 0x00;
        pushAddress(0x007491);
        SUB_003ABB();
        if (poppedEntry.value != 0x007491) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x00749D);
        SUB_0041BC();
        if (poppedEntry.value != 0x00749D) return;
        a = myMapper->readCPU(0x000E);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x000E, a);
        y = 0x00;
        pushAddress(0x0074A9);
        SUB_004149();
        if (poppedEntry.value != 0x0074A9) return;
        y = 0x00;
        do {
            myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xF68A + y));
            opINX(1);
            opINY(1);
            opCMP(y, 0xA8);
        } while (!flgC);
        pushAddress(0x0074BA);
        SUB_0075A3();
        if (poppedEntry.value != 0x0074BA) return;
        pushAddress(0x0074BD);
        SUB_0075A3();
        if (poppedEntry.value != 0x0074BD) return;
        pushAddress(0x0074C0);
        SUB_0075A3();
        if (poppedEntry.value != 0x0074C0) return;
        opINC(0x0058, 1);
        if (myMapper->readCPU(0x0058) >= 0xD0) {
            goto L_0074CE;
        }
    }
L_0074CE:
    myMapper->writeCPU(0x0058, 0x8C);
    while (true) {
        pushAddress(0x0074D2);
        SUB_007A7B();
        if (poppedEntry.value != 0x0074D2) return;
        myMapper->writeCPU(0x000D, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000E, 0xD0);
        myMapper->writeCPU(0x0013, 0x01);
        a = myMapper->readCPU(0x0058);
        opLSR_A(1);
        opAND(0x03);
        x = a;
        y = myMapper->readCPU(0xF0D5 + x);
        myMapper->writeCPU(0x0005, y);
        x = 0x00;
        pushAddress(0x0074EE);
        SUB_003ABB();
        if (poppedEntry.value != 0x0074EE) return;
        a = myMapper->readCPU(0x0058);
        flgC = true;
        opSBC(0x18);
        myMapper->writeCPU(0x000D, a);
        myMapper->writeCPU(0x0013, 0x00);
        y = myMapper->readCPU(0x0005);
        pushAddress(0x0074FE);
        SUB_003ABB();
        if (poppedEntry.value != 0x0074FE) return;
        y = 0x00;
        do {
            myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xF68A + y));
            opINX(1);
            opINY(1);
            opCMP(y, 0xA8);
        } while (!flgC);
        pushAddress(0x00750F);
        SUB_0075A3();
        if (poppedEntry.value != 0x00750F) return;
        pushAddress(0x007512);
        SUB_0075A3();
        if (poppedEntry.value != 0x007512) return;
        opINC(0x0058, 1);
        if (myMapper->readCPU(0x0058) >= 0xF8) {
            goto L_007520;
        }
    }
L_007520:
    myMapper->writeCPU(0x0058, 0xE0);
    while (true) {
        pushAddress(0x007524);
        SUB_007A7B();
        if (poppedEntry.value != 0x007524) return;
        myMapper->writeCPU(0x000D, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x000E, 0xD0);
        myMapper->writeCPU(0x0013, 0x00);
        a = myMapper->readCPU(0x0058);
        opLSR_A(1);
        opAND(0x03);
        x = a;
        y = myMapper->readCPU(0xF0D5 + x);
        myMapper->writeCPU(0x0005, y);
        x = 0x00;
        pushAddress(0x007540);
        SUB_003ABB();
        if (poppedEntry.value != 0x007540) return;
        y = 0x00;
        do {
            myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xF68A + y));
            opINX(1);
            opINY(1);
            opCMP(y, 0xA8);
        } while (!flgC);
        pushAddress(0x007551);
        SUB_0075A3();
        if (poppedEntry.value != 0x007551) return;
        pushAddress(0x007554);
        SUB_0075A3();
        if (poppedEntry.value != 0x007554) return;
        pushAddress(0x007557);
        SUB_0075A3();
        if (poppedEntry.value != 0x007557) return;
        opINC(0x0058, 1);
        if (myMapper->readCPU(0x0058) >= 0xF8) {
            goto L_007565;
        }
    }
L_007565:
    pushAddress(0x007565);
    SUB_007A7B();
    if (poppedEntry.value != 0x007565) return;
    x = 0x00;
    do {
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xF68A + x));
        opINX(1);
        opCMP(x, 0xA8);
    } while (!flgC);
    myMapper->writeCPU(0x0058, 0x64);
    do {
        myMapper->writeCPU(0x0021, 0x01);
    L_00757D:
        if (myMapper->readCPU(0x0021) != 0) {
            wait(1);
            goto L_00757D;
        }
        pushAddress(0x007581);
        SUB_00611E();
        if (poppedEntry.value != 0x007581) return;
        opDEC(0x0058, 1);
    } while (!flgZ);
    do {
        pushAddress(0x007588);
        SUB_0057C5();
        if (poppedEntry.value != 0x007588) return;
        opORA(0x00);
    } while (flgZ);
    popAddress();
}

void game::SUB_007590() {
    if (a != 0x00) {
        goto L_00759D;
    }
    if (myMapper->readCPU(0x0058) != 0) {
        goto L_00759B;
    }
    a = 0xE6;
    popAddress();
    return;
L_00759B:
    a = 0x00;
L_00759D:
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x0058, a);
    popAddress();
}

void game::SUB_0075A3() {
    myMapper->writeCPU(0x0021, 0x01);
L_0075A7:
    if (myMapper->readCPU(0x0021) != 0) {
        wait(1);
        goto L_0075A7;
    }
    pushAddress(0x0075AB);
    SUB_00611E();
    if (poppedEntry.value != 0x0075AB) return;
    popAddress();
}

void game::SUB_00775A() {
    flgC = true;
    a = myMapper->readCPU(0x0034);
    opSBC(myMapper->readCPU(0x002C));
    a = myMapper->readCPU(0x0035);
    opSBC(myMapper->readCPU(0x002D));
    a = myMapper->readCPU(0x0036);
    opSBC(myMapper->readCPU(0x002E));
    a = myMapper->readCPU(0x0037);
    opSBC(myMapper->readCPU(0x002F));
    a = myMapper->readCPU(0x0038);
    opSBC(myMapper->readCPU(0x0030));
    a = myMapper->readCPU(0x0039);
    opSBC(myMapper->readCPU(0x0031));
    a = myMapper->readCPU(0x003A);
    opSBC(myMapper->readCPU(0x0032));
    a = myMapper->readCPU(0x003B);
    opSBC(myMapper->readCPU(0x0033));
    if (flgC) {
        goto L_007786;
    }
    x = 0x07;
    do {
        myMapper->writeCPU((0x0034 + x) & 0x00ff, myMapper->readCPU((0x002C + x) & 0x00ff));
        opDEX(1);
    } while (!flgN);
L_007786:
    flgC = true;
    a = myMapper->readCPU(0x0034);
    opSBC(myMapper->readCPU(0x0024));
    a = myMapper->readCPU(0x0035);
    opSBC(myMapper->readCPU(0x0025));
    a = myMapper->readCPU(0x0036);
    opSBC(myMapper->readCPU(0x0026));
    a = myMapper->readCPU(0x0037);
    opSBC(myMapper->readCPU(0x0027));
    a = myMapper->readCPU(0x0038);
    opSBC(myMapper->readCPU(0x0028));
    a = myMapper->readCPU(0x0039);
    opSBC(myMapper->readCPU(0x0029));
    a = myMapper->readCPU(0x003A);
    opSBC(myMapper->readCPU(0x002A));
    a = myMapper->readCPU(0x003B);
    opSBC(myMapper->readCPU(0x002B));
    x = 0x07;
    do {
        myMapper->writeCPU((0x0034 + x) & 0x00ff, myMapper->readCPU((0x0024 + x) & 0x00ff));
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0077B1() {
    myMapper->writeCPU(0x0052, 0xFF);
    myMapper->writeCPU(0x2000, 0x10);
//L_0077BA:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_0077BA;
//    }
    x = myMapper->readCPU(0x0023);
    x = myMapper->readCPU(0xFA5A + x);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2006, 0x3F);
        myMapper->writeCPU(0x2006, y);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xA7BF + x));
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        opINX(1);
        opINY(1);
    } while (y != 0x10);
//L_0077EB:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_0077EB;
//    }
    x = myMapper->readCPU(0x0023);
    x = myMapper->readCPU(0xFA5A + x);
    do {
        myMapper->writeCPU(0x2006, 0x3F);
        myMapper->writeCPU(0x2006, y);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xA81F + x));
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        opINX(1);
        opINY(1);
        opCMP(y, 0x20);
    } while (!flgZ);
    myMapper->writeCPU(0x2000, 0x90);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x80);
    x = myMapper->readCPU(0x0023);
    a = myMapper->readCPU(0xFA6A + x);
    x = 0xB8;
    do {
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0005, 0x79);
    myMapper->writeCPU(0x0006, 0x9D);
    y = 0x00;
    x = myMapper->readCPU(0x0023);
    do {
        opDEX(1);
        if (flgZ) {
            goto L_007862;
        }
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            pushStatus();
            opINC(0x0005, 1);
            if (flgZ) {
                opINC(0x0006, 1);
            }
            opINC(0x0005, 1);
            if (!flgZ) {
                goto L_00785D;
            }
            opINC(0x0006, 1);
        L_00785D:
            popStatus();
        } while (!flgN);
    } while (flgN);
L_007862:
    myMapper->writeCPU(0x000B, 0x00);
    while (true) {
        y = myMapper->readCPU(0x000B);
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        opLSR_A(1);
        opPHA();
        opAND(0x10);
        myMapper->writeCPU(0x0059, a);
        opPLA();
        opLSR_A(1);
        opAND(0x10);
        myMapper->writeCPU(0x0058, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        opPHA();
        opAND(0x0F);
        opORA(myMapper->readCPU(0x0059));
        myMapper->writeCPU(0x0059, a);
        opPLA();
        opLSR_A(4);
        opORA(myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x0058, a);
        myMapper->writeCPU(0x0008, 0x00);
        a = myMapper->readCPU(0x0059);
        opASL_A(4);
        opROL_M(0x0008, 1);
        opASL_A(1);
        opROL_M(0x0008, 1);
        flgC = false;
        opADC(0x80);
        myMapper->writeCPU(0x0007, a);
        a = 0x20;
        opADC(myMapper->readCPU(0x0008));
        myMapper->writeCPU(0x0008, a);
        a = myMapper->readCPU(0x0058);
        flgC = false;
        opADC(myMapper->readCPU(0x0007));
        myMapper->writeCPU(0x0007, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x0008));
        myMapper->writeCPU(0x0008, a);
        myMapper->writeCPU(0x0009, 0x23);
        myMapper->writeCPU(0x000A, 0x9F);
        opDEY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        y = 0x00;
        opAND(0x1F);
        x = a;
        opINX(1);
        do {
        L_0078C1:
            a = myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y);
            opINC(0x0009, 1);
            if (!flgZ) {
                goto L_0078C9;
            }
            opINC(0x000A, 1);
        L_0078C9:
            if (a != 0xFF) {
                goto L_0078C1;
            }
            opDEX(1);
        } while (!flgZ);
        myMapper->writeCPU(0x000D, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
        opINC(0x0009, 1);
        if (flgZ) {
            opINC(0x000A, 1);
        }
        myMapper->writeCPU(0x000E, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
        opINC(0x0009, 1);
        if (!flgZ) {
            goto L_0078E4;
        }
        opINC(0x000A, 1);
    L_0078E4:
        x = 0x00;
        do {
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x0008));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x0007));
            y = 0x00;
            do {
                a = y;
                flgC = false;
                opADC(myMapper->readCPU(0x0058));
                if (a >= 0x20) {
                    goto L_0078FF;
                }
                myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0009) + (myMapper->readCPU((0x0009 + 1) & 0x00ff) << 8) + y));
            L_0078FF:
                opINY(1);
            } while (y < myMapper->readCPU(0x000D));
            a = myMapper->readCPU(0x000D);
            flgC = false;
            opADC(myMapper->readCPU(0x0009));
            myMapper->writeCPU(0x0009, a);
            a = 0x00;
            opADC(myMapper->readCPU(0x000A));
            myMapper->writeCPU(0x000A, a);
            flgC = false;
            a = 0x20;
            opADC(myMapper->readCPU(0x0007));
            myMapper->writeCPU(0x0007, a);
            a = 0x00;
            opADC(myMapper->readCPU(0x0008));
            myMapper->writeCPU(0x0008, a);
            opINX(1);
            a = x;
            flgC = false;
            opADC(myMapper->readCPU(0x0059));
            if (a >= 0x17) {
                goto L_00792B;
            }
        } while (x < myMapper->readCPU(0x000E));
    L_00792B:
        y = myMapper->readCPU(0x000B);
        if (myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y) & 0x80) {
            goto L_007938;
        }
        opINC(0x000B, 2);
    }
L_007938:
    if (myMapper->readCPU(0x0023) < 0x0D) {
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x40);
        x = myMapper->readCPU(0x0023);
        a = myMapper->readCPU(0xFA5A + x);
        opLSR_A(4);
        x = a;
        a = myMapper->readCPU(0xA7BB + x);
        x = 0x20;
        do {
            myMapper->writeCPU(0x2007, a);
            opDEX(1);
        } while (!flgZ);
    }
    a = myMapper->readCPU(0x0023);
    if (a == 0x0A) {
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x45);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x5B);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
    }
    else {
        if (a != 0x0B) {
            goto L_0079D5;
        }
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x43);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x4F);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x5B);
        a = 0xE6;
        setLoadFlag(a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        if (!flgZ) {
            goto L_007A18;
        }
    L_0079D5:
        if (a != 0x0C) {
            goto L_007A18;
        }
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x49);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x4F);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2006, 0x23);
        myMapper->writeCPU(0x2006, 0x55);
        a = 0xE6;
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
    }
L_007A18:
    myMapper->writeCPU(0x0006, 0x00);
    a = myMapper->readCPU(0x0023);
    flgC = true;
    opSBC(0x01);
    opASL_A(4);
    opROL_M(0x0006, 1);
    opASL_A(1);
    opROL_M(0x0006, 1);
    opASL_A(1);
    opROL_M(0x0006, 1);
    flgC = false;
    opADC(0x7F);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0006);
    opADC(0xA8);
    myMapper->writeCPU(0x0006, a);
    y = 0x00;
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0xC0);
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x40);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0052, 0x00);
    popAddress();
}

void game::SUB_007A7B() {
    x = 0x00;
    do {
        myMapper->writeCPU(0x0700 + x, 0xF8);
        opINX(1);
        a = 0x00;
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_007A94() {
    myMapper->writeCPU(0x00A4, 0xE9);
    myMapper->writeCPU(0x00AC, 0xF0);
    myMapper->writeCPU(0x00AD, 0xF7);
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A6, a);
    a = myMapper->readCPU(0x0025);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A7, a);
    a = myMapper->readCPU(0x0026);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A8, a);
    a = myMapper->readCPU(0x0027);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A9, a);
    a = myMapper->readCPU(0x0028);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00AA, a);
    a = myMapper->readCPU(0x0029);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00AB, a);
    a = myMapper->readCPU(0x003C);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A0, a);
    a = myMapper->readCPU(0x003D);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A1, a);
    a = myMapper->readCPU(0x003E);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A2, a);
    a = myMapper->readCPU(0x003F);
    flgC = false;
    opADC(0xF6);
    myMapper->writeCPU(0x00A3, a);
    if (myMapper->readCPU(0x0022) != 0x02) {
    }
    else {
        myMapper->writeCPU(0x0094, 0xE9);
        myMapper->writeCPU(0x009C, 0xF0);
        myMapper->writeCPU(0x009D, 0xF8);
        a = myMapper->readCPU(0x002C);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0096, a);
        a = myMapper->readCPU(0x002D);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0097, a);
        a = myMapper->readCPU(0x002E);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0098, a);
        a = myMapper->readCPU(0x002F);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0099, a);
        a = myMapper->readCPU(0x0030);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x009A, a);
        a = myMapper->readCPU(0x0031);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x009B, a);
        a = myMapper->readCPU(0x0040);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0090, a);
        a = myMapper->readCPU(0x0041);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0091, a);
        a = myMapper->readCPU(0x0042);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0092, a);
        a = myMapper->readCPU(0x0043);
        flgC = false;
        opADC(0xF6);
        myMapper->writeCPU(0x0093, a);
    }
    x = 0x00;
    do {
        if (myMapper->readCPU((0x00AB + x) & 0x00ff) != 0xF6) {
            goto L_007B52;
        }
        myMapper->writeCPU((0x00AB + x) & 0x00ff, 0xE6);
        opDEX(1);
    } while (x != 0xFB);
L_007B52:
    x = 0x00;
    do {
        if (myMapper->readCPU((0x00A3 + x) & 0x00ff) != 0xF6) {
            goto L_007B63;
        }
        myMapper->writeCPU((0x00A3 + x) & 0x00ff, 0xE6);
        opDEX(1);
    } while (x != 0xFD);
L_007B63:
    x = 0x00;
    do {
        if (myMapper->readCPU((0x009B + x) & 0x00ff) != 0xF6) {
            goto L_007B74;
        }
        myMapper->writeCPU((0x009B + x) & 0x00ff, 0xE6);
        opDEX(1);
    } while (x != 0xFB);
L_007B74:
    x = 0x00;
    do {
        if (myMapper->readCPU((0x0093 + x) & 0x00ff) != 0xF6) {
            goto L_007B85;
        }
        myMapper->writeCPU((0x0093 + x) & 0x00ff, 0xE6);
        opDEX(1);
    } while (x != 0xFD);
L_007B85:
    a = myMapper->readCPU(0x003E);
    opORA(myMapper->readCPU(0x003F));
    if (flgZ) {
        a = myMapper->readCPU(0x003C);
        opORA(myMapper->readCPU(0x003D));
        if (!flgZ) {
            a = myMapper->readCPU(0x003D);
            setLoadFlag(a);
            if (flgZ) {
                goto L_007BC0;
            }
            if (a == 0x01) {
                if (myMapper->readCPU(0x003C) == 0) {
                    goto L_007BC0;
                }
            }
        }
    }
    opCMP(myMapper->readCPU(0x0022), 0x02);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0042);
    opORA(myMapper->readCPU(0x0043));
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0040);
    opORA(myMapper->readCPU(0x0041));
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0041);
    setLoadFlag(a);
    if (!flgZ) {
        opCMP(a, 0x01);
        if (!flgZ) {
            popAddress();
            return;
        }
        if (myMapper->readCPU(0x0040) == 0) {
            goto L_007BC0;
        }
        popAddress();
        return;
    }
L_007BC0:
    SUB_006337();
    return;
}

void game::SUB_007BC3() {
    myMapper->writeCPU(0x2000, 0x94);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x3C);
    a = myMapper->readCPU(0x0078);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2000, 0x90);
    SUB_007F30();
    return;
}

void game::SUB_007BE5() {
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x25);
    a = myMapper->readCPU(0x0078);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x3B);
    a = myMapper->readCPU(0x0079);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    SUB_007F30();
    return;
}

void game::SUB_007C12() {
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x23);
    a = myMapper->readCPU(0x0078);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x2F);
    a = myMapper->readCPU(0x0079);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x3B);
    a = myMapper->readCPU(0x007A);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    SUB_007F30();
    return;
}

void game::SUB_007C54() {
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x29);
    a = myMapper->readCPU(0x0078);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x2F);
    a = myMapper->readCPU(0x0079);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x35);
    a = myMapper->readCPU(0x007A);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    SUB_007F30();
    return;
}

void game::SUB_007C96() {
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xA5);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0078));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xC4);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007A));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0079));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xE3);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007B));
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x02);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007D));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xDC);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007F));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007E));
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xFC);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0080));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x1A);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0082));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0081));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x3A);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0083));
    SUB_007F30();
    return;
}

void game::SUB_007D25() {
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xBB);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0078));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xDC);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0078));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xFD);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0078));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xA4);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0079));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xC3);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0079));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xE2);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0079));
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xE2);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007A));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x03);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007A));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x24);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007A));
    myMapper->writeCPU(0x2006, 0x22);
    myMapper->writeCPU(0x2006, 0xFD);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007B));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x1C);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007B));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x3B);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007B));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xA3);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xC2);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xBC);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007D));
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xDD);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007D));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x02);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007E));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007E));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x1D);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007F));
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0x3C);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x007F));
    SUB_007F30();
    return;
}

void game::nmi() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    if (myMapper->readCPU(0x0053) != 0) {
        SUB_007F4A();
        return;
    }
    a = myMapper->readCPU(0x0052);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_007F44();
        return;
    }
    a = myMapper->readCPU(0x0021);
    setLoadFlag(a);
    if (flgZ) {
        SUB_007F44();
        return;
    }
    opDEC(0x0021, 1);
    if (!flgZ) {
        SUB_007F44();
        return;
    }
    if (myMapper->readCPU(0x0023) == 0) {
        SUB_007F3A();
        return;
    }
    if (myMapper->readCPU(0x0055) == 0) {
        goto L_007E83;
    }
    SUB_007F30();
    return;
L_007E83:
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x60);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00AE));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00AD));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00AC));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00AB));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00AA));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A9));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A8));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A7));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A6));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A5));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A4));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A3));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A2));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A1));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x009F));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x009D));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x009C));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x009B));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0096));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0095));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0094));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0093));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0092));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0091));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0090));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x008F));
    indirectJump(myMapper->readCPU(0x0076) + (myMapper->readCPU((0x0076 + 1) & 0x00ff) << 8));
}

void game::SUB_007F30() {
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    opINC(0x0004, 1);
    SUB_007F3A();
    return;
}

void game::SUB_007F3A() {
    myMapper->writeCPU(0x2003, 0x00);
    a = 0x07;
    myMapper->writeCPU(0x4014, a);
    SUB_007F44();
    return;
}

void game::SUB_007F44() {
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    return;
}

void game::SUB_007F4A() {
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x0C);
    x = 0x08;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xCF92 + x));
        opDEX(1);
    } while (!flgN);
    opDEC(0x0021, 1);
    SUB_007F30();
    return;
}

void game::reset() {
    flgI = true;
    s = 0xFF;
    myMapper->writeCPU(0x2000, 0x00);
//L_007F6D:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_007F6D;
//    }
//L_007F72:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_007F72;
//    }
    myMapper->writeCPU(0x2000, 0x90);
    a = 0x00;
    x = a;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        myMapper->writeCPU(0x0100 + x, a);
        myMapper->writeCPU(0x0200 + x, a);
        myMapper->writeCPU(0x0300 + x, a);
        myMapper->writeCPU(0x0400 + x, a);
        myMapper->writeCPU(0x0500 + x, a);
        myMapper->writeCPU(0x0600 + x, a);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x2001, 0x01);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    a = 0xE6;
    x = 0x00;
    do {
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        myMapper->writeCPU(0x2007, a);
        opINX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x2001, 0x1E);
    myMapper->writeCPU(0x0076, 0x30);
    myMapper->writeCPU(0x0077, 0xFF);
    SUB_004C21();
    return;
}

void game::indirectJump(Uint16 target) {
    switch (target) {
    case 0xFBC3:
        SUB_007BC3();
        break;
    case 0xFBE5:
        SUB_007BE5();
        break;
    case 0xFC12:
        SUB_007C12();
        break;
    case 0xFC54:
        SUB_007C54();
        break;
    case 0xFC96:
        SUB_007C96();
        break;
    case 0xFD25:
        SUB_007D25();
        break;
    case 0xFF30:
        SUB_007F30();
        break;
    case 0x840C:
        SUB_00040C();
        break;
    case 0x89D2:
        SUB_0009D2();
        break;
    case 0x8A71:
        SUB_000A71();
        break;
    case 0x8B07:
        SUB_000B07();
        break;
    case 0x8B23:
        SUB_000B23();
        break;
    case 0x8B8F:
        SUB_000B8F();
        break;
    case 0x8BA0:
        SUB_000BA0();
        break;
    case 0x8C19:
        SUB_000C19();
        break;
    case 0x8C85:
        SUB_000C85();
        break;
    case 0x8C9E:
        SUB_000C9E();
        break;
    case 0x8CD5:
        SUB_000CD5();
        break;
    case 0x8D38:
        SUB_000D38();
        break;
    case 0x8E0D:
        SUB_000E0D();
        break;
    case 0x8E7E:
        SUB_000E7E();
        break;
    case 0x8F3E:
        SUB_000F3E();
        break;
    case 0x901F:
        SUB_00101F();
        break;
    case 0x91B3:
        SUB_0011B3();
        break;
    case 0x953A:
        SUB_00153A();
        break;
    case 0x9599:
        SUB_001599();
        break;
    case 0x95EE:
        SUB_0015EE();
        break;
    case 0x9768:
        SUB_001768();
        break;
    case 0x97A4:
        SUB_0017A4();
        break;
    case 0x9912:
        SUB_001912();
        break;
    case 0xC5E4:
        SUB_0045E4();
        break;
    case 0xC5EE:
        SUB_0045EE();
        break;
    case 0xC601:
        SUB_004601();
        break;
    case 0xC622:
        SUB_004622();
        break;
    case 0xC62C:
        SUB_00462C();
        break;
    case 0xC701:
        SUB_004701();
        break;
    case 0xC70B:
        SUB_00470B();
        break;
    case 0xC733:
        SUB_004733();
        break;
    case 0xC7AD:
        SUB_0047AD();
        break;
    case 0xC7D3:
        SUB_0047D3();
        break;
    case 0xC7F0:
        SUB_0047F0();
        break;
    case 0xC87F:
        SUB_00487F();
        break;
    case 0xC8A3:
        SUB_0048A3();
        break;
    case 0xC8B8:
        SUB_0048B8();
        break;
    case 0xC8E9:
        SUB_0048E9();
        break;
    case 0xC8F9:
        SUB_0048F9();
        break;
    case 0xC908:
        SUB_004908();
        break;
    case 0xC919:
        SUB_004919();
        break;
    case 0xC93E:
        SUB_00493E();
        break;
    case 0xC966:
        SUB_004966();
        break;
    case 0xCA89:
        SUB_004A89();
        break;
    case 0xCA9C:
        SUB_004A9C();
        break;
    case 0xCAAE:
        SUB_004AAE();
        break;
    case 0xCAC1:
        SUB_004AC1();
        break;
    case 0xCAD0:
        SUB_004AD0();
        break;
    case 0xE705:
        SUB_006705();
        break;
    case 0xE718:
        SUB_006718();
        break;
    case 0xE724:
        SUB_006724();
        break;
    case 0xE730:
        SUB_006730();
        break;
    case 0xE73C:
        SUB_00673C();
        break;
    case 0xE748:
        SUB_006748();
        break;
    case 0xE772:
        SUB_006772();
        break;
    case 0xE7A1:
        SUB_0067A1();
        break;
    case 0xE7D0:
        SUB_0067D0();
        break;
    case 0xE7F7:
        SUB_0067F7();
        break;
    case 0xE820:
        SUB_006820();
        break;
    case 0xE851:
        SUB_006851();
        break;
    case 0xE85D:
        SUB_00685D();
        break;
    case 0xE887:
        SUB_006887();
        break;
    case 0xE8AB:
        SUB_0068AB();
        break;
    case 0xE8D4:
        SUB_0068D4();
        break;
    case 0xE8F7:
        SUB_0068F7();
        break;
    case 0xAF05:
        SUB_002F05();
        break;
    case 0xAF06:
        SUB_002F06();
        break;
    case 0xAF29:
        SUB_002F29();
        break;
    case 0xAF40:
        SUB_002F40();
        break;
    case 0xAF94:
        SUB_002F94();
        break;
    case 0xAFB7:
        SUB_002FB7();
        break;
    case 0xAFF9:
        SUB_002FF9();
        break;
    case 0xB027:
        SUB_003027();
        break;
    case 0xB030:
        SUB_003030();
        break;
    case 0xB039:
        SUB_003039();
        break;
    case 0xB042:
        SUB_003042();
        break;
    case 0xB057:
        SUB_003057();
        break;
    case 0xB0BC:
        SUB_0030BC();
        break;
    case 0xB139:
        SUB_003139();
        break;
    case 0xB142:
        SUB_003142();
        break;
    case 0xB14B:
        SUB_00314B();
        break;
    case 0xB154:
        SUB_003154();
        break;
    case 0xB19D:
        SUB_00319D();
        break;
    case 0xB1AB:
        SUB_0031AB();
        break;
    case 0xB1E2:
        SUB_0031E2();
        break;
    case 0xB1EB:
        SUB_0031EB();
        break;
    case 0xB1FB:
        SUB_0031FB();
        break;
    case 0xB204:
        SUB_003204();
        break;
    case 0xB248:
        SUB_003248();
        break;
    case 0xB258:
        SUB_003258();
        break;
    case 0xB27D:
        SUB_00327D();
        break;
    case 0xB286:
        SUB_003286();
        break;
    case 0xB2F0:
        SUB_0032F0();
        break;
    case 0xB2FE:
        SUB_0032FE();
        break;
    case 0xB309:
        SUB_003309();
        break;
    case 0xB322:
        SUB_003322();
        break;
    case 0xB38F:
        SUB_00338F();
        break;
    case 0xB3BD:
        SUB_0033BD();
        break;
    case 0xB422:
        SUB_003422();
        break;
    case 0xB479:
        SUB_003479();
        break;
    case 0xB4F8:
        SUB_0034F8();
        break;
    case 0xB55B:
        SUB_00355B();
        break;
    case 0xB614:
        SUB_003614();
        break;
    case 0xB652:
        SUB_003652();
        break;
    case 0xB658:
        SUB_003658();
        break;
    case 0xB681:
        SUB_003681();
        break;
    case 0xB7DD:
        SUB_0037DD();
        break;
    case 0xB7DE:
        SUB_0037DE();
        break;
    case 0xB7E7:
        SUB_0037E7();
        break;
    case 0xB7ED:
        SUB_0037ED();
        break;
    case 0xB7FF:
        SUB_0037FF();
        break;
    case 0xB81F:
        SUB_00381F();
        break;
    case 0xB85A:
        SUB_00385A();
        break;
    case 0xB876:
        SUB_003876();
        break;
    case 0xB8A6:
        SUB_0038A6();
        break;
    case 0xB8A7:
        SUB_0038A7();
        break;
    default:
        bool test = false;
        Uint16 tmp = target;
    }
}
