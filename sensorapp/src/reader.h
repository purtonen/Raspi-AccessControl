#ifndef READER_H
#define READER_H

#include <vector>

#include "card.h"

class Door;

class Reader {
	int id;
	Door* door;
	void listenToCards();

public:
	Reader();
	void setDoor(Door* door);
	void startListener();
};

#endif