#include "ShipFuSMStates.h"
#include "../Ship.h"
#include "../MathUtils.h"

// --- Approach

void ApproachFuSMState::Enter()
{
}

void ApproachFuSMState::Update()
{
	if (control->ship == nullptr)
		return;

	control->ship->ThrustForward(activationLevel);
	control->ship->SteerToNearestAsteroid();
}

float ApproachFuSMState::CalculateActivation()
{
	Asteroid* nearest = control->ship->nearest;
	Ship* ship = control->ship;

	if (nearest == nullptr || ship == nullptr || ship->evadepanic)
		return 0.f;

	float dist = FunMath::Distance(nearest->getPosition(), ship->getPosition());
	this->activationLevel = dist / (CAMERA_HEIGHT / 2);

	CheckBounds();
	
	return activationLevel;
}

void ApproachFuSMState::Exit()
{
}

// --- Attack

void AttackFuSMState::Enter()
{
}

void AttackFuSMState::Update()
{
	if (control->ship == nullptr)
		return;

	control->ship->Shoot();
}

float AttackFuSMState::CalculateActivation()
{
	Asteroid* nearest = control->ship->nearest;
	Ship* ship = control->ship;

	if (nearest == nullptr || ship == nullptr)
		return 0.f;

	float dist = FunMath::Distance(nearest->getPosition(), ship->getPosition());
	
	if (dist <= ASTEROID_IN_RANGE)
		this->activationLevel = dist / ASTEROID_IN_RANGE;
	else
		this->activationLevel = 0.f;

	CheckBounds();

	return activationLevel;
}

void AttackFuSMState::Exit()
{
}

// --- Evade

void EvadeFuSMState::Enter()
{
	if (control->ship == nullptr)
		return;

	control->ship->evadepanic = true;
}

void EvadeFuSMState::Update()
{
	if (control->ship == nullptr)
		return;

	control->ship->Evade();
}

float EvadeFuSMState::CalculateActivation()
{
	Asteroid* nearest = control->ship->nearest;
	Ship* ship = control->ship;

	if (nearest == nullptr || ship == nullptr)
		return 0.f;

	float dist = FunMath::Distance(nearest->getPosition(), ship->getPosition());

	if (dist <= ASTEROID_PANIC_RANGE)
		this->activationLevel = (ASTEROID_PANIC_RANGE - dist) / ASTEROID_PANIC_RANGE;
	else
		this->activationLevel = 0.f;

	CheckBounds();

	return activationLevel;
}

void EvadeFuSMState::Exit()
{
	if (control->ship == nullptr)
		return;

	control->ship->evadepanic = false;
}
