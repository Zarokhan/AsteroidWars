#include "FSMControl.h"

FSMControl::FSMControl(Ship * ship) : Control(ship)
{
	statemachine = new StateMachine<Ship>(ship);
	statemachine->SetCurrentState(IdleState::Instance());
}

void FSMControl::Update()
{
	statemachine->Update();
}
