#ifndef DOOR_H
#define DOOR_H

#include <vector>
#include <string>

#include "gpioController.h"
#include "doorController.h"
#include "reader.h"
#include "card.h"

class Reader;
class DoorController;

class Door {
	int id, gpioIn, gpioOut;
	bool _isOpen, _isControllable, _hasButton, previousState;
	std::vector<Card> acceptedCards;
	Reader* reader;
	GPIOController* gc;
	DoorController* dc;
public:
	Door();
	Door(int gpioIn, int gpioOut, GPIOController* gc, DoorController* dc);
	void addCard(Card card);
	void setReader(Reader* reader);
	void cardReadEvent(std::string card);
	bool stateChanged();
	bool isOpen();
	bool isControllable();
	bool hasButton();
	void closeDoor();
	void openDoor();
};

#endif