#ifndef Reader_H
#define Reader_H

class Door;

class Reader{
	int id;
	Door* door;
	vector<Card*> cards;
	bool running;

public:
	Reader();
	void closeDoor();
	void openDoor();
	void setDoor(Door* door);
	void addCard(Card* card);
	void startReader();
};

#endif