#include "BuildingManager.h"

BuildingManager::BuildingManager()
{
	buildingArray = new BuildingTile*[MAX_CELLS];
	for (size_t i = 0; i < MAX_CELLS; ++i)
		buildingArray[i] = new BuildingTile[MAX_CELLS];
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::AddWall(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Wall placement exceeds max cell size" << std::endl;
		return;
	}

	BuildingEntity* wall = new BuildingEntity("wall");
	wall->SetHealth(100);
	wall->SetGrid(_x, _y);
	wall->SetLevel(1);
	wall->type = BuildingEntity::BUILDING_WALL;
	wall->SetCollider(true);

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		wall->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		wall->SetPosition(Vector3(_x * CELL_SIZE, wall->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		buildingArray[_x][_y].AddWall(wall, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		wall->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		wall->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE/2, wall->GetScale().y / 2, _y* CELL_SIZE));
		buildingArray[_x][_y].AddWall(wall, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		wall->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddWall(_x + 1, _y, BuildingTile::LEFT);
		else {
			wall->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, wall->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y].AddWall(wall, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		wall->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddWall(_x, _y + 1, BuildingTile::TOP);
		else {
			wall->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, wall->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			buildingArray[_x][_y].AddWall(wall, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid building direction" << std::endl;
		delete wall;
		return;
	}

	Vector3 max(wall->GetPosition().x + wall->GetScale().x / 2, 1, wall->GetPosition().z + wall->GetScale().z / 2);
	Vector3 min(wall->GetPosition().x - wall->GetScale().x / 2, 0, wall->GetPosition().z - wall->GetScale().z / 2);
	wall->SetAABB(max, min);
}
