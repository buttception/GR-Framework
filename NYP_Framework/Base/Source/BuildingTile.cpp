#include "BuildingTile.h"

BuildingTile::BuildingTile()
{
}

BuildingTile::~BuildingTile()
{
}

void BuildingTile::AddTile(BuildingEntity * entity, int direction)
{
	if (direction == 4) {
		if (!floor)
			floor = entity;
		else
			std::cout << "Floor already occupied";
	}
}

bool BuildingTile::RemoveTile(BuildingEntity * entity)
{
	for (int i = 0; i < 4; ++i) {
		if (wallList[i] == entity) {
			wallList[i]->SetIsDone(true);
			wallList[i] = NULL;
			return true;
		}
	}

	return false;
}
