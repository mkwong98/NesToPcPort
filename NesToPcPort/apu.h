#pragma once
#include <SDL3/SDL.h>

class console;

struct envelopeSettings {
	bool lengthCounterHalt;
	bool constantVolume;
	Uint8 volume; // 0-15
	bool envelopeStart;
	Uint8 dividerCounter;
	Uint8 decayLevelCounter;
	Uint8 outputVolume;
};

struct pulseSettings {
	Uint8 dutyCycle; // 0-3

	envelopeSettings envelope;

	bool sweepEnabled;
	Uint8 sweepPeriod; // 0-7
	bool sweepNegate;
	Uint8 sweepShift; // 0-7

	Uint16 timer;
	Uint8 lengthCounter;

	//sweep
	bool sweepReload;
	Uint8 sweepDivider;
	Uint16 targetPeriod; // Calculated target period after sweep

	bool enabled;
};

class apu
{
public:
	console* myConsole;

	pulseSettings pulse1Settings;
	pulseSettings pulse2Settings;

	//triangle settings
	bool triangleLengthCounterHalt;
	bool triangleLinearCounterReload;
	Uint8 triangleLinearCounterLoad;
	Uint16 triangleTimer;
	Uint8 triangleLengthCounter;
	Uint8 triangleLinearCounter;

	//noise settings
	envelopeSettings noiseEnvelope;
	Uint8 noiseLengthCounter;
	bool loopNoise;
	Uint16 noisePeriod;

	bool triangleEnabled;
	bool noiseEnabled;
	bool dmcEnabled;

	bool frameCounterMode;
	Uint8 frameCounter;
	bool irqInhibit;
	bool dmcInterrupt;
	bool frameInterrupt;
	static Uint64 apuTime;


	const Uint16 noisePeriodTable[16] = {
		4, 8, 16, 32, 64, 96, 128, 160,
		202, 254, 380, 508, 762, 1014, 2038, 4068
	};

	const Uint8 lengthCounterTable[32] = {
		10, 254, 20, 2, 40, 4, 80, 6,
		160, 8, 60, 10, 14, 12, 26, 14,
		12, 16, 24, 18, 48, 20, 96, 22,
		192, 24, 72, 26, 144, 28, 48, 30
	};

	apu();
	Uint8 readReg(Uint16 address);
	void writeReg(Uint16 address, Uint8 v);
	static Uint64 SDLCALL runFrame(void* userdata, SDL_TimerID timerID, Uint64 interval);
	void runFrame();

private:
	void writePulseReg0(pulseSettings* p, Uint8 v);
	void writePulseReg1(pulseSettings* p, Uint8 v);
	void writePulseReg2(pulseSettings* p, Uint8 v);
	void writePulseReg3(pulseSettings* p, Uint8 v);

	void writeReg4008(Uint8 v);
	void writeReg400A(Uint8 v);
	void writeReg400B(Uint8 v);

	void writeReg400C(Uint8 v);
	void writeReg400E(Uint8 v);
	void writeReg400F(Uint8 v);

	void writeReg4015(Uint8 v);
	Uint8 readReg4015();
	void writeReg4017(Uint8 v);

	void clockEnvelope(envelopeSettings* e);
	void clockPulseSweep(pulseSettings* p, bool isPulse1);
	void clockPulseLengthCounter(pulseSettings* p);
	void clockNoiseLengthCounter();

	void clockTriangleLengthCounter();
	void clockTriangleLinearCounter();
};

