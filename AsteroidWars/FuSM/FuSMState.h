#pragma once

class FuSMState
{
protected:
	float activationLevel;

public:
	FuSMState() { activationLevel = 0.f; }

	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Init() { activationLevel = 0.f; }
	virtual float CalculateActivation() { return activationLevel; }

	virtual void CheckLowerBound(float lbound = 0.f) { if (activationLevel < lbound) activationLevel = lbound; }
	virtual void CheckUpperBound(float ubound = 1.f) { if (activationLevel > ubound) activationLevel = ubound; }
	virtual void CheckBounds(float lb = 0.f, float ub = 1.f) { CheckLowerBound(lb); CheckUpperBound(ub); }
};