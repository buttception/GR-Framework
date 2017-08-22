#include "EnemyAI.h"
#include "BuildingManager.h"

EnemyAI::EnemyAI()
		:root(nullptr)
{
	target = Vector3(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2);
}

EnemyAI::~EnemyAI()
{
}

// parameter position is the position of the enemy
PathfindNode EnemyAI::Pathfind(PathfindNode &node)
{
	// temp pathfinding for now, need to use something like crash and turn to find optimal route
	//target = Vector3(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2);
	//pathfindingStack.push(target);

	//return this->pathfindingStack;

	//testing actual pathfinding
	//first node for route
	if (root == nullptr) {
		root = &node;
	}

	//once finish
	if (node.pos == target) {
		PathfindNode temp = *root;
		while (temp.child != nullptr) {
			pathfindingStack.push_front(temp.pos);
			temp = *temp.child;
		}
		return temp;
	}
	else {

		//find next node to go to
		Vector3 nextTile = FindNextTile(node.pos);

		PathfindNode nextNode(nextTile);
		nextNode.parent = &node;
		node.child = &nextNode;

		nextNode.child = &Pathfind(nextNode);

		return nextNode;

		/*
		//find the dir to the nextile
		Vector3 dir = nextTile - node.pos;
		// 1 = top left, 2 = top, 3 = top right, 4 = right
		// 5 = bottom right, 6 = bottom, 7 = bottom left, 8 = left
		int side = 0;
		if (dir.x < 0) {
			//means that they moving to the left
			if (dir.y == 0)
				side = 8;
			else if (dir.y > 0)
				side = 1;
			else if (dir.y < 0)
				side = 7;
		}
		else if (dir.x > 0) {
			//means that they moving to the right
			if (dir.y == 0)
				side = 4;
			else if (dir.y > 0)
				side = 3;
			else if (dir.y < 0)
				side = 5;
		}
		else if (dir.x == 0) {
			if (dir.y < 0)
				side = 6;
			else if (dir.y > 0)
				side = 2;
		}
		//check if way is blocked
		switch (side) {
		case 1:	//top left
			Pathfind(nextTile);
			break;
		case 2:	//top
			Pathfind(nextTile);
			break;
		case 3: //top right
			Pathfind(nextTile);
			break;
		case 4:	//right
			Pathfind(nextTile);
			break;
		case 5:	//bottom right
			Pathfind(nextTile);
			break;
		case 6:	//bottom
			Pathfind(nextTile);
			break;
		case 7:	//bottom left
			Pathfind(nextTile);
			break;
		case 8:	//left
			Pathfind(nextTile);
			break;
		}
		*/
	}
}

std::stack<Vector3> EnemyAI::GetRoute()
{
	std::stack<Vector3>route;
	for (auto it : pathfindingStack) {
		route.push(it);
	}
	return route;
}

void EnemyAI::PopRoute()
{
	if (pathfindingStack.empty()) {
		std::cout << "AI had reached destination\n";
		return;
	}
	else
		pathfindingStack.pop_back();
}

void EnemyAI::AddNode(PathfindNode * node)
{

}

bool EnemyAI::CheckRaytraceAABB(Vector3 _end, Vector3 _origin, Collision hitbox)
{
	//Vector3 dir = -_line.Normalized();
	//if (hitbox.HasAABB()) {
	//	float t1 = (hitbox.GetMinAABB().x - _origin.x)*dir.x;
	//	float t2 = (hitbox.GetMaxAABB().x - _origin.x)*dir.x;
	//	float t3 = (hitbox.GetMinAABB().y - _origin.y)*dir.y;
	//	float t4 = (hitbox.GetMaxAABB().y - _origin.y)*dir.y;
	//	float t5 = (hitbox.GetMinAABB().z - _origin.z)*dir.z;
	//	float t6 = (hitbox.GetMaxAABB().z - _origin.z)*dir.z;

	//	float tmin = Math::Max(Math::Max(Math::Min(t1, t2), Math::Min(t3, t4)), Math::Min(t5, t6));
	//	float tmax = Math::Min(Math::Min(Math::Max(t1, t2), Math::Max(t3, t4)), Math::Max(t5, t6));

	//	float t = 0;
	//	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	//	if (tmax < 0)
	//	{
	//		t = tmax;
	//		return false;
	//	}

	//	// if tmin > tmax, ray doesn't intersect AABB
	//	if (tmin > tmax)
	//	{
	//		t = tmax;
	//		return false;
	//	}

	//	t = tmin;
	//	return true;
	//}
	//else {
	//	std::cout << "No hitbox in CheckRaytraceAABB" << std::endl;
	//	return false;
	//}
	
	Vector3 dir = _end - _origin;
	dir.Normalize();

	float gradient = dir.z / dir.x;
	float c = _end.z - _end.x * gradient;

	//check min
	//if intersection point is greater or equals to min
	if (gradient * hitbox.GetMinAABB().x + c >= hitbox.GetMinAABB().z) {
		if ((hitbox.GetMinAABB().z - c) / gradient >= hitbox.GetMinAABB().x) {
			//check if intersection is smaller or equals to min
			if (gradient * hitbox.GetMaxAABB() + c <= hitbox.GetMaxAABB().z) {
				if ((hitbox.GetMaxAABB().z - c) / gradient <= hitbox.GetMaxAABB().x) {
					Vector3 hitboxPos = (hitbox.GetMaxAABB() - hitbox.GetMinAABB()) * 0.5 + hitbox.GetMinAABB();
					if ((_origin - hitboxPos).Dot(dir) < 0)
						return true; 
				}
			}
		}
	}
	return false;
}

// parameter _pos is the position of the central node
Vector3 EnemyAI::FindNextTile(Vector3 _pos)
{
	std::list<Vector3> potentialCollision;
	std::list<Collision> allBoxes;

	// find current grid position
	int _x, _y;
	_x = (int)_pos.x / CELL_SIZE;
	_y = (int)_pos.z / CELL_SIZE;

	//all boxes around the enemy
	if (_x < MAX_CELLS - 1)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x + 1][_y].hitbox);
	if (_x > 0)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x - 1][_y].hitbox);
	if (_y < MAX_CELLS - 1)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x][_y + 1].hitbox);
	if (_y > 0)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x][_y - 1].hitbox);
	if (_x < MAX_CELLS - 1 && _y < MAX_CELLS - 1)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x + 1][_y + 1].hitbox);
	if (_x > 0 && _y < MAX_CELLS - 1)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x - 1][_y + 1].hitbox);
	if (_x < MAX_CELLS - 1 && _y > 0)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x + 1][_y - 1].hitbox);
	if (_x > 0 && _y > 0)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x - 1][_y - 1].hitbox);

	for (auto it : allBoxes) {
		// if line intersects the hitbox
		if (CheckRaytraceAABB(target, _pos, it)) {
			// push back tile position
			Vector3 pos = (it.GetMaxAABB() - it.GetMinAABB()) * 0.5 + it.GetMinAABB();
			potentialCollision.push_back(pos);
		}
	}

	float dist = -1;
	Vector3 node;
	for (auto it : potentialCollision) {
		// find the node that is the closest to the target
		if ((target - it).LengthSquared() > dist) {
			node = it;
		}
	}

	return node;
}

PathfindNode::PathfindNode(Vector3 _pos)
{
	pos = _pos;
	child = sibling = parent = nullptr;
}

PathfindNode::~PathfindNode()
{
}