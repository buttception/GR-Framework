#pragma once
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "BuildingManager.h"

class StateMachine {
public :
	enum STATE_TYPE {
		NONE = 0,
		ATTACK_STATE,
		FLEE_STATE,
		CHASE_STATE,
		DEFAULT_STATE
	}state;

private:
	
};

#endif