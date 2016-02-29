#include "Ship.h"
#include "MathUtils.h"
#include <iostream>

Ship::Ship(GameSession* p)
	: GameObject("../Images/SpaceShip.png")
{
	this->parent = p;
	speed = START_SPEED;
	rotation_speed = START_ROTATION_SPEED;
	direction.x = 1.f;
}

void Ship::Update(float delta)
{
	Movement();
	AdjustRotation();

	OutOfBounds();
	CheckNearestAsteroid();

	if (control != nullptr)
		control->Update();
}

void Ship::Movement()
{
	velocity = direction * speed;
}

void Ship::Shoot()
{
	if (reload.getElapsedTime().asSeconds() >= RELOAD_TIME && lineofsight)
	{
		parent->SpawnProjectile();
		reload.restart();
	}
}

void Ship::SteerToNearestAsteroid()
{
	if (nearest == nullptr)
		return;

	sf::Vector2f target;
	target.x = (nearest->getPosition().x + nearest->GetVelocity().x) - this->getPosition().x;
	target.y = (nearest->getPosition().y + nearest->GetVelocity().y) - this->getPosition().y;

	float target_degrees_relative_ship = std::atan2f(target.y, target.x);
	target_degrees_relative_ship = FunMath::ToDegrees(target_degrees_relative_ship);

	// Shoot perception
	float perception = rotation - std::abs(target_degrees_relative_ship);
	if (perception > -SHOOT_PERCEPTION_DEGREES && perception < SHOOT_PERCEPTION_DEGREES)
		lineofsight = true;
	else
		false;
	
	// Turn perception
	perception = rotation - std::abs(target_degrees_relative_ship);
	if (perception > -STEER_PERCEPTION_DEGREES && perception < STEER_PERCEPTION_DEGREES)
		return;

	if (target_degrees_relative_ship > rotation)
		SteerRight(1.f);
	else
		SteerRight(-1.f);
}

bool Ship::NeedToEvade()
{
	if (nearest_asteroid_distance < ASTEROID_PANIC_RANGE)
		return true;
	else
		return false;
}

void Ship::Evade()
{
	if (nearest == nullptr)
		return;

	sf::Vector2f target = (nearest->getPosition() + nearest->GetVelocity()) - this->getPosition();

	float target_degrees = std::atan2f(target.y, target.x);
	target_degrees = FunMath::ToDegrees(target_degrees);
	float target_degrees_relative_ship = target_degrees - rotation;

	//std::cout << "Degrees: " << (int)target_degrees_relative_ship << std::endl;

	// In front of player
	if (target_degrees_relative_ship > -45 && target_degrees_relative_ship < 45)
		ThrustBackward();
	else if (target_degrees_relative_ship < -180 && target_degrees_relative_ship > -135 || target_degrees_relative_ship < 180 && target_degrees_relative_ship > 135)
		ThrustForward();
	else if (target_degrees_relative_ship > 45 && target_degrees_relative_ship < 135)
	{
		ThrustBackward();
		SteerRight(-0.5f);
	}
	else
	{
		ThrustBackward();
		SteerRight(0.5f);
	}
}

void Ship::CheckNearestAsteroid()
{
	nearest = nullptr;
	nearest_asteroid_distance = 10000.f;
	std::vector<Asteroid*> temp = parent->GetAsteroids();

	for (int i = 0; i < temp.size(); i++)
	{
		float distance = FunMath::Distance(temp[i]->getPosition(), this->getPosition());
		if (distance < nearest_asteroid_distance)
		{
			nearest = temp[i]; // Return nearest asteroid as a pointer reference
			nearest_asteroid_distance = distance;
		}
	}
}

void Ship::SteerRight(const float& val)
{
	rotation += val * rotation_speed;
	rotation = std::fmodf(rotation, 360);
}

void Ship::AdjustRotation()
{
	direction.x = std::cosf(FunMath::ToRadians(rotation));
	direction.y = std::sinf(FunMath::ToRadians(rotation));
	setRotation(rotation);
}

void Ship::OutOfBounds()
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

void Ship::KeyboardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		ThrustForward();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		ThrustBackward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		rotate(rotation_speed);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		rotate(-rotation_speed);
}

void Ship::ThrustForward(float val)
{
	move(velocity * val);
}

void Ship::ThrustBackward(float val)
{
	move(-velocity * val);
}

Ship::~Ship()
{

}