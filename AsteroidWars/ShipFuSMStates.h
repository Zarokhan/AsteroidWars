#pragma once
#include "FuSMState.h"
#include "FuSMControl.h"

class ApproachFuSMState : public FuSMState
{
private:
	FuSMControl* control;

public:
	ApproachFuSMState(FuSMControl* control) { this->control = control; }

	virtual void Enter() override;
	virtual void Update() override;
	virtual float CalculateActivation() override;
	virtual void Exit() override;
};

class AttackFuSMState : public FuSMState
{
private:
	FuSMControl* control;

public:
	AttackFuSMState(FuSMControl* control) { this->control = control; }

	virtual void Enter() override;
	virtual void Update() override;
	virtual float CalculateActivation() override;
	virtual void Exit() override;
};

class EvadeFuSMState : public FuSMState
{
private:
	FuSMControl* control;

public:
	EvadeFuSMState(FuSMControl* control) { this->control = control; }

	virtual void Enter() override;
	virtual void Update() override;
	virtual float CalculateActivation() override;
	virtual void Exit() override;
};