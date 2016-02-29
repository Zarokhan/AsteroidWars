#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f _position, const sf::Vector2f _direction)
	: GameObject("../Images/beam.png")
{
	setPosition(_position);
	direction = _direction;
	speed = PROJECTILE_SPEED;
}

void Projectile::Update(float delta)
{
	Movement();
	AdjustRotation();

	if (!isDead)
		OutOfBounds();
}

void Projectile::AdjustRotation()
{
	double degrees = std::atan2(direction.y, direction.x);
	degrees = degrees * (180 / 3.14159265359);
	setRotation((float)degrees);
}

void Projectile::Movement()
{
	velocity = direction * speed;
	move(velocity);
}

void Projectile::OutOfBounds()
{
	if (getPosition().x - getOrigin().x >= CAMERA_WIDTH)
		isDead = true;
	else if (getPosition().x + getOrigin().x < 0)
		isDead = true;

	if (getPosition().y + getOrigin().x < 0)
		isDead = true;
	else if (getPosition().y - getOrigin().y >= CAMERA_HEIGHT)
		isDead = true;
}

Projectile::~Projectile()
{
}