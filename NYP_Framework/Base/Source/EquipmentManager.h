#pragma once
#ifndef EQUIPMENT_MANAGER_H
#define EQUIPMENT_MANAGER_H

#define MAX_CELLS 25
#define CELL_SIZE 20

#include <list>

#include "SingletonTemplate.h"
#include "BuildingTile.h"

class EquipmentManager : public Singleton<EquipmentManager> {
	friend Singleton<EquipmentManager>;
public:
	EquipmentManager();
	virtual ~EquipmentManager();

	void AddEquipment(int _x, int _y, BuildingTile::TILE_SIDE direction, EquipmentEntity::EQUIPMENT_TYPE type);
	void AddTurret(int _x, int _y, BuildingTile::TILE_SIDE direction);
	void AddHealingStation(int _x, int _y, BuildingTile::TILE_SIDE direction);
	void AddFloorSpike(int _x, int _y, BuildingTile::TILE_SIDE direction);
	void AddShield(int _x, int _y, BuildingTile::TILE_SIDE direction);

private:
	// each cell will be 20 units by 20 units
	// a 2D array of MAXCELLS x MAXCELLS of building tiles
	BuildingTile* EquipmentArray[MAX_CELLS][MAX_CELLS];

};

#endif