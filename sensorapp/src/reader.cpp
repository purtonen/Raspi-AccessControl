#include "reader.h"
#include "door.h"

Reader::Reader(){
	this->running = false;
}

void Reader::closeDoor(){
	this->door.closeDoor();
}

void Reader::openDoor(){
	this->door.openDoor();
}

void Reader::setDoor(Door door){
	this->door = door;
}

void Reader::addCard(Card card){
	this->cards.push_back(card);
}

void Reader::startReader(){

}