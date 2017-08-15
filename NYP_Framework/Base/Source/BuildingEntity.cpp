#include "BuildingEntity.h"

BuildingEntity::BuildingEntity()
{
}

BuildingEntity::~BuildingEntity()
{
}

int BuildingEntity::GetHealth()
{
	return health;
}

void BuildingEntity::SetHealth(int _value)
{
	health = _value;
}

int BuildingEntity::GetLevel()
{
	return level;
}

void BuildingEntity::SetLevel(int _value)
{
	level = _value;
}

float BuildingEntity::GetRotation()
{
	return rotation;
}

void BuildingEntity::SetRotation(float _value)
{
	rotation = _value;
}

BuildingEntity* Create::Building(BuildingEntity::BUILDING_TYPE _type, Vector3 pos)
{
	BuildingEntity* b = new BuildingEntity();
	b->type = _type;
	b->SetPosition(pos);


	return b;
}
