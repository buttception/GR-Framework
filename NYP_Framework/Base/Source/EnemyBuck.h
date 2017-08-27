#ifndef ENEMY_BUCK_H
#define ENEMY_BUCK_H

#include "EnemyEntity.h"

// basic enemy type of the game
class EnemyBuck : public EnemyEntity {
public:
	EnemyBuck(std::string _meshName, Vector3 position);
	virtual ~EnemyBuck();

	enum MOVE_SET {
		CHARGE,
		SLAM,
		WHACK
	}moves;

	void Init();
	void Update(double dt);

	void CollisionResponse(GenericEntity* thatEntity);

	void Attack(GenericEntity* thatEntity, double dt);

private:
};

namespace Create {
	EnemyBuck* Buck(std::string _meshName, Vector3 position);
}

#endif