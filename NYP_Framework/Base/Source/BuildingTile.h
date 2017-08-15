#pragma once
#ifndef BUILDING_TILE_H
#define BUILDING_TILE_H

#include <vector>

#include "BuildingEntity.h"

class BuildingTile {
public:
	BuildingTile();
	virtual ~BuildingTile();

	void AddTile(BuildingEntity* entity, int direction);
	bool RemoveTile(BuildingEntity* entity);

private:
	BuildingEntity* wallList[4];
	BuildingEntity* floor;
};

#endif