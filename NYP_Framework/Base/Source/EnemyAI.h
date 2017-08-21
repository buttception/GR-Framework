#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "StateMachine.h"

// node struct for pathfinding
struct PathfindNode {
	PathfindNode(Vector3);
	~PathfindNode();

	Vector3 pos;

	PathfindNode* parent;
	PathfindNode* child;
	PathfindNode* sibling;
};

//enemy ai class, incharged of switching of states and pathfinding
class EnemyAI : public StateMachine{
public:
	EnemyAI();
	~EnemyAI();

	PathfindNode Pathfind(PathfindNode &node);

	std::stack<Vector3>GetRoute();
	void PopRoute();

	void AddNode(PathfindNode* node);

	bool CheckRaytraceAABB(Vector3 _end, Vector3 origin, Collision hitbox);
	Vector3 FindNextTile(Vector3 _pos);

protected:
	std::deque<Vector3>pathfindingStack;
	PathfindNode* root;
	Vector3 target;
};

#endif