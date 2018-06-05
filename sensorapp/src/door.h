#ifndef DOOR_H
#define DOOR_H

#include "gpioController.h"

class Door {
	int id, gpioIn, gpioOut;
	;
	bool _isOpen, _isControllable, _hasSensor;
	GPIOController* gc;
public:
	Door();
	Door(int gpioIn, int gpioOut, GPIOController* gc);
	bool isOpen();
	bool isControllable();
	bool hasSensor();
	void closeDoor();
	void openDoor();
};

#endif