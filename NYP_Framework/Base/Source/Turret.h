#ifndef TURRET_H
#define TURRET_H

#include "EquipmentEntity.h"

#include <vector>

class EnemyEntity;

class EquipmentTurret : public EquipmentEntity {
public:
	EquipmentTurret(Vector3 pos);
	~EquipmentTurret();

	void Update(double dt);

	//returns distance from the collided hit
	bool rayCast(Vector3 dir, Vector3 origin, GenericEntity* hitbox);

private:
	Vector3 direction;
	EnemyEntity* target;

	std::vector<GenericEntity*>vision;

	float projectileSpeed;
	float attackSpeed;
	float attackElasped;
	int damage;
};

namespace Create {
	EquipmentTurret* Turret(Vector3 pos);
}

#endif