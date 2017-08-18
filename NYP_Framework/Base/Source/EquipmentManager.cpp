#include "EquipmentManager.h"

EquipmentManager::EquipmentManager()
{
	for (int i = 0; i < MAX_CELLS; ++i) {
		for (int j = 0; j < MAX_CELLS; ++j) {
			EquipmentArray[i][j] = new BuildingTile();
		}
	}
}

EquipmentManager::~EquipmentManager()
{
}

void EquipmentManager::AddEquipment(int _x, int _y, BuildingTile::TILE_SIDE direction, EquipmentEntity::EQUIPMENT_TYPE type)
{
	switch (type)
	{
	case EquipmentEntity::EQUIPMENT_TURRET:
		AddTurret(_x, _y, direction);
		break;
	case EquipmentEntity::EQUIPMENT_HEALING_STATION:
		AddHealingStation(_x, _y, direction);
		break;
	case EquipmentEntity::EQUIPMENT_FLOOR_SPIKE:
		AddFloorSpike(_x, _y, direction);
		break;
	case EquipmentEntity::EQUIPMENT_SHIELD:
		AddShield(_x, _y, direction);
		break;
	}
}

void EquipmentManager::AddTurret(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Turret placement exceeds max cell size" << std::endl;
		return;
	}

	EquipmentEntity* Turret = new EquipmentEntity("Turret");
	Turret->SetHealth(50);
	Turret->SetGrid(_x, _y);
	Turret->SetLevel(1);
	Turret->type = EquipmentEntity::EQUIPMENT_TURRET;
	Turret->SetCollider(true);
	Turret->SetScale(Vector3(CELL_SIZE, 10, CELL_SIZE));

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		Turret->SetPosition(Vector3(_x * CELL_SIZE - CELL_SIZE / 2, Turret->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddTurret(Turret, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		Turret->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, Turret->GetScale().y / 2, _y * CELL_SIZE - CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddTurret(Turret, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddTurret(_x + 2, _y, BuildingTile::LEFT);
		else {
			Turret->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, Turret->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			EquipmentArray[_x][_y]->AddTurret(Turret, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddTurret(_x, _y + 2, BuildingTile::TOP);
		else {
			Turret->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, Turret->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			EquipmentArray[_x][_y]->AddTurret(Turret, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid Equipment direction" << std::endl;
		delete Turret;
		return;
	}

	Vector3 max(Turret->GetPosition().x + Turret->GetScale().x / 2, 1, Turret->GetPosition().z + Turret->GetScale().z / 2);
	Vector3 min(Turret->GetPosition().x - Turret->GetScale().x / 2, 0, Turret->GetPosition().z - Turret->GetScale().z / 2);
	Turret->SetAABB(max, min);
}

void EquipmentManager::AddHealingStation(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Healing Station placement exceeds max cell size" << std::endl;
		return;
	}

	EquipmentEntity* HealingStation = new EquipmentEntity("Healing Station");
	HealingStation->SetHealth(50);
	HealingStation->SetGrid(_x, _y);
	HealingStation->SetLevel(1);
	HealingStation->type = EquipmentEntity::EQUIPMENT_HEALING_STATION;
	HealingStation->SetCollider(true);
	HealingStation->SetScale(Vector3(CELL_SIZE, 10, CELL_SIZE));

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		HealingStation->SetPosition(Vector3(_x * CELL_SIZE - CELL_SIZE / 2, HealingStation->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddHealingStation(HealingStation, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		HealingStation->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, HealingStation->GetScale().y / 2, _y * CELL_SIZE - CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddHealingStation(HealingStation, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddHealingStation(_x + 2, _y, BuildingTile::LEFT);
		else {
			HealingStation->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, HealingStation->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			EquipmentArray[_x][_y]->AddHealingStation(HealingStation, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddHealingStation(_x, _y + 2, BuildingTile::TOP);
		else {
			HealingStation->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, HealingStation->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			EquipmentArray[_x][_y]->AddHealingStation(HealingStation, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid Equipment direction" << std::endl;
		delete HealingStation;
		return;
	}

	Vector3 max(HealingStation->GetPosition().x + HealingStation->GetScale().x / 2, 1, HealingStation->GetPosition().z + HealingStation->GetScale().z / 2);
	Vector3 min(HealingStation->GetPosition().x - HealingStation->GetScale().x / 2, 0, HealingStation->GetPosition().z - HealingStation->GetScale().z / 2);
	HealingStation->SetAABB(max, min);
}

void EquipmentManager::AddFloorSpike(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Floor Spike placement exceeds max cell size" << std::endl;
		return;
	}

	EquipmentEntity* FloorSpike = new EquipmentEntity("Floor Spike");
	FloorSpike->SetHealth(50);
	FloorSpike->SetGrid(_x, _y);
	FloorSpike->SetLevel(1);
	FloorSpike->type = EquipmentEntity::EQUIPMENT_FLOOR_SPIKE;
	FloorSpike->SetCollider(true);
	FloorSpike->SetScale(Vector3(CELL_SIZE, 10, CELL_SIZE));

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		FloorSpike->SetPosition(Vector3(_x * CELL_SIZE - CELL_SIZE / 2, FloorSpike->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddFloorSpike(FloorSpike, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		FloorSpike->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, FloorSpike->GetScale().y / 2, _y * CELL_SIZE - CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddFloorSpike(FloorSpike, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddFloorSpike(_x + 2, _y, BuildingTile::LEFT);
		else {
			FloorSpike->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, FloorSpike->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			EquipmentArray[_x][_y]->AddFloorSpike(FloorSpike, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddFloorSpike(_x, _y + 2, BuildingTile::TOP);
		else {
			FloorSpike->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, FloorSpike->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			EquipmentArray[_x][_y]->AddFloorSpike(FloorSpike, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid Equipment direction" << std::endl;
		delete FloorSpike;
		return;
	}

	Vector3 max(FloorSpike->GetPosition().x + FloorSpike->GetScale().x / 2, 1, FloorSpike->GetPosition().z + FloorSpike->GetScale().z / 2);
	Vector3 min(FloorSpike->GetPosition().x - FloorSpike->GetScale().x / 2, 0, FloorSpike->GetPosition().z - FloorSpike->GetScale().z / 2);
	FloorSpike->SetAABB(max, min);
}

void EquipmentManager::AddShield(int _x, int _y, BuildingTile::TILE_SIDE direction)
{
	// where _x and _y is 0 to 49
	if (_x >= MAX_CELLS || _y >= MAX_CELLS || _x < 0 || _y < 0) {
		std::cout << "Shield placement exceeds max cell size" << std::endl;
		return;
	}

	EquipmentEntity* Shield = new EquipmentEntity("Shield");
	Shield->SetHealth(50);
	Shield->SetGrid(_x, _y);
	Shield->SetLevel(1);
	Shield->type = EquipmentEntity::EQUIPMENT_SHIELD;
	Shield->SetCollider(true);
	Shield->SetScale(Vector3(CELL_SIZE, 10, CELL_SIZE));

	//where 1 -> left, 2 -> top, 3 -> right, 4 ->bottom
	if (direction == BuildingTile::LEFT) {
		Shield->SetPosition(Vector3(_x * CELL_SIZE - CELL_SIZE / 2, Shield->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddShield(Shield, BuildingTile::LEFT);
	}
	else if (direction == BuildingTile::TOP) {
		Shield->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, Shield->GetScale().y / 2, _y * CELL_SIZE - CELL_SIZE / 2));
		EquipmentArray[_x][_y]->AddShield(Shield, BuildingTile::TOP);
	}
	else if (direction == BuildingTile::RIGHT) {
		//if it is on the right, which is the next tile set unless is end
		if (_x + 1 != MAX_CELLS)
			AddShield(_x + 2, _y, BuildingTile::LEFT);
		else {
			Shield->SetPosition(Vector3(MAX_CELLS * CELL_SIZE, Shield->GetScale().y / 2, _y * CELL_SIZE + CELL_SIZE / 2));
			EquipmentArray[_x][_y]->AddShield(Shield, BuildingTile::RIGHT);
		}
	}
	else if (direction == BuildingTile::BOTTOM) {
		//if it is on the bottom, which is the bottom tile set unless is end
		if (_y >= 0)
			AddShield(_x, _y + 2, BuildingTile::TOP);
		else {
			Shield->SetPosition(Vector3(_x * CELL_SIZE + CELL_SIZE / 2, Shield->GetScale().y / 2, MAX_CELLS * CELL_SIZE));
			EquipmentArray[_x][_y]->AddShield(Shield, BuildingTile::BOTTOM);
		}
	}
	else {
		std::cout << "Invalid Equipment direction" << std::endl;
		delete Shield;
		return;
	}

	Vector3 max(Shield->GetPosition().x + Shield->GetScale().x / 2, 1, Shield->GetPosition().z + Shield->GetScale().z / 2);
	Vector3 min(Shield->GetPosition().x - Shield->GetScale().x / 2, 0, Shield->GetPosition().z - Shield->GetScale().z / 2);
	Shield->SetAABB(max, min);
}
