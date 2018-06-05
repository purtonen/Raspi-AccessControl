#ifndef DOORCONTROLLER_H
#define DOORCONTROLLER_H

#include <string>
#include <map>

#include "card.h"
#include "door.h"
#include "gpioController.h"

class DoorController {
	std::map<int, Door> doors;
	GPIOController* gc;
public:
	DoorController();
	DoorController(GPIOController* gc);
	void addDoor(int index, Door &door);
	void removeDoor(int index);
	void initDoors();
	int openDoor(int index);
	int closeDoor(int index);
	void callbackHandler(int argc, char **argv, char **azColName);
};

#endif