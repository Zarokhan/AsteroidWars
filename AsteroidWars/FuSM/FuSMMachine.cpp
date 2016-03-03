#include "FuSMMachine.h"

void FuSMMachine::UpdateMachine()
{
	// Return if we have no states
	if (states.size() == 0)
		return;

	// Check for activated states
	activatedStates.clear();
	std::vector<FuSMState*> nonActiveStates;
	for (int i = 0; i < states.size(); i++)
	{
		if (states[i]->CalculateActivation() > 0)
			activatedStates.push_back(states[i]);
		else
			nonActiveStates.push_back(states[i]);
	}

	// Exit all non active states
	for (int i = 0; i < nonActiveStates.size(); i++)
		nonActiveStates[i]->Exit();

	// Update all active states
	for (int i = 0; i < activatedStates.size(); i++)
		activatedStates[i]->Update();
}

void FuSMMachine::AddState(FuSMState* state)
{
	states.push_back(state);
}

bool FuSMMachine::IsActive(FuSMState* state)
{
	{
		for (int i = 0; i < activatedStates.size(); i++)
			if (activatedStates[i] == state)
				return true;
	}
	return false;
}

void FuSMMachine::Reset()
{
	for (int i = 0; i < states.size(); i++)
	{
		states[i]->Exit();
		states[i]->Init();
	}
}