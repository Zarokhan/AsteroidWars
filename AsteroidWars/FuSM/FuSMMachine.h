#pragma once
#include "FuSMState.h"
#include <vector>

class FuSMMachine
{
private:
	std::vector<FuSMState*> states;
	std::vector<FuSMState*> activatedStates;

public:
	FuSMMachine() {}

	virtual void UpdateMachine();
	virtual void AddState(FuSMState* state);
	virtual bool IsActive(FuSMState* state);
	virtual void Reset();
};