#include "EnemyRuck.h"
#include "MeshList.h"

EnemyRuck::EnemyRuck(std::string _meshName, Vector3 pos) : EnemyEntity(_meshName)
{
	position = pos;
	stateStack.push(DEFAULT_STATE);
}

EnemyRuck::~EnemyRuck()
{
}

EnemyRuck * Create::Ruck(std::string _meshName, Vector3 pos)
{
	EnemyRuck* ruck = new EnemyRuck(_meshName, pos);
	EntityManager::GetInstance()->AddEntity(ruck);
	return ruck;
}
