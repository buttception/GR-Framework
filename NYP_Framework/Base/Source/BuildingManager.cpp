#include "BuildingManager.h"

BuildingManager::BuildingManager()
{
	for (int i = 0; i < MAX_CELLS; ++i) {
		for (int j = 0; j < MAX_CELLS; ++j) {
			buildingArray[i][j] = new BuildingTile();
		}
	}
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::AddWall(int _x, int _y, int direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Wall placement exceeds max cell size" << std::endl;
		return;
	}

	BuildingEntity* wall = new BuildingEntity("wall");
	wall->SetScale(Vector3(20, 1, 2));
	wall->SetHealth(100);
	wall->SetGrid(_x, _y);
	wall->SetLevel(1);
	wall->type = BuildingEntity::BUILDING_WALL;
	wall->SetCollider(true);

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction >= 1 && direction <= 2) {
		//if it is left or top, just add the wall
		if (direction == 1) {
			wall->SetScale(Vector3(2, 5, 20));
			wall->SetPosition(Vector3(_x * CELL_SIZE, wall->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y]->AddWall(wall, 1);
		}
		if (direction == 2) {
			wall->SetScale(Vector3(20, 5, 2));
			wall->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE/2, wall->GetScale().y / 2, _y* CELL_SIZE));
			buildingArray[_x][_y]->AddWall(wall, 2);
		}
	}
	else if (direction == 3) {
		wall->SetScale(Vector3(2, 5, 20));
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddWall(_x + 1, _y, 1);
		else {
			wall->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, wall->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y]->AddWall(wall, 3);
		}
	}
	else if (direction == 4) {
		wall->SetScale(Vector3(20, 5, 2));
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddWall(_x, _y + 1, 2);
		else {
			wall->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, wall->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			buildingArray[_x][_y]->AddWall(wall, 4);
		}
	}
	else {
		std::cout << "Invalid building direction" << std::endl;
		delete wall;
		return;
	}

	if (direction == 1 || direction == 3) {
		Vector3 max(wall->GetPosition().x + wall->GetScale().x / 2, 1, wall->GetPosition().z + wall->GetScale().z / 2);
		Vector3 min(wall->GetPosition().x - wall->GetScale().x / 2, 1, wall->GetPosition().z - wall->GetScale().z / 2);
		wall->SetAABB(max, min);
	}
		
	if (direction == 2 || direction == 4) {
		Vector3 max(wall->GetPosition().z + wall->GetScale().z / 2, 1, wall->GetPosition().x + wall->GetScale().x / 2);
		Vector3 min(wall->GetPosition().z - wall->GetScale().z / 2, 1, wall->GetPosition().x - wall->GetScale().x / 2);
		wall->SetAABB(max, min);
	}
}

