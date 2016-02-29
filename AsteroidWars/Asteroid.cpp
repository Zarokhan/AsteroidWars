#include "Asteroid.h"

Asteroid::Asteroid(const int id, const float rot_scale, const float _speed, const sf::Vector2f position, const sf::Vector2f _direction)
	: GameObject("../Images/asteroids/medium/5.png"), ID(id), rotation_scale(rot_scale)
{
	setPosition(position);
	speed = _speed;
	direction.x = _direction.x;
	direction.y = _direction.y;
}

void Asteroid::Update(float delta)
{
	Movement();
	OutOfBounds();
}

void Asteroid::Movement()
{
	velocity = direction * speed;
	move(velocity);
	this->rotate(rotation_scale * ROTATION_SPEED);
}

void Asteroid::OutOfBounds()
{
	if (getPosition().x - getOrigin().x >= CAMERA_WIDTH)
		setPosition(-getOrigin().x, getPosition().y);
	else if (getPosition().x + getOrigin().x < 0)
		setPosition(CAMERA_WIDTH + getOrigin().x, getPosition().y);

	if (getPosition().y + getOrigin().x < 0)
		setPosition(getPosition().x, CAMERA_HEIGHT + getOrigin().y);
	else if (getPosition().y - getOrigin().y >= CAMERA_HEIGHT)
		setPosition(getPosition().x, -getOrigin().y);
}

Asteroid::~Asteroid()
{
}