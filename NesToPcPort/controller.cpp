#include "controller.h"
#include <SDL3/SDL.h>


controller::controller() {
	controller1.up = false;
	controller1.down = false;
	controller1.left = false;
	controller1.right = false;
	controller1.a = false;
	controller1.b = false;
	controller1.select = false;
	controller1.start = false;
	controller2.up = false;
	controller2.down = false;
	controller2.left = false;
	controller2.right = false;
	controller2.a = false;
	controller2.b = false;
	controller2.select = false;
	controller2.start = false;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++)
			inputSettings[j][i] = { 0, 0 };
	}
}

controller::~controller() {
	for (int i = 0; i < js.size(); i++) {
		SDL_CloseJoystick(js[i]);
	}
}

void controller::init() {
	int joyStickCnt;
	SDL_JoystickID* joySticks;

	joySticks = SDL_GetJoysticks(&joyStickCnt);
	for (int i = 0; i < joyStickCnt; i++) {
		SDL_Joystick* j = SDL_OpenJoystick(joySticks[i]);
		if (j) js.push_back(j);
	}
	SDL_free(joySticks);

	frameCounter = 0;
}

Uint8 controller::getController1State() {
	Uint8 state = 0;
	
	//code for auto fire
	//if (frameCounter == 255) frameCounter = 0;
	//else frameCounter++;
	//if (frameCounter & 0x01) state |= 0x01; //a button
	//if (frameCounter & 0x02) state |= 0x02; //b button

	if (controller1.a) state |= 0x01;
	if (controller1.b) state |= 0x02;
	if (controller1.select) state |= 0x04;
	if (controller1.start) state |= 0x08;
	if (controller1.up) state |= 0x10;
	if (controller1.down) state |= 0x20;
	if (controller1.left) state |= 0x40;
	if (controller1.right) state |= 0x80;
	return state;
}

Uint8 controller::getController2State() {
	Uint8 state = 0;
	if (controller2.a) state |= 0x01;
	if (controller2.b) state |= 0x02;
	if (controller2.select) state |= 0x04;
	if (controller2.start) state |= 0x08;
	if (controller2.up) state |= 0x10;
	if (controller2.down) state |= 0x20;
	if (controller2.left) state |= 0x40;
	if (controller2.right) state |= 0x80;
	return state;
}

void controller::handleEvent(SDL_Event* event) {
	inputSetting i = { 0, 0 };

	switch (event->type) {
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
		i.type = 1;
		i.v = event->key.scancode;
		break;
	case SDL_EVENT_JOYSTICK_AXIS_MOTION:
		i.type = 2;
		i.v = (event->jaxis.axis << 8) | (event->jaxis.value < 0 ? 0xFF : 0x00);
		break;
	case SDL_EVENT_JOYSTICK_HAT_MOTION:
		i.type = 3;
		i.v = (event->jhat.hat << 8) | event->jhat.value;
		break;
	case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
	case SDL_EVENT_JOYSTICK_BUTTON_UP:
		i.type = 4;
		i.v = event->jbutton.button;
		break;
	case SDL_EVENT_WINDOW_RESIZED:
		setScreenSize(event->window.data1, event->window.data2);
		break;
	case SDL_EVENT_MOUSE_MOTION:
		mouseX = (event->motion.x < 0 ? 0 : (event->motion.x > windowWidth ? windowWidth : event->motion.x));
		mouseY = (event->motion.y < 0 ? 0 : (event->motion.y > windowHeight ? windowHeight : event->motion.y));
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (event->button.button == 1) {
			//left button
			controller1.b = event->button.down;
		} 
		else {
			controller1.a = event->button.down;
		}
		break;
	}
	if (i.type != 0) {
		for (int p = 0; p < 4; p++) {
			for (int c = 0; c < 8; c++) {
				if (inputSettings[p][c].type == i.type) {
					switch (i.type) {
					case 1:
					case 4:
						//keyboard and button need exact match
						if (inputSettings[p][c].v == i.v) {
							bool pressed = ((event->type == SDL_EVENT_KEY_DOWN) || (event->type == SDL_EVENT_JOYSTICK_BUTTON_DOWN));
							if (p == 0 || p == 2) {
								switch (c) {
								case 0: controller1.up = pressed; break;
								case 1: controller1.down = pressed; break;
								case 2: controller1.left = pressed; break;
								case 3: controller1.right = pressed; break;
								case 4: controller1.a = pressed; break;
								case 5: controller1.b = pressed; break;
								case 6: controller1.select = pressed; break;
								case 7: controller1.start = pressed; break;
								}
							}
							else {
								switch (c) {
								case 0: controller2.up = pressed; break;
								case 1: controller2.down = pressed; break;
								case 2: controller2.left = pressed; break;
								case 3: controller2.right = pressed; break;
								case 4: controller2.a = pressed; break;
								case 5: controller2.b = pressed; break;
								case 6: controller2.select = pressed; break;
								case 7: controller2.start = pressed; break;
								}
							}
						}
						break;
					case 2:
					case 3:
						//clear other using the same axis / hat
						if ((inputSettings[p][c].v & 0xFF00) == (i.v & 0xFF00)) {
							bool pressed = (inputSettings[p][c].v == i.v);
							if (p == 0 || p == 2) {
								switch (c) {
								case 0: controller1.up = pressed; break;
								case 1: controller1.down = pressed; break;
								case 2: controller1.left = pressed; break;
								case 3: controller1.right = pressed; break;
								case 4: controller1.a = pressed; break;
								case 5: controller1.b = pressed; break;
								case 6: controller1.select = pressed; break;
								case 7: controller1.start = pressed; break;
								}
							}
							else {
								switch (c) {
								case 0: controller2.up = pressed; break;
								case 1: controller2.down = pressed; break;
								case 2: controller2.left = pressed; break;
								case 3: controller2.right = pressed; break;
								case 4: controller2.a = pressed; break;
								case 5: controller2.b = pressed; break;
								case 6: controller2.select = pressed; break;
								case 7: controller2.start = pressed; break;
								}
							}
						}
						break;
					}
				}
			}
		}
	}
}

void controller::setConfig(string h, string t) {
	inputSetting i = { 0, 0 };
	size_t idx = t.find("_");
	if (idx == string::npos) return;

	string value1 = t.substr(0, idx);
	string value2 = t.substr(idx + 1);
	i.type = atoi(value1.c_str());
	i.v = atoi(value2.c_str());

	if (h == "P1_UP") {
		inputSettings[0][0] = i;
	}
	else if (h == "P1_DOWN") {
		inputSettings[0][1] = i;
	}
	else if (h == "P1_LEFT") {
		inputSettings[0][2] = i;
	}
	else if (h == "P1_RIGHT") {
		inputSettings[0][3] = i;
	}
	else if (h == "P1_A") {
		inputSettings[0][4] = i;
	}
	else if (h == "P1_B") {
		inputSettings[0][5] = i;
	}
	else if (h == "P1_SELECT") {
		inputSettings[0][6] = i;
	}
	else if (h == "P1_START") {
		inputSettings[0][7] = i;
	}
	else if (h == "P2_UP") {
		inputSettings[1][0] = i;
	}
	else if (h == "P2_DOWN") {
		inputSettings[1][1] = i;
	}
	else if (h == "P2_LEFT") {
		inputSettings[1][2] = i;
	}
	else if (h == "P2_RIGHT") {
		inputSettings[1][3] = i;
	}
	else if (h == "P2_A") {
		inputSettings[1][4] = i;
	}
	else if (h == "P2_B") {
		inputSettings[1][5] = i;
	}
	else if (h == "P2_SELECT") {
		inputSettings[1][6] = i;
	}
	else if (h == "P2_START") {
		inputSettings[1][7] = i;
	}
	else if (h == "P1_UP2") {
		inputSettings[2][0] = i;
	}
	else if (h == "P1_DOWN2") {
		inputSettings[2][1] = i;
	}
	else if (h == "P1_LEFT2") {
		inputSettings[2][2] = i;
	}
	else if (h == "P1_RIGHT2") {
		inputSettings[2][3] = i;
	}
	else if (h == "P1_A2") {
		inputSettings[2][4] = i;
	}
	else if (h == "P1_B2") {
		inputSettings[2][5] = i;
	}
	else if (h == "P1_SELECT2") {
		inputSettings[2][6] = i;
	}
	else if (h == "P1_START2") {
		inputSettings[2][7] = i;
	}
	else if (h == "P2_UP2") {
		inputSettings[3][0] = i;
	}
	else if (h == "P2_DOWN2") {
		inputSettings[3][1] = i;
	}
	else if (h == "P2_LEFT2") {
		inputSettings[3][2] = i;
	}
	else if (h == "P2_RIGHT2") {
		inputSettings[3][3] = i;
	}
	else if (h == "P2_A2") {
		inputSettings[3][4] = i;
	}
	else if (h == "P2_B2") {
		inputSettings[3][5] = i;
	}
	else if (h == "P2_SELECT2") {
		inputSettings[3][6] = i;
	}
	else if (h == "P2_START2") {
		inputSettings[3][7] = i;
	}
}

void controller::setScreenSize(Sint32 w, Sint32 h) {
	windowWidth = w;
	windowHeight = h;
	if (windowWidth >= windowHeight * 16 / 15) {
		screenIsWide = true;
		screenXOffset = (windowWidth - windowHeight * 16 / 15) / 2;
		screenYOffset = 0;
	}
	else {
		screenIsWide = false;
		screenXOffset = 0;
		screenYOffset = (windowHeight - windowWidth * 15 / 16) / 2;
	}
}

Uint8 controller::getMouseX() {
	if (screenIsWide) {
		if (mouseX >= screenXOffset) {
			if (mouseX >= screenXOffset + windowHeight * 16 / 15)
				return 255;
			else
				return (Uint8)((mouseX - screenXOffset) * 256 / windowHeight * 15 / 16);
		}
		else
			return 0;
	}
	else {
		return (Uint8)(mouseX * 256 / windowWidth);
	}
}

Uint8 controller::getMouseY() {
	if (screenIsWide) {
		return (Uint8)(mouseY * 240 / windowHeight);
	}
	else {
		if(mouseY >= screenYOffset) {
			if (mouseY >= screenYOffset + windowWidth * 15 / 16)
				return 239;
			else
				return (Uint8)((mouseY - screenYOffset) * 240 / windowWidth * 16 / 15);
		}
		else
			return 0;
	}
}