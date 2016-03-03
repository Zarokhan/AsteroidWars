#pragma once
#include "State.h"

template <class entity>
class StateMachine
{
private:
	entity* m_owner;			// Owner entity
	State<entity>* m_current;
	State<entity>* m_previous;
	State<entity>* m_global;

public:
	StateMachine(entity* owner) : 
		m_owner(owner),
		m_current(NULL),
		m_previous(NULL),
		m_global(NULL)
	{}

	virtual ~StateMachine() {}

	void SetCurrentState(State<entity>* s) { m_current = s; }
	void SetPreviousState(State<entity>* s) { m_previous = s; }
	void SetGlobalState(State<entity>* s) { m_global = s; }

	void Update() const
	{
		// Execute global state if it exists
		if (m_global)
			m_global->Execute(m_owner);
		// The same for current state
		if (m_current)
			m_current->Execute(m_owner);
	}

	void ChangeState(State<entity>* s)
	{
		m_previous = m_current;		// Keep record of previous state
		m_current->Exit(m_owner);	// Calls exit method
		m_current = s;				// Set new state
		m_current->Enter(m_owner);	// Enter new state
	}

	// Reverst to previous state
	void RevertState()
	{
		ChangeState(m_previous);
	}

	// Returns true if current state is equal to param s state
	bool IsInState(const State<entity>& s) const
	{
		return typeid(*m_current) == typeid(s);
	}
};