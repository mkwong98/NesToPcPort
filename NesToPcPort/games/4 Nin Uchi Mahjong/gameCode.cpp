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
    SUB_003E74_B();
}


void game::reset() {
    needWaitScanline = false;

    flgD = false;
    flgI = true;
    a = 0x00;
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x4010, a);
    myMapper->writeCPU(0x4017, 0x40);
    goto L_000041;
L_000041:
    x = 0xFF;
    s = x;
    do {
        a = 0x00;
        pushAddress(0x000046);
        SUB_0037DA();
        if (poppedEntry.value != 0x000046) return;
    } while (!(myMapper->readCPU(0x2002) & 0x80));
    x = 0x00;
    //do {
    //    opINX(1);
    //} while (!(myMapper->readCPU(0x2002) & 0x80));
    flgI = false;
    pushAddress(0x000057);
    SUB_00397F();
    if (poppedEntry.value != 0x000057) return;
    myMapper->writeCPU(0x001E, myMapper->readCPU(0x2007));
    pushAddress(0x00005F);
    SUB_000F43();
    if (poppedEntry.value != 0x00005F) return;
    SUB_000062();
    return;
}

void game::SUB_000062() {
    a = 0xFF;
    myMapper->writeCPU(0x0012, a);
    myMapper->writeCPU(0x0095, a);
    SUB_000068();
    return;
}

void game::SUB_000068() {
    pushAddress(0x000068);
    SUB_000F79();
    if (poppedEntry.value != 0x000068) return;
    SUB_00006B();
    return;
}

void game::SUB_00006B() {
    while (true) {
        while (true) {
            while (true) {
            L_00006B:
                x = 0xFF;
                s = x;
                pushAddress(0x00006E);
                SUB_001305();
                if (poppedEntry.value != 0x00006E) return;
                if (!flgC) {
                    SUB_000068();
                    return;
                }
                pushAddress(0x000073);
                SUB_00342E();
                if (poppedEntry.value != 0x000073) return;
                pushAddress(0x000076);
                SUB_000FC0();
                if (poppedEntry.value != 0x000076) return;
                pushAddress(0x000079);
                SUB_00342E();
                if (poppedEntry.value != 0x000079) return;
                pushAddress(0x00007C);
                SUB_00107E();
                if (poppedEntry.value != 0x00007C) return;
                x = 0x02;
                y = 0xCE;
                pushAddress(0x000083);
                SUB_00379B();
                if (poppedEntry.value != 0x000083) return;
                a = 0x00;
                myMapper->writeCPU(0x0003, a);
                myMapper->writeCPU(0x001C, a);
                pushAddress(0x00008C);
                SUB_0010F0();
                if (poppedEntry.value != 0x00008C) return;
                while (true) {
                    pushAddress(0x00008F);
                    SUB_00053F();
                    if (poppedEntry.value != 0x00008F) return;
                    a = myMapper->readCPU(0x0039);
                    pushAddress(0x000094);
                    SUB_00346A();
                    if (poppedEntry.value != 0x000094) return;
                    myMapper->writeCPU(0x003E, myMapper->readCPU(0x000F));
                    myMapper->writeCPU(0x003F, myMapper->readCPU(0x0010));
                    if (myMapper->readCPU(0x0012) == 0) {
                        if (myMapper->readCPU(0x0039) == 0) {
                            goto L_0000AF;
                        }
                    }
                    pushAddress(0x0000A7);
                    SUB_00059D();
                    if (poppedEntry.value != 0x0000A7) return;
                    if (!flgC) {
                        goto L_0001DD;
                    L_0000AF:
                        pushAddress(0x0000AF);
                        SUB_00092B();
                        if (poppedEntry.value != 0x0000AF) return;
                        if (!flgC) {
                            goto L_0001DD;
                        }
                    }
                    pushAddress(0x0000B7);
                    SUB_0004F0();
                    if (poppedEntry.value != 0x0000B7) return;
                    if (!flgC) {
                        goto L_00010D;
                    }
                    pushAddress(0x0000BC);
                    SUB_002205();
                    if (poppedEntry.value != 0x0000BC) return;
                    pushAddress(0x0000BF);
                    SUB_001B50();
                    if (poppedEntry.value != 0x0000BF) return;
                    if (!flgC) {
                        goto L_0001DD;
                    }
                    pushAddress(0x0000C7);
                    SUB_000B52();
                    if (poppedEntry.value != 0x0000C7) return;
                    if (!flgC) {
                        goto L_00010D;
                    }
                    while (myMapper->readCPU(0x0047) != 0) {
                        pushAddress(0x0000D0);
                        SUB_001FD3();
                        if (poppedEntry.value != 0x0000D0) return;
                        if (!flgC) {
                            goto L_0001DD;
                        }
                        if (myMapper->readCPU(0x0072) != 0) {
                            goto L_00010B;
                        }
                        pushAddress(0x0000DC);
                        SUB_002205();
                        if (poppedEntry.value != 0x0000DC) return;
                        pushAddress(0x0000DF);
                        SUB_001B50();
                        if (poppedEntry.value != 0x0000DF) return;
                        if (flgC) {
                            goto L_0000E7;
                        }
                        goto L_0001DD;
                    L_0000E7:
                        pushAddress(0x0000E7);
                        SUB_002184();
                        if (poppedEntry.value != 0x0000E7) return;
                    }
                    a = myMapper->readCPU(0x0044);
                    pushAddress(0x0000EF);
                    SUB_000C3E();
                    if (poppedEntry.value != 0x0000EF) return;
                    if (myMapper->readCPU(0x0072) != 0) {
                        goto L_00010B;
                    }
                    if (myMapper->readCPU(0x0034) != 0) {
                        goto L_0000FE;
                    }
                    a = 0x02;
                    setLoadFlag(a);
                    if (!flgZ) {
                        goto L_00010D;
                    }
                L_0000FE:
                    opINC(0x0039, 1);
                    a = myMapper->readCPU(0x0039);
                    opAND(0x03);
                    myMapper->writeCPU(0x0039, a);
                    opINC(0x003D, 1);
                }
            L_00010B:
                a = 0x07;
                while (true) {
                    while (true) {
                        while (true) {
                        L_00010D:
                            myMapper->writeCPU(0x005E, a);
                            pushAddress(0x00010F);
                            SUB_0003C9();
                            if (poppedEntry.value != 0x00010F) return;
                            if (myMapper->readCPU(0x005E) == 0x06) {
                                y = 0x40;
                                a = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
                                flgC = false;
                                opADC(0x04);
                                myMapper->writeCPU(0x000B, a);
                                myMapper->writeCPU(0x000A, 0x1A);
                                a = 0x38;
                                pushAddress(0x000127);
                                SUB_003BDE();
                                if (poppedEntry.value != 0x000127) return;
                                opDEC(0x000A, 1);
                                a = myMapper->readCPU(0x0060);
                                pushAddress(0x00012E);
                                SUB_003BDE();
                                if (poppedEntry.value != 0x00012E) return;
                            }
                            myMapper->writeCPU(0x0067, 0x00);
                            pushAddress(0x000135);
                            SUB_00326F();
                            if (poppedEntry.value != 0x000135) return;
                            a = myMapper->readCPU(0x005E);
                            opCMP(a, 0x03);
                            if (!flgZ) {
                                opCMP(a, 0x02);
                                if (!flgZ) {
                                    goto L_0001A4;
                                }
                                pushAddress(0x000145);
                                SUB_002F04();
                                if (poppedEntry.value != 0x000145) return;
                                if (!flgC) {
                                    goto L_00027D;
                                }
                                x = 0x03;
                                y = 0x14;
                                pushAddress(0x000151);
                                SUB_00043E();
                                if (poppedEntry.value != 0x000151) return;
                                x = 0x03;
                                y = 0x5A;
                                pushAddress(0x000158);
                                SUB_00043E();
                                if (poppedEntry.value != 0x000158) return;
                                x = 0x03;
                                y = 0xA0;
                                pushAddress(0x00015F);
                                SUB_00043E();
                                if (poppedEntry.value != 0x00015F) return;
                                x = 0x02;
                                y = 0xCE;
                                pushAddress(0x000166);
                                SUB_00043E();
                                if (poppedEntry.value != 0x000166) return;
                                a = myMapper->readCPU(0x0067);
                                setLoadFlag(a);
                                if (flgZ) {
                                    goto L_0001A4;
                                }
                                if (!flgZ) {
                                    goto L_000173;
                                }
                            }
                            myMapper->writeCPU(0x0067, 0x04);
                        L_000173:
                            pushAddress(0x000173);
                            SUB_000522();
                            if (poppedEntry.value != 0x000173) return;
                            pushAddress(0x000176);
                            SUB_001AFB();
                            if (poppedEntry.value != 0x000176) return;
                            pushAddress(0x000179);
                            SUB_001643();
                            if (poppedEntry.value != 0x000179) return;
                            x = 0x03;
                            y = 0x14;
                            pushAddress(0x000180);
                            SUB_000467();
                            if (poppedEntry.value != 0x000180) return;
                            x = 0x03;
                            y = 0x5A;
                            pushAddress(0x000187);
                            SUB_000467();
                            if (poppedEntry.value != 0x000187) return;
                            x = 0x03;
                            y = 0xA0;
                            pushAddress(0x00018E);
                            SUB_000467();
                            if (poppedEntry.value != 0x00018E) return;
                            x = 0x02;
                            y = 0xCE;
                            pushAddress(0x000195);
                            SUB_000467();
                            if (poppedEntry.value != 0x000195) return;
                            if (myMapper->readCPU(0x0012) == 0) {
                                a = 0x00;
                                pushAddress(0x00019E);
                                SUB_001B0F();
                                if (poppedEntry.value != 0x00019E) return;
                                goto L_0001A7;
                            }
                        L_0001A4:
                            pushAddress(0x0001A4);
                            SUB_000522();
                            if (poppedEntry.value != 0x0001A4) return;
                        L_0001A7:
                            opINC(0x003B, 1);
                            a = myMapper->readCPU(0x0037);
                            opAND(0x04);
                            if (flgZ) {
                                if (myMapper->readCPU(0x0067) == 0) {
                                    goto L_0001DA;
                                }
                                if (myMapper->readCPU(0x003D) == 0) {
                                }
                                else {
                                    a = myMapper->readCPU(0x0036);
                                    pushAddress(0x0001BC);
                                    SUB_00346A();
                                    if (poppedEntry.value != 0x0001BC) return;
                                    y = 0x38;
                                    if (myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y) == 0) {
                                        opINC(0x0036, 1);
                                        a = myMapper->readCPU(0x0036);
                                        opAND(0x03);
                                        myMapper->writeCPU(0x0036, a);
                                        x = myMapper->readCPU(0x0037);
                                        opINX(1);
                                        a = x;
                                        opAND(0x07);
                                        if (!flgZ) {
                                            goto L_0001D8;
                                        }
                                        SUB_000062();
                                        return;
                                    L_0001D8:
                                        myMapper->writeCPU(0x0037, a);
                                    }
                                }
                            }
                        L_0001DA:
                            goto L_00006B;
                        L_0001DD:
                            if (a != 0x07) {
                                goto L_0001E4;
                            }
                        }
                    L_0001E4:
                        if (a != 0x05) {
                            goto L_0001EB;
                        }
                    }
                L_0001EB:
                    myMapper->writeCPU(0x005E, a);
                    a = myMapper->readCPU(0x002D);
                    setLoadFlag(a);
                    if (flgZ) {
                        goto L_0001F4;
                    }
                }
            L_0001F4:
                pushAddress(0x0001F4);
                SUB_0003C9();
                if (poppedEntry.value != 0x0001F4) return;
                if (myMapper->readCPU(0x0061) == 0) {
                    goto L_000220;
                }
                myMapper->writeCPU(0x00A2, myMapper->readCPU(0x003E));
                myMapper->writeCPU(0x00A3, myMapper->readCPU(0x003F));
                x = 0xC3;
                y = 0xAD;
                pushAddress(0x000207);
                SUB_000429();
                if (poppedEntry.value != 0x000207) return;
                a = myMapper->readCPU(0x0040);
                myMapper->writeCPU(0x00A2, a);
                myMapper->writeCPU(0x0042, a);
                a = myMapper->readCPU(0x0041);
                myMapper->writeCPU(0x00A3, a);
                myMapper->writeCPU(0x0043, a);
                x = 0xC3;
                y = 0xB2;
                pushAddress(0x00021A);
                SUB_000429();
                if (poppedEntry.value != 0x00021A) return;
                goto L_000233;
            L_000220:
                a = myMapper->readCPU(0x003E);
                myMapper->writeCPU(0x00A2, a);
                myMapper->writeCPU(0x0042, a);
                a = myMapper->readCPU(0x003F);
                myMapper->writeCPU(0x00A3, a);
                myMapper->writeCPU(0x0043, a);
                x = 0xC3;
                y = 0xB6;
                pushAddress(0x000230);
                SUB_000429();
                if (poppedEntry.value != 0x000230) return;
            L_000233:
                y = 0x39;
                a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
                pushAddress(0x000237);
                SUB_0010E2();
                if (poppedEntry.value != 0x000237) return;
                a = myMapper->readCPU(0x000B);
                flgC = false;
                opADC(0x04);
                myMapper->writeCPU(0x000B, a);
                a = 0x38;
                pushAddress(0x000243);
                SUB_003BDE();
                if (poppedEntry.value != 0x000243) return;
                opDEC(0x000A, 1);
                a = myMapper->readCPU(0x0060);
                pushAddress(0x00024A);
                SUB_003BDE();
                if (poppedEntry.value != 0x00024A) return;
                pushAddress(0x00024D);
                SUB_00324B();
                if (poppedEntry.value != 0x00024D) return;
                pushAddress(0x000250);
                SUB_000522();
                if (poppedEntry.value != 0x000250) return;
                pushAddress(0x000253);
                SUB_001593();
                if (poppedEntry.value != 0x000253) return;
                myMapper->writeCPU(0x003C, 0x00);
                if (myMapper->readCPU(0x023F) != 0) {
                    goto L_000264;
                }
                opINC(0x003B, 1);
            }
        L_000264:
            myMapper->writeCPU(0x003B, 0x00);
            opINC(0x0036, 1);
            a = myMapper->readCPU(0x0036);
            opAND(0x03);
            myMapper->writeCPU(0x0036, a);
            x = myMapper->readCPU(0x0037);
            opINX(1);
            a = x;
            opAND(0x07);
            if (flgZ) {
                goto L_0002C6;
            }
            myMapper->writeCPU(0x0037, a);
        }
    L_00027D:
        myMapper->writeCPU(0x005E, a);
        pushAddress(0x00027F);
        SUB_0003C9();
        if (poppedEntry.value != 0x00027F) return;
        pushAddress(0x000282);
        SUB_00324B();
        if (poppedEntry.value != 0x000282) return;
        a = myMapper->readCPU(0x003E);
        myMapper->writeCPU(0x0042, a);
        myMapper->writeCPU(0x000F, a);
        myMapper->writeCPU(0x00A2, a);
        a = myMapper->readCPU(0x003F);
        myMapper->writeCPU(0x0043, a);
        myMapper->writeCPU(0x0010, a);
        myMapper->writeCPU(0x00A3, a);
        pushAddress(0x000295);
        SUB_00370F();
        if (poppedEntry.value != 0x000295) return;
        x = 0xC3;
        y = 0xBA;
        pushAddress(0x00029C);
        SUB_000429();
        if (poppedEntry.value != 0x00029C) return;
        pushAddress(0x00029F);
        SUB_000522();
        if (poppedEntry.value != 0x00029F) return;
        pushAddress(0x0002A2);
        SUB_001AFB();
        if (poppedEntry.value != 0x0002A2) return;
        pushAddress(0x0002A5);
        SUB_001643();
        if (poppedEntry.value != 0x0002A5) return;
        myMapper->writeCPU(0x0003, 0xFF);
        a = myMapper->readCPU(0x003C);
        opPHA();
        a = myMapper->readCPU(0x003B);
        opPHA();
        a = 0x00;
        myMapper->writeCPU(0x003C, a);
        myMapper->writeCPU(0x003B, a);
        pushAddress(0x0002B8);
        SUB_0015F6();
        if (poppedEntry.value != 0x0002B8) return;
        opPLA();
        x = a;
        opINX(1);
        myMapper->writeCPU(0x003B, x);
        opPLA();
        myMapper->writeCPU(0x003C, a);
    }
L_0002C6:
    pushAddress(0x0002C6);
    SUB_0039DC();
    if (poppedEntry.value != 0x0002C6) return;
    myMapper->writeCPU(0x0003, 0xFF);
    myMapper->writeCPU(0x0039, myMapper->readCPU(0x0036));
    a = 0x00;
    myMapper->writeCPU(0x009A, a);
    myMapper->writeCPU(0x0099, a);
    x = 0x04;
    do {
        a = myMapper->readCPU(0x0039);
        pushAddress(0x0002DB);
        SUB_00346A();
        if (poppedEntry.value != 0x0002DB) return;
        y = 0x43;
        myMapper->writeCPU(0x0097, myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y));
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (!flgN) {
            myMapper->writeCPU(0x0098, a);
            a = myMapper->readCPU(0x009A);
            flgC = true;
            opSBC(myMapper->readCPU(0x0098));
            if (!flgC) {
                if (!flgZ) {
                    goto L_0002FB;
                }
                a = myMapper->readCPU(0x0099);
                flgC = true;
                opSBC(myMapper->readCPU(0x0097));
                if (flgC) {
                    goto L_00030B;
                }
            L_0002FB:
                myMapper->writeCPU(0x009A, myMapper->readCPU(0x0098));
                myMapper->writeCPU(0x0099, myMapper->readCPU(0x0097));
                myMapper->writeCPU(0x0042, myMapper->readCPU(0x000F));
                myMapper->writeCPU(0x0043, myMapper->readCPU(0x0010));
            }
        }
    L_00030B:
        opINC(0x0039, 1);
        a = myMapper->readCPU(0x0039);
        opAND(0x03);
        myMapper->writeCPU(0x0039, a);
        opDEX(1);
    } while (!flgZ);
    a = 0x00;
    myMapper->writeCPU(0x0061, a);
    myMapper->writeCPU(0x003C, a);
    a = 0x00;
    myMapper->writeCPU(0x0056, a);
    myMapper->writeCPU(0x0057, a);
    myMapper->writeCPU(0x0058, a);
    myMapper->writeCPU(0x0059, a);
    myMapper->writeCPU(0x0054, 0xB0);
    myMapper->writeCPU(0x0055, 0x04);
    x = 0x03;
    y = 0x14;
    myMapper->writeCPU(0x000B, 0x08);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x00033A);
    SUB_001665();
    if (poppedEntry.value != 0x00033A) return;
    pushAddress(0x00033D);
    SUB_00038B();
    if (poppedEntry.value != 0x00033D) return;
    x = 0x03;
    y = 0x5A;
    myMapper->writeCPU(0x000B, 0x0C);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x00034C);
    SUB_001665();
    if (poppedEntry.value != 0x00034C) return;
    pushAddress(0x00034F);
    SUB_00038B();
    if (poppedEntry.value != 0x00034F) return;
    x = 0x03;
    y = 0xA0;
    myMapper->writeCPU(0x000B, 0x10);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x00035E);
    SUB_001665();
    if (poppedEntry.value != 0x00035E) return;
    pushAddress(0x000361);
    SUB_00038B();
    if (poppedEntry.value != 0x000361) return;
    x = 0x02;
    y = 0xCE;
    myMapper->writeCPU(0x000B, 0x14);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x000370);
    SUB_001665();
    if (poppedEntry.value != 0x000370) return;
    pushAddress(0x000373);
    SUB_00038B();
    if (poppedEntry.value != 0x000373) return;
    myMapper->writeCPU(0x000B, 0x04);
    myMapper->writeCPU(0x000A, 0x08);
    x = 0xC3;
    y = 0xA6;
    pushAddress(0x000382);
    SUB_003B5D();
    if (poppedEntry.value != 0x000382) return;
    pushAddress(0x000385);
    SUB_000522();
    if (poppedEntry.value != 0x000385) return;
    SUB_000062();
    return;
}

void game::SUB_00038B() {
    opDEC(0x000B, 1);
    myMapper->writeCPU(0x000A, 0x0F);
    pushAddress(0x000391);
    SUB_0038BB();
    if (poppedEntry.value != 0x000391) return;
    a = myMapper->readCPU(0x0097);
    flgC = true;
    opSBC(0xB8);
    myMapper->writeCPU(0x0097, a);
    a = myMapper->readCPU(0x0098);
    opSBC(0x0B);
    myMapper->writeCPU(0x0098, a);
    opINC(0x000B, 1);
    SUB_0038BB();
    return;
}

void game::SUB_0003C9() {
    myMapper->writeCPU(0x000B, 0x00);
    myMapper->writeCPU(0x000A, 0x10);
    a = myMapper->readCPU(0x02C5);
    pushAddress(0x0003D4);
    SUB_003BDE();
    if (poppedEntry.value != 0x0003D4) return;
    a = myMapper->readCPU(0x0070);
    flgC = false;
    opADC(myMapper->readCPU(0x003C));
    myMapper->writeCPU(0x003C, a);
    myMapper->writeCPU(0x0070, 0x00);
    a = myMapper->readCPU(0x005E);
    flgC = false;
    opADC(0x43);
    pushAddress(0x0003E7);
    SUB_003089();
    if (poppedEntry.value != 0x0003E7) return;
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, 0x00);
    pushAddress(0x0003F0);
    SUB_003B5D();
    if (poppedEntry.value != 0x0003F0) return;
    myMapper->writeCPU(0x000B, 0x06);
    myMapper->writeCPU(0x000A, 0x00);
    x = 0x03;
    y = 0x14;
    pushAddress(0x0003FF);
    SUB_00379B();
    if (poppedEntry.value != 0x0003FF) return;
    pushAddress(0x000402);
    SUB_003B49();
    if (poppedEntry.value != 0x000402) return;
    myMapper->writeCPU(0x000B, 0x0C);
    myMapper->writeCPU(0x000A, 0x00);
    x = 0x03;
    y = 0x5A;
    pushAddress(0x000411);
    SUB_00379B();
    if (poppedEntry.value != 0x000411) return;
    pushAddress(0x000414);
    SUB_003B49();
    if (poppedEntry.value != 0x000414) return;
    myMapper->writeCPU(0x000B, 0x12);
    myMapper->writeCPU(0x000A, 0x00);
    x = 0x03;
    y = 0xA0;
    pushAddress(0x000423);
    SUB_00379B();
    if (poppedEntry.value != 0x000423) return;
    SUB_003B49();
    return;
}

void game::SUB_000429() {
    a = y;
    opPHA();
    y = 0x40;
    myMapper->writeCPU(0x000B, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    opINC(0x000B, 2);
    a = 0x04;
    myMapper->writeCPU(0x000A, a);
    opPLA();
    y = a;
    SUB_003CBE();
    return;
}

void game::SUB_00043E() {
    myMapper->writeCPU(0x00A3, x);
    myMapper->writeCPU(0x00A2, y);
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0x38;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
        goto L_00045E;
    }
    pushAddress(0x00044C);
    SUB_00370F();
    if (poppedEntry.value != 0x00044C) return;
    pushAddress(0x00044F);
    SUB_000E6E();
    if (poppedEntry.value != 0x00044F) return;
    x = 0xC3;
    y = 0xC4;
    if (flgC) {
        SUB_000429();
        return;
    }
    y = 0x38;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, 0x01);
L_00045E:
    opINC(0x0067, 1);
    x = 0xC3;
    y = 0xBF;
    SUB_000429();
    return;
}

void game::SUB_000467() {
    myMapper->writeCPU(0x00A2, y);
    myMapper->writeCPU(0x000F, y);
    myMapper->writeCPU(0x00A3, x);
    myMapper->writeCPU(0x0010, x);
    pushAddress(0x00046F);
    SUB_00370F();
    if (poppedEntry.value != 0x00046F) return;
    myMapper->writeCPU(0x000B, myMapper->readCPU(0x0240));
    myMapper->writeCPU(0x000A, 0x00);
    a = myMapper->readCPU(0x023F);
    opORA(0xE0);
    pushAddress(0x000480);
    SUB_003C68();
    if (poppedEntry.value != 0x000480) return;
    a = 0x6A;
    pushAddress(0x000485);
    SUB_003C68();
    if (poppedEntry.value != 0x000485) return;
    opINC(0x000B, 1);
    pushAddress(0x00048A);
    SUB_003945();
    if (poppedEntry.value != 0x00048A) return;
    opINC(0x000A, 1);
    x = myMapper->readCPU(0x0067);
    if (x != 0x04) {
        opDEX(1);
        a = x;
        opASL_A(2);
        x = a;
        if (myMapper->readCPU(0x0238) != 0) {
            opINX(2);
        }
        myMapper->writeCPU(0x0097, myMapper->readCPU(0xC4E4 + x));
        opINX(1);
        myMapper->writeCPU(0x0098, myMapper->readCPU(0xC4E4 + x));
        pushAddress(0x0004AC);
        SUB_0038BB();
        if (poppedEntry.value != 0x0004AC) return;
        pushAddress(0x0004AF);
        SUB_003966();
        if (poppedEntry.value != 0x0004AF) return;
    }
    opINC(0x000B, 1);
    myMapper->writeCPU(0x000A, 0x00);
    if (myMapper->readCPU(0x0238) == 0) {
        goto L_0004CE;
    }
    pushAddress(0x0004BD);
    SUB_000E7C();
    if (poppedEntry.value != 0x0004BD) return;
    x = 0xD6;
    y = 0x40;
    pushAddress(0x0004C4);
    SUB_003B5D();
    if (poppedEntry.value != 0x0004C4) return;
    x = 0x04;
    y = 0x71;
    pushAddress(0x0004CB);
    SUB_003B49();
    if (poppedEntry.value != 0x0004CB) return;
L_0004CE:
    opINC(0x000B, 2);
    myMapper->writeCPU(0x000A, 0x00);
    y = myMapper->readCPU(0x00A2);
    x = myMapper->readCPU(0x00A3);
    pushAddress(0x0004DA);
    SUB_003B49();
    if (poppedEntry.value != 0x0004DA) return;
    opINC(0x000A, 2);
    SUB_001AE4();
    return;
}

void game::SUB_0004F0() {
    a = myMapper->readCPU(0x003D);
    if (a == 0x03) {
        a = myMapper->readCPU(0x0044);
        if (a >= 0x30) {
            if (a >= 0x35) {
                goto L_000520;
            }
            a = myMapper->readCPU(0x0328);
            if (a == myMapper->readCPU(0x0044)) {
                a = myMapper->readCPU(0x036E);
                if (a == myMapper->readCPU(0x0044)) {
                    a = myMapper->readCPU(0x03B4);
                    if (a == myMapper->readCPU(0x0044)) {
                        a = myMapper->readCPU(0x02E2);
                        if (a != myMapper->readCPU(0x0044)) {
                            goto L_000520;
                        }
                        a = 0x04;
                        flgC = false;
                        popAddress();
                        return;
                    }
                }
            }
        }
    }
L_000520:
    flgC = true;
    popAddress();
}

void game::SUB_000522() {
    if (myMapper->readCPU(0x0012) == 0) {
        goto L_00052E;
    }
    a = 0x04;
    pushAddress(0x000528);
    SUB_001262();
    if (poppedEntry.value != 0x000528) return;
    SUB_000538();
    return;
L_00052E:
    if (myMapper->readCPU(0x001A) != 0) {
        wait();
        goto L_00052E;
    }
	bool firstLoop = true;
    do {
        if (firstLoop) firstLoop = false;
		else wait();
        opINC(0x001E, 1);
    } while (myMapper->readCPU(0x001A) == 0);
    SUB_000538();
    return;
}

void game::SUB_000538() {
	bool firstLoop = true;
    do {
        if (firstLoop) firstLoop = false;
        else wait();
        opINC(0x001E, 1);
        a = myMapper->readCPU(0x0019);
        setLoadFlag(a);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00053F() {
    if (myMapper->readCPU(0x0012) != 0) {
        goto L_00056F;
    }
    if (myMapper->readCPU(0x001C) == 0) {
        goto L_00056F;
    }
    a = myMapper->readCPU(0x0095);
    opEOR(0xFF);
    myMapper->writeCPU(0x0095, a);
    pushAddress(0x00054D);
    SUB_000538();
    if (poppedEntry.value != 0x00054D) return;
    opINC(0x001C, 1);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x03;
    y = 0x14;
    pushAddress(0x00055A);
    SUB_000570();
    if (poppedEntry.value != 0x00055A) return;
    x = 0x03;
    y = 0x5A;
    pushAddress(0x000561);
    SUB_000570();
    if (poppedEntry.value != 0x000561) return;
    x = 0x03;
    y = 0xA0;
    pushAddress(0x000568);
    SUB_000570();
    if (poppedEntry.value != 0x000568) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
L_00056F:
    popAddress();
}

void game::SUB_000570() {
    myMapper->writeCPU(0x000E, x);
    myMapper->writeCPU(0x000D, y);
    pushAddress(0x000574);
    SUB_00379B();
    if (poppedEntry.value != 0x000574) return;
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x000A, 0x00);
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_000596;
    }
    y = 0x39;
    x = myMapper->readCPU(myMapper->readCPU(0x000D) + (myMapper->readCPU((0x000D + 1) & 0x00ff) << 8) + y);
    do {
        a = 0x39;
        pushAddress(0x00058F);
        SUB_003BDE();
        if (poppedEntry.value != 0x00058F) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
    return;
L_000596:
    y = myMapper->readCPU(0x000D);
    x = myMapper->readCPU(0x000E);
    SUB_003B49();
    return;
}

void game::SUB_00059D() {
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x003F));
    pushAddress(0x0005A5);
    SUB_000FA9();
    if (poppedEntry.value != 0x0005A5) return;
    myMapper->writeCPU(0x009C, a);
    y = 0x39;
    a = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
    pushAddress(0x0005AE);
    SUB_0010E2();
    if (poppedEntry.value != 0x0005AE) return;
    a = 0x04;
    flgC = false;
    opADC(myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x000B, a);
    if (myMapper->readCPU(0x0095) == 0) {
        a = 0x39;
    }
    else {
        a = myMapper->readCPU(0x009C);
    }
    pushAddress(0x0005C1);
    SUB_003BDE();
    if (poppedEntry.value != 0x0005C1) return;
    x = myMapper->readCPU(0x003F);
    y = myMapper->readCPU(0x003E);
    a = myMapper->readCPU(0x009C);
    pushAddress(0x0005CA);
    SUB_0036B4();
    if (poppedEntry.value != 0x0005CA) return;
    pushAddress(0x0005CD);
    SUB_000617();
    if (poppedEntry.value != 0x0005CD) return;
    if (!flgC) {
        goto L_0005D7;
    }
    pushAddress(0x0005D2);
    SUB_0005E4();
    if (poppedEntry.value != 0x0005D2) return;
    flgC = true;
    popAddress();
    return;
L_0005D7:
    opPHA();
    y = 0x39;
    y = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
    a = 0xFF;
    myMapper->writeCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y, a);
    opPLA();
    flgC = false;
    popAddress();
}

void game::SUB_0005E4() {
    pushAddress(0x0005E4);
    SUB_000A64();
    if (poppedEntry.value != 0x0005E4) return;
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x000A, 0x00);
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_000607;
    }
    y = 0x39;
    x = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
    do {
        a = 0x39;
        pushAddress(0x0005FF);
        SUB_003BDE();
        if (poppedEntry.value != 0x0005FF) return;
        opDEX(1);
    } while (!flgZ);
    if (flgZ) {
        goto L_000611;
    }
L_000607:
    x = myMapper->readCPU(0x003F);
    y = myMapper->readCPU(0x003E);
    pushAddress(0x00060B);
    SUB_00379B();
    if (poppedEntry.value != 0x00060B) return;
    pushAddress(0x00060E);
    SUB_003B49();
    if (poppedEntry.value != 0x00060E) return;
L_000611:
    a = 0x38;
    pushAddress(0x000613);
    SUB_003BDE();
    if (poppedEntry.value != 0x000613) return;
    popAddress();
}

void game::SUB_000617() {
    while (true) {
        myMapper->writeCPU(0x000F, myMapper->readCPU(0x003E));
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x003F));
        pushAddress(0x00061F);
        SUB_00370F();
        if (poppedEntry.value != 0x00061F) return;
        pushAddress(0x000622);
        SUB_003751();
        if (poppedEntry.value != 0x000622) return;
        pushAddress(0x000625);
        SUB_002211();
        if (poppedEntry.value != 0x000625) return;
        pushAddress(0x000628);
        SUB_002422();
        if (poppedEntry.value != 0x000628) return;
        if (!flgC) {
            pushAddress(0x00062D);
            SUB_001260();
            if (poppedEntry.value != 0x00062D) return;
            a = 0x01;
            flgC = false;
            popAddress();
            return;
        }
        y = 0x3E;
        if (myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y) == 0) {
            pushAddress(0x00063A);
            SUB_00069B();
            if (poppedEntry.value != 0x00063A) return;
            if (!flgC) {
                goto L_000692;
            }
            pushAddress(0x00063F);
            SUB_002BD6();
            if (poppedEntry.value != 0x00063F) return;
            pushAddress(0x000642);
            SUB_000855();
            if (poppedEntry.value != 0x000642) return;
            pushAddress(0x000645);
            SUB_00090C();
            if (poppedEntry.value != 0x000645) return;
            pushAddress(0x000648);
            SUB_0006DB();
            if (poppedEntry.value != 0x000648) return;
            if (myMapper->readCPU(0x0012) != 0) {
                pushAddress(0x00064F);
                SUB_000538();
                if (poppedEntry.value != 0x00064F) return;
            }
            if (myMapper->readCPU(0x004A) >= 0x06) {
                if (myMapper->readCPU(0x0034) < 0x0C) {
                    goto L_00066D;
                }
                if (myMapper->readCPU(0x003D) >= 0x04) {
                    if (myMapper->readCPU(0x004E) >= 0x08) {
                        goto L_00066D;
                    }
                }
                pushAddress(0x00066A);
                SUB_000B23();
                if (poppedEntry.value != 0x00066A) return;
            L_00066D:
                a = myMapper->readCPU(0x004C);
                setLoadFlag(a);
                if (!flgZ) {
                    goto L_000674;
                }
            }
            pushAddress(0x000671);
            SUB_000811();
            if (poppedEntry.value != 0x000671) return;
        L_000674:
            x = myMapper->readCPU(0x003F);
            y = myMapper->readCPU(0x003E);
            pushAddress(0x000678);
            SUB_0036D1();
            if (poppedEntry.value != 0x000678) return;
            flgC = true;
            popAddress();
            return;
        }
        pushAddress(0x00067D);
        SUB_002266();
        if (poppedEntry.value != 0x00067D) return;
        if (flgC) {
            goto L_000687;
        }
        pushAddress(0x000682);
        SUB_00069B();
        if (poppedEntry.value != 0x000682) return;
        if (!flgC) {
            goto L_000692;
        }
    L_000687:
        pushAddress(0x000687);
        SUB_001260();
        if (poppedEntry.value != 0x000687) return;
        y = 0x39;
        a = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0098, a);
        flgC = true;
        popAddress();
        return;
    L_000692:
        opCMP(a, 0xFF);
        if (!flgZ) {
            goto L_000699;
        }
    }
L_000699:
    flgC = false;
    popAddress();
}

void game::SUB_00069B() {
    a = myMapper->readCPU(0x008B);
    setLoadFlag(a);
    if (flgZ) {
        a = myMapper->readCPU(0x007E);
        setLoadFlag(a);
        if (!flgZ) {
            a = myMapper->readCPU(0x007F);
            opAND(0x3F);
            myMapper->writeCPU(0x009C, a);
            if (a < 0x30) {
                x = myMapper->readCPU(0x009C);
                opDEX(1);
                a = x;
                x = myMapper->readCPU(0x003F);
                y = myMapper->readCPU(0x003E);
                pushAddress(0x0006B5);
                SUB_0036D1();
                if (poppedEntry.value != 0x0006B5) return;
                if (!flgC) {
                    goto L_0006D9;
                }
                x = myMapper->readCPU(0x009C);
                opINX(1);
                a = x;
                x = myMapper->readCPU(0x003F);
                y = myMapper->readCPU(0x003E);
                pushAddress(0x0006C2);
                SUB_0036D1();
                if (poppedEntry.value != 0x0006C2) return;
                if (!flgC) {
                    goto L_0006D9;
                }
            }
            myMapper->writeCPU(0x007E, myMapper->readCPU(0x007F));
            pushAddress(0x0006CB);
            SUB_001F76();
            if (poppedEntry.value != 0x0006CB) return;
            pushAddress(0x0006CE);
            SUB_00231D();
            if (poppedEntry.value != 0x0006CE) return;
            if (!flgC) {
                goto L_0006DA;
            }
            a = 0xFF;
            myMapper->writeCPU(0x0098, a);
            flgC = false;
            popAddress();
            return;
        L_0006D9:
            flgC = true;
        }
    }
L_0006DA:
    popAddress();
}

void game::SUB_0006DB() {
    myMapper->writeCPU(0x004A, 0x00);
    x = 0x00;
    do {
        myMapper->writeCPU(0x050F + x, myMapper->readCPU(0x054F + x));
        opINX(1);
    } while (x != 0x40);
    myMapper->writeCPU(0x0033, 0x00);
    a = myMapper->readCPU(0x044E);
    myMapper->writeCPU(0x009C, a);
    myMapper->writeCPU(0x004B, a);
    x = 0x02;
    y = 0x00;
    pushAddress(0x0006FB);
    SUB_003680();
    if (poppedEntry.value != 0x0006FB) return;
    opINC(0x0033, 1);
    if (!flgZ) {
        goto L_00071D;
    }
    while (true) {
        y = myMapper->readCPU(0x0033);
        a = myMapper->readCPU(0x044E + y);
        if (a == 0xFF) {
            goto L_000754;
        }
        opINC(0x0033, 1);
        myMapper->writeCPU(0x009C, a);
        x = 0x00;
        pushAddress(0x000711);
        SUB_0036FC();
        if (poppedEntry.value != 0x000711) return;
        myMapper->writeCPU(0x0200 + y, myMapper->readCPU(0x004B));
        myMapper->writeCPU(0x004B, myMapper->readCPU(0x009C));
    L_00071D:
        a = myMapper->readCPU(0x0033);
        opPHA();
        a = myMapper->readCPU(0x009C);
        opPHA();
        pushAddress(0x000723);
        SUB_000CF8();
        if (poppedEntry.value != 0x000723) return;
        opPLA();
        myMapper->writeCPU(0x009C, a);
        opPLA();
        myMapper->writeCPU(0x0033, a);
        x = myMapper->readCPU(0x004B);
        a = myMapper->readCPU(0x0066);
        setLoadFlag(a);
        myMapper->writeCPU(0x058F + x, a);
        if (!flgZ) {
            goto L_000738;
        }
        pushAddress(0x000735);
        SUB_0007D9();
        if (poppedEntry.value != 0x000735) return;
    L_000738:
        x = myMapper->readCPU(0x004B);
        a = myMapper->readCPU(0x0066);
        opASL_A(2);
        flgC = false;
        opADC(myMapper->readCPU(0x050F + x));
        myMapper->writeCPU(0x050F + x, a);
        y = myMapper->readCPU(0x004B);
        a = myMapper->readCPU(0x04CF + y);
        flgC = false;
        opADC(myMapper->readCPU(0x050F + x));
        myMapper->writeCPU(0x050F + x, a);
    }
L_000754:
    x = 0x02;
    y = 0x00;
    a = myMapper->readCPU(0x004B);
    pushAddress(0x00075A);
    SUB_0036B4();
    if (poppedEntry.value != 0x00075A) return;
    y = 0x00;
    myMapper->writeCPU(0x009D, myMapper->readCPU(0x0035));
    do {
        a = myMapper->readCPU(0x02C0 + y);
        opINY(1);
        pushAddress(0x000767);
        SUB_00376C();
        if (poppedEntry.value != 0x000767) return;
        x = a;
        opINC(0x050F + x, 2);
        if (myMapper->readCPU(0x02C0 + y) >= 0x30) {
            goto L_000784;
        }
        opDEX(1);
        opINC(0x050F + x, 1);
        opINX(1);
        opINC(0x050F + x, 1);
        opINX(1);
        opINC(0x050F + x, 1);
    L_000784:
        opINY(1);
        opDEC(0x009D, 1);
    } while (!flgZ);
    myMapper->writeCPU(0x0032, 0x00);
    do {
        do {
            do {
                y = myMapper->readCPU(0x0032);
                a = myMapper->readCPU(0x0200 + y);
                opCMP(a, 0xFF);
                if (flgZ) {
                    goto L_0007D8;
                }
                opINC(0x0032, 1);
                myMapper->writeCPU(0x009C, a);
                x = a;
                opINC(0x050F + x, 2);
                pushAddress(0x0007A1);
                SUB_0008DC();
                if (poppedEntry.value != 0x0007A1) return;
                a = myMapper->readCPU(0x009C);
                opCMP(a, 0x30);
                if (!flgC) {
                    goto L_0007B6;
                }
                pushAddress(0x0007AA);
                SUB_001FB3();
                if (poppedEntry.value != 0x0007AA) return;
            } while (flgC);
            x = myMapper->readCPU(0x009C);
            opINC(0x050F + x, 1);
        } while (!flgZ);
    L_0007B6:
        opDEX(2);
        if (flgN) {
            goto L_0007BD;
        }
        opINC(0x050F + x, 1);
    L_0007BD:
        opINX(1);
        opINC(0x050F + x, 2);
        opINX(1);
        opINC(0x050F + x, 2);
        opINX(1);
        opINC(0x050F + x, 2);
        opINX(1);
        opINC(0x050F + x, 1);
    } while (!flgZ);
L_0007D8:
    popAddress();
}

void game::SUB_0007D9() {
    a = myMapper->readCPU(0x0033);
    opPHA();
    a = myMapper->readCPU(0x02C5);
    opPHA();
    myMapper->writeCPU(0x02C5, 0x00);
    a = 0x01;
    myMapper->writeCPU(0x0061, a);
    myMapper->writeCPU(0x023E, a);
    pushAddress(0x0007EC);
    SUB_000E7C();
    if (poppedEntry.value != 0x0007EC) return;
    a = 0x00;
    myMapper->writeCPU(0x0061, a);
    myMapper->writeCPU(0x023E, a);
    opPLA();
    myMapper->writeCPU(0x02C5, a);
    opPLA();
    myMapper->writeCPU(0x0033, a);
    x = myMapper->readCPU(0x004E);
    opDEX(1);
    if (!flgN) {
        if (myMapper->readCPU(0x004A) >= myMapper->readCPU(0x0049)) {
            goto L_000810;
        }
        myMapper->writeCPU(0x004A, myMapper->readCPU(0x0049));
        myMapper->writeCPU(0x004C, myMapper->readCPU(0x004B));
    }
L_000810:
    popAddress();
}

void game::SUB_000811() {
    myMapper->writeCPU(0x009D, 0xFF);
    myMapper->writeCPU(0x0033, 0x00);
    do {
        do {
            x = myMapper->readCPU(0x0033);
            a = myMapper->readCPU(0x044E + x);
            opINC(0x0033, 1);
            if (a == 0xFF) {
                goto L_000842;
            }
            myMapper->writeCPU(0x009C, a);
            x = a;
            a = myMapper->readCPU(0x050F + x);
            opCMP(a, myMapper->readCPU(0x009D));
            if (flgZ) {
                goto L_000837;
            }
        } while (flgC);
        myMapper->writeCPU(0x009D, a);
        y = 0x00;
        myMapper->writeCPU(0x05CF, y);
    L_000837:
        myMapper->writeCPU(0x05D0 + y, myMapper->readCPU(0x009C));
        opINY(1);
        opINC(0x05CF, 1);
    } while (!flgZ);
L_000842:
    a = myMapper->readCPU(0x05CF);
    opCMP(a, 0x01);
    if (!flgZ) {
        goto L_00084D;
    }
    a = myMapper->readCPU(0x05D0);
    popAddress();
    return;
L_00084D:
    pushAddress(0x00084D);
    SUB_0037DA();
    if (poppedEntry.value != 0x00084D) return;
    x = a;
    a = myMapper->readCPU(0x05D0 + x);
    popAddress();
}

void game::SUB_000855() {
    if (myMapper->readCPU(0x0231) != 0) {
        goto L_00086F;
    }
    if (myMapper->readCPU(0x023A) != 0) {
        goto L_000870;
    }
    pushAddress(0x00085F);
    SUB_000E33();
    if (poppedEntry.value != 0x00085F) return;
    if (a >= 0x04) {
        goto L_000870;
    }
    y = 0x31;
    a = 0x04;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x0231, a);
L_00086F:
    popAddress();
    return;
L_000870:
    if (myMapper->readCPU(0x023B) < 0x06) {
        goto L_00086F;
    }
    a = 0x00;
    myMapper->writeCPU(0x004F, a);
    myMapper->writeCPU(0x0050, a);
    myMapper->writeCPU(0x0051, a);
    myMapper->writeCPU(0x0052, a);
    y = a;
    do {
        a = myMapper->readCPU(0x045D + y);
        opINY(1);
        if (a == 0xFF) {
            goto L_00089F;
        }
        x = 0x00;
        opAND(0x30);
        if (!flgZ) {
            opINX(1);
            if (a != 0x10) {
                opINX(1);
                if (a == 0x20) {
                    goto L_00089B;
                }
                opINX(1);
            }
        }
    L_00089B:
        opINC((0x004F + x) & 0x00ff, 1);
    } while (!flgZ);
L_00089F:
    a = myMapper->readCPU(0x004F);
    flgC = false;
    opADC(myMapper->readCPU(0x0052));
    myMapper->writeCPU(0x009F, a);
    myMapper->writeCPU(0x009C, 0x01);
    a = myMapper->readCPU(0x0050);
    flgC = false;
    opADC(myMapper->readCPU(0x0052));
    if (a >= myMapper->readCPU(0x009F)) {
        myMapper->writeCPU(0x009F, a);
        myMapper->writeCPU(0x009C, 0x11);
    }
    a = myMapper->readCPU(0x0051);
    flgC = false;
    opADC(myMapper->readCPU(0x0052));
    if (a >= myMapper->readCPU(0x009F)) {
        myMapper->writeCPU(0x009F, a);
        myMapper->writeCPU(0x009C, 0x21);
    }
    if (myMapper->readCPU(0x009F) >= 0x0A) {
        goto L_0008D2;
    }
    myMapper->writeCPU(0x009C, 0x00);
L_0008D2:
    y = 0x31;
    a = myMapper->readCPU(0x009C);
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x0231, a);
    popAddress();
}

void game::SUB_0008DC() {
    if (myMapper->readCPU(0x0231) == 0) {
        goto L_00090B;
    }
    if (myMapper->readCPU(0x0034) >= 0x10) {
        if (myMapper->readCPU(0x009C) < 0x30) {
            goto L_0008F1;
        }
        a = 0x0A;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_000904;
        }
    L_0008F1:
        a = myMapper->readCPU(0x0231);
        opAND(0x01);
        if (!flgZ) {
            a = myMapper->readCPU(0x009C);
            flgC = true;
            opSBC(myMapper->readCPU(0x0231));
            opAND(0x30);
            if (!flgZ) {
                goto L_00090B;
            }
            a = 0x1E;
        L_000904:
            flgC = false;
            opADC(myMapper->readCPU(0x050F + x));
            myMapper->writeCPU(0x050F + x, a);
        }
    }
L_00090B:
    popAddress();
}

void game::SUB_00090C() {
    x = 0x00;
    do {
        myMapper->writeCPU(0x04CF + x, myMapper->readCPU(0x048F + x));
        opINX(1);
    } while (x != 0x40);
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(0x0200 + y);
        if (a == 0xFF) {
            goto L_00092A;
        }
        opINY(1);
        x = a;
        opDEC(0x04CF + x, 1);
    }
L_00092A:
    popAddress();
}

void game::SUB_00092B() {
    myMapper->writeCPU(0x00A2, 0xCE);
    myMapper->writeCPU(0x00A3, 0x02);
    a = myMapper->readCPU(0x0307);
    pushAddress(0x000936);
    SUB_0010E2();
    if (poppedEntry.value != 0x000936) return;
    a = 0x04;
    flgC = false;
    opADC(myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x000B, a);
    pushAddress(0x000940);
    SUB_000FA9();
    if (poppedEntry.value != 0x000940) return;
    x = 0x02;
    y = 0xCE;
    pushAddress(0x000947);
    SUB_0036B4();
    if (poppedEntry.value != 0x000947) return;
    pushAddress(0x00094A);
    SUB_003BDE();
    if (poppedEntry.value != 0x00094A) return;
    pushAddress(0x00094D);
    SUB_000964();
    if (poppedEntry.value != 0x00094D) return;
    if (!flgC) {
        goto L_000957;
    }
    pushAddress(0x000952);
    SUB_000A4A();
    if (poppedEntry.value != 0x000952) return;
    flgC = true;
    popAddress();
    return;
L_000957:
    opPHA();
    x = 0x02;
    y = 0xCE;
    a = myMapper->readCPU(0x0060);
    pushAddress(0x00095E);
    SUB_003680();
    if (poppedEntry.value != 0x00095E) return;
    opPLA();
    flgC = false;
    popAddress();
}

void game::SUB_000964() {
    while (true) {
        myMapper->writeCPU(0x000F, 0xCE);
        myMapper->writeCPU(0x0010, 0x02);
        pushAddress(0x00096C);
        SUB_00370F();
        if (poppedEntry.value != 0x00096C) return;
        pushAddress(0x00096F);
        SUB_003751();
        if (poppedEntry.value != 0x00096F) return;
        pushAddress(0x000972);
        SUB_002211();
        if (poppedEntry.value != 0x000972) return;
        pushAddress(0x000975);
        SUB_002266();
        if (poppedEntry.value != 0x000975) return;
        if (flgC) {
            if (myMapper->readCPU(0x030C) == 0) {
                goto L_00098B;
            }
            pushAddress(0x00097F);
            SUB_002422();
            if (poppedEntry.value != 0x00097F) return;
            if (!flgC) {
                goto L_00098B;
            }
            pushAddress(0x000984);
            SUB_001260();
            if (poppedEntry.value != 0x000984) return;
            a = myMapper->readCPU(0x0307);
            popAddress();
            return;
        }
    L_00098B:
        a = myMapper->readCPU(0x0307);
        myMapper->writeCPU(0x008C, a);
        myMapper->writeCPU(0x008D, a);
        while (true) {
        L_000992:
            pushAddress(0x000992);
            SUB_000538();
            if (poppedEntry.value != 0x000992) return;
            pushAddress(0x000995);
            SUB_000A3C();
            if (poppedEntry.value != 0x000995) return;
            myMapper->writeCPU(0x006A, 0xB1);
            myMapper->writeCPU(0x006B, 0xCC);
            myMapper->writeCPU(0x006C, 0x00);
            myMapper->writeCPU(0x006D, 0x03);
            pushAddress(0x0009A8);
            SUB_000C7F();
            if (poppedEntry.value != 0x0009A8) return;
			bool firstLoop = true;
            do {
                if (firstLoop) firstLoop = false;
                else wait();

                if (myMapper->readCPU(0x008B) != 0) {
                    goto L_0009B2;
                }
                pushAddress(0x0009AF);
                SUB_000C61();
                if (poppedEntry.value != 0x0009AF) return;
            L_0009B2:
                if (myMapper->readCPU(0x006C) != 0) {
                    goto L_0009B9;
                }
                pushAddress(0x0009B6);
                SUB_000A0D();
                if (poppedEntry.value != 0x0009B6) return;
            L_0009B9:
                pushAddress(0x0009B9);
                SUB_00053F();
                if (poppedEntry.value != 0x0009B9) return;

                wait();
            } while (myMapper->readCPU(0x001A) == 0);
            pushAddress(0x0009C0);
            SUB_001231();
            if (poppedEntry.value != 0x0009C0) return;
            a = myMapper->readCPU(0x006C);
            setLoadFlag(a);
            if (!flgZ) {
                goto L_0009CD;
            }
            a = myMapper->readCPU(0x008C);
            myMapper->writeCPU(0x0098, a);
            flgC = true;
            popAddress();
            return;
        L_0009CD:
            if (a != 0x01) {
                goto L_0009D7;
            }
            pushAddress(0x0009D1);
            SUB_000B23();
            if (poppedEntry.value != 0x0009D1) return;
        }
    L_0009D7:
        opCMP(a, 0x02);
        if (!flgZ) {
            goto L_0009EE;
        }
        if (myMapper->readCPU(0x007E) == 0) {
            goto L_000A07;
        }
        pushAddress(0x0009DF);
        SUB_001F76();
        if (poppedEntry.value != 0x0009DF) return;
        pushAddress(0x0009E2);
        SUB_0022EB();
        if (poppedEntry.value != 0x0009E2) return;
        pushAddress(0x0009E5);
        SUB_00231D();
        if (poppedEntry.value != 0x0009E5) return;
        if (!flgC) {
            goto L_0009ED;
        }
    }
L_0009ED:
    popAddress();
    return;
L_0009EE:
    myMapper->writeCPU(0x000F, 0xCE);
    myMapper->writeCPU(0x0010, 0x02);
    pushAddress(0x0009F6);
    SUB_00370F();
    if (poppedEntry.value != 0x0009F6) return;
    pushAddress(0x0009F9);
    SUB_002422();
    if (poppedEntry.value != 0x0009F9) return;
    if (flgC) {
        goto L_000A07;
    }
    pushAddress(0x0009FE);
    SUB_001231();
    if (poppedEntry.value != 0x0009FE) return;
    a = 0x01;
    myMapper->writeCPU(0x0098, a);
    flgC = false;
    popAddress();
    return;
L_000A07:
    pushAddress(0x000A07);
    SUB_0012D5();
    if (poppedEntry.value != 0x000A07) return;
    goto L_000992;
}

void game::SUB_000A0D() {
    if (myMapper->readCPU(0x030C) != 0) {
        goto L_000A3B;
    }
    a = myMapper->readCPU(0x0019);
    opAND(0x40);
    if (flgZ) {
        goto L_000A23;
    }
    x = 0x8C;
    pushAddress(0x000A1A);
    SUB_000CD2();
    if (poppedEntry.value != 0x000A1A) return;
    pushAddress(0x000A1D);
    SUB_000A3C();
    if (poppedEntry.value != 0x000A1D) return;
    goto L_000A31;
L_000A23:
    a = myMapper->readCPU(0x0019);
    opAND(0x80);
    if (flgZ) {
        goto L_000A3B;
    }
    x = 0x8C;
    pushAddress(0x000A2B);
    SUB_000CC5();
    if (poppedEntry.value != 0x000A2B) return;
    pushAddress(0x000A2E);
    SUB_000A3C();
    if (poppedEntry.value != 0x000A2E) return;
L_000A31:
    x = 0xE0;
    y = 0x00;
    do {
        do {
            opDEY(1);
        } while (!flgZ);
        opDEX(1);
        if (x == 0xC0) wait();
        if (x == 0x80) wait();
        if (x == 0x40) wait();
    } while (!flgZ);
    wait();

L_000A3B:
    popAddress();
}

void game::SUB_000A3C() {
    a = myMapper->readCPU(0x008C);
    opASL_A(1);
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, 0x18);
    a = 0x00;
    SUB_003A8A();
    return;
}

void game::SUB_000A4A() {
    pushAddress(0x000A4A);
    SUB_000A64();
    if (poppedEntry.value != 0x000A4A) return;
    x = 0x02;
    y = 0xCE;
    pushAddress(0x000A51);
    SUB_00379B();
    if (poppedEntry.value != 0x000A51) return;
    myMapper->writeCPU(0x000B, 0x18);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x000A5C);
    SUB_003B49();
    if (poppedEntry.value != 0x000A5C) return;
    a = 0x38;
    SUB_003BDE();
    return;
}

void game::SUB_000A64() {
    opPHA();
    pushAddress(0x000A65);
    SUB_0010E2();
    if (poppedEntry.value != 0x000A65) return;
    a = 0x04;
    opADC(myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x000B, a);
    a = 0x38;
    pushAddress(0x000A70);
    SUB_003BDE();
    if (poppedEntry.value != 0x000A70) return;
    opPLA();
    y = a;
    a = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x0044, a);
    myMapper->writeCPU(0x0060, a);
    x = myMapper->readCPU(0x003F);
    y = myMapper->readCPU(0x003E);
    pushAddress(0x000A7F);
    SUB_003680();
    if (poppedEntry.value != 0x000A7F) return;
    x = a;
    a = myMapper->readCPU(0x058F + x);
    y = 0x42;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    y = 0x3B;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    flgC = false;
    opADC(0x13);
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x0044));
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x00A2));
    myMapper->writeCPU(0x0090, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x00A3));
    myMapper->writeCPU(0x0091, a);
    y = 0x40;
    myMapper->writeCPU(0x000B, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    y = 0x3B;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    if (a == 0x0C) {
        opPHA();
        myMapper->writeCPU(0x000A, 0x08);
        y = 0x14;
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            opPHA();
            opAND(0x40);
            if (flgZ) {
                goto L_000AD5;
            }
            a = myMapper->readCPU(0x000B);
            opPHA();
            a = myMapper->readCPU(0x000A);
            opPHA();
            opINC(0x000B, 1);
            pushAddress(0x000ACC);
            SUB_003A5F();
            if (poppedEntry.value != 0x000ACC) return;
            opPLA();
            myMapper->writeCPU(0x000A, a);
            opPLA();
            myMapper->writeCPU(0x000B, a);
        L_000AD5:
            opPLA();
            pushAddress(0x000AD6);
            SUB_003BDE();
            if (poppedEntry.value != 0x000AD6) return;
        } while (y != 0x1F);
        opINC(0x000B, 2);
        myMapper->writeCPU(0x000A, 0x08);
        x = 0x0B;
        do {
            a = 0x38;
            pushAddress(0x000AE9);
            SUB_003BDE();
            if (poppedEntry.value != 0x000AE9) return;
            opDEX(1);
        } while (!flgZ);
        opDEC(0x000B, 2);
        opPLA();
    }
    opINC(0x000B, 2);
    opCMP(a, 0x0C);
    if (flgC) {
        opSBC(0x0B);
    }
    opASL_A(1);
    flgC = false;
    opADC(0x06);
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x008F, a);
    myMapper->writeCPU(0x008E, myMapper->readCPU(0x000B));
    a = myMapper->readCPU(0x0044);
    pushAddress(0x000B0C);
    SUB_003BDE();
    if (poppedEntry.value != 0x000B0C) return;
    pushAddress(0x000B0F);
    SUB_000C4C();
    if (poppedEntry.value != 0x000B0F) return;
    myMapper->writeCPU(0x0075, 0x00);
    pushAddress(0x000B16);
    SUB_003287();
    if (poppedEntry.value != 0x000B16) return;
    if (myMapper->readCPU(0x0070) == 0) {
        goto L_000B22;
    }
    a = myMapper->readCPU(0x0044);
    pushAddress(0x000B1F);
    SUB_000C05();
    if (poppedEntry.value != 0x000B1F) return;
L_000B22:
    popAddress();
}

void game::SUB_000B23() {
    opCMP(myMapper->readCPU(0x0034), 0x04);
    if (!flgC) {
        SUB_0012D5();
        return;
    }
    y = 0x3E;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
        goto L_000B37;
    }
    pushAddress(0x000B32);
    SUB_000CDB();
    if (poppedEntry.value != 0x000B32) return;
    if (!flgC) {
        goto L_000B38;
    }
L_000B37:
    popAddress();
    return;
L_000B38:
    pushAddress(0x000B38);
    SUB_003257();
    if (poppedEntry.value != 0x000B38) return;
    myMapper->writeCPU(0x006F, 0x01);
    y = 0x40;
    myMapper->writeCPU(0x000B, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    opINC(0x000B, 1);
    myMapper->writeCPU(0x000A, 0x04);
    x = 0xFF;
    y = 0x24;
    SUB_003CBE();
    return;
}

void game::SUB_000B52() {
    a = myMapper->readCPU(0x006F);
    setLoadFlag(a);
    if (flgZ) {
        goto L_000B78;
    }
    myMapper->writeCPU(0x006F, 0x00);
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x003F));
    goto L_000B7A;
    do {
        y = 0x40;
        myMapper->writeCPU(0x000B, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
        opINC(0x000B, 1);
        myMapper->writeCPU(0x000A, 0x04);
        x = 0xD2;
        y = 0x5B;
        pushAddress(0x000B75);
        SUB_003CBE();
        if (poppedEntry.value != 0x000B75) return;
    L_000B78:
        flgC = true;
        popAddress();
        return;
    L_000B7A:
        myMapper->writeCPU(0x000F, myMapper->readCPU(0x003E));
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x003F));
        pushAddress(0x000B82);
        SUB_00370F();
        if (poppedEntry.value != 0x000B82) return;
        x = 0x01;
        if (myMapper->readCPU(0x003D) >= 0x04) {
            goto L_000B8E;
        }
        opINX(1);
    L_000B8E:
        myMapper->writeCPU(0x023E, x);
        myMapper->writeCPU(0x0061, 0x01);
        pushAddress(0x000B96);
        SUB_000E7C();
        if (poppedEntry.value != 0x000B96) return;
        a = 0x00;
        myMapper->writeCPU(0x0061, a);
        myMapper->writeCPU(0x023E, a);
        x = myMapper->readCPU(0x004E);
        opDEX(1);
    } while (flgN);
    x = myMapper->readCPU(0x008E);
    opINX(1);
    myMapper->writeCPU(0x000B, x);
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x008F));
    pushAddress(0x000BAE);
    SUB_003A5F();
    if (poppedEntry.value != 0x000BAE) return;
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    x = 0x81;
    if (myMapper->readCPU(0x003D) < 0x04) {
        opINX(1);
    }
    a = x;
    y = 0x3E;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x0097, 0x9C);
    myMapper->writeCPU(0x0098, 0xFF);
    pushAddress(0x000BCF);
    SUB_003966();
    if (poppedEntry.value != 0x000BCF) return;
    a = 0x01;
    y = 0x38;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x000A, 0x02);
    pushAddress(0x000BE5);
    SUB_003945();
    if (poppedEntry.value != 0x000BE5) return;
    opINC(0x0070, 1);
    if (myMapper->readCPU(0x0070) == 0x04) {
        goto L_000C01;
    }
    y = 0x14;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_000C04;
        }
        opINY(1);
        opAND(0x3F);
        pushAddress(0x000BFB);
        SUB_000C05();
        if (poppedEntry.value != 0x000BFB) return;
    }
L_000C01:
    a = 0x03;
    flgC = false;
L_000C04:
    popAddress();
}

void game::SUB_000C05() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = myMapper->readCPU(0x0098);
    x = a;
    if (a >= 0x30) {
        goto L_000C32;
    }
    opDEC(0x054F + x, 3);
    opINX(3);
    opDEC(0x054F + x, 2);
    x = myMapper->readCPU(0x0098);
    opDEX(3);
    if (flgN) {
        goto L_000C2F;
    }
    opDEC(0x054F + x, 2);
    while (true) {
    L_000C2F:
        opPLA();
        x = a;
        popAddress();
        return;
    L_000C32:
        opDEC(0x054F + x, 1);
        flgC = true;
        opSBC(0x04);
        myMapper->writeCPU(0x054F + x, a);
    }
    SUB_000C3E();
    return;
}

void game::SUB_000C3E() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    x = myMapper->readCPU(0x0098);
    opDEC(0x048F + x, 1);
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0098);
    popAddress();
}

void game::SUB_000C4C() {
    a = y;
    opPHA();
    y = 0x3E;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    opAND(0x03);
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    if (!flgZ) {
        goto L_000C5E;
    }
    a = 0x00;
    y = 0x3C;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
L_000C5E:
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_000C61() {
    x = 0x6C;
    a = myMapper->readCPU(0x0019);
    opAND(0x10);
    if (flgZ) {
        goto L_000C6F;
    }
    pushAddress(0x000C69);
    SUB_000CD2();
    if (poppedEntry.value != 0x000C69) return;
    goto L_000C78;
L_000C6F:
    a = myMapper->readCPU(0x0019);
    opAND(0x20);
    if (flgZ) {
        goto L_000C7E;
    }
    pushAddress(0x000C75);
    SUB_000CC5();
    if (poppedEntry.value != 0x000C75) return;
L_000C78:
    pushAddress(0x000C78);
    SUB_000C7F();
    if (poppedEntry.value != 0x000C78) return;
    SUB_000538();
    return;
L_000C7E:
    popAddress();
}

void game::SUB_000C7F() {
    a = myMapper->readCPU(0x006C);
    opASL_A(2);
    opADC(myMapper->readCPU(0x006C));
    opADC(myMapper->readCPU(0x006A));
    y = a;
    a = 0x00;
    opADC(myMapper->readCPU(0x006B));
    x = a;
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x04);
    SUB_003CBE();
    return;
}

void game::SUB_000CC5() {
    opINC((0x0000 + x) & 0x00ff, 1);
    if (myMapper->readCPU((0x0001 + x) & 0x00ff) >= myMapper->readCPU((0x0000 + x) & 0x00ff)) {
        goto L_000CD1;
    }
    myMapper->writeCPU((0x0000 + x) & 0x00ff, 0x00);
L_000CD1:
    popAddress();
}

void game::SUB_000CD2() {
    opDEC((0x0000 + x) & 0x00ff, 1);
    if (!flgN) {
        goto L_000CDA;
    }
    myMapper->writeCPU((0x0000 + x) & 0x00ff, myMapper->readCPU((0x0001 + x) & 0x00ff));
L_000CDA:
    popAddress();
}

void game::SUB_000CDB() {
    myMapper->writeCPU(0x005F, 0x00);
    if (myMapper->readCPU(0x023A) == 0) {
        goto L_000CF4;
    }
    x = 0x0F;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a == 0xFF) {
            goto L_000CF4;
        }
    } while (a >= 0xC0);
    flgC = true;
    popAddress();
    return;
L_000CF4:
    opINC(0x005F, 1);
    flgC = false;
    popAddress();
}

void game::SUB_000CF8() {
    pushAddress(0x000CF8);
    SUB_000E33();
    if (poppedEntry.value != 0x000CF8) return;
    if (flgC) {
        myMapper->writeCPU(0x0066, a);
        y = 0x31;
        a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
        opAND(0x04);
        flgC = true;
        if (flgZ) {
            pushAddress(0x000D08);
            SUB_003725();
            if (poppedEntry.value != 0x000D08) return;
            pushAddress(0x000D0B);
            SUB_000E09();
            if (poppedEntry.value != 0x000D0B) return;
            if (flgC) {
                goto L_000D11;
            }
        }
    }
    popAddress();
    return;
L_000D11:
    pushAddress(0x000D11);
    SUB_000D86();
    if (poppedEntry.value != 0x000D11) return;
    myMapper->writeCPU(0x0063, 0x01);
    x = 0x00;
    while (true) {
        a = myMapper->readCPU(0x0446 + x);
        if (a == 0xFF) {
            goto L_000D65;
        }
        myMapper->writeCPU(0x009C, a);
        opINX(1);
        a = x;
        opPHA();
        x = 0x00;
        pushAddress(0x000D28);
        SUB_0036FC();
        if (poppedEntry.value != 0x000D28) return;
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
        pushAddress(0x000D3A);
        SUB_0036FC();
        if (poppedEntry.value != 0x000D3A) return;
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
        a = x;
        opPHA();
        pushAddress(0x000D4E);
        SUB_000D8D();
        if (poppedEntry.value != 0x000D4E) return;
        if (!flgC) {
            goto L_000D80;
        }
        pushAddress(0x000D53);
        SUB_000D86();
        if (poppedEntry.value != 0x000D53) return;
        opPLA();
        x = a;
        pushAddress(0x000D58);
        SUB_000D9C();
        if (poppedEntry.value != 0x000D58) return;
        if (!flgC) {
            goto L_000D81;
        }
        pushAddress(0x000D5D);
        SUB_000D86();
        if (poppedEntry.value != 0x000D5D) return;
        opPLA();
        x = a;
    }
L_000D65:
    a = 0x00;
    myMapper->writeCPU(0x0063, a);
    x = a;
    pushAddress(0x000D6A);
    SUB_000D8D();
    if (poppedEntry.value != 0x000D6A) return;
    if (flgC) {
        pushAddress(0x000D6F);
        SUB_000D86();
        if (poppedEntry.value != 0x000D6F) return;
        x = 0x00;
        pushAddress(0x000D74);
        SUB_000D9C();
        if (poppedEntry.value != 0x000D74) return;
        if (!flgC) {
            goto L_000D7F;
        }
        pushAddress(0x000D79);
        SUB_000D86();
        if (poppedEntry.value != 0x000D79) return;
        a = myMapper->readCPU(0x0066);
        flgC = true;
    }
L_000D7F:
    popAddress();
    return;
L_000D80:
    opPLA();
L_000D81:
    opPLA();
    a = 0x00;
    flgC = false;
    popAddress();
}

void game::SUB_000D86() {
    if (a >= myMapper->readCPU(0x0066)) {
        goto L_000D8C;
    }
    myMapper->writeCPU(0x0098, a);
L_000D8C:
    popAddress();
}

void game::SUB_000D8D() {
    pushAddress(0x000D8D);
    SUB_003604();
    if (poppedEntry.value != 0x000D8D) return;
    pushAddress(0x000D90);
    SUB_000DDC();
    if (poppedEntry.value != 0x000D90) return;
    pushAddress(0x000D93);
    SUB_000DF1();
    if (poppedEntry.value != 0x000D93) return;
    pushAddress(0x000D96);
    SUB_003612();
    if (poppedEntry.value != 0x000D96) return;
    SUB_000DA8();
    return;
}

void game::SUB_000D9C() {
    pushAddress(0x000D9C);
    SUB_003604();
    if (poppedEntry.value != 0x000D9C) return;
    pushAddress(0x000D9F);
    SUB_000DF1();
    if (poppedEntry.value != 0x000D9F) return;
    pushAddress(0x000DA2);
    SUB_000DDC();
    if (poppedEntry.value != 0x000DA2) return;
    pushAddress(0x000DA5);
    SUB_003612();
    if (poppedEntry.value != 0x000DA5) return;
    SUB_000DA8();
    return;
}

void game::SUB_000DA8() {
    a = myMapper->readCPU(0x0062);
    flgC = false;
    opADC(myMapper->readCPU(0x0064));
    opADC(myMapper->readCPU(0x0065));
    if (a >= 0x05) {
        a = 0x04;
        flgC = true;
        opSBC(myMapper->readCPU(0x0062));
        myMapper->writeCPU(0x0065, a);
        a = myMapper->readCPU(0x0064);
        setLoadFlag(a);
        pushStatus();
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0064, a);
        popStatus();
        if (!flgZ) {
            opINC(0x0064, 1);
        }
    }
    a = myMapper->readCPU(0x0062);
    opASL_A(1);
    opADC(myMapper->readCPU(0x0064));
    opADC(myMapper->readCPU(0x0065));
    myMapper->writeCPU(0x0098, a);
    a = 0x08;
    flgC = true;
    opSBC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0066, a);
    if (!flgZ) {
        goto L_000DDA;
    }
    flgC = false;
    popAddress();
    return;
L_000DDA:
    flgC = true;
    popAddress();
}

void game::SUB_000DDC() {
    while (true) {
        y = x;
        do {
            a = myMapper->readCPU(0x0200 + y);
            opINY(1);
            if (a == 0xFF) {
                goto L_000DF0;
            }
            pushAddress(0x000DE6);
            SUB_0034EA();
            if (poppedEntry.value != 0x000DE6) return;
        } while (flgC);
        opINC(0x0062, 1);
    }
L_000DF0:
    popAddress();
}

void game::SUB_000DF1() {
    while (true) {
        myMapper->writeCPU(0x009E, 0x00);
        do {
            a = myMapper->readCPU(0x009E);
            pushAddress(0x000DF7);
            SUB_003657();
            if (poppedEntry.value != 0x000DF7) return;
            if (flgC) {
                goto L_000E08;
            }
            myMapper->writeCPU(0x009E, a);
            pushAddress(0x000DFE);
            SUB_003488();
            if (poppedEntry.value != 0x000DFE) return;
        } while (flgC);
        opINC(0x0062, 1);
    }
L_000E08:
    popAddress();
}

void game::SUB_000E09() {
    a = 0x06;
    flgC = true;
    opSBC(myMapper->readCPU(0x0064));
    if (flgZ) {
        goto L_000E12;
    }
    flgC = true;
    popAddress();
    return;
L_000E12:
    y = 0x00;
    do {
        a = myMapper->readCPU(0x0446 + y);
        opINY(1);
        if (a == 0xFF) {
            goto L_000E27;
        }
        x = 0x00;
        pushAddress(0x000E1E);
        SUB_00353E();
        if (poppedEntry.value != 0x000E1E) return;
        opCMP(a, 0x03);
        if (flgC) {
            goto L_000E2D;
        }
    } while (!flgC);
L_000E27:
    a = 0x00;
    myMapper->writeCPU(0x0066, a);
    flgC = false;
    popAddress();
    return;
L_000E2D:
    a = 0x01;
    myMapper->writeCPU(0x0066, a);
    flgC = true;
    popAddress();
}

void game::SUB_000E33() {
    if (myMapper->readCPU(0x023A) == 0) {
        goto L_000E3C;
    }
    a = 0x07;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_000E66;
    }
L_000E3C:
    a = 0x00;
    myMapper->writeCPU(0x009D, a);
    myMapper->writeCPU(0x009C, a);
    y = a;
    do {
        do {
            if (myMapper->readCPU(0xF0C3 + y) == 0) {
                goto L_000E5E;
            }
            opINY(1);
            a = 0x00;
            pushAddress(0x000E4B);
            SUB_00353E();
            if (poppedEntry.value != 0x000E4B) return;
        } while (a == 0x00);
        if (a == 0x01) {
            goto L_000E5A;
        }
        myMapper->writeCPU(0x009D, 0x01);
    L_000E5A:
        opINC(0x009C, 1);
    } while (!flgZ);
L_000E5E:
    a = 0x0D;
    flgC = true;
    opSBC(myMapper->readCPU(0x009C));
    flgC = true;
    opSBC(myMapper->readCPU(0x009D));
L_000E66:
    myMapper->writeCPU(0x0066, a);
    if (flgZ) {
        goto L_000E6C;
    }
    flgC = true;
    popAddress();
    return;
L_000E6C:
    flgC = false;
    popAddress();
}

void game::SUB_000E6E() {
    pushAddress(0x000E6E);
    SUB_000E7C();
    if (poppedEntry.value != 0x000E6E) return;
    if (myMapper->readCPU(0x0471) != 0xFF) {
        goto L_000E7A;
    }
    flgC = true;
    popAddress();
    return;
L_000E7A:
    flgC = false;
    popAddress();
}

void game::SUB_000E7C() {
    a = myMapper->readCPU(0x0060);
    opPHA();
    a = 0x00;
    myMapper->writeCPU(0x0022, a);
    myMapper->writeCPU(0x0049, a);
    myMapper->writeCPU(0x004D, a);
    myMapper->writeCPU(0x004E, 0xFF);
    a = 0x00;
    x = 0x02;
    y = 0x00;
    pushAddress(0x000E91);
    SUB_0036B4();
    if (poppedEntry.value != 0x000E91) return;
    myMapper->writeCPU(0x0471, 0xFF);
    while (true) {
        do {
            do {
                pushAddress(0x000E99);
                SUB_00344F();
                if (poppedEntry.value != 0x000E99) return;
                a = myMapper->readCPU(0x0022);
                if (a == 0xFF) {
                    goto L_000EFE;
                }
                pushAddress(0x000EA2);
                SUB_000F14();
                if (poppedEntry.value != 0x000EA2) return;
            } while (flgC);
            myMapper->writeCPU(0x009C, 0x00);
            x = 0x00;
            pushAddress(0x000EAD);
            SUB_0036FC();
            if (poppedEntry.value != 0x000EAD) return;
            a = myMapper->readCPU(0x0022);
            myMapper->writeCPU(0x0200 + y, a);
            myMapper->writeCPU(0x0060, a);
            pushAddress(0x000EB7);
            SUB_00243A();
            if (poppedEntry.value != 0x000EB7) return;
            pushStatus();
            myMapper->writeCPU(0x009C, myMapper->readCPU(0x0022));
            x = 0x00;
            pushAddress(0x000EC1);
            SUB_0036FC();
            if (poppedEntry.value != 0x000EC1) return;
            a = 0x00;
            setLoadFlag(a);
            myMapper->writeCPU(0x0200 + y, a);
            popStatus();
        } while (flgC);
        x = myMapper->readCPU(0x0022);
        a = myMapper->readCPU(0x0049);
        opADC(myMapper->readCPU(0x04CF + x));
        myMapper->writeCPU(0x0049, a);
        a = myMapper->readCPU(0x002E);
        flgC = false;
        opADC(myMapper->readCPU(0x004D));
        myMapper->writeCPU(0x004D, a);
        a = myMapper->readCPU(0x002E);
        flgC = true;
        opSBC(myMapper->readCPU(0x002F));
        if (!flgZ) {
            x = a;
            if (myMapper->readCPU(0x003B) >= 0x05) {
                opDEX(1);
            }
            a = x;
        }
        if (a >= myMapper->readCPU(0x004E)) {
            goto L_000EF2;
        }
        myMapper->writeCPU(0x004E, a);
    L_000EF2:
        x = 0x04;
        y = 0x71;
        a = myMapper->readCPU(0x0022);
        pushAddress(0x000EF8);
        SUB_0036B4();
        if (poppedEntry.value != 0x000EF8) return;
    }
L_000EFE:
    x = 0x02;
    y = 0x00;
    a = 0x00;
    pushAddress(0x000F04);
    SUB_003680();
    if (poppedEntry.value != 0x000F04) return;
    opPLA();
    myMapper->writeCPU(0x0060, a);
    a = myMapper->readCPU(0x0049);
    setLoadFlag(a);
    if (flgZ) {
        goto L_000F13;
    }
    flgC = false;
    opADC(myMapper->readCPU(0x004D));
    myMapper->writeCPU(0x0049, a);
L_000F13:
    popAddress();
}

void game::SUB_000F14() {
    myMapper->writeCPU(0x009C, a);
    x = 0x00;
    pushAddress(0x000F18);
    SUB_00353E();
    if (poppedEntry.value != 0x000F18) return;
    if (a < 0x04) {
        goto L_000F21;
    }
    flgC = true;
    do {
        do {
            do {
                popAddress();
                return;
            L_000F21:
                a = myMapper->readCPU(0x009C);
                pushAddress(0x000F23);
                SUB_002CAB();
                if (poppedEntry.value != 0x000F23) return;
            } while (!flgC);
            opDEC(0x009C, 1);
            if (flgZ) {
                goto L_000F33;
            }
            x = 0x00;
            pushAddress(0x000F2E);
            SUB_0036FC();
            if (poppedEntry.value != 0x000F2E) return;
        } while (!flgC);
    L_000F33:
        opINC(0x009C, 1);
        x = 0x00;
        pushAddress(0x000F37);
        SUB_0036FC();
        if (poppedEntry.value != 0x000F37) return;
    } while (!flgC);
    opINC(0x009C, 1);
    x = 0x00;
    SUB_0036FC();
    return;
}

void game::SUB_000F43() {
    x = 0x00;
    myMapper->writeCPU(0x0022, x);
    do {
        pushAddress(0x000F47);
        SUB_00344F();
        if (poppedEntry.value != 0x000F47) return;
        a = myMapper->readCPU(0x0022);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_000F62;
        }
        myMapper->writeCPU(0x0246 + x, a);
        opINX(1);
        myMapper->writeCPU(0x0246 + x, a);
        opINX(1);
        myMapper->writeCPU(0x0246 + x, a);
        opINX(1);
        myMapper->writeCPU(0x0246 + x, a);
        opINX(1);
    } while (!flgZ);
L_000F62:
    a = myMapper->readCPU(0x4016);
    opEOR(myMapper->readCPU(0x4017));
    myMapper->writeCPU(0x001E, a);
    a = 0x00;
    myMapper->writeCPU(0x0003, a);
    myMapper->writeCPU(0x0004, a);
    myMapper->writeCPU(0x0095, a);
    myMapper->writeCPU(0x0019, a);
    myMapper->writeCPU(0x0024, a);
    myMapper->writeCPU(0x0018, a);
    popAddress();
}

void game::SUB_000F79() {
    a = 0x00;
    pushAddress(0x000F7B);
    SUB_0037DA();
    if (poppedEntry.value != 0x000F7B) return;
    opAND(0x03);
    myMapper->writeCPU(0x0036, a);
    myMapper->writeCPU(0x0039, a);
    a = 0x00;
    myMapper->writeCPU(0x003B, a);
    myMapper->writeCPU(0x003C, a);
    myMapper->writeCPU(0x0037, a);
    x = 0x0A;
    y = 0x8C;
    myMapper->writeCPU(0x0358, x);
    myMapper->writeCPU(0x0357, y);
    myMapper->writeCPU(0x039E, x);
    myMapper->writeCPU(0x039D, y);
    myMapper->writeCPU(0x03E4, x);
    myMapper->writeCPU(0x03E3, y);
    myMapper->writeCPU(0x0312, x);
    myMapper->writeCPU(0x0311, y);
    popAddress();
}

void game::SUB_000FA9() {
    a = x;
    opPHA();
    x = myMapper->readCPU(0x0021);
    opINC(0x0021, 1);
    myMapper->writeCPU(0x0060, myMapper->readCPU(0x0246 + x));
    opDEC(0x0034, 1);
    pushAddress(0x000FB6);
    SUB_001278();
    if (poppedEntry.value != 0x000FB6) return;
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0060);
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_000FC0() {
    myMapper->writeCPU(0x0034, 0x46);
    a = 0x00;
    myMapper->writeCPU(0x0061, a);
    myMapper->writeCPU(0x006F, a);
    myMapper->writeCPU(0x003D, a);
    myMapper->writeCPU(0x0070, a);
    myMapper->writeCPU(0x0074, a);
    myMapper->writeCPU(0x0075, a);
    myMapper->writeCPU(0x0071, a);
    myMapper->writeCPU(0x0072, a);
    myMapper->writeCPU(0x0073, a);
    myMapper->writeCPU(0x008B, a);
    myMapper->writeCPU(0x005D, a);
    myMapper->writeCPU(0x008E, a);
    myMapper->writeCPU(0x008F, a);
    myMapper->writeCPU(0x0035, 0x01);
    a = myMapper->readCPU(0x02C0);
    pushAddress(0x000FE7);
    SUB_000C3E();
    if (poppedEntry.value != 0x000FE7) return;
    myMapper->writeCPU(0x0039, myMapper->readCPU(0x0036));
    x = 0x00;
    do {
        myMapper->writeCPU(0x048F + x, 0x04);
        myMapper->writeCPU(0x054F + x, 0x1E);
        opINX(1);
    } while (x != 0x40);
    x = 0x02;
    y = 0xCE;
    pushAddress(0x001003);
    SUB_00105D();
    if (poppedEntry.value != 0x001003) return;
    myMapper->writeCPU(0x030E, 0x14);
    myMapper->writeCPU(0x030F, 0x00);
    x = 0x03;
    y = 0x14;
    pushAddress(0x001014);
    SUB_00105D();
    if (poppedEntry.value != 0x001014) return;
    myMapper->writeCPU(0x0354, 0x02);
    myMapper->writeCPU(0x0355, 0x01);
    x = 0x03;
    y = 0x5A;
    pushAddress(0x001025);
    SUB_00105D();
    if (poppedEntry.value != 0x001025) return;
    myMapper->writeCPU(0x039A, 0x08);
    myMapper->writeCPU(0x039B, 0x02);
    x = 0x03;
    y = 0xA0;
    pushAddress(0x001036);
    SUB_00105D();
    if (poppedEntry.value != 0x001036) return;
    myMapper->writeCPU(0x03E0, 0x0E);
    myMapper->writeCPU(0x03E1, 0x03);
    y = 0x3F;
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0039);
        pushAddress(0x001049);
        SUB_00346A();
        if (poppedEntry.value != 0x001049) return;
        myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, x);
        opINC(0x0039, 1);
        a = myMapper->readCPU(0x0039);
        opAND(0x03);
        myMapper->writeCPU(0x0039, a);
        opINX(1);
        opCMP(x, 0x04);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00105D() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0x00;
    x = 0x2C;
    a = 0xFF;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    x = 0x16;
    a = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    a = 0x0D;
    y = 0x39;
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_00107E() {
    myMapper->writeCPU(0x0021, 0x34);
    x = 0x00;
    myMapper->writeCPU(0x000F, 0xCE);
    myMapper->writeCPU(0x0010, 0x02);
    pushAddress(0x00108C);
    SUB_0010AD();
    if (poppedEntry.value != 0x00108C) return;
    myMapper->writeCPU(0x000F, 0x14);
    myMapper->writeCPU(0x0010, 0x03);
    pushAddress(0x001097);
    SUB_0010AD();
    if (poppedEntry.value != 0x001097) return;
    myMapper->writeCPU(0x000F, 0x5A);
    myMapper->writeCPU(0x0010, 0x03);
    pushAddress(0x0010A2);
    SUB_0010AD();
    if (poppedEntry.value != 0x0010A2) return;
    myMapper->writeCPU(0x000F, 0xA0);
    myMapper->writeCPU(0x0010, 0x03);
    SUB_0010AD();
    return;
}

void game::SUB_0010AD() {
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x0010));
    y = 0x00;
    do {
        myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x0246 + x));
        opINX(1);
        opINY(1);
        opCMP(y, 0x0D);
    } while (!flgZ);
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, 0xFF);
    a = x;
    opPHA();
    pushAddress(0x0010C8);
    SUB_00370F();
    if (poppedEntry.value != 0x0010C8) return;
    pushAddress(0x0010CB);
    SUB_000CF8();
    if (poppedEntry.value != 0x0010CB) return;
    y = 0x42;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    pushAddress(0x0010D2);
    SUB_000E33();
    if (poppedEntry.value != 0x0010D2) return;
    if (a >= 0x04) {
        goto L_0010DF;
    }
    y = 0x31;
    a = 0x04;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
L_0010DF:
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_0010E2() {
    opASL_A(1);
    myMapper->writeCPU(0x000A, a);
    a = y;
    opPHA();
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    myMapper->writeCPU(0x000B, a);
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_0010F0() {
    pushAddress(0x0010F0);
    SUB_0039DC();
    if (poppedEntry.value != 0x0010F0) return;
    pushAddress(0x0010F3);
    SUB_00113D();
    if (poppedEntry.value != 0x0010F3) return;
    pushAddress(0x0010F6);
    SUB_001278();
    if (poppedEntry.value != 0x0010F6) return;
    x = 0x03;
    y = 0x14;
    pushAddress(0x0010FD);
    SUB_0011DB();
    if (poppedEntry.value != 0x0010FD) return;
    x = 0x03;
    y = 0x5A;
    pushAddress(0x001104);
    SUB_0011DB();
    if (poppedEntry.value != 0x001104) return;
    x = 0x03;
    y = 0xA0;
    pushAddress(0x00110B);
    SUB_0011DB();
    if (poppedEntry.value != 0x00110B) return;
    x = 0x02;
    y = 0xCE;
    myMapper->writeCPU(0x000B, 0x18);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x00111A);
    SUB_00379B();
    if (poppedEntry.value != 0x00111A) return;
    pushAddress(0x00111D);
    SUB_003B49();
    if (poppedEntry.value != 0x00111D) return;
    x = 0x03;
    y = 0x14;
    pushAddress(0x001124);
    SUB_001205();
    if (poppedEntry.value != 0x001124) return;
    x = 0x03;
    y = 0x5A;
    pushAddress(0x00112B);
    SUB_001205();
    if (poppedEntry.value != 0x00112B) return;
    x = 0x03;
    y = 0xA0;
    pushAddress(0x001132);
    SUB_001205();
    if (poppedEntry.value != 0x001132) return;
    x = 0x02;
    y = 0xCE;
    pushAddress(0x001139);
    SUB_001205();
    if (poppedEntry.value != 0x001139) return;
    popAddress();
}

void game::SUB_00113D() {
    myMapper->writeCPU(0x000B, 0x00);
    myMapper->writeCPU(0x000A, 0x10);
    x = 0x07;
    do {
        a = 0x39;
        pushAddress(0x001149);
        SUB_003BDE();
        if (poppedEntry.value != 0x001149) return;
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x000B, 0x00);
    myMapper->writeCPU(0x000A, 0x14);
    y = 0x00;
    x = myMapper->readCPU(0x0035);
    do {
        a = myMapper->readCPU(0x02C0 + y);
        opINY(1);
        pushAddress(0x00115F);
        SUB_003BDE();
        if (poppedEntry.value != 0x00115F) return;
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x000B, 0x00);
    myMapper->writeCPU(0x000A, 0x00);
    a = myMapper->readCPU(0x0037);
    opLSR_A(2);
    opORA(0xE0);
    pushAddress(0x001173);
    SUB_003C68();
    if (poppedEntry.value != 0x001173) return;
    a = myMapper->readCPU(0x0037);
    opAND(0x03);
    opORA(0x60);
    pushAddress(0x00117C);
    SUB_003C68();
    if (poppedEntry.value != 0x00117C) return;
    a = 0x6D;
    pushAddress(0x001181);
    SUB_003C68();
    if (poppedEntry.value != 0x001181) return;
    if (myMapper->readCPU(0x003C) != 0) {
        myMapper->writeCPU(0x000B, 0x00);
        myMapper->writeCPU(0x000A, 0x06);
        x = 0xFF;
        y = 0x1E;
        pushAddress(0x001194);
        SUB_003CBE();
        if (poppedEntry.value != 0x001194) return;
        myMapper->writeCPU(0x0097, myMapper->readCPU(0x003C));
        myMapper->writeCPU(0x0098, 0x00);
        a = 0x12;
        pushAddress(0x0011A1);
        SUB_0038DA();
        if (poppedEntry.value != 0x0011A1) return;
    }
    myMapper->writeCPU(0x000B, 0x01);
    myMapper->writeCPU(0x000A, 0x06);
    a = myMapper->readCPU(0x003B);
    setLoadFlag(a);
    if (!flgZ) {
        if (a < 0x05) {
            goto L_0011C6;
        }
        a = 0x01;
        pushAddress(0x0011B6);
        SUB_003B79();
        if (poppedEntry.value != 0x0011B6) return;
        opINC(0x000A, 2);
        a = 0x01;
        pushAddress(0x0011BF);
        SUB_003B79();
        if (poppedEntry.value != 0x0011BF) return;
        opDEC(0x000A, 2);
    L_0011C6:
        x = 0xFF;
        y = 0x21;
        pushAddress(0x0011CA);
        SUB_003CBE();
        if (poppedEntry.value != 0x0011CA) return;
        myMapper->writeCPU(0x0097, myMapper->readCPU(0x003B));
        myMapper->writeCPU(0x0098, 0x00);
        a = 0x12;
        pushAddress(0x0011D7);
        SUB_0038DA();
        if (poppedEntry.value != 0x0011D7) return;
    }
    popAddress();
}

void game::SUB_0011DB() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x000A, 0x00);
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_0011FB;
    }
    x = 0x0D;
    do {
        a = 0x39;
        pushAddress(0x0011F4);
        SUB_003BDE();
        if (poppedEntry.value != 0x0011F4) return;
        opDEX(1);
    } while (!flgZ);
    popAddress();
    return;
L_0011FB:
    x = myMapper->readCPU(0x0010);
    y = myMapper->readCPU(0x000F);
    pushAddress(0x0011FF);
    SUB_00379B();
    if (poppedEntry.value != 0x0011FF) return;
    SUB_003B49();
    return;
}

void game::SUB_001205() {
    myMapper->writeCPU(0x00A3, x);
    myMapper->writeCPU(0x00A2, y);
    y = 0x3F;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    opORA(0xE0);
    myMapper->writeCPU(0x0098, a);
    opINY(1);
    myMapper->writeCPU(0x000B, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(0x000A, 0x00);
    a = myMapper->readCPU(0x0098);
    pushAddress(0x00121C);
    SUB_003C68();
    if (poppedEntry.value != 0x00121C) return;
    a = 0x6A;
    pushAddress(0x001221);
    SUB_003C68();
    if (poppedEntry.value != 0x001221) return;
    opINC(0x000B, 3);
    myMapper->writeCPU(0x000A, 0x02);
    SUB_003945();
    return;
}

void game::SUB_001231() {
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x00;
    myMapper->writeCPU(0x000B, 0xF8);
    y = 0x0C;
    do {
        pushAddress(0x00123D);
        SUB_003AF0();
        if (poppedEntry.value != 0x00123D) return;
        opDEY(1);
    } while (!flgZ);
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x04);
    x = 0xD2;
    y = 0x5B;
    pushAddress(0x00124F);
    SUB_003CBE();
    if (poppedEntry.value != 0x00124F) return;
    a = 0xFF;
    myMapper->writeCPU(0x0004, a);
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_001260() {
    a = 0x01;
    SUB_001262();
    return;
}

void game::SUB_001262() {
	loopCounter = 0x00;
    do {
        opPHA();
        x = 0x00;
        y = 0x00;
        do {
            do {
                opPHA();
                opPHA();
                opPLA();
                opPLA();
                opDEX(1);
            } while (!flgZ);
            loopCounter++;
            if (loopCounter >= 0x08) {
                wait();
                loopCounter = 0x00;
            }
            opDEY(1);
        } while (!flgZ);
        opPLA();
        flgC = true;
        opSBC(0x01);
    } while (!flgZ);
    popAddress();
}

void game::SUB_001278() {
    a = myMapper->readCPU(0x000A);
    opPHA();
    a = myMapper->readCPU(0x000B);
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    myMapper->writeCPU(0x000B, 0x00);
    myMapper->writeCPU(0x000A, 0x0D);
    x = 0xD2;
    y = 0xCE;
    pushAddress(0x00128E);
    SUB_003CBE();
    if (poppedEntry.value != 0x00128E) return;
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x0034));
    myMapper->writeCPU(0x0098, 0x00);
    pushAddress(0x001299);
    SUB_003817();
    if (poppedEntry.value != 0x001299) return;
    myMapper->writeCPU(0x03EC, 0x00);
    if (myMapper->readCPU(0x03EB) != 0xEA) {
        goto L_0012AD;
    }
    myMapper->writeCPU(0x03EB, 0xF0);
L_0012AD:
    myMapper->writeCPU(0x000B, 0x01);
    myMapper->writeCPU(0x000A, 0x0C);
    x = 0x03;
    y = 0xEA;
    pushAddress(0x0012B9);
    SUB_003CBE();
    if (poppedEntry.value != 0x0012B9) return;
    x = 0xD2;
    y = 0xD2;
    pushAddress(0x0012C0);
    SUB_003CBE();
    if (poppedEntry.value != 0x0012C0) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    myMapper->writeCPU(0x000B, a);
    opPLA();
    myMapper->writeCPU(0x000A, a);
    popAddress();
}

void game::SUB_0012D5() {
    a = x;
    opPHA();
    a = y;
    opPHA();
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x03);
    x = 0xD2;
    y = 0xFF;
    pushAddress(0x0012E5);
    SUB_003CBE();
    if (poppedEntry.value != 0x0012E5) return;
    pushAddress(0x0012E8);
    SUB_00327B();
    if (poppedEntry.value != 0x0012E8) return;
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x00);
    x = 0xD2;
    y = 0x5B;
    pushAddress(0x0012F7);
    SUB_003CBE();
    if (poppedEntry.value != 0x0012F7) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_001305() {
    loopCounter = 0x00;
    a = myMapper->readCPU(0x0012);
    setLoadFlag(a);
    if (flgZ) {
        flgC = true;
        popAddress();
        return;
    }
    if (!flgN) {
        pushAddress(0x00130D);
        SUB_000F79();
        if (poppedEntry.value != 0x00130D) return;
    }
    myMapper->writeCPU(0x0012, 0x00);
    pushAddress(0x001314);
    SUB_003AFF();
    if (poppedEntry.value != 0x001314) return;
    myMapper->writeCPU(0x0003, 0x00);
    myMapper->writeCPU(0x0006, 0x88);
    pushAddress(0x00131F);
    SUB_0039DC();
    if (poppedEntry.value != 0x00131F) return;
    pushAddress(0x001322);
    SUB_0013B7();
    if (poppedEntry.value != 0x001322) return;
    x = 0xFF;
    y = 0xD2;
    pushAddress(0x001329);
    SUB_003B19();
    if (poppedEntry.value != 0x001329) return;
    a = 0xB0;
    myMapper->writeCPU(0x4000, a);
    myMapper->writeCPU(0x4004, a);
    pushAddress(0x001334);
    SUB_003AFF();
    if (poppedEntry.value != 0x001334) return;
    opINC(0x0018, 1);
    a = myMapper->readCPU(0x0018);
    opAND(0x01);
    if (!flgZ) {
        pushAddress(0x00133F);
        SUB_0032DB();
        if (poppedEntry.value != 0x00133F) return;
    }
    a = myMapper->readCPU(0x0024);
    opEOR(0xFF);
    myMapper->writeCPU(0x0024, a);
    do {
        do {
            myMapper->writeCPU(0x000B, 0x16);
            a = myMapper->readCPU(0x0024);
            opEOR(0xFF);
            myMapper->writeCPU(0x0024, a);
            opAND(0x0E);
            flgC = false;
            opADC(0x01);
            myMapper->writeCPU(0x000A, a);
            pushAddress(0x001359);
            SUB_003AC5();
            if (poppedEntry.value != 0x001359) return;
            pushAddress(0x00135C);
            SUB_000538();
            if (poppedEntry.value != 0x00135C) return;
        L_00135F:
            a = myMapper->readCPU(0x0019);
            opAND(0x08);
            if (!flgZ) {
                goto L_001393;
            }
            a = myMapper->readCPU(0x0019);
            opAND(0x04);
        } while (!flgZ);
        if (myMapper->readCPU(0x0017) != 0) {
            wait();
            goto L_00135F;
        }
        x = 0x00;
        y = 0x00;
    L_001373:
        loopCounter++;
        if (loopCounter >= 0x80) {
            wait();
            loopCounter = 0x00;
        }
        a = 0x10;
        do {
            flgC = true;
            opSBC(0x01);
        } while (!flgZ);
        a = myMapper->readCPU(0x0019);
        opAND(0x08);
        if (!flgZ) {
            goto L_001393;
        }
        a = myMapper->readCPU(0x0019);
        opAND(0x04);
    } while (!flgZ);
    if (myMapper->readCPU(0x0017) != 0) {
        goto L_001373;
    }
    opDEX(1);
    if (!flgZ) {
        goto L_001373;
    }
    opDEY(1);
    if (!flgZ) {
        goto L_001373;
    }
    flgC = true;
    if (!flgC) {
    L_001393:
        pushAddress(0x001393);
        SUB_000538();
        if (poppedEntry.value != 0x001393) return;
        a = 0x00;
        setLoadFlag(a);
        myMapper->writeCPU(0x0095, a);
        myMapper->writeCPU(0x001C, a);
        myMapper->writeCPU(0x0017, a);
        flgC = false;
    }
    pushStatus();
    pushAddress(0x0013A0);
    SUB_003AFF();
    if (poppedEntry.value != 0x0013A0) return;
    pushAddress(0x0013A3);
    SUB_0039DC();
    if (poppedEntry.value != 0x0013A3) return;
    x = 0xFF;
    y = 0xDB;
    pushAddress(0x0013AA);
    SUB_003B19();
    if (poppedEntry.value != 0x0013AA) return;
    a = 0x99;
    setLoadFlag(a);
    myMapper->writeCPU(0x0006, a);
    popStatus();
    if (!flgC) {
        goto L_0013B6;
    }
    opDEC(0x0012, 1);
L_0013B6:
    popAddress();
}

void game::SUB_0013B7() {
    pushAddress(0x0013B7);
    SUB_003A52();
    if (poppedEntry.value != 0x0013B7) return;
    myMapper->writeCPU(0x000B, 0x00);
    y = 0xFF;
    while (true) {
        x = 0x00;
    L_0013C2:
        opINY(1);
        a = myMapper->readCPU(0xD4C1 + y);
        myMapper->writeCPU(0x0098, a);
        if (a == 0xFF) {
            goto L_001413;
        }
        if (a != 0xF0) {
            goto L_0013E9;
        }
        a = y;
        opPHA();
        myMapper->writeCPU(0x0200 + x, 0x00);
        myMapper->writeCPU(0x000A, 0x01);
        opINC(0x000B, 1);
        x = 0x02;
        y = 0x00;
        pushAddress(0x0013E1);
        SUB_003CBE();
        if (poppedEntry.value != 0x0013E1) return;
        opPLA();
        y = a;
    }
L_0013E9:
    a = myMapper->readCPU(0x0098);
    if (a >= 0x90) {
        goto L_0013FA;
    }
    pushAddress(0x0013EF);
    SUB_001473();
    if (poppedEntry.value != 0x0013EF) return;
    a = myMapper->readCPU(0x0098);
    pushAddress(0x0013F4);
    SUB_001477();
    if (poppedEntry.value != 0x0013F4) return;
    goto L_0013C2;
L_0013FA:
    a = y;
    opPHA();
    a = myMapper->readCPU(0x0098);
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0x0098);
    pushAddress(0x001403);
    SUB_001473();
    if (poppedEntry.value != 0x001403) return;
    opDEY(1);
    do {
        myMapper->writeCPU(0x0200 + x, a);
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    opPLA();
    y = a;
    goto L_0013C2;
L_001413:
    //fill attribute from 23D8 using data from D4B6-D4BF, 
    // bit 4-7 is the index to attribute value from D4AF, bit 0-3 is the number of bytes to write
    myMapper->writeCPU(0x2006, 0x23);
    myMapper->writeCPU(0x2006, 0xD8);
    x = 0xFF;
    do {
        opINX(1);
        a = myMapper->readCPU(0xD4B6 + x);
        setLoadFlag(a);
        if (flgN) {
            goto L_00143E;
        }
        myMapper->writeCPU(0x0098, a);
        opLSR_A(4);
        y = a;
        a = myMapper->readCPU(0xD4AF + y);
        opPHA();
        a = myMapper->readCPU(0x0098);
        opAND(0x0F);
        y = a;
        opPLA();
        do {
            myMapper->writeCPU(0x2007, a);
            opDEY(1);
        } while (!flgZ);
    } while (flgZ);
L_00143E:
    pushAddress(0x00143E);
    SUB_003A52();
    if (poppedEntry.value != 0x00143E) return;
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x02);
    x = 0xD4;
    y = 0x9E;
    pushAddress(0x00144D);
    SUB_003B5D();
    if (poppedEntry.value != 0x00144D) return;
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x10);
    x = 0xD4;
    y = 0x98;
    pushAddress(0x00145C);
    SUB_003B5D();
    if (poppedEntry.value != 0x00145C) return;
    myMapper->writeCPU(0x000B, 0x19);
    myMapper->writeCPU(0x000A, 0x06);
    x = 0xD4;
    y = 0x86;
    pushAddress(0x00146B);
    SUB_003CBE();
    if (poppedEntry.value != 0x00146B) return;
    myMapper->writeCPU(0x0007, 0x1E);
    popAddress();
}

void game::SUB_001473() {
    opLSR_A(4);
    SUB_001477();
    return;
}

void game::SUB_001477() {
    opAND(0x0F);
    myMapper->writeCPU(0x0097, x);
    x = a;
    a = myMapper->readCPU(0xD4A4 + x);
    x = myMapper->readCPU(0x0097);
    myMapper->writeCPU(0x0200 + x, a);
    opINX(1);
    popAddress();
}

void game::SUB_001593() {
    pushAddress(0x001593);
    SUB_001AFB();
    if (poppedEntry.value != 0x001593) return;
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x0042));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x0043));
    pushAddress(0x00159E);
    SUB_00370F();
    if (poppedEntry.value != 0x00159E) return;
    pushAddress(0x0015A1);
    SUB_000E7C();
    if (poppedEntry.value != 0x0015A1) return;
    a = myMapper->readCPU(0x0060);
    x = 0x02;
    y = 0x00;
    pushAddress(0x0015AA);
    SUB_0036B4();
    if (poppedEntry.value != 0x0015AA) return;
    pushAddress(0x0015AD);
    SUB_002422();
    if (poppedEntry.value != 0x0015AD) return;
    myMapper->writeCPU(0x0003, 0xFF);
    pushAddress(0x0015B4);
    SUB_001643();
    if (poppedEntry.value != 0x0015B4) return;
    myMapper->writeCPU(0x000B, 0x02);
    myMapper->writeCPU(0x000A, 0x00);
    x = myMapper->readCPU(0x0043);
    y = myMapper->readCPU(0x0042);
    pushAddress(0x0015C3);
    SUB_003B49();
    if (poppedEntry.value != 0x0015C3) return;
    opINC(0x000A, 1);
    a = myMapper->readCPU(0x0060);
    pushAddress(0x0015CA);
    SUB_003BDE();
    if (poppedEntry.value != 0x0015CA) return;
    opINC(0x000A, 1);
    pushAddress(0x0015CF);
    SUB_001AE4();
    if (poppedEntry.value != 0x0015CF) return;
    opCMP(myMapper->readCPU(0x002E), 0x12);
    if (flgZ) {
        SUB_0015F6();
        return;
    }
    x = 0xD6;
    y = 0x40;
    myMapper->writeCPU(0x000B, 0x04);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x0015E4);
    SUB_003B5D();
    if (poppedEntry.value != 0x0015E4) return;
    myMapper->writeCPU(0x000B, 0x04);
    myMapper->writeCPU(0x000A, 0x04);
    x = 0x04;
    y = 0x71;
    pushAddress(0x0015F3);
    SUB_003B49();
    if (poppedEntry.value != 0x0015F3) return;
    SUB_0015F6();
    return;
}

void game::SUB_0015F6() {
    pushAddress(0x0015F6);
    SUB_0017DE();
    if (poppedEntry.value != 0x0015F6) return;
    pushAddress(0x0015F9);
    SUB_0018AE();
    if (poppedEntry.value != 0x0015F9) return;
    pushAddress(0x0015FC);
    SUB_0016FE();
    if (poppedEntry.value != 0x0015FC) return;
    x = 0x03;
    y = 0x14;
    myMapper->writeCPU(0x000B, 0x08);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x00160B);
    SUB_001665();
    if (poppedEntry.value != 0x00160B) return;
    x = 0x03;
    y = 0x5A;
    myMapper->writeCPU(0x000B, 0x0C);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x00161A);
    SUB_001665();
    if (poppedEntry.value != 0x00161A) return;
    x = 0x03;
    y = 0xA0;
    myMapper->writeCPU(0x000B, 0x10);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x001629);
    SUB_001665();
    if (poppedEntry.value != 0x001629) return;
    x = 0x02;
    y = 0xCE;
    myMapper->writeCPU(0x000B, 0x14);
    myMapper->writeCPU(0x000A, 0x00);
    pushAddress(0x001638);
    SUB_001665();
    if (poppedEntry.value != 0x001638) return;
    a = 0xFF;
    SUB_001B0F();
    return;
}

void game::SUB_001643() {
    pushAddress(0x001643);
    SUB_00113D();
    if (poppedEntry.value != 0x001643) return;
    myMapper->writeCPU(0x000B, 0x00);
    myMapper->writeCPU(0x000A, 0x10);
    a = myMapper->readCPU(0x02C5);
    pushAddress(0x001651);
    SUB_003BDE();
    if (poppedEntry.value != 0x001651) return;
    a = myMapper->readCPU(0x005E);
    flgC = false;
    opADC(0x43);
    pushAddress(0x001659);
    SUB_003089();
    if (poppedEntry.value != 0x001659) return;
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, 0x00);
    SUB_003B5D();
    return;
}

void game::SUB_001665() {
    myMapper->writeCPU(0x00A3, x);
    myMapper->writeCPU(0x00A2, y);
    myMapper->writeCPU(0x0041, x);
    myMapper->writeCPU(0x0040, y);
    y = 0x3F;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    opORA(0x40);
    pushAddress(0x001673);
    SUB_003C68();
    if (poppedEntry.value != 0x001673) return;
    a = 0xCF;
    pushAddress(0x001678);
    SUB_003C68();
    if (poppedEntry.value != 0x001678) return;
    pushAddress(0x00167B);
    SUB_003945();
    if (poppedEntry.value != 0x00167B) return;
    opINC(0x000B, 1);
    myMapper->writeCPU(0x000A, 0x08);
    if (myMapper->readCPU(0x0040) == myMapper->readCPU(0x0042)) {
        if (myMapper->readCPU(0x0041) != myMapper->readCPU(0x0043)) {
            goto L_00169B;
        }
        myMapper->writeCPU(0x0097, myMapper->readCPU(0x0054));
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x0055));
        goto L_0016DB;
    }
L_00169B:
    if (myMapper->readCPU(0x0061) == 0) {
        myMapper->writeCPU(0x0097, myMapper->readCPU(0x0058));
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x0059));
        y = 0x3F;
        if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
            myMapper->writeCPU(0x0097, myMapper->readCPU(0x0056));
            myMapper->writeCPU(0x0098, myMapper->readCPU(0x0057));
        }
        goto L_0016CC;
    }
    opCMP(myMapper->readCPU(0x0040), myMapper->readCPU(0x003E));
    if (!flgZ) {
        goto L_0016FD;
    }
    opCMP(myMapper->readCPU(0x0041), myMapper->readCPU(0x003F));
    if (!flgZ) {
        goto L_0016FD;
    }
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x0054));
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x0055));
L_0016CC:
    a = myMapper->readCPU(0x0098);
    opORA(myMapper->readCPU(0x0097));
    if (flgZ) {
        goto L_0016D8;
    }
    pushAddress(0x0016D2);
    SUB_003955();
    if (poppedEntry.value != 0x0016D2) return;
    pushAddress(0x0016D5);
    SUB_0038BB();
    if (poppedEntry.value != 0x0016D5) return;
L_0016D8:
    SUB_003966();
    return;
L_0016DB:
    a = myMapper->readCPU(0x0098);
    opPHA();
    a = myMapper->readCPU(0x0097);
    opPHA();
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x003C));
    myMapper->writeCPU(0x0097, 0x64);
    pushAddress(0x0016E9);
    SUB_003916();
    if (poppedEntry.value != 0x0016E9) return;
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x0097, a);
    opPLA();
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0098, a);
    pushAddress(0x0016F7);
    SUB_0038BB();
    if (poppedEntry.value != 0x0016F7) return;
    SUB_003966();
    return;
L_0016FD:
    popAddress();
}

void game::SUB_0016FE() {
    if (myMapper->readCPU(0x0069) != 0) {
        goto L_00175E;
    }
    myMapper->writeCPU(0x000B, 0x18);
    myMapper->writeCPU(0x000A, 0x02);
    a = myMapper->readCPU(0x005A);
    if (a >= 0x64) {
        opDEC(0x000A, 2);
    }
    myMapper->writeCPU(0x0097, a);
    myMapper->writeCPU(0x0098, 0x00);
    x = 0x12;
    if (myMapper->readCPU(0x005A) >= 0x64) {
        opINX(1);
    }
    a = x;
    pushAddress(0x001724);
    SUB_0038DA();
    if (poppedEntry.value != 0x001724) return;
    x = 0xD7;
    y = 0xD1;
    pushAddress(0x00172B);
    SUB_003CBE();
    if (poppedEntry.value != 0x00172B) return;
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x0030));
    myMapper->writeCPU(0x0098, 0x00);
    x = 0x12;
    if (myMapper->readCPU(0x005A) >= 0x64) {
        opINX(1);
    }
    a = x;
    pushAddress(0x001740);
    SUB_0038DA();
    if (poppedEntry.value != 0x001740) return;
    x = 0xD7;
    y = 0xD3;
    pushAddress(0x001747);
    SUB_003CBE();
    if (poppedEntry.value != 0x001747) return;
    myMapper->writeCPU(0x0097, myMapper->readCPU(0x002E));
    myMapper->writeCPU(0x0098, 0x00);
    a = 0x12;
    pushAddress(0x001754);
    SUB_0038DA();
    if (poppedEntry.value != 0x001754) return;
    x = 0xD7;
    y = 0xD7;
    pushAddress(0x00175B);
    SUB_003CBE();
    if (poppedEntry.value != 0x00175B) return;
L_00175E:
    myMapper->writeCPU(0x000B, 0x18);
    myMapper->writeCPU(0x000A, 0x0F);
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x003B));
    myMapper->writeCPU(0x0097, 0x1E);
    pushAddress(0x00176E);
    SUB_003916();
    if (poppedEntry.value != 0x00176E) return;
    myMapper->writeCPU(0x009F, myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x009E, myMapper->readCPU(0x0097));
    a = myMapper->readCPU(0x0054);
    flgC = true;
    opSBC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x0097, a);
    a = myMapper->readCPU(0x0055);
    opSBC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0098, a);
    a = 0x06;
    pushAddress(0x001788);
    SUB_0038DA();
    if (poppedEntry.value != 0x001788) return;
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x003C));
    myMapper->writeCPU(0x0097, 0x64);
    pushAddress(0x001793);
    SUB_003916();
    if (poppedEntry.value != 0x001793) return;
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(myMapper->readCPU(0x009E));
    myMapper->writeCPU(0x0097, a);
    a = myMapper->readCPU(0x0098);
    opADC(myMapper->readCPU(0x009F));
    myMapper->writeCPU(0x0098, a);
    opORA(myMapper->readCPU(0x0097));
    if (!flgZ) {
        a = myMapper->readCPU(0x0098);
        opPHA();
        x = 0xD7;
        y = 0xDB;
        pushAddress(0x0017AE);
        SUB_003CBE();
        if (poppedEntry.value != 0x0017AE) return;
        opPLA();
        myMapper->writeCPU(0x0098, a);
        a = 0x05;
        pushAddress(0x0017B6);
        SUB_0038DA();
        if (poppedEntry.value != 0x0017B6) return;
    }
    if (myMapper->readCPU(0x005D) == 0) {
        goto L_0017D0;
    }
    myMapper->writeCPU(0x000B, 0x16);
    myMapper->writeCPU(0x000A, 0x14);
    a = myMapper->readCPU(0x005D);
    flgC = false;
    opADC(0x38);
    pushAddress(0x0017CA);
    SUB_003089();
    if (poppedEntry.value != 0x0017CA) return;
    pushAddress(0x0017CD);
    SUB_003B5D();
    if (poppedEntry.value != 0x0017CD) return;
L_0017D0:
    popAddress();
}

void game::SUB_0017DE() {
    myMapper->writeCPU(0x0069, 0x00);
    myMapper->writeCPU(0x000B, 0x08);
    myMapper->writeCPU(0x0068, 0x00);
    x = 0x00;
    do {
        do {
            do {
                a = myMapper->readCPU(0x041E + x);
                if (a == 0xFF) {
                    goto L_0017FB;
                }
                if (a != 0x00) {
                    goto L_0017FC;
                }
                opINX(2);
            } while (!flgZ);
        L_0017FB:
            popAddress();
            return;
        L_0017FC:
            myMapper->writeCPU(0x000A, 0x10);
            opINC(0x0068, 1);
            a = myMapper->readCPU(0x0068);
            if (a >= 0x08) {
                goto L_001827;
            }
            a = x;
            opPHA();
            a = myMapper->readCPU(0x041E + x);
            pushAddress(0x00180D);
            SUB_003089();
            if (poppedEntry.value != 0x00180D) return;
            pushAddress(0x001810);
            SUB_003B5D();
            if (poppedEntry.value != 0x001810) return;
            opPLA();
            x = a;
            opINX(1);
            myMapper->writeCPU(0x000A, 0x1A);
            a = myMapper->readCPU(0x041E + x);
            opINX(1);
            pushAddress(0x00181E);
            SUB_00182B();
            if (poppedEntry.value != 0x00181E) return;
            opINC(0x000B, 2);
        } while (!flgZ);
    L_001827:
        opINX(2);
    } while (!flgZ);
    SUB_00182B();
    return;
}

void game::SUB_00182B() {
    if (a < 0x10) {
        goto L_001849;
    }
    myMapper->writeCPU(0x0069, a);
    opDEC(0x000A, 2);
    myMapper->writeCPU(0x009F, x);
    opAND(0x0F);
    opASL_A(2);
    opADC(0x54);
    y = a;
    a = 0x00;
    opADC(0xD8);
    x = a;
    pushAddress(0x001843);
    SUB_003B5D();
    if (poppedEntry.value != 0x001843) return;
    x = myMapper->readCPU(0x009F);
    popAddress();
    return;
L_001849:
    flgC = false;
    opADC(0x30);
    pushAddress(0x00184C);
    SUB_003C68();
    if (poppedEntry.value != 0x00184C) return;
    a = 0xCE;
    SUB_003C68();
    return;
}

void game::SUB_001860() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = myMapper->readCPU(0x0098);
    opAND(0x3F);
    x = a;
    a = myMapper->readCPU(0x0098);
    opAND(0xC0);
    if (!flgZ) {
        if (a == 0x40) {
            goto L_001890;
        }
        if (a == 0x80) {
            goto L_00189B;
        }
        a = x;
        pushAddress(0x001878);
        SUB_003BDE();
        if (poppedEntry.value != 0x001878) return;
        a = 0x39;
        pushAddress(0x00187D);
        SUB_003C0C();
        if (poppedEntry.value != 0x00187D) return;
        a = 0x39;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_0018A4;
        }
    }
    a = x;
    pushAddress(0x001885);
    SUB_003BDE();
    if (poppedEntry.value != 0x001885) return;
    opINX(1);
    a = x;
    pushAddress(0x00188A);
    SUB_003BDE();
    if (poppedEntry.value != 0x00188A) return;
    opINX(1);
    if (!flgZ) {
        goto L_0018A7;
    }
L_001890:
    a = x;
    pushAddress(0x001891);
    SUB_003BDE();
    if (poppedEntry.value != 0x001891) return;
    a = x;
    pushAddress(0x001895);
    SUB_003BDE();
    if (poppedEntry.value != 0x001895) return;
    goto L_0018A7;
L_00189B:
    a = x;
    pushAddress(0x00189C);
    SUB_003BDE();
    if (poppedEntry.value != 0x00189C) return;
    a = x;
    pushAddress(0x0018A0);
    SUB_003C0C();
    if (poppedEntry.value != 0x0018A0) return;
    a = x;
L_0018A4:
    pushAddress(0x0018A4);
    SUB_003C0C();
    if (poppedEntry.value != 0x0018A4) return;
L_0018A7:
    a = x;
    pushAddress(0x0018A8);
    SUB_003C0C();
    if (poppedEntry.value != 0x0018A8) return;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_0018AE() {
    myMapper->writeCPU(0x005D, 0x00);
    pushAddress(0x0018B2);
    SUB_001A38();
    if (poppedEntry.value != 0x0018B2) return;
    if (flgC) {
        a = myMapper->readCPU(0x0030);
        if (a != 0x19) {
            flgC = false;
            opADC(0x09);
            x = 0xFF;
            do {
                opINX(1);
                flgC = true;
                opSBC(0x0A);
            } while (flgC);
            a = x;
            myMapper->writeCPU(0x0098, a);
            y = a;
            opASL_A(2);
            flgC = false;
            opADC(myMapper->readCPU(0x0098));
            opASL_A(1);
        }
        myMapper->writeCPU(0x005A, a);
        if (myMapper->readCPU(0x002E) >= 0x05) {
            pushAddress(0x0018DA);
            SUB_0019ED();
            if (poppedEntry.value != 0x0018DA) return;
        }
        else {
            myMapper->writeCPU(0x00A0, myMapper->readCPU(0x005A));
            myMapper->writeCPU(0x00A1, 0x00);
            a = myMapper->readCPU(0x002E);
            flgC = false;
            opADC(0x02);
            x = a;
            do {
                opASL_M(0x00A0, 1);
                opROL_M(0x00A1, 1);
                opDEX(1);
            } while (!flgZ);
            pushAddress(0x0018F5);
            SUB_001AC0();
            if (poppedEntry.value != 0x0018F5) return;
            myMapper->writeCPU(0x005B, myMapper->readCPU(0x00A0));
            myMapper->writeCPU(0x005C, myMapper->readCPU(0x00A1));
            if (myMapper->readCPU(0x00A1) == 0) {
                a = myMapper->readCPU(0x00A0);
                flgC = true;
                opSBC(0xC8);
                if (!flgC) {
                    goto L_00190E;
                }
            }
            pushAddress(0x00190B);
            SUB_0019ED();
            if (poppedEntry.value != 0x00190B) return;
        }
    }
L_00190E:
    myMapper->writeCPU(0x00A0, myMapper->readCPU(0x005B));
    myMapper->writeCPU(0x00A1, myMapper->readCPU(0x005C));
    if (myMapper->readCPU(0x0061) != 0) {
        if (myMapper->readCPU(0x023F) != 0) {
            goto L_00193B;
        }
        myMapper->writeCPU(0x009E, myMapper->readCPU(0x00A0));
        myMapper->writeCPU(0x009F, myMapper->readCPU(0x00A1));
        opASL_M(0x00A0, 1);
        opROL_M(0x00A1, 1);
        a = myMapper->readCPU(0x00A0);
        flgC = false;
        opADC(myMapper->readCPU(0x009E));
        myMapper->writeCPU(0x00A0, a);
        a = myMapper->readCPU(0x00A1);
        opADC(myMapper->readCPU(0x009F));
        myMapper->writeCPU(0x00A1, a);
        goto L_00193F;
    L_00193B:
        opASL_M(0x00A0, 1);
        opROL_M(0x00A1, 1);
    L_00193F:
        opASL_M(0x00A0, 1);
        opROL_M(0x00A1, 1);
        pushAddress(0x001943);
        SUB_001A92();
        if (poppedEntry.value != 0x001943) return;
        myMapper->writeCPU(0x0098, myMapper->readCPU(0x003B));
        myMapper->writeCPU(0x0097, 0x1E);
        pushAddress(0x00194E);
        SUB_003916();
        if (poppedEntry.value != 0x00194E) return;
        a = myMapper->readCPU(0x00A0);
        flgC = false;
        opADC(myMapper->readCPU(0x0097));
        myMapper->writeCPU(0x00A0, a);
        a = myMapper->readCPU(0x00A1);
        opADC(myMapper->readCPU(0x0098));
        myMapper->writeCPU(0x00A1, a);
        x = myMapper->readCPU(0x00A1);
        y = myMapper->readCPU(0x00A0);
        myMapper->writeCPU(0x0055, x);
        myMapper->writeCPU(0x0054, y);
        myMapper->writeCPU(0x0059, x);
        myMapper->writeCPU(0x0058, y);
        myMapper->writeCPU(0x0057, x);
        myMapper->writeCPU(0x0056, y);
        popAddress();
        return;
    }
    opASL_M(0x00A0, 1);
    opROL_M(0x00A1, 1);
    pushAddress(0x001973);
    SUB_001A92();
    if (poppedEntry.value != 0x001973) return;
    myMapper->writeCPU(0x0098, myMapper->readCPU(0x003B));
    myMapper->writeCPU(0x0097, 0x0A);
    pushAddress(0x00197E);
    SUB_003916();
    if (poppedEntry.value != 0x00197E) return;
    a = myMapper->readCPU(0x00A0);
    flgC = false;
    opADC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x00A0, a);
    a = myMapper->readCPU(0x00A1);
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x00A1, a);
    if (myMapper->readCPU(0x023F) != 0) {
        goto L_0019B3;
    }
    myMapper->writeCPU(0x0058, myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x0059, myMapper->readCPU(0x00A1));
    opASL_M(0x00A0, 1);
    opROL_M(0x00A1, 1);
    a = myMapper->readCPU(0x00A0);
    flgC = false;
    opADC(myMapper->readCPU(0x0058));
    myMapper->writeCPU(0x0054, a);
    a = myMapper->readCPU(0x00A1);
    opADC(myMapper->readCPU(0x0059));
    myMapper->writeCPU(0x0055, a);
    a = 0x00;
    myMapper->writeCPU(0x0056, a);
    myMapper->writeCPU(0x0057, a);
    popAddress();
    return;
L_0019B3:
    myMapper->writeCPU(0x0056, myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x0057, myMapper->readCPU(0x00A1));
    myMapper->writeCPU(0x00A0, myMapper->readCPU(0x005B));
    myMapper->writeCPU(0x00A1, myMapper->readCPU(0x005C));
    pushAddress(0x0019C3);
    SUB_001A92();
    if (poppedEntry.value != 0x0019C3) return;
    a = myMapper->readCPU(0x00A0);
    flgC = false;
    opADC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x00A0, a);
    a = myMapper->readCPU(0x00A1);
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x0058, myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x0059, myMapper->readCPU(0x00A1));
    opASL_M(0x00A0, 1);
    opROL_M(0x00A1, 1);
    a = myMapper->readCPU(0x00A0);
    flgC = false;
    opADC(myMapper->readCPU(0x0056));
    myMapper->writeCPU(0x0054, a);
    a = myMapper->readCPU(0x00A1);
    opADC(myMapper->readCPU(0x0057));
    myMapper->writeCPU(0x0055, a);
    popAddress();
}

void game::SUB_0019ED() {
    myMapper->writeCPU(0x005D, 0x05);
    a = myMapper->readCPU(0x002E);
    if (a >= 0x0D) {
        myMapper->writeCPU(0x005B, 0x20);
        myMapper->writeCPU(0x005C, 0x03);
        popAddress();
        return;
    }
    opDEC(0x005D, 1);
    if (a >= 0x0B) {
        myMapper->writeCPU(0x005B, 0x58);
        myMapper->writeCPU(0x005C, 0x02);
        popAddress();
        return;
    }
    opDEC(0x005D, 1);
    if (a >= 0x08) {
        myMapper->writeCPU(0x005B, 0x90);
        myMapper->writeCPU(0x005C, 0x01);
        popAddress();
        return;
    }
    opDEC(0x005D, 1);
    if (a < 0x06) {
        goto L_001A2D;
    }
    myMapper->writeCPU(0x005B, 0x2C);
    myMapper->writeCPU(0x005C, 0x01);
    popAddress();
    return;
L_001A2D:
    opDEC(0x005D, 1);
    myMapper->writeCPU(0x005B, 0xC8);
    myMapper->writeCPU(0x005C, 0x00);
    popAddress();
}

void game::SUB_001A38() {
    a = myMapper->readCPU(0x0069);
    setLoadFlag(a);
    if (flgZ) {
        flgC = true;
        popAddress();
        return;
    }
    if (a == 0x12) {
        myMapper->writeCPU(0x005D, 0x01);
        x = 0x00;
        y = 0xC8;
    }
    else {
        if (a != 0x11) {
            goto L_001A5C;
        }
        myMapper->writeCPU(0x005D, 0x0A);
        x = 0x04;
        y = 0xB0;
        goto L_001A8C;
    L_001A5C:
        a = myMapper->readCPU(0x0068);
        flgC = false;
        opADC(0x04);
        myMapper->writeCPU(0x005D, a);
        x = 0x03;
        y = 0x20;
        if (myMapper->readCPU(0x0068) == 0x01) {
            goto L_001A8C;
        }
        myMapper->writeCPU(0x00A1, x);
        myMapper->writeCPU(0x00A0, y);
        myMapper->writeCPU(0x009F, x);
        myMapper->writeCPU(0x009E, y);
        x = myMapper->readCPU(0x0068);
        opDEX(1);
        do {
            a = myMapper->readCPU(0x00A0);
            flgC = false;
            opADC(myMapper->readCPU(0x009E));
            myMapper->writeCPU(0x00A0, a);
            a = myMapper->readCPU(0x00A1);
            opADC(myMapper->readCPU(0x009F));
            myMapper->writeCPU(0x00A1, a);
            opDEX(1);
        } while (!flgZ);
        x = myMapper->readCPU(0x00A1);
        y = myMapper->readCPU(0x00A0);
    }
L_001A8C:
    myMapper->writeCPU(0x005C, x);
    myMapper->writeCPU(0x005B, y);
    flgC = false;
    popAddress();
}

void game::SUB_001A92() {
    a = 0x09;
    flgC = false;
    opADC(myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x00A0, a);
    a = 0x00;
    opADC(myMapper->readCPU(0x00A1));
    myMapper->writeCPU(0x00A1, a);
    pushAddress(0x001A9F);
    SUB_001AC0();
    if (poppedEntry.value != 0x001A9F) return;
    a = myMapper->readCPU(0x00A1);
    opPHA();
    a = myMapper->readCPU(0x00A0);
    opPHA();
    opASL_M(0x00A0, 1);
    opROL_M(0x00A1, 1);
    opASL_M(0x00A0, 1);
    opROL_M(0x00A1, 1);
    opPLA();
    flgC = false;
    opADC(myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x00A0, a);
    opPLA();
    opADC(myMapper->readCPU(0x00A1));
    myMapper->writeCPU(0x00A1, a);
    opASL_M(0x00A0, 1);
    opROL_M(0x00A1, 1);
    popAddress();
}

void game::SUB_001AC0() {
    myMapper->writeCPU(0x0099, myMapper->readCPU(0x00A0));
    myMapper->writeCPU(0x009A, myMapper->readCPU(0x00A1));
    a = 0xFF;
    myMapper->writeCPU(0x00A1, a);
    myMapper->writeCPU(0x00A0, a);
    do {
        opINC(0x00A0, 1);
        if (!flgZ) {
            goto L_001AD4;
        }
        opINC(0x00A1, 1);
    L_001AD4:
        a = myMapper->readCPU(0x0099);
        flgC = true;
        opSBC(0x0A);
        myMapper->writeCPU(0x0099, a);
        a = myMapper->readCPU(0x009A);
        opSBC(0x00);
        myMapper->writeCPU(0x009A, a);
    } while (!flgN);
    popAddress();
}

void game::SUB_001AE4() {
    if (myMapper->readCPU(0x023A) == 0) {
        goto L_001AFA;
    }
    x = 0x0F;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_001AFA;
        }
        pushAddress(0x001AF3);
        SUB_001860();
        if (poppedEntry.value != 0x001AF3) return;
        opINC(0x000A, 1);
    } while (!flgZ);
L_001AFA:
    popAddress();
}

void game::SUB_001AFB() {
    if (myMapper->readCPU(0x0012) != 0) {
        goto L_001B0C;
    }
    myMapper->writeCPU(0x0005, 0x24);
    myMapper->writeCPU(0x0007, 0x0E);
    myMapper->writeCPU(0x0006, 0x98);
    popAddress();
    return;
L_001B0C:
    SUB_0039DC();
    return;
}

void game::SUB_001B0F() {
    bool firstLoop = true;
    myMapper->writeCPU(0x0098, a);
    if (myMapper->readCPU(0x0012) == 0) {
        goto L_001B18;
    }
    SUB_000522();
    return;
    while (true) {
        do {
        L_001B18:
            if (firstLoop) firstLoop = false;
			else wait();
            if (myMapper->readCPU(0x001A) != 0) {
                goto L_001B3E;
            }
            a = myMapper->readCPU(0x0019);
            opAND(0x04);
        } while (flgZ);
        a = myMapper->readCPU(0x0006);
        opEOR(0x01);
        myMapper->writeCPU(0x0006, a);
        a = myMapper->readCPU(0x0003);
        opEOR(myMapper->readCPU(0x0098));
        myMapper->writeCPU(0x0003, a);
        a = myMapper->readCPU(0x0007);
        opEOR(0x10);
        myMapper->writeCPU(0x0007, a);
        myMapper->writeCPU(0x0004, 0xFF);
        pushAddress(0x001B38);
        SUB_000538();
        if (poppedEntry.value != 0x001B38) return;
    }
L_001B3E:
    pushAddress(0x001B3E);
    SUB_000538();
    if (poppedEntry.value != 0x001B3E) return;
    pushAddress(0x001B41);
    SUB_0039DC();
    if (poppedEntry.value != 0x001B41) return;
    myMapper->writeCPU(0x0005, 0x20);
    pushAddress(0x001B48);
    SUB_003A52();
    if (poppedEntry.value != 0x001B48) return;
    a = 0x99;
    myMapper->writeCPU(0x0006, a);
    popAddress();
}

void game::SUB_001B50() {
    a = 0x00;
    myMapper->writeCPU(0x0076, a);
    myMapper->writeCPU(0x007C, a);
    myMapper->writeCPU(0x007E, a);
    myMapper->writeCPU(0x0084, a);
    a = myMapper->readCPU(0x0039);
    flgC = false;
    opADC(0x01);
    opAND(0x03);
    myMapper->writeCPU(0x006E, a);
    x = 0x03;
    do {
        a = x;
        opPHA();
        opINC(0x0039, 1);
        a = myMapper->readCPU(0x0039);
        opAND(0x03);
        myMapper->writeCPU(0x0039, a);
        pushAddress(0x001B6F);
        SUB_00346A();
        if (poppedEntry.value != 0x001B6F) return;
        a = myMapper->readCPU(0x000F);
        myMapper->writeCPU(0x0040, a);
        myMapper->writeCPU(0x00A2, a);
        a = myMapper->readCPU(0x0010);
        myMapper->writeCPU(0x0041, a);
        myMapper->writeCPU(0x00A3, a);
        pushAddress(0x001B7E);
        SUB_00370F();
        if (poppedEntry.value != 0x001B7E) return;
        a = myMapper->readCPU(0x0060);
        x = 0x02;
        y = 0x00;
        pushAddress(0x001B87);
        SUB_0036B4();
        if (poppedEntry.value != 0x001B87) return;
        a = 0x00;
        y = 0x2C;
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
        opINY(1);
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, 0xFF);
        pushAddress(0x001B9E);
        SUB_001E10();
        if (poppedEntry.value != 0x001B9E) return;
        pushAddress(0x001BA1);
        SUB_001E83();
        if (poppedEntry.value != 0x001BA1) return;
        pushAddress(0x001BA4);
        SUB_001EB7();
        if (poppedEntry.value != 0x001BA4) return;
        opPLA();
        x = a;
        opDEX(1);
    } while (!flgZ);
    opINC(0x0039, 1);
    a = myMapper->readCPU(0x0039);
    opAND(0x03);
    myMapper->writeCPU(0x0039, a);
    if (myMapper->readCPU(0x0076) >= 0x03) {
        if (myMapper->readCPU(0x0039) == 0) {
            goto L_001BC9;
        }
        myMapper->writeCPU(0x0047, 0x04);
        a = 0x00;
        pushAddress(0x001BC4);
        SUB_001C24();
        if (poppedEntry.value != 0x001BC4) return;
        if (flgC) {
            goto L_001BD0;
        }
    L_001BC9:
        pushAddress(0x001BC9);
        SUB_00240D();
        if (poppedEntry.value != 0x001BC9) return;
        a = 0x05;
        flgC = false;
        popAddress();
        return;
    }
L_001BD0:
    myMapper->writeCPU(0x0047, 0x04);
    x = 0x00;
    if (myMapper->readCPU((0x0076 + x) & 0x00ff) != 0) {
        do {
            opINX(1);
            if (myMapper->readCPU((0x0076 + x) & 0x00ff) == 0xFF) {
                goto L_001BF0;
            }
            a = x;
            opPHA();
            a = myMapper->readCPU((0x0076 + x) & 0x00ff);
            pushAddress(0x001BE5);
            SUB_001C24();
            if (poppedEntry.value != 0x001BE5) return;
            opPLA();
            x = a;
        } while (flgC);
        a = 0x00;
        flgC = false;
        popAddress();
        return;
    }
L_001BF0:
    opDEC(0x0047, 1);
    if (myMapper->readCPU(0x007E) != 0) {
        a = myMapper->readCPU(0x007F);
        pushAddress(0x001BF8);
        SUB_001C24();
        if (poppedEntry.value != 0x001BF8) return;
        if (!flgC) {
            pushAddress(0x001BFD);
            SUB_001F76();
            if (poppedEntry.value != 0x001BFD) return;
            flgC = true;
            popAddress();
            return;
        }
    }
    opDEC(0x0047, 1);
    if (myMapper->readCPU(0x007C) != 0) {
        a = myMapper->readCPU(0x007D);
        pushAddress(0x001C0A);
        SUB_001C24();
        if (poppedEntry.value != 0x001C0A) return;
        if (!flgC) {
            flgC = true;
            popAddress();
            return;
        }
    }
    opDEC(0x0047, 1);
    a = myMapper->readCPU(0x0084);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x0085);
        pushAddress(0x001C19);
        SUB_001C24();
        if (poppedEntry.value != 0x001C19) return;
        if (flgC) {
            goto L_001C20;
        }
        flgC = true;
        popAddress();
        return;
    }
L_001C20:
    opDEC(0x0047, 1);
    flgC = true;
    popAddress();
}

void game::SUB_001C24() {
    myMapper->writeCPU(0x0048, a);
    pushAddress(0x001C26);
    SUB_00346A();
    if (poppedEntry.value != 0x001C26) return;
    a = myMapper->readCPU(0x000F);
    myMapper->writeCPU(0x0040, a);
    myMapper->writeCPU(0x00A2, a);
    a = myMapper->readCPU(0x0010);
    myMapper->writeCPU(0x0041, a);
    myMapper->writeCPU(0x00A3, a);
    pushAddress(0x001C35);
    SUB_00370F();
    if (poppedEntry.value != 0x001C35) return;
    y = 0x30;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (!flgZ) {
        if (a != 0xFF) {
            goto L_001C5D;
        }
        y = 0x3E;
        if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
            if (myMapper->readCPU(0x0047) != 0x04) {
                goto L_001C7D;
            }
        }
        a = myMapper->readCPU(0x0048);
        opORA(myMapper->readCPU(0x0012));
        if (flgZ) {
            pushAddress(0x001C54);
            SUB_001D9E();
            if (poppedEntry.value != 0x001C54) return;
        }
        else {
            pushAddress(0x001C5A);
            SUB_001C8E();
            if (poppedEntry.value != 0x001C5A) return;
        }
    L_001C5D:
        y = 0x30;
        a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
        if (a == myMapper->readCPU(0x0047)) {
            goto L_001C77;
        }
        if (a == 0x00) {
            a = myMapper->readCPU(0x0047);
            if (a == 0x04) {
                a = 0x01;
                y = 0x3C;
                myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
            }
        }
    }
    flgC = true;
    popAddress();
    return;
L_001C77:
    if (a == 0x04) {
        goto L_001C85;
    }
    flgC = false;
    popAddress();
    return;
L_001C7D:
    a = 0x00;
    y = 0x30;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    flgC = true;
    popAddress();
    return;
L_001C85:
    pushAddress(0x001C85);
    SUB_00240D();
    if (poppedEntry.value != 0x001C85) return;
    a = 0x01;
    myMapper->writeCPU(0x0061, a);
    flgC = false;
    popAddress();
}

void game::SUB_001C8E() {
    y = 0x31;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    opAND(0x04);
    if (flgZ) {
        y = 0x2C;
        if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
            a = 0x04;
            setLoadFlag(a);
            if (!flgZ) {
                goto L_001CCF;
            }
        }
        y = 0x3C;
        if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
            pushAddress(0x001CA6);
            SUB_000CDB();
            if (poppedEntry.value != 0x001CA6) return;
            y = 0x31;
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            opAND(0x01);
            if (flgZ) {
                if (myMapper->readCPU(0x003B) >= 0x05) {
                    goto L_001CCD;
                }
            }
            if (myMapper->readCPU(0x005F) == 0) {
                goto L_001CC3;
            }
            y = 0x42;
            if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) < 0x03) {
                goto L_001CCD;
            }
        L_001CC3:
            pushAddress(0x001CC3);
            SUB_001D3B();
            if (poppedEntry.value != 0x001CC3) return;
            if (!flgC) {
                goto L_001CCF;
            }
            pushAddress(0x001CC8);
            SUB_001CD4();
            if (poppedEntry.value != 0x001CC8) return;
            if (!flgC) {
                goto L_001CCF;
            }
        }
    }
L_001CCD:
    a = 0x00;
L_001CCF:
    y = 0x30;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    popAddress();
}

void game::SUB_001CD4() {
    y = 0x2F;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (!flgZ) {
        a = myMapper->readCPU(0x0084);
        if (a < 0x02) {
            y = 0x31;
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            opAND(0x01);
            if (!flgZ) {
                a = myMapper->readCPU(0x0060);
                flgC = true;
                opSBC(myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
                opAND(0x30);
                if (flgZ) {
                    goto L_001CF8;
                }
                popAddress();
                return;
            }
            a = myMapper->readCPU(0x005F);
            setLoadFlag(a);
            if (flgZ) {
                goto L_001CF8;
            }
        }
    }
    flgC = true;
    popAddress();
    return;
L_001CF8:
    a = myMapper->readCPU(0x0086);
    myMapper->writeCPU(0x009D, a);
    myMapper->writeCPU(0x009C, a);
    opDEC(0x009C, 1);
    x = 0x00;
    pushAddress(0x001D02);
    SUB_0036FC();
    if (poppedEntry.value != 0x001D02) return;
    if (flgC) {
        a = myMapper->readCPU(0x009C);
        opADC(0x03);
        myMapper->writeCPU(0x009C, a);
        x = 0x00;
        pushAddress(0x001D0F);
        SUB_0036FC();
        if (poppedEntry.value != 0x001D0F) return;
        if (flgC) {
            myMapper->writeCPU(0x009C, myMapper->readCPU(0x009D));
            x = 0x00;
            pushAddress(0x001D1A);
            SUB_0036FC();
            if (poppedEntry.value != 0x001D1A) return;
            if (!flgC) {
                opINC(0x009C, 1);
                x = 0x00;
                pushAddress(0x001D23);
                SUB_0036FC();
                if (poppedEntry.value != 0x001D23) return;
                if (flgC) {
                    goto L_001D31;
                }
                opINC(0x009C, 1);
                x = 0x00;
                pushAddress(0x001D2C);
                SUB_0036FC();
                if (poppedEntry.value != 0x001D2C) return;
                if (!flgC) {
                    goto L_001D39;
                }
            }
        L_001D31:
            myMapper->writeCPU(0x0045, myMapper->readCPU(0x009D));
            a = 0x01;
            flgC = false;
            popAddress();
            return;
        }
    }
L_001D39:
    flgC = true;
    popAddress();
}

void game::SUB_001D3B() {
    y = 0x2E;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    setLoadFlag(a);
    if (!flgZ) {
        y = 0x2D;
        a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgZ) {
            a = myMapper->readCPU(0x0060);
            pushAddress(0x001D49);
            SUB_001FB3();
            if (poppedEntry.value != 0x001D49) return;
            if (!flgC) {
                goto L_001D98;
            }
            y = 0x31;
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            opAND(0x01);
            if (flgZ) {
                goto L_001D65;
            }
            a = myMapper->readCPU(0x0060);
            if (a >= 0x30) {
                goto L_001D69;
            }
            flgC = true;
            opSBC(myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
            opAND(0x30);
            if (flgZ) {
                goto L_001D69;
            }
        }
    }
    do {
        flgC = true;
        popAddress();
        return;
    L_001D65:
        a = myMapper->readCPU(0x005F);
        setLoadFlag(a);
    } while (!flgZ);
L_001D69:
    a = myMapper->readCPU(0x0060);
    if (a < 0x30) {
        myMapper->writeCPU(0x009C, a);
        opINC(0x009C, 1);
        x = 0x00;
        pushAddress(0x001D75);
        SUB_0036FC();
        if (poppedEntry.value != 0x001D75) return;
        if (!flgC) {
            opDEC(0x009C, 2);
            x = 0x00;
            pushAddress(0x001D80);
            SUB_0036FC();
            if (poppedEntry.value != 0x001D80) return;
            if (!flgC) {
                goto L_001D9C;
            }
        }
        if (myMapper->readCPU(0x0242) != 0) {
            goto L_001D98;
        }
        x = 0x0E;
        do {
            opINX(1);
            a = myMapper->readCPU(0x0200 + x);
            if (a < 0x10) {
                goto L_001D9C;
            }
        } while (a != 0xFF);
    }
L_001D98:
    a = 0x02;
    flgC = false;
    popAddress();
    return;
L_001D9C:
    flgC = true;
    popAddress();
}

void game::SUB_001D9E() {
    myMapper->writeCPU(0x000B, myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x008F));
    a = 0x02;
    pushAddress(0x001DA8);
    SUB_003A8A();
    if (poppedEntry.value != 0x001DA8) return;
    pushAddress(0x001DAB);
    SUB_003263();
    if (poppedEntry.value != 0x001DAB) return;
    while (true) {
        pushAddress(0x001DAE);
        SUB_000538();
        if (poppedEntry.value != 0x001DAE) return;
        myMapper->writeCPU(0x006A, 0x98);
        myMapper->writeCPU(0x006B, 0xCC);
        myMapper->writeCPU(0x006C, 0x00);
        myMapper->writeCPU(0x006D, 0x04);
        pushAddress(0x001DC1);
        SUB_000C7F();
        if (poppedEntry.value != 0x001DC1) return;
		bool firstLoop = true;
        do {
			if (firstLoop) firstLoop = false;
			else wait();

            pushAddress(0x001DC4);
            SUB_000C61();
            if (poppedEntry.value != 0x001DC4) return;
            pushAddress(0x001DC7);
            SUB_00053F();
            if (poppedEntry.value != 0x001DC7) return;
        } while (myMapper->readCPU(0x001A) == 0);
        a = myMapper->readCPU(0x006C);
        setLoadFlag(a);
        if (!flgZ) {
            if (a != 0x01) {
                goto L_001DE2;
            }
            y = 0x2F;
            if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
                goto L_001E0A;
            }
            pushAddress(0x001DDC);
            SUB_001F07();
            if (poppedEntry.value != 0x001DDC) return;
            goto L_001E00;
        L_001DE2:
            opCMP(a, 0x02);
            if (flgZ) {
                y = 0x2E;
                a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_001E0A;
                }
                if (!flgZ) {
                    goto L_001E00;
                }
            }
            opCMP(a, 0x03);
            if (!flgZ) {
                goto L_001DFA;
            }
            y = 0x2D;
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            setLoadFlag(a);
            if (flgZ) {
                goto L_001E0A;
            }
            if (!flgZ) {
                goto L_001E00;
            }
        L_001DFA:
            y = 0x2C;
            if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
                goto L_001E0A;
            }
        }
    L_001E00:
        a = myMapper->readCPU(0x006C);
        y = 0x30;
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
        pushAddress(0x001E06);
        SUB_001231();
        if (poppedEntry.value != 0x001E06) return;
        popAddress();
        return;
    L_001E0A:
        pushAddress(0x001E0A);
        SUB_0012D5();
        if (poppedEntry.value != 0x001E0A) return;
    }
    SUB_001E10();
    return;
}

void game::SUB_001E10() {
    myMapper->writeCPU(0x0061, 0x01);
    pushAddress(0x001E14);
    SUB_002422();
    if (poppedEntry.value != 0x001E14) return;
    if (flgC) {
        goto L_001E1C;
    }
    pushAddress(0x001E19);
    SUB_001E21();
    if (poppedEntry.value != 0x001E19) return;
L_001E1C:
    myMapper->writeCPU(0x0061, 0x00);
    popAddress();
}

void game::SUB_001E21() {
    y = 0x3C;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
        myMapper->writeCPU(0x000F, myMapper->readCPU(0x0040));
        myMapper->writeCPU(0x0010, myMapper->readCPU(0x0041));
        pushAddress(0x001E2F);
        SUB_00370F();
        if (poppedEntry.value != 0x001E2F) return;
        myMapper->writeCPU(0x0061, 0xFF);
        pushAddress(0x001E36);
        SUB_000E7C();
        if (poppedEntry.value != 0x001E36) return;
        opINC(0x0061, 1);
        a = myMapper->readCPU(0x0060);
        x = 0x02;
        y = 0x00;
        pushAddress(0x001E41);
        SUB_0036B4();
        if (poppedEntry.value != 0x001E41) return;
        x = myMapper->readCPU(0x004E);
        opDEX(1);
        if (flgN) {
            goto L_001E66;
        }
        x = 0x14;
        do {
            a = myMapper->readCPU(0x0200 + x);
            if (a == 0xFF) {
                goto L_001E6E;
            }
            opINX(1);
            opAND(0x3F);
            myMapper->writeCPU(0x0098, a);
            y = 0x00;
        L_001E5A:
            a = myMapper->readCPU(0x0471 + y);
        } while (a == 0xFF);
        opINY(1);
        if (a != myMapper->readCPU(0x0098)) {
            goto L_001E5A;
        }
    L_001E66:
        y = 0x3C;
        myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, 0x01);
    }
    flgC = true;
    popAddress();
    return;
L_001E6E:
    opINC(0x0076, 1);
    x = myMapper->readCPU(0x0076);
    myMapper->writeCPU((0x0076 + x) & 0x00ff, myMapper->readCPU(0x0039));
    opINX(1);
    myMapper->writeCPU((0x0076 + x) & 0x00ff, 0xFF);
    y = 0x2C;
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, 0x01);
    flgC = false;
    popAddress();
}

void game::SUB_001E83() {
    y = 0x3E;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
        x = 0x00;
        a = myMapper->readCPU(0x0060);
        pushAddress(0x001E8D);
        SUB_00353E();
        if (poppedEntry.value != 0x001E8D) return;
        opCMP(a, 0x03);
        if (flgC) {
            if (flgZ) {
                goto L_001EA8;
            }
            if (myMapper->readCPU(0x0034) == 0) {
                goto L_001EA8;
            }
            myMapper->writeCPU(0x007E, 0x01);
            myMapper->writeCPU(0x007F, myMapper->readCPU(0x0039));
            y = 0x2D;
            myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, 0x01);
        L_001EA8:
            myMapper->writeCPU(0x007C, 0x01);
            myMapper->writeCPU(0x007D, myMapper->readCPU(0x0039));
            y = 0x2E;
            myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, 0x01);
        }
    }
    popAddress();
}

void game::SUB_001EB7() {
    a = myMapper->readCPU(0x008B);
    setLoadFlag(a);
    if (flgZ) {
        y = 0x3E;
        a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgZ) {
            a = myMapper->readCPU(0x0039);
            if (a == myMapper->readCPU(0x006E)) {
                myMapper->writeCPU(0x0085, a);
                x = 0x02;
                a = myMapper->readCPU(0x0060);
                flgC = true;
                opSBC(0x02);
                pushAddress(0x001ED0);
                SUB_001EED();
                if (poppedEntry.value != 0x001ED0) return;
                a = myMapper->readCPU(0x0060);
                flgC = true;
                opSBC(0x01);
                pushAddress(0x001ED8);
                SUB_001EED();
                if (poppedEntry.value != 0x001ED8) return;
                a = myMapper->readCPU(0x0060);
                pushAddress(0x001EDD);
                SUB_001EED();
                if (poppedEntry.value != 0x001EDD) return;
                a = myMapper->readCPU(0x0084);
                setLoadFlag(a);
                if (flgZ) {
                    goto L_001EEC;
                }
                y = 0x2F;
                myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
                a = 0xFF;
                myMapper->writeCPU((0x0084 + x) & 0x00ff, a);
            }
        }
    }
L_001EEC:
    popAddress();
}

void game::SUB_001EED() {
    myMapper->writeCPU(0x009C, a);
    a = x;
    opPHA();
    x = 0x00;
    a = myMapper->readCPU(0x009C);
    pushAddress(0x001EF5);
    SUB_003488();
    if (poppedEntry.value != 0x001EF5) return;
    if (!flgC) {
        goto L_001EFD;
    }
    opPLA();
    x = a;
    popAddress();
    return;
L_001EFD:
    opPLA();
    x = a;
    myMapper->writeCPU((0x0084 + x) & 0x00ff, myMapper->readCPU(0x009C));
    opINX(1);
    opINC(0x0084, 1);
    popAddress();
}

void game::SUB_001F07() {
    opCMP(myMapper->readCPU(0x0084), 0x01);
    if (!flgZ) {
        goto L_001F12;
    }
    myMapper->writeCPU(0x0045, myMapper->readCPU(0x0086));
    popAddress();
    return;
    do {
    L_001F12:
        pushAddress(0x001F12);
        SUB_000538();
        if (poppedEntry.value != 0x001F12) return;
        x = 0x02;
    L_001F17:
        a = myMapper->readCPU((0x0084 + x) & 0x00ff);
        opINX(1);
        opCMP(a, 0xFF);
    } while (flgZ);
    myMapper->writeCPU(0x0045, a);
    a = x;
    opPHA();
    myMapper->writeCPU(0x009D, 0x00);
    do {
        pushAddress(0x001F26);
        SUB_001F38();
        if (poppedEntry.value != 0x001F26) return;
        a = myMapper->readCPU(0x001A);
        setLoadFlag(a);
        if (!flgZ) {
            goto L_001F36;
        }
        opDEC(0x009D, 1);
    } while (!flgZ);
    opPLA();
    x = a;
    goto L_001F17;
L_001F36:
    opPLA();
    popAddress();
}

void game::SUB_001F38() {
    myMapper->writeCPU(0x009B, 0x00);
    x = myMapper->readCPU(0x0045);
    y = 0x03;
    do {
        a = x;
        pushAddress(0x001F41);
        SUB_001F49();
        if (poppedEntry.value != 0x001F41) return;
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_001F49() {
    opCMP(a, myMapper->readCPU(0x0044));
    if (flgZ) {
        goto L_001F75;
    }
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x02;
    y = 0xCE;
    a = myMapper->readCPU(0x0098);
    pushAddress(0x001F59);
    SUB_0036D1();
    if (poppedEntry.value != 0x001F59) return;
    opASL_A(1);
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, 0x18);
    a = myMapper->readCPU(0x009B);
    pushAddress(0x001F65);
    SUB_003A8A();
    if (poppedEntry.value != 0x001F65) return;
    x = 0x00;
    do {
        opPHA();
        opPLA();
        opDEX(1);
    } while (!flgZ);
    loopCounter++;
    if (loopCounter >= 0x08) {
        wait();
        loopCounter = 0x00;
    }

    opINC(0x009B, 1);
    opPLA();
    y = a;
    opPLA();
    x = a;
L_001F75:
    popAddress();
}

void game::SUB_001F76() {
    if (myMapper->readCPU(0x0072) != 0) {
        goto L_001FAE;
    }
    opINC(0x0073, 1);
    a = myMapper->readCPU(0x0073);
    if (a != 0x05) {
        if (a != 0x04) {
            goto L_001FB2;
        }
        y = 0x3A;
        if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) < 0x03) {
            goto L_001FAB;
        }
        y = 0x0F;
        myMapper->writeCPU(0x009C, 0x00);
        myMapper->writeCPU(0x009D, 0x03);
        do {
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            opINY(1);
            if (a < 0x80) {
                goto L_001FA1;
            }
            opINC(0x009C, 1);
        L_001FA1:
            opDEC(0x009D, 1);
        } while (!flgZ);
        a = myMapper->readCPU(0x009C);
        if (a == 0x03) {
            goto L_001FB2;
        }
    L_001FAB:
        a = 0x04;
        goto L_001FB0;
    }
L_001FAE:
    a = myMapper->readCPU(0x0005);
L_001FB0:
    myMapper->writeCPU(0x0072, a);
L_001FB2:
    popAddress();
}

void game::SUB_001FB3() {
    myMapper->writeCPU(0x0098, a);
    if (a < 0x35) {
        a = myMapper->readCPU(0x0037);
        opLSR_A(2);
        flgC = false;
        opADC(0x31);
        if (a != myMapper->readCPU(0x0098)) {
            y = 0x3F;
            a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
            flgC = false;
            opADC(0x31);
            if (a == myMapper->readCPU(0x0098)) {
                goto L_001FD1;
            }
            flgC = true;
            popAddress();
            return;
        }
    }
L_001FD1:
    flgC = false;
    popAddress();
}

void game::SUB_001FD3() {
    a = myMapper->readCPU(0x0048);
    pushAddress(0x001FD5);
    SUB_00346A();
    if (poppedEntry.value != 0x001FD5) return;
    y = myMapper->readCPU(0x000F);
    myMapper->writeCPU(0x0040, y);
    myMapper->writeCPU(0x00A2, y);
    x = myMapper->readCPU(0x0010);
    myMapper->writeCPU(0x0041, x);
    myMapper->writeCPU(0x00A3, x);
    a = myMapper->readCPU(0x0044);
    pushAddress(0x001FE6);
    SUB_0036B4();
    if (poppedEntry.value != 0x001FE6) return;
    y = myMapper->readCPU(0x0040);
    x = myMapper->readCPU(0x0041);
    a = myMapper->readCPU(0x0047);
    opCMP(a, 0x02);
    if (!flgZ) {
        opCMP(a, 0x03);
        if (flgZ) {
            goto L_002041;
        }
        a = myMapper->readCPU(0x0045);
        pushAddress(0x001FF9);
        SUB_000C3E();
        if (poppedEntry.value != 0x001FF9) return;
        pushAddress(0x001FFC);
        SUB_003680();
        if (poppedEntry.value != 0x001FFC) return;
        flgC = false;
        opADC(0x01);
        pushAddress(0x002002);
        SUB_000C3E();
        if (poppedEntry.value != 0x002002) return;
        pushAddress(0x002005);
        SUB_003680();
        if (poppedEntry.value != 0x002005) return;
        flgC = false;
        opADC(0x01);
        pushAddress(0x00200B);
        SUB_000C3E();
        if (poppedEntry.value != 0x00200B) return;
        pushAddress(0x00200E);
        SUB_003680();
        if (poppedEntry.value != 0x00200E) return;
        a = myMapper->readCPU(0x0045);
        pushAddress(0x002013);
        SUB_0020FD();
        if (poppedEntry.value != 0x002013) return;
        pushAddress(0x002016);
        SUB_003293();
        if (poppedEntry.value != 0x002016) return;
        a = 0x01;
        setLoadFlag(a);
        myMapper->writeCPU(0x008B, a);
        if (!flgZ) {
            SUB_002077();
            return;
        }
    }
    a = myMapper->readCPU(0x0044);
    pushAddress(0x002021);
    SUB_000C3E();
    if (poppedEntry.value != 0x002021) return;
    pushAddress(0x002024);
    SUB_003680();
    if (poppedEntry.value != 0x002024) return;
    pushAddress(0x002027);
    SUB_000C3E();
    if (poppedEntry.value != 0x002027) return;
    pushAddress(0x00202A);
    SUB_003680();
    if (poppedEntry.value != 0x00202A) return;
    pushAddress(0x00202D);
    SUB_000C3E();
    if (poppedEntry.value != 0x00202D) return;
    pushAddress(0x002030);
    SUB_003680();
    if (poppedEntry.value != 0x002030) return;
    opORA(0x40);
    pushAddress(0x002035);
    SUB_0020FD();
    if (poppedEntry.value != 0x002035) return;
    pushAddress(0x002038);
    SUB_003293();
    if (poppedEntry.value != 0x002038) return;
    a = 0x01;
    setLoadFlag(a);
    myMapper->writeCPU(0x008B, a);
    if (!flgZ) {
        SUB_002077();
        return;
    }
L_002041:
    a = myMapper->readCPU(0x0044);
    pushAddress(0x002043);
    SUB_000C3E();
    if (poppedEntry.value != 0x002043) return;
    pushAddress(0x002046);
    SUB_003680();
    if (poppedEntry.value != 0x002046) return;
    pushAddress(0x002049);
    SUB_000C3E();
    if (poppedEntry.value != 0x002049) return;
    pushAddress(0x00204C);
    SUB_003680();
    if (poppedEntry.value != 0x00204C) return;
    pushAddress(0x00204F);
    SUB_000C3E();
    if (poppedEntry.value != 0x00204F) return;
    pushAddress(0x002052);
    SUB_003680();
    if (poppedEntry.value != 0x002052) return;
    pushAddress(0x002055);
    SUB_000C3E();
    if (poppedEntry.value != 0x002055) return;
    pushAddress(0x002058);
    SUB_003680();
    if (poppedEntry.value != 0x002058) return;
    opORA(0x80);
    pushAddress(0x00205D);
    SUB_0020FD();
    if (poppedEntry.value != 0x00205D) return;
    pushAddress(0x002060);
    SUB_0021A9();
    if (poppedEntry.value != 0x002060) return;
    if (!flgC) {
        goto L_002073;
    }
    y = myMapper->readCPU(0x0040);
    x = myMapper->readCPU(0x0041);
    pushAddress(0x002069);
    SUB_0036B4();
    if (poppedEntry.value != 0x002069) return;
    pushAddress(0x00206C);
    SUB_003293();
    if (poppedEntry.value != 0x00206C) return;
    myMapper->writeCPU(0x0071, 0x01);
L_002073:
    pushAddress(0x002073);
    SUB_002077();
    if (poppedEntry.value != 0x002073) return;
    popAddress();
}

void game::SUB_002077() {
    pushAddress(0x002077);
    SUB_00240D();
    if (poppedEntry.value != 0x002077) return;
    a = myMapper->readCPU(0x003E);
    opPHA();
    a = myMapper->readCPU(0x003F);
    opPHA();
    a = myMapper->readCPU(0x0040);
    myMapper->writeCPU(0x000F, a);
    myMapper->writeCPU(0x003E, a);
    myMapper->writeCPU(0x00A2, a);
    a = myMapper->readCPU(0x0041);
    myMapper->writeCPU(0x000F, a);
    myMapper->writeCPU(0x003F, a);
    myMapper->writeCPU(0x00A3, a);
    pushAddress(0x002090);
    SUB_00370F();
    if (poppedEntry.value != 0x002090) return;
    a = myMapper->readCPU(0x0072);
    opCMP(a, 0x05);
    if (!flgZ) {
        myMapper->writeCPU(0x008B, 0xFF);
        y = 0x41;
        a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
        opORA(myMapper->readCPU(0x0012));
        if (flgZ) {
            pushAddress(0x0020A5);
            SUB_000964();
            if (poppedEntry.value != 0x0020A5) return;
            if (!flgC) {
                goto L_0020CA;
            }
            pushAddress(0x0020AA);
            SUB_000A4A();
            if (poppedEntry.value != 0x0020AA) return;
        }
        else {
            pushAddress(0x0020B0);
            SUB_000617();
            if (poppedEntry.value != 0x0020B0) return;
            if (!flgC) {
                goto L_0020CA;
            }
            pushAddress(0x0020B5);
            SUB_0005E4();
            if (poppedEntry.value != 0x0020B5) return;
        }
        myMapper->writeCPU(0x008B, 0x00);
        y = 0x41;
        myMapper->writeCPU(0x0039, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
        a = 0x00;
        myMapper->writeCPU(0x008B, a);
        opPLA();
        opPLA();
        flgC = true;
        popAddress();
        return;
    L_0020CA:
        y = myMapper->readCPU(0x003E);
        x = myMapper->readCPU(0x003F);
        a = myMapper->readCPU(0x0060);
        pushAddress(0x0020D0);
        SUB_003680();
        if (poppedEntry.value != 0x0020D0) return;
        a = myMapper->readCPU(0x0075);
        if (a != 0x01) {
            goto L_0020F1;
        }
        myMapper->writeCPU(0x0040, myMapper->readCPU(0x003E));
        a = myMapper->readCPU(0x003F);
        myMapper->writeCPU(0x0041, a);
        opPLA();
        myMapper->writeCPU(0x003F, a);
        opPLA();
        myMapper->writeCPU(0x003E, a);
        myMapper->writeCPU(0x0061, 0x01);
        myMapper->writeCPU(0x0098, 0x00);
        flgC = false;
        popAddress();
        return;
    L_0020F1:
        opPLA();
        opPLA();
        a = 0x01;
        flgC = false;
        popAddress();
        return;
    }
    opPLA();
    opPLA();
    a = 0x07;
    flgC = false;
    popAddress();
}

void game::SUB_0020FD() {
    myMapper->writeCPU(0x009C, a);
    a = myMapper->readCPU(0x0040);
    flgC = false;
    opADC(0x0F);
    y = a;
    a = myMapper->readCPU(0x0041);
    opADC(0x00);
    x = a;
    a = myMapper->readCPU(0x009C);
    pushAddress(0x00210C);
    SUB_0036B4();
    if (poppedEntry.value != 0x00210C) return;
    y = 0x3A;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x01);
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    opDEY(1);
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    flgC = true;
    opSBC(0x03);
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    myMapper->writeCPU(0x000A, 0x00);
    opINY(1);
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
        goto L_00213F;
    }
L_002132:
    x = myMapper->readCPU(0x0041);
    y = myMapper->readCPU(0x0040);
    pushAddress(0x002136);
    SUB_00379B();
    if (poppedEntry.value != 0x002136) return;
    pushAddress(0x002139);
    SUB_003B49();
    if (poppedEntry.value != 0x002139) return;
    goto L_002150;
L_00213F:
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_002132;
    }
    y = 0x39;
    x = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    do {
        a = 0x39;
        pushAddress(0x00214A);
        SUB_003BDE();
        if (poppedEntry.value != 0x00214A) return;
        opDEX(1);
    } while (!flgZ);
L_002150:
    x = 0x04;
    do {
        a = 0x38;
        pushAddress(0x002154);
        SUB_003BDE();
        if (poppedEntry.value != 0x002154) return;
        opDEX(1);
    } while (!flgZ);
    y = 0x3A;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    pushAddress(0x00215E);
    SUB_00216D();
    if (poppedEntry.value != 0x00215E) return;
    a = myMapper->readCPU(0x009C);
    pushAddress(0x002163);
    SUB_001860();
    if (poppedEntry.value != 0x002163) return;
    a = myMapper->readCPU(0x009C);
    opAND(0x3F);
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_00216D() {
    myMapper->writeCPU(0x0098, a);
    opASL_A(1);
    opADC(myMapper->readCPU(0x0098));
    opASL_A(1);
    flgC = true;
    opSBC(0x1F);
    opEOR(0xFF);
    myMapper->writeCPU(0x000A, a);
    y = 0x40;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    popAddress();
}

void game::SUB_002184() {
    a = myMapper->readCPU(0x030C);
    opAND(0x03);
    myMapper->writeCPU(0x030C, a);
    a = myMapper->readCPU(0x0352);
    opAND(0x03);
    myMapper->writeCPU(0x0352, a);
    a = myMapper->readCPU(0x0398);
    opAND(0x03);
    myMapper->writeCPU(0x0398, a);
    a = myMapper->readCPU(0x03DE);
    opAND(0x03);
    myMapper->writeCPU(0x03DE, a);
    a = 0x0A;
    myMapper->writeCPU(0x003D, a);
    popAddress();
}

void game::SUB_0021A9() {
    a = myMapper->readCPU(0x0072);
    if (a == 0x05) {
        flgC = false;
        popAddress();
        return;
    }
    opDEC(0x0034, 1);
    x = myMapper->readCPU(0x0073);
    opDEX(1);
    myMapper->writeCPU(0x0060, myMapper->readCPU(0x02CA + x));
    y = 0x39;
    a = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
    pushAddress(0x0021BF);
    SUB_0010E2();
    if (poppedEntry.value != 0x0021BF) return;
    a = myMapper->readCPU(0x000B);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    y = 0x41;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
        goto L_0021D3;
    }
L_0021CF:
    a = myMapper->readCPU(0x0060);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_0021D9;
    }
L_0021D3:
    if (myMapper->readCPU(0x0095) != 0) {
        goto L_0021CF;
    }
    a = 0x39;
L_0021D9:
    pushAddress(0x0021D9);
    SUB_003BDE();
    if (poppedEntry.value != 0x0021D9) return;
    pushAddress(0x0021DC);
    SUB_001278();
    if (poppedEntry.value != 0x0021DC) return;
    opINC(0x0075, 1);
    a = myMapper->readCPU(0x0060);
    flgC = true;
    popAddress();
}

void game::SUB_0021E5() {
    if (myMapper->readCPU(0x0073) != 0x05) {
        goto L_0021EC;
    }
    popAddress();
    return;
L_0021EC:
    opINC(0x0035, 1);
    a = myMapper->readCPU(0x0035);
    opASL_A(1);
    opADC(0x12);
    myMapper->writeCPU(0x000A, a);
    myMapper->writeCPU(0x000B, 0x00);
    x = myMapper->readCPU(0x0035);
    opDEX(1);
    a = myMapper->readCPU(0x02C0 + x);
    pushAddress(0x0021FF);
    SUB_000C3E();
    if (poppedEntry.value != 0x0021FF) return;
    SUB_003BDE();
    return;
}

void game::SUB_002205() {
    if (myMapper->readCPU(0x0071) == 0) {
        goto L_002210;
    }
    pushAddress(0x002209);
    SUB_0021E5();
    if (poppedEntry.value != 0x002209) return;
    myMapper->writeCPU(0x0071, 0x00);
L_002210:
    popAddress();
}

void game::SUB_002211() {
    myMapper->writeCPU(0x007E, 0x00);
    if (myMapper->readCPU(0x0034) == 0) {
        goto L_002265;
    }
    myMapper->writeCPU(0x0033, 0x00);
    do {
        x = myMapper->readCPU(0x0033);
        a = myMapper->readCPU(0x044E + x);
        if (a == 0xFF) {
            goto L_00225E;
        }
        x = 0x00;
        pushAddress(0x002228);
        SUB_00353E();
        if (poppedEntry.value != 0x002228) return;
        if (a >= 0x04) {
            x = myMapper->readCPU(0x0033);
            a = myMapper->readCPU(0x044E + x);
            opORA(0xC0);
            if (!flgZ) {
                goto L_002254;
            }
        }
        if (myMapper->readCPU(0x023A) != 0) {
            x = myMapper->readCPU(0x0033);
            a = myMapper->readCPU(0x044E + x);
            opORA(0x40);
            myMapper->writeCPU(0x009C, a);
            x = 0x0F;
            pushAddress(0x002248);
            SUB_0036FC();
            if (poppedEntry.value != 0x002248) return;
            if (flgC) {
                goto L_00225A;
            }
            x = myMapper->readCPU(0x0033);
            a = myMapper->readCPU(0x044E + x);
            opORA(0x80);
        L_002254:
            opINC(0x007E, 1);
            x = myMapper->readCPU(0x007E);
            myMapper->writeCPU((0x007E + x) & 0x00ff, a);
        }
    L_00225A:
        opINC(0x0033, 1);
    } while (!flgZ);
L_00225E:
    x = myMapper->readCPU(0x007E);
    opINX(1);
    myMapper->writeCPU((0x007E + x) & 0x00ff, 0xFF);
L_002265:
    popAddress();
}

void game::SUB_002266() {
    if (myMapper->readCPU(0x007E) == 0) {
        goto L_00227B;
    }
    y = 0x3E;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) != 0) {
        a = myMapper->readCPU(0x0060);
        x = 0x00;
        pushAddress(0x002274);
        SUB_00353E();
        if (poppedEntry.value != 0x002274) return;
        if (a >= 0x04) {
            goto L_00227D;
        }
    }
L_00227B:
    flgC = true;
    popAddress();
    return;
L_00227D:
    myMapper->writeCPU(0x007E, 0x01);
    a = myMapper->readCPU(0x0060);
    opORA(0xC0);
    myMapper->writeCPU(0x007F, a);
    myMapper->writeCPU(0x0080, 0xFF);
    x = 0x02;
    y = 0x00;
    a = myMapper->readCPU(0x0060);
    pushAddress(0x002291);
    SUB_003680();
    if (poppedEntry.value != 0x002291) return;
    pushAddress(0x002294);
    SUB_000E7C();
    if (poppedEntry.value != 0x002294) return;
    x = 0x00;
    do {
        myMapper->writeCPU(0x0480 + x, myMapper->readCPU(0x0471 + x));
        opINX(1);
        opCMP(x, 0x0F);
    } while (!flgZ);
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x003F));
    pushAddress(0x0022AC);
    SUB_00370F();
    if (poppedEntry.value != 0x0022AC) return;
    x = 0x02;
    y = 0x00;
    a = myMapper->readCPU(0x0060);
    pushAddress(0x0022B5);
    SUB_003680();
    if (poppedEntry.value != 0x0022B5) return;
    pushAddress(0x0022B8);
    SUB_003680();
    if (poppedEntry.value != 0x0022B8) return;
    pushAddress(0x0022BB);
    SUB_003680();
    if (poppedEntry.value != 0x0022BB) return;
    pushAddress(0x0022BE);
    SUB_003680();
    if (poppedEntry.value != 0x0022BE) return;
    pushAddress(0x0022C1);
    SUB_000E7C();
    if (poppedEntry.value != 0x0022C1) return;
    x = 0x00;
    do {
        opCMP(myMapper->readCPU(0x0471 + x), myMapper->readCPU(0x0480 + x));
        if (!flgZ) {
            goto L_0022D5;
        }
        opINX(1);
        opCMP(x, 0x0F);
    } while (!flgZ);
    if (!flgZ) {
    L_0022D5:
        myMapper->writeCPU(0x007E, 0x00);
    }
    myMapper->writeCPU(0x000F, myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x0010, myMapper->readCPU(0x003F));
    pushAddress(0x0022E1);
    SUB_00370F();
    if (poppedEntry.value != 0x0022E1) return;
    a = myMapper->readCPU(0x007E);
    setLoadFlag(a);
    flgC = true;
    if (flgZ) {
        goto L_0022EA;
    }
    flgC = false;
L_0022EA:
    popAddress();
}

void game::SUB_0022EB() {
    opCMP(myMapper->readCPU(0x007E), 0x01);
    if (!flgZ) {
        goto L_0022F6;
    }
    myMapper->writeCPU(0x007E, myMapper->readCPU(0x007F));
    popAddress();
    return;
    do {
    L_0022F6:
        pushAddress(0x0022F6);
        SUB_000538();
        if (poppedEntry.value != 0x0022F6) return;
        x = 0x01;
    L_0022FB:
        a = myMapper->readCPU((0x007E + x) & 0x00ff);
        opINX(1);
        opCMP(a, 0xFF);
    } while (flgZ);
    myMapper->writeCPU(0x007E, a);
    y = 0x00;
    do {
        myMapper->writeCPU(0x009B, 0x00);
        a = myMapper->readCPU(0x007E);
        opAND(0x3F);
        pushAddress(0x00230E);
        SUB_001F49();
        if (poppedEntry.value != 0x00230E) return;
        if (myMapper->readCPU(0x001A) != 0) {
            goto L_00231A;
        }
        opDEY(1);
    } while (!flgZ);
    if (flgZ) {
        goto L_0022FB;
    }
L_00231A:
    SUB_001231();
    return;
}

void game::SUB_00231D() {
    pushAddress(0x00231D);
    SUB_002205();
    if (poppedEntry.value != 0x00231D) return;
    pushAddress(0x002320);
    SUB_003293();
    if (poppedEntry.value != 0x002320) return;
    y = myMapper->readCPU(0x003E);
    x = myMapper->readCPU(0x003F);
    a = myMapper->readCPU(0x007E);
    opCMP(a, 0xC0);
    if (flgC) {
        myMapper->writeCPU(0x0041, x);
        myMapper->writeCPU(0x0040, y);
        opAND(0x3F);
        pushAddress(0x002333);
        SUB_000C3E();
        if (poppedEntry.value != 0x002333) return;
        pushAddress(0x002336);
        SUB_003680();
        if (poppedEntry.value != 0x002336) return;
        pushAddress(0x002339);
        SUB_000C3E();
        if (poppedEntry.value != 0x002339) return;
        pushAddress(0x00233C);
        SUB_003680();
        if (poppedEntry.value != 0x00233C) return;
        pushAddress(0x00233F);
        SUB_000C3E();
        if (poppedEntry.value != 0x00233F) return;
        pushAddress(0x002342);
        SUB_003680();
        if (poppedEntry.value != 0x002342) return;
        pushAddress(0x002345);
        SUB_000C3E();
        if (poppedEntry.value != 0x002345) return;
        pushAddress(0x002348);
        SUB_003680();
        if (poppedEntry.value != 0x002348) return;
        opORA(0xC0);
        pushAddress(0x00234D);
        SUB_0020FD();
        if (poppedEntry.value != 0x00234D) return;
        pushAddress(0x002350);
        SUB_0021E5();
        if (poppedEntry.value != 0x002350) return;
        pushAddress(0x002353);
        SUB_0021A9();
        if (poppedEntry.value != 0x002353) return;
        if (!flgC) {
            goto L_002407;
        }
        y = myMapper->readCPU(0x003E);
        x = myMapper->readCPU(0x003F);
        pushAddress(0x00235F);
        SUB_0036B4();
        if (poppedEntry.value != 0x00235F) return;
        pushAddress(0x002362);
        SUB_002184();
        if (poppedEntry.value != 0x002362) return;
        flgC = true;
        popAddress();
        return;
    }
    opAND(0x3F);
    myMapper->writeCPU(0x0060, a);
    pushAddress(0x00236B);
    SUB_003680();
    if (poppedEntry.value != 0x00236B) return;
    pushAddress(0x00236E);
    SUB_000C3E();
    if (poppedEntry.value != 0x00236E) return;
    a = 0x00;
    pushAddress(0x002373);
    SUB_0010E2();
    if (poppedEntry.value != 0x002373) return;
    a = myMapper->readCPU(0x000B);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    y = 0x41;
    if (myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y) == 0) {
    L_002383:
        y = myMapper->readCPU(0x003E);
        x = myMapper->readCPU(0x003F);
        pushAddress(0x002387);
        SUB_00379B();
        if (poppedEntry.value != 0x002387) return;
        pushAddress(0x00238A);
        SUB_003B49();
        if (poppedEntry.value != 0x00238A) return;
    }
    else {
        if (myMapper->readCPU(0x0095) != 0) {
            goto L_002383;
        }
        y = 0x39;
        x = myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y);
        do {
            a = 0x39;
            pushAddress(0x00239B);
            SUB_003BDE();
            if (poppedEntry.value != 0x00239B) return;
            opDEX(1);
        } while (!flgZ);
    }
    a = 0x38;
    pushAddress(0x0023A3);
    SUB_003BDE();
    if (poppedEntry.value != 0x0023A3) return;
    a = myMapper->readCPU(0x0060);
    opORA(0x40);
    myMapper->writeCPU(0x009C, a);
    x = 0x0F;
    pushAddress(0x0023AE);
    SUB_0036FC();
    if (poppedEntry.value != 0x0023AE) return;
    a = y;
    opPHA();
    flgC = true;
    opSBC(0x0E);
    pushAddress(0x0023B6);
    SUB_00216D();
    if (poppedEntry.value != 0x0023B6) return;
    opPLA();
    y = a;
    myMapper->writeCPU(myMapper->readCPU(0x003E) + (myMapper->readCPU((0x003E + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x007E));
    myMapper->writeCPU(0x008E, myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x008F, myMapper->readCPU(0x000A));
    a = myMapper->readCPU(0x007E);
    pushAddress(0x0023C9);
    SUB_001860();
    if (poppedEntry.value != 0x0023C9) return;
    pushAddress(0x0023CC);
    SUB_001B50();
    if (poppedEntry.value != 0x0023CC) return;
    myMapper->writeCPU(0x00A2, myMapper->readCPU(0x003E));
    myMapper->writeCPU(0x00A3, myMapper->readCPU(0x003F));
    if (!flgC) {
        goto L_0023EE;
    }
    pushAddress(0x0023D9);
    SUB_0021A9();
    if (poppedEntry.value != 0x0023D9) return;
    if (!flgC) {
        goto L_002407;
    }
    y = myMapper->readCPU(0x003E);
    x = myMapper->readCPU(0x003F);
    pushAddress(0x0023E2);
    SUB_0036B4();
    if (poppedEntry.value != 0x0023E2) return;
    myMapper->writeCPU(0x0071, 0x01);
    pushAddress(0x0023E9);
    SUB_002184();
    if (poppedEntry.value != 0x0023E9) return;
    flgC = true;
    popAddress();
    return;
L_0023EE:
    a = 0x01;
    myMapper->writeCPU(0x0061, a);
    myMapper->writeCPU(0x0074, a);
    a = myMapper->readCPU(0x0048);
    pushAddress(0x0023F6);
    SUB_00346A();
    if (poppedEntry.value != 0x0023F6) return;
    myMapper->writeCPU(0x0040, myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x0041, myMapper->readCPU(0x0010));
    a = 0x00;
    myMapper->writeCPU(0x0098, a);
    flgC = false;
    popAddress();
    return;
L_002407:
    a = 0x07;
    myMapper->writeCPU(0x0098, a);
    flgC = false;
    popAddress();
}

void game::SUB_00240D() {
    y = 0x00;
    a = myMapper->readCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y);
    opORA(0x80);
    myMapper->writeCPU(myMapper->readCPU(0x0090) + (myMapper->readCPU((0x0090 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x000B, myMapper->readCPU(0x008E));
    myMapper->writeCPU(0x000A, myMapper->readCPU(0x008F));
    a = 0x01;
    SUB_003B79();
    return;
}

void game::SUB_002422() {
    pushAddress(0x002422);
    SUB_00243A();
    if (poppedEntry.value != 0x002422) return;
    a = myMapper->readCPU(0x002E);
    flgC = true;
    opSBC(myMapper->readCPU(0x002F));
    x = a;
    setLoadFlag(x);
    if (!flgN) {
        if (myMapper->readCPU(0x003B) < 0x05) {
            goto L_002434;
        }
        opDEX(1);
    L_002434:
        opDEX(1);
        flgC = false;
        if (!flgN) {
            SUB_002439();
            return;
        }
    }
    flgC = true;
    SUB_002439();
    return;
}

void game::SUB_002439() {
    popAddress();
}

void game::SUB_00243A() {
    a = 0x00;
    myMapper->writeCPU(0x0030, a);
    myMapper->writeCPU(0x0026, a);
    myMapper->writeCPU(0x002E, a);
    pushAddress(0x002442);
    SUB_002D64();
    if (poppedEntry.value != 0x002442) return;
    if (!flgC) {
        SUB_002439();
        return;
    }
    pushAddress(0x002447);
    SUB_002E95();
    if (poppedEntry.value != 0x002447) return;
    if (!flgC) {
        SUB_002439();
        return;
    }
    pushAddress(0x00244C);
    SUB_003725();
    if (poppedEntry.value != 0x00244C) return;
    x = 0x00;
    while (true) {
        a = myMapper->readCPU(0x0446 + x);
        myMapper->writeCPU(0x0098, a);
        if (a == 0xFF) {
            goto L_002491;
        }
        opINX(1);
        a = x;
        opPHA();
        a = myMapper->readCPU(0x0098);
        myMapper->writeCPU(0x002C, a);
        myMapper->writeCPU(0x009C, a);
        x = 0x00;
        pushAddress(0x002465);
        SUB_0036FC();
        if (poppedEntry.value != 0x002465) return;
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
        pushAddress(0x002477);
        SUB_0036FC();
        if (poppedEntry.value != 0x002477) return;
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
        pushAddress(0x002489);
        SUB_0024A1();
        if (poppedEntry.value != 0x002489) return;
        opPLA();
        x = a;
    }
L_002491:
    if (myMapper->readCPU(0x0064) == 0x07) {
        pushAddress(0x002497);
        SUB_002DB1();
        if (poppedEntry.value != 0x002497) return;
    }
    a = myMapper->readCPU(0x0026);
    setLoadFlag(a);
    flgC = true;
    if (flgZ) {
        goto L_0024A0;
    }
    flgC = false;
L_0024A0:
    popAddress();
}

void game::SUB_0024A1() {
    a = x;
    opPHA();
    if (myMapper->readCPU(0x0200 + x) != 0xFF) {
        pushAddress(0x0024AA);
        SUB_00363C();
        if (poppedEntry.value != 0x0024AA) return;
        pushAddress(0x0024AD);
        SUB_0034EA();
        if (poppedEntry.value != 0x0024AD) return;
        if (!flgC) {
            pushAddress(0x0024B2);
            SUB_0024A1();
            if (poppedEntry.value != 0x0024B2) return;
            opDEX(3);
        }
        pushAddress(0x0024B8);
        SUB_00363C();
        if (poppedEntry.value != 0x0024B8) return;
        pushAddress(0x0024BB);
        SUB_003488();
        if (poppedEntry.value != 0x0024BB) return;
        if (flgC) {
            goto L_0024C6;
        }
        pushAddress(0x0024C0);
        SUB_0024A1();
        if (poppedEntry.value != 0x0024C0) return;
        opPLA();
        x = a;
        popAddress();
        return;
    L_0024C6:
        opPLA();
        x = a;
        flgC = true;
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0026, 0x01);
    pushAddress(0x0024CE);
    SUB_0024D8();
    if (poppedEntry.value != 0x0024CE) return;
    pushAddress(0x0024D1);
    SUB_0025A8();
    if (poppedEntry.value != 0x0024D1) return;
    opPLA();
    x = a;
    flgC = false;
    popAddress();
}

void game::SUB_0024D8() {
    y = 0x00;
    x = 0x02;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_002501;
        }
        myMapper->writeCPU(0x009C, a);
        opINX(1);
        a = myMapper->readCPU(0x0200 + x);
        opINX(2);
        opCMP(a, myMapper->readCPU(0x009C));
        if (flgZ) {
            goto L_0024F3;
        }
        a = 0x00;
        setLoadFlag(a);
        if (flgZ) {
            goto L_0024F5;
        }
    L_0024F3:
        a = 0x01;
    L_0024F5:
        myMapper->writeCPU(0x03EE + y, a);
        opINY(1);
        myMapper->writeCPU(0x03EE + y, myMapper->readCPU(0x009C));
        opINY(1);
    } while (!flgZ);
L_002501:
    a = myMapper->readCPU(0x023A);
    setLoadFlag(a);
    if (!flgZ) {
        myMapper->writeCPU(0x0031, y);
        myMapper->writeCPU(0x009D, a);
        y = 0x0F;
        do {
            a = myMapper->readCPU(0x0200 + y);
            opINY(1);
            myMapper->writeCPU(0x009C, a);
            opROL_A(3);
            opAND(0x03);
            x = a;
            a = myMapper->readCPU(0xE5A4 + x);
            x = myMapper->readCPU(0x0031);
            myMapper->writeCPU(0x03EE + x, a);
            opINX(1);
            a = myMapper->readCPU(0x009C);
            opAND(0x3F);
            myMapper->writeCPU(0x03EE + x, a);
            opINX(1);
            myMapper->writeCPU(0x0031, x);
            opDEC(0x009D, 1);
        } while (!flgZ);
    }
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opAND(0x04);
        if (!flgZ) {
            goto L_00253F;
        }
        opINX(2);
        opDEY(1);
    } while (!flgZ);
L_00253F:
    myMapper->writeCPU(0x0025, a);
    if (myMapper->readCPU(0x0061) != 0) {
        x = 0x00;
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            if (a == 0x01) {
                if (myMapper->readCPU(0x03EE + x) != myMapper->readCPU(0x0060)) {
                    goto L_002569;
                }
                a = x;
                opPHA();
                x = 0x00;
                a = myMapper->readCPU(0x0060);
                pushAddress(0x00255E);
                SUB_00353E();
                if (poppedEntry.value != 0x00255E) return;
                opPLA();
                x = a;
                if (myMapper->readCPU(0x0098) == 0x03) {
                    goto L_00256F;
                }
            }
        L_002569:
            opINX(1);
            opDEY(1);
        } while (!flgZ);
        if (flgZ) {
            goto L_002575;
        }
    L_00256F:
        opDEX(1);
        myMapper->writeCPU(0x03EE + x, 0x05);
    }
L_002575:
    a = 0x00;
    myMapper->writeCPU(0x0029, a);
    myMapper->writeCPU(0x002A, a);
    myMapper->writeCPU(0x002B, a);
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        myMapper->writeCPU(0x009C, a);
        opAND(0x05);
        if (a == 0x01) {
            opINC(0x002A, 1);
            if (!flgZ) {
                goto L_002594;
            }
        }
        if (a == 0x05) {
        L_002594:
            opINC(0x0029, 1);
        }
        a = myMapper->readCPU(0x009C);
        opAND(0x02);
        if (flgZ) {
            goto L_00259E;
        }
        opINC(0x002B, 1);
    L_00259E:
        opINX(2);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0025A8() {
    pushAddress(0x0025A8);
    SUB_0025DD();
    if (poppedEntry.value != 0x0025A8) return;
    if (myMapper->readCPU(0x0025) == 0) {
        pushAddress(0x0025AF);
        SUB_00265D();
        if (poppedEntry.value != 0x0025AF) return;
    }
    pushAddress(0x0025B2);
    SUB_0027BB();
    if (poppedEntry.value != 0x0025B2) return;
    if (myMapper->readCPU(0x0029) >= 0x04) {
        pushAddress(0x0025BB);
        SUB_0027CB();
        if (poppedEntry.value != 0x0025BB) return;
    }
    if (myMapper->readCPU(0x0029) >= 0x03) {
        pushAddress(0x0025C4);
        SUB_002863();
        if (poppedEntry.value != 0x0025C4) return;
    }
    if (myMapper->readCPU(0x0029) < 0x01) {
        goto L_0025D0;
    }
    pushAddress(0x0025CD);
    SUB_002943();
    if (poppedEntry.value != 0x0025CD) return;
L_0025D0:
    pushAddress(0x0025D0);
    SUB_002A0D();
    if (poppedEntry.value != 0x0025D0) return;
    pushAddress(0x0025D3);
    SUB_002C7D();
    if (poppedEntry.value != 0x0025D3) return;
    pushAddress(0x0025D6);
    SUB_0025F7();
    if (poppedEntry.value != 0x0025D6) return;
    pushAddress(0x0025D9);
    SUB_00262A();
    if (poppedEntry.value != 0x0025D9) return;
    popAddress();
}

void game::SUB_0025DD() {
    a = 0x00;
    myMapper->writeCPU(0x0023, a);
    myMapper->writeCPU(0x0027, a);
    myMapper->writeCPU(0x0028, a);
    myMapper->writeCPU(0x002D, a);
    myMapper->writeCPU(0x002F, a);
    x = 0x00;
    y = 0x28;
    a = 0xFF;
    do {
        myMapper->writeCPU(0x03F6 + x, a);
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_0025F7() {
    x = 0x00;
    do {
    L_0025F9:
        if (myMapper->readCPU(0x03F6 + x) == 0xFF) {
            goto L_002629;
        }
        opINX(1);
        a = myMapper->readCPU(0x03F6 + x);
        opINX(1);
    } while (a < 0x10);
    x = 0x00;
    do {
        do {
            if (myMapper->readCPU(0x03F6 + x) == 0xFF) {
                goto L_0025F9;
            }
            opINX(1);
            a = myMapper->readCPU(0x03F6 + x);
            opINX(1);
        } while (a >= 0x10);
        opDEX(2);
        a = 0x00;
        myMapper->writeCPU(0x03F6 + x, a);
        opINX(1);
        myMapper->writeCPU(0x03F6 + x, a);
        opINX(1);
    } while (!flgZ);
L_002629:
    popAddress();
}

void game::SUB_00262A() {
    x = 0x01;
    myMapper->writeCPU(0x009D, 0x00);
    while (true) {
        a = myMapper->readCPU(0x03F6 + x);
        if (a == 0xFF) {
            goto L_002641;
        }
        opINX(2);
        flgC = false;
        opADC(myMapper->readCPU(0x009D));
        myMapper->writeCPU(0x009D, a);
    }
L_002641:
    a = myMapper->readCPU(0x002E);
    opCMP(a, myMapper->readCPU(0x009D));
    if (flgC) {
        goto L_00265C;
    }
    myMapper->writeCPU(0x002E, myMapper->readCPU(0x009D));
    pushAddress(0x00264B);
    SUB_002F4D();
    if (poppedEntry.value != 0x00264B) return;
    x = 0x00;
    y = 0x28;
    do {
        a = myMapper->readCPU(0x03F6 + x);
        myMapper->writeCPU(0x041E + x, a);
        opINX(1);
        opDEY(1);
    } while (!flgZ);
L_00265C:
    popAddress();
}

void game::SUB_00265D() {
    pushAddress(0x00265D);
    SUB_00276E();
    if (poppedEntry.value != 0x00265D) return;
    myMapper->writeCPU(0x009D, 0x09);
    x = 0x00;
    do {
        a = myMapper->readCPU(0x009D);
        pushAddress(0x002668);
        SUB_00353E();
        if (poppedEntry.value != 0x002668) return;
        if (a == 0x00) {
            goto L_0026A9;
        }
        opDEC(0x009D, 1);
    } while (!flgZ);
    a = 0x01;
    pushAddress(0x002675);
    SUB_00353E();
    if (poppedEntry.value != 0x002675) return;
    if (a >= 0x03) {
        a = 0x09;
        pushAddress(0x00267E);
        SUB_00353E();
        if (poppedEntry.value != 0x00267E) return;
        if (a >= 0x03) {
            a = 0x06;
            pushAddress(0x002687);
            SUB_00304F();
            if (poppedEntry.value != 0x002687) return;
            a = myMapper->readCPU(0x0060);
            if (a != 0x01) {
                if (a == 0x09) {
                    goto L_00269D;
                }
                pushAddress(0x002694);
                SUB_00353E();
                if (poppedEntry.value != 0x002694) return;
                opCMP(a, 0x02);
                if (!flgZ) {
                    goto L_0026A9;
                }
                if (flgZ) {
                    goto L_0026A4;
                }
            }
        L_00269D:
            pushAddress(0x00269D);
            SUB_00353E();
            if (poppedEntry.value != 0x00269D) return;
            if (a == 0x04) {
            L_0026A4:
                a = 0x07;
                pushAddress(0x0026A6);
                SUB_00304F();
                if (poppedEntry.value != 0x0026A6) return;
            }
        }
    }
L_0026A9:
    a = myMapper->readCPU(0x03EF);
    pushAddress(0x0026AC);
    SUB_002CF7();
    if (poppedEntry.value != 0x0026AC) return;
    if (a == 0x02) {
        a = myMapper->readCPU(0x03F3);
        pushAddress(0x0026B6);
        SUB_002CF7();
        if (poppedEntry.value != 0x0026B6) return;
        if (a == 0x02) {
            a = 0x09;
            pushAddress(0x0026BF);
            SUB_00304F();
            if (poppedEntry.value != 0x0026BF) return;
            goto L_0026E3;
        }
    }
    x = 0x01;
    myMapper->writeCPU(0x009D, 0x03);
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(2);
        pushAddress(0x0026D0);
        SUB_002CF7();
        if (poppedEntry.value != 0x0026D0) return;
        if (a != 0x02) {
            goto L_0026DF;
        }
        a = 0x0F;
        pushAddress(0x0026D9);
        SUB_00304F();
        if (poppedEntry.value != 0x0026D9) return;
        goto L_0026E3;
    L_0026DF:
        opDEC(0x009D, 1);
    } while (!flgZ);
L_0026E3:
    a = myMapper->readCPU(0x002C);
    pushAddress(0x0026E5);
    SUB_002CAB();
    if (poppedEntry.value != 0x0026E5) return;
    if (flgC) {
        x = 0x00;
        myMapper->writeCPU(0x009D, 0x04);
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            myMapper->writeCPU(0x009E, a);
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            myMapper->writeCPU(0x009F, a);
            if (a >= 0x30) {
                goto L_00270E;
            }
            pushAddress(0x002700);
            SUB_002D1F();
            if (poppedEntry.value != 0x002700) return;
            if (!flgC) {
                goto L_00270E;
            }
            opDEC(0x009D, 1);
        } while (!flgZ);
        a = 0x11;
        pushAddress(0x00270B);
        SUB_00304F();
        if (poppedEntry.value != 0x00270B) return;
    }
L_00270E:
    if (myMapper->readCPU(0x0029) == 0) {
        opCMP(myMapper->readCPU(0x002C), 0x35);
        if (!flgC) {
            a = myMapper->readCPU(0x023F);
            opADC(0x31);
            if (a != myMapper->readCPU(0x002C)) {
                a = myMapper->readCPU(0x0037);
                opLSR_A(2);
                flgC = false;
                opADC(0x31);
                if (a != myMapper->readCPU(0x002C)) {
                    a = myMapper->readCPU(0x0060);
                    opAND(0x0F);
                    if (a < 0x07) {
                        x = 0x01;
                        y = 0x04;
                        do {
                            a = myMapper->readCPU(0x03EE + x);
                            opINX(2);
                            if (a == myMapper->readCPU(0x0060)) {
                                goto L_002764;
                            }
                            opDEY(1);
                        } while (!flgZ);
                    }
                    a = myMapper->readCPU(0x0060);
                    opAND(0x0F);
                    if (a >= 0x04) {
                        x = myMapper->readCPU(0x0060);
                        opDEX(2);
                        myMapper->writeCPU(0x0098, x);
                        x = 0x01;
                        y = 0x04;
                        do {
                            a = myMapper->readCPU(0x03EE + x);
                            opINX(2);
                            if (a == myMapper->readCPU(0x0098)) {
                                goto L_002764;
                            }
                            opDEY(1);
                        } while (!flgZ);
                        if (flgZ) {
                            goto L_00276D;
                        }
                    L_002764:
                        myMapper->writeCPU(0x0028, 0x01);
                        a = 0x10;
                        pushAddress(0x00276A);
                        SUB_00304F();
                        if (poppedEntry.value != 0x00276A) return;
                    }
                }
            }
        }
    }
L_00276D:
    popAddress();
}

void game::SUB_00276E() {
    a = myMapper->readCPU(0x023E);
    setLoadFlag(a);
    if (!flgZ) {
        opAND(0x03);
        if (a == 0x01) {
            a = 0x0B;
        }
        else {
            a = myMapper->readCPU(0x000C);
        }
        pushAddress(0x00277E);
        SUB_00304F();
        if (poppedEntry.value != 0x00277E) return;
        if (myMapper->readCPU(0x023E) >= 0x80) {
            opINC(0x002F, 1);
            a = 0x0D;
            pushAddress(0x00278C);
            SUB_00304F();
            if (poppedEntry.value != 0x00278C) return;
        }
    }
    if (myMapper->readCPU(0x0061) == 0) {
        if (myMapper->readCPU(0x003D) != 0) {
            goto L_00279F;
        }
        a = 0x01;
        pushAddress(0x002799);
        SUB_00304F();
        if (poppedEntry.value != 0x002799) return;
        goto L_0027B1;
    }
L_00279F:
    if (myMapper->readCPU(0x003D) < 0x04) {
        if (myMapper->readCPU(0x0061) != 0) {
            goto L_0027AC;
        }
        a = 0x02;
        goto L_0027AE;
    L_0027AC:
        a = myMapper->readCPU(0x0003);
    L_0027AE:
        pushAddress(0x0027AE);
        SUB_00304F();
        if (poppedEntry.value != 0x0027AE) return;
    }
L_0027B1:
    if (myMapper->readCPU(0x0061) != 0) {
        SUB_0027BA();
        return;
    }
    a = 0x0E;
    pushAddress(0x0027B7);
    SUB_00304F();
    if (poppedEntry.value != 0x0027B7) return;
    SUB_0027BA();
    return;
}

void game::SUB_0027BA() {
    popAddress();
}

void game::SUB_0027BB() {
    if (myMapper->readCPU(0x0034) != 0) {
        SUB_0027BA();
        return;
    }
    if (myMapper->readCPU(0x0061) != 0) {
        goto L_0027C6;
    }
    a = 0x2D;
    goto L_0027C8;
L_0027C6:
    a = myMapper->readCPU(0x0038);
L_0027C8:
    SUB_00304F();
    return;
}

void game::SUB_0027CB() {
    if (myMapper->readCPU(0x002C) < 0x30) {
        goto L_0027E6;
    }
    x = 0x01;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(2);
        if (a < 0x30) {
            goto L_0027E6;
        }
        opDEY(1);
    } while (!flgZ);
    a = 0x13;
    pushAddress(0x0027E3);
    SUB_00304F();
    if (poppedEntry.value != 0x0027E3) return;
L_0027E6:
    x = 0x01;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(2);
        if (a < 0x30) {
            goto L_0027FF;
        }
        if (a >= 0x35) {
            goto L_0027FF;
        }
        opDEY(1);
    } while (!flgZ);
    a = 0x14;
    pushAddress(0x0027FC);
    SUB_00304F();
    if (poppedEntry.value != 0x0027FC) return;
L_0027FF:
    if (myMapper->readCPU(0x002B) >= 0x04) {
        a = 0x15;
        pushAddress(0x002807);
        SUB_00304F();
        if (poppedEntry.value != 0x002807) return;
    }
    if (myMapper->readCPU(0x002A) >= 0x04) {
        a = 0x16;
        pushAddress(0x002812);
        SUB_00304F();
        if (poppedEntry.value != 0x002812) return;
        if (myMapper->readCPU(0x002C) == myMapper->readCPU(0x0060)) {
            a = 0x17;
            pushAddress(0x00281D);
            SUB_00304F();
            if (poppedEntry.value != 0x00281D) return;
        }
    }
    a = myMapper->readCPU(0x002C);
    pushAddress(0x002822);
    SUB_002C99();
    if (poppedEntry.value != 0x002822) return;
    if (!flgC) {
        x = 0x01;
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(2);
            pushAddress(0x002830);
            SUB_002C99();
            if (poppedEntry.value != 0x002830) return;
            if (flgC) {
                goto L_002840;
            }
            opDEY(1);
        } while (!flgZ);
        a = 0x18;
        pushAddress(0x00283A);
        SUB_00304F();
        if (poppedEntry.value != 0x00283A) return;
    }
    else {
    L_002840:
        a = myMapper->readCPU(0x002C);
        pushAddress(0x002842);
        SUB_002CAB();
        if (poppedEntry.value != 0x002842) return;
        if (flgC) {
            goto L_00285D;
        }
        x = 0x01;
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(2);
            pushAddress(0x002850);
            SUB_002CAB();
            if (poppedEntry.value != 0x002850) return;
            if (flgC) {
                goto L_00285D;
            }
            opDEY(1);
        } while (!flgZ);
        a = 0x19;
        pushAddress(0x00285A);
        SUB_00304F();
        if (poppedEntry.value != 0x00285A) return;
    }
L_00285D:
    a = 0x1A;
    pushAddress(0x00285F);
    SUB_00304F();
    if (poppedEntry.value != 0x00285F) return;
    popAddress();
}

void game::SUB_002863() {
    a = 0x35;
    pushAddress(0x002865);
    SUB_002CB1();
    if (poppedEntry.value != 0x002865) return;
    if (!flgC) {
        a = 0x36;
        pushAddress(0x00286C);
        SUB_002CB1();
        if (poppedEntry.value != 0x00286C) return;
        if (!flgC) {
            a = 0x37;
            pushAddress(0x002873);
            SUB_002CB1();
            if (poppedEntry.value != 0x002873) return;
            if (!flgC) {
                a = 0x1B;
                pushAddress(0x00287A);
                SUB_00304F();
                if (poppedEntry.value != 0x00287A) return;
            }
        }
    }
    a = myMapper->readCPU(0x002C);
    if (a >= 0x30) {
        if (a >= 0x35) {
            goto L_0028B3;
        }
        x = 0x00;
        myMapper->writeCPU(0x009C, 0x00);
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            opAND(0x01);
            if (!flgZ) {
                a = myMapper->readCPU(0x03EE + x);
                if (a >= 0x30) {
                    if (a >= 0x35) {
                        goto L_0028A4;
                    }
                    opINC(0x009C, 1);
                }
            }
        L_0028A4:
            opINX(1);
            opDEY(1);
        } while (!flgZ);
        if (myMapper->readCPU(0x009C) == 0x03) {
            a = 0x1C;
            pushAddress(0x0028B0);
            SUB_00304F();
            if (poppedEntry.value != 0x0028B0) return;
        }
    }
L_0028B3:
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opPHA();
        a = myMapper->readCPU(0x03EE + x);
        myMapper->writeCPU(0x009C, a);
        opPLA();
        opINX(1);
        opAND(0x01);
        if (!flgZ) {
            if (myMapper->readCPU(0x009C) >= 0x30) {
                goto L_0028E7;
            }
            opINC(0x009C, 1);
            a = myMapper->readCPU(0x009C);
            pushAddress(0x0028D1);
            SUB_002CB1();
            if (poppedEntry.value != 0x0028D1) return;
            if (!flgC) {
                opINC(0x009C, 1);
                a = myMapper->readCPU(0x009C);
                pushAddress(0x0028DA);
                SUB_002CB1();
                if (poppedEntry.value != 0x0028DA) return;
                if (flgC) {
                    goto L_0028E7;
                }
                a = 0x1D;
                pushAddress(0x0028E1);
                SUB_00304F();
                if (poppedEntry.value != 0x0028E1) return;
                goto L_0028EA;
            }
        }
    L_0028E7:
        opDEY(1);
    } while (!flgZ);
L_0028EA:
    if (myMapper->readCPU(0x002A) == 0x03) {
        a = 0x1E;
        pushAddress(0x0028F2);
        SUB_00304F();
        if (poppedEntry.value != 0x0028F2) return;
    }
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opPHA();
        a = myMapper->readCPU(0x03EE + x);
        myMapper->writeCPU(0x009C, a);
        opPLA();
        opINX(1);
        opAND(0x01);
        if (!flgZ) {
            a = myMapper->readCPU(0x009C);
            if (a < 0x30) {
                opAND(0x0F);
                pushAddress(0x002911);
                SUB_002CB1();
                if (poppedEntry.value != 0x002911) return;
                if (!flgC) {
                    a = myMapper->readCPU(0x009C);
                    opAND(0x0F);
                    opORA(0x10);
                    pushAddress(0x00291C);
                    SUB_002CB1();
                    if (poppedEntry.value != 0x00291C) return;
                    if (!flgC) {
                        a = myMapper->readCPU(0x009C);
                        opAND(0x0F);
                        opORA(0x20);
                        pushAddress(0x002927);
                        SUB_002CB1();
                        if (poppedEntry.value != 0x002927) return;
                        if (flgC) {
                            goto L_002934;
                        }
                        a = 0x1F;
                        pushAddress(0x00292E);
                        SUB_00304F();
                        if (poppedEntry.value != 0x00292E) return;
                        goto L_002937;
                    }
                }
            }
        }
    L_002934:
        opDEY(1);
    } while (!flgZ);
L_002937:
    if (myMapper->readCPU(0x002B) != 0x03) {
        goto L_002942;
    }
    a = 0x20;
    pushAddress(0x00293F);
    SUB_00304F();
    if (poppedEntry.value != 0x00293F) return;
L_002942:
    popAddress();
}

void game::SUB_002943() {
    a = 0x35;
    pushAddress(0x002945);
    SUB_002CB1();
    if (poppedEntry.value != 0x002945) return;
    if (!flgC) {
        a = 0x21;
        pushAddress(0x00294C);
        SUB_00304F();
        if (poppedEntry.value != 0x00294C) return;
    }
    a = 0x36;
    pushAddress(0x002951);
    SUB_002CB1();
    if (poppedEntry.value != 0x002951) return;
    if (!flgC) {
        a = 0x22;
        pushAddress(0x002958);
        SUB_00304F();
        if (poppedEntry.value != 0x002958) return;
    }
    a = 0x37;
    pushAddress(0x00295D);
    SUB_002CB1();
    if (poppedEntry.value != 0x00295D) return;
    if (!flgC) {
        a = 0x23;
        pushAddress(0x002964);
        SUB_00304F();
        if (poppedEntry.value != 0x002964) return;
    }
    a = myMapper->readCPU(0x0037);
    opLSR_A(2);
    myMapper->writeCPU(0x009F, a);
    myMapper->writeCPU(0x009E, myMapper->readCPU(0x023F));
    a = 0x31;
    pushAddress(0x002974);
    SUB_002CB1();
    if (poppedEntry.value != 0x002974) return;
    if (!flgC) {
        y = 0x00;
        if (myMapper->readCPU(0x009F) == 0) {
            opINY(1);
        }
        if (myMapper->readCPU(0x009E) == 0) {
            opINY(1);
        }
        if (y != 0x00) {
            if (y == 0x02) {
                goto L_002990;
            }
            a = 0x24;
            goto L_002992;
        L_002990:
            a = myMapper->readCPU(0x0028);
        L_002992:
            pushAddress(0x002992);
            SUB_00304F();
            if (poppedEntry.value != 0x002992) return;
        }
    }
    a = 0x32;
    pushAddress(0x002997);
    SUB_002CB1();
    if (poppedEntry.value != 0x002997) return;
    if (!flgC) {
        y = 0x00;
        if (myMapper->readCPU(0x009F) == 0x01) {
            opINY(1);
        }
        if (myMapper->readCPU(0x009E) == 0x01) {
            opINY(1);
        }
        if (y != 0x00) {
            if (y == 0x02) {
                goto L_0029B7;
            }
            a = 0x25;
            goto L_0029B9;
        L_0029B7:
            a = myMapper->readCPU(0x0029);
        L_0029B9:
            pushAddress(0x0029B9);
            SUB_00304F();
            if (poppedEntry.value != 0x0029B9) return;
        }
    }
    if (myMapper->readCPU(0x009E) == 0x02) {
        a = 0x33;
        pushAddress(0x0029C4);
        SUB_002CB1();
        if (poppedEntry.value != 0x0029C4) return;
        if (!flgC) {
            a = 0x26;
            pushAddress(0x0029CB);
            SUB_00304F();
            if (poppedEntry.value != 0x0029CB) return;
        }
    }
    if (myMapper->readCPU(0x009E) == 0x03) {
        a = 0x34;
        pushAddress(0x0029D6);
        SUB_002CB1();
        if (poppedEntry.value != 0x0029D6) return;
        if (!flgC) {
            a = 0x27;
            pushAddress(0x0029DD);
            SUB_00304F();
            if (poppedEntry.value != 0x0029DD) return;
        }
    }
    if (myMapper->readCPU(0x002C) >= 0x35) {
        x = 0x00;
        y = 0x04;
        myMapper->writeCPU(0x009C, x);
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            opAND(0x01);
            if (!flgZ) {
                if (myMapper->readCPU(0x03EE + x) < 0x35) {
                    goto L_0029FD;
                }
                opINC(0x009C, 1);
            }
        L_0029FD:
            opINX(1);
            opDEY(1);
        } while (!flgZ);
        if (myMapper->readCPU(0x009C) != 0x02) {
            goto L_002A0C;
        }
        a = 0x2A;
        pushAddress(0x002A09);
        SUB_00304F();
        if (poppedEntry.value != 0x002A09) return;
    }
L_002A0C:
    popAddress();
}

void game::SUB_002A0D() {
    if (myMapper->readCPU(0x0025) == 0) {
        goto L_002A3D;
    }
    if (myMapper->readCPU(0x0024) != 0) {
        a = myMapper->readCPU(0x002C);
        pushAddress(0x002A17);
        SUB_002CAB();
        if (poppedEntry.value != 0x002A17) return;
        if (flgC) {
            x = 0x00;
            y = 0x04;
            do {
                a = myMapper->readCPU(0x03EE + x);
                opINX(1);
                myMapper->writeCPU(0x009E, a);
                a = myMapper->readCPU(0x03EE + x);
                opINX(1);
                myMapper->writeCPU(0x009F, a);
                if (a >= 0x30) {
                    goto L_002A3D;
                }
                pushAddress(0x002A30);
                SUB_002D1F();
                if (poppedEntry.value != 0x002A30) return;
                if (!flgC) {
                    goto L_002A3D;
                }
                opDEY(1);
            } while (!flgZ);
            a = 0x11;
            pushAddress(0x002A3A);
            SUB_00304F();
            if (poppedEntry.value != 0x002A3A) return;
        }
    }
L_002A3D:
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x03EE + x);
            myMapper->writeCPU(0x009F, a);
            opAND(0x0F);
            if (a == 0x01) {
                a = myMapper->readCPU(0x009F);
                flgC = false;
                opADC(0x03);
                pushAddress(0x002A59);
                SUB_002CD1();
                if (poppedEntry.value != 0x002A59) return;
                if (!flgC) {
                    a = myMapper->readCPU(0x009F);
                    flgC = false;
                    opADC(0x06);
                    pushAddress(0x002A63);
                    SUB_002CD1();
                    if (poppedEntry.value != 0x002A63) return;
                    if (flgC) {
                        goto L_002A70;
                    }
                    a = 0x2E;
                    pushAddress(0x002A6A);
                    SUB_00304F();
                    if (poppedEntry.value != 0x002A6A) return;
                    goto L_002A74;
                }
            }
        }
    L_002A70:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
L_002A74:
    x = 0x00;
    y = 0x02;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x03EE + x);
            if (a < 0x30) {
                opAND(0x0F);
                myMapper->writeCPU(0x009F, a);
                pushAddress(0x002A8B);
                SUB_002CD1();
                if (poppedEntry.value != 0x002A8B) return;
                if (!flgC) {
                    a = myMapper->readCPU(0x009F);
                    opORA(0x10);
                    pushAddress(0x002A94);
                    SUB_002CD1();
                    if (poppedEntry.value != 0x002A94) return;
                    if (!flgC) {
                        a = myMapper->readCPU(0x009F);
                        opORA(0x20);
                        pushAddress(0x002A9D);
                        SUB_002CD1();
                        if (poppedEntry.value != 0x002A9D) return;
                        if (flgC) {
                            goto L_002AAA;
                        }
                        a = 0x2F;
                        pushAddress(0x002AA4);
                        SUB_00304F();
                        if (poppedEntry.value != 0x002AA4) return;
                        goto L_002AAE;
                    }
                }
            }
        }
    L_002AAA:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
L_002AAE:
    x = 0x00;
    y = 0x02;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (!flgZ) {
            goto L_002ACC;
        }
        a = myMapper->readCPU(0x03EE + x);
        pushAddress(0x002ABD);
        SUB_002CF7();
        if (poppedEntry.value != 0x002ABD) return;
        if (a != 0x03) {
            goto L_002AD0;
        }
        a = 0x30;
        pushAddress(0x002AC6);
        SUB_00304F();
        if (poppedEntry.value != 0x002AC6) return;
        goto L_002AD0;
    L_002ACC:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
L_002AD0:
    a = myMapper->readCPU(0x002C);
    pushAddress(0x002AD2);
    SUB_002C99();
    if (poppedEntry.value != 0x002AD2) return;
    if (!flgC) {
        x = 0x00;
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            myMapper->writeCPU(0x009E, a);
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            myMapper->writeCPU(0x009F, a);
            pushAddress(0x002AE7);
            SUB_002D1F();
            if (poppedEntry.value != 0x002AE7) return;
            if (flgC) {
                goto L_002AF7;
            }
            opDEY(1);
        } while (!flgZ);
        a = 0x32;
        pushAddress(0x002AF1);
        SUB_00304F();
        if (poppedEntry.value != 0x002AF1) return;
    }
    else {
    L_002AF7:
        a = myMapper->readCPU(0x002C);
        pushAddress(0x002AF9);
        SUB_002CAB();
        if (poppedEntry.value != 0x002AF9) return;
        if (!flgC) {
            x = 0x00;
            y = 0x04;
            myMapper->writeCPU(0x009C, x);
            do {
                a = myMapper->readCPU(0x03EE + x);
                opINX(1);
                myMapper->writeCPU(0x009E, a);
                a = myMapper->readCPU(0x03EE + x);
                opINX(1);
                myMapper->writeCPU(0x009F, a);
                if (a < 0x30) {
                    pushAddress(0x002B14);
                    SUB_002D1F();
                    if (poppedEntry.value != 0x002B14) return;
                    if (flgC) {
                        goto L_002B2D;
                    }
                    a = myMapper->readCPU(0x009E);
                    opAND(0x01);
                    if (!flgZ) {
                        goto L_002B21;
                    }
                    opINC(0x009C, 1);
                }
            L_002B21:
                opDEY(1);
            } while (!flgZ);
            if (myMapper->readCPU(0x009C) != 0) {
                a = 0x31;
                pushAddress(0x002B2A);
                SUB_00304F();
                if (poppedEntry.value != 0x002B2A) return;
            }
        }
    }
L_002B2D:
    a = myMapper->readCPU(0x002C);
    opAND(0xF0);
    myMapper->writeCPU(0x0098, a);
    x = 0x01;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(2);
        opAND(0xF0);
        if (a != myMapper->readCPU(0x0098)) {
            goto L_002B4D;
        }
        opDEY(1);
    } while (!flgZ);
    a = 0x34;
    pushAddress(0x002B47);
    SUB_00304F();
    if (poppedEntry.value != 0x002B47) return;
    goto L_002B87;
L_002B4D:
    myMapper->writeCPU(0x009E, 0xFF);
    a = myMapper->readCPU(0x002C);
    if (a < 0x30) {
        opAND(0xF0);
        myMapper->writeCPU(0x009E, a);
    }
    x = 0x01;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        myMapper->writeCPU(0x009F, a);
        opINX(2);
        if (a < 0x30) {
            opINC(0x009E, 1);
            if (!flgZ) {
                goto L_002B77;
            }
            a = myMapper->readCPU(0x009F);
            opAND(0xF0);
            myMapper->writeCPU(0x009E, a);
            goto L_002B7F;
        L_002B77:
            opDEC(0x009E, 1);
            opAND(0xF0);
            if (a != myMapper->readCPU(0x009E)) {
                goto L_002B87;
            }
        }
    L_002B7F:
        opDEY(1);
    } while (!flgZ);
    a = 0x33;
    pushAddress(0x002B84);
    SUB_00304F();
    if (poppedEntry.value != 0x002B84) return;
L_002B87:
    myMapper->writeCPU(0x009E, 0x00);
    a = myMapper->readCPU(0x002C);
    pushAddress(0x002B8D);
    SUB_002D44();
    if (poppedEntry.value != 0x002B8D) return;
    if (!flgC) {
        x = 0x00;
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            opPHA();
            a = myMapper->readCPU(0x03EE + x);
            myMapper->writeCPU(0x009F, a);
            opPLA();
            opINX(1);
            opAND(0x01);
            if (!flgZ) {
                goto L_002BAC;
            }
            if (myMapper->readCPU(0x009F) != 0x12) {
                goto L_002BBF;
            }
        L_002BAC:
            a = myMapper->readCPU(0x009F);
            pushAddress(0x002BAE);
            SUB_002D44();
            if (poppedEntry.value != 0x002BAE) return;
            if (flgC) {
                goto L_002BBF;
            }
            opDEY(1);
        } while (!flgZ);
        opINC(0x009E, 1);
        if (flgZ) {
            a = 0x12;
            pushAddress(0x002BBC);
            SUB_00304F();
            if (poppedEntry.value != 0x002BBC) return;
        }
    }
L_002BBF:
    if (myMapper->readCPU(0x0075) != 0) {
        opINC(0x002F, 1);
        a = 0x2B;
        pushAddress(0x002BC7);
        SUB_00304F();
        if (poppedEntry.value != 0x002BC7) return;
    }
    if (myMapper->readCPU(0x0074) == 0) {
        goto L_002BD5;
    }
    opINC(0x002F, 1);
    a = 0x2C;
    pushAddress(0x002BD2);
    SUB_00304F();
    if (poppedEntry.value != 0x002BD2) return;
L_002BD5:
    popAddress();
}

void game::SUB_002BD6() {
    a = 0x00;
    x = a;
    y = a;
    while (true) {
        a = myMapper->readCPU(0x0200 + x);
        if (a == 0xFF) {
            goto L_002BE9;
        }
        opINX(1);
        myMapper->writeCPU(0x045D + y, a);
        opINY(1);
    }
L_002BE9:
    a = myMapper->readCPU(0x023A);
    setLoadFlag(a);
    if (flgZ) {
        goto L_002C33;
    }
    myMapper->writeCPU(0x009D, a);
    x = 0x0F;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        myMapper->writeCPU(0x009C, a);
        opAND(0xC0);
        if (flgZ) {
            a = myMapper->readCPU(0x009C);
            opAND(0x3F);
            myMapper->writeCPU(0x045D + y, a);
            opINY(1);
            opINC(0x009C, 1);
            myMapper->writeCPU(0x045D + y, myMapper->readCPU(0x009C));
            opINY(1);
            opINC(0x009C, 1);
            myMapper->writeCPU(0x045D + y, myMapper->readCPU(0x009C));
            opINY(1);
        }
        else {
            a = x;
            opPHA();
            x = 0x03;
            a = 0x80;
            opBIT(myMapper->readCPU(0x009C));
            if (flgZ) {
                goto L_002C22;
            }
            opINX(1);
        L_002C22:
            a = myMapper->readCPU(0x009C);
            opAND(0x3F);
            do {
                myMapper->writeCPU(0x045D + y, a);
                opINY(1);
                opDEX(1);
            } while (!flgZ);
            opPLA();
            x = a;
        }
        opDEC(0x009D, 1);
    } while (!flgZ);
L_002C33:
    myMapper->writeCPU(0x045D + y, 0xFF);
    popAddress();
}

void game::SUB_002C39() {
    a = myMapper->readCPU(0x009D);
    opPHA();
    pushAddress(0x002C3C);
    SUB_002BD6();
    if (poppedEntry.value != 0x002C3C) return;
    a = 0x00;
    myMapper->writeCPU(0x0097, a);
    x = a;
    y = myMapper->readCPU(0x0035);
    do {
        a = myMapper->readCPU(0x02C0 + x);
        opINX(1);
        pushAddress(0x002C4A);
        SUB_002C61();
        if (poppedEntry.value != 0x002C4A) return;
        opDEY(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x023E);
    setLoadFlag(a);
    if (flgZ) {
        goto L_002C5B;
    }
    a = myMapper->readCPU(0x02C5);
    pushAddress(0x002C58);
    SUB_002C61();
    if (poppedEntry.value != 0x002C58) return;
L_002C5B:
    opPLA();
    myMapper->writeCPU(0x009D, a);
    a = myMapper->readCPU(0x0097);
    popAddress();
}

void game::SUB_002C61() {
    pushAddress(0x002C61);
    SUB_00376C();
    if (poppedEntry.value != 0x002C61) return;
    myMapper->writeCPU(0x009D, a);
    a = x;
    opPHA();
    x = 0x00;
    do {
        do {
            a = myMapper->readCPU(0x045D + x);
            opINX(1);
            if (a == 0xFF) {
                goto L_002C7A;
            }
        } while (a != myMapper->readCPU(0x009D));
        opINC(0x0097, 1);
    } while (!flgZ);
L_002C7A:
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_002C7D() {
    pushAddress(0x002C7D);
    SUB_002C39();
    if (poppedEntry.value != 0x002C7D) return;
    if (a != 0x00) {
        goto L_002C85;
    }
    popAddress();
    return;
L_002C85:
    opPHA();
    flgC = false;
    opADC(myMapper->readCPU(0x002F));
    myMapper->writeCPU(0x002F, a);
    a = 0x35;
    x = 0x03;
    y = 0xF6;
    pushAddress(0x002C91);
    SUB_0036B4();
    if (poppedEntry.value != 0x002C91) return;
    opPLA();
    pushAddress(0x002C95);
    SUB_0036B4();
    if (poppedEntry.value != 0x002C95) return;
    popAddress();
}

void game::SUB_002C99() {
    opCMP(a, 0x30);
    if (flgC) {
        SUB_002CA9();
        return;
    }
    opAND(0x0F);
    opCMP(a, 0x01);
    if (flgZ) {
        SUB_002CA7();
        return;
    }
    opCMP(a, 0x09);
    if (!flgZ) {
        SUB_002CA9();
        return;
    }
    SUB_002CA7();
    return;
}

void game::SUB_002CA7() {
    flgC = false;
    popAddress();
}

void game::SUB_002CA9() {
    flgC = true;
    popAddress();
}

void game::SUB_002CAB() {
    opCMP(a, 0x30);
    if (flgC) {
        SUB_002CA7();
        return;
    }
    if (!flgC) {
        SUB_002C99();
        return;
    }
    SUB_002CB1();
    return;
}

void game::SUB_002CB1() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (flgZ) {
            goto L_002CCA;
        }
        a = myMapper->readCPU(0x03EE + x);
        if (a == myMapper->readCPU(0x0098)) {
            SUB_002CF1();
            return;
        }
    L_002CCA:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    flgC = true;
    if (flgC) {
        SUB_002CF2();
        return;
    }
    SUB_002CD1();
    return;
}

void game::SUB_002CD1() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (!flgZ) {
            goto L_002CEA;
        }
        a = myMapper->readCPU(0x03EE + x);
        if (a == myMapper->readCPU(0x0098)) {
            SUB_002CF1();
            return;
        }
    L_002CEA:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    flgC = true;
    if (flgC) {
        SUB_002CF2();
        return;
    }
    SUB_002CF1();
    return;
}

void game::SUB_002CF1() {
    flgC = false;
    SUB_002CF2();
    return;
}

void game::SUB_002CF2() {
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_002CF7() {
    myMapper->writeCPU(0x0097, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x00;
    y = 0x04;
    myMapper->writeCPU(0x0098, x);
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (flgZ) {
            a = myMapper->readCPU(0x03EE + x);
            if (a != myMapper->readCPU(0x0097)) {
                goto L_002D14;
            }
            opINC(0x0098, 1);
        }
    L_002D14:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
    opPLA();
    y = a;
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0098);
    popAddress();
}

void game::SUB_002D1F() {
    a = x;
    opPHA();
    a = myMapper->readCPU(0x009F);
    if (a < 0x30) {
        opAND(0x0F);
        myMapper->writeCPU(0x009F, a);
        if (a != 0x01) {
            x = 0x07;
            a = myMapper->readCPU(0x009E);
            opAND(0x01);
            if (!flgZ) {
                opINX(2);
            }
            if (x == myMapper->readCPU(0x009F)) {
                goto L_002D40;
            }
            flgC = true;
            if (flgC) {
                goto L_002D41;
            }
        }
    L_002D40:
        flgC = false;
    }
L_002D41:
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_002D44() {
    if (a == 0x36) {
        goto L_002D5E;
    }
    if (a == 0x12) {
        goto L_002D62;
    }
    if (a == 0x13) {
        goto L_002D62;
    }
    if (a == 0x14) {
        goto L_002D62;
    }
    if (a == 0x16) {
        goto L_002D62;
    }
    if (a == 0x18) {
        goto L_002D62;
    }
    flgC = true;
    popAddress();
    return;
L_002D5E:
    myMapper->writeCPU(0x009E, 0xFF);
L_002D62:
    flgC = false;
    popAddress();
}

void game::SUB_002D64() {
    pushAddress(0x002D64);
    SUB_0025DD();
    if (poppedEntry.value != 0x002D64) return;
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a == 0xFF) {
            goto L_002D77;
        }
        pushAddress(0x002D71);
        SUB_002CAB();
        if (poppedEntry.value != 0x002D71) return;
    } while (!flgC);
    popAddress();
    return;
L_002D77:
    x = 0x00;
    do {
        a = myMapper->readCPU(0xF0C3 + x);
        setLoadFlag(a);
        if (flgZ) {
            goto L_002D91;
        }
        myMapper->writeCPU(0x0098, a);
        opINX(1);
        a = x;
        opPHA();
        x = 0x02;
        y = 0x00;
        a = myMapper->readCPU(0x0098);
        pushAddress(0x002D89);
        SUB_0036D1();
        if (poppedEntry.value != 0x002D89) return;
        opPLA();
        x = a;
    } while (!flgC);
    popAddress();
    return;
L_002D91:
    pushAddress(0x002D91);
    SUB_00276E();
    if (poppedEntry.value != 0x002D91) return;
    a = 0x04;
    pushAddress(0x002D96);
    SUB_00304F();
    if (poppedEntry.value != 0x002D96) return;
    x = 0x00;
    a = myMapper->readCPU(0x0060);
    pushAddress(0x002D9D);
    SUB_00353E();
    if (poppedEntry.value != 0x002D9D) return;
    if (a != 0x02) {
        goto L_002DA9;
    }
    a = 0x05;
    pushAddress(0x002DA6);
    SUB_00304F();
    if (poppedEntry.value != 0x002DA6) return;
L_002DA9:
    pushAddress(0x002DA9);
    SUB_0025F7();
    if (poppedEntry.value != 0x002DA9) return;
    pushAddress(0x002DAC);
    SUB_00262A();
    if (poppedEntry.value != 0x002DAC) return;
    flgC = false;
    popAddress();
}

void game::SUB_002DB1() {
    pushAddress(0x002DB1);
    SUB_0025DD();
    if (poppedEntry.value != 0x002DB1) return;
    pushAddress(0x002DB4);
    SUB_00276E();
    if (poppedEntry.value != 0x002DB4) return;
    pushAddress(0x002DB7);
    SUB_0027BB();
    if (poppedEntry.value != 0x002DB7) return;
    a = 0x08;
    pushAddress(0x002DBC);
    SUB_00304F();
    if (poppedEntry.value != 0x002DBC) return;
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a == 0xFF) {
            goto L_002DD0;
        }
        pushAddress(0x002DC9);
        SUB_002CAB();
        if (poppedEntry.value != 0x002DC9) return;
        if (!flgC) {
            goto L_002DD5;
        }
    } while (flgC);
L_002DD0:
    a = 0x11;
    pushAddress(0x002DD2);
    SUB_00304F();
    if (poppedEntry.value != 0x002DD2) return;
L_002DD5:
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a == 0xFF) {
            goto L_002DE5;
        }
        opCMP(a, 0x30);
        if (!flgC) {
            goto L_002DED;
        }
    } while (flgC);
L_002DE5:
    a = 0x13;
    pushAddress(0x002DE7);
    SUB_00304F();
    if (poppedEntry.value != 0x002DE7) return;
    goto L_002E81;
L_002DED:
    x = 0x00;
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a == 0xFF) {
            goto L_002DFE;
        }
        pushAddress(0x002DF7);
        SUB_002CAB();
        if (poppedEntry.value != 0x002DF7) return;
        if (flgC) {
            goto L_002E03;
        }
    } while (!flgC);
L_002DFE:
    a = 0x19;
    pushAddress(0x002E00);
    SUB_00304F();
    if (poppedEntry.value != 0x002E00) return;
L_002E03:
    x = 0x00;
    a = myMapper->readCPU(0x0200 + x);
    opINX(1);
    opAND(0xF0);
    myMapper->writeCPU(0x009E, a);
    do {
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a == 0xFF) {
            goto L_002E1D;
        }
        opAND(0xF0);
        opCMP(a, myMapper->readCPU(0x009E));
        if (!flgZ) {
            goto L_002E2A;
        }
    } while (flgZ);
L_002E1D:
    a = 0x34;
    pushAddress(0x002E1F);
    SUB_00304F();
    if (poppedEntry.value != 0x002E1F) return;
    opCMP(myMapper->readCPU(0x009E), 0x20);
    if (!flgZ) {
        if (!flgZ) {
            goto L_002E81;
        }
    L_002E2A:
        myMapper->writeCPU(0x009E, 0xFF);
        x = 0x00;
        a = myMapper->readCPU(0x0200 + x);
        opINX(1);
        if (a >= 0x30) {
            goto L_002E3C;
        }
        opAND(0xF0);
        myMapper->writeCPU(0x009E, a);
        do {
            while (true) {
                do {
                L_002E3C:
                    a = myMapper->readCPU(0x0200 + x);
                    opINX(1);
                    if (a == 0xFF) {
                        goto L_002E5D;
                    }
                } while (a >= 0x30);
                opINC(0x009E, 1);
                if (!flgZ) {
                    goto L_002E53;
                }
                opAND(0xF0);
                myMapper->writeCPU(0x009E, a);
            }
        L_002E53:
            opDEC(0x009E, 1);
            opAND(0xF0);
            opCMP(a, myMapper->readCPU(0x009E));
        } while (flgZ);
        if (!flgZ) {
            goto L_002E81;
        }
    L_002E5D:
        a = 0x33;
        pushAddress(0x002E5F);
        SUB_00304F();
        if (poppedEntry.value != 0x002E5F) return;
    }
    else {
        x = 0x00;
        pushAddress(0x002E67);
        SUB_00363C();
        if (poppedEntry.value != 0x002E67) return;
        myMapper->writeCPU(0x009C, a);
        y = 0x07;
        do {
            a = y;
            opPHA();
            pushAddress(0x002E70);
            SUB_0036FC();
            if (poppedEntry.value != 0x002E70) return;
            opPLA();
            y = a;
            if (flgC) {
                goto L_002E81;
            }
            opINC(0x009C, 1);
            opDEY(1);
        } while (!flgZ);
        a = 0x0A;
        pushAddress(0x002E7E);
        SUB_00304F();
        if (poppedEntry.value != 0x002E7E) return;
    }
L_002E81:
    a = 0x01;
    myMapper->writeCPU(0x0026, a);
    myMapper->writeCPU(0x0027, a);
    pushAddress(0x002E87);
    SUB_002C7D();
    if (poppedEntry.value != 0x002E87) return;
    pushAddress(0x002E8A);
    SUB_0025F7();
    if (poppedEntry.value != 0x002E8A) return;
    pushAddress(0x002E8D);
    SUB_00262A();
    if (poppedEntry.value != 0x002E8D) return;
    myMapper->writeCPU(0x0027, 0x00);
    popAddress();
}

void game::SUB_002E95() {
    opCMP(myMapper->readCPU(0x003D), 0x04);
    if (!flgC) {
        a = myMapper->readCPU(0x0061);
        setLoadFlag(a);
        if (flgZ) {
            a = myMapper->readCPU(0x023A);
            setLoadFlag(a);
            if (flgZ) {
                myMapper->writeCPU(0x0063, 0x00);
                pushAddress(0x002EA8);
                SUB_0025DD();
                if (poppedEntry.value != 0x002EA8) return;
                pushAddress(0x002EAB);
                SUB_003604();
                if (poppedEntry.value != 0x002EAB) return;
                x = 0x00;
                pushAddress(0x002EB0);
                SUB_003612();
                if (poppedEntry.value != 0x002EB0) return;
                if (myMapper->readCPU(0x0064) == 0x01) {
                    if (myMapper->readCPU(0x0065) != 0) {
                        goto L_002ED7;
                    }
                    pushAddress(0x002EBD);
                    SUB_003604();
                    if (poppedEntry.value != 0x002EBD) return;
                    x = 0x01;
                    pushAddress(0x002EC2);
                    SUB_003612();
                    if (poppedEntry.value != 0x002EC2) return;
                    if (myMapper->readCPU(0x0064) == 0) {
                        if (myMapper->readCPU(0x0065) != 0) {
                            goto L_002ED7;
                        }
                        a = 0x37;
                        pushAddress(0x002ECF);
                        SUB_00304F();
                        if (poppedEntry.value != 0x002ECF) return;
                        pushAddress(0x002ED2);
                        SUB_00262A();
                        if (poppedEntry.value != 0x002ED2) return;
                        flgC = false;
                        popAddress();
                        return;
                    }
                }
            L_002ED7:
                a = 0x00;
                x = a;
                y = a;
                do {
                    do {
                        a = myMapper->readCPU(0x044E + x);
                        opINX(1);
                        if (a == 0xFF) {
                            goto L_002EEB;
                        }
                        pushAddress(0x002EE3);
                        SUB_002CAB();
                        if (poppedEntry.value != 0x002EE3) return;
                    } while (flgC);
                    opINY(1);
                } while (!flgZ);
            L_002EEB:
                opCMP(y, 0x09);
                if (flgC) {
                    if (myMapper->readCPU(0x0241) == 0) {
                        goto L_002EF8;
                    }
                    opCMP(y, 0x0A);
                    if (flgC) {
                        goto L_002F02;
                    }
                L_002EF8:
                    myMapper->writeCPU(0x002E, 0x12);
                    a = 0x06;
                    setLoadFlag(a);
                    myMapper->writeCPU(0x002D, a);
                    flgC = false;
                    popAddress();
                    return;
                }
            }
        }
    }
L_002F02:
    flgC = true;
    popAddress();
}

void game::SUB_002F04() {
    myMapper->writeCPU(0x0039, myMapper->readCPU(0x0036));
    y = 0x04;
    do {
        a = myMapper->readCPU(0x0039);
        pushAddress(0x002F0C);
        SUB_00346A();
        if (poppedEntry.value != 0x002F0C) return;
        myMapper->writeCPU(0x003E, myMapper->readCPU(0x000F));
        myMapper->writeCPU(0x003F, myMapper->readCPU(0x0010));
        pushAddress(0x002F17);
        SUB_00370F();
        if (poppedEntry.value != 0x002F17) return;
        x = 0x14;
        do {
            a = myMapper->readCPU(0x0200 + x);
            opINX(1);
            if (a == 0xFF) {
                goto L_002F3C;
            }
            if (a < 0x00) {
                goto L_002F2F;
            }
            opAND(0x3F);
            pushAddress(0x002F2A);
            SUB_002CAB();
            if (poppedEntry.value != 0x002F2A) return;
        } while (!flgC);
    L_002F2F:
        opINC(0x0039, 1);
        a = myMapper->readCPU(0x0039);
        opAND(0x03);
        myMapper->writeCPU(0x0039, a);
        opDEY(1);
    } while (!flgZ);
    flgC = true;
    popAddress();
    return;
L_002F3C:
    pushAddress(0x002F3C);
    SUB_0025DD();
    if (poppedEntry.value != 0x002F3C) return;
    a = 0x36;
    pushAddress(0x002F41);
    SUB_00304F();
    if (poppedEntry.value != 0x002F41) return;
    pushAddress(0x002F44);
    SUB_00262A();
    if (poppedEntry.value != 0x002F44) return;
    a = 0x08;
    myMapper->writeCPU(0x0098, a);
    flgC = false;
    SUB_002F4C();
    return;
}

void game::SUB_002F4C() {
    popAddress();
}

void game::SUB_002F4D() {
    if (myMapper->readCPU(0x0027) == 0) {
        goto L_002F56;
    }
    myMapper->writeCPU(0x0030, 0x19);
    popAddress();
    return;
L_002F56:
    myMapper->writeCPU(0x0030, 0x14);
    if (myMapper->readCPU(0x0061) != 0) {
        if (myMapper->readCPU(0x0025) != 0) {
            goto L_002F66;
        }
        myMapper->writeCPU(0x0030, 0x1E);
    }
L_002F66:
    a = myMapper->readCPU(0x0028);
    setLoadFlag(a);
    if (!flgZ) {
        SUB_002F4C();
        return;
    }
    if (myMapper->readCPU(0x002C) >= 0x36) {
        opINC(0x0030, 2);
        if (!flgZ) {
            goto L_002F93;
        }
    }
    a = myMapper->readCPU(0x023F);
    flgC = false;
    opADC(0x31);
    if (a == myMapper->readCPU(0x002C)) {
        opINC(0x0030, 2);
    }
    a = myMapper->readCPU(0x0037);
    opLSR_A(2);
    flgC = false;
    opADC(0x31);
    if (a == myMapper->readCPU(0x002C)) {
        opINC(0x0030, 2);
    }
L_002F93:
    pushAddress(0x002F93);
    SUB_002FF9();
    if (poppedEntry.value != 0x002F93) return;
    if (!flgC) {
        opINC(0x0030, 2);
        if (!flgZ) {
            goto L_002FB3;
        }
    }
    pushAddress(0x002F9E);
    SUB_00301E();
    if (poppedEntry.value != 0x002F9E) return;
    if (!flgC) {
        opINC(0x0030, 2);
        if (!flgZ) {
            goto L_002FB3;
        }
    }
    if (myMapper->readCPU(0x002C) == myMapper->readCPU(0x0060)) {
        opINC(0x0030, 2);
    }
L_002FB3:
    if (myMapper->readCPU(0x0061) != 0) {
        goto L_002FBB;
    }
    opINC(0x0030, 2);
L_002FBB:
    x = 0x00;
    y = 0x04;
    do {
        myMapper->writeCPU(0x0098, 0x00);
        a = myMapper->readCPU(0x03EE + x);
        opAND(0x01);
        if (!flgZ) {
            myMapper->writeCPU(0x0098, 0x02);
            a = myMapper->readCPU(0x03EE + x);
            opAND(0x02);
            if (!flgZ) {
                opASL_M(0x0098, 2);
            }
            a = myMapper->readCPU(0x03EE + x);
            opAND(0x04);
            if (flgZ) {
                opASL_M(0x0098, 1);
            }
        }
        opINX(1);
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        pushAddress(0x002FE7);
        SUB_002CAB();
        if (poppedEntry.value != 0x002FE7) return;
        if (flgC) {
            goto L_002FEE;
        }
        opASL_M(0x0098, 1);
    L_002FEE:
        a = myMapper->readCPU(0x0098);
        flgC = false;
        opADC(myMapper->readCPU(0x0030));
        myMapper->writeCPU(0x0030, a);
        opDEY(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_002FF9() {
    a = myMapper->readCPU(0x0060);
    if (a >= 0x30) {
        goto L_00301A;
    }
    myMapper->writeCPU(0x0097, a);
    opDEC(0x0097, 1);
    x = 0x00;
    y = 0x04;
    do {
        a = myMapper->readCPU(0x03EE + x);
        opINX(1);
        opAND(0x01);
        if (!flgZ) {
            goto L_003016;
        }
        if (myMapper->readCPU(0x03EE + x) == myMapper->readCPU(0x0097)) {
            goto L_00301C;
        }
    L_003016:
        opINX(1);
        opDEY(1);
    } while (!flgZ);
L_00301A:
    flgC = true;
    popAddress();
    return;
L_00301C:
    flgC = false;
    popAddress();
}

void game::SUB_00301E() {
    a = myMapper->readCPU(0x0060);
    if (a < 0x30) {
        myMapper->writeCPU(0x0097, a);
        opAND(0x0F);
        if (a == 0x07) {
            goto L_003034;
        }
        if (a != 0x03) {
            goto L_00304B;
        }
        opDEC(0x0097, 2);
    L_003034:
        x = 0x00;
        y = 0x04;
        do {
            a = myMapper->readCPU(0x03EE + x);
            opINX(1);
            opAND(0x01);
            if (!flgZ) {
                goto L_003047;
            }
            if (myMapper->readCPU(0x03EE + x) == myMapper->readCPU(0x0097)) {
                goto L_00304D;
            }
        L_003047:
            opINX(1);
            opDEY(1);
        } while (!flgZ);
    }
L_00304B:
    flgC = true;
    popAddress();
    return;
L_00304D:
    flgC = false;
    popAddress();
}

void game::SUB_00304F() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    x = myMapper->readCPU(0x0023);
    opINC(0x0023, 2);
    myMapper->writeCPU(0x03F6 + x, myMapper->readCPU(0x0098));
    opINX(1);
    a = x;
    opPHA();
    myMapper->writeCPU(0x0097, 0x00);
    if (myMapper->readCPU(0x0025) != 0) {
        a = myMapper->readCPU(0x0098);
        if (a >= 0x2E) {
            if (a >= 0x35) {
                goto L_003075;
            }
            opINC(0x0097, 1);
        }
    }
L_003075:
    a = myMapper->readCPU(0x0098);
    pushAddress(0x003077);
    SUB_003089();
    if (poppedEntry.value != 0x003077) return;
    flgC = true;
    opSBC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x0098, a);
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0098);
    myMapper->writeCPU(0x03F6 + x, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003089() {
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(0x000F, 0xD0);
    myMapper->writeCPU(0x0010, 0xF0);
    a = myMapper->readCPU(0x0098);
    flgC = true;
    opSBC(0x28);
    if (!flgC) {
        goto L_0030A6;
    }
    opADC(0x00);
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(0x000F, 0x8D);
    myMapper->writeCPU(0x0010, 0xF1);
L_0030A6:
    y = 0xFF;
    do {
        do {
            opINY(1);
        } while (myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y) != 0);
        opDEC(0x0098, 1);
    } while (!flgZ);
    opINY(1);
    myMapper->writeCPU(0x0098, myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y));
    a = y;
    flgC = true;
    opADC(myMapper->readCPU(0x000F));
    y = a;
    a = 0x00;
    opADC(myMapper->readCPU(0x0010));
    x = a;
    a = myMapper->readCPU(0x0098);
    popAddress();
}

void game::SUB_00324B() {
    myMapper->writeCPU(0x0015, 0x56);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x64;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00329D();
        return;
    }
    SUB_003257();
    return;
}

void game::SUB_003257() {
    myMapper->writeCPU(0x0015, 0x4F);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x32;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00329D();
        return;
    }
    SUB_003263();
    return;
}

void game::SUB_003263() {
    myMapper->writeCPU(0x0015, 0x60);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x32;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00329D();
        return;
    }
    SUB_00326F();
    return;
}

void game::SUB_00326F() {
    myMapper->writeCPU(0x0015, 0x67);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x1E;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00329D();
        return;
    }
    SUB_00327B();
    return;
}

void game::SUB_00327B() {
    myMapper->writeCPU(0x0015, 0x72);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x50;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00329D();
        return;
    }
    SUB_003287();
    return;
}

void game::SUB_003287() {
    myMapper->writeCPU(0x0015, 0x4D);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x14;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_00329D();
        return;
    }
    SUB_003293();
    return;
}

void game::SUB_003293() {
    myMapper->writeCPU(0x0015, 0x64);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x32;
    SUB_00329D();
    return;
}

void game::SUB_00329D() {
    myMapper->writeCPU(0x009A, a);
    myMapper->writeCPU(0x4000, 0xBF);
    a = x;
    opPHA();
    a = y;
    opPHA();
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x0015) + (myMapper->readCPU((0x0015 + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_0032D1;
        }
        pushAddress(0x0032B0);
        SUB_0032FB();
        if (poppedEntry.value != 0x0032B0) return;
        myMapper->writeCPU(0x4002, myMapper->readCPU(0x0092));
        myMapper->writeCPU(0x4003, myMapper->readCPU(0x0093));
        a = y;
        opPHA();
        x = 0x00;
        y = myMapper->readCPU(0x009A);
    	loopCounter = 0x00;
        do {
            do {
                opPHA();
                opPLA();
                opDEX(1);
            } while (!flgZ);
            loopCounter++;
            if (loopCounter >= 0x08) {
                wait();
                loopCounter = 0x00;
            }
            opDEY(1);
        } while (!flgZ);
        opPLA();
        y = a;
        opINY(1);
    }
L_0032D1:
    a = 0xB0;
    myMapper->writeCPU(0x4000, a);
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_0032DB() {
    myMapper->writeCPU(0x0015, 0x76);
    myMapper->writeCPU(0x0016, 0xF3);
    a = 0x84;
    myMapper->writeCPU(0x4000, a);
    myMapper->writeCPU(0x4004, a);
    myMapper->writeCPU(0x4008, 0x10);
    a = 0x0A;
    myMapper->writeCPU(0x0013, a);
    myMapper->writeCPU(0x0014, a);
    myMapper->writeCPU(0x0017, 0x01);
    popAddress();
}

void game::SUB_0032FB() {
    if (a != 0x81) {
        goto L_003301;
    }
    a = 0x0C;
L_003301:
    myMapper->writeCPU(0x0098, a);
    opAND(0x0F);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x0092, myMapper->readCPU(0xF333 + x));
    myMapper->writeCPU(0x0093, myMapper->readCPU(0xF334 + x));
    a = myMapper->readCPU(0x0098);
    opAND(0xF0);
    if (!flgZ) {
        opLSR_A(4);
        x = a;
        do {
            opLSR_M(0x0093, 1);
            opROR_M(0x0092, 1);
            opDEX(1);
        } while (!flgZ);
    }
    a = myMapper->readCPU(0x0092);
    opORA(myMapper->readCPU(0x0093));
    if (flgZ) {
        goto L_003331;
    }
    a = myMapper->readCPU(0x0093);
    opORA(0xC0);
    myMapper->writeCPU(0x0093, a);
    flgC = true;
    popAddress();
    return;
L_003331:
    flgC = false;
    popAddress();
}

void game::SUB_00342E() {
    myMapper->writeCPU(0x0021, 0x87);
    do {
        a = 0x88;
        myMapper->writeCPU(0x001D, a);
        pushAddress(0x003436);
        SUB_0037DA();
        if (poppedEntry.value != 0x003436) return;
        x = a;
        y = myMapper->readCPU(0x0021);
        a = myMapper->readCPU(0x0246 + x);
        opPHA();
        a = myMapper->readCPU(0x0246 + y);
        myMapper->writeCPU(0x0246 + x, a);
        opPLA();
        myMapper->writeCPU(0x0246 + y, a);
        opDEC(0x0021, 1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_00344F() {
    opINC(0x0022, 1);
    a = myMapper->readCPU(0x0022);
    if (a != 0x38) {
        opAND(0x0F);
        if (a != 0x0A) {
            goto L_003464;
        }
        a = myMapper->readCPU(0x0022);
        flgC = false;
        opADC(0x07);
        myMapper->writeCPU(0x0022, a);
    L_003464:
        popAddress();
        return;
    }
    myMapper->writeCPU(0x0022, 0xFF);
    popAddress();
}

void game::SUB_00346A() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = myMapper->readCPU(0x0098);
    opASL_A(1);
    x = a;
    myMapper->writeCPU(0x000F, myMapper->readCPU(0xF480 + x));
    opINX(1);
    a = myMapper->readCPU(0xF480 + x);
    myMapper->writeCPU(0x0010, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003488() {
    if (a >= 0x30) {
        goto L_0034E8;
    }
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x009C);
    opPHA();
    a = y;
    opPHA();
    a = x;
    opPHA();
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x0098));
    pushAddress(0x003499);
    SUB_0036FC();
    if (poppedEntry.value != 0x003499) return;
    if (!flgC) {
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
        opINC(0x009C, 1);
        pushAddress(0x0034AF);
        SUB_0036FC();
        if (poppedEntry.value != 0x0034AF) return;
        if (!flgC) {
            a = myMapper->readCPU(0x0200 + x);
            opPHA();
            a = myMapper->readCPU(0x0200 + y);
            myMapper->writeCPU(0x0200 + x, a);
            opPLA();
            myMapper->writeCPU(0x0200 + y, a);
            opINX(1);
            opINC(0x009C, 1);
            pushAddress(0x0034C5);
            SUB_0036FC();
            if (poppedEntry.value != 0x0034C5) return;
            if (flgC) {
                goto L_0034E1;
            }
            a = myMapper->readCPU(0x0200 + x);
            opPHA();
            a = myMapper->readCPU(0x0200 + y);
            myMapper->writeCPU(0x0200 + x, a);
            opPLA();
            myMapper->writeCPU(0x0200 + y, a);
            opINX(1);
            opPLA();
            opPLA();
            y = a;
            opPLA();
            myMapper->writeCPU(0x009C, a);
            flgC = false;
            popAddress();
            return;
        }
    }
L_0034E1:
    opPLA();
    x = a;
    opPLA();
    y = a;
    opPLA();
    myMapper->writeCPU(0x009C, a);
L_0034E8:
    flgC = true;
    popAddress();
}

void game::SUB_0034EA() {
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x009C);
    opPHA();
    a = myMapper->readCPU(0x0098);
    myMapper->writeCPU(0x009C, a);
    pushAddress(0x0034F3);
    SUB_00353E();
    if (poppedEntry.value != 0x0034F3) return;
    if (a >= 0x03) {
        goto L_0034FF;
    }
    opPLA();
    myMapper->writeCPU(0x009C, a);
    flgC = true;
    popAddress();
    return;
L_0034FF:
    a = y;
    opPHA();
    pushAddress(0x003501);
    SUB_0036FC();
    if (poppedEntry.value != 0x003501) return;
    a = myMapper->readCPU(0x0200 + x);
    opPHA();
    a = myMapper->readCPU(0x0200 + y);
    myMapper->writeCPU(0x0200 + x, a);
    opPLA();
    myMapper->writeCPU(0x0200 + y, a);
    opINX(1);
    pushAddress(0x003513);
    SUB_0036FC();
    if (poppedEntry.value != 0x003513) return;
    a = myMapper->readCPU(0x0200 + x);
    opPHA();
    a = myMapper->readCPU(0x0200 + y);
    myMapper->writeCPU(0x0200 + x, a);
    opPLA();
    myMapper->writeCPU(0x0200 + y, a);
    opINX(1);
    pushAddress(0x003525);
    SUB_0036FC();
    if (poppedEntry.value != 0x003525) return;
    a = myMapper->readCPU(0x0200 + x);
    opPHA();
    a = myMapper->readCPU(0x0200 + y);
    myMapper->writeCPU(0x0200 + x, a);
    opPLA();
    myMapper->writeCPU(0x0200 + y, a);
    opINX(1);
    opPLA();
    y = a;
    opPLA();
    myMapper->writeCPU(0x009C, a);
    flgC = false;
    popAddress();
}

void game::SUB_00353E() {
    myMapper->writeCPU(0x0098, a);
    a = x;
    opPHA();
    a = y;
    opPHA();
    y = 0x00;
    do {
        do {
            a = myMapper->readCPU(0x0200 + x);
            opINX(1);
            if (a == 0xFF) {
                goto L_003555;
            }
        } while (a != myMapper->readCPU(0x0098));
        opINY(1);
    } while (!flgZ);
L_003555:
    myMapper->writeCPU(0x0098, y);
    opPLA();
    y = a;
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0098);
    popAddress();
}

void game::SUB_00355E() {
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x009C);
    opPHA();
    a = myMapper->readCPU(0x0098);
    myMapper->writeCPU(0x009C, a);
    pushAddress(0x003567);
    SUB_00353E();
    if (poppedEntry.value != 0x003567) return;
    if (a >= 0x02) {
        goto L_003573;
    }
    opPLA();
    myMapper->writeCPU(0x009C, a);
    flgC = true;
    popAddress();
    return;
L_003573:
    a = y;
    opPHA();
    pushAddress(0x003575);
    SUB_0036FC();
    if (poppedEntry.value != 0x003575) return;
    a = myMapper->readCPU(0x0200 + x);
    opPHA();
    a = myMapper->readCPU(0x0200 + y);
    myMapper->writeCPU(0x0200 + x, a);
    opPLA();
    myMapper->writeCPU(0x0200 + y, a);
    opINX(1);
    pushAddress(0x003587);
    SUB_0036FC();
    if (poppedEntry.value != 0x003587) return;
    a = myMapper->readCPU(0x0200 + x);
    opPHA();
    a = myMapper->readCPU(0x0200 + y);
    myMapper->writeCPU(0x0200 + x, a);
    opPLA();
    myMapper->writeCPU(0x0200 + y, a);
    opINX(1);
    opPLA();
    y = a;
    opPLA();
    myMapper->writeCPU(0x009C, a);
    flgC = false;
    popAddress();
}

void game::SUB_0035A0() {
    if (a >= 0x30) {
        goto L_003602;
    }
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x009C);
    opPHA();
    a = y;
    opPHA();
    a = x;
    opPHA();
    myMapper->writeCPU(0x009C, myMapper->readCPU(0x0098));
    pushAddress(0x0035B1);
    SUB_0036FC();
    if (poppedEntry.value != 0x0035B1) return;
    if (!flgC) {
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
        opINC(0x009C, 1);
        pushAddress(0x0035C7);
        SUB_0036FC();
        if (poppedEntry.value != 0x0035C7) return;
        if (!flgC) {
            a = myMapper->readCPU(0x0200 + x);
            opPHA();
            a = myMapper->readCPU(0x0200 + y);
            myMapper->writeCPU(0x0200 + x, a);
            opPLA();
            myMapper->writeCPU(0x0200 + y, a);
            opINX(1);
            if (!flgZ) {
                goto L_0035F3;
            }
        }
        opINC(0x009C, 1);
        pushAddress(0x0035DF);
        SUB_0036FC();
        if (poppedEntry.value != 0x0035DF) return;
        if (flgC) {
            goto L_0035FB;
        }
        a = myMapper->readCPU(0x0200 + x);
        opPHA();
        a = myMapper->readCPU(0x0200 + y);
        myMapper->writeCPU(0x0200 + x, a);
        opPLA();
        myMapper->writeCPU(0x0200 + y, a);
        opINX(1);
    L_0035F3:
        opPLA();
        opPLA();
        y = a;
        opPLA();
        myMapper->writeCPU(0x009C, a);
        flgC = false;
        popAddress();
        return;
    }
L_0035FB:
    opPLA();
    x = a;
    opPLA();
    y = a;
    opPLA();
    myMapper->writeCPU(0x009C, a);
L_003602:
    flgC = true;
    popAddress();
}

void game::SUB_003604() {
    myMapper->writeCPU(0x0062, myMapper->readCPU(0x023A));
    myMapper->writeCPU(0x0064, myMapper->readCPU(0x0063));
    myMapper->writeCPU(0x0065, 0x00);
    popAddress();
}

void game::SUB_003612() {
    do {
        y = x;
        do {
            a = myMapper->readCPU(0x0200 + y);
            opINY(1);
            if (a == 0xFF) {
                goto L_003625;
            }
            pushAddress(0x00361C);
            SUB_00355E();
            if (poppedEntry.value != 0x00361C) return;
        } while (flgC);
        opINC(0x0064, 1);
    } while (!flgZ);
L_003625:
    myMapper->writeCPU(0x009E, 0x00);
    do {
        do {
            a = myMapper->readCPU(0x009E);
            pushAddress(0x00362B);
            SUB_003657();
            if (poppedEntry.value != 0x00362B) return;
            if (flgC) {
                goto L_00363B;
            }
            myMapper->writeCPU(0x009E, a);
            pushAddress(0x003632);
            SUB_0035A0();
            if (poppedEntry.value != 0x003632) return;
        } while (flgC);
        opINC(0x0065, 1);
    } while (!flgZ);
L_00363B:
    popAddress();
}

void game::SUB_00363C() {
    a = x;
    opPHA();
    myMapper->writeCPU(0x0098, 0xFF);
    do {
        do {
            a = myMapper->readCPU(0x0200 + x);
            opINX(1);
            if (a == 0xFF) {
                goto L_003652;
            }
            opCMP(a, myMapper->readCPU(0x0098));
        } while (flgC);
        myMapper->writeCPU(0x0098, a);
    } while (!flgZ);
L_003652:
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0098);
    popAddress();
}

void game::SUB_003657() {
    myMapper->writeCPU(0x0097, a);
    a = x;
    opPHA();
    x = 0xFF;
    myMapper->writeCPU(0x0098, x);
    opINX(1);
    do {
        do {
            do {
                do {
                    a = myMapper->readCPU(0x0200 + x);
                    opINX(1);
                    if (a == 0xFF) {
                        goto L_003676;
                    }
                } while (a >= myMapper->readCPU(0x0098));
                opCMP(a, myMapper->readCPU(0x0097));
            } while (!flgC);
        } while (flgZ);
        myMapper->writeCPU(0x0098, a);
    } while (!flgZ);
L_003676:
    opPLA();
    x = a;
    a = myMapper->readCPU(0x0098);
    opCMP(a, 0xFF);
    if (flgZ) {
        goto L_00367F;
    }
    flgC = false;
L_00367F:
    popAddress();
}

void game::SUB_003680() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    myMapper->writeCPU(0x0098, a);
    opPHA();
    a = y;
    opPHA();
    y = 0xFF;
    do {
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        if (a == 0xFF) {
            goto L_0036AE;
        }
    } while (a != myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0098, y);
    do {
        opINY(1);
    } while (myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y) != 0xFF);
    opDEY(1);
    a = y;
    opPHA();
    a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
    y = myMapper->readCPU(0x0098);
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    opPLA();
    y = a;
    a = 0xFF;
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
L_0036AE:
    opPLA();
    y = a;
    opPLA();
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_0036B4() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    opPHA();
    y = 0xFF;
    do {
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
    } while (!flgZ);
    opPLA();
    opPHA();
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    a = 0xFF;
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    x = myMapper->readCPU(0x0010);
    y = myMapper->readCPU(0x000F);
    opPLA();
    popAddress();
}

void game::SUB_0036D1() {
    myMapper->writeCPU(0x0097, a);
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        if (a == 0xFF) {
            goto L_0036FA;
        }
        if (a == myMapper->readCPU(0x0097)) {
            goto L_0036E6;
        }
        opINY(1);
    } while (!flgZ);
L_0036E6:
    a = y;
    myMapper->writeCPU(0x0098, a);
    flgC = false;
    opADC(myMapper->readCPU(0x000F));
    myMapper->writeCPU(0x000F, a);
    y = a;
    a = 0x00;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0010, a);
    x = a;
    a = myMapper->readCPU(0x0098);
    flgC = false;
    popAddress();
    return;
L_0036FA:
    flgC = true;
    popAddress();
}

void game::SUB_0036FC() {
    y = x;
    opDEY(1);
    do {
        opINY(1);
        a = myMapper->readCPU(0x0200 + y);
        if (a == 0xFF) {
            goto L_00370D;
        }
    } while (a != myMapper->readCPU(0x009C));
    flgC = false;
    popAddress();
    return;
L_00370D:
    flgC = true;
    popAddress();
}

void game::SUB_00370F() {
    a = x;
    opPHA();
    a = y;
    opPHA();
    x = 0x46;
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        myMapper->writeCPU(0x0200 + y, a);
        opINY(1);
        opDEX(1);
    } while (!flgZ);
    opPLA();
    y = a;
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003725() {
    myMapper->writeCPU(0x0064, 0x00);
    a = 0x00;
    myMapper->writeCPU(0x009D, a);
    x = a;
    y = a;
    do {
        do {
            a = myMapper->readCPU(0x009D);
            pushAddress(0x003731);
            SUB_003657();
            if (poppedEntry.value != 0x003731) return;
            if (flgC) {
                goto L_00374B;
            }
            myMapper->writeCPU(0x009D, a);
            x = 0x00;
            pushAddress(0x00373A);
            SUB_00353E();
            if (poppedEntry.value != 0x00373A) return;
        } while (a < 0x02);
        myMapper->writeCPU(0x0446 + y, myMapper->readCPU(0x009D));
        opINY(1);
        opINC(0x0064, 1);
    } while (!flgZ);
L_00374B:
    myMapper->writeCPU(0x0446 + y, 0xFF);
    popAddress();
}

void game::SUB_003751() {
    a = 0x00;
    myMapper->writeCPU(0x009D, a);
    x = a;
    y = a;
    do {
        a = myMapper->readCPU(0x009D);
        pushAddress(0x003759);
        SUB_003657();
        if (poppedEntry.value != 0x003759) return;
        if (flgC) {
            goto L_003766;
        }
        myMapper->writeCPU(0x009D, a);
        myMapper->writeCPU(0x044E + y, a);
        opINY(1);
    } while (!flgZ);
L_003766:
    myMapper->writeCPU(0x044E + y, 0xFF);
    popAddress();
}

void game::SUB_00376C() {
    if (a == 0x00) {
        goto L_00379A;
    }
    myMapper->writeCPU(0x0098, a);
    if (a < 0x30) {
        opAND(0x0F);
        if (a != 0x09) {
            goto L_003794;
        }
        a = myMapper->readCPU(0x0098);
        opAND(0xF0);
        opORA(0x01);
        if (!flgZ) {
            goto L_003798;
        }
    }
    if (a == 0x34) {
        a = 0x31;
        setLoadFlag(a);
        if (!flgZ) {
            goto L_003798;
        }
    }
    if (a != 0x37) {
        goto L_003794;
    }
    a = 0x35;
    setLoadFlag(a);
    if (!flgZ) {
        goto L_003798;
    }
L_003794:
    opINC(0x0098, 1);
    a = myMapper->readCPU(0x0098);
L_003798:
    myMapper->writeCPU(0x0098, a);
L_00379A:
    popAddress();
}

void game::SUB_00379B() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0xFF;
    myMapper->writeCPU(0x009A, y);
    opINY(1);
    if (myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y) != 0xFF) {
        goto L_0037AF;
    }
L_0037AA:
    x = myMapper->readCPU(0x0010);
    y = myMapper->readCPU(0x000F);
    popAddress();
    return;
    do {
    L_0037AF:
        if (myMapper->readCPU(0x009A) == 0) {
            goto L_0037AA;
        }
        x = 0xFF;
        myMapper->writeCPU(0x0097, x);
        opINX(1);
        myMapper->writeCPU(0x009A, x);
    L_0037BA:
        opINC(0x0097, 1);
        y = myMapper->readCPU(0x0097);
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
    } while (a == 0xFF);
    opDEY(1);
    if (a >= myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y)) {
        goto L_0037BA;
    }
    x = a;
    a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
    opPHA();
    a = x;
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    opINY(1);
    opPLA();
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    opINC(0x009A, 1);
    goto L_0037BA;
}

void game::SUB_0037DA() {
    myMapper->writeCPU(0x001D, a);
    a = x;
    opPHA();
    a = myMapper->readCPU(0x001F);
    opROL_A(3);
    opEOR(myMapper->readCPU(0x0020));
    opROR_A(1);
    pushStatus();
    a = myMapper->readCPU(0x001F);
    opEOR(myMapper->readCPU(0x0020));
    myMapper->writeCPU(0x001F, a);
    a = myMapper->readCPU(0x001E);
    opEOR(myMapper->readCPU(0x0020));
    myMapper->writeCPU(0x0020, a);
    popStatus();
    opROL_M(0x0020, 1);
    opROL_M(0x001F, 1);
    a = myMapper->readCPU(0x001D);
    opPHA();
    a = myMapper->readCPU(0x001F);
    opEOR(myMapper->readCPU(0x0020));
    myMapper->writeCPU(0x001D, a);
    opPLA();
    if (flgZ) {
        goto L_003812;
    }
    x = a;
    a = myMapper->readCPU(0x001D);
    myMapper->writeCPU(0x001D, x);
    do {
        flgC = true;
        opSBC(myMapper->readCPU(0x001D));
    } while (flgC);
    opADC(myMapper->readCPU(0x001D));
    myMapper->writeCPU(0x001D, a);
L_003812:
    opPLA();
    x = a;
    a = myMapper->readCPU(0x001D);
    popAddress();
}

void game::SUB_003817() {
    myMapper->writeCPU(0x000F, 0xE6);
    myMapper->writeCPU(0x0010, 0x03);
    y = 0x00;
    myMapper->writeCPU(0x0011, 0xEF);
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, 0xFA);
    if (myMapper->readCPU(0x0098) & 0x80) {
        myMapper->writeCPU(0x0011, 0xDF);
        myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, 0xEB);
        a = 0xFF;
        opEOR(myMapper->readCPU(0x0098));
        myMapper->writeCPU(0x0098, a);
        a = 0xFF;
        opEOR(myMapper->readCPU(0x0097));
        myMapper->writeCPU(0x0097, a);
        opINC(0x0097, 1);
        if (!flgZ) {
            goto L_003847;
        }
        opINC(0x0098, 1);
    }
L_003847:
    opINY(1);
    myMapper->writeCPU(0x009A, 0x27);
    myMapper->writeCPU(0x0099, 0x10);
    pushAddress(0x003850);
    SUB_003898();
    if (poppedEntry.value != 0x003850) return;
    myMapper->writeCPU(0x009A, 0x03);
    myMapper->writeCPU(0x0099, 0xE8);
    pushAddress(0x00385B);
    SUB_003898();
    if (poppedEntry.value != 0x00385B) return;
    myMapper->writeCPU(0x009A, 0x00);
    myMapper->writeCPU(0x0099, 0x64);
    pushAddress(0x003866);
    SUB_003898();
    if (poppedEntry.value != 0x003866) return;
    myMapper->writeCPU(0x009A, 0x00);
    myMapper->writeCPU(0x0099, 0x0A);
    pushAddress(0x003871);
    SUB_003898();
    if (poppedEntry.value != 0x003871) return;
    opINC(0x0011, 1);
    a = myMapper->readCPU(0x0011);
    flgC = false;
    opADC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, a);
    y = 0x01;
    do {
        if (myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y) != myMapper->readCPU(0x0011)) {
            goto L_00388C;
        }
        myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, 0xEA);
        opINY(1);
    } while (!flgZ);
L_00388C:
    y = 0x06;
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, myMapper->readCPU(0x0011));
    opINY(1);
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, 0x00);
    popAddress();
}

void game::SUB_003898() {
    x = myMapper->readCPU(0x0011);
    do {
        opINX(1);
        a = myMapper->readCPU(0x0097);
        flgC = true;
        opSBC(myMapper->readCPU(0x0099));
        myMapper->writeCPU(0x0097, a);
        a = myMapper->readCPU(0x0098);
        opSBC(myMapper->readCPU(0x009A));
        myMapper->writeCPU(0x0098, a);
    } while (flgC);
    a = myMapper->readCPU(0x0097);
    opADC(myMapper->readCPU(0x0099));
    myMapper->writeCPU(0x0097, a);
    a = myMapper->readCPU(0x0098);
    opADC(myMapper->readCPU(0x009A));
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y, x);
    opINY(1);
    popAddress();
}

void game::SUB_0038BB() {
    a = myMapper->readCPU(0x0098);
    opPHA();
    a = myMapper->readCPU(0x0097);
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    pushAddress(0x0038C5);
    SUB_003817();
    if (poppedEntry.value != 0x0038C5) return;
    x = 0x03;
    y = 0xE6;
    pushAddress(0x0038CC);
    SUB_003CBE();
    if (poppedEntry.value != 0x0038CC) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    myMapper->writeCPU(0x0097, a);
    opPLA();
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_0038DA() {
    myMapper->writeCPU(0x009B, a);
    a = myMapper->readCPU(0x0098);
    opPHA();
    a = myMapper->readCPU(0x0097);
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    pushAddress(0x0038E6);
    SUB_003817();
    if (poppedEntry.value != 0x0038E6) return;
    a = myMapper->readCPU(0x009B);
    if (a < 0x10) {
        goto L_0038FA;
    }
    opAND(0x03);
    myMapper->writeCPU(0x009B, a);
    opINC(0x009B, 1);
    myMapper->writeCPU(0x03EC, 0x00);
L_0038FA:
    a = 0x07;
    flgC = true;
    opSBC(myMapper->readCPU(0x009B));
    flgC = false;
    opADC(0xE6);
    y = a;
    a = 0x00;
    opADC(0x03);
    x = a;
    pushAddress(0x003908);
    SUB_003CBE();
    if (poppedEntry.value != 0x003908) return;
    opPLA();
    y = a;
    opPLA();
    x = a;
    opPLA();
    myMapper->writeCPU(0x0097, a);
    opPLA();
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_003916() {
    a = x;
    opPHA();
    x = myMapper->readCPU(0x0098);
    a = 0x00;
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(0x009A, a);
    myMapper->writeCPU(0x0099, a);
    while (true) {
        a = x;
        setLoadFlag(a);
        if (flgZ) {
            goto L_00393E;
        }
        opLSR_A(1);
        x = a;
        if (!flgC) {
            goto L_003937;
        }
        a = myMapper->readCPU(0x009A);
        flgC = false;
        opADC(myMapper->readCPU(0x0097));
        myMapper->writeCPU(0x009A, a);
        a = myMapper->readCPU(0x0098);
        opADC(myMapper->readCPU(0x0099));
        myMapper->writeCPU(0x0098, a);
    L_003937:
        opASL_M(0x0097, 1);
        opROL_M(0x0099, 1);
    }
L_00393E:
    a = myMapper->readCPU(0x009A);
    myMapper->writeCPU(0x0097, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003945() {
    y = 0x43;
    myMapper->writeCPU(0x0097, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    opINY(1);
    myMapper->writeCPU(0x0098, myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    a = 0x06;
    SUB_0038DA();
    return;
}

void game::SUB_003955() {
    a = 0x00;
    flgC = true;
    opSBC(myMapper->readCPU(0x0097));
    myMapper->writeCPU(0x0097, a);
    a = 0x00;
    opSBC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0098, a);
    popAddress();
}

void game::SUB_003966() {
    a = y;
    opPHA();
    y = 0x43;
    a = myMapper->readCPU(0x0097);
    flgC = false;
    opADC(myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x0097, a);
    opINY(1);
    a = myMapper->readCPU(0x0098);
    opADC(myMapper->readCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y));
    myMapper->writeCPU(myMapper->readCPU(0x00A2) + (myMapper->readCPU((0x00A2 + 1) & 0x00ff) << 8) + y, a);
    myMapper->writeCPU(0x0098, a);
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_00397F() {
    a = 0x00;
    myMapper->writeCPU(0x0000, a);
    myMapper->writeCPU(0x0001, a);
    myMapper->writeCPU(0x0700, a);
    myMapper->writeCPU(0x0004, a);
    myMapper->writeCPU(0x0003, a);
    myMapper->writeCPU(0x0017, a);
    myMapper->writeCPU(0x0008, 0xF8);
    a = 0x99;
    myMapper->writeCPU(0x0006, a);
    myMapper->writeCPU(0x2000, a);
    pushAddress(0x003999);
    SUB_003A52();
    if (poppedEntry.value != 0x003999) return;
    myMapper->writeCPU(0x000D, 0x08);
    myMapper->writeCPU(0x000E, 0x3F);
    x = 0xFF;
    y = 0xB9;
    pushAddress(0x0039A8);
    SUB_003CC1();
    if (poppedEntry.value != 0x0039A8) return;
    myMapper->writeCPU(0x4015, 0x07);
    x = 0x00;
    y = 0x7E;
    pushAddress(0x0039B4);
    SUB_003A33();
    if (poppedEntry.value != 0x0039B4) return;
    pushAddress(0x0039B7);
    SUB_003A33();
    if (poppedEntry.value != 0x0039B7) return;
    opINY(1);
    pushAddress(0x0039BB);
    SUB_003A33();
    if (poppedEntry.value != 0x0039BB) return;
    pushAddress(0x0039BE);
    SUB_003A28();
    if (poppedEntry.value != 0x0039BE) return;
    pushAddress(0x0039C1);
    SUB_003A28();
    if (poppedEntry.value != 0x0039C1) return;
    pushAddress(0x0039C4);
    SUB_003A28();
    if (poppedEntry.value != 0x0039C4) return;
    pushAddress(0x0039C7);
    SUB_003A28();
    if (poppedEntry.value != 0x0039C7) return;
    y = 0x6E;
    a = 0x03;
    pushAddress(0x0039CE);
    SUB_003A44();
    if (poppedEntry.value != 0x0039CE) return;
    myMapper->writeCPU(0x0005, 0x24);
    pushAddress(0x0039D5);
    SUB_0039DC();
    if (poppedEntry.value != 0x0039D5) return;
    myMapper->writeCPU(0x0005, 0x20);
    SUB_0039DC();
    return;
}

void game::SUB_0039DC() {
L_0039DC:
    if (myMapper->readCPU(0x0000) != myMapper->readCPU(0x0001)) {
        wait();
        goto L_0039DC;
    }
    pushAddress(0x0039E2);
    SUB_003A52();
    if (poppedEntry.value != 0x0039E2) return;
    a = myMapper->readCPU(0x0006);
    opAND(0x7F);
    myMapper->writeCPU(0x2000, a);
    myMapper->writeCPU(0x2006, myMapper->readCPU(0x0005));
    myMapper->writeCPU(0x2006, 0x00);
    a = 0xEA;
    x = 0xC0;
    y = 0x04;
    do {
        do {
            myMapper->writeCPU(0x2007, a);
            opDEX(1);
        } while (!flgZ);
        opDEY(1);
    } while (!flgZ);
    a = 0x00;
    x = 0x40;
    do {
        myMapper->writeCPU(0x2007, a);
        opDEX(1);
    } while (!flgZ);
    myMapper->writeCPU(0x0007, 0x1E);
    myMapper->writeCPU(0x0004, 0xFF);
    myMapper->writeCPU(0x2000, myMapper->readCPU(0x0006));
    SUB_003A1C();
    return;
}

void game::SUB_003A1C() {
    x = 0x00;
    do {
        a = x;
        pushAddress(0x003A1F);
        SUB_003A81();
        if (poppedEntry.value != 0x003A1F) return;
        opINX(1);
        opCMP(x, 0x10);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003A28() {
    y = 0x6F;
    a = 0x02;
    pushAddress(0x003A2C);
    SUB_003A44();
    if (poppedEntry.value != 0x003A2C) return;
    a = 0x02;
    setLoadFlag(a);
    if (!flgZ) {
        SUB_003A44();
        return;
    }
    SUB_003A33();
    return;
}

void game::SUB_003A33() {
    a = 0x02;
    pushAddress(0x003A35);
    SUB_003A44();
    if (poppedEntry.value != 0x003A35) return;
    a = 0x42;
    pushAddress(0x003A3A);
    SUB_003A44();
    if (poppedEntry.value != 0x003A3A) return;
    a = 0xC2;
    pushAddress(0x003A3F);
    SUB_003A44();
    if (poppedEntry.value != 0x003A3F) return;
    a = 0x82;
    SUB_003A44();
    return;
}

void game::SUB_003A44() {
    opPHA();
    opINX(1);
    a = y;
    myMapper->writeCPU(0x0600 + x, a);
    opINX(1);
    opPLA();
    myMapper->writeCPU(0x0600 + x, a);
    opINX(2);
    popAddress();
}

void game::SUB_003A52() {
    a = 0x00;
    myMapper->writeCPU(0x0007, a);
    myMapper->writeCPU(0x0004, a);
    a = myMapper->readCPU(0x0009);
    do {
        wait();
        opCMP(a, myMapper->readCPU(0x0009));
    } while (flgZ);
    popAddress();
}

void game::SUB_003A5F() {
    a = x;
    opPHA();
    pushAddress(0x003A61);
    SUB_003ADD();
    if (poppedEntry.value != 0x003A61) return;
    a = myMapper->readCPU(0x0039);
    opASL_A(3);
    flgC = false;
    opADC(0x30);
    x = a;
    pushAddress(0x003A6D);
    SUB_003AF0();
    if (poppedEntry.value != 0x003A6D) return;
    a = 0x07;
    flgC = false;
    opADC(myMapper->readCPU(0x000A));
    myMapper->writeCPU(0x000A, a);
    pushAddress(0x003A77);
    SUB_003AF0();
    if (poppedEntry.value != 0x003A77) return;
    a = 0xFF;
    myMapper->writeCPU(0x0004, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003A81() {
    opPHA();
    myMapper->writeCPU(0x000B, 0x1D);
    a = 0x00;
    setLoadFlag(a);
    if (flgZ) {
        SUB_003A8D();
        return;
    }
    SUB_003A8A();
    return;
}

void game::SUB_003A8A() {
    opPHA();
    a = 0x08;
    SUB_003A8D();
    return;
}

void game::SUB_003A8D() {
    myMapper->writeCPU(0x0098, a);
    opPLA();
    opASL_A(4);
    myMapper->writeCPU(0x000C, a);
    pushAddress(0x003A96);
    SUB_003ADD();
    if (poppedEntry.value != 0x003A96) return;
    a = x;
    opPHA();
    x = myMapper->readCPU(0x000C);
    pushAddress(0x003A9D);
    SUB_003AF0();
    if (poppedEntry.value != 0x003A9D) return;
    a = myMapper->readCPU(0x0098);
    flgC = false;
    opADC(myMapper->readCPU(0x000A));
    myMapper->writeCPU(0x000A, a);
    pushAddress(0x003AA7);
    SUB_003AF0();
    if (poppedEntry.value != 0x003AA7) return;
    a = myMapper->readCPU(0x0098);
    flgC = false;
    opADC(myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x000B, a);
    pushAddress(0x003AB1);
    SUB_003AF0();
    if (poppedEntry.value != 0x003AB1) return;
    a = myMapper->readCPU(0x000A);
    flgC = true;
    opSBC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x000A, a);
    pushAddress(0x003ABB);
    SUB_003AF0();
    if (poppedEntry.value != 0x003ABB) return;
    a = 0xFF;
    myMapper->writeCPU(0x0004, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003AC5() {
    a = x;
    opPHA();
    pushAddress(0x003AC7);
    SUB_003ADD();
    if (poppedEntry.value != 0x003AC7) return;
    a = myMapper->readCPU(0x000B);
    flgC = false;
    opADC(0x04);
    myMapper->writeCPU(0x000B, a);
    x = 0x50;
    pushAddress(0x003AD3);
    SUB_003AF0();
    if (poppedEntry.value != 0x003AD3) return;
    a = 0xFF;
    myMapper->writeCPU(0x0004, a);
    opPLA();
    x = a;
    popAddress();
}

void game::SUB_003ADD() {
    a = myMapper->readCPU(0x000A);
    opASL_A(3);
    opADC(0x08);
    myMapper->writeCPU(0x000A, a);
    a = myMapper->readCPU(0x000B);
    opASL_A(3);
    opADC(0x0F);
    myMapper->writeCPU(0x000B, a);
    popAddress();
}

void game::SUB_003AF0() {
    myMapper->writeCPU(0x0600 + x, myMapper->readCPU(0x000B));
    opINX(3);
    myMapper->writeCPU(0x0600 + x, myMapper->readCPU(0x000A));
    opINX(1);
    popAddress();
}

void game::SUB_003AFF() {
    loopCounter = 0x00;
    pushAddress(0x003AFF);
    SUB_003A1C();
    if (poppedEntry.value != 0x003AFF) return;
    x = 0x00;
    do {
        opINC(0x0008, 1);
        if (!flgZ) {
            goto L_003B0E;
        }
        a = myMapper->readCPU(0x0006);
        opEOR(0x01);
        myMapper->writeCPU(0x0006, a);
    L_003B0E:
        y = 0x00;
        do {
            opPHA();
            opPLA();
            opDEY(1);
        } while (!flgZ);

		loopCounter++;
        if(loopCounter >= 0x08) {
            wait();
			loopCounter = 0x00;
		}
        opDEX(1);
    } while (!flgZ);
    popAddress();
}

void game::SUB_003B19() {
    myMapper->writeCPU(0x000D, 0x00);
    myMapper->writeCPU(0x000E, 0x3F);
    SUB_003CC1();
    return;
}

void game::SUB_003B24() {
    myMapper->writeCPU(0x000E, 0x00);
    a = myMapper->readCPU(0x000B);
    opASL_A(1);
    opROL_M(0x000E, 1);
    opASL_A(1);
    opROL_M(0x000E, 1);
    opASL_A(1);
    opROL_M(0x000E, 1);
    opASL_A(1);
    opROL_M(0x000E, 1);
    opASL_A(1);
    opROL_M(0x000E, 1);
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x000A);
    flgC = false;
    opADC(myMapper->readCPU(0x000D));
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x0005);
    opADC(myMapper->readCPU(0x000E));
    myMapper->writeCPU(0x000E, a);
    popAddress();
}

void game::SUB_003B49() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0x00;
    while (true) {
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        opINY(1);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_003B5C;
        }
        pushAddress(0x003B56);
        SUB_003BDE();
        if (poppedEntry.value != 0x003B56) return;
    }
L_003B5C:
    popAddress();
}

void game::SUB_003B5D() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        if (flgZ) {
            goto L_003B6D;
        }
        pushAddress(0x003B67);
        SUB_003C68();
        if (poppedEntry.value != 0x003B67) return;
        opINY(1);
    } while (!flgZ);
L_003B6D:
    opINY(1);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x000F));
    y = a;
    a = 0x00;
    opADC(myMapper->readCPU(0x0010));
    x = a;
    popAddress();
}

void game::SUB_003B79() {
    myMapper->writeCPU(0x0011, a);
    a = y;
    opPHA();
    a = myMapper->readCPU(0x000B);
    opAND(0xFC);
    opASL_A(1);
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x000A);
    opLSR_A(2);
    flgC = false;
    opADC(myMapper->readCPU(0x000D));
    opADC(0xC0);
    myMapper->writeCPU(0x000D, a);
    a = myMapper->readCPU(0x0005);
    flgC = false;
    opADC(0x03);
    myMapper->writeCPU(0x000E, a);
    a = 0x02;
    opAND(myMapper->readCPU(0x000B));
    myMapper->writeCPU(0x0098, a);
    a = myMapper->readCPU(0x000A);
    opAND(0x03);
    opLSR_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    opASL_A(1);
    myMapper->writeCPU(0x0098, a);
    myMapper->writeCPU(0x0097, 0xFC);
    a = myMapper->readCPU(0x0098);
    setLoadFlag(a);
    if (flgZ) {
        goto L_003BB8;
    }
    y = a;
    do {
        opASL_M(0x0011, 1);
        flgC = true;
        opROL_M(0x0097, 1);
        opDEY(1);
    } while (!flgZ);
L_003BB8:
    a = myMapper->readCPU(0x0001);
    opPHA();
    a = myMapper->readCPU(0x000E);
    pushAddress(0x003BBD);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BBD) return;
    a = myMapper->readCPU(0x000D);
    pushAddress(0x003BC2);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BC2) return;
    a = myMapper->readCPU(0x0097);
    pushAddress(0x003BC7);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BC7) return;
    a = myMapper->readCPU(0x0011);
    pushAddress(0x003BCC);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BCC) return;
    a = 0x00;
    pushAddress(0x003BD1);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BD1) return;
    opPLA();
    y = a;
    a = 0x01;
    myMapper->writeCPU(0x0700 + y, a);
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_003BDE() {
    myMapper->writeCPU(0x000C, a);
    a = y;
    opPHA();
    pushAddress(0x003BE2);
    SUB_003C38();
    if (poppedEntry.value != 0x003BE2) return;
    pushAddress(0x003BE5);
    SUB_003B24();
    if (poppedEntry.value != 0x003BE5) return;
    a = myMapper->readCPU(0x0001);
    opPHA();
    a = myMapper->readCPU(0x000E);
    pushAddress(0x003BED);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BED) return;
    a = myMapper->readCPU(0x000D);
    pushAddress(0x003BF2);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BF2) return;
    a = y;
    pushAddress(0x003BF6);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BF6) return;
    a = 0x00;
    pushAddress(0x003BFB);
    SUB_003CFC();
    if (poppedEntry.value != 0x003BFB) return;
    opPLA();
    y = a;
    a = 0x02;
    myMapper->writeCPU(0x0700 + y, a);
    opINC(0x000A, 2);
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_003C0C() {
    myMapper->writeCPU(0x000C, a);
    a = y;
    opPHA();
    pushAddress(0x003C10);
    SUB_003C38();
    if (poppedEntry.value != 0x003C10) return;
    pushAddress(0x003C13);
    SUB_003B24();
    if (poppedEntry.value != 0x003C13) return;
    a = myMapper->readCPU(0x0001);
    opPHA();
    a = myMapper->readCPU(0x000E);
    pushAddress(0x003C1B);
    SUB_003CFC();
    if (poppedEntry.value != 0x003C1B) return;
    a = myMapper->readCPU(0x000D);
    pushAddress(0x003C20);
    SUB_003CFC();
    if (poppedEntry.value != 0x003C20) return;
    a = y;
    pushAddress(0x003C24);
    SUB_003CFC();
    if (poppedEntry.value != 0x003C24) return;
    a = 0x00;
    pushAddress(0x003C29);
    SUB_003CFC();
    if (poppedEntry.value != 0x003C29) return;
    opPLA();
    y = a;
    a = 0x05;
    myMapper->writeCPU(0x0700 + y, a);
    opINC(0x000A, 1);
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_003C38() {
    y = 0x00;
    a = myMapper->readCPU(0x000C);
    setLoadFlag(a);
    if (flgN) {
        goto L_003C42;
    }
    if (a != 0x39) {
        goto L_003C43;
    }
L_003C42:
    opINY(1);
L_003C43:
    a = y;
    pushAddress(0x003C44);
    SUB_003B79();
    if (poppedEntry.value != 0x003C44) return;
    a = myMapper->readCPU(0x000C);
    opAND(0x3F);
    myMapper->writeCPU(0x000C, a);
    opAND(0xF0);
    opLSR_A(1);
    myMapper->writeCPU(0x0098, a);
    opLSR_A(3);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x0098, a);
    y = myMapper->readCPU(0x000C);
    opDEY(1);
    a = y;
    opAND(0x0F);
    opADC(myMapper->readCPU(0x0098));
    opASL_A(2);
    myMapper->writeCPU(0x0098, a);
    y = a;
    popAddress();
}

void game::SUB_003C68() {
    myMapper->writeCPU(0x000C, a);
    a = y;
    opPHA();
    a = myMapper->readCPU(0x000C);
    setLoadFlag(a);
    pushStatus();
    opAND(0x7F);
    flgC = true;
    opSBC(0x20);
    opCMP(a, 0x40);
    if (flgC) {
        opSBC(0x20);
    }
    myMapper->writeCPU(0x000C, a);
    opAND(0xF8);
    opASL_A(2);
    myMapper->writeCPU(0x0098, a);
    a = 0x07;
    opAND(myMapper->readCPU(0x000C));
    opASL_A(1);
    flgC = false;
    opADC(myMapper->readCPU(0x0098));
    myMapper->writeCPU(0x000C, a);
    y = 0x02;
    setLoadFlag(y);
    popStatus();
    if (!flgN) {
        goto L_003C92;
    }
    opINY(1);
L_003C92:
    a = y;
    pushAddress(0x003C93);
    SUB_003B79();
    if (poppedEntry.value != 0x003C93) return;
    pushAddress(0x003C96);
    SUB_003B24();
    if (poppedEntry.value != 0x003C96) return;
    a = myMapper->readCPU(0x0001);
    opPHA();
    a = myMapper->readCPU(0x000E);
    pushAddress(0x003C9E);
    SUB_003CFC();
    if (poppedEntry.value != 0x003C9E) return;
    a = myMapper->readCPU(0x000D);
    pushAddress(0x003CA3);
    SUB_003CFC();
    if (poppedEntry.value != 0x003CA3) return;
    a = myMapper->readCPU(0x000C);
    pushAddress(0x003CA8);
    SUB_003CFC();
    if (poppedEntry.value != 0x003CA8) return;
    a = 0x00;
    pushAddress(0x003CAD);
    SUB_003CFC();
    if (poppedEntry.value != 0x003CAD) return;
    opPLA();
    y = a;
    a = 0x03;
    myMapper->writeCPU(0x0700 + y, a);
    opINC(0x000A, 2);
    opPLA();
    y = a;
    popAddress();
}

void game::SUB_003CBE() {
    pushAddress(0x003CBE);
    SUB_003B24();
    if (poppedEntry.value != 0x003CBE) return;
    SUB_003CC1();
    return;
}

void game::SUB_003CC1() {
    myMapper->writeCPU(0x0010, x);
    myMapper->writeCPU(0x000F, y);
    a = myMapper->readCPU(0x0001);
    opPHA();
    a = myMapper->readCPU(0x000E);
    pushAddress(0x003CCA);
    SUB_003CFC();
    if (poppedEntry.value != 0x003CCA) return;
    a = myMapper->readCPU(0x000D);
    pushAddress(0x003CCF);
    SUB_003CFC();
    if (poppedEntry.value != 0x003CCF) return;
    y = 0x00;
    do {
        a = myMapper->readCPU(myMapper->readCPU(0x000F) + (myMapper->readCPU((0x000F + 1) & 0x00ff) << 8) + y);
        setLoadFlag(a);
        pushStatus();
        pushAddress(0x003CD7);
        SUB_003CFC();
        if (poppedEntry.value != 0x003CD7) return;
        opINC(0x000A, 1);
        opINY(1);
        popStatus();
    } while (!flgZ);
    opDEC(0x000A, 1);
    a = y;
    flgC = false;
    opADC(myMapper->readCPU(0x000F));
    y = a;
    a = 0x00;
    opADC(myMapper->readCPU(0x0010));
    myMapper->writeCPU(0x0098, a);
    a = 0x00;
    pushAddress(0x003CEF);
    SUB_003CFC();
    if (poppedEntry.value != 0x003CEF) return;
    opPLA();
    x = a;
    a = 0x04;
    myMapper->writeCPU(0x0700 + x, a);
    x = myMapper->readCPU(0x0098);
    popAddress();
}

void game::SUB_003CFC() {
    opPHA();
    myMapper->writeCPU(0x0098, y);
    opINC(0x0001, 1);
	bool firstLoop = true;
    do {
        if (firstLoop) firstLoop = false;
        else wait();
        y = myMapper->readCPU(0x0001);
        opCMP(y, myMapper->readCPU(0x0000));
    } while (flgZ);
    opPLA();
    myMapper->writeCPU(0x0700 + y, a);
    y = myMapper->readCPU(0x0098);
    popAddress();
}

void game::nmi() {
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    if (myMapper->readCPU(0x0004) != 0) {
        myMapper->writeCPU(0x2003, 0x00);
        myMapper->writeCPU(0x4014, 0x06);
        myMapper->writeCPU(0x0004, 0x00);
        goto L_003D4F;
    }
    myMapper->writeCPU(0x0002, 0x0D);
    if (myMapper->readCPU(0x0003) == 0) {
        goto L_003D32;
    }
    opDEC(0x0002, 1);
    while (true) {
        while (true) {
            while (true) {
                while (true) {
                    while (true) {
                    L_003D32:
                        opDEC(0x0002, 1);
                        if (!flgN) {
                            y = myMapper->readCPU(0x0000);
                            x = myMapper->readCPU(0x0700 + y);
                            setLoadFlag(x);
                            if (!flgZ) {
                                opINY(1);
                                myMapper->writeCPU(0x0000, y);
                                opDEX(1);
                                if (flgZ) {
                                    goto L_003DA2;
                                }
                                opDEX(1);
                                if (flgZ) {
                                    goto L_003D7E;
                                }
                                opDEX(1);
                                if (flgZ) {
                                    goto L_003D78;
                                }
                                opDEX(1);
                                if (flgZ) {
                                    goto L_003D81;
                                }
                                opDEX(1);
                                if (flgZ) {
                                    goto L_003D7B;
                                }
                            }
                        }
                    L_003D4F:
                        myMapper->writeCPU(0x2005, myMapper->readCPU(0x0008));
                        myMapper->writeCPU(0x2005, 0xE0);
                        myMapper->writeCPU(0x2000, myMapper->readCPU(0x0006));
                        myMapper->writeCPU(0x2001, myMapper->readCPU(0x0007));
                        if (myMapper->readCPU(0x0003) == 0) {
                            goto L_003D6A;
                        }
                        pushAddress(0x003D67);
                        SUB_003E74();
                        if (poppedEntry.value != 0x003D67) return;
                    L_003D6A:
                        pushAddress(0x003D6A);
                        SUB_003ECA();
                        if (poppedEntry.value != 0x003D6A) return;
                        pushAddress(0x003D6D);
                        SUB_003E8B();
                        if (poppedEntry.value != 0x003D6D) return;
                        opINC(0x0009, 1);
                        opPLA();
                        y = a;
                        opPLA();
                        x = a;
                        opPLA();
                        return;
                    L_003D78:
                        goto L_003E05;
                    L_003D7B:
                        goto L_003E32;
                    L_003D7E:
                        goto L_003DD0;
                    L_003D81:
                        a = myMapper->readCPU(0x0700 + y);
                        opINY(1);
                        myMapper->writeCPU(0x2006, a);
                        myMapper->writeCPU(0x2006, myMapper->readCPU(0x0700 + y));
                        while (true) {
                            opINY(1);
                            a = myMapper->readCPU(0x0700 + y);
                            setLoadFlag(a);
                            if (flgZ) {
                                goto L_003D9A;
                            }
                            myMapper->writeCPU(0x2007, a);
                        }
                    L_003D9A:
                        opINY(1);
                        myMapper->writeCPU(0x0000, y);
                        opINC(0x001E, 1);
                    }
                L_003DA2:
                    a = myMapper->readCPU(0x0700 + y);
                    opINY(1);
                    myMapper->writeCPU(0x2006, a);
                    x = a;
                    a = myMapper->readCPU(0x0700 + y);
                    opINY(1);
                    myMapper->writeCPU(0x2006, a);
                    opPHA();
                    a = myMapper->readCPU(0x2007);
                    a = myMapper->readCPU(0x2007);
                    opAND(myMapper->readCPU(0x0700 + y));
                    opINY(1);
                    opORA(myMapper->readCPU(0x0700 + y));
                    opINY(1);
                    myMapper->writeCPU(0x0000, y);
                    y = a;
                    myMapper->writeCPU(0x2006, x);
                    opPLA();
                    myMapper->writeCPU(0x2006, a);
                    myMapper->writeCPU(0x2007, y);
                }
            L_003DD0:
                a = myMapper->readCPU(0x0700 + y);
                opINY(1);
                myMapper->writeCPU(0x2006, a);
                a = myMapper->readCPU(0x0700 + y);
                opINY(1);
                myMapper->writeCPU(0x2006, a);
                x = myMapper->readCPU(0x0700 + y);
                opINY(1);
                myMapper->writeCPU(0x0000, y);
                a = myMapper->readCPU(0xFF29 + x);
                opINX(1);
                myMapper->writeCPU(0x2007, a);
                a = myMapper->readCPU(0xFF29 + x);
                opINX(1);
                myMapper->writeCPU(0x2007, a);
                pushAddress(0x003DF2);
                SUB_003E5B();
                if (poppedEntry.value != 0x003DF2) return;
                a = myMapper->readCPU(0xFF29 + x);
                opINX(1);
                myMapper->writeCPU(0x2007, a);
                myMapper->writeCPU(0x2007, myMapper->readCPU(0xFF29 + x));
            }
        L_003E05:
            a = myMapper->readCPU(0x0700 + y);
            opINY(1);
            myMapper->writeCPU(0x2006, a);
            a = myMapper->readCPU(0x0700 + y);
            opINY(1);
            myMapper->writeCPU(0x2006, a);
            x = myMapper->readCPU(0x0700 + y);
            opINY(1);
            myMapper->writeCPU(0x0000, y);
            myMapper->writeCPU(0x2007, x);
            opINX(1);
            myMapper->writeCPU(0x2007, x);
            pushAddress(0x003E20);
            SUB_003E5B();
            if (poppedEntry.value != 0x003E20) return;
            a = x;
            flgC = false;
            opADC(0x0F);
            x = a;
            myMapper->writeCPU(0x2007, x);
            opINX(1);
            myMapper->writeCPU(0x2007, x);
        }
    L_003E32:
        a = myMapper->readCPU(0x0700 + y);
        opINY(1);
        myMapper->writeCPU(0x2006, a);
        a = myMapper->readCPU(0x0700 + y);
        opINY(1);
        myMapper->writeCPU(0x2006, a);
        x = myMapper->readCPU(0x0700 + y);
        opINY(1);
        myMapper->writeCPU(0x0000, y);
        opINX(1);
        a = myMapper->readCPU(0xFF29 + x);
        opINX(2);
        myMapper->writeCPU(0x2007, a);
        pushAddress(0x003E4F);
        SUB_003E5B();
        if (poppedEntry.value != 0x003E4F) return;
        myMapper->writeCPU(0x2007, myMapper->readCPU(0xFF29 + x));
    }
    SUB_003E5B();
    return;
}

void game::SUB_003E5B() {
    y = myMapper->readCPU(0x0000);
    opDEY(2);
    a = 0x20;
    flgC = false;
    opADC(myMapper->readCPU(0x0700 + y));
    opPHA();
    opDEY(1);
    a = 0x00;
    opADC(myMapper->readCPU(0x0700 + y));
    myMapper->writeCPU(0x2006, a);
    opPLA();
    myMapper->writeCPU(0x2006, a);
    popAddress();
}

void game::SUB_003E74() {
    needWaitScanline = true;
	waitScanline = 64;
    popAddress();
}

void game::SUB_003E74_B() {
    //    //wait for vblank
//L_003E74:
//    if (myMapper->readCPU(0x2002) & 0x80) {
//        goto L_003E74;
//    }
//    //loop until specific scan line
//    x = 0x84;
//    y = 0x08;
//    do {
//        do {
//            opDEX(1);
//        } while (!flgZ);
//        opDEY(1);
//    } while (!flgZ);
    //change background pattern table address
    a = myMapper->readCPU(0x0006);
    opEOR(0x10);
    myMapper->writeCPU(0x2000, a);
}

void game::SUB_003E8B() {
    x = 0x01;
    myMapper->writeCPU(0x4016, x);
    opDEX(1);
    myMapper->writeCPU(0x4016, x);
    x = 0x08;
    do {
        a = myMapper->readCPU(0x4016);
        opROR_A(1);
        opROR_M(0x0019, 1);
        opDEX(1);
    } while (!flgZ);
    a = myMapper->readCPU(0x0019);
    opAND(0x04);
    if (flgZ) {
        goto L_003EA9;
    }
    myMapper->writeCPU(0x001C, 0xFF);
L_003EA9:
    a = myMapper->readCPU(0x0019);
    opAND(0x03);
    myMapper->writeCPU(0x001A, a);
    a = myMapper->readCPU(0x0012);
    setLoadFlag(a);
    if (!flgZ) {
        goto L_003EB4;
    }
    do {
        popAddress();
        return;
    L_003EB4:
        a = myMapper->readCPU(0x0019);
        opAND(0x0C);
    } while (flgZ);
    flgI = false;
    x = 0x00;
    myMapper->writeCPU(0x0000, x);
    myMapper->writeCPU(0x0001, x);
    myMapper->writeCPU(0x0700, x);
    opINX(1);
    myMapper->writeCPU(0x0012, x);
    SUB_00006B();
    return;
}

void game::SUB_003ECA() {
    if (myMapper->readCPU(0x0017) == 0) {
        goto L_003F18;
    }
    opDEC(0x0013, 1);
    if (flgZ) {
        myMapper->writeCPU(0x0013, myMapper->readCPU(0x0014));
        y = myMapper->readCPU(0x0017);
        opINC(0x0017, 3);
        opDEY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0015) + (myMapper->readCPU((0x0015 + 1) & 0x00ff) << 8) + y);
        opCMP(a, 0xFF);
        if (flgZ) {
            goto L_003F19;
        }
        pushAddress(0x003EE5);
        SUB_0032FB();
        if (poppedEntry.value != 0x003EE5) return;
        if (flgC) {
            myMapper->writeCPU(0x4002, myMapper->readCPU(0x0092));
            myMapper->writeCPU(0x4003, myMapper->readCPU(0x0093));
        }
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0015) + (myMapper->readCPU((0x0015 + 1) & 0x00ff) << 8) + y);
        pushAddress(0x003EF7);
        SUB_0032FB();
        if (poppedEntry.value != 0x003EF7) return;
        if (flgC) {
            myMapper->writeCPU(0x4006, myMapper->readCPU(0x0092));
            myMapper->writeCPU(0x4007, myMapper->readCPU(0x0093));
        }
        opINY(1);
        a = myMapper->readCPU(myMapper->readCPU(0x0015) + (myMapper->readCPU((0x0015 + 1) & 0x00ff) << 8) + y);
        pushAddress(0x003F09);
        SUB_0032FB();
        if (poppedEntry.value != 0x003F09) return;
        if (!flgC) {
            goto L_003F18;
        }
        myMapper->writeCPU(0x400A, myMapper->readCPU(0x0092));
        myMapper->writeCPU(0x400B, myMapper->readCPU(0x0093));
    }
L_003F18:
    popAddress();
    return;
L_003F19:
    myMapper->writeCPU(0x0017, 0x00);
    popAddress();
}

