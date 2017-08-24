#ifndef ENEMY_CUCK_H
#define ENEMY_CUCK_H

#include "EnemyEntity.h"

// basic enemy type of the game
class EnemyCuck : public EnemyEntity{
public:
	EnemyCuck();
	EnemyCuck(std::string _meshName, Vector3 position);
	virtual ~EnemyCuck();

	void Init();
	void Update(double dt);

	void CollisionResponse(GenericEntity* thatEntity);

	void Attack(GenericEntity* thatEntity, double dt);

private:
};

namespace Create {
	EnemyCuck* Cuck(std::string _meshName, Vector3 position);
}

#endif