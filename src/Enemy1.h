#pragma once
#include "Ship.h"

class Enemy1 : public Ship {
	ofImage explosion;
	bool diving;
	int diveCounter;
public:
	Enemy1() = default;
	Enemy1(int, int, int, int);
	void draw();
	void move(int);
	bool fire();
};