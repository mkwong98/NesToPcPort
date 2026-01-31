#include <SDL3/SDL_mutex.h>
#include "game.h"
#include "console.h"
#include "mapper.h"
#include <stdexcept> // Add this include to resolve std::runtime_error


//OAMDMA 0x200

#define PPU_CTRL      0x2000
#define PPU_MASK      0x2001
#define PPU_STATUS    0x2002
#define PPU_OAMADDR   0x2003
#define PPU_OAMDATA   0x2004
#define PPU_SCROLL    0x2005
#define PPU_ADDR      0x2006
#define PPU_DATA      0x2007
#define PPU_OAMDMA    0x4014

#define APU_P1REG0   0x4000
#define APU_P1REG1   0x4001
#define APU_P1REG2   0x4002
#define APU_P1REG3   0x4003
#define APU_P2REG0   0x4004
#define APU_P2REG1   0x4005
#define APU_P2REG2   0x4006
#define APU_P2REG3   0x4007
#define APU_TRIANGREG0 0x4008
#define APU_TRIANGREG1 0x400A
#define APU_TRIANGREG2 0x400B
#define APU_NOISEREG1 0x400C
#define APU_NOISEREG2 0x400E
#define APU_NOISEREG3 0x400F
#define APU_DMCREG0   0x4010
#define APU_DMCREG1  0x4011
#define APU_DMCREG2  0x4012
#define APU_DMCREG3  0x4013
#define APU_STATUS    0x4015
#define APU_FRAMECNT  0x4017

#define JOY1         0x4016
#define JOY2         0x4017

//RAM
#define PLAYER_OFFSET  0x051 // Each player data takes 0x14 bytes
#define NUKE_COUNT     0x052
#define HEALTH1        0x054
#define HEALTH2        0x055
#define ARREST         0x056
#define LIVES          0x058

#define SCROLL_FINE  0x583
#define SCROLL_LARGE 0x584

void game::repeat() {
}

void game::brk() {
}

void game::initGame() {
}

void game::endGame() {

}

void game::atScanline(Uint8 scanline) {
    pushAddress(0x80B6);
    SUB_01FE95_SetScroll();
    a = myMapper->readCPU(0x0010);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    myMapper->writeCPU(0xBFFF, a);
    opLSR_A(1);
    x = 0x08;
    do {
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0xBFFF, a);
}

void game::atSprite0Hit() {
}

void game::SUB_000000() {
    pushAddress(0x8002);
    jump(0x819F);
    if (handleReturnAddress(poppedEntry.value, 0x8002)) return;
    myMapper->writeCPU(0x05AC, a);
    if (!flgN) {
        if (a != 0x01) {
            popAddress();
        }
        x = 0x07;
        a = 0x00;
    }
    else {
        myMapper->writeCPU(0x0547, 0x80);
        x = 0x03;
        a = 0x0C;
    }
    jump(0x8029);
}

void game::SUB_000020() {
    a = 0x06;
    pushAddress(0x8024);
    SUB_01FFAA_SwitchCHRBank1();
    x = 0x0F;
    a = 0x27;
    SUB_000029();
    return;
}

void game::SUB_000029() {
    myMapper->writeCPU(0x05A2, x);
    myMapper->writeCPU(0x05CA, a);
    a = 0x02;
    pushAddress(0x8033);
    SUB_01FFD2_SwitchCHRBank0();
    pushAddress(0x8036);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0x8036)) return;
    pushAddress(0x8039);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x8039)) return;
    a = myMapper->readCPU(0x03C1);
    opAND(0xF8);
    myMapper->writeCPU(0x03C1, a);
    myMapper->writeCPU(0x058A, myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x058B, myMapper->readCPU(0x001F));
    myMapper->writeCPU(0x001E, 0x32);
    a = 0xC9;
    myMapper->writeCPU(0x001F, a);
    x = myMapper->readCPU(0x0589);
    setLoadFlag(x);
    if (!flgN) {
        myMapper->writeCPU(0x040E, x);
        opINX(1);
        myMapper->writeCPU(0x040F, x);
        a = 0x05;
        myMapper->writeCPU(0x042C, a);
        myMapper->writeCPU(0x042D, a);
        a = 0x00;
        myMapper->writeCPU(0x03B4, a);
        myMapper->writeCPU(0x03B5, a);
        myMapper->writeCPU(0x03F0, a);
        myMapper->writeCPU(0x03F1, a);
        a = 0x20;
        myMapper->writeCPU(0x03D2, a);
        myMapper->writeCPU(0x03D3, a);
        myMapper->writeCPU(0x0396, 0x08);
        a = 0x28;
        myMapper->writeCPU(0x0397, a);
    }
    goto L_000090;
    while (true) {
        a = 0x02;
        pushAddress(0x808F);
        SUB_01FFD2_SwitchCHRBank0();
    L_000090:
        a = myMapper->readCPU(0x0040);
        opAND(0xFE);
        myMapper->writeCPU(PPU_CTRL, a);
        x = myMapper->readCPU(0x05CA);
        a = myMapper->readCPU(0x8171 + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_000133;
        }
        myMapper->writeCPU(0x03FD, a);
        a = myMapper->readCPU(0x003F);
        opAND(myMapper->readCPU(0x05A2));
        if (flgZ) {
            opINC(0x05CA, 1);
        }
    L_0000AF:
        wait(2); 
		needWaitScanline = true;
		waitScanline = 32;
        wait(3);
        if (myMapper->readCPU(0x03FD) == 0x18) {
            a = 0x16;
            pushAddress(0x80DC);
            jump(0xEA16);
            if (handleReturnAddress(poppedEntry.value, 0x80DC)) return;
        }
        a = myMapper->readCPU(0x05AC);
        if (a == 0xFF) {
            pushAddress(0x80E6);
            jump(0xF822);
            if (handleReturnAddress(poppedEntry.value, 0x80E6)) return;
        }
        a = myMapper->readCPU(0x003F);
        opLSR_A(1);
        if (flgC) {
            if (myMapper->readCPU(0x05D1) != 0xFE) {
                goto L_0000FB;
            }
            opINC(0x03C1, 1);
            if (flgZ) {
                opINC(0x03DF, 1);
            }
        }
    L_0000FB:
        a = 0x04;
        myMapper->writeCPU(0x0028, a);
        y = 0x00;
        pushAddress(0x8103);
        jump(0xCA70);
        if (handleReturnAddress(poppedEntry.value, 0x8103)) return;
        x = myMapper->readCPU(0x0589);
        setLoadFlag(x);
        if (!flgN) {
            y = 0x11;
            pushAddress(0x810D);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x810D)) return;
            y = 0x12;
            pushAddress(0x8112);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x8112)) return;
            pushAddress(0x8115);
            jump(0xCA60);
            if (handleReturnAddress(poppedEntry.value, 0x8115)) return;
        }
        pushAddress(0x8118);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x8118)) return;
        pushAddress(0x811B);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x811B)) return;
        pushAddress(0x811E);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x811E)) return;
        pushAddress(0x8121);
        jump(0xEA36);
        if (handleReturnAddress(poppedEntry.value, 0x8121)) return;
        a = myMapper->readCPU(0x000D);
        setLoadFlag(a);
        if (flgZ) {
            goto L_000128;
        }
        myMapper->writeCPU(0x000B, a);
    L_000128:
        pushAddress(0x812A);
        jump(0xDBB3);
        if (handleReturnAddress(poppedEntry.value, 0x812A)) return;
        a = 0x06;
        pushAddress(0x812F);
        SUB_01FFAA_SwitchCHRBank1();
    }
L_000133:
    if (myMapper->readCPU(0x05AC) == 0xFF) {
        a = myMapper->readCPU(0x0091);
        if (a == 0xFF) {
            a = myMapper->readCPU(0x0547);
            setLoadFlag(a);
            if (flgZ) {
                goto L_000154;
            }
            opDEC(0x0547, 1);
            if (a != 0x32) {
                goto L_000151;
            }
            a = 0x0F;
            pushAddress(0x8150);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x8150)) return;
        }
    L_000151:
        goto L_0000AF;
    }
L_000154:
    a = 0x00;
    myMapper->writeCPU(0x05CA, a);
    myMapper->writeCPU(0x0486, a);
    myMapper->writeCPU(0x0487, a);
    myMapper->writeCPU(0x00B9, a);
    myMapper->writeCPU(0x004C, a);
    myMapper->writeCPU(0x001E, myMapper->readCPU(0x058A));
    myMapper->writeCPU(0x001F, myMapper->readCPU(0x058B));
    a = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_00019F() {
    pushAddress(0x81A1);
    jump(0xDE68);
    if (handleReturnAddress(poppedEntry.value, 0x81A1)) return;
    pushAddress(0x81A4);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0x81A4)) return;
    pushAddress(0x81A7);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0x81A7)) return;
    pushAddress(0x81AA);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0x81AA)) return;
    pushAddress(0x81AD);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x81AD)) return;
    myMapper->writeCPU(0x05D3, 0x03);
    x = 0x00;
    myMapper->writeCPU(0x0589, 0x00);
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    setLoadFlag(a);
    if (!flgZ) {
        y = 0x02;
        myMapper->writeCPU(0x0589, y);
        x = 0x16;
        if (a != 0x03) {
            y = 0x04;
            myMapper->writeCPU(0x0589, y);
            x = 0x2C;
            if (a == 0x05) {
                goto L_0001E9;
            }
            y = 0xFF;
            myMapper->writeCPU(0x0589, y);
            x = 0x42;
            if (a == 0x11) {
                goto L_000206;
            }
            x = 0x58;
            opCMP(a, 0x12);
            if (flgZ) {
                goto L_000206;
            }
            popAddress();
            return;
        }
    }
L_0001E9:
    myMapper->writeCPU(0x05BF, 0x53);
    myMapper->writeCPU(0x05C0, 0x57);
    a = 0x5E;
    myMapper->writeCPU(0x05C1, a);
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x81FD);
    jump(0x8223);
    if (handleReturnAddress(poppedEntry.value, 0x81FD)) return;
    a = 0x02;
    pushAddress(0x8202);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x8202)) return;
    jump(0x82BB);
    return;
L_000206:
    myMapper->writeCPU(0x05BF, 0x2E);
    myMapper->writeCPU(0x05C0, 0x32);
    a = 0x40;
    myMapper->writeCPU(0x05C1, a);
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x821A);
    jump(0x8223);
    if (handleReturnAddress(poppedEntry.value, 0x821A)) return;
    a = 0x01;
    pushAddress(0x821F);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x821F)) return;
    jump(0x82BB);
    return;
}

void game::SUB_000223() {
    myMapper->writeCPU(0x041B, 0x06);
    a = 0x00;
    myMapper->writeCPU(0x05CD, a);
    myMapper->writeCPU(0x03FD, a);
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
    myMapper->writeCPU(0x05D2, a);
    myMapper->writeCPU(0x05D1, a);
    myMapper->writeCPU(0x05D0, a);
    myMapper->writeCPU(0x059D, a);
    myMapper->writeCPU(0x0091, 0x64);
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x8447 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x8448 + x));
    myMapper->writeCPU(0x0587, myMapper->readCPU(0x8449 + x));
    myMapper->writeCPU(0x0588, myMapper->readCPU(0x844A + x));
    myMapper->writeCPU(0x05BE, myMapper->readCPU(0x844B + x));
    myMapper->writeCPU(0x0092, myMapper->readCPU(0x844C + x));
    myMapper->writeCPU(0x0093, myMapper->readCPU(0x844D + x));
    myMapper->writeCPU(0x000C, myMapper->readCPU(0x844E + x));
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x844F + x));
    myMapper->writeCPU(0x009A, myMapper->readCPU(0x8450 + x));
    myMapper->writeCPU(0x009B, myMapper->readCPU(0x8451 + x));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x8452 + x));
    myMapper->writeCPU(0x009D, myMapper->readCPU(0x8453 + x));
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x8454 + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x8455 + x));
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x8456 + x));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x8457 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x8458 + x));
    a = myMapper->readCPU(0x8459 + x);
    myMapper->writeCPU(0x000F, a);
    y = myMapper->readCPU(0x845A + x);
    pushAddress(0x82AD);
    jump(0x838B);
    if (handleReturnAddress(poppedEntry.value, 0x82AD)) return;
    a = myMapper->readCPU(0x845B + x);
    y = myMapper->readCPU(0x845C + x);
    x = a;
    pushAddress(0x82B7);
    jump(0xDC63);
    if (handleReturnAddress(poppedEntry.value, 0x82B7)) return;
    jump(0xDEF4);
    return;
}

void game::SUB_0002BB() {
    myMapper->writeCPU(0x0005, 0x9E);
    myMapper->writeCPU(0x0006, 0xE9);
    myMapper->writeCPU(0x0007, 0xDE);
    a = 0xE9;
    myMapper->writeCPU(0x0008, a);
    pushAddress(0x82CD);
    jump(0xDD83);
    if (handleReturnAddress(poppedEntry.value, 0x82CD)) return;
    pushAddress(0x82D0);
    jump(0x83CF);
    if (handleReturnAddress(poppedEntry.value, 0x82D0)) return;
    a = myMapper->readCPU(0x0042);
    opORA(0x80);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    pushAddress(0x82DD);
    jump(0xDCFD);
    if (handleReturnAddress(poppedEntry.value, 0x82DD)) return;
    pushAddress(0x82E0);
    jump(0x8020);
    if (handleReturnAddress(poppedEntry.value, 0x82E0)) return;
    a = 0x00;
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x05AF, a);
    goto L_000308;
L_0002EB:
    pushAddress(0x82ED);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0x82ED)) return;
    a = myMapper->readCPU(0x05D1);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0011);
    pushAddress(0x82F8);
    SUB_01FFAA_SwitchCHRBank1();
    a = 0x02;
    pushAddress(0x82FD);
    SUB_01FFD2_SwitchCHRBank0();
    a = myMapper->readCPU(0x0040);
    opAND(0xFE);
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0x8307);
    jump(0xDBDF);
    if (handleReturnAddress(poppedEntry.value, 0x8307)) return;
L_000308:
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x830F);
        jump(0xE6E4);
        if (handleReturnAddress(poppedEntry.value, 0x830F)) return;
        pushAddress(0x8312);
        jump(0xE7DF);
        if (handleReturnAddress(poppedEntry.value, 0x8312)) return;
        pushAddress(0x8315);
        jump(0xE84A);
        if (handleReturnAddress(poppedEntry.value, 0x8315)) return;
        pushAddress(0x8318);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x8318)) return;
        pushAddress(0x831B);
        jump(0xE685);
        if (handleReturnAddress(poppedEntry.value, 0x831B)) return;
        pushAddress(0x831E);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x831E)) return;
        pushAddress(0x8321);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x8321)) return;
        pushAddress(0x8324);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0x8324)) return;
    }
	wait(2);
    needWaitScanline = true;
    waitScanline = 32;
	wait(3);
    a = myMapper->readCPU(0x00B9);
    if (a == 0x10) {
        a = myMapper->readCPU(0x058C);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x058C, 1);
            a = myMapper->readCPU(0x058D);
            pushAddress(0x835A);
            jump(0xE9E6);
            if (handleReturnAddress(poppedEntry.value, 0x835A)) return;
            a = 0x0F;
            pushAddress(0x835F);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x835F)) return;
            goto L_000388;
        }
        opINC(0x058C, 1);
        pushAddress(0x8368);
        jump(0xEA06);
        if (handleReturnAddress(poppedEntry.value, 0x8368)) return;
        a = 0x0E;
        pushAddress(0x836D);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x836D)) return;
    }
    pushAddress(0x8225);
    jump(0xEA36);
    if (handleReturnAddress(poppedEntry.value, 0x8225)) return;
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000388;
    }
    pushAddress(0x8378);
    jump(0xE61C);
    if (handleReturnAddress(poppedEntry.value, 0x8378)) return;
    pushAddress(0x837B);
    jump(0x8B52);
    if (handleReturnAddress(poppedEntry.value, 0x837B)) return;
    pushAddress(0x837E);
    jump(0x84D9);
    if (handleReturnAddress(poppedEntry.value, 0x837E)) return;
    pushAddress(0x8381);
    jump(0xE1F0);
    if (handleReturnAddress(poppedEntry.value, 0x8381)) return;
    pushAddress(0x8384);
    jump(0xE34E);
    if (handleReturnAddress(poppedEntry.value, 0x8384)) return;
    pushAddress(0x8387);
    jump(0xCA15);
    if (handleReturnAddress(poppedEntry.value, 0x8387)) return;
L_000388:
    goto L_0002EB;
}

void game::SUB_00038B() {
    myMapper->writeCPU(0x05AC, x);
    x = 0x00;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0x839F + y));
        opINX(1);
        opINY(1);
    } while (x != 0x10);
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_0003CF() {
    a = myMapper->readCPU(0x0042);
    opAND(0x7F);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    a = myMapper->readCPU(SCROLL_FINE);
    opPHA();
    a = myMapper->readCPU(SCROLL_LARGE);
    opPHA();
    myMapper->writeCPU(SCROLL_LARGE, 0x00);
    a = myMapper->readCPU(0x00A0);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    myMapper->writeCPU(SCROLL_FINE, a);
    opDEC(SCROLL_LARGE, 1);
    myMapper->writeCPU(0x05AF, 0x08);
    do {
        a = myMapper->readCPU(0x00A0);
        pushAddress(0x840B);
        jump(0xE20C);
        if (handleReturnAddress(poppedEntry.value, 0x840B)) return;
        pushAddress(0x840E);
        jump(0x97E3);
        if (handleReturnAddress(poppedEntry.value, 0x840E)) return;
        pushAddress(0x8411);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8411)) return;
        pushAddress(0x8414);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8414)) return;
        pushAddress(0x8417);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8417)) return;
        pushAddress(0x841A);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x841A)) return;
        pushAddress(0x841D);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x841D)) return;
        pushAddress(0x8420);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8420)) return;
        pushAddress(0x8423);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8423)) return;
        pushAddress(0x8426);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8426)) return;
        flgC = false;
        a = myMapper->readCPU(SCROLL_FINE);
        opADC(0x20);
        myMapper->writeCPU(SCROLL_FINE, a);
        if (!flgC) {
            goto L_000435;
        }
        opINC(SCROLL_LARGE, 1);
    L_000435:
        opINC(0x00A0, 1);
        opDEC(0x05AF, 1);
    } while (!flgN);
    opDEC(0x00A0, 1);
    opPLA();
    myMapper->writeCPU(SCROLL_LARGE, a);
    opPLA();
    myMapper->writeCPU(SCROLL_FINE, a);
    popAddress();
}

void game::SUB_0004D9() {
    if (myMapper->readCPU(0x05D0) == 0) {
        goto L_0004F1;
    }
    if (myMapper->readCPU(0x0439) >= 0xC0) {
        x = 0x00;
        myMapper->writeCPU(0x05A3, x);
        myMapper->writeCPU(0x05A4, x);
        opDEX(1);
        myMapper->writeCPU(0x05D0, x);
    }
L_0004F1:
    a = 0x00;
    myMapper->writeCPU(0x05CF, a);
    pushAddress(0x84F8);
    jump(0x8A62);
    if (handleReturnAddress(poppedEntry.value, 0x84F8)) return;
    a = myMapper->readCPU(0x05D2);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
        }
        else {
            opBIT(myMapper->readCPU(0x059F));
            if (flgN) {
            }
            else {
                a = myMapper->readCPU(0x05C3);
                myMapper->writeCPU(0x05C6, a);
                if (a < 0x10) {
                    if (a < 0x08) {
                        goto L_000522;
                    }
                    goto L_0005DD;
                L_000522:
                    a = myMapper->readCPU(0x059D);
                    setLoadFlag(a);
                    if (flgN) {
                        goto L_0005EA;
                    }
                    x = 0x00;
                    y = 0x00;
                    jump(0x8A1A);
                    return;
                }
                flgC = true;
                opSBC(0x10);
                x = a;
                if (myMapper->readCPU(0x05D0) == 0xFF) {
                    a = 0xFF;
                    myMapper->writeCPU(0x05D1, a);
                    popAddress();
                    return;
                }
                a = myMapper->readCPU(0x8A9D + x);
                myMapper->writeCPU(0x05AA, a);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x05AB, a);
                myMapper->writeCPU(0x05A6, myMapper->readCPU(0x8AB5 + x));
                myMapper->writeCPU(0x05A7, myMapper->readCPU(0x8ACD + x));
                myMapper->writeCPU(0x05A8, myMapper->readCPU(0x8AE5 + x));
                if (myMapper->readCPU(0x059D) != 0) {
                    a = 0x25;
                    pushAddress(0x856B);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x856B)) return;
                    x = 0x18;
                    pushAddress(0x8570);
                    jump(0x8A0C);
                    if (handleReturnAddress(poppedEntry.value, 0x8570)) return;
                }
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
                a = myMapper->readCPU(0x05C6);
                myMapper->writeCPU(0x05A5, 0x00);
                x = 0x02;
                if (a != 0x18) {
                    x = 0x04;
                    if (a != 0x19) {
                        goto L_00059D;
                    }
                }
                myMapper->writeCPU(0x05A5, x);
                a = myMapper->readCPU(0x001A);
                pushAddress(0x8599);
                jump(0xEA16);
                if (handleReturnAddress(poppedEntry.value, 0x8599)) return;
                goto L_0005EA;
            L_00059D:
                if (a == 0x1D) {
                    x = myMapper->readCPU(0x05CB);
                    a = myMapper->readCPU(0x004B);
                    opAND(0x80);
                    if (!flgZ) {
                        if (x == 0xF2) {
                            goto L_0005B7;
                        }
                        opDEX(1);
                    }
                    else {
                        if (x == 0xF9) {
                            goto L_0005B7;
                        }
                        opINX(1);
                    }
                L_0005B7:
                    myMapper->writeCPU(0x05CB, x);
                    y = 0x00;
                    pushAddress(0x85BE);
                    jump(0x8A1A);
                    if (handleReturnAddress(poppedEntry.value, 0x85BE)) return;
                    a = 0x15;
                    pushAddress(0x85C3);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x85C3)) return;
                    goto L_0005EA;
                }
                x = 0xF9;
                myMapper->writeCPU(0x05CB, x);
                if (a == 0x1C) {
                    x = myMapper->readCPU(0x05B8);
                    setLoadFlag(x);
                    if (flgN) {
                        x = 0x28;
                        myMapper->writeCPU(0x05B8, x);
                    }
                }
                goto L_0005EA;
            L_0005DD:
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
            }
        }
    }
L_0005EA:
    y = myMapper->readCPU(0x004B);
    a = y;
    opAND(0x01);
    if (!flgZ) {
        a = 0x00;
        myMapper->writeCPU(0x05CD, a);
        pushAddress(0x85F8);
        jump(0xE195);
        if (handleReturnAddress(poppedEntry.value, 0x85F8)) return;
    }
    a = y;
    opAND(0x02);
    if (!flgZ) {
        a = 0x80;
        myMapper->writeCPU(0x05CD, a);
        pushAddress(0x8605);
        jump(0xE195);
        if (handleReturnAddress(poppedEntry.value, 0x8605)) return;
    }
    a = y;
    opAND(0x08);
    if (!flgZ) {
    }
    if (myMapper->readCPU(0x059D) != 0) {
        goto L_00063C;
    }
    a = y;
    opAND(0x04);
    if (!flgZ) {
        if (myMapper->readCPU(0x05C3) == 0x17) {
            goto L_00062E;
        }
        if (myMapper->readCPU(0x05C9) != 0) {
            goto L_00064B;
        }
        x = 0x15;
        a = 0x10;
        myMapper->writeCPU(0x05C9, a);
        pushAddress(0x862A);
        jump(0x8A11);
        if (handleReturnAddress(poppedEntry.value, 0x862A)) return;
        goto L_00064B;
    L_00062E:
        a = myMapper->readCPU(0x058E);
        y = myMapper->readCPU(0x0051);
        myMapper->writeCPU(0x0059 + y, a);
        a = 0xFE;
        myMapper->writeCPU(0x05D1, a);
        popAddress();
        return;
    }
L_00063C:
    if (myMapper->readCPU(0x05C9) != 0) {
        myMapper->writeCPU(0x05C9, 0x00);
        myMapper->writeCPU(0x05CA, 0x18);
    }
L_00064B:
    a = myMapper->readCPU(0x004C);
    opAND(0x80);
    if (!flgZ) {
        if (myMapper->readCPU(0x0655) == 0) {
            goto L_00066C;
        }
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_000660;
        }
        a = myMapper->readCPU(0x059D);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_00066C;
        }
    L_000660:
        x = 0xFB;
        y = 0x00;
        pushAddress(0x8666);
        jump(0x8A1A);
        if (handleReturnAddress(poppedEntry.value, 0x8666)) return;
        a = 0x10;
        pushAddress(0x866B);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x866B)) return;
    }
L_00066C:
    if (myMapper->readCPU(0x05A0) == 0) {
        goto L_00068E;
    }
    opDEC(0x05A0, 1);
    a = y;
    opAND(0x80);
    if (flgZ) {
        goto L_00068E;
    }
    if (myMapper->readCPU(0x059E) == 0xF8) {
        goto L_00068E;
    }
    flgC = true;
    a = myMapper->readCPU(0x059E);
    opSBC(0x01);
    myMapper->writeCPU(0x059E, a);
    if (!flgC) {
        opDEC(0x059F, 1);
    }
L_00068E:
    a = myMapper->readCPU(0x059D);
    setLoadFlag(a);
    if (!flgZ) {
        opBIT(myMapper->readCPU(0x059F));
        if (flgN) {
            if (myMapper->readCPU(0x05C4) < 0x10) {
                goto L_0006AA;
            }
            a = 0x00;
            myMapper->writeCPU(0x059F, a);
            myMapper->writeCPU(0x05A0, a);
            myMapper->writeCPU(0x059E, a);
        }
    L_0006AA:
        flgC = false;
        a = myMapper->readCPU(0x03C1);
        opADC(myMapper->readCPU(0x059E));
        myMapper->writeCPU(0x03C1, a);
        a = myMapper->readCPU(0x03DF);
        opADC(myMapper->readCPU(0x059F));
        myMapper->writeCPU(0x03DF, a);
        if (a == 0x02) {
            myMapper->writeCPU(0x05D1, 0x02);
        }
        opINC(0x05A9, 1);
        a = myMapper->readCPU(0x05A9);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x059E) == 0x08) {
                goto L_0006DF;
            }
            opINC(0x059E, 1);
            if (flgZ) {
                opINC(0x059F, 1);
            }
        }
    }
L_0006DF:
    a = myMapper->readCPU(0x004C);
    opAND(0x40);
    if (!flgZ) {
        if (myMapper->readCPU(0x0655) == 0) {
            goto L_0006F9;
        }
        x = 0x01;
        a = myMapper->readCPU(0x05C9);
        setLoadFlag(a);
        if (!flgZ) {
            x = 0x07;
        }
        pushAddress(0x86F5);
        jump(0x8A0C);
        if (handleReturnAddress(poppedEntry.value, 0x86F5)) return;
        goto L_000705;
    L_0006F9:
        x = 0x0D;
        a = myMapper->readCPU(0x05C9);
        setLoadFlag(a);
        if (!flgZ) {
            x = 0x11;
        }
        pushAddress(0x8704);
        jump(0x8A0C);
        if (handleReturnAddress(poppedEntry.value, 0x8704)) return;
    }
L_000705:
    y = 0x05;
    x = 0x01;
    a = myMapper->readCPU(0x05A4);
    setLoadFlag(a);
    if (!flgN) {
        x = 0x03;
    }
    pushAddress(0x8712);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8712)) return;
    myMapper->writeCPU(0x05C7, a);
    if (a < 0x08) {
        a = myMapper->readCPU(0x059D);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00073B;
        }
        a = myMapper->readCPU(0x059F);
        setLoadFlag(a);
        if (flgN) {
            goto L_00073B;
        }
        y = 0x06;
        pushAddress(0x8728);
        jump(0xE587);
        if (handleReturnAddress(poppedEntry.value, 0x8728)) return;
        myMapper->writeCPU(0x05C8, a);
        if (a < 0x08) {
            goto L_00073B;
        }
    }
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
    myMapper->writeCPU(0x05A5, a);
L_00073B:
    pushAddress(0x873D);
    jump(0xE0C9);
    if (handleReturnAddress(poppedEntry.value, 0x873D)) return;
    pushAddress(0x8740);
    jump(0xDED2);
    if (handleReturnAddress(poppedEntry.value, 0x8740)) return;
    opCMP(y, myMapper->readCPU(SCROLL_LARGE));
    if (!flgZ) {
        if (flgC) {
            goto L_000750;
        }
    }
    else {
        if (x < myMapper->readCPU(SCROLL_FINE)) {
            goto L_000756;
        }
    L_000750:
        myMapper->writeCPU(SCROLL_FINE, x);
        myMapper->writeCPU(SCROLL_LARGE, y);
    }
L_000756:
    x = myMapper->readCPU(0x05CA);
    setLoadFlag(x);
    if (flgZ) {
    }
    else {
        a = myMapper->readCPU(0x84B5 + x);
        setLoadFlag(a);
        if (!flgN) {
            x = a;
            opAND(0x3F);
            opORA(myMapper->readCPU(0x05CD));
            myMapper->writeCPU(0x03FD, a);
            opDEC(0x05CE, 1);
            if (flgN) {
                goto L_000785;
            }
            popAddress();
            return;
        }
        x = 0x00;
        myMapper->writeCPU(0x05CA, x);
        a = myMapper->readCPU(0x059D);
        setLoadFlag(a);
        if (!flgZ) {
            a = 0x1F;
            opORA(myMapper->readCPU(0x05CD));
            myMapper->writeCPU(0x03FD, a);
        }
        popAddress();
        return;
    L_000785:
        a = 0x03;
        myMapper->writeCPU(0x05CE, a);
        opINC(0x05CA, 1);
        if (x != 0x05) {
            if (x == 0x0B) {
                goto L_0007A6;
            }
            if (x == 0x07) {
                goto L_000804;
            }
            if (x == 0x0D) {
                goto L_000804;
            }
            if (x == 0x47) {
                goto L_000804;
            }
            if (x == 0x4D) {
                goto L_000804;
            }
            popAddress();
            return;
        }
    L_0007A6:
        y = 0x01;
        myMapper->writeCPU(0x05BC, y);
        pushAddress(0x87AD);
        jump(0x891A);
        if (handleReturnAddress(poppedEntry.value, 0x87AD)) return;
        if (!flgZ) {
            y = 0x02;
            pushAddress(0x87B4);
            jump(0x891A);
            if (handleReturnAddress(poppedEntry.value, 0x87B4)) return;
            if (!flgZ) {
                y = 0x06;
                pushAddress(0x87BB);
                jump(0x891A);
                if (handleReturnAddress(poppedEntry.value, 0x87BB)) return;
                if (!flgZ) {
                    y = 0x07;
                    pushAddress(0x87C2);
                    jump(0x891A);
                    if (handleReturnAddress(poppedEntry.value, 0x87C2)) return;
                    if (!flgZ) {
                        y = 0x0E;
                        pushAddress(0x87C9);
                        jump(0x891A);
                        if (handleReturnAddress(poppedEntry.value, 0x87C9)) return;
                        if (!flgZ) {
                            y = 0x0F;
                            pushAddress(0x87D0);
                            jump(0x891A);
                            if (handleReturnAddress(poppedEntry.value, 0x87D0)) return;
                            if (!flgZ) {
                                y = 0x10;
                                pushAddress(0x87D7);
                                jump(0x891A);
                                if (handleReturnAddress(poppedEntry.value, 0x87D7)) return;
                                if (!flgZ) {
                                    y = 0x11;
                                    pushAddress(0x87DE);
                                    jump(0x891A);
                                    if (handleReturnAddress(poppedEntry.value, 0x87DE)) return;
                                    if (!flgZ) {
                                        popAddress();
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        a = 0x0D;
        pushAddress(0x87E6);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x87E6)) return;
        a = myMapper->readCPU(0x050B + y);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x050B + y, a);
        if (flgN) {
            x = 0x00;
            jump(0x9083);
            return;
        }
        x = y;
        a = myMapper->readCPU(0x03FD);
        myMapper->writeCPU(0x0565 + x, a);
        y = 0x12;
        jump(0x9156);
        return;
    L_000804:
        a = myMapper->readCPU(0x0595);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x0596, 1);
            if (flgZ) {
                myMapper->writeCPU(0x0595, 0x00);
                a = 0x02;
                myMapper->writeCPU(0x0594, a);
            }
            if (x >= 0x40) {
                if (a == 0x04) {
                    goto L_00086D;
                }
                if (a == 0x05) {
                    goto L_00086D;
                }
                x = 0x00;
                y = 0x03;
                a = myMapper->readCPU(0x0475 + y);
                setLoadFlag(a);
                if (flgZ) {
                    a = myMapper->readCPU(0x0595);
                    if (a == 0x01) {
                        goto L_000857;
                    }
                    if (a == 0x02) {
                        goto L_000839;
                    }
                }
            }
            popAddress();
            return;
        L_000839:
            pushAddress(0x886F);
            jump(0x89B5);
            if (handleReturnAddress(poppedEntry.value, 0x886F)) return;
            y = 0x04;
            x = 0xFA;
            pushAddress(0x8842);
            jump(0x89B5);
            if (handleReturnAddress(poppedEntry.value, 0x8842)) return;
            y = 0x05;
            x = 0x06;
            pushAddress(0x8849);
            jump(0x89B5);
            if (handleReturnAddress(poppedEntry.value, 0x8849)) return;
            a = 0x00;
            myMapper->writeCPU(0x0497, a);
            myMapper->writeCPU(0x0498, a);
            a = 0x07;
            jump(0xEA1B);
            return;
        L_000857:
            pushAddress(0x8887);
            jump(0x89B5);
            if (handleReturnAddress(poppedEntry.value, 0x8887)) return;
            x = 0xFA;
            y = 0x04;
            pushAddress(0x8860);
            jump(0x89B5);
            if (handleReturnAddress(poppedEntry.value, 0x8860)) return;
            x = 0x06;
            y = 0x05;
            pushAddress(0x8867);
            jump(0x89B5);
            if (handleReturnAddress(poppedEntry.value, 0x8867)) return;
            a = 0x08;
            jump(0xEA1B);
            return;
        }
    L_00086D:
        x = 0x00;
        y = 0x03;
        if (myMapper->readCPU(0x0475 + y) != 0) {
            y = 0x04;
            if (myMapper->readCPU(0x0475 + y) != 0) {
                y = 0x05;
                a = myMapper->readCPU(0x0475 + y);
                setLoadFlag(a);
                if (!flgZ) {
                    popAddress();
                    return;
                }
            }
        }
        a = 0x06;
        pushAddress(0x8889);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x8889)) return;
        jump(0x89B5);
        return;
    }
    a = 0x09;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        if (myMapper->readCPU(0x059D) == 0) {
            goto L_0008A7;
        }
        a = 0x1F;
        goto L_0008A0;
    L_00089E:
        a = 0x00;
    }
L_0008A0:
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    popAddress();
    return;
L_0008A7:
    a = myMapper->readCPU(0x05C3);
    opCMP(a, 0x11);
    if (!flgZ) {
        opCMP(a, 0x12);
        if (!flgZ) {
            goto L_0008B7;
        }
    }
    if (myMapper->readCPU(0x05CF) == 0) {
        goto L_00089E;
    }
L_0008B7:
    a = myMapper->readCPU(0x05A3);
    opORA(myMapper->readCPU(0x05A4));
    if (!flgZ) {
        opDEC(0x05A2, 1);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x05A4));
            if (flgN) {
                a = myMapper->readCPU(0x05A3);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x05A4);
                opEOR(0xFF);
                opADC(0x00);
            }
            else {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x05A3));
                a = myMapper->readCPU(0x05A4);
            }
            opROL_M(0x0000, 1);
            opROL_A(1);
            x = a;
            myMapper->writeCPU(0x05A2, myMapper->readCPU(0x8A98 + x));
            opINC(0x03FD, 1);
        }
    }
    a = myMapper->readCPU(0x03FD);
    opAND(0x03);
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    opAND(0x7F);
    if (a != myMapper->readCPU(0x00B8)) {
        myMapper->writeCPU(0x00B8, a);
        a = myMapper->readCPU(0x00FD);
        setLoadFlag(a);
        if (flgZ) {
            x = 0x23;
            a = myMapper->readCPU(0x00B8);
            setLoadFlag(a);
            if (flgZ) {
                goto L_000915;
            }
            x = 0x24;
            if (a != 0x02) {
                goto L_000919;
            }
        L_000915:
            a = x;
            jump(0xEA1B);
            return;
        }
    }
L_000919:
    popAddress();
}

void game::SUB_00091A() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x11) {
            goto L_00097D;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_00097D;
            }
            if (myMapper->readCPU(0x0529 + y) < 0x12) {
                if (myMapper->readCPU(0x03DF) != 0) {
                    goto L_00097D;
                }
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(myMapper->readCPU(0x05C9));
                myMapper->writeCPU(0x0000, a);
                if (myMapper->readCPU(0x041B + y) != 0x07) {
                    goto L_000980;
                }
                a = myMapper->readCPU(0x03C1 + y);
                flgC = false;
                opADC(0x20);
                flgC = true;
                opSBC(myMapper->readCPU(0x0000));
                if (!flgN) {
                    if (a >= 0x30) {
                        goto L_00097D;
                    }
                    flgC = true;
                    opBIT(myMapper->readCPU(0x03FD));
                    if (!flgN) {
                        goto L_00096F;
                    }
                    a = myMapper->readCPU(0x0439);
                    opSBC(myMapper->readCPU(0x0439 + y));
                    if (flgC) {
                        if (a >= 0x18) {
                            goto L_00097D;
                        }
                        do {
                            do {
                                a = 0x00;
                                setLoadFlag(a);
                                popAddress();
                                return;
                            L_00096F:
                                a = myMapper->readCPU(0x0439 + y);
                                opSBC(myMapper->readCPU(0x0439));
                                if (!flgC) {
                                    goto L_00097D;
                                }
                                opCMP(a, 0x20);
                            } while (flgZ);
                        } while (!flgC);
                    }
                }
            }
        }
    }
L_00097D:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
    return;
L_000980:
    a = myMapper->readCPU(0x03C1 + y);
    flgC = false;
    opADC(0x08);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    if (flgC) {
        if (a >= 0x18) {
            goto L_0009B2;
        }
        flgC = true;
        opBIT(myMapper->readCPU(0x03FD));
        if (!flgN) {
            goto L_0009A4;
        }
        a = myMapper->readCPU(0x0439);
        opSBC(myMapper->readCPU(0x0439 + y));
        if (flgC) {
            if (a >= 0x18) {
                goto L_0009B2;
            }
            do {
                do {
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                L_0009A4:
                    a = myMapper->readCPU(0x0439 + y);
                    opSBC(myMapper->readCPU(0x0439));
                    if (!flgC) {
                        goto L_0009B2;
                    }
                    opCMP(a, 0x20);
                } while (flgZ);
            } while (!flgC);
        }
    }
L_0009B2:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0009B5() {
    myMapper->writeCPU(0x04B1 + y, x);
    a = myMapper->readCPU(0x0385);
    opBIT(myMapper->readCPU(0x05CD));
    if (flgN) {
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        a = 0xFA;
        myMapper->writeCPU(0x0493 + y, a);
    }
    else {
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        myMapper->writeCPU(0x0493 + y, 0x06);
    }
    myMapper->writeCPU(0x03DF + y, myMapper->readCPU(0x03DF));
    a = 0x08;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        goto L_0009F9;
    }
    a = 0x18;
L_0009F9:
    flgC = false;
    opADC(myMapper->readCPU(0x03C1));
    myMapper->writeCPU(0x03C1 + y, a);
    myMapper->writeCPU(0x03FD + y, myMapper->readCPU(0x05CD));
    a = 0x03;
    myMapper->writeCPU(0x0475 + y, a);
    popAddress();
}

void game::SUB_000A0C() {
    a = myMapper->readCPU(0x05CA);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x8A19);
        return;
    }
    SUB_000A11();
    return;
}

void game::SUB_000A11() {
    myMapper->writeCPU(0x05CA, x);
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    SUB_000A19();
    return;
}

void game::SUB_000A19() {
    popAddress();
}

void game::SUB_000A1A() {
    a = myMapper->readCPU(0x05A1);
    setLoadFlag(a);
    if (!flgZ) {
        a = 0x20;
        myMapper->writeCPU(0x05A6, a);
    }
    myMapper->writeCPU(0x05A0, y);
    myMapper->writeCPU(0x059E, x);
    x = 0x00;
    myMapper->writeCPU(0x05A1, x);
    myMapper->writeCPU(0x05A9, x);
    opBIT(myMapper->readCPU(0x059E));
    if (!flgN) {
        goto L_000A38;
    }
    opDEX(1);
L_000A38:
    myMapper->writeCPU(0x059F, x);
    opDEX(1);
    myMapper->writeCPU(0x059D, x);
    popAddress();
}

void game::SUB_000A40() {
    y = 0x02;
    if (!(myMapper->readCPU(0x0493 + x) & 0x80)) {
        goto L_000A49;
    }
    y = 0xFE;
L_000A49:
    myMapper->writeCPU(0x05A4, y);
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    x = 0xFB;
    y = 0x00;
    pushAddress(0x8A57);
    jump(0x8A1A);
    if (handleReturnAddress(poppedEntry.value, 0x8A57)) return;
    myMapper->writeCPU(0x05D2, 0xFF);
    a = 0x1F;
    jump(0xEA16);
    return;
}

void game::SUB_000A62() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF));
    y = myMapper->readCPU(0x03C1);
    flgC = true;
    a = myMapper->readCPU(0x0385);
    opSBC(0x04);
    x = a;
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    myMapper->writeCPU(0x0095, a);
    pushAddress(0x8A7A);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x8A7A)) return;
    x = 0x02;
    y = 0x06;
    pushAddress(0x8A81);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8A81)) return;
    myMapper->writeCPU(0x05C3, a);
    y = 0x00;
    pushAddress(0x8A89);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8A89)) return;
    myMapper->writeCPU(0x05C4, a);
    x = 0x02;
    y = 0x05;
    pushAddress(0x8A93);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8A93)) return;
    myMapper->writeCPU(0x05C5, a);
    popAddress();
}

void game::SUB_000B52() {
    pushAddress(0x8B54);
    jump(0x97E3);
    if (handleReturnAddress(poppedEntry.value, 0x8B54)) return;
    x = 0x00;
    myMapper->writeCPU(0x0659, x);
    myMapper->writeCPU(0x05BC, x);
    myMapper->writeCPU(0x05A1, x);
    opDEX(1);
    myMapper->writeCPU(0x0655, x);
    x = 0x01;
    myMapper->writeCPU(0x05CC, myMapper->readCPU(0x0587));
    SUB_000B6C();
    return;
}

void game::SUB_000B6C() {
    myMapper->writeCPU(0x05AC, x);
    y = myMapper->readCPU(0x0475 + x);
    setLoadFlag(y);
    if (flgZ) {
        jump(0x8B87);
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x8B12 + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x8B32 + y));
    a = 0x8B;
    opPHA();
    a = 0x86;
    opPHA();
	pushManualAddress(0x8B86);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_000B87() {
    opINC(0x05AF, 1);
    x = myMapper->readCPU(0x05AC);
    opINX(1);
    opDEC(0x05CC, 1);
    if (!flgZ) {
        jump(0x8B6C);
        return;
    }
    SUB_000B93();
    return;
}

void game::SUB_000B93() {
    a = myMapper->readCPU(0x003F);
    opADC(myMapper->readCPU(0x05AF));
    myMapper->writeCPU(0x05AF, a);
    popAddress();
}

void game::SUB_000B9C() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x03A3 + x));
    y = myMapper->readCPU(0x03C1 + x);
    a = myMapper->readCPU(0x0385 + x);
    x = a;
    pushAddress(0x8BAF);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x8BAF)) return;
    x = myMapper->readCPU(0x05AC);
    a = 0x00;
    if (myMapper->readCPU(0x0493 + x) & 0x80) {
        goto L_000BBC;
    }
    a = 0x02;
L_000BBC:
    x = a;
    y = 0x02;
    pushAddress(0x8BC1);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8BC1)) return;
    myMapper->writeCPU(0x05C7, a);
    x = 0x01;
    y = 0x03;
    pushAddress(0x8BCB);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8BCB)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_000BD0() {
    a = myMapper->readCPU(0x04CF + x);
    setLoadFlag(a);
    if (!flgN) {
        if (flgZ) {
            goto L_000BE0;
        }
        opDEC(0x04CF + x, 1);
    }
    myMapper->writeCPU(0x03FD + x, 0xFF);
    popAddress();
    return;
L_000BE0:
    y = 0x03;
    pushAddress(0x8BE4);
    jump(0x9B88);
    if (handleReturnAddress(poppedEntry.value, 0x8BE4)) return;
    if (!flgN) {
        pushAddress(0x8BE9);
        jump(0x8A40);
        if (handleReturnAddress(poppedEntry.value, 0x8BE9)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x003F);
    opLSR_A(1);
    y = myMapper->readCPU(0x0493 + x);
    setLoadFlag(y);
    if (!flgN) {
        opEOR(0xFF);
    }
    opAND(0x03);
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x03FD + x, a);
    pushAddress(0x8C01);
    jump(0x8B9C);
    if (handleReturnAddress(poppedEntry.value, 0x8C01)) return;
    if (a < 0x08) {
        pushAddress(0x8C08);
        jump(0x9207);
        if (handleReturnAddress(poppedEntry.value, 0x8C08)) return;
    }
    else {
        myMapper->writeCPU(0x04B1 + x, 0x00);
        a = myMapper->readCPU(0x03C1 + x);
        opAND(0xF8);
        myMapper->writeCPU(0x03C1 + x, a);
    }
    opCMP(myMapper->readCPU(0x05C7), 0x08);
    if (flgC) {
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0xFF);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0493 + x, a);
    }
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (!flgN) {
        goto L_000C33;
    }
    opDEY(1);
L_000C33:
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    popAddress();
}

void game::SUB_000C41() {
    if (myMapper->readCPU(0x0565 + x) == 0) {
        goto L_000C56;
    }
    opDEC(0x0565 + x, 1);
    if (!flgZ) {
        goto L_000CAC;
    }
    myMapper->writeCPU(0x04ED + x, 0x00);
    myMapper->writeCPU(0x0475 + x, 0x01);
    popAddress();
    return;
L_000C56:
    a = 0x87;
    flgC = false;
    opADC(myMapper->readCPU(0x04CF + x));
    myMapper->writeCPU(0x03FD + x, a);
    pushAddress(0x8C61);
    jump(0x8FE1);
    if (handleReturnAddress(poppedEntry.value, 0x8C61)) return;
    if (!flgN) {
        pushAddress(0x8C66);
        jump(0x970F);
        if (handleReturnAddress(poppedEntry.value, 0x8C66)) return;
        if (flgN) {
            goto L_000CAC;
        }
        a = 0x19;
        pushAddress(0x8C6D);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x8C6D)) return;
        myMapper->writeCPU(0x0565 + x, 0x20);
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3 + x);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x03C1 + y, a);
        a = 0x00;
        myMapper->writeCPU(0x0457 + y, a);
        myMapper->writeCPU(0x03DF + y, a);
        myMapper->writeCPU(0x04B1 + y, a);
        myMapper->writeCPU(0x03FD + y, 0x80);
        myMapper->writeCPU(0x0493 + y, 0xFC);
        myMapper->writeCPU(0x0475 + y, 0x07);
        myMapper->writeCPU(0x041B + y, 0x01);
    }
L_000CAC:
    popAddress();
}

void game::SUB_000CAD() {
    if (myMapper->readCPU(0x04CF + x) != 0) {
        goto L_000CD1;
    }
    myMapper->writeCPU(0x03FD + x, 0xFF);
    a = myMapper->readCPU(0x05AF);
    opAND(0x3F);
    if (!flgZ) {
        popAddress();
        return;
    }
    y = 0x00;
    if (myMapper->readCPU(0x0439) < myMapper->readCPU(0x0439 + x)) {
        y = 0x80;
    }
    a = y;
    opORA(0x01);
    myMapper->writeCPU(0x03FD + x, a);
L_000CD1:
    opINC(0x04CF + x, 1);
    a = myMapper->readCPU(0x04CF + x);
    if (a != 0x0C) {
        if (a == 0x24) {
            goto L_000CE0;
        }
        popAddress();
        return;
    L_000CE0:
        myMapper->writeCPU(0x04CF + x, 0x00);
        popAddress();
        return;
    }
    jump(0x966B);
    return;
}

void game::SUB_000CE9() {
    if (myMapper->readCPU(0x04CF + x) != 0) {
        goto L_000D00;
    }
    myMapper->writeCPU(0x03FD + x, 0xFF);
    a = myMapper->readCPU(0x05AF);
    opAND(0xDF);
    if (!flgZ) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x03FD + x, 0x00);
L_000D00:
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        a = myMapper->readCPU(0x03C1 + x);
        opAND(0xF8);
        myMapper->writeCPU(0x0000, a);
        a = myMapper->readCPU(0x004D);
        opAND(0x03);
        opORA(myMapper->readCPU(0x0000));
        myMapper->writeCPU(0x03C1 + x, a);
    }
    opINC(0x04CF + x, 1);
    a = myMapper->readCPU(0x04CF + x);
    if (a != 0x14) {
        if (a == 0x28) {
            goto L_000D2F;
        }
        if (a == 0x50) {
            goto L_000D29;
        }
        popAddress();
        return;
    L_000D29:
        myMapper->writeCPU(0x04CF + x, 0x00);
        popAddress();
        return;
    }
L_000D2F:
    jump(0x96CF);
    return;
}

void game::SUB_000D32() {
    myMapper->writeCPU(0x04CF + x, 0x00);
    a = 0x00;
    y = 0x01;
    jump(0x8D70);
    return;
}

void game::SUB_000D3E() {
    myMapper->writeCPU(0x04CF + x, 0x00);
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x66);
    myMapper->writeCPU(0x0385 + x, a);
    if (!flgC) {
        goto L_000D51;
    }
    opINC(0x03A3 + x, 1);
L_000D51:
    a = 0x2D;
    y = 0x01;
    jump(0x8D70);
    return;
}

void game::SUB_000D58() {
    myMapper->writeCPU(0x04CF + x, 0x01);
    a = 0x00;
    y = 0x00;
    jump(0x8D70);
    return;
}

void game::SUB_000D64() {
    myMapper->writeCPU(0x04CF + x, 0x01);
    a = 0x22;
    y = 0x00;
    jump(0x8D70);
    return;
}

void game::SUB_000D70() {
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x03FD + x, y);
    myMapper->writeCPU(0x0475 + x, 0x1B);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    popAddress();
}

void game::SUB_000D87() {
    a = 0x00;
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0x05A1);
    setLoadFlag(a);
    if (flgZ) {
        opBIT(myMapper->readCPU(0x059F));
        if (!flgN) {
            myMapper->writeCPU(0x0000, myMapper->readCPU(0x03DF));
            a = myMapper->readCPU(0x03C1);
            flgC = false;
            opADC(0x30);
            if (flgC) {
                opINC(0x0000, 1);
            }
            flgC = true;
            opSBC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x0001, a);
            a = myMapper->readCPU(0x0000);
            opSBC(0x00);
            if (flgZ) {
                if (myMapper->readCPU(0x0001) >= 0x10) {
                    goto L_000E03;
                }
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x03A3));
                a = myMapper->readCPU(0x0385);
                flgC = false;
                opADC(0x08);
                if (flgC) {
                    opINC(0x0000, 1);
                }
                flgC = true;
                opSBC(myMapper->readCPU(0x0385 + x));
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x0000);
                opSBC(myMapper->readCPU(0x03A3 + x));
                if (flgZ) {
                    if (myMapper->readCPU(0x0001) >= 0x28) {
                        goto L_000E03;
                    }
                    a = 0x1A;
                    pushAddress(0x8DDE);
                    jump(0xEA16);
                    if (handleReturnAddress(poppedEntry.value, 0x8DDE)) return;
                    a = 0xFF;
                    myMapper->writeCPU(0x05A1, a);
                    myMapper->writeCPU(0x0004, a);
                    if (myMapper->readCPU(0x059D) != 0) {
                        a = 0x00;
                        myMapper->writeCPU(0x05A3, a);
                        myMapper->writeCPU(0x05A4, a);
                    }
                    a = 0x00;
                    myMapper->writeCPU(0x059D, a);
                    myMapper->writeCPU(0x059E, a);
                    myMapper->writeCPU(0x059F, a);
                    myMapper->writeCPU(0x05A6, 0x10);
                }
            }
        }
    }
L_000E03:
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        y = myMapper->readCPU(0x0493 + x);
        while (true) {
            if (myMapper->readCPU(0x04CF + x) == 0) {
                goto L_000E17;
            }
            a = myMapper->readCPU(0x8F57 + y);
            goto L_000E1A;
        L_000E17:
            a = myMapper->readCPU(0x8EA2 + y);
        L_000E1A:
            myMapper->writeCPU(0x0002, a);
            if (a != 0x81) {
                goto L_000E29;
            }
            a = 0x00;
            myMapper->writeCPU(0x0493 + x, a);
            y = a;
        }
    L_000E29:
        flgC = false;
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            if (!flgC) {
                goto L_000E47;
            }
            opINC(0x03A3 + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            if (!flgC) {
                opDEC(0x03A3 + x, 1);
            }
        }
    L_000E47:
        flgC = false;
        if (myMapper->readCPU(0x04CF + x) != 0) {
            a = myMapper->readCPU(0x8F9C + y);
            setLoadFlag(a);
        }
        else {
            a = myMapper->readCPU(0x8EFD + y);
            setLoadFlag(a);
        }
        if (!flgN) {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                goto L_000E71;
            }
            opINC(0x03DF + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                opDEC(0x03DF + x, 1);
            }
        }
    L_000E71:
        opINC(0x0493 + x, 1);
    }
    if (myMapper->readCPU(0x0004) != 0) {
        myMapper->writeCPU(0x03DF, myMapper->readCPU(0x03DF + x));
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x03C1, a);
        if (!flgC) {
            opDEC(0x03DF, 1);
        }
        y = 0x00;
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (!flgN) {
            goto L_000E93;
        }
        opDEY(1);
    L_000E93:
        flgC = false;
        opADC(myMapper->readCPU(0x0385));
        myMapper->writeCPU(0x0385, a);
        a = y;
        opADC(myMapper->readCPU(0x03A3));
        myMapper->writeCPU(0x03A3, a);
    }
    popAddress();
}

void game::SUB_000FE1() {
    if (myMapper->readCPU(0x04ED + x) == 0x09) {
        goto L_000FED;
    }
    if (myMapper->readCPU(0x05BD) != 0) {
        goto L_00100A;
    }
L_000FED:
    if (myMapper->readCPU(0x0457 + x) == 0) {
        if (myMapper->readCPU(0x03DF) != 0) {
            goto L_00100A;
        }
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x20);
        flgC = true;
        opSBC(myMapper->readCPU(0x03C1));
        if (!flgN) {
            if (a >= 0x3F) {
                goto L_00100A;
            }
            a = 0x00;
            setLoadFlag(a);
            popAddress();
            return;
        }
    }
L_00100A:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00100D() {
    pushAddress(0x900F);
    jump(0x8FE1);
    if (handleReturnAddress(poppedEntry.value, 0x900F)) return;
    if (flgZ) {
        flgC = true;
        if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
            goto L_001037;
        }
        a = myMapper->readCPU(0x0439 + x);
        opSBC(myMapper->readCPU(0x0439));
        if (flgC) {
            if (a < 0x0C) {
                goto L_001043;
            }
            if (a >= 0x18) {
                goto L_001043;
            }
            do {
                a = 0x00;
                myMapper->writeCPU(0x05BB, a);
                myMapper->writeCPU(0x0655, a);
                myMapper->writeCPU(0x05A3, a);
                myMapper->writeCPU(0x05A4, a);
                popAddress();
                return;
            L_001037:
                a = myMapper->readCPU(0x0439);
                opSBC(myMapper->readCPU(0x0439 + x));
                if (!flgC) {
                    goto L_001043;
                }
            } while (a < 0x10);
        }
    }
L_001043:
    a = 0xFF;
    myMapper->writeCPU(0x05BB, a);
    popAddress();
}

void game::SUB_001049() {
    pushAddress(0x904B);
    jump(0x9064);
    if (handleReturnAddress(poppedEntry.value, 0x904B)) return;
    myMapper->writeCPU(0x05C3, a);
    y = 0x05;
    a = myMapper->readCPU(0x03FD + x);
    setLoadFlag(a);
    if (flgN) {
        goto L_00105B;
    }
    x = 0x02;
    goto L_00105D;
L_00105B:
    x = 0x00;
L_00105D:
    pushAddress(0x905F);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x905F)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_001064() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x03A3 + x));
    y = myMapper->readCPU(0x03C1 + x);
    a = myMapper->readCPU(0x0385 + x);
    x = a;
    pushAddress(0x9077);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x9077)) return;
    x = 0x01;
    y = 0x05;
    pushAddress(0x907E);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x907E)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_001083() {
    myMapper->writeCPU(0x0565 + y, myMapper->readCPU(0x03FD + x));
    myMapper->writeCPU(0x04B1 + y, 0xFB);
    myMapper->writeCPU(0x0475 + y, 0x11);
    a = myMapper->readCPU(0x03FD + y);
    opAND(0x80);
    flgC = false;
    x = myMapper->readCPU(0x04ED + y);
    opCMP(x, 0x06);
    if (!flgC) {
        goto L_0010EB;
    }
    if (x < 0x09) {
        goto L_0010D7;
    }
    if (x == 0x09) {
        opORA(myMapper->readCPU(0x04CF + y));
        myMapper->writeCPU(0x03FD + y, a);
        a = myMapper->readCPU(0x05BC);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0010C4;
        }
        a = 0x13;
        pushAddress(0x90B7);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x90B7)) return;
        a = myMapper->readCPU(0x0565 + y);
        opEOR(0x80);
        myMapper->writeCPU(0x0565 + y, a);
        opINC(0x0083, 1);
        opINC(0x008F, 1);
    L_0010C4:
        popAddress();
        return;
    }
    opORA(myMapper->readCPU(0x04CF + y));
    myMapper->writeCPU(0x03FD + y, a);
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0082, a);
    while (true) {
        while (true) {
            a = 0x1F;
            jump(0xEA1B);
            return;
        L_0010D7:
            opORA(0x05);
            myMapper->writeCPU(0x03FD + y, a);
            myMapper->writeCPU(0x041B + y, 0x07);
            a = myMapper->readCPU(0x0082);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x0082, a);
        }
    L_0010EB:
        opORA(myMapper->readCPU(0x04CF + y));
        opADC(0x05);
        myMapper->writeCPU(0x03FD + y, a);
        opINC(0x0082, 1);
    }
    SUB_0010F8();
    return;
}

void game::SUB_0010F8() {
    opCMP(myMapper->readCPU(0x03DF + x), 0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x04B1 + x);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                goto L_00111D;
            }
            opINC(0x03DF + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                opDEC(0x03DF + x, 1);
            }
        }
    L_00111D:
        a = myMapper->readCPU(0x003F);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x04B1 + x) == 0x08) {
                goto L_00112D;
            }
            opINC(0x04B1 + x, 1);
        }
    L_00112D:
        if (!(myMapper->readCPU(0x0565 + x) & 0x80)) {
            goto L_001141;
        }
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x03);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            goto L_001140;
        }
        opDEC(0x03A3 + x, 1);
        do {
        L_001140:
            popAddress();
            return;
        L_001141:
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x0385 + x, a);
        } while (!flgC);
        opINC(0x03A3 + x, 1);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_001156() {
    myMapper->writeCPU(0x0529 + x, y);
    myMapper->writeCPU(0x0547 + x, 0x06);
    a = myMapper->readCPU(0x03FD + x);
    opAND(0x80);
    myMapper->writeCPU(0x0493 + x, a);
    popAddress();
}

void game::SUB_001168() {
    y = a;
    a = myMapper->readCPU(0x8AFD + y);
    setLoadFlag(a);
    if (!flgN) {
        y = a;
        opAND(0x3F);
        opORA(myMapper->readCPU(0x0493 + x));
        flgC = false;
        opADC(myMapper->readCPU(0x04CF + x));
        myMapper->writeCPU(0x03FD + x, a);
        if (y == 0x40) {
            goto L_001185;
        }
        while (true) {
            while (true) {
                opDEC(0x0547 + x, 1);
                if (flgN) {
                    goto L_0011C1;
                }
                popAddress();
                return;
            L_001185:
                a = myMapper->readCPU(0x04CF + x);
                opORA(myMapper->readCPU(0x0493 + x));
                myMapper->writeCPU(0x03FD + x, a);
                if (!(myMapper->readCPU(0x0565 + x) & 0x80)) {
                    goto L_0011A7;
                }
                a = myMapper->readCPU(0x0385 + x);
                flgC = true;
                opSBC(0x04);
                myMapper->writeCPU(0x0385 + x, a);
                a = myMapper->readCPU(0x03A3 + x);
                opSBC(0x00);
                myMapper->writeCPU(0x03A3 + x, a);
            }
        L_0011A7:
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x04);
            myMapper->writeCPU(0x0385 + x, a);
            a = myMapper->readCPU(0x03A3 + x);
            opADC(0x00);
            myMapper->writeCPU(0x03A3 + x, a);
        }
    }
    myMapper->writeCPU(0x0529 + x, 0x00);
    popAddress();
    return;
L_0011C1:
    a = 0x06;
    myMapper->writeCPU(0x0547 + x, a);
    opINC(0x0529 + x, 1);
    if (y != 0x46) {
        if (y == 0x48) {
            goto L_0011E7;
        }
        if (y == 0x44) {
            goto L_0011DA;
        }
        if (y == 0x45) {
            goto L_0011DA;
        }
        do {
            popAddress();
            return;
        L_0011DA:
            a = myMapper->readCPU(0x05BB);
            setLoadFlag(a);
        } while (flgN);
        opDEC(0x008E, 1);
        jump(0x9448);
        return;
    }
    jump(0x966B);
    return;
L_0011E7:
    pushAddress(0x96D1);
    jump(0x970F);
    if (handleReturnAddress(poppedEntry.value, 0x96D1)) return;
    if (flgN) {
        goto L_001206;
    }
    myMapper->writeCPU(0x0475 + y, 0x12);
    myMapper->writeCPU(0x04B1 + y, 0xFA);
    myMapper->writeCPU(0x03FD + y, 0x01);
    myMapper->writeCPU(0x03C1 + y, myMapper->readCPU(0x03C1 + x));
    a = 0x00;
    jump(0x968B);
    return;
L_001206:
    popAddress();
}

void game::SUB_001207() {
    myMapper->writeCPU(0x0529 + x, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    if (!flgC) {
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x04B1 + x);
            if (a == 0x08) {
                goto L_001228;
            }
            opINC(0x04B1 + x, 1);
        }
    L_001228:
        popAddress();
        return;
    }
    a = 0x00;
    myMapper->writeCPU(0x0475 + x, a);
    popAddress();
}

void game::SUB_00122F() {
    pushAddress(0x9231);
    jump(0x900D);
    if (handleReturnAddress(poppedEntry.value, 0x9231)) return;
    pushAddress(0x9234);
    jump(0x9064);
    if (handleReturnAddress(poppedEntry.value, 0x9234)) return;
    if (a < 0x08) {
        pushAddress(0x923B);
        jump(0x9207);
        if (handleReturnAddress(poppedEntry.value, 0x923B)) return;
        y = 0x00;
    }
    else {
        y = myMapper->readCPU(0x04ED + x);
        myMapper->writeCPU(0x04B1 + x, 0x00);
        a = myMapper->readCPU(0x03C1 + x);
        opAND(0xF8);
        myMapper->writeCPU(0x03C1 + x, a);
        a = myMapper->readCPU(0x0529 + x);
        setLoadFlag(a);
        if (!flgZ) {
            jump(0x9168);
            return;
        }
        if (y != 0x09) {
            if (myMapper->readCPU(0x05BB) & 0x80) {
                goto L_00129D;
            }
            a = myMapper->readCPU(0x004D);
            opAND(0x07);
            if (flgZ) {
                if (y == 0x0A) {
                    goto L_001279;
                }
                y = 0x01;
                a = myMapper->readCPU(0x05AF);
                opLSR_A(1);
                if (flgC) {
                    y = 0x03;
                }
                jump(0x9156);
                return;
            L_001279:
                y = 0x01;
                jump(0x9156);
                return;
            }
            a = myMapper->readCPU(0x04CF + x);
            opORA(0x80);
            myMapper->writeCPU(0x03FD + x, a);
            popAddress();
            return;
        }
        y = 0x05;
        myMapper->writeCPU(0x0659, y);
        pushAddress(0x928E);
        jump(0x9B92);
        if (handleReturnAddress(poppedEntry.value, 0x928E)) return;
        if (flgN) {
            goto L_00129D;
        }
        y = x;
        x = 0x00;
        a = 0xFF;
        myMapper->writeCPU(0x05BC, a);
        jump(0x9083);
        return;
    L_00129D:
        a = myMapper->readCPU(0x003F);
        opAND(0x0C);
        opLSR_A(1);
        flgC = true;
        opROR_A(1);
        opADC(myMapper->readCPU(0x04CF + x));
        myMapper->writeCPU(0x03FD + x, a);
    }
    a = myMapper->readCPU(0x0385 + x);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0385 + x, a);
    a = myMapper->readCPU(0x03A3 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03A3 + x, a);
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x92C8 + y));
    a = myMapper->readCPU(0x92D3 + y);
    myMapper->writeCPU(0x0006, a);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_0012DE() {
    a = myMapper->readCPU(0x05AF);
    opAND(0x3F);
    if (!flgZ) {
        jump(0x92EA);
        return;
    }
    y = 0x05;
    jump(0x9156);
    return;
}

void game::SUB_0012EA() {
    popAddress();
}

void game::SUB_0012EB() {
    pushAddress(0x92ED);
    jump(0x8FE1);
    if (handleReturnAddress(poppedEntry.value, 0x92ED)) return;
    if (flgN) {
        jump(0x92EA);
        return;
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x1F);
    if (!flgZ) {
        jump(0x92EA);
        return;
    }
    y = 0x0C;
    jump(0x9156);
    return;
}

void game::SUB_0012FB() {
    pushAddress(0x92FD);
    jump(0x900D);
    if (handleReturnAddress(poppedEntry.value, 0x92FD)) return;
    pushAddress(0x9300);
    jump(0x9049);
    if (handleReturnAddress(poppedEntry.value, 0x9300)) return;
    if (a < 0x08) {
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0x80);
        myMapper->writeCPU(0x0493 + x, a);
    }
    a = myMapper->readCPU(0x05C3);
    if (a < 0x08) {
        jump(0x9207);
        return;
    }
    myMapper->writeCPU(0x04B1 + x, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    opAND(0xF8);
    myMapper->writeCPU(0x03C1 + x, a);
    a = myMapper->readCPU(0x0529 + x);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x9168);
        return;
    }
    if (!(myMapper->readCPU(0x05BB) & 0x80)) {
        a = myMapper->readCPU(0x004F);
        opAND(0x07);
        if (flgZ) {
            a = myMapper->readCPU(0x04CF + x);
            if (a != 0x09) {
                y = 0x01;
                a = myMapper->readCPU(0x05AF);
                opLSR_A(1);
                if (flgC) {
                    y = 0x03;
                }
                jump(0x9156);
                return;
            }
            y = 0x01;
            jump(0x9156);
            return;
        }
        a = myMapper->readCPU(0x04CF + x);
        opORA(myMapper->readCPU(0x0493 + x));
        myMapper->writeCPU(0x03FD + x, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x0C);
    opLSR_A(2);
    opORA(myMapper->readCPU(0x0493 + x));
    opADC(myMapper->readCPU(0x04CF + x));
    myMapper->writeCPU(0x03FD + x, a);
    y = myMapper->readCPU(0x04ED + x);
    if (!(myMapper->readCPU(0x0493 + x) & 0x80)) {
        goto L_001385;
    }
    a = myMapper->readCPU(0x0385 + x);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x0385 + x, a);
    a = myMapper->readCPU(0x03A3 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03A3 + x, a);
    goto L_001396;
L_001385:
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0385 + x, a);
    a = myMapper->readCPU(0x03A3 + x);
    opADC(0x00);
    myMapper->writeCPU(0x03A3 + x, a);
L_001396:
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x92C8 + y));
    a = myMapper->readCPU(0x92D3 + y);
    myMapper->writeCPU(0x0006, a);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_0013A3() {
    flgC = false;
    a = myMapper->readCPU(0x04B1 + x);
    setLoadFlag(a);
    if (!flgN) {
        opADC(myMapper->readCPU(0x03C1 + x));
        myMapper->writeCPU(0x03C1 + x, a);
        if (!flgC) {
            goto L_0013CA;
        }
        opINC(0x03DF + x, 1);
        if (flgZ) {
            goto L_0013CA;
        }
        myMapper->writeCPU(0x0475 + x, 0x00);
        popAddress();
        return;
    }
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    if (!flgC) {
        opDEC(0x03DF + x, 1);
    }
L_0013CA:
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (!flgZ) {
        goto L_0013D3;
    }
    opINC(0x04B1 + x, 1);
L_0013D3:
    jump(0x93E4);
    return;
}

void game::SUB_0013D6() {
    a = myMapper->readCPU(0x04B1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    if (a >= 0xF4) {
        jump(0x93E9);
        return;
    }
    myMapper->writeCPU(0x03C1 + x, a);
    SUB_0013E4();
    return;
}

void game::SUB_0013E4() {
    if (myMapper->readCPU(0x0457 + x) == 0) {
        jump(0x93EF);
        return;
    }
    SUB_0013E9();
    return;
}

void game::SUB_0013E9() {
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_0013EF() {
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    myMapper->writeCPU(0x0024, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    myMapper->writeCPU(0x0025, a);
    if (myMapper->readCPU(0x05BD) == 0) {
        myMapper->writeCPU(0x0001, 0x38);
        a = 0x20;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x941A);
        jump(0x9B88);
        if (handleReturnAddress(poppedEntry.value, 0x941A)) return;
        if (!flgN) {
            goto L_00141E;
        }
    }
    popAddress();
    return;
L_00141E:
    a = myMapper->readCPU(0x0475 + x);
    if (a == 0x12) {
        pushAddress(0x9427);
        jump(0x95D3);
        if (handleReturnAddress(poppedEntry.value, 0x9427)) return;
        a = 0xFE;
    }
    else {
        a = myMapper->readCPU(0x041B + x);
        if (a != 0x01) {
            goto L_00143C;
        }
        pushAddress(0x9436);
        jump(0x95C9);
        if (handleReturnAddress(poppedEntry.value, 0x9436)) return;
        a = 0xFE;
        goto L_001443;
    L_00143C:
        myMapper->writeCPU(0x0475 + x, 0x00);
        a = 0xFE;
    }
L_001443:
    flgC = false;
    opADC(myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x008E, a);
    SUB_001448();
    return;
}

void game::SUB_001448() {
    if (myMapper->readCPU(0x04B1 + x) == 0) {
        goto L_001455;
    }
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
L_001455:
    a = 0x0C;
    pushAddress(0x9459);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9459)) return;
    x = 0x1C;
    a = myMapper->readCPU(0x05C9);
    setLoadFlag(a);
    if (flgZ) {
        goto L_001463;
    }
    x = 0x20;
L_001463:
    jump(0x8A0C);
    return;
}

void game::SUB_001466() {
    if (myMapper->readCPU(0x0457 + x) == 0) {
        goto L_001471;
    }
    while (true) {
        do {
            myMapper->writeCPU(0x0475 + x, 0x00);
            popAddress();
            return;
        L_001471:
            y = 0x00;
            a = myMapper->readCPU(0x0493 + x);
            setLoadFlag(a);
            if (!flgN) {
                goto L_001479;
            }
            opDEY(1);
        L_001479:
            flgC = false;
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            myMapper->writeCPU(0x0024, a);
            a = y;
            opADC(myMapper->readCPU(0x03A3 + x));
            myMapper->writeCPU(0x03A3 + x, a);
            myMapper->writeCPU(0x0025, a);
            a = myMapper->readCPU(0x04B1 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x03C1 + x));
        } while (a >= 0xF4);
        myMapper->writeCPU(0x03C1 + x, a);
        myMapper->writeCPU(0x0001, 0x30);
        a = 0x18;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x94A5);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94A5)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        y = 0x02;
        pushAddress(0x94AC);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94AC)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        y = 0x06;
        pushAddress(0x94B3);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94B3)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        y = 0x07;
        pushAddress(0x94BA);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94BA)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        a = 0x20;
        myMapper->writeCPU(0x0001, a);
        myMapper->writeCPU(0x0002, a);
        y = 0x0E;
        pushAddress(0x94C7);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94C7)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        y = 0x0F;
        pushAddress(0x94CE);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94CE)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        y = 0x10;
        pushAddress(0x94D5);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94D5)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        y = 0x11;
        pushAddress(0x94DC);
        jump(0x9508);
        if (handleReturnAddress(poppedEntry.value, 0x94DC)) return;
        if (!flgN) {
            goto L_0014E0;
        }
        do {
            popAddress();
            return;
        L_0014E0:
            a = 0x0D;
            pushAddress(0x94E4);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x94E4)) return;
            a = myMapper->readCPU(0x050B + y);
            flgC = true;
            opSBC(myMapper->readCPU(0x0594));
            myMapper->writeCPU(0x050B + y, a);
            if (!flgN) {
                goto L_0014F7;
            }
            pushAddress(0x94F3);
            jump(0x9083);
            if (handleReturnAddress(poppedEntry.value, 0x94F3)) return;
            x = myMapper->readCPU(0x05AC);
        L_0014F7:
            a = myMapper->readCPU(0x0595);
        } while (a == 0x05);
        if (a == 0x04) {
            goto L_001505;
        }
    }
L_001505:
    jump(0x95D3);
    return;
}

void game::SUB_001508() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x11) {
            goto L_001548;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_001548;
            }
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(0x08);
            flgC = true;
            opSBC(myMapper->readCPU(0x03C1 + y));
            if (flgC) {
                if (a >= myMapper->readCPU(0x0001)) {
                    goto L_001548;
                }
                a = myMapper->readCPU(0x0024);
                flgC = false;
                opADC(0x08);
                flgC = true;
                opSBC(myMapper->readCPU(0x0385 + y));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x0025);
                opSBC(myMapper->readCPU(0x03A3 + y));
                if (flgZ) {
                    if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x0002)) {
                        goto L_001548;
                    }
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                }
            }
        }
    }
L_001548:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00154B() {
    myMapper->writeCPU(0x03FD + x, myMapper->readCPU(0x04CF + x));
    a = 0x02;
    myMapper->writeCPU(0x041B + x, a);
    y = 0x02;
    pushAddress(0x955A);
    jump(0x9B92);
    if (handleReturnAddress(poppedEntry.value, 0x955A)) return;
    if (!flgN) {
        y = myMapper->readCPU(0x03FD + x);
        if (y == 0x00) {
            goto L_0015BD;
        }
        myMapper->writeCPU(0x0475 + x, 0x00);
        if (y == 0x08) {
            goto L_00158C;
        }
        if (y == 0x01) {
            goto L_001593;
        }
        if (y == 0x06) {
            goto L_001580;
        }
        if (y == 0x07) {
            goto L_00157A;
        }
    }
    popAddress();
    return;
L_00157A:
    myMapper->writeCPU(0x05BD, 0x06);
    popAddress();
    return;
L_001580:
    a = myMapper->readCPU(0x008E);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x008E, a);
    a = 0x11;
    jump(0xEA1B);
    return;
L_00158C:
    a = 0x05;
    a = 0x0E;
    jump(0xEA1B);
    return;
L_001593:
    y = myMapper->readCPU(0x05BE);
    myMapper->writeCPU(0x0595, y);
    myMapper->writeCPU(0x0594, myMapper->readCPU(0xEA43 + y));
    myMapper->writeCPU(0x0596, myMapper->readCPU(0xEA49 + y));
    y = myMapper->readCPU(0x0051);
    if (myMapper->readCPU(0x0059 + y) != 0x05) {
        goto L_0015B8;
    }
    myMapper->writeCPU(0x04DD, 0x55);
    myMapper->writeCPU(0x04A1, 0x01);
L_0015B8:
    a = 0x12;
    jump(0xEA1B);
    return;
L_0015BD:
    a = 0x81;
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x0081, a);
    opINC(0x0090, 1);
    jump(0x95C9);
    return;
}

void game::SUB_0015C9() {
    myMapper->writeCPU(0x041B + x, 0x02);
    a = 0x02;
    jump(0x95DA);
    return;
}

void game::SUB_0015D3() {
    myMapper->writeCPU(0x041B + x, 0x00);
    a = 0x02;
    SUB_0015DA();
    return;
}

void game::SUB_0015DA() {
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x04CF + x, 0x00);
    myMapper->writeCPU(0x0475 + x, 0x05);
    a = 0x0B;
    pushAddress(0x95EB);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x95EB)) return;
    SUB_0015EC();
    return;
}

void game::SUB_0015EC() {
    a = myMapper->readCPU(0x04CF + x);
    opLSR_A(2);
    opINC(0x04CF + x, 1);
    if (a == 0x04) {
        goto L_001600;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0565 + x));
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_001600:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_001606() {
    myMapper->writeCPU(0x041B + x, 0x07);
    y = myMapper->readCPU(0x0565 + x);
    setLoadFlag(y);
    if (flgZ) {
        myMapper->writeCPU(0x03FD + x, 0xFF);
        a = myMapper->readCPU(0x003F);
        opAND(0x7F);
        if (!flgZ) {
            popAddress();
            return;
        }
        a = 0x04;
        myMapper->writeCPU(0x04ED + x, a);
        opBIT(myMapper->readCPU(0x003F));
        if (flgN) {
            myMapper->writeCPU(0x0565 + x, 0x20);
        }
        y = 0x18;
        if (myMapper->readCPU(0x0439) < myMapper->readCPU(0x0439 + x)) {
            y = 0x98;
        }
        myMapper->writeCPU(0x03FD + x, y);
        myMapper->writeCPU(0x050B + x, 0x00);
    }
    opINC(0x0565 + x, 1);
    a = myMapper->readCPU(0x03C1 + x);
    if (y == 0x30) {
        goto L_001652;
    }
    if (y == 0x0C) {
        goto L_001662;
    }
    if (y == 0x20) {
        goto L_001658;
    }
    popAddress();
    return;
L_001652:
    myMapper->writeCPU(0x0565 + x, 0x00);
    popAddress();
    return;
L_001658:
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x03C1 + x, a);
    opDEC(0x03FD + x, 1);
    popAddress();
    return;
L_001662:
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x03C1 + x, a);
    opINC(0x03FD + x, 1);
    SUB_00166B();
    return;
}

void game::SUB_00166B() {
    pushAddress(0x966D);
    jump(0x970F);
    if (handleReturnAddress(poppedEntry.value, 0x966D)) return;
    if (flgN) {
        jump(0x96CE);
        return;
    }
    a = 0x06;
    pushAddress(0x9674);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9674)) return;
    myMapper->writeCPU(0x0475 + y, 0x07);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x03C1 + y, a);
    a = 0x00;
    myMapper->writeCPU(0x03FD + y, a);
    myMapper->writeCPU(0x04B1 + y, a);
    SUB_00168B();
    return;
}

void game::SUB_00168B() {
    myMapper->writeCPU(0x041B + y, a);
    myMapper->writeCPU(0x0457 + y, a);
    myMapper->writeCPU(0x03DF + y, a);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x0493 + y, 0x03);
    if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
        goto L_0016BF;
    }
    myMapper->writeCPU(0x0493 + y, 0xFD);
    a = myMapper->readCPU(0x0000);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x0001);
    opSBC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    jump(0x96CE);
    return;
L_0016BF:
    a = myMapper->readCPU(0x0000);
    flgC = false;
    opADC(0x18);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x0001);
    opADC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    SUB_0016CE();
    return;
}

void game::SUB_0016CE() {
    popAddress();
}

void game::SUB_0016CF() {
    pushAddress(0x96D1);
    jump(0x970F);
    if (handleReturnAddress(poppedEntry.value, 0x96D1)) return;
    if (flgN) {
        jump(0x96CE);
        return;
    }
    a = 0x06;
    pushAddress(0x96D8);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x96D8)) return;
    myMapper->writeCPU(0x0475 + y, 0x07);
    a = 0x00;
    myMapper->writeCPU(0x041B + y, a);
    myMapper->writeCPU(0x0493 + y, a);
    myMapper->writeCPU(0x03FD + y, a);
    myMapper->writeCPU(0x03DF + y, a);
    myMapper->writeCPU(0x0457 + y, a);
    myMapper->writeCPU(0x04B1 + y, 0xFD);
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x0C);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x03A3 + x);
    opADC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x03C1 + y, a);
    popAddress();
}

void game::SUB_00170F() {
    y = 0x08;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x09;
        if (myMapper->readCPU(0x0475 + y) == 0) {
            goto L_001720;
        }
        a = 0xFF;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_001720:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_001723() {
    a = 0x13;
    pushAddress(0x9727);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9727)) return;
    y = 0x09;
    a = 0x00;
    jump(0x9733);
    return;
}

void game::SUB_00172F() {
    y = 0x00;
    a = 0x01;
    SUB_001733();
    return;
}

void game::SUB_001733() {
    myMapper->writeCPU(0x050B + x, a);
    myMapper->writeCPU(0x04ED + x, y);
    myMapper->writeCPU(0x0475 + x, 0x01);
    myMapper->writeCPU(0x041B + x, 0x07);
    popAddress();
}

void game::SUB_001745() {
    y = 0x01;
    a = 0x01;
    jump(0x9733);
    return;
}

void game::SUB_00174C() {
    y = 0x02;
    a = 0x01;
    jump(0x9733);
    return;
}

void game::SUB_001753() {
    a = 0x07;
    y = 0x0A;
    jump(0x9733);
    return;
}

void game::SUB_00175A() {
    y = 0x00;
    a = 0x01;
    SUB_00175E();
    return;
}

void game::SUB_00175E() {
    myMapper->writeCPU(0x050B + x, a);
    myMapper->writeCPU(0x04ED + x, y);
    myMapper->writeCPU(0x0475 + x, 0x02);
    myMapper->writeCPU(0x0493 + x, 0x80);
    myMapper->writeCPU(0x041B + x, 0x07);
    popAddress();
}

void game::SUB_001775() {
    a = 0x07;
    y = 0x0A;
    jump(0x975E);
    return;
}

void game::SUB_00177C() {
    a = 0x01;
    y = 0x01;
    jump(0x975E);
    return;
}

void game::SUB_001783() {
    a = 0x01;
    y = 0x02;
    jump(0x975E);
    return;
}

void game::SUB_00178A() {
    myMapper->writeCPU(0x04ED + x, 0x07);
    myMapper->writeCPU(0x0475 + x, 0x15);
    myMapper->writeCPU(0x041B + x, 0x04);
    myMapper->writeCPU(0x050B + x, 0x00);
    popAddress();
}

void game::SUB_00179F() {
    myMapper->writeCPU(0x04ED + x, 0x06);
    myMapper->writeCPU(0x0475 + x, 0x14);
    myMapper->writeCPU(0x041B + x, 0x04);
    myMapper->writeCPU(0x050B + x, 0x00);
    popAddress();
}

void game::SUB_0017B4() {
    myMapper->writeCPU(0x04ED + x, 0x03);
    myMapper->writeCPU(0x0475 + x, 0x16);
    myMapper->writeCPU(0x050B + x, 0x01);
    myMapper->writeCPU(0x041B + x, 0x07);
    popAddress();
}

void game::SUB_0017C9() {
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x0475 + x, 0x13);
    myMapper->writeCPU(0x041B + x, 0x04);
    myMapper->writeCPU(0x0493 + x, 0xFF);
    myMapper->writeCPU(0x04B1 + x, 0x00);
    popAddress();
}

void game::SUB_0017E3() {
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        if (a != myMapper->readCPU(0x00A0)) {
            goto L_0017F1;
        }
        pushAddress(0x97ED);
        jump(0x97FC);
        if (handleReturnAddress(poppedEntry.value, 0x97ED)) return;
    }
L_0017F1:
    flgC = false;
    a = y;
    opADC(myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x000E, a);
    if (!flgC) {
        goto L_0017FB;
    }
    opINC(0x000F, 1);
L_0017FB:
    popAddress();
}

void game::SUB_0017FC() {
    opINY(1);
    x = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    a = myMapper->readCPU(0x0475 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_00183B;
    }
    myMapper->writeCPU(0x0385 + x, myMapper->readCPU(SCROLL_FINE));
    a = myMapper->readCPU(SCROLL_LARGE);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x03A3 + x, a);
    opINY(1);
    myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    a = 0x00;
    myMapper->writeCPU(0x03DF + x, a);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0529 + x, a);
    myMapper->writeCPU(0x0565 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0475 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x04CF + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = 0xFF;
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_00183B:
    opINY(4);
    popAddress();
}

void game::SUB_001B88() {
    if (myMapper->readCPU(0x05D2) != 0) {
        jump(0x9BE7);
        return;
    }
    if (myMapper->readCPU(0x05BD) != 0) {
        jump(0x9BE7);
        return;
    }
    SUB_001B92();
    return;
}

void game::SUB_001B92() {
    if (myMapper->readCPU(0x03DF) != 0) {
        jump(0x9BE7);
        return;
    }
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(myMapper->readCPU(0x05C9));
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x9BF3 + y));
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    if (!flgC) {
        jump(0x9BE7);
        return;
    }
    opPHA();
    a = myMapper->readCPU(0x05C9);
    setLoadFlag(a);
    if (!flgZ) {
        opPLA();
        opCMP(a, myMapper->readCPU(0x9C0E + y));
        if (flgC) {
            jump(0x9BE7);
            return;
        }
        if (!flgC) {
            goto L_001BC0;
        }
    }
    opPLA();
    if (a >= myMapper->readCPU(0x9C05 + y)) {
        jump(0x9BE7);
        return;
    }
L_001BC0:
    myMapper->writeCPU(0x0025, myMapper->readCPU(0x03A3 + x));
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x9BEA + y));
    if (!flgC) {
        goto L_001BD0;
    }
    opINC(0x0025, 1);
L_001BD0:
    flgC = true;
    opSBC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opSBC(myMapper->readCPU(0x03A3));
    if (!flgZ) {
        jump(0x9BE7);
        return;
    }
    if (myMapper->readCPU(0x0024) >= myMapper->readCPU(0x9BFC + y)) {
        jump(0x9BE7);
        return;
    }
    a = 0x00;
    popAddress();
}

void game::SUB_001BE7() {
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_004000() {
    pushAddress(0x8002);
    jump(0x81B3);
    if (handleReturnAddress(poppedEntry.value, 0x8002)) return;
    myMapper->writeCPU(0x05AC, a);
    if (!flgN) {
        if (a == 0x01) {
            goto L_004011;
        }
        if (a == 0x03) {
            goto L_004024;
        }
        popAddress();
        return;
    L_004011:
        x = 0x07;
        a = 0x00;
        jump(0x8034);
        return;
    }
    myMapper->writeCPU(0x0547, 0x80);
    x = 0x03;
    a = 0x0C;
    jump(0x8034);
    return;
L_004024:
    x = 0x0F;
    a = 0x2E;
    jump(0x8034);
    return;
}

void game::SUB_00402B() {
    a = 0x06;
    pushAddress(0x802F);
    SUB_01FFAA_SwitchCHRBank1();
    x = 0x0F;
    a = 0x27;
    SUB_004034();
    return;
}

void game::SUB_004034() {
    myMapper->writeCPU(0x05A2, x);
    myMapper->writeCPU(0x05CA, a);
    a = 0x02;
    pushAddress(0x803E);
    SUB_01FFD2_SwitchCHRBank0();
    pushAddress(0x8041);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0x8041)) return;
    pushAddress(0x8044);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x8044)) return;
    a = myMapper->readCPU(0x03C1);
    opAND(0xF8);
    myMapper->writeCPU(0x03C1, a);
    myMapper->writeCPU(0x058A, myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x058B, myMapper->readCPU(0x001F));
    myMapper->writeCPU(0x001E, 0x32);
    a = 0xC9;
    myMapper->writeCPU(0x001F, a);
    x = myMapper->readCPU(0x0589);
    setLoadFlag(x);
    if (!flgN) {
        myMapper->writeCPU(0x040E, x);
        opINX(1);
        myMapper->writeCPU(0x040F, x);
        a = 0x05;
        myMapper->writeCPU(0x042C, a);
        myMapper->writeCPU(0x042D, a);
        a = 0x00;
        myMapper->writeCPU(0x03B4, a);
        myMapper->writeCPU(0x03B5, a);
        myMapper->writeCPU(0x03F0, a);
        myMapper->writeCPU(0x03F1, a);
        a = 0x20;
        myMapper->writeCPU(0x03D2, a);
        myMapper->writeCPU(0x03D3, a);
        myMapper->writeCPU(0x0396, 0x08);
        a = 0x28;
        myMapper->writeCPU(0x0397, a);
    }
    goto L_00409B;
    while (true) {
        a = 0x02;
        pushAddress(0x809A);
        SUB_01FFD2_SwitchCHRBank0();
    L_00409B:
        a = myMapper->readCPU(0x0040);
        opAND(0xFE);
        myMapper->writeCPU(PPU_CTRL, a);
        x = myMapper->readCPU(0x05CA);
        a = myMapper->readCPU(0x8181 + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_004143;
        }
        myMapper->writeCPU(0x03FD, a);
        a = myMapper->readCPU(0x003F);
        opAND(myMapper->readCPU(0x05A2));
        if (flgZ) {
            opINC(0x05CA, 1);
        }
    L_0040BA:
        wait(2);
        needWaitScanline = true;
        waitScanline = 32;
        wait(3);
        if (myMapper->readCPU(0x03FD) == 0x18) {
            a = 0x16;
            pushAddress(0x80E7);
            jump(0xEA16);
            if (handleReturnAddress(poppedEntry.value, 0x80E7)) return;
        }
        a = myMapper->readCPU(0x05AC);
        if (a == 0xFF) {
            pushAddress(0x80F1);
            jump(0xF822);
            if (handleReturnAddress(poppedEntry.value, 0x80F1)) return;
        }
        a = 0x04;
        myMapper->writeCPU(0x0028, a);
        y = 0x00;
        pushAddress(0x80FA);
        jump(0xCA70);
        if (handleReturnAddress(poppedEntry.value, 0x80FA)) return;
        x = myMapper->readCPU(0x0589);
        setLoadFlag(x);
        if (!flgN) {
            y = 0x11;
            pushAddress(0x8104);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x8104)) return;
            y = 0x12;
            pushAddress(0x8109);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x8109)) return;
            pushAddress(0x810C);
            jump(0xCA60);
            if (handleReturnAddress(poppedEntry.value, 0x810C)) return;
        }
        pushAddress(0x810F);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x810F)) return;
        pushAddress(0x8112);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x8112)) return;
        a = myMapper->readCPU(0x003F);
        opLSR_A(1);
        if (flgC) {
            a = myMapper->readCPU(0x05D1);
            if (a == 0xFE) {
                a = myMapper->readCPU(0x03DF);
                setLoadFlag(a);
                if (!flgN) {
                    opINC(0x03C1, 1);
                    if (flgZ) {
                        opINC(0x03DF, 1);
                    }
                }
            }
        }
        pushAddress(0x812E);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x812E)) return;
        pushAddress(0x8131);
        jump(0xEA36);
        if (handleReturnAddress(poppedEntry.value, 0x8131)) return;
        a = myMapper->readCPU(0x000D);
        setLoadFlag(a);
        if (flgZ) {
            goto L_004138;
        }
        myMapper->writeCPU(0x000B, a);
    L_004138:
        pushAddress(0x813A);
        jump(0xDBB3);
        if (handleReturnAddress(poppedEntry.value, 0x813A)) return;
        a = 0x06;
        pushAddress(0x813F);
        SUB_01FFAA_SwitchCHRBank1();
    }
L_004143:
    if (myMapper->readCPU(0x05AC) == 0xFF) {
        a = myMapper->readCPU(0x0091);
        if (a == 0xFF) {
            a = myMapper->readCPU(0x0547);
            setLoadFlag(a);
            if (flgZ) {
                goto L_004164;
            }
            opDEC(0x0547, 1);
            if (a != 0x32) {
                goto L_004161;
            }
            a = 0x0F;
            pushAddress(0x8160);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x8160)) return;
        }
    L_004161:
        goto L_0040BA;
    }
L_004164:
    a = 0x00;
    myMapper->writeCPU(0x00B9, a);
    myMapper->writeCPU(0x004C, a);
    myMapper->writeCPU(0x05CA, a);
    myMapper->writeCPU(0x0486, a);
    myMapper->writeCPU(0x0487, a);
    myMapper->writeCPU(0x001E, myMapper->readCPU(0x058A));
    myMapper->writeCPU(0x001F, myMapper->readCPU(0x058B));
    a = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_0041B3() {
    pushAddress(0x81B5);
    jump(0xDE68);
    if (handleReturnAddress(poppedEntry.value, 0x81B5)) return;
    pushAddress(0x81B8);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0x81B8)) return;
    pushAddress(0x81BB);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0x81BB)) return;
    pushAddress(0x81BE);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0x81BE)) return;
    pushAddress(0x81C1);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x81C1)) return;
    myMapper->writeCPU(0x05D3, 0x07);
    myMapper->writeCPU(0x058D, 0x03);
    x = 0x00;
    myMapper->writeCPU(0x0589, 0x00);
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    if (a != 0x01) {
        x = 0x16;
        if (a != 0x02) {
            myMapper->writeCPU(0x0589, 0xFF);
            y = 0x01;
            myMapper->writeCPU(0x058D, y);
            x = 0x2C;
            if (a == 0x13) {
                goto L_004219;
            }
            myMapper->writeCPU(0x058D, 0x03);
            y = 0x02;
            myMapper->writeCPU(0x0589, y);
            x = 0x42;
            if (a == 0x04) {
                goto L_004233;
            }
            y = 0x04;
            myMapper->writeCPU(0x0589, y);
            x = 0x58;
            if (a == 0x06) {
                goto L_004233;
            }
            y = 0x08;
            myMapper->writeCPU(0x058D, y);
            x = 0x6E;
            opCMP(a, 0x07);
            if (flgZ) {
                goto L_004233;
            }
            popAddress();
            return;
        }
    }
L_004219:
    myMapper->writeCPU(0x05BF, 0x16);
    myMapper->writeCPU(0x05C0, 0x1A);
    myMapper->writeCPU(0x05C1, 0x52);
    a = 0x36;
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x822F);
    jump(0x824D);
    if (handleReturnAddress(poppedEntry.value, 0x822F)) return;
    jump(0x82E8);
    return;
L_004233:
    myMapper->writeCPU(0x05BF, 0x33);
    myMapper->writeCPU(0x05C0, 0x40);
    myMapper->writeCPU(0x05C1, 0x45);
    a = 0x49;
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x8249);
    jump(0x824D);
    if (handleReturnAddress(poppedEntry.value, 0x8249)) return;
    jump(0x82E8);
    return;
}

void game::SUB_00424D() {
    myMapper->writeCPU(0x041B, 0x06);
    a = 0x00;
    myMapper->writeCPU(0x05B5, a);
    myMapper->writeCPU(0x05CD, a);
    myMapper->writeCPU(0x03FD, a);
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
    myMapper->writeCPU(0x05D2, a);
    myMapper->writeCPU(0x05D1, a);
    myMapper->writeCPU(0x05D0, a);
    myMapper->writeCPU(0x059D, a);
    myMapper->writeCPU(0x0091, 0x64);
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x8498 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x8499 + x));
    myMapper->writeCPU(0x0587, myMapper->readCPU(0x849A + x));
    myMapper->writeCPU(0x0588, myMapper->readCPU(0x849B + x));
    myMapper->writeCPU(0x05BE, myMapper->readCPU(0x849C + x));
    myMapper->writeCPU(0x0092, myMapper->readCPU(0x849D + x));
    myMapper->writeCPU(0x0093, myMapper->readCPU(0x849E + x));
    myMapper->writeCPU(0x000C, myMapper->readCPU(0x849F + x));
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x84A0 + x));
    myMapper->writeCPU(0x009A, myMapper->readCPU(0x84A1 + x));
    myMapper->writeCPU(0x009B, myMapper->readCPU(0x84A2 + x));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x84A3 + x));
    myMapper->writeCPU(0x009D, myMapper->readCPU(0x84A4 + x));
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x84A5 + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x84A6 + x));
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x84A7 + x));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x84A8 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x84A9 + x));
    a = myMapper->readCPU(0x84AA + x);
    myMapper->writeCPU(0x000F, a);
    y = myMapper->readCPU(0x84AB + x);
    pushAddress(0x82DA);
    jump(0x83D9);
    if (handleReturnAddress(poppedEntry.value, 0x82DA)) return;
    a = myMapper->readCPU(0x84AC + x);
    y = myMapper->readCPU(0x84AD + x);
    x = a;
    pushAddress(0x82E4);
    jump(0xDC63);
    if (handleReturnAddress(poppedEntry.value, 0x82E4)) return;
    jump(0xDEF4);
    return;
}

void game::SUB_0042E8() {
    a = myMapper->readCPU(0x058D);
    pushAddress(0x82ED);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x82ED)) return;
    myMapper->writeCPU(0x0005, 0x9E);
    myMapper->writeCPU(0x0006, 0xE9);
    myMapper->writeCPU(0x0007, 0xDE);
    a = 0xE9;
    myMapper->writeCPU(0x0008, a);
    pushAddress(0x8300);
    jump(0xDD83);
    if (handleReturnAddress(poppedEntry.value, 0x8300)) return;
    pushAddress(0x8303);
    jump(0x841D);
    if (handleReturnAddress(poppedEntry.value, 0x8303)) return;
    a = myMapper->readCPU(0x0042);
    opORA(0x80);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    a = 0x00;
    myMapper->writeCPU(0x05AF, a);
    myMapper->writeCPU(0x003F, a);
    pushAddress(0x8317);
    jump(0xDCFD);
    if (handleReturnAddress(poppedEntry.value, 0x8317)) return;
    pushAddress(0x831A);
    jump(0x802B);
    if (handleReturnAddress(poppedEntry.value, 0x831A)) return;
    a = 0x00;
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x05AF, a);
    goto L_004342;
L_004325:
    pushAddress(0x8327);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0x8327)) return;
    a = myMapper->readCPU(0x05D1);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0011);
    pushAddress(0x8332);
    SUB_01FFAA_SwitchCHRBank1();
    a = 0x02;
    pushAddress(0x8337);
    SUB_01FFD2_SwitchCHRBank0();
    a = myMapper->readCPU(0x0040);
    opAND(0xFE);
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0x8341);
    jump(0xDBDF);
    if (handleReturnAddress(poppedEntry.value, 0x8341)) return;
L_004342:
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x8349);
        jump(0xE6E4);
        if (handleReturnAddress(poppedEntry.value, 0x8349)) return;
        pushAddress(0x834C);
        jump(0xE7DF);
        if (handleReturnAddress(poppedEntry.value, 0x834C)) return;
        pushAddress(0x834F);
        jump(0xE84A);
        if (handleReturnAddress(poppedEntry.value, 0x834F)) return;
        pushAddress(0x8352);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x8352)) return;
        pushAddress(0x8355);
        jump(0xE685);
        if (handleReturnAddress(poppedEntry.value, 0x8355)) return;
        pushAddress(0x8358);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x8358)) return;
        pushAddress(0x835B);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x835B)) return;
        pushAddress(0x835E);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0x835E)) return;
    }
	wait(2);
    needWaitScanline = true;
    waitScanline = 32;
    wait(3);
    a = myMapper->readCPU(0x00B9);
    if (a == 0x10) {
        a = myMapper->readCPU(0x058C);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x058C, 1);
            a = myMapper->readCPU(0x058D);
            pushAddress(0x8394);
            jump(0xE9E6);
            if (handleReturnAddress(poppedEntry.value, 0x8394)) return;
            a = 0x0F;
            pushAddress(0x8399);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x8399)) return;
            goto L_0043D6;
        }
        opINC(0x058C, 1);
        pushAddress(0x83A2);
        jump(0xEA06);
        if (handleReturnAddress(poppedEntry.value, 0x83A2)) return;
        a = 0x0E;
        pushAddress(0x83A7);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x83A7)) return;
    }
    pushAddress(0x824F);
    jump(0xEA36);
    if (handleReturnAddress(poppedEntry.value, 0x824F)) return;
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x83B2);
        jump(0xE61C);
        if (handleReturnAddress(poppedEntry.value, 0x83B2)) return;
        pushAddress(0x83B5);
        jump(0x8C65);
        if (handleReturnAddress(poppedEntry.value, 0x83B5)) return;
        pushAddress(0x83B8);
        jump(0x8540);
        if (handleReturnAddress(poppedEntry.value, 0x83B8)) return;
        x = myMapper->readCPU(0x0654);
        setLoadFlag(x);
        if (flgZ) {
            goto L_0043CA;
        }
        myMapper->writeCPU(0x0385 + x, myMapper->readCPU(0x0385));
        a = myMapper->readCPU(0x03A3);
        myMapper->writeCPU(0x03A3 + x, a);
    L_0043CA:
        pushAddress(0x83CC);
        jump(0xE1F0);
        if (handleReturnAddress(poppedEntry.value, 0x83CC)) return;
        pushAddress(0x83CF);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x83CF)) return;
        pushAddress(0x83D2);
        jump(0xCA15);
        if (handleReturnAddress(poppedEntry.value, 0x83D2)) return;
        pushAddress(0x83D5);
        jump(0x9FCD);
        if (handleReturnAddress(poppedEntry.value, 0x83D5)) return;
    }
L_0043D6:
    goto L_004325;
}

void game::SUB_0043D9() {
    myMapper->writeCPU(0x05AC, x);
    x = 0x00;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0x83ED + y));
        opINX(1);
        opINY(1);
    } while (x != 0x10);
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_00441D() {
    a = myMapper->readCPU(0x0042);
    opAND(0x7F);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    a = myMapper->readCPU(SCROLL_FINE);
    opPHA();
    a = myMapper->readCPU(SCROLL_LARGE);
    opPHA();
    myMapper->writeCPU(SCROLL_LARGE, 0x00);
    a = myMapper->readCPU(0x00A0);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    myMapper->writeCPU(SCROLL_FINE, a);
    opDEC(SCROLL_LARGE, 1);
    myMapper->writeCPU(0x05AF, 0x08);
    do {
        a = myMapper->readCPU(0x00A0);
        pushAddress(0x8459);
        jump(0xE20C);
        if (handleReturnAddress(poppedEntry.value, 0x8459)) return;
        pushAddress(0x845C);
        jump(0x9BCF);
        if (handleReturnAddress(poppedEntry.value, 0x845C)) return;
        pushAddress(0x845F);
        jump(0x9FCD);
        if (handleReturnAddress(poppedEntry.value, 0x845F)) return;
        pushAddress(0x8462);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8462)) return;
        pushAddress(0x8465);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8465)) return;
        pushAddress(0x8468);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8468)) return;
        pushAddress(0x846B);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x846B)) return;
        pushAddress(0x846E);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x846E)) return;
        pushAddress(0x8471);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8471)) return;
        pushAddress(0x8474);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8474)) return;
        pushAddress(0x8477);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8477)) return;
        flgC = false;
        a = myMapper->readCPU(SCROLL_FINE);
        opADC(0x20);
        myMapper->writeCPU(SCROLL_FINE, a);
        if (!flgC) {
            goto L_004486;
        }
        opINC(SCROLL_LARGE, 1);
    L_004486:
        opINC(0x00A0, 1);
        opDEC(0x05AF, 1);
    } while (!flgN);
    opDEC(0x00A0, 1);
    opPLA();
    myMapper->writeCPU(SCROLL_LARGE, a);
    opPLA();
    myMapper->writeCPU(SCROLL_FINE, a);
    popAddress();
}

void game::SUB_004540() {
    y = myMapper->readCPU(0x0051);
    if (myMapper->readCPU(0x0059 + y) == 0x04) {
        a = myMapper->readCPU(0x0385);
        opORA(myMapper->readCPU(0x03A3));
        if (flgZ) {
            if (myMapper->readCPU(0x05C3) < 0x10) {
                goto L_004564;
            }
            myMapper->writeCPU(0x0059 + y, myMapper->readCPU(0x058E));
            a = 0xFE;
            myMapper->writeCPU(0x05D1, a);
            popAddress();
            return;
        }
    }
L_004564:
    if (myMapper->readCPU(0x05D0) != 0) {
        if (myMapper->readCPU(0x0439) < 0xC0) {
            goto L_00458A;
        }
        x = 0x00;
        myMapper->writeCPU(0x05A3, x);
        myMapper->writeCPU(0x05A4, x);
        x = myMapper->readCPU(0x0051);
        if (myMapper->readCPU((0x0059 + x) & 0x00ff) == 0x07) {
            if (myMapper->readCPU(0x0476) != 0) {
                goto L_00458A;
            }
        }
        myMapper->writeCPU(0x05D0, 0xFF);
    }
L_00458A:
    a = 0x00;
    myMapper->writeCPU(0x05CF, a);
    pushAddress(0x8591);
    jump(0x8B5D);
    if (handleReturnAddress(poppedEntry.value, 0x8591)) return;
    a = myMapper->readCPU(0x05D2);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
            if (!flgN) {
                goto L_0045B4;
            }
        }
        a = myMapper->readCPU(0x05C3);
        if (a != 0x01) {
            a = myMapper->readCPU(0x05C4);
            if (a != 0x01) {
                goto L_0045B4;
            }
        }
        x = 0x00;
        jump(0x8B37);
        return;
    L_0045B4:
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
        }
        else {
            opBIT(myMapper->readCPU(0x059F));
            if (flgN) {
            }
            else {
                a = myMapper->readCPU(0x05C3);
                myMapper->writeCPU(0x05C6, a);
                if (a < 0x10) {
                    if (a < 0x08) {
                        goto L_0045D5;
                    }
                    goto L_0046B9;
                L_0045D5:
                    a = myMapper->readCPU(0x059D);
                    setLoadFlag(a);
                    if (flgN) {
                        goto L_0046C6;
                    }
                    x = 0x00;
                    y = 0x00;
                    jump(0x8B1E);
                    return;
                }
                flgC = true;
                opSBC(0x10);
                x = a;
                if (myMapper->readCPU(0x05D0) == 0xFF) {
                    a = 0xFF;
                    myMapper->writeCPU(0x05D1, a);
                    popAddress();
                    return;
                }
                a = myMapper->readCPU(0x8B98 + x);
                myMapper->writeCPU(0x05AA, a);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x05AB, a);
                myMapper->writeCPU(0x05A6, myMapper->readCPU(0x8BB0 + x));
                myMapper->writeCPU(0x05A7, myMapper->readCPU(0x8BC8 + x));
                myMapper->writeCPU(0x05A8, myMapper->readCPU(0x8BE0 + x));
                if (myMapper->readCPU(0x059D) != 0) {
                    a = 0x25;
                    pushAddress(0x861E);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x861E)) return;
                    x = 0x18;
                    pushAddress(0x8623);
                    jump(0x8B01);
                    if (handleReturnAddress(poppedEntry.value, 0x8623)) return;
                }
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
                a = myMapper->readCPU(0x05C6);
                if (a == 0x1E) {
                    if (myMapper->readCPU(0x0483) != 0x11) {
                        goto L_004657;
                    }
                    a = myMapper->readCPU(0x0439);
                    flgC = false;
                    opADC(0x18);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0447));
                    if (!flgN) {
                        if (a >= 0x38) {
                            goto L_004657;
                        }
                        a = 0x01;
                        myMapper->writeCPU(0x0573, a);
                        goto L_0046C6;
                    }
                L_004657:
                    a = 0x01;
                    myMapper->writeCPU(0x0574, a);
                    goto L_0046C6;
                }
                myMapper->writeCPU(0x05A5, 0x00);
                x = 0x01;
                if (a != 0x18) {
                    x = 0x02;
                    if (a != 0x19) {
                        goto L_00467B;
                    }
                }
                myMapper->writeCPU(0x05A5, x);
                a = 0x1A;
                pushAddress(0x8677);
                jump(0xEA16);
                if (handleReturnAddress(poppedEntry.value, 0x8677)) return;
                goto L_0046C6;
            L_00467B:
                if (a == 0x1D) {
                    a = 0x04;
                    myMapper->writeCPU(0x05A4, a);
                    myMapper->writeCPU(0x05AA, a);
                    a = 0x00;
                    myMapper->writeCPU(0x05A3, a);
                    x = 0xF7;
                    y = 0x00;
                    pushAddress(0x8692);
                    jump(0x8B0F);
                    if (handleReturnAddress(poppedEntry.value, 0x8692)) return;
                    a = 0x0C;
                    myMapper->writeCPU(0x05A7, a);
                    myMapper->writeCPU(0x05A6, a);
                    a = 0x15;
                    pushAddress(0x869F);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x869F)) return;
                    goto L_0046C6;
                }
                x = 0xFD;
                myMapper->writeCPU(0x05CB, x);
                if (a == 0x1C) {
                    x = myMapper->readCPU(0x05B8);
                    setLoadFlag(x);
                    if (flgN) {
                        x = 0x14;
                        myMapper->writeCPU(0x05B8, x);
                    }
                }
                goto L_0046C6;
            L_0046B9:
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
            }
        }
    }
L_0046C6:
    y = myMapper->readCPU(0x004B);
    a = y;
    opAND(0x01);
    if (!flgZ) {
        a = 0x00;
        myMapper->writeCPU(0x05CD, a);
        pushAddress(0x86D4);
        jump(0xE195);
        if (handleReturnAddress(poppedEntry.value, 0x86D4)) return;
    }
    a = y;
    opAND(0x02);
    if (!flgZ) {
        a = 0x80;
        myMapper->writeCPU(0x05CD, a);
        pushAddress(0x86E1);
        jump(0xE195);
        if (handleReturnAddress(poppedEntry.value, 0x86E1)) return;
    }
    if (myMapper->readCPU(0x059D) == 0) {
        if (myMapper->readCPU(0x0654) != 0) {
            goto L_004718;
        }
        a = y;
        opAND(0x04);
        if (!flgZ) {
            if (myMapper->readCPU(0x05C3) == 0x17) {
                goto L_00470A;
            }
            if (myMapper->readCPU(0x05C9) != 0) {
                goto L_004727;
            }
            x = 0x15;
            a = 0x10;
            myMapper->writeCPU(0x05C9, a);
            pushAddress(0x8706);
            jump(0x8B06);
            if (handleReturnAddress(poppedEntry.value, 0x8706)) return;
            goto L_004727;
        L_00470A:
            a = myMapper->readCPU(0x058E);
            y = myMapper->readCPU(0x0051);
            myMapper->writeCPU(0x0059 + y, a);
            a = 0xFE;
            myMapper->writeCPU(0x05D1, a);
            popAddress();
            return;
        }
    }
L_004718:
    if (myMapper->readCPU(0x05C9) != 0) {
        myMapper->writeCPU(0x05C9, 0x00);
        myMapper->writeCPU(0x05CA, 0x18);
    }
L_004727:
    a = myMapper->readCPU(0x004C);
    opAND(0x80);
    if (!flgZ) {
        if (myMapper->readCPU(0x0655) == 0) {
            goto L_004743;
        }
        a = myMapper->readCPU(0x059D);
        setLoadFlag(a);
        if (flgZ) {
            x = 0xFB;
            y = 0x00;
            pushAddress(0x873D);
            jump(0x8B0F);
            if (handleReturnAddress(poppedEntry.value, 0x873D)) return;
            a = 0x10;
            pushAddress(0x8742);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x8742)) return;
        }
    }
L_004743:
    if (myMapper->readCPU(0x05A0) != 0) {
        opDEC(0x05A0, 1);
        a = y;
        opAND(0x80);
        if (!flgZ) {
            if (myMapper->readCPU(0x059E) == 0xF8) {
                goto L_004765;
            }
            flgC = true;
            a = myMapper->readCPU(0x059E);
            opSBC(0x01);
            myMapper->writeCPU(0x059E, a);
            if (!flgC) {
                opDEC(0x059F, 1);
            }
        }
    }
L_004765:
    a = myMapper->readCPU(0x059D);
    setLoadFlag(a);
    if (!flgZ) {
        opBIT(myMapper->readCPU(0x059F));
        if (flgN) {
            if (myMapper->readCPU(0x05C4) < 0x10) {
                goto L_004781;
            }
            a = 0x00;
            myMapper->writeCPU(0x059F, a);
            myMapper->writeCPU(0x05A0, a);
            myMapper->writeCPU(0x059E, a);
        }
    L_004781:
        flgC = false;
        a = myMapper->readCPU(0x03C1);
        opADC(myMapper->readCPU(0x059E));
        myMapper->writeCPU(0x03C1, a);
        a = myMapper->readCPU(0x03DF);
        opADC(myMapper->readCPU(0x059F));
        myMapper->writeCPU(0x03DF, a);
        if (a == 0x02) {
            myMapper->writeCPU(0x05D1, 0x02);
        }
        opINC(0x05A9, 1);
        a = myMapper->readCPU(0x05A9);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x059E) == 0x08) {
                goto L_0047B6;
            }
            opINC(0x059E, 1);
            if (flgZ) {
                opINC(0x059F, 1);
            }
        }
    }
L_0047B6:
    a = myMapper->readCPU(0x0654);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x004C);
        opAND(0x40);
        if (!flgZ) {
            if (myMapper->readCPU(0x0655) == 0) {
                goto L_0047D5;
            }
            x = 0x01;
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (!flgZ) {
                x = 0x07;
            }
            pushAddress(0x87D1);
            jump(0x8B01);
            if (handleReturnAddress(poppedEntry.value, 0x87D1)) return;
            goto L_0047E1;
        L_0047D5:
            x = 0x0D;
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (!flgZ) {
                x = 0x11;
            }
            pushAddress(0x87E0);
            jump(0x8B01);
            if (handleReturnAddress(poppedEntry.value, 0x87E0)) return;
        }
    }
L_0047E1:
    pushAddress(0x87E3);
    jump(0x883B);
    if (handleReturnAddress(poppedEntry.value, 0x87E3)) return;
    a = myMapper->readCPU(0x05A1);
    setLoadFlag(a);
    if (flgZ) {
        y = 0x05;
        x = 0x01;
        a = myMapper->readCPU(0x05A4);
        setLoadFlag(a);
        if (!flgN) {
            x = 0x03;
        }
        pushAddress(0x87F6);
        jump(0xE587);
        if (handleReturnAddress(poppedEntry.value, 0x87F6)) return;
        myMapper->writeCPU(0x05C7, a);
        if (a < 0x08) {
            a = myMapper->readCPU(0x059D);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00481F;
            }
            a = myMapper->readCPU(0x059F);
            setLoadFlag(a);
            if (flgN) {
                goto L_00481F;
            }
            y = 0x06;
            pushAddress(0x880C);
            jump(0xE587);
            if (handleReturnAddress(poppedEntry.value, 0x880C)) return;
            myMapper->writeCPU(0x05C8, a);
            if (a < 0x08) {
                goto L_00481F;
            }
        }
        a = 0x00;
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
        myMapper->writeCPU(0x05A5, a);
    }
L_00481F:
    pushAddress(0x8821);
    jump(0xE0C9);
    if (handleReturnAddress(poppedEntry.value, 0x8821)) return;
    pushAddress(0x8824);
    jump(0xDED2);
    if (handleReturnAddress(poppedEntry.value, 0x8824)) return;
    opCMP(y, myMapper->readCPU(SCROLL_LARGE));
    if (!flgZ) {
        if (flgC) {
            goto L_004834;
        }
    }
    else {
        if (x < myMapper->readCPU(SCROLL_FINE)) {
            goto L_00483A;
        }
    L_004834:
        myMapper->writeCPU(SCROLL_FINE, x);
        myMapper->writeCPU(SCROLL_LARGE, y);
    }
L_00483A:
    popAddress();
}

void game::SUB_00483B() {
    x = myMapper->readCPU(0x05CA);
    setLoadFlag(x);
    if (flgZ) {
        jump(0x8979);
        return;
    }
    a = myMapper->readCPU(0x851C + x);
    setLoadFlag(a);
    if (!flgN) {
        x = a;
        opAND(0x3F);
        opORA(myMapper->readCPU(0x05CD));
        myMapper->writeCPU(0x03FD, a);
        if (x != 0x0A) {
            if (x != 0x04) {
                goto L_00485C;
            }
        }
        pushAddress(0x885B);
        jump(0x8896);
        if (handleReturnAddress(poppedEntry.value, 0x885B)) return;
    L_00485C:
        opDEC(0x05CE, 1);
        if (flgN) {
            goto L_004875;
        }
        popAddress();
        return;
    }
    x = 0x00;
    myMapper->writeCPU(0x05CA, x);
    if (myMapper->readCPU(0x059D) == 0) {
        goto L_004874;
    }
    a = 0x1F;
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
L_004874:
    popAddress();
    return;
L_004875:
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    opINC(0x05CA, 1);
    if (x == 0x05) {
        jump(0x88AD);
        return;
    }
    if (x == 0x0B) {
        jump(0x88AD);
        return;
    }
    if (x == 0x07) {
        jump(0x88F0);
        return;
    }
    if (x == 0x0D) {
        jump(0x88F0);
        return;
    }
    if (x == 0x47) {
        jump(0x88F0);
        return;
    }
    if (x == 0x4D) {
        jump(0x88F0);
        return;
    }
    popAddress();
}

void game::SUB_004896() {
    y = 0x00;
    a = myMapper->readCPU(0x0656);
    setLoadFlag(a);
    if (!flgN) {
        goto L_00489E;
    }
    opDEY(1);
L_00489E:
    flgC = false;
    opADC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0385, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3));
    myMapper->writeCPU(0x03A3, a);
    popAddress();
}

void game::SUB_0048AD() {
    y = 0x01;
    myMapper->writeCPU(0x05BC, y);
    pushAddress(0x88B4);
    jump(0x8A0B);
    if (handleReturnAddress(poppedEntry.value, 0x88B4)) return;
    if (!flgZ) {
        y = 0x02;
        pushAddress(0x88BB);
        jump(0x8A0B);
        if (handleReturnAddress(poppedEntry.value, 0x88BB)) return;
        if (!flgZ) {
            y = 0x06;
            pushAddress(0x88C2);
            jump(0x8A0B);
            if (handleReturnAddress(poppedEntry.value, 0x88C2)) return;
            if (!flgZ) {
                y = 0x07;
                pushAddress(0x88C9);
                jump(0x8A0B);
                if (handleReturnAddress(poppedEntry.value, 0x88C9)) return;
                if (!flgZ) {
                    popAddress();
                    return;
                }
            }
        }
    }
    a = 0x0D;
    pushAddress(0x88D1);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x88D1)) return;
    a = myMapper->readCPU(0x050B + y);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x050B + y, a);
    if (flgN) {
        x = 0x00;
        jump(0x941F);
        return;
    }
    x = y;
    y = 0x1C;
    a = myMapper->readCPU(0x05C9);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0048ED;
    }
    y = 0x20;
L_0048ED:
    jump(0x94F3);
    return;
}

void game::SUB_0048F0() {
    a = myMapper->readCPU(0x0595);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x0596, 1);
        if (flgZ) {
            myMapper->writeCPU(0x0595, 0x00);
            a = 0x02;
            myMapper->writeCPU(0x0594, a);
        }
        if (x >= 0x40) {
            if (a == 0x04) {
                goto L_004959;
            }
            if (a == 0x05) {
                goto L_004959;
            }
            x = 0x00;
            y = 0x03;
            if (myMapper->readCPU(0x0475 + y) == 0) {
                a = myMapper->readCPU(0x0595);
                if (a == 0x01) {
                    goto L_004943;
                }
                if (a == 0x02) {
                    goto L_004925;
                }
            }
        }
        popAddress();
        return;
    L_004925:
        pushAddress(0x895B);
        jump(0x8AAA);
        if (handleReturnAddress(poppedEntry.value, 0x895B)) return;
        y = 0x04;
        x = 0xFA;
        pushAddress(0x892E);
        jump(0x8AAA);
        if (handleReturnAddress(poppedEntry.value, 0x892E)) return;
        y = 0x05;
        x = 0x06;
        pushAddress(0x8935);
        jump(0x8AAA);
        if (handleReturnAddress(poppedEntry.value, 0x8935)) return;
        a = 0x00;
        myMapper->writeCPU(0x0497, a);
        myMapper->writeCPU(0x0498, a);
        a = 0x07;
        jump(0xEA1B);
        return;
    L_004943:
        pushAddress(0x8973);
        jump(0x8AAA);
        if (handleReturnAddress(poppedEntry.value, 0x8973)) return;
        x = 0xFA;
        y = 0x04;
        pushAddress(0x894C);
        jump(0x8AAA);
        if (handleReturnAddress(poppedEntry.value, 0x894C)) return;
        x = 0x06;
        y = 0x05;
        pushAddress(0x8953);
        jump(0x8AAA);
        if (handleReturnAddress(poppedEntry.value, 0x8953)) return;
        a = 0x08;
        jump(0xEA1B);
        return;
    }
L_004959:
    x = 0x00;
    y = 0x03;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x04;
        if (myMapper->readCPU(0x0475 + y) != 0) {
            y = 0x05;
            if (myMapper->readCPU(0x0475 + y) == 0) {
                goto L_004971;
            }
            popAddress();
            return;
        }
    }
L_004971:
    a = 0x06;
    pushAddress(0x8975);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x8975)) return;
    jump(0x8AAA);
    return;
}

void game::SUB_004979() {
    a = 0x09;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        if (myMapper->readCPU(0x0654) != 0) {
            goto L_00498F;
        }
        if (myMapper->readCPU(0x059D) == 0) {
            goto L_004998;
        }
        a = 0x1F;
        goto L_004991;
    L_00498F:
        a = 0x00;
    }
L_004991:
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    popAddress();
    return;
L_004998:
    a = myMapper->readCPU(0x05C3);
    opCMP(a, 0x11);
    if (!flgZ) {
        opCMP(a, 0x12);
        if (!flgZ) {
            goto L_0049A8;
        }
    }
    if (myMapper->readCPU(0x05CF) == 0) {
        goto L_00498F;
    }
L_0049A8:
    a = myMapper->readCPU(0x05A3);
    opORA(myMapper->readCPU(0x05A4));
    if (!flgZ) {
        opDEC(0x05A2, 1);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x05A4));
            if (flgN) {
                a = myMapper->readCPU(0x05A3);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x05A4);
                opEOR(0xFF);
                opADC(0x00);
            }
            else {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x05A3));
                a = myMapper->readCPU(0x05A4);
            }
            opROL_M(0x0000, 1);
            opROL_A(1);
            x = a;
            myMapper->writeCPU(0x05A2, myMapper->readCPU(0x8B93 + x));
            opINC(0x03FD, 1);
        }
    }
    a = myMapper->readCPU(0x03FD);
    opAND(0x03);
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    opAND(0x7F);
    if (a != myMapper->readCPU(0x00B8)) {
        myMapper->writeCPU(0x00B8, a);
        if (myMapper->readCPU(0x00FD) == 0) {
            x = 0x23;
            a = myMapper->readCPU(0x00B8);
            setLoadFlag(a);
            if (flgZ) {
                goto L_004A06;
            }
            x = 0x24;
            if (a != 0x02) {
                goto L_004A0A;
            }
        L_004A06:
            a = x;
            jump(0xEA1B);
            return;
        }
    }
L_004A0A:
    popAddress();
}

void game::SUB_004A0B() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x06) {
            goto L_004A72;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_004A72;
            }
            if (myMapper->readCPU(0x0529 + y) < 0x1C) {
                if (myMapper->readCPU(0x03DF) != 0) {
                    goto L_004A72;
                }
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(myMapper->readCPU(0x05C9));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x041B + y);
                if (a != 0x06) {
                    if (a != 0x07) {
                        goto L_004A75;
                    }
                }
                a = myMapper->readCPU(0x03C1 + y);
                flgC = false;
                opADC(0x20);
                flgC = true;
                opSBC(myMapper->readCPU(0x0000));
                if (!flgN) {
                    if (a >= 0x30) {
                        goto L_004A72;
                    }
                    flgC = true;
                    opBIT(myMapper->readCPU(0x03FD));
                    if (!flgN) {
                        goto L_004A64;
                    }
                    a = myMapper->readCPU(0x0439);
                    opSBC(myMapper->readCPU(0x0439 + y));
                    if (flgC) {
                        if (a >= 0x08) {
                            goto L_004A72;
                        }
                        do {
                            do {
                                a = 0x00;
                                setLoadFlag(a);
                                popAddress();
                                return;
                            L_004A64:
                                a = myMapper->readCPU(0x0439 + y);
                                opSBC(myMapper->readCPU(0x0439));
                                if (!flgC) {
                                    goto L_004A72;
                                }
                                opCMP(a, 0x10);
                            } while (flgZ);
                        } while (!flgC);
                    }
                }
            }
        }
    }
L_004A72:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
    return;
L_004A75:
    a = myMapper->readCPU(0x03C1 + y);
    flgC = false;
    opADC(0x08);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    if (flgC) {
        if (a >= 0x18) {
            goto L_004AA7;
        }
        flgC = true;
        opBIT(myMapper->readCPU(0x03FD));
        if (!flgN) {
            goto L_004A99;
        }
        a = myMapper->readCPU(0x0439);
        opSBC(myMapper->readCPU(0x0439 + y));
        if (flgC) {
            if (a >= 0x10) {
                goto L_004AA7;
            }
            do {
                do {
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                L_004A99:
                    a = myMapper->readCPU(0x0439 + y);
                    opSBC(myMapper->readCPU(0x0439));
                    if (!flgC) {
                        goto L_004AA7;
                    }
                    opCMP(a, 0x18);
                } while (flgZ);
            } while (!flgC);
        }
    }
L_004AA7:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_004AAA() {
    myMapper->writeCPU(0x04B1 + y, x);
    a = myMapper->readCPU(0x0385);
    opBIT(myMapper->readCPU(0x05CD));
    if (flgN) {
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        a = 0xFA;
        myMapper->writeCPU(0x0493 + y, a);
    }
    else {
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        myMapper->writeCPU(0x0493 + y, 0x06);
    }
    myMapper->writeCPU(0x03DF + y, myMapper->readCPU(0x03DF));
    a = 0x08;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        goto L_004AEE;
    }
    a = 0x18;
L_004AEE:
    flgC = false;
    opADC(myMapper->readCPU(0x03C1));
    myMapper->writeCPU(0x03C1 + y, a);
    myMapper->writeCPU(0x03FD + y, myMapper->readCPU(0x05CD));
    a = 0x02;
    myMapper->writeCPU(0x0475 + y, a);
    popAddress();
}

void game::SUB_004B01() {
    a = myMapper->readCPU(0x05CA);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x8B0E);
        return;
    }
    SUB_004B06();
    return;
}

void game::SUB_004B06() {
    myMapper->writeCPU(0x05CA, x);
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    SUB_004B0E();
    return;
}

void game::SUB_004B0E() {
    popAddress();
}

void game::SUB_004B0F() {
    if (myMapper->readCPU(0x05A1) != 0) {
        goto L_004B19;
    }
    a = myMapper->readCPU(0x05A6);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x8B1E);
        return;
    }
L_004B19:
    a = 0x40;
    myMapper->writeCPU(0x05A6, a);
    SUB_004B1E();
    return;
}

void game::SUB_004B1E() {
    myMapper->writeCPU(0x05A0, y);
    myMapper->writeCPU(0x059E, x);
    x = 0x00;
    myMapper->writeCPU(0x05A9, x);
    opBIT(myMapper->readCPU(0x059E));
    if (!flgN) {
        goto L_004B2F;
    }
    opDEX(1);
L_004B2F:
    myMapper->writeCPU(0x059F, x);
    opDEX(1);
    myMapper->writeCPU(0x059D, x);
    popAddress();
}

void game::SUB_004B37() {
    pushAddress(0x8B39);
    jump(0x8B45);
    if (handleReturnAddress(poppedEntry.value, 0x8B39)) return;
    a = 0x1F;
    pushAddress(0x8B3E);
    jump(0xEA16);
    if (handleReturnAddress(poppedEntry.value, 0x8B3E)) return;
    a = 0xFF;
    myMapper->writeCPU(0x05D2, a);
    popAddress();
}

void game::SUB_004B45() {
    y = 0x02;
    if (!(myMapper->readCPU(0x0493 + x) & 0x80)) {
        goto L_004B4E;
    }
    y = 0xFE;
L_004B4E:
    myMapper->writeCPU(0x05A4, y);
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    x = 0xFB;
    y = 0x00;
    jump(0x8B0F);
    return;
}

void game::SUB_004B5D() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF));
    y = myMapper->readCPU(0x03C1);
    flgC = true;
    a = myMapper->readCPU(0x0385);
    opSBC(0x04);
    x = a;
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    myMapper->writeCPU(0x0095, a);
    pushAddress(0x8B75);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x8B75)) return;
    x = 0x02;
    y = 0x06;
    pushAddress(0x8B7C);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8B7C)) return;
    myMapper->writeCPU(0x05C3, a);
    y = 0x00;
    pushAddress(0x8B84);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8B84)) return;
    myMapper->writeCPU(0x05C4, a);
    x = 0x02;
    y = 0x05;
    pushAddress(0x8B8E);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8B8E)) return;
    myMapper->writeCPU(0x05C5, a);
    popAddress();
}

void game::SUB_004C65() {
    pushAddress(0x8C67);
    jump(0x9BCF);
    if (handleReturnAddress(poppedEntry.value, 0x8C67)) return;
    x = 0x00;
    myMapper->writeCPU(0x0659, x);
    myMapper->writeCPU(0x0654, x);
    myMapper->writeCPU(0x05BC, x);
    myMapper->writeCPU(0x05A1, x);
    opDEX(1);
    myMapper->writeCPU(0x0655, x);
    x = 0x01;
    myMapper->writeCPU(0x05CC, myMapper->readCPU(0x0587));
    SUB_004C82();
    return;
}

void game::SUB_004C82() {
    myMapper->writeCPU(0x05AC, x);
    y = myMapper->readCPU(0x0475 + x);
    setLoadFlag(y);
    if (flgZ) {
        jump(0x8C9D);
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x8C1B + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x8C40 + y));
    a = 0x8C;
    opPHA();
    a = 0x9C;
    opPHA();
    pushManualAddress(0x8C9C);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_004C9D() {
    opINC(0x05AF, 1);
    x = myMapper->readCPU(0x05AC);
    opINX(1);
    opDEC(0x05CC, 1);
    if (!flgZ) {
        jump(0x8C82);
        return;
    }
    SUB_004CA9();
    return;
}

void game::SUB_004CA9() {
    a = myMapper->readCPU(0x003F);
    opADC(myMapper->readCPU(0x05AF));
    myMapper->writeCPU(0x05AF, a);
    popAddress();
}

void game::SUB_004CB2() {
    myMapper->writeCPU(0x04B1 + x, 0x08);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x0493 + x, myMapper->readCPU(0x004E));
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0385 + x, a);
    if (!flgC) {
        goto L_004CCF;
    }
    opINC(0x03A3 + x, 1);
L_004CCF:
    opINC(0x0475 + x, 1);
    SUB_004CD2();
    return;
}

void game::SUB_004CD2() {
    a = myMapper->readCPU(0x03FD + x);
    if (a == 0xFF) {
        opINC(0x0493 + x, 1);
        a = myMapper->readCPU(0x0493 + x);
        opAND(0xB3);
        if (!flgZ) {
            goto L_004D29;
        }
        myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
        a = 0x18;
        pushAddress(0x8CED);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x8CED)) return;
    }
    y = 0x09;
    pushAddress(0x8CF2);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x8CF2)) return;
    if (!flgN) {
        pushAddress(0x8CF7);
        jump(0x8B37);
        if (handleReturnAddress(poppedEntry.value, 0x8CF7)) return;
        x = myMapper->readCPU(0x05AC);
    }
    myMapper->writeCPU(0x041B + x, 0x07);
    a = myMapper->readCPU(0x003F);
    opAND(0x04);
    opLSR_A(2);
    opADC(0x06);
    myMapper->writeCPU(0x03FD + x, a);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    opDEC(0x0565 + x, 1);
    if (flgZ) {
        goto L_004D1B;
    }
    popAddress();
    return;
L_004D1B:
    myMapper->writeCPU(0x03FD + x, 0xFF);
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x04B1 + x, a);
L_004D29:
    popAddress();
}

void game::SUB_004D2A() {
    myMapper->writeCPU(0x04CF + x, 0x00);
    a = 0x00;
    y = 0x00;
    jump(0x8D50);
    return;
}

void game::SUB_004D36() {
    myMapper->writeCPU(0x04CF + x, 0x00);
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x66);
    myMapper->writeCPU(0x0385 + x, a);
    if (!flgC) {
        goto L_004D49;
    }
    opINC(0x03A3 + x, 1);
L_004D49:
    a = 0x2D;
    y = 0x00;
    jump(0x8D50);
    return;
}

void game::SUB_004D50() {
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x03FD + x, y);
    myMapper->writeCPU(0x0475 + x, 0x08);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    popAddress();
}

void game::SUB_004D67() {
    myMapper->writeCPU(0x0565 + x, 0xFF);
    a = 0x00;
    y = 0x02;
    pushAddress(0x8D72);
    jump(0x8D50);
    if (handleReturnAddress(poppedEntry.value, 0x8D72)) return;
    myMapper->writeCPU(0x041B + x, 0x04);
    popAddress();
}

void game::SUB_004D79() {
    a = myMapper->readCPU(0x0565 + x);
    setLoadFlag(a);
    if (!flgN) {
        pushAddress(0x8D80);
        jump(0x8EF3);
        if (handleReturnAddress(poppedEntry.value, 0x8D80)) return;
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        y = myMapper->readCPU(0x0493 + x);
        while (true) {
            if (myMapper->readCPU(0x04CF + x) == 0) {
                goto L_004D95;
            }
            a = myMapper->readCPU(0x8EF3 + y);
            goto L_004D98;
        L_004D95:
            a = myMapper->readCPU(0x8E3E + y);
        L_004D98:
            myMapper->writeCPU(0x0002, a);
            if (a != 0x81) {
                goto L_004DA7;
            }
            a = 0x00;
            myMapper->writeCPU(0x0493 + x, a);
            y = a;
        }
    L_004DA7:
        flgC = false;
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            if (!flgC) {
                goto L_004DC5;
            }
            opINC(0x03A3 + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            if (!flgC) {
                opDEC(0x03A3 + x, 1);
            }
        }
    L_004DC5:
        flgC = false;
        if (myMapper->readCPU(0x04CF + x) != 0) {
            a = myMapper->readCPU(0x8EF3 + y);
            setLoadFlag(a);
        }
        else {
            a = myMapper->readCPU(0x8E99 + y);
            setLoadFlag(a);
        }
        if (!flgN) {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                goto L_004DEF;
            }
            opINC(0x03DF + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                opDEC(0x03DF + x, 1);
            }
        }
    L_004DEF:
        opINC(0x0493 + x, 1);
    }
    if (myMapper->readCPU(0x0565 + x) & 0x80) {
        goto L_004E2A;
    }
    if (myMapper->readCPU(0x0004) != 0) {
        a = 0x1A;
        pushAddress(0x8DFF);
        jump(0xEA16);
        if (handleReturnAddress(poppedEntry.value, 0x8DFF)) return;
        myMapper->writeCPU(0x03DF, myMapper->readCPU(0x03DF + x));
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x03C1, a);
        if (!flgC) {
            opDEC(0x03DF, 1);
        }
        y = 0x00;
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (!flgN) {
            goto L_004E1B;
        }
        opDEY(1);
    L_004E1B:
        flgC = false;
        opADC(myMapper->readCPU(0x0385));
        myMapper->writeCPU(0x0385, a);
        a = y;
        opADC(myMapper->readCPU(0x03A3));
        myMapper->writeCPU(0x03A3, a);
    }
    do {
        popAddress();
        return;
    L_004E2A:
        a = myMapper->readCPU(0x003F);
        opAND(0x02);
        opLSR_A(1);
        opADC(0x02);
        myMapper->writeCPU(0x03FD + x, a);
        y = 0x03;
        pushAddress(0x8E38);
        jump(0x9F39);
        if (handleReturnAddress(poppedEntry.value, 0x8E38)) return;
    } while (flgN);
    jump(0x8B37);
    return;
}

void game::SUB_004EF3() {
    a = 0x00;
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0004, a);
    if (myMapper->readCPU(0x05D2) == 0) {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x059F));
            if (!flgN) {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x03DF));
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(0x30);
                if (flgC) {
                    opINC(0x0000, 1);
                }
                flgC = true;
                opSBC(myMapper->readCPU(0x03C1 + x));
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x0000);
                opSBC(0x00);
                if (flgZ) {
                    if (myMapper->readCPU(0x0001) >= 0x10) {
                        goto L_004F72;
                    }
                    myMapper->writeCPU(0x0000, myMapper->readCPU(0x03A3));
                    a = myMapper->readCPU(0x0385);
                    flgC = false;
                    opADC(0x10);
                    if (flgC) {
                        opINC(0x0000, 1);
                    }
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0385 + x));
                    myMapper->writeCPU(0x0001, a);
                    a = myMapper->readCPU(0x0000);
                    opSBC(myMapper->readCPU(0x03A3 + x));
                    if (flgZ) {
                        if (myMapper->readCPU(0x0001) >= 0x28) {
                            goto L_004F72;
                        }
                        a = 0xFF;
                        myMapper->writeCPU(0x05A1, a);
                        myMapper->writeCPU(0x0004, a);
                        if (myMapper->readCPU(0x059D) == 0) {
                            goto L_004F5F;
                        }
                        a = 0x00;
                        myMapper->writeCPU(0x05A3, a);
                        myMapper->writeCPU(0x05A4, a);
                    L_004F5F:
                        a = 0x00;
                        myMapper->writeCPU(0x05A5, a);
                        myMapper->writeCPU(0x059D, a);
                        myMapper->writeCPU(0x059E, a);
                        myMapper->writeCPU(0x059F, a);
                        myMapper->writeCPU(0x05A6, 0x10);
                    }
                }
            }
        }
    }
L_004F72:
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_004F75() {
    a = 0xFF;
    myMapper->writeCPU(0x04B1 + x, a);
    jump(0x8F85);
    return;
}

void game::SUB_004F7D() {
    a = 0xFE;
    myMapper->writeCPU(0x04B1 + x, a);
    jump(0x8F85);
    return;
}

void game::SUB_004F85() {
    myMapper->writeCPU(0x03FD + x, 0x00);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    myMapper->writeCPU(0x0475 + x, 0x14);
    popAddress();
}

void game::SUB_004FA0() {
    pushAddress(0x8FA2);
    jump(0x8EF3);
    if (handleReturnAddress(poppedEntry.value, 0x8FA2)) return;
    flgC = false;
    a = myMapper->readCPU(0x04B1 + x);
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    y = myMapper->readCPU(0x0004);
    setLoadFlag(y);
    if (!flgZ) {
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x03C1, a);
        a = 0x00;
        opSBC(0x00);
        myMapper->writeCPU(0x03DF, a);
        a = 0x1A;
        pushAddress(0x8FC2);
        jump(0xEA16);
        if (handleReturnAddress(poppedEntry.value, 0x8FC2)) return;
    }
    opDEC(0x0565 + x, 1);
    if (!flgZ) {
        goto L_004FD7;
    }
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x04B1 + x, a);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
L_004FD7:
    popAddress();
}

void game::SUB_004FD8() {
    a = 0x02;
    myMapper->writeCPU(0x03FD + x, a);
    myMapper->writeCPU(0x04B1 + x, a);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    opINC(0x0475 + x, 1);
    SUB_004FED();
    return;
}

void game::SUB_004FED() {
    a = 0x00;
    myMapper->writeCPU(0x0486, a);
    pushAddress(0x8FF4);
    jump(0x8EF3);
    if (handleReturnAddress(poppedEntry.value, 0x8FF4)) return;
    if (flgZ) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0654, x);
    a = myMapper->readCPU(0x004B);
    opAND(0x40);
    if (!flgZ) {
        if (myMapper->readCPU(0x04B1 + x) == 0xFE) {
            goto L_00500C;
        }
        opDEC(0x04B1 + x, 1);
    }
L_00500C:
    a = myMapper->readCPU(0x003F);
    opAND(0x07);
    if (flgZ) {
        if (myMapper->readCPU(0x04B1 + x) == 0x02) {
            goto L_00501C;
        }
        opINC(0x04B1 + x, 1);
    }
L_00501C:
    a = myMapper->readCPU(0x03C1 + x);
    y = myMapper->readCPU(0x04B1 + x);
    setLoadFlag(y);
    if (flgN) {
        if (a >= 0x52) {
            goto L_005054;
        }
        y = myMapper->readCPU(0x03A3);
        if (y != 0x03) {
            goto L_00505B;
        }
        y = myMapper->readCPU(0x0385);
        if (y < 0xE0) {
            goto L_00505B;
        }
        if (a >= 0x21) {
            goto L_005054;
        }
        y = myMapper->readCPU(0x0051);
        myMapper->writeCPU(0x0059 + y, myMapper->readCPU(0x058E));
        myMapper->writeCPU(0x05D1, 0xFE);
        myMapper->writeCPU(0x03DF, 0xFE);
        popAddress();
        return;
    }
    if (a < 0xF8) {
        goto L_005054;
    }
    jump(0x8B37);
    return;
L_005054:
    flgC = false;
    opADC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
L_00505B:
    a = myMapper->readCPU(0x03C1 + x);
    flgC = true;
    opSBC(0x30);
    myMapper->writeCPU(0x03C1, a);
    a = 0x00;
    opSBC(0x00);
    myMapper->writeCPU(0x03DF, a);
    a = myMapper->readCPU(0x004B);
    opAND(0x40);
    if (flgZ) {
        jump(0x90AD);
        return;
    }
    a = 0x17;
    pushAddress(0x9075);
    jump(0xEA16);
    if (handleReturnAddress(poppedEntry.value, 0x9075)) return;
    y = 0x11;
    myMapper->writeCPU(0x0385 + y, myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x03A3 + y, myMapper->readCPU(0x03A3 + x));
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x03C1 + y, a);
    a = 0x00;
    opADC(0x00);
    myMapper->writeCPU(0x03DF + y, a);
    myMapper->writeCPU(0x04ED + y, 0xFF);
    myMapper->writeCPU(0x041B + y, 0x05);
    a = myMapper->readCPU(0x003F);
    opAND(0x02);
    opLSR_A(1);
    opADC(0x03);
    myMapper->writeCPU(0x03FD + y, a);
    myMapper->writeCPU(0x0475 + y, 0x19);
    SUB_0050AD();
    return;
}

void game::SUB_0050AD() {
    popAddress();
}

void game::SUB_0050AE() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x03A3 + x));
    a = myMapper->readCPU(0x03C1 + x);
    flgC = true;
    opSBC(0x08);
    y = a;
    if (flgC) {
        goto L_0050C3;
    }
    opDEC(0x0097, 1);
L_0050C3:
    a = myMapper->readCPU(0x0385 + x);
    x = a;
    pushAddress(0x90C9);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x90C9)) return;
    x = 0x01;
    y = 0x01;
    pushAddress(0x90D0);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x90D0)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_0050D5() {
    myMapper->writeCPU(0x04ED + x, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x03FD + x, a);
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x0475 + x, 0x1A);
    popAddress();
}

void game::SUB_0050ED() {
    a = 0xFF;
    myMapper->writeCPU(0x04ED + x, a);
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x03FD + x, 0x00);
    myMapper->writeCPU(0x041B + x, 0x05);
    a = 0x1B;
    myMapper->writeCPU(0x0475 + x, a);
    SUB_005104();
    return;
}

void game::SUB_005104() {
    pushAddress(0x9106);
    jump(0x8EF3);
    if (handleReturnAddress(poppedEntry.value, 0x9106)) return;
    if (!flgZ) {
        goto L_00510A;
    }
    popAddress();
    return;
L_00510A:
    myMapper->writeCPU(0x0385, myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x03A3, myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x05AA, 0x02);
    myMapper->writeCPU(0x05AB, 0xFE);
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
    a = 0x00;
    myMapper->writeCPU(0x05A6, a);
    jump(0x913D);
    return;
}

void game::SUB_005130() {
    y = 0x06;
    pushAddress(0x9134);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x9134)) return;
    if (flgN) {
        jump(0x913D);
        return;
    }
    pushAddress(0x9139);
    jump(0x8B37);
    if (handleReturnAddress(poppedEntry.value, 0x9139)) return;
    x = myMapper->readCPU(0x05AC);
    SUB_00513D();
    return;
}

void game::SUB_00513D() {
    a = myMapper->readCPU(0x03C1 + x);
    opORA(myMapper->readCPU(0x0385 + x));
    opAND(0x07);
    if (flgZ) {
        pushAddress(0x9149);
        jump(0x90AE);
        if (handleReturnAddress(poppedEntry.value, 0x9149)) return;
        if (a == 0x02) {
            if (myMapper->readCPU(0x0565 + x) & 0x80) {
                goto L_005173;
            }
            opDEC(0x0529 + x, 1);
            if (flgZ) {
                myMapper->writeCPU(0x0529 + x, 0x2B);
                opINC(0x0547 + x, 1);
                a = myMapper->readCPU(0x0547 + x);
                opAND(0x0F);
                y = a;
                a = myMapper->readCPU(0x91F7 + y);
                y = a;
                goto L_00518E;
            }
            do {
                myMapper->writeCPU(0x04B1 + x, 0x00);
                popAddress();
                return;
            L_005173:
                y = 0x00;
                x = myMapper->readCPU(0x004B);
                a = x;
                opAND(0x02);
                if (flgZ) {
                    opINY(1);
                    a = x;
                    opAND(0x01);
                    if (flgZ) {
                        opINY(1);
                        a = x;
                        opAND(0x08);
                        if (!flgZ) {
                            goto L_00518E;
                        }
                        opINY(1);
                        a = x;
                        opAND(0x04);
                        if (flgZ) {
                            goto L_0051CE;
                        }
                    }
                }
            L_00518E:
                x = myMapper->readCPU(0x05AC);
                myMapper->writeCPU(0x0493 + x, myMapper->readCPU(0x91E7 + y));
                myMapper->writeCPU(0x04B1 + x, myMapper->readCPU(0x91EB + y));
                x = myMapper->readCPU(0x91F3 + y);
                a = myMapper->readCPU(0x91EF + y);
                y = a;
                pushAddress(0x91A6);
                jump(0xE587);
                if (handleReturnAddress(poppedEntry.value, 0x91A6)) return;
                x = myMapper->readCPU(0x05AC);
            } while (a != 0x03);
        }
    }
    a = myMapper->readCPU(0x04B1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
L_0051CE:
    x = myMapper->readCPU(0x05AC);
    if (!(myMapper->readCPU(0x0565 + x) & 0x80)) {
        goto L_0051E6;
    }
    a = myMapper->readCPU(0x03C1 + x);
    flgC = true;
    opSBC(0x30);
    myMapper->writeCPU(0x03C1, a);
    a = 0x00;
    opSBC(0x00);
    myMapper->writeCPU(0x03DF, a);
L_0051E6:
    popAddress();
}

void game::SUB_005207() {
    if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
        goto L_005223;
    }
    a = myMapper->readCPU(0x05AF);
    opAND(0x3F);
    if (!flgZ) {
        goto L_005253;
    }
    myMapper->writeCPU(0x041B + x, 0x02);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(0x04CF + x));
L_005223:
    a = 0x1E;
    pushAddress(0x9227);
    jump(0xEA16);
    if (handleReturnAddress(poppedEntry.value, 0x9227)) return;
    a = myMapper->readCPU(0x003F);
    opAND(0x0C);
    opLSR_A(2);
    opADC(0x0A);
    myMapper->writeCPU(0x03FD + x, a);
    y = 0x02;
    pushAddress(0x9237);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x9237)) return;
    if (flgN) {
        goto L_005246;
    }
    pushAddress(0x923C);
    jump(0x8B37);
    if (handleReturnAddress(poppedEntry.value, 0x923C)) return;
    x = myMapper->readCPU(0x05AC);
    do {
        myMapper->writeCPU(0x03FD + x, 0xFF);
        popAddress();
        return;
    L_005246:
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x03C1 + x, a);
    } while (a < 0x20);
L_005253:
    popAddress();
}

void game::SUB_005254() {
    if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
        goto L_00527A;
    }
    a = myMapper->readCPU(0x05AF);
    opAND(0xB7);
    if (!flgZ) {
        goto L_005293;
    }
    myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(0x04CF + x));
    myMapper->writeCPU(0x03FD + x, 0x09);
    myMapper->writeCPU(0x04B1 + x, 0x00);
    myMapper->writeCPU(0x041B + x, 0x02);
    myMapper->writeCPU(0x04ED + x, 0xFF);
L_00527A:
    a = myMapper->readCPU(0x03C1 + x);
    if (a >= 0xE0) {
        goto L_00528A;
    }
    y = 0x02;
    pushAddress(0x9285);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x9285)) return;
    if (flgN) {
        goto L_005290;
    }
    opDEC(0x008E, 1);
L_00528A:
    myMapper->writeCPU(0x03FD + x, 0xFF);
    popAddress();
    return;
L_005290:
    jump(0x959F);
    return;
L_005293:
    popAddress();
}

void game::SUB_005294() {
    myMapper->writeCPU(0x03FD + x, 0x00);
    if (myMapper->readCPU(0x03C1 + x) >= myMapper->readCPU(0x04CF + x)) {
        goto L_005311;
    }
    myMapper->writeCPU(0x041B + x, 0x04);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    if (myMapper->readCPU(0x05A1) != 0) {
        goto L_005310;
    }
    a = myMapper->readCPU(0x05D2);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_005310;
    }
    y = 0x0A;
    pushAddress(0x92B9);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x92B9)) return;
    if (flgN) {
        goto L_005310;
    }
    a = 0x14;
    pushAddress(0x92C0);
    jump(0xEA16);
    if (handleReturnAddress(poppedEntry.value, 0x92C0)) return;
    myMapper->writeCPU(0x03FD + x, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x05A6, a);
    myMapper->writeCPU(0x059D, a);
    myMapper->writeCPU(0x059F, a);
    myMapper->writeCPU(0x0655, a);
    myMapper->writeCPU(0x05A1, 0xFF);
    myMapper->writeCPU(0x0654, x);
    a = 0x04;
    myMapper->writeCPU(0x05A4, a);
    myMapper->writeCPU(0x05AA, a);
    myMapper->writeCPU(0x05A3, 0x00);
    opINC(0x03C1 + x, 1);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x0F);
    myMapper->writeCPU(0x03C1, a);
    a = 0x00;
    opADC(0x00);
    myMapper->writeCPU(0x03DF, a);
    a = myMapper->readCPU(0x004C);
    opAND(0x80);
    if (flgZ) {
        goto L_005310;
    }
    while (true) {
        opINC(0x03C1, 1);
        a = 0x00;
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
        myMapper->writeCPU(0x05A1, a);
    L_005310:
        popAddress();
        return;
    L_005311:
        a = 0x19;
        myMapper->writeCPU(0x0475 + x, a);
    }
    SUB_005319();
    return;
}

void game::SUB_005319() {
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x03FD + x, 0x01);
    myMapper->writeCPU(0x041B + x, 0x05);
    a = myMapper->readCPU(0x0565 + x);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x0654, x);
        myMapper->writeCPU(0x05A1, x);
        if (!flgN) {
            a = 0x00;
            myMapper->writeCPU(0x05A3, a);
            myMapper->writeCPU(0x05A4, a);
            myMapper->writeCPU(0x05A6, a);
            myMapper->writeCPU(0x0655, a);
            myMapper->writeCPU(0x059D, a);
            myMapper->writeCPU(0x059F, a);
            a = myMapper->readCPU(0x03C1);
            flgC = true;
            opSBC(0x04);
            myMapper->writeCPU(0x03C1, a);
            if (a >= 0x30) {
                goto L_005386;
            }
            myMapper->writeCPU(0x0565 + x, 0xFF);
        }
        a = 0x14;
        pushAddress(0x935F);
        jump(0xEA16);
        if (handleReturnAddress(poppedEntry.value, 0x935F)) return;
        a = 0x04;
        myMapper->writeCPU(0x05A4, a);
        myMapper->writeCPU(0x05AA, a);
        a = 0x00;
        myMapper->writeCPU(0x0655, a);
        myMapper->writeCPU(0x059D, a);
        myMapper->writeCPU(0x05A3, a);
        opDEC(0x04CF + x, 1);
        if (!flgZ) {
            goto L_005386;
        }
        a = 0x00;
        myMapper->writeCPU(0x0565 + x, a);
        myMapper->writeCPU(0x05A1, a);
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
    }
L_005386:
    popAddress();
}

void game::SUB_005387() {
    if (myMapper->readCPU(0x05BD) != 0) {
        goto L_0053A6;
    }
    if (myMapper->readCPU(0x0457 + x) == 0) {
        if (myMapper->readCPU(0x03DF) != 0) {
            goto L_0053A6;
        }
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(myMapper->readCPU(0x03C1));
        if (!flgN) {
            if (a >= 0x38) {
                goto L_0053A6;
            }
            a = 0x00;
            setLoadFlag(a);
            popAddress();
            return;
        }
    }
L_0053A6:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0053A9() {
    pushAddress(0x93AB);
    jump(0x9387);
    if (handleReturnAddress(poppedEntry.value, 0x93AB)) return;
    if (flgZ) {
        flgC = true;
        if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
            goto L_0053D3;
        }
        a = myMapper->readCPU(0x0439 + x);
        opSBC(myMapper->readCPU(0x0439));
        if (flgC) {
            if (a < 0x0C) {
                goto L_0053DF;
            }
            if (a >= 0x10) {
                goto L_0053DF;
            }
            do {
                a = 0x00;
                myMapper->writeCPU(0x0655, a);
                myMapper->writeCPU(0x05BB, a);
                myMapper->writeCPU(0x05A3, a);
                myMapper->writeCPU(0x05A4, a);
                popAddress();
                return;
            L_0053D3:
                a = myMapper->readCPU(0x0439);
                opSBC(myMapper->readCPU(0x0439 + x));
                if (!flgC) {
                    goto L_0053DF;
                }
            } while (a < 0x08);
        }
    }
L_0053DF:
    myMapper->writeCPU(0x05BB, 0xFF);
    popAddress();
}

void game::SUB_00541F() {
    a = myMapper->readCPU(0x03FD + x);
    opORA(0x01);
    myMapper->writeCPU(0x0565 + y, a);
    myMapper->writeCPU(0x04B1 + y, 0xFB);
    SUB_00542C();
    return;
}

void game::SUB_00542C() {
    myMapper->writeCPU(0x0475 + y, 0x06);
    a = myMapper->readCPU(0x03FD + y);
    opAND(0x80);
    flgC = false;
    x = myMapper->readCPU(0x04ED + y);
    if (x != 0x04) {
        if (x == 0x03) {
            goto L_00548A;
        }
        if (x != 0x09) {
            goto L_005474;
        }
        opORA(myMapper->readCPU(0x04CF + y));
        myMapper->writeCPU(0x03FD + y, a);
        if (myMapper->readCPU(0x05BC) == 0) {
            goto L_005462;
        }
        a = 0x13;
        pushAddress(0x9455);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x9455)) return;
        a = myMapper->readCPU(0x0565 + y);
        opEOR(0x80);
        myMapper->writeCPU(0x0565 + y, a);
        opINC(0x0083, 1);
        opINC(0x008F, 1);
    L_005462:
        popAddress();
        return;
    }
    opORA(0x25);
    myMapper->writeCPU(0x03FD + y, a);
    a = myMapper->readCPU(0x0084);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x0084, a);
    a = 0x13;
    jump(0xEA1B);
    return;
L_005474:
    opORA(0x03);
    myMapper->writeCPU(0x03FD + y, a);
    myMapper->writeCPU(0x041B + y, 0x07);
    while (true) {
        a = myMapper->readCPU(0x0082);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x0082, a);
        a = 0x1F;
        jump(0xEA1B);
        return;
    L_00548A:
        opORA(myMapper->readCPU(0x04CF + y));
        myMapper->writeCPU(0x03FD + y, a);
    }
    SUB_005493();
    return;
}

void game::SUB_005493() {
    opCMP(myMapper->readCPU(0x03DF + x), 0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x04B1 + x);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                goto L_0054B8;
            }
            opINC(0x03DF + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                opDEC(0x03DF + x, 1);
            }
        }
    L_0054B8:
        a = myMapper->readCPU(0x003F);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x04B1 + x) == 0x08) {
                goto L_0054C8;
            }
            opINC(0x04B1 + x, 1);
        }
    L_0054C8:
        a = myMapper->readCPU(0x0565 + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (!flgN) {
                goto L_0054DE;
            }
            a = myMapper->readCPU(0x0385 + x);
            flgC = true;
            opSBC(0x03);
            myMapper->writeCPU(0x0385 + x, a);
            if (flgC) {
                goto L_0054DD;
            }
            opDEC(0x03A3 + x, 1);
        }
        do {
        L_0054DD:
            popAddress();
            return;
        L_0054DE:
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x0385 + x, a);
        } while (!flgC);
        opINC(0x03A3 + x, 1);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_0054F3() {
    myMapper->writeCPU(0x0529 + x, y);
    myMapper->writeCPU(0x0547 + x, 0x06);
    a = myMapper->readCPU(0x03FD + x);
    opAND(0x80);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0547 + x, 0x00);
    a = myMapper->readCPU(0x0529 + x);
    SUB_00550C();
    return;
}

void game::SUB_00550C() {
    y = a;
    a = myMapper->readCPU(0x8BF8 + y);
    setLoadFlag(a);
    if (!flgN) {
        y = a;
        opAND(0x3F);
        opORA(myMapper->readCPU(0x0493 + x));
        flgC = false;
        opADC(myMapper->readCPU(0x04CF + x));
        myMapper->writeCPU(0x03FD + x, a);
        if (y == 0x40) {
            goto L_005529;
        }
        while (true) {
            opDEC(0x0547 + x, 1);
            if (flgN) {
                goto L_005548;
            }
            popAddress();
            return;
        L_005529:
            myMapper->writeCPU(0x03FD + x, 0xA0);
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x04);
            myMapper->writeCPU(0x0385 + x, a);
            a = myMapper->readCPU(0x03A3 + x);
            opADC(0x00);
            myMapper->writeCPU(0x03A3 + x, a);
        }
    }
    a = 0x00;
    myMapper->writeCPU(0x0529 + x, a);
    popAddress();
    return;
L_005548:
    a = 0x06;
    myMapper->writeCPU(0x0547 + x, a);
    opINC(0x0529 + x, 1);
    if (y != 0x68) {
        if (y == 0x66) {
            goto L_00557C;
        }
        if (y == 0x42) {
            goto L_00557F;
        }
        if (y == 0x64) {
            goto L_005565;
        }
        if (y == 0x65) {
            goto L_005570;
        }
        do {
            do {
                popAddress();
                return;
            L_005565:
                a = myMapper->readCPU(0x05BB);
                setLoadFlag(a);
            } while (flgN);
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (flgZ) {
                goto L_005575;
            }
            popAddress();
            return;
        L_005570:
            a = myMapper->readCPU(0x05BB);
            setLoadFlag(a);
        } while (flgN);
    L_005575:
        opDEC(0x008E, 2);
        jump(0x9962);
        return;
    }
L_00557C:
    jump(0x9838);
    return;
L_00557F:
    pushAddress(0x988E);
    jump(0x9BBB);
    if (handleReturnAddress(poppedEntry.value, 0x988E)) return;
    if (flgN) {
        goto L_00559E;
    }
    myMapper->writeCPU(0x0475 + y, 0x07);
    myMapper->writeCPU(0x04B1 + y, 0xFA);
    myMapper->writeCPU(0x03FD + y, 0x01);
    myMapper->writeCPU(0x03C1 + y, myMapper->readCPU(0x03C1 + x));
    a = 0x00;
    jump(0x9B37);
    return;
L_00559E:
    popAddress();
}

void game::SUB_00559F() {
    myMapper->writeCPU(0x0529 + x, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    if (!flgC) {
        a = myMapper->readCPU(0x003F);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x04B1 + x) == 0x08) {
                goto L_0055C0;
            }
            opINC(0x04B1 + x, 1);
        }
    L_0055C0:
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_0055C7() {
    myMapper->writeCPU(0x050B + x, 0x03);
    a = 0x03;
    y = 0x80;
    jump(0x95FE);
    return;
}

void game::SUB_0055D3() {
    myMapper->writeCPU(0x050B + x, 0x00);
    a = 0x00;
    y = 0x80;
    jump(0x95FE);
    return;
}

void game::SUB_0055DF() {
    myMapper->writeCPU(0x050B + x, 0x03);
    a = 0x01;
    y = 0x80;
    jump(0x95FE);
    return;
}

void game::SUB_0055EB() {
    a = 0x13;
    pushAddress(0x95EF);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x95EF)) return;
    myMapper->writeCPU(0x050B + x, 0x00);
    myMapper->writeCPU(0x0547 + x, 0x03);
    a = 0x09;
    y = 0x04;
    SUB_0055FE();
    return;
}

void game::SUB_0055FE() {
    myMapper->writeCPU(0x04ED + x, a);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    a = y;
    myMapper->writeCPU(0x03FD + x, a);
    opAND(0x7F);
    myMapper->writeCPU(0x04CF + x, a);
    myMapper->writeCPU(0x041B + x, 0x07);
    myMapper->writeCPU(0x0475 + x, 0x18);
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0385 + x, a);
    if (!flgC) {
        goto L_005628;
    }
    opINC(0x03A3 + x, 1);
L_005628:
    popAddress();
}

void game::SUB_005629() {
    a = myMapper->readCPU(0x0529 + x);
    setLoadFlag(a);
    if (!flgZ) {
        pushAddress(0x9630);
        jump(0x950C);
        if (handleReturnAddress(poppedEntry.value, 0x9630)) return;
    }
    y = 0x05;
    pushAddress(0x9635);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x9635)) return;
    if (!flgN) {
        a = myMapper->readCPU(0x04ED + x);
        if (a == 0x09) {
            y = x;
            x = 0x00;
            a = 0x01;
            myMapper->writeCPU(0x05BC, a);
            jump(0x941F);
            return;
        }
        pushAddress(0x96BE);
        jump(0x8B37);
        if (handleReturnAddress(poppedEntry.value, 0x96BE)) return;
        x = myMapper->readCPU(0x05AC);
    }
    y = myMapper->readCPU(0x0565 + x);
    setLoadFlag(y);
    if (!flgZ) {
        if (myMapper->readCPU(0x04ED + x) != 0x03) {
            goto L_005680;
        }
        a = myMapper->readCPU(0x0493 + y);
        opAND(0x80);
        flgC = false;
        opADC(myMapper->readCPU(0x04CF + x));
        myMapper->writeCPU(0x03FD + x, a);
        a = myMapper->readCPU(0x03C1 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x04B1 + y));
        flgC = true;
        opSBC(0x28);
        myMapper->writeCPU(0x03C1 + x, a);
        a = 0x00;
        opSBC(0x00);
        myMapper->writeCPU(0x03DF + x, a);
        goto L_005694;
    L_005680:
        a = myMapper->readCPU(0x03C1 + y);
        flgC = false;
        opADC(myMapper->readCPU(0x04B1 + y));
        flgC = true;
        opSBC(0x20);
        myMapper->writeCPU(0x03C1 + x, a);
        a = 0x00;
        opSBC(0x00);
        myMapper->writeCPU(0x03DF + x, a);
    L_005694:
        a = myMapper->readCPU(0x0385 + y);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0385 + x, a);
        a = myMapper->readCPU(0x03A3 + y);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + x, a);
    }
    a = myMapper->readCPU(0x04ED + x);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x04B1 + x, 1);
        if (!flgN) {
            goto L_0056C6;
        }
        if (a == 0x01) {
            goto L_0056D0;
        }
        if (a == 0x03) {
            goto L_005709;
        }
        if (a == 0x09) {
            goto L_0056DA;
        }
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x05AF);
    opAND(0xCF);
    if (flgZ) {
        jump(0x9B17);
        return;
    L_0056C6:
        if (a == 0x09) {
            myMapper->writeCPU(0x0493 + x, 0x00);
        }
    }
    popAddress();
    return;
L_0056D0:
    a = 0x50;
    myMapper->writeCPU(0x04B1 + x, a);
    y = 0x01;
    jump(0x94F3);
    return;
L_0056DA:
    myMapper->writeCPU(0x0659, x);
    if (myMapper->readCPU(0x0493 + x) == 0) {
        opDEC(0x0547 + x, 1);
        if (flgZ) {
            myMapper->writeCPU(0x04B1 + x, 0xFE);
            myMapper->writeCPU(0x0565 + x, 0x00);
            a = x;
            y = a;
            x = 0x00;
            jump(0x942C);
            return;
        }
        myMapper->writeCPU(0x0493 + x, 0xFF);
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x04);
    opLSR_A(2);
    opADC(0x04);
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_005709:
    a = 0x64;
    myMapper->writeCPU(0x04B1 + x, a);
    pushAddress(0x9710);
    jump(0x9BBB);
    if (handleReturnAddress(poppedEntry.value, 0x9710)) return;
    if (!flgN) {
        a = 0x19;
        pushAddress(0x9717);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x9717)) return;
        if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
            goto L_00573B;
        }
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3 + x);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        myMapper->writeCPU(0x0493 + y, 0xFC);
        a = 0x80;
        myMapper->writeCPU(0x03FD + y, a);
        goto L_005756;
    L_00573B:
        a = myMapper->readCPU(0x0385 + x);
        flgC = false;
        opADC(0x18);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3 + x);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        myMapper->writeCPU(0x0493 + y, 0x04);
        myMapper->writeCPU(0x03FD + y, 0x00);
    L_005756:
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x03C1 + y, a);
        a = 0x00;
        myMapper->writeCPU(0x0457 + y, a);
        myMapper->writeCPU(0x03DF + y, a);
        myMapper->writeCPU(0x04B1 + y, a);
        myMapper->writeCPU(0x0475 + y, 0x05);
        myMapper->writeCPU(0x041B + y, 0x01);
    }
    popAddress();
}

void game::SUB_005775() {
    myMapper->writeCPU(0x03FD + x, 0xA6);
    myMapper->writeCPU(0x0565 + x, 0x0E);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x050B + x, 0x14);
    myMapper->writeCPU(0x0475 + x, 0x01);
    myMapper->writeCPU(0x041B + x, 0x06);
    SUB_005793();
    return;
}

void game::SUB_005793() {
    a = 0x60;
    opCMP(a, myMapper->readCPU(0x0385));
    if (!flgZ) {
        if (!flgN) {
            goto L_0057A7;
        }
    }
    myMapper->writeCPU(0x0385, a);
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
L_0057A7:
    myMapper->writeCPU(0x0656, 0xFE);
    a = myMapper->readCPU(0x0565 + x);
    setLoadFlag(a);
    if (flgZ) {
        a = 0x04;
        myMapper->writeCPU(0x04ED + x, a);
        pushAddress(0x97B8);
        jump(0x93A9);
        if (handleReturnAddress(poppedEntry.value, 0x97B8)) return;
        myMapper->writeCPU(0x0655, 0x00);
        myMapper->writeCPU(0x04B1 + x, 0x00);
        a = myMapper->readCPU(0x03C1 + x);
        opAND(0xF8);
        myMapper->writeCPU(0x03C1 + x, a);
        a = myMapper->readCPU(0x0529 + x);
        setLoadFlag(a);
        if (!flgZ) {
            jump(0x950C);
            return;
        }
        if (!(myMapper->readCPU(0x05BB) & 0x80)) {
            a = myMapper->readCPU(0x05AF);
            opLSR_A(1);
            if (flgC) {
                y = 0x08;
                opAND(0x03);
                if (flgZ) {
                    y = 0x0D;
                }
                jump(0x94F3);
                return;
            }
            myMapper->writeCPU(0x03FD + x, 0xA0);
            popAddress();
            return;
        }
        a = myMapper->readCPU(0x003F);
        opAND(0x0C);
        opLSR_A(1);
        flgC = true;
        opROR_A(1);
        opADC(0x20);
        myMapper->writeCPU(0x03FD + x, a);
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0385 + x, a);
        a = myMapper->readCPU(0x03A3 + x);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + x, a);
        popAddress();
        return;
    }
    y = 0x05;
    pushAddress(0x9811);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x9811)) return;
    if (!flgN) {
        pushAddress(0x9816);
        jump(0x8B37);
        if (handleReturnAddress(poppedEntry.value, 0x9816)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x0529 + x);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x950C);
        return;
    }
    a = myMapper->readCPU(0x05AF);
    opAND(0x77);
    if (flgZ) {
        a = myMapper->readCPU(0x03FD + x);
        y = 0x17;
        if (a == 0xA6) {
            goto L_005834;
        }
        y = 0x12;
    L_005834:
        jump(0x94F3);
        return;
    }
    popAddress();
}

void game::SUB_005838() {
    pushAddress(0x983A);
    jump(0x9BBB);
    if (handleReturnAddress(poppedEntry.value, 0x983A)) return;
    if (!flgN) {
        a = 0x09;
        pushAddress(0x9841);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x9841)) return;
        opDEC(0x0565 + x, 1);
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3 + x);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        if (myMapper->readCPU(0x03FD + x) == 0xA6) {
            goto L_005869;
        }
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x16);
        myMapper->writeCPU(0x03C1 + y, a);
        goto L_00586F;
    L_005869:
        myMapper->writeCPU(0x03C1 + y, myMapper->readCPU(0x03C1 + x));
    L_00586F:
        a = 0x00;
        myMapper->writeCPU(0x0457 + y, a);
        myMapper->writeCPU(0x03DF + y, a);
        myMapper->writeCPU(0x0493 + y, 0xFC);
        myMapper->writeCPU(0x0475 + y, 0x24);
        myMapper->writeCPU(0x041B + y, 0x05);
        a = 0x80;
        myMapper->writeCPU(0x03FD + y, a);
    }
    popAddress();
}

void game::SUB_00588C() {
    y = 0x06;
    pushAddress(0x9890);
    jump(0x9F39);
    if (handleReturnAddress(poppedEntry.value, 0x9890)) return;
    if (!flgN) {
        a = 0x00;
        myMapper->writeCPU(0x0475 + x, a);
        pushAddress(0x989A);
        jump(0x8B45);
        if (handleReturnAddress(poppedEntry.value, 0x989A)) return;
        a = myMapper->readCPU(0x008E);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x008E, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0385 + x);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0385 + x, a);
    if (flgC) {
        goto L_0058B1;
    }
    opDEC(0x03A3 + x, 1);
L_0058B1:
    a = myMapper->readCPU(0x003F);
    opAND(0x04);
    opLSR_A(2);
    opADC(0x80);
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
}

void game::SUB_0058BD() {
    flgC = false;
    a = myMapper->readCPU(0x04B1 + x);
    setLoadFlag(a);
    if (!flgN) {
        opADC(myMapper->readCPU(0x03C1 + x));
        myMapper->writeCPU(0x03C1 + x, a);
        if (!flgC) {
            goto L_0058E4;
        }
        opINC(0x03DF + x, 1);
        if (flgZ) {
            goto L_0058E4;
        }
        myMapper->writeCPU(0x0475 + x, 0x00);
        popAddress();
        return;
    }
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    if (!flgC) {
        opDEC(0x03DF + x, 1);
    }
L_0058E4:
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (!flgZ) {
        goto L_0058ED;
    }
    opINC(0x04B1 + x, 1);
L_0058ED:
    jump(0x98FE);
    return;
}

void game::SUB_0058F0() {
    a = myMapper->readCPU(0x04B1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    if (a >= 0xF4) {
        jump(0x9903);
        return;
    }
    myMapper->writeCPU(0x03C1 + x, a);
    SUB_0058FE();
    return;
}

void game::SUB_0058FE() {
    if (myMapper->readCPU(0x0457 + x) == 0) {
        jump(0x9909);
        return;
    }
    SUB_005903();
    return;
}

void game::SUB_005903() {
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_005909() {
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    myMapper->writeCPU(0x0024, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    myMapper->writeCPU(0x0025, a);
    if (myMapper->readCPU(0x05BD) == 0) {
        myMapper->writeCPU(0x0001, 0x38);
        a = 0x20;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x9934);
        jump(0x9F39);
        if (handleReturnAddress(poppedEntry.value, 0x9934)) return;
        if (!flgN) {
            goto L_005938;
        }
    }
    popAddress();
    return;
L_005938:
    a = myMapper->readCPU(0x0475 + x);
    if (a == 0x07) {
        pushAddress(0x9941);
        jump(0x9AE4);
        if (handleReturnAddress(poppedEntry.value, 0x9941)) return;
        a = 0xFE;
    }
    else {
        a = myMapper->readCPU(0x041B + x);
        if (a != 0x01) {
            goto L_005956;
        }
        pushAddress(0x9950);
        jump(0x9ADA);
        if (handleReturnAddress(poppedEntry.value, 0x9950)) return;
        a = 0xFE;
        goto L_00595D;
    L_005956:
        myMapper->writeCPU(0x0475 + x, 0x00);
        a = 0xFE;
    }
L_00595D:
    flgC = false;
    opADC(myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x008E, a);
    SUB_005962();
    return;
}

void game::SUB_005962() {
    if (myMapper->readCPU(0x04B1 + x) == 0) {
        goto L_00596F;
    }
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
L_00596F:
    x = 0x1C;
    if (myMapper->readCPU(0x05C9) != 0) {
        x = 0x20;
    }
    a = 0x0C;
    pushAddress(0x997C);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x997C)) return;
    a = myMapper->readCPU(0x04ED + x);
    if (a == 0x04) {
        goto L_005987;
    }
    jump(0x8B01);
    return;
L_005987:
    jump(0x8B06);
    return;
}

void game::SUB_00598A() {
    if (myMapper->readCPU(0x0457 + x) == 0) {
        goto L_005995;
    }
    while (true) {
        do {
            myMapper->writeCPU(0x0475 + x, 0x00);
            popAddress();
            return;
        L_005995:
            y = 0x00;
            a = myMapper->readCPU(0x0493 + x);
            setLoadFlag(a);
            if (!flgN) {
                goto L_00599D;
            }
            opDEY(1);
        L_00599D:
            flgC = false;
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            myMapper->writeCPU(0x0024, a);
            a = y;
            opADC(myMapper->readCPU(0x03A3 + x));
            myMapper->writeCPU(0x03A3 + x, a);
            myMapper->writeCPU(0x0025, a);
            a = myMapper->readCPU(0x04B1 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x03C1 + x));
        } while (a >= 0xF4);
        myMapper->writeCPU(0x03C1 + x, a);
        myMapper->writeCPU(0x0001, 0x30);
        a = 0x18;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x99C9);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99C9)) return;
        if (!flgN) {
            goto L_005A04;
        }
        y = 0x02;
        pushAddress(0x99D0);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99D0)) return;
        if (!flgN) {
            goto L_005A04;
        }
        y = 0x06;
        pushAddress(0x99D7);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99D7)) return;
        if (!flgN) {
            goto L_005A04;
        }
        y = 0x07;
        pushAddress(0x99DE);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99DE)) return;
        if (!flgN) {
            goto L_005A04;
        }
        a = 0x20;
        myMapper->writeCPU(0x0001, a);
        myMapper->writeCPU(0x0002, a);
        y = 0x0E;
        pushAddress(0x99EB);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99EB)) return;
        if (!flgN) {
            goto L_005A04;
        }
        y = 0x0F;
        pushAddress(0x99F2);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99F2)) return;
        if (!flgN) {
            goto L_005A04;
        }
        y = 0x10;
        pushAddress(0x99F9);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x99F9)) return;
        if (!flgN) {
            goto L_005A04;
        }
        y = 0x11;
        pushAddress(0x9A00);
        jump(0x9A2C);
        if (handleReturnAddress(poppedEntry.value, 0x9A00)) return;
        if (!flgN) {
            goto L_005A04;
        }
        do {
            popAddress();
            return;
        L_005A04:
            a = 0x0D;
            pushAddress(0x9A08);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x9A08)) return;
            a = myMapper->readCPU(0x050B + y);
            flgC = true;
            opSBC(myMapper->readCPU(0x0594));
            myMapper->writeCPU(0x050B + y, a);
            if (!flgN) {
                goto L_005A1B;
            }
            pushAddress(0x9A17);
            jump(0x941F);
            if (handleReturnAddress(poppedEntry.value, 0x9A17)) return;
            x = myMapper->readCPU(0x05AC);
        L_005A1B:
            a = myMapper->readCPU(0x0595);
        } while (a == 0x05);
        if (a == 0x04) {
            goto L_005A29;
        }
    }
L_005A29:
    jump(0x9AE4);
    return;
}

void game::SUB_005A2C() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x06) {
            goto L_005A6C;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_005A6C;
            }
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(0x08);
            flgC = true;
            opSBC(myMapper->readCPU(0x03C1 + y));
            if (flgC) {
                if (a >= myMapper->readCPU(0x0001)) {
                    goto L_005A6C;
                }
                a = myMapper->readCPU(0x0024);
                flgC = false;
                opADC(0x08);
                flgC = true;
                opSBC(myMapper->readCPU(0x0385 + y));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x0025);
                opSBC(myMapper->readCPU(0x03A3 + y));
                if (flgZ) {
                    if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x0002)) {
                        goto L_005A6C;
                    }
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                }
            }
        }
    }
L_005A6C:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_005A6F() {
    myMapper->writeCPU(0x03FD + x, myMapper->readCPU(0x04CF + x));
    a = 0x02;
    myMapper->writeCPU(0x041B + x, a);
    y = 0x02;
    pushAddress(0x9A7E);
    jump(0x9F43);
    if (handleReturnAddress(poppedEntry.value, 0x9A7E)) return;
    if (flgN) {
        goto L_005A9D;
    }
    y = myMapper->readCPU(0x03FD + x);
    if (y == 0x00) {
        goto L_005ACE;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    if (y == 0x08) {
        goto L_005AB0;
    }
    if (y == 0x01) {
        goto L_005AB7;
    }
    if (y == 0x06) {
        goto L_005AA4;
    }
    if (y == 0x07) {
        goto L_005A9E;
    }
L_005A9D:
    popAddress();
    return;
L_005A9E:
    myMapper->writeCPU(0x05BD, 0x06);
    popAddress();
    return;
L_005AA4:
    a = myMapper->readCPU(0x008E);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x008E, a);
    a = 0x11;
    jump(0xEA1B);
    return;
L_005AB0:
    a = 0x05;
    a = 0x0E;
    jump(0xEA1B);
    return;
L_005AB7:
    y = myMapper->readCPU(0x05BE);
    myMapper->writeCPU(0x0595, y);
    myMapper->writeCPU(0x0594, myMapper->readCPU(0xEA43 + y));
    myMapper->writeCPU(0x0596, myMapper->readCPU(0xEA49 + y));
    a = 0x12;
    jump(0xEA1B);
    return;
L_005ACE:
    a = myMapper->readCPU(0x0081);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x0081, a);
    opINC(0x0090, 1);
    jump(0x9ADA);
    return;
}

void game::SUB_005ADA() {
    myMapper->writeCPU(0x041B + x, 0x02);
    a = 0x02;
    jump(0x9AEB);
    return;
}

void game::SUB_005AE4() {
    myMapper->writeCPU(0x041B + x, 0x00);
    a = 0x02;
    SUB_005AEB();
    return;
}

void game::SUB_005AEB() {
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x04CF + x, 0x00);
    myMapper->writeCPU(0x0475 + x, 0x04);
    a = 0x0B;
    pushAddress(0x9AFC);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9AFC)) return;
    SUB_005AFD();
    return;
}

void game::SUB_005AFD() {
    a = myMapper->readCPU(0x04CF + x);
    opLSR_A(2);
    opINC(0x04CF + x, 1);
    if (a == 0x04) {
        goto L_005B11;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0565 + x));
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_005B11:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_005B17() {
    pushAddress(0x9B19);
    jump(0x9BBB);
    if (handleReturnAddress(poppedEntry.value, 0x9B19)) return;
    if (flgN) {
        jump(0x9B7A);
        return;
    }
    a = 0x06;
    pushAddress(0x9B20);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9B20)) return;
    myMapper->writeCPU(0x0475 + y, 0x05);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x03C1 + y, a);
    a = 0x00;
    myMapper->writeCPU(0x03FD + y, a);
    myMapper->writeCPU(0x04B1 + y, a);
    SUB_005B37();
    return;
}

void game::SUB_005B37() {
    myMapper->writeCPU(0x041B + y, a);
    myMapper->writeCPU(0x0457 + y, a);
    myMapper->writeCPU(0x03DF + y, a);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x0493 + y, 0x03);
    if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
        goto L_005B6B;
    }
    myMapper->writeCPU(0x0493 + y, 0xFD);
    a = myMapper->readCPU(0x0000);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x0001);
    opSBC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    jump(0x9B7A);
    return;
L_005B6B:
    a = myMapper->readCPU(0x0000);
    flgC = false;
    opADC(0x18);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x0001);
    opADC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    SUB_005B7A();
    return;
}

void game::SUB_005B7A() {
    popAddress();
}

void game::SUB_005BBB() {
    y = 0x08;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x09;
        if (myMapper->readCPU(0x0475 + y) == 0) {
            goto L_005BCC;
        }
        a = 0xFF;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_005BCC:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_005BCF() {
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        if (a != myMapper->readCPU(0x00A0)) {
            goto L_005BDD;
        }
        pushAddress(0x9BD9);
        jump(0x9BE8);
        if (handleReturnAddress(poppedEntry.value, 0x9BD9)) return;
    }
L_005BDD:
    flgC = false;
    a = y;
    opADC(myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x000E, a);
    if (!flgC) {
        goto L_005BE7;
    }
    opINC(0x000F, 1);
L_005BE7:
    popAddress();
}

void game::SUB_005BE8() {
    opINY(1);
    x = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    a = myMapper->readCPU(0x0475 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_005C2C;
    }
    a = myMapper->readCPU(SCROLL_FINE);
    opAND(0xF8);
    myMapper->writeCPU(0x0385 + x, a);
    a = myMapper->readCPU(SCROLL_LARGE);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x03A3 + x, a);
    opINY(1);
    myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    a = 0x00;
    myMapper->writeCPU(0x03DF + x, a);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0529 + x, a);
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x0547 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0475 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x04CF + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = 0xFF;
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_005C2C:
    opINY(4);
    popAddress();
}

void game::SUB_005F39() {
    if (myMapper->readCPU(0x05D2) != 0) {
        jump(0x9F9E);
        return;
    }
    if (myMapper->readCPU(0x05BD) != 0) {
        jump(0x9F9E);
        return;
    }
    SUB_005F43();
    return;
}

void game::SUB_005F43() {
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03DF));
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(myMapper->readCPU(0x05C9));
    myMapper->writeCPU(0x0000, a);
    if (flgC) {
        opINC(0x0001, 1);
    }
    myMapper->writeCPU(0x0002, myMapper->readCPU(0x03DF + x));
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x9FAC + y));
    if (flgC) {
        opINC(0x0002, 1);
    }
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0002);
    opSBC(myMapper->readCPU(0x0001));
    if (!flgZ) {
        jump(0x9F9E);
        return;
    }
    if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x9FC2 + y)) {
        jump(0x9F9E);
        return;
    }
    myMapper->writeCPU(0x0025, myMapper->readCPU(0x03A3 + x));
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x9FA1 + y));
    if (!flgC) {
        goto L_005F87;
    }
    opINC(0x0025, 1);
L_005F87:
    flgC = true;
    opSBC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opSBC(myMapper->readCPU(0x03A3));
    if (!flgZ) {
        jump(0x9F9E);
        return;
    }
    if (myMapper->readCPU(0x0024) >= myMapper->readCPU(0x9FB7 + y)) {
        jump(0x9F9E);
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_005F9E() {
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_005FCD() {
    a = myMapper->readCPU(0x00A0);
    if (a == myMapper->readCPU(0x05BA)) {
        a = 0x00;
        myMapper->writeCPU(0x05B5, a);
    }
    opBIT(myMapper->readCPU(0x05B5));
    if (!flgN) {
        if (!flgV) {
            goto L_005FE3;
        }
        goto L_0060CA;
    L_005FE3:
        y = 0x03;
        x = myMapper->readCPU(0x0051);
        if (myMapper->readCPU((0x0059 + x) & 0x00ff) != 0x01) {
            y = 0x0B;
        }
        a = myMapper->readCPU(0x00A0);
        x = 0x03;
        do {
            if (a == myMapper->readCPU(0xA136 + y)) {
                goto L_005FFD;
            }
            opDEY(1);
            opDEX(1);
        } while (!flgN);
        popAddress();
        return;
    L_005FFD:
        flgC = false;
        opADC(0x09);
        myMapper->writeCPU(0x05BA, a);
        myMapper->writeCPU(0x05B9, myMapper->readCPU(0xA13A + y));
        myMapper->writeCPU(0x05B3, myMapper->readCPU(0x0371));
        myMapper->writeCPU(0x05B4, myMapper->readCPU(0x0370));
        myMapper->writeCPU(0x05B1, myMapper->readCPU(0x0301));
        myMapper->writeCPU(0x05B2, myMapper->readCPU(0x0300));
    L_006021:
        a = myMapper->readCPU(0x05B9);
        myMapper->writeCPU(0x05B7, a);
        x = 0x00;
        myMapper->writeCPU(0x05B6, x);
        opDEX(1);
        myMapper->writeCPU(0x05B5, x);
        myMapper->writeCPU(0x05B8, x);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x05B8);
    setLoadFlag(a);
    if (!flgN) {
        if (flgZ) {
            goto L_00603F;
        }
        opDEC(0x05B8, 1);
    }
    popAddress();
    return;
L_00603F:
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x05B1));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x05B3));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x05B4));
    a = myMapper->readCPU(0x05B6);
    flgC = false;
    opADC(0x04);
    x = 0x31;
    pushAddress(0xA05D);
    jump(0xE3C9);
    if (handleReturnAddress(poppedEntry.value, 0xA05D)) return;
    if (myMapper->readCPU(0x05B6) == 0x02) {
        myMapper->writeCPU(0x05B6, 0x00);
        flgC = false;
        a = myMapper->readCPU(0x05B3);
        opADC(0x08);
        myMapper->writeCPU(0x05B3, a);
        myMapper->writeCPU(0x0009, a);
        flgC = false;
        a = myMapper->readCPU(0x05B1);
        opADC(0x80);
        myMapper->writeCPU(0x05B1, a);
        myMapper->writeCPU(0x0005, a);
        if (flgC) {
            opINC(0x05B2, 1);
        }
        myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
        a = 0x04;
        x = 0x4C;
        pushAddress(0xA090);
        jump(0xE3C9);
        if (handleReturnAddress(poppedEntry.value, 0xA090)) return;
    }
    opINC(0x05B6, 1);
    a = myMapper->readCPU(0x05B7);
    if (a < 0x03) {
        a = myMapper->readCPU(0x05C3);
        if (a == 0x1C) {
            a = 0x03;
            myMapper->writeCPU(0x05D1, a);
            goto L_0060C5;
        }
    }
    opDEC(0x05B7, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x05B5, 0x40);
    myMapper->writeCPU(0x05B6, 0x01);
    myMapper->writeCPU(0x05B7, myMapper->readCPU(0x05B9));
    myMapper->writeCPU(0x05B8, 0x08);
L_0060C5:
    a = 0x22;
    jump(0xEA1B);
    return;
L_0060CA:
    a = myMapper->readCPU(0x05B8);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x05B8, 1);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x05B1));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x05B3));
    x = myMapper->readCPU(0x05B4);
    myMapper->writeCPU(0x000A, x);
    a = myMapper->readCPU(0x05B6);
    setLoadFlag(a);
    if (flgN) {
        a = 0x00;
    }
    else {
        flgC = false;
        opADC(0x04);
    }
    x = 0x31;
    pushAddress(0xA0F8);
    jump(0xE3C9);
    if (handleReturnAddress(poppedEntry.value, 0xA0F8)) return;
    a = myMapper->readCPU(0x05B6);
    setLoadFlag(a);
    if (flgN) {
        myMapper->writeCPU(0x05B6, 0x01);
        flgC = true;
        a = myMapper->readCPU(0x05B3);
        opSBC(0x08);
        myMapper->writeCPU(0x05B3, a);
        myMapper->writeCPU(0x0009, a);
        flgC = true;
        a = myMapper->readCPU(0x05B1);
        opSBC(0x80);
        myMapper->writeCPU(0x05B1, a);
        myMapper->writeCPU(0x0005, a);
        if (!flgC) {
            opDEC(0x05B2, 1);
        }
        myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
        a = 0x05;
        x = 0x4C;
        pushAddress(0xA129);
        jump(0xE3C9);
        if (handleReturnAddress(poppedEntry.value, 0xA129)) return;
    }
    opDEC(0x05B6, 1);
    opDEC(0x05B7, 1);
    if (flgZ) {
        goto L_006133;
    }
    popAddress();
    return;
L_006133:
    goto L_006021;
}

void game::SUB_008000() {
    pushAddress(0x8002);
    jump(0x81B0);
    if (handleReturnAddress(poppedEntry.value, 0x8002)) return;
    myMapper->writeCPU(0x05AC, a);
    if (a != 0xFF) {
        if (a == 0x01) {
            goto L_008013;
        }
        if (a == 0x03) {
            goto L_008026;
        }
        popAddress();
        return;
    L_008013:
        x = 0x07;
        a = 0x00;
        jump(0x8036);
        return;
    }
    myMapper->writeCPU(0x0547, 0x80);
    x = 0x03;
    a = 0x0C;
    jump(0x8036);
    return;
L_008026:
    x = 0x0F;
    a = 0x2E;
    jump(0x8036);
    return;
}

void game::SUB_00802D() {
    a = 0x06;
    pushAddress(0x8031);
    SUB_01FFAA_SwitchCHRBank1();
    x = 0x0F;
    a = 0x27;
    SUB_008036();
    return;
}

void game::SUB_008036() {
    myMapper->writeCPU(0x05A2, x);
    myMapper->writeCPU(0x05CA, a);
    a = 0x02;
    pushAddress(0x8040);
    SUB_01FFD2_SwitchCHRBank0();
    pushAddress(0x8043);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0x8043)) return;
    pushAddress(0x8046);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x8046)) return;
    a = myMapper->readCPU(0x03C1);
    opAND(0xF8);
    myMapper->writeCPU(0x03C1, a);
    myMapper->writeCPU(0x058A, myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x058B, myMapper->readCPU(0x001F));
    myMapper->writeCPU(0x001E, 0x32);
    a = 0xC9;
    myMapper->writeCPU(0x001F, a);
    x = myMapper->readCPU(0x0589);
    setLoadFlag(x);
    if (!flgN) {
        myMapper->writeCPU(0x040E, x);
        opINX(1);
        myMapper->writeCPU(0x040F, x);
        a = 0x05;
        myMapper->writeCPU(0x042C, a);
        myMapper->writeCPU(0x042D, a);
        a = 0x00;
        myMapper->writeCPU(0x03B4, a);
        myMapper->writeCPU(0x03B5, a);
        myMapper->writeCPU(0x03F0, a);
        myMapper->writeCPU(0x03F1, a);
        a = 0x20;
        myMapper->writeCPU(0x03D2, a);
        myMapper->writeCPU(0x03D3, a);
        myMapper->writeCPU(0x0396, 0x08);
        a = 0x28;
        myMapper->writeCPU(0x0397, a);
    }
    goto L_00809D;
    while (true) {
        a = 0x02;
        pushAddress(0x809C);
        SUB_01FFD2_SwitchCHRBank0();
    L_00809D:
        a = myMapper->readCPU(0x0040);
        opAND(0xFE);
        myMapper->writeCPU(PPU_CTRL, a);
        x = myMapper->readCPU(0x05CA);
        a = myMapper->readCPU(0x817E + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_008140;
        }
        myMapper->writeCPU(0x03FD, a);
        a = myMapper->readCPU(0x003F);
        opAND(myMapper->readCPU(0x05A2));
        if (flgZ) {
            opINC(0x05CA, 1);
        }
        //do {
        //L_0080BC:
        //    opBIT(myMapper->readCPU(PPU_STATUS));
        //} while (!flgV);
    L_0080BC:
        wait(2);
        needWaitScanline = true;
        waitScanline = 32;
        wait(3);
        if (myMapper->readCPU(0x03FD) == 0x18) {
            a = 0x16;
            pushAddress(0x80E9);
            jump(0xEA16);
            if (handleReturnAddress(poppedEntry.value, 0x80E9)) return;
        }
        a = myMapper->readCPU(0x05AC);
        if (a == 0xFF) {
            pushAddress(0x80F3);
            jump(0xF822);
            if (handleReturnAddress(poppedEntry.value, 0x80F3)) return;
        }
        a = 0x04;
        myMapper->writeCPU(0x0028, a);
        y = 0x00;
        pushAddress(0x80FC);
        jump(0xCA70);
        if (handleReturnAddress(poppedEntry.value, 0x80FC)) return;
        x = myMapper->readCPU(0x0589);
        setLoadFlag(x);
        if (!flgN) {
            y = 0x11;
            pushAddress(0x8106);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x8106)) return;
            y = 0x12;
            pushAddress(0x810B);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x810B)) return;
            pushAddress(0x810E);
            jump(0xCA60);
            if (handleReturnAddress(poppedEntry.value, 0x810E)) return;
        }
        pushAddress(0x8111);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x8111)) return;
        pushAddress(0x8114);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x8114)) return;
        a = myMapper->readCPU(0x003F);
        opLSR_A(1);
        if (flgC) {
            a = myMapper->readCPU(0x05D1);
            if (a == 0xFE) {
                opINC(0x03C1, 1);
                if (flgZ) {
                    opINC(0x03DF, 1);
                }
            }
        }
        pushAddress(0x812B);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x812B)) return;
        pushAddress(0x812E);
        jump(0xEA36);
        if (handleReturnAddress(poppedEntry.value, 0x812E)) return;
        a = myMapper->readCPU(0x000D);
        setLoadFlag(a);
        if (flgZ) {
            goto L_008135;
        }
        myMapper->writeCPU(0x000B, a);
    L_008135:
        pushAddress(0x8137);
        jump(0xDBB3);
        if (handleReturnAddress(poppedEntry.value, 0x8137)) return;
        a = 0x06;
        pushAddress(0x813C);
        SUB_01FFAA_SwitchCHRBank1();
    }
L_008140:
    if (myMapper->readCPU(0x05AC) == 0xFF) {
        a = myMapper->readCPU(0x0091);
        if (a == 0xFF) {
            a = myMapper->readCPU(0x0547);
            setLoadFlag(a);
            if (flgZ) {
                goto L_008161;
            }
            opDEC(0x0547, 1);
            if (a != 0x32) {
                goto L_00815E;
            }
            a = 0x0F;
            pushAddress(0x815D);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x815D)) return;
        }
    L_00815E:
        goto L_0080BC;
    }
L_008161:
    a = 0x00;
    myMapper->writeCPU(0x05CA, a);
    myMapper->writeCPU(0x0486, a);
    myMapper->writeCPU(0x0487, a);
    myMapper->writeCPU(0x00B9, a);
    myMapper->writeCPU(0x004C, a);
    myMapper->writeCPU(0x001E, myMapper->readCPU(0x058A));
    myMapper->writeCPU(0x001F, myMapper->readCPU(0x058B));
    a = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_0081B0() {
    pushAddress(0x81B2);
    jump(0xDE68);
    if (handleReturnAddress(poppedEntry.value, 0x81B2)) return;
    pushAddress(0x81B5);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0x81B5)) return;
    pushAddress(0x81B8);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0x81B8)) return;
    pushAddress(0x81BB);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0x81BB)) return;
    pushAddress(0x81BE);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x81BE)) return;
    a = 0x04;
    pushAddress(0x81C3);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x81C3)) return;
    myMapper->writeCPU(0x05D3, 0x03);
    x = 0x00;
    myMapper->writeCPU(0x0589, 0x06);
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    if (a != 0x08) {
        x = 0x16;
        if (a == 0x09) {
            goto L_0081EC;
        }
        x = 0x2C;
        if (a == 0x0A) {
            goto L_008202;
        }
        x = 0x42;
        if (a == 0x0B) {
            goto L_008202;
        }
        popAddress();
        return;
    }
L_0081EC:
    myMapper->writeCPU(0x05BF, 0x17);
    a = 0x08;
    myMapper->writeCPU(0x05C0, a);
    myMapper->writeCPU(0x05C1, a);
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x81FE);
    jump(0x821A);
    if (handleReturnAddress(poppedEntry.value, 0x81FE)) return;
    jump(0x82BF);
    return;
L_008202:
    myMapper->writeCPU(0x05BF, 0x02);
    myMapper->writeCPU(0x05C0, 0x09);
    a = 0x13;
    myMapper->writeCPU(0x05C1, a);
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x8216);
    jump(0x821A);
    if (handleReturnAddress(poppedEntry.value, 0x8216)) return;
    jump(0x82BF);
    return;
}

void game::SUB_00821A() {
    myMapper->writeCPU(0x041B, 0x06);
    a = 0x00;
    myMapper->writeCPU(0x05B5, a);
    myMapper->writeCPU(0x05CD, a);
    myMapper->writeCPU(0x03FD, a);
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
    myMapper->writeCPU(0x05D2, a);
    myMapper->writeCPU(0x05D1, a);
    myMapper->writeCPU(0x05D0, a);
    myMapper->writeCPU(0x059D, a);
    myMapper->writeCPU(0x0091, 0x64);
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x8452 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x8453 + x));
    myMapper->writeCPU(0x0587, myMapper->readCPU(0x8454 + x));
    myMapper->writeCPU(0x0588, myMapper->readCPU(0x8455 + x));
    myMapper->writeCPU(0x05BE, myMapper->readCPU(0x8456 + x));
    if (myMapper->readCPU(0x059C) == 0) {
        goto L_008266;
    }
    myMapper->writeCPU(0x05BE, 0x00);
L_008266:
    myMapper->writeCPU(0x0092, myMapper->readCPU(0x8457 + x));
    myMapper->writeCPU(0x0093, myMapper->readCPU(0x8458 + x));
    myMapper->writeCPU(0x000C, myMapper->readCPU(0x8459 + x));
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x845A + x));
    myMapper->writeCPU(0x009A, myMapper->readCPU(0x845B + x));
    myMapper->writeCPU(0x009B, myMapper->readCPU(0x845C + x));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x845D + x));
    myMapper->writeCPU(0x009D, myMapper->readCPU(0x845E + x));
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x845F + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x8460 + x));
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x8461 + x));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x8462 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x8463 + x));
    a = myMapper->readCPU(0x8464 + x);
    myMapper->writeCPU(0x000F, a);
    y = myMapper->readCPU(0x8465 + x);
    pushAddress(0x82B1);
    jump(0x83A3);
    if (handleReturnAddress(poppedEntry.value, 0x82B1)) return;
    a = myMapper->readCPU(0x8466 + x);
    y = myMapper->readCPU(0x8467 + x);
    x = a;
    pushAddress(0x82BB);
    jump(0xDC63);
    if (handleReturnAddress(poppedEntry.value, 0x82BB)) return;
    jump(0xDEF4);
    return;
}

void game::SUB_0082BF() {
    myMapper->writeCPU(0x0005, 0x9E);
    myMapper->writeCPU(0x0006, 0xE9);
    myMapper->writeCPU(0x0007, 0xDE);
    a = 0xE9;
    myMapper->writeCPU(0x0008, a);
    pushAddress(0x82D1);
    jump(0xDD83);
    if (handleReturnAddress(poppedEntry.value, 0x82D1)) return;
    pushAddress(0x82D4);
    jump(0x83D7);
    if (handleReturnAddress(poppedEntry.value, 0x82D4)) return;
    a = myMapper->readCPU(0x0042);
    opORA(0x80);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    pushAddress(0x82E1);
    jump(0xDCFD);
    if (handleReturnAddress(poppedEntry.value, 0x82E1)) return;
    pushAddress(0x82E4);
    jump(0x802D);
    if (handleReturnAddress(poppedEntry.value, 0x82E4)) return;
    a = 0x00;
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x05AF, a);
    goto L_00830C;
L_0082EF:
    pushAddress(0x82F1);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0x82F1)) return;
    a = myMapper->readCPU(0x05D1);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0011);
    pushAddress(0x82FC);
    SUB_01FFAA_SwitchCHRBank1();
    a = 0x02;
    pushAddress(0x8301);
    SUB_01FFD2_SwitchCHRBank0();
    a = myMapper->readCPU(0x0040);
    opAND(0xFE);
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0x830B);
    jump(0xDBDF);
    if (handleReturnAddress(poppedEntry.value, 0x830B)) return;
L_00830C:
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x8313);
        jump(0xE6E4);
        if (handleReturnAddress(poppedEntry.value, 0x8313)) return;
        pushAddress(0x8316);
        jump(0xE7DF);
        if (handleReturnAddress(poppedEntry.value, 0x8316)) return;
        pushAddress(0x8319);
        jump(0xE84A);
        if (handleReturnAddress(poppedEntry.value, 0x8319)) return;
        pushAddress(0x831C);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x831C)) return;
        pushAddress(0x831F);
        jump(0xE685);
        if (handleReturnAddress(poppedEntry.value, 0x831F)) return;
        pushAddress(0x8322);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x8322)) return;
        pushAddress(0x8325);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x8325)) return;
        pushAddress(0x8328);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0x8328)) return;
    }
    //do {
    //    opBIT(myMapper->readCPU(PPU_STATUS));
    //} while (!flgV);
	wait(2);
    needWaitScanline = true;
    waitScanline = 32;
    wait(3);
    a = myMapper->readCPU(0x00B9);
    if (a == 0x10) {
        a = myMapper->readCPU(0x058C);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x058C, 1);
            a = myMapper->readCPU(0x058D);
            pushAddress(0x835E);
            jump(0xE9E6);
            if (handleReturnAddress(poppedEntry.value, 0x835E)) return;
            a = 0x0F;
            pushAddress(0x8363);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x8363)) return;
            goto L_0083A0;
        }
        opINC(0x058C, 1);
        pushAddress(0x836C);
        jump(0xEA06);
        if (handleReturnAddress(poppedEntry.value, 0x836C)) return;
        a = 0x0E;
        pushAddress(0x8371);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x8371)) return;
    }
    pushAddress(0x821C);
    jump(0xEA36);
    if (handleReturnAddress(poppedEntry.value, 0x821C)) return;
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x837C);
        jump(0xE61C);
        if (handleReturnAddress(poppedEntry.value, 0x837C)) return;
        pushAddress(0x837F);
        jump(0x8B93);
        if (handleReturnAddress(poppedEntry.value, 0x837F)) return;
        pushAddress(0x8382);
        jump(0x84CE);
        if (handleReturnAddress(poppedEntry.value, 0x8382)) return;
        x = myMapper->readCPU(0x0654);
        setLoadFlag(x);
        if (flgZ) {
            goto L_008394;
        }
        myMapper->writeCPU(0x0385 + x, myMapper->readCPU(0x0385));
        a = myMapper->readCPU(0x03A3);
        myMapper->writeCPU(0x03A3 + x, a);
    L_008394:
        pushAddress(0x8396);
        jump(0xE1F0);
        if (handleReturnAddress(poppedEntry.value, 0x8396)) return;
        pushAddress(0x8399);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8399)) return;
        pushAddress(0x839C);
        jump(0xCA15);
        if (handleReturnAddress(poppedEntry.value, 0x839C)) return;
        pushAddress(0x839F);
        jump(0x9A10);
        if (handleReturnAddress(poppedEntry.value, 0x839F)) return;
    }
L_0083A0:
    goto L_0082EF;
}

void game::SUB_0083A3() {
    myMapper->writeCPU(0x05AC, x);
    x = 0x00;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0x83B7 + y));
        opINX(1);
        opINY(1);
    } while (x != 0x10);
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_0083D7() {
    a = myMapper->readCPU(0x0042);
    opAND(0x7F);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    a = myMapper->readCPU(SCROLL_FINE);
    opPHA();
    a = myMapper->readCPU(SCROLL_LARGE);
    opPHA();
    myMapper->writeCPU(SCROLL_LARGE, 0x00);
    a = myMapper->readCPU(0x00A0);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    myMapper->writeCPU(SCROLL_FINE, a);
    opDEC(SCROLL_LARGE, 1);
    myMapper->writeCPU(0x05AF, 0x08);
    do {
        a = myMapper->readCPU(0x00A0);
        pushAddress(0x8413);
        jump(0xE20C);
        if (handleReturnAddress(poppedEntry.value, 0x8413)) return;
        pushAddress(0x8416);
        jump(0x968C);
        if (handleReturnAddress(poppedEntry.value, 0x8416)) return;
        pushAddress(0x8419);
        jump(0x9A10);
        if (handleReturnAddress(poppedEntry.value, 0x8419)) return;
        pushAddress(0x841C);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x841C)) return;
        pushAddress(0x841F);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x841F)) return;
        pushAddress(0x8422);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8422)) return;
        pushAddress(0x8425);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8425)) return;
        pushAddress(0x8428);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x8428)) return;
        pushAddress(0x842B);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x842B)) return;
        pushAddress(0x842E);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x842E)) return;
        pushAddress(0x8431);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x8431)) return;
        flgC = false;
        a = myMapper->readCPU(SCROLL_FINE);
        opADC(0x20);
        myMapper->writeCPU(SCROLL_FINE, a);
        if (!flgC) {
            goto L_008440;
        }
        opINC(SCROLL_LARGE, 1);
    L_008440:
        opINC(0x00A0, 1);
        opDEC(0x05AF, 1);
    } while (!flgN);
    opDEC(0x00A0, 1);
    opPLA();
    myMapper->writeCPU(SCROLL_LARGE, a);
    opPLA();
    myMapper->writeCPU(SCROLL_FINE, a);
    popAddress();
}

void game::SUB_0084CE() {
    if (myMapper->readCPU(0x05D0) == 0) {
        goto L_0084F3;
    }
    if (myMapper->readCPU(0x0439) >= 0xC0) {
        x = 0x00;
        myMapper->writeCPU(0x05A3, x);
        myMapper->writeCPU(0x05A4, x);
        x = myMapper->readCPU(0x0051);
        if (myMapper->readCPU((0x0059 + x) & 0x00ff) == 0x07) {
            if (myMapper->readCPU(0x0476) != 0) {
                goto L_0084F3;
            }
        }
        opDEX(1);
        myMapper->writeCPU(0x05D0, x);
    }
L_0084F3:
    a = 0x00;
    myMapper->writeCPU(0x05CF, a);
    pushAddress(0x84FA);
    jump(0x8AB1);
    if (handleReturnAddress(poppedEntry.value, 0x84FA)) return;
    a = myMapper->readCPU(0x05D2);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
            if (!flgN) {
                goto L_00851D;
            }
        }
        a = myMapper->readCPU(0x05C3);
        if (a != 0x01) {
            a = myMapper->readCPU(0x05C4);
            if (a != 0x01) {
                goto L_00851D;
            }
        }
        x = 0x00;
        jump(0x8A8B);
        return;
    L_00851D:
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
        }
        else {
            opBIT(myMapper->readCPU(0x059F));
            if (flgN) {
            }
            else {
                a = myMapper->readCPU(0x05C3);
                myMapper->writeCPU(0x05C6, a);
                if (a < 0x10) {
                    if (a < 0x08) {
                        goto L_00853E;
                    }
                    goto L_008607;
                L_00853E:
                    a = myMapper->readCPU(0x059D);
                    setLoadFlag(a);
                    if (flgN) {
                        goto L_008614;
                    }
                    x = 0x00;
                    y = 0x00;
                    jump(0x8A72);
                    return;
                }
                flgC = true;
                opSBC(0x10);
                x = a;
                if (myMapper->readCPU(0x05D0) == 0xFF) {
                    a = 0xFF;
                    myMapper->writeCPU(0x05D1, a);
                    popAddress();
                    return;
                }
                a = myMapper->readCPU(0x8AEC + x);
                myMapper->writeCPU(0x05AA, a);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x05AB, a);
                myMapper->writeCPU(0x05A6, myMapper->readCPU(0x8B04 + x));
                myMapper->writeCPU(0x05A7, myMapper->readCPU(0x8B1C + x));
                myMapper->writeCPU(0x05A8, myMapper->readCPU(0x8B34 + x));
                if (myMapper->readCPU(0x059D) != 0) {
                    a = 0x25;
                    pushAddress(0x8587);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x8587)) return;
                    x = 0x18;
                    pushAddress(0x858C);
                    jump(0x8A55);
                    if (handleReturnAddress(poppedEntry.value, 0x858C)) return;
                }
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
                a = myMapper->readCPU(0x05C6);
                x = 0x00;
                myMapper->writeCPU(0x0657, x);
                if (a == 0x1A) {
                    a = 0xFF;
                    myMapper->writeCPU(0x0657, a);
                }
                if (a == 0x1E) {
                    myMapper->writeCPU(0x0655, x);
                }
                myMapper->writeCPU(0x05A5, 0x00);
                x = 0x01;
                if (a != 0x18) {
                    x = 0x02;
                    if (a != 0x19) {
                        goto L_0085CE;
                    }
                }
                myMapper->writeCPU(0x05A5, x);
                a = 0x1A;
                pushAddress(0x85CA);
                jump(0xEA16);
                if (handleReturnAddress(poppedEntry.value, 0x85CA)) return;
                goto L_008614;
            L_0085CE:
                if (a == 0x1D) {
                    a = 0x04;
                    myMapper->writeCPU(0x05A4, a);
                    myMapper->writeCPU(0x05AA, a);
                    a = 0x00;
                    myMapper->writeCPU(0x05A3, a);
                    x = 0xF8;
                    y = 0x00;
                    pushAddress(0x85E5);
                    jump(0x8A63);
                    if (handleReturnAddress(poppedEntry.value, 0x85E5)) return;
                    myMapper->writeCPU(0x05A7, 0x10);
                    a = 0x15;
                    pushAddress(0x85EF);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x85EF)) return;
                    goto L_008614;
                }
                x = 0xFD;
                myMapper->writeCPU(0x05CB, x);
                if (a == 0x1C) {
                    x = myMapper->readCPU(0x05B8);
                    setLoadFlag(x);
                    if (!flgZ) {
                        opDEC(0x05B8, 1);
                    }
                }
                goto L_008614;
            L_008607:
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
            }
        }
    }
L_008614:
    y = myMapper->readCPU(0x004B);
    a = y;
    opAND(0x01);
    if (flgZ) {
        goto L_00862B;
    }
    if (myMapper->readCPU(0x0657) == 0) {
        do {
            a = 0x00;
            myMapper->writeCPU(0x05CD, a);
            pushAddress(0x8627);
            jump(0xE195);
            if (handleReturnAddress(poppedEntry.value, 0x8627)) return;
            goto L_00863D;
        L_00862B:
            a = y;
            opAND(0x02);
            if (flgZ) {
                goto L_00863D;
            }
        } while (myMapper->readCPU(0x0657) != 0);
    }
    a = 0x80;
    myMapper->writeCPU(0x05CD, a);
    pushAddress(0x863C);
    jump(0xE195);
    if (handleReturnAddress(poppedEntry.value, 0x863C)) return;
L_00863D:
    if (myMapper->readCPU(0x059D) == 0) {
        if (myMapper->readCPU(0x0654) != 0) {
            goto L_008673;
        }
        a = y;
        opAND(0x04);
        if (!flgZ) {
            if (myMapper->readCPU(0x05C3) == 0x17) {
                goto L_008665;
            }
            if (myMapper->readCPU(0x05C9) != 0) {
                goto L_008682;
            }
            x = 0x15;
            a = 0x10;
            myMapper->writeCPU(0x05C9, a);
            pushAddress(0x8661);
            jump(0x8A5A);
            if (handleReturnAddress(poppedEntry.value, 0x8661)) return;
            goto L_008682;
        L_008665:
            a = myMapper->readCPU(0x058E);
            y = myMapper->readCPU(0x0051);
            myMapper->writeCPU(0x0059 + y, a);
            a = 0xFE;
            myMapper->writeCPU(0x05D1, a);
            popAddress();
            return;
        }
    }
L_008673:
    if (myMapper->readCPU(0x05C9) != 0) {
        myMapper->writeCPU(0x05C9, 0x00);
        myMapper->writeCPU(0x05CA, 0x18);
    }
L_008682:
    a = myMapper->readCPU(0x004C);
    opAND(0x80);
    if (!flgZ) {
        if (myMapper->readCPU(0x0655) == 0) {
            goto L_00869E;
        }
        a = myMapper->readCPU(0x059D);
        setLoadFlag(a);
        if (flgZ) {
            x = 0xFB;
            y = 0x00;
            pushAddress(0x8698);
            jump(0x8A63);
            if (handleReturnAddress(poppedEntry.value, 0x8698)) return;
            a = 0x10;
            pushAddress(0x869D);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x869D)) return;
        }
    }
L_00869E:
    if (myMapper->readCPU(0x05A0) != 0) {
        opDEC(0x05A0, 1);
        a = y;
        opAND(0x80);
        if (!flgZ) {
            if (myMapper->readCPU(0x059E) == 0xF8) {
                goto L_0086C0;
            }
            flgC = true;
            a = myMapper->readCPU(0x059E);
            opSBC(0x01);
            myMapper->writeCPU(0x059E, a);
            if (!flgC) {
                opDEC(0x059F, 1);
            }
        }
    }
L_0086C0:
    a = myMapper->readCPU(0x059D);
    setLoadFlag(a);
    if (!flgZ) {
        opBIT(myMapper->readCPU(0x059F));
        if (flgN) {
            if (myMapper->readCPU(0x05C4) < 0x10) {
                goto L_0086DC;
            }
            a = 0x00;
            myMapper->writeCPU(0x059F, a);
            myMapper->writeCPU(0x05A0, a);
            myMapper->writeCPU(0x059E, a);
        }
    L_0086DC:
        flgC = false;
        a = myMapper->readCPU(0x03C1);
        opADC(myMapper->readCPU(0x059E));
        myMapper->writeCPU(0x03C1, a);
        a = myMapper->readCPU(0x03DF);
        opADC(myMapper->readCPU(0x059F));
        myMapper->writeCPU(0x03DF, a);
        if (a == 0x02) {
            myMapper->writeCPU(0x05D1, 0x02);
        }
        opINC(0x05A9, 1);
        a = myMapper->readCPU(0x05A9);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x059E) == 0x08) {
                goto L_008711;
            }
            opINC(0x059E, 1);
            if (flgZ) {
                opINC(0x059F, 1);
            }
        }
    }
L_008711:
    a = myMapper->readCPU(0x0654);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x004C);
        opAND(0x40);
        if (!flgZ) {
            if (myMapper->readCPU(0x0655) == 0) {
                goto L_008730;
            }
            x = 0x01;
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (!flgZ) {
                x = 0x07;
            }
            pushAddress(0x872C);
            jump(0x8A55);
            if (handleReturnAddress(poppedEntry.value, 0x872C)) return;
            goto L_00873C;
        L_008730:
            x = 0x0D;
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (!flgZ) {
                x = 0x11;
            }
            pushAddress(0x873B);
            jump(0x8A55);
            if (handleReturnAddress(poppedEntry.value, 0x873B)) return;
        }
    }
L_00873C:
    pushAddress(0x873E);
    jump(0x8796);
    if (handleReturnAddress(poppedEntry.value, 0x873E)) return;
    a = myMapper->readCPU(0x05A1);
    setLoadFlag(a);
    if (flgZ) {
        y = 0x05;
        x = 0x01;
        a = myMapper->readCPU(0x05A4);
        setLoadFlag(a);
        if (!flgN) {
            x = 0x03;
        }
        pushAddress(0x8751);
        jump(0xE587);
        if (handleReturnAddress(poppedEntry.value, 0x8751)) return;
        myMapper->writeCPU(0x05C7, a);
        if (a < 0x08) {
            a = myMapper->readCPU(0x059D);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00877A;
            }
            a = myMapper->readCPU(0x059F);
            setLoadFlag(a);
            if (flgN) {
                goto L_00877A;
            }
            y = 0x06;
            pushAddress(0x8767);
            jump(0xE587);
            if (handleReturnAddress(poppedEntry.value, 0x8767)) return;
            myMapper->writeCPU(0x05C8, a);
            if (a < 0x08) {
                goto L_00877A;
            }
        }
        a = 0x00;
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
        myMapper->writeCPU(0x05A5, a);
    }
L_00877A:
    pushAddress(0x877C);
    jump(0xE0C9);
    if (handleReturnAddress(poppedEntry.value, 0x877C)) return;
    pushAddress(0x877F);
    jump(0xDED2);
    if (handleReturnAddress(poppedEntry.value, 0x877F)) return;
    opCMP(y, myMapper->readCPU(SCROLL_LARGE));
    if (!flgZ) {
        if (flgC) {
            goto L_00878F;
        }
    }
    else {
        if (x < myMapper->readCPU(SCROLL_FINE)) {
            goto L_008795;
        }
    L_00878F:
        myMapper->writeCPU(SCROLL_FINE, x);
        myMapper->writeCPU(SCROLL_LARGE, y);
    }
L_008795:
    popAddress();
}

void game::SUB_008796() {
    x = myMapper->readCPU(0x05CA);
    setLoadFlag(x);
    if (flgZ) {
        jump(0x88CD);
        return;
    }
    a = myMapper->readCPU(0x84AA + x);
    setLoadFlag(a);
    if (!flgN) {
        x = a;
        opAND(0x3F);
        opORA(myMapper->readCPU(0x05CD));
        myMapper->writeCPU(0x03FD, a);
        if (x != 0x0A) {
            if (x != 0x04) {
                goto L_0087B7;
            }
        }
        pushAddress(0x87B6);
        jump(0x87F1);
        if (handleReturnAddress(poppedEntry.value, 0x87B6)) return;
    L_0087B7:
        opDEC(0x05CE, 1);
        if (flgN) {
            goto L_0087D0;
        }
        popAddress();
        return;
    }
    x = 0x00;
    myMapper->writeCPU(0x05CA, x);
    if (myMapper->readCPU(0x059D) == 0) {
        goto L_0087CF;
    }
    a = 0x1F;
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
L_0087CF:
    popAddress();
    return;
L_0087D0:
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    opINC(0x05CA, 1);
    if (x == 0x05) {
        jump(0x8808);
        return;
    }
    if (x == 0x0B) {
        jump(0x8808);
        return;
    }
    if (x == 0x07) {
        jump(0x8844);
        return;
    }
    if (x == 0x0D) {
        jump(0x8844);
        return;
    }
    if (x == 0x47) {
        jump(0x8844);
        return;
    }
    if (x == 0x4D) {
        jump(0x8844);
        return;
    }
    popAddress();
}

void game::SUB_0087F1() {
    y = 0x00;
    a = myMapper->readCPU(0x0656);
    setLoadFlag(a);
    if (!flgN) {
        goto L_0087F9;
    }
    opDEY(1);
L_0087F9:
    flgC = false;
    opADC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0385, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3));
    myMapper->writeCPU(0x03A3, a);
    popAddress();
}

void game::SUB_008808() {
    y = 0x01;
    myMapper->writeCPU(0x05BC, y);
    pushAddress(0x880F);
    jump(0x895F);
    if (handleReturnAddress(poppedEntry.value, 0x880F)) return;
    if (!flgZ) {
        y = 0x02;
        pushAddress(0x8816);
        jump(0x895F);
        if (handleReturnAddress(poppedEntry.value, 0x8816)) return;
        if (!flgZ) {
            y = 0x06;
            pushAddress(0x881D);
            jump(0x895F);
            if (handleReturnAddress(poppedEntry.value, 0x881D)) return;
            if (!flgZ) {
                y = 0x07;
                pushAddress(0x8824);
                jump(0x895F);
                if (handleReturnAddress(poppedEntry.value, 0x8824)) return;
                if (!flgZ) {
                    popAddress();
                    return;
                }
            }
        }
    }
    a = 0x0D;
    pushAddress(0x882C);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x882C)) return;
    a = myMapper->readCPU(0x050B + y);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x050B + y, a);
    if (!flgN) {
        goto L_00883D;
    }
    x = 0x00;
    jump(0x9130);
    return;
L_00883D:
    a = y;
    x = a;
    y = 0x09;
    jump(0x91E2);
    return;
}

void game::SUB_008844() {
    a = myMapper->readCPU(0x0595);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x0596, 1);
        if (flgZ) {
            myMapper->writeCPU(0x0595, 0x00);
            a = 0x02;
            myMapper->writeCPU(0x0594, a);
        }
        if (x >= 0x40) {
            if (a == 0x04) {
                goto L_0088AD;
            }
            if (a == 0x05) {
                goto L_0088AD;
            }
            x = 0x00;
            y = 0x03;
            if (myMapper->readCPU(0x0475 + y) == 0) {
                a = myMapper->readCPU(0x0595);
                if (a == 0x01) {
                    goto L_008897;
                }
                if (a == 0x02) {
                    goto L_008879;
                }
            }
        }
        popAddress();
        return;
    L_008879:
        pushAddress(0x88AF);
        jump(0x89FE);
        if (handleReturnAddress(poppedEntry.value, 0x88AF)) return;
        y = 0x04;
        x = 0xFA;
        pushAddress(0x8882);
        jump(0x89FE);
        if (handleReturnAddress(poppedEntry.value, 0x8882)) return;
        y = 0x05;
        x = 0x06;
        pushAddress(0x8889);
        jump(0x89FE);
        if (handleReturnAddress(poppedEntry.value, 0x8889)) return;
        a = 0x00;
        myMapper->writeCPU(0x0497, a);
        myMapper->writeCPU(0x0498, a);
        a = 0x07;
        jump(0xEA1B);
        return;
    L_008897:
        pushAddress(0x88C7);
        jump(0x89FE);
        if (handleReturnAddress(poppedEntry.value, 0x88C7)) return;
        x = 0xFA;
        y = 0x04;
        pushAddress(0x88A0);
        jump(0x89FE);
        if (handleReturnAddress(poppedEntry.value, 0x88A0)) return;
        x = 0x06;
        y = 0x05;
        pushAddress(0x88A7);
        jump(0x89FE);
        if (handleReturnAddress(poppedEntry.value, 0x88A7)) return;
        a = 0x08;
        jump(0xEA1B);
        return;
    }
L_0088AD:
    x = 0x00;
    y = 0x03;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x04;
        if (myMapper->readCPU(0x0475 + y) != 0) {
            y = 0x05;
            if (myMapper->readCPU(0x0475 + y) == 0) {
                goto L_0088C5;
            }
            popAddress();
            return;
        }
    }
L_0088C5:
    a = 0x06;
    pushAddress(0x88C9);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x88C9)) return;
    jump(0x89FE);
    return;
}

void game::SUB_0088CD() {
    a = 0x09;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        if (myMapper->readCPU(0x0654) != 0) {
            goto L_0088E3;
        }
        if (myMapper->readCPU(0x059D) == 0) {
            goto L_0088EC;
        }
        a = 0x1F;
        goto L_0088E5;
    L_0088E3:
        a = 0x00;
    }
L_0088E5:
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    popAddress();
    return;
L_0088EC:
    a = myMapper->readCPU(0x05C3);
    opCMP(a, 0x11);
    if (!flgZ) {
        opCMP(a, 0x12);
        if (!flgZ) {
            goto L_0088FC;
        }
    }
    if (myMapper->readCPU(0x05CF) == 0) {
        goto L_0088E3;
    }
L_0088FC:
    a = myMapper->readCPU(0x05A3);
    opORA(myMapper->readCPU(0x05A4));
    if (!flgZ) {
        opDEC(0x05A2, 1);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x05A4));
            if (flgN) {
                a = myMapper->readCPU(0x05A3);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x05A4);
                opEOR(0xFF);
                opADC(0x00);
            }
            else {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x05A3));
                a = myMapper->readCPU(0x05A4);
            }
            opROL_M(0x0000, 1);
            opROL_A(1);
            x = a;
            myMapper->writeCPU(0x05A2, myMapper->readCPU(0x8AE7 + x));
            opINC(0x03FD, 1);
        }
    }
    a = myMapper->readCPU(0x03FD);
    opAND(0x03);
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    opAND(0x7F);
    if (a != myMapper->readCPU(0x00B8)) {
        myMapper->writeCPU(0x00B8, a);
        if (myMapper->readCPU(0x00FD) == 0) {
            x = 0x23;
            a = myMapper->readCPU(0x00B8);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00895A;
            }
            x = 0x24;
            if (a != 0x02) {
                goto L_00895E;
            }
        L_00895A:
            a = x;
            jump(0xEA1B);
            return;
        }
    }
L_00895E:
    popAddress();
}

void game::SUB_00895F() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x05) {
            goto L_0089C6;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_0089C6;
            }
            if (myMapper->readCPU(0x0529 + y) < 0x09) {
                if (myMapper->readCPU(0x03DF) != 0) {
                    goto L_0089C6;
                }
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(myMapper->readCPU(0x05C9));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x041B + y);
                if (a != 0x06) {
                    if (a != 0x07) {
                        goto L_0089C9;
                    }
                }
                a = myMapper->readCPU(0x03C1 + y);
                flgC = false;
                opADC(0x20);
                flgC = true;
                opSBC(myMapper->readCPU(0x0000));
                if (!flgN) {
                    if (a >= 0x30) {
                        goto L_0089C6;
                    }
                    flgC = true;
                    opBIT(myMapper->readCPU(0x03FD));
                    if (!flgN) {
                        goto L_0089B8;
                    }
                    a = myMapper->readCPU(0x0439);
                    opSBC(myMapper->readCPU(0x0439 + y));
                    if (flgC) {
                        if (a >= 0x08) {
                            goto L_0089C6;
                        }
                        do {
                            do {
                                a = 0x00;
                                setLoadFlag(a);
                                popAddress();
                                return;
                            L_0089B8:
                                a = myMapper->readCPU(0x0439 + y);
                                opSBC(myMapper->readCPU(0x0439));
                                if (!flgC) {
                                    goto L_0089C6;
                                }
                                opCMP(a, 0x10);
                            } while (flgZ);
                        } while (!flgC);
                    }
                }
            }
        }
    }
L_0089C6:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
    return;
L_0089C9:
    a = myMapper->readCPU(0x03C1 + y);
    flgC = false;
    opADC(0x08);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    if (flgC) {
        if (a >= 0x18) {
            goto L_0089FB;
        }
        flgC = true;
        opBIT(myMapper->readCPU(0x03FD));
        if (!flgN) {
            goto L_0089ED;
        }
        a = myMapper->readCPU(0x0439);
        opSBC(myMapper->readCPU(0x0439 + y));
        if (flgC) {
            if (a >= 0x10) {
                goto L_0089FB;
            }
            do {
                do {
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                L_0089ED:
                    a = myMapper->readCPU(0x0439 + y);
                    opSBC(myMapper->readCPU(0x0439));
                    if (!flgC) {
                        goto L_0089FB;
                    }
                    opCMP(a, 0x18);
                } while (flgZ);
            } while (!flgC);
        }
    }
L_0089FB:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0089FE() {
    myMapper->writeCPU(0x04B1 + y, x);
    a = myMapper->readCPU(0x0385);
    opBIT(myMapper->readCPU(0x05CD));
    if (flgN) {
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        a = 0xFA;
        myMapper->writeCPU(0x0493 + y, a);
    }
    else {
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        myMapper->writeCPU(0x0493 + y, 0x06);
    }
    myMapper->writeCPU(0x03DF + y, myMapper->readCPU(0x03DF));
    a = 0x08;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        goto L_008A42;
    }
    a = 0x18;
L_008A42:
    flgC = false;
    opADC(myMapper->readCPU(0x03C1));
    myMapper->writeCPU(0x03C1 + y, a);
    myMapper->writeCPU(0x03FD + y, myMapper->readCPU(0x05CD));
    a = 0x01;
    myMapper->writeCPU(0x0475 + y, a);
    popAddress();
}

void game::SUB_008A55() {
    a = myMapper->readCPU(0x05CA);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x8A62);
        return;
    }
    SUB_008A5A();
    return;
}

void game::SUB_008A5A() {
    myMapper->writeCPU(0x05CA, x);
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    SUB_008A62();
    return;
}

void game::SUB_008A62() {
    popAddress();
}

void game::SUB_008A63() {
    if (myMapper->readCPU(0x05A1) != 0) {
        goto L_008A6D;
    }
    a = myMapper->readCPU(0x05A6);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x8A72);
        return;
    }
L_008A6D:
    a = 0x40;
    myMapper->writeCPU(0x05A6, a);
    SUB_008A72();
    return;
}

void game::SUB_008A72() {
    myMapper->writeCPU(0x05A0, y);
    myMapper->writeCPU(0x059E, x);
    x = 0x00;
    myMapper->writeCPU(0x05A9, x);
    opBIT(myMapper->readCPU(0x059E));
    if (!flgN) {
        goto L_008A83;
    }
    opDEX(1);
L_008A83:
    myMapper->writeCPU(0x059F, x);
    opDEX(1);
    myMapper->writeCPU(0x059D, x);
    popAddress();
}

void game::SUB_008A8B() {
    pushAddress(0x8A8D);
    jump(0x8A99);
    if (handleReturnAddress(poppedEntry.value, 0x8A8D)) return;
    a = 0x1F;
    pushAddress(0x8A92);
    jump(0xEA16);
    if (handleReturnAddress(poppedEntry.value, 0x8A92)) return;
    a = 0xFF;
    myMapper->writeCPU(0x05D2, a);
    popAddress();
}

void game::SUB_008A99() {
    y = 0x02;
    if (!(myMapper->readCPU(0x0493 + x) & 0x80)) {
        goto L_008AA2;
    }
    y = 0xFE;
L_008AA2:
    myMapper->writeCPU(0x05A4, y);
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    x = 0xFB;
    y = 0x00;
    jump(0x8A63);
    return;
}

void game::SUB_008AB1() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF));
    y = myMapper->readCPU(0x03C1);
    flgC = true;
    a = myMapper->readCPU(0x0385);
    opSBC(0x04);
    x = a;
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    myMapper->writeCPU(0x0095, a);
    pushAddress(0x8AC9);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x8AC9)) return;
    x = 0x02;
    y = 0x06;
    pushAddress(0x8AD0);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8AD0)) return;
    myMapper->writeCPU(0x05C3, a);
    y = 0x00;
    pushAddress(0x8AD8);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8AD8)) return;
    myMapper->writeCPU(0x05C4, a);
    x = 0x02;
    y = 0x05;
    pushAddress(0x8AE2);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8AE2)) return;
    myMapper->writeCPU(0x05C5, a);
    popAddress();
}

void game::SUB_008B93() {
    pushAddress(0x8B95);
    jump(0x968C);
    if (handleReturnAddress(poppedEntry.value, 0x8B95)) return;
    x = 0x00;
    myMapper->writeCPU(0x0659, x);
    myMapper->writeCPU(0x0654, x);
    myMapper->writeCPU(0x05BC, x);
    myMapper->writeCPU(0x05A1, x);
    opDEX(1);
    myMapper->writeCPU(0x0655, x);
    x = 0x01;
    myMapper->writeCPU(0x05CC, myMapper->readCPU(0x0587));
    SUB_008BB0();
    return;
}

void game::SUB_008BB0() {
    myMapper->writeCPU(0x05AC, x);
    y = myMapper->readCPU(0x0475 + x);
    setLoadFlag(y);
    if (flgZ) {
        jump(0x8BCB);
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x8B59 + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x8B76 + y));
    a = 0x8B;
    opPHA();
    a = 0xCA;
    opPHA();
    pushManualAddress(0x8BCA);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_008BCB() {
    opINC(0x05AF, 1);
    x = myMapper->readCPU(0x05AC);
    opINX(1);
    opDEC(0x05CC, 1);
    if (!flgZ) {
        jump(0x8BB0);
        return;
    }
    SUB_008BD7();
    return;
}

void game::SUB_008BD7() {
    a = myMapper->readCPU(0x003F);
    flgC = false;
    opADC(myMapper->readCPU(0x05AF));
    myMapper->writeCPU(0x05AF, a);
    popAddress();
}

void game::SUB_008BE1() {
    y = 0x09;
    pushAddress(0x8BE5);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x8BE5)) return;
    if (!flgN) {
        pushAddress(0x8BEA);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8BEA)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x02);
    opLSR_A(1);
    opADC(0x04);
    myMapper->writeCPU(0x03FD + x, a);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x03C1 + x, a);
    if (a >= 0xD0) {
        goto L_008C06;
    }
    popAddress();
    return;
L_008C06:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_008C0C() {
    y = 0x06;
    pushAddress(0x8C10);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x8C10)) return;
    if (!flgN) {
        pushAddress(0x8C15);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8C15)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x02);
    opLSR_A(1);
    opADC(0x81);
    myMapper->writeCPU(0x03FD + x, a);
    a = myMapper->readCPU(0x0385 + x);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0385 + x, a);
    if (flgC) {
        goto L_008C31;
    }
    opDEC(0x03A3 + x, 1);
L_008C31:
    popAddress();
}

void game::SUB_008C32() {
    opDEC(0x03A3 + x, 1);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x0457 + x, 0x00);
    opINC(0x0475 + x, 1);
    SUB_008C47();
    return;
}

void game::SUB_008C47() {
    a = myMapper->readCPU(0x003F);
    opAND(0x02);
    opLSR_A(1);
    opADC(0x03);
    myMapper->writeCPU(0x03FD + x, a);
    if (myMapper->readCPU(0x0457 + x) != 0x01) {
        a = myMapper->readCPU(0x05D0);
        setLoadFlag(a);
        if (flgZ) {
            goto L_008C69;
        }
        pushAddress(0x8C5F);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8C5F)) return;
        x = myMapper->readCPU(0x05AC);
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
    return;
L_008C69:
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0385 + x, a);
    if (flgC) {
        opINC(0x03A3 + x, 1);
    }
    y = 0x0B;
    pushAddress(0x8C7B);
    jump(0x9968);
    if (handleReturnAddress(poppedEntry.value, 0x8C7B)) return;
    if (flgN) {
        goto L_008CB0;
    }
    a = myMapper->readCPU(0x03C1 + x);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x03C1, a);
    myMapper->writeCPU(0x03DF, 0x00);
    a = myMapper->readCPU(0x0385);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0385, a);
    a = myMapper->readCPU(0x03A3);
    opADC(0x00);
    myMapper->writeCPU(0x03A3, a);
    a = 0xFF;
    myMapper->writeCPU(0x05A1, a);
    myMapper->writeCPU(0x05D2, a);
    a = 0x00;
    myMapper->writeCPU(0x0655, a);
    myMapper->writeCPU(0x059D, a);
    myMapper->writeCPU(0x05A6, a);
L_008CB0:
    popAddress();
}

void game::SUB_008CB1() {
    myMapper->writeCPU(0x04ED + x, 0x0A);
    myMapper->writeCPU(0x050B + x, 0x03);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    myMapper->writeCPU(0x041B + x, 0x07);
    opINC(0x0475 + x, 1);
    a = 0x80;
    myMapper->writeCPU(0x0493 + x, a);
    SUB_008CCE();
    return;
}

void game::SUB_008CCE() {
    y = 0x05;
    pushAddress(0x8CD2);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x8CD2)) return;
    if (!flgN) {
        pushAddress(0x8CD7);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8CD7)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x05AF);
    opAND(0x33);
    if (flgZ) {
        pushAddress(0x8CE4);
        jump(0x959D);
        if (handleReturnAddress(poppedEntry.value, 0x8CE4)) return;
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x02);
    opLSR_A(1);
    opADC(0x02);
    opORA(myMapper->readCPU(0x0493 + x));
    myMapper->writeCPU(0x03FD + x, a);
    if (myMapper->readCPU(0x0493 + x) != 0) {
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            goto L_008D16;
        }
        opDEC(0x03A3 + x, 1);
    }
    else {
        a = myMapper->readCPU(0x0385 + x);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            opINC(0x03A3 + x, 1);
        }
    }
L_008D16:
    opDEC(0x04CF + x, 1);
    if (flgZ) {
        myMapper->writeCPU(0x04CF + x, myMapper->readCPU(0x0565 + x));
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0x80);
        myMapper->writeCPU(0x0493 + x, a);
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (!flgZ) {
        goto L_008D42;
    }
    opINC(0x0529 + x, 1);
    a = myMapper->readCPU(0x0529 + x);
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0x8D43 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
L_008D42:
    popAddress();
}

void game::SUB_008D53() {
    myMapper->writeCPU(0x04ED + x, 0x0A);
    myMapper->writeCPU(0x050B + x, 0x05);
    myMapper->writeCPU(0x03FD + x, 0x00);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    a = 0x04;
    myMapper->writeCPU(0x041B + x, a);
    opINC(0x0475 + x, 1);
    SUB_008D70();
    return;
}

void game::SUB_008D70() {
    y = 0x03;
    pushAddress(0x8D74);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x8D74)) return;
    if (!flgN) {
        pushAddress(0x8D79);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8D79)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x0529 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_008DC9;
    }
    if (myMapper->readCPU(0x0493 + x) != 0) {
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            goto L_008DA6;
        }
        opDEC(0x03A3 + x, 1);
    }
    else {
        a = myMapper->readCPU(0x0385 + x);
        flgC = false;
        opADC(0x01);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            opINC(0x03A3 + x, 1);
        }
    }
L_008DA6:
    opDEC(0x04CF + x, 1);
    if (flgZ) {
        myMapper->writeCPU(0x04CF + x, myMapper->readCPU(0x0565 + x));
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0xFF);
        myMapper->writeCPU(0x0493 + x, a);
    }
    opINC(0x0547 + x, 1);
    a = myMapper->readCPU(0x0547 + x);
    opAND(0xCF);
    if (!flgZ) {
        goto L_008DC8;
    }
    myMapper->writeCPU(0x0529 + x, 0x37);
    do {
        do {
        L_008DC8:
            popAddress();
            return;
        L_008DC9:
            opDEC(0x0529 + x, 1);
        } while (!flgZ);
        pushAddress(0x8DD0);
        jump(0x9601);
        if (handleReturnAddress(poppedEntry.value, 0x8DD0)) return;
    } while (flgN);
    a = 0x18;
    pushAddress(0x8DD7);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x8DD7)) return;
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x18);
    myMapper->writeCPU(0x03C1 + y, a);
    myMapper->writeCPU(0x03DF + y, 0x00);
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x03A3 + x);
    opADC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    myMapper->writeCPU(0x0475 + y, 0x10);
    myMapper->writeCPU(0x041B + y, 0x07);
    myMapper->writeCPU(0x04ED + y, 0xFF);
    myMapper->writeCPU(0x03FD + y, 0x04);
    popAddress();
}

void game::SUB_008E0C() {
    myMapper->writeCPU(0x04ED + x, 0x0A);
    myMapper->writeCPU(0x050B + x, 0x05);
    myMapper->writeCPU(0x03FD + x, 0x01);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    a = 0x04;
    myMapper->writeCPU(0x041B + x, a);
    opINC(0x0475 + x, 1);
    SUB_008E29();
    return;
}

void game::SUB_008E29() {
    y = 0x03;
    pushAddress(0x8E2D);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x8E2D)) return;
    if (!flgN) {
        pushAddress(0x8E32);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8E32)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x0529 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_008E6C;
    }
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x03C1 + x, 1);
    }
    else {
        opINC(0x03C1 + x, 1);
    }
    opDEC(0x04CF + x, 1);
    if (flgZ) {
        myMapper->writeCPU(0x04CF + x, myMapper->readCPU(0x0565 + x));
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0xFF);
        myMapper->writeCPU(0x0493 + x, a);
    }
    opINC(0x0547 + x, 1);
    a = myMapper->readCPU(0x0547 + x);
    opAND(0x9F);
    if (!flgZ) {
        goto L_008E6B;
    }
    myMapper->writeCPU(0x0529 + x, 0x37);
    do {
    L_008E6B:
        popAddress();
        return;
    L_008E6C:
        opDEC(0x0529 + x, 1);
    } while (!flgZ);
    SUB_008E71();
    return;
}

void game::SUB_008E71() {
    pushAddress(0x8E73);
    jump(0x9601);
    if (handleReturnAddress(poppedEntry.value, 0x8E73)) return;
    if (flgN) {
        goto L_008EAE;
    }
    a = 0x18;
    pushAddress(0x8E7A);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x8E7A)) return;
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x03C1 + y, a);
    myMapper->writeCPU(0x03DF + y, 0x00);
    a = myMapper->readCPU(0x0385 + x);
    flgC = true;
    opSBC(0x20);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x03A3 + x);
    opSBC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    myMapper->writeCPU(0x0475 + y, 0x0F);
    myMapper->writeCPU(0x041B + y, 0x05);
    myMapper->writeCPU(0x04ED + y, 0xFF);
    myMapper->writeCPU(0x03FD + y, 0x81);
L_008EAE:
    popAddress();
}

void game::SUB_008EAF() {
    myMapper->writeCPU(0x03FD + x, 0xFF);
    opINC(0x04CF + x, 1);
    a = myMapper->readCPU(0x04CF + x);
    if (a == 0x40) {
        jump(0x8E71);
        return;
    }
    if (a == 0x80) {
        jump(0x8E71);
        return;
    }
    popAddress();
}

void game::SUB_008EC3() {
    myMapper->writeCPU(0x041B + x, 0x04);
    myMapper->writeCPU(0x050B + x, 0x0C);
    a = 0x0A;
    myMapper->writeCPU(0x04ED + x, a);
    opINC(0x0475 + x, 1);
    SUB_008ED5();
    return;
}

void game::SUB_008ED5() {
    y = 0x03;
    pushAddress(0x8ED9);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x8ED9)) return;
    if (!flgN) {
        pushAddress(0x8EDE);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x8EDE)) return;
        x = myMapper->readCPU(0x05AC);
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x06);
    opLSR_A(1);
    opADC(0x00);
    myMapper->writeCPU(0x03FD + x, a);
    pushAddress(0x8EEE);
    jump(0x90B3);
    if (handleReturnAddress(poppedEntry.value, 0x8EEE)) return;
    if (a == 0x00) {
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0xFF);
        myMapper->writeCPU(0x0493 + x, a);
    }
    if (myMapper->readCPU(0x0493 + x) == 0) {
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            goto L_008F1D;
        }
        opDEC(0x03A3 + x, 1);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0385 + x, a);
    if (!flgC) {
        goto L_008F1D;
    }
    opINC(0x03A3 + x, 1);
L_008F1D:
    popAddress();
}

void game::SUB_008F1E() {
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x03FD + x, 0x00);
    a = 0xFF;
    myMapper->writeCPU(0x04ED + x, a);
    pushAddress(0x8F2F);
    jump(0x8F5F);
    if (handleReturnAddress(poppedEntry.value, 0x8F2F)) return;
    if (!flgZ) {
        goto L_008F38;
    }
    myMapper->writeCPU(0x04B1 + x, 0x04);
    do {
        popAddress();
        return;
    L_008F38:
        pushAddress(0x8F3A);
        jump(0x926F);
        if (handleReturnAddress(poppedEntry.value, 0x8F3A)) return;
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x03C1, a);
    } while (myMapper->readCPU(0x0475 + x) != 0);
    a = myMapper->readCPU(0x04CF + x);
    setLoadFlag(a);
    if (flgZ) {
        goto L_008F5C;
    }
    a = myMapper->readCPU(0x058E);
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0059 + y, a);
    myMapper->writeCPU(0x05D1, 0xFE);
    popAddress();
    return;
L_008F5C:
    jump(0x8A8B);
    return;
}

void game::SUB_008F5F() {
    a = 0x00;
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0004, a);
    if (myMapper->readCPU(0x05D2) == 0) {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x059F));
            if (!flgN) {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x03DF));
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(0x30);
                if (flgC) {
                    opINC(0x0000, 1);
                }
                flgC = true;
                opSBC(myMapper->readCPU(0x03C1 + x));
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x0000);
                opSBC(0x00);
                if (flgZ) {
                    if (myMapper->readCPU(0x0001) >= 0x10) {
                        goto L_008FE3;
                    }
                    myMapper->writeCPU(0x0000, myMapper->readCPU(0x03A3));
                    a = myMapper->readCPU(0x0385);
                    flgC = false;
                    opADC(0x10);
                    if (flgC) {
                        opINC(0x0000, 1);
                    }
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0385 + x));
                    myMapper->writeCPU(0x0001, a);
                    a = myMapper->readCPU(0x0000);
                    opSBC(myMapper->readCPU(0x03A3 + x));
                    if (flgZ) {
                        if (myMapper->readCPU(0x0001) >= 0x28) {
                            goto L_008FE3;
                        }
                        a = 0x1A;
                        pushAddress(0x8FBB);
                        jump(0xEA16);
                        if (handleReturnAddress(poppedEntry.value, 0x8FBB)) return;
                        a = 0xFF;
                        myMapper->writeCPU(0x05A1, a);
                        myMapper->writeCPU(0x0004, a);
                        if (myMapper->readCPU(0x059D) == 0) {
                            goto L_008FD0;
                        }
                        a = 0x00;
                        myMapper->writeCPU(0x05A3, a);
                        myMapper->writeCPU(0x05A4, a);
                    L_008FD0:
                        a = 0x00;
                        myMapper->writeCPU(0x05A5, a);
                        myMapper->writeCPU(0x059D, a);
                        myMapper->writeCPU(0x059E, a);
                        myMapper->writeCPU(0x059F, a);
                        myMapper->writeCPU(0x05A6, 0x10);
                    }
                }
            }
        }
    }
L_008FE3:
    a = myMapper->readCPU(0x0004);
    setLoadFlag(a);
    popAddress();
}

void game::SUB_008FE6() {
    myMapper->writeCPU(0x04B1 + x, 0xFF);
    a = 0x01;
    myMapper->writeCPU(0x0493 + x, a);
    jump(0x9000);
    return;
}

void game::SUB_008FF3() {
    myMapper->writeCPU(0x04B1 + x, 0xFE);
    a = 0x02;
    myMapper->writeCPU(0x0493 + x, a);
    jump(0x9000);
    return;
}

void game::SUB_009000() {
    myMapper->writeCPU(0x03FD + x, 0x00);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    myMapper->writeCPU(0x0475 + x, 0x08);
    a = myMapper->readCPU(0x0385 + x);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0385 + x, a);
    if (flgC) {
        goto L_009028;
    }
    opDEC(0x03A3 + x, 1);
L_009028:
    popAddress();
}

void game::SUB_009029() {
    pushAddress(0x902B);
    jump(0x8F5F);
    if (handleReturnAddress(poppedEntry.value, 0x902B)) return;
    flgC = false;
    a = myMapper->readCPU(0x04B1 + x);
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    if (myMapper->readCPU(0x0004) != 0) {
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x03C1, a);
        a = 0x00;
        opSBC(0x00);
        myMapper->writeCPU(0x03DF, a);
        y = 0x00;
        a = myMapper->readCPU(0x0493 + x);
        setLoadFlag(a);
        if (flgN) {
            opDEY(1);
        }
        flgC = false;
        opADC(myMapper->readCPU(0x0385));
        myMapper->writeCPU(0x0385, a);
        a = y;
        opADC(myMapper->readCPU(0x03A3));
        myMapper->writeCPU(0x03A3, a);
    }
    opDEC(0x0565 + x, 1);
    if (!flgZ) {
        goto L_009093;
    }
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0493 + x));
    myMapper->writeCPU(0x0493 + x, a);
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x04B1 + x, a);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
L_009093:
    popAddress();
}

void game::SUB_009094() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x03A3 + x));
    y = myMapper->readCPU(0x03C1 + x);
    a = myMapper->readCPU(0x0385 + x);
    x = a;
    pushAddress(0x90A7);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x90A7)) return;
    x = 0x00;
    y = 0x06;
    pushAddress(0x90AE);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x90AE)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_0090B3() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x03A3 + x));
    y = myMapper->readCPU(0x03C1 + x);
    a = myMapper->readCPU(0x0385 + x);
    x = a;
    pushAddress(0x90C6);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x90C6)) return;
    x = 0x01;
    y = 0x03;
    pushAddress(0x90CD);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x90CD)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_009130() {
    a = myMapper->readCPU(0x03FD + x);
    opORA(0x01);
    myMapper->writeCPU(0x0565 + y, a);
    myMapper->writeCPU(0x04B1 + y, 0xFB);
    SUB_00913D();
    return;
}

void game::SUB_00913D() {
    myMapper->writeCPU(0x0475 + y, 0x05);
    a = myMapper->readCPU(0x03FD + y);
    opAND(0x80);
    flgC = false;
    x = myMapper->readCPU(0x04ED + y);
    if (x != 0x0A) {
        if (x == 0x00) {
            goto L_009176;
        }
        if (myMapper->readCPU(0x05BC) == 0) {
            goto L_009169;
        }
        a = 0x13;
        pushAddress(0x915C);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x915C)) return;
        a = myMapper->readCPU(0x0565 + y);
        opEOR(0x80);
        myMapper->writeCPU(0x0565 + y, a);
        opINC(0x0083, 1);
        opINC(0x008F, 1);
    L_009169:
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0082);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0082, a);
    a = 0x1F;
    jump(0xEA1B);
    return;
L_009176:
    a = myMapper->readCPU(0x0083);
    flgC = false;
    opADC(0x02);
    myMapper->writeCPU(0x0083, a);
    a = 0x1F;
    jump(0xEA1B);
    return;
}

void game::SUB_009182() {
    opCMP(myMapper->readCPU(0x03DF + x), 0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x04B1 + x);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                goto L_0091A7;
            }
            opINC(0x03DF + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                opDEC(0x03DF + x, 1);
            }
        }
    L_0091A7:
        a = myMapper->readCPU(0x003F);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x04B1 + x) == 0x08) {
                goto L_0091B7;
            }
            opINC(0x04B1 + x, 1);
        }
    L_0091B7:
        a = myMapper->readCPU(0x0565 + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (!flgN) {
                goto L_0091CD;
            }
            a = myMapper->readCPU(0x0385 + x);
            flgC = true;
            opSBC(0x03);
            myMapper->writeCPU(0x0385 + x, a);
            if (flgC) {
                goto L_0091CC;
            }
            opDEC(0x03A3 + x, 1);
        }
        do {
        L_0091CC:
            popAddress();
            return;
        L_0091CD:
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x03);
            myMapper->writeCPU(0x0385 + x, a);
        } while (!flgC);
        opINC(0x03A3 + x, 1);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_0091E2() {
    myMapper->writeCPU(0x0529 + x, y);
    myMapper->writeCPU(0x0547 + x, 0x06);
    a = myMapper->readCPU(0x03FD + x);
    opAND(0x80);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0547 + x, 0x00);
    a = myMapper->readCPU(0x0529 + x);
    SUB_0091FB();
    return;
}

void game::SUB_0091FB() {
    y = a;
    a = myMapper->readCPU(0x8B4C + y);
    setLoadFlag(a);
    if (!flgN) {
        y = a;
        opAND(0x3F);
        myMapper->writeCPU(0x03FD + x, a);
        if (y == 0x40) {
            goto L_009211;
        }
        while (true) {
            opDEC(0x0547 + x, 1);
            if (flgN) {
                goto L_00922E;
            }
            popAddress();
            return;
        L_009211:
            myMapper->writeCPU(0x03FD + x, a);
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x04);
            myMapper->writeCPU(0x0385 + x, a);
            a = myMapper->readCPU(0x03A3 + x);
            opADC(0x00);
            myMapper->writeCPU(0x03A3 + x, a);
        }
    }
    myMapper->writeCPU(0x0529 + x, 0x00);
    popAddress();
    return;
L_00922E:
    myMapper->writeCPU(0x0547 + x, 0x06);
    opINC(0x0529 + x, 1);
    if (y == 0x62) {
        goto L_00923B;
    }
    do {
        popAddress();
        return;
    L_00923B:
        a = 0x22;
        pushAddress(0x923F);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x923F)) return;
        y = 0x04;
        pushAddress(0x9244);
        jump(0x995E);
        if (handleReturnAddress(poppedEntry.value, 0x9244)) return;
    } while (flgN);
    a = myMapper->readCPU(0x059D);
    setLoadFlag(a);
    if (flgZ) {
        goto L_00924F;
    }
    jump(0x8A8B);
    return;
L_00924F:
    myMapper->writeCPU(0x05D1, 0x01);
    popAddress();
}

void game::SUB_00926F() {
    myMapper->writeCPU(0x0529 + x, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    if (!flgC) {
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            if (myMapper->readCPU(0x04B1 + x) == 0x08) {
                goto L_009290;
            }
            opINC(0x04B1 + x, 1);
        }
    L_009290:
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_009297() {
    myMapper->writeCPU(0x041B + x, 0x06);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    a = myMapper->readCPU(0x0529 + x);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x91FB);
        return;
    }
    myMapper->writeCPU(0x03FD + x, 0xFF);
    opINC(0x0565 + x, 1);
    a = myMapper->readCPU(0x0565 + x);
    opAND(0xD7);
    if (!flgZ) {
        goto L_0092BD;
    }
    y = 0x01;
    jump(0x91E2);
    return;
L_0092BD:
    popAddress();
}

void game::SUB_0092BE() {
    a = 0x13;
    pushAddress(0x92C2);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x92C2)) return;
    a = 0x09;
    y = 0x00;
    myMapper->writeCPU(0x04ED + x, a);
    myMapper->writeCPU(0x0565 + x, myMapper->readCPU(0x04CF + x));
    a = y;
    myMapper->writeCPU(0x03FD + x, a);
    opAND(0x7F);
    myMapper->writeCPU(0x04CF + x, a);
    myMapper->writeCPU(0x041B + x, 0x07);
    myMapper->writeCPU(0x0547 + x, 0x03);
    myMapper->writeCPU(0x0475 + x, 0x0A);
    myMapper->writeCPU(0x050B + x, 0x00);
    popAddress();
}

void game::SUB_0092EE() {
    y = 0x05;
    myMapper->writeCPU(0x0659, y);
    pushAddress(0x92F5);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x92F5)) return;
    if (!flgN) {
        y = x;
        x = 0x00;
        a = 0x01;
        myMapper->writeCPU(0x05BC, a);
        jump(0x9130);
        return;
    }
    opDEC(0x04B1 + x, 1);
    if (flgV) {
        myMapper->writeCPU(0x0493 + x, 0x00);
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x0493 + x) != 0) {
        goto L_00931E;
    }
    opDEC(0x0547 + x, 1);
    if (flgZ) {
        goto L_00932B;
    }
    myMapper->writeCPU(0x0493 + x, 0xFF);
L_00931E:
    a = myMapper->readCPU(0x003F);
    opLSR_A(2);
    opAND(0x01);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_00932B:
    myMapper->writeCPU(0x04B1 + x, 0xFE);
    a = x;
    y = a;
    x = 0x00;
    jump(0x913D);
    return;
}

void game::SUB_009337() {
    a = myMapper->readCPU(0x003F);
    opAND(0x02);
    opLSR_A(1);
    opADC(0x02);
    myMapper->writeCPU(0x03FD + x, a);
    SUB_009341();
    return;
}

void game::SUB_009341() {
    a = myMapper->readCPU(0x04B1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    if (a < 0xF4) {
        myMapper->writeCPU(0x03C1 + x, a);
        if (myMapper->readCPU(0x0457 + x) == 0) {
            goto L_00935A;
        }
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
    return;
L_00935A:
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    myMapper->writeCPU(0x0024, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    myMapper->writeCPU(0x0025, a);
    if (myMapper->readCPU(0x05BD) == 0) {
        myMapper->writeCPU(0x0001, 0x38);
        a = 0x20;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x9385);
        jump(0x995E);
        if (handleReturnAddress(poppedEntry.value, 0x9385)) return;
        if (!flgN) {
            goto L_009389;
        }
    }
    popAddress();
    return;
L_009389:
    a = myMapper->readCPU(0x0475 + x);
    a = myMapper->readCPU(0x041B + x);
    if (a == 0x01) {
        pushAddress(0x9395);
        jump(0x9513);
        if (handleReturnAddress(poppedEntry.value, 0x9395)) return;
        a = 0xFE;
    }
    else {
        myMapper->writeCPU(0x0475 + x, 0x00);
        a = 0xFF;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x008E, a);
    if (myMapper->readCPU(0x04B1 + x) != 0) {
        a = 0x00;
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
    }
    x = 0x1C;
    if (myMapper->readCPU(0x05C9) == 0) {
        goto L_0093BD;
    }
    x = 0x20;
L_0093BD:
    a = myMapper->readCPU(0x04ED + x);
    jump(0x8A55);
    return;
}

void game::SUB_0093C3() {
    if (myMapper->readCPU(0x0457 + x) == 0) {
        goto L_0093CE;
    }
    while (true) {
        do {
            myMapper->writeCPU(0x0475 + x, 0x00);
            popAddress();
            return;
        L_0093CE:
            y = 0x00;
            a = myMapper->readCPU(0x0493 + x);
            setLoadFlag(a);
            if (!flgN) {
                goto L_0093D6;
            }
            opDEY(1);
        L_0093D6:
            flgC = false;
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            myMapper->writeCPU(0x0024, a);
            a = y;
            opADC(myMapper->readCPU(0x03A3 + x));
            myMapper->writeCPU(0x03A3 + x, a);
            myMapper->writeCPU(0x0025, a);
            a = myMapper->readCPU(0x04B1 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x03C1 + x));
        } while (a >= 0xF4);
        myMapper->writeCPU(0x03C1 + x, a);
        myMapper->writeCPU(0x0001, 0x32);
        a = 0x18;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x9402);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9402)) return;
        if (!flgN) {
            goto L_00943D;
        }
        y = 0x02;
        pushAddress(0x9409);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9409)) return;
        if (!flgN) {
            goto L_00943D;
        }
        y = 0x06;
        pushAddress(0x9410);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9410)) return;
        if (!flgN) {
            goto L_00943D;
        }
        y = 0x07;
        pushAddress(0x9417);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9417)) return;
        if (!flgN) {
            goto L_00943D;
        }
        a = 0x20;
        myMapper->writeCPU(0x0001, a);
        myMapper->writeCPU(0x0002, a);
        y = 0x0E;
        pushAddress(0x9424);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9424)) return;
        if (!flgN) {
            goto L_00943D;
        }
        y = 0x0F;
        pushAddress(0x942B);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x942B)) return;
        if (!flgN) {
            goto L_00943D;
        }
        y = 0x10;
        pushAddress(0x9432);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9432)) return;
        if (!flgN) {
            goto L_00943D;
        }
        y = 0x11;
        pushAddress(0x9439);
        jump(0x9465);
        if (handleReturnAddress(poppedEntry.value, 0x9439)) return;
        if (!flgN) {
            goto L_00943D;
        }
        do {
            popAddress();
            return;
        L_00943D:
            a = 0x0D;
            pushAddress(0x9441);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x9441)) return;
            a = myMapper->readCPU(0x050B + y);
            flgC = true;
            opSBC(myMapper->readCPU(0x0594));
            myMapper->writeCPU(0x050B + y, a);
            if (!flgN) {
                goto L_009454;
            }
            pushAddress(0x9450);
            jump(0x9130);
            if (handleReturnAddress(poppedEntry.value, 0x9450)) return;
            x = myMapper->readCPU(0x05AC);
        L_009454:
            a = myMapper->readCPU(0x0595);
        } while (a == 0x05);
        if (a == 0x04) {
            goto L_009462;
        }
    }
L_009462:
    jump(0x951D);
    return;
}

void game::SUB_009465() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x05) {
            goto L_0094A5;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_0094A5;
            }
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(0x08);
            flgC = true;
            opSBC(myMapper->readCPU(0x03C1 + y));
            if (flgC) {
                if (a >= myMapper->readCPU(0x0001)) {
                    goto L_0094A5;
                }
                a = myMapper->readCPU(0x0024);
                flgC = false;
                opADC(0x08);
                flgC = true;
                opSBC(myMapper->readCPU(0x0385 + y));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x0025);
                opSBC(myMapper->readCPU(0x03A3 + y));
                if (flgZ) {
                    if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x0002)) {
                        goto L_0094A5;
                    }
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                }
            }
        }
    }
L_0094A5:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0094A8() {
    myMapper->writeCPU(0x03FD + x, myMapper->readCPU(0x04CF + x));
    a = 0x02;
    myMapper->writeCPU(0x041B + x, a);
    y = 0x02;
    pushAddress(0x94B7);
    jump(0x9968);
    if (handleReturnAddress(poppedEntry.value, 0x94B7)) return;
    if (flgN) {
        goto L_0094D6;
    }
    y = myMapper->readCPU(0x03FD + x);
    if (y == 0x00) {
        goto L_009507;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    if (y == 0x08) {
        goto L_0094E9;
    }
    if (y == 0x01) {
        goto L_0094F0;
    }
    if (y == 0x06) {
        goto L_0094DD;
    }
    if (y == 0x07) {
        goto L_0094D7;
    }
L_0094D6:
    popAddress();
    return;
L_0094D7:
    myMapper->writeCPU(0x05BD, 0x06);
    popAddress();
    return;
L_0094DD:
    a = myMapper->readCPU(0x008E);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x008E, a);
    a = 0x11;
    jump(0xEA1B);
    return;
L_0094E9:
    a = 0x05;
    a = 0x0E;
    jump(0xEA1B);
    return;
L_0094F0:
    y = myMapper->readCPU(0x05BE);
    myMapper->writeCPU(0x0595, y);
    myMapper->writeCPU(0x0594, myMapper->readCPU(0xEA43 + y));
    myMapper->writeCPU(0x0596, myMapper->readCPU(0xEA49 + y));
    a = 0x12;
    jump(0xEA1B);
    return;
L_009507:
    a = myMapper->readCPU(0x0081);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x0081, a);
    opINC(0x0090, 1);
    jump(0x9513);
    return;
}

void game::SUB_009513() {
    myMapper->writeCPU(0x041B + x, 0x02);
    a = 0x02;
    jump(0x9524);
    return;
}

void game::SUB_00951D() {
    myMapper->writeCPU(0x041B + x, 0x00);
    a = 0x02;
    SUB_009524();
    return;
}

void game::SUB_009524() {
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x04CF + x, 0x00);
    myMapper->writeCPU(0x0475 + x, 0x03);
    a = 0x0B;
    pushAddress(0x9535);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x9535)) return;
    SUB_009536();
    return;
}

void game::SUB_009536() {
    a = myMapper->readCPU(0x04CF + x);
    opLSR_A(2);
    opINC(0x04CF + x, 1);
    if (a == 0x04) {
        goto L_00954A;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0565 + x));
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_00954A:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_009550() {
    pushAddress(0x9552);
    jump(0x9601);
    if (handleReturnAddress(poppedEntry.value, 0x9552)) return;
    if (!flgN) {
        a = 0x09;
        pushAddress(0x9559);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x9559)) return;
        opINC(0x03FD + x, 1);
        myMapper->writeCPU(0x0475 + y, 0x16);
        myMapper->writeCPU(0x03FD + y, 0x02);
        a = myMapper->readCPU(0x04CF + x);
        if (a != 0xA0) {
            if (a == 0xA2) {
                goto L_009580;
            }
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(0x20);
            myMapper->writeCPU(0x03C1 + y, a);
            a = 0x00;
            jump(0x95BA);
            return;
        L_009580:
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(0x18);
            myMapper->writeCPU(0x03C1 + y, a);
            a = 0x00;
            jump(0x95BA);
            return;
        }
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU(0x03C1 + y, a);
        a = 0x00;
        jump(0x95BA);
        return;
    }
    popAddress();
}

void game::SUB_00959D() {
    pushAddress(0x959F);
    jump(0x9601);
    if (handleReturnAddress(poppedEntry.value, 0x959F)) return;
    if (flgN) {
        jump(0x9600);
        return;
    }
    a = 0x06;
    pushAddress(0x95A6);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x95A6)) return;
    myMapper->writeCPU(0x0475 + y, 0x04);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x03C1 + y, a);
    a = 0x00;
    myMapper->writeCPU(0x03FD + y, a);
    SUB_0095BA();
    return;
}

void game::SUB_0095BA() {
    myMapper->writeCPU(0x04B1 + y, a);
    myMapper->writeCPU(0x041B + y, a);
    myMapper->writeCPU(0x0457 + y, a);
    myMapper->writeCPU(0x03DF + y, a);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x0493 + y, 0x03);
    if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
        goto L_0095F1;
    }
    myMapper->writeCPU(0x0493 + y, 0xFD);
    a = myMapper->readCPU(0x0000);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x0001);
    opSBC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    jump(0x9600);
    return;
L_0095F1:
    a = myMapper->readCPU(0x0000);
    flgC = false;
    opADC(0x18);
    myMapper->writeCPU(0x0385 + y, a);
    a = myMapper->readCPU(0x0001);
    opADC(0x00);
    myMapper->writeCPU(0x03A3 + y, a);
    SUB_009600();
    return;
}

void game::SUB_009600() {
    popAddress();
}

void game::SUB_009601() {
    y = 0x08;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x09;
        if (myMapper->readCPU(0x0475 + y) == 0) {
            goto L_009612;
        }
        a = 0xFF;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_009612:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_009615() {
    myMapper->writeCPU(0x050B + x, 0x10);
    myMapper->writeCPU(0x04ED + x, 0x00);
    a = 0x06;
    myMapper->writeCPU(0x041B + x, a);
    opINC(0x0475 + x, 1);
    SUB_009627();
    return;
}

void game::SUB_009627() {
    y = 0x07;
    pushAddress(0x962B);
    jump(0x995E);
    if (handleReturnAddress(poppedEntry.value, 0x962B)) return;
    if (!flgN) {
        pushAddress(0x9630);
        jump(0x8A8B);
        if (handleReturnAddress(poppedEntry.value, 0x9630)) return;
        x = myMapper->readCPU(0x05AC);
    }
    myMapper->writeCPU(0x03FD + x, myMapper->readCPU(0x04CF + x));
    a = myMapper->readCPU(0x05AF);
    opAND(0xD7);
    if (!flgZ) {
        a = myMapper->readCPU(0x05AF);
        opAND(0x6E);
        if (flgZ) {
            jump(0x9550);
            return;
        }
        popAddress();
        return;
    }
    pushAddress(0x9603);
    jump(0x9094);
    if (handleReturnAddress(poppedEntry.value, 0x9603)) return;
    if (a != 0x00) {
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(0x0385 + x, a);
        if (!flgC) {
            opDEC(0x03A3 + x, 1);
        }
    }
    a = myMapper->readCPU(0x04CF + x);
    if (a != 0xA0) {
        if (a == 0xA4) {
            goto L_009683;
        }
        a = myMapper->readCPU(0x003F);
        opLSR_A(1);
        if (!flgC) {
            goto L_00967A;
        }
        a = 0xA4;
        myMapper->writeCPU(0x04CF + x, a);
        myMapper->writeCPU(0x03FD + x, a);
        popAddress();
        return;
    L_00967A:
        a = 0xA0;
        myMapper->writeCPU(0x04CF + x, a);
        myMapper->writeCPU(0x03FD + x, a);
        popAddress();
        return;
    }
L_009683:
    a = 0xA2;
    myMapper->writeCPU(0x04CF + x, a);
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
}

void game::SUB_00968C() {
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        if (a != myMapper->readCPU(0x00A0)) {
            goto L_00969A;
        }
        pushAddress(0x9696);
        jump(0x96A5);
        if (handleReturnAddress(poppedEntry.value, 0x9696)) return;
    }
L_00969A:
    flgC = false;
    a = y;
    opADC(myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x000E, a);
    if (!flgC) {
        goto L_0096A4;
    }
    opINC(0x000F, 1);
L_0096A4:
    popAddress();
}

void game::SUB_0096A5() {
    opINY(1);
    x = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    a = myMapper->readCPU(0x0475 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0096E9;
    }
    a = myMapper->readCPU(SCROLL_FINE);
    opAND(0xF8);
    myMapper->writeCPU(0x0385 + x, a);
    a = myMapper->readCPU(SCROLL_LARGE);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x03A3 + x, a);
    opINY(1);
    myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    a = 0x00;
    myMapper->writeCPU(0x03DF + x, a);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0529 + x, a);
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x0547 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0475 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x04CF + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = 0xFF;
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_0096E9:
    opINY(4);
    popAddress();
}

void game::SUB_00995E() {
    if (myMapper->readCPU(0x05D2) != 0) {
        jump(0x99D1);
        return;
    }
    if (myMapper->readCPU(0x05BD) != 0) {
        jump(0x99D1);
        return;
    }
    SUB_009968();
    return;
}

void game::SUB_009968() {
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03DF));
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(myMapper->readCPU(0x05C9));
    myMapper->writeCPU(0x0000, a);
    if (flgC) {
        opINC(0x0001, 1);
    }
    myMapper->writeCPU(0x0002, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x99E0 + y));
    if (flgC) {
        opINC(0x0002, 1);
    }
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0002);
    opSBC(myMapper->readCPU(0x0001));
    if (!flgZ) {
        jump(0x99D1);
        return;
    }
    if (myMapper->readCPU(0x05C9) != 0) {
        a = myMapper->readCPU(0x0000);
        if (a >= myMapper->readCPU(0x9A04 + y)) {
            jump(0x99D1);
            return;
        }
    }
    else {
        if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x99F8 + y)) {
            jump(0x99D1);
            return;
        }
    }
    myMapper->writeCPU(0x0025, myMapper->readCPU(0x03A3 + x));
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x99D4 + y));
    if (!flgC) {
        goto L_0099BA;
    }
    opINC(0x0025, 1);
L_0099BA:
    flgC = true;
    opSBC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opSBC(myMapper->readCPU(0x03A3));
    if (!flgZ) {
        jump(0x99D1);
        return;
    }
    if (myMapper->readCPU(0x0024) >= myMapper->readCPU(0x99EC + y)) {
        jump(0x99D1);
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_0099D1() {
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_009A10() {
    a = myMapper->readCPU(0x00A0);
    if (a == myMapper->readCPU(0x05BA)) {
        a = 0x00;
        myMapper->writeCPU(0x05B5, a);
    }
    opBIT(myMapper->readCPU(0x05B5));
    if (flgV) {
    }
    else {
        y = 0x03;
        x = myMapper->readCPU(0x0051);
        a = myMapper->readCPU((0x0059 + x) & 0x00ff);
        if (a != 0x08) {
            y = 0x0B;
            if (a != 0x09) {
                goto L_009A41;
            }
        }
        a = myMapper->readCPU(0x00A0);
        x = 0x03;
        do {
            if (a == myMapper->readCPU(0x9B3B + y)) {
                goto L_009A42;
            }
            opDEY(1);
            opDEX(1);
        } while (!flgN);
    L_009A41:
        popAddress();
        return;
    L_009A42:
        myMapper->writeCPU(0x05B0, a);
        flgC = false;
        opADC(0x09);
        myMapper->writeCPU(0x05BA, a);
        myMapper->writeCPU(0x05B9, myMapper->readCPU(0x9B3F + y));
        a = myMapper->readCPU(0x0371);
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x05B3, a);
        a = myMapper->readCPU(0x0370);
        opADC(0x00);
        myMapper->writeCPU(0x05B4, a);
        myMapper->writeCPU(0x05B1, myMapper->readCPU(0x0301));
        a = myMapper->readCPU(0x0300);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x05B2, a);
        myMapper->writeCPU(0x05B5, 0x40);
        myMapper->writeCPU(0x05B6, 0x02);
        myMapper->writeCPU(0x05B7, myMapper->readCPU(0x05B9));
        a = 0x20;
        myMapper->writeCPU(0x05B8, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x05B8);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x05B1));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x05B3));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x05B4));
    a = myMapper->readCPU(0x05B6);
    flgC = false;
    opADC(0x27);
    x = 0x31;
    pushAddress(0x9AAB);
    jump(0xE3C9);
    if (handleReturnAddress(poppedEntry.value, 0x9AAB)) return;
    if (myMapper->readCPU(0x05B6) == 0x02) {
        myMapper->writeCPU(0x05B6, 0x00);
        flgC = true;
        a = myMapper->readCPU(0x05B3);
        opSBC(0x08);
        myMapper->writeCPU(0x05B3, a);
        myMapper->writeCPU(0x0009, a);
        flgC = true;
        a = myMapper->readCPU(0x05B1);
        opSBC(0x80);
        myMapper->writeCPU(0x05B1, a);
        myMapper->writeCPU(0x0005, a);
        if (!flgC) {
            opDEC(0x05B2, 1);
        }
        myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
        a = 0x27;
        x = 0x4C;
        pushAddress(0x9ADE);
        jump(0xE3C9);
        if (handleReturnAddress(poppedEntry.value, 0x9ADE)) return;
    }
    opINC(0x05B6, 1);
    a = myMapper->readCPU(0x03C1);
    flgC = true;
    opSBC(0x10);
    myMapper->writeCPU(0x03C1, a);
    a = 0x00;
    opSBC(0x00);
    myMapper->writeCPU(0x03DF, a);
    a = 0xFF;
    myMapper->writeCPU(0x0655, a);
    myMapper->writeCPU(0x05A1, a);
    myMapper->writeCPU(0x059D, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x05A6, a);
    opDEC(0x05B7, 1);
    if (flgZ) {
        goto L_009B0A;
    }
    popAddress();
    return;
L_009B0A:
    x = myMapper->readCPU(0x05B0);
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    if (a == 0x08) {
        goto L_009B24;
    }
    if (a == 0x09) {
        goto L_009B34;
    }
    while (true) {
    L_009B1A:
        myMapper->writeCPU(0x05D1, 0x03);
        a = 0x22;
        jump(0xEA1B);
        return;
    L_009B24:
        if (x != 0x38) {
            goto L_009B1A;
        }
    L_009B28:
        myMapper->writeCPU(0x0059 + y, myMapper->readCPU(0x058E));
        a = 0xFE;
        myMapper->writeCPU(0x05D1, a);
        popAddress();
        return;
    L_009B34:
        if (x == 0x3E) {
            goto L_009B28;
        }
    }
    SUB_00C000();
    return;
}

void game::SUB_00C000() {
    pushAddress(0x8002);
    jump(0x81B0);
    if (handleReturnAddress(poppedEntry.value, 0x8002)) return;
    myMapper->writeCPU(0x05AC, a);
    if (a != 0xFF) {
        if (a == 0x01) {
            goto L_00C013;
        }
        if (a == 0x03) {
            goto L_00C026;
        }
        popAddress();
        return;
    L_00C013:
        x = 0x07;
        a = 0x00;
        jump(0x8036);
        return;
    }
    myMapper->writeCPU(0x0547, 0x80);
    x = 0x03;
    a = 0x0C;
    jump(0x8036);
    return;
L_00C026:
    x = 0x0F;
    a = 0x2E;
    jump(0x8036);
    return;
}

void game::SUB_00C02D() {
    a = 0x06;
    pushAddress(0x8031);
    SUB_01FFAA_SwitchCHRBank1();
    x = 0x0F;
    a = 0x27;
    SUB_00C036();
    return;
}

void game::SUB_00C036() {
    myMapper->writeCPU(0x05A2, x);
    myMapper->writeCPU(0x05CA, a);
    a = 0x02;
    pushAddress(0x8040);
    SUB_01FFD2_SwitchCHRBank0();
    pushAddress(0x8043);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0x8043)) return;
    pushAddress(0x8046);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x8046)) return;
    a = myMapper->readCPU(0x03C1);
    opAND(0xF8);
    myMapper->writeCPU(0x03C1, a);
    myMapper->writeCPU(0x058A, myMapper->readCPU(0x001E));
    myMapper->writeCPU(0x058B, myMapper->readCPU(0x001F));
    myMapper->writeCPU(0x001E, 0x32);
    a = 0xC9;
    myMapper->writeCPU(0x001F, a);
    x = myMapper->readCPU(0x0589);
    setLoadFlag(x);
    if (!flgN) {
        myMapper->writeCPU(0x040F, x);
        opINX(1);
        myMapper->writeCPU(0x0410, x);
        a = 0x05;
        myMapper->writeCPU(0x042D, a);
        myMapper->writeCPU(0x042E, a);
        a = 0x00;
        myMapper->writeCPU(0x03B5, a);
        myMapper->writeCPU(0x03B6, a);
        myMapper->writeCPU(0x03F1, a);
        myMapper->writeCPU(0x03F2, a);
        a = 0x20;
        myMapper->writeCPU(0x03D3, a);
        myMapper->writeCPU(0x03D4, a);
        myMapper->writeCPU(0x0397, 0x08);
        a = 0x28;
        myMapper->writeCPU(0x0398, a);
    }
    goto L_00C09D;
    while (true) {
        a = 0x02;
        pushAddress(0x809C);
        SUB_01FFD2_SwitchCHRBank0();
    L_00C09D:
        a = myMapper->readCPU(0x0040);
        opAND(0xFE);
        myMapper->writeCPU(PPU_CTRL, a);
        x = myMapper->readCPU(0x05CA);
        a = myMapper->readCPU(0x817E + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_00C140;
        }
        myMapper->writeCPU(0x03FD, a);
        a = myMapper->readCPU(0x003F);
        opAND(myMapper->readCPU(0x05A2));
        if (flgZ) {
            opINC(0x05CA, 1);
        }
        //do {
        //L_00C0BC:
        //    opBIT(myMapper->readCPU(PPU_STATUS));
        //} while (!flgV);
    L_00C0BC:
        wait(2);
        needWaitScanline = true;
        waitScanline = 32;
        wait(3);
        if (myMapper->readCPU(0x03FD) == 0x18) {
            a = 0x16;
            pushAddress(0x80E9);
            jump(0xEA16);
            if (handleReturnAddress(poppedEntry.value, 0x80E9)) return;
        }
        a = myMapper->readCPU(0x05AC);
        if (a == 0xFF) {
            pushAddress(0x80F3);
            jump(0xF822);
            if (handleReturnAddress(poppedEntry.value, 0x80F3)) return;
        }
        a = 0x04;
        myMapper->writeCPU(0x0028, a);
        y = 0x00;
        pushAddress(0x80FC);
        jump(0xCA70);
        if (handleReturnAddress(poppedEntry.value, 0x80FC)) return;
        x = myMapper->readCPU(0x0589);
        setLoadFlag(x);
        if (!flgN) {
            y = 0x12;
            pushAddress(0x8106);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x8106)) return;
            y = 0x13;
            pushAddress(0x810B);
            jump(0xCA70);
            if (handleReturnAddress(poppedEntry.value, 0x810B)) return;
            pushAddress(0x810E);
            jump(0xCA60);
            if (handleReturnAddress(poppedEntry.value, 0x810E)) return;
        }
        pushAddress(0x8111);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x8111)) return;
        pushAddress(0x8114);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x8114)) return;
        a = myMapper->readCPU(0x003F);
        opLSR_A(1);
        if (flgC) {
            a = myMapper->readCPU(0x05D1);
            if (a == 0xFE) {
                opINC(0x03C1, 1);
                if (flgZ) {
                    opINC(0x03DF, 1);
                }
            }
        }
        pushAddress(0x812B);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x812B)) return;
        pushAddress(0x812E);
        jump(0xEA36);
        if (handleReturnAddress(poppedEntry.value, 0x812E)) return;
        a = myMapper->readCPU(0x000D);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00C135;
        }
        myMapper->writeCPU(0x000B, a);
    L_00C135:
        pushAddress(0x8137);
        jump(0xDBB3);
        if (handleReturnAddress(poppedEntry.value, 0x8137)) return;
        a = 0x06;
        pushAddress(0x813C);
        SUB_01FFAA_SwitchCHRBank1();
    }
L_00C140:
    if (myMapper->readCPU(0x05AC) == 0xFF) {
        a = myMapper->readCPU(0x0091);
        if (a == 0xFF) {
            a = myMapper->readCPU(0x0547);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00C161;
            }
            opDEC(0x0547, 1);
            if (a != 0x32) {
                goto L_00C15E;
            }
            a = 0x0F;
            pushAddress(0x815D);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x815D)) return;
        }
    L_00C15E:
        goto L_00C0BC;
    }
L_00C161:
    a = 0x00;
    myMapper->writeCPU(0x00B9, a);
    myMapper->writeCPU(0x004C, a);
    myMapper->writeCPU(0x05CA, a);
    myMapper->writeCPU(0x0487, a);
    myMapper->writeCPU(0x0488, a);
    myMapper->writeCPU(0x001E, myMapper->readCPU(0x058A));
    myMapper->writeCPU(0x001F, myMapper->readCPU(0x058B));
    a = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_00C1B0() {
    pushAddress(0x81B2);
    jump(0xDE68);
    if (handleReturnAddress(poppedEntry.value, 0x81B2)) return;
    pushAddress(0x81B5);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0x81B5)) return;
    pushAddress(0x81B8);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0x81B8)) return;
    pushAddress(0x81BB);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0x81BB)) return;
    pushAddress(0x81BE);
    jump(0xFE80);
    if (handleReturnAddress(poppedEntry.value, 0x81BE)) return;
    a = 0x07;
    pushAddress(0x81C3);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0x81C3)) return;
    myMapper->writeCPU(0x05D3, 0x07);
    x = 0x00;
    myMapper->writeCPU(0x0589, 0x08);
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    if (a == 0x0C) {
        goto L_00C1DA;
    }
    popAddress();
    return;
L_00C1DA:
    myMapper->writeCPU(0x05BF, 0x12);
    a = 0x16;
    myMapper->writeCPU(0x05C0, a);
    myMapper->writeCPU(0x05C1, a);
    myMapper->writeCPU(0x05C2, a);
    pushAddress(0x81EC);
    jump(0x81F0);
    if (handleReturnAddress(poppedEntry.value, 0x81EC)) return;
    jump(0x828B);
    return;
}

void game::SUB_00C1F0() {
    myMapper->writeCPU(0x041B, 0x06);
    a = 0x00;
    myMapper->writeCPU(0x05B5, a);
    myMapper->writeCPU(0x05CD, a);
    myMapper->writeCPU(0x03FD, a);
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
    myMapper->writeCPU(0x05D2, a);
    myMapper->writeCPU(0x05D1, a);
    myMapper->writeCPU(0x05D0, a);
    myMapper->writeCPU(0x059D, a);
    myMapper->writeCPU(0x0091, 0x64);
    myMapper->writeCPU(0x0011, myMapper->readCPU(0x8415 + x));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x8416 + x));
    myMapper->writeCPU(0x0587, myMapper->readCPU(0x8417 + x));
    myMapper->writeCPU(0x0588, myMapper->readCPU(0x8418 + x));
    myMapper->writeCPU(0x05BE, myMapper->readCPU(0x8419 + x));
    myMapper->writeCPU(0x0092, myMapper->readCPU(0x841A + x));
    myMapper->writeCPU(0x0093, myMapper->readCPU(0x841B + x));
    myMapper->writeCPU(0x000C, myMapper->readCPU(0x841C + x));
    myMapper->writeCPU(0x000D, myMapper->readCPU(0x841D + x));
    myMapper->writeCPU(0x009A, myMapper->readCPU(0x841E + x));
    myMapper->writeCPU(0x009B, myMapper->readCPU(0x841F + x));
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x8420 + x));
    myMapper->writeCPU(0x009D, myMapper->readCPU(0x8421 + x));
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x8422 + x));
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x8423 + x));
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x8424 + x));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x8425 + x));
    myMapper->writeCPU(0x000E, myMapper->readCPU(0x8426 + x));
    a = myMapper->readCPU(0x8427 + x);
    myMapper->writeCPU(0x000F, a);
    y = myMapper->readCPU(0x8428 + x);
    pushAddress(0x827D);
    jump(0x8376);
    if (handleReturnAddress(poppedEntry.value, 0x827D)) return;
    a = myMapper->readCPU(0x8429 + x);
    y = myMapper->readCPU(0x842A + x);
    x = a;
    pushAddress(0x8287);
    jump(0xDC63);
    if (handleReturnAddress(poppedEntry.value, 0x8287)) return;
    jump(0xDEF4);
    return;
}

void game::SUB_00C28B() {
    myMapper->writeCPU(0x0005, 0x9E);
    myMapper->writeCPU(0x0006, 0xE9);
    myMapper->writeCPU(0x0007, 0xDE);
    a = 0xE9;
    myMapper->writeCPU(0x0008, a);
    pushAddress(0x829D);
    jump(0xDD83);
    if (handleReturnAddress(poppedEntry.value, 0x829D)) return;
    pushAddress(0x82A0);
    jump(0x839A);
    if (handleReturnAddress(poppedEntry.value, 0x82A0)) return;
    a = myMapper->readCPU(0x0042);
    opORA(0x80);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    a = 0x00;
    myMapper->writeCPU(0x05AF, a);
    myMapper->writeCPU(0x003F, a);
    pushAddress(0x82B4);
    jump(0xDCFD);
    if (handleReturnAddress(poppedEntry.value, 0x82B4)) return;
    pushAddress(0x82B7);
    jump(0x802D);
    if (handleReturnAddress(poppedEntry.value, 0x82B7)) return;
    a = 0x00;
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x05AF, a);
    goto L_00C2DF;
L_00C2C2:
    pushAddress(0x82C4);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0x82C4)) return;
    a = myMapper->readCPU(0x05D1);
    setLoadFlag(a);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0011);
    pushAddress(0x82CF);
    SUB_01FFAA_SwitchCHRBank1();
    a = 0x02;
    pushAddress(0x82D4);
    SUB_01FFD2_SwitchCHRBank0();
    a = myMapper->readCPU(0x0040);
    opAND(0xFE);
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0x82DE);
    jump(0xDBDF);
    if (handleReturnAddress(poppedEntry.value, 0x82DE)) return;
L_00C2DF:
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x82E6);
        jump(0xE6E4);
        if (handleReturnAddress(poppedEntry.value, 0x82E6)) return;
        pushAddress(0x82E9);
        jump(0xE7DF);
        if (handleReturnAddress(poppedEntry.value, 0x82E9)) return;
        pushAddress(0x82EC);
        jump(0xE84A);
        if (handleReturnAddress(poppedEntry.value, 0x82EC)) return;
        pushAddress(0x82EF);
        jump(0xE770);
        if (handleReturnAddress(poppedEntry.value, 0x82EF)) return;
        pushAddress(0x82F2);
        jump(0xE685);
        if (handleReturnAddress(poppedEntry.value, 0x82F2)) return;
        pushAddress(0x82F5);
        jump(0xE88C);
        if (handleReturnAddress(poppedEntry.value, 0x82F5)) return;
        pushAddress(0x82F8);
        jump(0xE50E);
        if (handleReturnAddress(poppedEntry.value, 0x82F8)) return;
        pushAddress(0x82FB);
        jump(0xDCD8);
        if (handleReturnAddress(poppedEntry.value, 0x82FB)) return;
    }
    //do {
    //    opBIT(myMapper->readCPU(PPU_STATUS));
    //} while (!flgV);
	wait(2);
    needWaitScanline = true;
    waitScanline = 32;
    wait(3);
    a = myMapper->readCPU(0x00B9);
    if (a == 0x10) {
        a = myMapper->readCPU(0x058C);
        setLoadFlag(a);
        if (!flgZ) {
            opDEC(0x058C, 1);
            a = myMapper->readCPU(0x058D);
            pushAddress(0x8331);
            jump(0xE9E6);
            if (handleReturnAddress(poppedEntry.value, 0x8331)) return;
            a = 0x0F;
            pushAddress(0x8336);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x8336)) return;
            goto L_00C373;
        }
        opINC(0x058C, 1);
        pushAddress(0x833F);
        jump(0xEA06);
        if (handleReturnAddress(poppedEntry.value, 0x833F)) return;
        a = 0x0E;
        pushAddress(0x8344);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x8344)) return;
    }
    pushAddress(0x82CD);
    jump(0xEA36);
    if (handleReturnAddress(poppedEntry.value, 0x82CD)) return;
    a = myMapper->readCPU(0x058C);
    setLoadFlag(a);
    if (flgZ) {
        pushAddress(0x834F);
        jump(0xE61C);
        if (handleReturnAddress(poppedEntry.value, 0x834F)) return;
        pushAddress(0x8352);
        jump(0x8AFF);
        if (handleReturnAddress(poppedEntry.value, 0x8352)) return;
        pushAddress(0x8355);
        jump(0x844F);
        if (handleReturnAddress(poppedEntry.value, 0x8355)) return;
        x = myMapper->readCPU(0x0654);
        setLoadFlag(x);
        if (flgZ) {
            goto L_00C367;
        }
        myMapper->writeCPU(0x0385 + x, myMapper->readCPU(0x0385));
        a = myMapper->readCPU(0x03A3);
        myMapper->writeCPU(0x03A3 + x, a);
    L_00C367:
        pushAddress(0x8369);
        jump(0xE1F0);
        if (handleReturnAddress(poppedEntry.value, 0x8369)) return;
        pushAddress(0x836C);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x836C)) return;
        pushAddress(0x836F);
        jump(0xCA15);
        if (handleReturnAddress(poppedEntry.value, 0x836F)) return;
        pushAddress(0x8372);
        jump(0x95F7);
        if (handleReturnAddress(poppedEntry.value, 0x8372)) return;
    }
L_00C373:
    goto L_00C2C2;
}

void game::SUB_00C376() {
    myMapper->writeCPU(0x05AC, x);
    x = 0x00;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0x838A + y));
        opINX(1);
        opINY(1);
    } while (x != 0x10);
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_00C39A() {
    a = myMapper->readCPU(0x0042);
    opAND(0x7F);
    myMapper->writeCPU(0x0042, a);
    opORA(0x04);
    myMapper->writeCPU(0x0043, a);
    a = myMapper->readCPU(SCROLL_FINE);
    opPHA();
    a = myMapper->readCPU(SCROLL_LARGE);
    opPHA();
    myMapper->writeCPU(SCROLL_LARGE, 0x00);
    a = myMapper->readCPU(0x00A0);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    opASL_A(1);
    opROL_M(SCROLL_LARGE, 1);
    myMapper->writeCPU(SCROLL_FINE, a);
    opDEC(SCROLL_LARGE, 1);
    myMapper->writeCPU(0x05AF, 0x08);
    do {
        a = myMapper->readCPU(0x00A0);
        pushAddress(0x83D6);
        jump(0xE20C);
        if (handleReturnAddress(poppedEntry.value, 0x83D6)) return;
        pushAddress(0x83D9);
        jump(0x93F0);
        if (handleReturnAddress(poppedEntry.value, 0x83D9)) return;
        pushAddress(0x83DC);
        jump(0x95F7);
        if (handleReturnAddress(poppedEntry.value, 0x83DC)) return;
        pushAddress(0x83DF);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x83DF)) return;
        pushAddress(0x83E2);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x83E2)) return;
        pushAddress(0x83E5);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x83E5)) return;
        pushAddress(0x83E8);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x83E8)) return;
        pushAddress(0x83EB);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x83EB)) return;
        pushAddress(0x83EE);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x83EE)) return;
        pushAddress(0x83F1);
        jump(0xE34E);
        if (handleReturnAddress(poppedEntry.value, 0x83F1)) return;
        pushAddress(0x83F4);
        jump(0xD60E);
        if (handleReturnAddress(poppedEntry.value, 0x83F4)) return;
        flgC = false;
        a = myMapper->readCPU(SCROLL_FINE);
        opADC(0x20);
        myMapper->writeCPU(SCROLL_FINE, a);
        if (!flgC) {
            goto L_00C403;
        }
        opINC(SCROLL_LARGE, 1);
    L_00C403:
        opINC(0x00A0, 1);
        opDEC(0x05AF, 1);
    } while (!flgN);
    opDEC(0x00A0, 1);
    opPLA();
    myMapper->writeCPU(SCROLL_LARGE, a);
    opPLA();
    myMapper->writeCPU(SCROLL_FINE, a);
    popAddress();
}

void game::SUB_00C44F() {
    if (myMapper->readCPU(0x05D0) == 0) {
        goto L_00C474;
    }
    if (myMapper->readCPU(0x0439) >= 0xC0) {
        x = 0x00;
        myMapper->writeCPU(0x05A3, x);
        myMapper->writeCPU(0x05A4, x);
        x = myMapper->readCPU(0x0051);
        if (myMapper->readCPU((0x0059 + x) & 0x00ff) == 0x07) {
            if (myMapper->readCPU(0x0476) != 0) {
                goto L_00C474;
            }
        }
        opDEX(1);
        myMapper->writeCPU(0x05D0, x);
    }
L_00C474:
    a = 0x00;
    myMapper->writeCPU(0x05CF, a);
    pushAddress(0x847B);
    jump(0x8A3A);
    if (handleReturnAddress(poppedEntry.value, 0x847B)) return;
    a = myMapper->readCPU(0x05D2);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
            if (!flgN) {
                goto L_00C49E;
            }
        }
        a = myMapper->readCPU(0x05C3);
        if (a != 0x01) {
            a = myMapper->readCPU(0x05C4);
            if (a != 0x01) {
                goto L_00C49E;
            }
        }
        x = 0x00;
        jump(0x8A14);
        return;
    L_00C49E:
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (!flgZ) {
        }
        else {
            opBIT(myMapper->readCPU(0x059F));
            if (flgN) {
            }
            else {
                a = myMapper->readCPU(0x05C3);
                myMapper->writeCPU(0x05C6, a);
                if (a < 0x10) {
                    if (a < 0x08) {
                        goto L_00C4BF;
                    }
                    goto L_00C588;
                L_00C4BF:
                    a = myMapper->readCPU(0x059D);
                    setLoadFlag(a);
                    if (flgN) {
                        goto L_00C595;
                    }
                    x = 0x00;
                    y = 0x00;
                    jump(0x89FB);
                    return;
                }
                flgC = true;
                opSBC(0x10);
                x = a;
                if (myMapper->readCPU(0x05D0) == 0xFF) {
                    a = 0xFF;
                    myMapper->writeCPU(0x05D1, a);
                    popAddress();
                    return;
                }
                a = myMapper->readCPU(0x8A75 + x);
                myMapper->writeCPU(0x05AA, a);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x05AB, a);
                myMapper->writeCPU(0x05A6, myMapper->readCPU(0x8A8D + x));
                myMapper->writeCPU(0x05A7, myMapper->readCPU(0x8AA5 + x));
                myMapper->writeCPU(0x05A8, myMapper->readCPU(0x8ABD + x));
                if (myMapper->readCPU(0x059D) != 0) {
                    a = 0x25;
                    pushAddress(0x8508);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x8508)) return;
                    x = 0x18;
                    pushAddress(0x850D);
                    jump(0x89E3);
                    if (handleReturnAddress(poppedEntry.value, 0x850D)) return;
                }
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
                a = myMapper->readCPU(0x05C6);
                x = 0x00;
                myMapper->writeCPU(0x0657, x);
                if (a == 0x1A) {
                    a = 0xFF;
                    myMapper->writeCPU(0x0657, a);
                }
                if (a == 0x1E) {
                    myMapper->writeCPU(0x0655, x);
                }
                myMapper->writeCPU(0x05A5, 0x00);
                x = 0x01;
                if (a != 0x18) {
                    x = 0x02;
                    if (a != 0x19) {
                        goto L_00C54F;
                    }
                }
                myMapper->writeCPU(0x05A5, x);
                a = 0x1A;
                pushAddress(0x854B);
                jump(0xEA16);
                if (handleReturnAddress(poppedEntry.value, 0x854B)) return;
                goto L_00C595;
            L_00C54F:
                if (a == 0x1D) {
                    a = 0x04;
                    myMapper->writeCPU(0x05A4, a);
                    myMapper->writeCPU(0x05AA, a);
                    a = 0x00;
                    myMapper->writeCPU(0x05A3, a);
                    x = 0xF8;
                    y = 0x00;
                    pushAddress(0x8566);
                    jump(0x89F1);
                    if (handleReturnAddress(poppedEntry.value, 0x8566)) return;
                    myMapper->writeCPU(0x05A7, 0x10);
                    a = 0x15;
                    pushAddress(0x8570);
                    jump(0xEA1B);
                    if (handleReturnAddress(poppedEntry.value, 0x8570)) return;
                    goto L_00C595;
                }
                x = 0xFD;
                myMapper->writeCPU(0x05CB, x);
                if (a == 0x1C) {
                    x = myMapper->readCPU(0x05B8);
                    setLoadFlag(x);
                    if (!flgZ) {
                        opDEC(0x05B8, 1);
                    }
                }
                goto L_00C595;
            L_00C588:
                myMapper->writeCPU(0x059D, 0x00);
                a = myMapper->readCPU(0x03C1);
                opAND(0xF8);
                myMapper->writeCPU(0x03C1, a);
            }
        }
    }
L_00C595:
    y = myMapper->readCPU(0x004B);
    a = y;
    opAND(0x01);
    if (flgZ) {
        goto L_00C5AC;
    }
    if (myMapper->readCPU(0x0657) == 0) {
        do {
            a = 0x00;
            myMapper->writeCPU(0x05CD, a);
            pushAddress(0x85A8);
            jump(0xE195);
            if (handleReturnAddress(poppedEntry.value, 0x85A8)) return;
            goto L_00C5BE;
        L_00C5AC:
            a = y;
            opAND(0x02);
            if (flgZ) {
                goto L_00C5BE;
            }
        } while (myMapper->readCPU(0x0657) != 0);
    }
    a = 0x80;
    myMapper->writeCPU(0x05CD, a);
    pushAddress(0x85BD);
    jump(0xE195);
    if (handleReturnAddress(poppedEntry.value, 0x85BD)) return;
L_00C5BE:
    if (myMapper->readCPU(0x059D) == 0) {
        if (myMapper->readCPU(0x0654) != 0) {
            goto L_00C5F4;
        }
        a = y;
        opAND(0x04);
        if (!flgZ) {
            if (myMapper->readCPU(0x05C3) == 0x17) {
                goto L_00C5E6;
            }
            if (myMapper->readCPU(0x05C9) != 0) {
                goto L_00C603;
            }
            x = 0x15;
            a = 0x10;
            myMapper->writeCPU(0x05C9, a);
            pushAddress(0x85E2);
            jump(0x89E8);
            if (handleReturnAddress(poppedEntry.value, 0x85E2)) return;
            goto L_00C603;
        L_00C5E6:
            a = myMapper->readCPU(0x058E);
            y = myMapper->readCPU(0x0051);
            myMapper->writeCPU(0x0059 + y, a);
            a = 0xFE;
            myMapper->writeCPU(0x05D1, a);
            popAddress();
            return;
        }
    }
L_00C5F4:
    if (myMapper->readCPU(0x05C9) != 0) {
        myMapper->writeCPU(0x05C9, 0x00);
        myMapper->writeCPU(0x05CA, 0x18);
    }
L_00C603:
    a = myMapper->readCPU(0x004C);
    opAND(0x80);
    if (!flgZ) {
        if (myMapper->readCPU(0x0655) == 0) {
            goto L_00C61F;
        }
        a = myMapper->readCPU(0x059D);
        setLoadFlag(a);
        if (flgZ) {
            x = 0xFB;
            y = 0x00;
            pushAddress(0x8619);
            jump(0x89F1);
            if (handleReturnAddress(poppedEntry.value, 0x8619)) return;
            a = 0x10;
            pushAddress(0x861E);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x861E)) return;
        }
    }
L_00C61F:
    if (myMapper->readCPU(0x05A0) != 0) {
        opDEC(0x05A0, 1);
        a = y;
        opAND(0x80);
        if (!flgZ) {
            if (myMapper->readCPU(0x059E) == 0xF8) {
                goto L_00C641;
            }
            flgC = true;
            a = myMapper->readCPU(0x059E);
            opSBC(0x01);
            myMapper->writeCPU(0x059E, a);
            if (!flgC) {
                opDEC(0x059F, 1);
            }
        }
    }
L_00C641:
    a = myMapper->readCPU(0x059D);
    setLoadFlag(a);
    if (!flgZ) {
        opBIT(myMapper->readCPU(0x059F));
        if (flgN) {
            if (myMapper->readCPU(0x05C4) < 0x10) {
                goto L_00C65D;
            }
            a = 0x00;
            myMapper->writeCPU(0x059F, a);
            myMapper->writeCPU(0x05A0, a);
            myMapper->writeCPU(0x059E, a);
        }
    L_00C65D:
        flgC = false;
        a = myMapper->readCPU(0x03C1);
        opADC(myMapper->readCPU(0x059E));
        myMapper->writeCPU(0x03C1, a);
        a = myMapper->readCPU(0x03DF);
        opADC(myMapper->readCPU(0x059F));
        myMapper->writeCPU(0x03DF, a);
        if (a == 0x02) {
            myMapper->writeCPU(0x05D1, 0x02);
        }
        opINC(0x05A9, 1);
        a = myMapper->readCPU(0x05A9);
        opAND(0x03);
        if (flgZ) {
            if (myMapper->readCPU(0x059E) == 0x08) {
                goto L_00C692;
            }
            opINC(0x059E, 1);
            if (flgZ) {
                opINC(0x059F, 1);
            }
        }
    }
L_00C692:
    a = myMapper->readCPU(0x0654);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x004C);
        opAND(0x40);
        if (!flgZ) {
            if (myMapper->readCPU(0x0655) == 0) {
                goto L_00C6B1;
            }
            x = 0x01;
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (!flgZ) {
                x = 0x07;
            }
            pushAddress(0x86AD);
            jump(0x89E3);
            if (handleReturnAddress(poppedEntry.value, 0x86AD)) return;
            goto L_00C6BD;
        L_00C6B1:
            x = 0x0D;
            a = myMapper->readCPU(0x05C9);
            setLoadFlag(a);
            if (!flgZ) {
                x = 0x11;
            }
            pushAddress(0x86BC);
            jump(0x89E3);
            if (handleReturnAddress(poppedEntry.value, 0x86BC)) return;
        }
    }
L_00C6BD:
    pushAddress(0x86BF);
    jump(0x8717);
    if (handleReturnAddress(poppedEntry.value, 0x86BF)) return;
    a = myMapper->readCPU(0x05A1);
    setLoadFlag(a);
    if (flgZ) {
        y = 0x05;
        x = 0x01;
        a = myMapper->readCPU(0x05A4);
        setLoadFlag(a);
        if (!flgN) {
            x = 0x03;
        }
        pushAddress(0x86D2);
        jump(0xE587);
        if (handleReturnAddress(poppedEntry.value, 0x86D2)) return;
        myMapper->writeCPU(0x05C7, a);
        if (a < 0x08) {
            a = myMapper->readCPU(0x059D);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00C6FB;
            }
            a = myMapper->readCPU(0x059F);
            setLoadFlag(a);
            if (flgN) {
                goto L_00C6FB;
            }
            y = 0x06;
            pushAddress(0x86E8);
            jump(0xE587);
            if (handleReturnAddress(poppedEntry.value, 0x86E8)) return;
            myMapper->writeCPU(0x05C8, a);
            if (a < 0x08) {
                goto L_00C6FB;
            }
        }
        a = 0x00;
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
        myMapper->writeCPU(0x05A5, a);
    }
L_00C6FB:
    pushAddress(0x86FD);
    jump(0xE0C9);
    if (handleReturnAddress(poppedEntry.value, 0x86FD)) return;
    pushAddress(0x8700);
    jump(0xDED2);
    if (handleReturnAddress(poppedEntry.value, 0x8700)) return;
    opCMP(y, myMapper->readCPU(SCROLL_LARGE));
    if (!flgZ) {
        if (flgC) {
            goto L_00C710;
        }
    }
    else {
        if (x < myMapper->readCPU(SCROLL_FINE)) {
            goto L_00C716;
        }
    L_00C710:
        myMapper->writeCPU(SCROLL_FINE, x);
        myMapper->writeCPU(SCROLL_LARGE, y);
    }
L_00C716:
    popAddress();
}

void game::SUB_00C717() {
    x = myMapper->readCPU(0x05CA);
    setLoadFlag(x);
    if (flgZ) {
        jump(0x8856);
        return;
    }
    a = myMapper->readCPU(0x842B + x);
    setLoadFlag(a);
    if (!flgN) {
        x = a;
        opAND(0x3F);
        opORA(myMapper->readCPU(0x05CD));
        myMapper->writeCPU(0x03FD, a);
        if (x != 0x0A) {
            if (x != 0x04) {
                goto L_00C738;
            }
        }
        pushAddress(0x8737);
        jump(0x8772);
        if (handleReturnAddress(poppedEntry.value, 0x8737)) return;
    L_00C738:
        opDEC(0x05CE, 1);
        if (flgN) {
            goto L_00C751;
        }
        popAddress();
        return;
    }
    x = 0x00;
    myMapper->writeCPU(0x05CA, x);
    if (myMapper->readCPU(0x059D) == 0) {
        goto L_00C750;
    }
    a = 0x1F;
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
L_00C750:
    popAddress();
    return;
L_00C751:
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    opINC(0x05CA, 1);
    if (x == 0x05) {
        jump(0x8789);
        return;
    }
    if (x == 0x0B) {
        jump(0x8789);
        return;
    }
    if (x == 0x07) {
        jump(0x87CD);
        return;
    }
    if (x == 0x0D) {
        jump(0x87CD);
        return;
    }
    if (x == 0x47) {
        jump(0x87CD);
        return;
    }
    if (x == 0x4D) {
        jump(0x87CD);
        return;
    }
    popAddress();
}

void game::SUB_00C772() {
    y = 0x00;
    a = myMapper->readCPU(0x0656);
    setLoadFlag(a);
    if (!flgN) {
        goto L_00C77A;
    }
    opDEY(1);
L_00C77A:
    flgC = false;
    opADC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0385, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3));
    myMapper->writeCPU(0x03A3, a);
    popAddress();
}

void game::SUB_00C789() {
    y = 0x01;
    myMapper->writeCPU(0x05BC, y);
    pushAddress(0x8790);
    jump(0x88E8);
    if (handleReturnAddress(poppedEntry.value, 0x8790)) return;
    if (!flgZ) {
        y = 0x02;
        pushAddress(0x8797);
        jump(0x88E8);
        if (handleReturnAddress(poppedEntry.value, 0x8797)) return;
        if (!flgZ) {
            y = 0x06;
            pushAddress(0x879E);
            jump(0x88E8);
            if (handleReturnAddress(poppedEntry.value, 0x879E)) return;
            if (!flgZ) {
                y = 0x07;
                pushAddress(0x87A5);
                jump(0x88E8);
                if (handleReturnAddress(poppedEntry.value, 0x87A5)) return;
                if (!flgZ) {
                    popAddress();
                    return;
                }
            }
        }
    }
    a = 0x0D;
    pushAddress(0x87AD);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x87AD)) return;
    a = myMapper->readCPU(0x050B + y);
    flgC = true;
    opSBC(0x01);
    myMapper->writeCPU(0x050B + y, a);
    if (!flgN) {
        goto L_00C7BE;
    }
    x = 0x00;
    jump(0x8F8A);
    return;
L_00C7BE:
    x = y;
    a = myMapper->readCPU(0x03FD);
    opAND(0x80);
    myMapper->writeCPU(0x0565 + x, a);
    y = 0x07;
    jump(0x9049);
    return;
}

void game::SUB_00C7CD() {
    a = myMapper->readCPU(0x0595);
    setLoadFlag(a);
    if (!flgZ) {
        opDEC(0x0596, 1);
        if (flgZ) {
            myMapper->writeCPU(0x0595, 0x00);
            a = 0x02;
            myMapper->writeCPU(0x0594, a);
        }
        if (x >= 0x40) {
            if (a == 0x04) {
                goto L_00C836;
            }
            if (a == 0x05) {
                goto L_00C836;
            }
            x = 0x00;
            y = 0x03;
            if (myMapper->readCPU(0x0475 + y) == 0) {
                a = myMapper->readCPU(0x0595);
                if (a == 0x01) {
                    goto L_00C820;
                }
                if (a == 0x02) {
                    goto L_00C802;
                }
            }
        }
        popAddress();
        return;
    L_00C802:
        pushAddress(0x8838);
        jump(0x8987);
        if (handleReturnAddress(poppedEntry.value, 0x8838)) return;
        y = 0x04;
        x = 0xFA;
        pushAddress(0x880B);
        jump(0x8987);
        if (handleReturnAddress(poppedEntry.value, 0x880B)) return;
        y = 0x05;
        x = 0x06;
        pushAddress(0x8812);
        jump(0x8987);
        if (handleReturnAddress(poppedEntry.value, 0x8812)) return;
        a = 0x00;
        myMapper->writeCPU(0x0497, a);
        myMapper->writeCPU(0x0498, a);
        a = 0x07;
        jump(0xEA1B);
        return;
    L_00C820:
        pushAddress(0x8850);
        jump(0x8987);
        if (handleReturnAddress(poppedEntry.value, 0x8850)) return;
        x = 0xFA;
        y = 0x04;
        pushAddress(0x8829);
        jump(0x8987);
        if (handleReturnAddress(poppedEntry.value, 0x8829)) return;
        x = 0x06;
        y = 0x05;
        pushAddress(0x8830);
        jump(0x8987);
        if (handleReturnAddress(poppedEntry.value, 0x8830)) return;
        a = 0x08;
        jump(0xEA1B);
        return;
    }
L_00C836:
    x = 0x00;
    y = 0x03;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x04;
        if (myMapper->readCPU(0x0475 + y) != 0) {
            y = 0x05;
            if (myMapper->readCPU(0x0475 + y) == 0) {
                goto L_00C84E;
            }
            popAddress();
            return;
        }
    }
L_00C84E:
    a = 0x06;
    pushAddress(0x8852);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x8852)) return;
    jump(0x8987);
    return;
}

void game::SUB_00C856() {
    a = 0x09;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        if (myMapper->readCPU(0x0654) != 0) {
            goto L_00C86C;
        }
        if (myMapper->readCPU(0x059D) == 0) {
            goto L_00C875;
        }
        a = 0x1F;
        goto L_00C86E;
    L_00C86C:
        a = 0x00;
    }
L_00C86E:
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    popAddress();
    return;
L_00C875:
    a = myMapper->readCPU(0x05C3);
    opCMP(a, 0x11);
    if (!flgZ) {
        opCMP(a, 0x12);
        if (!flgZ) {
            goto L_00C885;
        }
    }
    if (myMapper->readCPU(0x05CF) == 0) {
        goto L_00C86C;
    }
L_00C885:
    a = myMapper->readCPU(0x05A3);
    opORA(myMapper->readCPU(0x05A4));
    if (!flgZ) {
        opDEC(0x05A2, 1);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x05A4));
            if (flgN) {
                a = myMapper->readCPU(0x05A3);
                opEOR(0xFF);
                flgC = false;
                opADC(0x01);
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x05A4);
                opEOR(0xFF);
                opADC(0x00);
            }
            else {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x05A3));
                a = myMapper->readCPU(0x05A4);
            }
            opROL_M(0x0000, 1);
            opROL_A(1);
            x = a;
            myMapper->writeCPU(0x05A2, myMapper->readCPU(0x8A70 + x));
            opINC(0x03FD, 1);
        }
    }
    a = myMapper->readCPU(0x03FD);
    opAND(0x03);
    opORA(myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x03FD, a);
    opAND(0x7F);
    if (a != myMapper->readCPU(0x00B8)) {
        myMapper->writeCPU(0x00B8, a);
        if (myMapper->readCPU(0x00FD) == 0) {
            x = 0x23;
            a = myMapper->readCPU(0x00B8);
            setLoadFlag(a);
            if (flgZ) {
                goto L_00C8E3;
            }
            x = 0x24;
            if (a != 0x02) {
                goto L_00C8E7;
            }
        L_00C8E3:
            a = x;
            jump(0xEA1B);
            return;
        }
    }
L_00C8E7:
    popAddress();
}

void game::SUB_00C8E8() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x05) {
            goto L_00C94F;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_00C94F;
            }
            if (myMapper->readCPU(0x0529 + y) < 0x07) {
                if (myMapper->readCPU(0x03DF) != 0) {
                    goto L_00C94F;
                }
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(myMapper->readCPU(0x05C9));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x041B + y);
                if (a != 0x06) {
                    if (a != 0x07) {
                        goto L_00C952;
                    }
                }
                a = myMapper->readCPU(0x03C1 + y);
                flgC = false;
                opADC(0x20);
                flgC = true;
                opSBC(myMapper->readCPU(0x0000));
                if (!flgN) {
                    if (a >= 0x30) {
                        goto L_00C94F;
                    }
                    flgC = true;
                    opBIT(myMapper->readCPU(0x03FD));
                    if (!flgN) {
                        goto L_00C941;
                    }
                    a = myMapper->readCPU(0x0439);
                    opSBC(myMapper->readCPU(0x0439 + y));
                    if (flgC) {
                        if (a >= 0x08) {
                            goto L_00C94F;
                        }
                        do {
                            do {
                                a = 0x00;
                                setLoadFlag(a);
                                popAddress();
                                return;
                            L_00C941:
                                a = myMapper->readCPU(0x0439 + y);
                                opSBC(myMapper->readCPU(0x0439));
                                if (!flgC) {
                                    goto L_00C94F;
                                }
                                opCMP(a, 0x10);
                            } while (flgZ);
                        } while (!flgC);
                    }
                }
            }
        }
    }
L_00C94F:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
    return;
L_00C952:
    a = myMapper->readCPU(0x03C1 + y);
    flgC = false;
    opADC(0x08);
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    if (flgC) {
        if (a >= 0x18) {
            goto L_00C984;
        }
        flgC = true;
        opBIT(myMapper->readCPU(0x03FD));
        if (!flgN) {
            goto L_00C976;
        }
        a = myMapper->readCPU(0x0439);
        opSBC(myMapper->readCPU(0x0439 + y));
        if (flgC) {
            if (a >= 0x10) {
                goto L_00C984;
            }
            do {
                do {
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                L_00C976:
                    a = myMapper->readCPU(0x0439 + y);
                    opSBC(myMapper->readCPU(0x0439));
                    if (!flgC) {
                        goto L_00C984;
                    }
                    opCMP(a, 0x18);
                } while (flgZ);
            } while (!flgC);
        }
    }
L_00C984:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00C987() {
    myMapper->writeCPU(0x04B1 + y, x);
    a = myMapper->readCPU(0x0385);
    opBIT(myMapper->readCPU(0x05CD));
    if (flgN) {
        flgC = true;
        opSBC(0x10);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        a = 0xFA;
        myMapper->writeCPU(0x0493 + y, a);
    }
    else {
        flgC = false;
        opADC(0x20);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x03A3);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        myMapper->writeCPU(0x0493 + y, 0x06);
    }
    myMapper->writeCPU(0x03DF + y, myMapper->readCPU(0x03DF));
    a = 0x08;
    x = myMapper->readCPU(0x05C9);
    setLoadFlag(x);
    if (flgZ) {
        goto L_00C9CB;
    }
    a = 0x18;
L_00C9CB:
    flgC = false;
    opADC(myMapper->readCPU(0x03C1));
    myMapper->writeCPU(0x03C1 + y, a);
    myMapper->writeCPU(0x03FD + y, myMapper->readCPU(0x05CD));
    myMapper->writeCPU(0x0475 + y, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x0457 + y, a);
    popAddress();
}

void game::SUB_00C9E3() {
    a = myMapper->readCPU(0x05CA);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x89F0);
        return;
    }
    SUB_00C9E8();
    return;
}

void game::SUB_00C9E8() {
    myMapper->writeCPU(0x05CA, x);
    a = 0x03;
    myMapper->writeCPU(0x05CE, a);
    SUB_00C9F0();
    return;
}

void game::SUB_00C9F0() {
    popAddress();
}

void game::SUB_00C9F1() {
    a = myMapper->readCPU(0x05A6);
    setLoadFlag(a);
    if (!flgZ) {
        jump(0x89FB);
        return;
    }
    a = 0x40;
    myMapper->writeCPU(0x05A6, a);
    SUB_00C9FB();
    return;
}

void game::SUB_00C9FB() {
    myMapper->writeCPU(0x05A0, y);
    myMapper->writeCPU(0x059E, x);
    x = 0x00;
    myMapper->writeCPU(0x05A9, x);
    opBIT(myMapper->readCPU(0x059E));
    if (!flgN) {
        goto L_00CA0C;
    }
    opDEX(1);
L_00CA0C:
    myMapper->writeCPU(0x059F, x);
    opDEX(1);
    myMapper->writeCPU(0x059D, x);
    popAddress();
}

void game::SUB_00CA14() {
    pushAddress(0x8A16);
    jump(0x8A22);
    if (handleReturnAddress(poppedEntry.value, 0x8A16)) return;
    a = 0x1F;
    pushAddress(0x8A1B);
    jump(0xEA16);
    if (handleReturnAddress(poppedEntry.value, 0x8A1B)) return;
    a = 0xFF;
    myMapper->writeCPU(0x05D2, a);
    popAddress();
}

void game::SUB_00CA22() {
    y = 0x02;
    if (!(myMapper->readCPU(0x0493 + x) & 0x80)) {
        goto L_00CA2B;
    }
    y = 0xFE;
L_00CA2B:
    myMapper->writeCPU(0x05A4, y);
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    x = 0xFB;
    y = 0x00;
    jump(0x89F1);
    return;
}

void game::SUB_00CA3A() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF));
    y = myMapper->readCPU(0x03C1);
    flgC = true;
    a = myMapper->readCPU(0x0385);
    opSBC(0x04);
    x = a;
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    myMapper->writeCPU(0x0095, a);
    pushAddress(0x8A52);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x8A52)) return;
    x = 0x02;
    y = 0x06;
    pushAddress(0x8A59);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8A59)) return;
    myMapper->writeCPU(0x05C3, a);
    y = 0x00;
    pushAddress(0x8A61);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8A61)) return;
    myMapper->writeCPU(0x05C4, a);
    x = 0x02;
    y = 0x05;
    pushAddress(0x8A6B);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8A6B)) return;
    myMapper->writeCPU(0x05C5, a);
    popAddress();
}

void game::SUB_00CAFF() {
    pushAddress(0x8B01);
    jump(0x93F0);
    if (handleReturnAddress(poppedEntry.value, 0x8B01)) return;
    x = 0x00;
    myMapper->writeCPU(0x0659, x);
    myMapper->writeCPU(0x0654, x);
    myMapper->writeCPU(0x05BC, x);
    myMapper->writeCPU(0x05A1, x);
    opDEX(1);
    myMapper->writeCPU(0x0655, x);
    x = 0x01;
    myMapper->writeCPU(0x05CC, myMapper->readCPU(0x0587));
    SUB_00CB1C();
    return;
}

void game::SUB_00CB1C() {
    myMapper->writeCPU(0x05AC, x);
    y = myMapper->readCPU(0x0475 + x);
    setLoadFlag(y);
    if (flgZ) {
        jump(0x8B37);
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x8ADF + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x8AEF + y));
    a = 0x8B;
    opPHA();
    a = 0x36;
    opPHA();
    pushManualAddress(0x8B36);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_00CB37() {
    opINC(0x05AF, 1);
    x = myMapper->readCPU(0x05AC);
    opINX(1);
    opDEC(0x05CC, 1);
    if (!flgZ) {
        jump(0x8B1C);
        return;
    }
    SUB_00CB43();
    return;
}

void game::SUB_00CB43() {
    a = myMapper->readCPU(0x003F);
    flgC = false;
    opADC(myMapper->readCPU(0x05AF));
    myMapper->writeCPU(0x05AF, a);
    popAddress();
}

void game::SUB_00CB4D() {
    myMapper->writeCPU(0x03FD + x, 0xFF);
    opINC(0x04CF + x, 1);
    a = myMapper->readCPU(0x04CF + x);
    if (a != 0x40) {
        if (a == 0x50) {
            goto L_00CB61;
        }
        popAddress();
        return;
    }
L_00CB61:
    pushAddress(0x8B63);
    jump(0x93DC);
    if (handleReturnAddress(poppedEntry.value, 0x8B63)) return;
    if (flgN) {
        goto L_00CBA4;
    }
    myMapper->writeCPU(0x0475 + y, 0x09);
    myMapper->writeCPU(0x04B1 + y, 0xF8);
    myMapper->writeCPU(0x03FD + y, 0x09);
    myMapper->writeCPU(0x03C1 + y, myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x0385 + y, myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x03A3 + y, myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x041B + y, 0x02);
    a = 0x00;
    myMapper->writeCPU(0x0457 + y, a);
    myMapper->writeCPU(0x03DF + y, a);
    myMapper->writeCPU(0x0565 + y, a);
    if (myMapper->readCPU(0x0439 + x) >= myMapper->readCPU(0x0439)) {
        goto L_00CBA5;
    }
    myMapper->writeCPU(0x0493 + y, 0x03);
L_00CBA4:
    popAddress();
    return;
L_00CBA5:
    myMapper->writeCPU(0x0493 + y, 0xFD);
    popAddress();
}

void game::SUB_00CBAB() {
    y = 0x02;
    pushAddress(0x8BAF);
    jump(0x954A);
    if (handleReturnAddress(poppedEntry.value, 0x8BAF)) return;
    if (!flgN) {
        a = myMapper->readCPU(0x008E);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x008E, a);
        jump(0x9336);
        return;
    }
    a = myMapper->readCPU(0x04B1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    opCMP(a, 0xF0);
    if (!flgC) {
        opINC(0x0565 + x, 1);
        a = myMapper->readCPU(0x0565 + x);
        opAND(0x03);
        if (flgZ) {
            opINC(0x04B1 + x, 1);
        }
        y = 0x00;
        a = myMapper->readCPU(0x0493 + x);
        setLoadFlag(a);
        if (!flgN) {
            goto L_00CBDF;
        }
        opDEY(1);
    L_00CBDF:
        opADC(myMapper->readCPU(0x0385 + x));
        myMapper->writeCPU(0x0385 + x, a);
        a = y;
        opADC(myMapper->readCPU(0x03A3 + x));
        myMapper->writeCPU(0x03A3 + x, a);
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_00CBF3() {
    y = 0x03;
    pushAddress(0x8BF7);
    jump(0x954A);
    if (handleReturnAddress(poppedEntry.value, 0x8BF7)) return;
    if (!flgN) {
        a = myMapper->readCPU(0x008E);
        flgC = true;
        opSBC(0x02);
        myMapper->writeCPU(0x008E, a);
        jump(0x9336);
        return;
    }
    myMapper->writeCPU(0x050B + x, 0x00);
    myMapper->writeCPU(0x041B + x, 0x04);
    myMapper->writeCPU(0x04ED + x, 0x0B);
    myMapper->writeCPU(0x03FD + x, 0x00);
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        opINC(0x03C1 + x, 1);
        if (myMapper->readCPU(0x03C1 + x) >= 0xE8) {
            goto L_00CC4F;
        }
    }
    a = myMapper->readCPU(0x003F);
    opLSR_A(1);
    if (!flgC) {
        opINC(0x04CF + x, 1);
    }
    a = myMapper->readCPU(0x04CF + x);
    opAND(0x1F);
    y = a;
    a = myMapper->readCPU(0x8C55 + y);
    setLoadFlag(a);
    pushStatus();
    y = 0x00;
    setLoadFlag(y);
    popStatus();
    if (!flgN) {
        goto L_00CC40;
    }
    opDEY(1);
L_00CC40:
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    popAddress();
    return;
L_00CC4F:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_00CC75() {
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x0095, myMapper->readCPU(0x03A3 + x));
    y = myMapper->readCPU(0x03C1 + x);
    a = myMapper->readCPU(0x0385 + x);
    x = a;
    pushAddress(0x8C88);
    jump(0xE567);
    if (handleReturnAddress(poppedEntry.value, 0x8C88)) return;
    x = myMapper->readCPU(0x05AC);
    y = 0x05;
    a = myMapper->readCPU(0x0565 + x);
    setLoadFlag(a);
    if (flgN) {
        goto L_00CC98;
    }
    x = 0x02;
    goto L_00CC9A;
L_00CC98:
    x = 0x00;
L_00CC9A:
    pushAddress(0x8C9C);
    jump(0xE587);
    if (handleReturnAddress(poppedEntry.value, 0x8C9C)) return;
    x = myMapper->readCPU(0x05AC);
    popAddress();
}

void game::SUB_00CCA1() {
    myMapper->writeCPU(0x041B + x, 0x07);
    myMapper->writeCPU(0x050B + x, 0x03);
    myMapper->writeCPU(0x0475 + x, 0x0F);
    myMapper->writeCPU(0x04ED + x, 0x00);
    a = 0x80;
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x0493 + x, a);
    popAddress();
}

void game::SUB_00CCBE() {
    pushAddress(0x8CC0);
    jump(0x8F4E);
    if (handleReturnAddress(poppedEntry.value, 0x8CC0)) return;
    pushAddress(0x8CC3);
    jump(0x8C75);
    if (handleReturnAddress(poppedEntry.value, 0x8CC3)) return;
    if (a < 0x08) {
        pushAddress(0x8CCA);
        jump(0x90D0);
        if (handleReturnAddress(poppedEntry.value, 0x8CCA)) return;
        a = 0x04;
        opORA(myMapper->readCPU(0x0493 + x));
        myMapper->writeCPU(0x03FD + x, a);
    }
    else {
        if (a != 0xFE) {
            goto L_00CCE8;
        }
        a = myMapper->readCPU(0x0493 + x);
        opEOR(0x80);
        myMapper->writeCPU(0x0493 + x, a);
        myMapper->writeCPU(0x0565 + x, a);
        goto L_00CD17;
    L_00CCE8:
        myMapper->writeCPU(0x04B1 + x, 0xFA);
        a = myMapper->readCPU(0x03C1 + x);
        opAND(0xF8);
        myMapper->writeCPU(0x03C1 + x, a);
        a = myMapper->readCPU(0x0529 + x);
        setLoadFlag(a);
        if (!flgZ) {
            jump(0x9063);
            return;
        }
        if (!(myMapper->readCPU(0x05BB) & 0x80)) {
            a = myMapper->readCPU(0x004D);
            opAND(0x07);
            if (flgZ) {
                y = 0x01;
                jump(0x9049);
                return;
            }
            a = myMapper->readCPU(0x04CF + x);
            opORA(myMapper->readCPU(0x0493 + x));
            myMapper->writeCPU(0x03FD + x, a);
            popAddress();
            return;
        }
    L_00CD17:
        a = myMapper->readCPU(0x003F);
        opAND(0x0C);
        opLSR_A(2);
        opORA(myMapper->readCPU(0x0493 + x));
        opADC(myMapper->readCPU(0x04CF + x));
        myMapper->writeCPU(0x03FD + x, a);
    }
    if (myMapper->readCPU(0x05BB) != 0) {
        a = myMapper->readCPU(0x0493 + x);
        setLoadFlag(a);
        myMapper->writeCPU(0x0565 + x, a);
        if (flgN) {
            a = myMapper->readCPU(0x0385 + x);
            flgC = true;
            opSBC(0x02);
            myMapper->writeCPU(0x0385 + x, a);
            if (flgC) {
                goto L_00CD52;
            }
            opDEC(0x03A3 + x, 1);
        }
        else {
            a = myMapper->readCPU(0x0385 + x);
            flgC = false;
            opADC(0x02);
            myMapper->writeCPU(0x0385 + x, a);
            if (flgC) {
                opINC(0x03A3 + x, 1);
            }
        }
    }
L_00CD52:
    a = myMapper->readCPU(0x05AF);
    opAND(0xBB);
    if (!flgZ) {
        goto L_00CD5C;
    }
    jump(0x9378);
    return;
L_00CD5C:
    popAddress();
}

void game::SUB_00CD5D() {
    a = 0x00;
    y = 0x00;
    jump(0x8D68);
    return;
}

void game::SUB_00CD64() {
    a = 0x2C;
    y = 0x00;
    SUB_00CD68();
    return;
}

void game::SUB_00CD68() {
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x03FD + x, y);
    myMapper->writeCPU(0x0475 + x, 0x0C);
    myMapper->writeCPU(0x041B + x, 0x05);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    a = myMapper->readCPU(0x04CF + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    if (!flgC) {
        goto L_00CD8D;
    }
    opINC(0x03A3 + x, 1);
L_00CD8D:
    popAddress();
}

void game::SUB_00CD8E() {
    pushAddress(0x8D90);
    jump(0x8E88);
    if (handleReturnAddress(poppedEntry.value, 0x8D90)) return;
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        y = myMapper->readCPU(0x0493 + x);
        while (true) {
            a = myMapper->readCPU(0x8E1F + y);
            myMapper->writeCPU(0x0002, a);
            if (a != 0x81) {
                goto L_00CDAC;
            }
            a = 0x00;
            myMapper->writeCPU(0x0493 + x, a);
            y = a;
        }
    L_00CDAC:
        flgC = false;
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            if (!flgC) {
                goto L_00CDCA;
            }
            opINC(0x03A3 + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            if (!flgC) {
                opDEC(0x03A3 + x, 1);
            }
        }
    L_00CDCA:
        flgC = false;
        a = myMapper->readCPU(0x8E54 + y);
        setLoadFlag(a);
        if (!flgN) {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                goto L_00CDE9;
            }
            opINC(0x03DF + x, 1);
        }
        else {
            opADC(myMapper->readCPU(0x03C1 + x));
            myMapper->writeCPU(0x03C1 + x, a);
            if (!flgC) {
                opDEC(0x03DF + x, 1);
            }
        }
    L_00CDE9:
        opINC(0x0493 + x, 1);
    }
    if (myMapper->readCPU(0x0004) != 0) {
        myMapper->writeCPU(0x05A6, 0x18);
        myMapper->writeCPU(0x03DF, myMapper->readCPU(0x03DF + x));
        a = myMapper->readCPU(0x03C1 + x);
        flgC = true;
        opSBC(0x30);
        myMapper->writeCPU(0x03C1, a);
        if (!flgC) {
            opDEC(0x03DF, 1);
        }
        y = 0x00;
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
        if (!flgN) {
            goto L_00CE10;
        }
        opDEY(1);
    L_00CE10:
        flgC = false;
        opADC(myMapper->readCPU(0x0385));
        myMapper->writeCPU(0x0385, a);
        a = y;
        opADC(myMapper->readCPU(0x03A3));
        myMapper->writeCPU(0x03A3, a);
    }
    popAddress();
}

void game::SUB_00CE88() {
    a = 0x00;
    myMapper->writeCPU(0x0002, a);
    myMapper->writeCPU(0x0004, a);
    if (myMapper->readCPU(0x05D2) == 0) {
        a = myMapper->readCPU(0x05A1);
        setLoadFlag(a);
        if (flgZ) {
            opBIT(myMapper->readCPU(0x059F));
            if (!flgN) {
                myMapper->writeCPU(0x0000, myMapper->readCPU(0x03DF));
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(0x30);
                if (flgC) {
                    opINC(0x0000, 1);
                }
                flgC = true;
                opSBC(myMapper->readCPU(0x03C1 + x));
                myMapper->writeCPU(0x0001, a);
                a = myMapper->readCPU(0x0000);
                opSBC(0x00);
                if (flgZ) {
                    if (myMapper->readCPU(0x0001) >= 0x10) {
                        goto L_00CF07;
                    }
                    myMapper->writeCPU(0x0000, myMapper->readCPU(0x03A3));
                    a = myMapper->readCPU(0x0385);
                    flgC = false;
                    opADC(0x10);
                    if (flgC) {
                        opINC(0x0000, 1);
                    }
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0385 + x));
                    myMapper->writeCPU(0x0001, a);
                    a = myMapper->readCPU(0x0000);
                    opSBC(myMapper->readCPU(0x03A3 + x));
                    if (flgZ) {
                        if (myMapper->readCPU(0x0001) >= 0x28) {
                            goto L_00CF07;
                        }
                        a = 0x1A;
                        pushAddress(0x8EE4);
                        jump(0xEA16);
                        if (handleReturnAddress(poppedEntry.value, 0x8EE4)) return;
                        a = 0xFF;
                        myMapper->writeCPU(0x05A1, a);
                        myMapper->writeCPU(0x0004, a);
                        if (myMapper->readCPU(0x059D) == 0) {
                            goto L_00CEF9;
                        }
                        a = 0x00;
                        myMapper->writeCPU(0x05A3, a);
                        myMapper->writeCPU(0x05A4, a);
                    L_00CEF9:
                        a = 0x00;
                        myMapper->writeCPU(0x05A5, a);
                        myMapper->writeCPU(0x059D, a);
                        myMapper->writeCPU(0x059E, a);
                        myMapper->writeCPU(0x059F, a);
                    }
                }
            }
        }
    }
L_00CF07:
    a = myMapper->readCPU(0x0004);
    popAddress();
}

void game::SUB_00CF29() {
    if (myMapper->readCPU(0x05BD) != 0) {
        goto L_00CF4B;
    }
    if (myMapper->readCPU(0x0457 + x) == 0) {
        if (myMapper->readCPU(0x03DF) != 0) {
            goto L_00CF4B;
        }
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x30);
        flgC = true;
        opSBC(myMapper->readCPU(0x03C1));
        if (!flgN) {
            if (a >= 0x40) {
                goto L_00CF4B;
            }
            a = 0x00;
            setLoadFlag(a);
            popAddress();
            return;
        }
    }
L_00CF4B:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00CF4E() {
    pushAddress(0x8F50);
    jump(0x8F29);
    if (handleReturnAddress(poppedEntry.value, 0x8F50)) return;
    if (flgZ) {
        flgC = true;
        if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
            goto L_00CF78;
        }
        a = myMapper->readCPU(0x0439 + x);
        opSBC(myMapper->readCPU(0x0439));
        if (flgC) {
            if (a < 0x0C) {
                goto L_00CF84;
            }
            if (a >= 0x10) {
                goto L_00CF84;
            }
            do {
                a = 0x00;
                myMapper->writeCPU(0x0655, a);
                myMapper->writeCPU(0x05BB, a);
                myMapper->writeCPU(0x05A3, a);
                myMapper->writeCPU(0x05A4, a);
                popAddress();
                return;
            L_00CF78:
                a = myMapper->readCPU(0x0439);
                opSBC(myMapper->readCPU(0x0439 + x));
                if (!flgC) {
                    goto L_00CF84;
                }
            } while (a < 0x08);
        }
    }
L_00CF84:
    a = 0xFF;
    myMapper->writeCPU(0x05BB, a);
    popAddress();
}

void game::SUB_00CF8A() {
    a = myMapper->readCPU(0x03FD + x);
    opORA(0x01);
    myMapper->writeCPU(0x0565 + y, a);
    myMapper->writeCPU(0x04B1 + y, 0xFB);
    SUB_00CF97();
    return;
}

void game::SUB_00CF97() {
    myMapper->writeCPU(0x0475 + y, 0x05);
    a = myMapper->readCPU(0x03FD + y);
    opAND(0x80);
    flgC = false;
    x = myMapper->readCPU(0x04ED + y);
    if (x != 0x0B) {
        if (x == 0x0A) {
            goto L_00CFDA;
        }
        if (x != 0x09) {
            goto L_00CFE6;
        }
        opORA(myMapper->readCPU(0x04CF + y));
        myMapper->writeCPU(0x03FD + y, a);
        if (myMapper->readCPU(0x05BC) == 0) {
            goto L_00CFCD;
        }
        a = 0x13;
        pushAddress(0x8FC0);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x8FC0)) return;
        a = myMapper->readCPU(0x0565 + y);
        opEOR(0x80);
        myMapper->writeCPU(0x0565 + y, a);
        opINC(0x0083, 1);
        opINC(0x008F, 1);
    L_00CFCD:
        popAddress();
        return;
    }
    x = y;
    a = myMapper->readCPU(0x0081);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x0081, a);
    jump(0x9336);
    return;
    while (true) {
    L_00CFDA:
        a = myMapper->readCPU(0x0082);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x0082, a);
        a = 0x1F;
        jump(0xEA1B);
        return;
    L_00CFE6:
        a = 0x04;
        opORA(myMapper->readCPU(0x0493 + y));
        myMapper->writeCPU(0x03FD + y, a);
    }
    SUB_00CFF1();
    return;
}

void game::SUB_00CFF1() {
    if (myMapper->readCPU(0x03DF + x) == 0x01) {
        goto L_00D043;
    }
    y = 0x00;
    a = myMapper->readCPU(0x04B1 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    a = y;
    opADC(myMapper->readCPU(0x03DF + x));
    myMapper->writeCPU(0x03DF + x, a);
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        if (myMapper->readCPU(0x04B1 + x) == 0x08) {
            goto L_00D01E;
        }
        opINC(0x04B1 + x, 1);
    }
L_00D01E:
    a = myMapper->readCPU(0x0565 + x);
    setLoadFlag(a);
    if (!flgZ) {
        if (!flgN) {
            goto L_00D034;
        }
        a = myMapper->readCPU(0x0385 + x);
        flgC = true;
        opSBC(0x03);
        myMapper->writeCPU(0x0385 + x, a);
        if (flgC) {
            goto L_00D033;
        }
        opDEC(0x03A3 + x, 1);
    }
    do {
    L_00D033:
        popAddress();
        return;
    L_00D034:
        a = myMapper->readCPU(0x0385 + x);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x0385 + x, a);
    } while (!flgC);
    opINC(0x03A3 + x, 1);
    popAddress();
    return;
L_00D043:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_00D049() {
    myMapper->writeCPU(0x0529 + x, y);
    myMapper->writeCPU(0x0547 + x, 0x06);
    a = myMapper->readCPU(0x03FD + x);
    opAND(0x80);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0547 + x, 0x00);
    a = myMapper->readCPU(0x0529 + x);
    popAddress();
}

void game::SUB_00D063() {
    y = a;
    a = myMapper->readCPU(0x8AD5 + y);
    setLoadFlag(a);
    if (flgN) {
        goto L_00D0B2;
    }
    y = a;
    opAND(0x3F);
    opORA(myMapper->readCPU(0x0493 + x));
    myMapper->writeCPU(0x03FD + x, a);
    if (y == 0x40) {
        goto L_00D07C;
    }
    while (true) {
        while (true) {
            opDEC(0x0547 + x, 1);
            if (flgN) {
                goto L_00D0B8;
            }
            popAddress();
            return;
        L_00D07C:
            a = myMapper->readCPU(0x04CF + x);
            opORA(myMapper->readCPU(0x0493 + x));
            myMapper->writeCPU(0x03FD + x, a);
            if (!(myMapper->readCPU(0x0565 + x) & 0x80)) {
                goto L_00D09E;
            }
            a = myMapper->readCPU(0x0385 + x);
            flgC = true;
            opSBC(0x04);
            myMapper->writeCPU(0x0385 + x, a);
            a = myMapper->readCPU(0x03A3 + x);
            opSBC(0x00);
            myMapper->writeCPU(0x03A3 + x, a);
        }
    L_00D09E:
        a = myMapper->readCPU(0x0385 + x);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x0385 + x, a);
        a = myMapper->readCPU(0x03A3 + x);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + x, a);
    }
L_00D0B2:
    myMapper->writeCPU(0x0529 + x, 0x00);
    popAddress();
    return;
L_00D0B8:
    myMapper->writeCPU(0x0547 + x, 0x06);
    opINC(0x0529 + x, 1);
    if (y == 0x44) {
        goto L_00D0C5;
    }
    do {
        popAddress();
        return;
    L_00D0C5:
        a = myMapper->readCPU(0x05BB);
        setLoadFlag(a);
    } while (flgN);
    opDEC(0x008E, 1);
    jump(0x91CA);
    return;
}

void game::SUB_00D0D0() {
    myMapper->writeCPU(0x0529 + x, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04B1 + x));
    myMapper->writeCPU(0x03C1 + x, a);
    if (a < 0xF0) {
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            if (myMapper->readCPU(0x04B1 + x) == 0x08) {
                goto L_00D0F3;
            }
            opINC(0x04B1 + x, 1);
        }
    L_00D0F3:
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_00D0FA() {
    a = 0x13;
    pushAddress(0x90FE);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x90FE)) return;
    a = 0x09;
    y = 0x05;
    myMapper->writeCPU(0x04ED + x, a);
    myMapper->writeCPU(0x0565 + x, 0xDC);
    a = y;
    myMapper->writeCPU(0x03FD + x, a);
    opAND(0x7F);
    myMapper->writeCPU(0x04CF + x, a);
    myMapper->writeCPU(0x041B + x, 0x07);
    myMapper->writeCPU(0x0475 + x, 0x07);
    myMapper->writeCPU(0x050B + x, 0x00);
    popAddress();
}

void game::SUB_00D124() {
    y = 0x05;
    myMapper->writeCPU(0x0659, y);
    pushAddress(0x912B);
    jump(0x954A);
    if (handleReturnAddress(poppedEntry.value, 0x912B)) return;
    if (!flgN) {
        myMapper->writeCPU(0x05BC, 0x01);
        a = x;
        y = a;
        x = 0x00;
        jump(0x8F8A);
        return;
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        opDEC(0x0565 + x, 1);
        if (flgZ) {
            goto L_00D14B;
        }
    }
    opDEC(0x04B1 + x, 1);
    if (!flgV) {
        goto L_00D157;
    }
    popAddress();
    return;
L_00D14B:
    myMapper->writeCPU(0x04B1 + x, 0xFE);
    a = x;
    y = a;
    x = 0x00;
    jump(0x8F97);
    return;
L_00D157:
    a = myMapper->readCPU(0x003F);
    opLSR_A(2);
    opAND(0x01);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
}

void game::SUB_00D164() {
    a = myMapper->readCPU(0x04B1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x03C1 + x));
    if (a < 0xF4) {
        myMapper->writeCPU(0x03C1 + x, a);
        if (myMapper->readCPU(0x0457 + x) == 0) {
            goto L_00D17D;
        }
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
    return;
L_00D17D:
    y = 0x00;
    a = myMapper->readCPU(0x0493 + x);
    setLoadFlag(a);
    if (flgN) {
        opDEY(1);
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0385 + x));
    myMapper->writeCPU(0x0385 + x, a);
    myMapper->writeCPU(0x0024, a);
    a = y;
    opADC(myMapper->readCPU(0x03A3 + x));
    myMapper->writeCPU(0x03A3 + x, a);
    myMapper->writeCPU(0x0025, a);
    if (myMapper->readCPU(0x05BD) == 0) {
        myMapper->writeCPU(0x0001, 0x38);
        a = 0x20;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x91A8);
        jump(0x954A);
        if (handleReturnAddress(poppedEntry.value, 0x91A8)) return;
        if (!flgN) {
            goto L_00D1AC;
        }
    }
    popAddress();
    return;
L_00D1AC:
    a = myMapper->readCPU(0x0475 + x);
    a = myMapper->readCPU(0x041B + x);
    if (a != 0x01) {
        goto L_00D1BE;
    }
    pushAddress(0x91B8);
    jump(0x9336);
    if (handleReturnAddress(poppedEntry.value, 0x91B8)) return;
    a = 0xFE;
    goto L_00D1C5;
L_00D1BE:
    myMapper->writeCPU(0x0475 + x, 0x00);
    a = 0xFE;
L_00D1C5:
    flgC = false;
    opADC(myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x008E, a);
    SUB_00D1CA();
    return;
}

void game::SUB_00D1CA() {
    if (myMapper->readCPU(0x04B1 + x) == 0) {
        goto L_00D1D7;
    }
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    myMapper->writeCPU(0x05A4, a);
L_00D1D7:
    x = 0x1C;
    if (myMapper->readCPU(0x05C9) == 0) {
        goto L_00D1E0;
    }
    x = 0x20;
L_00D1E0:
    a = myMapper->readCPU(0x04ED + x);
    jump(0x89E3);
    return;
}

void game::SUB_00D1E6() {
    if (myMapper->readCPU(0x0457 + x) == 0) {
        goto L_00D1F1;
    }
    while (true) {
        do {
            myMapper->writeCPU(0x0475 + x, 0x00);
            popAddress();
            return;
        L_00D1F1:
            y = 0x00;
            a = myMapper->readCPU(0x0493 + x);
            setLoadFlag(a);
            if (!flgN) {
                goto L_00D1F9;
            }
            opDEY(1);
        L_00D1F9:
            flgC = false;
            opADC(myMapper->readCPU(0x0385 + x));
            myMapper->writeCPU(0x0385 + x, a);
            myMapper->writeCPU(0x0024, a);
            a = y;
            opADC(myMapper->readCPU(0x03A3 + x));
            myMapper->writeCPU(0x03A3 + x, a);
            myMapper->writeCPU(0x0025, a);
            a = myMapper->readCPU(0x04B1 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x03C1 + x));
        } while (a >= 0xF4);
        myMapper->writeCPU(0x03C1 + x, a);
        myMapper->writeCPU(0x0001, 0x32);
        a = 0x18;
        myMapper->writeCPU(0x0002, a);
        y = 0x01;
        pushAddress(0x9225);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x9225)) return;
        if (!flgN) {
            goto L_00D260;
        }
        y = 0x02;
        pushAddress(0x922C);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x922C)) return;
        if (!flgN) {
            goto L_00D260;
        }
        y = 0x06;
        pushAddress(0x9233);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x9233)) return;
        if (!flgN) {
            goto L_00D260;
        }
        y = 0x07;
        pushAddress(0x923A);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x923A)) return;
        if (!flgN) {
            goto L_00D260;
        }
        a = 0x20;
        myMapper->writeCPU(0x0001, a);
        myMapper->writeCPU(0x0002, a);
        y = 0x0E;
        pushAddress(0x9247);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x9247)) return;
        if (!flgN) {
            goto L_00D260;
        }
        y = 0x0F;
        pushAddress(0x924E);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x924E)) return;
        if (!flgN) {
            goto L_00D260;
        }
        y = 0x10;
        pushAddress(0x9255);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x9255)) return;
        if (!flgN) {
            goto L_00D260;
        }
        y = 0x11;
        pushAddress(0x925C);
        jump(0x9288);
        if (handleReturnAddress(poppedEntry.value, 0x925C)) return;
        if (!flgN) {
            goto L_00D260;
        }
        do {
            popAddress();
            return;
        L_00D260:
            a = 0x0D;
            pushAddress(0x9264);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0x9264)) return;
            a = myMapper->readCPU(0x050B + y);
            flgC = true;
            opSBC(myMapper->readCPU(0x0594));
            myMapper->writeCPU(0x050B + y, a);
            if (!flgN) {
                goto L_00D277;
            }
            pushAddress(0x9273);
            jump(0x8F8A);
            if (handleReturnAddress(poppedEntry.value, 0x9273)) return;
            x = myMapper->readCPU(0x05AC);
        L_00D277:
            a = myMapper->readCPU(0x0595);
        } while (a == 0x05);
        if (a == 0x04) {
            goto L_00D285;
        }
    }
L_00D285:
    jump(0x9340);
    return;
}

void game::SUB_00D288() {
    a = myMapper->readCPU(0x0475 + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x05) {
            goto L_00D2C8;
        }
        if (myMapper->readCPU(0x03FD + y) != 0xFF) {
            if (myMapper->readCPU(0x04ED + y) & 0x80) {
                goto L_00D2C8;
            }
            a = myMapper->readCPU(0x03C1 + x);
            flgC = false;
            opADC(0x08);
            flgC = true;
            opSBC(myMapper->readCPU(0x03C1 + y));
            if (flgC) {
                if (a >= myMapper->readCPU(0x0001)) {
                    goto L_00D2C8;
                }
                a = myMapper->readCPU(0x0024);
                flgC = false;
                opADC(0x08);
                flgC = true;
                opSBC(myMapper->readCPU(0x0385 + y));
                myMapper->writeCPU(0x0000, a);
                a = myMapper->readCPU(0x0025);
                opSBC(myMapper->readCPU(0x03A3 + y));
                if (flgZ) {
                    if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x0002)) {
                        goto L_00D2C8;
                    }
                    a = 0x00;
                    setLoadFlag(a);
                    popAddress();
                    return;
                }
            }
        }
    }
L_00D2C8:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00D2CB() {
    myMapper->writeCPU(0x03FD + x, myMapper->readCPU(0x04CF + x));
    a = 0x02;
    myMapper->writeCPU(0x041B + x, a);
    y = 0x02;
    pushAddress(0x92DA);
    jump(0x9554);
    if (handleReturnAddress(poppedEntry.value, 0x92DA)) return;
    if (flgN) {
        goto L_00D2F9;
    }
    y = myMapper->readCPU(0x03FD + x);
    if (y == 0x00) {
        goto L_00D32A;
    }
    myMapper->writeCPU(0x0475 + x, 0x00);
    if (y == 0x08) {
        goto L_00D30C;
    }
    if (y == 0x01) {
        goto L_00D313;
    }
    if (y == 0x06) {
        goto L_00D300;
    }
    if (y == 0x07) {
        goto L_00D2FA;
    }
L_00D2F9:
    popAddress();
    return;
L_00D2FA:
    myMapper->writeCPU(0x05BD, 0x06);
    popAddress();
    return;
L_00D300:
    a = myMapper->readCPU(0x008E);
    flgC = false;
    opADC(0x0A);
    myMapper->writeCPU(0x008E, a);
    a = 0x11;
    jump(0xEA1B);
    return;
L_00D30C:
    a = 0x05;
    a = 0x0E;
    jump(0xEA1B);
    return;
L_00D313:
    y = myMapper->readCPU(0x05BE);
    myMapper->writeCPU(0x0595, y);
    myMapper->writeCPU(0x0594, myMapper->readCPU(0xEA43 + y));
    myMapper->writeCPU(0x0596, myMapper->readCPU(0xEA49 + y));
    a = 0x12;
    jump(0xEA1B);
    return;
L_00D32A:
    a = myMapper->readCPU(0x0081);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x0081, a);
    opINC(0x0090, 1);
    jump(0x9336);
    return;
}

void game::SUB_00D336() {
    myMapper->writeCPU(0x041B + x, 0x02);
    a = 0x02;
    jump(0x9347);
    return;
}

void game::SUB_00D340() {
    myMapper->writeCPU(0x041B + x, 0x00);
    a = 0x02;
    SUB_00D347();
    return;
}

void game::SUB_00D347() {
    myMapper->writeCPU(0x0565 + x, a);
    myMapper->writeCPU(0x04CF + x, 0x00);
    myMapper->writeCPU(0x0475 + x, 0x03);
    myMapper->writeCPU(0x04ED + x, 0xFF);
    a = 0x0B;
    pushAddress(0x935D);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0x935D)) return;
    SUB_00D35E();
    return;
}

void game::SUB_00D35E() {
    a = myMapper->readCPU(0x04CF + x);
    opLSR_A(2);
    opINC(0x04CF + x, 1);
    if (a == 0x04) {
        goto L_00D372;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x0565 + x));
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_00D372:
    myMapper->writeCPU(0x0475 + x, 0x00);
    popAddress();
}

void game::SUB_00D378() {
    pushAddress(0x937A);
    jump(0x93DC);
    if (handleReturnAddress(poppedEntry.value, 0x937A)) return;
    if (!flgN) {
        a = 0x06;
        pushAddress(0x9381);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0x9381)) return;
        myMapper->writeCPU(0x0475 + y, 0x04);
        a = myMapper->readCPU(0x03C1 + x);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x03C1 + y, a);
        a = 0x00;
        myMapper->writeCPU(0x03FD + y, a);
        myMapper->writeCPU(0x04B1 + y, a);
        myMapper->writeCPU(0x041B + y, a);
        myMapper->writeCPU(0x0457 + y, a);
        myMapper->writeCPU(0x03DF + y, a);
        myMapper->writeCPU(0x0000, myMapper->readCPU(0x0385 + x));
        myMapper->writeCPU(0x0001, myMapper->readCPU(0x03A3 + x));
        myMapper->writeCPU(0x0493 + y, 0x03);
        if (!(myMapper->readCPU(0x03FD + x) & 0x80)) {
            goto L_00D3CC;
        }
        myMapper->writeCPU(0x0493 + y, 0xFD);
        a = myMapper->readCPU(0x0000);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x0001);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
        goto L_00D3DB;
    L_00D3CC:
        a = myMapper->readCPU(0x0000);
        flgC = false;
        opADC(0x18);
        myMapper->writeCPU(0x0385 + y, a);
        a = myMapper->readCPU(0x0001);
        opADC(0x00);
        myMapper->writeCPU(0x03A3 + y, a);
    }
L_00D3DB:
    popAddress();
}

void game::SUB_00D3DC() {
    y = 0x08;
    if (myMapper->readCPU(0x0475 + y) != 0) {
        y = 0x09;
        if (myMapper->readCPU(0x0475 + y) == 0) {
            goto L_00D3ED;
        }
        a = 0xFF;
        setLoadFlag(a);
        popAddress();
        return;
    }
L_00D3ED:
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00D3F0() {
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
        if (a != myMapper->readCPU(0x00A0)) {
            goto L_00D3FE;
        }
        pushAddress(0x93FA);
        jump(0x9409);
        if (handleReturnAddress(poppedEntry.value, 0x93FA)) return;
    }
L_00D3FE:
    flgC = false;
    a = y;
    opADC(myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x000E, a);
    if (!flgC) {
        goto L_00D408;
    }
    opINC(0x000F, 1);
L_00D408:
    popAddress();
}

void game::SUB_00D409() {
    opINY(1);
    x = myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y);
    a = myMapper->readCPU(0x0475 + x);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_00D44A;
    }
    a = myMapper->readCPU(SCROLL_FINE);
    opAND(0xF8);
    myMapper->writeCPU(0x0385 + x, a);
    a = myMapper->readCPU(SCROLL_LARGE);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x03A3 + x, a);
    opINY(1);
    myMapper->writeCPU(0x03C1 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    a = 0x00;
    myMapper->writeCPU(0x03DF + x, a);
    myMapper->writeCPU(0x0493 + x, a);
    myMapper->writeCPU(0x0529 + x, a);
    myMapper->writeCPU(0x0565 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0475 + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x04CF + x, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = 0xFF;
    myMapper->writeCPU(0x03FD + x, a);
    popAddress();
    return;
L_00D44A:
    opINY(4);
    popAddress();
}

void game::SUB_00D54A() {
    if (myMapper->readCPU(0x05D2) != 0) {
        jump(0x95BD);
        return;
    }
    if (myMapper->readCPU(0x05BD) != 0) {
        jump(0x95BD);
        return;
    }
    SUB_00D554();
    return;
}

void game::SUB_00D554() {
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03DF));
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(myMapper->readCPU(0x05C9));
    myMapper->writeCPU(0x0000, a);
    if (flgC) {
        opINC(0x0001, 1);
    }
    myMapper->writeCPU(0x0002, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x95CB + y));
    if (flgC) {
        opINC(0x0002, 1);
    }
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0002);
    opSBC(myMapper->readCPU(0x0001));
    if (!flgZ) {
        jump(0x95BD);
        return;
    }
    if (myMapper->readCPU(0x05C9) != 0) {
        a = myMapper->readCPU(0x0000);
        if (a >= myMapper->readCPU(0x95EC + y)) {
            jump(0x95BD);
            return;
        }
    }
    else {
        if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0x95E1 + y)) {
            jump(0x95BD);
            return;
        }
    }
    myMapper->writeCPU(0x0025, myMapper->readCPU(0x03A3 + x));
    a = myMapper->readCPU(0x0385 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x95C0 + y));
    if (!flgC) {
        goto L_00D5A6;
    }
    opINC(0x0025, 1);
L_00D5A6:
    flgC = true;
    opSBC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opSBC(myMapper->readCPU(0x03A3));
    if (!flgZ) {
        jump(0x95BD);
        return;
    }
    if (myMapper->readCPU(0x0024) >= myMapper->readCPU(0x95D6 + y)) {
        jump(0x95BD);
        return;
    }
    a = 0x00;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00D5BD() {
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_00D5F7() {
    if (myMapper->readCPU(0x00A0) != myMapper->readCPU(0x05BA)) {
        goto L_00D603;
    }
    myMapper->writeCPU(0x05B5, 0x00);
L_00D603:
    if (myMapper->readCPU(0x05B5) == 0) {
        y = 0x03;
        a = myMapper->readCPU(0x00A0);
        x = 0x03;
        do {
            if (a == myMapper->readCPU(0x9745 + y)) {
                goto L_00D618;
            }
            opDEY(1);
            opDEX(1);
        } while (!flgN);
        popAddress();
        return;
    L_00D618:
        myMapper->writeCPU(0x05B0, a);
        flgC = false;
        opADC(0x09);
        myMapper->writeCPU(0x05BA, a);
        myMapper->writeCPU(0x05B3, myMapper->readCPU(0x0371));
        myMapper->writeCPU(0x05B4, myMapper->readCPU(0x0370));
        myMapper->writeCPU(0x05B1, myMapper->readCPU(0x0301));
        myMapper->writeCPU(0x05B2, myMapper->readCPU(0x0300));
        x = myMapper->readCPU(0x9749 + y);
        setLoadFlag(x);
        myMapper->writeCPU(0x05B9, x);
        if (!flgZ) {
            do {
                a = myMapper->readCPU(0x05B3);
                flgC = false;
                opADC(0x08);
                myMapper->writeCPU(0x05B3, a);
                a = myMapper->readCPU(0x05B1);
                opADC(0x80);
                myMapper->writeCPU(0x05B1, a);
                a = myMapper->readCPU(0x05B2);
                opADC(0x00);
                myMapper->writeCPU(0x05B2, a);
                opDEX(1);
            } while (!flgZ);
        }
        myMapper->writeCPU(0x05B5, 0xFF);
        a = 0x00;
        myMapper->writeCPU(0x05B7, a);
        myMapper->writeCPU(0x05B8, a);
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x05B7) == 0) {
        opINC(0x05B8, 1);
        a = myMapper->readCPU(0x05B8);
        if (a != 0x20) {
            if (a == 0x60) {
                goto L_00D683;
            }
            if (a != 0xEC) {
                popAddress();
                return;
            }
        }
    L_00D683:
        myMapper->writeCPU(0x05B7, 0xFF);
        myMapper->writeCPU(0x05B6, 0x00);
    }
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x03A3));
    a = myMapper->readCPU(0x0385);
    flgC = false;
    opADC(0x10);
    if (flgC) {
        opINC(0x0000, 1);
    }
    opLSR_M(0x0000, 1);
    opROR_A(1);
    opLSR_M(0x0000, 1);
    opROR_A(1);
    opLSR_M(0x0000, 1);
    opROR_A(1);
    opLSR_M(0x0000, 1);
    opROR_A(1);
    opLSR_M(0x0000, 1);
    opROR_A(1);
    if (a == myMapper->readCPU(0x05B0)) {
        a = myMapper->readCPU(0x05B9);
        flgC = false;
        opADC(0x01);
        opASL_A(5);
        if (a < myMapper->readCPU(0x03C1)) {
            a = myMapper->readCPU(0x003F);
            opAND(0x07);
            if (flgZ) {
                opDEC(0x008E, 1);
            }
        }
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x05B1));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x05B3));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x05B4));
    y = 0x22;
    x = myMapper->readCPU(0x05B6);
    setLoadFlag(x);
    if (!flgZ) {
        if (x == 0x1F) {
            goto L_00D6F7;
        }
        y = 0x00;
        if (x != 0x20) {
            y = 0x00;
            a = myMapper->readCPU(0x003F);
            opAND(0x01);
            if (flgZ) {
                y = 0x21;
            }
        }
    }
L_00D6F7:
    a = y;
    x = 0x31;
    pushAddress(0x96FC);
    jump(0xE3C9);
    if (handleReturnAddress(poppedEntry.value, 0x96FC)) return;
    x = 0x00;
    a = myMapper->readCPU(0x05B6);
    setLoadFlag(a);
    if (!flgZ) {
        if (a >= 0x1F) {
            goto L_00D710;
        }
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            x = 0x22;
        }
    }
L_00D710:
    flgC = false;
    a = myMapper->readCPU(0x05B3);
    opADC(0x08);
    myMapper->writeCPU(0x0009, a);
    flgC = false;
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x05B2));
    a = myMapper->readCPU(0x05B1);
    opADC(0x80);
    myMapper->writeCPU(0x0005, a);
    if (flgC) {
        opINC(0x0006, 1);
    }
    a = x;
    x = 0x4C;
    pushAddress(0x972E);
    jump(0xE3C9);
    if (handleReturnAddress(poppedEntry.value, 0x972E)) return;
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        a = myMapper->readCPU(0x05B6);
        opINC(0x05B6, 1);
        if (a != 0x20) {
            goto L_00D744;
        }
        a = 0x00;
        myMapper->writeCPU(0x05B7, a);
    }
L_00D744:
    popAddress();
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
        myMapper->writeCPU(APU_P1REG0 + x, a);
        opDEX(1);
    } while (!flgN);
    a = 0x0F;
    myMapper->writeCPU(APU_STATUS, a);
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
        myMapper->writeCPU(APU_P1REG0 + y, a);
        myMapper->writeCPU(APU_P1REG1 + y, a);
        myMapper->writeCPU(APU_P1REG2 + y, a);
        myMapper->writeCPU(APU_P1REG3 + y, a);
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
                    myMapper->writeCPU(APU_P1REG2 + y, myMapper->readCPU(0x0773 + x));
                    a = myMapper->readCPU(0x06CA);
                    if (x == 0x02) {
                        opORA(myMapper->readCPU(0x0723 + x));
                    }
                    myMapper->writeCPU(APU_P1REG3 + y, a);
                    if (x == 0x02) {
                        myMapper->writeCPU(APU_TRIANGREG0, myMapper->readCPU(0x0727 + x));
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
                myMapper->writeCPU(APU_P1REG0 + y, a);
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
    myMapper->writeCPU(APU_P1REG2 + y, myMapper->readCPU(0x0773 + x));
    a = myMapper->readCPU(0x06CA);
    if (x == 0x7A) {
        opORA(myMapper->readCPU(0x079D));
    }
    myMapper->writeCPU(APU_P1REG3 + y, a);
    if (x == 0x7A) {
        myMapper->writeCPU(APU_TRIANGREG0, myMapper->readCPU(0x07A1));
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
    myMapper->writeCPU(APU_P1REG0 + y, a);
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
            myMapper->writeCPU(APU_TRIANGREG0, a);
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
    myMapper->writeCPU(APU_P1REG0 + y, a);
    myMapper->writeCPU(APU_P1REG1 + y, a);
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
        myMapper->writeCPU(APU_P1REG2 + y, a);
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
        myMapper->writeCPU(APU_P1REG1 + y, a);
        opPLA();
        x = a;
        myMapper->writeCPU(APU_P1REG2 + y, myMapper->readCPU(0x860F + x));
        myMapper->writeCPU(APU_P1REG3 + y, myMapper->readCPU(0x8610 + x));
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
    myMapper->writeCPU(APU_P1REG1 + y, a);
    myMapper->writeCPU(APU_P1REG0 + y, a);
    myMapper->writeCPU(APU_P1REG2 + y, a);
    myMapper->writeCPU(APU_P1REG3 + y, a);
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
    myMapper->writeCPU(APU_P1REG0 + x, myMapper->readCPU(myMapper->readCPU(0x00F0) + (myMapper->readCPU((0x00F0 + 1) & 0x00ff) << 8) + y));
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

void game::SUB_014000() {
    y = myMapper->readCPU(0x0051);
    a = myMapper->readCPU(0x0059 + y);
    if (a != 0x0D) {
        if (a == 0x14) {
            goto L_014016;
        }
        if (a == 0x15) {
            goto L_014016;
        }
        if (a == 0x18) {
            goto L_014019;
        }
        popAddress();
        return;
    L_014016:
        jump(0xB453);
        return;
    L_014019:
        a = 0xFF;
        myMapper->writeCPU(0x0660, a);
        jump(0x9484);
        return;
    }
    jump(0xA437);
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x19;
    pushAddress(0x94B9);
    SUB_01FFAA_SwitchCHRBank1();
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
    myMapper->writeCPU(SCROLL_FINE, a);
    myMapper->writeCPU(SCROLL_LARGE, a);
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
            //do {
            //    opBIT(myMapper->readCPU(PPU_STATUS));
            //} while (!flgV);
            wait(2);
            x = 0x0E;
            do {
                opDEX(1);
            } while (!flgZ);
            a = 0x00;
            myMapper->writeCPU(PPU_SCROLL, a);
            myMapper->writeCPU(PPU_SCROLL, a);
            myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0040));
            wait(3);
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
    myMapper->writeCPU(SCROLL_FINE, a);
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    myMapper->writeCPU(SCROLL_LARGE, a);
    if (flgN) {
        a = 0x00;
        myMapper->writeCPU(SCROLL_FINE, a);
        myMapper->writeCPU(SCROLL_LARGE, a);
    }
    if (myMapper->readCPU(SCROLL_LARGE) == 0) {
        goto L_0159A7;
    }
    myMapper->writeCPU(SCROLL_LARGE, 0x01);
    myMapper->writeCPU(SCROLL_FINE, 0x00);
L_0159A7:
    popAddress();
}

void game::SUB_0159A8() {
    myMapper->writeCPU(PPU_SCROLL, myMapper->readCPU(SCROLL_FINE));
    myMapper->writeCPU(PPU_SCROLL, 0x00);
    a = myMapper->readCPU(0x0040);
    x = myMapper->readCPU(SCROLL_LARGE);
    setLoadFlag(x);
    if (flgZ) {
        goto L_0159BE;
    }
    opAND(0xFE);
    opORA(0x01);
L_0159BE:
    myMapper->writeCPU(PPU_CTRL, a);
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

void game::SUB_016437() {
    a = 0x09;
    myMapper->writeCPU(0x009F, a);
    myMapper->writeCPU(0x00A0, a);
    a = 0x00;
    pushAddress(0xA441);
    jump(0xA489);
    if (handleReturnAddress(poppedEntry.value, 0xA441)) return;
    if (!(myMapper->readCPU(0x065C) & 0x80)) {
        a = 0x0C;
        pushAddress(0xA44B);
        jump(0xF0CE);
        if (handleReturnAddress(poppedEntry.value, 0xA44B)) return;
        pushAddress(0xA44E);
        jump(0xA477);
        if (handleReturnAddress(poppedEntry.value, 0xA44E)) return;
        a = 0x01;
        pushAddress(0xA453);
        jump(0xA489);
        if (handleReturnAddress(poppedEntry.value, 0xA453)) return;
        if (!(myMapper->readCPU(0x065C) & 0x80)) {
            a = 0x0D;
            pushAddress(0xA45D);
            jump(0xF0CE);
            if (handleReturnAddress(poppedEntry.value, 0xA45D)) return;
            pushAddress(0xA460);
            jump(0xA477);
            if (handleReturnAddress(poppedEntry.value, 0xA460)) return;
            a = 0x02;
            pushAddress(0xA465);
            jump(0xA489);
            if (handleReturnAddress(poppedEntry.value, 0xA465)) return;
            if (myMapper->readCPU(0x065C) & 0x80) {
                goto L_016471;
            }
            myMapper->writeCPU(0x05AC, 0xFF);
            popAddress();
            return;
        }
    }
L_016471:
    myMapper->writeCPU(0x05AC, 0x01);
    popAddress();
}

void game::SUB_016477() {
    a = myMapper->readCPU(0x009F);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x009F, a);
    if (a < 0x0A) {
        goto L_016488;
    }
    a = 0x09;
    myMapper->writeCPU(0x009F, a);
    myMapper->writeCPU(0x00A0, a);
L_016488:
    popAddress();
}

void game::SUB_016489() {
    myMapper->writeCPU(0x00A7, a);
    pushAddress(0xA48D);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xA48D)) return;
    pushAddress(0xA490);
    jump(0xC9F6);
    if (handleReturnAddress(poppedEntry.value, 0xA490)) return;
    pushAddress(0xA493);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xA493)) return;
    a = 0x08;
    pushAddress(0xA498);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xA498)) return;
    myMapper->writeCPU(0x0005, 0x44);
    a = 0x88;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xA4A7);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xA4A7)) return;
    myMapper->writeCPU(0x0005, 0x44);
    a = 0x8C;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x24;
    pushAddress(0xA4B6);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xA4B6)) return;
    a = 0x14;
    pushAddress(0xA4BB);
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x11;
    pushAddress(0xA4C0);
    SUB_01FFAA_SwitchCHRBank1();
    myMapper->writeCPU(0x000C, 0x44);
    a = 0x90;
    myMapper->writeCPU(0x000D, a);
    pushAddress(0xA4CB);
    jump(0xDD26);
    if (handleReturnAddress(poppedEntry.value, 0xA4CB)) return;
    pushAddress(0xA4CE);
    jump(0xA4D5);
    if (handleReturnAddress(poppedEntry.value, 0xA4CE)) return;
    pushAddress(0xA4D1);
    jump(0xDCFD);
    if (handleReturnAddress(poppedEntry.value, 0xA4D1)) return;
    jump(0xA5ED);
    return;
}

void game::SUB_0164D5() {
    myMapper->writeCPU(0x0203, 0x00);
    myMapper->writeCPU(0x0200, 0xAF);
    myMapper->writeCPU(0x0201, 0xFF);
    myMapper->writeCPU(0x0202, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x05BD, a);
    myMapper->writeCPU(0x0586, a);
    myMapper->writeCPU(0x0587, 0x1D);
    myMapper->writeCPU(0x0588, 0x1D);
    x = 0x0F;
    do {
        myMapper->writeCPU((0x0014 + x) & 0x00ff, myMapper->readCPU(0xA567 + x));
        opDEX(1);
    } while (!flgN);
    a = 0x00;
    myMapper->writeCPU(SCROLL_FINE, a);
    myMapper->writeCPU(SCROLL_LARGE, a);
    myMapper->writeCPU(0x0091, a);
    myMapper->writeCPU(0x0092, a);
    myMapper->writeCPU(0x00D0, a);
    myMapper->writeCPU(0x00D1, a);
    myMapper->writeCPU(0x0093, a);
    myMapper->writeCPU(0x0095, a);
    myMapper->writeCPU(0x0096, a);
    myMapper->writeCPU(0x009C, a);
    myMapper->writeCPU(0x065C, a);
    myMapper->writeCPU(0x00A4, a);
    myMapper->writeCPU(0x00A5, a);
    myMapper->writeCPU(0x058C, a);
    myMapper->writeCPU(0x009D, a);
    myMapper->writeCPU(0x0385, 0x30);
    myMapper->writeCPU(0x03A3, 0x00);
    myMapper->writeCPU(0x03C1, 0x80);
    myMapper->writeCPU(0x03DF, 0x00);
    myMapper->writeCPU(0x03FD, 0x00);
    myMapper->writeCPU(0x041B, 0x06);
    myMapper->writeCPU(0x0475, 0x01);
    myMapper->writeCPU(0x0097, 0xCF);
    myMapper->writeCPU(0x0098, 0x00);
    myMapper->writeCPU(0x0099, 0x48);
    myMapper->writeCPU(0x009A, 0x00);
    myMapper->writeCPU(0x009B, 0x00);
    a = 0x09;
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x00A2, a);
    popAddress();
}

void game::SUB_0165ED() {
    while (true) {
        pushAddress(0xA5EF);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xA5EF)) return;
        a = 0x14;
        pushAddress(0xA5F4);
        SUB_01FFD2_SwitchCHRBank0();
        pushAddress(0xA5F7);
        jump(0xAB9D);
        if (handleReturnAddress(poppedEntry.value, 0xA5F7)) return;
        myMapper->writeCPU(0x008F, 0x00);
        a = myMapper->readCPU(0x00A4);
        if (a == 0x01) {
            a = 0x06;
            pushAddress(0xA606);
            SUB_01FFAA_SwitchCHRBank1();
            opINC(0x00A4, 1);
        }
        pushAddress(0xA60B);
        jump(0xDBDF);
        if (handleReturnAddress(poppedEntry.value, 0xA60B)) return;
        a = myMapper->readCPU(0x059C);
        setLoadFlag(a);
        if (!flgZ) {
            opCMP(myMapper->readCPU(0x004C), 0x10);
            if (!flgZ) {
                goto L_016622;
            }
            a = 0xFF;
            myMapper->writeCPU(0x065C, a);
        }
        else {
            pushAddress(0xA67A);
            jump(0x95A0);
            if (handleReturnAddress(poppedEntry.value, 0xA67A)) return;
        }
    L_016622:
        a = myMapper->readCPU(0x058C);
        setLoadFlag(a);
        if (flgZ) {
            pushAddress(0xA629);
            jump(0xA73E);
            if (handleReturnAddress(poppedEntry.value, 0xA629)) return;
            pushAddress(0xA62C);
            jump(0xA679);
            if (handleReturnAddress(poppedEntry.value, 0xA62C)) return;
            pushAddress(0xA62F);
            jump(0xA699);
            if (handleReturnAddress(poppedEntry.value, 0xA62F)) return;
            pushAddress(0xA632);
            jump(0xA6B4);
            if (handleReturnAddress(poppedEntry.value, 0xA632)) return;
            a = myMapper->readCPU(0x00A4);
            opORA(myMapper->readCPU(0x00A5));
            if (!flgZ) {
                goto L_016648;
            }
            pushAddress(0xA63B);
            jump(0xABCF);
            if (handleReturnAddress(poppedEntry.value, 0xA63B)) return;
            pushAddress(0xA63E);
            jump(0xA86A);
            if (handleReturnAddress(poppedEntry.value, 0xA63E)) return;
            pushAddress(0xA641);
            jump(0xAADC);
            if (handleReturnAddress(poppedEntry.value, 0xA641)) return;
            pushAddress(0xA644);
            jump(0xAC5E);
            if (handleReturnAddress(poppedEntry.value, 0xA644)) return;
            pushAddress(0xA647);
            jump(0xAA1B);
            if (handleReturnAddress(poppedEntry.value, 0xA647)) return;
        }
    L_016648:
        pushAddress(0xA64A);
        jump(0xCA15);
        if (handleReturnAddress(poppedEntry.value, 0xA64A)) return;
        pushAddress(0xA64D);
        jump(0xABB5);
        if (handleReturnAddress(poppedEntry.value, 0xA64D)) return;
        pushAddress(0xA650);
        jump(0xA7A0);
        if (handleReturnAddress(poppedEntry.value, 0xA650)) return;
        pushAddress(0xA653);
        jump(0xA7D1);
        if (handleReturnAddress(poppedEntry.value, 0xA653)) return;
        //do {
        //    opBIT(myMapper->readCPU(PPU_STATUS));
        //} while (!flgV);
        wait(2);
        a = 0x00;
        myMapper->writeCPU(PPU_SCROLL, a);
        myMapper->writeCPU(PPU_SCROLL, a);
        x = 0x08;
        do {
            opDEX(1);
        } while (!flgZ);
        a = 0x18;
        pushAddress(0xA66A);
        SUB_01FFD2_SwitchCHRBank0();
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0040));
        wait(3);
        a = myMapper->readCPU(0x065C);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_016678;
        }
    }
L_016678:
    popAddress();
}

void game::SUB_016679() {
    a = myMapper->readCPU(0x009F);
    opORA(myMapper->readCPU(0x00A0));
    opORA(myMapper->readCPU(0x0093));
    opORA(myMapper->readCPU(0x00A4));
    if (!flgZ) {
        goto L_016698;
    }
    a = 0x16;
    pushAddress(0xA687);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xA687)) return;
    myMapper->writeCPU(0x00A4, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x00A6, a);
    x = 0x07;
    do {
        myMapper->writeCPU(0x0476 + x, a);
        opDEX(1);
    } while (!flgN);
L_016698:
    popAddress();
}

void game::SUB_016699() {
    a = myMapper->readCPU(0x00A1);
    opORA(myMapper->readCPU(0x00A2));
    opORA(myMapper->readCPU(0x00A5));
    opORA(myMapper->readCPU(0x0093));
    if (!flgZ) {
        goto L_0166B3;
    }
    myMapper->writeCPU(0x00A5, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x00A6, a);
    x = 0x07;
    do {
        myMapper->writeCPU(0x0476 + x, a);
        opDEX(1);
    } while (!flgN);
L_0166B3:
    popAddress();
}

void game::SUB_0166B4() {
    a = myMapper->readCPU(0x00A5);
    setLoadFlag(a);
    if (flgZ) {
    }
    else {
        y = 0x00;
        x = 0x0F;
        do {
            if (myMapper->readCPU(0x047A + x) != 0) {
                goto L_0166FA;
            }
            opINC(0x0081, 1);
            a = 0x01;
            myMapper->writeCPU(0x047A + x, a);
            pushAddress(0xA6CD);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0xA6CD)) return;
            opAND(0x3F);
            flgC = false;
            opADC(myMapper->readCPU(0x0097));
            myMapper->writeCPU(0x038A + x, a);
            a = myMapper->readCPU(0x0098);
            opADC(0x00);
            myMapper->writeCPU(0x03A8 + x, a);
            pushAddress(0xA6DF);
            jump(0xDCD8);
            if (handleReturnAddress(poppedEntry.value, 0xA6DF)) return;
            opAND(0x3F);
            flgC = false;
            opADC(myMapper->readCPU(0x0099));
            myMapper->writeCPU(0x03C6 + x, a);
            a = 0x0B;
            pushAddress(0xA6EC);
            jump(0xEA16);
            if (handleReturnAddress(poppedEntry.value, 0xA6EC)) return;
            a = 0x00;
            myMapper->writeCPU(0x03E4 + x, a);
            myMapper->writeCPU(0x04D4 + x, a);
            opINY(1);
            opCMP(y, 0x02);
            if (flgZ) {
                goto L_0166FD;
            }
        L_0166FA:
            opDEX(1);
        } while (!flgN);
    L_0166FD:
        x = 0x0F;
        do {
            if (myMapper->readCPU(0x047A + x) == 0) {
                goto L_016727;
            }
            myMapper->writeCPU(0x0420 + x, 0x02);
            a = myMapper->readCPU(0x04D4 + x);
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x0402 + x, a);
            a = myMapper->readCPU(0x003F);
            opAND(0x03);
            if (flgZ) {
                opINC(0x04D4 + x, 1);
                if (myMapper->readCPU(0x04D4 + x) != 0x04) {
                    goto L_016727;
                }
                myMapper->writeCPU(0x047A + x, 0x00);
            }
        L_016727:
            opDEX(1);
        } while (!flgN);
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            opINC(0x0097, 1);
            if (myMapper->readCPU(0x0097) != 0xFF) {
                goto L_01673D;
            }
            myMapper->writeCPU(0x065C, 0x01);
        }
    }
L_01673D:
    popAddress();
}

void game::SUB_01673E() {
    a = myMapper->readCPU(0x00A4);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x00A6);
        opCMP(a, 0x07);
        if (flgN) {
            flgC = false;
            opADC(0x18);
            myMapper->writeCPU(0x03FD, a);
        }
        a = myMapper->readCPU(0x003F);
        opAND(0x07);
        if (flgZ) {
            opINC(0x00A6, 1);
            a = myMapper->readCPU(0x00A6);
            opCMP(a, 0x1E);
            if (!flgZ) {
                goto L_016761;
            }
            a = 0xFF;
            myMapper->writeCPU(0x065C, a);
        }
    }
L_016761:
    popAddress();
}

void game::SUB_016762() {
    myMapper->writeCPU(0x0001, a);
    opINC(0x00A3, 1);
    a = myMapper->readCPU(0x00A3);
    opAND(0x01);
    if (flgZ) {
        a = myMapper->readCPU(0x00A2);
        flgC = true;
        opSBC(myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x00A2, a);
        if (flgN) {
            flgC = false;
            opADC(0x0A);
            myMapper->writeCPU(0x00A2, a);
            opDEC(0x00A1, 1);
            if (!flgN) {
                goto L_016784;
            }
            a = 0x00;
            myMapper->writeCPU(0x00A1, a);
            myMapper->writeCPU(0x00A2, a);
        }
    }
L_016784:
    popAddress();
}

void game::SUB_016785() {
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x00A0);
    flgC = true;
    opSBC(myMapper->readCPU(0x0001));
    myMapper->writeCPU(0x00A0, a);
    if (flgN) {
        flgC = false;
        opADC(0x0A);
        myMapper->writeCPU(0x00A0, a);
        opDEC(0x009F, 1);
        if (!flgN) {
            goto L_01679F;
        }
        a = 0x00;
        myMapper->writeCPU(0x009F, a);
        myMapper->writeCPU(0x00A0, a);
    }
L_01679F:
    popAddress();
}

void game::SUB_0167A0() {
    x = myMapper->readCPU(0x0051);
    y = 0x00;
    do {
        flgC = false;
        a = myMapper->readCPU((0x005A + x) & 0x00ff);
        opADC(myMapper->readCPU(0x007F + y));
        while (a >= 0x0A) {
            flgC = true;
            opSBC(0x0A);
            opINC((0x005B + x) & 0x00ff, 1);
        }
        myMapper->writeCPU((0x005A + x) & 0x00ff, a);
        opINX(1);
        opINY(1);
    } while (y != 0x08);
    a = 0x00;
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0081, a);
    myMapper->writeCPU(0x0082, a);
    myMapper->writeCPU(0x0083, a);
    myMapper->writeCPU(0x0084, a);
    myMapper->writeCPU(0x0085, a);
    myMapper->writeCPU(0x0086, a);
    popAddress();
}

void game::SUB_0167D1() {
    a = myMapper->readCPU(0x008F);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_016805;
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (!flgZ) {
        goto L_016806;
    }
    myMapper->writeCPU(0x0024, 0x14);
    myMapper->writeCPU(0x0025, 0x23);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x009F));
    a = myMapper->readCPU(0x00A0);
    myMapper->writeCPU(0x0001, a);
    x = 0x31;
    pushAddress(0xA7EF);
    jump(0x9E1C);
    if (handleReturnAddress(poppedEntry.value, 0xA7EF)) return;
    myMapper->writeCPU(0x0024, 0x1C);
    myMapper->writeCPU(0x0025, 0x23);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x00A1));
    a = myMapper->readCPU(0x00A2);
    myMapper->writeCPU(0x0001, a);
    x = 0x4C;
    pushAddress(0xA804);
    jump(0x9E1C);
    if (handleReturnAddress(poppedEntry.value, 0xA804)) return;
L_016805:
    popAddress();
    return;
L_016806:
    myMapper->writeCPU(0x0024, 0x00);
    myMapper->writeCPU(0x0025, 0x23);
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x0061 + y));
    a = myMapper->readCPU(0x0060 + y);
    myMapper->writeCPU(0x0001, a);
    x = 0x31;
    pushAddress(0xA81E);
    jump(0x9E1C);
    if (handleReturnAddress(poppedEntry.value, 0xA81E)) return;
    myMapper->writeCPU(0x0024, 0x04);
    myMapper->writeCPU(0x0025, 0x23);
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x005F + y));
    a = myMapper->readCPU(0x005E + y);
    myMapper->writeCPU(0x0001, a);
    x = 0x4C;
    pushAddress(0xA837);
    jump(0x9E1C);
    if (handleReturnAddress(poppedEntry.value, 0xA837)) return;
    myMapper->writeCPU(0x0024, 0x08);
    myMapper->writeCPU(0x0025, 0x23);
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x005D + y));
    a = myMapper->readCPU(0x005C + y);
    myMapper->writeCPU(0x0001, a);
    x = 0x92;
    pushAddress(0xA850);
    jump(0x9E1C);
    if (handleReturnAddress(poppedEntry.value, 0xA850)) return;
    myMapper->writeCPU(0x0024, 0x0C);
    myMapper->writeCPU(0x0025, 0x23);
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x005B + y));
    a = myMapper->readCPU(0x005A + y);
    myMapper->writeCPU(0x0001, a);
    x = 0xAD;
    jump(0x9E1C);
    return;
}

void game::SUB_01686A() {
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_0168AA;
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x02);
    if (!flgZ) {
        a = myMapper->readCPU(0x00D0);
        flgC = true;
        opSBC(0x3C);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opSBC(0x00);
        myMapper->writeCPU(0x00D1, a);
        a = myMapper->readCPU(0x0385);
        opLSR_A(3);
        opAND(0x03);
        myMapper->writeCPU(0x03FD, a);
    }
    a = myMapper->readCPU(0x004B);
    opAND(0x01);
    if (!flgZ) {
        a = myMapper->readCPU(0x00D0);
        flgC = false;
        opADC(0x3C);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opADC(0x00);
        myMapper->writeCPU(0x00D1, a);
        a = myMapper->readCPU(0x0385);
        opLSR_A(3);
        opAND(0x03);
        myMapper->writeCPU(0x03FD, a);
    }
L_0168AA:
    myMapper->writeCPU(0x05C9, 0x00);
    a = myMapper->readCPU(0x004B);
    opAND(0x04);
    if (!flgZ) {
        if (myMapper->readCPU(0x0093) != 0) {
            goto L_0168D1;
        }
        myMapper->writeCPU(0x05C9, 0x10);
        a = myMapper->readCPU(0x0095);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x03FD, a);
        a = myMapper->readCPU(0x0095);
        if (a == 0x01) {
            goto L_0168F1;
        }
        opINC(0x0095, 1);
        goto L_0168F1;
    }
L_0168D1:
    if (myMapper->readCPU(0x0095) != 0) {
        a = myMapper->readCPU(0x0095);
        flgC = false;
        opADC(0x07);
        myMapper->writeCPU(0x03FD, a);
        opDEC(0x0095, 1);
        if (flgZ) {
            a = myMapper->readCPU(0x0385);
            opLSR_A(3);
            opAND(0x03);
            myMapper->writeCPU(0x03FD, a);
            myMapper->writeCPU(0x05C9, 0x10);
        }
    }
L_0168F1:
    a = myMapper->readCPU(0x004B);
    opAND(0x80);
    if (!flgZ) {
        if (myMapper->readCPU(0x0093) != 0) {
            goto L_016903;
        }
        myMapper->writeCPU(0x0094, 0x05);
        myMapper->writeCPU(0x0093, 0x01);
    }
L_016903:
    a = myMapper->readCPU(0x004C);
    opAND(0x40);
    if (!flgZ) {
        if (myMapper->readCPU(0x0096) != 0) {
            goto L_016915;
        }
        myMapper->writeCPU(0x0096, 0x01);
        myMapper->writeCPU(0x00D4, 0x00);
    }
L_016915:
    if (myMapper->readCPU(0x0096) != 0) {
        if (myMapper->readCPU(0x0095) != 0) {
            goto L_01692B;
        }
        x = myMapper->readCPU(0x00D4);
        a = myMapper->readCPU(0xAA12 + x);
        flgC = false;
        opADC(0x06);
        myMapper->writeCPU(0x03FD, a);
        goto L_016936;
    L_01692B:
        x = myMapper->readCPU(0x00D4);
        a = myMapper->readCPU(0xAA12 + x);
        flgC = false;
        opADC(0x0C);
        myMapper->writeCPU(0x03FD, a);
    L_016936:
        a = myMapper->readCPU(0x003F);
        opAND(0x01);
        if (flgZ) {
            opINC(0x00D4, 1);
            opINX(1);
            if (myMapper->readCPU(0xAA12 + x) & 0x80) {
                myMapper->writeCPU(0x0096, 0x00);
                a = 0x00;
                x = myMapper->readCPU(0x0095);
                setLoadFlag(x);
                if (!flgZ) {
                    a = 0x09;
                }
                myMapper->writeCPU(0x03FD, a);
            }
        }
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        if (myMapper->readCPU(0x0096) == 0) {
            goto L_0169BA;
        }
        x = myMapper->readCPU(0x00D4);
        if (myMapper->readCPU(0xAA11 + x) != 0) {
            x = 0x03;
            do {
                a = myMapper->readCPU(0x0476 + x);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_016971;
                }
                opDEX(1);
            } while (!flgN);
            goto L_0169BA;
        L_016971:
            a = 0x06;
            pushAddress(0xA975);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0xA975)) return;
            myMapper->writeCPU(0x0476 + x, 0x07);
            a = 0x00;
            myMapper->writeCPU(0x041C + x, a);
            myMapper->writeCPU(0x03FE + x, a);
            a = myMapper->readCPU(0x0385);
            flgC = false;
            opADC(0x18);
            myMapper->writeCPU(0x0386 + x, a);
            a = myMapper->readCPU(0x03A3);
            opADC(0x00);
            myMapper->writeCPU(0x03A4 + x, a);
            a = myMapper->readCPU(0x03C1);
            flgC = false;
            opADC(0x08);
            myMapper->writeCPU(0x03C2 + x, a);
            a = myMapper->readCPU(0x03DF);
            opADC(0x00);
            myMapper->writeCPU(0x03E0 + x, a);
            if (myMapper->readCPU(0x0095) != 0) {
                a = myMapper->readCPU(0x03C1);
                flgC = false;
                opADC(0x18);
                myMapper->writeCPU(0x03C2 + x, a);
                a = myMapper->readCPU(0x03DF);
                opADC(0x00);
                myMapper->writeCPU(0x03E0 + x, a);
            }
        }
    }
L_0169BA:
    if (!(myMapper->readCPU(0x00D1) & 0x80)) {
        a = myMapper->readCPU(0x00D0);
        flgC = true;
        opSBC(0x00);
        a = myMapper->readCPU(0x00D1);
        opSBC(0x04);
        if (flgC) {
            myMapper->writeCPU(0x00D0, 0x00);
            myMapper->writeCPU(0x00D1, 0x04);
        }
        a = myMapper->readCPU(0x00D0);
        flgC = true;
        opSBC(0x1E);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opSBC(0x00);
        myMapper->writeCPU(0x00D1, a);
        if (!flgN) {
            goto L_016A11;
        }
        a = 0x00;
        myMapper->writeCPU(0x00D0, a);
        myMapper->writeCPU(0x00D1, a);
    }
    else {
        a = myMapper->readCPU(0x00D0);
        flgC = false;
        opADC(0x00);
        a = myMapper->readCPU(0x00D1);
        opADC(0x03);
        if (!flgC) {
            myMapper->writeCPU(0x00D0, 0x00);
            myMapper->writeCPU(0x00D1, 0xFD);
        }
        a = myMapper->readCPU(0x00D0);
        flgC = false;
        opADC(0x1E);
        myMapper->writeCPU(0x00D0, a);
        a = myMapper->readCPU(0x00D1);
        opADC(0x00);
        myMapper->writeCPU(0x00D1, a);
        if (flgN) {
            goto L_016A11;
        }
        a = 0x00;
        myMapper->writeCPU(0x00D0, a);
        myMapper->writeCPU(0x00D1, a);
    }
L_016A11:
    popAddress();
}

void game::SUB_016A1B() {
    x = 0x03;
    while (true) {
        a = myMapper->readCPU(0x0476 + x);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == 0x07) {
                goto L_016A4F;
            }
            if (a != 0x08) {
                goto L_016ABD;
            }
            a = myMapper->readCPU(0x0386 + x);
            flgC = true;
            opSBC(0x06);
            myMapper->writeCPU(0x0386 + x, a);
            a = myMapper->readCPU(0x03A4 + x);
            opSBC(0x00);
            myMapper->writeCPU(0x03A4 + x, a);
            if (!flgN) {
                goto L_016A45;
            }
            a = 0x00;
            myMapper->writeCPU(0x0476 + x, a);
        L_016A45:
            goto L_016A48;
        }
    L_016A48:
        opDEX(1);
        if (flgN) {
            goto L_016A4E;
        }
    }
L_016A4E:
    popAddress();
    return;
L_016A4F:
    a = myMapper->readCPU(0x0386 + x);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x0386 + x, a);
    a = myMapper->readCPU(0x03A4 + x);
    opADC(0x00);
    myMapper->writeCPU(0x03A4 + x, a);
    if (!flgZ) {
        myMapper->writeCPU(0x0476 + x, 0x00);
    }
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(0x20);
    if (a < myMapper->readCPU(0x0386 + x)) {
        a = myMapper->readCPU(0x00A7);
        if (a != 0x01) {
            if (a == 0x02) {
                goto L_016A8D;
            }
        }
        else {
            if (myMapper->readCPU(0x03C2 + x) >= 0x98) {
                goto L_016A9C;
            }
            a = 0x08;
            myMapper->writeCPU(0x0476 + x, a);
            goto L_016A48;
        L_016A8D:
            if (myMapper->readCPU(0x03C2 + x) >= 0x98) {
                a = 0x08;
                myMapper->writeCPU(0x0476 + x, a);
                goto L_016A48;
            }
        }
    L_016A9C:
        myMapper->writeCPU(0x0476 + x, 0x04);
        myMapper->writeCPU(0x04D0 + x, 0x00);
        a = 0x0B;
        pushAddress(0xAAAA);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xAAAA)) return;
        a = 0x01;
        pushAddress(0xAAAF);
        jump(0xA762);
        if (handleReturnAddress(poppedEntry.value, 0xAAAF)) return;
        opINC(0x0081, 1);
        opINC(0x0097, 1);
        if (flgZ) {
            a = 0xFF;
            myMapper->writeCPU(0x0097, a);
        }
    }
    goto L_016A48;
L_016ABD:
    y = myMapper->readCPU(0x04D0 + x);
    a = myMapper->readCPU(0xB1D7 + y);
    setLoadFlag(a);
    if (flgN) {
        a = 0x00;
        myMapper->writeCPU(0x0476 + x, a);
        goto L_016A48;
    }
    myMapper->writeCPU(0x03FE + x, a);
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (!flgZ) {
        goto L_016AD9;
    }
    opINC(0x04D0 + x, 1);
L_016AD9:
    goto L_016A48;
}

void game::SUB_016ADC() {
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
            goto L_016B15;
        }
        if (myMapper->readCPU(0x0385) >= 0x08) {
            goto L_016B15;
        }
    }
    myMapper->writeCPU(0x0385, 0x08);
    myMapper->writeCPU(0x03A3, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x00D0, a);
    myMapper->writeCPU(0x00D1, a);
    goto L_016B37;
L_016B15:
    a = myMapper->readCPU(0x03A3);
    if (a != 0x00) {
        if (a == 0x02) {
            goto L_016B27;
        }
        if (myMapper->readCPU(0x0385) < 0xE8) {
            goto L_016B37;
        }
    L_016B27:
        myMapper->writeCPU(0x0385, 0xE8);
        myMapper->writeCPU(0x03A3, 0x00);
        a = 0x00;
        myMapper->writeCPU(0x00D0, a);
        myMapper->writeCPU(0x00D1, a);
    }
L_016B37:
    if (myMapper->readCPU(0x0093) != 0) {
        if (myMapper->readCPU(0x0096) != 0) {
            goto L_016B44;
        }
        myMapper->writeCPU(0x03FD, 0x1F);
    L_016B44:
        x = 0x00;
        if (myMapper->readCPU(0x0094) & 0x80) {
            x = 0xFF;
        }
        myMapper->writeCPU(0x0001, x);
        a = myMapper->readCPU(0x03C1);
        flgC = true;
        opSBC(myMapper->readCPU(0x0094));
        myMapper->writeCPU(0x03C1, a);
        a = myMapper->readCPU(0x03DF);
        opSBC(myMapper->readCPU(0x0001));
        myMapper->writeCPU(0x03DF, a);
        a = myMapper->readCPU(0x03C1);
        flgC = true;
        opSBC(0x80);
        a = myMapper->readCPU(0x03DF);
        opSBC(0x00);
        if (flgC) {
            myMapper->writeCPU(0x03C1, 0x80);
            myMapper->writeCPU(0x03DF, 0x00);
            a = 0x00;
            myMapper->writeCPU(0x0093, a);
            myMapper->writeCPU(0x03FD, a);
        }
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        a = myMapper->readCPU(0x0094);
        flgC = true;
        opSBC(0x01);
        myMapper->writeCPU(0x0094, a);
    }
    a = myMapper->readCPU(0x0097);
    flgC = true;
    opSBC(0x10);
    if (a >= myMapper->readCPU(0x0385)) {
        goto L_016B9C;
    }
    myMapper->writeCPU(0x0385, a);
    a = 0x01;
    pushAddress(0xAB9B);
    jump(0xA785);
    if (handleReturnAddress(poppedEntry.value, 0xAB9B)) return;
L_016B9C:
    popAddress();
}

void game::SUB_016B9D() {
    myMapper->writeCPU(PPU_SCROLL, myMapper->readCPU(0x0091));
    myMapper->writeCPU(PPU_SCROLL, 0x00);
    a = myMapper->readCPU(0x0040);
    x = myMapper->readCPU(0x0092);
    setLoadFlag(x);
    if (flgZ) {
        goto L_016BB1;
    }
    opAND(0xFE);
    opORA(0x01);
L_016BB1:
    myMapper->writeCPU(PPU_CTRL, a);
    popAddress();
}

void game::SUB_016BB5() {
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x0091, a);
    a = 0x01;
    opSBC(myMapper->readCPU(0x0098));
    opAND(0x01);
    myMapper->writeCPU(0x0092, a);
    a = myMapper->readCPU(0x0097);
    opLSR_A(3);
    opAND(0x03);
    pushAddress(0xABCD);
    jump(0xB281);
    if (handleReturnAddress(poppedEntry.value, 0xABCD)) return;
    popAddress();
}

void game::SUB_016BCF() {
    a = myMapper->readCPU(0x00A7);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xAD45 + x));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0xAD46 + x));
    y = myMapper->readCPU(0x009C);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    if (a != 0x00) {
        if (a == 0x01) {
            goto L_016C09;
        }
        if (a != 0x02) {
            if (a == 0xFF) {
                goto L_016BF2;
            }
            popAddress();
            return;
        L_016BF2:
            a = 0x00;
            myMapper->writeCPU(0x009C, a);
            popAddress();
            return;
        }
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        pushAddress(0xABFC);
        jump(0xAE3E);
        if (handleReturnAddress(poppedEntry.value, 0xABFC)) return;
        if (flgC) {
            goto L_016C5A;
        }
        a = myMapper->readCPU(0x009C);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x009C, a);
        goto L_016C5A;
    L_016C09:
        a = myMapper->readCPU(0x009D);
        setLoadFlag(a);
        if (flgZ) {
            opINY(1);
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x009D, a);
        }
        opDEC(0x009D, 1);
        if (!flgZ) {
            goto L_016C5A;
        }
        a = myMapper->readCPU(0x009C);
        flgC = false;
        opADC(0x02);
        myMapper->writeCPU(0x009C, a);
        goto L_016C5A;
    }
    opINY(1);
    if (myMapper->readCPU(0x0097) < myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y)) {
        opINY(1);
        a = myMapper->readCPU(0x0097);
        flgC = false;
        opADC(myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0097, a);
        opDEY(1);
        if (a < myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y)) {
            goto L_016C5A;
        }
        myMapper->writeCPU(0x0097, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        a = myMapper->readCPU(0x009C);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x009C, a);
    }
    else {
        opINY(1);
        a = myMapper->readCPU(0x0097);
        flgC = true;
        opSBC(myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        myMapper->writeCPU(0x0097, a);
        opDEY(1);
        if (a >= myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y)) {
            goto L_016C5A;
        }
        myMapper->writeCPU(0x0097, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        a = myMapper->readCPU(0x009C);
        flgC = false;
        opADC(0x03);
        myMapper->writeCPU(0x009C, a);
    }
L_016C5A:
    pushAddress(0xAC5C);
    jump(0xB0BA);
    if (handleReturnAddress(poppedEntry.value, 0xAC5C)) return;
    popAddress();
}

void game::SUB_016C5E() {
    x = 0x01;
    do {
        y = myMapper->readCPU(0x0475 + x);
        if (y != 0x04) {
            if (y == 0x05) {
                goto L_016C94;
            }
            if (y != 0x07) {
                pushAddress(0xAC71);
                jump(0xACAC);
                if (handleReturnAddress(poppedEntry.value, 0xAC71)) return;
                if (!flgZ) {
                    goto L_016C94;
                }
                a = myMapper->readCPU(0x00D1);
                flgC = true;
                opSBC(0x02);
                myMapper->writeCPU(0x00D1, a);
                y = myMapper->readCPU(0x0475 + x);
                a = myMapper->readCPU(0xAC9A + y);
                pushAddress(0xAC83);
                jump(0xA785);
                if (handleReturnAddress(poppedEntry.value, 0xAC83)) return;
                a = 0x0B;
                pushAddress(0xAC88);
                jump(0xEA1B);
                if (handleReturnAddress(poppedEntry.value, 0xAC88)) return;
                myMapper->writeCPU(0x0475 + x, myMapper->readCPU(0xACA3 + y));
                a = 0x00;
                myMapper->writeCPU(0x04CF + x, a);
            }
        }
    L_016C94:
        opINX(1);
    } while (x != 0x09);
    popAddress();
}

void game::SUB_016CAC() {
    myMapper->writeCPU(0x0001, myMapper->readCPU(0x03DF));
    a = myMapper->readCPU(0x03C1);
    flgC = false;
    opADC(myMapper->readCPU(0x05C9));
    myMapper->writeCPU(0x0000, a);
    if (flgC) {
        opINC(0x0001, 1);
    }
    myMapper->writeCPU(0x0002, 0x00);
    a = myMapper->readCPU(0x03C1 + x);
    flgC = false;
    opADC(myMapper->readCPU(0xAD21 + y));
    if (flgC) {
        opINC(0x0002, 1);
    }
    flgC = true;
    opSBC(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x0000, a);
    a = myMapper->readCPU(0x0002);
    opSBC(myMapper->readCPU(0x0001));
    if (flgZ) {
        if (myMapper->readCPU(0x05C9) == 0) {
            goto L_016CE7;
        }
        a = myMapper->readCPU(0x0000);
        if (a >= myMapper->readCPU(0xAD3C + y)) {
            goto L_016D15;
        }
        goto L_016CEE;
    L_016CE7:
        if (myMapper->readCPU(0x0000) >= myMapper->readCPU(0xAD33 + y)) {
            goto L_016D15;
        }
    L_016CEE:
        myMapper->writeCPU(0x0025, myMapper->readCPU(0x03A3 + x));
        a = myMapper->readCPU(0x0385 + x);
        flgC = false;
        opADC(myMapper->readCPU(0xAD18 + y));
        if (flgC) {
            opINC(0x0025, 1);
        }
        flgC = true;
        opSBC(myMapper->readCPU(0x0385));
        myMapper->writeCPU(0x0024, a);
        a = myMapper->readCPU(0x0025);
        opSBC(myMapper->readCPU(0x03A3));
        if (flgZ) {
            if (myMapper->readCPU(0x0024) >= myMapper->readCPU(0xAD2A + y)) {
                goto L_016D15;
            }
            a = 0x00;
            setLoadFlag(a);
            popAddress();
            return;
        }
    }
L_016D15:
    a = 0xFF;
    setLoadFlag(a);
    popAddress();
}

void game::SUB_016E3E() {
    myMapper->writeCPU(0x0001, a);
    x = 0x03;
    do {
        a = myMapper->readCPU(0x047A + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_016E4C;
        }
        opDEX(1);
    } while (!flgN);
    flgC = true;
    popAddress();
    return;
L_016E4C:
    a = myMapper->readCPU(0x0001);
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xAE5D + y));
    a = myMapper->readCPU(0xAE5E + y);
    myMapper->writeCPU(0x0006, a);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_016E75() {
    myMapper->writeCPU(0x047A + x, 0x01);
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x038A + x, a);
    a = myMapper->readCPU(0x0099);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x03C6 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0498 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0402 + x, a);
    myMapper->writeCPU(0x0420 + x, 0x05);
    myMapper->writeCPU(0x04D4 + x, 0x08);
    myMapper->writeCPU(0x056A + x, 0x08);
    a = 0x19;
    pushAddress(0xAEAD);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAEAD)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016EB0() {
    myMapper->writeCPU(0x047A + x, 0x01);
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x038A + x, a);
    a = myMapper->readCPU(0x0099);
    flgC = false;
    opADC(0x10);
    myMapper->writeCPU(0x03C6 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0498 + x, a);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0402 + x, a);
    myMapper->writeCPU(0x0420 + x, 0x05);
    myMapper->writeCPU(0x04D4 + x, 0x08);
    myMapper->writeCPU(0x056A + x, 0x06);
    a = 0x19;
    pushAddress(0xAEE8);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAEE8)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016EEB() {
    myMapper->writeCPU(0x047A + x, 0x02);
    myMapper->writeCPU(0x038A + x, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x03C6 + x, 0x70);
    myMapper->writeCPU(0x03E4 + x, 0x00);
    myMapper->writeCPU(0x0402 + x, 0x05);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x056A + x, a);
    myMapper->writeCPU(0x04D4 + x, 0x04);
    a = 0x07;
    pushAddress(0xAF18);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAF18)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016F1B() {
    myMapper->writeCPU(0x047A + x, 0x02);
    myMapper->writeCPU(0x038A + x, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x03C6 + x, 0x7C);
    a = 0x00;
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0402 + x, 0x05);
    myMapper->writeCPU(0x04D4 + x, 0x04);
    myMapper->writeCPU(0x056A + x, 0x01);
    a = 0x07;
    pushAddress(0xAF48);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAF48)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016F4B() {
    myMapper->writeCPU(0x047A + x, 0x02);
    myMapper->writeCPU(0x038A + x, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x03C6 + x, 0x84);
    myMapper->writeCPU(0x0402 + x, 0x05);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x04D4 + x, 0x04);
    myMapper->writeCPU(0x056A + x, 0x02);
    a = 0x07;
    pushAddress(0xAF78);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAF78)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016F7B() {
    myMapper->writeCPU(0x047A + x, 0x03);
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x038A + x, a);
    myMapper->writeCPU(0x03C6 + x, 0x44);
    myMapper->writeCPU(0x0420 + x, 0x02);
    myMapper->writeCPU(0x04D4 + x, 0x05);
    myMapper->writeCPU(0x056A + x, 0x04);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0402 + x, a);
    myMapper->writeCPU(0x0498 + x, a);
    a = 0x03;
    pushAddress(0xAFAE);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAFAE)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016FB1() {
    myMapper->writeCPU(0x047A + x, 0x03);
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x038A + x, a);
    myMapper->writeCPU(0x03C6 + x, 0x44);
    myMapper->writeCPU(0x0420 + x, 0x02);
    myMapper->writeCPU(0x04D4 + x, 0x04);
    myMapper->writeCPU(0x056A + x, 0x03);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0402 + x, a);
    myMapper->writeCPU(0x0498 + x, a);
    a = 0x03;
    pushAddress(0xAFE4);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xAFE4)) return;
    flgC = false;
    popAddress();
}

void game::SUB_016FE7() {
    myMapper->writeCPU(0x047A + x, 0x03);
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x038A + x, a);
    myMapper->writeCPU(0x03C6 + x, 0x44);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x03E4 + x, a);
    myMapper->writeCPU(0x0402 + x, a);
    myMapper->writeCPU(0x0498 + x, a);
    myMapper->writeCPU(0x0420 + x, 0x02);
    myMapper->writeCPU(0x04D4 + x, 0x02);
    myMapper->writeCPU(0x056A + x, 0x03);
    a = 0x03;
    pushAddress(0xB01A);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB01A)) return;
    flgC = false;
    popAddress();
}

void game::SUB_01701D() {
    myMapper->writeCPU(0x047A + x, 0x06);
    myMapper->writeCPU(0x0498 + x, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x04B6 + x, 0x78);
    myMapper->writeCPU(0x03E4 + x, 0x00);
    myMapper->writeCPU(0x0402 + x, 0x05);
    myMapper->writeCPU(0x04D4 + x, 0x03);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x056A + x, a);
    myMapper->writeCPU(0x04F2 + x, a);
    a = 0x08;
    pushAddress(0xB04D);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB04D)) return;
    flgC = false;
    popAddress();
}

void game::SUB_017050() {
    myMapper->writeCPU(0x047A + x, 0x06);
    myMapper->writeCPU(0x0498 + x, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x04B6 + x, 0x78);
    myMapper->writeCPU(0x03E4 + x, 0x00);
    myMapper->writeCPU(0x0402 + x, 0x05);
    myMapper->writeCPU(0x04D4 + x, 0x04);
    myMapper->writeCPU(0x056A + x, 0x01);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x04F2 + x, a);
    a = 0x08;
    pushAddress(0xB082);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB082)) return;
    flgC = false;
    popAddress();
}

void game::SUB_017085() {
    myMapper->writeCPU(0x047A + x, 0x06);
    myMapper->writeCPU(0x0498 + x, myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x04B6 + x, 0x84);
    myMapper->writeCPU(0x03E4 + x, 0x00);
    myMapper->writeCPU(0x0402 + x, 0x05);
    myMapper->writeCPU(0x04D4 + x, 0x04);
    myMapper->writeCPU(0x056A + x, 0x02);
    a = 0x00;
    myMapper->writeCPU(0x03A8 + x, a);
    myMapper->writeCPU(0x0420 + x, a);
    myMapper->writeCPU(0x04F2 + x, a);
    a = 0x08;
    pushAddress(0xB0B7);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB0B7)) return;
    flgC = false;
    popAddress();
}

void game::SUB_0170BA() {
    x = 0x03;
    SUB_0170BC();
    return;
}

void game::SUB_0170BC() {
    a = myMapper->readCPU(0x047A + x);
    setLoadFlag(a);
    if (flgZ) {
        jump(0xB0D0);
        return;
    }
    opASL_A(1);
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(0xB0D4 + y));
    a = myMapper->readCPU(0xB0D5 + y);
    myMapper->writeCPU(0x0006, a);
    jump(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8));
}

void game::SUB_0170D0() {
    opDEX(1);
    if (!flgN) {
        jump(0xB0BC);
        return;
    }
    popAddress();
}

void game::SUB_0170E2() {
    y = myMapper->readCPU(0x04D4 + x);
    a = myMapper->readCPU(0x038A + x);
    flgC = true;
    opSBC(myMapper->readCPU(0xB128 + y));
    myMapper->writeCPU(0x038A + x, a);
    if (!flgC) {
        myMapper->writeCPU(0x047A + x, 0x00);
    }
    a = myMapper->readCPU(0x003F);
    opLSR_A(1);
    opAND(0x01);
    myMapper->writeCPU(0x0402 + x, a);
    y = myMapper->readCPU(0x056A + x);
    a = myMapper->readCPU(0x03C6 + x);
    flgC = false;
    opADC(myMapper->readCPU(0xB133 + y));
    myMapper->writeCPU(0x03C6 + x, a);
    opINC(0x0498 + x, 1);
    a = myMapper->readCPU(0x0498 + x);
    opAND(0x03);
    if (flgZ) {
        if (myMapper->readCPU(0x04D4 + x) == 0) {
            goto L_01711D;
        }
        opDEC(0x04D4 + x, 1);
    L_01711D:
        a = myMapper->readCPU(0x056A + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_017125;
        }
        opDEC(0x056A + x, 1);
    }
L_017125:
    jump(0xB0D0);
    return;
}

void game::SUB_01713E() {
    a = myMapper->readCPU(0x038A + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x04D4 + x));
    myMapper->writeCPU(0x038A + x, a);
    if (!flgC) {
        myMapper->writeCPU(0x047A + x, 0x00);
    }
    a = myMapper->readCPU(0x03C6 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x056A + x));
    myMapper->writeCPU(0x03C6 + x, a);
    if (a < 0xB8) {
        goto L_01716C;
    }
    a = 0x0B;
    pushAddress(0xB161);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB161)) return;
    myMapper->writeCPU(0x047A + x, 0x04);
    a = 0x00;
    myMapper->writeCPU(0x04D4 + x, a);
L_01716C:
    jump(0xB0D0);
    return;
}

void game::SUB_01716F() {
    a = myMapper->readCPU(0x038A + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x056A + x));
    myMapper->writeCPU(0x038A + x, a);
    if (!flgC) {
        a = 0x00;
        myMapper->writeCPU(0x047A + x, a);
        jump(0xB0D0);
        return;
    }
    a = myMapper->readCPU(0x03C6 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x04D4 + x));
    myMapper->writeCPU(0x03C6 + x, a);
    if (a >= 0xB0) {
        a = 0x0B;
        pushAddress(0xB195);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xB195)) return;
        myMapper->writeCPU(0x047A + x, 0x05);
        a = 0x00;
        myMapper->writeCPU(0x04D4 + x, a);
        jump(0xB0D0);
        return;
    }
    opINC(0x0498 + x, 1);
    a = myMapper->readCPU(0x0498 + x);
    opAND(0x03);
    if (!flgZ) {
        goto L_0171B0;
    }
    opDEC(0x04D4 + x, 1);
L_0171B0:
    jump(0xB0D0);
    return;
}

void game::SUB_0171B3() {
    myMapper->writeCPU(0x0420 + x, 0x00);
    y = myMapper->readCPU(0x04D4 + x);
    a = myMapper->readCPU(0xB1D7 + y);
    setLoadFlag(a);
    if (flgN) {
        a = 0x00;
        myMapper->writeCPU(0x047A + x, a);
        jump(0xB0D0);
        return;
    }
    myMapper->writeCPU(0x0402 + x, a);
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (!flgZ) {
        goto L_0171D4;
    }
    opINC(0x04D4 + x, 1);
L_0171D4:
    jump(0xB0D0);
    return;
}

void game::SUB_0171DC() {
    myMapper->writeCPU(0x0420 + x, 0x02);
    y = myMapper->readCPU(0x04D4 + x);
    a = myMapper->readCPU(0xB200 + y);
    setLoadFlag(a);
    if (flgN) {
        a = 0x00;
        myMapper->writeCPU(0x047A + x, a);
        jump(0xB0D0);
        return;
    }
    myMapper->writeCPU(0x0402 + x, a);
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (!flgZ) {
        goto L_0171FD;
    }
    opINC(0x04D4 + x, 1);
L_0171FD:
    jump(0xB0D0);
    return;
}

void game::SUB_017205() {
    a = myMapper->readCPU(0x0498 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x04D4 + x));
    myMapper->writeCPU(0x0498 + x, a);
    if (!flgC) {
        myMapper->writeCPU(0x047A + x, 0x00);
    }
    a = myMapper->readCPU(0x04B6 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x056A + x));
    myMapper->writeCPU(0x04B6 + x, a);
    if (a >= 0xB8) {
        a = 0x0B;
        pushAddress(0xB228);
        jump(0xEA1B);
        if (handleReturnAddress(poppedEntry.value, 0xB228)) return;
        myMapper->writeCPU(0x047A + x, 0x05);
        a = 0x00;
        myMapper->writeCPU(0x04D4 + x, a);
        jump(0xB0D0);
        return;
    }
    y = myMapper->readCPU(0x04F2 + x);
    a = myMapper->readCPU(0x0498 + x);
    flgC = false;
    opADC(myMapper->readCPU(0xB269 + y));
    myMapper->writeCPU(0x038A + x, a);
    a = myMapper->readCPU(0x04B6 + x);
    flgC = false;
    opADC(myMapper->readCPU(0xB275 + y));
    myMapper->writeCPU(0x03C6 + x, a);
    opINC(0x04F2 + x, 1);
    if (myMapper->readCPU(0x04F2 + x) != 0x0C) {
        goto L_01725C;
    }
    myMapper->writeCPU(0x04F2 + x, 0x00);
L_01725C:
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x0402 + x, a);
    jump(0xB0D0);
    return;
}

void game::SUB_017281() {
    if (a == myMapper->readCPU(0x0090)) {
        goto L_0172D4;
    }
    myMapper->writeCPU(0x0090, a);
    opASL_A(2);
    myMapper->writeCPU(0x0001, a);
    myMapper->writeCPU(0x0024, 0xC0);
    myMapper->writeCPU(0x0025, 0x25);
    a = myMapper->readCPU(0x0001);
    x = 0x31;
    pushAddress(0xB299);
    jump(0xB2D5);
    if (handleReturnAddress(poppedEntry.value, 0xB299)) return;
    myMapper->writeCPU(0x0024, 0xC4);
    myMapper->writeCPU(0x0025, 0x25);
    a = myMapper->readCPU(0x0001);
    flgC = false;
    opADC(0x01);
    x = 0x4C;
    pushAddress(0xB2AB);
    jump(0xB2D5);
    if (handleReturnAddress(poppedEntry.value, 0xB2AB)) return;
    myMapper->writeCPU(0x0024, 0x40);
    myMapper->writeCPU(0x0025, 0x26);
    a = myMapper->readCPU(0x0001);
    flgC = false;
    opADC(0x02);
    x = 0x92;
    pushAddress(0xB2BD);
    jump(0xB2D5);
    if (handleReturnAddress(poppedEntry.value, 0xB2BD)) return;
    myMapper->writeCPU(0x0024, 0x44);
    myMapper->writeCPU(0x0025, 0x26);
    a = myMapper->readCPU(0x0001);
    flgC = false;
    opADC(0x03);
    x = 0xAD;
    pushAddress(0xB2CF);
    jump(0xB2D5);
    if (handleReturnAddress(poppedEntry.value, 0xB2CF)) return;
    a = 0x01;
    myMapper->writeCPU(0x008F, a);
L_0172D4:
    popAddress();
}

void game::SUB_0172D5() {
    opASL_A(4);
    flgC = false;
    opADC(0x53);
    myMapper->writeCPU(0x0005, a);
    a = 0x00;
    opADC(0xB3);
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

void game::SUB_017453() {
    a = 0x0A;
    pushAddress(0xB457);
    jump(0xF0CE);
    if (handleReturnAddress(poppedEntry.value, 0xB457)) return;
    pushAddress(0xB45A);
    jump(0xF162);
    if (handleReturnAddress(poppedEntry.value, 0xB45A)) return;
    pushAddress(0xB45D);
    jump(0xCA04);
    if (handleReturnAddress(poppedEntry.value, 0xB45D)) return;
    pushAddress(0xB460);
    jump(0xDD59);
    if (handleReturnAddress(poppedEntry.value, 0xB460)) return;
    a = 0x01;
    pushAddress(0xB465);
    jump(0xE9E6);
    if (handleReturnAddress(poppedEntry.value, 0xB465)) return;
    myMapper->writeCPU(0x0005, 0x64);
    a = 0x90;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    y = 0x20;
    pushAddress(0xB474);
    jump(0xDD0B);
    if (handleReturnAddress(poppedEntry.value, 0xB474)) return;
    a = 0x13;
    pushAddress(0xB479);
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x15;
    pushAddress(0xB47E);
    SUB_01FFAA_SwitchCHRBank1();
    pushAddress(0xB481);
    jump(0xF218);
    if (handleReturnAddress(poppedEntry.value, 0xB481)) return;
    myMapper->writeCPU(0x0005, 0x64);
    a = 0x94;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    pushAddress(0xB48E);
    jump(0xDF13);
    if (handleReturnAddress(poppedEntry.value, 0xB48E)) return;
    pushAddress(0xB491);
    jump(0xB4D2);
    if (handleReturnAddress(poppedEntry.value, 0xB491)) return;
    pushAddress(0xB494);
    jump(0xB5A6);
    if (handleReturnAddress(poppedEntry.value, 0xB494)) return;
    do {
        pushAddress(0xB497);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xB497)) return;
        pushAddress(0xB49A);
        jump(0xDBE8);
        if (handleReturnAddress(poppedEntry.value, 0xB49A)) return;
        pushAddress(0xB49D);
        jump(0xB4FA);
        if (handleReturnAddress(poppedEntry.value, 0xB49D)) return;
        pushAddress(0xB4A0);
        jump(0xB54A);
        if (handleReturnAddress(poppedEntry.value, 0xB4A0)) return;
        pushAddress(0xB4A3);
        jump(0xB6CC);
        if (handleReturnAddress(poppedEntry.value, 0xB4A3)) return;
        pushAddress(0xB4A6);
        jump(0xB533);
        if (handleReturnAddress(poppedEntry.value, 0xB4A6)) return;
        pushAddress(0xB4A9);
        jump(0xF356);
        if (handleReturnAddress(poppedEntry.value, 0xB4A9)) return;
        a = myMapper->readCPU(0x065C);
        setLoadFlag(a);
    } while (flgZ);
    if (!flgN) {
        goto L_0174B8;
    }
    opINC(0x0085, 1);
    y = 0x02;
    pushAddress(0xB4B7);
    jump(0xF89D);
    if (handleReturnAddress(poppedEntry.value, 0xB4B7)) return;
L_0174B8:
    x = 0x02;
    do {
        y = 0x3C;
        do {
            pushAddress(0xB4BE);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB4BE)) return;
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0005, 0x64);
    a = 0x94;
    myMapper->writeCPU(0x0006, a);
    x = 0x00;
    jump(0xDF61);
    return;
}

void game::SUB_0174D2() {
    myMapper->writeCPU(0x0385, 0x58);
    myMapper->writeCPU(0x03C1, 0x78);
    myMapper->writeCPU(0x00EB, 0x05);
    myMapper->writeCPU(0x00EA, 0x09);
    a = 0x00;
    myMapper->writeCPU(0x065C, a);
    myMapper->writeCPU(0x00C8, a);
    myMapper->writeCPU(0x03FD, a);
    x = 0x18;
    do {
        a = myMapper->readCPU(0xB8D9 + x);
        myMapper->writeCPU(0x0565 + x, a);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0174FA() {
    a = myMapper->readCPU(0x003F);
    opAND(0x3F);
    if (flgZ) {
        opDEC(0x00EA, 1);
        if (flgN) {
            myMapper->writeCPU(0x00EA, 0x09);
            opDEC(0x00EB, 1);
            if (!flgN) {
                goto L_017517;
            }
            a = 0x00;
            myMapper->writeCPU(0x00EB, a);
            myMapper->writeCPU(0x00EA, a);
            myMapper->writeCPU(0x065C, 0x01);
        }
    }
L_017517:
    myMapper->writeCPU(0x047F, 0x40);
    x = 0xD0;
    y = 0x18;
    a = myMapper->readCPU(0x00EB);
    pushAddress(0xB524);
    jump(0xB7D6);
    if (handleReturnAddress(poppedEntry.value, 0xB524)) return;
    myMapper->writeCPU(0x047F, 0x80);
    x = 0xE8;
    y = 0x18;
    a = myMapper->readCPU(0x00EA);
    jump(0xB7D6);
    return;
}

void game::SUB_017533() {
    a = myMapper->readCPU(0x00C8);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_017549;
    }
    x = 0x18;
    do {
        a = myMapper->readCPU(0xB8D9 + x);
        if (a != myMapper->readCPU(0x0565 + x)) {
            goto L_017549;
        }
        opDEX(1);
    } while (!flgN);
    a = 0xFF;
    myMapper->writeCPU(0x065C, a);
L_017549:
    popAddress();
}

void game::SUB_01754A() {
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
        pushAddress(0xB58E);
        jump(0xB617);
        if (handleReturnAddress(poppedEntry.value, 0xB58E)) return;
        if (flgC) {
            pushAddress(0xB593);
            jump(0xB64D);
            if (handleReturnAddress(poppedEntry.value, 0xB593)) return;
        }
    }
    a = myMapper->readCPU(0x003F);
    opAND(0x07);
    if (!flgZ) {
        goto L_0175A5;
    }
    opINC(0x03FD, 1);
    a = myMapper->readCPU(0x03FD);
    opAND(0x03);
    myMapper->writeCPU(0x03FD, a);
L_0175A5:
    popAddress();
}

void game::SUB_0175A6() {
    x = 0x02;
    do {
        y = 0x3C;
        do {
            pushAddress(0xB5AC);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB5AC)) return;
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
    } while (!flgZ);
    a = 0x00;
    myMapper->writeCPU(0x00CD, a);
    while (true) {
        do {
            pushAddress(0xB5B9);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB5B9)) return;
            pushAddress(0xB5BC);
            jump(0xB6CC);
            if (handleReturnAddress(poppedEntry.value, 0xB5BC)) return;
            a = myMapper->readCPU(0x00C8);
            setLoadFlag(a);
        } while (!flgZ);
        x = 0x04;
        do {
            pushAddress(0xB5C5);
            jump(0xDBA4);
            if (handleReturnAddress(poppedEntry.value, 0xB5C5)) return;
            opDEX(1);
        } while (!flgZ);
        x = myMapper->readCPU(0x00CD);
        opINC(0x00CD, 1);
        y = myMapper->readCPU(0x0051);
        if (myMapper->readCPU(0x0059 + y) == 0x14) {
            goto L_0175DD;
        }
        a = myMapper->readCPU(0xB5FC + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_0175E8;
        }
        if (!flgN) {
            goto L_0175E2;
        }
    L_0175DD:
        a = myMapper->readCPU(0xB5E9 + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_0175E8;
        }
    L_0175E2:
        pushAddress(0xB5E4);
        jump(0xB64D);
        if (handleReturnAddress(poppedEntry.value, 0xB5E4)) return;
    }
L_0175E8:
    popAddress();
}

void game::SUB_017617() {
    a = myMapper->readCPU(0x0385);
    opLSR_A(3);
    myMapper->writeCPU(0x0001, a);
    a = myMapper->readCPU(0x03C1);
    opLSR_A(3);
    myMapper->writeCPU(0x0002, a);
    x = 0x08;
    do {
        a = myMapper->readCPU(0xB8F2 + x);
        if (a < myMapper->readCPU(0x0001)) {
            flgC = false;
            opADC(0x04);
            if (a >= myMapper->readCPU(0x0001)) {
                a = myMapper->readCPU(0xB8FB + x);
                if (a < myMapper->readCPU(0x0002)) {
                    flgC = false;
                    opADC(0x04);
                    if (a < myMapper->readCPU(0x0002)) {
                        goto L_017648;
                    }
                    a = x;
                    flgC = true;
                    popAddress();
                    return;
                }
            }
        }
    L_017648:
        opDEX(1);
    } while (!flgN);
    flgC = false;
    popAddress();
}

void game::SUB_01764D() {
    myMapper->writeCPU(0x00CB, a);
    x = a;
    y = myMapper->readCPU(0xB8D0 + x);
    a = myMapper->readCPU(0x00C8);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x0565 + y);
        setLoadFlag(a);
        if (!flgZ) {
            x = 0x00;
            if (myMapper->readCPU(0x0564 + y) == 0) {
                goto L_017679;
            }
            x = 0x01;
            if (myMapper->readCPU(0x0566 + y) == 0) {
                goto L_017679;
            }
            x = 0x02;
            if (myMapper->readCPU(0x0560 + y) == 0) {
                goto L_017679;
            }
            x = 0x03;
            a = myMapper->readCPU(0x056A + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_017679;
            }
        }
    }
    popAddress();
    return;
L_017679:
    myMapper->writeCPU(0x00CC, x);
    a = 0x03;
    pushAddress(0xB67F);
    jump(0xEA1B);
    if (handleReturnAddress(poppedEntry.value, 0xB67F)) return;
    myMapper->writeCPU(0x00CA, myMapper->readCPU(0x0565 + y));
    myMapper->writeCPU(0x0565 + y, 0x00);
    a = myMapper->readCPU(0x00CC);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x01) {
            goto L_0176A6;
        }
        if (a == 0x02) {
            goto L_01769E;
        }
        a = myMapper->readCPU(0x00CA);
        myMapper->writeCPU(0x056A + y, a);
        goto L_0176B3;
    L_01769E:
        a = myMapper->readCPU(0x00CA);
        myMapper->writeCPU(0x0560 + y, a);
        goto L_0176B3;
    L_0176A6:
        a = myMapper->readCPU(0x00CA);
        myMapper->writeCPU(0x0566 + y, a);
        goto L_0176B3;
    }
    myMapper->writeCPU(0x0564 + y, myMapper->readCPU(0x00CA));
L_0176B3:
    y = myMapper->readCPU(0x00CB);
    a = myMapper->readCPU(0xB8BE + y);
    myMapper->writeCPU(0x00C4, a);
    myMapper->writeCPU(0x00C6, a);
    a = myMapper->readCPU(0xB8C7 + y);
    myMapper->writeCPU(0x00C5, a);
    myMapper->writeCPU(0x00C7, a);
    myMapper->writeCPU(0x00C8, 0x01);
    a = 0x05;
    myMapper->writeCPU(0x00C9, a);
    popAddress();
}

void game::SUB_0176CC() {
    a = myMapper->readCPU(0x00C8);
    setLoadFlag(a);
    if (flgZ) {
        popAddress();
        return;
    }
    x = myMapper->readCPU(0x00C7);
    y = 0x20;
    pushAddress(0xB6D7);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xB6D7)) return;
    myMapper->writeCPU(0x0024, x);
    myMapper->writeCPU(0x0025, y);
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(myMapper->readCPU(0x00C6));
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x00);
    myMapper->writeCPU(0x0025, a);
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x20);
    myMapper->writeCPU(0x0025, a);
    a = 0x08;
    x = 0x31;
    pushAddress(0xB6FC);
    jump(0xB758);
    if (handleReturnAddress(poppedEntry.value, 0xB6FC)) return;
    x = myMapper->readCPU(0x00C5);
    y = 0x20;
    pushAddress(0xB703);
    jump(0xDCB2);
    if (handleReturnAddress(poppedEntry.value, 0xB703)) return;
    myMapper->writeCPU(0x0024, x);
    myMapper->writeCPU(0x0025, y);
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(myMapper->readCPU(0x00C4));
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x00);
    myMapper->writeCPU(0x0025, a);
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x00);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0025);
    opADC(0x20);
    myMapper->writeCPU(0x0025, a);
    a = myMapper->readCPU(0x00CA);
    flgC = true;
    opSBC(0x01);
    x = 0x4C;
    pushAddress(0xB72B);
    jump(0xB758);
    if (handleReturnAddress(poppedEntry.value, 0xB72B)) return;
    a = myMapper->readCPU(0x003F);
    opAND(0x01);
    if (flgZ) {
        a = myMapper->readCPU(0x00CC);
        setLoadFlag(a);
        if (!flgZ) {
            if (a == 0x01) {
                goto L_017748;
            }
            if (a != 0x02) {
                opINC(0x00C5, 1);
                goto L_01774F;
            }
            opDEC(0x00C5, 1);
            goto L_01774F;
        L_017748:
            opINC(0x00C4, 1);
            goto L_01774F;
        }
        opDEC(0x00C4, 1);
    L_01774F:
        opDEC(0x00C9, 1);
        if (!flgZ) {
            goto L_017757;
        }
        a = 0x00;
        myMapper->writeCPU(0x00C8, a);
    }
L_017757:
    popAddress();
}

void game::SUB_017758() {
    opASL_A(4);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0005, a);
    a = 0x00;
    opADC(0xB9);
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
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0114 + x, a);
        opINY(1);
        opINX(1);
    } while (y != 0x10);
    popAddress();
}

void game::SUB_0177D6() {
    myMapper->writeCPU(0x0391, x);
    myMapper->writeCPU(0x0001, x);
    myMapper->writeCPU(0x03CD, y);
    x = a;
    x = myMapper->readCPU(0xB83C + x);
    y = myMapper->readCPU(0x047F);
    a = 0x00;
    myMapper->writeCPU(0x0481, a);
    myMapper->writeCPU(0x0480, a);
    do {
        myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0xB846 + x));
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
            goto L_017830;
        }
        myMapper->writeCPU(0x0480, 0x00);
        myMapper->writeCPU(0x0391, myMapper->readCPU(0x0001));
        flgC = false;
        a = myMapper->readCPU(0x03CD);
        opADC(0x08);
        myMapper->writeCPU(0x03CD, a);
    L_017830:
        opINX(1);
        opINC(0x0481, 1);
        a = myMapper->readCPU(0x0481);
    } while (a != 0x0C);
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x1D;
    pushAddress(0x9D11);
    SUB_01FFAA_SwitchCHRBank1();
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
    myMapper->writeCPU(PPU_CTRL, a);
    myMapper->writeCPU(PPU_MASK, a);
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x1D;
    pushAddress(0xAF08);
    SUB_01FFAA_SwitchCHRBank1();
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x1D;
    pushAddress(0xB38D);
    SUB_01FFAA_SwitchCHRBank1();
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x15;
    pushAddress(0xB6C3);
    SUB_01FFAA_SwitchCHRBank1();
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
    myMapper->writeCPU(SCROLL_FINE, a);
    myMapper->writeCPU(SCROLL_LARGE, a);
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x15;
    pushAddress(0xBB27);
    SUB_01FFAA_SwitchCHRBank1();
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

void game::SUB_01C000_StartGame() {
    //init ram content
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

    SUB_01F189();
}

void game::SUB_01C030() {
    a = 0x00;
    myMapper->writeCPU(PPU_CTRL, a);
    myMapper->writeCPU(PPU_MASK, a);
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
        SUB_01FFE6_SwithPRGBank();
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
        myMapper->writeCPU(PPU_CTRL, y);
        myMapper->writeCPU(PPU_MASK, y);
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
        myMapper->writeCPU(PPU_CTRL, x);
        myMapper->writeCPU(PPU_MASK, x);
        x = 0x19;
        myMapper->writeCPU(0x0000, x);
        do {
            opBIT(myMapper->readCPU(PPU_STATUS));
            if (!flgN) wait(1);
            //do {
            //    opBIT(myMapper->readCPU(PPU_STATUS));
            //} while (!flgN);
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
    SUB_01FFE6_SwithPRGBank();
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
    if (!flgZ) {
        goto L_01CA4B;
    }
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
    jump(0xCA60);
    return;
L_01CA4B:
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
    SUB_01CA60();
    return;
}

void game::SUB_01CA60() {
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
    opSBC(myMapper->readCPU(SCROLL_FINE));
    myMapper->writeCPU(0x0439 + y, a);
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x03A3 + y);
    opSBC(myMapper->readCPU(SCROLL_LARGE));
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

void game::SUB_01CAC5() {
    popAddress();
}

void game::SUB_01CAC6() {
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x0018) + (myMapper->readCPU((0x0018 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x0018) + (myMapper->readCPU((0x0018 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0028);
    x = a;
    flgC = false;
    opADC(0x10);
    if (flgC) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0028, a);
    a = myMapper->readCPU(0x0026);
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0204 + x, a);
    a = myMapper->readCPU(0x0026);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0026, a);
    if (flgC) {
        opINC(0x0027, 1);
    }
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x0208 + x, a);
    myMapper->writeCPU(0x020C + x, a);
    a = myMapper->readCPU(0x0024);
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0200 + x, a);
        myMapper->writeCPU(0x0208 + x, a);
    }
    else {
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x020B + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0204 + x, a);
        myMapper->writeCPU(0x020C + x, a);
    }
    else {
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020F + x, a);
    }
    y = 0x00;
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        goto L_01CB6D;
    }
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0202 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0206 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0209 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020A + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020E + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    popAddress();
    return;
L_01CB6D:
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0206 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0202 + x, a);
    opINY(1);
    myMapper->writeCPU(0x020D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x020E + x, a);
    opINY(1);
    myMapper->writeCPU(0x0209 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x020A + x, a);
    popAddress();
}

void game::SUB_01CBA5() {
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x001C) + (myMapper->readCPU((0x001C + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x001C) + (myMapper->readCPU((0x001C + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0028);
    x = a;
    flgC = false;
    opADC(0x24);
    if (flgC) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0028, a);
    a = myMapper->readCPU(0x0026);
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0204 + x, a);
    myMapper->writeCPU(0x0208 + x, a);
    a = myMapper->readCPU(0x0026);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0026, a);
    if (flgC) {
        opINC(0x0027, 1);
    }
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x020C + x, a);
    myMapper->writeCPU(0x0210 + x, a);
    myMapper->writeCPU(0x0214 + x, a);
    a = myMapper->readCPU(0x0026);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0026, a);
    if (flgC) {
        opINC(0x0027, 1);
    }
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x0218 + x, a);
    myMapper->writeCPU(0x021C + x, a);
    myMapper->writeCPU(0x0220 + x, a);
    a = myMapper->readCPU(0x0024);
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0200 + x, a);
        myMapper->writeCPU(0x020C + x, a);
        myMapper->writeCPU(0x0218 + x, a);
    }
    else {
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x021B + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0204 + x, a);
        myMapper->writeCPU(0x0210 + x, a);
        myMapper->writeCPU(0x021C + x, a);
    }
    else {
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        myMapper->writeCPU(0x021F + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0208 + x, a);
        myMapper->writeCPU(0x0214 + x, a);
        myMapper->writeCPU(0x0220 + x, a);
    }
    else {
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x0217 + x, a);
        myMapper->writeCPU(0x0223 + x, a);
    }
    y = 0x00;
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        goto L_01CCDA;
    }
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0202 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0206 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0209 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020A + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020E + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0211 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0212 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0215 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0216 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0219 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x021A + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x021D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x021E + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0221 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0222 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    popAddress();
    return;
L_01CCDA:
    myMapper->writeCPU(0x0209 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x020A + x, a);
    opINY(1);
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0206 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0202 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0215 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0216 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0211 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0212 + x, a);
    opINY(1);
    myMapper->writeCPU(0x020D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x020E + x, a);
    opINY(1);
    myMapper->writeCPU(0x0221 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0222 + x, a);
    opINY(1);
    myMapper->writeCPU(0x021D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x021E + x, a);
    opINY(1);
    myMapper->writeCPU(0x0219 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x021A + x, a);
    popAddress();
}

void game::SUB_01CD58() {
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x0016) + (myMapper->readCPU((0x0016 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0028);
    x = a;
    flgC = false;
    opADC(0x08);
    if (flgC) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0028, a);
    a = myMapper->readCPU(0x0026);
    if (myMapper->readCPU(0x0027) != 0) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0204 + x, a);
    a = myMapper->readCPU(0x0024);
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0200 + x, a);
    }
    else {
        myMapper->writeCPU(0x0203 + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0204 + x, a);
    }
    else {
        myMapper->writeCPU(0x0207 + x, a);
    }
    y = 0x00;
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        goto L_01CDC3;
    }
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0202 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0206 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    popAddress();
    return;
L_01CDC3:
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0206 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0202 + x, a);
    popAddress();
}

void game::SUB_01CDDF() {
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x0014) + (myMapper->readCPU((0x0014 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0027);
    opORA(myMapper->readCPU(0x0025));
    if (!flgZ) {
        goto L_01CDF7;
    }
    a = myMapper->readCPU(0x0028);
    x = a;
    flgC = false;
    opADC(0x04);
    if (!flgC) {
        goto L_01CDF8;
    }
L_01CDF7:
    popAddress();
    return;
L_01CDF8:
    myMapper->writeCPU(0x0028, a);
    myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0026));
    a = myMapper->readCPU(0x0024);
    myMapper->writeCPU(0x0203 + x, a);
    y = 0x00;
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        goto L_01CE16;
    }
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
    while (true) {
        myMapper->writeCPU(0x0202 + x, a);
        popAddress();
        return;
    L_01CE16:
        myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
        opORA(0x40);
    }
    SUB_01CE23();
    return;
}

void game::SUB_01CE23() {
    y = a;
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x001E) + (myMapper->readCPU((0x001E + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0005);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0006);
    opADC(0x00);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0028);
    x = a;
    flgC = false;
    opADC(0x20);
    if (flgC) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0028, a);
    a = myMapper->readCPU(0x0026);
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x0200 + x, a);
    myMapper->writeCPU(0x0204 + x, a);
    myMapper->writeCPU(0x0208 + x, a);
    myMapper->writeCPU(0x020C + x, a);
    a = myMapper->readCPU(0x0026);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0026, a);
    if (flgC) {
        opINC(0x0027, 1);
    }
    if (myMapper->readCPU(0x0027) != 0) {
        a = 0xF0;
    }
    myMapper->writeCPU(0x0210 + x, a);
    myMapper->writeCPU(0x0214 + x, a);
    myMapper->writeCPU(0x0218 + x, a);
    myMapper->writeCPU(0x021C + x, a);
    a = myMapper->readCPU(0x0024);
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0200 + x, a);
        myMapper->writeCPU(0x0210 + x, a);
    }
    else {
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0213 + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0204 + x, a);
        myMapper->writeCPU(0x0214 + x, a);
    }
    else {
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x0217 + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x0208 + x, a);
        myMapper->writeCPU(0x0218 + x, a);
    }
    else {
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x021B + x, a);
    }
    a = myMapper->readCPU(0x0024);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0024, a);
    if (flgC) {
        opINC(0x0025, 1);
    }
    y = myMapper->readCPU(0x0025);
    setLoadFlag(y);
    if (!flgZ) {
        a = 0xF0;
        myMapper->writeCPU(0x020C + x, a);
        myMapper->writeCPU(0x021C + x, a);
    }
    else {
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x021F + x, a);
    }
    y = 0x00;
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        goto L_01CF4B;
    }
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0202 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0206 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0209 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x020A + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x020D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x020E + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0211 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0212 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0215 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0216 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0219 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x021A + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x021D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x021E + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    popAddress();
    return;
L_01CF4B:
    myMapper->writeCPU(0x020D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x020E + x, a);
    opINY(1);
    myMapper->writeCPU(0x0209 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x020A + x, a);
    opINY(1);
    myMapper->writeCPU(0x0205 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0206 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0201 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0202 + x, a);
    opINY(1);
    myMapper->writeCPU(0x021D + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x021E + x, a);
    opINY(1);
    myMapper->writeCPU(0x0219 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x021A + x, a);
    opINY(1);
    myMapper->writeCPU(0x0215 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0216 + x, a);
    opINY(1);
    myMapper->writeCPU(0x0211 + x, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(0x0212 + x, a);
    popAddress();
}

void game::SUB_01CFB3() {
    y = a;
    a = myMapper->readCPU(0x0028);
    flgC = false;
    opADC(0x60);
    if (flgC) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x0022) + (myMapper->readCPU((0x0022 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x0022) + (myMapper->readCPU((0x0022 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0005);
    flgC = false;
    opADC(0x18);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0006);
    opADC(0x00);
    myMapper->writeCPU(0x0008, a);
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        a = myMapper->readCPU(0x0024);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x0024, a);
        if (!flgC) {
            opDEC(0x0025, 1);
        }
    }
    a = myMapper->readCPU(0x0026);
    y = myMapper->readCPU(0x0027);
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x0032, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0035, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0034, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0037, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0036, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0039, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0038, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x003B, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x003A, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x003D, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x003C, y);
    a = myMapper->readCPU(0x0024);
    y = myMapper->readCPU(0x0025);
    myMapper->writeCPU(0x002B, a);
    myMapper->writeCPU(0x002A, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x002D, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x002C, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x002F, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x002E, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0031, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0030, y);
    a = 0x00;
    myMapper->writeCPU(0x003E, a);
    x = myMapper->readCPU(0x0028);
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        myMapper->writeCPU(0x003E, 0x40);
        a = myMapper->readCPU(0x002A);
        y = myMapper->readCPU(0x0030);
        myMapper->writeCPU(0x0030, a);
        myMapper->writeCPU(0x002A, y);
        a = myMapper->readCPU(0x002B);
        y = myMapper->readCPU(0x0031);
        myMapper->writeCPU(0x0031, a);
        myMapper->writeCPU(0x002B, y);
        a = myMapper->readCPU(0x002C);
        y = myMapper->readCPU(0x002E);
        myMapper->writeCPU(0x002E, a);
        myMapper->writeCPU(0x002C, y);
        a = myMapper->readCPU(0x002D);
        y = myMapper->readCPU(0x002F);
        myMapper->writeCPU(0x002F, a);
        myMapper->writeCPU(0x002D, y);
    }
    y = 0x00;
    a = myMapper->readCPU(0x002A);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x002B);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        myMapper->writeCPU(0x0217 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003C) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003D));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
    }
    y = 0x06;
    a = myMapper->readCPU(0x002C);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x002D);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        myMapper->writeCPU(0x0217 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003C) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003D));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
    }
    y = 0x0C;
    a = myMapper->readCPU(0x002E);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x002F);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        myMapper->writeCPU(0x0217 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003C) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003D));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
    }
    y = 0x12;
    a = myMapper->readCPU(0x0030);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x0031);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        myMapper->writeCPU(0x0217 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003C) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_01D37F;
            }
            myMapper->writeCPU(0x0201 + x, a);
            myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003D));
            a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
            opORA(myMapper->readCPU(0x003E));
            myMapper->writeCPU(0x0202 + x, a);
            opINX(4);
        }
    }
L_01D37F:
    myMapper->writeCPU(0x0028, x);
    popAddress();
}

void game::SUB_01D382() {
    y = a;
    a = myMapper->readCPU(0x0028);
    flgC = false;
    opADC(0x3C);
    if (flgC) {
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(myMapper->readCPU(0x0020) + (myMapper->readCPU((0x0020 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0006, myMapper->readCPU(myMapper->readCPU(0x0020) + (myMapper->readCPU((0x0020 + 1) & 0x00ff) << 8) + y));
    a = myMapper->readCPU(0x0005);
    flgC = false;
    opADC(0x0F);
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0006);
    opADC(0x00);
    myMapper->writeCPU(0x0008, a);
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        a = myMapper->readCPU(0x0024);
        flgC = true;
        opSBC(0x08);
        myMapper->writeCPU(0x0024, a);
        if (!flgC) {
            opDEC(0x0025, 1);
        }
    }
    a = myMapper->readCPU(0x0026);
    y = myMapper->readCPU(0x0027);
    myMapper->writeCPU(0x0033, a);
    myMapper->writeCPU(0x0032, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0035, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0034, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0037, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0036, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0039, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x0038, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x003B, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x003A, y);
    a = myMapper->readCPU(0x0024);
    y = myMapper->readCPU(0x0025);
    myMapper->writeCPU(0x002B, a);
    myMapper->writeCPU(0x002A, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x002D, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x002C, y);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x002F, a);
    if (flgC) {
        opINY(1);
    }
    myMapper->writeCPU(0x002E, y);
    a = 0x00;
    myMapper->writeCPU(0x003E, a);
    x = myMapper->readCPU(0x0028);
    opBIT(myMapper->readCPU(0x0002));
    if (flgN) {
        myMapper->writeCPU(0x003E, 0x40);
        a = myMapper->readCPU(0x002A);
        y = myMapper->readCPU(0x002E);
        myMapper->writeCPU(0x002E, a);
        myMapper->writeCPU(0x002A, y);
        a = myMapper->readCPU(0x002B);
        y = myMapper->readCPU(0x002F);
        myMapper->writeCPU(0x002F, a);
        myMapper->writeCPU(0x002B, y);
    }
    y = 0x00;
    a = myMapper->readCPU(0x002A);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x002B);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
    }
    y = 0x05;
    a = myMapper->readCPU(0x002C);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x002D);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
    }
    y = 0x0A;
    a = myMapper->readCPU(0x002E);
    setLoadFlag(a);
    if (!flgZ) {
    }
    else {
        a = myMapper->readCPU(0x002F);
        myMapper->writeCPU(0x0203 + x, a);
        myMapper->writeCPU(0x0207 + x, a);
        myMapper->writeCPU(0x020B + x, a);
        myMapper->writeCPU(0x020F + x, a);
        myMapper->writeCPU(0x0213 + x, a);
        if (myMapper->readCPU(0x0032) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0033));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0034) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0035));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0036) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0037));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x0038) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x0201 + x, a);
                myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x0039));
                a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
                opORA(myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x0202 + x, a);
                opINX(4);
            }
        }
        opINY(1);
        if (myMapper->readCPU(0x003A) == 0) {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_01D60A;
            }
            myMapper->writeCPU(0x0201 + x, a);
            myMapper->writeCPU(0x0200 + x, myMapper->readCPU(0x003B));
            a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
            opORA(myMapper->readCPU(0x003E));
            myMapper->writeCPU(0x0202 + x, a);
            opINX(4);
        }
    L_01D60A:
        opINY(1);
    }
    myMapper->writeCPU(0x0028, x);
    popAddress();
}

void game::SUB_01D60E() {
    a = myMapper->readCPU(PPU_STATUS);
    a = myMapper->readCPU(0x0100);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0101));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0043));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0102));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0103));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0104));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0105));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0106));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0107));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0108));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0109));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x010A));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x010B));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x010C));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x010D));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x010E));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x010F));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0110));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0111));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0112));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0113));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0114));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0115));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0116));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0117));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0118));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0119));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x011A));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x011B));
    }
    a = myMapper->readCPU(0x011C);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x011D));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x011E));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x011F));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0120));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0121));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0122));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0123));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0124));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0125));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0126));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0127));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0128));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0129));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x012A));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x012B));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x012C));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x012D));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x012E));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x012F));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0130));
    }
    a = myMapper->readCPU(0x0131);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0132));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0133));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0134));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0135));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0136));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0137));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0138));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0139));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x013A));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x013B));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x013C));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x013D));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x013E));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x013F));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0140));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0141));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0142));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0143));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0144));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0145));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0146));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0147));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0148));
        a = myMapper->readCPU(0x0149);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(PPU_ADDR, a);
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x014A));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x014B));
        }
    }
    a = myMapper->readCPU(0x014C);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x014D));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x014E));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x014F));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0150));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0151));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0152));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0153));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0154));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0155));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0156));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0157));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0158));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0159));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x015A));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x015B));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x015C));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x015D));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x015E));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x015F));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0160));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0161));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0162));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0163));
        a = myMapper->readCPU(0x0164);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(PPU_ADDR, a);
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0165));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0166));
        }
    }
    a = myMapper->readCPU(0x0167);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0168));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0169));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x016A));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x016B));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x016C));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x016D));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x016E));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x016F));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0170));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0171));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0172));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0173));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0174));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0175));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0176));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0177));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0178));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0179));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x017A));
    }
    a = myMapper->readCPU(0x017B);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x017C));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x017D));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x017E));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0181));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0182));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0183));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0184));
    }
    a = myMapper->readCPU(0x0187);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0188));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0189));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x018A));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x018B));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x018C));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x018D));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x018E));
    }
    a = myMapper->readCPU(0x018F);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0190));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0191));
    }
    a = myMapper->readCPU(0x0192);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0193));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0194));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0195));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0196));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0197));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0198));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x0199));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x019A));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x019B));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x019C));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x019D));
        a = myMapper->readCPU(0x019E);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(PPU_ADDR, a);
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x019F));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A0));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A1));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A2));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A3));
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01A4));
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01A5));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A6));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A7));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A8));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01A9));
        }
        a = myMapper->readCPU(0x01AA);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(PPU_ADDR, a);
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01AB));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01AC));
        }
    }
    a = myMapper->readCPU(0x01AD);
    setLoadFlag(a);
    if (flgN) {
    }
    else {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01AE));
        myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01AF));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B0));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B1));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B2));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01B3));
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01B4));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B5));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B6));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B7));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01B8));
        a = myMapper->readCPU(0x01B9);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(PPU_ADDR, a);
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01BA));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01BB));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01BC));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01BD));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01BE));
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01BF));
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01C0));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01C1));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01C2));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01C3));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01C4));
        }
        a = myMapper->readCPU(0x01C5);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(PPU_ADDR, a);
            myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01C6));
            myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01C7));
        }
    }
    a = myMapper->readCPU(0x01C8);
    setLoadFlag(a);
    if (!flgN) {
        myMapper->writeCPU(PPU_ADDR, a);
        myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01C9));
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01CA));
    }
    a = myMapper->readCPU(0x01CB);
    setLoadFlag(a);
    if (flgN) {
        goto L_01DB36;
    }
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, myMapper->readCPU(0x01CC));
    myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0043));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x01CD));
    a = myMapper->readCPU(0x01CE);
    myMapper->writeCPU(PPU_DATA, a);
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
        wait(1);
        goto L_01DBB5;
    }
    popAddress();
}

void game::SUB_01DBBA() {
    y = 0x01;
    myMapper->writeCPU(JOY1, y);
    opDEY(1);
    myMapper->writeCPU(JOY1, y);
    x = 0x07;
    do {
        a = myMapper->readCPU(JOY1);
        //NOP
        //NOP
        //NOP
        //NOP
        //NOP
        opLSR_A(1);
        opROL_M(0x0044, 1);
        a = myMapper->readCPU(JOY2);
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

void game::SUB_01DBDF() {
    pushAddress(0xDBE1);
    jump(0xDBBA);
    if (handleReturnAddress(poppedEntry.value, 0xDBE1)) return;
    pushAddress(0xDBE4);
    jump(0xE92A);
    if (handleReturnAddress(poppedEntry.value, 0xDBE4)) return;
    jump(0xDBEB);
    return;
}

void game::SUB_01DBE8() {
    pushAddress(0xDBEA);
    jump(0xDBBA);
    if (handleReturnAddress(poppedEntry.value, 0xDBEA)) return;
    SUB_01DBEB();
    return;
}

void game::SUB_01DBEB() {
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

void game::SUB_01DC63() {
    opDEY(1);
    myMapper->writeCPU(0x009F, y);
    myMapper->writeCPU(0x009E, x);
    flgC = false;
    a = myMapper->readCPU(0x00A2);
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x00A4, a);
    a = myMapper->readCPU(0x00A3);
    opADC(0x00);
    myMapper->writeCPU(0x00A5, a);
    a = myMapper->readCPU(0x00A4);
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x00A6, a);
    a = myMapper->readCPU(0x00A5);
    opADC(0x00);
    myMapper->writeCPU(0x00A7, a);
    a = myMapper->readCPU(0x00A6);
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x00A8, a);
    a = myMapper->readCPU(0x00A7);
    opADC(0x00);
    myMapper->writeCPU(0x00A9, a);
    a = myMapper->readCPU(0x00A8);
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x00AA, a);
    a = myMapper->readCPU(0x00A9);
    opADC(0x00);
    myMapper->writeCPU(0x00AB, a);
    a = myMapper->readCPU(0x00AA);
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x00AC, a);
    a = myMapper->readCPU(0x00AB);
    opADC(0x00);
    myMapper->writeCPU(0x00AD, a);
    a = myMapper->readCPU(0x00AC);
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x00AE, a);
    a = myMapper->readCPU(0x00AD);
    opADC(0x00);
    myMapper->writeCPU(0x00AF, a);
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
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0xDD04);
    jump(0xDBB3);
    if (handleReturnAddress(poppedEntry.value, 0xDD04)) return;
    a = myMapper->readCPU(0x0041);
    myMapper->writeCPU(PPU_MASK, a);
    popAddress();
}

void game::SUB_01DD0B() {
    a = myMapper->readCPU(PPU_STATUS);
    myMapper->writeCPU(PPU_ADDR, y);
    myMapper->writeCPU(PPU_ADDR, x);
    x = 0x04;
    do {
        y = 0x00;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(PPU_DATA, a);
            opINY(1);
        } while (!flgZ);
        opINC(0x0006, 1);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_01DD26() {
    //do {
    //    opBIT(myMapper->readCPU(PPU_STATUS));
    //} while (!flgN);
    opBIT(myMapper->readCPU(PPU_STATUS));
    if (!flgN) wait(1);
    SUB_01DD2B();
    return;
}

void game::SUB_01DD2B() {
    a = myMapper->readCPU(PPU_STATUS);
    myMapper->writeCPU(PPU_ADDR, 0x3F);
    myMapper->writeCPU(PPU_ADDR, 0x00);
    y = 0x00;
    do {
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(myMapper->readCPU(0x000C) + (myMapper->readCPU((0x000C + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x20);
    myMapper->writeCPU(PPU_ADDR, 0x3F);
    a = 0x00;
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(0x000D, a);
    myMapper->writeCPU(0x000B, a);
    popAddress();
}

void game::SUB_01DD59() {
    //do {
    //    opBIT(myMapper->readCPU(PPU_STATUS));
    //} while (!flgN);
    opBIT(myMapper->readCPU(PPU_STATUS));
    if (!flgN) wait(1);
    myMapper->writeCPU(PPU_ADDR, 0x3F);
    myMapper->writeCPU(PPU_ADDR, 0x00);
    a = 0x0F;
    y = 0x20;
    do {
        myMapper->writeCPU(PPU_DATA, a);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(PPU_ADDR, 0x3F);
    a = 0x00;
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, a);
    popAddress();
}

void game::SUB_01DD83() {
    a = myMapper->readCPU(PPU_STATUS);
    myMapper->writeCPU(PPU_ADDR, 0x20);
    myMapper->writeCPU(PPU_ADDR, 0x00);
    y = 0x40;
    a = 0x00;
    do {
        myMapper->writeCPU(PPU_DATA, a);
        opDEY(1);
    } while (!flgZ);
    y = 0x00;
    do {
        myMapper->writeCPU(PPU_DATA, myMapper->readCPU(myMapper->readCPU(0x0005) + (myMapper->readCPU((0x0005 + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x40);
    myMapper->writeCPU(PPU_ADDR, 0x24);
    myMapper->writeCPU(PPU_ADDR, 0x00);
    y = 0x00;
    a = 0x00;
    do {
        myMapper->writeCPU(PPU_DATA, a);
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(PPU_ADDR, 0x23);
    myMapper->writeCPU(PPU_ADDR, 0xC0);
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(PPU_DATA, a);
        opINY(1);
    } while (y != 0x08);
    pushAddress(0xDDD2);
    jump(0xE6B8);
    if (handleReturnAddress(poppedEntry.value, 0xDDD2)) return;
    pushAddress(0xDDD5);
    jump(0xE740);
    if (handleReturnAddress(poppedEntry.value, 0xDDD5)) return;
    y = myMapper->readCPU(0x0051);
    x = myMapper->readCPU((0x0052 + y) & 0x00ff);
    a = myMapper->readCPU(0x0053 + y);
    y = a;
    pushAddress(0xDDE0);
    jump(0xE81E);
    if (handleReturnAddress(poppedEntry.value, 0xDDE0)) return;
    pushAddress(0xDDE3);
    jump(0xD60E);
    if (handleReturnAddress(poppedEntry.value, 0xDDE3)) return;
    y = myMapper->readCPU(0x0051);
    x = myMapper->readCPU((0x0054 + y) & 0x00ff);
    a = myMapper->readCPU(0x0055 + y);
    y = a;
    pushAddress(0xDDEE);
    jump(0xE7CA);
    if (handleReturnAddress(poppedEntry.value, 0xDDEE)) return;
    pushAddress(0xDDF1);
    jump(0xD60E);
    if (handleReturnAddress(poppedEntry.value, 0xDDF1)) return;
    y = myMapper->readCPU(0x0051);
    x = myMapper->readCPU((0x0056 + y) & 0x00ff);
    a = myMapper->readCPU(0x0057);
    y = a;
    pushAddress(0xDDFB);
    jump(0xE877);
    if (handleReturnAddress(poppedEntry.value, 0xDDFB)) return;
    a = myMapper->readCPU(0x0593);
    opASL_A(2);
    x = a;
    a = 0x20;
    myMapper->writeCPU(0x017B, a);
    myMapper->writeCPU(0x0181, a);
    myMapper->writeCPU(0x017C, 0x4F);
    myMapper->writeCPU(0x0182, 0x6F);
    a = myMapper->readCPU(0xDE48 + x);
    myMapper->writeCPU(0x017D, a);
    myMapper->writeCPU(0x065B, a);
    a = myMapper->readCPU(0xDE49 + x);
    myMapper->writeCPU(0x017E, a);
    myMapper->writeCPU(0x065C, a);
    a = myMapper->readCPU(0xDE4A + x);
    myMapper->writeCPU(0x0183, a);
    myMapper->writeCPU(0x065D, a);
    a = myMapper->readCPU(0xDE4B + x);
    myMapper->writeCPU(0x0184, a);
    myMapper->writeCPU(0x065E, a);
    pushAddress(0xDE3A);
    jump(0xD60E);
    if (handleReturnAddress(poppedEntry.value, 0xDE3A)) return;
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x008D, myMapper->readCPU(0x0058 + y));
    a = 0x00;
    myMapper->writeCPU(0x0058 + y, a);
    popAddress();
}

void game::SUB_01DE68() {
    myMapper->writeCPU(0x03C1, a);
    myMapper->writeCPU(0x0000, x);
    a = x;
    x = 0x00;
    flgC = true;
    opSBC(0x04);
    if (flgN) {
        goto L_01DE76;
    }
    x = a;
L_01DE76:
    myMapper->writeCPU(0x00A0, x);
    myMapper->writeCPU(0x009F, 0xFF);
    a = 0x00;
    myMapper->writeCPU(0x0614, a);
    myMapper->writeCPU(0x0615, a);
    myMapper->writeCPU(0x0616, a);
    myMapper->writeCPU(0x0617, a);
    myMapper->writeCPU(0x0618, a);
    myMapper->writeCPU(0x0619, a);
    myMapper->writeCPU(0x061A, a);
    myMapper->writeCPU(0x061B, a);
    myMapper->writeCPU(0x061C, a);
    myMapper->writeCPU(0x061D, a);
    myMapper->writeCPU(0x061E, a);
    myMapper->writeCPU(0x061F, a);
    myMapper->writeCPU(0x0620, a);
    myMapper->writeCPU(0x0621, a);
    myMapper->writeCPU(0x0622, a);
    myMapper->writeCPU(0x0623, a);
    myMapper->writeCPU(0x03DF, a);
    opASL_M(0x0000, 1);
    opROL_A(1);
    opASL_M(0x0000, 1);
    opROL_A(1);
    opASL_M(0x0000, 1);
    opROL_A(1);
    opASL_M(0x0000, 1);
    opROL_A(1);
    opASL_M(0x0000, 1);
    opROL_A(1);
    myMapper->writeCPU(0x03A3, a);
    a = myMapper->readCPU(0x0000);
    myMapper->writeCPU(0x0385, a);
    pushAddress(0xDECA);
    jump(0xDED2);
    if (handleReturnAddress(poppedEntry.value, 0xDECA)) return;
    myMapper->writeCPU(SCROLL_FINE, x);
    myMapper->writeCPU(SCROLL_LARGE, y);
    popAddress();
}

void game::SUB_01DED2() {
    y = 0x00;
    a = myMapper->readCPU(0x0385);
    flgC = true;
    opSBC(0x68);
    x = a;
    a = myMapper->readCPU(0x03A3);
    opSBC(0x00);
    if (!flgN) {
        y = a;
        if (a != myMapper->readCPU(0x009F)) {
            goto L_01DEF0;
        }
        x = 0x00;
        y = myMapper->readCPU(0x009F);
        a = 0x01;
        myMapper->writeCPU(0x05D0, a);
    L_01DEF0:
        popAddress();
        return;
    }
    x = 0x00;
    popAddress();
}

void game::SUB_01DEF4() {
    y = 0x00;
    while (true) {
        do {
            a = myMapper->readCPU(0x00A0);
            opCMP(a, myMapper->readCPU(myMapper->readCPU(0x000E) + (myMapper->readCPU((0x000E + 1) & 0x00ff) << 8) + y));
            if (flgZ) {
                goto L_01DF0C;
            }
            if (!flgC) {
                goto L_01DF0C;
            }
            a = myMapper->readCPU(0x000E);
            flgC = false;
            opADC(0x05);
            myMapper->writeCPU(0x000E, a);
        } while (!flgC);
        opINC(0x000F, 1);
    }
L_01DF0C:
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
        //do {
        //L_01DFB8:
        //    opBIT(myMapper->readCPU(PPU_STATUS));
        //} while (!flgV);
    L_01DFB8:
        wait(2);
        a = 0x1F;
        pushAddress(0xDFC1);
        SUB_01FFD2_SwitchCHRBank0();
        pushAddress(0xDFC4);
        jump(0xDBA4);
        if (handleReturnAddress(poppedEntry.value, 0xDFC4)) return;
        a = 0x1E;
        pushAddress(0xDFC9);
        SUB_01FFD2_SwitchCHRBank0();
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
    a = myMapper->readCPU(PPU_STATUS);
    myMapper->writeCPU(PPU_ADDR, 0x3F);
    myMapper->writeCPU(PPU_ADDR, 0x00);
    myMapper->writeCPU(PPU_CTRL, myMapper->readCPU(0x0042));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0661));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0662));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0663));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0664));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0665));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0666));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0667));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0668));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0669));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x066A));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x066B));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x066C));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x066D));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x066E));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x066F));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0670));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0671));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0672));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0673));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0674));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0675));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0676));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0677));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0678));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0679));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x067A));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x067B));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x067C));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x067D));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x067E));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x067F));
    myMapper->writeCPU(PPU_DATA, myMapper->readCPU(0x0680));
    myMapper->writeCPU(PPU_ADDR, 0x3F);
    a = 0x00;
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, a);
    myMapper->writeCPU(PPU_ADDR, a);
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

void game::SUB_01E0C9() {
    a = myMapper->readCPU(0x05A4);
    setLoadFlag(a);
    if (!flgN) {
        if (a < myMapper->readCPU(0x05AA)) {
            goto L_01E0DE;
        }
        myMapper->writeCPU(0x05A4, myMapper->readCPU(0x05AA));
        myMapper->writeCPU(0x05A3, 0x00);
    L_01E0DE:
        flgC = false;
        a = myMapper->readCPU(0x0585);
        opADC(myMapper->readCPU(0x05A3));
        myMapper->writeCPU(0x0585, a);
        a = myMapper->readCPU(0x0385);
        opADC(myMapper->readCPU(0x05A4));
        myMapper->writeCPU(0x0385, a);
        a = myMapper->readCPU(0x03A3);
        opADC(0x00);
        myMapper->writeCPU(0x03A3, a);
    }
    else {
        if (a >= myMapper->readCPU(0x05AB)) {
            goto L_01E10C;
        }
        myMapper->writeCPU(0x05A4, myMapper->readCPU(0x05AB));
        myMapper->writeCPU(0x05A3, 0x00);
    L_01E10C:
        flgC = false;
        a = myMapper->readCPU(0x0585);
        opADC(myMapper->readCPU(0x05A3));
        myMapper->writeCPU(0x0585, a);
        a = myMapper->readCPU(0x0385);
        opADC(myMapper->readCPU(0x05A4));
        myMapper->writeCPU(0x0385, a);
        a = myMapper->readCPU(0x03A3);
        opSBC(0x00);
        myMapper->writeCPU(0x03A3, a);
        if (flgN) {
            goto L_01E14C;
        }
    }
    flgC = false;
    a = myMapper->readCPU(0x05A5);
    opADC(myMapper->readCPU(0x0385));
    myMapper->writeCPU(0x0385, a);
    if (flgC) {
        opINC(0x03A3, 1);
    }
    a = myMapper->readCPU(0x03A3);
    opCMP(a, myMapper->readCPU(SCROLL_LARGE));
    if (!flgZ) {
        if (flgN) {
            goto L_01E14C;
        }
        if (flgC) {
            goto L_01E15B;
        }
    }
    a = myMapper->readCPU(0x0385);
    if (a < myMapper->readCPU(SCROLL_FINE)) {
    L_01E14C:
        myMapper->writeCPU(0x0385, myMapper->readCPU(SCROLL_FINE));
        a = myMapper->readCPU(SCROLL_LARGE);
        myMapper->writeCPU(0x03A3, a);
    }
    else {
    L_01E15B:
        opBIT(myMapper->readCPU(0x05A4));
        if (flgN) {
            goto L_01E17F;
        }
        flgC = true;
        a = myMapper->readCPU(0x05A3);
        opSBC(myMapper->readCPU(0x05A7));
        myMapper->writeCPU(0x05A3, a);
        a = myMapper->readCPU(0x05A4);
        opSBC(myMapper->readCPU(0x05A8));
        if (flgN) {
            goto L_01E176;
        }
        myMapper->writeCPU(0x05A4, a);
        popAddress();
        return;
    }
    do {
    L_01E176:
        a = 0x00;
        myMapper->writeCPU(0x05A3, a);
        myMapper->writeCPU(0x05A4, a);
        popAddress();
        return;
    L_01E17F:
        flgC = false;
        a = myMapper->readCPU(0x05A3);
        opADC(myMapper->readCPU(0x05A7));
        myMapper->writeCPU(0x05A3, a);
        a = myMapper->readCPU(0x05A4);
        opADC(myMapper->readCPU(0x05A8));
    } while (!flgN);
    myMapper->writeCPU(0x05A4, a);
    popAddress();
}

void game::SUB_01E195() {
    a = myMapper->readCPU(0x05CA);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x05C9);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01E1A0;
        }
    }
    popAddress();
    return;
L_01E1A0:
    a = 0xFF;
    myMapper->writeCPU(0x05CF, a);
    opBIT(myMapper->readCPU(0x05CD));
    if (!flgN) {
        if (myMapper->readCPU(0x05AA) == myMapper->readCPU(0x05A4)) {
            goto L_01E1EA;
        }
        flgC = false;
        a = myMapper->readCPU(0x05A3);
        opADC(myMapper->readCPU(0x05A6));
        myMapper->writeCPU(0x05A3, a);
        a = myMapper->readCPU(0x05A4);
        opADC(0x00);
        myMapper->writeCPU(0x05A4, a);
        if (a == myMapper->readCPU(0x05AA)) {
            goto L_01E1EA;
        }
        popAddress();
        return;
    }
    if (myMapper->readCPU(0x05AB) != myMapper->readCPU(0x05A4)) {
        flgC = true;
        a = myMapper->readCPU(0x05A3);
        opSBC(myMapper->readCPU(0x05A6));
        myMapper->writeCPU(0x05A3, a);
        a = myMapper->readCPU(0x05A4);
        opSBC(0x00);
        myMapper->writeCPU(0x05A4, a);
        if (a == myMapper->readCPU(0x05AB)) {
            goto L_01E1EA;
        }
        popAddress();
        return;
    }
L_01E1EA:
    a = 0x00;
    myMapper->writeCPU(0x05A3, a);
    popAddress();
}

void game::SUB_01E1F0() {
    x = myMapper->readCPU(SCROLL_LARGE);
    opINX(1);
    myMapper->writeCPU(0x0000, x);
    a = myMapper->readCPU(SCROLL_FINE);
    opLSR_A(5);
    myMapper->writeCPU(0x0002, a);
    a = myMapper->readCPU(0x0000);
    opASL_A(3);
    opORA(myMapper->readCPU(0x0002));
    if (a != myMapper->readCPU(0x00A0)) {
        jump(0xE20C);
        return;
    }
    popAddress();
}

void game::SUB_01E20C() {
    myMapper->writeCPU(0x00A0, a);
    opAND(0x0F);
    y = a;
    myMapper->writeCPU(0x00A1, 0x00);
    a = myMapper->readCPU(0xE399 + y);
    myMapper->writeCPU(0x0300, a);
    myMapper->writeCPU(0x031C, a);
    myMapper->writeCPU(0x0338, a);
    myMapper->writeCPU(0x0354, a);
    x = myMapper->readCPU(0xE389 + y);
    myMapper->writeCPU(0x0301, x);
    opINX(1);
    myMapper->writeCPU(0x031D, x);
    opINX(1);
    myMapper->writeCPU(0x0339, x);
    opINX(1);
    myMapper->writeCPU(0x0355, x);
    a = myMapper->readCPU(0xE3B9 + y);
    myMapper->writeCPU(0x0370, a);
    myMapper->writeCPU(0x0373, a);
    myMapper->writeCPU(0x0376, a);
    myMapper->writeCPU(0x0379, a);
    myMapper->writeCPU(0x037C, a);
    myMapper->writeCPU(0x037F, a);
    myMapper->writeCPU(0x0382, a);
    flgC = false;
    a = myMapper->readCPU(0xE3A9 + y);
    myMapper->writeCPU(0x0371, a);
    opADC(0x08);
    myMapper->writeCPU(0x0374, a);
    opADC(0x08);
    myMapper->writeCPU(0x0377, a);
    opADC(0x08);
    myMapper->writeCPU(0x037A, a);
    opADC(0x08);
    myMapper->writeCPU(0x037D, a);
    opADC(0x08);
    myMapper->writeCPU(0x0380, a);
    opADC(0x08);
    myMapper->writeCPU(0x0383, a);
    x = 0x02;
    myMapper->writeCPU(0x00B7, x);
    myMapper->writeCPU(0x0000, x);
    y = myMapper->readCPU(0x00A0);
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B0, a);
    pushAddress(0xE281);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE281)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x00A4) + (myMapper->readCPU((0x00A4 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B1, a);
    pushAddress(0xE288);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE288)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x00A6) + (myMapper->readCPU((0x00A6 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B2, a);
    pushAddress(0xE28F);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE28F)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x00A8) + (myMapper->readCPU((0x00A8 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B3, a);
    pushAddress(0xE296);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE296)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x00AA) + (myMapper->readCPU((0x00AA + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B4, a);
    pushAddress(0xE29D);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE29D)) return;
    a = myMapper->readCPU(myMapper->readCPU(0x00AC) + (myMapper->readCPU((0x00AC + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B5, a);
    pushAddress(0xE2A4);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE2A4)) return;
    myMapper->writeCPU(0x00B7, 0x06);
    a = myMapper->readCPU(myMapper->readCPU(0x00AE) + (myMapper->readCPU((0x00AE + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x00B6, a);
    pushAddress(0xE2AF);
    jump(0xE2B7);
    if (handleReturnAddress(poppedEntry.value, 0xE2AF)) return;
    a = 0x00;
    myMapper->writeCPU(0x00B7, a);
    jump(0xE496);
    return;
}

void game::SUB_01E2B7() {
    myMapper->writeCPU(0x0004, a);
    opLSR_A(4);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0004);
    opASL_A(4);
    y = 0x00;
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0008);
    opADC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0008, a);
    myMapper->writeCPU(0x0300 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x031C + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0338 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0354 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    opINX(1);
    myMapper->writeCPU(0x0300 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x031C + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0338 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0354 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    opINX(1);
    if (myMapper->readCPU(0x00B7) == 0x06) {
        goto L_01E33C;
    }
    myMapper->writeCPU(0x0300 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x031C + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0338 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0354 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    opINX(1);
    myMapper->writeCPU(0x0300 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x031C + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0338 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0354 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    opINX(1);
L_01E33C:
    y = myMapper->readCPU(0x0004);
    a = myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y);
    y = myMapper->readCPU(0x0000);
    myMapper->writeCPU(0x0370 + y, a);
    a = y;
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x0000, a);
    y = myMapper->readCPU(0x00A0);
    popAddress();
}

void game::SUB_01E34E() {
    a = myMapper->readCPU(0x00A1);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01E358;
    }
    opCMP(a, 0x70);
    if (flgZ) {
        goto L_01E388;
    }
    if (!flgZ) {
        goto L_01E366;
    }
L_01E358:
    y = 0x70;
    x = 0x15;
    do {
        myMapper->writeCPU(0x00AC + y, myMapper->readCPU(0x0300 + y));
        opINY(1);
        opDEX(1);
    } while (!flgZ);
L_01E366:
    a = myMapper->readCPU(0x00A1);
    y = a;
    flgC = false;
    opADC(0x1C);
    myMapper->writeCPU(0x00A1, a);
    x = 0x00;
    myMapper->writeCPU(0x0000, 0x0E);
    do {
        myMapper->writeCPU(0x0100 + x, myMapper->readCPU(0x0300 + y));
        opINX(1);
        opINY(1);
        a = myMapper->readCPU(0x0300 + y);
        myMapper->writeCPU(0x0100 + x, a);
        opINX(1);
        opINY(1);
        opDEC(0x0000, 1);
    } while (!flgZ);
L_01E388:
    popAddress();
}

void game::SUB_01E3C9() {
    myMapper->writeCPU(0x0000, a);
    opLSR_A(4);
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0000);
    opASL_A(4);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0008);
    opADC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0006);
    myMapper->writeCPU(0x0100 + x, a);
    myMapper->writeCPU(0x0106 + x, a);
    myMapper->writeCPU(0x010C + x, a);
    myMapper->writeCPU(0x0112 + x, a);
    a = myMapper->readCPU(0x0005);
    myMapper->writeCPU(0x0101 + x, a);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0107 + x, a);
    if (flgC) {
        opINC(0x0106 + x, 1);
    }
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x010D + x, a);
    if (flgC) {
        opINC(0x010C + x, 1);
    }
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0113 + x, a);
    if (flgC) {
        opINC(0x0112 + x, 1);
    }
    opCMP(myMapper->readCPU(0x00B7), 0x06);
    if (!flgZ) {
        goto L_01E421;
    }
    myMapper->writeCPU(0x010C + x, 0xFF);
L_01E421:
    y = 0x00;
    myMapper->writeCPU(0x00B7, y);
    myMapper->writeCPU(0x0102 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0103 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0104 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0105 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0108 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0109 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x010A + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x010B + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x010E + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x010F + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0110 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0111 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0114 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0115 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0116 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0117 + x, myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y));
    y = myMapper->readCPU(0x0000);
    myMapper->writeCPU(0x011A + x, myMapper->readCPU(myMapper->readCPU(0x009A) + (myMapper->readCPU((0x009A + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x0118 + x, myMapper->readCPU(0x000A));
    a = myMapper->readCPU(0x0009);
    myMapper->writeCPU(0x0119 + x, a);
    popAddress();
}

void game::SUB_01E496() {
    a = myMapper->readCPU(0x05D3);
    opASL_A(1);
    y = a;
    opINY(1);
    do {
        if (myMapper->readCPU(0x00A0) != myMapper->readCPU(0x0624 + y)) {
            goto L_01E4A8;
        }
        myMapper->writeCPU(0x0614 + y, 0x00);
    L_01E4A8:
        opDEY(1);
    } while (!flgN);
    x = 0x06;
    do {
        a = myMapper->readCPU((0x00B0 + x) & 0x00ff);
        if (a == myMapper->readCPU(0x05BF)) {
            goto L_01E4C7;
        }
        if (a == myMapper->readCPU(0x05C0)) {
            goto L_01E4C7;
        }
        if (a == myMapper->readCPU(0x05C1)) {
            goto L_01E4C7;
        }
        if (a == myMapper->readCPU(0x05C2)) {
            goto L_01E4C7;
        }
    L_01E4C3:
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_01E4C7:
    opPHA();
    a = myMapper->readCPU(0x05D3);
    opASL_A(1);
    y = a;
    opINY(1);
    do {
        a = myMapper->readCPU(0x0614 + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_01E4DA;
        }
        opDEY(1);
    } while (!flgN);
    opPLA();
    goto L_01E4C3;
L_01E4DA:
    opPLA();
    myMapper->writeCPU(0x0614 + y, a);
    myMapper->writeCPU(0x0644 + y, x);
    a = myMapper->readCPU(0x00A0);
    flgC = false;
    opADC(0x09);
    myMapper->writeCPU(0x0624 + y, a);
    a = myMapper->readCPU(0x0301);
    opADC(myMapper->readCPU(0xE552 + x));
    myMapper->writeCPU(0x05D4 + y, a);
    a = myMapper->readCPU(0x0300);
    opADC(myMapper->readCPU(0xE559 + x));
    myMapper->writeCPU(0x05E4 + y, a);
    a = myMapper->readCPU(0x0371);
    opADC(myMapper->readCPU(0xE560 + x));
    myMapper->writeCPU(0x05F4 + y, a);
    a = myMapper->readCPU(0x0370);
    myMapper->writeCPU(0x0604 + y, a);
    goto L_01E4C3;
}

void game::SUB_01E50E() {
    a = myMapper->readCPU(0x003F);
    opAND(myMapper->readCPU(0x05D3));
    opASL_A(1);
    myMapper->writeCPU(0x0001, a);
    y = a;
    x = 0x92;
    pushAddress(0xE51B);
    jump(0xE521);
    if (handleReturnAddress(poppedEntry.value, 0xE51B)) return;
    y = myMapper->readCPU(0x0001);
    opINY(1);
    x = 0xAD;
    SUB_01E521();
    return;
}

void game::SUB_01E521() {
    a = myMapper->readCPU(0x0614 + y);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01E551;
    }
    myMapper->writeCPU(0x0005, myMapper->readCPU(0x05D4 + y));
    myMapper->writeCPU(0x0006, myMapper->readCPU(0x05E4 + y));
    myMapper->writeCPU(0x0009, myMapper->readCPU(0x05F4 + y));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x0604 + y));
    myMapper->writeCPU(0x00B7, myMapper->readCPU(0x0644 + y));
    flgC = false;
    a = myMapper->readCPU(0x0634 + y);
    opADC(0x01);
    myMapper->writeCPU(0x0634 + y, a);
    opAND(0x03);
    flgC = false;
    opADC(myMapper->readCPU(0x0614 + y));
    jump(0xE3C9);
    return;
L_01E551:
    popAddress();
}

void game::SUB_01E567() {
    a = x;
    opLSR_M(0x0095, 1);
    opROR_A(1);
    opLSR_M(0x0095, 1);
    opROR_A(1);
    opLSR_M(0x0095, 1);
    opROR_A(1);
    myMapper->writeCPU(0x0094, a);
    a = y;
    opLSR_M(0x0097, 1);
    opROR_A(1);
    opLSR_M(0x0097, 1);
    opROR_A(1);
    opLSR_M(0x0097, 1);
    opROR_A(1);
    flgC = true;
    opSBC(0x04);
    myMapper->writeCPU(0x0096, a);
    if (flgC) {
        goto L_01E586;
    }
    opDEC(0x0097, 1);
L_01E586:
    popAddress();
}

void game::SUB_01E587() {
    myMapper->writeCPU(0x0000, myMapper->readCPU(0x0095));
    myMapper->writeCPU(0x0002, myMapper->readCPU(0x0097));
    flgC = false;
    a = x;
    opADC(myMapper->readCPU(0x0094));
    if (flgC) {
        opINC(0x0000, 1);
    }
    myMapper->writeCPU(0x0003, a);
    opLSR_M(0x0000, 1);
    opROR_A(1);
    opLSR_M(0x0000, 1);
    opROR_A(1);
    myMapper->writeCPU(0x0001, a);
    flgC = false;
    a = y;
    opADC(myMapper->readCPU(0x0096));
    if (flgC) {
        opINC(0x0002, 1);
    }
    myMapper->writeCPU(0x0004, a);
    opLSR_M(0x0002, 1);
    opROR_A(1);
    opLSR_M(0x0002, 1);
    y = myMapper->readCPU(0x0001);
    opROR_A(1);
    if (flgZ) {
        goto L_01E5D0;
    }
    if (a == 0x06) {
        goto L_01E5EE;
    }
    if (a == 0x05) {
        goto L_01E5E9;
    }
    if (a == 0x04) {
        goto L_01E5E4;
    }
    if (a == 0x03) {
        goto L_01E5DF;
    }
    if (a == 0x02) {
        goto L_01E5DA;
    }
    if (a == 0x01) {
        goto L_01E5D5;
    }
    a = 0x00;
    popAddress();
    return;
L_01E5D0:
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    goto L_01E5F0;
L_01E5D5:
    a = myMapper->readCPU(myMapper->readCPU(0x00A4) + (myMapper->readCPU((0x00A4 + 1) & 0x00ff) << 8) + y);
    goto L_01E5F0;
L_01E5DA:
    a = myMapper->readCPU(myMapper->readCPU(0x00A6) + (myMapper->readCPU((0x00A6 + 1) & 0x00ff) << 8) + y);
    goto L_01E5F0;
L_01E5DF:
    a = myMapper->readCPU(myMapper->readCPU(0x00A8) + (myMapper->readCPU((0x00A8 + 1) & 0x00ff) << 8) + y);
    goto L_01E5F0;
L_01E5E4:
    a = myMapper->readCPU(myMapper->readCPU(0x00AA) + (myMapper->readCPU((0x00AA + 1) & 0x00ff) << 8) + y);
    goto L_01E5F0;
L_01E5E9:
    a = myMapper->readCPU(myMapper->readCPU(0x00AC) + (myMapper->readCPU((0x00AC + 1) & 0x00ff) << 8) + y);
    goto L_01E5F0;
L_01E5EE:
    a = myMapper->readCPU(myMapper->readCPU(0x00AE) + (myMapper->readCPU((0x00AE + 1) & 0x00ff) << 8) + y);
L_01E5F0:
    y = a;
    opLSR_A(4);
    myMapper->writeCPU(0x0008, a);
    a = y;
    opASL_A(4);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0007, a);
    a = myMapper->readCPU(0x0008);
    opADC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0008, a);
    a = myMapper->readCPU(0x0003);
    opAND(0x03);
    myMapper->writeCPU(0x0003, a);
    a = myMapper->readCPU(0x0004);
    opAND(0x03);
    opASL_A(2);
    opORA(myMapper->readCPU(0x0003));
    y = a;
    y = myMapper->readCPU(myMapper->readCPU(0x0007) + (myMapper->readCPU((0x0007 + 1) & 0x00ff) << 8) + y);
    a = myMapper->readCPU(myMapper->readCPU(0x009C) + (myMapper->readCPU((0x009C + 1) & 0x00ff) << 8) + y);
    popAddress();
}

void game::SUB_01E61C() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (!flgZ) {
        goto L_01E651;
    }
    a = 0x20;
    myMapper->writeCPU(0x017B, a);
    myMapper->writeCPU(0x0181, a);
    myMapper->writeCPU(0x017C, 0x4F);
    myMapper->writeCPU(0x0182, 0x6F);
    if (myMapper->readCPU(0x0659) == 0) {
        goto L_01E652;
    }
    a = myMapper->readCPU(0x065A);
    opEOR(0x01);
    myMapper->writeCPU(0x065A, a);
    if (flgZ) {
        goto L_01E652;
    }
    a = 0x00;
    myMapper->writeCPU(0x017D, a);
    myMapper->writeCPU(0x017E, a);
    myMapper->writeCPU(0x0183, a);
    myMapper->writeCPU(0x0184, a);
L_01E651:
    popAddress();
    return;
L_01E652:
    myMapper->writeCPU(0x017D, myMapper->readCPU(0x065B));
    myMapper->writeCPU(0x017E, myMapper->readCPU(0x065C));
    myMapper->writeCPU(0x0183, myMapper->readCPU(0x065D));
    a = myMapper->readCPU(0x065E);
    myMapper->writeCPU(0x0184, a);
    popAddress();
}

void game::SUB_01E66B() {
    x = myMapper->readCPU(0x0051);
    a = myMapper->readCPU((0x005F + x) & 0x00ff);
    if (myMapper->readCPU((0x0065 + x) & 0x00ff) != 0) {
        if (a >= 0x05) {
            goto L_01E684;
        }
        opINC((0x0065 + x) & 0x00ff, 1);
        opINC(0x008D, 1);
        popAddress();
        return;
    }
    if (a < 0x05) {
        goto L_01E684;
    }
    opDEC((0x0065 + x) & 0x00ff, 1);
    opINC(0x008D, 1);
L_01E684:
    popAddress();
}

void game::SUB_01E685() {
    x = myMapper->readCPU(0x0051);
    y = 0x00;
    do {
        flgC = false;
        a = myMapper->readCPU((0x005A + x) & 0x00ff);
        opADC(myMapper->readCPU(0x007F + y));
        while (a >= 0x0A) {
            flgC = true;
            opSBC(0x0A);
            opINC((0x005B + x) & 0x00ff, 1);
        }
        myMapper->writeCPU((0x005A + x) & 0x00ff, a);
        opINX(1);
        opINY(1);
    } while (y != 0x08);
    a = 0x00;
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x0080, a);
    myMapper->writeCPU(0x0081, a);
    myMapper->writeCPU(0x0082, a);
    myMapper->writeCPU(0x0083, a);
    myMapper->writeCPU(0x0084, a);
    myMapper->writeCPU(0x0085, a);
    myMapper->writeCPU(0x0086, a);
    pushAddress(0xE6B7);
    jump(0xE66B);
    if (handleReturnAddress(poppedEntry.value, 0xE6B7)) return;
    SUB_01E6B8();
    return;
}

void game::SUB_01E6B8() {
    a = 0x20;
    myMapper->writeCPU(0x0167, a);
    myMapper->writeCPU(0x0171, a);
    myMapper->writeCPU(0x0168, 0x41);
    myMapper->writeCPU(0x0172, 0x61);
    x = 0x07;
    y = myMapper->readCPU(0x0051);
    do {
        flgC = false;
        a = myMapper->readCPU(0x005A + y);
        opADC(0x01);
        myMapper->writeCPU(0x0169 + x, a);
        a = myMapper->readCPU(0x005A + y);
        opADC(0x0B);
        myMapper->writeCPU(0x0173 + x, a);
        opINY(1);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_01E6E4() {
    a = myMapper->readCPU(0x0091);
    if (a != 0xFF) {
        goto L_01E6EB;
    }
    do {
        popAddress();
        return;
    L_01E6EB:
        opDEC(0x0091, 1);
        if (flgZ) {
            myMapper->writeCPU(0x0091, myMapper->readCPU(0x0658));
            if (myMapper->readCPU(0x05BD) != 0) {
                opDEC(0x05BD, 1);
            }
            opDEC(0x0092, 1);
            if (flgN) {
                myMapper->writeCPU(0x0092, 0x09);
                opDEC(0x0093, 1);
                if (!flgN) {
                    goto L_01E732;
                }
                myMapper->writeCPU(0x0091, 0xFF);
                a = 0x00;
                myMapper->writeCPU(0x05A3, a);
                myMapper->writeCPU(0x05A4, a);
                myMapper->writeCPU(0x05A0, a);
                myMapper->writeCPU(0x05A1, a);
                myMapper->writeCPU(0x05A9, a);
                a = 0xFF;
                myMapper->writeCPU(0x05D2, a);
                myMapper->writeCPU(0x059F, a);
                myMapper->writeCPU(0x059D, a);
                myMapper->writeCPU(0x059E, 0xFB);
                a = 0x1F;
                jump(0xEA1B);
                return;
            }
        L_01E732:
            if (myMapper->readCPU(0x0093) != 0) {
                jump(0xE740);
                return;
            }
            a = 0x12;
            pushAddress(0xE73A);
            jump(0xEA1B);
            if (handleReturnAddress(poppedEntry.value, 0xE73A)) return;
        }
        a = myMapper->readCPU(0x003F);
        opLSR_A(1);
    } while (!flgC);
    SUB_01E740();
    return;
}

void game::SUB_01E740() {
    a = 0x20;
    myMapper->writeCPU(0x017B, a);
    myMapper->writeCPU(0x0181, a);
    myMapper->writeCPU(0x017C, 0x5E);
    myMapper->writeCPU(0x0182, 0x7E);
    flgC = false;
    a = myMapper->readCPU(0x0093);
    opADC(0x01);
    myMapper->writeCPU(0x017D, a);
    a = myMapper->readCPU(0x0092);
    opADC(0x01);
    myMapper->writeCPU(0x017E, a);
    a = myMapper->readCPU(0x0093);
    opADC(0x0B);
    myMapper->writeCPU(0x0183, a);
    a = myMapper->readCPU(0x0092);
    opADC(0x0B);
    myMapper->writeCPU(0x0184, a);
    popAddress();
}

void game::SUB_01E770() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (a == 0x03) {
        goto L_01E779;
    }
    do {
        do {
            popAddress();
            return;
        L_01E779:
            y = myMapper->readCPU(0x0051);
            x = myMapper->readCPU((0x0054 + y) & 0x00ff);
            y = myMapper->readCPU(0x0055 + y);
            a = myMapper->readCPU(0x008E);
            setLoadFlag(a);
        } while (flgZ);
        if (flgN) {
            opINC(0x008E, 1);
            myMapper->writeCPU(0x0000, y);
            a = x;
            opORA(myMapper->readCPU(0x0000));
            if (!flgZ) {
                opDEX(1);
                if (!flgN) {
                    goto L_01E7BC;
                }
                x = 0x09;
                opDEY(1);
                goto L_01E7BC;
            }
            if (myMapper->readCPU(0x059D) != 0) {
                goto L_01E7A4;
            }
            a = 0x01;
            myMapper->writeCPU(0x05D1, a);
            popAddress();
            return;
        L_01E7A4:
            a = 0xFF;
            myMapper->writeCPU(0x05D2, a);
            popAddress();
            return;
        }
        opDEC(0x008E, 1);
        if (y != 0x09) {
            goto L_01E7B4;
        }
    } while (x == 0x09);
L_01E7B4:
    opINX(1);
    if (x != 0x0A) {
        goto L_01E7BC;
    }
    x = 0x00;
    opINY(1);
L_01E7BC:
    myMapper->writeCPU(0x0000, y);
    a = y;
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0055 + y, a);
    myMapper->writeCPU(0x0054 + y, x);
    y = myMapper->readCPU(0x0000);
    SUB_01E7CA();
    return;
}

void game::SUB_01E7CA() {
    a = 0x20;
    myMapper->writeCPU(0x0187, a);
    myMapper->writeCPU(0x018B, a);
    myMapper->writeCPU(0x0188, 0x55);
    a = 0x75;
    myMapper->writeCPU(0x018C, a);
    jump(0xE830);
    return;
}

void game::SUB_01E7DF() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (a == 0x01) {
        goto L_01E7E8;
    }
    do {
        do {
            popAddress();
            return;
        L_01E7E8:
            y = myMapper->readCPU(0x0051);
            x = myMapper->readCPU((0x0052 + y) & 0x00ff);
            y = myMapper->readCPU(0x0053 + y);
            a = myMapper->readCPU(0x0090);
            setLoadFlag(a);
        } while (flgZ);
        if (!flgN) {
            goto L_01E806;
        }
        opINC(0x0090, 1);
        a = x;
        opORA(myMapper->readCPU(0x0053));
    } while (flgZ);
    opDEX(1);
    if (flgN) {
        x = 0x09;
        opDEY(1);
        goto L_01E810;
    L_01E806:
        opDEC(0x0090, 1);
        opINX(1);
        if (x != 0x0A) {
            goto L_01E810;
        }
        x = 0x00;
        opINY(1);
    }
L_01E810:
    myMapper->writeCPU(0x0001, y);
    a = y;
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0053 + y, a);
    myMapper->writeCPU(0x0052 + y, x);
    y = myMapper->readCPU(0x0001);
    SUB_01E81E();
    return;
}

void game::SUB_01E81E() {
    a = 0x20;
    myMapper->writeCPU(0x0187, a);
    myMapper->writeCPU(0x018B, a);
    myMapper->writeCPU(0x0188, 0x4C);
    myMapper->writeCPU(0x018C, 0x6C);
    SUB_01E830();
    return;
}

void game::SUB_01E830() {
    a = y;
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(0x0189, a);
    a = y;
    opADC(0x0B);
    myMapper->writeCPU(0x018D, a);
    a = x;
    opADC(0x01);
    myMapper->writeCPU(0x018A, a);
    a = x;
    opADC(0x0B);
    myMapper->writeCPU(0x018E, a);
    popAddress();
}

void game::SUB_01E84A() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (a == 0x02) {
        goto L_01E853;
    }
    do {
        popAddress();
        return;
    L_01E853:
        y = myMapper->readCPU(0x0051);
        x = myMapper->readCPU((0x0056 + y) & 0x00ff);
        y = myMapper->readCPU(0x0057 + y);
        a = myMapper->readCPU(0x008F);
        setLoadFlag(a);
    } while (flgZ);
    opDEC(0x008F, 1);
    opINX(1);
    if (x != 0x0A) {
        goto L_01E869;
    }
    x = 0x00;
    opINY(1);
L_01E869:
    myMapper->writeCPU(0x0001, y);
    a = y;
    y = myMapper->readCPU(0x0051);
    myMapper->writeCPU(0x0057 + y, a);
    myMapper->writeCPU(0x0056 + y, x);
    y = myMapper->readCPU(0x0001);
    SUB_01E877();
    return;
}

void game::SUB_01E877() {
    a = 0x20;
    myMapper->writeCPU(0x0187, a);
    myMapper->writeCPU(0x018B, a);
    myMapper->writeCPU(0x0188, 0x51);
    a = 0x71;
    myMapper->writeCPU(0x018C, a);
    jump(0xE830);
    return;
}

void game::SUB_01E88C() {
    a = myMapper->readCPU(0x003F);
    opAND(0x03);
    if (flgZ) {
        goto L_01E893;
    }
    do {
        popAddress();
        return;
    L_01E893:
        x = myMapper->readCPU(0x0051);
        a = myMapper->readCPU(0x008D);
        setLoadFlag(a);
    } while (flgZ);
    if (!flgN) {
        opDEC(0x008D, 1);
        a = myMapper->readCPU((0x0058 + x) & 0x00ff);
        if (a == 0x05) {
            popAddress();
            return;
        }
        opINC((0x0058 + x) & 0x00ff, 1);
        a = myMapper->readCPU((0x0058 + x) & 0x00ff);
        opCMP(a, 0x03);
        if (flgC) {
            opSBC(0x01);
            myMapper->writeCPU(0x0000, a);
            jump(0xE8D6);
            return;
        }
        a = 0x01;
        myMapper->writeCPU(0x0000, a);
        jump(0xE8D6);
        return;
    }
    opINC(0x008D, 1);
    a = myMapper->readCPU((0x0058 + x) & 0x00ff);
    setLoadFlag(a);
    if (flgZ) {
        popAddress();
        return;
    }
    opCMP(a, 0x03);
    if (!flgC) {
        goto L_01E8CC;
    }
    opSBC(0x02);
    myMapper->writeCPU(0x0000, a);
    goto L_01E8D0;
L_01E8CC:
    a = 0x00;
    myMapper->writeCPU(0x0000, a);
L_01E8D0:
    pushAddress(0xE8D2);
    jump(0xE8D6);
    if (handleReturnAddress(poppedEntry.value, 0xE8D2)) return;
    opDEC((0x0058 + x) & 0x00ff, 1);
    popAddress();
}

void game::SUB_01E8D6() {
    y = myMapper->readCPU(0x0051);
    x = myMapper->readCPU((0x0058 + y) & 0x00ff);
    a = 0x20;
    myMapper->writeCPU(0x0187, a);
    myMapper->writeCPU(0x018B, a);
    a = myMapper->readCPU(0xE90C + x);
    myMapper->writeCPU(0x0188, a);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x018C, a);
    a = myMapper->readCPU(0x0000);
    opASL_A(2);
    x = a;
    myMapper->writeCPU(0x0189, myMapper->readCPU(0xE912 + x));
    myMapper->writeCPU(0x018A, myMapper->readCPU(0xE913 + x));
    myMapper->writeCPU(0x018D, myMapper->readCPU(0xE914 + x));
    a = myMapper->readCPU(0xE915 + x);
    myMapper->writeCPU(0x018E, a);
    popAddress();
}

void game::SUB_01E92A() {
    a = myMapper->readCPU(0x059C);
    setLoadFlag(a);
    if (!flgZ) {
        if (myMapper->readCPU(0x0044) == 0x10) {
            goto L_01E955;
        }
        a = myMapper->readCPU(0x0599);
        opDEC(0x059A, 1);
        if (!flgZ) {
            goto L_01E952;
        }
        y = myMapper->readCPU(0x059B);
        a = myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0599, a);
        myMapper->writeCPU(0x0044, a);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x008A) + (myMapper->readCPU((0x008A + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x059A, a);
        opINY(1);
        myMapper->writeCPU(0x059B, y);
        popAddress();
        return;
    L_01E952:
        myMapper->writeCPU(0x0044, a);
    }
    popAddress();
    return;
L_01E955:
    a = 0x02;
    myMapper->writeCPU(0x05D1, a);
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
        SUB_01FFE6_SwithPRGBank();
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
    SUB_01FFE6_SwithPRGBank();
    pushAddress(0xEA12);
    jump(0x8000);
    if (handleReturnAddress(poppedEntry.value, 0xEA12)) return;
L_01EA13:
    jump(0xEA3E);
    return;
}

void game::SUB_01EA16() {
    if (a != myMapper->readCPU(0x00FD)) {
        jump(0xEA1B);
        return;
    }
    popAddress();
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
    SUB_01FFE6_SwithPRGBank();
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
    SUB_01FFE6_SwithPRGBank();
    pushAddress(0xEA3D);
    jump(0x800C);
    if (handleReturnAddress(poppedEntry.value, 0xEA3D)) return;
    SUB_01EA3E();
    return;
}

void game::SUB_01EA3E() {
    a = myMapper->readCPU(0x0012);
    SUB_01FFE6_SwithPRGBank();
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
    SUB_01FFD2_SwitchCHRBank0();
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
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x1D;
    pushAddress(0xEABD);
    SUB_01FFAA_SwitchCHRBank1();
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
        myMapper->writeCPU(PPU_CTRL, a);
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
        //do {
        //L_01EB35:
        //    a = myMapper->readCPU(PPU_STATUS);
        //    opAND(0x40);
        //} while (flgZ);
    L_01EB35:
        wait(2);
        a = 0x1F;
        pushAddress(0xEB40);
        SUB_01FFD2_SwitchCHRBank0();
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
        SUB_01FFD2_SwitchCHRBank0();
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

void game::SUB_01F0C6_RestoreBank012A() {
    opPHA();
    a = myMapper->readCPU(0x0012);
    pushAddress(0xF0CB);
    SUB_01FFE6_SwithPRGBank();
    opPLA();
    popAddress();
}

void game::SUB_01F0CE() {
    opPHA();
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF0D5);
    SUB_01FFE6_SwithPRGBank();
    opPLA();
    pushAddress(0xF0D9);
    jump(0x9CF1);
    if (handleReturnAddress(poppedEntry.value, 0xF0D9)) return;
    SUB_01F0DA_RestoreBank013();
    return;
}

void game::SUB_01F0DA_RestoreBank013() {
    a = myMapper->readCPU(0x0013);
    myMapper->writeCPU(0x0012, a);
    SUB_01FFE6_SwithPRGBank();
}

void game::SUB_01F0E1() {
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF0E7);
    SUB_01FFE6_SwithPRGBank();
    pushAddress(0xF0EA);
    jump(0xAE8E);
    if (handleReturnAddress(poppedEntry.value, 0xF0EA)) return;
    SUB_01F0DA_RestoreBank013();
    return;
}

void game::SUB_01F0EE() {
    a = 0x06;
    pushAddress(0xF0F2);
    SUB_01FFE6_SwithPRGBank();
    pushAddress(0xF0F5);
    jump(0xAEDD);
    if (handleReturnAddress(poppedEntry.value, 0xF0F5)) return;
    SUB_01F0C6_RestoreBank012A();
    return;
}

void game::SUB_01F0F9() {
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF0FF);
    SUB_01FFE6_SwithPRGBank();
    pushAddress(0xF102);
    jump(0xB32C);
    if (handleReturnAddress(poppedEntry.value, 0xF102)) return;
    x = 0x08;
    if (myMapper->readCPU(0x0003) >= 0x3C) {
        x = 0x07;
        a = myMapper->readCPU(0x0004);
        if (a >= 0x3C) {
            SUB_01F0DA_RestoreBank013();
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
    a = 0x00;
    myMapper->writeCPU(0x0660, a);
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
    SUB_01F0DA_RestoreBank013();
    return;
L_01F141:
    a = 0x0E;
    pushAddress(0xF145);
    jump(0xF0CE);
    if (handleReturnAddress(poppedEntry.value, 0xF145)) return;
    SUB_01F0DA_RestoreBank013();
    return;
}

void game::SUB_01F149() {
    opPHA();
    a = 0x05;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF150);
    SUB_01FFE6_SwithPRGBank();
    opPLA();
    jump(0x9484);
    return;
}

void game::SUB_01F155() {
    a = 0x06;
    myMapper->writeCPU(0x0012, a);
    pushAddress(0xF15B);
    SUB_01FFE6_SwithPRGBank();
    pushAddress(0xF15E);
    jump(0xB68B);
    if (handleReturnAddress(poppedEntry.value, 0xF15E)) return;
    SUB_01F0DA_RestoreBank013();
    return;
}

void game::SUB_01F162() {
    a = 0x00;
    myMapper->writeCPU(PPU_CTRL, a);
    myMapper->writeCPU(PPU_MASK, a);
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
    SUB_01F0C6_RestoreBank012A();
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
                    SUB_01F0C6_RestoreBank012A();
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
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0xF221);
    jump(0xDBA4);
    if (handleReturnAddress(poppedEntry.value, 0xF221)) return;
    a = myMapper->readCPU(0x0041);
    myMapper->writeCPU(PPU_MASK, a);
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
    if (myMapper->readCPU(0x0087) != 0) {
        myMapper->writeCPU(0x006C, x);
    }
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
    a = myMapper->readCPU(PPU_STATUS);
    a = 0x02;
    myMapper->writeCPU(PPU_OAMDMA, a);
    pushAddress(0xF27F);
    jump(0xDFCE);
    if (handleReturnAddress(poppedEntry.value, 0xF27F)) return;
    a = myMapper->readCPU(0x0040);
    myMapper->writeCPU(PPU_CTRL, a);
    pushAddress(0xF287);
    jump(0xD60E);
    if (handleReturnAddress(poppedEntry.value, 0xF287)) return;
    a = 0x00;
    myMapper->writeCPU(PPU_SCROLL, a);
    myMapper->writeCPU(PPU_SCROLL, a);
    do {
        opBIT(myMapper->readCPU(PPU_STATUS));
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
    SUB_01FFD2_SwitchCHRBank0();
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
    myMapper->writeCPU(PPU_MASK, a);
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

void game::SUB_01F822() {
    pushAddress(0xF824);
    jump(0xE6E4);
    if (handleReturnAddress(poppedEntry.value, 0xF824)) return;
    pushAddress(0xF827);
    jump(0xE685);
    if (handleReturnAddress(poppedEntry.value, 0xF827)) return;
    if (myMapper->readCPU(0x0091) != 0xFF) {
        goto L_01F82F;
    }
    do {
        popAddress();
        return;
    L_01F82F:
        myMapper->writeCPU(0x0658, 0x04);
    } while (myMapper->readCPU(0x0091) != 0x04);
    if (myMapper->readCPU(0x0092) != 0) {
        goto L_01F840;
    }
    opINC(0x008E, 1);
L_01F840:
    opINC(0x0082, 1);
    a = 0x05;
    jump(0xEA1B);
    return;
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
    SUB_01FFD2_SwitchCHRBank0();
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
    myMapper->writeCPU(PPU_MASK, a);
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

void game::SUB_01FE54() {
    opPHA();
    a = myMapper->readCPU(PPU_STATUS);
    myMapper->writeCPU(PPU_OAMDMA, 0x02);
    a = myMapper->readCPU(0x000B);
    setLoadFlag(a);
    if (flgZ) {
        goto L_01FE69;
    }
    pushAddress(0xFE63);
    jump(0xDD2B);
    if (handleReturnAddress(poppedEntry.value, 0xFE63)) return;
    a = myMapper->readCPU(0x0040);
    myMapper->writeCPU(0x2000, a);
L_01FE69:
    pushAddress(0xFE6B);
    jump(0xD60E);
    if (handleReturnAddress(poppedEntry.value, 0xFE6B)) return;
    a = 0x00;
    myMapper->writeCPU(PPU_SCROLL, a);
    myMapper->writeCPU(PPU_SCROLL, a);
    do {
        opBIT(myMapper->readCPU(PPU_STATUS));
    } while (flgV);
    opINC(0x003F, 1);
    pushAddress(0xFE7D);
    jump(0xDB37);
    if (handleReturnAddress(poppedEntry.value, 0xFE7D)) return;
    opPLA();
    return;
}

void game::SUB_01FE80() {
    myMapper->writeCPU(0x0203, 0xFC);
    myMapper->writeCPU(0x0200, 0x1D);
    myMapper->writeCPU(0x0201, 0xFF);
    myMapper->writeCPU(0x0202, 0x00);
    popAddress();
}

void game::SUB_01FE95_SetScroll() {
    a = myMapper->readCPU(PPU_STATUS);
    myMapper->writeCPU(PPU_SCROLL, myMapper->readCPU(SCROLL_FINE));
    myMapper->writeCPU(PPU_SCROLL, 0x00);
    a = myMapper->readCPU(SCROLL_LARGE);
    opAND(0x01);
    if (flgZ) {
        goto L_01FEB1;
    }
    a = myMapper->readCPU(0x0040);
    opORA(0x01);
    myMapper->writeCPU(0x2000, a);
L_01FEB1:
    popAddress();
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
    myMapper->writeCPU(PPU_CTRL, x);
    myMapper->writeCPU(PPU_MASK, x);
    myMapper->writeCPU(PPU_OAMADDR, x);
    myMapper->writeCPU(PPU_OAMADDR, x);
    opDEX(1);
    s = x;
    flgD = false;
    x = 0x02;
    pushAddress(0xFF87);
    SUB_01FF99_InitMapper();
    opINC(0xFF88, 1);
    pushAddress(0xFF8D);
    SUB_01FF99_InitMapper();
    myMapper->writeCPU(APU_FRAMECNT, 0x80);
    a = myMapper->readCPU(APU_STATUS);
    SUB_01C000_StartGame();
}

void game::SUB_01FF99_InitMapper() {
    a = 0x1E;
    pushAddress(0xFF9D);
    SUB_01FFBE_MapperControl();
    a = 0x00;
    pushAddress(0xFFA2);
    SUB_01FFE6_SwithPRGBank();
    a = 0x00;
    pushAddress(0xFFA7);
    SUB_01FFD2_SwitchCHRBank0();
    a = 0x01;
    SUB_01FFAA_SwitchCHRBank1();
}

void game::SUB_01FFAA_SwitchCHRBank1() {
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

void game::SUB_01FFBE_MapperControl() {
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

void game::SUB_01FFD2_SwitchCHRBank0() {
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

void game::SUB_01FFE6_SwithPRGBank() {
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
    case 0x00019F:
        SUB_00019F();
        break;
    case 0x000029:
        SUB_000029();
        break;
    case 0x01CA04:
        SUB_01CA04();
        break;
    case 0x01FE80:
        SUB_01FE80();
        break;
    case 0x01EA16:
        SUB_01EA16();
        break;
    case 0x01F822:
        SUB_01F822();
        break;
    case 0x01CA70:
        SUB_01CA70();
        break;
    case 0x01CA60:
        SUB_01CA60();
        break;
    case 0x01E88C:
        SUB_01E88C();
        break;
    case 0x01E770:
        SUB_01E770();
        break;
    case 0x01E50E:
        SUB_01E50E();
        break;
    case 0x01EA36:
        SUB_01EA36();
        break;
    case 0x01DBB3:
        SUB_01DBB3();
        break;
    case 0x01EA1B:
        SUB_01EA1B();
        break;
    case 0x01DE68:
        SUB_01DE68();
        break;
    case 0x01DB37:
        SUB_01DB37();
        break;
    case 0x01DD59:
        SUB_01DD59();
        break;
    case 0x01C9F6:
        SUB_01C9F6();
        break;
    case 0x000223:
        SUB_000223();
        break;
    case 0x01E9E6:
        SUB_01E9E6();
        break;
    case 0x0002BB:
        SUB_0002BB();
        break;
    case 0x00038B:
        SUB_00038B();
        break;
    case 0x01DC63:
        SUB_01DC63();
        break;
    case 0x01DEF4:
        SUB_01DEF4();
        break;
    case 0x01DD83:
        SUB_01DD83();
        break;
    case 0x0003CF:
        SUB_0003CF();
        break;
    case 0x01DCFD:
        SUB_01DCFD();
        break;
    case 0x000020:
        SUB_000020();
        break;
    case 0x01DBDF:
        SUB_01DBDF();
        break;
    case 0x01E6E4:
        SUB_01E6E4();
        break;
    case 0x01E7DF:
        SUB_01E7DF();
        break;
    case 0x01E84A:
        SUB_01E84A();
        break;
    case 0x01E685:
        SUB_01E685();
        break;
    case 0x01DCD8:
        SUB_01DCD8();
        break;
    case 0x01EA06:
        SUB_01EA06();
        break;
    case 0x01E61C:
        SUB_01E61C();
        break;
    case 0x000B52:
        SUB_000B52();
        break;
    case 0x0004D9:
        SUB_0004D9();
        break;
    case 0x01E1F0:
        SUB_01E1F0();
        break;
    case 0x01E34E:
        SUB_01E34E();
        break;
    case 0x01CA15:
        SUB_01CA15();
        break;
    case 0x01E20C:
        SUB_01E20C();
        break;
    case 0x0017E3:
        SUB_0017E3();
        break;
    case 0x01D60E:
        SUB_01D60E();
        break;
    case 0x000A62:
        SUB_000A62();
        break;
    case 0x000A1A:
        SUB_000A1A();
        break;
    case 0x000A0C:
        SUB_000A0C();
        break;
    case 0x01E195:
        SUB_01E195();
        break;
    case 0x000A11:
        SUB_000A11();
        break;
    case 0x01E587:
        SUB_01E587();
        break;
    case 0x01E0C9:
        SUB_01E0C9();
        break;
    case 0x01DED2:
        SUB_01DED2();
        break;
    case 0x00091A:
        SUB_00091A();
        break;
    case 0x001083:
        SUB_001083();
        break;
    case 0x001156:
        SUB_001156();
        break;
    case 0x0009B5:
        SUB_0009B5();
        break;
    case 0x000A19:
        SUB_000A19();
        break;
    case 0x01E567:
        SUB_01E567();
        break;
    case 0x000B87:
        SUB_000B87();
        break;
    case 0x000B6C:
        SUB_000B6C();
        break;
    case 0x001B88:
        SUB_001B88();
        break;
    case 0x000A40:
        SUB_000A40();
        break;
    case 0x000B9C:
        SUB_000B9C();
        break;
    case 0x001207:
        SUB_001207();
        break;
    case 0x000FE1:
        SUB_000FE1();
        break;
    case 0x00170F:
        SUB_00170F();
        break;
    case 0x00166B:
        SUB_00166B();
        break;
    case 0x0016CF:
        SUB_0016CF();
        break;
    case 0x000D70:
        SUB_000D70();
        break;
    case 0x001064:
        SUB_001064();
        break;
    case 0x001448:
        SUB_001448();
        break;
    case 0x00168B:
        SUB_00168B();
        break;
    case 0x00100D:
        SUB_00100D();
        break;
    case 0x001168:
        SUB_001168();
        break;
    case 0x001B92:
        SUB_001B92();
        break;
    case 0x0012EA:
        SUB_0012EA();
        break;
    case 0x001049:
        SUB_001049();
        break;
    case 0x0013E4:
        SUB_0013E4();
        break;
    case 0x0013E9:
        SUB_0013E9();
        break;
    case 0x0013EF:
        SUB_0013EF();
        break;
    case 0x0015D3:
        SUB_0015D3();
        break;
    case 0x0015C9:
        SUB_0015C9();
        break;
    case 0x001508:
        SUB_001508();
        break;
    case 0x0015DA:
        SUB_0015DA();
        break;
    case 0x0016CE:
        SUB_0016CE();
        break;
    case 0x001733:
        SUB_001733();
        break;
    case 0x00175E:
        SUB_00175E();
        break;
    case 0x0017FC:
        SUB_0017FC();
        break;
    case 0x001BE7:
        SUB_001BE7();
        break;
    case 0x0041B3:
        SUB_0041B3();
        break;
    case 0x004034:
        SUB_004034();
        break;
    case 0x00424D:
        SUB_00424D();
        break;
    case 0x0042E8:
        SUB_0042E8();
        break;
    case 0x0043D9:
        SUB_0043D9();
        break;
    case 0x00441D:
        SUB_00441D();
        break;
    case 0x00402B:
        SUB_00402B();
        break;
    case 0x004C65:
        SUB_004C65();
        break;
    case 0x004540:
        SUB_004540();
        break;
    case 0x005FCD:
        SUB_005FCD();
        break;
    case 0x005BCF:
        SUB_005BCF();
        break;
    case 0x004B5D:
        SUB_004B5D();
        break;
    case 0x004B37:
        SUB_004B37();
        break;
    case 0x004B1E:
        SUB_004B1E();
        break;
    case 0x004B01:
        SUB_004B01();
        break;
    case 0x004B0F:
        SUB_004B0F();
        break;
    case 0x004B06:
        SUB_004B06();
        break;
    case 0x00483B:
        SUB_00483B();
        break;
    case 0x004979:
        SUB_004979();
        break;
    case 0x004896:
        SUB_004896();
        break;
    case 0x0048AD:
        SUB_0048AD();
        break;
    case 0x0048F0:
        SUB_0048F0();
        break;
    case 0x004A0B:
        SUB_004A0B();
        break;
    case 0x00541F:
        SUB_00541F();
        break;
    case 0x0054F3:
        SUB_0054F3();
        break;
    case 0x004AAA:
        SUB_004AAA();
        break;
    case 0x004B0E:
        SUB_004B0E();
        break;
    case 0x004B45:
        SUB_004B45();
        break;
    case 0x004C9D:
        SUB_004C9D();
        break;
    case 0x004C82:
        SUB_004C82();
        break;
    case 0x005F39:
        SUB_005F39();
        break;
    case 0x004D50:
        SUB_004D50();
        break;
    case 0x004EF3:
        SUB_004EF3();
        break;
    case 0x004F85:
        SUB_004F85();
        break;
    case 0x0050AD:
        SUB_0050AD();
        break;
    case 0x00513D:
        SUB_00513D();
        break;
    case 0x0050AE:
        SUB_0050AE();
        break;
    case 0x00559F:
        SUB_00559F();
        break;
    case 0x005387:
        SUB_005387();
        break;
    case 0x005962:
        SUB_005962();
        break;
    case 0x005838:
        SUB_005838();
        break;
    case 0x005BBB:
        SUB_005BBB();
        break;
    case 0x005B37:
        SUB_005B37();
        break;
    case 0x0055FE:
        SUB_0055FE();
        break;
    case 0x00550C:
        SUB_00550C();
        break;
    case 0x005B17:
        SUB_005B17();
        break;
    case 0x00542C:
        SUB_00542C();
        break;
    case 0x0053A9:
        SUB_0053A9();
        break;
    case 0x0058FE:
        SUB_0058FE();
        break;
    case 0x005903:
        SUB_005903();
        break;
    case 0x005909:
        SUB_005909();
        break;
    case 0x005AE4:
        SUB_005AE4();
        break;
    case 0x005ADA:
        SUB_005ADA();
        break;
    case 0x005A2C:
        SUB_005A2C();
        break;
    case 0x005F43:
        SUB_005F43();
        break;
    case 0x005AEB:
        SUB_005AEB();
        break;
    case 0x005B7A:
        SUB_005B7A();
        break;
    case 0x005BE8:
        SUB_005BE8();
        break;
    case 0x005F9E:
        SUB_005F9E();
        break;
    case 0x01E3C9:
        SUB_01E3C9();
        break;
    case 0x0081B0:
        SUB_0081B0();
        break;
    case 0x008036:
        SUB_008036();
        break;
    case 0x00821A:
        SUB_00821A();
        break;
    case 0x0082BF:
        SUB_0082BF();
        break;
    case 0x0083A3:
        SUB_0083A3();
        break;
    case 0x0083D7:
        SUB_0083D7();
        break;
    case 0x00802D:
        SUB_00802D();
        break;
    case 0x008B93:
        SUB_008B93();
        break;
    case 0x0084CE:
        SUB_0084CE();
        break;
    case 0x009A10:
        SUB_009A10();
        break;
    case 0x00968C:
        SUB_00968C();
        break;
    case 0x008AB1:
        SUB_008AB1();
        break;
    case 0x008A8B:
        SUB_008A8B();
        break;
    case 0x008A72:
        SUB_008A72();
        break;
    case 0x008A55:
        SUB_008A55();
        break;
    case 0x008A63:
        SUB_008A63();
        break;
    case 0x008A5A:
        SUB_008A5A();
        break;
    case 0x008796:
        SUB_008796();
        break;
    case 0x0088CD:
        SUB_0088CD();
        break;
    case 0x0087F1:
        SUB_0087F1();
        break;
    case 0x008808:
        SUB_008808();
        break;
    case 0x008844:
        SUB_008844();
        break;
    case 0x00895F:
        SUB_00895F();
        break;
    case 0x009130:
        SUB_009130();
        break;
    case 0x0091E2:
        SUB_0091E2();
        break;
    case 0x0089FE:
        SUB_0089FE();
        break;
    case 0x008A62:
        SUB_008A62();
        break;
    case 0x008A99:
        SUB_008A99();
        break;
    case 0x008BCB:
        SUB_008BCB();
        break;
    case 0x008BB0:
        SUB_008BB0();
        break;
    case 0x00995E:
        SUB_00995E();
        break;
    case 0x009968:
        SUB_009968();
        break;
    case 0x00959D:
        SUB_00959D();
        break;
    case 0x009601:
        SUB_009601();
        break;
    case 0x008E71:
        SUB_008E71();
        break;
    case 0x0090B3:
        SUB_0090B3();
        break;
    case 0x008F5F:
        SUB_008F5F();
        break;
    case 0x00926F:
        SUB_00926F();
        break;
    case 0x009000:
        SUB_009000();
        break;
    case 0x0091FB:
        SUB_0091FB();
        break;
    case 0x00913D:
        SUB_00913D();
        break;
    case 0x009513:
        SUB_009513();
        break;
    case 0x009465:
        SUB_009465();
        break;
    case 0x00951D:
        SUB_00951D();
        break;
    case 0x009524:
        SUB_009524();
        break;
    case 0x0095BA:
        SUB_0095BA();
        break;
    case 0x009600:
        SUB_009600();
        break;
    case 0x009550:
        SUB_009550();
        break;
    case 0x009094:
        SUB_009094();
        break;
    case 0x0096A5:
        SUB_0096A5();
        break;
    case 0x0099D1:
        SUB_0099D1();
        break;
    case 0x00C1B0:
        SUB_00C1B0();
        break;
    case 0x00C036:
        SUB_00C036();
        break;
    case 0x00C1F0:
        SUB_00C1F0();
        break;
    case 0x00C28B:
        SUB_00C28B();
        break;
    case 0x00C376:
        SUB_00C376();
        break;
    case 0x00C39A:
        SUB_00C39A();
        break;
    case 0x00C02D:
        SUB_00C02D();
        break;
    case 0x00CAFF:
        SUB_00CAFF();
        break;
    case 0x00C44F:
        SUB_00C44F();
        break;
    case 0x00D5F7:
        SUB_00D5F7();
        break;
    case 0x00D3F0:
        SUB_00D3F0();
        break;
    case 0x00CA3A:
        SUB_00CA3A();
        break;
    case 0x00CA14:
        SUB_00CA14();
        break;
    case 0x00C9FB:
        SUB_00C9FB();
        break;
    case 0x00C9E3:
        SUB_00C9E3();
        break;
    case 0x00C9F1:
        SUB_00C9F1();
        break;
    case 0x00C9E8:
        SUB_00C9E8();
        break;
    case 0x00C717:
        SUB_00C717();
        break;
    case 0x00C856:
        SUB_00C856();
        break;
    case 0x00C772:
        SUB_00C772();
        break;
    case 0x00C789:
        SUB_00C789();
        break;
    case 0x00C7CD:
        SUB_00C7CD();
        break;
    case 0x00C8E8:
        SUB_00C8E8();
        break;
    case 0x00CF8A:
        SUB_00CF8A();
        break;
    case 0x00D049:
        SUB_00D049();
        break;
    case 0x00C987:
        SUB_00C987();
        break;
    case 0x00C9F0:
        SUB_00C9F0();
        break;
    case 0x00CA22:
        SUB_00CA22();
        break;
    case 0x00CB37:
        SUB_00CB37();
        break;
    case 0x00CB1C:
        SUB_00CB1C();
        break;
    case 0x00D3DC:
        SUB_00D3DC();
        break;
    case 0x00D54A:
        SUB_00D54A();
        break;
    case 0x00D336:
        SUB_00D336();
        break;
    case 0x00CF4E:
        SUB_00CF4E();
        break;
    case 0x00CC75:
        SUB_00CC75();
        break;
    case 0x00D0D0:
        SUB_00D0D0();
        break;
    case 0x00D063:
        SUB_00D063();
        break;
    case 0x00D378:
        SUB_00D378();
        break;
    case 0x00CD68:
        SUB_00CD68();
        break;
    case 0x00CE88:
        SUB_00CE88();
        break;
    case 0x00CF29:
        SUB_00CF29();
        break;
    case 0x00D1CA:
        SUB_00D1CA();
        break;
    case 0x00CF97:
        SUB_00CF97();
        break;
    case 0x00D288:
        SUB_00D288();
        break;
    case 0x00D340:
        SUB_00D340();
        break;
    case 0x00D554:
        SUB_00D554();
        break;
    case 0x00D347:
        SUB_00D347();
        break;
    case 0x00D409:
        SUB_00D409();
        break;
    case 0x00D5BD:
        SUB_00D5BD();
        break;
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
    case 0x017453:
        SUB_017453();
        break;
    case 0x015484:
        SUB_015484();
        break;
    case 0x016437:
        SUB_016437();
        break;
    case 0x01F162:
        SUB_01F162();
        break;
    case 0x01DD0B:
        SUB_01DD0B();
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
    case 0x0159A8:
        SUB_0159A8();
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
    case 0x016489:
        SUB_016489();
        break;
    case 0x01F0CE:
        SUB_01F0CE();
        break;
    case 0x016477:
        SUB_016477();
        break;
    case 0x0164D5:
        SUB_0164D5();
        break;
    case 0x0165ED:
        SUB_0165ED();
        break;
    case 0x01DBA4:
        SUB_01DBA4();
        break;
    case 0x016B9D:
        SUB_016B9D();
        break;
    case 0x01673E:
        SUB_01673E();
        break;
    case 0x016679:
        SUB_016679();
        break;
    case 0x016699:
        SUB_016699();
        break;
    case 0x0166B4:
        SUB_0166B4();
        break;
    case 0x016BCF:
        SUB_016BCF();
        break;
    case 0x01686A:
        SUB_01686A();
        break;
    case 0x016ADC:
        SUB_016ADC();
        break;
    case 0x016C5E:
        SUB_016C5E();
        break;
    case 0x016A1B:
        SUB_016A1B();
        break;
    case 0x016BB5:
        SUB_016BB5();
        break;
    case 0x0167A0:
        SUB_0167A0();
        break;
    case 0x0167D1:
        SUB_0167D1();
        break;
    case 0x016762:
        SUB_016762();
        break;
    case 0x016785:
        SUB_016785();
        break;
    case 0x017281:
        SUB_017281();
        break;
    case 0x016E3E:
        SUB_016E3E();
        break;
    case 0x0170BA:
        SUB_0170BA();
        break;
    case 0x016CAC:
        SUB_016CAC();
        break;
    case 0x0170D0:
        SUB_0170D0();
        break;
    case 0x0170BC:
        SUB_0170BC();
        break;
    case 0x0172D5:
        SUB_0172D5();
        break;
    case 0x01DF13:
        SUB_01DF13();
        break;
    case 0x0174D2:
        SUB_0174D2();
        break;
    case 0x0175A6:
        SUB_0175A6();
        break;
    case 0x0174FA:
        SUB_0174FA();
        break;
    case 0x01754A:
        SUB_01754A();
        break;
    case 0x0176CC:
        SUB_0176CC();
        break;
    case 0x017533:
        SUB_017533();
        break;
    case 0x01F356:
        SUB_01F356();
        break;
    case 0x01F89D:
        SUB_01F89D();
        break;
    case 0x01DF61:
        SUB_01DF61();
        break;
    case 0x0177D6:
        SUB_0177D6();
        break;
    case 0x017617:
        SUB_017617();
        break;
    case 0x01764D:
        SUB_01764D();
        break;
    case 0x017758:
        SUB_017758();
        break;
    case 0x01BAFC:
        SUB_01BAFC();
        break;
    case 0x019D50:
        SUB_019D50();
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
    case 0x019F13:
        SUB_019F13();
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
    case 0x01BB88:
        SUB_01BB88();
        break;
    case 0x01BBDD:
        SUB_01BBDD();
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
    case 0x01BC6F:
        SUB_01BC6F();
        break;
    case 0x01BE18:
        SUB_01BE18();
        break;
    case 0x01BD9A:
        SUB_01BD9A();
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
    case 0x01DB89:
        SUB_01DB89();
        break;
    case 0x01DBBA:
        SUB_01DBBA();
        break;
    case 0x01E92A:
        SUB_01E92A();
        break;
    case 0x01DBEB:
        SUB_01DBEB();
        break;
    case 0x01E6B8:
        SUB_01E6B8();
        break;
    case 0x01E740:
        SUB_01E740();
        break;
    case 0x01E81E:
        SUB_01E81E();
        break;
    case 0x01E7CA:
        SUB_01E7CA();
        break;
    case 0x01E877:
        SUB_01E877();
        break;
    case 0x01DFAC:
        SUB_01DFAC();
        break;
    case 0x01E2B7:
        SUB_01E2B7();
        break;
    case 0x01E496:
        SUB_01E496();
        break;
    case 0x01E521:
        SUB_01E521();
        break;
    case 0x01E66B:
        SUB_01E66B();
        break;
    case 0x01E830:
        SUB_01E830();
        break;
    case 0x01E8D6:
        SUB_01E8D6();
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
    case 0x01AEDD:
        SUB_01AEDD();
        break;
    case 0x01B32C:
        SUB_01B32C();
        break;
    case 0x01F149:
        SUB_01F149();
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
    case 0x01DD2B:
        SUB_01DD2B();
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
    case 0x000000:
        SUB_000000();
        break;
    case 0x004000:
        SUB_004000();
        break;
    case 0x01FE54:
        SUB_01FE54();
        break;
    case 0x01CDDF:
        SUB_01CDDF();
        break;
    case 0x01CD58:
        SUB_01CD58();
        break;
    case 0x01CAC6:
        SUB_01CAC6();
        break;
    case 0x01CAC5:
        SUB_01CAC5();
        break;
    case 0x01CBA5:
        SUB_01CBA5();
        break;
    case 0x01CE23:
        SUB_01CE23();
        break;
    case 0x01CFB3:
        SUB_01CFB3();
        break;
    case 0x01D382:
        SUB_01D382();
        break;
    case 0x000B93:
        SUB_000B93();
        break;
    case 0x00122F:
        SUB_00122F();
        break;
    case 0x0012FB:
        SUB_0012FB();
        break;
    case 0x001466:
        SUB_001466();
        break;
    case 0x00154B:
        SUB_00154B();
        break;
    case 0x0015EC:
        SUB_0015EC();
        break;
    case 0x001606:
        SUB_001606();
        break;
    case 0x0013D6:
        SUB_0013D6();
        break;
    case 0x00172F:
        SUB_00172F();
        break;
    case 0x001753:
        SUB_001753();
        break;
    case 0x00174C:
        SUB_00174C();
        break;
    case 0x001745:
        SUB_001745();
        break;
    case 0x00175A:
        SUB_00175A();
        break;
    case 0x001775:
        SUB_001775();
        break;
    case 0x001723:
        SUB_001723();
        break;
    case 0x00177C:
        SUB_00177C();
        break;
    case 0x001783:
        SUB_001783();
        break;
    case 0x0010F8:
        SUB_0010F8();
        break;
    case 0x0013A3:
        SUB_0013A3();
        break;
    case 0x000BD0:
        SUB_000BD0();
        break;
    case 0x000CE9:
        SUB_000CE9();
        break;
    case 0x000CAD:
        SUB_000CAD();
        break;
    case 0x000C41:
        SUB_000C41();
        break;
    case 0x00179F:
        SUB_00179F();
        break;
    case 0x00178A:
        SUB_00178A();
        break;
    case 0x0017B4:
        SUB_0017B4();
        break;
    case 0x0017C9:
        SUB_0017C9();
        break;
    case 0x000D87:
        SUB_000D87();
        break;
    case 0x000D32:
        SUB_000D32();
        break;
    case 0x000D3E:
        SUB_000D3E();
        break;
    case 0x000D58:
        SUB_000D58();
        break;
    case 0x000D64:
        SUB_000D64();
        break;
    case 0x0012DE:
        SUB_0012DE();
        break;
    case 0x0012EB:
        SUB_0012EB();
        break;
    case 0x004CA9:
        SUB_004CA9();
        break;
    case 0x005793:
        SUB_005793();
        break;
    case 0x00598A:
        SUB_00598A();
        break;
    case 0x005A6F:
        SUB_005A6F();
        break;
    case 0x005AFD:
        SUB_005AFD();
        break;
    case 0x0058F0:
        SUB_0058F0();
        break;
    case 0x005493:
        SUB_005493();
        break;
    case 0x0058BD:
        SUB_0058BD();
        break;
    case 0x004D79:
        SUB_004D79();
        break;
    case 0x004D2A:
        SUB_004D2A();
        break;
    case 0x004D36:
        SUB_004D36();
        break;
    case 0x004CB2:
        SUB_004CB2();
        break;
    case 0x004CD2:
        SUB_004CD2();
        break;
    case 0x004FD8:
        SUB_004FD8();
        break;
    case 0x004FED:
        SUB_004FED();
        break;
    case 0x005319:
        SUB_005319();
        break;
    case 0x004F75:
        SUB_004F75();
        break;
    case 0x004F7D:
        SUB_004F7D();
        break;
    case 0x004FA0:
        SUB_004FA0();
        break;
    case 0x0055D3:
        SUB_0055D3();
        break;
    case 0x0055DF:
        SUB_0055DF();
        break;
    case 0x0055EB:
        SUB_0055EB();
        break;
    case 0x005629:
        SUB_005629();
        break;
    case 0x005130:
        SUB_005130();
        break;
    case 0x005104:
        SUB_005104();
        break;
    case 0x0050D5:
        SUB_0050D5();
        break;
    case 0x0050ED:
        SUB_0050ED();
        break;
    case 0x005294:
        SUB_005294();
        break;
    case 0x005254:
        SUB_005254();
        break;
    case 0x005207:
        SUB_005207();
        break;
    case 0x0055C7:
        SUB_0055C7();
        break;
    case 0x004D67:
        SUB_004D67();
        break;
    case 0x005775:
        SUB_005775();
        break;
    case 0x00588C:
        SUB_00588C();
        break;
    case 0x008000:
        SUB_008000();
        break;
    case 0x008BD7:
        SUB_008BD7();
        break;
    case 0x0093C3:
        SUB_0093C3();
        break;
    case 0x0094A8:
        SUB_0094A8();
        break;
    case 0x009536:
        SUB_009536();
        break;
    case 0x009341:
        SUB_009341();
        break;
    case 0x009182:
        SUB_009182();
        break;
    case 0x008FE6:
        SUB_008FE6();
        break;
    case 0x008FF3:
        SUB_008FF3();
        break;
    case 0x009029:
        SUB_009029();
        break;
    case 0x0092BE:
        SUB_0092BE();
        break;
    case 0x0092EE:
        SUB_0092EE();
        break;
    case 0x008D53:
        SUB_008D53();
        break;
    case 0x008D70:
        SUB_008D70();
        break;
    case 0x008E0C:
        SUB_008E0C();
        break;
    case 0x008E29:
        SUB_008E29();
        break;
    case 0x008C0C:
        SUB_008C0C();
        break;
    case 0x008BE1:
        SUB_008BE1();
        break;
    case 0x008EC3:
        SUB_008EC3();
        break;
    case 0x008ED5:
        SUB_008ED5();
        break;
    case 0x008EAF:
        SUB_008EAF();
        break;
    case 0x009615:
        SUB_009615();
        break;
    case 0x009627:
        SUB_009627();
        break;
    case 0x009337:
        SUB_009337();
        break;
    case 0x008F1E:
        SUB_008F1E();
        break;
    case 0x008C32:
        SUB_008C32();
        break;
    case 0x008C47:
        SUB_008C47();
        break;
    case 0x009297:
        SUB_009297();
        break;
    case 0x008CB1:
        SUB_008CB1();
        break;
    case 0x008CCE:
        SUB_008CCE();
        break;
    case 0x00C000:
        SUB_00C000();
        break;
    case 0x00CB43:
        SUB_00CB43();
        break;
    case 0x00D1E6:
        SUB_00D1E6();
        break;
    case 0x00D2CB:
        SUB_00D2CB();
        break;
    case 0x00D35E:
        SUB_00D35E();
        break;
    case 0x00D164:
        SUB_00D164();
        break;
    case 0x00CFF1:
        SUB_00CFF1();
        break;
    case 0x00D0FA:
        SUB_00D0FA();
        break;
    case 0x00D124:
        SUB_00D124();
        break;
    case 0x00CB4D:
        SUB_00CB4D();
        break;
    case 0x00CBAB:
        SUB_00CBAB();
        break;
    case 0x00CD5D:
        SUB_00CD5D();
        break;
    case 0x00CD64:
        SUB_00CD64();
        break;
    case 0x00CD8E:
        SUB_00CD8E();
        break;
    case 0x00CBF3:
        SUB_00CBF3();
        break;
    case 0x00CCA1:
        SUB_00CCA1();
        break;
    case 0x00CCBE:
        SUB_00CCBE();
        break;
    case 0x014000:
        SUB_014000();
        break;
    case 0x016E75:
        SUB_016E75();
        break;
    case 0x016EB0:
        SUB_016EB0();
        break;
    case 0x016EEB:
        SUB_016EEB();
        break;
    case 0x016F1B:
        SUB_016F1B();
        break;
    case 0x016F4B:
        SUB_016F4B();
        break;
    case 0x016F7B:
        SUB_016F7B();
        break;
    case 0x016FB1:
        SUB_016FB1();
        break;
    case 0x016FE7:
        SUB_016FE7();
        break;
    case 0x01701D:
        SUB_01701D();
        break;
    case 0x017050:
        SUB_017050();
        break;
    case 0x017085:
        SUB_017085();
        break;
    case 0x0170E2:
        SUB_0170E2();
        break;
    case 0x01713E:
        SUB_01713E();
        break;
    case 0x01716F:
        SUB_01716F();
        break;
    case 0x0171B3:
        SUB_0171B3();
        break;
    case 0x0171DC:
        SUB_0171DC();
        break;
    case 0x017205:
        SUB_017205();
        break;
    default:
		string mapperMode = myMapper->getMapperMode();
        printf("Unhandled jump to address: %04X\n", target);
		exit(1);
    }
}
