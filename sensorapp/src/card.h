#ifndef CARD_H
#define CARD_H

#include <string>

class Card{
	int id;
	std::string cardholder;
	bool isOpen;

public:
	Card();
	std::string getCardholder();
	void setCardholder(std::string cardholder);
};

#endif