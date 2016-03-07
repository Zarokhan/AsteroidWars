#pragma once
#include "SFML\Graphics.hpp"
#include "../Ship.h"
#include "../Asteroid.h"
#include "../Projectile.h"
#include "../Window.h"
#include "GAMachine.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define ASTEROID_MAX_SPEED 12
#define ASTEROID_MIN_SPEED 10
#define ASTEROID_RESPAWN_TIME 1
#define MAX_ASTEROIDS 10
#define POPULATION_SIZE 10

class Ship;
class GAMachine;

class GASession
{
private:
	GAMachine* machine;
	std::vector<Asteroid*> asteroids;		// List of asteroids in gamescene
	std::vector<Projectile*> projectiles;	// List of projectiles in gamescene
	sf::View* camera;						// Viewport of scene, acts as a camera

	sf::Clock clock;					// Clock for spawning asteroids

	int spawnedAsteroids;

	void Init();	// Initialize method
	void Dispose();	// Dispose method

	void SpawnAsteroids();		// Spawns asteriods into the game
	void HandleProjectiles();	// Removes out of bound projectiles
	void HandleCollision();		// Handle collision for objects

	// Generates random float
	// @param max : generates float from 0 to max
	inline const float GNR_RANDOM_FLOAT(int max = 1)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	}

	// Generates random int
	// @param max : generates integer from 0 to max
	inline const int GNR_RANDOM_INT(int max)
	{
		return rand() % max;
	}

public:
	GASession() { Init(); }
	~GASession() { Dispose(); }

	void Update(float dt);
	void Draw();
	void SpawnProjectile();		// Spawns projectile into world

	// Gets all asteroid in gamesession
	std::vector<Asteroid*> GetAsteroids() const
	{
		return asteroids;
	}

	// Gets specific asteroid in gamesession by ID
	Asteroid* GetAsteroid(int ID) const;

	// Attributes
	Ship* ships[POPULATION_SIZE];							// Array of ships for test bed
};