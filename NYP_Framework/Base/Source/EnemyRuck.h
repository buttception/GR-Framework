#pragma once
#ifndef ENEMY_RUCK_H
#define ENEMY_RUCK_H

#include "EnemyEntity.h"

class EnemyRuck : public EnemyEntity {
public:
	EnemyRuck(std::string _meshName, Vector3 pos);
	~EnemyRuck();

	enum ATTACK_TYPE {
		MELEE_ATTACK,
		RANGED_ATTACK
	}attackType;

	void Init();
	void Update(double dt);

	void CollisionResponse(GenericEntity* thatEntity);

	void Attack(GenericEntity* thatEntity, double dt);

private:
	float range;
};

namespace Create {
	EnemyRuck* Ruck(std::string _meshName, Vector3 pos);
}

#endif