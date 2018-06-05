#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "gpio.h"

using namespace std;

GPIO::GPIO() {
	this->gpionum = "4"; //GPIO4 is default
	this->valueChanged = false;
}

GPIO::GPIO(string gnum) {
	this->gpionum = gnum; //Instantiate GPIO object for GPIO pin number "gnum"
	this->valueChanged = false;
}

int GPIO::export_gpio() {
	string export_str = "/sys/class/gpio/export";
	ofstream exportgpio(export_str.c_str()); // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames
	if (!exportgpio) {
		cout << " OPERATION FAILED: Unable to export GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	exportgpio << this->gpionum; //write GPIO number to export
	exportgpio.close(); //close export file
	return 0;
}

int GPIO::unexport_gpio() {
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_str.c_str()); //Open unexport file
	if (!unexportgpio) {
		cout << " OPERATION FAILED: Unable to unexport GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	unexportgpio << this->gpionum; //write GPIO number to unexport
	unexportgpio.close(); //close unexport file
	return 0;
}

int GPIO::setdir_gpio(string dir) {

	string setdir_str = "/sys/class/gpio/gpio" + this->gpionum + "/direction";
	ofstream setdirgpio(setdir_str.c_str()); // open direction file for gpio
	if (!setdirgpio) {
		cout << " OPERATION FAILED: Unable to set direction of GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	setdirgpio << dir; //write direction to direction file
	setdirgpio.close(); // close direction file
	this->direction = dir;
	return 0;
}

int GPIO::setval_gpio(string val) {

	string setval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ofstream setvalgpio(setval_str.c_str()); // open value file for gpio
	if (!setvalgpio) {
		cout << " OPERATION FAILED: Unable to set the value of GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	setvalgpio << val; //write value to value file
	setvalgpio.close(); // close value file

	if (this->previousValue != val) {
		this->valueChanged = true;
		this->previousValue = val;
	}

	return 0;
}

int GPIO::getval_gpio(string &val) {
	string line;

	string getval_str = "/sys/class/gpio/gpio" + this->gpionum + "/value";
	ifstream getvalgpio(getval_str.c_str(), ifstream::in); // open value file for gpio
	if (!getvalgpio) {
		cout << " OPERATION FAILED: Unable to get value of GPIO" << this->gpionum << " ." << endl;
		return -1;
	}

	getvalgpio >> val; //read gpio value

	if (val != "0")
		val = "1";
	else
		val = "0";

	getvalgpio.close(); //close the value file

	if (this->previousValue != val) {
		this->valueChanged = true;
		this->previousValue = val;
	}

	return 0;
}

string GPIO::get_gpionum() {

	return this->gpionum;
}

bool GPIO::valueIsChanged() {
	return this->valueChanged;
}

void GPIO::resetValueChanged() {
	this->valueChanged = false;
}