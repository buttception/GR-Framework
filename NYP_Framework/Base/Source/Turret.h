#ifndef TURRET_H
#define TURRET_H

#include "EquipmentEntity.h"

#include <stack>

class EnemyEntity;

class EquipmentTurret : public EquipmentEntity {
public:
	EquipmentTurret(Vector3 pos);
	~EquipmentTurret();

	void Update(double dt);

	enum STATE {
		ATTACK,
		SEARCH
	}state;

	//returns distance from the collided hit
	bool rayCast(Vector3 dir, Vector3 origin, GenericEntity* hitbox);

	void search();
	void attack();

	void SetDirection(Vector3 _dir) { direction = _dir; }
	Vector3 GetDirection() { return direction; }

private:
	Vector3 direction;
	EnemyEntity* target;

	float projectileSpeed;
	float attackSpeed;
	float attackElasped;
	float range;
	int damage;

	std::stack<STATE>states;
};

namespace Create {
	EquipmentTurret* Turret(Vector3 pos);
}

#endif