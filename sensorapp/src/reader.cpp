#include "reader.h"

Reader::Reader(){
	this->running = false;
}

void Reader::closeDoor(){
	this->door->open();
}

void Reader::closeDoor(){
	this->door->close();
}

void Reader::setDoor(Door* door){
	this->door = door;
}

void Reader::addCard(Card* card){
	this->cards.push_back(card);
}

void Reader::startReader(){

}