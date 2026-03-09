#include "mapper.h"
#include "rom.h"

using namespace std;



bool mapper::checkMemory(memoryCheck* check) {
	Uint16 value;
	if (check->valueAsAddress) {
		value = readCPU(check->value);
	}
	else {
		value = check->value;
	}
	value &= check->mask;

	Uint16 memValue = readCPU(check->address) & check->mask;

	switch (check->opType) {
	case memoryCheck::EQ:
		return memValue == value;
	case memoryCheck::NE:
		return memValue != value;
	case memoryCheck::GT:
		return memValue > value;
	case memoryCheck::LS:
		return memValue < value;
	case memoryCheck::GE:
		return memValue >= value;
	case memoryCheck::LE:
		return memValue <= value;
	default:
		return false;
	}
}

Uint32 mapper::readRealAddress(Uint16 address) {
	return (address - 0x8000) % rom->prgROMSize;
}

string mapper::getMapperMode() {
	return "";
}