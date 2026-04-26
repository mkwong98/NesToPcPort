#include "ppu.h"
#include "binaryUtil.h"
#include "rom.h"
#include "console.h"
#include "mapper.h"


ppu::ppu() {
	writeReg(0x2000, 0);
	writeReg(0x2001, 0);
	vblank = true;
	spriteOverflow = false;
	sprite0Hit = false;
	oamAddr = 0;
	wReg = false;
	readBuffer = 0;
	scrollX = 0;
	scrollY = 0;
	vramAddress = 0;
	ioBus = 0;
	frame = 0;
}


void ppu::render() {

	for (int i = 0; i < 256 * 240; i++) {
		bgScreenPixels[i].colourID = 0xFF;
		bgScreenPixels[i].tileID = 0xFFFF;
		spPixelLocations[i].clear();
	}

	for (int i = 0; i < 32 * 30; i++) {
		for (int j = 0; j < 4; j++) {
			bgScreenTiles[j][i].visible = false;
			bgScreenTiles[j][i].checkedForHDPackTile = false;
		}
	}
	for (int i = 0; i < 128; i++) {
		oamVisible[i] = false;
	}

	memset(bg0ColourIDs, 0xFF, 256 * 240);
	memset(oamIdx, 0xFF, 128 * 2);

	spScreenTiles.clear();

	Uint16 pixelID = 0;
	Uint8 frameScrollY = scrollY;
	Uint8 screenID;
	Uint16 bgTileID;
	sprite0Hit = false;
	for (Uint16 j = 0; j < 240; j++) {
		if(myConsole->cpu.needWaitScanline && myConsole->cpu.waitScanline == j) {
			myConsole->cpu.needWaitScanline = false;
			myConsole->cpu.atScanline(j);
		}
		Uint16 viewY = frameScrollY + j;
		Uint8 attributeShiftY = (((viewY % 240) % 32) >= 16 ? 4 : 0);
		Uint16 nametableAddress = baseNametableAddress;
		//check crossed nametable vertical boundary
		if (viewY >= 240) {
			nametableAddress ^= 0x800;
		}
		screenID = (nametableAddress >> 10) & 0x03;
		Uint16 nametableRowAddress = nametableAddress + (((viewY % 240) << 2) & 0xFFE0); //divide by 8 to get the row, multiply by 32 to get address of the row
		Uint16 nametableTileAddress = nametableRowAddress + (scrollX >> 3); //divide by 8 to get the column
		bgTileID = nametableTileAddress - nametableAddress;
		Uint8 nametableValue = myConsole->rom.mapper->readPPU(nametableTileAddress);

		Uint16 attributeTableAddress = nametableAddress + 0x3C0;
		Uint16 attributeTableRowAddress = attributeTableAddress + (((viewY % 240) >> 2) & 0xFFF8); //divide by 32 to get the row, multiply by 8 to get address of the row
		Uint16 attributeTableTileAddress = attributeTableRowAddress + (scrollX >> 5); //divide by 32 to get the column
		Uint8 attributeTableValue = myConsole->rom.mapper->readPPU(attributeTableTileAddress);

		Uint16 viewX = scrollX;
		Uint8 attributeShiftX = ((viewX % 32) >= 16 ? 2 : 0);
		Uint8 attributeID = attributeTableValue >> (attributeShiftY + attributeShiftX) & 0x03;

		Uint8 bgStripeID = viewY % 8;
		processedTile* processedTilePtr = myConsole->rom.mapper->getProcessedTile(bgPatternTableTileOffset + nametableValue);
		if (!bgScreenTiles[screenID][bgTileID].visible) {
			bgScreenTiles[screenID][bgTileID].visible = true;
			bgScreenTiles[screenID][bgTileID].patternID = processedTilePtr->tileID;
			bgScreenTiles[screenID][bgTileID].palette = palettes[0][attributeID];
			bgScreenTiles[screenID][bgTileID].y = j - (viewY & 0x07);
			bgScreenTiles[screenID][bgTileID].x = -(scrollX & 0x07);
		}

		Uint8 bg0ColourID = paletteRAM[0];
		if (greyscale) {
			bg0ColourID &= 0x30; // greyscale
		}

		Uint8 visibleSprites[MAX_SPRITE_PER_LINE];
		Uint8 visibleSpritesCnt = 0;
		processedTile* visibleSpriteProcessedTile[MAX_SPRITE_PER_LINE];
		Uint8 visibleSpriteLine[MAX_SPRITE_PER_LINE];
		for (Uint8 k = 0; k < MAX_SPRITE_PER_LINE; k++) {
			visibleSprites[k] = 0xFF; // no sprite
		}
		for (Uint8 k = 0; k < 64; k++) {
			Uint16 spriteY = oam[k * 4] + 1;
			if (j >= spriteY && j < spriteY + spriteHeight) {
				if (visibleSpritesCnt < MAX_SPRITE_PER_LINE) {
					visibleSpritesCnt++;
					visibleSprites[visibleSpritesCnt - 1] = k;
					Uint8 visibleLine = j - spriteY;
					bool isSecondTile = false;
					if (oam[k * 4 + 2] & 0x80) { // vertical flip
						visibleLine = spriteHeight - 1 - visibleLine;
					}
					if (spriteHeight == 8) {
						visibleSpriteProcessedTile[visibleSpritesCnt - 1] = myConsole->rom.mapper->getProcessedTile(spritePatternTableTileOffset + oam[k * 4 + 1]);
					}
					else {
						Uint16 patternTileID = oam[k * 4 + 1] & 0xFE; // ignore the least significant bit
						if (oam[k * 4 + 1] & 0x01) {
							patternTileID += (0x1000 >> 4);
						}
						if (visibleLine >= 8) {
							isSecondTile = true;
							visibleSprites[visibleSpritesCnt - 1] += 64;
							patternTileID++;
							visibleLine -= 8; // second half of the sprite
							if ((oam[k * 4 + 2] & 0x80)) 
								spriteY -= 8;
							else 
								spriteY += 8;
							
						}
						visibleSpriteProcessedTile[visibleSpritesCnt - 1] = myConsole->rom.mapper->getProcessedTile(patternTileID);
					}

					visibleSpriteLine[visibleSpritesCnt - 1] = visibleLine;
					if (!oamVisible[k + (isSecondTile ? 64 : 0)]) {
						oamVisible[k + (isSecondTile ? 64 : 0)] = true;
						oamIdx[k + (isSecondTile ? 64 : 0)] = spScreenTiles.size();
						spTileDetails spTile;
						spTile.patternID = visibleSpriteProcessedTile[visibleSpritesCnt - 1]->tileID;
						spTile.palette = palettes[1][oam[k * 4 + 2] & 0x03] | 0xFF000000;
						spTile.x = oam[k * 4 + 3];
						spTile.y = spriteY;
						spTile.hFlip = oam[k * 4 + 2] & 0x40;
						spTile.vFlip = oam[k * 4 + 2] & 0x80;
						spTile.front = !(oam[k * 4 + 2] & 0x20);
						spTile.spriteID = k + (isSecondTile ? 64 : 0);
						spTile.checkedForHDPackTile = false;
						spScreenTiles.push_back(spTile);
					}
				}
				else {
					spriteOverflow = true; // more than 8 sprites on the scanline
				}
			}
		}


		Uint8 paletteID = 0;
		for (Uint16 i = 0; i < 256; i++) {
			bg0ColourIDs[pixelID] = bg0ColourID;

			if ((viewX % 8) == 0 && i > 0) {
				//move to next tile
				if (viewX == 256) {
					screenID ^= 0x01;
					nametableRowAddress ^= 0x400;
					nametableTileAddress = nametableRowAddress;
					bgTileID = nametableTileAddress - (nametableAddress ^ 0x400);
					nametableValue = myConsole->rom.mapper->readPPU(nametableTileAddress);

					attributeTableRowAddress ^= 0x400;
					attributeTableTileAddress = attributeTableRowAddress;
					attributeTableValue = myConsole->rom.mapper->readPPU(attributeTableTileAddress);
					attributeShiftX = 0;
				}
				else {
					nametableTileAddress++;
					bgTileID++;
					nametableValue = myConsole->rom.mapper->readPPU(nametableTileAddress);

					if ((viewX % 32) == 0) {
						attributeTableTileAddress++;
					}
					if ((viewX % 16) == 0) {
						attributeShiftX ^= 2; // toggle attribute shift
					}
					attributeTableValue = myConsole->rom.mapper->readPPU(attributeTableTileAddress);
				}
				attributeID = (attributeTableValue >> (attributeShiftY + attributeShiftX)) & 0x03;
				processedTilePtr = myConsole->rom.mapper->getProcessedTile(bgPatternTableTileOffset + nametableValue);
				if (!bgScreenTiles[screenID][bgTileID].visible) {
					bgScreenTiles[screenID][bgTileID].visible = true;
					bgScreenTiles[screenID][bgTileID].patternID = processedTilePtr->tileID;
					bgScreenTiles[screenID][bgTileID].palette = palettes[0][attributeID];
					bgScreenTiles[screenID][bgTileID].y = j - (viewY & 0x07);
					bgScreenTiles[screenID][bgTileID].x = i;
				}
			}

			bgPixelDetails bgPixel;
			bgPixel.colourID = 0xFF;
			bgPixel.tileID = 0xFFFF;
			if (bgRenderingEnable) {
				if (i >= 8 or showLeftmostBg) {

					Uint8 pixelValue = (processedTilePtr->stripe[bgStripeID] >> ((7 - (viewX % 8)) << 1)) & 0x03;
					bgPixel.screenID = screenID;
					bgPixel.tileID = bgTileID;
					if (pixelValue != 0) {
						bgPixel.colourID = paletteRAM[(attributeID << 2) + pixelValue];
						if (greyscale) {
							bgPixel.colourID &= 0x30; // greyscale
						}
					}
					else {
						bgPixel.colourID = 0xFF;
					}
					bgPixel.x = viewX % 8;
					bgPixel.y = bgStripeID;
				}
			}
			bgScreenPixels[pixelID] = bgPixel;

			if (spriteRenderingEnable) {
				if (i >= 8 or showLeftmostSprite) {
					for (int k = 0; k < visibleSpritesCnt; k++) {
						Uint8 spriteID = visibleSprites[k];
						if (oam[(spriteID & 0x3F) * 4 + 3] <= i && oam[(spriteID & 0x3F) * 4 + 3] + 8 > i) {
							spPixelDetails spPixel;
							spPixel.tileID = oamIdx[spriteID];
							spPixel.visibleLine = visibleSpriteLine[k];
							spPixel.isAddition = false;

							Uint8 visiblePixel = i - oam[(spriteID & 0x3F) * 4 + 3];
							if (spScreenTiles[oamIdx[spriteID]].hFlip) {
								visiblePixel = 7 - visiblePixel;
							}
							spPixel.x = visiblePixel;

							Uint8 pixelValue = (visibleSpriteProcessedTile[k]->stripe[visibleSpriteLine[k]] >> ((7 - visiblePixel) << 1)) & 0x03;
							if (pixelValue == 0) {
								spPixel.colourID = 0xFF; // transparent pixel
							}
							else {
								spPixel.colourID = paletteRAM[16 + ((oam[(spriteID & 0x3F) * 4 + 2] & 0x03) << 2) + pixelValue];
								if (greyscale) {
									spPixel.colourID &= 0x30; // greyscale
								}

								//sprite 0 hit detection
								if ((!sprite0Hit) && spriteID == 0 && bgScreenPixels[pixelID].colourID != 0xFF && i < 255) {
									sprite0Hit = true;
									myConsole->cpu.atSprite0Hit();
									if(myConsole->waitType == 2) {
										myConsole->cpu.signal();
										SDL_WaitCondition(myConsole->cond, myConsole->lock);
									}
								}
							}
							spPixelLocations[pixelID].push_back(spPixel);
						}
					}
				}
			}
			viewX++;
			pixelID++;
		}
	}

	if (myConsole->waitType == 3) {
		myConsole->cpu.signal();
		SDL_WaitCondition(myConsole->cond, myConsole->lock);
	}
	vblank = true;
	sprite0Hit = false;
	frame++;
}

void ppu::signalNMI() {
	if (vblankNMIEnabled) {
		myConsole->cpu.pushAddress(0xFFFF);
		myConsole->cpu.pushStatus();
		myConsole->cpu.nmi();
	}
}

Uint8 ppu::readReg(Uint16 address) {
	switch (address) {
	case 0x2002:
		readReg2002();
		break;
	case 0x2004:
		readReg2004();
		break;
	case 0x2007:
		readReg2007();
		break;
	}
	return ioBus;
}

void ppu::writeReg(Uint16 address, Uint8 v) {
	ioBus = v;
	switch (address) {
	case 0x2000:
		writeReg2000();
		break;
	case 0x2001:
		writeReg2001();
		break;
	case 0x2003:
		writeReg2003();
		break;
	case 0x2004:
		writeReg2004();
		break;
	case 0x2005:
		writeReg2005();
		break;
	case 0x2006:
		writeReg2006();
		break;
	case 0x2007:
		writeReg2007();
		break;
	}
}


void ppu::writeReg2000() {
	switch (ioBus & 0x03) {
	case 0x00:
		baseNametableAddress = 0x2000;
		break;
	case 0x01:
		baseNametableAddress = 0x2400;
		break;
	case 0x02:
		baseNametableAddress = 0x2800;
		break;
	case 0x03:
		baseNametableAddress = 0x2C00;
		break;
	}
	vramAddressIncrement = (ioBus & 0x04 ? 32 : 1);
	spritePatternTable = (ioBus & 0x08 ? 0x1000 : 0x0000);
	spritePatternTableTileOffset = spritePatternTable >> 4;
	bgPatternTable = (ioBus & 0x10 ? 0x1000 : 0x0000);
	bgPatternTableTileOffset = bgPatternTable >> 4;
	spriteHeight = (ioBus & 0x20 ? 16 : 8);
	vblankNMIEnabled = ioBus & 0x80;
}

void ppu::writeReg2001() {
	greyscale = ioBus & 0x01;
	showLeftmostBg = ioBus & 0x02;
	showLeftmostSprite = ioBus & 0x04;
	bgRenderingEnable = ioBus & 0x08;
	spriteRenderingEnable = ioBus & 0x10;
	emphasizeRed = ioBus & 0x20;
	emphasizeGreen = ioBus & 0x40;
	emphasizeBlue = ioBus & 0x80;
}

void ppu::readReg2002() {
	ioBus &= 0x1F;
	if (spriteOverflow) ioBus |= 0x20;
	if (sprite0Hit) ioBus |= 0x40;
	if (vblank) ioBus |= 0x80;
	vblank = false;
	wReg = false;
}

void ppu::writeReg2003() {
	oamAddr = ioBus;
}

void ppu::readReg2004() {
	ioBus = oam[oamAddr];
}

void ppu::writeReg2004() {
	oam[oamAddr] = ioBus;
	binaryUtil::inc(&oamAddr);
	oamVisible[oamAddr / 4] = false;
}

void ppu::writeReg2005() {
	if (!wReg) scrollX = ioBus;
	else scrollY = ioBus;
	wReg = !wReg;
}

void ppu::writeReg2006() {
	if (!wReg) 
		vramAddress = (vramAddress & 0x00FF) | (ioBus << 8);
	else 
		vramAddress = (vramAddress & 0xFF00) | ioBus;
	wReg = !wReg;
}

void ppu::readReg2007() {
	ioBus = readBuffer;
	readBuffer = myConsole->rom.mapper->readPPU(vramAddress & 0x3FFF);
	vramAddress += vramAddressIncrement;
}

void ppu::writeReg2007() {
	myConsole->rom.mapper->writePPU(vramAddress & 0x3FFF, ioBus);
	vramAddress += vramAddressIncrement;
}

void ppu::writeReg4014(Uint8 v) {
	Uint16 pageAddress = v << 8;
	for (Uint16 i = 0; i < 256; i++) {
		oam[i] = myConsole->rom.mapper->readCPU(pageAddress + i);
	}
	for (int i = 0; i < 64; i++) {
		oamVisible[i] = false;
	}
}
