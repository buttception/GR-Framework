#include "BuildingTile.h"
#include "EntityManager.h"

#include "Sound_Engine.h"
#include "PlayerInfo\PlayerInfo.h"


BuildingTile::BuildingTile()
	: leftWall(nullptr)
	, rightWall(nullptr)
	, bottomWall(nullptr)
	, topWall(nullptr)

	, floor(nullptr)
	, equipment(nullptr)
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
	if (entity->type == BuildingEntity::BUILDING_COVER)
		std::cout << "Cover placed down" << std::endl;
	Player::GetInstance()->SetMaterial(Math::Max(0, Player::GetInstance()->GetMaterial() - 150));
	EntityManager::GetInstance()->AddEntity(entity);
	CSoundEngine::GetInstance()->playthesound("Build", 0.4f);
	std::cout << "Buld sound Played" << std::endl;
}

void BuildingTile::AddFloor(BuildingEntity * entity)
{
	if (floor) {
		std::cout << "Floor position occupied\n";
		return;
	}
	if (entity->type != BuildingEntity::BUILDING_FLOOR)
		return;
	floor = entity;
	EntityManager::GetInstance()->AddEntity(floor);
	CSoundEngine::GetInstance()->playthesound("Floor", 0.4f);
}

bool BuildingTile::RemoveBuilding(BuildingEntity * entity)
{
	

	return false;
}

void BuildingTile::AddEquipment(EquipmentEntity * entity)
{
	if (equipment) {
		std::cout << "Equipment slot is occupied\n";
		return;
	}
	equipment = entity;
	EntityManager::GetInstance()->AddEntity(equipment);
}
