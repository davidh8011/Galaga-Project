#include "Enemy1.h"


Enemy1::Enemy1(int x0, int y0, int s, int ss) {
	x = x0;
	y = y0;
	speed = s;
	shotSpeed = ss;
	ship.load("Enemy1.png");
	alive = true;
	diving = false;
}


void Enemy1::draw() {
	ofSetColor(ofColor::white);
	ship.draw(x, y, 50, 50);
}


void Enemy1::move(int pos) {
	if (diving == false)
		x += pos;
	int s = ofRandom(0, 5000);
	if (s == 5 && diving == false) {
		diving = true;
		diveCounter = 0;
	}
	if (diving == true)
	{
		//cout << diveCounter << endl;
		if (y < ofGetHeight())
			y+=4;
		else if (y >= ofGetHeight()) {
			y = 0;
			y+=4;
		}
		if (diveCounter >= 764)
			diving = false;
		diveCounter+=4;
	}

}

bool Enemy1::fire() {
	int r = ofRandom(0, 1000);
	if (r == 1)
		return true;
	else
		return false;
}
