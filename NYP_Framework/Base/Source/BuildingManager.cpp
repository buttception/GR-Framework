#include "BuildingManager.h"

BuildingManager::BuildingManager()
{
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::CreateBuilding(BuildingEntity::BUILDING_TYPE type, Vector3 pos)
{
	BuildingEntity* b = Create::Building(type, pos);
	AddBuilding(b);
}

void BuildingManager::AddBuilding(BuildingEntity * _add)
{
	//decides which tile to put it into
	int x = _add->GetPosition().x / CELL_SIZE;
	int y = _add->GetPosition().z / CELL_SIZE;

	if (x < 0 || x >= MAX_CELLS || y < 0 || y >= MAX_CELLS) {
		std::cout << "Object is outside the map" << std::endl;
		return;
	}

	//only put wall at the top and left
	float cellPosX = CELL_SIZE * (x - 1) + CELL_SIZE / 2;
	float cellPosY = CELL_SIZE * (y - 1) + CELL_SIZE / 2;

	bool right;
	bool left;
	bool top;
	bool bottom;
	right = bottom = top = left = false;
	
	//logic fucking wrong
	if (_add->GetPosition().x > cellPosX) {
		if (x + 1 > MAX_CELLS - 1)
			right = true;
		else {
			x += 1;
			left = true;
		}
	}
	else if (_add->GetPosition().z < cellPosY) {
		if (y + 1 > MAX_CELLS - 1)
			bottom = true;
		else {
			y += 1;
			top = true;
		}
	}
	if (_add->GetPosition().x < cellPosX) {
		left = true;
	}
	else if (_add->GetPosition().z > cellPosY) {
		top = true;
	}

	// left = 0
	// top =  1
	// right = 2
	// bottom = 3
	
}

bool BuildingManager::RemoveBuilding(BuildingEntity * _remove)
{
	return false;
}
