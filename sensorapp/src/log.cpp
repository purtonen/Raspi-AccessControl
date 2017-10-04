#include "log.h"

Log::Log(){
	
}

Log::Log(string description){
	this->description = description;
}

string Log::toString(){
	return this->timestamp + ' ' + this->description;
}