#include <string>
#include <iostream>
#include <unistd.h>
#include <ctime>

#include "doorController.h"
#include "door.h"

using namespace std;

DoorController::DoorController() {}

void DoorController::addDoor(int index, Door* door){
	this->doors[index] = door;
}

void DoorController::removeDoor(int index){
	this->doors.erase(index);
}

void DoorController::initDoors(){

}

int DoorController::openDoor(int index){
	if(this->doors.find(index) != this->doors.end()){
		return -1;
	}
	this->doors[index]->openDoor();

	return 0;
}

int DoorController::closeDoor(int index){
	if(this->doors.find(index) != this->doors.end()){
		return -1;
	}
	this->doors[index]->closeDoor();

	return 0;
}