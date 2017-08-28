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
	PathfindStack temp;
	temp.route.push(target);
	possibleRoutes.push_back(temp);

	return NULL;

	/*
	///pathfind fail, too advanced
	//testing actual pathfinding
	//first node for route
	if (root == nullptr) {
		root = &node;
	}

	//once finish
	if (node.pos == target) {
		PathfindStack newStack;
		PathfindNode temp = node;
		while (temp.parent != nullptr) {
			newStack.route.push(temp.pos);
			newStack.totalDifficulty += temp.difficulty;
			temp = *temp.parent;
		}
		//push back a possible route that was found
		possibleRoutes.push_back(newStack);
		return NULL;
	}
	else {

		//find next node to go to
		Vector3 nextTile = FindNextTile(node.pos);

		//create the next node and assign its parent and child
		PathfindNode nextNode(nextTile);
		nextNode.parent = &node;
		//node.child = &nextNode;
		nextNode.difficulty += 1;

		//recursive the next pathfind assuming no wall
		//nextNode.child = &Pathfind(nextNode);
		//nextNode.child->parent = &nextNode;

		//pathfind recursive, assign the next node parent to curr node
		PathfindNode temp = Pathfind(nextNode);
		temp.parent = &nextNode;

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
	}
	*/
}

std::stack<Vector3> EnemyAI::GetRoute()
{
	PathfindStack lowest;
	lowest = possibleRoutes.front();
	for (auto it : possibleRoutes) {
		if (it.totalDifficulty < lowest.totalDifficulty) {
			lowest = it;
		}
	}
	optimalRoute = lowest.route;
	return lowest.route;
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

	//4 line segements in total
	//y = hitbox.GetMinAABB().y
	//y = hitbox.GetMaxAABB().y

	//x = hitbox.GetMinAABB().x
	//x = hitbox.GetMaxAABB().x
	//if the line intersects inbetween 2 of the line segments of the same axis, the collision is true

	//y = mx + c
	//x = (y - c)/m

	//checking for collision on the z plane
	//check if intersection is bigger or equals to the x front of the box
	if (gradient * hitbox.GetMinAABB().x + c >= hitbox.GetMinAABB().z) {
		//check if the intersection is smaller or equals to the x back of the box
		if ((hitbox.GetMaxAABB().z - c)/ gradient <= hitbox.GetMaxAABB().x) {
			Vector3 hitboxPos = (hitbox.GetMaxAABB() - hitbox.GetMinAABB()) * 0.5 + hitbox.GetMinAABB();
			//check if line is facing the hitbox or away
			if ((_origin - hitboxPos).Dot(dir) < 0)
				return true;
		}
	}
	//checking collision on the x plane
	if ((hitbox.GetMinAABB().z - c) / gradient >= hitbox.GetMinAABB().x) {
		if ((gradient * hitbox.GetMaxAABB().x + c <= hitbox.GetMaxAABB().z)) {
			Vector3 hitboxPos = (hitbox.GetMaxAABB() - hitbox.GetMinAABB()) * 0.5 + hitbox.GetMinAABB();
			if ((_origin - hitboxPos).Dot(dir) < 0)
				return true;
		}
	}
	if (gradient * hitbox.GetMinAABB().x + c >= hitbox.GetMinAABB().z) {
		//check if the intersection is smaller or equals to the x back of the box
		if ((gradient * hitbox.GetMaxAABB().x + c <= hitbox.GetMaxAABB().z)) {
			Vector3 hitboxPos = (hitbox.GetMaxAABB() - hitbox.GetMinAABB()) * 0.5 + hitbox.GetMinAABB();
			//check if line is facing the hitbox or away
			if ((_origin - hitboxPos).Dot(dir) < 0)
				return true;
		}
	}
	//checking collision on the x plane
	if ((hitbox.GetMinAABB().z - c) / gradient >= hitbox.GetMinAABB().x) {
		if ((hitbox.GetMaxAABB().z - c) / gradient <= hitbox.GetMaxAABB().x) {
			Vector3 hitboxPos = (hitbox.GetMaxAABB() - hitbox.GetMinAABB()) * 0.5 + hitbox.GetMinAABB();
			if ((_origin - hitboxPos).Dot(dir) < 0)
				return true;
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
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x + 1][_y]->hitbox);
	if (_x > 0)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x - 1][_y]->hitbox);
	if (_y < MAX_CELLS - 1)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x][_y + 1]->hitbox);
	if (_y > 0)
		allBoxes.push_back(BuildingManager::GetInstance()->GetBuildingArray()[_x][_y - 1]->hitbox);

	for (auto it : allBoxes) {
		// if line intersects the hitbox
		if (CheckRaytraceAABB(target, _pos, it)) {
			// push back tile position
			Vector3 pos = (it.GetMaxAABB() - it.GetMinAABB()) * 0.5 + it.GetMinAABB();
			potentialCollision.push_back(pos);
		}
	}
	
	if (potentialCollision.empty())
		return Vector3(250, 0, 250);
	else {
		float dist = (target - potentialCollision.front()).LengthSquared();
		Vector3 node = potentialCollision.front();
		for (auto it : potentialCollision) {
			// find the node that is the closest to the target
			if ((target - it).LengthSquared() < dist) {
				node = it;
			}
		}

		return node;
	}
}

PathfindNode::PathfindNode(Vector3 _pos)
{
	pos = _pos;
	parent = nullptr;
	difficulty = 0;
}

PathfindNode::~PathfindNode()
{
}

PathfindStack::PathfindStack()
{
	totalDifficulty = 0;
}

PathfindStack::~PathfindStack()
{
}
