#include "BuildingTile.h"
#include "EntityManager.h"

#include "Sound_Engine.h"
#include "PlayerInfo\PlayerInfo.h"


BuildingTile::BuildingTile()
	: leftWall(nullptr)
	, rightWall(nullptr)
	, bottomWall(nullptr)
	, topWall(nullptr)

	, leftDoor(nullptr)
	, rightDoor(nullptr)
	, bottomDoor(nullptr)
	, topDoor(nullptr)

	, leftCover(nullptr)
	, rightCover(nullptr)
	, bottomCover(nullptr)
	, topCover(nullptr)

	, leftFloor(nullptr)
	, rightFloor(nullptr)
	, bottomFloor(nullptr)
	, topFloor(nullptr)

	, leftTurret(nullptr)
	, rightTurret(nullptr)
	, bottomTurret(nullptr)
	, topTurret(nullptr)

	, leftHealingStation(nullptr)
	, rightHealingStation(nullptr)
	, bottomHealingStation(nullptr)
	, topHealingStation(nullptr)

	, leftFloorSpike(nullptr)
	, rightFloorSpike(nullptr)
	, bottomFloorSpike(nullptr)
	, topFloorSpike(nullptr)

	, leftShield(nullptr)
	, rightShield(nullptr)
	, bottomShield(nullptr)
	, topShield(nullptr)
{
}

BuildingTile::~BuildingTile()
{
}

void BuildingTile::AddWall(BuildingEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftWall) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftWall = entity;
		break;
	case TOP:
		if (topWall) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topWall = entity;
		break;
	case RIGHT:
		if (rightWall) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightWall = entity;
		break;
	case BOTTOM:
		if (bottomWall) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomWall = entity;
		break;
	default:
		return;
	}
	std::cout << "Wall placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 150));
	EntityManager::GetInstance()->AddEntity(entity);
	CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddDoor(BuildingEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftDoor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftDoor = entity;
		break;
	case TOP:
		if (topDoor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topDoor = entity;
		break;
	case RIGHT:
		if (rightDoor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightDoor = entity;
		break;
	case BOTTOM:
		if (bottomDoor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomDoor = entity;
		break;
	default:
		return;
	}
	std::cout << "Door placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 100));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddCover(BuildingEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftCover) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftCover = entity;
		break;
	case TOP:
		if (topCover) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topCover = entity;
		break;
	case RIGHT:
		if (rightCover) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightCover = entity;
		break;
	case BOTTOM:
		if (bottomCover) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomCover = entity;
		break;
	default:
		return;
	}
	std::cout << "Cover placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 200));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddFloor(BuildingEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftFloor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftFloor = entity;
		break;
	case TOP:
		if (topFloor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topFloor = entity;
		break;
	case RIGHT:
		if (rightFloor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightFloor = entity;
		break;
	case BOTTOM:
		if (bottomFloor) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomFloor = entity;
		break;
	default:
		return;
	}
	std::cout << "Floor placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 50));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}

bool BuildingTile::RemoveBuilding(BuildingEntity * entity)
{
	

	return false;
}

void BuildingTile::AddTurret(EquipmentEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftTurret) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftTurret = entity;
		break;
	case TOP:
		if (topTurret) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topTurret = entity;
		break;
	case RIGHT:
		if (rightTurret) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightTurret = entity;
		break;
	case BOTTOM:
		if (bottomTurret) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomTurret = entity;
		break;
	default:
		return;
	}
	std::cout << "Turret placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 250));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddHealingStation(EquipmentEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftHealingStation) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftHealingStation = entity;
		break;
	case TOP:
		if (topHealingStation) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topHealingStation = entity;
		break;
	case RIGHT:
		if (rightHealingStation) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightHealingStation = entity;
		break;
	case BOTTOM:
		if (bottomHealingStation) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomHealingStation = entity;
		break;
	default:
		return;
	}
	std::cout << "Healing Station placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 250));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddFloorSpike(EquipmentEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftFloorSpike) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftFloorSpike = entity;
		break;
	case TOP:
		if (topFloorSpike) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topFloorSpike = entity;
		break;
	case RIGHT:
		if (rightFloorSpike) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightFloorSpike = entity;
		break;
	case BOTTOM:
		if (bottomFloorSpike) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomFloorSpike = entity;
		break;
	default:
		return;
	}
	std::cout << "Floor Spike placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 250));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddShield(EquipmentEntity * entity, TILE_SIDE direction)
{
	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	switch (direction) {
	case LEFT:
		if (leftShield) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		leftShield = entity;
		break;
	case TOP:
		if (topShield) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		topShield = entity;
		break;
	case RIGHT:
		if (rightShield) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		rightShield = entity;
		break;
	case BOTTOM:
		if (bottomShield) {
			std::cout << "Position occupied" << std::endl;
			return;
		}
		bottomShield = entity;
		break;
	default:
		return;
	}
	std::cout << "Shield placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 250));
	EntityManager::GetInstance()->AddEntity(entity);
	//CSoundEngine::GetInstance()->playthesound("Build", 0.4);
	//std::cout << "Buld sound Played" << std::endl;
}
