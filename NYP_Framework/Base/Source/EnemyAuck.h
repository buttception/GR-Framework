#ifndef ENEMY_AUCK_H
#define ENEMY_AUCK_H

#include "EnemyEntity.h"

// basic enemy type of the game
class EnemyAuck : public EnemyEntity {
public:
	EnemyAuck(std::string _meshName, Vector3 position);
	virtual ~EnemyAuck();

	void Init();
	void Update(double dt);

	void CollisionResponse(GenericEntity* thatEntity);

	void Attack(GenericEntity* thatEntity, double dt);

private:

	float range;
};

namespace Create {
	EnemyAuck* Auck(std::string _meshName, Vector3 position);
}

#endif