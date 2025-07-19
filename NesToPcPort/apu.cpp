#include "apu.h"
#include "console.h"

apu::apu() {
	// Initialize pulse 1 settings
	pulse1Settings.dutyCycle = 0;
	pulse1Settings.envelope.lengthCounterHalt = false;
	pulse1Settings.envelope.constantVolume = false;
	pulse1Settings.envelope.volume = 0;
	pulse1Settings.sweepEnabled = false;
	pulse1Settings.sweepPeriod = 0;
	pulse1Settings.sweepNegate = false;
	pulse1Settings.sweepShift = 0;
	pulse1Settings.timer = 0;
	pulse1Settings.lengthCounter = 0;
	pulse1Settings.enabled = false;
	// Initialize envelope settings
	pulse1Settings.envelope.envelopeStart = false;
	pulse1Settings.envelope.dividerCounter = 0;
	pulse1Settings.envelope.decayLevelCounter = 0;
	pulse1Settings.envelope.outputVolume = 0;
	// Initialize sweep
	pulse1Settings.sweepReload = false;
	pulse1Settings.sweepDivider = 0;
	pulse1Settings.targetPeriod = 0;

	// Initialize pulse 2 settings
	pulse2Settings.dutyCycle = 0;
	pulse2Settings.envelope.lengthCounterHalt = false;
	pulse2Settings.envelope.constantVolume = false;
	pulse2Settings.envelope.volume = 0;
	pulse2Settings.sweepEnabled = false;
	pulse2Settings.sweepPeriod = 0;
	pulse2Settings.sweepNegate = false;
	pulse2Settings.sweepShift = 0;
	pulse2Settings.timer = 0;
	pulse2Settings.lengthCounter = 0;
	pulse2Settings.enabled = false;
	// Initialize envelope settings
	pulse2Settings.envelope.envelopeStart = false;
	pulse2Settings.envelope.dividerCounter = 0;
	pulse2Settings.envelope.decayLevelCounter = 0;
	pulse1Settings.envelope.outputVolume = 0;
	// Initialize sweep
	pulse2Settings.sweepReload = false;
	pulse2Settings.sweepDivider = 0;
	pulse2Settings.targetPeriod = 0;

	triangleLengthCounterHalt = false;
	triangleLinearCounterReload = false;
	triangleLinearCounterLoad = 0;
	triangleTimer = 0;
	triangleLengthCounter = 0;
	triangleLinearCounter = 0;

	noiseEnvelope.lengthCounterHalt = false;
	noiseEnvelope.constantVolume = false;
	noiseEnvelope.volume = 0;
	noiseLengthCounter = 0;
	loopNoise = false;
	noisePeriod = 0;
	noiseEnvelope.envelopeStart = false;
	noiseEnvelope.dividerCounter = 0;
	noiseEnvelope.decayLevelCounter = 0;
	noiseEnvelope.outputVolume = 0;


	triangleEnabled = false;
	noiseEnabled = false;
	dmcEnabled = false;
	frameCounterMode = false; // Default to mode 0
	frameCounter = 0; // Initialize frame counter
	irqInhibit = true; // Default to inhibit IRQs
	dmcInterrupt = false; // Default to no interrupt
	frameInterrupt = false; // Default to no frame interrupt

}

Uint8 apu::readReg(Uint16 address) {
	if (address == 0x4015) {
		return readReg4015();
	}
	else {
		return 0; // Other addresses are not defined for APU
	}
}

Uint8 apu::readReg4015() {
	Uint8 status = 0;
	if (pulse1Settings.enabled) status |= 0x01;
	if (pulse2Settings.enabled) status |= 0x02;
	if (triangleEnabled) status |= 0x04;
	if (noiseEnabled) status |= 0x08;
	if (dmcEnabled) status |= 0x10;
	if (frameInterrupt) status |= 0x40; // Frame interrupt flag
	if (dmcInterrupt) status |= 0x80; // Frame interrupt flag

	frameInterrupt = false;
	return status;
}

void apu::writeReg(Uint16 address, Uint8 v) {
	switch (address) {
	case 0x4000: writePulseReg0(&pulse1Settings, v); break;
	case 0x4001: writePulseReg1(&pulse1Settings, v); break;
	case 0x4002: writePulseReg2(&pulse1Settings, v); break;
	case 0x4003: writePulseReg3(&pulse1Settings, v); break;
	case 0x4004: writePulseReg0(&pulse2Settings, v); break;
	case 0x4005: writePulseReg1(&pulse2Settings, v); break;
	case 0x4006: writePulseReg2(&pulse2Settings, v); break;
	case 0x4007: writePulseReg3(&pulse2Settings, v); break;
	case 0x4008: writeReg4008(v); break;
	case 0x400A: writeReg400A(v); break;
	case 0x400B: writeReg400B(v); break;
	case 0x400C: writeReg400C(v); break;
	case 0x400E: writeReg400E(v); break;
	case 0x400F: writeReg400F(v); break;
	case 0x4015: writeReg4015(v); break;
	case 0x4017: writeReg4017(v); break;
	default:
		break; // Other addresses are not defined for APU
	}
}

void apu::runFrame() {
	// Frame counter logic
	if (frameCounterMode) {
		// Mode 1: 5-step frame counter
		// Implement frame counter logic for mode 1 here
		switch (frameCounter)
		{
		case 0:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			break;
		case 1:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			clockPulseSweep(&pulse1Settings, true); // Clock pulse 1 sweep
			clockPulseSweep(&pulse2Settings, false); // Clock pulse 2 sweep
			clockPulseLengthCounter(&pulse1Settings); // Clock pulse 1 length counter
			clockPulseLengthCounter(&pulse2Settings); // Clock pulse 2 length counter
			clockNoiseLengthCounter(); // Clock noise length counter
			break;
		case 2:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			break;
		case 3:
			break;
		case 4:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			clockPulseSweep(&pulse1Settings, true); // Clock pulse 1 sweep
			clockPulseSweep(&pulse2Settings, false); // Clock pulse 2 sweep
			clockPulseLengthCounter(&pulse1Settings); // Clock pulse 1 length counter
			clockPulseLengthCounter(&pulse2Settings); // Clock pulse 2 length counter
			clockNoiseLengthCounter(); // Clock noise length counter
			break;
		default:
			break;
		}
		if (frameCounter == 4) {
			frameInterrupt = 0;
		}
		else {
			frameCounter++;
		}
	}
	else {
		// Mode 0: 4-step frame counter
		switch (frameCounter)
		{
		case 0:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			break;
		case 1:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			clockPulseSweep(&pulse1Settings, true); // Clock pulse 1 sweep
			clockPulseSweep(&pulse2Settings, false); // Clock pulse 2 sweep
			clockPulseLengthCounter(&pulse1Settings); // Clock pulse 1 length counter
			clockPulseLengthCounter(&pulse2Settings); // Clock pulse 2 length counter
			clockNoiseLengthCounter(); // Clock noise length counter
			break;
		case 2:
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			break;
		case 3:
			if (!irqInhibit) frameInterrupt = true; // Set frame interrupt flag
			clockEnvelope(&(pulse1Settings.envelope)); // Clock pulse 1 envelope
			clockEnvelope(&(pulse2Settings.envelope)); // Clock pulse 2 envelope
			clockEnvelope(&noiseEnvelope); // Clock noise envelope
			clockTriangleLinearCounter();
			clockPulseSweep(&pulse1Settings, true); // Clock pulse 1 sweep
			clockPulseSweep(&pulse2Settings, false); // Clock pulse 2 sweep
			clockPulseLengthCounter(&pulse1Settings); // Clock pulse 1 length counter
			clockPulseLengthCounter(&pulse2Settings); // Clock pulse 2 length counter
			clockNoiseLengthCounter(); // Clock noise length counter
			if (!irqInhibit) myConsole->cpu.brk();

			break;
		default:
			break;
		}
		frameCounter++;
		frameCounter &= 3; // Wrap around after 4 steps	
	}
	// Handle pulse channels, triangle, noise, and DMC channels here
	// This is where you would implement the sound generation logic
}

void apu::writePulseReg0(pulseSettings* p, Uint8 v) {
	p->dutyCycle = (v >> 6) & 0x03; // Bits 6-7
	p->envelope.lengthCounterHalt = v & 0x20; // Bit 5
	p->envelope.constantVolume = v & 0x10; // Bit 4
	p->envelope.volume = v & 0x0F; // Bits 0-3
}

void apu::writePulseReg1(pulseSettings* p, Uint8 v) {
	p->sweepEnabled = v & 0x80; // Bit 7
	p->sweepPeriod = (v >> 4) & 0x07; // Bits 4-6
	p->sweepNegate = v & 0x08; // Bit 3
	p->sweepShift = v & 0x07; // Bits 0-2
	p->sweepReload = true;
}

void apu::writePulseReg2(pulseSettings* p, Uint8 v) {
	p->timer = (p->timer & 0xFF00) | v; // Lower byte
}

void apu::writePulseReg3(pulseSettings* p, Uint8 v) {
	p->timer = (p->timer & 0x00FF) | ((v & 0x07) << 8); // Upper byte
	p->lengthCounter = lengthCounterTable[(v >> 3) & 0x1F]; // Bits 3-7
	p->envelope.envelopeStart = true;
}

void apu::writeReg4008(Uint8 v) {
	triangleLengthCounterHalt = v & 0x80;
	triangleLinearCounterLoad = v & 0x7F;
}

void apu::writeReg400A(Uint8 v) {
	triangleTimer = (triangleTimer & 0xFF00) | v; // Lower byte
}

void apu::writeReg400B(Uint8 v) {
	triangleTimer = (triangleTimer & 0x00FF) | ((v & 0x07) << 8); // Upper byte
	triangleLengthCounter = lengthCounterTable[(v >> 3) & 0x1F]; // Bits 3-7
	triangleLinearCounterReload = true;
}



void apu::writeReg4015(Uint8 v) {
	pulse1Settings.enabled = v & 0x01; // Bit 0
	if (!pulse1Settings.enabled) pulse1Settings.lengthCounter = 0;
	pulse2Settings.enabled = v & 0x02; // Bit 1
	if (!pulse2Settings.enabled) pulse2Settings.lengthCounter = 0;
	triangleEnabled = v & 0x04; // Bit 2
	if (!triangleEnabled) triangleLengthCounter = 0;
	noiseEnabled = v & 0x08; // Bit 3
	dmcEnabled = v & 0x10; // Bit 4
}

void apu::writeReg4017(Uint8 v) {
	frameCounterMode = v & 0x80; // Bit 7
	irqInhibit = v & 0x40; // Bit 6
	frameCounter = 0; // Reset frame counter
	if (frameCounterMode) {
		runFrame();
	}
	if (irqInhibit) {
		frameInterrupt = false;
	}
}

void apu::clockEnvelope(envelopeSettings* p) {
	// Clock the pulse channel
	if (p->envelopeStart) {
		p->envelopeStart = false;
		p->decayLevelCounter = 15;
		p->dividerCounter = p->volume;
	}
	else {
		//clock divider
		if (p->dividerCounter > 0) {
			p->dividerCounter--;
		}
		else {
			p->dividerCounter = p->volume;
			//clock decay level
			if (p->decayLevelCounter > 0) {
				p->decayLevelCounter--;
			}
			else if (p->lengthCounterHalt) {
				p->decayLevelCounter = 15;
			}
		}
	}
	if (p->constantVolume) {
		p->outputVolume = p->volume;
	}
	else {
		p->outputVolume = p->decayLevelCounter;
	}
}

void apu::clockPulseSweep(pulseSettings* p, bool isPulse1) {
	//calculate target period
	Uint16 changeAmount = p->timer >> p->sweepShift;
	p->targetPeriod = p->timer;
	if (p->sweepNegate) {
		if (isPulse1) changeAmount++;
		if (p->targetPeriod < changeAmount) {
			p->targetPeriod = 0; // Prevent underflow
		}
		else {
			p->targetPeriod -= changeAmount; // Subtract the change amount
		}
	}
	else {
		p->targetPeriod += changeAmount;
	}

	if (p->sweepDivider == 0 && p->sweepEnabled && p->sweepShift) {
		if (p->targetPeriod < 0x800 && p->timer >= 8) {
			p->timer = p->targetPeriod; // Update current period
		}
	}
	if (p->sweepReload || p->sweepDivider == 0) {
		p->sweepReload = false;
		p->sweepDivider = p->sweepPeriod; // Reset sweep divider
	}
	else {
		p->sweepDivider--;
	}
}

void apu::clockPulseLengthCounter(pulseSettings* p) {
	// Clock the length counter
	if (p->enabled && !p->envelope.lengthCounterHalt) {
		if (p->lengthCounter > 0) {
			p->lengthCounter--;
		}
	}
}

void apu::clockTriangleLengthCounter() {
	if (triangleEnabled && !triangleLengthCounterHalt) {
		if (triangleLengthCounter > 0) {
			triangleLengthCounter--;
		}
	}
}

void apu::clockTriangleLinearCounter() {
	if (triangleLinearCounterReload) {
		triangleLinearCounter = triangleLinearCounterLoad;
	}
	else if (triangleLinearCounter > 0) {
		triangleLinearCounter--;
	}
	if (!triangleLengthCounterHalt) triangleLinearCounterReload = false;
}

void apu::writeReg400C(Uint8 v) {
	noiseEnvelope.lengthCounterHalt = v & 0x20; // Bit 5
	noiseEnvelope.constantVolume = v & 0x10; // Bit 4
	noiseEnvelope.volume = v & 0x0F; // Bits 0-3
}

void apu::writeReg400E(Uint8 v) {
	loopNoise = v & 0x8000; // Bit 15
	noisePeriod = noisePeriodTable[v & 0x0F]; // Bits 0-3
}

void apu::writeReg400F(Uint8 v) {
	noiseLengthCounter = lengthCounterTable[(v >> 3) & 0x1F]; // Bits 3-7
	noiseEnvelope.envelopeStart = true;
}

void apu::clockNoiseLengthCounter() {
	// Clock the length counter
	if (noiseEnabled && !noiseEnvelope.lengthCounterHalt) {
		if (noiseLengthCounter > 0) {
			noiseLengthCounter--;
		}
	}
}

