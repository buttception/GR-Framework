#pragma once
#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#define MAX_CELLS 25
#define CELL_SIZE 20

#include <list>

#include "SingletonTemplate.h"
#include "BuildingTile.h"

class BuildingManager : public Singleton<BuildingManager> {
	friend Singleton<BuildingManager>;
public:
	BuildingManager();
	virtual ~BuildingManager();

	void AddBuilding(int _x, int _y, BuildingTile::TILE_SIDE direction, BuildingEntity::BUILDING_TYPE type);
	void AddWall(int _x, int _y, BuildingTile::TILE_SIDE direction);
	void AddDoor(int _x, int _y, BuildingTile::TILE_SIDE direction);
	void AddCover(int _x, int _y, BuildingTile::TILE_SIDE direction);
	void AddFloor(int _x, int _y, BuildingTile::TILE_SIDE direction);

private:
	// each cell will be 20 units by 20 units
	// a 2D array of MAXCELLS x MAXCELLS of building tiles
	BuildingTile* buildingArray[MAX_CELLS][MAX_CELLS];
	
};

#endif