#pragma once
#include "../Ship.h"
#include "State.h"
#include "Control.h"
#include "FSMControl.h"

class Ship;

class IdleState : public State<Ship>
{
private:
	IdleState() {}

	// Copy constructor should be private
	IdleState(const IdleState&);
	IdleState& operator=(const IdleState&);

public:
	static IdleState* Instance();	// Singleton

	virtual void Enter(Ship* ship) override;
	virtual void Execute(Ship* ship) override;
	virtual void Exit(Ship* ship) override;
};

class ApproachState : public State<Ship>
{
private:
	ApproachState() {}

	// Copy constructor should be private
	ApproachState(const ApproachState&);
	ApproachState& operator=(const ApproachState&);

public:
	static ApproachState* Instance();	// Singleton

	virtual void Enter(Ship* ship) override;
	virtual void Execute(Ship* ship) override;
	virtual void Exit(Ship* ship) override;
};

class EvadeState : public State<Ship>
{
private:
	EvadeState() {}

	// Copy constructor should be private
	EvadeState(const EvadeState&);
	EvadeState& operator=(const EvadeState&);

public:
	static EvadeState* Instance();	// Singleton

	virtual void Enter(Ship* ship) override;
	virtual void Execute(Ship* ship) override;
	virtual void Exit(Ship* ship) override;
};

class AttackState : public State<Ship>
{
private:
	AttackState() {}

	// Copy constructor should be private
	AttackState(const AttackState&);
	AttackState& operator=(const AttackState&);

public:
	static AttackState* Instance();	// Singleton

	virtual void Enter(Ship* ship) override;
	virtual void Execute(Ship* ship) override;
	virtual void Exit(Ship* ship) override;
};