#include <thread>
#include <string>
#include <unistd.h>

#include "MFRC522.h"
#include "reader.h"
#include "door.h"

using namespace std;

Reader::Reader() {
}

void Reader::listenToCards(){

	MFRC522 mfrc;
	mfrc.PCD_Init();
	string card;

	while (1) {
		// Look for a card
		if (!mfrc.PICC_IsNewCardPresent())
			continue;

		if (!mfrc.PICC_ReadCardSerial())
			continue;

		// Print UID
		for (byte i = 0; i < mfrc.uid.size; ++i) {
			if (mfrc.uid.uidByte[i] < 0x10) {
				printf(" 0");
				printf("%X", mfrc.uid.uidByte[i]);
			} else {
				printf(" ");
				printf("%X", mfrc.uid.uidByte[i]);
			}

		}
		//this->door->cardReadEvent(string card);
		printf("\n");
		usleep(500000);
	}
}

void Reader::setDoor(Door* door) {
	this->door = door;
}

void Reader::startListener() {
	thread cardListenerThread(listenToCards);
	cardListenerThread.join();
}