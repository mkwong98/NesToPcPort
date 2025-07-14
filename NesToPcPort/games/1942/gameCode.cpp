#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"

void game::repeat() {
}

void game::SUB_00001B() {
    a = myMapper->readCPU(0x008C);
    opAND(0x7F);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, 0x00);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0089));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0088));
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
        opDEC(0x0087, 1);
    } while (!flgZ);
    a = myMapper->readCPU(0x008C);
    opORA(0x80);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_001FDB() {
    myMapper->writeCPU(0x0075, 0x4C);
    myMapper->writeCPU(0x0076, 0x07);
    myMapper->writeCPU(0x0077, 0x52);
    myMapper->writeCPU(0x0078, 0x07);
    myMapper->writeCPU(0x0079, myMapper->readCPU(0xA411));
    myMapper->writeCPU(0x007A, myMapper->readCPU(0xA412));
    myMapper->writeCPU(0x007B, 0x00);
    myMapper->writeCPU(0x007C, 0x40);
    y = 0x00;
    a = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0075) + (myMapper->readCPU((0x0075 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
    } while (y != 0x06);
    y = 0x00;
    myMapper->writeCPU(0x0087, 0x06);
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, 0x00);
        a = y;
        flgC = false;
        opADC(0x08);
        y = a;
        opDEC(0x0087, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0088, 0x00);
    myMapper->writeCPU(0x0089, 0x40);
    myMapper->writeCPU(0x0087, 0x03);
    y = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, 0x70);
        opINY(4);
        opDEC(0x0087, 1);
    } while (!flgZ);
    pushAddress(0x002035);
    SUB_002050();
    if (poppedEntry.value != 0x002035) return;
    y = 0x05;
    a = 0xFF;
    do {
        myMapper->writeCPU(0x0746 + y, a);
        opDEY(1);
    } while (!flgN);
    y = 0x0B;
    a = 0x00;
    do {
        myMapper->writeCPU(0x0735 + y, a);
        opDEY(1);
    } while (!flgN);
    pushAddress(0x00204C);
    SUB_0020D0();
    if (poppedEntry.value != 0x00204C) return;
    popAddress();
}

void game::SUB_002050() {
    y = 0x04;
    a = 0x00;
    do {
        myMapper->writeCPU(0x0741 + y, a);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0020D0() {
    myMapper->writeCPU(0x008A, 0x0C);
    myMapper->writeCPU(0x008B, 0x40);
    y = 0x00;
    a = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, 0xFF);
    popAddress();
}

void game::SUB_0020EA() {
    myMapper->writeCPU(0x007D, myMapper->readCPU(0x0741));
    myMapper->writeCPU(0x007E, myMapper->readCPU(0x0742));
    myMapper->writeCPU(0x007F, myMapper->readCPU(0x0743));
    myMapper->writeCPU(0x0080, myMapper->readCPU(0x0744));
    myMapper->writeCPU(0x0081, myMapper->readCPU(0x0745));
    myMapper->writeCPU(0x0072, 0x28);
    do {
        opLSR_M(0x0081, 1);
        opROR_M(0x0080, 1);
        opROR_M(0x007F, 1);
        opROR_M(0x007E, 1);
        opROR_M(0x007D, 1);
        if (flgC) {
            goto L_00211D;
        }
    L_002113:
        opDEC(0x0072, 1);
    } while (!flgZ);
    pushAddress(0x002117);
    SUB_002050();
    if (poppedEntry.value != 0x002117) return;
    goto L_00218C;
L_00211D:
    a = 0x28;
    flgC = true;
    opSBC(myMapper->readCPU(0x0072));
    myMapper->writeCPU(0x0074, a);
    y = 0x05;
    do {
        if (a == myMapper->readCPU(0x0746 + y)) {
            goto L_002113;
        }
        opDEY(1);
    } while (!flgN);
    y = 0x00;
    a = 0xFF;
    do {
        if (a == myMapper->readCPU(0x0746 + y)) {
            goto L_002154;
        }
        opINY(1);
    } while (y != 0x06);
    y = 0x00;
    a = myMapper->readCPU(0x0074);
    do {
        if (a < myMapper->readCPU(0x0746 + y)) {
            goto L_00214D;
        }
    L_002145:
        opINY(1);
    } while (y != 0x06);
    goto L_002113;
L_00214D:
    a = myMapper->readCPU(0x0746 + y);
    if (a < 0x0E) {
        goto L_002145;
    }
L_002154:
    a = myMapper->readCPU(0x0074);
    myMapper->writeCPU(0x0746 + y, a);
    myMapper->writeCPU(0x0074, a);
    myMapper->writeCPU(0x074C + y, 0x01);
    a = y;
    opASL_A(1);
    myMapper->writeCPU(0x0082, a);
    opASL_A(2);
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, 0x00);
    a = myMapper->readCPU(0x0074);
    flgC = false;
    opADC(myMapper->readCPU(0x0074));
    y = a;
    myMapper->writeCPU(0x006F, myMapper->readCPU(0xA413 + y));
    opINY(1);
    myMapper->writeCPU(0x0070, myMapper->readCPU(0xA413 + y));
    y = myMapper->readCPU(0x0082);
    myMapper->writeCPU(0x0735 + y, myMapper->readCPU(0x006F));
    opINY(1);
    myMapper->writeCPU(0x0735 + y, myMapper->readCPU(0x0070));
    goto L_002113;
L_00218C:
    a = 0x00;
    myMapper->writeCPU(0x007D, a);
    myMapper->writeCPU(0x007E, a);
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0082, a);
    myMapper->writeCPU(0x0084, a);
    myMapper->writeCPU(0x0083, 0x7D);
    a = 0x00;
    myMapper->writeCPU(0x0074, a);
    myMapper->writeCPU(0x0073, a);
    while (true) {
        do {
            while (true) {
                do {
                    while (true) {
                        while (true) {
                            a = myMapper->readCPU(0x0074);
                            if (a == 0x17) {
                                goto L_002219;
                            }
                            a = myMapper->readCPU(0x0073);
                            if (a == 0x06) {
                                goto L_0021C2;
                            }
                            y = myMapper->readCPU(0x0073);
                            a = myMapper->readCPU(0x0746 + y);
                            if (a == 0xFF) {
                                goto L_0021BD;
                            }
                            if (a == myMapper->readCPU(0x0074)) {
                                goto L_0021CB;
                            }
                        L_0021BD:
                            opINC(0x0073, 1);
                        }
                    L_0021C2:
                        myMapper->writeCPU(0x0073, 0x00);
                        opINC(0x0074, 1);
                    }
                L_0021CB:
                    a = y;
                    opASL_A(3);
                    myMapper->writeCPU(0x0082, a);
                    opINC(0x0073, 1);
                    opINC(0x0074, 1);
                    y = myMapper->readCPU(0x0082);
                    a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
                    setLoadFlag(a);
                } while (flgZ);
                if (a < 0x05) {
                    goto L_0021EA;
                }
                flgC = true;
                opSBC(0x05);
                y = a;
                myMapper->writeCPU(myMapper->readCPU(0x0083) + (myMapper->readCPU((0x0083 + 1) & 0x00ff) << 8) + y, 0x01);
            }
        L_0021EA:
            flgC = true;
            opSBC(0x01);
            y = a;
        } while (myMapper->readCPU(myMapper->readCPU(0x0083) + (myMapper->readCPU((0x0083 + 1) & 0x00ff) << 8) + y) != 0);
        myMapper->writeCPU(myMapper->readCPU(0x0083) + (myMapper->readCPU((0x0083 + 1) & 0x00ff) << 8) + y, 0x01);
        a = y;
        x = a;
        flgC = false;
        opADC(0x05);
        y = myMapper->readCPU(0x0082);
        myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
        a = x;
        opASL_A(2);
        myMapper->writeCPU(0x007B, a);
        x = 0x00;
        a = 0x04;
        do {
            opPHA();
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(myMapper->readCPU((0x007B + x) & 0x00ff) + (myMapper->readCPU((0x007B + x + 1) & 0x00ff) << 8), a);
            opINC(0x007B, 1);
            opPLA();
            flgC = true;
            opSBC(0x01);
        } while (!flgZ);
    }
L_002219:
    y = 0x00;
    myMapper->writeCPU(0x0081, y);
    myMapper->writeCPU(0x0082, y);
    SUB_00221F();
    return;
}

void game::SUB_00221F() {
    if (myMapper->readCPU(0x038D) == 0) {
        goto L_002227;
    }
    SUB_0022CC();
    return;
L_002227:
    if (myMapper->readCPU(0x0380) != 0) {
        SUB_0022CC();
        return;
    }
    if (myMapper->readCPU(0x0384) != 0) {
        SUB_0022CC();
        return;
    }
    y = myMapper->readCPU(0x0081);
    if (myMapper->readCPU(myMapper->readCPU(0x0075) + (myMapper->readCPU((0x0075 + 1) & 0x00ff) << 8) + y) == 0) {
        SUB_0022CC();
        return;
    }
    y = myMapper->readCPU(0x0082);
    if (myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y) != 0) {
        goto L_00224C;
    }
    pushAddress(0x002246);
    SUB_00238F();
    if (poppedEntry.value != 0x002246) return;
    SUB_00225B();
    return;
L_00224C:
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x07);
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    if (!flgZ) {
        SUB_0022CC();
        return;
    }
    SUB_00225B();
    return;
}

void game::SUB_00225B() {
    pushAddress(0x00225B);
    SUB_00236A();
    if (poppedEntry.value != 0x00225B) return;
    if (a >= 0xF0) {
        SUB_0022E1();
        return;
    }
    if (a < 0xC0) {
        opPHA();
        y = myMapper->readCPU(0x0082);
        a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
        if (a >= 0x05) {
            flgC = true;
            opSBC(0x04);
        }
        if (a == 0x04) {
            opPLA();
            opINY(3);
        }
        else {
            opPLA();
            opPHA();
            opAND(0xF0);
            opLSR_A(3);
            x = a;
            myMapper->writeCPU(0x0083, myMapper->readCPU(0xA3F9 + x));
            a = myMapper->readCPU(0xA3FA + x);
            myMapper->writeCPU(0x0084, a);
            opPLA();
            opAND(0x0F);
            if (!flgZ) {
                x = a;
                do {
                    opLSR_M(0x0083, 1);
                    opROR_M(0x0084, 1);
                    opDEX(1);
                } while (!flgZ);
            }
            a = myMapper->readCPU(0x0082);
            flgC = false;
            opADC(0x04);
            y = a;
            a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
            opAND(0xF8);
            opORA(myMapper->readCPU(0x0083));
            myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
            a = myMapper->readCPU(0x0084);
            opDEY(1);
        }
        myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
        y = myMapper->readCPU(0x0082);
        a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
        if (a < 0x05) {
            goto L_0022BF;
        }
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    }
L_0022BF:
    pushAddress(0x0022BF);
    SUB_00236A();
    if (poppedEntry.value != 0x0022BF) return;
    opPHA();
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x07);
    y = a;
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    SUB_0022CC();
    return;
}

void game::SUB_0022CC() {
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0082, a);
    a = myMapper->readCPU(0x0081);
    opADC(0x01);
    myMapper->writeCPU(0x0081, a);
    if (a >= 0x06) {
        goto L_0022E0;
    }
    SUB_00221F();
    return;
L_0022E0:
    popAddress();
}

void game::SUB_0022E1() {
    opAND(0x0F);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0083, myMapper->readCPU(0xA2F2 + x));
    myMapper->writeCPU(0x0084, myMapper->readCPU(0xA2F3 + x));
    indirectJump(myMapper->readCPU(0x0083) + (myMapper->readCPU((0x0083 + 1) & 0x00ff) << 8));
}

void game::SUB_002312() {
    y = myMapper->readCPU(0x0082);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, 0x00);
    pushAddress(0x002318);
    SUB_00238F();
    if (poppedEntry.value != 0x002318) return;
    SUB_00225B();
    return;
}

void game::SUB_00231E() {
    y = myMapper->readCPU(0x0081);
    a = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x0075) + (myMapper->readCPU((0x0075 + 1) & 0x00ff) << 8) + y, a);
    y = myMapper->readCPU(0x0082);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    y = myMapper->readCPU(0x0081);
    myMapper->writeCPU(0x0746 + y, 0xFF);
    SUB_0022CC();
    return;
}

void game::SUB_002332() {
    pushAddress(0x002332);
    SUB_00236A();
    if (poppedEntry.value != 0x002332) return;
    opPHA();
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x01);
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
    opAND(0x3F);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    opPLA();
    opORA(myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    SUB_00225B();
    return;
}

void game::SUB_00234A() {
    pushAddress(0x00234A);
    SUB_00236A();
    if (poppedEntry.value != 0x00234A) return;
    opPHA();
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x01);
    y = a;
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    SUB_00225B();
    return;
}

void game::SUB_00235A() {
    pushAddress(0x00235A);
    SUB_00236A();
    if (poppedEntry.value != 0x00235A) return;
    opPHA();
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x02);
    y = a;
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    SUB_00225B();
    return;
}

void game::SUB_00236A() {
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x05);
    y = a;
    myMapper->writeCPU(0x0083, myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0084, myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y));
    x = 0x00;
    a = myMapper->readCPU(myMapper->readCPU((0x0083 + x) & 0x00ff) + (myMapper->readCPU((0x0083 + x + 1) & 0x00ff) << 8));
    opPHA();
    a = myMapper->readCPU(0x0083);
    opDEY(1);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0084);
    opADC(0x00);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    opPLA();
    popAddress();
}

void game::SUB_00238F() {
    a = myMapper->readCPU(0x0081);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0079) + (myMapper->readCPU((0x0079 + 1) & 0x00ff) << 8) + y);
    opPHA();
    a = myMapper->readCPU(0x0082);
    opADC(0x05);
    y = a;
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    a = myMapper->readCPU(0x0081);
    opASL_A(1);
    opADC(0x01);
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x0079) + (myMapper->readCPU((0x0079 + 1) & 0x00ff) << 8) + y);
    opPHA();
    a = myMapper->readCPU(0x0082);
    opADC(0x06);
    y = a;
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0023AF);
    SUB_00236A();
    if (poppedEntry.value != 0x0023AF) return;
    y = myMapper->readCPU(0x0082);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0023B6);
    SUB_00236A();
    if (poppedEntry.value != 0x0023B6) return;
    x = a;
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x01);
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, x);
    pushAddress(0x0023C3);
    SUB_00236A();
    if (poppedEntry.value != 0x0023C3) return;
    x = a;
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x02);
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, x);
    pushAddress(0x0023D0);
    SUB_00236A();
    if (poppedEntry.value != 0x0023D0) return;
    x = a;
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x04);
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, x);
    y = myMapper->readCPU(0x0082);
    a = myMapper->readCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y);
    popAddress();
}

void game::SUB_00393D() {
    a = myMapper->readCPU(0x008C);
    opAND(0x7F);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0723, 0xFF);
    a = 0xFF;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0200 + y, a);
        opDEY(1);
    } while (!flgZ);
    y = 0x47;
    do {
        myMapper->writeCPU(0x03AF + y, a);
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x008C);
    opORA(0x80);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0723, 0x00);
    popAddress();
}

void game::SUB_00396C() {
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x00);
    myMapper->writeCPU(0x008B, 0xB9);
    myMapper->writeCPU(0x008A, 0xC5);
    myMapper->writeCPU(0x0086, 0x1E);
    do {
        myMapper->writeCPU(0x0087, 0x20);
        pushAddress(0x003984);
        SUB_00001B();
        if (poppedEntry.value != 0x003984) return;
        flgC = false;
        a = myMapper->readCPU(0x0088);
        opADC(0x20);
        myMapper->writeCPU(0x0088, a);
        a = myMapper->readCPU(0x0089);
        opADC(0x00);
        myMapper->writeCPU(0x0089, a);
        opDEC(0x0086, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0089, 0x28);
    myMapper->writeCPU(0x0088, 0x00);
    myMapper->writeCPU(0x008B, 0xB9);
    myMapper->writeCPU(0x008A, 0xC5);
    myMapper->writeCPU(0x0086, 0x1E);
    do {
        myMapper->writeCPU(0x0087, 0x20);
        pushAddress(0x0039B0);
        SUB_00001B();
        if (poppedEntry.value != 0x0039B0) return;
        flgC = false;
        a = myMapper->readCPU(0x0088);
        opADC(0x20);
        myMapper->writeCPU(0x0088, a);
        a = myMapper->readCPU(0x0089);
        opADC(0x00);
        myMapper->writeCPU(0x0089, a);
        opDEC(0x0086, 1);
    } while (!flgZ);
    popAddress();
}

void game::reset() {
    flgI = true;
    flgD = false;
    s = 0xF3;
    myMapper->writeCPU(0x2000, 0x10);
L_003F9A:
    if (!(myMapper->readCPU(0x2002) & 0x80)) {
        goto L_003F9A;
    }
    a = myMapper->readCPU(0x07BD);
    if (a != 0x55) {
        goto L_003FAD;
    }
    a = myMapper->readCPU(0x07BE);
    if (a == 0xAA) {
        goto L_003FCA;
    }
L_003FAD:
    myMapper->writeCPU(0x008B, 0x07);
    myMapper->writeCPU(0x008A, 0x00);
    a = 0x00;
    do {
        do {
            myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
        } while (!flgZ);
        opDEC(0x008B, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x07BD, 0x55);
    myMapper->writeCPU(0x07BE, 0xAA);
L_003FCA:
    a = 0x00;
    x = 0x00;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opINX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x2001, 0x06);
    myMapper->writeCPU(0x008D, 0x1E);
    myMapper->writeCPU(0x2000, 0x10);
    myMapper->writeCPU(0x008C, 0x10);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x008F, a);
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x0090, a);
    pushAddress(0x003FF1);
    SUB_00396C();
    if (poppedEntry.value != 0x003FF1) return;
    pushAddress(0x003FF4);
    SUB_00393D();
    if (poppedEntry.value != 0x003FF4) return;
    a = 0xFF;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0200 + y, a);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x4015, 0x0F);
    myMapper->writeCPU(0x00D2, 0x00);
    myMapper->writeCPU(0x00D3, 0x03);
    myMapper->writeCPU(0x00D0, 0xC0);
    myMapper->writeCPU(0x00D1, 0x23);
    pushAddress(0x004016);
    SUB_001FDB();
    if (poppedEntry.value != 0x004016) return;
    myMapper->writeCPU(0x072B, 0x01);
    a = 0x06;
    pushAddress(0x004020);
    SUB_0041F5();
    if (poppedEntry.value != 0x004020) return;
    a = 0x02;
    pushAddress(0x004025);
    SUB_0041F5();
    if (poppedEntry.value != 0x004025) return;
    myMapper->writeCPU(0x07C5, 0x00);
    SUB_0042C0();
    return;
}

void game::nmi() {
    myMapper->writeCPU(0x0063, a);
    myMapper->writeCPU(0x0064, x);
    myMapper->writeCPU(0x0065, y);
    a = myMapper->readCPU(0x008C);
    opAND(0x7F);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x008C, a);
    myMapper->writeCPU(0x2003, 0x00);
    myMapper->writeCPU(0x4014, 0x02);
    myMapper->writeCPU(0x2001, 0x00);
    if (myMapper->readCPU(0x03AE) != 0) {
        x = 0x00;
        myMapper->writeCPU(0x00CF, x);
        while (true) {
            a = myMapper->readCPU(0x078F + x);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00407E;
            }
            a = myMapper->readCPU(0x2002);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x078F + x));
            opINX(1);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x078F + x));
            opINX(1);
            y = myMapper->readCPU(0x078F + x);
            opINX(1);
            do {
                myMapper->writeCPU(0x2007, myMapper->readCPU(0x078F + x));
                opINX(1);
                opDEY(1);
            } while (!flgZ);
        }
    L_00407E:
        myMapper->writeCPU(0x03AE, a);
    }
    y = 0x00;
    x = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x00D1));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x00D0));
    x = 0x20;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x00D2) + (myMapper->readCPU((0x00D2 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x00D2);
    flgC = false;
    opADC(0x20);
    opAND(0x7F);
    myMapper->writeCPU(0x00D2, a);
    a = myMapper->readCPU(0x00D0);
    flgC = false;
    opADC(0x20);
    opORA(0xC0);
    myMapper->writeCPU(0x00D0, a);
    a = myMapper->readCPU(0x00D1);
    opADC(0x00);
    if (a >= 0x2C) {
        a = 0x23;
    }
    else {
        if (a < 0x24) {
            goto L_0040C0;
        }
        a = 0x2B;
    }
L_0040C0:
    myMapper->writeCPU(0x00D1, a);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x07FF));
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2005, 0x00);
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0090));
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x008C));
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x008D));
    myMapper->writeCPU(0x072C, s);
    x = 0xFF;
    s = x;
    pushAddress(0x004100);
    SUB_0020EA();
    if (poppedEntry.value != 0x004100) return;
    pushAddress(0x004103);
    SUB_0041AD();
    if (poppedEntry.value != 0x004103) return;
    opINC(0x0062, 1);
    x = 0x00;
    a = 0xC0;
L_00410C:
    opINX(2);
    a = 0xC0;
    if (a == myMapper->readCPU((0x0002 + x) & 0x00ff)) {
        flgC = true;
        a = myMapper->readCPU((0x0022 + x) & 0x00ff);
        opSBC(0x01);
        myMapper->writeCPU((0x0022 + x) & 0x00ff, a);
        a = myMapper->readCPU((0x0023 + x) & 0x00ff);
        opSBC(0x00);
        myMapper->writeCPU((0x0023 + x) & 0x00ff, a);
        if (!flgC) {
            a = myMapper->readCPU((0x0002 + x) & 0x00ff);
            opAND(0xBF);
            myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
        }
    }
    if (x != 0x20) {
        goto L_00410C;
    }
    s = myMapper->readCPU(0x072C);
    if (myMapper->readCPU(0x0385) != 0) {
        opINC(0x0725, 1);
        a = myMapper->readCPU(0x0725);
        if (a == 0x3C) {
            myMapper->writeCPU(0x0725, 0x00);
            opINC(0x0726, 1);
            a = myMapper->readCPU(0x0726);
            opAND(0x01);
            if (flgZ) {
                goto L_004189;
            }
            if (myMapper->readCPU(0x0386) == 0) {
                goto L_004164;
            }
            y = 0x00;
            do {
                myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0xC372 + y));
                opINY(1);
            } while (y != 0x0C);
            goto L_004171;
        L_004164:
            y = 0x00;
            do {
                myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0xC366 + y));
                opINY(1);
            } while (y != 0x0C);
        }
    L_004171:
        y = 0x00;
        do {
            myMapper->writeCPU(0x0224 + y, myMapper->readCPU(0xC37E + y));
            opINY(1);
        } while (y < 0x0C);
        y = 0x09;
        myMapper->writeCPU(0x0224 + y, myMapper->readCPU(0x0436));
        goto L_00419D;
    }
L_004189:
    a = 0xFF;
    y = 0x0B;
    do {
        myMapper->writeCPU(0x0200 + y, a);
        opDEY(1);
    } while (!flgN);
    y = 0x00;
    do {
        myMapper->writeCPU(0x0224 + y, a);
        opINY(1);
    } while (y < 0x0C);
L_00419D:
    a = myMapper->readCPU(0x008C);
    opORA(0x80);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x008C, a);
    y = myMapper->readCPU(0x0065);
    x = myMapper->readCPU(0x0064);
    a = myMapper->readCPU(0x0063);
    return;
}

void game::SUB_0041AD() {
    myMapper->writeCPU(0x4016, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x4016, a);
    myMapper->writeCPU(0x0094, a);
    x = 0x00;
    pushAddress(0x0041BB);
    SUB_0041C7();
    if (poppedEntry.value != 0x0041BB) return;
    opINX(1);
    a = 0x00;
    myMapper->writeCPU(0x0094, a);
    pushAddress(0x0041C3);
    SUB_0041C7();
    if (poppedEntry.value != 0x0041C3) return;
    popAddress();
}

void game::SUB_0041C7() {
    y = 0x08;
    do {
        myMapper->writeCPU(0x0094, a);
        a = myMapper->readCPU(0x4016 + x);
        myMapper->writeCPU(0x0095, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0095));
        opLSR_A(1);
        a = myMapper->readCPU(0x0094);
        opROL_A(1);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0095, x);
    opASL_M(0x0095, 1);
    x = myMapper->readCPU(0x0095);
    myMapper->writeCPU(0x0095, myMapper->readCPU((0x0098 + x) & 0x00ff));
    myMapper->writeCPU((0x0098 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0099 + x) & 0x00ff, a);
    opAND(0xFF);
    if (flgN) {
        opBIT(myMapper->readCPU(0x0095));
        if (!flgN) {
            goto L_0041F4;
        }
        opAND(0x7F);
        myMapper->writeCPU((0x0099 + x) & 0x00ff, a);
    }
L_0041F4:
    popAddress();
}

void game::SUB_0041F5() {
    pushStatus();
    opPHA();
    myMapper->writeCPU(0x0066, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = myMapper->readCPU(0x0066);
    a = myMapper->readCPU((0x0002 + x) & 0x00ff);
    opAND(0x80);
    if (!flgZ) {
        goto L_004230;
    }
    a = myMapper->readCPU((0x0002 + x) & 0x00ff);
    opORA(0x80);
    myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
    a = myMapper->readCPU(0xC38A + x);
    flgC = true;
    opSBC(0x02);
    myMapper->writeCPU(0x0088, a);
    myMapper->writeCPU(0x0089, 0x01);
    y = 0x00;
    myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, 0x04);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xC3AA + x));
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0xC3AB + x));
    flgC = true;
    a = myMapper->readCPU(0x0088);
    opSBC(0x02);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
L_004230:
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    popAddress();
}

void game::SUB_0042C0() {
    while (true) {
        x = myMapper->readCPU(0x0000);
        if (x == 0x20) {
            goto L_0042D8;
        }
        a = 0x20;
        flgC = true;
        opSBC(myMapper->readCPU(0x0000));
        opLSR_A(1);
        y = a;
        a = 0x80;
        do {
            opINX(2);
            if (a == myMapper->readCPU((0x0002 + x) & 0x00ff)) {
                goto L_0042F5;
            }
            opDEY(1);
        } while (!flgZ);
    L_0042D8:
        myMapper->writeCPU(0x0000, 0x00);
        s = 0xF3;
        a = myMapper->readCPU(0x008C);
        opORA(0x80);
        myMapper->writeCPU(0x008C, a);
        myMapper->writeCPU(0x2000, a);
        do {
            a = myMapper->readCPU(0x0062);
        } while (a < 0x03);
        myMapper->writeCPU(0x0062, 0x00);
    }
L_0042F5:
    myMapper->writeCPU(0x0000, x);
    x = myMapper->readCPU((0x0003 + x) & 0x00ff);
    s = x;
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU((0x0043 + x) & 0x00ff);
    x = myMapper->readCPU((0x0042 + x) & 0x00ff);
    opPLA();
    popStatus();
    popAddress();
}

void game::indirectJump(Uint16 target) {
    switch (target) {
    case 0xA332:
        SUB_002332();
        break;
    case 0xA31E:
        SUB_00231E();
        break;
    case 0xA35A:
        SUB_00235A();
        break;
    case 0xA34A:
        SUB_00234A();
        break;
    case 0xA312:
        SUB_002312();
        break;
    }
}
