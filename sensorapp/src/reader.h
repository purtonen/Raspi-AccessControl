#ifndef READER_H
#define READER_H

#include <vector>

#include "door.h"
#include "card.h"

class Reader {
	int id;
	Door door;
	void listenToCards();

public:
	Reader();
	void setDoor(Door door);
	void startListener();
};

#endif