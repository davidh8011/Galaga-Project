#pragma once
#include "Ship.h"

class Fighter : public Ship {
	bool powerup;
public:
	Fighter(int, int, int, int);
	void draw();
	void powerOn();
	void powerOff();
	bool hasPowerUp();
	void revive();

};