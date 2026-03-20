#include "sound.h"
#include "console.h"

void SDLCALL sound::FeedAudioStream(void* userdata, SDL_AudioStream* astream, int additional_amount, int total_amount)
{
    sound* snd = static_cast<sound*>(userdata);
    snd->fillBuffer(astream, additional_amount, total_amount);
}

sound::sound() {
    pulse1Cycle = 0;
    pulse2Cycle = 0;
    triangleCycle = 0;
	noiseCycle = 0;
    noiseLFSR = 0x0001; // Initial value for noise LFSR
	dmcCycle = 0;

    for (Uint16 i = 0; i < 2048; i++) {
        float n = i;
        sqFreqChart[i] = 1789773.0 / (2.0 * (n + 1)) / 48000.0;
        triFreqChart[i] = 1789773.0 / (32.0 * (n + 1)) / 48000.0;
    }
    for (Uint8 i = 0; i < 16; i++) {
        noiseFreqChart[i] = 1789773.0 / noisePeriodTable[i] / 48000.0;
    }
}

void sound::fillBuffer(SDL_AudioStream* astream, int additional_amount, int total_amount) {
	myConsole->midi.updateReplacementSet();  /* make sure the MIDI driver is up to date with any changes to the sound channels. */

    additional_amount /= sizeof(float);  /* convert from bytes to samples */
    while (additional_amount > 0) {
        float samples[128];  /* this will feed 128 samples each iteration until we have enough. */
        float pulse1Samples[128];
        float pulse2Samples[128];
        float triangleSamples[128];
		float noiseSamples[128];
        float dmcSamples[128];

        const int total = SDL_min(additional_amount, SDL_arraysize(samples));
        
        if(myConsole->midi.channel[0].hasReplace)
            fillSilence(pulse1Samples, total);
        else 
            genPulseWave(myConsole->apu.pulse1Settings, pulse1Samples, total, &pulse1Cycle);


		if (myConsole->midi.channel[1].hasReplace)
            fillSilence(pulse2Samples, total);
		else
            genPulseWave(myConsole->apu.pulse2Settings, pulse2Samples, total, &pulse2Cycle);

        if (myConsole->midi.channel[2].hasReplace)
            fillSilence(triangleSamples, total);
        else
            genTriangleWave(triangleSamples, total);

        if (myConsole->midi.channel[3].hasReplace && myConsole->midi.channel[3].duty == ((myConsole->apu.loopNoise ? 0x10 : 0) | myConsole->apu.noisePeriod))
            fillSilence(noiseSamples, total);
        else
    		genNoiseWave(noiseSamples, total);
        genDMCWave(dmcSamples, total);

        for (int i = 0; i < total; i++) {
            samples[i] = 0.1504 * (pulse1Samples[i] + pulse2Samples[i]) + (0.1702 * triangleSamples[i]) + (0.0988 * noiseSamples[i]) + (0.0670 * 8.46 * dmcSamples[i]);
        }

        /* feed the new data to the stream. It will queue at the end, and trickle out as the hardware needs more data. */
        SDL_PutAudioStreamData(astream, samples, total * sizeof(float));
        additional_amount -= total;  /* subtract what we've just fed the stream. */
    }
}


void sound::genPulseWave(pulseSettings p, float* output, int samples, float* cycle) {
    if (p.enabled && p.lengthCounter > 0 && p.timer >= 8 && p.targetPeriod < 0x800) {
        float cyclePerSample = sqFreqChart[p.timer];
        float vol = p.envelope.outputVolume / 15.0;
        for (int i = 0; i < samples; i++) {
            (*cycle) += cyclePerSample;
            if ((*cycle) > 8.0) (*cycle) -= 8.0;
            if (pulseDuty[p.dutyCycle][(int)*cycle]) {
                output[i] = vol;
            }
            else {
                output[i] = 0;
            }
        }
    }
    else {
        for (int i = 0; i < samples; i++) {
            output[i] = 0;
        }
    }
}

void sound::genTriangleWave(float* output, int samples) {
    float cyclePerSample = triFreqChart[myConsole->apu.triangleTimer];
    for (int i = 0; i < samples; i++) {
        if (myConsole->apu.triangleEnabled && myConsole->apu.triangleLengthCounter > 0 && myConsole->apu.triangleLinearCounter > 0 && myConsole->apu.triangleTimer > 0 && cyclePerSample < 1.0) {
            triangleCycle += cyclePerSample;
        }
        if (triangleCycle > 1.0) triangleCycle -= 1.0;
        if (triangleCycle < 0.5) {
            output[i] = triangleCycle * 2;
        }
        else {
            output[i] = 1 - ((triangleCycle - 0.5) * 2);
        }
    }
}

void sound::genNoiseWave(float* output, int samples) {
    if (myConsole->apu.noiseEnabled && myConsole->apu.noiseLengthCounter) {
        float cyclePerSample = noiseFreqChart[myConsole->apu.noisePeriod];
        float vol = myConsole->apu.noiseEnvelope.outputVolume / 15.0;
        for (int i = 0; i < samples; i++) {
            noiseCycle += cyclePerSample;
            while (noiseCycle >= 1.0) {
				// Shift the LFSR and calculate the new bit
				Uint16 newBit = (noiseLFSR ^ (noiseLFSR >> (myConsole->apu.loopNoise ? 6 : 1))) & 0x01;
				noiseLFSR = (noiseLFSR >> 1) | (newBit << 14); // Shift right and insert new bit at MSB
				noiseCycle -= 1.0;
            }
            if (noiseLFSR & 0x01) {
                output[i] = vol;
            }
            else {
                output[i] = 0;
            }
        }
    }
    else {
        for (int i = 0; i < samples; i++) {
            output[i] = 0;
        }
    }
}

void sound::genDMCWave(float* output, int samples) {
    if (myConsole->apu.dmcEnabled && myConsole->apu.dmcBytesRemaining > 0) {
        float cyclePerSample = (1789773.0 / myConsole->apu.dmcRateTable[myConsole->apu.dmcRateIndex]) / 48000.0;
        for (int i = 0; i < samples; i++) {
			dmcCycle += cyclePerSample;
            while (dmcCycle >= 1.0) {
				myConsole->apu.clockDMC();
				dmcCycle -= 1.0;
            }
            output[i] = myConsole->apu.dmcOutputLevel / 127.0; 
        }
	}
    else {
        for (int i = 0; i < samples; i++) {
            output[i] = 0;
        }
    }
}

void sound::fillSilence(float* output, int samples) {
    for (int i = 0; i < samples; i++) {
        output[i] = 0;
    }
}

