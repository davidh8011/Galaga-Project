#include "Ship.h"
using namespace std;

Ship::Ship() {}

Ship::Ship(int x0, int y0, int s, int ss) {
	x = x0;
	y = y0;
	speed = s;
	shotSpeed = ss;
	ship.load("Ship.jpg");
}
void Ship::setX(int x0)
{
	x = x0;
}
void Ship::setY(int y0) {
	y = y0;
}
void Ship::setSpeed(int s) {
	speed = s;
}
void Ship::setShotSpeed(int ss) {
	shotSpeed = ss;
}
int Ship::getX() {
	return x;
}
int Ship::getY() {
	return y;
}
int Ship::getSpeed() {
	return speed;
}
int Ship::getShotSpeed() {
	return shotSpeed;
}
void Ship::move(int d) {
	x += d;
}
/*void Ship::draw()
{
	ofSetColor(ofColor::white);
	ship.draw(x, y, 50, 50);
}*/
bool Ship::isAlive() {
	return alive;
}



void Ship::die() {
	alive = false;
	//explosion.load("Explosion.png");
	//explosion.draw(x, y, 50, 50);
}