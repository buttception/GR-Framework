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

void BuildingManager::AddBuilding(int _x, int _y, BuildingTile::TILE_SIDE direction, BuildingEntity::BUILDING_TYPE type)
{
	switch (type)
	{
	case BuildingEntity::BUILDING_WALL:
		AddWall(_x, _y, direction);
		break;
	case BuildingEntity::BUILDING_DOOR:
		AddDoor(_x, _y, direction);
		break;
	case BuildingEntity::BUILDING_COVER:
		AddCover(_x, _y, direction);
		break;
	case BuildingEntity::BUILDING_FLOOR:
		AddFloor(_x, _y, direction);
		break;
	}
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
		buildingArray[_x][_y]->AddWall(wall, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		wall->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		wall->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE/2, wall->GetScale().y / 2, _y* CELL_SIZE));
		buildingArray[_x][_y]->AddWall(wall, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		wall->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddWall(_x + 1, _y, BuildingTile::LEFT);
		else {
			wall->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, wall->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y]->AddWall(wall, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		wall->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddWall(_x, _y + 1, BuildingTile::TOP);
		else {
			wall->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, wall->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			buildingArray[_x][_y]->AddWall(wall, BuildingTile::BOTTOM);
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

void BuildingManager::AddDoor(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Door placement exceeds max cell size" << std::endl;
		return;
	}

	BuildingEntity* door = new BuildingEntity("door");
	door->SetHealth(50);
	door->SetGrid(_x, _y);
	door->SetLevel(1);
	door->type = BuildingEntity::BUILDING_DOOR;
	door->SetCollider(true);

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		door->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		door->SetPosition(Vector3(_x * CELL_SIZE, door->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		buildingArray[_x][_y]->AddDoor(door, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		door->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		door->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, door->GetScale().y / 2, _y* CELL_SIZE));
		buildingArray[_x][_y]->AddDoor(door, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		door->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddDoor(_x + 1, _y, BuildingTile::LEFT);
		else {
			door->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, door->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y]->AddDoor(door, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		door->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddDoor(_x, _y + 1, BuildingTile::TOP);
		else {
			door->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, door->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			buildingArray[_x][_y]->AddDoor(door, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid building direction" << std::endl;
		delete door;
		return;
	}

	Vector3 max(door->GetPosition().x + door->GetScale().x / 2, 1, door->GetPosition().z + door->GetScale().z / 2);
	Vector3 min(door->GetPosition().x - door->GetScale().x / 2, 0, door->GetPosition().z - door->GetScale().z / 2);
	door->SetAABB(max, min);
}

void BuildingManager::AddCover(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Cover placement exceeds max cell size" << std::endl;
		return;
	}

	BuildingEntity* cover = new BuildingEntity("cover");
	cover->SetHealth(50);
	cover->SetGrid(_x, _y);
	cover->SetLevel(1);
	cover->type = BuildingEntity::BUILDING_COVER;
	cover->SetCollider(true);

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		cover->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		cover->SetPosition(Vector3(_x * CELL_SIZE, cover->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		buildingArray[_x][_y]->AddCover(cover, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		cover->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		cover->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, cover->GetScale().y / 2, _y* CELL_SIZE));
		buildingArray[_x][_y]->AddCover(cover, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		cover->SetScale(Vector3(2, 10, CELL_SIZE + 2));
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddCover(_x + 1, _y, BuildingTile::LEFT);
		else {
			cover->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, cover->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y]->AddCover(cover, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		cover->SetScale(Vector3(CELL_SIZE + 2, 10, 2));
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddCover(_x, _y + 1, BuildingTile::TOP);
		else {
			cover->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, cover->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			buildingArray[_x][_y]->AddCover(cover, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid building direction" << std::endl;
		delete cover;
		return;
	}

	Vector3 max(cover->GetPosition().x + cover->GetScale().x / 2, 1, cover->GetPosition().z + cover->GetScale().z / 2);
	Vector3 min(cover->GetPosition().x - cover->GetScale().x / 2, 0, cover->GetPosition().z - cover->GetScale().z / 2);
	cover->SetAABB(max, min);
}

void BuildingManager::AddFloor(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Floor placement exceeds max cell size" << std::endl;
		return;
	}

	BuildingEntity* floor = new BuildingEntity("floor");
	floor->SetHealth(50);
	floor->SetGrid(_x, _y);
	floor->SetLevel(1);
	floor->type = BuildingEntity::BUILDING_FLOOR;
	floor->SetCollider(false);
	floor->SetScale(Vector3(CELL_SIZE + 2, 2, CELL_SIZE + 2));

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		floor->SetPosition(Vector3(_x * CELL_SIZE - CELL_SIZE / 2, floor->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		buildingArray[_x][_y]->AddFloor(floor, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		floor->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, floor->GetScale().y / 2, _y * CELL_SIZE - CELL_SIZE / 2));
		buildingArray[_x][_y]->AddFloor(floor, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddFloor(_x + 2, _y, BuildingTile::LEFT);
		else {
			floor->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, floor->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			buildingArray[_x][_y]->AddFloor(floor, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddFloor(_x, _y + 2, BuildingTile::TOP);
		else {
			floor->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, floor->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			buildingArray[_x][_y]->AddFloor(floor, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid building direction" << std::endl;
		delete floor;
		return;
	}
}

