#include "GASession.h"

void GASession::Init()
{
	camera = new sf::View(sf::Vector2f(CAMERA_WIDTH / 2.f, CAMERA_HEIGHT / 2.f), sf::Vector2f(CAMERA_WIDTH, CAMERA_HEIGHT));
	std::srand(std::time(0));	// Sets seed for random numbers

	font.loadFromFile("../Assets/font.ttf");

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
	for (int i = 0; i < asteroids.size(); i++)
		delete asteroids.at(i);
	for (int i = 0; i < projectiles.size(); i++)
		delete projectiles.at(i);
	delete camera;
}

void GASession::Restart()
{
	for (int i = 0; i < asteroids.size(); i++)
		delete asteroids.at(i);
	asteroids.clear();

	for (int i = 0; i < POPULATION_SIZE; i++)
		delete ships[i];
	ships[POPULATION_SIZE];
	// Initialize all ships
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		Ship *ship = new Ship(this);
		ship->SetGASession(this);
		ship->setPosition(sf::Vector2f(GNR_RANDOM_INT(CAMERA_WIDTH), GNR_RANDOM_INT(CAMERA_HEIGHT)));
		ships[i] = ship;
	}

	spawnedAsteroids = 0;
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
	// Handle ship asteroids collision;
	for (int i = 0; i < asteroids.size(); i++)
	{
		for (int j = 0; j < POPULATION_SIZE; j++)
		{
			if (!ships[j]->active)
				continue;

			if (asteroids[i]->getGlobalBounds().intersects(ships[j]->getGlobalBounds()))
				ships[j]->active = false;
		}
	}
}

void GASession::Update(float dt)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	//	pressed = true;
	//else if (pressed)
	//{
	//	pressed = false;
	//	paused = !paused;
	//}

	if (paused)
		return;

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
	HandleCollision();
}

void GASession::Draw()
{
	Window->setView(*camera);

	for (int i = 0; i < asteroids.size(); i++)
		Window->draw(*asteroids[i]);

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (ships[i]->active)
			Window->draw(*ships[i]);
	}

	if (paused)
	{
		sf::Text text("Paused", font, 60);
		text.setPosition(sf::Vector2f((CAMERA_WIDTH - text.getLocalBounds().width)/2, (CAMERA_HEIGHT - text.getLocalBounds().height) / 2));
		Window->draw(text);
	}
}

void GASession::DrawInformation()
{
	for (int i = 0; i < 15; i++)
	{
		std::string string = "";

		switch (i)
		{
		case 0:
			string = "Generations " + Utils::ToString<int>(machine->generations);
			break;
		case 1:
			string = "LiveCount " + Utils::ToString<int>(machine->liveCount);
			break;
		case 2:
			string = "Asteroids " + Utils::ToString<int>(spawnedAsteroids);
			break;
		case 3:
			string = "TotalFitness " + Utils::ToString<float>(machine->totalFitness);
			break;
		case 4:
			string = "BestFitness " + Utils::ToString<float>(machine->bestFitness);
			break;
		case 5:
			string = "CrossoverRate " + Utils::ToString<float>(machine->crossoverRate);
			break;
		case 6:
			string = "MutationRate " + Utils::ToString<float>(machine->mutationRate);
			break;
		case 7:
			string = "OffsetSize " + Utils::ToString<float>(machine->offsetSize);
			break;
		case 8:
			string = "Elitism " + Utils::ToString<bool>(machine->elitism);
			break;
		case 10:
			string = "Generation " + Utils::ToString<float>(machine->singleGeneration);
			break;
		case 11:
			string = "Best single score " + Utils::ToString<float>(machine->bestFitnessGeneration);
			break;
		case 13:
			string = "Generation " + Utils::ToString<float>(machine->totalGeneration);
			break;
		case 14:
			string = "Best total score " + Utils::ToString<float>(machine->bestTotalFitnessGeneration);
			break;
		}

		sf::Text text(string, font, 25);
		text.setPosition(sf::Vector2f(0, 30 * i));
		DebugWindow->draw(text);
	}
}

void GASession::SpawnProjectile()
{
}

Asteroid * GASession::GetAsteroid(int ID) const
{
	return nullptr;
}
