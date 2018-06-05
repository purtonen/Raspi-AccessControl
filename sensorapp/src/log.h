#ifndef LOG_H
#define LOG_H

#include <string>

class Log {
	int id;
	std::string timestamp, description;

public:
	Log();
	Log(std::string description);
	std::string toString();
};

#endif