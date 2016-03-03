#include "FuSMControl.h"
#include "ShipFuSMStates.h"

FuSMControl::FuSMControl(Ship * ship)
{
	this->ship = ship;
	machine = new FuSMMachine();
	machine->AddState(new ApproachFuSMState(this));
	machine->AddState(new AttackFuSMState(this));
	machine->AddState(new EvadeFuSMState(this));
	machine->Reset();
}

void FuSMControl::Init()
{

}

void FuSMControl::Update()
{
	if (!ship)
	{
		machine->Reset();
		return;
	}

	UpdatePerceptions();
	machine->UpdateMachine();
}


void FuSMControl::UpdatePerceptions()
{
}
