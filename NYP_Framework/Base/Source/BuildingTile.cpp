#include "BuildingTile.h"
#include "EntityManager.h"

BuildingTile::BuildingTile()
	:leftWall(nullptr)
	,rightWall(nullptr)
	,topWall(nullptr)
	,bottomWall(nullptr)
	,floor(nullptr)
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
	std::cout << "wall placed down" << std::endl;

	EntityManager::GetInstance()->AddEntity(entity);
}

bool BuildingTile::RemoveBuilding(BuildingEntity * entity)
{
	

	return false;
}
