#pragma once

#define NUM_SECTORS 18

class Gene
{
	//Gene() { std::srand(std::time(0)); thrust = GNR_RANDOM_INT(2); sector = GNR_RANDOM_INT(NUM_SECTORS - 1); };
	Gene() {}
public:
	Gene(int a, int b) : thrust(a), sector(b) {}

	bool operator == (const Gene &rhs) const { return (thrust == rhs.thrust) && (sector == rhs.sector); }
	bool operator != (const Gene &rhs) const { return (thrust != rhs.thrust) || (sector != rhs.sector); }

	// data
	int thrust;	// forward, reverse, no thrust
	int sector;	// unsigned int, represents 0 - 17 sectors at which the AI wants the ship to point, 1 sector represents 20 degrees
};