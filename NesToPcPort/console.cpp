#include <SDL3/SDL.h>
#include <string>
#include <sstream>
#include "console.h"

using namespace std;

int console::gameThread(void* ptr) {
	try {
		console* myConsole = (console*)ptr;
		SDL_LockMutex(myConsole->lock);
		myConsole->cpu.reset();
		SDL_UnlockMutex(myConsole->lock);
	}
	catch (const std::exception& e) {
	}
	return 0;
}

console::console() {
	cpu.myConsole = this;
	ppu.myConsole = this;
	apu.myConsole = this;
	rom.myConsole = this;
	iop.myConsole = this;

	renderer.myConsole = this;
	snd.myConsole = this;
	controllers.myConsole = this;
}

void console::runFrame() {
	if (!SDL_TryLockMutex(lock)) {
		return;
	}
	ppu.render();
	renderer.renderFrame();
	ppu.signalNMI();
	cpu.signal();
	SDL_UnlockMutex(lock);
}

void console::readConfig() {
	char* configData;
	size_t dataSize;
	configData = (char*)SDL_LoadFile("config.txt", &dataSize);
	string tmpStr = configData;
	tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), '\r'), tmpStr.end());
	stringstream s(tmpStr);
	string configLine;
	while (getline(s, configLine)) {
		size_t findIdx = configLine.find(":");
		if (findIdx > 0) {
			string lineHead = configLine.substr(0, findIdx);
			string lineTail = configLine.substr(findIdx + 1);

			if (lineHead == "ROM") {
				rom.loadROM(SDL_IOFromFile(lineTail.c_str(), "rb"));
			}
			else {
				size_t findIdx2 = lineTail.find("=");
				string valueHead = lineTail.substr(0, findIdx2);
				string valueTail = lineTail.substr(findIdx2 + 1);
				if (lineHead == "DISPLAY") {
					renderer.setConfig(valueHead, valueTail);
				}
				else if (lineHead == "CONTROL") {
					controllers.setConfig(valueHead, valueTail);
				}
			}
		}
	}
	SDL_free(configData);
}

void console::initThread() {
	lock = SDL_CreateMutex();
	cond = SDL_CreateCondition();
}

void console::closeThread() {
	cpu.gameEnded = true;
	if (SDL_TryLockMutex(lock)) {
		cpu.signal();
		SDL_UnlockMutex(lock);
	}
	cpu.endGame();
	SDL_DestroyCondition(cond);
	SDL_DestroyMutex(lock);
}


