#include "StateMachine.h"

StateMachine::StateMachine()
{
	// initialize state machine with default state
	stateStack.push(NONE);
}

StateMachine::~StateMachine()
{
}

void StateMachine::AddState(STATE_TYPE _state)
{
	if (stateStack.top() != _state)
		stateStack.push(_state);
}

bool StateMachine::RemoverState()
{
	if (stateStack.size() <= 1){
		std::cout << "State stack is left with only one stack, cannot remove state\n";
		return false;
	}
	else {
		stateStack.pop();
		return true;
	}
}
