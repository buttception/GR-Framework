#ifndef ENEMY_ENTITY_H
#define ENEMY_ENTITY_H

#include "GenericEntity.h"
#include "EnemyAI.h"
#include "EntityManager.h"
#include "CollisionManager.h"

//base enemy entity class for ease of running all updates of its children
class EnemyEntity : public GenericEntity, public EnemyAI {
public:
	EnemyEntity(std::string _meshName);
	virtual ~EnemyEntity();

	virtual void Init();
	void Render();
	virtual void Update(double dt);

	int GetHealth();
	void SetHealth(int _value);

	virtual void CollisionResponse(GenericEntity* thatEntity);

	virtual void Attack(GenericEntity* thatEntity, double dt);

	void SetTarget(GenericEntity* _t) { target = _t; }
	GenericEntity* GetTarget() { return target; }

	Vector3 GetDirection();
	float GetSpeed();

protected:
	GenericEntity* target;

	Vector3 direction;
	float speed;

	int health;
	int damage;
	float size;

	bool attacking;
	float attackSpeed;
	float attackElaspedTime;
};

#endif