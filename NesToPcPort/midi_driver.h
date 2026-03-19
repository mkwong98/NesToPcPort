#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "rtmidi/RtMidi.h"
#include "mapper.h"

#include <fstream>
#include <sstream>


/*
0 = Acoustic Grand Piano
8 = Celesta
16 = Drawbar Organ
24 = Acoustic Guitar (nylon)
32 = Acoustic Bass
40 = Violin
56 = Trumpet
64 = Soprano Sax
72 = Piccolo
*/

const Uint8 CHANNEL_CNT = 4;
const Uint8 CHANNEL_SQ1 = 0;
const Uint8 CHANNEL_SQ2 = 1;
const Uint8 CHANNEL_TRIANGLE = 2;
const Uint8 CHANNEL_NOISE = 3;


class console;

struct midi_message {
	Uint8 status;
	Uint8 data[2];
	Uint8 dataLen;
};

struct midi_replacement {
	Uint8 instID;
	bool useHarmonic;
	Uint8 volume;
	Sint8 pitchShift; // in semitones
	bool hasReplacement;
};

struct midi_channel {
	Uint8 pitch;
	Uint8 sweepPitch;
	Uint16 volume;
	Uint8 duty;
	bool playing;
	bool hasReplace;
};

struct midi_replacement_set {
	vector<memoryCheck> checks;
	midi_replacement replacement[41];
};

struct midi_effect {
	vector<memoryCheck> checks;
	Uint8 channel;
};

class midi_driver
{
public:
	console* myConsole;

	midi_driver();
	~midi_driver();

	midi_channel channel[CHANNEL_CNT];

	void dutyChange(Uint8 c, Uint8 duty);
	void playSound(Uint8 c, Uint8 vol, double freq, Sint8 shift);
	void stopSound(Uint8 c);
	void pause();
	void unpause();
	void sqSweepTo(Uint8 c, Uint8 vol, double freq, Sint8 shift);
	void changeVolume(Uint8 c, Uint8 vol);
	Uint16 addReplacementSet();
	Uint16 addEffect(Uint8 c);
	void addMemoryCheck(Uint16 setID, memoryCheck c);
	void addReplacement(Uint16 setID, Uint8 c, Uint8 duty, Uint8 insID, bool useHarmonic, Uint8 vol, Sint8 pitchShift);
	bool checkHasReplace(Uint8 c);
	void updateReplacementSet();

private:
	const Uint8 NOTE_ON = 0x90;
	const Uint8 NOTE_OFF = 0x80;
	const Uint8 CONTROLLER_CHANGE = 0xB0;
	const Uint8 PROGRAM_CHANGE = 0xC0;
	const Uint8 PITCH_BEND = 0xE0;

	const Uint8 CONTROLLER_VOLUME = 7;
	const Uint8 CONTROLLER_PANORAMIC = 10;

	vector<midi_replacement_set> replacementSets;
	vector<midi_effect> effects;
	vector<Uint8> c1Duty;
	vector<Uint8> c2Duty;
	vector<Uint8> cNDuty;

	float freqChart[128][2];
	float sqFreqChart[2048];
	float triFreqChart[2048];

	Uint8 channelToReplacement[CHANNEL_CNT];
	Uint16 currentSet;
	bool blocking;

	RtMidiOut* midiout;
	void sendMidiMessage(Uint8 status, Uint8 data1, Uint8 data2, Uint8 len);
	void sendNoteOff(Uint8 c);
	void sendNoteOn(Uint8 c, Uint8 v, Uint8 p);
	void setInstrument(Uint8 c, Uint8 duty);
	Uint8 frequencyToPitch(double freq);
	Uint8 volumeConvert(Uint8 vol);
	bool channelUseHarmonic(Uint8 c);
	void clearSweep(Uint8 c);
	void sweep(Uint8 c, Uint8 p);
	void readReplacementSets();
};

