#include "EnemyEntity.h"
#include "MeshList.h"
#include "RenderHelper.h"
#include "GraphicsManager.h"

EnemyEntity::EnemyEntity(std::string _meshName)
	: GenericEntity(MeshList::GetInstance()->GetMesh(_meshName))
	,target(nullptr),
	speed(0),
	health(-1),
	damage(-1),
	size(1),
	attacking(false),
	attackSpeed(0),
	attackElaspedTime(0),
	active(false)
{
	objectType = GenericEntity::ENEMY;
	direction.SetZero();
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::Init()
{
}

void EnemyEntity::Render()
{
	if (!active)
		return;
	MS& ms = GraphicsManager::GetInstance()->GetModelStack();
	ms.PushMatrix();
	ms.Translate(position.x, position.y, position.z);
	ms.Rotate(Math::RadianToDegree(atan2(direction.x, direction.z)), 0, 1, 0);
	ms.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMeshWithLight(modelMesh);
	ms.PopMatrix();
}

int EnemyEntity::GetHealth()
{
	return health;
}

void EnemyEntity::SetHealth(int _value)
{
	health = _value;
}


void EnemyEntity::Update(double dt)
{
}

void EnemyEntity::CollisionResponse(GenericEntity * thatEntity)
{
}

void EnemyEntity::Attack(GenericEntity * thatEntity, double dt)
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

void EnemyEntity::Reset()
{
	attacking = false;
	stateStack = std::stack<STATE_TYPE>();
	optimalRoute = std::stack<Vector3>();
	if (!possibleRoutes.empty())
		possibleRoutes.clear();
	attackElaspedTime = 0;
}
