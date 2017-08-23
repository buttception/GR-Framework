#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "StateMachine.h"

// node struct for pathfinding
struct PathfindNode {
	PathfindNode(Vector3);
	~PathfindNode();

	Vector3 pos;

	int difficulty;

	PathfindNode* parent;
	PathfindNode* child;
	PathfindNode* sibling;
};

//struct for each route to keep track of the total difficulty
struct PathfindStack {
	PathfindStack();
	~PathfindStack();

	int totalDifficulty;
	std::stack<Vector3>route;
};

//enemy ai class, incharged of switching of states and pathfinding
class EnemyAI : public StateMachine{
public:
	EnemyAI();
	~EnemyAI();

	PathfindNode Pathfind(PathfindNode &node);

	std::stack<Vector3>GetRoute();

	bool CheckRaytraceAABB(Vector3 _end, Vector3 origin, Collision hitbox);
	Vector3 FindNextTile(Vector3 _pos);

protected:
	std::vector<PathfindStack>possibleRoutes;
	std::stack<Vector3>optimalRoute;
	PathfindNode* root;
	Vector3 target;
};

#endif