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
	void AddDoor(BuildingEntity* entity, TILE_SIDE direction);
	void AddCover(BuildingEntity* entity, TILE_SIDE direction);
	void AddFloor(BuildingEntity* entity, TILE_SIDE direction);
	bool RemoveBuilding(BuildingEntity* entity);

	void AddTurret(EquipmentEntity* entity, TILE_SIDE direction);
	void AddHealingStation(EquipmentEntity* entity, TILE_SIDE direction);
	void AddFloorSpike(EquipmentEntity* entity, TILE_SIDE direction);
	void AddShield(EquipmentEntity* entity, TILE_SIDE direction);

private:
	BuildingEntity* leftWall;
	BuildingEntity* rightWall;
	BuildingEntity* bottomWall;
	BuildingEntity* topWall;

	BuildingEntity* leftDoor;
	BuildingEntity* rightDoor;
	BuildingEntity* bottomDoor;
	BuildingEntity* topDoor;

	BuildingEntity* leftCover;
	BuildingEntity* rightCover;
	BuildingEntity* bottomCover;
	BuildingEntity* topCover;

	BuildingEntity* leftFloor;
	BuildingEntity* rightFloor;
	BuildingEntity* bottomFloor;
	BuildingEntity* topFloor;

	EquipmentEntity* leftTurret;
	EquipmentEntity* rightTurret;
	EquipmentEntity* bottomTurret;
	EquipmentEntity* topTurret;

	EquipmentEntity* leftHealingStation;
	EquipmentEntity* rightHealingStation;
	EquipmentEntity* bottomHealingStation;
	EquipmentEntity* topHealingStation;

	EquipmentEntity* leftFloorSpike;
	EquipmentEntity* rightFloorSpike;
	EquipmentEntity* bottomFloorSpike;
	EquipmentEntity* topFloorSpike;

	EquipmentEntity* leftShield;
	EquipmentEntity* rightShield;
	EquipmentEntity* bottomShield;
	EquipmentEntity* topShield;
};

#endif