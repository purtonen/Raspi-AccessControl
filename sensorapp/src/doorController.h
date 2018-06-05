#ifndef DOORCONTROLLER_H
#define DOORCONTROLLER_H

#include <string>
#include <vector>
#include <map>

#include "card.h"
#include "door.h"
#include "gpioController.h"

/* Door controller Class
 * Purpose: Wrap all Doors to one class for opening and closing doors
 */
class DoorController {
	std::map<int, Door> doors;
	std::vector<Card> acceptedCards;
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