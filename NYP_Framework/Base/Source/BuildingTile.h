#pragma once
#ifndef BUILDING_TILE_H
#define BUILDING_TILE_H

#include <vector>

#include "BuildingEntity.h"

class BuildingTile {
public:
	BuildingTile();
	virtual ~BuildingTile();

	void AddWall(BuildingEntity* entity, int direction);
	bool RemoveBuilding(BuildingEntity* entity);

private:
	BuildingEntity* leftWall;
	BuildingEntity* rightWall;
	BuildingEntity* bottomWall;
	BuildingEntity* topWall;
	BuildingEntity* floor;
};

#endif