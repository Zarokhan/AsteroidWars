#pragma once
#include "FuSMMachine.h"

class Ship;

class FuSMControl
{
private:
	FuSMMachine* machine;
	
public:
	Ship* ship;

	FuSMControl(Ship* ship = NULL);

	void Init();	// Resets all AI logic
	void Update();	
	void UpdatePerceptions();
	void SetShip(Ship* ship) { this->ship = ship; }
};