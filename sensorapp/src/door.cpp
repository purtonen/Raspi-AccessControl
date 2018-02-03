#include "door.h"

Door::Door(){
	open = true;
}

Door::Door(bool isControllable, GPIO &gpio, GPIOController &gc){
	this->open = true;
	this->controllable = isControllable;
	this->gpio = gpio;
	this->gc = gc;
}

bool Door::isOpen(){
	return this->open;
}

bool Door::isControllable(){
	return this->controllable;
}

void Door::openDoor(){
	open = true;
	this->gc.writeToGPIO(this->gpio, "0");
}

void Door::closeDoor(){
	open = false;
	this->gc.writeToGPIO(this->gpio, "1");
}