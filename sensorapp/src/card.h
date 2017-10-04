#ifndef Card_H
#define Card_H
#include <string>

class Card{
	int id;
	std::string cardholder;

public:
	Card();
	string getCardholder();
	void setCardholder(std::string cardholder);
};

#endif