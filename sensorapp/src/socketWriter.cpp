#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "socketWriter.h"

using namespace std;

SocketWriter::SocketWriter() {}

SocketWriter::SocketWriter(int cl){
	this->cl = cl;
}

void SocketWriter::writeToSocket(string msg){
    const char* msg_c = msg.c_str();
	if (send(this->cl, msg_c, strlen(msg_c), 0) < 0) {
		perror("ERROR writing to socket");
		exit(-1);
	}
}