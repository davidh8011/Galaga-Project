#include "Powerup.h"

Powerup::Powerup()
{
	int s = ofRandom(0, 10);
	if (s > 5) {
		x = 0;
		left = true;
	}
	else {
		x = ofGetWidth();
		left = false;
	}
	y = ofRandom(50, 100);
	flash = false;
	powertimer = -5;
}

void Powerup::move() {
	if (left)
		x+=2;
	else
		x-=2;
	if (flash) {
		flash = false;
		
	}
	else {
		flash = true;
	}
}

void Powerup::draw() {
	if (powertimer <0) {
		ofSetColor(ofColor::white);
	}
	else if(powertimer<7){
		ofSetColor(ofColor::red);
	}
	else {
		powertimer = -5;
		ofSetColor(ofColor::red);
	}
	powertimer++;
	ofDrawCircle(x, y, 25);
}

int Powerup::getX() {
	return x;
}

int Powerup::getY() {
	return y;
}