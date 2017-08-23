#include "EnemyManager.h"
#include "EnemyCuck.h"
#include "MyMath.h"

EnemyManager::EnemyManager():
	active(false),
	spawningAngle(0)
{
	enemyCount.insert(std::make_pair("Cuck", 0));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Init()
{
	// find a random angle to start spawning enemies
	spawningAngle = Math::RandIntMinMax(0, 360);

	SpawnEnemies();

	active = true;
}

// purpose of enemy manager is not to update enemy, but decide where and when to create them and destruct them
void EnemyManager::Update(double dt, std::list<EntityBase*> entityList)
{
}

void EnemyManager::End()
{
	ClearEnemies(EntityManager::GetInstance()->GetEntityList());

	// resets the enemy count
	for (auto &it : enemyCount) {
		it.second = 0;
	}
	// clear the route
	while (!route.empty())
		route.pop();

	active = false;
}

void EnemyManager::AddCount(std::string _name)
{
	if(enemyCount.count(_name)){
		enemyCount[_name] += 1;
	}
	else {
		std::cout << "Enemy name not found, nani dafuq\n";
	}
}

// to spawn enemy based on how many days
void EnemyManager::SpawnEnemies()
{
	// when spawn enemy, find optimal route from spawn to core
	if (route.empty()) {
		EnemyEntity* first = Create::Cuck("Cuck", Vector3(310, 0, 250));
		// only need to calculate one optimal route thus saving the stack
		first->Pathfind(PathfindNode(first->GetPosition()));
		route = first->GetRoute();
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
