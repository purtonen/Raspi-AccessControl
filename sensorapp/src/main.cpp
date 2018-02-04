// Std libraries
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <map>

// Local headers
#include "gpio.h"
#include "gpioController.h"
#include "socketWriter.h"
#include "card.h"
#include "door.h"
#include "reader.h"
#include "log.h"
#include "doorController.h"

using namespace std;

// Constants
const char *socketPath = (char*)"/tmp/ipc-test";
const string availableGPIO[] = {"2","3","4","17","27","22","10","9","11","14","15","18","23","24","25","8","7"};

// Main variables
SocketWriter sw;
GPIOController* gc;
DoorController dc;

// Functions
void msgInterpreter(string msg); // Interpret incoming JSON data and call the neccessary functions
void listenToSocket(int rc, int cl); // Thread: Continuously read the Unix socket and call msgInterpreter on message
void listenToGPIO(); // Thread: Continuously read the gpio controller and call socketwriter
void initGPIO(); // Initialize the GPIO and add them to the GPIO controller

// Main function
int main (int argc, char *argv[]) {
	usleep(50000);
	cout << " " << endl; // clear bash output

	struct sockaddr_un addr;
	int fd, cl, rc;
	char* msg = (char*)"Hello back";
	bool connected = false;

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	if (*socketPath == '\0'){
		*addr.sun_path = '\0';
		strncpy(addr.sun_path + 1, socketPath + 1, sizeof(addr.sun_path) - 2);
	} else {
		strncpy(addr.sun_path, socketPath, sizeof(addr.sun_path) - 1);
		unlink(socketPath);
	}

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("bind error");
		return -1;
	}

	if (listen(fd, 5) == -1) {
		perror("listen error");
		return -1;
	}

	// Wait for node.js connection
	while (!connected) {

		if ((cl = accept(fd, NULL, NULL)) == -1) {
			perror("accept error");
			continue;
		}

		cout << "socketserver: Connection established" << endl;

		connected = true;

		if (send(cl, msg, strlen(msg), 0) < 0) {
			perror("ERROR writing to socket");
			return -1;
		}
			
	}

	cout << "socketserver: Connections done" << endl;

	// Initialize the socketwriter and Door controller
	sw = SocketWriter(cl);
	gc = new GPIOController(sw);
	dc = DoorController(gc);
	dc.initDoors();
	dc.openDoor(18);

	gc->addGPIO(4, "in");

	// Start listeners
	thread socketlistenerThread(listenToSocket, rc, cl);
	thread gpioListenerThread(listenToGPIO);

	socketlistenerThread.join();
	gpioListenerThread.join();

	return 0;
}
// End main function


void msgInterpreter(string msg){
	vector<string> splitStrings;
	stringstream ss(msg);
    string item;
    while (getline(ss, item, '|')) {
        splitStrings.push_back(item);
    }
	for(auto it = splitStrings.begin(), end = splitStrings.end(); it != end; ++it){
		cout << "socketserver: interpreter: " << *it << endl;
	}
	if(splitStrings.size() > 2){
		stringstream split(splitStrings[1]);
		int targetDoorId;
		split >> targetDoorId;
		if(splitStrings[0] == "door" && splitStrings[2] == "open"){
			if(dc.openDoor(targetDoorId) == -1){
				cout << "socketserver: interpreter: door " << targetDoorId << " not controllable" << endl;
			}
		} else if(splitStrings[0] == "door" && splitStrings[2] == "close"){
			if(dc.closeDoor(targetDoorId) == -1){
				cout << "socketserver: interpreter: door " << targetDoorId << " not controllable" << endl;
			}
		}
	} else {
		cout << "socketserver: interpreter: command not valid" << endl;
	}
}

void listenToSocket(int rc, int cl){
	char buf[100];

	while(1){
		while ((rc = read(cl, buf, sizeof(buf))) > 0) {
			string msg(buf, rc);
			msgInterpreter(msg);
		}

		if (rc == -1) {
			perror("read");
			return;
		} else if (rc == 0) {
			printf("EOF\n");
			close(cl);
		}
	}
}

void listenToGPIO(){
    while(1){
        gc->readGPIO();
    }
}

void initGPIO(){
	// GPIO gpio4 = GPIO("4");
    // gpio4.export_gpio();
    // usleep(5000);
    // gpio4.setdir_gpio("in");

	// GPIO gpio18 = GPIO("18");
    // gpio18.export_gpio();
    // usleep(5000);
    // gpio18.setdir_gpio("out");

	// gc.addGPIO(gpio4);
	// gc.addGPIO(gpio18);

	// Door* door1 = new Door(0, gpio18, gc);

	// DoorController* dc = new DoorController();
	// dc->initDoors();

	// door1->closeDoor();

	//system("raspivid -vf -o $(date +%s).h264 -t 999999999");
}