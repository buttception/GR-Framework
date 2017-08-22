#include "EnemyCuck.h"
#include "MeshList.h"
#include "EnemyManager.h"

EnemyCuck::EnemyCuck(std::string _meshName, Vector3 position) : EnemyEntity(_meshName)
{
	this->position = position;
	stateStack.push(DEFAULT_STATE);
}

EnemyCuck::~EnemyCuck()
{
}

void EnemyCuck::Init()
{
	speed = 10;
	health = 100;
	damage = 10;
	size = 3;
	scale.Set(size, size, size);
	attackSpeed = 1.f;
	direction = (optimalRoute.top()- position).Normalized();
}

void EnemyCuck::Update(double dt)
{
	//if player is not attacking
	if (!attacking) {
		switch (stateStack.top()) {
		case StateMachine::DEFAULT_STATE:
			// if enemy reached a node
			if ((int)position.x == optimalRoute.top().x && (int)position.z == optimalRoute.top().z) {
				// pop the stack
				optimalRoute.pop();
				// find new direction to next node
				if (optimalRoute.empty())
					stateStack.push(StateMachine::NONE);
				else {
					direction = (optimalRoute.top() - position).Normalized();
					direction.x = round(direction.x);
					direction.z = round(direction.z);
				}
			}
			position += direction * speed * dt;
			//updates AABB if enemy move
			SetAABB(Vector3(position.x + size, position.y + size, position.z + size), Vector3(position.x - size, position.y - size, position.z - size));
			break;
		case StateMachine::ATTACK_STATE:
			if (target != nullptr) {
				attacking = true;
			}
			else
				stateStack.pop();
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
	switch (thatEntity->objectType) {
	case GenericEntity::BUILDING:
		//if collide with a building
		//set state to attack mode
		//if enemy is not already in attack mode
		if (stateStack.top() != ATTACK_STATE)
			stateStack.push(ATTACK_STATE);
		target = thatEntity;
		break;
	case GenericEntity::PROJECTILE:

		break;
	default:
		return;
	}
	
}

void EnemyCuck::Attack(GenericEntity * thatEntity, double dt)
{
	attackElaspedTime += dt;
	if (attackElaspedTime >= attackSpeed) {
		std::cout << "attack\n";
		//check if still in contact with its target
		//test if this is too weak against player
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
						target = nullptr;
						//pop the attack state
						stateStack.pop();
					}
				}
			//}
		}
		// resets attack time
		attackElaspedTime = 0.f;
		// stop attack animation
		attacking = false;
	}
	//else
		//std::cout << "waiting for attack speed\n";
}

EnemyCuck * Create::Cuck(std::string _meshName, Vector3 position)
{
	EnemyCuck* cuck = new EnemyCuck(_meshName, position);
	EnemyManager::GetInstance()->AddCount("Cuck");
	EntityManager::GetInstance()->AddEntity(cuck);
	return cuck;
}
