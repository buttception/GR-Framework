#include "EnemyManager.h"
#include "EnemyCuck.h"
#include "MyMath.h"
#include "Mtx44.h"

EnemyManager::EnemyManager():
	active(false),
	spawningAngle(0)
{
	std::list<EnemyEntity*> list;
	std::list<EnemyEntity*> list2;
	std::list<EnemyEntity*> list3;
	std::list<EnemyEntity*> list4;
	std::list<EnemyEntity*> list5;
	std::list<EnemyEntity*> list6;
	enemyMap.insert(std::make_pair("Cuck", list));
	enemyMap.insert(std::make_pair("Ruck", list2));
	//enemyMap.insert(std::make_pair("Cuck", list3));
	//enemyMap.insert(std::make_pair("Cuck", list4));
	//enemyMap.insert(std::make_pair("Cuck", list5));
	//enemyMap.insert(std::make_pair("Cuck", list6));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// find a random angle to start spawning enemies
	spawningAngle = Math::RandIntMinMax(0, 360);
	// set the angle size
	spawningSize = Math::RandIntMinMax(40, 60);
	
	int angle = spawningAngle + spawningSize / 2;
	int x, y;	x = y = MAX_CELLS / 2;
	//right
	if (angle <= 45 || angle > 315) {
		while (x < MAX_CELLS) {
			BuildingTile tile = BuildingManager::GetInstance()->GetBuildingArray()[x][y];
			//check if tile contain nth
			if (tile.GetEmpty())
				break;
			else
				++x;
		}
	}
	else if (angle > 45 && angle <= 135) {
		while (y < MAX_CELLS) {
			BuildingTile tile = BuildingManager::GetInstance()->GetBuildingArray()[x][y];
			//check if tile contain nth
			if (tile.GetEmpty())
				break;
			else
				--y;
		}
	}
	else if (angle > 135 && angle <= 225) {
		//right
		while (x >= 0) {
			BuildingTile tile = BuildingManager::GetInstance()->GetBuildingArray()[x][y];
			//check if tile contain nth
			if (tile.GetEmpty())
				break;
			else
				--x;
		}
	}
	else if (angle > 225 && angle <= 315) {
		//bottom
		while (y >= 0) {
			BuildingTile tile = BuildingManager::GetInstance()->GetBuildingArray()[x][y];
			//check if tile contain nth
			if (tile.GetEmpty())
				break;
			else
				++y;
		}
	}
	minDistance = 3 * CELL_SIZE;
	if (x != MAX_CELLS / 2) {
		minDistance += abs((x - MAX_CELLS) * CELL_SIZE);
	}
	else if (y != MAX_CELLS / 2) {
		minDistance += abs((y - MAX_CELLS) * CELL_SIZE);
	}
	maxDistance = minDistance + CELL_SIZE;

	//first time set up
	if (enemyMap["Cuck"].empty()) {
		for (size_t i = 0; i < 20; ++i) {

		}
	}

	SpawnEnemies();

	active = true;
}

// purpose of enemy manager is not to update enemy, but decide where and when to create them and destruct them
void EnemyManager::Update(double dt)
{
}

void EnemyManager::End()
{
	ClearEnemies();

	// clear the route
	while (!route.empty())
		route.pop();

	active = false;
	spawningAngle = spawningSize = minDistance = maxDistance = 0;
}

// to spawn enemy based on how many days
void EnemyManager::SpawnEnemies()
{
	// when spawn enemy, find optimal route from spawn to core
		int spawnAnglePosition = Math::RandIntMinMax(0, spawningSize) + spawningAngle;
		Vector3 spawnDir(1, 0, 0);
		Mtx44 rotate;	rotate.SetToRotation(spawnAnglePosition, 0, 1, 0);
		spawnDir = rotate * spawnDir;

		
}

// clearing all enemies in the case of day
void EnemyManager::ClearEnemies()
{
	for (auto &it : enemyMap) {
		for (auto it2 : it.second) {
			it2->SetActive(false);
		}
	}
}
