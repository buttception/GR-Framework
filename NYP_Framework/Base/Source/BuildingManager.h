#pragma once
#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#define MAX_CELLS 50
#define CELL_SIZE 20

#include <list>

#include "SingletonTemplate.h"
#include "BuildingEntity.h"

class BuildingManager : Singleton<BuildingManager> {
	friend Singleton<BuildingManager>;
public:
	BuildingManager();
	virtual ~BuildingManager();

	void AddBuilding(BuildingEntity* _add);
	bool RemoveBuilding(BuildingEntity* _remove);

private:
	// each cell will be 20 units by 20 units
	std::list<BuildingEntity*> buildingArray[MAX_CELLS][MAX_CELLS];
};

#endif