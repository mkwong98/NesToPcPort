#include "midi_driver.h"
#include "console.h"

midi_driver::midi_driver() {
	try {
		midiout = new RtMidiOut(RtMidi::Api::UNSPECIFIED);
		midiout->openPort(0);

		//fill freq chart
		for (Uint8 i = 0; i < 128; i++) {
			float n = i;
			//formula is 440 * pow(2, (n - 69.0) / 12.0), we use 0.5 to get max and min
			freqChart[i][0] = 440 * pow(2, (n - 69.5) / 12.0);
			freqChart[i][1] = 440 * pow(2, (n - 68.5) / 12.0);
		}
		for (Uint16 i = 0; i < 2048; i++) {
			float n = i;
			sqFreqChart[i] = 1789773.0 / (16.0 * (n + 1));
			triFreqChart[i] = 1789773.0 / (32.0 * (n + 1));
		}

		for (Uint8 i = 0; i < CHANNEL_CNT; i++) {
			channel[i].pitch = 0;
			channel[i].sweepPitch = 0;
			channel[i].playing = false;
			channel[i].volume = 0;
			channel[i].duty = 0xFF;
		}
		channelToReplacement[0] = 0;
		channelToReplacement[1] = 4;
		channelToReplacement[2] = 8;
		channelToReplacement[3] = 9;
		currentSet = UINT16_MAX;

		//init midi
		if (midiout->getPortCount()) {
			for (Uint8 i = 0; i < CHANNEL_CNT - 1; i++) {
				//panoramic is fixed to centre
				sendMidiMessage(CONTROLLER_CHANGE | i, CONTROLLER_PANORAMIC, 0x40, 2);
			}
			sendMidiMessage(CONTROLLER_CHANGE | 9, CONTROLLER_PANORAMIC, 0x40, 2);
		}
		else {
			delete midiout;
			midiout = 0;
		}
		blocking = false;

		//read replacement sets
		readReplacementSets();
	}
	catch (RtMidiError& error) {
		midiout = 0;
	}
}

midi_driver::~midi_driver()
{
	if (midiout) {
		for (Uint8 i = 0; i < CHANNEL_CNT; i++) {
			sendNoteOff(i);
		}
		midiout->closePort();
		delete midiout;
	}
}



/****** Send message to midi device ******/
void midi_driver::sendMidiMessage(Uint8 status, Uint8 data1, Uint8 data2, Uint8 len) {
	std::vector<unsigned char> message;
	message.push_back(status);
	if (len >= 1) message.push_back(data1);
	if (len >= 2) message.push_back(data2);
	midiout->sendMessage(&message);
}

/****** Stop a playing note on specific channel ******/
void midi_driver::sendNoteOff(Uint8 c) {
	if (channel[c].playing) {
		sendMidiMessage(NOTE_OFF | (c == 3 ? 9 : c) , channel[c].pitch, 0, 2);
		if (channelUseHarmonic(c)) {
			if (channel[c].pitch <= 115)
				sendMidiMessage(NOTE_OFF | (c == 3 ? 9 : c), channel[c].pitch + 12, 0, 2);
			if (channel[c].pitch >= 12)
				sendMidiMessage(NOTE_OFF | (c == 3 ? 9 : c), channel[c].pitch - 12, 0, 2);
		}
		channel[c].playing = false;
	}
}

/****** Start playing a note on specific channel ******/
void midi_driver::sendNoteOn(Uint8 c, Uint8 v, Uint8 p) {
	bool useH = channelUseHarmonic(c);
	if (useH) {
		sendMidiMessage(CONTROLLER_CHANGE | (c == 3 ? 9 : c), CONTROLLER_VOLUME, v / 3, 2);
	}
	else {
		sendMidiMessage(CONTROLLER_CHANGE | (c == 3 ? 9 : c), CONTROLLER_VOLUME, v, 2);
	}
	if (c == 3) {
		sendMidiMessage(NOTE_ON | 9, replacementSets[currentSet].replacement[channelToReplacement[c] + channel[3].duty].instID, 0x60, 2);
	}
	else {
		sendMidiMessage(NOTE_ON | c, p, 0x60, 2);
		if (useH) {
			if (p <= 115)
				sendMidiMessage(NOTE_ON | c, p + 12, 0x60, 2);
			if (p >= 12)
				sendMidiMessage(NOTE_ON | c, p - 12, 0x60, 2);
		}
	}

	channel[c].pitch = p;
	channel[c].sweepPitch = p;
	channel[c].volume = v;
	channel[c].playing = true;
}

/****** set the instrument for a channel ******/
void midi_driver::setInstrument(Uint8 c, Uint8 duty) {
	sendMidiMessage(PROGRAM_CHANGE | c, replacementSets[currentSet].replacement[channelToReplacement[c] + duty].instID, 0, 1);
	channel[c].duty = duty;
	channel[c].hasReplace = true;
}

/****** set instrument on duty change******/
void midi_driver::dutyChange(Uint8 c, Uint8 duty) {
	if (channel[c].duty != duty) stopSound(c);
	if (replacementSets[currentSet].replacement[channelToReplacement[c] + duty].hasReplacement) {
		setInstrument(c, duty);
	}
	else {
		channel[c].duty = duty;
		channel[c].hasReplace = false;
	}
}

/****** play sound ******/
void midi_driver::playSound(Uint8 c, Uint8 vol, double freq) {
	if (blocking || !channel[c].hasReplace) return;

	//find pitch from frequency
	Uint8 p = frequencyToPitch(freq);

	//stop playing with volume is 0
	if (vol == 0) {
		stopSound(c);

		//keep the pitch data for later, in case of envlope up
		channel[c].pitch = p;
		channel[c].sweepPitch = p;
		return;
	}

	Uint16 v = volumeConvert(vol) * replacementSets[currentSet].replacement[channelToReplacement[c] + channel[c].duty].volume / 100;
	if (channel[c].sweepPitch != channel[c].pitch) {
		clearSweep(c);
	}

	blocking = true;
	bool needWork;
	needWork = true;
	if (channel[c].playing) {
		if (channel[c].pitch == p && channel[c].volume == v) {
			needWork = false;
		}
		else {
			sendNoteOff(c);
		}
	}
	if (needWork) {
		sendNoteOn(c, v, p);
	}
	blocking = false;
}

/****** stop sound ******/
void midi_driver::stopSound(Uint8 c) {
	if (channel[c].sweepPitch != channel[c].pitch) {
		clearSweep(c);
	}
	sendNoteOff(c);
}

/****** pause play sound ******/
void midi_driver::pause() {
	//send note off without changing the playing flag
	for (Uint8 i = 0; i < CHANNEL_CNT; i++) {
		if (channel[i].playing) {
			sendMidiMessage(NOTE_OFF | i, channel[i].pitch, 0, 2);
			if (channelUseHarmonic(i)) {
				if (channel[i].pitch <= 115)
					sendMidiMessage(NOTE_OFF | i, channel[i].pitch + 12, 0, 2);
				if (channel[i].pitch >= 12)
					sendMidiMessage(NOTE_OFF | i, channel[i].pitch - 12, 0, 2);
			}
		}
	}
}

/****** unpause play sound ******/
void midi_driver::unpause() {
	//send note on base on the playing flag
	for (Uint8 i = 0; i < CHANNEL_CNT; i++) {
		if (channel[i].playing) {
			sendMidiMessage(NOTE_ON | i, channel[i].pitch, 0x40, 2);
			if (channelUseHarmonic(i)) {
				if (channel[i].pitch <= 115)
					sendMidiMessage(NOTE_ON | i, channel[i].pitch + 12, 0x40, 2);
				if (channel[i].pitch >= 12)
					sendMidiMessage(NOTE_ON | i, channel[i].pitch - 12, 0x40, 2);
			}
		}
	}
}


/****** handle sweep up or down ******/
void midi_driver::sqSweepTo(Uint8 c, Uint8 vol, double freq) {
	if (blocking) return;
	Uint8 p = frequencyToPitch(freq);
	if (channel[c].playing && channel[c].sweepPitch != p) {
		Uint8 dif;
		if (channel[c].playing) {
			if (p > channel[c].sweepPitch)
				dif = p - channel[c].sweepPitch;
			else
				dif = channel[c].sweepPitch - p;
		}
		//play sound if the difference is over 2
		if (dif <= 2) {
			sweep(c, p);
		}
		else {
			playSound(c, vol, freq);
		}
	}
}

/******** reverse pitch bend ********/
void midi_driver::clearSweep(Uint8 c) {
	sweep(c, channel[c].pitch);
}

/******* send pitch bend until p ******/
void midi_driver::sweep(Uint8 c, Uint8 p) {
	blocking = true;
	Uint8 dif;
	for (Uint8 i = 0; i <= 2; i += 2) {
		if (channel[i].playing) {
			if (p > channel[i].sweepPitch) {
				dif = p - channel[i].sweepPitch;
				if (dif > 1) {
					sendMidiMessage(PITCH_BEND | i, 0, 0x40, 2);
					channel[i].sweepPitch += 2;
				}
				else if (dif == 1) {
					sendMidiMessage(PITCH_BEND | i, 0, 0x30, 2);
					channel[i].sweepPitch++;
				}
			}
			else if (p < channel[i].sweepPitch) {
				dif = channel[i].sweepPitch - p;
				if (dif > 1) {
					sendMidiMessage(PITCH_BEND | i, 0, 0x00, 2);
					channel[i].sweepPitch -= 2;
				}
				else {
					sendMidiMessage(PITCH_BEND | i, 0, 0x10, 2);
					channel[i].sweepPitch--;
				}
			}
		}
	}
	blocking = false;
}

/****** convert frequency to pitch ******/
Uint8 midi_driver::frequencyToPitch(double freq) {
	//find pitch from frequency
	if (freq < freqChart[0][0]) return 0;
	else if (freq > freqChart[127][1]) return 127;
	else {
		Uint8 p;
		bool needWork = true;
		Uint8 rangeMin = 0;
		Uint8 rangeMax = 127;
		p = 63;
		while (needWork) {
			if (freq < freqChart[p][0]) rangeMax = p - 1;
			else if (freq > freqChart[p][1]) rangeMin = p + 1;
			else needWork = false;

			if (needWork) p = (rangeMin + rangeMax) / 2;
		}
		return p;
	}
}

/****** set volume ******/
void midi_driver::changeVolume(Uint8 c, Uint8 vol) {
	if (vol == 0) {
		stopSound(c);
		return;
	}
	Uint16 v = volumeConvert(vol) * replacementSets[currentSet].replacement[channelToReplacement[c] + channel[c].duty].volume / 100;
	if (channel[c].playing) {
		if (channelUseHarmonic(c)) {
			sendMidiMessage(CONTROLLER_CHANGE | c, CONTROLLER_VOLUME, v / 3, 2);
		}
		else {
			sendMidiMessage(CONTROLLER_CHANGE | c, CONTROLLER_VOLUME, v, 2);
		}
		channel[c].volume = v;
	}
}


/****** convert 4 bit vol to 7 bit vol ******/
Uint8 midi_driver::volumeConvert(Uint8 vol) {
	//get correct volume from 0x00-0x0F to 0x00-0x7F
	Uint16 v = (vol << 3) | (vol >> 1);
	return v;
}

/****** query whether the channel has replacement ******/
bool midi_driver::checkHasReplace(Uint8 c) {
	return channel[c].hasReplace;
}


/****** check replacement used uses harmonic ******/
bool midi_driver::channelUseHarmonic(Uint8 c) {
	return replacementSets[currentSet].replacement[channelToReplacement[c] + channel[c].duty].useHarmonic;
}

Uint16 midi_driver::addReplacementSet() {
	midi_replacement_set newSet;
	newSet.checks = vector<memoryCheck>();
	for (int i = 0; i < 41; i++) {
		newSet.replacement[i].instID = 0;
		newSet.replacement[i].useHarmonic = false;
		newSet.replacement[i].volume = 0;
		newSet.replacement[i].hasReplacement = false;
	}
	replacementSets.push_back(newSet);
	return replacementSets.size() - 1;
}

void midi_driver::addMemoryCheck(Uint16 setID, memoryCheck c) {
	if (setID < replacementSets.size()) {
		replacementSets[setID].checks.push_back(c);
	}
}

void midi_driver::addReplacement(Uint16 setID, Uint8 c, Uint8 duty, Uint8 insID, bool useHarmonic, Uint8 vol, Sint8 pitchShift) {
	if (setID < replacementSets.size() && c < CHANNEL_CNT) {
		replacementSets[setID].replacement[channelToReplacement[c] + duty].instID = insID;
		replacementSets[setID].replacement[channelToReplacement[c] + duty].useHarmonic = useHarmonic;
		replacementSets[setID].replacement[channelToReplacement[c] + duty].volume = vol;
		replacementSets[setID].replacement[channelToReplacement[c] + duty].pitchShift = pitchShift;
		replacementSets[setID].replacement[channelToReplacement[c] + duty].hasReplacement = true;
	}
}

void midi_driver::updateReplacementSet() {
	midi_channel tempChannel[CHANNEL_CNT];
	for (Uint8 i = 0; i < CHANNEL_CNT; i++) tempChannel[i].hasReplace = false;

	bool hasValidSet = false;
	for (Uint16 i = 0; i < replacementSets.size(); i++) {
		//check if all memory check passed
		bool valid = true;
		for (Uint16 j = 0; j < replacementSets[i].checks.size(); j++) {
			if (!myConsole->rom.mapper->checkMemory(&replacementSets[i].checks[j])) {
				valid = false;
				break;
			}
		}
		if (valid) {
			hasValidSet = true;
			if (currentSet != i) {
				//stop all channels
				for (Uint8 j = 0; j < CHANNEL_CNT; j++) {
					if (channel[j].playing) {
						sendNoteOff(j);
						channel[j].playing = false;
					}
					channel[j].hasReplace = false;
					channel[j].duty = 0xFF;
				}
				currentSet = i;
			}

			//check for changes
			pulseSettings p = myConsole->apu.pulse1Settings;
			midi_replacement r = replacementSets[currentSet].replacement[channelToReplacement[0] + p.dutyCycle];
			if (p.enabled && p.lengthCounter > 0 && p.timer >= 8 && p.targetPeriod < 0x800) {
				tempChannel[0].volume = volumeConvert(p.envelope.outputVolume) * r.volume / 100;
			}
			else {
				tempChannel[0].volume = 0;
			}
			tempChannel[0].pitch = min(max(frequencyToPitch(sqFreqChart[p.timer]) + r.pitchShift, 0), 127);
			tempChannel[0].duty = p.dutyCycle;
			tempChannel[0].hasReplace = r.hasReplacement;

			//changes that require stop
			if (channel[0].hasReplace && channel[0].playing) {
				if (tempChannel[0].hasReplace == false || tempChannel[0].duty != channel[0].duty || tempChannel[0].volume == 0) {
					stopSound(0);
				}
			}
			channel[0].hasReplace = tempChannel[0].hasReplace;
			if (tempChannel[0].hasReplace) {
				//changes that require change instrument
				if (tempChannel[0].duty != channel[0].duty) {
					setInstrument(0, tempChannel[0].duty);
					channel[0].duty = tempChannel[0].duty;
				}
				if (tempChannel[0].volume > 0) {
					if (!channel[0].playing) {
						playSound(0, p.envelope.outputVolume, sqFreqChart[p.timer]);
					}
					if (tempChannel[0].pitch != channel[0].pitch) {
						sqSweepTo(0, p.envelope.outputVolume, sqFreqChart[p.timer]);
					}
					if (tempChannel[0].volume != channel[0].volume) {
						changeVolume(0, p.envelope.outputVolume);
					}
				}
			}

			p = myConsole->apu.pulse2Settings;
			r = replacementSets[currentSet].replacement[channelToReplacement[1] + p.dutyCycle];
			if (p.enabled && p.lengthCounter > 0 && p.timer >= 8 && p.targetPeriod < 0x800) {
				tempChannel[1].volume = volumeConvert(p.envelope.outputVolume) * r.volume / 100;
			}
			else {
				tempChannel[1].volume = 0;
			}
			tempChannel[1].pitch = min(max(frequencyToPitch(sqFreqChart[p.timer]) + r.pitchShift, 0), 127);
			tempChannel[1].duty = p.dutyCycle;
			tempChannel[1].hasReplace = r.hasReplacement;

			//changes that require stop
			if (channel[1].hasReplace && channel[1].playing) {
				if (tempChannel[1].hasReplace == false || tempChannel[1].duty != channel[1].duty || tempChannel[1].volume == 0) {
					stopSound(1);
				}
			}
			channel[1].hasReplace = tempChannel[1].hasReplace;
			if (tempChannel[1].hasReplace) {
				//changes that require change instrument
				if (tempChannel[1].duty != channel[1].duty) {
					setInstrument(1, tempChannel[1].duty);
					channel[1].duty = tempChannel[1].duty;
				}
				if (!channel[1].playing) {
					playSound(1, p.envelope.outputVolume, sqFreqChart[p.timer]);
				}
				if (tempChannel[1].pitch != channel[1].pitch) {
					sqSweepTo(1, p.envelope.outputVolume, sqFreqChart[p.timer]);
				}
				if (tempChannel[1].volume != channel[1].volume) {
					changeVolume(1, p.envelope.outputVolume);
				}
			}

			r = replacementSets[currentSet].replacement[channelToReplacement[2]];
			if (myConsole->apu.triangleEnabled && myConsole->apu.triangleLengthCounter > 0 && myConsole->apu.triangleLinearCounter > 0) {
				tempChannel[2].volume = volumeConvert(0x0F) * r.volume / 100;
			}
			else {
				tempChannel[2].volume = 0x0;
			}
			tempChannel[2].pitch = min(max(frequencyToPitch(triFreqChart[myConsole->apu.triangleTimer]) + r.pitchShift, 0), 127);
			tempChannel[2].hasReplace = r.hasReplacement;
			tempChannel[2].duty = 0;

			//changes that require stop
			if (channel[2].hasReplace && channel[2].playing) {
				if (tempChannel[2].hasReplace == false || tempChannel[2].duty != channel[2].duty || tempChannel[2].volume == 0) {
					stopSound(2);
				}
			}
			channel[2].hasReplace = tempChannel[2].hasReplace;
			if (tempChannel[2].hasReplace) {
				//changes that require change instrument
				if (tempChannel[2].duty != channel[2].duty) {
					setInstrument(2, tempChannel[2].duty);
					channel[2].duty = tempChannel[2].duty;
				}
				if (tempChannel[2].volume > 0) {
					if (!channel[2].playing) {
						playSound(2, 0x0F, triFreqChart[myConsole->apu.triangleTimer]);
					}
					if (tempChannel[2].pitch != channel[2].pitch) {
						sqSweepTo(2, 0x0F, triFreqChart[myConsole->apu.triangleTimer]);
					}
					if (tempChannel[2].volume != channel[2].volume) {
						changeVolume(2, 0x0F);
					}
				}
			}

			Uint8 nDuty = (myConsole->apu.loopNoise ? 0x10 : 0x00) + myConsole->apu.noisePeriod;
			r = replacementSets[currentSet].replacement[channelToReplacement[3] + nDuty];
			
			if (myConsole->apu.noiseEnabled && myConsole->apu.noiseLengthCounter) {
				tempChannel[3].volume = volumeConvert(myConsole->apu.noiseEnvelope.outputVolume) * r.volume / 100;
			}
			else {
				tempChannel[3].volume = 0x0;
			}
			tempChannel[3].pitch = 0;
			tempChannel[3].hasReplace = r.hasReplacement;
			tempChannel[3].duty = nDuty;
			
			//changes that require stop
			if (channel[3].hasReplace && channel[3].playing) {
				if (tempChannel[3].hasReplace == false || tempChannel[3].duty != channel[3].duty || tempChannel[3].volume == 0) {
					stopSound(3);
				}
			}
			channel[3].hasReplace = tempChannel[3].hasReplace;
			if (tempChannel[3].hasReplace) {
				//changes that require change instrument
				if (tempChannel[3].duty != channel[3].duty) {
					channel[3].duty = tempChannel[3].duty;
				}
				if (tempChannel[3].volume > 0) {
					if (!channel[3].playing) {
						playSound(3, myConsole->apu.noiseEnvelope.outputVolume, 0);
					}
					if (tempChannel[3].volume != channel[3].volume) {
						changeVolume(3, myConsole->apu.noiseEnvelope.outputVolume);
					}
				}
			}
			break;
		}
	}
	if(hasValidSet == false && currentSet != UINT16_MAX) {
		//stop all channels
		for (Uint8 j = 0; j < CHANNEL_CNT; j++) {
			if (channel[j].playing) {
				sendNoteOff(j);
				channel[j].playing = false;
			}
			channel[j].hasReplace = false;
			channel[j].duty = 0xFF;
		}
		currentSet = UINT16_MAX;
	}
}

void midi_driver::readReplacementSets() {
	char* configData;
	size_t dataSize;
	configData = (char*)SDL_LoadFile("midi.txt", &dataSize);
	if (configData == NULL) {
		return;
	}
	string tmpStr = configData;
	tmpStr.erase(std::remove(tmpStr.begin(), tmpStr.end(), '\r'), tmpStr.end());
	stringstream s(tmpStr);
	string configLine;
	Uint16 setID = UINT16_MAX;
	while (getline(s, configLine)) {
		if (configLine == "SET") {
			setID = addReplacementSet();
		}
		else if (setID != UINT16_MAX) {
			size_t findIdx = configLine.find(":");
			if (findIdx > 0) {
				string lineHead = configLine.substr(0, findIdx);
				string lineTail = configLine.substr(findIdx + 1);

				if (lineHead == "MEM") {
					memoryCheck c;
					size_t findIdx2 = lineTail.find(",");
					c.address = stoi(lineTail.substr(0, findIdx2), nullptr, 16);
					lineTail = lineTail.substr(findIdx2 + 1);
					findIdx2 = lineTail.find(",");
					c.mask = stoi(lineTail.substr(0, findIdx2), nullptr, 16);
					lineTail = lineTail.substr(findIdx2 + 1);					
					findIdx2 = lineTail.find(",");
					string typeStr = lineTail.substr(0, findIdx2);
					if (typeStr == "EQ") c.opType = memoryCheck::EQ;
					else if (typeStr == "NE") c.opType = memoryCheck::NE;
					else if (typeStr == "GT") c.opType = memoryCheck::GT;
					else if (typeStr == "LS") c.opType = memoryCheck::LS;
					else if (typeStr == "GE") c.opType = memoryCheck::GE;
					else if (typeStr == "LE") c.opType = memoryCheck::LE;
					else c.opType = memoryCheck::EQ;
					lineTail = lineTail.substr(findIdx2 + 1);
					findIdx2 = lineTail.find(",");
					c.valueAsAddress = (lineTail.substr(0, findIdx2) == "A");
					lineTail = lineTail.substr(findIdx2 + 1);
					c.value = stoi(lineTail, nullptr, 16);
					addMemoryCheck(setID, c);
				}
				else if (lineHead == "MID") {
					size_t findIdx2 = lineTail.find(",");
					Uint8 c = stoi(lineTail.substr(0, findIdx2));
					lineTail = lineTail.substr(findIdx2 + 1);
					findIdx2 = lineTail.find(",");
					Uint8 duty = stoi(lineTail.substr(0, findIdx2));
					lineTail = lineTail.substr(findIdx2 + 1);
					findIdx2 = lineTail.find(",");
					Uint8 insID = stoi(lineTail.substr(0, findIdx2));
					lineTail = lineTail.substr(findIdx2 + 1);
					findIdx2 = lineTail.find(",");
					bool useHarmonic = (lineTail.substr(0, findIdx2) == "Y");
					lineTail = lineTail.substr(findIdx2 + 1);
					findIdx2 = lineTail.find(",");
					Sint8 pitchShift = stoi(lineTail.substr(0, findIdx2));
					lineTail = lineTail.substr(findIdx2 + 1);
					Uint8 vol = stoi(lineTail);
					addReplacement(setID, c, duty, insID, useHarmonic, vol, pitchShift);
				}
			}
		}
	}
	SDL_free(configData);
}


