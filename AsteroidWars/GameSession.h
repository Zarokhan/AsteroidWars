#pragma once
#include "SFML\Graphics.hpp"
#include "Ship.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "FuSMControl.h"
#include "FSMControl.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define ASTEROID_MAX_SPEED 12
#define ASTEROID_MIN_SPEED 10
#define ASTEROID_RESPAWN_TIME 1
#define MAX_ASTEROIDS 10

class Ship;

class GameSession
{
private:
	Ship* ship;								//
	FuSMControl* control;
	std::vector<Asteroid*> asteroids;		//
	std::vector<Projectile*> projectiles;	//
	sf::View* camera;						// Viewport of screen, acts as a camera

	sf::Clock clock;					// Clock for asteroids
	sf::Time curr;		
	sf::Time limit;	 
	
	int spawnedAsteroids;

	void Init();	// Initialize method
	void Dispose();	// Dispose method

	void SpawnAsteroids();		// Spawns asteriods into the game
	void HandleProjectiles();	// Removes out of bound projectiles
	void HandleCollision();		// Handle collision for objects

	// Generates random float
	// @param max : generates float from 0 to max
	inline const float GNR_RANDOM_FLOAT(int max)
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
	GameSession();
	~GameSession();
	void Update(float delta);
	void Draw(sf::RenderWindow* const window);
	void SpawnProjectile();		// Spawns projectile into world

	std::vector<Asteroid*> GetAsteroids() const
	{
		return asteroids;
	}

	Asteroid* GetAsteroid(int ID) const;
};