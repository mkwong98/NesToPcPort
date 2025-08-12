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
    if (scanline == 32) {
        a = myMapper->readCPU(0x0018);
        opORA(myMapper->readCPU(0x0000));
        myMapper->writeCPU(0x2000, a);
        myMapper->writeCPU(0x2005, myMapper->readCPU(0x0017));
        a = 0x00;
        myMapper->writeCPU(0x2005, a);
    }
}

void game::reset() {
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2001, a);
L_000008:
    if (!(myMapper->readCPU(0x2002) & 0x80)) {
        goto L_000008;
    }
    flgI = true;
    flgD = false;
    s = 0xFF;
    x = 0x12;
    a = 0x00;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        opINX(1);
    } while (!flgZ);
    x = 0x02;
    do {
        if (myMapper->readCPU(0x07FA + x) != myMapper->readCPU(0xC078 + x)) {
            goto L_00002A;
        }
        opDEX(1);
    } while (!flgN);
    if (flgN) {
        goto L_00006D;
    }
L_00002A:
    x = 0x00;
    a = x;
    do {
        myMapper->writeCPU((0x0000 + x) & 0x00ff, a);
        myMapper->writeCPU(0x0700 + x, a);
        opINX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0015, 0x32);
    do {
        a = 0x32;
        pushAddress(0x00003B);
        SUB_0016D4();
        if (poppedEntry.value != 0x00003B) return;
        myMapper->writeCPU(0x0046, 0x00);
        pushAddress(0x000042);
        SUB_00056F();
        if (poppedEntry.value != 0x000042) return;
        opDEC(0x0015, 1);
    } while (!flgZ);
    x = 0x0E;
    do {
        myMapper->writeCPU(0x0629 + x, myMapper->readCPU(0xC07B + x));
        opDEX(1);
    } while (!flgN);
    x = 0x04;
    do {
        myMapper->writeCPU((0x0003 + x) & 0x00ff, 0x00);
        opDEX(1);
    } while (!flgN);
    a = 0x00;
    pushAddress(0x00005F);
    SUB_0016D4();
    if (poppedEntry.value != 0x00005F) return;
    x = 0x02;
    do {
        myMapper->writeCPU(0x07FA + x, myMapper->readCPU(0xC078 + x));
        opDEX(1);
    } while (!flgN);
L_00006D:
    myMapper->writeCPU(0x0001, 0x1E);
    myMapper->writeCPU(0x0000, 0x90);
    SUB_0031CA();
    return;
}

void game::nmi() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    myMapper->writeCPU(0x2003, 0x00);
    myMapper->writeCPU(0x4014, 0x02);
    if (myMapper->readCPU(0x0052) != myMapper->readCPU(0x0053)) {
        pushAddress(0x00009F);
        SUB_000172();
        if (poppedEntry.value != 0x00009F) return;
    }
    pushAddress(0x0000A2);
    SUB_001603();
    if (poppedEntry.value != 0x0000A2) return;
    pushAddress(0x0000A5);
    SUB_00178E();
    if (poppedEntry.value != 0x0000A5) return;
    opINC(0x0019, 1);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x2005, a);
    myMapper->writeCPU(0x2005, a);
    pushAddress(0x0000BC);
    SUB_003FF7();
    if (poppedEntry.value != 0x0000BC) return;
    myMapper->writeCPU(0x0002, 0x01);
    a = myMapper->readCPU(0x0016);
    setLoadFlag(a);
    if (flgZ) {
        myConsole->cpu.needWaitScanline = false;
        goto L_0000E7;
    }
    myConsole->cpu.needWaitScanline = true;
    myConsole->cpu.waitScanline = 32;
//L_0000C7:
//    if (myMapper->readCPU(0x2002) & 0x80) {
//        goto L_0000C7;
//    }
//    x = 0x04;
//    y = 0xC6;
//    do {
//        do {
//            opDEY(1);
//        } while (!flgZ);
//        opDEX(1);
//    } while (!flgZ);

L_0000E7:
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    return;
}

void game::SUB_0000F0() {
    a = myMapper->readCPU(0x0000);
    opAND(0x7F);
    SUB_0000F4();
    return;
}

void game::SUB_0000F4() {
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x0000, a);
    popAddress();
}

void game::SUB_0000FA() {
    a = myMapper->readCPU(0x0000);
    opORA(0x80);
    if (!flgZ) {
        SUB_0000F4();
        return;
    }
    SUB_000100();
    return;
}

void game::SUB_000100() {
    a = 0x00;
    SUB_000102();
    return;
}

void game::SUB_000102() {
    opPHA();
    pushAddress(0x000103);
    SUB_00345B();
    if (poppedEntry.value != 0x000103) return;
    opPLA();
    myMapper->writeCPU(0x2001, a);
    popAddress();
}

void game::SUB_00010B() {
    a = myMapper->readCPU(0x0001);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_000102();
        return;
    }
    SUB_00010F();
    return;
}

void game::SUB_00010F() {
    pushAddress(0x00010F);
    SUB_00014A();
    if (poppedEntry.value != 0x00010F) return;
    y = 0x00;
    do {
        myMapper->writeCPU(0x0300 + x, myMapper->readCPU(0x0057 + y));
        opINX(1);
        opINY(1);
    } while (y != myMapper->readCPU(0x0056));
    myMapper->writeCPU(0x0053, x);
    popAddress();
}

void game::SUB_000123() {
    a = 0x57;
    y = 0x00;
    SUB_000127();
    return;
}

void game::SUB_000127() {
    myMapper->writeCPU(0x0021, a);
    myMapper->writeCPU(0x0022, y);
    a = x;
    opPHA();
    y = 0x02;
    a = myMapper->readCPU(myMapper->readCPU(0x0021) + (myMapper->readCPU((0x0021 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x0012, a);
    x = myMapper->readCPU(0x0053);
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x0021) + (myMapper->readCPU((0x0021 + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0300 + x, a);
        opINX(1);
        opINY(1);
    } while (y != myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0053, x);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_00014A() {
    x = myMapper->readCPU(0x0053);
    myMapper->writeCPU(0x0012, 0x00);
    a = myMapper->readCPU(0x0055);
    opASL_A(4);
    opROL_M(0x0012, 1);
    opASL_A(1);
    opROL_M(0x0012, 1);
    opORA(myMapper->readCPU(0x0054));
    opPHA();
    a = myMapper->readCPU(0x0012);
    opORA(0x20);
    myMapper->writeCPU(0x0300 + x, a);
    opINX(1);
    opPLA();
    myMapper->writeCPU(0x0300 + x, a);
    opINX(1);
    myMapper->writeCPU(0x0300 + x, myMapper->readCPU(0x0056));
    opINX(1);
    popAddress();
}

void game::SUB_000172() {
    a = y;
    opPHA();
    a = x;
    opPHA();
    pushAddress(0x000176);
    SUB_00017E();
    if (poppedEntry.value != 0x000176) return;
    opPLA();
    x = a;
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_00017E() {
    do {
        x = myMapper->readCPU(0x0052);
        a = myMapper->readCPU(0x0300 + x);
        opINX(1);
        myMapper->writeCPU(0x0050, a);
        myMapper->writeCPU(0x2006, a);
        a = myMapper->readCPU(0x0300 + x);
        opINX(1);
        myMapper->writeCPU(0x2006, a);
        y = myMapper->readCPU(0x0300 + x);
        opINX(1);
        do {
            a = myMapper->readCPU(0x0300 + x);
            opINX(1);
            myMapper->writeCPU(0x2007, a);
            opDEY(1);
        } while (!flgZ);
        a = myMapper->readCPU(0x0050);
        if (a != 0x3F) {
            goto L_0001B4;
        }
        myMapper->writeCPU(0x2006, 0x3F);
        a = 0x00;
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
        myMapper->writeCPU(0x2006, a);
    L_0001B4:
        myMapper->writeCPU(0x0052, x);
    } while (x != myMapper->readCPU(0x0053));
    popAddress();
}

void game::SUB_0001BB() {
    myMapper->writeCPU(0x00F2, 0x20);
    pushAddress(0x0001BF);
    SUB_00051D();
    if (poppedEntry.value != 0x0001BF) return;
    pushAddress(0x0001C2);
    SUB_00052F();
    if (poppedEntry.value != 0x0001C2) return;
    myMapper->writeCPU(0x00CD, 0xFF);
    myMapper->writeCPU(0x0023, 0xA3);
    myMapper->writeCPU(0x0024, 0xC4);
    a = 0x80;
    myMapper->writeCPU(0x0091, a);
    myMapper->writeCPU(0x0488, a);
    myMapper->writeCPU(0x009A, 0x70);
    pushAddress(0x0001DC);
    SUB_000D40();
    if (poppedEntry.value != 0x0001DC) return;
    a = 0x00;
    myMapper->writeCPU(0x0041, a);
    myMapper->writeCPU(0x00C9, a);
    myMapper->writeCPU(0x00CA, a);
    myMapper->writeCPU(0x00BA, a);
    myMapper->writeCPU(0x00C5, a);
    myMapper->writeCPU(0x00C8, a);
    pushAddress(0x0001ED);
    SUB_00349B();
    if (poppedEntry.value != 0x0001ED) return;
    x = 0x13;
    do {
        myMapper->writeCPU(0x0530 + x, 0xFF);
        myMapper->writeCPU(0x04A4 + x, 0xF0);
        opDEX(1);
    } while (!flgN);
    while (true) {
        pushAddress(0x0001FF);
        SUB_003466();
        if (poppedEntry.value != 0x0001FF) return;
        pushAddress(0x000202);
        SUB_002687();
        if (poppedEntry.value != 0x000202) return;
        if (myMapper->readCPU(0x00C5) == 0) {
            pushAddress(0x000209);
            SUB_0006EF();
            if (poppedEntry.value != 0x000209) return;
        }
        a = myMapper->readCPU(0x0019);
        opLSR_A(1);
        if (!flgC) {
        }
        else {
            if (myMapper->readCPU(0x00C5) == 0) {
                goto L_00021D;
            }
            opDEC(0x00C5, 1);
            goto L_0002C6;
        L_00021D:
            if (myMapper->readCPU(0x0017) == 0) {
                a = myMapper->readCPU(0x0018);
                opEOR(0x01);
                myMapper->writeCPU(0x0018, a);
            }
            opDEC(0x0017, 1);
            if (myMapper->readCPU(0x0488) != 0) {
                opINC(0x0488, 1);
                if (myMapper->readCPU(0x0488) >= 0xF0) {
                    myMapper->writeCPU(0x0488, 0x00);
                }
                if (myMapper->readCPU(0x00BD) != 0) {
                    opINC(0x0091, 1);
                }
            }
            x = 0x07;
            do {
                if (myMapper->readCPU(0x055D + x) & 0x80) {
                    goto L_000263;
                }
                opINC(0x0567 + x, 1);
                if (myMapper->readCPU(0x0567 + x) != 0xF8) {
                    goto L_000263;
                }
                myMapper->writeCPU(0x055D + x, 0xFF);
                myMapper->writeCPU(0x057B + x, 0xF0);
                myMapper->writeCPU(0x05CE, 0x00);
            L_000263:
                opDEX(1);
            } while (!flgN);
            x = 0x13;
            do {
                if (myMapper->readCPU(0x0530 + x) & 0x80) {
                    goto L_00027F;
                }
                opINC(0x0490 + x, 1);
                if (myMapper->readCPU(0x0490 + x) < 0xF8) {
                    goto L_00027F;
                }
                a = 0xF0;
                myMapper->writeCPU(0x04A4 + x, a);
                myMapper->writeCPU(0x0530 + x, a);
            L_00027F:
                opDEX(1);
            } while (!flgN);
            a = myMapper->readCPU(0x0017);
            opAND(0x07);
            if (flgZ) {
                x = myMapper->readCPU(0x0088);
                opDEX(1);
                if (!flgN) {
                    myMapper->writeCPU(0x003E, 0x00);
                    a = 0x01;
                    pushAddress(0x000293);
                    SUB_0016D4();
                    if (poppedEntry.value != 0x000293) return;
                    opINC(0x00C9, 1);
                    a = myMapper->readCPU(0x00C9);
                    opAND(0x1F);
                    if (flgZ) {
                        opINC(0x00CA, 1);
                        if (myMapper->readCPU(0x00CA) == 0x0A) {
                            myMapper->writeCPU(0x00CA, 0x02);
                            y = myMapper->readCPU(0x00BA);
                            opINY(1);
                            a = y;
                            opAND(0x03);
                            myMapper->writeCPU(0x00BA, a);
                        }
                    }
                    x = myMapper->readCPU(0x00CA);
                    a = myMapper->readCPU(0xC3B5 + x);
                    opASL_A(1);
                    y = a;
                    myMapper->writeCPU(0x0025, myMapper->readCPU(0xC3AB + y));
                    myMapper->writeCPU(0x0026, myMapper->readCPU(0xC3AC + y));
                    pushAddress(0x0002C3);
                    SUB_0003A8();
                    if (poppedEntry.value != 0x0002C3) return;
                }
            }
        }
    L_0002C6:
        x = 0x07;
        do {
            if (myMapper->readCPU(0x055D + x) & 0x80) {
                goto L_0002E5;
            }
            pushAddress(0x0002CD);
            SUB_000EC4();
            if (poppedEntry.value != 0x0002CD) return;
            if (myMapper->readCPU(0x05CD) == 0) {
                goto L_0002E5;
            }
            opDEC(0x05CD, 1);
            opINC(0x05CE, 1);
            a = x;
            opPHA();
            a = myMapper->readCPU(0x0559);
            pushAddress(0x0002E0);
            SUB_0016D4();
            if (poppedEntry.value != 0x0002E0) return;
            opPLA();
            x = a;
        L_0002E5:
            pushAddress(0x0002E5);
            SUB_000E25();
            if (poppedEntry.value != 0x0002E5) return;
            opDEX(1);
        } while (!flgN);
        x = 0x13;
        do {
            if (myMapper->readCPU(0x0530 + x) & 0x80) {
                goto L_00030D;
            }
            if (myMapper->readCPU(0x00C5) == 0) {
                pushAddress(0x0002F6);
                SUB_0009AC();
                if (poppedEntry.value != 0x0002F6) return;
                a = myMapper->readCPU(0x04A4 + x);
                if (a < 0x02) {
                    pushAddress(0x000300);
                    SUB_000A45();
                    if (poppedEntry.value != 0x000300) return;
                }
                if (a >= 0xD8) {
                    pushAddress(0x000307);
                    SUB_000A45();
                    if (poppedEntry.value != 0x000307) return;
                }
            }
            pushAddress(0x00030A);
            SUB_000B12();
            if (poppedEntry.value != 0x00030A) return;
        L_00030D:
            a = myMapper->readCPU(0x0019);
            opAND(0x07);
            opLSR_A(1);
            y = a;
            a = myMapper->readCPU(0xC9D3 + y);
            opPHA();
            a = myMapper->readCPU(0x0019);
            opLSR_A(1);
            a = x;
            if (!flgC) {
                goto L_000323;
            }
            myMapper->writeCPU(0x0012, a);
            a = 0x13;
            opSBC(myMapper->readCPU(0x0012));
        L_000323:
            opASL_A(2);
            y = a;
            opPLA();
            myMapper->writeCPU(0x02B1 + y, a);
            myMapper->writeCPU(0x02B0 + y, myMapper->readCPU(0x04A4 + x));
            myMapper->writeCPU(0x02B3 + y, myMapper->readCPU(0x0490 + x));
            myMapper->writeCPU(0x02B2 + y, 0x00);
            opDEX(1);
        } while (!flgN);
        if (myMapper->readCPU(0x05CE) >= 0x14) {
            opINC(0x0047, 1);
            a = 0x00;
            pushAddress(0x000349);
            SUB_0016D4();
            if (poppedEntry.value != 0x000349) return;
            opDEC(0x0047, 1);
            myMapper->writeCPU(0x00F2, 0x10);
            opINC(0x00C8, 1);
            pushAddress(0x000354);
            SUB_0013E3();
            if (poppedEntry.value != 0x000354) return;
            pushAddress(0x000357);
            SUB_00051D();
            if (poppedEntry.value != 0x000357) return;
            opDEC(0x00C8, 1);
            x = 0x64;
            pushAddress(0x00035E);
            SUB_003454();
            if (poppedEntry.value != 0x00035E) return;
            myMapper->writeCPU(0x00F2, 0x20);
        }
        x = 0xF0;
        a = myMapper->readCPU(0x0488);
        setLoadFlag(a);
        if (flgZ) {
            goto L_00036E;
        }
        x = 0x88;
    L_00036E:
        myMapper->writeCPU(0x0200, x);
        myMapper->writeCPU(0x0204, x);
        myMapper->writeCPU(0x0203, a);
        flgC = false;
        opADC(0x08);
        myMapper->writeCPU(0x0207, a);
        a = myMapper->readCPU(0x0019);
        opAND(0x03);
        myMapper->writeCPU(0x0202, a);
        myMapper->writeCPU(0x0206, a);
        x = 0xE3;
        myMapper->writeCPU(0x0201, x);
        opINX(1);
        myMapper->writeCPU(0x0205, x);
        if (myMapper->readCPU(0x0088) & 0x80) {
            goto L_000397;
        }
    }
L_000397:
    pushAddress(0x000397);
    SUB_00056F();
    if (poppedEntry.value != 0x000397) return;
    myMapper->writeCPU(0x00F0, 0x01);
    pushAddress(0x00039E);
    SUB_00345B();
    if (poppedEntry.value != 0x00039E) return;
    myMapper->writeCPU(0x00F2, 0x02);
    SUB_003360();
    return;
}

void game::SUB_0003A8() {
    indirectJump(myMapper->readCPU(0x0025) + (myMapper->readCPU((0x0025 + 1) & 0x00ff) << 8));
}

void game::SUB_0003BF() {
    while (true) {
        while (true) {
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x0023) + (myMapper->readCPU((0x0023 + 1) & 0x00ff) << 8) + y);
            opINC(0x0023, 1);
            if (!flgZ) {
                goto L_0003C9;
            }
            opINC(0x0024, 1);
        L_0003C9:
            x = a;
            setLoadFlag(x);
            if (flgZ) {
                goto L_0003EC;
            }
            opASL_A(3);
            myMapper->writeCPU(0x0015, a);
            myMapper->writeCPU(0x0014, 0x00);
            a = x;
            opAND(0xC0);
            if (a != 0x80) {
                goto L_0003E2;
            }
            pushAddress(0x0003DC);
            SUB_000461();
            if (poppedEntry.value != 0x0003DC) return;
        }
    L_0003E2:
        if (a != 0x00) {
            goto L_0003EC;
        }
        pushAddress(0x0003E6);
        SUB_00047C();
        if (poppedEntry.value != 0x0003E6) return;
    }
L_0003EC:
    popAddress();
}

void game::SUB_0003ED() {
    pushAddress(0x0003ED);
    SUB_0031A9();
    if (poppedEntry.value != 0x0003ED) return;
    opAND(0x7F);
    if (a < 0x04) {
        SUB_000402();
        return;
    }
    if (a >= 0x18) {
        SUB_000402();
        return;
    }
    opASL_A(3);
    myMapper->writeCPU(0x0015, a);
    pushAddress(0x0003FF);
    SUB_000461();
    if (poppedEntry.value != 0x0003FF) return;
    SUB_000402();
    return;
}

void game::SUB_000402() {
    while (true) {
        do {
            pushAddress(0x000402);
            SUB_0031A9();
            if (poppedEntry.value != 0x000402) return;
            opAND(0x3F);
            if (a < 0x02) {
                goto L_00042F;
            }
            if (a >= 0x18) {
                goto L_00042F;
            }
            opASL_A(3);
            myMapper->writeCPU(0x0015, a);
            pushAddress(0x000414);
            SUB_0031A9();
            if (poppedEntry.value != 0x000414) return;
            opAND(0x3F);
            x = myMapper->readCPU(0x00BA);
            opADC(myMapper->readCPU(0xC430 + x));
            myMapper->writeCPU(0x0014, a);
            pushAddress(0x000420);
            SUB_00047C();
            if (poppedEntry.value != 0x000420) return;
            pushAddress(0x000423);
            SUB_0031A9();
            if (poppedEntry.value != 0x000423) return;
            opLSR_A(1);
        } while (!flgC);
        pushAddress(0x000429);
        SUB_000A45();
        if (poppedEntry.value != 0x000429) return;
    }
L_00042F:
    popAddress();
}

void game::SUB_000434() {
    pushAddress(0x000434);
    SUB_0031A9();
    if (poppedEntry.value != 0x000434) return;
    opAND(0xCF);
    if (!flgZ) {
        SUB_0003ED();
        return;
    }
    y = myMapper->readCPU(0x0089);
    opINY(1);
    if (!flgZ) {
        SUB_0003ED();
        return;
    }
    myMapper->writeCPU(0x009B, 0xE6);
    a = myMapper->readCPU(0x001B);
    opAND(0x7F);
    opADC(0x40);
    myMapper->writeCPU(0x0092, a);
    myMapper->writeCPU(0x0089, 0x80);
    myMapper->writeCPU(0x0080, 0x00);
    SUB_000454();
    return;
}

void game::SUB_000454() {
    popAddress();
}

void game::SUB_000455() {
    pushAddress(0x000455);
    SUB_000402();
    if (poppedEntry.value != 0x000455) return;
    pushAddress(0x000458);
    SUB_0031A9();
    if (poppedEntry.value != 0x000458) return;
    opAND(0x7F);
    myMapper->writeCPU(0x0508 + x, a);
    popAddress();
}

void game::SUB_000461() {
    x = 0x07;
    do {
        if (myMapper->readCPU(0x055D + x) & 0x80) {
            goto L_00046C;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_00046C:
    myMapper->writeCPU(0x055D + x, 0x01);
    myMapper->writeCPU(0x0567 + x, 0x00);
    myMapper->writeCPU(0x057B + x, myMapper->readCPU(0x0015));
    popAddress();
}

void game::SUB_00047C() {
    x = 0x13;
    do {
        if (myMapper->readCPU(0x0530 + x) & 0x80) {
            goto L_000487;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_000487:
    a = 0x00;
    myMapper->writeCPU(0x0530 + x, a);
    myMapper->writeCPU(0x0490 + x, a);
    myMapper->writeCPU(0x04F4 + x, a);
    myMapper->writeCPU(0x0508 + x, a);
    myMapper->writeCPU(0x04E0 + x, a);
    myMapper->writeCPU(0x051C + x, myMapper->readCPU(0x0014));
    myMapper->writeCPU(0x04A4 + x, myMapper->readCPU(0x0015));
    popAddress();
}

void game::SUB_00051D() {
    pushAddress(0x00051D);
    SUB_0010D8();
    if (poppedEntry.value != 0x00051D) return;
    opASL_M(0x0559, 1);
    a = myMapper->readCPU(0x0559);
    opASL_A(2);
    opADC(myMapper->readCPU(0x0559));
    myMapper->writeCPU(0x0559, a);
    popAddress();
}

void game::SUB_00052F() {
    myMapper->writeCPU(0x0012, 0x00);
    do {
        a = myMapper->readCPU(0x0012);
        opASL_A(2);
        opADC(myMapper->readCPU(0x0012));
        myMapper->writeCPU(0x001D, a);
        myMapper->writeCPU(0x001E, 0x07);
        y = 0x04;
        do {
            opCMP(myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y), myMapper->readCPU(0x0003 + y));
            if (!flgC) {
                goto L_000559;
            }
            if (!flgZ) {
                goto L_00054F;
            }
            opDEY(1);
        } while (!flgN);
        if (flgN) {
            goto L_000559;
        }
    L_00054F:
        opINC(0x0012, 1);
    } while (myMapper->readCPU(0x0012) != 0x32);
    opDEC(0x0012, 1);
L_000559:
    opINC(0x0012, 1);
    a = myMapper->readCPU(0x0012);
    opPHA();
    myMapper->writeCPU(0x0043, a);
    y = 0x0A;
    pushAddress(0x000562);
    SUB_001772();
    if (poppedEntry.value != 0x000562) return;
    myMapper->writeCPU(0x004A, a);
    a = myMapper->readCPU(0x0043);
    myMapper->writeCPU(0x0049, a);
    opPLA();
    myMapper->writeCPU(0x0012, a);
    popAddress();
}

void game::SUB_00056F() {
    pushAddress(0x00056F);
    SUB_00052F();
    if (poppedEntry.value != 0x00056F) return;
    opDEC(0x0012, 1);
    a = 0x31;
    flgC = true;
    opSBC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0013, a);
    opASL_A(2);
    opADC(myMapper->readCPU(0x0013));
    y = a;
    a = myMapper->readCPU(0x0012);
    opASL_A(2);
    opADC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x001D, a);
    flgC = false;
    opADC(0x05);
    myMapper->writeCPU(0x001F, a);
    a = 0x07;
    myMapper->writeCPU(0x001E, a);
    myMapper->writeCPU(0x0020, a);
    if (y == 0) {
        goto L_0005A2;
    }
    opDEY(1);
    do {
        myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y));
L_0005A2:
    y = 0x04;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x0003 + y));
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0005B9() {
    a = myMapper->readCPU(0x048D);
    opLSR_A(3);
    x = a;
    if (myMapper->readCPU(0x048A) == 0) {
        a = myMapper->readCPU(0xC5AD + x);
    }
    else {
        a = myMapper->readCPU(0xC5B1 + x);
    }
    myMapper->writeCPU(0x0087, a);
    x = 0x08;
    pushAddress(0x0005D2);
    SUB_00239A();
    if (poppedEntry.value != 0x0005D2) return;
    if (myMapper->readCPU(0x048C) != 0) {
        x = myMapper->readCPU(0x048B);
        opCMP(myMapper->readCPU(0x048D), 0x20);
        if (flgZ) {
            a = 0xFF;
            setLoadFlag(a);
            myMapper->writeCPU((0x0088 + x) & 0x00ff, a);
            if (flgN) {
                goto L_000606;
            }
        }
        if (!flgC) {
            if (myMapper->readCPU(0x0450) != 0) {
                goto L_0005F8;
            }
            a = myMapper->readCPU(0x0099);
            flgC = false;
            opADC(0x04);
            if (!flgZ) {
                goto L_0005FD;
            }
        L_0005F8:
            a = myMapper->readCPU(0x0099);
            flgC = true;
            opSBC(0x04);
        L_0005FD:
            myMapper->writeCPU((0x0091 + x) & 0x00ff, a);
            a = myMapper->readCPU(0x00A2);
            flgC = true;
            opSBC(0x0A);
            myMapper->writeCPU((0x009A + x) & 0x00ff, a);
        L_000606:
            pushAddress(0x000606);
            SUB_00239A();
            if (poppedEntry.value != 0x000606) return;
        }
    }
    popAddress();
}

void game::SUB_00060A() {
    myMapper->writeCPU(0x048B, 0xFF);
    x = 0x07;
    do {
        if (myMapper->readCPU((0x0088 + x) & 0x00ff) & 0x80) {
            goto L_000621;
        }
        if (myMapper->readCPU((0x009A + x) & 0x00ff) < 0xB4) {
            goto L_000621;
        }
        if (myMapper->readCPU((0x0091 + x) & 0x00ff) == myMapper->readCPU(0x0099)) {
            goto L_000625;
        }
    L_000621:
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_000625:
    myMapper->writeCPU(0x048B, x);
    myMapper->writeCPU(0x0450, myMapper->readCPU(0x0448 + x));
    a = 0x00;
    myMapper->writeCPU(0x048A, a);
    myMapper->writeCPU(0x048D, a);
    myMapper->writeCPU(0x048C, a);
    myMapper->writeCPU(0x0489, a);
    myMapper->writeCPU(0x00A2, 0xDC);
    popAddress();
}

void game::SUB_000641() {
    opINC(0x0099, 1);
    if (myMapper->readCPU(0x0099) < 0xB1) {
        goto L_00064D;
    }
    myMapper->writeCPU(0x0099, 0x40);
L_00064D:
    popAddress();
}

void game::SUB_00064E() {
    if (myMapper->readCPU(0x0489) != 0) {
        goto L_000665;
    }
    opDEC(0x00A2, 1);
    if (myMapper->readCPU(0x00A2) >= 0xC4) {
        goto L_000667;
    }
    opINC(0x00A2, 1);
    opINC(0x048A, 1);
    opINC(0x0489, 1);
    if (!flgZ) {
        goto L_000667;
    }
L_000665:
    opINC(0x00A2, 1);
L_000667:
    opINC(0x048D, 1);
    if (myMapper->readCPU(0x048D) == 0x18) {
        x = myMapper->readCPU(0x048B);
        if (!(myMapper->readCPU((0x0088 + x) & 0x00ff) & 0x80)) {
            a = myMapper->readCPU((0x009A + x) & 0x00ff);
            flgC = false;
            opADC(0x10);
            if (a >= myMapper->readCPU(0x00A2)) {
                y = myMapper->readCPU(0x0451 + x);
                myMapper->writeCPU(0x0451 + x, myMapper->readCPU(0xC6AE + y));
                a = 0x00;
                myMapper->writeCPU((0x007F + x) & 0x00ff, a);
                myMapper->writeCPU((0x0088 + x) & 0x00ff, a);
                a = myMapper->readCPU(0x00F2);
                opORA(0x40);
                myMapper->writeCPU(0x00F2, a);
                opINC(0x048C, 1);
            }
        }
    }
    if (myMapper->readCPU(0x048A) != 0) {
        a = myMapper->readCPU(0x048D);
        if (a == 0x28) {
            goto L_0006A9;
        }
        if (a != 0x30) {
            goto L_0006AD;
        }
    L_0006A9:
        myMapper->writeCPU(0x00A2, 0xCC);
    }
L_0006AD:
    popAddress();
}

void game::SUB_0006BA() {
    if (myMapper->readCPU(0x0489) != 0) {
        goto L_0006EE;
    }
    x = myMapper->readCPU(0x048B);
    if (!(myMapper->readCPU((0x0088 + x) & 0x00ff) & 0x80)) {
        if (myMapper->readCPU((0x009A + x) & 0x00ff) < 0xB4) {
            goto L_0006D6;
        }
        a = myMapper->readCPU((0x0091 + x) & 0x00ff);
        if (a >= 0x40) {
            if (a < 0xB1) {
                goto L_0006E4;
            }
        }
    }
L_0006D6:
    a = 0x30;
    flgC = true;
    opSBC(myMapper->readCPU(0x048D));
    myMapper->writeCPU(0x048D, a);
    opINC(0x0489, 1);
    if (!flgZ) {
        goto L_0006EE;
    }
L_0006E4:
    myMapper->writeCPU(0x0099, myMapper->readCPU((0x0091 + x) & 0x00ff));
    myMapper->writeCPU(0x0450, myMapper->readCPU(0x0448 + x));
L_0006EE:
    popAddress();
}

void game::SUB_0006EF() {
    if (!(myMapper->readCPU(0x0087) & 0x80)) {
        goto L_000703;
    }
    pushAddress(0x0006F3);
    SUB_000641();
    if (poppedEntry.value != 0x0006F3) return;
    pushAddress(0x0006F6);
    SUB_00060A();
    if (poppedEntry.value != 0x0006F6) return;
    if (!(myMapper->readCPU(0x048B) & 0x80)) {
        goto L_0006FF;
    }
    popAddress();
    return;
L_0006FF:
    myMapper->writeCPU(0x00F3, 0x40);
L_000703:
    pushAddress(0x000703);
    SUB_0006BA();
    if (poppedEntry.value != 0x000703) return;
    pushAddress(0x000706);
    SUB_00064E();
    if (poppedEntry.value != 0x000706) return;
    SUB_0005B9();
    return;
}

void game::SUB_00070C() {
    x = 0x01;
    do {
        a = 0xFF;
        myMapper->writeCPU(0x0530 + x, a);
        myMapper->writeCPU(0x0544 + x, a);
        opDEX(1);
    } while (!flgN);
    pushAddress(0x000719);
    SUB_000770();
    if (poppedEntry.value != 0x000719) return;
    SUB_00071C();
    return;
}

void game::SUB_00071C() {
    x = myMapper->readCPU(0x003C);
    opCMP(x, 0x18);
    if (!flgC) {
        goto L_000724;
    }
    x = 0x18;
L_000724:
    myMapper->writeCPU(0x00BA, myMapper->readCPU(0xC73E + x));
    myMapper->writeCPU(0x00B8, myMapper->readCPU(0xC757 + x));
    a = 0xF0;
    myMapper->writeCPU(0x02E0, a);
    myMapper->writeCPU(0x02E4, a);
    myMapper->writeCPU(0x02E8, a);
    a = 0x03;
    SUB_00084C();
    return;
}

void game::SUB_000770() {
    a = myMapper->readCPU(0x00A3);
    setLoadFlag(a);
    if (!flgN) {
        goto L_000777;
    }
    do {
        do {
            myMapper->writeCPU(0x00A4, a);
            popAddress();
            return;
        L_000777:
            pushAddress(0x000777);
            SUB_0031A9();
            if (poppedEntry.value != 0x000777) return;
        L_00077A:
            opCMP(a, myMapper->readCPU(0x00A3));
        } while (!flgC);
    } while (flgZ);
    flgC = false;
    opSBC(myMapper->readCPU(0x00A3));
    goto L_00077A;
}

void game::SUB_000786() {
    a = myMapper->readCPU(0x0019);
    opAND(0x7F);
    if (flgZ) {
        goto L_00078D;
    }
    do {
        popAddress();
        return;
    L_00078D:
        opDEC(0x00B8, 1);
    } while (!flgZ);
    x = 0x00;
    if (!(myMapper->readCPU(0x0530 + x) & 0x80)) {
        opINX(1);
        if (!(myMapper->readCPU(0x0530 + x) & 0x80)) {
            myMapper->writeCPU(0x00B8, 0x01);
            popAddress();
            return;
        }
    }
    y = myMapper->readCPU(0x00A4);
    setLoadFlag(y);
    myMapper->writeCPU(0x00A5, y);
    if (flgN) {
        popAddress();
        return;
    }
    a = 0x80;
    myMapper->writeCPU(0x04B8 + x, a);
    myMapper->writeCPU(0x04CC + x, a);
    myMapper->writeCPU(0x0530 + x, 0x00);
    myMapper->writeCPU(0x0490 + x, myMapper->readCPU(0x00B2 + y));
    myMapper->writeCPU(0x04A4 + x, myMapper->readCPU(0x00B5 + y));
    y = myMapper->readCPU(0x00BA);
    pushAddress(0x0007C5);
    SUB_0031A9();
    if (poppedEntry.value != 0x0007C5) return;
    opAND(0x1F);
    opADC(myMapper->readCPU(0xC895 + y));
    myMapper->writeCPU(0x0508 + x, a);
    myMapper->writeCPU(0x051C + x, myMapper->readCPU(0xC8A1 + y));
    myMapper->writeCPU(0x04E0 + x, myMapper->readCPU(0xC89B + y));
    myMapper->writeCPU(0x04F4 + x, myMapper->readCPU(0xC8A7 + y));
    pushAddress(0x0007E2);
    SUB_0031A9();
    if (poppedEntry.value != 0x0007E2) return;
    opAND(0x03);
    myMapper->writeCPU(0x0544 + x, a);
    y = a;
    a = myMapper->readCPU(0xC88D + y);
    flgC = false;
    opADC(myMapper->readCPU(0x0490 + x));
    myMapper->writeCPU(0x0490 + x, a);
    a = myMapper->readCPU(0xC891 + y);
    flgC = false;
    opADC(myMapper->readCPU(0x04A4 + x));
    myMapper->writeCPU(0x04A4 + x, a);
    if (myMapper->readCPU(0xC885 + y) != 0) {
        pushAddress(0x000804);
        SUB_000A33();
        if (poppedEntry.value != 0x000804) return;
    }
    if (myMapper->readCPU(0xC889 + y) != 0) {
        pushAddress(0x00080C);
        SUB_000A4B();
        if (poppedEntry.value != 0x00080C) return;
    }
    if (myMapper->readCPU(0x00BA) >= 0x05) {
        goto L_000817;
    }
    opINC(0x00BA, 1);
L_000817:
    a = 0x06;
    flgC = true;
    opSBC(myMapper->readCPU(0x00BA));
    myMapper->writeCPU(0x00B8, a);
    a = myMapper->readCPU(0x00F0);
    opORA(0x04);
    myMapper->writeCPU(0x00F0, a);
    SUB_000770();
    return;
}

void game::SUB_000827() {
    a = myMapper->readCPU(0x00B8);
    opCMP(a, 0x01);
    if (!flgZ) {
        SUB_000880();
        return;
    }
    if (!(myMapper->readCPU(0x0530) & 0x80)) {
        if (myMapper->readCPU(0x0531) & 0x80) {
            goto L_00083C;
        }
        myMapper->writeCPU(0x00B8, 0x02);
        popAddress();
        return;
    }
L_00083C:
    a = myMapper->readCPU(0x0019);
    opAND(0x7F);
    opCMP(a, 0x40);
    if (!flgC) {
        SUB_000880();
        return;
    }
    if (!flgZ) {
        SUB_00084C();
        return;
    }
    a = myMapper->readCPU(0x00F1);
    opORA(0x08);
    myMapper->writeCPU(0x00F1, a);
    SUB_00084C();
    return;
}

void game::SUB_00084C() {
    opAND(0x03);
    x = a;
    a = myMapper->readCPU(0xC881 + x);
    myMapper->writeCPU(0x005A, a);
    x = myMapper->readCPU(0x00A4);
    setLoadFlag(x);
    if (flgN) {
        SUB_000880();
        return;
    }
    myMapper->writeCPU(0x0057, 0x23);
    myMapper->writeCPU(0x0058, myMapper->readCPU((0x00A6 + x) & 0x00ff));
    myMapper->writeCPU(0x0059, 0x01);
    pushAddress(0x000864);
    SUB_000879();
    if (poppedEntry.value != 0x000864) return;
    myMapper->writeCPU(0x0058, myMapper->readCPU((0x00A9 + x) & 0x00ff));
    pushAddress(0x00086B);
    SUB_000879();
    if (poppedEntry.value != 0x00086B) return;
    myMapper->writeCPU(0x0058, myMapper->readCPU((0x00AC + x) & 0x00ff));
    pushAddress(0x000872);
    SUB_000879();
    if (poppedEntry.value != 0x000872) return;
    myMapper->writeCPU(0x0058, myMapper->readCPU((0x00AF + x) & 0x00ff));
    SUB_000879();
    return;
}

void game::SUB_000879() {
    a = 0x57;
    y = 0x00;
    SUB_000127();
    return;
}

void game::SUB_000880() {
    popAddress();
}

void game::SUB_0008AD() {
    x = 0x01;
    while (true) {
        if (!(myMapper->readCPU(0x0530 + x) & 0x80)) {
            goto L_0008B7;
        }
        goto L_0009A5;
    L_0008B7:
        a = myMapper->readCPU(0x0544 + x);
        setLoadFlag(a);
        if (!flgN) {
            y = a;
            a = x;
            opPHA();
            x = myMapper->readCPU(0x00A5);
            a = myMapper->readCPU((0x00B2 + x) & 0x00ff);
            opADC(myMapper->readCPU(0xC9DB + y));
            myMapper->writeCPU(0x02E3, a);
            myMapper->writeCPU(0x02E7, a);
            myMapper->writeCPU(0x02EB, a);
            a = myMapper->readCPU((0x00B5 + x) & 0x00ff);
            opADC(myMapper->readCPU(0xC9EB + y));
            myMapper->writeCPU(0x02E0, a);
            opADC(myMapper->readCPU(0xC9FB + y));
            myMapper->writeCPU(0x02E4, a);
            opADC(myMapper->readCPU(0xC9FB + y));
            myMapper->writeCPU(0x02E8, a);
            a = y;
            opAND(0x03);
            x = a;
            a = y;
            opLSR_A(2);
            y = a;
            a = myMapper->readCPU(0x0019);
            opLSR_A(2);
            if (!flgC) {
                a = y;
                opADC(0x05);
                y = a;
            }
            myMapper->writeCPU(0x02E1, myMapper->readCPU(0xCA0B + y));
            myMapper->writeCPU(0x02E5, myMapper->readCPU(0xCA15 + y));
            myMapper->writeCPU(0x02E9, myMapper->readCPU(0xCA1F + y));
            a = myMapper->readCPU(0xCA29 + x);
            myMapper->writeCPU(0x02E2, a);
            myMapper->writeCPU(0x02E6, a);
            myMapper->writeCPU(0x02EA, a);
            opPLA();
            x = a;
            a = myMapper->readCPU(0x0019);
            opAND(0x07);
            if (flgZ) {
                a = myMapper->readCPU(0x0544 + x);
                flgC = false;
                opADC(0x04);
                myMapper->writeCPU(0x0544 + x, a);
                if (a >= 0x14) {
                    myMapper->writeCPU(0x0544 + x, 0xFF);
                }
            }
            opCMP(myMapper->readCPU(0x0544 + x), 0x10);
            if (!flgC) {
                goto L_0009A5;
            }
        }
        pushAddress(0x000937);
        SUB_0009AC();
        if (poppedEntry.value != 0x000937) return;
        if (myMapper->readCPU(0x0490 + x) < 0x02) {
            pushAddress(0x000941);
            SUB_000A2D();
            if (poppedEntry.value != 0x000941) return;
        }
        if (myMapper->readCPU(0x0490 + x) >= 0xF7) {
            pushAddress(0x00094B);
            SUB_000A2D();
            if (poppedEntry.value != 0x00094B) return;
        }
        if (myMapper->readCPU(0x04A4 + x) < 0x02) {
            pushAddress(0x000955);
            SUB_000A45();
            if (poppedEntry.value != 0x000955) return;
        }
        opCMP(myMapper->readCPU(0x04A4 + x), 0xE0);
        if (flgC) {
            myMapper->writeCPU(0x0530 + x, 0xFF);
            myMapper->writeCPU(0x04A4 + x, 0xF0);
        }
        else {
            pushAddress(0x00096C);
            SUB_000A5D();
            if (poppedEntry.value != 0x00096C) return;
            pushAddress(0x00096F);
            SUB_000B12();
            if (poppedEntry.value != 0x00096F) return;
            y = myMapper->readCPU(0x0530 + x);
            opINY(1);
            a = y;
            opAND(0x07);
            myMapper->writeCPU(0x0530 + x, a);
            y = myMapper->readCPU(0x0530 + x);
            myMapper->writeCPU(0x0012, myMapper->readCPU(0xC9D3 + y));
            a = x;
            opASL_A(2);
            flgC = false;
            y = a;
            a = myMapper->readCPU(0x04A4 + x);
            opCMP(a, 0xD0);
            myMapper->writeCPU(0x0200 + y, a);
            myMapper->writeCPU(0x0203 + y, myMapper->readCPU(0x0490 + x));
            myMapper->writeCPU(0x0201 + y, myMapper->readCPU(0x0012));
            a = 0x00;
            if (!flgC) {
                goto L_0009A2;
            }
            a = 0x20;
        L_0009A2:
            myMapper->writeCPU(0x0202 + y, a);
        }
    L_0009A5:
        opDEX(1);
        if (flgN) {
            goto L_0009AB;
        }
    }
L_0009AB:
    popAddress();
}

void game::SUB_0009AC() {
    a = myMapper->readCPU(0x0508 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04B8 + x));
    myMapper->writeCPU(0x04B8 + x, a);
    a = myMapper->readCPU(0x04E0 + x);
    opADC(myMapper->readCPU(0x0490 + x));
    myMapper->writeCPU(0x0490 + x, a);
    a = myMapper->readCPU(0x051C + x);
    flgC = false;
    opADC(myMapper->readCPU(0x04CC + x));
    myMapper->writeCPU(0x04CC + x, a);
    a = myMapper->readCPU(0x04F4 + x);
    opADC(myMapper->readCPU(0x04A4 + x));
    myMapper->writeCPU(0x04A4 + x, a);
    popAddress();
}

void game::SUB_000A2D() {
    a = myMapper->readCPU(0x00F3);
    opORA(0x80);
    myMapper->writeCPU(0x00F3, a);
    SUB_000A33();
    return;
}

void game::SUB_000A33() {
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0508 + x));
    myMapper->writeCPU(0x0508 + x, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x04E0 + x));
    myMapper->writeCPU(0x04E0 + x, a);
    popAddress();
}

void game::SUB_000A45() {
    a = myMapper->readCPU(0x00F3);
    opORA(0x80);
    myMapper->writeCPU(0x00F3, a);
    SUB_000A4B();
    return;
}

void game::SUB_000A4B() {
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x051C + x));
    myMapper->writeCPU(0x051C + x, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x04F4 + x));
    myMapper->writeCPU(0x04F4 + x, a);
    popAddress();
}

void game::SUB_000A5D() {
    y = myMapper->readCPU(0x00CD);
    while (true) {
        myMapper->writeCPU(0x00CC, 0x00);
        a = myMapper->readCPU(myMapper->readCPU(0x0027) + (myMapper->readCPU((0x0027 + 1) & 0x00ff) << 8) + y);
        flgC = true;
        opSBC(0x08);
        opCMP(a, myMapper->readCPU(0x04A4 + x));
        if (!flgC) {
            opADC(0x03);
            if (a >= myMapper->readCPU(0x04A4 + x)) {
                a = 0x01;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_000A88;
                }
            }
            a = myMapper->readCPU(myMapper->readCPU(0x0029) + (myMapper->readCPU((0x0029 + 1) & 0x00ff) << 8) + y);
            opCMP(a, myMapper->readCPU(0x04A4 + x));
            if (flgC) {
                opSBC(0x03);
                if (a < myMapper->readCPU(0x04A4 + x)) {
                    a = 0x02;
                L_000A88:
                    myMapper->writeCPU(0x00CC, a);
                    a = myMapper->readCPU(myMapper->readCPU(0x0023) + (myMapper->readCPU((0x0023 + 1) & 0x00ff) << 8) + y);
                    if (a != 0x10) {
                        flgC = true;
                        opSBC(0x04);
                        if (a >= myMapper->readCPU(0x0490 + x)) {
                            goto L_000A9F;
                        }
                    }
                    if (myMapper->readCPU(myMapper->readCPU(0x0025) + (myMapper->readCPU((0x0025 + 1) & 0x00ff) << 8) + y) < myMapper->readCPU(0x0490 + x)) {
                    L_000A9F:
                        myMapper->writeCPU(0x00CC, 0x00);
                    }
                }
                a = myMapper->readCPU(myMapper->readCPU(0x0023) + (myMapper->readCPU((0x0023 + 1) & 0x00ff) << 8) + y);
                if (a != 0x10) {
                    flgC = true;
                    opSBC(0x08);
                    opCMP(a, myMapper->readCPU(0x0490 + x));
                    if (flgC) {
                        goto L_000AD3;
                    }
                    opADC(0x03);
                    if (a >= myMapper->readCPU(0x0490 + x)) {
                        a = myMapper->readCPU(0x00CC);
                        opORA(0x04);
                        if (!flgZ) {
                            goto L_000AD1;
                        }
                    }
                }
                a = myMapper->readCPU(myMapper->readCPU(0x0025) + (myMapper->readCPU((0x0025 + 1) & 0x00ff) << 8) + y);
                if (a != 0xFF) {
                    opCMP(a, myMapper->readCPU(0x0490 + x));
                    if (flgC) {
                        opSBC(0x03);
                        if (flgC) {
                            goto L_000AD3;
                        }
                        a = myMapper->readCPU(0x00CC);
                        opORA(0x08);
                    L_000AD1:
                        myMapper->writeCPU(0x00CC, a);
                    }
                }
            }
        }
    L_000AD3:
        if (myMapper->readCPU(0x00CC) != 0) {
            goto L_000ADE;
        }
    L_000AD7:
        opDEY(1);
        if (flgN) {
            goto L_000ADD;
        }
    }
L_000ADD:
    popAddress();
    return;
L_000ADE:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (myMapper->readCPU(0x04F4 + x) & 0x80) {
            goto L_000AEA;
        }
        pushAddress(0x000AE7);
        SUB_000A45();
        if (poppedEntry.value != 0x000AE7) return;
    }
L_000AEA:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (!(myMapper->readCPU(0x04F4 + x) & 0x80)) {
            goto L_000AF6;
        }
        pushAddress(0x000AF3);
        SUB_000A45();
        if (poppedEntry.value != 0x000AF3) return;
    }
L_000AF6:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (myMapper->readCPU(0x04E0 + x) & 0x80) {
            goto L_000B02;
        }
        pushAddress(0x000AFF);
        SUB_000A2D();
        if (poppedEntry.value != 0x000AFF) return;
    }
L_000B02:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (!(myMapper->readCPU(0x04E0 + x) & 0x80)) {
            goto L_000B0E;
        }
        pushAddress(0x000B0B);
        SUB_000A2D();
        if (poppedEntry.value != 0x000B0B) return;
    }
L_000B0E:
    goto L_000AD7;
}

void game::SUB_000B12() {
    y = 0x01;
    do {
        a = myMapper->readCPU(0x0088 + y);
        setLoadFlag(a);
        if (!flgN) {
            if (flgZ) {
                goto L_000B66;
            }
            if (myMapper->readCPU(0x00BD + y) == 0) {
                a = myMapper->readCPU(0x0490 + x);
                flgC = true;
                opSBC(myMapper->readCPU(0x0091 + y));
                pushAddress(0x000B27);
                SUB_003084();
                if (poppedEntry.value != 0x000B27) return;
                if (a < 0x08) {
                    a = myMapper->readCPU(0x04A4 + x);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x009A + y));
                    flgC = true;
                    opSBC(0x08);
                    pushAddress(0x000B38);
                    SUB_003084();
                    if (poppedEntry.value != 0x000B38) return;
                    if (a >= 0x0C) {
                        goto L_000B66;
                    }
                    myMapper->writeCPU(0x0088 + y, 0x00);
                    a = 0x01;
                    myMapper->writeCPU(0x007F + y, a);
                    myMapper->writeCPU(0x00C1 + y, a);
                    myMapper->writeCPU(0x0451 + y, 0x0B);
                    myMapper->writeCPU(0x045A + y, 0x20);
                    a = myMapper->readCPU(0x00F0);
                    opORA(0x80);
                    myMapper->writeCPU(0x00F0, a);
                    myMapper->writeCPU(0x04A4 + x, 0xF0);
                    myMapper->writeCPU(0x0530 + x, 0xFF);
                }
            }
        }
    L_000B66:
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_000B6A() {
    x = myMapper->readCPU(0x05D1);
    setLoadFlag(x);
    if (flgN) {
        goto L_000B9D;
    }
    do {
        pushAddress(0x000B6F);
        SUB_000B9E();
        if (poppedEntry.value != 0x000B6F) return;
        if (myMapper->readCPU(0x0604 + x) != 0) {
            a = x;
            opEOR(myMapper->readCPU(0x0019));
            opAND(0x01);
            if (flgZ) {
                y = myMapper->readCPU(0x05FA + x);
                opINY(1);
                a = y;
                opAND(0x03);
                myMapper->writeCPU(0x05FA + x, a);
                pushAddress(0x000B88);
                SUB_000CC1();
                if (poppedEntry.value != 0x000B88) return;
                if (myMapper->readCPU(0x05FA + x) == 0x01) {
                    opDEC(0x060E + x, 1);
                    if (!flgZ) {
                        goto L_000B9A;
                    }
                    opDEC(0x0604 + x, 1);
                }
            }
        }
    L_000B9A:
        opDEX(1);
    } while (!flgN);
L_000B9D:
    popAddress();
}

void game::SUB_000B9E() {
    y = 0x07;
    if (myMapper->readCPU(0x0604 + x) != 0) {
        goto L_000BA8;
    }
    SUB_000C30();
    return;
    do {
    L_000BA8:
        a = myMapper->readCPU(0x0088 + y);
        setLoadFlag(a);
        if (!flgN) {
            if (flgZ) {
                goto L_000C25;
            }
            if (y >= 0x02) {
                if (a == 0x01) {
                    goto L_000C25;
                }
            }
            a = myMapper->readCPU(0x0091 + y);
            flgC = false;
            opADC(0x08);
            flgC = true;
            opSBC(myMapper->readCPU(0x05D2 + x));
            myMapper->writeCPU(0x0012, a);
            pushAddress(0x000BC3);
            SUB_003084();
            if (poppedEntry.value != 0x000BC3) return;
            if (a < 0x12) {
                a = myMapper->readCPU(0x009A + y);
                flgC = false;
                opADC(0x0C);
                flgC = true;
                opSBC(myMapper->readCPU(0x05DC + x));
                myMapper->writeCPU(0x0013, a);
                pushAddress(0x000BD6);
                SUB_003084();
                if (poppedEntry.value != 0x000BD6) return;
                if (a < 0x12) {
                    a = myMapper->readCPU(0x0012);
                    setLoadFlag(a);
                    if (!flgN) {
                        if (a < 0x03) {
                            goto L_000C01;
                        }
                        myMapper->writeCPU(0x041B + y, 0x02);
                        pushAddress(0x000BEA);
                        SUB_000C29();
                        if (poppedEntry.value != 0x000BEA) return;
                        pushAddress(0x000BED);
                        SUB_002BB1();
                        if (poppedEntry.value != 0x000BED) return;
                        if (!flgZ) {
                            goto L_000C01;
                        }
                    }
                    if (a < 0xFD) {
                        a = 0xFE;
                        myMapper->writeCPU(0x041B + y, a);
                        pushAddress(0x000BFB);
                        SUB_002BB1();
                        if (poppedEntry.value != 0x000BFB) return;
                        pushAddress(0x000BFE);
                        SUB_000C29();
                        if (poppedEntry.value != 0x000BFE) return;
                    }
                L_000C01:
                    a = myMapper->readCPU(0x0013);
                    setLoadFlag(a);
                    if (!flgN) {
                        if (a < 0x03) {
                            goto L_000C25;
                        }
                        a = 0x02;
                        myMapper->writeCPU(0x042D + y, a);
                        pushAddress(0x000C0E);
                        SUB_002BA8();
                        if (poppedEntry.value != 0x000C0E) return;
                        pushAddress(0x000C11);
                        SUB_000C29();
                        if (poppedEntry.value != 0x000C11) return;
                        if (!flgZ) {
                            goto L_000C25;
                        }
                    }
                    if (a >= 0xFD) {
                        goto L_000C25;
                    }
                    a = 0xFE;
                    myMapper->writeCPU(0x042D + y, a);
                    pushAddress(0x000C1F);
                    SUB_002BA8();
                    if (poppedEntry.value != 0x000C1F) return;
                    pushAddress(0x000C22);
                    SUB_000C29();
                    if (poppedEntry.value != 0x000C22) return;
                }
            }
        }
    L_000C25:
        opDEY(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_000C29() {
    a = myMapper->readCPU(0x00F1);
    opORA(0x02);
    myMapper->writeCPU(0x00F1, a);
    popAddress();
}

void game::SUB_000C30() {
    while (true) {
        a = myMapper->readCPU(0x0088 + y);
        setLoadFlag(a);
        if (!flgN) {
            if (flgZ) {
                goto L_000CAE;
            }
            if (y >= 0x02) {
                if (myMapper->readCPU(0x05FA + x) != 0x03) {
                    goto L_000C69;
                }
                a = myMapper->readCPU(0x05D2 + x);
                flgC = true;
                opSBC(0x0A);
                opCMP(a, myMapper->readCPU(0x0091 + y));
                if (!flgC) {
                    opADC(0x04);
                    if (a >= myMapper->readCPU(0x0091 + y)) {
                        a = myMapper->readCPU(0x05DC + x);
                        flgC = true;
                        opSBC(0x1C);
                        opCMP(a, myMapper->readCPU(0x009A + y));
                        if (!flgC) {
                            opADC(0x04);
                            if (a >= myMapper->readCPU(0x009A + y)) {
                                pushAddress(0x000C66);
                                SUB_000CB5();
                                if (poppedEntry.value != 0x000C66) return;
                            }
                        }
                    }
                }
            }
        L_000C69:
            a = myMapper->readCPU(0x0091 + y);
            flgC = false;
            opADC(0x08);
            flgC = true;
            opSBC(myMapper->readCPU(0x05D2 + x));
            pushAddress(0x000C73);
            SUB_003084();
            if (poppedEntry.value != 0x000C73) return;
            myMapper->writeCPU(0x0012, a);
            a = myMapper->readCPU(0x009A + y);
            flgC = false;
            opADC(0x0C);
            flgC = true;
            opSBC(myMapper->readCPU(0x05DC + x));
            pushAddress(0x000C82);
            SUB_003084();
            if (poppedEntry.value != 0x000C82) return;
            myMapper->writeCPU(0x0013, a);
            if (myMapper->readCPU(0x05FA + x) != 0x03) {
                a = myMapper->readCPU(0x0012);
                opPHA();
                a = myMapper->readCPU(0x0013);
                myMapper->writeCPU(0x0012, a);
                opPLA();
                myMapper->writeCPU(0x0013, a);
            }
            if (myMapper->readCPU(0x0012) < 0x14) {
                if (myMapper->readCPU(0x0013) >= 0x0B) {
                    goto L_000CAE;
                }
                myMapper->writeCPU(0x0604 + x, 0x01);
                myMapper->writeCPU(0x060E + x, 0x32);
            }
        }
    L_000CAE:
        opDEY(1);
        if (flgN) {
            goto L_000CB4;
        }
    }
L_000CB4:
    popAddress();
}

void game::SUB_000CB5() {
    a = x;
    opPHA();
    x = y;
    opINC(0x00CB, 1);
    pushAddress(0x000CBB);
    SUB_002979();
    if (poppedEntry.value != 0x000CBB) return;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_000CC1() {
    myMapper->writeCPU(0x0057, myMapper->readCPU(0x05F0 + x));
    myMapper->writeCPU(0x0058, myMapper->readCPU(0x05E6 + x));
    myMapper->writeCPU(0x0059, 0x03);
    y = myMapper->readCPU(0x05FA + x);
    myMapper->writeCPU(0x005A, myMapper->readCPU(0xCD1C + y));
    myMapper->writeCPU(0x005B, myMapper->readCPU(0xCD20 + y));
    myMapper->writeCPU(0x005C, myMapper->readCPU(0xCD24 + y));
    pushAddress(0x000CE1);
    SUB_000D05();
    if (poppedEntry.value != 0x000CE1) return;
    myMapper->writeCPU(0x005A, myMapper->readCPU(0xCD28 + y));
    myMapper->writeCPU(0x005B, myMapper->readCPU(0xCD2C + y));
    myMapper->writeCPU(0x005C, myMapper->readCPU(0xCD30 + y));
    pushAddress(0x000CF3);
    SUB_000D05();
    if (poppedEntry.value != 0x000CF3) return;
    myMapper->writeCPU(0x005A, myMapper->readCPU(0xCD34 + y));
    myMapper->writeCPU(0x005B, myMapper->readCPU(0xCD38 + y));
    myMapper->writeCPU(0x005C, myMapper->readCPU(0xCD3C + y));
    SUB_000D05();
    return;
}

void game::SUB_000D05() {
    a = y;
    opPHA();
    a = 0x57;
    y = 0x00;
    pushAddress(0x000D0B);
    SUB_000127();
    if (poppedEntry.value != 0x000D0B) return;
    opPLA();
    y = a;
    a = myMapper->readCPU(0x0058);
    flgC = false;
    opADC(0x20);
    myMapper->writeCPU(0x0058, a);
    if (!flgC) {
        goto L_000D1B;
    }
    opINC(0x0057, 1);
L_000D1B:
    popAddress();
}

void game::SUB_000D40() {
    x = 0x09;
    do {
        myMapper->writeCPU(0x055D + x, 0xFF);
        myMapper->writeCPU(0x057B + x, 0xF0);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_000D50() {
    opDEC(0x05CC, 1);
    if (!flgZ) {
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x001B);
    opAND(0x3F);
    opADC(0x28);
    myMapper->writeCPU(0x05CC, a);
    x = 0x09;
    do {
        if (myMapper->readCPU(0x055D + x) & 0x80) {
            goto L_000D6A;
        }
        opDEX(1);
    } while (!flgN);
    popAddress();
    return;
L_000D6A:
    a = 0x00;
    myMapper->writeCPU(0x055D + x, a);
    myMapper->writeCPU(0x0599 + x, a);
    myMapper->writeCPU(0x058F + x, a);
    a = 0x80;
    myMapper->writeCPU(0x0571 + x, a);
    myMapper->writeCPU(0x0585 + x, a);
    myMapper->writeCPU(0x057B + x, 0xD0);
    pushAddress(0x000D82);
    SUB_0031A9();
    if (poppedEntry.value != 0x000D82) return;
    opAND(0x03);
    y = a;
    myMapper->writeCPU(0x0567 + x, myMapper->readCPU(0xCEA4 + y));
    y = 0x00;
    a = myMapper->readCPU(0x001B);
    setLoadFlag(a);
    myMapper->writeCPU(0x05B7 + x, a);
    if (!flgN) {
        goto L_000D98;
    }
    opDEY(1);
L_000D98:
    myMapper->writeCPU(0x05C1 + x, y);
    opDEC(0x05CB, 1);
    popAddress();
}

void game::SUB_000DA0() {
    x = 0x09;
    while (true) {
        a = myMapper->readCPU(0x055D + x);
        setLoadFlag(a);
        if (!flgN) {
            if (flgZ) {
                goto L_000DF2;
            }
            myMapper->writeCPU(0x0012, myMapper->readCPU(0x0599 + x));
            myMapper->writeCPU(0x0013, myMapper->readCPU(0x058F + x));
            pushAddress(0x000DB3);
            SUB_00319C();
            if (poppedEntry.value != 0x000DB3) return;
            a = myMapper->readCPU(0x05B7 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x0012));
            myMapper->writeCPU(0x05B7 + x, a);
            myMapper->writeCPU(0x0012, a);
            a = myMapper->readCPU(0x05C1 + x);
            opADC(myMapper->readCPU(0x0013));
            myMapper->writeCPU(0x05C1 + x, a);
            myMapper->writeCPU(0x0013, a);
            pushAddress(0x000DCB);
            SUB_00319C();
            if (poppedEntry.value != 0x000DCB) return;
            a = myMapper->readCPU(0x0599 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0x0012));
            myMapper->writeCPU(0x0599 + x, a);
            a = myMapper->readCPU(0x058F + x);
            opSBC(myMapper->readCPU(0x0013));
            myMapper->writeCPU(0x058F + x, a);
            a = myMapper->readCPU(0x0571 + x);
            flgC = false;
            opADC(myMapper->readCPU(0x0599 + x));
            myMapper->writeCPU(0x0571 + x, a);
            a = myMapper->readCPU(0x0567 + x);
            opADC(myMapper->readCPU(0x058F + x));
            myMapper->writeCPU(0x0567 + x, a);
        L_000DF2:
            a = myMapper->readCPU(0x0585 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0x055A));
            myMapper->writeCPU(0x0585 + x, a);
            if (!flgC) {
                opDEC(0x057B + x, 1);
            }
            a = myMapper->readCPU(0x057B + x);
            if (a == 0xF0) {
                goto L_000E13;
            }
            if (a >= 0xA8) {
                goto L_000E18;
            }
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x055D + x, a);
            if (!flgZ) {
                goto L_000E18;
            }
        L_000E13:
            myMapper->writeCPU(0x055D + x, 0xFF);
        }
    L_000E18:
        pushAddress(0x000E18);
        SUB_000E25();
        if (poppedEntry.value != 0x000E18) return;
        pushAddress(0x000E1B);
        SUB_000EC4();
        if (poppedEntry.value != 0x000E1B) return;
        opDEX(1);
        if (flgN) {
            goto L_000E24;
        }
    }
L_000E24:
    popAddress();
}

void game::SUB_000E25() {
    y = myMapper->readCPU(0x055D + x);
    opINY(1);
    myMapper->writeCPU(0x0013, myMapper->readCPU(0xCEA8 + y));
    a = x;
    myMapper->writeCPU(0x0012, a);
    opASL_A(1);
    opADC(myMapper->readCPU(0x0012));
    opASL_A(2);
    y = a;
    a = myMapper->readCPU(0x057B + x);
    myMapper->writeCPU(0x0250 + y, a);
    myMapper->writeCPU(0x0254 + y, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0258 + y, a);
    a = myMapper->readCPU(0x0567 + x);
    myMapper->writeCPU(0x0253 + y, a);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x025B + y, a);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x0257 + y, a);
    a = myMapper->readCPU(0x0013);
    myMapper->writeCPU(0x0252 + y, a);
    myMapper->writeCPU(0x0256 + y, a);
    myMapper->writeCPU(0x025A + y, a);
    if (myMapper->readCPU(0x055D + x) & 0x80) {
        goto L_000E8F;
    }
    myMapper->writeCPU(0x0251 + y, 0xA8);
    myMapper->writeCPU(0x0255 + y, 0xA9);
    a = myMapper->readCPU(0x0019);
    opLSR_A(4);
    opAND(0x07);
    myMapper->writeCPU(0x0013, x);
    x = a;
    myMapper->writeCPU(0x0259 + y, myMapper->readCPU(0xCEAB + x));
    a = myMapper->readCPU(0x025A + y);
    opEOR(myMapper->readCPU(0xCEB3 + x));
    myMapper->writeCPU(0x025A + y, a);
    x = myMapper->readCPU(0x0013);
    popAddress();
    return;
L_000E8F:
    myMapper->writeCPU(0x057B + x, 0xF0);
    myMapper->writeCPU(0x0251 + y, 0xAC);
    myMapper->writeCPU(0x0255 + y, 0xAD);
    myMapper->writeCPU(0x0259 + y, 0xFC);
    popAddress();
}

void game::SUB_000EC4() {
    y = 0x01;
    do {
        a = myMapper->readCPU(0x0088 + y);
        setLoadFlag(a);
        if (!flgN) {
            if (flgZ) {
                goto L_000F05;
            }
            if (myMapper->readCPU(0x055D + x) & 0x80) {
                goto L_000F08;
            }
            a = myMapper->readCPU(0x009A + y);
            if (a < 0xC0) {
                flgC = true;
                opSBC(myMapper->readCPU(0x057B + x));
                pushAddress(0x000EDD);
                SUB_003084();
                if (poppedEntry.value != 0x000EDD) return;
                if (a < 0x18) {
                    a = myMapper->readCPU(0x0091 + y);
                    flgC = true;
                    opSBC(myMapper->readCPU(0x0567 + x));
                    pushAddress(0x000EEB);
                    SUB_003084();
                    if (poppedEntry.value != 0x000EEB) return;
                    if (a >= 0x10) {
                        goto L_000F05;
                    }
                    myMapper->writeCPU(0x055D + x, 0xFF);
                    a = myMapper->readCPU(0x05CD + y);
                    flgC = false;
                    opADC(0x01);
                    myMapper->writeCPU(0x05CD + y, a);
                    myMapper->writeCPU(0x00F0, 0x02);
                    popAddress();
                    return;
                }
            }
        }
    L_000F05:
        opDEY(1);
    } while (!flgN);
L_000F08:
    popAddress();
}

void game::SUB_000F09() {
    myMapper->writeCPU(0x00F2, 0x20);
    pushAddress(0x000F0D);
    SUB_0010D8();
    if (poppedEntry.value != 0x000F0D) return;
    pushAddress(0x000F10);
    SUB_000D40();
    if (poppedEntry.value != 0x000F10) return;
    x = myMapper->readCPU(0x0040);
    do {
        if (myMapper->readCPU((0x0041 + x) & 0x00ff) & 0x80) {
            goto L_000F1C;
        }
        pushAddress(0x000F19);
        SUB_0033A6();
        if (poppedEntry.value != 0x000F19) return;
    L_000F1C:
        opDEX(1);
    } while (!flgN);
    x = 0x00;
    myMapper->writeCPU(0x00BD, x);
    myMapper->writeCPU(0x00BE, x);
    myMapper->writeCPU(0x05CB, 0x14);
    do {
        do {
        L_000F2A:
            pushAddress(0x000F2A);
            SUB_003466();
            if (poppedEntry.value != 0x000F2A) return;
            opINC(0x004C, 1);
            pushAddress(0x000F2F);
            SUB_0018D3();
            if (poppedEntry.value != 0x000F2F) return;
            pushAddress(0x000F32);
            SUB_002687();
            if (poppedEntry.value != 0x000F32) return;
            if (myMapper->readCPU(0x05CB) == 0) {
                goto L_000F3D;
            }
            pushAddress(0x000F3A);
            SUB_000D50();
            if (poppedEntry.value != 0x000F3A) return;
        L_000F3D:
            pushAddress(0x000F3D);
            SUB_000DA0();
            if (poppedEntry.value != 0x000F3D) return;
        } while (myMapper->readCPU(0x05CB) != 0);
        x = 0x09;
        do {
            if (!(myMapper->readCPU(0x055D + x) & 0x80)) {
                goto L_000F2A;
            }
            opDEX(1);
        } while (!flgN);
    } while (myMapper->readCPU(0x0019) != 0);
    pushAddress(0x000F53);
    SUB_00123C();
    if (poppedEntry.value != 0x000F53) return;
    x = 0x02;
    myMapper->writeCPU(0x0046, x);
    pushAddress(0x000F5A);
    SUB_003454();
    if (poppedEntry.value != 0x000F5A) return;
    a = 0x21;
    y = 0xD1;
    pushAddress(0x000F61);
    SUB_000127();
    if (poppedEntry.value != 0x000F61) return;
    a = 0x50;
    y = 0xD1;
    pushAddress(0x000F68);
    SUB_000127();
    if (poppedEntry.value != 0x000F68) return;
    a = 0x5B;
    y = 0xD1;
    pushAddress(0x000F6F);
    SUB_000127();
    if (poppedEntry.value != 0x000F6F) return;
    x = myMapper->readCPU(0x0040);
    do {
        myMapper->writeCPU((0x0091 + x) & 0x00ff, 0x20);
        myMapper->writeCPU((0x009A + x) & 0x00ff, myMapper->readCPU(0xD194 + x));
        myMapper->writeCPU((0x007F + x) & 0x00ff, 0x03);
        myMapper->writeCPU(0x0448 + x, 0x01);
        pushAddress(0x000F86);
        SUB_0033A6();
        if (poppedEntry.value != 0x000F86) return;
        pushAddress(0x000F89);
        SUB_00239A();
        if (poppedEntry.value != 0x000F89) return;
        opDEX(1);
    } while (!flgN);
    a = 0x44;
    myMapper->writeCPU(0x0567, a);
    myMapper->writeCPU(0x0568, a);
    myMapper->writeCPU(0x057B, 0x54);
    myMapper->writeCPU(0x057C, 0x74);
    a = 0x01;
    myMapper->writeCPU(0x055D, a);
    myMapper->writeCPU(0x055E, a);
    x = myMapper->readCPU(0x0040);
    do {
        pushAddress(0x000FAB);
        SUB_000E25();
        if (poppedEntry.value != 0x000FAB) return;
        opDEX(1);
    } while (!flgN);
    pushAddress(0x000FB1);
    SUB_003452();
    if (poppedEntry.value != 0x000FB1) return;
    myMapper->writeCPU(0x0057, 0x2B);
    a = 0x24;
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x0059, a);
    myMapper->writeCPU(0x0054, 0x0C);
    myMapper->writeCPU(0x0055, 0x0B);
    myMapper->writeCPU(0x0056, 0x05);
    a = myMapper->readCPU(0x05CD);
    pushAddress(0x000FCD);
    SUB_0011BF();
    if (poppedEntry.value != 0x000FCD) return;
    if (myMapper->readCPU(0x0040) != 0) {
        myMapper->writeCPU(0x0055, 0x0F);
        a = myMapper->readCPU(0x05CE);
        pushAddress(0x000FDB);
        SUB_0011BF();
        if (poppedEntry.value != 0x000FDB) return;
    }
    pushAddress(0x000FDE);
    SUB_003452();
    if (poppedEntry.value != 0x000FDE) return;
    myMapper->writeCPU(0x0057, myMapper->readCPU(0x0559));
    a = 0x00;
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x0059, a);
    myMapper->writeCPU(0x0054, 0x08);
    myMapper->writeCPU(0x0055, 0x0B);
    myMapper->writeCPU(0x0056, 0x03);
    a = myMapper->readCPU(0x0559);
    pushAddress(0x000FFB);
    SUB_00010F();
    if (poppedEntry.value != 0x000FFB) return;
    if (myMapper->readCPU(0x0040) != 0) {
        myMapper->writeCPU(0x0055, 0x0F);
        pushAddress(0x001006);
        SUB_00010F();
        if (poppedEntry.value != 0x001006) return;
    }
    a = 0xFF;
    myMapper->writeCPU(0x055D, a);
    myMapper->writeCPU(0x055E, a);
    x = myMapper->readCPU(0x0040);
    do {
        pushAddress(0x001013);
        SUB_000E25();
        if (poppedEntry.value != 0x001013) return;
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x00F0, 0x02);
    x = 0x02;
    pushAddress(0x00101F);
    SUB_003454();
    if (poppedEntry.value != 0x00101F) return;
    x = myMapper->readCPU(0x0040);
    do {
        pushAddress(0x001024);
        SUB_000E25();
        if (poppedEntry.value != 0x001024) return;
        opDEX(1);
    } while (!flgN);
    pushAddress(0x00102A);
    SUB_001196();
    if (poppedEntry.value != 0x00102A) return;
    pushAddress(0x00102D);
    SUB_003452();
    if (poppedEntry.value != 0x00102D) return;
    myMapper->writeCPU(0x00F0, 0x01);
    pushAddress(0x001034);
    SUB_001117();
    if (poppedEntry.value != 0x001034) return;
    if (flgZ) {
        a = 0x66;
        y = 0xD1;
        pushAddress(0x00103D);
        SUB_000127();
        if (poppedEntry.value != 0x00103D) return;
        pushAddress(0x001040);
        SUB_00345B();
        if (poppedEntry.value != 0x001040) return;
        x = 0x1A;
        do {
            myMapper->writeCPU((0x0057 + x) & 0x00ff, myMapper->readCPU(0xD17A + x));
            opDEX(1);
        } while (!flgN);
        myMapper->writeCPU(0x0068, myMapper->readCPU(0x055B));
        myMapper->writeCPU(0x0069, myMapper->readCPU(0x055C));
        pushAddress(0x001057);
        SUB_000123();
        if (poppedEntry.value != 0x001057) return;
        myMapper->writeCPU(0x00F2, 0x10);
    }
    x = 0x78;
    pushAddress(0x001060);
    SUB_003454();
    if (poppedEntry.value != 0x001060) return;
    pushAddress(0x001063);
    SUB_001196();
    if (poppedEntry.value != 0x001063) return;
    do {
        do {
            myMapper->writeCPU(0x003E, 0x00);
            x = 0x04;
            pushAddress(0x00106C);
            SUB_001209();
            if (poppedEntry.value != 0x00106C) return;
            pushAddress(0x00106F);
            SUB_000123();
            if (poppedEntry.value != 0x00106F) return;
            if (myMapper->readCPU(0x0040) == 0) {
                goto L_001084;
            }
            opINC(0x003E, 1);
            x = 0x12;
            pushAddress(0x00107A);
            SUB_001209();
            if (poppedEntry.value != 0x00107A) return;
            a = 0x65;
            y = 0x00;
            pushAddress(0x001081);
            SUB_000127();
            if (poppedEntry.value != 0x001081) return;
        L_001084:
            myMapper->writeCPU(0x00F1, 0x01);
            x = 0x02;
            pushAddress(0x00108A);
            SUB_003454();
            if (poppedEntry.value != 0x00108A) return;
        } while (myMapper->readCPU(0x005D) != 0x24);
        if (myMapper->readCPU(0x0040) == 0) {
            goto L_00109E;
        }
    } while (myMapper->readCPU(0x006B) != 0x24);
L_00109E:
    x = 0x0A;
    pushAddress(0x0010A0);
    SUB_003454();
    if (poppedEntry.value != 0x0010A0) return;
    pushAddress(0x0010A3);
    SUB_001117();
    if (poppedEntry.value != 0x0010A3) return;
    if (!flgZ) {
        goto L_0010C4;
    }
    myMapper->writeCPU(0x0047, myMapper->readCPU(0x055B));
    myMapper->writeCPU(0x0048, myMapper->readCPU(0x055C));
    myMapper->writeCPU(0x003E, myMapper->readCPU(0x0040));
    do {
        pushAddress(0x0010B6);
        SUB_0016D2();
        if (poppedEntry.value != 0x0010B6) return;
        opDEC(0x003E, 1);
    } while (!flgN);
    myMapper->writeCPU(0x00F1, 0x01);
    pushAddress(0x0010C1);
    SUB_003452();
    if (poppedEntry.value != 0x0010C1) return;
L_0010C4:
    a = 0x00;
    myMapper->writeCPU(0x0047, a);
    myMapper->writeCPU(0x0048, a);
    x = 0x01;
    do {
        a = myMapper->readCPU((0x0041 + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgN) {
            goto L_0010D2;
        }
        myMapper->writeCPU((0x0088 + x) & 0x00ff, a);
    L_0010D2:
        opDEX(1);
    } while (!flgN);
    SUB_003349();
    return;
}

void game::SUB_0010D8() {
    x = myMapper->readCPU(0x0558);
    myMapper->writeCPU(0x0559, myMapper->readCPU(0xD103 + x));
    myMapper->writeCPU(0x055A, myMapper->readCPU(0xD108 + x));
    myMapper->writeCPU(0x055B, myMapper->readCPU(0xD10D + x));
    myMapper->writeCPU(0x055C, myMapper->readCPU(0xD112 + x));
    if (x >= 0x04) {
        goto L_0010FA;
    }
    opINC(0x0558, 1);
L_0010FA:
    a = 0x00;
    myMapper->writeCPU(0x05CD, a);
    myMapper->writeCPU(0x05CE, a);
    popAddress();
}

void game::SUB_001117() {
    a = myMapper->readCPU(0x05CD);
    flgC = false;
    opADC(myMapper->readCPU(0x05CE));
    opCMP(a, 0x14);
    popAddress();
}

void game::SUB_001196() {
    x = 0x1C;
    do {
        myMapper->writeCPU((0x0057 + x) & 0x00ff, myMapper->readCPU(0xD134 + x));
        opDEX(1);
    } while (!flgN);
    x = 0x04;
    y = myMapper->readCPU(0x05CD);
    pushAddress(0x0011A5);
    SUB_0011D2();
    if (poppedEntry.value != 0x0011A5) return;
    x = 0x12;
    y = myMapper->readCPU(0x05CE);
    pushAddress(0x0011AD);
    SUB_0011D2();
    if (poppedEntry.value != 0x0011AD) return;
    pushAddress(0x0011B0);
    SUB_000123();
    if (poppedEntry.value != 0x0011B0) return;
    if (myMapper->readCPU(0x0040) != 0) {
        goto L_0011B8;
    }
    popAddress();
    return;
L_0011B8:
    a = 0x65;
    y = 0x00;
    SUB_000127();
    return;
}

void game::SUB_0011BF() {
    y = 0x00;
    while (true) {
        opCMP(a, 0x0A);
        if (!flgC) {
            goto L_0011CB;
        }
        opINY(1);
        opSBC(0x0A);
    }
L_0011CB:
    myMapper->writeCPU(0x005A, y);
    myMapper->writeCPU(0x005B, a);
    SUB_00010F();
    return;
}

void game::SUB_0011D2() {
L_0011D2:
    opDEY(1);
    if (flgN) {
        SUB_0011F4();
        return;
    }
    a = myMapper->readCPU(0x0559);
    flgC = false;
    opADC(myMapper->readCPU((0x0059 + x) & 0x00ff));
    opCMP(a, 0x0A);
    if (flgC) {
        opSBC(0x0A);
        opINC((0x0058 + x) & 0x00ff, 1);
    }
    myMapper->writeCPU((0x0059 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0058 + x) & 0x00ff);
    opCMP(a, 0x0A);
    if (!flgC) {
        goto L_0011F1;
    }
    opSBC(0x0A);
    opINC((0x0057 + x) & 0x00ff, 1);
    myMapper->writeCPU((0x0058 + x) & 0x00ff, a);
L_0011F1:
    goto L_0011D2;
}

void game::SUB_0011F4() {
    y = 0x00;
    do {
        a = myMapper->readCPU((0x0057 + x) & 0x00ff);
        setLoadFlag(a);
        if (flgZ) {
            goto L_0011FE;
        }
        if (a != 0x24) {
            goto L_001208;
        }
    L_0011FE:
        myMapper->writeCPU((0x0057 + x) & 0x00ff, 0x24);
        opINX(1);
        opINY(1);
    } while (y != 0x04);
L_001208:
    popAddress();
}

void game::SUB_001209() {
    a = myMapper->readCPU((0x0059 + x) & 0x00ff);
    if (a != 0x24) {
        y = a;
        setLoadFlag(y);
        if (flgZ) {
            if (myMapper->readCPU((0x0058 + x) & 0x00ff) == 0x24) {
                goto L_001239;
            }
            if (myMapper->readCPU((0x0058 + x) & 0x00ff) != 0) {
                goto L_001228;
            }
            if (myMapper->readCPU((0x0057 + x) & 0x00ff) == 0x24) {
                goto L_001239;
            }
            myMapper->writeCPU((0x0058 + x) & 0x00ff, 0x0A);
            opDEC((0x0057 + x) & 0x00ff, 1);
        L_001228:
            myMapper->writeCPU((0x0059 + x) & 0x00ff, 0x0A);
            opDEC((0x0058 + x) & 0x00ff, 1);
        }
        opDEC((0x0059 + x) & 0x00ff, 1);
        a = x;
        opPHA();
        a = 0x0A;
        pushAddress(0x001234);
        SUB_0016D4();
        if (poppedEntry.value != 0x001234) return;
        opPLA();
        x = a;
    }
L_001239:
    SUB_0011F4();
    return;
}

void game::SUB_00123C() {
    pushAddress(0x00123C);
    SUB_000100();
    if (poppedEntry.value != 0x00123C) return;
    pushAddress(0x00123F);
    SUB_0000F0();
    if (poppedEntry.value != 0x00123F) return;
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x00);
    pushAddress(0x00124C);
    SUB_00126B();
    if (poppedEntry.value != 0x00124C) return;
    pushAddress(0x00124F);
    SUB_00126B();
    if (poppedEntry.value != 0x00124F) return;
    pushAddress(0x001252);
    SUB_0000FA();
    if (poppedEntry.value != 0x001252) return;
    pushAddress(0x001255);
    SUB_00010B();
    if (poppedEntry.value != 0x001255) return;
    x = 0x3F;
    y = 0x00;
    myMapper->writeCPU(0x004C, y);
    do {
        myMapper->writeCPU(0x0200 + y, 0xF0);
        opINY(4);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_00126B() {
    x = 0xF0;
    a = 0x24;
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
    popAddress();
}

void game::SUB_001289() {
    pushAddress(0x001289);
    SUB_000100();
    if (poppedEntry.value != 0x001289) return;
    pushAddress(0x00128C);
    SUB_0000F0();
    if (poppedEntry.value != 0x00128C) return;
    if (myMapper->readCPU(0x0016) != 0) {
        SUB_001568();
        return;
    }
    y = myMapper->readCPU(0x003B);
    myMapper->writeCPU(0x001D, myMapper->readCPU(0xDB20 + y));
    myMapper->writeCPU(0x001E, myMapper->readCPU(0xDB30 + y));
    pushAddress(0x0012A2);
    SUB_00148D();
    if (poppedEntry.value != 0x0012A2) return;
    x = 0x00;
    while (true) {
        pushAddress(0x0012A7);
        SUB_0014DB();
        if (poppedEntry.value != 0x0012A7) return;
        if (a == 0xFF) {
            goto L_001318;
        }
        myMapper->writeCPU(0x0054, a);
        pushAddress(0x0012B0);
        SUB_0014DB();
        if (poppedEntry.value != 0x0012B0) return;
        myMapper->writeCPU(0x0055, a);
        y = 0x03;
        do {
            pushAddress(0x0012B7);
            SUB_0014F1();
            if (poppedEntry.value != 0x0012B7) return;
            myMapper->writeCPU(0x0012, 0x04);
            a = myMapper->readCPU(0xD489 + y);
            do {
                myMapper->writeCPU(0x2007, a);
                flgC = false;
                opADC(0x04);
                opDEC(0x0012, 1);
            } while (!flgZ);
            opINC(0x0055, 1);
            opDEY(1);
        } while (!flgN);
        a = myMapper->readCPU(0x0055);
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(0x0055, a);
        pushAddress(0x0012D7);
        SUB_001512();
        if (poppedEntry.value != 0x0012D7) return;
        myMapper->writeCPU((0x00A6 + x) & 0x00ff, a);
        opINC(0x0054, 2);
        pushAddress(0x0012E0);
        SUB_001512();
        if (poppedEntry.value != 0x0012E0) return;
        myMapper->writeCPU((0x00A9 + x) & 0x00ff, a);
        opINC(0x0055, 2);
        pushAddress(0x0012E9);
        SUB_001512();
        if (poppedEntry.value != 0x0012E9) return;
        myMapper->writeCPU((0x00AF + x) & 0x00ff, a);
        opDEC(0x0054, 2);
        pushAddress(0x0012F2);
        SUB_001512();
        if (poppedEntry.value != 0x0012F2) return;
        myMapper->writeCPU((0x00AC + x) & 0x00ff, a);
        myMapper->writeCPU(0x00A4, x);
        a = 0x03;
        pushAddress(0x0012FB);
        SUB_00084C();
        if (poppedEntry.value != 0x0012FB) return;
        pushAddress(0x0012FE);
        SUB_000172();
        if (poppedEntry.value != 0x0012FE) return;
        x = myMapper->readCPU(0x00A4);
        a = myMapper->readCPU(0x0054);
        opASL_A(3);
        flgC = false;
        opADC(0x10);
        myMapper->writeCPU((0x00B2 + x) & 0x00ff, a);
        a = myMapper->readCPU(0x0055);
        opASL_A(3);
        myMapper->writeCPU((0x00B5 + x) & 0x00ff, a);
        opINX(1);
    }
L_001318:
    opDEX(1);
    myMapper->writeCPU(0x00A3, x);
    x = 0x00;
    while (true) {
        pushAddress(0x00131D);
        SUB_0014DB();
        if (poppedEntry.value != 0x00131D) return;
        if (a == 0xFF) {
            goto L_001374;
        }
        myMapper->writeCPU(0x0054, a);
        pushAddress(0x001326);
        SUB_0014DB();
        if (poppedEntry.value != 0x001326) return;
        myMapper->writeCPU(0x0055, a);
        pushAddress(0x00132B);
        SUB_0014DB();
        if (poppedEntry.value != 0x00132B) return;
        myMapper->writeCPU(0x05FA + x, a);
        a = myMapper->readCPU(0x0054);
        opASL_A(3);
        opADC(0x0C);
        myMapper->writeCPU(0x05D2 + x, a);
        a = myMapper->readCPU(0x0055);
        opASL_A(3);
        opADC(0x0C);
        myMapper->writeCPU(0x05DC + x, a);
        myMapper->writeCPU(0x0604 + x, 0x00);
        pushAddress(0x00134A);
        SUB_0014F1();
        if (poppedEntry.value != 0x00134A) return;
        myMapper->writeCPU(0x05E6 + x, a);
        myMapper->writeCPU(0x05F0 + x, myMapper->readCPU(0x0013));
        pushAddress(0x001355);
        SUB_001562();
        if (poppedEntry.value != 0x001355) return;
        pushAddress(0x001358);
        SUB_001532();
        if (poppedEntry.value != 0x001358) return;
        opINC(0x0054, 2);
        pushAddress(0x00135F);
        SUB_001532();
        if (poppedEntry.value != 0x00135F) return;
        opINC(0x0055, 2);
        pushAddress(0x001366);
        SUB_001532();
        if (poppedEntry.value != 0x001366) return;
        opDEC(0x0054, 2);
        pushAddress(0x00136D);
        SUB_001532();
        if (poppedEntry.value != 0x00136D) return;
        opINX(1);
    }
L_001374:
    opDEX(1);
    myMapper->writeCPU(0x05D1, x);
    pushAddress(0x001378);
    SUB_0014DB();
    if (poppedEntry.value != 0x001378) return;
    myMapper->writeCPU(0x001F, a);
    pushAddress(0x00137D);
    SUB_0014DB();
    if (poppedEntry.value != 0x00137D) return;
    myMapper->writeCPU(0x0020, a);
    y = 0x00;
    x = myMapper->readCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y);
    opDEX(1);
    if (!flgN) {
        goto L_00138F;
    }
    opINC(0x00C8, 1);
    goto L_0013B0;
L_00138F:
    opINY(1);
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU((0x0093 + x) & 0x00ff, a);
        a = myMapper->readCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU((0x009C + x) & 0x00ff, a);
        a = myMapper->readCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y);
        opINY(1);
        myMapper->writeCPU(0x0453 + x, a);
        myMapper->writeCPU((0x0081 + x) & 0x00ff, 0x02);
        myMapper->writeCPU((0x008A + x) & 0x00ff, 0x01);
        myMapper->writeCPU(0x0441 + x, myMapper->readCPU(0x00C6));
        opDEX(1);
    } while (!flgN);
L_0013B0:
    pushAddress(0x0013B0);
    SUB_0014DB();
    if (poppedEntry.value != 0x0013B0) return;
    myMapper->writeCPU(0x00CD, a);
    pushAddress(0x0013B5);
    SUB_0014DB();
    if (poppedEntry.value != 0x0013B5) return;
    myMapper->writeCPU(0x0023, a);
    pushAddress(0x0013BA);
    SUB_0014DB();
    if (poppedEntry.value != 0x0013BA) return;
    y = a;
    myMapper->writeCPU(0x0024, a);
    a = myMapper->readCPU(0x0023);
    pushAddress(0x0013C2);
    SUB_001482();
    if (poppedEntry.value != 0x0013C2) return;
    myMapper->writeCPU(0x0025, a);
    myMapper->writeCPU(0x0026, y);
    pushAddress(0x0013C9);
    SUB_001482();
    if (poppedEntry.value != 0x0013C9) return;
    myMapper->writeCPU(0x0027, a);
    myMapper->writeCPU(0x0028, y);
    pushAddress(0x0013D0);
    SUB_001482();
    if (poppedEntry.value != 0x0013D0) return;
    myMapper->writeCPU(0x0029, a);
    myMapper->writeCPU(0x002A, y);
    SUB_0013D7();
    return;
}

void game::SUB_0013D7() {
    pushAddress(0x0013D7);
    SUB_0015CF();
    if (poppedEntry.value != 0x0013D7) return;
    pushAddress(0x0013DA);
    SUB_0013E3();
    if (poppedEntry.value != 0x0013DA) return;
    pushAddress(0x0013DD);
    SUB_0000FA();
    if (poppedEntry.value != 0x0013DD) return;
    SUB_00010B();
    return;
}

void game::SUB_0013E3() {
    x = 0x22;
    do {
        myMapper->writeCPU((0x0057 + x) & 0x00ff, myMapper->readCPU(0xD42D + x));
        opDEX(1);
    } while (!flgN);
    if (myMapper->readCPU(0x00C8) != 0) {
        goto L_001406;
    }
    a = myMapper->readCPU(0x003B);
    opAND(0x0C);
    opORA(0x03);
    y = a;
    x = 0x03;
    do {
        myMapper->writeCPU((0x005A + x) & 0x00ff, myMapper->readCPU(0xD450 + y));
        opDEY(1);
        opDEX(1);
    } while (!flgN);
    do {
        do {
            SUB_000123();
            return;
        L_001406:
            x = myMapper->readCPU(0x0558);
            myMapper->writeCPU(0x001D, myMapper->readCPU(0xD460 + x));
            myMapper->writeCPU(0x001E, myMapper->readCPU(0xD465 + x));
            x = 0x03;
            y = 0x07;
            do {
                myMapper->writeCPU((0x0072 + x) & 0x00ff, myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y));
                opDEY(1);
                opDEX(1);
            } while (!flgN);
        } while (myMapper->readCPU(0x0016) != 0);
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y);
            myMapper->writeCPU(0x005A + y, a);
            opDEY(1);
        } while (!flgN);
    } while (flgN);
    //NOP
    SUB_001482();
    return;
}

void game::SUB_001482() {
    flgC = true;
    opADC(myMapper->readCPU(0x00CD));
    if (!flgC) {
        goto L_001488;
    }
    opINY(1);
L_001488:
    popAddress();
}

void game::SUB_00148D() {
    do {
        pushAddress(0x00148D);
        SUB_0014DB();
        if (poppedEntry.value != 0x00148D) return;
        myMapper->writeCPU(0x001F, a);
        pushAddress(0x001492);
        SUB_0014DB();
        if (poppedEntry.value != 0x001492) return;
        myMapper->writeCPU(0x0020, a);
        x = a;
        setLoadFlag(x);
        if (flgZ) {
            goto L_0014DA;
        }
    L_00149A:
        pushAddress(0x00149A);
        SUB_0014E6();
        if (poppedEntry.value != 0x00149A) return;
        x = a;
        setLoadFlag(x);
    } while (flgZ);
    opAND(0x7F);
    myMapper->writeCPU(0x2006, a);
    pushAddress(0x0014A5);
    SUB_0014E6();
    if (poppedEntry.value != 0x0014A5) return;
    myMapper->writeCPU(0x2006, a);
    pushAddress(0x0014AB);
    SUB_0014E6();
    if (poppedEntry.value != 0x0014AB) return;
    myMapper->writeCPU(0x0012, a);
    a = x;
    opAND(0x80);
    opLSR_A(5);
    opORA(myMapper->readCPU(0x0000));
    myMapper->writeCPU(0x2000, a);
    a = x;
    opAND(0x40);
    if (!flgZ) {
        goto L_0014CE;
    }
    do {
        pushAddress(0x0014C2);
        SUB_0014E6();
        if (poppedEntry.value != 0x0014C2) return;
        myMapper->writeCPU(0x2007, a);
        opDEC(0x0012, 1);
    } while (!flgZ);
    if (flgZ) {
        goto L_00149A;
    }
L_0014CE:
    pushAddress(0x0014CE);
    SUB_0014E6();
    if (poppedEntry.value != 0x0014CE) return;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEC(0x0012, 1);
    } while (!flgZ);
    if (flgZ) {
        goto L_00149A;
    }
L_0014DA:
    popAddress();
}

void game::SUB_0014DB() {
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y);
    opINC(0x001D, 1);
    if (!flgZ) {
        goto L_0014E5;
    }
    opINC(0x001E, 1);
L_0014E5:
    popAddress();
}

void game::SUB_0014E6() {
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y);
    opINC(0x001F, 1);
    if (!flgZ) {
        goto L_0014F0;
    }
    opINC(0x0020, 1);
L_0014F0:
    popAddress();
}

void game::SUB_0014F1() {
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0055));
    a = 0x00;
    opASL_M(0x0012, 4);
    opROL_A(1);
    opASL_M(0x0012, 1);
    opROL_A(1);
    opORA(0x20);
    myMapper->writeCPU(0x2006, a);
    myMapper->writeCPU(0x0013, a);
    a = myMapper->readCPU(0x0012);
    opORA(myMapper->readCPU(0x0054));
    myMapper->writeCPU(0x2006, a);
    popAddress();
}

void game::SUB_001512() {
    a = myMapper->readCPU(0x0055);
    opAND(0xFC);
    opASL_A(1);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0054);
    opLSR_A(2);
    opORA(myMapper->readCPU(0x0012));
    opORA(0xC0);
    opPHA();
    a = myMapper->readCPU(0x0055);
    opAND(0x02);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x0054);
    opAND(0x02);
    opLSR_A(1);
    opORA(myMapper->readCPU(0x0012));
    y = a;
    opPLA();
    popAddress();
}

void game::SUB_001532() {
    myMapper->writeCPU(0x2006, 0x23);
    pushAddress(0x001537);
    SUB_001512();
    if (poppedEntry.value != 0x001537) return;
    myMapper->writeCPU(0x2006, a);
    a = myMapper->readCPU(0x2007);
    a = myMapper->readCPU(0x2007);
    opAND(myMapper->readCPU(0xD55A + y));
    opORA(myMapper->readCPU(0xD55E + y));
    opPHA();
    myMapper->writeCPU(0x2006, 0x23);
    pushAddress(0x00154F);
    SUB_001512();
    if (poppedEntry.value != 0x00154F) return;
    myMapper->writeCPU(0x2006, a);
    opPLA();
    myMapper->writeCPU(0x2007, a);
    popAddress();
}

void game::SUB_001562() {
    pushAddress(0x001562);
    SUB_000CC1();
    if (poppedEntry.value != 0x001562) return;
    SUB_000172();
    return;
}

void game::SUB_001568() {
    a = 0xC0;
    y = 0x23;
    pushAddress(0x00156C);
    SUB_001589();
    if (poppedEntry.value != 0x00156C) return;
    a = 0xC0;
    y = 0x27;
    pushAddress(0x001573);
    SUB_001589();
    if (poppedEntry.value != 0x001573) return;
    y = 0x23;
    a = 0x60;
    pushAddress(0x00157A);
    SUB_0015AE();
    if (poppedEntry.value != 0x00157A) return;
    y = 0x27;
    a = 0x60;
    pushAddress(0x001581);
    SUB_0015AE();
    if (poppedEntry.value != 0x001581) return;
    opINC(0x00C8, 1);
    SUB_0013D7();
    return;
}

void game::SUB_001589() {
    myMapper->writeCPU(0x2006, y);
    myMapper->writeCPU(0x2006, a);
    x = 0x00;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xDCA4 + x));
        opINX(1);
    } while (x != 0x08);
    a = 0x00;
    x = 0x28;
    pushAddress(0x0015A0);
    SUB_0015A7();
    if (poppedEntry.value != 0x0015A0) return;
    a = 0xAA;
    x = 0x10;
    SUB_0015A7();
    return;
}

void game::SUB_0015A7() {
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0015AE() {
    myMapper->writeCPU(0x2006, y);
    myMapper->writeCPU(0x2006, a);
    x = 0x20;
    a = 0x58;
    pushAddress(0x0015B8);
    SUB_0015BF();
    if (poppedEntry.value != 0x0015B8) return;
    x = 0x40;
    a = 0x5C;
    SUB_0015BF();
    return;
}

void game::SUB_0015BF() {
    myMapper->writeCPU(0x0012, a);
    do {
        a = x;
        opAND(0x03);
        opEOR(0x03);
        opORA(myMapper->readCPU(0x0012));
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0015CF() {
    x = 0x00;
    do {
        pushAddress(0x0015D1);
        SUB_001647();
        if (poppedEntry.value != 0x0015D1) return;
        pushAddress(0x0015D4);
        SUB_0015E7();
        if (poppedEntry.value != 0x0015D4) return;
        a = myMapper->readCPU(0x0051);
        opORA(0x04);
        myMapper->writeCPU(0x0051, a);
        pushAddress(0x0015DD);
        SUB_0015E7();
        if (poppedEntry.value != 0x0015DD) return;
        opINX(2);
    } while (x != 0x80);
    popAddress();
}

void game::SUB_0015E7() {
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0051));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0050));
    a = myMapper->readCPU(0x2007);
    if (myMapper->readCPU(0x2007) != 0x24) {
        goto L_001602;
    }
    a = x;
    opAND(0x03);
    y = a;
    SUB_001631();
    return;
L_001602:
    popAddress();
}

void game::SUB_001603() {
    if (myMapper->readCPU(0x004C) == 0) {
        goto L_001630;
    }
    opDEC(0x004C, 1);
    a = myMapper->readCPU(0x004F);
    flgC = false;
    opADC(0x02);
    opAND(0x3F);
    myMapper->writeCPU(0x004F, a);
    x = a;
    pushAddress(0x001613);
    SUB_001647();
    if (poppedEntry.value != 0x001613) return;
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0051));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0050));
    a = myMapper->readCPU(0x2007);
    a = myMapper->readCPU(0x2007);
    y = 0x03;
    do {
        if (a == myMapper->readCPU(0xD642 + y)) {
            SUB_001631();
            return;
        }
        opDEY(1);
    } while (!flgN);
L_001630:
    popAddress();
}

void game::SUB_001631() {
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0051));
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0050));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0xD643 + y));
    popAddress();
}

void game::SUB_001647() {
    myMapper->writeCPU(0x0050, myMapper->readCPU(0xD652 + x));
    myMapper->writeCPU(0x0051, myMapper->readCPU(0xD653 + x));
    popAddress();
}

void game::SUB_0016D2() {
    a = 0x00;
    SUB_0016D4();
    return;
}

void game::SUB_0016D4() {
    myMapper->writeCPU(0x0043, a);
    a = myMapper->readCPU(0x003A);
    setLoadFlag(a);
    if (flgZ) {
        goto L_0016DB;
    }
    do {
        do {
            popAddress();
            return;
        L_0016DB:
            x = myMapper->readCPU(0x003E);
        } while (x >= 0x02);
        a = myMapper->readCPU((0x0041 + x) & 0x00ff);
        setLoadFlag(a);
    } while (flgN);
    y = 0x64;
    pushAddress(0x0016E7);
    SUB_001772();
    if (poppedEntry.value != 0x0016E7) return;
    flgC = false;
    opADC(myMapper->readCPU(0x0048));
    myMapper->writeCPU(0x0045, a);
    y = 0x0A;
    pushAddress(0x0016F1);
    SUB_001772();
    if (poppedEntry.value != 0x0016F1) return;
    myMapper->writeCPU(0x0044, a);
    x = myMapper->readCPU(0x003F);
    myMapper->writeCPU(0x0021, myMapper->readCPU(0xD76F + x));
    myMapper->writeCPU(0x0022, 0x06);
    a = myMapper->readCPU(0x003E);
    opASL_A(2);
    opORA(myMapper->readCPU(0x003E));
    x = a;
    flgC = false;
    a = myMapper->readCPU((0x0003 + x) & 0x00ff);
    opADC(myMapper->readCPU(0x0043));
    pushAddress(0x00170D);
    SUB_001785();
    if (poppedEntry.value != 0x00170D) return;
    myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0004 + x) & 0x00ff);
    opADC(myMapper->readCPU(0x0044));
    pushAddress(0x001716);
    SUB_001785();
    if (poppedEntry.value != 0x001716) return;
    myMapper->writeCPU((0x0004 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0005 + x) & 0x00ff);
    opADC(myMapper->readCPU(0x0045));
    pushAddress(0x00171F);
    SUB_001785();
    if (poppedEntry.value != 0x00171F) return;
    myMapper->writeCPU((0x0005 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0006 + x) & 0x00ff);
    opADC(myMapper->readCPU(0x0047));
    pushAddress(0x001728);
    SUB_001785();
    if (poppedEntry.value != 0x001728) return;
    myMapper->writeCPU((0x0006 + x) & 0x00ff, a);
    a = myMapper->readCPU((0x0007 + x) & 0x00ff);
    opADC(0x00);
    pushAddress(0x001731);
    SUB_001785();
    if (poppedEntry.value != 0x001731) return;
    myMapper->writeCPU((0x0007 + x) & 0x00ff, a);
    opINX(4);
    y = 0x04;
    do {
        opCMP(myMapper->readCPU((0x0003 + x) & 0x00ff), myMapper->readCPU(myMapper->readCPU(0x0021) + (myMapper->readCPU((0x0021 + 1) & 0x00ff) << 8) + y));
        if (!flgC) {
            goto L_00175B;
        }
        if (!flgZ) {
            goto L_001748;
        }
        opDEX(1);
        opDEY(1);
    } while (!flgN);
L_001748:
    y = 0x00;
    a = myMapper->readCPU(0x003E);
    opASL_A(2);
    opORA(myMapper->readCPU(0x003E));
    x = a;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x0021) + (myMapper->readCPU((0x0021 + 1) & 0x00ff) << 8) + y, myMapper->readCPU((0x0003 + x) & 0x00ff));
        opINX(1);
        opINY(1);
    } while (y != 0x05);
L_00175B:
    y = 0x04;
    do {
        myMapper->writeCPU(0x000D + y, myMapper->readCPU(myMapper->readCPU(0x0021) + (myMapper->readCPU((0x0021 + 1) & 0x00ff) << 8) + y));
        opDEY(1);
    } while (!flgN);
    opINC(0x0046, 1);
    a = myMapper->readCPU(0x0016);
    setLoadFlag(a);
    if (flgZ) {
        goto L_00176E;
    }
    pushAddress(0x00176B);
    SUB_00052F();
    if (poppedEntry.value != 0x00176B) return;
L_00176E:
    popAddress();
}

void game::SUB_001772() {
    myMapper->writeCPU(0x0012, y);
    x = 0xFF;
    a = myMapper->readCPU(0x0043);
    do {
        flgC = true;
        opSBC(myMapper->readCPU(0x0012));
        opINX(1);
    } while (flgC);
    flgC = false;
    opADC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0043, a);
    a = x;
    popAddress();
}

void game::SUB_001785() {
    opCMP(a, 0x0A);
    if (flgC) {
        goto L_00178A;
    }
    popAddress();
    return;
L_00178A:
    flgC = true;
    opSBC(0x0A);
    popAddress();
}

void game::SUB_00178E() {
    y = myMapper->readCPU(0x0046);
    opDEY(1);
    if (!flgZ) {
        if (!flgN) {
            goto L_0017FB;
        }
        popAddress();
        return;
    }
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x43);
    myMapper->writeCPU(0x2007, 0x8E);
    x = 0x04;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU((0x0003 + x) & 0x00ff));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2007, 0x00);
    a = 0x24;
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    x = 0x8C;
    myMapper->writeCPU(0x2007, x);
    opINX(1);
    myMapper->writeCPU(0x2007, x);
    x = 0x04;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU((0x000D + x) & 0x00ff));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2007, 0x00);
    a = 0x24;
    myMapper->writeCPU(0x2007, a);
    myMapper->writeCPU(0x2007, a);
    if (myMapper->readCPU(0x0016) != 0) {
        SUB_00184A();
        return;
    }
    if (myMapper->readCPU(0x0040) == 0) {
        goto L_0017F8;
    }
    myMapper->writeCPU(0x2007, 0x8F);
    x = 0x04;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU((0x0008 + x) & 0x00ff));
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x2007, 0x00);
L_0017F8:
    opDEC(0x0046, 1);
    popAddress();
    return;
L_0017FB:
    opDEC(0x0046, 1);
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x62);
    a = myMapper->readCPU(0x0041);
    setLoadFlag(a);
    pushAddress(0x001809);
    SUB_00181C();
    if (poppedEntry.value != 0x001809) return;
    if (myMapper->readCPU(0x0040) == 0) {
        SUB_001830();
        return;
    }
    myMapper->writeCPU(0x2006, 0x20);
    myMapper->writeCPU(0x2006, 0x75);
    a = myMapper->readCPU(0x0042);
    setLoadFlag(a);
    SUB_00181C();
    return;
}

void game::SUB_00181C() {
    if (flgN) {
        SUB_001831();
        return;
    }
    SUB_00181E();
    return;
}

void game::SUB_00181E() {
    myMapper->writeCPU(0x0050, a);
    x = 0x06;
    do {
        a = 0x24;
        if (x >= myMapper->readCPU(0x0050)) {
            goto L_00182A;
        }
        a = 0x2A;
    L_00182A:
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgN);
    SUB_001830();
    return;
}

void game::SUB_001830() {
    popAddress();
}

void game::SUB_001831() {
    a = myMapper->readCPU(0x0040);
    setLoadFlag(a);
    if (flgZ) {
        SUB_00181E();
        return;
    }
    x = 0x08;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xD841 + x));
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_00184A() {
    y = 0x04;
    do {
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xD862 + y));
        opDEY(1);
    } while (!flgN);
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x004A));
    myMapper->writeCPU(0x2007, myMapper->readCPU(0x0049));
    opDEC(0x0046, 1);
    popAddress();
}

void game::SUB_001867() {
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0013, x);
    myMapper->writeCPU(0x0014, y);
    x = 0x01;
    do {
        if (myMapper->readCPU(0x061A + x) & 0x80) {
            goto L_001882;
        }
        opDEX(1);
    } while (!flgN);
    x = 0x01;
    if (myMapper->readCPU(0x0619) < myMapper->readCPU(0x0618)) {
        goto L_001882;
    }
    opDEX(1);
L_001882:
    myMapper->writeCPU(0x0618 + x, 0x64);
    a = myMapper->readCPU(0x0012);
    myMapper->writeCPU(0x061A + x, a);
    y = a;
    a = x;
    opASL_A(3);
    x = a;
    myMapper->writeCPU(0x02F1 + x, myMapper->readCPU(0xD8C7 + y));
    myMapper->writeCPU(0x02F5 + x, myMapper->readCPU(0xD8CD + y));
    y = myMapper->readCPU(0x0013);
    a = myMapper->readCPU(0x009A + y);
    flgC = true;
    opSBC(0x08);
    myMapper->writeCPU(0x02F0 + x, a);
    myMapper->writeCPU(0x02F4 + x, a);
    a = myMapper->readCPU(0x0091 + y);
    myMapper->writeCPU(0x02F3 + x, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x02F7 + x, a);
    a = myMapper->readCPU(0x003E);
    myMapper->writeCPU(0x02F2 + x, a);
    myMapper->writeCPU(0x02F6 + x, a);
    y = myMapper->readCPU(0x0014);
    x = myMapper->readCPU(0x0013);
    a = myMapper->readCPU(0x0012);
    popAddress();
}

void game::SUB_0018D3() {
    x = 0x01;
    do {
        if (myMapper->readCPU(0x061A + x) & 0x80) {
            goto L_0018F1;
        }
        opDEC(0x0618 + x, 1);
        if (!flgZ) {
            goto L_0018F1;
        }
        myMapper->writeCPU(0x061A + x, 0xFF);
        a = x;
        opASL_A(3);
        y = a;
        a = 0xF0;
        myMapper->writeCPU(0x02F0 + y, a);
        myMapper->writeCPU(0x02F4 + y, a);
    L_0018F1:
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0018F5() {
    x = 0x01;
    do {
        myMapper->writeCPU(0x0618 + x, 0x00);
        myMapper->writeCPU(0x061A + x, 0xFF);
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_001905() {
    pushAddress(0x001905);
    SUB_00123C();
    if (poppedEntry.value != 0x001905) return;
    pushAddress(0x001908);
    SUB_000100();
    if (poppedEntry.value != 0x001908) return;
    pushAddress(0x00190B);
    SUB_00345B();
    if (poppedEntry.value != 0x00190B) return;
    pushAddress(0x00190E);
    SUB_0000F0();
    if (poppedEntry.value != 0x00190E) return;
    myMapper->writeCPU(0x001D, 0x22);
    myMapper->writeCPU(0x001E, 0xD9);
    pushAddress(0x001919);
    SUB_00148D();
    if (poppedEntry.value != 0x001919) return;
    pushAddress(0x00191C);
    SUB_0000FA();
    if (poppedEntry.value != 0x00191C) return;
    SUB_00010B();
    return;
}

void game::SUB_001AB7() {
    do {
        pushAddress(0x001AB7);
        SUB_0000FA();
        if (poppedEntry.value != 0x001AB7) return;
        pushAddress(0x001ABA);
        SUB_001905();
        if (poppedEntry.value != 0x001ABA) return;
        myMapper->writeCPU(0x0019, 0x00);
    L_001AC1:
        pushAddress(0x001AC1);
        SUB_00345B();
        if (poppedEntry.value != 0x001AC1) return;
        if (myMapper->readCPU(0x0019) != 0) {
            pushAddress(0x001AC8);
            SUB_001AFE();
            if (poppedEntry.value != 0x001AC8) return;
            pushAddress(0x001ACB);
            SUB_00275E();
            if (poppedEntry.value != 0x001ACB) return;
            x = a;
            opAND(0x10);
            if (flgZ) {
                a = x;
                opAND(0x20);
                if (flgZ) {
                    goto L_001AE3;
                }
                myMapper->writeCPU(0x0019, 0x00);
                x = myMapper->readCPU(0x003F);
                myMapper->writeCPU(0x003F, myMapper->readCPU(0xDAFB + x));
            L_001AE3:
                goto L_001AC1;
            }
            popAddress();
            return;
        }
        opINC(0x003A, 1);
        opINC(0x0040, 1);
        a = 0x00;
        myMapper->writeCPU(0x4015, a);
        myMapper->writeCPU(0x0016, a);
        pushAddress(0x001AF2);
        SUB_0031E8();
        if (poppedEntry.value != 0x001AF2) return;
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x003A, a);
    } while (flgZ);
    opORA(myMapper->readCPU(myMapper->readCPU((0x0002 + x) & 0x00ff) + (myMapper->readCPU((0x0002 + x + 1) & 0x00ff) << 8)));
    pushAddress(0x001AFD);
    popAddress();
}

void game::SUB_001AFE() {
    a = myMapper->readCPU(0x003F);
    //NOP
    opLSR_A(1);
    myMapper->writeCPU(0x0016, a);
    a = myMapper->readCPU(0x003F);
    x = a;
    opAND(0x01);
    myMapper->writeCPU(0x0040, a);
    myMapper->writeCPU(0x057B, myMapper->readCPU(0xDB1D + x));
    myMapper->writeCPU(0x0567, 0x2C);
    x = 0x00;
    myMapper->writeCPU(0x055D, x);
    SUB_000E25();
    return;
}

void game::SUB_00239A() {
    myMapper->writeCPU(0x001F, myMapper->readCPU(0xE388 + x));
    a = myMapper->readCPU(0x0019);
    opLSR_A(1);
    if (flgC) {
        myMapper->writeCPU(0x001F, myMapper->readCPU(0xE391 + x));
    }
    myMapper->writeCPU(0x0020, 0x02);
    a = myMapper->readCPU((0x0088 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgN) {
        goto L_0023C5;
    }
    opCMP(a, 0xFF);
    if (!flgZ) {
    }
    else {
        do {
            y = 0x14;
            do {
                myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, 0xF0);
                opDEY(4);
            } while (!flgN);
            popAddress();
            return;
        L_0023C5:
            opCMP(x, 0x08);
            if (!flgZ) {
                a = myMapper->readCPU((0x007F + x) & 0x00ff);
                opASL_A(2);
                opADC(myMapper->readCPU(0x0436 + x));
                opCMP(x, 0x02);
                if (flgC) {
                    goto L_0023FE;
                }
                y = myMapper->readCPU((0x0088 + x) & 0x00ff);
                opADC(myMapper->readCPU(0xE342 + y));
                y = a;
                myMapper->writeCPU(0x001D, myMapper->readCPU(0xE242 + y));
                myMapper->writeCPU(0x001E, myMapper->readCPU(0xE28E + y));
                if (myMapper->readCPU((0x00BD + x) & 0x00ff) == 0) {
                    goto L_00241F;
                }
                y = myMapper->readCPU((0x0088 + x) & 0x00ff);
                a = myMapper->readCPU(0xE345 + y);
                opADC(myMapper->readCPU(0x0436 + x));
                y = a;
                myMapper->writeCPU(0x001D, myMapper->readCPU(0xE2DA + y));
                myMapper->writeCPU(0x001E, myMapper->readCPU(0xE2E2 + y));
                goto L_00241F;
            L_0023FE:
                y = myMapper->readCPU((0x0088 + x) & 0x00ff);
                flgC = false;
                opADC(myMapper->readCPU(0xE348 + y));
                y = a;
                myMapper->writeCPU(0x001D, myMapper->readCPU(0xE2EA + y));
                a = myMapper->readCPU(0xE316 + y);
                setLoadFlag(a);
                myMapper->writeCPU(0x001E, a);
                if (!flgZ) {
                    goto L_00241F;
                }
            }
            y = myMapper->readCPU((0x007F + x) & 0x00ff);
            setLoadFlag(y);
        } while (flgN);
        myMapper->writeCPU(0x001D, myMapper->readCPU(0xE37A + y));
        myMapper->writeCPU(0x001E, myMapper->readCPU(0xE381 + y));
    L_00241F:
        myMapper->writeCPU(0x0015, myMapper->readCPU((0x0091 + x) & 0x00ff));
        myMapper->writeCPU(0x0012, myMapper->readCPU((0x009A + x) & 0x00ff));
        a = x;
        setLoadFlag(a);
        if (!flgZ) {
            if (x != 0x01) {
                goto L_002432;
            }
            a = 0x01;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_00243A;
            }
        L_002432:
            a = myMapper->readCPU(0x0451 + x);
            flgC = false;
            opADC(0x02);
            opAND(0x03);
        }
    L_00243A:
        if (myMapper->readCPU(0x0448 + x) != 0) {
            opORA(0x40);
        }
        if (myMapper->readCPU((0x0088 + x) & 0x00ff) == 0x02) {
            if (myMapper->readCPU((0x007F + x) & 0x00ff) != 0x05) {
                goto L_00244F;
            }
            opEOR(0x40);
        }
    L_00244F:
        if (myMapper->readCPU((0x009A + x) & 0x00ff) < 0xC9) {
            if (x != 0x09) {
                goto L_00245B;
            }
        }
        opORA(0x20);
    L_00245B:
        myMapper->writeCPU(0x0014, a);
        myMapper->writeCPU(0x0021, 0x39);
        myMapper->writeCPU(0x0022, 0xE0);
        if (myMapper->readCPU(0x0448 + x) != 0) {
            myMapper->writeCPU(0x0021, 0x6F);
            myMapper->writeCPU(0x0022, 0xE0);
        }
        y = 0x00;
        a = myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y);
        opINC(0x001D, 1);
        if (flgZ) {
            opINC(0x001E, 1);
        }
        opASL_A(1);
        myMapper->writeCPU(0x0013, a);
        opASL_A(1);
        opADC(myMapper->readCPU(0x0013));
        opADC(myMapper->readCPU(0x0021));
        myMapper->writeCPU(0x0021, a);
        if (flgC) {
            opINC(0x0022, 1);
        }
        a = x;
        opPHA();
        x = 0x05;
        y = 0x00;
        do {
            a = myMapper->readCPU(0x0012);
            flgC = false;
            opADC(myMapper->readCPU(0xE033 + x));
            myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, a);
            myMapper->writeCPU(0x0012, a);
            opINY(1);
            myMapper->writeCPU(0x0013, y);
            y = 0x00;
            a = myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y);
            opINC(0x001D, 1);
            if (flgZ) {
                opINC(0x001E, 1);
            }
            y = myMapper->readCPU(0x0013);
            myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x0014));
            opINY(1);
            myMapper->writeCPU(0x0013, y);
            y = 0x00;
            a = myMapper->readCPU(0x0015);
            flgC = false;
            opADC(myMapper->readCPU(myMapper->readCPU(0x0021) + (myMapper->readCPU((0x0021 + 1) & 0x00ff) << 8) + y));
            opINC(0x0021, 1);
            if (!flgZ) {
                goto L_0024C0;
            }
            opINC(0x0022, 1);
        L_0024C0:
            y = myMapper->readCPU(0x0013);
            myMapper->writeCPU(myMapper->readCPU(0x001F) + (myMapper->readCPU((0x001F + 1) & 0x00ff) << 8) + y, a);
            opINY(1);
            opDEX(1);
        } while (!flgN);
        opPLA();
        x = a;
        popAddress();
        return;
    }
    a = x;
    opPHA();
    y = myMapper->readCPU(0x001F);
    a = myMapper->readCPU((0x009A + x) & 0x00ff);
    myMapper->writeCPU(0x0200 + y, a);
    myMapper->writeCPU(0x0204 + y, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0208 + y, a);
    myMapper->writeCPU(0x020C + y, a);
    a = 0xF0;
    myMapper->writeCPU(0x0210 + y, a);
    myMapper->writeCPU(0x0214 + y, a);
    a = myMapper->readCPU((0x0091 + x) & 0x00ff);
    myMapper->writeCPU(0x0203 + y, a);
    myMapper->writeCPU(0x020B + y, a);
    flgC = false;
    opADC(0x08);
    myMapper->writeCPU(0x0207 + y, a);
    myMapper->writeCPU(0x020F + y, a);
    opCMP(myMapper->readCPU((0x009A + x) & 0x00ff), 0xD0);
    a = 0x03;
    if (flgC) {
        a = 0x23;
    }
    myMapper->writeCPU(0x0202 + y, a);
    if (myMapper->readCPU((0x007F + x) & 0x00ff) == 0) {
        a = myMapper->readCPU(0x0202 + y);
        myMapper->writeCPU(0x0206 + y, a);
        myMapper->writeCPU(0x020A + y, a);
        myMapper->writeCPU(0x020E + y, a);
        myMapper->writeCPU(0x0201 + y, 0xDA);
        myMapper->writeCPU(0x0205 + y, 0xDB);
        myMapper->writeCPU(0x0209 + y, 0xDC);
        myMapper->writeCPU(0x020D + y, 0xDD);
        x = myMapper->readCPU(0x001F);
        a = myMapper->readCPU(0x0019);
        opAND(0x20);
        if (!flgZ) {
            a = myMapper->readCPU(0x0019);
            opAND(0x40);
            if (flgZ) {
                opINC(0x0200 + x, 1);
                opINC(0x0204 + x, 1);
                if (!flgZ) {
                    goto L_002546;
                }
            }
            opINC(0x0203 + x, 1);
            opINC(0x020B + x, 1);
        }
    L_002546:
        opPLA();
        x = a;
        popAddress();
        return;
    }
    a = myMapper->readCPU(0x0202 + y);
    opORA(0x40);
    myMapper->writeCPU(0x0206 + y, a);
    opORA(0x80);
    myMapper->writeCPU(0x020E + y, a);
    opAND(0xBF);
    myMapper->writeCPU(0x020A + y, a);
    a = 0xDE;
    myMapper->writeCPU(0x0201 + y, a);
    myMapper->writeCPU(0x0205 + y, a);
    myMapper->writeCPU(0x0209 + y, a);
    myMapper->writeCPU(0x020D + y, a);
    opDEC(0x045A + x, 1);
    if (!flgN) {
        goto L_00257A;
    }
    myMapper->writeCPU((0x0088 + x) & 0x00ff, 0xFF);
    myMapper->writeCPU((0x009A + x) & 0x00ff, 0xF0);
    a = 0x04;
    myMapper->writeCPU(0x00F1, a);
L_00257A:
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_00257D() {
    x = myMapper->readCPU(0x00BB);
    setLoadFlag(x);
    if (!flgN) {
        myMapper->writeCPU(0x001D, myMapper->readCPU(0xE5BB + x));
        myMapper->writeCPU(0x001E, myMapper->readCPU(0xE5C0 + x));
        y = 0x00;
        x = 0x00;
    L_00258F:
        a = myMapper->readCPU(myMapper->readCPU(0x001D) + (myMapper->readCPU((0x001D + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x02E0 + x, a);
        opINY(1);
        opINX(1);
        if (a == 0xF0) {
            opINX(3);
        }
        if (x != 0x10) {
            goto L_00258F;
        }
        y = 0x0F;
        do {
            a = myMapper->readCPU(0x02E0 + y);
            flgC = false;
            opADC(myMapper->readCPU(0x00BC));
            myMapper->writeCPU(0x02E0 + y, a);
            opDEY(4);
        } while (!flgN);
        a = myMapper->readCPU(0x0019);
        opAND(0x03);
        if (!flgZ) {
            goto L_0025BA;
        }
        opDEC(0x00BB, 1);
    }
L_0025BA:
    popAddress();
}

void game::SUB_002687() {
    pushAddress(0x002687);
    SUB_002E1B();
    if (poppedEntry.value != 0x002687) return;
    x = 0x07;
    do {
        a = myMapper->readCPU((0x0088 + x) & 0x00ff);
        setLoadFlag(a);
        if (flgN) {
            if (a == 0xFF) {
                goto L_0026D8;
            }
            pushAddress(0x002694);
            SUB_002CB0();
            if (poppedEntry.value != 0x002694) return;
        }
        else {
            if (x < 0x02) {
                goto L_0026AE;
            }
            if (a == 0x01) {
                if (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x02) {
                    goto L_0026AE;
                }
                a = myMapper->readCPU(0x00F1);
                opORA(0x20);
                myMapper->writeCPU(0x00F1, a);
            }
        L_0026AE:
            opDEC(0x043F + x, 1);
            if (flgZ) {
                myMapper->writeCPU(0x043F + x, 0x03);
                if (x < 0x02) {
                    opDEC((0x00BF + x) & 0x00ff, 1);
                    if (!flgZ) {
                        goto L_0026C4;
                    }
                    myMapper->writeCPU((0x00BD + x) & 0x00ff, 0x00);
                }
            L_0026C4:
                pushAddress(0x0026C4);
                SUB_002A0E();
                if (poppedEntry.value != 0x0026C4) return;
                myMapper->writeCPU(0x003E, x);
                pushAddress(0x0026C9);
                SUB_002BBA();
                if (poppedEntry.value != 0x0026C9) return;
                pushAddress(0x0026CC);
                SUB_00278C();
                if (poppedEntry.value != 0x0026CC) return;
            }
            pushAddress(0x0026CF);
            SUB_002A4E();
            if (poppedEntry.value != 0x0026CF) return;
            pushAddress(0x0026D2);
            SUB_002D1E();
            if (poppedEntry.value != 0x0026D2) return;
            pushAddress(0x0026D5);
            SUB_002979();
            if (poppedEntry.value != 0x0026D5) return;
        }
    L_0026D8:
        pushAddress(0x0026D8);
        SUB_00239A();
        if (poppedEntry.value != 0x0026D8) return;
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_0026DF() {
    if (x >= 0x02) {
        goto L_0026FB;
    }
    a = myMapper->readCPU(0x0019);
    opAND(0x0F);
    if (flgZ) {
        pushAddress(0x0026E9);
        SUB_0031A9();
        if (poppedEntry.value != 0x0026E9) return;
        myMapper->writeCPU((0x0031 + x) & 0x00ff, a);
    }
    if (myMapper->readCPU(0x003A) != 0) {
        goto L_0026FB;
    }
    pushAddress(0x0026F2);
    SUB_002760();
    if (poppedEntry.value != 0x0026F2) return;
    myMapper->writeCPU((0x0031 + x) & 0x00ff, myMapper->readCPU(0x061C + x));
    do {
        popAddress();
        return;
    L_0026FB:
        if (myMapper->readCPU((0x009A + x) & 0x00ff) < 0xA0) {
            goto L_002708;
        }
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opORA(0x40);
        myMapper->writeCPU((0x0031 + x) & 0x00ff, a);
        popAddress();
        return;
    L_002708:
        opDEC(0x045A + x, 1);
    } while (!flgZ);
    pushAddress(0x00270D);
    SUB_0031A9();
    if (poppedEntry.value != 0x00270D) return;
    y = myMapper->readCPU(0x0451 + x);
    opAND(myMapper->readCPU(0xE758 + y));
    opADC(myMapper->readCPU(0xE75B + y));
    myMapper->writeCPU(0x045A + x, a);
    myMapper->writeCPU(0x0012, x);
    a = myMapper->readCPU(0x0019);
    opROL_A(2);
    opEOR(myMapper->readCPU(0x0012));
    opAND(0x01);
    y = a;
    if (!(myMapper->readCPU(0x0088 + y) & 0x80)) {
        if (myMapper->readCPU(0x00BD + y) != 0) {
            goto L_00273F;
        }
        myMapper->writeCPU((0x0031 + x) & 0x00ff, 0x00);
        a = myMapper->readCPU(0x009A + y);
        flgC = true;
        opSBC(0x04);
        if (a >= myMapper->readCPU((0x009A + x) & 0x00ff)) {
            goto L_002743;
        }
    }
L_00273F:
    myMapper->writeCPU((0x0031 + x) & 0x00ff, 0x40);
L_002743:
    if (myMapper->readCPU((0x0091 + x) & 0x00ff) >= myMapper->readCPU(0x0091 + y)) {
        goto L_002751;
    }
    a = myMapper->readCPU((0x0031 + x) & 0x00ff);
    opORA(0x01);
    myMapper->writeCPU((0x0031 + x) & 0x00ff, a);
    popAddress();
    return;
L_002751:
    a = myMapper->readCPU((0x0031 + x) & 0x00ff);
    opORA(0x02);
    myMapper->writeCPU((0x0031 + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_00275E() {
    x = 0x00;
    SUB_002760();
    return;
}

void game::SUB_002760() {
    myMapper->writeCPU(0x4016, 0x01);
    myMapper->writeCPU(0x4016, 0x00);
    y = 0x07;
    do {
        a = myMapper->readCPU(0x4016 + x);
        myMapper->writeCPU(0x0012, a);
        opLSR_A(1);
        opORA(myMapper->readCPU(0x0012));
        opLSR_A(1);
        opROL_M(0x061C + x, 1);
        opDEY(1);
    } while (!flgN);
    y = myMapper->readCPU(0x061E + x);
    myMapper->writeCPU(0x061E + x, myMapper->readCPU(0x061C + x));
    a = y;
    opEOR(myMapper->readCPU(0x061C + x));
    opAND(myMapper->readCPU(0x061C + x));
    popAddress();
}

void game::SUB_00278C() {
    a = myMapper->readCPU((0x0088 + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_002799;
    }
    do {
        a = 0x00;
        myMapper->writeCPU(0x0424 + x, a);
        myMapper->writeCPU(0x042D + x, a);
        popAddress();
        return;
    L_002799:
        if (a == 0x02) {
            SUB_0027DE();
            return;
        }
        if (x < 0x02) {
            SUB_0027DE();
            return;
        }
    } while (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x02);
    SUB_0027A7();
    return;
}

void game::SUB_0027A7() {
    myMapper->writeCPU(0x0012, myMapper->readCPU(0x0424 + x));
    myMapper->writeCPU(0x0013, myMapper->readCPU(0x042D + x));
    pushAddress(0x0027B1);
    SUB_00319C();
    if (poppedEntry.value != 0x0027B1) return;
    a = myMapper->readCPU(0x0463 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0463 + x, a);
    myMapper->writeCPU(0x0012, a);
    a = myMapper->readCPU(0x046C + x);
    opADC(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x046C + x, a);
    myMapper->writeCPU(0x0013, a);
    pushAddress(0x0027C9);
    SUB_00319C();
    if (poppedEntry.value != 0x0027C9) return;
    a = myMapper->readCPU(0x0424 + x);
    flgC = true;
    opSBC(myMapper->readCPU(0x0012));
    myMapper->writeCPU(0x0424 + x, a);
    a = myMapper->readCPU(0x042D + x);
    opSBC(myMapper->readCPU(0x0013));
    myMapper->writeCPU(0x042D + x, a);
    popAddress();
}

void game::SUB_0027DE() {
    if (myMapper->readCPU((0x007F + x) & 0x00ff) < 0x06) {
        goto L_0027E5;
    }
    popAddress();
    return;
L_0027E5:
    if (myMapper->readCPU((0x007F + x) & 0x00ff) == 0x04) {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x0448 + x);
            setLoadFlag(a);
            if (flgZ) {
                goto L_002807;
            }
            if (!flgZ) {
                goto L_002803;
            }
        }
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x01);
        if (!flgZ) {
            if (myMapper->readCPU(0x0448 + x) != 0) {
                goto L_002807;
            }
        L_002803:
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x05);
        }
    }
L_002807:
    if (myMapper->readCPU((0x007F + x) & 0x00ff) == 0x02) {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x02);
        if (!flgZ) {
            a = 0x00;
            setLoadFlag(a);
            if (flgZ) {
                goto L_00281F;
            }
        }
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x01);
        if (!flgZ) {
            a = 0x01;
        L_00281F:
            if (a == myMapper->readCPU(0x0448 + x)) {
                goto L_002828;
            }
        }
        myMapper->writeCPU((0x007F + x) & 0x00ff, 0x04);
    }
L_002828:
    if (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x04) {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x0448 + x);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_00284A;
            }
            if (flgZ) {
                goto L_002846;
            }
        }
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x01);
        if (!flgZ) {
            if (myMapper->readCPU(0x0448 + x) == 0) {
                goto L_00284A;
            }
        L_002846:
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x02);
        }
    }
L_00284A:
    if (myMapper->readCPU((0x007F + x) & 0x00ff) == 0x03) {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x03);
        if (!flgZ) {
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x02);
        }
    }
    if (myMapper->readCPU((0x007F + x) & 0x00ff) < 0x04) {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x02);
        if (!flgZ) {
            a = 0x00;
            setLoadFlag(a);
            if (flgZ) {
                goto L_002872;
            }
        }
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x01);
        if (!flgZ) {
            a = 0x01;
        L_002872:
            myMapper->writeCPU(0x0448 + x, a);
        }
    }
    if (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x04) {
        if (myMapper->readCPU(0x0436 + x) != 0x01) {
            goto L_0028AE;
        }
        y = myMapper->readCPU(0x0451 + x);
        if (myMapper->readCPU(0x0448 + x) != 0) {
            a = myMapper->readCPU(0x0424 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0xE61B + y));
            myMapper->writeCPU(0x0424 + x, a);
            a = myMapper->readCPU(0x042D + x);
            opSBC(0x00);
            goto L_0028F7;
        }
        a = myMapper->readCPU(0x0424 + x);
        flgC = false;
        opADC(myMapper->readCPU(0xE61B + y));
        myMapper->writeCPU(0x0424 + x, a);
        a = myMapper->readCPU(0x042D + x);
        opADC(0x00);
        goto L_0028F7;
    }
L_0028AE:
    a = myMapper->readCPU((0x007F + x) & 0x00ff);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x02) {
            goto L_0028FD;
        }
        if (a != 0x03) {
            goto L_002947;
        }
    }
    if (myMapper->readCPU(0x0436 + x) != 0x01) {
        goto L_002947;
    }
    y = myMapper->readCPU(0x0451 + x);
    a = myMapper->readCPU((0x0031 + x) & 0x00ff);
    opAND(0x02);
    if (!flgZ) {
        a = myMapper->readCPU(0x0424 + x);
        flgC = true;
        opSBC(myMapper->readCPU(0xE60F + y));
        myMapper->writeCPU(0x0424 + x, a);
        a = myMapper->readCPU(0x042D + x);
        opSBC(0x00);
    }
    else {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x01);
        if (flgZ) {
            goto L_002947;
        }
        a = myMapper->readCPU(0x0424 + x);
        flgC = false;
        opADC(myMapper->readCPU(0xE60F + y));
        myMapper->writeCPU(0x0424 + x, a);
        a = myMapper->readCPU(0x042D + x);
        opADC(0x00);
    }
L_0028F7:
    myMapper->writeCPU(0x042D + x, a);
    goto L_002947;
L_0028FD:
    if (myMapper->readCPU(0x0436 + x) == 0x01) {
        y = myMapper->readCPU(0x0451 + x);
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x02);
        if (!flgZ) {
            a = myMapper->readCPU(0x0424 + x);
            flgC = true;
            opSBC(myMapper->readCPU(0xE61B + y));
            myMapper->writeCPU(0x0424 + x, a);
            a = myMapper->readCPU(0x042D + x);
            opSBC(0x00);
        }
        else {
            a = myMapper->readCPU((0x0031 + x) & 0x00ff);
            opAND(0x01);
            if (flgZ) {
                goto L_002947;
            }
            a = myMapper->readCPU(0x0424 + x);
            flgC = false;
            opADC(myMapper->readCPU(0xE61B + y));
            myMapper->writeCPU(0x0424 + x, a);
            a = myMapper->readCPU(0x042D + x);
            opADC(0x00);
        }
        myMapper->writeCPU(0x042D + x, a);
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x03);
        if (!flgZ) {
            if (x >= 0x02) {
                goto L_002947;
            }
            a = myMapper->readCPU(0x00F0);
            opORA(0x08);
            myMapper->writeCPU(0x00F0, a);
        }
    }
L_002947:
    if (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x04) {
        if (myMapper->readCPU(0x0448 + x) != 0) {
            goto L_002959;
        }
        a = myMapper->readCPU(0x042D + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_002978;
        }
        if (!flgN) {
            goto L_00295E;
        }
    L_002959:
        if (myMapper->readCPU(0x042D + x) & 0x80) {
        L_00295E:
            if (myMapper->readCPU((0x007F + x) & 0x00ff) != 0x05) {
                goto L_00296C;
            }
            a = myMapper->readCPU(0x0448 + x);
            opEOR(0x01);
            myMapper->writeCPU(0x0448 + x, a);
        L_00296C:
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x03);
            a = 0x00;
            myMapper->writeCPU(0x0424 + x, a);
            myMapper->writeCPU(0x042D + x, a);
        }
    }
L_002978:
    popAddress();
}

void game::SUB_002979() {
    if (myMapper->readCPU(0x00CB) != 0) {
        goto L_0029AC;
    }
    if (myMapper->readCPU((0x00BD + x) & 0x00ff) != 0) {
        a = myMapper->readCPU(0x0488);
        setLoadFlag(a);
        if (!flgZ) {
            flgC = true;
            opSBC(myMapper->readCPU((0x0091 + x) & 0x00ff));
            pushAddress(0x002989);
            SUB_003084();
            if (poppedEntry.value != 0x002989) return;
            if (a < 0x05) {
                goto L_0029AC;
            }
        }
    }
    if (x >= 0x02) {
        a = myMapper->readCPU((0x0088 + x) & 0x00ff);
        if (a != 0x02) {
            goto L_0029E8;
        }
    }
    a = myMapper->readCPU((0x007F + x) & 0x00ff);
    if (a < 0x02) {
        goto L_0029E8;
    }
    if (a >= 0x06) {
        goto L_0029E8;
    }
    a = 0x01;
    myMapper->writeCPU((0x007F + x) & 0x00ff, a);
    myMapper->writeCPU(0x045A + x, a);
    popAddress();
    return;
L_0029AC:
    a = 0x00;
    myMapper->writeCPU(0x0412 + x, a);
    myMapper->writeCPU(0x041B + x, a);
    myMapper->writeCPU(0x0409 + x, a);
    myMapper->writeCPU(0x00CB, a);
    if (x >= 0x02) {
        a = myMapper->readCPU((0x0088 + x) & 0x00ff);
        if (a != 0x02) {
            if (a != 0x01) {
                goto L_0029E8;
            }
            a = myMapper->readCPU((0x007F + x) & 0x00ff);
            if (a < 0x02) {
                myMapper->writeCPU((0x007F + x) & 0x00ff, 0x02);
                myMapper->writeCPU(0x043F + x, myMapper->readCPU(0x00C6));
                a = 0x00;
                myMapper->writeCPU(0x0424 + x, a);
                myMapper->writeCPU(0x042D + x, a);
                myMapper->writeCPU(0x0463 + x, a);
                myMapper->writeCPU(0x046C + x, a);
                a = 0x40;
                myMapper->writeCPU(0x00F1, a);
            }
        L_0029E8:
            popAddress();
            return;
        }
        myMapper->writeCPU((0x007F + x) & 0x00ff, 0x00);
        a = 0x01;
        myMapper->writeCPU(0x045A + x, a);
        popAddress();
        return;
    }
    a = myMapper->readCPU((0x007F + x) & 0x00ff);
    if (a == 0x01) {
        if (a >= 0x06) {
            goto L_002A0D;
        }
        a = myMapper->readCPU(0x0424 + x);
        opORA(myMapper->readCPU(0x042D + x));
        if (!flgZ) {
            goto L_002A09;
        }
        a = 0x03;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_002A0B;
        }
    L_002A09:
        a = 0x02;
    L_002A0B:
        myMapper->writeCPU((0x007F + x) & 0x00ff, a);
    }
L_002A0D:
    popAddress();
}

void game::SUB_002A0E() {
    if (x >= 0x02) {
        goto L_002A22;
    }
    if (myMapper->readCPU((0x00BD + x) & 0x00ff) != 0) {
        goto L_002A3A;
    }
    a = myMapper->readCPU((0x007F + x) & 0x00ff);
    if (a == 0x01) {
        goto L_002A34;
    }
    opCMP(a, 0x03);
    if (!flgZ) {
        goto L_002A3A;
    }
    if (flgZ) {
        goto L_002A34;
    }
L_002A22:
    a = myMapper->readCPU((0x007F + x) & 0x00ff);
    if (a != 0x01) {
        if (a < 0x03) {
            goto L_002A3A;
        }
        a = myMapper->readCPU(0x0019);
        opAND(0x03);
        if (!flgZ) {
            goto L_002A3D;
        }
        if (flgZ) {
            goto L_002A3A;
        }
    }
L_002A34:
    a = myMapper->readCPU(0x0019);
    opAND(0x07);
    if (flgZ) {
    L_002A3A:
        opINC(0x0436 + x, 1);
    }
L_002A3D:
    a = myMapper->readCPU(0x0436 + x);
    opAND(0x03);
    myMapper->writeCPU(0x0436 + x, a);
    if (flgZ) {
        if (myMapper->readCPU((0x007F + x) & 0x00ff) != 0) {
            goto L_002A4D;
        }
        opINC((0x007F + x) & 0x00ff, 1);
    }
L_002A4D:
    popAddress();
}

void game::SUB_002A4E() {
    if (myMapper->readCPU(0x0475 + x) == 0) {
        goto L_002A56;
    }
    opDEC(0x0475 + x, 1);
L_002A56:
    if (x < 0x02) {
        if (myMapper->readCPU((0x00C1 + x) & 0x00ff) == 0) {
            goto L_002A82;
        }
        a = myMapper->readCPU(0x0019);
        opLSR_A(1);
        if (flgC) {
            opINC(0x0436 + x, 1);
            a = myMapper->readCPU(0x0436 + x);
            opAND(0x03);
            myMapper->writeCPU(0x0436 + x, a);
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x01);
            opDEC(0x045A + x, 1);
            if (flgZ) {
                a = 0x00;
                myMapper->writeCPU((0x00C1 + x) & 0x00ff, a);
                myMapper->writeCPU((0x007F + x) & 0x00ff, a);
                myMapper->writeCPU(0x00F0, 0x20);
            }
        }
        popAddress();
        return;
    }
L_002A82:
    a = myMapper->readCPU(0x0412 + x);
    flgC = false;
    y = myMapper->readCPU(0x0451 + x);
    opADC(myMapper->readCPU(0xE5F7 + y));
    myMapper->writeCPU(0x0412 + x, a);
    if (flgC) {
        opINC(0x041B + x, 1);
    }
    a = myMapper->readCPU(0x041B + x);
    setLoadFlag(a);
    if (!flgN) {
        opCMP(a, myMapper->readCPU(0xE663 + y));
        if (!flgC) {
            goto L_002AD2;
        }
        if (flgZ) {
            if (myMapper->readCPU(0x0412 + x) < myMapper->readCPU(0xE657 + y)) {
                goto L_002AD2;
            }
        }
        myMapper->writeCPU(0x0412 + x, myMapper->readCPU(0xE657 + y));
        myMapper->writeCPU(0x041B + x, myMapper->readCPU(0xE663 + y));
    }
    else {
        opCMP(a, myMapper->readCPU(0xE67B + y));
        if (flgC) {
            if (!flgZ) {
                goto L_002AD2;
            }
            if (myMapper->readCPU(0x0412 + x) >= myMapper->readCPU(0xE66F + y)) {
                goto L_002AD2;
            }
        }
        myMapper->writeCPU(0x0412 + x, myMapper->readCPU(0xE66F + y));
        myMapper->writeCPU(0x041B + x, myMapper->readCPU(0xE67B + y));
    }
L_002AD2:
    pushAddress(0x002AD2);
    SUB_002B96();
    if (poppedEntry.value != 0x002AD2) return;
    if (a < 0xF8) {
        if (a < 0xE8) {
            goto L_002B03;
        }
        myMapper->writeCPU((0x0088 + x) & 0x00ff, 0xFF);
        myMapper->writeCPU(0x00BB, 0x04);
        myMapper->writeCPU(0x00BC, myMapper->readCPU((0x0091 + x) & 0x00ff));
        if (x >= 0x02) {
            myMapper->writeCPU((0x0088 + x) & 0x00ff, 0x80);
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x00);
            a = 0x01;
            setLoadFlag(a);
            myMapper->writeCPU(0x00F3, a);
            if (!flgZ) {
                goto L_002B03;
            }
        }
        if (myMapper->readCPU(0x00C8) == 0) {
            myMapper->writeCPU(0x00F0, 0x40);
        }
    }
L_002B03:
    a = myMapper->readCPU(0x042D + x);
    setLoadFlag(a);
    if (!flgN) {
        opCMP(a, myMapper->readCPU(0xE633 + y));
        if (!flgC) {
            goto L_002B41;
        }
        if (flgZ) {
            if (myMapper->readCPU(0x0424 + x) < myMapper->readCPU(0xE627 + y)) {
                goto L_002B41;
            }
        }
        myMapper->writeCPU(0x0424 + x, myMapper->readCPU(0xE627 + y));
        myMapper->writeCPU(0x042D + x, myMapper->readCPU(0xE633 + y));
    }
    else {
        opCMP(a, myMapper->readCPU(0xE64B + y));
        if (flgC) {
            if (!flgZ) {
                goto L_002B41;
            }
            if (myMapper->readCPU(0x0424 + x) >= myMapper->readCPU(0xE63F + y)) {
                goto L_002B41;
            }
        }
        myMapper->writeCPU(0x0424 + x, myMapper->readCPU(0xE63F + y));
        myMapper->writeCPU(0x042D + x, myMapper->readCPU(0xE64B + y));
    }
L_002B41:
    pushAddress(0x002B41);
    SUB_002B84();
    if (poppedEntry.value != 0x002B41) return;
    if (myMapper->readCPU(0x0016) != 0) {
        a = myMapper->readCPU((0x0091 + x) & 0x00ff);
        if (a < 0x10) {
            a = 0x10;
        }
        if (a >= 0xE0) {
            a = 0xE0;
        }
        myMapper->writeCPU((0x0091 + x) & 0x00ff, a);
    }
    if (myMapper->readCPU(0x00C8) != 0) {
        if (myMapper->readCPU((0x0088 + x) & 0x00ff) != 0) {
            goto L_002B83;
        }
        if (myMapper->readCPU((0x009A + x) & 0x00ff) >= 0xC8) {
            myMapper->writeCPU((0x009A + x) & 0x00ff, 0xC7);
            if (myMapper->readCPU(0x0451 + x) != 0x0B) {
                goto L_002B7A;
            }
            opDEC(0x0451 + x, 1);
            pushAddress(0x002B74);
            SUB_0030FD();
            if (poppedEntry.value != 0x002B74) return;
            SUB_003182();
            return;
        L_002B7A:
            myMapper->writeCPU((0x0088 + x) & 0x00ff, 0x02);
            myMapper->writeCPU(0x0451 + x, 0x03);
        }
    }
L_002B83:
    popAddress();
}

void game::SUB_002B84() {
    a = myMapper->readCPU(0x0400 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0424 + x));
    myMapper->writeCPU(0x0400 + x, a);
    a = myMapper->readCPU((0x0091 + x) & 0x00ff);
    opADC(myMapper->readCPU(0x042D + x));
    myMapper->writeCPU((0x0091 + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_002B96() {
    a = myMapper->readCPU(0x0409 + x);
    flgC = false;
    opADC(myMapper->readCPU(0x0412 + x));
    myMapper->writeCPU(0x0409 + x, a);
    a = myMapper->readCPU((0x009A + x) & 0x00ff);
    opADC(myMapper->readCPU(0x041B + x));
    myMapper->writeCPU((0x009A + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_002BA8() {
    pushAddress(0x002BA8);
    SUB_0030AA();
    if (poppedEntry.value != 0x002BA8) return;
    pushAddress(0x002BAB);
    SUB_002B84();
    if (poppedEntry.value != 0x002BAB) return;
    SUB_0030AA();
    return;
}

void game::SUB_002BB1() {
    pushAddress(0x002BB1);
    SUB_0030AA();
    if (poppedEntry.value != 0x002BB1) return;
    pushAddress(0x002BB4);
    SUB_002B96();
    if (poppedEntry.value != 0x002BB4) return;
    SUB_0030AA();
    return;
}

void game::SUB_002BBA() {
    if (x >= 0x02) {
        goto L_002BD9;
    }
    if (myMapper->readCPU((0x0088 + x) & 0x00ff) == 0) {
        if (myMapper->readCPU(0x0436 + x) != 0) {
            goto L_002BCC;
        }
        myMapper->writeCPU((0x007F + x) & 0x00ff, 0x00);
        popAddress();
        return;
    }
L_002BCC:
    if (myMapper->readCPU((0x007F + x) & 0x00ff) < 0x06) {
        goto L_002C2E;
    }
    myMapper->writeCPU((0x007F + x) & 0x00ff, 0x01);
    opDEC((0x0088 + x) & 0x00ff, 1);
    popAddress();
    return;
L_002BD9:
    if (myMapper->readCPU((0x0088 + x) & 0x00ff) != 0x02) {
        if (myMapper->readCPU(0x0436 + x) != 0) {
            goto L_002BF3;
        }
        if (myMapper->readCPU((0x0088 + x) & 0x00ff) == 0) {
            myMapper->writeCPU((0x007F + x) & 0x00ff, 0x00);
            popAddress();
            return;
        }
        a = myMapper->readCPU((0x007F + x) & 0x00ff);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_002BF4;
        }
        opINC((0x007F + x) & 0x00ff, 1);
    L_002BF3:
        popAddress();
        return;
    L_002BF4:
        if (a < 0x02) {
            goto L_002BF3;
        }
        opDEC(0x045A + x, 1);
        if (flgZ) {
            myMapper->writeCPU(0x045A + x, myMapper->readCPU(0x00C7));
            opINC((0x007F + x) & 0x00ff, 1);
            if (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x07) {
                myMapper->writeCPU((0x0088 + x) & 0x00ff, 0x02);
                myMapper->writeCPU((0x007F + x) & 0x00ff, 0x00);
                y = myMapper->readCPU(0x0451 + x);
                a = myMapper->readCPU(0xECA4 + y);
                if (myMapper->readCPU(0x047E + x) == 0) {
                    opDEC(0x047E + x, 1);
                    a = myMapper->readCPU(0x0451 + x);
                    opAND(0x03);
                }
                myMapper->writeCPU(0x0451 + x, a);
                myMapper->writeCPU(0x041B + x, 0xFE);
            }
        }
        popAddress();
        return;
    }
L_002C2E:
    pushAddress(0x002C2E);
    SUB_0026DF();
    if (poppedEntry.value != 0x002C2E) return;
    a = myMapper->readCPU((0x0031 + x) & 0x00ff);
    opAND(0xC3);
    if (!flgZ) {
        if (x >= 0x02) {
            goto L_002C3F;
        }
        myMapper->writeCPU((0x00BD + x) & 0x00ff, 0x00);
    }
L_002C3F:
    a = myMapper->readCPU((0x0031 + x) & 0x00ff);
    opAND(0x40);
    if (flgZ) {
        a = myMapper->readCPU((0x0031 + x) & 0x00ff);
        opAND(0x80);
        if (flgZ) {
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0620 + x, a);
            if (flgZ) {
                goto L_002CA3;
            }
        }
        if (myMapper->readCPU(0x0620 + x) != 0) {
            goto L_002CA3;
        }
    }
    a = myMapper->readCPU((0x007F + x) & 0x00ff);
    if (a >= 0x02) {
        opDEC((0x009A + x) & 0x00ff, 2);
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0412 + x, a);
        myMapper->writeCPU(0x041B + x, a);
        if (flgZ) {
            goto L_002C74;
        }
    }
    if (a != 0x01) {
        if (myMapper->readCPU(0x0436 + x) != 0) {
            goto L_002CA3;
        }
    }
L_002C74:
    myMapper->writeCPU((0x007F + x) & 0x00ff, 0x00);
    myMapper->writeCPU(0x0436 + x, 0x01);
    myMapper->writeCPU(0x0620 + x, 0x01);
    y = 0x00;
    if (x >= 0x02) {
        opINY(1);
    }
    a = myMapper->readCPU(0x00F0 + y);
    opORA(0x10);
    myMapper->writeCPU(0x00F0 + y, a);
    a = myMapper->readCPU(0x0412 + x);
    flgC = true;
    y = myMapper->readCPU(0x0451 + x);
    opSBC(myMapper->readCPU(0xE603 + y));
    myMapper->writeCPU(0x0412 + x, a);
    if (flgC) {
        goto L_002CA3;
    }
    opDEC(0x041B + x, 1);
L_002CA3:
    popAddress();
}

void game::SUB_002CB0() {
    if (myMapper->readCPU((0x007F + x) & 0x00ff) != 0) {
        SUB_002D1D();
        return;
    }
    pushAddress(0x002CB4);
    SUB_0027A7();
    if (poppedEntry.value != 0x002CB4) return;
    pushAddress(0x002CB7);
    SUB_002B84();
    if (poppedEntry.value != 0x002CB7) return;
    a = myMapper->readCPU(0x0409 + x);
    flgC = true;
    opSBC(0x60);
    myMapper->writeCPU(0x0409 + x, a);
    a = myMapper->readCPU((0x009A + x) & 0x00ff);
    opSBC(0x00);
    myMapper->writeCPU((0x009A + x) & 0x00ff, a);
    if (a < 0xF1) {
        goto L_002CD1;
    }
    myMapper->writeCPU((0x0088 + x) & 0x00ff, 0xFF);
L_002CD1:
    a = x;
    opPHA();
    y = 0x01;
    do {
        a = myMapper->readCPU(0x0088 + y);
        setLoadFlag(a);
        if (!flgZ) {
            if (flgN) {
                goto L_002D18;
            }
            a = myMapper->readCPU((0x009A + x) & 0x00ff);
            flgC = true;
            opSBC(myMapper->readCPU(0x009A + y));
            pushAddress(0x002CE2);
            SUB_003084();
            if (poppedEntry.value != 0x002CE2) return;
            if (a < 0x18) {
                a = myMapper->readCPU((0x0091 + x) & 0x00ff);
                flgC = true;
                opSBC(myMapper->readCPU(0x0091 + y));
                pushAddress(0x002CEF);
                SUB_003084();
                if (poppedEntry.value != 0x002CEF) return;
                if (a >= 0x10) {
                    goto L_002D18;
                }
                myMapper->writeCPU((0x007F + x) & 0x00ff, 0xFF);
                myMapper->writeCPU(0x045A + x, 0x03);
                myMapper->writeCPU(0x00C5, 0x78);
                myMapper->writeCPU(0x00F0, 0x02);
                a = 0x32;
                myMapper->writeCPU(0x003E, y);
                pushAddress(0x002D0B);
                SUB_0016D4();
                if (poppedEntry.value != 0x002D0B) return;
                a = 0x01;
                x = myMapper->readCPU(0x003E);
                pushAddress(0x002D12);
                SUB_001867();
                if (poppedEntry.value != 0x002D12) return;
                opPLA();
                x = a;
                popAddress();
                return;
            }
        }
    L_002D18:
        opDEY(1);
    } while (!flgN);
    opPLA();
    x = a;
    SUB_002D1D();
    return;
}

void game::SUB_002D1D() {
    popAddress();
}

void game::SUB_002D1E() {
    y = myMapper->readCPU((0x0088 + x) & 0x00ff);
    opDEY(1);
    if (!flgN) {
        goto L_002D24;
    }
    do {
        popAddress();
        return;
    L_002D24:
        if (myMapper->readCPU((0x009A + x) & 0x00ff) < 0xF9) {
            goto L_002D36;
        }
    } while (!(myMapper->readCPU(0x041B + x) & 0x80));
    a = 0x00;
    myMapper->writeCPU(0x00CC, a);
    goto L_002DD7;
L_002D36:
    y = myMapper->readCPU(0x00CD);
    setLoadFlag(y);
    if (flgN) {
        SUB_002D1D();
        return;
    }
    while (true) {
        myMapper->writeCPU(0x00CC, 0x00);
        a = myMapper->readCPU(myMapper->readCPU(0x0027) + (myMapper->readCPU((0x0027 + 1) & 0x00ff) << 8) + y);
        flgC = true;
        opSBC(0x18);
        opCMP(a, myMapper->readCPU((0x009A + x) & 0x00ff));
        if (!flgC) {
            opADC(0x03);
            if (a >= myMapper->readCPU((0x009A + x) & 0x00ff)) {
                a = 0x01;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_002D5F;
                }
            }
            a = myMapper->readCPU(myMapper->readCPU(0x0029) + (myMapper->readCPU((0x0029 + 1) & 0x00ff) << 8) + y);
            opCMP(a, myMapper->readCPU((0x009A + x) & 0x00ff));
            if (flgC) {
                opSBC(0x03);
                if (a < myMapper->readCPU((0x009A + x) & 0x00ff)) {
                    a = 0x02;
                L_002D5F:
                    myMapper->writeCPU(0x00CC, a);
                    a = myMapper->readCPU(myMapper->readCPU(0x0023) + (myMapper->readCPU((0x0023 + 1) & 0x00ff) << 8) + y);
                    if (a != 0x10) {
                        flgC = true;
                        opSBC(0x0C);
                        if (a >= myMapper->readCPU((0x0091 + x) & 0x00ff)) {
                            goto L_002D7B;
                        }
                    }
                    a = myMapper->readCPU(myMapper->readCPU(0x0025) + (myMapper->readCPU((0x0025 + 1) & 0x00ff) << 8) + y);
                    if (a != 0xFF) {
                        flgC = true;
                        opSBC(0x04);
                        if (a < myMapper->readCPU((0x0091 + x) & 0x00ff)) {
                        L_002D7B:
                            myMapper->writeCPU(0x00CC, 0x00);
                        }
                    }
                }
                a = myMapper->readCPU(myMapper->readCPU(0x0023) + (myMapper->readCPU((0x0023 + 1) & 0x00ff) << 8) + y);
                flgC = true;
                opSBC(0x10);
                if (!flgZ) {
                    opCMP(a, myMapper->readCPU((0x0091 + x) & 0x00ff));
                    if (flgC) {
                        goto L_002DAC;
                    }
                    opADC(0x04);
                    if (a >= myMapper->readCPU((0x0091 + x) & 0x00ff)) {
                        a = myMapper->readCPU(0x00CC);
                        opORA(0x04);
                        if (!flgZ) {
                            goto L_002DAA;
                        }
                    }
                }
                a = myMapper->readCPU(myMapper->readCPU(0x0025) + (myMapper->readCPU((0x0025 + 1) & 0x00ff) << 8) + y);
                if (a != 0xFF) {
                    opCMP(a, myMapper->readCPU((0x0091 + x) & 0x00ff));
                    if (flgC) {
                        opSBC(0x04);
                        if (a >= myMapper->readCPU((0x0091 + x) & 0x00ff)) {
                            goto L_002DAC;
                        }
                        a = myMapper->readCPU(0x00CC);
                        opORA(0x08);
                    L_002DAA:
                        myMapper->writeCPU(0x00CC, a);
                    }
                }
            }
        }
    L_002DAC:
        if (myMapper->readCPU(0x00CC) != 0) {
            goto L_002DB7;
        }
        opDEY(1);
        if (flgN) {
            goto L_002DB6;
        }
    }
L_002DB6:
    popAddress();
    return;
L_002DB7:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (myMapper->readCPU(0x041B + x) & 0x80) {
            goto L_002DCC;
        }
        a = myMapper->readCPU(myMapper->readCPU(0x0027) + (myMapper->readCPU((0x0027 + 1) & 0x00ff) << 8) + y);
        opSBC(0x18);
        myMapper->writeCPU((0x009A + x) & 0x00ff, a);
        opINC((0x009A + x) & 0x00ff, 1);
        myMapper->writeCPU(0x00CB, 0x01);
    }
L_002DCC:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (!(myMapper->readCPU(0x041B + x) & 0x80)) {
            goto L_002DEA;
        }
        a = myMapper->readCPU(myMapper->readCPU(0x0029) + (myMapper->readCPU((0x0029 + 1) & 0x00ff) << 8) + y);
    L_002DD7:
        myMapper->writeCPU((0x009A + x) & 0x00ff, a);
        pushAddress(0x002DD9);
        SUB_0030FD();
        if (poppedEntry.value != 0x002DD9) return;
        pushAddress(0x002DDC);
        SUB_003182();
        if (poppedEntry.value != 0x002DDC) return;
        if (x < 0x02) {
            pushAddress(0x002DE3);
            SUB_000C29();
            if (poppedEntry.value != 0x002DE3) return;
        }
        if (myMapper->readCPU(0x00CB) != 0) {
            goto L_002E1A;
        }
    }
L_002DEA:
    opLSR_M(0x00CC, 1);
    if (flgC) {
        a = myMapper->readCPU(0x042D + x);
        setLoadFlag(a);
        if (!flgN) {
            if (!flgN) {
                goto L_002DFE;
            }
        }
    }
    opLSR_M(0x00CC, 1);
    if (flgC) {
        if (!(myMapper->readCPU(0x042D + x) & 0x80)) {
            goto L_002E1A;
        }
    L_002DFE:
        pushAddress(0x002DFE);
        SUB_0030D4();
        if (poppedEntry.value != 0x002DFE) return;
        pushAddress(0x002E01);
        SUB_003168();
        if (poppedEntry.value != 0x002E01) return;
        a = myMapper->readCPU(0x042D + x);
        opORA(myMapper->readCPU(0x0424 + x));
        if (flgZ) {
            goto L_002E1A;
        }
        a = myMapper->readCPU(0x0448 + x);
        opEOR(0x01);
        myMapper->writeCPU(0x0448 + x, a);
        a = myMapper->readCPU(0x00F1);
        opORA(0x02);
        myMapper->writeCPU(0x00F1, a);
    }
L_002E1A:
    popAddress();
}

void game::SUB_002E1B() {
    x = 0x07;
    while (true) {
        myMapper->writeCPU(0x0012, x);
        y = myMapper->readCPU(0x0012);
        opDEY(1);
        if (!flgN) {
            goto L_002E27;
        }
        do {
            do {
                do {
                    do {
                        goto L_002F20;
                    L_002E27:
                        a = myMapper->readCPU((0x0088 + x) & 0x00ff);
                        setLoadFlag(a);
                    } while (flgN);
                } while (flgZ);
                a = myMapper->readCPU(0x0088 + y);
                setLoadFlag(a);
            } while (flgN);
        } while (flgZ);
        myMapper->writeCPU(0x00CC, 0x00);
        a = myMapper->readCPU(0x009A + y);
        flgC = true;
        opSBC(myMapper->readCPU((0x009A + x) & 0x00ff));
        pushAddress(0x002E3E);
        SUB_003084();
        if (poppedEntry.value != 0x002E3E) return;
        if (a < 0x18) {
            a = myMapper->readCPU((0x009A + x) & 0x00ff);
            flgC = false;
            opADC(0x18);
            myMapper->writeCPU(0x0012, a);
            a = myMapper->readCPU(0x009A + y);
            flgC = false;
            opADC(0x07);
            flgC = true;
            opSBC(myMapper->readCPU(0x0012));
            pushAddress(0x002E55);
            SUB_003084();
            if (poppedEntry.value != 0x002E55) return;
            if (a < 0x04) {
                a = 0x01;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_002E72;
                }
            }
            a = myMapper->readCPU(0x009A + y);
            flgC = false;
            opADC(0x11);
            flgC = true;
            opSBC(myMapper->readCPU((0x009A + x) & 0x00ff));
            pushAddress(0x002E69);
            SUB_003084();
            if (poppedEntry.value != 0x002E69) return;
            if (a < 0x04) {
                a = 0x02;
            L_002E72:
                myMapper->writeCPU(0x00CC, a);
                a = myMapper->readCPU(0x0091 + y);
                flgC = true;
                opSBC(myMapper->readCPU((0x0091 + x) & 0x00ff));
                pushAddress(0x002E7A);
                SUB_003084();
                if (poppedEntry.value != 0x002E7A) return;
                if (a >= 0x10) {
                    myMapper->writeCPU(0x00CC, 0x00);
                }
            }
            a = myMapper->readCPU((0x0091 + x) & 0x00ff);
            flgC = false;
            opADC(0x10);
            myMapper->writeCPU(0x0012, a);
            a = myMapper->readCPU(0x0091 + y);
            flgC = false;
            opADC(0x07);
            flgC = true;
            opSBC(myMapper->readCPU(0x0012));
            pushAddress(0x002E95);
            SUB_003084();
            if (poppedEntry.value != 0x002E95) return;
            if (a < 0x04) {
                a = 0x04;
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_002EB2;
                }
            }
            a = myMapper->readCPU(0x0091 + y);
            flgC = false;
            opADC(0x09);
            flgC = true;
            opSBC(myMapper->readCPU((0x0091 + x) & 0x00ff));
            pushAddress(0x002EA9);
            SUB_003084();
            if (poppedEntry.value != 0x002EA9) return;
            if (a < 0x04) {
                a = 0x08;
            L_002EB2:
                opORA(myMapper->readCPU(0x00CC));
                myMapper->writeCPU(0x00CC, a);
            }
        }
        myMapper->writeCPU(0x004B, 0x00);
        opLSR_M(0x00CC, 1);
        if (flgC) {
            pushAddress(0x002EBE);
            SUB_00309C();
            if (poppedEntry.value != 0x002EBE) return;
            if (flgN) {
                goto L_002ECC;
            }
        }
        opLSR_M(0x00CC, 1);
        if (flgC) {
            pushAddress(0x002EC7);
            SUB_00309C();
            if (poppedEntry.value != 0x002EC7) return;
            if (!flgN) {
            L_002ECC:
                pushAddress(0x002ECC);
                SUB_0030B3();
                if (poppedEntry.value != 0x002ECC) return;
                if (!flgC) {
                    pushAddress(0x002ED1);
                    SUB_0030FD();
                    if (poppedEntry.value != 0x002ED1) return;
                    pushAddress(0x002ED4);
                    SUB_003182();
                    if (poppedEntry.value != 0x002ED4) return;
                    pushAddress(0x002ED7);
                    SUB_0030AA();
                    if (poppedEntry.value != 0x002ED7) return;
                    pushAddress(0x002EDA);
                    SUB_0030FD();
                    if (poppedEntry.value != 0x002EDA) return;
                    pushAddress(0x002EDD);
                    SUB_003182();
                    if (poppedEntry.value != 0x002EDD) return;
                    pushAddress(0x002EE0);
                    SUB_0030AA();
                    if (poppedEntry.value != 0x002EE0) return;
                }
                myMapper->writeCPU(0x004B, 0x01);
            }
        }
        opLSR_M(0x00CC, 1);
        if (flgC) {
            pushAddress(0x002EEB);
            SUB_00308E();
            if (poppedEntry.value != 0x002EEB) return;
            if (flgN) {
                goto L_002EF9;
            }
        }
        opLSR_M(0x00CC, 1);
        if (flgC) {
            pushAddress(0x002EF4);
            SUB_00308E();
            if (poppedEntry.value != 0x002EF4) return;
            if (!flgN) {
            L_002EF9:
                pushAddress(0x002EF9);
                SUB_0030B3();
                if (poppedEntry.value != 0x002EF9) return;
                if (!flgC) {
                    pushAddress(0x002EFE);
                    SUB_0030D4();
                    if (poppedEntry.value != 0x002EFE) return;
                    pushAddress(0x002F01);
                    SUB_003168();
                    if (poppedEntry.value != 0x002F01) return;
                    pushAddress(0x002F04);
                    SUB_0030AA();
                    if (poppedEntry.value != 0x002F04) return;
                    pushAddress(0x002F07);
                    SUB_0030D4();
                    if (poppedEntry.value != 0x002F07) return;
                    pushAddress(0x002F0A);
                    SUB_003168();
                    if (poppedEntry.value != 0x002F0A) return;
                    pushAddress(0x002F0D);
                    SUB_0030AA();
                    if (poppedEntry.value != 0x002F0D) return;
                }
                myMapper->writeCPU(0x004B, 0x01);
            }
        }
        pushAddress(0x002F14);
        SUB_002F2D();
        if (poppedEntry.value != 0x002F14) return;
        pushAddress(0x002F17);
        SUB_0030AA();
        if (poppedEntry.value != 0x002F17) return;
        pushAddress(0x002F1A);
        SUB_002F2D();
        if (poppedEntry.value != 0x002F1A) return;
        pushAddress(0x002F1D);
        SUB_0030AA();
        if (poppedEntry.value != 0x002F1D) return;
    L_002F20:
        opDEY(1);
        if (flgN) {
            goto L_002F26;
        }
        goto L_002E27;
    L_002F26:
        opDEX(1);
        if (flgN) {
            goto L_002F2C;
        }
    }
L_002F2C:
    popAddress();
}

void game::SUB_002F2D() {
    if (x < 0x02) {
        goto L_002F38;
    }
    if (y >= 0x02) {
        goto L_003039;
    }
L_002F38:
    myMapper->writeCPU(0x0487, 0x00);
    if (myMapper->readCPU(0x0475 + x) != 0) {
    }
    else {
        if (myMapper->readCPU(0x004B) != 0) {
            goto L_002F4C;
        }
        goto L_003039;
    L_002F4C:
        if (x < 0x02) {
            if (myMapper->readCPU((0x00BD + x) & 0x00ff) == 0) {
                goto L_002F68;
            }
        }
        else {
            if (myMapper->readCPU((0x0088 + x) & 0x00ff) != 0x01) {
                goto L_002F68;
            }
            if (myMapper->readCPU((0x007F + x) & 0x00ff) >= 0x02) {
                goto L_002F75;
            }
            myMapper->writeCPU(0x0487, 0x01);
        L_002F68:
            a = myMapper->readCPU(0x009A + y);
            flgC = false;
            opADC(0x04);
            if (a >= myMapper->readCPU((0x009A + x) & 0x00ff)) {
            }
            else {
            L_002F75:
                myMapper->writeCPU(0x0475 + x, 0x14);
                myMapper->writeCPU(0x0436 + x, 0x00);
                if (y >= 0x02) {
                    if (myMapper->readCPU(0x0088 + y) == 0x02) {
                        goto L_002F8D;
                    }
                    goto L_003039;
                }
            L_002F8D:
                a = myMapper->readCPU(0x00F0);
                opORA(0x02);
                myMapper->writeCPU(0x00F0, a);
                if (myMapper->readCPU((0x0088 + x) & 0x00ff) == 0x02) {
                    if (x >= 0x02) {
                        goto L_002FB6;
                    }
                    myMapper->writeCPU(0x0012, y);
                    y = myMapper->readCPU((0x007F + x) & 0x00ff);
                    a = myMapper->readCPU(0xF049 + y);
                    y = myMapper->readCPU(0x0012);
                    opPHA();
                    opPLA();
                    if (flgZ) {
                        goto L_003039;
                    }
                    myMapper->writeCPU((0x007F + x) & 0x00ff, a);
                    a = 0x00;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x0436 + x, a);
                    if (flgZ) {
                        goto L_002FE0;
                    }
                }
            L_002FB6:
                opDEC((0x0088 + x) & 0x00ff, 1);
                if (flgZ) {
                    myMapper->writeCPU(0x041B + x, 0xFF);
                    myMapper->writeCPU(0x0412 + x, 0x00);
                }
                a = 0x00;
                myMapper->writeCPU((0x007F + x) & 0x00ff, a);
                myMapper->writeCPU(0x0424 + x, a);
                myMapper->writeCPU(0x042D + x, a);
                if (!(myMapper->readCPU((0x0091 + x) & 0x00ff) & 0x80)) {
                    a = 0xFF;
                    setLoadFlag(a);
                    if (!flgZ) {
                        goto L_002FD8;
                    }
                }
                a = 0x00;
            L_002FD8:
                myMapper->writeCPU(0x046C + x, a);
                myMapper->writeCPU(0x0463 + x, 0x80);
            L_002FE0:
                myMapper->writeCPU(0x0012, y);
                y = myMapper->readCPU(0x0451 + x);
                myMapper->writeCPU(0x0451 + x, myMapper->readCPU(0xF054 + y));
                myMapper->writeCPU(0x047E + x, 0x01);
                y = myMapper->readCPU(0x0012);
                if (y < 0x02) {
                    a = myMapper->readCPU(0x0451 + x);
                    if (a != 0x07) {
                        if (a < 0x08) {
                            goto L_003007;
                        }
                        a = myMapper->readCPU(0x00F1);
                        opORA(0x80);
                        myMapper->writeCPU(0x00F1, a);
                    }
                L_003007:
                    y = myMapper->readCPU(0x0451 + x);
                    myMapper->writeCPU(0x0013, myMapper->readCPU(0xF060 + y));
                    if (myMapper->readCPU(0x0487) != 0) {
                        myMapper->writeCPU(0x0013, myMapper->readCPU(0xF06C + y));
                    }
                    a = myMapper->readCPU(0xF078 + y);
                    flgC = false;
                    opADC(myMapper->readCPU(0x0487));
                    myMapper->writeCPU(0x0014, a);
                    a = myMapper->readCPU(0x0012);
                    myMapper->writeCPU(0x003E, a);
                    opPHA();
                    a = x;
                    opPHA();
                    a = myMapper->readCPU(0x0013);
                    opPHA();
                    a = myMapper->readCPU(0x0014);
                    pushAddress(0x00302E);
                    SUB_001867();
                    if (poppedEntry.value != 0x00302E) return;
                    opPLA();
                    pushAddress(0x003032);
                    SUB_0016D4();
                    if (poppedEntry.value != 0x003032) return;
                    opPLA();
                    x = a;
                    opPLA();
                    y = a;
                }
            }
        }
    }
L_003039:
    a = myMapper->readCPU(0x0451 + x);
    if (a == 0x0B) {
        a = myMapper->readCPU(0x00C8);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_003048;
        }
        a = 0x20;
        myMapper->writeCPU(0x00F0, a);
    }
L_003048:
    popAddress();
}

void game::SUB_003084() {
    opPHA();
    opPLA();
    if (!flgN) {
        goto L_00308D;
    }
    opEOR(0xFF);
    flgC = false;
    opADC(0x01);
L_00308D:
    popAddress();
}

void game::SUB_00308E() {
    a = myMapper->readCPU(0x0424 + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x0424 + x));
    a = myMapper->readCPU(0x042D + y);
    opSBC(myMapper->readCPU(0x042D + x));
    popAddress();
}

void game::SUB_00309C() {
    a = myMapper->readCPU(0x0412 + y);
    flgC = true;
    opSBC(myMapper->readCPU(0x0412 + x));
    a = myMapper->readCPU(0x041B + y);
    opSBC(myMapper->readCPU(0x041B + x));
    popAddress();
}

void game::SUB_0030AA() {
    myMapper->writeCPU(0x0012, x);
    myMapper->writeCPU(0x0013, y);
    x = myMapper->readCPU(0x0013);
    y = myMapper->readCPU(0x0012);
    setLoadFlag(y);
    popAddress();
}

void game::SUB_0030B3() {
    opCMP(x, 0x02);
    if (flgC) {
        opCMP(myMapper->readCPU((0x007F + x) & 0x00ff), 0x02);
        if (flgC) {
            opCMP(0x01, myMapper->readCPU((0x0088 + x) & 0x00ff));
            if (!flgC) {
                opCMP(y, 0x02);
                if (flgC) {
                    opCMP(myMapper->readCPU(0x007F + y), 0x02);
                    if (!flgC) {
                        goto L_0030D3;
                    }
                    opCMP(0x01, myMapper->readCPU(0x0088 + y));
                }
            }
        }
    }
L_0030D3:
    popAddress();
}

void game::SUB_0030D4() {
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0424 + x));
    myMapper->writeCPU(0x0424 + x, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x042D + x));
    myMapper->writeCPU(0x042D + x, a);
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0463 + x));
    myMapper->writeCPU(0x0463 + x, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x046C + x));
    myMapper->writeCPU(0x046C + x, a);
    a = myMapper->readCPU((0x0031 + x) & 0x00ff);
    opAND(0x40);
    myMapper->writeCPU((0x0031 + x) & 0x00ff, a);
    popAddress();
}

void game::SUB_0030FD() {
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0412 + x));
    myMapper->writeCPU(0x0412 + x, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x041B + x));
    myMapper->writeCPU(0x041B + x, a);
    popAddress();
}

void game::SUB_00310F() {
    myMapper->writeCPU(0x002D, a);
    if (!(myMapper->readCPU(0x002C) & 0x80)) {
        SUB_003139();
        return;
    }
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x002B));
    myMapper->writeCPU(0x002B, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x002C));
    myMapper->writeCPU(0x002C, a);
    pushAddress(0x003122);
    SUB_003139();
    if (poppedEntry.value != 0x003122) return;
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x002E, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x002F));
    myMapper->writeCPU(0x002F, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x0030));
    myMapper->writeCPU(0x0030, a);
    popAddress();
}

void game::SUB_003139() {
    a = x;
    opPHA();
    a = 0x00;
    myMapper->writeCPU(0x002E, a);
    myMapper->writeCPU(0x002F, a);
    myMapper->writeCPU(0x0030, a);
    x = 0x08;
    do {
        opASL_M(0x002E, 1);
        opROL_M(0x002F, 1);
        opROL_M(0x0030, 1);
        opASL_M(0x002D, 1);
        if (!flgC) {
            goto L_003162;
        }
        flgC = false;
        a = myMapper->readCPU(0x002B);
        opADC(myMapper->readCPU(0x002E));
        myMapper->writeCPU(0x002E, a);
        a = myMapper->readCPU(0x002C);
        opADC(myMapper->readCPU(0x002F));
        myMapper->writeCPU(0x002F, a);
        a = 0x00;
        opADC(myMapper->readCPU(0x0030));
        myMapper->writeCPU(0x0030, a);
    L_003162:
        opDEX(1);
    } while (!flgZ);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003168() {
    myMapper->writeCPU(0x002B, myMapper->readCPU(0x0424 + x));
    myMapper->writeCPU(0x002C, myMapper->readCPU(0x042D + x));
    a = 0xCD;
    pushAddress(0x003174);
    SUB_00310F();
    if (poppedEntry.value != 0x003174) return;
    myMapper->writeCPU(0x0424 + x, myMapper->readCPU(0x002F));
    a = myMapper->readCPU(0x0030);
    myMapper->writeCPU(0x042D + x, a);
    popAddress();
}

void game::SUB_003182() {
    myMapper->writeCPU(0x002B, myMapper->readCPU(0x0412 + x));
    myMapper->writeCPU(0x002C, myMapper->readCPU(0x041B + x));
    a = 0xCD;
    pushAddress(0x00318E);
    SUB_00310F();
    if (poppedEntry.value != 0x00318E) return;
    myMapper->writeCPU(0x0412 + x, myMapper->readCPU(0x002F));
    a = myMapper->readCPU(0x0030);
    myMapper->writeCPU(0x041B + x, a);
    popAddress();
}

void game::SUB_00319C() {
    y = 0x04;
    do {
        a = myMapper->readCPU(0x0013);
        opASL_A(1);
        opROR_M(0x0013, 1);
        opROR_M(0x0012, 1);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0031A9() {
    a = x;
    opPHA();
    x = 0x0B;
    do {
        opASL_M(0x001B, 1);
        opROL_M(0x001C, 1);
        opROL_A(2);
        opEOR(myMapper->readCPU(0x001B));
        opROL_A(1);
        opEOR(myMapper->readCPU(0x001B));
        opLSR_A(2);
        opEOR(0xFF);
        opAND(0x01);
        opORA(myMapper->readCPU(0x001B));
        myMapper->writeCPU(0x001B, a);
        opDEX(1);
    } while (!flgZ);
    opPLA();
    x = a;
    a = myMapper->readCPU(0x001B);
    popAddress();
}

void game::SUB_0031CA() {
    pushAddress(0x0031CA);
    SUB_001AB7();
    if (poppedEntry.value != 0x0031CA) return;
    x = 0x09;
    do {
        a = 0x00;
        myMapper->writeCPU((0x0003 + x) & 0x00ff, a);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x003E, a);
    opINC(0x0041, 1);
    pushAddress(0x0031DA);
    SUB_0016D4();
    if (poppedEntry.value != 0x0031DA) return;
    myMapper->writeCPU(0x4015, 0x0F);
    myMapper->writeCPU(0x00F0, 0x01);
    a = 0x02;
    SUB_0031E8();
    return;
}

void game::SUB_0031E8() {
    myMapper->writeCPU(0x0041, a);
    y = myMapper->readCPU(0x0040);
    setLoadFlag(y);
    if (!flgZ) {
        goto L_0031F0;
    }
    a = 0xFF;
L_0031F0:
    myMapper->writeCPU(0x0042, a);
    x = 0x00;
    myMapper->writeCPU(0x0488, x);
    myMapper->writeCPU(0x003B, x);
    myMapper->writeCPU(0x003C, x);
    myMapper->writeCPU(0x0558, x);
    opDEX(1);
    myMapper->writeCPU(0x0089, x);
    x = myMapper->readCPU(0x0040);
    do {
        pushAddress(0x003203);
        SUB_0033A6();
        if (poppedEntry.value != 0x003203) return;
        opDEX(1);
    } while (!flgN);
    SUB_003209();
    return;
}

void game::SUB_003209() {
    myMapper->writeCPU(0x00C8, 0x00);
    a = myMapper->readCPU(0x003C);
    opLSR_A(2);
    if (a >= 0x08) {
        a = 0x08;
    }
    x = a;
    myMapper->writeCPU(0x00C6, myMapper->readCPU(0xF3B0 + x));
    myMapper->writeCPU(0x00C7, myMapper->readCPU(0xF3B9 + x));
    if (myMapper->readCPU(0x003C) < 0x02) {
        a = 0x03;
        myMapper->writeCPU(0x00C6, a);
        myMapper->writeCPU(0x00C7, a);
    }
    x = 0x07;
    do {
        a = 0x00;
        myMapper->writeCPU(0x0448 + x, a);
        myMapper->writeCPU(0x0475 + x, a);
        myMapper->writeCPU(0x047E + x, a);
        myMapper->writeCPU(0x0424 + x, a);
        myMapper->writeCPU(0x042D + x, a);
        myMapper->writeCPU(0x0412 + x, a);
        myMapper->writeCPU(0x041B + x, a);
        myMapper->writeCPU(0x0463 + x, a);
        myMapper->writeCPU(0x046C + x, a);
        myMapper->writeCPU(0x0400 + x, a);
        myMapper->writeCPU(0x0409 + x, a);
        a = 0x01;
        myMapper->writeCPU(0x043F + x, a);
        myMapper->writeCPU(0x045A + x, a);
        myMapper->writeCPU(0x0436 + x, 0x03);
        opDEX(1);
    } while (!flgN);
    x = 0x05;
    do {
        myMapper->writeCPU((0x008A + x) & 0x00ff, 0xFF);
        opDEX(1);
    } while (!flgN);
    x = myMapper->readCPU(0x0040);
    do {
        pushAddress(0x00326E);
        SUB_00337C();
        if (poppedEntry.value != 0x00326E) return;
        opDEX(1);
    } while (!flgN);
    pushAddress(0x003274);
    SUB_00123C();
    if (poppedEntry.value != 0x003274) return;
    pushAddress(0x003277);
    SUB_001289();
    if (poppedEntry.value != 0x003277) return;
    if (myMapper->readCPU(0x00C6) < 0x10) {
        myMapper->writeCPU(0x00C6, 0x58);
    }
    pushAddress(0x003284);
    SUB_00349B();
    if (poppedEntry.value != 0x003284) return;
    pushAddress(0x003287);
    SUB_0018F5();
    if (poppedEntry.value != 0x003287) return;
    if (myMapper->readCPU(0x0016) != 0) {
        SUB_0001BB();
        return;
    }
    if (myMapper->readCPU(0x00C8) != 0) {
        SUB_000F09();
        return;
    }
    pushAddress(0x003298);
    SUB_00070C();
    if (poppedEntry.value != 0x003298) return;
    a = myMapper->readCPU(0x003B);
    opAND(0x03);
    if (!flgZ) {
        goto L_0032A9;
    }
    myMapper->writeCPU(0x00F2, 0x08);
    x = myMapper->readCPU(0x003A);
    setLoadFlag(x);
    if (!flgZ) {
        goto L_0032AF;
    }
L_0032A9:
    myMapper->writeCPU(0x003D, 0xFF);
    opINC(0x003C, 1);
    while (true) {
        do {
            do {
                do {
                L_0032AF:
                    pushAddress(0x0032AF);
                    SUB_003466();
                    if (poppedEntry.value != 0x0032AF) return;
                    if (myMapper->readCPU(0x003D) != 0) {
                        opDEC(0x003D, 1);
                        pushAddress(0x0032B8);
                        SUB_0033C2();
                        if (poppedEntry.value != 0x0032B8) return;
                    }
                    pushAddress(0x0032BB);
                    SUB_0031A9();
                    if (poppedEntry.value != 0x0032BB) return;
                    pushAddress(0x0032BE);
                    SUB_002687();
                    if (poppedEntry.value != 0x0032BE) return;
                    pushAddress(0x0032C1);
                    SUB_0006EF();
                    if (poppedEntry.value != 0x0032C1) return;
                    pushAddress(0x0032C4);
                    SUB_000786();
                    if (poppedEntry.value != 0x0032C4) return;
                    pushAddress(0x0032C7);
                    SUB_000827();
                    if (poppedEntry.value != 0x0032C7) return;
                    pushAddress(0x0032CA);
                    SUB_0008AD();
                    if (poppedEntry.value != 0x0032CA) return;
                    pushAddress(0x0032CD);
                    SUB_0018D3();
                    if (poppedEntry.value != 0x0032CD) return;
                    pushAddress(0x0032D0);
                    SUB_00257D();
                    if (poppedEntry.value != 0x0032D0) return;
                    pushAddress(0x0032D3);
                    SUB_000B6A();
                    if (poppedEntry.value != 0x0032D3) return;
                    opINC(0x004C, 1);
                    x = myMapper->readCPU(0x0040);
                    do {
                        if (!(myMapper->readCPU((0x0088 + x) & 0x00ff) & 0x80)) {
                            goto L_003303;
                        }
                        if (myMapper->readCPU(0x003A) != 0) {
                            goto L_00331C;
                        }
                        if (!(myMapper->readCPU((0x0041 + x) & 0x00ff) & 0x80)) {
                            opDEC((0x00C3 + x) & 0x00ff, 1);
                            if (!flgZ) {
                                goto L_00331D;
                            }
                            a = x;
                            opPHA();
                            pushAddress(0x0032EC);
                            SUB_00071C();
                            if (poppedEntry.value != 0x0032EC) return;
                            opPLA();
                            x = a;
                            y = 0x02;
                            opDEC((0x0041 + x) & 0x00ff, 1);
                            myMapper->writeCPU(0x0046, y);
                            if (flgN) {
                                goto L_003303;
                            }
                            pushAddress(0x0032F9);
                            SUB_00337C();
                            if (poppedEntry.value != 0x0032F9) return;
                            pushAddress(0x0032FC);
                            SUB_0033A6();
                            if (poppedEntry.value != 0x0032FC) return;
                            myMapper->writeCPU(0x00F2, 0x80);
                        }
                    L_003303:
                        opDEX(1);
                    } while (!flgN);
                    if (!(myMapper->readCPU(0x0041) & 0x80)) {
                        goto L_00330E;
                    }
                    if (myMapper->readCPU(0x0042) & 0x80) {
                        SUB_00335C();
                        return;
                    }
                L_00330E:
                    if (myMapper->readCPU(0x003A) == 0) {
                        goto L_00331D;
                    }
                    pushAddress(0x003312);
                    SUB_00275E();
                    if (poppedEntry.value != 0x003312) return;
                    a = myMapper->readCPU(0x061C);
                    opAND(0x30);
                } while (flgZ);
            L_00331C:
                popAddress();
                return;
            L_00331D:
                x = 0x05;
            L_00331F:
                a = myMapper->readCPU((0x008A + x) & 0x00ff);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_003325;
                }
            } while (!flgN);
        L_003325:
            opDEX(1);
            if (!flgN) {
                goto L_00331F;
            }
        } while (!(myMapper->readCPU(0x00BB) & 0x80));
        x = myMapper->readCPU(0x0040);
    L_00332E:
        y = myMapper->readCPU((0x0088 + x) & 0x00ff);
        opDEY(1);
        if (!flgN) {
            goto L_003342;
        }
        if (myMapper->readCPU((0x0041 + x) & 0x00ff) & 0x80) {
            goto L_003342;
        }
        myMapper->writeCPU((0x0088 + x) & 0x00ff, 0xFF);
        myMapper->writeCPU((0x00C3 + x) & 0x00ff, 0x01);
    }
L_003342:
    opDEX(1);
    if (!flgN) {
        goto L_00332E;
    }
    myMapper->writeCPU(0x00F2, 0x02);
    SUB_003349();
    return;
}

void game::SUB_003349() {
    x = 0x96;
    pushAddress(0x00334B);
    SUB_003454();
    if (poppedEntry.value != 0x00334B) return;
    x = myMapper->readCPU(0x003B);
    opINX(1);
    if (x != 0x10) {
        goto L_003357;
    }
    x = 0x04;
L_003357:
    myMapper->writeCPU(0x003B, x);
    SUB_003209();
    return;
}

void game::SUB_00335C() {
    myMapper->writeCPU(0x00F2, 0x01);
    SUB_003360();
    return;
}

void game::SUB_003360() {
    a = 0x00;
    myMapper->writeCPU(0x0017, a);
    myMapper->writeCPU(0x0018, a);
    myMapper->writeCPU(0x0015, a);
    pushAddress(0x003368);
    SUB_003401();
    if (poppedEntry.value != 0x003368) return;
    do {
        pushAddress(0x00336B);
        SUB_00345B();
        if (poppedEntry.value != 0x00336B) return;
        pushAddress(0x00336E);
        SUB_00275E();
        if (poppedEntry.value != 0x00336E) return;
        opAND(0x30);
        if (!flgZ) {
            goto L_003379;
        }
        opDEC(0x0015, 1);
    } while (!flgZ);
L_003379:
    SUB_0031CA();
    return;
}

void game::SUB_00337C() {
    if (myMapper->readCPU((0x0041 + x) & 0x00ff) & 0x80) {
        goto L_0033A3;
    }
    myMapper->writeCPU((0x0091 + x) & 0x00ff, myMapper->readCPU(0xF3A4 + x));
    a = 0xB8;
    myMapper->writeCPU((0x009A + x) & 0x00ff, a);
    myMapper->writeCPU((0x00BD + x) & 0x00ff, a);
    myMapper->writeCPU((0x00BF + x) & 0x00ff, 0xC8);
    a = 0x5A;
    y = myMapper->readCPU((0x0041 + x) & 0x00ff);
    setLoadFlag(y);
    if (!flgN) {
        goto L_003397;
    }
    a = 0x01;
L_003397:
    myMapper->writeCPU((0x00C3 + x) & 0x00ff, a);
    a = 0x00;
    myMapper->writeCPU((0x00C1 + x) & 0x00ff, a);
    myMapper->writeCPU(0x042D + x, a);
    myMapper->writeCPU(0x0424 + x, a);
L_0033A3:
    popAddress();
}

void game::SUB_0033A6() {
    myMapper->writeCPU(0x0451 + x, 0x03);
    myMapper->writeCPU((0x0088 + x) & 0x00ff, 0x02);
    popAddress();
}

void game::SUB_0033C2() {
    a = myMapper->readCPU(0x003D);
    opAND(0x20);
    if (flgZ) {
        goto L_0033E4;
    }
    x = 0x0A;
    do {
        myMapper->writeCPU((0x0057 + x) & 0x00ff, myMapper->readCPU(0xF3EB + x));
        opDEX(1);
    } while (!flgN);
    y = 0x0A;
    myMapper->writeCPU(0x0043, myMapper->readCPU(0x003C));
    pushAddress(0x0033D8);
    SUB_001772();
    if (poppedEntry.value != 0x0033D8) return;
    myMapper->writeCPU(0x0060, a);
    myMapper->writeCPU(0x0061, myMapper->readCPU(0x0043));
    SUB_000123();
    return;
L_0033E4:
    a = 0xF6;
    y = 0xF3;
    SUB_000127();
    return;
}

void game::SUB_003401() {
    pushAddress(0x003401);
    SUB_00345B();
    if (poppedEntry.value != 0x003401) return;
    x = 0x01;
    do {
        a = myMapper->readCPU(0xF431 + x);
        y = myMapper->readCPU(0xF433 + x);
        pushAddress(0x00340C);
        SUB_000127();
        if (poppedEntry.value != 0x00340C) return;
        opDEX(1);
    } while (!flgN);
    x = 0x0F;
    do {
        myMapper->writeCPU((0x005A + x) & 0x00ff, 0x24);
        opDEX(1);
    } while (!flgN);
    myMapper->writeCPU(0x0059, 0x10);
    myMapper->writeCPU(0x0057, 0x21);
    x = 0x02;
    do {
        myMapper->writeCPU(0x0058, myMapper->readCPU(0xF435 + x));
        pushAddress(0x00342A);
        SUB_000123();
        if (poppedEntry.value != 0x00342A) return;
        opDEX(1);
    } while (!flgN);
    popAddress();
}

void game::SUB_003452() {
    x = 0x14;
    SUB_003454();
    return;
}

void game::SUB_003454() {
    do {
        pushAddress(0x003454);
        SUB_00345B();
        if (poppedEntry.value != 0x003454) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00345B() {
    myMapper->writeCPU(0x0002, 0x00);
    SUB_00345F();
    return;
}

void game::SUB_00345F() {
    do {
        wait();
        a = myMapper->readCPU(0x0002);
        setLoadFlag(a);
    } while (flgZ);
    opDEC(0x0002, 1);
    SUB_003465();
    return;
}

void game::SUB_003465() {
    popAddress();
}

void game::SUB_003466() {
    pushAddress(0x003466);
    SUB_00345F();
    if (poppedEntry.value != 0x003466) return;
    a = myMapper->readCPU(0x003A);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003465();
        return;
    }
    pushAddress(0x00346D);
    SUB_00275E();
    if (poppedEntry.value != 0x00346D) return;
    opAND(0x10);
    if (flgZ) {
        SUB_003465();
        return;
    }
    myMapper->writeCPU(0x00F2, 0x04);
    a = myMapper->readCPU(0x0001);
    opAND(0xEF);
    myMapper->writeCPU(0x2001, a);
    do {
        pushAddress(0x00347F);
        SUB_00345B();
        if (poppedEntry.value != 0x00347F) return;
        pushAddress(0x003482);
        SUB_00275E();
        if (poppedEntry.value != 0x003482) return;
        opAND(0x10);
    } while (flgZ);
    myMapper->writeCPU(0x2001, myMapper->readCPU(0x0001));
    y = 0x04;
    a = myMapper->readCPU(0x00C8);
    opORA(myMapper->readCPU(0x0016));
    if (flgZ) {
        goto L_003498;
    }
    y = 0x20;
L_003498:
    myMapper->writeCPU(0x00F2, y);
    popAddress();
}

void game::SUB_00349B() {
    a = 0x01;
    myMapper->writeCPU(0x048E, a);
    myMapper->writeCPU(0x048F, a);
    a = 0xFF;
    myMapper->writeCPU(0x00BB, a);
    myMapper->writeCPU(0x0087, a);
    myMapper->writeCPU(0x048C, a);
    x = 0x01;
    myMapper->writeCPU(0x0459, x);
    myMapper->writeCPU(0x0090, x);
    opINX(1);
    myMapper->writeCPU(0x0046, x);
    myMapper->writeCPU(0x0099, 0x40);
    popAddress();
}

void game::SUB_003500() {
    pushAddress(0x003500);
    SUB_00378F();
    if (poppedEntry.value != 0x003500) return;
    SUB_003503();
    return;
}

void game::SUB_003503() {
    popAddress();
}

void game::SUB_003504() {
    a = 0x00;
    x = a;
    setLoadFlag(x);
    myMapper->writeCPU(0x00FD, a);
    if (flgZ) {
        goto L_00351B;
    }
    do {
        a = x;
        opLSR_A(1);
        x = a;
    L_00350E:
        opINX(1);
        if (x == 0x04) {
            SUB_003503();
            return;
        }
        a = myMapper->readCPU(0x00FD);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x00FD, a);
    L_00351B:
        a = x;
        opASL_A(1);
        x = a;
        myMapper->writeCPU(0x00FE, myMapper->readCPU((0x00E0 + x) & 0x00ff));
        myMapper->writeCPU(0x00FF, myMapper->readCPU((0x00E1 + x) & 0x00ff));
    } while (myMapper->readCPU((0x00E1 + x) & 0x00ff) == 0);
    a = x;
    opLSR_A(1);
    x = a;
    opDEC((0x00D0 + x) & 0x00ff, 1);
    if (!flgZ) {
        goto L_00350E;
    }
L_003531:
    y = myMapper->readCPU((0x00E8 + x) & 0x00ff);
    opINC((0x00E8 + x) & 0x00ff, 1);
    a = myMapper->readCPU(myMapper->readCPU(0x00FE) + (myMapper->readCPU((0x00FE + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (flgZ) {
        SUB_003500();
        return;
    }
    y = a;
    if (a != 0xFF) {
        opAND(0xC0);
        if (a == 0xC0) {
            goto L_003553;
        }
    }
    else {
        if (myMapper->readCPU((0x00D8 + x) & 0x00ff) == 0) {
            goto L_00355E;
        }
        opDEC((0x00D8 + x) & 0x00ff, 1);
        a = myMapper->readCPU((0x00EC + x) & 0x00ff);
        setLoadFlag(a);
        myMapper->writeCPU((0x00E8 + x) & 0x00ff, a);
        if (flgZ) {
        L_003553:
            a = y;
            opAND(0x3F);
            myMapper->writeCPU((0x00D8 + x) & 0x00ff, a);
            opDEC((0x00D8 + x) & 0x00ff, 1);
            myMapper->writeCPU((0x00EC + x) & 0x00ff, myMapper->readCPU((0x00E8 + x) & 0x00ff));
        }
    L_00355E:
        goto L_003531;
    }
    a = y;
    setLoadFlag(a);
    if (!flgN) {
        goto L_00357B;
    }
    opAND(0x0F);
    flgC = false;
    opADC(myMapper->readCPU(0x00DF));
    y = a;
    a = myMapper->readCPU(0xF660 + y);
    myMapper->writeCPU((0x00D4 + x) & 0x00ff, a);
    y = a;
    if (x == 0x02) {
        goto L_0035C4;
    }
    while (true) {
        y = myMapper->readCPU((0x00E8 + x) & 0x00ff);
        opINC((0x00E8 + x) & 0x00ff, 1);
        a = myMapper->readCPU(myMapper->readCPU(0x00FE) + (myMapper->readCPU((0x00FE + 1) & 0x00ff) << 8) + y);
    L_00357B:
        y = a;
        a = x;
        if (a == 0x03) {
            goto L_0035E1;
        }
        opPHA();
        x = a;
        if (a == 0x01) {
            goto L_0035B9;
        }
        do {
            x = myMapper->readCPU(0x00FD);
            a = myMapper->readCPU(0xF601 + y);
            setLoadFlag(a);
            if (!flgZ) {
                myMapper->writeCPU(0x4002 + x, a);
                a = myMapper->readCPU(0xF600 + y);
                opORA(0x08);
                myMapper->writeCPU(0x4003 + x, a);
            }
            y = a;
            opPLA();
            x = a;
            if (y != 0) {
                goto L_0035AA;
            }
            y = 0x00;
            if (x == 0x02) {
                goto L_0035AC;
            }
            y = 0x10;
            setLoadFlag(y);
            if (!flgZ) {
                goto L_0035AC;
            }
        L_0035AA:
            y = myMapper->readCPU((0x00DC + x) & 0x00ff);
        L_0035AC:
            a = y;
            y = myMapper->readCPU(0x00FD);
            myMapper->writeCPU(0x4000 + y, a);
        L_0035B2:
            myMapper->writeCPU((0x00D0 + x) & 0x00ff, myMapper->readCPU((0x00D4 + x) & 0x00ff));
            goto L_00350E;
        L_0035B9:
            a = myMapper->readCPU(0x00F5);
            opAND(0x02);
        } while (flgZ);
        opPLA();
        x = a;
        goto L_0035B2;
    L_0035C4:
        a = y;
        if (myMapper->readCPU(0x06F0) != 0) {
            a = 0xFF;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0035D9;
            }
        }
        flgC = false;
        opADC(0xFE);
        opASL_A(2);
        if (a < 0x3C) {
            goto L_0035D9;
        }
        a = 0x3C;
    L_0035D9:
        myMapper->writeCPU(0x4008, a);
        myMapper->writeCPU(0x00DE, a);
    }
L_0035E1:
    if (myMapper->readCPU(0x00F4) == 0x02) {
        goto L_0035F9;
    }
    myMapper->writeCPU(0x400C, myMapper->readCPU(0xF700 + y));
    myMapper->writeCPU(0x400E, myMapper->readCPU(0xF701 + y));
    myMapper->writeCPU(0x400F, myMapper->readCPU(0xF702 + y));
L_0035F9:
    goto L_0035B2;
}

void game::SUB_003683() {
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_003691();
        return;
    }
    SUB_003687();
    return;
}

void game::SUB_003687() {
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003691();
        return;
    }
    SUB_00368B();
    return;
}

void game::SUB_00368B() {
    a = 0x0C;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003691();
        return;
    }
    SUB_00368F();
    return;
}

void game::SUB_00368F() {
    a = 0x04;
    SUB_003691();
    return;
}

void game::SUB_003691() {
    myMapper->writeCPU(0x00F9, a);
    myMapper->writeCPU(0x00FA, 0x40);
    myMapper->writeCPU(0x00FB, x);
    myMapper->writeCPU(0x00FC, y);
    y = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x00F9) + (myMapper->readCPU((0x00F9 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(myMapper->readCPU(0x00FB) + (myMapper->readCPU((0x00FB + 1) & 0x00ff) << 8) + y));
        opINY(1);
    } while (y != 0x04);
    popAddress();
}

void game::SUB_0036A8() {
    x = a;
    pushAddress(0x0036A9);
    SUB_003798();
    if (poppedEntry.value != 0x0036A9) return;
    myMapper->writeCPU(0x00F6, x);
    a = myMapper->readCPU(0x06F5);
    setLoadFlag(a);
    if (!flgZ) {
        if (a != 0x02) {
            goto L_0036BE;
        }
        myMapper->writeCPU(0x00F0, a);
        myMapper->writeCPU(0x06F5, 0x00);
    }
L_0036BE:
    y = myMapper->readCPU(0xFBCA + y);
    x = 0x00;
    do {
        myMapper->writeCPU((0x00DF + x) & 0x00ff, myMapper->readCPU(0xFBCA + y));
        opINY(1);
        opINX(1);
    } while (x != 0x09);
    a = 0x01;
    myMapper->writeCPU(0x00D0, a);
    myMapper->writeCPU(0x00D1, a);
    myMapper->writeCPU(0x00D2, a);
    myMapper->writeCPU(0x00D3, a);
    a = 0x00;
    myMapper->writeCPU(0x00E8, a);
    myMapper->writeCPU(0x00E9, a);
    myMapper->writeCPU(0x00EA, a);
    myMapper->writeCPU(0x00EB, a);
    popAddress();
}

void game::SUB_003712() {
    a = 0x7F;
    myMapper->writeCPU(0x4001, a);
    myMapper->writeCPU(0x4005, a);
    SUB_00371A();
    return;
}

void game::SUB_00371A() {
    myMapper->writeCPU(0x00DC, x);
    myMapper->writeCPU(0x00DD, y);
    popAddress();
}

void game::SUB_00371F() {
    x = 0xE5;
    y = 0xF6;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_003745();
        return;
    }
    SUB_003725();
    return;
}

void game::SUB_003725() {
    a = myMapper->readCPU(0x00F3);
    opLSR_A(1);
    if (flgC) {
        goto L_003736;
    }
    a = myMapper->readCPU(0x00F7);
    opLSR_A(1);
    if (flgC) {
        SUB_003749();
        return;
    }
    a = myMapper->readCPU(0x00F0);
    opAND(0x10);
    if (!flgZ) {
        SUB_00371F();
        return;
    }
    popAddress();
    return;
L_003736:
    a = myMapper->readCPU(0x00F7);
    opORA(0x01);
    myMapper->writeCPU(0x00F7, a);
    myMapper->writeCPU(0x06E4, 0x00);
    x = 0xFC;
    y = 0xF5;
    SUB_003745();
    return;
}

void game::SUB_003745() {
    pushAddress(0x003745);
    SUB_003683();
    if (poppedEntry.value != 0x003745) return;
    popAddress();
}

void game::SUB_003749() {
    opINC(0x06E4, 1);
    if (myMapper->readCPU(0x06E4) != 0x58) {
        SUB_00377B();
        return;
    }
    myMapper->writeCPU(0x00F7, 0x00);
    popAddress();
}

void game::SUB_003758() {
    myMapper->writeCPU(0x4017, 0xC0);
    pushAddress(0x00375D);
    SUB_003B25();
    if (poppedEntry.value != 0x00375D) return;
    pushAddress(0x003760);
    SUB_00390A();
    if (poppedEntry.value != 0x003760) return;
    pushAddress(0x003763);
    SUB_003A38();
    if (poppedEntry.value != 0x003763) return;
    pushAddress(0x003766);
    SUB_003AAC();
    if (poppedEntry.value != 0x003766) return;
    pushAddress(0x003769);
    SUB_003824();
    if (poppedEntry.value != 0x003769) return;
    myMapper->writeCPU(0x06E9, myMapper->readCPU(0x00F1));
    a = 0x00;
    myMapper->writeCPU(0x00F0, a);
    myMapper->writeCPU(0x00F1, a);
    myMapper->writeCPU(0x00F2, a);
    myMapper->writeCPU(0x00F3, a);
    SUB_00377B();
    return;
}

void game::SUB_00377B() {
    popAddress();
}

void game::SUB_00377C() {
    a = myMapper->readCPU(0x00F4);
    opAND(0x06);
    if (!flgZ) {
        SUB_00377B();
        return;
    }
    a = myMapper->readCPU(0x00F4);
    opAND(0xF0);
    myMapper->writeCPU(0x00F4, a);
    x = 0xE9;
    y = 0xF6;
    SUB_003879();
    return;
}

void game::SUB_00378F() {
    a = myMapper->readCPU(0x00F6);
    if (a != 0x20) {
        SUB_00379F();
        return;
    }
    opINC(0x06E8, 1);
    SUB_003798();
    return;
}

void game::SUB_003798() {
    opAND(0x0F);
    if (a != 0x0F) {
        SUB_0037A5();
        return;
    }
    a = x;
    SUB_00379F();
    return;
}

void game::SUB_00379F() {
    a = myMapper->readCPU(0x00F4);
    opAND(0x20);
    if (!flgZ) {
        SUB_0037C7();
        return;
    }
    SUB_0037A5();
    return;
}

void game::SUB_0037A5() {
    a = 0x10;
    myMapper->writeCPU(0x400C, a);
    myMapper->writeCPU(0x4000, a);
    myMapper->writeCPU(0x4004, a);
    a = 0x00;
    myMapper->writeCPU(0x00F4, a);
    SUB_0037B4();
    return;
}

void game::SUB_0037B4() {
    myMapper->writeCPU(0x00F5, a);
    myMapper->writeCPU(0x00F6, a);
    myMapper->writeCPU(0x06FA, a);
    myMapper->writeCPU(0x00F7, a);
    myMapper->writeCPU(0x4008, a);
    myMapper->writeCPU(0x4011, a);
    myMapper->writeCPU(0x06F0, a);
    popAddress();
}

void game::SUB_0037C7() {
    a = 0x10;
    myMapper->writeCPU(0x4004, a);
    myMapper->writeCPU(0x400C, a);
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_0037B4();
        return;
    }
    SUB_0037D3();
    return;
}

void game::SUB_0037D3() {
    myMapper->writeCPU(0x06FA, 0x00);
    popAddress();
}

void game::SUB_0037D9() {
    x = 0xF5;
    y = 0xF6;
    SUB_003879();
    return;
}

void game::SUB_0037E0() {
    opINC(0x06FB, 1);
    a = myMapper->readCPU(0x06FB);
    if (a == 0x10) {
        SUB_0037D9();
        return;
    }
    if (a == 0x20) {
        SUB_0037D3();
        return;
    }
    popAddress();
}

void game::SUB_0037EF() {
    myMapper->writeCPU(0x06FB, 0x00);
    myMapper->writeCPU(0x06FA, 0xF0);
    x = 0xF1;
    y = 0xF6;
    SUB_003879();
    return;
}

void game::SUB_003800() {
    a = myMapper->readCPU(0x00F4);
    opAND(0xF0);
    opORA(0x02);
    myMapper->writeCPU(0x00F4, a);
    myMapper->writeCPU(0x06F7, 0x00);
    x = 0xF1;
    y = 0xF6;
    SUB_003879();
    return;
}

void game::SUB_003814() {
    opINC(0x06F7, 1);
    if (myMapper->readCPU(0x06F7) != 0x10) {
        SUB_00385B();
        return;
    }
    SUB_00389B();
    return;
}

void game::SUB_003821() {
    SUB_0037A5();
    return;
}

void game::SUB_003824() {
    a = myMapper->readCPU(0x00F0);
    opLSR_A(1);
    if (flgC) {
        SUB_003821();
        return;
    }
    a = myMapper->readCPU(0x00F6);
    if (a != 0xDF) {
        if (a == 0x7F) {
            goto L_00383B;
        }
        if (a == 0x20) {
            goto L_00383B;
        }
        if (myMapper->readCPU(0x00F6) != 0) {
            SUB_00385B();
            return;
        }
    }
L_00383B:
    a = myMapper->readCPU(0x06FA);
    if (a == 0x0F) {
        SUB_0037EF();
        return;
    }
    if (a == 0xF0) {
        SUB_0037E0();
        return;
    }
    a = myMapper->readCPU(0x00F0);
    opLSR_A(2);
    if (flgC) {
        SUB_003800();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_00385F();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_00385C();
        return;
    }
    a = myMapper->readCPU(0x00F4);
    opLSR_A(2);
    if (flgC) {
        SUB_003814();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_00387D();
        return;
    }
    SUB_00385B();
    return;
}

void game::SUB_00385B() {
    popAddress();
}

void game::SUB_00385C() {
    SUB_00377C();
    return;
}

void game::SUB_00385F() {
    a = myMapper->readCPU(0x00F4);
    opAND(0x80);
    if (!flgZ) {
        SUB_00385B();
        return;
    }
    a = myMapper->readCPU(0x00F4);
    opAND(0xF0);
    opORA(0x04);
    myMapper->writeCPU(0x00F4, a);
    a = 0x00;
    myMapper->writeCPU(0x06F3, a);
    myMapper->writeCPU(0x06F1, a);
    x = 0xED;
    y = 0xF6;
    SUB_003879();
    return;
}

void game::SUB_003879() {
    pushAddress(0x003879);
    SUB_00368B();
    if (poppedEntry.value != 0x003879) return;
    popAddress();
}

void game::SUB_00387D() {
    opINC(0x06F3, 1);
    if (myMapper->readCPU(0x06F3) != 0x03) {
        SUB_0038A1();
        return;
    }
    myMapper->writeCPU(0x06F3, 0x00);
    opINC(0x06F1, 1);
    a = myMapper->readCPU(0x06F1);
    if (a != 0x10) {
        SUB_0038A2();
        return;
    }
    myMapper->writeCPU(0x400C, 0x10);
    SUB_00389B();
    return;
}

void game::SUB_00389B() {
    a = myMapper->readCPU(0x00F4);
    opAND(0xF0);
    myMapper->writeCPU(0x00F4, a);
    SUB_0038A1();
    return;
}

void game::SUB_0038A1() {
    popAddress();
}

void game::SUB_0038A2() {
    myMapper->writeCPU(0x400E, a);
    popAddress();
}

void game::SUB_0038A6() {
    myMapper->writeCPU(0x06E0, 0x00);
    flgC = false;
    a = myMapper->readCPU(0x001B);
    opAND(0x07);
    opADC(0x02);
    myMapper->writeCPU(0x06E1, a);
    a = myMapper->readCPU(0x00F7);
    opAND(0x00);
    opORA(0x80);
    myMapper->writeCPU(0x00F7, a);
    if (!flgZ) {
        SUB_0038E8();
        return;
    }
    SUB_0038BF();
    return;
}

void game::SUB_0038BF() {
    opINC(0x06E0, 1);
    if (myMapper->readCPU(0x06E0) != myMapper->readCPU(0x06E1)) {
        SUB_0038E8();
        return;
    }
    SUB_0038CA();
    return;
}

void game::SUB_0038CA() {
    a = 0x10;
    myMapper->writeCPU(0x4000, a);
    myMapper->writeCPU(0x4004, a);
    myMapper->writeCPU(0x00F7, 0x00);
    a = myMapper->readCPU(0x00F4);
    opAND(0x0F);
    myMapper->writeCPU(0x00F4, a);
    popAddress();
}

void game::SUB_0038DD() {
    pushAddress(0x0038DD);
    SUB_0037A5();
    if (poppedEntry.value != 0x0038DD) return;
    myMapper->writeCPU(0x00F4, 0x80);
    myMapper->writeCPU(0x00F0, 0x02);
    SUB_0038E8();
    return;
}

void game::SUB_0038E8() {
    x = 0xF9;
    y = 0xF6;
    pushAddress(0x0038EC);
    SUB_003683();
    if (poppedEntry.value != 0x0038EC) return;
    a = myMapper->readCPU(0x001B);
    opAND(0x0F);
    myMapper->writeCPU(0x4002, a);
    x = 0xF9;
    y = 0xF6;
    pushAddress(0x0038FA);
    SUB_00368F();
    if (poppedEntry.value != 0x0038FA) return;
    a = myMapper->readCPU(0x001B);
    opLSR_A(2);
    opAND(0x0F);
    myMapper->writeCPU(0x4006, a);
    popAddress();
}

void game::SUB_003907() {
    SUB_0038A6();
    return;
}

void game::SUB_00390A() {
    a = myMapper->readCPU(0x00F6);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0xDF) {
            goto L_00391B;
        }
        a = myMapper->readCPU(0x00F0);
        opAND(0xE0);
        if (flgZ) {
            goto L_00394E;
        }
        pushAddress(0x003918);
        SUB_0037A5();
        if (poppedEntry.value != 0x003918) return;
    }
L_00391B:
    a = myMapper->readCPU(0x00F0);
    opASL_A(1);
    if (flgC) {
        SUB_0038DD();
        return;
    }
    opASL_A(1);
    if (!flgC) {
        opASL_A(1);
        if (flgC) {
            goto L_003965;
        }
        a = myMapper->readCPU(0x00F4);
        opASL_A(1);
        if (flgC) {
            SUB_0038E8();
            return;
        }
        a = myMapper->readCPU(0x00F4);
        opAND(0xE0);
        if (flgZ) {
            if (myMapper->readCPU(0x00F6) == 0xDF) {
                goto L_00394B;
            }
            if (myMapper->readCPU(0x00F6) != 0) {
                goto L_00394E;
            }
            a = myMapper->readCPU(0x00F3);
            opASL_A(1);
            if (flgC) {
                SUB_003907();
                return;
            }
            opASL_A(1);
            if (flgC) {
                goto L_003977;
            }
            a = myMapper->readCPU(0x00F7);
            opASL_A(1);
            if (flgC) {
                goto L_00394F;
            }
            opASL_A(1);
            if (flgC) {
                goto L_003993;
            }
        L_00394B:
            pushAddress(0x00394B);
            SUB_003725();
            if (poppedEntry.value != 0x00394B) return;
        }
    L_00394E:
        popAddress();
        return;
    L_00394F:
        SUB_0038BF();
        return;
    }
    myMapper->writeCPU(0x06FA, 0x0F);
    a = myMapper->readCPU(0x00F4);
    opAND(0x0F);
    opORA(0x40);
    myMapper->writeCPU(0x00F4, a);
    x = 0xD1;
    y = 0xF9;
    setLoadFlag(y);
    if (flgZ) {
    L_003965:
        myMapper->writeCPU(0x00F0, 0x02);
        a = myMapper->readCPU(0x00F4);
        opAND(0x0F);
        opORA(0x20);
        myMapper->writeCPU(0x00F4, a);
        x = 0xCD;
        y = 0xF9;
        setLoadFlag(y);
        if (flgZ) {
        L_003977:
            myMapper->writeCPU(0x06FC, 0x00);
            a = myMapper->readCPU(0x00F7);
            opAND(0x00);
            opORA(0x40);
            myMapper->writeCPU(0x00F7, a);
            x = 0xD5;
            y = 0xF9;
            pushAddress(0x003988);
            SUB_00368F();
            if (poppedEntry.value != 0x003988) return;
            x = 0xD9;
            y = 0xF9;
        }
    }
    pushAddress(0x00398F);
    SUB_003683();
    if (poppedEntry.value != 0x00398F) return;
    popAddress();
    return;
L_003993:
    opINC(0x06FC, 1);
    a = myMapper->readCPU(0x06FC);
    if (a != 0x12) {
        opCMP(a, 0x06);
        if (!flgC) {
            goto L_0039B1;
        }
        a = myMapper->readCPU(0x001B);
        opORA(0x10);
        opAND(0x7F);
        myMapper->writeCPU(0x06FE, a);
        opROL_A(1);
        myMapper->writeCPU(0x06FD, a);
        goto L_0039BD;
    L_0039B1:
        opINC(0x06FD, 2);
        opINC(0x06FE, 2);
    L_0039BD:
        myMapper->writeCPU(0x4006, myMapper->readCPU(0x06FD));
        myMapper->writeCPU(0x4002, myMapper->readCPU(0x06FE));
        popAddress();
        return;
    }
    SUB_0038CA();
    return;
}

void game::SUB_0039E9() {
    a = myMapper->readCPU(0x00F5);
    opAND(0x02);
    if (!flgZ) {
        SUB_003A26();
        return;
    }
    if (myMapper->readCPU(0x00F6) == 0xDF) {
        goto L_0039F9;
    }
    if (myMapper->readCPU(0x00F6) != 0) {
        SUB_003A26();
        return;
    }
L_0039F9:
    myMapper->writeCPU(0x06F9, 0x00);
    a = myMapper->readCPU(0x00F5);
    opAND(0xE0);
    opORA(0x02);
    myMapper->writeCPU(0x00F5, a);
    x = 0xDD;
    y = 0xF9;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_003A7F();
        return;
    }
    SUB_003A0C();
    return;
}

void game::SUB_003A0C() {
    opINC(0x06F9, 1);
    if (myMapper->readCPU(0x06F9) != 0x07) {
        SUB_003A26();
        return;
    }
    myMapper->writeCPU(0x4005, 0x7F);
    myMapper->writeCPU(0x4004, 0x10);
    a = myMapper->readCPU(0x00F5);
    opAND(0xE0);
    myMapper->writeCPU(0x00F5, a);
    SUB_003A26();
    return;
}

void game::SUB_003A26() {
    popAddress();
}

void game::SUB_003A27() {
    pushAddress(0x003A27);
    SUB_0037A5();
    if (poppedEntry.value != 0x003A27) return;
    x = 0xE1;
    y = 0xF9;
    pushAddress(0x003A2E);
    SUB_003683();
    if (poppedEntry.value != 0x003A2E) return;
    x = 0xE5;
    y = 0xF9;
    SUB_003A7F();
    return;
}

void game::SUB_003A38() {
    a = myMapper->readCPU(0x00F6);
    setLoadFlag(a);
    if (!flgZ) {
        opAND(0x0F);
        if (a != 0x0F) {
            goto L_003A63;
        }
    }
    a = myMapper->readCPU(0x00F4);
    opAND(0x80);
    if (flgZ) {
        a = myMapper->readCPU(0x00F7);
        opAND(0xC0);
        if (!flgZ) {
            goto L_003A63;
        }
        a = myMapper->readCPU(0x00F1);
        opLSR_A(1);
        if (flgC) {
            SUB_003A27();
            return;
        }
        opLSR_A(1);
        if (flgC) {
            SUB_0039E9();
            return;
        }
        opLSR_A(1);
        if (flgC) {
            SUB_003A83();
            return;
        }
        opLSR_A(2);
        if (flgC) {
            goto L_003A64;
        }
        a = myMapper->readCPU(0x00F5);
        opLSR_A(2);
        if (flgC) {
            SUB_003A0C();
            return;
        }
    }
    do {
    L_003A63:
        popAddress();
        return;
    L_003A64:
        if (myMapper->readCPU(0x00F6) != 0) {
            goto L_003A63;
        }
        a = myMapper->readCPU(0x00F5);
        opAND(0x02);
    } while (!flgZ);
    x = 0x8A;
    y = 0xFA;
    pushAddress(0x003A72);
    SUB_00368F();
    if (poppedEntry.value != 0x003A72) return;
    a = myMapper->readCPU(0x001B);
    opAND(0x3F);
    opORA(0x10);
    myMapper->writeCPU(0x4006, a);
    popAddress();
}

void game::SUB_003A7F() {
    pushAddress(0x003A7F);
    SUB_00368F();
    if (poppedEntry.value != 0x003A7F) return;
    popAddress();
}

void game::SUB_003A83() {
    y = 0x0A;
    a = 0xEF;
    SUB_003BA5();
    return;
}

void game::SUB_003A96() {
    opINC(0x06F6, 1);
    if (myMapper->readCPU(0x06F6) != 0x04) {
        SUB_003AD8();
        return;
    }
    a = myMapper->readCPU(0x00F5);
    opAND(0x1F);
    myMapper->writeCPU(0x00F5, a);
    x = 0x92;
    y = 0xFA;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_003B00();
        return;
    }
    SUB_003AAC();
    return;
}

void game::SUB_003AAC() {
    a = myMapper->readCPU(0x00F6);
    setLoadFlag(a);
    if (!flgZ) {
        if (a == 0x08) {
            goto L_003ABA;
        }
        opAND(0x0F);
        if (a != 0x0F) {
            SUB_003AD8();
            return;
        }
    }
L_003ABA:
    a = myMapper->readCPU(0x00F4);
    opAND(0x80);
    if (!flgZ) {
        SUB_003AD8();
        return;
    }
    a = myMapper->readCPU(0x00F1);
    opASL_A(1);
    if (flgC) {
        SUB_003B17();
        return;
    }
    opASL_A(1);
    if (flgC) {
        SUB_003AE2();
        return;
    }
    a = myMapper->readCPU(0x00F5);
    opASL_A(2);
    if (flgC) {
        SUB_003A96();
        return;
    }
    a = myMapper->readCPU(0x00F1);
    opAND(0x20);
    if (flgZ) {
        SUB_003AD9();
        return;
    }
    if (myMapper->readCPU(0x00F6) == 0) {
        SUB_003B04();
        return;
    }
    SUB_003AD8();
    return;
}

void game::SUB_003AD8() {
    popAddress();
}

void game::SUB_003AD9() {
    if (myMapper->readCPU(0x00F6) != 0xDF) {
        SUB_003AD8();
        return;
    }
    SUB_00379F();
    return;
}

void game::SUB_003AE2() {
    a = myMapper->readCPU(0x00F5);
    opAND(0x1F);
    opORA(0x40);
    myMapper->writeCPU(0x00F5, a);
    a = 0x00;
    myMapper->writeCPU(0x4008, a);
    myMapper->writeCPU(0x00F6, a);
    myMapper->writeCPU(0x06F6, a);
    a = 0x10;
    myMapper->writeCPU(0x4004, a);
    myMapper->writeCPU(0x400C, a);
    x = 0x8E;
    y = 0xFA;
    SUB_003B00();
    return;
}

void game::SUB_003B00() {
    pushAddress(0x003B00);
    SUB_003687();
    if (poppedEntry.value != 0x003B00) return;
    popAddress();
}

void game::SUB_003B04() {
    a = myMapper->readCPU(0x06E9);
    opAND(0x20);
    if (!flgZ) {
        goto L_003B10;
    }
    myMapper->writeCPU(0x06F5, 0x02);
L_003B10:
    y = 0x08;
    a = 0xDF;
    SUB_003BA5();
    return;
}

void game::SUB_003B17() {
    y = 0x04;
    a = 0x7F;
    SUB_003BA5();
    return;
}

void game::SUB_003B1E() {
    y = 0x00;
    a = 0x02;
    SUB_003BC1();
    return;
}

void game::SUB_003B25() {
    if (myMapper->readCPU(0x06E8) != 0) {
        SUB_003B5E();
        return;
    }
    a = myMapper->readCPU(0x00F2);
    opLSR_A(1);
    if (flgC) {
        SUB_003B82();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B1E();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B4C();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B7C();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B69();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B5E();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B58();
        return;
    }
    opLSR_A(1);
    if (flgC) {
        SUB_003B52();
        return;
    }
    if (myMapper->readCPU(0x00F6) != 0) {
        SUB_003B49();
        return;
    }
    popAddress();
}

void game::SUB_003B49() {
    SUB_003504();
    return;
}

void game::SUB_003B4C() {
    y = 0x02;
    a = 0x04;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003BA5();
        return;
    }
    SUB_003B52();
    return;
}

void game::SUB_003B52() {
    y = 0x09;
    a = 0x80;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003B6D();
        return;
    }
    SUB_003B58();
    return;
}

void game::SUB_003B58() {
    y = 0x07;
    a = 0x40;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003B6D();
        return;
    }
    SUB_003B5E();
    return;
}

void game::SUB_003B5E() {
    myMapper->writeCPU(0x06E8, 0x00);
    y = 0x06;
    a = 0x20;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003BC1();
        return;
    }
    SUB_003B69();
    return;
}

void game::SUB_003B69() {
    y = 0x05;
    a = 0x10;
    SUB_003B6D();
    return;
}

void game::SUB_003B6D() {
    pushAddress(0x003B6D);
    SUB_0036A8();
    if (poppedEntry.value != 0x003B6D) return;
    x = 0xFC;
    y = 0xFC;
    pushAddress(0x003B74);
    SUB_003712();
    if (poppedEntry.value != 0x003B74) return;
    opINC(0x06F0, 1);
    if (!flgZ) {
        SUB_003B49();
        return;
    }
    SUB_003B7C();
    return;
}

void game::SUB_003B7C() {
    y = 0x03;
    a = 0x08;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003B86();
        return;
    }
    SUB_003B82();
    return;
}

void game::SUB_003B82() {
    y = 0x01;
    a = 0x01;
    SUB_003B86();
    return;
}

void game::SUB_003B86() {
    pushAddress(0x003B86);
    SUB_0036A8();
    if (poppedEntry.value != 0x003B86) return;
    x = 0x80;
    y = 0x80;
    SUB_003B8D();
    return;
}

void game::SUB_003B8D() {
    pushAddress(0x003B8D);
    SUB_00371A();
    if (poppedEntry.value != 0x003B8D) return;
    myMapper->writeCPU(0x4001, 0x83);
    a = 0x7F;
    setLoadFlag(a);
    myMapper->writeCPU(0x4005, a);
    if (!flgZ) {
        SUB_003BAF();
        return;
    }
    pushAddress(0x003B9C);
    SUB_0036A8();
    if (poppedEntry.value != 0x003B9C) return;
    x = 0x04;
    y = 0x04;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_003BAC();
        return;
    }
    SUB_003BA5();
    return;
}

void game::SUB_003BA5() {
    pushAddress(0x003BA5);
    SUB_0036A8();
    if (poppedEntry.value != 0x003BA5) return;
    x = 0x80;
    y = 0x80;
    SUB_003BAC();
    return;
}

void game::SUB_003BAC() {
    pushAddress(0x003BAC);
    SUB_003712();
    if (poppedEntry.value != 0x003BAC) return;
    SUB_003BAF();
    return;
}

void game::SUB_003BAF() {
    myMapper->writeCPU(0x06F0, 0x00);
    a = myMapper->readCPU(0x00F4);
    opAND(0x20);
    if (flgZ) {
        SUB_003B49();
        return;
    }
    a = 0xD5;
    setLoadFlag(a);
    myMapper->writeCPU(0x4001, a);
    if (!flgZ) {
        SUB_003B49();
        return;
    }
    SUB_003BC1();
    return;
}

void game::SUB_003BC1() {
    pushAddress(0x003BC1);
    SUB_0036A8();
    if (poppedEntry.value != 0x003BC1) return;
    x = 0x80;
    y = 0xBA;
    setLoadFlag(y);
    if (!flgZ) {
        SUB_003B8D();
        return;
    }
    //NOP
    SUB_003FF7();
    return;
}

void game::SUB_003FF7() {
    SUB_003758();
    return;
}

void game::indirectJump(Uint16 target) {
    switch (target) {
    case 0xC3BF:
        SUB_0003BF();
        break;
    case 0xC3ED:
        SUB_0003ED();
        break;
    case 0xC434:
        SUB_000434();
        break;
    case 0xC454:
        SUB_000454();
        break;
    case 0xC455:
        SUB_000455();
        break;
    default:
        bool test = false;
        Uint16 tmp = target;
    }
}
