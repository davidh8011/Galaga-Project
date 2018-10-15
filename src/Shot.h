#pragma once
#include "ofMain.h"

class Shot {
	int x;
	int y;
	int speed;
	//ofImage bullet;

public:
	Shot();
	Shot(int, int, int);
	void setSpeed(int);
	void move();
	void draw();
	int getSpeed();
	int getX();
	int getY();

};
