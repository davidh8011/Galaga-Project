#pragma once
#include "ofMain.h"

class Powerup {
	int x;
	int y;
	bool left;
	bool flash;
	ofImage pic;
	ofSpherePrimitive sphere;
	int powertimer;
public:
	Powerup();
	void move();
	void draw();
	int getX();
	int getY();
};
