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
