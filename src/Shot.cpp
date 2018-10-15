#include "Shot.h"
#include "ofMain.h"

Shot::Shot() {};
Shot::Shot(int x, int y, int s) {
	this->x = x;
	this->y = y;
	speed = s;
	//bullet.load("shot.png");
}
void Shot::setSpeed(int s) {
	speed = s;
}
void Shot::move() {
	y -= speed;
}

int Shot::getSpeed() {
	return speed;
}

void Shot::draw()
{
	ofSetColor(ofColor::white);
	//bullet.draw(x, y, 10, 20);
	ofDrawRectangle(x,y,5, 10);
}

int Shot::getX() {
	return x;
}
int Shot::getY() {
	return y;
}