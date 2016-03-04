#pragma once
#include "GameObject.h"
#include "FSM/ShipOwnedStates.h"
#include "GameSession.h"
#include "GA\GASession.h"
#include "Asteroid.h"
#include "Control.h"
#include <cmath>

#define START_SPEED 12
#define START_ROTATION_SPEED 4
#define STEER_PERCEPTION_DEGREES 5
#define SHOOT_PERCEPTION_DEGREES 30
#define RELOAD_TIME 0.2
#define ASTEROID_IN_RANGE 400
#define ASTEROID_PANIC_RANGE 250

class GameSession;
class GASession;
class Control;

class Ship : public GameObject
{
private:
	GameSession* parent;
	GASession* session;
	sf::Clock reload;
	float rotation;

	Ship(const Ship&);
	Ship() : GameObject("../Images/SpaceShip.png") {};

	void CheckNearestAsteroid();

protected:
	virtual void OutOfBounds() override;
	virtual void Movement() override;
	void AdjustRotation();

public:
	Ship(GameSession* p);
	Ship(GASession* p);
	~Ship();
	virtual void Update(float delta) override;
	
	GameSession* GetSession() const { return parent; }
	Control* control;
	
	void KeyboardInput();

	void SteerRight(const float& val);
	void ThrustForward(float val = 1.f);
	void ThrustBackward(float val = 1.f);

	bool NeedToEvade();
	void Evade();
	void Shoot();
	void SteerToNearestAsteroid();

	float nearest_asteroid_distance;
	bool lineofsight;	// of nearest asteroid
	bool evadepanic;
	bool active;		// GA only, if ship is active
	Asteroid* nearest;
};