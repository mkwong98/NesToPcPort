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


void game::SUB_010000() {
    jump(0x8012);
    return;
}

void game::SUB_010003() {
    jump(0x80A6);
    return;
}

void game::SUB_01000C() {
    jump(0x811A);
    return;
}

void game::SUB_01000F() {
    jump(0x8031);
    return;
}

void game::SUB_010012() {
    pushAddress(0x8014);
    jump(0x85BB);
    if (handleReturnAddress(poppedEntry.value, 0x8014)) return;
    a = 0x00;
    myMapper->writeCPU(0x06EC, a);
    myMapper->writeCPU(0x06ED, a);
    myMapper->writeCPU(0x06EE, a);
    myMapper->writeCPU(0x06EF, a);
    x = 0x0F;
    do {
        myMapper->writeCPU(0x4000 + x, a);
        opDEX(1);
    } while (!flgN);
    a = 0x0F;
    myMapper->writeCPU(0x4015, a);
    popAddress();
}

void game::SUB_010031() {
    opASL_A(2);
    opORA(0x03);
    y = a;
    x = 0x03;
    do {
        a = myMapper->readCPU(0x8793 + y);
        setLoadFlag(a);
        if (flgN) {
            goto L_010079;
        }
        myMapper->writeCPU(0x06F0, y);
        opASL_A(1);
        y = a;
        myMapper->writeCPU(0x06CD + x, myMapper->readCPU(0x8733 + y));
        myMapper->writeCPU(0x06D1 + x, myMapper->readCPU(0x8734 + y));
        a = 0x01;
        myMapper->writeCPU(0x06EC + x, a);
        myMapper->writeCPU(0x07C3 + x, a);
        a = 0x00;
        y = myMapper->readCPU(0x872F + x);
        myMapper->writeCPU(0x4000 + y, a);
        myMapper->writeCPU(0x4001 + y, a);
        myMapper->writeCPU(0x4002 + y, a);
        myMapper->writeCPU(0x4003 + y, a);
        myMapper->writeCPU(0x078B + x, a);
        myMapper->writeCPU(0x07E3 + x, a);
        myMapper->writeCPU(0x07BB + x, a);
        myMapper->writeCPU(0x07F3 + x, a);
        myMapper->writeCPU(0x07EF + x, a);
        y = myMapper->readCPU(0x06F0);
    L_010079:
        opDEY(1);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0100A6() {
    opASL_A(3);
    x = a;
    pushAddress(0x80AC);
    jump(0x85BB);
    if (handleReturnAddress(poppedEntry.value, 0x80AC)) return;
    myMapper->writeCPU(0x06D8, myMapper->readCPU(0x8EB4 + x));
    myMapper->writeCPU(0x06DC, myMapper->readCPU(0x8EB5 + x));
    myMapper->writeCPU(0x06D9, myMapper->readCPU(0x8EB6 + x));
    myMapper->writeCPU(0x06DD, myMapper->readCPU(0x8EB7 + x));
    myMapper->writeCPU(0x06DA, myMapper->readCPU(0x8EB8 + x));
    myMapper->writeCPU(0x06DE, myMapper->readCPU(0x8EB9 + x));
    myMapper->writeCPU(0x06DB, myMapper->readCPU(0x8EBA + x));
    myMapper->writeCPU(0x06DF, myMapper->readCPU(0x8EBB + x));
    myMapper->writeCPU(0x06D5, 0x03);
    do {
        x = myMapper->readCPU(0x06D5);
        a = 0x00;
        myMapper->writeCPU(0x06E4 + x, a);
        myMapper->writeCPU(0x0707 + x, a);
        myMapper->writeCPU(0x06E0 + x, a);
        pushAddress(0x80F2);
        jump(0x830A);
        if (handleReturnAddress(poppedEntry.value, 0x80F2)) return;
        x = myMapper->readCPU(0x06D5);
        a = 0x00;
        myMapper->writeCPU(0x076B + x, a);
        myMapper->writeCPU(0x0743 + x, a);
        myMapper->writeCPU(0x077B + x, a);
        a = 0x01;
        myMapper->writeCPU(0x074B + x, a);
        myMapper->writeCPU(0x06E8 + x, a);
        myMapper->writeCPU(0x0767 + x, a);
        opDEC(0x06D5, 1);
    } while (!flgN);
    a = 0x02;
    myMapper->writeCPU(0x074C, a);
    myMapper->writeCPU(0x074E, a);
    popAddress();
}

void game::SUB_01011A() {
    myMapper->writeCPU(0x06D5, 0x03);
    while (true) {
        x = myMapper->readCPU(0x06D5);
        myMapper->writeCPU(0x06D6, myMapper->readCPU(0x872F + x));
        if (myMapper->readCPU(0x06EC + x) == 0x01) {
            myMapper->writeCPU(0x06CB, myMapper->readCPU(0x073B + x));
            myMapper->writeCPU(0x06CC, myMapper->readCPU(0x073F + x));
            a = myMapper->readCPU(0x06CD + x);
            opPHA();
            a = myMapper->readCPU(0x06D1 + x);
            opPHA();
            a = x;
            flgC = false;
            opADC(0x78);
            myMapper->writeCPU(0x06D5, a);
            x = a;
            opPLA();
            myMapper->writeCPU(0x073F + x, a);
            opPLA();
            myMapper->writeCPU(0x073B + x, a);
            pushAddress(0x8155);
            jump(0x825D);
            if (handleReturnAddress(poppedEntry.value, 0x8155)) return;
            a = myMapper->readCPU(0x0674 + x);
            if (a != 0x02) {
                pushAddress(0x815F);
                jump(0x8209);
                if (handleReturnAddress(poppedEntry.value, 0x815F)) return;
            }
            a = x;
            flgC = true;
            opSBC(0x78);
            myMapper->writeCPU(0x06D5, a);
            x = a;
            myMapper->writeCPU(0x073B + x, myMapper->readCPU(0x06CB));
            myMapper->writeCPU(0x073F + x, myMapper->readCPU(0x06CC));
        }
        a = myMapper->readCPU(0x06E8 + x);
        setLoadFlag(a);
        if (flgZ) {
        }
        else {
            pushAddress(0x820A);
            jump(0x825D);
            if (handleReturnAddress(poppedEntry.value, 0x820A)) return;
            a = myMapper->readCPU(0x06E8 + x);
            setLoadFlag(a);
            if (!flgZ) {
                a = myMapper->readCPU(0x06EC + x);
                setLoadFlag(a);
                if (!flgZ) {
                    if (a == 0x01) {
                        goto L_010200;
                    }
                    a = myMapper->readCPU(0x0763 + x);
                    setLoadFlag(a);
                    if (flgZ) {
                        goto L_010200;
                    }
                    myMapper->writeCPU(0x06EC + x, 0x00);
                }
                a = myMapper->readCPU(0x077B + x);
                setLoadFlag(a);
                if (!flgZ) {
                    pushAddress(0x819E);
                    jump(0x855B);
                    if (handleReturnAddress(poppedEntry.value, 0x819E)) return;
                }
                else {
                    if (myMapper->readCPU(0x0763 + x) == 0) {
                        goto L_0101E3;
                    }
                    a = myMapper->readCPU(0x075F + x);
                    flgC = false;
                    opADC(myMapper->readCPU(0x0707 + x));
                    if (x == 0x02) {
                        flgC = false;
                        opADC(0x0C);
                    }
                    opASL_A(1);
                    y = a;
                    myMapper->writeCPU(0x0773 + x, myMapper->readCPU(0x860F + y));
                    myMapper->writeCPU(0x06CA, myMapper->readCPU(0x8610 + y));
                    y = myMapper->readCPU(0x06D6);
                    myMapper->writeCPU(0x4002 + y, myMapper->readCPU(0x0773 + x));
                    a = myMapper->readCPU(0x06CA);
                    if (x == 0x02) {
                        opORA(myMapper->readCPU(0x0723 + x));
                    }
                    myMapper->writeCPU(0x4003 + y, a);
                    if (x == 0x02) {
                        myMapper->writeCPU(0x4008, myMapper->readCPU(0x0727 + x));
                    }
                }
            L_0101E3:
                a = myMapper->readCPU(0x076B + x);
                setLoadFlag(a);
                if (!flgZ) {
                    pushAddress(0x81EA);
                    jump(0x8507);
                    if (handleReturnAddress(poppedEntry.value, 0x81EA)) return;
                }
                if (x == 0x02) {
                    goto L_010200;
                }
                pushAddress(0x81F1);
                jump(0x83A6);
                if (handleReturnAddress(poppedEntry.value, 0x81F1)) return;
                y = myMapper->readCPU(0x06D6);
                a = myMapper->readCPU(0x0713 + x);
                opORA(myMapper->readCPU(0x0747 + x));
                opORA(0x30);
                myMapper->writeCPU(0x4000 + y, a);
            }
        }
    L_010200:
        opDEC(0x06D5, 1);
        if (flgN) {
            goto L_010208;
        }
    }
L_010208:
    popAddress();
}

void game::SUB_010209() {
    if (myMapper->readCPU(0x0763 + x) == 0) {
        goto L_01023F;
    }
    a = myMapper->readCPU(0x075F + x);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0773 + x, myMapper->readCPU(0x860F + y));
    myMapper->writeCPU(0x06CA, myMapper->readCPU(0x8610 + y));
    y = myMapper->readCPU(0x06D6);
    myMapper->writeCPU(0x4002 + y, myMapper->readCPU(0x0773 + x));
    a = myMapper->readCPU(0x06CA);
    if (x == 0x7A) {
        opORA(myMapper->readCPU(0x079D));
    }
    myMapper->writeCPU(0x4003 + y, a);
    if (x == 0x7A) {
        myMapper->writeCPU(0x4008, myMapper->readCPU(0x07A1));
    }
L_01023F:
    a = myMapper->readCPU(0x076B + x);
    setLoadFlag(a);
    if (!flgZ) {
        pushAddress(0x8246);
        jump(0x8507);
        if (handleReturnAddress(poppedEntry.value, 0x8246)) return;
    }
    if (x == 0x7A) {
        goto L_01025C;
    }
    pushAddress(0x824D);
    jump(0x83A6);
    if (handleReturnAddress(poppedEntry.value, 0x824D)) return;
    y = myMapper->readCPU(0x06D6);
    a = myMapper->readCPU(0x0713 + x);
    opORA(myMapper->readCPU(0x0747 + x));
    opORA(0x30);
    myMapper->writeCPU(0x4000 + y, a);
L_01025C:
    popAddress();
}

void game::SUB_01025D() {
    opDEC(0x074B + x, 1);
    if (flgZ) {
        goto L_010268;
    }
    myMapper->writeCPU(0x0763 + x, 0x00);
    popAddress();
    return;
L_010268:
    myMapper->writeCPU(0x00F0, myMapper->readCPU(0x073B + x));
    a = myMapper->readCPU(0x073F + x);
    myMapper->writeCPU(0x00F1, a);
    pushAddress(0x8274);
    jump(0x8279);
    if (handleReturnAddress(poppedEntry.value, 0x8274)) return;
    opINC(0x0777 + x, 1);
    popAddress();
}

void game::SUB_010279() {
    y = myMapper->readCPU(0x0777 + x);
    a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        if (a != 0x60) {
            goto L_010293;
        }
        if (x == 0x02) {
            a = 0x00;
            myMapper->writeCPU(0x4008, a);
        }
        goto L_0102C3;
    L_010293:
        myMapper->writeCPU(0x075F + x, a);
        pushAddress(0x8298);
        jump(0x8425);
        if (handleReturnAddress(poppedEntry.value, 0x8298)) return;
        a = 0x01;
        myMapper->writeCPU(0x0763 + x, a);
        myMapper->writeCPU(0x0767 + x, a);
        a = 0x00;
        if (myMapper->readCPU(0x076B + x) != 0) {
            myMapper->writeCPU(0x074F + x, myMapper->readCPU(0x0753 + x));
            myMapper->writeCPU(0x0757 + x, myMapper->readCPU(0x075B + x));
        }
        if (myMapper->readCPU(0x077B + x) != 0) {
            myMapper->writeCPU(0x0703 + x, 0x00);
            myMapper->writeCPU(0x06FB + x, 0x01);
        }
    L_0102C3:
        if (myMapper->readCPU(0x0743 + x) != 0) {
            a = myMapper->readCPU(0x077F + x);
        }
        else {
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
        }
        myMapper->writeCPU(0x06F1, a);
        a = myMapper->readCPU(0x0733 + x);
        setLoadFlag(a);
        if (!flgN) {
            goto L_0102E8;
        }
        opAND(0x7F);
        myMapper->writeCPU(0x06F2, a);
        a = myMapper->readCPU(0x06F1);
        flgC = true;
        opSBC(myMapper->readCPU(0x06F2));
        myMapper->writeCPU(0x072F + x, a);
    L_0102E8:
        myMapper->writeCPU(0x074B + x, myMapper->readCPU(0x06F1));
        myMapper->writeCPU(0x0777 + x, y);
        popAddress();
        return;
    }
    x = a;
    myMapper->writeCPU(0x00F8, myMapper->readCPU(0x8691 + x));
    a = myMapper->readCPU(0x869C + x);
    myMapper->writeCPU(0x00F9, a);
    x = myMapper->readCPU(0x06D5);
    jump(myMapper->readCPU(0x00F8) + (myMapper->readCPU((0x00F8 + 1) & 0x00ff) << 8));
}

void game::SUB_010304() {
    pushAddress(0x8306);
    jump(0x830A);
    if (handleReturnAddress(poppedEntry.value, 0x8306)) return;
    jump(0x8279);
    return;
}

void game::SUB_01030A() {
    x = myMapper->readCPU(0x06D5);
    myMapper->writeCPU(0x00F2, myMapper->readCPU(0x06D8 + x));
    myMapper->writeCPU(0x00F3, myMapper->readCPU(0x06DC + x));
    myMapper->writeCPU(0x0777 + x, 0x00);
    if (myMapper->readCPU(0x0707 + x) == 0) {
        jump(0x832B);
        return;
    }
    if (myMapper->readCPU(0x06E0 + x) != 0) {
        jump(0x832B);
        return;
    }
    myMapper->writeCPU(0x0707 + x, 0x00);
    SUB_01032B();
    return;
}

void game::SUB_01032B() {
    y = myMapper->readCPU(0x06E4 + x);
    a = myMapper->readCPU(myMapper->readCPU(0x00F2) + (myMapper->readCPU((0x00F2 + 1) & 0x00ff) << 8) + y);
    if (a < 0xF0) {
        y = a;
        a = myMapper->readCPU(0x89F9 + y);
        myMapper->writeCPU(0x00F0, a);
        myMapper->writeCPU(0x073B + x, a);
        a = myMapper->readCPU(0x8A8F + y);
        myMapper->writeCPU(0x00F1, a);
        myMapper->writeCPU(0x073F + x, a);
        a = myMapper->readCPU(0x06E0 + x);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x06E0 + x, 1);
            if (flgZ) {
                goto L_010350;
            }
            popAddress();
            return;
        }
    L_010350:
        opINC(0x06E4 + x, 1);
        popAddress();
        return;
    }
    x = a;
    myMapper->writeCPU(0x00F8, myMapper->readCPU(0x8637 + x));
    a = myMapper->readCPU(0x863B + x);
    myMapper->writeCPU(0x00F9, a);
    x = myMapper->readCPU(0x06D5);
    jump(myMapper->readCPU(0x00F8) + (myMapper->readCPU((0x00F8 + 1) & 0x00ff) << 8));
}

void game::SUB_010365() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F2) + (myMapper->readCPU((0x00F2 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x06E4 + x, a);
    jump(0x832B);
    return;
}

void game::SUB_01036E() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F2) + (myMapper->readCPU((0x00F2 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x06E0 + x, a);
    opINC(0x06E4 + x, 2);
    jump(0x832B);
    return;
}

void game::SUB_01037D() {
    myMapper->writeCPU(0x06E8 + x, 0x00);
    y = myMapper->readCPU(0x06D6);
    a = 0x00;
    myMapper->writeCPU(0x0713 + x, a);
    myMapper->writeCPU(0x4000 + y, a);
    myMapper->writeCPU(0x4001 + y, a);
    myMapper->writeCPU(0x070F + x, 0x06);
    popAddress();
}

void game::SUB_010396() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F2) + (myMapper->readCPU((0x00F2 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0707 + x, a);
    opINC(0x06E4 + x, 2);
    jump(0x832B);
    return;
}

void game::SUB_0103A5() {
    popAddress();
}

void game::SUB_0103A6() {
    a = myMapper->readCPU(0x070F + x);
    if (a >= 0x06) {
        jump(0x83A5);
        return;
    }
    y = a;
    myMapper->writeCPU(0x00F8, myMapper->readCPU(0x83BC + y));
    opINY(1);
    a = myMapper->readCPU(0x83BC + y);
    myMapper->writeCPU(0x00F9, a);
    jump(myMapper->readCPU(0x00F8) + (myMapper->readCPU((0x00F8 + 1) & 0x00ff) << 8));
}

void game::SUB_0103C2() {
    opINC(0x0717 + x, 1);
    if (myMapper->readCPU(0x0717 + x) != myMapper->readCPU(0x0723 + x)) {
        jump(0x83E9);
        return;
    }
    myMapper->writeCPU(0x0717 + x, 0x00);
    a = myMapper->readCPU(0x0713 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x072B + x));
    myMapper->writeCPU(0x0713 + x, a);
    if (a < myMapper->readCPU(0x070B + x)) {
        jump(0x83E9);
        return;
    }
    a = myMapper->readCPU(0x070B + x);
    setLoadFlag(a);
    myMapper->writeCPU(0x0713 + x, a);
    if (!flgZ) {
        jump(0x83F5);
        return;
    }
    SUB_0103E9();
    return;
}

void game::SUB_0103E9() {
    popAddress();
}

void game::SUB_0103EA() {
    opINC(0x071B + x, 1);
    a = myMapper->readCPU(0x071B + x);
    if (a != myMapper->readCPU(0x072F + x)) {
        jump(0x83E9);
        return;
    }
    SUB_0103F5();
    return;
}

void game::SUB_0103F5() {
    opINC(0x070F + x, 2);
    jump(0x83A6);
    return;
}

void game::SUB_0103FE() {
    opINC(0x071F + x, 1);
    if (myMapper->readCPU(0x071F + x) != myMapper->readCPU(0x0727 + x)) {
        jump(0x83E9);
        return;
    }
    myMapper->writeCPU(0x071F + x, 0x00);
    a = myMapper->readCPU(0x0713 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0737 + x));
    myMapper->writeCPU(0x0713 + x, a);
    if (flgZ) {
        jump(0x83F5);
        return;
    }
    if (!flgN) {
        jump(0x83E9);
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    myMapper->writeCPU(0x0713 + x, a);
    if (flgZ) {
        jump(0x83F5);
        return;
    }
    popAddress();
}

void game::SUB_010425() {
    a = 0x00;
    myMapper->writeCPU(0x070F + x, a);
    myMapper->writeCPU(0x0713 + x, a);
    myMapper->writeCPU(0x0717 + x, a);
    myMapper->writeCPU(0x071B + x, a);
    myMapper->writeCPU(0x071F + x, a);
    popAddress();
}

void game::SUB_010437() {
    opINY(1);
    myMapper->writeCPU(0x06D7, myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = y;
    myMapper->writeCPU(0x0777 + x, a);
    pushAddress(0x8444);
    jump(0x8448);
    if (handleReturnAddress(poppedEntry.value, 0x8444)) return;
    jump(0x8279);
    return;
}

void game::SUB_010448() {
    a = myMapper->readCPU(0x06D7);
    opASL_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x06D7));
    opADC(myMapper->readCPU(0x06D7));
    opADC(myMapper->readCPU(0x06D7));
    y = a;
    myMapper->writeCPU(0x0747 + x, myMapper->readCPU(0x8DCA + y));
    myMapper->writeCPU(0x070B + x, myMapper->readCPU(0x8DCB + y));
    myMapper->writeCPU(0x072B + x, myMapper->readCPU(0x8DCC + y));
    a = myMapper->readCPU(0x8DCD + y);
    myMapper->writeCPU(0x072F + x, a);
    myMapper->writeCPU(0x0733 + x, a);
    myMapper->writeCPU(0x0737 + x, myMapper->readCPU(0x8DCE + y));
    myMapper->writeCPU(0x0723 + x, myMapper->readCPU(0x8DCF + y));
    a = myMapper->readCPU(0x8DD0 + y);
    myMapper->writeCPU(0x0727 + x, a);
    popAddress();
}

void game::SUB_010486() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x00F6, y);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0753 + x, myMapper->readCPU(0x8B25 + y));
    myMapper->writeCPU(0x075B + x, myMapper->readCPU(0x8B26 + y));
    a = myMapper->readCPU(0x00F6);
    myMapper->writeCPU(0x0777 + x, a);
    myMapper->writeCPU(0x076B + x, a);
    a = 0x00;
    myMapper->writeCPU(0x077B + x, a);
    jump(0x8279);
    return;
}

void game::SUB_0104AA() {
    myMapper->writeCPU(0x076B + x, 0x00);
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x00F4, myMapper->readCPU(0x8C76 + x));
    myMapper->writeCPU(0x00F5, myMapper->readCPU(0x8C77 + x));
    opINY(1);
    a = y;
    x = myMapper->readCPU(0x06D5);
    myMapper->writeCPU(0x0777 + x, a);
    y = 0x00;
    myMapper->writeCPU(0x06FF + x, myMapper->readCPU(myMapper->readCPU(0x00F4) + (myMapper->readCPU((0x00F4 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x077B + x, myMapper->readCPU(myMapper->readCPU(0x00F4) + (myMapper->readCPU((0x00F4 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x00F4);
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x06F3 + x, a);
    a = myMapper->readCPU(0x00F5);
    opADC(0x00);
    myMapper->writeCPU(0x06F7 + x, a);
    jump(0x8279);
    return;
}

void game::SUB_0104E5() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x077F + x, a);
    myMapper->writeCPU(0x0743 + x, a);
    opINY(1);
    a = y;
    myMapper->writeCPU(0x0777 + x, a);
    jump(0x8279);
    return;
}

void game::SUB_0104F6() {
    a = 0x00;
    myMapper->writeCPU(0x0743 + x, a);
    opINC(0x0777 + x, 1);
    jump(0x8279);
    return;
}

void game::SUB_010501() {
    opINC(0x0777 + x, 1);
    jump(0x8279);
    return;
}

void game::SUB_010507() {
    a = myMapper->readCPU(0x076B + x);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x0767 + x, 1);
        if (!flgZ) {
            goto L_01054A;
        }
        myMapper->writeCPU(0x00F0, myMapper->readCPU(0x074F + x));
        myMapper->writeCPU(0x00F1, myMapper->readCPU(0x0757 + x));
        while (true) {
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
            if (a != 0x4C) {
                goto L_010532;
            }
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
            opPHA();
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x00F1, a);
            opPLA();
            myMapper->writeCPU(0x00F0, a);
        }
    L_010532:
        myMapper->writeCPU(0x0767 + x, a);
        opINY(1);
        myMapper->writeCPU(0x076F + x, myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y));
        a = myMapper->readCPU(0x00F0);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x074F + x, a);
        a = myMapper->readCPU(0x00F1);
        opADC(0x00);
        myMapper->writeCPU(0x0757 + x, a);
    L_01054A:
        y = myMapper->readCPU(0x06D6);
        a = myMapper->readCPU(0x0773 + x);
        flgC = false;
        opADC(myMapper->readCPU(0x076F + x));
        myMapper->writeCPU(0x0773 + x, a);
        myMapper->writeCPU(0x4002 + y, a);
    }
    popAddress();
}

void game::SUB_01055B() {
    a = myMapper->readCPU(0x077B + x);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x06FB + x, 1);
        if (!flgZ) {
            popAddress();
            return;
        }
        myMapper->writeCPU(0x00F0, myMapper->readCPU(0x06F3 + x));
        myMapper->writeCPU(0x00F1, myMapper->readCPU(0x06F7 + x));
        myMapper->writeCPU(0x06FB + x, myMapper->readCPU(0x06FF + x));
        y = myMapper->readCPU(0x0703 + x);
        a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
        flgC = false;
        opADC(myMapper->readCPU(0x075F + x));
        opADC(myMapper->readCPU(0x0707 + x));
        y = myMapper->readCPU(0x06D6);
        opASL_A(1);
        opPHA();
        a = 0x00;
        myMapper->writeCPU(0x4001 + y, a);
        opPLA();
        x = a;
        myMapper->writeCPU(0x4002 + y, myMapper->readCPU(0x860F + x));
        myMapper->writeCPU(0x4003 + y, myMapper->readCPU(0x8610 + x));
        x = myMapper->readCPU(0x06D5);
        opINC(0x0703 + x, 1);
        a = myMapper->readCPU(0x0703 + x);
        if (a != myMapper->readCPU(0x077B + x)) {
            goto L_0105AD;
        }
        a = 0x00;
        myMapper->writeCPU(0x0703 + x, a);
    }
L_0105AD:
    popAddress();
}

void game::SUB_0105BB() {
    a = 0x00;
    myMapper->writeCPU(0x06E8, a);
    myMapper->writeCPU(0x06E9, a);
    myMapper->writeCPU(0x06EA, a);
    myMapper->writeCPU(0x06EB, a);
    popAddress();
}

void game::SUB_0105CA() {
    myMapper->writeCPU(0x0674 + x, 0x02);
    y = myMapper->readCPU(0x06D6);
    a = 0x00;
    myMapper->writeCPU(0x4001 + y, a);
    myMapper->writeCPU(0x4000 + y, a);
    myMapper->writeCPU(0x4002 + y, a);
    myMapper->writeCPU(0x4003 + y, a);
    myMapper->writeCPU(0x00FD, a);
    popAddress();
}

void game::SUB_0105E3() {
    opINY(1);
    myMapper->writeCPU(0x0747 + x, myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = y;
    myMapper->writeCPU(0x0777 + x, a);
    jump(0x8279);
    return;
}

void game::SUB_0105F1() {
    opINY(1);
    x = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
    opINY(1);
    myMapper->writeCPU(0x4000 + x, myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = y;
    x = myMapper->readCPU(0x06D5);
    myMapper->writeCPU(0x0777 + x, a);
    jump(0x8279);
    return;
}

void game::SUB_010606() {
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0777 + x, a);
    jump(0x8279);
    return;
}

void game::SUB_015484() {
    pushAddress(0x9486);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0x9486)) return;
    pushAddress(0x9489);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0x9489)) return;
    pushAddress(0x948C);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0x948C)) return;
    a = 0x06;
    pushAddress(0x9491);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x9491)) return;
    myMapper->writeCPU(0x0005, 0x24);
    a = 0x80;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0x94A0);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0x94A0)) return;
    myMapper->writeCPU(0x0005, 0x24);
    a = 0x84;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x24;
    pushAddress(0x94AF);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0x94AF)) return;
    a = 0x18;
    pushAddress(0x94B4);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0x94B4)) return;
    a = 0x19;
    pushAddress(0x94B9);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0x94B9)) return;
    myMapper->writeCPU(0x000C, 0x24);
    a = 0x88;
    myMapper->writeCPU(0x000D, a);
    pushAddress(0x94C4);
    jump(0xDD26);
    if (handleReturnAddress(poppedEntry.value, 0x94C4)) return;
    a = myMapper->readCPU(0x0041);
    opAND(0xF9);
    myMapper->writeCPU(0x0041, a);
    pushAddress(0x94CD);
    jump(0x94D4);
    if (handleReturnAddress(poppedEntry.value, 0x94CD)) return;
    pushAddress(0x94D0);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0x94D0)) return;
    jump(0x95C5);
    return;
}

void game::SUB_0154D4() {
    myMapper->writeCPU(0x0203, 0x01);
    myMapper->writeCPU(0x0200, 0xBE);
    myMapper->writeCPU(0x0201, 0xFF);
    myMapper->writeCPU(0x0202, 0x00);
    myMapper->writeCPU(0x0587, 0x19);
    myMapper->writeCPU(0x0588, 0x19);
    x = 0x0F;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0xA0A1 + x));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0385, 0x80);
    myMapper->writeCPU(0x03C1, 0x70);
    myMapper->writeCPU(0x03FD, 0x04);
    myMapper->writeCPU(0x0475, 0x01);
    myMapper->writeCPU(0x041B, 0x07);
    myMapper->writeCPU(0x00D6, 0x01);
    myMapper->writeCPU(0x00DF, 0x0A);
    myMapper->writeCPU(0x00EC, 0x03);
    myMapper->writeCPU(0x00EB, 0x05);
    x = myMapper->readCPU(0x0051);
    a = myMapper->readCPU((0x0064 + x) & 0x00ff);
    opPHA();
    if (a == 0x3C) {
        goto L_015533;
    }
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU((0x0064 + x) & 0x00ff, a);
L_015533:
    opPLA();
    x = 0xFF;
    do {
        opINX(1);
        flgC = true;
        opSBC(0x0A);
    } while (!flgN);
    myMapper->writeCPU(0x065A, x);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x0659, a);
    myMapper->writeCPU(0x00EE, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x00ED, a);
    myMapper->writeCPU(0x00EA, a);
    myMapper->writeCPU(0x05BD, a);
    myMapper->writeCPU(0x0586, a);
    myMapper->writeCPU(0x0583, a);
    myMapper->writeCPU(0x0584, a);
    myMapper->writeCPU(0x00D0, a);
    myMapper->writeCPU(0x00D1, a);
    myMapper->writeCPU(0x00D2, a);
    myMapper->writeCPU(0x00D3, a);
    myMapper->writeCPU(0x03DF, a);
    myMapper->writeCPU(0x03A3, a);
    myMapper->writeCPU(0x00D7, a);
    myMapper->writeCPU(0x065B, a);
    myMapper->writeCPU(0x00E6, a);
    myMapper->writeCPU(0x065C, a);
    myMapper->writeCPU(0x065D, a);
    myMapper->writeCPU(0x00E8, a);
    myMapper->writeCPU(0x00E9, a);
    myMapper->writeCPU(0x058C, a);
    myMapper->writeCPU(0x00CE, a);
    myMapper->writeCPU(0x00CF, a);
    x = 0x05;
    a = 0x00;
    do {
        myMapper->writeCPU((0x00E0 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    x = 0x06;
    do {
        pushAddress(0x958E);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0x958E)) return;
        opAND(0x1F);
        myMapper->writeCPU(0x04CF + x, a);
        opDEX(1);
    } while (flgZ);
    myMapper->writeCPU(0x00E7, 0x01);
    a = 0xFF;
    myMapper->writeCPU(0x00D4, a);
    popAddress();
}

void game::SUB_0155A0() {
    x = myMapper->readCPU(0x004C);
    if (x != 0x10) {
        goto L_0155B9;
    }
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0155BA;
    }
    a = myMapper->readCPU(0x058D);
    pushAddress(0x95B0);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x95B0)) return;
    a = 0x0F;
    pushAddress(0x95B5);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x95B5)) return;
    opDEC(0x058C, 1);
L_0155B9:
    popAddress();
    return;
L_0155BA:
    opINC(0x058C, 1);
    pushAddress(0x95BF);
    jump(0xEA06);
    if (handleReturnAddress(poppedEntry.value, 0x95BF)) return;
    a = 0x0E;
    jump(0xEA1B);
    return;
}

void game::SUB_0155C5() {
    do {
        do {
            pushAddress(0x95C7);
            jump(0xDBB3);
            if (handleReturnAddress(poppedEntry.value, 0x95C7)) return;
            pushAddress(0x95CA);
            jump(0x99A8);
            if (handleReturnAddress(poppedEntry.value, 0x95CA)) return;
            pushAddress(0x95CD);
            jump(0xEA36);
            if (handleReturnAddress(poppedEntry.value, 0x95CD)) return;
            pushAddress(0x95D0);
            jump(0xDBE8);
            if (handleReturnAddress(poppedEntry.value, 0x95D0)) return;
            pushAddress(0x95D3);
            jump(0x9D96);
            if (handleReturnAddress(poppedEntry.value, 0x95D3)) return;
            pushAddress(0x95D6);
            jump(0x95A0);
            if (handleReturnAddress(poppedEntry.value, 0x95D6)) return;
            a = myMapper->readCPU(0x058C);
            setLoadFlag(a);
            if (flgZ) {
                pushAddress(0x95DE);
                jump(0x9815);
                if (handleReturnAddress(poppedEntry.value, 0x95DE)) return;
                pushAddress(0x95E1);
                jump(0x98F7);
                if (handleReturnAddress(poppedEntry.value, 0x95E1)) return;
                pushAddress(0x95E4);
                jump(0x9646);
                if (handleReturnAddress(poppedEntry.value, 0x95E4)) return;
                a = myMapper->readCPU(0x00E7);
                setLoadFlag(a);
                if (flgZ) {
                    pushAddress(0x95EB);
                    jump(0x9D0C);
                    if (handleReturnAddress(poppedEntry.value, 0x95EB)) return;
                    pushAddress(0x95EE);
                    jump(0x9A6D);
                    if (handleReturnAddress(poppedEntry.value, 0x95EE)) return;
                    pushAddress(0x95F1);
                    jump(0x9B26);
                    if (handleReturnAddress(poppedEntry.value, 0x95F1)) return;
                    pushAddress(0x95F4);
                    jump(0x9B4D);
                    if (handleReturnAddress(poppedEntry.value, 0x95F4)) return;
                    pushAddress(0x95F7);
                    jump(0x9C95);
                    if (handleReturnAddress(poppedEntry.value, 0x95F7)) return;
                }
                pushAddress(0x95FA);
                jump(0x997D);
                if (handleReturnAddress(poppedEntry.value, 0x95FA)) return;
                a = 0x04;
                pushAddress(0x95FF);
                jump(0xCA17);
                if (handleReturnAddress(poppedEntry.value, 0x95FF)) return;
                a = myMapper->readCPU(0x065C);
                setLoadFlag(a);
                if (flgZ) {
                    pushAddress(0x9607);
                    jump(0x96CD);
                    if (handleReturnAddress(poppedEntry.value, 0x9607)) return;
                }
            }
            do {
                opBIT(myMapper->readCPU(0x2002));
            } while (!flgV);
            x = 0x0E;
            do {
                opDEX(1);
            } while (!flgZ);
            a = 0x00;
            myMapper->writeCPU(0x2005, a);
            myMapper->writeCPU(0x2005, a);
            myMapper->writeCPU(0x2000, myMapper->readCPU(0x0040));
            a = myMapper->readCPU(0x003F);
            opAND(0x03);
            if (flgZ) {
                if (myMapper->readCPU(0x065D) == 0) {
                    goto L_01562D;
                }
                opDEC(0x065D, 1);
            }
        L_01562D:
            a = myMapper->readCPU(0x065D);
            setLoadFlag(a);
        } while (!flgZ);
        a = myMapper->readCPU(0x065C);
        setLoadFlag(a);
    } while (flgZ);
    if (flgN) {
        a = myMapper->readCPU(0x0660);
        setLoadFlag(a);
        if (flgZ) {
            goto L_015645;
        }
        a = myMapper->readCPU(0x0084);
        flgC = false;
        opADC(0x05);
        myMapper->writeCPU(0x0084, a);
    }
L_015645:
    popAddress();
}

void game::SUB_015646() {
    if (myMapper->readCPU(0x00E7) == 0) {
        goto L_015698;
    }
    x = 0x0A;
    do {
        myMapper->writeCPU(0x0475 + x, 0x01);
        myMapper->writeCPU(0x0385 + x, 0x10);
        a = 0x00;
        myMapper->writeCPU(0x03A3 + x, a);
        myMapper->writeCPU(0x03DF + x, a);
        myMapper->writeCPU(0x041B + x, 0x06);
        opINX(1);
    } while (x != 0x0D);
    myMapper->writeCPU(0x03CB, 0x10);
    myMapper->writeCPU(0x03CC, 0x38);
    myMapper->writeCPU(0x03CD, 0x60);
    opINC(0x00E8, 1);
    if (myMapper->readCPU(0x00E8) != 0x3C) {
        goto L_0156A7;
    }
    myMapper->writeCPU(0x00E8, 0x00);
    opINC(0x00E9, 1);
    opCMP(myMapper->readCPU(0x00E9), 0x04);
    if (!flgZ) {
        goto L_015699;
    }
    a = 0x00;
    myMapper->writeCPU(0x047F, a);
    myMapper->writeCPU(0x0480, a);
    myMapper->writeCPU(0x0481, a);
    myMapper->writeCPU(0x00E7, a);
L_015698:
    popAddress();
    return;
L_015699:
    x = 0x1B;
    if (myMapper->readCPU(0x00E9) != 0x03) {
        goto L_0156A3;
    }
    x = 0x1C;
L_0156A3:
    a = x;
    pushAddress(0x96A6);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x96A6)) return;
L_0156A7:
    a = myMapper->readCPU(0x00E9);
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x00E9));
    x = a;
    myMapper->writeCPU(0x0407, myMapper->readCPU(0x96C1 + x));
    myMapper->writeCPU(0x0408, myMapper->readCPU(0x96C2 + x));
    myMapper->writeCPU(0x0409, myMapper->readCPU(0x96C3 + x));
    popAddress();
}

void game::SUB_0156CD() {
    pushAddress(0x96CF);
    jump(0x9748);
    if (handleReturnAddress(poppedEntry.value, 0x96CF)) return;
    if (myMapper->readCPU(0x00D6) == 0) {
        a = myMapper->readCPU(0x00D4);
        if (a == 0x02) {
            opDEC(0x00D7, 1);
            a = myMapper->readCPU(0x00D7);
            opASL_A(1);
            x = a;
            myMapper->writeCPU(0x01CC, myMapper->readCPU(0x9728 + x));
            myMapper->writeCPU(0x01CB, myMapper->readCPU(0x9729 + x));
            a = 0x00;
            myMapper->writeCPU(0x01CD, a);
            myMapper->writeCPU(0x01CE, a);
            a = myMapper->readCPU(0x00D7);
            setLoadFlag(a);
            if (flgZ) {
                a = 0x01;
                myMapper->writeCPU(0x00D6, a);
                pushAddress(0x96FE);
                jump(0x97DD);
                if (handleReturnAddress(poppedEntry.value, 0x96FE)) return;
            }
        }
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x00D7) < 0x10) {
        goto L_01570B;
    }
    a = 0x00;
    myMapper->writeCPU(0x00D6, a);
    popAddress();
    return;
L_01570B:
    a = myMapper->readCPU(0x00D7);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x01CC, myMapper->readCPU(0x9728 + x));
    myMapper->writeCPU(0x01CB, myMapper->readCPU(0x9729 + x));
    myMapper->writeCPU(0x01CD, 0xC8);
    a = 0xCC;
    myMapper->writeCPU(0x01CE, a);
    opINC(0x00D7, 1);
    popAddress();
}

void game::SUB_015748() {
    a = myMapper->readCPU(0x003F);
    opAND(0x0F);
    if (flgZ) {
        opDEC(0x00EA, 1);
        if (flgN) {
            myMapper->writeCPU(0x00EA, 0x09);
            opDEC(0x00EB, 1);
            if (flgN) {
                myMapper->writeCPU(0x00EB, 0x09);
                opDEC(0x00EC, 1);
                if (flgN) {
                    a = 0x00;
                    myMapper->writeCPU(0x00EA, a);
                    myMapper->writeCPU(0x00EB, a);
                    myMapper->writeCPU(0x00EC, a);
                }
            }
        }
        a = myMapper->readCPU(0x00EA);
        opORA(myMapper->readCPU(0x00EB));
        opORA(myMapper->readCPU(0x00EC));
        if (!flgZ) {
            goto L_01577C;
        }
        myMapper->writeCPU(0x065C, 0x01);
        myMapper->writeCPU(0x065D, 0x50);
    }
L_01577C:
    popAddress();
}

void game::SUB_01577D() {
    opDEC(0x0659, 1);
    if (flgN) {
        myMapper->writeCPU(0x0659, 0x09);
        opDEC(0x065A, 1);
        if (flgN) {
            myMapper->writeCPU(0x065A, 0x09);
            opDEC(0x065B, 1);
            if (flgN) {
                a = 0x00;
                myMapper->writeCPU(0x0659, a);
                myMapper->writeCPU(0x065A, a);
                myMapper->writeCPU(0x065B, a);
            }
        }
    }
    a = myMapper->readCPU(0x0659);
    opORA(myMapper->readCPU(0x065A));
    opORA(myMapper->readCPU(0x065B));
    if (!flgZ) {
        goto L_0157B6;
    }
    myMapper->writeCPU(0x065C, 0xFF);
    myMapper->writeCPU(0x065D, 0x50);
L_0157B6:
    popAddress();
}

void game::SUB_0157B7() {
    opINC(0x065A, 1);
    if (myMapper->readCPU(0x065A) != 0x0A) {
        goto L_0157C9;
    }
    myMapper->writeCPU(0x065A, 0x00);
    opINC(0x065B, 1);
L_0157C9:
    popAddress();
}

void game::SUB_0157CA() {
    a = myMapper->readCPU(0x00EB);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x00EB, a);
    if (a < 0x0A) {
        goto L_0157DC;
    }
    flgC = true;
    opSBC(0x0A);
    myMapper->writeCPU(0x00EB, a);
    opINC(0x00EC, 1);
L_0157DC:
    popAddress();
}

void game::SUB_0157DD() {
    opDEC(0x00ED, 1);
    if (flgN) {
        a = 0x09;
        myMapper->writeCPU(0x00ED, a);
        opDEC(0x00EE, 1);
        if (!flgN) {
            goto L_0157F9;
        }
        a = 0x00;
        myMapper->writeCPU(0x00ED, a);
        myMapper->writeCPU(0x00EE, a);
        myMapper->writeCPU(0x065C, 0x01);
        a = 0x50;
        myMapper->writeCPU(0x065D, a);
    }
L_0157F9:
    popAddress();
}

void game::SUB_0157FA() {
    opINC(0x00ED, 1);
    a = myMapper->readCPU(0x00ED);
    if (a == 0x0A) {
        myMapper->writeCPU(0x00ED, 0x00);
        opINC(0x00EE, 1);
        a = myMapper->readCPU(0x00EE);
        if (a != 0x0A) {
            goto L_015814;
        }
        a = 0x09;
        myMapper->writeCPU(0x00ED, a);
        myMapper->writeCPU(0x00EE, a);
    }
L_015814:
    popAddress();
}

void game::SUB_015815() {
    if (myMapper->readCPU(0x065C) != 0) {
        goto L_015880;
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x02);
    if (!flgZ) {
        a = myMapper->readCPU(0x00D0);
        flgC = true;
        opSBC(0x64);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opSBC(0x00);
        myMapper->writeCPU(0x00D1, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x00D0);
        flgC = false;
        opADC(0x64);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opADC(0x00);
        myMapper->writeCPU(0x00D1, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x08);
    if (!flgZ) {
        a = myMapper->readCPU(0x00D2);
        flgC = true;
        opSBC(0x64);
        myMapper->writeCPU(0x00D2, a);
        a = myMapper->readCPU(0x00D3);
        opSBC(0x00);
        myMapper->writeCPU(0x00D3, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x04);
    if (!flgZ) {
        a = myMapper->readCPU(0x00D2);
        flgC = false;
        opADC(0x64);
        myMapper->writeCPU(0x00D2, a);
        a = myMapper->readCPU(0x00D3);
        opADC(0x00);
        myMapper->writeCPU(0x00D3, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0xC0);
    if (!flgZ) {
        if (!(myMapper->readCPU(0x00D4) & 0x80)) {
            goto L_015880;
        }
        if (myMapper->readCPU(0x00D6) == 0) {
            a = 0x06;
            pushAddress(0x9878);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x9878)) return;
            a = 0x03;
            myMapper->writeCPU(0x00D4, a);
            pushAddress(0x987F);
            jump(0x99C2);
            if (handleReturnAddress(poppedEntry.value, 0x987F)) return;
        }
    }
L_015880:
    if (!(myMapper->readCPU(0x00D1) & 0x80)) {
        a = myMapper->readCPU(0x00D0);
        flgC = true;
        opSBC(0x32);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opSBC(0x00);
        myMapper->writeCPU(0x00D1, a);
        if (!flgN) {
            goto L_0158B1;
        }
        a = 0x00;
        myMapper->writeCPU(0x00D0, a);
        myMapper->writeCPU(0x00D1, a);
    }
    else {
        a = myMapper->readCPU(0x00D0);
        flgC = false;
        opADC(0x32);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opADC(0x00);
        myMapper->writeCPU(0x00D1, a);
        if (!flgN) {
            a = 0x00;
            myMapper->writeCPU(0x00D0, a);
            myMapper->writeCPU(0x00D1, a);
        }
    }
L_0158B1:
    if (!(myMapper->readCPU(0x00D3) & 0x80)) {
        a = myMapper->readCPU(0x00D2);
        flgC = true;
        opSBC(0x32);
        myMapper->writeCPU(0x00D2, a);
        a = myMapper->readCPU(0x00D3);
        opSBC(0x00);
        myMapper->writeCPU(0x00D3, a);
        if (!flgN) {
            goto L_0158E2;
        }
        a = 0x00;
        myMapper->writeCPU(0x00D2, a);
        myMapper->writeCPU(0x00D3, a);
    }
    else {
        a = myMapper->readCPU(0x00D2);
        flgC = false;
        opADC(0x32);
        myMapper->writeCPU(0x00D2, a);
        a = myMapper->readCPU(0x00D3);
        opADC(0x00);
        myMapper->writeCPU(0x00D3, a);
        if (!flgN) {
            a = 0x00;
            myMapper->writeCPU(0x00D2, a);
            myMapper->writeCPU(0x00D3, a);
        }
    }
L_0158E2:
    x = myMapper->readCPU(0x00D4);
    setLoadFlag(x);
    if (flgN) {
        goto L_0158F2;
    }
    a = myMapper->readCPU(0x98F3 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1));
    myMapper->writeCPU(0x03C1, a);
    opDEC(0x00D4, 1);
L_0158F2:
    popAddress();
}

void game::SUB_0158F7() {
    x = 0x00;
    if (myMapper->readCPU(0x00D1) & 0x80) {
        x = 0xFF;
    }
    myMapper->writeCPU(0x0001, x);
    a = myMapper->readCPU(0x0385);
    flgC = false;
    opADC(myMapper->readCPU(0x00D1));
    myMapper->writeCPU(0x0385, a);
    a = myMapper->readCPU(0x03A3);
    opADC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x03A3, a);
    if (!flgN) {
        if (!flgZ) {
            goto L_015930;
        }
        if (myMapper->readCPU(0x0385) >= 0x08) {
            goto L_015930;
        }
    }
    myMapper->writeCPU(0x0385, 0x08);
    myMapper->writeCPU(0x03A3, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x00D0, a);
    myMapper->writeCPU(0x00D1, a);
    goto L_015952;
L_015930:
    a = myMapper->readCPU(0x03A3);
    if (a != 0x00) {
        if (a == 0x02) {
            goto L_015942;
        }
        if (myMapper->readCPU(0x0385) < 0xE8) {
            goto L_015952;
        }
    L_015942:
        myMapper->writeCPU(0x0385, 0xE8);
        myMapper->writeCPU(0x03A3, 0x01);
        a = 0x00;
        myMapper->writeCPU(0x00D0, a);
        myMapper->writeCPU(0x00D1, a);
    }
L_015952:
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(myMapper->readCPU(0x00D3));
    myMapper->writeCPU(0x03C1, a);
    opCMP(a, 0x10);
    if (!flgC) {
        myMapper->writeCPU(0x03C1, 0x10);
        a = 0x00;
        myMapper->writeCPU(0x00D2, a);
        myMapper->writeCPU(0x00D3, a);
    }
    else {
        opCMP(a, 0xA8);
        if (!flgC) {
            goto L_01597C;
        }
        myMapper->writeCPU(0x03C1, 0xA8);
        a = 0x00;
        myMapper->writeCPU(0x00D2, a);
        myMapper->writeCPU(0x00D3, a);
    }
L_01597C:
    popAddress();
}

void game::SUB_01597D() {
    a = myMapper->readCPU(0x0385);
    flgC = true;
    opSBC(0x7F);
    myMapper->writeCPU(0x0583, a);
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    myMapper->writeCPU(0x0584, a);
    if (flgN) {
        a = 0x00;
        myMapper->writeCPU(0x0583, a);
        myMapper->writeCPU(0x0584, a);
    }
    if (myMapper->readCPU(0x0584) == 0) {
        goto L_0159A7;
    }
    myMapper->writeCPU(0x0584, 0x01);
    myMapper->writeCPU(0x0583, 0x00);
L_0159A7:
    popAddress();
}

void game::SUB_0159A8() {
    myMapper->writeCPU(0x2005, myMapper->readCPU(0x0583));
    myMapper->writeCPU(0x2005, 0x00);
    a = myMapper->readCPU(0x0040);
    x = myMapper->readCPU(0x0584);
    setLoadFlag(x);
    if (flgZ) {
        goto L_0159BE;
    }
    opAND(0xFE);
    opORA(0x01);
L_0159BE:
    myMapper->writeCPU(0x2000, a);
    popAddress();
}

void game::SUB_0159C2() {
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(0x0C);
    opLSR_A(3);
    x = a;
    y = 0x20;
    pushAddress(0x99D0);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0x99D0)) return;
    myMapper->writeCPU(0x05AD, x);
    myMapper->writeCPU(0x05AE, y);
    a = myMapper->readCPU(0x0385);
    flgC = false;
    opADC(0x0C);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x03A3);
    opADC(0x00);
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0x0001);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x05AD));
    myMapper->writeCPU(0x05AD, a);
    a = myMapper->readCPU(0x05AE);
    opADC(0x00);
    myMapper->writeCPU(0x05AE, a);
    if (myMapper->readCPU(0x0002) == 0) {
        a = myMapper->readCPU(0x05AD);
        flgC = false;
        opADC(0x24);
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x05AE);
        opADC(0x80);
        myMapper->writeCPU(0x0006, a);
    }
    else {
        a = myMapper->readCPU(0x05AD);
        flgC = false;
        opADC(0x24);
        myMapper->writeCPU(0x0005, a);
        a = myMapper->readCPU(0x05AE);
        opADC(0x84);
        myMapper->writeCPU(0x0006, a);
    }
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    y = 0x00;
    while (true) {
        x = myMapper->readCPU(0x9A35 + y);
        setLoadFlag(x);
        if (flgZ) {
            goto L_015A6C;
        }
        if (a == myMapper->readCPU(0x9A34 + y)) {
            goto L_015A40;
        }
        opINY(2);
    }
L_015A40:
    if (myMapper->readCPU(0x0002) != 0) {
        goto L_015A58;
    }
    a = myMapper->readCPU(0x05AD);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x01C9, a);
    a = myMapper->readCPU(0x05AE);
    opADC(0x20);
    myMapper->writeCPU(0x01C8, a);
    goto L_015A69;
L_015A58:
    a = myMapper->readCPU(0x05AD);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x01C9, a);
    a = myMapper->readCPU(0x05AE);
    opADC(0x24);
    myMapper->writeCPU(0x01C8, a);
L_015A69:
    myMapper->writeCPU(0x01CA, x);
L_015A6C:
    popAddress();
}

void game::SUB_015A6D() {
    x = 0x06;
    while (true) {
        a = myMapper->readCPU(0x0475 + x);
        setLoadFlag(a);
        if (!flgZ) {
        }
        else {
            a = myMapper->readCPU(0x04CF + x);
            setLoadFlag(a);
            if (!flgZ) {
                opDEC(0x04CF + x, 1);
            }
            else {
                opINC(0x00E6, 1);
                a = myMapper->readCPU(0x00E6);
                if (a == 0x06) {
                    a = 0x00;
                    myMapper->writeCPU(0x00E6, a);
                }
                y = a;
                a = myMapper->readCPU(0x00E0 + y);
                if (a == 0x01) {
                    goto L_015B08;
                }
                a = myMapper->readCPU(0x00E0 + y);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x00E0 + y, a);
                a = y;
                myMapper->writeCPU(0x0547 + x, a);
                opASL_A(3);
                myMapper->writeCPU(0x0001, a);
                pushAddress(0x9AAA);
                jump(0xDCD8);
                if (handleReturnAddress(poppedEntry.value, 0x9AAA)) return;
                opAND(0x07);
                flgC = false;
                opADC(myMapper->readCPU(0x0001));
                y = a;
                myMapper->writeCPU(0x0001, 0x00);
                a = myMapper->readCPU(0x9F17 + y);
                opASL_A(1);
                opROL_M(0x0001, 1);
                opASL_A(1);
                opROL_M(0x0001, 1);
                myMapper->writeCPU(0x0385 + x, a);
                myMapper->writeCPU(0x03A3 + x, myMapper->readCPU(0x0001));
                if (myMapper->readCPU(0x0660) != 0) {
                    goto L_015B0F;
                }
                a = myMapper->readCPU(0x9F47 + y);
                opASL_A(3);
                myMapper->writeCPU(0x03C1 + x, a);
                myMapper->writeCPU(0x03DF + x, 0x00);
                a = myMapper->readCPU(0x9FB5 + y);
                y = a;
                myMapper->writeCPU(0x04ED + x, a);
            L_015AE0:
                a = myMapper->readCPU(0xA001 + y);
                opASL_A(3);
                myMapper->writeCPU(0x050B + x, a);
                a = myMapper->readCPU(0xA00F + y);
                opASL_A(3);
                myMapper->writeCPU(0x0529 + x, a);
                myMapper->writeCPU(0x041B + x, myMapper->readCPU(0xA01D + y));
                myMapper->writeCPU(0x04CF + x, 0x06);
                myMapper->writeCPU(0x03FD + x, myMapper->readCPU(0x9FF3 + y));
                a = 0x01;
                myMapper->writeCPU(0x0475 + x, a);
            }
        }
    L_015B08:
        opDEX(1);
        if (flgZ) {
            goto L_015B0E;
        }
    }
L_015B0E:
    popAddress();
    return;
L_015B0F:
    a = myMapper->readCPU(0x9F77 + y);
    opASL_A(3);
    myMapper->writeCPU(0x03C1 + x, a);
    myMapper->writeCPU(0x03DF + x, 0x00);
    a = 0x00;
    y = a;
    myMapper->writeCPU(0x04ED + x, a);
    goto L_015AE0;
}

void game::SUB_015B26() {
    a = myMapper->readCPU(0x003F);
    opAND(0x3F);
    if (!flgZ) {
        goto L_015B4C;
    }
    x = 0x06;
    do {
        a = myMapper->readCPU(0x0475 + x);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x04CF + x, 1);
            if (!flgZ) {
                goto L_015B49;
            }
            myMapper->writeCPU(0x0475 + x, 0x00);
            y = myMapper->readCPU(0x0547 + x);
            a = myMapper->readCPU(0x00E0 + y);
            flgC = true;
            opSBC(0x01);
            myMapper->writeCPU(0x00E0 + y, a);
        }
    L_015B49:
        opDEX(1);
    } while (!flgZ);
L_015B4C:
    popAddress();
}

void game::SUB_015B4D() {
    myMapper->writeCPU(0x03FD, 0x04);
    x = 0x09;
    do {
        a = myMapper->readCPU(0x0475 + x);
        setLoadFlag(a);
        if (!flgZ) {
            a = myMapper->readCPU(0x0457 + x);
            setLoadFlag(a);
            if (flgZ) {
                a = myMapper->readCPU(0x0439);
                flgC = false;
                opADC(0x0C);
                flgC = true;
                opSBC(myMapper->readCPU(0x0439 + x));
                if (flgC) {
                    if (a >= myMapper->readCPU(0x050B + x)) {
                        goto L_015B83;
                    }
                    a = myMapper->readCPU(0x03C1);
                    flgC = false;
                    opADC(0x0C);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x03C1 + x));
                    if (flgC) {
                        if (a >= myMapper->readCPU(0x0529 + x)) {
                            goto L_015B83;
                        }
                        goto L_015BAB;
                    }
                }
            }
        }
    L_015B83:
        opDEX(1);
    } while (!flgZ);
    do {
        do {
            popAddress();
            return;
        L_015B87:
            a = myMapper->readCPU(0x04CF + x);
            setLoadFlag(a);
        } while (!flgZ);
        myMapper->writeCPU(0x04CF + x, 0x01);
        a = myMapper->readCPU(0x03FD + x);
        if (a == 0x05) {
            goto L_015BA3;
        }
        pushAddress(0x9B9A);
        jump(0x97FA);
        if (handleReturnAddress(poppedEntry.value, 0x9B9A)) return;
        pushAddress(0x9B9D);
        jump(0x97FA);
        if (handleReturnAddress(poppedEntry.value, 0x9B9D)) return;
        a = 0x12;
        jump(0xEA1B);
        return;
    L_015BA3:
        pushAddress(0x9C97);
        jump(0x97CA);
        if (handleReturnAddress(poppedEntry.value, 0x9C97)) return;
        a = 0x12;
        jump(0xEA1B);
        return;
    L_015BAB:
        myMapper->writeCPU(0x03FD, 0x03);
        a = myMapper->readCPU(0x00D4);
    } while (a != 0x02);
    if (x == 0x09) {
        goto L_015B87;
    }
    y = myMapper->readCPU(0x0547 + x);
    a = myMapper->readCPU(0x00E0 + y);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x00E0 + y, a);
    y = myMapper->readCPU(0x04ED + x);
    a = myMapper->readCPU(0x9FE5 + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_015BD9;
    }
    pushAddress(0x9BD0);
    jump(0x97B7);
    if (handleReturnAddress(poppedEntry.value, 0x9BD0)) return;
    a = 0x1F;
    pushAddress(0x9BD5);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9BD5)) return;
    goto L_015BDC;
L_015BD9:
    pushAddress(0x9BA5);
    jump(0x977D);
    if (handleReturnAddress(poppedEntry.value, 0x9BA5)) return;
L_015BDC:
    a = 0x0D;
    pushAddress(0x9BE0);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9BE0)) return;
    myMapper->writeCPU(0x0475 + x, 0x00);
    myMapper->writeCPU(0x04CF + x, 0x78);
    a = myMapper->readCPU(0x0385 + x);
    myMapper->writeCPU(0x00DB, a);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x03A3 + x);
    myMapper->writeCPU(0x00DC, a);
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x00DD, myMapper->readCPU(0x03C1 + x));
    y = myMapper->readCPU(0x04ED + x);
    a = myMapper->readCPU(0xA001 + y);
    myMapper->writeCPU(0x00D9, a);
    myMapper->writeCPU(0x00DE, a);
    myMapper->writeCPU(0x00DA, myMapper->readCPU(0xA00F + y));
    a = y;
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xA02B + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0xA02C + y));
    myMapper->writeCPU(0x00D8, 0x00);
    while (true) {
        do {
            x = myMapper->readCPU(0x00DF);
            myMapper->writeCPU(0x0385 + x, myMapper->readCPU(0x00DB));
            myMapper->writeCPU(0x03A3 + x, myMapper->readCPU(0x00DC));
            myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(0x00DD));
            myMapper->writeCPU(0x03DF + x, 0x00);
            y = myMapper->readCPU(0x00D8);
            myMapper->writeCPU(0x0493 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x04B1 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
            opINY(1);
            myMapper->writeCPU(0x00D8, y);
            a = 0x00;
            myMapper->writeCPU(0x03FD + x, a);
            myMapper->writeCPU(0x041B + x, a);
            a = 0x01;
            myMapper->writeCPU(0x0475 + x, a);
            pushAddress(0x9C53);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0x9C53)) return;
            opAND(0x03);
            y = a;
            myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0xEFAF + y));
            opINC(0x00DF, 1);
            if (myMapper->readCPU(0x00DF) != 0x1A) {
                goto L_015C69;
            }
            myMapper->writeCPU(0x00DF, 0x0A);
        L_015C69:
            a = myMapper->readCPU(0x00DB);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x00DB, a);
            a = myMapper->readCPU(0x00DC);
            opADC(0x00);
            myMapper->writeCPU(0x00DC, a);
            opDEC(0x00D9, 1);
        } while (!flgZ);
        myMapper->writeCPU(0x00D9, myMapper->readCPU(0x00DE));
        myMapper->writeCPU(0x00DB, myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x00DC, myMapper->readCPU(0x0002));
        a = myMapper->readCPU(0x00DD);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x00DD, a);
        opDEC(0x00DA, 1);
        if (flgZ) {
            goto L_015C94;
        }
    }
L_015C94:
    popAddress();
}

void game::SUB_015C95() {
    x = 0x0A;
    do {
        a = myMapper->readCPU(0x0475 + x);
        setLoadFlag(a);
        if (!flgZ) {
            y = 0x00;
            if (myMapper->readCPU(0x0493 + x) & 0x80) {
                y = 0xFF;
            }
            myMapper->writeCPU(0x0001, y);
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x0493 + x));
            myMapper->writeCPU(0x0385 + x, a);
            a = myMapper->readCPU(0x03A3 + x);
            opADC(myMapper->readCPU(0x0001));
            myMapper->writeCPU(0x03A3 + x, a);
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x04B1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (a >= 0xC0) {
                myMapper->writeCPU(0x0475 + x, 0x00);
            }
            a = myMapper->readCPU(0x003F);
            opAND(0x01);
            if (flgZ) {
                opINC(0x04B1 + x, 1);
                a = myMapper->readCPU(0x003F);
                opAND(0x03);
                if (flgZ) {
                    a = myMapper->readCPU(0x0493 + x);
                    setLoadFlag(a);
                    if (!flgZ) {
                        if (!flgN) {
                            goto L_015CE8;
                        }
                        opINC(0x0493 + x, 1);
                        goto L_015CEB;
                    L_015CE8:
                        opDEC(0x0493 + x, 1);
                    }
                }
            }
        L_015CEB:
            a = myMapper->readCPU(0x003F);
            opAND(0x07);
            if (flgZ) {
                opINC(0x00E8, 1);
                if (myMapper->readCPU(0x00E8) < 0x06) {
                    goto L_015CFD;
                }
                myMapper->writeCPU(0x00E8, 0xFF);
            }
        L_015CFD:
            a = myMapper->readCPU(0x00E8);
            flgC = false;
            opADC(myMapper->readCPU(0x0565 + x));
            myMapper->writeCPU(0x03FD + x, a);
        }
        opINX(1);
    } while (x != 0x1A);
    popAddress();
}

void game::SUB_015D0C() {
    if (myMapper->readCPU(0x047E) != 0) {
        goto L_015D70;
    }
    a = myMapper->readCPU(0x003F);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_015D84;
    }
    opINC(0x00CF, 1);
    a = myMapper->readCPU(0x00CF);
    opAND(0x03);
    if (!flgZ) {
        goto L_015D84;
    }
    a = myMapper->readCPU(0x00CE);
    opEOR(0x01);
    opAND(0x01);
    myMapper->writeCPU(0x00CE, a);
    if (!flgZ) {
        myMapper->writeCPU(0x0424, 0x07);
        myMapper->writeCPU(0x0406, 0x05);
        a = 0x18;
        myMapper->writeCPU(0x0514, a);
        myMapper->writeCPU(0x0532, a);
    }
    else {
        myMapper->writeCPU(0x0424, 0x07);
        myMapper->writeCPU(0x0406, 0x06);
        myMapper->writeCPU(0x0514, 0x10);
        a = 0x18;
        myMapper->writeCPU(0x0532, a);
    }
    pushAddress(0x9D52);
    jump(0xDCD8);
    if (handleReturnAddress(poppedEntry.value, 0x9D52)) return;
    myMapper->writeCPU(0x038E, a);
    pushAddress(0x9D58);
    jump(0xDCD8);
    if (handleReturnAddress(poppedEntry.value, 0x9D58)) return;
    opAND(0x01);
    myMapper->writeCPU(0x03AC, a);
    a = 0x00;
    myMapper->writeCPU(0x03CA, a);
    myMapper->writeCPU(0x03E8, a);
    myMapper->writeCPU(0x047E, 0x01);
    myMapper->writeCPU(0x04D8, 0x00);
L_015D70:
    if (myMapper->readCPU(0x04D8) != 0) {
        goto L_015D85;
    }
    opINC(0x03CA, 1);
    a = myMapper->readCPU(0x03CA);
    if (a < 0xA8) {
        goto L_015D84;
    }
    a = 0x00;
    myMapper->writeCPU(0x047E, a);
    do {
    L_015D84:
        popAddress();
        return;
    L_015D85:
        a = myMapper->readCPU(0x03CA);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x03CA, a);
    } while (flgC);
    a = 0x00;
    myMapper->writeCPU(0x047E, a);
    popAddress();
}

void game::SUB_015D96() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (!flgZ) {
        if (a == 0x01) {
            goto L_015E06;
        }
        if (a == 0x02) {
            goto L_015DAF;
        }
        myMapper->writeCPU(0x000C, 0x24);
        a = 0x88;
        myMapper->writeCPU(0x000D, a);
        jump(0xE0BC);
        return;
    L_015DAF:
        myMapper->writeCPU(0x0024, 0x18);
        myMapper->writeCPU(0x0025, 0x23);
        myMapper->writeCPU(0x0000, 0x0A);
        a = myMapper->readCPU(0x00EC);
        myMapper->writeCPU(0x0001, a);
        x = 0x92;
        pushAddress(0x9DC3);
        jump(0x9E1C);
        if (handleReturnAddress(poppedEntry.value, 0x9DC3)) return;
        myMapper->writeCPU(0x0024, 0x1C);
        myMapper->writeCPU(0x0025, 0x23);
        myMapper->writeCPU(0x0000, myMapper->readCPU(0x00EB));
        a = myMapper->readCPU(0x00EA);
        myMapper->writeCPU(0x0001, a);
        x = 0xAD;
        jump(0x9E1C);
        return;
    }
    myMapper->writeCPU(0x0024, 0x01);
    myMapper->writeCPU(0x0025, 0x23);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x065B));
    a = 0x0A;
    myMapper->writeCPU(0x0001, a);
    x = 0x31;
    pushAddress(0x9DEE);
    jump(0x9E1C);
    if (handleReturnAddress(poppedEntry.value, 0x9DEE)) return;
    myMapper->writeCPU(0x0024, 0x03);
    myMapper->writeCPU(0x0025, 0x23);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x065A));
    a = myMapper->readCPU(0x0659);
    myMapper->writeCPU(0x0001, a);
    x = 0x4C;
    jump(0x9E1C);
    return;
L_015E06:
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x00EE));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x00ED));
    myMapper->writeCPU(0x0024, 0x0C);
    a = 0x23;
    myMapper->writeCPU(0x0025, a);
    x = 0x31;
    jump(0x9E1C);
    return;
}

void game::SUB_015E1C() {
    a = myMapper->readCPU(0x0000);
    opASL_A(3);
    flgC = false;
    opADC(0xB9);
    myMapper->writeCPU(0x0005, a);
    a = 0x00;
    opADC(0x9E);
    myMapper->writeCPU(0x0006, a);
    a = myMapper->readCPU(0x0001);
    opASL_A(3);
    flgC = false;
    opADC(0xB9);
    myMapper->writeCPU(0x0007, a);
    a = 0x00;
    opADC(0x9E);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0025);
    myMapper->writeCPU(0x0100 + x, a);
    myMapper->writeCPU(0x0106 + x, a);
    myMapper->writeCPU(0x010C + x, a);
    myMapper->writeCPU(0x0112 + x, a);
    flgC = false;
    a = myMapper->readCPU(0x0024);
    myMapper->writeCPU(0x0101 + x, a);
    opADC(0x20);
    myMapper->writeCPU(0x0107 + x, a);
    opADC(0x20);
    myMapper->writeCPU(0x010D + x, a);
    opADC(0x20);
    myMapper->writeCPU(0x0113 + x, a);
    y = 0x00;
    myMapper->writeCPU(0x0102 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0104 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0103 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0105 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0108 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x010A + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0109 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x010B + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x010E + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0110 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x010F + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0111 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0114 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0116 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0115 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0117 + x, a);
    popAddress();
}

void game::SUB_018000() {
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    if (a != 0x16) {
        if (a == 0x17) {
            goto L_01800E;
        }
        popAddress();
        return;
    }
L_01800E:
    jump(0xBAFC);
    return;
}

void game::SUB_019CF1() {
    myMapper->writeCPU(0x0004, a);
    pushAddress(0x9CF5);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0x9CF5)) return;
    pushAddress(0x9CF8);
    jump(0xEA06);
    if (handleReturnAddress(poppedEntry.value, 0x9CF8)) return;
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x88;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0x9D07);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0x9D07)) return;
    a = 0x1C;
    pushAddress(0x9D0C);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0x9D0C)) return;
    a = 0x1D;
    pushAddress(0x9D11);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0x9D11)) return;
    pushAddress(0x9D14);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0x9D14)) return;
    pushAddress(0x9D17);
    jump(0x9D50);
    if (handleReturnAddress(poppedEntry.value, 0x9D17)) return;
    pushAddress(0x9D1A);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0x9D1A)) return;
    pushAddress(0x9D1D);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0x9D1D)) return;
    myMapper->writeCPU(0x0005, 0x51);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0x9D2A);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0x9D2A)) return;
    a = 0x00;
    myMapper->writeCPU(0x05AC, a);
    x = 0x3C;
    pushAddress(0x9D34);
    jump(0x9D79);
    if (handleReturnAddress(poppedEntry.value, 0x9D34)) return;
    pushAddress(0x9D37);
    jump(0x9D59);
    if (handleReturnAddress(poppedEntry.value, 0x9D37)) return;
    pushAddress(0x9D3A);
    jump(0xA073);
    if (handleReturnAddress(poppedEntry.value, 0x9D3A)) return;
    pushAddress(0x9D3D);
    jump(0x9EF3);
    if (handleReturnAddress(poppedEntry.value, 0x9D3D)) return;
    x = 0x00;
    pushAddress(0x9D42);
    jump(0x9D98);
    if (handleReturnAddress(poppedEntry.value, 0x9D42)) return;
    myMapper->writeCPU(0x0005, 0x51);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_019D50() {
    a = 0x00;
    myMapper->writeCPU(0x0533, a);
    myMapper->writeCPU(0x0534, a);
    popAddress();
}

void game::SUB_019D59() {
    a = 0x03;
    pushAddress(0x9D5D);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9D5D)) return;
    a = 0x00;
    myMapper->writeCPU(0x0535, a);
    do {
        x = 0x03;
        pushAddress(0x9D67);
        jump(0x9D79);
        if (handleReturnAddress(poppedEntry.value, 0x9D67)) return;
        a = myMapper->readCPU(0x0535);
        pushAddress(0x9D6D);
        jump(0x9F13);
        if (handleReturnAddress(poppedEntry.value, 0x9D6D)) return;
        opINC(0x0535, 1);
        a = myMapper->readCPU(0x0535);
    } while (a != 0x04);
    popAddress();
}

void game::SUB_019D79() {
    myMapper->writeCPU(0x0003, x);
    do {
        a = myMapper->readCPU(0x05AC);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_019D93;
        }
        pushAddress(0x9D82);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0x9D82)) return;
        pushAddress(0x9D85);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0x9D85)) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x10);
        if (!flgZ) {
            goto L_019D94;
        }
        pushAddress(0x9D8E);
        jump(0x9DBA);
        if (handleReturnAddress(poppedEntry.value, 0x9D8E)) return;
        opDEC(0x0003, 1);
    } while (!flgZ);
L_019D93:
    popAddress();
    return;
L_019D94:
    myMapper->writeCPU(0x05AC, a);
    popAddress();
}

void game::SUB_019D98() {
    myMapper->writeCPU(0x0003, x);
    do {
        a = myMapper->readCPU(0x05AC);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_019DB5;
        }
        pushAddress(0x9DA1);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0x9DA1)) return;
        pushAddress(0x9DA4);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0x9DA4)) return;
        pushAddress(0x9DA7);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0x9DA7)) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x10);
        if (!flgZ) {
            goto L_019DB6;
        }
        pushAddress(0x9DB0);
        jump(0x9DBA);
        if (handleReturnAddress(poppedEntry.value, 0x9DB0)) return;
        opDEC(0x0003, 1);
    } while (!flgZ);
L_019DB5:
    popAddress();
    return;
L_019DB6:
    myMapper->writeCPU(0x05AC, a);
    popAddress();
}

void game::SUB_019DBA() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        opDEC(0x0533, 1);
        if (flgN) {
            a = 0x07;
            myMapper->writeCPU(0x0533, a);
            pushAddress(0x9DD1);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0x9DD1)) return;
            opAND(0x03);
            opASL_A(1);
            x = a;
            myMapper->writeCPU(0x038F, myMapper->readCPU(0x9E9B + x));
            myMapper->writeCPU(0x03CB, myMapper->readCPU(0x9E9C + x));
        }
        opDEC(0x0534, 1);
        if (!flgN) {
            goto L_019DFF;
        }
        a = 0x07;
        myMapper->writeCPU(0x0534, a);
        pushAddress(0x9DEE);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0x9DEE)) return;
        opAND(0x03);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x0390, myMapper->readCPU(0x9E9B + x));
        myMapper->writeCPU(0x03CC, myMapper->readCPU(0x9E9C + x));
    L_019DFF:
        myMapper->writeCPU(0x047F, 0x80);
        x = myMapper->readCPU(0x0533);
        a = myMapper->readCPU(0x9E93 + x);
        x = myMapper->readCPU(0x038F);
        y = myMapper->readCPU(0x03CB);
        pushAddress(0x9E12);
        jump(0x9E2D);
        if (handleReturnAddress(poppedEntry.value, 0x9E12)) return;
        myMapper->writeCPU(0x047F, 0xC0);
        x = myMapper->readCPU(0x0534);
        a = myMapper->readCPU(0x9E93 + x);
        x = myMapper->readCPU(0x0390);
        y = myMapper->readCPU(0x03CC);
        pushAddress(0x9E26);
        jump(0x9E2D);
        if (handleReturnAddress(poppedEntry.value, 0x9E26)) return;
    }
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    popAddress();
}

void game::SUB_019E2D() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0001, x);
    myMapper->writeCPU(0x03CD, y);
    opASL_A(4);
    x = a;
    y = myMapper->readCPU(0x047F);
    a = 0x00;
    myMapper->writeCPU(0x0481, a);
    myMapper->writeCPU(0x0480, a);
    do {
        myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0x9EA3 + x));
        myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
        myMapper->writeCPU(0x0202 + y, 0x00);
        a = y;
        flgC = false;
        opADC(0x04);
        y = a;
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opINC(0x0480, 1);
        if (myMapper->readCPU(0x0480) != 0x04) {
            goto L_019E87;
        }
        myMapper->writeCPU(0x0480, 0x00);
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0001));
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_019E87:
        opINX(1);
        opINC(0x0481, 1);
        a = myMapper->readCPU(0x0481);
    } while (a != 0x10);
    popAddress();
}

void game::SUB_019EF3() {
    a = 0x03;
    pushAddress(0x9EF7);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9EF7)) return;
    a = 0x03;
    myMapper->writeCPU(0x0535, a);
    do {
        x = 0x03;
        pushAddress(0x9F01);
        jump(0x9D79);
        if (handleReturnAddress(poppedEntry.value, 0x9F01)) return;
        a = myMapper->readCPU(0x0535);
        pushAddress(0x9F07);
        jump(0x9F13);
        if (handleReturnAddress(poppedEntry.value, 0x9F07)) return;
        opDEC(0x0535, 1);
        a = myMapper->readCPU(0x0535);
        setLoadFlag(a);
    } while (!flgN);
    jump(0xCA04);
    return;
}

void game::SUB_019F13() {
    opPHA();
    pushAddress(0x9F16);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0x9F16)) return;
    opPLA();
    opASL_A(6);
    x = a;
    myMapper->writeCPU(0x0391, 0x30);
    myMapper->writeCPU(0x03CD, 0x88);
    y = 0x00;
    myMapper->writeCPU(0x0481, y);
    do {
        a = myMapper->readCPU(0x9F73 + x);
        setLoadFlag(a);
        if (!flgZ) {
            myMapper->writeCPU(0x0201 + y, a);
            myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
            myMapper->writeCPU(0x0202 + y, 0x00);
            a = y;
            flgC = false;
            opADC(0x04);
            y = a;
        }
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        if (a != 0x70) {
            goto L_019F67;
        }
        myMapper->writeCPU(0x0391, 0x30);
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_019F67:
        opINX(1);
        opINC(0x0481, 1);
    } while (myMapper->readCPU(0x0481) != 0x40);
    popAddress();
}

void game::SUB_01A073() {
    a = myMapper->readCPU(0x0004);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xA139 + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0xA13A + y));
    myMapper->writeCPU(0x0385, 0x0F);
    myMapper->writeCPU(0x03C1, 0x04);
    myMapper->writeCPU(0x0475, 0x00);
    while (true) {
        while (true) {
            while (true) {
                a = myMapper->readCPU(0x05AC);
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_01A0FD;
                }
                pushAddress(0xA097);
                jump(0xDBE8);
                if (handleReturnAddress(poppedEntry.value, 0xA097)) return;
                a = myMapper->readCPU(0x004C);
                opAND(0x10);
                if (!flgZ) {
                    goto L_01A0FD;
                }
                x = 0x01;
                pushAddress(0xA0A2);
                jump(0x9D79);
                if (handleReturnAddress(poppedEntry.value, 0xA0A2)) return;
                y = myMapper->readCPU(0x0475);
                a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
                setLoadFlag(a);
                if (flgN) {
                    goto L_01A0FD;
                }
                if (a != 0x0D) {
                    goto L_01A0BC;
                }
                a = 0x0F;
                myMapper->writeCPU(0x0385, a);
                opINC(0x03C1, 1);
                opINC(0x0475, 1);
            }
        L_01A0BC:
            if (a >= 0x30) {
                if (a >= 0x39) {
                    goto L_01A0CA;
                }
                flgC = true;
                opSBC(0x2A);
                goto L_01A101;
            }
        L_01A0CA:
            if (a == 0x23) {
                a = 0xFF;
                goto L_01A101;
            }
            if (a == 0x20) {
                a = 0x00;
                goto L_01A101;
            }
            if (a == 0x3A) {
                a = 0xFD;
                goto L_01A101;
            }
            if (a != 0x2E) {
                goto L_01A0EE;
            }
            a = 0xFE;
            goto L_01A101;
        L_01A0EE:
            if (a != 0x01) {
                goto L_01A0FE;
            }
            x = 0x4B;
            pushAddress(0xA0F6);
            jump(0x9D79);
            if (handleReturnAddress(poppedEntry.value, 0xA0F6)) return;
            opINC(0x0475, 1);
        }
    L_01A0FD:
        popAddress();
        return;
    L_01A0FE:
        flgC = true;
        opSBC(0x7E);
    L_01A101:
        myMapper->writeCPU(0x01CA, a);
        x = myMapper->readCPU(0x03C1);
        y = 0x20;
        pushAddress(0xA10B);
        jump(0xDCB2);
        if (handleReturnAddress(poppedEntry.value, 0xA10B)) return;
        a = x;
        flgC = false;
        opADC(myMapper->readCPU(0x0385));
        myMapper->writeCPU(0x05AD, a);
        a = y;
        opADC(0x00);
        myMapper->writeCPU(0x05AE, a);
        flgC = false;
        a = myMapper->readCPU(0x05AD);
        opADC(0x00);
        myMapper->writeCPU(0x01C9, a);
        a = myMapper->readCPU(0x05AE);
        opADC(0x20);
        myMapper->writeCPU(0x01C8, a);
        opINC(0x0475, 1);
        opINC(0x0385, 1);
        a = 0x04;
        pushAddress(0xA135);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xA135)) return;
    }
    SUB_01AE8E();
    return;
}

void game::SUB_01AE8E() {
    pushAddress(0xAE90);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xAE90)) return;
    x = myMapper->readCPU(0x0051);
    y = 0x00;
    do {
        a = myMapper->readCPU((0x005A + x) & 0x00ff);
        myMapper->writeCPU(0x00AA + y, a);
        opINX(1);
        opINY(1);
    } while (y != 0x08);
    pushAddress(0xAEA2);
    jump(0xAF22);
    if (handleReturnAddress(poppedEntry.value, 0xAEA2)) return;
    a = myMapper->readCPU(0x0386);
    if (a != 0x08) {
        goto L_01AEAB;
    }
    popAddress();
    return;
L_01AEAB:
    pushAddress(0xAEAD);
    jump(0xAEE3);
    if (handleReturnAddress(poppedEntry.value, 0xAEAD)) return;
    pushAddress(0xAEB0);
    jump(0xB005);
    if (handleReturnAddress(poppedEntry.value, 0xAEB0)) return;
    SUB_01AEB1();
    return;
}

void game::SUB_01AEB1() {
    a = 0x0F;
    myMapper->writeCPU(0x058C, a);
    do {
        do {
            pushAddress(0xAEB8);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xAEB8)) return;
            pushAddress(0xAEBB);
            jump(0xDBE8);
            if (handleReturnAddress(poppedEntry.value, 0xAEBB)) return;
            a = myMapper->readCPU(0x004C);
            opAND(0x10);
            if (!flgZ) {
                goto L_01AECD;
            }
            a = myMapper->readCPU(0x003F);
            opAND(0x3F);
        } while (!flgZ);
        opDEC(0x058C, 1);
    } while (!flgZ);
L_01AECD:
    myMapper->writeCPU(0x0005, 0x71);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    myMapper->writeCPU(0x058C, x);
    jump(0xDF61);
    return;
}

void game::SUB_01AEDD() {
    pushAddress(0xAEDF);
    jump(0xAEE3);
    if (handleReturnAddress(poppedEntry.value, 0xAEDF)) return;
    jump(0xAEB1);
    return;
}

void game::SUB_01AEE3() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x8C;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xAEF9);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xAEF9)) return;
    a = 0x05;
    pushAddress(0xAEFE);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xAEFE)) return;
    a = 0x1A;
    pushAddress(0xAF03);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xAF03)) return;
    a = 0x1D;
    pushAddress(0xAF08);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0xAF08)) return;
    pushAddress(0xAF0B);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xAF0B)) return;
    pushAddress(0xAF0E);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xAF0E)) return;
    pushAddress(0xAF11);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xAF11)) return;
    myMapper->writeCPU(0x0005, 0x71);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xAF1E);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xAF1E)) return;
    jump(0xB172);
    return;
}

void game::SUB_01AF22() {
    a = myMapper->readCPU(0x00AA);
    x = myMapper->readCPU(0x00B1);
    myMapper->writeCPU(0x00B1, a);
    myMapper->writeCPU(0x00AA, x);
    a = myMapper->readCPU(0x00AB);
    x = myMapper->readCPU(0x00B0);
    myMapper->writeCPU(0x00B0, a);
    myMapper->writeCPU(0x00AB, x);
    a = myMapper->readCPU(0x00AC);
    x = myMapper->readCPU(0x00AF);
    myMapper->writeCPU(0x00AF, a);
    myMapper->writeCPU(0x00AC, x);
    a = myMapper->readCPU(0x00AD);
    x = myMapper->readCPU(0x00AE);
    myMapper->writeCPU(0x00AE, a);
    myMapper->writeCPU(0x00AD, x);
    myMapper->writeCPU(0x0386, 0x00);
    do {
        a = myMapper->readCPU(0x0386);
        opASL_A(2);
        x = a;
        y = 0x00;
        do {
            a = myMapper->readCPU(0x06A9 + x);
            opLSR_A(4);
            opCMP(a, myMapper->readCPU(0x00AA + y));
            if (!flgZ) {
                if (!flgC) {
                    goto L_01AF81;
                }
                goto L_01AF76;
            }
            a = myMapper->readCPU(0x06A9 + x);
            opAND(0x0F);
            opCMP(a, myMapper->readCPU(0x00AB + y));
            if (flgZ) {
                goto L_01AF6F;
            }
            if (!flgC) {
                goto L_01AF81;
            }
            goto L_01AF76;
        L_01AF6F:
            opINX(1);
            opINY(2);
        } while (y != 0x08);
    L_01AF76:
        opINC(0x0386, 1);
    } while (myMapper->readCPU(0x0386) != 0x08);
    popAddress();
    return;
L_01AF81:
    x = 0x23;
    a = 0x07;
    flgC = true;
    opSBC(myMapper->readCPU(0x0386));
    y = a;
    setLoadFlag(y);
    if (!flgZ) {
        do {
            myMapper->writeCPU(0x0681 + x, myMapper->readCPU(0x067C + x));
            myMapper->writeCPU(0x0682 + x, myMapper->readCPU(0x067D + x));
            myMapper->writeCPU(0x0683 + x, myMapper->readCPU(0x067E + x));
            myMapper->writeCPU(0x0684 + x, myMapper->readCPU(0x067F + x));
            myMapper->writeCPU(0x0685 + x, myMapper->readCPU(0x0680 + x));
            a = x;
            flgC = true;
            opSBC(0x05);
            x = a;
            opDEY(1);
        } while (!flgZ);
    }
    a = 0x20;
    myMapper->writeCPU(0x0681 + x, a);
    myMapper->writeCPU(0x0682 + x, a);
    myMapper->writeCPU(0x0683 + x, a);
    myMapper->writeCPU(0x0684 + x, a);
    myMapper->writeCPU(0x0685 + x, a);
    x = 0x1C;
    a = 0x07;
    flgC = true;
    opSBC(myMapper->readCPU(0x0386));
    y = a;
    setLoadFlag(y);
    if (flgZ) {
        goto L_01AFEE;
    }
    do {
        myMapper->writeCPU(0x06A9 + x, myMapper->readCPU(0x06A5 + x));
        myMapper->writeCPU(0x06AA + x, myMapper->readCPU(0x06A6 + x));
        myMapper->writeCPU(0x06AB + x, myMapper->readCPU(0x06A7 + x));
        myMapper->writeCPU(0x06AC + x, myMapper->readCPU(0x06A8 + x));
        a = x;
        flgC = true;
        opSBC(0x04);
        x = a;
        opDEY(1);
    } while (!flgZ);
L_01AFEE:
    y = 0x00;
    do {
        a = myMapper->readCPU(0x00AA + y);
        opASL_A(4);
        opORA(myMapper->readCPU(0x00AB + y));
        myMapper->writeCPU(0x06A9 + x, a);
        opINY(2);
        opINX(1);
    } while (y != 0x08);
    popAddress();
}

void game::SUB_01B005() {
    a = 0x00;
    myMapper->writeCPU(0x052A, a);
    myMapper->writeCPU(0x0476, a);
    a = 0x7D;
    myMapper->writeCPU(0x0385, a);
    do {
        pushAddress(0xB014);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xB014)) return;
        pushAddress(0xB017);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xB017)) return;
        pushAddress(0xB01A);
        jump(0xB031);
        if (handleReturnAddress(poppedEntry.value, 0xB01A)) return;
        pushAddress(0xB01D);
        jump(0xB119);
        if (handleReturnAddress(poppedEntry.value, 0xB01D)) return;
        pushAddress(0xB020);
        jump(0xB0E4);
        if (handleReturnAddress(poppedEntry.value, 0xB020)) return;
        a = myMapper->readCPU(0x004B);
        opAND(0x10);
        if (!flgZ) {
            goto L_01B02E;
        }
        a = myMapper->readCPU(0x0476);
    } while (a != 0x05);
L_01B02E:
    jump(0xCA04);
    return;
}

void game::SUB_01B031() {
    a = myMapper->readCPU(0x052A);
    opASL_A(3);
    flgC = false;
    opADC(0x15);
    if (a == myMapper->readCPU(0x0385)) {
        a = myMapper->readCPU(0x004B);
        opAND(0x02);
        if (!flgZ) {
            if (myMapper->readCPU(0x052A) == 0) {
                goto L_01B04D;
            }
            opDEC(0x052A, 1);
        }
    L_01B04D:
        a = myMapper->readCPU(0x004B);
        opAND(0x01);
        if (!flgZ) {
            if (myMapper->readCPU(0x052A) == 0x19) {
                goto L_01B05D;
            }
            opINC(0x052A, 1);
        }
    }
L_01B05D:
    a = myMapper->readCPU(0x004C);
    opAND(0x40);
    if (!flgZ) {
        if (myMapper->readCPU(0x0476) == 0) {
            goto L_01B094;
        }
        a = myMapper->readCPU(0x0386);
        opASL_A(2);
        flgC = false;
        opADC(myMapper->readCPU(0x0386));
        flgC = false;
        opADC(myMapper->readCPU(0x0476));
        y = a;
        myMapper->writeCPU(0x0681 + y, 0x20);
        opDEC(0x0476, 1);
        a = myMapper->readCPU(0x0386);
        opASL_A(1);
        y = a;
        a = myMapper->readCPU(0xB0D4 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x0476));
        x = a;
        y = myMapper->readCPU(0xB0D5 + y);
        a = 0x20;
        pushAddress(0xB093);
        jump(0xB263);
        if (handleReturnAddress(poppedEntry.value, 0xB093)) return;
    }
L_01B094:
    a = myMapper->readCPU(0x004C);
    opAND(0x80);
    if (flgZ) {
        goto L_01B0D3;
    }
    a = 0x1D;
    pushAddress(0xB09E);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB09E)) return;
    a = myMapper->readCPU(0x0386);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0xB0D4 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0476));
    x = a;
    y = myMapper->readCPU(0xB0D5 + y);
    a = myMapper->readCPU(0x052A);
    flgC = false;
    opADC(0x61);
    pushAddress(0xB0B8);
    jump(0xB263);
    if (handleReturnAddress(poppedEntry.value, 0xB0B8)) return;
    a = myMapper->readCPU(0x0386);
    opASL_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x0386));
    flgC = false;
    opADC(myMapper->readCPU(0x0476));
    y = a;
    a = myMapper->readCPU(0x052A);
    flgC = false;
    opADC(0x61);
    myMapper->writeCPU(0x0681 + y, a);
    opINC(0x0476, 1);
L_01B0D3:
    popAddress();
}

void game::SUB_01B0E4() {
    a = myMapper->readCPU(0x0386);
    opASL_A(1);
    y = a;
    a = myMapper->readCPU(0xB0D4 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0476));
    x = a;
    y = myMapper->readCPU(0xB0D5 + y);
    a = x;
    opASL_A(3);
    myMapper->writeCPU(0x0217, a);
    a = y;
    opASL_A(3);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0214, a);
    x = 0x00;
    a = myMapper->readCPU(0x003F);
    opAND(0x08);
    if (!flgZ) {
        goto L_01B110;
    }
    x = 0x90;
L_01B110:
    myMapper->writeCPU(0x0215, x);
    myMapper->writeCPU(0x0216, 0x00);
    popAddress();
}

void game::SUB_01B119() {
    myMapper->writeCPU(0x03C1, 0xA0);
    a = myMapper->readCPU(0x052A);
    opASL_A(3);
    flgC = false;
    opADC(0x15);
    opCMP(a, myMapper->readCPU(0x0385));
    if (!flgZ) {
        if (flgC) {
            goto L_01B134;
        }
        opDEC(0x0385, 1);
        goto L_01B137;
    L_01B134:
        opINC(0x0385, 1);
    }
L_01B137:
    a = myMapper->readCPU(0x0385);
    myMapper->writeCPU(0x0207, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x020B, a);
    a = myMapper->readCPU(0x03C1);
    myMapper->writeCPU(0x0204, a);
    myMapper->writeCPU(0x0208, a);
    a = myMapper->readCPU(0x003F);
    opLSR_A(3);
    opAND(0x03);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0205, myMapper->readCPU(0xB16A + x));
    myMapper->writeCPU(0x0209, myMapper->readCPU(0xB16B + x));
    a = 0x00;
    myMapper->writeCPU(0x0206, a);
    myMapper->writeCPU(0x020A, a);
    popAddress();
}

void game::SUB_01B172() {
    a = 0x00;
    myMapper->writeCPU(0x0475, a);
    myMapper->writeCPU(0x0385, a);
    a = 0x06;
    myMapper->writeCPU(0x03C1, a);
    do {
        opINC(0x0385, 1);
        pushAddress(0xB184);
        jump(0xB1AC);
        if (handleReturnAddress(poppedEntry.value, 0xB184)) return;
        pushAddress(0xB187);
        jump(0xB1C2);
        if (handleReturnAddress(poppedEntry.value, 0xB187)) return;
        opINC(0x0385, 1);
        pushAddress(0xB18D);
        jump(0xB1F6);
        if (handleReturnAddress(poppedEntry.value, 0xB18D)) return;
        opINC(0x0475, 1);
        a = myMapper->readCPU(0x0475);
        opAND(0x01);
        if (!flgZ) {
            goto L_01B1A4;
        }
        myMapper->writeCPU(0x0385, a);
        flgC = false;
        a = myMapper->readCPU(0x03C1);
        opADC(0x03);
        myMapper->writeCPU(0x03C1, a);
    L_01B1A4:
        a = myMapper->readCPU(0x0475);
    } while (a != 0x08);
    popAddress();
}

void game::SUB_01B1AC() {
    pushAddress(0xB1AE);
    jump(0xDBA4);
    if (handleReturnAddress(poppedEntry.value, 0xB1AE)) return;
    a = myMapper->readCPU(0x0475);
    flgC = false;
    opADC(0x31);
    x = myMapper->readCPU(0x0385);
    y = myMapper->readCPU(0x03C1);
    pushAddress(0xB1BD);
    jump(0xB263);
    if (handleReturnAddress(poppedEntry.value, 0xB1BD)) return;
    opINC(0x0385, 1);
    popAddress();
}

void game::SUB_01B1C2() {
    a = myMapper->readCPU(0x0475);
    opASL_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x0475));
    myMapper->writeCPU(0x0529, a);
    a = 0x00;
    myMapper->writeCPU(0x0535, a);
    do {
        pushAddress(0xB1D5);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xB1D5)) return;
        x = myMapper->readCPU(0x0529);
        a = myMapper->readCPU(0x0681 + x);
        x = myMapper->readCPU(0x0385);
        y = myMapper->readCPU(0x03C1);
        pushAddress(0xB1E4);
        jump(0xB263);
        if (handleReturnAddress(poppedEntry.value, 0xB1E4)) return;
        opINC(0x0529, 1);
        opINC(0x0385, 1);
        opINC(0x0535, 1);
        a = myMapper->readCPU(0x0535);
    } while (a != 0x05);
    popAddress();
}

void game::SUB_01B1F6() {
    a = myMapper->readCPU(0x0475);
    opASL_A(2);
    myMapper->writeCPU(0x0529, a);
    a = 0x00;
    myMapper->writeCPU(0x0535, a);
    do {
        pushAddress(0xB205);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xB205)) return;
        x = myMapper->readCPU(0x0529);
        a = myMapper->readCPU(0x06A9 + x);
        opLSR_A(4);
        flgC = false;
        opADC(0x30);
        x = myMapper->readCPU(0x0385);
        y = myMapper->readCPU(0x03C1);
        pushAddress(0xB21B);
        jump(0xB263);
        if (handleReturnAddress(poppedEntry.value, 0xB21B)) return;
        pushAddress(0xB21E);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xB21E)) return;
        opINC(0x0385, 1);
        x = myMapper->readCPU(0x0529);
        a = myMapper->readCPU(0x06A9 + x);
        opAND(0x0F);
        flgC = false;
        opADC(0x30);
        x = myMapper->readCPU(0x0385);
        y = myMapper->readCPU(0x03C1);
        pushAddress(0xB235);
        jump(0xB263);
        if (handleReturnAddress(poppedEntry.value, 0xB235)) return;
        opINC(0x0529, 1);
        opINC(0x0385, 1);
        opINC(0x0535, 1);
        a = myMapper->readCPU(0x0535);
    } while (a != 0x04);
    popAddress();
}

void game::SUB_01B263() {
    opPHA();
    a = x;
    opPHA();
    x = 0x20;
    pushAddress(0xB26A);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xB26A)) return;
    a = x;
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x01C9, a);
    a = y;
    opADC(0x20);
    myMapper->writeCPU(0x01C8, a);
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x01C9));
    myMapper->writeCPU(0x01C9, a);
    a = myMapper->readCPU(0x01C8);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x01C8, a);
    a = myMapper->readCPU(0x01C9);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0190, a);
    a = myMapper->readCPU(0x01C8);
    opADC(0x00);
    myMapper->writeCPU(0x018F, a);
    a = 0x1A;
    myMapper->writeCPU(0x065E, a);
    opPLA();
    if (a == 0x20) {
        a = 0x00;
        myMapper->writeCPU(0x065E, a);
    }
    else {
        if (a < 0x30) {
            goto L_01B2BF;
        }
        if (a >= 0x3A) {
            goto L_01B2BF;
        }
        flgC = true;
        opSBC(0xFB);
        x = 0x0A;
        myMapper->writeCPU(0x065E, x);
        goto L_01B2C2;
    L_01B2BF:
        flgC = true;
        opSBC(0x60);
    }
L_01B2C2:
    myMapper->writeCPU(0x01CA, a);
    flgC = false;
    opADC(myMapper->readCPU(0x065E));
    myMapper->writeCPU(0x0191, a);
    popAddress();
}

void game::SUB_01B2CD() {
    x = 0x1F;
    do {
        myMapper->writeCPU(0x06A9 + x, myMapper->readCPU(0xB30C + x));
        opDEX(1);
    } while (!flgN);
    x = 0x27;
    do {
        a = myMapper->readCPU(0xB2E4 + x);
        myMapper->writeCPU(0x0681 + x, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01B32C() {
    pushAddress(0xB32E);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xB32E)) return;
    pushAddress(0xB331);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xB331)) return;
    pushAddress(0xB334);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xB334)) return;
    y = myMapper->readCPU(0x0051);
    x = myMapper->readCPU((0x0059 + y) & 0x00ff);
    myMapper->writeCPU(0x007C, myMapper->readCPU(0xC280 + x));
    myMapper->writeCPU(0x007D, myMapper->readCPU(0xC29E + x));
    a = 0x00;
    x = myMapper->readCPU((0x0053 + y) & 0x00ff);
    setLoadFlag(x);
    if (!flgZ) {
        do {
            flgC = false;
            opADC(0x0A);
            opDEX(1);
        } while (!flgZ);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0052 + y));
    myMapper->writeCPU(0x00A8, a);
    a = 0x00;
    x = myMapper->readCPU((0x0057 + y) & 0x00ff);
    setLoadFlag(x);
    if (flgZ) {
        goto L_01B361;
    }
    do {
        flgC = false;
        opADC(0x0A);
        opDEX(1);
    } while (!flgZ);
L_01B361:
    flgC = false;
    opADC(myMapper->readCPU(0x0056 + y));
    myMapper->writeCPU(0x00A9, a);
    a = 0x00;
    myMapper->writeCPU(0x0052 + y, a);
    myMapper->writeCPU(0x0053 + y, a);
    myMapper->writeCPU(0x0056 + y, a);
    myMapper->writeCPU(0x0057 + y, a);
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x90;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xB383);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xB383)) return;
    a = 0x16;
    pushAddress(0xB388);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xB388)) return;
    a = 0x1D;
    pushAddress(0xB38D);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0xB38D)) return;
    pushAddress(0xB390);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xB390)) return;
    pushAddress(0xB393);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xB393)) return;
    myMapper->writeCPU(0x0005, 0x91);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xB3A0);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xB3A0)) return;
    pushAddress(0xB3A3);
    jump(0xB3C1);
    if (handleReturnAddress(poppedEntry.value, 0xB3A3)) return;
    pushAddress(0xB3A6);
    jump(0xB425);
    if (handleReturnAddress(poppedEntry.value, 0xB3A6)) return;
    x = 0x02;
    do {
        y = 0x3C;
        do {
            pushAddress(0xB3AD);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB3AD)) return;
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0005, 0x91);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_01B3C1() {
    x = myMapper->readCPU(0x00A8);
    y = 0x64;
    pushAddress(0xB3C7);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xB3C7)) return;
    myMapper->writeCPU(0x05AD, x);
    myMapper->writeCPU(0x05AE, y);
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x007C));
    a = 0x00;
    myMapper->writeCPU(0x0002, a);
    pushAddress(0xB3D8);
    jump(0xB408);
    if (handleReturnAddress(poppedEntry.value, 0xB3D8)) return;
    a = myMapper->readCPU(0x05AD);
    if (a >= 0x63) {
        a = 0x63;
    }
    myMapper->writeCPU(0x0003, a);
    x = myMapper->readCPU(0x00A9);
    y = 0x64;
    pushAddress(0xB3EA);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xB3EA)) return;
    myMapper->writeCPU(0x05AD, x);
    myMapper->writeCPU(0x05AE, y);
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x007D));
    a = 0x00;
    myMapper->writeCPU(0x0002, a);
    pushAddress(0xB3FB);
    jump(0xB408);
    if (handleReturnAddress(poppedEntry.value, 0xB3FB)) return;
    a = myMapper->readCPU(0x05AD);
    if (a < 0x63) {
        goto L_01B405;
    }
    a = 0x63;
L_01B405:
    myMapper->writeCPU(0x0004, a);
    popAddress();
}

void game::SUB_01B408() {
    x = 0x00;
    while (true) {
        a = myMapper->readCPU(0x05AD);
        flgC = true;
        opSBC(myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x05AD, a);
        a = myMapper->readCPU(0x05AE);
        opSBC(myMapper->readCPU(0x0002));
        myMapper->writeCPU(0x05AE, a);
        if (!flgC) {
            goto L_01B421;
        }
        opINX(1);
    }
L_01B421:
    myMapper->writeCPU(0x05AD, x);
    popAddress();
}

void game::SUB_01B425() {
    myMapper->writeCPU(0x047F, 0x00);
    x = 0x90;
    y = 0x30;
    a = 0x00;
    pushAddress(0xB432);
    jump(0xB5A3);
    if (handleReturnAddress(poppedEntry.value, 0xB432)) return;
    myMapper->writeCPU(0x047F, 0x30);
    x = 0xA8;
    y = 0x30;
    a = 0x00;
    pushAddress(0xB440);
    jump(0xB5A3);
    if (handleReturnAddress(poppedEntry.value, 0xB440)) return;
    a = 0xC0;
    myMapper->writeCPU(0x047F, a);
    x = 0xC0;
    y = 0x38;
    pushAddress(0xB44C);
    jump(0xB53A);
    if (handleReturnAddress(poppedEntry.value, 0xB44C)) return;
    a = 0xE0;
    myMapper->writeCPU(0x047F, a);
    x = 0x50;
    y = 0xA0;
    pushAddress(0xB458);
    jump(0xB53A);
    if (handleReturnAddress(poppedEntry.value, 0xB458)) return;
    myMapper->writeCPU(0x047F, 0x60);
    x = 0x20;
    y = 0x98;
    a = 0x00;
    pushAddress(0xB466);
    jump(0xB5A3);
    if (handleReturnAddress(poppedEntry.value, 0xB466)) return;
    myMapper->writeCPU(0x047F, 0x90);
    x = 0x38;
    y = 0x98;
    a = 0x00;
    pushAddress(0xB474);
    jump(0xB5A3);
    if (handleReturnAddress(poppedEntry.value, 0xB474)) return;
    a = 0x00;
    myMapper->writeCPU(0x0529, a);
    while (true) {
        pushAddress(0xB47C);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xB47C)) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x10);
        if (flgZ) {
            goto L_01B488;
        }
        myMapper->writeCPU(0x0529, myMapper->readCPU(0x0003));
    L_01B488:
        a = myMapper->readCPU(0x0529);
        opLSR_A(3);
        x = a;
        do {
            pushAddress(0xB491);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB491)) return;
            opDEX(1);
        } while (!flgN);
        a = myMapper->readCPU(0x0529);
        x = 0x00;
        while (true) {
            flgC = true;
            opSBC(0x0A);
            if (!flgC) {
                goto L_01B4A3;
            }
            opINX(1);
        }
    L_01B4A3:
        if (x >= 0x0A) {
            goto L_01B4D7;
        }
        flgC = false;
        opADC(0x0A);
        opPHA();
        myMapper->writeCPU(0x047F, 0x00);
        a = x;
        x = 0x90;
        y = 0x30;
        pushAddress(0xB4B7);
        jump(0xB5A3);
        if (handleReturnAddress(poppedEntry.value, 0xB4B7)) return;
        a = 0x30;
        myMapper->writeCPU(0x047F, a);
        opPLA();
        x = 0xA8;
        y = 0x30;
        pushAddress(0xB4C4);
        jump(0xB5A3);
        if (handleReturnAddress(poppedEntry.value, 0xB4C4)) return;
        if (myMapper->readCPU(0x0529) == myMapper->readCPU(0x0003)) {
            goto L_01B4D7;
        }
        opINC(0x0529, 1);
        a = 0x05;
        pushAddress(0xB4D3);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xB4D3)) return;
    }
L_01B4D7:
    a = 0x00;
    myMapper->writeCPU(0x0529, a);
    while (true) {
        pushAddress(0xB4DE);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xB4DE)) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x10);
        if (flgZ) {
            goto L_01B4EA;
        }
        myMapper->writeCPU(0x0529, myMapper->readCPU(0x0004));
    L_01B4EA:
        a = myMapper->readCPU(0x0529);
        opLSR_A(3);
        x = a;
        do {
            pushAddress(0xB4F3);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB4F3)) return;
            opDEX(1);
        } while (!flgN);
        a = myMapper->readCPU(0x0529);
        x = 0x00;
        while (true) {
            flgC = true;
            opSBC(0x0A);
            if (!flgC) {
                goto L_01B505;
            }
            opINX(1);
        }
    L_01B505:
        if (x >= 0x0A) {
            goto L_01B539;
        }
        flgC = false;
        opADC(0x0A);
        opPHA();
        myMapper->writeCPU(0x047F, 0x60);
        a = x;
        x = 0x20;
        y = 0x98;
        pushAddress(0xB519);
        jump(0xB5A3);
        if (handleReturnAddress(poppedEntry.value, 0xB519)) return;
        a = 0x90;
        myMapper->writeCPU(0x047F, a);
        opPLA();
        x = 0x38;
        y = 0x98;
        pushAddress(0xB526);
        jump(0xB5A3);
        if (handleReturnAddress(poppedEntry.value, 0xB526)) return;
        a = 0x05;
        pushAddress(0xB52B);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xB52B)) return;
        a = myMapper->readCPU(0x0529);
        if (a == myMapper->readCPU(0x0004)) {
            goto L_01B539;
        }
        opINC(0x0529, 1);
    }
L_01B539:
    popAddress();
}

void game::SUB_01B53A() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0001, x);
    myMapper->writeCPU(0x03CD, y);
    y = myMapper->readCPU(0x047F);
    a = 0x00;
    myMapper->writeCPU(0x0481, a);
    myMapper->writeCPU(0x0480, a);
    x = 0x00;
    do {
        myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0xB59D + x));
        myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
        myMapper->writeCPU(0x0202 + y, 0x00);
        a = y;
        flgC = false;
        opADC(0x04);
        y = a;
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opINC(0x0480, 1);
        if (myMapper->readCPU(0x0480) != 0x02) {
            goto L_01B591;
        }
        myMapper->writeCPU(0x0480, 0x00);
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0001));
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_01B591:
        opINX(1);
        opINC(0x0481, 1);
    } while (myMapper->readCPU(0x0481) != 0x06);
    popAddress();
}

void game::SUB_01B5A3() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0001, x);
    myMapper->writeCPU(0x03CD, y);
    x = a;
    x = myMapper->readCPU(0xB609 + x);
    y = myMapper->readCPU(0x047F);
    a = 0x00;
    myMapper->writeCPU(0x0481, a);
    myMapper->writeCPU(0x0480, a);
    do {
        myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0xB613 + x));
        myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
        myMapper->writeCPU(0x0202 + y, 0x00);
        a = y;
        flgC = false;
        opADC(0x04);
        y = a;
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opINC(0x0480, 1);
        if (myMapper->readCPU(0x0480) != 0x03) {
            goto L_01B5FD;
        }
        myMapper->writeCPU(0x0480, 0x00);
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0001));
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_01B5FD:
        opINX(1);
        opINC(0x0481, 1);
    } while (myMapper->readCPU(0x0481) != 0x0C);
    popAddress();
}

void game::SUB_01B68B() {
    pushAddress(0xB68D);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xB68D)) return;
    a = 0x09;
    pushAddress(0xB692);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xB692)) return;
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x94;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xB6A1);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xB6A1)) return;
    if (myMapper->readCPU(0x0051) == 0) {
        goto L_01B6BA;
    }
    myMapper->writeCPU(0x01CB, 0x20);
    myMapper->writeCPU(0x01CC, 0x59);
    myMapper->writeCPU(0x01CD, 0x0C);
    myMapper->writeCPU(0x01CE, 0x13);
L_01B6BA:
    a = 0x17;
    pushAddress(0xB6BE);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xB6BE)) return;
    a = 0x15;
    pushAddress(0xB6C3);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0xB6C3)) return;
    pushAddress(0xB6C6);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xB6C6)) return;
    pushAddress(0xB6C9);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xB6C9)) return;
    pushAddress(0xB6CC);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xB6CC)) return;
    pushAddress(0xB6CF);
    jump(0xB70F);
    if (handleReturnAddress(poppedEntry.value, 0xB6CF)) return;
    myMapper->writeCPU(0x0005, 0xB1);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xB6DC);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xB6DC)) return;
    a = 0x0A;
    myMapper->writeCPU(0x058C, a);
    do {
        do {
            pushAddress(0xB6E4);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB6E4)) return;
            pushAddress(0xB6E7);
            jump(0xB7F4);
            if (handleReturnAddress(poppedEntry.value, 0xB6E7)) return;
            pushAddress(0xB6EA);
            jump(0xCA15);
            if (handleReturnAddress(poppedEntry.value, 0xB6EA)) return;
            pushAddress(0xB6ED);
            jump(0xDBE8);
            if (handleReturnAddress(poppedEntry.value, 0xB6ED)) return;
            a = myMapper->readCPU(0x004C);
            opAND(0x10);
            if (!flgZ) {
                goto L_01B6FF;
            }
            a = myMapper->readCPU(0x003F);
            opAND(0x3F);
        } while (!flgZ);
        opDEC(0x058C, 1);
    } while (!flgZ);
L_01B6FF:
    myMapper->writeCPU(0x0005, 0xB1);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    myMapper->writeCPU(0x058C, x);
    jump(0xDF61);
    return;
}

void game::SUB_01B70F() {
    pushAddress(0xB711);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0xB711)) return;
    a = 0x00;
    myMapper->writeCPU(0x05BD, a);
    myMapper->writeCPU(0x0586, a);
    myMapper->writeCPU(0x0587, 0x1D);
    myMapper->writeCPU(0x0588, 0x1D);
    x = 0x0F;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0xB866 + x));
        opDEX(1);
    } while (!flgN);
    a = 0x00;
    myMapper->writeCPU(0x0583, a);
    myMapper->writeCPU(0x0584, a);
    myMapper->writeCPU(0x0386, 0x00);
    myMapper->writeCPU(0x03C2, 0xB8);
    a = 0x00;
    myMapper->writeCPU(0x03A4, a);
    myMapper->writeCPU(0x03E0, a);
    myMapper->writeCPU(0x041C, 0x04);
    myMapper->writeCPU(0x03FE, 0x00);
    myMapper->writeCPU(0x0476, 0x01);
    myMapper->writeCPU(0x038B, 0xD7);
    myMapper->writeCPU(0x03C7, 0xD6);
    a = 0x00;
    myMapper->writeCPU(0x03A9, a);
    myMapper->writeCPU(0x03E5, a);
    myMapper->writeCPU(0x0421, 0x02);
    myMapper->writeCPU(0x0403, 0x00);
    myMapper->writeCPU(0x047B, 0x01);
    myMapper->writeCPU(0x0388, 0x6A);
    myMapper->writeCPU(0x03C4, 0x57);
    myMapper->writeCPU(0x0389, 0x82);
    myMapper->writeCPU(0x03C5, 0x57);
    a = 0x00;
    myMapper->writeCPU(0x03A6, a);
    myMapper->writeCPU(0x03E2, a);
    myMapper->writeCPU(0x03A7, a);
    myMapper->writeCPU(0x03E3, a);
    a = 0x07;
    myMapper->writeCPU(0x041E, a);
    myMapper->writeCPU(0x041F, a);
    myMapper->writeCPU(0x0400, 0x08);
    myMapper->writeCPU(0x0401, 0x09);
    a = 0x01;
    myMapper->writeCPU(0x0478, a);
    myMapper->writeCPU(0x0479, a);
    myMapper->writeCPU(0x0385, 0xC0);
    myMapper->writeCPU(0x03C1, 0xA7);
    myMapper->writeCPU(0x0387, 0xD8);
    myMapper->writeCPU(0x03C3, 0xA7);
    a = 0x00;
    myMapper->writeCPU(0x03A3, a);
    myMapper->writeCPU(0x03DF, a);
    myMapper->writeCPU(0x03A5, a);
    myMapper->writeCPU(0x03E1, a);
    a = 0x07;
    myMapper->writeCPU(0x041B, a);
    myMapper->writeCPU(0x041D, a);
    myMapper->writeCPU(0x03FD, 0x0A);
    myMapper->writeCPU(0x03FF, 0x0B);
    a = 0x01;
    myMapper->writeCPU(0x0475, a);
    myMapper->writeCPU(0x0477, a);
    pushAddress(0xB7F2);
    jump(0xCA15);
    if (handleReturnAddress(poppedEntry.value, 0xB7F2)) return;
    popAddress();
}

void game::SUB_01B7F4() {
    a = myMapper->readCPU(0x003F);
    opLSR_A(1);
    opAND(0x03);
    opASL_A(1);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x03FD, a);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x03FF, a);
    a = myMapper->readCPU(0x003F);
    opLSR_A(2);
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x0403, myMapper->readCPU(0xB842 + y));
    a = myMapper->readCPU(0x003F);
    opAND(0x1F);
    if (flgZ) {
        opINC(0x04CF, 1);
        a = myMapper->readCPU(0x04CF);
        opAND(0x1F);
        y = a;
        a = myMapper->readCPU(0xB846 + y);
        myMapper->writeCPU(0x0400, a);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0401, a);
    }
    myMapper->writeCPU(0x03FE, 0x00);
    a = myMapper->readCPU(0x003F);
    opLSR_A(3);
    opAND(0x07);
    if (!flgZ) {
        goto L_01B841;
    }
    a = 0x01;
    myMapper->writeCPU(0x03FE, a);
L_01B841:
    popAddress();
}

void game::SUB_01BAFC() {
    a = 0x0B;
    pushAddress(0xBB00);
    jump(0xF0CE);
    if (handleReturnAddress(poppedEntry.value, 0xBB00)) return;
    pushAddress(0xBB03);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xBB03)) return;
    pushAddress(0xBB06);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xBB06)) return;
    pushAddress(0xBB09);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xBB09)) return;
    a = 0x01;
    pushAddress(0xBB0E);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xBB0E)) return;
    myMapper->writeCPU(0x0005, 0xD1);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xBB1D);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xBB1D)) return;
    a = 0x12;
    pushAddress(0xBB22);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xBB22)) return;
    a = 0x15;
    pushAddress(0xBB27);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0xBB27)) return;
    pushAddress(0xBB2A);
    jump(0xBB88);
    if (handleReturnAddress(poppedEntry.value, 0xBB2A)) return;
    pushAddress(0xBB2D);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xBB2D)) return;
    myMapper->writeCPU(0x0005, 0xD1);
    a = 0x9C;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xBB3A);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xBB3A)) return;
    do {
        pushAddress(0xBB3D);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xBB3D)) return;
        pushAddress(0xBB40);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xBB40)) return;
        pushAddress(0xBB43);
        jump(0xBBDD);
        if (handleReturnAddress(poppedEntry.value, 0xBB43)) return;
        pushAddress(0xBB46);
        jump(0xF356);
        if (handleReturnAddress(poppedEntry.value, 0xBB46)) return;
        pushAddress(0xBB49);
        jump(0xBCF5);
        if (handleReturnAddress(poppedEntry.value, 0xBB49)) return;
        pushAddress(0xBB4C);
        jump(0xBCA5);
        if (handleReturnAddress(poppedEntry.value, 0xBB4C)) return;
        pushAddress(0xBB4F);
        jump(0xBD5C);
        if (handleReturnAddress(poppedEntry.value, 0xBB4F)) return;
        pushAddress(0xBB52);
        jump(0xBD2E);
        if (handleReturnAddress(poppedEntry.value, 0xBB52)) return;
        a = myMapper->readCPU(0x00C1);
        if (a == 0x03) {
            goto L_01BB67;
        }
        a = myMapper->readCPU(0x00C2);
        if (a == 0x06) {
            goto L_01BB6E;
        }
        a = myMapper->readCPU(0x065C);
        setLoadFlag(a);
    } while (flgZ);
    goto L_01BB6E;
L_01BB67:
    opINC(0x0085, 1);
    y = 0x01;
    pushAddress(0xBB6D);
    jump(0xF89D);
    if (handleReturnAddress(poppedEntry.value, 0xBB6D)) return;
L_01BB6E:
    x = 0x04;
    do {
        y = 0x3C;
        do {
            pushAddress(0xBB74);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xBB74)) return;
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0005, 0xD1);
    a = 0x9C;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_01BB88() {
    myMapper->writeCPU(0x0385, 0x58);
    myMapper->writeCPU(0x03C1, 0x78);
    a = 0x00;
    myMapper->writeCPU(0x03FD, a);
    myMapper->writeCPU(0x00B2, a);
    myMapper->writeCPU(0x00B7, a);
    myMapper->writeCPU(0x00C2, a);
    myMapper->writeCPU(0x00C1, a);
    myMapper->writeCPU(0x00EA, a);
    myMapper->writeCPU(0x065C, a);
    myMapper->writeCPU(0x00EC, 0x01);
    myMapper->writeCPU(0x00EB, 0x03);
    a = 0xFF;
    myMapper->writeCPU(0x00BE, a);
    myMapper->writeCPU(0x00BF, a);
    myMapper->writeCPU(0x00C0, a);
    myMapper->writeCPU(0x00BB, a);
    myMapper->writeCPU(0x00BC, a);
    myMapper->writeCPU(0x00BD, a);
    x = 0x02;
    do {
        do {
            pushAddress(0xBBBE);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0xBBBE)) return;
            opAND(0x07);
            y = a;
            do {
                pushAddress(0xBBC4);
                jump(0xDCD8);
                if (handleReturnAddress(poppedEntry.value, 0xBBC4)) return;
                opDEY(1);
            } while (!flgN);
            pushAddress(0xBBCA);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0xBBCA)) return;
            opAND(0x07);
            y = 0x02;
        L_01BBCF:
            opCMP(a, myMapper->readCPU(0x00BE + y));
        } while (flgZ);
        opDEY(1);
        if (!flgN) {
            goto L_01BBCF;
        }
        myMapper->writeCPU((0x00BE + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01BBDD() {
    a = myMapper->readCPU(0x004B);
    opAND(0x08);
    if (!flgZ) {
        a = myMapper->readCPU(0x03C1);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x03C1, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x04);
    if (!flgZ) {
        a = myMapper->readCPU(0x03C1);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x03C1, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x02);
    if (!flgZ) {
        a = myMapper->readCPU(0x0385);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x0385, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x0385);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x0385, a);
    }
    a = myMapper->readCPU(0x004C);
    opAND(0xC0);
    if (!flgZ) {
        a = myMapper->readCPU(0x00B7);
        setLoadFlag(a);
        if (flgZ) {
            pushAddress(0xBC25);
            jump(0xBC6F);
            if (handleReturnAddress(poppedEntry.value, 0xBC25)) return;
            if (flgC) {
                x = myMapper->readCPU(0x00B2);
                if (x != 0x03) {
                    y = 0x02;
                    do {
                        if (a == myMapper->readCPU(0x00BB + y)) {
                            goto L_01BC5A;
                        }
                        opDEY(1);
                    } while (!flgN);
                    myMapper->writeCPU((0x00BB + x) & 0x00ff, a);
                    myMapper->writeCPU(0x00B3, a);
                    y = myMapper->readCPU(0x00B2);
                    myMapper->writeCPU(0x00B5, myMapper->readCPU(0xBC6C + y));
                    y = myMapper->readCPU(0x00C2);
                    myMapper->writeCPU(0x00B6, myMapper->readCPU(0xBCEF + y));
                    myMapper->writeCPU(0x00B7, 0x01);
                    myMapper->writeCPU(0x00B4, 0x00);
                    opINC(0x00B2, 1);
                    a = 0x01;
                    pushAddress(0xBC59);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0xBC59)) return;
                }
            }
        }
    }
L_01BC5A:
    a = myMapper->readCPU(0x003F);
    opAND(0x07);
    if (!flgZ) {
        goto L_01BC6B;
    }
    opINC(0x03FD, 1);
    a = myMapper->readCPU(0x03FD);
    opAND(0x03);
    myMapper->writeCPU(0x03FD, a);
L_01BC6B:
    popAddress();
}

void game::SUB_01BC6F() {
    a = myMapper->readCPU(0x0385);
    opLSR_A(3);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x03C1);
    opLSR_A(3);
    myMapper->writeCPU(0x0002, a);
    x = 0x07;
    do {
        a = myMapper->readCPU(0xBD8A + x);
        if (a < myMapper->readCPU(0x0001)) {
            flgC = false;
            opADC(0x03);
            if (a >= myMapper->readCPU(0x0001)) {
                a = myMapper->readCPU(0xBD92 + x);
                if (a < myMapper->readCPU(0x0002)) {
                    flgC = false;
                    opADC(0x04);
                    if (a < myMapper->readCPU(0x0002)) {
                        goto L_01BCA0;
                    }
                    a = x;
                    flgC = true;
                    popAddress();
                    return;
                }
            }
        }
    L_01BCA0:
        opDEX(1);
    } while (!flgN);
    flgC = false;
    popAddress();
}

void game::SUB_01BCA5() {
    a = myMapper->readCPU(0x00B2);
    if (a == 0x03) {
        a = myMapper->readCPU(0x00B7);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_01BCEE;
        }
        a = 0x00;
        myMapper->writeCPU(0x00B8, a);
        myMapper->writeCPU(0x00B9, a);
        myMapper->writeCPU(0x00BA, a);
        myMapper->writeCPU(0x00C1, a);
        x = 0x02;
        do {
            y = 0x02;
            do {
                if (myMapper->readCPU((0x00B8 + x) & 0x00ff) != 0) {
                    goto L_01BCCE;
                }
                if (myMapper->readCPU((0x00BE + x) & 0x00ff) != myMapper->readCPU(0x00BB + y)) {
                    goto L_01BCCE;
                }
                opINC(0x00C1, 1);
                myMapper->writeCPU((0x00B8 + x) & 0x00ff, 0xFF);
            L_01BCCE:
                opDEY(1);
            } while (!flgN);
            opDEX(1);
        } while (!flgN);
        a = 0xFF;
        myMapper->writeCPU(0x00BB, a);
        myMapper->writeCPU(0x00BC, a);
        myMapper->writeCPU(0x00BD, a);
        x = myMapper->readCPU(0x00C2);
        y = myMapper->readCPU(0xBCEF + x);
        x = 0x1A;
        a = myMapper->readCPU(0x00C1);
        pushAddress(0xBCE7);
        jump(0xBE18);
        if (handleReturnAddress(poppedEntry.value, 0xBCE7)) return;
        a = 0x00;
        myMapper->writeCPU(0x00B2, a);
        opINC(0x00C2, 1);
    }
L_01BCEE:
    popAddress();
}

void game::SUB_01BCF5() {
    a = myMapper->readCPU(0x00B7);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x02) {
            goto L_01BD29;
        }
        if (myMapper->readCPU(0x00B4) == myMapper->readCPU(0x00B3)) {
            goto L_01BD18;
        }
        x = myMapper->readCPU(0x00B5);
        y = myMapper->readCPU(0x00B6);
        a = myMapper->readCPU(0x00B4);
        flgC = false;
        opADC(0x01);
        pushAddress(0xBD0E);
        jump(0xBE18);
        if (handleReturnAddress(poppedEntry.value, 0xBD0E)) return;
        a = myMapper->readCPU(0x003F);
        opAND(0x03);
        if (!flgZ) {
            goto L_01BD28;
        }
        opINC(0x00B4, 1);
        popAddress();
        return;
    L_01BD18:
        myMapper->writeCPU(0x00B7, 0x02);
        x = myMapper->readCPU(0x00B5);
        y = myMapper->readCPU(0x00B6);
        a = myMapper->readCPU(0x00B4);
        flgC = false;
        opADC(0x01);
        pushAddress(0xBD27);
        jump(0xBE18);
        if (handleReturnAddress(poppedEntry.value, 0xBD27)) return;
    }
L_01BD28:
    popAddress();
    return;
L_01BD29:
    a = 0x00;
    myMapper->writeCPU(0x00B7, a);
    popAddress();
}

void game::SUB_01BD2E() {
    myMapper->writeCPU(0x0024, 0x5C);
    myMapper->writeCPU(0x0025, 0x20);
    a = myMapper->readCPU(0x00EA);
    x = 0x4C;
    pushAddress(0xBD3C);
    jump(0xBD9A);
    if (handleReturnAddress(poppedEntry.value, 0xBD3C)) return;
    myMapper->writeCPU(0x0024, 0x59);
    myMapper->writeCPU(0x0025, 0x20);
    a = myMapper->readCPU(0x00EB);
    x = 0x92;
    pushAddress(0xBD4B);
    jump(0xBD9A);
    if (handleReturnAddress(poppedEntry.value, 0xBD4B)) return;
    myMapper->writeCPU(0x0024, 0x56);
    myMapper->writeCPU(0x0025, 0x20);
    a = myMapper->readCPU(0x00EC);
    x = 0xAD;
    pushAddress(0xBD5A);
    jump(0xBD9A);
    if (handleReturnAddress(poppedEntry.value, 0xBD5A)) return;
    popAddress();
}

void game::SUB_01BD5C() {
    a = myMapper->readCPU(0x003F);
    opAND(0x0F);
    if (flgZ) {
        opDEC(0x00EA, 1);
        if (flgN) {
            myMapper->writeCPU(0x00EA, 0x09);
            opDEC(0x00EB, 1);
            if (flgN) {
                myMapper->writeCPU(0x00EB, 0x05);
                opDEC(0x00EC, 1);
            }
        }
        a = myMapper->readCPU(0x00EA);
        opORA(myMapper->readCPU(0x00EB));
        opORA(myMapper->readCPU(0x00EC));
        if (!flgZ) {
            goto L_01BD89;
        }
        myMapper->writeCPU(0x065C, 0x01);
        a = 0x00;
        myMapper->writeCPU(0x00EA, a);
        myMapper->writeCPU(0x00EB, a);
        myMapper->writeCPU(0x00EC, a);
    }
L_01BD89:
    popAddress();
}

void game::SUB_01BD9A() {
    opASL_A(4);
    flgC = false;
    opADC(0xAA);
    myMapper->writeCPU(0x0005, a);
    a = 0x00;
    opADC(0xBE);
    myMapper->writeCPU(0x0006, a);
    myMapper->writeCPU(0x0101 + x, myMapper->readCPU(0x0024));
    myMapper->writeCPU(0x0100 + x, myMapper->readCPU(0x0025));
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x00);
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x0107 + x, myMapper->readCPU(0x0024));
    myMapper->writeCPU(0x0106 + x, myMapper->readCPU(0x0025));
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x00);
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x010D + x, myMapper->readCPU(0x0024));
    myMapper->writeCPU(0x010C + x, myMapper->readCPU(0x0025));
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x00);
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x0113 + x, myMapper->readCPU(0x0024));
    myMapper->writeCPU(0x0112 + x, myMapper->readCPU(0x0025));
    y = 0x00;
    do {
        myMapper->writeCPU(0x0102 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0108 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x010E + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        myMapper->writeCPU(0x0114 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        opINX(1);
    } while (y != 0x10);
    popAddress();
}

void game::SUB_01BE18() {
    opPHA();
    a = x;
    opPHA();
    x = 0x20;
    pushAddress(0xBE1F);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xBE1F)) return;
    myMapper->writeCPU(0x05AD, x);
    myMapper->writeCPU(0x05AE, y);
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x05AD));
    myMapper->writeCPU(0x05AD, a);
    a = myMapper->readCPU(0x05AE);
    opADC(0x00);
    myMapper->writeCPU(0x05AE, a);
    a = myMapper->readCPU(0x05AD);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x05AD, a);
    a = myMapper->readCPU(0x05AE);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x05AE, a);
    myMapper->writeCPU(0x0187, myMapper->readCPU(0x05AE));
    myMapper->writeCPU(0x0188, myMapper->readCPU(0x05AD));
    a = myMapper->readCPU(0x05AD);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x018C, a);
    a = myMapper->readCPU(0x05AE);
    opADC(0x00);
    myMapper->writeCPU(0x018B, a);
    opPLA();
    opASL_A(2);
    x = a;
    myMapper->writeCPU(0x0189, myMapper->readCPU(0xBE82 + x));
    myMapper->writeCPU(0x018A, myMapper->readCPU(0xBE83 + x));
    myMapper->writeCPU(0x018D, myMapper->readCPU(0xBE84 + x));
    a = myMapper->readCPU(0xBE85 + x);
    myMapper->writeCPU(0x018E, a);
    popAddress();
}

void game::SUB_01C000() {
    pushAddress(0xC002);
    jump(0xFEB2);
    if (handleReturnAddress(poppedEntry.value, 0xC002)) return;
    s = 0xFF;
    a = 0x00;
    x = 0x00;
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
    x = 0x0F;
    do {
        a = x;
        myMapper->writeCPU(0x0634 + x, a);
        opDEX(1);
    } while (!flgN);
    jump(0xF189);
    return;
}

void game::SUB_01C030() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    pushAddress(0xC03A);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0xC03A)) return;
    a = 0x88;
    myMapper->writeCPU(0x0040, a);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    myMapper->writeCPU(0x0041, 0x18);
    myMapper->writeCPU(0x00FE, 0x54);
    a = 0xFE;
    myMapper->writeCPU(0x00FF, a);
    popAddress();
}

void game::SUB_01C052() {
    pushAddress(0xC054);
    jump(0xC030);
    if (handleReturnAddress(poppedEntry.value, 0xC054)) return;
    a = 0xFF;
    myMapper->writeCPU(0x0062, a);
    myMapper->writeCPU(0x0076, a);
    myMapper->writeCPU(0x007E, a);
    jump(0xC075);
    return;
}

void game::SUB_01C060() {
    myMapper->writeCPU(0x058F, myMapper->readCPU((0x0052 + x) & 0x00ff));
    myMapper->writeCPU(0x0590, myMapper->readCPU((0x0053 + x) & 0x00ff));
    myMapper->writeCPU(0x0591, myMapper->readCPU((0x0056 + x) & 0x00ff));
    myMapper->writeCPU(0x0592, myMapper->readCPU((0x0057 + x) & 0x00ff));
    popAddress();
}

void game::SUB_01C075() {
    do {
        x = 0x00;
        myMapper->writeCPU(0x0051, x);
        myMapper->writeCPU(0x0595, 0x00);
        myMapper->writeCPU(0x0594, 0x02);
        a = myMapper->readCPU(0x0087);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01C0A5;
        }
        pushAddress(0xC089);
        jump(0xF2A0);
        if (handleReturnAddress(poppedEntry.value, 0xC089)) return;
        do {
            pushAddress(0xC08C);
            jump(0xC0B6);
            if (handleReturnAddress(poppedEntry.value, 0xC08C)) return;
            a = myMapper->readCPU(0x05AC);
        } while (a == 0xFF);
        x = 0x14;
        myMapper->writeCPU(0x0051, x);
        pushAddress(0xC09A);
        jump(0xF2A0);
        if (handleReturnAddress(poppedEntry.value, 0xC09A)) return;
        myMapper->writeCPU(0x0595, 0x00);
        a = 0x02;
        myMapper->writeCPU(0x0594, a);
        do {
        L_01C0A5:
            pushAddress(0xC0A7);
            jump(0xC0B6);
            if (handleReturnAddress(poppedEntry.value, 0xC0A7)) return;
            a = myMapper->readCPU(0x05AC);
        } while (a == 0xFF);
        a = myMapper->readCPU(0x0058);
        opORA(myMapper->readCPU(0x006C));
    } while (!flgZ);
    popAddress();
}

void game::SUB_01C0B6() {
    x = myMapper->readCPU(0x0051);
    a = myMapper->readCPU((0x0058 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01C0C0;
    }
    myMapper->writeCPU(0x05AC, a);
    popAddress();
    return;
L_01C0C0:
    x = myMapper->readCPU(0x0051);
    pushAddress(0xC0C4);
    jump(0xC060);
    if (handleReturnAddress(poppedEntry.value, 0xC0C4)) return;
    while (true) {
        y = myMapper->readCPU((0x0059 + x) & 0x00ff);
        a = myMapper->readCPU(0xC1EA + y);
        myMapper->writeCPU(0x0013, a);
        myMapper->writeCPU(0x0012, a);
        pushAddress(0xC0D0);
        jump(0xFFE6);
        if (handleReturnAddress(poppedEntry.value, 0xC0D0)) return;
        myMapper->writeCPU(0x058E, myMapper->readCPU(0xC244 + y));
        myMapper->writeCPU(0x0593, myMapper->readCPU(0xC262 + y));
        myMapper->writeCPU(0x0004, myMapper->readCPU(0xC2BC + y));
        a = myMapper->readCPU((0x0062 + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x0000, a);
            a = myMapper->readCPU((0x0063 + x) & 0x00ff);
            x = myMapper->readCPU(0x0000);
        }
        else {
            myMapper->writeCPU((0x0063 + x) & 0x00ff, myMapper->readCPU(0xC226 + y));
            a = myMapper->readCPU(0xC208 + y);
            myMapper->writeCPU((0x0063 + x) & 0x00ff, a);
            x = myMapper->readCPU(0xC226 + y);
        }
        myMapper->writeCPU(0x007A, x);
        myMapper->writeCPU(0x007B, a);
        a = myMapper->readCPU(0x059C);
        setLoadFlag(a);
        if (flgZ) {
            a = myMapper->readCPU(0x0004);
            setLoadFlag(a);
            if (!flgN) {
                if (a == myMapper->readCPU(0x007E)) {
                    goto L_01C112;
                }
                myMapper->writeCPU(0x007E, a);
                pushAddress(0xC111);
                jump(0xF0CE);
                if (handleReturnAddress(poppedEntry.value, 0xC111)) return;
            }
        }
    L_01C112:
        pushAddress(0xC114);
        jump(0xC030);
        if (handleReturnAddress(poppedEntry.value, 0xC114)) return;
        pushAddress(0xC117);
        jump(0xDB6A);
        if (handleReturnAddress(poppedEntry.value, 0xC117)) return;
        y = 0x00;
        myMapper->writeCPU(0x05AC, y);
        myMapper->writeCPU(0x2000, y);
        myMapper->writeCPU(0x2001, y);
        opDEY(1);
        myMapper->writeCPU(0x0586, y);
        a = myMapper->readCPU(0x007B);
        x = myMapper->readCPU(0x007A);
        pushAddress(0xC12D);
        jump(0x8000);
        if (handleReturnAddress(poppedEntry.value, 0xC12D)) return;
        pushAddress(0xC130);
        jump(0xEA06);
        if (handleReturnAddress(poppedEntry.value, 0xC130)) return;
        x = 0x00;
        myMapper->writeCPU(0x2000, x);
        myMapper->writeCPU(0x2001, x);
        x = 0x19;
        myMapper->writeCPU(0x0000, x);
        do {
            do {
                opBIT(myMapper->readCPU(0x2002));
            } while (!flgN);
            pushAddress(0xC144);
            jump(0xEA36);
            if (handleReturnAddress(poppedEntry.value, 0xC144)) return;
            opDEC(0x0000, 1);
        } while (!flgZ);
        x = myMapper->readCPU(0x0051);
        if (myMapper->readCPU(0x05AC) != 0xFE) {
            a = myMapper->readCPU((0x0059 + x) & 0x00ff);
            if (a >= 0x11) {
                goto L_01C1BD;
            }
            a = myMapper->readCPU(0x05AC);
            if (a != 0xFF) {
                myMapper->writeCPU((0x0052 + x) & 0x00ff, myMapper->readCPU(0x058F));
                myMapper->writeCPU((0x0053 + x) & 0x00ff, myMapper->readCPU(0x0590));
                myMapper->writeCPU((0x0056 + x) & 0x00ff, myMapper->readCPU(0x0591));
                myMapper->writeCPU((0x0057 + x) & 0x00ff, myMapper->readCPU(0x0592));
                myMapper->writeCPU((0x0055 + x) & 0x00ff, 0x02);
                a = 0x00;
                myMapper->writeCPU((0x0054 + x) & 0x00ff, a);
                myMapper->writeCPU(0x008E, a);
                opDEC((0x0058 + x) & 0x00ff, 1);
                if (flgZ) {
                    a = myMapper->readCPU(0x059C);
                    setLoadFlag(a);
                    if (flgZ) {
                        pushAddress(0xC188);
                        jump(0xF155);
                        if (handleReturnAddress(poppedEntry.value, 0xC188)) return;
                        jump(0xF0E1);
                        return;
                    }
                }
                popAddress();
                return;
            }
            y = myMapper->readCPU((0x0059 + x) & 0x00ff);
            if (y != 0x07) {
                if (y == 0x0D) {
                    goto L_01C19A;
                }
                pushAddress(0xC199);
                jump(0xF0F9);
                if (handleReturnAddress(poppedEntry.value, 0xC199)) return;
            }
        L_01C19A:
            x = myMapper->readCPU(0x0051);
            opINC((0x0059 + x) & 0x00ff, 1);
            if (myMapper->readCPU((0x0059 + x) & 0x00ff) == 0x0E) {
                goto L_01C1A9;
            }
            myMapper->writeCPU((0x0062 + x) & 0x00ff, 0xFF);
            popAddress();
            return;
        L_01C1A9:
            a = 0x00;
            myMapper->writeCPU((0x0058 + x) & 0x00ff, a);
            myMapper->writeCPU(0x05AC, a);
            pushAddress(0xC1B2);
            jump(0xF847);
            if (handleReturnAddress(poppedEntry.value, 0xC1B2)) return;
            jump(0xF0E1);
            return;
        }
        a = 0xFF;
        myMapper->writeCPU((0x0062 + x) & 0x00ff, a);
    }
L_01C1BD:
    flgC = true;
    opSBC(0x11);
    y = a;
    pushAddress(0xC1C3);
    jump(0xC060);
    if (handleReturnAddress(poppedEntry.value, 0xC1C3)) return;
    a = myMapper->readCPU(0xC2DA + y);
    myMapper->writeCPU((0x0059 + x) & 0x00ff, a);
    x = a;
    a = myMapper->readCPU(0xC1EA + x);
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0013, a);
    pushAddress(0xC1D3);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xC1D3)) return;
    x = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0xC2E2 + y);
    myMapper->writeCPU((0x0062 + x) & 0x00ff, a);
    myMapper->writeCPU(0x007A, a);
    a = myMapper->readCPU(0xC2EA + y);
    myMapper->writeCPU((0x0063 + x) & 0x00ff, a);
    myMapper->writeCPU(0x007B, a);
    x = myMapper->readCPU(0xC2E2 + y);
    goto L_01C112;
}

void game::SUB_01C9F6() {
    flgC = false;
    y = 0x1D;
    a = 0x00;
    do {
        myMapper->writeCPU(0x0475 + y, a);
        myMapper->writeCPU(0x041B + y, a);
        opDEY(1);
    } while (!flgN);
    SUB_01CA04();
    return;
}

void game::SUB_01CA04() {
    x = 0x00;
    y = 0x40;
    a = 0xF4;
    do {
        myMapper->writeCPU(0x0200 + x, a);
        opINX(4);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01CA15() {
    a = 0x04;
    SUB_01CA17();
    return;
}

void game::SUB_01CA17() {
    myMapper->writeCPU(0x0028, a);
    a = myMapper->readCPU(0x05BD);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x003F);
        opAND(0x04);
        if (!flgZ) {
            goto L_01CA29;
        }
    }
    y = 0x00;
    pushAddress(0xCA28);
    jump(0xCA70);
    if (handleReturnAddress(poppedEntry.value, 0xCA28)) return;
L_01CA29:
    myMapper->writeCPU(0x0004, myMapper->readCPU(0x0587));
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        myMapper->writeCPU(0x0029, 0x01);
        do {
            y = myMapper->readCPU(0x0029);
            opINC(0x0029, 1);
            a = myMapper->readCPU(0x0475 + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_01CA44;
            }
            pushAddress(0xCA43);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0xCA43)) return;
        L_01CA44:
            opDEC(0x0004, 1);
        } while (!flgZ);
    }
    else {
        myMapper->writeCPU(0x0029, myMapper->readCPU(0x0588));
        do {
            y = myMapper->readCPU(0x0029);
            opDEC(0x0029, 1);
            a = myMapper->readCPU(0x0475 + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_01CA5C;
            }
            pushAddress(0xCA5B);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0xCA5B)) return;
        L_01CA5C:
            opDEC(0x0004, 1);
        } while (!flgZ);
    }
    x = myMapper->readCPU(0x0028);
    setLoadFlag(x);
    if (flgZ) {
        goto L_01CA6F;
    }
    a = 0xF4;
    do {
        myMapper->writeCPU(0x0200 + x, a);
        opINX(4);
    } while (!flgZ);
L_01CA6F:
    popAddress();
}

void game::SUB_01CA70() {
    flgC = true;
    a = myMapper->readCPU(0x0385 + y);
    opSBC(myMapper->readCPU(0x0583));
    myMapper->writeCPU(0x0439 + y, a);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x03A3 + y);
    opSBC(myMapper->readCPU(0x0584));
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x0457 + y, a);
    a = myMapper->readCPU(0x0457 + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01CA9F;
    }
    if (flgN) {
        if (myMapper->readCPU(0x0024) >= 0xE0) {
            goto L_01CA9F;
        }
        a = myMapper->readCPU(0x0586);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01CA9E;
        }
        a = 0x00;
        myMapper->writeCPU(0x0475 + y, a);
    }
    do {
    L_01CA9E:
        popAddress();
        return;
    L_01CA9F:
        myMapper->writeCPU(0x0026, myMapper->readCPU(0x03C1 + y));
        myMapper->writeCPU(0x0027, myMapper->readCPU(0x03DF + y));
        x = myMapper->readCPU(0x041B + y);
        myMapper->writeCPU(0x0007, myMapper->readCPU(0xC9E6 + x));
        myMapper->writeCPU(0x0008, myMapper->readCPU(0xC9EE + x));
        a = myMapper->readCPU(0x03FD + y);
    } while (a == 0xFF);
    myMapper->writeCPU(0x0002, a);
    opAND(0x7F);
    opASL_A(1);
    jump(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8));
}

void game::SUB_01D60E() {
    a = myMapper->readCPU(0x2002);
    a = myMapper->readCPU(0x0100);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0101));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0043));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0102));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0103));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0104));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0105));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0106));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0107));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0108));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0109));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x010A));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x010B));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x010C));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x010D));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x010E));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x010F));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0110));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0111));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0112));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0113));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0114));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0115));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0116));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0117));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0118));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0119));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x011A));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x011B));
    }
    a = myMapper->readCPU(0x011C);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x011D));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x011E));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x011F));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0120));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0121));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0122));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0123));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0124));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0125));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0126));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0127));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0128));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0129));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x012A));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x012B));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x012C));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x012D));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x012E));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x012F));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0130));
    }
    a = myMapper->readCPU(0x0131);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0132));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0133));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0134));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0135));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0136));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0137));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0138));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0139));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x013A));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x013B));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x013C));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x013D));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x013E));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x013F));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0140));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0141));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0142));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0143));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0144));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0145));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0146));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0147));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0148));
        a = myMapper->readCPU(0x0149);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x2006, a);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x014A));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x014B));
        }
    }
    a = myMapper->readCPU(0x014C);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x014D));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x014E));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x014F));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0150));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0151));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0152));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0153));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0154));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0155));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0156));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0157));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0158));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0159));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x015A));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x015B));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x015C));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x015D));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x015E));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x015F));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0160));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0161));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0162));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0163));
        a = myMapper->readCPU(0x0164);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x2006, a);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x0165));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x0166));
        }
    }
    a = myMapper->readCPU(0x0167);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0168));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0169));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x016A));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x016B));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x016C));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x016D));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x016E));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x016F));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0170));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0171));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0172));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0173));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0174));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0175));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0176));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0177));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0178));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0179));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x017A));
    }
    a = myMapper->readCPU(0x017B);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x017C));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x017D));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x017E));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0181));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0182));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0183));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0184));
    }
    a = myMapper->readCPU(0x0187);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0188));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0189));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x018A));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x018B));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x018C));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x018D));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x018E));
    }
    a = myMapper->readCPU(0x018F);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0190));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0191));
    }
    a = myMapper->readCPU(0x0192);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0193));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0194));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0195));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0196));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x0197));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0198));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0199));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x019A));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x019B));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x019C));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x019D));
        a = myMapper->readCPU(0x019E);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x2006, a);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x019F));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A0));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A1));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A2));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A3));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01A4));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01A5));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A6));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A7));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A8));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01A9));
        }
        a = myMapper->readCPU(0x01AA);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x2006, a);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01AB));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01AC));
        }
    }
    a = myMapper->readCPU(0x01AD);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x01AE));
        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01AF));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B0));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B1));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B2));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x01B3));
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x01B4));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B5));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B6));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B7));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01B8));
        a = myMapper->readCPU(0x01B9);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x2006, a);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01BA));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01BB));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01BC));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01BD));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01BE));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01BF));
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01C0));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01C1));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01C2));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01C3));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01C4));
        }
        a = myMapper->readCPU(0x01C5);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x2006, a);
            myMapper->writeCPU(0x2006, myMapper->readCPU(0x01C6));
            myMapper->writeCPU(0x2007, myMapper->readCPU(0x01C7));
        }
    }
    a = myMapper->readCPU(0x01C8);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, myMapper->readCPU(0x01C9));
        myMapper->writeCPU(0x2007, myMapper->readCPU(0x01CA));
    }
    a = myMapper->readCPU(0x01CB);
    setLoadFlag(a);
    if (flgN) {
        goto L_01DB36;
    }
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x01CC));
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x0043));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x01CD));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x01CE));
L_01DB36:
    popAddress();
}

void game::SUB_01DB37() {
    a = 0xFF;
    myMapper->writeCPU(0x0100, a);
    myMapper->writeCPU(0x011C, a);
    myMapper->writeCPU(0x0131, a);
    myMapper->writeCPU(0x014C, a);
    myMapper->writeCPU(0x0167, a);
    myMapper->writeCPU(0x017B, a);
    myMapper->writeCPU(0x0187, a);
    myMapper->writeCPU(0x018F, a);
    myMapper->writeCPU(0x0192, a);
    myMapper->writeCPU(0x01AD, a);
    myMapper->writeCPU(0x01C8, a);
    myMapper->writeCPU(0x0149, a);
    myMapper->writeCPU(0x0164, a);
    myMapper->writeCPU(0x01AA, a);
    myMapper->writeCPU(0x01C5, a);
    myMapper->writeCPU(0x01CB, a);
    popAddress();
}

void game::SUB_01DB6A() {
    pushAddress(0xDB6C);
    jump(0xDB89);
    if (handleReturnAddress(poppedEntry.value, 0xDB6C)) return;
    a = 0x00;
    myMapper->writeCPU(0x058C, a);
    x = a;
    y = 0xC2;
    do {
        myMapper->writeCPU(0x059D + x, a);
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    x = 0x08;
    do {
        myMapper->writeCPU((0x008D + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0658, 0x64);
    popAddress();
}

void game::SUB_01DB89() {
    if (myMapper->readCPU(0x059C) != 0) {
        goto L_01DBA3;
    }
    x = 0x00;
    a = 0x00;
    do {
        myMapper->writeCPU(0x06CA + x, a);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
    } while (!flgZ);
    y = 0x0A;
    do {
        myMapper->writeCPU(0x00F0 + y, a);
        opDEY(1);
    } while (!flgN);
L_01DBA3:
    popAddress();
}

void game::SUB_01DBA4() {
    a = x;
    opPHA();
    a = y;
    opPHA();
    pushAddress(0xDBAA);
    jump(0xEA36);
    if (handleReturnAddress(poppedEntry.value, 0xDBAA)) return;
    pushAddress(0xDBAD);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0xDBAD)) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_01DBB3() {
    a = myMapper->readCPU(0x003F);
L_01DBB5:
    if (a == myMapper->readCPU(0x003F)) {
        wait();
        goto L_01DBB5;
    }
    popAddress();
}

void game::SUB_01DBBA() {
    y = 0x01;
    myMapper->writeCPU(0x4016, y);
    opDEY(1);
    myMapper->writeCPU(0x4016, y);
    x = 0x07;
    do {
        a = myMapper->readCPU(0x4016);
        //NOP
        //NOP
        //NOP
        //NOP
        //NOP
        opLSR_A(1);
        opROL_M(0x0044, 1);
        a = myMapper->readCPU(0x4017);
        //NOP
        //NOP
        //NOP
        //NOP
        //NOP
        opLSR_A(1);
        opROL_M(0x0046, 1);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01DBE8() {
    pushAddress(0xDBEA);
    jump(0xDBBA);
    if (handleReturnAddress(poppedEntry.value, 0xDBEA)) return;
    a = 0x00;
    myMapper->writeCPU(0x0045, a);
    myMapper->writeCPU(0x0047, a);
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x0044));
    myMapper->writeCPU(0x0002, myMapper->readCPU(0x0046));
    x = 0x07;
    do {
        opASL_M(0x0001, 1);
        if (flgC) {
            opASL_M(0x0048, 1);
            if (!flgC) {
                a = myMapper->readCPU(0x0048);
                opORA(0x01);
                myMapper->writeCPU(0x0048, a);
                flgC = true;
                opROL_M(0x0045, 1);
                goto L_01DC23;
            }
            a = myMapper->readCPU(0x0048);
            opORA(0x01);
            myMapper->writeCPU(0x0048, a);
            goto L_01DC20;
        }
        opASL_M(0x0048, 1);
        a = myMapper->readCPU(0x0048);
        opAND(0xFE);
        myMapper->writeCPU(0x0048, a);
    L_01DC20:
        flgC = false;
        opROL_M(0x0045, 1);
    L_01DC23:
        opASL_M(0x0002, 1);
        if (flgC) {
            opASL_M(0x0049, 1);
            if (flgC) {
                goto L_01DC37;
            }
            a = myMapper->readCPU(0x0049);
            opORA(0x01);
            myMapper->writeCPU(0x0049, a);
            flgC = true;
            opROL_M(0x0047, 1);
            goto L_01DC4B;
        L_01DC37:
            a = myMapper->readCPU(0x0049);
            opORA(0x01);
            myMapper->writeCPU(0x0049, a);
            goto L_01DC48;
        }
        opASL_M(0x0049, 1);
        a = myMapper->readCPU(0x0049);
        opAND(0xFE);
        myMapper->writeCPU(0x0049, a);
    L_01DC48:
        flgC = false;
        opROL_M(0x0047, 1);
    L_01DC4B:
        opDEX(1);
    } while (!flgN);
    x = myMapper->readCPU(0x0046);
    y = myMapper->readCPU(0x0047);
    a = myMapper->readCPU(0x0051);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_01DC5A;
    }
    x = myMapper->readCPU(0x0044);
    y = myMapper->readCPU(0x0045);
L_01DC5A:
    myMapper->writeCPU(0x004B, x);
    myMapper->writeCPU(0x004C, y);
    y = myMapper->readCPU(0x004C);
    myMapper->writeCPU(0x00B9, y);
    popAddress();
}

void game::SUB_01DCB2() {
    myMapper->writeCPU(0x0001, y);
    myMapper->writeCPU(0x0000, x);
    a = 0x00;
    myMapper->writeCPU(0x05AD, a);
    myMapper->writeCPU(0x05AE, a);
    x = 0x07;
    do {
        opASL_A(1);
        opROL_M(0x05AE, 1);
        opASL_M(0x0000, 1);
        if (flgC) {
            flgC = false;
            opADC(myMapper->readCPU(0x0001));
            if (!flgC) {
                goto L_01DCD0;
            }
            opINC(0x05AE, 1);
        }
    L_01DCD0:
        opDEX(1);
    } while (!flgN);
    x = a;
    y = myMapper->readCPU(0x05AE);
    popAddress();
}

void game::SUB_01DCD8() {
    opROR_M(0x004D, 1);
    opROL_M(0x004E, 1);
    a = myMapper->readCPU(0x004F);
    opADC(0x2F);
    myMapper->writeCPU(0x004F, a);
    opEOR(myMapper->readCPU(0x004D));
    opSBC(myMapper->readCPU(0x004E));
    opPHA();
    opEOR(myMapper->readCPU(0x004D));
    myMapper->writeCPU(0x004D, a);
    opPLA();
    popAddress();
}

void game::SUB_01DCFD() {
    a = myMapper->readCPU(0x0040);
    myMapper->writeCPU(0x2000, a);
    pushAddress(0xDD04);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0xDD04)) return;
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x0041));
    popAddress();
}

void game::SUB_01DD0B() {
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, y);
    myMapper->writeCPU(0x2006, x);
    x = 0x04;
    do {
        y = 0x00;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x2007, a);
            opINY(1);
        } while (!flgZ);
        opINC(0x0006, 1);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01DD26() {
    do {
        opBIT(myMapper->readCPU(0x2002));
    } while (!flgN);
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    y = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(myMapper->readCPU(0x000C) + (myMapper->readCPU((0x000C + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x20);
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x000D, a);
    myMapper->writeCPU(0x000B, a);
    popAddress();
}

void game::SUB_01DD59() {
    do {
        opBIT(myMapper->readCPU(0x2002));
        if (!flgN) wait();
    } while (!flgN);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    a = 0x0F;
    y = 0x20;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    popAddress();
}

void game::SUB_01DF13() {
    myMapper->writeCPU(0x065F, x);
    y = 0x1F;
    a = 0x0F;
    do {
        myMapper->writeCPU(0x0661 + y, a);
        opDEY(1);
    } while (!flgN);
    x = 0x01;
    pushAddress(0xDF24);
    jump(0xDFAC);
    if (handleReturnAddress(poppedEntry.value, 0xDF24)) return;
    a = 0x00;
    myMapper->writeCPU(0x0001, a);
    do {
        x = 0x05;
        pushAddress(0xDF2D);
        jump(0xDFAC);
        if (handleReturnAddress(poppedEntry.value, 0xDF2D)) return;
        y = 0x1F;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            opLSR_A(4);
            opAND(0x03);
            if (a >= myMapper->readCPU(0x0001)) {
                goto L_01DF44;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x0661 + y, a);
            goto L_01DF55;
        L_01DF44:
            a = myMapper->readCPU(0x0001);
            opASL_A(4);
            myMapper->writeCPU(0x0002, a);
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            opAND(0xCF);
            opORA(myMapper->readCPU(0x0002));
            myMapper->writeCPU(0x0661 + y, a);
        L_01DF55:
            opDEY(1);
        } while (!flgN);
        opINC(0x0001, 1);
        a = myMapper->readCPU(0x0001);
    } while (a != 0x04);
    popAddress();
}

void game::SUB_01DF61() {
    myMapper->writeCPU(0x065F, x);
    a = 0x03;
    myMapper->writeCPU(0x0001, a);
    do {
        x = 0x05;
        pushAddress(0xDF6C);
        jump(0xDFAC);
        if (handleReturnAddress(poppedEntry.value, 0xDF6C)) return;
        y = 0x1F;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            opLSR_A(4);
            opAND(0x03);
            if (a >= myMapper->readCPU(0x0001)) {
                goto L_01DF83;
            }
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x0661 + y, a);
            goto L_01DF94;
        L_01DF83:
            a = myMapper->readCPU(0x0001);
            opASL_A(4);
            myMapper->writeCPU(0x0002, a);
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            opAND(0xCF);
            opORA(myMapper->readCPU(0x0002));
            myMapper->writeCPU(0x0661 + y, a);
        L_01DF94:
            opDEY(1);
        } while (!flgN);
        opDEC(0x0001, 1);
    } while (!flgN);
    x = 0x05;
    pushAddress(0xDF9F);
    jump(0xDFAC);
    if (handleReturnAddress(poppedEntry.value, 0xDF9F)) return;
    y = 0x1F;
    a = 0x0F;
    do {
        myMapper->writeCPU(0x0661 + y, a);
        opDEY(1);
    } while (!flgN);
    x = 0x05;
    SUB_01DFAC();
    return;
}

void game::SUB_01DFAC() {
    do {
        a = myMapper->readCPU(0x065F);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_01DFB8;
        }
        pushAddress(0xDFB3);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xDFB3)) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
    return;
    do {
        do {
        L_01DFB8:
            opBIT(myMapper->readCPU(0x2002));
            if (!flgV) wait();
        } while (!flgV);
        a = 0x1F;
        pushAddress(0xDFC1);
        jump(0xFFD2);
        if (handleReturnAddress(poppedEntry.value, 0xDFC1)) return;
        pushAddress(0xDFC4);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xDFC4)) return;
        a = 0x1E;
        pushAddress(0xDFC9);
        jump(0xFFD2);
        if (handleReturnAddress(poppedEntry.value, 0xDFC9)) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01DFCE() {
    if (!(myMapper->readCPU(0x0661) & 0x80)) {
        goto L_01DFD4;
    }
    popAddress();
    return;
L_01DFD4:
    a = myMapper->readCPU(0x2002);
    myMapper->writeCPU(0x2006, 0x3F);
    myMapper->writeCPU(0x2006, 0x00);
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x0042));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0661));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0662));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0663));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0664));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0665));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0666));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0667));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0668));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0669));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x066A));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x066B));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x066C));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x066D));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x066E));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x066F));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0670));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0671));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0672));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0673));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0674));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0675));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0676));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0677));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0678));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0679));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x067A));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x067B));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x067C));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x067D));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x067E));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x067F));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0680));
    myMapper->writeCPU(0x2006, 0x3F);
    a = 0x00;
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x0661, 0xFF);
    popAddress();
}

void game::SUB_01E0BC() {
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x000C) + (myMapper->readCPU((0x000C + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0661 + y, a);
        opINY(1);
    } while (y != 0x20);
    popAddress();
}

void game::SUB_01E95B() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        goto L_01E963;
    }
    do {
        flgC = false;
        popAddress();
        return;
    L_01E963:
        opDEC(0x0597, 1);
    } while (!flgZ);
    opINC(0x0598, 1);
    a = myMapper->readCPU(0x0598);
    if (a != 0x05) {
        goto L_01E977;
    }
    a = 0x01;
    myMapper->writeCPU(0x0598, a);
L_01E977:
    x = a;
    opDEX(1);
    myMapper->writeCPU(0x008C, myMapper->readCPU(0x0059));
    myMapper->writeCPU(0x0059, myMapper->readCPU(0xE992 + x));
    myMapper->writeCPU(0x008A, myMapper->readCPU(0xE996 + x));
    myMapper->writeCPU(0x008B, myMapper->readCPU(0xE99A + x));
    a = 0x03;
    myMapper->writeCPU(0x0003, a);
    flgC = true;
    popAddress();
}

void game::SUB_01E9E6() {
    x = myMapper->readCPU(0x059C);
    setLoadFlag(x);
    if (flgZ) {
        myMapper->writeCPU(0x058D, a);
        a = 0x04;
        pushAddress(0xE9F2);
        jump(0xFFE6);
        if (handleReturnAddress(poppedEntry.value, 0xE9F2)) return;
        pushAddress(0xE9F5);
        jump(0x8000);
        if (handleReturnAddress(poppedEntry.value, 0xE9F5)) return;
        pushAddress(0xE9F8);
        jump(0xDB89);
        if (handleReturnAddress(poppedEntry.value, 0xE9F8)) return;
        x = myMapper->readCPU(0x0088);
        setLoadFlag(x);
        if (flgZ) {
            goto L_01EA03;
        }
        a = myMapper->readCPU(0x058D);
        pushAddress(0xEA02);
        jump(0x8003);
        if (handleReturnAddress(poppedEntry.value, 0xEA02)) return;
    }
L_01EA03:
    jump(0xEA3E);
    return;
}

void game::SUB_01EA06() {
    x = myMapper->readCPU(0x059C);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_01EA13;
    }
    a = 0x04;
    pushAddress(0xEA0F);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xEA0F)) return;
    pushAddress(0xEA12);
    jump(0x8000);
    if (handleReturnAddress(poppedEntry.value, 0xEA12)) return;
L_01EA13:
    jump(0xEA3E);
    return;
}

void game::SUB_01EA1B() {
    myMapper->writeCPU(0x0000, x);
    myMapper->writeCPU(0x0001, y);
    myMapper->writeCPU(0x00FD, a);
    if (myMapper->readCPU(0x0089) == 0) {
        goto L_01EA2F;
    }
    x = a;
    a = 0x04;
    pushAddress(0xEA2A);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xEA2A)) return;
    a = x;
    pushAddress(0xEA2E);
    jump(0x800F);
    if (handleReturnAddress(poppedEntry.value, 0xEA2E)) return;
L_01EA2F:
    x = myMapper->readCPU(0x0000);
    y = myMapper->readCPU(0x0001);
    jump(0xEA3E);
    return;
}

void game::SUB_01EA36() {
    a = 0x04;
    pushAddress(0xEA3A);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xEA3A)) return;
    pushAddress(0xEA3D);
    jump(0x800C);
    if (handleReturnAddress(poppedEntry.value, 0xEA3D)) return;
    SUB_01EA3E();
    return;
}

void game::SUB_01EA3E() {
    a = myMapper->readCPU(0x0012);
    jump(0xFFE6);
    return;
}

void game::SUB_01EA4F() {
    a = 0x09;
    pushAddress(0xEA53);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xEA53)) return;
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x80;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xEA62);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xEA62)) return;
    a = 0x1B;
    pushAddress(0xEA67);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xEA67)) return;
    pushAddress(0xEA6A);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xEA6A)) return;
    pushAddress(0xEA6D);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xEA6D)) return;
    pushAddress(0xEA70);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xEA70)) return;
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xEA7D);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xEA7D)) return;
    x = 0x04;
    do {
        y = 0x3C;
        do {
            pushAddress(0xEA84);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xEA84)) return;
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_01EA98() {
    a = 0x00;
    pushAddress(0xEA9C);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xEA9C)) return;
    myMapper->writeCPU(0x059C, 0x00);
    myMapper->writeCPU(0x0005, 0x11);
    a = 0x84;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xEAB0);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xEAB0)) return;
    pushAddress(0xEAB3);
    jump(0xEB66);
    if (handleReturnAddress(poppedEntry.value, 0xEAB3)) return;
    a = 0x1E;
    pushAddress(0xEAB8);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xEAB8)) return;
    a = 0x1D;
    pushAddress(0xEABD);
    jump(0xFFAA);
    if (handleReturnAddress(poppedEntry.value, 0xEABD)) return;
    pushAddress(0xEAC0);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xEAC0)) return;
    myMapper->writeCPU(0x0203, 0x10);
    myMapper->writeCPU(0x0200, 0x70);
    myMapper->writeCPU(0x0201, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x0202, a);
    pushAddress(0xEAD7);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xEAD7)) return;
    pushAddress(0xEADA);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xEADA)) return;
    pushAddress(0xEADD);
    jump(0xEE99);
    if (handleReturnAddress(poppedEntry.value, 0xEADD)) return;
    pushAddress(0xEAE0);
    jump(0xDBA4);
    if (handleReturnAddress(poppedEntry.value, 0xEAE0)) return;
    pushAddress(0xEAE3);
    jump(0xEE99);
    if (handleReturnAddress(poppedEntry.value, 0xEAE3)) return;
    pushAddress(0xEAE6);
    jump(0xDBA4);
    if (handleReturnAddress(poppedEntry.value, 0xEAE6)) return;
    pushAddress(0xEAE9);
    jump(0xEE99);
    if (handleReturnAddress(poppedEntry.value, 0xEAE9)) return;
    pushAddress(0xEAEC);
    jump(0xDBA4);
    if (handleReturnAddress(poppedEntry.value, 0xEAEC)) return;
    myMapper->writeCPU(0x0005, 0x31);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x01;
    pushAddress(0xEAF9);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xEAF9)) return;
    while (true) {
        pushAddress(0xEAFC);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xEAFC)) return;
        a = myMapper->readCPU(0x008D);
        myMapper->writeCPU(0x2000, a);
        pushAddress(0xEB04);
        jump(0xEDE5);
        if (handleReturnAddress(poppedEntry.value, 0xEB04)) return;
        pushAddress(0xEB07);
        jump(0xEB90);
        if (handleReturnAddress(poppedEntry.value, 0xEB07)) return;
        pushAddress(0xEB0A);
        jump(0xEFCD);
        if (handleReturnAddress(poppedEntry.value, 0xEB0A)) return;
        a = myMapper->readCPU(0x0044);
        opAND(0x09);
        if (a == 0x09) {
            if (myMapper->readCPU(0x0046) != 0x06) {
                goto L_01EB35;
            }
            a = myMapper->readCPU(0x0045);
            x = 0x00;
            if (a != 0x80) {
                if (a != 0x40) {
                    goto L_01EB35;
                }
                x = myMapper->readCPU(0x0059);
                opINX(1);
                if (x < 0x0E) {
                    goto L_01EB2E;
                }
                x = 0x00;
            }
        L_01EB2E:
            myMapper->writeCPU(0x0059, x);
            a = 0x02;
            pushAddress(0xEB34);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0xEB34)) return;
        }
        do {
        L_01EB35:
            a = myMapper->readCPU(0x2002);
            opAND(0x40);
        } while (flgZ);
        a = 0x1F;
        pushAddress(0xEB40);
        jump(0xFFD2);
        if (handleReturnAddress(poppedEntry.value, 0xEB40)) return;
        pushAddress(0xEB43);
        jump(0xE95B);
        if (handleReturnAddress(poppedEntry.value, 0xEB43)) return;
        if (flgC) {
            goto L_01EB59;
        }
        pushAddress(0xEB48);
        jump(0xEE3E);
        if (handleReturnAddress(poppedEntry.value, 0xEB48)) return;
        if (flgC) {
            goto L_01EB59;
        }
        pushAddress(0xEB4D);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xEB4D)) return;
        a = 0x1E;
        pushAddress(0xEB52);
        jump(0xFFD2);
        if (handleReturnAddress(poppedEntry.value, 0xEB52)) return;
        pushAddress(0xEB55);
        jump(0xEE99);
        if (handleReturnAddress(poppedEntry.value, 0xEB55)) return;
    }
L_01EB59:
    myMapper->writeCPU(0x0005, 0x31);
    a = 0x98;
    myMapper->writeCPU(0x0006, a);
    x = 0x01;
    jump(0xDF61);
    return;
}

void game::SUB_01EB66() {
    a = 0x00;
    myMapper->writeCPU(0x0479, a);
    myMapper->writeCPU(0x0476, a);
    myMapper->writeCPU(0x0477, a);
    myMapper->writeCPU(0x0478, a);
    myMapper->writeCPU(0x0409, a);
    myMapper->writeCPU(0x03FD, a);
    myMapper->writeCPU(0x0533, a);
    myMapper->writeCPU(0x0534, a);
    myMapper->writeCPU(0x008E, a);
    myMapper->writeCPU(0x052D, 0x02);
    myMapper->writeCPU(0x0003, myMapper->readCPU(0x0050));
    myMapper->writeCPU(0x0050, 0x01);
    popAddress();
}

void game::SUB_01EB90() {
    a = myMapper->readCPU(0x0479);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0xEB97);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0xEB97)) return;
        opAND(0x07);
        if (flgZ) {
            myMapper->writeCPU(0x0479, 0x01);
            a = 0x00;
            pushAddress(0xEBA5);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0xEBA5)) return;
            myMapper->writeCPU(0x052D, 0x00);
            x = myMapper->readCPU(0x0409);
            if (myMapper->readCPU(0x0476 + x) == 0) {
                myMapper->writeCPU(0x0476 + x, 0x01);
                myMapper->writeCPU(0x052A + x, 0x00);
                myMapper->writeCPU(0x0386 + x, 0x78);
                myMapper->writeCPU(0x03C2 + x, 0x70);
                opINC(0x0409, 1);
                if (myMapper->readCPU(0x0409) == 0x03) {
                    myMapper->writeCPU(0x0409, 0x00);
                }
            }
        }
    }
    x = 0xA0;
    y = 0x50;
    a = myMapper->readCPU(0x052D);
    pushAddress(0xEBDF);
    jump(0xED03);
    if (handleReturnAddress(poppedEntry.value, 0xEBDF)) return;
    if (myMapper->readCPU(0x0479) != 0) {
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            opINC(0x052D, 1);
            if (myMapper->readCPU(0x052D) != 0x02) {
                goto L_01EBFA;
            }
            myMapper->writeCPU(0x0479, 0x00);
        }
    }
L_01EBFA:
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0476 + x);
        setLoadFlag(a);
        if (!flgZ) {
            y = myMapper->readCPU(0x052A + x);
            a = myMapper->readCPU(0x0386 + x);
            flgC = false;
            opADC(myMapper->readCPU(0xEC49 + y));
            myMapper->writeCPU(0x0386 + x, a);
            a = myMapper->readCPU(0xEC67 + y);
            if (a != 0x9C) {
                goto L_01EC22;
            }
            myMapper->writeCPU(0x0476 + x, 0x00);
            a = 0xF0;
            myMapper->writeCPU(0x03C2 + x, a);
            goto L_01EC29;
        L_01EC22:
            flgC = false;
            opADC(myMapper->readCPU(0x03C2 + x));
            myMapper->writeCPU(0x03C2 + x, a);
        L_01EC29:
            a = x;
            opPHA();
            myMapper->writeCPU(0x0002, myMapper->readCPU(0xEC7E + x));
            y = myMapper->readCPU(0x03C2 + x);
            x = myMapper->readCPU(0x0386 + x);
            a = myMapper->readCPU(0x003F);
            opAND(0x03);
            pushAddress(0xEC3D);
            jump(0xEC81);
            if (handleReturnAddress(poppedEntry.value, 0xEC3D)) return;
            opPLA();
            x = a;
            opINC(0x052A + x, 1);
        }
        opINX(1);
        opCMP(x, 0x03);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01EC81() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0004, x);
    myMapper->writeCPU(0x03CD, y);
    opASL_A(2);
    x = a;
    myMapper->writeCPU(0x0480, 0x02);
    y = myMapper->readCPU(0x0002);
    myMapper->writeCPU(0x0481, 0x00);
    do {
        a = myMapper->readCPU(0xECE3 + x);
        setLoadFlag(a);
        if (!flgZ) {
            myMapper->writeCPU(0x0201 + y, a);
            myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
            myMapper->writeCPU(0x0202 + y, 0x02);
            a = y;
            flgC = false;
            opADC(0x04);
            y = a;
        }
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opDEC(0x0480, 1);
        if (!flgZ) {
            goto L_01ECD7;
        }
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0004));
        myMapper->writeCPU(0x0480, 0x02);
        a = myMapper->readCPU(0x03CD);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_01ECD7:
        opINX(1);
        opINC(0x0481, 1);
        a = myMapper->readCPU(0x0481);
    } while (a != 0x04);
    popAddress();
}

void game::SUB_01ED03() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0004, x);
    myMapper->writeCPU(0x03CD, y);
    y = a;
    x = 0x24;
    pushAddress(0xED10);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xED10)) return;
    myMapper->writeCPU(0x0480, 0x06);
    y = 0x50;
    myMapper->writeCPU(0x0481, 0x00);
    do {
        a = myMapper->readCPU(0xED79 + x);
        setLoadFlag(a);
        if (!flgZ) {
            myMapper->writeCPU(0x0201 + y, a);
            myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
            myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
            myMapper->writeCPU(0x0202 + y, 0x02);
            a = y;
            flgC = false;
            opADC(0x04);
            y = a;
        }
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opDEC(0x0480, 1);
        if (!flgZ) {
            goto L_01ED5C;
        }
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0004));
        myMapper->writeCPU(0x0480, 0x06);
        a = myMapper->readCPU(0x03CD);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_01ED5C:
        opINX(1);
        opINC(0x0481, 1);
    } while (myMapper->readCPU(0x0481) != 0x24);
    while (y != 0xE4) {
        myMapper->writeCPU(0x0200 + y, 0xF0);
        a = y;
        flgC = false;
        opADC(0x04);
        y = a;
    }
    popAddress();
}

void game::SUB_01EDE5() {
    a = myMapper->readCPU(0x003F);
    opAND(0x07);
    if (flgZ) {
        opINC(0x03FD, 1);
        a = myMapper->readCPU(0x03FD);
        opAND(0x03);
        myMapper->writeCPU(0x03FD, a);
    }
    a = myMapper->readCPU(0x0045);
    setLoadFlag(a);
    //NOP
    //NOP
    if (!flgZ) {
        x = 0x00;
        myMapper->writeCPU(0x0597, x);
    }
    opAND(0x04);
    if (!flgZ) {
        a = 0x01;
        pushAddress(0xEE09);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xEE09)) return;
        opINC(0x0003, 1);
        if (myMapper->readCPU(0x0003) == 0x06) {
            myMapper->writeCPU(0x0003, 0x00);
        }
    }
    a = myMapper->readCPU(0x0045);
    //NOP
    //NOP
    opAND(0x08);
    if (!flgZ) {
        a = 0x01;
        pushAddress(0xEE22);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xEE22)) return;
        opDEC(0x0003, 1);
        if (!flgN) {
            goto L_01EE2B;
        }
        myMapper->writeCPU(0x0003, 0x05);
    }
L_01EE2B:
    a = myMapper->readCPU(0x0003);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0385, myMapper->readCPU(0xEE8D + x));
    a = myMapper->readCPU(0xEE8E + x);
    myMapper->writeCPU(0x03C1, a);
    jump(0xEF3D);
    return;
}

void game::SUB_01EE3E() {
    a = myMapper->readCPU(0x0045);
    //NOP
    //NOP
    opAND(0x10);
    if (!flgZ) {
        a = 0x02;
        pushAddress(0xEE4A);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xEE4A)) return;
        a = myMapper->readCPU(0x0003);
        if (a != 0x00) {
            if (a == 0x01) {
                goto L_01EE68;
            }
            if (a != 0x02) {
                if (a == 0x03) {
                    goto L_01EE6A;
                }
                if (a == 0x04) {
                    goto L_01EE74;
                }
                if (a != 0x05) {
                    goto L_01EE68;
                }
                goto L_01EE83;
            }
        }
    L_01EE68:
        flgC = true;
        popAddress();
        return;
    L_01EE6A:
        a = myMapper->readCPU(0x0087);
        opEOR(0xFF);
        opAND(0x01);
        myMapper->writeCPU(0x0087, a);
    }
    flgC = false;
    popAddress();
    return;
L_01EE74:
    a = myMapper->readCPU(0x0088);
    opEOR(0xFF);
    opAND(0x01);
    myMapper->writeCPU(0x0088, a);
    a = 0x00;
    pushAddress(0xEE80);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xEE80)) return;
    flgC = false;
    popAddress();
    return;
L_01EE83:
    a = myMapper->readCPU(0x0089);
    opEOR(0xFF);
    opAND(0x01);
    myMapper->writeCPU(0x0089, a);
    flgC = false;
    popAddress();
}

void game::SUB_01EE99() {
    opINC(0x008E, 1);
    if (myMapper->readCPU(0x008E) != 0x03) {
        goto L_01EEA5;
    }
    myMapper->writeCPU(0x008E, 0x00);
L_01EEA5:
    a = myMapper->readCPU(0x008E);
    x = a;
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x017C, myMapper->readCPU(0xEF37 + y));
    myMapper->writeCPU(0x017B, myMapper->readCPU(0xEF38 + y));
    a = myMapper->readCPU(0xEF37 + y);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0182, a);
    a = myMapper->readCPU(0xEF38 + y);
    opADC(0x00);
    myMapper->writeCPU(0x0181, a);
    a = myMapper->readCPU(0xEF37 + y);
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x0188, a);
    a = myMapper->readCPU(0xEF38 + y);
    opADC(0x00);
    myMapper->writeCPU(0x0187, a);
    a = myMapper->readCPU(0xEF37 + y);
    flgC = false;
    opADC(0x22);
    myMapper->writeCPU(0x018C, a);
    a = myMapper->readCPU(0xEF38 + y);
    opADC(0x00);
    myMapper->writeCPU(0x018B, a);
    a = myMapper->readCPU((0x0087 + x) & 0x00ff);
    flgC = false;
    opADC(myMapper->readCPU(0xEF14 + x));
    opASL_A(3);
    x = a;
    y = 0x00;
    do {
        myMapper->writeCPU(0x017D + y, myMapper->readCPU(0xEF17 + x));
        myMapper->writeCPU(0x0183 + y, myMapper->readCPU(0xEF1B + x));
        myMapper->writeCPU(0x0189 + y, myMapper->readCPU(0xEF19 + x));
        a = myMapper->readCPU(0xEF1D + x);
        myMapper->writeCPU(0x018D + y, a);
        opINX(1);
        opINY(1);
    } while (y != 0x02);
    popAddress();
}

void game::SUB_01EF3D() {
    a = myMapper->readCPU(0x0385);
    myMapper->writeCPU(0x0207, a);
    myMapper->writeCPU(0x0213, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x020B, a);
    myMapper->writeCPU(0x0217, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x020F, a);
    myMapper->writeCPU(0x021B, a);
    a = myMapper->readCPU(0x03C1);
    myMapper->writeCPU(0x0204, a);
    myMapper->writeCPU(0x0208, a);
    myMapper->writeCPU(0x020C, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0210, a);
    myMapper->writeCPU(0x0214, a);
    myMapper->writeCPU(0x0218, a);
    y = myMapper->readCPU(0x03FD);
    x = myMapper->readCPU(0xEFAF + y);
    myMapper->writeCPU(0x0205, myMapper->readCPU(0xEFB5 + x));
    myMapper->writeCPU(0x0209, myMapper->readCPU(0xEFB6 + x));
    myMapper->writeCPU(0x020D, myMapper->readCPU(0xEFB7 + x));
    myMapper->writeCPU(0x0211, myMapper->readCPU(0xEFB8 + x));
    myMapper->writeCPU(0x0215, myMapper->readCPU(0xEFB9 + x));
    myMapper->writeCPU(0x0219, myMapper->readCPU(0xEFBA + x));
    a = 0x00;
    myMapper->writeCPU(0x0206, a);
    myMapper->writeCPU(0x020A, a);
    myMapper->writeCPU(0x020E, a);
    myMapper->writeCPU(0x0212, a);
    myMapper->writeCPU(0x0216, a);
    myMapper->writeCPU(0x021A, a);
    popAddress();
}

void game::SUB_01EFCD() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        opDEC(0x0533, 1);
        if (flgN) {
            a = 0x07;
            myMapper->writeCPU(0x0533, a);
            pushAddress(0xEFDF);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0xEFDF)) return;
            opAND(0x03);
            opASL_A(1);
            x = a;
            myMapper->writeCPU(0x038F, myMapper->readCPU(0xF0A2 + x));
            myMapper->writeCPU(0x03CB, myMapper->readCPU(0xF0A3 + x));
        }
        opDEC(0x0534, 1);
        if (!flgN) {
            goto L_01F00D;
        }
        a = 0x07;
        myMapper->writeCPU(0x0534, a);
        pushAddress(0xEFFC);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0xEFFC)) return;
        opAND(0x07);
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x0390, myMapper->readCPU(0xF0A2 + x));
        myMapper->writeCPU(0x03CC, myMapper->readCPU(0xF0A3 + x));
    }
L_01F00D:
    myMapper->writeCPU(0x047F, 0xC0);
    x = myMapper->readCPU(0x0533);
    a = myMapper->readCPU(0xF09A + x);
    x = myMapper->readCPU(0x038F);
    y = myMapper->readCPU(0x03CB);
    pushAddress(0xF020);
    jump(0xF036);
    if (handleReturnAddress(poppedEntry.value, 0xF020)) return;
    myMapper->writeCPU(0x047F, 0xD0);
    x = myMapper->readCPU(0x0534);
    a = myMapper->readCPU(0xF09A + x);
    x = myMapper->readCPU(0x0390);
    y = myMapper->readCPU(0x03CC);
    pushAddress(0xF034);
    jump(0xF036);
    if (handleReturnAddress(poppedEntry.value, 0xF034)) return;
    popAddress();
}

void game::SUB_01F036() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0001, x);
    myMapper->writeCPU(0x03CD, y);
    opASL_A(2);
    x = a;
    y = myMapper->readCPU(0x047F);
    a = 0x00;
    myMapper->writeCPU(0x0481, a);
    myMapper->writeCPU(0x0480, a);
    do {
        myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0xF0B2 + x));
        myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
        myMapper->writeCPU(0x0202 + y, 0x00);
        a = y;
        flgC = false;
        opADC(0x04);
        y = a;
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opINC(0x0480, 1);
        if (myMapper->readCPU(0x0480) != 0x02) {
            goto L_01F08E;
        }
        myMapper->writeCPU(0x0480, 0x00);
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0001));
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_01F08E:
        opINX(1);
        opINC(0x0481, 1);
    } while (myMapper->readCPU(0x0481) != 0x04);
    popAddress();
}

void game::SUB_01F0C6() {
    opPHA();
    a = myMapper->readCPU(0x0012);
    pushAddress(0xF0CB);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF0CB)) return;
    opPLA();
    popAddress();
}

void game::SUB_01F0CE() {
    opPHA();
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF0D5);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF0D5)) return;
    opPLA();
    pushAddress(0xF0D9);
    jump(0x9CF1);
    if (handleReturnAddress(poppedEntry.value, 0xF0D9)) return;
    SUB_01F0DA();
    return;
}

void game::SUB_01F0DA() {
    a = myMapper->readCPU(0x0013);
    myMapper->writeCPU(0x0012, a);
    jump(0xFFE6);
    return;
}

void game::SUB_01F0E1() {
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF0E7);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF0E7)) return;
    pushAddress(0xF0EA);
    jump(0xAE8E);
    if (handleReturnAddress(poppedEntry.value, 0xF0EA)) return;
    jump(0xF0DA);
    return;
}

void game::SUB_01F0EE() {
    a = 0x06;
    pushAddress(0xF0F2);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF0F2)) return;
    pushAddress(0xF0F5);
    jump(0xAEDD);
    if (handleReturnAddress(poppedEntry.value, 0xF0F5)) return;
    jump(0xF0C6);
    return;
}

void game::SUB_01F0F9() {
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF0FF);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF0FF)) return;
    pushAddress(0xF102);
    jump(0xB32C);
    if (handleReturnAddress(poppedEntry.value, 0xF102)) return;
    x = 0x08;
    if (myMapper->readCPU(0x0003) >= 0x3C) {
        x = 0x07;
        a = myMapper->readCPU(0x0004);
        if (a >= 0x3C) {
            jump(0xF0DA);
            return;
        }
    }
    y = myMapper->readCPU(0x0051);
    if (myMapper->readCPU(0x0064 + y) == 0x3C) {
        goto L_01F134;
    }
    a = x;
    pushAddress(0xF122);
    jump(0xF0CE);
    if (handleReturnAddress(poppedEntry.value, 0xF122)) return;
    myMapper->writeCPU(0x0660, 0x00);
    pushAddress(0xF12A);
    jump(0xF149);
    if (handleReturnAddress(poppedEntry.value, 0xF12A)) return;
    if (a == 0x00) {
        goto L_01F141;
    }
    a = 0x09;
    goto L_01F136;
L_01F134:
    a = 0x11;
L_01F136:
    pushAddress(0xF138);
    jump(0xF0CE);
    if (handleReturnAddress(poppedEntry.value, 0xF138)) return;
    x = myMapper->readCPU(0x0051);
    opDEC((0x0059 + x) & 0x00ff, 1);
    a = y;
    jump(0xF0DA);
    return;
L_01F141:
    a = 0x0E;
    pushAddress(0xF145);
    jump(0xF0CE);
    if (handleReturnAddress(poppedEntry.value, 0xF145)) return;
    jump(0xF0DA);
    return;
}

void game::SUB_01F149() {
    opPHA();
    a = 0x05;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF150);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF150)) return;
    opPLA();
    jump(0x9484);
    return;
}

void game::SUB_01F155() {
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF15B);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xF15B)) return;
    pushAddress(0xF15E);
    jump(0xB68B);
    if (handleReturnAddress(poppedEntry.value, 0xF15E)) return;
    jump(0xF0DA);
    return;
}

void game::SUB_01F162() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
    pushAddress(0xF16C);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0xF16C)) return;
    a = 0x88;
    myMapper->writeCPU(0x0040, a);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    myMapper->writeCPU(0x0041, 0x1E);
    myMapper->writeCPU(0x0661, 0xFF);
    myMapper->writeCPU(0x00FE, 0x70);
    a = 0xF2;
    myMapper->writeCPU(0x00FF, a);
    popAddress();
}

void game::SUB_01F189() {
    pushAddress(0xF18B);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xF18B)) return;
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF192);
    jump(0xF0C6);
    if (handleReturnAddress(poppedEntry.value, 0xF192)) return;
    a = 0x01;
    myMapper->writeCPU(0x0088, a);
    myMapper->writeCPU(0x0089, a);
    a = 0x00;
    myMapper->writeCPU(0x059C, a);
    myMapper->writeCPU(0x0059, a);
    myMapper->writeCPU(0x0087, a);
    a = 0x00;
    myMapper->writeCPU(0x0051, a);
    pushAddress(0xF1A8);
    jump(0xB2CD);
    if (handleReturnAddress(poppedEntry.value, 0xF1A8)) return;
    pushAddress(0xF1AB);
    jump(0xEA4F);
    if (handleReturnAddress(poppedEntry.value, 0xF1AB)) return;
    a = 0x28;
    myMapper->writeCPU(0x0064, a);
    myMapper->writeCPU(0x0078, a);
    while (true) {
        while (true) {
            while (true) {
                while (true) {
                    pushAddress(0xF1B4);
                    jump(0xF162);
                    if (handleReturnAddress(poppedEntry.value, 0xF1B4)) return;
                    a = 0x06;
                    myMapper->writeCPU(0x0012, a);
                    pushAddress(0xF1BB);
                    jump(0xF0C6);
                    if (handleReturnAddress(poppedEntry.value, 0xF1BB)) return;
                    a = 0x00;
                    myMapper->writeCPU(0x0051, a);
                    pushAddress(0xF1C2);
                    jump(0xEA98);
                    if (handleReturnAddress(poppedEntry.value, 0xF1C2)) return;
                    a = myMapper->readCPU(0x0003);
                    setLoadFlag(a);
                    if (flgZ) {
                        goto L_01F1F2;
                    }
                    if (a == 0x01) {
                        goto L_01F20A;
                    }
                    if (a == 0x03) {
                        goto L_01F1D5;
                    }
                    pushAddress(0xF1D1);
                    jump(0xF0EE);
                    if (handleReturnAddress(poppedEntry.value, 0xF1D1)) return;
                }
            L_01F1D5:
                pushAddress(0xF21A);
                jump(0xF23A);
                if (handleReturnAddress(poppedEntry.value, 0xF21A)) return;
                x = 0x01;
                myMapper->writeCPU(0x0058, x);
                myMapper->writeCPU(0x059C, x);
                myMapper->writeCPU(0x059A, x);
                opDEX(1);
                myMapper->writeCPU(0x059B, x);
                myMapper->writeCPU(0x006C, x);
                pushAddress(0xF1EA);
                jump(0xC052);
                if (handleReturnAddress(poppedEntry.value, 0xF1EA)) return;
                a = myMapper->readCPU(0x008C);
                myMapper->writeCPU(0x0059, a);
            }
        L_01F1F2:
            pushAddress(0xF1D7);
            jump(0xF23A);
            if (handleReturnAddress(poppedEntry.value, 0xF1D7)) return;
            a = 0x28;
            myMapper->writeCPU(0x0064, a);
            myMapper->writeCPU(0x0078, a);
            a = 0x00;
            myMapper->writeCPU(0x0598, a);
            myMapper->writeCPU(0x0059, a);
            myMapper->writeCPU(0x006D, a);
            pushAddress(0xF206);
            jump(0xC052);
            if (handleReturnAddress(poppedEntry.value, 0xF206)) return;
        }
    L_01F20A:
        pushAddress(0xF20C);
        jump(0xF23A);
        if (handleReturnAddress(poppedEntry.value, 0xF20C)) return;
        a = 0x00;
        myMapper->writeCPU(0x0598, a);
        pushAddress(0xF214);
        jump(0xC052);
        if (handleReturnAddress(poppedEntry.value, 0xF214)) return;
    }
    SUB_01F218();
    return;
}

void game::SUB_01F218() {
    a = myMapper->readCPU(0x0040);
    myMapper->writeCPU(0x008D, a);
    myMapper->writeCPU(0x2000, a);
    pushAddress(0xF221);
    jump(0xDBA4);
    if (handleReturnAddress(poppedEntry.value, 0xF221)) return;
    a = myMapper->readCPU(0x0041);
    myMapper->writeCPU(0x2001, a);
    popAddress();
}

void game::SUB_01F23A() {
    a = 0x02;
    myMapper->writeCPU(0x0055, a);
    myMapper->writeCPU(0x0069, a);
    a = 0x00;
    myMapper->writeCPU(0x0054, a);
    myMapper->writeCPU(0x0068, a);
    x = 0x04;
    myMapper->writeCPU(0x0058, x);
    if (myMapper->readCPU(0x0087) == 0) {
        goto L_01F250;
    }
    myMapper->writeCPU(0x006C, x);
L_01F250:
    a = 0x00;
    myMapper->writeCPU(0x0056, a);
    myMapper->writeCPU(0x0057, a);
    myMapper->writeCPU(0x006A, a);
    myMapper->writeCPU(0x006B, a);
    myMapper->writeCPU(0x0052, a);
    myMapper->writeCPU(0x0053, a);
    myMapper->writeCPU(0x0066, a);
    myMapper->writeCPU(0x0067, a);
    myMapper->writeCPU(0x0065, a);
    myMapper->writeCPU(0x0079, a);
    x = 0x07;
    do {
        myMapper->writeCPU((0x005A + x) & 0x00ff, a);
        myMapper->writeCPU((0x006E + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01F270() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x2002);
    a = 0x02;
    myMapper->writeCPU(0x4014, a);
    pushAddress(0xF27F);
    jump(0xDFCE);
    if (handleReturnAddress(poppedEntry.value, 0xF27F)) return;
    a = myMapper->readCPU(0x0040);
    myMapper->writeCPU(0x2000, a);
    pushAddress(0xF287);
    jump(0xD60E);
    if (handleReturnAddress(poppedEntry.value, 0xF287)) return;
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    do {
        opBIT(myMapper->readCPU(0x2002));
    } while (flgV);
    opINC(0x003F, 1);
    pushAddress(0xF299);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0xF299)) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    return;
}

void game::SUB_01F2A0() {
    a = myMapper->readCPU(0x059C);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0087);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_01F2AA;
        }
    }
    do {
        popAddress();
        return;
    L_01F2AA:
        a = myMapper->readCPU((0x0058 + x) & 0x00ff);
        setLoadFlag(a);
    } while (flgZ);
    pushAddress(0xF2B0);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xF2B0)) return;
    pushAddress(0xF2B3);
    jump(0xEA06);
    if (handleReturnAddress(poppedEntry.value, 0xF2B3)) return;
    a = 0x02;
    pushAddress(0xF2B8);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xF2B8)) return;
    myMapper->writeCPU(0x0005, 0x02);
    a = 0xF4;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xF2C7);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xF2C7)) return;
    a = myMapper->readCPU(0x0051);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01F30B;
    }
    a = 0x22;
    myMapper->writeCPU(0x0192, a);
    myMapper->writeCPU(0x0198, a);
    myMapper->writeCPU(0x019E, a);
    myMapper->writeCPU(0x01A4, a);
    myMapper->writeCPU(0x0193, 0x99);
    myMapper->writeCPU(0x0199, 0xB9);
    myMapper->writeCPU(0x019F, 0xD9);
    myMapper->writeCPU(0x01A5, 0xF9);
    x = 0x03;
    do {
        myMapper->writeCPU(0x0194 + x, myMapper->readCPU(0xF346 + x));
        myMapper->writeCPU(0x019A + x, myMapper->readCPU(0xF34A + x));
        myMapper->writeCPU(0x01A0 + x, myMapper->readCPU(0xF34E + x));
        a = myMapper->readCPU(0xF352 + x);
        myMapper->writeCPU(0x01A6 + x, a);
        opDEX(1);
    } while (!flgN);
L_01F30B:
    pushAddress(0xF30D);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0xF30D)) return;
    pushAddress(0xF310);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xF310)) return;
    pushAddress(0xF313);
    jump(0xDCFD);
    if (handleReturnAddress(poppedEntry.value, 0xF313)) return;
    a = myMapper->readCPU(0x0041);
    opORA(0x02);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0005, 0x02);
    a = 0xF8;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xF327);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xF327)) return;
    do {
        pushAddress(0xF32A);
        jump(0xDBB3);
        if (handleReturnAddress(poppedEntry.value, 0xF32A)) return;
        pushAddress(0xF32D);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xF32D)) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x10);
    } while (flgZ);
    a = 0x02;
    pushAddress(0xF338);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xF338)) return;
    myMapper->writeCPU(0x0005, 0x02);
    a = 0xF8;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_01F356() {
    a = myMapper->readCPU(0x0385);
    myMapper->writeCPU(0x0391, a);
    myMapper->writeCPU(0x0001, a);
    myMapper->writeCPU(0x03CD, myMapper->readCPU(0x03C1));
    a = myMapper->readCPU(0x03FD);
    opASL_A(4);
    x = a;
    y = 0x00;
    myMapper->writeCPU(0x0481, y);
    myMapper->writeCPU(0x0480, y);
    do {
        myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0xF3C2 + x));
        myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0391));
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x03CD));
        myMapper->writeCPU(0x0202 + y, 0x00);
        a = y;
        flgC = false;
        opADC(0x04);
        y = a;
        flgC = false;
        a = myMapper->readCPU(0x0391);
        opADC(0x08);
        myMapper->writeCPU(0x0391, a);
        opINC(0x0480, 1);
        if (myMapper->readCPU(0x0480) != 0x04) {
            goto L_01F3B6;
        }
        myMapper->writeCPU(0x0480, 0x00);
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0001));
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_01F3B6:
        opINX(1);
        opINC(0x0481, 1);
        a = myMapper->readCPU(0x0481);
    } while (a != 0x10);
    popAddress();
}

void game::SUB_01F847() {
    pushAddress(0xF849);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xF849)) return;
    pushAddress(0xF84C);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xF84C)) return;
    pushAddress(0xF84F);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xF84F)) return;
    a = 0x07;
    pushAddress(0xF854);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xF854)) return;
    a = 0x03;
    pushAddress(0xF859);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xF859)) return;
    myMapper->writeCPU(0x0005, 0xAB);
    a = 0xF8;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xF868);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xF868)) return;
    pushAddress(0xF86B);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xF86B)) return;
    a = myMapper->readCPU(0x0041);
    opORA(0x02);
    myMapper->writeCPU(0x2001, a);
    myMapper->writeCPU(0x0005, 0xAB);
    myMapper->writeCPU(0x0006, 0xFC);
    x = myMapper->readCPU(0x0051);
    a = 0x00;
    myMapper->writeCPU((0x0059 + x) & 0x00ff, a);
    pushAddress(0xF883);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xF883)) return;
    do {
        pushAddress(0xF886);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xF886)) return;
        pushAddress(0xF889);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xF889)) return;
        a = myMapper->readCPU(0x004C);
        opAND(0x10);
    } while (flgZ);
    myMapper->writeCPU(0x0005, 0xAB);
    a = 0xFC;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_01F89D() {
    x = myMapper->readCPU(0x0051);
    do {
        a = myMapper->readCPU((0x0058 + x) & 0x00ff);
        if (a == 0x05) {
            goto L_01F8AA;
        }
        opINC((0x0058 + x) & 0x00ff, 1);
        opDEY(1);
    } while (!flgZ);
L_01F8AA:
    popAddress();
}

void game::nmi() {
    jump(myMapper->readCPU(0x00FE) + (myMapper->readCPU((0x00FE + 1) & 0x00ff) << 8));
}

void game::SUB_01FEB2() {
    do {
        x = 0x16;
        do {
            a = myMapper->readCPU(0xFEC2 + x);
            flgC = false;
            opADC(myMapper->readCPU((0x0010 + x) & 0x00ff));
            if (!flgZ) {
                goto L_01FEC1;
            }
            opDEX(1);
        } while (!flgN);
    } while (flgN);
L_01FEC1:
    popAddress();
}

void game::reset() {
    flgI = true;
    x = 0x00;
    myMapper->writeCPU(0x2000, x);
    myMapper->writeCPU(0x2001, x);
    myMapper->writeCPU(0x2003, x);
    myMapper->writeCPU(0x2003, x);
    opDEX(1);
    s = x;
    flgD = false;
    x = 0x02;
    //do {
    //    do {
    //        opBIT(myMapper->readCPU(0x2002));
    //    } while (!flgN);
    //    do {
    //        opBIT(myMapper->readCPU(0x2002));
    //    } while (flgN);
    //    opDEX(1);
    //} while (!flgZ);
    pushAddress(0xFF87);
    jump(0xFF99);
    if (handleReturnAddress(poppedEntry.value, 0xFF87)) return;
    opINC(0xFF88, 1);
    pushAddress(0xFF8D);
    jump(0xFF99);
    if (handleReturnAddress(poppedEntry.value, 0xFF8D)) return;
    myMapper->writeCPU(0x4017, 0x80);
    a = myMapper->readCPU(0x4015);
    jump(0xC000);
    return;
}

void game::SUB_01FF99() {
    a = 0x1E;
    pushAddress(0xFF9D);
    jump(0xFFBE);
    if (handleReturnAddress(poppedEntry.value, 0xFF9D)) return;
    a = 0x00;
    pushAddress(0xFFA2);
    jump(0xFFE6);
    if (handleReturnAddress(poppedEntry.value, 0xFFA2)) return;
    a = 0x00;
    pushAddress(0xFFA7);
    jump(0xFFD2);
    if (handleReturnAddress(poppedEntry.value, 0xFFA7)) return;
    a = 0x01;
    SUB_01FFAA();
    return;
}

void game::SUB_01FFAA() {
    myMapper->writeCPU(0xDFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xDFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xDFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xDFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xDFFF, a);
    popAddress();
}

void game::SUB_01FFBE() {
    myMapper->writeCPU(0x9FFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0x9FFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0x9FFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0x9FFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0x9FFF, a);
    popAddress();
}

void game::SUB_01FFD2() {
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    popAddress();
}

void game::SUB_01FFE6() {
    myMapper->writeCPU(0xFFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xFFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xFFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xFFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xFFFF, a);
    popAddress();
}

void game::jump(Uint16 target) {
    Uint32 tAddress = myMapper->readRealAddress(target);
    switch (tAddress) {
    case 0x010012:
        SUB_010012();
        break;
    case 0x0100A6:
        SUB_0100A6();
        break;
    case 0x01011A:
        SUB_01011A();
        break;
    case 0x010031:
        SUB_010031();
        break;
    case 0x0105BB:
        SUB_0105BB();
        break;
    case 0x01030A:
        SUB_01030A();
        break;
    case 0x01025D:
        SUB_01025D();
        break;
    case 0x010209:
        SUB_010209();
        break;
    case 0x01055B:
        SUB_01055B();
        break;
    case 0x010507:
        SUB_010507();
        break;
    case 0x0103A6:
        SUB_0103A6();
        break;
    case 0x010279:
        SUB_010279();
        break;
    case 0x010425:
        SUB_010425();
        break;
    case 0x01032B:
        SUB_01032B();
        break;
    case 0x0103A5:
        SUB_0103A5();
        break;
    case 0x0103E9:
        SUB_0103E9();
        break;
    case 0x0103F5:
        SUB_0103F5();
        break;
    case 0x010448:
        SUB_010448();
        break;
    case 0x01F162:
        SUB_01F162();
        break;
    case 0x01C9F6:
        SUB_01C9F6();
        break;
    case 0x01DD59:
        SUB_01DD59();
        break;
    case 0x01E9E6:
        SUB_01E9E6();
        break;
    case 0x01DD0B:
        SUB_01DD0B();
        break;
    case 0x01FFD2:
        SUB_01FFD2();
        break;
    case 0x01FFAA:
        SUB_01FFAA();
        break;
    case 0x01DD26:
        SUB_01DD26();
        break;
    case 0x0154D4:
        SUB_0154D4();
        break;
    case 0x01F218:
        SUB_01F218();
        break;
    case 0x0155C5:
        SUB_0155C5();
        break;
    case 0x01DCD8:
        SUB_01DCD8();
        break;
    case 0x01EA1B:
        SUB_01EA1B();
        break;
    case 0x01EA06:
        SUB_01EA06();
        break;
    case 0x01DBB3:
        SUB_01DBB3();
        break;
    case 0x0159A8:
        SUB_0159A8();
        break;
    case 0x01EA36:
        SUB_01EA36();
        break;
    case 0x01DBE8:
        SUB_01DBE8();
        break;
    case 0x015D96:
        SUB_015D96();
        break;
    case 0x0155A0:
        SUB_0155A0();
        break;
    case 0x015815:
        SUB_015815();
        break;
    case 0x0158F7:
        SUB_0158F7();
        break;
    case 0x015646:
        SUB_015646();
        break;
    case 0x015D0C:
        SUB_015D0C();
        break;
    case 0x015A6D:
        SUB_015A6D();
        break;
    case 0x015B26:
        SUB_015B26();
        break;
    case 0x015B4D:
        SUB_015B4D();
        break;
    case 0x015C95:
        SUB_015C95();
        break;
    case 0x01597D:
        SUB_01597D();
        break;
    case 0x01CA17:
        SUB_01CA17();
        break;
    case 0x0156CD:
        SUB_0156CD();
        break;
    case 0x015748:
        SUB_015748();
        break;
    case 0x0157DD:
        SUB_0157DD();
        break;
    case 0x0159C2:
        SUB_0159C2();
        break;
    case 0x01DCB2:
        SUB_01DCB2();
        break;
    case 0x0157FA:
        SUB_0157FA();
        break;
    case 0x0157CA:
        SUB_0157CA();
        break;
    case 0x0157B7:
        SUB_0157B7();
        break;
    case 0x01577D:
        SUB_01577D();
        break;
    case 0x01E0BC:
        SUB_01E0BC();
        break;
    case 0x015E1C:
        SUB_015E1C();
        break;
    case 0x01BAFC:
        SUB_01BAFC();
        break;
    case 0x01CA04:
        SUB_01CA04();
        break;
    case 0x019D50:
        SUB_019D50();
        break;
    case 0x01DF13:
        SUB_01DF13();
        break;
    case 0x019D79:
        SUB_019D79();
        break;
    case 0x019D59:
        SUB_019D59();
        break;
    case 0x01A073:
        SUB_01A073();
        break;
    case 0x019EF3:
        SUB_019EF3();
        break;
    case 0x019D98:
        SUB_019D98();
        break;
    case 0x01DF61:
        SUB_01DF61();
        break;
    case 0x019F13:
        SUB_019F13();
        break;
    case 0x01DBA4:
        SUB_01DBA4();
        break;
    case 0x019DBA:
        SUB_019DBA();
        break;
    case 0x019E2D:
        SUB_019E2D();
        break;
    case 0x01AF22:
        SUB_01AF22();
        break;
    case 0x01AEE3:
        SUB_01AEE3();
        break;
    case 0x01B005:
        SUB_01B005();
        break;
    case 0x01AEB1:
        SUB_01AEB1();
        break;
    case 0x01B172:
        SUB_01B172();
        break;
    case 0x01B031:
        SUB_01B031();
        break;
    case 0x01B119:
        SUB_01B119();
        break;
    case 0x01B0E4:
        SUB_01B0E4();
        break;
    case 0x01B263:
        SUB_01B263();
        break;
    case 0x01B1AC:
        SUB_01B1AC();
        break;
    case 0x01B1C2:
        SUB_01B1C2();
        break;
    case 0x01B1F6:
        SUB_01B1F6();
        break;
    case 0x01B3C1:
        SUB_01B3C1();
        break;
    case 0x01B425:
        SUB_01B425();
        break;
    case 0x01B408:
        SUB_01B408();
        break;
    case 0x01B5A3:
        SUB_01B5A3();
        break;
    case 0x01B53A:
        SUB_01B53A();
        break;
    case 0x01B70F:
        SUB_01B70F();
        break;
    case 0x01B7F4:
        SUB_01B7F4();
        break;
    case 0x01CA15:
        SUB_01CA15();
        break;
    case 0x01F0CE:
        SUB_01F0CE();
        break;
    case 0x01BB88:
        SUB_01BB88();
        break;
    case 0x01BBDD:
        SUB_01BBDD();
        break;
    case 0x01F356:
        SUB_01F356();
        break;
    case 0x01BCF5:
        SUB_01BCF5();
        break;
    case 0x01BCA5:
        SUB_01BCA5();
        break;
    case 0x01BD5C:
        SUB_01BD5C();
        break;
    case 0x01BD2E:
        SUB_01BD2E();
        break;
    case 0x01F89D:
        SUB_01F89D();
        break;
    case 0x01BC6F:
        SUB_01BC6F();
        break;
    case 0x01BE18:
        SUB_01BE18();
        break;
    case 0x01BD9A:
        SUB_01BD9A();
        break;
    case 0x01FEB2:
        SUB_01FEB2();
        break;
    case 0x01F189:
        SUB_01F189();
        break;
    case 0x01DB37:
        SUB_01DB37();
        break;
    case 0x01C030:
        SUB_01C030();
        break;
    case 0x01C075:
        SUB_01C075();
        break;
    case 0x01F2A0:
        SUB_01F2A0();
        break;
    case 0x01C0B6:
        SUB_01C0B6();
        break;
    case 0x01C060:
        SUB_01C060();
        break;
    case 0x01FFE6:
        SUB_01FFE6();
        break;
    case 0x01DB6A:
        SUB_01DB6A();
        break;
    case 0x018000:
        SUB_018000();
        break;
    case 0x01F155:
        SUB_01F155();
        break;
    case 0x01F0E1:
        SUB_01F0E1();
        break;
    case 0x01F0F9:
        SUB_01F0F9();
        break;
    case 0x01F847:
        SUB_01F847();
        break;
    case 0x01CA70:
        SUB_01CA70();
        break;
    case 0x01DB89:
        SUB_01DB89();
        break;
    case 0x01DBBA:
        SUB_01DBBA();
        break;
    case 0x01DFAC:
        SUB_01DFAC();
        break;
    case 0x010000:
        SUB_010000();
        break;
    case 0x010003:
        SUB_010003();
        break;
    case 0x01EA3E:
        SUB_01EA3E();
        break;
    case 0x01000F:
        SUB_01000F();
        break;
    case 0x01000C:
        SUB_01000C();
        break;
    case 0x01EB66:
        SUB_01EB66();
        break;
    case 0x01EE99:
        SUB_01EE99();
        break;
    case 0x01EDE5:
        SUB_01EDE5();
        break;
    case 0x01EB90:
        SUB_01EB90();
        break;
    case 0x01EFCD:
        SUB_01EFCD();
        break;
    case 0x01E95B:
        SUB_01E95B();
        break;
    case 0x01EE3E:
        SUB_01EE3E();
        break;
    case 0x01ED03:
        SUB_01ED03();
        break;
    case 0x01EC81:
        SUB_01EC81();
        break;
    case 0x01EF3D:
        SUB_01EF3D();
        break;
    case 0x01F036:
        SUB_01F036();
        break;
    case 0x019CF1:
        SUB_019CF1();
        break;
    case 0x01AE8E:
        SUB_01AE8E();
        break;
    case 0x01F0DA:
        SUB_01F0DA();
        break;
    case 0x01AEDD:
        SUB_01AEDD();
        break;
    case 0x01F0C6:
        SUB_01F0C6();
        break;
    case 0x01B32C:
        SUB_01B32C();
        break;
    case 0x01F149:
        SUB_01F149();
        break;
    case 0x015484:
        SUB_015484();
        break;
    case 0x01B68B:
        SUB_01B68B();
        break;
    case 0x01B2CD:
        SUB_01B2CD();
        break;
    case 0x01EA4F:
        SUB_01EA4F();
        break;
    case 0x01EA98:
        SUB_01EA98();
        break;
    case 0x01F0EE:
        SUB_01F0EE();
        break;
    case 0x01F23A:
        SUB_01F23A();
        break;
    case 0x01C052:
        SUB_01C052();
        break;
    case 0x01DFCE:
        SUB_01DFCE();
        break;
    case 0x01D60E:
        SUB_01D60E();
        break;
    case 0x01DCFD:
        SUB_01DCFD();
        break;
    case 0x01FF99:
        SUB_01FF99();
        break;
    case 0x01C000:
        SUB_01C000();
        break;
    case 0x01FFBE:
        SUB_01FFBE();
        break;
    case 0x010396:
        SUB_010396();
        break;
    case 0x01037D:
        SUB_01037D();
        break;
    case 0x01036E:
        SUB_01036E();
        break;
    case 0x010365:
        SUB_010365();
        break;
    case 0x0103C2:
        SUB_0103C2();
        break;
    case 0x0103EA:
        SUB_0103EA();
        break;
    case 0x0103FE:
        SUB_0103FE();
        break;
    case 0x010304:
        SUB_010304();
        break;
    case 0x010437:
        SUB_010437();
        break;
    case 0x010486:
        SUB_010486();
        break;
    case 0x0104AA:
        SUB_0104AA();
        break;
    case 0x010501:
        SUB_010501();
        break;
    case 0x0104E5:
        SUB_0104E5();
        break;
    case 0x0104F6:
        SUB_0104F6();
        break;
    case 0x0105CA:
        SUB_0105CA();
        break;
    case 0x0105E3:
        SUB_0105E3();
        break;
    case 0x0105F1:
        SUB_0105F1();
        break;
    case 0x010606:
        SUB_010606();
        break;
    case 0x01F270:
        SUB_01F270();
        break;
    default:
		string mapperMode = myMapper->getMapperMode();
        printf("Unhandled jump to address: %04X\n", target);
		exit(1);
    }
}
