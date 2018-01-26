#ifndef DOOR_H
#define DOOR_H

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