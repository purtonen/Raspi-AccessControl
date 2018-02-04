#include <string>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include "gpioController.h"
#include "gpio.h"

using namespace std;

GPIOController::GPIOController() {}

GPIOController::GPIOController(SocketWriter sw){
	this->sw = sw;
}

GPIOController::GPIOController(map<int, GPIO> gpios, SocketWriter sw){
	this->gpios = gpios;
	this->sw = sw;
}

void GPIOController::addGPIO(int gpioId, string direction){
	GPIO gpio = GPIO(to_string(gpioId));
    gpio.export_gpio();
    usleep(5000);
    gpio.setdir_gpio(direction);
	this->gpios[gpioId] = gpio;
	usleep(5000);
}
void GPIOController::removeGPIO(int gpioId){
	// TODO
}
void GPIOController::readGPIO(){

	string val;

	for (auto it=gpios.begin(); it!=gpios.end(); ++it){
		val = "NULL";
		it->second.getval_gpio(val);
		if (it->second.valueIsChanged()) {
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
			it->second.resetValueChanged();
		}
	}
	
}
void GPIOController::writeToGPIO(int gpioId, string value){
	gpios[gpioId].setval_gpio(value);
}

void GPIOController::initController(){

}