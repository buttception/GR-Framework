#include "EnemyEntity.h"
#include "MeshList.h"

EnemyEntity::EnemyEntity(std::string _meshName)
	: GenericEntity(MeshList::GetInstance()->GetMesh(_meshName))
{
	objectType = GenericEntity::ENEMY;
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Init()
{
}

void EnemyEntity::Update(double dt)
{
}

Vector3 EnemyEntity::GetDirection()
{
	return direction;
}

float EnemyEntity::GetSpeed()
{
	return speed;
}
