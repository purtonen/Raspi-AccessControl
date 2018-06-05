#include <iostream>
#include <thread>
#include <vector>

#include "door.h"

using namespace std;

Door::Door() {
	this->_isControllable = false;
	this->_hasButton = false;
}

Door::Door(int gpioIn, int gpioOut, GPIOController* gc, DoorController* dc) {
	this->gpioIn = gpioIn;
	this->gpioOut = gpioOut;
	this->gc = gc;
	this->dc = dc;
	this->reader = reader;
	this->acceptedCards = acceptedCards;
	
	if(gpioIn != NULL) {
		this->_hasButton = true;
	}
	
	if(gpioOut != NULL) {
		this->_isControllable = true;
	}
}

void Door::addCard(Card card){
	
}

void Door::setReader(Reader* reader){
	this->reader = reader;
	reader->setDoor(this);
}

void Door::cardReadEvent(string card){
	cout << card << endl;
}

bool Door::stateChanged(){
	bool changed = this->_isOpen == this->previousState;
	if(changed) {
		this->previousState = this->_isOpen;
	}
	return changed;
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