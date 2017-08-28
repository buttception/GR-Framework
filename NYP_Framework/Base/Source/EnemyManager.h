#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <map>
#include <list>

#include "SingletonTemplate.h"
#include "EnemyEntity.h"

class EnemyManager : public Singleton<EnemyManager>{
	friend Singleton<EnemyManager>;
public:
	EnemyManager();
	virtual ~EnemyManager();

	// bool for whether the manager is active
	bool active;

	void Init();
	void Update(double dt);

	void End();

	EnemyEntity* FetchEnemy(std::string _type);

	void SpawnEnemies();
	void ClearEnemies();

	void ClearAll();

private:
	// spawning angle for the enemies
	int spawningAngle;
	// spawning angle size to spawn the enemy
	int spawningSize;
	// minimun distance need to spawn the enemy
	int minDistance;
	// maximum distance to spawn enemy
	int maxDistance;
	// keep track of the total number of enemy
	std::map<std::string, std::list<EnemyEntity*>> enemyMap;
	// route to core
	std::stack<Vector3> route;
};

#endif