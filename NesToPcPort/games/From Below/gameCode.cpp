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

void game::reset() {
    flgI = true;
    flgD = false;
    myMapper->writeCPU(0x4017, 0x40);
    x = 0xFF;
    s = x;
    opINX(1);
    myMapper->writeCPU(0x2001, x);
    myMapper->writeCPU(0x4010, x);
    myMapper->writeCPU(0x2000, x);
    opBIT(myMapper->readCPU(0x2002));
    do {
        opBIT(myMapper->readCPU(0x2002));
        wait();
    } while (!flgN);
    do {
        opBIT(myMapper->readCPU(0x2002));
        wait();
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, x);
    a = 0x0F;
    x = 0x20;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    a = x;
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, a);
    y = 0x10;
    do {
        do {
            myMapper->writeCPU(0x2007, a);
            opINX(1);
        } while (!flgZ);
        opDEY(1);
    } while (!flgZ);
    a = x;
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
    a = 0x04;
    pushAddress(0x000064);
    SUB_000276();
    if (poppedEntry.value != 0x000064) return;
    pushAddress(0x000067);
    SUB_00024B();
    if (poppedEntry.value != 0x000067) return;
    pushAddress(0x00006A);
    SUB_0002A3();
    if (poppedEntry.value != 0x00006A) return;
    pushAddress(0x00006D);
    SUB_00377D();
    if (poppedEntry.value != 0x00006D) return;
    pushAddress(0x000070);
    SUB_003352();
    if (poppedEntry.value != 0x000070) return;
    myMapper->writeCPU(0x00BC, 0x00);
    myMapper->writeCPU(0x00BD, 0x08);
    a = 0x80;
    myMapper->writeCPU(0x0016, a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0018, 0x06);
    a = myMapper->readCPU(0x0001);
L_000088:
    if (a == myMapper->readCPU(0x0001)) {
        wait();
        goto L_000088;
    }
    x = 0x34;
    y = 0x18;
    do {
        do {
            opDEX(1);
        } while (!flgZ);
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x2002);
    opAND(0x80);
    myMapper->writeCPU(0x0000, a);
    pushAddress(0x00009D);
    SUB_00027D();
    if (poppedEntry.value != 0x00009D) return;
    a = 0x00;
    x = 0x00;
    pushAddress(0x0000A4);
    SUB_000502();
    if (poppedEntry.value != 0x0000A4) return;
    x = 0xA0;
    y = 0xB7;
    a = myMapper->readCPU(0x0000);
    pushAddress(0x0000AD);
    SUB_000A9C();
    if (poppedEntry.value != 0x0000AD) return;
    x = 0x73;
    y = 0xD5;
    pushAddress(0x0000B4);
    SUB_000E83();
    if (poppedEntry.value != 0x0000B4) return;
    a = 0xFD;
    myMapper->writeCPU(0x0019, a);
    myMapper->writeCPU(0x001A, a);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    SUB_002D9D();
    return;
}

void game::nmi() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x0018);
    opAND(0x18);
    if (flgZ) {
    }
    else {
        myMapper->writeCPU(0x4014, 0x02);
        if (myMapper->readCPU(0x0007) == 0) {
        }
        else {
            x = 0x00;
            myMapper->writeCPU(0x0007, x);
            myMapper->writeCPU(0x2006, 0x3F);
            myMapper->writeCPU(0x2006, x);
            y = myMapper->readCPU(0x01C0);
            a = myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x2007, a);
            x = a;
            y = myMapper->readCPU(0x01C1);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01C2);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01C3);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01C5);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01C6);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01C7);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01C9);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01CA);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01CB);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01CD);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01CE);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01CF);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x0008) + (myMapper->readCPU((0x0008 + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01D1);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01D2);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01D3);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01D5);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01D6);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01D7);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01D9);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01DA);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01DB);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(0x2007, x);
            y = myMapper->readCPU(0x01DD);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01DE);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x01DF);
            myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000A) + (myMapper->readCPU((0x000A + 1) & 0x00ff) << 8) + y));
        }
        if (myMapper->readCPU(0x0003) != 0) {
            myMapper->writeCPU(0x0003, 0x00);
            if (myMapper->readCPU(0x0006) != 0) {
                pushAddress(0x0001D8);
                SUB_00050F();
                if (poppedEntry.value != 0x0001D8) return;
            }
        }
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2005, myMapper->readCPU(0x000C));
        myMapper->writeCPU(0x2005, myMapper->readCPU(0x000D));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0016));
    }
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x0018));
    opINC(0x0001, 1);
    opINC(0x0002, 1);
    if (myMapper->readCPU(0x0002) != 0x06) {
        goto L_000205;
    }
    myMapper->writeCPU(0x0002, 0x00);
L_000205:
    pushAddress(0x000205);
    SUB_000BC3();
    if (poppedEntry.value != 0x000205) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    return;
}

void game::SUB_000216() {
    myMapper->writeCPU(0x0020, a);
    y = 0x00;
    do {
        myMapper->writeCPU(0x01C0 + x, myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y));
        opINX(1);
        opINY(1);
        opDEC(0x0020, 1);
    } while (!flgZ);
    opINC(0x0007, 1);
    popAddress();
}

void game::SUB_000228() {
    myMapper->writeCPU(0x001E, a);
    myMapper->writeCPU(0x001F, x);
    x = 0x00;
    a = 0x10;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000216();
        return;
    }
    SUB_000232();
    return;
}

void game::SUB_000232() {
    myMapper->writeCPU(0x001E, a);
    myMapper->writeCPU(0x001F, x);
    x = 0x10;
    a = x;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000216();
        return;
    }
    myMapper->writeCPU(0x001E, a);
    pushAddress(0x00023D);
    SUB_003635();
    if (poppedEntry.value != 0x00023D) return;
    opAND(0x1F);
    x = a;
    myMapper->writeCPU(0x01C0 + x, myMapper->readCPU(0x001E));
    opINC(0x0007, 1);
    popAddress();
}

void game::SUB_00024B() {
    a = 0x0F;
    x = 0x00;
    do {
        myMapper->writeCPU(0x01C0 + x, a);
        opINX(1);
    } while (x != 0x20);
    myMapper->writeCPU(0x0007, x);
    popAddress();
}

void game::SUB_00025A() {
    x = a;
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x860B + x));
    a = myMapper->readCPU(0x8614 + x);
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x0007, a);
    popAddress();
}

void game::SUB_000268() {
    x = a;
    myMapper->writeCPU(0x0008, myMapper->readCPU(0x860B + x));
    a = myMapper->readCPU(0x8614 + x);
    myMapper->writeCPU(0x0009, a);
    myMapper->writeCPU(0x0007, a);
    popAddress();
}

void game::SUB_000276() {
    pushAddress(0x000276);
    SUB_00025A();
    if (poppedEntry.value != 0x000276) return;
    a = x;
    SUB_000268();
    return;
}

void game::SUB_00027D() {
    a = myMapper->readCPU(0x0018);
    opAND(0xE7);
    myMapper->writeCPU(0x0018, a);
    SUB_000365();
    return;
}

void game::SUB_000286() {
    a = myMapper->readCPU(0x0018);
    opORA(0x18);
    myMapper->writeCPU(0x0018, a);
    SUB_000365();
    return;
}

void game::SUB_0002A3() {
    x = 0x00;
    myMapper->writeCPU(0x0029, x);
    a = 0xFF;
    do {
        myMapper->writeCPU(0x0200 + x, a);
        opINX(4);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0002B3() {
    opAND(0xFC);
    myMapper->writeCPU(0x0029, a);
    popAddress();
}

void game::SUB_0002CF() {
    x = myMapper->readCPU(0x0029);
    myMapper->writeCPU(0x0202 + x, a);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0201 + x, a);
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0203 + x, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x00BC);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x00BC, a);
    if (!flgC) {
        goto L_0002F2;
    }
    opINC(0x00BD, 1);
L_0002F2:
    a = x;
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0029, a);
    popAddress();
}

void game::SUB_000365() {
    myMapper->writeCPU(0x0003, 0x01);
    a = myMapper->readCPU(0x0001);
L_00036B:
    if (a == myMapper->readCPU(0x0001)) {
		wait();
        goto L_00036B;
    }
    popAddress();
}

void game::SUB_000370() {
    y = a;
    myMapper->writeCPU(0x001F, x);
    myMapper->writeCPU(0x001E, 0x00);
    myMapper->writeCPU(0x0020, myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    if (!flgZ) {
        goto L_000380;
    }
    opINC(0x001F, 1);
    do {
        do {
        L_000380:
            a = myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y);
            opINY(1);
            if (!flgZ) {
                goto L_000387;
            }
            opINC(0x001F, 1);
        L_000387:
            opCMP(a, myMapper->readCPU(0x0020));
            if (flgZ) {
                goto L_000392;
            }
            myMapper->writeCPU(0x2007, a);
            myMapper->writeCPU(0x0021, a);
        } while (!flgZ);
    L_000392:
        a = myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0003A6;
        }
        opINY(1);
        if (!flgZ) {
            goto L_00039B;
        }
        opINC(0x001F, 1);
    L_00039B:
        x = a;
        a = myMapper->readCPU(0x0021);
        do {
            myMapper->writeCPU(0x2007, a);
            opDEX(1);
        } while (!flgZ);
    } while (flgZ);
L_0003A6:
    popAddress();
}

void game::SUB_0003A7() {
    myMapper->writeCPU(0x001E, a);
    if (x == 0) {
        a = myMapper->readCPU(0x001E);
        if (a >= 0xF0) {
            goto L_0003BA;
        }
        myMapper->writeCPU(0x000D, a);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x001E, a);
        if (flgZ) {
            goto L_0003C5;
        }
    }
L_0003BA:
    flgC = true;
    a = myMapper->readCPU(0x001E);
    opSBC(0xF0);
    myMapper->writeCPU(0x000D, a);
    myMapper->writeCPU(0x001E, 0x02);
L_0003C5:
    pushAddress(0x0003C5);
    SUB_0033DB();
    if (poppedEntry.value != 0x0003C5) return;
    myMapper->writeCPU(0x000C, a);
    a = x;
    opAND(0x01);
    opORA(myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x001E, a);
    a = myMapper->readCPU(0x0016);
    opAND(0xFC);
    opORA(myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x0016, a);
    popAddress();
}

void game::SUB_000403() {
    opAND(0x01);
    opASL_A(3);
    myMapper->writeCPU(0x001E, a);
    a = myMapper->readCPU(0x0016);
    opAND(0xF7);
    opORA(myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x0016, a);
    popAddress();
}

void game::SUB_000475() {
    opAND(0x03);
    x = a;
    x = myMapper->readCPU(0x8482 + x);
    pushAddress(0x00047C);
    SUB_003635();
    if (poppedEntry.value != 0x00047C) return;
    SUB_000EC4();
    return;
}

void game::SUB_000487() {
    y = a;
    x = 0x03;
    do {
        a = 0x01;
        myMapper->writeCPU(0x4016, a);
        myMapper->writeCPU((0x001E + x) & 0x00ff, a);
        myMapper->writeCPU(0x4016, 0x00);
        myMapper->writeCPU(0x001E, 0x08);
        do {
            a = myMapper->readCPU(0x4016 + y);
            opLSR_A(1);
            opROL_M((0x001E + x) & 0x00ff, 1);
        } while (!flgC);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x001F);
    if (a != myMapper->readCPU(0x0020)) {
        if (a == myMapper->readCPU(0x0021)) {
            goto L_0004B1;
        }
        a = myMapper->readCPU(0x0020);
    }
L_0004B1:
    myMapper->writeCPU(0x0010 + y, a);
    x = a;
    opEOR(myMapper->readCPU(0x0012 + y));
    opAND(myMapper->readCPU(0x0010 + y));
    myMapper->writeCPU(0x0014 + y, a);
    a = x;
    myMapper->writeCPU(0x0012 + y, a);
    x = 0x00;
    popAddress();
}

void game::SUB_000502() {
    myMapper->writeCPU(0x0004, a);
    myMapper->writeCPU(0x0005, x);
    opORA(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0006, a);
    popAddress();
}

void game::SUB_00050F() {
    y = 0x00;
    while (true) {
        while (true) {
            a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            if (a >= 0x40) {
                goto L_00052A;
            }
            myMapper->writeCPU(0x2006, a);
            a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            myMapper->writeCPU(0x2006, a);
            a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            myMapper->writeCPU(0x2007, a);
        }
    L_00052A:
        x = a;
        a = myMapper->readCPU(0x0016);
        if (x < 0x80) {
            goto L_000539;
        }
        if (x == 0xFF) {
            goto L_00055F;
        }
        opORA(0x04);
        if (!flgZ) {
            goto L_00053B;
        }
    L_000539:
        opAND(0xFB);
    L_00053B:
        myMapper->writeCPU(0x2000, a);
        a = x;
        opAND(0x3F);
        myMapper->writeCPU(0x2006, a);
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x2006, a);
        a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        x = a;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0004) + (myMapper->readCPU((0x0004 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            myMapper->writeCPU(0x2007, a);
            opDEX(1);
        } while (!flgZ);
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0016));
    }
L_00055F:
    popAddress();
}

void game::SUB_000560() {
    myMapper->writeCPU(0x2006, x);
    myMapper->writeCPU(0x2006, a);
    popAddress();
}

void game::SUB_0005A1() {
    myMapper->writeCPU(0x0020, a);
    myMapper->writeCPU(0x0021, x);
    pushAddress(0x0005A5);
    SUB_0033DB();
    if (poppedEntry.value != 0x0005A5) return;
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x0026, x);
    pushAddress(0x0005AC);
    SUB_0033DB();
    if (poppedEntry.value != 0x0005AC) return;
    myMapper->writeCPU(0x0027, a);
    myMapper->writeCPU(0x0028, x);
    x = 0x00;
    while (myMapper->readCPU(0x0021) != 0) {
        pushAddress(0x0005B9);
        SUB_0005C9();
        if (poppedEntry.value != 0x0005B9) return;
        opDEC(0x0021, 1);
        opINC(0x0026, 1);
        opINC(0x0028, 1);
    }
    x = myMapper->readCPU(0x0020);
    setLoadFlag(x);
    if (flgZ) {
        SUB_0005D3();
        return;
    }
    SUB_0005C9();
    return;
}

void game::SUB_0005C9() {
    y = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0027) + (myMapper->readCPU((0x0027 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x0025) + (myMapper->readCPU((0x0025 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    SUB_0005D3();
    return;
}

void game::SUB_0005D3() {
    popAddress();
}

void game::SUB_0005D4() {
    myMapper->writeCPU(0x0020, a);
    myMapper->writeCPU(0x0021, x);
    pushAddress(0x0005D8);
    SUB_003635();
    if (poppedEntry.value != 0x0005D8) return;
    myMapper->writeCPU(0x001E, a);
    pushAddress(0x0005DD);
    SUB_0033DB();
    if (poppedEntry.value != 0x0005DD) return;
    myMapper->writeCPU(0x0027, a);
    myMapper->writeCPU(0x0028, x);
    x = 0x00;
    while (myMapper->readCPU(0x0021) != 0) {
        pushAddress(0x0005EA);
        SUB_0005F8();
        if (poppedEntry.value != 0x0005EA) return;
        opDEC(0x0021, 1);
        opINC(0x0028, 1);
    }
    x = myMapper->readCPU(0x0020);
    setLoadFlag(x);
    if (flgZ) {
        SUB_000602();
        return;
    }
    SUB_0005F8();
    return;
}

void game::SUB_0005F8() {
    y = 0x00;
    a = myMapper->readCPU(0x001E);
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0027) + (myMapper->readCPU((0x0027 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    SUB_000602();
    return;
}

void game::SUB_000602() {
    popAddress();
}

void game::SUB_000603() {
    x = a;
    do {
        pushAddress(0x000604);
        SUB_000365();
        if (poppedEntry.value != 0x000604) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0006DD() {
    myMapper->writeCPU(0x0700, 0xFF);
    x = 0x07;
    a = 0x00;
    SUB_000502();
    return;
}

void game::SUB_0006E9() {
    y = myMapper->readCPU(0x002A);
    myMapper->writeCPU(0x0701 + y, a);
    a = x;
    flgC = false;
    opADC(0x40);
    myMapper->writeCPU(0x0700 + y, a);
    SUB_0006F5();
    return;
}

void game::SUB_0006F5() {
    pushAddress(0x0006F5);
    SUB_003635();
    if (poppedEntry.value != 0x0006F5) return;
    myMapper->writeCPU(0x0021, a);
    y = myMapper->readCPU(0x002A);
    myMapper->writeCPU(0x0702 + y, a);
    pushAddress(0x0006FF);
    SUB_0033DB();
    if (poppedEntry.value != 0x0006FF) return;
    myMapper->writeCPU(0x001E, a);
    myMapper->writeCPU(0x001F, x);
    x = myMapper->readCPU(0x002A);
    opINX(3);
    y = 0x00;
    do {
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y));
        opINX(1);
        opINY(1);
    } while (y != myMapper->readCPU(0x0021));
    myMapper->writeCPU(0x0700 + x, 0xFF);
    myMapper->writeCPU(0x002A, x);
    popAddress();
}

void game::SUB_000720() {
    y = myMapper->readCPU(0x002A);
    myMapper->writeCPU(0x0701 + y, a);
    a = x;
    flgC = false;
    opADC(0x80);
    myMapper->writeCPU(0x0700 + y, a);
    SUB_0006F5();
    return;
}

void game::SUB_00072F() {
    y = myMapper->readCPU(0x002A);
    myMapper->writeCPU(0x0701 + y, a);
    myMapper->writeCPU(0x0700 + y, x);
    opINY(2);
    myMapper->writeCPU(0x001E, y);
    pushAddress(0x00073C);
    SUB_003635();
    if (poppedEntry.value != 0x00073C) return;
    y = myMapper->readCPU(0x001E);
    myMapper->writeCPU(0x0700 + y, a);
    opINY(1);
    myMapper->writeCPU(0x0700 + y, 0xFF);
    myMapper->writeCPU(0x002A, y);
    popAddress();
}

void game::SUB_00074D() {
    myMapper->writeCPU(0x002A, 0x00);
    myMapper->writeCPU(0x0700, 0xFF);
    popAddress();
}

void game::SUB_000757() {
    y = a;
    a = myMapper->readCPU(0x0014 + y);
    x = 0x00;
    popAddress();
}

void game::SUB_000850() {
    opAND(0xF8);
    x = 0x00;
    myMapper->writeCPU(0x001F, x);
    opASL_A(1);
    opROL_M(0x001F, 1);
    opASL_A(1);
    opROL_M(0x001F, 1);
    myMapper->writeCPU(0x001E, a);
    pushAddress(0x00085E);
    SUB_003635();
    if (poppedEntry.value != 0x00085E) return;
    opLSR_A(3);
    opORA(myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x001E, a);
    pushAddress(0x000868);
    SUB_003635();
    if (poppedEntry.value != 0x000868) return;
    opAND(0x03);
    opASL_A(2);
    opORA(0x20);
    opORA(myMapper->readCPU(0x001F));
    x = a;
    a = myMapper->readCPU(0x001E);
    popAddress();
}

void game::SUB_000A9C() {
    myMapper->writeCPU(0x0165, x);
    myMapper->writeCPU(0x0166, y);
    myMapper->writeCPU(0x001B, x);
    myMapper->writeCPU(0x001C, y);
    if (a == 0) {
        goto L_000AAB;
    }
    a = 0x40;
L_000AAB:
    myMapper->writeCPU(0x0164, a);
    pushAddress(0x000AAE);
    SUB_000AF4();
    if (poppedEntry.value != 0x000AAE) return;
    y = 0x01;
    myMapper->writeCPU(0x0167, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0168, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x016D, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x016E, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    a = 0xFF;
    myMapper->writeCPU(0x0161, a);
    myMapper->writeCPU(0x0163, a);
    myMapper->writeCPU(0x4015, 0x0F);
    myMapper->writeCPU(0x4008, 0x80);
    myMapper->writeCPU(0x400F, 0x00);
    a = 0x30;
    myMapper->writeCPU(0x4000, a);
    myMapper->writeCPU(0x4004, a);
    myMapper->writeCPU(0x400C, a);
    a = 0x08;
    myMapper->writeCPU(0x4001, a);
    myMapper->writeCPU(0x4005, a);
    SUB_000AF4();
    return;
}

void game::SUB_000AF4() {
    a = 0x00;
    myMapper->writeCPU(0x014A, a);
    myMapper->writeCPU(0x016F, a);
    x = 0x37;
    do {
        a = 0x00;
        myMapper->writeCPU(0x0114 + x, a);
        myMapper->writeCPU(0x010F + x, a);
        myMapper->writeCPU(0x010A + x, a);
        myMapper->writeCPU(0x0123 + x, a);
        myMapper->writeCPU(0x0128 + x, 0x30);
        opINX(1);
    } while (x != 0x3C);
    x = 0x00;
    do {
        myMapper->writeCPU(0x0116 + x, 0x94);
        myMapper->writeCPU(0x0121 + x, 0x8F);
        a = 0x00;
        myMapper->writeCPU(0x010B + x, a);
        myMapper->writeCPU(0x0100 + x, a);
        opINX(1);
    } while (x != 0x0B);
    SUB_000E7D();
    return;
}

void game::SUB_000B32() {
    myMapper->writeCPU(0x001B, myMapper->readCPU(0x0165));
    x = myMapper->readCPU(0x0166);
    myMapper->writeCPU(0x001C, x);
    y = 0x00;
    if (a < myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y)) {
        opASL_A(1);
        myMapper->writeCPU(0x001B, a);
        opASL_A(1);
        x = a;
        opASL_A(1);
        opADC(myMapper->readCPU(0x001B));
        myMapper->writeCPU(0x001B, x);
        opADC(myMapper->readCPU(0x001B));
        opADC(0x05);
        y = a;
        myMapper->writeCPU(0x001B, myMapper->readCPU(0x0165));
        pushAddress(0x000B56);
        SUB_000AF4();
        if (poppedEntry.value != 0x000B56) return;
        x = 0x37;
        do {
            myMapper->writeCPU(0x0100 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x0105 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
            opINY(1);
            a = 0x00;
            myMapper->writeCPU(0x0114 + x, a);
            myMapper->writeCPU(0x010F + x, a);
            myMapper->writeCPU(0x010A + x, a);
            myMapper->writeCPU(0x0123 + x, a);
            myMapper->writeCPU(0x0128 + x, 0x30);
            opINX(1);
        } while (x != 0x3C);
        if (myMapper->readCPU(0x0164) == 0) {
            goto L_000B86;
        }
        opINY(2);
    L_000B86:
        myMapper->writeCPU(0x0169, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x016A, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x016B, 0x00);
        a = 0x06;
        myMapper->writeCPU(0x016C, a);
        myMapper->writeCPU(0x014A, a);
    }
    popAddress();
}

void game::SUB_000B9F() {
    x = a;
    setLoadFlag(x);
    if (flgZ) {
        goto L_000BBA;
    }
    pushAddress(0x000BA2);
    SUB_000E7D();
    if (poppedEntry.value != 0x000BA2) return;
    a = 0x00;
    myMapper->writeCPU(0x0100, a);
    myMapper->writeCPU(0x0103, a);
    myMapper->writeCPU(0x0106, a);
    myMapper->writeCPU(0x0109, a);
    a = myMapper->readCPU(0x014A);
    opORA(0x80);
    if (!flgZ) {
        goto L_000BBF;
    }
L_000BBA:
    a = myMapper->readCPU(0x014A);
    opAND(0x7F);
L_000BBF:
    myMapper->writeCPU(0x014A, a);
    popAddress();
}

void game::SUB_000BC3() {
    a = myMapper->readCPU(0x001B);
    opPHA();
    a = myMapper->readCPU(0x001C);
    opPHA();
    a = myMapper->readCPU(0x014A);
    setLoadFlag(a);
    if (!flgN) {
        if (!flgZ) {
            goto L_000BD3;
        }
    }
    goto L_000C76;
L_000BD3:
    flgC = false;
    a = myMapper->readCPU(0x016B);
    opADC(myMapper->readCPU(0x0169));
    myMapper->writeCPU(0x016B, a);
    a = myMapper->readCPU(0x016C);
    opADC(myMapper->readCPU(0x016A));
    if (a < myMapper->readCPU(0x014A)) {
        myMapper->writeCPU(0x016C, a);
    }
    else {
        flgC = true;
        opSBC(myMapper->readCPU(0x014A));
        myMapper->writeCPU(0x016C, a);
        x = 0x37;
        pushAddress(0x000BF7);
        SUB_000DCF();
        if (poppedEntry.value != 0x000BF7) return;
        if (flgC) {
            x = 0x00;
            a = myMapper->readCPU(0x0146);
            pushAddress(0x000C01);
            SUB_000D7C();
            if (poppedEntry.value != 0x000C01) return;
            myMapper->writeCPU(0x015F, a);
        }
        x = 0x38;
        pushAddress(0x000C09);
        SUB_000DCF();
        if (poppedEntry.value != 0x000C09) return;
        if (flgC) {
            x = 0x03;
            a = myMapper->readCPU(0x0147);
            pushAddress(0x000C13);
            SUB_000D7C();
            if (poppedEntry.value != 0x000C13) return;
            myMapper->writeCPU(0x0160, a);
        }
        x = 0x39;
        pushAddress(0x000C1B);
        SUB_000DCF();
        if (poppedEntry.value != 0x000C1B) return;
        if (flgC) {
            x = 0x06;
            a = myMapper->readCPU(0x0148);
            pushAddress(0x000C25);
            SUB_000D7C();
            if (poppedEntry.value != 0x000C25) return;
        }
        x = 0x3A;
        pushAddress(0x000C2A);
        SUB_000DCF();
        if (poppedEntry.value != 0x000C2A) return;
        if (flgC) {
            x = 0x09;
            a = myMapper->readCPU(0x0149);
            pushAddress(0x000C34);
            SUB_000D7C();
            if (poppedEntry.value != 0x000C34) return;
            myMapper->writeCPU(0x0162, a);
        }
    }
    x = 0x00;
    do {
        if (myMapper->readCPU(0x010B + x) == 0) {
            goto L_000C46;
        }
        opDEC(0x010B + x, 1);
        if (!flgZ) {
            goto L_000C71;
        }
    L_000C46:
        myMapper->writeCPU(0x001B, myMapper->readCPU(0x0116 + x));
        myMapper->writeCPU(0x001C, myMapper->readCPU(0x0121 + x));
        y = myMapper->readCPU(0x012C + x);
        while (true) {
            a = myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgN) {
                goto L_000C60;
            }
            flgC = false;
            opADC(0x40);
            myMapper->writeCPU(0x0100 + x, a);
            opINY(1);
            if (!flgZ) {
                goto L_000C6D;
            }
        L_000C60:
            if (!flgZ) {
                goto L_000C69;
            }
            opINY(1);
            y = myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y);
        }
    L_000C69:
        opINY(1);
        myMapper->writeCPU(0x010B + x, a);
    L_000C6D:
        myMapper->writeCPU(0x012C + x, y);
    L_000C71:
        opINX(1);
    } while (x != 0x0B);
L_000C76:
    a = myMapper->readCPU(0x0141);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = false;
        opADC(myMapper->readCPU(0x0101));
        opORA(myMapper->readCPU(0x0164));
        x = a;
        a = myMapper->readCPU(0x0102);
        y = a;
        opADC(myMapper->readCPU(0x8F97 + x));
        myMapper->writeCPU(0x0171, a);
        a = y;
        opORA(0x7F);
        if (!flgN) {
            a = 0x00;
        }
        opADC(myMapper->readCPU(0x9017 + x));
        myMapper->writeCPU(0x0172, a);
        a = myMapper->readCPU(0x0100);
    }
    opORA(myMapper->readCPU(0x015F));
    myMapper->writeCPU(0x0170, a);
    a = myMapper->readCPU(0x0142);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = false;
        opADC(myMapper->readCPU(0x0104));
        opORA(myMapper->readCPU(0x0164));
        x = a;
        a = myMapper->readCPU(0x0105);
        y = a;
        opADC(myMapper->readCPU(0x8F97 + x));
        myMapper->writeCPU(0x0174, a);
        a = y;
        opORA(0x7F);
        if (!flgN) {
            a = 0x00;
        }
        opADC(myMapper->readCPU(0x9017 + x));
        myMapper->writeCPU(0x0175, a);
        a = myMapper->readCPU(0x0103);
    }
    opORA(myMapper->readCPU(0x0160));
    myMapper->writeCPU(0x0173, a);
    a = myMapper->readCPU(0x0143);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = false;
        opADC(myMapper->readCPU(0x0107));
        opORA(myMapper->readCPU(0x0164));
        x = a;
        a = myMapper->readCPU(0x0108);
        y = a;
        opADC(myMapper->readCPU(0x8F97 + x));
        myMapper->writeCPU(0x0177, a);
        a = y;
        opORA(0x7F);
        if (!flgN) {
            a = 0x00;
        }
        opADC(myMapper->readCPU(0x9017 + x));
        myMapper->writeCPU(0x0178, a);
        a = myMapper->readCPU(0x0106);
    }
    opORA(0x80);
    myMapper->writeCPU(0x0176, a);
    a = myMapper->readCPU(0x0144);
    setLoadFlag(a);
    if (!flgZ) {
        flgC = false;
        opADC(myMapper->readCPU(0x010A));
        opAND(0x0F);
        opEOR(0x0F);
        myMapper->writeCPU(0x001D, a);
        a = myMapper->readCPU(0x0162);
        opASL_A(1);
        opAND(0x80);
        opORA(myMapper->readCPU(0x001D));
        myMapper->writeCPU(0x017A, a);
        a = myMapper->readCPU(0x0109);
    }
    opORA(0xF0);
    myMapper->writeCPU(0x0179, a);
    x = 0x00;
    pushAddress(0x000D20);
    SUB_000EDF();
    if (poppedEntry.value != 0x000D20) return;
    myMapper->writeCPU(0x4000, myMapper->readCPU(0x0170));
    myMapper->writeCPU(0x4002, myMapper->readCPU(0x0171));
    a = myMapper->readCPU(0x0172);
    if (a != myMapper->readCPU(0x0161)) {
        myMapper->writeCPU(0x0161, a);
        myMapper->writeCPU(0x4003, a);
    }
    myMapper->writeCPU(0x4004, myMapper->readCPU(0x0173));
    myMapper->writeCPU(0x4006, myMapper->readCPU(0x0174));
    a = myMapper->readCPU(0x0175);
    if (a == myMapper->readCPU(0x0163)) {
        goto L_000D57;
    }
    myMapper->writeCPU(0x0163, a);
    myMapper->writeCPU(0x4007, a);
L_000D57:
    myMapper->writeCPU(0x4008, myMapper->readCPU(0x0176));
    myMapper->writeCPU(0x400A, myMapper->readCPU(0x0177));
    myMapper->writeCPU(0x400B, myMapper->readCPU(0x0178));
    myMapper->writeCPU(0x400C, myMapper->readCPU(0x0179));
    a = myMapper->readCPU(0x017A);
    myMapper->writeCPU(0x400E, a);
    opPLA();
    myMapper->writeCPU(0x001C, a);
    opPLA();
    myMapper->writeCPU(0x001B, a);
    popAddress();
}

void game::SUB_000D7C() {
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0x0168);
    opADC(0x00);
    myMapper->writeCPU(0x001C, a);
    myMapper->writeCPU(0x001B, myMapper->readCPU(0x0167));
    myMapper->writeCPU(0x001D, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0116 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x0121 + x, a);
    opINX(1);
    myMapper->writeCPU(0x0116 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0121 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    a = 0x00;
    myMapper->writeCPU(0x010A + x, a);
    myMapper->writeCPU(0x012B + x, a);
    myMapper->writeCPU(0x010B + x, a);
    myMapper->writeCPU(0x012C + x, a);
    if (x >= 0x09) {
        goto L_000DCC;
    }
    opINX(1);
    opINY(1);
    myMapper->writeCPU(0x010B + x, a);
    myMapper->writeCPU(0x012C + x, a);
    myMapper->writeCPU(0x0116 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0121 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
L_000DCC:
    a = myMapper->readCPU(0x001D);
    popAddress();
}

void game::SUB_000DCF() {
    if (myMapper->readCPU(0x0114 + x) == 0) {
        goto L_000DD9;
    }
    opDEC(0x0114 + x, 1);
    flgC = false;
    popAddress();
    return;
L_000DD9:
    myMapper->writeCPU(0x001B, myMapper->readCPU(0x0100 + x));
    myMapper->writeCPU(0x001C, myMapper->readCPU(0x0105 + x));
    y = 0x00;
    while (true) {
        do {
            do {
                while (true) {
                    do {
                        a = myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y);
                        opINC(0x001B, 1);
                        if (flgZ) {
                            opINC(0x001C, 1);
                        }
                        opORA(0x00);
                        if (!flgN) {
                            opLSR_A(1);
                            if (!flgC) {
                                goto L_000DF7;
                            }
                            opINC(0x0114 + x, 1);
                        L_000DF7:
                            myMapper->writeCPU(0x010A + x, a);
                            flgC = true;
                            if (flgC) {
                                goto L_000E5B;
                            }
                        }
                        opAND(0x7F);
                        opLSR_A(1);
                        if (flgC) {
                            goto L_000E09;
                        }
                        opASL_A(2);
                        myMapper->writeCPU(0x010F + x, a);
                    } while (!flgC);
                L_000E09:
                    opCMP(a, 0x3D);
                    if (!flgC) {
                        goto L_000E58;
                    }
                    if (flgZ) {
                        goto L_000E3A;
                    }
                    if (a == 0x3E) {
                        goto L_000E47;
                    }
                    flgC = false;
                    a = myMapper->readCPU(0x001B);
                    opADC(0x03);
                    myMapper->writeCPU(0x0119 + x, a);
                    a = myMapper->readCPU(0x001C);
                    opADC(0x00);
                    myMapper->writeCPU(0x011E + x, a);
                    myMapper->writeCPU(0x0123 + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
                    opINY(1);
                    myMapper->writeCPU(0x001D, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
                    opINY(1);
                    myMapper->writeCPU(0x001C, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
                    myMapper->writeCPU(0x001B, myMapper->readCPU(0x001D));
                    y = 0x00;
                }
            L_000E3A:
                myMapper->writeCPU(0x014A, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
                opINC(0x001B, 1);
            } while (!flgZ);
            opINC(0x001C, 1);
        } while (!flgZ);
    L_000E47:
        myMapper->writeCPU(0x001D, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x001C, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x001B, myMapper->readCPU(0x001D));
        opDEY(1);
    }
L_000E58:
    myMapper->writeCPU(0x0114 + x, a);
L_000E5B:
    if (myMapper->readCPU(0x0123 + x) != 0) {
        opDEC(0x0123 + x, 1);
        if (!flgZ) {
            goto L_000E72;
        }
        myMapper->writeCPU(0x0100 + x, myMapper->readCPU(0x0119 + x));
        myMapper->writeCPU(0x0105 + x, myMapper->readCPU(0x011E + x));
        popAddress();
        return;
    }
L_000E72:
    myMapper->writeCPU(0x0100 + x, myMapper->readCPU(0x001B));
    myMapper->writeCPU(0x0105 + x, myMapper->readCPU(0x001C));
    popAddress();
}

void game::SUB_000E7D() {
    myMapper->writeCPU(0x4015, 0x0F);
    popAddress();
}

void game::SUB_000E83() {
    myMapper->writeCPU(0x001B, x);
    myMapper->writeCPU(0x001C, y);
    y = 0x00;
    if (myMapper->readCPU(0x0164) != 0) {
        goto L_000E90;
    }
    opINY(2);
L_000E90:
    myMapper->writeCPU(0x017B, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x017C, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    do {
        pushAddress(0x000E9D);
        SUB_000EAA();
        if (poppedEntry.value != 0x000E9D) return;
        a = x;
        flgC = false;
        opADC(0x0F);
        x = a;
    } while (x != 0x0F);
    popAddress();
}

void game::SUB_000EAA() {
    a = 0x00;
    myMapper->writeCPU(0x017F + x, a);
    myMapper->writeCPU(0x017D + x, a);
    myMapper->writeCPU(0x0180 + x, a);
    myMapper->writeCPU(0x0187 + x, a);
    a = 0x30;
    myMapper->writeCPU(0x0181 + x, a);
    myMapper->writeCPU(0x0184 + x, a);
    myMapper->writeCPU(0x018A + x, a);
    popAddress();
}

void game::SUB_000EC4() {
    opASL_A(1);
    y = a;
    pushAddress(0x000EC6);
    SUB_000EAA();
    if (poppedEntry.value != 0x000EC6) return;
    myMapper->writeCPU(0x001B, myMapper->readCPU(0x017B));
    myMapper->writeCPU(0x001C, myMapper->readCPU(0x017C));
    myMapper->writeCPU(0x017E + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x017F + x, myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y));
    popAddress();
}

void game::SUB_000EDF() {
    if (myMapper->readCPU(0x017D + x) == 0) {
        goto L_000EE9;
    }
    opDEC(0x017D + x, 1);
    if (!flgZ) {
        goto L_000F1F;
    }
L_000EE9:
    a = myMapper->readCPU(0x017F + x);
    setLoadFlag(a);
    if (flgZ) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x001C, a);
    myMapper->writeCPU(0x001B, myMapper->readCPU(0x017E + x));
    y = myMapper->readCPU(0x0180 + x);
    flgC = false;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgN) {
            goto L_000F0B;
        }
        if (flgZ) {
            goto L_000F1C;
        }
        opINY(1);
        myMapper->writeCPU(0x017D + x, a);
        myMapper->writeCPU(0x0180 + x, y);
        goto L_000F1F;
    L_000F0B:
        opINY(1);
        myMapper->writeCPU(0x001D, x);
        opADC(myMapper->readCPU(0x001D));
        x = a;
        a = myMapper->readCPU(myMapper->readCPU(0x001B) + (myMapper->readCPU((0x001B + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x0101 + x, a);
        x = myMapper->readCPU(0x001D);
    }
L_000F1C:
    myMapper->writeCPU(0x017F + x, a);
L_000F1F:
    a = myMapper->readCPU(0x0170);
    opAND(0x0F);
    myMapper->writeCPU(0x001D, a);
    a = myMapper->readCPU(0x0181 + x);
    opAND(0x0F);
    if (a >= myMapper->readCPU(0x001D)) {
        myMapper->writeCPU(0x0170, myMapper->readCPU(0x0181 + x));
        myMapper->writeCPU(0x0171, myMapper->readCPU(0x0182 + x));
        myMapper->writeCPU(0x0172, myMapper->readCPU(0x0183 + x));
    }
    a = myMapper->readCPU(0x0173);
    opAND(0x0F);
    myMapper->writeCPU(0x001D, a);
    a = myMapper->readCPU(0x0184 + x);
    opAND(0x0F);
    if (a >= myMapper->readCPU(0x001D)) {
        myMapper->writeCPU(0x0173, myMapper->readCPU(0x0184 + x));
        myMapper->writeCPU(0x0174, myMapper->readCPU(0x0185 + x));
        myMapper->writeCPU(0x0175, myMapper->readCPU(0x0186 + x));
    }
    a = myMapper->readCPU(0x0187 + x);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x0176, a);
        myMapper->writeCPU(0x0177, myMapper->readCPU(0x0188 + x));
        myMapper->writeCPU(0x0178, myMapper->readCPU(0x0189 + x));
    }
    a = myMapper->readCPU(0x0179);
    opAND(0x0F);
    myMapper->writeCPU(0x001D, a);
    a = myMapper->readCPU(0x018A + x);
    opAND(0x0F);
    if (a < myMapper->readCPU(0x001D)) {
        goto L_000F93;
    }
    myMapper->writeCPU(0x0179, myMapper->readCPU(0x018A + x));
    myMapper->writeCPU(0x017A, myMapper->readCPU(0x018B + x));
L_000F93:
    popAddress();
}

void game::SUB_001097() {
    pushAddress(0x001097);
    SUB_0002A3();
    if (poppedEntry.value != 0x001097) return;
    a = myMapper->readCPU(0x002F);
    opAND(0x3F);
    myMapper->writeCPU(0x05F1, a);
    if (a >= 0x31) {
        a = 0x69;
    }
    else {
        if (myMapper->readCPU(0x05F1) < 0x21) {
            goto L_0010B6;
        }
        a = 0x68;
        goto L_0010C4;
    L_0010B6:
        if (myMapper->readCPU(0x05F1) < 0x11) {
            goto L_0010C2;
        }
        a = 0x67;
        goto L_0010C4;
    L_0010C2:
        a = 0x66;
    }
L_0010C4:
    myMapper->writeCPU(0x0091, a);
    pushAddress(0x0010C6);
    SUB_00338C();
    if (poppedEntry.value != 0x0010C6) return;
    a = 0x50;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0xB8;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0091);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = y;
    pushAddress(0x0010DA);
    SUB_0002CF();
    if (poppedEntry.value != 0x0010DA) return;
    pushAddress(0x0010DD);
    SUB_00338C();
    if (poppedEntry.value != 0x0010DD) return;
    a = 0xB0;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0xB8;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0091);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = y;
    pushAddress(0x0010F1);
    SUB_0002CF();
    if (poppedEntry.value != 0x0010F1) return;
    pushAddress(0x0010F4);
    SUB_00338C();
    if (poppedEntry.value != 0x0010F4) return;
    a = 0x98;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x60;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x001109);
    SUB_0002CF();
    if (poppedEntry.value != 0x001109) return;
    pushAddress(0x00110C);
    SUB_00338C();
    if (poppedEntry.value != 0x00110C) return;
    a = 0xA0;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x61;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x001121);
    SUB_0002CF();
    if (poppedEntry.value != 0x001121) return;
    pushAddress(0x001124);
    SUB_00338C();
    if (poppedEntry.value != 0x001124) return;
    a = 0x98;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x001139);
    SUB_0002CF();
    if (poppedEntry.value != 0x001139) return;
    pushAddress(0x00113C);
    SUB_00338C();
    if (poppedEntry.value != 0x00113C) return;
    a = 0xA0;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x71;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x001151);
    SUB_0002CF();
    if (poppedEntry.value != 0x001151) return;
    pushAddress(0x001154);
    SUB_00338C();
    if (poppedEntry.value != 0x001154) return;
    a = 0x98;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x80;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x001167);
    SUB_0002CF();
    if (poppedEntry.value != 0x001167) return;
    pushAddress(0x00116A);
    SUB_00338C();
    if (poppedEntry.value != 0x00116A) return;
    a = 0xA0;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x80;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x81;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x00117F);
    SUB_0002CF();
    if (poppedEntry.value != 0x00117F) return;
    pushAddress(0x001182);
    SUB_00338C();
    if (poppedEntry.value != 0x001182) return;
    a = 0x98;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x90;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x001197);
    SUB_0002CF();
    if (poppedEntry.value != 0x001197) return;
    pushAddress(0x00119A);
    SUB_00338C();
    if (poppedEntry.value != 0x00119A) return;
    a = 0xA0;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x91;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    SUB_0002CF();
    return;
}

void game::SUB_0011B2() {
    pushAddress(0x0011B2);
    SUB_0002A3();
    if (poppedEntry.value != 0x0011B2) return;
    a = myMapper->readCPU(0x0322);
    opASL_A(3);
    flgC = false;
    opADC(0x60);
    myMapper->writeCPU(0x008F, a);
    a = myMapper->readCPU(0x0323);
    opASL_A(3);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x0090, a);
    if (myMapper->readCPU(0x0323) != 0xFF) {
        myMapper->writeCPU(0x05F4, 0x00);
        while (myMapper->readCPU(0x05F4) < 0x04) {
            y = myMapper->readCPU(0x05F4);
            myMapper->writeCPU(0x05F5, myMapper->readCPU(0x0044 + y));
            y = myMapper->readCPU(0x05F5);
            myMapper->writeCPU(0x0091, myMapper->readCPU(0xEA06 + y));
            y = myMapper->readCPU(0x05F5);
            myMapper->writeCPU(0x0092, myMapper->readCPU(0xEA16 + y));
            x = 0x00;
            a = myMapper->readCPU(0x0092);
            pushAddress(0x0011FB);
            SUB_003333();
            if (poppedEntry.value != 0x0011FB) return;
            flgC = false;
            opADC(myMapper->readCPU(0x0090));
            if (flgC) {
                opINX(1);
            }
            flgC = true;
            opSBC(myMapper->readCPU(0xEA97));
            myMapper->writeCPU(0x00CC, a);
            a = x;
            opSBC(0x00);
            opORA(myMapper->readCPU(0x00CC));
            if (flgC) {
                if (flgZ) {
                    goto L_001236;
                }
                pushAddress(0x001213);
                SUB_00338C();
                if (poppedEntry.value != 0x001213) return;
                a = myMapper->readCPU(0x0091);
                opASL_A(3);
                flgC = false;
                opADC(myMapper->readCPU(0x008F));
                y = 0x02;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = myMapper->readCPU(0x0092);
                opASL_A(3);
                flgC = false;
                opADC(myMapper->readCPU(0x0090));
                opDEY(1);
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = myMapper->readCPU(0x0058);
                opDEY(1);
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = y;
                pushAddress(0x001233);
                SUB_0002CF();
                if (poppedEntry.value != 0x001233) return;
            }
        L_001236:
            opINC(0x05F4, 1);
        }
    }
    if (myMapper->readCPU(0x003A) == 0x02) {
    }
    else {
        myMapper->writeCPU(0x05F2, 0x00);
        if (myMapper->readCPU(0x003A) == 0x01) {
            opCMP(myMapper->readCPU(0x0034), 0x00);
            if (flgZ) {
                opCMP(myMapper->readCPU(0x0033), 0x78);
            }
            if (!flgC) {
                a = myMapper->readCPU(0x002F);
                goto L_00127C;
            }
            opCMP(myMapper->readCPU(0x0034), 0x01);
            if (flgZ) {
                opCMP(myMapper->readCPU(0x0033), 0x2C);
            }
            if (!flgC) {
                a = myMapper->readCPU(0x002F);
                goto L_00127B;
            }
            a = myMapper->readCPU(0x002F);
            opLSR_A(1);
            goto L_00127A;
        }
        a = myMapper->readCPU(0x002F);
    L_00127A:
        opLSR_A(1);
    L_00127B:
        opLSR_A(1);
    L_00127C:
        opLSR_A(2);
        myMapper->writeCPU(0x05F3, a);
        myMapper->writeCPU(0x0091, 0x00);
        while (true) {
            if (myMapper->readCPU(0x0091) < 0x0A) {
                goto L_00128E;
            }
            goto L_001332;
        L_00128E:
            y = myMapper->readCPU(0x0091);
            myMapper->writeCPU(0x0096, myMapper->readCPU(0x0070 + y));
            if (myMapper->readCPU(0x0096) != 0) {
                goto L_00129C;
            }
            goto L_00132D;
        L_00129C:
            a = 0x00;
            myMapper->writeCPU(0x0092, a);
            x = a;
            while (true) {
                a = myMapper->readCPU(0x0092);
                if (a >= myMapper->readCPU(0x0096)) {
                    goto L_00132D;
                }
                flgC = false;
                opADC(myMapper->readCPU(0x05F3));
                opAND(0x03);
                myMapper->writeCPU(0x00C4, a);
                a = x;
                flgC = false;
                opADC(0x03);
                myMapper->writeCPU(0x00C5, a);
                y = 0x42;
                myMapper->writeCPU(0x05F2, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
                a = myMapper->readCPU(0x0096);
                flgC = true;
                opSBC(0x01);
                if (!flgC) {
                    opDEX(1);
                }
                if (x == 0x00) {
                    if (a != myMapper->readCPU(0x0092)) {
                        goto L_0012F8;
                    }
                    pushAddress(0x0012CF);
                    SUB_00338C();
                    if (poppedEntry.value != 0x0012CF) return;
                    a = myMapper->readCPU(0x0091);
                    opASL_A(3);
                    flgC = false;
                    opADC(0x60);
                    flgC = false;
                    opADC(myMapper->readCPU(0x05F2));
                    y = 0x02;
                    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                    a = 0xE0;
                    pushAddress(0x0012E4);
                    SUB_003667();
                    if (poppedEntry.value != 0x0012E4) return;
                    a = myMapper->readCPU(0x0092);
                    pushAddress(0x0012E9);
                    SUB_003333();
                    if (poppedEntry.value != 0x0012E9) return;
                    pushAddress(0x0012EC);
                    SUB_00370A();
                    if (poppedEntry.value != 0x0012EC) return;
                    y = 0x01;
                    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                    a = 0xF9;
                    goto L_00131E;
                }
            L_0012F8:
                pushAddress(0x0012F8);
                SUB_00338C();
                if (poppedEntry.value != 0x0012F8) return;
                a = myMapper->readCPU(0x0091);
                opASL_A(3);
                flgC = false;
                opADC(0x60);
                flgC = false;
                opADC(myMapper->readCPU(0x05F2));
                y = 0x02;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0xE0;
                pushAddress(0x00130D);
                SUB_003667();
                if (poppedEntry.value != 0x00130D) return;
                a = myMapper->readCPU(0x0092);
                pushAddress(0x001312);
                SUB_003333();
                if (poppedEntry.value != 0x001312) return;
                pushAddress(0x001315);
                SUB_00370A();
                if (poppedEntry.value != 0x001315) return;
                y = 0x01;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0xF8;
            L_00131E:
                opDEY(1);
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0x01;
                pushAddress(0x001323);
                SUB_0002CF();
                if (poppedEntry.value != 0x001323) return;
                x = 0x00;
                opINC(0x0092, 1);
            }
        L_00132D:
            opINC(0x0091, 1);
        }
    }
L_001332:
    if (myMapper->readCPU(0x0032) != 0) {
        pushAddress(0x001336);
        SUB_00338C();
        if (poppedEntry.value != 0x001336) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xC0;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x65;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x01;
        pushAddress(0x00134B);
        SUB_0002CF();
        if (poppedEntry.value != 0x00134B) return;
        pushAddress(0x00134E);
        SUB_00338C();
        if (poppedEntry.value != 0x00134E) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xC8;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x64;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x01;
        pushAddress(0x001363);
        SUB_0002CF();
        if (poppedEntry.value != 0x001363) return;
        pushAddress(0x001366);
        SUB_00338C();
        if (poppedEntry.value != 0x001366) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xD0;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x74;
    }
    else {
        if (myMapper->readCPU(0x003A) != 0x02) {
            goto L_0013AA;
        }
        pushAddress(0x00137F);
        SUB_00338C();
        if (poppedEntry.value != 0x00137F) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xC8;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x63;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x01;
        pushAddress(0x001394);
        SUB_0002CF();
        if (poppedEntry.value != 0x001394) return;
        pushAddress(0x001397);
        SUB_00338C();
        if (poppedEntry.value != 0x001397) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xD0;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x73;
        goto L_00142A;
    L_0013AA:
        a = myMapper->readCPU(0x0030);
        x = myMapper->readCPU(0x0031);
        pushAddress(0x0013AE);
        SUB_003669();
        if (poppedEntry.value != 0x0013AE) return;
        x = 0x01;
        a = 0x2C;
        pushAddress(0x0013B5);
        SUB_00376E();
        if (poppedEntry.value != 0x0013B5) return;
        myMapper->writeCPU(0x0093, a);
        myMapper->writeCPU(0x0094, x);
        opCMP(a, 0x28);
        a = x;
        opSBC(0x01);
        if (!flgC) {
            opCMP(myMapper->readCPU(0x0093), 0x23);
            a = myMapper->readCPU(0x0094);
            opSBC(0x01);
            if (flgC) {
                pushAddress(0x0013CD);
                SUB_00338C();
                if (poppedEntry.value != 0x0013CD) return;
                a = 0x18;
                y = 0x02;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0xC8;
                opDEY(1);
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0x63;
                opDEY(1);
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0x01;
                pushAddress(0x0013E2);
                SUB_0002CF();
                if (poppedEntry.value != 0x0013E2) return;
                pushAddress(0x0013E5);
                SUB_00338C();
                if (poppedEntry.value != 0x0013E5) return;
                a = 0x18;
                y = 0x02;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0xD0;
                opDEY(1);
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                a = 0x73;
                goto L_00142A;
            }
            opCMP(myMapper->readCPU(0x0093), 0x1E);
            a = myMapper->readCPU(0x0094);
            opSBC(0x01);
            if (!flgC) {
                goto L_001432;
            }
        }
        pushAddress(0x001402);
        SUB_00338C();
        if (poppedEntry.value != 0x001402) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xC8;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x62;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x01;
        pushAddress(0x001417);
        SUB_0002CF();
        if (poppedEntry.value != 0x001417) return;
        pushAddress(0x00141A);
        SUB_00338C();
        if (poppedEntry.value != 0x00141A) return;
        a = 0x18;
        y = 0x02;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xD0;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x72;
    }
L_00142A:
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x01;
    pushAddress(0x00142F);
    SUB_0002CF();
    if (poppedEntry.value != 0x00142F) return;
L_001432:
    a = myMapper->readCPU(0x002F);
    x = 0x00;
    opAND(0x3F);
    myMapper->writeCPU(0x0093, a);
    myMapper->writeCPU(0x0094, x);
    if (a >= 0x31) {
        a = 0x69;
    }
    else {
        opCMP(myMapper->readCPU(0x0093), 0x21);
        a = myMapper->readCPU(0x0094);
        opSBC(0x00);
        if (flgC) {
            a = 0x68;
        }
        else {
            opCMP(myMapper->readCPU(0x0093), 0x11);
            a = myMapper->readCPU(0x0094);
            opSBC(0x00);
            if (!flgC) {
                goto L_001463;
            }
            a = 0x67;
            goto L_001465;
        L_001463:
            a = 0x66;
        }
    }
L_001465:
    myMapper->writeCPU(0x0091, a);
    pushAddress(0x001467);
    SUB_00338C();
    if (poppedEntry.value != 0x001467) return;
    a = 0x40;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x08;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0091);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x02;
    pushAddress(0x00147C);
    SUB_0002CF();
    if (poppedEntry.value != 0x00147C) return;
    pushAddress(0x00147F);
    SUB_00338C();
    if (poppedEntry.value != 0x00147F) return;
    a = 0xC0;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x08;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0091);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x02;
    pushAddress(0x001494);
    SUB_0002CF();
    if (poppedEntry.value != 0x001494) return;
    pushAddress(0x001497);
    SUB_00338C();
    if (poppedEntry.value != 0x001497) return;
    a = 0x18;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x50;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0091);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = y;
    pushAddress(0x0014AB);
    SUB_0002CF();
    if (poppedEntry.value != 0x0014AB) return;
    pushAddress(0x0014AE);
    SUB_00338C();
    if (poppedEntry.value != 0x0014AE) return;
    a = 0xD8;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x50;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0091);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = y;
    SUB_0002CF();
    return;
}

void game::SUB_0014C5() {
    a = 0x00;
    myMapper->writeCPU(0x0086, a);
    myMapper->writeCPU(0x0087, a);
    myMapper->writeCPU(0x0088, a);
    myMapper->writeCPU(0x009E, a);
    if (myMapper->readCPU(0x00A4) == 0) {
        opDEC(0x007C, 1);
    }
    else {
        opDEC(0x00A4, 1);
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x20);
    if (!flgZ) {
        if (myMapper->readCPU(0x00A1) != 0xFF) {
            goto L_0014EA;
        }
        myMapper->writeCPU(0x009B, 0x01);
    }
L_0014EA:
    a = myMapper->readCPU(0x0036);
    opAND(0x80);
    if (!flgZ) {
        a = 0x01;
    }
    else {
        a = myMapper->readCPU(0x0036);
        opAND(0x40);
        if (flgZ) {
            goto L_001500;
        }
        a = 0xFF;
    }
    pushAddress(0x0014FD);
    SUB_001A0F();
    if (poppedEntry.value != 0x0014FD) return;
L_001500:
    if (myMapper->readCPU(0x007A) != 0) {
        opDEC(0x007A, 1);
    }
    myMapper->writeCPU(0x0088, myMapper->readCPU(0x0322));
    a = myMapper->readCPU(0x0035);
    opAND(0x01);
    if (!flgZ) {
        if (myMapper->readCPU(0x007A) == 0) {
            goto L_00151B;
        }
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x01);
    if (!flgZ) {
    L_00151B:
        myMapper->writeCPU(0x007A, myMapper->readCPU(0xEA96));
        a = myMapper->readCPU(0x0036);
        opAND(0x01);
        if (!flgZ) {
            a = myMapper->readCPU(0x007A);
            opASL_A(1);
            myMapper->writeCPU(0x007A, a);
        }
        myMapper->writeCPU(0x0088, myMapper->readCPU(0x0322));
        opINC(0x0322, 1);
    }
    else {
        a = myMapper->readCPU(0x0035);
        opAND(0x02);
        if (!flgZ) {
            if (myMapper->readCPU(0x007A) == 0) {
                goto L_001546;
            }
        }
        a = myMapper->readCPU(0x0036);
        opAND(0x02);
        if (!flgZ) {
        L_001546:
            myMapper->writeCPU(0x007A, myMapper->readCPU(0xEA96));
            a = myMapper->readCPU(0x0036);
            opAND(0x02);
            if (!flgZ) {
                a = myMapper->readCPU(0x007A);
                opASL_A(1);
                myMapper->writeCPU(0x007A, a);
            }
            myMapper->writeCPU(0x0088, myMapper->readCPU(0x0322));
            opDEC(0x0322, 1);
        }
    }
    if (myMapper->readCPU(0x0088) != myMapper->readCPU(0x0322)) {
        pushAddress(0x001565);
        SUB_001836();
        if (poppedEntry.value != 0x001565) return;
        if (a != 0) {
            myMapper->writeCPU(0x0322, myMapper->readCPU(0x0088));
        }
    }
    myMapper->writeCPU(0x0087, myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x05F6, 0x00);
    if (myMapper->readCPU(0x003F) != 0) {
        a = myMapper->readCPU(0x0035);
        opAND(0x08);
        if (!flgZ) {
            a = myMapper->readCPU(0x0035);
            opAND(0x03);
            if (flgZ) {
                a = myMapper->readCPU(0x0035);
                opAND(0x08);
                if (!flgZ) {
                    if (myMapper->readCPU(0x0041) == 0) {
                        goto L_001599;
                    }
                }
                a = myMapper->readCPU(0x0036);
                opAND(0x08);
                if (flgZ) {
                    goto L_0015CB;
                }
            L_001599:
                opDEC(0x0040, 1);
                if (!flgZ) {
                    goto L_0015CB;
                }
                a = 0x01;
                myMapper->writeCPU(0x05F6, a);
                myMapper->writeCPU(0x0041, a);
                goto L_0015AA;
                do {
                    opINC(0x0323, 1);
                L_0015AA:
                    pushAddress(0x0015AA);
                    SUB_001836();
                    if (poppedEntry.value != 0x0015AA) return;
                } while (a == 0);
                myMapper->writeCPU(0x009E, 0x01);
                goto L_0015CB;
            }
        }
    }
    a = myMapper->readCPU(0x0035);
    opAND(0x03);
    if (flgZ) {
        myMapper->writeCPU(0x0041, a);
    }
    a = myMapper->readCPU(0x003F);
    if (a != 0x01) {
        if (a != 0x02) {
            goto L_0015CB;
        }
    }
    myMapper->writeCPU(0x0040, a);
L_0015CB:
    if (myMapper->readCPU(0x05F6) == 0) {
        a = myMapper->readCPU(0x0036);
        opAND(0x04);
        if (flgZ) {
            if (myMapper->readCPU(0x009D) == 0xFF) {
                goto L_0015ED;
            }
        }
        a = myMapper->readCPU(0x0036);
        opAND(0x04);
        if (!flgZ) {
            myMapper->writeCPU(0x009E, 0x01);
            a = 0x00;
        }
        myMapper->writeCPU(0x007B, a);
        goto L_001600;
    L_0015ED:
        a = myMapper->readCPU(0x0035);
        opAND(0x04);
        if (!flgZ) {
            if (myMapper->readCPU(0x007B) != 0) {
                goto L_001602;
            }
            a = myMapper->readCPU(0x007C);
            setLoadFlag(a);
            if (flgZ) {
            }
            else {
                a = 0x01;
            }
        L_001600:
            myMapper->writeCPU(0x007C, a);
        }
    L_001602:
        a = myMapper->readCPU(0x007C);
        setLoadFlag(a);
        if (flgZ) {
            myMapper->writeCPU(0x00A4, a);
            opINC(0x0323, 1);
            myMapper->writeCPU(0x007C, myMapper->readCPU(0x0324));
        }
    }
    opCMP(myMapper->readCPU(0x0324), 0x10);
    a = 0x00;
    if (flgC) {
        myMapper->writeCPU(0x009E, 0x01);
        a = 0x00;
    }
    myMapper->writeCPU(0x0086, a);
    pushAddress(0x001621);
    SUB_001836();
    if (poppedEntry.value != 0x001621) return;
    x = a;
    setLoadFlag(x);
    if (!flgZ) {
        if (myMapper->readCPU(0x009D) != 0xFF) {
            goto L_001637;
        }
        a = 0x0F;
        flgC = true;
        opSBC(myMapper->readCPU(0x0324));
        opCMP(a, 0x80);
        myMapper->writeCPU(0x009D, a);
    L_001637:
        opDEC(0x009D, 1);
        opDEC(0x0323, 1);
        if (myMapper->readCPU(0x009D) != 0) {
            if (myMapper->readCPU(0x009E) == 0) {
                goto L_00164C;
            }
        }
        myMapper->writeCPU(0x0086, 0x01);
    }
    myMapper->writeCPU(0x009D, 0xFF);
L_00164C:
    if (myMapper->readCPU(0x0086) == 0) {
        goto L_001657;
    }
    pushAddress(0x001650);
    SUB_00172B();
    if (poppedEntry.value != 0x001650) return;
    myMapper->writeCPU(0x009F, 0x05);
L_001657:
    popAddress();
}

void game::SUB_001658() {
    if (myMapper->readCPU(0x008D) < 0x04) {
        goto L_0016AA;
    }
    pushAddress(0x00165E);
    SUB_00337F();
    if (poppedEntry.value != 0x00165E) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x008C);
    opASL_A(3);
    flgC = false;
    opADC(0x60);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x008D);
    opASL_A(3);
    flgC = false;
    opADC(0x10);
    pushAddress(0x00167A);
    SUB_000850();
    if (poppedEntry.value != 0x00167A) return;
    myMapper->writeCPU(0x00A7, a);
    myMapper->writeCPU(0x00A8, x);
    a = myMapper->readCPU(0x008E);
    pushAddress(0x001683);
    SUB_003653();
    if (poppedEntry.value != 0x001683) return;
    a = myMapper->readCPU(0x00A7);
    x = myMapper->readCPU(0x00A8);
    pushAddress(0x00168A);
    SUB_00072F();
    if (poppedEntry.value != 0x00168A) return;
    y = myMapper->readCPU(0x008D);
    x = 0x00;
    a = myMapper->readCPU(0x0349 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x008C));
    if (!flgC) {
        goto L_00169B;
    }
    opINX(1);
    flgC = false;
L_00169B:
    opADC(0xF9);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0x03);
    myMapper->writeCPU(0x00C5, a);
    a = myMapper->readCPU(0x008E);
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
L_0016AA:
    popAddress();
}

void game::SUB_00172B() {
    myMapper->writeCPU(0x008B, 0x00);
    myMapper->writeCPU(0x008A, 0xFF);
    myMapper->writeCPU(0x05F7, 0x00);
    while (myMapper->readCPU(0x05F7) < 0x04) {
        y = myMapper->readCPU(0x05F7);
        myMapper->writeCPU(0x05F8, myMapper->readCPU(0x0044 + y));
        y = myMapper->readCPU(0x05F8);
        myMapper->writeCPU(0x0091, myMapper->readCPU(0xEA06 + y));
        y = myMapper->readCPU(0x05F8);
        myMapper->writeCPU(0x0092, myMapper->readCPU(0xEA16 + y));
        a = myMapper->readCPU(0x0322);
        flgC = false;
        opADC(myMapper->readCPU(0x0091));
        myMapper->writeCPU(0x008C, a);
        a = myMapper->readCPU(0x0323);
        flgC = false;
        opADC(myMapper->readCPU(0x0092));
        myMapper->writeCPU(0x008D, a);
        myMapper->writeCPU(0x008E, myMapper->readCPU(0x0058));
        a = myMapper->readCPU(0x008D);
        if (a < myMapper->readCPU(0x008A)) {
            myMapper->writeCPU(0x008A, a);
        }
        a = myMapper->readCPU(0x008D);
        flgC = true;
        opSBC(myMapper->readCPU(0x008B));
        if (flgC) {
            if (flgZ) {
                goto L_001781;
            }
            myMapper->writeCPU(0x008B, myMapper->readCPU(0x008D));
        }
    L_001781:
        pushAddress(0x001781);
        SUB_001658();
        if (poppedEntry.value != 0x001781) return;
        opINC(0x05F7, 1);
    }
    if (myMapper->readCPU(0x003C) != 0) {
        a = 0x01;
        pushAddress(0x001790);
        SUB_003653();
        if (poppedEntry.value != 0x001790) return;
        a = 0x00;
        pushAddress(0x001795);
        SUB_000475();
        if (poppedEntry.value != 0x001795) return;
    }
    myMapper->writeCPU(0x0323, 0xFF);
    a = 0x00;
    pushAddress(0x00179F);
    SUB_0002B3();
    if (poppedEntry.value != 0x00179F) return;
    pushAddress(0x0017A2);
    SUB_00338C();
    if (poppedEntry.value != 0x0017A2) return;
    a = 0x00;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0017B1);
    SUB_0002CF();
    if (poppedEntry.value != 0x0017B1) return;
    pushAddress(0x0017B4);
    SUB_00338C();
    if (poppedEntry.value != 0x0017B4) return;
    a = 0x00;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0017C3);
    SUB_0002CF();
    if (poppedEntry.value != 0x0017C3) return;
    pushAddress(0x0017C6);
    SUB_00338C();
    if (poppedEntry.value != 0x0017C6) return;
    a = 0x00;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0017D5);
    SUB_0002CF();
    if (poppedEntry.value != 0x0017D5) return;
    pushAddress(0x0017D8);
    SUB_00338C();
    if (poppedEntry.value != 0x0017D8) return;
    a = 0x00;
    y = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0017E7);
    SUB_0002CF();
    if (poppedEntry.value != 0x0017E7) return;
    if (myMapper->readCPU(0x003A) != 0) {
        goto L_0017F2;
    }
    myMapper->writeCPU(0x009B, 0x01);
L_0017F2:
    a = myMapper->readCPU(0x008B);
    SUB_002316();
    return;
}

void game::SUB_001836() {
    a = 0x00;
    myMapper->writeCPU(0x05FB, a);
    x = a;
    while (myMapper->readCPU(0x05FB) < 0x04) {
        y = myMapper->readCPU(0x05FB);
        myMapper->writeCPU(0x05FC, myMapper->readCPU(0x0044 + y));
        y = myMapper->readCPU(0x05FC);
        myMapper->writeCPU(0x0091, myMapper->readCPU(0xEA06 + y));
        y = myMapper->readCPU(0x05FC);
        myMapper->writeCPU(0x0092, myMapper->readCPU(0xEA16 + y));
        a = myMapper->readCPU(0x0322);
        flgC = false;
        opADC(myMapper->readCPU(0x0091));
        myMapper->writeCPU(0x05F9, a);
        a = myMapper->readCPU(0x0323);
        flgC = false;
        opADC(myMapper->readCPU(0x0092));
        myMapper->writeCPU(0x05FA, a);
        if (a < 0x18) {
            if (myMapper->readCPU(0x05F9) < 0x0A) {
                goto L_00187C;
            }
        }
        a = 0x01;
        popAddress();
        return;
    L_00187C:
        y = myMapper->readCPU(0x05FA);
        a = myMapper->readCPU(0x0349 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x05F9));
        if (flgC) {
            opINX(1);
        }
        myMapper->writeCPU(0x00C4, a);
        a = x;
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x00C5, a);
        y = 0xF9;
        x = 0x00;
        if (myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y) == 0) {
            goto L_00189C;
        }
        a = 0x01;
        popAddress();
        return;
    L_00189C:
        opINC(0x05FB, 1);
    }
    a = x;
    popAddress();
}

void game::SUB_0018A4() {
    myMapper->writeCPU(0x0089, 0x00);
    myMapper->writeCPU(0x009D, 0xFF);
    myMapper->writeCPU(0x007B, 0x01);
    myMapper->writeCPU(0x007C, myMapper->readCPU(0x0324));
    myMapper->writeCPU(0x0043, 0x00);
    y = 0x0F;
    do {
        myMapper->writeCPU(0x0048 + y, myMapper->readCPU(0x005E + y));
        opDEY(1);
    } while (!flgN);
    y = 0x03;
    do {
        myMapper->writeCPU(0x0044 + y, myMapper->readCPU(0x0048 + y));
        opDEY(1);
    } while (!flgN);
    myMapper->writeCPU(0x0058, myMapper->readCPU(0x006E));
    myMapper->writeCPU(0x0059, myMapper->readCPU(0x006F));
    myMapper->writeCPU(0x0322, 0x03);
    y = myMapper->readCPU(0x0059);
    myMapper->writeCPU(0x0323, myMapper->readCPU(0x033B + y));
    pushAddress(0x0018E4);
    SUB_00367F();
    if (poppedEntry.value != 0x0018E4) return;
    pushAddress(0x0018E7);
    SUB_003669();
    if (poppedEntry.value != 0x0018E7) return;
    x = 0x00;
    a = 0x07;
    pushAddress(0x0018EE);
    SUB_003561();
    if (poppedEntry.value != 0x0018EE) return;
    myMapper->writeCPU(0x0089, a);
    if (myMapper->readCPU(0x0059) == myMapper->readCPU(0x0089)) {
        pushAddress(0x0018F9);
        SUB_00367F();
        if (poppedEntry.value != 0x0018F9) return;
        pushAddress(0x0018FC);
        SUB_003669();
        if (poppedEntry.value != 0x0018FC) return;
        x = 0x00;
        a = 0x07;
        pushAddress(0x001903);
        SUB_003561();
        if (poppedEntry.value != 0x001903) return;
        myMapper->writeCPU(0x0089, a);
    }
    myMapper->writeCPU(0x006F, myMapper->readCPU(0x0089));
    a = 0x5E;
    x = 0x00;
    pushAddress(0x001910);
    SUB_003669();
    if (poppedEntry.value != 0x001910) return;
    x = 0x00;
    a = myMapper->readCPU(0x0089);
    opASL_A(1);
    if (flgC) {
        opINX(1);
        flgC = false;
    }
    opADC(0x26);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0x03);
    myMapper->writeCPU(0x00C5, a);
    y = 0x01;
    x = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    pushAddress(0x00192D);
    SUB_003669();
    if (poppedEntry.value != 0x00192D) return;
    x = 0x00;
    a = 0x10;
    pushAddress(0x001934);
    SUB_0005A1();
    if (poppedEntry.value != 0x001934) return;
    y = 0x03;
    do {
        myMapper->writeCPU(0x005A + y, myMapper->readCPU(0x005E + y));
        opDEY(1);
    } while (!flgN);
    y = myMapper->readCPU(0x0089);
    myMapper->writeCPU(0x006E, myMapper->readCPU(0x0334 + y));
    a = 0x00;
    myMapper->writeCPU(0x0092, a);
    myMapper->writeCPU(0x0091, a);
    myMapper->writeCPU(0x0094, a);
    myMapper->writeCPU(0x0093, myMapper->readCPU(0x006E));
    pushAddress(0x001955);
    SUB_00338C();
    if (poppedEntry.value != 0x001955) return;
    a = 0x61;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x03);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x001969);
    SUB_00337F();
    if (poppedEntry.value != 0x001969) return;
    a = myMapper->readCPU(0x0084);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x10;
    pushAddress(0x001978);
    SUB_000850();
    if (poppedEntry.value != 0x001978) return;
    pushAddress(0x00197B);
    SUB_0006E9();
    if (poppedEntry.value != 0x00197B) return;
    pushAddress(0x00197E);
    SUB_00338C();
    if (poppedEntry.value != 0x00197E) return;
    a = 0x61;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x03);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x001992);
    SUB_00337F();
    if (poppedEntry.value != 0x001992) return;
    a = myMapper->readCPU(0x0084);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x18;
    pushAddress(0x0019A1);
    SUB_000850();
    if (poppedEntry.value != 0x0019A1) return;
    pushAddress(0x0019A4);
    SUB_0006E9();
    if (poppedEntry.value != 0x0019A4) return;
    myMapper->writeCPU(0x05FD, 0x00);
    while (myMapper->readCPU(0x05FD) < 0x04) {
        y = myMapper->readCPU(0x05FD);
        myMapper->writeCPU(0x05FE, myMapper->readCPU(0x005A + y));
        y = myMapper->readCPU(0x05FE);
        myMapper->writeCPU(0x0091, myMapper->readCPU(0xEA06 + y));
        y = myMapper->readCPU(0x05FE);
        myMapper->writeCPU(0x0092, myMapper->readCPU(0xEA16 + y));
        a = myMapper->readCPU(0x0093);
        pushAddress(0x0019CE);
        SUB_003653();
        if (poppedEntry.value != 0x0019CE) return;
        pushAddress(0x0019D1);
        SUB_00337F();
        if (poppedEntry.value != 0x0019D1) return;
        a = myMapper->readCPU(0x0084);
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = myMapper->readCPU(0x0091);
        opASL_A(3);
        flgC = false;
        opADC(0x78);
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = myMapper->readCPU(0x0092);
        opASL_A(3);
        flgC = false;
        opADC(0x08);
        pushAddress(0x0019ED);
        SUB_000850();
        if (poppedEntry.value != 0x0019ED) return;
        pushAddress(0x0019F0);
        SUB_00072F();
        if (poppedEntry.value != 0x0019F0) return;
        opINC(0x05FD, 1);
    }
    if (myMapper->readCPU(0x0316) == 0x06) {
        goto L_001A06;
    }
    pushAddress(0x001A00);
    SUB_001836();
    if (poppedEntry.value != 0x001A00) return;
    x = a;
    setLoadFlag(x);
    if (!flgZ) {
        goto L_001A07;
    }
L_001A06:
    popAddress();
    return;
L_001A07:
    pushAddress(0x001A07);
    SUB_00172B();
    if (poppedEntry.value != 0x001A07) return;
    a = 0x06;
    SUB_001B01();
    return;
}

void game::SUB_001A0F() {
    pushAddress(0x001A0F);
    SUB_003653();
    if (poppedEntry.value != 0x001A0F) return;
    myMapper->writeCPU(0x05FF, myMapper->readCPU(0x0043));
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0043));
    opAND(0x03);
    myMapper->writeCPU(0x0043, a);
    a = 0x44;
    x = 0x00;
    pushAddress(0x001A26);
    SUB_003669();
    if (poppedEntry.value != 0x001A26) return;
    x = 0x00;
    a = myMapper->readCPU(0x0043);
    pushAddress(0x001A2D);
    SUB_003328();
    if (poppedEntry.value != 0x001A2D) return;
    flgC = false;
    opADC(0x48);
    y = a;
    a = x;
    opADC(0x00);
    x = a;
    a = y;
    pushAddress(0x001A39);
    SUB_003669();
    if (poppedEntry.value != 0x001A39) return;
    x = 0x00;
    a = 0x04;
    pushAddress(0x001A40);
    SUB_0005A1();
    if (poppedEntry.value != 0x001A40) return;
    pushAddress(0x001A43);
    SUB_001836();
    if (poppedEntry.value != 0x001A43) return;
    x = a;
    setLoadFlag(x);
    if (flgZ) {
    }
    else {
        opINC(0x0322, 1);
        pushAddress(0x001A4F);
        SUB_001836();
        if (poppedEntry.value != 0x001A4F) return;
        x = a;
        setLoadFlag(x);
        if (flgZ) {
        }
        else {
            a = myMapper->readCPU(0x0322);
            flgC = true;
            opSBC(0x02);
            myMapper->writeCPU(0x0322, a);
            pushAddress(0x001A61);
            SUB_001836();
            if (poppedEntry.value != 0x001A61) return;
            x = a;
            setLoadFlag(x);
            if (flgZ) {
            }
            else {
                if (myMapper->readCPU(0x0059) != 0x02) {
                    goto L_001ABC;
                }
                a = 0x03;
                flgC = false;
                opADC(myMapper->readCPU(0x0322));
                myMapper->writeCPU(0x0322, a);
                pushAddress(0x001A79);
                SUB_001836();
                if (poppedEntry.value != 0x001A79) return;
                x = a;
                setLoadFlag(x);
                if (flgZ) {
                    goto L_001AF3;
                }
                a = myMapper->readCPU(0x0322);
                flgC = true;
                opSBC(0x02);
                myMapper->writeCPU(0x0322, a);
                myMapper->writeCPU(0x0043, myMapper->readCPU(0x05FF));
                a = 0x44;
                x = 0x00;
                pushAddress(0x001A91);
                SUB_003669();
                if (poppedEntry.value != 0x001A91) return;
                x = 0x00;
                a = myMapper->readCPU(0x0043);
                pushAddress(0x001A98);
                SUB_003328();
                if (poppedEntry.value != 0x001A98) return;
                flgC = false;
                opADC(0x48);
                y = a;
                a = x;
                opADC(0x00);
                x = a;
                a = y;
                pushAddress(0x001AA4);
                SUB_003669();
                if (poppedEntry.value != 0x001AA4) return;
                x = 0x00;
                a = 0x04;
                pushAddress(0x001AAB);
                SUB_0005A1();
                if (poppedEntry.value != 0x001AAB) return;
                if (myMapper->readCPU(0x003C) == 0) {
                    goto L_001AFE;
                }
                a = 0x06;
                pushAddress(0x001AB4);
                SUB_003653();
                if (poppedEntry.value != 0x001AB4) return;
                a = 0x00;
                goto L_001AFB;
            L_001ABC:
                opINC(0x0322, 1);
                myMapper->writeCPU(0x0043, myMapper->readCPU(0x05FF));
                a = 0x44;
                x = 0x00;
                pushAddress(0x001AC8);
                SUB_003669();
                if (poppedEntry.value != 0x001AC8) return;
                x = 0x00;
                a = myMapper->readCPU(0x0043);
                pushAddress(0x001ACF);
                SUB_003328();
                if (poppedEntry.value != 0x001ACF) return;
                flgC = false;
                opADC(0x48);
                y = a;
                a = x;
                opADC(0x00);
                x = a;
                a = y;
                pushAddress(0x001ADB);
                SUB_003669();
                if (poppedEntry.value != 0x001ADB) return;
                x = 0x00;
                a = 0x04;
                pushAddress(0x001AE2);
                SUB_0005A1();
                if (poppedEntry.value != 0x001AE2) return;
                if (myMapper->readCPU(0x003C) == 0) {
                    goto L_001AFE;
                }
                a = 0x06;
                pushAddress(0x001AEB);
                SUB_003653();
                if (poppedEntry.value != 0x001AEB) return;
                a = 0x00;
                goto L_001AFB;
            }
        }
    }
L_001AF3:
    if (myMapper->readCPU(0x003C) == 0) {
        goto L_001AFE;
    }
    a = x;
    pushAddress(0x001AF8);
    SUB_003653();
    if (poppedEntry.value != 0x001AF8) return;
L_001AFB:
    pushAddress(0x001AFB);
    SUB_000475();
    if (poppedEntry.value != 0x001AFB) return;
L_001AFE:
    SUB_0033D4();
    return;
}

void game::SUB_001B01() {
    pushAddress(0x001B01);
    SUB_003653();
    if (poppedEntry.value != 0x001B01) return;
    myMapper->writeCPU(0x0601, 0x05);
    myMapper->writeCPU(0x0602, myMapper->readCPU(0x0316));
    a = myMapper->readCPU(0x0316);
    if (a != 0x01) {
        if (a == 0x03) {
            goto L_001B38;
        }
        if (a == 0x04) {
            goto L_001B79;
        }
        if (a == 0x05) {
            goto L_001B71;
        }
        if (a != 0x07) {
            goto L_001BC4;
        }
    }
    if (myMapper->readCPU(0x003B) == 0) {
    }
    else {
        a = 0x00;
        pushAddress(0x001B32);
        SUB_000B32();
        if (poppedEntry.value != 0x001B32) return;
        goto L_001BC4;
    L_001B38:
        a = 0x9C;
        x = 0xEA;
        pushAddress(0x001B3C);
        SUB_000228();
        if (poppedEntry.value != 0x001B3C) return;
        myMapper->writeCPU(0x003E, myMapper->readCPU(0x0325));
        a = myMapper->readCPU(0x0325);
        if (a < 0x1E) {
        }
        else {
            a = 0x1E;
        }
        myMapper->writeCPU(0x00C4, a);
        a = 0x00;
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x00C5, a);
        y = 0x89;
        myMapper->writeCPU(0x0324, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x00A1, 0xFF);
        myMapper->writeCPU(0x00A4, 0x78);
        pushAddress(0x001B68);
        SUB_00227E();
        if (poppedEntry.value != 0x001B68) return;
        pushAddress(0x001B6B);
        SUB_0020A4();
        if (poppedEntry.value != 0x001B6B) return;
        goto L_001BC4;
    L_001B71:
        a = 0x04;
        pushAddress(0x001B73);
        SUB_000276();
        if (poppedEntry.value != 0x001B73) return;
        goto L_001BC4;
    L_001B79:
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x0083));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x0082));
        x = myMapper->readCPU(0x0081);
        a = myMapper->readCPU(0x0080);
        pushAddress(0x001B85);
        SUB_003484();
        if (poppedEntry.value != 0x001B85) return;
        x = 0x00;
        a = myMapper->readCPU(0x003A);
        pushAddress(0x001B8C);
        SUB_003328();
        if (poppedEntry.value != 0x001B8C) return;
        flgC = false;
        opADC(0x00);
        y = a;
        a = x;
        opADC(0x03);
        x = a;
        a = y;
        pushAddress(0x001B98);
        SUB_00345E();
        if (poppedEntry.value != 0x001B98) return;
        pushAddress(0x001B9B);
        SUB_003516();
        if (poppedEntry.value != 0x001B9B) return;
        if (!flgZ) {
            x = 0x00;
            a = myMapper->readCPU(0x003A);
            pushAddress(0x001BA4);
            SUB_003328();
            if (poppedEntry.value != 0x001BA4) return;
            flgC = false;
            opADC(0x00);
            y = a;
            a = x;
            opADC(0x03);
            x = a;
            a = y;
            pushAddress(0x001BB0);
            SUB_003669();
            if (poppedEntry.value != 0x001BB0) return;
            myMapper->writeCPU(0x00BF, myMapper->readCPU(0x0083));
            myMapper->writeCPU(0x00BE, myMapper->readCPU(0x0082));
            x = myMapper->readCPU(0x0081);
            a = myMapper->readCPU(0x0080);
            y = 0x00;
            pushAddress(0x001BC1);
            SUB_0036E6();
            if (poppedEntry.value != 0x001BC1) return;
        }
    }
L_001BC4:
    y = 0x00;
    myMapper->writeCPU(0x0316, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0316);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x01) {
            goto L_001C1C;
        }
        if (a == 0x02) {
            goto L_001C3A;
        }
        if (a == 0x03) {
            goto L_001CB0;
        }
        if (a == 0x04) {
            goto L_001D22;
        }
        if (a == 0x05) {
            goto L_001DCD;
        }
        if (a == 0x06) {
            goto L_001DE1;
        }
        if (a == 0x07) {
            goto L_001CF1;
        }
        SUB_0033D4();
        return;
    }
    a = 0xBC;
    x = 0xEA;
    pushAddress(0x001C02);
    SUB_000228();
    if (poppedEntry.value != 0x001C02) return;
    pushAddress(0x001C05);
    SUB_00027D();
    if (poppedEntry.value != 0x001C05) return;
    x = 0x20;
    a = 0x00;
    pushAddress(0x001C0C);
    SUB_000560();
    if (poppedEntry.value != 0x001C0C) return;
    a = 0xBA;
    x = 0xE6;
    pushAddress(0x001C13);
    SUB_000370();
    if (poppedEntry.value != 0x001C13) return;
    pushAddress(0x001C16);
    SUB_000286();
    if (poppedEntry.value != 0x001C16) return;
    SUB_0033D4();
    return;
L_001C1C:
    a = 0xBC;
    x = 0xEA;
    pushAddress(0x001C20);
    SUB_000228();
    if (poppedEntry.value != 0x001C20) return;
    pushAddress(0x001C23);
    SUB_00027D();
    if (poppedEntry.value != 0x001C23) return;
    x = 0x20;
    a = 0x00;
    pushAddress(0x001C2A);
    SUB_000560();
    if (poppedEntry.value != 0x001C2A) return;
    a = 0xB7;
    x = 0xE8;
    pushAddress(0x001C31);
    SUB_000370();
    if (poppedEntry.value != 0x001C31) return;
    pushAddress(0x001C34);
    SUB_000286();
    if (poppedEntry.value != 0x001C34) return;
    SUB_0033D4();
    return;
L_001C3A:
    a = 0x9C;
    x = 0xEA;
    pushAddress(0x001C3E);
    SUB_000228();
    if (poppedEntry.value != 0x001C3E) return;
    a = 0xAC;
    x = 0xEA;
    pushAddress(0x001C45);
    SUB_000232();
    if (poppedEntry.value != 0x001C45) return;
    a = 0x00;
    myMapper->writeCPU(0x0037, a);
    myMapper->writeCPU(0x0038, a);
    myMapper->writeCPU(0x00A9, a);
    myMapper->writeCPU(0x0042, a);
    if (myMapper->readCPU(0x0602) != 0x03) {
        a = myMapper->readCPU(0x0602);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == 0x01) {
                goto L_001C66;
            }
            if (a != 0x07) {
                goto L_001C80;
            }
        }
    }
L_001C66:
    pushAddress(0x001C66);
    SUB_0002A3();
    if (poppedEntry.value != 0x001C66) return;
    pushAddress(0x001C69);
    SUB_00027D();
    if (poppedEntry.value != 0x001C69) return;
    x = 0x20;
    a = 0x00;
    pushAddress(0x001C70);
    SUB_000560();
    if (poppedEntry.value != 0x001C70) return;
    a = 0xE6;
    x = 0xE2;
    pushAddress(0x001C77);
    SUB_000370();
    if (poppedEntry.value != 0x001C77) return;
    pushAddress(0x001C7A);
    SUB_000286();
    if (poppedEntry.value != 0x001C7A) return;
    SUB_0033D4();
    return;
L_001C80:
    if (myMapper->readCPU(0x0602) == 0x06) {
        pushAddress(0x001C87);
        SUB_002D4D();
        if (poppedEntry.value != 0x001C87) return;
    }
    pushAddress(0x001C8A);
    SUB_0028F4();
    if (poppedEntry.value != 0x001C8A) return;
    pushAddress(0x001C8D);
    SUB_003665();
    if (poppedEntry.value != 0x001C8D) return;
    x = 0x01;
    a = 0xDF;
    pushAddress(0x001C94);
    SUB_0003A7();
    if (poppedEntry.value != 0x001C94) return;
    if (myMapper->readCPU(0x003B) != 0) {
        a = 0x00;
        pushAddress(0x001C9D);
        SUB_000B32();
        if (poppedEntry.value != 0x001C9D) return;
    }
    if (myMapper->readCPU(0x0602) != 0x06) {
        SUB_0033D4();
        return;
    }
    pushAddress(0x001CAA);
    SUB_002D75();
    if (poppedEntry.value != 0x001CAA) return;
    SUB_0033D4();
    return;
L_001CB0:
    pushAddress(0x001CB0);
    SUB_0002A3();
    if (poppedEntry.value != 0x001CB0) return;
    pushAddress(0x001CB3);
    SUB_00027D();
    if (poppedEntry.value != 0x001CB3) return;
    a = 0xBC;
    x = 0xEA;
    pushAddress(0x001CBA);
    SUB_000228();
    if (poppedEntry.value != 0x001CBA) return;
    x = 0x20;
    a = 0x00;
    pushAddress(0x001CC1);
    SUB_000560();
    if (poppedEntry.value != 0x001CC1) return;
    a = 0xF7;
    x = 0xE4;
    pushAddress(0x001CC8);
    SUB_000370();
    if (poppedEntry.value != 0x001CC8) return;
    a = myMapper->readCPU(0x0325);
    pushAddress(0x001CCE);
    SUB_003667();
    if (poppedEntry.value != 0x001CCE) return;
    a = 0x0A;
    pushAddress(0x001CD3);
    SUB_00376C();
    if (poppedEntry.value != 0x001CD3) return;
    myMapper->writeCPU(0x0325, a);
    myMapper->writeCPU(0x0039, 0x00);
    pushAddress(0x001CDD);
    SUB_000286();
    if (poppedEntry.value != 0x001CDD) return;
    pushAddress(0x001CE0);
    SUB_002B05();
    if (poppedEntry.value != 0x001CE0) return;
    a = 0x01;
    pushAddress(0x001CE5);
    SUB_000603();
    if (poppedEntry.value != 0x001CE5) return;
    pushAddress(0x001CE8);
    SUB_00074D();
    if (poppedEntry.value != 0x001CE8) return;
    pushAddress(0x001CEB);
    SUB_00218E();
    if (poppedEntry.value != 0x001CEB) return;
    SUB_0033D4();
    return;
L_001CF1:
    pushAddress(0x001CF1);
    SUB_0002A3();
    if (poppedEntry.value != 0x001CF1) return;
    pushAddress(0x001CF4);
    SUB_00027D();
    if (poppedEntry.value != 0x001CF4) return;
    a = 0xBC;
    x = 0xEA;
    pushAddress(0x001CFB);
    SUB_000228();
    if (poppedEntry.value != 0x001CFB) return;
    x = 0x20;
    a = 0x00;
    pushAddress(0x001D02);
    SUB_000560();
    if (poppedEntry.value != 0x001D02) return;
    a = 0xAB;
    x = 0xE7;
    pushAddress(0x001D09);
    SUB_000370();
    if (poppedEntry.value != 0x001D09) return;
    pushAddress(0x001D0C);
    SUB_000286();
    if (poppedEntry.value != 0x001D0C) return;
    a = 0x00;
    myMapper->writeCPU(0x0099, a);
    myMapper->writeCPU(0x0097, a);
    myMapper->writeCPU(0x0098, 0xFF);
    pushAddress(0x001D19);
    SUB_0029DF();
    if (poppedEntry.value != 0x001D19) return;
    pushAddress(0x001D1C);
    SUB_002A72();
    if (poppedEntry.value != 0x001D1C) return;
    SUB_0033D4();
    return;
L_001D22:
    if (myMapper->readCPU(0x0602) == 0x06) {
        pushAddress(0x001D29);
        SUB_0028F4();
        if (poppedEntry.value != 0x001D29) return;
    }
    if (myMapper->readCPU(0x0602) == 0x05) {
    }
    else {
        pushAddress(0x001D36);
        SUB_0002A3();
        if (poppedEntry.value != 0x001D36) return;
        goto L_001D56;
    L_001D3C:
        pushAddress(0x001D3C);
        SUB_003665();
        if (poppedEntry.value != 0x001D3C) return;
        a = myMapper->readCPU(0x0037);
        x = myMapper->readCPU(0x0038);
        pushAddress(0x001D43);
        SUB_0003A7();
        if (poppedEntry.value != 0x001D43) return;
        a = 0x01;
        pushAddress(0x001D48);
        SUB_000603();
        if (poppedEntry.value != 0x001D48) return;
        a = 0x04;
        flgC = false;
        opADC(myMapper->readCPU(0x0037));
        myMapper->writeCPU(0x0037, a);
        if (flgC) {
            opINC(0x0038, 1);
        }
    L_001D56:
        opCMP(myMapper->readCPU(0x0038), 0x00);
        if (flgZ) {
            opCMP(myMapper->readCPU(0x0037), 0xF0);
        }
        if (!flgC) {
            goto L_001D3C;
        }
        pushAddress(0x001D62);
        SUB_003665();
        if (poppedEntry.value != 0x001D62) return;
        a = 0xEF;
        pushAddress(0x001D67);
        SUB_0003A7();
        if (poppedEntry.value != 0x001D67) return;
        pushAddress(0x001D6A);
        SUB_0018A4();
        if (poppedEntry.value != 0x001D6A) return;
        pushAddress(0x001D6D);
        SUB_0018A4();
        if (poppedEntry.value != 0x001D6D) return;
        pushAddress(0x001D70);
        SUB_00338C();
        if (poppedEntry.value != 0x001D70) return;
        a = 0x70;
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x00);
        a = 0x00;
        y = a;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        x = a;
        a = 0x0A;
        pushAddress(0x001D86);
        SUB_0005D4();
        if (poppedEntry.value != 0x001D86) return;
        a = myMapper->readCPU(0x0030);
        x = myMapper->readCPU(0x0031);
        pushAddress(0x001D8D);
        SUB_0036A1();
        if (poppedEntry.value != 0x001D8D) return;
        pushAddress(0x001D90);
        SUB_00367F();
        if (poppedEntry.value != 0x001D90) return;
        pushAddress(0x001D93);
        SUB_003669();
        if (poppedEntry.value != 0x001D93) return;
        x = 0x00;
        a = 0x0A;
        pushAddress(0x001D9A);
        SUB_003561();
        if (poppedEntry.value != 0x001D9A) return;
        myMapper->writeCPU(0x0600, a);
        y = myMapper->readCPU(0x0600);
        a = 0x01;
        myMapper->writeCPU(0x0070 + y, a);
        myMapper->writeCPU(0x007B, a);
        if (myMapper->readCPU(0x003A) == 0x01) {
            myMapper->writeCPU(0x0034, myMapper->readCPU(0xEA05));
            myMapper->writeCPU(0x0033, myMapper->readCPU(0xEA04));
        }
    }
    myMapper->writeCPU(0x009A, 0x01);
    if (myMapper->readCPU(0x003B) == 0) {
        SUB_0033D4();
        return;
    }
    a = 0x01;
    pushAddress(0x001DC7);
    SUB_000B32();
    if (poppedEntry.value != 0x001DC7) return;
    SUB_0033D4();
    return;
L_001DCD:
    a = 0x02;
    pushAddress(0x001DCF);
    SUB_000276();
    if (poppedEntry.value != 0x001DCF) return;
    if (myMapper->readCPU(0x003B) == 0) {
        SUB_0033D4();
        return;
    }
    a = 0x03;
    pushAddress(0x001DDB);
    SUB_000B32();
    if (poppedEntry.value != 0x001DDB) return;
    SUB_0033D4();
    return;
L_001DE1:
    a = 0x01;
    pushAddress(0x001DE3);
    SUB_000603();
    if (poppedEntry.value != 0x001DE3) return;
    pushAddress(0x001DE6);
    SUB_00074D();
    if (poppedEntry.value != 0x001DE6) return;
    pushAddress(0x001DE9);
    SUB_0011B2();
    if (poppedEntry.value != 0x001DE9) return;
    pushAddress(0x001DEC);
    SUB_000AF4();
    if (poppedEntry.value != 0x001DEC) return;
    if (myMapper->readCPU(0x003B) != 0) {
        a = 0x04;
        pushAddress(0x001DF5);
        SUB_003653();
        if (poppedEntry.value != 0x001DF5) return;
        a = 0x00;
        pushAddress(0x001DFA);
        SUB_000475();
        if (poppedEntry.value != 0x001DFA) return;
    }
    if (myMapper->readCPU(0x003B) != 0) {
        a = 0x78;
        pushAddress(0x001E03);
        SUB_000603();
        if (poppedEntry.value != 0x001E03) return;
    }
    if (myMapper->readCPU(0x003B) == 0) {
        goto L_001E14;
    }
    a = 0x0C;
    pushAddress(0x001E0C);
    SUB_003653();
    if (poppedEntry.value != 0x001E0C) return;
    a = 0x00;
    pushAddress(0x001E11);
    SUB_000475();
    if (poppedEntry.value != 0x001E11) return;
L_001E14:
    a = 0x05;
    pushAddress(0x001E16);
    SUB_000276();
    if (poppedEntry.value != 0x001E16) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001E1C);
    SUB_000603();
    if (poppedEntry.value != 0x001E1C) return;
    a = 0x06;
    pushAddress(0x001E21);
    SUB_000276();
    if (poppedEntry.value != 0x001E21) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001E27);
    SUB_000603();
    if (poppedEntry.value != 0x001E27) return;
    a = 0x07;
    pushAddress(0x001E2C);
    SUB_000276();
    if (poppedEntry.value != 0x001E2C) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001E32);
    SUB_000603();
    if (poppedEntry.value != 0x001E32) return;
    a = 0x08;
    pushAddress(0x001E37);
    SUB_000276();
    if (poppedEntry.value != 0x001E37) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001E3D);
    SUB_000603();
    if (poppedEntry.value != 0x001E3D) return;
    pushAddress(0x001E40);
    SUB_00337F();
    if (poppedEntry.value != 0x001E40) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x60;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    pushAddress(0x001E50);
    SUB_000850();
    if (poppedEntry.value != 0x001E50) return;
    myMapper->writeCPU(0x00A7, a);
    myMapper->writeCPU(0x00A8, x);
    pushAddress(0x001E57);
    SUB_00338C();
    if (poppedEntry.value != 0x001E57) return;
    a = 0x4C;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x0A;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x00A7);
    x = myMapper->readCPU(0x00A8);
    pushAddress(0x001E6F);
    SUB_0006E9();
    if (poppedEntry.value != 0x001E6F) return;
    pushAddress(0x001E72);
    SUB_00337F();
    if (poppedEntry.value != 0x001E72) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x60;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    pushAddress(0x001E82);
    SUB_000850();
    if (poppedEntry.value != 0x001E82) return;
    myMapper->writeCPU(0x00A7, a);
    myMapper->writeCPU(0x00A8, x);
    pushAddress(0x001E89);
    SUB_00338C();
    if (poppedEntry.value != 0x001E89) return;
    a = 0x57;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x0A;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x00A7);
    x = myMapper->readCPU(0x00A8);
    pushAddress(0x001EA1);
    SUB_0006E9();
    if (poppedEntry.value != 0x001EA1) return;
    pushAddress(0x001EA4);
    SUB_00337F();
    if (poppedEntry.value != 0x001EA4) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x60;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x80;
    pushAddress(0x001EB4);
    SUB_000850();
    if (poppedEntry.value != 0x001EB4) return;
    myMapper->writeCPU(0x00A7, a);
    myMapper->writeCPU(0x00A8, x);
    pushAddress(0x001EBB);
    SUB_00338C();
    if (poppedEntry.value != 0x001EBB) return;
    a = 0x62;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x0A;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x00A7);
    x = myMapper->readCPU(0x00A8);
    pushAddress(0x001ED3);
    SUB_0006E9();
    if (poppedEntry.value != 0x001ED3) return;
    a = 0x07;
    pushAddress(0x001ED8);
    SUB_000276();
    if (poppedEntry.value != 0x001ED8) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001EDE);
    SUB_000603();
    if (poppedEntry.value != 0x001EDE) return;
    a = 0x06;
    pushAddress(0x001EE3);
    SUB_000276();
    if (poppedEntry.value != 0x001EE3) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001EE9);
    SUB_000603();
    if (poppedEntry.value != 0x001EE9) return;
    a = 0x05;
    pushAddress(0x001EEE);
    SUB_000276();
    if (poppedEntry.value != 0x001EEE) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001EF4);
    SUB_000603();
    if (poppedEntry.value != 0x001EF4) return;
    a = 0x04;
    pushAddress(0x001EF9);
    SUB_000276();
    if (poppedEntry.value != 0x001EF9) return;
    a = myMapper->readCPU(0x0601);
    pushAddress(0x001EFF);
    SUB_000603();
    if (poppedEntry.value != 0x001EFF) return;
    SUB_0033D4();
    return;
}

void game::SUB_001F05() {
    opINC(0x007D, 1);
    if (myMapper->readCPU(0x007D) != 0x0A) {
        SUB_00204A();
        return;
    }
    x = 0x00;
    a = myMapper->readCPU(0x007F);
    pushAddress(0x001F14);
    SUB_0035F1();
    if (poppedEntry.value != 0x001F14) return;
    flgC = false;
    opADC(myMapper->readCPU(0x007E));
    myMapper->writeCPU(0x0603, a);
    a = myMapper->readCPU(0x0325);
    flgC = true;
    opSBC(myMapper->readCPU(0x0603));
    myMapper->writeCPU(0x00CC, a);
    if (myMapper->readCPU(0x00CC) != 0) {
        if (flgC) {
            goto L_001F7C;
        }
    }
    opINC(0x0325, 1);
    a = myMapper->readCPU(0x0325);
    if (a < 0x1E) {
        if (a >= 0x1E) {
            goto L_001F3D;
        }
        goto L_001F3F;
    L_001F3D:
        a = 0x1E;
    L_001F3F:
        myMapper->writeCPU(0x00C4, a);
        a = 0x00;
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x00C5, a);
        y = 0x89;
        myMapper->writeCPU(0x0324, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    }
    else {
        a = myMapper->readCPU(0x0325);
        if (a < 0x28) {
            if (a != 0x1E) {
                goto L_001F78;
            }
            a = 0x3B;
            pushAddress(0x001F5F);
            SUB_003653();
            if (poppedEntry.value != 0x001F5F) return;
            pushAddress(0x001F62);
            SUB_00337F();
            if (poppedEntry.value != 0x001F62) return;
            a = myMapper->readCPU(0x0084);
            y = 0x01;
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            a = 0x20;
            opDEY(1);
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            a = 0x48;
            pushAddress(0x001F72);
            SUB_000850();
            if (poppedEntry.value != 0x001F72) return;
            pushAddress(0x001F75);
            SUB_00072F();
            if (poppedEntry.value != 0x001F75) return;
        L_001F78:
            myMapper->writeCPU(0x00A3, 0x01);
        }
    }
L_001F7C:
    opINC(0x00A9, 1);
    opCMP(myMapper->readCPU(0x00A9), 0x08);
    x = 0x00;
    if (flgC) {
        myMapper->writeCPU(0x00A9, x);
    }
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x001F8A);
    SUB_003341();
    if (poppedEntry.value != 0x001F8A) return;
    flgC = false;
    opADC(0xCC);
    y = a;
    a = x;
    opADC(0xEA);
    x = a;
    a = y;
    pushAddress(0x001F96);
    SUB_000228();
    if (poppedEntry.value != 0x001F96) return;
    y = 0x0F;
    do {
        myMapper->writeCPU(0x00AA + y, myMapper->readCPU(0xEAAC + y));
        opDEY(1);
    } while (!flgN);
    x = 0x00;
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x001FA8);
    SUB_003341();
    if (poppedEntry.value != 0x001FA8) return;
    flgC = false;
    opADC(0xCC);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0xEA);
    myMapper->writeCPU(0x00C5, a);
    y = 0x01;
    myMapper->writeCPU(0x00AB, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x001FBF);
    SUB_003341();
    if (poppedEntry.value != 0x001FBF) return;
    flgC = false;
    opADC(0xCC);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0xEA);
    myMapper->writeCPU(0x00C5, a);
    opINY(1);
    myMapper->writeCPU(0x00AC, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x001FD5);
    SUB_003341();
    if (poppedEntry.value != 0x001FD5) return;
    flgC = false;
    opADC(0xCC);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0xEA);
    myMapper->writeCPU(0x00C5, a);
    opINY(1);
    myMapper->writeCPU(0x00AD, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x001FEB);
    SUB_003341();
    if (poppedEntry.value != 0x001FEB) return;
    flgC = false;
    opADC(0xCC);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0xEA);
    myMapper->writeCPU(0x00C5, a);
    y = 0x0E;
    myMapper->writeCPU(0x00B0, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x002002);
    SUB_003341();
    if (poppedEntry.value != 0x002002) return;
    flgC = false;
    opADC(0xCC);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0xEA);
    myMapper->writeCPU(0x00C5, a);
    opINY(1);
    myMapper->writeCPU(0x00B1, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    a = myMapper->readCPU(0x00A9);
    pushAddress(0x002018);
    SUB_003341();
    if (poppedEntry.value != 0x002018) return;
    flgC = false;
    opADC(0xCC);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0xEA);
    myMapper->writeCPU(0x00C5, a);
    y = 0x02;
    myMapper->writeCPU(0x00B4, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    a = 0xAA;
    x = 0x00;
    pushAddress(0x00202F);
    SUB_000232();
    if (poppedEntry.value != 0x00202F) return;
    pushAddress(0x002032);
    SUB_00227E();
    if (poppedEntry.value != 0x002032) return;
    myMapper->writeCPU(0x007D, 0x00);
    opINC(0x007E, 1);
    if (myMapper->readCPU(0x007E) != 0x0A) {
        goto L_002047;
    }
    myMapper->writeCPU(0x007E, 0x00);
    opINC(0x007F, 1);
L_002047:
    SUB_00204A();
    return;
}

void game::SUB_00204A() {
    a = myMapper->readCPU(0x007F);
    flgC = false;
    opADC(0x30);
    pushAddress(0x00204F);
    SUB_003653();
    if (poppedEntry.value != 0x00204F) return;
    pushAddress(0x002052);
    SUB_00337F();
    if (poppedEntry.value != 0x002052) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x20;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x18;
    pushAddress(0x002062);
    SUB_000850();
    if (poppedEntry.value != 0x002062) return;
    pushAddress(0x002065);
    SUB_00072F();
    if (poppedEntry.value != 0x002065) return;
    a = myMapper->readCPU(0x007E);
    flgC = false;
    opADC(0x30);
    pushAddress(0x00206D);
    SUB_003653();
    if (poppedEntry.value != 0x00206D) return;
    pushAddress(0x002070);
    SUB_00337F();
    if (poppedEntry.value != 0x002070) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x28;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x18;
    pushAddress(0x002080);
    SUB_000850();
    if (poppedEntry.value != 0x002080) return;
    pushAddress(0x002083);
    SUB_00072F();
    if (poppedEntry.value != 0x002083) return;
    a = myMapper->readCPU(0x007D);
    flgC = false;
    opADC(0x30);
    pushAddress(0x00208B);
    SUB_003653();
    if (poppedEntry.value != 0x00208B) return;
    pushAddress(0x00208E);
    SUB_00337F();
    if (poppedEntry.value != 0x00208E) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x30;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x18;
    pushAddress(0x00209E);
    SUB_000850();
    if (poppedEntry.value != 0x00209E) return;
    SUB_00072F();
    return;
}

void game::SUB_0020A4() {
    myMapper->writeCPU(0x00BF, myMapper->readCPU(0x0083));
    myMapper->writeCPU(0x00BE, myMapper->readCPU(0x0082));
    x = myMapper->readCPU(0x0081);
    myMapper->writeCPU(0x0604, myMapper->readCPU(0x0080));
    myMapper->writeCPU(0x0605, x);
    myMapper->writeCPU(0x0606, myMapper->readCPU(0x00BE));
    myMapper->writeCPU(0x0607, myMapper->readCPU(0x00BF));
    pushAddress(0x0020C0);
    SUB_00338C();
    if (poppedEntry.value != 0x0020C0) return;
    a = 0x75;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x06;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0020D4);
    SUB_00337F();
    if (poppedEntry.value != 0x0020D4) return;
    a = myMapper->readCPU(0x0084);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x00;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x30;
    pushAddress(0x0020E3);
    SUB_000850();
    if (poppedEntry.value != 0x0020E3) return;
    pushAddress(0x0020E6);
    SUB_0006E9();
    if (poppedEntry.value != 0x0020E6) return;
    myMapper->writeCPU(0x0608, 0x00);
    goto L_00216B;
    while (true) {
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x0607));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x0606));
        x = myMapper->readCPU(0x0605);
        a = myMapper->readCPU(0x0604);
        pushAddress(0x002101);
        SUB_003484();
        if (poppedEntry.value != 0x002101) return;
        x = 0x00;
        a = 0x0A;
        pushAddress(0x002108);
        SUB_00351C();
        if (poppedEntry.value != 0x002108) return;
        pushAddress(0x00210B);
        SUB_003653();
        if (poppedEntry.value != 0x00210B) return;
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
        flgC = false;
        opADC(0x30);
        pushAddress(0x002115);
        SUB_003653();
        if (poppedEntry.value != 0x002115) return;
        pushAddress(0x002118);
        SUB_00337F();
        if (poppedEntry.value != 0x002118) return;
        a = myMapper->readCPU(0x0084);
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x30;
        pushAddress(0x002123);
        SUB_003667();
        if (poppedEntry.value != 0x002123) return;
        a = myMapper->readCPU(0x0608);
        pushAddress(0x002129);
        SUB_003333();
        if (poppedEntry.value != 0x002129) return;
        pushAddress(0x00212C);
        SUB_00370A();
        if (poppedEntry.value != 0x00212C) return;
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x30;
        pushAddress(0x002135);
        SUB_000850();
        if (poppedEntry.value != 0x002135) return;
        pushAddress(0x002138);
        SUB_00072F();
        if (poppedEntry.value != 0x002138) return;
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x0607));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x0606));
        x = myMapper->readCPU(0x0605);
        a = myMapper->readCPU(0x0604);
        pushAddress(0x00214B);
        SUB_003484();
        if (poppedEntry.value != 0x00214B) return;
        x = 0x00;
        a = 0x0A;
        pushAddress(0x002152);
        SUB_00349C();
        if (poppedEntry.value != 0x002152) return;
        myMapper->writeCPU(0x0604, a);
        myMapper->writeCPU(0x0605, x);
        myMapper->writeCPU(0x0606, myMapper->readCPU(0x00BE));
        y = myMapper->readCPU(0x00BF);
        myMapper->writeCPU(0x0607, y);
        opINC(0x0608, 1);
        pushAddress(0x002168);
        SUB_0033D4();
        if (poppedEntry.value != 0x002168) return;
    L_00216B:
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x0607));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x0606));
        x = myMapper->readCPU(0x0605);
        a = myMapper->readCPU(0x0604);
        pushAddress(0x00217B);
        SUB_003484();
        if (poppedEntry.value != 0x00217B) return;
        x = 0x00;
        myMapper->writeCPU(0x00BE, x);
        myMapper->writeCPU(0x00BF, x);
        a = x;
        pushAddress(0x002185);
        SUB_003475();
        if (poppedEntry.value != 0x002185) return;
        if (flgZ) {
            goto L_00218D;
        }
    }
L_00218D:
    popAddress();
}

void game::SUB_00218E() {
    x = 0x00;
    a = myMapper->readCPU(0x003A);
    pushAddress(0x002192);
    SUB_003328();
    if (poppedEntry.value != 0x002192) return;
    flgC = false;
    opADC(0x00);
    y = a;
    a = x;
    opADC(0x03);
    x = a;
    a = y;
    pushAddress(0x00219E);
    SUB_00345E();
    if (poppedEntry.value != 0x00219E) return;
    myMapper->writeCPU(0x0609, a);
    myMapper->writeCPU(0x060A, x);
    myMapper->writeCPU(0x060B, myMapper->readCPU(0x00BE));
    myMapper->writeCPU(0x060C, myMapper->readCPU(0x00BF));
    pushAddress(0x0021B1);
    SUB_00338C();
    if (poppedEntry.value != 0x0021B1) return;
    a = 0x6D;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x07;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0021C5);
    SUB_00337F();
    if (poppedEntry.value != 0x0021C5) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0xD8;
    pushAddress(0x0021D3);
    SUB_000850();
    if (poppedEntry.value != 0x0021D3) return;
    pushAddress(0x0021D6);
    SUB_0006E9();
    if (poppedEntry.value != 0x0021D6) return;
    myMapper->writeCPU(0x060D, 0x00);
    goto L_00225B;
    while (true) {
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x060C));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x060B));
        x = myMapper->readCPU(0x060A);
        a = myMapper->readCPU(0x0609);
        pushAddress(0x0021F1);
        SUB_003484();
        if (poppedEntry.value != 0x0021F1) return;
        x = 0x00;
        a = 0x0A;
        pushAddress(0x0021F8);
        SUB_00351C();
        if (poppedEntry.value != 0x0021F8) return;
        pushAddress(0x0021FB);
        SUB_003653();
        if (poppedEntry.value != 0x0021FB) return;
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
        flgC = false;
        opADC(0x30);
        pushAddress(0x002205);
        SUB_003653();
        if (poppedEntry.value != 0x002205) return;
        pushAddress(0x002208);
        SUB_00337F();
        if (poppedEntry.value != 0x002208) return;
        a = 0x00;
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xB8;
        pushAddress(0x002213);
        SUB_003667();
        if (poppedEntry.value != 0x002213) return;
        a = myMapper->readCPU(0x060D);
        pushAddress(0x002219);
        SUB_003333();
        if (poppedEntry.value != 0x002219) return;
        pushAddress(0x00221C);
        SUB_00370A();
        if (poppedEntry.value != 0x00221C) return;
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0xD8;
        pushAddress(0x002225);
        SUB_000850();
        if (poppedEntry.value != 0x002225) return;
        pushAddress(0x002228);
        SUB_00072F();
        if (poppedEntry.value != 0x002228) return;
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x060C));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x060B));
        x = myMapper->readCPU(0x060A);
        a = myMapper->readCPU(0x0609);
        pushAddress(0x00223B);
        SUB_003484();
        if (poppedEntry.value != 0x00223B) return;
        x = 0x00;
        a = 0x0A;
        pushAddress(0x002242);
        SUB_00349C();
        if (poppedEntry.value != 0x002242) return;
        myMapper->writeCPU(0x0609, a);
        myMapper->writeCPU(0x060A, x);
        myMapper->writeCPU(0x060B, myMapper->readCPU(0x00BE));
        y = myMapper->readCPU(0x00BF);
        myMapper->writeCPU(0x060C, y);
        opINC(0x060D, 1);
        pushAddress(0x002258);
        SUB_0033D4();
        if (poppedEntry.value != 0x002258) return;
    L_00225B:
        myMapper->writeCPU(0x00BF, myMapper->readCPU(0x060C));
        myMapper->writeCPU(0x00BE, myMapper->readCPU(0x060B));
        x = myMapper->readCPU(0x060A);
        a = myMapper->readCPU(0x0609);
        pushAddress(0x00226B);
        SUB_003484();
        if (poppedEntry.value != 0x00226B) return;
        x = 0x00;
        myMapper->writeCPU(0x00BE, x);
        myMapper->writeCPU(0x00BF, x);
        a = x;
        pushAddress(0x002275);
        SUB_003475();
        if (poppedEntry.value != 0x002275) return;
        if (flgZ) {
            goto L_00227D;
        }
    }
L_00227D:
    popAddress();
}

void game::SUB_00227E() {
    myMapper->writeCPU(0x060E, myMapper->readCPU(0x0325));
    a = 0x00;
    myMapper->writeCPU(0x060F, a);
    x = a;
    if (myMapper->readCPU(0x0325) < 0x0A) {
        goto L_002294;
    }
    goto L_002310;
L_002294:
    pushAddress(0x002294);
    SUB_00338C();
    if (poppedEntry.value != 0x002294) return;
    a = 0x72;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0022A7);
    SUB_00337F();
    if (poppedEntry.value != 0x0022A7) return;
    a = myMapper->readCPU(0x0084);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x28;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x48;
    pushAddress(0x0022B6);
    SUB_000850();
    if (poppedEntry.value != 0x0022B6) return;
    pushAddress(0x0022B9);
    SUB_0006E9();
    if (poppedEntry.value != 0x0022B9) return;
    goto L_00230E;
L_0022BF:
    a = myMapper->readCPU(0x060E);
    pushAddress(0x0022C2);
    SUB_003669();
    if (poppedEntry.value != 0x0022C2) return;
    a = 0x0A;
    pushAddress(0x0022C7);
    SUB_00376E();
    if (poppedEntry.value != 0x0022C7) return;
    pushAddress(0x0022CA);
    SUB_003653();
    if (poppedEntry.value != 0x0022CA) return;
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x30);
    pushAddress(0x0022D4);
    SUB_003653();
    if (poppedEntry.value != 0x0022D4) return;
    pushAddress(0x0022D7);
    SUB_00337F();
    if (poppedEntry.value != 0x0022D7) return;
    a = myMapper->readCPU(0x0084);
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x30;
    pushAddress(0x0022E2);
    SUB_003667();
    if (poppedEntry.value != 0x0022E2) return;
    a = myMapper->readCPU(0x060F);
    pushAddress(0x0022E8);
    SUB_003333();
    if (poppedEntry.value != 0x0022E8) return;
    pushAddress(0x0022EB);
    SUB_00370A();
    if (poppedEntry.value != 0x0022EB) return;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x48;
    pushAddress(0x0022F4);
    SUB_000850();
    if (poppedEntry.value != 0x0022F4) return;
    pushAddress(0x0022F7);
    SUB_00072F();
    if (poppedEntry.value != 0x0022F7) return;
    a = myMapper->readCPU(0x060E);
    pushAddress(0x0022FD);
    SUB_003667();
    if (poppedEntry.value != 0x0022FD) return;
    a = 0x0A;
    pushAddress(0x002302);
    SUB_00371D();
    if (poppedEntry.value != 0x002302) return;
    myMapper->writeCPU(0x060E, a);
    opINC(0x060F, 1);
    pushAddress(0x00230B);
    SUB_0033D4();
    if (poppedEntry.value != 0x00230B) return;
L_00230E:
    x = 0x00;
L_002310:
    if (myMapper->readCPU(0x060E) != 0) {
        goto L_0022BF;
    }
    popAddress();
}

void game::SUB_002316() {
    pushAddress(0x002316);
    SUB_003653();
    if (poppedEntry.value != 0x002316) return;
    myMapper->writeCPU(0x0611, 0x00);
    myMapper->writeCPU(0x0612, myMapper->readCPU(0x0325));
    pushAddress(0x002324);
    SUB_00338C();
    if (poppedEntry.value != 0x002324) return;
    a = 0xED;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x05);
    a = 0xFF;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    x = 0x00;
    a = 0x04;
    pushAddress(0x00233C);
    SUB_0005D4();
    if (poppedEntry.value != 0x00233C) return;
    y = 0x00;
    myMapper->writeCPU(0x0092, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    while (true) {
        if (myMapper->readCPU(0x0092) >= 0x04) {
            goto L_00234E;
        }
        goto L_002410;
    L_00234E:
        myMapper->writeCPU(0x0610, 0x01);
        myMapper->writeCPU(0x0091, 0x00);
        while (myMapper->readCPU(0x0091) < 0x0A) {
            y = myMapper->readCPU(0x0092);
            x = 0x00;
            a = myMapper->readCPU(0x0349 + y);
            flgC = false;
            opADC(myMapper->readCPU(0x0091));
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0xF9;
            a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                y = myMapper->readCPU(0x0092);
                x = 0x00;
                a = myMapper->readCPU(0x0349 + y);
                flgC = false;
                opADC(myMapper->readCPU(0x0091));
                if (!flgC) {
                    goto L_002385;
                }
                opINX(1);
            L_002385:
                myMapper->writeCPU(0x00C4, a);
                a = x;
                flgC = false;
                opADC(0x03);
                myMapper->writeCPU(0x00C5, a);
                y = 0xF9;
                if (myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y) != 0x01) {
                    goto L_00239D;
                }
                a = 0x00;
            }
            myMapper->writeCPU(0x0610, a);
            goto L_0023A2;
        L_00239D:
            opINC(0x0091, 1);
        }
    L_0023A2:
        if (myMapper->readCPU(0x0610) == 0) {
            goto L_00240B;
        }
        myMapper->writeCPU(0x0091, 0x00);
        while (myMapper->readCPU(0x0091) < 0x0A) {
            y = myMapper->readCPU(0x0091);
            if (myMapper->readCPU(0x0070 + y) >= 0x04) {
                y = myMapper->readCPU(0x0091);
                x = 0x00;
                a = myMapper->readCPU(0x0070 + y);
                flgC = true;
                opSBC(0x04);
                if (!flgC) {
                    opDEX(1);
                }
                pushAddress(0x0023C7);
                SUB_003669();
                if (poppedEntry.value != 0x0023C7) return;
                a = 0x17;
                flgC = true;
                opSBC(myMapper->readCPU(0x0092));
                pushAddress(0x0023CF);
                SUB_0033A6();
                if (poppedEntry.value != 0x0023CF) return;
                if (!flgC) {
                    goto L_0023D8;
                }
                myMapper->writeCPU(0x0032, 0x3C);
            }
        L_0023D8:
            opINC(0x0091, 1);
        }
        pushAddress(0x0023DD);
        SUB_001F05();
        if (poppedEntry.value != 0x0023DD) return;
        y = myMapper->readCPU(0x0092);
        a = myMapper->readCPU(0x0349 + y);
        flgC = false;
        opADC(0xF9);
        y = a;
        a = 0x00;
        opADC(0x03);
        x = a;
        a = y;
        pushAddress(0x0023EF);
        SUB_003669();
        if (poppedEntry.value != 0x0023EF) return;
        a = 0x61;
        x = 0x03;
        pushAddress(0x0023F6);
        SUB_003669();
        if (poppedEntry.value != 0x0023F6) return;
        x = 0x00;
        a = 0x0A;
        pushAddress(0x0023FD);
        SUB_0005A1();
        if (poppedEntry.value != 0x0023FD) return;
        y = myMapper->readCPU(0x0611);
        myMapper->writeCPU(0x05ED + y, myMapper->readCPU(0x0092));
        opINC(0x0611, 1);
    L_00240B:
        opDEC(0x0092, 1);
    }
L_002410:
    if (myMapper->readCPU(0x0611) == 0) {
        SUB_0033D4();
        return;
    }
    x = 0x00;
    if (myMapper->readCPU(0x0325) != myMapper->readCPU(0x0612)) {
        if (myMapper->readCPU(0x003C) == 0) {
            goto L_00244A;
        }
        a = 0x07;
    }
    else {
        if (myMapper->readCPU(0x0611) != 0x04) {
            goto L_00243B;
        }
        if (myMapper->readCPU(0x003C) == 0) {
            goto L_00244A;
        }
        a = 0x03;
        goto L_002441;
    L_00243B:
        if (myMapper->readCPU(0x003C) == 0) {
            goto L_00244A;
        }
        a = 0x02;
    }
L_002441:
    pushAddress(0x002441);
    SUB_003653();
    if (poppedEntry.value != 0x002441) return;
    a = x;
    pushAddress(0x002445);
    SUB_000475();
    if (poppedEntry.value != 0x002445) return;
    x = 0x00;
L_00244A:
    a = myMapper->readCPU(0x0611);
    if (a != 0x01) {
        if (a == 0x02) {
            goto L_002465;
        }
        if (a == 0x03) {
            goto L_00246A;
        }
        if (a == 0x04) {
            goto L_002470;
        }
    }
    else {
        a = 0x28;
        goto L_002474;
    L_002465:
        a = 0x64;
        goto L_002474;
    L_00246A:
        opINX(1);
        a = 0x2C;
        goto L_002474;
    }
L_002470:
    x = 0x04;
    a = 0xB0;
L_002474:
    myMapper->writeCPU(0x00BA, a);
    myMapper->writeCPU(0x00BB, x);
    a = myMapper->readCPU(0x00BA);
    x = myMapper->readCPU(0x00BB);
    pushAddress(0x00247C);
    SUB_003669();
    if (poppedEntry.value != 0x00247C) return;
    x = 0x00;
    a = myMapper->readCPU(0x0325);
    flgC = false;
    opADC(0x01);
    if (flgC) {
        opINX(1);
    }
    pushAddress(0x00248A);
    SUB_003572();
    if (poppedEntry.value != 0x00248A) return;
    y = 0x00;
    myMapper->writeCPU(0x00BE, y);
    myMapper->writeCPU(0x00BF, y);
    myMapper->writeCPU(0x00C4, 0x80);
    y = 0x00;
    pushAddress(0x002499);
    SUB_0033FE();
    if (poppedEntry.value != 0x002499) return;
    pushAddress(0x00249C);
    SUB_0020A4();
    if (poppedEntry.value != 0x00249C) return;
    if (myMapper->readCPU(0x0032) == 0) {
        goto L_0024A6;
    }
    pushAddress(0x0024A3);
    SUB_0011B2();
    if (poppedEntry.value != 0x0024A3) return;
L_0024A6:
    pushAddress(0x0024A6);
    SUB_0024AC();
    if (poppedEntry.value != 0x0024A6) return;
    SUB_0033D4();
    return;
}

void game::SUB_0024AC() {
    a = 0x01;
    pushAddress(0x0024AE);
    SUB_000603();
    if (poppedEntry.value != 0x0024AE) return;
    pushAddress(0x0024B1);
    SUB_00074D();
    if (poppedEntry.value != 0x0024B1) return;
    myMapper->writeCPU(0x0613, 0x04);
    while (true) {
    L_0024B9:
        x = myMapper->readCPU(0x0613);
        setLoadFlag(x);
        if (flgN) {
            goto L_002602;
        }
        myMapper->writeCPU(0x0614, 0x00);
        while (myMapper->readCPU(0x0614) < 0x14) {
            a = 0xD9;
            x = 0x05;
            flgC = false;
            opADC(myMapper->readCPU(0x0614));
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00BE, a);
            myMapper->writeCPU(0x00BF, x);
            x = 0x00;
            a = myMapper->readCPU(0x0614);
            flgC = false;
            opADC(0x03);
            if (flgC) {
                opINX(1);
                flgC = false;
            }
            opADC(0x01);
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0x49;
            myMapper->writeCPU(0x00C4, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
            x = 0x00;
            a = myMapper->readCPU(0x0613);
            setLoadFlag(a);
            if (flgN) {
                opDEX(1);
            }
            flgC = false;
            opADC(myMapper->readCPU(0x00C4));
            if (!flgC) {
                goto L_002509;
            }
            opINX(1);
        L_002509:
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0xF9;
            a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
            y = 0x00;
            myMapper->writeCPU(myMapper->readCPU(0x00BE) + (myMapper->readCPU((0x00BE + 1) & 0x00ff) << 8) + y, a);
            opINC(0x0614, 1);
        }
        pushAddress(0x00251F);
        SUB_00338C();
        if (poppedEntry.value != 0x00251F) return;
        a = 0xD9;
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x05);
        a = 0x14;
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        pushAddress(0x002533);
        SUB_00337F();
        if (poppedEntry.value != 0x002533) return;
        a = myMapper->readCPU(0x0084);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = myMapper->readCPU(0x0613);
        opASL_A(3);
        flgC = false;
        opADC(0x60);
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x30;
        pushAddress(0x002549);
        SUB_000850();
        if (poppedEntry.value != 0x002549) return;
        pushAddress(0x00254C);
        SUB_000720();
        if (poppedEntry.value != 0x00254C) return;
        myMapper->writeCPU(0x0614, 0x00);
        while (myMapper->readCPU(0x0614) < 0x14) {
            a = 0xD9;
            x = 0x05;
            flgC = false;
            opADC(myMapper->readCPU(0x0614));
            if (flgC) {
                opINX(1);
            }
            pushAddress(0x002566);
            SUB_003669();
            if (poppedEntry.value != 0x002566) return;
            x = 0x00;
            a = myMapper->readCPU(0x0614);
            flgC = false;
            opADC(0x03);
            if (flgC) {
                opINX(1);
                flgC = false;
            }
            opADC(0x01);
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0x49;
            a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
            pushAddress(0x002586);
            SUB_003667();
            if (poppedEntry.value != 0x002586) return;
            a = 0x09;
            pushAddress(0x00258B);
            SUB_003667();
            if (poppedEntry.value != 0x00258B) return;
            a = myMapper->readCPU(0x0613);
            setLoadFlag(a);
            if (!flgN) {
                goto L_002595;
            }
            x = 0xFF;
        L_002595:
            pushAddress(0x002595);
            SUB_00370A();
            if (poppedEntry.value != 0x002595) return;
            pushAddress(0x002598);
            SUB_003300();
            if (poppedEntry.value != 0x002598) return;
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0xF9;
            a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
            y = 0x00;
            pushAddress(0x0025A9);
            SUB_0036D0();
            if (poppedEntry.value != 0x0025A9) return;
            opINC(0x0614, 1);
        }
        pushAddress(0x0025B2);
        SUB_00338C();
        if (poppedEntry.value != 0x0025B2) return;
        a = 0xD9;
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x05);
        a = 0x14;
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        pushAddress(0x0025C6);
        SUB_00337F();
        if (poppedEntry.value != 0x0025C6) return;
        a = myMapper->readCPU(0x0084);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x09;
        pushAddress(0x0025D0);
        SUB_003667();
        if (poppedEntry.value != 0x0025D0) return;
        a = myMapper->readCPU(0x0613);
        setLoadFlag(a);
        if (!flgN) {
            goto L_0025DA;
        }
        x = 0xFF;
    L_0025DA:
        pushAddress(0x0025DA);
        SUB_00370A();
        if (poppedEntry.value != 0x0025DA) return;
        opASL_A(3);
        flgC = false;
        opADC(0x60);
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x30;
        pushAddress(0x0025E9);
        SUB_000850();
        if (poppedEntry.value != 0x0025E9) return;
        pushAddress(0x0025EC);
        SUB_000720();
        if (poppedEntry.value != 0x0025EC) return;
        a = 0x05;
        pushAddress(0x0025F1);
        SUB_000603();
        if (poppedEntry.value != 0x0025F1) return;
        pushAddress(0x0025F4);
        SUB_00074D();
        if (poppedEntry.value != 0x0025F4) return;
        opDEC(0x0613, 1);
        if (flgN) {
            goto L_0025FF;
        }
    }
L_0025FF:
    goto L_0024B9;
L_002602:
    a = 0x17;
    flgC = true;
    opSBC(myMapper->readCPU(0x05ED));
    myMapper->writeCPU(0x0616, a);
    myMapper->writeCPU(0x0615, 0x00);
    while (myMapper->readCPU(0x0615) < 0x0A) {
        y = myMapper->readCPU(0x0615);
        if (myMapper->readCPU(0x0070 + y) >= 0x04) {
            y = myMapper->readCPU(0x0615);
            x = 0x00;
            a = myMapper->readCPU(0x0070 + y);
            flgC = true;
            opSBC(0x04);
            if (flgC) {
                goto L_00262F;
            }
            opDEX(1);
        L_00262F:
            opCMP(a, myMapper->readCPU(0x0616));
            a = x;
            opSBC(0x00);
            if (flgC) {
                goto L_00265D;
            }
            goto L_002665;
            do {
                a = 0x70;
                x = 0x00;
                flgC = false;
                opADC(myMapper->readCPU(0x0615));
                if (!flgC) {
                    goto L_002645;
                }
                opINX(1);
            L_002645:
                myMapper->writeCPU(0x00C4, a);
                myMapper->writeCPU(0x00C5, x);
                y = 0x00;
                a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
                flgC = true;
                opSBC(0x01);
                myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
                a = 0x01;
                pushAddress(0x002654);
                SUB_000603();
                if (poppedEntry.value != 0x002654) return;
                pushAddress(0x002657);
                SUB_0011B2();
                if (poppedEntry.value != 0x002657) return;
                pushAddress(0x00265A);
                SUB_00074D();
                if (poppedEntry.value != 0x00265A) return;
            L_00265D:
                y = myMapper->readCPU(0x0615);
            } while (myMapper->readCPU(0x0070 + y) != 0);
        }
    L_002665:
        opINC(0x0615, 1);
    }
    myMapper->writeCPU(0x0617, 0x03);
    while (true) {
        do {
            x = myMapper->readCPU(0x0617);
            setLoadFlag(x);
            if (flgN) {
                goto L_0026B0;
            }
            y = myMapper->readCPU(0x0617);
            a = myMapper->readCPU(0x05ED + y);
            myMapper->writeCPU(0x0616, a);
            if (a == 0xFF) {
                goto L_0026A8;
            }
            y = 0x00;
            do {
                myMapper->writeCPU(0x04E9 + y, myMapper->readCPU(0x03F9 + y));
                opINY(1);
            } while (y != 0xF0);
            a = 0x03;
            x = 0x04;
            pushAddress(0x002693);
            SUB_003669();
            if (poppedEntry.value != 0x002693) return;
            a = 0xE9;
            x = 0x04;
            pushAddress(0x00269A);
            SUB_003669();
            if (poppedEntry.value != 0x00269A) return;
            x = 0x00;
            a = myMapper->readCPU(0x0616);
            pushAddress(0x0026A2);
            SUB_0035F1();
            if (poppedEntry.value != 0x0026A2) return;
            pushAddress(0x0026A5);
            SUB_0005A1();
            if (poppedEntry.value != 0x0026A5) return;
        L_0026A8:
            opDEC(0x0617, 1);
        } while (!flgN);
    }
L_0026B0:
    SUB_0026B3();
    return;
}

void game::SUB_0026B3() {
    if (myMapper->readCPU(0x0316) != 0x04) {
        goto L_0026BD;
    }
    pushAddress(0x0026BA);
    SUB_0011B2();
    if (poppedEntry.value != 0x0026BA) return;
L_0026BD:
    myMapper->writeCPU(0x0091, 0x00);
    while (true) {
        if (myMapper->readCPU(0x0091) < 0x0A) {
            goto L_0026C8;
        }
        popAddress();
        return;
    L_0026C8:
        myMapper->writeCPU(0x0092, 0x00);
        while (myMapper->readCPU(0x0092) < 0x14) {
            a = 0xD9;
            x = 0x05;
            flgC = false;
            opADC(myMapper->readCPU(0x0092));
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00BE, a);
            myMapper->writeCPU(0x00BF, x);
            x = 0x00;
            a = myMapper->readCPU(0x0092);
            flgC = false;
            opADC(0x03);
            if (flgC) {
                opINX(1);
                flgC = false;
            }
            opADC(0x01);
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0x49;
            x = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
            flgC = false;
            opADC(myMapper->readCPU(0x0091));
            if (!flgC) {
                goto L_002704;
            }
            opINX(1);
        L_002704:
            myMapper->writeCPU(0x00C4, a);
            a = x;
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00C5, a);
            y = 0xF9;
            a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
            y = 0x00;
            myMapper->writeCPU(myMapper->readCPU(0x00BE) + (myMapper->readCPU((0x00BE + 1) & 0x00ff) << 8) + y, a);
            opINC(0x0092, 1);
        }
        pushAddress(0x002719);
        SUB_00338C();
        if (poppedEntry.value != 0x002719) return;
        a = 0xD9;
        y = 0x01;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x05);
        a = 0x14;
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        pushAddress(0x00272D);
        SUB_00337F();
        if (poppedEntry.value != 0x00272D) return;
        a = myMapper->readCPU(0x0084);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = myMapper->readCPU(0x0091);
        opASL_A(3);
        flgC = false;
        opADC(0x60);
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x30;
        pushAddress(0x002742);
        SUB_000850();
        if (poppedEntry.value != 0x002742) return;
        pushAddress(0x002745);
        SUB_000720();
        if (poppedEntry.value != 0x002745) return;
        a = myMapper->readCPU(0x0091);
        pushAddress(0x00274A);
        SUB_003667();
        if (poppedEntry.value != 0x00274A) return;
        a = 0x03;
        pushAddress(0x00274F);
        SUB_00376C();
        if (poppedEntry.value != 0x00274F) return;
        if (x == 0x00) {
            if (a != 0x00) {
                goto L_002762;
            }
            a = 0x01;
            pushAddress(0x00275C);
            SUB_000603();
            if (poppedEntry.value != 0x00275C) return;
            pushAddress(0x00275F);
            SUB_00074D();
            if (poppedEntry.value != 0x00275F) return;
        }
    L_002762:
        opINC(0x0091, 1);
    }
    SUB_002767();
    return;
}

void game::SUB_002767() {
    a = 0x00;
    myMapper->writeCPU(0x061A, a);
    myMapper->writeCPU(0x0618, a);
    while (true) {
    L_00276F:
        a = myMapper->readCPU(0x0618);
        flgC = true;
        opSBC(0x0A);
        if (flgV) {
            opEOR(0x80);
        }
        if (!flgN) {
            goto L_002896;
        }
        y = myMapper->readCPU(0x0618);
        if (myMapper->readCPU(0x0070 + y) == 0) {
        }
        else {
            y = myMapper->readCPU(0x0618);
            if (myMapper->readCPU(0x0070 + y) >= 0x0A) {
                myMapper->writeCPU(0x00A1, myMapper->readCPU(0x0618));
                goto L_002896;
            }
            opINC(0x061A, 1);
            a = 0x70;
            x = 0x00;
            flgC = false;
            opADC(myMapper->readCPU(0x0618));
            if (flgC) {
                opINX(1);
            }
            myMapper->writeCPU(0x00C4, a);
            myMapper->writeCPU(0x00C5, x);
            y = 0x00;
            a = 0x01;
            flgC = false;
            opADC(myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
            y = myMapper->readCPU(0x0618);
            if (myMapper->readCPU(0x0070 + y) < 0x04) {
            }
            else {
                myMapper->writeCPU(0x0619, 0x17);
                while (true) {
                    opCMP(myMapper->readCPU(0x0619), 0x04);
                    x = 0x00;
                    if (!flgC) {
                        goto L_002861;
                    }
                    y = myMapper->readCPU(0x0619);
                    myMapper->writeCPU(0x00C4, myMapper->readCPU(0x0349 + y));
                    a = myMapper->readCPU(0x0618);
                    setLoadFlag(a);
                    if (flgN) {
                        opDEX(1);
                    }
                    flgC = false;
                    opADC(myMapper->readCPU(0x00C4));
                    if (flgC) {
                        opINX(1);
                    }
                    myMapper->writeCPU(0x00C4, a);
                    a = x;
                    flgC = false;
                    opADC(0x03);
                    myMapper->writeCPU(0x00C5, a);
                    y = 0xF9;
                    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
                    setLoadFlag(a);
                    if (!flgZ) {
                        goto L_00285B;
                    }
                    x = a;
                    while (true) {
                        if (myMapper->readCPU(0x0619) >= 0x18) {
                            goto L_002861;
                        }
                        y = myMapper->readCPU(0x0619);
                        myMapper->writeCPU(0x00C4, myMapper->readCPU(0x0349 + y));
                        a = myMapper->readCPU(0x0618);
                        setLoadFlag(a);
                        if (flgN) {
                            opDEX(1);
                        }
                        flgC = false;
                        opADC(myMapper->readCPU(0x00C4));
                        if (flgC) {
                            opINX(1);
                            flgC = false;
                        }
                        opADC(0xF9);
                        myMapper->writeCPU(0x00BE, a);
                        a = x;
                        opADC(0x03);
                        myMapper->writeCPU(0x00BF, a);
                        x = 0x00;
                        a = myMapper->readCPU(0x0619);
                        flgC = false;
                        opADC(0x01);
                        if (flgC) {
                            opINX(1);
                        }
                        myMapper->writeCPU(0x00C4, a);
                        a = x;
                        flgC = false;
                        opADC(0x03);
                        myMapper->writeCPU(0x00C5, a);
                        y = 0x49;
                        myMapper->writeCPU(0x00C4, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
                        x = 0x00;
                        a = myMapper->readCPU(0x0618);
                        setLoadFlag(a);
                        if (flgN) {
                            opDEX(1);
                        }
                        flgC = false;
                        opADC(myMapper->readCPU(0x00C4));
                        if (!flgC) {
                            goto L_002843;
                        }
                        opINX(1);
                    L_002843:
                        myMapper->writeCPU(0x00C4, a);
                        a = x;
                        flgC = false;
                        opADC(0x03);
                        myMapper->writeCPU(0x00C5, a);
                        y = 0xF9;
                        a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
                        y = 0x00;
                        myMapper->writeCPU(myMapper->readCPU(0x00BE) + (myMapper->readCPU((0x00BE + 1) & 0x00ff) << 8) + y, a);
                        x = 0x00;
                        opINC(0x0619, 1);
                    }
                L_00285B:
                    opDEC(0x0619, 1);
                }
            L_002861:
                a = myMapper->readCPU(0x0618);
                setLoadFlag(a);
                if (flgN) {
                    opDEX(1);
                }
                flgC = false;
                opADC(myMapper->readCPU(0x0360));
                if (flgC) {
                    opINX(1);
                    flgC = false;
                }
                opADC(0xF9);
                myMapper->writeCPU(0x00C4, a);
                a = x;
                opADC(0x03);
                myMapper->writeCPU(0x00C5, a);
                y = myMapper->readCPU(0x009C);
                a = myMapper->readCPU(0x0346 + y);
                y = 0x00;
                myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
                opINC(0x009C, 1);
                if (myMapper->readCPU(0x009C) < 0x03) {
                    goto L_00288B;
                }
                myMapper->writeCPU(0x009C, y);
            }
        }
    L_00288B:
        opINC(0x0618, 1);
        if (flgN) {
            goto L_002893;
        }
    }
L_002893:
    goto L_00276F;
L_002896:
    if (myMapper->readCPU(0x061A) != 0) {
        goto L_0028B8;
    }
    pushAddress(0x00289B);
    SUB_00367F();
    if (poppedEntry.value != 0x00289B) return;
    pushAddress(0x00289E);
    SUB_003669();
    if (poppedEntry.value != 0x00289E) return;
    x = 0x00;
    a = 0x0A;
    pushAddress(0x0028A5);
    SUB_003561();
    if (poppedEntry.value != 0x0028A5) return;
    flgC = false;
    opADC(0x70);
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(0x00);
    myMapper->writeCPU(0x00C5, a);
    a = 0x01;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
L_0028B8:
    SUB_0026B3();
    return;
}

void game::SUB_0028BB() {
    pushAddress(0x0028BB);
    SUB_00338C();
    if (poppedEntry.value != 0x0028BB) return;
    a = 0x17;
    flgC = true;
    opSBC(myMapper->readCPU(0x00A2));
    myMapper->writeCPU(0x00C4, a);
    a = 0x00;
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x00C5, a);
    y = 0x49;
    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0xF9);
    y = a;
    a = 0x00;
    opADC(0x03);
    x = a;
    a = y;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, x);
    a = 0x01;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    x = 0x00;
    a = 0x0A;
    pushAddress(0x0028EC);
    SUB_0005D4();
    if (poppedEntry.value != 0x0028EC) return;
    opINC(0x00A2, 1);
    SUB_0026B3();
    return;
}

void game::SUB_0028F4() {
    pushAddress(0x0028F4);
    SUB_00338C();
    if (poppedEntry.value != 0x0028F4) return;
    a = 0xF9;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x03);
    a = 0x00;
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    x = a;
    a = 0xF0;
    pushAddress(0x00290A);
    SUB_0005D4();
    if (poppedEntry.value != 0x00290A) return;
    x = 0x00;
    a = x;
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0081, a);
    myMapper->writeCPU(0x0082, a);
    myMapper->writeCPU(0x0083, a);
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x007E, a);
    myMapper->writeCPU(0x007D, a);
    a = myMapper->readCPU(0x003E);
    myMapper->writeCPU(0x0325, a);
    if (a >= 0x1E) {
        goto L_00292D;
    }
    a = myMapper->readCPU(0x0325);
    goto L_00292F;
L_00292D:
    a = 0x1E;
L_00292F:
    myMapper->writeCPU(0x00C4, a);
    a = x;
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x00C5, a);
    y = 0x89;
    myMapper->writeCPU(0x0324, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    a = 0xFF;
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x009D, a);
    myMapper->writeCPU(0x00A2, x);
    myMapper->writeCPU(0x00A4, 0x78);
    a = x;
    myMapper->writeCPU(0x00A9, a);
    pushAddress(0x00294D);
    SUB_003341();
    if (poppedEntry.value != 0x00294D) return;
    flgC = false;
    opADC(0xCC);
    y = a;
    a = x;
    opADC(0xEA);
    x = a;
    a = y;
    pushAddress(0x002959);
    SUB_000228();
    if (poppedEntry.value != 0x002959) return;
    a = 0xAC;
    x = 0xEA;
    pushAddress(0x002960);
    SUB_000232();
    if (poppedEntry.value != 0x002960) return;
    a = 0x08;
    pushAddress(0x002965);
    SUB_003653();
    if (poppedEntry.value != 0x002965) return;
    pushAddress(0x002968);
    SUB_00337F();
    if (poppedEntry.value != 0x002968) return;
    a = 0x02;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x20;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x48;
    pushAddress(0x002978);
    SUB_000850();
    if (poppedEntry.value != 0x002978) return;
    pushAddress(0x00297B);
    SUB_00072F();
    if (poppedEntry.value != 0x00297B) return;
    pushAddress(0x00297E);
    SUB_00204A();
    if (poppedEntry.value != 0x00297E) return;
    pushAddress(0x002981);
    SUB_0020A4();
    if (poppedEntry.value != 0x002981) return;
    pushAddress(0x002984);
    SUB_00227E();
    if (poppedEntry.value != 0x002984) return;
    pushAddress(0x002987);
    SUB_0002A3();
    if (poppedEntry.value != 0x002987) return;
    pushAddress(0x00298A);
    SUB_00338C();
    if (poppedEntry.value != 0x00298A) return;
    a = 0x61;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x03);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x00299E);
    SUB_00337F();
    if (poppedEntry.value != 0x00299E) return;
    a = myMapper->readCPU(0x0084);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x10;
    pushAddress(0x0029AD);
    SUB_000850();
    if (poppedEntry.value != 0x0029AD) return;
    pushAddress(0x0029B0);
    SUB_0006E9();
    if (poppedEntry.value != 0x0029B0) return;
    pushAddress(0x0029B3);
    SUB_00338C();
    if (poppedEntry.value != 0x0029B3) return;
    a = 0x61;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0x03);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0029C7);
    SUB_00337F();
    if (poppedEntry.value != 0x0029C7) return;
    a = myMapper->readCPU(0x0084);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x78;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x18;
    pushAddress(0x0029D6);
    SUB_000850();
    if (poppedEntry.value != 0x0029D6) return;
    pushAddress(0x0029D9);
    SUB_0006E9();
    if (poppedEntry.value != 0x0029D9) return;
    SUB_0026B3();
    return;
}

void game::SUB_0029DF() {
    myMapper->writeCPU(0x061B, myMapper->readCPU(0x0097));
    a = 0x00;
    myMapper->writeCPU(0x061C, a);
    x = a;
    if (myMapper->readCPU(0x0097) >= 0x64) {
        goto L_002A6C;
    }
    pushAddress(0x0029F0);
    SUB_00338C();
    if (poppedEntry.value != 0x0029F0) return;
    a = 0x71;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x03;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002A04);
    SUB_00337F();
    if (poppedEntry.value != 0x002A04) return;
    a = x;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x20;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    pushAddress(0x002A12);
    SUB_000850();
    if (poppedEntry.value != 0x002A12) return;
    pushAddress(0x002A15);
    SUB_0006E9();
    if (poppedEntry.value != 0x002A15) return;
    goto L_002A6A;
L_002A1B:
    a = myMapper->readCPU(0x061B);
    pushAddress(0x002A1E);
    SUB_003669();
    if (poppedEntry.value != 0x002A1E) return;
    a = 0x0A;
    pushAddress(0x002A23);
    SUB_00376E();
    if (poppedEntry.value != 0x002A23) return;
    pushAddress(0x002A26);
    SUB_003653();
    if (poppedEntry.value != 0x002A26) return;
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x30);
    pushAddress(0x002A30);
    SUB_003653();
    if (poppedEntry.value != 0x002A30) return;
    pushAddress(0x002A33);
    SUB_00337F();
    if (poppedEntry.value != 0x002A33) return;
    a = 0x00;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x30;
    pushAddress(0x002A3E);
    SUB_003667();
    if (poppedEntry.value != 0x002A3E) return;
    a = myMapper->readCPU(0x061C);
    pushAddress(0x002A44);
    SUB_003333();
    if (poppedEntry.value != 0x002A44) return;
    pushAddress(0x002A47);
    SUB_00370A();
    if (poppedEntry.value != 0x002A47) return;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    pushAddress(0x002A50);
    SUB_000850();
    if (poppedEntry.value != 0x002A50) return;
    pushAddress(0x002A53);
    SUB_00072F();
    if (poppedEntry.value != 0x002A53) return;
    a = myMapper->readCPU(0x061B);
    pushAddress(0x002A59);
    SUB_003667();
    if (poppedEntry.value != 0x002A59) return;
    a = 0x0A;
    pushAddress(0x002A5E);
    SUB_00371D();
    if (poppedEntry.value != 0x002A5E) return;
    myMapper->writeCPU(0x061B, a);
    opINC(0x061C, 1);
    pushAddress(0x002A67);
    SUB_0033D4();
    if (poppedEntry.value != 0x002A67) return;
L_002A6A:
    x = 0x00;
L_002A6C:
    if (myMapper->readCPU(0x061B) != 0) {
        goto L_002A1B;
    }
    popAddress();
}

void game::SUB_002A72() {
    myMapper->writeCPU(0x061D, myMapper->readCPU(0x0099));
    a = 0x00;
    myMapper->writeCPU(0x061E, a);
    x = a;
    if (myMapper->readCPU(0x0097) >= 0x64) {
        goto L_002AFF;
    }
    pushAddress(0x002A83);
    SUB_00338C();
    if (poppedEntry.value != 0x002A83) return;
    a = 0x71;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEB);
    a = 0x03;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002A97);
    SUB_00337F();
    if (poppedEntry.value != 0x002A97) return;
    a = x;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0xC8;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    pushAddress(0x002AA5);
    SUB_000850();
    if (poppedEntry.value != 0x002AA5) return;
    pushAddress(0x002AA8);
    SUB_0006E9();
    if (poppedEntry.value != 0x002AA8) return;
    goto L_002AFD;
L_002AAE:
    a = myMapper->readCPU(0x061D);
    pushAddress(0x002AB1);
    SUB_003669();
    if (poppedEntry.value != 0x002AB1) return;
    a = 0x0A;
    pushAddress(0x002AB6);
    SUB_00376E();
    if (poppedEntry.value != 0x002AB6) return;
    pushAddress(0x002AB9);
    SUB_003653();
    if (poppedEntry.value != 0x002AB9) return;
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x30);
    pushAddress(0x002AC3);
    SUB_003653();
    if (poppedEntry.value != 0x002AC3) return;
    pushAddress(0x002AC6);
    SUB_00337F();
    if (poppedEntry.value != 0x002AC6) return;
    a = 0x00;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0xD8;
    pushAddress(0x002AD1);
    SUB_003667();
    if (poppedEntry.value != 0x002AD1) return;
    a = myMapper->readCPU(0x061E);
    pushAddress(0x002AD7);
    SUB_003333();
    if (poppedEntry.value != 0x002AD7) return;
    pushAddress(0x002ADA);
    SUB_00370A();
    if (poppedEntry.value != 0x002ADA) return;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x70;
    pushAddress(0x002AE3);
    SUB_000850();
    if (poppedEntry.value != 0x002AE3) return;
    pushAddress(0x002AE6);
    SUB_00072F();
    if (poppedEntry.value != 0x002AE6) return;
    a = myMapper->readCPU(0x061D);
    pushAddress(0x002AEC);
    SUB_003667();
    if (poppedEntry.value != 0x002AEC) return;
    a = 0x0A;
    pushAddress(0x002AF1);
    SUB_00371D();
    if (poppedEntry.value != 0x002AF1) return;
    myMapper->writeCPU(0x061D, a);
    opINC(0x061E, 1);
    pushAddress(0x002AFA);
    SUB_0033D4();
    if (poppedEntry.value != 0x002AFA) return;
L_002AFD:
    x = 0x00;
L_002AFF:
    if (myMapper->readCPU(0x061D) != 0) {
        goto L_002AAE;
    }
    popAddress();
}

void game::SUB_002B05() {
    a = 0x01;
    pushAddress(0x002B07);
    SUB_000603();
    if (poppedEntry.value != 0x002B07) return;
    pushAddress(0x002B0A);
    SUB_00074D();
    if (poppedEntry.value != 0x002B0A) return;
    pushAddress(0x002B0D);
    SUB_00338C();
    if (poppedEntry.value != 0x002B0D) return;
    a = 0x0C;
    x = 0x03;
    flgC = false;
    opADC(myMapper->readCPU(0x0325));
    if (flgC) {
        opINX(1);
    }
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, x);
    a = 0x01;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002B29);
    SUB_00337F();
    if (poppedEntry.value != 0x002B29) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    opASL_A(3);
    pushAddress(0x002B3B);
    SUB_000850();
    if (poppedEntry.value != 0x002B3B) return;
    pushAddress(0x002B3E);
    SUB_0006E9();
    if (poppedEntry.value != 0x002B3E) return;
    pushAddress(0x002B41);
    SUB_00338C();
    if (poppedEntry.value != 0x002B41) return;
    x = 0x00;
    a = myMapper->readCPU(0x003A);
    pushAddress(0x002B48);
    SUB_00360A();
    if (poppedEntry.value != 0x002B48) return;
    flgC = false;
    opADC(0xA7);
    y = a;
    a = x;
    opADC(0x03);
    x = a;
    a = y;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, x);
    a = 0x07;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002B62);
    SUB_00337F();
    if (poppedEntry.value != 0x002B62) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x02);
    opASL_A(3);
    pushAddress(0x002B77);
    SUB_000850();
    if (poppedEntry.value != 0x002B77) return;
    pushAddress(0x002B7A);
    SUB_0006E9();
    if (poppedEntry.value != 0x002B7A) return;
    pushAddress(0x002B7D);
    SUB_00338C();
    if (poppedEntry.value != 0x002B7D) return;
    x = 0x00;
    a = myMapper->readCPU(0x003B);
    pushAddress(0x002B84);
    SUB_003328();
    if (poppedEntry.value != 0x002B84) return;
    flgC = false;
    opADC(0xBC);
    y = a;
    a = x;
    opADC(0x03);
    x = a;
    a = y;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, x);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002B9E);
    SUB_00337F();
    if (poppedEntry.value != 0x002B9E) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x04);
    opASL_A(3);
    pushAddress(0x002BB3);
    SUB_000850();
    if (poppedEntry.value != 0x002BB3) return;
    pushAddress(0x002BB6);
    SUB_0006E9();
    if (poppedEntry.value != 0x002BB6) return;
    pushAddress(0x002BB9);
    SUB_00338C();
    if (poppedEntry.value != 0x002BB9) return;
    x = 0x00;
    a = myMapper->readCPU(0x003C);
    pushAddress(0x002BC0);
    SUB_003328();
    if (poppedEntry.value != 0x002BC0) return;
    flgC = false;
    opADC(0xBC);
    y = a;
    a = x;
    opADC(0x03);
    x = a;
    a = y;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, x);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002BDA);
    SUB_00337F();
    if (poppedEntry.value != 0x002BDA) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x06);
    opASL_A(3);
    pushAddress(0x002BEF);
    SUB_000850();
    if (poppedEntry.value != 0x002BEF) return;
    pushAddress(0x002BF2);
    SUB_0006E9();
    if (poppedEntry.value != 0x002BF2) return;
    pushAddress(0x002BF5);
    SUB_00338C();
    if (poppedEntry.value != 0x002BF5) return;
    x = 0x00;
    a = myMapper->readCPU(0x003F);
    pushAddress(0x002BFC);
    SUB_003328();
    if (poppedEntry.value != 0x002BFC) return;
    flgC = false;
    opADC(0xD2);
    y = a;
    a = x;
    opADC(0x03);
    x = a;
    a = y;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, x);
    a = 0x04;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002C16);
    SUB_00337F();
    if (poppedEntry.value != 0x002C16) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x88;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x08);
    opASL_A(3);
    pushAddress(0x002C2B);
    SUB_000850();
    if (poppedEntry.value != 0x002C2B) return;
    pushAddress(0x002C2E);
    SUB_0006E9();
    if (poppedEntry.value != 0x002C2E) return;
    pushAddress(0x002C31);
    SUB_00338C();
    if (poppedEntry.value != 0x002C31) return;
    a = 0x98;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEA);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002C44);
    SUB_00337F();
    if (poppedEntry.value != 0x002C44) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x38;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    opASL_A(3);
    pushAddress(0x002C56);
    SUB_000850();
    if (poppedEntry.value != 0x002C56) return;
    pushAddress(0x002C59);
    SUB_0006E9();
    if (poppedEntry.value != 0x002C59) return;
    pushAddress(0x002C5C);
    SUB_00338C();
    if (poppedEntry.value != 0x002C5C) return;
    a = 0x98;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEA);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002C6F);
    SUB_00337F();
    if (poppedEntry.value != 0x002C6F) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x38;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x02);
    opASL_A(3);
    pushAddress(0x002C84);
    SUB_000850();
    if (poppedEntry.value != 0x002C84) return;
    pushAddress(0x002C87);
    SUB_0006E9();
    if (poppedEntry.value != 0x002C87) return;
    pushAddress(0x002C8A);
    SUB_00338C();
    if (poppedEntry.value != 0x002C8A) return;
    a = 0x98;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEA);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002C9D);
    SUB_00337F();
    if (poppedEntry.value != 0x002C9D) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x38;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x04);
    opASL_A(3);
    pushAddress(0x002CB2);
    SUB_000850();
    if (poppedEntry.value != 0x002CB2) return;
    pushAddress(0x002CB5);
    SUB_0006E9();
    if (poppedEntry.value != 0x002CB5) return;
    pushAddress(0x002CB8);
    SUB_00338C();
    if (poppedEntry.value != 0x002CB8) return;
    a = 0x98;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEA);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002CCB);
    SUB_00337F();
    if (poppedEntry.value != 0x002CCB) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x38;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x06);
    opASL_A(3);
    pushAddress(0x002CE0);
    SUB_000850();
    if (poppedEntry.value != 0x002CE0) return;
    pushAddress(0x002CE3);
    SUB_0006E9();
    if (poppedEntry.value != 0x002CE3) return;
    pushAddress(0x002CE6);
    SUB_00338C();
    if (poppedEntry.value != 0x002CE6) return;
    a = 0x98;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEA);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002CF9);
    SUB_00337F();
    if (poppedEntry.value != 0x002CF9) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x38;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x03F4);
    flgC = false;
    opADC(0x08);
    opASL_A(3);
    pushAddress(0x002D0E);
    SUB_000850();
    if (poppedEntry.value != 0x002D0E) return;
    pushAddress(0x002D11);
    SUB_0006E9();
    if (poppedEntry.value != 0x002D11) return;
    pushAddress(0x002D14);
    SUB_00338C();
    if (poppedEntry.value != 0x002D14) return;
    a = 0x9A;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, 0xEA);
    a = y;
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x002D27);
    SUB_00337F();
    if (poppedEntry.value != 0x002D27) return;
    a = y;
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = 0x38;
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0039);
    opASL_A(1);
    if (!flgC) {
        goto L_002D39;
    }
    flgC = false;
L_002D39:
    opADC(myMapper->readCPU(0x03F4));
    opASL_A(3);
    pushAddress(0x002D3F);
    SUB_000850();
    if (poppedEntry.value != 0x002D3F) return;
    pushAddress(0x002D42);
    SUB_0006E9();
    if (poppedEntry.value != 0x002D42) return;
    a = 0x01;
    pushAddress(0x002D47);
    SUB_000603();
    if (poppedEntry.value != 0x002D47) return;
    SUB_00074D();
    return;
}

void game::SUB_002D4D() {
    a = 0x03;
    pushAddress(0x002D4F);
    SUB_000276();
    if (poppedEntry.value != 0x002D4F) return;
    a = 0x02;
    pushAddress(0x002D54);
    SUB_000603();
    if (poppedEntry.value != 0x002D54) return;
    a = 0x02;
    pushAddress(0x002D59);
    SUB_000276();
    if (poppedEntry.value != 0x002D59) return;
    a = 0x02;
    pushAddress(0x002D5E);
    SUB_000603();
    if (poppedEntry.value != 0x002D5E) return;
    a = 0x01;
    pushAddress(0x002D63);
    SUB_000276();
    if (poppedEntry.value != 0x002D63) return;
    a = 0x02;
    pushAddress(0x002D68);
    SUB_000603();
    if (poppedEntry.value != 0x002D68) return;
    a = 0x00;
    pushAddress(0x002D6D);
    SUB_000276();
    if (poppedEntry.value != 0x002D6D) return;
    a = 0x02;
    SUB_000603();
    return;
}

void game::SUB_002D75() {
    a = 0x01;
    pushAddress(0x002D77);
    SUB_000276();
    if (poppedEntry.value != 0x002D77) return;
    a = 0x02;
    pushAddress(0x002D7C);
    SUB_000603();
    if (poppedEntry.value != 0x002D7C) return;
    a = 0x02;
    pushAddress(0x002D81);
    SUB_000276();
    if (poppedEntry.value != 0x002D81) return;
    a = 0x02;
    pushAddress(0x002D86);
    SUB_000603();
    if (poppedEntry.value != 0x002D86) return;
    a = 0x03;
    pushAddress(0x002D8B);
    SUB_000276();
    if (poppedEntry.value != 0x002D8B) return;
    a = 0x02;
    pushAddress(0x002D90);
    SUB_000603();
    if (poppedEntry.value != 0x002D90) return;
    a = 0x04;
    pushAddress(0x002D95);
    SUB_000276();
    if (poppedEntry.value != 0x002D95) return;
    a = 0x02;
    SUB_000603();
    return;
}

void game::SUB_002D9D() {
    pushAddress(0x002D9D);
    SUB_00027D();
    if (poppedEntry.value != 0x002D9D) return;
    a = 0x01;
    pushAddress(0x002DA2);
    SUB_000403();
    if (poppedEntry.value != 0x002DA2) return;
    pushAddress(0x002DA5);
    SUB_0006DD();
    if (poppedEntry.value != 0x002DA5) return;
    pushAddress(0x002DA8);
    SUB_00074D();
    if (poppedEntry.value != 0x002DA8) return;
    myMapper->writeCPU(0x0085, 0x00);
    myMapper->writeCPU(0x0084, 0x02);
    x = 0x20;
    a = 0x00;
    pushAddress(0x002DB7);
    SUB_000560();
    if (poppedEntry.value != 0x002DB7) return;
    a = 0xE6;
    x = 0xE2;
    pushAddress(0x002DBE);
    SUB_000370();
    if (poppedEntry.value != 0x002DBE) return;
    x = 0x28;
    a = 0x00;
    pushAddress(0x002DC5);
    SUB_000560();
    if (poppedEntry.value != 0x002DC5) return;
    a = 0xDA;
    x = 0xDF;
    pushAddress(0x002DCC);
    SUB_000370();
    if (poppedEntry.value != 0x002DCC) return;
    pushAddress(0x002DCF);
    SUB_003665();
    if (poppedEntry.value != 0x002DCF) return;
    x = 0x01;
    a = 0xDF;
    pushAddress(0x002DD6);
    SUB_0003A7();
    if (poppedEntry.value != 0x002DD6) return;
    pushAddress(0x002DD9);
    SUB_000286();
    if (poppedEntry.value != 0x002DD9) return;
    a = 0x01;
    myMapper->writeCPU(0x003A, a);
    myMapper->writeCPU(0x003B, a);
    myMapper->writeCPU(0x003C, a);
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x0316, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x009C, a);
    pushAddress(0x002DF1);
    SUB_000276();
    if (poppedEntry.value != 0x002DF1) return;
    a = 0x00;
    while (true) {
        while (true) {
            while (true) {
                while (true) {
                    pushAddress(0x002DF6);
                    SUB_001B01();
                    if (poppedEntry.value != 0x002DF6) return;
                    pushAddress(0x002DF9);
                    SUB_002D75();
                    if (poppedEntry.value != 0x002DF9) return;
                    do {
                    L_002DFC:
                        pushAddress(0x002DFC);
                        SUB_000365();
                        if (poppedEntry.value != 0x002DFC) return;
                        opINC(0x002F, 1);
                        opINC(0x0030, 1);
                        if (flgZ) {
                            opINC(0x0031, 1);
                        }
                        a = 0x00;
                        pushAddress(0x002E09);
                        SUB_000487();
                        if (poppedEntry.value != 0x002E09) return;
                        myMapper->writeCPU(0x0035, a);
                        a = 0x00;
                        pushAddress(0x002E10);
                        SUB_000757();
                        if (poppedEntry.value != 0x002E10) return;
                        myMapper->writeCPU(0x0036, a);
                        pushAddress(0x002E15);
                        SUB_00074D();
                        if (poppedEntry.value != 0x002E15) return;
                        if (myMapper->readCPU(0x0316) != 0x02) {
                            a = myMapper->readCPU(0x0035);
                            opAND(0x80);
                            if (!flgZ) {
                                a = myMapper->readCPU(0x0035);
                                opAND(0x40);
                                if (!flgZ) {
                                    a = myMapper->readCPU(0x0035);
                                    opAND(0x20);
                                    if (!flgZ) {
                                        a = myMapper->readCPU(0x0035);
                                        opAND(0x10);
                                        if (!flgZ) {
                                            a = 0x02;
                                            pushAddress(0x002E39);
                                            SUB_001B01();
                                            if (poppedEntry.value != 0x002E39) return;
                                        }
                                    }
                                }
                            }
                        }
                        a = myMapper->readCPU(0x0316);
                        setLoadFlag(a);
                        if (!flgZ) {
                            if (a == 0x01) {
                                goto L_002E83;
                            }
                            if (a == 0x02) {
                                goto L_002E9A;
                            }
                            if (a == 0x03) {
                                goto L_002F2D;
                            }
                            if (a == 0x04) {
                                goto L_003133;
                            }
                            if (a == 0x05) {
                                goto L_003248;
                            }
                            if (a == 0x06) {
                                goto L_00325C;
                            }
                            if (a != 0x07) {
                                goto L_002E6C;
                            }
                            goto L_003278;
                        L_002E6C:
                            goto L_002DFC;
                        }
                        if (myMapper->readCPU(0x002F) == 0x78) {
                            goto L_002E7B;
                        }
                        a = myMapper->readCPU(0x0036);
                        opAND(0x10);
                    } while (flgZ);
                L_002E7B:
                    pushAddress(0x002E7B);
                    SUB_002D4D();
                    if (poppedEntry.value != 0x002E7B) return;
                    a = 0x01;
                }
            L_002E83:
                if (myMapper->readCPU(0x002F) != 0x68) {
                    a = myMapper->readCPU(0x0036);
                    opAND(0x10);
                    if (!flgZ) {
                        goto L_002E92;
                    }
                    goto L_002DFC;
                }
            L_002E92:
                pushAddress(0x002E92);
                SUB_002D4D();
                if (poppedEntry.value != 0x002E92) return;
                a = 0x02;
            }
        L_002E9A:
            pushAddress(0x002E9A);
            SUB_001097();
            if (poppedEntry.value != 0x002E9A) return;
            a = myMapper->readCPU(0x002F);
            opAND(0x7F);
            if (flgZ) {
                pushAddress(0x002EA3);
                SUB_00338C();
                if (poppedEntry.value != 0x002EA3) return;
                a = 0xDE;
                y = 0x01;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                opINY(1);
                a = 0x03;
            }
            else {
                a = myMapper->readCPU(0x002F);
                opAND(0x7F);
                if (a != 0x60) {
                    goto L_002EE0;
                }
                pushAddress(0x002EBA);
                SUB_00338C();
                if (poppedEntry.value != 0x002EBA) return;
                a = 0xE9;
                y = 0x01;
                myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
                opINY(1);
                a = 0x03;
            }
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            a = 0x0A;
            y = 0x00;
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            pushAddress(0x002ECE);
            SUB_00337F();
            if (poppedEntry.value != 0x002ECE) return;
            a = y;
            opINY(1);
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            a = 0x60;
            opDEY(1);
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            pushAddress(0x002EDA);
            SUB_000850();
            if (poppedEntry.value != 0x002EDA) return;
            pushAddress(0x002EDD);
            SUB_0006E9();
            if (poppedEntry.value != 0x002EDD) return;
        L_002EE0:
            if (myMapper->readCPU(0x0036) != 0) {
                y = myMapper->readCPU(0x0042);
                a = myMapper->readCPU(0x0317 + y);
                opAND(myMapper->readCPU(0x0036));
                opPHA();
                opPLA();
                if (!flgZ) {
                    opINC(0x0042, 1);
                }
                else {
                    myMapper->writeCPU(0x0042, a);
                }
            }
            a = myMapper->readCPU(0x0036);
            opAND(0x10);
            if (flgZ) {
                goto L_002DFC;
            }
            a = myMapper->readCPU(0x0030);
            x = myMapper->readCPU(0x0031);
            pushAddress(0x002F03);
            SUB_0036A1();
            if (poppedEntry.value != 0x002F03) return;
            if (myMapper->readCPU(0x0042) >= 0x0B) {
                if (myMapper->readCPU(0x003C) == 0) {
                    goto L_002F1A;
                }
                a = 0x08;
                pushAddress(0x002F12);
                SUB_003653();
                if (poppedEntry.value != 0x002F12) return;
                a = 0x00;
                pushAddress(0x002F17);
                SUB_000475();
                if (poppedEntry.value != 0x002F17) return;
            L_002F1A:
                pushAddress(0x002F1A);
                SUB_000AF4();
                if (poppedEntry.value != 0x002F1A) return;
                a = 0x07;
                pushAddress(0x002F1F);
                SUB_001B01();
                if (poppedEntry.value != 0x002F1F) return;
                goto L_002DFC;
            }
            pushAddress(0x002F25);
            SUB_002D4D();
            if (poppedEntry.value != 0x002F25) return;
            a = 0x03;
        }
    L_002F2D:
        a = myMapper->readCPU(0x002F);
        opAND(0x7F);
        if (flgZ) {
            pushAddress(0x002F33);
            SUB_00338C();
            if (poppedEntry.value != 0x002F33) return;
            a = 0xDE;
            y = 0x01;
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            a = 0x03;
        }
        else {
            a = myMapper->readCPU(0x002F);
            opAND(0x7F);
            if (a != 0x60) {
                goto L_002F70;
            }
            pushAddress(0x002F4A);
            SUB_00338C();
            if (poppedEntry.value != 0x002F4A) return;
            a = 0xE9;
            y = 0x01;
            myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            a = 0x03;
        }
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x0A;
        y = 0x00;
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        pushAddress(0x002F5E);
        SUB_00337F();
        if (poppedEntry.value != 0x002F5E) return;
        a = y;
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        a = 0x60;
        opDEY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
        pushAddress(0x002F6A);
        SUB_000850();
        if (poppedEntry.value != 0x002F6A) return;
        pushAddress(0x002F6D);
        SUB_0006E9();
        if (poppedEntry.value != 0x002F6D) return;
    L_002F70:
        a = myMapper->readCPU(0x0036);
        opAND(0x10);
        if (!flgZ) {
            pushAddress(0x002F76);
            SUB_000AF4();
            if (poppedEntry.value != 0x002F76) return;
            if (myMapper->readCPU(0x003C) != 0) {
                a = 0x05;
                pushAddress(0x002F7F);
                SUB_003653();
                if (poppedEntry.value != 0x002F7F) return;
                a = 0x00;
                pushAddress(0x002F84);
                SUB_000475();
                if (poppedEntry.value != 0x002F84) return;
            }
            pushAddress(0x002F87);
            SUB_002D4D();
            if (poppedEntry.value != 0x002F87) return;
            pushAddress(0x002F8A);
            SUB_00027D();
            if (poppedEntry.value != 0x002F8A) return;
            x = 0x20;
            a = 0x00;
            pushAddress(0x002F91);
            SUB_000560();
            if (poppedEntry.value != 0x002F91) return;
            a = 0xE6;
            x = 0xE2;
            pushAddress(0x002F98);
            SUB_000370();
            if (poppedEntry.value != 0x002F98) return;
            pushAddress(0x002F9B);
            SUB_000286();
            if (poppedEntry.value != 0x002F9B) return;
            pushAddress(0x002F9E);
            SUB_002D75();
            if (poppedEntry.value != 0x002F9E) return;
            if (myMapper->readCPU(0x0325) == 0x09) {
                a = myMapper->readCPU(0x0035);
                opAND(0x20);
                if (flgZ) {
                    goto L_002FB3;
                }
                a = 0x1D;
                goto L_002FBF;
            }
        L_002FB3:
            a = myMapper->readCPU(0x0035);
            opAND(0x80);
            if (flgZ) {
                goto L_002FC2;
            }
            a = 0x0A;
            flgC = false;
            opADC(myMapper->readCPU(0x0325));
        L_002FBF:
            myMapper->writeCPU(0x0325, a);
        L_002FC2:
            a = 0x04;
            pushAddress(0x002FC4);
            SUB_001B01();
            if (poppedEntry.value != 0x002FC4) return;
        }
        a = myMapper->readCPU(0x0036);
        opAND(0x40);
        if (flgZ) {
            goto L_002FD5;
        }
        pushAddress(0x002FCD);
        SUB_002D4D();
        if (poppedEntry.value != 0x002FCD) return;
        a = 0x02;
    }
L_002FD5:
    a = myMapper->readCPU(0x0036);
    opAND(0x01);
    if (flgZ) {
    }
    else {
        a = myMapper->readCPU(0x0039);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == 0x01) {
                goto L_00300A;
            }
            if (a == 0x02) {
                goto L_003018;
            }
            if (a == 0x03) {
                goto L_003031;
            }
            if (a == 0x04) {
                goto L_00303C;
            }
        }
        else {
            if (myMapper->readCPU(0x0325) >= 0x09) {
                goto L_003002;
            }
            opINC(0x0325, 1);
            goto L_003044;
        L_003002:
            myMapper->writeCPU(0x0325, 0x00);
            goto L_003044;
        L_00300A:
            if (myMapper->readCPU(0x003A) < 0x02) {
                opINC(0x003A, 1);
                pushAddress(0x003012);
                SUB_00218E();
                if (poppedEntry.value != 0x003012) return;
                goto L_003044;
            L_003018:
                if (myMapper->readCPU(0x003B) == 0) {
                    myMapper->writeCPU(0x003B, 0x01);
                    a = myMapper->readCPU(0x003B);
                    setLoadFlag(a);
                    if (!flgZ) {
                        a = 0x00;
                        pushAddress(0x003026);
                        SUB_000B32();
                        if (poppedEntry.value != 0x003026) return;
                        a = 0x00;
                    }
                    pushAddress(0x00302B);
                    SUB_000B9F();
                    if (poppedEntry.value != 0x00302B) return;
                    goto L_003044;
                L_003031:
                    if (myMapper->readCPU(0x003C) == 0) {
                        myMapper->writeCPU(0x003C, 0x01);
                        goto L_003044;
                    L_00303C:
                        if (myMapper->readCPU(0x003F) < 0x02) {
                            opINC(0x003F, 1);
                        }
                    }
                }
            }
        }
    L_003044:
        if (myMapper->readCPU(0x003C) != 0) {
            a = 0x0A;
            pushAddress(0x00304A);
            SUB_003653();
            if (poppedEntry.value != 0x00304A) return;
            a = 0x00;
            pushAddress(0x00304F);
            SUB_000475();
            if (poppedEntry.value != 0x00304F) return;
        }
        pushAddress(0x003052);
        SUB_002B05();
        if (poppedEntry.value != 0x003052) return;
        goto L_002DFC;
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x02);
    if (!flgZ) {
        a = myMapper->readCPU(0x0039);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == 0x01) {
                goto L_003088;
            }
            if (a == 0x02) {
                goto L_003094;
            }
            if (a == 0x03) {
                goto L_0030A7;
            }
            if (a == 0x04) {
                goto L_0030B2;
            }
        }
        else {
            if (myMapper->readCPU(0x0325) == 0) {
                goto L_003080;
            }
            opDEC(0x0325, 1);
            goto L_0030B8;
        L_003080:
            myMapper->writeCPU(0x0325, 0x09);
            goto L_0030B8;
        L_003088:
            if (myMapper->readCPU(0x003A) != 0) {
                opDEC(0x003A, 1);
                pushAddress(0x00308E);
                SUB_00218E();
                if (poppedEntry.value != 0x00308E) return;
                goto L_0030B8;
            L_003094:
                if (myMapper->readCPU(0x003B) != 0) {
                    myMapper->writeCPU(0x003B, 0x00);
                    a = 0x01;
                    pushAddress(0x00309E);
                    SUB_000B9F();
                    if (poppedEntry.value != 0x00309E) return;
                    pushAddress(0x0030A1);
                    SUB_000AF4();
                    if (poppedEntry.value != 0x0030A1) return;
                    goto L_0030B8;
                L_0030A7:
                    if (myMapper->readCPU(0x003C) != 0) {
                        myMapper->writeCPU(0x003C, 0x00);
                        goto L_0030B8;
                    L_0030B2:
                        if (myMapper->readCPU(0x003F) != 0) {
                            opDEC(0x003F, 1);
                        }
                    }
                }
            }
        }
    L_0030B8:
        if (myMapper->readCPU(0x003C) != 0) {
            a = 0x0B;
            pushAddress(0x0030BE);
            SUB_003653();
            if (poppedEntry.value != 0x0030BE) return;
            a = 0x00;
            pushAddress(0x0030C3);
            SUB_000475();
            if (poppedEntry.value != 0x0030C3) return;
        }
        pushAddress(0x0030C6);
        SUB_002B05();
        if (poppedEntry.value != 0x0030C6) return;
        goto L_002DFC;
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x04);
    if (!flgZ) {
        x = 0x00;
        a = myMapper->readCPU(0x0039);
        flgC = false;
        opADC(0x01);
        if (flgC) {
            opINX(1);
        }
        pushAddress(0x0030DC);
        SUB_003669();
        if (poppedEntry.value != 0x0030DC) return;
        a = 0x05;
        pushAddress(0x0030E1);
        SUB_00376C();
        if (poppedEntry.value != 0x0030E1) return;
        myMapper->writeCPU(0x0039, a);
        if (myMapper->readCPU(0x003C) != 0) {
            a = 0x0B;
            pushAddress(0x0030EC);
            SUB_003653();
            if (poppedEntry.value != 0x0030EC) return;
            a = 0x00;
            pushAddress(0x0030F1);
            SUB_000475();
            if (poppedEntry.value != 0x0030F1) return;
        }
        pushAddress(0x0030F4);
        SUB_002B05();
        if (poppedEntry.value != 0x0030F4) return;
        goto L_002DFC;
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x08);
    if (flgZ) {
        goto L_002DFC;
    }
    x = 0x00;
    if (myMapper->readCPU(0x0039) == 0) {
        myMapper->writeCPU(0x0039, 0x05);
    }
    a = myMapper->readCPU(0x0039);
    flgC = true;
    opSBC(0x01);
    if (!flgC) {
        opDEX(1);
    }
    pushAddress(0x003115);
    SUB_003669();
    if (poppedEntry.value != 0x003115) return;
    a = 0x05;
    pushAddress(0x00311A);
    SUB_00376C();
    if (poppedEntry.value != 0x00311A) return;
    myMapper->writeCPU(0x0039, a);
    if (myMapper->readCPU(0x003C) != 0) {
        a = 0x0A;
        pushAddress(0x003125);
        SUB_003653();
        if (poppedEntry.value != 0x003125) return;
        a = 0x00;
        pushAddress(0x00312A);
        SUB_000475();
        if (poppedEntry.value != 0x00312A) return;
    }
    pushAddress(0x00312D);
    SUB_002B05();
    if (poppedEntry.value != 0x00312D) return;
    goto L_002DFC;
L_003133:
    if (myMapper->readCPU(0x0032) != 0) {
        opDEC(0x0032, 1);
    }
    x = myMapper->readCPU(0x00A1);
    setLoadFlag(x);
    if (!flgN) {
        a = 0x70;
        x = 0x00;
        flgC = false;
        opADC(myMapper->readCPU(0x00A1));
        if (flgC) {
            opINX(1);
        }
        myMapper->writeCPU(0x00C4, a);
        myMapper->writeCPU(0x00C5, x);
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
        y = myMapper->readCPU(0x00A1);
        if (myMapper->readCPU(0x0070 + y) == 0) {
            myMapper->writeCPU(0x00A1, 0xFF);
        }
    }
    if (myMapper->readCPU(0x003A) != 0x02) {
        if (myMapper->readCPU(0x009B) == 0) {
            goto L_00317F;
        }
        pushAddress(0x003169);
        SUB_002767();
        if (poppedEntry.value != 0x003169) return;
        a = 0x17;
        pushAddress(0x00316E);
        SUB_002316();
        if (poppedEntry.value != 0x00316E) return;
        myMapper->writeCPU(0x009B, 0x00);
        myMapper->writeCPU(0x0034, myMapper->readCPU(0xEA05));
        myMapper->writeCPU(0x0033, myMapper->readCPU(0xEA04));
    }
L_00317F:
    if (myMapper->readCPU(0x00A3) != 0) {
        pushAddress(0x003183);
        SUB_0028BB();
        if (poppedEntry.value != 0x003183) return;
        myMapper->writeCPU(0x00A3, 0x00);
    }
    if (myMapper->readCPU(0x009F) != 0xFF) {
        if (myMapper->readCPU(0x007A) == 0) {
            goto L_003196;
        }
        opDEC(0x007A, 1);
    L_003196:
        opDEC(0x009F, 1);
        if (!flgZ) {
            goto L_0031A7;
        }
        pushAddress(0x00319A);
        SUB_0018A4();
        if (poppedEntry.value != 0x00319A) return;
        myMapper->writeCPU(0x009D, 0xFF);
    }
    else {
        pushAddress(0x0031A4);
        SUB_0014C5();
        if (poppedEntry.value != 0x0031A4) return;
    }
L_0031A7:
    pushAddress(0x0031A7);
    SUB_0011B2();
    if (poppedEntry.value != 0x0031A7) return;
    if (myMapper->readCPU(0x003A) == 0x01) {
        a = myMapper->readCPU(0x0033);
        opORA(myMapper->readCPU(0x0034));
        if (flgZ) {
            goto L_0031D7;
        }
        a = myMapper->readCPU(0x0033);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0033, a);
        if (!flgC) {
            opDEC(0x0034, 1);
        }
        a = myMapper->readCPU(0x0033);
        opORA(myMapper->readCPU(0x0034));
        if (flgZ) {
            myMapper->writeCPU(0x009B, 0x01);
            myMapper->writeCPU(0x0034, myMapper->readCPU(0xEA05));
            myMapper->writeCPU(0x0033, myMapper->readCPU(0xEA04));
        }
    }
    a = 0x00;
L_0031D7:
    myMapper->writeCPU(0x0093, a);
    myMapper->writeCPU(0x0094, a);
    myMapper->writeCPU(0x0092, a);
    while (myMapper->readCPU(0x0092) < 0x46) {
        x = 0x00;
        a = myMapper->readCPU(0x0092);
        flgC = false;
        opADC(0x28);
        if (flgC) {
            opINX(1);
        }
        myMapper->writeCPU(0x00C4, a);
        a = x;
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x00C5, a);
        y = 0xF9;
        if (myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y) != 0) {
            x = 0x00;
            myMapper->writeCPU(0x0093, 0x01);
            myMapper->writeCPU(0x0094, x);
            if (myMapper->readCPU(0x009A) != 0x01) {
                goto L_003219;
            }
            myMapper->writeCPU(0x009A, 0x02);
            if (myMapper->readCPU(0x003B) == 0) {
                goto L_00321E;
            }
            a = 0x02;
            pushAddress(0x003213);
            SUB_000B32();
            if (poppedEntry.value != 0x003213) return;
            goto L_00321E;
        }
    L_003219:
        opINC(0x0092, 1);
    }
L_00321E:
    a = myMapper->readCPU(0x0093);
    opORA(myMapper->readCPU(0x0094));
    if (flgZ) {
        if (myMapper->readCPU(0x009A) != 0x02) {
            goto L_003237;
        }
        myMapper->writeCPU(0x009A, 0x01);
        if (myMapper->readCPU(0x003B) != 0) {
            a = 0x01;
            pushAddress(0x003234);
            SUB_000B32();
            if (poppedEntry.value != 0x003234) return;
        }
    }
L_003237:
    a = myMapper->readCPU(0x0036);
    opAND(0x10);
    if (flgZ) {
        goto L_002DFC;
    }
    a = 0x05;
    pushAddress(0x003242);
    SUB_001B01();
    if (poppedEntry.value != 0x003242) return;
    goto L_002DFC;
L_003248:
    pushAddress(0x003248);
    SUB_0002A3();
    if (poppedEntry.value != 0x003248) return;
    a = myMapper->readCPU(0x0036);
    opAND(0x10);
    if (flgZ) {
        goto L_002DFC;
    }
    a = 0x04;
    pushAddress(0x003256);
    SUB_001B01();
    if (poppedEntry.value != 0x003256) return;
    goto L_002DFC;
L_00325C:
    a = myMapper->readCPU(0x0036);
    opAND(0x40);
    if (!flgZ) {
        a = 0x02;
        pushAddress(0x003264);
        SUB_001B01();
        if (poppedEntry.value != 0x003264) return;
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x80);
    if (flgZ) {
        goto L_002DFC;
    }
    a = 0x04;
    pushAddress(0x003272);
    SUB_001B01();
    if (poppedEntry.value != 0x003272) return;
    goto L_002DFC;
L_003278:
    a = myMapper->readCPU(0x0036);
    opAND(0x04);
    if (!flgZ) {
        if (myMapper->readCPU(0x0097) >= 0x0F) {
            goto L_003289;
        }
        opINC(0x0097, 1);
        goto L_003295;
    }
L_003289:
    a = myMapper->readCPU(0x0036);
    opAND(0x08);
    if (flgZ) {
        goto L_003298;
    }
    if (myMapper->readCPU(0x0097) == 0) {
        goto L_003298;
    }
    opDEC(0x0097, 1);
L_003295:
    pushAddress(0x003295);
    SUB_0029DF();
    if (poppedEntry.value != 0x003295) return;
L_003298:
    a = myMapper->readCPU(0x0036);
    opAND(0x40);
    if (!flgZ) {
        if (myMapper->readCPU(0x0098) != myMapper->readCPU(0x0097)) {
            goto L_0032AE;
        }
        myMapper->writeCPU(0x0098, 0xFF);
        pushAddress(0x0032A8);
        SUB_000AF4();
        if (poppedEntry.value != 0x0032A8) return;
        goto L_0032B7;
    L_0032AE:
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x0097));
        a = myMapper->readCPU(0x0097);
        pushAddress(0x0032B4);
        SUB_000B32();
        if (poppedEntry.value != 0x0032B4) return;
    }
L_0032B7:
    a = myMapper->readCPU(0x0036);
    opAND(0x01);
    if (!flgZ) {
        if (myMapper->readCPU(0x0099) >= 0x1F) {
            goto L_0032C8;
        }
        opINC(0x0099, 1);
        goto L_0032D4;
    }
L_0032C8:
    a = myMapper->readCPU(0x0036);
    opAND(0x02);
    if (flgZ) {
        goto L_0032D7;
    }
    if (myMapper->readCPU(0x0099) == 0) {
        goto L_0032D7;
    }
    opDEC(0x0099, 1);
L_0032D4:
    pushAddress(0x0032D4);
    SUB_002A72();
    if (poppedEntry.value != 0x0032D4) return;
L_0032D7:
    a = myMapper->readCPU(0x0036);
    opAND(0x80);
    if (!flgZ) {
        a = myMapper->readCPU(0x0099);
        pushAddress(0x0032DF);
        SUB_003653();
        if (poppedEntry.value != 0x0032DF) return;
        a = 0x00;
        pushAddress(0x0032E4);
        SUB_000475();
        if (poppedEntry.value != 0x0032E4) return;
    }
    a = myMapper->readCPU(0x0036);
    opAND(0x20);
    if (flgZ) {
        a = myMapper->readCPU(0x0036);
        opAND(0x10);
        if (!flgZ) {
            goto L_0032F6;
        }
        goto L_002DFC;
    }
L_0032F6:
    a = 0x02;
    pushAddress(0x0032F8);
    SUB_001B01();
    if (poppedEntry.value != 0x0032F8) return;
    goto L_002DFC;
}

void game::SUB_003300() {
    flgC = false;
    y = 0x00;
    opADC(myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x00CC, a);
    a = x;
    opADC(myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    x = a;
    flgC = false;
    a = myMapper->readCPU(0x00BC);
    opADC(0x02);
    myMapper->writeCPU(0x00BC, a);
    if (!flgC) {
        goto L_003317;
    }
    opINC(0x00BD, 1);
L_003317:
    a = myMapper->readCPU(0x00CC);
    popAddress();
}

void game::SUB_00331A() {
    opINY(1);
    SUB_00331B();
    return;
}

void game::SUB_00331B() {
    opPHA();
    flgC = false;
    a = y;
    opADC(myMapper->readCPU(0x00BC));
    myMapper->writeCPU(0x00BC, a);
    if (!flgC) {
        goto L_003326;
    }
    opINC(0x00BD, 1);
L_003326:
    opPLA();
    popAddress();
}

void game::SUB_003328() {
    myMapper->writeCPU(0x00CC, x);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    x = myMapper->readCPU(0x00CC);
    popAddress();
}

void game::SUB_003333() {
    myMapper->writeCPU(0x00CC, x);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    x = myMapper->readCPU(0x00CC);
    popAddress();
}

void game::SUB_003341() {
    myMapper->writeCPU(0x00CC, x);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    opASL_A(1);
    opROL_M(0x00CC, 1);
    x = myMapper->readCPU(0x00CC);
    popAddress();
}

void game::SUB_003352() {
    myMapper->writeCPU(0x00C4, 0x7C);
    myMapper->writeCPU(0x00C5, 0xEB);
    myMapper->writeCPU(0x00C6, 0x00);
    myMapper->writeCPU(0x00C7, 0x03);
    x = 0x06;
    myMapper->writeCPU(0x00CC, 0xFF);
    y = 0x00;
    do {
        do {
            opINX(1);
            if (flgZ) {
                goto L_00337A;
            }
        L_00336D:
            myMapper->writeCPU(myMapper->readCPU(0x00C6) + (myMapper->readCPU((0x00C6 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
            opINY(1);
        } while (!flgZ);
        opINC(0x00C5, 1);
        opINC(0x00C7, 1);
    } while (!flgZ);
L_00337A:
    opINC(0x00CC, 1);
    if (!flgZ) {
        goto L_00336D;
    }
    popAddress();
}

void game::SUB_00337F() {
    a = myMapper->readCPU(0x00BC);
    flgC = true;
    opSBC(0x02);
    myMapper->writeCPU(0x00BC, a);
    if (!flgC) {
        goto L_003389;
    }
    popAddress();
    return;
L_003389:
    opDEC(0x00BD, 1);
    popAddress();
}

void game::SUB_00338C() {
    a = myMapper->readCPU(0x00BC);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(0x00BC, a);
    if (!flgC) {
        goto L_003396;
    }
    popAddress();
    return;
L_003396:
    opDEC(0x00BD, 1);
    popAddress();
}

void game::SUB_003399() {
    a = myMapper->readCPU(0x00BC);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x00BC, a);
    if (!flgC) {
        goto L_0033A3;
    }
    popAddress();
    return;
L_0033A3:
    opDEC(0x00BD, 1);
    popAddress();
}

void game::SUB_0033A6() {
    x = 0x00;
    myMapper->writeCPU(0x00BE, a);
    myMapper->writeCPU(0x00BF, x);
    y = 0x00;
    x = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opINC(0x00BC, 1);
    if (flgZ) {
        opINC(0x00BD, 1);
    }
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opINC(0x00BC, 1);
    if (flgZ) {
        opINC(0x00BD, 1);
    }
    flgC = true;
    opSBC(myMapper->readCPU(0x00BF));
    if (flgZ) {
        opCMP(x, myMapper->readCPU(0x00BE));
        if (flgZ) {
            goto L_0033CC;
        }
        opADC(0xFF);
        opORA(0x01);
    L_0033CC:
        popAddress();
        return;
    }
    if (!flgV) {
        goto L_0033CC;
    }
    opEOR(0xFF);
    opORA(0x01);
    popAddress();
}

void game::SUB_0033D4() {
    opINC(0x00BC, 1);
    if (!flgZ) {
        goto L_0033DA;
    }
    opINC(0x00BD, 1);
L_0033DA:
    popAddress();
}

void game::SUB_0033DB() {
    y = 0x01;
    x = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    SUB_0033E3();
    return;
}

void game::SUB_0033E3() {
    opINC(0x00BC, 1);
    if (flgZ) {
        goto L_0033EC;
    }
    opINC(0x00BC, 1);
    if (flgZ) {
        goto L_0033EE;
    }
    popAddress();
    return;
L_0033EC:
    opINC(0x00BC, 1);
L_0033EE:
    opINC(0x00BD, 1);
    popAddress();
}

void game::SUB_0033F1() {
    y = 0x04;
    SUB_00331B();
    return;
}

void game::SUB_0033FE() {
    myMapper->writeCPU(0x00C5, y);
    flgC = false;
    y = 0x00;
    opADC(myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    opPHA();
    a = x;
    opADC(myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
    x = a;
    opINY(1);
    a = myMapper->readCPU(0x00BE);
    opADC(myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x00BE, a);
    opINY(1);
    a = myMapper->readCPU(0x00BF);
    opADC(myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x00BF, a);
    opPLA();
    popAddress();
}

void game::SUB_003423() {
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, x);
    y = 0x03;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x00BF));
    if (flgZ) {
        opDEY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
        opCMP(a, myMapper->readCPU(0x00BE));
        if (flgZ) {
            opDEY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
            opCMP(a, myMapper->readCPU(0x00C5));
            if (flgZ) {
                opDEY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
                opCMP(a, myMapper->readCPU(0x00C4));
            }
        }
        pushStatus();
        pushAddress(0x003444);
        SUB_0033F1();
        if (poppedEntry.value != 0x003444) return;
        popStatus();
        if (!flgZ) {
            if (flgC) {
                goto L_00344F;
            }
            a = 0xFF;
            setLoadFlag(a);
        }
        popAddress();
        return;
    L_00344F:
        a = 0x01;
        setLoadFlag(a);
        popAddress();
        return;
    }
    if (!flgV) {
        goto L_003458;
    }
    opEOR(0xFF);
    opORA(0x01);
L_003458:
    pushStatus();
    pushAddress(0x003459);
    SUB_0033F1();
    if (poppedEntry.value != 0x003459) return;
    popStatus();
    popAddress();
}

void game::SUB_00345E() {
    y = 0x03;
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, x);
    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    opDEY(1);
    myMapper->writeCPU(0x00BF, a);
    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    opDEY(1);
    myMapper->writeCPU(0x00BE, a);
    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    opDEY(1);
    x = a;
    a = myMapper->readCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y);
    popAddress();
}

void game::SUB_003475() {
    pushAddress(0x003475);
    SUB_003423();
    if (poppedEntry.value != 0x003475) return;
    SUB_003535();
    return;
}

void game::SUB_003484() {
    opPHA();
    pushAddress(0x003485);
    SUB_003399();
    if (poppedEntry.value != 0x003485) return;
    y = 0x03;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x00BF));
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x00BE));
    opDEY(1);
    a = x;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opPLA();
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_00349C() {
    y = 0x00;
    myMapper->writeCPU(0x00BE, y);
    myMapper->writeCPU(0x00BF, y);
    pushAddress(0x0034A2);
    SUB_0034AD();
    if (poppedEntry.value != 0x0034A2) return;
    pushAddress(0x0034A5);
    SUB_0034D1();
    if (poppedEntry.value != 0x0034A5) return;
    a = myMapper->readCPU(0x00C4);
    x = myMapper->readCPU(0x00C5);
    popAddress();
}

void game::SUB_0034AD() {
    myMapper->writeCPU(0x00C8, a);
    myMapper->writeCPU(0x00C9, x);
    myMapper->writeCPU(0x00CA, myMapper->readCPU(0x00BE));
    myMapper->writeCPU(0x00CB, myMapper->readCPU(0x00BF));
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x00BE, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00BF, a);
    SUB_00331A();
    return;
}

void game::SUB_0034D1() {
    a = 0x00;
    myMapper->writeCPU(0x00C7, a);
    myMapper->writeCPU(0x00CE, a);
    myMapper->writeCPU(0x00CF, a);
    y = 0x20;
    do {
        opASL_M(0x00C4, 1);
        opROL_M(0x00C5, 1);
        opROL_M(0x00BE, 1);
        opROL_M(0x00BF, 1);
        opROL_A(1);
        opROL_M(0x00C7, 1);
        opROL_M(0x00CE, 1);
        opROL_M(0x00CF, 1);
        x = a;
        opCMP(a, myMapper->readCPU(0x00C8));
        a = myMapper->readCPU(0x00C7);
        opSBC(myMapper->readCPU(0x00C9));
        a = myMapper->readCPU(0x00CE);
        opSBC(myMapper->readCPU(0x00CA));
        a = myMapper->readCPU(0x00CF);
        opSBC(myMapper->readCPU(0x00CB));
        if (!flgC) {
            goto L_00350F;
        }
        myMapper->writeCPU(0x00CF, a);
        a = x;
        opSBC(myMapper->readCPU(0x00C8));
        x = a;
        a = myMapper->readCPU(0x00C7);
        opSBC(myMapper->readCPU(0x00C9));
        myMapper->writeCPU(0x00C7, a);
        a = myMapper->readCPU(0x00CE);
        opSBC(myMapper->readCPU(0x00CA));
        myMapper->writeCPU(0x00CE, a);
        opINC(0x00C4, 1);
    L_00350F:
        a = x;
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x00C6, a);
    popAddress();
}

void game::SUB_003516() {
    pushAddress(0x003516);
    SUB_003423();
    if (poppedEntry.value != 0x003516) return;
    SUB_00355A();
    return;
}

void game::SUB_00351C() {
    y = 0x00;
    myMapper->writeCPU(0x00BE, y);
    myMapper->writeCPU(0x00BF, y);
    pushAddress(0x003522);
    SUB_0034AD();
    if (poppedEntry.value != 0x003522) return;
    pushAddress(0x003525);
    SUB_0034D1();
    if (poppedEntry.value != 0x003525) return;
    myMapper->writeCPU(0x00BE, myMapper->readCPU(0x00CE));
    myMapper->writeCPU(0x00BF, myMapper->readCPU(0x00CF));
    a = myMapper->readCPU(0x00C6);
    x = myMapper->readCPU(0x00C7);
    popAddress();
}

void game::SUB_003535() {
    if (!flgZ) {
        SUB_00353D();
        return;
    }
    SUB_003537();
    return;
}

void game::SUB_003537() {
    x = 0x00;
    a = x;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00353D() {
    x = 0x00;
    a = 0x01;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00355A() {
    if (flgZ) {
        SUB_003537();
        return;
    }
    x = 0x00;
    a = x;
    opROL_A(1);
    popAddress();
}

void game::SUB_003561() {
    x = 0x00;
    pushAddress(0x003563);
    SUB_0036B0();
    if (poppedEntry.value != 0x003563) return;
    a = myMapper->readCPU(0x00BE);
    x = myMapper->readCPU(0x00BF);
    opBIT(myMapper->readCPU(0x00CC));
    if (!flgN) {
        goto L_003571;
    }
    SUB_003627();
    return;
L_003571:
    popAddress();
}

void game::SUB_003572() {
    myMapper->writeCPU(0x00CA, a);
    if (x != 0) {
        myMapper->writeCPU(0x00CB, x);
        pushAddress(0x003579);
        SUB_003641();
        if (poppedEntry.value != 0x003579) return;
        a = y;
        if (myMapper->readCPU(0x00C5) == 0) {
            goto L_0035A8;
        }
        myMapper->writeCPU(0x00CC, a);
        y = 0x10;
        opLSR_M(0x00CB, 1);
        opROR_M(0x00CA, 1);
        do {
            if (!flgC) {
                goto L_003596;
            }
            flgC = false;
            opADC(myMapper->readCPU(0x00C4));
            x = a;
            a = myMapper->readCPU(0x00C5);
            opADC(myMapper->readCPU(0x00CC));
            myMapper->writeCPU(0x00CC, a);
            a = x;
        L_003596:
            opROR_M(0x00CC, 1);
            opROR_A(1);
            opROR_M(0x00CB, 1);
            opROR_M(0x00CA, 1);
            opDEY(1);
        } while (!flgZ);
        a = myMapper->readCPU(0x00CA);
        x = myMapper->readCPU(0x00CB);
        popAddress();
        return;
    }
    goto L_0035B9;
L_0035A8:
    myMapper->writeCPU(0x00C5, x);
    y = myMapper->readCPU(0x00C4);
    myMapper->writeCPU(0x00C4, myMapper->readCPU(0x00CA));
    myMapper->writeCPU(0x00CA, y);
    y = 0x08;
    goto L_0035C3;
L_0035B9:
    pushAddress(0x0035B9);
    SUB_003641();
    if (poppedEntry.value != 0x0035B9) return;
    a = y;
    y = 0x08;
    if (myMapper->readCPU(0x00C5) == 0) {
        goto L_0035E0;
    }
L_0035C3:
    myMapper->writeCPU(0x00CB, a);
    opLSR_M(0x00CA, 1);
    do {
        if (!flgC) {
            goto L_0035D4;
        }
        flgC = false;
        opADC(myMapper->readCPU(0x00C4));
        x = a;
        a = myMapper->readCPU(0x00C5);
        opADC(myMapper->readCPU(0x00CB));
        myMapper->writeCPU(0x00CB, a);
        a = x;
    L_0035D4:
        opROR_M(0x00CB, 1);
        opROR_A(1);
        opROR_M(0x00CA, 1);
        opDEY(1);
    } while (!flgZ);
    x = a;
    a = myMapper->readCPU(0x00CA);
    popAddress();
    return;
L_0035E0:
    opLSR_M(0x00CA, 1);
    do {
        if (!flgC) {
            goto L_0035E7;
        }
        flgC = false;
        opADC(myMapper->readCPU(0x00C4));
    L_0035E7:
        opROR_A(1);
        opROR_M(0x00CA, 1);
        opDEY(1);
    } while (!flgZ);
    x = a;
    a = myMapper->readCPU(0x00CA);
    popAddress();
}

void game::SUB_0035F1() {
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, x);
    opASL_A(1);
    opROL_M(0x00C5, 1);
    opASL_A(1);
    opROL_M(0x00C5, 1);
    flgC = false;
    opADC(myMapper->readCPU(0x00C4));
    myMapper->writeCPU(0x00C4, a);
    a = x;
    opADC(myMapper->readCPU(0x00C5));
    opASL_M(0x00C4, 1);
    opROL_A(1);
    x = a;
    a = myMapper->readCPU(0x00C4);
    popAddress();
}

void game::SUB_00360A() {
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, x);
    opASL_A(1);
    opROL_M(0x00C5, 1);
    opASL_A(1);
    opROL_M(0x00C5, 1);
    opASL_A(1);
    opROL_M(0x00C5, 1);
    flgC = true;
    opSBC(myMapper->readCPU(0x00C4));
    opPHA();
    a = x;
    opEOR(0xFF);
    opADC(myMapper->readCPU(0x00C5));
    x = a;
    opPLA();
    popAddress();
}

void game::SUB_003627() {
    flgC = false;
    opEOR(0xFF);
    opADC(0x01);
    opPHA();
    a = x;
    opEOR(0xFF);
    opADC(0x00);
    x = a;
    opPLA();
    popAddress();
}

void game::SUB_003635() {
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    opINC(0x00BC, 1);
    if (flgZ) {
        goto L_00363E;
    }
    popAddress();
    return;
L_00363E:
    opINC(0x00BD, 1);
    popAddress();
}

void game::SUB_003641() {
    y = 0x01;
    myMapper->writeCPU(0x00C5, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00C4, a);
    SUB_0033E3();
    return;
}

void game::SUB_003653() {
    y = myMapper->readCPU(0x00BC);
    setLoadFlag(y);
    if (flgZ) {
        goto L_00365E;
    }
    opDEC(0x00BC, 1);
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    popAddress();
    return;
L_00365E:
    opDEC(0x00BD, 1);
    opDEC(0x00BC, 1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_003665() {
    a = 0x00;
    SUB_003667();
    return;
}

void game::SUB_003667() {
    x = 0x00;
    SUB_003669();
    return;
}

void game::SUB_003669() {
    opPHA();
    a = myMapper->readCPU(0x00BC);
    flgC = true;
    opSBC(0x02);
    myMapper->writeCPU(0x00BC, a);
    if (flgC) {
        goto L_003675;
    }
    opDEC(0x00BD, 1);
L_003675:
    y = 0x01;
    a = x;
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    opPLA();
    opDEY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_00367F() {
    flgC = false;
    a = myMapper->readCPU(0x03F5);
    opADC(0xB3);
    myMapper->writeCPU(0x03F5, a);
    opADC(myMapper->readCPU(0x03F6));
    myMapper->writeCPU(0x03F6, a);
    opADC(myMapper->readCPU(0x03F7));
    myMapper->writeCPU(0x03F7, a);
    opAND(0x7F);
    x = a;
    a = myMapper->readCPU(0x03F7);
    opADC(myMapper->readCPU(0x03F8));
    myMapper->writeCPU(0x03F8, a);
    popAddress();
}

void game::SUB_0036A1() {
    myMapper->writeCPU(0x03F5, a);
    myMapper->writeCPU(0x03F6, x);
    a = 0x00;
    myMapper->writeCPU(0x03F7, a);
    myMapper->writeCPU(0x03F8, a);
    popAddress();
}

void game::SUB_0036B0() {
    myMapper->writeCPU(0x00CD, x);
    if (x < 0x00) {
        pushAddress(0x0036B6);
        SUB_003627();
        if (poppedEntry.value != 0x0036B6) return;
    }
    myMapper->writeCPU(0x00CA, a);
    myMapper->writeCPU(0x00CB, x);
    pushAddress(0x0036BD);
    SUB_0033DB();
    if (poppedEntry.value != 0x0036BD) return;
    myMapper->writeCPU(0x00CC, x);
    if (x >= 0x00) {
        goto L_0036C9;
    }
    pushAddress(0x0036C6);
    SUB_003627();
    if (poppedEntry.value != 0x0036C6) return;
L_0036C9:
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, x);
    SUB_00372E();
    return;
}

void game::SUB_0036D0() {
    opPHA();
    myMapper->writeCPU(0x00CC, y);
    y = 0x01;
    myMapper->writeCPU(0x00C5, myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00C4, a);
    y = myMapper->readCPU(0x00CC);
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
    SUB_0033E3();
    return;
}

void game::SUB_0036E6() {
    myMapper->writeCPU(0x00CC, a);
    myMapper->writeCPU(0x00CD, x);
    myMapper->writeCPU(0x00CE, y);
    pushAddress(0x0036EC);
    SUB_003641();
    if (poppedEntry.value != 0x0036EC) return;
    y = myMapper->readCPU(0x00CE);
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x00CC));
    opINY(1);
    a = myMapper->readCPU(0x00CD);
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    x = a;
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x00BE));
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x00BF));
    a = myMapper->readCPU(0x00CC);
    popAddress();
}

void game::SUB_00370A() {
    flgC = true;
    opEOR(0xFF);
    y = 0x00;
    opADC(myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    opINY(1);
    opPHA();
    a = x;
    opEOR(0xFF);
    opADC(myMapper->readCPU(myMapper->readCPU(0x00BC) + (myMapper->readCPU((0x00BC + 1) & 0x00ff) << 8) + y));
    x = a;
    opPLA();
    SUB_00331A();
    return;
}

void game::SUB_00371D() {
    x = 0x00;
    myMapper->writeCPU(0x00CA, a);
    myMapper->writeCPU(0x00CB, x);
    pushAddress(0x003723);
    SUB_003641();
    if (poppedEntry.value != 0x003723) return;
    pushAddress(0x003726);
    SUB_00372E();
    if (poppedEntry.value != 0x003726) return;
    a = myMapper->readCPU(0x00C4);
    x = myMapper->readCPU(0x00C5);
    popAddress();
}

void game::SUB_00372E() {
    a = 0x00;
    myMapper->writeCPU(0x00BF, a);
    y = 0x10;
    if (myMapper->readCPU(0x00CB) == 0) {
        goto L_003757;
    }
    do {
        opASL_M(0x00C4, 1);
        opROL_M(0x00C5, 1);
        opROL_A(1);
        opROL_M(0x00BF, 1);
        x = a;
        opCMP(a, myMapper->readCPU(0x00CA));
        a = myMapper->readCPU(0x00BF);
        opSBC(myMapper->readCPU(0x00CB));
        if (!flgC) {
            goto L_003750;
        }
        myMapper->writeCPU(0x00BF, a);
        a = x;
        opSBC(myMapper->readCPU(0x00CA));
        x = a;
        opINC(0x00C4, 1);
    L_003750:
        a = x;
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x00BE, a);
    popAddress();
    return;
    do {
    L_003757:
        opASL_M(0x00C4, 1);
        opROL_M(0x00C5, 1);
        opROL_A(1);
        if (flgC) {
            goto L_003762;
        }
        opCMP(a, myMapper->readCPU(0x00CA));
        if (!flgC) {
            goto L_003766;
        }
    L_003762:
        opSBC(myMapper->readCPU(0x00CA));
        opINC(0x00C4, 1);
    L_003766:
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x00BE, a);
    popAddress();
}

void game::SUB_00376C() {
    x = 0x00;
    SUB_00376E();
    return;
}

void game::SUB_00376E() {
    myMapper->writeCPU(0x00CA, a);
    myMapper->writeCPU(0x00CB, x);
    pushAddress(0x003772);
    SUB_003641();
    if (poppedEntry.value != 0x003772) return;
    pushAddress(0x003775);
    SUB_00372E();
    if (poppedEntry.value != 0x003775) return;
    a = myMapper->readCPU(0x00BE);
    x = myMapper->readCPU(0x00BF);
    popAddress();
}

void game::SUB_00377D() {
    myMapper->writeCPU(0x00C4, 0xF9);
    myMapper->writeCPU(0x00C5, 0x03);
    a = 0x00;
    y = a;
    x = 0x02;
    setLoadFlag(x);
    if (flgZ) {
        goto L_003796;
    }
    do {
        do {
            myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
        } while (!flgZ);
        opINC(0x00C5, 1);
        opDEX(1);
    } while (!flgZ);
    do {
    L_003796:
        if (y == 0x26) {
            goto L_00379F;
        }
        myMapper->writeCPU(myMapper->readCPU(0x00C4) + (myMapper->readCPU((0x00C4 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
    } while (!flgZ);
L_00379F:
    popAddress();
}

