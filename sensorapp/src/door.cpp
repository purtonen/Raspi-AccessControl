#include <iostream>

#include "door.h"

using namespace std;

Door::Door() {
	this->_isOpen = true;
	this->_isControllable = false;
	this->_hasButton = false;
}

Door::Door(int gpioIn, int gpioOut, GPIOController* gc) {
	this->_isOpen = true;
	this->gpioIn = gpioIn;
	this->gpioOut = gpioOut;
	this->gc = gc;
	
	if(gpioIn != null) {
		this->_hasButton = true;
	}
	
	if(gpioOut != null) {
		this->_isControllable = true;
	}
}

bool Door::isOpen() {
	return this->_isOpen;
}

bool Door::isControllable() {
	return this->_isControllable;
}

bool Door::hasButton() {
	return this->_hasButton;
}

void Door::openDoor() {
	if (this->_isControllable) {
		this->_isOpen = true;
		this->gc->writeToGPIO(this->gpioOut, "0");
	} else {
		cout << "sensorapp: ERROR: trying to open non-controllable door" << endl;
	}
}

void Door::closeDoor() {
	if (this->_isControllable) {
		this->_isOpen = true;
		this->gc->writeToGPIO(this->gpioOut, "1");
	} else {
		cout << "sensorapp: ERROR: trying to close non-controllable door" << endl;
	}
}