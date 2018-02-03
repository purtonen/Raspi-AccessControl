#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <string>
#include <vector>

#include "gpio.h"
#include "socketWriter.h"

/* GPIO controller Class
 * Purpose: Wrap all GPIO objects/pins to one class for reading and writing
 */
class GPIOController {
    std::vector<GPIO> gpios;
    SocketWriter sw;
public:
    GPIOController();
    GPIOController(SocketWriter sw);
    GPIOController(std::vector<GPIO> gpios, SocketWriter sw);
    void addGPIO(GPIO &gpio);
    void removeGPIO(GPIO &gpio);
    void readGPIO();
    void writeToGPIO(GPIO &gpio, std::string value);
    void initController();
};

#endif