#include "ShipOwnedStates.h"
#include <iostream>

// IdleState
IdleState* IdleState::Instance()
{
	static IdleState instance;

	return &instance;
}

void IdleState::Enter(Ship* ship)
{
	std::cout << "Idle" << std::endl;
}

void IdleState::Execute(Ship* ship)
{
	// If there is no asteroids
	if (ship->GetSession()->GetAsteroids().size() == 0)
		return;

	FSMControl* ctrl = (FSMControl*)ship->control;

	// Check if we need to evade
	if (ship->NeedToEvade())
		ctrl->GetFSM()->ChangeState(EvadeState::Instance());
	// Check if nearest asteroid is in range
	else if (ship->nearest_asteroid_distance < ASTEROID_IN_RANGE)
		ctrl->GetFSM()->ChangeState(AttackState::Instance());
	else // Approach to get in range
		ctrl->GetFSM()->ChangeState(ApproachState::Instance());

}

void IdleState::Exit(Ship* ship)
{

}

// ApproachState
ApproachState* ApproachState::Instance()
{
	static ApproachState instance;

	return &instance;
}

void ApproachState::Enter(Ship* ship)
{
	std::cout << "Approach" << std::endl;
}

void ApproachState::Execute(Ship* ship)
{
	FSMControl* ctrl = (FSMControl*)ship->control;

	// Check if we need to evade
	if (ship->NeedToEvade())
		ctrl->GetFSM()->ChangeState(EvadeState::Instance());

	// Approach nearest asteroid
	ship->SteerToNearestAsteroid();

	if (ship->nearest_asteroid_distance < ASTEROID_IN_RANGE)
		ctrl->GetFSM()->ChangeState(IdleState::Instance());
	else
		ship->ThrustForward();
}

void ApproachState::Exit(Ship* ship)
{

}

// EvadeState
EvadeState* EvadeState::Instance()
{
	static EvadeState instance;

	return &instance;
}

void EvadeState::Enter(Ship* ship)
{
	std::cout << "Evade" << std::endl;
}

void EvadeState::Execute(Ship* ship)
{
	FSMControl* ctrl = (FSMControl*)ship->control;

	if (ship->nearest_asteroid_distance > ASTEROID_PANIC_RANGE)
		ctrl->GetFSM()->ChangeState(IdleState::Instance());

	ship->Evade();
}

void EvadeState::Exit(Ship* ship)
{

}

// AttackState
AttackState* AttackState::Instance()
{
	static AttackState instance;

	return &instance;
}

void AttackState::Enter(Ship* ship)
{
	std::cout << "Attack" << std::endl;
}

void AttackState::Execute(Ship* ship)
{
	FSMControl* ctrl = (FSMControl*)ship->control;

	// Check if we need to evade
	if (ship->NeedToEvade())
		ctrl->GetFSM()->ChangeState(EvadeState::Instance());

	if (ship->nearest_asteroid_distance > ASTEROID_IN_RANGE)
		ctrl->GetFSM()->ChangeState(IdleState::Instance());
	else
	{
		ship->SteerToNearestAsteroid();
		ship->Shoot();
	}
}

void AttackState::Exit(Ship* ship)
{

}