#ifndef ENEMY_TUCK_H
#define ENEMY_TUCK_H

#include "EnemyEntity.h"

// basic enemy type of the game
class EnemyTuck : public EnemyEntity {
public:
	EnemyTuck(std::string _meshName, Vector3 position);
	virtual ~EnemyTuck();

	void Init();
	void Update(double dt);

	void CollisionResponse(GenericEntity* thatEntity);

	void Attack(GenericEntity* thatEntity, double dt);

private:
};

namespace Create {
	EnemyTuck* Tuck(std::string _meshName, Vector3 position);
}

#endif