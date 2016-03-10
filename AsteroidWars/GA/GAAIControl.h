#pragma once
#include <SFML\Graphics.hpp>
#include "GASession.h"

class GASession;

class GAAIControl
{
private:
	GASession* Session;
public:
	GAAIControl(GASession* session) : Session(session) {}

	void UpdatePerceptions(float delta, int index);

	inline float DOT(sf::Vector2f &a, sf::Vector2f &b)
	{
		return a.x*b.x + a.y*b.y;
	}

	int* test = new int;
	sf::Vector2f* test2 = new sf::Vector2f();

	int currentEvasionSituation;
};