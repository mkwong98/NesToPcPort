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

void game::reset() {
    flgD = false;
    SUB_01C009();
    return;
}

void game::brk() {
    flgI = true;
L_01C00A:
    if (!(myMapper->readCPU(0x2002) & 0x80)) {
        goto L_01C00A;
    }
    do {
        a = myMapper->readCPU(0x2002);
        setLoadFlag(a);
    } while (!flgN);
    pushAddress(0xC016);
    jump(0xC132);
    if (handleReturnAddress(poppedEntry.value, 0xC016)) return;
    x = 0xFF;
    s = x;
    pushAddress(0xC01C);
    jump(0xC16D);
    if (handleReturnAddress(poppedEntry.value, 0xC01C)) return;
    pushAddress(0xC01F);
    jump(0xC18E);
    if (handleReturnAddress(poppedEntry.value, 0xC01F)) return;
    pushAddress(0xC022);
    jump(0xC19B);
    if (handleReturnAddress(poppedEntry.value, 0xC022)) return;
    pushAddress(0xC025);
    jump(0xC0F7);
    if (handleReturnAddress(poppedEntry.value, 0xC025)) return;
    pushAddress(0xC028);
    jump(0xC14B);
    if (handleReturnAddress(poppedEntry.value, 0xC028)) return;
    a = 0x06;
    myMapper->writeCPU(0x0024, a);
    pushAddress(0xC02F);
    jump(0xC1D4);
    if (handleReturnAddress(poppedEntry.value, 0xC02F)) return;
    a = myMapper->readCPU(0x006F);
    opORA(myMapper->readCPU(0x001A));
    opAND(0x0F);
    y = a;
    a = myMapper->readCPU(0xC03F + y);
    myMapper->writeCPU(0x006F, a);
    pushAddress(0xC03E);

    if (handleReturnAddress(poppedEntry.value, 0xC03E)) return;
    SUB_01C052();
    return;
}

void game::nmi() {
    pushStatus();
    opPHA();
    a = x;
    opPHA();
    a = y;
    opPHA();
    a = myMapper->readCPU(0x2002);
    y = myMapper->readCPU(0x001B);
    setLoadFlag(y);
    if (flgZ) {
        pushAddress(0xC061);
        jump(0xC132);
        if (handleReturnAddress(poppedEntry.value, 0xC061)) return;
        a = 0x00;
        myMapper->writeCPU(0x2003, a);
        myMapper->writeCPU(0x4014, 0x02);
        y = 0x00;
        pushAddress(0xC070);
        jump(0xC1D6);
        if (handleReturnAddress(poppedEntry.value, 0xC070)) return;
        pushAddress(0xC073);
        jump(0x800A);
        if (handleReturnAddress(poppedEntry.value, 0xC073)) return;
        pushAddress(0xC076);
        jump(0xC1D4);
        if (handleReturnAddress(poppedEntry.value, 0xC076)) return;
        a = myMapper->readCPU(0x00FE);
        x = myMapper->readCPU(0x001F);
        setLoadFlag(x);
        if (!flgZ) {
            x = myMapper->readCPU(0x001B);
            setLoadFlag(x);
            if (flgZ) {
                opDEC(0x001F, 1);
                if (flgZ) {
                    goto L_01C087;
                }
            }
            a = 0x00;
        }
    L_01C087:
        myMapper->writeCPU(0x2001, a);
        pushAddress(0xC08C);
        jump(0xF87D);
        if (handleReturnAddress(poppedEntry.value, 0xC08C)) return;
        pushAddress(0xC08F);
        jump(0xC11F);
        if (handleReturnAddress(poppedEntry.value, 0xC08F)) return;
        opINC(0x001B, 1);
        y = 0x00;
        pushAddress(0xC096);
        jump(0xC1D6);
        if (handleReturnAddress(poppedEntry.value, 0xC096)) return;
        pushAddress(0xC099);
        jump(0x838A);
        if (handleReturnAddress(poppedEntry.value, 0xC099)) return;
        pushAddress(0xC09C);
        jump(0xC1D4);
        if (handleReturnAddress(poppedEntry.value, 0xC09C)) return;
        y = 0x06;
        myMapper->writeCPU(0x0027, y);
        pushAddress(0xC0A3);
        jump(0xC8CD);
        if (handleReturnAddress(poppedEntry.value, 0xC0A3)) return;
        pushAddress(0xC0A6);
        jump(0xC1E4);
        if (handleReturnAddress(poppedEntry.value, 0xC0A6)) return;
        y = 0x00;
        pushAddress(0xC0AB);
        jump(0xC1D6);
        if (handleReturnAddress(poppedEntry.value, 0xC0AB)) return;
        pushAddress(0xC0AE);
        jump(0x8052);
        if (handleReturnAddress(poppedEntry.value, 0xC0AE)) return;
        pushAddress(0xC0B1);
        jump(0xC1D4);
        if (handleReturnAddress(poppedEntry.value, 0xC0B1)) return;
        pushAddress(0xC0B4);
        jump(0xCCEE);
        if (handleReturnAddress(poppedEntry.value, 0xC0B4)) return;
        a = 0x00;
        myMapper->writeCPU(0x001B, a);
        opPLA();
        y = a;
        opPLA();
        x = a;
        opPLA();
        popStatus();
        return;
    }
    a = myMapper->readCPU(0x00FE);
    x = myMapper->readCPU(0x001F);
    setLoadFlag(x);
    if (flgZ) {
        goto L_01C0C8;
    }
    a = 0x00;
L_01C0C8:
    myMapper->writeCPU(0x2001, a);
    pushAddress(0xC0CD);
    jump(0xF87D);
    if (handleReturnAddress(poppedEntry.value, 0xC0CD)) return;
    pushAddress(0xC0D0);
    jump(0xC11F);
    if (handleReturnAddress(poppedEntry.value, 0xC0D0)) return;
    pushAddress(0xC0D3);
    jump(0xC0D7);
    if (handleReturnAddress(poppedEntry.value, 0xC0D3)) return;
    pushAddress(0xC0D6);

    if (handleReturnAddress(poppedEntry.value, 0xC0D6)) return;
}




void game::jump(Uint16 target) {
    Uint32 tAddress = myMapper->readRealAddress(target);
    switch (tAddress) {

    default:
		string mapperMode = myMapper->getMapperMode();
        printf("Unhandled jump to address: %04X\n", target);
		exit(1);
    }
}
