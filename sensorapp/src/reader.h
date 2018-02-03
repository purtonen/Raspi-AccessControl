#ifndef READER_H
#define READER_H

#include <vector>

#include "door.h"
#include "card.h"

class Reader{
	int id;
	Door door;
	std::vector<Card> cards;
	bool running;

public:
	Reader();
	void closeDoor();
	void openDoor();
	void setDoor(Door door);
	void addCard(Card card);
	void startReader();
};

#endif