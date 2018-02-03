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

// Local headers
#include "gpio.h"
#include "gpioController.h"
#include "socketWriter.h"
#include "card.h"
#include "door.h"
#include "reader.h"
#include "log.h"

using namespace std;

// Path to the Unix socket to be used for inter-process-communication (ipc)
char *socketPath = "/tmp/ipc-test";

// Functions
void msgInterpreter(string msg); // Interpret incoming JSON data and call the neccessary functions
void listenToSocket(int rc, int cl); // Thread: Continuously read the Unix socket and call msgInterpreter on message
void listenToGPIO(GPIOController gc); // Thread: Continuously read the gpio controller and call socketwriter
void initGPIO(GPIOController &gc); // Initialize the GPIO and GPIO controller

// Main function
int main (int argc, char *argv[]) {
	usleep(50000);
	cout << " " << endl; // clear bash output

	struct sockaddr_un addr;
	int fd, cl, rc;
	char *msg = "Hello back";
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

	// Initialize the socketwriter and GPIO controllers
	SocketWriter sw = SocketWriter(cl);
	GPIOController gc = GPIOController(sw);
	initGPIO(gc);

	// Start listeners
	thread socketlistenerThread(listenToSocket, rc, cl);
	thread gpioListenerThread(listenToGPIO, gc);

	socketlistenerThread.join();
	gpioListenerThread.join();

	while(true){

	}

	return 0;
}
// End main function


void msgInterpreter(string msg){
	cout << "socketserver: interpreter: " << msg << endl;
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

void listenToGPIO(GPIOController gc){
    while(1){
        gc.readGPIO();
    }
}

void initGPIO(GPIOController &gc){
	GPIO gpio4 = GPIO("4");
    gpio4.export_gpio();
    usleep(5000);
    gpio4.setdir_gpio("in");

	GPIO gpio18 = GPIO("18");
    gpio18.export_gpio();
    usleep(5000);
    gpio18.setdir_gpio("out");

	gc.addGPIO(gpio4);
	gc.addGPIO(gpio18);
}