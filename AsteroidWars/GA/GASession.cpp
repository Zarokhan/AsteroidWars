#include "GASession.h"

void GASession::Init()
{
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	
	ship = new Ship(this);
	ship->setPosition(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f));

	std::srand(std::time(0));	// Sets seed for random numbers

	spawnedAsteroids = 0;
}

void GASession::Dispose()
{
}

void GASession::SpawnAsteroids()
{
}

void GASession::HandleProjectiles()
{
}

void GASession::HandleCollision()
{
}

void GASession::Update(float delta)
{
}

void GASession::Draw()
{
}

void GASession::SpawnProjectile()
{
}

Asteroid * GASession::GetAsteroid(int ID) const
{
	return nullptr;
}
