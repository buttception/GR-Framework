#include "EnemyManager.h"
#include "EnemyCuck.h"
#include "MyMath.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// resets the enemy count
	for (auto &it : enemyCount) {
		it.second = 0;
	}
	// find a random angle to start spawning enemies
	spawningAngle = Math::RandIntMinMax(0, 360);

	SpawnEnemies();
}

// purpose of enemy manager is not to update enemy, but decide where and when to create them and destruct them
void EnemyManager::Update(double dt, std::list<EntityBase*> entityList)
{
}

// to spawn enemy based on how many days
void EnemyManager::SpawnEnemies()
{
	// when spawn enemy, find optimal route from spawn to core
	if (route.empty()) {
		EnemyEntity* first = Create::Cuck("Cuck", Vector3(300, 0, 250));
		// only need to calculate one optimal route thus saving the stack
		route = first->Pathfind(first->GetPosition());
		// init the enemy
		first->Init();
	}
	else {

	}

}

// clearing all enemies in the case of day
void EnemyManager::ClearEnemies(std::list<EntityBase*> entityList)
{
	for (auto it : entityList) {
		GenericEntity* entity;
		if (entity = dynamic_cast<GenericEntity*>(it)) {
			if (entity->objectType == GenericEntity::ENEMY)
				entity->SetIsDone(true);
		}
	}
}
