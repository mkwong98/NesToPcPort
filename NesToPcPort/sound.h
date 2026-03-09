#pragma once
#include <SDL3/SDL.h>
#include "midi_driver.h"

struct pulseSettings;
class console;

class sound
{
public:
    static void SDLCALL FeedAudioStream(void* userdata, SDL_AudioStream* astream, int additional_amount, int total_amount);
    const Uint8 pulseDuty[4][8] = { { 0, 1, 0, 0, 0, 0, 0, 0 },
                                   { 0, 1, 1, 0, 0, 0, 0, 0 },
                                   { 0, 1, 1, 1, 1, 0, 0, 0 },
                                   { 1, 0, 0, 1, 1, 1, 1, 1 } };
    const float noisePeriodTable[16] = {
        4, 8, 16, 32, 64, 96, 128, 160,
        202, 254, 380, 508, 762, 1014, 2038, 4068
    };
    float sqFreqChart[2048];
    float triFreqChart[2048];
    float noiseFreqChart[16];

    console* myConsole;

    sound();
    float pulse1Cycle;
    float pulse2Cycle;
    float triangleCycle;
	float noiseCycle;
	float dmcCycle;
    Uint16 noiseLFSR;
    void fillBuffer(SDL_AudioStream* astream, int additional_amount, int total_amount);
    void genPulseWave(pulseSettings p, float* output, int samples, float* cycle);
    void genTriangleWave(float* output, int samples);
    void genNoiseWave(float* output, int samples);
    void genDMCWave(float* output, int samples);
    void fillSilence(float* output, int samples);

};
