#include "door.h"

Door::Door(){
	open = true;
}

Door::Door(bool isControllable){
	this->open = true;
	this->controllable = isControllable;
}

bool Door::isOpen(){
	return this->open;
}

bool Door::isControllable(){
	return this->controllable;
}

void Door::openDoor(){
	open = true;
}

void Door::closeDoor(){
	open = false;
}