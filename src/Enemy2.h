#pragma once
#include "Ship.h"

class Enemy2 : public Ship {
	ofImage explosion;
public:
	Enemy2() = default;
	Enemy2(int, int, int, int);
	void draw();
	void move();
	bool fire();

};