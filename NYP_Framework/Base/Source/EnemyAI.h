#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "StateMachine.h"

//enemy ai class, incharged of switching of states and pathfinding
class EnemyAI : public StateMachine{
public:
	EnemyAI();
	~EnemyAI();

	std::stack<Vector3> Pathfind(Vector3 position);

	void PopRoute();

protected:
	std::stack<Vector3>pathfindingStack;
};

#endif