#include "EnemyRuck.h"
#include "MeshList.h"
#include "PlayerInfo\PlayerInfo.h"
#include "Sound_Engine.h"

EnemyRuck::EnemyRuck(std::string _meshName, Vector3 pos) : EnemyEntity(_meshName)
{
	position = pos;
	stateStack.push(DEFAULT_STATE);
}

EnemyRuck::~EnemyRuck()
{
}

void EnemyRuck::Init()
{
	stateStack.push(DEFAULT_STATE);
	attackElaspedTime = 0;
	attacking = false;
	attackSpeed = 1.5;
	attackType = MELEE_ATTACK;
	damage = 5;
	health = 50;
	size = 2.f;
	scale.Set(size, size, size);
	Pathfind(PathfindNode(position));
	GetRoute();
	direction = (optimalRoute.top() - position).Normalized();
	active = true;
}

void EnemyRuck::Update(double dt)
{
	if (!active)
		return;
	if (!attacking) {
		switch (stateStack.top()) {
		case StateMachine::DEFAULT_STATE:
			// if enemy reached a node
			if ((int)position.x == optimalRoute.top().x && (int)position.z == optimalRoute.top().z) {
				// pop the stack
				optimalRoute.pop();
			}
			// find new direction to next node
			if (optimalRoute.empty())
				stateStack.push(StateMachine::NONE);
			else {
				direction = (optimalRoute.top() - position).Normalized();
			}
			direction.y = 0;
			direction.Normalize();
			direction.x = round(direction.x);
			direction.z = round(direction.z);
			position += direction * speed * dt;
			//updates AABB if enemy move
			SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));
			if (CollisionManager::GetInstance()->CheckPointToSphereCollision(position, Player::GetInstance())) {
				stateStack.push(CHASE_STATE);
				target = Player::GetInstance();
			}
			break;
		case StateMachine::ATTACK_STATE:

			if (target != nullptr) {
				attacking = true;
			}
			else
				stateStack.pop();

			attacking = true;
			CSoundEngine::GetInstance()->playsinglesound("PEW", 0.1f);
			stateStack.pop();

			break;
		case StateMachine::CHASE_STATE:
			try {
				if (target == nullptr)
					stateStack.pop();
				else {
					direction = (target->GetPosition() - position);
					direction.y = 0;
					direction.Normalize();
				}
			}
			catch (std::exception &e) {
				direction.SetZero();
			}
			position += direction * speed * dt;
			SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));
			break;
		default:
			return;
		}
	}
	else if (attacking) {
		Attack(target, dt);
	}

	//Equipment Timer Update
	EquipmentEntity::spikeTimer += (float)dt;
}

void EnemyRuck::CollisionResponse(GenericEntity * thatEntity)
{
}

void EnemyRuck::Attack(GenericEntity * thatEntity, double dt)
{
}

EnemyRuck * Create::Ruck(std::string _meshName, Vector3 pos)
{
	EnemyRuck* ruck = new EnemyRuck(_meshName, pos);
	EntityManager::GetInstance()->AddEntity(ruck);
	return ruck;
}
