#pragma once
#include "GameObject.h"
#include "SFML\Graphics.hpp"

#define ROTATION_SPEED 10

class Asteroid : public GameObject
{
private:
	float rotation_scale; // Scales the rotation speed
	int ID;

protected:
	virtual void OutOfBounds() override;
	virtual void Movement() override;

public:
	Asteroid(const int id, const float rot_scale, const float _speed, const sf::Vector2f position, const sf::Vector2f _direction);
	~Asteroid();
	virtual void Update(float delta) override;

	const int GetID() { return ID; }
};