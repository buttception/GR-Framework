#include "EnemyCuck.h"
#include "MeshList.h"

EnemyCuck::EnemyCuck(std::string _meshName, Vector3 position) : EnemyEntity(_meshName)
{
	this->position = position;
	state = StateMachine::DEFAULT_STATE;
}

EnemyCuck::~EnemyCuck()
{
}

void EnemyCuck::Init()
{
	speed = 10;
	health = 100;
	damage = 10;
	direction = (pathfindingStack.top()- position).Normalized();
}

void EnemyCuck::Update(double dt)
{
	switch (state) {
	case StateMachine::DEFAULT_STATE:
		// if enemy reached a node
		if (position == pathfindingStack.top()) {
			// pop the stack
			PopRoute();
			// find new direction to next node
			direction = (pathfindingStack.top() - position).Normalized();
		}
		position += direction * speed * dt;
		break;
	default:
		return;
	}
}

EnemyCuck * Create::Cuck(std::string _meshName, Vector3 position)
{
	EnemyCuck* cuck = new EnemyCuck(_meshName, position);
	EntityManager::GetInstance()->AddEntity(cuck);
	return cuck;
}
