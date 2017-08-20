#pragma once
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <stack>

#include "BuildingManager.h"

// statemachine class with just a stack of the states the enemy has
class StateMachine {
public :
	StateMachine();
	virtual ~StateMachine();

	enum STATE_TYPE {
		NONE = 0,
		ATTACK_STATE,
		FLEE_STATE,
		CHASE_STATE,
		DEFAULT_STATE
	}state;

	void AddState(STATE_TYPE _state);
	bool RemoverState();

protected:
	std::stack<STATE_TYPE>stateStack;
};

#endif