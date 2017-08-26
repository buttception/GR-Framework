#include "BuildingEntity.h"
#include "EntityManager.h"
#include "BuildingManager.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

BuildingEntity::BuildingEntity(const std::string _meshName)
				: GenericEntity(MeshList::GetInstance()->GetMesh(_meshName))
{
	SetIsFixed(true);
}

BuildingEntity::~BuildingEntity()
{
}

void BuildingEntity::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y + scale.y / 2, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMeshWithLight(modelMesh);
	modelStack.PopMatrix();
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

int BuildingEntity::GetGridX()
{
	return gridX;
}

int BuildingEntity::GetGridZ()
{
	return gridZ;
}

void BuildingEntity::SetGrid(int _x, int _z)
{
	gridX = _x;
	gridZ = _z;
}
