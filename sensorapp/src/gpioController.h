#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <string>
#include <map>

#include "gpio.h"
#include "socketWriter.h"

/* GPIO controller Class
 * Purpose: Wrap all GPIO objects/pins to one class for reading and writing
 */
class GPIOController {
    std::map<int, GPIO> gpios;
    SocketWriter sw;
public:
    GPIOController();
    GPIOController(SocketWriter sw);
    GPIOController(std::map<int, GPIO> gpios, SocketWriter sw);
    void addGPIO(int gpioId, std::string direction);
    void removeGPIO(int gpioId);
    void readGPIO();
    void writeToGPIO(int gpioId, std::string value);
    void initController();
};

#endif