#include "mapper.h"
#include "rom.h"

using namespace std;

Uint32 mapper::readRealAddress(Uint16 address) {
	return (address - 0x8000) % rom->prgROMSize;
}

string mapper::getMapperMode() {
	return "";
}