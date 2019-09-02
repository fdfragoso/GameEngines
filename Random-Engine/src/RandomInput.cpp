//
// Created by Random Engine on 12/12/16.
//

#include "RandomInput.hpp"
#include "RandomEngine.hpp"
#include <vector>
#include <iostream>
using namespace std;


std::map<int, InputKey*> RandomInput::myInputList = {};

InputKey::InputKey(bool keyDown, bool keyHeldDown, bool keyUp) : keyDown(keyDown), keyHeldDown(keyHeldDown), keyUp(keyUp)
{
}

void RandomInput::updateKeyDown(int index) {
	if (!myInputList[index]->keyDown && !myInputList[index]->keyHeldDown) {
		myInputList[index]->keyDown = true;
		myInputList[index]->keyHeldDown = false;
		myInputList[index]->keyUp = false;
	}
	else {
		myInputList[index]->keyDown = false;
		myInputList[index]->keyHeldDown = true;
		myInputList[index]->keyUp = false;
	}
	
}

void RandomInput::updateKeyUp(int index) {
	myInputList[index]->keyDown = false;
	myInputList[index]->keyHeldDown = false;
	myInputList[index]->keyUp = true;
}

bool RandomInput::getKeyDown(int index) {
	if (myInputList.find(index) == myInputList.end()) {
		myInputList.emplace(index, new InputKey(false, false, false));
	}
	return myInputList[index]->keyDown;
}

bool RandomInput::getKeyUp(int index) {
	if (myInputList.find(index) == myInputList.end()) {
		myInputList.emplace(index, new InputKey(false, false, false));
	}
	return myInputList[index]->keyUp;
}

bool RandomInput::getKey(int index) {
	if (myInputList.find(index) == myInputList.end()) {
		myInputList.emplace(index, new InputKey(false, false, false));
	}
	return myInputList[index]->keyHeldDown;
}

void RandomInput::checkInput() {
	keyboardState = SDL_GetKeyboardState(NULL);
	for (auto i = myInputList.begin(); i != myInputList.end(); i++) {
		if (keyboardState[SDL_GetScancodeFromKey(i->first)]) {
			updateKeyDown(i->first);
		}
		else {
			updateKeyUp(i->first);
		}
	}
}

void RandomInput::onQuitClear() {
	for (auto i = myInputList.begin(); i != myInputList.end(); i++) {
		delete i->second;
	}
	myInputList.clear();
}


