#include "BuildingManager.h"

BuildingManager::BuildingManager()
{
	// new all the buildingtiles
	buildingArray = new BuildingTile*[MAX_CELLS];
	for (size_t i = 0; i < MAX_CELLS; ++i)
		buildingArray[i] = new BuildingTile[MAX_CELLS];

	for (size_t i = 0; i < MAX_CELLS; ++i) {
		for (size_t j = 0; j < MAX_CELLS; ++j) {
			Vector3 max(((float)i + 1.f) * CELL_SIZE, 1, ((float)j + 1.f) * CELL_SIZE);
			Vector3 min((float)i * CELL_SIZE, - 1.f, (float)j * CELL_SIZE);
			buildingArray[i][j].hitbox.SetAABB(max, min);
		}
	}
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::AddBuilding(int _x, int _y, BuildingTile::TILE_SIDE direction, BuildingEntity::BUILDING_TYPE type)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Wall placement exceeds max cell size" << std::endl;
		return;
	}

	BuildingEntity* wall;
	if (type != BuildingEntity::BUILDING_FLOOR)
		wall = new BuildingEntity("wall");
	else
		wall = new BuildingEntity("floor");
	wall->SetHealth(100);
	wall->SetGrid(_x, _y);
	wall->SetLevel(1);
	wall->objectType = GenericEntity::BUILDING;
	wall->type = type;

	if (type != BuildingEntity::BUILDING_FLOOR) {
		//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
		if (direction == BuildingTile::LEFT) {
			wall->SetScale(Vector3(2, 10, CELL_SIZE));
			wall->SetPosition(Vector3((float)_x * CELL_SIZE, wall->GetScale().y / 2.f, (float)_y * CELL_SIZE + CELL_SIZE / 2.f));
			buildingArray[_x][_y].AddWall(wall, BuildingTile::LEFT);
		}
		else if (direction == BuildingTile::TOP) {
			wall->SetScale(Vector3(CELL_SIZE, 10, 2));
			wall->SetPosition(Vector3((float)_x * CELL_SIZE + CELL_SIZE / 2.f, wall->GetScale().y / 2.f, (float)_y * CELL_SIZE));
			buildingArray[_x][_y].AddWall(wall, BuildingTile::TOP);
		}
		else if (direction == BuildingTile::RIGHT) {
			wall->SetScale(Vector3(2, 10, CELL_SIZE));
			//if it is on the right, which is the next tile set unless is end
			if (_x + 1 != MAX_CELLS)
				AddBuilding(_x + 1, _y, BuildingTile::LEFT, type);
			else {
				wall->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, wall->GetScale().y / 2.f, (float)_y * CELL_SIZE + CELL_SIZE / 2.f));
				buildingArray[_x][_y].AddWall(wall, BuildingTile::RIGHT);
			}
		}
		else if (direction == BuildingTile::BOTTOM) {
			wall->SetScale(Vector3(CELL_SIZE, 10, 2));
			//if it is on the bottom, which is the bottom tile set unless is end
			if (_y >= 0)
				AddBuilding(_x, _y + 1, BuildingTile::TOP, type);
			else {
				wall->SetPosition(Vector3((float)_x * CELL_SIZE + CELL_SIZE / 2.f, wall->GetScale().y / 2.f, MAX_CELLS * CELL_SIZE));
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
	else {
		wall->SetScale(Vector3(CELL_SIZE, 1.f, CELL_SIZE));
		wall->SetPosition(Vector3((float)_x * CELL_SIZE + CELL_SIZE / 2.f, 0.1f, (float)_y * CELL_SIZE + CELL_SIZE / 2.f));
		buildingArray[_x][_y].AddFloor(wall);
	}
}

void BuildingManager::AddEquipment(int _x, int _y, EquipmentEntity::EQUIPMENT_TYPE _type)
{
	if (buildingArray[_x][_y].floor) {
		EquipmentEntity* e;
		switch (_type) {
		case EquipmentEntity::EQUIPMENT_FLOOR_SPIKE:
			e = new EquipmentEntity("Floor Spike");
			break;
		case EquipmentEntity::EQUIPMENT_HEALING_STATION:
			e = new EquipmentEntity("Healing Station");
			break;
		case EquipmentEntity::EQUIPMENT_SHIELD:
			e = new EquipmentEntity("Shield");
			break;
		case EquipmentEntity::EQUIPMENT_TURRET:
			e = new EquipmentEntity("Turret");
			break;
		}
		e->type = _type;
		e->objectType = GenericEntity::EQUIPMENT;
		e->SetScale(Vector3(CELL_SIZE, 1.f, CELL_SIZE));
		e->SetPosition(Vector3((float)_x * CELL_SIZE + CELL_SIZE / 2.f, 0.1f, (float)_y * CELL_SIZE + CELL_SIZE / 2.f));
		Vector3 max(e->GetPosition().x + e->GetScale().x / 2, 1, e->GetPosition().z + e->GetScale().z / 2);
		Vector3 min(e->GetPosition().x - e->GetScale().x / 2, 0, e->GetPosition().z - e->GetScale().z / 2);
		e->SetAABB(max, min);
		buildingArray[_x][_y].AddEquipment(e);
	}
	else
		std::cout << "No floor to place equipment on\n";
}
