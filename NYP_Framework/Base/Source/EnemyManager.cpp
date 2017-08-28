#include "EnemyManager.h"

#include "EnemyCuck.h"
#include "EnemyRuck.h"
#include "EnemyTuck.h"
#include "EnemyAuck.h"
#include "EnemyBuck.h"

#include "MyMath.h"
#include "Mtx44.h"
#include "SceneText.h"

EnemyManager::EnemyManager():
	active(false),
	spawningAngle(0)
{
	//initializing of the map
	std::list<EnemyEntity*> list;
	std::list<EnemyEntity*> list2;
	std::list<EnemyEntity*> list3;
	std::list<EnemyEntity*> list5;
	std::list<EnemyEntity*> list6;
	enemyMap.insert(std::make_pair("Cuck", list));
	enemyMap.insert(std::make_pair("Ruck", list2));
	enemyMap.insert(std::make_pair("Tuck", list3));
	enemyMap.insert(std::make_pair("Auck", list5));
	enemyMap.insert(std::make_pair("Buck", list6));
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
	
	//int angle = spawningAngle + spawningSize / 2;
	//int x, y;	x = y = MAX_CELLS / 2;
	////right
	//if (angle <= 45 || angle > 315) {
	//	while (x < MAX_CELLS) {
	//		BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][y];
	//		//check if tile contain nth
	//		if (tile->leftWall || tile->rightWall || tile->bottomWall || tile->topWall || tile->floor || tile->equipment) {
	//				++x;
	//		}
	//		else
	//			break;
	//	}
	//}
	//else if (angle > 45 && angle <= 135) {
	//	while (y < MAX_CELLS) {
	//		BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][y];
	//		//check if tile contain nth
	//		if (tile->leftWall || tile->rightWall || tile->bottomWall || tile->topWall || tile->floor || tile->equipment) {
	//				--y;
	//		}
	//		else
	//			break;
	//	}
	//}
	//else if (angle > 135 && angle <= 225) {
	//	//right
	//	while (x >= 0) {
	//		BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][y];
	//		//check if tile contain nth
	//		if (tile->leftWall || tile->rightWall || tile->bottomWall || tile->topWall || tile->floor || tile->equipment) {
	//				--x;
	//		}
	//		else
	//			break;
	//	}
	//}
	//else if (angle > 225 && angle <= 315) {
	//	//bottom
	//	while (y >= 0) {
	//		BuildingTile* tile = &BuildingManager::GetInstance()->GetBuildingArray()[x][y];
	//		//check if tile contain nth
	//		if (tile->leftWall || tile->rightWall || tile->bottomWall || tile->topWall || tile->floor || tile->equipment) {
	//				++y;
	//		}
	//		else
	//			break;
	//	}
	//}
	//minDistance = 5 * CELL_SIZE;
	//if (x != MAX_CELLS / 2) {
	//	minDistance += abs((x - MAX_CELLS /2) * CELL_SIZE);
	//}
	//else if (y != MAX_CELLS / 2) {
	//	minDistance += abs((y - MAX_CELLS / 2) * CELL_SIZE);
	//}
	//maxDistance = minDistance + CELL_SIZE;

	maxDistance = (MAX_CELLS / 2 - 1) * CELL_SIZE;
	minDistance = (MAX_CELLS / 2 - 2) * CELL_SIZE;
	std::cout << "max: " << maxDistance << std::endl;
	std::cout << "min: " << minDistance << std::endl;

	bool test = false;

	if (test) {
		//enemyMap["Ruck"].push_back(Create::Ruck("Ruck", Vector3(0, 0, 0)));
		//enemyMap["Cuck"].push_back(Create::Cuck("Cuck", Vector3(0, 0, 0)));
		//enemyMap["Tuck"].push_back(Create::Tuck("Tuck", Vector3(0, 0, 0)));
		//enemyMap["Auck"].push_back(Create::Auck("Auck", Vector3(0, 0, 0)));
		enemyMap["Buck"].push_back(Create::Buck("Buck", Vector3(0, 0, 0)));
		//enemyMap["Ruck"].push_back(Create::Ruck("Ruck", Vector3(0, 0, 0)));
	}
	else {
		//this is for the game itself
		//first time set up
		switch (SceneText::GetScene()->GetNoOfDays()) {
		case 1:
			for (size_t i = 0; i < 5; ++i) {
				enemyMap["Cuck"].push_back(Create::Cuck("Cuck", Vector3(0, 0, 0)));
			}
			break;
		case 2:
			for (size_t i = 0; i < 5; ++i) {
				enemyMap["Ruck"].push_back(Create::Ruck("Ruck", Vector3(0, 0, 0)));
				if (i < 3)
					enemyMap["Cuck"].push_back(Create::Cuck("Cuck", Vector3(0, 0, 0)));
			}
			break;
		case 3:
			for (size_t i = 0; i < 3; ++i) {
				enemyMap["Tuck"].push_back(Create::Tuck("Tuck", Vector3(0, 0, 0)));
			}
			break;
		case 4:
			for (size_t i = 0; i < 3; ++i) {
				enemyMap["Auck"].push_back(Create::Auck("Auck", Vector3(0, 0, 0)));
			}
			break;
		case 5:
			enemyMap["Buck"].push_back(Create::Buck("Buck", Vector3(0, 0, 0)));
			break;
		}
	}

	active = true;
}

// purpose of enemy manager is not to update enemy, but decide where and when to create them and destruct them
void EnemyManager::Update(double dt)
{
	if (active)
		SpawnEnemies();
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

EnemyEntity * EnemyManager::FetchEnemy(std::string _type)
{
	if (enemyMap.count(_type)) {
		for (auto it : enemyMap[_type]) {
			if (it->GetActive() == false)
				return it;
		}
	}
	return nullptr;
}

// to spawn enemy based on how many days
void EnemyManager::SpawnEnemies()
{
	static int i = 0;
	if (i > 30) {
		EnemyEntity* e;
		Vector3 center(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2);
		int spawnAnglePosition = Math::RandIntMinMax(0, spawningSize) + spawningAngle;
		Vector3 spawnDir(1, 0, 0);
		Mtx44 rotate;	rotate.SetToRotation(spawnAnglePosition, 0, 1, 0);
		spawnDir = rotate * spawnDir;
		if (e = FetchEnemy("Cuck")) {
			EnemyCuck*c = dynamic_cast<EnemyCuck*>(e);
			if (c) {
				c->SetPosition(center + spawnDir * Math::RandFloatMinMax(minDistance, maxDistance));
				c->Init();
			}
		}
		else if (e = FetchEnemy("Ruck")) {
			EnemyRuck*r = dynamic_cast<EnemyRuck*>(e);
			if (r) {
				r->SetPosition(center + spawnDir * Math::RandFloatMinMax(minDistance, maxDistance));
				r->Init();
			}
		}
		else if (e = FetchEnemy("Tuck")) {
			EnemyTuck*t = dynamic_cast<EnemyTuck*>(e);
			if (t) {
				t->SetPosition(center + spawnDir * Math::RandFloatMinMax(minDistance, maxDistance));
				t->Init();
			}
		}
		else if (e = FetchEnemy("Auck")) {
			EnemyAuck*a = dynamic_cast<EnemyAuck*>(e);
			if (a) {
				a->SetPosition(center + spawnDir * Math::RandFloatMinMax(minDistance, maxDistance));
				a->Init();
			}
		}
		else if (e = FetchEnemy("Buck")) {
			EnemyBuck* b = dynamic_cast<EnemyBuck*>(e);
			if (b) {
				b->SetPosition(center + spawnDir * Math::RandFloatMinMax(minDistance, maxDistance));
				b->Init();
			}
		}

		i = 0;
	}
	++i;
}

// clearing all enemies in the case of day
void EnemyManager::ClearEnemies()
{
	for (auto &it : enemyMap) {
		for (auto it2 : it.second) {
			it2->SetActive(false);
			it2->Reset();
		}
	}
}

void EnemyManager::ClearAll()
{
	enemyMap.clear();
}
