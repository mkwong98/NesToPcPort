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
    for(auto& thread : threadList) {
        if (thread.threadIdx > -1) {
			thread.threadIdx = -1;
            SDL_LockMutex(thread.lock);
            SDL_SignalCondition(thread.cond);
            SDL_UnlockMutex(thread.lock);

            SDL_WaitThread(thread.thread, NULL);
        }
	}
}


void game::SUB_000000() {
    myMapper->writeCPU(0x038E, 0x1E);
    do {
        myMapper->writeCPU(0x03A8, 0xF8);
        myMapper->writeCPU(0x03A9, 0xFF);
        pushAddress(0x00000F);
        SUB_00004C();
        if (poppedEntry.value != 0x00000F) return;
        pushAddress(0x000012);
        SUB_004275();
        if (poppedEntry.value != 0x000012) return;
        opDEC(0x038E, 1);
    } while (!flgZ);
    popAddress();
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

void game::SUB_00004C() {
    flgC = false;
    a = myMapper->readCPU(0x039C);
    opADC(myMapper->readCPU(0x03A4));
    myMapper->writeCPU(0x039C, a);
    a = myMapper->readCPU(0x039D);
    opADC(myMapper->readCPU(0x03A5));
    myMapper->writeCPU(0x039D, a);
    flgC = false;
    a = myMapper->readCPU(0x039F);
    opADC(myMapper->readCPU(0x03A7));
    myMapper->writeCPU(0x039F, a);
    a = myMapper->readCPU(0x03A0);
    myMapper->writeCPU(0x03A2, a);
    opADC(myMapper->readCPU(0x03A8));
    myMapper->writeCPU(0x03A0, a);
    y = myMapper->readCPU(0x03A1);
    myMapper->writeCPU(0x03A3, y);
    if (a >= 0xF0) {
        if (a >= 0xF8) {
            opDEC(0x03A1, 1);
            flgC = true;
            opSBC(0x10);
        }
        else{
            opINC(0x03A1, 1);
            flgC = false;
            opADC(0x10);
        }
        myMapper->writeCPU(0x03A0, a);
    }
    a = myMapper->readCPU(0x03A0);
    opAND(0x08);
    myMapper->writeCPU(0x0086, a);
    a = myMapper->readCPU(0x03A2);
    opAND(0x08);
    if (a == myMapper->readCPU(0x0086)) {
        goto L_0000AB;
    }
    pushAddress(0x0000A8);
    SUB_0000DA();
    if (poppedEntry.value != 0x0000A8) return;
L_0000AB:
    myMapper->writeCPU(0x008F, myMapper->readCPU(0x039D));
    myMapper->writeCPU(0x0090, myMapper->readCPU(0x03A0));
    a = myMapper->readCPU(0x03A1);
    opASL_A(1);
    opAND(0x02);
    myMapper->writeCPU(0x0086, a);
    a = myMapper->readCPU(0x008C);
    opAND(0xFD);
    opORA(myMapper->readCPU(0x0086));
    myMapper->writeCPU(0x008C, a);
    a = 0x00;
    myMapper->writeCPU(0x03A4, a);
    myMapper->writeCPU(0x03A5, a);
    myMapper->writeCPU(0x03A6, a);
    myMapper->writeCPU(0x03A7, a);
    myMapper->writeCPU(0x03A8, a);
    myMapper->writeCPU(0x03A9, a);
    popAddress();
}

void game::SUB_0000DA() {
    myMapper->writeCPU(0x0086, 0x04);
    if (!(myMapper->readCPU(0x03A9) & 0x80)) {
        myMapper->writeCPU(0x0086, 0xEE);
    }
    a = myMapper->readCPU(0x03A0);
    flgC = false;
    opADC(myMapper->readCPU(0x0086));
    myMapper->writeCPU(0x039A, a);
    if (flgC || a >= 0xF0) {
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x039A, a);
        y = myMapper->readCPU(0x03A1);
        opINY(1);
        myMapper->writeCPU(0x0399, y);
    }
    else {
        myMapper->writeCPU(0x0399, myMapper->readCPU(0x03A1));
    }
    a = myMapper->readCPU(0x039D);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0397, a);
    myMapper->writeCPU(0x0396, 0x00);
    pushAddress(0x000120);
    SUB_0001E6();
    if (poppedEntry.value != 0x000120) return;
    pushAddress(0x000123);
    SUB_00026C();
    if (poppedEntry.value != 0x000123) return;
    a = myMapper->readCPU(0x008B);
    x = 0x00;
    myMapper->writeCPU(0x078F + x, a);
    opINX(1);
    myMapper->writeCPU(0x078F + x, myMapper->readCPU(0x008A));
    opINX(1);
    myMapper->writeCPU(0x078F + x, 0x00);
    myMapper->writeCPU(0x0087, x);
    opINX(1);
    a = 0x00;
    myMapper->writeCPU(0x0086, a);
    myMapper->writeCPU(0x0088, a);
    pushAddress(0x000142);
    SUB_00024F();
    if (poppedEntry.value != 0x000142) return;
    a = myMapper->readCPU(0x0397);
    opAND(0x08);
    Uint8 startY = 0;
    if (!flgZ) {
        startY = 1;
    }
    while (true) {
        while (true) {
            for(; startY < 2; startY++) {
                y = startY;
                a = myMapper->readCPU(0x039A);
                opAND(0x08);
                if (!flgZ) {
                    opINY(2);
                }
                myMapper->writeCPU(0x078F + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
                opINX(1);
                opINC(0x0086, 1);
                opINC(0x0088, 1);
                a = myMapper->readCPU(0x0086);
                if (a == 0x22) {
                    goto L_0001D1;
                }
			}
            startY = 0;
            pushAddress(0x000182);
            SUB_0002B9();
            if (poppedEntry.value != 0x000182) return;
            a = myMapper->readCPU(0x03AA);
            flgC = false;
            opADC(0x01);
            opAND(0x10);
            myMapper->writeCPU(0x0085, a);
            a = myMapper->readCPU(0x03AA);
            opAND(0x10);
            if (a != myMapper->readCPU(0x0085)) {
                goto L_0001A1;
            }
            opINC(0x03AA, 1);
            pushAddress(0x00019B);
            SUB_00024F();
            if (poppedEntry.value != 0x00019B) return;
        }
    L_0001A1:
        y = myMapper->readCPU(0x0087);
        myMapper->writeCPU(0x078F + y, myMapper->readCPU(0x0088));
        myMapper->writeCPU(0x0088, 0x00);
        a = myMapper->readCPU(0x078D + y);
        opEOR(0x04);
        myMapper->writeCPU(0x078F + x, a);
        opINX(1);
        a = myMapper->readCPU(0x078E + y);
        opAND(0xE0);
        myMapper->writeCPU(0x078F + x, a);
        opINX(1);
        myMapper->writeCPU(0x0087, x);
        opINX(1);
        myMapper->writeCPU(0x0397, 0x00);
        a = myMapper->readCPU(0x00CA);
        pushAddress(0x0001C8);
        SUB_0001EE();
        if (poppedEntry.value != 0x0001C8) return;
        pushAddress(0x0001CB);
        SUB_00024F();
        if (poppedEntry.value != 0x0001CB) return;
    }
L_0001D1:
    pushAddress(0x0001D1);
    SUB_0002B9();
    if (poppedEntry.value != 0x0001D1) return;
    myMapper->writeCPU(0x078F + x, 0x00);
    a = myMapper->readCPU(0x0088);
    x = myMapper->readCPU(0x0087);
    myMapper->writeCPU(0x078F + x, a);
    myMapper->writeCPU(0x03AE, 0xFF);
    popAddress();
}

void game::SUB_0001E6() {
    a = myMapper->readCPU(0x0399);
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
    SUB_0001EE();
    return;
}

void game::SUB_0001EE() {
    myMapper->writeCPU(0x00CA, a);
    y = a;
    a = myMapper->readCPU(0x844B + y);
    myMapper->writeCPU(0x00CB, a);
    flgC = false;
    opADC(0x85);
    myMapper->writeCPU(0x00CD, a);
    myMapper->writeCPU(0x00CC, 0x4B);
    myMapper->writeCPU(0x038C, myMapper->readCPU(0x00CB));
    myMapper->writeCPU(0x038B, 0x00);
    opASL_M(0x038C, 1);
    opROL_M(0x038B, 1);
    opASL_M(0x038C, 1);
    opROL_M(0x038B, 1);
    opASL_M(0x038C, 1);
    opROL_M(0x038B, 1);
    opASL_M(0x038C, 1);
    opROL_M(0x038B, 1);
    flgC = true;
    a = myMapper->readCPU(0x00CC);
    opSBC(myMapper->readCPU(0x038C));
    myMapper->writeCPU(0x00CC, a);
    a = myMapper->readCPU(0x00CD);
    opSBC(myMapper->readCPU(0x038B));
    myMapper->writeCPU(0x00CD, a);
    a = myMapper->readCPU(0x0397);
    opLSR_A(4);
    myMapper->writeCPU(0x03AA, a);
    a = myMapper->readCPU(0x039A);
    opAND(0xF0);
    flgC = false;
    opADC(myMapper->readCPU(0x03AA));
    myMapper->writeCPU(0x03AA, a);
    SUB_000246();
    return;
}

void game::SUB_000246() {
    y = myMapper->readCPU(0x03AA);
    a = myMapper->readCPU(myMapper->readCPU(0x00CC) + (myMapper->readCPU((0x00CC + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x03AB, a);
    popAddress();
}

void game::SUB_00024F() {
    myMapper->writeCPU(0x008B, 0x00);
    pushAddress(0x000253);
    SUB_000246();
    if (poppedEntry.value != 0x000253) return;
    opASL_A(1);
    opROL_M(0x008B, 1);
    opASL_A(1);
    opROL_M(0x008B, 1);
    myMapper->writeCPU(0x008A, a);
    a = 0xDB;
    flgC = false;
    opADC(myMapper->readCPU(0x008A));
    myMapper->writeCPU(0x008A, a);
    a = 0x9A;
    opADC(myMapper->readCPU(0x008B));
    myMapper->writeCPU(0x008B, a);
    popAddress();
}

void game::SUB_00026C() {
    myMapper->writeCPU(0x008B, 0x00);
    a = myMapper->readCPU(0x039A);
    opAND(0xF8);
    opASL_A(1);
    opROL_M(0x008B, 1);
    opASL_A(1);
    opROL_M(0x008B, 1);
    myMapper->writeCPU(0x008A, a);
    a = myMapper->readCPU(0x0397);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x008A));
    myMapper->writeCPU(0x008A, a);
    a = myMapper->readCPU(0x008B);
    opADC(0x00);
    myMapper->writeCPU(0x008B, a);
    if (a == 0x03) {
        a = myMapper->readCPU(0x008A);
        if (a >= 0xC0) {
            flgC = false;
            opADC(0x20);
            myMapper->writeCPU(0x008A, a);
            a = myMapper->readCPU(0x008B);
            opADC(0x00);
            opAND(0x03);
            myMapper->writeCPU(0x008B, a);
        }
    }
    a = myMapper->readCPU(0x008B);
    opORA(0x20);
    myMapper->writeCPU(0x008B, a);
    a = myMapper->readCPU(0x0399);
    opAND(0x01);
    if (flgZ) {
        goto L_0002B8;
    }
    a = myMapper->readCPU(0x008B);
    opORA(0x08);
    myMapper->writeCPU(0x008B, a);
L_0002B8:
    popAddress();
}

void game::SUB_0002B9() {
    a = myMapper->readCPU(0x00CA);
    opAND(0x01);
    if (!flgZ) {
        a = 0x03;
        y = 0x40;
    }
    else {
        a = 0x03;
        y = 0x00;
    }
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, y);
    a = myMapper->readCPU(0x03AA);
    opAND(0x0F);
    opLSR_A(1);
    myMapper->writeCPU(0x0732, a);
    a = myMapper->readCPU(0x03AA);
    opAND(0xE0);
    opLSR_A(2);
    opORA(myMapper->readCPU(0x0732));
    myMapper->writeCPU(0x0732, a);
    y = myMapper->readCPU(0x03AB);
    myMapper->writeCPU(0x0734, myMapper->readCPU(0x9EDB + y));
    y = myMapper->readCPU(0x0732);
    myMapper->writeCPU(0x0733, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x03AA);
    opAND(0x01);
    if (flgZ) {
        a = myMapper->readCPU(0x03AA);
        opAND(0x10);
        if (flgZ) {
            a = 0xFC;
            goto L_00032D;
        }
        a = 0xCF;
        goto L_000321;
    }
    a = myMapper->readCPU(0x03AA);
    opAND(0x10);
    if (!flgZ) {
        goto L_000319;
    }
    a = 0xF3;
    goto L_000327;
L_000319:
    a = 0x3F;
    opASL_M(0x0734, 2);
L_000321:
    opASL_M(0x0734, 2);
L_000327:
    opASL_M(0x0734, 2);
L_00032D:
    opAND(myMapper->readCPU(0x0733));
    opORA(myMapper->readCPU(0x0734));
    myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
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

void game::SUB_00205B() {
    y = 0x00;
    do {
        if (a == myMapper->readCPU(0x0746 + y)) {
            goto L_002069;
        }
        opINY(1);
    } while (y != 0x06);
    flgC = false;
    popAddress();
    return;
L_002069:
    flgC = true;
    popAddress();
}

void game::SUB_00206B() {
    y = a;
    opLSR_A(3);
    myMapper->writeCPU(0x0087, a);
    a = 0x41;
    flgC = false;
    opADC(myMapper->readCPU(0x0087));
    myMapper->writeCPU(0x008A, a);
    a = 0x07;
    opADC(0x00);
    myMapper->writeCPU(0x008B, a);
    a = y;
    opAND(0x07);
    y = a;
    a = myMapper->readCPU(0xA08C + y);
    y = 0x00;
    opORA(myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_002094() {
    pushAddress(0x002094);
    SUB_00205B();
    if (poppedEntry.value != 0x002094) return;
    if (flgC) {
        goto L_00209A;
    }
    popAddress();
    return;
L_00209A:
    myMapper->writeCPU(0x0087, y);
    myMapper->writeCPU(0x0086, myMapper->readCPU(0x0746 + y));
    a = 0xE2;
    flgC = false;
    opADC(myMapper->readCPU(0x0086));
    myMapper->writeCPU(0x008A, a);
    a = 0xA3;
    opADC(0x00);
    myMapper->writeCPU(0x008B, a);
    y = 0x00;
    myMapper->writeCPU(0x008B, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opASL_M(0x0087, 3);
    y = myMapper->readCPU(0x0087);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x008B));
    a = 0x05;
    flgC = false;
    opADC(myMapper->readCPU(0x0087));
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, 0x3B);
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x0077) + (myMapper->readCPU((0x0077 + 1) & 0x00ff) << 8) + y, 0xA7);
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

void game::SUB_00273E() {
    a = myMapper->readCPU(0x03A1);
    setLoadFlag(a);
    if (flgZ) {
        goto L_002747;
    }
    if (a < 0x21) {
        goto L_002752;
    }
L_002747:
    myMapper->writeCPU(0x008B, 0xA7);
    myMapper->writeCPU(0x008A, 0x70);
    SUB_00275A();
    return;
L_002752:
    myMapper->writeCPU(0x008B, 0xA7);
    myMapper->writeCPU(0x008A, 0x90);
    SUB_00275A();
    return;
}

void game::SUB_00275A() {
    myMapper->writeCPU(0x0087, 0x20);
    myMapper->writeCPU(0x0089, 0x3F);
    myMapper->writeCPU(0x0088, 0x00);
    y = 0x00;
    myMapper->writeCPU(0x07FF, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    SUB_00001B();
    return;
}

void game::SUB_002816() {
    opINC(0x008A, 1);
    a = myMapper->readCPU(0x008A);
    if (a != 0x0A) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x008A, 0x00);
    opINC(0x008B, 1);
    a = myMapper->readCPU(0x008B);
    if (a == 0x0A) {
        goto L_00282C;
    }
    popAddress();
    return;
L_00282C:
    myMapper->writeCPU(0x008B, 0x00);
    opINC(0x038B, 1);
    popAddress();
}

void game::SUB_002834() {
    myMapper->writeCPU(0x0086, 0x00);
    while (true) {
        a = myMapper->readCPU(0x008A);
        flgC = true;
        opSBC(myMapper->readCPU(0x0088));
        myMapper->writeCPU(0x008A, a);
        a = myMapper->readCPU(0x008B);
        opSBC(myMapper->readCPU(0x0089));
        myMapper->writeCPU(0x008B, a);
        a = myMapper->readCPU(0x038B);
        opSBC(0x00);
        myMapper->writeCPU(0x038B, a);
        if (!flgC) {
            goto L_002854;
        }
        opINC(0x0086, 1);
    }
L_002854:
    popAddress();
}

void game::SUB_002855() {
    myMapper->writeCPU(0x0089, myMapper->readCPU(0x038B));
    myMapper->writeCPU(0x0088, myMapper->readCPU(0x008B));
    myMapper->writeCPU(0x0087, myMapper->readCPU(0x008A));
    a = 0x00;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, a);
    myMapper->writeCPU(0x038B, a);
    myMapper->writeCPU(0x0086, a);
    do {
        opLSR_M(0x0089, 1);
        opROR_M(0x0088, 1);
        opROR_M(0x0087, 1);
        opROR_M(0x0086, 1);
        opASL_M(0x0085, 1);
        if (!flgC) {
            goto L_00288E;
        }
        a = myMapper->readCPU(0x0086);
        flgC = false;
        opADC(myMapper->readCPU(0x008A));
        myMapper->writeCPU(0x008A, a);
        a = myMapper->readCPU(0x0087);
        opADC(myMapper->readCPU(0x008B));
        myMapper->writeCPU(0x008B, a);
        a = myMapper->readCPU(0x0088);
        opADC(myMapper->readCPU(0x038B));
        myMapper->writeCPU(0x038B, a);
    L_00288E:
        a = myMapper->readCPU(0x0085);
        setLoadFlag(a);
    } while (!flgZ);
    popAddress();
}

void game::SUB_002893() {
    myMapper->writeCPU(0x0397, myMapper->readCPU(0x043F));
    myMapper->writeCPU(0x0396, myMapper->readCPU(0x0440));
    myMapper->writeCPU(0x0391, myMapper->readCPU(0x043D));
    myMapper->writeCPU(0x0390, myMapper->readCPU(0x043E));
    SUB_0028C6();
    return;
}

void game::SUB_0028AE() {
    myMapper->writeCPU(0x0397, myMapper->readCPU(0x043B));
    myMapper->writeCPU(0x0396, myMapper->readCPU(0x043C));
    myMapper->writeCPU(0x0391, myMapper->readCPU(0x0439));
    myMapper->writeCPU(0x0390, myMapper->readCPU(0x043A));
    SUB_0028C6();
    return;
}

void game::SUB_0028C6() {
    myMapper->writeCPU(0x038B, 0x00);
    myMapper->writeCPU(0x008A, myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x008B, myMapper->readCPU(0x0396));
    myMapper->writeCPU(0x0085, 0x64);
    pushAddress(0x0028D9);
    SUB_002855();
    if (poppedEntry.value != 0x0028D9) return;
    a = myMapper->readCPU(0x0391);
    myMapper->writeCPU(0x0088, a);
    opORA(myMapper->readCPU(0x0390));
    if (!flgZ) {
        goto L_0028F0;
    }
    a = 0x00;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, a);
    myMapper->writeCPU(0x038B, a);
    popAddress();
    return;
L_0028F0:
    myMapper->writeCPU(0x0089, myMapper->readCPU(0x0390));
    pushAddress(0x0028F5);
    SUB_002834();
    if (poppedEntry.value != 0x0028F5) return;
    myMapper->writeCPU(0x008A, myMapper->readCPU(0x0086));
    a = 0x00;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x038B, a);
    while (true) {
        do {
            a = myMapper->readCPU(0x008A);
            flgC = true;
            opSBC(0x0A);
            if (!flgC) {
                goto L_00291D;
            }
            myMapper->writeCPU(0x008A, a);
            opINC(0x008B, 1);
            a = myMapper->readCPU(0x008B);
            flgC = true;
            opSBC(0x0A);
        } while (!flgC);
        myMapper->writeCPU(0x008B, a);
        opINC(0x038B, 1);
    }
L_00291D:
    popAddress();
}

void game::SUB_0029D3() {
    y = 0x00;
    pushAddress(0x0029D5);
    SUB_0030BC();
    if (poppedEntry.value != 0x0029D5) return;
    pushAddress(0x0029D8);
    SUB_0030E5();
    if (poppedEntry.value != 0x0029D8) return;
    myMapper->writeCPU(0x00B0, 0x50);
    myMapper->writeCPU(0x00B2, 0x20);
    myMapper->writeCPU(0x00B1, 0xB0);
    myMapper->writeCPU(0x00B3, 0xE0);
    SUB_002A00();
    return;
}

void game::SUB_0029F4() {
    a = 0x06;
    myMapper->writeCPU(0x00B0, a);
    myMapper->writeCPU(0x00B2, a);
    a = 0xFA;
    myMapper->writeCPU(0x00B1, a);
    myMapper->writeCPU(0x00B3, a);
    SUB_002A00();
    return;
}

void game::SUB_002A00() {
    myMapper->writeCPU(0x00DE, myMapper->readCPU(0x0399));
    pushAddress(0x002A05);
    SUB_002EAD();
    if (poppedEntry.value != 0x002A05) return;
    pushAddress(0x002A08);
    SUB_00311F();
    if (poppedEntry.value != 0x002A08) return;
    a = myMapper->readCPU(0x0396);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0397);
        opCMP(a, myMapper->readCPU(0x00B0));
        if (!flgC) {
            goto L_002A24;
        }
        if (flgC) {
            goto L_002A5D;
        }
    }
    if (a == 0xFF) {
        a = myMapper->readCPU(0x0397);
        if (a >= myMapper->readCPU(0x00B1)) {
        L_002A24:
            a = myMapper->readCPU(0x0399);
            setLoadFlag(a);
            if (flgZ) {
                a = myMapper->readCPU(0x00DE);
                if (a != myMapper->readCPU(0x0393)) {
                    a = myMapper->readCPU(0x039A);
                    flgC = true;
                    opSBC(0x10);
                    myMapper->writeCPU(0x039A, a);
                }
                a = myMapper->readCPU(0x039A);
                opCMP(a, myMapper->readCPU(0x00B2));
                if (!flgC) {
                    goto L_002A5F;
                }
                if (flgC) {
                    goto L_002A5D;
                }
            }
            if (a == 0xFF) {
                a = myMapper->readCPU(0x00DE);
                if (a == myMapper->readCPU(0x0393)) {
                    goto L_002A56;
                }
                a = myMapper->readCPU(0x039A);
                flgC = false;
                opADC(0x10);
                myMapper->writeCPU(0x039A, a);
            L_002A56:
                a = myMapper->readCPU(0x039A);
                if (a >= myMapper->readCPU(0x00B3)) {
                    goto L_002A5F;
                }
            }
        }
    }
L_002A5D:
    flgC = false;
    popAddress();
    return;
L_002A5F:
    flgC = true;
    popAddress();
}

void game::SUB_002A61() {
    myMapper->writeCPU(0x071D, y);
    myMapper->writeCPU(0x0391, myMapper->readCPU(0x04C0 + x));
    myMapper->writeCPU(0x0394, myMapper->readCPU(0x04A7 + x));
    myMapper->writeCPU(0x0397, myMapper->readCPU(0x04C0 + y));
    myMapper->writeCPU(0x039A, myMapper->readCPU(0x04A7 + y));
    a = myMapper->readCPU(0x04D9 + x);
    pushAddress(0x002A7F);
    SUB_002B2C();
    if (poppedEntry.value != 0x002A7F) return;
    y = 0x00;
    do {
        myMapper->writeCPU(0x00B0 + y, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y < 0x04);
    y = myMapper->readCPU(0x071D);
    a = myMapper->readCPU(0x04D9 + y);
    pushAddress(0x002A94);
    SUB_002B2C();
    if (poppedEntry.value != 0x002A94) return;
    y = 0x00;
    do {
        myMapper->writeCPU(0x00B4 + y, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y < 0x04);
    a = myMapper->readCPU(0x0391);
    flgC = false;
    opADC(myMapper->readCPU(0x00B1));
    if (flgC) {
        a = 0xFF;
    }
    myMapper->writeCPU(0x0087, a);
    a = myMapper->readCPU(0x0397);
    flgC = true;
    opSBC(myMapper->readCPU(0x00B4));
    if (!flgC) {
        a = 0x00;
    }
    if (a >= myMapper->readCPU(0x0087)) {
    }
    else {
        a = myMapper->readCPU(0x0391);
        flgC = true;
        opSBC(myMapper->readCPU(0x00B0));
        if (!flgC) {
            a = 0x00;
        }
        myMapper->writeCPU(0x0087, a);
        a = myMapper->readCPU(0x0397);
        flgC = false;
        opADC(myMapper->readCPU(0x00B5));
        if (flgC) {
            a = 0xFF;
        }
        if (a < myMapper->readCPU(0x0087)) {
        }
        else {
            a = myMapper->readCPU(0x0394);
            flgC = false;
            opADC(myMapper->readCPU(0x00B3));
            if (!flgC) {
                if (a >= 0xF0) {
                    goto L_002AEC;
                }
                goto L_002AEE;
            }
        L_002AEC:
            a = 0xFF;
        L_002AEE:
            myMapper->writeCPU(0x0087, a);
            a = myMapper->readCPU(0x039A);
            flgC = true;
            opSBC(myMapper->readCPU(0x00B6));
            if (!flgC) {
                a = 0x00;
            }
            if (a >= myMapper->readCPU(0x0087)) {
            }
            else {
                a = myMapper->readCPU(0x0394);
                flgC = true;
                opSBC(myMapper->readCPU(0x00B2));
                if (!flgC) {
                    a = 0x00;
                }
                myMapper->writeCPU(0x0087, a);
                a = myMapper->readCPU(0x039A);
                flgC = false;
                opADC(myMapper->readCPU(0x00B7));
                if (!flgC) {
                    if (a >= 0xF0) {
                        goto L_002B1C;
                    }
                    goto L_002B1E;
                }
            L_002B1C:
                a = 0xFF;
            L_002B1E:
                if (a >= myMapper->readCPU(0x0087)) {
                    goto L_002B27;
                }
            }
        }
    }
    y = myMapper->readCPU(0x071D);
    flgC = false;
    popAddress();
    return;
L_002B27:
    y = myMapper->readCPU(0x071D);
    flgC = true;
    popAddress();
}

void game::SUB_002B2C() {
    if (a != 0x00) {
        goto L_002B35;
    }
    a = 0x00;
    goto L_002BC2;
L_002B35:
    if (a == 0x01) {
        a = 0x01;
    }
    else {
        if (a != 0x07) {
            goto L_002B47;
        }
        a = 0x0A;
        goto L_002BC2;
    L_002B47:
        if (a == 0x08) {
            a = 0x02;
        }
        else {
            if (a != 0x09) {
                goto L_002B59;
            }
            a = 0x03;
            goto L_002BC2;
        L_002B59:
            if (a == 0x0A) {
                a = 0x04;
            }
            else {
                if (a != 0x0B) {
                    goto L_002B6B;
                }
                a = 0x05;
                goto L_002BC2;
            L_002B6B:
                if (a == 0x0C) {
                    a = 0x06;
                }
                else {
                    if (a != 0x0D) {
                        goto L_002B7D;
                    }
                    a = 0x07;
                    goto L_002BC2;
                L_002B7D:
                    if (a == 0x0E) {
                        a = 0x08;
                    }
                    else {
                        if (a != 0x0F) {
                            goto L_002B8F;
                        }
                        a = 0x09;
                        goto L_002BC2;
                    L_002B8F:
                        if (a >= 0x10) {
                            if (a >= 0x60) {
                                goto L_002B9C;
                            }
                            a = 0x0B;
                            goto L_002BC2;
                        }
                    L_002B9C:
                        if (a < 0x72) {
                            a = 0x0C;
                        }
                        else {
                            if (a >= 0x79) {
                                goto L_002BAE;
                            }
                            a = 0x0D;
                            goto L_002BC2;
                        L_002BAE:
                            if (a < 0x8E) {
                                a = 0x0E;
                            }
                            else {
                                if (a >= 0x8F) {
                                    goto L_002BC0;
                                }
                                a = 0x0F;
                                goto L_002BC2;
                            L_002BC0:
                                a = 0x10;
                            }
                        }
                    }
                }
            }
        }
    }
L_002BC2:
    opASL_A(2);
    flgC = false;
    opADC(0xD0);
    myMapper->writeCPU(0x008A, a);
    a = 0x00;
    opADC(0xAB);
    myMapper->writeCPU(0x008B, a);
    popAddress();
}

void game::SUB_002C14() {
    a = 0x00;
    myMapper->writeCPU(0x0089, a);
    myMapper->writeCPU(0x0088, a);
    SUB_002C1A();
    return;
}

void game::SUB_002C1A() {
    myMapper->writeCPU(0x038B, x);
    myMapper->writeCPU(0x038C, y);
    a = myMapper->readCPU(0x042B);
    flgC = false;
    opADC(myMapper->readCPU(0x008A));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
    }
    myMapper->writeCPU(0x042B, a);
    a = myMapper->readCPU(0x042A);
    opADC(myMapper->readCPU(0x008B));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
    }
    myMapper->writeCPU(0x042A, a);
    a = myMapper->readCPU(0x0429);
    opADC(myMapper->readCPU(0x0088));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
    }
    myMapper->writeCPU(0x0429, a);
    a = myMapper->readCPU(0x0428);
    opADC(myMapper->readCPU(0x0089));
    opCMP(a, 0x0A);
    if (flgC) {
        flgC = true;
        opSBC(0x0A);
    }
    myMapper->writeCPU(0x0428, a);
    a = myMapper->readCPU(0x0427);
    opADC(0x00);
    if (a >= 0x0A) {
        flgC = true;
        opSBC(0x0A);
    }
    myMapper->writeCPU(0x0427, a);
    pushAddress(0x002C6C);
    SUB_002D39();
    if (poppedEntry.value != 0x002C6C) return;
    if (myMapper->readCPU(0x042E) == 0) {
        a = myMapper->readCPU(0x0428);
        if (a < 0x02) {
            goto L_002CC8;
        }
        myMapper->writeCPU(0x042E, 0xFF);
        a = 0x00;
        myMapper->writeCPU(0x0430, a);
        myMapper->writeCPU(0x042F, a);
        goto L_002CA6;
    }
    a = myMapper->readCPU(0x0427);
    opCMP(a, myMapper->readCPU(0x042F));
    if (!flgZ) {
        if (flgC) {
            goto L_002CA6;
        }
        goto L_002CC8;
    }
    a = myMapper->readCPU(0x0428);
    if (a < myMapper->readCPU(0x0430)) {
        goto L_002CC8;
    }
L_002CA6:
    pushAddress(0x002CA6);
    SUB_002D0E();
    if (poppedEntry.value != 0x002CA6) return;
    a = myMapper->readCPU(0x0430);
    flgC = false;
    opADC(0x08);
    if (a < 0x0A) {
        goto L_002CC5;
    }
    flgC = true;
    opSBC(0x0A);
    myMapper->writeCPU(0x0430, a);
    a = myMapper->readCPU(0x042F);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x042F, a);
    goto L_002CC8;
L_002CC5:
    myMapper->writeCPU(0x0430, a);
L_002CC8:
    y = 0x00;
    do {
        a = myMapper->readCPU(0x07BF + y);
        opCMP(a, myMapper->readCPU(0x0427 + y));
        if (!flgC) {
            goto L_002CE0;
        }
        if (!flgZ) {
            goto L_002CD9;
        }
        opINY(1);
    } while (y != 0x06);
    while (true) {
        while (true) {
        L_002CD9:
            x = myMapper->readCPU(0x038B);
            y = myMapper->readCPU(0x038C);
            popAddress();
            return;
        L_002CE0:
            y = 0x00;
            do {
                myMapper->writeCPU(0x07BF + y, myMapper->readCPU(0x0427 + y));
                opINY(1);
            } while (y != 0x06);
            if (myMapper->readCPU(0x0386) != 0) {
                goto L_002D00;
            }
            y = 0x05;
            do {
                myMapper->writeCPU(0x07BF + y, myMapper->readCPU(0x044A + y));
                opDEY(1);
            } while (!flgN);
        }
    L_002D00:
        y = 0x05;
        do {
            myMapper->writeCPU(0x07BF + y, myMapper->readCPU(0x046B + y));
            opDEY(1);
        } while (!flgN);
    }
    SUB_002D0E();
    return;
}

void game::SUB_002D0E() {
    opINC(0x0432, 1);
    a = myMapper->readCPU(0x0432);
    if (a >= 0x0A) {
        myMapper->writeCPU(0x0432, 0x00);
        a = myMapper->readCPU(0x0431);
        if (a == 0x09) {
            goto L_002D2A;
        }
        opINC(0x0431, 1);
        goto L_002D2F;
    L_002D2A:
        myMapper->writeCPU(0x0431, 0x09);
    }
L_002D2F:
    a = 0x10;
    pushAddress(0x002D31);
    SUB_00206B();
    if (poppedEntry.value != 0x002D31) return;
    a = 0x11;
    SUB_00206B();
    return;
}

void game::SUB_002D39() {
    a = myMapper->readCPU(0x0380);
    if (a == 0xFF) {
        popAddress();
        return;
    }
    y = 0x00;
    x = 0x00;
    if (myMapper->readCPU(0x0386) != 0) {
        goto L_002D5D;
    }
    myMapper->writeCPU(0x008A, 0x4A);
    myMapper->writeCPU(0x008B, 0x04);
    myMapper->writeCPU(0x0088, 0x99);
    myMapper->writeCPU(0x0089, 0xAD);
    goto L_002D6D;
L_002D5D:
    myMapper->writeCPU(0x008A, 0x6B);
    myMapper->writeCPU(0x008B, 0x04);
    myMapper->writeCPU(0x0088, 0xB1);
    myMapper->writeCPU(0x0089, 0xAD);
    do {
    L_002D6D:
        a = myMapper->readCPU(0x0427 + x);
        opAND(0x0F);
        myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opINX(1);
    } while (x != 0x06);
    y = 0x00;
    do {
        myMapper->writeCPU(0x020C + y, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x18);
    y = 0x00;
    x = 0x01;
    do {
        myMapper->writeCPU(0x020C + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
        opINX(4);
    } while (y != 0x06);
    popAddress();
}

void game::SUB_002DC9() {
    myMapper->writeCPU(0x0087, y);
    pushAddress(0x002DCB);
    SUB_002EAD();
    if (poppedEntry.value != 0x002DCB) return;
    flgC = true;
    a = myMapper->readCPU(0x039A);
    opSBC(myMapper->readCPU(0x0394));
    myMapper->writeCPU(0x039A, a);
    a = myMapper->readCPU(0x0399);
    opSBC(myMapper->readCPU(0x0393));
    myMapper->writeCPU(0x0399, a);
    flgC = true;
    a = myMapper->readCPU(0x0397);
    opSBC(myMapper->readCPU(0x0391));
    myMapper->writeCPU(0x0397, a);
    a = myMapper->readCPU(0x0396);
    opSBC(myMapper->readCPU(0x0390));
    myMapper->writeCPU(0x0396, a);
    if (!flgN) {
        if (myMapper->readCPU(0x0399) & 0x80) {
            goto L_002E00;
        }
        a = 0x04;
        goto L_002E17;
    L_002E00:
        pushAddress(0x002E00);
        SUB_002E8C();
        if (poppedEntry.value != 0x002E00) return;
        a = 0x00;
        goto L_002E17;
    }
    if (!(myMapper->readCPU(0x0399) & 0x80)) {
        pushAddress(0x002E0D);
        SUB_002E8C();
        if (poppedEntry.value != 0x002E0D) return;
        a = 0x08;
    }
    else {
        a = 0x0C;
    }
L_002E17:
    myMapper->writeCPU(0x0086, a);
    if (myMapper->readCPU(0x0399) & 0x80) {
        a = 0x00;
        flgC = true;
        opSBC(myMapper->readCPU(0x039A));
        myMapper->writeCPU(0x039A, a);
        a = 0x00;
        opSBC(myMapper->readCPU(0x0399));
        myMapper->writeCPU(0x0399, a);
    }
    if (!(myMapper->readCPU(0x0396) & 0x80)) {
        goto L_002E45;
    }
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x0397, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x0396));
    myMapper->writeCPU(0x0396, a);
    while (true) {
    L_002E45:
        if (myMapper->readCPU(0x0399) != 0) {
            goto L_002E4F;
        }
        if (myMapper->readCPU(0x0396) == 0) {
            goto L_002E5E;
        }
    L_002E4F:
        opLSR_M(0x0399, 1);
        opROR_M(0x039A, 1);
        opLSR_M(0x0396, 1);
        opROR_M(0x0397, 1);
    }
    while (true) {
    L_002E5E:
        a = myMapper->readCPU(0x039A);
        opAND(0xF0);
        if (!flgZ) {
            goto L_002E6C;
        }
        a = myMapper->readCPU(0x0397);
        opAND(0xF0);
        if (flgZ) {
            goto L_002E75;
        }
    L_002E6C:
        opLSR_M(0x039A, 1);
        opLSR_M(0x0397, 1);
    }
L_002E75:
    a = myMapper->readCPU(0x039A);
    opASL_A(4);
    flgC = false;
    opADC(myMapper->readCPU(0x0397));
    y = a;
    a = myMapper->readCPU(0xB1FB + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0086));
    opAND(0x0F);
    y = myMapper->readCPU(0x0087);
    popAddress();
}

void game::SUB_002E8C() {
    myMapper->writeCPU(0x008B, myMapper->readCPU(0x0399));
    myMapper->writeCPU(0x008A, myMapper->readCPU(0x039A));
    myMapper->writeCPU(0x0399, myMapper->readCPU(0x0396));
    myMapper->writeCPU(0x039A, myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x0396, myMapper->readCPU(0x008B));
    myMapper->writeCPU(0x0397, myMapper->readCPU(0x008A));
    popAddress();
}

void game::SUB_002EAD() {
    a = myMapper->readCPU(0x0396);
    flgC = false;
    opADC(myMapper->readCPU(0x0390));
    if (a == 0x07) {
        if (myMapper->readCPU(0x0396) != 0) {
            goto L_002EC5;
        }
        myMapper->writeCPU(0x0390, 0xFF);
        goto L_002ECF;
    L_002EC5:
        if (myMapper->readCPU(0x0390) == 0) {
            myMapper->writeCPU(0x0396, 0xFF);
        }
    }
L_002ECF:
    a = myMapper->readCPU(0x0399);
    flgC = false;
    opADC(myMapper->readCPU(0x0393));
    if (a == 0x07) {
        if (myMapper->readCPU(0x0399) != 0) {
            goto L_002EE5;
        }
        myMapper->writeCPU(0x0393, 0xFF);
        popAddress();
        return;
    L_002EE5:
        if (myMapper->readCPU(0x0393) != 0) {
            goto L_002EEF;
        }
        myMapper->writeCPU(0x0399, 0xFF);
    }
L_002EEF:
    popAddress();
}

void game::SUB_002EF0() {
    myMapper->writeCPU(0x038C, y);
    a = myMapper->readCPU(0x0086);
    opAND(0x0F);
    opASL_A(2);
    y = a;
    pushAddress(0x002EFA);
    SUB_002F55();
    if (poppedEntry.value != 0x002EFA) return;
    opADC(myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x0397, a);
    a = myMapper->readCPU(0x038B);
    opADC(myMapper->readCPU(0x0396));
    opAND(0x01);
    myMapper->writeCPU(0x0396, a);
    pushAddress(0x002F0E);
    SUB_002F55();
    if (poppedEntry.value != 0x002F0E) return;
    opADC(myMapper->readCPU(0x039A));
    myMapper->writeCPU(0x039A, a);
    a = myMapper->readCPU(0x038B);
    opADC(myMapper->readCPU(0x0399));
    opCMP(a, myMapper->readCPU(0x0399));
    myMapper->writeCPU(0x0399, a);
    if (flgZ) {
        a = myMapper->readCPU(0x039A);
        if (a < 0xF0) {
            goto L_002F46;
        }
        flgC = false;
        opADC(0x10);
        opINC(0x0399, 1);
    }
    else {
        if (flgC) {
            goto L_002F40;
        }
        a = myMapper->readCPU(0x039A);
        flgC = true;
        opSBC(0x10);
        goto L_002F46;
    L_002F40:
        a = myMapper->readCPU(0x039A);
        flgC = false;
        opADC(0x10);
    }
L_002F46:
    myMapper->writeCPU(0x039A, a);
    a = myMapper->readCPU(0x0399);
    opAND(0x01);
    myMapper->writeCPU(0x0399, a);
    y = myMapper->readCPU(0x038C);
    popAddress();
}

void game::SUB_002F55() {
    myMapper->writeCPU(0x008A, myMapper->readCPU(0xB33B + y));
    opINY(1);
    myMapper->writeCPU(0x038B, 0x00);
    a = myMapper->readCPU(0xB33B + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x008B, a);
    if (!flgN) {
        goto L_002F6C;
    }
    myMapper->writeCPU(0x038B, 0xFF);
L_002F6C:
    opINY(1);
    a = myMapper->readCPU(0x0085);
    opPHA();
    pushAddress(0x002F70);
    SUB_002855();
    if (poppedEntry.value != 0x002F70) return;
    opPLA();
    myMapper->writeCPU(0x0085, a);
    a = myMapper->readCPU(0x008B);
    flgC = false;
    popAddress();
}

void game::SUB_002F7A() {
    myMapper->writeCPU(0x0086, a);
    myMapper->writeCPU(0x0087, y);
    a = 0xB2;
    y = 0xFB;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, y);
    a = myMapper->readCPU(0x050B + x);
    opASL_A(2);
    y = a;
    a = 0x00;
    myMapper->writeCPU(0x0399, a);
    myMapper->writeCPU(0x0396, a);
    myMapper->writeCPU(0x039B, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x039A, a);
    if (flgN) {
        myMapper->writeCPU(0x0399, 0xFF);
    }
    opINY(1);
    myMapper->writeCPU(0x0398, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    myMapper->writeCPU(0x0397, a);
    if (!flgN) {
        goto L_002FB9;
    }
    myMapper->writeCPU(0x0396, 0xFF);
L_002FB9:
    myMapper->writeCPU(0x0732, myMapper->readCPU(0x039B));
    myMapper->writeCPU(0x0731, myMapper->readCPU(0x039A));
    myMapper->writeCPU(0x0733, myMapper->readCPU(0x0399));
    myMapper->writeCPU(0x0734, myMapper->readCPU(0x0398));
    myMapper->writeCPU(0x038C, myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x038B, myMapper->readCPU(0x0396));
    a = 0x00;
    myMapper->writeCPU(0x039B, a);
    myMapper->writeCPU(0x039A, a);
    myMapper->writeCPU(0x0399, a);
    myMapper->writeCPU(0x0398, a);
    myMapper->writeCPU(0x0397, a);
    myMapper->writeCPU(0x0396, a);
    do {
        flgC = false;
        a = myMapper->readCPU(0x0732);
        opADC(myMapper->readCPU(0x039B));
        myMapper->writeCPU(0x039B, a);
        a = myMapper->readCPU(0x0731);
        opADC(myMapper->readCPU(0x039A));
        myMapper->writeCPU(0x039A, a);
        a = myMapper->readCPU(0x0733);
        opADC(myMapper->readCPU(0x0399));
        myMapper->writeCPU(0x0399, a);
        flgC = false;
        a = myMapper->readCPU(0x0734);
        opADC(myMapper->readCPU(0x0398));
        myMapper->writeCPU(0x0398, a);
        a = myMapper->readCPU(0x038C);
        opADC(myMapper->readCPU(0x0397));
        myMapper->writeCPU(0x0397, a);
        a = myMapper->readCPU(0x038B);
        opADC(myMapper->readCPU(0x0396));
        myMapper->writeCPU(0x0396, a);
        opDEC(0x0086, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003048() {
    pushAddress(0x003048);
    SUB_002F7A();
    if (poppedEntry.value != 0x003048) return;
    flgC = false;
    a = myMapper->readCPU(0x039B);
    opADC(myMapper->readCPU(0x0556 + x));
    myMapper->writeCPU(0x0556 + x, a);
    a = myMapper->readCPU(0x039A);
    opADC(myMapper->readCPU(0x053D + x));
    myMapper->writeCPU(0x053D + x, a);
    a = myMapper->readCPU(0x0399);
    opADC(myMapper->readCPU(0x0524 + x));
    myMapper->writeCPU(0x0399, a);
    if (a != myMapper->readCPU(0x0524 + x)) {
        flgC = true;
        a = myMapper->readCPU(0x053D + x);
        opSBC(0x10);
        myMapper->writeCPU(0x053D + x, a);
    }
    else {
        a = myMapper->readCPU(0x053D + x);
        opCMP(a, 0xF0);
        if (!flgC) {
            goto L_003087;
        }
        opADC(0x10);
        myMapper->writeCPU(0x053D + x, a);
        opINC(0x0399, 1);
    }
L_003087:
    a = myMapper->readCPU(0x0399);
    opAND(0x01);
    myMapper->writeCPU(0x0524 + x, a);
    a = myMapper->readCPU(0x0398);
    flgC = false;
    opADC(myMapper->readCPU(0x05A1 + x));
    myMapper->writeCPU(0x05A1 + x, a);
    a = myMapper->readCPU(0x0397);
    opADC(myMapper->readCPU(0x0588 + x));
    myMapper->writeCPU(0x0588 + x, a);
    a = myMapper->readCPU(0x0396);
    opADC(myMapper->readCPU(0x056F + x));
    opAND(0x01);
    myMapper->writeCPU(0x056F + x, a);
    y = myMapper->readCPU(0x0087);
    popAddress();
}

void game::SUB_0030BC() {
    myMapper->writeCPU(0x0391, myMapper->readCPU(0x0588 + x));
    a = myMapper->readCPU(0x056F + x);
    opAND(0x01);
    myMapper->writeCPU(0x0390, a);
    myMapper->writeCPU(0x0394, myMapper->readCPU(0x053D + x));
    a = myMapper->readCPU(0x0524 + x);
    opAND(0x01);
    myMapper->writeCPU(0x0393, a);
    popAddress();
}

void game::SUB_0030E5() {
    myMapper->writeCPU(0x0397, myMapper->readCPU(0x0588 + y));
    a = myMapper->readCPU(0x056F + y);
    opAND(0x01);
    myMapper->writeCPU(0x0396, a);
    myMapper->writeCPU(0x039A, myMapper->readCPU(0x053D + y));
    a = myMapper->readCPU(0x0524 + y);
    opAND(0x01);
    myMapper->writeCPU(0x0399, a);
    popAddress();
}

void game::SUB_003102() {
    myMapper->writeCPU(0x0397, myMapper->readCPU(0x061E + x));
    a = myMapper->readCPU(0x0605 + x);
    opAND(0x01);
    myMapper->writeCPU(0x0396, a);
    myMapper->writeCPU(0x039A, myMapper->readCPU(0x0650 + x));
    a = myMapper->readCPU(0x0637 + x);
    opAND(0x01);
    myMapper->writeCPU(0x0399, a);
    popAddress();
}

void game::SUB_00311F() {
    pushAddress(0x00311F);
    SUB_00312B();
    if (poppedEntry.value != 0x00311F) return;
    SUB_003148();
    return;
}

void game::SUB_00312B() {
    flgC = true;
    if (flgC) {
        goto L_003135;
    }
    flgC = true;
    a = myMapper->readCPU(0x0392);
    opSBC(myMapper->readCPU(0x0398));
L_003135:
    a = myMapper->readCPU(0x0391);
    opSBC(myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x0397, a);
    a = myMapper->readCPU(0x0390);
    opSBC(myMapper->readCPU(0x0396));
    myMapper->writeCPU(0x0396, a);
    popAddress();
}

void game::SUB_003148() {
    flgC = true;
    if (flgC) {
        goto L_003152;
    }
    flgC = true;
    a = myMapper->readCPU(0x0395);
    opSBC(myMapper->readCPU(0x039B));
L_003152:
    a = myMapper->readCPU(0x0394);
    opSBC(myMapper->readCPU(0x039A));
    myMapper->writeCPU(0x039A, a);
    a = myMapper->readCPU(0x0393);
    opSBC(myMapper->readCPU(0x0399));
    myMapper->writeCPU(0x0399, a);
    popAddress();
}

void game::SUB_00316F() {
    myMapper->writeCPU(0x0397, 0x80);
    a = 0x00;
    opAND(0x01);
    myMapper->writeCPU(0x0396, a);
    myMapper->writeCPU(0x039A, 0x70);
    a = 0x00;
    opAND(0x01);
    myMapper->writeCPU(0x0399, a);
    popAddress();
}

void game::SUB_0031D7() {
    pushAddress(0x0031D7);
    SUB_0030BC();
    if (poppedEntry.value != 0x0031D7) return;
    pushAddress(0x0031DA);
    SUB_00316F();
    if (poppedEntry.value != 0x0031DA) return;
    pushAddress(0x0031DD);
    SUB_00311F();
    if (poppedEntry.value != 0x0031DD) return;
    if (myMapper->readCPU(0x0524 + x) == 0) {
        goto L_0031EE;
    }
    a = myMapper->readCPU(0x039A);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x039A, a);
L_0031EE:
    myMapper->writeCPU(0x04A7 + x, myMapper->readCPU(0x039A));
    myMapper->writeCPU(0x04C0 + x, myMapper->readCPU(0x0397));
    popAddress();
}

void game::SUB_00337B() {
    if (myMapper->readCPU(0x056F + x) == 0) {
        goto L_00338E;
    }
    a = myMapper->readCPU(0x0588 + x);
    if (a >= 0xC1) {
        goto L_0033C9;
    }
    if (a >= 0x81) {
        goto L_0033C0;
    }
    goto L_003399;
L_00338E:
    a = myMapper->readCPU(0x0588 + x);
    if (a < 0x40) {
        goto L_0033C9;
    }
    if (a < 0x80) {
        goto L_0033C0;
    }
L_003399:
    if (myMapper->readCPU(0x0524 + x) == 0) {
        goto L_0033AC;
    }
    a = myMapper->readCPU(0x053D + x);
    if (a >= 0xB1) {
        goto L_0033C9;
    }
    if (a >= 0x71) {
        goto L_0033C0;
    }
    goto L_0033B7;
L_0033AC:
    a = myMapper->readCPU(0x053D + x);
    if (a < 0x30) {
        goto L_0033C9;
    }
    if (a < 0x70) {
        goto L_0033C0;
    }
L_0033B7:
    a = myMapper->readCPU(0x048E + x);
    opORA(0x80);
    myMapper->writeCPU(0x048E + x, a);
    popAddress();
    return;
L_0033C0:
    a = myMapper->readCPU(0x048E + x);
    opAND(0x7F);
    myMapper->writeCPU(0x048E + x, a);
    popAddress();
    return;
L_0033C9:
    myMapper->writeCPU(0x048E + x, 0x00);
    popAddress();
}

void game::SUB_0033CF() {
    a = myMapper->readCPU(0x048E + x);
    opAND(0x01);
    popAddress();
}

void game::SUB_0033D5() {
    x = 0x0B;
    a = myMapper->readCPU(0x0380);
    if (a != 0xFF) {
        x = 0x0B;
        SUB_0033E3();
        SUB_0033E8();
        return;
    }
    SUB_0034F9();
    return;
}

void game::SUB_0033E3() {
    a = myMapper->readCPU(0x048E + x);
    setLoadFlag(a);
    if (flgN) {
        SUB_0033F3();
    }
}

void game::SUB_0033E8() {
    while (true) {
        opINX(1);
        if (x >= 0x0E) {
            pushAddress(0x0033ED);
            SUB_004275();
            if (poppedEntry.value != 0x0033ED) return;
            x = 0x0B;
        }
        a = myMapper->readCPU(0x048E + x);
        setLoadFlag(a);
        if (flgN) {
            SUB_0033F3_B();
        }
    }
}

void game::SUB_0033F3_B() {
    opAND(0x20);
    if (flgZ) {
        goto L_0033FA;
    }
    SUB_0034E0();
    return;
L_0033FA:
    pushAddress(0x0033FA);
    SUB_00340A();
    if (poppedEntry.value != 0x0033FA) return;
    if (flgC) {
        myMapper->writeCPU(0x048E + x, 0x00);
    }
}

void game::SUB_0033F3() {
    SUB_0033F3_B();
    SUB_0033E8();
}

void game::SUB_00340A() {
    a = 0x34;
    pushAddress(0x00340C);
    SUB_003048();
    if (poppedEntry.value != 0x00340C) return;
    pushAddress(0x00340F);
    SUB_0031D7();
    if (poppedEntry.value != 0x00340F) return;
    pushAddress(0x003412);
    SUB_00337B();
    if (poppedEntry.value != 0x003412) return;
    a = myMapper->readCPU(0x048E + x);
    opAND(0x08);
    if (flgZ) {
        goto L_003457;
    }
    a = myMapper->readCPU(0x048E + x);
    opAND(0x80);
    if (flgZ) {
        goto L_003457;
    }
    if (myMapper->readCPU(0x078C) != 0) {
        goto L_003455;
    }
    y = 0x0E;
    do {
        a = myMapper->readCPU(0x048E + y);
        setLoadFlag(a);
        if (!flgN) {
        }
        else {
            opAND(0x21);
            if (flgZ) {
                if (y != 0x18) {
                    goto L_003441;
                }
                a = myMapper->readCPU(0x04D9 + y);
                if (a == 0x79) {
                    goto L_003450;
                }
            L_003441:
                a = myMapper->readCPU(0x05D3 + y);
                if (a < 0xFF) {
                    goto L_00344B;
                }
                goto L_0034C5;
            L_00344B:
                pushAddress(0x00344B);
                SUB_002A61();
                if (poppedEntry.value != 0x00344B) return;
                if (flgC) {
                    goto L_003459;
                }
            }
        }
    L_003450:
        opINY(1);
    } while (y < 0x19);
    while (true) {
        while (true) {
        L_003455:
            flgC = false;
            popAddress();
            return;
            while (true) {
            L_003457:
                flgC = true;
                popAddress();
                return;
            L_003459:
                a = myMapper->readCPU(0x05D3 + y);
                if (a >= 0x20) {
                    goto L_00346B;
                }
            L_003460:
                a = myMapper->readCPU(0x048E + y);
                opORA(0x01);
                myMapper->writeCPU(0x048E + y, a);
            }
        L_00346B:
            a = myMapper->readCPU(0x05EC + y);
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x05EC + y, a);
            a = myMapper->readCPU(0x05D3 + y);
            if (a < 0xFF) {
                if (a >= 0x30) {
                    goto L_003489;
                }
                a = myMapper->readCPU(0x05EC + y);
                if (a >= 0x05) {
                    goto L_003460;
                }
                goto L_0034B0;
            L_003489:
                a = myMapper->readCPU(0x05EC + y);
                if (a >= 0x0A) {
                    goto L_003460;
                }
                goto L_0034B0;
            }
            myMapper->writeCPU(0x0086, myMapper->readCPU(0x05EC + y));
            myMapper->writeCPU(0x0087, y);
            a = 0x00;
            flgC = true;
            opSBC(myMapper->readCPU(0x03A1));
            opLSR_A(6);
            y = a;
            a = myMapper->readCPU(0xB4DC + y);
            y = myMapper->readCPU(0x0087);
            if (a < myMapper->readCPU(0x0086)) {
                goto L_003460;
            }
        L_0034B0:
            a = myMapper->readCPU(0x048E + x);
            opORA(0x20);
            myMapper->writeCPU(0x048E + x, a);
            myMapper->writeCPU(0x069B + x, 0xFF);
            myMapper->writeCPU(0x04F2 + x, 0x01);
        }
    L_0034C5:
        myMapper->writeCPU(0x04D9 + y, 0x8E);
        pushAddress(0x0034CA);
        SUB_002A61();
        if (poppedEntry.value != 0x0034CA) return;
        if (flgC) {
            goto L_003459;
        }
        myMapper->writeCPU(0x04D9 + y, 0x8F);
        pushAddress(0x0034D4);
        SUB_002A61();
        if (poppedEntry.value != 0x0034D4) return;
        if (flgC) {
            goto L_003459;
        }
    }
    SUB_0034E0();
    return;
}

void game::SUB_0034E0() {
    opINC(0x069B + x, 1);
    a = myMapper->readCPU(0x069B + x);
    opLSR_A(1);
    opAND(0x0F);
    if (a >= 0x02) {
        myMapper->writeCPU(0x048E + x, 0x00);
    }
    else {
        flgC = false;
        opADC(0x80);
        myMapper->writeCPU(0x04D9 + x, a);
    }
    SUB_0033E8();
}

void game::SUB_0034F9() {
    myMapper->writeCPU(0x048E + x, 0x88);
    myMapper->writeCPU(0x04D9 + x, 0x01);
    while (true) {
        pushAddress(0x003503);
        SUB_004275();
        if (poppedEntry.value != 0x003503) return;
    }
}

void game::SUB_003509() {
    while (true) {
        x = 0x03;
        do {
            if (myMapper->readCPU(0x048E + x) & 0x80) {
                goto L_00351B;
            }
        L_003510:
            opINX(1);
        } while (x != 0x0B);
        pushAddress(0x003515);
        SUB_004275();
        if (poppedEntry.value != 0x003515) return;
    }
L_00351B:
    myMapper->writeCPU(0x04D9 + x, 0x07);
    pushAddress(0x003520);
    SUB_003533();
    if (poppedEntry.value != 0x003520) return;
    if (flgC) {
        goto L_003528;
    }
    goto L_003510;
L_003528:
    myMapper->writeCPU(0x048E + x, 0x00);
    goto L_003510;
}

void game::SUB_003533() {
    a = 0x13;
    pushAddress(0x003535);
    SUB_003048();
    if (poppedEntry.value != 0x003535) return;
    pushAddress(0x003538);
    SUB_0031D7();
    if (poppedEntry.value != 0x003538) return;
    pushAddress(0x00353B);
    SUB_00337B();
    if (poppedEntry.value != 0x00353B) return;
    a = myMapper->readCPU(0x048E + x);
    opAND(0x08);
    if (!flgZ) {
        a = myMapper->readCPU(0x048E + x);
        opAND(0x80);
        if (flgZ) {
            goto L_00357B;
        }
        y = 0x00;
        do {
            if (myMapper->readCPU(0x048E + y) & 0x80) {
                goto L_003556;
            }
            goto L_003574;
        L_003556:
            if (y == 0x00) {
                goto L_003568;
            }
            a = myMapper->readCPU(0x048E + y);
            opAND(0x08);
            if (flgZ) {
                goto L_003574;
            }
            a = myMapper->readCPU(0x048E + y);
            opAND(0x04);
            if (!flgZ) {
                goto L_003574;
            }
        L_003568:
            a = myMapper->readCPU(0x048E + y);
            opAND(0x10);
            if (!flgZ) {
                goto L_003579;
            }
            pushAddress(0x00356F);
            SUB_002A61();
            if (poppedEntry.value != 0x00356F) return;
            if (flgC) {
                goto L_00357D;
            }
        L_003574:
            opINY(1);
        } while (y != 0x03);
    L_003579:
        flgC = false;
        popAddress();
        return;
    }
    while (true) {
    L_00357B:
        flgC = true;
        popAddress();
        return;
    L_00357D:
        a = myMapper->readCPU(0x048E + y);
        opORA(0x01);
        myMapper->writeCPU(0x048E + y, a);
    }
}

void game::SUB_003588() {
    x = 0x18;
    myMapper->writeCPU(0x048E + x, 0x0A);
    a = myMapper->readCPU(0x071F);
    opAND(0x01);
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x056F + x, myMapper->readCPU(0xB657 + y));
    opINY(1);
    myMapper->writeCPU(0x0588 + x, myMapper->readCPU(0xB657 + y));
    opINY(1);
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(0xB657 + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(0xB657 + y));
    myMapper->writeCPU(0x04F2 + x, 0x02);
    myMapper->writeCPU(0x05BA + x, 0x01);
    myMapper->writeCPU(0x050B + x, 0x00);
    myMapper->writeCPU(0x04D9 + x, 0x10);
    myMapper->writeCPU(0x069B + x, 0xFF);
    do {
        pushAddress(0x0035CB);
        SUB_004275();
        if (poppedEntry.value != 0x0035CB) return;
        pushAddress(0x0035CE);
        SUB_0077CD();
        if (poppedEntry.value != 0x0035CE) return;
    } while (flgZ);
    while (true) {
        a = myMapper->readCPU(0x048E + x);
        opAND(0x01);
        if (!flgZ) {
            goto L_003612;
        }
        opINC(0x069B + x, 1);
        a = myMapper->readCPU(0x069B + x);
        opAND(0x03);
        if (flgZ) {
            opINC(0x05BA + x, 1);
        }
        pushAddress(0x0035E7);
        SUB_0077CD();
        if (poppedEntry.value != 0x0035E7) return;
        if (flgZ) {
            goto L_003654;
        }
        y = 0x00;
        pushAddress(0x0035EE);
        SUB_002A61();
        if (poppedEntry.value != 0x0035EE) return;
        if (!flgC) {
            y = 0x01;
            pushAddress(0x0035F5);
            SUB_002A61();
            if (poppedEntry.value != 0x0035F5) return;
            if (flgC) {
                goto L_003601;
            }
            y = 0x02;
            pushAddress(0x0035FC);
            SUB_002A61();
            if (poppedEntry.value != 0x0035FC) return;
            if (!flgC) {
                goto L_00360C;
            }
        }
    L_003601:
        a = myMapper->readCPU(0x048E + y);
        opORA(0x01);
        myMapper->writeCPU(0x048E + y, a);
        SUB_00783C();
        return;
    L_00360C:
        pushAddress(0x00360C);
        SUB_004275();
        if (poppedEntry.value != 0x00360C) return;
    }
L_003612:
    myMapper->writeCPU(0x06B4 + x, 0x20);
    myMapper->writeCPU(0x05D3 + x, 0x02);
    pushAddress(0x00361C);
    SUB_00719C();
    if (poppedEntry.value != 0x00361C) return;
    myMapper->writeCPU(0x04D9 + x, 0x79);
    myMapper->writeCPU(0x04F2 + x, 0x01);
    myMapper->writeCPU(0x05BA + x, 0x04);
    myMapper->writeCPU(0x050B + x, 0x08);
    while (true) {
        pushAddress(0x003633);
        SUB_0077CD();
        if (poppedEntry.value != 0x003633) return;
        if (flgZ) {
            goto L_003654;
        }
        y = 0x00;
        pushAddress(0x00363A);
        SUB_002A61();
        if (poppedEntry.value != 0x00363A) return;
        if (flgC) {
            goto L_003645;
        }
        pushAddress(0x00363F);
        SUB_004275();
        if (poppedEntry.value != 0x00363F) return;
    }
L_003645:
    a = 0x0F;
    pushAddress(0x003647);
    SUB_00206B();
    if (poppedEntry.value != 0x003647) return;
    a = 0x09;
    pushAddress(0x00364C);
    SUB_0079E1();
    if (poppedEntry.value != 0x00364C) return;
    myMapper->writeCPU(0x048E + x, 0x00);
L_003654:
    pushAddress(0x003654);
    SUB_004237();
    if (poppedEntry.value != 0x003654) return;
    pushAddress(0x003657);
    flgB = true;
    pushStatus();
    reset();
    popStatus();
    flgB = false;
    popAddress();
    opORA(myMapper->readCPU(myMapper->readCPU((0x00A0 + x) & 0x00ff) + (myMapper->readCPU((0x00A0 + x + 1) & 0x00ff) << 8)));
    opORA(myMapper->readCPU(myMapper->readCPU((0x0060 + x) & 0x00ff) + (myMapper->readCPU((0x0060 + x + 1) & 0x00ff) << 8)));
    opORA(myMapper->readCPU(myMapper->readCPU((0x00A0 + x) & 0x00ff) + (myMapper->readCPU((0x00A0 + x + 1) & 0x00ff) << 8)));
    SUB_00365F();
    return;
}

void game::SUB_00365F() {
    a = 0x00;
    myMapper->writeCPU(0x0382, a);
    myMapper->writeCPU(0x07BC, a);
    pushAddress(0x003667);
    SUB_006240();
    if (poppedEntry.value != 0x003667) return;
    myMapper->writeCPU(0x0723, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x006E, a);
    myMapper->writeCPU(0x006D, a);
    myMapper->writeCPU(0x078F, a);
    myMapper->writeCPU(0x07BB, a);
    myMapper->writeCPU(0x006B, 0x8F);
    myMapper->writeCPU(0x006C, 0x07);
    a = myMapper->readCPU(0x008C);
    opAND(0xFD);
    myMapper->writeCPU(0x008C, a);
    a = 0x00;
    myMapper->writeCPU(0x008F, a);
    myMapper->writeCPU(0x0090, a);
    a = 0x00;
    myMapper->writeCPU(0x0723, a);
    pushAddress(0x003694);
    SUB_002094();
    if (poppedEntry.value != 0x003694) return;
    pushAddress(0x003697);
    SUB_00396C();
    if (poppedEntry.value != 0x003697) return;
    pushAddress(0x00369A);
    SUB_00393D();
    if (poppedEntry.value != 0x00369A) return;
    pushAddress(0x00369D);
    SUB_003A12();
    if (poppedEntry.value != 0x00369D) return;
    myMapper->writeCPU(0x0385, 0x00);
    myMapper->writeCPU(0x0380, 0xFF);
    y = 0x0B;
    myMapper->writeCPU(0x04C0 + y, 0x48);
    myMapper->writeCPU(0x04A7 + y, 0x7F);
    myMapper->writeCPU(0x04D9 + y, 0x20);
    a = 0x1A;
    pushAddress(0x0036BD);
    SUB_0041F5();
    if (poppedEntry.value != 0x0036BD) return;
    myMapper->writeCPU(0x070B, 0xFF);
L_0036C5:
    pushAddress(0x0036C5);
    SUB_004275();
    if (poppedEntry.value != 0x0036C5) return;
    a = myMapper->readCPU(0x0098);
    opAND(0x20);
    if (flgZ) {
        goto L_003717;
    }
    if (myMapper->readCPU(0x0382) != 0) {
        goto L_003724;
    }
    while (true) {
        myMapper->writeCPU(0x0382, 0xFF);
        myMapper->writeCPU(0x07BC, 0x00);
        opINC(0x07BB, 1);
        a = myMapper->readCPU(0x07BB);
        opAND(0x03);
        myMapper->writeCPU(0x07BB, a);
        if (a != 0x03) {
            if (a != 0x02) {
                goto L_003702;
            }
            if (myMapper->readCPU(0x07C5) == 0) {
                goto L_00370A;
            }
            myMapper->writeCPU(0x07BC, 0xFF);
            myMapper->writeCPU(0x04B2, 0x9F);
            goto L_003731;
        L_003702:
            myMapper->writeCPU(0x04B2, 0x8F);
            goto L_003731;
        }
    L_00370A:
        myMapper->writeCPU(0x07BB, 0x00);
        myMapper->writeCPU(0x04B2, 0x7F);
        goto L_003731;
    L_003717:
        myMapper->writeCPU(0x0382, 0x00);
        myMapper->writeCPU(0x070A, 0x14);
        goto L_003731;
    L_003724:
        opDEC(0x070A, 1);
        if (!flgZ) {
            goto L_003731;
        }
        myMapper->writeCPU(0x070A, 0x14);
    }
L_003731:
    a = myMapper->readCPU(0x0098);
    opAND(0x10);
    if (!flgZ) {
        if (myMapper->readCPU(0x0388) != 0) {
            goto L_003744;
        }
    }
    else {
        myMapper->writeCPU(0x0388, 0x00);
    L_003744:
        opDEC(0x070B, 1);
        a = myMapper->readCPU(0x070B);
        opAND(0x03);
        if (flgZ) {
            y = 0x04;
            do {
                a = myMapper->readCPU(0x032A + y);
                opEOR(0xFF);
                myMapper->writeCPU(0x032A + y, a);
                opDEY(1);
            } while (!flgN);
        }
        goto L_0036C5;
    }
    a = 0x00;
    myMapper->writeCPU(0x0385, a);
    myMapper->writeCPU(0x0380, a);
    myMapper->writeCPU(0x0384, a);
    pushAddress(0x003769);
    SUB_004306();
    if (poppedEntry.value != 0x003769) return;
    if (myMapper->readCPU(0x07BC) != 0) {
        goto L_003777;
    }
    myMapper->writeCPU(0x0381, myMapper->readCPU(0x07BB));
L_003777:
    a = 0x04;
    pushAddress(0x003779);
    SUB_0041F5();
    if (poppedEntry.value != 0x003779) return;
    pushAddress(0x00377C);
    SUB_004237();
    if (poppedEntry.value != 0x00377C) return;
    //NOP
    createThread(0x37C3);
    //SUB_0037C3();
    return;
}



void game::SUB_0037C3() {
    if (myMapper->readCPU(0x07BC) != 0) {
        goto L_0037D5;
    }
    pushAddress(0x0037C8);
    SUB_0039E5();
    if (poppedEntry.value != 0x0037C8) return;
    myMapper->writeCPU(0x03A1, 0x01);
    myMapper->writeCPU(0x03A0, 0x00);
L_0037D5:
    pushAddress(0x0037D5);
    SUB_001FDB();
    if (poppedEntry.value != 0x0037D5) return;
    myMapper->writeCPU(0x0385, 0xFF);
    myMapper->writeCPU(0x0432, 0x02);
    a = 0x00;
    myMapper->writeCPU(0x048C, a);
    myMapper->writeCPU(0x0386, a);
    myMapper->writeCPU(0x00C9, a);
    myMapper->writeCPU(0x042E, a);
    myMapper->writeCPU(0x038D, a);
    y = 0x11;
    do {
        myMapper->writeCPU(0x0437 + y, a);
        opDEY(1);
    } while (!flgN);
    pushAddress(0x0037FA);
    SUB_003922();
    if (poppedEntry.value != 0x0037FA) return;
    if (myMapper->readCPU(0x0384) == 0) {
        if (myMapper->readCPU(0x0381) != 0) {
            goto L_003842;
        }
    }
    while (true) {
        while (true) {
            pushAddress(0x003807);
            SUB_0057A1();
            if (poppedEntry.value != 0x003807) return;
            if (myMapper->readCPU(0x0384) != 0) {
                goto L_00382A;
            }
            if (myMapper->readCPU(0x0432) != 0) {
                goto L_003824;
            }
            if (myMapper->readCPU(0x0431) == 0) {
                goto L_00382A;
            }
            opDEC(0x0431, 1);
            myMapper->writeCPU(0x0432, 0x09);
        }
    L_003824:
        opDEC(0x0432, 1);
    }
L_00382A:
    pushAddress(0x00382A);
    SUB_003D3A();
    if (poppedEntry.value != 0x00382A) return;
    if (myMapper->readCPU(0x0384) == 0) {
        goto L_00383A;
    }
    myMapper->writeCPU(0x0383, 0xFF);
    pushAddress(0x003837);
    SUB_004237();
    if (poppedEntry.value != 0x003837) return;
    while (true) {
    L_00383A:
        a = 0x02;
        pushAddress(0x00383C);
        SUB_0041F5();
        if (poppedEntry.value != 0x00383C) return;
        pushAddress(0x00383F);
        SUB_004237();
        if (poppedEntry.value != 0x00383F) return;
    L_003842:
        if (myMapper->readCPU(0x07BC) != 0) {
            pushAddress(0x003847);
            SUB_003F7F();
            if (poppedEntry.value != 0x003847) return;
            myMapper->writeCPU(0x0432, 0x02);
        }
        pushAddress(0x00384F);
        SUB_0057A1();
        if (poppedEntry.value != 0x00384F) return;
        opDEC(0x0432, 1);
        pushAddress(0x003855);
        SUB_003F58();
        if (poppedEntry.value != 0x003855) return;
        myMapper->writeCPU(0x0432, 0x02);
        a = 0x00;
        myMapper->writeCPU(0x042E, a);
        y = 0x11;
        do {
            myMapper->writeCPU(0x0437 + y, a);
            opDEY(1);
        } while (!flgN);
        if (myMapper->readCPU(0x07BC) != 0) {
            goto L_003879;
        }
        myMapper->writeCPU(0x03A1, 0x01);
        myMapper->writeCPU(0x03A0, 0x00);
    L_003879:
        a = 0x00;
        y = 0x11;
        do {
            myMapper->writeCPU(0x0437 + y, a);
            opDEY(1);
        } while (!flgN);
        pushAddress(0x003883);
        SUB_0057A1();
        if (poppedEntry.value != 0x003883) return;
        opDEC(0x0432, 1);
        while (true) {
            while (true) {
                pushAddress(0x003889);
                SUB_003F74();
                if (poppedEntry.value != 0x003889) return;
                pushAddress(0x00388C);
                SUB_0057A1();
                if (poppedEntry.value != 0x00388C) return;
                if (myMapper->readCPU(0x0432) != 0) {
                    goto L_0038A4;
                }
                if (myMapper->readCPU(0x0431) == 0) {
                    goto L_0038C8;
                }
                opDEC(0x0431, 1);
                myMapper->writeCPU(0x0432, 0x09);
                goto L_0038A7;
            L_0038A4:
                opDEC(0x0432, 1);
            L_0038A7:
                pushAddress(0x0038A7);
                SUB_003F58();
                if (poppedEntry.value != 0x0038A7) return;
                pushAddress(0x0038AA);
                SUB_0057A1();
                if (poppedEntry.value != 0x0038AA) return;
                if (myMapper->readCPU(0x0432) != 0) {
                    goto L_0038C2;
                }
                if (myMapper->readCPU(0x0431) == 0) {
                    goto L_0038F2;
                }
                opDEC(0x0431, 1);
                myMapper->writeCPU(0x0432, 0x09);
            }
        L_0038C2:
            opDEC(0x0432, 1);
        }
    L_0038C8:
        pushAddress(0x0038C8);
        SUB_003D3A();
        if (poppedEntry.value != 0x0038C8) return;
        pushAddress(0x0038CB);
        SUB_003F58();
        if (poppedEntry.value != 0x0038CB) return;
        while (true) {
            while (true) {
                pushAddress(0x0038CE);
                SUB_0057A1();
                if (poppedEntry.value != 0x0038CE) return;
                pushAddress(0x0038D1);
                SUB_003F74();
                if (poppedEntry.value != 0x0038D1) return;
                pushAddress(0x0038D4);
                SUB_003F58();
                if (poppedEntry.value != 0x0038D4) return;
                if (myMapper->readCPU(0x0432) != 0) {
                    goto L_0038EC;
                }
                if (myMapper->readCPU(0x0431) == 0) {
                    goto L_00391C;
                }
                opDEC(0x0431, 1);
                myMapper->writeCPU(0x0432, 0x09);
            }
        L_0038EC:
            opDEC(0x0432, 1);
        }
    L_0038F2:
        pushAddress(0x0038F2);
        SUB_003D3A();
        if (poppedEntry.value != 0x0038F2) return;
        pushAddress(0x0038F5);
        SUB_003F74();
        if (poppedEntry.value != 0x0038F5) return;
        while (true) {
            while (true) {
                pushAddress(0x0038F8);
                SUB_0057A1();
                if (poppedEntry.value != 0x0038F8) return;
                pushAddress(0x0038FB);
                SUB_003F58();
                if (poppedEntry.value != 0x0038FB) return;
                pushAddress(0x0038FE);
                SUB_003F74();
                if (poppedEntry.value != 0x0038FE) return;
                if (myMapper->readCPU(0x0432) != 0) {
                    goto L_003916;
                }
                if (myMapper->readCPU(0x0431) == 0) {
                    goto L_00391C;
                }
                opDEC(0x0431, 1);
                myMapper->writeCPU(0x0432, 0x09);
            }
        L_003916:
            opDEC(0x0432, 1);
        }
    L_00391C:
        pushAddress(0x00391C);
        SUB_003D3A();
        if (poppedEntry.value != 0x00391C) return;
    }
}

void game::SUB_003922() {
    a = 0x00;
    y = 0x05;
    do {
        myMapper->writeCPU(0x0427 + y, a);
        opDEY(1);
    } while (!flgN);
    y = 0x05;
    do {
        myMapper->writeCPU(0x044A + y, a);
        opDEY(1);
    } while (!flgN);
    y = 0x05;
    do {
        myMapper->writeCPU(0x046B + y, a);
        opDEY(1);
    } while (!flgN);
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

void game::SUB_0039E5() {
    myMapper->writeCPU(0x008B, 0x04);
    myMapper->writeCPU(0x008A, 0x27);
    myMapper->writeCPU(0x0087, 0x03);
    myMapper->writeCPU(0x0086, 0x68);
    y = 0x00;
    a = myMapper->readCPU(0x0087);
    setLoadFlag(a);
    if (!flgZ) {
        a = 0x00;
        do {
            do {
                myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
                opINY(1);
            } while (!flgZ);
            opINC(0x008B, 1);
            opDEC(0x0087, 1);
        } while (!flgZ);
    }
    y = myMapper->readCPU(0x0086);
    setLoadFlag(y);
    if (flgZ) {
        goto L_003A11;
    }
    do {
        myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, a);
        opDEY(1);
    } while (!flgZ);
L_003A11:
    popAddress();
}

void game::SUB_003A12() {
    myMapper->writeCPU(0x008B, 0xBB);
    myMapper->writeCPU(0x008A, 0x51);
    pushAddress(0x003A1A);
    SUB_00275A();
    if (poppedEntry.value != 0x003A1A) return;
    y = 0x3F;
    do {
        myMapper->writeCPU(0x0300 + y, myMapper->readCPU(0xBB71 + y));
        opDEY(1);
    } while (!flgN);
    y = 0x3F;
    do {
        myMapper->writeCPU(0x0340 + y, myMapper->readCPU(0xBB71 + y));
        opDEY(1);
    } while (!flgN);
    myMapper->writeCPU(0x008B, 0xBB);
    myMapper->writeCPU(0x008A, 0x71);
    myMapper->writeCPU(0x0089, 0x23);
    myMapper->writeCPU(0x0088, 0xC0);
    myMapper->writeCPU(0x0087, 0x40);
    pushAddress(0x003A47);
    SUB_00001B();
    if (poppedEntry.value != 0x003A47) return;
    myMapper->writeCPU(0x008B, 0xBB);
    myMapper->writeCPU(0x008A, 0xB1);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x45);
    myMapper->writeCPU(0x0087, 0x03);
    pushAddress(0x003A5E);
    SUB_00001B();
    if (poppedEntry.value != 0x003A5E) return;
    myMapper->writeCPU(0x008B, 0x04);
    myMapper->writeCPU(0x008A, 0x4A);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x63);
    myMapper->writeCPU(0x0087, 0x06);
    pushAddress(0x003A75);
    SUB_00001B();
    if (poppedEntry.value != 0x003A75) return;
    myMapper->writeCPU(0x008B, 0xBB);
    myMapper->writeCPU(0x008A, 0xB7);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x4C);
    myMapper->writeCPU(0x0087, 0x08);
    pushAddress(0x003A8C);
    SUB_00001B();
    if (poppedEntry.value != 0x003A8C) return;
    myMapper->writeCPU(0x008B, 0x07);
    myMapper->writeCPU(0x008A, 0xBF);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x6D);
    myMapper->writeCPU(0x0087, 0x06);
    pushAddress(0x003AA3);
    SUB_00001B();
    if (poppedEntry.value != 0x003AA3) return;
    if (myMapper->readCPU(0x0381) != 0) {
        myMapper->writeCPU(0x008B, 0xBB);
        myMapper->writeCPU(0x008A, 0xB4);
        myMapper->writeCPU(0x0089, 0x20);
        myMapper->writeCPU(0x0088, 0x59);
        myMapper->writeCPU(0x0087, 0x03);
        pushAddress(0x003ABF);
        SUB_00001B();
        if (poppedEntry.value != 0x003ABF) return;
        myMapper->writeCPU(0x008B, 0x04);
        myMapper->writeCPU(0x008A, 0x6B);
        myMapper->writeCPU(0x0089, 0x20);
        myMapper->writeCPU(0x0088, 0x77);
        myMapper->writeCPU(0x0087, 0x06);
        pushAddress(0x003AD6);
        SUB_00001B();
        if (poppedEntry.value != 0x003AD6) return;
    }
    myMapper->writeCPU(0x008B, 0xBB);
    myMapper->writeCPU(0x008A, 0xBF);
    myMapper->writeCPU(0x0087, 0xA0);
    myMapper->writeCPU(0x0089, 0x21);
    myMapper->writeCPU(0x0088, 0x00);
    pushAddress(0x003AED);
    SUB_00001B();
    if (poppedEntry.value != 0x003AED) return;
    myMapper->writeCPU(0x008B, 0xBC);
    myMapper->writeCPU(0x008A, 0x5F);
    myMapper->writeCPU(0x0089, 0x22);
    myMapper->writeCPU(0x0088, 0x0B);
    myMapper->writeCPU(0x0087, 0x09);
    pushAddress(0x003B04);
    SUB_00001B();
    if (poppedEntry.value != 0x003B04) return;
    myMapper->writeCPU(0x008B, 0xBC);
    myMapper->writeCPU(0x008A, 0x68);
    myMapper->writeCPU(0x0089, 0x22);
    myMapper->writeCPU(0x0088, 0x4B);
    myMapper->writeCPU(0x0087, 0x09);
    pushAddress(0x003B1B);
    SUB_00001B();
    if (poppedEntry.value != 0x003B1B) return;
    if (myMapper->readCPU(0x07C5) == 0) {
        goto L_003B3A;
    }
    myMapper->writeCPU(0x008B, 0xBC);
    myMapper->writeCPU(0x008A, 0x71);
    myMapper->writeCPU(0x0089, 0x22);
    myMapper->writeCPU(0x0088, 0x8B);
    myMapper->writeCPU(0x0087, 0x08);
    pushAddress(0x003B37);
    SUB_00001B();
    if (poppedEntry.value != 0x003B37) return;
L_003B3A:
    myMapper->writeCPU(0x008B, 0xBC);
    myMapper->writeCPU(0x008A, 0x79);
    myMapper->writeCPU(0x0087, 0x0D);
    myMapper->writeCPU(0x0089, 0x23);
    myMapper->writeCPU(0x0088, 0x09);
    SUB_00001B();
    return;
}

void game::SUB_003C86() {
    myMapper->writeCPU(0x0723, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x0385, a);
    myMapper->writeCPU(0x006E, a);
    myMapper->writeCPU(0x006D, a);
    myMapper->writeCPU(0x078F, a);
    myMapper->writeCPU(0x006B, 0x8F);
    myMapper->writeCPU(0x006C, 0x07);
    myMapper->writeCPU(0x048C, 0x00);
    myMapper->writeCPU(0x0723, 0x00);
    myMapper->writeCPU(0x0385, 0x01);
    popAddress();
}

void game::SUB_003CAF() {
    myMapper->writeCPU(0x0086, 0x0A);
    myMapper->writeCPU(0x0087, 0x00);
    SUB_004251();
    return;
}

void game::SUB_003CBA() {
    a = 0x08;
    SUB_00206B();
    return;
}

void game::SUB_003CBF() {
    do {
        myMapper->writeCPU(0x008A, myMapper->readCPU(0x00DD));
        myMapper->writeCPU(0x008B, myMapper->readCPU(0x00DE));
        myMapper->writeCPU(0x0088, myMapper->readCPU(0x00DF));
        myMapper->writeCPU(0x0089, myMapper->readCPU(0x00E0));
        a = 0x01;
        myMapper->writeCPU(0x0087, a);
        myMapper->writeCPU(0x0086, a);
        pushAddress(0x003CD5);
        SUB_00001B();
        if (poppedEntry.value != 0x003CD5) return;
        pushAddress(0x003CD8);
        SUB_003CBA();
        if (poppedEntry.value != 0x003CD8) return;
        pushAddress(0x003CDB);
        SUB_003CAF();
        if (poppedEntry.value != 0x003CDB) return;
        opINC(0x00DD, 1);
        if (flgZ) {
            opINC(0x00DE, 1);
        }
        opINC(0x00DF, 1);
        if (!flgZ) {
            goto L_003CEA;
        }
        opINC(0x00E0, 1);
    L_003CEA:
        opDEC(0x00E2, 1);
    } while (!flgZ);
    SUB_003CAF();
    return;
}

void game::SUB_003CF1() {
    a = myMapper->readCPU(0x008C);
    opAND(0xFD);
    myMapper->writeCPU(0x008C, a);
    a = 0x00;
    myMapper->writeCPU(0x008F, a);
    myMapper->writeCPU(0x0090, a);
    pushAddress(0x003CFD);
    SUB_00393D();
    if (poppedEntry.value != 0x003CFD) return;
    pushAddress(0x003D00);
    SUB_00396C();
    if (poppedEntry.value != 0x003D00) return;
    myMapper->writeCPU(0x008A, 0x51);
    myMapper->writeCPU(0x008B, 0xBB);
    pushAddress(0x003D0B);
    SUB_00275A();
    if (poppedEntry.value != 0x003D0B) return;
    y = 0x3F;
    a = 0x00;
    do {
        myMapper->writeCPU(0x0300 + y, a);
        opDEY(1);
    } while (!flgN);
    myMapper->writeCPU(0x008B, 0xBB);
    myMapper->writeCPU(0x008A, 0x71);
    myMapper->writeCPU(0x0089, 0x23);
    myMapper->writeCPU(0x0088, 0xC0);
    myMapper->writeCPU(0x0087, 0x40);
    pushAddress(0x003D2C);
    SUB_00001B();
    if (poppedEntry.value != 0x003D2C) return;
    a = myMapper->readCPU(0x008C);
    opAND(0xEF);
    opORA(0x08);
    myMapper->writeCPU(0x008C, a);
    SUB_004275();
    return;
}

void game::SUB_003D3A() {
    a = 0x07;
    pushAddress(0x003D3C);
    SUB_00206B();
    if (poppedEntry.value != 0x003D3C) return;
    a = 0x09;
    pushAddress(0x003D41);
    SUB_00206B();
    if (poppedEntry.value != 0x003D41) return;
    if (myMapper->readCPU(0x0384) == 0) {
        if (myMapper->readCPU(0x0386) != 0) {
            goto L_003D5E;
        }
        y = 0x05;
        do {
            myMapper->writeCPU(0x044A + y, myMapper->readCPU(0x0427 + y));
            opDEY(1);
        } while (y != 0xFF);
        goto L_003D6B;
    L_003D5E:
        y = 0x05;
        do {
            myMapper->writeCPU(0x046B + y, myMapper->readCPU(0x0427 + y));
            opDEY(1);
        } while (y != 0xFF);
    }
L_003D6B:
    pushAddress(0x003D6B);
    SUB_003CF1();
    if (poppedEntry.value != 0x003D6B) return;
    myMapper->writeCPU(0x008B, 0xBF);
    myMapper->writeCPU(0x008A, 0x0F);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x45);
    myMapper->writeCPU(0x0087, 0x03);
    pushAddress(0x003D82);
    SUB_00001B();
    if (poppedEntry.value != 0x003D82) return;
    myMapper->writeCPU(0x008B, 0x04);
    myMapper->writeCPU(0x008A, 0x4A);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x63);
    myMapper->writeCPU(0x0087, 0x06);
    pushAddress(0x003D99);
    SUB_00001B();
    if (poppedEntry.value != 0x003D99) return;
    myMapper->writeCPU(0x008B, 0xBF);
    myMapper->writeCPU(0x008A, 0x15);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x4C);
    myMapper->writeCPU(0x0087, 0x08);
    pushAddress(0x003DB0);
    SUB_00001B();
    if (poppedEntry.value != 0x003DB0) return;
    myMapper->writeCPU(0x008B, 0x07);
    myMapper->writeCPU(0x008A, 0xBF);
    myMapper->writeCPU(0x0089, 0x20);
    myMapper->writeCPU(0x0088, 0x6D);
    myMapper->writeCPU(0x0087, 0x06);
    pushAddress(0x003DC7);
    SUB_00001B();
    if (poppedEntry.value != 0x003DC7) return;
    if (myMapper->readCPU(0x0381) != 0) {
        myMapper->writeCPU(0x008B, 0xBF);
        myMapper->writeCPU(0x008A, 0x12);
        myMapper->writeCPU(0x0089, 0x20);
        myMapper->writeCPU(0x0088, 0x59);
        myMapper->writeCPU(0x0087, 0x03);
        pushAddress(0x003DE3);
        SUB_00001B();
        if (poppedEntry.value != 0x003DE3) return;
        myMapper->writeCPU(0x008B, 0x04);
        myMapper->writeCPU(0x008A, 0x6B);
        myMapper->writeCPU(0x0089, 0x20);
        myMapper->writeCPU(0x0088, 0x77);
        myMapper->writeCPU(0x0087, 0x06);
        pushAddress(0x003DFA);
        SUB_00001B();
        if (poppedEntry.value != 0x003DFA) return;
    }
    myMapper->writeCPU(0x00DE, 0xBF);
    myMapper->writeCPU(0x00DD, 0x36);
    myMapper->writeCPU(0x00E0, 0x21);
    myMapper->writeCPU(0x00DF, 0x04);
    myMapper->writeCPU(0x00E2, 0x0D);
    pushAddress(0x003E11);
    SUB_003CBF();
    if (poppedEntry.value != 0x003E11) return;
    myMapper->writeCPU(0x00DE, 0x04);
    myMapper->writeCPU(0x00DD, 0x41);
    myMapper->writeCPU(0x00E0, 0x21);
    myMapper->writeCPU(0x00DF, 0x15);
    myMapper->writeCPU(0x00E2, 0x05);
    pushAddress(0x003E28);
    SUB_003CBF();
    if (poppedEntry.value != 0x003E28) return;
    myMapper->writeCPU(0x00DE, 0xBF);
    myMapper->writeCPU(0x00DD, 0x43);
    myMapper->writeCPU(0x00E0, 0x21);
    myMapper->writeCPU(0x00DF, 0x44);
    myMapper->writeCPU(0x00E2, 0x0A);
    pushAddress(0x003E3F);
    SUB_003CBF();
    if (poppedEntry.value != 0x003E3F) return;
    pushAddress(0x003E42);
    SUB_002893();
    if (poppedEntry.value != 0x003E42) return;
    a = myMapper->readCPU(0x038B);
    setLoadFlag(a);
    if (flgZ) {
        a = 0xFF;
    }
    myMapper->writeCPU(0x0720, a);
    myMapper->writeCPU(0x0721, myMapper->readCPU(0x008B));
    myMapper->writeCPU(0x0722, myMapper->readCPU(0x008A));
    myMapper->writeCPU(0x00DE, 0x07);
    myMapper->writeCPU(0x00DD, 0x20);
    myMapper->writeCPU(0x00E0, 0x21);
    myMapper->writeCPU(0x00DF, 0x57);
    myMapper->writeCPU(0x00E2, 0x03);
    pushAddress(0x003E6D);
    SUB_003CBF();
    if (poppedEntry.value != 0x003E6D) return;
    myMapper->writeCPU(0x00DE, 0xBF);
    myMapper->writeCPU(0x00DD, 0x4D);
    myMapper->writeCPU(0x00E0, 0x21);
    myMapper->writeCPU(0x00DF, 0x5A);
    myMapper->writeCPU(0x00E2, 0x01);
    pushAddress(0x003E84);
    SUB_003CBF();
    if (poppedEntry.value != 0x003E84) return;
    myMapper->writeCPU(0x008B, 0xBF);
    myMapper->writeCPU(0x008A, 0x2D);
    myMapper->writeCPU(0x0089, 0x22);
    myMapper->writeCPU(0x0088, 0x4B);
    myMapper->writeCPU(0x0087, 0x09);
    pushAddress(0x003E9B);
    SUB_00001B();
    if (poppedEntry.value != 0x003E9B) return;
    myMapper->writeCPU(0x0723, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x006E, a);
    myMapper->writeCPU(0x006D, a);
    myMapper->writeCPU(0x078F, a);
    myMapper->writeCPU(0x006B, 0x8F);
    myMapper->writeCPU(0x006C, 0x07);
    myMapper->writeCPU(0x0437, 0x00);
    myMapper->writeCPU(0x0723, 0x00);
    if (myMapper->readCPU(0x0386) == 0) {
        goto L_003ECE;
    }
    myMapper->writeCPU(0x008B, 0xBF);
    myMapper->writeCPU(0x008A, 0x25);
    goto L_003ED6;
L_003ECE:
    myMapper->writeCPU(0x008B, 0xBF);
    myMapper->writeCPU(0x008A, 0x1D);
L_003ED6:
    myMapper->writeCPU(0x0089, 0x21);
    myMapper->writeCPU(0x0088, 0xEC);
    myMapper->writeCPU(0x0087, 0x08);
    pushAddress(0x003EE2);
    SUB_00001B();
    if (poppedEntry.value != 0x003EE2) return;
    myMapper->writeCPU(0x0087, 0x00);
    myMapper->writeCPU(0x0086, 0x80);
    pushAddress(0x003EED);
    SUB_004251();
    if (poppedEntry.value != 0x003EED) return;
    a = myMapper->readCPU(0x008D);
    opAND(0xE7);
    myMapper->writeCPU(0x008D, a);
    pushAddress(0x003EF6);
    SUB_004275();
    if (poppedEntry.value != 0x003EF6) return;
    pushAddress(0x003EF9);
    SUB_00396C();
    if (poppedEntry.value != 0x003EF9) return;
    a = myMapper->readCPU(0x008C);
    opEOR(0x18);
    myMapper->writeCPU(0x008C, a);
    pushAddress(0x003F02);
    SUB_004275();
    if (poppedEntry.value != 0x003F02) return;
    a = myMapper->readCPU(0x008D);
    opORA(0x18);
    myMapper->writeCPU(0x008D, a);
    pushAddress(0x003F0B);
    SUB_004275();
    if (poppedEntry.value != 0x003F0B) return;
    popAddress();
}

void game::SUB_003F58() {
    x = 0x21;
    do {
        myMapper->writeCPU(0x0449 + x, myMapper->readCPU(0x0426 + x));
        opDEX(1);
    } while (!flgZ);
    x = 0x21;
    do {
        myMapper->writeCPU(0x0426 + x, myMapper->readCPU(0x046A + x));
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0386, 0x01);
    popAddress();
}

void game::SUB_003F74() {
    x = 0x21;
    do {
        myMapper->writeCPU(0x046A + x, myMapper->readCPU(0x0426 + x));
        opDEX(1);
    } while (!flgZ);
    SUB_003F7F();
    return;
}

void game::SUB_003F7F() {
    x = 0x21;
    do {
        myMapper->writeCPU(0x0426 + x, myMapper->readCPU(0x0449 + x));
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0386, 0x00);
    popAddress();
}

void game::reset() {
    runningThread = {-1, 0, NULL, NULL, NULL, NULL, 0, -1};
    xIdx = -1;

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
    if (flgZ) {
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
    }
    SUB_004230();
    return;
}

void game::SUB_004230() {
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popStatus();
    popAddress();
}

void game::SUB_004237() {
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU((0x0002 + x) & 0x00ff, 0x00);
    SUB_0042C0();
    return;
}

void game::SUB_004240() {
    pushStatus();
    opPHA();
    myMapper->writeCPU(0x0066, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = myMapper->readCPU(0x0066);
    a = 0x00;
    myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
    SUB_004230();
    return;
}

void game::SUB_004251() {
    markThread();
    pushStatus();
    opPHA();
    a = x;
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU((0x0042 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0043 + x) & 0x00ff, y);
    a = s;
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0002 + x) & 0x00ff);
    opORA(0x40);
    myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0022 + x) & 0x00ff, myMapper->readCPU(0x0086));
    myMapper->writeCPU((0x0023 + x) & 0x00ff, myMapper->readCPU(0x0087));
    SUB_0042C0();
    return;
}

void game::SUB_004275() {
    markThread();
    pushStatus();
    opPHA();
    a = x;
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU((0x0042 + x) & 0x00ff, a);
    myMapper->writeCPU((0x0043 + x) & 0x00ff, y);
    a = s;
    x = myMapper->readCPU(0x0000);
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
	SUB_0042C0();
}

void game::SUB_004288() {
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
        a = myMapper->readCPU((0x0002 + x) & 0x00ff);
        opAND(0xFE);
        myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
    }
    SUB_004230();
    return;
}

void game::SUB_0042A4() {
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
        a = myMapper->readCPU((0x0002 + x) & 0x00ff);
        opORA(0x01);
        myMapper->writeCPU((0x0002 + x) & 0x00ff, a);
    }
    SUB_004230();
    return;
}

void game::SUB_0042C0() {
    while (true) {
        x = myMapper->readCPU(0x0000);
        if (x != 0x20) {
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
        }
        myMapper->writeCPU(0x0000, 0x00);
        s = 0xF3;

        a = myMapper->readCPU(0x008C);
        opORA(0x80);
        myMapper->writeCPU(0x008C, a);
        myMapper->writeCPU(0x2000, a);
        SDL_LockMutex(myConsole->lock);
        do {
            wait();
            a = myMapper->readCPU(0x0062);
        } while (a < 0x03);
        SDL_UnlockMutex(myConsole->lock);
        myMapper->writeCPU(0x0062, 0x00);
    }
L_0042F5:
    xIdx = x;
    myMapper->writeCPU(0x0000, x);
    x = myMapper->readCPU((0x0003 + x) & 0x00ff);
    s = x;
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU((0x0043 + x) & 0x00ff);
    x = myMapper->readCPU((0x0042 + x) & 0x00ff);
    opPLA();
    popStatus();
    popAddress();

    if (poppedEntry.value > 0x8000) {
        createThread(poppedEntry.value - 0x7FFF);
    }
    else {
        switchThread();
    }
}

void game::SUB_004306() {
    a = x;
    opPHA();
    myMapper->writeCPU(0x071D, 0x0A);
    do {
        a = myMapper->readCPU(0x071D);
        pushAddress(0x004310);
        SUB_004240();
        if (poppedEntry.value != 0x004310) return;
        opINC(0x071D, 2);
        a = myMapper->readCPU(0x071D);
    } while (a != 0x20);
    x = 0x03;
    do {
        pushAddress(0x004322);
        SUB_00432D();
        if (poppedEntry.value != 0x004322) return;
        opINX(1);
    } while (x != 0x19);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_00432D() {
    a = 0x00;
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x04D9 + x, a);
    myMapper->writeCPU(0x050B + x, a);
    myMapper->writeCPU(0x05BA + x, a);
    myMapper->writeCPU(0x04C0 + x, a);
    myMapper->writeCPU(0x04A7 + x, a);
    myMapper->writeCPU(0x056F + x, a);
    myMapper->writeCPU(0x0588 + x, a);
    myMapper->writeCPU(0x05A1 + x, a);
    myMapper->writeCPU(0x0524 + x, a);
    myMapper->writeCPU(0x053D + x, a);
    myMapper->writeCPU(0x0556 + x, a);
    myMapper->writeCPU(0x05EC + x, a);
    myMapper->writeCPU(0x0605 + x, a);
    myMapper->writeCPU(0x061E + x, a);
    myMapper->writeCPU(0x0637 + x, a);
    myMapper->writeCPU(0x0650 + x, a);
    myMapper->writeCPU(0x069B + x, a);
    popAddress();
}

void game::SUB_0043CA() {
    while (true) {
        x = 0x00;
        y = 0x00;
        do {
            if (!(myMapper->readCPU(0x048E + x) & 0x80)) {
                goto L_0043F3;
            }
            myMapper->writeCPU(0x03AF + y, myMapper->readCPU(0x04A7 + x));
            opINY(1);
            myMapper->writeCPU(0x03AF + y, myMapper->readCPU(0x04D9 + x));
            opINY(1);
            myMapper->writeCPU(0x03AF + y, myMapper->readCPU(0x04F2 + x));
            opINY(1);
            myMapper->writeCPU(0x03AF + y, myMapper->readCPU(0x04C0 + x));
            opINY(1);
            if (y >= 0x74) {
                goto L_0043F8;
            }
        L_0043F3:
            opINX(1);
        } while (x != 0x19);
    L_0043F8:
        myMapper->writeCPU(0x0087, 0x04);
        do {
            myMapper->writeCPU(0x03AF + y, 0xFF);
            opINY(1);
            opDEC(0x0087, 1);
        } while (!flgZ);
        myMapper->writeCPU(0x009C, 0xAF);
        myMapper->writeCPU(0x009D, 0x03);
        a = myMapper->readCPU(0x078C);
        if (a == 0xFF) {
            goto L_004424;
        }
        if (a == 0x80) {
            goto L_00442F;
        }
        myMapper->writeCPU(0x009E, 0x30);
        myMapper->writeCPU(0x009F, 0x02);
        goto L_004437;
    L_004424:
        myMapper->writeCPU(0x009E, 0x40);
        myMapper->writeCPU(0x009F, 0x02);
        goto L_004437;
    L_00442F:
        myMapper->writeCPU(0x009E, 0x64);
        myMapper->writeCPU(0x009F, 0x02);
    L_004437:
        pushAddress(0x004437);
        SUB_00445A();
        if (poppedEntry.value != 0x004437) return;
        y = 0x00;
        myMapper->writeCPU(0x008A, myMapper->readCPU(0x009E));
        myMapper->writeCPU(0x008B, myMapper->readCPU(0x009F));
        while (true) {
            a = myMapper->readCPU(0x008B);
            opCMP(a, 0x03);
            if (flgC) {
                goto L_004454;
            }
            myMapper->writeCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y, 0xFF);
            pushAddress(0x00444E);
            SUB_00454D();
            if (poppedEntry.value != 0x00444E) return;
        }
    L_004454:
        pushAddress(0x004454);
        SUB_004275();
        if (poppedEntry.value != 0x004454) return;
    }
    SUB_00445A();
    return;
}

void game::SUB_00445A() {
    while (true) {
        y = 0x01;
        a = myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y);
        if (a != 0xFF) {
            goto L_004463;
        }
        popAddress();
        return;
    L_004463:
        x = 0x00;
        y = 0x00;
        flgC = false;
        myMapper->writeCPU(0x0088, a);
        myMapper->writeCPU(0x0089, 0x00);
        opASL_M(0x0088, 1);
        opROL_M(0x0089, 1);
        flgC = false;
        a = myMapper->readCPU(0x0088);
        opADC(0x65);
        myMapper->writeCPU(0x0088, a);
        a = myMapper->readCPU(0x0089);
        opADC(0xC5);
        myMapper->writeCPU(0x0089, a);
        myMapper->writeCPU(0x008A, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x008B, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0087, myMapper->readCPU(myMapper->readCPU((0x008A + x) & 0x00ff) + (myMapper->readCPU((0x008A + x + 1) & 0x00ff) << 8)));
        pushAddress(0x00448C);
        SUB_00454D();
        if (poppedEntry.value != 0x00448C) return;
        a = myMapper->readCPU(myMapper->readCPU((0x008A + x) & 0x00ff) + (myMapper->readCPU((0x008A + x + 1) & 0x00ff) << 8));
        opASL_A(1);
        opADC(0x0E);
        myMapper->writeCPU(0x0088, a);
        a = 0x00;
        opADC(0xCE);
        myMapper->writeCPU(0x0089, a);
        y = 0x00;
        myMapper->writeCPU(0x00A2, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x00A3, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        pushAddress(0x0044A7);
        SUB_00454D();
        if (poppedEntry.value != 0x0044A7) return;
        y = 0x02;
        a = myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y);
        opASL_A(1);
        opADC(0x10);
        myMapper->writeCPU(0x0088, a);
        a = 0x00;
        opADC(0xD0);
        myMapper->writeCPU(0x0089, a);
        y = 0x00;
        myMapper->writeCPU(0x00A0, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x00A1, myMapper->readCPU(myMapper->readCPU(0x0088) + (myMapper->readCPU((0x0088 + 1) & 0x00ff) << 8) + y));
        do {
            y = 0x01;
            a = myMapper->readCPU(myMapper->readCPU((0x008A + x) & 0x00ff) + (myMapper->readCPU((0x008A + x + 1) & 0x00ff) << 8));
            opCMP(a, 0xFF);
            if (flgZ) {
                goto L_004526;
            }
            myMapper->writeCPU(myMapper->readCPU(0x009E) + (myMapper->readCPU((0x009E + 1) & 0x00ff) << 8) + y, a);
            y = 0x03;
            a = myMapper->readCPU(myMapper->readCPU((0x00A2 + x) & 0x00ff) + (myMapper->readCPU((0x00A2 + x + 1) & 0x00ff) << 8));
            flgC = false;
            opADC(myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(myMapper->readCPU(0x009E) + (myMapper->readCPU((0x009E + 1) & 0x00ff) << 8) + y, a);
            pushAddress(0x0044D7);
            SUB_004546();
            if (poppedEntry.value != 0x0044D7) return;
            a = myMapper->readCPU(myMapper->readCPU((0x00A2 + x) & 0x00ff) + (myMapper->readCPU((0x00A2 + x + 1) & 0x00ff) << 8));
            y = 0x00;
            flgC = false;
            opADC(myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y));
            myMapper->writeCPU(myMapper->readCPU(0x009E) + (myMapper->readCPU((0x009E + 1) & 0x00ff) << 8) + y, a);
            pushAddress(0x0044E3);
            SUB_004546();
            if (poppedEntry.value != 0x0044E3) return;
            a = myMapper->readCPU(myMapper->readCPU((0x00A0 + x) & 0x00ff) + (myMapper->readCPU((0x00A0 + x + 1) & 0x00ff) << 8));
            y = 0x02;
            myMapper->writeCPU(myMapper->readCPU(0x009E) + (myMapper->readCPU((0x009E + 1) & 0x00ff) << 8) + y, a);
            pushAddress(0x0044EC);
            SUB_00454D();
            if (poppedEntry.value != 0x0044EC) return;
            a = myMapper->readCPU(myMapper->readCPU((0x008A + x) & 0x00ff) + (myMapper->readCPU((0x008A + x + 1) & 0x00ff) << 8));
            opROR_A(3);
            opORA(myMapper->readCPU(myMapper->readCPU(0x009E) + (myMapper->readCPU((0x009E + 1) & 0x00ff) << 8) + y));
            opAND(0xC3);
            myMapper->writeCPU(myMapper->readCPU(0x009E) + (myMapper->readCPU((0x009E + 1) & 0x00ff) << 8) + y, a);
            pushAddress(0x0044FA);
            SUB_00454D();
            if (poppedEntry.value != 0x0044FA) return;
            pushAddress(0x0044FD);
            SUB_00453F();
            if (poppedEntry.value != 0x0044FD) return;
            flgC = false;
            a = myMapper->readCPU(0x009E);
            opADC(0x04);
            myMapper->writeCPU(0x009E, a);
            a = myMapper->readCPU(0x009F);
            opADC(0x00);
            myMapper->writeCPU(0x009F, a);
            if (a < 0x03) {
                goto L_004512;
            }
            popAddress();
            return;
        L_004512:
            opDEC(0x0087, 1);
        } while (!flgZ);
        flgC = false;
        a = myMapper->readCPU(0x009C);
        opADC(0x04);
        myMapper->writeCPU(0x009C, a);
        a = myMapper->readCPU(0x009D);
        opADC(0x00);
        myMapper->writeCPU(0x009D, a);
    }
L_004526:
    pushAddress(0x004526);
    SUB_00454D();
    if (poppedEntry.value != 0x004526) return;
    pushAddress(0x004529);
    SUB_00454D();
    if (poppedEntry.value != 0x004529) return;
    pushAddress(0x00452C);
    SUB_00453F();
    if (poppedEntry.value != 0x00452C) return;
    pushAddress(0x00452F);
    SUB_004546();
    if (poppedEntry.value != 0x00452F) return;
    pushAddress(0x004532);
    SUB_004546();
    if (poppedEntry.value != 0x004532) return;
    goto L_004512;
}

void game::SUB_00453F() {
    opINC(0x00A0, 1);
    if (!flgZ) {
        goto L_004545;
    }
    opINC(0x00A1, 1);
L_004545:
    popAddress();
}

void game::SUB_004546() {
    opINC(0x00A2, 1);
    if (!flgZ) {
        goto L_00454C;
    }
    opINC(0x00A3, 1);
L_00454C:
    popAddress();
}

void game::SUB_00454D() {
    opINC(0x008A, 1);
    if (flgZ) {
        goto L_004552;
    }
    popAddress();
    return;
L_004552:
    opINC(0x008B, 1);
    popAddress();
}

void game::SUB_00506A() {
    x = 0x00;
    a = myMapper->readCPU(0x048E);
    opORA(0x08);
    opORA(0x80);
    myMapper->writeCPU(0x048E, a);
    a = 0x01;
    myMapper->writeCPU(0x056F, a);
    myMapper->writeCPU(0x0524, a);
    myMapper->writeCPU(0x0588, 0x02);
    myMapper->writeCPU(0x053D, 0x50);
    a = 0x00;
    myMapper->writeCPU(0x05A1, a);
    myMapper->writeCPU(0x0556, a);
    myMapper->writeCPU(0x04F2, 0x03);
    if (myMapper->readCPU(0x07BC) != 0) {
        if (myMapper->readCPU(0x0437) != 0) {
            goto L_0050A2;
        }
        SUB_00515B();
        return;
    L_0050A2:
        SUB_005165();
        return;
    }
    if (myMapper->readCPU(0x0437) == 0) {
        goto L_0050AD;
    }
    SUB_005165();
    return;
L_0050AD:
    myMapper->writeCPU(0x04D9, 0xA0);
    pushAddress(0x0050B2);
    SUB_004275();
    if (poppedEntry.value != 0x0050B2) return;
    SUB_0050B5();
    return;
}

void game::SUB_0050B5() {
    myMapper->writeCPU(0x050B, 0x00);
    myMapper->writeCPU(0x05BA, 0x08);
    do {
        a = 0x0A;
        pushAddress(0x0050C1);
        SUB_00206B();
        if (poppedEntry.value != 0x0050C1) return;
        pushAddress(0x0050C4);
        SUB_00519A();
        if (poppedEntry.value != 0x0050C4) return;
    } while (a < 0x28);
    a = 0x0A;
    pushAddress(0x0050CD);
    SUB_002094();
    if (poppedEntry.value != 0x0050CD) return;
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    a = 0x15;
    pushAddress(0x0050DA);
    SUB_00206B();
    if (poppedEntry.value != 0x0050DA) return;
    do {
        pushAddress(0x0050DD);
        SUB_00519A();
        if (poppedEntry.value != 0x0050DD) return;
    } while (a < 0x08);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x0050EC);
        SUB_00519A();
        if (poppedEntry.value != 0x0050EC) return;
    } while (a < 0x08);
    opINC(0x04D9, 1);
    pushAddress(0x0050F6);
    SUB_004275();
    if (poppedEntry.value != 0x0050F6) return;
    pushAddress(0x0050F9);
    SUB_004275();
    if (poppedEntry.value != 0x0050F9) return;
    pushAddress(0x0050FC);
    SUB_004275();
    if (poppedEntry.value != 0x0050FC) return;
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x050B + x, 0x08);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x00510C);
        SUB_00519A();
        if (poppedEntry.value != 0x00510C) return;
    } while (a < 0x0A);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x00511B);
        SUB_00519A();
        if (poppedEntry.value != 0x00511B) return;
    } while (a < 0x14);
    do {
        pushAddress(0x005122);
        SUB_00519A();
        if (poppedEntry.value != 0x005122) return;
        a = myMapper->readCPU(0x04A7 + x);
    } while (a < 0xC0);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x005134);
        SUB_00519A();
        if (poppedEntry.value != 0x005134) return;
    } while (a < 0x08);
    opINC(0x04D9, 1);
    pushAddress(0x00513E);
    SUB_004275();
    if (poppedEntry.value != 0x00513E) return;
    pushAddress(0x005141);
    SUB_004275();
    if (poppedEntry.value != 0x005141) return;
    pushAddress(0x005144);
    SUB_004275();
    if (poppedEntry.value != 0x005144) return;
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x050B, 0x00);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x005154);
        SUB_00519A();
        if (poppedEntry.value != 0x005154) return;
    } while (a < 0x0A);
    SUB_00515B();
    return;
}

void game::SUB_00515B() {
    a = 0x0E;
    pushAddress(0x00515D);
    SUB_00206B();
    if (poppedEntry.value != 0x00515D) return;
    a = 0x16;
    pushAddress(0x005162);
    SUB_00206B();
    if (poppedEntry.value != 0x005162) return;
    SUB_005165();
    return;
}

void game::SUB_005165() {
    a = 0x01;
    myMapper->writeCPU(0x056F, a);
    myMapper->writeCPU(0x0524, a);
    myMapper->writeCPU(0x0588, 0x02);
    myMapper->writeCPU(0x053D, 0x30);
    a = 0x00;
    myMapper->writeCPU(0x05A1, a);
    myMapper->writeCPU(0x0556, a);
    myMapper->writeCPU(0x04D9, 0x00);
    myMapper->writeCPU(0x05BA, 0x14);
    pushAddress(0x005189);
    SUB_0031D7();
    if (poppedEntry.value != 0x005189) return;
    a = myMapper->readCPU(0x048E);
    opAND(0xBE);
    myMapper->writeCPU(0x048E, a);
    pushAddress(0x005194);
    SUB_004275();
    if (poppedEntry.value != 0x005194) return;
    SUB_0051AC();
    return;
}

void game::SUB_00519A() {
    a = 0x08;
    pushAddress(0x00519C);
    SUB_003048();
    if (poppedEntry.value != 0x00519C) return;
    pushAddress(0x00519F);
    SUB_0031D7();
    if (poppedEntry.value != 0x00519F) return;
    pushAddress(0x0051A2);
    SUB_004275();
    if (poppedEntry.value != 0x0051A2) return;
    opINC(0x069B, 1);
    a = myMapper->readCPU(0x069B);
    popAddress();
}

void game::SUB_0051AC() {
    x = 0x00;
    SUB_0051AE();
    return;
}

void game::SUB_0051AE() {
    while (true) {
        a = myMapper->readCPU(0x048E + x);
        opAND(0x08);
        if (!flgZ) {
            SUB_0051C0_B();
        }
        else {
            SUB_0051B5_B();
        }
    }
}

void game::SUB_0051B5_B() {
    opINX(1);
    if (x == 0x03) {
        pushAddress(0x0051BA);
        SUB_004275();
        if (poppedEntry.value != 0x0051BA) return;
        x = 0x00;
    }
}


void game::SUB_0051B5() {
    SUB_0051B5_B();
    SUB_0051AE();
    return;
}

void game::SUB_0051C0_B() {
    a = myMapper->readCPU(0x048E + x);
    opAND(0x20);
    if (!flgZ) {
        SUB_0055BC();
        return;
    }
    pushAddress(0x0051CA);
    SUB_00579B();
    if (poppedEntry.value != 0x0051CA) return;
    if (!flgZ) {
        pushAddress(0x0051CF);
        SUB_0033CF();
        if (poppedEntry.value != 0x0051CF) return;
        if (!flgZ) {
            SUB_0055A5();
            return;
        }
    }
    if (x != 0x00) {
        a = myMapper->readCPU(0x048E + x);
        opAND(0x10);
        if (!flgZ) {
            SUB_005617();
            return;
        }
        a = myMapper->readCPU(0x048E + x);
        opAND(0x02);
        if (flgZ) {
            goto L_0051F2;
        }
        SUB_005698();
        return;
    L_0051F2:
        a = myMapper->readCPU(0x048E + x);
        opAND(0x04);
        if (flgZ) {
            SUB_0051FC();
            return;
        }
        SUB_0056B7();
        return;
    }
    SUB_005214_B();
}

void game::SUB_0051C0() {
    SUB_0051C0_B();
    SUB_0051AE();
}

void game::SUB_0051FC() {
    pushAddress(0x0051FC);
    SUB_00525B();
    if (poppedEntry.value != 0x0051FC) return;
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(0x053D));
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(0x0524));
    pushAddress(0x00520B);
    SUB_0031D7();
    if (poppedEntry.value != 0x00520B) return;
    pushAddress(0x00520E);
    SUB_00337B();
    if (poppedEntry.value != 0x00520E) return;
    SUB_0051B5();
    return;
}

void game::SUB_005214_B() {
    pushAddress(0x005214);
    SUB_00579B();
    if (poppedEntry.value != 0x005214) return;
    if (!flgZ) {
        pushAddress(0x005219);
        SUB_0033CF();
        if (poppedEntry.value != 0x005219) return;
        if (!flgZ) {
            SUB_0055A5();
            return;
        }
    }
    a = myMapper->readCPU(0x0785);
    opAND(0x80);
    if (flgZ) {
        a = myMapper->readCPU(0x0388);
        opAND(0xFE);
        myMapper->writeCPU(0x0388, a);
    }
    else {
        a = myMapper->readCPU(0x0388);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x0388);
            opORA(0x01);
            myMapper->writeCPU(0x0388, a);
            pushAddress(0x00523A);
            SUB_005303();
            if (poppedEntry.value != 0x00523A) return;
        }
    }
    pushAddress(0x005248);
    SUB_0052AA();
    if (poppedEntry.value != 0x005248) return;
    pushAddress(0x00524B);
    SUB_005472();
    if (poppedEntry.value != 0x00524B) return;
    a = myMapper->readCPU(0x0437);
    if (a == 0xFF) {
        SUB_00563E();
        return;
    }
    SUB_0051B5_B();

}

void game::SUB_005214() {
    SUB_005214_B();
    SUB_0051AE();
}

void game::SUB_00525B() {
    a = myMapper->readCPU(0x048E + x);
    opAND(0x80);
    if (!flgZ) {
        if (x != 0x01) {
            goto L_005289;
        }
        a = myMapper->readCPU(0x0588);
        flgC = true;
        opSBC(0x15);
        if (!flgC) {
            myMapper->writeCPU(0x0588 + x, a);
            a = myMapper->readCPU(0x056F);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU(0x056F + x, a);
            goto L_0052A9;
        }
        myMapper->writeCPU(0x0588 + x, a);
        myMapper->writeCPU(0x056F + x, myMapper->readCPU(0x056F));
        goto L_0052A9;
    L_005289:
        a = myMapper->readCPU(0x0588);
        flgC = false;
        opADC(0x15);
        if (!flgC) {
            goto L_0052A0;
        }
        myMapper->writeCPU(0x0588 + x, a);
        a = myMapper->readCPU(0x056F);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x056F + x, a);
        goto L_0052A9;
    L_0052A0:
        myMapper->writeCPU(0x0588 + x, a);
        myMapper->writeCPU(0x056F + x, myMapper->readCPU(0x056F));
    }
L_0052A9:
    popAddress();
}

void game::SUB_0052AA() {
    a = myMapper->readCPU(0x0785);
    opAND(0x40);
    if (!flgZ) {
        a = myMapper->readCPU(0x0388);
        opAND(0x10);
        if (!flgZ) {
            goto L_0052C3;
        }
        a = myMapper->readCPU(0x0388);
        opORA(0x10);
        myMapper->writeCPU(0x0388, a);
        goto L_0052CB;
    L_0052C3:
        opINC(0x00DB, 1);
        a = myMapper->readCPU(0x00DB);
        if (a < 0x0A) {
            goto L_0052DD;
        }
    L_0052CB:
        myMapper->writeCPU(0x00DB, 0x00);
        pushAddress(0x0052CF);
        SUB_0053B9();
        if (poppedEntry.value != 0x0052CF) return;
    }
    else {
        a = myMapper->readCPU(0x0388);
        opAND(0xEF);
        myMapper->writeCPU(0x0388, a);
    }
L_0052DD:
    popAddress();
}

void game::SUB_0052DE() {
    x = 0x01;
    pushAddress(0x0052E0);
    SUB_00525B();
    if (poppedEntry.value != 0x0052E0) return;
    pushAddress(0x0052E3);
    SUB_0031D7();
    if (poppedEntry.value != 0x0052E3) return;
    x = 0x02;
    pushAddress(0x0052E8);
    SUB_00525B();
    if (poppedEntry.value != 0x0052E8) return;
    pushAddress(0x0052EB);
    SUB_0031D7();
    if (poppedEntry.value != 0x0052EB) return;
    x = 0x00;
    SUB_005472();
    return;
}

void game::SUB_0052F3() {
    myMapper->writeCPU(0x050B, 0x00);
    SUB_00519A();
    return;
}

void game::SUB_0052FB() {
    myMapper->writeCPU(0x050B, 0x08);
    SUB_00519A();
    return;
}

void game::SUB_005303() {
    if (myMapper->readCPU(0x0436) != 0) {
        goto L_005309;
    }
    popAddress();
    return;
L_005309:
    opDEC(0x0436, 1);
    a = myMapper->readCPU(0x048E);
    opORA(0x10);
    myMapper->writeCPU(0x048E, a);
    myMapper->writeCPU(0x069B, 0x00);
    a = 0x15;
    pushAddress(0x00531B);
    SUB_00206B();
    if (poppedEntry.value != 0x00531B) return;
    do {
        pushAddress(0x00531E);
        SUB_0052DE();
        if (poppedEntry.value != 0x00531E) return;
        pushAddress(0x005321);
        SUB_0052F3();
        if (poppedEntry.value != 0x005321) return;
    } while (a < 0x08);
    myMapper->writeCPU(0x04D9, 0xA1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x005332);
        SUB_0052DE();
        if (poppedEntry.value != 0x005332) return;
        pushAddress(0x005335);
        SUB_0052F3();
        if (poppedEntry.value != 0x005335) return;
    } while (a < 0x04);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x005344);
        SUB_0052DE();
        if (poppedEntry.value != 0x005344) return;
        pushAddress(0x005347);
        SUB_0052FB();
        if (poppedEntry.value != 0x005347) return;
    } while (a < 0x04);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x005356);
        SUB_0052DE();
        if (poppedEntry.value != 0x005356) return;
        pushAddress(0x005359);
        SUB_0052FB();
        if (poppedEntry.value != 0x005359) return;
    } while (a < 0x08);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x005368);
        SUB_0052DE();
        if (poppedEntry.value != 0x005368) return;
        pushAddress(0x00536B);
        SUB_0052FB();
        if (poppedEntry.value != 0x00536B) return;
    } while (a < 0x08);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x00537A);
        SUB_0052DE();
        if (poppedEntry.value != 0x00537A) return;
        pushAddress(0x00537D);
        SUB_0052FB();
        if (poppedEntry.value != 0x00537D) return;
    } while (a < 0x04);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x00538C);
        SUB_0052DE();
        if (poppedEntry.value != 0x00538C) return;
        pushAddress(0x00538F);
        SUB_0052F3();
        if (poppedEntry.value != 0x00538F) return;
    } while (a < 0x04);
    opINC(0x04D9, 1);
    myMapper->writeCPU(0x069B, 0x00);
    do {
        pushAddress(0x00539E);
        SUB_0052AA();
        if (poppedEntry.value != 0x00539E) return;
        pushAddress(0x0053A1);
        SUB_0052DE();
        if (poppedEntry.value != 0x0053A1) return;
        pushAddress(0x0053A4);
        SUB_0052F3();
        if (poppedEntry.value != 0x0053A4) return;
    } while (a < 0x08);
    myMapper->writeCPU(0x04D9, 0x00);
    a = myMapper->readCPU(0x048E);
    opAND(0xEF);
    myMapper->writeCPU(0x048E, a);
    popAddress();
}

void game::SUB_0053B9() {
    myMapper->writeCPU(0x071A, 0x0B);
    myMapper->writeCPU(0x0719, 0x01);
    while (true) {
        y = myMapper->readCPU(0x071A);
        if (!(myMapper->readCPU(0x048E + y) & 0x80)) {
        }
        else {
            goto L_005464;
        }
        myMapper->writeCPU(0x048E + y, 0x88);
        pushAddress(0x0053D6);
        SUB_005769();
        if (poppedEntry.value != 0x0053D6) return;
        a = myMapper->readCPU(0x048F);
        opAND(0x10);
        if (flgZ) {
            a = myMapper->readCPU(0x048F);
            opAND(0x04);
            if (flgZ) {
                a = myMapper->readCPU(0x048F);
                opAND(0x08);
                if (!flgZ) {
                    goto L_005423;
                }
                a = myMapper->readCPU(0x0490);
                opAND(0x08);
                if (!flgZ) {
                    goto L_00540C;
                }
            }
        }
        a = myMapper->readCPU(0x048E);
        opAND(0x02);
        if (flgZ) {
            myMapper->writeCPU(0x04D9 + y, 0x08);
        }
        else {
            myMapper->writeCPU(0x04D9 + y, 0x09);
            goto L_005455;
        L_00540C:
            a = myMapper->readCPU(0x048E);
            opAND(0x02);
            if (flgZ) {
                myMapper->writeCPU(0x04D9 + y, 0x0C);
            }
            else {
                myMapper->writeCPU(0x04D9 + y, 0x0F);
                goto L_005455;
            L_005423:
                a = myMapper->readCPU(0x0490);
                opAND(0x08);
                if (flgZ) {
                    a = myMapper->readCPU(0x048E);
                    opAND(0x02);
                    if (flgZ) {
                        myMapper->writeCPU(0x04D9 + y, 0x0B);
                        goto L_005455;
                    }
                    myMapper->writeCPU(0x04D9 + y, 0x0E);
                    goto L_005455;
                }
                a = myMapper->readCPU(0x048E);
                opAND(0x02);
                if (!flgZ) {
                    goto L_005450;
                }
                myMapper->writeCPU(0x04D9 + y, 0x0A);
                goto L_005455;
            L_005450:
                myMapper->writeCPU(0x04D9 + y, 0x0D);
            }
        }
    L_005455:
        myMapper->writeCPU(0x04F2 + y, 0x01);
        a = 0x14;
        pushAddress(0x00545C);
        SUB_00206B();
        if (poppedEntry.value != 0x00545C) return;
        opDEC(0x0719, 1);
        if (flgZ) {
            goto L_005471;
        }
    L_005464:
        opINC(0x071A, 1);
        y = myMapper->readCPU(0x071A);
        if (y == 0x0E) {
            goto L_005471;
        }
    }
L_005471:
    popAddress();
}

void game::SUB_005472() {
    a = myMapper->readCPU(0x0785);
    opAND(0x0F);
    if (flgZ) {
        SUB_005592();
        return;
    }
    if (a == 0x01) {
    }
    else {
        if (a != 0x02) {
            goto L_00548A;
        }
        goto L_005512;
    L_00548A:
        if (a == 0x04) {
            goto L_005577;
        }
        if (a == 0x05) {
            goto L_005554;
        }
        if (a == 0x06) {
            goto L_005527;
        }
        if (a == 0x08) {
            goto L_0054EE;
        }
        if (a == 0x09) {
            goto L_0054D5;
        }
        a = 0x0E;
        pushAddress(0x0054AF);
        SUB_005593();
        if (poppedEntry.value != 0x0054AF) return;
        a = myMapper->readCPU(0x04C0 + x);
        if (a < 0x1C) {
            goto L_0054EE;
        }
        a = myMapper->readCPU(0x04A7 + x);
        opCMP(a, 0x30);
        if (flgZ) {
            goto L_005512;
        }
        if (!flgC) {
            goto L_005512;
        }
        SUB_005589();
        return;
        while (true) {
            a = myMapper->readCPU(0x04A7 + x);
            if (a >= 0x30) {
                pushAddress(0x0054CF);
                SUB_005589();
                if (poppedEntry.value != 0x0054CF) return;
            }
            SUB_005592();
            return;
        L_0054D5:
            a = 0x02;
            pushAddress(0x0054D7);
            SUB_005593();
            if (poppedEntry.value != 0x0054D7) return;
            a = myMapper->readCPU(0x04C0 + x);
            if (a >= 0xE4) {
            }
            else {
                a = myMapper->readCPU(0x04A7 + x);
                if (a < 0x31) {
                    goto L_005500;
                }
                SUB_005589();
                return;
            }
        L_0054EE:
            a = myMapper->readCPU(0x048E);
            opAND(0x10);
            if (flgZ) {
                goto L_0054F8;
            }
            SUB_005592();
            return;
        L_0054F8:
            a = 0x00;
            pushAddress(0x0054FA);
            SUB_005593();
            if (poppedEntry.value != 0x0054FA) return;
        }
    }
    while (true) {
    L_005500:
        a = 0x04;
        pushAddress(0x005502);
        SUB_005593();
        if (poppedEntry.value != 0x005502) return;
        a = myMapper->readCPU(0x04C0 + x);
        if (a < 0xE4) {
            goto L_00550F;
        }
        SUB_005592();
        return;
    L_00550F:
        SUB_005589();
        return;
        while (true) {
        L_005512:
            a = 0x0C;
            pushAddress(0x005514);
            SUB_005593();
            if (poppedEntry.value != 0x005514) return;
            a = myMapper->readCPU(0x04C0 + x);
            if (a < 0x1C) {
                goto L_005521;
            }
            goto L_005524;
        L_005521:
            SUB_005592();
            return;
        L_005524:
            SUB_005589();
            return;
        L_005527:
            a = 0x0A;
            pushAddress(0x005529);
            SUB_005593();
            if (poppedEntry.value != 0x005529) return;
            a = myMapper->readCPU(0x04A7 + x);
            if (a < 0xC0) {
                goto L_005540;
            }
            a = myMapper->readCPU(0x04C0 + x);
            if (a < 0x1C) {
                goto L_00553D;
            }
        }
    L_00553D:
        SUB_005592();
        return;
    L_005540:
        a = myMapper->readCPU(0x04C0 + x);
        if (a < 0x1C) {
            goto L_005577;
        }
        SUB_005589();
        return;
    L_00554A:
        a = myMapper->readCPU(0x04A7 + x);
        if (a >= 0xC0) {
            SUB_005592();
            return;
        }
        SUB_005589();
        return;
    L_005554:
        a = 0x06;
        pushAddress(0x005556);
        SUB_005593();
        if (poppedEntry.value != 0x005556) return;
        a = myMapper->readCPU(0x04A7 + x);
        if (a < 0xC0) {
            goto L_00556D;
        }
        a = myMapper->readCPU(0x04C0 + x);
        if (a >= 0xE4) {
            goto L_00556A;
        }
    }
L_00556A:
    SUB_005592();
    return;
L_00556D:
    a = myMapper->readCPU(0x04C0 + x);
    if (a < 0xE4) {
        SUB_005589();
        return;
    }
L_005577:
    a = myMapper->readCPU(0x048E);
    opAND(0x10);
    if (flgZ) {
        goto L_005581;
    }
    SUB_005592();
    return;
L_005581:
    a = 0x08;
    pushAddress(0x005583);
    SUB_005593();
    if (poppedEntry.value != 0x005583) return;
    goto L_00554A;
}

void game::SUB_005589() {
    a = myMapper->readCPU(0x05BA + x);
    pushAddress(0x00558C);
    SUB_003048();
    if (poppedEntry.value != 0x00558C) return;
    pushAddress(0x00558F);
    SUB_0031D7();
    if (poppedEntry.value != 0x00558F) return;
    SUB_005592();
    return;
}

void game::SUB_005592() {
    popAddress();
}

void game::SUB_005593() {
    if (a != myMapper->readCPU(0x050B + x)) {
        goto L_005599;
    }
    popAddress();
    return;
L_005599:
    opPHA();
    a = myMapper->readCPU(0x050B + x);
    myMapper->writeCPU(0x048D, a);
    opPLA();
    myMapper->writeCPU(0x050B + x, a);
    popAddress();
}

void game::SUB_0055A5() {
    a = myMapper->readCPU(0x048E + x);
    opORA(0x20);
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x069B + x, 0xFF);
    myMapper->writeCPU(0x04F2 + x, 0x01);
    a = 0x12;
    pushAddress(0x0055B9);
    SUB_00206B();
    if (poppedEntry.value != 0x0055B9) return;
    SUB_0055BC();
    return;
}

void game::SUB_0055BC() {
    opINC(0x069B + x, 1);
    a = myMapper->readCPU(0x069B + x);
    if (x != 0x00) {
        opAND(0x0F);
        if (a == 0x04) {
            goto L_0055E2;
        }
        flgC = false;
        opADC(0x80);
    }
    else {
        opLSR_A(1);
        opAND(0x0F);
        if (a == 0x08) {
            goto L_0055E2;
        }
        flgC = false;
        opADC(0x90);
    }
    myMapper->writeCPU(0x04D9 + x, a);
    SUB_0051B5();
    return;
L_0055E2:
    if (x != 0x00) {
        goto L_00560F;
    }
    myMapper->writeCPU(0x04D9, 0x8F);
    pushAddress(0x0055EB);
    SUB_004275();
    if (poppedEntry.value != 0x0055EB) return;
    myMapper->writeCPU(0x0086, 0x5A);
    myMapper->writeCPU(0x0087, 0x00);
    pushAddress(0x0055F6);
    SUB_004251();
    if (poppedEntry.value != 0x0055F6) return;
    myMapper->writeCPU(0x048C, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x048E, a);
    myMapper->writeCPU(0x048F, a);
    myMapper->writeCPU(0x0490, a);
    myMapper->writeCPU(0x05EC, a);
    pushAddress(0x00560C);
    SUB_004237();
    if (poppedEntry.value != 0x00560C) return;
L_00560F:
    myMapper->writeCPU(0x048E + x, 0x00);
    SUB_0051B5();
    return;
}

void game::SUB_005617() {
    pushAddress(0x005617);
    SUB_00337B();
    if (poppedEntry.value != 0x005617) return;
    a = myMapper->readCPU(0x048E + x);
    opAND(0x80);
    if (flgZ) {
        goto L_005636;
    }
    myMapper->writeCPU(0x050B + x, 0x08);
    myMapper->writeCPU(0x05BA + x, 0x1E);
    myMapper->writeCPU(0x04D9 + x, 0x14);
    pushAddress(0x005630);
    SUB_005589();
    if (poppedEntry.value != 0x005630) return;
    while (true) {
        SUB_0051B5();
        return;
    L_005636:
        myMapper->writeCPU(0x04D9 + x, 0x8E);
    }
    SUB_00563E();
    return;
}

void game::SUB_00563E() {
    myMapper->writeCPU(0x04D9 + x, 0xA0);
    pushAddress(0x005643);
    SUB_004275();
    if (poppedEntry.value != 0x005643) return;
    do {
        a = 0x01;
        myMapper->writeCPU(0x0396, a);
        myMapper->writeCPU(0x0605 + x, a);
        a = 0x00;
        myMapper->writeCPU(0x0399, a);
        myMapper->writeCPU(0x0637 + x, a);
        a = 0x02;
        myMapper->writeCPU(0x0397, a);
        myMapper->writeCPU(0x061E + x, a);
        a = 0xD0;
        myMapper->writeCPU(0x039A, a);
        myMapper->writeCPU(0x0650 + x, a);
        pushAddress(0x005666);
        SUB_0030BC();
        if (poppedEntry.value != 0x005666) return;
        pushAddress(0x005669);
        SUB_002DC9();
        if (poppedEntry.value != 0x005669) return;
        myMapper->writeCPU(0x050B + x, a);
        a = 0x08;
        pushAddress(0x005671);
        SUB_003048();
        if (poppedEntry.value != 0x005671) return;
        pushAddress(0x005674);
        SUB_0031D7();
        if (poppedEntry.value != 0x005674) return;
        pushAddress(0x005677);
        SUB_004275();
        if (poppedEntry.value != 0x005677) return;
        pushAddress(0x00567A);
        SUB_003102();
        if (poppedEntry.value != 0x00567A) return;
        pushAddress(0x00567D);
        SUB_0030BC();
        if (poppedEntry.value != 0x00567D) return;
        pushAddress(0x005680);
        SUB_0029F4();
        if (poppedEntry.value != 0x005680) return;
    } while (!flgC);
    do {
        pushAddress(0x005685);
        SUB_004275();
        if (poppedEntry.value != 0x005685) return;
    } while (myMapper->readCPU(0x0437) != 0);
    a = myMapper->readCPU(0x048E);
    opORA(0x40);
    myMapper->writeCPU(0x048E, a);
    SUB_0050B5();
    return;
}

void game::SUB_005698() {
    myMapper->writeCPU(0x069B + x, 0xFF);
    pushAddress(0x00569D);
    SUB_00337B();
    if (poppedEntry.value != 0x00569D) return;
    a = myMapper->readCPU(0x048E + x);
    opAND(0x80);
    if (!flgZ) {
        goto L_0056AD;
    }
    pushAddress(0x0056A7);
    SUB_005589();
    if (poppedEntry.value != 0x0056A7) return;
    SUB_0051B5();
    return;
L_0056AD:
    a = myMapper->readCPU(0x048E + x);
    opAND(0xFD);
    opORA(0x04);
    myMapper->writeCPU(0x048E + x, a);
    SUB_0056B7();
    return;
}

void game::SUB_0056B7() {
    if (x != 0x01) {
        goto L_0056C1;
    }
    pushAddress(0x0056BB);
    SUB_00570E();
    if (poppedEntry.value != 0x0056BB) return;
    goto L_0056C4;
L_0056C1:
    pushAddress(0x0056C1);
    SUB_00572F();
    if (poppedEntry.value != 0x0056C1) return;
L_0056C4:
    myMapper->writeCPU(0x039A, myMapper->readCPU(0x053D));
    myMapper->writeCPU(0x0399, myMapper->readCPU(0x0524));
    pushAddress(0x0056D0);
    SUB_0030BC();
    if (poppedEntry.value != 0x0056D0) return;
    pushAddress(0x0056D3);
    SUB_002DC9();
    if (poppedEntry.value != 0x0056D3) return;
    myMapper->writeCPU(0x050B + x, a);
    pushAddress(0x0056D9);
    SUB_005589();
    if (poppedEntry.value != 0x0056D9) return;
    pushAddress(0x0056DC);
    SUB_00574E();
    if (poppedEntry.value != 0x0056DC) return;
    if (flgC) {
        goto L_0056F2;
    }
    opINC(0x069B + x, 1);
    a = myMapper->readCPU(0x069B + x);
    opAND(0x07);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x04D9 + x, a);
    SUB_0051B5();
    return;
L_0056F2:
    a = myMapper->readCPU(0x048E + x);
    opAND(0xFB);
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x050B + x, myMapper->readCPU(0x050B));
    myMapper->writeCPU(0x05BA + x, myMapper->readCPU(0x05BA));
    myMapper->writeCPU(0x04D9 + x, 0x01);
    SUB_0051FC();
    return;
}

void game::SUB_00570E() {
    a = myMapper->readCPU(0x0588);
    flgC = true;
    opSBC(0x15);
    if (flgC) {
        goto L_005725;
    }
    myMapper->writeCPU(0x0397, a);
    a = myMapper->readCPU(0x056F);
    flgC = true;
    opSBC(0x01);
    opAND(0x01);
    myMapper->writeCPU(0x0396, a);
    popAddress();
    return;
L_005725:
    myMapper->writeCPU(0x0397, a);
    myMapper->writeCPU(0x0396, myMapper->readCPU(0x056F));
    popAddress();
}

void game::SUB_00572F() {
    a = myMapper->readCPU(0x0588);
    flgC = false;
    opADC(0x15);
    if (!flgC) {
        goto L_005744;
    }
    myMapper->writeCPU(0x0397, a);
    a = myMapper->readCPU(0x056F);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0396, a);
    popAddress();
    return;
L_005744:
    myMapper->writeCPU(0x0397, a);
    myMapper->writeCPU(0x0396, myMapper->readCPU(0x056F));
    popAddress();
}

void game::SUB_00574E() {
    y = 0x00;
    pushAddress(0x005750);
    SUB_0030E5();
    if (poppedEntry.value != 0x005750) return;
    pushAddress(0x005753);
    SUB_0030BC();
    if (poppedEntry.value != 0x005753) return;
    myMapper->writeCPU(0x00B0, 0x30);
    myMapper->writeCPU(0x00B1, 0xD0);
    myMapper->writeCPU(0x00B2, 0x10);
    myMapper->writeCPU(0x00B3, 0xF0);
    SUB_002A00();
    return;
}

void game::SUB_005769() {
    a = myMapper->readCPU(0x053D);
    flgC = true;
    opSBC(0x10);
    if (flgC) {
        goto L_005785;
    }
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x053D + y, a);
    flgC = true;
    a = myMapper->readCPU(0x0524 + y);
    opSBC(0x01);
    opAND(0x01);
    myMapper->writeCPU(0x0524 + y, a);
    goto L_00578E;
L_005785:
    myMapper->writeCPU(0x053D + y, a);
    myMapper->writeCPU(0x0524 + y, myMapper->readCPU(0x0524));
L_00578E:
    myMapper->writeCPU(0x0588 + y, myMapper->readCPU(0x0588));
    myMapper->writeCPU(0x056F + y, myMapper->readCPU(0x056F));
    popAddress();
}

void game::SUB_00579B() {
    a = myMapper->readCPU(0x0437);
    opCMP(a, 0xFF);
    popAddress();
}

void game::SUB_0057A1() {
    a = 0xFF;
    myMapper->writeCPU(0x07C5, a);
    myMapper->writeCPU(0x0718, a);
    a = 0x00;
    myMapper->writeCPU(0x0439, a);
    myMapper->writeCPU(0x043A, a);
    myMapper->writeCPU(0x043B, a);
    myMapper->writeCPU(0x043C, a);
    a = myMapper->readCPU(0x008D);
    opAND(0xE7);
    myMapper->writeCPU(0x008D, a);
    pushAddress(0x0057BD);
    SUB_004275();
    if (poppedEntry.value != 0x0057BD) return;
    pushAddress(0x0057C0);
    SUB_006240();
    if (poppedEntry.value != 0x0057C0) return;
    if (myMapper->readCPU(0x07BC) != 0) {
        goto L_0057CD;
    }
    if (myMapper->readCPU(0x0437) == 0) {
        goto L_0057D3;
    }
L_0057CD:
    myMapper->writeCPU(0x03A1, myMapper->readCPU(0x0435));
L_0057D3:
    pushAddress(0x0057D3);
    SUB_000000();
    if (poppedEntry.value != 0x0057D3) return;
    pushAddress(0x0057D6);
    SUB_00273E();
    if (poppedEntry.value != 0x0057D6) return;
    a = 0x00;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, a);
    pushAddress(0x0057DF);
    SUB_002C14();
    if (poppedEntry.value != 0x0057DF) return;
    a = myMapper->readCPU(0x008D);
    opORA(0x18);
    myMapper->writeCPU(0x008D, a);
    pushAddress(0x0057E8);
    SUB_004275();
    if (poppedEntry.value != 0x0057E8) return;
    a = 0x08;
    pushAddress(0x0057ED);
    SUB_0041F5();
    if (poppedEntry.value != 0x0057ED) return;
    SUB_0057F0();
    return;
}

void game::SUB_0057F0() {
    a = 0x00;
    myMapper->writeCPU(0x0433, a);
    flgC = true;
    opSBC(myMapper->readCPU(0x03A1));
    opLSR_A(3);
    myMapper->writeCPU(0x0438, a);
    a = 0x20;
    flgC = true;
    opSBC(myMapper->readCPU(0x0438));
    myMapper->writeCPU(0x0434, a);
    while (true) {
        flgC = true;
        opSBC(0x0A);
        if (!flgC) {
            goto L_005816;
        }
        myMapper->writeCPU(0x0434, a);
        opINC(0x0433, 1);
    }
L_005816:
    if (myMapper->readCPU(0x07BC) == 0) {
        a = myMapper->readCPU(0x048E);
        opORA(0x40);
        myMapper->writeCPU(0x048E, a);
    }
    y = 0x01;
    do {
        do {
            a = myMapper->readCPU(0x048E + y);
            opAND(0x08);
            if (flgZ) {
                goto L_00584B;
            }
            a = myMapper->readCPU(0x048E + y);
            opAND(0xEF);
            opORA(0x02);
            myMapper->writeCPU(0x048E + y, a);
            myMapper->writeCPU(0x050B + y, 0x00);
            opINY(1);
        } while (y < 0x03);
        a = myMapper->readCPU(0x048E);
        opORA(0x04);
        myMapper->writeCPU(0x048E, a);
        goto L_005850;
    L_00584B:
        opINY(1);
    } while (y < 0x03);
L_005850:
    myMapper->writeCPU(0x0436, 0x03);
    x = 0x0B;
    a = 0x00;
    do {
        myMapper->writeCPU(0x048E + x, a);
        opINX(1);
    } while (x < 0x0E);
    a = 0x1A;
    pushAddress(0x005863);
    SUB_0041F5();
    if (poppedEntry.value != 0x005863) return;
    a = 0x1C;
    pushAddress(0x005868);
    SUB_0041F5();
    if (poppedEntry.value != 0x005868) return;
    pushAddress(0x00586B);
    SUB_003C86();
    if (poppedEntry.value != 0x00586B) return;
    if (myMapper->readCPU(0x0384) == 0) {
        if (myMapper->readCPU(0x0437) != 0) {
            a = 0x04;
            pushAddress(0x00587A);
            SUB_00206B();
            if (poppedEntry.value != 0x00587A) return;
            a = 0x05;
            pushAddress(0x00587F);
            SUB_00206B();
            if (poppedEntry.value != 0x00587F) return;
            a = 0x06;
            pushAddress(0x005884);
            SUB_00206B();
            if (poppedEntry.value != 0x005884) return;
            myMapper->writeCPU(0x00C9, 0x00);
        }
    }
    myMapper->writeCPU(0x071D, 0x0E);
    myMapper->writeCPU(0x071E, 0xAA);
    do {
        y = myMapper->readCPU(0x071D);
        myMapper->writeCPU(0x04D9 + y, myMapper->readCPU(0x071E));
        a = y;
        flgC = true;
        opSBC(0x0D);
        opASL_A(1);
        flgC = false;
        opADC(0x08);
        pushAddress(0x0058A6);
        SUB_0041F5();
        if (poppedEntry.value != 0x0058A6) return;
        opINC(0x071E, 1);
        opINC(0x071D, 1);
        a = myMapper->readCPU(0x071D);
    } while (a != 0x13);
    x = 0x00;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0xE25F + y));
        opINX(1);
        opINY(1);
    } while (y < 0x08);
    x = 0x01;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0x0433 + y));
        opINY(1);
        opINX(4);
    } while (y < 0x02);
    x = 0x08;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0xE267 + y));
        opINX(1);
        opINY(1);
    } while (y < 0x08);
    x = 0x09;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0x0431 + y));
        opINY(1);
        opINX(4);
    } while (y < 0x02);
    myMapper->writeCPU(0x078C, 0xFF);
    myMapper->writeCPU(0x070A, 0x3C);
    while (true) {
        opDEC(0x070A, 1);
        if (flgZ) {
            goto L_005924;
        }
        pushAddress(0x00590B);
        SUB_005E82();
        if (poppedEntry.value != 0x00590B) return;
        myMapper->writeCPU(0x03A7, 0x40);
        a = 0xFF;
        myMapper->writeCPU(0x03A8, a);
        myMapper->writeCPU(0x03A9, a);
        pushAddress(0x00591B);
        SUB_00004C();
        if (poppedEntry.value != 0x00591B) return;
        pushAddress(0x00591E);
        SUB_004275();
        if (poppedEntry.value != 0x00591E) return;
    }
L_005924:
    if (myMapper->readCPU(0x0437) == 0) {
        while (true) {
            a = myMapper->readCPU(0x048E);
            opAND(0x40);
            if (flgZ) {
                goto L_005946;
            }
            myMapper->writeCPU(0x03A7, 0x40);
            a = 0xFF;
            myMapper->writeCPU(0x03A8, a);
            myMapper->writeCPU(0x03A9, a);
            pushAddress(0x00593D);
            SUB_00004C();
            if (poppedEntry.value != 0x00593D) return;
            pushAddress(0x005940);
            SUB_004275();
            if (poppedEntry.value != 0x005940) return;
        }
    }
L_005946:
    myMapper->writeCPU(0x071D, 0x0E);
    do {
        y = myMapper->readCPU(0x071D);
        myMapper->writeCPU(0x048E + y, 0x00);
        a = y;
        flgC = true;
        opSBC(0x0D);
        opASL_A(1);
        flgC = false;
        opADC(0x08);
        pushAddress(0x00595B);
        SUB_004240();
        if (poppedEntry.value != 0x00595B) return;
        opINC(0x071D, 1);
        a = myMapper->readCPU(0x071D);
    } while (a != 0x13);
    pushAddress(0x005968);
    SUB_004275();
    if (poppedEntry.value != 0x005968) return;
    myMapper->writeCPU(0x078C, 0x00);
    a = myMapper->readCPU(0x03A1);
    opLSR_A(2);
    opAND(0x3E);
    y = a;
    myMapper->writeCPU(0x00D4, myMapper->readCPU(0xE26F + y));
    opINY(1);
    myMapper->writeCPU(0x00D5, myMapper->readCPU(0xE26F + y));
    if (myMapper->readCPU(0x03A1) == 0) {
        goto L_0059AF;
    }
    while (true) {
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x00D4) + (myMapper->readCPU((0x00D4 + 1) & 0x00ff) << 8) + y);
        opAND(0x07);
        myMapper->writeCPU(0x00B0, a);
        a = myMapper->readCPU(0x03A1);
        opAND(0x07);
        myMapper->writeCPU(0x00B1, a);
        a = myMapper->readCPU(0x00B0);
        opCMP(a, myMapper->readCPU(0x00B1));
        if (flgZ) {
            goto L_0059AF;
        }
        if (!flgC) {
            goto L_0059AF;
        }
        a = myMapper->readCPU(0x00D4);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x00D4, a);
        a = myMapper->readCPU(0x00D5);
        opADC(0x00);
        myMapper->writeCPU(0x00D5, a);
    }
L_0059AF:
    pushAddress(0x0059AF);
    SUB_005E92();
    if (poppedEntry.value != 0x0059AF) return;
    while (true) {
        while (true) {
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00D4) + (myMapper->readCPU((0x00D4 + 1) & 0x00ff) << 8) + y);
            opAND(0x07);
            myMapper->writeCPU(0x00B0, a);
            a = myMapper->readCPU(0x03A1);
            opAND(0x07);
            myMapper->writeCPU(0x00B1, a);
            a = myMapper->readCPU(0x00B0);
            opCMP(a, myMapper->readCPU(0x00B1));
            if (!flgZ) {
                if (flgC) {
                    goto L_0059CC;
                }
                goto L_005A81;
            L_0059CC:
                goto L_005A71;
            }
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00D4) + (myMapper->readCPU((0x00D4 + 1) & 0x00ff) << 8) + y);
            if (a < myMapper->readCPU(0x03A0)) {
                goto L_005A81;
            }
            y = 0x00;
            while (true) {
                a = myMapper->readCPU(0x06CD + y);
                if (a == 0xFF) {
                    goto L_0059F2;
                }
                a = y;
                flgC = false;
                opADC(0x05);
                if (a < 0x3C) {
                    goto L_0059EE;
                }
                goto L_005A81;
            L_0059EE:
                y = a;
            }
        L_0059F2:
            myMapper->writeCPU(0x071E, y);
            y = 0x02;
            a = myMapper->readCPU(myMapper->readCPU(0x00D4) + (myMapper->readCPU((0x00D4 + 1) & 0x00ff) << 8) + y);
            if (a >= 0x10) {
                if (a >= 0x27) {
                    goto L_005A1E;
                }
                myMapper->writeCPU(0x00B0, a);
                x = 0x00;
                do {
                    a = myMapper->readCPU(0xEBF5 + x);
                    if (a == myMapper->readCPU(0x00B0)) {
                        goto L_005A14;
                    }
                    opINX(1);
                } while (x < 0x05);
                goto L_005A1C;
            L_005A14:
                myMapper->writeCPU(0x0717, 0x00);
                pushAddress(0x005A19);
                SUB_005E92();
                if (poppedEntry.value != 0x005A19) return;
            L_005A1C:
                a = myMapper->readCPU(0x00B0);
            }
        L_005A1E:
            opASL_A(2);
            y = a;
            myMapper->writeCPU(0x00B1, myMapper->readCPU(0xEB19 + y));
            opINY(1);
            myMapper->writeCPU(0x00B2, myMapper->readCPU(0xEB19 + y));
            opINY(1);
            myMapper->writeCPU(0x00B3, myMapper->readCPU(0xEB19 + y));
            opINY(1);
            myMapper->writeCPU(0x00B4, myMapper->readCPU(0xEB19 + y));
            y = myMapper->readCPU(0x071E);
            myMapper->writeCPU(0x06CD + y, myMapper->readCPU(0x00B1));
            opINY(1);
            a = myMapper->readCPU(0x00B2);
            myMapper->writeCPU(0x06CD + y, a);
            opINY(1);
            myMapper->writeCPU(0x06CD + y, a);
            opINY(1);
            myMapper->writeCPU(0x06CD + y, myMapper->readCPU(0x00B3));
            opINY(1);
            myMapper->writeCPU(0x06CD + y, myMapper->readCPU(0x00B4));
            y = 0x02;
            a = myMapper->readCPU(myMapper->readCPU(0x00D4) + (myMapper->readCPU((0x00D4 + 1) & 0x00ff) << 8) + y);
            if (a >= 0x10) {
                goto L_005A71;
            }
            myMapper->writeCPU(0x0709, a);
            opASL_A(2);
            y = a;
            myMapper->writeCPU(0x070A, myMapper->readCPU(0xEBDD + y));
            opINY(1);
            myMapper->writeCPU(0x070B, myMapper->readCPU(0xEBDD + y));
        L_005A71:
            a = myMapper->readCPU(0x00D4);
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x00D4, a);
            a = myMapper->readCPU(0x00D5);
            opADC(0x00);
            myMapper->writeCPU(0x00D5, a);
        }
    L_005A81:
        myMapper->writeCPU(0x071E, 0x00);
        do {
            y = myMapper->readCPU(0x071E);
            a = myMapper->readCPU(0x06CD + y);
            if (a == 0xFF) {
                goto L_005A9C;
            }
            opINY(1);
            a = myMapper->readCPU(0x06CD + y);
            flgC = true;
            opSBC(0x01);
            if (flgZ) {
                goto L_005AAC;
            }
            myMapper->writeCPU(0x06CD + y, a);
        L_005A9C:
            a = myMapper->readCPU(0x071E);
            flgC = false;
            opADC(0x05);
            myMapper->writeCPU(0x071E, a);
        } while (a < 0x3C);
        goto L_005B42;
    L_005AAC:
        opINY(1);
        a = myMapper->readCPU(0x06CD + y);
        opDEY(1);
        myMapper->writeCPU(0x06CD + y, a);
        a = myMapper->readCPU(0x071E);
        flgC = false;
        opADC(0x03);
        y = a;
        myMapper->writeCPU(0x071B, myMapper->readCPU(0x06CD + y));
        y = 0x0E;
        do {
            a = myMapper->readCPU(0x048E + y);
            opAND(0x08);
            if (flgZ) {
                goto L_005AD3;
            }
        L_005ACB:
            opINY(1);
        } while (y < 0x16);
        goto L_005B23;
    L_005AD3:
        myMapper->writeCPU(0x071D, y);
        y = myMapper->readCPU(0x071E);
        a = myMapper->readCPU(0x06CD + y);
        y = myMapper->readCPU(0x071D);
        myMapper->writeCPU(0x05D3 + y, a);
        a = myMapper->readCPU(0x048E + y);
        opORA(0x08);
        myMapper->writeCPU(0x048E + y, a);
        a = y;
        flgC = true;
        opSBC(0x0D);
        opASL_A(1);
        flgC = false;
        opADC(0x08);
        pushAddress(0x005AF2);
        SUB_0041F5();
        if (poppedEntry.value != 0x005AF2) return;
        y = myMapper->readCPU(0x071D);
        opDEC(0x071B, 1);
        if (!flgZ) {
            goto L_005ACB;
        }
        a = myMapper->readCPU(0x071E);
        flgC = false;
        opADC(0x04);
        y = a;
        a = myMapper->readCPU(0x06CD + y);
        opDEY(1);
        flgC = true;
        opSBC(myMapper->readCPU(0x06CD + y));
        if (flgC) {
            if (flgZ) {
                goto L_005B18;
            }
            opINY(1);
            myMapper->writeCPU(0x06CD + y, a);
            goto L_005A9C;
        }
        do {
            do {
            L_005B18:
                y = myMapper->readCPU(0x071E);
                myMapper->writeCPU(0x06CD + y, 0xFF);
                goto L_005A9C;
            L_005B23:
                a = myMapper->readCPU(0x071E);
                flgC = false;
                opADC(0x03);
                y = a;
                a = myMapper->readCPU(0x06CD + y);
                flgC = true;
                opSBC(myMapper->readCPU(0x071B));
                myMapper->writeCPU(0x00B0, a);
                opINY(1);
                a = myMapper->readCPU(0x06CD + y);
                flgC = true;
                opSBC(myMapper->readCPU(0x00B0));
            } while (!flgC);
        } while (flgZ);
        myMapper->writeCPU(0x06CD + y, a);
    L_005B42:
        a = myMapper->readCPU(0x070A);
        opORA(myMapper->readCPU(0x070B));
        if (!flgZ) {
            opDEC(0x070A, 1);
            a = myMapper->readCPU(0x070A);
            if (a != 0xFF) {
                goto L_005B72;
            }
            opDEC(0x070B, 1);
        }
        else {
            myMapper->writeCPU(0x070C, 0x01);
            a = myMapper->readCPU(0x0709);
            opASL_A(2);
            y = a;
            myMapper->writeCPU(0x070A, myMapper->readCPU(0xEBDD + y));
            opINY(1);
            myMapper->writeCPU(0x070B, myMapper->readCPU(0xEBDD + y));
        }
    L_005B72:
        a = myMapper->readCPU(0x0718);
        if (a == 0xFF) {
        }
        else {
            if (a == 0x00) {
                goto L_005B92;
            }
            if (a == 0x01) {
                goto L_005BA3;
            }
            if (a == 0x02) {
                goto L_005BBC;
            }
            if (a == 0x03) {
                goto L_005B9D;
            }
            pushAddress(0x005B8C);
            SUB_002D0E();
            if (poppedEntry.value != 0x005B8C) return;
            goto L_005C01;
        L_005B92:
            a = myMapper->readCPU(0x048E);
            opORA(0x02);
            myMapper->writeCPU(0x048E, a);
            goto L_005C01;
        L_005B9D:
            pushAddress(0x005B9D);
            SUB_006229();
            if (poppedEntry.value != 0x005B9D) return;
            goto L_005C01;
        L_005BA3:
            y = 0x0E;
            while (true) {
                if (y == 0x16) {
                    goto L_005C01;
                }
                a = myMapper->readCPU(0x048E + y);
                opAND(0x08);
                if (flgZ) {
                    goto L_005BB8;
                }
                a = myMapper->readCPU(0x048E + y);
                opORA(0x01);
                myMapper->writeCPU(0x048E + y, a);
            L_005BB8:
                opINY(1);
            }
        L_005BBC:
            if (!(myMapper->readCPU(0x048F) & 0x80)) {
                if (myMapper->readCPU(0x0490) & 0x80) {
                    goto L_005C01;
                }
                y = 0x01;
                myMapper->writeCPU(0x056F + y, 0x00);
                myMapper->writeCPU(0x0588 + y, 0xE0);
                opINY(1);
                myMapper->writeCPU(0x056F + y, 0x01);
                myMapper->writeCPU(0x0588 + y, 0x20);
                opDEY(1);
                do {
                    myMapper->writeCPU(0x048E + y, 0x0A);
                    myMapper->writeCPU(0x053D + y, 0x50);
                    myMapper->writeCPU(0x0524 + y, 0x00);
                    myMapper->writeCPU(0x050B + y, 0x08);
                    myMapper->writeCPU(0x05BA + y, 0x1E);
                    myMapper->writeCPU(0x04F2 + y, 0x03);
                    opINY(1);
                } while (y < 0x03);
            }
        }
    L_005C01:
        myMapper->writeCPU(0x0718, 0xFF);
        if (myMapper->readCPU(0x0446) == 0) {
            a = myMapper->readCPU(0x0447);
            if (a < 0xC8) {
                goto L_005C2E;
            }
            a = 0x1E;
            pushAddress(0x005C14);
            SUB_0041F5();
            if (poppedEntry.value != 0x005C14) return;
            opINC(0x0446, 1);
        }
        else {
            a = myMapper->readCPU(0x0447);
            if (a < 0x96) {
                goto L_005C2E;
            }
            a = 0x1E;
            pushAddress(0x005C26);
            SUB_0041F5();
            if (poppedEntry.value != 0x005C26) return;
        }
        myMapper->writeCPU(0x0447, 0x00);
    L_005C2E:
        if (myMapper->readCPU(0x0384) != 0) {
            if (myMapper->readCPU(0x0783) != 0) {
                goto L_005C46;
            }
            y = myMapper->readCPU(0x0784);
            opINY(1);
            myMapper->writeCPU(0x0783, myMapper->readCPU(0xE26F + y));
            opINY(1);
            myMapper->writeCPU(0x0784, y);
        L_005C46:
            opDEC(0x0783, 1);
            y = myMapper->readCPU(0x0784);
            a = myMapper->readCPU(0xE26F + y);
            SUB_005E8E();
            return;
        }
        while (true) {
            pushAddress(0x005C72);
            SUB_005E82();
            if (poppedEntry.value != 0x005C72) return;
            a = myMapper->readCPU(0x048C);
            if (a == 0xFF) {
                SUB_0061E0();
                return;
            }
            a = myMapper->readCPU(0x03A1);
            opAND(0x07);
            if (flgZ) {
                a = myMapper->readCPU(0x03A0);
                if (a < 0x81) {
                    if (a < 0x71) {
                        goto L_005CB0;
                    }
                    y = 0x03;
                    a = 0x00;
                    do {
                        myMapper->writeCPU(0x048E + y, a);
                        opINY(1);
                    } while (y < 0x0B);
                    y = 0x0E;
                    do {
                        a = myMapper->readCPU(0x048E + y);
                        setLoadFlag(a);
                        if (flgZ) {
                            goto L_005CA9;
                        }
                        opORA(0x01);
                        myMapper->writeCPU(0x048E + y, a);
                    L_005CA9:
                        opINY(1);
                        opCMP(y, 0x16);
                    } while (!flgC);
                    if (flgC) {
                        goto L_005CBD;
                    }
                L_005CB0:
                    pushAddress(0x005CB0);
                    SUB_005E5C();
                    if (poppedEntry.value != 0x005CB0) return;
                    a = myMapper->readCPU(0x03A0);
                    if (a < 0x61) {
                        SUB_005E9D();
                        return;
                    }
                }
            }
        L_005CBD:
            if (myMapper->readCPU(0x0384) == 0) {
                a = myMapper->readCPU(0x0098);
                opAND(0x10);
                if (!flgZ) {
                    goto L_005CCB;
                }
            }
            goto L_005D45;
        L_005CCB:
            y = 0x00;
            do {
                myMapper->writeCPU(0x0230 + y, myMapper->readCPU(0xE24B + y));
                opINY(1);
            } while (y != 0x14);
            a = 0xFF;
            do {
                myMapper->writeCPU(0x0230 + y, a);
                opINY(1);
            } while (y != 0xC8);
            a = 0x06;
            do {
                pushAddress(0x005CE4);
                SUB_0042A4();
                if (poppedEntry.value != 0x005CE4) return;
                flgC = false;
                opADC(0x02);
            } while (a != 0x20);
            a = 0x03;
            pushAddress(0x005CF0);
            SUB_00206B();
            if (poppedEntry.value != 0x005CF0) return;
        L_005CF3:
            pushAddress(0x005CF3);
            SUB_004275();
            if (poppedEntry.value != 0x005CF3) return;
            y = 0x05;
            a = 0x03;
            do {
                if (a == myMapper->readCPU(0x0746 + y)) {
                    goto L_005CF3;
                }
                opDEY(1);
            } while (!flgN);
            a = 0x00;
            pushAddress(0x005D04);
            SUB_00206B();
            if (poppedEntry.value != 0x005D04) return;
            a = 0x01;
            pushAddress(0x005D09);
            SUB_00206B();
            if (poppedEntry.value != 0x005D09) return;
            a = 0x02;
            pushAddress(0x005D0E);
            SUB_00206B();
            if (poppedEntry.value != 0x005D0E) return;
            pushAddress(0x005D11);
            SUB_0020D0();
            if (poppedEntry.value != 0x005D11) return;
            do {
                pushAddress(0x005D14);
                SUB_004275();
                if (poppedEntry.value != 0x005D14) return;
                myMapper->writeCPU(0x038D, 0xFF);
                a = myMapper->readCPU(0x0098);
                opAND(0x10);
            } while (!flgZ);
            do {
                pushAddress(0x005D22);
                SUB_004275();
                if (poppedEntry.value != 0x005D22) return;
                a = myMapper->readCPU(0x0098);
                opAND(0x10);
            } while (flgZ);
            do {
                pushAddress(0x005D2B);
                SUB_004275();
                if (poppedEntry.value != 0x005D2B) return;
                a = myMapper->readCPU(0x0098);
                opAND(0x10);
            } while (!flgZ);
            a = 0x06;
            do {
                pushAddress(0x005D36);
                SUB_004288();
                if (poppedEntry.value != 0x005D36) return;
                flgC = false;
                opADC(0x02);
            } while (a != 0x20);
            myMapper->writeCPU(0x038D, 0x00);
        L_005D45:
            if (myMapper->readCPU(0x0437) != 0) {
                if (myMapper->readCPU(0x00C9) != 0) {
                    goto L_005D63;
                }
                a = 0x06;
                pushAddress(0x005D50);
                SUB_00205B();
                if (poppedEntry.value != 0x005D50) return;
                if (!flgC) {
                    myMapper->writeCPU(0x00C9, 0xFF);
                    a = 0x0E;
                    pushAddress(0x005D5B);
                    SUB_00206B();
                    if (poppedEntry.value != 0x005D5B) return;
                    a = 0x16;
                    pushAddress(0x005D60);
                    SUB_00206B();
                    if (poppedEntry.value != 0x005D60) return;
                }
            }
        L_005D63:
            a = myMapper->readCPU(0x078D);
            if (a == 0xFF) {
                goto L_005E42;
            }
            if (a != 0x01) {
                if (a != 0x02) {
                    goto L_005D78;
                }
                goto L_005DEB;
            L_005D78:
                y = 0x00;
                do {
                    a = myMapper->readCPU(0x03A1);
                    if (a == myMapper->readCPU(0xDE58 + y)) {
                        goto L_005D8A;
                    }
                    opINY(1);
                } while (y < 0x04);
                goto L_005E42;
            L_005D8A:
                myMapper->writeCPU(0x078D, 0x01);
                y = 0x0E;
                do {
                    a = myMapper->readCPU(0x048E + y);
                    opORA(0x01);
                    myMapper->writeCPU(0x048E + y, a);
                    opINY(1);
                } while (y < 0x16);
                pushAddress(0x005D9E);
                SUB_005E92();
                if (poppedEntry.value != 0x005D9E) return;
            }
            pushAddress(0x005DA1);
            SUB_005E5C();
            if (poppedEntry.value != 0x005DA1) return;
            a = myMapper->readCPU(0x03A0);
            if (a >= 0x90) {
                goto L_005E42;
            }
            pushAddress(0x005DAE);
            SUB_004275();
            if (poppedEntry.value != 0x005DAE) return;
            y = 0x0E;
            myMapper->writeCPU(0x048E + y, 0x08);
            myMapper->writeCPU(0x05D3 + y, 0xFF);
            myMapper->writeCPU(0x04D9 + y, 0x8E);
            myMapper->writeCPU(0x05BA + y, 0x04);
            a = 0x00;
            myMapper->writeCPU(0x056F + y, a);
            myMapper->writeCPU(0x0524 + y, a);
            myMapper->writeCPU(0x05EC + y, a);
            myMapper->writeCPU(0x0588 + y, 0xF8);
            myMapper->writeCPU(0x053D + y, 0x40);
            a = 0x0A;
            pushAddress(0x005DDE);
            SUB_0041F5();
            if (poppedEntry.value != 0x005DDE) return;
            myMapper->writeCPU(0x078D, 0x02);
            myMapper->writeCPU(0x078E, 0x00);
        L_005DEB:
            a = myMapper->readCPU(0x078E);
            opAND(0x01);
            if (flgZ) {
                a = 0xFF;
                myMapper->writeCPU(0x03A8, a);
                myMapper->writeCPU(0x03A9, a);
                pushAddress(0x005DFA);
                SUB_00004C();
                if (poppedEntry.value != 0x005DFA) return;
                myMapper->writeCPU(0x0519, 0x08);
                a = myMapper->readCPU(0x03A0);
                if (a >= 0xE8) {
                    goto L_005E2C;
                }
            }
            else {
                myMapper->writeCPU(0x03A8, 0x01);
                myMapper->writeCPU(0x03A9, 0x00);
                pushAddress(0x005E16);
                SUB_00004C();
                if (poppedEntry.value != 0x005E16) return;
                myMapper->writeCPU(0x0519, 0x00);
                a = myMapper->readCPU(0x03A0);
                if (a < 0xE8) {
                    if (a >= 0x30) {
                        goto L_005E2C;
                    }
                    goto L_005E2F;
                L_005E2C:
                    opINC(0x078E, 1);
                }
            }
        L_005E2F:
            a = myMapper->readCPU(0x049C);
            opORA(0x08);
            myMapper->writeCPU(0x049C, a);
            pushAddress(0x005E37);
            SUB_004275();
            if (poppedEntry.value != 0x005E37) return;
        }
    L_005E42:
        myMapper->writeCPU(0x03A7, 0x40);
        a = 0xFF;
        myMapper->writeCPU(0x03A8, a);
        myMapper->writeCPU(0x03A9, a);
        pushAddress(0x005E4F);
        SUB_00004C();
        if (poppedEntry.value != 0x005E4F) return;
        pushAddress(0x005E52);
        SUB_004275();
        if (poppedEntry.value != 0x005E52) return;
    }
    SUB_005E5C();
    return;
}

void game::SUB_005E5C() {
    y = 0x01;
    do {
        a = myMapper->readCPU(0x048E + y);
        opAND(0x10);
        if (!flgZ) {
            goto L_005E81;
        }
        a = myMapper->readCPU(0x048E + y);
        opAND(0x08);
        if (flgZ) {
            goto L_005E74;
        }
        a = myMapper->readCPU(0x048E + y);
        opORA(0x10);
        myMapper->writeCPU(0x048E + y, a);
    L_005E74:
        opINY(1);
    } while (y < 0x03);
    a = myMapper->readCPU(0x048E);
    opAND(0xFB);
    myMapper->writeCPU(0x048E, a);
L_005E81:
    popAddress();
}

void game::SUB_005E82() {
    if (myMapper->readCPU(0x0386) != 0) {
        goto L_005E8C;
    }
    a = myMapper->readCPU(0x0098);
    SUB_005E8E();
    return;
L_005E8C:
    a = myMapper->readCPU(0x009A);
    SUB_005E8E();
    return;
}

void game::SUB_005E8E() {
    myMapper->writeCPU(0x0785, a);
    popAddress();
}

void game::SUB_005E92() {
    x = 0x3C;
    a = 0xFF;
    do {
        myMapper->writeCPU(0x06CD + x, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_005E9D() {
    myMapper->writeCPU(0x0437, 0xFF);
    pushAddress(0x005EA2);
    SUB_004275();
    if (poppedEntry.value != 0x005EA2) return;
    pushAddress(0x005EA5);
    SUB_004306();
    if (poppedEntry.value != 0x005EA5) return;
    x = 0x0B;
    a = 0x00;
    do {
        myMapper->writeCPU(0x048E + x, a);
        opINX(1);
    } while (x < 0x0E);
    do {
        pushAddress(0x005EB4);
        SUB_004275();
        if (poppedEntry.value != 0x005EB4) return;
        if (myMapper->readCPU(0x048C) == 0) {
            goto L_005EC4;
        }
        myMapper->writeCPU(0x0437, 0x00);
        SUB_0061E0();
        return;
    L_005EC4:
        a = myMapper->readCPU(0x04D9);
    } while (a != 0xA0);
    pushAddress(0x005ECB);
    SUB_0028AE();
    if (poppedEntry.value != 0x005ECB) return;
    a = myMapper->readCPU(0x038B);
    setLoadFlag(a);
    if (flgZ) {
        a = 0xFF;
    }
    myMapper->writeCPU(0x0720, a);
    myMapper->writeCPU(0x0721, myMapper->readCPU(0x008B));
    myMapper->writeCPU(0x0722, myMapper->readCPU(0x008A));
    y = 0x00;
    do {
        myMapper->writeCPU(0x0230 + y, myMapper->readCPU(0xE1AC + y));
        opINY(1);
    } while (y < 0x0C);
    x = 0x01;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0x0720 + y));
        opINY(1);
        opINX(4);
    } while (y < 0x03);
    a = myMapper->readCPU(0x0720);
    if (a != 0xFF) {
        if (a < 0x01) {
            goto L_005F10;
        }
        goto L_005FFD;
    }
L_005F10:
    a = myMapper->readCPU(0x0722);
    if (a < 0x05) {
        a = myMapper->readCPU(0x0721);
        flgC = true;
        opSBC(0x05);
        if (!flgC) {
            goto L_005FE6;
        }
        opASL_A(3);
        y = a;
        myMapper->writeCPU(0x0089, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x0088, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x008B, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x008A, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x00E0, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x00DF, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x00DE, myMapper->readCPU(0xDF58 + y));
        opINY(1);
        myMapper->writeCPU(0x00DD, myMapper->readCPU(0xDF58 + y));
        goto L_006013;
    }
    a = myMapper->readCPU(0x0721);
    flgC = true;
    opSBC(0x05);
    if (flgC) {
        opASL_A(3);
        y = a;
        myMapper->writeCPU(0x0089, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x0088, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x008B, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x008A, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x00E0, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x00DF, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x00DE, myMapper->readCPU(0xDFBE + y));
        opINY(1);
        myMapper->writeCPU(0x00DD, myMapper->readCPU(0xDFBE + y));
        goto L_006013;
    }
L_005FE6:
    a = 0x00;
    myMapper->writeCPU(0x0089, a);
    myMapper->writeCPU(0x0088, a);
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, a);
    a = 0xFF;
    myMapper->writeCPU(0x00E0, a);
    myMapper->writeCPU(0x00DF, a);
    myMapper->writeCPU(0x00DE, a);
    myMapper->writeCPU(0x00DD, a);
    goto L_006013;
L_005FFD:
    myMapper->writeCPU(0x0089, 0x0A);
    myMapper->writeCPU(0x00E0, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x008A, a);
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x0088, a);
    myMapper->writeCPU(0x00DD, a);
    myMapper->writeCPU(0x00DE, a);
    myMapper->writeCPU(0x00DF, a);
L_006013:
    myMapper->writeCPU(0x00D6, myMapper->readCPU(0x00E0));
    myMapper->writeCPU(0x00D7, myMapper->readCPU(0x00DF));
    myMapper->writeCPU(0x00D8, myMapper->readCPU(0x00DE));
    myMapper->writeCPU(0x00D9, myMapper->readCPU(0x00DD));
    y = 0x00;
    x = 0x0C;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0xE1B8 + y));
        opINX(1);
        opINY(1);
    } while (y < 0x18);
    y = 0x00;
    x = 0x0D;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0x00D6 + y));
        opINY(1);
        opINX(4);
    } while (y < 0x04);
    pushAddress(0x006046);
    SUB_002C1A();
    if (poppedEntry.value != 0x006046) return;
    a = 0x00;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x008A, a);
    a = myMapper->readCPU(0x0436);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x0087, a);
        do {
            pushAddress(0x006056);
            SUB_002816();
            if (poppedEntry.value != 0x006056) return;
            opDEC(0x0087, 1);
        } while (!flgZ);
    }
    a = myMapper->readCPU(0x008B);
    myMapper->writeCPU(0x0089, a);
    myMapper->writeCPU(0x00D6, a);
    a = myMapper->readCPU(0x008A);
    myMapper->writeCPU(0x0088, a);
    myMapper->writeCPU(0x00D7, a);
    a = 0x00;
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x00D8, a);
    myMapper->writeCPU(0x008A, a);
    myMapper->writeCPU(0x00D9, a);
    y = 0x00;
    x = 0x24;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0xE1D0 + y));
        opINX(1);
        opINY(1);
    } while (y < 0x10);
    y = 0x01;
    x = 0x25;
    do {
        myMapper->writeCPU(0x0230 + x, myMapper->readCPU(0x00D6 + y));
        opINY(1);
        opINX(4);
    } while (y < 0x05);
    pushAddress(0x006096);
    SUB_002C1A();
    if (poppedEntry.value != 0x006096) return;
    myMapper->writeCPU(0x071D, 0x0E);
    myMapper->writeCPU(0x071E, 0x02);
    do {
        y = myMapper->readCPU(0x071D);
        myMapper->writeCPU(0x04D9 + y, myMapper->readCPU(0x071E));
        a = y;
        flgC = true;
        opSBC(0x0D);
        opASL_A(1);
        flgC = false;
        opADC(0x08);
        pushAddress(0x0060B4);
        SUB_0041F5();
        if (poppedEntry.value != 0x0060B4) return;
        opINC(0x071E, 1);
        opINC(0x071D, 1);
        a = myMapper->readCPU(0x071D);
    } while (a != 0x13);
    myMapper->writeCPU(0x078C, 0x80);
    myMapper->writeCPU(0x070A, 0x3C);
    while (true) {
        opDEC(0x070A, 1);
        if (flgZ) {
            goto L_0060E9;
        }
        myMapper->writeCPU(0x03A7, 0x40);
        a = 0xFF;
        myMapper->writeCPU(0x03A8, a);
        myMapper->writeCPU(0x03A9, a);
        pushAddress(0x0060E0);
        SUB_00004C();
        if (poppedEntry.value != 0x0060E0) return;
        pushAddress(0x0060E3);
        SUB_004275();
        if (poppedEntry.value != 0x0060E3) return;
    }
L_0060E9:
    myMapper->writeCPU(0x071D, 0x0E);
    do {
        y = myMapper->readCPU(0x071D);
        myMapper->writeCPU(0x048E + y, 0x00);
        a = y;
        flgC = true;
        opSBC(0x0D);
        opASL_A(1);
        flgC = false;
        opADC(0x08);
        pushAddress(0x0060FE);
        SUB_004240();
        if (poppedEntry.value != 0x0060FE) return;
        opINC(0x071D, 1);
        a = myMapper->readCPU(0x071D);
    } while (a != 0x13);
    a = 0x00;
    myMapper->writeCPU(0x078C, a);
    myMapper->writeCPU(0x0439, a);
    myMapper->writeCPU(0x043A, a);
    myMapper->writeCPU(0x043B, a);
    myMapper->writeCPU(0x043C, a);
    do {
        a = 0x10;
        pushAddress(0x00611E);
        SUB_00205B();
        if (poppedEntry.value != 0x00611E) return;
    } while (flgC);
    pushAddress(0x006123);
    SUB_001FDB();
    if (poppedEntry.value != 0x006123) return;
    pushAddress(0x006126);
    SUB_004275();
    if (poppedEntry.value != 0x006126) return;
    a = 0x0B;
    pushAddress(0x00612B);
    SUB_00206B();
    if (poppedEntry.value != 0x00612B) return;
    a = 0x0C;
    pushAddress(0x006130);
    SUB_00206B();
    if (poppedEntry.value != 0x006130) return;
    a = 0x0D;
    pushAddress(0x006135);
    SUB_00206B();
    if (poppedEntry.value != 0x006135) return;
    do {
        a = 0x0D;
        pushAddress(0x00613A);
        SUB_00205B();
        if (poppedEntry.value != 0x00613A) return;
    } while (flgC);
    myMapper->writeCPU(0x0087, 0x00);
    myMapper->writeCPU(0x0086, 0x78);
    pushAddress(0x006147);
    SUB_004251();
    if (poppedEntry.value != 0x006147) return;
    if (myMapper->readCPU(0x03A1) == 0) {
        goto L_00615D;
    }
    a = 0x00;
    myMapper->writeCPU(0x0437, a);
    myMapper->writeCPU(0x078D, a);
    pushAddress(0x006157);
    SUB_00273E();
    if (poppedEntry.value != 0x006157) return;
    SUB_0057F0();
    return;
L_00615D:
    myMapper->writeCPU(0x0385, 0x00);
    a = 0x08;
    pushAddress(0x006164);
    SUB_004240();
    if (poppedEntry.value != 0x006164) return;
    pushAddress(0x006167);
    SUB_004306();
    if (poppedEntry.value != 0x006167) return;
    pushAddress(0x00616A);
    SUB_006240();
    if (poppedEntry.value != 0x00616A) return;
    pushAddress(0x00616D);
    SUB_003CF1();
    if (poppedEntry.value != 0x00616D) return;
    myMapper->writeCPU(0x00DD, 0x9E);
    myMapper->writeCPU(0x00DE, 0xE1);
    myMapper->writeCPU(0x00DF, 0xC9);
    myMapper->writeCPU(0x00E0, 0x21);
    myMapper->writeCPU(0x00E2, 0x0E);
    pushAddress(0x006184);
    SUB_003CBF();
    if (poppedEntry.value != 0x006184) return;
    myMapper->writeCPU(0x0086, 0x1E);
    a = 0x00;
    myMapper->writeCPU(0x0087, a);
    myMapper->writeCPU(0x0431, a);
    myMapper->writeCPU(0x0432, a);
    myMapper->writeCPU(0x07C5, a);
    pushAddress(0x006198);
    SUB_004251();
    if (poppedEntry.value != 0x006198) return;
    SUB_0061E0();
    return;
}

void game::SUB_0061E0() {
    opINC(0x0437, 1);
    myMapper->writeCPU(0x078D, 0x00);
    pushAddress(0x0061E8);
    SUB_001FDB();
    if (poppedEntry.value != 0x0061E8) return;
    pushAddress(0x0061EB);
    SUB_004275();
    if (poppedEntry.value != 0x0061EB) return;
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x03A1));
    myMapper->writeCPU(0x0086, a);
    opAND(0x07);
    if (flgZ) {
        goto L_006202;
    }
    if (a == 0x01) {
        goto L_00620E;
    }
    if (a < 0x05) {
        goto L_00620C;
    }
L_006202:
    opDEC(0x0086, 1);
    a = myMapper->readCPU(0x0086);
    opAND(0xFC);
    myMapper->writeCPU(0x0086, a);
    opINC(0x0086, 1);
L_00620C:
    opDEC(0x0086, 1);
L_00620E:
    opDEC(0x0086, 1);
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0086));
    myMapper->writeCPU(0x03A1, a);
    myMapper->writeCPU(0x0435, a);
    myMapper->writeCPU(0x03A0, 0x00);
    pushAddress(0x006220);
    SUB_004306();
    if (poppedEntry.value != 0x006220) return;
    myMapper->writeCPU(0x0385, 0x00);
    popAddress();
}

void game::SUB_006229() {
    a = myMapper->readCPU(0x0436);
    flgC = false;
    opADC(0x01);
    if (a == 0x0A) {
        goto L_006237;
    }
    myMapper->writeCPU(0x0436, a);
    popAddress();
    return;
L_006237:
    myMapper->writeCPU(0x0436, 0x00);
    opINC(0x0437, 1);
    popAddress();
}

void game::SUB_006240() {
    a = 0x00;
    y = 0x18;
    do {
        myMapper->writeCPU(0x048E + y, a);
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_006C0C() {
    x = 0x0E;
    a = myMapper->readCPU(0x078C);
    if (a != 0xFF) {
        if (a == 0x80) {
            goto L_006C38;
        }
        a = myMapper->readCPU(0x078D);
        if (a == 0x02) {
            goto L_006C23;
        }
        SUB_006E5F();
        return;
    L_006C23:
        myMapper->writeCPU(0x070D, 0x00);
        SUB_006D67();
        return;
    }
    myMapper->writeCPU(0x04C0 + x, 0x70);
    myMapper->writeCPU(0x04A7 + x, 0x48);
    SUB_006D57();
    return;
L_006C38:
    myMapper->writeCPU(0x04C0 + x, 0x88);
    myMapper->writeCPU(0x04A7 + x, 0x48);
    SUB_006D57();
    return;
}

void game::SUB_006C45() {
    x = 0x0F;
    a = myMapper->readCPU(0x078C);
    if (a != 0xFF) {
        if (a == 0x80) {
            goto L_006C6C;
        }
        a = myMapper->readCPU(0x078D);
        if (a == 0xFF) {
            goto L_006C5C;
        }
        SUB_006E5F();
        return;
    L_006C5C:
        SUB_006E36();
        return;
    }
    myMapper->writeCPU(0x04C0 + x, 0x78);
    myMapper->writeCPU(0x04A7 + x, 0x58);
    SUB_006D57();
    return;
L_006C6C:
    myMapper->writeCPU(0x04C0 + x, 0x68);
    myMapper->writeCPU(0x04A7 + x, 0x78);
    SUB_006D57();
    return;
}

void game::SUB_006C79() {
    x = 0x10;
    a = myMapper->readCPU(0x078C);
    if (a != 0xFF) {
        if (a == 0x80) {
            goto L_006CA0;
        }
        a = myMapper->readCPU(0x078D);
        if (a == 0xFF) {
            goto L_006C90;
        }
        SUB_006E5F();
        return;
    L_006C90:
        SUB_006E36();
        return;
    }
    myMapper->writeCPU(0x04C0 + x, 0x68);
    myMapper->writeCPU(0x04A7 + x, 0x78);
    SUB_006D57();
    return;
L_006CA0:
    myMapper->writeCPU(0x04C0 + x, 0x88);
    myMapper->writeCPU(0x04A7 + x, 0x88);
    SUB_006D57();
    return;
}

void game::SUB_006CAD() {
    x = 0x11;
    a = myMapper->readCPU(0x078C);
    if (a != 0xFF) {
        if (a == 0x80) {
            goto L_006CDF;
        }
        a = myMapper->readCPU(0x078D);
        if (a != 0xFF) {
            SUB_006E5F();
            return;
        }
        SUB_006E36();
        return;
    }
    myMapper->writeCPU(0x04C0 + x, 0x60);
    myMapper->writeCPU(0x04A7 + x, 0x88);
    if (myMapper->readCPU(0x0386) == 0) {
        goto L_006CDC;
    }
    opINC(0x04D9 + x, 2);
L_006CDC:
    SUB_006D57();
    return;
L_006CDF:
    myMapper->writeCPU(0x04C0 + x, 0x58);
    myMapper->writeCPU(0x04A7 + x, 0xA8);
    myMapper->writeCPU(0x04F2 + x, 0x04);
    SUB_006D5C();
    return;
}

void game::SUB_006CF1() {
    x = 0x12;
    a = myMapper->readCPU(0x078C);
    if (a != 0xFF) {
        if (a == 0x80) {
            goto L_006D1D;
        }
        a = myMapper->readCPU(0x078D);
        if (a == 0xFF) {
            goto L_006D08;
        }
        SUB_006E5F();
        return;
    L_006D08:
        SUB_006E36();
        return;
    }
    myMapper->writeCPU(0x04C0 + x, 0x18);
    myMapper->writeCPU(0x04A7 + x, 0xD0);
    myMapper->writeCPU(0x04F2 + x, 0x03);
    SUB_006D5C();
    return;
L_006D1D:
    myMapper->writeCPU(0x04C0 + x, 0xA0);
    myMapper->writeCPU(0x04A7 + x, 0xB8);
    SUB_006D57();
    return;
}

void game::SUB_006D2A() {
    x = 0x13;
    a = myMapper->readCPU(0x078D);
    if (a == 0xFF) {
        goto L_006D36;
    }
    SUB_006E5F();
    return;
L_006D36:
    SUB_006E36();
    return;
}

void game::SUB_006D39() {
    x = 0x14;
    a = myMapper->readCPU(0x078D);
    if (a == 0xFF) {
        goto L_006D45;
    }
    SUB_006E5F();
    return;
L_006D45:
    SUB_006E36();
    return;
}

void game::SUB_006D48() {
    x = 0x15;
    a = myMapper->readCPU(0x078D);
    if (a == 0xFF) {
        goto L_006D54;
    }
    SUB_006E5F();
    return;
L_006D54:
    SUB_006E36();
    return;
}

void game::SUB_006D57() {
    myMapper->writeCPU(0x04F2 + x, 0x02);
    SUB_006D5C();
    return;
}

void game::SUB_006D5C() {
    myMapper->writeCPU(0x048E + x, 0x88);
    while (true) {
        pushAddress(0x006D61);
        SUB_004275();
        if (poppedEntry.value != 0x006D61) return;
    }
}

void game::SUB_006D67() {
    while (true) {
        pushAddress(0x006D67);
        SUB_0077CD();
        if (poppedEntry.value != 0x006D67) return;
        if (!flgZ) {
            goto L_006D72;
        }
        pushAddress(0x006D6C);
        SUB_004275();
        if (poppedEntry.value != 0x006D6C) return;
    }
    while (true) {
    L_006D72:
        pushAddress(0x006D72);
        SUB_0033CF();
        if (poppedEntry.value != 0x006D72) return;
        if (!flgZ) {
            goto L_006D86;
        }
        pushAddress(0x006D77);
        SUB_0077FC();
        if (poppedEntry.value != 0x006D77) return;
        pushAddress(0x006D7A);
        SUB_007B00();
        if (poppedEntry.value != 0x006D7A) return;
        pushAddress(0x006D7D);
        SUB_0077CD();
        if (poppedEntry.value != 0x006D7D) return;
        pushAddress(0x006D80);
        SUB_004275();
        if (poppedEntry.value != 0x006D80) return;
    }
L_006D86:
    a = myMapper->readCPU(0x048E + x);
    opORA(0x20);
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x0682 + x, 0x00);
    myMapper->writeCPU(0x078D, 0xFF);
    myMapper->writeCPU(0x050B + x, 0x08);
    while (true) {
        a = myMapper->readCPU(0x0682 + x);
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x00B0, myMapper->readCPU(0xEE2A + y));
        opINY(1);
        myMapper->writeCPU(0x00B1, myMapper->readCPU(0xEE2A + y));
        y = 0x0F;
        do {
            if (myMapper->readCPU(0x048E + y) == 0) {
                goto L_006DBC;
            }
            opINY(1);
        } while (y < 0x16);
        goto L_006E05;
    L_006DBC:
        myMapper->writeCPU(0x048E + y, 0xA9);
        myMapper->writeCPU(0x04D9 + y, 0x80);
        myMapper->writeCPU(0x04F2 + y, 0x01);
        myMapper->writeCPU(0x05BA + y, 0x02);
        myMapper->writeCPU(0x069B + y, 0xFF);
        myMapper->writeCPU(0x056F + y, myMapper->readCPU(0x00B0));
        myMapper->writeCPU(0x0588 + y, myMapper->readCPU(0x00B1));
        myMapper->writeCPU(0x053D + y, myMapper->readCPU(0x053D + x));
        myMapper->writeCPU(0x0524 + y, myMapper->readCPU(0x0524 + x));
        a = y;
        flgC = true;
        opSBC(0x0D);
        opASL_A(1);
        flgC = false;
        opADC(0x08);
        pushAddress(0x006DF3);
        SUB_0041F5();
        if (poppedEntry.value != 0x006DF3) return;
        opINC(0x0682 + x, 1);
        a = myMapper->readCPU(0x0682 + x);
        if (a < 0x06) {
            goto L_006E05;
        }
        myMapper->writeCPU(0x0682 + x, 0x00);
    L_006E05:
        pushAddress(0x006E05);
        SUB_0077CD();
        if (poppedEntry.value != 0x006E05) return;
        if (flgZ) {
            goto L_006E10;
        }
        pushAddress(0x006E0A);
        SUB_004275();
        if (poppedEntry.value != 0x006E0A) return;
    }
L_006E10:
    myMapper->writeCPU(0x04C0 + x, 0x78);
    myMapper->writeCPU(0x04A7 + x, 0x78);
    myMapper->writeCPU(0x048E + x, 0x88);
    pushAddress(0x006E1F);
    SUB_004275();
    if (poppedEntry.value != 0x006E1F) return;
    a = 0x13;
    pushAddress(0x006E24);
    SUB_0079E1();
    if (poppedEntry.value != 0x006E24) return;
    SUB_00794A();
    return;
}

void game::SUB_006E36() {
    a = 0x13;
    pushAddress(0x006E38);
    SUB_00206B();
    if (poppedEntry.value != 0x006E38) return;
    while (true) {
        opINC(0x069B + x, 1);
        a = myMapper->readCPU(0x069B + x);
        opLSR_A(1);
        if (a >= 0x04) {
            goto L_006E5C;
        }
        flgC = false;
        opADC(0x80);
        myMapper->writeCPU(0x04D9 + x, a);
        myMapper->writeCPU(0x050B + x, 0x08);
        pushAddress(0x006E51);
        SUB_0077CD();
        if (poppedEntry.value != 0x006E51) return;
        if (flgZ) {
            goto L_006E5C;
        }
        pushAddress(0x006E56);
        SUB_004275();
        if (poppedEntry.value != 0x006E56) return;
    }
L_006E5C:
    SUB_00794A();
    return;
}

void game::SUB_006E5F() {
    opINC(0x0439, 1);
    if (flgZ) {
        opINC(0x043A, 1);
    }
    opINC(0x043D, 1);
    if (!flgZ) {
        goto L_006E6F;
    }
    opINC(0x043E, 1);
L_006E6F:
    myMapper->writeCPU(0x048E + x, 0x88);
    myMapper->writeCPU(0x069B + x, 0xFF);
    a = myMapper->readCPU(0x05D3 + x);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x008A, myMapper->readCPU(0xEFF2 + y));
    opINY(1);
    myMapper->writeCPU(0x008B, myMapper->readCPU(0xEFF2 + y));
	Uint16 jmptarget = myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8);
    indirectJump(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8));
}

void game::SUB_006E8C() {
    myMapper->writeCPU(0x05D3 + x, 0x00);
    myMapper->writeCPU(0x05BA + x, 0x11);
    myMapper->writeCPU(0x04F2 + x, 0x02);
    myMapper->writeCPU(0x06B4 + x, 0x44);
    pushAddress(0x006EA0);
    SUB_007176();
    if (poppedEntry.value != 0x006EA0) return;
    a = myMapper->readCPU(0x050B + x);
    opAND(0xFE);
    myMapper->writeCPU(0x050B + x, a);
    pushAddress(0x006EAB);
    SUB_007386();
    if (poppedEntry.value != 0x006EAB) return;
    pushAddress(0x006EAE);
    SUB_00715A();
    if (poppedEntry.value != 0x006EAE) return;
    SUB_00794A();
    return;
}

void game::SUB_006EB4() {
    myMapper->writeCPU(0x05BA + x, 0x13);
    myMapper->writeCPU(0x04F2 + x, 0x02);
    myMapper->writeCPU(0x06B4 + x, 0x5C);
    pushAddress(0x006EC3);
    SUB_00734C();
    if (poppedEntry.value != 0x006EC3) return;
    a = myMapper->readCPU(0x050B + x);
    opAND(0xFE);
    myMapper->writeCPU(0x050B + x, a);
    pushAddress(0x006ECE);
    SUB_007386();
    if (poppedEntry.value != 0x006ECE) return;
    pushAddress(0x006ED1);
    SUB_00715A();
    if (poppedEntry.value != 0x006ED1) return;
    SUB_00794A();
    return;
}

void game::SUB_006ED7() {
    myMapper->writeCPU(0x05BA + x, 0x12);
    myMapper->writeCPU(0x04F2 + x, 0x00);
    pushAddress(0x006EE1);
    SUB_007054();
    if (poppedEntry.value != 0x006EE1) return;
    pushAddress(0x006EE4);
    SUB_00715A();
    if (poppedEntry.value != 0x006EE4) return;
    SUB_00794A();
    return;
}

void game::SUB_006EEA() {
    myMapper->writeCPU(0x05BA + x, 0x12);
    myMapper->writeCPU(0x04F2 + x, 0x00);
    pushAddress(0x006EF4);
    SUB_007054();
    if (poppedEntry.value != 0x006EF4) return;
    pushAddress(0x006EF7);
    SUB_0070CE();
    if (poppedEntry.value != 0x006EF7) return;
    pushAddress(0x006EFA);
    SUB_00715A();
    if (poppedEntry.value != 0x006EFA) return;
    SUB_00794A();
    return;
}

void game::SUB_006F00() {
    myMapper->writeCPU(0x05BA + x, 0x12);
    myMapper->writeCPU(0x04F2 + x, 0x00);
    pushAddress(0x006F0A);
    SUB_00742C();
    if (poppedEntry.value != 0x006F0A) return;
    pushAddress(0x006F0D);
    SUB_0074BA();
    if (poppedEntry.value != 0x006F0D) return;
    SUB_00794A();
    return;
}

void game::SUB_006F13() {
    myMapper->writeCPU(0x05BA + x, 0x12);
    myMapper->writeCPU(0x04F2 + x, 0x02);
    myMapper->writeCPU(0x06B4 + x, 0x48);
    pushAddress(0x006F22);
    SUB_00734C();
    if (poppedEntry.value != 0x006F22) return;
    pushAddress(0x006F25);
    SUB_0074BA();
    if (poppedEntry.value != 0x006F25) return;
    SUB_00794A();
    return;
}

void game::SUB_006F2B() {
    myMapper->writeCPU(0x05BA + x, 0x12);
    myMapper->writeCPU(0x04F2 + x, 0x00);
    myMapper->writeCPU(0x06B4 + x, 0x35);
    pushAddress(0x006F3A);
    SUB_007054();
    if (poppedEntry.value != 0x006F3A) return;
    pushAddress(0x006F3D);
    SUB_0070CE();
    if (poppedEntry.value != 0x006F3D) return;
    pushAddress(0x006F40);
    SUB_007176();
    if (poppedEntry.value != 0x006F40) return;
    pushAddress(0x006F43);
    SUB_00715A();
    if (poppedEntry.value != 0x006F43) return;
    SUB_00794A();
    return;
}

void game::SUB_006F49() {
    opINC(0x0717, 1);
    myMapper->writeCPU(0x04F2 + x, 0x01);
    myMapper->writeCPU(0x05BA + x, 0x15);
    myMapper->writeCPU(0x0682 + x, 0x00);
    a = myMapper->readCPU(0x048E + x);
    opORA(0x10);
    opORA(0x02);
    myMapper->writeCPU(0x048E + x, a);
    pushAddress(0x006F65);
    SUB_007570();
    if (poppedEntry.value != 0x006F65) return;
    SUB_00794A();
    return;
}

void game::SUB_006F6B() {
    SUB_006F49();
    return;
}

void game::SUB_006F6E() {
    a = myMapper->readCPU(0x048E + x);
    opORA(0x02);
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x04F2 + x, 0x02);
    SUB_006F7B();
    return;
}

void game::SUB_006F7B() {
    a = 0x0A;
    SUB_006F7D();
    return;
}

void game::SUB_006F7D() {
    myMapper->writeCPU(0x05BA + x, a);
    a = 0x00;
    myMapper->writeCPU(0x0682 + x, a);
    myMapper->writeCPU(0x05EC + x, a);
    pushAddress(0x006F88);
    SUB_007570();
    if (poppedEntry.value != 0x006F88) return;
    SUB_00794A();
    return;
}

void game::SUB_006F8E() {
    SUB_006F6E();
    return;
}

void game::SUB_006F91() {
    a = 0x71;
    SUB_006F98();
    return;
}

void game::SUB_006F96() {
    a = 0x70;
    SUB_006F98();
    return;
}

void game::SUB_006F98() {
    myMapper->writeCPU(0x04D9 + x, a);
    a = 0x06;
    SUB_006F7D();
    return;
}

void game::SUB_006FA0() {
    myMapper->writeCPU(0x04F2 + x, 0x00);
    a = 0x60;
    myMapper->writeCPU(0x04D9 + x, a);
    SUB_006F98();
    return;
}

void game::SUB_006FAD() {
    myMapper->writeCPU(0x04F2 + x, 0x02);
    SUB_006F96();
    return;
}

void game::SUB_006FB5() {
    myMapper->writeCPU(0x04F2 + x, 0x00);
    SUB_006F91();
    return;
}

void game::SUB_006FBD() {
    myMapper->writeCPU(0x04F2 + x, 0x00);
    SUB_006F96();
    return;
}

void game::SUB_006FC5() {
    myMapper->writeCPU(0x04F2 + x, 0x02);
    SUB_006F91();
    return;
}

void game::SUB_006FCD() {
    myMapper->writeCPU(0x04F2 + x, 0x02);
    myMapper->writeCPU(0x04D9 + x, 0x60);
    SUB_006F7B();
    return;
}

void game::SUB_006FDA() {
    myMapper->writeCPU(0x04F2 + x, 0x02);
    myMapper->writeCPU(0x05BA + x, 0x0B);
    a = 0x00;
    myMapper->writeCPU(0x0682 + x, a);
    myMapper->writeCPU(0x05EC + x, a);
    pushAddress(0x006FEC);
    SUB_0076E8();
    if (poppedEntry.value != 0x006FEC) return;
    SUB_00794A();
    return;
}

void game::SUB_007054() {
    a = myMapper->readCPU(0x071F);
    opAND(0x07);
    opASL_A(2);
    y = a;
    opINC(0x071F, 1);
    myMapper->writeCPU(0x056F + x, myMapper->readCPU(0xF12E + y));
    opINY(1);
    myMapper->writeCPU(0x0588 + x, myMapper->readCPU(0xF12E + y));
    opINY(1);
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(0xF12E + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(0xF12E + y));
    myMapper->writeCPU(0x04D9 + x, 0x14);
    pushAddress(0x00707F);
    SUB_0030BC();
    if (poppedEntry.value != 0x00707F) return;
    y = 0x00;
    pushAddress(0x007084);
    SUB_0030E5();
    if (poppedEntry.value != 0x007084) return;
    pushAddress(0x007087);
    SUB_002DC9();
    if (poppedEntry.value != 0x007087) return;
    myMapper->writeCPU(0x050B + x, a);
    do {
        while (true) {
            pushAddress(0x00708D);
            SUB_0077CD();
            if (poppedEntry.value != 0x00708D) return;
            if (!flgZ) {
                goto L_007098;
            }
            pushAddress(0x007092);
            SUB_004275();
            if (poppedEntry.value != 0x007092) return;
        }
    L_007098:
        pushAddress(0x007098);
        SUB_007A32();
        if (poppedEntry.value != 0x007098) return;
        pushAddress(0x00709B);
        SUB_0029D3();
        if (poppedEntry.value != 0x00709B) return;
        if (flgC) {
            goto L_0070C1;
        }
        a = myMapper->readCPU(0x04A7 + x);
        if (a >= myMapper->readCPU(0x04A7)) {
            goto L_0070C1;
        }
        pushAddress(0x0070AE);
        SUB_0077FC();
        if (poppedEntry.value != 0x0070AE) return;
        if (!flgC) {
            goto L_0070B6;
        }
        SUB_00783C();
        return;
    L_0070B6:
        pushAddress(0x0070B6);
        SUB_004275();
        if (poppedEntry.value != 0x0070B6) return;
        pushAddress(0x0070B9);
        SUB_0033CF();
        if (poppedEntry.value != 0x0070B9) return;
    } while (flgZ);
    SUB_00783C();
    return;
L_0070C1:
    myMapper->writeCPU(0x069B + x, 0xFF);
    myMapper->writeCPU(0x05EC + x, 0x20);
    SUB_0070FD();
    return;
}

void game::SUB_0070CE() {
    do {
        pushAddress(0x0070CE);
        SUB_0077CD();
        if (poppedEntry.value != 0x0070CE) return;
        if (flgZ) {
            SUB_00794A();
            return;
        }
        pushAddress(0x0070D6);
        SUB_007A32();
        if (poppedEntry.value != 0x0070D6) return;
        a = myMapper->readCPU(0x04A7 + x);
        if (a < 0x30) {
            goto L_0070F3;
        }
        pushAddress(0x0070E0);
        SUB_0077FC();
        if (poppedEntry.value != 0x0070E0) return;
        if (!flgC) {
            goto L_0070E8;
        }
        SUB_00783C();
        return;
    L_0070E8:
        pushAddress(0x0070E8);
        SUB_004275();
        if (poppedEntry.value != 0x0070E8) return;
        pushAddress(0x0070EB);
        SUB_0033CF();
        if (poppedEntry.value != 0x0070EB) return;
    } while (flgZ);
    SUB_00783C();
    return;
L_0070F3:
    myMapper->writeCPU(0x069B + x, 0xFF);
    myMapper->writeCPU(0x05EC + x, 0x24);
    SUB_0070FD();
    return;
}

void game::SUB_0070FD() {
    do {
        opINC(0x069B + x, 1);
        a = myMapper->readCPU(0x069B + x);
        opLSR_A(1);
        opAND(0x07);
        if (a == 0x04) {
            goto L_00711C;
        }
        flgC = false;
        opADC(myMapper->readCPU(0x05EC + x));
        myMapper->writeCPU(0x04D9 + x, a);
        pushAddress(0x007111);
        SUB_004275();
        if (poppedEntry.value != 0x007111) return;
        pushAddress(0x007114);
        SUB_0033CF();
        if (poppedEntry.value != 0x007114) return;
    } while (flgZ);
    SUB_00783C();
    return;
L_00711C:
    a = myMapper->readCPU(0x050B + x);
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0xF14A + y);
    pushAddress(0x007125);
    SUB_0077C3();
    if (poppedEntry.value != 0x007125) return;
    myMapper->writeCPU(0x04F2 + x, 0x00);
    popAddress();
}

void game::SUB_00715A() {
    do {
        pushAddress(0x00715A);
        SUB_0077CD();
        if (poppedEntry.value != 0x00715A) return;
        if (flgZ) {
            popAddress();
            return;
        }
        pushAddress(0x00715F);
        SUB_007A32();
        if (poppedEntry.value != 0x00715F) return;
        pushAddress(0x007162);
        SUB_0077FC();
        if (poppedEntry.value != 0x007162) return;
        if (flgC) {
            SUB_00783C();
            return;
        }
        pushAddress(0x00716A);
        SUB_004275();
        if (poppedEntry.value != 0x00716A) return;
        pushAddress(0x00716D);
        SUB_0033CF();
        if (poppedEntry.value != 0x00716D) return;
    } while (flgZ);
    SUB_00783C();
}

void game::SUB_007176() {
    a = myMapper->readCPU(0x071F);
    opAND(0x0F);
    opASL_A(2);
    y = a;
    opINC(0x071F, 1);
    myMapper->writeCPU(0x056F + x, myMapper->readCPU(0xF3EC + y));
    opINY(1);
    myMapper->writeCPU(0x0588 + x, myMapper->readCPU(0xF3EC + y));
    opINY(1);
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(0xF3EC + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(0xF3EC + y));
    SUB_00719C();
    return;
}

void game::SUB_00719C() {
    if (myMapper->readCPU(0x056F) == 0) {
        goto L_0071AB;
    }
    if (myMapper->readCPU(0x0524) == 0) {
        goto L_0071B5;
    }
    a = 0x60;
    goto L_0071BC;
L_0071AB:
    if (myMapper->readCPU(0x0524) == 0) {
        goto L_0071BA;
    }
    a = 0x40;
    goto L_0071BC;
L_0071B5:
    a = 0x20;
    goto L_0071BC;
L_0071BA:
    a = 0x00;
L_0071BC:
    myMapper->writeCPU(0x00B0, a);
    a = myMapper->readCPU(0x071F);
    opAND(0x07);
    opASL_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x00B0));
    myMapper->writeCPU(0x05EC + x, a);
    SUB_0071CB();
    return;
}

void game::SUB_0071CB() {
    y = myMapper->readCPU(0x05EC + x);
    myMapper->writeCPU(0x0605 + x, myMapper->readCPU(0xFC53 + y));
    opINY(1);
    myMapper->writeCPU(0x061E + x, myMapper->readCPU(0xFC53 + y));
    opINY(2);
    a = myMapper->readCPU(0xFC53 + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x06B4 + x));
    if (!flgC) {
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0650 + x, a);
        opDEY(1);
        a = myMapper->readCPU(0xFC53 + y);
        flgC = true;
        opSBC(0x01);
        opAND(0x01);
        myMapper->writeCPU(0x0637 + x, a);
    }
    else {
        myMapper->writeCPU(0x0650 + x, a);
        opDEY(1);
        myMapper->writeCPU(0x0637 + x, myMapper->readCPU(0xFC53 + y));
    }
    while (true) {
        do {
            do {
                pushAddress(0x007205);
                SUB_003102();
                if (poppedEntry.value != 0x007205) return;
                pushAddress(0x007208);
                SUB_0030BC();
                if (poppedEntry.value != 0x007208) return;
                pushAddress(0x00720B);
                SUB_002DC9();
                if (poppedEntry.value != 0x00720B) return;
                pushAddress(0x00720E);
                SUB_0077C3();
                if (poppedEntry.value != 0x00720E) return;
                pushAddress(0x007211);
                SUB_007386();
                if (poppedEntry.value != 0x007211) return;
                pushAddress(0x007214);
                SUB_003102();
                if (poppedEntry.value != 0x007214) return;
                pushAddress(0x007217);
                SUB_0030BC();
                if (poppedEntry.value != 0x007217) return;
                pushAddress(0x00721A);
                SUB_0029F4();
                if (poppedEntry.value != 0x00721A) return;
                if (flgC) {
                    goto L_007251;
                }
                pushAddress(0x00721F);
                SUB_0077CD();
                if (poppedEntry.value != 0x00721F) return;
                if (flgZ) {
                    goto L_00724B;
                }
                pushAddress(0x007224);
                SUB_007A32();
                if (poppedEntry.value != 0x007224) return;
                pushAddress(0x007227);
                SUB_0077FC();
                if (poppedEntry.value != 0x007227) return;
                if (flgC) {
                    if (x == 0x18) {
                        goto L_007233;
                    }
                    SUB_00783C();
                    return;
                L_007233:
                    a = myMapper->readCPU(0x048E + y);
                    opAND(0xFE);
                    myMapper->writeCPU(0x048E + y, a);
                    popAddress();
                    return;
                }
                pushAddress(0x00723C);
                SUB_004275();
                if (poppedEntry.value != 0x00723C) return;
            } while (x == 0x18);
            pushAddress(0x007243);
            SUB_0033CF();
            if (poppedEntry.value != 0x007243) return;
        } while (flgZ);
        SUB_00783C();
        return;
    L_00724B:
        pushAddress(0x00724B);
        SUB_004275();
        if (poppedEntry.value != 0x00724B) return;
    }
L_007251:
    a = myMapper->readCPU(0x050B + x);
    opAND(0x0F);
    if (a < 0x08) {
        myMapper->writeCPU(0x0669 + x, 0x01);
        a = myMapper->readCPU(0x048E + x);
        opAND(0xFB);
        myMapper->writeCPU(0x048E + x, a);
    }
    else {
        myMapper->writeCPU(0x0669 + x, 0x0F);
        a = myMapper->readCPU(0x048E + x);
        opORA(0x04);
        myMapper->writeCPU(0x048E + x, a);
    }
L_007277:
    a = myMapper->readCPU(0x05D3 + x);
    if (a == 0x07) {
        a = myMapper->readCPU(0x04A7 + x);
        if (a >= 0x78) {
            popAddress();
            return;
        }
    }
    y = myMapper->readCPU(0x05EC + x);
    myMapper->writeCPU(0x0396, myMapper->readCPU(0xFC53 + y));
    opINY(1);
    myMapper->writeCPU(0x0397, myMapper->readCPU(0xFC53 + y));
    opINY(1);
    myMapper->writeCPU(0x0399, myMapper->readCPU(0xFC53 + y));
    opINY(1);
    myMapper->writeCPU(0x039A, myMapper->readCPU(0xFC53 + y));
    myMapper->writeCPU(0x0086, myMapper->readCPU(0x0669 + x));
    myMapper->writeCPU(0x0085, myMapper->readCPU(0x06B4 + x));
    pushAddress(0x0072AE);
    SUB_002EF0();
    if (poppedEntry.value != 0x0072AE) return;
    myMapper->writeCPU(0x061E + x, myMapper->readCPU(0x0397));
    myMapper->writeCPU(0x0605 + x, myMapper->readCPU(0x0396));
    myMapper->writeCPU(0x0650 + x, myMapper->readCPU(0x039A));
    myMapper->writeCPU(0x0637 + x, myMapper->readCPU(0x0399));
L_0072C9:
    pushAddress(0x0072C9);
    SUB_003102();
    if (poppedEntry.value != 0x0072C9) return;
    pushAddress(0x0072CC);
    SUB_0030BC();
    if (poppedEntry.value != 0x0072CC) return;
    pushAddress(0x0072CF);
    SUB_002DC9();
    if (poppedEntry.value != 0x0072CF) return;
    pushAddress(0x0072D2);
    SUB_0077C3();
    if (poppedEntry.value != 0x0072D2) return;
    pushAddress(0x0072D5);
    SUB_007386();
    if (poppedEntry.value != 0x0072D5) return;
    pushAddress(0x0072D8);
    SUB_0077CD();
    if (poppedEntry.value != 0x0072D8) return;
    if (!flgZ) {
        if (x == 0x18) {
            goto L_0072EC;
        }
        pushAddress(0x0072E1);
        SUB_007A32();
        if (poppedEntry.value != 0x0072E1) return;
        pushAddress(0x0072E4);
        SUB_0077FC();
        if (poppedEntry.value != 0x0072E4) return;
        if (flgC) {
            SUB_00783C();
            return;
        }
    }
L_0072EC:
    pushAddress(0x0072EC);
    SUB_004275();
    if (poppedEntry.value != 0x0072EC) return;
    if (x != 0x18) {
        pushAddress(0x0072F3);
        SUB_0033CF();
        if (poppedEntry.value != 0x0072F3) return;
        if (!flgZ) {
            SUB_00783C();
            return;
        }
    }
    pushAddress(0x0072FB);
    SUB_003102();
    if (poppedEntry.value != 0x0072FB) return;
    pushAddress(0x0072FE);
    SUB_0030BC();
    if (poppedEntry.value != 0x0072FE) return;
    pushAddress(0x007301);
    SUB_0029F4();
    if (poppedEntry.value != 0x007301) return;
    if (flgC) {
        if (x != 0x18) {
            goto L_007310;
        }
        opDEC(0x05D3 + x, 1);
        if (flgZ) {
            popAddress();
            return;
        }
    L_007310:
        a = myMapper->readCPU(0x048E + x);
        opAND(0x04);
        if (!flgZ) {
            goto L_007326;
        }
        opINC(0x0669 + x, 1);
        a = myMapper->readCPU(0x0669 + x);
        opAND(0x0F);
        if (flgZ) {
            goto L_00733B;
        }
        opCMP(a, 0x01);
        goto L_007332;
    L_007326:
        opDEC(0x0669 + x, 1);
        a = myMapper->readCPU(0x0669 + x);
        opAND(0x0F);
        if (a == 0x0F) {
            goto L_007340;
        }
    L_007332:
        goto L_007277;
    }
    goto L_0072C9;
L_00733B:
    a = 0x06;
    goto L_007342;
L_007340:
    a = 0x0A;
L_007342:
    myMapper->writeCPU(0x050B + x, a);
    pushAddress(0x007345);
    SUB_0077C3();
    if (poppedEntry.value != 0x007345) return;
    pushAddress(0x007348);
    SUB_007386();
    if (poppedEntry.value != 0x007348) return;
    popAddress();
}

void game::SUB_00734C() {
    a = myMapper->readCPU(0x071F);
    opAND(0x03);
    opASL_A(2);
    y = a;
    opINC(0x071F, 1);
    myMapper->writeCPU(0x056F + x, myMapper->readCPU(0xF3EC + y));
    opINY(1);
    myMapper->writeCPU(0x0588 + x, myMapper->readCPU(0xF3EC + y));
    opINY(1);
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(0xF3EC + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(0xF3EC + y));
    a = myMapper->readCPU(0x056F + x);
    if (a == 0x01) {
        goto L_00737E;
    }
    a = 0x0C;
    goto L_007380;
L_00737E:
    a = 0x2C;
L_007380:
    myMapper->writeCPU(0x05EC + x, a);
    SUB_0071CB();
    return;
}

void game::SUB_007386() {
    if (x == 0x18) {
        goto L_0073DD;
    }
    a = myMapper->readCPU(0x05D3 + x);
    if (a == 0x07) {
        goto L_0073B7;
    }
    if (a == 0x01) {
        goto L_0073CA;
    }
    a = myMapper->readCPU(0x048E + x);
    opAND(0x80);
    if (flgZ) {
        goto L_0073A3;
    }
    a = myMapper->readCPU(0x050B + x);
    opAND(0x01);
    if (!flgZ) {
        goto L_0073B6;
    }
L_0073A3:
    a = 0x10;
    while (true) {
        while (true) {
            myMapper->writeCPU(0x04D9 + x, a);
            a = myMapper->readCPU(0x050B + x);
            opLSR_A(1);
            opAND(0x0F);
            y = a;
            flgC = false;
            opADC(myMapper->readCPU(0x04D9 + x));
            myMapper->writeCPU(0x04D9 + x, a);
            do {
            L_0073B6:
                popAddress();
                return;
            L_0073B7:
                a = myMapper->readCPU(0x048E + x);
                opAND(0x80);
                if (flgZ) {
                    goto L_0073C5;
                }
                a = myMapper->readCPU(0x050B + x);
                opAND(0x01);
            } while (!flgZ);
        L_0073C5:
            a = 0x40;
        }
    L_0073CA:
        a = myMapper->readCPU(0x048E + x);
        opAND(0x80);
        if (flgZ) {
            goto L_0073D8;
        }
        a = myMapper->readCPU(0x050B + x);
        opAND(0x01);
        if (!flgZ) {
            goto L_0073B6;
        }
    L_0073D8:
        a = 0x50;
    }
L_0073DD:
    opINC(0x069B + x, 1);
    a = myMapper->readCPU(0x069B + x);
    opAND(0x07);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x04D9 + x, a);
    popAddress();
}

void game::SUB_00742C() {
    a = myMapper->readCPU(0x071F);
    opAND(0x07);
    opASL_A(2);
    y = a;
    opINC(0x071F, 1);
    myMapper->writeCPU(0x056F + x, myMapper->readCPU(0xF550 + y));
    opINY(1);
    myMapper->writeCPU(0x0588 + x, myMapper->readCPU(0xF550 + y));
    opINY(1);
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(0xF550 + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(0xF550 + y));
    myMapper->writeCPU(0x050B + x, 0x08);
    while (true) {
        do {
            do {
                while (true) {
                    myMapper->writeCPU(0x04D9 + x, 0x14);
                    pushAddress(0x00745C);
                    SUB_0077CD();
                    if (poppedEntry.value != 0x00745C) return;
                    if (!flgZ) {
                        goto L_007467;
                    }
                    pushAddress(0x007461);
                    SUB_004275();
                    if (poppedEntry.value != 0x007461) return;
                }
            L_007467:
                pushAddress(0x007467);
                SUB_007A32();
                if (poppedEntry.value != 0x007467) return;
                y = 0x00;
                a = myMapper->readCPU(0x04A7 + y);
                flgC = true;
                opSBC(0x40);
                if (flgC) {
                    if (a >= myMapper->readCPU(0x04A7 + x)) {
                        goto L_007484;
                    }
                }
                a = myMapper->readCPU(0x04A7 + y);
                flgC = true;
                opSBC(0x20);
                if (a >= myMapper->readCPU(0x04A7 + x)) {
                    goto L_007497;
                }
            L_007484:
                pushAddress(0x007484);
                SUB_0077FC();
                if (poppedEntry.value != 0x007484) return;
                if (!flgC) {
                    goto L_00748C;
                }
                SUB_00783C();
                return;
            L_00748C:
                pushAddress(0x00748C);
                SUB_004275();
                if (poppedEntry.value != 0x00748C) return;
                pushAddress(0x00748F);
                SUB_0033CF();
                if (poppedEntry.value != 0x00748F) return;
            } while (flgZ);
            SUB_00783C();
            return;
        L_007497:
            pushAddress(0x007497);
            SUB_004275();
            if (poppedEntry.value != 0x007497) return;
            y = 0x00;
            a = myMapper->readCPU(0x04C0 + y);
            flgC = true;
            opSBC(0x50);
            if (!flgC) {
                goto L_0074A9;
            }
        } while (a >= myMapper->readCPU(0x04C0 + x));
    L_0074A9:
        a = myMapper->readCPU(0x04C0 + y);
        flgC = false;
        opADC(0x50);
        if (flgC) {
            goto L_0074B9;
        }
        if (a >= myMapper->readCPU(0x04C0 + x)) {
            goto L_0074B9;
        }
    }
L_0074B9:
    popAddress();
}

void game::SUB_0074BA() {
    y = 0x00;
    pushAddress(0x0074BC);
    SUB_0030E5();
    if (poppedEntry.value != 0x0074BC) return;
    pushAddress(0x0074BF);
    SUB_0030BC();
    if (poppedEntry.value != 0x0074BF) return;
    a = myMapper->readCPU(0x0391);
    flgC = true;
    opSBC(myMapper->readCPU(0x0397));
    a = myMapper->readCPU(0x0390);
    opSBC(myMapper->readCPU(0x0396));
    if (!flgC) {
        goto L_0074D6;
    }
    a = 0x0A;
    goto L_0074D8;
L_0074D6:
    a = 0x06;
L_0074D8:
    myMapper->writeCPU(0x050B + x, a);
    opINC(0x05BA + x, 2);
    myMapper->writeCPU(0x069B + x, 0x00);
    while (true) {
        do {
            pushAddress(0x0074E6);
            SUB_0077CD();
            if (poppedEntry.value != 0x0074E6) return;
            if (flgZ) {
                goto L_007501;
            }
            pushAddress(0x0074EB);
            SUB_007A32();
            if (poppedEntry.value != 0x0074EB) return;
            pushAddress(0x0074EE);
            SUB_0077FC();
            if (poppedEntry.value != 0x0074EE) return;
            if (!flgC) {
                goto L_0074F6;
            }
            SUB_00783C();
            return;
        L_0074F6:
            pushAddress(0x0074F6);
            SUB_007507();
            if (poppedEntry.value != 0x0074F6) return;
            pushAddress(0x0074F9);
            SUB_0033CF();
            if (poppedEntry.value != 0x0074F9) return;
        } while (flgZ);
        SUB_00783C();
        return;
    L_007501:
        pushAddress(0x007501);
        SUB_004275();
        if (poppedEntry.value != 0x007501) return;
    }
    SUB_007507();
    return;
}

void game::SUB_007507() {
    a = myMapper->readCPU(0x05D3 + x);
    opCMP(a, 0x07);
    if (!flgZ) {
        a = myMapper->readCPU(0x050B + x);
        opAND(0x0F);
        if (flgZ) {
            a = 0x28;
        }
        else {
            a = 0x2C;
        }
        myMapper->writeCPU(0x00B0, a);
        a = myMapper->readCPU(0x069B + x);
        if (a < 0x06) {
            opINC(0x069B + x, 1);
            a = myMapper->readCPU(0x069B + x);
            opLSR_A(1);
            opAND(0x03);
            flgC = false;
            opADC(myMapper->readCPU(0x00B0));
            myMapper->writeCPU(0x04D9 + x, a);
        }
        pushAddress(0x007534);
        SUB_004275();
        if (poppedEntry.value != 0x007534) return;
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x050B + x);
    opAND(0x0F);
    if (flgC) {
        goto L_007544;
    }
    a = 0x4C;
    goto L_007546;
L_007544:
    a = 0x48;
L_007546:
    myMapper->writeCPU(0x00B0, a);
    myMapper->writeCPU(0x04F2 + x, 0x00);
    SUB_0077B1();
    return;
}

void game::SUB_007570() {
    myMapper->writeCPU(0x069B + x, 0xFF);
    pushAddress(0x007575);
    SUB_0076D1();
    if (poppedEntry.value != 0x007575) return;
    myMapper->writeCPU(0x056F + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0588 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(0x0682 + x);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0682 + x, a);
    myMapper->writeCPU(0x0605 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x061E + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0637 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0650 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    pushAddress(0x0075B0);
    SUB_003102();
    if (poppedEntry.value != 0x0075B0) return;
    pushAddress(0x0075B3);
    SUB_0030BC();
    if (poppedEntry.value != 0x0075B3) return;
    pushAddress(0x0075B6);
    SUB_002DC9();
    if (poppedEntry.value != 0x0075B6) return;
    myMapper->writeCPU(0x050B + x, a);
    SUB_0075BC();
    return;
}

void game::SUB_0075BC() {
    while (true) {
        pushAddress(0x0075BC);
        SUB_0076D1();
        if (poppedEntry.value != 0x0075BC) return;
        a = myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y);
        if (a == 0xFF) {
            SUB_00794A();
            return;
        }
        myMapper->writeCPU(0x0605 + x, a);
        opINY(1);
        myMapper->writeCPU(0x061E + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0637 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0650 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        a = myMapper->readCPU(0x0682 + x);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x0682 + x, a);
    L_0075E6:
        pushAddress(0x0075E6);
        SUB_003102();
        if (poppedEntry.value != 0x0075E6) return;
        pushAddress(0x0075E9);
        SUB_0030BC();
        if (poppedEntry.value != 0x0075E9) return;
        pushAddress(0x0075EC);
        SUB_002DC9();
        if (poppedEntry.value != 0x0075EC) return;
        myMapper->writeCPU(0x0669 + x, a);
        a = myMapper->readCPU(0x050B + x);
        opAND(0x0F);
        flgC = true;
        opSBC(myMapper->readCPU(0x0669 + x));
        if (!flgZ) {
            opAND(0x0F);
            if (a == 0x08) {
                goto L_007661;
            }
            opAND(0x08);
            if (!flgZ) {
                opINC(0x050B + x, 1);
            }
            else {
                opDEC(0x050B + x, 1);
            }
            a = myMapper->readCPU(0x050B + x);
            opAND(0x0F);
            myMapper->writeCPU(0x050B + x, a);
            pushAddress(0x007618);
            SUB_007775();
            if (poppedEntry.value != 0x007618) return;
            pushAddress(0x00761B);
            SUB_0077FC();
            if (poppedEntry.value != 0x00761B) return;
            if (flgC) {
                SUB_00783C();
                return;
            }
        }
    L_007623:
        pushAddress(0x007623);
        SUB_0077CD();
        if (poppedEntry.value != 0x007623) return;
        if (flgZ) {
            goto L_00765B;
        }
        a = myMapper->readCPU(0x05D3 + x);
        if (a >= 0x30) {
            goto L_007635;
        }
        pushAddress(0x00762F);
        SUB_007A32();
        if (poppedEntry.value != 0x00762F) return;
        goto L_00763D;
    L_007635:
        myMapper->writeCPU(0x04D9 + x, 0x72);
        pushAddress(0x00763A);
        SUB_007B00();
        if (poppedEntry.value != 0x00763A) return;
    L_00763D:
        pushAddress(0x00763D);
        SUB_003102();
        if (poppedEntry.value != 0x00763D) return;
        pushAddress(0x007640);
        SUB_0030BC();
        if (poppedEntry.value != 0x007640) return;
        pushAddress(0x007643);
        SUB_0029F4();
        if (poppedEntry.value != 0x007643) return;
        if (!flgC) {
            goto L_00764B;
        }
    }
L_00764B:
    pushAddress(0x00764B);
    SUB_0077FC();
    if (poppedEntry.value != 0x00764B) return;
    if (!flgC) {
        pushAddress(0x007650);
        SUB_007775();
        if (poppedEntry.value != 0x007650) return;
        pushAddress(0x007653);
        SUB_0033CF();
        if (poppedEntry.value != 0x007653) return;
        if (flgZ) {
            goto L_0075E6;
        }
    }
    SUB_00783C();
    return;
L_00765B:
    pushAddress(0x00765B);
    SUB_004275();
    if (poppedEntry.value != 0x00765B) return;
    goto L_007623;
L_007661:
    a = myMapper->readCPU(0x050B + x);
    opAND(0x07);
    if (!flgZ) {
        a = myMapper->readCPU(0x050B + x);
        opAND(0x08);
        if (!flgZ) {
            goto L_007691;
        }
    }
    else {
        a = myMapper->readCPU(0x050B + x);
        opAND(0x08);
        if (!flgZ) {
            goto L_007681;
        }
        myMapper->writeCPU(0x05EC + x, 0x24);
        goto L_007696;
    L_007681:
        myMapper->writeCPU(0x05EC + x, 0x20);
        goto L_007696;
    }
    myMapper->writeCPU(0x05EC + x, 0x98);
    goto L_007696;
L_007691:
    myMapper->writeCPU(0x05EC + x, 0x9B);
L_007696:
    myMapper->writeCPU(0x069B + x, 0xFF);
    while (true) {
        opINC(0x069B + x, 1);
        a = myMapper->readCPU(0x069B + x);
        opLSR_A(1);
        opAND(0x07);
        if (a == 0x04) {
            goto L_0076C5;
        }
        flgC = false;
        opADC(myMapper->readCPU(0x05EC + x));
        myMapper->writeCPU(0x04D9 + x, a);
        pushAddress(0x0076AF);
        SUB_0077FC();
        if (poppedEntry.value != 0x0076AF) return;
        if (flgC) {
            SUB_00783C();
            return;
        }
        pushAddress(0x0076B7);
        SUB_0033CF();
        if (poppedEntry.value != 0x0076B7) return;
        if (flgZ) {
            goto L_0076BF;
        }
        SUB_00783C();
        return;
    L_0076BF:
        pushAddress(0x0076BF);
        SUB_004275();
        if (poppedEntry.value != 0x0076BF) return;
    }
L_0076C5:
    myMapper->writeCPU(0x050B + x, myMapper->readCPU(0x0669 + x));
    pushAddress(0x0076CB);
    SUB_007775();
    if (poppedEntry.value != 0x0076CB) return;
    goto L_007623;
}

void game::SUB_0076D1() {
    a = myMapper->readCPU(0x05D3 + x);
    flgC = true;
    opSBC(0x0A);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x008A, myMapper->readCPU(0xFD4A + y));
    opINY(1);
    myMapper->writeCPU(0x008B, myMapper->readCPU(0xFD4A + y));
    y = myMapper->readCPU(0x0682 + x);
    popAddress();
}

void game::SUB_0076E8() {
    a = myMapper->readCPU(0x048E + x);
    opORA(0x02);
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x04D9 + x, 0x72);
    a = myMapper->readCPU(0x04C0);
    if (a >= 0x80) {
        goto L_007709;
    }
    myMapper->writeCPU(0x056F + x, 0x00);
    myMapper->writeCPU(0x0588 + x, 0xC0);
    goto L_007713;
L_007709:
    myMapper->writeCPU(0x056F + x, 0x01);
    myMapper->writeCPU(0x0588 + x, 0x40);
L_007713:
    pushAddress(0x007713);
    SUB_0076D1();
    if (poppedEntry.value != 0x007713) return;
    y = 0x02;
    myMapper->writeCPU(0x0524 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x053D + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    y = 0x06;
    myMapper->writeCPU(0x0637 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0650 + x, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0605 + x, myMapper->readCPU(0x056F + x));
    myMapper->writeCPU(0x061E + x, myMapper->readCPU(0x0588 + x));
    myMapper->writeCPU(0x0682 + x, 0x08);
    while (true) {
        do {
            pushAddress(0x007741);
            SUB_0077CD();
            if (poppedEntry.value != 0x007741) return;
            if (flgZ) {
                goto L_00776F;
            }
            pushAddress(0x007746);
            SUB_004275();
            if (poppedEntry.value != 0x007746) return;
            pushAddress(0x007749);
            SUB_003102();
            if (poppedEntry.value != 0x007749) return;
            pushAddress(0x00774C);
            SUB_0030BC();
            if (poppedEntry.value != 0x00774C) return;
            pushAddress(0x00774F);
            SUB_0029F4();
            if (poppedEntry.value != 0x00774F) return;
            if (flgC) {
                a = myMapper->readCPU(0x048E + x);
                opAND(0xFD);
                myMapper->writeCPU(0x048E + x, a);
                SUB_0075BC();
                return;
            }
            pushAddress(0x00775F);
            SUB_0077FC();
            if (poppedEntry.value != 0x00775F) return;
            if (!flgC) {
                goto L_007767;
            }
            SUB_00783C();
            return;
        L_007767:
            pushAddress(0x007767);
            SUB_0033CF();
            if (poppedEntry.value != 0x007767) return;
        } while (flgZ);
        SUB_00783C();
        return;
    L_00776F:
        pushAddress(0x00776F);
        SUB_004275();
        if (poppedEntry.value != 0x00776F) return;
    }
    SUB_007775();
    return;
}

void game::SUB_007775() {
    a = myMapper->readCPU(0x05D3 + x);
    if (a < 0x30) {
        if (a >= 0x20) {
            goto L_00778C;
        }
        a = myMapper->readCPU(0x050B + x);
        opAND(0x01);
        if (!flgZ) {
            goto L_0077AE;
        }
        a = 0x10;
        goto L_007798;
    L_00778C:
        a = myMapper->readCPU(0x05D3 + x);
        if (a < 0x22) {
            goto L_007796;
        }
        goto L_0077AE;
    L_007796:
        a = 0x60;
    L_007798:
        myMapper->writeCPU(0x04D9 + x, a);
        a = myMapper->readCPU(0x050B + x);
        opLSR_A(1);
        opAND(0x0F);
        y = a;
        flgC = false;
        opADC(myMapper->readCPU(0x04D9 + x));
        goto L_0077AB;
    }
    a = 0x72;
L_0077AB:
    myMapper->writeCPU(0x04D9 + x, a);
L_0077AE:
    SUB_004275();
    return;
}

void game::SUB_0077B1() {
    opINC(0x069B, 1);
    a = myMapper->readCPU(0x069B);
    opLSR_A(1);
    opAND(0x03);
    opADC(myMapper->readCPU(0x00B0));
    myMapper->writeCPU(0x04D9 + x, a);
    pushAddress(0x0077BF);
    SUB_004275();
    if (poppedEntry.value != 0x0077BF) return;
    popAddress();
}

void game::SUB_0077C3() {
    if (a != myMapper->readCPU(0x050B + x)) {
        goto L_0077C9;
    }
    popAddress();
    return;
L_0077C9:
    myMapper->writeCPU(0x050B + x, a);
    popAddress();
}

void game::SUB_0077CD() {
    a = myMapper->readCPU(0x0437);
    if (a == 0xFF) {
        SUB_00783C();
        return;
    }
    a = myMapper->readCPU(0x05BA + x);
    pushAddress(0x0077D7);
    SUB_003048();
    if (poppedEntry.value != 0x0077D7) return;
    pushAddress(0x0077DA);
    SUB_0031D7();
    if (poppedEntry.value != 0x0077DA) return;
    pushAddress(0x0077DD);
    SUB_00337B();
    if (poppedEntry.value != 0x0077DD) return;
    a = myMapper->readCPU(0x048E + x);
    opAND(0x08);
    if (flgZ) {
        a = myMapper->readCPU(0x05D3 + x);
        if (a == 0xFF) {
            goto L_0077F6;
        }
        myMapper->writeCPU(0x048E + x, 0x00);
        pushAddress(0x0077F3);
        SUB_004237();
        if (poppedEntry.value != 0x0077F3) return;
    }
L_0077F6:
    a = myMapper->readCPU(0x048E + x);
    opAND(0x80);
    popAddress();
}

void game::SUB_0077FC() {
    y = 0x00;
    do {
        if (y == 0x00) {
            goto L_007810;
        }
        a = myMapper->readCPU(0x048E + y);
        opAND(0x08);
        if (flgZ) {
            goto L_007835;
        }
        a = myMapper->readCPU(0x048E + y);
        opAND(0x04);
        if (!flgZ) {
            goto L_007835;
        }
    L_007810:
        a = myMapper->readCPU(0x048E + y);
        opAND(0x10);
        if (!flgZ) {
            goto L_00783A;
        }
        a = myMapper->readCPU(0x048E + y);
        opAND(0x20);
        if (!flgZ) {
            goto L_00783A;
        }
        pushAddress(0x00781E);
        SUB_002A61();
        if (poppedEntry.value != 0x00781E) return;
        if (!flgC) {
            goto L_007835;
        }
        a = myMapper->readCPU(0x048E + y);
        opORA(0x01);
        myMapper->writeCPU(0x048E + y, a);
        a = myMapper->readCPU(0x048E + x);
        opORA(0x40);
        myMapper->writeCPU(0x048E + x, a);
        flgC = true;
        popAddress();
        return;
    L_007835:
        opINY(1);
    } while (y != 0x03);
L_00783A:
    flgC = false;
    popAddress();
}

void game::SUB_00783C() {
    opINC(0x0447, 1);
    opINC(0x043B, 1);
    if (flgZ) {
        opINC(0x043C, 1);
    }
    opINC(0x043F, 1);
    if (flgZ) {
        opINC(0x0440, 1);
    }
    y = 0x04;
    do {
        a = myMapper->readCPU(0x0441 + y);
        flgC = false;
        opADC(0x01);
        if (a == 0x0A) {
            goto L_007861;
        }
        myMapper->writeCPU(0x0441 + y, a);
        goto L_007869;
    L_007861:
        myMapper->writeCPU(0x0441 + y, 0x00);
        opDEY(1);
    } while (!flgN);
L_007869:
    a = myMapper->readCPU(0x048E + x);
    opORA(0x20);
    myMapper->writeCPU(0x048E + x, a);
    myMapper->writeCPU(0x05BA + x, 0x04);
    myMapper->writeCPU(0x050B + x, 0x08);
    myMapper->writeCPU(0x069B + x, 0xFF);
    a = myMapper->readCPU(0x05D3 + x);
    if (a >= 0x30) {
        SUB_0079AB();
        return;
    }
    myMapper->writeCPU(0x04F2 + x, 0x01);
    a = myMapper->readCPU(0x05D3 + x);
    if (a >= 0x20) {
        SUB_007955();
        return;
    }
    a = myMapper->readCPU(0x0437);
    if (a != 0xFF) {
        a = 0x13;
        pushAddress(0x0078A2);
        SUB_00206B();
        if (poppedEntry.value != 0x0078A2) return;
        while (true) {
            opINC(0x069B + x, 1);
            a = myMapper->readCPU(0x069B + x);
            if (a >= 0x04) {
                goto L_0078C0;
            }
            flgC = false;
            opADC(0x80);
            myMapper->writeCPU(0x04D9 + x, a);
            pushAddress(0x0078B5);
            SUB_0077CD();
            if (poppedEntry.value != 0x0078B5) return;
            if (flgZ) {
                goto L_0078C0;
            }
            pushAddress(0x0078BA);
            SUB_004275();
            if (poppedEntry.value != 0x0078BA) return;
        }
    }
L_0078C0:
    a = myMapper->readCPU(0x048E + x);
    opAND(0x10);
    if (!flgZ) {
        myMapper->writeCPU(0x008B, 0x01);
        a = 0x00;
        myMapper->writeCPU(0x0089, a);
        myMapper->writeCPU(0x0088, a);
        myMapper->writeCPU(0x008A, a);
        pushAddress(0x0078D3);
        SUB_002C1A();
        if (poppedEntry.value != 0x0078D3) return;
        opDEC(0x0717, 1);
        if (!flgZ) {
            SUB_00794A();
            return;
        }
        a = 0x00;
        pushAddress(0x0078DD);
        SUB_0079E1();
        if (poppedEntry.value != 0x0078DD) return;
        y = 0x00;
        a = myMapper->readCPU(0x05D3 + x);
        if (a != 0x0A) {
            opINY(1);
            if (a != 0x0B) {
                opINY(1);
                if (a >= 0x11) {
                    opINY(1);
                    if (a < 0x14) {
                        goto L_0078F9;
                    }
                    opINY(1);
                }
            }
        }
    L_0078F9:
        a = y;
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x04D9 + x, myMapper->readCPU(0xFCD3 + y));
        opINY(1);
        myMapper->writeCPU(0x04F2 + x, myMapper->readCPU(0xFCD3 + y));
        while (true) {
            pushAddress(0x007909);
            SUB_0077CD();
            if (poppedEntry.value != 0x007909) return;
            if (flgZ) {
                SUB_00794A();
                return;
            }
            y = 0x01;
            pushAddress(0x007910);
            SUB_002A61();
            if (poppedEntry.value != 0x007910) return;
            if (flgC) {
                goto L_007929;
            }
            y = 0x02;
            pushAddress(0x007917);
            SUB_002A61();
            if (poppedEntry.value != 0x007917) return;
            if (flgC) {
                goto L_007929;
            }
            y = 0x00;
            pushAddress(0x00791E);
            SUB_002A61();
            if (poppedEntry.value != 0x00791E) return;
            if (flgC) {
                goto L_007929;
            }
            pushAddress(0x007923);
            SUB_004275();
            if (poppedEntry.value != 0x007923) return;
        }
    L_007929:
        a = 0x0F;
        pushAddress(0x00792B);
        SUB_00206B();
        if (poppedEntry.value != 0x00792B) return;
        a = myMapper->readCPU(0x04D9 + x);
        flgC = true;
        opSBC(0x7A);
        myMapper->writeCPU(0x0718, a);
        a = 0x01;
        pushAddress(0x007939);
        SUB_0079E1();
        if (poppedEntry.value != 0x007939) return;
        SUB_00794A();
        return;
    }
    myMapper->writeCPU(0x008A, 0x05);
    myMapper->writeCPU(0x008B, 0x00);
    pushAddress(0x007947);
    SUB_002C14();
    if (poppedEntry.value != 0x007947) return;
    SUB_00794A();
    return;
}

void game::SUB_00794A() {
    myMapper->writeCPU(0x048E + x, 0x00);
    pushAddress(0x00794F);
    SUB_00432D();
    if (poppedEntry.value != 0x00794F) return;
    pushAddress(0x007952);
    SUB_004237();
    if (poppedEntry.value != 0x007952) return;
    SUB_007955();
    return;
}

void game::SUB_007955() {
    a = myMapper->readCPU(0x0437);
    if (a == 0xFF) {
        SUB_00797D();
        return;
    }
    a = 0x13;
    pushAddress(0x00795E);
    SUB_00206B();
    if (poppedEntry.value != 0x00795E) return;
    SUB_007961();
    return;
}

void game::SUB_007961() {
    while (true) {
        opINC(0x069B + x, 1);
        a = myMapper->readCPU(0x069B + x);
        opLSR_A(1);
        if (a >= 0x0A) {
            SUB_00797D();
            return;
        }
        flgC = false;
        opADC(0x84);
        myMapper->writeCPU(0x04D9 + x, a);
        pushAddress(0x007972);
        SUB_0077CD();
        if (poppedEntry.value != 0x007972) return;
        if (flgZ) {
            SUB_00797D();
            return;
        }
        pushAddress(0x007977);
        SUB_004275();
        if (poppedEntry.value != 0x007977) return;
    }
    SUB_00797D();
    return;
}

void game::SUB_00797D() {
    a = myMapper->readCPU(0x05D3 + x);
    if (a < 0x30) {
        if (myMapper->readCPU(0x04F2 + x) == 0) {
            goto L_00798E;
        }
        a = 0x01;
        goto L_007990;
    L_00798E:
        a = 0x02;
    L_007990:
        pushAddress(0x007990);
        SUB_0079E1();
        if (poppedEntry.value != 0x007990) return;
        SUB_00794A();
        return;
    }
    a = myMapper->readCPU(0x05EC);
    flgC = false;
    opADC(0x03);
    if (a < 0x11) {
        goto L_0079A2;
    }
    a = 0x11;
L_0079A2:
    pushAddress(0x0079A2);
    SUB_0079E1();
    if (poppedEntry.value != 0x0079A2) return;
    opINC(0x05EC, 1);
    SUB_00794A();
    return;
}

void game::SUB_0079AB() {
    a = myMapper->readCPU(0x0437);
    if (a == 0xFF) {
        SUB_00797D();
        return;
    }
    a = 0x12;
    pushAddress(0x0079B4);
    SUB_00206B();
    if (poppedEntry.value != 0x0079B4) return;
    while (true) {
        opINC(0x069B + x, 1);
        a = myMapper->readCPU(0x069B + x);
        opLSR_A(2);
        if (a >= 0x03) {
            goto L_0079D4;
        }
        flgC = false;
        opADC(0x72);
        myMapper->writeCPU(0x04D9 + x, a);
        pushAddress(0x0079C9);
        SUB_0077CD();
        if (poppedEntry.value != 0x0079C9) return;
        if (flgZ) {
            SUB_00797D();
            return;
        }
        pushAddress(0x0079CE);
        SUB_004275();
        if (poppedEntry.value != 0x0079CE) return;
    }
L_0079D4:
    myMapper->writeCPU(0x069B + x, 0xFF);
    myMapper->writeCPU(0x04F2 + x, 0x01);
    SUB_007961();
    return;
}

void game::SUB_0079E1() {
    myMapper->writeCPU(0x00B0, a);
    flgC = false;
    opADC(0xB0);
    myMapper->writeCPU(0x04D9 + x, a);
    myMapper->writeCPU(0x04F2 + x, 0x03);
    a = myMapper->readCPU(0x048E + x);
    opAND(0x40);
    if (!flgZ) {
        a = myMapper->readCPU(0x05D3 + x);
        if (a >= 0x30) {
            goto L_007A03;
        }
        myMapper->writeCPU(0x00B0, 0x09);
        goto L_007A07;
    L_007A03:
        myMapper->writeCPU(0x00B0, 0x12);
    }
L_007A07:
    a = myMapper->readCPU(0x00B0);
    opASL_A(2);
    y = a;
    myMapper->writeCPU(0x0089, myMapper->readCPU(0xFCDF + y));
    opINY(1);
    myMapper->writeCPU(0x0088, myMapper->readCPU(0xFCDF + y));
    opINY(1);
    myMapper->writeCPU(0x008B, myMapper->readCPU(0xFCDF + y));
    opINY(1);
    myMapper->writeCPU(0x008A, myMapper->readCPU(0xFCDF + y));
    pushAddress(0x007A23);
    SUB_002C1A();
    if (poppedEntry.value != 0x007A23) return;
    myMapper->writeCPU(0x0086, 0x28);
    myMapper->writeCPU(0x0087, 0x00);
    pushAddress(0x007A2E);
    SUB_004251();
    if (poppedEntry.value != 0x007A2E) return;
    popAddress();
}

void game::SUB_007A32() {
    a = myMapper->readCPU(0x0438);
    opAND(0x03);
    if (a != 0x03) {
        a = myMapper->readCPU(0x048E + x);
        opAND(0x02);
        if (flgZ) {
            goto L_007A43;
        }
    }
    do {
        popAddress();
        return;
    L_007A43:
        opINC(0x07C7, 1);
        a = myMapper->readCPU(0x03A1);
        opLSR_A(2);
    } while (a >= myMapper->readCPU(0x07C7));
    myMapper->writeCPU(0x07C7, 0xFF);
    y = 0x00;
    pushAddress(0x007A57);
    SUB_0030BC();
    if (poppedEntry.value != 0x007A57) return;
    pushAddress(0x007A5A);
    SUB_0030E5();
    if (poppedEntry.value != 0x007A5A) return;
    a = 0x70;
    myMapper->writeCPU(0x00B0, a);
    myMapper->writeCPU(0x00B2, a);
    a = 0x90;
    myMapper->writeCPU(0x00B1, a);
    myMapper->writeCPU(0x00B3, a);
    pushAddress(0x007A69);
    SUB_002A00();
    if (poppedEntry.value != 0x007A69) return;
    if (!flgC) {
        popAddress();
        return;
    }
    y = 0x00;
    pushAddress(0x007A71);
    SUB_0030BC();
    if (poppedEntry.value != 0x007A71) return;
    pushAddress(0x007A74);
    SUB_0030E5();
    if (poppedEntry.value != 0x007A74) return;
    a = 0x20;
    myMapper->writeCPU(0x00B0, a);
    myMapper->writeCPU(0x00B2, a);
    a = 0xE0;
    myMapper->writeCPU(0x00B1, a);
    myMapper->writeCPU(0x00B3, a);
    pushAddress(0x007A83);
    SUB_002A00();
    if (poppedEntry.value != 0x007A83) return;
    if (flgC) {
        popAddress();
        return;
    }
    y = 0x00;
    pushAddress(0x007A8B);
    SUB_0030E5();
    if (poppedEntry.value != 0x007A8B) return;
    pushAddress(0x007A8E);
    SUB_0030BC();
    if (poppedEntry.value != 0x007A8E) return;
    pushAddress(0x007A91);
    SUB_002DC9();
    if (poppedEntry.value != 0x007A91) return;
    if (a < 0x06) {
        popAddress();
        return;
    }
    if (a >= 0x0B) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x00B0, a);
    a = myMapper->readCPU(0x05D3 + x);
    if (a == 0x00) {
        a = myMapper->readCPU(0x050B + x);
        flgC = true;
        opSBC(0x03);
        opAND(0x0F);
        if (a >= myMapper->readCPU(0x00B0)) {
            popAddress();
            return;
        }
    }
    a = myMapper->readCPU(0x050B + x);
    flgC = false;
    opADC(0x02);
    if (a >= myMapper->readCPU(0x00B0)) {
        goto L_007ABF;
    }
    popAddress();
    return;
L_007ABF:
    y = 0x03;
    do {
        a = myMapper->readCPU(0x048E + y);
        opAND(0x08);
        if (flgZ) {
            goto L_007ACE;
        }
        opINY(1);
    } while (y < 0x0B);
    popAddress();
    return;
L_007ACE:
    myMapper->writeCPU(0x050B + y, myMapper->readCPU(0x00B0));
    myMapper->writeCPU(0x05BA + y, 0x14);
    myMapper->writeCPU(0x0588 + y, myMapper->readCPU(0x0588 + x));
    myMapper->writeCPU(0x056F + y, myMapper->readCPU(0x056F + x));
    myMapper->writeCPU(0x053D + y, myMapper->readCPU(0x053D + x));
    myMapper->writeCPU(0x0524 + y, myMapper->readCPU(0x0524 + x));
    myMapper->writeCPU(0x04F2 + y, 0x01);
    myMapper->writeCPU(0x048E + y, 0x88);
    myMapper->writeCPU(0x070C, 0x00);
    popAddress();
}

void game::SUB_007B00() {
    if (myMapper->readCPU(0x070D) == 0) {
        goto L_007B13;
    }
    y = 0x01;
    a = myMapper->readCPU(0x070E + y);
    flgC = true;
    opSBC(0x01);
    if (!flgZ) {
        myMapper->writeCPU(0x070E + y, a);
        do {
            popAddress();
            return;
        L_007B13:
            opINC(0x07C6, 1);
            a = myMapper->readCPU(0x03A1);
            opLSR_A(4);
        } while (a >= myMapper->readCPU(0x07C6));
        myMapper->writeCPU(0x07C6, 0x00);
        a = myMapper->readCPU(0x05D3 + x);
        if (a == 0xFF) {
            a = 0x02;
        }
        else {
            a = 0x00;
            flgC = true;
            opSBC(myMapper->readCPU(0x03A1));
            opROL_A(2);
            opAND(0x01);
        }
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x008A, myMapper->readCPU(0xFD2F + y));
        opINY(1);
        myMapper->writeCPU(0x008B, myMapper->readCPU(0xFD2F + y));
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x070E + y, a);
        myMapper->writeCPU(0x0087, a);
        opINY(1);
        myMapper->writeCPU(0x070E + y, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
        opINY(1);
        do {
            myMapper->writeCPU(0x070E + y, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
            opINY(1);
            opDEC(0x0087, 1);
        } while (!flgZ);
        y = 0x00;
        pushAddress(0x007B66);
        SUB_0030E5();
        if (poppedEntry.value != 0x007B66) return;
        pushAddress(0x007B69);
        SUB_0030BC();
        if (poppedEntry.value != 0x007B69) return;
        pushAddress(0x007B6C);
        SUB_002DC9();
        if (poppedEntry.value != 0x007B6C) return;
        myMapper->writeCPU(0x00B0, a);
        myMapper->writeCPU(0x0087, myMapper->readCPU(0x070E));
        y = 0x02;
        do {
            a = myMapper->readCPU(0x070E + y);
            flgC = false;
            opADC(myMapper->readCPU(0x00B0));
            myMapper->writeCPU(0x070E + y, a);
            opINY(1);
            opDEC(0x0087, 1);
        } while (!flgZ);
        myMapper->writeCPU(0x070D, 0xFF);
        popAddress();
        return;
    }
    y = 0x02;
    a = myMapper->readCPU(0x070E);
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x00B0, a);
    do {
        a = myMapper->readCPU(0x070E + y);
        if (a != 0xFF) {
            goto L_007BA8;
        }
        opINY(1);
    } while (y < myMapper->readCPU(0x00B0));
    myMapper->writeCPU(0x070D, 0x00);
    popAddress();
    return;
L_007BA8:
    myMapper->writeCPU(0x00B0, a);
    myMapper->writeCPU(0x071D, y);
    y = 0x03;
    do {
        a = myMapper->readCPU(0x048E + y);
        opAND(0x08);
        if (flgZ) {
            goto L_007BBE;
        }
        opINY(1);
    } while (y < 0x0B);
    goto L_007C2F;
L_007BBE:
    myMapper->writeCPU(0x050B + y, myMapper->readCPU(0x00B0));
    myMapper->writeCPU(0x05BA + y, 0x14);
    myMapper->writeCPU(0x0588 + y, myMapper->readCPU(0x0588 + x));
    myMapper->writeCPU(0x056F + y, myMapper->readCPU(0x056F + x));
    myMapper->writeCPU(0x053D + y, myMapper->readCPU(0x053D + x));
    myMapper->writeCPU(0x0524 + y, myMapper->readCPU(0x0524 + x));
    myMapper->writeCPU(0x04F2 + y, 0x01);
    myMapper->writeCPU(0x048E + y, 0x88);
    a = myMapper->readCPU(0x05D3 + x);
    if (a == 0xFF) {
        a = myMapper->readCPU(0x0588 + y);
        flgC = true;
        opSBC(0x07);
        myMapper->writeCPU(0x0588 + y, a);
        a = myMapper->readCPU(0x056F + y);
        opSBC(0x00);
        myMapper->writeCPU(0x056F + y, a);
        a = myMapper->readCPU(0x03A0);
        opAND(0x0F);
        flgC = false;
        opADC(myMapper->readCPU(0x0588 + y));
        myMapper->writeCPU(0x0588 + y, a);
        a = myMapper->readCPU(0x056F + y);
        opADC(0x00);
        myMapper->writeCPU(0x056F + y, a);
        a = myMapper->readCPU(0x053D + y);
        flgC = false;
        opADC(0x40);
        myMapper->writeCPU(0x053D + y, a);
        a = myMapper->readCPU(0x0524 + y);
        opADC(0x00);
        myMapper->writeCPU(0x0524 + y, a);
    }
    y = myMapper->readCPU(0x071D);
    myMapper->writeCPU(0x070E + y, 0xFF);
L_007C2F:
    a = myMapper->readCPU(0x05D3 + x);
    if (a != 0xFF) {
        goto L_007C3B;
    }
    a = 0x02;
    goto L_007C3E;
L_007C3B:
    flgC = true;
    opSBC(0x30);
L_007C3E:
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x008A, myMapper->readCPU(0xFD2F + y));
    opINY(1);
    myMapper->writeCPU(0x008B, myMapper->readCPU(0xFD2F + y));
    y = 0x01;
    myMapper->writeCPU(0x070E + y, myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y));
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
    case 0xEEB4:
        SUB_006EB4();
        break;
    case 0xEE8C:
        SUB_006E8C();
        break;
    case 0xEED7:
        SUB_006ED7();
        break;
    case 0xEEEA:
        SUB_006EEA();
        break;
    case 0xEF00:
        SUB_006F00();
        break;
    case 0xEF13:
        SUB_006F13();
        break;
    case 0xEF2B:
        SUB_006F2B();
        break;
    case 0xEF49:
        SUB_006F49();
        break;
    case 0xEF6B:
        SUB_006F6B();
        break;
    case 0xEF6E:
        SUB_006F6E();
        break;
    case 0xEF8E:
        SUB_006F8E();
        break;
    case 0xEFA0:
        SUB_006FA0();
        break;
    case 0xEFAD:
        SUB_006FAD();
        break;
    case 0xEFB5:
        SUB_006FB5();
        break;
    case 0xEFBD:
        SUB_006FBD();
        break;
    case 0xEFC5:
        SUB_006FC5();
        break;
    case 0xEFCD:
        SUB_006FCD();
        break;
    case 0xEFDA:
        SUB_006FDA();
        break;
    default:
        bool test = true;
    }
}

void game::switchThread() {
    if (runningThread.xIdx == xIdx) {
        return;
    } 

    threadData oldThread = runningThread;
    for (int newIdx = 0; newIdx < threadList.size(); newIdx++) {
        if (threadList[newIdx].xIdx == xIdx) {
            runningThread = threadList[newIdx];
            SDL_LockMutex(threadList[newIdx].lock);
            SDL_SignalCondition(threadList[newIdx].cond);
            SDL_UnlockMutex(threadList[newIdx].lock);
            if (oldThread.threadIdx != -1) {
                holdThread(oldThread.threadIdx);
            }
            return;
        }
    }
    bool test = true;
}

int game::gameThread(void* ptr) {
    threadData* tThread = (threadData*)ptr;
    SDL_Mutex* tmpLock = tThread->lock;
    SDL_LockMutex(tmpLock);
    try {
        switch (tThread->threadId) {
        case 0x0033D5:
            tThread->myGame->SUB_0033D5();
            break;
        case 0x003509:
            tThread->myGame->SUB_003509();
            break;
        case 0x003588:
            tThread->myGame->SUB_003588();
            break;
        case 0x00365F:
            tThread->myGame->SUB_00365F();
            break;
        case 0x0037C3:
            tThread->myGame->SUB_0037C3();
            break;
        case 0x0043CA:
            tThread->myGame->SUB_0043CA();
            break;
        case 0x00506A:
            tThread->myGame->SUB_00506A();
            break;
        case 0x006C0C:
            tThread->myGame->SUB_006C0C();
            break;
        case 0x006C45:
            tThread->myGame->SUB_006C45();
            break;
        case 0x006C79:
            tThread->myGame->SUB_006C79();
            break;
        case 0x006CAD:
            tThread->myGame->SUB_006CAD();
            break;
        case 0x006CF1:
            tThread->myGame->SUB_006CF1();
            break;
        case 0x006D2A:
            tThread->myGame->SUB_006D2A();
            break;
        case 0x006D39:
            tThread->myGame->SUB_006D39();
            break;
        case 0x006D48:
            tThread->myGame->SUB_006D48();
            break;
        default:
            bool test = true;
        }
        tThread->myGame->threadList[tThread->threadIdx].threadId = 0;
        tThread->myGame->threadList[tThread->threadIdx].threadIdx = -1;
    }
    catch (const std::runtime_error& e) {
    }
    SDL_UnlockMutex(tmpLock);
    SDL_DestroyMutex(tThread->lock);
    SDL_DestroyCondition(tThread->cond);
    free(tThread);

    return 0;
}

void game::createThread(Uint32 address){
    threadData oldThread = runningThread;

    threadData* newThread = (threadData*)malloc(sizeof(threadData));
    newThread->threadIdx = threadList.size();
    newThread->threadId = address;
	newThread->thread = NULL;
	newThread->lock = SDL_CreateMutex();
	newThread->cond = SDL_CreateCondition();
	newThread->myGame = this;
    newThread->continueAddress = 0;
    newThread->xIdx = -1;

    threadList.push_back(*newThread);
    SDL_Thread* thread = SDL_CreateThread(game::gameThread, std::to_string(address).c_str(), newThread);
    threadList[threadList.size() - 1].thread = thread;
    runningThread = threadList[threadList.size() - 1];

    if (oldThread.threadIdx != -1) {
        holdThread(oldThread.threadIdx);
    }
}

void game::holdThread(int threadIdx){
    SDL_WaitCondition(threadList[threadIdx].cond, threadList[threadIdx].lock);
    if (threadList[threadIdx].threadIdx == -1) {
		throw std::runtime_error("Thread already finished");
        return;
    }
}


void game::markThread() {
    runningThread.continueAddress = pushedAddress;
    runningThread.xIdx = myMapper->readCPU(0x0000);
    threadList[runningThread.threadIdx] = runningThread;

    for (int newIdx = 0; newIdx < threadList.size(); newIdx++) {
        if ((threadList[newIdx].xIdx == runningThread.xIdx) && (newIdx != runningThread.threadIdx)) {
            threadList[newIdx].threadIdx = -1;
            threadList[newIdx].threadId = 0;
            threadList[newIdx].continueAddress = 0;
            threadList[newIdx].xIdx = -1;
            SDL_LockMutex(threadList[newIdx].lock);
            SDL_SignalCondition(threadList[newIdx].cond);
            SDL_UnlockMutex(threadList[newIdx].lock);
            SDL_DetachThread(threadList[newIdx].thread);
        }
    }
}
