#pragma once
#ifndef EQUIPMENT_ENTITY_H
#define EQUIPMENT_ENTITY_H

#include "GenericEntity.h"

class Mesh;

class EquipmentEntity : public GenericEntity {
public:
	EquipmentEntity(const std::string _meshName);
	virtual ~EquipmentEntity();

	enum EQUIPMENT_TYPE {
		EQUIPMENT_TURRET,
		EQUIPMENT_HEALING_STATION,
		EQUIPMENT_FLOOR_SPIKE,
		EQUIPMENT_SHIELD
	}type;

	void Render();

	int GetHealth();
	void SetHealth(int _value);

	int GetLevel();
	void SetLevel(int _value);

	float GetRotation();
	void SetRotation(float _value);

	int GetGridX();
	int GetGridZ();
	void SetGrid(int _x, int _z);

	static float healTimer, healCoolDown,
				 spikeTimer, spikeCoolDown;
private:
	int health;
	int level;
	float rotation;
	int gridX, gridZ;
};

#endif