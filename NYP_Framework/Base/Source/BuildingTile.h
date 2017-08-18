#pragma once
#ifndef BUILDING_TILE_H
#define BUILDING_TILE_H

#include <vector>

#include "BuildingEntity.h"

class BuildingTile {
public:
	BuildingTile();
	virtual ~BuildingTile();

	enum TILE_SIDE {
		NONE = 0,
		LEFT,
		TOP, 
		RIGHT,
		BOTTOM
	}side;

	void AddWall(BuildingEntity* entity, TILE_SIDE direction);
	bool RemoveBuilding(BuildingEntity* entity);

	BuildingEntity* leftWall;
	BuildingEntity* rightWall;
	BuildingEntity* bottomWall;
	BuildingEntity* topWall;

private:
	BuildingEntity* floor;
};

#endif