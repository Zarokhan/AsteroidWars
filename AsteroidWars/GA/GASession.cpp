#include "GASession.h"

void GASession::Init()
{
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	std::srand(std::time(0));	// Sets seed for random numbers

	// Initialize all ships
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		Ship *ship = new Ship(this);
		ship->setPosition(sf::Vector2f(GNR_RANDOM_INT(CAMERA_WIDTH), GNR_RANDOM_INT(CAMERA_HEIGHT)));
		ships[i] = ship;
	}

	machine = new GAMachine(NULL);
	machine->parrent = this;

	spawnedAsteroids = 0;
}

void GASession::Dispose()
{
	delete machine;
	for (int i = 0; i < POPULATION_SIZE; i++)
		delete ships[i];
	delete ships;
	int size = asteroids.size();
	for (int i = 0; i < size; i++)
		delete asteroids.at(i);
	size = projectiles.size();
	for (int i = 0; i < size; i++)
		delete projectiles.at(i);
	delete camera;
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
	Window->setView(*camera);

	for (int i = 0; i < POPULATION_SIZE; i++)
		Window->draw(*ships[i]);
}

void GASession::SpawnProjectile()
{
}

Asteroid * GASession::GetAsteroid(int ID) const
{
	return nullptr;
}
