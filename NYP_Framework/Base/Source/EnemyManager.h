#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <map>

#include "SingletonTemplate.h"
#include "EnemyEntity.h"

class EnemyManager : public Singleton<EnemyManager>{
	friend Singleton<EnemyManager>;
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Init();
	void Update(double dt, std::list<EntityBase*> entityList);
	void SpawnEnemies();
	void ClearEnemies(std::list<EntityBase*> entityList);

private:
	// spawning angle for the enemies
	int spawningAngle;
	// enemyCount needed to keep track of how many enemies there are to spawn more or stop spawning
	std::map <std::string, int> enemyCount;
	// route to core
	std::stack<Vector3> route;
};

#endif