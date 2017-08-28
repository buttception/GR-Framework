#include "EnemyCuck.h"
#include "MeshList.h"
#include "EnemyManager.h"
#include "../Source/Sound_Engine.h"
#include "PlayerInfo\PlayerInfo.h"
#include "SceneText.h"

EnemyCuck::EnemyCuck(std::string _meshName, Vector3 position) : EnemyEntity(_meshName)
{
	this->position = position;
}

EnemyCuck::~EnemyCuck()
{
}

void EnemyCuck::Init()
{
	stateStack.push(DEFAULT_STATE);
	speed = 8.f;
	health = 100;
	damage = 10;
	size = 3.f;
	scale.Set(size, size, size);
	attackSpeed = 1.f;
	optimalRoute.push(Vector3(MAX_CELLS * CELL_SIZE / 2, 0, MAX_CELLS * CELL_SIZE / 2));
	direction = (optimalRoute.top()- position).Normalized();
	active = true;
	
}

void EnemyCuck::Update(double dt)
{
	if (!active)
		return;
	//if player is not attacking
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
			position += direction * speed * (float)dt;
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
			position += direction * speed * (float)dt;
			SetAABB(Vector3(position.x + size / 2, position.y + size / 2, position.z + size / 2), Vector3(position.x - size / 2, position.y - size / 2, position.z - size / 2));
			break;
		default:
			return;
		}
	}
	else if (attacking) {
		Attack(target, dt);
	}
}

void EnemyCuck::CollisionResponse(GenericEntity * thatEntity)
{
	if (active) {
		switch (thatEntity->objectType) {
		case GenericEntity::BUILDING:
			//if collide with a building
			//set state to attack mode
			//if enemy is not already in attack mode
			if (!stateStack.empty())
				if (stateStack.top() != ATTACK_STATE)
					stateStack.push(ATTACK_STATE);
			target = thatEntity;
			break;
		case EntityBase::PROJECTILE:

			break;
		case EntityBase::EQUIPMENT: {
			EquipmentEntity* equipment = dynamic_cast<EquipmentEntity*>(thatEntity);
			// Attack Equipment except floor spike and healing station
			if (stateStack.top() != ATTACK_STATE &&
				equipment->type != EquipmentEntity::EQUIPMENT_FLOOR_SPIKE &&
				equipment->type != EquipmentEntity::EQUIPMENT_HEALING_STATION)
			{
				stateStack.push(ATTACK_STATE);
				target = thatEntity;
			}
			break;
			switch (equipment->type) {
			case EquipmentEntity::EQUIPMENT_TURRET:
				std::cout << "collided with turret" << std::endl;
				break;
			case EquipmentEntity::EQUIPMENT_FLOOR_SPIKE:
				if (equipment->spikeTimer >= equipment->spikeCoolDown)
				{
					health = Math::Max(0, health - 10);
					speed = 2.f;
					equipment->spikeTimer = 0.f;
				}
				if (health == 0)
					SetIsDone(true);
				break;
			case EquipmentEntity::EQUIPMENT_SHIELD:
				std::cout << "collided with shield" << std::endl;
				break;
			}
		}
			break;
		default:
			return;
		}
	}
	else
		return;
}

void EnemyCuck::Attack(GenericEntity * thatEntity, double dt)
{
	attackElaspedTime += (float)dt;
	if (attackElaspedTime >= attackSpeed) {
		CSoundEngine::GetInstance()->playsinglesound("MELEE", 0.1f);
		//check if still in contact with its target
		//test if this is too weak against player
		if (target)
		{
		//if (CollisionManager::GetInstance()->CheckAABBCollision(this, thatEntity)){
			if (thatEntity->objectType == BUILDING) {
				BuildingEntity* building = dynamic_cast<BuildingEntity*>(thatEntity);
				if (building) {
					// damage the building
					building->SetHealth(building->GetHealth() - damage);
					std::cout << "building health: " << building->GetHealth() << std::endl;
					// check if the building is dead
					if (building->GetHealth() <= 0) {
						//destroy the building
						building->SetIsDone(true);
						if (building->type != BuildingEntity::BUILDING_CORE) {
							if (building->tile->leftWall == building) {
								building->tile->leftWall = nullptr;
							}
							else if (building->tile->rightWall == building) {
								building->tile->rightWall = nullptr;
							}
							else if (building->tile->topWall == building) {
								building->tile->topWall = nullptr;
							}
							else if (building->tile->bottomWall == building) {
								building->tile->bottomWall = nullptr;
							}
						}
						if (stateStack.top() == CHASE_STATE)
							target = Player::GetInstance();
						else
							target = nullptr;
					}
				}
				//}
			}
			else {
				if (stateStack.top() == CHASE_STATE)
					target = Player::GetInstance();
			}
		}
		// resets attack time
		attackElaspedTime = 0.f;
		// stop attack animation
		attacking = false;

		/*if (CollisionManager::GetInstance()->CheckPointToSphereCollision(position, Player::GetInstance())) {
			stateStack.push(CHASE_STATE);
			target = Player::GetInstance();
		}*/

		if (!stateStack.empty())
			if (stateStack.top() == ATTACK_STATE)
				stateStack.pop();
	}
}

EnemyCuck * Create::Cuck(std::string _meshName, Vector3 position)
{
	EnemyCuck* cuck = new EnemyCuck(_meshName, position);
	EntityManager::GetInstance()->AddEntity(cuck);
	return cuck;
}
