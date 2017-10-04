#ifndef Door_H
#define Door_H

#include <vector>
using namespace std;

class Card;

class Door{
	int id;
	bool open, controllable;

public:
	Door();
	Door(bool isControllable);
	bool isOpen();
	bool isControllable();
	void closeDoor();
	void openDoor();
};

#endif