#include "EquipmentEntity.h"
#include "EntityManager.h"
#include "BuildingManager.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

EquipmentEntity::EquipmentEntity(const std::string _meshName)
	: GenericEntity(MeshList::GetInstance()->GetMesh(_meshName))
	, healTimer(0.f)
	, healCoolDown(3.f)
	, spikeTimer(0.f)
	, spikeCoolDown(2.f)
{
	modelMesh = MeshList::GetInstance()->GetMesh(_meshName);
	SetIsFixed(true);
}

EquipmentEntity::~EquipmentEntity()
{
}

void EquipmentEntity::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMeshWithLight(modelMesh);
	modelStack.PopMatrix();
}

void EquipmentEntity::Update(double dt)
{
	healTimer += (float)dt;
	spikeTimer += (float)dt;
}

int EquipmentEntity::GetHealth()
{
	return health;
}

void EquipmentEntity::SetHealth(int _value)
{
	health = _value;
}

int EquipmentEntity::GetLevel()
{
	return level;
}

void EquipmentEntity::SetLevel(int _value)
{
	level = _value;
}

float EquipmentEntity::GetRotation()
{
	return rotation;
}

void EquipmentEntity::SetRotation(float _value)
{
	rotation = _value;
}

int EquipmentEntity::GetGridX()
{
	return gridX;
}

int EquipmentEntity::GetGridZ()
{
	return gridZ;
}

void EquipmentEntity::SetGrid(int _x, int _z)
{
	gridX = _x;
	gridZ = _z;
}
