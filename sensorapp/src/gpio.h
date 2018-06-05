#ifndef GPIO_H
#define GPIO_H

#include <string>

/* GPIO Class
 * Purpose: Each object instantiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 */
class GPIO {
public:
	GPIO(); // create a GPIO object that controls GPIO4 (default
	GPIO(std::string x); // create a GPIO object that controls GPIOx, where x is passed to this constructor
	int export_gpio(); // exports GPIO
	int unexport_gpio(); // unexport GPIO
	int setdir_gpio(std::string dir); // Set GPIO Direction
	int setval_gpio(std::string val); // Set GPIO Value (putput pins)
	int getval_gpio(std::string& val); // Get GPIO Value (input/ output pins)
	std::string get_gpionum(); // return the GPIO number associated with the instance of an object
	void resetValueChanged();
	bool valueIsChanged();
private:
	std::string gpionum; // GPIO number associated with the instance of an object
	std::string direction; // GPIO pin direction: input or output, "in" or "out"
	std::string value;
	std::string previousValue;
	bool valueChanged;
};

#endif