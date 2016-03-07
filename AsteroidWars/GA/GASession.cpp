#include "GASession.h"

void GASession::Init()
{
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	std::srand(std::time(0));	// Sets seed for random numbers

	// Initialize all ships
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		Ship *ship = new Ship(this);
		ship->SetGASession(this);
		ship->setPosition(sf::Vector2f(GNR_RANDOM_INT(CAMERA_WIDTH), GNR_RANDOM_INT(CAMERA_HEIGHT)));
		ships[i] = ship;
	}

	machine = new GAMachine(new GAAIControl(this));
	machine->Session = this;
	machine->CreateStartPopulation();

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
	if (clock.getElapsedTime().asSeconds() >= ASTEROID_RESPAWN_TIME && asteroids.size() < MAX_ASTEROIDS)
	{
		// Random rotation
		float random = GNR_RANDOM_FLOAT(2);
		random -= 1.f;
		// Random speed
		float speed = std::abs(random) * ASTEROID_MAX_SPEED;
		if (speed < ASTEROID_MIN_SPEED)
			speed = ASTEROID_MIN_SPEED;
		// Random spawn
		sf::Vector2f pos;
		int spawn = GNR_RANDOM_INT(6000);
		if (spawn <= CAMERA_WIDTH) // TOP
		{
			pos.x = spawn;
			pos.y = 0;
		}
		else if (spawn <= CAMERA_WIDTH + CAMERA_HEIGHT)	// LEFT
		{
			spawn -= CAMERA_WIDTH;
			pos.y = spawn;
			pos.x = CAMERA_WIDTH;
		}
		else if (spawn <= (CAMERA_WIDTH * 2) + CAMERA_HEIGHT) // BOTTOM
		{
			spawn -= CAMERA_WIDTH + CAMERA_HEIGHT;
			pos.x = CAMERA_WIDTH - spawn;
			pos.y = CAMERA_HEIGHT;
		}
		else // RIGHT
		{
			spawn -= (CAMERA_WIDTH * 2) + CAMERA_HEIGHT;
			pos.y = CAMERA_HEIGHT - spawn;
			pos.x = 0;
		}
		// Random direction
		sf::Vector2f dir;
		dir.x = GNR_RANDOM_FLOAT(2);
		dir.x -= 1.f;
		dir.y = GNR_RANDOM_FLOAT(2);
		dir.y -= 1.f;
		// Create asteroid
		Asteroid* a = new Asteroid(spawnedAsteroids, random, speed, pos, dir);
		asteroids.push_back(a);
		clock.restart();

		spawnedAsteroids++;
	}
}

void GASession::HandleProjectiles()
{
}

void GASession::HandleCollision()
{
}

void GASession::Update(float dt)
{
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (ships[i] == NULL)
			continue;
		ships[i]->Update(dt);
	}

	machine->Update(dt);

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update(dt);

	SpawnAsteroids();
}

void GASession::Draw()
{
	Window->setView(*camera);

	for (int i = 0; i < asteroids.size(); i++)
		Window->draw(*asteroids[i]);

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
