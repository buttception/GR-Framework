#pragma once
#ifndef BUILDING_ENTITY_H
#define BUILDING_ENTITY_H

#include "EntityBase.h"
#include "Collider\Collider.h"

class BuildingEntity : public EntityBase , public Collision{
public:
	enum BUILDING_TYPE {
		BUILDING_WALL,
		BUILDING_DOOR,
		BUILDING_COVER,
		BUILDING_FLOOR
	}type;

	BuildingEntity();
	virtual ~BuildingEntity();

	int GetHealth();
	void SetHealth(int _value);

	int GetLevel();
	void SetLevel(int _value);

	float GetRotation();
	void SetRotation(float _value);

private:
	int health;
	int level;
	float rotation;
	int gridX, gridZ;
};

namespace Create {
	BuildingEntity* Building(BuildingEntity::BUILDING_TYPE _type, Vector3 pos);
}

#endif