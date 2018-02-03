#include <string>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include "gpioController.h"

using namespace std;

GPIOController::GPIOController() {}

GPIOController::GPIOController(SocketWriter sw){
	this->sw = sw;
}

GPIOController::GPIOController(vector<GPIO> gpios, SocketWriter sw){
	this->gpios = gpios;
	this->sw = sw;
}

void GPIOController::addGPIO(GPIO &gpio){
	this->gpios.push_back(gpio);
}
void GPIOController::removeGPIO(GPIO &gpio){
	// TODO
}
void GPIOController::readGPIO(){

	string val;

	for (vector<GPIO>::iterator it = this->gpios.begin(); it != this->gpios.end(); ++it){
		val = "NULL";
		it->getval_gpio(val);
		if (it->valueIsChanged()) {
			time_t timestamp = time(nullptr);
			string date = to_string(timestamp);
			string date_r = R"()" + date + R"()";
			string msg = R"({
				"logEntry":{
					"timestamp":")" + date_r + R"(",
					"event_type":"sensor_triggered",
					"sensor_type":"raw",
					"sensor_value":")" + val + R"("
				}
			})";
			this->sw.writeToSocket(msg);
			it->resetValueChanged();
		}
	}
	
}
void GPIOController::writeToGPIO(GPIO &gpio, string value){

}

void GPIOController::initController(){

}