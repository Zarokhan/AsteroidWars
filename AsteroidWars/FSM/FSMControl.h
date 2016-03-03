#pragma once
#include "../Control.h"
#include "StateMachine.h"

class FSMControl : public Control
{
private:
	StateMachine<Ship>* statemachine;

public:
	FSMControl(Ship* ship = NULL);

	StateMachine<Ship>* GetFSM() const { return statemachine; }
	virtual void Update() override;

};