#pragma once
#ifndef BUILDING_TILE_H
#define BUILDING_TILE_H

#include <vector>

#include "BuildingEntity.h"
#include "EquipmentEntity.h"

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
	void AddFloor(BuildingEntity* entity);
	bool RemoveBuilding(BuildingEntity* entity);
	
	void AddEquipment(EquipmentEntity* entity);

	BuildingEntity* leftWall;
	BuildingEntity* rightWall;
	BuildingEntity* bottomWall;
	BuildingEntity* topWall;
	BuildingEntity* floor;

private:
	EquipmentEntity* equipment;

};

#endif