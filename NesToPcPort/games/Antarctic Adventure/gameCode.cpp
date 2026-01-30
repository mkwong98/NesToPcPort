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

void game::SUB_000010() {
    if (myMapper->readCPU(0x00C2) == 0) {
        goto L_00001D;
    }
    a = myMapper->readCPU(0x00C1);
    opCMP(a, 0x07);
    if (!flgZ) {
        goto L_000023;
    }
    pushAddress(0x00001A);
    SUB_000612();
    if (poppedEntry.value != 0x00001A) return;
L_00001D:
    pushAddress(0x00001D);
    SUB_000519();
    if (poppedEntry.value != 0x00001D) return;
    SUB_00002A();
    return;
L_000023:
    opCMP(a, 0x03);
    if (!flgZ) {
        SUB_00002A();
        return;
    }
    pushAddress(0x000027);
    SUB_000612();
    if (poppedEntry.value != 0x000027) return;
    SUB_00002A();
    return;
}

void game::SUB_00002A() {
    y = 0x00;
    a = myMapper->readCPU(0x065C + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_000052;
    }
    myMapper->writeCPU(0x00C3, a);
    opINY(1);
    do {
        x = myMapper->readCPU(0x065C + y);
        opINY(1);
        a = myMapper->readCPU(0x065C + y);
        opINY(1);
        pushAddress(0x00003C);
        SUB_00009C();
        if (poppedEntry.value != 0x00003C) return;
        x = myMapper->readCPU(0x065C + y);
        opINY(1);
        do {
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x065C + y));
            opINY(1);
            opDEX(1);
        } while (!flgZ);
        opDEC(0x00C3, 1);
    } while (!flgZ);
L_000052:
    a = 0x00;
    myMapper->writeCPU(0x065C, a);
    popAddress();
}

void game::SUB_000058() {
    pushAddress(0x000058);
    SUB_0006CB();
    if (poppedEntry.value != 0x000058) return;
    pushAddress(0x00005B);
    SUB_00095B();
    if (poppedEntry.value != 0x00005B) return;
    pushAddress(0x00005E);
    SUB_00099C();
    if (poppedEntry.value != 0x00005E) return;
    pushAddress(0x000061);
    SUB_0005C5();
    if (poppedEntry.value != 0x000061) return;
    pushAddress(0x000064);
    SUB_0004D5();
    if (poppedEntry.value != 0x000064) return;
    pushAddress(0x000067);
    SUB_001F88();
    if (poppedEntry.value != 0x000067) return;
    pushAddress(0x00006A);
    SUB_002297();
    if (poppedEntry.value != 0x00006A) return;
    pushAddress(0x00006D);
    SUB_002496();
    if (poppedEntry.value != 0x00006D) return;
    pushAddress(0x000070);
    SUB_00008C();
    if (poppedEntry.value != 0x000070) return;
    SUB_0002F7();
    return;
}

void game::SUB_000076() {
    y = 0x60;
    myMapper->writeCPU(0x0090, 0x90);
    a = 0x20;
    x = 0x00;
    pushAddress(0x000080);
    SUB_00009C();
    if (poppedEntry.value != 0x000080) return;
    a = myMapper->readCPU(0x0090);
    do {
        myMapper->writeCPU(0x2007, a);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00008C() {
    y = 0x04;
    do {
        myMapper->writeCPU(0x01FF + y, myMapper->readCPU(0xC097 + y));
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00009C() {
    opPHA();
    a = myMapper->readCPU(0x2002);
    opPLA();
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, x);
    popAddress();
}

void game::SUB_0000A8() {
    pushAddress(0x0000A8);
    SUB_002F27();
    if (poppedEntry.value != 0x0000A8) return;
    pushAddress(0x0000AB);
    SUB_002F07();
    if (poppedEntry.value != 0x0000AB) return;
    pushAddress(0x0000AE);
    SUB_000107();
    if (poppedEntry.value != 0x0000AE) return;
    myMapper->writeCPU(0x00DA, 0x00);
    pushAddress(0x0000B5);
    SUB_00022D();
    if (poppedEntry.value != 0x0000B5) return;
    pushAddress(0x0000B8);
    SUB_00002A();
    if (poppedEntry.value != 0x0000B8) return;
    pushAddress(0x0000BB);
    SUB_000169();
    if (poppedEntry.value != 0x0000BB) return;
    pushAddress(0x0000BE);
    SUB_000172();
    if (poppedEntry.value != 0x0000BE) return;
    pushAddress(0x0000C1);
    SUB_00017B();
    if (poppedEntry.value != 0x0000C1) return;
    pushAddress(0x0000C4);
    SUB_000184();
    if (poppedEntry.value != 0x0000C4) return;
    myMapper->writeCPU(0x0080, 0xE0);
    myMapper->writeCPU(0x0081, 0x21);
    myMapper->writeCPU(0x0082, 0x00);
    y = 0x02;
    do {
        a = 0xB1;
        pushAddress(0x0000D7);
        SUB_003833();
        if (poppedEntry.value != 0x0000D7) return;
        opINC(0x0081, 1);
        myMapper->writeCPU(0x0082, 0xC0);
        opDEY(1);
    } while (!flgZ);
    a = 0x09;
    pushAddress(0x0000E5);
    SUB_001063();
    if (poppedEntry.value != 0x0000E5) return;
    a = 0x00;
    pushAddress(0x0000EA);
    SUB_001067();
    if (poppedEntry.value != 0x0000EA) return;
    a = 0x01;
    pushAddress(0x0000EF);
    SUB_001067();
    if (poppedEntry.value != 0x0000EF) return;
    pushAddress(0x0000F2);
    SUB_00002A();
    if (poppedEntry.value != 0x0000F2) return;
    a = 0x17;
    pushAddress(0x0000F7);
    SUB_001063();
    if (poppedEntry.value != 0x0000F7) return;
    a = 0x0E;
    pushAddress(0x0000FC);
    SUB_001067();
    if (poppedEntry.value != 0x0000FC) return;
    a = 0x0F;
    pushAddress(0x000101);
    SUB_001067();
    if (poppedEntry.value != 0x000101) return;
    SUB_00002A();
    return;
}

void game::SUB_000107() {
    x = myMapper->readCPU(0x00DC);
    if (myMapper->readCPU(0xC129 + x) != 0) {
        pushAddress(0x00010E);
        SUB_002F1F();
        if (poppedEntry.value != 0x00010E) return;
    }
    opCMP(myMapper->readCPU(0x0000), 0x08);
    if (flgC) {
        goto L_000128;
    }
    a = 0x20;
    x = 0xC0;
    pushAddress(0x00011B);
    SUB_00009C();
    if (poppedEntry.value != 0x00011B) return;
    x = 0xE0;
    a = 0x98;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
L_000128:
    popAddress();
}

void game::SUB_000133() {
    a = 0x08;
    setLoadFlag(a);
    myMapper->writeCPU(0x0090, a);
    if (!flgZ) {
        goto L_00013B;
    }
    y = 0x00;
    do {
    L_00013B:
        a = myMapper->readCPU(0xC149 + y);
        myMapper->writeCPU(0x02E0 + y, a);
        opINY(1);
        opDEC(0x0090, 1);
    } while (!flgZ);
    opDEC(0x00B0, 1);
    popAddress();
}

void game::SUB_000169() {
    myMapper->writeCPU(0x00A4, 0x05);
    y = 0x00;
    SUB_000133();
    return;
}

void game::SUB_000172() {
    myMapper->writeCPU(0x00A5, 0x0F);
    y = 0x08;
    SUB_000133();
    return;
}

void game::SUB_00017B() {
    myMapper->writeCPU(0x00A6, 0x0A);
    y = 0x10;
    SUB_000133();
    return;
}

void game::SUB_000184() {
    myMapper->writeCPU(0x00A7, 0x14);
    y = 0x18;
    SUB_000133();
    return;
}

void game::SUB_00018D() {
    a = myMapper->readCPU(0x00C0);
    opAND(0x80);
    if (!flgZ) {
        a = myMapper->readCPU(0x00C0);
        opAND(0x40);
        if (!flgZ) {
            goto L_0001CE;
        }
        a = myMapper->readCPU(0x00C0);
        opAND(0x20);
        if (!flgZ) {
            goto L_0001A2;
        }
    }
    SUB_00023F();
    return;
L_0001A2:
    opCMP(myMapper->readCPU(0x00A2), 0x20);
    if (!flgN) {
        myMapper->writeCPU(0x00A2, 0x00);
    }
    opINC(0x00A2, 1);
    a = myMapper->readCPU(0x00A2);
    myMapper->writeCPU(0x00B6, a);
    y = a;
    pushAddress(0x0001B3);
    SUB_000204();
    if (poppedEntry.value != 0x0001B3) return;
    do {
        opINX(1);
        a = myMapper->readCPU(0xC252 + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_0001C4;
        }
        myMapper->writeCPU(0x065C + x, a);
        opINY(1);
    } while (!flgZ);
L_0001C4:
    y = 0x00;
    do {
        pushAddress(0x0001C6);
        SUB_000222();
        if (poppedEntry.value != 0x0001C6) return;
        opDEC(0x00B6, 1);
    } while (!flgZ);
    popAddress();
    return;
L_0001CE:
    opCMP(myMapper->readCPU(0x00A0), 0x1F);
    if (flgN) {
        goto L_0001D7;
    }
    pushAddress(0x0001D4);
    SUB_00022D();
    if (poppedEntry.value != 0x0001D4) return;
L_0001D7:
    opINC(0x00A0, 1);
    a = 0x20;
    flgC = true;
    opSBC(myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x0501, a);
    myMapper->writeCPU(0x00B7, myMapper->readCPU(0x00A0));
    pushAddress(0x0001E5);
    SUB_000204();
    if (poppedEntry.value != 0x0001E5) return;
    y = myMapper->readCPU(0x0501);
    do {
        opINX(1);
        a = myMapper->readCPU(0xC252 + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_0001F9;
        }
        myMapper->writeCPU(0x065C + x, a);
        opINY(1);
    } while (!flgZ);
L_0001F9:
    y = 0x00;
    do {
        pushAddress(0x0001FB);
        SUB_000222();
        if (poppedEntry.value != 0x0001FB) return;
        opDEC(0x0501, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_000204() {
    myMapper->writeCPU(0x0090, 0x20);
    a = 0x01;
    x = myMapper->readCPU(0x00DA);
    myMapper->writeCPU(0x065C + x, a);
    a = 0xA0;
    opINX(1);
    myMapper->writeCPU(0x065C + x, a);
    a = 0x21;
    opINX(1);
    myMapper->writeCPU(0x065C + x, a);
    a = myMapper->readCPU(0x0090);
    opINX(1);
    myMapper->writeCPU(0x065C + x, a);
    popAddress();
}

void game::SUB_000222() {
    a = myMapper->readCPU(0xC252 + y);
    SUB_000225();
    return;
}

void game::SUB_000225() {
    myMapper->writeCPU(0x065C + x, a);
    SUB_000228();
    return;
}

void game::SUB_000228() {
    opINX(1);
    opINY(1);
    opDEC(0x0090, 1);
    popAddress();
}

void game::SUB_00022D() {
    pushAddress(0x00022D);
    SUB_000204();
    if (poppedEntry.value != 0x00022D) return;
    opINX(1);
    y = 0x00;
    do {
        pushAddress(0x000233);
        SUB_000222();
        if (poppedEntry.value != 0x000233) return;
    } while (!flgZ);
    a = 0x00;
    myMapper->writeCPU(0x00A2, a);
    myMapper->writeCPU(0x00A0, a);
    popAddress();
}

void game::SUB_00023F() {
    x = myMapper->readCPU(0x00C0);
    y = myMapper->readCPU(0xC273 + x);
    pushAddress(0x000245);
    SUB_000204();
    if (poppedEntry.value != 0x000245) return;
    opINX(1);
    do {
        a = myMapper->readCPU(0xC277 + y);
        pushAddress(0x00024C);
        SUB_000225();
        if (poppedEntry.value != 0x00024C) return;
    } while (!flgZ);
    popAddress();
}

void game::SUB_0002F7() {
    pushAddress(0x0002F7);
    SUB_000471();
    if (poppedEntry.value != 0x0002F7) return;
    a = myMapper->readCPU(0x0070);
    opCMP(a, 0x07);
    if (!flgN) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00D4);
    opORA(myMapper->readCPU(0x00D5));
    opORA(myMapper->readCPU(0x00D6));
    opORA(myMapper->readCPU(0x00D7));
    if (!flgZ) {
        a = myMapper->readCPU(0x009A);
        setLoadFlag(a);
        if (flgZ) {
            goto L_000312;
        }
        opDEC(0x009A, 1);
    }
    popAddress();
    return;
L_000312:
    myMapper->writeCPU(0x0090, 0xE0);
    myMapper->writeCPU(0x0091, 0x02);
    a = myMapper->readCPU(0x00A4);
    setLoadFlag(a);
    if (flgZ) {
        opDEC(0x00AE, 1);
    }
    myMapper->writeCPU(0x00AF, a);
    a = myMapper->readCPU(0x00C2);
    flgC = true;
    opSBC(0x08);
    x = a;
    myMapper->writeCPU(0x009A, myMapper->readCPU(0xC4B7 + x));
    myMapper->writeCPU(0x00AD, 0x02);
    myMapper->writeCPU(0x00A8, 0x01);
    pushAddress(0x000335);
    SUB_000401();
    if (poppedEntry.value != 0x000335) return;
    if (myMapper->readCPU(0x00AF) == 0) {
        pushAddress(0x00033C);
        SUB_000458();
        if (poppedEntry.value != 0x00033C) return;
    }
    if (myMapper->readCPU(0x00B0) != 0) {
        opINC(0x00AE, 1);
        pushAddress(0x000345);
        SUB_000169();
        if (poppedEntry.value != 0x000345) return;
    }
    else {
        y = 0x00;
        opCMP(myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y), 0x5B);
        if (flgZ) {
            opDEC(0x00A4, 1);
        }
    }
    myMapper->writeCPU(0x0090, 0xE8);
    myMapper->writeCPU(0x0091, 0x02);
    a = myMapper->readCPU(0x00A5);
    setLoadFlag(a);
    if (flgZ) {
        opDEC(0x00B1, 1);
    }
    myMapper->writeCPU(0x00AF, a);
    myMapper->writeCPU(0x00AD, 0x01);
    myMapper->writeCPU(0x00A8, 0x01);
    pushAddress(0x00036D);
    SUB_000401();
    if (poppedEntry.value != 0x00036D) return;
    if (myMapper->readCPU(0x00AF) == 0) {
        pushAddress(0x000374);
        SUB_000446();
        if (poppedEntry.value != 0x000374) return;
    }
    if (myMapper->readCPU(0x00B0) != 0) {
        opINC(0x00B1, 1);
        pushAddress(0x00037E);
        SUB_000172();
        if (poppedEntry.value != 0x00037E) return;
    }
    else {
        y = 0x00;
        opCMP(myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y), 0x62);
        if (flgZ) {
            opDEC(0x00A5, 1);
        }
    }
    myMapper->writeCPU(0x0090, 0xF0);
    myMapper->writeCPU(0x0091, 0x02);
    a = myMapper->readCPU(0x00B0);
    a = myMapper->readCPU(0x00A6);
    setLoadFlag(a);
    if (flgZ) {
        opDEC(0x00B4, 1);
    }
    myMapper->writeCPU(0x00AF, a);
    myMapper->writeCPU(0x00AD, 0x01);
    myMapper->writeCPU(0x00A8, 0x01);
    pushAddress(0x0003A8);
    SUB_000401();
    if (poppedEntry.value != 0x0003A8) return;
    if (myMapper->readCPU(0x00AF) == 0) {
        pushAddress(0x0003AF);
        SUB_000458();
        if (poppedEntry.value != 0x0003AF) return;
    }
    if (myMapper->readCPU(0x00B0) != 0) {
        opINC(0x00B4, 1);
        pushAddress(0x0003B8);
        SUB_00017B();
        if (poppedEntry.value != 0x0003B8) return;
    }
    else {
        y = 0x00;
        opCMP(myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y), 0x62);
        if (flgZ) {
            opDEC(0x00A6, 1);
        }
    }
    myMapper->writeCPU(0x0090, 0xF8);
    myMapper->writeCPU(0x0091, 0x02);
    a = myMapper->readCPU(0x00A7);
    setLoadFlag(a);
    if (flgZ) {
        opDEC(0x00B5, 1);
    }
    myMapper->writeCPU(0x00AF, a);
    myMapper->writeCPU(0x00AD, 0x02);
    myMapper->writeCPU(0x00A8, 0x01);
    pushAddress(0x0003E0);
    SUB_000401();
    if (poppedEntry.value != 0x0003E0) return;
    if (myMapper->readCPU(0x00AF) == 0) {
        pushAddress(0x0003E7);
        SUB_000446();
        if (poppedEntry.value != 0x0003E7) return;
    }
    if (myMapper->readCPU(0x00B0) != 0) {
        opINC(0x00B5, 1);
        pushAddress(0x0003F0);
        SUB_000184();
        if (poppedEntry.value != 0x0003F0) return;
    }
    else {
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0x5B);
        if (!flgZ) {
            goto L_000400;
        }
        opDEC(0x00A7, 1);
    }
L_000400:
    popAddress();
}

void game::SUB_000401() {
    if (myMapper->readCPU(0x00AF) == 0) {
        goto L_000406;
    }
    popAddress();
    return;
L_000406:
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x00A8));
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    y = 0x04;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    opCMP(a, 0x28);
    if (flgN) {
        goto L_000420;
    }
    opCMP(a, 0x48);
    if (flgN) {
        goto L_000436;
    }
    opCMP(a, 0x50);
    if (flgN) {
        goto L_000426;
    }
    popAddress();
    return;
L_000420:
    pushAddress(0x000420);
    SUB_00046A();
    if (poppedEntry.value != 0x000420) return;
    opINC(0x00B0, 1);
    popAddress();
    return;
L_000426:
    pushAddress(0x000426);
    SUB_00046A();
    if (poppedEntry.value != 0x000426) return;
    a = 0xA7;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    y = 0x05;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, 0xA8);
    popAddress();
    return;
L_000436:
    pushAddress(0x000436);
    SUB_00046A();
    if (poppedEntry.value != 0x000436) return;
    a = 0xA9;
    y = 0x01;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    a = 0xAA;
    y = 0x05;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_000446() {
    y = 0x03;
    pushAddress(0x000448);
    SUB_0004CD();
    if (poppedEntry.value != 0x000448) return;
    y = 0x07;
    pushAddress(0x00044D);
    SUB_0004CD();
    if (poppedEntry.value != 0x00044D) return;
    pushAddress(0x000450);
    SUB_00046A();
    if (poppedEntry.value != 0x000450) return;
    y = 0x06;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_000458() {
    y = 0x03;
    pushAddress(0x00045A);
    SUB_0004C5();
    if (poppedEntry.value != 0x00045A) return;
    y = 0x07;
    pushAddress(0x00045F);
    SUB_0004C5();
    if (poppedEntry.value != 0x00045F) return;
    pushAddress(0x000462);
    SUB_00046A();
    if (poppedEntry.value != 0x000462) return;
    y = 0x06;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_00046A() {
    y = 0x02;
    a = 0x02;
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_000471() {
    pushAddress(0x000471);
    SUB_00048E();
    if (poppedEntry.value != 0x000471) return;
    do {
        myMapper->writeCPU(0x0204 + y, myMapper->readCPU(0xC497 + x));
        pushAddress(0x00047A);
        SUB_000228();
        if (poppedEntry.value != 0x00047A) return;
    } while (!flgZ);
    pushAddress(0x00047F);
    SUB_00048E();
    if (poppedEntry.value != 0x00047F) return;
    do {
        myMapper->writeCPU(0x02D0 + y, myMapper->readCPU(0xC4A7 + x));
        pushAddress(0x000488);
        SUB_000228();
        if (poppedEntry.value != 0x000488) return;
    } while (!flgZ);
    popAddress();
}

void game::SUB_00048E() {
    myMapper->writeCPU(0x0090, 0x10);
    x = 0x00;
    y = 0x00;
    popAddress();
}

void game::SUB_0004C5() {
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x00AD));
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_0004CD() {
    a = myMapper->readCPU(0x00AD);
    flgC = false;
    opADC(myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_0004D5() {
    if (myMapper->readCPU(0x0638) != 0) {
        goto L_000500;
    }
    a = myMapper->readCPU(0x0009);
    opAND(0x3F);
    if (!flgZ) {
        goto L_000518;
    }
    myMapper->writeCPU(0x0095, 0xA9);
    myMapper->writeCPU(0x0096, 0x00);
    pushAddress(0x0004E8);
    SUB_000762();
    if (poppedEntry.value != 0x0004E8) return;
    a = myMapper->readCPU(0x00AB);
    opORA(myMapper->readCPU(0x00AA));
    if (!flgZ) {
        goto L_000518;
    }
    if (myMapper->readCPU(0x00A9) != 0) {
        a = 0x0B;
        SUB_003A88();
        return;
    }
    myMapper->writeCPU(0x0638, 0x01);
    popAddress();
    return;
L_000500:
    if (myMapper->readCPU(0x0070) != 0x08) {
        if (myMapper->readCPU(0x00C1) < 0x03) {
            goto L_000518;
        }
    }
    a = myMapper->readCPU(0x00D7);
    opORA(myMapper->readCPU(0x00D6));
    opORA(myMapper->readCPU(0x00D5));
    opORA(myMapper->readCPU(0x00D4));
    if (flgZ) {
        goto L_000518;
    }
    opINC(0x000A, 1);
L_000518:
    popAddress();
}

void game::SUB_000519() {
    myMapper->writeCPU(0x0095, 0xA9);
    myMapper->writeCPU(0x0096, 0x00);
    x = 0x87;
    a = 0x20;
    SUB_00061E();
    return;
}

void game::SUB_000528() {
    x = 0x0C;
    a = myMapper->readCPU(0x00C2);
    setLoadFlag(a);
    if (!flgZ) {
        if (a != 0x12) {
            goto L_000535;
        }
        flgC = false;
        opADC(0x01);
    L_000535:
        flgC = true;
        opSBC(0x08);
        x = a;
    }
    y = myMapper->readCPU(0xC56A + x);
    myMapper->writeCPU(0x0090, 0x06);
    a = myMapper->readCPU(0x065C);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x065C, a);
    x = myMapper->readCPU(0x00DA);
    myMapper->writeCPU(0x065C + x, 0x99);
    a = 0x20;
    opINX(1);
    myMapper->writeCPU(0x065C + x, a);
    a = myMapper->readCPU(0x0090);
    opINX(1);
    myMapper->writeCPU(0x065C + x, a);
    do {
        opINX(1);
        a = myMapper->readCPU(0xC577 + y);
        myMapper->writeCPU(0x065C + x, a);
        opINY(1);
        opDEC(0x0090, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0005C5() {
    if (myMapper->readCPU(0x00C2) != 0) {
        goto L_0005CD;
    }
    x = 0x07;
    setLoadFlag(x);
    if (!flgZ) {
        goto L_0005D8;
    }
L_0005CD:
    opDEC(0x00C1, 1);
    a = myMapper->readCPU(0x00C1);
    opCMP(a, 0x08);
    if (!flgC) {
        goto L_0005D6;
    }
    popAddress();
    return;
L_0005D6:
    x = myMapper->readCPU(0x00C1);
L_0005D8:
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xC5E6));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xC5E7));
    a = x;
    SUB_003760();
    return;
}

void game::SUB_0005F7() {
    if (myMapper->readCPU(0x00CE) == 0) {
        goto L_000601;
    }
    pushAddress(0x0005FB);
    SUB_000C7F();
    if (poppedEntry.value != 0x0005FB) return;
    SUB_000528();
    return;
L_000601:
    x = 0x01;
    if (myMapper->readCPU(0x00C2) == 0) {
        goto L_00060D;
    }
    opDEX(1);
    myMapper->writeCPU(0x00DA, x);
    pushAddress(0x00060A);
    SUB_00018D();
    if (poppedEntry.value != 0x00060A) return;
L_00060D:
    myMapper->writeCPU(0x00DA, x);
    SUB_000528();
    return;
}

void game::SUB_000612() {
    myMapper->writeCPU(0x0095, 0xD4);
    myMapper->writeCPU(0x0096, 0x00);
    x = 0x8F;
    a = 0x20;
    SUB_00061E();
    return;
}

void game::SUB_00061E() {
    pushAddress(0x00061E);
    SUB_00009C();
    if (poppedEntry.value != 0x00061E) return;
    y = 0x03;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y);
        opORA(0x30);
        myMapper->writeCPU(0x2007, a);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_00062E() {
    pushAddress(0x00062E);
    SUB_0006AD();
    if (poppedEntry.value != 0x00062E) return;
    a = 0x0D;
    myMapper->writeCPU(0x00C1, a);
    myMapper->writeCPU(0x00C2, a);
    a = 0x01;
    myMapper->writeCPU(0x00C6, a);
    myMapper->writeCPU(0x00C9, a);
    myMapper->writeCPU(0x0603, 0x0F);
    myMapper->writeCPU(0x009D, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x00D4, a);
    myMapper->writeCPU(0x00D5, a);
    myMapper->writeCPU(0x00A9, a);
    myMapper->writeCPU(0x00AC, a);
    a = myMapper->readCPU(0x00DC);
    opASL_A(1);
    y = a;
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00D6, myMapper->readCPU(0xC777 + x));
    myMapper->writeCPU(0x00D7, myMapper->readCPU(0xC778 + x));
    myMapper->writeCPU(0x00AA, myMapper->readCPU(0xC779 + x));
    myMapper->writeCPU(0x00AB, myMapper->readCPU(0xC77A + x));
    //myMapper->writeCPU(0x00A9, 0x9);
    //myMapper->writeCPU(0x00AA, 0x9);
    //myMapper->writeCPU(0x00AB, 0x9);
    if (myMapper->readCPU(0x00DD) != 0) {
        if (myMapper->readCPU(0x06DE + y) == 0) {
            goto L_000698;
        }
        x = 0x00;
        myMapper->writeCPU(0x0090, 0x02);
        flgC = true;
        do {
            a = myMapper->readCPU((0x00A9 + x) & 0x00ff);
            opSBC(myMapper->readCPU(0x06DD + y));
            if (flgC) {
                goto L_000684;
            }
            opADC(0x0A);
            flgC = false;
        L_000684:
            myMapper->writeCPU((0x00A9 + x) & 0x00ff, a);
            opINY(1);
            opINX(1);
            opDEC(0x0090, 1);
        } while (!flgZ);
        if (!flgC) {
            opDEC((0x00A9 + x) & 0x00ff, 1);
        }
        opDEX(1);
        y = myMapper->readCPU(0x00DD);
        opDEY(1);
        if (!flgZ) {
            goto L_000698;
        }
        opINC((0x00A9 + x) & 0x00ff, 1);
    }
L_000698:
    popAddress();
}

void game::SUB_000699() {
    y = 0x00;
    myMapper->writeCPU(0x00DC, y);
    myMapper->writeCPU(0x00DD, y);
    a = myMapper->readCPU(0x0003);
    opAND(0x40);
    if (flgZ) {
        goto L_0006A8;
    }
    y = myMapper->readCPU(0x0731);
L_0006A8:
    myMapper->writeCPU(0x009C, y);
    opINY(1);
    myMapper->writeCPU(0x0061, y);
    SUB_0006AD();
    return;
}

void game::SUB_0006AD() {
    x = 0x1C;
    a = 0x00;
    do {
        myMapper->writeCPU((0x00B7 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgZ);
    x = 0xDC;
    a = 0x00;
    do {
        myMapper->writeCPU(0x05FF + x, a);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0006CB() {
    if (myMapper->readCPU(0x0070) >= 0x07) {
        goto L_00070B;
    }
    a = myMapper->readCPU(0x0007);
    opAND(0x08);
    if (!flgZ) {
        myMapper->writeCPU(0x0600, 0x02);
        opDEC(0x0601, 1);
        if (flgN) {
            myMapper->writeCPU(0x0601, 0x0C);
            if (myMapper->readCPU(0x00C2) >= 0x09) {
                opDEC(0x00C2, 1);
            }
        }
    }
    a = myMapper->readCPU(0x0007);
    opAND(0x04);
    if (!flgZ) {
        myMapper->writeCPU(0x0601, 0x0C);
        opDEC(0x0600, 1);
        if (flgN) {
            myMapper->writeCPU(0x0600, 0x02);
            if (myMapper->readCPU(0x00C2) >= 0x12) {
                goto L_00070B;
            }
            opINC(0x00C2, 1);
        }
    }
L_00070B:
    popAddress();
}

void game::SUB_00070C() {
    pushAddress(0x00070C);
    SUB_000721();
    if (poppedEntry.value != 0x00070C) return;
    myMapper->writeCPU(0x00C1, myMapper->readCPU(0x00C2));
    SUB_000713();
    return;
}

void game::SUB_000713() {
    pushAddress(0x000713);
    SUB_0007F0();
    if (poppedEntry.value != 0x000713) return;
    myMapper->writeCPU(0x0095, 0xD4);
    myMapper->writeCPU(0x0096, 0x00);
    SUB_000762();
    return;
}

void game::SUB_000721() {
    a = myMapper->readCPU(0x00D6);
    opLSR_A(1);
    if (!flgC) {
        goto L_00073C;
    }
    myMapper->writeCPU(0x0639, 0x00);
    a = myMapper->readCPU(0x00C0);
    opAND(0x10);
    if (flgZ) {
        goto L_000761;
    }
    if (myMapper->readCPU(0x063A) != 0) {
        goto L_000761;
    }
    opINC(0x063A, 1);
    goto L_000749;
L_00073C:
    myMapper->writeCPU(0x063A, 0x00);
    if (myMapper->readCPU(0x0639) != 0) {
        goto L_000761;
    }
    opINC(0x0639, 1);
L_000749:
    a = myMapper->readCPU(0x00DC);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0090, myMapper->readCPU(0xC79F + y));
    myMapper->writeCPU(0x0091, myMapper->readCPU(0xC7A0 + y));
    y = myMapper->readCPU(0x0602);
    myMapper->writeCPU(0x00C0, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
    opINC(0x0602, 1);
L_000761:
    popAddress();
}

void game::SUB_000762() {
    y = 0x00;
    do {
        x = myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y);
        opDEX(1);
        a = x;
        setLoadFlag(a);
        myMapper->writeCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y, a);
        if (!flgN) {
            goto L_000776;
        }
        a = 0x09;
        myMapper->writeCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opCMP(y, 0x04);
    } while (!flgZ);
L_000776:
    popAddress();
}

void game::SUB_0007F0() {
    a = myMapper->readCPU(0x00D7);
    opORA(myMapper->readCPU(0x00D6));
    if (flgZ) {
        a = myMapper->readCPU(0x00D5);
        opCMP(a, 0x08);
        if (!flgC) {
            x = a;
            opORA(myMapper->readCPU(0x00D4));
            if (!flgZ) {
                goto L_00081D;
            }
            a = 0x00;
            myMapper->writeCPU(0x00C1, a);
            myMapper->writeCPU(0x00C2, a);
            a = myMapper->readCPU(0x00DC);
            opASL_A(1);
            x = a;
            myMapper->writeCPU(0x06DD + x, myMapper->readCPU(0x00A9));
            opINX(1);
            myMapper->writeCPU(0x06DD + x, myMapper->readCPU(0x00AA));
            a = 0x01;
            myMapper->writeCPU(0x000B, a);
            myMapper->writeCPU(0x007E, a);
            popAddress();
            return;
        L_00081D:
            myMapper->writeCPU(0x00CE, 0x01);
        }
    }
    popAddress();
}

void game::SUB_000822() {
    myMapper->writeCPU(0x00DE, a);
    myMapper->writeCPU(0x00DF, x);
    if (!flgZ) {
        SUB_000841();
        return;
    }
    SUB_000828();
    return;
}

void game::SUB_000828() {
    a = 0x01;
    x = 0x0D;
    setLoadFlag(x);
    pushAddress(0x00082C);
    SUB_000822();
    if (poppedEntry.value != 0x00082C) return;
    pushAddress(0x00082F);
    SUB_000AC7();
    if (poppedEntry.value != 0x00082F) return;
    SUB_00070C();
    return;
}

void game::SUB_000835() {
    a = 0x0F;
    x = 0x10;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_000822();
        return;
    }
    SUB_00083B();
    return;
}

void game::SUB_00083B() {
    a = 0x0D;
    x = 0x0F;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_000822();
        return;
    }
    SUB_000841();
    return;
}

void game::SUB_000841() {
    myMapper->writeCPU(0x00DA, 0x01);
    y = 0x00;
    SUB_000847();
    return;
}

void game::SUB_000847() {
    myMapper->writeCPU(0x00DB, y);
    a = myMapper->readCPU(0x0607 + y);
    setLoadFlag(a);
    if (flgZ) {
        SUB_000892();
        return;
    }
    if (a == 0x10) {
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0607 + y, a);
        if (flgZ) {
            SUB_000892();
            return;
        }
    }
    if (a < myMapper->readCPU(0x00DE)) {
        SUB_000892();
        return;
    }
    if (a >= myMapper->readCPU(0x00DF)) {
        SUB_000892();
        return;
    }
    a = myMapper->readCPU(0x0608 + y);
    opAND(0x0F);
    if (a >= 0x05) {
        SUB_0008A5();
        return;
    }
    y = myMapper->readCPU(0x00DB);
    if (myMapper->readCPU(0x0608 + y) == 0) {
        pushAddress(0x000871);
        SUB_00093E();
        if (poppedEntry.value != 0x000871) return;
        pushAddress(0x000874);
        SUB_001073();
        if (poppedEntry.value != 0x000874) return;
    }
    else {
        pushAddress(0x00087A);
        SUB_000BD4();
        if (poppedEntry.value != 0x00087A) return;
    }
    if (myMapper->readCPU(0x00D1) != 0) {
        goto L_000884;
    }
    pushAddress(0x000881);
    SUB_001B84();
    if (poppedEntry.value != 0x000881) return;
L_000884:
    if (myMapper->readCPU(0x00EF) != 0) {
        SUB_00088B();
        return;
    }
    pushAddress(0x000888);
    SUB_001B0E();
    if (poppedEntry.value != 0x000888) return;
    SUB_00088B();
    return;
}

void game::SUB_00088B() {
    x = myMapper->readCPU(0x00DB);
    opINC(0x0607 + x, 1);
    SUB_000890();
    return;
}

void game::SUB_000890() {
    y = myMapper->readCPU(0x00DB);
    SUB_000892();
    return;
}

void game::SUB_000892() {
    a = y;
    flgC = false;
    opADC(0x06);
    y = a;
    opCMP(a, 0x1E);
    if (!flgC) {
        SUB_000847();
        return;
    }
    popAddress();
}

void game::SUB_00089C() {
    a = 0x0F;
    myMapper->writeCPU(0x0607 + y, a);
    myMapper->writeCPU(0x00DB, y);
    myMapper->writeCPU(0x00B8, a);
    SUB_0008A5();
    return;
}

void game::SUB_0008A5() {
    pushAddress(0x0008A5);
    SUB_00093E();
    if (poppedEntry.value != 0x0008A5) return;
    x = 0x00;
    y = 0x00;
    myMapper->writeCPU(0x0095, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x009D);
    if (a == 0xFF) {
        myMapper->writeCPU(0x009D, myMapper->readCPU(0x00DB));
    }
    else {
        if (a == myMapper->readCPU(0x00DB)) {
            goto L_0008D1;
        }
        if (myMapper->readCPU(0x029C + x) != 0xF4) {
            y = myMapper->readCPU(0x00DB);
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0607 + y, a);
            if (flgZ) {
                SUB_000890();
                return;
            }
        }
    }
L_0008D1:
    if (myMapper->readCPU(0x0704) == 0) {
        if (myMapper->readCPU(0x00BD) < 0x03) {
            goto L_0008E0;
        }
        myMapper->writeCPU(0x00BD, 0xFF);
    L_0008E0:
        opINC(0x00BD, 1);
    }
    do {
        opINY(1);
        myMapper->writeCPU(0x029C + x, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x029C + x, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
        opINX(1);
        opINY(1);
        a = myMapper->readCPU(0x0704);
        setLoadFlag(a);
        if (flgZ) {
            if (myMapper->readCPU(0x0705) == 0) {
                goto L_000902;
            }
            a = 0x03;
            setLoadFlag(a);
            myMapper->writeCPU(0x0704, a);
            if (!flgZ) {
                goto L_000904;
            }
        L_000902:
            a = myMapper->readCPU(0x00BD);
        }
    L_000904:
        myMapper->writeCPU(0x029C + x, a);
        opINX(1);
        myMapper->writeCPU(0x029C + x, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
        opINX(1);
        opDEC(0x0095, 1);
    } while (!flgZ);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    if (a != 0xFF) {
        myMapper->writeCPU(0x0095, a);
        do {
            opINY(1);
            myMapper->writeCPU(0x029C + x, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
            opINX(1);
            opDEC(0x0095, 1);
        } while (!flgZ);
    }
    y = myMapper->readCPU(0x00DB);
    opCMP(myMapper->readCPU(0x0607 + y), 0x0F);
    if (flgC) {
        y = 0xFF;
        myMapper->writeCPU(0x009D, y);
        a = myMapper->readCPU(0x00B8);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00093B;
        }
        opINY(1);
        myMapper->writeCPU(0x00B8, y);
        popAddress();
        return;
    }
L_00093B:
    SUB_00088B();
    return;
}

void game::SUB_00093E() {
    x = myMapper->readCPU(0x0607 + y);
    opDEX(1);
    a = x;
    opASL_A(1);
    opPHA();
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x0609 + y));
    a = myMapper->readCPU(0x060A + y);
    myMapper->writeCPU(0x0096, a);
    opPLA();
    y = a;
    myMapper->writeCPU(0x0090, myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0091, myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y));
    popAddress();
}

void game::SUB_00095B() {
    y = 0x0B;
    a = myMapper->readCPU(0x00D5);
    opAND(0x01);
    if (flgZ) {
        y = 0x09;
    }
    a = myMapper->readCPU(0x0061);
    x = 0x01;
    opAND(0xFC);
    if (!flgZ) {
        opINX(1);
        opAND(0xE0);
        if (!flgZ) {
            opINX(1);
        }
    }
    if (myMapper->readCPU(0x00C2) < 0x0D) {
        opINX(1);
        if (myMapper->readCPU(0x009C) >= 0x02) {
            goto L_00098C;
        }
        if (myMapper->readCPU(0x00D6) >= 0x08) {
            goto L_00098D;
        }
        if (myMapper->readCPU(0x00AA) < 0x03) {
            goto L_00098D;
        }
    L_00098C:
        opINX(1);
    }
    do {
    L_00098D:
        opDEY(2);
        if (y >= 0x02) {
            goto L_000995;
        }
        y = 0x02;
    L_000995:
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0604, y);
    popAddress();
}

void game::SUB_00099C() {
    a = myMapper->readCPU(0x00DC);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0x00D7);
    opLSR_A(1);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x00BE, myMapper->readCPU(0xCA07 + y));
    a = myMapper->readCPU(0x00DC);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0095, myMapper->readCPU(0xCA53 + y));
    myMapper->writeCPU(0x0096, myMapper->readCPU(0xCA54 + y));
    y = 0x00;
    a = myMapper->readCPU(0x00D6);
    opLSR_A(1);
    if (flgC) {
        myMapper->writeCPU(0x063C, y);
        if (myMapper->readCPU(0x063B) != 0) {
            goto L_000A06;
        }
        opINY(1);
        myMapper->writeCPU(0x063B, y);
        if (!flgZ) {
            goto L_0009DA;
        }
    }
    myMapper->writeCPU(0x063B, y);
    if (myMapper->readCPU(0x063C) == 0) {
        opINY(1);
        myMapper->writeCPU(0x063C, y);
    L_0009DA:
        opINC(0x063D, 1);
        y = myMapper->readCPU(0x063D);
        x = myMapper->readCPU(0x009C);
        a = myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y);
        opDEX(1);
        if (flgN) {
            goto L_0009F6;
        }
        if (!flgZ) {
            goto L_0009FA;
        }
        a = myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0009FA;
        }
        x = myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y);
        opDEX(1);
        a = x;
        goto L_0009FA;
    L_0009F6:
        a = myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y);
        opAND(0x03);
    L_0009FA:
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x00CC, myMapper->readCPU(0xCA1B + x));
        myMapper->writeCPU(0x00CD, myMapper->readCPU(0xCA1C + x));
    }
L_000A06:
    popAddress();
}

void game::SUB_000A7F() {
    a = myMapper->readCPU(0x00BF);
    opLSR_A(1);
    if (flgC) {
        opDEC(0x0627, 1);
        if (!flgZ) {
            goto L_000A8D;
        }
        myMapper->writeCPU(0x00BF, 0x00);
    L_000A8D:
        myMapper->writeCPU(0x0090, 0x03);
    }
    popAddress();
}

void game::SUB_000A92() {
    a = myMapper->readCPU(0x00D6);
    myMapper->writeCPU(0x0092, a);
    if (a < 0x07) {
        if (a < 0x03) {
            goto L_000A9E;
        }
    L_000A9E:
        if (myMapper->readCPU(0x00D5) == 0) {
            if (myMapper->readCPU(0x00D4) >= 0x02) {
                goto L_000ABC;
            }
            a = myMapper->readCPU(0x00DC);
            setLoadFlag(a);
            if (!flgZ) {
                opAND(myMapper->readCPU(0x0092));
                if (flgZ) {
                    goto L_000ABC;
                }
                myMapper->writeCPU(0x00BF, 0x03);
                y = myMapper->readCPU(0x00DC);
                myMapper->writeCPU(0x0627, myMapper->readCPU(0xCABD + y));
            }
        }
    }
L_000ABC:
    popAddress();
}

void game::SUB_000AC7() {
    pushAddress(0x000AC7);
    SUB_000A92();
    if (poppedEntry.value != 0x000AC7) return;
    a = myMapper->readCPU(0x00D7);
    opORA(myMapper->readCPU(0x00D6));
    if (flgZ) {
        if (myMapper->readCPU(0x00D5) < 0x0A) {
            goto L_000AFD;
        }
        if (myMapper->readCPU(0x00C2) == 0) {
            goto L_000AFD;
        }
    }
    opDEC(0x0605, 1);
    if (flgN) {
        myMapper->writeCPU(0x0605, myMapper->readCPU(0x0604));
        x = 0x00;
        y = 0x03;
        if (myMapper->readCPU(0x0061) >= 0x05) {
            opINY(1);
        }
        do {
            if (myMapper->readCPU(0x0607 + x) == 0) {
                goto L_000AFE;
            }
            a = x;
            flgC = false;
            opADC(0x06);
            x = a;
            opDEY(1);
        } while (!flgZ);
    }
L_000AFD:
    popAddress();
    return;
L_000AFE:
    opINC(0x0607 + x, 1);
    opINC(0x0606, 1);
    a = myMapper->readCPU(0x0606);
    if (a >= 0x06) {
        a = 0x00;
        myMapper->writeCPU(0x0606, a);
    }
    y = a;
    myMapper->writeCPU(0x0090, myMapper->readCPU(myMapper->readCPU(0x00CC) + (myMapper->readCPU((0x00CC + 1) & 0x00ff) << 8) + y));
    pushAddress(0x000B15);
    SUB_000A7F();
    if (poppedEntry.value != 0x000B15) return;
    opINC(0x0090, 1);
    if (!flgZ) {
        opDEC(0x0090, 1);
        a = myMapper->readCPU(0x0090);
        setLoadFlag(a);
        if (flgZ) {
            goto L_000B48;
        }
        opAND(0x0F);
        if (a >= 0x05) {
            goto L_000B48;
        }
        a = myMapper->readCPU(0x0090);
        opAND(0x10);
        if (flgZ) {
            goto L_000B3D;
        }
        a = myMapper->readCPU(0x0090);
        opAND(0x03);
        myMapper->writeCPU(0x0625, a);
        if (!flgZ) {
            goto L_000B48;
        }
    }
    myMapper->writeCPU(0x0607 + x, 0x00);
    popAddress();
    return;
L_000B3D:
    if (myMapper->readCPU(0x00E1) & 0x80) {
        a = myMapper->readCPU(0x0090);
        opLSR_A(1);
        if (flgC) {
            opINC(0x0090, 1);
        }
    }
L_000B48:
    myMapper->writeCPU(0x0608 + x, myMapper->readCPU(0x0090));
    if (myMapper->readCPU(0x0090) >= 0x05) {
        if (myMapper->readCPU(0x029C) != 0xF4) {
            goto L_000B79;
        }
        a = myMapper->readCPU(0x0009);
        y = 0x02;
        opAND(0x07);
        if (!flgZ) {
            y = 0x01;
            opAND(0x03);
            if (!flgZ) {
                y = 0x00;
                opINC(0x06F1, 1);
                a = myMapper->readCPU(0x06F1);
                opAND(0x03);
                if (!flgZ) {
                    y = 0x03;
                }
            }
        }
        myMapper->writeCPU(0x0704, y);
    }
L_000B79:
    pushAddress(0x000B79);
    SUB_000BA5();
    if (poppedEntry.value != 0x000B79) return;
    a = myMapper->readCPU(0x0625);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x02) {
            goto L_000B89;
        }
        a = 0x02;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_000B8B;
        }
    L_000B89:
        a = 0x01;
    L_000B8B:
        myMapper->writeCPU(0x0090, a);
        x = 0x18;
        if (myMapper->readCPU(0x0607 + x) != 0) {
            goto L_000B9F;
        }
        opINC(0x0607 + x, 1);
        myMapper->writeCPU(0x0608 + x, myMapper->readCPU(0x0090));
        pushAddress(0x000B9C);
        SUB_000BA5();
        if (poppedEntry.value != 0x000B9C) return;
    L_000B9F:
        myMapper->writeCPU(0x0625, 0x00);
    }
    popAddress();
}

void game::SUB_000BA5() {
    a = myMapper->readCPU(0x0090);
    opAND(0x0F);
    y = a;
    setLoadFlag(y);
    if (flgZ) {
        goto L_000BB6;
    }
    a = 0x04;
    do {
        opDEY(1);
        if (flgZ) {
            goto L_000BB6;
        }
        flgC = false;
        opADC(0x04);
    } while (!flgZ);
L_000BB6:
    y = a;
    myMapper->writeCPU(0x0090, 0x02);
    opINY(2);
    opINX(2);
    do {
        myMapper->writeCPU(0x0607 + x, myMapper->readCPU(0xCC61 + y));
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x0607 + x, myMapper->readCPU(0xCC61 + y));
        opINX(1);
        opINY(1);
        opDEC(0x0090, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_000BD4() {
    x = myMapper->readCPU(0x00DB);
    y = myMapper->readCPU(0x0607 + x);
    opDEY(1);
    a = y;
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x0609 + x));
    myMapper->writeCPU(0x0096, myMapper->readCPU(0x060A + x));
    myMapper->writeCPU(0x0090, myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0091, myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x060B + x));
    myMapper->writeCPU(0x0096, myMapper->readCPU(0x060C + x));
    myMapper->writeCPU(0x0093, myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y));
    opDEY(1);
    myMapper->writeCPU(0x0092, myMapper->readCPU(myMapper->readCPU(0x0095) + (myMapper->readCPU((0x0095 + 1) & 0x00ff) << 8) + y));
    y = 0x00;
    myMapper->writeCPU(0x0095, y);
    myMapper->writeCPU(0x0094, y);
    x = myMapper->readCPU(0x00DA);
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00D8, a);
    flgC = false;
    opADC(myMapper->readCPU(0x065C));
    myMapper->writeCPU(0x065C, a);
    do {
        y = myMapper->readCPU(0x0094);
        opINY(1);
        myMapper->writeCPU(0x065C + x, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x065C + x, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0094, y);
        y = myMapper->readCPU(0x0095);
        a = myMapper->readCPU(myMapper->readCPU(0x0092) + (myMapper->readCPU((0x0092 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x00D9, a);
        opINX(1);
        myMapper->writeCPU(0x065C + x, a);
        do {
            opINY(1);
            opINX(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0092) + (myMapper->readCPU((0x0092 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_000C4F;
            }
            opINY(1);
            myMapper->writeCPU(0x0096, myMapper->readCPU(myMapper->readCPU(0x0092) + (myMapper->readCPU((0x0092 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0092) + (myMapper->readCPU((0x0092 + 1) & 0x00ff) << 8) + y);
            do {
                opDEC(0x00D9, 1);
                myMapper->writeCPU(0x065C + x, a);
                opINX(1);
                opDEC(0x0096, 1);
            } while (!flgZ);
            opDEX(1);
            opINC(0x00D9, 1);
            goto L_000C52;
        L_000C4F:
            myMapper->writeCPU(0x065C + x, a);
        L_000C52:
            opDEC(0x00D9, 1);
        } while (!flgZ);
        opINY(1);
        myMapper->writeCPU(0x0095, y);
        opINX(1);
        opDEC(0x00D8, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x00DA, x);
    popAddress();
}

void game::SUB_000C7F() {
    a = myMapper->readCPU(0x00D5);
    setLoadFlag(a);
    if (flgZ) {
        SUB_000CC8();
        return;
    }
    if (a < 0x02) {
        SUB_000CBA();
        return;
    }
    if (a < 0x04) {
        SUB_000CB6();
        return;
    }
    if (a < 0x06) {
        SUB_000CA3();
        return;
    }
    y = 0x00;
    pushAddress(0x000C91);
    SUB_000CA5();
    if (poppedEntry.value != 0x000C91) return;
    y = 0x00;
    SUB_000C96();
    return;
}

void game::SUB_000C96() {
    myMapper->writeCPU(0x0090, myMapper->readCPU(0xCE88 + y));
    myMapper->writeCPU(0x0091, myMapper->readCPU(0xCE89 + y));
    SUB_001073();
    return;
}

void game::SUB_000CA3() {
    y = 0x02;
    SUB_000CA5();
    return;
}

void game::SUB_000CA5() {
    myMapper->writeCPU(0x00DA, 0x01);
    SUB_000CA9();
    return;
}

void game::SUB_000CA9() {
    myMapper->writeCPU(0x0090, myMapper->readCPU(0xCD13 + y));
    myMapper->writeCPU(0x0091, myMapper->readCPU(0xCD14 + y));
    SUB_001073();
    return;
}

void game::SUB_000CB6() {
    y = 0x04;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_000CA5();
        return;
    }
    SUB_000CBA();
    return;
}

void game::SUB_000CBA() {
    y = 0x06;
    pushAddress(0x000CBC);
    SUB_000CA5();
    if (poppedEntry.value != 0x000CBC) return;
    y = 0x02;
    pushAddress(0x000CC1);
    SUB_000C96();
    if (poppedEntry.value != 0x000CC1) return;
    y = 0x00;
    setLoadFlag(y);
    if (flgZ) {
        SUB_000CD9();
        return;
    }
    SUB_000CC8();
    return;
}

void game::SUB_000CC8() {
    y = 0x08;
    pushAddress(0x000CCA);
    SUB_000CA5();
    if (poppedEntry.value != 0x000CCA) return;
    y = 0x04;
    pushAddress(0x000CCF);
    SUB_000C96();
    if (poppedEntry.value != 0x000CCF) return;
    y = 0x0A;
    pushAddress(0x000CD4);
    SUB_000CA9();
    if (poppedEntry.value != 0x000CD4) return;
    y = 0x09;
    SUB_000CD9();
    return;
}

void game::SUB_000CD9() {
    myMapper->writeCPU(0x00D0, 0x01);
    x = 0x00;
    myMapper->writeCPU(0x0090, myMapper->readCPU(0xCCF1 + y));
    do {
        opINY(1);
        myMapper->writeCPU(0x0264 + x, myMapper->readCPU(0xCCF1 + y));
        opINX(1);
        opDEC(0x0090, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_000EAE() {
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xCEBD));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xCEBE));
    a = myMapper->readCPU(0x00C4);
    SUB_003760();
    return;
}

void game::SUB_000ECF() {
    a = myMapper->readCPU(0x00C0);
    setLoadFlag(a);
    myMapper->writeCPU(0x0097, a);
    if (!flgN) {
        myMapper->writeCPU(0x00C8, 0x00);
    }
    a = myMapper->readCPU(0x00C0);
    opLSR_A(1);
    if (flgC) {
        SUB_000F0E();
        return;
    }
    x = myMapper->readCPU(0x00C6);
    opDEX(1);
    if (!flgZ) {
        x = myMapper->readCPU(0x00C8);
        opDEX(1);
        if (!flgZ) {
            myMapper->writeCPU(0x00C6, 0x01);
            a = 0x00;
            y = 0x01;
            opINC(0x00C5, 1);
            if (!flgZ) {
                SUB_000F4A();
                return;
            }
        }
    }
    opINC(0x00C5, 1);
    if (myMapper->readCPU(0x00C7) != 0) {
        goto L_000F00;
    }
    opINC(0x00C7, 1);
    a = 0x02;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000F48();
        return;
    }
L_000F00:
    myMapper->writeCPU(0x00C7, 0x00);
    a = 0x03;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000F48();
        return;
    }
    SUB_000F08();
    return;
}

void game::SUB_000F08() {
    a = 0x01;
    opINC(0x00C5, 1);
    if (!flgZ) {
        SUB_000F48();
        return;
    }
    SUB_000F0E();
    return;
}

void game::SUB_000F0E() {
    if (myMapper->readCPU(0x00C6) == 0x02) {
        goto L_000F28;
    }
    if (myMapper->readCPU(0x00C8) != 0x02) {
        myMapper->writeCPU(0x00C6, 0x02);
        a = 0x04;
        y = 0x02;
        myMapper->writeCPU(0x00C4, y);
        opINC(0x00C5, 1);
        if (!flgZ) {
            SUB_000F4A();
            return;
        }
    }
L_000F28:
    opINC(0x00C5, 1);
    opINC(0x00C7, 1);
    x = myMapper->readCPU(0x00C7);
    opDEX(1);
    if (flgZ) {
        goto L_000F3C;
    }
    opDEX(1);
    if (flgZ) {
        goto L_000F40;
    }
    myMapper->writeCPU(0x00C7, 0x00);
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000F48();
        return;
    }
L_000F3C:
    a = 0x06;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000F48();
        return;
    }
L_000F40:
    a = 0x07;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000F48();
        return;
    }
    SUB_000F44();
    return;
}

void game::SUB_000F44() {
    a = 0x05;
    opINC(0x00C5, 1);
    SUB_000F48();
    return;
}

void game::SUB_000F48() {
    y = 0x03;
    SUB_000F4A();
    return;
}

void game::SUB_000F4A() {
    myMapper->writeCPU(0x00C4, y);
    SUB_001063();
    return;
}

void game::SUB_000F4F() {
    if (myMapper->readCPU(0x0097) & 0x80) {
        goto L_000F57;
    }
    myMapper->writeCPU(0x00CB, 0x00);
L_000F57:
    a = myMapper->readCPU(0x0097);
    opAND(0x03);
    if (a >= 0x02) {
        SUB_000F8F();
        return;
    }
    x = myMapper->readCPU(0x00C9);
    opDEX(1);
    if (!flgZ) {
        x = myMapper->readCPU(0x00CB);
        opDEX(1);
        if (!flgZ) {
            myMapper->writeCPU(0x00C9, 0x01);
            a = 0x0E;
            y = 0x04;
            opINC(0x00C5, 1);
            if (!flgZ) {
                SUB_000F4A();
                return;
            }
        }
    }
    opINC(0x00C5, 1);
    if (myMapper->readCPU(0x00CA) != 0) {
        goto L_000F81;
    }
    opINC(0x00CA, 1);
    a = 0x10;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000FC7();
        return;
    }
L_000F81:
    myMapper->writeCPU(0x00CA, 0x00);
    a = 0x11;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000FC7();
        return;
    }
    SUB_000F89();
    return;
}

void game::SUB_000F89() {
    a = 0x0F;
    opINC(0x00C5, 1);
    if (!flgZ) {
        SUB_000FC7();
        return;
    }
    SUB_000F8F();
    return;
}

void game::SUB_000F8F() {
    if (myMapper->readCPU(0x00C9) == 0x02) {
        goto L_000FA7;
    }
    if (myMapper->readCPU(0x00CB) != 0x02) {
        myMapper->writeCPU(0x00C9, 0x02);
        a = 0x12;
        y = 0x05;
        opINC(0x00C5, 1);
        if (!flgZ) {
            SUB_000F4A();
            return;
        }
    }
L_000FA7:
    opINC(0x00C5, 1);
    opINC(0x00CA, 1);
    x = myMapper->readCPU(0x00CA);
    opDEX(1);
    if (flgZ) {
        goto L_000FBB;
    }
    opDEX(1);
    if (flgZ) {
        goto L_000FBF;
    }
    myMapper->writeCPU(0x00CA, 0x00);
    a = 0x16;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000FC7();
        return;
    }
L_000FBB:
    a = 0x14;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000FC7();
        return;
    }
L_000FBF:
    a = 0x15;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000FC7();
        return;
    }
    SUB_000FC3();
    return;
}

void game::SUB_000FC3() {
    a = 0x13;
    opINC(0x00C5, 1);
    SUB_000FC7();
    return;
}

void game::SUB_000FC7() {
    pushAddress(0x000FC7);
    SUB_001063();
    if (poppedEntry.value != 0x000FC7) return;
    opCMP(myMapper->readCPU(0x0097), myMapper->readCPU(0x0603));
    if (flgZ) {
    }
    else {
        a = myMapper->readCPU(0x00C0);
        setLoadFlag(a);
        myMapper->writeCPU(0x0603, a);
        if (flgN) {
            a = 0x00;
            myMapper->writeCPU(0x00C6, a);
            myMapper->writeCPU(0x00C9, a);
            a = myMapper->readCPU(0x0097);
            opAND(0xF0);
            if (a >= 0xC0) {
                a = myMapper->readCPU(0x0097);
                opLSR_A(1);
                if (flgC) {
                    goto L_001006;
                }
                a = 0x19;
                opPHA();
                a = 0x0B;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_001000;
                }
            }
            a = myMapper->readCPU(0x0097);
            opAND(0x02);
            if (flgZ) {
                a = 0x1A;
                opPHA();
                a = 0x0C;
            L_001000:
                y = 0x01;
                setLoadFlag(y);
                myMapper->writeCPU(0x00C8, y);
                if (!flgZ) {
                    goto L_001048;
                }
            L_001006:
                y = 0x02;
                myMapper->writeCPU(0x00C8, y);
                opDEY(1);
                myMapper->writeCPU(0x00CB, y);
                a = 0x19;
                opPHA();
                a = 0x0D;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_001048;
                }
            }
            y = 0x02;
            myMapper->writeCPU(0x00CB, y);
            opDEY(1);
            myMapper->writeCPU(0x00C8, y);
            a = 0x0C;
            opPHA();
            a = 0x1B;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001048;
            }
        }
        a = myMapper->readCPU(0x0097);
        opCMP(a, 0x01);
        if (!flgZ) {
            if (!flgC) {
                goto L_00103C;
            }
            if (a == 0x03) {
                goto L_001035;
            }
            a = 0x18;
            opPHA();
            a = 0x09;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001048;
            }
        L_001035:
            a = 0x18;
            opPHA();
            a = 0x0A;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001048;
            }
        L_00103C:
            a = 0x17;
            opPHA();
            a = 0x09;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001048;
            }
        }
        a = 0x17;
        opPHA();
        a = 0x0A;
    L_001048:
        pushAddress(0x001048);
        SUB_001067();
        if (poppedEntry.value != 0x001048) return;
        opPLA();
        pushAddress(0x00104C);
        SUB_001067();
        if (poppedEntry.value != 0x00104C) return;
    }
    y = myMapper->readCPU(0x00C5);
    opDEY(2);
    if (flgZ) {
        SUB_00105E();
        return;
    }
    SUB_001055();
    return;
}

void game::SUB_001055() {
    a = 0x00;
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C5, a);
    SUB_000713();
    return;
}

void game::SUB_00105E() {
    myMapper->writeCPU(0x00C4, 0x07);
    popAddress();
}

void game::SUB_001063() {
    myMapper->writeCPU(0x00DA, 0x01);
    SUB_001067();
    return;
}

void game::SUB_001067() {
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0090, myMapper->readCPU(0xD0BF + y));
    myMapper->writeCPU(0x0091, myMapper->readCPU(0xD0C0 + y));
    SUB_001073();
    return;
}

void game::SUB_001073() {
    x = myMapper->readCPU(0x00DA);
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00D8, a);
    flgC = false;
    opADC(myMapper->readCPU(0x065C));
    myMapper->writeCPU(0x065C, a);
    opINY(1);
    do {
        myMapper->writeCPU(0x0092, 0x03);
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x065C + x, a);
            opINY(1);
            opINX(1);
            opDEC(0x0092, 1);
        } while (!flgZ);
        myMapper->writeCPU(0x00D9, a);
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0010AF;
            }
            opINY(1);
            myMapper->writeCPU(0x0095, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
            do {
                myMapper->writeCPU(0x065C + x, a);
                opINX(1);
                opDEC(0x00D9, 1);
                opDEC(0x0095, 1);
            } while (!flgZ);
            opINC(0x00D9, 1);
            opDEX(1);
            if (flgZ) {
                goto L_0010B2;
            }
        L_0010AF:
            myMapper->writeCPU(0x065C + x, a);
        L_0010B2:
            opINX(1);
            opINY(1);
            opDEC(0x00D9, 1);
        } while (!flgZ);
        opDEC(0x00D8, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x00DA, x);
    popAddress();
}

void game::SUB_001B0E() {
    if (myMapper->readCPU(0x00D1) != 0) {
        goto L_001B6A;
    }
    if (myMapper->readCPU(0x0009) >= myMapper->readCPU(0x00BE)) {
        y = myMapper->readCPU(0x00DB);
        if (myMapper->readCPU(0x0607 + y) == 0x06) {
            a = myMapper->readCPU(0x0608 + y);
            x = a;
            opAND(0x0F);
            if (a < 0x03) {
                a = x;
                opAND(0x10);
                if (flgZ) {
                    a = x;
                    myMapper->writeCPU(0x0628, y);
                    myMapper->writeCPU(0x00D2, a);
                }
                else {
                    myMapper->writeCPU(0x0092, 0x02);
                    if (!(myMapper->readCPU(0x00E1) & 0x80)) {
                        opDEC(0x0092, 1);
                    }
                    a = myMapper->readCPU(0x0608 + y);
                    opAND(0x0F);
                    if (a != myMapper->readCPU(0x0092)) {
                        x = 0x18;
                        if (myMapper->readCPU(0x0608 + x) != 0x07) {
                            goto L_001B57;
                        }
                        y = 0x19;
                    }
                L_001B57:
                    a = myMapper->readCPU(0x0608 + y);
                    myMapper->writeCPU(0x0628, y);
                    opAND(0x03);
                    myMapper->writeCPU(0x00D2, a);
                }
                myMapper->writeCPU(0x006A, 0x00);
                myMapper->writeCPU(0x00D1, 0x01);
            }
        }
    }
    do {
        do {
            popAddress();
            return;
        L_001B6A:
            a = myMapper->readCPU(0x00DB);
            y = a;
        } while (a != myMapper->readCPU(0x0628));
        opINC(0x006A, 1);
    } while (myMapper->readCPU(0x0607 + y) != 0x0F);
    myMapper->writeCPU(0x00D1, 0x00);
    myMapper->writeCPU(0x006A, 0x09);
    popAddress();
}

void game::SUB_001B84() {
    if (myMapper->readCPU(0x00EF) != 0) {
        goto L_001BB7;
    }
    if (myMapper->readCPU(0x0009) < myMapper->readCPU(0x00BE)) {
        y = myMapper->readCPU(0x00DB);
        if (myMapper->readCPU(0x0607 + y) == 0x05) {
            a = myMapper->readCPU(0x0608 + y);
            if (a < 0x03) {
                opAND(0x0F);
                myMapper->writeCPU(0x006F, a);
                a = myMapper->readCPU(0x0007);
                opAND(0x03);
                if (flgZ) {
                    a = myMapper->readCPU(0x0009);
                }
                x = 0x00;
                opAND(0x02);
                if (flgZ) {
                    goto L_001BB1;
                }
                opINX(1);
            L_001BB1:
                myMapper->writeCPU(0x006E, x);
                myMapper->writeCPU(0x00EF, 0x01);
            }
        }
    }
L_001BB7:
    popAddress();
}

void game::SUB_001E4D() {
    a = myMapper->readCPU(0x00B2);
    setLoadFlag(a);
    if (flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00B3);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_001EEA();
        return;
    }
    opINC(0x00B3, 1);
    myMapper->writeCPU(0x0002, 0x17);
    pushAddress(0x001E5F);
    SUB_001F11();
    if (poppedEntry.value != 0x001E5F) return;
    myMapper->writeCPU(0x0090, 0x6F);
    myMapper->writeCPU(0x0093, 0x02);
    y = 0x00;
    do {
        myMapper->writeCPU(0x0092, 0x00);
        do {
            myMapper->writeCPU(0x0091, myMapper->readCPU(0xDF21 + y));
            opINY(1);
            a = myMapper->readCPU(0xDF21 + y);
            opINY(1);
            x = a;
            do {
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0090));
                a = 0x00;
                opINX(1);
                myMapper->writeCPU(0x0200 + x, a);
                opINX(1);
                myMapper->writeCPU(0x0200 + x, a);
                opINX(1);
                myMapper->writeCPU(0x0200 + x, a);
                opINX(1);
                opINC(0x0092, 1);
                opDEC(0x0091, 1);
            } while (!flgZ);
        } while (myMapper->readCPU(0x0092) < 0x08);
        myMapper->writeCPU(0x0090, 0x77);
        opDEC(0x0093, 1);
    } while (!flgZ);
    x = 0x02;
    a = myMapper->readCPU(0x00DC);
    opCMP(a, 0x06);
    if (!flgZ) {
        goto L_001EAC;
    }
    opDEX(1);
L_001EAC:
    myMapper->writeCPU(0x0090, x);
    x = a;
    y = myMapper->readCPU(0xDF2A + x);
    x = 0x00;
    myMapper->writeCPU(0x0091, 0x6F);
    pushAddress(0x001EB8);
    SUB_001EBB();
    if (poppedEntry.value != 0x001EB8) return;
    SUB_001EBB();
    return;
}

void game::SUB_001EBB() {
    myMapper->writeCPU(0x0093, 0x02);
    myMapper->writeCPU(0x0092, 0x7F);
    do {
        myMapper->writeCPU(0x02F0 + x, myMapper->readCPU(0x0091));
        opINX(1);
        myMapper->writeCPU(0x02F0 + x, myMapper->readCPU(0xDF34 + y));
        opINY(1);
        opINX(1);
        myMapper->writeCPU(0x02F0 + x, myMapper->readCPU(0x0090));
        opINX(1);
        myMapper->writeCPU(0x02F0 + x, myMapper->readCPU(0x0092));
        opINX(1);
        myMapper->writeCPU(0x0092, 0x87);
        opDEC(0x0093, 1);
    } while (!flgZ);
    a = 0x77;
    myMapper->writeCPU(0x0091, a);
    popAddress();
}

void game::SUB_001EEA() {
    opDEC(0x0002, 1);
    if (!flgZ) {
        goto L_001F10;
    }
    myMapper->writeCPU(0x0002, 0x17);
    x = 0x00;
    do {
        y = myMapper->readCPU(0x02F0 + x);
        opDEY(2);
        opCMP(y, 0x57);
        if (!flgC) {
            goto L_001F0A;
        }
        a = y;
        myMapper->writeCPU(0x02F0 + x, a);
        opINX(4);
        opCMP(x, 0x10);
    } while (!flgC);
    popAddress();
    return;
L_001F0A:
    a = 0x00;
    myMapper->writeCPU(0x00B2, a);
    myMapper->writeCPU(0x00B3, a);
L_001F10:
    popAddress();
}

void game::SUB_001F11() {
    y = 0x00;
    a = 0xF8;
    do {
        myMapper->writeCPU(0x02E0 + y, a);
        opINY(4);
        opCMP(y, 0x20);
    } while (!flgZ);
    popAddress();
}

void game::SUB_001F54() {
    a = 0x00;
    x = 0x1C;
    do {
        myMapper->writeCPU(0x0063 + x, a);
        opDEX(1);
    } while (!flgN);
    x = 0x0D;
    do {
        myMapper->writeCPU(0x00E2 + x, a);
        opDEX(1);
    } while (!flgN);
    x = 0x20;
    do {
        myMapper->writeCPU(0x0700 + x, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x007A, 0x04);
    myMapper->writeCPU(0x0074, 0x0E);
    myMapper->writeCPU(0x006A, 0x18);
    popAddress();
}

void game::SUB_001F7B() {
    myMapper->writeCPU(0x00E0, 0xB8);
    myMapper->writeCPU(0x00E1, 0x70);
    myMapper->writeCPU(0x0074, 0x00);
    popAddress();
}

void game::SUB_001F88() {
    opINC(0x0730, 1);
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xDF9A));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xDF9B));
    a = myMapper->readCPU(0x0070);
    SUB_003760();
    return;
}

void game::SUB_001FB0() {
    pushAddress(0x001FB0);
    SUB_001FB6();
    if (poppedEntry.value != 0x001FB0) return;
    SUB_002003();
    return;
}

void game::SUB_001FB6() {
    pushAddress(0x001FB6);
    SUB_001FD7();
    if (poppedEntry.value != 0x001FB6) return;
    pushAddress(0x001FB9);
    SUB_00200C();
    if (poppedEntry.value != 0x001FB9) return;
    SUB_00202F();
    return;
}

void game::SUB_001FBF() {
    pushAddress(0x001FBF);
    SUB_001FB6();
    if (poppedEntry.value != 0x001FBF) return;
    SUB_001FFA();
    return;
}

void game::SUB_001FC5() {
    pushAddress(0x001FC5);
    SUB_001FCB();
    if (poppedEntry.value != 0x001FC5) return;
    SUB_002003();
    return;
}

void game::SUB_001FCB() {
    pushAddress(0x001FCB);
    SUB_001FD7();
    if (poppedEntry.value != 0x001FCB) return;
    SUB_002053();
    return;
}

void game::SUB_001FD1() {
    pushAddress(0x001FD1);
    SUB_001FCB();
    if (poppedEntry.value != 0x001FD1) return;
    SUB_001FFA();
    return;
}

void game::SUB_001FD7() {
    if (myMapper->readCPU(0x00C0) & 0x80) {
        SUB_001FE0();
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x0071, a);
    SUB_001FDF();
    return;
}

void game::SUB_001FDF() {
    popAddress();
}

void game::SUB_001FE0() {
    a = myMapper->readCPU(0x0071);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x00C2);
        opLSR_A(2);
        myMapper->writeCPU(0x0071, a);
    }
    opDEC(0x0071, 1);
    if (!flgZ) {
        SUB_002002();
        return;
    }
    a = 0x20;
    opBIT(myMapper->readCPU(0x00C0));
    if (flgZ) {
        goto L_001FF7;
    }
    SUB_001FFA();
    return;
L_001FF7:
    SUB_002003();
    return;
}

void game::SUB_001FFA() {
    a = 0x14;
    opCMP(a, myMapper->readCPU(0x00E1));
    if (flgZ) {
        SUB_002002();
        return;
    }
    opDEC(0x00E1, 1);
    SUB_002002();
    return;
}

void game::SUB_002002() {
    popAddress();
}

void game::SUB_002003() {
    a = 0xCC;
    opCMP(a, myMapper->readCPU(0x00E1));
    if (flgZ) {
        SUB_002002();
        return;
    }
    opINC(0x00E1, 1);
    popAddress();
}

void game::SUB_00200C() {
    myMapper->writeCPU(0x007A, 0x00);
    if (myMapper->readCPU(0x0072) != 0) {
        goto L_00201E;
    }
    opCMP(myMapper->readCPU(0x0070), 0x09);
    if (flgZ) {
        goto L_00202B;
    }
    a = 0x08;
    do {
        myMapper->writeCPU(0x0072, a);
    L_00201E:
        opDEC(0x0072, 1);
        if (!flgZ) {
            goto L_002024;
        }
        opINC(0x0074, 1);
    L_002024:
        a = myMapper->readCPU(0x0074);
        opAND(0x03);
        myMapper->writeCPU(0x0074, a);
        popAddress();
        return;
    L_00202B:
        a = 0x04;
        setLoadFlag(a);
    } while (!flgZ);
    SUB_00202F();
    return;
}

void game::SUB_00202F() {
    if (myMapper->readCPU(0x007E) == 0) {
        goto L_002039;
    }
    pushAddress(0x002033);
    SUB_002491();
    if (poppedEntry.value != 0x002033) return;
    SUB_00209F();
    return;
L_002039:
    a = myMapper->readCPU(0x0005);
    opAND(0xC0);
    if (!flgZ) {
        goto L_002042;
    }
    x = a;
    setLoadFlag(x);
    if (flgZ) {
        goto L_002044;
    }
L_002042:
    x = 0x04;
L_002044:
    myMapper->writeCPU(0x0090, x);
    a = myMapper->readCPU(0x0007);
    opAND(0x03);
    opORA(myMapper->readCPU(0x0090));
    x = a;
    a = myMapper->readCPU(0xE7B1 + x);
    myMapper->writeCPU(0x0070, a);
    popAddress();
}

void game::SUB_002053() {
    pushAddress(0x002053);
    SUB_0031BB();
    if (poppedEntry.value != 0x002053) return;
    opINC(0x00E9, 1);
    a = myMapper->readCPU(0x00E9);
    opAND(0x04);
    if (!flgZ) {
        myMapper->writeCPU(0x00E9, 0x00);
        if (myMapper->readCPU(0x0065) != 0) {
            opINC(0x0063, 1);
            if (!flgZ) {
                goto L_002079;
            }
        }
        opINC(0x0065, 1);
        myMapper->writeCPU(0x0063, 0x00);
        myMapper->writeCPU(0x0074, 0x04);
        a = 0x02;
        pushAddress(0x002076);
        SUB_003A88();
        if (poppedEntry.value != 0x002076) return;
    L_002079:
        x = myMapper->readCPU(0x0063);
        myMapper->writeCPU(0x00E0, myMapper->readCPU(0xE796 + x));
        myMapper->writeCPU(0x007A, myMapper->readCPU(0xE7A2 + x));
        a = 0x01;
        opEOR(myMapper->readCPU(0x0074));
        myMapper->writeCPU(0x0074, a);
        a = myMapper->readCPU(0x00E0);
        opCMP(a, 0xB8);
        if (!flgZ) {
            goto L_002099;
        }
        a = 0x00;
        myMapper->writeCPU(0x0074, a);
        myMapper->writeCPU(0x0065, a);
        myMapper->writeCPU(0x0070, a);
    }
L_002099:
    popAddress();
}

void game::SUB_00209A() {
    a = 0x12;
    myMapper->writeCPU(0x00C2, a);
    popAddress();
}

void game::SUB_00209F() {
    pushAddress(0x00209F);
    SUB_0020A5();
    if (poppedEntry.value != 0x00209F) return;
    myMapper->writeCPU(0x00C2, a);
    SUB_0020A4();
    return;
}

void game::SUB_0020A4() {
    popAddress();
}

void game::SUB_0020A5() {
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0078, a);
    myMapper->writeCPU(0x0079, a);
    popAddress();
}

void game::SUB_0020AC() {
    pushAddress(0x0020AC);
    SUB_0020A5();
    if (poppedEntry.value != 0x0020AC) return;
    a = 0x06;
    opORA(myMapper->readCPU(0x007C));
    myMapper->writeCPU(0x0074, a);
    if (myMapper->readCPU(0x00EE) != 0) {
        SUB_0020DC();
        return;
    }
    opCMP(myMapper->readCPU(0x00E0), 0xB8);
    if (!flgZ) {
        goto L_0020D0;
    }
    x = 0x00;
    myMapper->writeCPU(0x00ED, x);
    myMapper->writeCPU(0x007D, x);
    opINX(1);
    myMapper->writeCPU(0x00EE, x);
    pushAddress(0x0020C8);
    SUB_0031EF();
    if (poppedEntry.value != 0x0020C8) return;
    a = 0x03;
    SUB_003A88();
    return;
L_0020D0:
    opINC(0x00E0, 1);
    SUB_0020D2();
    return;
}

void game::SUB_0020D2() {
    if (myMapper->readCPU(0x007C) != 0) {
        goto L_0020D9;
    }
    SUB_002003();
    return;
L_0020D9:
    SUB_001FFA();
    return;
}

void game::SUB_0020DC() {
    opINC(0x0069, 1);
    a = myMapper->readCPU(0x0069);
    opAND(0x04);
    if (flgZ) {
        SUB_0020A4();
        return;
    }
    myMapper->writeCPU(0x0069, 0x00);
    opINC(0x007D, 1);
    x = myMapper->readCPU(0x007D);
    myMapper->writeCPU(0x007A, myMapper->readCPU(0xE77D + x));
    a = myMapper->readCPU(0xE764 + x);
    myMapper->writeCPU(0x00E0, a);
    if (a != 0xB8) {
        goto L_002111;
    }
    if (myMapper->readCPU(0x0700) != 0) {
        goto L_002104;
    }
    a = 0x04;
    pushAddress(0x002101);
    SUB_003A88();
    if (poppedEntry.value != 0x002101) return;
L_002104:
    opCMP(myMapper->readCPU(0x00ED), 0x01);
    if (flgZ) {
        goto L_002128;
    }
    if (!flgN) {
        goto L_002111;
    }
    do {
        opINC(0x00ED, 1);
        pushAddress(0x00210E);
        SUB_00209A();
        if (poppedEntry.value != 0x00210E) return;
    L_002111:
        pushAddress(0x002111);
        SUB_0020D2();
        if (poppedEntry.value != 0x002111) return;
        pushAddress(0x002114);
        SUB_0020D2();
        if (poppedEntry.value != 0x002114) return;
        a = myMapper->readCPU(0x007D);
        opCMP(a, 0x18);
        if (!flgZ) {
            SUB_0020A4();
            return;
        }
        a = 0x00;
        myMapper->writeCPU(0x00EE, a);
        myMapper->writeCPU(0x0065, a);
        myMapper->writeCPU(0x0070, a);
        SUB_00209A();
        return;
    L_002128:
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0709, a);
    } while (flgZ);
    SUB_00212F();
    return;
}

void game::SUB_00212F() {
    pushAddress(0x00212F);
    SUB_0020A5();
    if (poppedEntry.value != 0x00212F) return;
    pushAddress(0x002132);
    SUB_0031EF();
    if (poppedEntry.value != 0x002132) return;
    if (myMapper->readCPU(0x00E8) != 0) {
        SUB_00215D();
        return;
    }
    a = 0x05;
    pushAddress(0x00213B);
    SUB_003A88();
    if (poppedEntry.value != 0x00213B) return;
    x = 0x00;
    myMapper->writeCPU(0x007B, x);
    opINX(1);
    myMapper->writeCPU(0x00E8, x);
    myMapper->writeCPU(0x00EA, 0x01);
    SUB_002149();
    return;
}

void game::SUB_002149() {
    myMapper->writeCPU(0x00E0, 0xC7);
    a = 0x04;
    myMapper->writeCPU(0x0074, a);
    myMapper->writeCPU(0x007A, a);
    a = myMapper->readCPU(0x070D);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00218C();
        return;
    }
    SUB_002158();
    return;
}

void game::SUB_002158() {
    popAddress();
}

void game::SUB_002159() {
    a = 0xC0;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002176();
        return;
    }
    SUB_00215D();
    return;
}

void game::SUB_00215D() {
    opINC(0x007B, 1);
    a = 0x7F;
    opAND(myMapper->readCPU(0x007B));
    opCMP(a, 0x20);
    if (flgN) {
        SUB_002149();
        return;
    }
    opLSR_A(3);
    opAND(0x03);
    opORA(0x08);
    myMapper->writeCPU(0x0074, a);
    opAND(0x01);
    if (flgZ) {
        SUB_002159();
        return;
    }
    a = 0xBE;
    SUB_002176();
    return;
}

void game::SUB_002176() {
    myMapper->writeCPU(0x00E0, a);
    if (myMapper->readCPU(0x070D) != 0) {
        SUB_00218C();
        return;
    }
    a = myMapper->readCPU(0x0005);
    opAND(0xC0);
    if (flgZ) {
        SUB_002158();
        return;
    }
    pushAddress(0x002183);
    SUB_00209A();
    if (poppedEntry.value != 0x002183) return;
    a = 0x01;
    myMapper->writeCPU(0x070D, a);
    popAddress();
}

void game::SUB_00218C() {
    a = myMapper->readCPU(0x00C1);
    opCMP(a, 0x02);
    if (!flgZ) {
        SUB_002158();
        return;
    }
    myMapper->writeCPU(0x00E0, 0xB8);
    a = 0x00;
    myMapper->writeCPU(0x070D, a);
    myMapper->writeCPU(0x0074, a);
    myMapper->writeCPU(0x0070, a);
    myMapper->writeCPU(0x00E8, a);
    myMapper->writeCPU(0x00EA, a);
    myMapper->writeCPU(0x007A, a);
    popAddress();
}

void game::SUB_0021A6() {
    pushAddress(0x0021A6);
    SUB_0031EF();
    if (poppedEntry.value != 0x0021A6) return;
    if (myMapper->readCPU(0x0066) != 0) {
    }
    else {
        pushAddress(0x0021B0);
        SUB_00200C();
        if (poppedEntry.value != 0x0021B0) return;
        a = myMapper->readCPU(0x0072);
        setLoadFlag(a);
        if (!flgZ) {
            SUB_002158();
            return;
        }
        a = myMapper->readCPU(0x0067);
        setLoadFlag(a);
        if (flgZ) {
            myMapper->writeCPU(0x0075, a);
            opINC(0x0067, 1);
            a = 0x70;
            flgC = true;
            opSBC(myMapper->readCPU(0x00E1));
            if (flgZ) {
                myMapper->writeCPU(0x0068, a);
                if (flgZ) {
                    goto L_0021E9;
                }
            }
            myMapper->writeCPU(0x0076, a);
            if (a >= 0x61) {
                a = 0x00;
                flgC = true;
                opSBC(myMapper->readCPU(0x0076));
                myMapper->writeCPU(0x0076, a);
                a = 0x02;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_0021DD;
                }
            }
            a = 0x01;
        L_0021DD:
            myMapper->writeCPU(0x0068, a);
            a = myMapper->readCPU(0x0076);
            opLSR_A(4);
            x = a;
            opINX(1);
            myMapper->writeCPU(0x0076, x);
        }
    L_0021E9:
        opDEC(0x00E0, 1);
        opINC(0x0075, 1);
        a = myMapper->readCPU(0x0075);
        if (a < 0x14) {
            y = myMapper->readCPU(0x0076);
            do {
                a = myMapper->readCPU(0x00E1);
                opCMP(a, 0x70);
                if (flgZ) {
                    goto L_002241;
                }
                a = myMapper->readCPU(0x0068);
                opCMP(a, 0x01);
                if (flgZ) {
                    goto L_002205;
                }
                opDEC(0x00E1, 2);
            L_002205:
                opINC(0x00E1, 1);
                opDEY(1);
            } while (!flgZ);
            popAddress();
            return;
        }
        opCMP(a, 0x15);
        if (flgZ) {
            x = 0x00;
            myMapper->writeCPU(0x0075, x);
            opINX(1);
            myMapper->writeCPU(0x0066, x);
            myMapper->writeCPU(0x00BA, x);
            myMapper->writeCPU(0x0074, 0x0C);
            a = 0x04;
            myMapper->writeCPU(0x007A, a);
        }
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x00EC) == 0) {
        a = 0x10;
        opCMP(a, myMapper->readCPU(0x0075));
        if (!flgZ) {
            if (!flgN) {
                goto L_002259;
            }
            if (myMapper->readCPU(0x006D) == 0x0E) {
                goto L_00225C;
            }
            a = myMapper->readCPU(0x0032);
            opCMP(a, 0x01);
            if (flgZ) {
                opINC(0x006D, 1);
                a = myMapper->readCPU(0x0074);
                opEOR(0x01);
                myMapper->writeCPU(0x0074, a);
            }
        L_002241:
            popAddress();
            return;
        }
        myMapper->writeCPU(0x00B2, 0x01);
        a = 0x11;
        pushAddress(0x002248);
        SUB_003A88();
        if (poppedEntry.value != 0x002248) return;
        a = 0x52;
        pushAddress(0x00224D);
        SUB_003A88();
        if (poppedEntry.value != 0x00224D) return;
        a = 0x93;
        pushAddress(0x002252);
        SUB_003A88();
        if (poppedEntry.value != 0x002252) return;
        a = 0x0D;
        myMapper->writeCPU(0x0074, a);
    L_002259:
        opINC(0x0075, 1);
        popAddress();
        return;
    L_00225C:
        x = 0x00;
        myMapper->writeCPU(0x0075, x);
        opINX(1);
        myMapper->writeCPU(0x00EC, x);
    }
    opINC(0x0075, 1);
    opCMP(myMapper->readCPU(0x0075), 0x80);
    if (flgZ) {
        goto L_002276;
    }
    a = myMapper->readCPU(0x00DC);
    opCMP(a, 0x04);
    if (flgZ) {
        goto L_002287;
    }
    opCMP(a, 0x09);
    if (flgZ) {
        goto L_002287;
    }
    popAddress();
    return;
L_002276:
    a = 0x00;
    myMapper->writeCPU(0x0075, a);
    myMapper->writeCPU(0x00EC, a);
    myMapper->writeCPU(0x0066, a);
    myMapper->writeCPU(0x0067, a);
    myMapper->writeCPU(0x007E, a);
    myMapper->writeCPU(0x006D, a);
    SUB_00247D();
    return;
L_002287:
    myMapper->writeCPU(0x0074, 0x0F);
    x = 0x3F;
    do {
        a = myMapper->readCPU(0xE724 + x);
        myMapper->writeCPU(0x0224 + x, a);
        opDEX(1);
    } while (!flgN);
    SUB_002296();
    return;
}

void game::SUB_002296() {
    popAddress();
}

void game::SUB_002297() {
    a = myMapper->readCPU(0x0070);
    opCMP(a, 0x08);
    if (!flgN) {
        SUB_002296();
        return;
    }
    a = myMapper->readCPU(0x0709);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002296();
        return;
    }
    if (myMapper->readCPU(0x00E0) >= 0xAE) {
        goto L_0022AF;
    }
    a = 0x01;
    do {
        myMapper->writeCPU(0x00E3, a);
        goto L_0022B3;
    L_0022AF:
        a = 0x00;
        setLoadFlag(a);
    } while (flgZ);
L_0022B3:
    opCMP(myMapper->readCPU(0x006A), 0x07);
    if (!flgZ) {
        if (!flgZ) {
            goto L_0022F5;
        }
    }
    a = myMapper->readCPU(0x00D2);
    opASL_A(1);
    opORA(myMapper->readCPU(0x00E3));
    opASL_A(2);
    x = a;
    a = myMapper->readCPU(0x00E1);
    if (a < myMapper->readCPU(0xE70C + x)) {
        goto L_0022F5;
    }
    opINX(1);
    if (a >= myMapper->readCPU(0xE70C + x)) {
        goto L_0022E5;
    }
    a = 0x01;
    do {
        myMapper->writeCPU(0x007C, a);
        a = 0x09;
        pushAddress(0x0022D6);
        SUB_003A88();
        if (poppedEntry.value != 0x0022D6) return;
        pushAddress(0x0022D9);
        SUB_002481();
        if (poppedEntry.value != 0x0022D9) return;
        myMapper->writeCPU(0x00EE, 0x00);
        pushAddress(0x0022E0);
        SUB_00209F();
        if (poppedEntry.value != 0x0022E0) return;
        if (!flgZ) {
            goto L_0022F5;
        }
    L_0022E5:
        opINX(1);
        if (a < myMapper->readCPU(0xE70C + x)) {
            goto L_0022F5;
        }
        opINX(1);
        if (a >= myMapper->readCPU(0xE70C + x)) {
            goto L_0022F5;
        }
        a = 0x00;
        setLoadFlag(a);
    } while (flgZ);
L_0022F5:
    a = myMapper->readCPU(0x0077);
    if (a < 0x1A) {
        SUB_002337();
        return;
    }
    if (a >= 0x1E) {
        SUB_002337();
        return;
    }
    a = myMapper->readCPU(0x0267);
    flgC = false;
    opADC(0x04);
    flgC = true;
    opSBC(myMapper->readCPU(0x00E1));
    if (!flgC) {
        SUB_002337();
        return;
    }
    if (a >= 0x19) {
        SUB_002337();
        return;
    }
    x = myMapper->readCPU(0x0073);
    a = myMapper->readCPU(0xE321 + x);
    pushAddress(0x002313);
    SUB_002325();
    if (poppedEntry.value != 0x002313) return;
    a = 0x07;
    pushAddress(0x002318);
    SUB_003A88();
    if (poppedEntry.value != 0x002318) return;
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x00EF, a);
    if (flgZ) {
        SUB_002337();
        return;
    }
    //NOP
    SUB_002325();
    return;
}

void game::SUB_002325() {
    myMapper->writeCPU(0x008A, a);
    myMapper->writeCPU(0x008B, 0x00);
    SUB_0039AF();
    return;
}

void game::SUB_00232E() {
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, 0x00);
    SUB_0039AF();
    return;
}

void game::SUB_002337() {
    x = 0x00;
    myMapper->writeCPU(0x00E5, x);
    SUB_00233B();
    return;
}

void game::SUB_00233B() {
    if (myMapper->readCPU(0x0607 + x) == 0x0E) {
        SUB_00236E();
        return;
    }
    SUB_002342();
    return;
}

void game::SUB_002342() {
    opINC(0x00E5, 1);
    SUB_002344();
    return;
}

void game::SUB_002344() {
    a = x;
    flgC = false;
    opADC(0x06);
    x = a;
    if (x != 0x1E) {
        SUB_00233B();
        return;
    }
    if (0x05 == myMapper->readCPU(0x00E5)) {
        if (myMapper->readCPU(0x0078) == 0) {
            goto L_002360;
        }
        a = 0x30;
        pushAddress(0x002359);
        SUB_00232E();
        if (poppedEntry.value != 0x002359) return;
        myMapper->writeCPU(0x0078, 0x00);
    L_002360:
        if (myMapper->readCPU(0x0079) == 0) {
            goto L_00236D;
        }
        a = 0x30;
        pushAddress(0x002366);
        SUB_00232E();
        if (poppedEntry.value != 0x002366) return;
        myMapper->writeCPU(0x0079, 0x00);
    }
L_00236D:
    popAddress();
}

void game::SUB_00236E() {
    a = myMapper->readCPU(0x0608 + x);
    if (a == 0x11) {
        SUB_0023CB();
        return;
    }
    if (a == 0x12) {
        SUB_0023DB();
        return;
    }
    if (a >= 0x07) {
        SUB_002342();
        return;
    }
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xE38D + y));
    opINY(1);
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xE38D + y));
    indirectJump(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8));
}

void game::SUB_00239B() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x49) {
        SUB_002344();
        return;
    }
    if (a < 0x70) {
        SUB_0023AB();
        return;
    }
    opCMP(a, 0x97);
    if (!flgC) {
        SUB_0023BB();
        return;
    }
    if (flgC) {
        SUB_002344();
        return;
    }
    SUB_0023AB();
    return;
}

void game::SUB_0023AB() {
    opCMP(myMapper->readCPU(0x00E0), 0xB8);
    if (!flgZ) {
        SUB_0023C5();
        return;
    }
    a = 0x01;
    SUB_0023B3();
    return;
}

void game::SUB_0023B3() {
    myMapper->writeCPU(0x007C, a);
    pushAddress(0x0023B5);
    SUB_002481();
    if (poppedEntry.value != 0x0023B5) return;
    SUB_00209F();
    return;
}

void game::SUB_0023BB() {
    opCMP(myMapper->readCPU(0x00E0), 0xB8);
    if (!flgZ) {
        SUB_0023C5();
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_0023B3();
        return;
    }
    SUB_0023C5();
    return;
}

void game::SUB_0023C5() {
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0078, a);
    if (!flgZ) {
        SUB_0023E9();
        return;
    }
    SUB_0023CB();
    return;
}

void game::SUB_0023CB() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x11) {
        SUB_0023E9();
        return;
    }
    if (a < 0x30) {
        SUB_0023AB();
        return;
    }
    opCMP(a, 0x4F);
    if (!flgC) {
        SUB_0023BB();
        return;
    }
    if (flgC) {
        SUB_0023E9();
        return;
    }
    SUB_0023DB();
    return;
}

void game::SUB_0023DB() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x91) {
        SUB_0023E9();
        return;
    }
    if (a < 0xB0) {
        SUB_0023AB();
        return;
    }
    if (a < 0xCF) {
        SUB_0023BB();
        return;
    }
    SUB_0023E9();
    return;
}

void game::SUB_0023E9() {
    SUB_002344();
    return;
}

void game::SUB_0023EC() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x10) {
        SUB_0023E9();
        return;
    }
    if (a < 0x37) {
        SUB_002400();
        return;
    }
    if (a < 0x83) {
        SUB_00241A();
        return;
    }
    opCMP(a, 0xA5);
    if (!flgC) {
        SUB_002410();
        return;
    }
    if (flgC) {
        SUB_0023E9();
        return;
    }
    SUB_002400();
    return;
}

void game::SUB_002400() {
    opCMP(myMapper->readCPU(0x00E0), 0xB8);
    if (flgN) {
        SUB_00240A();
        return;
    }
    a = 0x01;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_0023B3();
        return;
    }
    SUB_00240A();
    return;
}

void game::SUB_00240A() {
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x0079, a);
    if (!flgZ) {
        SUB_0023E9();
        return;
    }
    SUB_002410();
    return;
}

void game::SUB_002410() {
    opCMP(myMapper->readCPU(0x00E0), 0xB8);
    if (flgN) {
        SUB_00240A();
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_0023B3();
        return;
    }
    SUB_00241A();
    return;
}

void game::SUB_00241A() {
    opCMP(myMapper->readCPU(0x00E0), 0xB8);
    if (!flgZ) {
        SUB_00240A();
        return;
    }
    pushAddress(0x002420);
    SUB_00209F();
    if (poppedEntry.value != 0x002420) return;
    myMapper->writeCPU(0x007B, 0x00);
    SUB_00248D();
    return;
}

void game::SUB_00242A() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x40) {
        SUB_0023E9();
        return;
    }
    if (a < 0x67) {
        SUB_002400();
        return;
    }
    if (a < 0xB3) {
        SUB_00241A();
        return;
    }
    opCMP(a, 0xD5);
    if (!flgC) {
        SUB_002410();
        return;
    }
    if (flgC) {
        SUB_0023E9();
        return;
    }
    SUB_00243E();
    return;
}

void game::SUB_00243E() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x2C) {
        SUB_00246A();
        return;
    }
    if (a >= 0x51) {
        SUB_00246A();
        return;
    }
    SUB_002448();
    return;
}

void game::SUB_002448() {
    a = x;
    myMapper->writeCPU(0x00E4, a);
    y = a;
    pushAddress(0x00244C);
    SUB_00089C();
    if (poppedEntry.value != 0x00244C) return;
    opINC(0x06F1, 1);
    x = myMapper->readCPU(0x0704);
    a = myMapper->readCPU(0xE46D + x);
    if (a != 0x10) {
        goto L_00245F;
    }
    opINC(0x0705, 1);
L_00245F:
    pushAddress(0x00245F);
    SUB_002325();
    if (poppedEntry.value != 0x00245F) return;
    a = 0x06;
    pushAddress(0x002464);
    SUB_003A88();
    if (poppedEntry.value != 0x002464) return;
    x = myMapper->readCPU(0x00E4);
    SUB_00246A();
    return;
}

void game::SUB_00246A() {
    SUB_002344();
    return;
}

void game::SUB_002471() {
    a = myMapper->readCPU(0x00E1);
    if (a < 0x94) {
        SUB_00246A();
        return;
    }
    opCMP(a, 0xB9);
    if (flgC) {
        SUB_00246A();
        return;
    }
    if (!flgC) {
        SUB_002448();
        return;
    }
    SUB_00247D();
    return;
}

void game::SUB_00247D() {
    a = 0x03;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002493();
        return;
    }
    SUB_002481();
    return;
}

void game::SUB_002481() {
    x = 0x00;
    myMapper->writeCPU(0x00EE, x);
    opINX(1);
    myMapper->writeCPU(0x0709, x);
    a = 0x07;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002493();
        return;
    }
    SUB_00248D();
    return;
}

void game::SUB_00248D() {
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002493();
        return;
    }
    SUB_002491();
    return;
}

void game::SUB_002491() {
    a = 0x09;
    SUB_002493();
    return;
}

void game::SUB_002493() {
    myMapper->writeCPU(0x0070, a);
    popAddress();
}

void game::SUB_002496() {
    y = 0x00;
    do {
        myMapper->writeCPU(0x0080 + y, myMapper->readCPU(0xE702 + y));
        opINY(1);
        opCMP(y, 0x0A);
    } while (!flgZ);
    if (!flgZ) {
    }
    y = 0x00;
    if (myMapper->readCPU(0x00EA) == 0) {
        goto L_0024CC;
    }
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xE6D4 + y));
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xE6D4 + y));
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xE6D4 + y));
        opINY(1);
        a = myMapper->readCPU(0xE6D4 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x00E1));
        myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opCMP(y, 0x10);
    } while (!flgZ);
    if (flgZ) {
        goto L_0024F0;
    }
L_0024CC:
    a = myMapper->readCPU(0x0074);
    if (a != 0x01) {
        if (a == 0x03) {
            goto L_0024D9;
        }
        a = y;
        setLoadFlag(a);
        if (flgZ) {
            goto L_0024DB;
        }
    L_0024D9:
        a = 0xFF;
    }
L_0024DB:
    myMapper->writeCPU(0x0092, a);
    if (myMapper->readCPU(0x0706) == 0) {
        if (myMapper->readCPU(0x0705) != 0) {
            goto L_0024F2;
        }
        do {
            a = 0xF4;
            do {
                myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, a);
                opINY(1);
                opCMP(y, 0x10);
            } while (!flgZ);
        L_0024F0:
            if (flgZ) {
                goto L_002531;
            }
        L_0024F2:
            a = y;
            myMapper->writeCPU(0x070A, a);
        L_0024F6:
            opASL_A(1);
            x = a;
            myMapper->writeCPU(0x0090, myMapper->readCPU(0xE6E4 + x));
            myMapper->writeCPU(0x0091, myMapper->readCPU(0xE6E5 + x));
            do {
                a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
                flgC = false;
                opADC(myMapper->readCPU(0x00E0));
                myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, a);
                opINY(1);
                myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
                opINY(1);
                myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y));
                opINY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
                flgC = false;
                opADC(myMapper->readCPU(0x00E1));
                flgC = false;
                opADC(myMapper->readCPU(0x0092));
                myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, a);
                opINY(1);
                opCMP(y, 0x08);
            } while (!flgZ);
        } while (flgZ);
    }
    opINC(0x070A, 1);
    a = myMapper->readCPU(0x070A);
    opCMP(a, 0x03);
    if (!flgZ) {
        goto L_0024F6;
    }
    if (flgZ) {
        goto L_0024F2;
    }
L_002531:
    a = myMapper->readCPU(0x0074);
    opCMP(a, 0x0E);
    if (!flgZ) {
        if (!flgN) {
            goto L_002588;
        }
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x008C, myMapper->readCPU(0xEA29 + y));
        myMapper->writeCPU(0x008D, myMapper->readCPU(0xEA2A + y));
        x = 0x00;
        y = 0x00;
        do {
            a = myMapper->readCPU(0xEA85 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x00E0));
            myMapper->writeCPU(0x0224 + x, a);
            opINX(1);
            a = myMapper->readCPU(myMapper->readCPU(0x008C) + (myMapper->readCPU((0x008C + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            myMapper->writeCPU(0x0224 + x, a);
            if (flgZ) {
                goto L_002573;
            }
        L_00255A:
            opINX(1);
            opINY(1);
            myMapper->writeCPU(0x0224 + x, myMapper->readCPU(myMapper->readCPU(0x008C) + (myMapper->readCPU((0x008C + 1) & 0x00ff) << 8) + y));
            opINX(1);
            a = myMapper->readCPU(0xEA85 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x00E1));
            myMapper->writeCPU(0x0224 + x, a);
            opINX(1);
            opINY(1);
            opCMP(y, 0x20);
        } while (!flgZ);
        if (flgZ) {
            goto L_002588;
        }
    L_002573:
        opDEX(1);
        myMapper->writeCPU(0x0224 + x, 0x00);
        opINX(1);
        goto L_00255A;
    }
    y = 0x00;
    a = 0xF4;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0082) + (myMapper->readCPU((0x0082 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
    } while (y != 0x40);
L_002588:
    a = myMapper->readCPU(0x007A);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x00E0);
        flgC = false;
        opADC(0x1E);
    }
    else {
        if (a == 0x04) {
            goto L_0025D3;
        }
        a = 0xD6;
    }
    myMapper->writeCPU(0x0092, a);
    myMapper->writeCPU(0x0091, myMapper->readCPU(0x00E1));
    a = myMapper->readCPU(0x007A);
    opASL_A(4);
    opAND(0x3F);
    x = a;
    y = 0x00;
    do {
        a = myMapper->readCPU(0xEA45 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0092));
        myMapper->writeCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opINX(1);
        myMapper->writeCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xEA45 + x));
        opINY(1);
        opINX(1);
        myMapper->writeCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xEA45 + x));
        opINY(1);
        opINX(1);
        a = myMapper->readCPU(0xEA45 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0091));
        myMapper->writeCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opINX(1);
        opCMP(y, 0x10);
    } while (!flgZ);
    if (!flgZ) {
    L_0025D3:
        y = 0x00;
        a = 0xF4;
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            opCMP(y, 0x10);
        } while (!flgZ);
    }
    if (myMapper->readCPU(0x00D0) == 0) {
        a = myMapper->readCPU(0x006A);
        opCMP(a, 0x09);
        if (flgZ) {
            goto L_00263D;
        }
        if (flgC) {
            goto L_00263D;
        }
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x008E, myMapper->readCPU(0xEC45 + y));
        myMapper->writeCPU(0x008F, myMapper->readCPU(0xEC46 + y));
        x = myMapper->readCPU(0x006A);
        opCMP(myMapper->readCPU(0x00D2), 0x01);
        if (flgZ) {
            goto L_002624;
        }
        if (!flgN) {
            goto L_002629;
        }
        a = 0x00;
        do {
            do {
                myMapper->writeCPU(0x0092, a);
                y = 0x00;
                while (true) {
                    a = myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y);
                    if (a == 0xFF) {
                        goto L_00262E;
                    }
                    myMapper->writeCPU(myMapper->readCPU(0x0086) + (myMapper->readCPU((0x0086 + 1) & 0x00ff) << 8) + y, a);
                    opINY(1);
                    myMapper->writeCPU(myMapper->readCPU(0x0086) + (myMapper->readCPU((0x0086 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y));
                    opINY(1);
                    myMapper->writeCPU(myMapper->readCPU(0x0086) + (myMapper->readCPU((0x0086 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y));
                    opINY(1);
                    a = myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y);
                    flgC = false;
                    opADC(myMapper->readCPU(0x0092));
                    myMapper->writeCPU(myMapper->readCPU(0x0086) + (myMapper->readCPU((0x0086 + 1) & 0x00ff) << 8) + y, a);
                    opINY(1);
                }
            L_002624:
                a = myMapper->readCPU(0xEC57 + x);
                setLoadFlag(a);
            } while (!flgZ);
        L_002629:
            a = myMapper->readCPU(0xEC60 + x);
            setLoadFlag(a);
        } while (!flgZ);
        do {
        L_00262E:
            a = 0xF4;
            while (true) {
                opCMP(y, 0x30);
                if (flgZ) {
                    goto L_002641;
                }
                myMapper->writeCPU(myMapper->readCPU(0x0086) + (myMapper->readCPU((0x0086 + 1) & 0x00ff) << 8) + y, a);
                opINY(4);
            }
        L_00263D:
            y = 0x00;
            setLoadFlag(y);
        } while (flgZ);
    L_002641:
        if (myMapper->readCPU(0x00EF) != 0) {
            goto L_00265F;
        }
        a = myMapper->readCPU(0x0730);
        opAND(0x07);
        x = a;
        myMapper->writeCPU(0x0073, myMapper->readCPU(0xE657 + x));
        a = 0x00;
        myMapper->writeCPU(0x006B, a);
        myMapper->writeCPU(0x0077, a);
    }
    popAddress();
    return;
L_00265F:
    opINC(0x006B, 1);
    a = myMapper->readCPU(0x006B);
    opAND(0x01);
    if (!flgZ) {
        opINC(0x0077, 1);
    }
    opCMP(myMapper->readCPU(0x0077), 0x20);
    if (flgN) {
        goto L_002674;
    }
    myMapper->writeCPU(0x00EF, 0x00);
    popAddress();
    return;
L_002674:
    x = myMapper->readCPU(0x006F);
    myMapper->writeCPU(0x0092, myMapper->readCPU(0xE7AE + x));
    a = myMapper->readCPU(0x0077);
    if (a < 0x10) {
        goto L_00268B;
    }
    if (a < 0x1A) {
        goto L_00268F;
    }
    a = 0x04;
    setLoadFlag(a);
    do {
        do {
            myMapper->writeCPU(0x0093, a);
            if (!flgZ) {
                goto L_002693;
            }
        L_00268B:
            a = 0x01;
            setLoadFlag(a);
        } while (!flgZ);
    L_00268F:
        a = 0x03;
        setLoadFlag(a);
    } while (!flgZ);
L_002693:
    a = myMapper->readCPU(0x0077);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x008E, myMapper->readCPU(0xE7B9 + x));
    myMapper->writeCPU(0x008F, myMapper->readCPU(0xE7BA + x));
    if (myMapper->readCPU(0x006E) != 0) {
        goto L_0026C5;
    }
    do {
        y = 0x00;
        do {
            myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y));
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y);
            opORA(myMapper->readCPU(0x0073));
            myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x008E) + (myMapper->readCPU((0x008E + 1) & 0x00ff) << 8) + y);
            flgC = false;
            opADC(myMapper->readCPU(0x0092));
            myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            opDEC(0x0093, 1);
        } while (!flgZ);
        popAddress();
        return;
    L_0026C5:
        a = 0x18;
        flgC = false;
        opADC(myMapper->readCPU(0x008E));
        myMapper->writeCPU(0x008E, a);
        a = 0x01;
        opADC(myMapper->readCPU(0x008F));
        myMapper->writeCPU(0x008F, a);
    } while (!flgZ);
    opDEC(0x00FC + x, 1);
    pushAddress(0x0026D7);
    flgB = true;
    //NOP
    SUB_002D72();
    return;
}

void game::SUB_002D72() {
    x = myMapper->readCPU(0x006C);
    opDEX(1);
    if (!flgZ) {
        if (!flgN) {
            goto L_002D9F;
        }
        pushAddress(0x002D79);
        SUB_002EFF();
        if (poppedEntry.value != 0x002D79) return;
        pushAddress(0x002D7C);
        SUB_003813();
        if (poppedEntry.value != 0x002D7C) return;
        pushAddress(0x002D7F);
        SUB_002EE4();
        if (poppedEntry.value != 0x002D7F) return;
        pushAddress(0x002D82);
        SUB_002EF7();
        if (poppedEntry.value != 0x002D82) return;
        pushAddress(0x002D85);
        SUB_002EA3();
        if (poppedEntry.value != 0x002D85) return;
        pushAddress(0x002D88);
        SUB_002EB4();
        if (poppedEntry.value != 0x002D88) return;
        pushAddress(0x002D8B);
        SUB_002EC2();
        if (poppedEntry.value != 0x002D8B) return;
        pushAddress(0x002D8E);
        SUB_002EC8();
        if (poppedEntry.value != 0x002D8E) return;
        a = 0x00;
        myMapper->writeCPU(0x00EB, a);
        myMapper->writeCPU(0x007F, a);
        myMapper->writeCPU(0x0064, a);
        opINC(0x006C, 1);
        pushAddress(0x002D9B);
        SUB_00374C();
        if (poppedEntry.value != 0x002D9B) return;
        popAddress();
        return;
    L_002D9F:
        SUB_002E21();
        return;
    }
    opINC(0x00EB, 1);
    if (flgZ) {
        SUB_002E10();
        return;
    }
    a = myMapper->readCPU(0x0064);
    opCMP(a, 0x0A);
    if (!flgZ) {
        SUB_002E0D();
        return;
    }
    a = myMapper->readCPU(0x0005);
    opAND(0x10);
    if (!flgZ) {
        SUB_002DF7();
        return;
    }
    a = myMapper->readCPU(0x0005);
    opAND(0x20);
    if (flgZ) {
        SUB_002E0C();
        return;
    }
    opINC(0x0731, 1);
    SUB_002DBB();
    return;
}

void game::SUB_002DBB() {
    if (myMapper->readCPU(0x0731) >= 0x03) {
        goto L_002DF0;
    }
    do {
        myMapper->writeCPU(0x00EB, 0x00);
        a = myMapper->readCPU(0xF10D);
        x = myMapper->readCPU(0xF10E);
        pushAddress(0x002DCC);
        SUB_002F3D();
        if (poppedEntry.value != 0x002DCC) return;
        x = myMapper->readCPU(0x0731);
        opDEX(1);
        if (!flgZ) {
            if (!flgN) {
                goto L_002DE7;
            }
            a = myMapper->readCPU(0xF11E);
            x = myMapper->readCPU(0xF11F);
            setLoadFlag(x);
            if (!flgZ) {
                goto L_002DED;
            }
        }
        a = myMapper->readCPU(0xF125);
        x = myMapper->readCPU(0xF126);
        setLoadFlag(x);
        if (!flgZ) {
            goto L_002DED;
        }
    L_002DE7:
        a = myMapper->readCPU(0xF12C);
        x = myMapper->readCPU(0xF12D);
    L_002DED:
        SUB_002F3D();
        return;
    L_002DF0:
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0731, a);
    } while (flgZ);
    SUB_002DF7();
    return;
}

void game::SUB_002DF7() {
    a = 0x14;
    pushAddress(0x002DF9);
    SUB_003A88();
    if (poppedEntry.value != 0x002DF9) return;
    a = 0x55;
    pushAddress(0x002DFE);
    SUB_003A88();
    if (poppedEntry.value != 0x002DFE) return;
    a = 0x96;
    pushAddress(0x002E03);
    SUB_003A88();
    if (poppedEntry.value != 0x002E03) return;
    opINC(0x006C, 1);
    a = 0x00;
    myMapper->writeCPU(0x00EB, a);
    SUB_002E0C();
    return;
}

void game::SUB_002E0C() {
    popAddress();
}

void game::SUB_002E0D() {
    opINC(0x0064, 1);
    popAddress();
}

void game::SUB_002E10() {
    pushAddress(0x002E10);
    SUB_002EE4();
    if (poppedEntry.value != 0x002E10) return;
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x0064, a);
    myMapper->writeCPU(0x006C, a);
    myMapper->writeCPU(0x0200, 0xF0);
    SUB_003576();
    return;
}

void game::SUB_002E21() {
    opINC(0x00EB, 1);
    if (!flgZ) {
        a = myMapper->readCPU(0x00EB);
        opAND(0x0F);
        if (flgZ) {
            goto L_002E30;
        }
        opCMP(a, 0x08);
        if (flgZ) {
            goto L_002E3C;
        }
        popAddress();
        return;
    L_002E30:
        y = 0x47;
        do {
            a = myMapper->readCPU(0xF173 + y);
            myMapper->writeCPU(0x0244 + y, a);
            opDEY(1);
        } while (!flgN);
        popAddress();
        return;
    L_002E3C:
        x = myMapper->readCPU(0x0731);
        y = myMapper->readCPU(0xEE4E + x);
        x = 0x17;
        a = 0x00;
        do {
            myMapper->writeCPU(0x0244 + y, a);
            opINY(1);
            opDEX(1);
        } while (!flgN);
        popAddress();
        return;
    }
    pushAddress(0x002E51);
    SUB_002EE4();
    if (poppedEntry.value != 0x002E51) return;
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x0064, a);
    myMapper->writeCPU(0x006C, a);
    SUB_0038AC();
    return;
}

void game::SUB_002E5D() {
    myMapper->writeCPU(0x006C, 0x00);
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xEE70));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xEE71));
    a = myMapper->readCPU(0x007F);
    SUB_003760();
    return;
}

void game::SUB_002E80() {
    myMapper->writeCPU(0x0056, 0x01);
    myMapper->writeCPU(0x0053, 0x92);
    pushAddress(0x002E88);
    SUB_002EFF();
    if (poppedEntry.value != 0x002E88) return;
    pushAddress(0x002E8B);
    SUB_002EF7();
    if (poppedEntry.value != 0x002E8B) return;
    opINC(0x007F, 1);
    SUB_00374C();
    return;
}

void game::SUB_002E93() {
    opINC(0x0056, 2);
    a = myMapper->readCPU(0x0056);
    opCMP(a, 0xEF);
    if (!flgZ) {
        goto L_002EA2;
    }
    pushAddress(0x002E9D);
    SUB_002EE4();
    if (poppedEntry.value != 0x002E9D) return;
    opINC(0x007F, 1);
L_002EA2:
    popAddress();
}

void game::SUB_002EA3() {
    pushAddress(0x002EA3);
    SUB_002F37();
    if (poppedEntry.value != 0x002EA3) return;
    y = 0x1F;
    do {
        a = myMapper->readCPU(0xF133 + y);
        myMapper->writeCPU(0x0204 + y, a);
        opDEY(1);
    } while (!flgN);
    opINC(0x007F, 1);
    popAddress();
}

void game::SUB_002EB4() {
    y = 0x1F;
    do {
        a = myMapper->readCPU(0xF153 + y);
        myMapper->writeCPU(0x0224 + y, a);
        opDEY(1);
    } while (!flgN);
    opINC(0x007F, 1);
    popAddress();
}

void game::SUB_002EC2() {
    pushAddress(0x002EC2);
    SUB_002DBB();
    if (poppedEntry.value != 0x002EC2) return;
    opINC(0x007F, 1);
    popAddress();
}

void game::SUB_002EC8() {
    y = 0x47;
    do {
        a = myMapper->readCPU(0xF173 + y);
        myMapper->writeCPU(0x0244 + y, a);
        opDEY(1);
    } while (!flgN);
    opINC(0x007F, 1);
    popAddress();
}

void game::SUB_002ED6() {
    x = 0x00;
    myMapper->writeCPU(0x007F, x);
    myMapper->writeCPU(0x00EB, x);
    opINX(1);
    myMapper->writeCPU(0x006C, x);
    opINC(0x0000, 1);
    SUB_003497();
    return;
}

void game::SUB_002EE4() {
    myMapper->writeCPU(0x0053, 0x90);
    myMapper->writeCPU(0x0054, 0x1E);
    a = 0x00;
    myMapper->writeCPU(0x0056, a);
    popAddress();
}

void game::SUB_002EF1() {
    pushAddress(0x002EF1);
    SUB_002F3D();
    if (poppedEntry.value != 0x002EF1) return;
    SUB_002F64();
    return;
}

void game::SUB_002EF7() {
    a = myMapper->readCPU(0xF098);
    x = myMapper->readCPU(0xF099);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002F3D();
        return;
    }
    SUB_002EFF();
    return;
}

void game::SUB_002EFF() {
    a = myMapper->readCPU(0xEF75);
    x = myMapper->readCPU(0xEF76);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002EF1();
        return;
    }
    SUB_002F07();
    return;
}

void game::SUB_002F07() {
    a = myMapper->readCPU(0xEF9A);
    x = myMapper->readCPU(0xEF9B);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002EF1();
        return;
    }
    SUB_002F0F();
    return;
}

void game::SUB_002F0F() {
    a = myMapper->readCPU(0xEFD4);
    x = myMapper->readCPU(0xEFD5);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002EF1();
        return;
    }
    SUB_002F17();
    return;
}

void game::SUB_002F17() {
    a = myMapper->readCPU(0xEFE9);
    x = myMapper->readCPU(0xEFEA);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002EF1();
        return;
    }
    SUB_002F1F();
    return;
}

void game::SUB_002F1F() {
    a = myMapper->readCPU(0xEFBF);
    x = myMapper->readCPU(0xEFC0);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002EF1();
        return;
    }
    SUB_002F27();
    return;
}

void game::SUB_002F27() {
    a = myMapper->readCPU(0xF00E);
    x = myMapper->readCPU(0xF00F);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002F3D();
        return;
    }
    SUB_002F2F();
    return;
}

void game::SUB_002F2F() {
    a = myMapper->readCPU(0xF053);
    x = myMapper->readCPU(0xF054);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_002F3D();
        return;
    }
    SUB_002F37();
    return;
}

void game::SUB_002F37() {
    a = myMapper->readCPU(0xF0FB);
    x = myMapper->readCPU(0xF0FC);
    SUB_002F3D();
    return;
}

void game::SUB_002F3D() {
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0081, x);
    y = 0x00;
    do {
        a = myMapper->readCPU(0x2002);
        x = myMapper->readCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x2006, myMapper->readCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x2006, x);
        opINY(1);
    L_002F53:
        a = myMapper->readCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y);
        opINY(1);
    } while (a == 0xAA);
    opCMP(a, 0xBB);
    if (flgZ) {
        goto L_002F63;
    }
    myMapper->writeCPU(0x2007, a);
    if (!flgZ) {
        goto L_002F53;
    }
L_002F63:
    popAddress();
}

void game::SUB_002F64() {
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    popAddress();
}

void game::SUB_0031BB() {
    opCMP(myMapper->readCPU(0x0000), 0x08);
    if (flgZ) {
        SUB_0031EF();
        return;
    }
    if (myMapper->readCPU(0x0705) != 0) {
        if (myMapper->readCPU(0x0706) != 0) {
            SUB_003202();
            return;
        }
        a = myMapper->readCPU(0x0005);
        opAND(0xC0);
        if (!flgZ) {
            opCMP(0xAC, myMapper->readCPU(0x00E0));
            if (flgN) {
                goto L_0031EE;
            }
            x = 0x00;
            myMapper->writeCPU(0x0707, x);
            myMapper->writeCPU(0x0708, x);
            opINX(1);
            myMapper->writeCPU(0x0706, x);
            a = 0x08;
            pushAddress(0x0031E5);
            SUB_003A88();
            if (poppedEntry.value != 0x0031E5) return;
            a = 0x04;
            setLoadFlag(a);
            myMapper->writeCPU(0x0070, a);
            if (!flgZ) {
                SUB_003233();
                return;
            }
        }
    }
L_0031EE:
    popAddress();
}

void game::SUB_0031EF() {
    if (myMapper->readCPU(0x0706) == 0) {
        goto L_0031F9;
    }
    a = 0x00;
    pushAddress(0x0031F6);
    SUB_003A88();
    if (poppedEntry.value != 0x0031F6) return;
L_0031F9:
    a = 0x00;
    myMapper->writeCPU(0x0705, a);
    myMapper->writeCPU(0x0706, a);
    popAddress();
}

void game::SUB_003202() {
    opINC(0x00E9, 1);
    a = myMapper->readCPU(0x00E9);
    opAND(0x04);
    if (!flgZ) {
        myMapper->writeCPU(0x00E9, 0x00);
        pushAddress(0x00320E);
        SUB_003236();
        if (poppedEntry.value != 0x00320E) return;
    }
    opINC(0x0707, 1);
    opINC(0x0708, 1);
    opCMP(0x1E, myMapper->readCPU(0x0708));
    if (!flgZ) {
        if (myMapper->readCPU(0x0707) == 0) {
            goto L_003230;
        }
        a = myMapper->readCPU(0x0005);
        opAND(0xC0);
        if (flgZ) {
            SUB_003233();
            return;
        }
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0708, a);
        if (flgZ) {
            SUB_003233();
            return;
        }
    }
L_003230:
    pushAddress(0x003230);
    SUB_0031EF();
    if (poppedEntry.value != 0x003230) return;
    SUB_003233();
    return;
}

void game::SUB_003233() {
    opPLA();
    opPLA();
    popAddress();
}

void game::SUB_003236() {
    a = myMapper->readCPU(0x0074);
    opEOR(0x01);
    opORA(0x04);
    myMapper->writeCPU(0x0074, a);
    if (a == 0x04) {
        goto L_003246;
    }
    opDEC(0x00E0, 2);
L_003246:
    opINC(0x00E0, 1);
    popAddress();
}

void game::reset() {
    pushAddress(0x003249);
    SUB_00374C();
    if (poppedEntry.value != 0x003249) return;
    flgI = true;
    flgD = false;
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    s = 0xFF;
    x = 0x10;
    do {
        opCMP(x, myMapper->readCPU(0x07EF + x));
        if (!flgZ) {
            goto L_003264;
        }
        opDEX(1);
    } while (!flgZ);
L_003264:
    myMapper->writeCPU(0x0082, x);
    y = 0xEF;
    myMapper->writeCPU(0x0081, 0x07);
    a = 0x00;
    myMapper->writeCPU(0x0080, a);
    do {
        do {
        L_003270:
            myMapper->writeCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y, a);
            opDEY(1);
        } while (!flgZ);
        opDEC(0x0081, 1);
        if (flgN) {
            goto L_003283;
        }
    } while (!flgZ);
    x = myMapper->readCPU(0x0082);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_003281;
    }
    y = 0x56;
    setLoadFlag(y);
L_003281:
    if (!flgZ) {
        goto L_003270;
    }
L_003283:
    myMapper->writeCPU(0x0000, a);
    x = 0x10;
    do {
        myMapper->writeCPU(0x07EF + x, x);
        opDEX(1);
    } while (!flgZ);
    pushAddress(0x00328E);
    SUB_0037E8();
    if (poppedEntry.value != 0x00328E) return;
}

void game::nmi() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x2002);
    if (myMapper->readCPU(0x0004) == 0) {
        opINC(0x0004, 1);
        a = myMapper->readCPU(0x0054);
        opAND(0xE7);
        myMapper->writeCPU(0x2001, a);
        x = myMapper->readCPU(0x0000);
        if (x >= 0x05) {
            if (myMapper->readCPU(0x000E) == 0) {
                goto L_0032E0;
            }
            if (myMapper->readCPU(0x00BC) == 0) {
                if (myMapper->readCPU(0x0070) == 0x08) {
                    goto L_0032C3;
                }
                if (myMapper->readCPU(0x00C1) >= 0x03) {
                    goto L_0032E0;
                }
            L_0032C3:
                if (x >= 0x08) {
                    goto L_0032EF;
                }
                myMapper->writeCPU(0x00BC, 0x01);
                a = 0x17;
                pushAddress(0x0032CD);
                SUB_003A88();
                if (poppedEntry.value != 0x0032CD) return;
                a = 0x07;
                pushAddress(0x0032D2);
                SUB_00376E();
                if (poppedEntry.value != 0x0032D2) return;
                goto L_0032EF;
            }
            opCMP(myMapper->readCPU(0x0000), 0x06);
            if (flgC) {
                goto L_0032E4;
            }
            if (!flgC) {
                goto L_003302;
            }
        L_0032E0:
            if (myMapper->readCPU(0x00BC) != 0) {
            L_0032E4:
                a = 0x00;
                myMapper->writeCPU(0x00BC, a);
                myMapper->writeCPU(0x000E, a);
                a = 0x08;
                pushAddress(0x0032EC);
                SUB_00376E();
                if (poppedEntry.value != 0x0032EC) return;
            }
        }
    L_0032EF:
        myMapper->writeCPU(0x2003, 0x00);
        myMapper->writeCPU(0x4014, 0x02);
        pushAddress(0x0032F9);
        SUB_0033FC();
        if (poppedEntry.value != 0x0032F9) return;
        opCMP(myMapper->readCPU(0x0000), 0x05);
        if (!flgC) {
        L_003302:
            myMapper->writeCPU(0x2001, myMapper->readCPU(0x0054));
        }
        opDEC(0x0004, 1);
        a = myMapper->readCPU(0x2002);
        myMapper->writeCPU(0x2006, 0x20);
        myMapper->writeCPU(0x2006, 0x20);
    }
    pushAddress(0x003316);
    SUB_0038DB();
    if (poppedEntry.value != 0x003316) return;
    a = myMapper->readCPU(0x0053);
    opAND(0x7F);
    myMapper->writeCPU(0x2000, a);
    pushAddress(0x003320);
    SUB_003B3A();
    if (poppedEntry.value != 0x003320) return;
    if (myMapper->readCPU(0x0004) == 0) {
        opINC(0x0004, 1);
        pushAddress(0x003329);
        SUB_00383E();
        if (poppedEntry.value != 0x003329) return;
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0053));
        a = myMapper->readCPU(0x00BC);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_003338;
        }
        pushAddress(0x003335);
        SUB_003348();
        if (poppedEntry.value != 0x003335) return;
    L_003338:
        opDEC(0x0004, 1);
    }
    else {
        a = myMapper->readCPU(0x0053);
        myMapper->writeCPU(0x2000, a);
    }
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
}

void game::SUB_003348() {
    opINC(0x0009, 1);
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xF359));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xF35A));
    a = myMapper->readCPU(0x0000);
    SUB_003760();
    return;
}

void game::SUB_00336D() {
    popAddress();
}

void game::SUB_00336E() {
    x = myMapper->readCPU(0x0001);
    setLoadFlag(x);
    if (flgZ) {
        SUB_00336D();
        return;
    }
    SUB_0036DE();
    return;
}

void game::SUB_00337A() {
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00336D();
        return;
    }
    pushAddress(0x00337E);
    SUB_000699();
    if (poppedEntry.value != 0x00337E) return;
    SUB_0038F7();
    return;
}

void game::SUB_003384() {
    x = myMapper->readCPU(0x0001);
    opDEX(1);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0633);
    opCMP(a, 0x14);
    if (!flgC) {
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x0090, myMapper->readCPU(0xDBB8 + y));
        myMapper->writeCPU(0x0091, myMapper->readCPU(0xDBB9 + y));
        myMapper->writeCPU(0x00DA, 0x01);
        pushAddress(0x0033A1);
        SUB_001073();
        if (poppedEntry.value != 0x0033A1) return;
        a = myMapper->readCPU(0x0633);
        opINC(0x0633, 1);
        opCMP(a, 0x03);
        if (flgZ) {
            goto L_0033D1;
        }
        opCMP(a, 0x09);
        if (flgZ) {
            goto L_0033D1;
        }
        opCMP(a, 0x0E);
        if (flgZ) {
            goto L_0033D1;
        }
        opCMP(a, 0x10);
        if (flgZ) {
            goto L_0033D1;
        }
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x00DC);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0033C3;
    }
    y = a;
    a = myMapper->readCPU(0xDDCB + y);
L_0033C3:
    myMapper->writeCPU(0x0636, a);
    myMapper->writeCPU(0x0099, 0x21);
    a = 0x73;
    myMapper->writeCPU(0x0098, a);
    SUB_0034AF();
    return;
L_0033D1:
    y = myMapper->readCPU(0x0634);
    x = myMapper->readCPU(0xDD8B + y);
    y = myMapper->readCPU(0x0635);
    myMapper->writeCPU(0x0090, myMapper->readCPU(0xDD8F + x));
    opINX(1);
    do {
        a = myMapper->readCPU(0xDD8F + x);
        myMapper->writeCPU(0x0264 + y, a);
        opINX(1);
        opINY(1);
        opDEC(0x0090, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0635, y);
    opINC(0x0634, 1);
    popAddress();
}

void game::SUB_0033F3() {
    pushAddress(0x0033F3);
    SUB_002496();
    if (poppedEntry.value != 0x0033F3) return;
    pushAddress(0x0033F6);
    SUB_001F88();
    if (poppedEntry.value != 0x0033F6) return;
    SUB_001E4D();
    return;
}

void game::SUB_0033FC() {
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xF459));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xF45A));
    a = myMapper->readCPU(0x0000);
    pushAddress(0x003408);
    SUB_003760();
    if (poppedEntry.value != 0x003408) return;
    a = myMapper->readCPU(0x0000);
    if (a != 0x01) {
        opCMP(a, 0x03);
        if (!flgZ) {
            goto L_003416;
        }
    }
    popAddress();
    return;
L_003416:
    a = myMapper->readCPU(0x0003);
    opAND(0x40);
    if (flgZ) {
        SUB_003456();
        return;
    }
    if (myMapper->readCPU(0x00CF) == 0) {
        opCMP(myMapper->readCPU(0x0000), 0x05);
        if (!flgC) {
            goto L_003451;
        }
        pushAddress(0x003426);
        SUB_00397C();
        if (poppedEntry.value != 0x003426) return;
        do {
            a = myMapper->readCPU(0x2002);
            opAND(0x40);
        } while (!flgZ);
        myMapper->writeCPU(0x2001, 0x1E);
        a = myMapper->readCPU(0x2002);
        myMapper->writeCPU(0x2006, 0x20);
        myMapper->writeCPU(0x2006, 0x00);
        do {
            opINC(0x00D3, 1);
            if (myMapper->readCPU(0x00D3) >= 0xFF) {
                goto L_003451;
            }
            a = myMapper->readCPU(0x2002);
            opAND(0x40);
        } while (flgZ);
    }
L_003451:
    myMapper->writeCPU(0x00D3, 0x00);
    SUB_003455();
    return;
}

void game::SUB_003455() {
    popAddress();
}

void game::SUB_003456() {
    SUB_003899();
    return;
}

void game::SUB_00346D() {
    x = myMapper->readCPU(0x0001);
    opDEX(1);
    if (flgZ) {
        goto L_00348A;
    }
    if (!flgN) {
        goto L_003494;
    }
    pushAddress(0x003474);
    SUB_0036CA();
    if (poppedEntry.value != 0x003474) return;
    pushAddress(0x003477);
    SUB_003813();
    if (poppedEntry.value != 0x003477) return;
    pushAddress(0x00347A);
    SUB_001F54();
    if (poppedEntry.value != 0x00347A) return;
    pushAddress(0x00347D);
    SUB_000699();
    if (poppedEntry.value != 0x00347D) return;
    myMapper->writeCPU(0x0002, 0x10);
    pushAddress(0x003484);
    SUB_00374C();
    if (poppedEntry.value != 0x003484) return;
    SUB_0034AF();
    return;
L_00348A:
    opDEC(0x0002, 1);
    if (!flgZ) {
        SUB_003455();
        return;
    }
    pushAddress(0x00348E);
    SUB_0037FB();
    if (poppedEntry.value != 0x00348E) return;
    SUB_0034AF();
    return;
L_003494:
    SUB_002E5D();
    return;
}

void game::SUB_003497() {
    SUB_002D72();
    return;
}

void game::SUB_00349A() {
    x = myMapper->readCPU(0x0001);
    setLoadFlag(x);
    if (flgZ) {
        goto L_0034A1;
    }
    SUB_000010();
    return;
L_0034A1:
    pushAddress(0x0034A1);
    SUB_000699();
    if (poppedEntry.value != 0x0034A1) return;
    a = 0x04;
    myMapper->writeCPU(0x0000, a);
    SUB_0034C6();
    return;
}

void game::SUB_0034AB() {
    a = 0x20;
    SUB_0034AD();
    return;
}

void game::SUB_0034AD() {
    myMapper->writeCPU(0x0002, a);
    SUB_0034AF();
    return;
}

void game::SUB_0034AF() {
    opINC(0x0001, 1);
    popAddress();
}

void game::SUB_0034B2() {
    pushAddress(0x0034B2);
    SUB_003576();
    if (poppedEntry.value != 0x0034B2) return;
    opPLA();
    opPLA();
    popAddress();
}

void game::SUB_0034B8() {
    x = myMapper->readCPU(0x0001);
    setLoadFlag(x);
    if (flgZ) {
        goto L_0034BF;
    }
    SUB_0034B2();
    return;
L_0034BF:
    a = 0x50;
    myMapper->writeCPU(0x0002, a);
    SUB_0034AF();
    return;
}

void game::SUB_0034C6() {
    x = myMapper->readCPU(0x0001);
    opDEX(1);
    if (flgN) {
        SUB_003583();
        return;
    }
    if (!flgZ) {
        opDEX(1);
        if (!flgZ) {
            goto L_00352A;
        }
        a = myMapper->readCPU(0x00BB);
        if (a >= myMapper->readCPU(0x0636)) {
            flgC = false;
            opADC(0x3C);
        }
        y = a;
        a = myMapper->readCPU(0xDDD5 + y);
        x = a;
        opAND(0xF0);
        if (flgZ) {
            myMapper->writeCPU(0x0637, x);
            opINC(0x00BB, 1);
            opINY(1);
        }
        x = 0x01;
        a = myMapper->readCPU(0x0637);
        opLSR_A(1);
        if (flgC) {
            x = 0x20;
        }
        opLSR_A(1);
        if (!flgC) {
            a = x;
            x = 0x98;
            pushAddress(0x0034FC);
            SUB_0037B7();
            if (poppedEntry.value != 0x0034FC) return;
        }
        else {
            a = x;
            x = 0x98;
            pushAddress(0x003505);
            SUB_0037C1();
            if (poppedEntry.value != 0x003505) return;
        }
        myMapper->writeCPU(0x0081, myMapper->readCPU(0x0099));
        a = myMapper->readCPU(0x0098);
        myMapper->writeCPU(0x0080, a);
        pushAddress(0x003510);
        SUB_0038E9();
        if (poppedEntry.value != 0x003510) return;
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xDDD5 + y));
        opINC(0x00BB, 1);
        a = myMapper->readCPU(0x00BB);
        opCMP(a, 0x3C);
        if (!flgC) {
            popAddress();
            return;
        }
        a = 0x90;
        SUB_0034AD();
        return;
    }
    SUB_00002A();
    return;
L_00352A:
    opDEC(0x0002, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    pushAddress(0x00352F);
    SUB_003813();
    if (poppedEntry.value != 0x00352F) return;
    myMapper->writeCPU(0x0053, 0x88);
    myMapper->writeCPU(0x0056, 0x00);
    pushAddress(0x00353A);
    SUB_003919();
    if (poppedEntry.value != 0x00353A) return;
    pushAddress(0x00353D);
    SUB_0000A8();
    if (poppedEntry.value != 0x00353D) return;
    pushAddress(0x003540);
    SUB_00374C();
    if (poppedEntry.value != 0x003540) return;
    myMapper->writeCPU(0x000E, 0x00);
    pushAddress(0x003547);
    SUB_00062E();
    if (poppedEntry.value != 0x003547) return;
    pushAddress(0x00354A);
    SUB_001F54();
    if (poppedEntry.value != 0x00354A) return;
    pushAddress(0x00354D);
    SUB_001F7B();
    if (poppedEntry.value != 0x00354D) return;
    pushAddress(0x003550);
    SUB_00008C();
    if (poppedEntry.value != 0x003550) return;
    pushAddress(0x003553);
    SUB_000076();
    if (poppedEntry.value != 0x003553) return;
    myMapper->writeCPU(0x00CF, 0xFF);
    a = myMapper->readCPU(0x0003);
    opAND(0x40);
    if (!flgZ) {
        goto L_003568;
    }
    y = 0x02;
    myMapper->writeCPU(0x0000, y);
    opDEY(1);
    myMapper->writeCPU(0x0001, y);
    popAddress();
    return;
L_003568:
    a = 0x4C;
    pushAddress(0x00356A);
    SUB_003A88();
    if (poppedEntry.value != 0x00356A) return;
    a = 0x8D;
    pushAddress(0x00356F);
    SUB_003A88();
    if (poppedEntry.value != 0x00356F) return;
    myMapper->writeCPU(0x000A, 0x01);
    SUB_003576();
    return;
}

void game::SUB_003576() {
    a = 0x20;
    SUB_003578();
    return;
}

void game::SUB_003578() {
    myMapper->writeCPU(0x0002, a);
    opINC(0x0000, 1);
    SUB_00357C();
    return;
}

void game::SUB_00357C() {
    a = 0x00;
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x0001, a);
    popAddress();
}

void game::SUB_003583() {
    myMapper->writeCPU(0x0053, 0x90);
    myMapper->writeCPU(0x0200, 0x00);
    pushAddress(0x00358C);
    SUB_003813();
    if (poppedEntry.value != 0x00358C) return;
    pushAddress(0x00358F);
    SUB_00374C();
    if (poppedEntry.value != 0x00358F) return;
    pushAddress(0x003592);
    SUB_002F17();
    if (poppedEntry.value != 0x003592) return;
    pushAddress(0x003595);
    SUB_002F2F();
    if (poppedEntry.value != 0x003595) return;
    SUB_0034AF();
    return;
}

void game::SUB_00359B() {
    opINC(0x00CF, 1);
    if (flgZ) {
        goto L_0035AE;
    }
    opDEC(0x00CF, 1);
    pushAddress(0x0035A1);
    SUB_000010();
    if (poppedEntry.value != 0x0035A1) return;
    a = 0x08;
    x = myMapper->readCPU(0x000B);
    setLoadFlag(x);
    if (!flgZ) {
        SUB_0035D4();
        return;
    }
    a = myMapper->readCPU(0x000A);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003576();
        return;
    }
L_0035AE:
    popAddress();
}

void game::SUB_0035AF() {
    a = 0x0E;
    pushAddress(0x0035B1);
    SUB_003A88();
    if (poppedEntry.value != 0x0035B1) return;
    a = 0x4F;
    pushAddress(0x0035B6);
    SUB_003A88();
    if (poppedEntry.value != 0x0035B6) return;
    a = 0x90;
    pushAddress(0x0035BB);
    SUB_003A88();
    if (poppedEntry.value != 0x0035BB) return;
    a = 0x04;
    pushAddress(0x0035C0);
    SUB_00376E();
    if (poppedEntry.value != 0x0035C0) return;
    pushAddress(0x0035C3);
    SUB_000519();
    if (poppedEntry.value != 0x0035C3) return;
    pushAddress(0x0035C6);
    SUB_001F11();
    if (poppedEntry.value != 0x0035C6) return;
    myMapper->writeCPU(0x0000, 0x06);
    a = 0x00;
    SUB_003578();
    return;
}

void game::SUB_0035D2() {
    a = 0x04;
    SUB_0035D4();
    return;
}

void game::SUB_0035D4() {
    myMapper->writeCPU(0x0000, a);
    myMapper->writeCPU(0x0002, 0x20);
    SUB_00357C();
    return;
}

void game::SUB_0035DD() {
    a = myMapper->readCPU(0x0005);
    opAND(0x10);
    if (!flgZ) {
        a = myMapper->readCPU(0x0003);
        opAND(0xBF);
        myMapper->writeCPU(0x0003, a);
        pushAddress(0x0035E9);
        SUB_0036CA();
        if (poppedEntry.value != 0x0035E9) return;
        SUB_003899();
        return;
    }
    a = myMapper->readCPU(0x0034);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0035F4;
    }
    popAddress();
    return;
L_0035F4:
    a = myMapper->readCPU(0x0003);
    opAND(0xBF);
    myMapper->writeCPU(0x0003, a);
    a = 0x00;
    SUB_0035D4();
    return;
}

void game::SUB_0035FF() {
    x = myMapper->readCPU(0x0001);
    opDEX(1);
    if (!flgN) {
        if (flgZ) {
            goto L_003631;
        }
        opDEX(1);
        if (flgZ) {
            SUB_00366C();
            return;
        }
        SUB_003699();
        return;
    }
    x = myMapper->readCPU(0x00BA);
    opDEX(1);
    if (!flgZ) {
        opDEX(1);
        if (flgZ) {
            goto L_003628;
        }
        popAddress();
        return;
    }
    y = 0x0C;
    pushAddress(0x003617);
    SUB_000CA5();
    if (poppedEntry.value != 0x003617) return;
    pushAddress(0x00361A);
    SUB_00002A();
    if (poppedEntry.value != 0x00361A) return;
    a = 0xF4;
    myMapper->writeCPU(0x0274, a);
    myMapper->writeCPU(0x0278, a);
    opINC(0x00BA, 1);
    popAddress();
    return;
L_003628:
    pushAddress(0x003628);
    SUB_002F0F();
    if (poppedEntry.value != 0x003628) return;
    opINC(0x00BA, 1);
    do {
        SUB_0034AF();
        return;
    L_003630:
        popAddress();
        return;
    L_003631:
        a = myMapper->readCPU(0x007E);
        setLoadFlag(a);
    } while (flgZ);
    if (myMapper->readCPU(0x00BA) == 0) {
        goto L_003630;
    }
    myMapper->writeCPU(0x00BA, 0x00);
    a = myMapper->readCPU(0x00DC);
    opCMP(a, 0x04);
    if (flgZ) {
        goto L_00364E;
    }
    flgC = false;
    opADC(0x07);
    opASL_A(1);
    y = a;
    pushAddress(0x003648);
    SUB_000CA5();
    if (poppedEntry.value != 0x003648) return;
    SUB_00002A();
    return;
L_00364E:
    y = 0x00;
    x = 0xB8;
    myMapper->writeCPU(0x0091, 0x08);
    pushAddress(0x003656);
    SUB_003659();
    if (poppedEntry.value != 0x003656) return;
    SUB_003659();
    return;
}

void game::SUB_003659() {
    do {
        myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0xCE1F + y));
        opINY(1);
        opINX(1);
        opDEC(0x0091, 1);
    } while (!flgZ);
    x = 0xD0;
    a = 0x10;
    myMapper->writeCPU(0x0091, a);
    popAddress();
}

void game::SUB_00366C() {
    a = myMapper->readCPU(0x00AA);
    opORA(myMapper->readCPU(0x00A9));
    if (flgZ) {
        goto L_003696;
    }
    myMapper->writeCPU(0x0095, 0xA9);
    myMapper->writeCPU(0x0096, 0x00);
    pushAddress(0x00367A);
    SUB_000762();
    if (poppedEntry.value != 0x00367A) return;
    pushAddress(0x00367D);
    SUB_000519();
    if (poppedEntry.value != 0x00367D) return;
    a = 0x01;
    pushAddress(0x003682);
    SUB_003A88();
    if (poppedEntry.value != 0x003682) return;
    myMapper->writeCPU(0x008A, 0x01);
    myMapper->writeCPU(0x008B, 0x00);
    pushAddress(0x00368D);
    SUB_0039AF();
    if (poppedEntry.value != 0x00368D) return;
    a = myMapper->readCPU(0x00AA);
    opORA(myMapper->readCPU(0x00A9));
    if (!flgZ) {
        SUB_0036C9();
        return;
    }
L_003696:
    SUB_0034AB();
    return;
}

void game::SUB_003699() {
    opDEC(0x0002, 1);
    if (!flgZ) {
        SUB_0036C9();
        return;
    }
    opINC(0x00DC, 1);
    if (myMapper->readCPU(0x00DC) == 0x0A) {
        opINC(0x00DD, 1);
        if (myMapper->readCPU(0x00DD) >= 0x03) {
            if (myMapper->readCPU(0x009C) >= 0x02) {
                goto L_0036B5;
            }
            opINC(0x009C, 1);
        }
    L_0036B5:
        myMapper->writeCPU(0x00DC, 0x00);
    }
    x = 0x00;
    myMapper->writeCPU(0x000B, x);
    a = myMapper->readCPU(0x0061);
    opINX(1);
    flgC = false;
    pushAddress(0x0036C1);
    SUB_0039DF();
    if (poppedEntry.value != 0x0036C1) return;
    myMapper->writeCPU(0x0061, a);
    SUB_0035D2();
    return;
}

void game::SUB_0036C9() {
    popAddress();
}

void game::SUB_0036CA() {
    a = 0x00;
    pushAddress(0x0036CC);
    SUB_003A88();
    if (poppedEntry.value != 0x0036CC) return;
    a = 0x40;
    pushAddress(0x0036D1);
    SUB_003A88();
    if (poppedEntry.value != 0x0036D1) return;
    a = 0x80;
    pushAddress(0x0036D6);
    SUB_003A88();
    if (poppedEntry.value != 0x0036D6) return;
    a = 0xC0;
    SUB_003A88();
    return;
}

void game::SUB_0036DE() {
    opDEC(0x062D, 1);
    if (!flgN) {
        goto L_0036FE;
    }
    y = myMapper->readCPU(0x062E);
    a = myMapper->readCPU(0xF71D + y);
    opCMP(a, 0xFF);
    if (flgZ) {
        goto L_003713;
    }
    myMapper->writeCPU(0x062D, a);
    opINY(1);
    a = myMapper->readCPU(0xF71D + y);
    myMapper->writeCPU(0x062F, a);
    myMapper->writeCPU(0x0630, a);
    opINY(1);
    myMapper->writeCPU(0x062E, y);
L_0036FE:
    a = myMapper->readCPU(0x0005);
    opAND(0x3F);
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0630);
    opORA(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0005, a);
    myMapper->writeCPU(0x0007, myMapper->readCPU(0x062F));
    SUB_000058();
    return;
L_003713:
    a = 0x00;
    myMapper->writeCPU(0x062E, a);
    myMapper->writeCPU(0x0054, a);
    SUB_0035D4();
    return;
}

void game::SUB_00374C() {
    myMapper->writeCPU(0x2003, 0x00);
    a = 0x02;
    myMapper->writeCPU(0x4014, a);
    popAddress();
}

void game::SUB_003760() {
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0082, myMapper->readCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0083, a);
    indirectJump(myMapper->readCPU(0x0082) + (myMapper->readCPU((0x0082 + 1) & 0x00ff) << 8));
}

void game::SUB_00376E() {
    x = 0xFF;
    opASL_A(1);
    y = a;
    if (!flgC) {
        goto L_003775;
    }
    opINX(1);
L_003775:
    myMapper->writeCPU(0x0084, myMapper->readCPU(0xFA26));
    myMapper->writeCPU(0x0085, myMapper->readCPU(0xFA27));
    myMapper->writeCPU(0x0082, myMapper->readCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0083, myMapper->readCPU(myMapper->readCPU(0x0084) + (myMapper->readCPU((0x0084 + 1) & 0x00ff) << 8) + y));
    a = x;
    goto L_003792;
L_003792:
    myMapper->writeCPU(0x0084, a);
    y = 0x00;
    do {
        myMapper->writeCPU(0x0080, myMapper->readCPU(myMapper->readCPU(0x0082) + (myMapper->readCPU((0x0082 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0082) + (myMapper->readCPU((0x0082 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0081, a);
        opINY(1);
        pushAddress(0x0037A0);
        SUB_0038E9();
        if (poppedEntry.value != 0x0037A0) return;
    L_0037A3:
        a = myMapper->readCPU(myMapper->readCPU(0x0082) + (myMapper->readCPU((0x0082 + 1) & 0x00ff) << 8) + y);
        opINY(1);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_0037B6;
        }
        opCMP(a, 0xFE);
    } while (flgZ);
    opAND(myMapper->readCPU(0x0084));
    myMapper->writeCPU(0x2007, a);
    goto L_0037A3;
L_0037B6:
    popAddress();
}

void game::SUB_0037B7() {
    flgC = false;
    opADC(myMapper->readCPU((0x0000 + x) & 0x00ff));
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (!flgC) {
        goto L_0037C0;
    }
    opINC((0x0001 + x) & 0x00ff, 1);
L_0037C0:
    popAddress();
}

void game::SUB_0037C1() {
    opEOR(0xFF);
    flgC = true;
    opADC(myMapper->readCPU((0x0000 + x) & 0x00ff));
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    if (flgC) {
        goto L_0037CC;
    }
    opDEC((0x0001 + x) & 0x00ff, 1);
L_0037CC:
    popAddress();
}

void game::SUB_0037DA() {
    a = 0xF4;
    x = 0x00;
    do {
        myMapper->writeCPU(0x0200 + x, a);
        opINX(4);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0037E8() {
    pushAddress(0x0037E8);
    SUB_003813();
    if (poppedEntry.value != 0x0037E8) return;
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x2003, a);
    myMapper->writeCPU(0x4014, 0x02);
    SUB_0037FB();
    return;
}

void game::SUB_0037FB() {
    myMapper->writeCPU(0x4015, 0x1F);
    myMapper->writeCPU(0x4017, 0xC0);
    a = 0x1E;
    myMapper->writeCPU(0x0054, a);
    myMapper->writeCPU(0x0051, a);
    a = 0x88;
    myMapper->writeCPU(0x0053, a);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_003813() {
    pushAddress(0x003813);
    SUB_00381A();
    if (poppedEntry.value != 0x003813) return;
    a = 0x2C;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00381C();
        return;
    }
    SUB_00381A();
    return;
}

void game::SUB_00381A() {
    a = 0x20;
    SUB_00381C();
    return;
}

void game::SUB_00381C() {
    myMapper->writeCPU(0x0081, a);
    y = 0x04;
    a = 0x00;
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0082, a);
    do {
        pushAddress(0x003826);
        SUB_003831();
        if (poppedEntry.value != 0x003826) return;
        opINC(0x0081, 1);
        opDEY(1);
    } while (!flgZ);
    SUB_0037DA();
    return;
}

void game::SUB_003831() {
    a = 0x00;
    SUB_003833();
    return;
}

void game::SUB_003833() {
    pushAddress(0x003833);
    SUB_0038E9();
    if (poppedEntry.value != 0x003833) return;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEC(0x0082, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00383E() {
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    y = 0x08;
    do {
        a = myMapper->readCPU(0x4016);
        myMapper->writeCPU(0x0087, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0087));
        opLSR_A(1);
        opROL_M(0x0084, 1);
        a = myMapper->readCPU(0x4017);
        myMapper->writeCPU(0x0087, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0087));
        opLSR_A(1);
        opROL_M(0x0085, 1);
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0005);
    opAND(0x10);
    opEOR(myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x000E, a);
    a = myMapper->readCPU(0x0003);
    opAND(0x20);
    if (flgZ) {
        SUB_00388A();
        return;
    }
    a = myMapper->readCPU(0x0003);
    opAND(0xF0);
    opCMP(a, 0xE0);
    if (flgZ) {
        SUB_00388E();
        return;
    }
    a = myMapper->readCPU(0x0084);
    pushAddress(0x00387A);
    SUB_003894();
    if (poppedEntry.value != 0x00387A) return;
    opINX(1);
    a = myMapper->readCPU((0x0084 + x) & 0x00ff);
    SUB_003880();
    return;
}

void game::SUB_003880() {
    y = a;
    opEOR(myMapper->readCPU((0x0007 + x) & 0x00ff));
    opAND(myMapper->readCPU((0x0084 + x) & 0x00ff));
    myMapper->writeCPU((0x0005 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0007 + x) & 0x00ff, y);
    popAddress();
}

void game::SUB_00388A() {
    a = 0xFF;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003890();
        return;
    }
    SUB_00388E();
    return;
}

void game::SUB_00388E() {
    a = 0x30;
    SUB_003890();
    return;
}

void game::SUB_003890() {
    opAND(myMapper->readCPU(0x0084));
    opORA(myMapper->readCPU(0x0085));
    SUB_003894();
    return;
}

void game::SUB_003894() {
    myMapper->writeCPU(0x0084, a);
    SUB_003880();
    return;
}

void game::SUB_003899() {
    a = myMapper->readCPU(0x0005);
    opAND(0x30);
    if (flgZ) {
        SUB_0038B5();
        return;
    }
    myMapper->writeCPU(0x0002, 0x00);
    x = myMapper->readCPU(0x0000);
    opDEX(1);
    if (!flgZ) {
        SUB_0038B6();
        return;
    }
    opAND(0x20);
    if (!flgZ) {
        SUB_0038B5();
        return;
    }
    SUB_0038AC();
    return;
}

void game::SUB_0038AC() {
    myMapper->writeCPU(0x0003, 0x40);
    a = 0x03;
    SUB_0035D4();
    return;
}

void game::SUB_0038B5() {
    popAddress();
}

void game::SUB_0038B6() {
    opAND(0x10);
    myMapper->writeCPU(0x000E, a);
    myMapper->writeCPU(0x0054, myMapper->readCPU(0x0051));
    pushAddress(0x0038BE);
    SUB_002D72();
    if (poppedEntry.value != 0x0038BE) return;
    myMapper->writeCPU(0x0000, 0x01);
    pushAddress(0x0038C5);
    SUB_0036CA();
    if (poppedEntry.value != 0x0038C5) return;
    SUB_00357C();
    return;
}

void game::SUB_0038DB() {
    x = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0055));
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0056));
    popAddress();
}

void game::SUB_0038E9() {
    x = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0081));
    x = myMapper->readCPU(0x0080);
    myMapper->writeCPU(0x2006, x);
    popAddress();
}

void game::SUB_0038F7() {
    x = 0x5D;
    a = myMapper->readCPU(0x0003);
    opAND(0x20);
    pushStatus();
    a = 0x00;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opINX(1);
    } while (!flgZ);
    x = 0xFD;
    do {
        a = myMapper->readCPU(0xFEFA + x);
        myMapper->writeCPU((0x0063 + x) & 0x00ff, a);
        opINX(1);
    } while (!flgZ);
    popStatus();
    popAddress();
}

void game::SUB_003919() {
    a = 0x00;
    pushAddress(0x00391B);
    SUB_00376E();
    if (poppedEntry.value != 0x00391B) return;
    pushAddress(0x00391E);
    SUB_003931();
    if (poppedEntry.value != 0x00391E) return;
    pushAddress(0x003921);
    SUB_00395E();
    if (poppedEntry.value != 0x003921) return;
    x = 0x00;
    do {
        myMapper->writeCPU(0x0294 + x, myMapper->readCPU(0xF911 + x));
        opINX(1);
        opCMP(x, 0x08);
    } while (!flgC);
    SUB_003931();
    return;
}

void game::SUB_003931() {
    pushAddress(0x003931);
    SUB_003941();
    if (poppedEntry.value != 0x003931) return;
    SUB_003934();
    return;
}

void game::SUB_003934() {
    myMapper->writeCPU(0x0080, 0x65);
    a = 0x20;
    myMapper->writeCPU(0x0081, a);
    y = 0x5D;
    SUB_00394E();
    return;
}

void game::SUB_003941() {
    myMapper->writeCPU(0x0080, 0x6F);
    a = 0x20;
    myMapper->writeCPU(0x0081, a);
    y = 0x57;
    SUB_00394E();
    return;
}

void game::SUB_00394E() {
    pushAddress(0x00394E);
    SUB_0038E9();
    if (poppedEntry.value != 0x00394E) return;
    x = 0x03;
    do {
        a = myMapper->readCPU(0x0002 + y);
        pushAddress(0x003956);
        SUB_00396B();
        if (poppedEntry.value != 0x003956) return;
        opDEY(1);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00395E() {
    myMapper->writeCPU(0x0080, 0x7C);
    myMapper->writeCPU(0x0081, 0x20);
    a = myMapper->readCPU(0x0061);
    pushAddress(0x003968);
    SUB_0038E9();
    if (poppedEntry.value != 0x003968) return;
    SUB_00396B();
    return;
}

void game::SUB_00396B() {
    opPHA();
    opLSR_A(4);
    pushAddress(0x003970);
    SUB_003974();
    if (poppedEntry.value != 0x003970) return;
    opPLA();
    SUB_003974();
    return;
}

void game::SUB_003974() {
    opAND(0x0F);
    opORA(0x30);
    myMapper->writeCPU(0x2007, a);
    SUB_00397B();
    return;
}

void game::SUB_00397B() {
    popAddress();
}

void game::SUB_00397C() {
    a = myMapper->readCPU(0x0003);
    opROR_A(1);
    if (flgC) {
        SUB_00397B();
        return;
    }
    a = myMapper->readCPU(0x0009);
    opAND(0x03);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0080, myMapper->readCPU(0xF994 + x));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0xF995 + x));
    indirectJump(myMapper->readCPU(0x0080) + (myMapper->readCPU((0x0080 + 1) & 0x00ff) << 8));
}

void game::SUB_00399C() {
    myMapper->writeCPU(0x0084, 0x1F);
    x = 0x01;
    a = myMapper->readCPU(0x0009);
    opAND(0x20);
    if (flgZ) {
        goto L_0039AA;
    }
    x = 0x81;
L_0039AA:
    a = x;
    SUB_00376E();
    return;
}

void game::SUB_0039AE() {
    popAddress();
}

void game::SUB_0039AF() {
    myMapper->writeCPU(0x0089, 0x00);
    a = myMapper->readCPU(0x0003);
    opASL_A(1);
    if (!flgN) {
        popAddress();
        return;
    }
    a = 0x5D;
    if (!flgC) {
        goto L_0039BF;
    }
    a = 0x5A;
L_0039BF:
    myMapper->writeCPU(0x008C, a);
    y = 0x00;
    myMapper->writeCPU(0x008D, y);
    x = 0x03;
    flgC = false;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x008C) + (myMapper->readCPU((0x008C + 1) & 0x00ff) << 8) + y);
        pushAddress(0x0039CA);
        SUB_0039E3();
        if (poppedEntry.value != 0x0039CA) return;
        myMapper->writeCPU(myMapper->readCPU(0x008C) + (myMapper->readCPU((0x008C + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    if (!flgC) {
        SUB_003A0D();
        return;
    }
    x = 0x02;
    a = 0x99;
    do {
        myMapper->writeCPU((0x0057 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0039DF() {
    myMapper->writeCPU(0x0088, x);
    x = 0x00;
    SUB_0039E3();
    return;
}

void game::SUB_0039E3() {
    myMapper->writeCPU(0x008F, a);
    opAND(0xF0);
    myMapper->writeCPU(0x008E, a);
    opEOR(myMapper->readCPU(0x008F));
    myMapper->writeCPU(0x008F, a);
    a = myMapper->readCPU((0x0088 + x) & 0x00ff);
    opAND(0x0F);
    opADC(myMapper->readCPU(0x008F));
    opCMP(a, 0x0A);
    if (flgC) {
        opADC(0x05);
    }
    opADC(myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x008E, a);
    a = myMapper->readCPU((0x0088 + x) & 0x00ff);
    opAND(0xF0);
    opADC(myMapper->readCPU(0x008E));
    if (flgC) {
        goto L_003A09;
    }
    opCMP(a, 0xA0);
    if (!flgC) {
        goto L_003A0C;
    }
L_003A09:
    opSBC(0xA0);
    flgC = true;
L_003A0C:
    popAddress();
}

void game::SUB_003A0D() {
    y = 0x02;
    do {
        opCMP(myMapper->readCPU(0x0057 + y), myMapper->readCPU(myMapper->readCPU(0x008C) + (myMapper->readCPU((0x008C + 1) & 0x00ff) << 8) + y));
        if (!flgC) {
            goto L_003A1B;
        }
        if (!flgZ) {
            goto L_003A25;
        }
        opDEY(1);
    } while (!flgN);
L_003A1B:
    y = 0x02;
    do {
        myMapper->writeCPU(0x0057 + y, myMapper->readCPU(myMapper->readCPU(0x008C) + (myMapper->readCPU((0x008C + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgN);
L_003A25:
    popAddress();
}

void game::SUB_003A88() {
    myMapper->writeCPU(0x0049, x);
    myMapper->writeCPU(0x0038, y);
    myMapper->writeCPU(0x0027, a);
    opLSR_A(4);
    opAND(0x0C);
    myMapper->writeCPU(0x0016, a);
    opLSR_A(2);
    y = a;
    x = myMapper->readCPU(0xFAEF + y);
    a = myMapper->readCPU(0x0027);
    opAND(0x3F);
    if (!flgZ) {
        opCMP(a, myMapper->readCPU((0x0002 + x) & 0x00ff));
        if (!flgC) {
            goto L_003AEA;
        }
        if (flgZ) {
            goto L_003AEA;
        }
        myMapper->writeCPU(0x0027, a);
        myMapper->writeCPU((0x0002 + x) & 0x00ff, 0x00);
        opASL_A(1);
        y = a;
        a = myMapper->readCPU(0xFCC2 + y);
        myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
        myMapper->writeCPU(0x00F2, a);
        a = myMapper->readCPU(0xFCC3 + y);
        myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
        myMapper->writeCPU(0x00F3, a);
        y = 0x01;
        myMapper->writeCPU((0x0000 + x) & 0x00ff, y);
        myMapper->writeCPU((0x0001 + x) & 0x00ff, y);
        opDEY(1);
        myMapper->writeCPU((0x0007 + x) & 0x00ff, y);
        myMapper->writeCPU((0x0008 + x) & 0x00ff, y);
        a = myMapper->readCPU(myMapper->readCPU(0x00F2) + (myMapper->readCPU((0x00F2 + 1) & 0x00ff) << 8) + y);
        opAND(0xF0);
        if (a != 0x20) {
            opINY(1);
        }
        myMapper->writeCPU((0x000A + x) & 0x00ff, y);
    }
    a = 0x00;
    y = myMapper->readCPU(0x0016);
    opCMP(y, 0x08);
    if (flgZ) {
        goto L_003ADE;
    }
    a = 0x30;
L_003ADE:
    myMapper->writeCPU(0x4000 + y, a);
    myMapper->writeCPU(0x4001 + y, a);
    a = myMapper->readCPU(0x0027);
    opAND(0x3F);
    myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
L_003AEA:
    x = myMapper->readCPU(0x0049);
    y = myMapper->readCPU(0x0038);
    popAddress();
}

void game::SUB_003AF3() {
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    flgC = false;
    opADC(0x01);
    opINY(1);
    opCMP(a, myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y));
    if (!flgZ) {
        if (flgN) {
            goto L_003B02;
        }
        flgC = true;
        opSBC(0x01);
    L_003B02:
        myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
        opINY(1);
        myMapper->writeCPU((0x0003 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU((0x0004 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y));
    }
    else {
        myMapper->writeCPU((0x0007 + x) & 0x00ff, 0x00);
        opINY(3);
        a = y;
        flgC = false;
        opADC(myMapper->readCPU(0x00F6));
        myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x00F7));
        myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
    }
    myMapper->writeCPU((0x0000 + x) & 0x00ff, 0x01);
    SUB_003B5C();
    return;
}

void game::SUB_003B2B() {
    myMapper->writeCPU((0x0002 + x) & 0x00ff, y);
    a = y;
    x = myMapper->readCPU(0x00F5);
    opCMP(x, 0x08);
    if (flgZ) {
        goto L_003B36;
    }
    a = 0x30;
L_003B36:
    myMapper->writeCPU(0x4000 + x, a);
    popAddress();
}

void game::SUB_003B3A() {
    x = 0x10;
    y = 0x00;
    do {
        myMapper->writeCPU(0x00F4, x);
        myMapper->writeCPU(0x00F5, y);
        if (myMapper->readCPU((0x0002 + x) & 0x00ff) != 0) {
            pushAddress(0x003B46);
            SUB_003B5C();
            if (poppedEntry.value != 0x003B46) return;
        }
        a = myMapper->readCPU(0x00F4);
        flgC = false;
        opADC(0x11);
        opCMP(a, 0x54);
        if (!flgZ) {
            goto L_003B53;
        }
        popAddress();
        return;
    L_003B53:
        x = a;
        a = myMapper->readCPU(0x00F5);
        flgC = false;
        opADC(0x04);
        y = a;
    } while (!flgC);
    SUB_003B5C();
    return;
}

void game::SUB_003B5C() {
    y = 0x00;
    myMapper->writeCPU(0x00F6, myMapper->readCPU((0x0003 + x) & 0x00ff));
    myMapper->writeCPU(0x00F7, myMapper->readCPU((0x0004 + x) & 0x00ff));
    opDEC((0x0000 + x) & 0x00ff, 1);
    if (flgZ) {
        goto L_003B82;
    }
    if (myMapper->readCPU(0x00BC) == 0) {
        goto L_003B81;
    }
    opCMP(myMapper->readCPU((0x0002 + x) & 0x00ff), 0x17);
    if (flgZ) {
        goto L_003B81;
    }
    while (true) {
        opINC((0x0000 + x) & 0x00ff, 1);
        a = y;
        myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
        x = myMapper->readCPU(0x00F5);
        myMapper->writeCPU(0x4002 + x, a);
        myMapper->writeCPU(0x4003 + x, a);
    L_003B81:
        popAddress();
        return;
    L_003B82:
        opCMP(myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y), 0xFE);
        if (flgC) {
            if (!flgZ) {
                SUB_003B2B();
                return;
            }
            SUB_003AF3();
            return;
        }
        if (myMapper->readCPU((0x000A + x) & 0x00ff) != 0) {
        }
        else {
            a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
            opAND(0xF0);
            if (a == 0x20) {
                a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
                opAND(0x0F);
                myMapper->writeCPU((0x0001 + x) & 0x00ff, a);
                opINY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
                x = myMapper->readCPU(0x00F5);
                myMapper->writeCPU(0x4000 + x, a);
                x = myMapper->readCPU(0x00F4);
                myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
                opINY(1);
            }
            myMapper->writeCPU((0x0000 + x) & 0x00ff, myMapper->readCPU((0x0001 + x) & 0x00ff));
            a = myMapper->readCPU((0x0009 + x) & 0x00ff);
            opAND(0x10);
            if (!flgZ) {
                a = myMapper->readCPU((0x0009 + x) & 0x00ff);
                opAND(0xF0);
                myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
                a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
                if (a != 0xF8) {
                    goto L_003BC8;
                }
                opINY(1);
                a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
            L_003BC8:
                opLSR_A(4);
                opORA(myMapper->readCPU((0x0009 + x) & 0x00ff));
                myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
                x = myMapper->readCPU(0x00F5);
                myMapper->writeCPU(0x4000 + x, a);
            }
            a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
            opAND(0x07);
            myMapper->writeCPU(0x00F0, a);
            opINY(1);
            myMapper->writeCPU(0x00F1, myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y));
            x = myMapper->readCPU(0x00F4);
            pushAddress(0x003BE2);
            SUB_003C71();
            if (poppedEntry.value != 0x003BE2) return;
            SUB_003C9A();
            return;
        }
        if (myMapper->readCPU(0x00BC) == 0) {
            goto L_003BEF;
        }
    }
L_003BEF:
    a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    if (a == 0xD0) {
        a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
        opAND(0x0F);
        myMapper->writeCPU((0x000D + x) & 0x00ff, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU((0x0005 + x) & 0x00ff, a);
        x = myMapper->readCPU(0x00F5);
        myMapper->writeCPU(0x4000 + x, a);
        opINY(1);
    }
    a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
    opAND(0xF0);
    if (a == 0xE0) {
        a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
        opAND(0x0F);
        x = myMapper->readCPU(0x00F4);
        myMapper->writeCPU((0x000B + x) & 0x00ff, a);
        opINY(1);
    }
    pushAddress(0x003C19);
    SUB_003C9A();
    if (poppedEntry.value != 0x003C19) return;
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
    opAND(0x0F);
    myMapper->writeCPU(0x00F0, a);
    if (!flgZ) {
        a = myMapper->readCPU((0x000D + x) & 0x00ff);
        flgC = false;
        do {
            opADC(myMapper->readCPU((0x000D + x) & 0x00ff));
            opDEC(0x00F0, 1);
        } while (!flgZ);
        if (flgZ) {
            goto L_003C32;
        }
    }
    a = myMapper->readCPU((0x000D + x) & 0x00ff);
L_003C32:
    myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0005 + x) & 0x00ff);
    myMapper->writeCPU((0x0009 + x) & 0x00ff, a);
    x = myMapper->readCPU(0x00F5);
    myMapper->writeCPU(0x4000 + x, a);
    a = myMapper->readCPU(myMapper->readCPU(0x00F6) + (myMapper->readCPU((0x00F6 + 1) & 0x00ff) << 8) + y);
    opLSR_A(4);
    if (a == 0x0C) {
        a = 0x00;
        opCMP(x, 0x08);
        if (flgZ) {
            goto L_003C4F;
        }
        a = 0x30;
    L_003C4F:
        myMapper->writeCPU(0x4000 + x, a);
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x00F4);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00F0, myMapper->readCPU(0xFCAC + y));
    opINY(1);
    myMapper->writeCPU(0x00F1, myMapper->readCPU(0xFCAC + y));
    y = myMapper->readCPU((0x000B + x) & 0x00ff);
    while (true) {
        if (y == 0x04) {
            SUB_003C71();
            return;
        }
        opLSR_M(0x00F0, 1);
        opROR_M(0x00F1, 1);
        opINY(1);
    }
    SUB_003C71();
    return;
}

void game::SUB_003C71() {
    a = myMapper->readCPU(0x00F0);
    opORA(0x08);
    myMapper->writeCPU(0x00F0, a);
    opCMP(a, myMapper->readCPU((0x0008 + x) & 0x00ff));
    if (!flgZ) {
        goto L_003C89;
    }
    a = myMapper->readCPU((0x0009 + x) & 0x00ff);
    opAND(0x10);
    if (flgZ) {
        goto L_003C8B;
    }
    x = myMapper->readCPU(0x00F5);
    opCMP(x, 0x08);
    if (flgZ) {
        goto L_003C8B;
    }
    if (!flgZ) {
        goto L_003C92;
    }
L_003C89:
    myMapper->writeCPU((0x0008 + x) & 0x00ff, a);
L_003C8B:
    a = myMapper->readCPU(0x00F0);
    x = myMapper->readCPU(0x00F5);
    myMapper->writeCPU(0x4003 + x, a);
L_003C92:
    x = myMapper->readCPU(0x00F5);
    myMapper->writeCPU(0x4002 + x, myMapper->readCPU(0x00F1));
    popAddress();
}

void game::SUB_003C9A() {
    opINY(1);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x00F6));
    x = myMapper->readCPU(0x00F4);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    if (!flgC) {
        goto L_003CAB;
    }
    a = myMapper->readCPU(0x00F7);
    opADC(0x00);
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
L_003CAB:
    popAddress();
}

void game::indirectJump(Uint16 target) {
    switch (target) {
    case 0xE39B:
        SUB_00239B();
        break;
    case 0xE3CB:
        SUB_0023CB();
        break;
    case 0xE3DB:
        SUB_0023DB();
        break;
    case 0xE3EC:
        SUB_0023EC();
        break;
    case 0xE42A:
        SUB_00242A();
        break;
    case 0xE43E:
        SUB_00243E();
        break;
    case 0xE471:
        SUB_002471();
        break;
    case 0xC83B:
        SUB_00083B();
        break;
    case 0xC835:
        SUB_000835();
        break;
    case 0xC828:
        SUB_000828();
        break;
    case 0xC5F7:
        SUB_0005F7();
        break;
    case 0xCEAE:
        SUB_000EAE();
        break;
    case 0xCECF:
        SUB_000ECF();
        break;
    case 0xCF44:
        SUB_000F44();
        break;
    case 0xCF4F:
        SUB_000F4F();
        break;
    case 0xCF89:
        SUB_000F89();
        break;
    case 0xCFC3:
        SUB_000FC3();
        break;
    case 0xCF08:
        SUB_000F08();
        break;
    case 0xD055:
        SUB_001055();
        break;
    case 0xD05E:
        SUB_00105E();
        break;
    case 0xDFB0:
        SUB_001FB0();
        break;
    case 0xDFBF:
        SUB_001FBF();
        break;
    case 0xDFDF:
        SUB_001FDF();
        break;
    case 0xDFCB:
        SUB_001FCB();
        break;
    case 0xDFC5:
        SUB_001FC5();
        break;
    case 0xDFD1:
        SUB_001FD1();
        break;
    case 0xDFB6:
        SUB_001FB6();
        break;
    case 0xE0AC:
        SUB_0020AC();
        break;
    case 0xE12F:
        SUB_00212F();
        break;
    case 0xE1A6:
        SUB_0021A6();
        break;
    case 0xEE80:
        SUB_002E80();
        break;
    case 0xEE93:
        SUB_002E93();
        break;
    case 0xEEA3:
        SUB_002EA3();
        break;
    case 0xEEB4:
        SUB_002EB4();
        break;
    case 0xEEC2:
        SUB_002EC2();
        break;
    case 0xEEC8:
        SUB_002EC8();
        break;
    case 0xEED6:
        SUB_002ED6();
        break;
    case 0xF36D:
        SUB_00336D();
        break;
    case 0xF36E:
        SUB_00336E();
        break;
    case 0xF37A:
        SUB_00337A();
        break;
    case 0xF384:
        SUB_003384();
        break;
    case 0xC058:
        SUB_000058();
        break;
    case 0xF3F3:
        SUB_0033F3();
        break;
    case 0xF497:
        SUB_003497();
        break;
    case 0xF49A:
        SUB_00349A();
        break;
    case 0xF4B8:
        SUB_0034B8();
        break;
    case 0xF4C6:
        SUB_0034C6();
        break;
    case 0xF46D:
        SUB_00346D();
        break;
    case 0xF5AF:
        SUB_0035AF();
        break;
    case 0xF5DD:
        SUB_0035DD();
        break;
    case 0xF5FF:
        SUB_0035FF();
        break;
    case 0xF59B:
        SUB_00359B();
        break;
    case 0xF934:
        SUB_003934();
        break;
    case 0xF9AE:
        SUB_0039AE();
        break;
    case 0xF99C:
        SUB_00399C();
        break;
    case 0xF941:
        SUB_003941();
        break;
    default:
        bool test = true;
        break;
    }
}

