#include "Fighter.h"


Fighter::Fighter(int x0, int y0, int s, int ss) {
	x = x0;
	y = y0;
	speed = s;
	shotSpeed = ss;
	powerup = false;
	ship.load("Ship.jpg");
	alive = true;
}
void Fighter::draw() {
	ofSetColor(ofColor::white);
	if (powerup)
		ofSetColor(ofColor::red);
	ship.draw(x, y, 50, 50);
}

void Fighter::powerOn() {
	powerup = true;
	shotSpeed *= 2;
	speed *= 2;
}

void Fighter::powerOff() {
	powerup = false;
	shotSpeed /= 2;
	speed /= 2;
}

bool Fighter::hasPowerUp()
{
	return powerup;
}

void Fighter::revive() {
	alive = true;
}