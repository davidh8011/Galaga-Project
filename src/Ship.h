#pragma once
#include "ofMain.h"

class Ship{
protected:
	int x;
	int y;
	int speed;
	int shotSpeed;
	ofImage ship;
	bool alive;

public:
	Ship();
	Ship(int, int, int, int);
	void setX(int);
	void setY(int);
	void setSpeed(int);
	void setShotSpeed(int);
	int getX();
	int getY();
	int getSpeed();
	int getShotSpeed();
	void move(int);
	//void draw();
	bool isAlive();
	void die();

};