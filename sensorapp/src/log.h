#ifndef Log_H
#define Log_H
#include <string>

class Log{
	int id;
	std::string timestamp, description;

public:
	Log();
	Log(std::string description);
	string toString();
};

#endif