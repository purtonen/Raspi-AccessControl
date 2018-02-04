#include <string>
#include <iostream>
#include <unistd.h>
#include <ctime>

#include "sqlite3.h"
#include "doorController.h"
#include "gpioController.h"
#include "door.h"

using namespace std;

DoorController::DoorController() {}

DoorController::DoorController(GPIOController* gc){
	this->gc = gc;
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName){
	DoorController* dc = (DoorController*) NotUsed;
	dc->callbackHandler(argc, argv, azColName);
	return 0;
}

void DoorController::addDoor(int index, Door &door){
	this->doors[index] = door;
}

void DoorController::removeDoor(int index){
	this->doors.erase(index);
}

void DoorController::initDoors(){
	sqlite3* db;
	char* dbPath = (char*)"sensorapp/db/sensorapp";
	char* testSql = (char*)"SELECT id, gpio_in, gpio_out FROM door";
	char* zErrMsg = 0;

	if(sqlite3_open(dbPath, &db)){
		cout << "SQLite open error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return;
	}
	
	if(sqlite3_exec(db, testSql, callback, (void*) this, &zErrMsg) != SQLITE_OK){
		cout << "SQLite exec error: " << sqlite3_errmsg(db) << endl;
		sqlite3_free(db);
		return;
	}

	sqlite3_close(db);
}

void DoorController::callbackHandler(int argc, char **argv, char **azColName){
	for(int i = 0; i < argc; i++){
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\t";
	}

	int in, out;
	if(argv[1]){
		in = strtol(argv[1], NULL, 0);
		cout << "add gpio" << endl;
		this->gc->addGPIO(in, "in");
	}
	if(argv[2]){
		out = strtol(argv[2], NULL, 0);
		this->gc->addGPIO(out, "out");
	}

	Door newDoor = Door(in, out, this->gc);
	int doorIndex = strtol(argv[0], NULL, 0);
	this->doors[doorIndex] = newDoor;
}

int DoorController::openDoor(int index){
	if(this->doors.find(index) == this->doors.end()){
		return -1;
	}
	if(this->doors[index].isControllable()){
		this->doors[index].openDoor();
		return 0;
	}

	return -1;
}

int DoorController::closeDoor(int index){
	if(this->doors.find(index) == this->doors.end()){
		return -1;
	}
	if(this->doors[index].isControllable()){
		this->doors[index].closeDoor();
		return 0;
	}

	return -1;
}