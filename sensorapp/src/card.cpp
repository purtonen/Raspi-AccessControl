#include "card.h"
using namespace std;

Card::Card(){
	isOpen = true;
}

string Card::getCardholder(){
	return cardholder;
}

void Card::setCardholder(string cardholder){
	this->cardholder = cardholder;
}
