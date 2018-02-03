#ifndef DOOR_H
#define DOOR_H

#include "gpio.h"
#include "gpioController.h"

class Door{
	int id;
	bool open, controllable;
	GPIO gpio;
	GPIOController gc;
public:
	Door();
	Door(bool isControllable, GPIO &gpio, GPIOController &gc);
	bool isOpen();
	bool isControllable();
	void closeDoor();
	void openDoor();
};

#endif