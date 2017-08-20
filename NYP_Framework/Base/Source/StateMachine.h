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
		// enemy will enter attack mode and damage its target
		ATTACK_STATE,
		// if enemy can flee, they will run to reposition themself
		FLEE_STATE,
		// if the player agro the enemy, they will chase the player
		CHASE_STATE,
		// default state, enemy will just try to destroy the generator core
		DEFAULT_STATE
	}state;

	void AddState(STATE_TYPE _state);
	bool RemoverState();

protected:
	std::stack<STATE_TYPE>stateStack;
};

#endif