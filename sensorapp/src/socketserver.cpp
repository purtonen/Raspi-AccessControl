#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <string>
#include <cstring>
// #include "card.cpp"
// #include "door.cpp"
// #include "reader.cpp"
// #include "log.cpp"

using namespace std;

char *socketPath = "/tmp/ipc-test";

void msgInterpreter(string msg){
	cout << "interpreter: " << msg << endl;
}

void listenToSocket(char *socketPath){
	struct sockaddr_un addr;
	int fd, cl, rc;
	char buf[100];

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(-1);
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
		exit(-1);
	}

	if (listen(fd, 5) == -1) {
		perror("listen error");
		exit(-1);
	}

	while (1) {
		if ((cl = accept(fd, NULL, NULL)) == -1)
		{
			perror("accept error");
			continue;
		}

		while ((rc = read(cl, buf, sizeof(buf))) > 0) {
			string msg(buf, rc);
			msgInterpreter(msg);
		}

		if (rc == -1) {
			perror("read");
			exit(-1);
		} else if (rc == 0) {
			printf("EOF\n");
			close(cl);
		}
			
	}

}

void writeToSocket(char *socketPath, char *msg){
	struct sockaddr_un addr;
	int fd, cl;

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket error");
		exit(-1);
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
		exit(-1);
	}

	if (listen(fd, 5) == -1) {
		perror("listen error");
		exit(-1);
	}

	if ((cl = accept(fd, NULL, NULL)) == -1){
		perror("accept error");
	}

	printf("writer running\n");

	if (write(cl, msg, strlen(msg)) < 0) {
		printf("write error\n");
		perror("ERROR writing to socket");
		exit(-1);
	} else {
		printf("socketserver written data\n");
	}
}

int main (int argc, char *argv[]) {

	thread listenThread(listenToSocket, socketPath);

	listenThread.join();

	return 0;
}