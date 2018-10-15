#include "Enemy2.h"


Enemy2::Enemy2(int x0, int y0, int s, int ss) {
	x = x0;
	y = y0;
	speed = s;
	shotSpeed = ss;
	ship.load("Enemy2.png");
	alive = true;
}


void Enemy2::draw() {
	ofSetColor(ofColor::white);
	ship.draw(x, y, 50, 50);
}


void Enemy2::move() {
	x += ofRandom(-2, 3);
	y += ofRandom(-2, 3);
}

bool Enemy2::fire() {
	int x = ofRandom(0, 500);
	if (x == 1)
		return true;
	else
		return false;
}
