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
    SUB_000009();
    return;
}

void game::nmi() {
    SUB_0019C2();
    return;
}

void game::SUB_000009() {
    flgD = false;
    flgI = true;
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    x = 0x03;
    //do {
    //L_000015:
    //    if (!(myMapper->readCPU(0x2002) & 0x80)) {
    //        goto L_000015;
    //    }
    //L_00001A:
    //    if (myMapper->readCPU(0x2002) & 0x80) {
    //        goto L_00001A;
    //    }
    //    opDEX(1);
    //} while (!flgZ);
    s = 0xF0;
    pushAddress(0x000025);
    SUB_000133();
    if (poppedEntry.value != 0x000025) return;
    a = 0x00;
    myMapper->writeCPU(0x0680, a);
    myMapper->writeCPU(0x0681, a);
    myMapper->writeCPU(0x0682, a);
    myMapper->writeCPU(0x0683, a);
    myMapper->writeCPU(0x00F0, a);
    a = myMapper->readCPU(0x0690);
    flgC = false;
    opADC(myMapper->readCPU(0x0691));
    flgC = false;
    opADC(myMapper->readCPU(0x0692));
    opCMP(a, 0x06);
    if (flgZ) {
        SUB_000051();
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x00F1, a);
    myMapper->writeCPU(0x00F2, a);
    myMapper->writeCPU(0x00F3, a);
    myMapper->writeCPU(0x00F4, a);
    SUB_000051();
    return;
}

void game::SUB_000051() {
    pushAddress(0x000051);
    SUB_0051E0();
    if (poppedEntry.value != 0x000051) return;
    x = 0x01;
    myMapper->writeCPU(0x0690, x);
    opINX(1);
    myMapper->writeCPU(0x0691, x);
    opINX(1);
    myMapper->writeCPU(0x0692, x);
    pushAddress(0x000061);
    SUB_00015B();
    if (poppedEntry.value != 0x000061) return;
    SUB_000064();
    return;
}

void game::SUB_000064() {
    pushAddress(0x000064);
    SUB_0001A5();
    if (poppedEntry.value != 0x000064) return;
    pushAddress(0x000067);
    SUB_001AE6();
    if (poppedEntry.value != 0x000067) return;
    pushAddress(0x00006A);
    SUB_001FC4();
    if (poppedEntry.value != 0x00006A) return;
    pushAddress(0x00006D);
    SUB_002C48();
    if (poppedEntry.value != 0x00006D) return;
    pushAddress(0x000070);
    SUB_0003A8();
    if (poppedEntry.value != 0x000070) return;
    pushAddress(0x000073);
    SUB_001B1E();
    if (poppedEntry.value != 0x000073) return;
    a = 0x00;
    pushAddress(0x000078);
    SUB_0051A5();
    if (poppedEntry.value != 0x000078) return;
    a = 0x10;
    pushAddress(0x00007D);
    SUB_0051A5();
    if (poppedEntry.value != 0x00007D) return;
    SUB_000080();
    return;
}

void game::SUB_000080() {
    pushAddress(0x000080);
    SUB_00011F();
    if (poppedEntry.value != 0x000080) return;
    SUB_000083();
    return;
}

void game::SUB_000083() {
    while (true) {
        do {
            wait();
            a = myMapper->readCPU(0x0000);
            opCMP(a, myMapper->readCPU(0x0001));
        } while (flgZ);
        myMapper->writeCPU(0x0001, a);
        pushAddress(0x00008B);
        SUB_0003B8();
        if (poppedEntry.value != 0x00008B) return;
        pushAddress(0x00008E);
        SUB_001A2C();
        if (poppedEntry.value != 0x00008E) return;
        pushAddress(0x000091);
        SUB_0030C9();
        if (poppedEntry.value != 0x000091) return;
        pushAddress(0x000094);
        SUB_001D14();
        if (poppedEntry.value != 0x000094) return;
        pushAddress(0x000097);
        SUB_001B1E();
        if (poppedEntry.value != 0x000097) return;
        pushAddress(0x00009A);
        SUB_00275C();
        if (poppedEntry.value != 0x00009A) return;
        if (myMapper->readCPU(0x0084) != 0) {
            pushAddress(0x0000A1);
            SUB_0051E0();
            if (poppedEntry.value != 0x0000A1) return;
            a = 0x05;
            pushAddress(0x0000A6);
            SUB_0051A5();
            if (poppedEntry.value != 0x0000A6) return;
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0084, a);
            if (flgZ) {
                goto L_0000D5;
            }
        }
        a = myMapper->readCPU(0x003A);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0000BA;
        }
        pushAddress(0x0000B3);
        SUB_0051A5();
        if (poppedEntry.value != 0x0000B3) return;
        myMapper->writeCPU(0x003A, 0x00);
    L_0000BA:
        pushAddress(0x0000BA);
        SUB_002702();
        if (poppedEntry.value != 0x0000BA) return;
        pushAddress(0x0000BD);
        SUB_001E35();
        if (poppedEntry.value != 0x0000BD) return;
        pushAddress(0x0000C0);
        SUB_002CD2();
        if (poppedEntry.value != 0x0000C0) return;
        pushAddress(0x0000C3);
        SUB_005356();
        if (poppedEntry.value != 0x0000C3) return;
        pushAddress(0x0000C6);
        SUB_000451();
        if (poppedEntry.value != 0x0000C6) return;
        pushAddress(0x0000C9);
        SUB_001493();
        if (poppedEntry.value != 0x0000C9) return;
        pushAddress(0x0000CC);
        SUB_00072A();
        if (poppedEntry.value != 0x0000CC) return;
        pushAddress(0x0000CF);
        SUB_0017A5();
        if (poppedEntry.value != 0x0000CF) return;
        pushAddress(0x0000D2);
        SUB_0035E2();
        if (poppedEntry.value != 0x0000D2) return;
    L_0000D5:
        pushAddress(0x0000D5);
        SUB_00277D();
        if (poppedEntry.value != 0x0000D5) return;
        pushAddress(0x0000D8);
        SUB_0004F3();
        if (poppedEntry.value != 0x0000D8) return;
        pushAddress(0x0000DB);
        SUB_002BFC();
        if (poppedEntry.value != 0x0000DB) return;
        pushAddress(0x0000DE);
        SUB_0025E6();
        if (poppedEntry.value != 0x0000DE) return;
        pushAddress(0x0000E1);
        SUB_002CFD();
        if (poppedEntry.value != 0x0000E1) return;
        pushAddress(0x0000E4);
        SUB_0025A6();
        if (poppedEntry.value != 0x0000E4) return;
        opDEC(0x000B, 1);
        x = myMapper->readCPU(0x0030);
        if (myMapper->readCPU((0x002E + x) & 0x00ff) & 0x80) {
            goto L_0000F2;
        }
    }
L_0000F2:
    a = 0x00;
    myMapper->writeCPU(0x0094, a);
    myMapper->writeCPU(0x0095, a);
    myMapper->writeCPU(0x0036, a);
    myMapper->writeCPU(0x003E, a);
    myMapper->writeCPU(0x0035, a);
    pushAddress(0x0000FE);
    SUB_00048F();
    if (poppedEntry.value != 0x0000FE) return;
    x = myMapper->readCPU(0x0030);
    a = myMapper->readCPU((0x002E + x) & 0x00ff);
    opAND(0x0F);
    myMapper->writeCPU((0x002E + x) & 0x00ff, a);
    opDEC((0x002E + x) & 0x00ff, 1);
    if (flgZ) {
        pushAddress(0x00010D);
        SUB_0002BC();
        if (poppedEntry.value != 0x00010D) return;
    }
    pushAddress(0x000110);
    SUB_000365();
    if (poppedEntry.value != 0x000110) return;
    a = myMapper->readCPU(0x002E);
    opORA(myMapper->readCPU(0x002F));
    if (flgZ) {
        goto L_00011C;
    }
    SUB_000064();
    return;
L_00011C:
    SUB_000051();
    return;
}

void game::SUB_00011F() {
    myMapper->writeCPU(0x2000, 0x80);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    popAddress();
}

void game::SUB_000133() {
    x = 0xEF;
    a = 0x00;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00013D() {
    a = 0x00;
    x = a;
    do {
        myMapper->writeCPU(0x0200 + x, a);
        myMapper->writeCPU(0x0300 + x, a);
        myMapper->writeCPU(0x0400 + x, a);
        myMapper->writeCPU(0x0500 + x, a);
        opINX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_000150() {
    x = 0x00;
    a = 0xF8;
    do {
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00015B() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    pushAddress(0x000163);
    SUB_0051E0();
    if (poppedEntry.value != 0x000163) return;
    pushAddress(0x000166);
    SUB_0030E4();
    if (poppedEntry.value != 0x000166) return;
    while (true) {
        do {
            a = 0x01;
            pushAddress(0x00016B);
            SUB_0051A5();
            if (poppedEntry.value != 0x00016B) return;
            myMapper->writeCPU(0x0033, 0x02);
            pushAddress(0x000172);
            SUB_0046C1();
            if (poppedEntry.value != 0x000172) return;
            a = myMapper->readCPU(0x0003);
            opAND(0x10);
            if (!flgZ) {
                goto L_000193;
            }
            myMapper->writeCPU(0x0033, 0x01);
            a = 0x00;
            pushAddress(0x000181);
            SUB_0051A5();
            if (poppedEntry.value != 0x000181) return;
            pushAddress(0x000184);
            SUB_0046BB();
            if (poppedEntry.value != 0x000184) return;
            a = myMapper->readCPU(0x0002);
            opAND(0x30);
        } while (!flgZ);
        pushAddress(0x00018D);
        SUB_004D21();
        if (poppedEntry.value != 0x00018D) return;
    }
L_000193:
    pushAddress(0x000193);
    SUB_000133();
    if (poppedEntry.value != 0x000193) return;
    a = 0x05;
    if (myMapper->readCPU(0x00F0) == 0) {
        goto L_00019E;
    }
    myMapper->writeCPU(0x002F, a);
L_00019E:
    myMapper->writeCPU(0x002E, a);
    myMapper->writeCPU(0x0030, 0x00);
    popAddress();
}

void game::SUB_0001A5() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0003, a);
    pushAddress(0x0001B3);
    SUB_000150();
    if (poppedEntry.value != 0x0001B3) return;
    pushAddress(0x0001B6);
    SUB_000226();
    if (poppedEntry.value != 0x0001B6) return;
    pushAddress(0x0001B9);
    SUB_00013D();
    if (poppedEntry.value != 0x0001B9) return;
    pushAddress(0x0001BC);
    SUB_000150();
    if (poppedEntry.value != 0x0001BC) return;
    pushAddress(0x0001BF);
    SUB_0001C8();
    if (poppedEntry.value != 0x0001BF) return;
    pushAddress(0x0001C2);
    SUB_0004C2();
    if (poppedEntry.value != 0x0001C2) return;
    SUB_003CF9();
    return;
}

void game::SUB_0001C8() {
    a = 0x00;
    x = 0x3F;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opINX(1);
        opCMP(x, 0x71);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0001D4() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x0003);
    opAND(0x20);
    if (flgZ) {
        SUB_00020E();
        return;
    }
    opINC(0x00F0, 1);
    SUB_0001E1();
    return;
}

void game::SUB_0001E1() {
    y = 0x02;
    myMapper->writeCPU(0x00B5, 0xC0);
    a = myMapper->readCPU(0x00F0);
    opAND(0x01);
    myMapper->writeCPU(0x00F0, a);
    x = a;
    do {
        a = myMapper->readCPU(0x8224 + x);
        opPHA();
        a = myMapper->readCPU(0x2002);
        a = 0x22;
        myMapper->writeCPU(0x2006, a);
        opPLA();
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x00B5));
        myMapper->writeCPU(0x00B5, 0xAA);
        a = x;
        opEOR(0x01);
        x = a;
        opDEY(1);
    } while (!flgZ);
    SUB_00020E();
    return;
}

void game::SUB_00020E() {
    myMapper->writeCPU(0x2000, 0x88);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2001, 0x1A);
    popAddress();
}

void game::SUB_000226() {
    myMapper->writeCPU(0x2001, 0x00);
    pushAddress(0x00022B);
    SUB_0051E0();
    if (poppedEntry.value != 0x00022B) return;
    pushAddress(0x00022E);
    SUB_003D2D();
    if (poppedEntry.value != 0x00022E) return;
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x8A);
    a = myMapper->readCPU(0x0030);
    flgC = false;
    opADC(0xDB);
    myMapper->writeCPU(0x2007, a);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x8304 + y));
        opINY(1);
    } while (y != 0x0C);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0xD1);
    myMapper->writeCPU(0x2007, 0x86);
    myMapper->writeCPU(0x2007, 0xAA);
    x = myMapper->readCPU(0x0030);
    a = myMapper->readCPU((0x002E + x) & 0x00ff);
    flgC = false;
    opADC(0xDA);
    myMapper->writeCPU(0x2007, a);
    a = 0x70;
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0704, a);
    myMapper->writeCPU(0x0708, a);
    myMapper->writeCPU(0x0703, a);
    myMapper->writeCPU(0x0707, 0x78);
    myMapper->writeCPU(0x070B, 0x68);
    myMapper->writeCPU(0x0705, 0x01);
    myMapper->writeCPU(0x0709, 0x52);
    myMapper->writeCPU(0x070A, 0x02);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0701, a);
    myMapper->writeCPU(0x0702, a);
    myMapper->writeCPU(0x0706, a);
    myMapper->writeCPU(0x2001, 0x1A);
    myMapper->writeCPU(0x2000, 0x88);
    SUB_00031D();
    return;
}

void game::SUB_0002BC() {
    myMapper->writeCPU(0x2001, 0x00);
    pushAddress(0x0002C1);
    SUB_0051E0();
    if (poppedEntry.value != 0x0002C1) return;
    pushAddress(0x0002C4);
    SUB_003D2D();
    if (poppedEntry.value != 0x0002C4) return;
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x21);
    myMapper->writeCPU(0x2006, 0x89);
    a = myMapper->readCPU(0x0030);
    flgC = false;
    opADC(0xDB);
    myMapper->writeCPU(0x2007, a);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x8310 + y));
        opINY(1);
    } while (y != 0x0D);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0081, a);
    myMapper->writeCPU(0x0092, a);
    myMapper->writeCPU(0x0094, a);
    myMapper->writeCPU(0x0095, a);
    myMapper->writeCPU(0x2001, 0x0A);
    SUB_00033B();
    return;
}

void game::SUB_00031D() {
    myMapper->writeCPU(0x0033, 0x01);
    myMapper->writeCPU(0x2000, 0x88);
    y = 0x50;
    do {
        do {
            wait();
            a = myMapper->readCPU(0x0000);
            opCMP(a, myMapper->readCPU(0x0001));
        } while (flgZ);
        myMapper->writeCPU(0x0001, a);
        opDEY(1);
    } while (!flgZ);
    a = 0x00;
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_00033B() {
    myMapper->writeCPU(0x0033, 0x01);
    myMapper->writeCPU(0x2000, 0x80);
    myMapper->writeCPU(0x00C0, 0x50);
    do {
        do {
			wait();
            a = myMapper->readCPU(0x0000);
        } while (a == myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x0001, a);
        pushAddress(0x000350);
        SUB_001A2C();
        if (poppedEntry.value != 0x000350) return;
        a = myMapper->readCPU(0x0003);
        opAND(0x30);
        if (!flgZ) {
            goto L_00035D;
        }
        opDEC(0x00C0, 1);
    } while (!flgZ);
L_00035D:
    a = 0x00;
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_000365() {
    if (myMapper->readCPU(0x00F0) == 0) {
        goto L_000374;
    }
    a = myMapper->readCPU(0x0030);
    opAND(0x01);
    opEOR(0x01);
    x = a;
    if (myMapper->readCPU((0x002E + x) & 0x00ff) != 0) {
        goto L_000375;
    }
L_000374:
    popAddress();
    return;
L_000375:
    myMapper->writeCPU(0x0030, x);
    a = myMapper->readCPU(0x0081);
    opPHA();
    a = myMapper->readCPU(0x0092);
    opPHA();
    a = myMapper->readCPU(0x0094);
    opPHA();
    a = myMapper->readCPU(0x0095);
    opPHA();
    myMapper->writeCPU(0x0081, myMapper->readCPU(0x0680));
    myMapper->writeCPU(0x0092, myMapper->readCPU(0x0681));
    myMapper->writeCPU(0x0094, myMapper->readCPU(0x0682));
    a = myMapper->readCPU(0x0683);
    myMapper->writeCPU(0x0095, a);
    opPLA();
    myMapper->writeCPU(0x0683, a);
    opPLA();
    myMapper->writeCPU(0x0682, a);
    opPLA();
    myMapper->writeCPU(0x0681, a);
    opPLA();
    myMapper->writeCPU(0x0680, a);
    popAddress();
}

void game::SUB_0003A8() {
    a = myMapper->readCPU(0x0030);
    opPHA();
    a = myMapper->readCPU(0x0030);
    opEOR(0x01);
    myMapper->writeCPU(0x0030, a);
    pushAddress(0x0003B1);
    SUB_002A02();
    if (poppedEntry.value != 0x0003B1) return;
    opPLA();
    myMapper->writeCPU(0x0030, a);
    popAddress();
}

void game::SUB_0003B8() {
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_0003C6;
    }
    a = myMapper->readCPU(0x0014);
    opAND(0x40);
    if (flgZ) {
        if (myMapper->readCPU(0x0091) == 0) {
            goto L_0003C7;
        }
    }
L_0003C6:
    popAddress();
    return;
L_0003C7:
    if (myMapper->readCPU(0x0034) == 0) {
        a = myMapper->readCPU(0x0003);
        opAND(0x10);
        if (flgZ) {
            goto L_000415;
        }
        a = myMapper->readCPU(0x0034);
        opEOR(0xFF);
        myMapper->writeCPU(0x0034, a);
        pushAddress(0x0003D7);
        SUB_000416();
        if (poppedEntry.value != 0x0003D7) return;
        pushAddress(0x0003DA);
        SUB_005798();
        if (poppedEntry.value != 0x0003DA) return;
        myMapper->writeCPU(0x00B4, 0x02);
        a = 0xC0;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0003EB;
        }
    }
    myMapper->writeCPU(0x00B4, 0x05);
    a = 0x24;
L_0003EB:
    myMapper->writeCPU(0x0098, a);
    pushAddress(0x0003ED);
    SUB_00275C();
    if (poppedEntry.value != 0x0003ED) return;
    pushAddress(0x0003F0);
    SUB_001A2C();
    if (poppedEntry.value != 0x0003F0) return;
    a = myMapper->readCPU(0x00C2);
    opORA(myMapper->readCPU(0x00C3));
    if (!flgZ) {
        pushAddress(0x0003F9);
        SUB_0057B0();
        if (poppedEntry.value != 0x0003F9) return;
    }
    a = myMapper->readCPU(0x0003);
    opAND(0x10);
    if (!flgZ) {
        goto L_000407;
    }
    opPLA();
    opPLA();
    SUB_000083();
    return;
L_000407:
    a = 0x00;
    myMapper->writeCPU(0x0034, a);
    myMapper->writeCPU(0x0003, a);
    pushAddress(0x00040D);
    SUB_000430();
    if (poppedEntry.value != 0x00040D) return;
    opPLA();
    opPLA();
    SUB_000083();
    return;
L_000415:
    popAddress();
}

void game::SUB_000416() {
    x = 0x00;
    a = 0xF8;
    do {
        myMapper->writeCPU(0x0730 + x, a);
        opINX(1);
    } while (x != 0xD0);
    x = 0x00;
    do {
        myMapper->writeCPU(0x0720 + x, myMapper->readCPU(0x843D + x));
        opINX(1);
        opCMP(x, 0x14);
    } while (!flgZ);
    popAddress();
}

void game::SUB_000430() {
    x = 0x00;
    a = 0xAA;
    do {
        myMapper->writeCPU(0x0720 + x, a);
        opINX(1);
    } while (x != 0x14);
    popAddress();
}

void game::SUB_000451() {
    a = myMapper->readCPU(0x0095);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x80) {
            goto L_00045F;
        }
        pushAddress(0x000459);
        SUB_00047B();
        if (poppedEntry.value != 0x000459) return;
        goto L_00047A;
    L_00045F:
        pushAddress(0x00045F);
        SUB_0036E2();
        if (poppedEntry.value != 0x00045F) return;
        if (myMapper->readCPU(0x0095) != 0) {
            goto L_00047A;
        }
        pushAddress(0x000466);
        SUB_00047B();
        if (poppedEntry.value != 0x000466) return;
        myMapper->writeCPU(0x0094, 0x00);
        myMapper->writeCPU(0x0035, 0x40);
        a = 0x1F;
        myMapper->writeCPU(0x006A, a);
        myMapper->writeCPU(0x0093, a);
        pushAddress(0x000477);
        SUB_002A97();
        if (poppedEntry.value != 0x000477) return;
    }
L_00047A:
    popAddress();
}

void game::SUB_00047B() {
    x = 0x00;
    a = x;
    do {
        myMapper->writeCPU(0x0200 + x, a);
        myMapper->writeCPU(0x0300 + x, a);
        if (x >= 0xE0) {
            goto L_00048B;
        }
        myMapper->writeCPU(0x0720 + x, a);
    L_00048B:
        opINX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00048F() {
    y = 0x00;
    a = myMapper->readCPU(0x0081);
    opCMP(a, 0x1E);
    if (flgZ) {
        myMapper->writeCPU(0x0092, y);
        myMapper->writeCPU(0x0094, 0x80);
        popAddress();
        return;
    }
    opINY(1);
    opCMP(a, 0x3E);
    if (flgZ) {
        myMapper->writeCPU(0x0092, y);
        myMapper->writeCPU(0x0094, 0x80);
        popAddress();
        return;
    }
    opINY(1);
    opCMP(a, 0x5E);
    if (flgZ) {
        myMapper->writeCPU(0x0092, y);
        myMapper->writeCPU(0x0094, 0x80);
        popAddress();
        return;
    }
    opINY(1);
    opCMP(a, 0x7E);
    if (!flgZ) {
        goto L_0004C1;
    }
    myMapper->writeCPU(0x0092, y);
    myMapper->writeCPU(0x0094, 0x80);
L_0004C1:
    popAddress();
}

void game::SUB_0004C2() {
    myMapper->writeCPU(0x0014, 0x80);
    myMapper->writeCPU(0x0015, 0x38);
    myMapper->writeCPU(0x0703, 0x34);
    myMapper->writeCPU(0x0016, 0x70);
    myMapper->writeCPU(0x0700, 0x6C);
    a = 0x00;
    myMapper->writeCPU(0x0701, a);
    myMapper->writeCPU(0x0702, a);
    myMapper->writeCPU(0x0706, a);
    myMapper->writeCPU(0x0705, 0x01);
    myMapper->writeCPU(0x0709, 0x50);
    myMapper->writeCPU(0x070A, 0x02);
    popAddress();
}

void game::SUB_0004F3() {
    pushAddress(0x0004F3);
    SUB_000501();
    if (poppedEntry.value != 0x0004F3) return;
    pushAddress(0x0004F6);
    SUB_0006C8();
    if (poppedEntry.value != 0x0004F6) return;
    if (myMapper->readCPU(0x0097) != 0) {
        goto L_000500;
    }
    pushAddress(0x0004FD);
    SUB_0005A2();
    if (poppedEntry.value != 0x0004FD) return;
L_000500:
    popAddress();
}

void game::SUB_000501() {
    if (myMapper->readCPU(0x0097) == 0) {
        goto L_00050C;
    }
    myMapper->writeCPU(0x0016, 0x88);
    goto L_0005A1;
L_00050C:
    if (myMapper->readCPU(0x0091) == 0) {
        a = myMapper->readCPU(0x0014);
        opAND(0x40);
        if (flgZ) {
            goto L_000519;
        }
    }
    goto L_0005A1;
L_000519:
    myMapper->writeCPU(0x007B, 0x00);
    a = myMapper->readCPU(0x0002);
    opAND(0x02);
    if (!flgZ) {
        if (myMapper->readCPU(0x0015) < 0x18) {
            goto L_00053F;
        }
        opDEC(0x0015, 2);
        if (!flgZ) {
            goto L_00053F;
        }
    }
    a = myMapper->readCPU(0x0002);
    opAND(0x01);
    if (!flgZ) {
        if (myMapper->readCPU(0x0015) >= 0xE8) {
            goto L_00053F;
        }
        opINC(0x0015, 2);
    }
L_00053F:
    if (myMapper->readCPU(0x007D) != 0) {
        a = myMapper->readCPU(0x0015);
        if (a < 0x18) {
            goto L_00057D;
        }
        myMapper->writeCPU(0x007B, 0x00);
        if (a < 0x38) {
            goto L_00057D;
        }
        myMapper->writeCPU(0x007B, 0x01);
        if (a < 0x58) {
            goto L_00057D;
        }
        x = 0x02;
        setLoadFlag(x);
        myMapper->writeCPU(0x007B, x);
        if (!flgZ) {
            goto L_00057D;
        }
    }
    if (0xE8 >= myMapper->readCPU(0x0015)) {
        myMapper->writeCPU(0x007B, 0x00);
        if (0xC8 >= myMapper->readCPU(0x0015)) {
            myMapper->writeCPU(0x007B, 0x01);
            if (0xA8 >= myMapper->readCPU(0x0015)) {
                myMapper->writeCPU(0x007B, 0x02);
            }
        }
    }
L_00057D:
    a = myMapper->readCPU(0x0002);
    opAND(0x04);
    if (!flgZ) {
        opINC(0x0016, 2);
    }
    a = myMapper->readCPU(0x0002);
    opAND(0x08);
    if (!flgZ) {
        opDEC(0x0016, 2);
    }
    a = myMapper->readCPU(0x0016);
    if (a < 0x30) {
        a = 0x30;
    }
    if (a < 0xD8) {
        goto L_00059F;
    }
    a = 0xD8;
L_00059F:
    myMapper->writeCPU(0x0016, a);
L_0005A1:
    popAddress();
}

void game::SUB_0005A2() {
    a = myMapper->readCPU(0x0014);
    opAND(0x40);
    if (!flgZ) {
        SUB_000634();
        return;
    }
    a = myMapper->readCPU(0x004F);
    opAND(0x80);
    if (!flgZ) {
        a = myMapper->readCPU(0x000B);
        opAND(0x03);
        if (flgZ) {
            myMapper->writeCPU(0x00B4, 0x30);
            myMapper->writeCPU(0x00B6, 0x31);
            a = 0x02;
            setLoadFlag(a);
            myMapper->writeCPU(0x00B5, a);
            if (!flgZ) {
                goto L_0005D9;
            }
        }
        a = 0xAA;
        myMapper->writeCPU(0x00B4, a);
        myMapper->writeCPU(0x00B6, a);
        a = 0x00;
        setLoadFlag(a);
        if (flgZ) {
            goto L_0005DE;
        }
    }
    a = 0x00;
    myMapper->writeCPU(0x00B4, a);
    myMapper->writeCPU(0x00B5, a);
    myMapper->writeCPU(0x00B6, 0x01);
L_0005D9:
    a = myMapper->readCPU(0x0002);
    opAND(0x0C);
    opLSR_A(1);
L_0005DE:
    myMapper->writeCPU(0x00B7, a);
    flgC = false;
    opADC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x0701, a);
    a = myMapper->readCPU(0x00B7);
    flgC = false;
    opADC(myMapper->readCPU(0x00B6));
    myMapper->writeCPU(0x0705, a);
    if (myMapper->readCPU(0x007D) == 0) {
        goto L_000605;
    }
    a = 0x00;
    flgC = false;
    opADC(myMapper->readCPU(0x00B5));
    myMapper->writeCPU(0x0702, a);
    myMapper->writeCPU(0x0706, a);
    myMapper->writeCPU(0x070A, 0x02);
    goto L_000615;
L_000605:
    a = 0x40;
    flgC = false;
    opADC(myMapper->readCPU(0x00B5));
    myMapper->writeCPU(0x0702, a);
    myMapper->writeCPU(0x0706, a);
    myMapper->writeCPU(0x070A, 0x42);
L_000615:
    pushAddress(0x000615);
    SUB_000619();
    if (poppedEntry.value != 0x000615) return;
    popAddress();
}

void game::SUB_000619() {
    a = myMapper->readCPU(0x004F);
    opAND(0x80);
    if (flgZ) {
        goto L_00062B;
    }
    opINC(0x0019, 1);
    if (!flgZ) {
        goto L_000633;
    }
    opINC(0x001A, 1);
    if (myMapper->readCPU(0x001A) != 0x03) {
        goto L_000633;
    }
L_00062B:
    a = 0x00;
    myMapper->writeCPU(0x0019, a);
    myMapper->writeCPU(0x001A, a);
    myMapper->writeCPU(0x004F, a);
L_000633:
    popAddress();
}

void game::SUB_000634() {
    opINC(0x0031, 1);
    a = myMapper->readCPU(0x0031);
    if (a < 0x60) {
        goto L_000654;
    }
    opPHA();
    myMapper->writeCPU(0x0014, 0x80);
    x = myMapper->readCPU(0x0030);
    a = myMapper->readCPU((0x002E + x) & 0x00ff);
    opORA(0x80);
    myMapper->writeCPU((0x002E + x) & 0x00ff, a);
    a = 0x00;
    myMapper->writeCPU(0x0031, a);
    myMapper->writeCPU(0x001B, a);
    myMapper->writeCPU(0x001F, a);
    myMapper->writeCPU(0x0027, a);
    opPLA();
L_000654:
    opLSR_A(3);
    opAND(0x03);
    opPHA();
    a = myMapper->readCPU(0x0700);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0708, a);
    a = myMapper->readCPU(0x0704);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070C, a);
    myMapper->writeCPU(0x070B, myMapper->readCPU(0x0703));
    a = myMapper->readCPU(0x0707);
    myMapper->writeCPU(0x070F, a);
    opPLA();
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0x86A8 + x));
    myMapper->writeCPU(0x00B5, myMapper->readCPU(0x86A9 + x));
    x = 0x00;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0701 + x, myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x00B6, x);
        if (myMapper->readCPU(0x007D) != 0) {
            goto L_000699;
        }
        opEOR(0x40);
    L_000699:
        x = myMapper->readCPU(0x00B6);
        myMapper->writeCPU(0x0702 + x, a);
        opINY(1);
        opINX(4);
    } while (y != 0x08);
    popAddress();
}

void game::SUB_0006C8() {
    if (myMapper->readCPU(0x007D) == 0) {
        goto L_0006FB;
    }
    a = myMapper->readCPU(0x0015);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0703, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0707, a);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x070B, a);
    a = myMapper->readCPU(0x0016);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0704, a);
    myMapper->writeCPU(0x0708, a);
    a = myMapper->readCPU(0x000B);
    opAND(0x06);
    opLSR_A(2);
    flgC = false;
    opADC(0x50);
    myMapper->writeCPU(0x0709, a);
    popAddress();
    return;
L_0006FB:
    a = myMapper->readCPU(0x0015);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0703, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x070B, a);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x0707, a);
    a = myMapper->readCPU(0x0016);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0704, a);
    myMapper->writeCPU(0x0708, a);
    a = myMapper->readCPU(0x000B);
    opAND(0x06);
    opLSR_A(2);
    flgC = false;
    opADC(0x50);
    myMapper->writeCPU(0x0709, a);
    popAddress();
}

void game::SUB_00072A() {
    if (myMapper->readCPU(0x0036) == 0) {
        goto L_00072F;
    }
    popAddress();
    return;
L_00072F:
    pushAddress(0x00072F);
    SUB_000993();
    if (poppedEntry.value != 0x00072F) return;
    pushAddress(0x000732);
    SUB_0008F6();
    if (poppedEntry.value != 0x000732) return;
    pushAddress(0x000735);
    SUB_000745();
    if (poppedEntry.value != 0x000735) return;
    pushAddress(0x000738);
    SUB_000D0A();
    if (poppedEntry.value != 0x000738) return;
    pushAddress(0x00073B);
    SUB_00140F();
    if (poppedEntry.value != 0x00073B) return;
    a = myMapper->readCPU(0x0032);
    opAND(0x7F);
    myMapper->writeCPU(0x0032, a);
    popAddress();
}

void game::SUB_000745() {
    if (myMapper->readCPU(0x0047) == 0) {
        goto L_00074F;
    }
    a = 0x16;
    setLoadFlag(a);
    myMapper->writeCPU(0x003F, a);
    if (!flgZ) {
        goto L_000759;
    }
L_00074F:
    if (myMapper->readCPU(0x004E) == 0x80) {
        myMapper->writeCPU(0x003F, 0x17);
    L_000759:
        myMapper->writeCPU(0x0044, 0x01);
    }
    if (myMapper->readCPU(0x0044) == 0) {
        if (myMapper->readCPU(0x0055) != 0) {
            goto L_00079D;
        }
        a = myMapper->readCPU(0x0057);
        opAND(0x7E);
        x = a;
        myMapper->writeCPU(0x00B1, myMapper->readCPU(0x87AC + x));
        myMapper->writeCPU(0x00B2, myMapper->readCPU(0x87AD + x));
        y = myMapper->readCPU(0x0050);
        a = myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y);
        if (a == 0xFF) {
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0050, a);
            if (flgZ) {
                goto L_00079D;
            }
        }
        myMapper->writeCPU(0x0044, a);
        a = myMapper->readCPU(0x0057);
        opAND(0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x0044);
            opAND(0x0F);
            myMapper->writeCPU(0x0044, a);
        }
        opINY(1);
        myMapper->writeCPU(0x003F, myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0055, myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0050, y);
    }
L_00079D:
    if (myMapper->readCPU(0x0055) != 0) {
        opDEC(0x0055, 1);
        if (flgZ) {
            if (myMapper->readCPU(0x003F) != 0) {
                goto L_0007AB;
            }
            opDEC(0x0044, 1);
        }
    }
L_0007AB:
    popAddress();
}

void game::SUB_0008F6() {
    if (myMapper->readCPU(0x0044) & 0x80) {
        goto L_000927;
    }
    a = myMapper->readCPU(0x0057);
    opAND(0x1E);
    x = a;
    myMapper->writeCPU(0x00AD, myMapper->readCPU(0x89F8 + x));
    myMapper->writeCPU(0x00AE, myMapper->readCPU(0x89F9 + x));
    a = myMapper->readCPU(0x0040);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00B1, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x00B2, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
    y = 0x00;
    do {
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y);
            if (a != 0xFF) {
                goto L_000934;
            }
            x = 0x00;
            if (myMapper->readCPU(0x007D) != 0) {
                goto L_000925;
            }
            opINX(1);
        L_000925:
            myMapper->writeCPU((0x0051 + x) & 0x00ff, a);
        L_000927:
            popAddress();
            return;
        L_000928:
            opINY(2);
            a = myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y);
            opINY(1);
        } while (a != 0x1E);
        opINY(1);
    } while (!flgZ);
L_000934:
    a = myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B4, a);
    flgC = true;
    opSBC(myMapper->readCPU(0x0075));
    if (myMapper->readCPU(0x007D) != 0) {
        if (a < 0xFE) {
            goto L_000928;
        }
        a = myMapper->readCPU(0x00B4);
        opCMP(a, myMapper->readCPU(0x0051));
        if (flgZ) {
            SUB_000992();
            return;
        }
        myMapper->writeCPU(0x0051, a);
        if (!flgZ) {
            goto L_000959;
        }
    }
    if (a >= 0x03) {
        goto L_000928;
    }
    a = myMapper->readCPU(0x00B4);
    if (a == myMapper->readCPU(0x0052)) {
        SUB_000992();
        return;
    }
    myMapper->writeCPU(0x0052, a);
L_000959:
    myMapper->writeCPU(0x0044, 0x81);
    myMapper->writeCPU(0x0041, myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0042, myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x003F, a);
    if (a != 0x1E) {
        goto L_000974;
    }
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00B1) + (myMapper->readCPU((0x00B1 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x005D, a);
L_000974:
    if (a != 0x15) {
        goto L_000984;
    }
    a = myMapper->readCPU(0x0057);
    opAND(0x01);
    if (flgZ) {
        SUB_000992();
        return;
    }
    do {
        a = 0x00;
        myMapper->writeCPU(0x0044, a);
        myMapper->writeCPU(0x003F, a);
    L_000984:
        if (a != 0x11) {
            SUB_000992();
            return;
        }
    } while (myMapper->readCPU(0x005E) >= myMapper->readCPU(0x0057));
    myMapper->writeCPU(0x005E, myMapper->readCPU(0x0057));
    SUB_000992();
    return;
}

void game::SUB_000992() {
    popAddress();
}

void game::SUB_000993() {
    a = myMapper->readCPU(0x0044);
    setLoadFlag(a);
    if (flgN) {
        SUB_000992();
        return;
    }
    opCMP(a, 0x40);
    a = 0x00;
    if (flgC) {
        a = 0x80;
    }
    myMapper->writeCPU(0x0060, a);
    a = myMapper->readCPU(0x007D);
    opASL_A(1);
    y = myMapper->readCPU(0x0074);
    myMapper->writeCPU(0x0041, myMapper->readCPU(0x0075));
    a = myMapper->readCPU(0x0082);
    opBIT(myMapper->readCPU(0x0060));
    if (!flgN) {
        if (!flgC) {
            goto L_0009E1;
        }
        if (flgC) {
            goto L_0009B6;
        }
    }
    if (!flgC) {
    L_0009B6:
        x = myMapper->readCPU(0x0086);
        a = myMapper->readCPU(0x0041);
        flgC = false;
        opADC(0xFF);
        myMapper->writeCPU(0x0041, a);
        a = myMapper->readCPU(0x0072);
        opADC(0x00);
        opCMP(a, myMapper->readCPU(0x89F6 + x));
        opAND(myMapper->readCPU(0x89F4 + x));
        y = a;
        a = myMapper->readCPU(0x0080);
        if (flgC) {
            y = 0x00;
            if (y != myMapper->readCPU(0x0040)) {
                myMapper->writeCPU(0x0051, y);
                myMapper->writeCPU(0x0052, y);
            }
            flgC = false;
            opADC(0x01);
            if (a >= 0x40) {
                a = 0x00;
            }
        }
    }
L_0009E1:
    myMapper->writeCPU(0x0040, y);
    if (a != myMapper->readCPU(0x0057)) {
        myMapper->writeCPU(0x0057, a);
        myMapper->writeCPU(0x0050, 0x00);
    }
    a = myMapper->readCPU(0x0057);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0009F3;
    }
    myMapper->writeCPU(0x005E, a);
L_0009F3:
    popAddress();
}

void game::SUB_000D0A() {
    a = 0x00;
    myMapper->writeCPU(0x0043, a);
    myMapper->writeCPU(0x005C, a);
    myMapper->writeCPU(0x005F, 0xFF);
    x = myMapper->readCPU(0x0043);
    if (myMapper->readCPU(0x0209 + x) == 0) {
        if (myMapper->readCPU(0x0044) != 0) {
            goto L_000D22;
        }
        do {
            goto L_000D6C;
        L_000D22:
            a = myMapper->readCPU(0x003F);
            opAND(0x7F);
        } while (a >= 0x1F);
        if (x >= 0x80) {
            if (a >= 0x16) {
                goto L_000D4E;
            }
        }
        else {
            if (a >= 0x16) {
                goto L_000D6C;
            }
            if (a != 0x04) {
                if (a >= 0x09) {
                    goto L_000D4E;
                }
                a = myMapper->readCPU(0x0081);
                opLSR_A(1);
                opAND(0x0F);
                y = a;
                if (myMapper->readCPU(0x005C) >= myMapper->readCPU(0x8DFA + y)) {
                    goto L_000D6C;
                }
            }
        L_000D4E:
            myMapper->writeCPU(0x0201 + x, myMapper->readCPU(0x0041));
            myMapper->writeCPU(0x020E + x, myMapper->readCPU(0x0040));
            a = myMapper->readCPU(0x003F);
            myMapper->writeCPU(0x0209 + x, a);
            opAND(0x7F);
            if (a != 0x04) {
                if (a < 0x09) {
                    goto L_000D6C;
                }
            }
            myMapper->writeCPU(0x0203 + x, myMapper->readCPU(0x0042));
        }
    }
L_000D6C:
    a = 0x8D;
    opPHA();
    a = 0xB0;
    opPHA();
    pushAddress(0x000D72);
    SUB_003013();
    if (poppedEntry.value != 0x000D72) return;
    a = myMapper->readCPU(0x006A);
    setLoadFlag(a);
    if (!flgZ) {
        opAND(0x7F);
        if (a < 0x09) {
            if (a == 0x04) {
                goto L_000D8D;
            }
            opINC(0x005C, 1);
            if (myMapper->readCPU(0x006F) != 0) {
                myMapper->writeCPU(0x005F, myMapper->readCPU(0x0043));
            }
        }
    L_000D8D:
        if (!(myMapper->readCPU(0x0061) & 0x80)) {
            goto L_000E46;
        }
        pushAddress(0x000D94);
        SUB_00311B();
        if (poppedEntry.value != 0x000D94) return;
        a = myMapper->readCPU(0x0061);
        opAND(0x40);
        if (!flgZ) {
            SUB_002FE4();
            return;
        }
        a = myMapper->readCPU(0x006A);
        setLoadFlag(a);
        if (!flgZ) {
            opAND(0x7F);
            opASL_A(1);
            x = a;
            a = myMapper->readCPU(0x8E09 + x);
            opPHA();
            a = myMapper->readCPU(0x8E08 + x);
            opPHA();
        }
    }
    popAddress();
    return;
L_000E46:
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    x = a;
    if (x != 0x16) {
        if (x == 0x17) {
            goto L_000EA4;
        }
        if (x == 0x1E) {
            goto L_000EC3;
        }
        if (x == 0x15) {
            myMapper->writeCPU(0x004E, 0x00);
        }
        if (x != 0x04) {
            opCMP(x, 0x09);
            if (!flgC) {
                if (myMapper->readCPU(0x0045) != 0) {
                    goto L_000E8F;
                }
                a = myMapper->readCPU(0x00A8);
                opAND(0x1F);
                opADC(myMapper->readCPU(0x8EF3 + x));
                myMapper->writeCPU(0x0045, a);
                a = myMapper->readCPU(0x00A8);
                opAND(myMapper->readCPU(0x8E92 + x));
                opORA(myMapper->readCPU(0x8E9B + x));
                myMapper->writeCPU(0x0064, a);
            }
        }
        pushAddress(0x000E7E);
        SUB_000ECD();
        if (poppedEntry.value != 0x000E7E) return;
        if (myMapper->readCPU(0x006A) == 0x0A) {
            a = myMapper->readCPU(0x00A8);
            opAND(0x20);
            opORA(myMapper->readCPU(0x0061));
            myMapper->writeCPU(0x0061, a);
        }
    L_000E8F:
        opDEC(0x0045, 1);
        popAddress();
        return;
    }
L_000EA4:
    myMapper->writeCPU(0x0062, myMapper->readCPU(0x0048));
    myMapper->writeCPU(0x0064, myMapper->readCPU(0x0049));
    myMapper->writeCPU(0x006F, myMapper->readCPU(0x004A));
    pushAddress(0x000EB0);
    SUB_000ECD();
    if (poppedEntry.value != 0x000EB0) return;
    if (myMapper->readCPU(0x006A) == 0x17) {
        goto L_000EBE;
    }
    myMapper->writeCPU(0x0047, 0x00);
    popAddress();
    return;
L_000EBE:
    myMapper->writeCPU(0x004E, 0xC0);
    popAddress();
    return;
L_000EC3:
    pushAddress(0x000EC3);
    SUB_000ECD();
    if (poppedEntry.value != 0x000EC3) return;
    opDEC(0x0045, 1);
    myMapper->writeCPU(0x006C, myMapper->readCPU(0x005D));
    popAddress();
}

void game::SUB_000ECD() {
    opINC(0x0053, 1);
    opDEC(0x0044, 1);
    a = myMapper->readCPU(0x0044);
    opAND(0x7F);
    myMapper->writeCPU(0x0044, a);
    SUB_000ED7();
    return;
}

void game::SUB_000ED7() {
    a = myMapper->readCPU(0x007D);
    opASL_A(1);
    a = 0x20;
    opROL_A(2);
    opEOR(0x02);
    myMapper->writeCPU(0x0061, a);
    a = myMapper->readCPU(0x0044);
    opAND(0x40);
    if (!flgZ) {
        if (!(myMapper->readCPU(0x0060) & 0x80)) {
            goto L_000EF2;
        }
        a = myMapper->readCPU(0x0061);
        opEOR(0x02);
        myMapper->writeCPU(0x0061, a);
    }
L_000EF2:
    popAddress();
}

void game::SUB_00140F() {
    x = 0x0C;
    y = 0x06;
    myMapper->writeCPU(0x00B4, 0xF6);
    if (myMapper->readCPU(0x0058) != 0) {
        a = myMapper->readCPU(0x007D);
        opASL_A(1);
        a = myMapper->readCPU(0x007A);
        if (!flgC) {
            goto L_001425;
        }
        pushAddress(0x001422);
        SUB_002DBD();
        if (poppedEntry.value != 0x001422) return;
    L_001425:
        flgC = false;
        opADC(myMapper->readCPU(0x0059));
        myMapper->writeCPU(0x0059, a);
        do {
            a = myMapper->readCPU(0x0059);
            flgC = false;
            opADC(myMapper->readCPU(0x9462 + y));
            myMapper->writeCPU(0x072B + x, a);
            a = myMapper->readCPU(0x005A);
            flgC = false;
            opADC(myMapper->readCPU(0x9463 + y));
            myMapper->writeCPU(0x0728 + x, a);
            myMapper->writeCPU(0x0729 + x, myMapper->readCPU(0x00B4));
            myMapper->writeCPU(0x072A + x, 0x01);
            opDEC(0x00B4, 1);
            opDEX(4);
            opDEY(2);
        } while (!flgN);
        opDEC(0x0058, 1);
        popAddress();
        return;
    }
    a = 0xF8;
    do {
        myMapper->writeCPU(0x0728 + x, a);
        myMapper->writeCPU(0x072B + x, a);
        opDEX(4);
    } while (!flgN);
    popAddress();
}

void game::SUB_001493() {
    if (myMapper->readCPU(0x0097) != 0) {
        goto L_0014A4;
    }
    if (myMapper->readCPU(0x0091) == 0) {
        a = myMapper->readCPU(0x0014);
        opAND(0x40);
        if (!flgZ) {
            goto L_0014A4;
        }
        pushAddress(0x0014A1);
        SUB_0014AB();
        if (poppedEntry.value != 0x0014A1) return;
    }
L_0014A4:
    pushAddress(0x0014A4);
    SUB_001574();
    if (poppedEntry.value != 0x0014A4) return;
    pushAddress(0x0014A7);
    SUB_00161C();
    if (poppedEntry.value != 0x0014A7) return;
    popAddress();
}

void game::SUB_0014AB() {
    a = myMapper->readCPU(0x0002);
    opAND(0x40);
    if (!flgZ) {
        a = myMapper->readCPU(0x0002);
        opAND(0x08);
        if (!flgZ) {
            goto L_00154F;
        }
    }
    if (myMapper->readCPU(0x0003) & 0x80) {
    }
    else {
    L_0014C1:
        a = myMapper->readCPU(0x0032);
        opAND(0x0F);
        myMapper->writeCPU(0x0032, a);
        popAddress();
        return;
    }
    x = 0x00;
    do {
        if (myMapper->readCPU((0x001B + x) & 0x00ff) & 0x80) {
            goto L_00150F;
        }
        a = 0x08;
        pushAddress(0x0014D0);
        SUB_0051A5();
        if (poppedEntry.value != 0x0014D0) return;
        pushAddress(0x0014D3);
        SUB_00156D();
        if (poppedEntry.value != 0x0014D3) return;
        a = myMapper->readCPU(0x0016);
        myMapper->writeCPU((0x001D + x) & 0x00ff, a);
        myMapper->writeCPU(0x0710 + x, a);
        a = myMapper->readCPU(0x0015);
        myMapper->writeCPU((0x001C + x) & 0x00ff, a);
        myMapper->writeCPU(0x0713 + x, a);
        myMapper->writeCPU(0x0711 + x, 0x06);
        if (myMapper->readCPU(0x007D) != 0) {
            a = 0x40;
            setLoadFlag(a);
            myMapper->writeCPU(0x0712 + x, a);
            if (!flgZ) {
                goto L_0014F9;
            }
        }
        myMapper->writeCPU(0x0712 + x, 0x00);
    L_0014F9:
        if (myMapper->readCPU(0x007D) != 0) {
            a = 0x02;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001503;
            }
        }
        a = 0x04;
    L_001503:
        opAND(0x06);
        if (!flgC) {
            goto L_001509;
        }
        opORA(0x40);
    L_001509:
        opORA(0x80);
        myMapper->writeCPU((0x001B + x) & 0x00ff, a);
        if (!flgZ) {
            goto L_001517;
        }
    L_00150F:
        opINX(4);
        opCMP(x, 0x08);
    } while (!flgC);
L_001517:
    if (!(myMapper->readCPU(0x0027) & 0x80)) {
        a = myMapper->readCPU(0x0016);
        myMapper->writeCPU(0x0029, a);
        myMapper->writeCPU(0x071C, a);
        a = myMapper->readCPU(0x0015);
        myMapper->writeCPU(0x0028, a);
        myMapper->writeCPU(0x071F, a);
        myMapper->writeCPU(0x071D, 0x08);
        if (myMapper->readCPU(0x007D) != 0) {
            a = 0x02;
            setLoadFlag(a);
            myMapper->writeCPU(0x071E, a);
            if (!flgZ) {
                goto L_00153E;
            }
        }
        myMapper->writeCPU(0x071E, 0x42);
    L_00153E:
        a = myMapper->readCPU(0x007D);
        opROL_A(2);
        opEOR(0x01);
        opAND(0x01);
        opORA(0x80);
        myMapper->writeCPU(0x0027, a);
        if (flgZ) {
        }
    }
    goto L_0014C1;
L_00154F:
    if (myMapper->readCPU(0x0094) == 0) {
        if (myMapper->readCPU(0x0036) != 0) {
            goto L_00156C;
        }
        a = myMapper->readCPU(0x0035);
        if (a >= 0x30) {
            flgC = true;
            opSBC(0x06);
            myMapper->writeCPU(0x0035, a);
            a = myMapper->readCPU(0x0032);
            opAND(0xC0);
            if (!flgZ) {
                goto L_00156C;
            }
            opORA(0xC0);
            myMapper->writeCPU(0x0032, a);
        }
    }
L_00156C:
    popAddress();
}

void game::SUB_00156D() {
    opINC(0x002B, 1);
    if (!flgZ) {
        goto L_001573;
    }
    opINC(0x002C, 1);
L_001573:
    popAddress();
}

void game::SUB_001574() {
    y = 0x00;
    do {
        if (!(myMapper->readCPU(0x001B + y) & 0x80)) {
            goto L_0015D4;
        }
        a = myMapper->readCPU(0x001B + y);
        opAND(0x10);
        if (!flgZ) {
            a = myMapper->readCPU(0x001B + y);
            opAND(0x08);
            if (flgZ) {
                if (myMapper->readCPU(0x007D) == 0) {
                    goto L_00159A;
                }
                a = myMapper->readCPU(0x001B + y);
                opAND(0xF0);
                opORA(0x04);
                myMapper->writeCPU(0x001B + y, a);
                goto L_0015A4;
            L_00159A:
                a = myMapper->readCPU(0x001B + y);
                opAND(0xF0);
                opORA(0x02);
                myMapper->writeCPU(0x001B + y, a);
            }
        }
    L_0015A4:
        a = myMapper->readCPU(0x001B + y);
        opAND(0x07);
        opASL_A(1);
        x = a;
        a = myMapper->readCPU(0x96A1 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x001C + y));
        myMapper->writeCPU(0x001C + y, a);
        myMapper->writeCPU(0x0713 + y, a);
        a = myMapper->readCPU(0x96A2 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x001D + y));
        myMapper->writeCPU(0x001D + y, a);
        flgC = true;
        opSBC(0x03);
        myMapper->writeCPU(0x0710 + y, a);
        a = myMapper->readCPU(0x000B);
        opLSR_A(2);
        opAND(0x01);
        flgC = false;
        opADC(0x06);
        myMapper->writeCPU(0x0711 + y, a);
    L_0015D4:
        opINY(4);
    } while (y < 0x08);
    a = myMapper->readCPU(0x0027);
    setLoadFlag(a);
    if (!flgN) {
        goto L_00161B;
    }
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0x96B1 + x));
    myMapper->writeCPU(0x00B5, myMapper->readCPU(0x96B2 + x));
    a = myMapper->readCPU(0x002D);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00B6, myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x00B7, myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0028);
    flgC = false;
    opADC(myMapper->readCPU(0x00B6));
    myMapper->writeCPU(0x0028, a);
    myMapper->writeCPU(0x071F, a);
    a = myMapper->readCPU(0x0029);
    flgC = false;
    opADC(myMapper->readCPU(0x00B7));
    myMapper->writeCPU(0x0029, a);
    myMapper->writeCPU(0x071C, a);
    opINC(0x002D, 1);
    a = myMapper->readCPU(0x000B);
    opLSR_A(2);
    opAND(0x01);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x071D, a);
L_00161B:
    popAddress();
}

void game::SUB_00161C() {
    a = myMapper->readCPU(0x0015);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x00B4, a);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x00B5, a);
    a = myMapper->readCPU(0x0016);
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x00B6, a);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x00B7, a);
    y = 0x00;
    do {
        a = myMapper->readCPU(0x001B + y);
        opAND(0x20);
        if (!flgZ) {
            a = myMapper->readCPU(0x001C + y);
            if (a < myMapper->readCPU(0x00B4)) {
                if (a < myMapper->readCPU(0x00B5)) {
                    goto L_00165A;
                }
                a = myMapper->readCPU(0x001D + y);
                if (a < myMapper->readCPU(0x00B6)) {
                    if (a < myMapper->readCPU(0x00B7)) {
                        goto L_00165A;
                    }
                    a = myMapper->readCPU(0x0014);
                    opORA(myMapper->readCPU(0x00F5));
                    myMapper->writeCPU(0x0014, a);
                    popAddress();
                    return;
                }
            }
        }
    L_00165A:
        if (myMapper->readCPU(0x001B + y) & 0x80) {
            if (myMapper->readCPU(0x001C + y) >= 0xF8) {
                goto L_00166D;
            }
            if (myMapper->readCPU(0x001D + y) < 0xF8) {
                goto L_00167A;
            }
        L_00166D:
            myMapper->writeCPU(0x001B + y, 0x00);
            a = 0xF8;
            myMapper->writeCPU(0x0710 + y, a);
            myMapper->writeCPU(0x0713 + y, a);
        }
    L_00167A:
        opINY(4);
    } while (y < 0x08);
    if (myMapper->readCPU(0x0027) & 0x80) {
        if (myMapper->readCPU(0x0028) >= 0xF8) {
            goto L_001692;
        }
        if (myMapper->readCPU(0x0029) < 0xF8) {
            goto L_0016A0;
        }
    L_001692:
        a = 0x00;
        myMapper->writeCPU(0x0027, a);
        myMapper->writeCPU(0x002D, a);
        a = 0xF8;
        myMapper->writeCPU(0x071C, a);
        myMapper->writeCPU(0x071F, a);
    }
L_0016A0:
    popAddress();
}

void game::SUB_0017A5() {
    if (myMapper->readCPU(0x0036) != 0) {
        goto L_0017AF;
    }
    pushAddress(0x0017A9);
    SUB_001830();
    if (poppedEntry.value != 0x0017A9) return;
    pushAddress(0x0017AC);
    SUB_0018E8();
    if (poppedEntry.value != 0x0017AC) return;
L_0017AF:
    popAddress();
}

void game::SUB_001830() {
    x = 0x00;
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(0x02A0 + x);
        opORA(myMapper->readCPU(0x02A1 + x));
        if (flgZ) {
            a = 0xF8;
            setLoadFlag(a);
            myMapper->writeCPU(0x07D0 + y, a);
            myMapper->writeCPU(0x07D3 + y, a);
            if (!flgZ) {
                goto L_00189D;
            }
        }
        if (myMapper->readCPU(0x02A3 + x) == 0x80) {
            goto L_0018BA;
        }
        a = myMapper->readCPU(0x02A4 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x02A6 + x));
        myMapper->writeCPU(0x02A4 + x, a);
        a = myMapper->readCPU(0x02A0 + x);
        opADC(myMapper->readCPU(0x02A2 + x));
        myMapper->writeCPU(0x02A0 + x, a);
        a = myMapper->readCPU(0x007D);
        opASL_A(1);
        a = myMapper->readCPU(0x007A);
        if (!flgC) {
            goto L_00186D;
        }
        pushAddress(0x00186A);
        SUB_002DBD();
        if (poppedEntry.value != 0x00186A) return;
    L_00186D:
        flgC = false;
        opADC(myMapper->readCPU(0x02A0 + x));
        myMapper->writeCPU(0x02A0 + x, a);
        myMapper->writeCPU(0x07D3 + y, a);
        a = myMapper->readCPU(0x02A5 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x02A7 + x));
        myMapper->writeCPU(0x02A5 + x, a);
        a = myMapper->readCPU(0x02A1 + x);
        opADC(myMapper->readCPU(0x02A3 + x));
        myMapper->writeCPU(0x02A1 + x, a);
        myMapper->writeCPU(0x07D0 + y, a);
        a = myMapper->readCPU(0x000B);
        opLSR_A(1);
        opAND(0x01);
        flgC = false;
        opADC(0x39);
        myMapper->writeCPU(0x07D1 + y, a);
        myMapper->writeCPU(0x07D2 + y, 0x02);
    L_00189D:
        myMapper->writeCPU(0x07D3 + y, myMapper->readCPU(0x02A0 + x));
        myMapper->writeCPU(0x07D0 + y, myMapper->readCPU(0x02A1 + x));
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        opINY(4);
        if (x >= 0x20) {
            goto L_0018B9;
        }
    }
L_0018B9:
    popAddress();
    return;
L_0018BA:
    a = y;
    opPHA();
    y = myMapper->readCPU(0x02A2 + x);
    a = myMapper->readCPU(0x02A0 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x99B2 + y));
    myMapper->writeCPU(0x02A0 + x, a);
    a = myMapper->readCPU(0x02A1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x99BA + y));
    myMapper->writeCPU(0x02A1 + x, a);
    opPLA();
    y = a;
    a = myMapper->readCPU(0x000B);
    opLSR_A(1);
    opAND(0x01);
    flgC = false;
    opADC(0x37);
    myMapper->writeCPU(0x07D1 + y, a);
    myMapper->writeCPU(0x07D2 + y, 0x00);
    goto L_00189D;
}

void game::SUB_0018E8() {
    x = 0x00;
    do {
        a = myMapper->readCPU(0x02A0 + x);
        opORA(myMapper->readCPU(0x02A1 + x));
        if (!flgZ) {
            a = myMapper->readCPU(0x02A0 + x);
            if (a >= 0x08) {
                if (a >= 0xF8) {
                    goto L_001908;
                }
                a = myMapper->readCPU(0x02A1 + x);
                if (a < 0x30) {
                    goto L_001908;
                }
                if (a < 0xD0) {
                    goto L_001918;
                }
            }
        L_001908:
            a = 0x00;
            myMapper->writeCPU(0x02A0 + x, a);
            myMapper->writeCPU(0x02A1 + x, a);
            a = 0xF8;
            myMapper->writeCPU(0x07D0 + x, a);
            myMapper->writeCPU(0x07D3 + x, a);
        }
    L_001918:
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
    } while (x < 0x20);
    popAddress();
}

void game::SUB_00197B() {
    myMapper->writeCPU(0x00B8, 0x00);
    a = myMapper->readCPU(0x0015);
    flgC = true;
    opSBC(myMapper->readCPU(0x0062));
    pushStatus();
    pushAddress(0x001985);
    SUB_002DBB();
    if (poppedEntry.value != 0x001985) return;
    myMapper->writeCPU(0x00B4, a);
    popStatus();
    if (flgC) {
        myMapper->writeCPU(0x00B8, 0x02);
    }
    a = myMapper->readCPU(0x0016);
    flgC = true;
    opSBC(myMapper->readCPU(0x0064));
    pushStatus();
    pushAddress(0x001997);
    SUB_002DBB();
    if (poppedEntry.value != 0x001997) return;
    popStatus();
    myMapper->writeCPU(0x00B5, a);
    if (flgC) {
        a = myMapper->readCPU(0x00B8);
        opORA(0x04);
        myMapper->writeCPU(0x00B8, a);
    }
    if (myMapper->readCPU(0x00B4) >= myMapper->readCPU(0x00B5)) {
        goto L_0019B1;
    }
    a = myMapper->readCPU(0x00B8);
    opORA(0x01);
    myMapper->writeCPU(0x00B8, a);
L_0019B1:
    popAddress();
}

void game::SUB_0019C2() {
    pushStatus();
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x00B4);
    opPHA();
    a = myMapper->readCPU(0x00B5);
    opPHA();
    myMapper->writeCPU(0x4014, 0x07);
    a = myMapper->readCPU(0x0033);
    opAND(0x01);
    if (flgZ) {
        a = myMapper->readCPU(0x0000);
        opAND(0x03);
        if (flgZ) {
            pushAddress(0x0019DF);
            SUB_002A02();
            if (poppedEntry.value != 0x0019DF) return;
        }
        else {
            if (a != 0x01) {
                goto L_0019F2;
            }
            pushAddress(0x0019E9);
            SUB_002D2A();
            if (poppedEntry.value != 0x0019E9) return;
            pushAddress(0x0019EC);
            SUB_001A20();
            if (poppedEntry.value != 0x0019EC) return;
            goto L_001A05;
        L_0019F2:
            if (a == 0x02) {
                pushAddress(0x0019F6);
                SUB_002A46();
                if (poppedEntry.value != 0x0019F6) return;
            }
            else {
                pushAddress(0x0019FC);
                SUB_002C86();
                if (poppedEntry.value != 0x0019FC) return;
                pushAddress(0x0019FF);
                SUB_001A26();
                if (poppedEntry.value != 0x0019FF) return;
                goto L_001A05;
            }
        }
    L_001A05:
        a = myMapper->readCPU(0x0033);
        opAND(0x02);
        if (!flgZ) {
            goto L_001A0E;
        }
        pushAddress(0x001A0B);
        SUB_001F3F();
        if (poppedEntry.value != 0x001A0B) return;
    }
L_001A0E:
    opINC(0x0000, 1);
    a = myMapper->readCPU(0x2002);
    opPLA();
    myMapper->writeCPU(0x00B5, a);
    opPLA();
    myMapper->writeCPU(0x00B4, a);
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    return;
}

void game::SUB_001A20() {
    x = 0x10;
    do {
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_001A26() {
    x = 0x14;
    do {
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_001A2C() {
    a = x;
    opPHA();
    a = myMapper->readCPU(0x00B4);
    opPHA();
    a = myMapper->readCPU(0x0002);
    opPHA();
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    x = 0x07;
    myMapper->writeCPU(0x0002, 0x00);
    flgC = false;
    do {
        a = myMapper->readCPU(0x4016);
        myMapper->writeCPU(0x0007, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0007));
        opAND(0x01);
        opORA(myMapper->readCPU(0x0002));
        opASL_A(1);
        myMapper->writeCPU(0x0002, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x4016);
    myMapper->writeCPU(0x0007, a);
    opLSR_A(1);
    opORA(myMapper->readCPU(0x0007));
    opAND(0x01);
    opORA(myMapper->readCPU(0x0002));
    myMapper->writeCPU(0x0002, a);
    x = a;
    opPLA();
    myMapper->writeCPU(0x00B4, a);
    a = x;
    opORA(myMapper->readCPU(0x00B4));
    opEOR(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x0004);
    opPHA();
    x = 0x01;
    myMapper->writeCPU(0x4017, x);
    opDEX(1);
    myMapper->writeCPU(0x4017, x);
    x = 0x07;
    myMapper->writeCPU(0x0004, 0x00);
    flgC = false;
    do {
        a = myMapper->readCPU(0x4017);
        myMapper->writeCPU(0x0008, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0008));
        opAND(0x01);
        opORA(myMapper->readCPU(0x0004));
        opASL_A(1);
        myMapper->writeCPU(0x0004, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x4017);
    myMapper->writeCPU(0x0008, a);
    opLSR_A(1);
    opORA(myMapper->readCPU(0x0008));
    opAND(0x01);
    opORA(myMapper->readCPU(0x0004));
    myMapper->writeCPU(0x0004, a);
    x = a;
    opPLA();
    myMapper->writeCPU(0x00B4, a);
    a = x;
    opORA(myMapper->readCPU(0x00B4));
    opEOR(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x0005, a);
    a = myMapper->readCPU(0x0004);
    opAND(0xCF);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0x0005);
    opAND(0xCF);
    myMapper->writeCPU(0x0005, a);
    if (myMapper->readCPU(0x0030) == 0) {
        goto L_001AD0;
    }
    a = myMapper->readCPU(0x0002);
    opAND(0x30);
    opORA(myMapper->readCPU(0x0004));
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0x0003);
    opAND(0x30);
    opORA(myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x0003, a);
    goto L_001AE0;
L_001AD0:
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
    a = myMapper->readCPU(0x0002);
L_001AE0:
    opPLA();
    myMapper->writeCPU(0x00B4, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_001AE6() {
    myMapper->writeCPU(0x007D, 0x80);
    x = 0x05;
    myMapper->writeCPU(0x0087, x);
    opDEX(1);
    myMapper->writeCPU(0x0088, x);
    opDEX(1);
    myMapper->writeCPU(0x0089, x);
    opDEX(1);
    myMapper->writeCPU(0x0072, x);
    myMapper->writeCPU(0x008A, x);
    opDEX(1);
    myMapper->writeCPU(0x0079, x);
    myMapper->writeCPU(0x0073, x);
    myMapper->writeCPU(0x008F, x);
    opDEX(1);
    myMapper->writeCPU(0x0074, x);
    myMapper->writeCPU(0x0075, x);
    myMapper->writeCPU(0x0078, 0x88);
    a = myMapper->readCPU(0x0081);
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0082, a);
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x008D, a);
    myMapper->writeCPU(0x008E, a);
    popAddress();
}

void game::SUB_001B1E() {
    if (myMapper->readCPU(0x007D) != 0) {
        goto L_001B28;
    }
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x00B4, a);
    if (!flgZ) {
        goto L_001B2E;
    }
L_001B28:
    a = 0x02;
    myMapper->writeCPU(0x00B4, 0x02);
L_001B2E:
    a = 0x40;
    flgC = false;
    opADC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x00B6, a);
    a = myMapper->readCPU(0x0002);
    opAND(0x40);
    myMapper->writeCPU(0x00B5, a);
    a = myMapper->readCPU(0x0003);
    opAND(myMapper->readCPU(0x00B4));
    flgC = false;
    opADC(myMapper->readCPU(0x00B5));
    if (a == myMapper->readCPU(0x00B6)) {
        a = myMapper->readCPU(0x007D);
        opEOR(0x80);
        myMapper->writeCPU(0x007D, a);
    }
    else {
        a = myMapper->readCPU(0x007D);
        opORA(0x00);
        myMapper->writeCPU(0x007D, a);
        a = 0x00;
    }
    a = myMapper->readCPU(0x0094);
    opORA(myMapper->readCPU(0x0036));
    if (!flgZ) {
        myMapper->writeCPU(0x007D, 0x80);
    }
    else {
        a = 0x00;
        a = myMapper->readCPU(0x00B4);
        a = 0x00;
    }
    if (myMapper->readCPU(0x0094) == 0) {
        a = 0x00;
        a = myMapper->readCPU(0x00B4);
        a = myMapper->readCPU(0x00B4);
        a = myMapper->readCPU(0x00B4);
        a = myMapper->readCPU(0x00B4);
        a = myMapper->readCPU(0x00B4);
    }
    else {
        myMapper->writeCPU(0x007B, 0x01);
        a = 0x00;
        if (myMapper->readCPU(0x0072) != 0x06) {
            goto L_001BA1;
        }
        a = 0xC0;
        myMapper->writeCPU(0x0094, a);
        myMapper->writeCPU(0x0095, a);
        myMapper->writeCPU(0x0036, a);
        goto L_001BA1;
    }
    a = 0x00;
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    goto L_001BC2;
L_001BA1:
    if (myMapper->readCPU(0x0072) == 0x07) {
        a = myMapper->readCPU(0x0075);
        if (a == 0x00) {
            myMapper->writeCPU(0x0099, a);
            myMapper->writeCPU(0x0095, 0x80);
        }
        if (myMapper->readCPU(0x0075) == 0x80) {
            a = 0x00;
            myMapper->writeCPU(0x007B, a);
            myMapper->writeCPU(0x007F, a);
            goto L_001BCA;
        }
    }
L_001BC2:
    a = 0x00;
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
L_001BCA:
    a = myMapper->readCPU(0x007F);
    opAND(0x03);
    if (flgZ) {
        myMapper->writeCPU(0x007C, myMapper->readCPU(0x007B));
    }
    else {
        a = myMapper->readCPU(0x00B4);
        a = myMapper->readCPU(0x00B4);
        a = myMapper->readCPU(0x00B4);
    }
    x = myMapper->readCPU(0x007C);
    a = myMapper->readCPU(0x007F);
    opAND(0x01);
    if (!flgZ) {
        myMapper->writeCPU(0x007A, myMapper->readCPU(0x9B18 + x));
        opINC(0x007F, 1);
    }
    else {
        myMapper->writeCPU(0x007A, myMapper->readCPU(0x9B1B + x));
        opINC(0x007F, 1);
        a = 0x00;
    }
    myMapper->writeCPU(0x0098, 0x55);
    if (myMapper->readCPU(0x007D) == 0) {
        pushAddress(0x001C01);
        SUB_001C59();
        if (poppedEntry.value != 0x001C01) return;
    }
    else {
        a = myMapper->readCPU(0x00B4);
        pushAddress(0x001C09);
        SUB_001C2D();
        if (poppedEntry.value != 0x001C09) return;
    }
    pushAddress(0x001C0C);
    SUB_001F14();
    if (poppedEntry.value != 0x001C0C) return;
    a = myMapper->readCPU(0x0082);
    opAND(0x10);
    if (!flgZ) {
        goto L_001C1C;
    }
    myMapper->writeCPU(0x0036, 0x00);
    goto L_001C22;
L_001C1C:
    a = myMapper->readCPU(0x00B4);
    a = 0x00;
    a = myMapper->readCPU(0x00B4);
L_001C22:
    pushAddress(0x001C22);
    SUB_002260();
    if (poppedEntry.value != 0x001C22) return;
    pushAddress(0x001C25);
    SUB_002310();
    if (poppedEntry.value != 0x001C25) return;
    myMapper->writeCPU(0x00B4, 0x01);
    popAddress();
}

void game::SUB_001C2D() {
    pushAddress(0x001C2D);
    SUB_001C85();
    if (poppedEntry.value != 0x001C2D) return;
    if (myMapper->readCPU(0x007A) != 0) {
        a = myMapper->readCPU(0x0075);
        flgC = false;
        opADC(myMapper->readCPU(0x007A));
        myMapper->writeCPU(0x0075, a);
        if (myMapper->readCPU(0x0075) != myMapper->readCPU(0x0083)) {
            goto L_001C43;
        }
        opINC(0x0079, 1);
    L_001C43:
        pushAddress(0x001C43);
        SUB_001CEC();
        if (poppedEntry.value != 0x001C43) return;
        a = myMapper->readCPU(0x0098);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x0098, a);
        pushAddress(0x001C4D);
        SUB_001D35();
        if (poppedEntry.value != 0x001C4D) return;
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0098);
    flgC = false;
    opADC(0x0E);
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_001C59() {
    pushAddress(0x001C59);
    SUB_001CBC();
    if (poppedEntry.value != 0x001C59) return;
    if (myMapper->readCPU(0x007A) != 0) {
        a = myMapper->readCPU(0x0075);
        flgC = true;
        opSBC(myMapper->readCPU(0x007A));
        myMapper->writeCPU(0x0075, a);
        if (myMapper->readCPU(0x0075) != myMapper->readCPU(0x0083)) {
            goto L_001C6F;
        }
        opINC(0x0079, 1);
    L_001C6F:
        pushAddress(0x001C6F);
        SUB_001D00();
        if (poppedEntry.value != 0x001C6F) return;
        a = myMapper->readCPU(0x0098);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x0098, a);
        pushAddress(0x001C79);
        SUB_001E6D();
        if (poppedEntry.value != 0x001C79) return;
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0098);
    flgC = false;
    opADC(0x0E);
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_001C85() {
    myMapper->writeCPU(0x0083, 0x00);
    a = myMapper->readCPU(0x0075);
    opAND(0x01);
    if (flgZ) {
        goto L_001CA5;
    }
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x007A);
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x0083, a);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    popAddress();
    return;
L_001CA5:
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    popAddress();
}

void game::SUB_001CBC() {
    if (myMapper->readCPU(0x007A) == 0x01) {
        goto L_001CD7;
    }
    a = myMapper->readCPU(0x0075);
    opAND(0x01);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x007A);
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x00B4, a);
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x0083, a);
    popAddress();
    return;
L_001CD7:
    a = 0x00;
    opAND(0x01);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x007A);
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x00B4, a);
    a = 0x00;
    flgC = true;
    myMapper->writeCPU(0x0083, 0xFF);
    popAddress();
}

void game::SUB_001CEC() {
    if (myMapper->readCPU(0x0075) != myMapper->readCPU(0x0083)) {
        goto L_001CF9;
    }
    a = myMapper->readCPU(0x0078);
    opEOR(0x01);
    myMapper->writeCPU(0x0078, a);
    popAddress();
    return;
L_001CF9:
    a = 0x00;
    a = 0x00;
    a = myMapper->readCPU(0x00B4);
    popAddress();
}

void game::SUB_001D00() {
    if (myMapper->readCPU(0x0075) != myMapper->readCPU(0x0083)) {
        goto L_001D0D;
    }
    a = myMapper->readCPU(0x0078);
    opEOR(0x01);
    myMapper->writeCPU(0x0078, a);
    popAddress();
    return;
L_001D0D:
    a = 0x00;
    a = 0x00;
    a = myMapper->readCPU(0x00B4);
    popAddress();
}

void game::SUB_001D14() {
    if (myMapper->readCPU(0x000B) != 0) {
        goto L_001D2A;
    }
    if (myMapper->readCPU(0x0035) == 0) {
        goto L_001D23;
    }
    opDEC(0x0035, 1);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    popAddress();
    return;
L_001D23:
    a = myMapper->readCPU(0x0014);
    opORA(myMapper->readCPU(0x00F5));
    myMapper->writeCPU(0x0014, a);
    popAddress();
    return;
L_001D2A:
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    a = myMapper->readCPU(0x00B4);
    popAddress();
}

void game::SUB_001D35() {
    if (myMapper->readCPU(0x0075) == myMapper->readCPU(0x0083)) {
        goto L_001D42;
    }
    opDEC(0x0098, 2);
    goto L_001DA2;
L_001D42:
    myMapper->writeCPU(0x0074, myMapper->readCPU(0x0073));
    myMapper->writeCPU(0x0073, myMapper->readCPU(0x0072));
    myMapper->writeCPU(0x0082, myMapper->readCPU(0x0081));
    opDEC(0x0098, 4);
    a = myMapper->readCPU(0x0080);
    if (a != myMapper->readCPU(0x0081)) {
        myMapper->writeCPU(0x0081, a);
        myMapper->writeCPU(0x0050, 0x00);
        opDEC(0x0098, 2);
    }
    opDEC(0x0098, 2);
    opINC(0x0072, 1);
    if (myMapper->readCPU(0x0072) == 0x08) {
        opDEC(0x0098, 2);
        myMapper->writeCPU(0x0072, 0x00);
        a = myMapper->readCPU(0x0080);
        opAND(0x1F);
        if (a != 0x1E) {
            opAND(0x01);
            if (!flgZ) {
                goto L_001D8E;
            }
            opDEC(0x0098, 1);
            if (myMapper->readCPU(0x0086) == 0) {
                goto L_001D8E;
            }
        }
        opINC(0x0080, 1);
    L_001D8E:
        opINC(0x0080, 1);
        a = myMapper->readCPU(0x0080);
        opAND(0x1F);
        if (a == 0x1E) {
            opDEC(0x0098, 2);
            a = myMapper->readCPU(0x0094);
            opORA(0x80);
            myMapper->writeCPU(0x0094, a);
        }
    }
L_001DA2:
    a = myMapper->readCPU(0x008F);
    opAND(0x01);
    if (flgZ) {
        a = myMapper->readCPU(0x0083);
        flgC = true;
        opSBC(0x00);
        myMapper->writeCPU(0x0083, a);
    }
    else {
        a = myMapper->readCPU(0x0083);
        flgC = true;
        opSBC(0x80);
        myMapper->writeCPU(0x0083, a);
    }
    opDEC(0x0098, 4);
    if (myMapper->readCPU(0x0075) == myMapper->readCPU(0x0083)) {
        opINC(0x008F, 1);
        myMapper->writeCPU(0x008A, myMapper->readCPU(0x0089));
        myMapper->writeCPU(0x0089, myMapper->readCPU(0x0088));
        myMapper->writeCPU(0x0088, myMapper->readCPU(0x0087));
        myMapper->writeCPU(0x008E, myMapper->readCPU(0x008D));
        myMapper->writeCPU(0x008D, myMapper->readCPU(0x008C));
        myMapper->writeCPU(0x008C, myMapper->readCPU(0x008B));
        opDEC(0x0098, 6);
        opINC(0x0087, 1);
        if (myMapper->readCPU(0x0087) == 0x10) {
            opDEC(0x0098, 2);
            myMapper->writeCPU(0x0087, 0x00);
            a = myMapper->readCPU(0x008B);
            opAND(0x1F);
            if (a != 0x1E) {
                opAND(0x01);
                if (!flgZ) {
                    goto L_001E1E;
                }
                opDEC(0x0098, 3);
                pushAddress(0x001E0F);
                SUB_00369F();
                if (poppedEntry.value != 0x001E0F) return;
                a = 0x00;
                myMapper->writeCPU(0x0053, a);
                myMapper->writeCPU(0x0054, a);
                if (myMapper->readCPU(0x0086) == 0) {
                    goto L_001E1E;
                }
            }
            opINC(0x008B, 1);
        L_001E1E:
            opINC(0x008B, 1);
        }
    }
    if (myMapper->readCPU(0x008B) == 0x80) {
        myMapper->writeCPU(0x008B, 0x20);
    }
    if (myMapper->readCPU(0x0080) != 0x80) {
        goto L_001E34;
    }
    myMapper->writeCPU(0x0080, 0x20);
L_001E34:
    popAddress();
}

void game::SUB_001E35() {
    if (myMapper->readCPU(0x0400) != 0) {
        goto L_001E5C;
    }
    a = myMapper->readCPU(0x004F);
    opAND(0x80);
    if (!flgZ) {
        a = 0x0C;
        setLoadFlag(a);
        myMapper->writeCPU(0x003D, a);
        if (!flgZ) {
            goto L_001E51;
        }
    }
    a = myMapper->readCPU(0x0081);
    opLSR_A(1);
    opAND(0x0F);
    x = a;
    myMapper->writeCPU(0x003D, myMapper->readCPU(0x9E5D + x));
L_001E51:
    a = myMapper->readCPU(0x003D);
    if (a == myMapper->readCPU(0x003E)) {
        goto L_001E5C;
    }
    myMapper->writeCPU(0x003E, a);
    pushAddress(0x001E59);
    SUB_0051A5();
    if (poppedEntry.value != 0x001E59) return;
L_001E5C:
    popAddress();
}

void game::SUB_001E6D() {
    if (myMapper->readCPU(0x0075) == myMapper->readCPU(0x0083)) {
        goto L_001E7A;
    }
    opDEC(0x0098, 2);
    goto L_001EBB;
L_001E7A:
    opDEC(0x0098, 4);
    myMapper->writeCPU(0x0072, myMapper->readCPU(0x0073));
    myMapper->writeCPU(0x0073, myMapper->readCPU(0x0074));
    myMapper->writeCPU(0x0080, myMapper->readCPU(0x0081));
    a = myMapper->readCPU(0x0082);
    if (a != myMapper->readCPU(0x0081)) {
        myMapper->writeCPU(0x0081, a);
        myMapper->writeCPU(0x0050, 0x00);
        opDEC(0x0098, 2);
    }
    opDEC(0x0098, 2);
    if (myMapper->readCPU(0x0074) != 0) {
        opDEC(0x0074, 1);
    }
    else {
        myMapper->writeCPU(0x0074, 0x07);
        a = myMapper->readCPU(0x0082);
        opAND(0x0F);
        if (!flgZ) {
            opDEC(0x0082, 1);
            opDEC(0x0098, 2);
        }
    }
L_001EBB:
    a = myMapper->readCPU(0x008F);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x0083);
        flgC = true;
        opSBC(0x00);
        myMapper->writeCPU(0x0083, a);
    }
    else {
        a = myMapper->readCPU(0x0083);
        flgC = true;
        opSBC(0x80);
        myMapper->writeCPU(0x0083, a);
    }
    if (myMapper->readCPU(0x0075) == myMapper->readCPU(0x0083)) {
        opINC(0x008F, 1);
        opDEC(0x0098, 4);
        myMapper->writeCPU(0x0087, myMapper->readCPU(0x0088));
        myMapper->writeCPU(0x0088, myMapper->readCPU(0x0089));
        myMapper->writeCPU(0x0089, myMapper->readCPU(0x008A));
        myMapper->writeCPU(0x008B, myMapper->readCPU(0x008C));
        myMapper->writeCPU(0x008C, myMapper->readCPU(0x008D));
        myMapper->writeCPU(0x008D, myMapper->readCPU(0x008E));
        if (myMapper->readCPU(0x008A) != 0) {
            opDEC(0x008A, 1);
        }
        else {
            opDEC(0x0098, 2);
            myMapper->writeCPU(0x008A, 0x0F);
            a = myMapper->readCPU(0x008E);
            opAND(0x0F);
            if (flgZ) {
                goto L_001F13;
            }
            opDEC(0x008E, 1);
        }
    }
L_001F13:
    popAddress();
}

void game::SUB_001F14() {
    if (myMapper->readCPU(0x007D) == 0) {
        goto L_001F22;
    }
    y = myMapper->readCPU(0x0088);
    a = myMapper->readCPU(0x008C);
    opAND(0x1F);
    x = a;
    goto L_001F29;
L_001F22:
    y = myMapper->readCPU(0x008A);
    a = myMapper->readCPU(0x008E);
    opAND(0x1F);
    x = a;
L_001F29:
    a = myMapper->readCPU(0xA132 + x);
    myMapper->writeCPU(0x007E, a);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0xA152 + x));
    myMapper->writeCPU(0x00B5, myMapper->readCPU(0xA153 + x));
    a = myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0071, a);
    popAddress();
}

void game::SUB_001F3F() {
    myMapper->writeCPU(0x2001, 0x00);
    myMapper->writeCPU(0x2000, 0x0C);
    a = myMapper->readCPU(0x2002);
    a = myMapper->readCPU(0x0079);
    if (myMapper->readCPU(0x007D) != 0) {
        goto L_001F54;
    }
    opEOR(0x01);
L_001F54:
    opAND(0x01);
    opASL_A(2);
    myMapper->writeCPU(0x00B5, a);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x2006, a);
    a = 0xC0;
    flgC = false;
    opADC(myMapper->readCPU(0x0076));
    myMapper->writeCPU(0x2006, a);
    x = 0x18;
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0600 + x));
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0x0077));
    myMapper->writeCPU(0x2000, 0x08);
    a = 0x23;
    flgC = false;
    opADC(myMapper->readCPU(0x00B5));
    myMapper->writeCPU(0x00B5, a);
    x = 0x07;
    y = 0x00;
    do {
        a = myMapper->readCPU(0x2002);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B5));
        a = 0xC8;
        flgC = false;
        opADC(myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0620 + x));
        a = myMapper->readCPU(0x00B4);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x00B4, a);
        opDEX(1);
    } while (!flgZ);
    pushAddress(0x001FA9);
    SUB_0024EE();
    if (poppedEntry.value != 0x001FA9) return;
    a = 0x88;
    myMapper->writeCPU(0x00F9, a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, 0x1A);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    popAddress();
}

void game::SUB_001FC4() {
    myMapper->writeCPU(0x2001, 0x00);
    myMapper->writeCPU(0x00BB, 0x02);
    a = myMapper->readCPU(0x007D);
    opPHA();
    a = myMapper->readCPU(0x008A);
    opPHA();
    a = myMapper->readCPU(0x0089);
    opPHA();
    do {
        myMapper->writeCPU(0x007D, 0x00);
        if (myMapper->readCPU(0x00BB) == 0x02) {
            myMapper->writeCPU(0x008A, myMapper->readCPU(0x008A));
        }
        else {
            myMapper->writeCPU(0x008A, myMapper->readCPU(0x0089));
        }
        pushAddress(0x001FEB);
        SUB_001F14();
        if (poppedEntry.value != 0x001FEB) return;
        a = myMapper->readCPU(0x0071);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x00AD, myMapper->readCPU(0xA0E2 + x));
        myMapper->writeCPU(0x00AE, myMapper->readCPU(0xA0E3 + x));
        myMapper->writeCPU(0x00B4, 0x20);
        if (myMapper->readCPU(0x00BB) != 0x02) {
            goto L_00200D;
        }
        myMapper->writeCPU(0x00B5, 0xC0);
        goto L_002011;
    L_00200D:
        myMapper->writeCPU(0x00B5, 0xD0);
    L_002011:
        x = 0x18;
        do {
            a = myMapper->readCPU(0x2002);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B4));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B5));
            y = 0x00;
            do {
                myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
                opINY(1);
            } while (y != 0x10);
            a = myMapper->readCPU(0x00B5);
            flgC = false;
            opADC(0x20);
            myMapper->writeCPU(0x00B5, a);
            a = myMapper->readCPU(0x00B4);
            opADC(0x00);
            myMapper->writeCPU(0x00B4, a);
            a = myMapper->readCPU(0x00AD);
            flgC = false;
            opADC(0x10);
            myMapper->writeCPU(0x00AD, a);
            a = myMapper->readCPU(0x00AE);
            opADC(0x00);
            myMapper->writeCPU(0x00AE, a);
            opDEX(1);
        } while (!flgZ);
        opDEC(0x00BB, 1);
        a = myMapper->readCPU(0x00BB);
        setLoadFlag(a);
    } while (!flgZ);
    opPLA();
    myMapper->writeCPU(0x0089, a);
    opPLA();
    myMapper->writeCPU(0x008A, a);
    a = myMapper->readCPU(0x008A);
    opPHA();
    a = myMapper->readCPU(0x0089);
    opPHA();
    myMapper->writeCPU(0x00BB, 0x02);
    do {
        myMapper->writeCPU(0x007D, 0x00);
        if (myMapper->readCPU(0x00BB) == 0x02) {
            myMapper->writeCPU(0x008A, myMapper->readCPU(0x008A));
        }
        else {
            myMapper->writeCPU(0x008A, myMapper->readCPU(0x0089));
        }
        pushAddress(0x002074);
        SUB_001F14();
        if (poppedEntry.value != 0x002074) return;
        a = myMapper->readCPU(0x0071);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x00AD, myMapper->readCPU(0xA10A + x));
        myMapper->writeCPU(0x00AE, myMapper->readCPU(0xA10B + x));
        myMapper->writeCPU(0x00B4, 0x23);
        if (myMapper->readCPU(0x00BB) != 0x02) {
            goto L_002096;
        }
        myMapper->writeCPU(0x00B5, 0xC8);
        goto L_00209A;
    L_002096:
        myMapper->writeCPU(0x00B5, 0xCC);
    L_00209A:
        x = 0x07;
        do {
            a = myMapper->readCPU(0x2002);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B4));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B5));
            y = 0x00;
            do {
                myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
                opINY(1);
            } while (y != 0x04);
            a = myMapper->readCPU(0x00B5);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x00B5, a);
            a = myMapper->readCPU(0x00B4);
            opADC(0x00);
            myMapper->writeCPU(0x00B4, a);
            a = myMapper->readCPU(0x00AD);
            flgC = false;
            opADC(0x04);
            myMapper->writeCPU(0x00AD, a);
            a = myMapper->readCPU(0x00AE);
            opADC(0x00);
            myMapper->writeCPU(0x00AE, a);
            opDEX(1);
        } while (!flgZ);
        opDEC(0x00BB, 1);
        a = myMapper->readCPU(0x00BB);
        setLoadFlag(a);
    } while (!flgZ);
    opPLA();
    myMapper->writeCPU(0x0089, a);
    opPLA();
    myMapper->writeCPU(0x008A, a);
    opPLA();
    myMapper->writeCPU(0x007D, a);
    popAddress();
}

void game::SUB_002260() {
    a = myMapper->readCPU(0x0075);
    opAND(0xF8);
    opLSR_A(3);
    myMapper->writeCPU(0x0076, a);
    opAND(0x0F);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x0071);
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0xA0E2 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x00AD, a);
    a = myMapper->readCPU(0xA0E3 + x);
    opADC(0x00);
    myMapper->writeCPU(0x00AE, a);
    x = 0x18;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0600 + x, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
        a = myMapper->readCPU(0x00AD);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x00AD, a);
        a = myMapper->readCPU(0x00AE);
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0076);
    opAND(0x1C);
    opLSR_A(2);
    myMapper->writeCPU(0x0077, a);
    pushAddress(0x0022A1);
    SUB_0022BE();
    if (poppedEntry.value != 0x0022A1) return;
    x = 0x07;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0620 + x, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
        a = myMapper->readCPU(0x00AD);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x00AD, a);
        a = myMapper->readCPU(0x00AE);
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0022BE() {
    a = myMapper->readCPU(0x0077);
    opAND(0x03);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x0081);
    opAND(0x70);
    if (a == 0x70) {
        if (myMapper->readCPU(0x0071) != 0x09) {
            goto L_0022E0;
        }
        a = 0xF4;
        flgC = false;
        opADC(myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x00AD, a);
        a = 0xA2;
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        popAddress();
        return;
    }
L_0022E0:
    a = myMapper->readCPU(0x0071);
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0xA10A + x);
    flgC = false;
    opADC(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x00AD, a);
    a = myMapper->readCPU(0xA10B + x);
    opADC(0x00);
    myMapper->writeCPU(0x00AE, a);
    popAddress();
}

void game::SUB_002310() {
    a = myMapper->readCPU(0x007D);
    opPHA();
    myMapper->writeCPU(0x00C4, 0x00);
    do {
        x = myMapper->readCPU(0x00C4);
        a = myMapper->readCPU(0x02A0 + x);
        opLSR_A(3);
        pushAddress(0x00231F);
        SUB_002472();
        if (poppedEntry.value != 0x00231F) return;
        x = myMapper->readCPU(0x00C4);
        a = myMapper->readCPU(0x02A1 + x);
        flgC = true;
        opSBC(0x30);
        opAND(0xF8);
        opASL_A(1);
        opPHA();
        a = myMapper->readCPU(0x00AE);
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        opPLA();
        flgC = false;
        opADC(myMapper->readCPU(0x00AD));
        myMapper->writeCPU(0x00AD, a);
        a = myMapper->readCPU(0x00AE);
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        x = myMapper->readCPU(0x00C4);
        pushAddress(0x002342);
        SUB_0024C4();
        if (poppedEntry.value != 0x002342) return;
        if (!flgZ) {
            if (myMapper->readCPU(0x0036) != 0) {
                goto L_002355;
            }
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x02A0 + x, a);
            myMapper->writeCPU(0x02A1 + x, a);
            if (flgZ) {
                goto L_00235B;
            }
        }
    L_002355:
        a = 0x00;
        a = 0x00;
        a = 0x00;
    L_00235B:
        a = myMapper->readCPU(0x00C4);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x00C4, a);
    } while (a != 0x10);
    myMapper->writeCPU(0x00C4, 0x00);
    do {
        x = myMapper->readCPU(0x00C4);
        a = myMapper->readCPU((0x001C + x) & 0x00ff);
        opPHA();
        a = myMapper->readCPU(0x007D);
        setLoadFlag(a);
        if (flgZ) {
            opPLA();
            flgC = true;
            opSBC(0x04);
        }
        else {
            opPLA();
            flgC = false;
            opADC(0x04);
        }
        opLSR_A(3);
        pushAddress(0x002381);
        SUB_002472();
        if (poppedEntry.value != 0x002381) return;
        x = myMapper->readCPU(0x00C4);
        a = myMapper->readCPU((0x001D + x) & 0x00ff);
        flgC = true;
        opSBC(0x30);
        opAND(0xF8);
        opASL_A(1);
        opPHA();
        a = myMapper->readCPU(0x00AE);
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        opPLA();
        flgC = false;
        opADC(myMapper->readCPU(0x00AD));
        myMapper->writeCPU(0x00AD, a);
        a = myMapper->readCPU(0x00AE);
        opADC(0x00);
        myMapper->writeCPU(0x00AE, a);
        x = myMapper->readCPU(0x00C4);
        pushAddress(0x0023A3);
        SUB_0024C4();
        if (poppedEntry.value != 0x0023A3) return;
        if (!flgZ) {
            if (myMapper->readCPU((0x001B + x) & 0x00ff) == 0) {
                goto L_0023BE;
            }
            myMapper->writeCPU(0x003A, 0x0B);
            myMapper->writeCPU((0x001B + x) & 0x00ff, 0x00);
            a = 0xF8;
            setLoadFlag(a);
            myMapper->writeCPU(0x0710 + x, a);
            myMapper->writeCPU(0x0713 + x, a);
            if (flgZ) {
                goto L_0023CC;
            }
        }
    L_0023BE:
        a = 0x00;
        a = 0x00;
        a = 0x00;
        a = 0x00;
        a = 0x00;
        a = 0x00;
        a = 0x00;
    L_0023CC:
        a = myMapper->readCPU(0x00C4);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x00C4, a);
    } while (a != 0x08);
    a = myMapper->readCPU(0x0028);
    opLSR_A(3);
    pushAddress(0x0023DC);
    SUB_002472();
    if (poppedEntry.value != 0x0023DC) return;
    a = myMapper->readCPU(0x0029);
    flgC = true;
    opSBC(0x2C);
    opAND(0xF8);
    opASL_A(1);
    opPHA();
    a = myMapper->readCPU(0x00AE);
    opADC(0x00);
    myMapper->writeCPU(0x00AE, a);
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x00AD));
    myMapper->writeCPU(0x00AD, a);
    a = myMapper->readCPU(0x00AE);
    opADC(0x00);
    myMapper->writeCPU(0x00AE, a);
    pushAddress(0x0023FA);
    SUB_0024C4();
    if (poppedEntry.value != 0x0023FA) return;
    if (!flgZ) {
        a = 0x00;
        myMapper->writeCPU(0x0027, a);
        myMapper->writeCPU(0x002D, a);
        a = 0xF8;
        myMapper->writeCPU(0x071C, a);
        myMapper->writeCPU(0x071F, a);
    }
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = myMapper->readCPU(0x0015);
    opLSR_A(3);
    pushAddress(0x00241C);
    SUB_002472();
    if (poppedEntry.value != 0x00241C) return;
    a = myMapper->readCPU(0x0016);
    flgC = true;
    opSBC(0x30);
    opAND(0xF8);
    opASL_A(1);
    opPHA();
    a = myMapper->readCPU(0x00AE);
    opADC(0x00);
    myMapper->writeCPU(0x00AE, a);
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x00AD));
    myMapper->writeCPU(0x00AD, a);
    a = myMapper->readCPU(0x00AE);
    opADC(0x00);
    myMapper->writeCPU(0x00AE, a);
    pushAddress(0x00243A);
    SUB_0024C4();
    if (poppedEntry.value != 0x00243A) return;
    if (!flgZ) {
        if (myMapper->readCPU(0x0091) != 0) {
            goto L_00245C;
        }
        if (myMapper->readCPU(0x0031) == 0) {
            if (myMapper->readCPU(0x0097) != 0) {
                goto L_00245C;
            }
            a = myMapper->readCPU(0x0014);
            opORA(myMapper->readCPU(0x00F5));
            myMapper->writeCPU(0x0014, a);
            myMapper->writeCPU(0x0031, 0x00);
            a = 0x05;
            myMapper->writeCPU(0x0084, a);
            goto L_00246E;
        }
    }
L_00245C:
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
    a = 0x00;
L_00246E:
    opPLA();
    myMapper->writeCPU(0x007D, a);
    popAddress();
}

void game::SUB_002472() {
    flgC = false;
    opADC(myMapper->readCPU(0x0076));
    opPHA();
    opAND(0x0F);
    myMapper->writeCPU(0x00C3, a);
    opPLA();
    opAND(0x30);
    opLSR_A(4);
    x = a;
    a = myMapper->readCPU(0x0088);
    opPHA();
    a = myMapper->readCPU(0x008C);
    opPHA();
    a = myMapper->readCPU(0x008F);
    opAND(0x01);
    if (flgZ) {
        goto L_002494;
    }
    a = myMapper->readCPU(0xA4BC + x);
    goto L_002497;
L_002494:
    a = myMapper->readCPU(0xA4C0 + x);
L_002497:
    x = a;
    myMapper->writeCPU(0x0088, myMapper->readCPU((0x0087 + x) & 0x00ff));
    myMapper->writeCPU(0x008C, myMapper->readCPU((0x008B + x) & 0x00ff));
    myMapper->writeCPU(0x007D, 0x80);
    pushAddress(0x0024A4);
    SUB_001F14();
    if (poppedEntry.value != 0x0024A4) return;
    opPLA();
    myMapper->writeCPU(0x008C, a);
    opPLA();
    myMapper->writeCPU(0x0088, a);
    a = myMapper->readCPU(0x0071);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00AD, myMapper->readCPU(0xA0E2 + x));
    myMapper->writeCPU(0x00AE, myMapper->readCPU(0xA0E3 + x));
    popAddress();
}

void game::SUB_0024C4() {
    y = myMapper->readCPU(0x00C3);
    a = myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y);
    opCMP(a, 0x4F);
    if (flgC) {
        opCMP(a, 0xAA);
        if (!flgZ) {
            opCMP(a, 0x9C);
            if (!flgZ) {
                opCMP(a, 0x9D);
                if (!flgZ) {
                    opCMP(a, 0x9E);
                    if (!flgZ) {
                        opCMP(a, 0x9F);
                        if (!flgZ) {
                            opCMP(a, 0xA0);
                            if (!flgZ) {
                                opCMP(a, 0xA1);
                                if (flgZ) {
                                    goto L_0024EB;
                                }
                                a = 0xFF;
                                setLoadFlag(a);
                                popAddress();
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
L_0024EB:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0024EE() {
    y = 0x00;
    myMapper->writeCPU(0x2001, y);
    a = myMapper->readCPU(0x0092);
    if (a == 0x04) {
        goto L_0024FB;
    }
    opAND(0x03);
L_0024FB:
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0xA53C + x));
    myMapper->writeCPU(0x00B5, myMapper->readCPU(0xA53D + x));
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x10);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xA596 + y));
        opINY(1);
        opCMP(y, 0x10);
    } while (!flgZ);
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    popAddress();
}

void game::SUB_0025A6() {
    if (myMapper->readCPU(0x0093) == 0) {
        goto L_0025B2;
    }
    opINC(0x0092, 1);
    if (myMapper->readCPU(0x0092) == 0x80) {
        goto L_0025B3;
    }
    do {
        do {
            do {
                do {
                L_0025B2:
                    popAddress();
                    return;
                L_0025B3:
                    myMapper->writeCPU(0x0093, 0x00);
                    a = myMapper->readCPU(0x0081);
                    if (a != 0x1E) {
                        goto L_0025C3;
                    }
                    a = 0x01;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0092, a);
                } while (!flgZ);
            L_0025C3:
                if (a != 0x3E) {
                    goto L_0025CD;
                }
                a = 0x02;
                setLoadFlag(a);
                myMapper->writeCPU(0x0092, a);
            } while (!flgZ);
        L_0025CD:
            if (a != 0x5E) {
                goto L_0025D7;
            }
            a = 0x03;
            setLoadFlag(a);
            myMapper->writeCPU(0x0092, a);
        } while (!flgZ);
    L_0025D7:
        if (a != 0x7E) {
            goto L_0025E1;
        }
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0092, a);
    } while (!flgZ);
L_0025E1:
    myMapper->writeCPU(0x0092, 0x00);
    popAddress();
}

void game::SUB_0025E6() {
    if (myMapper->readCPU(0x0094) != 0) {
        goto L_0025FE;
    }
    if (myMapper->readCPU(0x0036) == 0) {
        a = myMapper->readCPU(0x0014);
        opAND(0x40);
        if (flgZ) {
            if (myMapper->readCPU(0x0091) != 0) {
                goto L_002612;
            }
            if (myMapper->readCPU(0x0035) >= 0x20) {
                goto L_0025FF;
            }
        }
    }
    do {
        do {
            do {
            L_0025FE:
                popAddress();
                return;
            L_0025FF:
                a = myMapper->readCPU(0x0002);
                opAND(0x40);
            } while (flgZ);
            a = myMapper->readCPU(0x0003);
            opAND(0x04);
        } while (flgZ);
        a = myMapper->readCPU(0x0035);
        flgC = true;
        opSBC(0x0C);
        myMapper->writeCPU(0x0035, a);
    L_002612:
        opINC(0x0091, 1);
        if (myMapper->readCPU(0x007D) == 0) {
            x = 0x04;
            y = 0x00;
            setLoadFlag(y);
            if (!flgZ) {
                goto L_002622;
            }
        }
        x = 0x00;
        y = 0x04;
    L_002622:
        a = myMapper->readCPU(0x0091);
        if (a < 0x40) {
            opAND(0x07);
            if (!flgZ) {
                goto L_00263A;
            }
            myMapper->writeCPU(0x00B4, 0x00);
            myMapper->writeCPU(0x00B5, 0x01);
            a = 0x50;
            setLoadFlag(a);
            myMapper->writeCPU(0x00B6, a);
            if (!flgZ) {
                goto L_002642;
            }
        }
    L_00263A:
        a = 0xAA;
        myMapper->writeCPU(0x00B4, a);
        myMapper->writeCPU(0x00B5, a);
        myMapper->writeCPU(0x00B6, a);
    L_002642:
        myMapper->writeCPU(0x0701, myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x0705 + x, myMapper->readCPU(0x00B5));
        myMapper->writeCPU(0x0705 + y, myMapper->readCPU(0x00B6));
        opCMP(myMapper->readCPU(0x0091), 0x60);
    } while (!flgZ);
    myMapper->writeCPU(0x0033, 0x01);
    pushAddress(0x00265B);
    SUB_0051E0();
    if (poppedEntry.value != 0x00265B) return;
    a = 0x06;
    pushAddress(0x002660);
    SUB_0051A5();
    if (poppedEntry.value != 0x002660) return;
    pushAddress(0x002663);
    SUB_0046BB();
    if (poppedEntry.value != 0x002663) return;
    pushAddress(0x002666);
    SUB_0051E0();
    if (poppedEntry.value != 0x002666) return;
    pushAddress(0x002669);
    SUB_00013D();
    if (poppedEntry.value != 0x002669) return;
    pushAddress(0x00266C);
    SUB_0001C8();
    if (poppedEntry.value != 0x00266C) return;
    pushAddress(0x00266F);
    SUB_000150();
    if (poppedEntry.value != 0x00266F) return;
    x = 0x00;
    a = myMapper->readCPU(0x00A8);
    opAND(0x03);
    myMapper->writeCPU(0x00A8, a);
    a = myMapper->readCPU(0x0072);
    flgC = false;
    opADC(myMapper->readCPU(0x00A8));
    if (a >= 0x08) {
        opINC(0x0080, 1);
    }
    opAND(0x07);
    myMapper->writeCPU(0x0072, a);
    a = myMapper->readCPU(0x0073);
    flgC = false;
    opADC(myMapper->readCPU(0x00A8));
    if (a >= 0x08) {
        opINC(0x0081, 1);
    }
    opAND(0x07);
    myMapper->writeCPU(0x0073, a);
    a = myMapper->readCPU(0x0074);
    flgC = false;
    opADC(myMapper->readCPU(0x00A8));
    if (a >= 0x08) {
        opINC(0x0082, 1);
    }
    opAND(0x07);
    myMapper->writeCPU(0x0074, a);
    a = myMapper->readCPU(0x0073);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x008A, x);
    opINX(1);
    myMapper->writeCPU(0x0089, x);
    a = myMapper->readCPU(0x0072);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0088, x);
    opINX(1);
    myMapper->writeCPU(0x0087, x);
    a = myMapper->readCPU(0x0081);
    myMapper->writeCPU(0x008E, a);
    myMapper->writeCPU(0x008D, a);
    a = myMapper->readCPU(0x0080);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x007D, 0x80);
    myMapper->writeCPU(0x0078, 0x88);
    a = 0x01;
    myMapper->writeCPU(0x0079, a);
    myMapper->writeCPU(0x008F, a);
    a = 0x00;
    myMapper->writeCPU(0x0075, a);
    myMapper->writeCPU(0x0032, a);
    myMapper->writeCPU(0x0039, a);
    myMapper->writeCPU(0x003E, a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x2000, a);
    pushAddress(0x0026E3);
    SUB_001FC4();
    if (poppedEntry.value != 0x0026E3) return;
    pushAddress(0x0026E6);
    SUB_002C4C();
    if (poppedEntry.value != 0x0026E6) return;
    a = 0x00;
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x0091, a);
    a = myMapper->readCPU(0x0080);
    opAND(0x1F);
    if (a != 0x1E) {
        goto L_0026FD;
    }
    a = myMapper->readCPU(0x0094);
    opORA(0x80);
    myMapper->writeCPU(0x0094, a);
L_0026FD:
    opPLA();
    opPLA();
    SUB_000080();
    return;
}

void game::SUB_002702() {
    if (myMapper->readCPU(0x0097) != 0) {
        goto L_002741;
    }
    myMapper->writeCPU(0x00F5, 0x40);
    x = myMapper->readCPU(0x0030);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_002716;
    }
    a = myMapper->readCPU(0x000D);
    opAND(0x10);
    if (!flgZ) {
        goto L_00275B;
    }
    if (flgZ) {
        goto L_00271C;
    }
L_002716:
    a = myMapper->readCPU(0x0010);
    opAND(0x10);
    if (!flgZ) {
        goto L_00275B;
    }
L_00271C:
    if (myMapper->readCPU(0x0094) == 0) {
        goto L_00275B;
    }
    if (myMapper->readCPU(0x0072) != 0x04) {
        goto L_00275B;
    }
    a = myMapper->readCPU(0x0016);
    if (a < 0x80) {
        goto L_00275B;
    }
    if (a >= 0x90) {
        goto L_00275B;
    }
    a = myMapper->readCPU(0x0015);
    flgC = false;
    opADC(myMapper->readCPU(0x0075));
    if (a != 0xF0) {
        goto L_00275B;
    }
    myMapper->writeCPU(0x0097, 0xA0);
    myMapper->writeCPU(0x00F5, 0x00);
L_002741:
    a = myMapper->readCPU(0x0702);
    opORA(0x20);
    myMapper->writeCPU(0x0702, a);
    a = myMapper->readCPU(0x0706);
    opORA(0x20);
    myMapper->writeCPU(0x0706, a);
    a = myMapper->readCPU(0x070A);
    opORA(0x20);
    myMapper->writeCPU(0x070A, a);
    opDEC(0x0097, 1);
L_00275B:
    popAddress();
}

void game::SUB_00275C() {
    pushAddress(0x00275C);
    SUB_002772();
    if (poppedEntry.value != 0x00275C) return;
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x0078));
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0075));
    myMapper->writeCPU(0x2005, 0x00);
    popAddress();
}

void game::SUB_002772() {
    x = myMapper->readCPU(0x00B4);
    y = myMapper->readCPU(0x0098);
    do {
        do {
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00277D() {
    if (myMapper->readCPU(0x0036) == 0) {
        goto L_002782;
    }
    popAddress();
    return;
L_002782:
    myMapper->writeCPU(0x00B3, 0x38);
    a = 0x00;
    myMapper->writeCPU(0x0085, a);
    do {
        x = a;
        opPHA();
        a = myMapper->readCPU(0x0200 + x);
        setLoadFlag(a);
        if (flgN) {
            y = myMapper->readCPU(0x0086);
            a = myMapper->readCPU(0x0201 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0x0075));
            myMapper->writeCPU(0x0062, a);
            a = myMapper->readCPU(0x020E + x);
            opSBC(myMapper->readCPU(0x0073));
            opAND(myMapper->readCPU(0x89F4 + y));
            if (flgZ) {
                myMapper->writeCPU(0x0064, myMapper->readCPU(0x0203 + x));
                a = myMapper->readCPU(0x0200 + x);
                opAND(0x40);
                if (flgZ) {
                    if (myMapper->readCPU(0x0209 + x) != 0x0E) {
                        goto L_0027BE;
                    }
                    pushAddress(0x0027B8);
                    SUB_002890();
                    if (poppedEntry.value != 0x0027B8) return;
                    goto L_0027F8;
                L_0027BE:
                    a = myMapper->readCPU(0x0209 + x);
                    myMapper->writeCPU(0x006A, a);
                    if (a != 0x1C) {
                        if (a != 0x1A) {
                            goto L_0027D2;
                        }
                    }
                    a = myMapper->readCPU(0x0205 + x);
                    setLoadFlag(a);
                    if (flgN) {
                        if (flgN) {
                            goto L_0027F2;
                        }
                    L_0027D2:
                        if (a != 0x1E) {
                            goto L_0027E2;
                        }
                        a = myMapper->readCPU(0x0200 + x);
                        opAND(0x20);
                        if (flgZ) {
                            goto L_0027F8;
                        }
                        a = myMapper->readCPU(0x020C + x);
                        setLoadFlag(a);
                        if (!flgZ) {
                            goto L_0027F8;
                        }
                    L_0027E2:
                        a = myMapper->readCPU(0x0200 + x);
                        opAND(0x02);
                        if (!flgZ) {
                            goto L_0027F2;
                        }
                    }
                }
                a = myMapper->readCPU(0x020D + x);
                pushAddress(0x0027EC);
                SUB_002831();
                if (poppedEntry.value != 0x0027EC) return;
                goto L_0027F8;
            L_0027F2:
                a = myMapper->readCPU(0x020D + x);
                pushAddress(0x0027F5);
                SUB_002842();
                if (poppedEntry.value != 0x0027F5) return;
            }
        }
    L_0027F8:
        opPLA();
        flgC = false;
        opADC(0x10);
    } while (a != 0xA0);
    x = myMapper->readCPU(0x00B3);
    do {
        if (x >= 0xD0) {
            goto L_00280E;
        }
        myMapper->writeCPU(0x0700 + x, 0xF8);
        opINX(1);
    } while (!flgZ);
L_00280E:
    popAddress();
}

void game::SUB_002831() {
    x = myMapper->readCPU(0x00B3);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00AD, myMapper->readCPU(0xBD74 + y));
    myMapper->writeCPU(0x00AE, myMapper->readCPU(0xBD75 + y));
    SUB_002853();
    return;
}

void game::SUB_002842() {
    x = myMapper->readCPU(0x00B3);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x00AD, myMapper->readCPU(0xC35D + y));
    myMapper->writeCPU(0x00AE, myMapper->readCPU(0xC35E + y));
    SUB_002853();
    return;
}

void game::SUB_002853() {
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y);
        if (a == 0x80) {
            SUB_00288F();
            return;
        }
        flgC = false;
        opADC(myMapper->readCPU(0x0064));
        myMapper->writeCPU(0x0700 + x, a);
        opINY(1);
        myMapper->writeCPU(0x0701 + x, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0702 + x, myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y));
        if (myMapper->readCPU(0x006A) != 0x84) {
            goto L_00287B;
        }
        a = myMapper->readCPU(0x0702 + x);
        opAND(0xF0);
        myMapper->writeCPU(0x0702 + x, a);
    L_00287B:
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x00AD) + (myMapper->readCPU((0x00AD + 1) & 0x00ff) << 8) + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0062));
        myMapper->writeCPU(0x0703 + x, a);
        opINY(1);
        opINX(4);
        myMapper->writeCPU(0x00B3, x);
    } while (x < 0xD0);
    SUB_00288F();
    return;
}

void game::SUB_00288F() {
    popAddress();
}

void game::SUB_002890() {
    myMapper->writeCPU(0x006C, myMapper->readCPU(0x020B + x));
    x = myMapper->readCPU(0x00B3);
    a = myMapper->readCPU(0x0081);
    opLSR_A(1);
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0xA954 + y);
    setLoadFlag(a);
    if (flgZ) {
        SUB_00288F();
        return;
    }
    myMapper->writeCPU(0x00AD, a);
    opASL_A(2);
    myMapper->writeCPU(0x00AE, a);
    a = myMapper->readCPU(0x0064);
    flgC = true;
    opSBC(myMapper->readCPU(0x00AE));
    myMapper->writeCPU(0x0700 + x, a);
    myMapper->writeCPU(0x0704 + x, a);
    a = 0x83;
    myMapper->writeCPU(0x0701 + x, a);
    myMapper->writeCPU(0x0705 + x, a);
    opINC(0x0705 + x, 1);
    if (myMapper->readCPU(0x006C) == 0x02) {
        a = 0xAA;
        myMapper->writeCPU(0x0701 + x, a);
        myMapper->writeCPU(0x0705 + x, a);
    }
    a = 0x00;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
    a = myMapper->readCPU(0x0062);
    myMapper->writeCPU(0x0707 + x, a);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0703 + x, a);
    while (true) {
        a = x;
        flgC = false;
        opADC(0x08);
        x = a;
        myMapper->writeCPU(0x00B3, x);
        if (x >= 0xD0) {
            goto L_002953;
        }
        opDEC(0x00AD, 1);
        if (flgZ) {
            goto L_00292D;
        }
        a = myMapper->readCPU(0x00AE);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x00AE, a);
        a = myMapper->readCPU(0x0064);
        flgC = true;
        opSBC(myMapper->readCPU(0x00AE));
        myMapper->writeCPU(0x0700 + x, a);
        myMapper->writeCPU(0x0704 + x, a);
        a = 0x87;
        myMapper->writeCPU(0x0701 + x, a);
        myMapper->writeCPU(0x0705 + x, a);
        if (myMapper->readCPU(0x006C) == 0) {
            goto L_002914;
        }
        a = 0xAA;
        myMapper->writeCPU(0x0701 + x, a);
        myMapper->writeCPU(0x0705 + x, a);
    L_002914:
        a = myMapper->readCPU(0x000B);
        opLSR_A(1);
        opAND(0x02);
        myMapper->writeCPU(0x0702 + x, a);
        myMapper->writeCPU(0x0706 + x, a);
        a = myMapper->readCPU(0x0062);
        myMapper->writeCPU(0x0707 + x, a);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x0703 + x, a);
    }
L_00292D:
    a = x;
    flgC = true;
    opSBC(0x08);
    x = a;
    a = 0x83;
    myMapper->writeCPU(0x0701 + x, a);
    myMapper->writeCPU(0x0705 + x, a);
    opINC(0x0705 + x, 1);
    if (myMapper->readCPU(0x006C) != 0x01) {
        goto L_00294B;
    }
    a = 0xAA;
    myMapper->writeCPU(0x0701 + x, a);
    myMapper->writeCPU(0x0705 + x, a);
L_00294B:
    a = 0x80;
    myMapper->writeCPU(0x0702 + x, a);
    myMapper->writeCPU(0x0706 + x, a);
L_002953:
    popAddress();
}

void game::SUB_002A02() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x0033);
    opAND(0x02);
    if (!flgZ) {
        opINC(0x000B, 1);
        a = myMapper->readCPU(0x000B);
        opAND(0x01);
    }
    else {
        a = myMapper->readCPU(0x0030);
        setLoadFlag(a);
    }
    if (!flgZ) {
        goto L_002A30;
    }
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x65);
    x = 0x02;
    y = 0x0E;
    a = myMapper->readCPU(0x000F);
    setLoadFlag(a);
    SUB_002A6B();
    return;
L_002A30:
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x77);
    x = 0x02;
    y = 0x12;
    a = myMapper->readCPU(0x0013);
    setLoadFlag(a);
    SUB_002A6B();
    return;
}

void game::SUB_002A46() {
    a = myMapper->readCPU(0x2002);
    a = myMapper->readCPU(0x0033);
    opAND(0x02);
    if (flgZ) {
        goto L_002A5B;
    }
    myMapper->writeCPU(0x2006, 0x20);
    a = 0x8E;
    setLoadFlag(a);
    myMapper->writeCPU(0x2006, a);
    if (!flgZ) {
        goto L_002A65;
    }
L_002A5B:
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x97);
L_002A65:
    x = 0x02;
    y = 0xF3;
    a = myMapper->readCPU(0x00F4);
    setLoadFlag(a);
    SUB_002A6B();
    return;
}

void game::SUB_002A6B() {
    if (!flgZ) {
        goto L_002A74;
    }
    a = 0xAA;
    setLoadFlag(a);
    myMapper->writeCPU(0x2007, a);
    if (!flgZ) {
        goto L_002A7A;
    }
L_002A74:
    flgC = false;
    opADC(0xDA);
    myMapper->writeCPU(0x2007, a);
    do {
    L_002A7A:
        a = myMapper->readCPU(0x0000 + y);
        opPHA();
        opLSR_A(4);
        pushAddress(0x002A82);
        SUB_002A8E();
        if (poppedEntry.value != 0x002A82) return;
        opPLA();
        pushAddress(0x002A86);
        SUB_002A8E();
        if (poppedEntry.value != 0x002A86) return;
        opDEY(1);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_002A8E() {
    opAND(0x0F);
    flgC = false;
    opADC(0xDA);
    myMapper->writeCPU(0x2007, a);
    popAddress();
}

void game::SUB_002A97() {
    if (myMapper->readCPU(0x0030) == 0) {
        goto L_002A9E;
    }
    goto L_002B24;
L_002A9E:
    a = x;
    opPHA();
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    opASL_A(1);
    x = a;
    if (x == 0x1C) {
        if (myMapper->readCPU(0x006C) != 0x03) {
            goto L_002ABE;
        }
        x = 0x10;
    }
    if (x == 0x12) {
        a = myMapper->readCPU(0x0061);
        opAND(0x20);
        if (!flgZ) {
            x = 0x06;
        }
    }
L_002ABE:
    a = myMapper->readCPU(0xABBC + x);
    flgC = false;
    opADC(myMapper->readCPU(0x000C));
    if (flgC) {
        flgC = false;
        opADC(0x60);
        opINC(0x000D, 1);
    }
    opCMP(a, 0xA0);
    if (flgC) {
        flgC = false;
        opADC(0x60);
    }
    myMapper->writeCPU(0x000C, a);
    a = myMapper->readCPU(0xABBD + x);
    opAND(0x0F);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x000D);
    opAND(0x0F);
    opADC(myMapper->readCPU(0x00B4));
    if (a >= 0x10) {
        flgC = false;
        opADC(0x06);
    }
    opPHA();
    opAND(0x0F);
    opCMP(a, 0x0A);
    opPLA();
    if (flgC) {
        flgC = false;
        opADC(0x06);
    }
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0xABBD + x);
    opAND(0xF0);
    myMapper->writeCPU(0x00B5, a);
    a = myMapper->readCPU(0x000D);
    opAND(0xF0);
    opADC(myMapper->readCPU(0x00B4));
    opADC(myMapper->readCPU(0x00B5));
    if (flgC) {
        opINC(0x000E, 1);
        flgC = false;
        opADC(0x60);
    }
    opCMP(a, 0xA0);
    if (flgC) {
        flgC = false;
        opADC(0x60);
    }
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x000E);
    opADC(0x00);
    pushAddress(0x002B18);
    SUB_002BAA();
    if (poppedEntry.value != 0x002B18) return;
    myMapper->writeCPU(0x000E, a);
    if (flgC) {
        opINC(0x000F, 1);
    }
    opPLA();
    x = a;
    popAddress();
    return;
L_002B24:
    a = x;
    opPHA();
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    opASL_A(1);
    x = a;
    if (x == 0x1C) {
        if (myMapper->readCPU(0x006C) != 0x03) {
            goto L_002B44;
        }
        x = 0x10;
    }
    if (x == 0x12) {
        a = myMapper->readCPU(0x0061);
        opAND(0x20);
        if (!flgZ) {
            x = 0x06;
        }
    }
L_002B44:
    a = myMapper->readCPU(0xABBC + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0010));
    if (flgC) {
        flgC = false;
        opADC(0x60);
        opINC(0x0011, 1);
    }
    opCMP(a, 0xA0);
    if (flgC) {
        flgC = false;
        opADC(0x60);
    }
    myMapper->writeCPU(0x0010, a);
    a = myMapper->readCPU(0xABBD + x);
    opAND(0x0F);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x0011);
    opAND(0x0F);
    opADC(myMapper->readCPU(0x00B4));
    if (a >= 0x10) {
        flgC = false;
        opADC(0x06);
    }
    opPHA();
    opAND(0x0F);
    opCMP(a, 0x0A);
    opPLA();
    if (flgC) {
        flgC = false;
        opADC(0x06);
    }
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0xABBD + x);
    opAND(0xF0);
    myMapper->writeCPU(0x00B5, a);
    a = myMapper->readCPU(0x0011);
    opAND(0xF0);
    opADC(myMapper->readCPU(0x00B4));
    opADC(myMapper->readCPU(0x00B5));
    if (flgC) {
        opINC(0x0012, 1);
        flgC = false;
        opADC(0x60);
    }
    opCMP(a, 0xA0);
    if (flgC) {
        flgC = false;
        opADC(0x60);
    }
    myMapper->writeCPU(0x0011, a);
    a = myMapper->readCPU(0x0012);
    opADC(0x00);
    pushAddress(0x002B9E);
    SUB_002BAA();
    if (poppedEntry.value != 0x002B9E) return;
    myMapper->writeCPU(0x0012, a);
    if (!flgC) {
        goto L_002BA7;
    }
    opINC(0x0013, 1);
L_002BA7:
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_002BAA() {
    opPHA();
    opAND(0x0F);
    opCMP(a, 0x0A);
    if (flgC) {
        opPLA();
        opADC(0x05);
        opPHA();
    }
    opPLA();
    opCMP(a, 0xA0);
    if (!flgC) {
        goto L_002BBD;
    }
    flgC = false;
    opADC(0x60);
L_002BBD:
    popAddress();
}

void game::SUB_002BFC() {
    if (myMapper->readCPU(0x0030) != 0) {
        goto L_002C24;
    }
    a = myMapper->readCPU(0x00F1);
    flgC = true;
    opSBC(myMapper->readCPU(0x000C));
    a = myMapper->readCPU(0x00F2);
    opSBC(myMapper->readCPU(0x000D));
    a = myMapper->readCPU(0x00F3);
    opSBC(myMapper->readCPU(0x000E));
    a = myMapper->readCPU(0x00F4);
    opSBC(myMapper->readCPU(0x000F));
    if (!flgC) {
        myMapper->writeCPU(0x00F1, myMapper->readCPU(0x000C));
        myMapper->writeCPU(0x00F2, myMapper->readCPU(0x000D));
        myMapper->writeCPU(0x00F3, myMapper->readCPU(0x000E));
        myMapper->writeCPU(0x00F4, myMapper->readCPU(0x000F));
    }
    popAddress();
    return;
L_002C24:
    a = myMapper->readCPU(0x00F1);
    flgC = true;
    opSBC(myMapper->readCPU(0x0010));
    a = myMapper->readCPU(0x00F2);
    opSBC(myMapper->readCPU(0x0011));
    a = myMapper->readCPU(0x00F3);
    opSBC(myMapper->readCPU(0x0012));
    a = myMapper->readCPU(0x00F4);
    opSBC(myMapper->readCPU(0x0013));
    if (flgC) {
        goto L_002C47;
    }
    myMapper->writeCPU(0x00F1, myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x00F2, myMapper->readCPU(0x0011));
    myMapper->writeCPU(0x00F3, myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x00F4, myMapper->readCPU(0x0013));
L_002C47:
    popAddress();
}

void game::SUB_002C48() {
    myMapper->writeCPU(0x0035, 0x40);
    SUB_002C4C();
    return;
}

void game::SUB_002C4C() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x40);
    x = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xC633 + x));
        opINX(1);
    } while (x != 0x80);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0xC0);
    x = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xC6B3 + x));
        opINX(1);
    } while (x != 0x08);
    popAddress();
}

void game::SUB_002C86() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xA3);
    x = 0x00;
    a = myMapper->readCPU(0x0035);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x00B4, a);
        opAND(0x78);
        opLSR_A(3);
        if (flgZ) {
            goto L_002CB7;
        }
        myMapper->writeCPU(0x00B5, a);
        a = 0xBF;
        do {
            myMapper->writeCPU(0x2007, a);
            opINX(1);
            opCMP(x, 0x08);
            if (flgZ) {
                goto L_002CD1;
            }
        } while (x != myMapper->readCPU(0x00B5));
    L_002CB7:
        a = myMapper->readCPU(0x00B4);
        opAND(0x07);
        y = a;
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xACF5 + y));
        opINX(1);
        opCMP(x, 0x08);
        if (flgZ) {
            goto L_002CD1;
        }
    }
    a = 0xAA;
    do {
        myMapper->writeCPU(0x2007, a);
        opINX(1);
        opCMP(x, 0x08);
    } while (!flgZ);
L_002CD1:
    popAddress();
}

void game::SUB_002CD2() {
    if (myMapper->readCPU(0x0037) != 0) {
        goto L_002CE5;
    }
    if (myMapper->readCPU(0x0035) != 0x1B) {
        goto L_002CF4;
    }
    if (myMapper->readCPU(0x000B) != 0) {
        goto L_002CF4;
    }
    a = 0x0A;
    pushAddress(0x002CE2);
    SUB_0051A5();
    if (poppedEntry.value != 0x002CE2) return;
L_002CE5:
    opINC(0x0037, 1);
    if (myMapper->readCPU(0x0037) != 0) {
        goto L_002CF4;
    }
    myMapper->writeCPU(0x0037, 0x00);
    a = 0x8A;
    pushAddress(0x002CF1);
    SUB_0051A5();
    if (poppedEntry.value != 0x002CF1) return;
L_002CF4:
    popAddress();
}

void game::SUB_002CFD() {
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_002D29;
    }
    myMapper->writeCPU(0x0724, 0x25);
    myMapper->writeCPU(0x0725, 0xB3);
    myMapper->writeCPU(0x0726, 0x00);
    myMapper->writeCPU(0x0727, 0x34);
    myMapper->writeCPU(0x0720, 0x25);
    myMapper->writeCPU(0x0721, 0xB3);
    myMapper->writeCPU(0x0722, 0x02);
    myMapper->writeCPU(0x0723, 0x44);
L_002D29:
    popAddress();
}

void game::SUB_002D2A() {
    myMapper->writeCPU(0x2001, 0x00);
    if (myMapper->readCPU(0x0094) == 0) {
        if (myMapper->readCPU(0x0036) != 0) {
            goto L_002D3D;
        }
        a = myMapper->readCPU(0x0035);
        if (a >= 0x20) {
            goto L_002D42;
        }
    }
L_002D3D:
    x = 0x02;
    goto L_002D4D;
L_002D42:
    if (a >= 0x30) {
        goto L_002D4B;
    }
    x = 0x01;
    goto L_002D4D;
L_002D4B:
    x = 0x00;
L_002D4D:
    a = x;
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0xAD74 + x));
    myMapper->writeCPU(0x00B5, myMapper->readCPU(0xAD75 + x));
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0xB5);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        opCMP(y, 0x08);
    } while (!flgZ);
    popAddress();
}

void game::SUB_002DBB() {
    if (flgC) {
        SUB_002DC2();
        return;
    }
    SUB_002DBD();
    return;
}

void game::SUB_002DBD() {
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
    SUB_002DC2();
    return;
}

void game::SUB_002DC2() {
    popAddress();
}

void game::SUB_002DC3() {
    a = myMapper->readCPU(0x0015);
    flgC = true;
    opSBC(myMapper->readCPU(0x0062));
    pushStatus();
    pushAddress(0x002DC9);
    SUB_002DBB();
    if (poppedEntry.value != 0x002DC9) return;
    myMapper->writeCPU(0x009C, a);
    a = myMapper->readCPU(0x0016);
    flgC = true;
    opSBC(myMapper->readCPU(0x0064));
    pushStatus();
    pushAddress(0x002DD4);
    SUB_002DBB();
    if (poppedEntry.value != 0x002DD4) return;
    myMapper->writeCPU(0x009A, a);
    opCMP(a, myMapper->readCPU(0x009C));
    pushStatus();
    if (!flgC) {
        opPHA();
        a = myMapper->readCPU(0x009C);
        myMapper->writeCPU(0x009A, a);
        opPLA();
        myMapper->writeCPU(0x009C, a);
    }
    pushAddress(0x002DE6);
    SUB_003059();
    if (poppedEntry.value != 0x002DE6) return;
    popStatus();
    if (!flgC) {
        a = myMapper->readCPU(0x00A2);
        opPHA();
        a = myMapper->readCPU(0x00A3);
        opPHA();
        myMapper->writeCPU(0x00A2, myMapper->readCPU(0x00A0));
        a = myMapper->readCPU(0x00A1);
        myMapper->writeCPU(0x00A3, a);
        opPLA();
        myMapper->writeCPU(0x00A1, a);
        opPLA();
        myMapper->writeCPU(0x00A0, a);
    }
    popStatus();
    if (!flgC) {
        a = myMapper->readCPU(0x00A1);
        setLoadFlag(a);
        flgC = true;
        if (!flgZ) {
            pushAddress(0x002E08);
            SUB_002DBD();
            if (poppedEntry.value != 0x002E08) return;
            myMapper->writeCPU(0x00A1, a);
            flgC = false;
        }
        a = myMapper->readCPU(0x00A0);
        opEOR(0xFF);
        opADC(0x00);
        myMapper->writeCPU(0x00A0, a);
    }
    popStatus();
    if (!flgC) {
        a = myMapper->readCPU(0x00A3);
        setLoadFlag(a);
        flgC = true;
        if (flgZ) {
            goto L_002E24;
        }
        pushAddress(0x002E1E);
        SUB_002DBD();
        if (poppedEntry.value != 0x002E1E) return;
        myMapper->writeCPU(0x00A3, a);
        flgC = false;
    L_002E24:
        a = myMapper->readCPU(0x00A2);
        opEOR(0xFF);
        opADC(0x00);
        myMapper->writeCPU(0x00A2, a);
    }
    while (true) {
        a = myMapper->readCPU(0x00A2);
        if (a < 0x04) {
            goto L_002E36;
        }
        if (a < 0xFD) {
            goto L_002E40;
        }
    L_002E36:
        a = myMapper->readCPU(0x00A0);
        if (a < 0x04) {
            goto L_002E51;
        }
        if (a >= 0xFD) {
            goto L_002E51;
        }
    L_002E40:
        a = myMapper->readCPU(0x00A2);
        opASL_A(1);
        opROR_M(0x00A2, 1);
        opROR_M(0x00A3, 1);
        a = myMapper->readCPU(0x00A0);
        opASL_A(1);
        opROR_M(0x00A0, 1);
        opROR_M(0x00A1, 1);
    }
L_002E51:
    popAddress();
}

void game::SUB_002FE4() {
    a = myMapper->readCPU(0x006B);
    opLSR_A(2);
    opAND(0x01);
    flgC = false;
    opADC(0x71);
    myMapper->writeCPU(0x006E, a);
    opINC(0x006B, 1);
    if (myMapper->readCPU(0x006B) >= 0x08) {
        a = myMapper->readCPU(0x0061);
        opAND(0xBF);
        myMapper->writeCPU(0x0061, a);
        if (myMapper->readCPU(0x006A) == 0x07) {
            opINC(0x006C, 1);
            if (myMapper->readCPU(0x006C) >= 0x03) {
                goto L_00300C;
            }
            popAddress();
            return;
        }
    L_00300C:
        a = myMapper->readCPU(0x0061);
        opORA(0x01);
        myMapper->writeCPU(0x0061, a);
    }
    popAddress();
}

void game::SUB_003013() {
    y = 0x00;
    do {
        myMapper->writeCPU(0x0061 + y, myMapper->readCPU(0x0200 + x));
        opINX(1);
        opINY(1);
    } while (y != 0x10);
    y = myMapper->readCPU(0x0086);
    a = myMapper->readCPU(0x0062);
    flgC = true;
    opSBC(myMapper->readCPU(0x0075));
    myMapper->writeCPU(0x0062, a);
    a = myMapper->readCPU(0x006F);
    opSBC(myMapper->readCPU(0x0073));
    opAND(myMapper->readCPU(0x89F4 + y));
    myMapper->writeCPU(0x006F, a);
    popAddress();
}

void game::SUB_003059() {
    a = 0x00;
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x00A0, a);
    myMapper->writeCPU(0x00A3, a);
    a = myMapper->readCPU(0x009A);
    opORA(myMapper->readCPU(0x009C));
    if (!flgZ) {
        goto L_00306A;
    }
    myMapper->writeCPU(0x00A2, a);
    popAddress();
    return;
L_00306A:
    myMapper->writeCPU(0x00A2, 0x01);
    myMapper->writeCPU(0x009E, myMapper->readCPU(0x009A));
    do {
        myMapper->writeCPU(0x00B5, 0x09);
        myMapper->writeCPU(0x00B4, 0x01);
        myMapper->writeCPU(0x009F, myMapper->readCPU(0x009C));
        do {
            opDEC(0x00B5, 1);
            if (flgZ) {
                goto L_0030AC;
            }
            opASL_M(0x00B4, 1);
            opASL_M(0x009F, 1);
            if (flgC) {
                goto L_00308F;
            }
        } while (myMapper->readCPU(0x009E) >= myMapper->readCPU(0x009F));
        flgC = false;
    L_00308F:
        opROR_M(0x009F, 1);
        opROR_M(0x00B4, 1);
        a = myMapper->readCPU(0x009E);
        flgC = true;
        opSBC(myMapper->readCPU(0x009F));
        if (!flgC) {
            goto L_0030AC;
        }
        myMapper->writeCPU(0x009E, a);
        pushStatus();
        a = myMapper->readCPU(0x00A0);
        opORA(myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x00A0, a);
        popStatus();
        if (flgZ) {
            goto L_0030C8;
        }
    } while (myMapper->readCPU(0x009F) != myMapper->readCPU(0x009C));
L_0030AC:
    myMapper->writeCPU(0x00B4, 0x08);
    do {
        opASL_M(0x009E, 1);
        if (flgC) {
            opROR_M(0x009E, 1);
        }
        a = myMapper->readCPU(0x009E);
        setLoadFlag(a);
        flgC = false;
        if (!flgZ) {
            flgC = true;
            opSBC(myMapper->readCPU(0x009F));
            if (!flgC) {
                goto L_0030C2;
            }
            myMapper->writeCPU(0x009E, a);
        }
    L_0030C2:
        opROL_M(0x00A1, 1);
        opDEC(0x00B4, 1);
    } while (!flgZ);
L_0030C8:
    popAddress();
}

void game::SUB_0030C9() {
    a = myMapper->readCPU(0x06F0);
    opASL_A(2);
    opEOR(myMapper->readCPU(0x06F2));
    opASL_A(1);
    opROL_M(0x06F0, 1);
    opROL_M(0x06F1, 1);
    a = 0x00;
    opROR_A(1);
    myMapper->writeCPU(0x06F2, a);
    a = myMapper->readCPU(0x06F0);
    myMapper->writeCPU(0x00A8, a);
    popAddress();
}

void game::SUB_0030E4() {
    myMapper->writeCPU(0x06F0, 0x55);
    myMapper->writeCPU(0x06F1, 0xDA);
    myMapper->writeCPU(0x06F2, 0x17);
    popAddress();
}

void game::SUB_00311B() {
    a = x;
    opPHA();
    a = myMapper->readCPU(0x0091);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0061);
        opAND(0x41);
        if (flgZ) {
            a = myMapper->readCPU(0x006F);
            setLoadFlag(a);
            if (flgZ) {
                if (!(myMapper->readCPU(0x0032) & 0x80)) {
                    goto L_003138;
                }
                pushAddress(0x00312F);
                SUB_0033EA();
                if (poppedEntry.value != 0x00312F) return;
                pushAddress(0x003132);
                SUB_003403();
                if (poppedEntry.value != 0x003132) return;
            }
        }
    }
    opPLA();
    x = a;
    popAddress();
    return;
L_003138:
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0x0014);
    opAND(0x40);
    if (!flgZ) {
    }
    else {
        myMapper->writeCPU(0x00B4, myMapper->readCPU(0x0015));
        myMapper->writeCPU(0x00B5, myMapper->readCPU(0x0016));
        pushAddress(0x00314F);
        SUB_00336C();
        if (poppedEntry.value != 0x00314F) return;
        if (!flgC) {
            a = myMapper->readCPU(0x006A);
            opAND(0x7F);
            if (a == 0x0A) {
                myMapper->writeCPU(0x006C, 0x00);
            }
            goto L_003246;
        }
        a = myMapper->readCPU(0x006A);
        opAND(0x7F);
        if (a == 0x0A) {
            a = myMapper->readCPU(0x006C);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0031CA;
            }
            a = myMapper->readCPU(0x0061);
            opAND(0x20);
            if (flgZ) {
                goto L_0031E3;
            }
            a = myMapper->readCPU(0x0061);
            opAND(0xDF);
            myMapper->writeCPU(0x0061, a);
            myMapper->writeCPU(0x006C, 0x01);
            a = myMapper->readCPU(0x00B7);
            opLSR_A(2);
            flgC = false;
            opADC(0x01);
            if (a == 0x05) {
                opPHA();
                myMapper->writeCPU(0x0058, 0x20);
                myMapper->writeCPU(0x0059, myMapper->readCPU(0x0062));
                a = myMapper->readCPU(0x0064);
                myMapper->writeCPU(0x005A, a);
                opPLA();
            }
            do {
                opPHA();
                pushAddress(0x003199);
                SUB_002A97();
                if (poppedEntry.value != 0x003199) return;
                opPLA();
                flgC = true;
                opSBC(0x01);
            } while (!flgZ);
            a = 0x07;
            pushAddress(0x0031A4);
            SUB_0051A5();
            if (poppedEntry.value != 0x0031A4) return;
        }
        else {
            if (a != 0x17) {
                goto L_0031E3;
            }
            myMapper->writeCPU(0x004F, 0x80);
            a = 0x04;
            pushAddress(0x0031B4);
            SUB_0051A5();
            if (poppedEntry.value != 0x0031B4) return;
            goto L_00323F;
        }
        do {
            pushAddress(0x0031BA);
            SUB_003403();
            if (poppedEntry.value != 0x0031BA) return;
        L_0031BD:
            a = myMapper->readCPU(0x006A);
            if (a != 0x0E) {
                if (a == 0x0F) {
                    goto L_0031CA;
                }
                pushAddress(0x0031C7);
                SUB_002A97();
                if (poppedEntry.value != 0x0031C7) return;
            }
        L_0031CA:
            goto L_003323;
            do {
                do {
                    x = myMapper->readCPU(0x0030);
                    opINC((0x002E + x) & 0x00ff, 1);
                    if (myMapper->readCPU((0x002E + x) & 0x00ff) < 0x0F) {
                        goto L_0031DB;
                    }
                    myMapper->writeCPU((0x002E + x) & 0x00ff, 0x0F);
                L_0031DB:
                    a = 0x07;
                    pushAddress(0x0031DD);
                    SUB_0051A5();
                    if (poppedEntry.value != 0x0031DD) return;
                    goto L_00323F;
                L_0031E3:
                    if (a == 0x16) {
                        goto L_00322D;
                    }
                } while (a == 0x11);
                if (a != 0x1C) {
                    goto L_0031F6;
                }
                a = myMapper->readCPU(0x000D);
                opLSR_A(1);
            } while (flgC);
            if (flgC) {
            L_0031F6:
                if (a < 0x19) {
                    goto L_003213;
                }
                if (a != 0x1E) {
                    a = 0x07;
                    pushAddress(0x003200);
                    SUB_0051A5();
                    if (poppedEntry.value != 0x003200) return;
                    a = myMapper->readCPU(0x006A);
                    if (a != 0x0E) {
                        if (a == 0x0F) {
                            goto L_003210;
                        }
                        pushAddress(0x00320D);
                        SUB_002A97();
                        if (poppedEntry.value != 0x00320D) return;
                    }
                L_003210:
                    goto L_00323F;
                }
            }
        L_003213:
            if (myMapper->readCPU(0x006A) == 0x0A) {
                goto L_00321D;
            }
        } while (myMapper->readCPU(0x004F) != 0);
    L_00321D:
        a = myMapper->readCPU(0x0014);
        opORA(myMapper->readCPU(0x00F5));
        myMapper->writeCPU(0x0014, a);
        myMapper->writeCPU(0x0084, 0x05);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0018, a);
        if (flgZ) {
            goto L_0031BD;
        }
    L_00322D:
        a = myMapper->readCPU(0x0035);
        flgC = false;
        opADC(0x30);
        if (a >= 0x40) {
            a = 0x40;
        }
        myMapper->writeCPU(0x0035, a);
        a = 0x04;
        pushAddress(0x00323C);
        SUB_0051A5();
        if (poppedEntry.value != 0x00323C) return;
    L_00323F:
        a = 0x81;
        myMapper->writeCPU(0x0061, a);
        goto L_003323;
    }
L_003246:
    if (myMapper->readCPU(0x001B) & 0x80) {
        myMapper->writeCPU(0x00B5, myMapper->readCPU(0x001D));
        myMapper->writeCPU(0x00B4, myMapper->readCPU(0x001C));
        pushAddress(0x003252);
        SUB_00336C();
        if (poppedEntry.value != 0x003252) return;
        if (flgC) {
            a = myMapper->readCPU(0x006A);
            if (a != 0x04) {
                if (a != 0x84) {
                    goto L_003279;
                }
                pushAddress(0x003261);
                SUB_00197B();
                if (poppedEntry.value != 0x003261) return;
                a = myMapper->readCPU(0x001B);
                opAND(0xF0);
                opORA(0x08);
                opORA(myMapper->readCPU(0x00B8));
                myMapper->writeCPU(0x001B, a);
            }
            a = myMapper->readCPU(0x001B);
            opORA(0x20);
            opEOR(0x10);
            myMapper->writeCPU(0x001B, a);
            goto L_0032EF;
        L_003279:
            myMapper->writeCPU(0x001B, 0x00);
            a = 0xF8;
            myMapper->writeCPU(0x0710, a);
            myMapper->writeCPU(0x0713, a);
            goto L_0032EF;
        }
    }
    if (myMapper->readCPU(0x001F) & 0x80) {
        myMapper->writeCPU(0x00B5, myMapper->readCPU(0x0021));
        myMapper->writeCPU(0x00B4, myMapper->readCPU(0x0020));
        pushAddress(0x003294);
        SUB_00336C();
        if (poppedEntry.value != 0x003294) return;
        if (flgC) {
            a = myMapper->readCPU(0x006A);
            if (a != 0x04) {
                if (a != 0x84) {
                    goto L_0032BA;
                }
                pushAddress(0x0032A3);
                SUB_00197B();
                if (poppedEntry.value != 0x0032A3) return;
                a = myMapper->readCPU(0x001F);
                opAND(0xF0);
                opORA(0x08);
                opORA(myMapper->readCPU(0x00B8));
                myMapper->writeCPU(0x001F, a);
            }
            a = myMapper->readCPU(0x001F);
            opORA(0x20);
            opEOR(0x10);
            myMapper->writeCPU(0x001F, a);
            if (!flgZ) {
                goto L_0032EF;
            }
        L_0032BA:
            myMapper->writeCPU(0x001F, 0x00);
            a = 0xF8;
            setLoadFlag(a);
            myMapper->writeCPU(0x0714, a);
            myMapper->writeCPU(0x0717, a);
            if (!flgZ) {
                goto L_0032EF;
            }
        }
    }
    a = myMapper->readCPU(0x0027);
    setLoadFlag(a);
    if (!flgN) {
        goto L_003323;
    }
    myMapper->writeCPU(0x00B5, myMapper->readCPU(0x0029));
    myMapper->writeCPU(0x00B4, myMapper->readCPU(0x0028));
    pushAddress(0x0032D4);
    SUB_00336C();
    if (poppedEntry.value != 0x0032D4) return;
    if (!flgC) {
        goto L_003323;
    }
    a = 0x00;
    myMapper->writeCPU(0x0027, a);
    myMapper->writeCPU(0x002D, a);
    a = 0xF8;
    myMapper->writeCPU(0x071C, a);
    myMapper->writeCPU(0x071F, a);
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    if (a == 0x04) {
        goto L_003323;
    }
L_0032EF:
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    if (a == 0x0A) {
        goto L_003326;
    }
    if (a != 0x11) {
        if (a == 0x1E) {
            goto L_003332;
        }
        if (a != 0x18) {
            if (a >= 0x15) {
                goto L_003323;
            }
        }
        a = myMapper->readCPU(0x006A);
        opAND(0x7F);
        opCMP(a, 0x09);
        a = 0x02;
        if (flgC) {
            a = 0x09;
        }
        pushAddress(0x003313);
        SUB_0051A5();
        if (poppedEntry.value != 0x003313) return;
        a = myMapper->readCPU(0x006A);
        if (a != 0x0E) {
            if (a == 0x0F) {
                goto L_003323;
            }
            pushAddress(0x003320);
            SUB_002A97();
            if (poppedEntry.value != 0x003320) return;
        }
    }
    do {
        do {
        L_003323:
            opPLA();
            x = a;
            popAddress();
            return;
        L_003326:
            a = myMapper->readCPU(0x0061);
            opAND(0x20);
        } while (flgZ);
        a = 0x1F;
        setLoadFlag(a);
        myMapper->writeCPU(0x006B, a);
    } while (!flgZ);
L_003332:
    opDEC(0x006C, 1);
    x = myMapper->readCPU(0x006C);
    setLoadFlag(x);
    if (!flgN) {
        pushAddress(0x003338);
        SUB_000ED7();
        if (poppedEntry.value != 0x003338) return;
        myMapper->writeCPU(0x006D, 0x00);
        a = myMapper->readCPU(0xB368 + x);
        myMapper->writeCPU(0x006A, a);
        if (a != 0x1E) {
            goto L_003352;
        }
        a = myMapper->readCPU(0x0061);
        opORA(0x20);
        myMapper->writeCPU(0x0061, a);
        myMapper->writeCPU(0x006D, 0x08);
    L_003352:
        a = 0x00;
        myMapper->writeCPU(0x0066, a);
        myMapper->writeCPU(0x0067, a);
        myMapper->writeCPU(0x0068, a);
        myMapper->writeCPU(0x0069, a);
        myMapper->writeCPU(0x006B, a);
        myMapper->writeCPU(0x006C, a);
        a = 0x03;
        pushAddress(0x003362);
        SUB_0051A5();
        if (poppedEntry.value != 0x003362) return;
    }
    goto L_003323;
}

void game::SUB_00336C() {
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    if (a == 0x0E) {
        SUB_00342C();
        return;
    }
    a = myMapper->readCPU(0x0062);
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    pushAddress(0x00337C);
    SUB_002DBB();
    if (poppedEntry.value != 0x00337C) return;
    if (a < myMapper->readCPU(0xB661 + y)) {
        goto L_003387;
    }
    do {
        SUB_003401();
        return;
    L_003387:
        a = myMapper->readCPU(0x0064);
        flgC = true;
        opSBC(myMapper->readCPU(0x00B5));
        pushAddress(0x00338C);
        SUB_002DBB();
        if (poppedEntry.value != 0x00338C) return;
    } while (a >= myMapper->readCPU(0xB662 + y));
    myMapper->writeCPU(0x00B7, a);
    a = myMapper->readCPU(0x006A);
    if (a == 0x0F) {
        a = myMapper->readCPU(0x00B7);
        if (a >= 0x0C) {
            SUB_0033FF();
            return;
        }
        a = myMapper->readCPU(0x0064);
        opCMP(a, myMapper->readCPU(0x00B5));
        if (flgC) {
            if (flgC) {
                SUB_0033FF();
                return;
            }
        }
        SUB_0033EA();
        return;
    }
    opAND(0x7F);
    if (a >= 0x15) {
        if (a >= 0x18) {
            goto L_0033BE;
        }
        a = 0x00;
        myMapper->writeCPU(0x004B, a);
    }
L_0033BE:
    if (a == 0x11) {
        SUB_0033EC();
        return;
    }
    if (a == 0x1E) {
        SUB_0033EA();
        return;
    }
    if (a == 0x19) {
        SUB_0033EC();
        return;
    }
    if (a == 0x1A) {
        SUB_0033EC();
        return;
    }
    if (a == 0x17) {
        SUB_0033EC();
        return;
    }
    if (a < 0x1C) {
        goto L_0033E2;
    }
    if (a != 0x1D) {
        SUB_0033EC();
        return;
    }
    a = myMapper->readCPU(0x0061);
    opORA(0x20);
    myMapper->writeCPU(0x0061, a);
    flgC = false;
    popAddress();
    return;
L_0033E2:
    if (a == 0x0A) {
        SUB_0033FF();
        return;
    }
    if (a == 0x04) {
        SUB_0033FF();
        return;
    }
    SUB_0033EA();
    return;
}

void game::SUB_0033EA() {
    opINC(0x0054, 1);
    SUB_0033EC();
    return;
}

void game::SUB_0033EC() {
    a = myMapper->readCPU(0x0061);
    opORA(0x40);
    myMapper->writeCPU(0x0061, a);
    myMapper->writeCPU(0x006B, 0x00);
    a = myMapper->readCPU(0x006A);
    if (a != 0x0F) {
        SUB_0033FF();
        return;
    }
    pushAddress(0x0033FC);
    SUB_002A97();
    if (poppedEntry.value != 0x0033FC) return;
    SUB_0033FF();
    return;
}

void game::SUB_0033FF() {
    flgC = true;
    popAddress();
}

void game::SUB_003401() {
    flgC = false;
    popAddress();
}

void game::SUB_003403() {
    x = 0x02;
    a = myMapper->readCPU(0x006A);
    opAND(0x7F);
    if (a >= 0x09) {
        if (a == 0x18) {
            goto L_003427;
        }
        if (a != 0x1E) {
            if (a == 0x0A) {
                goto L_003425;
            }
            x = 0x09;
            if (a < 0x16) {
                goto L_003427;
            }
            x = 0x04;
            if (a < 0x18) {
                goto L_003427;
            }
        L_003425:
            x = 0x07;
        }
    }
L_003427:
    a = x;
    pushAddress(0x003428);
    SUB_0051A5();
    if (poppedEntry.value != 0x003428) return;
    popAddress();
}

void game::SUB_00342C() {
    a = myMapper->readCPU(0x0080);
    opLSR_A(1);
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0x0062);
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    pushAddress(0x003437);
    SUB_002DBB();
    if (poppedEntry.value != 0x003437) return;
    if (a < 0x08) {
        a = myMapper->readCPU(0x0064);
        flgC = true;
        opSBC(myMapper->readCPU(0x00B5));
        pushAddress(0x003443);
        SUB_002DBB();
        if (poppedEntry.value != 0x003443) return;
        if (a < myMapper->readCPU(0xB47C + y)) {
            if (a >= myMapper->readCPU(0xB48D + y)) {
                goto L_003456;
            }
            a = myMapper->readCPU(0x006C);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_003473;
            }
            if (flgZ) {
                goto L_003479;
            }
        L_003456:
            opCMP(myMapper->readCPU(0x0064), myMapper->readCPU(0x00B5));
            a = 0x01;
            if (flgC) {
                a = 0x02;
            }
            if (a == myMapper->readCPU(0x006C)) {
                goto L_003473;
            }
            opORA(myMapper->readCPU(0x006C));
            myMapper->writeCPU(0x006C, a);
            pushAddress(0x003468);
            SUB_002A97();
            if (poppedEntry.value != 0x003468) return;
            a = myMapper->readCPU(0x006C);
            opCMP(a, 0x03);
            if (flgZ) {
                goto L_003476;
            }
            if (!flgZ) {
                goto L_003479;
            }
        }
    }
L_003473:
    SUB_003401();
    return;
L_003476:
    SUB_0033EA();
    return;
L_003479:
    SUB_0033FF();
    return;
}

void game::SUB_0035E2() {
    if (myMapper->readCPU(0x0036) != 0) {
        goto L_00362A;
    }
    if (myMapper->readCPU(0x0091) != 0) {
        goto L_00362A;
    }
    a = myMapper->readCPU(0x0014);
    opAND(0x40);
    if (!flgZ) {
        goto L_00362A;
    }
    x = 0x00;
    do {
        a = myMapper->readCPU(0x02A0 + x);
        if (a < 0xF0) {
            flgC = true;
            opSBC(myMapper->readCPU(0x0015));
            pushAddress(0x0035FC);
            SUB_002DBB();
            if (poppedEntry.value != 0x0035FC) return;
            if (a < 0x0C) {
                a = myMapper->readCPU(0x02A1 + x);
                flgC = true;
                opSBC(myMapper->readCPU(0x0016));
                pushAddress(0x003609);
                SUB_002DBB();
                if (poppedEntry.value != 0x003609) return;
                if (a < 0x06) {
                    a = 0x00;
                    myMapper->writeCPU(0x02A0 + x, a);
                    myMapper->writeCPU(0x02A1 + x, a);
                    if (myMapper->readCPU(0x004F) == 0) {
                        a = myMapper->readCPU(0x0014);
                        opORA(myMapper->readCPU(0x00F5));
                        myMapper->writeCPU(0x0014, a);
                        myMapper->writeCPU(0x0084, 0x05);
                        myMapper->writeCPU(0x0018, 0x00);
                    }
                L_00362A:
                    popAddress();
                    return;
                }
            }
            if (myMapper->readCPU(0x004B) != 0) {
                a = myMapper->readCPU(0x02A0 + x);
                flgC = true;
                opSBC(myMapper->readCPU(0x004C));
                pushAddress(0x003635);
                SUB_002DBB();
                if (poppedEntry.value != 0x003635) return;
                if (a < 0x08) {
                    a = myMapper->readCPU(0x02A1 + x);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x004D));
                    pushAddress(0x003642);
                    SUB_002DBB();
                    if (poppedEntry.value != 0x003642) return;
                    if (a >= 0x10) {
                        goto L_003656;
                    }
                    a = 0x00;
                    myMapper->writeCPU(0x02A0 + x, a);
                    myMapper->writeCPU(0x02A1 + x, a);
                    myMapper->writeCPU(0x004B, 0x40);
                    popAddress();
                    return;
                }
            }
        }
    L_003656:
        opINX(8);
    } while (x < 0x20);
    popAddress();
}

void game::SUB_00369F() {
    a = myMapper->readCPU(0x0053);
    flgC = true;
    opSBC(myMapper->readCPU(0x0054));
    if (a >= myMapper->readCPU(0x0054)) {
        goto L_0036AC;
    }
    a = 0x01;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0036AE;
    }
L_0036AC:
    a = 0x00;
L_0036AE:
    myMapper->writeCPU(0x0086, a);
    popAddress();
}

void game::SUB_0036E2() {
    x = myMapper->readCPU(0x0099);
    setLoadFlag(x);
    if (flgZ) {
        opDEX(1);
        myMapper->writeCPU(0x0099, x);
        pushAddress(0x0036E9);
        SUB_003A3B();
        if (poppedEntry.value != 0x0036E9) return;
    }
    pushAddress(0x0036EC);
    SUB_0039FD();
    if (poppedEntry.value != 0x0036EC) return;
    pushAddress(0x0036EF);
    SUB_00399D();
    if (poppedEntry.value != 0x0036EF) return;
    pushAddress(0x0036F2);
    SUB_00397F();
    if (poppedEntry.value != 0x0036F2) return;
    if (myMapper->readCPU(0x0075) == 0x80) {
        pushAddress(0x0036FB);
        SUB_003711();
        if (poppedEntry.value != 0x0036FB) return;
        pushAddress(0x0036FE);
        SUB_003AD7();
        if (poppedEntry.value != 0x0036FE) return;
    }
    pushAddress(0x003701);
    SUB_0037E8();
    if (poppedEntry.value != 0x003701) return;
    a = myMapper->readCPU(0x0216);
    opORA(myMapper->readCPU(0x021A));
    opAND(0x10);
    if (!flgZ) {
        goto L_003710;
    }
    myMapper->writeCPU(0x0095, a);
L_003710:
    popAddress();
}

void game::SUB_003711() {
    x = 0x00;
    myMapper->writeCPU(0x00B8, x);
    myMapper->writeCPU(0x00B9, 0x08);
    do {
        a = myMapper->readCPU(0x026E + x);
        opAND(0x10);
        if (!flgZ) {
            goto L_003746;
        }
        if (myMapper->readCPU(0x00B8) != 0) {
            goto L_003749;
        }
        a = myMapper->readCPU(0x000B);
        opAND(0x0F);
        if (!flgZ) {
            goto L_003749;
        }
        myMapper->writeCPU(0x00B8, 0xFF);
        a = myMapper->readCPU(0x00A8);
        opAND(0x04);
        y = a;
        a = myMapper->readCPU(0x0208 + y);
        myMapper->writeCPU(0x026C + x, a);
        myMapper->writeCPU(0x0064, a);
        a = myMapper->readCPU(0x020B + y);
        myMapper->writeCPU(0x026F + x, a);
        myMapper->writeCPU(0x0062, a);
        pushAddress(0x003743);
        SUB_003753();
        if (poppedEntry.value != 0x003743) return;
    L_003746:
        pushAddress(0x003746);
        SUB_0037A0();
        if (poppedEntry.value != 0x003746) return;
    L_003749:
        a = x;
        flgC = false;
        opADC(0x0A);
        x = a;
        opDEC(0x00B9, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003753() {
    y = 0x00;
    a = myMapper->readCPU(0x00A8);
    opAND(0x02);
    if (!flgZ) {
        y = 0x20;
        a = myMapper->readCPU(0x00A8);
        opAND(0x04);
        if (!flgZ) {
            y = 0xE0;
        }
    }
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x0064));
    myMapper->writeCPU(0x0064, a);
    a = x;
    opPHA();
    pushAddress(0x00376D);
    SUB_002DC3();
    if (poppedEntry.value != 0x00376D) return;
    opPLA();
    x = a;
    if (myMapper->readCPU(0x0080) == 0x7E) {
        goto L_003786;
    }
    a = myMapper->readCPU(0x00A0);
    opASL_A(1);
    opROR_M(0x00A0, 1);
    opROR_M(0x00A1, 1);
    a = myMapper->readCPU(0x00A2);
    opASL_A(1);
    opROR_M(0x00A2, 1);
    opROR_M(0x00A3, 1);
L_003786:
    myMapper->writeCPU(0x0272 + x, myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x0273 + x, myMapper->readCPU(0x00A1));
    myMapper->writeCPU(0x0274 + x, myMapper->readCPU(0x00A2));
    myMapper->writeCPU(0x0275 + x, myMapper->readCPU(0x00A3));
    myMapper->writeCPU(0x026E + x, 0x10);
    popAddress();
}

void game::SUB_0037A0() {
    a = myMapper->readCPU(0x000B);
    opLSR_A(2);
    opAND(0x01);
    flgC = false;
    opADC(0x37);
    myMapper->writeCPU(0x026D + x, a);
    a = myMapper->readCPU(0x0270 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0273 + x));
    myMapper->writeCPU(0x0270 + x, a);
    a = myMapper->readCPU(0x026C + x);
    opADC(myMapper->readCPU(0x0272 + x));
    myMapper->writeCPU(0x026C + x, a);
    if (a >= 0x40) {
        if (a >= 0xC8) {
            goto L_0037E2;
        }
        a = myMapper->readCPU(0x0271 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x0275 + x));
        myMapper->writeCPU(0x0271 + x, a);
        a = myMapper->readCPU(0x026F + x);
        opADC(myMapper->readCPU(0x0274 + x));
        myMapper->writeCPU(0x026F + x, a);
        if (a < 0x08) {
            goto L_0037E2;
        }
        if (a < 0xF8) {
            goto L_0037E7;
        }
    }
L_0037E2:
    myMapper->writeCPU(0x026E + x, 0x00);
L_0037E7:
    popAddress();
}

void game::SUB_0037E8() {
    a = myMapper->readCPU(0x0200);
    myMapper->writeCPU(0x0720, a);
    myMapper->writeCPU(0x0724, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0728, a);
    myMapper->writeCPU(0x072C, a);
    a = myMapper->readCPU(0x0202);
    opAND(0x10);
    if (!flgZ) {
        goto L_00380F;
    }
    a = 0xF0;
    myMapper->writeCPU(0x0720, a);
    myMapper->writeCPU(0x0724, a);
    myMapper->writeCPU(0x0728, a);
    myMapper->writeCPU(0x072C, a);
L_00380F:
    y = myMapper->readCPU(0x0201);
    myMapper->writeCPU(0x0721, y);
    opINY(1);
    myMapper->writeCPU(0x0725, y);
    opINY(1);
    myMapper->writeCPU(0x0729, y);
    opINY(1);
    myMapper->writeCPU(0x072D, y);
    a = myMapper->readCPU(0x0202);
    opAND(0xE3);
    myMapper->writeCPU(0x0722, a);
    myMapper->writeCPU(0x0726, a);
    myMapper->writeCPU(0x072A, a);
    myMapper->writeCPU(0x072E, a);
    a = myMapper->readCPU(0x0203);
    myMapper->writeCPU(0x0723, a);
    myMapper->writeCPU(0x072B, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0727, a);
    myMapper->writeCPU(0x072F, a);
    x = 0x04;
    myMapper->writeCPU(0x00B4, 0x06);
    y = 0x10;
    do {
        a = myMapper->readCPU(0x0200 + x);
        myMapper->writeCPU(0x0720 + y, a);
        myMapper->writeCPU(0x0724 + y, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0728 + y, a);
        myMapper->writeCPU(0x072C + y, a);
        a = myMapper->readCPU(0x0202 + x);
        opAND(0x10);
        if (!flgZ) {
            goto L_003873;
        }
        a = 0xFF;
        myMapper->writeCPU(0x0720 + y, a);
        myMapper->writeCPU(0x0724 + y, a);
        myMapper->writeCPU(0x0728 + y, a);
        myMapper->writeCPU(0x072C + y, a);
    L_003873:
        opINX(1);
        a = myMapper->readCPU(0x0200 + x);
        myMapper->writeCPU(0x0721 + y, a);
        myMapper->writeCPU(0x0725 + y, a);
        myMapper->writeCPU(0x0729 + y, a);
        myMapper->writeCPU(0x072D + y, a);
        opINX(1);
        a = myMapper->readCPU(0x0200 + x);
        opAND(0x23);
        myMapper->writeCPU(0x0722 + y, a);
        opORA(0x40);
        myMapper->writeCPU(0x0726 + y, a);
        opORA(0xC0);
        myMapper->writeCPU(0x072E + y, a);
        opAND(0xBF);
        myMapper->writeCPU(0x072A + y, a);
        opINX(1);
        a = myMapper->readCPU(0x0200 + x);
        myMapper->writeCPU(0x0723 + y, a);
        myMapper->writeCPU(0x072B + y, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0727 + y, a);
        myMapper->writeCPU(0x072F + y, a);
        opINX(1);
        a = y;
        flgC = false;
        opADC(0x10);
        y = a;
        opDEC(0x00B4, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x00B4, 0x04);
    do {
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        a = myMapper->readCPU(0x0202 + x);
        opAND(0x10);
        if (!flgZ) {
            goto L_0038CE;
        }
        myMapper->writeCPU(0x0720 + y, 0xF0);
    L_0038CE:
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        opINX(1);
        opINY(1);
        a = myMapper->readCPU(0x0200 + x);
        opAND(0xE3);
        myMapper->writeCPU(0x0720 + y, a);
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        opINX(1);
        opINY(1);
        opDEC(0x00B4, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x00B4, 0x10);
    do {
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        a = myMapper->readCPU(0x0202 + x);
        opAND(0x10);
        if (!flgZ) {
            goto L_003904;
        }
        myMapper->writeCPU(0x0720 + y, 0xF0);
    L_003904:
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        opINX(1);
        opINY(1);
        a = myMapper->readCPU(0x0200 + x);
        opAND(0xE3);
        myMapper->writeCPU(0x0720 + y, a);
        opINX(1);
        opINY(1);
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        opINX(1);
        opINY(1);
        opDEC(0x00B4, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x00B4, 0x08);
    do {
        myMapper->writeCPU(0x0720 + y, myMapper->readCPU(0x0200 + x));
        a = myMapper->readCPU(0x0202 + x);
        opAND(0x10);
        if (!flgZ) {
            goto L_00393A;
        }
        myMapper->writeCPU(0x0720 + y, 0xF0);
    L_00393A:
        myMapper->writeCPU(0x0721 + y, myMapper->readCPU(0x0201 + x));
        a = myMapper->readCPU(0x0202 + x);
        opAND(0xE3);
        myMapper->writeCPU(0x0722 + y, a);
        myMapper->writeCPU(0x0723 + y, myMapper->readCPU(0x0203 + x));
        opINY(4);
        a = x;
        flgC = false;
        opADC(0x0A);
        x = a;
        opDEC(0x00B4, 1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0075);
    opEOR(0x7F);
    myMapper->writeCPU(0x00B4, a);
    opINC(0x00B4, 1);
    x = 0x20;
    do {
        a = myMapper->readCPU(0x0703 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x0703 + x, a);
        if (!flgC) {
            goto L_003975;
        }
        myMapper->writeCPU(0x0700 + x, 0xF1);
    L_003975:
        opDEC(0x0700 + x, 1);
        opINX(4);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00397F() {
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x021E + x);
        opAND(0xFC);
        myMapper->writeCPU(0x00B4, a);
        a = myMapper->readCPU(0x000B);
        opLSR_A(2);
        opAND(0x03);
        opORA(myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x021E + x, a);
        opINX(4);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00399D() {
    x = 0x00;
    y = 0x00;
    do {
        a = myMapper->readCPU(0x000B);
        myMapper->writeCPU(0x00B4, a);
        opAND(0x10);
        if (!flgZ) {
            a = myMapper->readCPU(0x000B);
            opEOR(0xFF);
            myMapper->writeCPU(0x00B4, a);
        }
        myMapper->writeCPU(0x00B5, myMapper->readCPU(0x00B4));
        a = y;
        opAND(0x01);
        if (!flgZ) {
            a = myMapper->readCPU(0x00B5);
            opEOR(0xFF);
            myMapper->writeCPU(0x00B5, a);
        }
        if (y < 0x04) {
            goto L_0039C4;
        }
        opASL_M(0x00B5, 1);
    L_0039C4:
        a = myMapper->readCPU(0x00B5);
        opAND(0x0F);
        flgC = false;
        opADC(myMapper->readCPU(0xBA7F + x));
        myMapper->writeCPU(0x0204 + x, a);
        a = myMapper->readCPU(0x0206 + x);
        opAND(0xFC);
        myMapper->writeCPU(0x00B4, a);
        a = myMapper->readCPU(0x000B);
        opLSR_A(2);
        opAND(0x03);
        opORA(myMapper->readCPU(0x00B4));
        myMapper->writeCPU(0x0206 + x, a);
        opINX(4);
        opINY(1);
    } while (y != 0x06);
    a = myMapper->readCPU(0x0202);
    opAND(0xFC);
    myMapper->writeCPU(0x00B4, a);
    a = myMapper->readCPU(0x000B);
    opLSR_A(2);
    opAND(0x03);
    opORA(myMapper->readCPU(0x00B4));
    myMapper->writeCPU(0x0202, a);
    popAddress();
}

void game::SUB_0039FD() {
    x = 0x01;
    y = 0x00;
    a = myMapper->readCPU(0x000B);
    opLSR_A(2);
    myMapper->writeCPU(0x00B4, a);
    do {
        if (y == 0x01) {
            goto L_003A31;
        }
        if (y != 0x02) {
            if (y == 0x0B) {
                goto L_003A31;
            }
            if (y != 0x0C) {
                a = y;
                flgC = false;
                opADC(myMapper->readCPU(0x00B4));
                myMapper->writeCPU(0x00B5, a);
                opAND(0x04);
                if (flgZ) {
                    goto L_003A27;
                }
                a = myMapper->readCPU(0x00B5);
                opEOR(0xFF);
                myMapper->writeCPU(0x00B5, a);
            L_003A27:
                a = myMapper->readCPU(0x00B5);
                opAND(0x03);
                flgC = false;
                opADC(0xD7);
                myMapper->writeCPU(0x022C + x, a);
            }
        }
    L_003A31:
        opINX(4);
        opINY(1);
    } while (y != 0x10);
    popAddress();
}

void game::SUB_003A3B() {
    x = 0x2B;
    do {
        myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0xBA7B + x));
        opDEX(1);
    } while (!flgN);
    x = 0x00;
    y = 0x00;
    myMapper->writeCPU(0x00B4, 0x10);
    do {
        myMapper->writeCPU(0x022C + x, myMapper->readCPU(0xBAA9 + y));
        opINX(1);
        myMapper->writeCPU(0x022C + x, 0xD7);
        opINX(1);
        myMapper->writeCPU(0x022C + x, myMapper->readCPU(0xBAA7 + y));
        opINX(1);
        myMapper->writeCPU(0x022C + x, myMapper->readCPU(0xBAA8 + y));
        opINX(1);
        opINY(3);
        opDEC(0x00B4, 1);
    } while (!flgZ);
    x = 0x4F;
    a = 0x00;
    do {
        myMapper->writeCPU(0x026C + x, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_003AD7() {
    pushAddress(0x003AD7);
    SUB_003AE7();
    if (poppedEntry.value != 0x003AD7) return;
    pushAddress(0x003ADA);
    SUB_003B44();
    if (poppedEntry.value != 0x003ADA) return;
    pushAddress(0x003ADD);
    SUB_003B8A();
    if (poppedEntry.value != 0x003ADD) return;
    popAddress();
}

void game::SUB_003AE1() {
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
    popAddress();
}

void game::SUB_003AE7() {
    x = 0x00;
    y = 0x00;
    do {
        if (x != 0x1C) {
            goto L_003AF1;
        }
        y = 0x04;
    L_003AF1:
        a = myMapper->readCPU(0x0014);
        opAND(0x40);
        if (flgZ) {
            a = myMapper->readCPU(0x0202 + x);
            opAND(0x08);
            if (flgZ) {
                a = myMapper->readCPU(0x0200 + x);
                flgC = false;
                opADC(myMapper->readCPU(0xBB3C + y));
                flgC = true;
                opSBC(myMapper->readCPU(0x0016));
                if (flgN) {
                    pushAddress(0x003B0A);
                    SUB_003AE1();
                    if (poppedEntry.value != 0x003B0A) return;
                }
                if (a < myMapper->readCPU(0xBB3D + y)) {
                    a = myMapper->readCPU(0x0203 + x);
                    flgC = false;
                    opADC(myMapper->readCPU(0xBB3E + y));
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0015));
                    if (flgN) {
                        pushAddress(0x003B1E);
                        SUB_003AE1();
                        if (poppedEntry.value != 0x003B1E) return;
                    }
                    if (a >= myMapper->readCPU(0xBB3F + y)) {
                        goto L_003B33;
                    }
                    a = myMapper->readCPU(0x0202 + x);
                    opAND(0xEF);
                    opORA(0x08);
                    myMapper->writeCPU(0x0202 + x, a);
                    pushAddress(0x003B30);
                    SUB_003CD1();
                    if (poppedEntry.value != 0x003B30) return;
                }
            }
        }
    L_003B33:
        opINX(4);
    } while (x != 0x2C);
    popAddress();
}

void game::SUB_003B44() {
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0014);
        opAND(0x40);
        if (flgZ) {
            a = myMapper->readCPU(0x026E + x);
            opEOR(0x10);
            opAND(0x08);
            if (flgZ) {
                a = myMapper->readCPU(0x026C + x);
                flgC = true;
                opSBC(myMapper->readCPU(0x0016));
                if (flgN) {
                    pushAddress(0x003B5D);
                    SUB_003AE1();
                    if (poppedEntry.value != 0x003B5D) return;
                }
                if (a < 0x03) {
                    a = myMapper->readCPU(0x026F + x);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0015));
                    if (flgN) {
                        pushAddress(0x003B6C);
                        SUB_003AE1();
                        if (poppedEntry.value != 0x003B6C) return;
                    }
                    if (a >= 0x07) {
                        goto L_003B80;
                    }
                    a = myMapper->readCPU(0x026E + x);
                    opAND(0xEF);
                    opORA(0x08);
                    myMapper->writeCPU(0x026E + x, a);
                    pushAddress(0x003B7D);
                    SUB_003CD1();
                    if (poppedEntry.value != 0x003B7D) return;
                }
            }
        }
    L_003B80:
        a = x;
        flgC = false;
        opADC(0x0A);
        x = a;
    } while (x != 0x50);
    popAddress();
}

void game::SUB_003B8A() {
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0222);
        opAND(0x08);
        if (!flgZ) {
            goto L_003BEF;
        }
        a = 0x0A;
        x = 0x0A;
        if (y < 0x0C) {
            a = 0x05;
            x = 0x08;
        }
        myMapper->writeCPU(0x00B4, a);
        myMapper->writeCPU(0x00B5, x);
        if (myMapper->readCPU(0x001B + y) & 0x80) {
            a = myMapper->readCPU(0x0220);
            flgC = false;
            opADC(0x04);
            flgC = true;
            opSBC(myMapper->readCPU(0x001D + y));
            if (flgN) {
                pushAddress(0x003BB4);
                SUB_003AE1();
                if (poppedEntry.value != 0x003BB4) return;
            }
            if (a < myMapper->readCPU(0x00B4)) {
                a = myMapper->readCPU(0x0223);
                flgC = false;
                opADC(0x04);
                flgC = true;
                opSBC(myMapper->readCPU(0x001C + y));
                if (flgN) {
                    pushAddress(0x003BC7);
                    SUB_003AE1();
                    if (poppedEntry.value != 0x003BC7) return;
                }
                if (a < myMapper->readCPU(0x00B5)) {
                    pushAddress(0x003BCE);
                    SUB_003CDD();
                    if (poppedEntry.value != 0x003BCE) return;
                    a = myMapper->readCPU(0x020E);
                    opAND(0x08);
                    if (flgZ) {
                        goto L_003BE7;
                    }
                    a = myMapper->readCPU(0x0222);
                    opAND(0xEF);
                    opORA(0x08);
                    myMapper->writeCPU(0x0222, a);
                    a = 0x09;
                    pushAddress(0x003BE4);
                    SUB_0051A5();
                    if (poppedEntry.value != 0x003BE4) return;
                }
            }
        }
    L_003BE7:
        opINY(4);
    } while (y != 0x10);
L_003BEF:
    y = 0x00;
    do {
        myMapper->writeCPU(0x00B6, y);
        x = 0x00;
        pushAddress(0x003BF5);
        SUB_003C05();
        if (poppedEntry.value != 0x003BF5) return;
        if (flgZ) {
            goto L_003C04;
        }
        y = myMapper->readCPU(0x00B6);
        opINY(4);
    } while (y != 0x10);
L_003C04:
    popAddress();
}

void game::SUB_003C05() {
    while (true) {
        myMapper->writeCPU(0x00B6, y);
        myMapper->writeCPU(0x00B4, myMapper->readCPU(0xBC89 + x));
        myMapper->writeCPU(0x00B5, myMapper->readCPU(0xBC8A + x));
        y = 0x02;
        a = myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y);
        opAND(0x08);
        if (flgZ) {
            y = myMapper->readCPU(0x00B6);
            if (!(myMapper->readCPU(0x001B + y) & 0x80)) {
                goto L_003C86;
            }
            y = 0x00;
            a = myMapper->readCPU(0xBCC0 + x);
            flgC = false;
            opADC(myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x00B6);
            flgC = true;
            opSBC(myMapper->readCPU(0x001D + y));
            if (flgN) {
                pushAddress(0x003C30);
                SUB_003AE1();
                if (poppedEntry.value != 0x003C30) return;
            }
            if (y < 0x0C) {
                opCMP(a, myMapper->readCPU(0xBCAD + x));
            }
            else {
                opCMP(a, myMapper->readCPU(0xBCAE + x));
            }
            if (flgC) {
                goto L_003C86;
            }
            y = 0x03;
            a = myMapper->readCPU(0xBCBF + x);
            flgC = false;
            opADC(myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
            y = myMapper->readCPU(0x00B6);
            flgC = true;
            opSBC(myMapper->readCPU(0x001C + y));
            if (flgN) {
                pushAddress(0x003C52);
                SUB_003AE1();
                if (poppedEntry.value != 0x003C52) return;
            }
            if (y >= 0x0C) {
                goto L_003C5F;
            }
            opCMP(a, myMapper->readCPU(0xBC9B + x));
            goto L_003C62;
        L_003C5F:
            opCMP(a, myMapper->readCPU(0xBC9C + x));
        L_003C62:
            if (flgC) {
                goto L_003C86;
            }
            y = myMapper->readCPU(0x00B6);
            pushAddress(0x003C66);
            SUB_003CDD();
            if (poppedEntry.value != 0x003C66) return;
            y = 0x02;
            a = myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y);
            opAND(0xEF);
            opORA(0x08);
            myMapper->writeCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y, a);
            a = 0x09;
            pushAddress(0x003C75);
            SUB_0051A5();
            if (poppedEntry.value != 0x003C75) return;
        }
        y = myMapper->readCPU(0x00B6);
        opINX(2);
        if (x == 0x12) {
            goto L_003C83;
        }
    }
L_003C83:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
    return;
L_003C86:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_003CD1() {
    a = 0x05;
    pushAddress(0x003CD3);
    SUB_0051A5();
    if (poppedEntry.value != 0x003CD3) return;
    a = myMapper->readCPU(0x0014);
    opORA(myMapper->readCPU(0x00F5));
    myMapper->writeCPU(0x0014, a);
    popAddress();
}

void game::SUB_003CDD() {
    a = 0x00;
    myMapper->writeCPU(0x001B + y, a);
    myMapper->writeCPU(0x001C + y, a);
    myMapper->writeCPU(0x0713 + y, a);
    a = 0xF8;
    myMapper->writeCPU(0x001D + y, a);
    myMapper->writeCPU(0x0710 + y, a);
    if (y < 0x0C) {
        goto L_003CF8;
    }
    myMapper->writeCPU(0x002D, 0x00);
L_003CF8:
    popAddress();
}

void game::SUB_003CF9() {
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    x = 0xC0;
    do {
        myMapper->writeCPU(0x2007, 0xAA);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x24);
    myMapper->writeCPU(0x2006, 0x00);
    x = 0xC0;
    do {
        myMapper->writeCPU(0x2007, 0xAA);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003D2D() {
    a = 0x00;
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x2000, a);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    y = 0x04;
    x = 0x00;
    do {
        do {
            myMapper->writeCPU(0x2007, 0xAA);
            opDEX(1);
        } while (!flgZ);
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0xC0);
    x = 0x40;
    a = 0xFF;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    popAddress();
}

void game::SUB_0046BB() {
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x00C2, a);
    if (!flgZ) {
        SUB_0046C7();
        return;
    }
    SUB_0046C1();
    return;
}

void game::SUB_0046C1() {
    myMapper->writeCPU(0x00C2, 0xF0);
    a = 0x00;
    SUB_0046C7();
    return;
}

void game::SUB_0046C7() {
    myMapper->writeCPU(0x00BA, a);
    a = 0x08;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x00F9, a);
    pushAddress(0x0046D0);
    SUB_000150();
    if (poppedEntry.value != 0x0046D0) return;
    if (myMapper->readCPU(0x00BA) != 0) {
        pushAddress(0x0046D7);
        SUB_003D2D();
        if (poppedEntry.value != 0x0046D7) return;
        myMapper->writeCPU(0x2001, 0x10);
    }
    else {
        pushAddress(0x0046E2);
        SUB_0048B0();
        if (poppedEntry.value != 0x0046E2) return;
        pushAddress(0x0046E5);
        SUB_0001E1();
        if (poppedEntry.value != 0x0046E5) return;
    }
    pushAddress(0x0046E8);
    SUB_004956();
    if (poppedEntry.value != 0x0046E8) return;
    a = 0x80;
    opORA(myMapper->readCPU(0x00F9));
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x00F9, a);
    while (true) {
        do {
            while (true) {
                do {
                    wait();
                L_0046F4:
                    a = myMapper->readCPU(0x0000);
                } while (a == myMapper->readCPU(0x0001));
                myMapper->writeCPU(0x0001, a);
                pushAddress(0x0046FC);
                SUB_001A2C();
                if (poppedEntry.value != 0x0046FC) return;
                opINC(0x000B, 1);
                if (myMapper->readCPU(0x00BA) == 0) {
                    pushAddress(0x004705);
                    SUB_0001D4();
                    if (poppedEntry.value != 0x004705) return;
                }
                pushAddress(0x004708);
                SUB_005356();
                if (poppedEntry.value != 0x004708) return;
                a = myMapper->readCPU(0x0003);
                opAND(0x10);
                if (!flgZ) {
                    if (myMapper->readCPU(0x0091) != 0) {
                        goto L_004716;
                    }
                    popAddress();
                    return;
                }
            L_004716:
                a = myMapper->readCPU(0x000B);
                opAND(0x07);
                if (!flgZ) {
                    goto L_00472E;
                }
                x = 0x08;
                opPHA();
                do {
                    pushAddress(0x00471F);
                    SUB_0030C9();
                    if (poppedEntry.value != 0x00471F) return;
                    opAND(0x03);
                    myMapper->writeCPU(0x0702 + x, a);
                    opINX(4);
                } while (!flgZ);
                opPLA();
            L_00472E:
                opLSR_A(1);
                if (flgC) {
                    goto L_004737;
                }
                pushAddress(0x004731);
                SUB_004817();
                if (poppedEntry.value != 0x004731) return;
            }
        L_004737:
            if (myMapper->readCPU(0x00BA) == 0) {
                goto L_004797;
            }
            if (myMapper->readCPU(0x0700) < 0xAD) {
                goto L_00474A;
            }
            a = myMapper->readCPU(0x000B);
            opAND(0x03);
        } while (a != 0x03);
    L_00474A:
        myMapper->writeCPU(0x00B4, 0x08);
        x = 0x00;
        do {
            a = myMapper->readCPU(0x0200 + x);
            opPHA();
            opLSR_A(3);
            y = a;
            myMapper->writeCPU(0x00B8, myMapper->readCPU(0xC7EF + y));
            a = myMapper->readCPU(0xC7F3 + y);
            myMapper->writeCPU(0x00B9, a);
            opPLA();
            opAND(0x07);
            opASL_A(1);
            y = a;
            myMapper->writeCPU(0x00B6, myMapper->readCPU(0xC7F7 + y));
            myMapper->writeCPU(0x00B7, myMapper->readCPU(0xC7F8 + y));
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00B6) + (myMapper->readCPU((0x00B6 + 1) & 0x00ff) << 8) + y);
            opEOR(myMapper->readCPU(0x00B8));
            opPHA();
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00B6) + (myMapper->readCPU((0x00B6 + 1) & 0x00ff) << 8) + y);
            opEOR(myMapper->readCPU(0x00B9));
            y = myMapper->readCPU(0x00B4);
            flgC = false;
            opADC(myMapper->readCPU(0x0700 + y));
            myMapper->writeCPU(0x0700 + y, a);
            opPLA();
            flgC = false;
            opADC(myMapper->readCPU(0x0703 + y));
            myMapper->writeCPU(0x0703 + y, a);
            opINX(1);
            opINY(4);
            myMapper->writeCPU(0x00B4, y);
        } while (!flgZ);
    L_004797:
        a = myMapper->readCPU(0x000B);
        opAND(0x03);
        if (a == 0x03) {
            goto L_0047A2;
        }
    }
L_0047A2:
    opDEC(0x0700, 1);
    opDEC(0x0704, 1);
    a = myMapper->readCPU(0x0700);
    opCMP(a, 0x7C);
    if (!flgC) {
        a = 0x7C;
        myMapper->writeCPU(0x0700, a);
        myMapper->writeCPU(0x0704, a);
        a = 0xAA;
        myMapper->writeCPU(0x0701, a);
        myMapper->writeCPU(0x0705, a);
        opDEC(0x00C2, 1);
        if (flgZ) {
            a = 0x00;
            popAddress();
            return;
        }
        goto L_0046F4;
    }
    if (a == 0xAD) {
        x = 0xC0;
        myMapper->writeCPU(0x0701, x);
        opINX(1);
        myMapper->writeCPU(0x0705, x);
        if (!flgZ) {
            goto L_0047EC;
        }
    }
    if (a != 0x95) {
        goto L_0047EC;
    }
    a = 0xC2;
    myMapper->writeCPU(0x0701, a);
    myMapper->writeCPU(0x0705, a);
    a = 0x75;
    myMapper->writeCPU(0x0703, a);
    myMapper->writeCPU(0x0707, a);
L_0047EC:
    goto L_0046F4;
}

void game::SUB_004817() {
    y = 0x08;
    x = 0x00;
    do {
        a = x;
        opPHA();
        a = myMapper->readCPU(0x0700 + y);
        if (a >= 0x08) {
            if (a >= 0xE8) {
                goto L_00486F;
            }
            a = myMapper->readCPU(0x0703 + y);
            if (a >= 0x08) {
                if (a >= 0xF8) {
                    goto L_00486F;
                }
                x = 0x00;
                if (a >= 0x5A) {
                    if (a < 0x96) {
                        goto L_004847;
                    }
                }
                opINX(1);
                if (a >= 0x34) {
                    if (a < 0xBC) {
                        goto L_004847;
                    }
                }
                opINX(1);
            L_004847:
                myMapper->writeCPU(0x0701 + y, myMapper->readCPU(0xC87C + x));
                a = myMapper->readCPU(0x0700 + y);
                x = 0x00;
                if (a >= 0x5A) {
                    if (a < 0x96) {
                        goto L_004864;
                    }
                }
                opINX(1);
                if (a < 0x3C) {
                    goto L_004863;
                }
                if (a < 0xB4) {
                    goto L_004864;
                }
            L_004863:
                opINX(1);
            L_004864:
                a = myMapper->readCPU(0xC87C + x);
                myMapper->writeCPU(0x0701 + y, a);
                opPLA();
                x = a;
                goto L_004874;
            }
        }
    L_00486F:
        opPLA();
        x = a;
        pushAddress(0x004871);
        SUB_00487F();
        if (poppedEntry.value != 0x004871) return;
    L_004874:
        opINX(1);
        opINY(4);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00487F() {
    pushAddress(0x00487F);
    SUB_0030C9();
    if (poppedEntry.value != 0x00487F) return;
    opAND(0x1F);
    myMapper->writeCPU(0x0200 + x, a);
    opASL_A(1);
    myMapper->writeCPU(0x00B4, y);
    y = a;
    pushAddress(0x00488B);
    SUB_0030C9();
    if (poppedEntry.value != 0x00488B) return;
    opAND(0x07);
    flgC = true;
    opSBC(0x03);
    flgC = false;
    opADC(myMapper->readCPU(0xC8AE));
    opPHA();
    pushAddress(0x004898);
    SUB_0030C9();
    if (poppedEntry.value != 0x004898) return;
    opAND(0x07);
    flgC = true;
    opSBC(0x03);
    flgC = false;
    opADC(myMapper->readCPU(0xC8AF));
    y = myMapper->readCPU(0x00B4);
    myMapper->writeCPU(0x0700 + y, a);
    opPLA();
    myMapper->writeCPU(0x0703 + y, a);
    popAddress();
}

void game::SUB_0048B0() {
    myMapper->writeCPU(0x00B4, 0xCD);
    myMapper->writeCPU(0x00B5, 0xCA);
    y = 0x00;
    wait();
//L_0048BA:
//    if (myMapper->readCPU(0x2002) & 0x80) {
//        goto L_0048BA;
//    }
//L_0048BF:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_0048BF;
//    }
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    x = 0x00;
    while (true) {
        while (true) {
            a = myMapper->readCPU(myMapper->readCPU((0x00B4 + x) & 0x00ff) + (myMapper->readCPU((0x00B4 + x + 1) & 0x00ff) << 8));
            pushAddress(0x0048DA);
            SUB_00494F();
            if (poppedEntry.value != 0x0048DA) return;
            if (a == 0xF9) {
                goto L_0048FC;
            }
            if (a != 0xAA) {
                goto L_0048F6;
            }
            y = myMapper->readCPU(myMapper->readCPU((0x00B4 + x) & 0x00ff) + (myMapper->readCPU((0x00B4 + x + 1) & 0x00ff) << 8));
            a = 0xAA;
            do {
                myMapper->writeCPU(0x2007, a);
                opDEY(1);
            } while (!flgZ);
            pushAddress(0x0048F0);
            SUB_00494F();
            if (poppedEntry.value != 0x0048F0) return;
        }
    L_0048F6:
        myMapper->writeCPU(0x2007, a);
    }
L_0048FC:
    pushAddress(0x0048FC);
    SUB_004944();
    if (poppedEntry.value != 0x0048FC) return;
    myMapper->writeCPU(0x00B4, 0xAD);
    myMapper->writeCPU(0x00B5, 0xCA);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x00B4) + (myMapper->readCPU((0x00B4 + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x20);
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    pushAddress(0x004930);
    SUB_004944();
    if (poppedEntry.value != 0x004930) return;
    myMapper->writeCPU(0x2001, 0x1A);
    a = myMapper->readCPU(0x2002);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    popAddress();
}

void game::SUB_004944() {
    wait();
//L_004944:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_004944;
//    }
//L_004949:
//    if (myMapper->readCPU(0x2002) & 0x80) {
//        goto L_004949;
//    }
    popAddress();
}

void game::SUB_00494F() {
    opINC(0x00B4, 1);
    if (!flgZ) {
        goto L_004955;
    }
    opINC(0x00B5, 1);
L_004955:
    popAddress();
}

void game::SUB_004956() {
    x = 0x00;
    do {
        myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0xC9B5 + x));
        opINX(1);
    } while (x != 0x3E);
    y = 0x00;
    x = 0x08;
    do {
        myMapper->writeCPU(0x0700 + x, myMapper->readCPU(0xC9F3 + y));
        a = myMapper->readCPU(0xC9F4 + y);
        opPHA();
        opLSR_A(4);
        flgC = false;
        opADC(0xB6);
        myMapper->writeCPU(0x0701 + x, a);
        opPLA();
        opAND(0x0F);
        myMapper->writeCPU(0x0702 + x, a);
        myMapper->writeCPU(0x0703 + x, myMapper->readCPU(0xC9F5 + y));
        opINY(3);
        opINX(4);
    } while (!flgZ);
    a = 0xD0;
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0704, a);
    myMapper->writeCPU(0x0701, 0xBE);
    myMapper->writeCPU(0x0705, 0xBF);
    a = 0x00;
    myMapper->writeCPU(0x0702, a);
    myMapper->writeCPU(0x0706, a);
    myMapper->writeCPU(0x0703, 0x70);
    myMapper->writeCPU(0x0707, 0x78);
    popAddress();
}

void game::SUB_004D21() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    pushAddress(0x004D29);
    SUB_000150();
    if (poppedEntry.value != 0x004D29) return;
    pushAddress(0x004D2C);
    SUB_004E30();
    if (poppedEntry.value != 0x004D2C) return;
    pushAddress(0x004D2F);
    SUB_003D2D();
    if (poppedEntry.value != 0x004D2F) return;
    pushAddress(0x004D32);
    SUB_004E30();
    if (poppedEntry.value != 0x004D32) return;
    a = myMapper->readCPU(0x0092);
    opPHA();
    myMapper->writeCPU(0x0092, 0x04);
    pushAddress(0x004D3C);
    SUB_0024EE();
    if (poppedEntry.value != 0x004D3C) return;
    pushAddress(0x004D3F);
    SUB_004D48();
    if (poppedEntry.value != 0x004D3F) return;
    opPLA();
    myMapper->writeCPU(0x0092, a);
    SUB_0051E0();
    return;
}

void game::SUB_004D48() {
    pushAddress(0x004D48);
    SUB_004E30();
    if (poppedEntry.value != 0x004D48) return;
    myMapper->writeCPU(0x4014, 0x07);
    myMapper->writeCPU(0x00B8, 0xFF);
    myMapper->writeCPU(0x00B4, 0x8D);
    myMapper->writeCPU(0x00B5, 0xCE);
    myMapper->writeCPU(0x2000, 0x08);
L_004D61:
    opINC(0x00B8, 1);
    myMapper->writeCPU(0x00B6, 0x00);
    myMapper->writeCPU(0x00B7, 0x20);
    y = 0x00;
    myMapper->writeCPU(0x2001, 0x1A);
    while (true) {
        pushAddress(0x004D72);
        SUB_004E25();
        if (poppedEntry.value != 0x004D72) return;
        pushAddress(0x004D75);
        SUB_001A2C();
        if (poppedEntry.value != 0x004D75) return;
        a = myMapper->readCPU(0x0003);
        opAND(0x10);
        if (!flgZ) {
            popAddress();
            return;
        }
        pushAddress(0x004D7F);
        SUB_004E25();
        if (poppedEntry.value != 0x004D7F) return;
        a = y;
        opPHA();
        opINY(1);
        opAND(0x0F);
        if (flgZ) {
            a = myMapper->readCPU(0x00B8);
            if (a != 0x02) {
                opPLA();
                pushAddress(0x004D90);
                SUB_004E4D();
                if (poppedEntry.value != 0x004D90) return;
                goto L_004DDD;
            }
        }
        opPLA();
        opAND(0x07);
        if (!flgZ) {
            goto L_004DEA;
        }
        if (myMapper->readCPU(0x00B8) == 0x02) {
            if (y < 0x58) {
                goto L_004DA9;
            }
            if (y < 0x98) {
                goto L_004DAF;
            }
        L_004DA9:
            pushAddress(0x004DA9);
            SUB_004E4D();
            if (poppedEntry.value != 0x004DA9) return;
            goto L_004DDD;
        }
    L_004DAF:
        pushAddress(0x004DAF);
        SUB_004E3B();
        if (poppedEntry.value != 0x004DAF) return;
        a = y;
        opPHA();
        pushAddress(0x004DB4);
        SUB_004E49();
        if (poppedEntry.value != 0x004DB4) return;
        x = 0x00;
        y = 0x1A;
        do {
            a = myMapper->readCPU(myMapper->readCPU((0x00B4 + x) & 0x00ff) + (myMapper->readCPU((0x00B4 + x + 1) & 0x00ff) << 8));
            opINC(0x00B4, 1);
            if (flgZ) {
                opINC(0x00B5, 1);
            }
            if (a != 0x00) {
                goto L_004DCF;
            }
            x = y;
            pushAddress(0x004DC9);
            SUB_004E52();
            if (poppedEntry.value != 0x004DC9) return;
            goto L_004DD8;
        L_004DCF:
            pushAddress(0x004DCF);
            SUB_004E5B();
            if (poppedEntry.value != 0x004DCF) return;
            myMapper->writeCPU(0x2007, a);
            opDEY(1);
        } while (!flgZ);
    L_004DD8:
        pushAddress(0x004DD8);
        SUB_004E49();
        if (poppedEntry.value != 0x004DD8) return;
        opPLA();
        y = a;
    L_004DDD:
        a = 0x20;
        flgC = false;
        opADC(myMapper->readCPU(0x00B6));
        myMapper->writeCPU(0x00B6, a);
        a = myMapper->readCPU(0x00B7);
        opADC(0x00);
        myMapper->writeCPU(0x00B7, a);
    L_004DEA:
        if (y >= 0xF0) {
            goto L_004DF1;
        }
    }
L_004DF1:
    if (myMapper->readCPU(0x00B8) < 0x02) {
        goto L_004E22;
    }
    y = 0x04;
    do {
        x = 0x3C;
        do {
            a = x;
            opPHA();
            a = y;
            opPHA();
            wait();
            //do {
            //    a = myMapper->readCPU(0x2002);
            //    setLoadFlag(a);
            //} while (flgN);
            opPLA();
            y = a;
            opPLA();
            x = a;
        //L_004E08:
        //    if (!(myMapper->readCPU(0x2002) & 0x80)) {
        //        goto L_004E08;
        //    }
            pushAddress(0x004E0D);
            SUB_001A2C();
            if (poppedEntry.value != 0x004E0D) return;
            a = myMapper->readCPU(0x0003);
            opAND(0x10);
            if (flgZ) {
                goto L_004E17;
            }
            popAddress();
            return;
        L_004E17:
            opDEX(1);
        } while (!flgZ);
        opDEY(1);
    } while (!flgZ);
    a = y;
    myMapper->writeCPU(0x2001, a);
    popAddress();
    return;
L_004E22:
    goto L_004D61;
}

void game::SUB_004E25() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2005, 0x00);
    myMapper->writeCPU(0x2005, y);
    SUB_004E30();
    return;
}

void game::SUB_004E30() {
	wait();
//L_004E30:
//    if (myMapper->readCPU(0x2002) & 0x80) {
//        goto L_004E30;
//    }
//L_004E35:
//    if (!(myMapper->readCPU(0x2002) & 0x80)) {
//        goto L_004E35;
//    }
    popAddress();
}

void game::SUB_004E3B() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B7));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x00B6));
    popAddress();
}

void game::SUB_004E49() {
    x = 0x03;
    setLoadFlag(x);
    if (!flgZ) {
        SUB_004E52();
        return;
    }
    SUB_004E4D();
    return;
}

void game::SUB_004E4D() {
    pushAddress(0x004E4D);
    SUB_004E3B();
    if (poppedEntry.value != 0x004E4D) return;
    x = 0x20;
    SUB_004E52();
    return;
}

void game::SUB_004E52() {
    a = 0xAA;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_004E5B() {
    if (a >= 0x30) {
        goto L_004E69;
    }
    flgC = true;
    opSBC(0x20);
    x = a;
    a = myMapper->readCPU(0xCE7D + x);
    x = 0x00;
    popAddress();
    return;
L_004E69:
    if (a < 0x3A) {
        goto L_004E79;
    }
    if (a < 0x41) {
        goto L_004E7C;
    }
    if (a >= 0x5B) {
        goto L_004E7C;
    }
    flgC = false;
    opADC(0xA3);
    popAddress();
    return;
L_004E79:
    flgC = false;
    opADC(0xAA);
L_004E7C:
    popAddress();
}

void game::SUB_0051A5() {
    myMapper->writeCPU(0x04A8, a);
    a = myMapper->readCPU(0x0400);
    if (a != 0x01) {
        goto L_0051B7;
    }
    a = myMapper->readCPU(0x04A8);
    opORA(0x80);
    myMapper->writeCPU(0x04A8, a);
L_0051B7:
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    pushAddress(0x0051BC);
    SUB_0051C5();
    if (poppedEntry.value != 0x0051BC) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popAddress();
}

void game::SUB_0051C5() {
    a = myMapper->readCPU(0x04A8);
    opASL_A(1);
    if (flgZ) {
        SUB_0051E0();
        return;
    }
    x = a;
    myMapper->writeCPU(0x00E9, myMapper->readCPU(0xD99A + x));
    myMapper->writeCPU(0x00EA, myMapper->readCPU(0xD99B + x));
    if (flgC) {
        goto L_0051DC;
    }
    pushAddress(0x0051D8);
    SUB_005266();
    if (poppedEntry.value != 0x0051D8) return;
    popAddress();
    return;
L_0051DC:
    pushAddress(0x0051DC);
    SUB_005308();
    if (poppedEntry.value != 0x0051DC) return;
    popAddress();
}

void game::SUB_0051E0() {
    a = 0x00;
    x = 0x27;
    do {
        myMapper->writeCPU((0x00C8 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x00EB, 0xAC);
    myMapper->writeCPU(0x00EC, 0x00);
    myMapper->writeCPU(0x00E9, 0x00);
    myMapper->writeCPU(0x00EA, 0x04);
    x = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU((0x00E9 + x) & 0x00ff) + (myMapper->readCPU((0x00E9 + x + 1) & 0x00ff) << 8), 0x00);
        opINC(0x00E9, 1);
        if (flgZ) {
            opINC(0x00EA, 1);
        }
        if (myMapper->readCPU(0x00EB) != 0) {
            goto L_00520B;
        }
        opDEC(0x00EC, 1);
    L_00520B:
        opDEC(0x00EB, 1);
        a = myMapper->readCPU(0x00EB);
        opORA(myMapper->readCPU(0x00EC));
    } while (!flgZ);
    myMapper->writeCPU(0x00E9, a);
    myMapper->writeCPU(0x00EA, a);
    a = 0xFF;
    myMapper->writeCPU(0x04A4, a);
    myMapper->writeCPU(0x04A5, a);
    myMapper->writeCPU(0x04A6, a);
    myMapper->writeCPU(0x04A7, a);
    pushAddress(0x005225);
    SUB_005229();
    if (poppedEntry.value != 0x005225) return;
    popAddress();
}

void game::SUB_005229() {
    a = 0x30;
    myMapper->writeCPU(0x4000, a);
    myMapper->writeCPU(0x4004, a);
    myMapper->writeCPU(0x400C, a);
    myMapper->writeCPU(0x400F, a);
    a = 0x08;
    myMapper->writeCPU(0x4001, a);
    myMapper->writeCPU(0x4005, a);
    myMapper->writeCPU(0x4008, 0x80);
    a = 0x00;
    myMapper->writeCPU(0x4002, a);
    myMapper->writeCPU(0x4003, a);
    myMapper->writeCPU(0x4006, a);
    myMapper->writeCPU(0x4007, a);
    myMapper->writeCPU(0x400A, a);
    myMapper->writeCPU(0x400B, a);
    myMapper->writeCPU(0x400E, a);
    myMapper->writeCPU(0x4015, 0x0F);
    a = 0xC0;
    myMapper->writeCPU(0x4017, a);
    popAddress();
}

void game::SUB_005266() {
    y = 0x00;
    myMapper->writeCPU(0x00EB, myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00EC, a);
    opINY(1);
    opORA(myMapper->readCPU(0x00EB));
    if (!flgZ) {
        x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0400 + x, 0x01);
        a = x;
        opASL_A(1);
        x = a;
        a = myMapper->readCPU(0x00EB);
        myMapper->writeCPU((0x00C9 + x) & 0x00ff, a);
        myMapper->writeCPU(0x0484 + x, a);
        a = myMapper->readCPU(0x00EC);
        myMapper->writeCPU((0x00CA + x) & 0x00ff, a);
        myMapper->writeCPU(0x0485 + x, a);
    }
    opINY(1);
    myMapper->writeCPU(0x00EB, myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00EC, a);
    opINY(1);
    opORA(myMapper->readCPU(0x00EB));
    if (!flgZ) {
        x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0404 + x, 0x01);
        a = x;
        opASL_A(1);
        x = a;
        a = myMapper->readCPU(0x00EB);
        myMapper->writeCPU((0x00D1 + x) & 0x00ff, a);
        myMapper->writeCPU(0x048C + x, a);
        a = myMapper->readCPU(0x00EC);
        myMapper->writeCPU((0x00D2 + x) & 0x00ff, a);
        myMapper->writeCPU(0x048D + x, a);
    }
    opINY(1);
    myMapper->writeCPU(0x00EB, myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00EC, a);
    opINY(1);
    opORA(myMapper->readCPU(0x00EB));
    if (!flgZ) {
        x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0409 + x, 0x01);
        a = x;
        opASL_A(1);
        x = a;
        a = myMapper->readCPU(0x00EB);
        myMapper->writeCPU((0x00DB + x) & 0x00ff, a);
        myMapper->writeCPU(0x0496 + x, a);
        a = myMapper->readCPU(0x00EC);
        myMapper->writeCPU((0x00DC + x) & 0x00ff, a);
        myMapper->writeCPU(0x0497 + x, a);
    }
    opINY(1);
    myMapper->writeCPU(0x00EB, myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00EC, a);
    opINY(1);
    opORA(myMapper->readCPU(0x00EB));
    if (flgZ) {
        goto L_005307;
    }
    x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x040E + x, 0x01);
    a = x;
    opASL_A(1);
    x = a;
    a = myMapper->readCPU(0x00EB);
    myMapper->writeCPU((0x00E5 + x) & 0x00ff, a);
    myMapper->writeCPU(0x04A0 + x, a);
    a = myMapper->readCPU(0x00EC);
    myMapper->writeCPU((0x00E6 + x) & 0x00ff, a);
    myMapper->writeCPU(0x04A1 + x, a);
L_005307:
    popAddress();
}

void game::SUB_005308() {
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    opORA(myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    pushStatus();
    opINY(1);
    popStatus();
    if (!flgZ) {
        x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0400 + x, 0x00);
    }
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    opORA(myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    pushStatus();
    opINY(1);
    popStatus();
    if (!flgZ) {
        x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0404 + x, 0x00);
    }
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    opORA(myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    pushStatus();
    opINY(1);
    popStatus();
    if (!flgZ) {
        x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0409 + x, 0x00);
    }
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    opORA(myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y));
    pushStatus();
    opINY(1);
    popStatus();
    if (flgZ) {
        goto L_005355;
    }
    x = myMapper->readCPU(myMapper->readCPU(0x00E9) + (myMapper->readCPU((0x00E9 + 1) & 0x00ff) << 8) + y);
    a = 0x00;
    myMapper->writeCPU(0x040E + x, a);
L_005355:
    popAddress();
}

void game::SUB_005356() {
    pushAddress(0x005356);
    SUB_005372();
    if (poppedEntry.value != 0x005356) return;
    pushAddress(0x005359);
    SUB_00545C();
    if (poppedEntry.value != 0x005359) return;
    pushAddress(0x00535C);
    SUB_00547D();
    if (poppedEntry.value != 0x00535C) return;
    pushAddress(0x00535F);
    SUB_005567();
    if (poppedEntry.value != 0x00535F) return;
    pushAddress(0x005362);
    SUB_005588();
    if (poppedEntry.value != 0x005362) return;
    pushAddress(0x005365);
    SUB_005672();
    if (poppedEntry.value != 0x005365) return;
    pushAddress(0x005368);
    SUB_005693();
    if (poppedEntry.value != 0x005368) return;
    pushAddress(0x00536B);
    SUB_005777();
    if (poppedEntry.value != 0x00536B) return;
    pushAddress(0x00536E);
    SUB_0057FA();
    if (poppedEntry.value != 0x00536E) return;
    popAddress();
}

void game::SUB_005372() {
    x = 0x00;
    while (true) {
        while (true) {
            do {
                if (myMapper->readCPU(0x0400 + x) != 0) {
                    goto L_00537F;
                }
            L_005379:
                opINX(1);
            } while (x != 0x04);
            popAddress();
            return;
        L_00537F:
            if (myMapper->readCPU(0x0410 + x) == 0) {
                a = x;
                opPHA();
                opASL_A(1);
                x = a;
                a = myMapper->readCPU(myMapper->readCPU((0x00C9 + x) & 0x00ff) + (myMapper->readCPU((0x00C9 + x + 1) & 0x00ff) << 8));
                setLoadFlag(a);
                if (flgN) {
                    goto L_0053FE;
                }
                opASL_A(1);
                y = a;
                myMapper->writeCPU(0x0444 + x, myMapper->readCPU(0xD8F0 + y));
                myMapper->writeCPU(0x0445 + x, myMapper->readCPU(0xD8F1 + y));
                myMapper->writeCPU(0x0440, 0x01);
                opINC((0x00C9 + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00CA + x) & 0x00ff, 1);
                }
                y = myMapper->readCPU(myMapper->readCPU((0x00C9 + x) & 0x00ff) + (myMapper->readCPU((0x00C9 + x + 1) & 0x00ff) << 8));
                opDEY(1);
                opINC((0x00C9 + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00CA + x) & 0x00ff, 1);
                }
                a = x;
                opLSR_A(1);
                x = a;
                a = y;
                myMapper->writeCPU(0x0410 + x, a);
                myMapper->writeCPU(0x04A9, a);
                a = myMapper->readCPU(0x0474 + x);
                opAND(0x40);
                if (!flgZ) {
                    a = myMapper->readCPU(0x0474 + x);
                    opAND(0x0F);
                    myMapper->writeCPU(0x04AA, a);
                    myMapper->writeCPU(0x0464 + x, a);
                    pushAddress(0x0053CB);
                    SUB_0058C2();
                    if (poppedEntry.value != 0x0053CB) return;
                    a = myMapper->readCPU(0x04A9);
                    myMapper->writeCPU(0x0420 + x, a);
                    myMapper->writeCPU(0x0430 + x, a);
                }
                opPLA();
                x = a;
                goto L_005379;
            }
            opDEC(0x0410 + x, 1);
            a = myMapper->readCPU(0x0474 + x);
            opAND(0xC0);
            if (flgZ) {
                if (flgZ) {
                    goto L_005379;
                }
            }
            opDEC(0x0420 + x, 1);
            if (flgZ) {
                myMapper->writeCPU(0x0420 + x, myMapper->readCPU(0x0430 + x));
                if (myMapper->readCPU(0x0464 + x) != 0) {
                    opDEC(0x0464 + x, 1);
                }
            }
            goto L_005379;
        L_0053FE:
            if (a == 0xFF) {
                goto L_005440;
            }
            if (a == 0xFE) {
                goto L_00544D;
            }
            opINC((0x00C9 + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00CA + x) & 0x00ff, 1);
            }
            y = myMapper->readCPU(myMapper->readCPU((0x00C9 + x) & 0x00ff) + (myMapper->readCPU((0x00C9 + x + 1) & 0x00ff) << 8));
            opINC((0x00C9 + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00CA + x) & 0x00ff, 1);
            }
            myMapper->writeCPU(0x04A9, myMapper->readCPU(myMapper->readCPU((0x00C9 + x) & 0x00ff) + (myMapper->readCPU((0x00C9 + x + 1) & 0x00ff) << 8)));
            opINC((0x00C9 + x) & 0x00ff, 1);
            if (!flgZ) {
                goto L_005420;
            }
            opINC((0x00CA + x) & 0x00ff, 1);
        L_005420:
            a = x;
            opLSR_A(1);
            x = a;
            a = y;
            myMapper->writeCPU(0x0474 + x, a);
            opAND(0x0F);
            myMapper->writeCPU(0x0464 + x, a);
            myMapper->writeCPU(0x04AA, a);
            pushAddress(0x00542F);
            SUB_0058C2();
            if (poppedEntry.value != 0x00542F) return;
            a = myMapper->readCPU(0x04A9);
            myMapper->writeCPU(0x0420 + x, a);
            myMapper->writeCPU(0x0430 + x, a);
            opPLA();
            x = a;
        }
    L_005440:
        a = x;
        opLSR_A(1);
        x = a;
        a = 0x00;
        myMapper->writeCPU(0x0400 + x, a);
        opPLA();
        x = a;
        goto L_005379;
    L_00544D:
        myMapper->writeCPU((0x00C9 + x) & 0x00ff, myMapper->readCPU(0x0484 + x));
        a = myMapper->readCPU(0x0485 + x);
        myMapper->writeCPU((0x00CA + x) & 0x00ff, a);
        opPLA();
        x = a;
    }
    SUB_00545C();
    return;
}

void game::SUB_00545C() {
    x = 0x00;
    do {
        if (myMapper->readCPU(0x0400 + x) != 0) {
            goto L_00546E;
        }
        opINX(1);
    } while (x != 0x04);
    myMapper->writeCPU(0x04A4, 0xFF);
    do {
    L_00546D:
        popAddress();
        return;
    L_00546E:
        if (x == myMapper->readCPU(0x04A4)) {
            goto L_00546D;
        }
        myMapper->writeCPU(0x04A4, x);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0440, a);
    } while (!flgZ);
    SUB_00547D();
    return;
}

void game::SUB_00547D() {
    x = 0x00;
    while (true) {
        while (true) {
            do {
                if (myMapper->readCPU(0x0404 + x) != 0) {
                    goto L_00548A;
                }
            L_005484:
                opINX(1);
            } while (x != 0x05);
            popAddress();
            return;
        L_00548A:
            if (myMapper->readCPU(0x0414 + x) == 0) {
                a = x;
                opPHA();
                opASL_A(1);
                x = a;
                a = myMapper->readCPU(myMapper->readCPU((0x00D1 + x) & 0x00ff) + (myMapper->readCPU((0x00D1 + x + 1) & 0x00ff) << 8));
                setLoadFlag(a);
                if (flgN) {
                    goto L_005509;
                }
                opASL_A(1);
                y = a;
                myMapper->writeCPU(0x044C + x, myMapper->readCPU(0xD8F0 + y));
                myMapper->writeCPU(0x044D + x, myMapper->readCPU(0xD8F1 + y));
                myMapper->writeCPU(0x0441, 0x01);
                opINC((0x00D1 + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00D2 + x) & 0x00ff, 1);
                }
                y = myMapper->readCPU(myMapper->readCPU((0x00D1 + x) & 0x00ff) + (myMapper->readCPU((0x00D1 + x + 1) & 0x00ff) << 8));
                opDEY(1);
                opINC((0x00D1 + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00D2 + x) & 0x00ff, 1);
                }
                a = x;
                opLSR_A(1);
                x = a;
                a = y;
                myMapper->writeCPU(0x0414 + x, a);
                myMapper->writeCPU(0x04A9, a);
                a = myMapper->readCPU(0x0478 + x);
                opAND(0x40);
                if (!flgZ) {
                    a = myMapper->readCPU(0x0478 + x);
                    opAND(0x0F);
                    myMapper->writeCPU(0x04AA, a);
                    myMapper->writeCPU(0x0468 + x, a);
                    pushAddress(0x0054D6);
                    SUB_0058C2();
                    if (poppedEntry.value != 0x0054D6) return;
                    a = myMapper->readCPU(0x04A9);
                    myMapper->writeCPU(0x0424 + x, a);
                    myMapper->writeCPU(0x0434 + x, a);
                }
                opPLA();
                x = a;
                goto L_005484;
            }
            opDEC(0x0414 + x, 1);
            a = myMapper->readCPU(0x0478 + x);
            opAND(0xC0);
            if (flgZ) {
                if (flgZ) {
                    goto L_005484;
                }
            }
            opDEC(0x0424 + x, 1);
            if (flgZ) {
                myMapper->writeCPU(0x0424 + x, myMapper->readCPU(0x0434 + x));
                if (myMapper->readCPU(0x0468 + x) != 0) {
                    opDEC(0x0468 + x, 1);
                }
            }
            goto L_005484;
        L_005509:
            if (a == 0xFF) {
                goto L_00554B;
            }
            if (a == 0xFE) {
                goto L_005558;
            }
            opINC((0x00D1 + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00D2 + x) & 0x00ff, 1);
            }
            y = myMapper->readCPU(myMapper->readCPU((0x00D1 + x) & 0x00ff) + (myMapper->readCPU((0x00D1 + x + 1) & 0x00ff) << 8));
            opINC((0x00D1 + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00D2 + x) & 0x00ff, 1);
            }
            myMapper->writeCPU(0x04A9, myMapper->readCPU(myMapper->readCPU((0x00D1 + x) & 0x00ff) + (myMapper->readCPU((0x00D1 + x + 1) & 0x00ff) << 8)));
            opINC((0x00D1 + x) & 0x00ff, 1);
            if (!flgZ) {
                goto L_00552B;
            }
            opINC((0x00D2 + x) & 0x00ff, 1);
        L_00552B:
            a = x;
            opLSR_A(1);
            x = a;
            a = y;
            myMapper->writeCPU(0x0478 + x, a);
            opAND(0x0F);
            myMapper->writeCPU(0x0468 + x, a);
            myMapper->writeCPU(0x04AA, a);
            pushAddress(0x00553A);
            SUB_0058C2();
            if (poppedEntry.value != 0x00553A) return;
            a = myMapper->readCPU(0x04A9);
            myMapper->writeCPU(0x0424 + x, a);
            myMapper->writeCPU(0x0434 + x, a);
            opPLA();
            x = a;
        }
    L_00554B:
        a = x;
        opLSR_A(1);
        x = a;
        a = 0x00;
        myMapper->writeCPU(0x0404 + x, a);
        opPLA();
        x = a;
        goto L_005484;
    L_005558:
        myMapper->writeCPU((0x00D1 + x) & 0x00ff, myMapper->readCPU(0x048C + x));
        a = myMapper->readCPU(0x048D + x);
        myMapper->writeCPU((0x00D2 + x) & 0x00ff, a);
        opPLA();
        x = a;
    }
    SUB_005567();
    return;
}

void game::SUB_005567() {
    x = 0x00;
    do {
        if (myMapper->readCPU(0x0404 + x) != 0) {
            goto L_005579;
        }
        opINX(1);
    } while (x != 0x05);
    myMapper->writeCPU(0x04A5, 0xFF);
    do {
    L_005578:
        popAddress();
        return;
    L_005579:
        if (x == myMapper->readCPU(0x04A5)) {
            goto L_005578;
        }
        myMapper->writeCPU(0x04A5, x);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0441, a);
    } while (!flgZ);
    SUB_005588();
    return;
}

void game::SUB_005588() {
    x = 0x00;
    while (true) {
        while (true) {
            do {
                if (myMapper->readCPU(0x0409 + x) != 0) {
                    goto L_005595;
                }
            L_00558F:
                opINX(1);
            } while (x != 0x05);
            popAddress();
            return;
        L_005595:
            if (myMapper->readCPU(0x0419 + x) == 0) {
                a = x;
                opPHA();
                opASL_A(1);
                x = a;
                a = myMapper->readCPU(myMapper->readCPU((0x00DB + x) & 0x00ff) + (myMapper->readCPU((0x00DB + x + 1) & 0x00ff) << 8));
                setLoadFlag(a);
                if (flgN) {
                    goto L_005614;
                }
                opASL_A(1);
                y = a;
                myMapper->writeCPU(0x0456 + x, myMapper->readCPU(0xD8F0 + y));
                myMapper->writeCPU(0x0457 + x, myMapper->readCPU(0xD8F1 + y));
                myMapper->writeCPU(0x0442, 0x01);
                opINC((0x00DB + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00DC + x) & 0x00ff, 1);
                }
                y = myMapper->readCPU(myMapper->readCPU((0x00DB + x) & 0x00ff) + (myMapper->readCPU((0x00DB + x + 1) & 0x00ff) << 8));
                opDEY(1);
                opINC((0x00DB + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00DC + x) & 0x00ff, 1);
                }
                a = x;
                opLSR_A(1);
                x = a;
                a = y;
                myMapper->writeCPU(0x0419 + x, a);
                myMapper->writeCPU(0x04A9, a);
                a = myMapper->readCPU(0x047D + x);
                opAND(0x40);
                if (!flgZ) {
                    a = myMapper->readCPU(0x047D + x);
                    opAND(0x0F);
                    myMapper->writeCPU(0x04AA, a);
                    myMapper->writeCPU(0x046D + x, a);
                    pushAddress(0x0055E1);
                    SUB_0058C2();
                    if (poppedEntry.value != 0x0055E1) return;
                    a = myMapper->readCPU(0x04A9);
                    myMapper->writeCPU(0x0429 + x, a);
                    myMapper->writeCPU(0x0439 + x, a);
                }
                opPLA();
                x = a;
                goto L_00558F;
            }
            opDEC(0x0419 + x, 1);
            a = myMapper->readCPU(0x047D + x);
            opAND(0xC0);
            if (flgZ) {
                if (flgZ) {
                    goto L_00558F;
                }
            }
            opDEC(0x0429 + x, 1);
            if (flgZ) {
                myMapper->writeCPU(0x0429 + x, myMapper->readCPU(0x0439 + x));
                if (myMapper->readCPU(0x046D + x) != 0) {
                    opDEC(0x046D + x, 1);
                }
            }
            goto L_00558F;
        L_005614:
            if (a == 0xFF) {
                goto L_005656;
            }
            if (a == 0xFE) {
                goto L_005663;
            }
            opINC((0x00DB + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00DC + x) & 0x00ff, 1);
            }
            y = myMapper->readCPU(myMapper->readCPU((0x00DB + x) & 0x00ff) + (myMapper->readCPU((0x00DB + x + 1) & 0x00ff) << 8));
            opINC((0x00DB + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00DC + x) & 0x00ff, 1);
            }
            myMapper->writeCPU(0x04A9, myMapper->readCPU(myMapper->readCPU((0x00DB + x) & 0x00ff) + (myMapper->readCPU((0x00DB + x + 1) & 0x00ff) << 8)));
            opINC((0x00DB + x) & 0x00ff, 1);
            if (!flgZ) {
                goto L_005636;
            }
            opINC((0x00DC + x) & 0x00ff, 1);
        L_005636:
            a = x;
            opLSR_A(1);
            x = a;
            a = y;
            myMapper->writeCPU(0x047D + x, a);
            opAND(0x0F);
            myMapper->writeCPU(0x046D + x, a);
            myMapper->writeCPU(0x04AA, a);
            pushAddress(0x005645);
            SUB_0058C2();
            if (poppedEntry.value != 0x005645) return;
            a = myMapper->readCPU(0x04A9);
            myMapper->writeCPU(0x0429 + x, a);
            myMapper->writeCPU(0x0439 + x, a);
            opPLA();
            x = a;
        }
    L_005656:
        a = x;
        opLSR_A(1);
        x = a;
        a = 0x00;
        myMapper->writeCPU(0x0409 + x, a);
        opPLA();
        x = a;
        goto L_00558F;
    L_005663:
        myMapper->writeCPU((0x00DB + x) & 0x00ff, myMapper->readCPU(0x0496 + x));
        a = myMapper->readCPU(0x0497 + x);
        myMapper->writeCPU((0x00DC + x) & 0x00ff, a);
        opPLA();
        x = a;
    }
    SUB_005672();
    return;
}

void game::SUB_005672() {
    x = 0x00;
    do {
        if (myMapper->readCPU(0x0409 + x) != 0) {
            goto L_005684;
        }
        opINX(1);
    } while (x != 0x05);
    myMapper->writeCPU(0x04A6, 0xFF);
    do {
    L_005683:
        popAddress();
        return;
    L_005684:
        if (x == myMapper->readCPU(0x04A6)) {
            goto L_005683;
        }
        myMapper->writeCPU(0x04A6, x);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0442, a);
    } while (!flgZ);
    SUB_005693();
    return;
}

void game::SUB_005693() {
    x = 0x00;
    while (true) {
        while (true) {
            do {
                if (myMapper->readCPU(0x040E + x) != 0) {
                    goto L_0056A0;
                }
            L_00569A:
                opINX(1);
            } while (x != 0x02);
            popAddress();
            return;
        L_0056A0:
            if (myMapper->readCPU(0x041E + x) == 0) {
                a = x;
                opPHA();
                opASL_A(1);
                x = a;
                a = myMapper->readCPU(myMapper->readCPU((0x00E5 + x) & 0x00ff) + (myMapper->readCPU((0x00E5 + x + 1) & 0x00ff) << 8));
                setLoadFlag(a);
                if (flgN) {
                    goto L_005719;
                }
                myMapper->writeCPU(0x0460 + x, a);
                myMapper->writeCPU(0x0461 + x, 0x30);
                myMapper->writeCPU(0x0443, 0x01);
                opINC((0x00E5 + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00E6 + x) & 0x00ff, 1);
                }
                y = myMapper->readCPU(myMapper->readCPU((0x00E5 + x) & 0x00ff) + (myMapper->readCPU((0x00E5 + x + 1) & 0x00ff) << 8));
                opDEY(1);
                opINC((0x00E5 + x) & 0x00ff, 1);
                if (flgZ) {
                    opINC((0x00E6 + x) & 0x00ff, 1);
                }
                a = x;
                opLSR_A(1);
                x = a;
                a = y;
                myMapper->writeCPU(0x041E + x, a);
                myMapper->writeCPU(0x04A9, a);
                a = myMapper->readCPU(0x0482 + x);
                opAND(0x40);
                if (!flgZ) {
                    a = myMapper->readCPU(0x0482 + x);
                    opAND(0x0F);
                    myMapper->writeCPU(0x04AA, a);
                    myMapper->writeCPU(0x0472 + x, a);
                    pushAddress(0x0056E6);
                    SUB_0058C2();
                    if (poppedEntry.value != 0x0056E6) return;
                    a = myMapper->readCPU(0x04A9);
                    myMapper->writeCPU(0x042E + x, a);
                    myMapper->writeCPU(0x043E + x, a);
                }
                opPLA();
                x = a;
                goto L_00569A;
            }
            opDEC(0x041E + x, 1);
            a = myMapper->readCPU(0x0482 + x);
            opAND(0xC0);
            if (flgZ) {
                if (flgZ) {
                    goto L_00569A;
                }
            }
            opDEC(0x042E + x, 1);
            if (flgZ) {
                myMapper->writeCPU(0x042E + x, myMapper->readCPU(0x043E + x));
                if (myMapper->readCPU(0x0472 + x) != 0) {
                    opDEC(0x0472 + x, 1);
                }
            }
            goto L_00569A;
        L_005719:
            if (a == 0xFF) {
                goto L_00575B;
            }
            if (a == 0xFE) {
                goto L_005768;
            }
            opINC((0x00E5 + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00E6 + x) & 0x00ff, 1);
            }
            y = myMapper->readCPU(myMapper->readCPU((0x00E5 + x) & 0x00ff) + (myMapper->readCPU((0x00E5 + x + 1) & 0x00ff) << 8));
            opINC((0x00E5 + x) & 0x00ff, 1);
            if (flgZ) {
                opINC((0x00E6 + x) & 0x00ff, 1);
            }
            myMapper->writeCPU(0x04A9, myMapper->readCPU(myMapper->readCPU((0x00E5 + x) & 0x00ff) + (myMapper->readCPU((0x00E5 + x + 1) & 0x00ff) << 8)));
            opINC((0x00E5 + x) & 0x00ff, 1);
            if (!flgZ) {
                goto L_00573B;
            }
            opINC((0x00E6 + x) & 0x00ff, 1);
        L_00573B:
            a = x;
            opLSR_A(1);
            x = a;
            a = y;
            myMapper->writeCPU(0x0482 + x, a);
            opAND(0x0F);
            myMapper->writeCPU(0x0472 + x, a);
            myMapper->writeCPU(0x04AA, a);
            pushAddress(0x00574A);
            SUB_0058C2();
            if (poppedEntry.value != 0x00574A) return;
            a = myMapper->readCPU(0x04A9);
            myMapper->writeCPU(0x042E + x, a);
            myMapper->writeCPU(0x043E + x, a);
            opPLA();
            x = a;
        }
    L_00575B:
        a = x;
        opLSR_A(1);
        x = a;
        a = 0x00;
        myMapper->writeCPU(0x040E + x, a);
        opPLA();
        x = a;
        goto L_00569A;
    L_005768:
        myMapper->writeCPU((0x00E5 + x) & 0x00ff, myMapper->readCPU(0x04A0 + x));
        a = myMapper->readCPU(0x04A1 + x);
        myMapper->writeCPU((0x00E6 + x) & 0x00ff, a);
        opPLA();
        x = a;
    }
    SUB_005777();
    return;
}

void game::SUB_005777() {
    x = 0x00;
    do {
        if (myMapper->readCPU(0x040E + x) != 0) {
            goto L_005789;
        }
        opINX(1);
        opCMP(x, 0x02);
    } while (!flgZ);
    myMapper->writeCPU(0x04A7, 0xFF);
    do {
        do {
            popAddress();
            return;
        L_005789:
            opCMP(x, myMapper->readCPU(0x04A7));
        } while (flgZ);
        myMapper->writeCPU(0x04A7, x);
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x0443, a);
    } while (!flgZ);
    SUB_005798();
    return;
}

void game::SUB_005798() {
    a = 0xFF;
    myMapper->writeCPU(0x04A4, a);
    myMapper->writeCPU(0x04A5, a);
    myMapper->writeCPU(0x04A6, a);
    myMapper->writeCPU(0x04A7, a);
    pushAddress(0x0057A6);
    SUB_005229();
    if (poppedEntry.value != 0x0057A6) return;
    a = 0x14;
    myMapper->writeCPU(0x00C2, a);
    myMapper->writeCPU(0x00C3, a);
    popAddress();
}

void game::SUB_0057B0() {
    a = myMapper->readCPU(0x00C2);
    setLoadFlag(a);
    if (!flgZ) {
        if (a != 0x14) {
            goto L_0057CC;
        }
        myMapper->writeCPU(0x4000, 0x08);
        myMapper->writeCPU(0x4001, 0x00);
        myMapper->writeCPU(0x4002, 0x40);
        myMapper->writeCPU(0x4003, 0x08);
    L_0057CC:
        opDEC(0x00C2, 1);
        if (!flgZ) {
            goto L_0057F8;
        }
    }
    if (myMapper->readCPU(0x00C3) == 0x14) {
        myMapper->writeCPU(0x4002, 0x50);
        myMapper->writeCPU(0x4003, 0x08);
    }
    opDEC(0x00C3, 1);
    if (!flgZ) {
        goto L_0057F8;
    }
    a = 0x00;
    myMapper->writeCPU(0x4002, a);
    myMapper->writeCPU(0x4003, a);
    myMapper->writeCPU(0x4006, a);
    myMapper->writeCPU(0x4007, a);
    myMapper->writeCPU(0x400A, a);
    myMapper->writeCPU(0x400B, a);
L_0057F8:
    popAddress();
}

void game::SUB_0057FA() {
    x = myMapper->readCPU(0x04A4);
    setLoadFlag(x);
    if (!flgN) {
        a = myMapper->readCPU(0x0474 + x);
        opASL_A(2);
        opAND(0xC0);
        opORA(0x30);
        opORA(myMapper->readCPU(0x0464 + x));
        myMapper->writeCPU(0x4000, a);
        if (myMapper->readCPU(0x0440) == 0) {
            goto L_00582C;
        }
        a = x;
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x4002, myMapper->readCPU(0x0444 + x));
        a = myMapper->readCPU(0x0445 + x);
        myMapper->writeCPU(0x4003, a);
        opORA(myMapper->readCPU(0x0444 + x));
        if (!flgZ) {
            goto L_00582C;
        }
    }
    myMapper->writeCPU(0x4000, 0x30);
L_00582C:
    x = myMapper->readCPU(0x04A5);
    setLoadFlag(x);
    if (!flgN) {
        a = myMapper->readCPU(0x0478 + x);
        opASL_A(2);
        opAND(0xC0);
        opORA(0x30);
        opORA(myMapper->readCPU(0x0468 + x));
        myMapper->writeCPU(0x4004, a);
        if (myMapper->readCPU(0x0441) == 0) {
            goto L_00585E;
        }
        a = x;
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x4006, myMapper->readCPU(0x044C + x));
        a = myMapper->readCPU(0x044D + x);
        myMapper->writeCPU(0x4007, a);
        opORA(myMapper->readCPU(0x044C + x));
        if (!flgZ) {
            goto L_00585E;
        }
    }
    myMapper->writeCPU(0x4004, 0x30);
L_00585E:
    x = myMapper->readCPU(0x04A6);
    setLoadFlag(x);
    if (!flgN) {
        myMapper->writeCPU(0x4008, 0xFF);
        if (myMapper->readCPU(0x0442) == 0) {
            goto L_005886;
        }
        a = x;
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x400A, myMapper->readCPU(0x0456 + x));
        a = myMapper->readCPU(0x0457 + x);
        myMapper->writeCPU(0x400B, a);
        opORA(myMapper->readCPU(0x0456 + x));
        if (!flgZ) {
            goto L_005886;
        }
    }
    myMapper->writeCPU(0x4008, 0x00);
L_005886:
    x = myMapper->readCPU(0x04A7);
    setLoadFlag(x);
    if (!flgN) {
        a = 0x10;
        opORA(myMapper->readCPU(0x0472 + x));
        myMapper->writeCPU(0x400C, a);
        if (myMapper->readCPU(0x0443) == 0) {
            goto L_0058B3;
        }
        a = x;
        opASL_A(1);
        x = a;
        a = myMapper->readCPU(0x0460 + x);
        opCMP(a, 0x54);
        if (flgZ) {
            goto L_0058AE;
        }
        myMapper->writeCPU(0x400E, a);
        myMapper->writeCPU(0x400F, myMapper->readCPU(0x0461 + x));
        goto L_0058B3;
    }
L_0058AE:
    myMapper->writeCPU(0x400C, 0x30);
L_0058B3:
    a = 0x00;
    myMapper->writeCPU(0x0440, a);
    myMapper->writeCPU(0x0441, a);
    myMapper->writeCPU(0x0442, a);
    myMapper->writeCPU(0x0443, a);
    popAddress();
}

void game::SUB_0058C2() {
    a = x;
    opPHA();
    myMapper->writeCPU(0x04AB, 0x00);
    x = 0x08;
    opASL_M(0x04A9, 1);
    do {
        opROL_M(0x04AB, 1);
        a = myMapper->readCPU(0x04AB);
        opCMP(a, myMapper->readCPU(0x04AA));
        if (!flgC) {
            goto L_0058DF;
        }
        opSBC(myMapper->readCPU(0x04AA));
        myMapper->writeCPU(0x04AB, a);
    L_0058DF:
        opROL_M(0x04A9, 1);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x04A9);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0058ED;
    }
    opINC(0x04A9, 1);
L_0058ED:
    opPLA();
    x = a;
    popAddress();
}

