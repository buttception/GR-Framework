#include "EnemyAI.h"
#include "BuildingManager.h"

EnemyAI::EnemyAI()
{
}

EnemyAI::~EnemyAI()
{
}

// parameter position is the position of the enemy
std::stack<Vector3> EnemyAI::Pathfind(Vector3 position)
{
	// temp pathfinding for now, need to use something like crash and turn to find optimal route
	Vector3 corePosition(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2);
	pathfindingStack.push(corePosition);

	return this->pathfindingStack;
}

void EnemyAI::PopRoute()
{
	if (pathfindingStack.empty()) {
		std::cout << "AI had reached destination\n";
		return;
	}
	else
		pathfindingStack.pop();
}
