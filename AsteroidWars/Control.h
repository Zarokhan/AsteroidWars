#pragma once
#include "Ship.h"

class Ship;

class Control
{
protected:
	Ship* ship;

public:
	Control(Ship* ship = NULL) { this->ship = ship; }

	virtual void Update() = 0;
	void SetShip(Ship* ship) { this->ship = ship; }
};