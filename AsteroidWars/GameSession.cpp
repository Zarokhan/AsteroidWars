#include "GameSession.h"
#include <iostream>

GameSession::GameSession()
{
	Init();
}

void GameSession::Init()
{
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	
	ship = new Ship(this);
	ship->setPosition(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f));
	//ship->control = new FSMControl(ship);
	control = new FuSMControl(ship);

	curr = sf::Time::Zero;
	limit = sf::seconds(1.f);
	std::srand(std::time(0));

	spawnedAsteroids = 0;
}

void GameSession::Update(float delta)
{
	ship->Update(delta);

	if (control != nullptr)
		control->Update();

	for (int i = 0; i < asteroids.size(); i++)
		asteroids[i]->Update(delta);

	for (int i = 0; i < projectiles.size(); i++)
		projectiles[i]->Update(delta);

	SpawnAsteroids();
	HandleProjectiles();
	HandleCollision();
}

void GameSession::HandleCollision()
{
	// Handle projectile asteroids collision
	for (int i = 0; i < asteroids.size(); i++)
	{
		for (int j = 0; j < projectiles.size(); j++)
		{
			bool intersects = asteroids[i]->getGlobalBounds().intersects(projectiles[j]->getGlobalBounds());
			if (intersects)
			{
				asteroids.erase(asteroids.begin() + i);
				projectiles.erase(projectiles.begin() + j);
			}
		}
	}
	// Handle ship asteroids collision;
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i]->getGlobalBounds().intersects(ship->getGlobalBounds()))
		{
			Dispose();
			Init();
			return;
		}
	}
}

void GameSession::HandleProjectiles()
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->IsDead())
		{
			projectiles.erase(projectiles.begin() + i);
		}
	}
}

void GameSession::SpawnProjectile()
{
	Projectile* p = new Projectile(ship->getPosition(), ship->GetDirection());
	projectiles.push_back(p);
}

void GameSession::SpawnAsteroids()
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

void GameSession::Draw(sf::RenderWindow* const window)
{
	window->setView(*camera);

	// Draws asteriods
	for (int i = 0; i < asteroids.size(); i++)
		window->draw(*asteroids[i]);

	for (int i = 0; i < projectiles.size(); i++)
		window->draw(*projectiles[i]);

	window->draw(*ship);
}

void GameSession::Dispose()
{
	for (int i = 0; i < asteroids.size(); i++)
		asteroids.erase(asteroids.begin() + i);

	for (int i = 0; i < projectiles.size(); i++)
		projectiles.erase(projectiles.begin() + i);

	asteroids.clear();
	projectiles.clear();

	delete control;
	delete camera;
	delete ship;
}

GameSession::~GameSession()
{
	Dispose();
}

Asteroid* GameSession::GetAsteroid(int ID) const
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i]->GetID() == ID)
			return asteroids[i];
	}
	return nullptr;
}